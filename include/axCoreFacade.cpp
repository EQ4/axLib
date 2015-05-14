//
//  axCoreFacade.cpp
//  axLib
//
//  Created by Alexandre Arsenault on 2015-05-14.
//  Copyright (c) 2015 Alexandre Arsenault. All rights reserved.
//

#include "axCoreFacade.h"

#ifdef __linux__
#include "axCoreX11.h"
//#endif //__linux__

#elif _MSC_VER
#if _axWxWidgetsCore_ == 1
#include "axCoreWxWidgets.h"

#else
#include "axCoreWin32.h"
#endif // _axWxWidgetsCore_.
//#endif //_MSC_VER


#else// __APPLE__
#ifdef _AX_VST_APP_
#include "axVstCoreMac.h"
#else
#include "axCoreMac.h"
#endif // _AX_VST_APP_
#endif // __APPLE__

namespace ax
{
    namespace Core
    {
        Facade::Facade(const ax::Size& frame_size)
        {
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
        
        void Facade::Init(const ax::Size& frame_size)
        {
            _core->Init(frame_size);
        }
        
        std::string Facade::GetAppDirectory()
        {
            return _core->GetAppDirectory();
        }
        
        std::string Facade::GetAppPath()
        {
            return _core->GetAppPath();
        }
        
        std::string Facade::OpenFileDialog()
        {
            return _core->OpenFileDialog();
        }
        
        ax::Rect Facade::GetScreenRect()
        {
            return _core->GetScreenRect();
        }
        
        ax::Size Facade::GetScreenSize()
        {
            return _core->GetScreenSize();
        }
        
        ax::Size Facade::GetFrameSize() const
        {
            return _core->GetGlobalSize();
        }
        
        void Facade::SetFrameSize(const ax::Size& size)
        {
            _core->ResizeFrame(size);
        }
        
        ax::Core::WindowManager* Facade::GetWindowManager()
        {
            return _core->GetWindowManager();
        }
        
        ax::Core::WindowManager* Facade::GetPopupManager()
        {
            return _core->GetPopupManager();
        }
        
        ax::Core::WindowManager* Facade::GetRealPopWindowManager()
        {
            return _core->GetRealPopWindowManager();
        }
        
        void Facade::UpdateAll()
        {
            _core->UpdateAll();
        }
        
        void Facade::HideMouse()
        {
            _core->HideMouse();
        }
        
        void Facade::ShowMouse()
        {
            _core->ShowMouse();
        }
        
        void Facade::Draw()
        {
            _core->DrawGLScene();
        }
        
        void Facade::MainLoop()
        {
            _core->MainLoop();
        }
        
        void Facade::PushEventOnSystemQueue()
        {
            _core->PushEventOnSystemQueue();
        }
    }
}