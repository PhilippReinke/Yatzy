//
// RelayCommand.h
// Deklaration des RelayCommand und verknüpfter Klassen
//

#pragma once

// <summary>
// Ein Befehl mit dem einzigen Zweck, seine Funktionalität zu vermitteln 
// zu anderen Objekten durch Aufrufen von Delegaten. 
// Der Standardrückgabewert für die CanExecute-Methode ist 'true'.
// <see cref="RaiseCanExecuteChanged"/> muss jedes mal aufgerufen werden, wenn
// <see cref="CanExecute"/> muss einen anderen Wert zurückgeben.
// </summary>


namespace Yatzy
{
	namespace Common
	{
		[Windows::Foundation::Metadata::WebHostHidden]
		public ref class RelayCommand sealed :[Windows::Foundation::Metadata::Default] Windows::UI::Xaml::Input::ICommand
		{
		public:
			virtual event Windows::Foundation::EventHandler<Object^>^ CanExecuteChanged;
			virtual bool CanExecute(Object^ parameter);
			virtual void Execute(Object^ parameter);
			virtual ~RelayCommand();

		internal:
			RelayCommand(std::function<bool(Platform::Object^)> canExecuteCallback,
				std::function<void(Platform::Object^)> executeCallback);
			void RaiseCanExecuteChanged();

		private:
			std::function<bool(Platform::Object^)> _canExecuteCallback;
			std::function<void(Platform::Object^)> _executeCallback;
		};
	}
}