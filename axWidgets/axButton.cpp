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
#include "axButton.h"
#include "axObjectLoader.h"
//#include "axDebugButton.h"
#include "axMath.h"

/*******************************************************************************
 * axButon::Flags.
 ******************************************************************************/
const axFlag ax::Button::Flags::SINGLE_IMG = axFLAG_1;
const axFlag ax::Button::Flags::IMG_RESIZE = axFLAG_2;
const axFlag ax::Button::Flags::CAN_SELECTED = axFLAG_3;

/*******************************************************************************
 * axButon::Msg.
 ******************************************************************************/
ax::Button::Msg::Msg()
{
    _sender = nullptr;
}

ax::Button::Msg::Msg(ax::Button* sender, const std::string& msg)
{
    _sender = sender;
    _msg = msg;
}

ax::Button* ax::Button::Msg::GetSender() const
{
    return _sender;
}

std::string ax::Button::Msg::GetMsg() const
{
    return _msg;
}

ax::Event::Msg* ax::Button::Msg::GetCopy()
{
    return new_ ax::Button::Msg(*this);
}

/*******************************************************************************
 * axButon::Info.
 ******************************************************************************/
ax::Button::Info::Info() :
axInfo()
{
    
}

ax::Button::Info::Info(const axColor& normal_color,
                     const axColor& hover_color,
                     const axColor& clicked_color,
                     const axColor& selected_color,
                     const axColor& contour_color,
                     const axColor& font_color_,
                     const int& roundCornerRadius) :
// Heritage.
axInfo(),
// Members.
normal(normal_color),
hover(hover_color),
clicking(clicked_color),
selected(selected_color),
contour(contour_color),
font_color(font_color_),
round_corner_radius(roundCornerRadius)
{
    
}

ax::Button::Info::Info(const std::string& path):
// Heritage.
axInfo(path)
{
    axWidgetLoader loader;
    ax::StringPairVector att = loader.GetAttributes(path);
    
    SetAttributes(att);
}

ax::Button::Info::Info(const ax::StringPairVector& attributes)
{
    SetAttributes(attributes);
}

ax::StringVector ax::Button::Info::GetParamNameList() const
{
    return ax::StringVector{"normal",
                            "hover",
                            "clicking",
                            "selected",
                            "contour",
                            "font_color",
                            "corner_radius"};
}

std::string ax::Button::Info::GetAttributeValue(const std::string& name)
{
    if(name == "normal")
    {
        return normal.ToString();
    }
    else if(name == "hover")
    {
        return hover.ToString();
    }
    else if(name == "clicking")
    {
        return clicking.ToString();
    }
    else if(name == "selected")
    {
        return selected.ToString();
    }
    else if(name == "contour")
    {
        return contour.ToString();
    }
    else if(name == "font_color")
    {
        return font_color.ToString();
    }
    else if(name == "corner_radius")
    {
        return std::to_string(round_corner_radius);
    }
    
    return "";
}

void ax::Button::Info::SetAttribute(const ax::StringPair& attribute)
{
    if(attribute.first == "normal")
    {
        normal.LoadFromString(attribute.second);
    }
    else if(attribute.first == "hover")
    {
        hover.LoadFromString(attribute.second);
    }
    else if(attribute.first == "clicking")
    {
        clicking.LoadFromString(attribute.second);
    }
    else if(attribute.first == "selected")
    {
        selected.LoadFromString(attribute.second);
    }
    else if(attribute.first == "contour")
    {
        contour.LoadFromString(attribute.second);
    }
    else if(attribute.first == "font_color")
    {
        font_color.LoadFromString(attribute.second);
    }
    else if(attribute.first == "corner_radius")
    {
        round_corner_radius = std::stoi(attribute.second);
    }
}

/*******************************************************************************
 * ax::Button::Builder.
 ******************************************************************************/
ax::Button::Builder::Builder(axWindow* parent):
axWidgetBuilder(parent),
//_parent(win),
_past(nullptr),
_flags(0)
{
    
}

axWidget* ax::Button::Builder::Create(const ax::StringPairVector& attributes)
{
    std::string name;
    ax::Point pos;
    ax::Button::Events evts;
    axWindow* parent = GetParent();
    
    for(auto& s : attributes)
    {
        if(s.first == "name")
        {
            name = s.second;
        }
        else if(s.first == "rect")
        {
            ax::StringVector strVec;
            strVec = ax::Utils::String::Split(s.second, ",");
            
            pos = ax::Point(stoi(strVec[0]),
                          stoi(strVec[1]));
            
            _size = ax::Size(stoi(strVec[2]),
                           stoi(strVec[3]));
        }
        else if(s.first == "info")
        {
            _info = ax::Button::Info(s.second);
        }
        else if(s.first == "img")
        {
            _img = s.second;
        }
        else if(s.first == "label")
        {
            _label = s.second;
        }
        else if(s.first == "flags")
        {
            _flags = stoi(s.second);
        }
        else if(s.first == std::string("event"))
        {
            evts.button_click = parent->GetEventFunction(s.second);
        }
        else if(s.first == "msg")
        {
            _msg = s.second;
        }
    }
    
    ax::Button* btn = new_ ax::Button(parent, ax::Rect(pos, _size), evts,
                                 _info, _img, _label, _flags, _msg);
    
    parent->GetResourceManager()->Add(name, btn);
    btn->SetBuilderAttributes(attributes);
    return btn;
}

ax::StringVector ax::Button::Builder::GetParamNameList() const
{
    return ax::StringVector
    {
        "name",
        "rect",
        "info",
        "img",
        "label",
        "flags",
        "event",
        "msg"
    };
}

/*******************************************************************************
 * axButon::ax::Button.
 ******************************************************************************/
ax::Button::Button(axWindow* parent,
                   const ax::Rect& rect,
                   const ax::Button::Events& events,
                   const ax::Button::Info& info,
                   std::string img_path,
                   std::string label,
                   axFlag flags,
                   std::string msg):
// Heritage.
axWidget(parent, rect, new_ ax::Button::Info(info)),
// Members.
_events(events),
_label(label),
_flags(flags),
_nCurrentImg(axBTN_NORMAL),
_selected(false),
_msg(msg),
_font(nullptr)
{
    _currentColor = &static_cast<ax::Button::Info*>(_info)->normal;
    
    _btnImg = new_ axImage(img_path);
    
    _font = std::unique_ptr<axFont>(new_ axFont(0));
    
    if(_events.button_click)
    {
        AddConnection(Events::BUTTON_CLICK, _events.button_click);
    }
}

void ax::Button::SetMsg(const std::string& msg)
{
    _msg = msg;
}

void ax::Button::SetSelected(const bool& selected)
{
    if (_selected != selected)
    {
        _selected = selected;
        
        if (_selected)
        {
            if (_currentColor == &static_cast<ax::Button::Info*>(_info)->normal)
            {
                _currentColor = &static_cast<ax::Button::Info*>(_info)->selected;
                Update();
            }
        }
        else
        {
            if (_currentColor == &static_cast<ax::Button::Info*>(_info)->selected)
            {
                _currentColor = &static_cast<ax::Button::Info*>(_info)->normal;
                Update();
            }
        }
    }
}

void ax::Button::SetLabel(const std::string& label)
{
    _label = label;
    Update();
}

void ax::Button::OnMouseLeftDown(const ax::Point& pos)
{
    _currentColor = &static_cast<ax::Button::Info*>(_info)->clicking;
    _nCurrentImg = axBTN_DOWN;
    
    GrabMouse();
    
    PushEvent(Events::BUTTON_CLICK, new_ Msg(this, _msg));
    
    Update();
}

void ax::Button::OnMouseLeftUp(const ax::Point& pos)
{
    if (IsGrabbed())
    {
        UnGrabMouse();
        
        if (IsMouseHoverWindow())
        {
            _currentColor = &static_cast<ax::Button::Info*>(_info)->hover;
            _nCurrentImg = axBTN_HOVER;
            _selected = true;
        }
        else
        {
            if (_selected)
            {
                _currentColor = &static_cast<ax::Button::Info*>(_info)->selected;
                _nCurrentImg = axBTN_SELECTED;
            }
            else
            {
                _currentColor = &static_cast<ax::Button::Info*>(_info)->normal;
                _nCurrentImg = axBTN_NORMAL;
            }
        }
        
        Update();
    }
}

void ax::Button::OnMouseEnter()
{
    axDebug("ax::Button::OnMouseEnter()");
    
    if (!IsGrabbed())
    {
        _currentColor = &static_cast<ax::Button::Info*>(_info)->hover;
        _nCurrentImg = axBTN_HOVER;
        Update();
    }
}

void ax::Button::OnMouseLeave()
{
    if (!IsGrabbed())
    {
        if (_selected)
        {
            _currentColor = &static_cast<ax::Button::Info*>(_info)->selected;
            _nCurrentImg = axBTN_SELECTED;
        }
        else
        {
            _currentColor = &static_cast<ax::Button::Info*>(_info)->normal;
            _nCurrentImg = axBTN_NORMAL;
        }
    }
    
    Update();
}

void ax::Button::OnPaint()
{
    axGC gc = axGC(this);
    
    ax::Rect rect(GetRect());
    ax::Rect rect0(GetDrawingRect());
    
    gc.SetColor(*_currentColor);
    
    int radius = static_cast<ax::Button::Info*>(_info)->round_corner_radius;
    if(radius > 1)
    {
        gc.DrawRoundedRectangle(rect0, radius);
    }
    else
    {
        gc.DrawRectangle(rect0);
    }
    
    
    if (_btnImg->IsImageReady())
    {
        if (IsFlag(Flags::SINGLE_IMG, _flags))
        {
            gc.DrawImageResize(_btnImg, ax::Point(0, 0), rect0.size, 1.0);
        }
        else
        {
            gc.DrawPartOfImage(_btnImg, ax::Point(0, _nCurrentImg * rect.size.y),
                                rect.size, ax::Point(0, 0));
        }
    }
    
    if(!_label.empty())
    {
        gc.SetColor(static_cast<ax::Button::Info*>(_info)->font_color, 1.0);
        gc.DrawStringAlignedCenter(*_font, _label, rect0);
    }
    
    gc.SetColor(static_cast<ax::Button::Info*>(_info)->contour);
    
    
    if(radius > 1)
    {
        gc.DrawRoundedRectangleContour(rect0, radius);
    }
    else
    {
        gc.DrawRectangleContour(rect0);
    }
}


