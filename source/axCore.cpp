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
#include "axCore.h"
#include <axGL/axGraphicInterface.h>

axCore::axCore():
// Members.
_needToDraw(true),
_popupNeedToDraw(true)
{
    _windowManager = nullptr;
    _popupManager = nullptr;
}

void axCore::InitManagers()
{
	_windowManager = std::unique_ptr<axManager>(new axManager());
    _windowManager->_managerName = "WindowManager";
    
	_popupManager = std::unique_ptr<axManager>(new axManager());
    _popupManager->_managerName = "PopupManager";
    
    _realPopWindowManager = std::unique_ptr<axManager>(new axManager());
    _realPopWindowManager->_managerName = "RealPopWindowManager";
}

int axCore::InitGL()
{
    ax::GL::Init();
    return true;
}

axManager* axCore::GetWindowManager()
{
	return _windowManager.get();
}

axManager* axCore::GetPopupManager()
{
	 return _popupManager.get();
}

axManager* axCore::GetRealPopWindowManager()
{
    return _realPopWindowManager.get();
}

void axCore::ResizeGLScene(const ax::Size& size)
{
    // Prevent a division by zero.
	_size = ax::Size(size.x, size.y == 0 ? 1 : size.y);
    
    ax::GL::Resize(_size);
    
	_needToDraw = true;
	_popupNeedToDraw = true;
    
    GetWindowManager()->OnSize(size);
}

ax::Size axCore::GetGlobalSize() const
{
	return _size;
}

void axCore::SetGlobalSize(const ax::Size& size)
{
    _size = size;
}

void axCore::UpdateAll()
{
	_needToDraw = true;
	_popupNeedToDraw = true;
}

int axCore::DrawGLScene()
{
	if (_needToDraw == true)
	{
        ax::GL::Draw(_size);
		
        GetWindowManager()->OnPaint();
        GetPopupManager()->OnPaint();

        _needToDraw = false;
        
		return true;
	}
	return false;
}
