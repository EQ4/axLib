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
#include "axWindowManager.h"
#include "axWindow.h"
//#include "axMath.h"
#include "axApp.h"
#include "axCore.h"
#include "axConfig.h"

namespace ax
{
    namespace Core
    {
        WindowManager::WindowManager() :
        // Heritage.
        axMouseManager(),
        axKeyboardManager()
        {
            axMouseManager::SetWindowTree(&_windowTree);
            axKeyboardManager::SetWindowTree(&_windowTree);
        }
        
        WindowManager::~WindowManager()
        {
        }
        
        void WindowManager::Add(axWindow* win)
        {
            _windowTree.AddWindow(win);
        }
        
        void WindowManager::OnPaint()
        {
            _windowTree.DrawTree();
        }
        
        void WindowManager::OnFocusIn()
        {
            
        }
        
        void WindowManager::OnUpdate()
        {
            
        }
        
        axWindowTree* WindowManager::GetWindowTree()
        {
            return &_windowTree;
        }
        
        void WindowManager::OnSize(const ax::Size& size)
        {
            
            //    for(auto& n : _windowTree.GetMainNode())
            //    {
            //        n->window->OnResize(size);
            //    }
            //    _windowTree.GetMainNode()[0]->window->OnResize(size);
            
            for (axWindowNode* it : _windowTree.GetMainNode())
            {
                if(it != nullptr)
                {
                    it->ResizeNode(size);
                }
            }
            
            //    for (auto& x :  _windowTree.GetMainNode())
            //    {
            //        
            ////        axWindow* win = x->second;
            ////        win->OnResize(size);
            //    }
        }
    }
}

