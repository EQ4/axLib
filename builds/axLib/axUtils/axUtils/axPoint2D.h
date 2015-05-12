//
//  axPoint2D.h
//  axUtils
//
//  Created by Alexandre Arsenault on 2015-05-12.
//  Copyright (c) 2015 Alexandre Arsenault. All rights reserved.
//

#ifndef __axUtils__axPoint2D__
#define __axUtils__axPoint2D__

namespace ax
{
    namespace Utils
    {
        /***********************************************************************
         * ax::Utils::Point2D.
         **********************************************************************/
        template<typename T>
        class Point2D
        {
        public:
            Point2D(T X = 0, T Y = 0)
            {
                x = X; y = Y;
            }
            
            T x, y;
            
            Point2D operator + (const Point2D& pt) const
            {
                return Point2D(x + pt.x, y + pt.y);
            }
            
            Point2D operator - (const Point2D& pt) const
            {
                return axTemplate2DPoint(x - pt.x, y - pt.y);
            }
            
            Point2D& operator += (const Point2D& pt)
            {
                x += pt.x; y += pt.y; return *this;
            }
            
            Point2D& operator -= (const Point2D& pt)
            {
                x -= pt.x; y -= pt.y; return *this;
            }
            
            Point2D& operator = (const T& pt)
            {
                x = pt; y = pt; return *this;
            }
            
            Point2D& operator = (const Point2D& pt)
            {
                x = pt.x; y = pt.y; return *this;
            }
            
            bool operator == (const Point2D& pt)
            { return (x == pt.x && y == pt.y); }
            
            bool operator != (const Point2D& pt)
            { return !(x == pt.x && y == pt.y); }
            
            bool operator < (const Point2D& pt)
            { return (x < pt.x && y < pt.y); }
            
            bool operator <= (const Point2D& pt)
            { return (x <= pt.x && y <= pt.y); }
            
            bool operator > (const Point2D& pt)
            { return (x > pt.x && y > pt.y); }
            
            bool operator >= (const Point2D& pt)
            { return (x >= pt.x && y >= pt.y); }
            
            Point2D& operator()(const T& X, const T& Y)
            {
                x = X;
                y = Y;
                return *this;
            }
        };
    }
}


#endif /* defined(__axUtils__axPoint2D__) */
