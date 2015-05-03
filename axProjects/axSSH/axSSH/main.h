//
//  main.h
//  axSSH
//
//  Created by Alexandre Arsenault on 2015-04-20.
//  Copyright (c) 2015 Alexandre Arsenault. All rights reserved.
//

#ifndef __axSSH__main__
#define __axSSH__main__

#include <axLib/axLib.h>

class axSSH;
class FileBrowser;
class MenuBar;

class MainPanel : public axPanel
{
public:
    MainPanel(axWindow* parent, const axRect& rect);
    
    
    axEVENT_ACCESSOR(axButton::Msg, OnConnectButton);
private:
//    axTextBox *_ipTxtBox, *_pwordtxtBox, *_commandtxtBox;
//    axSSH* _ssh;
    FileBrowser* _fileBrowser;
//    axScrollBar* _scrollBar;
    MenuBar* _menuBar;
    
//    axImage* _bgImg;
//    axPanel* _connectionPanel;
    
    virtual void OnPaint();
    
    void OnConnectButton(const axButton::Msg& msg);
    
};


#endif /* defined(__axSSH__main__) */
