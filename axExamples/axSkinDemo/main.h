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

namespace ax
{
    class FileBrowser;
}

class MainPanel : public axPanel
{
public:
    MainPanel(axApp* app, const axRect& rect);
    
    axEVENT_ACCESSOR(axButton::Msg, OnButtonClick);
    
private:
    ax::FileBrowser* _fileBrowser;
    virtual void OnPaint();
    
    void OnButtonClick(const axButton::Msg& msg);
    
    virtual void OnResize(const axSize& size);
    
};


#endif /* defined(__Demo__main__) */
