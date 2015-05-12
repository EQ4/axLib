//
//  axInterpole.h
//  axUtils
//
//  Created by Alexandre Arsenault on 2015-05-12.
//  Copyright (c) 2015 Alexandre Arsenault. All rights reserved.
//

#ifndef __axUtils__axInterpole__
#define __axUtils__axInterpole__


#include <cmath>

namespace ax
{
    namespace Utils
    {
        namespace Interpole
        {
            template <typename T>
            T Lineair(const T& y1, const T& y2, const T& mu)
            {
                return y1 + mu * (y2 - y1);
            }
            
            template <typename T>
            T Logarithmic(const T& y1, const T& y2, const T& mu)
            {
                return pow(y2, mu) * pow(y1, 1.0 - mu);
            }
        }
    }
}

#endif /* defined(__axUtils__axInterpole__) */
