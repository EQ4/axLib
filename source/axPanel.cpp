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
#include "axPanel.h"
#include "axApp.h"
//#include "axWidgetSelector.h"
#include "axScrollBar.h"

axPanel::axPanel(ax::App* app, const ax::Rect& rect) :
axWindow(app, rect)
{

}

axPanel::axPanel(axWindow* parent, const ax::Rect& rect) : 
axWindow(parent, rect)
{

}

axPanel::axPanel(const int& type, ax::App* app, const ax::Rect& rect) :
axWindow(type, app, rect)
{

}

axPanel::~axPanel()
{    
    axWindow::~axWindow();
}

void axPanel::SetScrollBar(axScrollBar* scrollbar)
{
    _scrollBar = scrollbar;
}

axScrollBar* axPanel::GetScrollBar()
{
    return _scrollBar;
}
