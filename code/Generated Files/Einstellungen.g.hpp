

//------------------------------------------------------------------------------
//     This code was generated by a tool.
//
//     Changes to this file may cause incorrect behavior and will be lost if
//     the code is regenerated.
//------------------------------------------------------------------------------
#include "pch.h"
#include "Einstellungen.xaml.h"




void ::Yatzy::Einstellungen::InitializeComponent()
{
    if (_contentLoaded)
        return;

    _contentLoaded = true;

    // Call LoadComponent on ms-appx:///Einstellungen.xaml
    ::Windows::UI::Xaml::Application::LoadComponent(this, ref new ::Windows::Foundation::Uri(L"ms-appx:///Einstellungen.xaml"), ::Windows::UI::Xaml::Controls::Primitives::ComponentResourceLocation::Application);

    // Get the Grid named 'LayoutRoot'
    LayoutRoot = safe_cast<::Windows::UI::Xaml::Controls::Grid^>(static_cast<Windows::UI::Xaml::IFrameworkElement^>(this)->FindName(L"LayoutRoot"));
    // Get the Button named 'buttonReset'
    buttonReset = safe_cast<::Windows::UI::Xaml::Controls::Button^>(static_cast<Windows::UI::Xaml::IFrameworkElement^>(this)->FindName(L"buttonReset"));
    // Get the Button named 'buttonOK'
    buttonOK = safe_cast<::Windows::UI::Xaml::Controls::Button^>(static_cast<Windows::UI::Xaml::IFrameworkElement^>(this)->FindName(L"buttonOK"));
    // Get the Grid named 'gridName'
    gridName = safe_cast<::Windows::UI::Xaml::Controls::Grid^>(static_cast<Windows::UI::Xaml::IFrameworkElement^>(this)->FindName(L"gridName"));
    // Get the Grid named 'gridVorschau'
    gridVorschau = safe_cast<::Windows::UI::Xaml::Controls::Grid^>(static_cast<Windows::UI::Xaml::IFrameworkElement^>(this)->FindName(L"gridVorschau"));
    // Get the Grid named 'gridWürfel'
    gridWürfel = safe_cast<::Windows::UI::Xaml::Controls::Grid^>(static_cast<Windows::UI::Xaml::IFrameworkElement^>(this)->FindName(L"gridWürfel"));
    // Get the Grid named 'gridHintergrund'
    gridHintergrund = safe_cast<::Windows::UI::Xaml::Controls::Grid^>(static_cast<Windows::UI::Xaml::IFrameworkElement^>(this)->FindName(L"gridHintergrund"));
    // Get the TextBlock named 'textHintergrund'
    textHintergrund = safe_cast<::Windows::UI::Xaml::Controls::TextBlock^>(static_cast<Windows::UI::Xaml::IFrameworkElement^>(this)->FindName(L"textHintergrund"));
    // Get the ComboBox named 'ComboBoxFarbeBackground'
    ComboBoxFarbeBackground = safe_cast<::Windows::UI::Xaml::Controls::ComboBox^>(static_cast<Windows::UI::Xaml::IFrameworkElement^>(this)->FindName(L"ComboBoxFarbeBackground"));
    // Get the TextBlock named 'textWürfel'
    textWürfel = safe_cast<::Windows::UI::Xaml::Controls::TextBlock^>(static_cast<Windows::UI::Xaml::IFrameworkElement^>(this)->FindName(L"textWürfel"));
    // Get the ComboBox named 'ComboBoxWürfel'
    ComboBoxWürfel = safe_cast<::Windows::UI::Xaml::Controls::ComboBox^>(static_cast<Windows::UI::Xaml::IFrameworkElement^>(this)->FindName(L"ComboBoxWürfel"));
    // Get the TextBlock named 'textVorschau'
    textVorschau = safe_cast<::Windows::UI::Xaml::Controls::TextBlock^>(static_cast<Windows::UI::Xaml::IFrameworkElement^>(this)->FindName(L"textVorschau"));
    // Get the ToggleSwitch named 'ToggleVorschau'
    ToggleVorschau = safe_cast<::Windows::UI::Xaml::Controls::ToggleSwitch^>(static_cast<Windows::UI::Xaml::IFrameworkElement^>(this)->FindName(L"ToggleVorschau"));
    // Get the TextBlock named 'textName'
    textName = safe_cast<::Windows::UI::Xaml::Controls::TextBlock^>(static_cast<Windows::UI::Xaml::IFrameworkElement^>(this)->FindName(L"textName"));
    // Get the TextBox named 'TextBoxName'
    TextBoxName = safe_cast<::Windows::UI::Xaml::Controls::TextBox^>(static_cast<Windows::UI::Xaml::IFrameworkElement^>(this)->FindName(L"TextBoxName"));
    // Get the TextBlock named 'textÜberschrift'
    textÜberschrift = safe_cast<::Windows::UI::Xaml::Controls::TextBlock^>(static_cast<Windows::UI::Xaml::IFrameworkElement^>(this)->FindName(L"textÜberschrift"));
    // Get the Rectangle named 'rectÜberschrift'
    rectÜberschrift = safe_cast<::Windows::UI::Xaml::Shapes::Rectangle^>(static_cast<Windows::UI::Xaml::IFrameworkElement^>(this)->FindName(L"rectÜberschrift"));
}

void ::Yatzy::Einstellungen::Connect(int connectionId, Platform::Object^ target)
{
    switch (connectionId)
    {
    case 1:
        (safe_cast<::Windows::UI::Xaml::Controls::Primitives::ButtonBase^>(target))->Click +=
            ref new ::Windows::UI::Xaml::RoutedEventHandler(this, (void (::Yatzy::Einstellungen::*)(Platform::Object^, Windows::UI::Xaml::RoutedEventArgs^))&Einstellungen::buttonReset_Click);
        break;
    case 2:
        (safe_cast<::Windows::UI::Xaml::Controls::Primitives::ButtonBase^>(target))->Click +=
            ref new ::Windows::UI::Xaml::RoutedEventHandler(this, (void (::Yatzy::Einstellungen::*)(Platform::Object^, Windows::UI::Xaml::RoutedEventArgs^))&Einstellungen::ButtonOK_Click);
        break;
    case 3:
        (safe_cast<::Windows::UI::Xaml::UIElement^>(target))->GotFocus +=
            ref new ::Windows::UI::Xaml::RoutedEventHandler(this, (void (::Yatzy::Einstellungen::*)(Platform::Object^, Windows::UI::Xaml::RoutedEventArgs^))&Einstellungen::TextBoxName_GotFocus);
        break;
    }
    (void)connectionId; // Unused parameter
    (void)target; // Unused parameter
    _contentLoaded = true;
}

