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
#ifndef __AX_CPP__
#define __AX_CPP__

/// @defgroup Utils
/// @{

#ifdef __linux__
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <GL/glx.h>
#include <GL/gl.h>
#include <GL/glu.h>
//#endif //__linux__

#elif _MSC_VER
#include <windows.h>
#include "GL/glew.h"
//#include <gl\gl.h>
#include <gl\glu.h>

#pragma warning( disable : 4018 )
#pragma warning( disable : 4244 )
#pragma warning( disable : 4305 )

//#endif //_MSC_VER

#else //__APPLE__
    #include <OpenGL/OpenGL.h>
    #include <OpenGL/glu.h>
#endif // __APPLE__

#include <stdint.h>
#include <memory>
#include <functional>
#include <iostream>
//#include "axUtils.h"
#include <axUtils/axUtils.h>

#define axDEBUG_LEVEL0 0
#define axDEBUG_MINIMAL_LEVEL 1
#define axDEBUG_MEDIUM_LEVEL 2
#define axDEBUG_HIGH_LEVEL 3

#define axDEBUG_LEVEL (axDEBUG_MINIMAL_LEVEL)

#if axDEBUG_LEVEL > 0
#define axREMOVE_ON_RELEASE(x) x
#else
#define axREMOVE_ON_RELEASE(x) 
#endif

#if axDEBUG_LEVEL > 0 && !defined(new) && defined(_MSC_VER)
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>

// Placement new does not allocate, so we simply return the pointer without
// using the crtdbg version.
inline void * __CRTDECL operator new(size_t size,
                                     int blockType,
                                     const char* fileName,
                                     int lineNumber,
                                     void* placement)
{
    (size);
    (blockType);
    (fileName);
    (lineNumber);
    return placement;
}

#define newp(...) new(_NORMAL_BLOCK, __FILE__, __LINE__, __VA_ARGS__)
#define new_ new(_NORMAL_BLOCK, __FILE__, __LINE__)
#else
#define newp new
#define new_ new
#endif

//#define DSTREAM cout
#define DSTREAM(x) if(x <= axDEBUG_LEVEL) cout 

// If altenative.
#define if_error_in if
#define if_no_error_in if 
#define if_not_empty(str) if((str) != "")
#define if_not_null(ptr) if((ptr) != nullptr)
#define if_not_zero(var) if((var) != 0)

// While alternative.
#define while_not_null(ptr) while((ptr) != nullptr)

#define axOUTPUT_VARIABLE(v) std::cout << #v << " : " << v << std::endl;

// Standard type.
typedef float axFloat;
typedef double axDouble;
typedef int axInt;
typedef unsigned int axUint;
typedef long axLong;
typedef unsigned long axUlong;
typedef unsigned char axByte;

/// @}
#endif //__AX_CPP__


