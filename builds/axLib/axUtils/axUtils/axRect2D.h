//
//  axRect2D.h
//  axUtils
//
//  Created by Alexandre Arsenault on 2015-05-12.
//  Copyright (c) 2015 Alexandre Arsenault. All rights reserved.
//

#ifndef __axUtils__axRect2D__
#define __axUtils__axRect2D__

#include "axPoint2D.h"

namespace ax
{
    namespace Utils
    {
        /***********************************************************************
         * ax::Utils::RectPoints.
         **********************************************************************/
        template<typename T>
        struct RectPoints
        {
            RectPoints()
            {
            }
            
            RectPoints(const T& bl,
                       const T& tl,
                       const T& tr,
                       const T& br):
            bottom_left(bl),
            top_left(tl),
            top_right(tr),
            bottom_right(br)
            {
            }
            
            T bottom_left, top_left, top_right, bottom_right;
        };
        
        /*******************************************************************************
         * axTemplateRect.
         ******************************************************************************/
        template < typename CPos, typename CSize, typename T >
        class Rect2D
        {
        public:
            Rect2D(CPos pt_ = CPos(0, 0), CSize size_ = CSize(0, 0)):
            size( size_ ), position( pt_ )
            {
            }
            
            Rect2D(T x, T y, T w, T h):
            position(x, y),
            size(w, h)
            {
            }
            
            CSize size;
            CPos position;
            
            Rect2D operator + (const Rect2D& rect) const
            {
                return Rect2D(position.x + rect.position.x,
                              position.y + rect.position.y,
                              size.x + rect.size.x,
                              size.y + rect.size.y);
            }
            
            Rect2D operator - (const Rect2D& rect) const
            {
                return Rect2D(position.x - rect.position.x,
                              position.y - rect.position.y,
                              size.x - rect.size.x,
                              size.y - rect.size.y);
            }
            
            bool operator == (const Rect2D& rect)
            {
                return (rect.position.x == position.x &&
                        rect.position.y == position.y &&
                        rect.size.x == size.x &&
                        rect.size.y == size.y);
            }
            
            bool operator != (const Rect2D& rect)
            {
                return ( (rect.position.x != position.x ||
                          rect.position.y != position.y) ||
                        ( rect.size.x != size.x ||
                         rect.size.y != size.y ) );
            }
            
            bool operator < (const Rect2D& rect)
            {
                return (size.x < rect.size.x && size.y < rect.size.y);
            }
            
            bool operator <= (const Rect2D& rect)
            {
                return (size.x <= rect.size.x && size.y <= rect.size.y);
            }
            
            bool operator > (const Rect2D& rect)
            {
                return (size.x > rect.size.x && size.y > rect.size.y);
            }
            
            bool operator >= (const Rect2D& rect)
            {
                return (size.x >= rect.size.x && size.y >= rect.size.y);
            }
            
            bool IsPointInside(const CPos& pos)
            {
                return	pos.x >= position.x &&
                pos.x <= position.x + size.x &&
                pos.y >= position.y &&
                pos.y <= position.y + size.y;
            }
            
            Rect2D GetInteriorRect(const CPos& point) const
            {
                return Rect2D(position.x + point.x, position.y + point.y,
                              size.x - (T)(2.0 * point.x),
                              size.y - (T)(2.0 * point.y));
            }
            
            CPos GetTopLeft() const
            {
                return position;
            }
            
            CPos GetTopRight() const
            {
                return CPos(position.x + size.x,
                            position.y);
            }
            
            CPos GetBottomLeft() const
            {
                return CPos(position.x,
                            position.y + size.y);
            }
            
            CPos GetBottomRight() const
            {
                return CPos(position.x + size.x,
                            position.y + size.y);
            }
            
            CPos GetMiddle() const
            {
                return CPos(position.x + size.x * 0.5,
                            position.y + size.y * 0.5);
            }
            
            RectPoints<CPos> GetPoints() const
            {
                return RectPoints<CPos>(CPos(position.x, position.y + size.y),
                                        CPos(position.x, position.y),
                                        CPos(position.x + size.x, position.y),
                                        CPos(position.x + size.x, position.y + size.y));
            }
        };
    }
}

#endif /* defined(__axUtils__axRect2D__) */
