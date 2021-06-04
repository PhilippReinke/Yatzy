//
// Würfel.h - Yatzy by Philipp Reinke |2014|
//
#ifndef WÜRFEL_H
#define WÜRFEL_H

#include <random>
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Media;


class Würfel
{
public:
	// Variablen
	int iIndexWürfelsatz{0};
	int iDice[5];
	bool bDiceStatus[5];
	ToggleButton^ hDice[5];
	std::vector<std::tuple<std::vector<ImageBrush^>, std::vector<ImageBrush^>>> imageBrush;

	// Methoden
	Würfel();
	int identifiziereButton(ToggleButton^);
	void dice();
	void initialisieren(ToggleButton^, ToggleButton^, ToggleButton^, ToggleButton^, ToggleButton^);
	void addWürfelsatz(std::vector<ImageBrush^>, std::vector<ImageBrush^>);
	void reloadDice();
	void setDiceStatus(bool);
};


void Würfel::reloadDice()
{
	// Würfel erneut laden
	for (int i = 0; i <= 4; i++)
	{
		// Hintergrund und Border des Buttons festlegen
		if (iIndexWürfelsatz == 2)hDice[i]->BorderBrush = ref new SolidColorBrush(Windows::UI::Colors::Transparent);
		hDice[i]->Background = std::get<0>(imageBrush.at(iIndexWürfelsatz)).at(iDice[i] - 1);
	}
}


void Würfel::addWürfelsatz(std::vector<ImageBrush^> tempWürfelsatzAktiv, std::vector<ImageBrush^> tempWürfelsatzPassiv)
{
	imageBrush.push_back(std::make_tuple(tempWürfelsatzAktiv, tempWürfelsatzPassiv));
}


Würfel::Würfel()
{
	// Initialisierungen
	for (int i = 0; i <= 5; i++)
		bDiceStatus[i] = false;

	for (int i = 0; i <= 4; i++)
		iDice[i] = i + 1;
}


int Würfel::identifiziereButton(ToggleButton^ tempButton)
{
	if (tempButton->Name == "dice1") return 0;
	if (tempButton->Name == "dice2") return 1;
	if (tempButton->Name == "dice3") return 2;
	if (tempButton->Name == "dice4") return 3;
	if (tempButton->Name == "dice5") return 4;
	// Fehler
	return -1;
}

void Würfel::initialisieren(ToggleButton^ tempDice1, ToggleButton^ tempDice2,
	ToggleButton^ tempDice3, ToggleButton^ tempDice4, ToggleButton^ tempDice5)
{
	// Adresse der Würfel zuweisen
	hDice[0] = tempDice1;
	hDice[1] = tempDice2;
	hDice[2] = tempDice3;
	hDice[3] = tempDice4;
	hDice[4] = tempDice5;
}


void Würfel::dice()
{
	// Zufallszahl
	std::uniform_int_distribution<int> distribution(1, 6);

	// Engine erzeugen
	std::random_device generator;
	
	// würfeln
	for (int i = 0; i <= 4; i++)
	{
		// neue Zufallszahl generieren
		int iRnd = distribution(generator);

		// Ist der Würfel fixiert?
		if (bDiceStatus[i] == true) continue;

		// Hintergrund und Border des Buttons festlegen
		if (iIndexWürfelsatz == 2)hDice[i]->BorderBrush = ref new SolidColorBrush(Windows::UI::Colors::Transparent);
		hDice[i]->Background = std::get<0>(imageBrush.at(iIndexWürfelsatz)).at(iRnd - 1);
		iDice[i] = iRnd;
	}
}

#endif

