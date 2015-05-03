//
//  axFileBrowser.h
//  axSSH
//
//  Created by Alexandre Arsenault on 2015-04-20.
//  Copyright (c) 2015 Alexandre Arsenault. All rights reserved.
//

#ifndef __axSSH__axFileBrowser__
#define __axSSH__axFileBrowser__

#include <axLib/axLib.h>
#include "FileBrowserFolder.h"

class axSSH;

class FileBrowser : public axPanel
{
public:
    FileBrowser(axWindow* parent, const axRect& rect);
    
//    void SetSSHHandle(axSSH* ssh);
    
    void ListFile(const std::string& path);
    
    axEVENT_ACCESSOR(axButton::Msg, OnButtonClick);
    
private:
    virtual void OnPaint();
    
    std::vector<FileBrowserFolder*> _folders;
    void OnButtonClick(const axButton::Msg& msg);

    axStringVector _files;
//    axSSH* _ssh;
};

#endif /* defined(__axSSH__axFileBrowser__) */
