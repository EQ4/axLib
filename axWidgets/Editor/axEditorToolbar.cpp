//
//  axEditorToolbar.cpp
//  axLib
//
//  Created by Alexandre Arsenault on 2015-03-31.
//  Copyright (c) 2015 Alexandre Arsenault. All rights reserved.
//

#include "axEditorToolbar.h"

axEditorToolbar::axEditorToolbar(axWindow* parent, const ax::Rect& rect,
                                 const ax::Button::Events& evt):
axPanel(parent, rect)
{
    ax::Button::Info btn_info;
    btn_info.normal = ax::Color(0.7, 0.7, 0.7, 0.3);
    btn_info.hover = ax::Color(0.9, 0.9, 0.9, 0.3);
    btn_info.clicking = ax::Color(0.8, 0.8, 0.8, 0.3);
    btn_info.contour = ax::Color(0.0, 0.0, 0.0, 1.0);
    btn_info.selected = btn_info.normal;
    btn_info.round_corner_radius = 3;
    
    ax::Button* btn1 = new ax::Button(this,
                                  ax::Rect(10, 7, 60, 26),
                                  evt,
                                  btn_info,
                                  "", "Widgets", ax::FlagValue::NO_FLAG, "Widgets");
    
    btn1->AddProperty("EditingWidget");
//    btn1->SetEditingWidget(true);
//    btn1->SetEditable(false);
    
    ax::Button* btn2 = new ax::Button(this,
                                  ax::Rect(btn1->GetRect().GetNextPosRight(10), ax::Size(60, 26)),
                                  evt,
                                  btn_info,
                                  "", "Attributes", ax::FlagValue::NO_FLAG, "Attributes");
    
    btn2->AddProperty("EditingWidget");
//    btn2->SetEditingWidget(true);
//    btn2->SetEditable(false);
}

void axEditorToolbar::OnPaint()
{
    ax::GC gc;
    ax::Rect rect(GetDrawingRect());
    
//    gc.DrawRectangleColorFade(rect, ax::Color(0.8), ax::Color(0.7));
//    
//    gc.SetColor(ax::Color(0.0));
    gc.DrawRectangleContour(rect);
//    gc.DrawRectangleColorFade(ax::Rect(0, 0, rect.size.x, 40),
//                              ax::Color(0.6), ax::Color(0.9));
}