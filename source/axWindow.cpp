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
#include "axWindow.h"
#include "axApp.h"
#include "axConfig.h"
#include "axWindowTree.h"
#include "axWindowManager.h"

axWindow::axWindow(ax::App* app, const ax::Rect& rect):
// Heritage.
ax::Event::Object(app->GetEventManager()),
// Members.
_parent(nullptr),
_rect(rect),
_isHidden(false),
_shownRect(ax::Point(0, 0), rect.size),
_windowColor(0.0, 0.0, 0.0, 0.0),
_contourColor(0.0, 0.0, 0.0, 0.0),
_needUpdate(true),
_frameBufferObj(rect.size),
_app(app),
_windowManager(app->GetWindowManager())
{
    AddProperty("BackBuffer");
    AddProperty("Selectable");
    
    _windowManager->Add(this);
}

// A nullptr parent should never be use.
// First parent->GetApp()->GetEventManager() is gonna crash and a nullptr
// argument should generate an anbiguous error between ax::App* and ax::Window*
// constructor. Use axApp* constructor for top level window.

 axWindow::axWindow(axWindow* parent, const ax::Rect& rect):
// Heritage.
ax::Event::Object(parent->GetApp()->GetEventManager()),
// Members.
_parent(parent),
_rect(rect),
_isHidden(false),
_shownRect(ax::Point(0, 0), rect.size),
_windowColor(0.0, 0.0, 0.0, 0.0),
_contourColor(0.0, 0.0, 0.0, 0.0),
_needUpdate(true),
_frameBufferObj(rect.size),
_app(parent->GetApp())
{
    AddProperty("BackBuffer");
    AddProperty("Selectable");

    _absolutePosition = parent->_absolutePosition + rect.position;

    if(parent->HasProperty("Popup"))
    {
        AddProperty("Popup");
        _windowManager = _app->GetPopupManager();
    }
    else
    {
        _windowManager = _app->GetWindowManager();
    }
    
    _windowManager->Add(this);
}

axWindow::axWindow(const int& type, ax::App* app, const ax::Rect& rect):
// Heritage.
ax::Event::Object(app->GetEventManager()),
// Members.
_parent(nullptr),
_rect(rect),
_isHidden(false),
_shownRect(ax::Point(0, 0), rect.size),
_windowColor(0.0, 0.0, 0.0, 0.0),
_contourColor(0.0, 0.0, 0.0, 0.0),
_needUpdate(true),
_frameBufferObj(rect.size),
_app(app)
{
    axUNUSED(type); // For now only popup window possible.
    AddProperty("BackBuffer");
    AddProperty("Selectable");
    AddProperty("Popup");
    
    _windowManager = app->GetPopupManager();
    _windowManager->Add(this);
}

axWindow::~axWindow()
{
    if(IsGrabbed())
    {
        UnGrabMouse();
    }
    
    if(IsMouseHoverWindow())
    {
        _windowManager->ReleaseMouseHover();
    }
    
    if(IsKeyGrab())
    {
        UnGrabKey();
    }
    
//    axPrint("DELETE WINDOW : ", GetId());
//    axApp::GetInstance()->GetCore()->GetWindowManager()->GetWindowTree()->DeleteWindow(this);
}

void axWindow::DeleteWindow()
{
    
//    GetApp()->GetCore()->GetPopupManager()->GetWindowTree()->
//    DeleteWindow( std::get<2>(_infoEditor[i]) );
    _windowManager->GetWindowTree()->DeleteWindow(this);
}

axWindow* axWindow::GetParent() const
{
	return _parent;
}

void axWindow::SetScrollDecay(const ax::Point& decay)
{
	_scrollDecay = decay;
}

ax::Point axWindow::GetScrollDecay() const
{
	return _scrollDecay;
}

bool axWindow::IsShown() const
{
    const axWindow* win = this;
    
    while(win != nullptr)
    {
        if(win->_isHidden == true)
        {
            return false;
        }
        
        win = win->GetParent();
        
    }
    return true;
}

void axWindow::Show()
{
    if (_isHidden != false)
    {
        _isHidden = false;
        Update();
    }
}

void axWindow::Hide()
{
    if (_isHidden != true)
    {
        _isHidden = true;
        Update();
    }
}

void axWindow::Reparent(axWindow* parent, const ax::Point& position)
{
	_parent = parent;
	SetPosition(position);

    ax::Event::ID temp = _parent->GetId();
	_parent->ChangeId(GetId());
	ChangeId(temp);

	Update();
}

ax::Rect axWindow::GetShownRect() const
{
    return _shownRect;
}

void axWindow::SetShownRect(const ax::Rect& rect)
{
    _shownRect = rect;
}

ax::Rect axWindow::GetRect() const
{
	return _rect;
}

ax::Rect axWindow::GetAbsoluteRect() const
{
	ax::Point pos = _rect.position;
	const axWindow* win = this;

	// Too slow.
	while (win->GetParent() != nullptr)
	{
		pos += win->GetParent()->GetRect().position;
        pos -= win->GetParent()->GetScrollDecay();
		win = win->GetParent();
	}

	return ax::Rect(pos, _rect.size);
}

ax::Size axWindow::GetSize() const
{
	return _rect.size;
}

void axWindow::SetSize(const ax::Size& size)
{
	_rect.size = size;
    _shownRect.size = size;

    if(HasProperty("BackBuffer"))
    {
        _frameBufferObj.Resize(size);
    }
    
    Update();
}

void axWindow::SetSizeNoShowRect(const ax::Size& size)
{
    _rect.size = size;
    
    if(HasProperty("BackBuffer"))
    {
        _frameBufferObj.Resize(size);
    }
    
    Update();
}

void axWindow::SetRect(const ax::Rect& rect)
{
	_rect.position = rect.position;
	_rect.size = rect.size;
	_shownRect.size = rect.size;

    if(HasProperty("BackBuffer"))
    {
        _frameBufferObj.Resize(rect.size);
    }
	
	Update();
}

void axWindow::SetPosition(const ax::Point& pos)
{
	if (_parent == nullptr)
	{
		_absolutePosition = pos;
	}
	else
	{
		_absolutePosition = _parent->GetAbsoluteRect().position + pos;
	}

	_rect.position = pos;

	Update();
}

void axWindow::SetWindowColor(const ax::Color& color)
{
    _windowColor = color;
}

void axWindow::SetContourColor(const ax::Color& color)
{
    _contourColor = color;
}

ax::Rect axWindow::GetDrawingRect() const
{
    return ax::Rect(1, 1, _rect.size.x - 1, _rect.size.y - 1);
}

void axWindow::SetNeedUpdate()
{
    _needUpdate = true;
}

ax::ResourceStorage* axWindow::GetResourceManager()
{
    return &_resourceManager;
}


void axWindow::GrabMouse()
{
    _windowManager->GrabMouse(this);
}

void axWindow::UnGrabMouse()
{
    _windowManager->UnGrabMouse();
}

bool axWindow::IsGrabbed() const
{
    // Need to change this with this pointer to current ax::Window.
    return _windowManager->IsGrab();
}

bool axWindow::IsMouseHoverWindow() const
{
    return _windowManager->IsMouseHoverWindow(this);
}

void axWindow::GrabKey()
{
    _windowManager->GrabKey(this);
}

void axWindow::UnGrabKey()
{
    _windowManager->UnGrabKey();
}

bool axWindow::IsKeyGrab() const
{
    return _windowManager->IsKeyGrab(this);
}

void axWindow::Update()
{
    _needUpdate = true;
    _app->UpdateAll();
}

void axWindow::OnPaint()
{
    ax::GC gc;
    ax::Rect rect(GetDrawingRect());
    
    gc.SetColor(_windowColor);
    gc.DrawRectangle(rect);
    
    gc.SetColor(_contourColor);
    gc.DrawRectangle(rect);
}

void axWindow::RenderWindow()
{
#if _axBackBufferWindow_ == 1
    
    if(HasProperty("BackBuffer"))
    {
        if(_needUpdate)
        {
//            _frameBufferObj.DrawOnFrameBuffer([this](){ OnPaint(); },
//                                              GetRect().size,
//                                              GetApp()->GetCore()->GetGlobalSize());
            
            _frameBufferObj.DrawOnFrameBuffer([this](){ OnPaint(); },
                                              GetRect().size,
                                              GetApp()->GetFrameSize());
            _needUpdate = false;
        }
        
        _frameBufferObj.DrawFrameBuffer(GetShownRect().size);
    }
    else
    {
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        OnPaint();
    }
    
#else
    OnPaint();
#endif //_axBackBufferWindow_
}

ax::Rect axWindow::GetWindowPixelData(unsigned char*& data) const
{
    ax::Rect rect(GetAbsoluteRect());
    rect.position.x -= 1;
    rect.size.x += 1;
    rect.position.y -= 1;
    rect.size.y += 1;
    
    data = new unsigned char[rect.size.x * rect.size.y * 4];
    
//    ax::Size globalSize(_app->GetCore()->GetGlobalSize());
    ax::Size globalSize(_app->GetFrameSize());
    
    /// @todo Move this to axGL framework.
    glReadPixels(rect.position.x,
                 globalSize.y - rect.position.y - rect.size.y,
                 rect.size.x,
                 rect.size.y,
                 GL_RGBA, // Format.
                 GL_UNSIGNED_BYTE, // Type.
                 (void*)data);
    
    return rect;
}