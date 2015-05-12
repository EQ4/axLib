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
	axPanel(int f, axWindow* parent, const ax::Rect& rect);

    virtual ~axPanel();
    
	void UpdateAll();
	virtual void Update();
    
    virtual axWindowType GetWindowType();

	void GrabMouse();
	void UnGrabMouse();
	bool IsGrabbed();
	bool IsMouseHoverWindow();
	void DeleteWindow(axWindow* win);

    void GrabKey();
    void UnGrabKey();
    
    void ShowMouse();
    void HideMouse();
    
    bool IsKeyGrab();
    
//	axApp* GetApp();

	void BlockDrawing();
	void BlockDrawing(const ax::Rect& rect);

	void UnBlockDrawing();
    
    ax::Rect GetWindowPixelData(unsigned char*& data) const;
    
    void SetScrollBar(axScrollBar* scrollbar);
    axScrollBar* GetScrollBar();

//    void SetPanelColor(const axColor& color);

private:
	bool _isInPopup;
    axScrollBar* _scrollBar = nullptr;
    axWindowType _windowType;
    
//    axColor _panelColor;
};

/// @}
#endif //__AX_PANEL__
