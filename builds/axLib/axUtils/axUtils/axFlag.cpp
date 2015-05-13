//
//  axFlag.cpp
//  axUtils
//
//  Created by Alexandre Arsenault on 2015-05-13.
//  Copyright (c) 2015 Alexandre Arsenault. All rights reserved.
//

#include "axFlag.h"

namespace ax
{
    bool IsFlag(const Flag& FLAG, Flag flags)
    {
        return((flags & FLAG) != 0);
    }
    
    namespace FlagValue
    {
        const Flag NO_FLAG = 0;
        const Flag FLAG_1 = 1;
        const Flag FLAG_2 = 2;
        const Flag FLAG_3 = 4;
        const Flag FLAG_4 = 8;
        const Flag FLAG_5 = 16;
        const Flag FLAG_6 = 32;
        const Flag FLAG_7 = 64;
        const Flag FLAG_8 = 128;
        const Flag FLAG_9 = 256;
        const Flag FLAG_10 = 512;
        const Flag FLAG_11 = 1024;
        const Flag FLAG_12 = 2048;
        const Flag FLAG_13 = 4096;
        const Flag FLAG_14 = 8192;
        const Flag FLAG_15 = 16384;
        const Flag FLAG_16 = 32768;
    }
}
