//
//  main.cpp
//  Demo
//
//  Created by Alexandre Arsenault on 2014-11-02.
//  Copyright (c) 2014 Alexandre Arsenault. All rights reserved.
//

#include "main.h"


MainPanel::MainPanel(axWindow* parent, const axRect& rect):
// Parent.
axPanel(parent, rect)
{
    
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
    
    axApp* app = GetApp();
    std::string btnInfoPath(app->GetResourceFile("axButtonBlueInfo.axobj"));
    
    axButton* btn = new axButton(this, axRect(150, 150, 60, 25),
                                 axButton::Events(),
                                 axButton::Info(btnInfoPath),
                                 "",
                                 "Button");
}


void MainPanel::OnPaint()
{
    axGC* gc = GetGC();
    axRect rect(GetRect());
    axRect rect0(axPoint(0, 0), rect.size);
    
    gc->SetColor(axColor(0.95));
    gc->DrawRectangle(rect0);
    
//    
//    gc->SetColor(axColor(0.0, 0.0, 0.0), 1.0);
//    gc->DrawRectangleContour(rect0);
    
}

int main(int argc, char* argv[])
{
    
    axPrint("Main");
	axEventManager::GetInstance();
	axApp* app = axApp::CreateApp(axSize(550, 500));

    app->AddMainEntry([]()
    {
        MainPanel* mainPanel = new MainPanel(nullptr, axRect(0, 0, 550, 500));
    });

	app->MainLoop();
	return 0;
}
