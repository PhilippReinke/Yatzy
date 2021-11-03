//
// Hilfe.xaml.cpp
// Implementierung der Hilfe-Klasse
//

#include "pch.h"
#include "Hilfe.xaml.h"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <istream>

using namespace Yatzy;

using namespace Platform;
using namespace Platform::Collections;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::Graphics::Display;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Interop;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Navigation;

// Die Elementvorlage "Standardseite" ist unter "http://go.microsoft.com/fwlink/?LinkID=390556" dokumentiert.

Hilfe::Hilfe()
{
	InitializeComponent();
	SetValue(_defaultViewModelProperty, ref new Platform::Collections::Map<String^, Object^>(std::less<String^>()));
	auto navigationHelper = ref new Common::NavigationHelper(this);
	SetValue(_navigationHelperProperty, navigationHelper);
	navigationHelper->LoadState += ref new Common::LoadStateEventHandler(this, &Hilfe::LoadState);
	navigationHelper->SaveState += ref new Common::SaveStateEventHandler(this, &Hilfe::SaveState);
}

DependencyProperty^ Hilfe::_defaultViewModelProperty =
DependencyProperty::Register("DefaultViewModel",
TypeName(IObservableMap<String^, Object^>::typeid), TypeName(Hilfe::typeid), nullptr);


IObservableMap<String^, Object^>^ Hilfe::DefaultViewModel::get()
{
	return safe_cast<IObservableMap<String^, Object^>^>(GetValue(_defaultViewModelProperty));
}

DependencyProperty^ Hilfe::_navigationHelperProperty =
DependencyProperty::Register("NavigationHelper",
TypeName(Common::NavigationHelper::typeid), TypeName(Hilfe::typeid), nullptr);

Common::NavigationHelper^ Hilfe::NavigationHelper::get()
{
	return safe_cast<Common::NavigationHelper^>(GetValue(_navigationHelperProperty));
}

#pragma region Navigation support


void Hilfe::OnNavigatedTo(NavigationEventArgs^ e)
{
	NavigationHelper->OnNavigatedTo(e);

	// Skalierungsfaktor berechnen
	double dScaleFactor = Window::Current->Bounds.Width / 400;

	// Überschrift anpassen
	textÜberschrift->FontSize = static_cast<int>(dScaleFactor * 24);
	rectÜberschrift->Height = static_cast<int>(dScaleFactor * 3);

	// Anleitung hinzufügen
	String^ textÜberschrift, ^textAnleitung;
	textÜberschrift = "Anleitung";
	textAnleitung = "Yatzuu ist ein rundenbasiertes Würfelspiel, dessen Ziel die Erfüllung bestimmter ";
	textAnleitung += "Würfelkombinationen ist. Dabei stehen Ihnen pro Runde drei Würfe mit einer beliebigen Anzahl von Würfeln zur ";
	textAnleitung += "Verfügung, um die maximale Punktzahl einer bestimmten Kombination zu erreichen. Jede Runde findet ihren Abschluss ";
	textAnleitung += "in der Speicherung der erreichten Punktzahl, wobei eine Runde auch vor dem dritten Wurf beendet werden kann. ";
	textAnleitung += "Wählen Sie dafür das Feld neben der gewünschten Kombination aus und bestätigen Sie Ihre Wahl mit „Neue Runde “. ";
	textAnleitung += "Die Fixierung eines Würfels erfolgt durch die Berührung mit einem Finger und kann durch erneute Berührung gelöst ";
	textAnleitung += "werden. Das Ende des Spiels ist mit der Vervollständigung aller Felder erreicht und ermöglich die Freischaltung ";
	textAnleitung += "neuer Hintergrundfarben und Würfelsätze.";
	// Text skalieren
	textBlockBewertung->FontSize = static_cast<int>(dScaleFactor * 16);
	textBlockAnleitung1->FontSize = static_cast<int>(dScaleFactor * 20);
	textBlockAnleitung2->FontSize = static_cast<int>(dScaleFactor * 16);
	// Text einfügen
	textBlockAnleitung1->Text = textÜberschrift;
	textBlockAnleitung2->Text = textAnleitung;

	// Würfelkombiantion / Punkte skalieren
	textBlockWürfelkombination1->FontSize = static_cast<int>(dScaleFactor * 20);
	listViewAusgabe->Width = static_cast<int>(dScaleFactor * 400);
	for (int i = 0; i <= 13; i++)
	{
		// Variable
		TextBlock^ tempTextBlock1, ^tempTextBlock2;

		switch (i)
		{
		case 0: 
			tempTextBlock1 = tabelleEiner1;
			tempTextBlock2 = tabelleEiner2;
			break;
		case 1:
			tempTextBlock1 = tabelleZweier1;
			tempTextBlock2 = tabelleZweier2;
			break;
		case 2:
			tempTextBlock1 = tabelleDreier1;
			tempTextBlock2 = tabelleDreier2;
			break;
		case 3:
			tempTextBlock1 = tabelleVierer1;
			tempTextBlock2 = tabelleVierer2;
			break;
		case 4:
			tempTextBlock1 = tabelleFünfer1;
			tempTextBlock2 = tabelleFünfer2;
			break;
		case 5:
			tempTextBlock1 = tabelleSechser1;
			tempTextBlock2 = tabelleSechser2;
			break;
		case 6:
			tempTextBlock1 = tabelleBonus1;
			tempTextBlock2 = tabelleBonus2;
			break;
		case 7:
			tempTextBlock1 = tabelle3erPasch1;
			tempTextBlock2 = tabelle3erPasch2;
			break;
		case 8:
			tempTextBlock1 = tabelle4erPasch1;
			tempTextBlock2 = tabelle4erPasch2;
			break;
		case 9:
			tempTextBlock1 = tabelleklStraße1;
			tempTextBlock2 = tabelleklStraße2;
			break;
		case 10:
			tempTextBlock1 = tabellegrStraße1;
			tempTextBlock2 = tabellegrStraße2;
			break;
		case 11:
			tempTextBlock1 = tabelleFullHouse1;
			tempTextBlock2 = tabelleFullHouse2;
			break;
		case 12:
			tempTextBlock1 = tabelleChance1;
			tempTextBlock2 = tabelleChance2;
			break;
		case 13:
			tempTextBlock1 = tabelleYatzy1;
			tempTextBlock2 = tabelleYatzy2;
			break;
		}
		tempTextBlock1->FontSize = static_cast<int>(dScaleFactor * 16);
		tempTextBlock2->FontSize = static_cast<int>(dScaleFactor * 16);
	}

	// Über Yatzy
	textÜberschrift = ref new String;
	textAnleitung = ref new String;
	textÜberschrift = "Über Yatzuu";
	textAnleitung = "Die Ihnen vorliegende Adaption des Spieles Yatzy ist von Philipp Reinke geplant und entwickelt worden. ";
	textAnleitung += "Sollten Sie Fragen, Anmerkungen oder Verbesserungsvorschläge haben, senden Sie diese bitte an ";
	textAnleitung += "die E-Mail-Adresse .... Ich bemühe mich um eine schnellstmögliche Bearbeitung Ihrer Anfrage ";
	textAnleitung += "und wünsche Ihnen viel Vergnügen beim Würfeln.";
	// Text skalieren
	textBlockInfo1->FontSize = static_cast<int>(dScaleFactor * 20);
	textBlockInfo2->FontSize = static_cast<int>(dScaleFactor * 16);
	// Text einfügen
	textBlockInfo1->Text = textÜberschrift;
	textBlockInfo2->Text = textAnleitung;

	// Pfad bestimmen und in std::string konvertieren
	String^ tempPfad = Windows::Storage::ApplicationData::Current->LocalFolder->Path;
	tempPfad += "\\data2.yatzy";
	std::string tempPfadConvert2(tempPfad->Begin(), tempPfad->End());

	// Hintergrund anpassen
	std::ifstream file2(tempPfadConvert2);
	std::string tempString;
	std::vector<std::string> tempVektor;

	// Fehlerüberprüfung
	if (!file2)
		return;

	// Einstellungen auslesen
	while (!file2.eof() && file2.good())
	{
		// Name
		getline(file2, tempString);
		if (!tempString.compare("")) tempString = "unknown";
		tempVektor.push_back(tempString);
	}

	// aufräumen
	file2.close();

	// Farbe
	int iTemp = atoi(tempVektor.at(3).c_str());

	switch (iTemp)
	{
	case 0: Hilfe::Background = ref new SolidColorBrush(Windows::UI::ColorHelper::FromArgb(255, 0, 0, 0)); break;			// schwarz
	case 1: Hilfe::Background = ref new SolidColorBrush(Windows::UI::ColorHelper::FromArgb(255, 5, 42, 78)); break;			// dunkelblau
	case 2: Hilfe::Background = ref new SolidColorBrush(Windows::UI::ColorHelper::FromArgb(255, 85, 136, 186)); break;		// hellblau
	case 3: Hilfe::Background = ref new SolidColorBrush(Windows::UI::ColorHelper::FromArgb(255, 78, 5, 5)); break;			// dunkelrot
	case 4: Hilfe::Background = ref new SolidColorBrush(Windows::UI::ColorHelper::FromArgb(255, 186, 85, 85)); break;		// hellrot
	case 5: Hilfe::Background = ref new SolidColorBrush(Windows::UI::ColorHelper::FromArgb(255, 5, 78, 27)); break;			// dunkelgrün
	case 6: Hilfe::Background = ref new SolidColorBrush(Windows::UI::ColorHelper::FromArgb(255, 101, 186, 85)); break;		// hellgrün
	case 7: Hilfe::Background = ref new SolidColorBrush(Windows::UI::ColorHelper::FromArgb(255, 255, 185, 1)); break;		// gelb
	case 8: Hilfe::Background = ref new SolidColorBrush(Windows::UI::ColorHelper::FromArgb(255, 124, 76, 35)); break;		// dunkelbraun
	case 9: Hilfe::Background = ref new SolidColorBrush(Windows::UI::ColorHelper::FromArgb(255, 192, 130, 76)); break;		// hellbraun
	case 10: Hilfe::Background = ref new SolidColorBrush(Windows::UI::ColorHelper::FromArgb(255, 95, 158, 160)); break;		// türkis
	case 11: Hilfe::Background = ref new SolidColorBrush(Windows::UI::ColorHelper::FromArgb(255, 43, 43, 43)); break;		// grau (dunkel)
	case 12: Hilfe::Background = ref new SolidColorBrush(Windows::UI::ColorHelper::FromArgb(255, 98, 98, 98)); break;		// grau (mittel)
	case 13: Hilfe::Background = ref new SolidColorBrush(Windows::UI::ColorHelper::FromArgb(255, 167, 167, 167)); break;	// grau (hell)
	case 14: Hilfe::Background = ref new SolidColorBrush(Windows::UI::ColorHelper::FromArgb(255, 167, 108, 154)); break;	// lila (hell)
	case 15: Hilfe::Background = ref new SolidColorBrush(Windows::UI::ColorHelper::FromArgb(255, 102, 64, 94)); break;		// lila (dunkel)
	case 16: Hilfe::Background = ref new SolidColorBrush(Windows::UI::ColorHelper::FromArgb(255, 255, 153, 0)); break;		// orange (hell)
	case 17: Hilfe::Background = ref new SolidColorBrush(Windows::UI::ColorHelper::FromArgb(255, 226, 111, 0)); break;		// orange (dunkel)
	case 18: Hilfe::Background = ref new SolidColorBrush(Windows::UI::ColorHelper::FromArgb(255, 224, 132, 187)); break;	// rosa
	}
}

void Hilfe::OnNavigatedFrom(NavigationEventArgs^ e)
{
	NavigationHelper->OnNavigatedFrom(e);
}

#pragma endregion


void Hilfe::LoadState(Object^ sender, Common::LoadStateEventArgs^ e)
{
	(void) sender;	// Nicht verwendeter Parameter
	(void) e;	// Nicht verwendeter Parameter
}


void Hilfe::SaveState(Object^ sender, Common::SaveStateEventArgs^ e){
	(void) sender;	// Nicht verwendeter Parameter
	(void) e; // Nicht verwendeter Parameter
}


void Yatzy::Hilfe::AppBarButton_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	Windows::System::Launcher^ launcher;
	auto async = launcher->LaunchUriAsync(ref new Uri("ms-windows-store://pdp/?productid=9PJX8QMKXM4X"));
	
	while (async->Status != Windows::Foundation::AsyncStatus::Completed)
	{
		switch (async->Status)
		{
		case Windows::Foundation::AsyncStatus::Error:
		case Windows::Foundation::AsyncStatus::Canceled:
			return;
		default:
			break;
		}
	}

	auto result = async->GetResults();
}
