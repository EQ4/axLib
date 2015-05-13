//
//  axClamp.cpp
//  axUtils
//
//  Created by Alexandre Arsenault on 2015-05-12.
//  Copyright (c) 2015 Alexandre Arsenault. All rights reserved.
//

#include "axClamp.h"

template int ax::Utils::Clamp<int>(int, int, int);
template double ax::Utils::Clamp<double>(double, double, double);
