//
// RelayCommand.cpp
// Implementierung des RelayCommand und verknüpfter Klassen
//

#include "pch.h"
#include "RelayCommand.h"
#include "NavigationHelper.h"

using namespace Yatzy::Common;

using namespace Platform;
using namespace Platform::Collections;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::System;
using namespace Windows::UI::Core;
using namespace Windows::UI::ViewManagement;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Navigation;

/// <summary>
/// Legt fest, ob dieser <see cref="RelayCommand"/> im aktuellen Zustand ausgeführt werden kann.
/// </summary>
/// <param name="parameter">
/// Die vom Befehl verwendeten Daten. Wenn für den Befehl keine Datenübergabe erforderlich ist, kann dieses Objekt auf NULL festgelegt werden.
/// </param>
/// <returns>True, wenn dieser Befehl ausgeführt werden kann, andernfalls False.</returns>
bool RelayCommand::CanExecute(Object^ parameter)
{
	return (_canExecuteCallback) (parameter);
}

/// <summary>
/// Führt den <see cref="RelayCommand"/> im aktuellen Befehlsziel aus.
/// </summary>
/// <param name="parameter">
/// Die vom Befehl verwendeten Daten. Wenn für den Befehl keine Datenübergabe erforderlich ist, kann dieses Objekt auf NULL festgelegt werden.
/// </param>
void RelayCommand::Execute(Object^ parameter)
{
	(_executeCallback) (parameter);
}

/// <summary>
/// Zum Aufrufen des <see cref="CanExecuteChanged"/>-Ereignisses verwendete Methode
/// um anzugeben, dass der Rückgabewert von <see cref="CanExecute"/>
/// Die Methode hat sich geändert.
/// </summary>
void RelayCommand::RaiseCanExecuteChanged()
{
	CanExecuteChanged(this, nullptr);
}

/// <summary>
/// RelayCommand-Klassendestruktor.
/// </summary>
RelayCommand::~RelayCommand()
{
	_canExecuteCallback = nullptr;
	_executeCallback = nullptr;
};

/// <summary>
/// Erstellt einen neuen Befehl, der immer ausgeführt werden kann.
/// </summary>
/// <param name="canExecuteCallback">Die Logik des Ausführungsstatus.</param>
/// <param name="executeCallback">Die Ausführungslogik.</param>
RelayCommand::RelayCommand(std::function<bool(Platform::Object^)> canExecuteCallback,
	std::function<void(Platform::Object^)> executeCallback) :
	_canExecuteCallback(canExecuteCallback),
	_executeCallback(executeCallback)
	{
	}
