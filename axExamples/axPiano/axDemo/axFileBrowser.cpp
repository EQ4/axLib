//
//  axFileBrowser.cpp
//  axDemo
//
//  Created by Alexandre Arsenault on 2015-05-11.
//  Copyright (c) 2015 Alexandre Arsenault. All rights reserved.
//

#include "axFileBrowser.h"
//#include <axGL/axGL.h>
//#include <axGL/axGLMath.h>

namespace ax
{
    FileBrowser::FileBrowser(axWindow* parent, const ax::Rect& rect):
    // Parent.
    axPanel(parent, rect)
    {
        
        _rotate = 0.0;
        
        _timer = new ax::Event::Timer(GetApp()->GetEventManager(),
                                      GetOnTimer());
        
        using ms = ax::Event::Timer::TimeMs;
        _timer->StartTimer(ms(50), ms(10000000));
        ///ax::StringVector dir = ax::Utils::ListDirectory("/Users/alexarse/");
        
//        for(auto& n : dir)
//        {
//            axPrint(n);
//        }
    }
    
    void FileBrowser::OnTimer(const ax::Event::Timer::Msg& msg)
    {
        _rotate += 3.9;
        Update();
    }
    
    void FileBrowser::OnPaint()
    {
        ax::GC gc;
        ax::Rect rect(GetDrawingRect());
        
        gc.SetColor(ax::Color(0.55));
        gc.DrawRectangle(rect);
        
        gc.SetColor(ax::Color(0.45));
        gc.DrawRectangleContour(rect);

        
//        glAlphaFunc ( GL_GREATER, 0.1 ) ;
//        glEnable ( GL_ALPHA_TEST ) ;
        
//        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//        glEnable( GL_BLEND );

//        glEnable (GL_BLEND);
//        glBlendFunc (GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
        
        glDisable(GL_BLEND);
        
        glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);				// Black Background
        glClearDepth(1.0f);									// Depth Buffer Setup
        glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
        glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
        glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations

        glViewport(0, 0, rect.size.x, rect.size.y);						// Reset The Current Viewport
        
        glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
        glLoadIdentity();									// Reset The Projection Matrix
        
        // Calculate The Aspect Ratio Of The Window
        gluPerspective(45.0f,(GLfloat)rect.size.x/(GLfloat)rect.size.y,0.1f,100.0f);
        
//        glViewport(0, 0, rect.size.x, rect.size.y);
//        
//        glMatrixMode(GL_PROJECTION);
//        
//        ax::GL::Math::Matrix4 proj;
//        ax::GL::Math::Ortho2D(proj.Identity().GetData(), rect.size);
        
        // Select the modelview matrix.
        glMatrixMode(GL_MODELVIEW);

        glLoadIdentity();
        glTranslatef(0.0f,0.0f,-12.0f);
        
        glRotatef(_rotate, 1.0f,1.0f,1.0f);

        glBegin(GL_QUADS);
        glColor3f(0.0f, 1.0f, 0.0f);          // Set The Color To Green
        glVertex3f( 1.0f, 1.0f,-1.0f);          // Top Right Of The Quad (Top)
        glVertex3f(-1.0f, 1.0f,-1.0f);          // Top Left Of The Quad (Top)
        glVertex3f(-1.0f, 1.0f, 1.0f);          // Bottom Left Of The Quad (Top)
        glVertex3f( 1.0f, 1.0f, 1.0f);          // Bottom Right Of The Quad (Top)

        
        glColor3f(1.0f,0.5f,0.0f);          // Set The Color To Orange
        glVertex3f( 1.0f,-1.0f, 1.0f);          // Top Right Of The Quad (Bottom)
        glVertex3f(-1.0f,-1.0f, 1.0f);          // Top Left Of The Quad (Bottom)
        glVertex3f(-1.0f,-1.0f,-1.0f);          // Bottom Left Of The Quad (Bottom)
        glVertex3f( 1.0f,-1.0f,-1.0f);          // Bottom Right Of The Quad (Bottom)

        glColor3f(1.0f,0.0f,0.0f);          // Set The Color To Red
        glVertex3f( 1.0f, 1.0f, 1.0f);          // Top Right Of The Quad (Front)
        glVertex3f(-1.0f, 1.0f, 1.0f);          // Top Left Of The Quad (Front)
        glVertex3f(-1.0f,-1.0f, 1.0f);          // Bottom Left Of The Quad (Front)
        glVertex3f( 1.0f,-1.0f, 1.0f);          // Bottom Right Of The Quad (Front)

        glColor3f(1.0f,1.0f,0.0f);          // Set The Color To Yellow
        glVertex3f( 1.0f,-1.0f,-1.0f);          // Bottom Left Of The Quad (Back)
        glVertex3f(-1.0f,-1.0f,-1.0f);          // Bottom Right Of The Quad (Back)
        glVertex3f(-1.0f, 1.0f,-1.0f);          // Top Right Of The Quad (Back)
        glVertex3f( 1.0f, 1.0f,-1.0f);          // Top Left Of The Quad (Back)
        
        glColor3f(0.0f,0.0f,1.0f);          // Set The Color To Blue
        glVertex3f(-1.0f, 1.0f, 1.0f);          // Top Right Of The Quad (Left)
        glVertex3f(-1.0f, 1.0f,-1.0f);          // Top Left Of The Quad (Left)
        glVertex3f(-1.0f,-1.0f,-1.0f);          // Bottom Left Of The Quad (Left)
        glVertex3f(-1.0f,-1.0f, 1.0f);          // Bottom Right Of The Quad (Left)

        glColor3f(1.0f,0.0f,1.0f);          // Set The Color To Violet
        glVertex3f( 1.0f, 1.0f,-1.0f);          // Top Right Of The Quad (Right)
        glVertex3f( 1.0f, 1.0f, 1.0f);          // Top Left Of The Quad (Right)
        glVertex3f( 1.0f,-1.0f, 1.0f);          // Bottom Left Of The Quad (Right)
        glVertex3f( 1.0f,-1.0f,-1.0f);          // Bottom Right Of The Quad (Right)
        glEnd();                        // Done Drawing The Quad

        glEnable( GL_BLEND );
    }
    
}