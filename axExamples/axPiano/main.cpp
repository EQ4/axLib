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

#include "AudioPiano.h"
#include "MidiPiano.h"


MainPanel::MainPanel(ax::App* app, const ax::Rect& rect):
// Parent.
axPanel(app, rect),
_loadPercent(0.0)
{

}

void MainPanel::OnButtonClick(const ax::Button::Msg& msg)
{

}

void MainPanel::OnLoadSampleProcess(const ax::Event::SimpleMsg<double>& msg)
{
    ax::Print("Msg :", msg.GetMsg());
    _loadPercent = msg.GetMsg();
    Update();
}

void MainPanel::OnResize(const ax::Size& size)
{
//    ax::Print("MainPanel::OnResize : size : ", size.x, size.y);
    SetSize(size);
}

void MainPanel::OnPaint()
{
    ax::GC gc;
    ax::Rect rect(GetDrawingRect());
    
    gc.SetColor(ax::Color(0.95));
    gc.DrawRectangle(rect);
    
    gc.SetColor(ax::Color(0.75));
    gc.DrawRectangle(ax::Rect(0, 0, rect.size.x , 40));
    
    
    gc.SetColor(ax::Color(0.2, 0.45, 0.9));
    gc.DrawRectangle(ax::Rect(100, 100, 300 * _loadPercent, 20));
    
    gc.SetColor(ax::Color(0.0));
    gc.DrawRectangleContour(ax::Rect(100, 100, 300, 20));
    
    gc.SetColor(ax::Color(0.45));
    gc.DrawRectangleContour(rect);
}

int main(int argc, char* argv[])
{
    ax::App app(ax::Size(550, 500));
    
    AudioPiano piano(&app);
    PianoMidi midi(&piano);

    app.AddMainEntry([&app, &piano]()
    {
        MainPanel* mainPanel = new MainPanel(&app, ax::Rect(0, 0, 550, 500));
        piano.AddConnection(0, mainPanel->GetOnLoadSampleProcess());
    });
    
    std::thread load_thread([&piano]
                            {
                                piano.LoadSamples();
                            });

//    app.AddAfterGUILoadFunction([&piano]
//                                {
//                                    std::thread load_thread([&piano]
//                                                            {
//                                                                piano.LoadSamples();
//                                                            });
//                                    
////                                    piano.InitAudio();
////                                    piano.StartAudio();
//                                });

	app.MainLoop();
    
	return 0;
}
