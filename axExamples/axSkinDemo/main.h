//
//  main.h
//  Demo
//
//  Created by Alexandre Arsenault on 2014-11-02.
//  Copyright (c) 2014 Alexandre Arsenault. All rights reserved.
//

#ifndef __Demo__main__
#define __Demo__main__

#include <axLib/axLib.h>
//#include "axLib.h"

class MainPanel : public axPanel
{
public:
    MainPanel(axWindow* parent, const axRect& rect);
    

private:
    virtual void OnPaint();
    
};


#endif /* defined(__Demo__main__) */
