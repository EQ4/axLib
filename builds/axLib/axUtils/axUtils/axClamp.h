//
//  axClamp.h
//  axUtils
//
//  Created by Alexandre Arsenault on 2015-05-12.
//  Copyright (c) 2015 Alexandre Arsenault. All rights reserved.
//

#ifndef __axUtils__axClamp__
#define __axUtils__axClamp__

namespace ax
{
    namespace Utils
    {
        /***********************************************************************
         * ax::Utils::Clamp.
         **********************************************************************/
        template<typename T>
        T axClamp(T d, T min, T max)
        {
            const T t = d < min ? min : d;
            return t > max ? max : t;
        }
    }
}


#endif /* defined(__axUtils__axClamp__) */
