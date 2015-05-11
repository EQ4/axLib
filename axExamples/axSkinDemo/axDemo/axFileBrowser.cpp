//
//  axFileBrowser.cpp
//  axDemo
//
//  Created by Alexandre Arsenault on 2015-05-11.
//  Copyright (c) 2015 Alexandre Arsenault. All rights reserved.
//

#include "axFileBrowser.h"

namespace ax
{
    FileBrowser::FileBrowser(axWindow* parent, const axRect& rect):
    // Parent.
    axPanel(parent, rect)
    {
        
    }
    
    void FileBrowser::OnPaint()
    {
        axGC gc(this);
        axRect rect(GetDrawingRect());
        
        gc.SetColor(axColor(0.55));
        gc.DrawRectangle(rect);
        
        gc.SetColor(axColor(0.45));
        gc.DrawRectangleContour(rect);
    }
    
}