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
#ifndef __AX_GC__
#define __AX_GC__

/// @defgroup Graphic
/// @{

#include <axUtils/axUtils.h>
#include <axGL/axImage.h>
//#include "ax::Color.h"
#include <axGL/axFont.h>
//#include "axDrawingBuffer.h"

class axWindow;

class axGC
{
public:
	axGC(axWindow* win);

	void SetColor(const ax::Color& color);
    
    void SetColor(const ax::Color& color, const float& alpha);

	void SetColor(const double& r,
                  const double& g,
                  const double& b);
    
    void SetColor(const double& r,
                  const double& g,
                  const double& b,
                  const double& a);

	void DrawRectangle(const ax::Rect& rect);

	void DrawRectangleContour(const ax::Rect& rect, float linewidth = 1.0);

    void DrawRoundedRectangle(const ax::Rect& rect,
                              const int& radius);
    
    void DrawRoundedRectangleContour(const ax::Rect& rect,
                                     const int& radius);
    
    void DrawRoundedRectangleContourSmooth(const ax::Rect& rect,
                                           const int& radius);
    
	void DrawImage(ax::Image* img, const ax::Point& pos, double alpha = 1.0);
    
	void DrawImageResize(ax::Image* img,
                         const ax::Point& position,
                         const ax::Size& size,
                         double alpha = 1.0);

	void DrawPartOfImage(ax::Image* img,
                         const ax::Point& posInImage,
                         const ax::Size& sizeInImage,
                         const ax::Point& pos,
                         double alpha = 1.0);
    
    void DrawPartOfImageResize(ax::Image* img,
                               const ax::Point& posInImage,
                               const ax::Size& sizeInImage,
                               const ax::Rect& rect,
                               double alpha = 1.0);

    ax::Point DrawChar(ax::Font& font,
                     const char& key,
                     const ax::Point& pos);
    
	void DrawString(ax::Font& font,
                    const std::string& text,
                    const ax::Point& pos);

	void DrawStringAlignedCenter(ax::Font& font,
                                 const std::string& text,
                                 const ax::Rect& rect);

	void DrawRectangleColorFade(const ax::Rect& rect,
                                const ax::Color& c1,
                                const float& alpha1,
                                const ax::Color& c2,
                                const float& alpha2);
    
    void DrawRectangleColorFade(const ax::Rect& rect,
                                const ax::Color& c1,
                                const ax::Color& c2);
    
    void DrawPolygone(const std::vector<ax::Point>& points);
    
    void DrawArrow(const ax::Point& p1,
                   const ax::Point& p2,
                   const double& arrow_length = 12,
                   const double& base_length = 8,
                   const double& width = 1);
    
    void DrawTriangleColorFade(const ax::Point& p1,
                          const ax::Point& p2,
                          const ax::Point& p3,
                          const ax::Color& c1,
                          const ax::Color& c2,
                          const ax::Color& c3);

    
	void DrawLine(const ax::Point& pt1, const ax::Point& pt2, float width = 1.0);
    
    void DrawLineColorfade(const ax::Point& pt1, const ax::Point& pt2,
                           const ax::Color& c1, const ax::Color& c2,
                           float width = 1.0);
    
    void DrawSmouthLine(const ax::Point& pt1, const ax::Point& pt2, float width = 2.0);
    void DrawLines(const std::vector<ax::Point>& pts, float width = 1.0);
    
    void DrawPoint(const ax::Point& pt, const int& size);
    
    /// @todo This function is not finish. (Add some param)
    void DrawLineCubic(const ax::Point& pt1, const ax::Point& pt2);

    void SetLineWidth(const double& width);
    
    void SetSmoothLine(const int& width);
    void SetDefaultLine();
    
	void DrawCircle(const ax::Point& pos,
                    const double& radius,
                    const int& nSegments);
	
	void DrawTexture(uint32_t texture,
                     const ax::Rect& rect,
                     ax::Color color = ax::Color(0.0, 0.0, 0.0));
    
//	void DrawBigImageResize(axBigImage* img,
//		const ax::Point& position,
//		const ax::Size& size,
//		double alpha = 1.0);

//    void DrawWindowBuffer();
    
    // Just blocking x axis for now.
    void BlockDrawing(const ax::Rect& rect);
    void UnBlockDrawing();
    
    //void DrawBuffer(axDrawingBuffer* buffer);

private:
	axWindow* _win;
//	ax::Font _font;
    
    ax::FloatRect RectToFloatRect(const ax::Rect& rect);
};

/// @}
#endif //__AX_GC__

