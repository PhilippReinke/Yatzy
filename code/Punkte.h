//
// Punkte.h - Yatzy by Philipp Reinke |2014|
//
#ifndef PUNKTE_H
#define PUNKTE_H
#include <Verwaltung.h>

using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Media;

class Punkte
{
public:
// Variablen
	int iTempPkt[13];
	int iSicherePkt[16];
	ToggleButton^ hSelectedPkt{};

// Methoden
	Punkte();
	void resetTempPkt();
	void berechnePkt(Ausgabe, Würfel, Verwaltung);
	void ausgabePkt(Ausgabe, Verwaltung);
	void resetSicherePkt();
};


void Punkte::resetSicherePkt()
{
	for (int i = 0; i <= 15; i++)
		iSicherePkt[i] = 0;

	// ausgewählten Button zurücksetzen
	hSelectedPkt = nullptr;
}


Punkte::Punkte()
{
	for (int i = 0; i <= 15; i++)
		iSicherePkt[i] = 0;

	for (int i = 0; i <= 12; i++)
		iTempPkt[i] = 0;
}


void Punkte::berechnePkt(Ausgabe tempAusgabe, Würfel tempWürfel, Verwaltung tempVerwaltung)
{ 
	// Berechnung
	for (int i = 0; i <= 4; i++)
	{
		// Chance
		iTempPkt[11] += tempWürfel.iDice[i];

		// Einer
		if (tempWürfel.iDice[i] == 1)
			iTempPkt[0] += 1;

		// Zweier
		else if (tempWürfel.iDice[i] == 2)
			iTempPkt[1] += 2;

		// Dreier
		else if (tempWürfel.iDice[i] == 3)
			iTempPkt[2] += 3;

		// Vierer
		else if (tempWürfel.iDice[i] == 4)
			iTempPkt[3] += 4;

		// Fünfer
		else if (tempWürfel.iDice[i] == 5)
			iTempPkt[4] += 5;

		// Sechser
		else if (tempWürfel.iDice[i] == 6)
			iTempPkt[5] += 6;
	}

	// 3er-Pasch
	if (iTempPkt[5] >= 18 || iTempPkt[4] >= 15 || iTempPkt[3] >= 12 || iTempPkt[2] >= 9 || iTempPkt[1] >= 6 || iTempPkt[0] >= 3)
		iTempPkt[6] = iTempPkt[5] + iTempPkt[4] + iTempPkt[3] + iTempPkt[2] + iTempPkt[1] + iTempPkt[0];

	// 4er-Pasch
	if (iTempPkt[5] >= 24 || iTempPkt[4] >= 20 || iTempPkt[3] >= 16 || iTempPkt[2] >= 12 || iTempPkt[1] >= 8 || iTempPkt[0] >= 4)
		iTempPkt[7] = iTempPkt[5] + iTempPkt[4] + iTempPkt[3] + iTempPkt[2] + iTempPkt[1] + iTempPkt[0];

	// kleine Straße
	if (iTempPkt[2] >= 3 && iTempPkt[3] >= 4 && ((iTempPkt[0] >= 1 && iTempPkt[1] >= 2) || (iTempPkt[1] >= 2 && iTempPkt[4] >= 5) || (iTempPkt[4] >= 5 && iTempPkt[5] >= 6)))
		iTempPkt[8] = 30;

	// große Straße
	if (iTempPkt[1] == 2 && iTempPkt[2] == 3 && iTempPkt[3] == 4 && iTempPkt[4] == 5 && ((iTempPkt[0] == 1 || iTempPkt[5] == 6)))
		iTempPkt[9] = 40;

	// Full house
	if (iTempPkt[6] != 0 && (iTempPkt[0] == 2 || iTempPkt[1] == 4 || iTempPkt[2] == 6 || iTempPkt[3] == 8 || iTempPkt[4] == 10 || iTempPkt[5] == 12))
		iTempPkt[10] = 25;

	// Yatzy
	if (iTempPkt[0] == 5 || iTempPkt[1] == 10 || iTempPkt[2] == 15 || iTempPkt[3] == 20 || iTempPkt[4] == 25 || iTempPkt[5] == 30)
		iTempPkt[12] = 50;

	// Summe, Bonus und Gesamt zurücksetzen
	for (int i = 0; i <= 3; i++)
		iSicherePkt[i + 13] = 0;

	// Summe
	for (int i = 0; i <= 5; i++)
		iSicherePkt[14] += iSicherePkt[i];

	// Bonus
	if (iSicherePkt[14] >= 63)
	{
		iSicherePkt[13] = 35;
		iSicherePkt[14] += 35;
	}

	// Gesamt
	for (int i = 0; i <= 14; i++)
		iSicherePkt[15] += iSicherePkt[i];
	iSicherePkt[15] -= iSicherePkt[14];

	// Ausgabe
	ausgabePkt(tempAusgabe, tempVerwaltung);
}


void Punkte::ausgabePkt(Ausgabe tempAusgabe, Verwaltung tempVerwaltung)
{
	// Ausgabe
	for (int i = 0; i <= 12; i++)
	{
		if (tempAusgabe.bPktStatus[i] == true)
			continue;
		else if (iTempPkt[i] != 0 && tempVerwaltung.getVorschau())
			tempAusgabe.hToggleButton[i]->Content = iTempPkt[i];
		else
			tempAusgabe.hToggleButton[i]->Content = "";
	}

	// Ausgabe Summe, Bonus, Gesamt
	for (int i = 0; i <= 2; i++)
		tempAusgabe.hTextBlock[i]->Text = iSicherePkt[i + 13].ToString();
}


void Punkte::resetTempPkt()
{
	// temporäre Punkte zurücksetzen
	for (int i = 0; i <= 12; i++)
		iTempPkt[i] = 0;
}

#endif