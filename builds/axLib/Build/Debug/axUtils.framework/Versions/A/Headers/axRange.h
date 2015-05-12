//
//  axRange.h
//  axUtils
//
//  Created by Alexandre Arsenault on 2015-05-12.
//  Copyright (c) 2015 Alexandre Arsenault. All rights reserved.
//

#ifndef __axUtils__axRange__
#define __axUtils__axRange__


namespace ax
{
    namespace Utils
    {
        /***********************************************************************
         * ax::Utils::Range.
         **********************************************************************/
        template < typename T >
        struct Range
        {
            Range()
            {
            }
            
            Range(const T& minimum, const T& maximum) :
            left( minimum ),
            right( maximum )
            {
            }
            
            double GetZeroToOneValue(const double& value) const
            {
                double v = double(value - left) / double(right - left);
                if(v > 1.0) v = 1.0;
                if(v < 0.0) v = 0.0;
                
                return v;
            }
            
            double GetValueFromZeroToOne(const double& value)
            {
                double v = double(left) + value * double(right - left);
                if(v > right) v = right;
                if(v < left) v = left;
                return v;
            }
            
            T left, right;
        };
    }
}


#endif /* defined(__axUtils__axRange__) */
