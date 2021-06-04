//
// W�rfel.h - Yatzy by Philipp Reinke |2014|
//
#ifndef W�RFEL_H
#define W�RFEL_H

#include <random>
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Media;


class W�rfel
{
public:
	// Variablen
	int iIndexW�rfelsatz{0};
	int iDice[5];
	bool bDiceStatus[5];
	ToggleButton^ hDice[5];
	std::vector<std::tuple<std::vector<ImageBrush^>, std::vector<ImageBrush^>>> imageBrush;

	// Methoden
	W�rfel();
	int identifiziereButton(ToggleButton^);
	void dice();
	void initialisieren(ToggleButton^, ToggleButton^, ToggleButton^, ToggleButton^, ToggleButton^);
	void addW�rfelsatz(std::vector<ImageBrush^>, std::vector<ImageBrush^>);
	void reloadDice();
	void setDiceStatus(bool);
};


void W�rfel::reloadDice()
{
	// W�rfel erneut laden
	for (int i = 0; i <= 4; i++)
	{
		// Hintergrund und Border des Buttons festlegen
		if (iIndexW�rfelsatz == 2)hDice[i]->BorderBrush = ref new SolidColorBrush(Windows::UI::Colors::Transparent);
		hDice[i]->Background = std::get<0>(imageBrush.at(iIndexW�rfelsatz)).at(iDice[i] - 1);
	}
}


void W�rfel::addW�rfelsatz(std::vector<ImageBrush^> tempW�rfelsatzAktiv, std::vector<ImageBrush^> tempW�rfelsatzPassiv)
{
	imageBrush.push_back(std::make_tuple(tempW�rfelsatzAktiv, tempW�rfelsatzPassiv));
}


W�rfel::W�rfel()
{
	// Initialisierungen
	for (int i = 0; i <= 5; i++)
		bDiceStatus[i] = false;

	for (int i = 0; i <= 4; i++)
		iDice[i] = i + 1;
}


int W�rfel::identifiziereButton(ToggleButton^ tempButton)
{
	if (tempButton->Name == "dice1") return 0;
	if (tempButton->Name == "dice2") return 1;
	if (tempButton->Name == "dice3") return 2;
	if (tempButton->Name == "dice4") return 3;
	if (tempButton->Name == "dice5") return 4;
	// Fehler
	return -1;
}

void W�rfel::initialisieren(ToggleButton^ tempDice1, ToggleButton^ tempDice2,
	ToggleButton^ tempDice3, ToggleButton^ tempDice4, ToggleButton^ tempDice5)
{
	// Adresse der W�rfel zuweisen
	hDice[0] = tempDice1;
	hDice[1] = tempDice2;
	hDice[2] = tempDice3;
	hDice[3] = tempDice4;
	hDice[4] = tempDice5;
}


void W�rfel::dice()
{
	// Zufallszahl
	std::uniform_int_distribution<int> distribution(1, 6);

	// Engine erzeugen
	std::random_device generator;
	
	// w�rfeln
	for (int i = 0; i <= 4; i++)
	{
		// neue Zufallszahl generieren
		int iRnd = distribution(generator);

		// Ist der W�rfel fixiert?
		if (bDiceStatus[i] == true) continue;

		// Hintergrund und Border des Buttons festlegen
		if (iIndexW�rfelsatz == 2)hDice[i]->BorderBrush = ref new SolidColorBrush(Windows::UI::Colors::Transparent);
		hDice[i]->Background = std::get<0>(imageBrush.at(iIndexW�rfelsatz)).at(iRnd - 1);
		iDice[i] = iRnd;
	}
}

#endif

