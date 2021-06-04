//
// Einstellungen.xaml.h
// Deklaration der Einstellungen-Klasse
//

#pragma once

#include "Einstellungen.g.h"
#include "Common\NavigationHelper.h"

namespace Yatzy
{
	/// <summary>
	/// Eine Standardseite mit Eigenschaften, die die meisten Anwendungen aufweisen.
	/// </summary>
	[Windows::Foundation::Metadata::WebHostHidden]
	public ref class Einstellungen sealed
	{
	public:
		Einstellungen();

		/// <summary>
		/// Ruft das Anzeigemodell für diese <see cref="Page"/> ab. 
		/// Dies kann in ein stark typisiertes Anzeigemodell geändert werden.
		/// </summary>
		property Windows::Foundation::Collections::IObservableMap<Platform::String^, Platform::Object^>^ DefaultViewModel
		{
			Windows::Foundation::Collections::IObservableMap<Platform::String^, Platform::Object^>^  get();
		}

		/// <summary>
		/// Ruft den <see cref="NavigationHelper"/> ab, der mit dieser <see cref="Page"/> verknüpft ist.
		/// </summary>
		property Common::NavigationHelper^ NavigationHelper
		{
			Common::NavigationHelper^ get();
		}

	protected:
		virtual void OnNavigatedTo(Windows::UI::Xaml::Navigation::NavigationEventArgs^ e) override;
		virtual void OnNavigatedFrom(Windows::UI::Xaml::Navigation::NavigationEventArgs^ e) override;

	private:
		void LoadState(Platform::Object^ sender, Common::LoadStateEventArgs^ e);
		void SaveState(Platform::Object^ sender, Common::SaveStateEventArgs^ e);

		static Windows::UI::Xaml::DependencyProperty^ _defaultViewModelProperty;
		static Windows::UI::Xaml::DependencyProperty^ _navigationHelperProperty;
		void ButtonOK_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void buttonReset_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void TextBoxName_GotFocus(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
	};

}
