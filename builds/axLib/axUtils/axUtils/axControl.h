//
//  axControl.h
//  axUtils
//
//  Created by Alexandre Arsenault on 2015-05-12.
//  Copyright (c) 2015 Alexandre Arsenault. All rights reserved.
//

#ifndef __axUtils__axControl__
#define __axUtils__axControl__

namespace ax
{
    namespace Utils
    {
        namespace Control
        {
            /*******************************************************************
             * ax::Utils::Control::Type.
             ******************************************************************/
            enum Type
            {
                axCTRL_NO_TYPE,
                axCTRL_FLOAT,
                axCTRL_INT,
                axCTRL_PAN
            };
            
            /*******************************************************************
             * ax::Utils::Control::Unit.
             ******************************************************************/
            enum Unit
            {
                axCTRL_NO_UNIT,
                axCTRL_HERTZ,
                axCTRL_DECIBEL,
                axCTRL_TIME_MS,
                axCTRL_TIME_SEC
            };
            
            /*******************************************************************
             * ax::Utils::Control::Interpolation.
             ******************************************************************/
            enum Interpolation
            {
                axCTRL_LINEAR,
                axCTRL_EXPONENTIAL,
                axCTRL_LOGARITHME
            };
        }
    }
}
#endif /* defined(__axUtils__axControl__) */
