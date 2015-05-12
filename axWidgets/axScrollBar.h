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

#ifndef __AX_SCROLL_BAR__
#define __AX_SCROLL_BAR__

/// @defgroup Widgets
/// @{

/// @defgroup ScrollBar
/// @{

#include <axEvent/axEvent.h>
#include "axPanel.h"
#include "axColor.h"
#include "axGC.h"
#include "axImage.h"
#include <fstream>

#include "axButton.h"

/**************************************************************************//**
 * axButtonFlags.
******************************************************************************/
// #define axBUTTON_SINGLE_IMG	axFLAG_1
// #define axBUTTON_IMG_RESIZE	axFLAG_2

class axScrollBar;

class axScrollBarMsg : public ax::Event::Msg
{
public:
	axScrollBarMsg()
	{
		_sender = nullptr;
	}

	axScrollBarMsg(axScrollBar* sender, const string& msg)
	{
		_sender = sender;
		_msg = msg;
	}

	axScrollBar* GetSender() const
	{
		return _sender;
	}

	string GetMsg() const
	{
		return _msg;
	}
    
    ax::Event::Msg* GetCopy()
    {
        return new axScrollBarMsg(*this);
    }

private:
	axScrollBar* _sender;
	string _msg;
};

struct axScrollBarEvents
{
    enum : ax::Event::Id { VALUE_CHANGE };
	
	axScrollBarEvents(){}
    axScrollBarEvents(ax::Event::Function& fct){ value_change = fct; }
    
    ax::Event::Function value_change;
};

struct axScrollBarInfo
{
	axColor normal;
	axColor hover;
	axColor clicking;
	axColor slider_contour;
	axColor contour;
	axColor bg_top;
    axColor bg_bottom;

	axScrollBarInfo(){}
	axScrollBarInfo(
		const axColor& normal_color,
		const axColor& hover_color,
		const axColor& clicked_color,
		const axColor& sliderContour,
		const axColor& contour_color,
		const axColor& bgTop,
        const axColor& bgBottom) :
		normal(normal_color),
		hover(hover_color),
		clicking(clicked_color),
		slider_contour(sliderContour),
		contour(contour_color),
		bg_top(bgTop),
        bg_bottom(bgBottom){}
};


class axScrollBar : public axPanel
{
public:
	axScrollBar(axWindow* parent, axWindow* handle,
                const ax::Rect& rect,
                const axScrollBarEvents& events,
                const axScrollBarInfo& info,
                axFlag flags = 0);

//	double getZeroToOneValue();
//
//	// void setBackgroundImage(wxBitmap& bmp);
//	void setSliderPositionZeroToOne(const double& value);
//	void setInputTopDelta(int y);
//	void setInputFrameHeight(int y);
//	void setInputPanelHeight(int y);
//	void setInputInfo(int frameSize, int panelSize, int topDelta);
//	double getSliderValue() const;
//	inline void recalculateInputValue();
    
    void SetPanelSize(const ax::Size& size);

private:
	axScrollBarEvents _events;
	axScrollBarInfo _info;
	axFlag _flags;
    axWindow* _handle;

    ax::Button* _btn[2];

	int _imgHeight, _sliderHeight, _sliderMaxHeight, _sliderPos, _yClickDelta;
    ax::Size _panelSize;
    
    axColor* _currentScrollBarColor;
	double _value;

	virtual void OnPaint();
	virtual void OnMouseLeftDragging(const ax::Point& pos);
	virtual void OnMouseLeftDown(const ax::Point& pos);
	virtual void OnMouseLeftUp(const ax::Point& pos);
    virtual void OnMouseMotion(const ax::Point& pos);
	virtual void OnMouseEnter();
	virtual void OnMouseLeave();
};

/// @}
/// @}
#endif //__AX_SCROLL_BAR__

