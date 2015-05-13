//
//  axInterpole.cpp
//  axUtils
//
//  Created by Alexandre Arsenault on 2015-05-12.
//  Copyright (c) 2015 Alexandre Arsenault. All rights reserved.
//

#include "axInterpole.h"

namespace ax
{
    namespace Utils
    {
        namespace Interpole
        {
            template double Lineair<double>(const double&,
                                            const double&,
                                            const double&);
            
            template double Logarithmic<double>(const double&,
                                                const double&,
                                                const double&);
        }
    }
}