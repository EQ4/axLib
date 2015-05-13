//
//  NSOpenGLView+axPopupWindowCocoaView.m
//  axLib
//
//  Created by Alexandre Arsenault on 2015-05-01.
//  Copyright (c) 2015 Alexandre Arsenault. All rights reserved.
//

#import "NSOpenGLView+axPopupWindowCocoaView.h"
#include "AppDelegate.h"
#include <OpenGL/OpenGL.h>
#include <OpenGL/glu.h>

#include <iostream>
#include "axLib.h"
//#include "axMath.h"

//#include "axGraphicInterface.h"

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
    [[self openGLContext] makeCurrentContext];
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
    
    
    
    
    
//    axApp* app = axApp::GetInstance();
//    app->CallPopupEntryFunction();
    
    
    
    [delegate setNeedsDisplay:YES];
    [delegate setNeedsDisplay:YES];
    [delegate setNeedsDisplay:YES];
    
    [GlobalAppDelegate setNeedsDisplay:YES];

}

-(id)MemberTestFunc
{
//#ifdef _AX_VST_APP_
//    axApp* app = axApp::CreateApp();
//    axVstCoreMac* vstCoreMac = static_cast<axVstCoreMac*>(app->GetCore());
//    axAppDelegate* delegate = (__bridge axAppDelegate*)vstCoreMac->GetCurrentAppDelegate();
//    
//    [delegate setNeedsDisplay:YES];
//    return delegate;
//#else
    
    [global_popup_view setNeedsDisplay:YES];
    
    return self;
//#endif // _AX_VST_APP_
    
}

- (void)viewDidMoveToWindow
{
//    [[self openGLContext] makeCurrentContext];
//    std::cout << "viewDidMoveToWindow" << std::endl;
//    [self addTrackingRect:[self bounds] owner:self userData:NULL assumeInside:YES];
//    [[self window] makeFirstResponder:self];
//    
//    
//    global_popup_view = self;
//    
//    
//    
//    axApp* app = axApp::GetInstance();
//    app->CallPopupEntryFunction();
//    
//    [self setNeedsDisplay:YES];
    
}



-(void)mouseDown:(NSEvent *)event
{
    
    std::cout << "Mouse down" << std::endl;
    [self setNeedsDisplay:YES];
}







// Each time window has to be redrawn, this method is called
- (void)drawRect:(NSRect)bounds
{
//    [[self openGLContext] makeCurrentContext];
//    
//    std::cout << "Draw popup window." << std::endl;
//
//    NSRect backingBounds = [self convertRectToBacking:[self bounds]];
//    axSize size(backingBounds.size.width, backingBounds.size.height);
//    axPrint("Size :", size.x, size.y);
//    
//    axGraphicInterface::Resize(size);
//    
//    axGraphicInterface::Draw(size);
//    axManager* man = axApp::GetInstance()->GetCore()->GetRealPopWindowManager();
//    axWindowTree* man_tree = man->GetWindowTree();
//    man->OnPaint();
//    glFlush();
}

@end
