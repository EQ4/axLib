//
//  axFileBrowser.h
//  axDemo
//
//  Created by Alexandre Arsenault on 2015-05-11.
//  Copyright (c) 2015 Alexandre Arsenault. All rights reserved.
//

#ifndef __axDemo__axFileBrowser__
#define __axDemo__axFileBrowser__

#include <axLib/axLib.h>
#include <axEvent/axTimer.h>

namespace ax
{
    class FileBrowser: public axPanel
    {
    public:
        FileBrowser(axWindow* parent, const ax::Rect& rect);
        
//        axEVENT_ACCESSOR(axButton::Msg, OnButtonClick);
        
        axEVENT_ACCESSOR(ax::Event::Timer::Msg, OnTimer);
        
    private:
        ax::Event::Timer* _timer;
        double _rotate;
        
        virtual void OnPaint();
        
        void OnTimer(const ax::Event::Timer::Msg& msg);
        
//        void OnButtonClick(const axButton::Msg& msg);
        
//        virtual void OnResize(const axSize& size);
    };
}


#endif /* defined(__axDemo__axFileBrowser__) */
