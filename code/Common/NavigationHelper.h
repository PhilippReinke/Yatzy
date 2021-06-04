//
// NavigationHelper.h
// Deklaration der NavigationHelper-Klasse und verknüpfter Klassen
//

#pragma once

#include "RelayCommand.h"

namespace Yatzy
{
	namespace Common
	{
		/// <summary>
		/// Klasse, die zum Speichern der erforderlichen Ereignisdaten verwendet wird, wenn eine Seite versucht, den Zustand zu laden.
		/// </summary>
		public ref class LoadStateEventArgs sealed
		{
		public:

			/// <summary>
			/// Der an <see cref="Frame->Navigate(Type, Object)"/> übergebene Parameterwert 
			/// übergeben wurde, als diese Seite ursprünglich angefordert wurde.
			/// </summary>
			property Platform::Object^ NavigationParameter
			{
				Platform::Object^ get();
			}

			/// <summary>
			/// Ein Wörterbuch des Zustands, der von dieser Seite während einer früheren
			/// beibehalten wurde.  Beim ersten Aufrufen einer Seite ist dieser Wert NULL.
			/// </summary>
			property Windows::Foundation::Collections::IMap<Platform::String^, Platform::Object^>^ PageState
			{
				Windows::Foundation::Collections::IMap<Platform::String^, Platform::Object^>^ get();
			}

		internal:
			LoadStateEventArgs(Platform::Object^ navigationParameter, Windows::Foundation::Collections::IMap<Platform::String^, Platform::Object^>^ pageState);

		private:
			Platform::Object^ _navigationParameter;
			Windows::Foundation::Collections::IMap<Platform::String^, Platform::Object^>^ _pageState;
		};

		/// <summary>
		/// Repräsentiert die Methode, mit der das <see cref="NavigationHelper->LoadState"/>-Ereignis behandelt wird
		/// </summary>
		public delegate void LoadStateEventHandler(Platform::Object^ sender, LoadStateEventArgs^ e);

		/// <summary>
		/// Klasse, die zum Speichern der erforderlichen Ereignisdaten verwendet wird, wenn eine Seite versucht, den Zustand zu speichern.
		/// </summary>
		public ref class SaveStateEventArgs sealed
		{
		public:

			/// <summary>
			/// Ein leeres Wörterbuch, das mit dem serialisierbaren Zustand aufgefüllt wird.
			/// </summary>
			property Windows::Foundation::Collections::IMap<Platform::String^, Platform::Object^>^ PageState
			{
				Windows::Foundation::Collections::IMap<Platform::String^, Platform::Object^>^ get();
			}

		internal:
			SaveStateEventArgs(Windows::Foundation::Collections::IMap<Platform::String^, Platform::Object^>^ pageState);

		private:
			Windows::Foundation::Collections::IMap<Platform::String^, Platform::Object^>^ _pageState;
		};

		/// <summary>
		/// Repräsentiert die Methode, mit der das <see cref="NavigationHelper->SaveState"/>-Ereignis behandelt wird
		/// </summary>
		public delegate void SaveStateEventHandler(Platform::Object^ sender, SaveStateEventArgs^ e);

		/// <summary>
		/// NavigationHelper bietet Unterstützung bei der Navigation zwischen Seiten.  Es werden Befehle zum 
		/// rückwärts und vorwärts navigieren sowie Register für Standardmaus und -tastatur 
		/// Verknüpfungen, um in Windows nach vorne oder zurück zu wechseln sowie Hardwaretaste im
		/// Windows Phone.  Darüber hinaus wird SuspensionManger zur Verwaltung der Prozesslebensdauer
		/// und der Zustandsverwaltung beim Navigieren zwischen Seiten integriert.
		/// </summary>
		/// <example>
		/// Zur Verwendung von NavigationHelper diesen Schritten folgen, oder
		/// Starten Sie mit der Elementvorlage "Standardseite" oder einer beliebigen anderen Elementvorlage vom Typ "Seite" außer "Leere Seite".
		/// 
		/// 1) Eine Instanz von NavigationHelper erstellen an einem Ort wie 
		///		Konstruktor für die Seite und Registrierung eines Rückrufs für LoadState und 
		///		SaveState-Ereignisse.
		/// <code>
		///		MyPage::MyPage()
		///		{
		///			InitializeComponent();
		///			auto navigationHelper = ref new Common::NavigationHelper(this);
		///			navigationHelper->LoadState += ref new Common::LoadStateEventHandler(this, &MyPage::LoadState);
		///			navigationHelper->SaveState += ref new Common::SaveStateEventHandler(this, &MyPage::SaveState);
		///		}
		///		
		///		void MyPage::LoadState(Object^ sender, Common::LoadStateEventArgs^ e)
		///		{ }
		///		void MyPage::SaveState(Object^ sender, Common::SaveStateEventArgs^ e)
		///		{ }
		/// </code>
		/// 
		/// 2) Die Seite für den Aufruf an NavigationHelper registrieren, wenn die Seite 
		///		bei der Navigation, indem <see cref="Windows::UI::Xaml::Controls::Page::OnNavigatedTo"/> überschrieben wird 
		///		und <see cref="Windows::UI::Xaml::Controls::Page::OnNavigatedFrom"/>-Ereignisse.
		/// <code>
		///		void MyPage::OnNavigatedTo(NavigationEventArgs^ e)
		///		{
		///			NavigationHelper->OnNavigatedTo(e);
		///		}
		///
		///		void MyPage::OnNavigatedFrom(NavigationEventArgs^ e)
		///		{
		///			NavigationHelper->OnNavigatedFrom(e);
		///		}
		/// </code>
		/// </example>
		[Windows::Foundation::Metadata::WebHostHidden]
		[Windows::UI::Xaml::Data::Bindable]
		public ref class NavigationHelper sealed
		{
		public:
			/// <summary>
			/// <see cref="RelayCommand"/> zum Binden der Command-Eigenschaft der Schaltfläche "Zurück"
			/// zum Navigieren zum neuesten Element im Rückwärtsnavigationsverlauf, wenn ein Frame
			/// verwaltet einen eigenen Navigationsverlauf.
			/// 
			/// <see cref="RelayCommand"/> ist für die Verwendung der virtuellen Methode <see cref="GoBack"/> eingerichtet
			/// als Ausführungsaktion und <see cref="CanGoBack"/> für CanExecute.
			/// </summary>
			property RelayCommand^ GoBackCommand
			{
				RelayCommand^ get();
			}

			/// <summary>
			/// <see cref="RelayCommand"/> zum Navigieren zum letzten Element im 
			/// der Vorwärtsnavigationsverlauf, wenn ein Frame seinen eigenen Navigationsverlauf verwaltet.
			/// 
			/// <see cref="RelayCommand"/> ist für die Verwendung der virtuellen Methode <see cref="GoForward"/> eingerichtet
			/// als Ausführungsaktion und <see cref="CanGoForward"/> für CanExecute.
			/// </summary>
			property RelayCommand^ GoForwardCommand
			{
				RelayCommand^ get();
			}

		internal:
			NavigationHelper(Windows::UI::Xaml::Controls::Page^ page,
				RelayCommand^ goBack = nullptr,
				RelayCommand^ goForward = nullptr);

			bool CanGoBack();
			void GoBack();
			bool CanGoForward();
			void GoForward();

			void OnNavigatedTo(Windows::UI::Xaml::Navigation::NavigationEventArgs^ e);
			void OnNavigatedFrom(Windows::UI::Xaml::Navigation::NavigationEventArgs^ e);

			event LoadStateEventHandler^ LoadState;
			event SaveStateEventHandler^ SaveState;

		private:
			Platform::WeakReference _page;

			RelayCommand^ _goBackCommand;
			RelayCommand^ _goForwardCommand;

#if WINAPI_FAMILY==WINAPI_FAMILY_PHONE_APP
			Windows::Foundation::EventRegistrationToken _backPressedEventToken;

			void HardwareButton_BackPressed(Platform::Object^ sender,
				Windows::Phone::UI::Input::BackPressedEventArgs^ e);
#else
			bool _navigationShortcutsRegistered;
			Windows::Foundation::EventRegistrationToken _acceleratorKeyEventToken;
			Windows::Foundation::EventRegistrationToken _pointerPressedEventToken;

			void CoreDispatcher_AcceleratorKeyActivated(Windows::UI::Core::CoreDispatcher^ sender,
				Windows::UI::Core::AcceleratorKeyEventArgs^ e);
			void CoreWindow_PointerPressed(Windows::UI::Core::CoreWindow^ sender,
				Windows::UI::Core::PointerEventArgs^ e);
#endif

			Platform::String^ _pageKey;
			Windows::Foundation::EventRegistrationToken _loadedEventToken;
			Windows::Foundation::EventRegistrationToken _unloadedEventToken;
			void OnLoaded(Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
			void OnUnloaded(Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);

			~NavigationHelper();
		};
	}
}
