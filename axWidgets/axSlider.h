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

#ifndef __AX_SLIDER__
#define __AX_SLIDER__

/// @defgroup Widgets
/// @{

/// @defgroup Slider
/// @{

#include <axEvent/axEvent.h>
#include <axUtils/axUtils.h>
#include "axPanel.h"
//#include <axUtils/axUtils.h>
#include <axGL/axGC.h>
#include <axGL/axImage.h>
//#include "ax::Event::Msg.h"

/**************************************************************************//**
 * axSliderFlags.
******************************************************************************/
#define axSLIDER_FLAG_VERTICAL			ax::FlagValue::FLAG_1
#define axSLIDER_FLAG_CLICK_ANYWHERE    ax::FlagValue::FLAG_2
#define axSLIDER_FLAG_RELEASE_ON_LEAVE  ax::FlagValue::FLAG_3
#define axSLIDER_FLAG_LEFT_CLICK_ENTER  ax::FlagValue::FLAG_4
#define axSLIDER_FLAG_RIGHT_ALIGN       ax::FlagValue::FLAG_5
#define axSLIDER_FLAG_MIDDLE_ALIGN      ax::FlagValue::FLAG_6
#define axSLIDER_FLAG_BACK_SLIDER       ax::FlagValue::FLAG_7
#define axSLIDER_FLAG_NO_SLIDER_LINE    ax::FlagValue::FLAG_8

/**************************************************************************//**
 * axSliderMsg
******************************************************************************/
class axSliderMsg : public ax::Event::Msg
{
public:
	axSliderMsg(const double& value):
		_value(value)
	{
	}

	double GetValue() const
	{
		return _value;
	}
    
    ax::Event::Msg* GetCopy()
    {
        return new axSliderMsg(*this);
    }

private:
	double _value;
};

/**************************************************************************//**
 * axSliderEvents.
******************************************************************************/
struct axSliderEvents
{
    enum : ax::Event::Id { VALUE_CHANGE };
    
    axSliderEvents(){}
    axSliderEvents(const ax::Event::Function& fct){ slider_value_change = fct; }
    
    ax::Event::Function slider_value_change;
};

/**************************************************************************//**
 * axSliderInfo.
******************************************************************************/
struct axSliderInfo
{
	std::string img_path;
	ax::Size btn_size;
	unsigned int slider_width;
    int contour_round_radius = 0;

	ax::Color bgColorNormal,
			bgColorHover,
			bgColorClicked,
			sliderColorNormal,
			sliderColorHover,
			sliderColorClicked,
			sliderContourColor,
			contourColor,
			backSliderColor,
			backSliderContourColor;

    axSliderInfo(){}
    axSliderInfo(const std::string& imgPath,
				 const ax::Size& size,
				 const ax::Color& bg_normal,
				 const ax::Color& bg_hover,
				 const ax::Color& bg_clicking,
				 const ax::Color& slider_normal,
				 const ax::Color& slider_hover,
				 const ax::Color& slider_clicking,
				 const ax::Color& slider_contour,
				 const ax::Color& contour,
				 const ax::Color& back_slider,
				 const ax::Color& back_slider_contour,
				 const unsigned int width,
                 const int& contourRadius) :
				 // Members.
				 img_path(imgPath),
				 btn_size(size),
				 bgColorNormal(bg_normal),
				 bgColorHover(bg_hover),
				 bgColorClicked(bg_clicking),
				 sliderColorNormal(slider_normal),
				 sliderColorHover(slider_hover),
				 sliderColorClicked(slider_clicking),
				 sliderContourColor(slider_contour),
				 contourColor(contour),
				 backSliderColor(back_slider),
				 backSliderContourColor(back_slider_contour),
				 slider_width(width),
                 contour_round_radius(contourRadius){}

    axSliderInfo(const std::string& info_path)
	{
		axUNUSED(info_path);
	// 	ifstream file;
	// 	file.open(info_path);

	// 	if (file.fail())
	// 	{
	// 		cerr << "Problem opening file " << info_path << endl;
	// 	}
	// 	else
	// 	{
	// 		string line;

	// 		if (file.good())
	// 		{
	// 			getline(file, line);
	// 			img_path = line;
	// 		}

	// 		if (file.good())
	// 		{
	// 			getline(file, line);
	// 			btn_size.x = stoi(line);
	// 		}

	// 		if (file.good())
	// 		{
	// 			getline(file, line);
	// 			btn_size.y = stoi(line);
	// 		}

	// 		if (file.good())
	// 		{
	// 			getline(file, line);
	// 			slider_width = stoi(line);
	// 		}
			

	// 		ax::Color* ptr = &bgColorNormal;
	// 		while (file.good())
	// 		{
	// 			getline(file, line);
	// 			*ptr++ = ax::Color(line);
	// 		}
	// 	}
	}
};

/**************************************************************************//**
 * axSlider.
******************************************************************************/
class axSlider : public axPanel
{
public:
	axSlider(axWindow* parent,
			 const ax::Rect& rect,
			 const axSliderEvents& events,
			 const axSliderInfo& info,
			 ax::Flag flags = 0);

	void SetBackgroundAlpha(const float& alpha)
	{
		_bg_alpha = alpha;
	}

	void ResizeSlider(const ax::Size& size)
	{
		SetSize(size);
		_sliderYPos = int((GetSize().x - _info.slider_width) * 0.5);
		_btnYPos = int((GetSize().x - _info.btn_size.x) * 0.5);
	}

	double GetValue() const
	{
		return _sliderValue;
	}

	void SetValue(const double& value);
	
protected:
	//axSliderMembers _members;
	//axSliderOrientationStrategy* _sliderOrientationStrategy;
	axSliderEvents _events;
	axSliderInfo _info;
	ax::Flag _flag;
	ax::Color _currentBgColor, 
			_currentSliderColor;



	ax::Image _btnImg;
	ax::Flag _flags;
	int _nCurrentImg,
		_sliderPosition,
		_btnYPos,
		_sliderYPos,
		_delta_click;

    float _bg_alpha;

	double _sliderValue;

	enum axButtonState 
	{
		axBTN_NORMAL,
		axBTN_HOVER,
		axBTN_DOWN
	};

	void blockSliderPosition(const ax::Point& pos);
	void updateSliderValue();

    void DrawVerticalSlider(ax::GC* gc, const ax::Rect& rect0);
    void DrawLineBehindSlider_Vertical(ax::GC* gc, const ax::Rect& rect0);



	void OnPaint();
	void OnMouseEnter(const ax::Point& pos);
	void OnMouseLeftDown(const ax::Point& pos);
	void OnMouseLeftUp(const ax::Point& pos);
	void OnMouseMotion(const ax::Point& pos);
	void OnMouseLeftDragging(const ax::Point& pos);
	void OnMouseLeave(const ax::Point& pos);
	//void OnFocusIn();
};

/**************************************************************************//**
 * axSliderOrientation.
******************************************************************************/
//class axSliderOrientationStrategy : public axSlider
//{
//public:
//	axSliderOrientationStrategy(bool vertical)
//	{
//
//	}
//};
//
//
//class axSliderVertical : public axSliderOrientation
//{
//public:
//	axSliderVertical()
//	{
//
//	}
//}

//#define axSLIDER_STANDARD_BLUE axSliderInfo( "ressources/images/bouttons/sliderCtrl.png",   \
//											 ax::Size(12, 12),								\
//											 ax::Color("#444444"),							\
//											 ax::Color("#444444"),							\
//											 ax::Color("#444444"),							\
//											 ax::Color("#3333FF"),							\
//											 ax::Color("#4444FF"),							\
//											 ax::Color("#5555FF"),							\
//											 ax::Color("#000000"),							\
//											 ax::Color("#000000"),							\
//											 ax::Color("#000000"),							\
//											 ax::Color("#000000"),							\
//											 5)
//
//#define axSLIDER_STANDARD_BLUE_NO_IMG axSliderInfo( "",										\
//													ax::Size(0, 0),							\
//													ax::Color("#AAAAAA"),						\
//													ax::Color("#BBBBBB"),						\
//													ax::Color("#CCCCCC"),						\
//													ax::Color("#3333FF"),						\
//													ax::Color("#4444FF"),						\
//													ax::Color("#5555FF"),						\
//													ax::Color("#000000"),						\
//													ax::Color("#000000"),						\
//													ax::Color("#000000"),						\
//													ax::Color("#000000"),						\
//													5)
//

#define axSLIDER_PLAIN_GREY     axSliderInfo( "/Users/alexarse/Project/axLib/ressources/sliderPlain.png",          \
	ax::Size(12, 12), \
	ax::Color(0.1, 0.1, 0.1), \
	ax::Color("#888888"), \
	ax::Color("#888888"), \
	ax::Color("#3333FF"), \
	ax::Color("#4444FF"), \
	ax::Color("#5555FF"), \
	ax::Color("#000000"), \
	ax::Color(0.2, 0.2, 0.2), \
	ax::Color("#444444"), \
	ax::Color("#000000"), \
	5)

/// @}
/// @}
#endif // __AX_SLIDER__
