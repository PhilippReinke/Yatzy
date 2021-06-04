//
// SuspensionManager.h
// Deklaration der SuspensionManager-Klasse
//

#pragma once

namespace Yatzy
{
	namespace Common
	{
		/// <summary>
		/// SuspensionManager erfasst den globalen Sitzungszustand, um die Verwaltung der Prozesslebensdauer
		/// für eine Anwendung zu vereinfachen.  Beachten, dass der Sitzungszustand bei einer Vielzahl von Bedingungen
		/// automatisch gelöscht wird und niemals zum Speichern von Informationen verwendet werden sollte, die zwischen Sitzungen zwar bequem übertragen werden können,
		/// jedoch beim Absturz der Anwendung gelöscht werden sollen oder
		/// aktualisiert werden.
		/// </summary>
		class SuspensionManager sealed
		{
		public:
			static void RegisterFrame(Windows::UI::Xaml::Controls::Frame^ frame, Platform::String^ sessionStateKey, Platform::String^ sessionBaseKey = nullptr);
			static void UnregisterFrame(Windows::UI::Xaml::Controls::Frame^ frame);
			static concurrency::task<void> SaveAsync();
			static concurrency::task<void> RestoreAsync(Platform::String^ sessionBaseKey = nullptr);
			static Windows::Foundation::Collections::IMap<Platform::String^, Platform::Object^>^ SessionState();
			static Windows::Foundation::Collections::IMap<Platform::String^, Platform::Object^>^ SessionStateForFrame(
				Windows::UI::Xaml::Controls::Frame^ frame);

		private:
			static void RestoreFrameNavigationState(Windows::UI::Xaml::Controls::Frame^ frame);
			static void SaveFrameNavigationState(Windows::UI::Xaml::Controls::Frame^ frame);

			static Platform::Collections::Map<Platform::String^, Platform::Object^>^ _sessionState;
			static const wchar_t* sessionStateFilename;

			static std::vector<Platform::WeakReference> _registeredFrames;
			static Windows::UI::Xaml::DependencyProperty^ FrameSessionStateKeyProperty;
			static Windows::UI::Xaml::DependencyProperty^ FrameSessionBaseKeyProperty;
			static Windows::UI::Xaml::DependencyProperty^ FrameSessionStateProperty;
		};
	}
}
