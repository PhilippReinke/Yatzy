//
// Verwaltung.h - Yatzy by Philipp Reinke |2014|
//
#ifndef VERWALTUNG_H
#define VERWALTUNG_H
#include <string>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace Windows::UI::Xaml::Media::Imaging;
using namespace Windows::Foundation;
using namespace Platform;

class Verwaltung
{
private:
	bool bNächsteRunde = false;
	std::vector<TextBlock^> hTextBlock;
	int iRunde{ 0 };
	int ivorherigeRunde{ 0 };
	double dScaleFactor;

	// data2.yatzy
	String^ name{ "nemo" };
	Brush^ brushBackground;
	int iBackgroundIndex;
	bool bVorschau = true;
	int iWürfelStyle;

public:
	// true -> nächste Runde | false -> warten
	bool getbNächsteRunde(){ return bNächsteRunde; }
	bool nächsteRunde(Ausgabe, Würfel);
	void intialisieren(std::vector<TextBlock^>, double);
	bool endOfGame(Ausgabe);
	bool refreshData();
	void skalieren(Ausgabe, Würfel);

	// getter
	std::vector<TextBlock^> gethTextBlock(){ return hTextBlock; }
	Brush^ getBrushBackground(){ return brushBackground; }
	double getScaleFactor(){ return dScaleFactor; }
	int getRunde(){ return iRunde; }
	std::string getName();
	int getWürfelStyleIndex(){ return iWürfelStyle; }
	bool getVorschau(){ return bVorschau; }
	int getBackgroundIndex(){ return iBackgroundIndex; }

	// setter
	void setbNächsteRunde(bool, Ausgabe);
	void setTextControlButton(Ausgabe);
	void setRunde(int i){ iRunde = i; }
};


void Verwaltung::skalieren(Ausgabe tempAusgabe, Würfel tempWürfel)
{
	// Text skalieren
	for (auto puffer : hTextBlock)
		puffer->FontSize = static_cast<int>(23 * dScaleFactor);

	// Würfel anpassen
	for (int i = 0; i <= 4; i++)
	{
		tempWürfel.hDice[i]->Height = static_cast<int>(80 * dScaleFactor);
		tempWürfel.hDice[i]->Width = static_cast<int>(60 * dScaleFactor);
	}

	// Ausgabe anpassen
	for (int i = 0; i <= 12; i++)
	{
		tempAusgabe.hToggleButton[i]->Height = 55 * dScaleFactor;
		tempAusgabe.hToggleButton[i]->FontSize = static_cast<int>(20 * dScaleFactor);
	}

	// Hauptbutton anpassen
	tempAusgabe.hControlButton->Height = static_cast<int>(57 * dScaleFactor);
	tempAusgabe.hControlButton->FontSize = static_cast<int>(19 * dScaleFactor);

	// Ausgabe skalieren (Bonus, Summe, Gesamt)
	for (int i = 0; i <= 2; i++)
	{
		tempAusgabe.hTextBlock[i]->FontSize = static_cast<int>(20 * dScaleFactor);
	}
}


void Verwaltung::setTextControlButton(Ausgabe tempAusgabe)
{
	switch (iRunde)
	{
	case 0: tempAusgabe.hControlButton->Content = "Los"; break;
	case 1: tempAusgabe.hControlButton->Content = "2. Wurf"; break;
	case 2: tempAusgabe.hControlButton->Content = "3. Wurf"; break;
	case 3:
		tempAusgabe.hControlButton->Content = "Neue Runde";
		tempAusgabe.hControlButton->IsEnabled = (bNächsteRunde == true) ? true : false;
		break;
	}
}


void Verwaltung::intialisieren(std::vector<TextBlock^> tempTextBlock, double dTempScaleFactor)
{
	hTextBlock = tempTextBlock;
	dScaleFactor = dTempScaleFactor;
}


// Daten aus data2.yatzy erneut laden und speichern
bool Verwaltung::refreshData()
{
	// Pfad bestimmen und in std::string konvertieren
	String^ tempPfad = Windows::Storage::ApplicationData::Current->LocalFolder->Path;
	tempPfad += "\\data2.yatzy";
	std::string tempPfadConvert(tempPfad->Begin(), tempPfad->End());

	// Einstellungen auslesen
	std::ifstream file(tempPfadConvert);
	std::string tempString;
	std::vector<std::string> tempVektor;
	
	// Variablen der Konvertierung
	std::wstring wstringPuffer;
	wchar_t* wString;
	String^ convert;

	// Fehlerprüfung
	if (file.fail() == true)
	{
		brushBackground = ref new SolidColorBrush(Windows::UI::Colors::Black);
		return false;
	}		

	// Einstellungen auslesen
	while (!file.eof() && file.good())
	{
		// Name
		getline(file, tempString);
		if (!tempString.compare("")) tempString = "nemo";
		tempVektor.push_back(tempString);
	}

	// aufräumen
	file.close();

	// Name
	wstringPuffer = std::wstring(tempVektor.at(0).begin(), tempVektor.at(0).end());
	wString = const_cast<wchar_t*>(wstringPuffer.c_str());
	name = ref new String(wString);

	// Vorschau
	(tempVektor.at(1).compare("1") == 0) ? bVorschau = true : bVorschau = false;

	// Designsatz der Würfel festlegen
	iWürfelStyle = atoi(tempVektor.at(2).c_str());

	// Farbe
	iBackgroundIndex = atoi(tempVektor.at(3).c_str());

	switch (iBackgroundIndex)
	{
	case 0: brushBackground = ref new SolidColorBrush(Windows::UI::ColorHelper::FromArgb(255, 0, 0, 0)); break;			// schwarz
	case 1: brushBackground = ref new SolidColorBrush(Windows::UI::ColorHelper::FromArgb(255, 5, 42, 78)); break;		// dunkelblau
	case 2: brushBackground = ref new SolidColorBrush(Windows::UI::ColorHelper::FromArgb(255, 85, 136, 186)); break;	// hellblau
	case 3: brushBackground = ref new SolidColorBrush(Windows::UI::ColorHelper::FromArgb(255, 78, 5, 5)); break;		// dunkelrot
	case 4: brushBackground = ref new SolidColorBrush(Windows::UI::ColorHelper::FromArgb(255, 186, 85, 85)); break;		// hellrot
	case 5: brushBackground = ref new SolidColorBrush(Windows::UI::ColorHelper::FromArgb(255, 5, 78, 27)); break;		// dunkelgrün
	case 6: brushBackground = ref new SolidColorBrush(Windows::UI::ColorHelper::FromArgb(255, 101, 186, 85)); break;	// hellgrün
	case 7: brushBackground = ref new SolidColorBrush(Windows::UI::ColorHelper::FromArgb(255, 255, 185, 1)); break;		// gelb
	case 8: brushBackground = ref new SolidColorBrush(Windows::UI::ColorHelper::FromArgb(255, 124, 76, 35)); break;		// dunkelbraun
	case 9: brushBackground = ref new SolidColorBrush(Windows::UI::ColorHelper::FromArgb(255, 192, 130, 76)); break;	// hellbraun
	case 10: brushBackground = ref new SolidColorBrush(Windows::UI::ColorHelper::FromArgb(255, 95, 158, 160)); break;	// türkis
	case 11: brushBackground = ref new SolidColorBrush(Windows::UI::ColorHelper::FromArgb(255, 43, 43, 43)); break;		// grau (dunkel)
	case 12: brushBackground = ref new SolidColorBrush(Windows::UI::ColorHelper::FromArgb(255, 98, 98, 98)); break;		// grau (mittel)
	case 13: brushBackground = ref new SolidColorBrush(Windows::UI::ColorHelper::FromArgb(255, 167, 167, 167)); break;	// grau (hell)
	case 14: brushBackground = ref new SolidColorBrush(Windows::UI::ColorHelper::FromArgb(255, 167, 108, 154)); break;	// lila (hell)
	case 15: brushBackground = ref new SolidColorBrush(Windows::UI::ColorHelper::FromArgb(255, 102, 64, 94)); break;	// lila (dunkel)
	case 16: brushBackground = ref new SolidColorBrush(Windows::UI::ColorHelper::FromArgb(255, 255, 153, 0)); break;	// orange (hell)
	case 17: brushBackground = ref new SolidColorBrush(Windows::UI::ColorHelper::FromArgb(255, 226, 111, 0)); break;	// orange (dunkel)
	case 18: brushBackground = ref new SolidColorBrush(Windows::UI::ColorHelper::FromArgb(255, 224, 132, 187)); break;	// rosa
	}

	return true;
}


// String^ to std::string
std::string Verwaltung::getName()
{
	std::string wtempString(name->Begin(), name->End());
	return wtempString;
}


bool Verwaltung::endOfGame(Ausgabe tempAusgabe)
{
	// Status der Punkte zurücksetzen
	for (int i = 0; i <= 12; i++)
		if (tempAusgabe.bPktStatus[i] == false)
			return false;

	// Runde auf Start setzen
	iRunde = 0;
	return true;
}


bool Verwaltung::nächsteRunde(Ausgabe tempAusgabe, Würfel tempDice)
{
	// wenn Punkte fixiert, dann nächste Runde
	if (bNächsteRunde == true)
	{
		ivorherigeRunde = iRunde;
		iRunde = 3;
	}

	switch (iRunde)
	{
	case 0:
		tempAusgabe.hControlButton->Content = "2. Wurf";
		break;
	case 1:
		tempAusgabe.hControlButton->Content = "3. Wurf";
		break;
	case 2:
		tempAusgabe.hControlButton->Content = "Neue Runde";
		tempAusgabe.hControlButton->IsEnabled = false;
		break;
	case 3:
		// Spieler darf nicht in die nächste Runde
		if (bNächsteRunde == false)
			return false;
		// Spieler darf in die nächste Runde
		else
		{
			// nächste Runde vorbereiten
			bNächsteRunde = false;
			ivorherigeRunde = iRunde;
			iRunde = 1;
			tempAusgabe.hControlButton->Content = "2. Wurf";
			return true;
		}
	}

	// aktuelle Runde inkrementieren
	ivorherigeRunde = iRunde;
	iRunde++;

	// Spieler kommt in die nächste Runde.
	return true;
}


void Verwaltung::setbNächsteRunde(bool temp, Ausgabe tempAusgabe)
{
	if (temp == true)
		tempAusgabe.hControlButton->Content = "Neue Runde";
	bNächsteRunde = temp;
}

#endif