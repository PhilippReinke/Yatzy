//
// Erfolge.xaml.cpp
// Implementierung der Erfolge-Klasse
//

#include "pch.h"
#include "Erfolge.xaml.h"
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
using namespace Windows::Graphics::Imaging;
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

Erfolge::Erfolge()
{
	InitializeComponent();
	SetValue(_defaultViewModelProperty, ref new Platform::Collections::Map<String^, Object^>(std::less<String^>()));
	auto navigationHelper = ref new Common::NavigationHelper(this);
	SetValue(_navigationHelperProperty, navigationHelper);
	navigationHelper->LoadState += ref new Common::LoadStateEventHandler(this, &Erfolge::LoadState);
	navigationHelper->SaveState += ref new Common::SaveStateEventHandler(this, &Erfolge::SaveState);
}

DependencyProperty^ Erfolge::_defaultViewModelProperty =
DependencyProperty::Register("DefaultViewModel",
TypeName(IObservableMap<String^, Object^>::typeid), TypeName(Erfolge::typeid), nullptr);


IObservableMap<String^, Object^>^ Erfolge::DefaultViewModel::get()
{
	return safe_cast<IObservableMap<String^, Object^>^>(GetValue(_defaultViewModelProperty));
}

DependencyProperty^ Erfolge::_navigationHelperProperty =
DependencyProperty::Register("NavigationHelper",
TypeName(Common::NavigationHelper::typeid), TypeName(Erfolge::typeid), nullptr);


Common::NavigationHelper^ Erfolge::NavigationHelper::get()
{
	return safe_cast<Common::NavigationHelper^>(GetValue(_navigationHelperProperty));
}

#pragma region Navigation support


void Erfolge::OnNavigatedTo(NavigationEventArgs^ e)
{
	NavigationHelper->OnNavigatedTo(e);

	// Skalierungsfaktor berechnen
	double dScaleFactor = Window::Current->Bounds.Width / 400;

	// Pfad bestimmen und in std::string konvertieren
	String^ tempPfad = Windows::Storage::ApplicationData::Current->LocalFolder->Path;
	tempPfad += "\\data1.yatzy";
	std::string tempPfadConvert(tempPfad->Begin(), tempPfad->End());

	// Status der Erfolge bestimmen
	std::ifstream file(tempPfadConvert);
	std::vector<bool> bStatusErfolge(8);

	// bStatus initialisieren
	for (auto puffer : bStatusErfolge)
		puffer = false;

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

		// Status der Erfolge bestimmen
		for (auto puffer : iVecPunkte)
		{
			// Willkommen
			if(puffer) bStatusErfolge.at(0) = true;
			// Sieger der Herzen
			if (puffer == 5) bStatusErfolge.at(1) = true;
			// Perfektes Spiel
			if (puffer == 375) bStatusErfolge.at(2) = true;
			// Anfänger
			if (puffer >= 200) bStatusErfolge.at(3) = true;
			// Gelegenheitsspieler
			if (puffer >= 250) bStatusErfolge.at(4) = true;
			// Fortgeschrittener
			if (puffer >= 300) bStatusErfolge.at(5) = true;
			// Profi
			if (puffer >= 320) bStatusErfolge.at(6) = true;
			// Meister
			if (puffer >= 350) bStatusErfolge.at(7) = true;
		}
	}
	
	// Bilder in Vektor packen
	std::vector<Image^> vecImage{ ImageWillkommenWeiß, ImageSiegerWeiß, ImagePerfektWeiß,
		ImageAnfängerWeiß, ImageGelegenWeiß, ImageFortgWeiß, ImageProfiWeiß, ImageMeisterWeiß };

	// Elemente anpassen
	for (int i = 0; i <= 7; i++)
	{
		// Variablen
		std::tuple<TextBlock^, TextBlock^> tempTupel;
		Border^ tempBorder;
		Grid^ tempGrid;
		Image^ tempImage;

		// temporäre Elemente initailisieren
		switch (i)
		{
		case 0: 
			tempTupel = std::make_tuple(text1Will, text2Will);
			tempBorder = borderWill;
			tempGrid = gridWill;
			tempImage = imageWill;
			break;
		case 1:
			tempTupel = std::make_tuple(text1Sieger, text2Sieger);
			tempBorder = borderSieger;
			tempGrid = gridSieger;
			tempImage = imageSieger;
			break;
		case 2:
			tempTupel = std::make_tuple(text1Perf, text2Perf);
			tempBorder = borderPerf;
			tempGrid = gridPerf;
			tempImage = imagePerf;
			break;
		case 3:
			tempTupel = std::make_tuple(text1Anf, text2Anf);
			tempBorder = borderAnf;
			tempGrid = gridAnf;
			tempImage = imageAnf;
			break;
		case 4:
			tempTupel = std::make_tuple(text1Geleg, text2Geleg);
			tempBorder = borderGeleg;
			tempGrid = gridGeleg;
			tempImage = imageGeleg;
			break;
		case 5:
			tempTupel = std::make_tuple(text1Fortg, text2Fortg);
			tempBorder = borderFortg;
			tempGrid = gridFortg;
			tempImage = imageFortg;
			break;
		case 6:
			tempTupel = std::make_tuple(text1Profi, text2Profi);
			tempBorder = borderProfi;
			tempGrid = gridProfi;
			tempImage = imageProfi;
			break;
		case 7:
			tempTupel = std::make_tuple(text1Meister, text2Meister);
			tempBorder = borderMeister;
			tempGrid = gridMeister;
			tempImage = imageMeister;
			break;
		default:
			tempTupel = std::make_tuple(text1Will, text2Will);
			tempBorder = borderWill;
			tempGrid = gridWill;
			tempImage = imageWill;
		}

		// Elemente anpassen
		tempGrid->Width = static_cast<int>(dScaleFactor * 350);
		tempBorder->Height = static_cast<int>(dScaleFactor * 60);
		tempBorder->Width = static_cast<int>(dScaleFactor * 60);
		std::get<0>(tempTupel)->FontSize = static_cast<int>(dScaleFactor * 20);
		std::get<1>(tempTupel)->FontSize = static_cast<int>(dScaleFactor * 16);

		// erfüllt oder nicht erfüllt?
		if (bStatusErfolge.at(i) == true)
		{
			tempImage->Source = vecImage.at(i)->Source;
			std::get<0>(tempTupel)->Foreground = ref new SolidColorBrush(Windows::UI::Colors::White);
			std::get<1>(tempTupel)->Foreground = ref new SolidColorBrush(Windows::UI::Colors::White);

		}
	}

	// Überschrift anpassen
	textÜberschrift->FontSize = static_cast<int>(dScaleFactor * 24);
	rectÜberschrift->Height = static_cast<int>(dScaleFactor * 3);

	// Pfad bestimmen und in std::string konvertieren
	tempPfad = Windows::Storage::ApplicationData::Current->LocalFolder->Path;
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
	case 0: Erfolge::Background = ref new SolidColorBrush(Windows::UI::ColorHelper::FromArgb(255, 0, 0, 0)); break;			// schwarz
	case 1: Erfolge::Background = ref new SolidColorBrush(Windows::UI::ColorHelper::FromArgb(255, 5, 42, 78)); break;		// dunkelblau
	case 2: Erfolge::Background = ref new SolidColorBrush(Windows::UI::ColorHelper::FromArgb(255, 85, 136, 186)); break;	// hellblau
	case 3: Erfolge::Background = ref new SolidColorBrush(Windows::UI::ColorHelper::FromArgb(255, 78, 5, 5)); break;		// dunkelrot
	case 4: Erfolge::Background = ref new SolidColorBrush(Windows::UI::ColorHelper::FromArgb(255, 186, 85, 85)); break;		// hellrot
	case 5: Erfolge::Background = ref new SolidColorBrush(Windows::UI::ColorHelper::FromArgb(255, 5, 78, 27)); break;		// dunkelgrün
	case 6: Erfolge::Background = ref new SolidColorBrush(Windows::UI::ColorHelper::FromArgb(255, 101, 186, 85)); break;	// hellgrün
	case 7: Erfolge::Background = ref new SolidColorBrush(Windows::UI::ColorHelper::FromArgb(255, 255, 185, 1)); break;		// gelb
	case 8: Erfolge::Background = ref new SolidColorBrush(Windows::UI::ColorHelper::FromArgb(255, 124, 76, 35)); break;		// dunkelbraun
	case 9: Erfolge::Background = ref new SolidColorBrush(Windows::UI::ColorHelper::FromArgb(255, 192, 130, 76)); break;	// hellbraun
	case 10: Erfolge::Background = ref new SolidColorBrush(Windows::UI::ColorHelper::FromArgb(255, 95, 158, 160)); break;	// türkis
	case 11: Erfolge::Background = ref new SolidColorBrush(Windows::UI::ColorHelper::FromArgb(255, 43, 43, 43)); break;		// grau (dunkel)
	case 12: Erfolge::Background = ref new SolidColorBrush(Windows::UI::ColorHelper::FromArgb(255, 98, 98, 98)); break;		// grau (mittel)
	case 13: Erfolge::Background = ref new SolidColorBrush(Windows::UI::ColorHelper::FromArgb(255, 167, 167, 167)); break;	// grau (hell)
	case 14: Erfolge::Background = ref new SolidColorBrush(Windows::UI::ColorHelper::FromArgb(255, 167, 108, 154)); break;	// lila (hell)
	case 15: Erfolge::Background = ref new SolidColorBrush(Windows::UI::ColorHelper::FromArgb(255, 102, 64, 94)); break;	// lila (dunkel)
	case 16: Erfolge::Background = ref new SolidColorBrush(Windows::UI::ColorHelper::FromArgb(255, 255, 153, 0)); break;	// orange (hell)
	case 17: Erfolge::Background = ref new SolidColorBrush(Windows::UI::ColorHelper::FromArgb(255, 226, 111, 0)); break;	// orange (dunkel)
	case 18: Erfolge::Background = ref new SolidColorBrush(Windows::UI::ColorHelper::FromArgb(255, 224, 132, 187)); break;	// rosa
	}
}

void Erfolge::OnNavigatedFrom(NavigationEventArgs^ e)
{
	NavigationHelper->OnNavigatedFrom(e);
}

#pragma endregion


void Erfolge::LoadState(Object^ sender, Common::LoadStateEventArgs^ e)
{
	(void) sender;	// Nicht verwendeter Parameter
	(void) e;	// Nicht verwendeter Parameter
}


void Erfolge::SaveState(Object^ sender, Common::SaveStateEventArgs^ e){
	(void) sender;	// Nicht verwendeter Parameter
	(void) e; // Nicht verwendeter Parameter
}
