﻿

#pragma once
//------------------------------------------------------------------------------
//     This code was generated by a tool.
//
//     Changes to this file may cause incorrect behavior and will be lost if
//     the code is regenerated.
//------------------------------------------------------------------------------

namespace Windows {
    namespace UI {
        namespace Xaml {
            namespace Controls {
                ref class Grid;
                ref class ListView;
                ref class StackPanel;
                ref class TextBlock;
            }
        }
    }
}
namespace Windows {
    namespace UI {
        namespace Xaml {
            namespace Shapes {
                ref class Rectangle;
            }
        }
    }
}

namespace Yatzy
{
    partial ref class Score : public ::Windows::UI::Xaml::Controls::Page, 
        public ::Windows::UI::Xaml::Markup::IComponentConnector
    {
    public:
        void InitializeComponent();
        virtual void Connect(int connectionId, ::Platform::Object^ target);
    
    private:
        bool _contentLoaded;
    
        private: ::Windows::UI::Xaml::Controls::Grid^ LayoutRoot;
        private: ::Windows::UI::Xaml::Controls::ListView^ ausgabeInfo_Pkt;
        private: ::Windows::UI::Xaml::Controls::ListView^ ausgabeInfo_Text;
        private: ::Windows::UI::Xaml::Controls::StackPanel^ stackPlatz;
        private: ::Windows::UI::Xaml::Controls::ListView^ ausgabePunkte;
        private: ::Windows::UI::Xaml::Controls::ListView^ ausgabeName;
        private: ::Windows::UI::Xaml::Controls::ListView^ ausgabePlatz;
        private: ::Windows::UI::Xaml::Controls::TextBlock^ textÜberschrift;
        private: ::Windows::UI::Xaml::Shapes::Rectangle^ rectÜberschrift;
    };
}
