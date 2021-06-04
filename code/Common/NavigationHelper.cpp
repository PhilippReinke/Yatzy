//
// NavigationHelper.cpp
// Implementierung der NavigationHelper-Klasse und verknüpfter Klassen
//

#include "pch.h"
#include "NavigationHelper.h"
#include "RelayCommand.h"
#include "SuspensionManager.h"

using namespace Yatzy::Common;

using namespace Platform;
using namespace Platform::Collections;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::System;
using namespace Windows::UI::Core;
using namespace Windows::UI::ViewManagement;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Interop;
using namespace Windows::UI::Xaml::Navigation;

#if WINAPI_FAMILY==WINAPI_FAMILY_PHONE_APP
using namespace Windows::Phone::UI::Input;
#endif

/// <summary>
/// Initialisiert eine neue Instanz der <see cref="LoadStateEventArgs"/>-Klasse.
/// </summary>
/// <param name="navigationParameter">
/// Der an <see cref="Frame->Navigate(Type, Object)"/> übergebene Parameterwert 
/// übergeben wurde, als diese Seite ursprünglich angefordert wurde.
/// </param>
/// <param name="pageState">
/// Ein Wörterbuch des Zustands, der von dieser Seite während einer früheren
/// beibehalten wurde.  Beim ersten Aufrufen einer Seite ist dieser Wert NULL.
/// </param>
LoadStateEventArgs::LoadStateEventArgs(Object^ navigationParameter, IMap<String^, Object^>^ pageState)
{
	_navigationParameter = navigationParameter;
	_pageState = pageState;
}

/// <summary>
/// Ruft die <see cref="NavigationParameter"/>-Eigenschaft der <see cref"LoadStateEventArgs"/>-Klasse ab.
/// </summary>
Object^ LoadStateEventArgs::NavigationParameter::get()
{
	return _navigationParameter;
}

/// <summary>
/// Ruft die <see cref="PageState"/>-Eigenschaft der <see cref"LoadStateEventArgs"/>-Klasse ab.
/// </summary>
IMap<String^, Object^>^ LoadStateEventArgs::PageState::get()
{
	return _pageState;
}

/// <summary>
/// Initialisiert eine neue Instanz der <see cref="SaveStateEventArgs"/>-Klasse.
/// </summary>
/// <param name="pageState">Ein leeres Wörterbuch, das mit dem serialisierbaren Zustand aufgefüllt wird.</param>
SaveStateEventArgs::SaveStateEventArgs(IMap<String^, Object^>^ pageState)
{
	_pageState = pageState;
}

/// <summary>
/// Ruft die <see cref="PageState"/>-Eigenschaft der <see cref"SaveStateEventArgs"/>-Klasse ab.
/// </summary>
IMap<String^, Object^>^ SaveStateEventArgs::PageState::get()
{
	return _pageState;
}

/// <summary>
/// Initialisiert eine neue Instanz der <see cref="NavigationHelper"/>-Klasse.
/// </summary>
/// <param name="page">Ein Verweis auf die aktuelle für die Navigation verwendete Seite.  
/// Dieser Verweis ermöglicht eine Änderung des Rahmens und stellt sicher, dass die Tastatur 
/// Navigationsanforderungen treten nur auf, wenn die Seite das gesamte Fenster einnimmt.</param>
NavigationHelper::NavigationHelper(Page^ page, RelayCommand^ goBack, RelayCommand^ goForward) :
_page(page),
_goBackCommand(goBack),
_goForwardCommand(goForward)
{
	// Zwei Änderungen vornehmen, wenn diese Seite Teil der visuellen Struktur ist:
	// 1) Den Ansichtszustand der Anwendung dem visuellen Zustand für die Seite zuordnen
	// 2) Behandeln von Hardwarenavigationsanforderungen
	_loadedEventToken = page->Loaded += ref new RoutedEventHandler(this, &NavigationHelper::OnLoaded);

	//// Dieselben Änderungen rückgängig machen, wenn die Seite nicht mehr sichtbar ist
	_unloadedEventToken = page->Unloaded += ref new RoutedEventHandler(this, &NavigationHelper::OnUnloaded);
}

NavigationHelper::~NavigationHelper()
{
	delete _goBackCommand;
	delete _goForwardCommand;

	_page = nullptr;
}

/// <summary>
/// Wird aufgerufen, wenn die Seite Teil der visuellen Struktur ist
/// </summary>
/// <param name="sender">Instanz, von der das Ereignis ausgelöst wurde.</param>
/// <param name="e">Ereignisdaten, die die Bedingungen beschreiben, die zu dem Ereignis geführt haben.</param>
void NavigationHelper::OnLoaded(Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
#if WINAPI_FAMILY==WINAPI_FAMILY_PHONE_APP
	_backPressedEventToken = HardwareButtons::BackPressed +=
		ref new EventHandler<BackPressedEventArgs^>(this,
		&NavigationHelper::HardwareButton_BackPressed);
#else
	Page ^page = _page.Resolve<Page>();

	// Tastatur- und Mausnavigation trifft nur zu, wenn das gesamte Fenster ausgefüllt wird.
	if (page != nullptr &&
		page->ActualHeight == Window::Current->Bounds.Height &&
		page->ActualWidth == Window::Current->Bounds.Width)
	{
		// Direkt am Fenster lauschen, sodass kein Fokus erforderlich ist
		_acceleratorKeyEventToken = Window::Current->CoreWindow->Dispatcher->AcceleratorKeyActivated +=
			ref new TypedEventHandler<CoreDispatcher^, AcceleratorKeyEventArgs^>(this,
			&NavigationHelper::CoreDispatcher_AcceleratorKeyActivated);

		_pointerPressedEventToken = Window::Current->CoreWindow->PointerPressed +=
			ref new TypedEventHandler<CoreWindow^, PointerEventArgs^>(this,
			&NavigationHelper::CoreWindow_PointerPressed);

		_navigationShortcutsRegistered = true;
	}
#endif
}

/// <summary>
/// Wird aufgerufen, wenn die Seite aus der visuellen Struktur entfernt wird
/// </summary>
/// <param name="sender">Instanz, von der das Ereignis ausgelöst wurde.</param>
/// <param name="e">Ereignisdaten, die die Bedingungen beschreiben, die zu dem Ereignis geführt haben.</param>
void NavigationHelper::OnUnloaded(Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
#if WINAPI_FAMILY==WINAPI_FAMILY_PHONE_APP
	HardwareButtons::BackPressed -= _backPressedEventToken;
#else
	if (_navigationShortcutsRegistered)
	{
		Window::Current->CoreWindow->Dispatcher->AcceleratorKeyActivated -= _acceleratorKeyEventToken;
		Window::Current->CoreWindow->PointerPressed -= _pointerPressedEventToken;
		_navigationShortcutsRegistered = false;
	}
#endif

	// Den Handler entfernen und den Seitenverweis freigeben
	Page ^page = _page.Resolve<Page>();
	if (page != nullptr)
	{
		page->Loaded -= _loadedEventToken;
		page->Unloaded -= _unloadedEventToken;
		delete _goBackCommand;
		delete _goForwardCommand;
		_goForwardCommand = nullptr;
		_goBackCommand = nullptr;
	}
}

#pragma region Navigation support

/// <summary>
/// Von der <see cref="GoBackCommand"/>-Eigenschaft verwendete Methode
/// um zu bestimmen, ob <see cref="Frame"/> zurückgesetzt werden kann.
/// </summary>
/// <returns>
/// "True", wenn <see cref="Frame"/> mindestens einen Eintrag aufweist 
/// im Rückwärtsnavigationsverlauf.
/// </returns>
bool NavigationHelper::CanGoBack()
{
	Page ^page = _page.Resolve<Page>();
	if (page != nullptr)
	{
		auto frame = page->Frame;
		return (frame != nullptr && frame->CanGoBack);
	}

	return false;
}

/// <summary>
/// Von der <see cref="GoBackCommand"/>-Eigenschaft verwendete Methode
/// um die <see cref="Windows::UI::Xaml::Controls::Frame::GoBack"/>-Methode aufzurufen.
/// </summary>
void NavigationHelper::GoBack()
{
	Page ^page = _page.Resolve<Page>();
	if (page != nullptr)
	{
		auto frame = page->Frame;
		if (frame != nullptr && frame->CanGoBack)
		{
			frame->GoBack();
		}
	}
}

/// <summary>
/// Von der <see cref="GoForwardCommand"/>-Eigenschaft verwendete Methode
/// um zu bestimmen, ob <see cref="Frame"/> fortgesetzt werden kann.
/// </summary>
/// <returns>
/// "True", wenn <see cref="Frame"/> mindestens einen Eintrag aufweist 
/// im Vorwärtsnavigationsverlauf.
/// </returns>
bool NavigationHelper::CanGoForward()
{
	Page ^page = _page.Resolve<Page>();
	if (page != nullptr)
	{
		auto frame = page->Frame;
		return (frame != nullptr && frame->CanGoForward);
	}

	return false;
}

/// <summary>
/// Von der <see cref="GoForwardCommand"/>-Eigenschaft verwendete Methode
/// um die <see cref="Windows::UI::Xaml::Controls::Frame::GoBack"/>-Methode aufzurufen.
/// </summary>
void NavigationHelper::GoForward()
{
	Page ^page = _page.Resolve<Page>();
	if (page != nullptr)
	{
		auto frame = page->Frame;
		if (frame != nullptr && frame->CanGoForward)
		{
			frame->GoForward();
		}
	}
}

/// <summary>
/// Ruft die <see cref="GoBackCommand"/>-Eigenschaft der <see cref"NavigationHelper"/>-Klasse ab.
/// </summary>
RelayCommand^ NavigationHelper::GoBackCommand::get()
{
	if (_goBackCommand == nullptr)
	{
		_goBackCommand = ref new RelayCommand(
			[this](Object^) -> bool
		{
			return CanGoBack();
		},
			[this](Object^) -> void
		{
			GoBack();
		}
		);
	}
	return _goBackCommand;
}

/// <summary>
/// Ruft die <see cref="GoForwardCommand"/>-Eigenschaft der <see cref"NavigationHelper"/>-Klasse ab.
/// </summary>
RelayCommand^ NavigationHelper::GoForwardCommand::get()
{
	if (_goForwardCommand == nullptr)
	{
		_goForwardCommand = ref new RelayCommand(
			[this](Object^) -> bool
		{
			return CanGoForward();
		},
			[this](Object^) -> void
		{
			GoForward();
		}
		);
	}
	return _goForwardCommand;
}

#if WINAPI_FAMILY==WINAPI_FAMILY_PHONE_APP
/// <summary>
/// Behandelt das Verhalten der Schaltfläche "Zurück" und navigiert durch den Verlauf des Stammframes.
/// </summary>
void NavigationHelper::HardwareButton_BackPressed(Object^ sender, BackPressedEventArgs^ e)
{
	if (this->GoBackCommand->CanExecute(nullptr))
	{
		e->Handled = true;
		this->GoBackCommand->Execute(nullptr);
	}
}
#else
/// <summary>
/// Wird bei jeder Tastatureingabe aufgerufen, einschließlich Systemtasten wie ALT-Tastenkombinationen, wenn
/// diese Seite aktiv ist und das gesamte Fenster ausfüllt.  Wird zum Erkennen von Tastaturnavigation verwendet
/// zwischen Seiten, auch wenn die Seite selbst nicht den Fokus hat.
/// </summary>
/// <param name="sender">Instanz, von der das Ereignis ausgelöst wurde.</param>
/// <param name="e">Ereignisdaten, die die Bedingungen beschreiben, die zu dem Ereignis geführt haben.</param>
void NavigationHelper::CoreDispatcher_AcceleratorKeyActivated(CoreDispatcher^ sender,
	AcceleratorKeyEventArgs^ e)
{
	sender; // Nicht verwendeter Parameter
	auto virtualKey = e->VirtualKey;

	// Weitere Untersuchungen nur durchführen, wenn die Taste "Nach links", "Nach rechts" oder die dezidierten Tasten "Zurück" oder "Weiter"
	// gedrückt werden
	if ((e->EventType == CoreAcceleratorKeyEventType::SystemKeyDown ||
		e->EventType == CoreAcceleratorKeyEventType::KeyDown) &&
		(virtualKey == VirtualKey::Left || virtualKey == VirtualKey::Right ||
		virtualKey == VirtualKey::GoBack || virtualKey == VirtualKey::GoForward))
	{
		auto coreWindow = Window::Current->CoreWindow;
		auto downState = Windows::UI::Core::CoreVirtualKeyStates::Down;
		bool menuKey = (coreWindow->GetKeyState(VirtualKey::Menu) & downState) == downState;
		bool controlKey = (coreWindow->GetKeyState(VirtualKey::Control) & downState) == downState;
		bool shiftKey = (coreWindow->GetKeyState(VirtualKey::Shift) & downState) == downState;
		bool noModifiers = !menuKey && !controlKey && !shiftKey;
		bool onlyAlt = menuKey && !controlKey && !shiftKey;

		if ((virtualKey == VirtualKey::GoBack && noModifiers) ||
			(virtualKey == VirtualKey::Left && onlyAlt))
		{
			// Wenn die Taste "Zurück" oder ALT+NACH-LINKS-TASTE gedrückt wird, zurück navigieren
			e->Handled = true;
			GoBackCommand->Execute(this);
		}
		else if ((virtualKey == VirtualKey::GoForward && noModifiers) ||
			(virtualKey == VirtualKey::Right && onlyAlt))
		{
			// Wenn die Taste "Weiter" oder ALT+NACH-RECHTS-TASTE gedrückt wird, vorwärts navigieren
			e->Handled = true;
			GoForwardCommand->Execute(this);
		}
	}
}

/// <summary>
/// Wird bei jedem Mausklick, jeder Touchscreenberührung oder einer äquivalenten Interaktion aufgerufen, wenn diese
/// Seite aktiv ist und das gesamte Fenster ausfüllt.  Wird zum Erkennen von "Weiter"- und "Zurück"-Maustastenklicks
/// im Browserstil verwendet, um zwischen Seiten zu navigieren.
/// </summary>
/// <param name="sender">Instanz, von der das Ereignis ausgelöst wurde.</param>
/// <param name="e">Ereignisdaten, die die Bedingungen beschreiben, die zu dem Ereignis geführt haben.</param>
void NavigationHelper::CoreWindow_PointerPressed(CoreWindow^ sender, PointerEventArgs^ e)
{
	auto properties = e->CurrentPoint->Properties;

	// Tastenkombinationen mit der linken, rechten und mittleren Taste ignorieren
	if (properties->IsLeftButtonPressed ||
		properties->IsRightButtonPressed ||
		properties->IsMiddleButtonPressed)
	{
		return;
	}

	// Wenn "Zurück" oder "Vorwärts" gedrückt wird (jedoch nicht gleichzeitig), entsprechend navigieren
	bool backPressed = properties->IsXButton1Pressed;
	bool forwardPressed = properties->IsXButton2Pressed;
	if (backPressed ^ forwardPressed)
	{
		e->Handled = true;
		if (backPressed)
		{
			if (GoBackCommand->CanExecute(this))
			{
				GoBackCommand->Execute(this);
			}
		}
		else
		{
			if (GoForwardCommand->CanExecute(this))
			{
				GoForwardCommand->Execute(this);
			}
		}
	}
}
#endif

#pragma endregion

#pragma region Process lifetime management

/// <summary>
/// Wird aufgerufen, wenn diese Seite in einem Rahmen angezeigt werden soll.
/// </summary>
/// <param name="e">Ereignisdaten, die beschreiben, wie diese Seite erreicht wurde.  Die
/// Parametereigenschaft stellt die anzuzeigende Gruppe bereit.</param>
void NavigationHelper::OnNavigatedTo(NavigationEventArgs^ e)
{
	Page ^page = _page.Resolve<Page>();
	if (page != nullptr)
	{
		auto frameState = SuspensionManager::SessionStateForFrame(page->Frame);
		_pageKey = "Page-" + page->Frame->BackStackDepth;

		if (e->NavigationMode == NavigationMode::New)
		{
			// Bestehenden Zustand für die Vorwärtsnavigation löschen, wenn dem Navigationsstapel eine neue
			// Seite hinzugefügt wird
			auto nextPageKey = _pageKey;
			int nextPageIndex = page->Frame->BackStackDepth;
			while (frameState->HasKey(nextPageKey))
			{
				frameState->Remove(nextPageKey);
				nextPageIndex++;
				nextPageKey = "Page-" + nextPageIndex;
			}

			// Den Navigationsparameter an die neue Seite übergeben
			LoadState(this, ref new LoadStateEventArgs(e->Parameter, nullptr));
		}
		else
		{
			// Den Navigationsparameter und den beibehaltenen Seitenzustand an die Seite übergeben,
			// dabei die gleiche Strategie verwenden wie zum Laden des angehaltenen Zustands und zum erneuten Erstellen von im Cache verworfenen
			// Seiten
			LoadState(this, ref new LoadStateEventArgs(e->Parameter, safe_cast<IMap<String^, Object^>^>(frameState->Lookup(_pageKey))));
		}
	}
}

/// <summary>
/// Wird aufgerufen, wenn diese Seite nicht mehr in einem Rahmen angezeigt wird.
/// </summary>
/// <param name="e">Ereignisdaten, die beschreiben, wie diese Seite erreicht wurde.  Die
/// Parametereigenschaft stellt die anzuzeigende Gruppe bereit.</param>
void NavigationHelper::OnNavigatedFrom(NavigationEventArgs^ e)
{
	Page ^page = _page.Resolve<Page>();
	if (page != nullptr)
	{
		auto frameState = SuspensionManager::SessionStateForFrame(page->Frame);
		auto pageState = ref new Map<String^, Object^>();
		SaveState(this, ref new SaveStateEventArgs(pageState));
		frameState->Insert(_pageKey, pageState);
	}
}
#pragma endregion