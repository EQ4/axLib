//
//  FileBrowserElements.h
//  axSSH
//
//  Created by Alexandre Arsenault on 2015-04-20.
//  Copyright (c) 2015 Alexandre Arsenault. All rights reserved.
//

#ifndef __axSSH__FileBrowserElements__
#define __axSSH__FileBrowserElements__

#include <axLib/axLib.h>

class FileBrowserElement : public axButton
{
public:
    FileBrowserElement(axWindow* parent,
                       const axRect& rect,
                       const axButton::Events& events,
                       const axButton::Info& info,
                       std::string img_path = "",
                       std::string label = "",
                       axFlag flags = 0,
                       std::string msg = "");

private:
    axStringVector _files;
    
    virtual void OnPaint();
};

#endif /* defined(__axSSH__FileBrowserElements__) */
