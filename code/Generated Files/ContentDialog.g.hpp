

//------------------------------------------------------------------------------
//     This code was generated by a tool.
//
//     Changes to this file may cause incorrect behavior and will be lost if
//     the code is regenerated.
//------------------------------------------------------------------------------
#include "pch.h"
#include "ContentDialog.xaml.h"




void ::Yatzy::ContentDialog::InitializeComponent()
{
    if (_contentLoaded)
        return;

    _contentLoaded = true;

    // Call LoadComponent on ms-appx:///ContentDialog.xaml
    ::Windows::UI::Xaml::Application::LoadComponent(this, ref new ::Windows::Foundation::Uri(L"ms-appx:///ContentDialog.xaml"), ::Windows::UI::Xaml::Controls::Primitives::ComponentResourceLocation::Application);

    // Get the TextBox named 'email'
    email = safe_cast<::Windows::UI::Xaml::Controls::TextBox^>(static_cast<Windows::UI::Xaml::IFrameworkElement^>(this)->FindName(L"email"));
    // Get the PasswordBox named 'password'
    password = safe_cast<::Windows::UI::Xaml::Controls::PasswordBox^>(static_cast<Windows::UI::Xaml::IFrameworkElement^>(this)->FindName(L"password"));
    // Get the CheckBox named 'showPassword'
    showPassword = safe_cast<::Windows::UI::Xaml::Controls::CheckBox^>(static_cast<Windows::UI::Xaml::IFrameworkElement^>(this)->FindName(L"showPassword"));
    // Get the TextBlock named 'body'
    body = safe_cast<::Windows::UI::Xaml::Controls::TextBlock^>(static_cast<Windows::UI::Xaml::IFrameworkElement^>(this)->FindName(L"body"));
}

void ::Yatzy::ContentDialog::Connect(int connectionId, Platform::Object^ target)
{
    switch (connectionId)
    {
    case 1:
        (safe_cast<::Windows::UI::Xaml::Controls::ContentDialog^>(target))->PrimaryButtonClick +=
            ref new ::Windows::Foundation::TypedEventHandler<::Windows::UI::Xaml::Controls::ContentDialog^, ::Windows::UI::Xaml::Controls::ContentDialogButtonClickEventArgs^>(this, (void (::Yatzy::ContentDialog::*)(Windows::UI::Xaml::Controls::ContentDialog^, Windows::UI::Xaml::Controls::ContentDialogButtonClickEventArgs^))&ContentDialog::ContentDialog_PrimaryButtonClick);
        (safe_cast<::Windows::UI::Xaml::Controls::ContentDialog^>(target))->SecondaryButtonClick +=
            ref new ::Windows::Foundation::TypedEventHandler<::Windows::UI::Xaml::Controls::ContentDialog^, ::Windows::UI::Xaml::Controls::ContentDialogButtonClickEventArgs^>(this, (void (::Yatzy::ContentDialog::*)(Windows::UI::Xaml::Controls::ContentDialog^, Windows::UI::Xaml::Controls::ContentDialogButtonClickEventArgs^))&ContentDialog::ContentDialog_SecondaryButtonClick);
        break;
    }
    (void)connectionId; // Unused parameter
    (void)target; // Unused parameter
    _contentLoaded = true;
}

