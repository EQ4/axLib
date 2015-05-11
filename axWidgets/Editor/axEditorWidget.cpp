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
                               const axRect& rect,
                               const std::string& label) :
// Heritage.
axPanel(parent, rect),
// Members.
//_events(events),
_info(axColor(0.7),
      axColor(0.78),
      axColor(0.74),
      axColor(0.7),
      axColor(0.0),
      axColor(0.0)),
_label(label),
_flags(axButton::Flags::SINGLE_IMG),
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

void axEditorWidget::SetMsg(const string& msg)
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

void axEditorWidget::OnMouseLeftDown(const axPoint& pos)
{
    _currentColor = &_info.clicking;
    
    GrabMouse();
    
    
        
//    PushEvent(axButton::Events::BUTTON_CLICK,
//              new_ axButton::Msg(nullptr, _msg));
    
    Update();
    
    
}

void axEditorWidget::OnMouseLeftDragging(const axPoint &pos)
{
//    axApp::GetInstance()->GetEditor()->UpdateInfo();
//    
//    
//    axWindow* panel = GetParent()->GetParent();
//    axRect panelRect = panel->GetAbsoluteRect();
//    
//    axPoint position(pos);
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

void axEditorWidget::OnMouseLeftUp(const axPoint& pos)
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
            axPrint(id, win->GetWindowType());
            
            if(win->GetWindowType() == axWindowType::axWINDOW_TYPE_PANEL)
            {
                axButton::Info btn_info;
                btn_info.normal = axColor(0.7, 0.7, 0.7, 0.3);
                btn_info.hover = axColor(0.9, 0.9, 0.9, 0.3);
                btn_info.clicking = axColor(0.8, 0.8, 0.8, 0.3);
                btn_info.contour = axColor(0.0, 0.0, 0.0, 1.0);
                btn_info.selected = btn_info.normal;
                btn_info.round_corner_radius = 3;
                
                axPoint rel_pos = pos - win->GetAbsoluteRect().position;
                
                axButton* btn1 = new axButton(win,
                                              axRect(rel_pos, axSize(60, 26)),
                                              axButton::Events(),
                                              btn_info,
                                              "", "Widgets",
                                              axNO_FLAG, "Widgets");
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

void axEditorWidget::OnMouseRightDown(const axPoint& pos)
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
    axRect rect(GetDrawingRect());
    
//    gc->SetColor(*_currentColor);
//    gc->DrawRectangle(rect);
    
    gc->DrawRectangleColorFade(rect, axColor(0.95), axColor(0.9));
    
    gc->SetColor(0.0);
    gc->DrawRectangleContour(axRect(5, 5, 40, 30));
    
    gc->DrawString(_fontBold, _label, axPoint(50, 12));
    
    gc->DrawString(_font, "Simple button (60x26)", axPoint(120, 12));

    
    gc->SetColor(_info.contour);
    gc->DrawRectangleContour(rect);
}



