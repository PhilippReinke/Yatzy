

//------------------------------------------------------------------------------
//     This code was generated by a tool.
//
//     Changes to this file may cause incorrect behavior and will be lost if
//     the code is regenerated.
//------------------------------------------------------------------------------
#include "pch.h"
#include "Score.xaml.h"




void ::Yatzy::Score::InitializeComponent()
{
    if (_contentLoaded)
        return;

    _contentLoaded = true;

    // Call LoadComponent on ms-appx:///Score.xaml
    ::Windows::UI::Xaml::Application::LoadComponent(this, ref new ::Windows::Foundation::Uri(L"ms-appx:///Score.xaml"), ::Windows::UI::Xaml::Controls::Primitives::ComponentResourceLocation::Application);

    // Get the Grid named 'LayoutRoot'
    LayoutRoot = safe_cast<::Windows::UI::Xaml::Controls::Grid^>(static_cast<Windows::UI::Xaml::IFrameworkElement^>(this)->FindName(L"LayoutRoot"));
    // Get the ListView named 'ausgabeInfo_Pkt'
    ausgabeInfo_Pkt = safe_cast<::Windows::UI::Xaml::Controls::ListView^>(static_cast<Windows::UI::Xaml::IFrameworkElement^>(this)->FindName(L"ausgabeInfo_Pkt"));
    // Get the ListView named 'ausgabeInfo_Text'
    ausgabeInfo_Text = safe_cast<::Windows::UI::Xaml::Controls::ListView^>(static_cast<Windows::UI::Xaml::IFrameworkElement^>(this)->FindName(L"ausgabeInfo_Text"));
    // Get the StackPanel named 'stackPlatz'
    stackPlatz = safe_cast<::Windows::UI::Xaml::Controls::StackPanel^>(static_cast<Windows::UI::Xaml::IFrameworkElement^>(this)->FindName(L"stackPlatz"));
    // Get the ListView named 'ausgabePunkte'
    ausgabePunkte = safe_cast<::Windows::UI::Xaml::Controls::ListView^>(static_cast<Windows::UI::Xaml::IFrameworkElement^>(this)->FindName(L"ausgabePunkte"));
    // Get the ListView named 'ausgabeName'
    ausgabeName = safe_cast<::Windows::UI::Xaml::Controls::ListView^>(static_cast<Windows::UI::Xaml::IFrameworkElement^>(this)->FindName(L"ausgabeName"));
    // Get the ListView named 'ausgabePlatz'
    ausgabePlatz = safe_cast<::Windows::UI::Xaml::Controls::ListView^>(static_cast<Windows::UI::Xaml::IFrameworkElement^>(this)->FindName(L"ausgabePlatz"));
    // Get the TextBlock named 'textÜberschrift'
    textÜberschrift = safe_cast<::Windows::UI::Xaml::Controls::TextBlock^>(static_cast<Windows::UI::Xaml::IFrameworkElement^>(this)->FindName(L"textÜberschrift"));
    // Get the Rectangle named 'rectÜberschrift'
    rectÜberschrift = safe_cast<::Windows::UI::Xaml::Shapes::Rectangle^>(static_cast<Windows::UI::Xaml::IFrameworkElement^>(this)->FindName(L"rectÜberschrift"));
}

void ::Yatzy::Score::Connect(int connectionId, Platform::Object^ target)
{
    (void)connectionId; // Unused parameter
    (void)target; // Unused parameter
    _contentLoaded = true;
}

