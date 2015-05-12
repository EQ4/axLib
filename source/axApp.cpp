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
#include "axApp.h"
#include "axResourceManager.h"

#include "axPanel.h"
#include "axToggle.h"
#include "axConfig.h"
#include "axEditorMenu.h"
#include "axWidget.h"

#include "axScrollBar.h"
#include <axEvent/axEventManager.h>

ax::App* ax::App::_mainApp = nullptr;

//axApp* axApp::MainInstance = nullptr;
//axResourceManager* axApp::_resourceManager = nullptr;

ax::App::App():
_debugEditorActive(false)
{
    _mainApp = this;
    _evtManager = new ax::Event::Manager([&]
    {
        this->GetCore()->PushEventOnSystemQueue();
    });
    
#ifdef __linux__
	_core = new axCoreX11(this);
	_core->Init(ax::Size(0, 0));
//#endif //__linux__


#elsif _MSC_VER
	#if _axWxWidgetsCore_ == 1
    
	_core = new axCoreWxWidgets();
	_core->Init(ax::Size(0, 0));
	#else
		_core = new axCoreWin32();
		axCORE = _core;
		_core->Init(ax::Size(0, 0));
	#endif //_axWxWidgetsCore_

//#endif //_MSC_VER
    
#else// __APPLE__
    
#ifdef _AX_VST_APP_
    _core = new axVstCoreMac();
    _core->Init(ax::Size(800, 273));
#else
    _core = new axCoreMac();
//    _core->Init(ax::Size(500, 500));
#endif // _AX_VST_APP_
    
#endif // __APPLE__

}

ax::App::App(const ax::Size& frame_size):
_debugEditorActive(false)
{
    _mainApp = this;
    _evtManager = new ax::Event::Manager();
    
#ifdef __linux__
	_core = new axCoreX11(this);
	_core->Init(frame_size);
//#endif //__linux__

#elsif _MSC_VER
	#if _axWxWidgetsCore_ == 1
		_core = new axCoreWxWidgets();
		_core->Init(frame_size);
	#else
		_core = new axCoreWin32();
		axCORE = _core;
		_core->Init(frame_size);
	#endif //_axWxWidgetsCore_

//#endif // _MSC_VER
    
    
#else// __APPLE__
    
#ifdef _AX_VST_APP_
    _core = new axVstCoreMac();
    _core->Init(frame_size);
#else
    _core = new axCoreMac();
    _core->SetGlobalSize(frame_size);
    //_core->Init(frame_size);
#endif // _AX_VST_APP_
    
#endif // __APPLE__
}

void ax::App::CreateEditor()
{
#if _axDebugEditor_ == 1
    // @todo Fix this.
//    MainInstance = this;
    
    ax::Size size = _core->GetGlobalSize();
    
    axPrint("Size : ", size.x, size.y);
    
    _widgetSelector = new axWidgetSelector(nullptr);
    
    /// @todo Change debugPanel position.
    axPanel* debugPanel = new axPanel(3, nullptr,
                                      ax::Rect(size.x - 20, size.y - 20, 20, 20));
    
    axToggle::Info btn_info;
    btn_info.normal = axColor(1.0, 0.8, 0.8, 0.0);
    btn_info.hover = axColor(0.9, 0.9, 0.9, 0.0);
    btn_info.clicking = axColor(0.7, 0.7, 0.7, 0.0);
    
    btn_info.selected = axColor(0.8, 0.4, 0.4, 0.0);
    btn_info.selected_hover = axColor(0.9, 0.4, 0.4, 0.0);
    btn_info.selected_clicking = axColor(0.7, 0.4, 0.4, 0.0);
    
    btn_info.contour = axColor(0.0, 0.0, 0.0, 0.0);
    btn_info.font_color = axColor(0.0, 0.0, 0.0, 0.0);
    
    btn_info.img = GetResourceFile("settings.png");
    btn_info.single_img = true;
    
    axToggle* tog = new axToggle(debugPanel,
                                 ax::Rect(ax::Point(0, 0), ax::Size(20, 20)),
                                 axToggle::Events(GetOnDebugEditor()),
                                 btn_info,
                                 "",
                                 "",
                                 axToggle::Flags::SINGLE_IMG);
    tog->SetEditable(false);
    
    _debugMenu = new axEditorMenu(ax::Rect(size.x, 0, 300, size.y));
    _debugMenu->Hide();

#endif // _axDebugEditor_
}

void ax::App::AddMainEntry(std::function<void()> fct)
{
    _mainEntryFunction = fct;
}

void ax::App::CallMainEntryFunction()
{
    if(_mainEntryFunction)
    {
        _mainEntryFunction();
    }
}

//------------------------------------------------------------------------------
void ax::App::OnDebugEditor(const ax::Event::Msg& msg)
{
    if(_debugEditorActive)
    {
        _debugEditorActive = false;
        ax::Size size = _core->GetGlobalSize();
        _core->ResizeFrame(ax::Size(size.x - 300, size.y));
        _debugMenu->Hide();
        
        if(_widgetSelector != nullptr)
        {
            _widgetSelector->Hide();
        }
    }
    else
    {
        _debugEditorActive = true;
        ax::Size size = _core->GetGlobalSize();
        _core->ResizeFrame(ax::Size(size.x + 300, size.y));
        _debugMenu->SetRect(ax::Rect(ax::Rect(size.x, 0, 310, size.y)));
        _debugMenu->Show();
        
        if(_widgetSelector != nullptr)
        {
            _widgetSelector->Show();
        }
    }
}
//------------------------------------------------------------------------------

std::string ax::App::OpenFileDialog()
{
	return _core->OpenFileDialog();
}

std::string ax::App::GetAppDirectory()
{
	return _core->GetAppDirectory();
}

std::string ax::App::GetResourceFile(const std::string& file_name)
{
    std::string app_path = GetCore()->GetAppPath();
    axPrint("core ressource folder : ", app_path);
    app_path = app_path.substr(0, app_path.find_last_of("/"));
    app_path = app_path.substr(0, app_path.find_last_of("/"));
    app_path = app_path.substr(0, app_path.find_last_of("/"));
    
    std::string last_folder = app_path.substr(app_path.find_last_of("/"),
                                              app_path.size());
    
    if(last_folder == "/MacOS")
    {
        app_path = app_path.substr(0, app_path.find_last_of("/"));
    }
    
    app_path += std::string("/Frameworks/axLib.framework/Resources/");
    
    axPrint("axLib ressource folder : ", app_path);
    return app_path + file_name;
}

//std::string GetAppPath()
//{
//    return _core->GetAppPath();
//}


void ax::App::MainLoop()
{
	//CallMainEntryFunction();
	_core->MainLoop();
}

void ax::App::UpdateAll()
{
//    if(_widgetSelector != nullptr)
//    {
//        _widgetSelector->SetNeedUpdate();
//    }
    
	_core->UpdateAll();
}

axManager* ax::App::GetWindowManager()
{
	return _core->GetWindowManager();
}

axManager* ax::App::GetPopupManager()
{
    return _core->GetPopupManager();
}

void ax::App::AddWindow(axWindow* win)
{
	GetWindowManager()->Add(win);
}

void ax::App::AddPopWindow(axWindow* win)
{
	_core->GetPopupManager()->Add(win);
}

void ax::App::ActivateDebugEditor(const bool& active)
{
    _debugEditorActive = active;
    UpdateAll();
}

bool ax::App::IsDebugEditorActive() const
{
    return _debugEditorActive;
}

axCore* ax::App::GetCore()
{
	return _core;
}

axResourceManager* ax::App::GetResourceManager()
{
    axResourceManager*& rm = _resourceManager;
    return rm == nullptr ? rm = new axResourceManager() : rm;
}

void ax::App::AddAfterGUILoadFunction(std::function<void()> fct)
{
    _afterGuiLoadFunction = fct;
}

void ax::App::CallAfterGUILoadFunction()
{
    if(_afterGuiLoadFunction)
    {
        _afterGuiLoadFunction();
    }
}

void ax::App::AddPopupEntryFunction(std::function<void()> fct)
{
    _popupEntryFunction = fct;
}

void ax::App::CallPopupEntryFunction()
{
    if(_popupEntryFunction)
    {
        _popupEntryFunction();
    }
}

void ax::App::SetEditingWidget(axWidget* widget)
{
    _widgetSelector->SetSelectedWidget(widget);
    _debugMenu->SetEditingWidget(widget);
}

axEditorMenu* ax::App::GetEditor()
{
    return _debugMenu;
}