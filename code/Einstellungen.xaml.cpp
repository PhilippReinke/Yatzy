//
// Einstellungen.xaml.cpp
// Implementierung der Einstellungen-Klasse
//

#include "pch.h"
#include "Einstellungen.xaml.h"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

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
using namespace Windows::UI::Popups;

// Die Elementvorlage "Standardseite" ist unter "http://go.microsoft.com/fwlink/?LinkID=390556" dokumentiert.

Einstellungen::Einstellungen()
{
	InitializeComponent();
	SetValue(_defaultViewModelProperty, ref new Platform::Collections::Map<String^, Object^>(std::less<String^>()));
	auto navigationHelper = ref new Common::NavigationHelper(this);
	SetValue(_navigationHelperProperty, navigationHelper);
	navigationHelper->LoadState += ref new Common::LoadStateEventHandler(this, &Einstellungen::LoadState);
	navigationHelper->SaveState += ref new Common::SaveStateEventHandler(this, &Einstellungen::SaveState);
}

DependencyProperty^ Einstellungen::_defaultViewModelProperty =
DependencyProperty::Register("DefaultViewModel",
TypeName(IObservableMap<String^, Object^>::typeid), TypeName(Einstellungen::typeid), nullptr);


IObservableMap<String^, Object^>^ Einstellungen::DefaultViewModel::get()
{
	return safe_cast<IObservableMap<String^, Object^>^>(GetValue(_defaultViewModelProperty));
}

DependencyProperty^ Einstellungen::_navigationHelperProperty =
DependencyProperty::Register("NavigationHelper",
TypeName(Common::NavigationHelper::typeid), TypeName(Einstellungen::typeid), nullptr);


Common::NavigationHelper^ Einstellungen::NavigationHelper::get()
{
	return safe_cast<Common::NavigationHelper^>(GetValue(_navigationHelperProperty));
}

#pragma region Navigation support


void Einstellungen::OnNavigatedTo(NavigationEventArgs^ e)
{
	NavigationHelper->OnNavigatedTo(e);

	//
	// Status der Erfolge bestimmen
	// Pfad bestimmen und in std::string konvertieren
	String^ tempPfad = Windows::Storage::ApplicationData::Current->LocalFolder->Path;
	tempPfad += "\\data1.yatzy";
	std::string tempPfadConvert(tempPfad->Begin(), tempPfad->End());

	std::ifstream file(tempPfadConvert);
	int iAnzahlFarben{ 1 }, iAnzahlWürfel{ 1 };

	// Fehlerprüfung
	if (file.fail() == false)
	{
		// Variablen
		std::vector<std::string> szVecPunkte;
		std::vector<int> iVecPunkte;
		std::string puffer;
		int iTemp;

		// Punkte auslesen
		while (!file.eof() && file.good())
		{
			// Name ignorieren
			getline(file, puffer);
			if (!puffer.compare("")) continue;
			// Punkte
			getline(file, puffer);
			szVecPunkte.push_back(puffer);
		}

		// std::string to int
		for (auto puffer : szVecPunkte)
		{
			std::istringstream(puffer) >> iTemp;
			iVecPunkte.push_back(iTemp);
		}

		// Vektor anlegen und initialisieren
		std::vector<bool> bVec(7);
		for (auto puffer : bVec)
			puffer = false;

		// Status der Erfolge bestimmen
		for (auto puffer : iVecPunkte)
		{
			// Willkommen
			if (puffer && bVec.at(0) == false){
				iAnzahlFarben += 2;
				iAnzahlWürfel += 1;
				bVec.at(0) = true;
			}
			// Sieger der Herzen
			if (puffer <= 5 && bVec.at(1) == false){
				iAnzahlFarben += 3;
				iAnzahlWürfel += 1;
				bVec.at(1) = true;
			}
			// Perfektes Spiel
			if (puffer == 375){
				iAnzahlFarben = 19;
				iAnzahlWürfel = 8;
				break;
			}
			// Anfänger
			if (puffer >= 200 && bVec.at(2) == false){
				iAnzahlFarben += 2;
				iAnzahlWürfel += 1;
				bVec.at(2) = true;
			}
			// Gelegenheitsspieler
			if (puffer >= 250 && bVec.at(3) == false){
				iAnzahlFarben += 3;
				iAnzahlWürfel += 1;
				bVec.at(3) = true;
			}
			// Fortgeschrittener
			if (puffer >= 300 && bVec.at(4) == false){
				iAnzahlFarben += 3;
				iAnzahlWürfel += 1;
				bVec.at(4) = true;
			}
			// Profi
			if (puffer >= 320 && bVec.at(5) == false){
				iAnzahlFarben += 3;
				iAnzahlWürfel += 1;
				bVec.at(5) = true;
			}
			// Meister
			if (puffer >= 350 && bVec.at(6) == false){
				iAnzahlFarben += 3;
				iAnzahlWürfel += 2;
				bVec.at(6) = true;
			}
		}
	}

	// freigeschaltete Farben anzeigen#
	//iAnzahlFarben = 19;
	//iAnzahlWürfel = 8;
	for (int i = 0; i <= iAnzahlFarben - 1; i++)
	{
		TextBlock^ tempTextBlock = ref new TextBlock;

		switch (i)
		{
		case 0: tempTextBlock->Text = "schwarz"; break;
		case 1: tempTextBlock->Text = "dunkelblau"; break;
		case 2: tempTextBlock->Text = "hellblau"; break;
		case 3: tempTextBlock->Text = "dunkelrot"; break;
		case 4: tempTextBlock->Text = "hellrot"; break;
		case 5: tempTextBlock->Text = "dunkelgrün"; break;
		case 6: tempTextBlock->Text = "hellgrün"; break;
		case 7: tempTextBlock->Text = "gelb"; break;
		case 8: tempTextBlock->Text = "dunkelbraun"; break;
		case 9: tempTextBlock->Text = "hellbraun"; break;
		case 10: tempTextBlock->Text = "türkis"; break;
		case 11: tempTextBlock->Text = "grau (dunkel)"; break;
		case 12: tempTextBlock->Text = "grau (mittel)"; break;
		case 13: tempTextBlock->Text = "grau (hell)"; break;
		case 14: tempTextBlock->Text = "helllila"; break;
		case 15: tempTextBlock->Text = "dunkellila"; break;
		case 16: tempTextBlock->Text = "hellorange"; break;
		case 17: tempTextBlock->Text = "dunkelorange"; break;
		case 18: tempTextBlock->Text = "rosa"; break;
		default: tempTextBlock->Text = "unbelegt"; break;
		}
		ComboBoxFarbeBackground->Items->Append(tempTextBlock);
	}

	// freigeschaltete Würfel anzeigen
	for (int i = 0; i <= iAnzahlWürfel - 1; i++)
	{
		TextBlock^ tempTextBlock = ref new TextBlock;

		switch (i)
		{
		case 0: tempTextBlock->Text = "klassisch"; break;
		case 1: tempTextBlock->Text = "modern"; break;
		case 2: tempTextBlock->Text = "rund"; break;
		case 3: tempTextBlock->Text = "numerisch"; break;
		case 4: tempTextBlock->Text = "Brailleschrift"; break;
		case 5: tempTextBlock->Text = "japanisch"; break;
		case 6: tempTextBlock->Text = "römisch"; break;
		case 7: tempTextBlock->Text = "intuitiv"; break;
		default: tempTextBlock->Text = "unbelegt"; break;
		}
		ComboBoxWürfel->Items->Append(tempTextBlock);
	}

	// Standard einstellen
	ComboBoxWürfel->SelectedIndex = 0;
	ComboBoxFarbeBackground->SelectedIndex = 0;

	//
	// Skalierungsfaktor berechnen
	double dScaleFactor = Window::Current->Bounds.Width / 400;

	// Überschrift anpassen
	textÜberschrift->FontSize = static_cast<int>(dScaleFactor * 24);
	rectÜberschrift->Height = static_cast<int>(dScaleFactor * 3);

	// Grid skalieren
	for (int i = 0; i <= 3; i++)
	{
		Grid^ tempGrid;

		switch (i)
		{
		case 0: tempGrid = gridName;  break;
		case 1: tempGrid = gridVorschau; break;
		case 2: tempGrid = gridWürfel; break;
		case 3: tempGrid = gridHintergrund; break;
		}

		tempGrid->Width = static_cast<int>(dScaleFactor * 400);
	}

	// Text skalieren
	for (int i = 0; i <= 3; i++)
	{
		TextBlock^ tempTextBlock;

		switch (i)
		{
		case 0: tempTextBlock = textName; break;
		case 1: tempTextBlock = textVorschau; break;
		case 2: tempTextBlock = textWürfel; break;
		case 3: tempTextBlock = textHintergrund; break;
		}
		tempTextBlock->Height = static_cast<int>(dScaleFactor * 40);
		tempTextBlock->Width = static_cast<int>(dScaleFactor * 180);
		tempTextBlock->FontSize = static_cast<int>(dScaleFactor * 23);
	}

	// TextBox skalieren
	TextBoxName->Width = static_cast<int>(dScaleFactor * 180);
	TextBoxName->Height = static_cast<int>(dScaleFactor * 40);

	// ToggleSwitch skalieren
	ToggleVorschau->Width = static_cast<int>(dScaleFactor * 180);

	// ComboBox skalieren
	for (int i = 0; i <= 1; i++)
	{
		ComboBox^ tempComboBox;

		switch (i)
		{
		case 0: tempComboBox = ComboBoxWürfel; break;
		case 1: tempComboBox = ComboBoxFarbeBackground; break;
		}

		tempComboBox->Width = static_cast<int>(dScaleFactor * 180);
		tempComboBox->FontSize = static_cast<int>(dScaleFactor * 20);
	}

	// Button skalieren
	for (int i = 0; i <= 1; i++)
	{
		Button^ tempButton;

		switch (i)
		{
		case 0: tempButton = buttonOK; break;
		case 1: tempButton = buttonReset; break;
		}

		tempButton->FontSize = static_cast<int>(dScaleFactor * 18);
		tempButton->Height = static_cast<int>(dScaleFactor * 57);
		tempButton->Width = static_cast<int>(dScaleFactor * 134);
	}

	// Pfad bestimmen und in std::string konvertieren
	tempPfad = Windows::Storage::ApplicationData::Current->LocalFolder->Path;
	tempPfad += "\\data2.yatzy";
	std::string tempPfadConvert2(tempPfad->Begin(), tempPfad->End());

	// Punkte auslesen
	std::ifstream file2(tempPfadConvert2);
	std::string tempString;
	std::vector<std::string> tempVektor;
	String^ convert;
	std::wstring wstringPuffer;
	wchar_t* wString;

	// Fehlerprüfung
	if (file2.fail() == true)
		return;

	// Einstellungen auslesen
	while (!file2.eof() && file2.good())
	{
		// Name
		getline(file2, tempString);
		if (!tempString.compare("")) tempString = "nemo";
		tempVektor.push_back(tempString);
	}

	// aufräumen
	file2.close();

	// Name
	wstringPuffer = std::wstring(tempVektor.at(0).begin(), tempVektor.at(0).end());
	wString = const_cast<wchar_t*>(wstringPuffer.c_str());
	TextBoxName->Text = ref new String(wString);

	// Vorschau
	(tempVektor.at(1).compare("1") != 0) ? ToggleVorschau->IsOn = false : ToggleVorschau->IsOn = true;

	// Würfel
	ComboBoxWürfel->SelectedIndex = atoi(tempVektor.at(2).c_str());
	
	// Farbe
	ComboBoxFarbeBackground->SelectedIndex = atoi(tempVektor.at(3).c_str());

	// Hintergrundfarbe anpassen
	int iTemp = atoi(tempVektor.at(3).c_str());

	switch (iTemp)
	{
	case 0: Einstellungen::Background = ref new SolidColorBrush(Windows::UI::ColorHelper::FromArgb(255, 0, 0, 0)); break;			// schwarz
	case 1: Einstellungen::Background = ref new SolidColorBrush(Windows::UI::ColorHelper::FromArgb(255, 5, 42, 78)); break;			// dunkelblau
	case 2: Einstellungen::Background = ref new SolidColorBrush(Windows::UI::ColorHelper::FromArgb(255, 85, 136, 186)); break;		// hellblau
	case 3: Einstellungen::Background = ref new SolidColorBrush(Windows::UI::ColorHelper::FromArgb(255, 78, 5, 5)); break;			// dunkelrot
	case 4: Einstellungen::Background = ref new SolidColorBrush(Windows::UI::ColorHelper::FromArgb(255, 186, 85, 85)); break;		// hellrot
	case 5: Einstellungen::Background = ref new SolidColorBrush(Windows::UI::ColorHelper::FromArgb(255, 5, 78, 27)); break;			// dunkelgrün
	case 6: Einstellungen::Background = ref new SolidColorBrush(Windows::UI::ColorHelper::FromArgb(255, 101, 186, 85)); break;		// hellgrün
	case 7: Einstellungen::Background = ref new SolidColorBrush(Windows::UI::ColorHelper::FromArgb(255, 255, 185, 1)); break;		// gelb
	case 8: Einstellungen::Background = ref new SolidColorBrush(Windows::UI::ColorHelper::FromArgb(255, 124, 76, 35)); break;		// dunkelbraun
	case 9: Einstellungen::Background = ref new SolidColorBrush(Windows::UI::ColorHelper::FromArgb(255, 192, 130, 76)); break;		// hellbraun
	case 10: Einstellungen::Background = ref new SolidColorBrush(Windows::UI::ColorHelper::FromArgb(255, 95, 158, 160)); break;		// türkis
	case 11: Einstellungen::Background = ref new SolidColorBrush(Windows::UI::ColorHelper::FromArgb(255, 43, 43, 43)); break;		// grau (dunkel)
	case 12: Einstellungen::Background = ref new SolidColorBrush(Windows::UI::ColorHelper::FromArgb(255, 98, 98, 98)); break;		// grau (mittel)
	case 13: Einstellungen::Background = ref new SolidColorBrush(Windows::UI::ColorHelper::FromArgb(255, 167, 167, 167)); break;	// grau (hell)
	case 14: Einstellungen::Background = ref new SolidColorBrush(Windows::UI::ColorHelper::FromArgb(255, 167, 108, 154)); break;	// lila (hell)
	case 15: Einstellungen::Background = ref new SolidColorBrush(Windows::UI::ColorHelper::FromArgb(255, 102, 64, 94)); break;		// lila (dunkel)
	case 16: Einstellungen::Background = ref new SolidColorBrush(Windows::UI::ColorHelper::FromArgb(255, 255, 153, 0)); break;		// orange (hell)
	case 17: Einstellungen::Background = ref new SolidColorBrush(Windows::UI::ColorHelper::FromArgb(255, 226, 111, 0)); break;		// orange (dunkel)
	case 18: Einstellungen::Background = ref new SolidColorBrush(Windows::UI::ColorHelper::FromArgb(255, 224, 132, 187)); break;	// rosa
	}
}

void Einstellungen::OnNavigatedFrom(NavigationEventArgs^ e)
{
	NavigationHelper->OnNavigatedFrom(e);
}

#pragma endregion


void Einstellungen::LoadState(Object^ sender, Common::LoadStateEventArgs^ e)
{
	(void) sender;	// Nicht verwendeter Parameter
	(void) e;	// Nicht verwendeter Parameter
}


void Einstellungen::SaveState(Object^ sender, Common::SaveStateEventArgs^ e){
	(void) sender;	// Nicht verwendeter Parameter
	(void) e; // Nicht verwendeter Parameter
}


void Yatzy::Einstellungen::ButtonOK_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	// neue Einstellungen speichern
	std::string tempName(TextBoxName->Text->Begin(), TextBoxName->Text->End());
	bool tempVorschau = ToggleVorschau->IsOn;
	int tempWürfel = ComboBoxWürfel->SelectedIndex;
	int tempFarbeBackground = ComboBoxFarbeBackground->SelectedIndex;
	std::ofstream file;

	// Pfad bestimmen und in std::string konvertieren
	String^ tempPfad = Windows::Storage::ApplicationData::Current->LocalFolder->Path;
	tempPfad += "\\data2.yatzy";
	std::string tempPfadConvert(tempPfad->Begin(), tempPfad->End());

	file.open(tempPfadConvert, std::ios::trunc);
	file << tempName << '\n' << tempVorschau
		<< '\n' << tempWürfel << '\n' << tempFarbeBackground  << '\n';
	file.close();

	// Meldung ausgeben
	MessageDialog^ msg = ref new MessageDialog("Ihre Einstellungen wurden erfolgreich gespeichert.");
	msg->Title = "Information";

	// zeige den Dialog
	msg->ShowAsync();

	// Fehlerprüfung
	if (file.fail() == true)
		return;

	// Hintergrundfarbe anpassen
	switch (tempFarbeBackground)
	{
	case 0: Einstellungen::Background = ref new SolidColorBrush(Windows::UI::ColorHelper::FromArgb(255, 0, 0, 0)); break;			// schwarz
	case 1: Einstellungen::Background = ref new SolidColorBrush(Windows::UI::ColorHelper::FromArgb(255, 5, 42, 78)); break;			// dunkelblau
	case 2: Einstellungen::Background = ref new SolidColorBrush(Windows::UI::ColorHelper::FromArgb(255, 85, 136, 186)); break;		// hellblau
	case 3: Einstellungen::Background = ref new SolidColorBrush(Windows::UI::ColorHelper::FromArgb(255, 78, 5, 5)); break;			// dunkelrot
	case 4: Einstellungen::Background = ref new SolidColorBrush(Windows::UI::ColorHelper::FromArgb(255, 186, 85, 85)); break;		// hellrot
	case 5: Einstellungen::Background = ref new SolidColorBrush(Windows::UI::ColorHelper::FromArgb(255, 5, 78, 27)); break;			// dunkelgrün
	case 6: Einstellungen::Background = ref new SolidColorBrush(Windows::UI::ColorHelper::FromArgb(255, 101, 186, 85)); break;		// hellgrün
	case 7: Einstellungen::Background = ref new SolidColorBrush(Windows::UI::ColorHelper::FromArgb(255, 255, 185, 1)); break;		// gelb
	case 8: Einstellungen::Background = ref new SolidColorBrush(Windows::UI::ColorHelper::FromArgb(255, 124, 76, 35)); break;		// dunkelbraun
	case 9: Einstellungen::Background = ref new SolidColorBrush(Windows::UI::ColorHelper::FromArgb(255, 192, 130, 76)); break;		// hellbraun
	case 10: Einstellungen::Background = ref new SolidColorBrush(Windows::UI::ColorHelper::FromArgb(255, 95, 158, 160)); break;		// türkis
	case 11: Einstellungen::Background = ref new SolidColorBrush(Windows::UI::ColorHelper::FromArgb(255, 43, 43, 43)); break;		// grau (dunkel)
	case 12: Einstellungen::Background = ref new SolidColorBrush(Windows::UI::ColorHelper::FromArgb(255, 98, 98, 98)); break;		// grau (mittel)
	case 13: Einstellungen::Background = ref new SolidColorBrush(Windows::UI::ColorHelper::FromArgb(255, 167, 167, 167)); break;	// grau (hell)
	case 14: Einstellungen::Background = ref new SolidColorBrush(Windows::UI::ColorHelper::FromArgb(255, 167, 108, 154)); break;	// lila (hell)
	case 15: Einstellungen::Background = ref new SolidColorBrush(Windows::UI::ColorHelper::FromArgb(255, 102, 64, 94)); break;		// lila (dunkel)
	case 16: Einstellungen::Background = ref new SolidColorBrush(Windows::UI::ColorHelper::FromArgb(255, 255, 153, 0)); break;		// orange (hell)
	case 17: Einstellungen::Background = ref new SolidColorBrush(Windows::UI::ColorHelper::FromArgb(255, 226, 111, 0)); break;		// orange (dunkel)
	case 18: Einstellungen::Background = ref new SolidColorBrush(Windows::UI::ColorHelper::FromArgb(255, 224, 132, 187)); break;	// rosa
	}
}


void Yatzy::Einstellungen::buttonReset_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	// Pfad bestimmen und in std::string konvertieren
	String^ tempPfad = Windows::Storage::ApplicationData::Current->LocalFolder->Path;
	tempPfad += "\\data1.yatzy";
	std::string tempPfadConvert1(tempPfad->Begin(), tempPfad->End());
	// Pfad bestimmen und in std::string konvertieren
	tempPfad = Windows::Storage::ApplicationData::Current->LocalFolder->Path;
	tempPfad += "\\data2.yatzy";
	std::string tempPfadConvert2(tempPfad->Begin(), tempPfad->End());

	// Dateien löschen
	if (std::remove(tempPfadConvert2.c_str()) == 0)
		if (std::remove(tempPfadConvert1.c_str()) == 0)
		{
			// Meldung ausgeben
			MessageDialog^ msg = ref new MessageDialog("Yatzuu wurde erfolgreich zurückgesetzt.");
			msg->Title = "Information";

			// zeige den Dialog
			msg->ShowAsync();

			// Einstellungen laden
			Einstellungen::Background = ref new SolidColorBrush(Windows::UI::Colors::Black);
			ComboBoxWürfel->SelectedIndex = 0;
			ComboBoxFarbeBackground->SelectedIndex = 0;
			ToggleVorschau->IsOn = true;
			TextBoxName->Text = "nemo";

			return;
		}

	// Fehlermeldung ausgeben
	MessageDialog^ msg = ref new MessageDialog("Yatzuu ist bereits zurückgesetzt.");
	msg->Title = "Information";

	// zeige den Dialog
	msg->ShowAsync();

	// Einstellungen laden
	Einstellungen::Background = ref new SolidColorBrush(Windows::UI::Colors::Black);
	ComboBoxWürfel->SelectedIndex = 0;
	ComboBoxFarbeBackground->SelectedIndex = 0;
	ToggleVorschau->IsOn = true;
	TextBoxName->Text = "nemo";
}


void Yatzy::Einstellungen::TextBoxName_GotFocus(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	TextBoxName->Text = "";
}
