//
//  axEditorToolbar.cpp
//  axLib
//
//  Created by Alexandre Arsenault on 2015-03-31.
//  Copyright (c) 2015 Alexandre Arsenault. All rights reserved.
//

#include "axEditorToolbar.h"

axEditorToolbar::axEditorToolbar(axWindow* parent, const axRect& rect,
                                 const axButton::Events& evt):
axPanel(parent, rect)
{
    axButton::Info btn_info;
    btn_info.normal = axColor(0.7, 0.7, 0.7, 0.3);
    btn_info.hover = axColor(0.9, 0.9, 0.9, 0.3);
    btn_info.clicking = axColor(0.8, 0.8, 0.8, 0.3);
    btn_info.contour = axColor(0.0, 0.0, 0.0, 1.0);
    btn_info.selected = btn_info.normal;
    btn_info.round_corner_radius = 3;
    
    axButton* btn1 = new axButton(this,
                                  axRect(10, 7, 60, 26),
                                  evt,
                                  btn_info,
                                  "", "Widgets", axNO_FLAG, "Widgets");
    
    btn1->SetEditingWidget(true);
    btn1->SetEditable(false);
    
    axButton* btn2 = new axButton(this,
                                  axRect(btn1->GetNextPosRight(10), axSize(60, 26)),
                                  evt,
                                  btn_info,
                                  "", "Attributes", axNO_FLAG, "Attributes");
    
    btn2->SetEditingWidget(true);
    btn2->SetEditable(false);
}

void axEditorToolbar::OnPaint()
{
    axGC gc(this);
    axRect rect(GetDrawingRect());
    
    gc.DrawRectangleColorFade(rect, axColor(0.8), axColor(0.7));
    
    gc.SetColor(axColor(0.0));
    gc.DrawRectangleContour(rect);
//    gc.DrawRectangleColorFade(axRect(0, 0, rect.size.x, 40),
//                              axColor(0.6), axColor(0.9));
}