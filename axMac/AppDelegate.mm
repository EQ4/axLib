
/*******************************************************************************
 * Copyright (c) 2013 Alexandre Arsenault.
 *
 * This file is part of axLibrary.
 *
 * axLibrary is free or commercial software: you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 or any later version of the
 * License or use a commercial axLibrary License.
 *
 * axLibrary is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with axLibrary. If not, see <http://www.gnu.org/licenses/>.
 *
 * To release a closed-source product which uses axLibrary, commercial
 * licenses are available, email alx.arsenault@gmail.com for more information.
 ******************************************************************************/
#import "AppDelegate.h"


#include <axEvent/axEventManager.h>
#include <OpenGL/OpenGL.h>
#include <OpenGL/glu.h>
#include "axCocoaInterfaceMac.h"
#include "axWindowManager.h"
#include <iostream>
#include "axLib.h"

//axApp* GlobalApp = nullptr;
axAppDelegate* GlobalAppDelegate = nullptr;

@implementation axAppDelegate

- (id)initWithFrame:(NSRect)frame
{
    std::cout << "Enter - (id)initWithFrame:(NSRect)frame " << std::endl;
    [self installRunLoopObserver];
    
    self = [super initWithFrame:frame];
    
    // Helps optimize Open GL context initialization for the best available
    // resolution, important for Retina screens for example.
    if (self)
    {
        
        [self wantsBestResolutionOpenGLSurface];
    }

    return self;
}



- (void)viewDidMoveToWindow
{
    std::cout << "viewDidMoveToWindow" << std::endl;
    
//     trackingRect = [self addTrackingRect:eyeBox owner:self userData:NULL assumeInside:NO];
    
    [self addTrackingRect:[self bounds] owner:self userData:NULL assumeInside:YES];
    [[self window] makeFirstResponder:self];
    [[self window] setAcceptsMouseMovedEvents:YES];
    
    
   
}

//-(BOOL) canBecomeKeyWindow
//{
//    return YES;
//}

-(BOOL) canBecomeMainWindow
{
    return YES;
}

- (void)applicationDidFinishLaunching:(NSNotification *)aNotification
{
    std::cout << "applicationDidFinishLaunching" << std::endl;
    
    
//    [[self window] setAcceptsMouseMovedEvents:YES];

//    NSArray* args = [[NSProcessInfo processInfo] arguments];
    // use -objectAtIndex: to obtain an element of the array
    // and -count to obtain the number of elements in the array
    
    
//    _axApp = axApp::GetMainApp();
////    _axApp->GetCore()->Init(ax::Size(500, 500));
//    
//    _axApp->CallMainEntryFunction();
//    _axApp->CallAfterGUILoadFunction();
//    _axApp->CreateEditor();
}

- (void)prepareOpenGL
{
    std::cout << "prepareOpenGL" << std::endl;
    GlobalAppDelegate = self;
    
    // Synchronize buffer swaps with vertical refresh rate
    GLint swapInt = 1;
    [[self window] setAcceptsMouseMovedEvents:YES];
    [[self openGLContext] setValues:&swapInt forParameter:NSOpenGLCPSwapInterval];
    
#ifdef _AX_VST_APP_
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
#else
    
    _axApp = ax::App::GetMainApp();
    _axApp->Init(ax::Size(500, 500));
//    _axApp->GetCore()->Init(ax::Size(500, 500));
    
    _axApp->CallMainEntryFunction();
    _axApp->CallAfterGUILoadFunction();
//    _axApp->CreateEditor();
    //axEventManager::GetInstance();
//    axApp* app = axApp::GetInstance();
    
    
    
    //**************************************************************************

//    app->GetCore()->Init(ax::Size(500, 500));
//    
//    app->CallMainEntryFunction();
//    app->CallAfterGUILoadFunction();
//    app->CreateEditor();
    
    
    
    //**************************************************************************

    
    [GlobalAppDelegate setNeedsDisplay:YES];
#endif // _AX_VST_APP_
}

-(void)awakeFromNib
{

}

-(id)MemberTestFunc
{
#ifdef _AX_VST_APP_
    axApp* app = axApp::CreateApp();
    axVstCoreMac* vstCoreMac = static_cast<axVstCoreMac*>(app->GetCore());
    axAppDelegate* delegate = (__bridge axAppDelegate*)vstCoreMac->GetCurrentAppDelegate();

    [delegate setNeedsDisplay:YES];
    return delegate;
#else
    
    [GlobalAppDelegate setNeedsDisplay:YES];
    
    return self;
#endif // _AX_VST_APP_

}

- (void)windowDidResize:(NSNotification *)notification
{
    
    ax::Size size([[self window] frame].size.width,
                [[self window] frame].size.height);
    
    ax::Size size2([self bounds].size.width,
                 [self bounds].size.height);
    
    ax::Size size3([[self window] contentLayoutRect].size.width,
                [[self window] contentLayoutRect].size.height);
    
    ax::Print("windowDidResize. : ", size.x, size.y);
    ax::Print("Bounds : ", size2.x, size2.y);
    ax::Print("Content : ", size3.x, size3.y);
    
//    ax::Size size(frameSize.width, frameSize.height);
    
    
    ///*************************************************************************************************************************************
    ///*************************************************************************************************************************************
    ///*************************************************************************************************************************************
//    ax::App::GetMainApp()->GetCore()->ResizeGLScene(size3);
    ax::App::GetMainApp()->SetFrameSize(size3);
    ///*************************************************************************************************************************************
    ///*************************************************************************************************************************************
    ///*************************************************************************************************************************************
    
    // Resize openGL panel.
    [GlobalAppDelegate setFrame:NSMakeRect(0.f, 0.f, size3.x, size3.y)];
                                           
//    _axApp->GetWindowManager()->OnSize(size3);
    
//    [GlobalAppDelegate setBounds:NSMakeRect(0.f, 0.f, size3.x, size3.y)];

//    std::cout << "windowDidResize. : " << std::endl;
}

//- (NSSize)windowWillResize:(NSWindow *)sender
//                    toSize:(NSSize)frameSize
//{
////    std::cout << "windowWillResize. " << std::endl;
////    return frameSize;
//    
//    // Resize frame.
////    [[GlobalAppDelegate window] setContentSize : frameSize];
////    // Resize openGL panel.
////    [GlobalAppDelegate setFrame:NSMakeRect(0.f, 0.f,
////                                           frameSize.width, frameSize.height)];
////    
////    [GlobalAppDelegate setBounds:NSMakeRect(0.f, 0.f,
////                                            frameSize.width, frameSize.height)];
////    
////    ax::Size size(frameSize.width, frameSize.height);
////    _axApp->GetWindowManager()->OnSize(size);
//
//    return frameSize;
//}
//- (void)windowDidResize:(NSEvent *)event
//{
//    std::cout << "Resize. " << std::endl;
//}

//- (NSSize)windowWillResize:(NSWindow *)sender
//                    toSize:(NSSize)frameSize
//{
//    std::cout << "windowWillResize. " << std::endl;
//}

- (void)windowDidMove:(NSNotification *)notification
{
//    std::cout << "Mouve. " << std::endl;
}

//- (void) setFrameSize:(NSSize)newSize
//{
//
//}



- (void) SetFrameSize:(NSSize)newSize
{
    // Resize frame.
    [[GlobalAppDelegate window] setContentSize : newSize];

    // Resize openGL panel.
    [GlobalAppDelegate setFrame:NSMakeRect(0.f, 0.f,
                                           newSize.width, newSize.height)];
    
    [GlobalAppDelegate setBounds:NSMakeRect(0.f, 0.f,
                                            newSize.width, newSize.height)];
}


// Working.
-(void)mouseDown:(NSEvent *)event
{
    NSPoint locationInView = [self convertPoint:[event locationInWindow]
                                       fromView:nil];
    
    ax::Point pos(locationInView.x, locationInView.y);
    
        //**************************************************************************
    // Double click.
    if (event.clickCount == 2)
    {
//        _axApp->GetPopupManager()->OnMouseLeftDoubleClick(pos);
//        if(_axApp->GetPopupManager()->IsEventReachWindow() == false)
//        {
//            _axApp->GetWindowManager()->OnMouseLeftDoubleClick(pos);
//        }
        _axApp->GetPopupManager()->OnMouseLeftDoubleClick(pos);
        if(_axApp->GetPopupManager()->IsEventReachWindow() == false)
        {
            _axApp->GetWindowManager()->OnMouseLeftDoubleClick(pos);
        }
    }
    
    // Simple click.
    else
    {
        _axApp->GetPopupManager()->OnMouseLeftDown(pos);
        
        if(_axApp->GetPopupManager()->IsEventReachWindow() == false)
        {
            _axApp->GetWindowManager()->OnMouseLeftDown(pos);
        }
    }
}

- (void) rightMouseDown: (NSEvent*) event
{
    NSPoint locationInView = [self convertPoint:[event locationInWindow]
                                       fromView:nil];
    
    ax::Point pos(locationInView.x, locationInView.y);
    
    // Double click.
    if (event.clickCount == 2)
    {
//        _axApp->GetPopupManager()->OnMouseRightDoubleClick(pos);
//        if(_axApp->GetPopupManager()->IsEventReachWindow() == false)
//        {
//            _axApp->GetWindowManager()->OnMouseRightDoubleClick(pos);
//        }
    }
    
    // Simple click.
    else
    {
            //**************************************************************************
        _axApp->GetPopupManager()->OnMouseRightDown(pos);
        
        if(_axApp->GetPopupManager()->IsEventReachWindow() == false)
        {
            _axApp->GetWindowManager()->OnMouseRightDown(pos);
        }
    }
}

// Working.
- (void)mouseUp:(NSEvent *)anEvent
{
    NSPoint locationInView = [self convertPoint:[anEvent locationInWindow]
                                       fromView:nil];

        //**************************************************************************
    ax::Point pos(locationInView.x, locationInView.y);
    _axApp->GetPopupManager()->OnMouseLeftUp(pos);

    // TODO :: Fix this.
    _axApp->GetWindowManager()->OnMouseLeftUp(pos);

}

// Working.
- (void)mouseDragged:(NSEvent *)theEvent
{
    NSPoint locationInView = [self convertPoint:[theEvent locationInWindow]
                                       fromView:nil];
    
        //**************************************************************************
    ax::Point pos(locationInView.x, locationInView.y);
    _axApp->GetPopupManager()->OnMouseLeftDragging(pos);
    
    if(_axApp->GetPopupManager()->IsEventReachWindow() == false)
    {
        _axApp->GetWindowManager()->OnMouseLeftDragging(pos);
    }
}

// Working.
- (void)mouseMoved:(NSEvent *) evt
{
//    axDebug("mouseMoved:(NSEvent *)MyMouseMouse");
//    axPrint("mouseMoved:(NSEvent *)MyMouseMouse");
    
    NSPoint locationInView =
            [self convertPoint:[evt locationInWindow] fromView:nil];

    ax::Point pos(locationInView.x, locationInView.y);
    _axApp->GetPopupManager()->OnMouseMotion(pos);
    
    if(_axApp->GetPopupManager()->IsEventReachWindow() == false)
    {
        _axApp->GetWindowManager()->OnMouseMotion(pos);
    }
}

// Working.
- (void)mouseEntered:(NSEvent *)theEvent
{
//    NSLog(@"Mouse enter");
}

- (void)mouseExited:(NSEvent *)theEvent
{
//    NSLog(@"Mouse leave");
}

-(BOOL) canBecomeKeyWindow
{
    return true;
}

- (void) flagsChanged: (NSEvent *)evt
{
    unsigned int key = [evt keyCode];
    
    ax::Print(key);
}

- (void)keyDown: (NSEvent *) event
{
    unsigned short key = [event keyCode];

        //**************************************************************************//
    // BackSpace.
    if(key == 51)
    {
        _axApp->GetWindowManager()->OnBackSpaceDown();
        _axApp->GetPopupManager()->OnBackSpaceDown();
    }
    // Delete
    else if(key == 117)
    {
        _axApp->GetWindowManager()->OnKeyDeleteDown();
        _axApp->GetPopupManager()->OnKeyDeleteDown();
    }
    // Enter.
    else if(key == 36)
    {
        _axApp->GetWindowManager()->OnEnterDown();
        _axApp->GetPopupManager()->OnEnterDown();
    }
    // Left arrow.
    else if(key == 123)
    {
        _axApp->GetWindowManager()->OnLeftArrowDown();
        _axApp->GetPopupManager()->OnLeftArrowDown();
    }
    // Right arrow.
    else if(key == 124)
    {
        _axApp->GetWindowManager()->OnRightArrowDown();
        _axApp->GetPopupManager()->OnRightArrowDown();
    }
    else
    {
        std::string str = [[event characters] UTF8String];
        _axApp->GetWindowManager()->OnKeyDown(str[0]);
        _axApp->GetPopupManager()->OnKeyDown(str[0]);
    }
}


//static int test_value = 0;
void MyRunLoopObserver(CFRunLoopObserverRef observer,
                       CFRunLoopActivity activity,
                       void* info)
{
        //**************************************************************************
    ax::App::GetMainApp()->GetEventManager()->CallNext();
//    axEventManager::GetInstance()->CallNext();
}

-(void) installRunLoopObserver
{
    // Run loop observer.
    CFRunLoopObserverRef myObserver = NULL;
    int myActivities = kCFRunLoopAllActivities; //kCFRunLoopBeforeWaiting;
    
    // Create observer reference.
    myObserver = CFRunLoopObserverCreate(NULL,
                                         myActivities,
                                         YES, 0,
                                         &MyRunLoopObserver,
                                         NULL);

    if(myObserver)
    {
        CFRunLoopAddObserver(CFRunLoopGetCurrent(),
                             myObserver,
                             kCFRunLoopCommonModes);
    }
}

// Timer callback method
- (void)timerFired:(id)sender
{

}

// Set origin at top left position.
- (BOOL)isFlipped
{
    return YES;
}

- (void) itemChanged:(NSMenuItem *)anObject
{
    std::cout << "Menu item" << std::endl;
}

// Each time window has to be redrawn, this method is called
- (void)drawRect:(NSRect)bounds
{
    std::cout << "DrawRect" << std::endl;
    //int frame_height = bounds.size.height;

    NSRect backingBounds = [self convertRectToBacking:[self bounds]];
    
        //**************************************************************************
//    axCore* core = _axApp->GetCore();
    
//    ax::Size global_size = core->GetGlobalSize();
    ax::Size global_size = _axApp->GetFrameSize();
    
    if(global_size.x != backingBounds.size.width ||
       global_size.y != backingBounds.size.height)
    {
        _axApp->SetFrameSize(ax::Size(backingBounds.size.width,
                                      backingBounds.size.height));
        
//        core->ResizeGLScene(ax::Size(backingBounds.size.width,
//                                   backingBounds.size.height));
//        core->ResizeGLScene(backingBounds.size.width,
//                            backingBounds.size.height,
//                            frame_height - backingBounds.size.height);
    }

//    if ([self inLiveResize])
//    {
//        // Draw a quick approximation
//        std::cout << "Live resize drawing." << std::endl;
//    }
//    else
    {
        // Is only gonna draw if necessary.
//        core->DrawGLScene();
        _axApp->Draw();
        glFlush();
    }

}

@end