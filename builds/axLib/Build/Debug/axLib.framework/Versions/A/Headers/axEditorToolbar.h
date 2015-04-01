//
//  axEditorToolbar.h
//  axLib
//
//  Created by Alexandre Arsenault on 2015-03-31.
//  Copyright (c) 2015 Alexandre Arsenault. All rights reserved.
//

#ifndef __axLib__axEditorToolbar__
#define __axLib__axEditorToolbar__

#include "axLib.h"

class axEditorToolbar : public axPanel
{
public:
    axEditorToolbar(axWindow* parent, const axRect& rect,
                    const axButton::Events& evt);
    
    
    
private:
    
    
    virtual void OnPaint();
};


#endif /* defined(__axLib__axEditorToolbar__) */
