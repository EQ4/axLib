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

//namespace ax
//{
//    class FileBrowser;
//}

class MainPanel : public axPanel
{
public:
    MainPanel(ax::App* app, const ax::Rect& rect);
    
    axEVENT_ACCESSOR(ax::Button::Msg, OnButtonClick);
    axEVENT_ACCESSOR(ax::Event::SimpleMsg<double>, OnLoadSampleProcess);
    
private:
//    ax::FileBrowser* _fileBrowser;
    virtual void OnPaint();
    
    double _loadPercent;
    
    void OnButtonClick(const ax::Button::Msg& msg);
    void OnLoadSampleProcess(const ax::Event::SimpleMsg<double>& msg);
    
    virtual void OnResize(const ax::Size& size);
    
};


#endif /* defined(__Demo__main__) */
