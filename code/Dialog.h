//
// Dialog.h - Yatzy by Philipp Reinke |2014|
//
#ifndef DIALOG_H
#define DIALOG_H

using namespace Windows::UI::Popups;
using namespace Windows::UI::Xaml;
using namespace Platform;

class Dialog
{
public:
	void zeigeDialogOK(String^, String^);
};


void Dialog::zeigeDialogOK(String^ tempTitle, String^ tempContent)
{
	// erzeuge Dialog und setze den Inhalt
	MessageDialog^ msg = ref new MessageDialog(tempContent);
	msg->Title = tempTitle;

	// zeige den Dialog
	msg->ShowAsync();
}

#endif