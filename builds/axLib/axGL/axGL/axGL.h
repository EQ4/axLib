//
//  axGL.h
//  axGL
//
//  Created by Alexandre Arsenault on 2015-05-13.
//  Copyright (c) 2015 Alexandre Arsenault. All rights reserved.
//

//#import <Cocoa/Cocoa.h>

////! Project version number for axGL.
//FOUNDATION_EXPORT double axGLVersionNumber;
//
////! Project version string for axGL.
//FOUNDATION_EXPORT const unsigned char axGLVersionString[];

// In this header, you should import all the public headers of your framework using statements like #import <axGL/PublicHeader.h>

#ifdef __linux__
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <GL/glx.h>
#include <GL/gl.h>
#include <GL/glu.h>

#elif _MSC_VER
#include <windows.h>
#include "GL/glew.h"
//#include <gl\gl.h>
#include <gl\glu.h>

#else //__APPLE__
#include <OpenGL/OpenGL.h>
#include <OpenGL/glu.h>
#endif // __APPLE__
