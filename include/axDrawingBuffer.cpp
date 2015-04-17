////
////  axDrawingBuffer.cpp
////  axLib
////
////  Created by Alexandre Arsenault on 2015-02-20.
////  Copyright (c) 2015 Alexandre Arsenault. All rights reserved.
////
//
//#include "axDrawingBuffer.h"
//
//axDrawingBuffer::axDrawingBuffer(const axSize& size):
//_size(size)
//{
//    // Create cairo-surface/context to act as OpenGL-texture source
//    context = contexteate_cairo_context(size.x, size.y, 4,
//                                        &surface, surf_data);
//    
//    glGenTextures (1, &_texture);
//
//    
////    glGenFramebuffers(1, &_frameBuffer);
////    glBindFramebuffer(GL_FRAMEBUFFER, _frameBuffer);
//    
////    glGenTextures (1, &_texture);
////    glBindTexture (GL_TEXTURE_RECTANGLE_ARB, _texture);
////    glTexImage2D (GL_TEXTURE_RECTANGLE_ARB,
////                  0,
////                  GL_RGBA,
////                  size.x,
////                  size.y,
////                  0,
////                  GL_BGRA,
////                  GL_UNSIGNED_BYTE,
////                  NULL);
////    glTexEnvi (GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
//    
////    // Attach 2D texture to this FBO.
////    glFramebufferTexture2D(GL_FRAMEBUFFER,
////                           GL_COLOR_ATTACHMENT0,
////                           GL_TEXTURE_2D,
////                           _texture,
////                           0);
//    
////    // Does the GPU support current FBO configuration.
////    GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER_EXT);
////    
////    if(status != GL_FRAMEBUFFER_COMPLETE_EXT)
////    {
////        axError("Generating frame buffer : ", status);
////    }
////    
////    
////    glBindFramebuffer(GL_FRAMEBUFFER, _frameBuffer);
////    glBindFramebuffer(GL_FRAMEBUFFER, 0);
//}
//
//cairo_t* axDrawingBuffer::contexteate_cairo_context(int width,
//                                                    int height,
//                                                    int channels,
//                                                    cairo_surface_t** surf,
//                                                    unsigned char*& buffer)
//
//{
//    cairo_t* cr;
//    
//    // create cairo-surface/context to act as OpenGL-texture source
//    buffer = (unsigned char*)calloc(channels * width * height, sizeof (unsigned char));
//    if (!buffer)
//    {
//        printf ("create_cairo_context() - Couldn't allocate buffer\n");
//        return NULL;
//    }
//    
//    *surf = cairo_image_surface_create_for_data(buffer,
//                                                CAIRO_FORMAT_ARGB32,
//                                                width,
//                                                height,
//                                                channels * width);
//    if (cairo_surface_status (*surf) != CAIRO_STATUS_SUCCESS)
//    {
//        free (buffer);
//        printf ("create_cairo_context() - Couldn't create surface\n");
//        return NULL;
//    }
//    
//    cr = cairo_create (*surf);
//    if (cairo_status (cr) != CAIRO_STATUS_SUCCESS)
//    {
//        free (buffer);
//        printf ("create_cairo_context() - Couldn't create context\n");
//        return NULL;
//    }
//    
//    return cr;
//}
//
//
//void axDrawingBuffer::DrawRectangle()
//{
//    double xc = 128.0;
//    double yc = 128.0;
//    double radius = 100.0;
//    double angle1 = 45.0  * (M_PI/180.0);  /* angles are specified */
//    double angle2 = 180.0 * (M_PI/180.0);  /* in radians           */
//    
//    cairo_set_line_width (context, 10.0);
//    cairo_arc_negative (context, xc, yc, radius, angle1, angle2);
//    cairo_stroke (context);
//    
//    /* draw helping lines */
//    cairo_set_source_rgba (context, 1, 0.2, 0.2, 0.6);
//    cairo_set_line_width (context, 6.0);
//    
//    cairo_arc (context, xc, yc, 10.0, 0, 2 * M_PI);
//    cairo_fill (context);
//    
//    cairo_arc (context, xc, yc, radius, angle1, angle1);
//    cairo_line_to (context, xc, yc);
//    cairo_arc (context, xc, yc, radius, angle2, angle2);
//    cairo_line_to (context, xc, yc);
//    cairo_stroke (context);
//    
//    glBindTexture (GL_TEXTURE_RECTANGLE_ARB, _texture);
//    glTexImage2D (GL_TEXTURE_RECTANGLE_ARB,
//                  0,
//                  GL_RGBA,
//                  _size.x,
//                  _size.y,
//                  0,
//                  GL_BGRA,
//                  GL_UNSIGNED_BYTE,
//                  surf_data);
//    glTexEnvi (GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
//    
//    //        cairo_set_line_width (context, 40.96);
//    //        cairo_move_to (context, 76.8, 84.48);
//    //        cairo_rel_line_to (context, 51.2, 51.2);
//    //        cairo_rel_line_to (context, 51.2, 200);
//    //        cairo_set_line_join (context, CAIRO_LINE_JOIN_MITER); /* default */
//    //        cairo_stroke (context);
//    
//    //        cairo_move_to (context, 76.8, 161.28);
//    //        cairo_rel_line_to (context, 51.2, -51.2);
//    //        cairo_rel_line_to (context, 51.2, 51.2);
//    //        cairo_set_line_join (context, CAIRO_LINE_JOIN_BEVEL);
//    //        cairo_stroke (context);
//    //
//    //        cairo_move_to (context, 76.8, 238.08);
//    //        cairo_rel_line_to (context, 51.2, -51.2);
//    //        cairo_rel_line_to (context, 51.2, 51.2);
//    //        cairo_set_line_join (context, CAIRO_LINE_JOIN_ROUND);
//    //        cairo_stroke (context);
//    
//    //        cairo_restore (context);
//}
//
////void axFrameBuffer::DrawOnFrameBuffer(const std::function<void()>& fct,
////                                      const axSize& size)
////{
////#if _axBackBufferWindow_ == 1
////    bool need_to_reactive_clip_test = false;
////    
////    if(glIsEnabled(GL_SCISSOR_TEST))
////    {
////        glDisable(GL_SCISSOR_TEST);
////        need_to_reactive_clip_test = true;
////    }
////    
////    // Save modelView matrix.
////    glMatrixMode(GL_MODELVIEW);
////    axMatrix4 modelView(GL_MODELVIEW_MATRIX);
////    
////    glBindFramebuffer(GL_FRAMEBUFFER, _frameBuffer);
////    glPushAttrib(GL_DEPTH_BUFFER_BIT);
////    glClearColor(0.0, 0.0, 0.0, 0.0);
////    glClearDepth(1.0f);
////    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
////    
////    DrawingOnFrameBufferBlendFunction();
////    
////    glViewport(0, 0, size.x, size.y);
////    
////    glMatrixMode(GL_PROJECTION);
////    
////    // Using axMath for projection flip every upside down.
////    axMatrix4 proj;
////    
////    /// @todo Use axMath for projection.
////    glLoadIdentity();
////    glOrtho(0.0, size.x,
////            0.0, size.y,
////            0.0, 1.0);
////    
////    glMatrixMode(GL_MODELVIEW);
////    axMatrix4 mv_matrix;
////    mv_matrix.Identity().Load();
////    
////    if(fct)
////    {
////        fct();
////    }
////    
////    glBindFramebuffer(GL_FRAMEBUFFER, 0);
////    
////    axSize gSize(axApp::GetInstance()->GetCore()->GetGlobalSize());
////    glViewport(0, 0, gSize.x, gSize.y);
////    axOrtho2D(proj.Identity().GetData(), gSize);
////    
////    glMatrixMode(GL_MODELVIEW);
////    modelView.Load();
////    glPopAttrib();
////    
////    if(need_to_reactive_clip_test)
////    {
////        glEnable(GL_SCISSOR_TEST);
////    }
////#endif //_axBackBufferWindow_
////}
////
////void axFrameBuffer::DrawFrameBuffer(const axSize& shownSize)
////{
////#if _axBackBufferWindow_ == 1
////    glEnable(GL_TEXTURE_2D);
////    
////    DrawingFrameBufferBlendFunction();
////    
////    axFloatPoint pos(0.0, 0.0);
////    axFloatSize size(shownSize.x, shownSize.y);
////    
////    glBindTexture(GL_TEXTURE_2D, _frameBufferTexture);
////    
////    glBegin(GL_QUADS);
////    
////    // Bottom left.
////    glTexCoord2d(0.0, 0.0);
////    glVertex2d(pos.x, pos.y);
////    
////    // Top left.
////    glTexCoord2d(0.0, 1.0);
////    glVertex2d(pos.x, pos.y + size.y);
////    
////    // Top right.
////    glTexCoord2d(1.0, 1.0);
////    glVertex2d(pos.x + size.x, pos.y + size.y);
////    
////    // Buttom right.
////    glTexCoord2d(1.0, 0.0);
////    glVertex2d(pos.x + size.x, pos.y);
////    
////    glEnd();
////    
////    //	glDisable(GL_BLEND);
////    glDisable(GL_TEXTURE_2D);
////    
////#endif //_axBackBufferWindow_
////}
////
////void axFrameBuffer::DrawingOnFrameBufferBlendFunction()
////{
////    // All other blend function doesn't work except this one when drawing
////    // multiple transparent frame buffer.
////    glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA,
////                        GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
////}
////
////void axFrameBuffer::DrawingFrameBufferBlendFunction()
////{
////    // This seem to be the only way to make the alpha and color blend properly.
////    glBlendFuncSeparate(GL_DST_ALPHA, GL_ONE_MINUS_SRC_ALPHA,
////                        GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
////}
