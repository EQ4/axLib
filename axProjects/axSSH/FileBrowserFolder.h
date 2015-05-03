//
//  FileBrowser.h
//  axSSH
//
//  Created by Alexandre Arsenault on 2015-04-20.
//  Copyright (c) 2015 Alexandre Arsenault. All rights reserved.
//

#ifndef __axSSH__FileBrowser__
#define __axSSH__FileBrowser__

#include <axLib/axLib.h>
//#include "axSSH.h"

class FileBrowserFolder : public axPanel
{
public:
    FileBrowserFolder(axWindow* parent, const axRect& rect);
    
//    void SetSSHHandle(axSSH* ssh);
    
    void ListFile(const std::string& path, const std::string& selected_folder);
    
    
//    axEVENT_ACCESSOR(axButton::Msg, OnButtonClick);
    
private:
    virtual void OnPaint();
    axStringVector _files;
    std::string _currentFolder;
    axFont _font;
    
//    void OnButtonClick(const axButton::Msg& msg);
    
    std::vector<axButton*> _folders;
    axPanel* _scrolled_panel;
    
//    axSSH* _ssh;
};

#endif /* defined(__axSSH__FileBrowser__) */
