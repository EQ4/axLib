//
//  axEditorWidgets.cpp
//  axLib
//
//  Created by Alexandre Arsenault on 2015-04-01.
//  Copyright (c) 2015 Alexandre Arsenault. All rights reserved.
//

#include "axEditorWidgetsPanel.h"
#include "axEditorWidget.h"

axEditorWidgetsPanel::axEditorWidgetsPanel(axWindow* parent, const ax::Rect& rect):
axPanel(parent, rect)
{
//    SetBlockDrawing(true);
    
    ax::Size btnSize(rect.size.x, 40);
    axEditorWidget* btn1 = new axEditorWidget(this,
                                              ax::Rect(ax::Point(0, 0), btnSize),
                                              "Button");
    
    axEditorWidget* btn2 = new axEditorWidget(this,
                                  ax::Rect(btn1->GetNextPosDown(0), btnSize),
                                              "Toggle");
    
    axEditorWidget* btn3 = new axEditorWidget(this,
                                  ax::Rect(btn2->GetNextPosDown(0), btnSize),
                                              "Number");
    
    axEditorWidget* btn4 = new axEditorWidget(this,
                                  ax::Rect(btn3->GetNextPosDown(0), btnSize),
                                              "Knob");
    
    axEditorWidget* btn5 = new axEditorWidget(this,
                                  ax::Rect(btn4->GetNextPosDown(0), btnSize),
                                              "Slider");

    btn1->SetEditingWidget(true);
    btn1->SetEditable(false);
    
    btn2->SetEditingWidget(true);
    btn2->SetEditable(false);
    
    btn3->SetEditingWidget(true);
    btn3->SetEditable(false);
    
    btn4->SetEditingWidget(true);
    btn4->SetEditable(false);
    
    btn5->SetEditingWidget(true);
    btn5->SetEditable(false);
}

void axEditorWidgetsPanel::OnPaint()
{
//    axGC gc(this);
    ax::GC gc;
    ax::Rect rect(GetDrawingRect());
    
//    gc.DrawRectangleColorFade(rect, ax::Color(0.8), ax::Color(0.7));
//    
//    gc.SetColor(ax::Color(0.0));
    gc.DrawRectangleContour(rect);
    //    gc.DrawRectangleColorFade(ax::Rect(0, 0, rect.size.x, 40),
    //                              axColor(0.6), axColor(0.9));
}