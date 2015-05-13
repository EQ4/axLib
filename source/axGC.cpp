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
#include "axGC.h"
#include "axWindow.h"
//#include "axMath.h"
#include <axGL/axGLMath.h>

#include "axApp.h"
#include "axCore.h"

#include <cmath>

axGC::axGC(axWindow* win)//:
//_font("tt")
{
    _win = win;
}

ax::FloatRect axGC::RectToFloatRect(const ax::Rect& rect)
{
    return ax::FloatRect(axFloat(rect.position.x), axFloat(rect.position.y),
					     axFloat(rect.size.x), axFloat(rect.size.y));
}

void axGC::SetColor(const axDouble& r, const axDouble& g, const axDouble& b)
{
	glColor4d(r, b, g, 1.0);
}

void axGC::SetColor(const axDouble& r,
                    const axDouble& g,
                    const axDouble& b,
                    const axDouble& a)
{
    glColor4d(r, g, b, a);
}

void axGC::SetColor(const ax::Color& color)
{
	glColor4d(color.GetRed(),
              color.GetGreen(),
              color.GetBlue(),
              color.GetAlpha());
}

void axGC::SetColor(const ax::Color& color, const float& alpha)
{
	glColor4d(color.GetRed(), color.GetGreen(), color.GetBlue(), alpha);
}

void axGC::DrawRectangle(const ax::Rect& rect)
{
//    axMatrix4 mview_before(GL_MODELVIEW_MATRIX);
//    axMatrix4 mview;
    
//    mview.Identity().Translate(_win->GetAbsoluteRect().position).Process();
    
    ax::FloatRect frect = RectToFloatRect(rect);
    ax::Utils::RectPoints<ax::FloatPoint> points = frect.GetPoints(); // Order : bl, tl, tr, br.
    
    // For scroll bar.
    //	frect.position.x  -= floor(_win->GetScrollDecay().x);
    //	frect.position.y  -= _win->GetScrollDecay().y;

	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(2, GL_DOUBLE, 0, &points);
	glDrawArrays(GL_QUADS, 0, 4);
	glDisableClientState(GL_VERTEX_ARRAY);
    
//    mview_before.Load();
}

void DrawQuarterCircleContour(const ax::FloatPoint& pos,
                              const int& radius,
                              const double& angle,
                              const int& nSegments)
{
    glBegin(GL_LINES);
    for(int i = 1; i < nSegments; i++)
    {
        // Get the current angle.
        double theta = (2.0f * M_PI) * 0.25 * (double(i - 1)) / double(nSegments);
        
        double x = radius * cosf(theta + angle);
        double y = radius * sinf(theta + angle);
        
        glVertex2d(x + pos.x, y + pos.y);
        
        theta = (2.0f * M_PI) * 0.25 * (double(i)) / double(nSegments);
        
        x = radius * cosf(theta + angle);
        y = radius * sinf(theta + angle);
        glVertex2d(x + pos.x, y + pos.y);
    }
    glEnd();
}

void axGC::DrawRoundedRectangleContour(const ax::Rect& rect, const int& radius)
{

    int r = radius;
    
    if(r > rect.size.y * 0.5)
    {
        r = rect.size.y * 0.5;
    }
    
    int nSegments = 10;
    ax::FloatRect frect = RectToFloatRect(rect);

    glBegin(GL_LINES);
    
    // Top line.
    glVertex2d(frect.position.x + r - 2,
               frect.position.y);
    
    glVertex2d(frect.position.x + frect.size.x - r + 2,
               frect.position.y);
    
    // Bottom line.
    glVertex2d(frect.position.x + r - 2,
               frect.position.y + frect.size.y);
    
    glVertex2d(frect.position.x + frect.size.x - r + 2,
               frect.position.y + frect.size.y);
    
    // Left line.
    glVertex2d(frect.position.x,
               frect.position.y + r - 2);
    
    glVertex2d(frect.position.x,
               frect.position.y + frect.size.y - r + 2);
    
    // Right line.
    glVertex2d(frect.position.x + + frect.size.x,
               frect.position.y + r - 2);
    
    glVertex2d(frect.position.x + + frect.size.x,
               frect.position.y + frect.size.y - r + 2);
    glEnd();
    


    
    // Bottom right.
    DrawQuarterCircleContour(ax::FloatPoint(frect.position.x + frect.size.x - r,
                                          frect.position.y + frect.size.y - r),
                             r, 0, nSegments);
    
    // Top left.
    DrawQuarterCircleContour(ax::FloatPoint(frect.position.x + r - 1 ,
                                          frect.position.y + r - 1),
                             r, M_PI, nSegments);
    
    // Top right.
    DrawQuarterCircleContour(ax::FloatPoint(frect.position.x + frect.size.x - r,
                                          frect.position.y + r - 1),
                             r, 3.0 * M_PI * 0.5, nSegments);
    
    // Bottom left.
    DrawQuarterCircleContour(ax::FloatPoint(frect.position.x + r - 1,
                                          frect.position.y + frect.size.y - r),
                             r, M_PI * 0.5, nSegments);
}

void DrawQuarterCircleContourSmooth(axGC* gc, const ax::FloatPoint& pos,
                              const int& radius,
                              const double& angle,
                              const int& nSegments)
{
//    glBegin(GL_LINES);
    for(int i = 1; i < nSegments; i++)
    {
        // Get the current angle.
        double theta = (2.0f * M_PI) * 0.25 * (double(i - 1)) / double(nSegments);
        
        double x = radius * cosf(theta + angle);
        double y = radius * sinf(theta + angle);
        
//        glVertex2d(x + pos.x, y + pos.y);
        
        ax::Point pt1(x + pos.x, y + pos.y);
        theta = (2.0f * M_PI) * 0.25 * (double(i)) / double(nSegments);
        
        x = radius * cosf(theta + angle);
        y = radius * sinf(theta + angle);
        
        ax::Point pt2(x + pos.x, y + pos.y);
//        glVertex2d(x + pos.x, y + pos.y);
        
        gc->DrawSmouthLine(pt1, pt2, 3);
    }
//    glEnd();
}

void axGC::DrawRoundedRectangleContourSmooth(const ax::Rect& rect,
                                             const int& radius)
{
    
    int r = radius;
    
    if(r > rect.size.y * 0.5)
    {
        r = rect.size.y * 0.5;
    }
    
    int nSegments = 5;
    ax::FloatRect frect = RectToFloatRect(rect);
    
    glLineWidth(2.0f);
    glEnable(GL_LINE_SMOOTH);
//    glEnable(GL_POLYGON_SMOOTH);
    glHint(GL_LINE_SMOOTH_HINT, GL_FASTEST);
//    glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
    
    glBegin(GL_LINES);
    
    // Top line.
    DrawSmouthLine(ax::Point(frect.position.x + r - 2,
                           frect.position.y),
                   ax::Point(frect.position.x + frect.size.x - r + 2,
                           frect.position.y));
    
    // Bottom line.
    DrawSmouthLine(ax::Point(frect.position.x + r - 2,
                           frect.position.y + frect.size.y),
                   ax::Point(frect.position.x + frect.size.x - r + 2,
                           frect.position.y + frect.size.y));
    
//    DrawSmouthLine();
//    DrawSmouthLine();
    // Top line.
//    glVertex2d(frect.position.x + r - 2,
//               frect.position.y);
//    
//    glVertex2d(frect.position.x + frect.size.x - r + 2,
//               frect.position.y);
//    
//    // Bottom line.
//    glVertex2d(frect.position.x + r - 2,
//               frect.position.y + frect.size.y);
//    
//    glVertex2d(frect.position.x + frect.size.x - r + 2,
//               frect.position.y + frect.size.y);
//    
//    // Left line.
//    glVertex2d(frect.position.x,
//               frect.position.y + r - 2);
//    
//    glVertex2d(frect.position.x,
//               frect.position.y + frect.size.y - r + 2);
//    
//    // Right line.
//    glVertex2d(frect.position.x + + frect.size.x,
//               frect.position.y + r - 2);
//    
//    glVertex2d(frect.position.x + + frect.size.x,
//               frect.position.y + frect.size.y - r + 2);
//    glEnd();
    
    // Bottom right.
    DrawQuarterCircleContourSmooth(this, ax::FloatPoint(frect.position.x + frect.size.x - r,
                                          frect.position.y + frect.size.y - r),
                             r, 0, nSegments);
    
    // Top left.
    DrawQuarterCircleContourSmooth(this, ax::FloatPoint(frect.position.x + r,
                                          frect.position.y + r),
                             r, M_PI, nSegments);
    
    // Top right.
    DrawQuarterCircleContourSmooth(this, ax::FloatPoint(frect.position.x + frect.size.x - r,
                                          frect.position.y + r),
                             r, 3.0 * M_PI * 0.5, nSegments);
    
    // Bottom left.
    DrawQuarterCircleContourSmooth(this, ax::FloatPoint(frect.position.x + r,
                                          frect.position.y + frect.size.y - r),
                             r, M_PI * 0.5, nSegments);
    
    glDisable(GL_LINE_SMOOTH);
    glLineWidth(1.0f);
//    glDisable(GL_POLYGON_SMOOTH);
    
}

void DrawQuarterCircle(const ax::FloatPoint& pos,
                       const int& radius,
                       const double& angle,
                       const int& nSegments)
{
    glBegin(GL_TRIANGLE_FAN);
    
    glVertex2d(pos.x, pos.y);
    
    for(int i = 0; i < nSegments; i++)
    {
        // Get the current angle.
        double theta = (2.0f * M_PI) * 0.25 * (double(i)) / double(nSegments);
        
        double x = radius * cosf(theta + angle);
        double y = radius * sinf(theta + angle);
        
        glVertex2d(x + pos.x, y + pos.y);
    }
    glEnd();
}

void axGC::DrawRoundedRectangle(const ax::Rect& rect, const int& radius)
{
    int r = radius;
    
    if(r > rect.size.y * 0.5)
    {
        r = rect.size.y * 0.5;
    }
    
    int nSegments = 40;
    ax::FloatRect frect = RectToFloatRect(rect);
    
    // Middle.
    DrawRectangle(ax::Rect(frect.position.x + r - 1,
                         frect.position.y - 1,
                         frect.size.x - 2.0 * r + 1,
                         frect.size.y + 1));

    int size_rect_height = frect.size.y - 2.0 * r + 1;
    
    if(size_rect_height > 0)
    {
        // Left.
        DrawRectangle(ax::Rect(frect.position.x - 1,
                             frect.position.y + r - 1,
                             r,
                             size_rect_height));
        
        // Right.
        DrawRectangle(ax::Rect(frect.position.x +frect.size.x - r,
                             frect.position.y + r - 1,
                             r + 1,
                             size_rect_height));
    }

    // Bottom right.
    DrawQuarterCircle(ax::FloatPoint(frect.position.x + frect.size.x - r,
                                   frect.position.y + frect.size.y - r),
                      r, 0, nSegments);

    
    // Top left.
    DrawQuarterCircle(ax::FloatPoint(frect.position.x + r - 1 ,
                                   frect.position.y + r - 1),
                      r, M_PI, nSegments);
    
    // Top right.
    DrawQuarterCircle(ax::FloatPoint(frect.position.x + frect.size.x - r,
                                   frect.position.y + r - 1),
                      r, 3.0 * M_PI * 0.5, nSegments);
    
    // Bottom left.
    DrawQuarterCircle(ax::FloatPoint(frect.position.x + r - 1,
                                   frect.position.y + frect.size.y - r),
                      r, M_PI * 0.5, nSegments);
    
}

void axGC::DrawRectangleContour(const ax::Rect& rect, float linewidth)
{
//    axMatrix4 mview_before(GL_MODELVIEW_MATRIX);
//    axMatrix4 mview;
//    mview.Identity().Translate(_win->GetAbsoluteRect().position).Process();
    
	ax::FloatRect frect = RectToFloatRect(rect);
//	frect.position.x  -= floor(_win->GetScrollDecay().x);
//	frect.position.y  -= _win->GetScrollDecay().y;
    
	// Note that OpenGL coordinate space has no notion of integers, 
	// everything is a float and the "centre" of an OpenGL pixel is 
	// really at the 0.5,0.5 instead of its top-left corner. 
	// Therefore, if you want a 1px wide line from 0,0 to 10,10 inclusive, 
	// you really had to draw a line from 0.5,0.5 to 10.5,10.5. 
	frect.position.x -= 0.5; // Seems to be only on linux and mac.

	glLineWidth((GLfloat)linewidth);
    
    ax::Utils::RectPoints<ax::FloatPoint> points = frect.GetPoints(); // Order : bl, tl, tr, br.
    GLubyte indices[] = {1,2, 2,3, 3,0, 0,1};
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(2, GL_DOUBLE, 0, &points); // The value of z defaults is 0.
    glDrawElements(GL_LINE_LOOP, 8, GL_UNSIGNED_BYTE, indices);
    glDisableClientState(GL_VERTEX_ARRAY);

//    mview_before.Load();
    
    glLineWidth(1.0f);
}

void axGC::DrawTexture(GLuint texture, const ax::Rect& rect, ax::Color color)
{
//	ax::Point pos = rect.position + _win->GetAbsoluteRect().position;
    ax::Point pos = rect.position;
//	pos.x  -= _win->GetScrollDecay().x;
//	pos.y  -= _win->GetScrollDecay().y;

	//ax::ColorStruct c = color.GetColorStruct();
	//glColor4f(c.r, c.g, c.b, 1.0);

	glEnable(GL_TEXTURE_2D);
//	glEnable(GL_BLEND);
//    glEnable(GL_DEPTH_TEST);
    
    
//	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


	glBindTexture(GL_TEXTURE_2D, texture);

//	axREMOVE_ON_RELEASE
//	(
//		GLenum err = glGetError();
//
//		if (err != GL_NO_ERROR)
//		{
//			DSTREAM(3) << "GL TEXTURE ERROR : " << " " <<
//				gluErrorString(err) << endl;
//		}
//	)
//    glColor4d(1.0, 1.0, 1.0, 1.0);
	glDepthMask(GL_TRUE);
	ax::Size img_size = rect.size;

	glBegin(GL_QUADS);
	
	// Bottom left.
	glTexCoord2d(0.0, 0.0);
	glVertex2d(pos.x, pos.y);

	// Top left.
	glTexCoord2d(0.0, 1.0);
	glVertex2d(pos.x, pos.y + img_size.y);

	// Top right.
	glTexCoord2d(1.0, 1.0);
	glVertex2d(pos.x + img_size.x, pos.y + img_size.y);

	// Buttom right.
	glTexCoord2d(1.0, 0.0);
	glVertex2d(pos.x + img_size.x, pos.y);

	glEnd();

//	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);
//    glBlendFunc(GL_ONE, GL_ZERO);
//    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

struct axRectPointsOrder
{
    axRectPointsOrder(){}
    axRectPointsOrder(const ax::Utils::RectPoints<ax::FloatPoint>& points):
    top_left(points.top_left),
    top_right(points.top_right),
    bottom_left(points.bottom_left),
    bottom_right(points.bottom_right)
    {
    }
    axRectPointsOrder(const ax::FloatPoint& tl,
                      const ax::FloatPoint& tr,
                      const ax::FloatPoint& bl,
                      const ax::FloatPoint& br):
    top_left(tl), top_right(tr), bottom_left(bl),bottom_right(br)
    {
        
    }
    
    ax::FloatPoint top_left, top_right, bottom_left, bottom_right;
};

void axGC::DrawImage(axImage* img, const ax::Point& position, double alpha)
{
//	ax::Point pos = position + _win->GetAbsoluteRect().position;
    ax::Point pos = position;
	//pos -= _win->GetScrollDecay();

	glColor4f(1.0, 1.0, 1.0, alpha);

	glEnable(GL_TEXTURE_2D);
//	glEnable(GL_BLEND);
//	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glBindTexture(GL_TEXTURE_2D, img->GetTexture());
//	glDepthMask(GL_TRUE);
	ax::Size img_size = img->GetSize();

	// OpenGL stores texture upside down so glTexCoord2d must be flipped.
	glBegin(GL_QUADS);
	// Buttom left.
	glTexCoord2d(0.0, 1.0);
	glVertex2d(pos.x, pos.y);

	// Top left.
	glTexCoord2d(0.0, 0.0);
	glVertex2d(pos.x, pos.y + img_size.y);

	// Top right.
	glTexCoord2d(1.0, 0.0);
	glVertex2d(pos.x + img_size.x, pos.y + img_size.y);

	// Buttom right.
	glTexCoord2d(1.0, 1.0);
	glVertex2d(pos.x + img_size.x, pos.y);
	glEnd();
//	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);
}

void axGC::DrawImageResize(axImage* img, const ax::Point& position, const ax::Size& size, double alpha)
{
//	ax::Point pos = position + _win->GetAbsoluteRect().position;
    ax::Point pos = position;
	//pos -= _win->GetScrollDecay();

	glColor4f(1.0, 1.0, 1.0, alpha);

	glEnable(GL_TEXTURE_2D);
//	glEnable(GL_BLEND);
//	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glBindTexture(GL_TEXTURE_2D, img->GetTexture());
//	glDepthMask(GL_TRUE);
	ax::Size img_size = size;

	// OpenGL stores texture upside down so glTexCoord2d must be flipped.
	glBegin(GL_QUADS);
	// Buttom left.
	glTexCoord2d(0.0, 1.0);
	glVertex2d(pos.x, pos.y);

	// Top left.
	glTexCoord2d(0.0, 0.0);
	glVertex2d(pos.x, pos.y + img_size.y);

	// Top right.
	glTexCoord2d(1.0, 0.0);
	glVertex2d(pos.x + img_size.x, pos.y + img_size.y);

	// Buttom right.
	glTexCoord2d(1.0, 1.0);
	glVertex2d(pos.x + img_size.x, pos.y);
	glEnd();

//	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);
}

void axGC::DrawPartOfImage(axImage* img,
                           const ax::Point& posInImage,
                           const ax::Size& sizeInImage,
                           const ax::Point& position,
                           double alpha)
{
    //	ax::Point pos = position + _win->GetAbsoluteRect().position;
    
    ax::Point pos = position;
    //pos -= _win->GetScrollDecay();
    
    ax::Size img_size = img->GetSize();
    
    double img_x = (posInImage.x + sizeInImage.x) / double(img_size.x),
    img_y = 1.0 - (posInImage.y + sizeInImage.y) / double(img_size.y);
    
    double x = posInImage.x / double(img_size.x);
    double y = 1.0 - posInImage.y / double(img_size.y);
    
    glColor4f(1.0, 1.0, 1.0, alpha);
    
    glEnable(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, img->GetTexture());
//    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//    glBlendFunc(GL_DST_ALPHA, GL_ONE_MINUS_DST_ALPHA);
//    glDepthMask(GL_TRUE);
    
    // OpenGL stores texture upside down so glTexCoord2d must be flipped.
    glBegin(GL_QUADS);
    
    // Buttom left.
    glTexCoord2d(x, y);
    glVertex2d(pos.x, pos.y);
    
    // Top left.
    glTexCoord2d(x, img_y);
    glVertex2d(pos.x, pos.y + sizeInImage.y-1);
    
    // Top right.
    glTexCoord2d(img_x, img_y);
    glVertex2d(pos.x + sizeInImage.x-1, pos.y + sizeInImage.y-1);
    
    // Buttom right.
    glTexCoord2d(img_x, y);
    glVertex2d(pos.x + sizeInImage.x-1, pos.y);
    glEnd();
    //	glDisable(GL_BLEND);
    glDisable(GL_TEXTURE_2D);
//    glBlendFunc(GL_ONE, GL_ZERO);
}


void axGC::DrawPartOfImageResize(axImage* img,
					 const ax::Point& posInImage,
					 const ax::Size& sizeInImage,
					 const ax::Rect& rect,
                     double alpha)
{
    ax::Point pos = rect.position;
	ax::Size img_size = img->GetSize();

	double img_x = (posInImage.x + sizeInImage.x) / double(img_size.x),
		img_y = 1.0 - (posInImage.y + sizeInImage.y) / double(img_size.y);

	double x = posInImage.x / double(img_size.x);
	double y = 1.0 - posInImage.y / double(img_size.y);

	glColor4f(1.0, 1.0, 1.0, alpha);

	glEnable(GL_TEXTURE_2D);
//	glEnable(GL_BLEND);
//	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glBindTexture(GL_TEXTURE_2D, img->GetTexture());
//	glDepthMask(GL_TRUE);
	
	// OpenGL stores texture upside down so glTexCoord2d must be flipped.
	glBegin(GL_QUADS);
	
	// Buttom left.
	glTexCoord2d(x, y);
	glVertex2d(pos.x, pos.y);

	// Top left.
	glTexCoord2d(x, img_y);
	glVertex2d(pos.x, pos.y + rect.size.y);

	// Top right.
	glTexCoord2d(img_x, img_y);
	glVertex2d(pos.x + rect.size.x, pos.y + rect.size.y);

	// Buttom right.
	glTexCoord2d(img_x, y);
	glVertex2d(pos.x + rect.size.x, pos.y);
	glEnd();
//	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);
}

void axGC::DrawString(axFont& font,
                      const std::string& text,
                      const ax::Point& pos)
{
    if(font)
    {
        int x = pos.x;
        
        for (int i = 0; i < text.size(); i++)
        {
            font.SetChar(text[i]);
            ax::Point delta = font.GetDelta();
            
            DrawTexture(font.GetTexture(),
                        ax::Rect(ax::Point(x + delta.x, pos.y - delta.y + font.GetFontSize()),
                               font.GetSize()));
            
            x += font.GetNextPosition();
        }
    }

}

ax::Point axGC::DrawChar(axFont& font,
                       const char& key,
                       const ax::Point& pos)
{
    if(font)
    {
        int x = pos.x;
        
        font.SetChar(key);
        ax::Point delta = font.GetDelta();
        
        DrawTexture(font.GetTexture(),
                    ax::Rect(ax::Point(x + delta.x, pos.y - delta.y + font.GetFontSize()),
                           font.GetSize()));
        
        x += font.GetNextPosition();
        
        return ax::Point(x, pos.y);
    }

    return ax::Point(0, 0);
}


// Just blocking x axis for now.
void axGC::BlockDrawing(const ax::Rect& rect)
{
    ax::GL::Math::Matrix4 before_proj(GL_MODELVIEW);
    ax::GL::Math::Matrix4 proj;
    proj.Identity().Load();
    
//    ax::Rect r = rect;
    
    ax::Point abso(_win->GetAbsoluteRect().position);
    
    glScissor(abso.x + rect.position.x,
              _win->GetApp()->GetCore()->GetGlobalSize().y -
              (abso.y + rect.position.y + rect.size.y),
              rect.size.x,
              rect.size.y);
    
    glEnable(GL_SCISSOR_TEST);
    before_proj.Load();
}

void axGC::UnBlockDrawing()
{
    glDisable(GL_SCISSOR_TEST);
}

void axGC::DrawStringAlignedCenter(axFont& font,
                                   const std::string& text,
								   //const ax::Point& pos,
								   const ax::Rect& rect)
{
    if(font)
    {
        int length = 0;
        int height = 0;
        for (int i = 0; i < text.size(); i++)
        {
            font.SetChar(text[i]);
            length += font.GetNextPosition();
            
            if (font.GetSize().y > height)
                height = font.GetSize().y;
        }
        
        ax::Point pos(rect.position.x + (rect.size.x - length) * 0.5,
                    rect.position.y + ceil((rect.size.y - height) * 0.5));
        
        int x = pos.x;
        for (int i = 0; i < text.size(); i++)
        {
            font.SetChar(text[i]);
            ax::Point delta = font.GetDelta();
            
            DrawTexture(font.GetTexture(),
                        ax::Rect(ax::Point(x + delta.x, pos.y - delta.y + height),
                               font.GetSize()));
            
            x += font.GetNextPosition();
        }
    }
}

void axGC::DrawRectangleColorFade(const ax::Rect& rectangle,
								  const ax::Color& c1, const float& alpha1,
								  const ax::Color& c2, const float& alpha2)
{
//	ax::FloatRect rect = RectToFloatRect(rectangle + _win->GetAbsoluteRect().position);
    ax::FloatRect rect = RectToFloatRect(rectangle);
	//rect.position.x  -= _win->GetScrollDecay().x;
	//rect.position.y  -= _win->GetScrollDecay().y;

	glBegin(GL_QUADS);
	SetColor(c1, alpha1);
	glVertex3f(rect.position.x, rect.position.y, 0); // Bottom left.

	//SetColor(c1);
	glVertex3f(rect.position.x + rect.size.x,
		rect.position.y, 0); // Bottom Right.

	SetColor(c2, alpha2);
	glVertex3f(rect.position.x + rect.size.x,
		rect.position.y + rect.size.y, 0); // Top Right.

	//SetColor(c2);
	glVertex3f(rect.position.x,
		rect.position.y + rect.size.y, 0); // Top Left
	glEnd();
}

void axGC::DrawRectangleColorFade(const ax::Rect& rectangle,
                                  const ax::Color& c1,
                                  const ax::Color& c2)
{
//    ax::FloatRect rect = RectToFloatRect(rectangle + _win->GetAbsoluteRect().position);
    ax::FloatRect rect = RectToFloatRect(rectangle);
    
    glBegin(GL_QUADS);
    SetColor(c1);
    glVertex3f(rect.position.x, rect.position.y, 0); // Bottom left.
    
    glVertex3f(rect.position.x + rect.size.x,
               rect.position.y, 0); // Bottom Right.
    
    SetColor(c2);
    glVertex3f(rect.position.x + rect.size.x,
               rect.position.y + rect.size.y, 0); // Top Right.
    
    glVertex3f(rect.position.x,
               rect.position.y + rect.size.y, 0); // Top Left
    glEnd();
}

void axGC::DrawLines(const std::vector<ax::Point>& pts, float width)
{
//	ax::Point real_pos = _win->GetAbsoluteRect().position;
//    ax::Point real_pos = _win->GetRect().position;
//	real_pos.x -= _win->GetScrollDecay().x;
//	real_pos.y -= _win->GetScrollDecay().y;
//
//    glPushMatrix();
//    glTranslated(real_pos.x, real_pos.y, 0.0);

	glLineWidth(width);

    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(2, GL_INT, 0, pts.data());
    glDrawArrays(GL_LINES, 0, int(pts.size()));
    glDisableClientState(GL_VERTEX_ARRAY);
    
    glPopMatrix();
}


void axGC::DrawSmouthLine(const ax::Point& pt1, const ax::Point& pt2, float width)
{
//    glEnable(GL_LINE_SMOOTH);
//    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
//    
//    glBegin(GL_LINES);
//    glVertex2f(pt1.x, pt1.y);
//    glVertex2f(pt2.x, pt2.y);
//    glEnd();
//    
//    glDisable(GL_LINE_SMOOTH);
//    float width = 3;
    
    double dx = pt2.x - pt1.x;
    double dy = pt2.y - pt1.y;
    double m = dx == 0.0 ? 999999.9 : dy / dx;
    
    m = abs(m);
    
    if(m > 1.0)
    {
        m = abs(dy/dx);
    }
    
    double wx = 0.0;
    double wy = 0.0;//0.5 - m;
    
    if(m <= 0.5)
    {
        wx = ax::Utils::Clamp<double>(0.5 + m, 0.0, 1.0);
    }
    else
    {
        wy = ax::Utils::Clamp<double>(0.5 + m, 0.0, 1.0);

    }
    
    
//    ax::Print("M : ", m);
//    std::cout << "M : " << m <<
    
    	glEnable(GL_POLYGON_SMOOTH);
    //	glEnable(GL_BLEND);
    //	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    //	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    	glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
    
    glBegin(GL_TRIANGLE_STRIP);
    glColor3f(1, 1, 1);
    glVertex3f(pt1.x, pt1.y, 0);
    glVertex3f(pt2.x, pt2.y, 0);
    
    glColor3f(1, 0, 0);
    glVertex3f(pt1.x + wx, pt1.y + wy, 0);
    glVertex3f(pt2.x + wx, pt2.y + wy, 0);
    
    glColor3f(1, 1, 1);
    glVertex3f(pt1.x + 2.0 * wx, pt1.y + wy * 2.0, 0);
    glVertex3f(pt2.x + 2.0 * wx, pt2.y + wy * 2.0, 0);
    glEnd();
    
    glDisable(GL_POLYGON_SMOOTH);
}

void axGC::DrawLine(const ax::Point& pt1, const ax::Point& pt2, float width)
{

    
//	ax::Point real_pos = _win->GetAbsoluteRect().position;
//    ax::Point real_pos = _win->GetRect().position;
//	real_pos.x  -= _win->GetScrollDecay().x;
//	real_pos.y  -= _win->GetScrollDecay().y;

    ax::Point p1 = pt1;// - _win->GetScrollDecay().x;;// + real_pos;
    ax::Point p2 = pt2;// - _win->GetScrollDecay().y;// + real_pos;

//	glEnable(GL_LINE_SMOOTH);
//	glEnable(GL_POLYGON_SMOOTH);
//	glEnable(GL_BLEND);
//	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
//	glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);

	glLineWidth(width);

	glBegin(GL_LINES);
	glVertex2f(p1.x, p1.y);
	glVertex2f(p2.x, p2.y);
	glEnd();
    
//    glDisable(GL_LINE_SMOOTH);
}

void axGC::DrawLineColorfade(const ax::Point& pt1, const ax::Point& pt2,
                             const ax::Color& c1, const ax::Color& c2,
                             float width)
{
    ax::Point p1 = pt1;
    ax::Point p2 = pt2;

    glLineWidth(width);
    
    glBegin(GL_LINES);
    SetColor(c1);
    glVertex2f(p1.x, p1.y);
    SetColor(c2);
    glVertex2f(p2.x, p2.y);
    glEnd();
}

void axGC::DrawPoint(const ax::Point& pt, const int& size)
{
    glEnable(GL_POINT_SMOOTH);
    glPointSize(size);
    glBegin(GL_POINTS);
    glVertex2f(pt.x, pt.y);
    glEnd();
    glDisable(GL_POINT_SMOOTH);
}

void axGC::DrawLineCubic(const ax::Point& pt1, const ax::Point& pt2)
{
    // H1(t) = 2t^3 - 3t^2 + 1
    // H2(t) = -2t^3 + 3t^2
    // H3(t) = t^3 - 2t^2 + t
    // H4(t) = t^3 - t^2
    // V1 = Tengente at point 1.
    // V2 = Tengente at point 2.
    // P(t) = [H1(t) H2(t) H3(t) H4(t)] * [P1 P2 V1 V2];
    // P(t) = H1(t) * P1.x + H2(t) * P2.x + H3(t) *
    
//    double t = 0.0;
    
    double v1x = 100.0, v1y = 200;
    double v2x = 100.0, v2y = -200;
    
    double pp_x = pt1.x, pp_y = pt1.y;
    
    glBegin(GL_LINES);
    for(int i = 1; i < 101; i++)
    {
        double t = i / double(101.0);
        
        double h1 = 2.0 * pow(t, 3.0) - 3.0 * pow(t, 2.0) + 1.0;
        double h2 = -2.0 * pow(t, 3.0) + 3.0 * pow(t, 2.0);
        double h3 = pow(t, 3.0) - 2.0 * pow(t, 2.0) + t;
        double h4 = pow(t, 3.0) - pow(t, 2.0);
        
        double p_x = h1 * pt1.x + h2 * pt2.x + h3 * v1x + h4 * v2x;
        double p_y = h1 * pt1.y + h2 * pt2.y + h3 * v1y + h4 * v2y;
        
        glVertex2f(pp_x, pp_y);
        glVertex2f(p_x, p_y);
        
        pp_x = p_x;
        pp_y = p_y;
    }
    glEnd();
    
    
//    glVertex2f(pt1.x, pt1.y);
//    glVertex2f(pt2.x, pt2.y);
    
}

void axGC::SetLineWidth(const double& width)
{
//    glEnable(GL_LINE_SMOOTH);
//    glEnable(GL_POLYGON_SMOOTH);
//    glEnable(GL_BLEND);
//    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
//    glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
    
    glLineWidth(width);

}

void axGC::SetSmoothLine(const int& width)
{
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_POLYGON_SMOOTH);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
    
    glLineWidth(width);
    
}

void axGC::SetDefaultLine()
{
    glDisable(GL_LINE_SMOOTH);
    glDisable(GL_POLYGON_SMOOTH);
    glLineWidth(1.0);
}

void axGC::DrawCircle(const ax::Point& pos,
                      const double& radius,
                      const int& nSegments)
{
    ax::Point real_pos = pos;

	glBegin(GL_LINE_LOOP); 
	for(int i = 0; i < nSegments; i++)
	{
        // Get the current angle.
		double theta = 2.0f * M_PI * double(i) / double(nSegments);

		double x = radius * cosf(theta);
		double y = radius * sinf(theta);

		glVertex2d(x + real_pos.x, y + real_pos.y);
	} 
	glEnd(); 
}


//void axGC::DrawBuffer(axDrawingBuffer* buffer)
//{
//    unsigned char* surf_data = buffer->GetData();
//    GLuint texture_id = buffer->GetTexture();
//    ax::Size size(buffer->GetSize());
//    
//    if (!surf_data)
//    {
//        printf ("draw_func() - No valid pointer to surface-data passed\n");
//        return;
//    }
//    
////    glMatrixMode(GL_MODELVIEW);
////    glLoadIdentity ();
////    glClear(GL_COLOR_BUFFER_BIT);
//    
//    
//    //glPushMatrix();
//    axPrint("Cairo draw.");
//    glEnable(GL_TEXTURE_2D);
//    glEnable(GL_TEXTURE_RECTANGLE_ARB);
//    glBindTexture(GL_TEXTURE_RECTANGLE_ARB, texture_id);
//    glTexImage2D (GL_TEXTURE_RECTANGLE_ARB,
//                  0,
//                  GL_RGBA,
//                  size.x,
//                  size.y,
//                  0,
//                  GL_BGRA,
//                  GL_UNSIGNED_BYTE,
//                  surf_data);
//    
//    glColor3f (1.0f, 0.0f, 1.0f);
//    glBegin (GL_QUADS);
//    
//    glTexCoord2f (0.0f, 0.0f);
//    glVertex2f (0.0f, 0.0f);
//    
//    glTexCoord2f ((GLfloat) size.x, 0.0f);
//    glVertex2f (1.0f, 0.0f);
//    
//    glTexCoord2f ((GLfloat) size.x, (GLfloat) size.y);
//    glVertex2f (1.0f, 1.0f);
//    
//    glTexCoord2f (0.0f, (GLfloat) size.y);
//    glVertex2f (0.0f, 1.0f);
//    
//    glEnd ();
//    
//    glDisable(GL_TEXTURE_RECTANGLE_ARB);
//    glDisable(GL_TEXTURE_2D);
//
//    
////    glPopMatrix();
//  
//}


void axGC::DrawBigImageResize(axBigImage* img,
	const ax::Point& position,
	const ax::Size& size,
	double alpha)
{
	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	axBigImage::ColorType color_type = img->GetColorType();
	//axBigImage::PixelDepth depth = img->GetPixelDepth();
	ax::Size real_img_size(img->GetImageSize());
	void* data = img->GetImageData();

	if (color_type == axBigImage::RGB)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, real_img_size.x, real_img_size.y,
			0, GL_RGB, GL_UNSIGNED_BYTE, data);
	}
	else
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, real_img_size.x, real_img_size.y,
			0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	}
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	GLenum err = glGetError();
	
	if (err != GL_NO_ERROR)
	{
        ax::Error("Can't draw axBigImage in axGC : ", err);
	}

	ax::Point pos = position;

	glColor4f(1.0, 1.0, 1.0, alpha);

	glEnable(GL_TEXTURE_2D);
	//	glEnable(GL_BLEND);
	//	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//glBindTexture(GL_TEXTURE_2D, texture);
	//	glDepthMask(GL_TRUE);
	ax::Size img_size = size;

	// OpenGL stores texture upside down so glTexCoord2d must be flipped.
	glBegin(GL_QUADS);
	// Buttom left.
	glTexCoord2d(0.0, 1.0);
	glVertex2d(pos.x, pos.y);

	// Top left.
	glTexCoord2d(0.0, 0.0);
	glVertex2d(pos.x, pos.y + img_size.y);

	// Top right.
	glTexCoord2d(1.0, 0.0);
	glVertex2d(pos.x + img_size.x, pos.y + img_size.y);

	// Buttom right.
	glTexCoord2d(1.0, 1.0);
	glVertex2d(pos.x + img_size.x, pos.y);
	glEnd();

	//	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);
	glDeleteTextures(1, &texture);
}

void axGC::DrawPolygone(const std::vector<ax::Point>& points)
{
    glBegin(GL_POLYGON);
    
    for(auto& n : points)
    {
        glVertex2d(n.x, n.y);
    }
    
    glEnd();
}

void axGC::DrawArrow(const ax::Point& p1, const ax::Point& p2,
                     const double& arrow_length, const double& base_length,
                     const double& width)
{
    glLineWidth(width);
//    double arrow_length = 12;
//    double base_length = 8;
    
    ax::Point arrow_vec = p2 - p1;
    ax::Point normal_vec = ax::Point(-arrow_vec.y, arrow_vec.x);
    double normal_norm = sqrt(normal_vec.x * normal_vec.x +
                              normal_vec.y * normal_vec.y);
    
    normal_vec.x = (normal_vec.x / normal_norm) * base_length;
    normal_vec.y = (normal_vec.y / normal_norm) * base_length;
    
    
    ax::Point arrow_base = arrow_vec;
    double norm = sqrt(arrow_base.x * arrow_base.x +
                       arrow_base.y * arrow_base.y);
    arrow_base.x = (arrow_base.x / norm) * arrow_length;
    arrow_base.y = (arrow_base.y / norm) * arrow_length;
    arrow_base = p2 - arrow_base;

    
    ax::Point pt_vec1 = arrow_base + normal_vec;
    ax::Point pt_vec2 = arrow_base - normal_vec;
    
    glBegin(GL_LINES);
    glVertex2f(p1.x, p1.y);
    glVertex2f(p2.x, p2.y);
    glEnd();
    
    
    glBegin(GL_POLYGON);
    glVertex2f(pt_vec1.x, pt_vec1.y);
    glVertex2f(pt_vec2.x, pt_vec2.y);
    glVertex2f(p2.x, p2.y);
    glEnd();

    
//    glBegin(GL_LINES);
//    glVertex2f(arrow_base.x, arrow_base.y);
//    glVertex2f(pt_vec1.x, pt_vec1.y);
//    
//    glVertex2f(arrow_base.x, arrow_base.y);
//    glVertex2f(pt_vec2.x, pt_vec2.y);
//    glEnd();
}

void axGC::DrawTriangleColorFade(const ax::Point& p1,
                                 const ax::Point& p2,
                                 const ax::Point& p3,
                                 const ax::Color& c1,
                                 const ax::Color& c2,
                                 const ax::Color& c3)
{
    glBegin(GL_POLYGON);
    
    SetColor(c1);
    glVertex2d(p1.x, p1.y);
    SetColor(c2);
    glVertex2d(p2.x, p2.y);
    SetColor(c3);
    glVertex2d(p3.x, p3.y);
    
    glEnd();
}