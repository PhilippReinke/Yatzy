//
// Speicherverwaltung.h - Yatzy by Philipp Reinke |2014|
//
#ifndef SPEICHERVERWALTUNG_H
#define SPEICHERVERWALTUNG_H

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
using namespace Platform;

class Speicherverwaltung
{
public:
	// Variablen
	String^ szText;
	
	// Methoden
	bool l�schePunkte();
	bool sicherePunkte(Punkte, Verwaltung);
	String^ getPunkte(){ return szText; }
};


bool Speicherverwaltung::l�schePunkte()
{
	std::ofstream file;

	// Pfad bestimmen und in std::string konvertieren
	String^ tempPfad = Windows::Storage::ApplicationData::Current->LocalFolder->Path;
	tempPfad += "\\data1.yatzy";
	std::string tempPfadConvert(tempPfad->Begin(), tempPfad->End());

	// Datei �ffnen und l�schen
	file.open(tempPfadConvert, std::ios::trunc);

	// Fehlerpr�fung
	if (file.fail() == true)
		return false;
	return true;

	// aufr�umen
	file.close();
}


bool Speicherverwaltung::sicherePunkte(Punkte tempPkt, Verwaltung tempVerwaltung)
{
	std::ofstream file;

	// Pfad bestimmen und in std::string konvertieren
	String^ tempPfad = Windows::Storage::ApplicationData::Current->LocalFolder->Path;
	tempPfad += "\\data1.yatzy";
	std::string tempPfadConvert(tempPfad->Begin(), tempPfad->End());

	file.open(tempPfadConvert, std::ios::out | std::ios::app);
	file << tempVerwaltung.getName() << "\n" << tempPkt.iSicherePkt[15] << "\n";
	file.close();

	// Fehlerpr�fung
	if (file.fail() == true)
		return false;
	return true;
}

#endif