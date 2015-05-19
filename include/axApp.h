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
        
        axEditorMenu* GetEditor();
        void CreateEditor();
        
        void SetEditingWidget(axWidget* widget);
        
        axWidgetSelector* _widgetSelector = nullptr;
        
        void ActivateDebugEditor(const bool& active);
        bool IsDebugEditorActive() const;
        
    private:
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