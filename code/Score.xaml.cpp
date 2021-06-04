//
// Score.xaml.cpps
// Implementierung der Score-Klasse
//

#include "pch.h"
#include "Score.xaml.h"
#include "MainPage.xaml.h"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <istream>
#include <tuple>

using namespace Yatzy;

using namespace Platform;
using namespace Platform::Collections;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Interop;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Navigation;

// Die Elementvorlage "Standardseite" ist unter "http://go.microsoft.com/fwlink/?LinkID=390556" dokumentiert.

Score::Score()
{
	InitializeComponent();
	SetValue(_defaultViewModelProperty, ref new Platform::Collections::Map<String^, Object^>(std::less<String^>()));
	auto navigationHelper = ref new Common::NavigationHelper(this);
	SetValue(_navigationHelperProperty, navigationHelper);
	navigationHelper->LoadState += ref new Common::LoadStateEventHandler(this, &Score::LoadState);
	navigationHelper->SaveState += ref new Common::SaveStateEventHandler(this, &Score::SaveState);
}


DependencyProperty^ Score::_defaultViewModelProperty =
DependencyProperty::Register("DefaultViewModel",
TypeName(IObservableMap<String^, Object^>::typeid), TypeName(Score::typeid), nullptr);


IObservableMap<String^, Object^>^ Score::DefaultViewModel::get()
{
	return safe_cast<IObservableMap<String^, Object^>^>(GetValue(_defaultViewModelProperty));
}

DependencyProperty^ Score::_navigationHelperProperty =
DependencyProperty::Register("NavigationHelper",
TypeName(Common::NavigationHelper::typeid), TypeName(Score::typeid), nullptr);


Common::NavigationHelper^ Score::NavigationHelper::get()
{
	return safe_cast<Common::NavigationHelper^>(GetValue(_navigationHelperProperty));
}


#pragma region Navigation support


bool pktSort(std::tuple<std::string, std::string> tupleTemp1, std::tuple<std::string, std::string> tupleTemp2)
{
	// std::string to int
	int iTemp1, iTemp2;
	std::istringstream(std::get<1>(tupleTemp1)) >> iTemp1;
	std::istringstream(std::get<1>(tupleTemp2)) >> iTemp2;

	// Vergleich
	if (iTemp1 < iTemp2)
		return false;
	return true;
}


void Score::OnNavigatedTo(NavigationEventArgs^ e)
{
	NavigationHelper->OnNavigatedTo(e);

	// Skalierungsfaktor berechnen
	double dScaleFactor = Window::Current->Bounds.Width / 400;

	// Überschrift anpassen
	textÜberschrift->FontSize = static_cast<int>(dScaleFactor * 24);
	rectÜberschrift->Height = static_cast<int>(dScaleFactor * 3);

	// Pfad auslesen und speichern
	String^ tempPfad = Windows::Storage::ApplicationData::Current->LocalFolder->Path;
	tempPfad += "\\data2.yatzy";
	std::string tempPfadConvert2(tempPfad->Begin(), tempPfad->End());

	// Hintergrund anpassen
	std::ifstream file2(tempPfadConvert2);
	std::string tempString;
	std::vector<std::string> tempVektor;

	// Fehlerprüfung
	if (file2.fail() != true)
	{

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

		// Farbe
		int iTemp = atoi(tempVektor.at(3).c_str());

		switch (iTemp)
		{
		case 0: Score::Background = ref new SolidColorBrush(Windows::UI::ColorHelper::FromArgb(255, 0, 0, 0)); break;			// schwarz
		case 1: Score::Background = ref new SolidColorBrush(Windows::UI::ColorHelper::FromArgb(255, 5, 42, 78)); break;			// dunkelblau
		case 2: Score::Background = ref new SolidColorBrush(Windows::UI::ColorHelper::FromArgb(255, 85, 136, 186)); break;		// hellblau
		case 3: Score::Background = ref new SolidColorBrush(Windows::UI::ColorHelper::FromArgb(255, 78, 5, 5)); break;			// dunkelrot
		case 4: Score::Background = ref new SolidColorBrush(Windows::UI::ColorHelper::FromArgb(255, 186, 85, 85)); break;		// hellrot
		case 5: Score::Background = ref new SolidColorBrush(Windows::UI::ColorHelper::FromArgb(255, 5, 78, 27)); break;			// dunkelgrün
		case 6: Score::Background = ref new SolidColorBrush(Windows::UI::ColorHelper::FromArgb(255, 101, 186, 85)); break;		// hellgrün
		case 7: Score::Background = ref new SolidColorBrush(Windows::UI::ColorHelper::FromArgb(255, 255, 185, 1)); break;		// gelb
		case 8: Score::Background = ref new SolidColorBrush(Windows::UI::ColorHelper::FromArgb(255, 124, 76, 35)); break;		// dunkelbraun
		case 9: Score::Background = ref new SolidColorBrush(Windows::UI::ColorHelper::FromArgb(255, 192, 130, 76)); break;		// hellbraun
		case 10: Score::Background = ref new SolidColorBrush(Windows::UI::ColorHelper::FromArgb(255, 95, 158, 160)); break;		// türkis
		case 11: Score::Background = ref new SolidColorBrush(Windows::UI::ColorHelper::FromArgb(255, 43, 43, 43)); break;		// grau (dunkel)
		case 12: Score::Background = ref new SolidColorBrush(Windows::UI::ColorHelper::FromArgb(255, 98, 98, 98)); break;		// grau (mittel)
		case 13: Score::Background = ref new SolidColorBrush(Windows::UI::ColorHelper::FromArgb(255, 167, 167, 167)); break;	// grau (hell)
		case 14: Score::Background = ref new SolidColorBrush(Windows::UI::ColorHelper::FromArgb(255, 167, 108, 154)); break;	// lila (hell)
		case 15: Score::Background = ref new SolidColorBrush(Windows::UI::ColorHelper::FromArgb(255, 102, 64, 94)); break;		// lila (dunkel)
		case 16: Score::Background = ref new SolidColorBrush(Windows::UI::ColorHelper::FromArgb(255, 255, 153, 0)); break;		// orange (hell)
		case 17: Score::Background = ref new SolidColorBrush(Windows::UI::ColorHelper::FromArgb(255, 226, 111, 0)); break;		// orange (dunkel)
		case 18: Score::Background = ref new SolidColorBrush(Windows::UI::ColorHelper::FromArgb(255, 224, 132, 187)); break;	// rosa
		}
	}

	// Pfad auslesen und speichern
	tempPfad = Windows::Storage::ApplicationData::Current->LocalFolder->Path;
	tempPfad += "\\data1.yatzy";
	std::string tempPfadConvert1(tempPfad->Begin(), tempPfad->End());

	// Punkte auslesen
	std::vector<std::tuple < std::string, std::string>> vecValues;
	std::ifstream file1(tempPfadConvert1);
	std::string puffer, tempName;
	std::wstring wstringPuffer;
	TextBlock^ tempTextBlock;
	wchar_t* wString;
	String^ convert;
	int iCounter{ 0 }, iPunkteGesamt{ 0 };

	// Fehlerprüfung
	if (file1.fail() != true)
	{

		// Namen und Punkte auslesen
		while (!file1.eof() && file1.good())
		{
			// Name
			getline(file1, puffer);
			if (!puffer.compare("")) continue;
			tempName = puffer;
			// Punkte
			getline(file1, puffer);
			vecValues.push_back(std::tuple<std::string, std::string>(tempName, puffer));	// Tupel -> Name, Punktzahl
		}

		// aufräumen
		file1.close();

		// Vektor Punkte sortieren
		std::sort(vecValues.begin(), vecValues.end(), pktSort);

		// Ausgabe der Namen, Punkte und des Platzes
		for (auto puffer : vecValues)
		{
			// nur die 10 besten Wertungen
			if (iCounter++ >= 10)
			{
				iPunkteGesamt += atoi(std::get<1>(puffer).c_str());
				continue;
			}

			// TextBlock füllen
			tempTextBlock = ref new TextBlock;
			tempTextBlock->Text = iCounter.ToString();
			tempTextBlock->FontSize = static_cast<int>(dScaleFactor * 18);

			// Ausgabe des Platzes
			ausgabePlatz->Items->Append(tempTextBlock);

			// Name -> std::string to String^
			wstringPuffer = std::wstring(std::get<0>(puffer).begin(), std::get<0>(puffer).end());
			wString = const_cast<wchar_t*>(wstringPuffer.c_str());
			convert = ref new String(wString);

			// TextBlock füllen
			tempTextBlock = ref new TextBlock;
			tempTextBlock->Text = convert;
			tempTextBlock->FontSize = 18;

			// Name ausgeben
			ausgabeName->Items->Append(tempTextBlock);

			// Punkte -> std::string to String^
			wstringPuffer = std::wstring(std::get<1>(puffer).begin(), std::get<1>(puffer).end());
			wString = const_cast<wchar_t*>(wstringPuffer.c_str());
			convert = ref new String(wString);
			iPunkteGesamt += atoi(std::get<1>(puffer).c_str());

			// TextBlock füllen
			tempTextBlock = ref new TextBlock;
			tempTextBlock->Text = convert;
			tempTextBlock->FontSize = static_cast<int>(dScaleFactor * 18);

			// Punkte ausgeben
			ausgabePunkte->Items->Append(tempTextBlock);
		}

		// arithmetisches Mittel und Anzahl der Spiele ausgeben
		for (int i = 0; i <= 3; i++)
		{
			tempTextBlock = ref new TextBlock;
			tempTextBlock->FontSize = static_cast<int>(dScaleFactor * 18);

			switch (i)
			{
			case 0: tempTextBlock->Text = "Anzahl der Spiele"; break;
			case 1: tempTextBlock->Text = iCounter.ToString(); break;
			case 2: tempTextBlock->Text = "arithmetisches Mittel"; break;
			case 3: tempTextBlock->Text = (iPunkteGesamt / iCounter).ToString(); break;
			}

			if (i%2 == 0)
				ausgabeInfo_Text->Items->Append(tempTextBlock);
			else
				ausgabeInfo_Pkt->Items->Append(tempTextBlock);
		}
	}
}

void Score::OnNavigatedFrom(NavigationEventArgs^ e)
{
	NavigationHelper->OnNavigatedFrom(e);
}

#pragma endregion


void Score::LoadState(Object^ sender, Common::LoadStateEventArgs^ e)
{
	(void) sender;	// Nicht verwendeter Parameter
	(void) e;	// Nicht verwendeter Parameter
}


void Score::SaveState(Object^ sender, Common::SaveStateEventArgs^ e){
	(void) sender;	// Nicht verwendeter Parameter
	(void) e; // Nicht verwendeter Parameter
}
