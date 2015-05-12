//
//  axUtils.h
//  axUtils
//
//  Created by Alexandre Arsenault on 2015-05-12.
//  Copyright (c) 2015 Alexandre Arsenault. All rights reserved.
//

#include "axRect2D.h"
#include "axRange.h"
#include "axInterpole.h"
#include "axClamp.h"
#include "axString.h"
#include "axControl.h"
#include "axDirection.h"

namespace ax
{
    // ax::Point
    typedef Utils::Point2D<int> Point;
    
    // ax::FloatPoint
    typedef Utils::Point2D<double> FloatPoint;
    
    // ax::Size
    typedef Utils::Point2D<int> Size;
    
    // ax::FloatSize
    typedef Utils::Point2D<double> FloatSize;
    
    // ax::Rect
    typedef Utils::Rect2D<Point, Size, int> Rect;
    
    // ax::FloatRect
    typedef Utils::Rect2D<FloatPoint, FloatSize, double> FloatRect;
    
    // ax::FloatRange
    typedef Utils::Range<double> FloatRange;
    
    // ax::IntRange
    typedef Utils::Range<int> IntRange;
    
    // ax::StringPair
    typedef Utils::String::Pair StringPair;
    
    // ax::StringPairVector
    typedef Utils::String::PairVector StringPairVector;
    
    // ax::StringVector
    typedef Utils::String::Vector StringVector;
}


