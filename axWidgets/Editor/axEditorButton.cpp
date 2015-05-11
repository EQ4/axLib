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
#include "axEditorButton.h"

#include "axLabel.h"
#include "axTextBox.h"
#include "axEditorMenu.h"

axDebugButton::axDebugButton(axWindow* parent) :
// Heritage.
axPanel(parent, axRect(axPoint(parent->GetSize().x - 8,
                               parent->GetSize().y - 8),
                       axSize(8, 8))),
// Members.
//_events(events),
_info(axColor(0.9, 0.0, 0.0, 0.6),
      axColor(1.0, 0.0, 0.0, 0.6),
      axColor(0.85, 0.0, 0.0, 0.6),
      axColor(0.9, 0.0, 0.0, 0.6),
      axColor(0.0, 0.0, 0.0, 0.6),
      axColor(0.0, 0.0, 0.0, 0.6)),
_label(""),
_flags(axButton::Flags::SINGLE_IMG),
_selected(false),
_msg(""),
//_isEditing(false),
_font(nullptr)
{
    _currentColor = &_info.normal;
    _font = std::unique_ptr<axFont>(new_ axFont(0));
    
    SetEditingWidget(true);
    SetEditable(false);
}

void axDebugButton::SetMsg(const string& msg)
{
    _msg = msg;
}

void axDebugButton::SetSelected(const bool& selected)
{
    if (_selected != selected)
    {
        _selected = selected;
        
        if (_selected)
        {
            if (_currentColor == &_info.normal)
            {
                _currentColor = &_info.selected;
                Update();
            }
        }
        else
        {
            if (_currentColor == &_info.selected)
            {
                _currentColor = &_info.normal;
                Update();
            }
        }
    }
}

void axDebugButton::SetLabel(const std::string& label)
{
    _label = label;
    Update();
}

void axDebugButton::OnMouseLeftDown(const axPoint& pos)
{
    _currentColor = &_info.clicking;
    
    axWidget* widget = static_cast<axWidget*>(GetParent());
    
    // Prevent from click on the hidden edit button of editing widgets.
    if(!widget->IsEditingWidget() && widget->axWindow::IsEditable())
    {
        
        //axPrint("Ctrl :", );
        GetApp()->SetEditingWidget(widget);
        
        GrabMouse();
        
        PushEvent(axButton::Events::BUTTON_CLICK,
                  new_ axButton::Msg(nullptr, _msg));
        
        Update();
    }
    
}

void axDebugButton::OnMouseLeftDragging(const axPoint &pos)
{
    GetApp()->GetEditor()->UpdateInfo();
    
    
    axWindow* panel = GetParent()->GetParent();
    axRect panelRect = panel->GetAbsoluteRect();
    
    axPoint position(pos);
    position = position - panelRect.position;
    position.x = position.x - GetParent()->GetSize().x + 5;
    position.y = position.y - GetParent()->GetSize().y + 5;


    position.x = axClamp<int>(position.x, 0,
                              panelRect.size.x - GetParent()->GetSize().x);
    
    position.y = axClamp<int>(position.y, 0,
                              panelRect.size.y - GetParent()->GetSize().y);
    
    
    GetParent()->SetPosition(position);
}

void axDebugButton::OnMouseLeftUp(const axPoint& pos)
{
    if (IsGrabbed())
    {
        UnGrabMouse();
        
        if (IsMouseHoverWindow())
        {
            _currentColor = &_info.hover;
            _selected = true;
        }
        else
        {
            if (_selected)
            {
                _currentColor = &_info.selected;
            }
            else
            {
                _currentColor = &_info.normal;
            }
        }
        
        Update();
    }
}

void axDebugButton::OnMouseRightDown(const axPoint& pos)
{

}

void axDebugButton::OnAttributeEdit(const axTextBox::Msg& msg)
{
    axWidget* widget = static_cast<axWidget*>(GetParent());
    
    axVectorPairString attributes;
    
    for(auto& n : _infoEditor)
    {
        std::string name = std::get<0>(n);
        std::string value = std::get<2>(n)->GetLabel();
        attributes.push_back(axStringPair(name, value));
    }
    
    widget->SetInfo(attributes);
}

void axDebugButton::OnKeyDown(const char& key)
{
    axPrint(key);
}

void axDebugButton::OnMouseEnter()
{
    if (!IsGrabbed())
    {
        GrabKey();
        _currentColor = &_info.hover;
        Update();
    }
}

void axDebugButton::OnMouseLeave()
{
    if (!IsGrabbed())
    {
        UnGrabKey();
        if (_selected)
        {
            _currentColor = &_info.selected;
        }
        else
        {
            _currentColor = &_info.normal;
        }
    }
    
    Update();
}

void axDebugButton::OnPaint()
{
    axGC* gc = GetGC();
    axRect rect(GetRect());
    axRect rect0(axPoint(0, 0), rect.size);
    
    gc->SetColor(*_currentColor);
    gc->DrawRectangle(rect0);
    
    gc->SetColor(_info.contour);
    gc->DrawRectangleContour(axRect(axPoint(0, 0), rect.size));
}



