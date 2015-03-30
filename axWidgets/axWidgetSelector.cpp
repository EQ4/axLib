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
#include "axWidgetSelector.h"

/*******************************************************************************
 * axWidgetSelector::Info.
 ******************************************************************************/
axWidgetSelector::Info::Info()
{
    
}

axWidgetSelector::Info::Info(const axColor& color):
_color(color)
{
    
}

/*******************************************************************************
 * axWidgetSelector.
 ******************************************************************************/
axWidgetSelector::axWidgetSelector(axWindow* parent):
axPanel(3, parent, axRect(0, 0, 20, 20)),
_info(axColor(1.0, 0.33, 0.0)),
_selectedWidget(nullptr)
{
    SetSelectable(false);
    SetHasBackBuffer(false);
    Hide();
}

void axWidgetSelector::SetSelectedWidget(axWindow* win)
{
    _selectedWidget = win;
    axRect rect = win->GetAbsoluteRect();
    
    SetPosition(axPoint(rect.position.x - 3, rect.position.y - 3));
    SetSize(axSize(rect.size.x + 6, rect.size.y + 6));
    
    Show();
}

axWindow* axWidgetSelector::GetSelectedWidget()
{
    return _selectedWidget;
}

void axWidgetSelector::OnPaint()
{
    if(_selectedWidget != nullptr && _selectedWidget->IsShown())
    {
        axRect sel_rect = _selectedWidget->GetAbsoluteRect();
        
        SetPosition(axPoint(sel_rect.position.x - 3, sel_rect.position.y - 3));
        SetSize(axSize(sel_rect.size.x + 6, sel_rect.size.y + 6));
        
        axGC* gc = GetGC();
        axRect rect(GetDrawingRect());
        
        gc->SetColor(_info._color, 0.1);
        gc->DrawRectangleContour(rect);
        
        gc->SetColor(_info._color, 0.2);
        gc->DrawRectangleContour(rect.GetInteriorRect(axPoint(0, 0)));
        
        gc->SetColor(_info._color, 0.4);
        gc->DrawRectangleContour(rect.GetInteriorRect(axPoint(1, 1)));
        
        gc->SetColor(_info._color, 0.5);
        gc->DrawRectangleContour(rect.GetInteriorRect(axPoint(2, 2)));
    }

}
