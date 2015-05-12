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
#ifndef _AX_TIMER_
#define _AX_TIMER_

/// @defgroup Core
/// @{

#include <iostream>
#include <thread>
#include <mutex>
#include <string>
#include <chrono>

#include <axEvent/axEventManager.h>
#include <axEvent/axObject.h>

namespace ax
{
    namespace Event
    {
        class Timer : public Object
        {
        public:
            typedef std::chrono::milliseconds TimeMs;
            
            enum : Id
            {
                TIMER_ID
            };
            
            //******************************************************************
            // ax::Event::Timer::Msg
            //******************************************************************
            class Msg : public ax::Event::Msg
            {
            public:
                Msg(const TimeMs& t);
                
                TimeMs GetTime() const;
                
                virtual ax::Event::Msg* GetCopy();
                
            private:
                TimeMs _time;
            };
            
            //******************************************************************
            // ax::Event::Timer
            //******************************************************************
            Timer(Manager* evtManager, const Function& fct);
                
            Timer(Manager* evtManager);
            
            static void timer_thread(Timer& timer,
                                     const TimeMs& interval_ms,
                                     const TimeMs& length_ms);
            
            static void timer_thread_no_end(Timer& timer,
                                            const TimeMs& interval_ms);
            
            void StartTimer(const TimeMs& interval_ms,
                            const TimeMs& length_ms);
            
            void StartTimer(const TimeMs& interval_ms);
            
            bool IsRunning() const;
            
            void StopTimer();
            
        private:
            std::thread _timerThread;
            std::mutex timer_mutex;
            bool _isRunning;
        };
    }
}

/// @}
#endif //_AX_TIMER_
