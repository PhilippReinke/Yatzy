

//------------------------------------------------------------------------------
//     This code was generated by a tool.
//
//     Changes to this file may cause incorrect behavior and will be lost if
//     the code is regenerated.
//------------------------------------------------------------------------------
#include "pch.h"
#include "Hilfe.xaml.h"




void ::Yatzy::Hilfe::InitializeComponent()
{
    if (_contentLoaded)
        return;

    _contentLoaded = true;

    // Call LoadComponent on ms-appx:///Hilfe.xaml
    ::Windows::UI::Xaml::Application::LoadComponent(this, ref new ::Windows::Foundation::Uri(L"ms-appx:///Hilfe.xaml"), ::Windows::UI::Xaml::Controls::Primitives::ComponentResourceLocation::Application);

    // Get the Grid named 'LayoutRoot'
    LayoutRoot = safe_cast<::Windows::UI::Xaml::Controls::Grid^>(static_cast<Windows::UI::Xaml::IFrameworkElement^>(this)->FindName(L"LayoutRoot"));
    // Get the ListView named 'listText'
    listText = safe_cast<::Windows::UI::Xaml::Controls::ListView^>(static_cast<Windows::UI::Xaml::IFrameworkElement^>(this)->FindName(L"listText"));
    // Get the ListViewItem named 'listViewAusgabe'
    listViewAusgabe = safe_cast<::Windows::UI::Xaml::Controls::ListViewItem^>(static_cast<Windows::UI::Xaml::IFrameworkElement^>(this)->FindName(L"listViewAusgabe"));
    // Get the TextBlock named 'textBlockBewertung'
    textBlockBewertung = safe_cast<::Windows::UI::Xaml::Controls::TextBlock^>(static_cast<Windows::UI::Xaml::IFrameworkElement^>(this)->FindName(L"textBlockBewertung"));
    // Get the TextBlock named 'textBlockAnleitung1'
    textBlockAnleitung1 = safe_cast<::Windows::UI::Xaml::Controls::TextBlock^>(static_cast<Windows::UI::Xaml::IFrameworkElement^>(this)->FindName(L"textBlockAnleitung1"));
    // Get the TextBlock named 'textBlockAnleitung2'
    textBlockAnleitung2 = safe_cast<::Windows::UI::Xaml::Controls::TextBlock^>(static_cast<Windows::UI::Xaml::IFrameworkElement^>(this)->FindName(L"textBlockAnleitung2"));
    // Get the TextBlock named 'textBlockWürfelkombination1'
    textBlockWürfelkombination1 = safe_cast<::Windows::UI::Xaml::Controls::TextBlock^>(static_cast<Windows::UI::Xaml::IFrameworkElement^>(this)->FindName(L"textBlockWürfelkombination1"));
    // Get the TextBlock named 'textBlockInfo1'
    textBlockInfo1 = safe_cast<::Windows::UI::Xaml::Controls::TextBlock^>(static_cast<Windows::UI::Xaml::IFrameworkElement^>(this)->FindName(L"textBlockInfo1"));
    // Get the TextBlock named 'textBlockInfo2'
    textBlockInfo2 = safe_cast<::Windows::UI::Xaml::Controls::TextBlock^>(static_cast<Windows::UI::Xaml::IFrameworkElement^>(this)->FindName(L"textBlockInfo2"));
    // Get the TextBlock named 'tabelleEiner1'
    tabelleEiner1 = safe_cast<::Windows::UI::Xaml::Controls::TextBlock^>(static_cast<Windows::UI::Xaml::IFrameworkElement^>(this)->FindName(L"tabelleEiner1"));
    // Get the TextBlock named 'tabelleEiner2'
    tabelleEiner2 = safe_cast<::Windows::UI::Xaml::Controls::TextBlock^>(static_cast<Windows::UI::Xaml::IFrameworkElement^>(this)->FindName(L"tabelleEiner2"));
    // Get the TextBlock named 'tabelleZweier1'
    tabelleZweier1 = safe_cast<::Windows::UI::Xaml::Controls::TextBlock^>(static_cast<Windows::UI::Xaml::IFrameworkElement^>(this)->FindName(L"tabelleZweier1"));
    // Get the TextBlock named 'tabelleZweier2'
    tabelleZweier2 = safe_cast<::Windows::UI::Xaml::Controls::TextBlock^>(static_cast<Windows::UI::Xaml::IFrameworkElement^>(this)->FindName(L"tabelleZweier2"));
    // Get the TextBlock named 'tabelleDreier1'
    tabelleDreier1 = safe_cast<::Windows::UI::Xaml::Controls::TextBlock^>(static_cast<Windows::UI::Xaml::IFrameworkElement^>(this)->FindName(L"tabelleDreier1"));
    // Get the TextBlock named 'tabelleDreier2'
    tabelleDreier2 = safe_cast<::Windows::UI::Xaml::Controls::TextBlock^>(static_cast<Windows::UI::Xaml::IFrameworkElement^>(this)->FindName(L"tabelleDreier2"));
    // Get the TextBlock named 'tabelleVierer1'
    tabelleVierer1 = safe_cast<::Windows::UI::Xaml::Controls::TextBlock^>(static_cast<Windows::UI::Xaml::IFrameworkElement^>(this)->FindName(L"tabelleVierer1"));
    // Get the TextBlock named 'tabelleVierer2'
    tabelleVierer2 = safe_cast<::Windows::UI::Xaml::Controls::TextBlock^>(static_cast<Windows::UI::Xaml::IFrameworkElement^>(this)->FindName(L"tabelleVierer2"));
    // Get the TextBlock named 'tabelleFünfer1'
    tabelleFünfer1 = safe_cast<::Windows::UI::Xaml::Controls::TextBlock^>(static_cast<Windows::UI::Xaml::IFrameworkElement^>(this)->FindName(L"tabelleFünfer1"));
    // Get the TextBlock named 'tabelleFünfer2'
    tabelleFünfer2 = safe_cast<::Windows::UI::Xaml::Controls::TextBlock^>(static_cast<Windows::UI::Xaml::IFrameworkElement^>(this)->FindName(L"tabelleFünfer2"));
    // Get the TextBlock named 'tabelleSechser1'
    tabelleSechser1 = safe_cast<::Windows::UI::Xaml::Controls::TextBlock^>(static_cast<Windows::UI::Xaml::IFrameworkElement^>(this)->FindName(L"tabelleSechser1"));
    // Get the TextBlock named 'tabelleSechser2'
    tabelleSechser2 = safe_cast<::Windows::UI::Xaml::Controls::TextBlock^>(static_cast<Windows::UI::Xaml::IFrameworkElement^>(this)->FindName(L"tabelleSechser2"));
    // Get the TextBlock named 'tabelleBonus1'
    tabelleBonus1 = safe_cast<::Windows::UI::Xaml::Controls::TextBlock^>(static_cast<Windows::UI::Xaml::IFrameworkElement^>(this)->FindName(L"tabelleBonus1"));
    // Get the TextBlock named 'tabelleBonus2'
    tabelleBonus2 = safe_cast<::Windows::UI::Xaml::Controls::TextBlock^>(static_cast<Windows::UI::Xaml::IFrameworkElement^>(this)->FindName(L"tabelleBonus2"));
    // Get the TextBlock named 'tabelle3erPasch1'
    tabelle3erPasch1 = safe_cast<::Windows::UI::Xaml::Controls::TextBlock^>(static_cast<Windows::UI::Xaml::IFrameworkElement^>(this)->FindName(L"tabelle3erPasch1"));
    // Get the TextBlock named 'tabelle3erPasch2'
    tabelle3erPasch2 = safe_cast<::Windows::UI::Xaml::Controls::TextBlock^>(static_cast<Windows::UI::Xaml::IFrameworkElement^>(this)->FindName(L"tabelle3erPasch2"));
    // Get the TextBlock named 'tabelle4erPasch1'
    tabelle4erPasch1 = safe_cast<::Windows::UI::Xaml::Controls::TextBlock^>(static_cast<Windows::UI::Xaml::IFrameworkElement^>(this)->FindName(L"tabelle4erPasch1"));
    // Get the TextBlock named 'tabelle4erPasch2'
    tabelle4erPasch2 = safe_cast<::Windows::UI::Xaml::Controls::TextBlock^>(static_cast<Windows::UI::Xaml::IFrameworkElement^>(this)->FindName(L"tabelle4erPasch2"));
    // Get the TextBlock named 'tabelleklStraße1'
    tabelleklStraße1 = safe_cast<::Windows::UI::Xaml::Controls::TextBlock^>(static_cast<Windows::UI::Xaml::IFrameworkElement^>(this)->FindName(L"tabelleklStraße1"));
    // Get the TextBlock named 'tabelleklStraße2'
    tabelleklStraße2 = safe_cast<::Windows::UI::Xaml::Controls::TextBlock^>(static_cast<Windows::UI::Xaml::IFrameworkElement^>(this)->FindName(L"tabelleklStraße2"));
    // Get the TextBlock named 'tabellegrStraße1'
    tabellegrStraße1 = safe_cast<::Windows::UI::Xaml::Controls::TextBlock^>(static_cast<Windows::UI::Xaml::IFrameworkElement^>(this)->FindName(L"tabellegrStraße1"));
    // Get the TextBlock named 'tabellegrStraße2'
    tabellegrStraße2 = safe_cast<::Windows::UI::Xaml::Controls::TextBlock^>(static_cast<Windows::UI::Xaml::IFrameworkElement^>(this)->FindName(L"tabellegrStraße2"));
    // Get the TextBlock named 'tabelleFullHouse1'
    tabelleFullHouse1 = safe_cast<::Windows::UI::Xaml::Controls::TextBlock^>(static_cast<Windows::UI::Xaml::IFrameworkElement^>(this)->FindName(L"tabelleFullHouse1"));
    // Get the TextBlock named 'tabelleFullHouse2'
    tabelleFullHouse2 = safe_cast<::Windows::UI::Xaml::Controls::TextBlock^>(static_cast<Windows::UI::Xaml::IFrameworkElement^>(this)->FindName(L"tabelleFullHouse2"));
    // Get the TextBlock named 'tabelleChance1'
    tabelleChance1 = safe_cast<::Windows::UI::Xaml::Controls::TextBlock^>(static_cast<Windows::UI::Xaml::IFrameworkElement^>(this)->FindName(L"tabelleChance1"));
    // Get the TextBlock named 'tabelleChance2'
    tabelleChance2 = safe_cast<::Windows::UI::Xaml::Controls::TextBlock^>(static_cast<Windows::UI::Xaml::IFrameworkElement^>(this)->FindName(L"tabelleChance2"));
    // Get the TextBlock named 'tabelleYatzy1'
    tabelleYatzy1 = safe_cast<::Windows::UI::Xaml::Controls::TextBlock^>(static_cast<Windows::UI::Xaml::IFrameworkElement^>(this)->FindName(L"tabelleYatzy1"));
    // Get the TextBlock named 'tabelleYatzy2'
    tabelleYatzy2 = safe_cast<::Windows::UI::Xaml::Controls::TextBlock^>(static_cast<Windows::UI::Xaml::IFrameworkElement^>(this)->FindName(L"tabelleYatzy2"));
    // Get the TextBlock named 'textÜberschrift'
    textÜberschrift = safe_cast<::Windows::UI::Xaml::Controls::TextBlock^>(static_cast<Windows::UI::Xaml::IFrameworkElement^>(this)->FindName(L"textÜberschrift"));
    // Get the Rectangle named 'rectÜberschrift'
    rectÜberschrift = safe_cast<::Windows::UI::Xaml::Shapes::Rectangle^>(static_cast<Windows::UI::Xaml::IFrameworkElement^>(this)->FindName(L"rectÜberschrift"));
}

void ::Yatzy::Hilfe::Connect(int connectionId, Platform::Object^ target)
{
    switch (connectionId)
    {
    case 1:
        (safe_cast<::Windows::UI::Xaml::Controls::Primitives::ButtonBase^>(target))->Click +=
            ref new ::Windows::UI::Xaml::RoutedEventHandler(this, (void (::Yatzy::Hilfe::*)(Platform::Object^, Windows::UI::Xaml::RoutedEventArgs^))&Hilfe::AppBarButton_Click);
        break;
    }
    (void)connectionId; // Unused parameter
    (void)target; // Unused parameter
    _contentLoaded = true;
}

