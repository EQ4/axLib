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

#ifndef __AX_TOGGLE__
#define __AX_TOGGLE__

/*******************************************************************************
 * @file    axToggle
 * @author  Alexandre Arsenault <alx.arsenault@gmail.com>
 * @brief   axToggle.
 * @date    19/07/2013
 ******************************************************************************/

/// @defgroup Widgets
/// @{

/// @defgroup Toggle
/// @{

#include <axEvent/axEvent.h>
#include <axUtils/axUtils.h>

#include "axWidget.h"
#include "axPanel.h"
//#include "ax::Color.h"
#include "axGC.h"
#include <axGL/axFont.h>
#include <axGL/axImage.h>
//#include <axEvent"ax::Event::Msg.h"
#include <fstream>

/*******************************************************************************
 * axToggle.
 ******************************************************************************/
class axToggle : public axWidget
{
public:
    /***************************************************************************
     * axToggle::Flags.
     **************************************************************************/
    class Flags
    {
    public:
        static const ax::Flag SINGLE_IMG;
        static const ax::Flag IMG_RESIZE;
        static const ax::Flag CLICK_ON_LEFT_DOWN;
        static const ax::Flag CANT_UNSELECT_WITH_MOUSE;
    };
    
    /***************************************************************************
     * axToggle::Msg.
     **************************************************************************/
    class Msg : public ax::Event::Msg
    {
    public:
        Msg();
        
        Msg(axToggle* sender, const bool& selected);
        
        Msg(axToggle* sender, const bool& selected, const std::string& msg);
        
        axToggle* GetSender() const;
        
        bool GetSelected() const;
        
        std::string GetMsg() const;
        
        ax::Event::Msg* GetCopy();
        
    private:
        axToggle* _sender;
        bool _selected;
        std::string _msg;
    };
    
    /***************************************************************************
     * axToggle::Events.
     **************************************************************************/
    class Events
    {
    public:
        enum : ax::Event::Id { BUTTON_CLICK };
        
        ax::Event::Function button_click;
        
        Events(){}
        Events(const ax::Event::Function& fct){ button_click = fct; }
    };
    
    /***************************************************************************
     * axToggle::Info.
     **************************************************************************/
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
             const ax::Color& selectedHover_color,
             const ax::Color& selectedClicking_color,
             const ax::Color& contour_color,
             const ax::Color& font_color_,
             const std::string& img = "",
             const bool& singleImg = false);
        
        // Info needed for debug editor. Derived from axInfo.
        virtual ax::StringVector GetParamNameList() const;
        virtual std::string GetAttributeValue(const std::string& name);
        virtual void SetAttribute(const ax::StringPair& attribute);
        
        ax::Color normal;
        ax::Color hover;
        ax::Color clicking;
        
        ax::Color selected;
        ax::Color selected_hover;
        ax::Color selected_clicking;
        
        /// @todo Add select font color to axToggle.
        ax::Color selected_font_color;
        
        ax::Color contour;
        ax::Color font_color;
        int font_size = 12;
        
        std::string img;
        bool single_img;
    };
    
    /***************************************************************************
     * axToggle::Builder.
     **************************************************************************/
    class Builder
    {
    public:
        Builder(axPanel* parent,
                const ax::Size& size,
                const axToggle::Info& info,
                std::string img_path = "",
                std::string label = "",
                ax::Flag flags = 0,
                int nextPositionDelta = 5,
                ax::Utils::Direction direction = ax::Utils::axDIRECTION_RIGHT);
        
        Builder(axWindow* win);
        
        axToggle* Create(const ax::StringPairVector& attributes);
        
        virtual ax::StringVector GetParamNameList() const;
    
    private:
        axWindow* _parent;
        axToggle::Info _info;
        std::string _label;
        std::string _img;
        ax::Flag _flags;
        ax::Size _size;
        int _nextPositionDelta;
        axToggle* _past;
        ax::Utils::Direction _direction;
    };
    
    /***************************************************************************
     * axToggle::axToggle.
     **************************************************************************/
    axToggle(axWindow* parent,
             const ax::Rect& rect,
             const axToggle::Events& events,
             const axToggle::Info& info,
             std::string img_path = "",
             std::string label = "",
             ax::Flag flags = 0,
             std::string msg = "");
        
    void SetMsg(const std::string& msg);
    void SetSelected(const bool& selected);

protected:
	enum axToggleState
	{
		axTOG_NORMAL,
		axTOG_HOVER,
		axTOG_CLICK,
		axTOG_SEL_NORMAL,
		axTOG_SEL_HOVER,
		axTOG_SEL_CLICK
	};

	int _nCurrentImg;

    axToggle::Events _events;
	ax::Color* _currentColor;
	ax::Image* _bgImg;
    std::string _label;
    std::string _msg;
    std::unique_ptr<ax::Font> _font;
	
	bool _selected;
    ax::Flag _flags;
	ax::Color test;
	axFloat _bgAlpha;

    // Events.
	virtual void OnPaint();
	virtual void OnMouseLeftDown(const ax::Point& pos);
	virtual void OnMouseLeftUp(const ax::Point& pos);
	virtual void OnMouseEnter();
	virtual void OnMouseLeave();
};

#define axSTANDARD_TOGGLE 	axToggleInfo( \
ax::Color(0.5, 0.5, 0.5),\
ax::Color(0.6, 0.6, 0.6),\
ax::Color(0.4, 0.4, 0.4),\
ax::Color(0.5, 0.5, 0.5),\
ax::Color(0.0, 0.0, 0.0),\
ax::Color(0.0, 0.0, 0.0))

#define axTOGGLE_TRANSPARENT 	axToggleInfo( \
ax::Color(0.5, 0.5, 0.5, 0.0),\
ax::Color(0.6, 0.6, 0.6, 0.0),\
ax::Color(0.4, 0.4, 0.4, 0.0),\
ax::Color(0.5, 0.5, 0.5, 0.0),\
ax::Color(0.0, 0.0, 0.0, 0.0),\
ax::Color(0.0, 0.0, 0.0, 0.0),\
ax::Color(0.0, 0.0, 0.0, 0.0),\
ax::Color(0.0, 0.0, 0.0, 1.0))

/// @}
/// @}
#endif //__AX_TOGGLE__

