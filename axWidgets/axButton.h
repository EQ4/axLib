/*******************************************************************************
 * Copyright (c) 2013 Alexandre Arsenault.
 *
 * This file is part of axLibrary.
 *
 * axLibrary is free or commercial software: you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 or any later version of the
 * License or use a commercial axLibrary License.
 *
 * axLibrary is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with axLibrary. If not, see <http://www.gnu.org/licenses/>.
 *
 * To release a closed-source product which uses axLibrary, commercial
 * licenses are available, email alx.arsenault@gmail.com for more information.
 ******************************************************************************/

#ifndef __AX_BUTTON__
#define __AX_BUTTON__

/*******************************************************************************
 * @file    axButton.h
 * @author  Alexandre Arsenault <alx.arsenault@gmail.com>
 * @brief   axButton.
 * @date    19/07/2013
 ******************************************************************************/

/// @defgroup Widgets
/// @{

/// @defgroup Button
/// @{

#include <axEvent/axEvent.h>
#include "axWidget.h"
#include <axUtils/axUtils.h>
#include <axGL/axGC.h>
#include <axGL/axImage.h>
//#include "ax::Event::Msg.h"
#include "axConfig.h"
#include "axWidgetBuilder.h"


namespace ax
{
    /***************************************************************************
     * axButon.
     **************************************************************************/
    class Button : public axWidget
    {
    public:
        /***********************************************************************
         * axButton::Flags.
         **********************************************************************/
        class Flags
        {
        public:
            static const ax::Flag SINGLE_IMG;
            static const ax::Flag IMG_RESIZE;
            static const ax::Flag CAN_SELECTED;
        };
        
        /***********************************************************************
         * axButton::Msg.
         **********************************************************************/
        class Msg : public Event::Msg
        {
        public:
            Msg();
            
            Msg(Button* sender, const std::string& msg);
            
            Button* GetSender() const;
            
            std::string GetMsg() const;
            
            Event::Msg* GetCopy();
            
        private:
            Button* _sender;
            std::string _msg;
        };
        
        /***********************************************************************
         * axButton::Events.
         **********************************************************************/
        class Events
        {
        public:
            enum : ax::Event::Id { BUTTON_CLICK };
            
            Events(){}
            Events(const ax::Event::Function& fct){ button_click = fct; }
            
            ax::Event::Function button_click;
        };
        
        /***********************************************************************
         * axButton::Info.
         **********************************************************************/
        class Info : public axInfo
        {
        public:
            Info();
            
            Info(const std::string& path);
            
            Info(const ax::StringPairVector& attributes);
            
            Info(const ax::Color& normal_color,
                 const ax::Color& hover_color,
                 const ax::Color& clicked_color,
                 const ax::Color& selected_color,
                 const ax::Color& contour_color,
                 const ax::Color& font_color,
                 const int& roundCornerRadius = 0);
            
            // Info needed for debug editor. Derived from axInfo.
            virtual ax::StringVector GetParamNameList() const;
            virtual std::string GetAttributeValue(const std::string& name);
            virtual void SetAttribute(const ax::StringPair& attribute);
            
            ax::Color normal;
            ax::Color hover;
            ax::Color clicking;
            ax::Color selected;
            ax::Color contour;
            ax::Color font_color;
            int round_corner_radius = 0;
        };
        
        /***********************************************************************
         * axButton::Builder.
         **********************************************************************/
        class Builder : public axWidgetBuilder
        {
        public:
            Builder(axWindow* parent);
            
            virtual axWidget* Create(const ax::StringPairVector& attributes);
            
            ax::StringVector GetParamNameList() const;
            
        private:
            Button::Info _info;
            std::string _label, _img, _msg;
            ax::Flag _flags;
            ax::Size _size;
            int _nextPositionDelta;
            Button* _past;
            ax::Utils::Direction _direction;
        };
        
        /***********************************************************************
         * axButton::axButton.
         **********************************************************************/
        Button(axWindow* parent,
                 const ax::Rect& rect,
                 const Button::Events& events,
                 const Button::Info& info,
                 std::string img_path = "",
                 std::string label = "",
                 ax::Flag flags = 0,
                 std::string msg = "");
        
        void SetMsg(const std::string& msg);
        
        void SetSelected(const bool& selected);
        
        void SetLabel(const std::string& label);
        
    protected:
        Button::Events _events;
        ax::Image* _btnImg;
        ax::Flag _flags;
        std::string _label, _msg;
        std::unique_ptr<ax::Font> _font;
        
        ax::Color* _currentColor;
        bool _selected;
        int _nCurrentImg;
        
        enum axButtonState
        {
            axBTN_NORMAL,
            axBTN_HOVER,
            axBTN_DOWN,
            axBTN_SELECTED
        };
        
        virtual void OnPaint();
        virtual void OnMouseLeftDown(const ax::Point& pos);
        virtual void OnMouseLeftUp(const ax::Point& pos);
        virtual void OnMouseEnter();
        virtual void OnMouseLeave();
    };
}

/*******************************************************************************
 * axButonInfo template.
 ******************************************************************************/
#define axSTANDARD_BUTTON 	axButton::Info( \
ax::Color(0.5, 0.5, 0.5),\
ax::Color(0.6, 0.6, 0.6),\
ax::Color(0.4, 0.4, 0.4),\
ax::Color(0.5, 0.5, 0.5),\
ax::Color(0.0, 0.0, 0.0),\
ax::Color(0.0, 0.0, 0.0), 3)

#define axBUTTON_TRANSPARENT 	axButton::Info( \
ax::Color(0.0, 0.0, 0.0, 0.0),\
ax::Color(0.0, 0.0, 0.0, 0.0),\
ax::Color(0.0, 0.0, 0.0, 0.0),\
ax::Color(0.0, 0.0, 0.0, 0.0),\
ax::Color(0.0, 0.0, 0.0, 0.0),\
ax::Color(0.0, 0.0, 0.0, 1.0), 3)

#define btn_xml "<?xml version=\"1.0\" encoding=\"UTF-8\"?>         \
                    <axButton normal=\"0.45, 0.45, 0.45, 1.0\"      \
                              hover=\"0.5, 0.5, 0.5, 1.0\"          \
                              clicking=\"0.4, 0.4, 0.4, 1.0\"       \
                              selected=\"0.45, 0.45, 0.45, 1.0\"    \
                              contour=\"0.0, 0.0, 0.0, 1.0\"        \
                              font_color=\"0.0, 0.0, 0.0, 1.0\">    \
                    </axButton>"
/// @}
/// @}
#endif //__AX_BUTTON__




