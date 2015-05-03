//
//  FileBrowserElements.cpp
//  axSSH
//
//  Created by Alexandre Arsenault on 2015-04-20.
//  Copyright (c) 2015 Alexandre Arsenault. All rights reserved.
//

#include "FileBrowserElements.h"

FileBrowserElement::FileBrowserElement(axWindow* parent,
                                       const axRect& rect,
                                       const axButton::Events& events,
                                       const axButton::Info& info,
                                       std::string img_path,
                                       std::string label,
                                       axFlag flags,
                                       std::string msg):
// Parent.
axButton(parent, rect, events, info, img_path, label, flags, msg)
{

}

void FileBrowserElement::OnPaint()
{
    axGC gc = axGC(this);
    axRect rect0(GetDrawingRect());
    
    gc.SetColor(*_currentColor);
    gc.DrawRectangle(rect0);
    
    if (_btnImg->IsImageReady())
    {
        gc.DrawImage(_btnImg, axPoint(2, 2));
    }
    
    if_not_empty(_label)
    {
        gc.SetColor(static_cast<axButton::Info*>(_info)->font_color, 1.0);
        gc.DrawString(*_font, _label, axPoint(25, 3));
    }
    
    // DrawContour.
    gc.SetColor(static_cast<axButton::Info*>(_info)->contour);
    gc.DrawRectangleContour(rect0);
}