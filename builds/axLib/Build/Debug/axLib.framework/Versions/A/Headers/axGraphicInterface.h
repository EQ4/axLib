//
//  axGraphicInterface.h
//  axLib
//
//  Created by Alexandre Arsenault on 2015-02-17.
//  Copyright (c) 2015 Alexandre Arsenault. All rights reserved.
//

#ifndef __axLib__axGraphicInterface__
#define __axLib__axGraphicInterface__

#include "axC++.h"

class axWindow;

namespace axGraphicInterface
{
    void Resize(const ax::Size& size);
    
    void Init();
    
    void Draw(const ax::Size& size);
}

#endif /* defined(__axLib__axGraphicInterface__) */
