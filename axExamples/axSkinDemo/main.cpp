//
//  main.cpp
//  Demo
//
//  Created by Alexandre Arsenault on 2014-11-02.
//  Copyright (c) 2014 Alexandre Arsenault. All rights reserved.
//

#include "main.h"
#include <axlib/axCocoaInterfaceMac.h>
#include "axFileBrowser.h"

MainPanel::MainPanel(axApp* app, const axRect& rect):
// Parent.
axPanel(app, rect)
{
    
    _fileBrowser = new ax::FileBrowser(this,
                                       axRect(0, 40, 200, rect.size.y - 40));
    
    axToggle::Events toggle_events;
    
    axRadio::Info radio_info;
    radio_info.normal = axColor(0.8, 0.8, 0.8, 0.0);
    radio_info.hover = axColor(0.9, 0.9, 0.9, 0.0);
    radio_info.clicking = axColor(0.7, 0.7, 0.7, 0.0);
    
    radio_info.selected = axColor("#35A6EE");
    radio_info.selected_hover = axColor("#35A6EE");
    radio_info.selected_clicking = axColor("#35A6EE");
    
    radio_info.contour = axColor("#35A6EE");
//    radio_info.font_color = axColor(0.0, 0.0, 0.0, 0.0);
    radio_info.img = "";
    radio_info.single_img = false;
    
    axRadio* radio = new axRadio(this,
                                  axRect(axPoint(50, 50), axSize(18, 18)),
                                  toggle_events,
                                  radio_info,
                                  "");
    
    axToggle::Info tog_info;
    tog_info.normal = axColor(0.8, 0.8, 0.8, 0.0);
    tog_info.hover = axColor(0.9, 0.9, 0.9, 0.0);
    tog_info.clicking = axColor(0.7, 0.7, 0.7, 0.0);
    
    tog_info.selected = axColor(0.8, 0.4, 0.4, 0.0);
    tog_info.selected_hover = axColor(0.9, 0.4, 0.4, 0.0);
    tog_info.selected_clicking = axColor(0.7, 0.4, 0.4, 0.0);
    
    tog_info.contour = axColor(0.0, 0.0, 0.0, 0.0);
    tog_info.font_color = axColor(0.0, 0.0, 0.0, 0.0);
    tog_info.img = "checkbox.png";
    tog_info.single_img = false;
    
    axToggle* togg2 = new axToggle(this,
                                   axRect(axPoint(50, 100), axSize(15, 15)),
                                   toggle_events,
                                   tog_info,
                                   "");
    
//    axApp* app = GetApp();
    std::string btnInfoPath(app->GetResourceFile("axButtonBlueInfo.axobj"));
    
    axButton* btn = new axButton(this, axRect(150, 150, 60, 25),
                                 GetOnButtonClick(),
                                 axButton::Info(btnInfoPath),
                                 "",
                                 "Button");
    
    
//    axButton* btn_pop = new axButton(this, axRect(150, 150, 60, 25),
//                                 GetOnButtonClick(),
//                                 axButton::Info(btnInfoPath),
//                                 "",
//                                 "Button");
    
    axPanel* panel2 = new axPanel(this, axRect(10, 10, 60, 25));
    panel2->SetWindowColor(axColor(1.0, 0.0, 0.0));
                                 
}

void MainPanel::OnButtonClick(const axButton::Msg& msg)
{
    axPrint("Btn click.");
//
//    std::function<void()> popup_fct = [&]()
//    {
//        std::cout << "popup fct." << std::endl;
//        SetCurrentOpenGLContext();
//        
//        axPanel* panel = new axPanel(86, nullptr, axRect(0, 0, 200, 270));
//        panel->SetWindowColor(axColor(1.0, 0.0, 0.0));
//        panel->SetRealPopupWindow(true);
//        
//        axApp* app = GetApp();
//        std::string btnInfoPath(app->GetResourceFile("axButtonBlueInfo.axobj"));
//        axButton* btn = new axButton(panel, axRect(10, 10, 60, 25),
//                                     axButton::Events(),
//                                     axButton::Info(btnInfoPath),
//                                     "",
//                                     "Button");
//
//        
//        
//    };
//    
//    SetCurrentOpenGLContext();
//    axApp::GetInstance()->AddPopupEntryFunction(popup_fct);
//    
//    CreateNewPopupWindow();
    
    
    
    
//    NewWindowController *controllerWindow = [[NewWindowController alloc] initWithWindowNibName:@"You Window XIB Name"];
//    [controllerWindow showWindow:self];
}

void MainPanel::OnResize(const axSize& size)
{
    axPrint("MainPanel::OnResize : size : ", size.x, size.y);
    SetSize(size);
    
    _fileBrowser->SetSize(axSize(200, size.y - 40));
}

void MainPanel::OnPaint()
{
    axGC gc(this);
    axRect rect(GetDrawingRect());
    
    gc.SetColor(axColor(0.95));
    gc.DrawRectangle(rect);
    
    gc.SetColor(axColor(0.75));
    gc.DrawRectangle(axRect(0, 0, rect.size.x , 40));
    
//    gc.SetColor(axColor(0.55));
//    gc.DrawRectangle(axRect(0, 40, 200 , rect.size.y - 40));
    
    gc.SetColor(axColor(0.45));
    gc.DrawRectangleContour(rect);
    
}

int main(int argc, char* argv[])
{
//	axEventManager::GetInstance();
    axApp app(axSize(550, 500));
//	axApp* app = axApp::CreateApp(axSize(550, 500));

    app.AddMainEntry([&app]()
    {
        MainPanel* mainPanel = new MainPanel(&app, axRect(0, 0, 550, 500));
    });

	app.MainLoop();
    
	return 0;
}
