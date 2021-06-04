//
// App.xaml.cpp
// Implementierung der App-Klasse
//

#include "pch.h"
#include "MainPage.xaml.h"

using namespace Yatzy;

using namespace Platform;
using namespace Windows::ApplicationModel;
using namespace Windows::ApplicationModel::Activation;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Interop;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Media::Animation;
using namespace Windows::UI::Xaml::Navigation;

// Die Vorlage "Leere Anwendung" ist unter http://go.microsoft.com/fwlink/?LinkID=391641 dokumentiert.

/// <summary>
/// Initialisiert das Singletonanwendungsobjekt.  Dies ist die erste ausgeführte Zeile von erstelltem Code
/// und daher das logische Äquivalent von main() bzw. WinMain().
/// </summary>
App::App()
{
	InitializeComponent();
	Suspending += ref new SuspendingEventHandler(this, &App::OnSuspending);
}

/// <summary>
/// Wird aufgerufen, wenn die Anwendung durch den Endbenutzer normal gestartet wird. Weitere Einstiegspunkte
/// werden verwendet, wenn die Anwendung zum Öffnen einer bestimmten Datei, zum Anzeigen
/// von Suchergebnissen usw. gestartet wird.
/// </summary>
/// <param name="e">Details über Startanforderung und -prozess.</param>
void App::OnLaunched(LaunchActivatedEventArgs^ e)
{
#if _DEBUG
	if (IsDebuggerPresent())
	{
		DebugSettings->EnableFrameRateCounter = true;
	}
#endif

	auto rootFrame = dynamic_cast<Frame^>(Window::Current->Content);

	// App-Initialisierung nicht wiederholen, wenn das Fenster bereits Inhalte enthält.
	// Nur sicherstellen, dass das Fenster aktiv ist.
	if (rootFrame == nullptr)
	{
		// Einen Rahmen erstellen, der als Navigationskontext fungiert, und ihn mit
		// einem SuspensionManager-Schlüssel verknüpfen
		rootFrame = ref new Frame();

		// TODO: diesen Wert auf eine Cachegröße ändern, die für Ihre Anwendung geeignet ist
		rootFrame->CacheSize = 1;

		if (e->PreviousExecutionState == ApplicationExecutionState::Terminated)
		{
			// TODO: Den gespeicherten Sitzungszustand nur bei Bedarf wiederherstellen. Dabei die
			// abschließenden Schritte zum Start planen, nachdem die Wiederherstellung abgeschlossen ist.
		}

		// Den Rahmen im aktuellen Fenster platzieren
		Window::Current->Content = rootFrame;
	}

	if (rootFrame->Content == nullptr)
	{
		// Entfernt die Drehkreuznavigation für den Start.
		if (rootFrame->ContentTransitions != nullptr)
		{
			_transitions = ref new TransitionCollection();
			for (auto transition : rootFrame->ContentTransitions)
			{
				_transitions->Append(transition);
			}
		}

		rootFrame->ContentTransitions = nullptr;
		_firstNavigatedToken = rootFrame->Navigated += ref new NavigatedEventHandler(this, &App::RootFrame_FirstNavigated);

		// Wenn der Navigationsstapel nicht wiederhergestellt wird, zur ersten Seite navigieren
		// und die neue Seite konfigurieren, indem die erforderlichen Informationen als Navigationsparameter
		// Parameter.
		if (!rootFrame->Navigate(MainPage::typeid, e->Arguments))
		{
			throw ref new FailureException("Failed to create initial page");
		}
	}

	// Sicherstellen, dass das aktuelle Fenster aktiv ist
	Window::Current->Activate();
}

/// <summary>
/// Stellt die Inhaltsübergänge nach dem Start der App wieder her.
/// </summary>
void App::RootFrame_FirstNavigated(Object^ sender, NavigationEventArgs^ e)
{
	auto rootFrame = safe_cast<Frame^>(sender);

	TransitionCollection^ newTransitions;
	if (_transitions == nullptr)
	{
		newTransitions = ref new TransitionCollection();
		newTransitions->Append(ref new NavigationThemeTransition());
	}
	else
	{
		newTransitions = _transitions;
	}

	rootFrame->ContentTransitions = newTransitions;
	rootFrame->Navigated -= _firstNavigatedToken;
}

/// <summary>
/// Wird aufgerufen, wenn die Ausführung der Anwendung angehalten wird. Der Anwendungszustand wird gespeichert,
/// ohne zu wissen, ob die Anwendung beendet oder fortgesetzt wird und die Speicherinhalte dabei
/// unbeschädigt bleiben.
/// </summary>
void App::OnSuspending(Object^ sender, SuspendingEventArgs^ e)
{
	(void) sender;	// Nicht verwendeter Parameter
	(void) e;		// Nicht verwendeter Parameter

	// TODO: Anwendungszustand speichern und alle Hintergrundaktivitäten beenden
}