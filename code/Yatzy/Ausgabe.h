//
// Ausgabe.h - Yatzy by Philipp Reinke |2014|
//
#ifndef AUSGABE_H
#define AUSGABE_H

using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Controls;

class Ausgabe
{
public:
	// Variablen
	bool bPktStatus[13];
	Button^ hControlButton;
	ToggleButton^ hToggleButton[13];
	TextBlock^ hTextBlock[3];

	// Methoden
	Ausgabe();
	void initialisieren(ToggleButton^, ToggleButton^, ToggleButton^, ToggleButton^, ToggleButton^,
		ToggleButton^, ToggleButton^, ToggleButton^, ToggleButton^, ToggleButton^,
		ToggleButton^, ToggleButton^, ToggleButton^, TextBlock^, TextBlock^, TextBlock^, Button^);
	void updateFarbePotPkt(ToggleButton^, int);
	int identifiziereButton(ToggleButton^);
	void reset(int);
};


void Ausgabe::updateFarbePotPkt(ToggleButton^ tempToggleButton, int iBackgroundIndex)
{
	switch (iBackgroundIndex)
	{
	// hellrot
	case 4:
		tempToggleButton->Foreground = ref new SolidColorBrush(Windows::UI::ColorHelper::FromArgb(255, 78, 5, 5));
		break;
	// hellgrün
	case 6:
		tempToggleButton->Foreground = ref new SolidColorBrush(Windows::UI::ColorHelper::FromArgb(255, 5, 78, 27));
		break;
	// gelb
	case 7:
		tempToggleButton->Foreground = ref new SolidColorBrush(Windows::UI::Colors::Gray);
		break;
	// hellbraun
	case 9:
		tempToggleButton->Foreground = ref new SolidColorBrush(Windows::UI::ColorHelper::FromArgb(255, 124, 76, 35));
		break;
	// türkis
	case 10:
		tempToggleButton->Foreground = ref new SolidColorBrush(Windows::UI::ColorHelper::FromArgb(255, 63, 63, 63));
		break;
	// grau (hell)
	case 13:
		tempToggleButton->Foreground = ref new SolidColorBrush(Windows::UI::ColorHelper::FromArgb(255, 98, 98, 98));
		break;
	// lila (hell)
	case 14:
		tempToggleButton->Foreground = ref new SolidColorBrush(Windows::UI::ColorHelper::FromArgb(255, 102, 64, 94));
		break;
	// orange (hell/dunkel)
	case 16:
	case 17:
		tempToggleButton->Foreground = ref new SolidColorBrush(Windows::UI::ColorHelper::FromArgb(255, 210, 60, 60));
		break;
	// rosa
	case 18:
		tempToggleButton->Foreground = ref new SolidColorBrush(Windows::UI::ColorHelper::FromArgb(255, 186, 62, 62));
		break;
	default:
		tempToggleButton->Foreground = ref new SolidColorBrush(Windows::UI::Colors::LightCoral);
		break;
	}
}


void Ausgabe::reset(int iBackgroundIndex)
{
	// Punkte zurücksetzen
	for (int i = 0; i <= 12; i++)
	{
		bPktStatus[i] = false;
		hToggleButton[i]->Content = "";
		hToggleButton[i]->IsEnabled = true;
		updateFarbePotPkt(hToggleButton[i], iBackgroundIndex);
	}

	// Summe, Bonus und Ausgabe zurücksetzen
	for (int i = 0; i <= 2; i++)
		hTextBlock[i]->Text = "0";
}


Ausgabe::Ausgabe()
{
	for (int i = 0; i <= 12; i++)
		bPktStatus[i] = false;
}


int Ausgabe::identifiziereButton(ToggleButton^ tempButton)
{
	if (tempButton->Name == "pktEiner")		return 0;
	if (tempButton->Name == "pktZweier")	return 1;
	if (tempButton->Name == "pktDreier")	return 2;
	if (tempButton->Name == "pktVierer")	return 3;
	if (tempButton->Name == "pktFünfer")	return 4;
	if (tempButton->Name == "pktSechser")	return 5;
	if (tempButton->Name == "pkt3Pasch")	return 6;
	if (tempButton->Name == "pkt4Pasch")	return 7;
	if (tempButton->Name == "pktKlStraße")	return 8;
	if (tempButton->Name == "pktGrStraße")	return 9;
	if (tempButton->Name == "pktFullHouse")	return 10;
	if (tempButton->Name == "pktChance")	return 11;
	if (tempButton->Name == "pktYatzy")		return 12;
	// Fehler
	return -1;
}


void Ausgabe::initialisieren(ToggleButton^ einer, ToggleButton^ zweier, ToggleButton^ dreier,
	ToggleButton^ vierer, ToggleButton^ fünfer, ToggleButton^ sechser,
	ToggleButton^ pasch3, ToggleButton^ pasch4, ToggleButton^ klStraße,
	ToggleButton^ grStraße, ToggleButton^ fullHouse, ToggleButton^ chance,
	ToggleButton^ yatzy, TextBlock^ bonus, TextBlock^ summe, TextBlock^ gesamt,
	Button^ controlButton)
{
	hToggleButton[0] = einer;
	hToggleButton[1] = zweier;
	hToggleButton[2] = dreier;
	hToggleButton[3] = vierer;
	hToggleButton[4] = fünfer;
	hToggleButton[5] = sechser;
	hToggleButton[6] = pasch3;
	hToggleButton[7] = pasch4;
	hToggleButton[8] = klStraße;
	hToggleButton[9] = grStraße;
	hToggleButton[10] = fullHouse;
	hToggleButton[11] = chance;
	hToggleButton[12] = yatzy;
	hTextBlock[0] = bonus;
	hTextBlock[1] = summe;
	hTextBlock[2] = gesamt;
	hControlButton = controlButton;
}

#endif