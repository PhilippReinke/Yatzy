//
// SuspensionManager.cpp
// Implementierung der SuspensionManager-Klasse
//

#include "pch.h"
#include "SuspensionManager.h"

#include <algorithm>

using namespace Yatzy::Common;

using namespace concurrency;
using namespace Platform;
using namespace Platform::Collections;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::Storage;
using namespace Windows::Storage::FileProperties;
using namespace Windows::Storage::Streams;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Interop;

Map<String^, Object^>^ SuspensionManager::_sessionState = ref new Map<String^, Object^>();

const wchar_t* SuspensionManager::sessionStateFilename = L"_sessionState.dat";

std::vector<WeakReference> SuspensionManager::_registeredFrames;

DependencyProperty^ SuspensionManager::FrameSessionStateKeyProperty =
	DependencyProperty::RegisterAttached("_FrameSessionStateKeyProperty",
	TypeName(String::typeid), TypeName(SuspensionManager::typeid), nullptr);

DependencyProperty^ SuspensionManager::FrameSessionBaseKeyProperty =
	DependencyProperty::RegisterAttached("_FrameSessionBaseKeyProperty",
	TypeName(String::typeid), TypeName(SuspensionManager::typeid), nullptr);

DependencyProperty^ SuspensionManager::FrameSessionStateProperty =
	DependencyProperty::RegisterAttached("_FrameSessionStateProperty",
	TypeName(IMap<String^, Object^>::typeid), TypeName(SuspensionManager::typeid), nullptr);

class ObjectSerializeHelper
{
public:
	// Codes zum Identifizieren von serialisierten Typen
	enum StreamTypes {
		NullPtrType = 0,

		// Unterstützte IPropertyValue-Typen
		UInt8Type, UInt16Type, UInt32Type, UInt64Type, Int16Type, Int32Type, Int64Type,
		SingleType, DoubleType, BooleanType, Char16Type, GuidType, StringType,

		// Weitere unterstützte Typen
		StringToObjectMapType,

		// Markierungswerte zum Sicherstellen der Datenstromintegrität
		MapEndMarker
	};
	static String^ ReadString(DataReader^ reader);
	static IMap<String^, Object^>^ ReadStringToObjectMap(DataReader^ reader);
	static Object^ ReadObject(DataReader^ reader);
	static void WriteString(DataWriter^ writer, String^ string);
	static void WriteProperty(DataWriter^ writer, IPropertyValue^ propertyValue);
	static void WriteStringToObjectMap(DataWriter^ writer, IMap<String^, Object^>^ map);
	static void WriteObject(DataWriter^ writer, Object^ object);
};

/// <summary>
/// Bietet Zugriff auf den globalen Sitzungszustand für die aktuelle Sitzung.  Dieser Zustand wird von
/// <see cref="SaveAsync"/> serialisiert und von <see cref="RestoreAsync"/> wiederhergestellt. Daher müssen Werte die folgenden
/// Typen aufweisen: geschachtelte Werte wie Ganzzahlen, einzelne und doppelte Gleitkommawerte,
/// Breitzeichen, boolesche Werte, Zeichenfolgen und GUIDs oder Map<String^, Object^>, wobei für Zuordnungswerte
/// die gleichen Beschränkungen gelten.  Der Sitzungszustand sollte so kompakt wie möglich sein.
/// </summary>
IMap<String^, Object^>^ SuspensionManager::SessionState()
{
	return _sessionState;
}

/// <summary>
/// Registriert eine <see cref="Frame"/>-Instanz, um den zugehörigen Navigationsverlauf mithilfe von
/// <see cref="SessionState"/> speichern und wiederherstellen zu können.  Rahmen sollten direkt nach der Erstellung
/// registriert werden, wenn diese Bestandteil der Verwaltung des Sitzungszustands sind.  Wenn der
/// Zustand für den speziellen Schlüssel bereits wiederhergestellt wurde,
/// wird der Navigationsverlauf bei der Registrierung sofort wiederhergestellt.  Bei nachfolgenden Aufrufen von
/// <see cref="RestoreAsync(String)"/> wird der Navigationsverlauf ebenfalls wiederhergestellt.
/// </summary>
/// <param name="frame">Eine Instanz, deren Navigationsverlauf von
/// <see cref="SuspensionManager"/> verwaltet werden soll</param>
/// <param name="sessionStateKey">Ein eindeutiger Schlüssel in <see cref="SessionState"/> zum
/// Speichern von navigationsbezogenen Informationen.</param>
/// <param name="sessionBaseKey">Ein optionaler Schlüssel zum Identifizieren des Typs der Sitzung.
/// Damit können verschiedene Szenarien für den Anwendungsstart unterschieden werden.</param>
void SuspensionManager::RegisterFrame(Frame^ frame, String^ sessionStateKey, String^ sessionBaseKey)
{
	if (frame->GetValue(FrameSessionStateKeyProperty) != nullptr)
	{
		throw ref new FailureException("Frames can only be registered to one session state key");
	}

	if (frame->GetValue(FrameSessionStateProperty) != nullptr)
	{
		throw ref new FailureException("Frames must be either be registered before accessing frame session state, or not registered at all");
	}

	if (sessionBaseKey != nullptr)
	{
		frame->SetValue(FrameSessionBaseKeyProperty, sessionBaseKey);
		sessionStateKey = sessionBaseKey + "_" + sessionStateKey;
	}

	// Eine Abhängigkeitseigenschaft verwenden, um den Sitzungsschlüssel mit einem Rahmen zu verknüpfen, und eine Liste von Rahmen speichern, deren
	// Navigationszustand verwaltet werden soll
	frame->SetValue(FrameSessionStateKeyProperty, sessionStateKey);
	_registeredFrames.insert(_registeredFrames.begin(), WeakReference(frame));

	// Überprüfen, ob der Navigationszustand wiederhergestellt werden kann
	RestoreFrameNavigationState(frame);
}

/// <summary>
/// Hebt die Verknüpfung eines <see cref="Frame"/>, der zuvor durch <see cref="RegisterFrame"/> registriert wurde,
/// mit <see cref="SessionState"/> auf.  Alle zuvor erfassten Navigationszustände werden
/// entfernt.
/// </summary>
/// <param name="frame">Eine Instanz, deren Navigationsverlauf nicht mehr
/// verwaltet werden soll.</param>
void SuspensionManager::UnregisterFrame(Frame^ frame)
{
	// Sitzungszustand und Rahmen aus der Liste der Rahmen entfernen, deren Navigationszustand
	// gespeichert wird (gemeinsam mit allen schwachen Verweisen, die nicht mehr erreichbar sind)
	auto key = safe_cast<String^>(frame->GetValue(FrameSessionStateKeyProperty));
	if (SessionState()->HasKey(key))
	{
		SessionState()->Remove(key);
	}
	_registeredFrames.erase(
		std::remove_if(_registeredFrames.begin(), _registeredFrames.end(), [=](WeakReference& e)
	{
		auto testFrame = e.Resolve<Frame>();
		return testFrame == nullptr || testFrame == frame;
	}),
		_registeredFrames.end()
		);
}

/// <summary>
/// Bietet Speichermöglichkeit für den Sitzungszustand, der mit dem angegebenen <see cref="Frame"/> verknüpft ist.
/// Für Rahmen, die zuvor mit <see cref="RegisterFrame"/> registriert wurden, wird der
/// Sitzungszustand automatisch als Teil des globalen <see cref="SessionState"/>
/// gespeichert und wiederhergestellt.  Rahmen, die nicht registriert sind, verfügen über einen vorübergehenden Zustand,
/// der weiterhin nützlich sein kann, wenn Seiten wiederhergestellt werden, die aus dem
/// Navigationscache gelöscht wurden.
/// </summary>
/// <remarks>Apps können beim Verwalten des seitenspezifischen Zustands auf <see cref="NavigationHelper"/> zurückgreifen,
/// anstatt direkt mit dem Rahmensitzungszustand zu arbeiten.</remarks>
/// <param name="frame">Die Instanz, für die der Sitzungszustand gewünscht wird.</param>
/// <returns>Eine Auflistung des Zustands, für den der gleiche Serialisierungsmechanismus wie für
/// <see cref="SessionState"/> gilt.</returns>
IMap<String^, Object^>^ SuspensionManager::SessionStateForFrame(Frame^ frame)
{
	auto frameState = safe_cast<IMap<String^, Object^>^>(frame->GetValue(FrameSessionStateProperty));

	if (frameState == nullptr)
	{
		auto frameSessionKey = safe_cast<String^>(frame->GetValue(FrameSessionStateKeyProperty));
		if (frameSessionKey != nullptr)
		{
			// Registrierte Rahmen geben den entsprechenden Sitzungszustand wieder.
			if (!_sessionState->HasKey(frameSessionKey))
			{
				_sessionState->Insert(frameSessionKey, ref new Map<String^, Object^>());
			}
			frameState = safe_cast<IMap<String^, Object^>^>(_sessionState->Lookup(frameSessionKey));
		}
		else
		{
			// Rahmen, die nicht registriert sind, verfügen über einen vorübergehenden Zustand
			frameState = ref new Map<String^, Object^>();
		}
		frame->SetValue(FrameSessionStateProperty, frameState);
	}
	return frameState;
}

void SuspensionManager::RestoreFrameNavigationState(Frame^ frame)
{
	auto frameState = SessionStateForFrame(frame);
	if (frameState->HasKey("Navigation"))
	{
		frame->SetNavigationState(safe_cast<String^>(frameState->Lookup("Navigation")));
	}
}

void SuspensionManager::SaveFrameNavigationState(Frame^ frame)
{
	auto frameState = SessionStateForFrame(frame);
	frameState->Insert("Navigation", frame->GetNavigationState());
}

/// <summary>
/// Den aktuellen <see cref="SessionState"/> speichern.  Alle <see cref="Frame"/>-Instanzen,
/// die bei <see cref="RegisterFrame"/> registriert wurden, behalten ebenfalls ihren aktuellen
/// Navigationsstapel bei, wodurch deren aktive <see cref="Page"/> eine Gelegenheit
/// zum Speichern des zugehörigen Zustands erhält.
/// </summary>
/// <returns>Eine asynchrone Aufgabe, die das Speichern des Sitzungszustands wiedergibt.</returns>
task<void> SuspensionManager::SaveAsync(void)
{
	// Navigationszustand für alle registrierten Rahmen speichern
	for (auto && weakFrame : _registeredFrames)
	{
		auto frame = weakFrame.Resolve<Frame>();
		if (frame != nullptr) SaveFrameNavigationState(frame);
	}

	// Sitzungszustand synchron serialisieren, um einen asynchronen Zugriff auf den freigegebenen
	// Zustand zu vermeiden
	auto sessionData = ref new InMemoryRandomAccessStream();
	auto sessionDataWriter = ref new DataWriter(sessionData->GetOutputStreamAt(0));
	ObjectSerializeHelper::WriteObject(sessionDataWriter, _sessionState);

	// Mit dem asynchronen Vorgang zum Schreiben des Ergebnisses auf den Datenträger beginnen,
	// sobald der Sitzungszustand erfasst wurde
	return task<unsigned int>(sessionDataWriter->StoreAsync()).then([=](unsigned int)
	{
		return ApplicationData::Current->LocalFolder->CreateFileAsync(StringReference(sessionStateFilename),
			CreationCollisionOption::ReplaceExisting);
	})
		.then([=](StorageFile^ createdFile)
	{
		return createdFile->OpenAsync(FileAccessMode::ReadWrite);
	})
		.then([=](IRandomAccessStream^ newStream)
	{
		return RandomAccessStream::CopyAsync(
			sessionData->GetInputStreamAt(0), newStream->GetOutputStreamAt(0));
	})
		.then([=](UINT64 copiedBytes)
	{
		(void) copiedBytes; // Nicht verwendeter Parameter
		return;
	});
}

/// <summary>
/// Stellt den zuvor gespeicherten <see cref="SessionState"/> wieder her.  Für alle <see cref="Frame"/>-Instanzen,
/// die bei <see cref="RegisterFrame"/> registriert wurden, wird ebenfalls der vorherige
/// Navigationszustand wiederhergestellt, wodurch deren aktive <see cref="Page"/> eine Gelegenheit zum Wiederherstellen
/// des Zustands erhält.
/// </summary>
/// <param name="sessionBaseKey">Ein optionaler Schlüssel zum Identifizieren des Typs der Sitzung.
/// Damit können verschiedene Szenarien für den Anwendungsstart unterschieden werden.</param>
/// <returns>Eine asynchrone Aufgabe, die das Lesen des Sitzungszustands wiedergibt.  Auf den
/// Inhalt von <see cref="SessionState"/> sollte erst zurückgegriffen werden, wenn diese Aufgabe
/// abgeschlossen ist.</returns>
task<void> SuspensionManager::RestoreAsync(String^ sessionBaseKey)
{
	_sessionState->Clear();

	task<StorageFile^> getFileTask(ApplicationData::Current->LocalFolder->GetFileAsync(StringReference(sessionStateFilename)));
	return getFileTask.then([=](StorageFile^ stateFile)
	{
		task<BasicProperties^> getBasicPropertiesTask(stateFile->GetBasicPropertiesAsync());
		return getBasicPropertiesTask.then([=](BasicProperties^ stateFileProperties)
		{
			auto size = unsigned int(stateFileProperties->Size);
			if (size != stateFileProperties->Size) throw ref new FailureException("Session state larger than 4GB");
			task<IRandomAccessStreamWithContentType^> openReadTask(stateFile->OpenReadAsync());
			return openReadTask.then([=](IRandomAccessStreamWithContentType^ stateFileStream)
			{
				auto stateReader = ref new DataReader(stateFileStream);
				return task<unsigned int>(stateReader->LoadAsync(size)).then([=](unsigned int bytesRead)
				{
					(void) bytesRead; // Nicht verwendeter Parameter
					// Sitzungszustand deserialisieren
					Object^ content = ObjectSerializeHelper::ReadObject(stateReader);
					_sessionState = (Map<String^, Object^>^)content;

					// Alle registrierten Rahmen auf den gespeicherten Zustand wiederherstellen
					for (auto && weakFrame : _registeredFrames)
					{
						auto frame = weakFrame.Resolve<Frame>();
						if (frame != nullptr && safe_cast<String^>(frame->GetValue(FrameSessionBaseKeyProperty)) == sessionBaseKey)
						{
							frame->ClearValue(FrameSessionStateProperty);
							RestoreFrameNavigationState(frame);
						}
					}
				}, task_continuation_context::use_current());
			});
		});
	});
}

#pragma region Object serialization for a known set of types

void ObjectSerializeHelper::WriteString(DataWriter^ writer, String^ string)
{
	writer->WriteByte(StringType);
	writer->WriteUInt32(writer->MeasureString(string));
	writer->WriteString(string);
}

void ObjectSerializeHelper::WriteProperty(DataWriter^ writer, IPropertyValue^ propertyValue)
{
	switch (propertyValue->Type)
	{
	case PropertyType::UInt8:
		writer->WriteByte(StreamTypes::UInt8Type);
		writer->WriteByte(propertyValue->GetUInt8());
		return;
	case PropertyType::UInt16:
		writer->WriteByte(StreamTypes::UInt16Type);
		writer->WriteUInt16(propertyValue->GetUInt16());
		return;
	case PropertyType::UInt32:
		writer->WriteByte(StreamTypes::UInt32Type);
		writer->WriteUInt32(propertyValue->GetUInt32());
		return;
	case PropertyType::UInt64:
		writer->WriteByte(StreamTypes::UInt64Type);
		writer->WriteUInt64(propertyValue->GetUInt64());
		return;
	case PropertyType::Int16:
		writer->WriteByte(StreamTypes::Int16Type);
		writer->WriteUInt16(propertyValue->GetInt16());
		return;
	case PropertyType::Int32:
		writer->WriteByte(StreamTypes::Int32Type);
		writer->WriteUInt32(propertyValue->GetInt32());
		return;
	case PropertyType::Int64:
		writer->WriteByte(StreamTypes::Int64Type);
		writer->WriteUInt64(propertyValue->GetInt64());
		return;
	case PropertyType::Single:
		writer->WriteByte(StreamTypes::SingleType);
		writer->WriteSingle(propertyValue->GetSingle());
		return;
	case PropertyType::Double:
		writer->WriteByte(StreamTypes::DoubleType);
		writer->WriteDouble(propertyValue->GetDouble());
		return;
	case PropertyType::Boolean:
		writer->WriteByte(StreamTypes::BooleanType);
		writer->WriteBoolean(propertyValue->GetBoolean());
		return;
	case PropertyType::Char16:
		writer->WriteByte(StreamTypes::Char16Type);
		writer->WriteUInt16(propertyValue->GetChar16());
		return;
	case PropertyType::Guid:
		writer->WriteByte(StreamTypes::GuidType);
		writer->WriteGuid(propertyValue->GetGuid());
		return;
	case PropertyType::String:
		WriteString(writer, propertyValue->GetString());
		return;
	default:
		throw ref new InvalidArgumentException("Unsupported property type");
	}
}

void ObjectSerializeHelper::WriteStringToObjectMap(DataWriter^ writer, IMap<String^, Object^>^ map)
{
	writer->WriteByte(StringToObjectMapType);
	writer->WriteUInt32(map->Size);
	for (auto && pair : map)
	{
		WriteObject(writer, pair->Key);
		WriteObject(writer, pair->Value);
	}
	writer->WriteByte(MapEndMarker);
}

void ObjectSerializeHelper::WriteObject(DataWriter^ writer, Object^ object)
{
	if (object == nullptr)
	{
		writer->WriteByte(NullPtrType);
		return;
	}

	auto propertyObject = dynamic_cast<IPropertyValue^>(object);
	if (propertyObject != nullptr)
	{
		WriteProperty(writer, propertyObject);
		return;
	}

	auto mapObject = dynamic_cast<IMap<String^, Object^>^>(object);
	if (mapObject != nullptr)
	{
		WriteStringToObjectMap(writer, mapObject);
		return;
	}

	throw ref new InvalidArgumentException("Unsupported data type");
}

String^ ObjectSerializeHelper::ReadString(DataReader^ reader)
{
	int length = reader->ReadUInt32();
	String^ string = reader->ReadString(length);
	return string;
}

IMap<String^, Object^>^ ObjectSerializeHelper::ReadStringToObjectMap(DataReader^ reader)
{
	auto map = ref new Map<String^, Object^>();
	auto size = reader->ReadUInt32();
	for (unsigned int index = 0; index < size; index++)
	{
		auto key = safe_cast<String^>(ReadObject(reader));
		auto value = ReadObject(reader);
		map->Insert(key, value);
	}
	if (reader->ReadByte() != StreamTypes::MapEndMarker)
	{
		throw ref new InvalidArgumentException("Invalid stream");
	}
	return map;
}

Object^ ObjectSerializeHelper::ReadObject(DataReader^ reader)
{
	auto type = reader->ReadByte();
	switch (type)
	{
	case StreamTypes::NullPtrType:
		return nullptr;
	case StreamTypes::UInt8Type:
		return reader->ReadByte();
	case StreamTypes::UInt16Type:
		return reader->ReadUInt16();
	case StreamTypes::UInt32Type:
		return reader->ReadUInt32();
	case StreamTypes::UInt64Type:
		return reader->ReadUInt64();
	case StreamTypes::Int16Type:
		return reader->ReadInt16();
	case StreamTypes::Int32Type:
		return reader->ReadInt32();
	case StreamTypes::Int64Type:
		return reader->ReadInt64();
	case StreamTypes::SingleType:
		return reader->ReadSingle();
	case StreamTypes::DoubleType:
		return reader->ReadDouble();
	case StreamTypes::BooleanType:
		return reader->ReadBoolean();
	case StreamTypes::Char16Type:
		return (char16_t) reader->ReadUInt16();
	case StreamTypes::GuidType:
		return reader->ReadGuid();
	case StreamTypes::StringType:
		return ReadString(reader);
	case StreamTypes::StringToObjectMapType:
		return ReadStringToObjectMap(reader);
	default:
		throw ref new InvalidArgumentException("Unsupported property type");
	}
}

#pragma endregion
