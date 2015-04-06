
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

#include <OpenGL/OpenGL.h>
#include <OpenGL/glu.h>
#include "axCocoaInterfaceMac.h"

#include <iostream>
#include "axLib.h"

axApp* GlobalApp = nullptr;
axAppDelegate* GlobalAppDelegate = nullptr;

@implementation axAppDelegate

- (id)initWithFrame:(NSRect)frame
{
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
    [self addTrackingRect:[self bounds] owner:self userData:NULL assumeInside:YES];
    [[self window] makeFirstResponder:self];
    
    GlobalAppDelegate = self;
}

- (void)prepareOpenGL
{
    // Synchronize buffer swaps with vertical refresh rate
    GLint swapInt = 1;
    [[self window] setAcceptsMouseMovedEvents:YES];
    [[self openGLContext] setValues:&swapInt forParameter:NSOpenGLCPSwapInterval];
    
#ifdef _AX_VST_APP_
    axApp* app = axApp::CreateApp();

    axVstCoreMac* vstCoreMac = static_cast<axVstCoreMac*>(app->GetCore());
    axVstCoreData* coreData = vstCoreMac->GetVstCoreData();
    
    if(coreData->appDelegate == nullptr)
    {
        coreData->appDelegate = (__bridge void*)GlobalAppDelegate;
    }

    axMain::MainEntryPoint(app);

    axAppDelegate* d = (__bridge axAppDelegate*)coreData->appDelegate;
    [d setNeedsDisplay:YES];
    
#else
    //axEventManager::GetInstance();
    axApp* app = axApp::GetInstance();
    
    app->GetCore()->Init(axSize(500, 500));
    
    app->CallMainEntryFunction();
    app->CallAfterGUILoadFunction();
    app->CreateEditor();

    
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

- (void)windowDidResize:(NSEvent *)event
{
//    std::cout << "Resize. " << std::endl;
}

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
    
    axPoint pos(locationInView.x, locationInView.y);
    
    // Double click.
    if (event.clickCount == 2)
    {
        axApp::GetInstance()->GetPopupManager()->OnMouseLeftDoubleClick(pos);
        if(axApp::GetInstance()->GetPopupManager()->IsEventReachWindow() == false)
        {
            axApp::GetInstance()->GetWindowManager()->OnMouseLeftDoubleClick(pos);
        }
    }
    
    // Simple click.
    else
    {
        axApp::GetInstance()->GetPopupManager()->OnMouseLeftDown(pos);
        
        if(axApp::GetInstance()->GetPopupManager()->IsEventReachWindow() == false)
        {
            axApp::GetInstance()->GetWindowManager()->OnMouseLeftDown(pos);
        }
    }
}

- (void) rightMouseDown: (NSEvent*) event
{
    NSPoint locationInView = [self convertPoint:[event locationInWindow]
                                       fromView:nil];
    
    axPoint pos(locationInView.x, locationInView.y);
    
    // Double click.
    if (event.clickCount == 2)
    {
//        axApp::MainInstance->GetPopupManager()->OnMouseRightDoubleClick(pos);
//        if(axApp::MainInstance->GetPopupManager()->IsEventReachWindow() == false)
//        {
//            axApp::MainInstance->GetWindowManager()->OnMouseRightDoubleClick(pos);
//        }
    }
    
    // Simple click.
    else
    {
        axApp::GetInstance()->GetPopupManager()->OnMouseRightDown(pos);
        
        if(axApp::GetInstance()->GetPopupManager()->IsEventReachWindow() == false)
        {
            axApp::GetInstance()->GetWindowManager()->OnMouseRightDown(pos);
        }
    }
}

// Working.
- (void)mouseUp:(NSEvent *)anEvent
{
    NSPoint locationInView = [self convertPoint:[anEvent locationInWindow]
                                       fromView:nil];

    axPoint pos(locationInView.x, locationInView.y);
    axApp::GetInstance()->GetPopupManager()->OnMouseLeftUp(pos);

    // TODO :: Fix this.
    axApp::GetInstance()->GetWindowManager()->OnMouseLeftUp(pos);

}

// Working.
- (void)mouseDragged:(NSEvent *)theEvent
{
    NSPoint locationInView = [self convertPoint:[theEvent locationInWindow]
                                       fromView:nil];
    
    axPoint pos(locationInView.x, locationInView.y);
    axApp::GetInstance()->GetPopupManager()->OnMouseLeftDragging(pos);
    
    if(axApp::GetInstance()->GetPopupManager()->IsEventReachWindow() == false)
    {
        axApp::GetInstance()->GetWindowManager()->OnMouseLeftDragging(pos);
    }
}

// Working.
- (void)mouseMoved:(NSEvent *)MyMouseMouse
{
    NSPoint locationInView = [self convertPoint:[MyMouseMouse locationInWindow]
                                       fromView:nil];

//    NSPoint kkk = [MyMouseMouse locationInWindow];
//    axPoint pos(kkk.x, kkk.y);

    axPoint pos(locationInView.x, locationInView.y);
    
    axApp::GetInstance()->GetPopupManager()->OnMouseMotion(pos);
    if(axApp::GetInstance()->GetPopupManager()->IsEventReachWindow() == false)
    {
        axApp::GetInstance()->GetWindowManager()->OnMouseMotion(pos);
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
    
    axPrint(key);
}

- (void)keyDown: (NSEvent *) event
{
    unsigned short key = [event keyCode];

    axPrint("key : ", key);

    // BackSpace.
    if(key == 51)
    {
        axApp::GetInstance()->GetWindowManager()->OnBackSpaceDown();
        axApp::GetInstance()->GetPopupManager()->OnBackSpaceDown();
    }
    // Delete
    else if(key == 117)
    {
        axApp::GetInstance()->GetWindowManager()->OnKeyDeleteDown();
        axApp::GetInstance()->GetPopupManager()->OnKeyDeleteDown();
    }
    // Enter.
    else if(key == 36)
    {
        axApp::GetInstance()->GetWindowManager()->OnEnterDown();
        axApp::GetInstance()->GetPopupManager()->OnEnterDown();
    }
    // Left arrow.
    else if(key == 123)
    {
        axApp::GetInstance()->GetWindowManager()->OnLeftArrowDown();
        axApp::GetInstance()->GetPopupManager()->OnLeftArrowDown();
    }
    // Right arrow.
    else if(key == 124)
    {
        axApp::GetInstance()->GetWindowManager()->OnRightArrowDown();
        axApp::GetInstance()->GetPopupManager()->OnRightArrowDown();
    }
    else
    {
        std::string str = [[event characters] UTF8String];
        axApp::GetInstance()->GetWindowManager()->OnKeyDown(str[0]);
        axApp::GetInstance()->GetPopupManager()->OnKeyDown(str[0]);
    }
}


static int test_value = 0;
void MyRunLoopObserver(CFRunLoopObserverRef observer,
                       CFRunLoopActivity activity,
                       void* info)
{
    axEventManager::GetInstance()->CallNext();
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
    int frame_height = bounds.size.height;

    NSRect backingBounds = [self convertRectToBacking:[self bounds]];
    
    axCore* core = axApp::GetInstance()->GetCore();
    
    axSize global_size = core->GetGlobalSize();
    if(global_size.x != backingBounds.size.width ||
       global_size.y != backingBounds.size.height)
    {
        core->ResizeGLScene(axSize(backingBounds.size.width,
                                   backingBounds.size.height));
//        core->ResizeGLScene(backingBounds.size.width,
//                            backingBounds.size.height,
//                            frame_height - backingBounds.size.height);
    }

    if ([self inLiveResize])
    {
        // Draw a quick approximation
//        std::cout << "Live resize drawing." << std::endl;
    }
    else
    {
        // Is only gonna draw if necessary.
        core->DrawGLScene();
        glFlush();
    }

}

@end