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

#ifndef __AX_NUMBER_BOX__
#define __AX_NUMBER_BOX__

/*******************************************************************************
 * @file    axNumberBox.h
 * @author  Alexandre Arsenault <alx.arsenault@gmail.com>
 * @brief   axNumberBox.
 * @date    19/07/2013
 ******************************************************************************/

/// @defgroup Widgets
/// @{

/// @defgroup NumberBox
/// @{

#include <axEvent/axEvent.h>
#include "axWidget.h"
#include "axColor.h"
#include "axGC.h"
#include "axImage.h"
//#include "ax::Event::Msg.h"

/***************************************************************************
 * axNumberBox.
 **************************************************************************/
class axNumberBox: public axWidget
{
public:
    /***************************************************************************
     * axNumberBox::Flags.
     **************************************************************************/
    class Flags
    {
    public:
        static const axFlag SINGLE_IMG;
        static const axFlag NO_IMG_RESIZE;
        static const axFlag LABEL;
        static const axFlag SLIDER;
        static const axFlag NO_MOUSE;
    };
    
    /***************************************************************************
     * axNumberBox::Msg.
     **************************************************************************/
    class Msg : public ax::Event::Msg
    {
    public:
        Msg(const double& value);
        
        double GetValue() const;
        
        ax::Event::Msg* GetCopy();
        
    private:
        double _value;
    };
    
    /***************************************************************************
     * axNumberBox::Events.
     **************************************************************************/
    class Events
    {
    public:
        enum : ax::Event::Id { VALUE_CHANGE };
        
        Events(){}
        Events(ax::Event::Function& fct){ value_change = fct; }
        
        ax::Event::Function value_change;
    };
    
    /***************************************************************************
     * axNumberBox::Info.
     **************************************************************************/
    class Info : public axInfo
    {
    public:
        Info();
        
        Info(const std::string& path);
        
        Info(const ax::StringPairVector& attributes);
        
        Info(const axColor& normal_color,
             const axColor& hover_color,
             const axColor& clicked_color,
             const axColor& selected_color,
             const axColor& contour_color,
             const axColor& fontColor,
             const std::string& img = "",
             const bool& singleImg = false);
  
        // Info needed for debug editor. Derived from axInfo.
        virtual ax::StringVector GetParamNameList() const;
        virtual std::string GetAttributeValue(const std::string& name);
        virtual void SetAttribute(const ax::StringPair& attribute);

        axColor normal;
        axColor hover;
        axColor clicking;
        axColor selected;
        axColor contour;
        axColor font_color;
        
        std::string img;
        bool single_img;
    };
    
    /***************************************************************************
     * axNumberBox::Builder.
     **************************************************************************/
    class Builder
    {
    public:
        Builder(axWindow* win);
        
        axNumberBox* Create(ax::StringPairVector attributes);
        
    private:
        axWindow* _parent;
        axNumberBox::Info _info;
        axFlag _flags;
        ax::Size _size;
        int _nextPositionDelta;
        axNumberBox* _past;
        ax::Utils::Direction _direction;
    };
    
    /***************************************************************************
     * axNumberBox::axNumberBox.
     **************************************************************************/
    axNumberBox(axWindow* parent,
                const ax::Rect& rect,
                const axNumberBox::Events& events,
                const axNumberBox::Info& info,
                axFlag flags = 0,
                double value = 0.0,
                ax::FloatRange range = ax::FloatRange(0.0, 1.0),
                ax::Utils::Control::Type type = ax::Utils::Control::axCTRL_FLOAT,
                ax::Utils::Control::Unit m_unit = ax::Utils::Control::axCTRL_NO_UNIT,
                ax::Utils::Control::Interpolation interpolation = ax::Utils::Control::axCTRL_LINEAR,
                std::string label = "");

    double GetValue();
    
    virtual void SetInfo(const ax::StringPairVector& attributes);

	void SetValue(const double& value)
	{
		_value = value;
		Update();
	}
    
private:
    axNumberBox::Events _events;
    axFlag _flags;
    axImage* _bgImg;
    axFont* _font;

    ax::Utils::Control::Type _type;
    ax::Utils::Control::Unit _unit;
    ax::FloatRange _range;
    ax::Utils::Control::Interpolation _interpolation;

    axColor* _currentColor;
    int _nCurrentImg;
    double _value;
    double _zeroToOneValue;
    std::string _label;

    int _clickPosY;

    enum axNumberBoxState
    {
        axNUM_BOX_NORMAL,
        axNUM_BOX_HOVER,
        axNUM_BOX_DOWN
    };

    // Events.
    virtual void OnPaint();
    virtual void OnMouseEnter();
    virtual void OnMouseLeftDown(const ax::Point& pos);
    virtual void OnMouseLeftUp(const ax::Point& pos);
    virtual void OnMouseLeftDragging(const ax::Point& pos);
    virtual void OnMouseLeave();

};

#define axNUMBER_BOX_STANDARD axNumberBox::Info( axColor("#AA1111"),          \
                                               axColor("#CC1111"),          \
                                               axColor("#FF1111"),          \
                                               axColor("#FF0000"),          \
                                               axColor("#000000") )

#define axNUMBER_BOX_WHITE axNumberBox::Info( axColor("#FFFFFF"),          \
                                            axColor("#DDDDDD"),          \
                                            axColor("#AAAAAA"),          \
                                            axColor("#FF0000"),          \
                                            axColor("#000000") )

/// @}
/// @}
#endif // __AX_NUMBER_BOX__
