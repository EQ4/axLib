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
#ifndef __AX_WINDOW__
#define __AX_WINDOW__

/// @defgroup Core
/// @{

#include <axEvent/axObject.h>
#include <axUtils/axUtils.h>
#include <axUtils/axResourceStorage.h>
#include <axGL/axGC.h>
#include <axGL/axFrameBuffer.h>

#include "axConfig.h"
#include "axC++.h"
#include <exception>

namespace ax
{
    class App;
    
    namespace Core
    {
        class WindowManager;
    }
}

//class axManager;

class axWindow : public ax::Event::Object
{
public:
    
//    class axWindowException: public std::exception
//    {
//        virtual const char* what() const throw()
//        {
//            return "ax::Window needs a parent window. \
//            Use ax::Window(ax::App* app, ...) constructor for top level window.";
//        }
//    } ExceptionNoParent;
    
    // First window in the application.
    axWindow(ax::App* app, const ax::Rect& rect);
    
	axWindow(axWindow* parent, const ax::Rect& rect);
    
    axWindow(const int& type, ax::App* app, const ax::Rect& rect);
    
    virtual ~axWindow();
    
    axWindow* GetParent() const;
    
    //--------------------------------------------------------------------------
	ax::Rect GetRect() const;
	ax::Rect GetAbsoluteRect() const;
	ax::Size GetSize() const;
    ax::Rect GetShownRect() const;
    
    void SetRect(const ax::Rect& rect);
	void SetSize(const ax::Size& size);
	void SetPosition(const ax::Point& pos);
    void SetShownRect(const ax::Rect& size);
    void SetSizeNoShowRect(const ax::Size& size);
    //--------------------------------------------------------------------------

	void SetScrollDecay(const ax::Point& decay);
	ax::Point GetScrollDecay() const;

    bool IsShown() const;
    void Show();
    void Hide();
    
	void Reparent(axWindow* parent, const ax::Point& position);

    ax::ResourceStorage* GetResourceManager();
    
    void SetWindowColor(const ax::Color& color);
    
    void SetContourColor(const ax::Color& color);
    
    void RenderWindow();
    
    ax::Rect GetWindowPixelData(unsigned char*& data) const;
    
    ax::Rect GetDrawingRect() const;
    
    void SetNeedUpdate();
    
    void GrabMouse();
    void UnGrabMouse();
    bool IsGrabbed() const;
    bool IsMouseHoverWindow() const;
    
    void GrabKey();
    void UnGrabKey();
    bool IsKeyGrab() const;
    
    // Drawing events.
    virtual void OnPaint();
    virtual void OnPaintStatic(){}
    virtual void Update();
    virtual void OnResize(const ax::Size& size){}
    
    // Mouse events.
    virtual void OnLeftDragging(){}
    virtual void OnRightDragging(){}
	virtual void OnMouseMotion(const ax::Point& pos){ axUNUSED(pos); }
	virtual void OnMouseLeftDown(const ax::Point& pos){ axUNUSED(pos); }
	virtual void OnMouseLeftDoubleClick(const ax::Point& pos){ axUNUSED(pos); }
	virtual void OnMouseLeftUp(const ax::Point& pos){ axUNUSED(pos); }
	virtual void OnMouseRightDown(const ax::Point& pos){ axUNUSED(pos); }
    virtual void OnMouseRightUp(){}
    virtual void OnMouseEnter(){}
    virtual void OnMouseLeave(){}
    virtual void OnFocusIn(){}
	virtual void OnMouseLeftDragging(const ax::Point& pos){ axUNUSED(pos); }
    
    // Keyboard events.
	virtual void OnKeyDown(const char& key){ axUNUSED(key); }
    virtual void OnBackSpaceDown(){}
    virtual void OnEnterDown(){}
    virtual void OnKeyDeleteDown(){}
    virtual void OnLeftArrowDown(){}
    virtual void OnRightArrowDown(){}
    virtual void OnWasKeyUnGrabbed(){}
    virtual void OnWasKeyGrabbed(){}
    
    inline ax::App* GetApp() const;
    
    inline ax::App* GetApp();
    
    ax::Property& GetProperties();
    
    void AddProperty(const std::string& property);
    
    void RemoveProperty(const std::string& property);
    
    bool HasProperty(const std::string& property) const;
    
private:
    ax::App* _app;
    ax::Core::WindowManager* _windowManager;
	axWindow* _parent;
	ax::Rect _rect, _shownRect;
	ax::Point _absolutePosition, _scrollDecay;
    ax::Color _windowColor, _contourColor;
    ax::GL::FrameBuffer _frameBufferObj;
    
    
    ax::ResourceStorage _resourceManager;
    
    bool _needUpdate;
    bool _isHidden;
    
    //--------------------
    // Property list :
    //--------------------
    // Popup
    // RealPopup
    // BlockDrawing
    // Selectable
    // EditingWidget
    // Editable
    // BackBuffer
    // AcceptWidget
    ax::Property _properties;
};

inline ax::App* axWindow::GetApp() const
{
    return _app;
}

inline ax::App* axWindow::GetApp()
{
    return _app;
}

inline void axWindow::AddProperty(const std::string& property)
{
    _properties.AddProperty(property);
}

inline void axWindow::RemoveProperty(const std::string& property)
{
    _properties.RemoveProperty(property);
}

inline bool axWindow::HasProperty(const std::string& property) const
{
    return _properties.HasProperty(property);
}

inline ax::Property& axWindow::GetProperties()
{
    return _properties;
}


/// @}
#endif //__AX_WINDOW__