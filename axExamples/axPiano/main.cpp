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
#include "Audio.h"

MainPanel::MainPanel(ax::App* app, const ax::Rect& rect):
// Parent.
axPanel(app, rect)
{

                                 
}

void MainPanel::OnButtonClick(const ax::Button::Msg& msg)
{

}

void MainPanel::OnResize(const ax::Size& size)
{
    ax::Print("MainPanel::OnResize : size : ", size.x, size.y);
    SetSize(size);
    
//    _fileBrowser->SetSize(ax::Size(200, size.y - 40));
}

void MainPanel::OnPaint()
{
    ax::GC gc;
    ax::Rect rect(GetDrawingRect());
    
    gc.SetColor(ax::Color(0.95));
    gc.DrawRectangle(rect);
    
    gc.SetColor(ax::Color(0.75));
    gc.DrawRectangle(ax::Rect(0, 0, rect.size.x , 40));
    
    gc.SetColor(ax::Color(0.45));
    gc.DrawRectangleContour(rect);
}

int main(int argc, char* argv[])
{
    AudioPiano piano;
    ax::App app(ax::Size(550, 500));

    app.AddMainEntry([&app]()
    {
        MainPanel* mainPanel = new MainPanel(&app, ax::Rect(0, 0, 550, 500));
    });
    
    app.AddAfterGUILoadFunction([&piano]
                                {
                                    piano.InitAudio();
                                    piano.StartAudio();
                                });

	app.MainLoop();
    
	return 0;
}
