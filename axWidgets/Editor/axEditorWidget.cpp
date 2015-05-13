//
//  axEditorWidget.cpp
//  axLib
//
//  Created by Alexandre Arsenault on 2015-04-01.
//  Copyright (c) 2015 Alexandre Arsenault. All rights reserved.
//

#include "axEditorWidget.h"
#include "axButton.h"

axEditorWidget::axEditorWidget(axWindow* parent,
                               const ax::Rect& rect,
                               const std::string& label) :
// Heritage.
axPanel(parent, rect),
// Members.
//_events(events),
_info(ax::Color(0.7),
      ax::Color(0.78),
      ax::Color(0.74),
      ax::Color(0.7),
      ax::Color(0.0),
      ax::Color(0.0)),
_label(label),
_flags(ax::Button::Flags::SINGLE_IMG),
_selected(false),
_msg(""),
//_isEditing(false),
_font(0),
_fontBold("FreeSansBold.ttf")
{
    _currentColor = &_info.normal;
    
    SetEditingWidget(true);
    SetEditable(false);
}

void axEditorWidget::SetMsg(const std::string& msg)
{
    _msg = msg;
}

void axEditorWidget::SetSelected(const bool& selected)
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

void axEditorWidget::SetLabel(const std::string& label)
{
    _label = label;
    Update();
}

void axEditorWidget::OnMouseLeftDown(const ax::Point& pos)
{
    _currentColor = &_info.clicking;
    
    GrabMouse();
    
    
        
//    PushEvent(axButton::Events::BUTTON_CLICK,
//              new_ axButton::Msg(nullptr, _msg));
    
    Update();
    
    
}

void axEditorWidget::OnMouseLeftDragging(const ax::Point &pos)
{
//    axApp::GetInstance()->GetEditor()->UpdateInfo();
//    
//    
//    axWindow* panel = GetParent()->GetParent();
//    ax::Rect panelRect = panel->GetAbsoluteRect();
//    
//    ax::Point position(pos);
//    position = position - panelRect.position;
//    position.x = position.x - GetParent()->GetSize().x + 5;
//    position.y = position.y - GetParent()->GetSize().y + 5;
//    
//    
//    position.x = axClamp<int>(position.x, 0,
//                              panelRect.size.x - GetParent()->GetSize().x);
//    
//    position.y = axClamp<int>(position.y, 0,
//                              panelRect.size.y - GetParent()->GetSize().y);
//    
//    
//    GetParent()->SetPosition(position);
}

void axEditorWidget::OnMouseLeftUp(const ax::Point& pos)
{
    if (IsGrabbed())
    {
        UnGrabMouse();
        
        
        // Find panel under mouse.
        
        axManager* manager = GetApp()->GetCore()->GetWindowManager();
        axWindow* win = manager->GetWindowTree()->FindMousePosition(pos);
        
        
        int id = win != nullptr ? win->GetId() : -1;
        
        if(id != -1)
        {
//            ax::Print(id, win->GetWindowType());
            
            if(win->GetWindowType() == axWindowType::axWINDOW_TYPE_PANEL)
            {
                ax::Button::Info btn_info;
                btn_info.normal = ax::Color(0.7, 0.7, 0.7, 0.3);
                btn_info.hover = ax::Color(0.9, 0.9, 0.9, 0.3);
                btn_info.clicking = ax::Color(0.8, 0.8, 0.8, 0.3);
                btn_info.contour = ax::Color(0.0, 0.0, 0.0, 1.0);
                btn_info.selected = btn_info.normal;
                btn_info.round_corner_radius = 3;
                
                ax::Point rel_pos = pos - win->GetAbsoluteRect().position;
                
                ax::Button* btn1 = new ax::Button(win,
                                                  ax::Rect(rel_pos, ax::Size(60, 26)),
                                                  ax::Button::Events(),
                                                  btn_info,
                                                  "", "Widgets",
                                                  ax::FlagValue::NO_FLAG,
                                                  "Widgets");
            }
        }
        
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

void axEditorWidget::OnMouseRightDown(const ax::Point& pos)
{
    
}

void axEditorWidget::OnMouseEnter()
{
    if (!IsGrabbed())
    {
        GrabKey();
        _currentColor = &_info.hover;
        Update();
    }
}

void axEditorWidget::OnMouseLeave()
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

void axEditorWidget::OnPaint()
{
    axGC* gc = GetGC();
    ax::Rect rect(GetDrawingRect());
    
//    gc->SetColor(*_currentColor);
//    gc->DrawRectangle(rect);
    
    gc->DrawRectangleColorFade(rect, ax::Color(0.95), ax::Color(0.9));
    
    gc->SetColor(0.0);
    gc->DrawRectangleContour(ax::Rect(5, 5, 40, 30));
    
    gc->DrawString(_fontBold, _label, ax::Point(50, 12));
    
    gc->DrawString(_font, "Simple button (60x26)", ax::Point(120, 12));

    
    gc->SetColor(_info.contour);
    gc->DrawRectangleContour(rect);
}



