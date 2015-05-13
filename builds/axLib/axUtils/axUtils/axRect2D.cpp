//
//  axRect2D.cpp
//  axUtils
//
//  Created by Alexandre Arsenault on 2015-05-12.
//  Copyright (c) 2015 Alexandre Arsenault. All rights reserved.
//

#include "axRect2D.h"

namespace ax
{
    namespace Utils
    {
        template class Rect2D<Point2D<int>, Point2D<int>, int>;
        template class Rect2D<Point2D<double>, Point2D<double>, double>;
    }
}