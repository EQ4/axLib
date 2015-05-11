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
#include "axWidgetSelector.h"
#include "axScrollBar.h"
//#include "NSOpenGLView+axPopupWindowCocoaView.h"

axPanel::axPanel(axApp* app, const axRect& rect) :
axWindow(app, rect)
{
    if(GetIsPopup())
    {
        app->AddPopWindow(this);
    }
    else if(GetIsRealPopup())
    {
        SetRealPopupWindow(true);
        axManager* man = app->GetCore()->GetRealPopWindowManager();
        man->Add(this);
    }
    else
    {
        app->AddWindow(this);
    }
//    if (parent != nullptr)
//    {
//        if (parent->GetIsPopup())
//        {
//            SetPopupWindow(true);
//            GetApp()->AddPopWindow(this);
//        }
//        else if(parent->GetIsRealPopup())
//        {
//            SetRealPopupWindow(true);
//            axManager* man = GetApp()->GetCore()->GetRealPopWindowManager();
//            man->Add(this);
//        }
//        else
//        {
//            GetApp()->AddWindow(this);
//        }
//    }
//    else
//    {
//        if(GetIsPopup())
//        {
//            GetApp()->AddPopWindow(this);
//        }
//        else if(GetIsRealPopup())
//        {
//            SetRealPopupWindow(true);
//            axManager* man = GetApp()->GetCore()->GetRealPopWindowManager();
//            man->Add(this);
//        }
//        else
//        {
//            GetApp()->AddWindow(this);
//        }
//        
//    }
}



axPanel::axPanel(axWindow* parent, const axRect& rect) : 
axWindow(parent, rect)
{
	if (parent != nullptr)
	{
		if (parent->GetIsPopup())
		{
            SetPopupWindow(true);
			GetApp()->AddPopWindow(this);
		}
        else if(parent->GetIsRealPopup())
        {
            SetRealPopupWindow(true);
            axManager* man = GetApp()->GetCore()->GetRealPopWindowManager();
            man->Add(this);
        }
		else
		{
			GetApp()->AddWindow(this);
		}
	}
	else
	{
        if(GetIsPopup())
        {
            GetApp()->AddPopWindow(this);
        }
        else if(GetIsRealPopup())
        {
            SetRealPopupWindow(true);
            axManager* man = GetApp()->GetCore()->GetRealPopWindowManager();
            man->Add(this);
        }
        else
        {
            GetApp()->AddWindow(this);
        }
		
	}
}

axPanel::axPanel(int f, axWindow* parent, const axRect& rect) :
axWindow(parent, rect)
{
    if(f == 86)
    {
        axManager* man = GetApp()->GetCore()->GetRealPopWindowManager();
        man->Add(this);
        return;
    }
    
    SetPopupWindow(true);
	GetApp()->AddPopWindow(this);
}

axPanel::~axPanel()
{
    if(IsGrabbed())
    {
        UnGrabMouse();
    }
    
    if(IsMouseHoverWindow())
    {
        if(GetIsPopup())
        {
            GetApp()->GetPopupManager()->ReleaseMouseHover();
        }
        else
        {
            GetApp()->GetWindowManager()->ReleaseMouseHover();
        }
        
    }
    
    
    if(IsKeyGrab())
    {
        UnGrabKey();
    }
    
    axWindow::~axWindow();
}

axPanel::axWindowType axPanel::GetWindowType()
{
    return axWindowType::axWINDOW_TYPE_PANEL;
}

void axPanel::BlockDrawing()
{
	axRect absRect(GetAbsoluteRect());
	axSize gSize(GetApp()->GetCore()->GetGlobalSize());
	
	glScissor(absRect.position.x-1, 
			  gSize.y - absRect.position.y - absRect.size.y,
			  absRect.size.x+1, 
			  absRect.size.y+1);

	glEnable(GL_SCISSOR_TEST);

}

void axPanel::BlockDrawing(const axRect& rect)
{
	axSize gSize(GetApp()->GetCore()->GetGlobalSize());
	
	glScissor(rect.position.x-1, 
			  gSize.y - rect.position.y - rect.size.y, 
			  rect.size.x+1, 
			  rect.size.y+1);

	glEnable(GL_SCISSOR_TEST);
}

void axPanel::UnBlockDrawing()
{
	glDisable(GL_SCISSOR_TEST);
}

//axApp* axPanel::GetApp()
//{
//	//return _app;
//	return axApp::GetInstance();
//
//}

void axPanel::ShowMouse()
{
    GetApp()->GetCore()->ShowMouse();
}

void axPanel::HideMouse()
{
    GetApp()->GetCore()->HideMouse();
}

void axPanel::GrabMouse()
{
    if(GetIsPopup())
    {
        GetApp()->GetPopupManager()->GrabMouse(this);
    }
    else
    {
        GetApp()->GetWindowManager()->GrabMouse(this);
    }
	
}

void axPanel::UnGrabMouse()
{
    if(GetIsPopup())
    {
        GetApp()->GetPopupManager()->UnGrabMouse();
    }
    else
    {
        GetApp()->GetWindowManager()->UnGrabMouse();
    }
	
}

void axPanel::GrabKey()
{
    if(GetIsPopup())
    {
        GetApp()->GetPopupManager()->GrabKey(this);
    }
    else
    {
        GetApp()->GetWindowManager()->GrabKey(this);
    }
}

void axPanel::UnGrabKey()
{
    if(GetIsPopup())
    {
        GetApp()->GetPopupManager()->UnGrabKey();
    }
    else
    {
        GetApp()->GetWindowManager()->UnGrabKey();
    }
}

bool axPanel::IsKeyGrab()
{
    if(GetIsPopup())
    {
        return GetApp()->GetPopupManager()->IsKeyGrab(this);
    }
    else
    {
        return GetApp()->GetWindowManager()->IsKeyGrab(this);
    }
    
}

void axPanel::UpdateAll()
{
	GetApp()->UpdateAll();
}

void axPanel::Update()
{
    if(GetApp()->_widgetSelector != nullptr &&
       GetApp()->_widgetSelector->GetSelectedWidget() == this)
    {
        if(GetApp()->IsDebugEditorActive())
        {
            GetApp()->_widgetSelector->SetSelectedWidget(this);
        }
        
    }
    SetNeedUpdate();
	UpdateAll();
}

bool axPanel::IsGrabbed()
{
    if(GetIsPopup())
    {
        return GetApp()->GetPopupManager()->IsGrab();
    }
    else
    {
        return GetApp()->GetWindowManager()->IsGrab();
    }
	
}

bool axPanel::IsMouseHoverWindow()
{
    if(GetIsPopup())
    {
        return GetApp()->GetPopupManager()->IsMouseHoverWindow(this);
    }
    else
    {
        return GetApp()->GetWindowManager()->IsMouseHoverWindow(this);
    }
	
}

void axPanel::DeleteWindow(axWindow* win)
{

}

axRect axPanel::GetWindowPixelData(unsigned char*& data) const
{
    axRect rect(GetAbsoluteRect());
    rect.position.x -= 1;
    rect.size.x += 1;
    rect.position.y -= 1;
    rect.size.y += 1;
    
    data = new unsigned char[rect.size.x * rect.size.y * 4];
    
    axSize globalSize(GetApp()->GetCore()->GetGlobalSize());

    glReadPixels(rect.position.x,
                 globalSize.y - rect.position.y - rect.size.y,
                 rect.size.x,
                 rect.size.y,
                 GL_RGBA, // Format.
                 GL_UNSIGNED_BYTE, // Type.
                 (void*)data);
    
    return rect;
}

void axPanel::SetScrollBar(axScrollBar* scrollbar)
{
    _scrollBar = scrollbar;
}

axScrollBar* axPanel::GetScrollBar()
{
    return _scrollBar;
}
