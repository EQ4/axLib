//
//  axDirection.h
//  axUtils
//
//  Created by Alexandre Arsenault on 2015-05-12.
//  Copyright (c) 2015 Alexandre Arsenault. All rights reserved.
//

#ifndef __axUtils__axDirection__
#define __axUtils__axDirection__

namespace ax
{
    namespace Utils
    {
        /***********************************************************************
         * ax::Utils::Direction.
         **********************************************************************/
        enum Direction
        {
            axDIRECTION_LEFT,
            axDIRECTION_UP,
            axDIRECTION_RIGHT,
            axDIRECTION_DOWN
        };
        
        /***********************************************************************
         * ax::Utils::Alignement.
         **********************************************************************/
        enum Alignement
        {
            axALIGN_LEFT,
            axALIGN_CENTER,
            axALIGN_RIGHT
        };
    }
}

#endif /* defined(__axUtils__axDirection__) */
