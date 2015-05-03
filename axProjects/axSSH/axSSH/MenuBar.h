//
//  MenuBar.h
//  axSSH
//
//  Created by Alexandre Arsenault on 2015-04-21.
//  Copyright (c) 2015 Alexandre Arsenault. All rights reserved.
//

#ifndef __axSSH__MenuBar__
#define __axSSH__MenuBar__

#include <axLib/axLib.h>

class MenuBar : public axPanel
{
public:
    MenuBar(axWindow* parent, const axRect& rect);
    
private:
    virtual void OnPaint();
};

#endif /* defined(__axSSH__MenuBar__) */
