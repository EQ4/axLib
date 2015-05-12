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
#include "axMath.h"
#include "axConfig.h"
#include "axGraphicInterface.h"
#include "axWindowTree.h"

axWindow::axWindow(ax::App* app, const ax::Rect& rect):
// Heritage.
axObject(app),
_parent(nullptr),
_rect(rect),
_isHidden(false),
_isPopup(false),
_isRealPopup(false),
_isBlockDrawing(false),
_shownRect(ax::Point(0, 0), rect.size),
_isSelectable(true),
_windowColor(0.0, 0.0, 0.0, 0.0),
_contourColor(0.0, 0.0, 0.0, 0.0),
_needUpdate(true),
_isEditingWidget(false),
_isEditable(true),
_frameBufferObj(rect.size),
_hasBackBuffer(true)
{
    
}

axWindow::axWindow(axWindow* parent, const ax::Rect& rect):
// Heritage.
axObject(parent->GetApp()),
// Members.
_parent(parent),
_rect(rect),
_isHidden(false),
_isPopup(false),
_isRealPopup(false),
_isBlockDrawing(false),
_shownRect(ax::Point(0, 0), rect.size),
_isSelectable(true),
_windowColor(0.0, 0.0, 0.0, 0.0),
_contourColor(0.0, 0.0, 0.0, 0.0),
_needUpdate(true),
_isEditingWidget(false),
_isEditable(true),
_frameBufferObj(rect.size),
_hasBackBuffer(true)
//_app(nullptr)
{
	if (parent == nullptr)
	{
        // Should now never happen with new axApp.
//        std::cerr << "SHOULD NEVER HAPPEN." << std::endl;
//        assert(true);
        
		_absolutePosition = rect.position;
	}
	else
	{
//        _app = parent->GetApp();
		_absolutePosition = parent->_absolutePosition + rect.position;
	}
    
	_gc = new axGC(this);
}

axWindow::~axWindow()
{
//    axPrint("DELETE WINDOW : ", GetId());
//    axApp::GetInstance()->GetCore()->GetWindowManager()->GetWindowTree()->DeleteWindow(this);
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

	axID temp = _parent->GetId();
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

ax::Point axWindow::GetBottomLeftPosition() const
{
	return ax::Point(_rect.position.x, 
		_rect.position.y + _rect.size.y);
}

ax::Point axWindow::GetTopRightPosition() const
{
    return ax::Point(_rect.position.x + _rect.size.x, _rect.position.y);
}

ax::Point axWindow::GetNextPosRight(const int& delta) const
{
    return ax::Point(_rect.position.x + _rect.size.x + delta, _rect.position.y);
}

ax::Point axWindow::GetNextPosDown(const int& delta) const
{
    return ax::Point(_rect.position.x, _rect.position.y + _rect.size.y + delta);
}

ax::Point axWindow::GetNextPosLeft(const int& delta) const
{
     return ax::Point(_rect.position.x, _rect.position.y - delta);
}

ax::Point axWindow::GetNextPosUp(const int& delta) const
{
    return ax::Point(_rect.position.x, _rect.position.y - delta);
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

axGC* axWindow::GetGC()
{
	return _gc;
}

void axWindow::SetSize(const ax::Size& size)
{
	_rect.size = size;
    _shownRect.size = size;

//    InitGLWindowBackBufferDrawing();
    if(_hasBackBuffer)
    {
        _frameBufferObj.Resize(size);
    }
    
    Update();
}

void axWindow::SetSizeNoShowRect(const ax::Size& size)
{
    _rect.size = size;
    
    //    InitGLWindowBackBufferDrawing();
    if(_hasBackBuffer)
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

	//    InitGLWindowBackBufferDrawing();
    
    if(_hasBackBuffer)
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

bool axWindow::IsSelectable() const
{
    if(IsEditingWidget() && GetApp()->IsDebugEditorActive() == false)
    {
        return false;
    }
    
    return _isSelectable;
}

bool axWindow::IsEditingWidget() const
{
    return _isEditingWidget;
}

void axWindow::SetEditingWidget(const bool& editing)
{
    _isEditingWidget = editing;
}

void axWindow::SetEditable(const bool& editable)
{
    _isEditable = editable;
}

bool axWindow::IsEditable() const
{
    return _isEditable;
}

void axWindow::SetPopupWindow(const bool& popup)
{
    _isPopup = popup;
}


bool axWindow::GetIsRealPopup()
{
    return _isRealPopup;
}

void axWindow::SetRealPopupWindow(const bool& popup)
{
    _isRealPopup = popup;
}

void axWindow::SetWindowColor(const axColor& color)
{
    _windowColor = color;
}

void axWindow::SetContourColor(const axColor& color)
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

bool axWindow::GetIsPopup()
{
    return _isPopup;
}

void axWindow::SetSelectable(const bool& selectable)
{
    _isSelectable = selectable;
}

bool axWindow::IsBlockDrawing() const
{
    return _isBlockDrawing;
}

void axWindow::SetBlockDrawing(const bool& block)
{
    _isBlockDrawing = block;
}

void axWindow::SetHasBackBuffer(const bool& hasBackBuffer)
{
    _hasBackBuffer = hasBackBuffer;
}

axResourceManager* axWindow::GetResourceManager()
{
    return &_resourceManager;
}

void axWindow::OnPaint()
{
    
    axGC* gc = GetGC();
    ax::Rect rect(GetRect());
    
    gc->SetColor(_windowColor);
    gc->DrawRectangle(ax::Rect(ax::Point(0, 0), rect.size));
    
    gc->SetColor(_contourColor);
    gc->DrawRectangle(ax::Rect(ax::Point(0, 0), rect.size));
}

void axWindow::RenderWindow()
{
#if _axBackBufferWindow_ == 1
    
    if(_hasBackBuffer)
    {
        if(_needUpdate)
        {
//            std::function<void()> draw([this](){ OnPaint(); });
            
            _frameBufferObj.DrawOnFrameBuffer([this](){ OnPaint(); },
                                              GetRect().size,
                                              GetApp()->GetCore()->GetGlobalSize());
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