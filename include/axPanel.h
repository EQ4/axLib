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
#ifndef __AX_PANEL__
#define __AX_PANEL__

/// @defgroup Core
/// @{

#include "axApp.h"
#include "axWindow.h"

class axScrollBar;

class axPanel : public axWindow
{
public:
    axPanel(ax::App* app, const ax::Rect& rect);
	axPanel(axWindow* parent, const ax::Rect& rect);
	axPanel(const int& type, ax::App* app, const ax::Rect& rect);

    virtual ~axPanel();
        
    void SetScrollBar(axScrollBar* scrollbar);
    axScrollBar* GetScrollBar();

private:
    axScrollBar* _scrollBar = nullptr;
};

/// @}
#endif //__AX_PANEL__
