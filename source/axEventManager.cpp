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
#include "axEventManager.h"
#include <iostream>

std::mutex manager_mutex;

namespace ax
{
    namespace Event
    {
        Manager::Manager()
        {
            
        }
        
        Manager::Manager(const std::function<void()>& unblock_main_thread_fct):
        _unblockMainThreadFct(unblock_main_thread_fct)
        {
            
        }
        
        void Manager::AddFunction(axBindedEvent fct)
        {
            //manager_mutex.lock();
            
            _evtQueue.push_back(fct);
            
            //manager_mutex.unlock();
        }
        
        int Manager::GetEventQueueSize() const
        {
            return (int)_evtQueue.size();
        }
        
        void Manager::AddConnection(const ID& id, const Id& evtId, Function fct)
        {
            manager_mutex.lock();
            
            auto it = _event_fct_map.find(id);
            
            if(it != _event_fct_map.end())
            {
                it->second.insert(MultimapPair(evtId, fct));
            }
            else
            {
                Multimap evt_map;
                evt_map.insert(MultimapPair(evtId, fct));
                _event_fct_map.insert(MapPair(id, evt_map));
            }
            
            manager_mutex.unlock();
        }
        
        void Manager::PushEvent(const ID& id, const Id& evtId, Msg* msg)
        {
            manager_mutex.lock();
            
            auto it = _event_fct_map.find(id);
            
            if(it != _event_fct_map.end())
            {
                // Pair of the first and last element of this id.
                auto range(it->second.equal_range(evtId));
                
                // Add every connected functions from this id to the event queue.
                for (Multimap::iterator i = range.first; i != range.second; ++i)
                {
                    // Create a Copy of child params
                    // (this will create a new pointer with his own memory).
                    Msg* msg_copy = msg->GetCopy();
                    
                    // Add binded function to event queue.
                    AddFunction(axBindedEvent(i->second, msg_copy));
                    
                    if(_unblockMainThreadFct)
                    {
                        _unblockMainThreadFct();
                    }
                }
            }
            
            manager_mutex.unlock();
            
            delete msg;
        }
        
        void Manager::CallNext()
        {
            manager_mutex.lock();
            
            if (_evtQueue.size() != 0)
            {
                manager_mutex.unlock();
                
                // Call function.
                _evtQueue[0]();
                
                manager_mutex.lock();
                
                // Remove function from queue.
                _evtQueue.pop_front();
            }
            
            manager_mutex.unlock();
        }
    }
}


