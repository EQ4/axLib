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
#ifndef __AX_POPUP_MENU__
#define __AX_POPUP_MENU__

/// @defgroup Widgets
/// @{

/// @defgroup PopupMenu
/// @{

#include <axEvent/axEvent.h>
#include <axUtils/axUtils.h>
//#include <axEvent/ax::Event::Msg.h>
#include "axPanel.h"
#include "axColor.h"
#include "axGC.h"
#include "axImage.h"
#include "axToggle.h"

/**************************************************************************//**
* axPopupMenuMsg
******************************************************************************/
class axPopupMenuMsg : public ax::Event::Msg
{
public:
	axPopupMenuMsg(const std::string& msg) :
		_msg(msg)
	{
	}

    std::string GetMsg() const
	{
		return _msg;
	}
    
    ax::Event::Msg* GetCopy()
    {
        return new axPopupMenuMsg(*this);
    }

private:
    std::string _msg;
};

/**************************************************************************//**
* axPopupMenuEvents.
******************************************************************************/
struct axPopupMenuEvents
{
    enum : ax::Event::Id { SELECTION_CHANGE };

	axPopupMenuEvents(){}
    axPopupMenuEvents(ax::Event::Function& fct){ selection_change = fct; }
    
    ax::Event::Function selection_change;
};

/**************************************************************************//**
* axPopupMenuInfo.
******************************************************************************/
struct axPopupMenuInfo
{
	axColor bgColorNormal,
			bgColorHover,
			bgColorSelected,
			lineColor,
			contourColor,
			fontColor;

	axPopupMenuInfo(){}
	axPopupMenuInfo(const axColor& bg_normal,
		const axColor& bg_hover,
		const axColor& bg_selected,
		const axColor& lineColor,
		const axColor& contour,
		const axColor& font_color) :
		// Members.
		bgColorNormal(bg_normal),
		bgColorHover(bg_hover),
		bgColorSelected(bg_selected),
		lineColor(lineColor),
		contourColor(contour),
		fontColor(font_color){}
};



/*******************************************************************************//**
* axPopupMenu.
***********************************************************************************/
class axPopupMenu : public axPanel
{
public:
	axPopupMenu(axWindow* parent,
				const ax::Rect& rect,
				const axPopupMenuEvents& events,
				const axPopupMenuInfo& info,
                const std::vector<std::string>& labels,
                std::string bgImg = "",
                ax::Flag flags = 0);

	//~axPopupMenu();

	int GetIndexValue() { return _index; }
    void SetSelectedIndex(const int& index);
	
private:
	axPopupMenuEvents _events;
	axPopupMenuInfo _info;
    ax::Flag _flag;
    std::vector<std::string> _labels;
    std::vector<axToggle*> _btns;
	int _index;
	axToggle* _lastSelected;

    //axEVENT_ACCESSOR(axToggle::Msg, OnButtonClick);
    void OnButtonClick(const axToggle::Msg& msg);

	virtual void OnPaint();
	virtual void OnMouseMotion(const ax::Point& pos);
	virtual void OnMouseLeftUp(const ax::Point& pos);

	static const int LABEL_HEIGHT = 20;

};

/// @}
/// @}
#endif // __AX_POPUP_MENU__
