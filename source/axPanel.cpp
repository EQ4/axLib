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

axPanel::axPanel(ax::App* app, const ax::Rect& rect) :
axWindow(app, rect)
{
//    if(GetIsPopup())
//    if(HasProperty("Popup"))
//    {
//        app->AddPopWindow(this);
//    }
//    else if(GetIsRealPopup())
//    {
//        SetRealPopupWindow(true);
//        axManager* man = app->GetCore()->GetRealPopWindowManager();
//        man->Add(this);
//    }
//    else
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



axPanel::axPanel(axWindow* parent, const ax::Rect& rect) : 
axWindow(parent, rect)
{
	if (parent != nullptr)
	{
//		if (parent->GetIsPopup())
        if(parent->HasProperty("Popup"))
		{
//            SetPopupWindow(true);
            AddProperty("Popup");
			ax::App::GetMainApp()->AddPopWindow(this);
		}
//        else if(parent->GetIsRealPopup())
//        {
//            SetRealPopupWindow(true);
//            axManager* man = ax::App::GetMainApp()->GetCore()->GetRealPopWindowManager();
//            man->Add(this);
//        }
		else
		{
			ax::App::GetMainApp()->AddWindow(this);
		}
	}
	else
	{
        if(HasProperty("Popup"))
        {
            ax::App::GetMainApp()->AddPopWindow(this);
        }
//        else if(GetIsRealPopup())
//        {
//            SetRealPopupWindow(true);
//            axManager* man = ax::App::GetMainApp()->GetCore()->GetRealPopWindowManager();
//            man->Add(this);
//        }
        else
        {
            ax::App::GetMainApp()->AddWindow(this);
        }
		
	}
}

axPanel::axPanel(int f, axWindow* parent, const ax::Rect& rect) :
axWindow(parent, rect)
{
    if(f == 86)
    {
        ax::Core::WindowManager* man = ax::App::GetMainApp()->GetCore()->GetRealPopWindowManager();
        man->Add(this);
        return;
    }
    
//    SetPopupWindow(true);
    AddProperty("Popup");
	ax::App::GetMainApp()->AddPopWindow(this);
}

axPanel::~axPanel()
{
    if(IsGrabbed())
    {
        UnGrabMouse();
    }
    
    if(IsMouseHoverWindow())
    {
        //if(GetIsPopup())
        if(HasProperty("Popup"))
        {
            ax::App::GetMainApp()->GetPopupManager()->ReleaseMouseHover();
        }
        else
        {
            ax::App::GetMainApp()->GetWindowManager()->ReleaseMouseHover();
        }
        
    }
    
    
    if(IsKeyGrab())
    {
        UnGrabKey();
    }
    
    axWindow::~axWindow();
}

//axPanel::axWindowType axPanel::GetWindowType()
//{
//    return axWindowType::axWINDOW_TYPE_PANEL;
//}

void axPanel::BlockDrawing()
{
	ax::Rect absRect(GetAbsoluteRect());
    ax::Size gSize(ax::App::GetMainApp()->GetCore()->GetGlobalSize());
	
	glScissor(absRect.position.x-1, 
			  gSize.y - absRect.position.y - absRect.size.y,
			  absRect.size.x+1, 
			  absRect.size.y+1);

	glEnable(GL_SCISSOR_TEST);

}

void axPanel::BlockDrawing(const ax::Rect& rect)
{
	ax::Size gSize(ax::App::GetMainApp()->GetCore()->GetGlobalSize());
	
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
    ax::App::GetMainApp()->GetCore()->ShowMouse();
}

void axPanel::HideMouse()
{
    ax::App::GetMainApp()->GetCore()->HideMouse();
}

void axPanel::GrabMouse()
{
//    if(GetIsPopup())
    if(HasProperty("Popup"))
    {
        ax::App::GetMainApp()->GetPopupManager()->GrabMouse(this);
    }
    else
    {
        ax::App::GetMainApp()->GetWindowManager()->GrabMouse(this);
    }
	
}

void axPanel::UnGrabMouse()
{
//    if(GetIsPopup())
    if(HasProperty("Popup"))
    {
        ax::App::GetMainApp()->GetPopupManager()->UnGrabMouse();
    }
    else
    {
        ax::App::GetMainApp()->GetWindowManager()->UnGrabMouse();
    }
	
}

void axPanel::GrabKey()
{
//    if(GetIsPopup())
    if(HasProperty("Popup"))
    {
        ax::App::GetMainApp()->GetPopupManager()->GrabKey(this);
    }
    else
    {
        ax::App::GetMainApp()->GetWindowManager()->GrabKey(this);
    }
}

void axPanel::UnGrabKey()
{
//    if(GetIsPopup())
    if(HasProperty("Popup"))
    {
        ax::App::GetMainApp()->GetPopupManager()->UnGrabKey();
    }
    else
    {
        ax::App::GetMainApp()->GetWindowManager()->UnGrabKey();
    }
}

bool axPanel::IsKeyGrab()
{
//    if(GetIsPopup())
    if(HasProperty("Popup"))
    {
        return ax::App::GetMainApp()->GetPopupManager()->IsKeyGrab(this);
    }
    else
    {
        return ax::App::GetMainApp()->GetWindowManager()->IsKeyGrab(this);
    }
    
}

void axPanel::UpdateAll()
{
	ax::App::GetMainApp()->UpdateAll();
}

void axPanel::Update()
{
    if(ax::App::GetMainApp()->_widgetSelector != nullptr &&
       ax::App::GetMainApp()->_widgetSelector->GetSelectedWidget() == this)
    {
        if(ax::App::GetMainApp()->IsDebugEditorActive())
        {
            ax::App::GetMainApp()->_widgetSelector->SetSelectedWidget(this);
        }
        
    }
    SetNeedUpdate();
	UpdateAll();
}

bool axPanel::IsGrabbed()
{
//    if(GetIsPopup())
    if(HasProperty("Popup"))
    {
        return ax::App::GetMainApp()->GetPopupManager()->IsGrab();
    }
    else
    {
        return ax::App::GetMainApp()->GetWindowManager()->IsGrab();
    }
}

bool axPanel::IsMouseHoverWindow()
{
//    if(GetIsPopup())
    if(HasProperty("Popup"))
    {
        return ax::App::GetMainApp()->GetPopupManager()->IsMouseHoverWindow(this);
    }
    else
    {
        return ax::App::GetMainApp()->GetWindowManager()->IsMouseHoverWindow(this);
    }
	
}

void axPanel::DeleteWindow(axWindow* win)
{

}

ax::Rect axPanel::GetWindowPixelData(unsigned char*& data) const
{
    ax::Rect rect(GetAbsoluteRect());
    rect.position.x -= 1;
    rect.size.x += 1;
    rect.position.y -= 1;
    rect.size.y += 1;
    
    data = new unsigned char[rect.size.x * rect.size.y * 4];
    
    ax::Size globalSize(ax::App::GetMainApp()->GetCore()->GetGlobalSize());

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
