// engine_test.cpp by Philipp Reinke |2014|
#include <iostream>
#include <random>

// Engine erzeugen
std::random_device generator;


int main()
{
	// Variablen
	std::uniform_int_distribution<int> distribution(1, 6);
	std::vector<int> vec(6);
	float x, iGesamt{0.0f};

	// Vektor initialisieren
	for (auto puffer : vec)
		puffer = 0;

	// Zweck definieren
	std::cout << "Dieses Programm dient der Feststellung der Haeufigkeits- " << std::endl;
	std::cout << "verteilung der Engine \"random_device\". Dafuer " << std::endl;
	std::cout << "wird eine Menge zufaelliger Werte zwischen 1 und 6 mit " << std::endl;
	std::cout << "x Elementen erzeugt, um die Verteilung empirisch zu ermitteln.\n" << std::endl;
	std::cout << "Bitte geben Sie x ein: ";
	std::cin >>  x;
	std::cout << "\nStatus:    ";

	// Zufallszahlen erzeugen
	for (int i = 0; i <= x; i++)
	{
		int iOldStatus{ 0 };

		// neue Zufallszahl generieren und Zähler inkrementieren
		int iRnd = distribution(generator);
		vec.at(iRnd - 1)+=1;
		iGesamt++;

		// Status ausgeben
		if (static_cast<int>(iGesamt / x) == iOldStatus) continue;
		else if (iGesamt / x <= 0.1f) std::cout << "\b\b" << static_cast<int>(iGesamt / x * 100.0f) << "%";
		else if (iGesamt / x <= 1.0f) std::cout << "\b\b\b" << static_cast<int>(iGesamt / x * 100.0f) << "%";

		// alten Status speichern
		iOldStatus = static_cast<int>(iGesamt / x);
	}

	// Leerzeilen ausgeben
	std::cout << "\n\n";

	// Auswertung
	for (int i = 0; i <= 5; i++)
		std::cout << i + 1 << " - " << static_cast<int>(vec.at(i) / iGesamt * 100.0f) << " %" << std::endl;
	std::cout << "\n";
	system("pause");
}