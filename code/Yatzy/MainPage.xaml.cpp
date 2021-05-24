//
// MainPage.xaml.cpp - Yatzy by Philipp Reinke |2014|
//

#include "pch.h"
#include "MainPage.xaml.h"
#include "Einstellungen.xaml.h"
#include "Erfolge.xaml.h"
#include "Hilfe.xaml.h"
#include "Score.xaml.h"
#include "globaleDefinitionen.h"


using namespace Yatzy;

using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Graphics::Display;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Navigation;
using namespace Windows::UI::Xaml::Media::Imaging;

MainPage::MainPage()
{
	InitializeComponent();

	//
	// Begrüßung beim ersten Start
	static bool bFirstStart = true;
	std::ofstream file1, file2;

	// Pfad bestimmen und in std::string konvertieren
	String^ tempPfad = Windows::Storage::ApplicationData::Current->LocalFolder->Path;
	tempPfad += "\\data1.yatzy";
	std::string tempPfadConvert1(tempPfad->Begin(), tempPfad->End());
	tempPfad = Windows::Storage::ApplicationData::Current->LocalFolder->Path;
	tempPfad += "\\data2.yatzy";
	std::string tempPfadConvert2(tempPfad->Begin(), tempPfad->End());

	// Datei öffnen
	file1.open(tempPfadConvert1, std::ios::in);
	file2.open(tempPfadConvert2, std::ios::in);

	// Fehlerprüfung
	if (file1.fail() && file2.fail() && bFirstStart)
	{
		String^ szÜberschrirft, ^szText;
		szÜberschrirft = "Begrüßung";
		szText = "Seien Sie Willkommen! Bitte geben Sie Ihren Namen unter |Einstellungen| ";
		szText += "ein und tauchen Sie in die minimalistische Welt des Spiels Yatzuu ein, die ";
		szText += "Sie mit freischaltbaren Hintergründen und Würfeln beliebig gestalten können. ";
		szText += "Schaffen Sie es mit einer guten Strategie und etwas Glück zum Meister?";

		// Text anzeigen
		Dialog dialog;
		dialog.zeigeDialogOK(szÜberschrirft, szText);
		bFirstStart = false;
	}

	// aufräumen
	file1.close();
	file2.close();

	//
	// Initialisierung der Ausgabe
	ausgabe.initialisieren(pktEiner, pktZweier, pktDreier, pktVierer, pktFünfer,
		pktSechser, pkt3Pasch, pkt4Pasch, pktKlStraße, pktGrStraße, pktFullHouse,
		pktChance, pktYatzy, pktBonus, pktSumme, pktGesamt, controlButton);
	 
	// Pointer auf Würfel erzeugen
	würfel.initialisieren(dice1, dice2, dice3, dice4, dice5);

	// Würfelsätze speichern
	for (int i = 0; i <= 7; i++)
	{
		// Variablen
		std::vector<ImageBrush^> tempWürfelsatzAktiv;
		std::vector<ImageBrush^> tempWürfelsatzPassiv;

		switch (i)
		{
		case 0:
			// ausgewählte Würfel
			tempWürfelsatzAktiv.push_back(BrushKlassischWeiß1);
			tempWürfelsatzAktiv.push_back(BrushKlassischWeiß2);
			tempWürfelsatzAktiv.push_back(BrushKlassischWeiß3);
			tempWürfelsatzAktiv.push_back(BrushKlassischWeiß4);
			tempWürfelsatzAktiv.push_back(BrushKlassischWeiß5);
			tempWürfelsatzAktiv.push_back(BrushKlassischWeiß6);
			// fixierte Würfel
			tempWürfelsatzPassiv.push_back(BrushKlassischGrau1);
			tempWürfelsatzPassiv.push_back(BrushKlassischGrau2);
			tempWürfelsatzPassiv.push_back(BrushKlassischGrau3);
			tempWürfelsatzPassiv.push_back(BrushKlassischGrau4);
			tempWürfelsatzPassiv.push_back(BrushKlassischGrau5);
			tempWürfelsatzPassiv.push_back(BrushKlassischGrau6);
			break;
		case 1:
			// ausgewählte Würfel
			tempWürfelsatzAktiv.push_back(BrushModernWeiß1);
			tempWürfelsatzAktiv.push_back(BrushModernWeiß2);
			tempWürfelsatzAktiv.push_back(BrushModernWeiß3);
			tempWürfelsatzAktiv.push_back(BrushModernWeiß4);
			tempWürfelsatzAktiv.push_back(BrushModernWeiß5);
			tempWürfelsatzAktiv.push_back(BrushModernWeiß6);
			// fixierte Würfel
			tempWürfelsatzPassiv.push_back(BrushModernGrau1);
			tempWürfelsatzPassiv.push_back(BrushModernGrau2);
			tempWürfelsatzPassiv.push_back(BrushModernGrau3);
			tempWürfelsatzPassiv.push_back(BrushModernGrau4);
			tempWürfelsatzPassiv.push_back(BrushModernGrau5);
			tempWürfelsatzPassiv.push_back(BrushModernGrau6);
			break;
		case 2:
			// ausgewählte Würfel
			tempWürfelsatzAktiv.push_back(BrushRundWeiß1);
			tempWürfelsatzAktiv.push_back(BrushRundWeiß2);
			tempWürfelsatzAktiv.push_back(BrushRundWeiß3);
			tempWürfelsatzAktiv.push_back(BrushRundWeiß4);
			tempWürfelsatzAktiv.push_back(BrushRundWeiß5);
			tempWürfelsatzAktiv.push_back(BrushRundWeiß6);
			// fixierte Würfel
			tempWürfelsatzPassiv.push_back(BrushRundGrau1);
			tempWürfelsatzPassiv.push_back(BrushRundGrau2);
			tempWürfelsatzPassiv.push_back(BrushRundGrau3);
			tempWürfelsatzPassiv.push_back(BrushRundGrau4);
			tempWürfelsatzPassiv.push_back(BrushRundGrau5);
			tempWürfelsatzPassiv.push_back(BrushRundGrau6);
		case 3:
			// ausgewählte Würfel
			tempWürfelsatzAktiv.push_back(BrushNumerischWeiß1);
			tempWürfelsatzAktiv.push_back(BrushNumerischWeiß2);
			tempWürfelsatzAktiv.push_back(BrushNumerischWeiß3);
			tempWürfelsatzAktiv.push_back(BrushNumerischWeiß4);
			tempWürfelsatzAktiv.push_back(BrushNumerischWeiß5);
			tempWürfelsatzAktiv.push_back(BrushNumerischWeiß6);
			// fixierte Würfel
			tempWürfelsatzPassiv.push_back(BrushNumerischGrau1);
			tempWürfelsatzPassiv.push_back(BrushNumerischGrau2);
			tempWürfelsatzPassiv.push_back(BrushNumerischGrau3);
			tempWürfelsatzPassiv.push_back(BrushNumerischGrau4);
			tempWürfelsatzPassiv.push_back(BrushNumerischGrau5);
			tempWürfelsatzPassiv.push_back(BrushNumerischGrau6);
		case 4:
			// ausgewählte Würfel
			tempWürfelsatzAktiv.push_back(BrushBrailleWeiß1);
			tempWürfelsatzAktiv.push_back(BrushBrailleWeiß2);
			tempWürfelsatzAktiv.push_back(BrushBrailleWeiß3);
			tempWürfelsatzAktiv.push_back(BrushBrailleWeiß4);
			tempWürfelsatzAktiv.push_back(BrushBrailleWeiß5);
			tempWürfelsatzAktiv.push_back(BrushBrailleWeiß6);
			// fixierte Würfel
			tempWürfelsatzPassiv.push_back(BrushBrailleGrau1);
			tempWürfelsatzPassiv.push_back(BrushBrailleGrau2);
			tempWürfelsatzPassiv.push_back(BrushBrailleGrau3);
			tempWürfelsatzPassiv.push_back(BrushBrailleGrau4);
			tempWürfelsatzPassiv.push_back(BrushBrailleGrau5);
			tempWürfelsatzPassiv.push_back(BrushBrailleGrau6);
		case 5:
			// ausgewählte Würfel
			tempWürfelsatzAktiv.push_back(BrushJapanischWeiß1);
			tempWürfelsatzAktiv.push_back(BrushJapanischWeiß2);
			tempWürfelsatzAktiv.push_back(BrushJapanischWeiß3);
			tempWürfelsatzAktiv.push_back(BrushJapanischWeiß4);
			tempWürfelsatzAktiv.push_back(BrushJapanischWeiß5);
			tempWürfelsatzAktiv.push_back(BrushJapanischWeiß6);
			// fixierte Würfel
			tempWürfelsatzPassiv.push_back(BrushJapanischGrau1);
			tempWürfelsatzPassiv.push_back(BrushJapanischGrau2);
			tempWürfelsatzPassiv.push_back(BrushJapanischGrau3);
			tempWürfelsatzPassiv.push_back(BrushJapanischGrau4);
			tempWürfelsatzPassiv.push_back(BrushJapanischGrau5);
			tempWürfelsatzPassiv.push_back(BrushJapanischGrau6);
		case 6:
			// ausgewählte Würfel
			tempWürfelsatzAktiv.push_back(BrushRömischWeiß1);
			tempWürfelsatzAktiv.push_back(BrushRömischWeiß2);
			tempWürfelsatzAktiv.push_back(BrushRömischWeiß3);
			tempWürfelsatzAktiv.push_back(BrushRömischWeiß4);
			tempWürfelsatzAktiv.push_back(BrushRömischWeiß5);
			tempWürfelsatzAktiv.push_back(BrushRömischWeiß6);
			// fixierte Würfel
			tempWürfelsatzPassiv.push_back(BrushRömischGrau1);
			tempWürfelsatzPassiv.push_back(BrushRömischGrau2);
			tempWürfelsatzPassiv.push_back(BrushRömischGrau3);
			tempWürfelsatzPassiv.push_back(BrushRömischGrau4);
			tempWürfelsatzPassiv.push_back(BrushRömischGrau5);
			tempWürfelsatzPassiv.push_back(BrushRömischGrau6);
		case 7:
			// ausgewählte Würfel
			tempWürfelsatzAktiv.push_back(nullptr);
			tempWürfelsatzAktiv.push_back(nullptr);
			tempWürfelsatzAktiv.push_back(nullptr);
			tempWürfelsatzAktiv.push_back(nullptr);
			tempWürfelsatzAktiv.push_back(nullptr);
			tempWürfelsatzAktiv.push_back(nullptr);
			// fixierte Würfel
			tempWürfelsatzPassiv.push_back(nullptr);
			tempWürfelsatzPassiv.push_back(nullptr);
			tempWürfelsatzPassiv.push_back(nullptr);
			tempWürfelsatzPassiv.push_back(nullptr);
			tempWürfelsatzPassiv.push_back(nullptr);
			tempWürfelsatzPassiv.push_back(nullptr);
		default:
			// ausgewählte Würfel
			tempWürfelsatzAktiv.push_back(BrushKlassischWeiß1);
			tempWürfelsatzAktiv.push_back(BrushKlassischWeiß2);
			tempWürfelsatzAktiv.push_back(BrushKlassischWeiß3);
			tempWürfelsatzAktiv.push_back(BrushKlassischWeiß4);
			tempWürfelsatzAktiv.push_back(BrushKlassischWeiß5);
			tempWürfelsatzAktiv.push_back(BrushKlassischWeiß6);
			// fixierte Würfel
			tempWürfelsatzPassiv.push_back(BrushKlassischGrau1);
			tempWürfelsatzPassiv.push_back(BrushKlassischGrau2);
			tempWürfelsatzPassiv.push_back(BrushKlassischGrau3);
			tempWürfelsatzPassiv.push_back(BrushKlassischGrau4);
			tempWürfelsatzPassiv.push_back(BrushKlassischGrau5);
			tempWürfelsatzPassiv.push_back(BrushKlassischGrau6);
		}

		// temporären Würfelsatz speichern
		würfel.addWürfelsatz(tempWürfelsatzAktiv, tempWürfelsatzPassiv);
	}

	// Daten der Verwaltung aus data2.yatzy laden
	verwaltung.refreshData();

	// Hintergrundfarbe anpassen
	MainPage::Background = verwaltung.getBrushBackground();

	// Initialisierung der Verwaltung
	std::vector<TextBlock^> vectorTextBlock;
	TextBlock^ tempTextBlock;
	for (int i = 0; i <= 15; i++)
	{
		switch (i)
		{
		case 0: tempTextBlock = pktEinerText; break;
		case 1: tempTextBlock = pktZweierText; break;
		case 2: tempTextBlock = pktDreierText; break;
		case 3: tempTextBlock = pktViererText; break;
		case 4: tempTextBlock = pktFünferText; break;
		case 5: tempTextBlock = pktSechserText; break;
		case 6: tempTextBlock = pktBonusText; break;
		case 7: tempTextBlock = pktSummeText; break;
		case 8: tempTextBlock = pkt3PaschText; break;
		case 9: tempTextBlock = pkt4PaschText; break;
		case 10: tempTextBlock = pktKlStraßeText; break;
		case 11: tempTextBlock = pktGrStraßeText; break;
		case 12: tempTextBlock = pktFullHouseText; break;
		case 13: tempTextBlock = pktChanceText; break;
		case 14: tempTextBlock = ptkYatzyText; break;
		case 15: tempTextBlock = pktGesamtText; break;
		}
		
		vectorTextBlock.push_back(tempTextBlock);
	}
	verwaltung.intialisieren(vectorTextBlock, Window::Current->Bounds.Width / 400.0f);

	// Elemente skalieren
	verwaltung.skalieren(ausgabe, würfel);

	// Farbe der potentiellen Punkte anpassen
	for (int i = 0; i <= 12; i++)
		if (ausgabe.bPktStatus[i] == false)
			ausgabe.updateFarbePotPkt(ausgabe.hToggleButton[i], verwaltung.getBackgroundIndex());

	// Index des Würfelsatzes an Würfel weitergeben
	würfel.iIndexWürfelsatz = verwaltung.getWürfelStyleIndex();
}


void MainPage::OnNavigatedTo(NavigationEventArgs^ e)
{
	// Daten der Verwaltung erneut aus data2.yatzy laden
	verwaltung.refreshData();

	// Text des Hauptbuttons setzen
	verwaltung.setTextControlButton(ausgabe);

	// Daten nach Seitenwechsel laden
	// gespeicherte Punkte eintragen
	for (int i = 0; i <= 12; i++)
	{
		// potenzielle Punkte ausgeben
		punkte.ausgabePkt(ausgabe, verwaltung);

		// gespeicherte Punkte ausgeben
		if (ausgabe.bPktStatus[i] == true)
		{
			// sichere Punkte ausgeben
			ausgabe.hToggleButton[i]->Content = punkte.iSicherePkt[i];
			if (ausgabe.hToggleButton[i] != punkte.hSelectedPkt) ausgabe.hToggleButton[i]->IsEnabled = false;
			// ausgewählte Punkte weiß
			else punkte.hSelectedPkt->Foreground = ref new SolidColorBrush(Windows::UI::Colors::White);
		}
	}

	// Würfel erneut laden
	for (int i = 0; i <= 4; i++)
	{
		// Hintergrund und Border des Buttons festlegen
		if (würfel.iIndexWürfelsatz == 2)würfel.hDice[i]->BorderBrush = ref new SolidColorBrush(Windows::UI::Colors::Transparent);
		würfel.hDice[i]->Background = std::get<0>(würfel.imageBrush.at(würfel.iIndexWürfelsatz)).at(würfel.iDice[i] - 1);
		// Staus des Würfels anpassen
		if (würfel.bDiceStatus[i] == true)
		{
			würfel.bDiceStatus[i] = false;
			dice_Click(würfel.hDice[i], nullptr);
		}
	}
}


void Yatzy::MainPage::controlButton_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	// erste Runde -> Punkte zurücksetzen
	static bool bFirstRound = false;
	if (bFirstRound == false)
	{
		AppBarButtonNeustart_Click(nullptr, nullptr);
		bFirstRound = true;
		return;
	}
	
	// Ende des Spiels erreicht?
	if (verwaltung.endOfGame(ausgabe) == true)
	{
		// Berechnung und Ausgabe des temporären Punktestandes
		punkte.berechnePkt(ausgabe, würfel, verwaltung);

		// Würfel zurücksetzen
		for (int i = 0; i <= 4; i++)
			if (würfel.bDiceStatus[i] == true)
				dice_Click(würfel.hDice[i], nullptr);

		// Punkte speichern
		speicher.sicherePunkte(punkte, verwaltung);

		// Dialog anzeigen
		String^ ausgabeDialog("Sie haben ");
		ausgabeDialog += punkte.iSicherePkt[15];
		ausgabeDialog += " Punkte erreicht.";
		dialog.zeigeDialogOK("Herzlichen Glückwunsch!", ausgabeDialog);

		// Ausgabe und Punkte zurücksetzen
		ausgabe.reset(verwaltung.getBackgroundIndex());
		punkte.resetSicherePkt();
		punkte.resetTempPkt();

		// neue Runde starten
		controlButton_Click(nullptr, nullptr);

		return;
	}

	// Verwaltung
	if (!verwaltung.nächsteRunde(ausgabe, würfel))
		return;

	// wenn erste Runde, dann Würfel freigeben
	if (verwaltung.getRunde() == 0 || verwaltung.getRunde() == 1)
	{
		for (int i = 0; i <= 4; i++){
			if (würfel.bDiceStatus[i] == true)
				dice_Click(würfel.hDice[i], nullptr);
		}
	}

	// ausgewählte Punkte deaktivieren
	if (punkte.hSelectedPkt != nullptr)
		punkte.hSelectedPkt->IsEnabled = false;

	// würfeln
	würfel.dice();

	// temporären Punktestand zurücksetzen
	punkte.resetTempPkt();

	// Berechnung und Ausgabe des temporären Punktestandes
	punkte.berechnePkt(ausgabe, würfel, verwaltung);
}


void Yatzy::MainPage::pkt_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	// Sender in ToggleButton konvertieren
	ToggleButton^ tempToggleButton = safe_cast<ToggleButton^>(sender);

	// Button ist immer unchecked
	tempToggleButton->IsChecked = false;

	// Punktestand wird gesichert
	if (ausgabe.bPktStatus[ausgabe.identifiziereButton(tempToggleButton)] == false)
	{
		// anderen ausgewählten Button freigeben
		if (punkte.hSelectedPkt != nullptr)
			pkt_Click(punkte.hSelectedPkt, nullptr);

		// Buttonhandle und Index speichern
		punkte.hSelectedPkt = tempToggleButton;

		// ControlButton aktivieren
		if( verwaltung.getRunde() == 3) ausgabe.hControlButton->IsEnabled = true;

		// nächste Runde wird gewährt
		verwaltung.setbNächsteRunde(true, ausgabe);

		// Button ist fixiert
		ausgabe.bPktStatus[ausgabe.identifiziereButton(tempToggleButton)] = true;

		// Design anpassen
		tempToggleButton->Foreground = ref new SolidColorBrush(Windows::UI::Colors::White);

		// trage 0 ein, falls kein Wert eingetragen
		if (punkte.iTempPkt[ausgabe.identifiziereButton(tempToggleButton)] == 0) tempToggleButton->Content = "0";

		// wenn Vorschau aus -> Wert eintragen
		if (verwaltung.getVorschau() == false) tempToggleButton->Content = punkte.iTempPkt[ausgabe.identifiziereButton(tempToggleButton)];

		// temporäre Punkte sichern
		punkte.iSicherePkt[ausgabe.identifiziereButton(tempToggleButton)] = punkte.iTempPkt[ausgabe.identifiziereButton(tempToggleButton)];
	}

	// Punktestannd wird entsichert
	else
	{
		// Text des Hauptbuttons setzen
		verwaltung.setTextControlButton(ausgabe);

		// wenn Vorschau aus -> Wert löschen
		if (verwaltung.getVorschau() == false) tempToggleButton->Content = "";

		// Buttonhandle und Index freigeben
		punkte.hSelectedPkt = nullptr;

		// ControlButton deaktivieren
		if (verwaltung.getRunde() == 3) ausgabe.hControlButton->IsEnabled = false;

		// nächste Runde wird verwehrt
		verwaltung.setbNächsteRunde(false, ausgabe);

		// Button freigeben
		ausgabe.bPktStatus[ausgabe.identifiziereButton(tempToggleButton)] = false;

		// Design anpassen
		ausgabe.updateFarbePotPkt(tempToggleButton, verwaltung.getBackgroundIndex());

		// lösche Eintrag, falls 0 Punkte angezeigt werden
		if (punkte.iTempPkt[ausgabe.identifiziereButton(tempToggleButton)] == 0) tempToggleButton->Content = "";

		// gesicherte Punkte löschen
		punkte.iSicherePkt[ausgabe.identifiziereButton(tempToggleButton)] = 0;
	}
}


void Yatzy::MainPage::dice_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	// sender in ToggleButton konvertieren
	ToggleButton^ tempToggleButton = safe_cast<ToggleButton^>(sender);

	// Button ist immer unchecked
	tempToggleButton->IsChecked = false;

	// Index des Würfels bestimmen
	int iTempIndex = würfel.identifiziereButton(tempToggleButton);

	// Design des Buttons an Modus anpassen
	if (würfel.bDiceStatus[iTempIndex] == false){
		würfel.hDice[iTempIndex]->Background = std::get<1>(würfel.imageBrush.at(würfel.iIndexWürfelsatz)).at(würfel.iDice[iTempIndex] - 1);
		würfel.bDiceStatus[iTempIndex] = true;
		if (würfel.iIndexWürfelsatz != 2)tempToggleButton->BorderBrush = ref new SolidColorBrush(Windows::UI::ColorHelper::FromArgb(50, 255, 255, 255));
		else tempToggleButton->BorderBrush = ref new SolidColorBrush(Windows::UI::Colors::Transparent);
	}
	else{
		würfel.hDice[iTempIndex]->Background = std::get<0>(würfel.imageBrush.at(würfel.iIndexWürfelsatz)).at(würfel.iDice[iTempIndex] - 1);
		würfel.bDiceStatus[iTempIndex] = false;
		if (würfel.iIndexWürfelsatz != 2)tempToggleButton->BorderBrush = ref new SolidColorBrush(Windows::UI::Colors::White);
		else tempToggleButton->BorderBrush = ref new SolidColorBrush(Windows::UI::Colors::Transparent);
	}
}


void Yatzy::MainPage::AppBarButtonEinstellungen_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	// Wechsel vorbereiten
	if (punkte.hSelectedPkt != nullptr)
		controlButton_Click(nullptr, nullptr);

	this->Frame->Navigate(Einstellungen::typeid, this);
}


void Yatzy::MainPage::AppBarButtonPunkte_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	// Wechsel vorbereiten
	if (punkte.hSelectedPkt != nullptr)
		controlButton_Click(nullptr, nullptr);

	this->Frame->Navigate(Score::typeid, this);
}


void Yatzy::MainPage::AppBarButtonHilfe_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	// Wechsel vorbereiten
	if (punkte.hSelectedPkt != nullptr)
		controlButton_Click(nullptr, nullptr);

	this->Frame->Navigate(Hilfe::typeid, this);
}


void Yatzy::MainPage::AppBarButtonErfolge_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	// Wechsel vorbereiten
	if (punkte.hSelectedPkt != nullptr)
		controlButton_Click(nullptr, nullptr);

	this->Frame->Navigate(Erfolge::typeid, this);
}


void Yatzy::MainPage::AppBarButtonNeustart_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	// aktuelles Spiel zurücksetzen
	// Würfel zurücksetzen
	for (int i = 0; i <= 4; i++)
		if (würfel.bDiceStatus[i] == true)
			dice_Click(würfel.hDice[i], nullptr);

	// Ausgabe und Punkte zurücksetzen
	ausgabe.reset(verwaltung.getBackgroundIndex());
	punkte.resetSicherePkt();
	punkte.resetTempPkt();

	// Text des Hauptbuttons setzen
	ausgabe.hControlButton->Content = "2. Wurf";
	ausgabe.hControlButton->IsEnabled = true;

	// Rundenanzahl zurücksetzen
	verwaltung.setRunde(1);

	// Würfeln
	würfel.dice();

	// Punkte berechnen und anzeigen
	punkte.berechnePkt(ausgabe, würfel, verwaltung);
}