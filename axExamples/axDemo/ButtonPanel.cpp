//
//  ButtonPanel.cpp
//  Demo
//
//  Created by Alexandre Arsenault on 2014-11-02.
//  Copyright (c) 2014 Alexandre Arsenault. All rights reserved.
//

#include "ButtonPanel.h"

ButtonPanel::ButtonPanel(axWindow* parent,
                         const axRect& rect):
// Parent.
axPanel(parent, rect)
{
    _selector = new axWidgetSelector(this);
    
//    _drawingBuffer = new axDsrawingBuffer(rect.size);
//    _drawingBuffer->DrawRectangle();
    
    std::string app_path(axApp::GetInstance()->GetAppDirectory());
    
    axButton::Info btn1_info;
    btn1_info.normal = axColor(1.0, 0.0, 0.0, 0.3);
    btn1_info.hover = axColor(0.9, 0.9, 0.9, 0.3);
    btn1_info.clicking = axColor(0.7, 0.7, 0.7, 0.3);
    btn1_info.contour = axColor(0.0, 0.0, 1.0, 0.5);
    btn1_info.selected = btn1_info.normal;
    btn1_info.round_corner_radius = 3;
    
    axButton::Events btn1_evts;
    btn1_evts.button_click = GetOnButtonWithEvtManager();
    
    axButton* btn1 = new axButton(this,
                                  axRect(40, 40, 60, 25),
                                  btn1_evts,
                                  btn1_info,
                                  "", "Btn1");

    
    axButton::Info btn2_info;
    btn2_info.normal = axColor(1.0, 0.0, 0.0, 1.0);
    btn2_info.hover = axColor(0.0, 1.0, 0.0, 1.0);
    btn2_info.clicking = axColor(0.0, 0.0, 1.0, 1.0);
    btn2_info.contour = axColor(0.0, 0.0, 0.0, 0.0);
    btn2_info.selected = btn2_info.normal;
    btn2_info.round_corner_radius = 0;
    
    axButton* btn6 = new axButton(this,
                                  axRect(390, 40, 25, 25),
                                  axButton::Events(),
                                  btn2_info,
                                  app_path + std::string("playTest.png"),
                                  "",
								  axButton::Flags::IMG_RESIZE);
    
    axButton* btn7 = new axButton(this,
                                  axRect(390, 90, 25, 25),
                                  axButton::Events(),
                                  axBUTTON_TRANSPARENT,
                                  app_path + std::string("playTest.png"),
                                  "",
                                  axButton::Flags::IMG_RESIZE);
    
    _timer = new axTimer();
    _timer->AddConnection(0, GetOnTimerEvent());
    
    _colorTimer = axColor(1.0, 1.0, 1.0);

    
    axButton* btn9 = new axButton(this,
                                  axRect(240, 40, 12, 12),
                                  axButton::Events(),
                                  axBUTTON_TRANSPARENT,
                                  app_path + std::string("upSquare.png"));
    
    axButton* btn10 = new axButton(this,
                                   axRect(btn9->GetNextPosDown(-2), axSize(12, 12)),
                                   axButton::Events(),
                                   axBUTTON_TRANSPARENT,
                                   app_path + std::string("downSquare.png"));
    
    // Tab button event.
    axToggle::Events btn_evts;
//    btn_evts.button_click = GetOnTabClick();
    
    // Tab buttons info.
    axToggle::Info btn_info;
    btn_info.normal = axColor(0.8, 0.8, 0.8, 0.0);
    btn_info.hover = axColor(0.9, 0.9, 0.9, 0.0);
    btn_info.clicking = axColor(0.7, 0.7, 0.7, 0.0);
    
    btn_info.selected = axColor(0.8, 0.4, 0.4, 0.0);
    btn_info.selected_hover = axColor(0.9, 0.4, 0.4, 0.0);
    btn_info.selected_clicking = axColor(0.7, 0.4, 0.4, 0.0);
    
    btn_info.contour = axColor(0.0, 0.0, 0.0, 0.0);
    btn_info.font_color = axColor(0.0, 0.0, 0.0, 0.0);
    btn_info.img = "radio.png";
    
    axToggle* togg = new axToggle(this,
                                 axRect(axPoint(150, 200), axSize(15, 15)),
                                 btn_evts,
                                 btn_info,
                                 "");
    
    btn_info.img = "checkbox.png";
    axToggle* togg2 = new axToggle(this,
                                   axRect(axPoint(150, 250), axSize(15, 15)),
                                   btn_evts,
                                   btn_info,
                                   "");
    
    axLabel::Info labelInfo;
    labelInfo.normal = axColor(0.8, 0.8, 0.8, 0.0);
    labelInfo.contour = axColor(0.9, 0.9, 0.9, 0.0);
    labelInfo.font_color = axColor(0.0, 0.0, 0.0, 1.0);
    labelInfo.font_size = 12;
    labelInfo.font_name = "FreeSans.ttf";
    labelInfo._alignement = axALIGN_CENTER;
    
    axLabel* label = new axLabel(this, axRect(100, 200, 70, 30),
                                 labelInfo, "Radio");
    
    axLabel* label2 = new axLabel(this, axRect(20, 250, 70, 30),
                                 labelInfo, "Checkbox");
    
    
    _font = new axFont(0);
    
//    axAnimatedButton* animBtn = new axAnimatedButton(this,
//                                                     axRect(50, 160, 60, 25),
//                                                     axButton::Events(),
//                                                     "axButtonImg.png",
//                                                     "Test");
}

void ButtonPanel::OnButtonWithEvtManager(const axButton::Msg& msg)
{
    Update();
}

void ButtonPanel::OnTimerEvent(const axTimerMsg& msg)
{
//    std::cout << "Timer : " << msg.GetTime() << std::endl;
    double timer_ratio = msg.GetTime() / double(800 - 20) * 0.4;
    _colorTimer = axColor(timer_ratio, timer_ratio, 0.4);
    Update();
}

void ButtonPanel::OnPaint()
{
    axGC* gc = GetGC();
    axRect rect(GetRect());
    axRect rect0(axPoint(0, 0), rect.size);

    gc->SetColor(axColor::axWhiteColor);
    gc->DrawRectangle(rect0);
    
//    gc->DrawTexture(_drawingBuffer->GetTexture(),
//                    axRect(axPoint(0, 0), _drawingBuffer->GetSize()));
    
}