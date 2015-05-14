//
//  axCoreFacade.h
//  axLib
//
//  Created by Alexandre Arsenault on 2015-05-14.
//  Copyright (c) 2015 Alexandre Arsenault. All rights reserved.
//

#ifndef __axLib__axCoreFacade__
#define __axLib__axCoreFacade__

#include <axUtils/axUtils.h>
#include <string>

class axCore;

namespace ax
{
    namespace Core
    {
        class WindowManager;
        
        class Facade
        {
        public:
            Facade(const ax::Size& frame_size);
            
            void Init(const ax::Size& frame_size);
            
            std::string GetAppDirectory();
            
            std::string GetAppPath();
            
            std::string OpenFileDialog();
            
            ax::Rect GetScreenRect();
            
            ax::Size GetScreenSize();
            
            ax::Size GetFrameSize() const;
            
            void SetFrameSize(const ax::Size& size);
            
            ax::Core::WindowManager* GetWindowManager();
            
            ax::Core::WindowManager* GetPopupManager();
            
            ax::Core::WindowManager* GetRealPopWindowManager();
            
            void UpdateAll();
            
            void HideMouse();
            
            void ShowMouse();
            
            void Draw();
            
            void MainLoop();
            
        protected:
            void PushEventOnSystemQueue();
            
        private:
            axCore* _core;
        };
    }
}

#endif /* defined(__axLib__axCoreFacade__) */
