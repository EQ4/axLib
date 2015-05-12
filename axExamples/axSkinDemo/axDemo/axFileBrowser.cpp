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
    FileBrowser::FileBrowser(axWindow* parent, const ax::Rect& rect):
    // Parent.
    axPanel(parent, rect)
    {
        ax::StringVector dir = ax::Utils::ListDirectory("/Users/alexarse/");
        
        for(auto& n : dir)
        {
            axPrint(n);
        }
    }
    
    void FileBrowser::OnPaint()
    {
        axGC gc(this);
        ax::Rect rect(GetDrawingRect());
        
        gc.SetColor(axColor(0.55));
        gc.DrawRectangle(rect);
        
        gc.SetColor(axColor(0.45));
        gc.DrawRectangleContour(rect);
    }
    
}