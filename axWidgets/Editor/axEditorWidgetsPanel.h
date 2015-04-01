//
//  axEditorWidgets.h
//  axLib
//
//  Created by Alexandre Arsenault on 2015-04-01.
//  Copyright (c) 2015 Alexandre Arsenault. All rights reserved.
//

#ifndef __axLib__axEditorWidgets__
#define __axLib__axEditorWidgets__


#include "axLib.h"

class axEditorWidgetsPanel : public axPanel
{
public:
    axEditorWidgetsPanel(axWindow* parent, const axRect& rect);
    
private:
    
    virtual void OnPaint();
};

#endif /* defined(__axLib__axEditorWidgets__) */
