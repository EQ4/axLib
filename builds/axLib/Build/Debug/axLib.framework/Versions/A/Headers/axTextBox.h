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

#ifndef __AX_TEXT_BOX__
#define __AX_TEXT_BOX__

/*******************************************************************************
 * @file    axTextBox.h
 * @author  Alexandre Arsenault <alx.arsenault@gmail.com>
 * @brief   axButton.
 * @date    24/01/2015
 ******************************************************************************/

/// @defgroup Widgets
/// @{

#include <axEvent/axEvent.h>
#include "axWidget.h"
#include <axUtils/axUtils.h>
#include <axGL/axGC.h>
#include <axGL/axImage.h>
//#include "ax::Event::Msg.h"
#include "axConfig.h"
#include "axWidgetBuilder.h"
#include <axEvent/axTimer.h>

/*******************************************************************************
 * axTextBox.
 ******************************************************************************/
class axTextBox : public axWidget
{
public:
    /***************************************************************************
     * axTextBox::Flags.
     **************************************************************************/
    class Flags
    {
    public:
        static const ax::Flag FLASHING_CURSOR;
        static const ax::Flag CONTOUR_HIGHLIGHT;
        static const ax::Flag CONTOUR_NO_FADE;
        static const ax::Flag HIDDEN_TEXT;
    };
    
    /***************************************************************************
     * axTextBox::Msg.
     **************************************************************************/
    class Msg : public ax::Event::Msg
    {
    public:
        Msg();
        
        Msg(axTextBox* sender, const std::string& msg);
        
        axTextBox* GetSender() const;
        
        std::string GetMsg() const;
        
        ax::Event::Msg* GetCopy();
        
    private:
        axTextBox* _sender;
        std::string _msg;
    };
    
    /***************************************************************************
     * axTextBox::Events.
     **************************************************************************/
    class Events
    {
    public:
        enum : ax::Event::Id { BUTTON_CLICK, ENTER_CLICK };
        
        Events(){}
        Events(ax::Event::Function& fct){ button_click = fct; }
        
        ax::Event::Function button_click;
        ax::Event::Function enter_click;
    };
    
    /***************************************************************************
     * axTextBox::Info.
     **************************************************************************/
    class Info : public axInfo
    {
    public:
        Info();
        
        Info(const std::string& path);
        
        Info(const ax::StringPairVector& attributes);
        
        Info(const ax::Color& normal,
             const ax::Color& hover,
             const ax::Color& highlight,
             const ax::Color& selected,
             const ax::Color& selected_shadow,
             const ax::Color& cursor,
             const ax::Color& contour,
             const ax::Color& font_color);
        
        // Info needed for debug editor. Derived from axInfo.
        virtual ax::StringVector GetParamNameList() const;
        virtual std::string GetAttributeValue(const std::string& name);
        virtual void SetAttribute(const ax::StringPair& attribute);
        
        ax::Color normal;
        ax::Color hover;
        ax::Color highlight; // This needs to be transparent (alpha < 1.0).
        ax::Color selected;
        ax::Color selected_shadow;
        ax::Color cursor;
        ax::Color contour;
        ax::Color font_color;
    };
    
    /***************************************************************************
     * axTextBox::Builder.
     **************************************************************************/
    class Builder : public axWidgetBuilder
    {
    public:
        Builder(axWindow* parent);
        
        virtual axWidget* Create(const ax::StringPairVector& attributes);
        
    private:
        ax::Size _size;
        ax::Flag _flags;
        axTextBox::Info _info;
        std::string _imgPath;
        std::string _label;
    };
    
    
    /***************************************************************************
     * axTextBox::axTextBox.
     **************************************************************************/
    axTextBox(axWindow* parent,
              const ax::Rect& rect,
              const axTextBox::Events& events,
              const axTextBox::Info& info,
              std::string img_path = "",
              std::string label = "",
              ax::Flag flags = 0);

    void SetLabel(const std::string& label);
    
    std::string GetLabel() const;
    
    void SetMaximumChar(const unsigned int& max_number_of_char);
    
protected:
    axTextBox::Events _events;
    std::string _label;
    ax::Image* _btnImg;
    ax::Flag _flags;
    ax::Font* _font;
        
    ax::Color* _currentColor;
    int _nCurrentImg, _cursorIndex, _cursorBarXPosition, _lastCharXPosition;
    unsigned int _maxNumChar;
    bool _isHightlight, _findClickCursorIndex, _cursorFlashActive;
    ax::Point _clickPosition;
    
    enum axTextBoxState
    {
        axBTN_NORMAL,
        axBTN_HOVER,
        axBTN_DOWN,
        axBTN_SELECTED
    };
    
    ax::Event::Timer* _flashingCursor;
    
	virtual void OnPaint();
	virtual void OnMouseLeftDown(const ax::Point& pos);
    virtual void OnMouseLeftDragging(const ax::Point& pos);
	virtual void OnMouseLeftUp(const ax::Point& pos);
	virtual void OnMouseEnter();
	virtual void OnMouseLeave();
    virtual void OnMouseLeftDoubleClick(const ax::Point& pos);
    virtual void OnKeyDown(const char& key);
    virtual void OnBackSpaceDown();
    
    virtual void OnEnterDown();
    virtual void OnLeftArrowDown();
    virtual void OnRightArrowDown();
    virtual void OnWasKeyUnGrabbed();
    virtual void OnWasKeyGrabbed();
    virtual void OnKeyDeleteDown();
    
    virtual void DrawContourRectangle(ax::GC* gc);
    
    axEVENT_ACCESSOR(ax::Event::Timer::Msg, OnFlashingCursorTimer);
    void OnFlashingCursorTimer(const ax::Event::Timer::Msg& msg);
};

/// @}
#endif // __AX_TEXT_BOX__

