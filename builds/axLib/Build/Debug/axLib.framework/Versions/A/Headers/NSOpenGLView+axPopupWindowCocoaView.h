//
//  NSOpenGLView+axPopupWindowCocoaView.h
//  axLib
//
//  Created by Alexandre Arsenault on 2015-05-01.
//  Copyright (c) 2015 Alexandre Arsenault. All rights reserved.
//

#import <Cocoa/Cocoa.h>

@interface axPopupWindowCocoaView : NSOpenGLView

// Windows paint callback.
- (void) drawRect: (NSRect)bounds;

- (id) MemberTestFunc;

@end

extern axPopupWindowCocoaView* global_popup_view;