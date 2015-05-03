//
//  MenuBar.cpp
//  axSSH
//
//  Created by Alexandre Arsenault on 2015-04-21.
//  Copyright (c) 2015 Alexandre Arsenault. All rights reserved.
//

#include "MenuBar.h"

MenuBar::MenuBar(axWindow* parent, const axRect& rect):
// Parent.
axPanel(parent, rect)
{
    axApp* app = GetApp();
    std::string btnInfoPath(app->GetResourceFile("axButtonInfo.axobj"));
    
    axButton::Info btnInfo;
    btnInfo.normal = axColor::axTransparentColor;
    btnInfo.hover = axColor::axTransparentColor;
    btnInfo.selected = btnInfo.normal;
    btnInfo.contour = axColor::axTransparentColor;
    

    
    
    axButton* btn = new axButton(this, axRect(5, 5, 32, 32),
                                 axButton::Events(),
                                 btnInfo,
                                 "folderBig.png");
}

void MenuBar::OnPaint()
{
    axGC& gc(*GetGC());
    axRect rect0(GetDrawingRect());
    
    gc.SetColor(axColor(0.93));
    gc.DrawRectangle(rect0);
    
    gc.SetColor(axColor::axBlackColor);
    gc.DrawRectangleContour(rect0);
}