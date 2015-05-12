/*******************************************************************************
 * Copyright (c) 2013 Alexandre Arsenault.
 *
 * This file is part of axLibrary.
 *
 * axLibrary is free or commercial software: you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 or any later version of the
 * License or use a commercial axLibrary License.
 *
 * axLibrary is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with axLibrary. If not, see <http://www.gnu.org/licenses/>.
 *
 * To release a closed-source product which uses axLibrary, commercial
 * licenses are available, email alx.arsenault@gmail.com for more information.
 ******************************************************************************/
#ifndef __AX_EVENT__
#define __AX_EVENT__

/// @defgroup Event
/// @{

#include <functional>
#include "axMsg.h"

namespace ax
{
    namespace Event
    {
        typedef unsigned int Id;
        
        typedef std::function<void(ax::Event::Msg*)> Function;
        
        #define axEVENT_ACCESSOR(TYPE, FUNC) ax::Event::Function Get ## FUNC() \
        { return [=](ax::Event::Msg* x) \
        { return this->FUNC(*static_cast<TYPE*>(x)); }; }
        
        class axBindedEvent
        {
        public:
            axBindedEvent(Function& fct, Msg* msg):
            _fct(fct), _msg(msg){}
            
            void operator() (void) { _fct(_msg); delete _msg; }
            
        private:
            Function _fct;
            Msg* _msg;
        };
    }
}

/// @}
#endif //__AX_EVENT__
