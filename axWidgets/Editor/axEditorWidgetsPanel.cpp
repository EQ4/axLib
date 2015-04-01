//
//  axEditorWidgets.cpp
//  axLib
//
//  Created by Alexandre Arsenault on 2015-04-01.
//  Copyright (c) 2015 Alexandre Arsenault. All rights reserved.
//

#include "axEditorWidgetsPanel.h"
#include "axEditorWidget.h"

axEditorWidgetsPanel::axEditorWidgetsPanel(axWindow* parent, const axRect& rect):
axPanel(parent, rect)
{
    axSize btnSize(50, 50);
    axEditorWidget* btn1 = new axEditorWidget(this,
                                              axRect(axPoint(8, 7), btnSize),
                                              "Button");
    
    axEditorWidget* btn2 = new axEditorWidget(this,
                                  axRect(btn1->GetNextPosRight(6), btnSize),
                                              "Toggle");
    
    axEditorWidget* btn3 = new axEditorWidget(this,
                                  axRect(btn2->GetNextPosRight(6), btnSize),
                                              "Number");
    
    axEditorWidget* btn4 = new axEditorWidget(this,
                                  axRect(btn3->GetNextPosRight(6), btnSize),
                                              "Knob");
    
    axEditorWidget* btn5 = new axEditorWidget(this,
                                  axRect(btn4->GetNextPosRight(6), btnSize),
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
    axGC gc(this);
    axRect rect(GetDrawingRect());
    
    gc.DrawRectangleColorFade(rect, axColor(0.8), axColor(0.7));
    
    gc.SetColor(axColor(0.0));
    gc.DrawRectangleContour(rect);
    //    gc.DrawRectangleColorFade(axRect(0, 0, rect.size.x, 40),
    //                              axColor(0.6), axColor(0.9));
}