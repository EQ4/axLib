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

#ifndef _AX_OBJECT_
#define _AX_OBJECT_

/*******************************************************************************
 * @file    axObject.h
 * @author  Alexandre Arsenault <alx.arsenault@gmail.com>
 * @date    17/02/2015
 ******************************************************************************/

/// @defgroup Core
/// @{

#include <axEvent/axEvent.h>
#include <string>
#include <map>
#include <iostream>

namespace ax
{
//    class App;
    
    namespace Event
    {
        class Manager;
        
        typedef unsigned int ID;
        
        /// Id from axObject are used has unique identifier in axEventManager.
        class Object
        {
        public:
            Object() = delete;
            
            Object(Manager* evtManager);
            
            /// Add a function to the EventManager.
            void AddConnection(const Id& evtId, Function fct) const;
                               
            /// Add the function to the EventManager queue.
            void PushEvent(const ax::Event::Id& evtId, ax::Event::Msg* msg);
            
            /// Indefine behavior if two axObject has the same id.
            void ChangeId(const ID& id);
            
            inline ID GetId() const { return _id; }
            
            /// Add a function to the object map without adding it to the event manager.
            void AddEventFunction(const std::string& name, Function fct);
            
            /// Get a function from the object map.
            ax::Event::Function GetEventFunction(const std::string& name);
            
            //        inline ax::App* GetApp()
            //        {
            //            return _app;
            //        }
            //
            //        inline ax::App* GetApp() const
            //        {
            //            return _app;
            //        }
            
        private:
            //        ax::App* _app;
            ax::Event::Manager* _evtManager;
            
            /// Unique identifier.
            ID _id;
            
            /// Map of lamda functions.
            std::map<std::string, Function> _evtMap;
            
            static ID _global_id_count;
            static ID IncrementGlobalIdCount();
        };
    }
}

/// @}
#endif // _AX_OBJECT_ 
