//
//  NSOpenGLView+axPopupWindowCocoaView.m
//  axLib
//
//  Created by Alexandre Arsenault on 2015-05-01.
//  Copyright (c) 2015 Alexandre Arsenault. All rights reserved.
//

#import "NSOpenGLView+axPopupWindowCocoaView.h"
#include <OpenGL/OpenGL.h>
#include <OpenGL/glu.h>

#include <iostream>
#include "axLib.h"
#include "axMath.h"

axPopupWindowCocoaView* global_popup_view = nullptr;

@implementation axPopupWindowCocoaView

//- (id)initWithWindowNibName:(NSString *)nibNameOrNil
//{
//    std::cout << "axPopupWindowCocoaView with file" << std::endl;
//    
//    self = [super initWithWindowNibName:nibNameOrNil ];
//    
//    if (self)
//    {
//        // Initialization code here.
//        [self setNeedsDisplay:YES];
//    }
//    
//    return self;
//}

//- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
//{
//    std::cout << "axPopupWindowCocoaView initWithNibName" << std::endl;
//    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
//    
//    if (self)
//    {
//        // Initialization code here.
//    }
//    
//    return self;
//}

- (id)initWithFrame:(NSRect)frame
{
//    [self installRunLoopObserver];
    
    self = [super initWithFrame:frame];
    
    std::cout << "axPopupWindowCocoaView Init" << std::endl;
//    self = [super initWithWindowNibName:@"axPopupWindow"];
    
//    NSWindowController* ctrlWindow = [[NSWindowController alloc] initWithWindowNibName:@"axPopupWindow"];
//    [ctrlWindow showWindow:self];
    
    
//    [[ctrlWindow window] setView:
//    [ctrlWindow t]
//    [menuItem setView:[viewController view]];
    
//    [[[ctrlWindow window] contentView] addSubview:self];
//    [[ctrlWindow contentView] addSubview:self];
    
//    [[ctrlWindow window] makeFirstResponder:self];
    
    //self = [super initWithFrame:frame];
    
    // Helps optimize Open GL context initialization for the best available
    // resolution, important for Retina screens for example.
//    if (self)
//    {
//        [self wantsBestResolutionOpenGLSurface];
//    }
    
    [self setNeedsDisplay:YES];
    
    return self;
}

- (void)prepareOpenGL
{
    std::cout << "prepareOpenGL" << std::endl;
    
    // Synchronize buffer swaps with vertical refresh rate
    GLint swapInt = 1;
    [[self window] setAcceptsMouseMovedEvents:YES];
    [[self openGLContext] setValues:&swapInt forParameter:NSOpenGLCPSwapInterval];
    
    
    axPopupWindowCocoaView* delegate = (__bridge axPopupWindowCocoaView*)
    global_popup_view;
    
    [[delegate openGLContext] makeCurrentContext];
    
    // Enable Smooth Shading.
    glShadeModel(GL_SMOOTH);
    
    // Black Background
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    
    // Depth Buffer Setup
    glClearDepth(1.0f);
    
    // Enables Depth Testing
    glEnable(GL_DEPTH_TEST);
    
    glEnable(GL_BLEND); // Enable blending.
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    // The type of depth testing to do.
    glDepthFunc(GL_LEQUAL);
    
    // Really nice perspective calculations.
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    
    
    
    
    
    axApp* app = axApp::GetInstance();
    app->CallPopupEntryFunction();
    
    
    
    [delegate setNeedsDisplay:YES];
    [delegate setNeedsDisplay:YES];
    [delegate setNeedsDisplay:YES];
    
    
//
//    app->GetCore()->Init(axSize(500, 500));
    
//    app->CallMainEntryFunction();
//    app->CallAfterGUILoadFunction();
//    app->CreateEditor();
//#ifdef _AX_VST_APP_
//    axApp* app = axApp::CreateApp();
//    
//    axVstCoreMac* vstCoreMac = static_cast<axVstCoreMac*>(app->GetCore());
//    axVstCoreData* coreData = vstCoreMac->GetVstCoreData();
//    
//    if(coreData->appDelegate == nullptr)
//    {
//        coreData->appDelegate = (__bridge void*)GlobalAppDelegate;
//    }
//    
//    axMain::MainEntryPoint(app);
//    
//    axAppDelegate* d = (__bridge axAppDelegate*)coreData->appDelegate;
//    [d setNeedsDisplay:YES];
//    
//#else
//    //axEventManager::GetInstance();
//    axApp* app = axApp::GetInstance();
//    
//    app->GetCore()->Init(axSize(500, 500));
//    
//    app->CallMainEntryFunction();
//    app->CallAfterGUILoadFunction();
//    app->CreateEditor();
//    
//    
//    [GlobalAppDelegate setNeedsDisplay:YES];
//#endif // _AX_VST_APP_
}

- (void)viewDidMoveToWindow
{
    std::cout << "viewDidMoveToWindow" << std::endl;
    [self addTrackingRect:[self bounds] owner:self userData:NULL assumeInside:YES];
    [[self window] makeFirstResponder:self];
    
    
    global_popup_view = self;
    
    [self setNeedsDisplay:YES];
    
    
//
//    GlobalAppDelegate = self;
}



-(void)mouseDown:(NSEvent *)event
{
    
    std::cout << "Mouse down" << std::endl;
    [self setNeedsDisplay:YES];
//    NSPoint locationInView = [self convertPoint:[event locationInWindow]
//                                       fromView:nil];
//    
//    axPoint pos(locationInView.x, locationInView.y);
//    
//    // Double click.
//    if (event.clickCount == 2)
//    {
//        axApp::GetInstance()->GetPopupManager()->OnMouseLeftDoubleClick(pos);
//        if(axApp::GetInstance()->GetPopupManager()->IsEventReachWindow() == false)
//        {
//            axApp::GetInstance()->GetWindowManager()->OnMouseLeftDoubleClick(pos);
//        }
//    }
//    
//    // Simple click.
//    else
//    {
//        axApp::GetInstance()->GetPopupManager()->OnMouseLeftDown(pos);
//        
//        if(axApp::GetInstance()->GetPopupManager()->IsEventReachWindow() == false)
//        {
//            axApp::GetInstance()->GetWindowManager()->OnMouseLeftDown(pos);
//        }
//    }
}







// Each time window has to be redrawn, this method is called
- (void)drawRect:(NSRect)bounds
{
    std::cout << "Draw popup window." << std::endl;
    int frame_height = bounds.size.height;
//
    NSRect backingBounds = [self convertRectToBacking:[self bounds]];
    axSize size(backingBounds.size.width, backingBounds.size.height);
    
    
    // RESIZE.
    glViewport(0, 0, size.x, size.y);
    glMatrixMode(GL_PROJECTION);
    
    axMatrix4 proj;
    axOrtho2D(proj.Identity().GetData(), size);
    
    // Select the modelview matrix.
    glMatrixMode(GL_MODELVIEW);
    
//    if ([self inLiveResize])
//    {
//        // Draw a quick approximation
//        //        std::cout << "Live resize drawing." << std::endl;
//    }
//    else
//    {
        // Clear screen and depth buffer.
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        // Set projection matrix.
        glMatrixMode(GL_PROJECTION);
        
//        axMatrix4 proj;
//        axOrtho2D(proj.Identity().GetData(), size);
    
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        
        // Draw black rectangle.
        glColor4d(0.0, 1.0, 1.0, 1.0);
        // Draw black rectangle.
        axFloatRect rect(-1.0, -1.0, size.x * 2.0, size.y * 2.0);
        axRectFloatPoints points = rect.GetPoints();
        GLubyte indices[] = {0, 1,2, 2,3};
        glEnableClientState(GL_VERTEX_ARRAY);
        glVertexPointer(2, GL_DOUBLE, 0, &points);
        glDrawElements(GL_TRIANGLE_FAN, 6, GL_UNSIGNED_BYTE, indices);
        glDisableClientState(GL_VERTEX_ARRAY);

        
        axManager* man = axApp::GetInstance()->GetCore()->GetRealPopWindowManager();
        axWindowTree* man_tree = man->GetWindowTree();
    
        man->OnPaint();
        glFlush();
//    }

//
//    axCore* core = axApp::GetInstance()->GetCore();
//
//    axSize global_size = core->GetGlobalSize();
//    if(global_size.x != backingBounds.size.width ||
//       global_size.y != backingBounds.size.height)
//    {
//        core->ResizeGLScene(axSize(backingBounds.size.width,
//                                   backingBounds.size.height));
//        //        core->ResizeGLScene(backingBounds.size.width,
//        //                            backingBounds.size.height,
//        //                            frame_height - backingBounds.size.height);
//    }
//    
//    if ([self inLiveResize])
//    {
//        // Draw a quick approximation
//        //        std::cout << "Live resize drawing." << std::endl;
//    }
//    else
//    {
//        // Is only gonna draw if necessary.
//        core->DrawGLScene();
//        glFlush();
//    }
    
}

@end
