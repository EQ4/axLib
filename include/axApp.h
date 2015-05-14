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
#ifndef __AX_APP__
#define __AX_APP__

#include "axConfig.h"

/// @defgroup Core
/// @{

//#ifdef __linux__
//#include "axCoreX11.h"
////#endif //__linux__
//
//#elif _MSC_VER
//	#if _axWxWidgetsCore_ == 1
//		#include "axCoreWxWidgets.h"
//		
//	#else
//		#include "axCoreWin32.h"
//	#endif // _axWxWidgetsCore_.
////#endif //_MSC_VER
//
//
//#else// __APPLE__
//    #ifdef _AX_VST_APP_
//        #include "axVstCoreMac.h"
//    #else
//        #include "axCoreMac.h"
//    #endif // _AX_VST_APP_
//#endif // __APPLE__


#include "axC++.h"
#include "axCoreFacade.h"
#include <axUtils/axResourceStorage.h>
#include <axEvent/axEvent.h>

class axEditorMenu;
class axWidget;
class axWidgetSelector;

namespace ax
{
    namespace Event
    {
        class Manager;
    }
    
    class App : public ax::Core::Facade
    {
    public:
        App();
        
        App(const ax::Size& frame_size);
        
        inline ax::Event::Manager* GetEventManager();
        
        static inline App* GetMainApp();
        
        std::string GetResourceFile(const std::string& file_name);
        
        ax::ResourceStorage* GetResourceManager();
        
        void CallMainEntryFunction();
        void AddMainEntry(std::function<void()> fct);
        
        void AddAfterGUILoadFunction(std::function<void()> fct);
        void CallAfterGUILoadFunction();
        
        void AddPopupEntryFunction(std::function<void()> fct);
        void CallPopupEntryFunction();
        
        //----------------------------------------------------------------------

        
//        void MainLoop();
//        
//        ax::Core::WindowManager* GetWindowManager();
//        ax::Core::WindowManager* GetPopupManager();
//        
//        void UpdateAll();
//        
//        axCore* GetCore();
//        
//        std::string OpenFileDialog();
//        
//        bool CreatePopupWindow(const char*, int, int);
//        
//        std::string GetAppDirectory();
//        
//        inline std::string GetAppPath()
//        {
//            return _core->GetAppPath();
//        }
        
        
        //----------------------------------------------------------------------
        axEditorMenu* GetEditor();
        void CreateEditor();
        
        void SetEditingWidget(axWidget* widget);
        
        axWidgetSelector* _widgetSelector = nullptr;
        
        void ActivateDebugEditor(const bool& active);
        bool IsDebugEditorActive() const;
        

        
        
        
    private:
//        axCore* _core;
        static App* _mainApp;
        
        ax::Event::Manager* _evtManager;
        
        axEditorMenu* _debugMenu;
        
        std::function<void()> _mainEntryFunction, _afterGuiLoadFunction;
        std::function<void()> _popupEntryFunction;
        ax::ResourceStorage* _resourceManager;
        
        bool _debugEditorActive;
        
        axEVENT_ACCESSOR(ax::Event::Msg, OnDebugEditor);
        void OnDebugEditor(const ax::Event::Msg& msg);
    };
    
    inline ax::Event::Manager* App::GetEventManager()
    {
        return _evtManager;
    }
    
    inline App* App::GetMainApp()
    {
        return _mainApp;
    }
}

/// @}
#endif //__AX_APP__