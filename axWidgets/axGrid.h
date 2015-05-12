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
#ifndef __AX_GRID__
#define __AX_GRID__

/// @defgroup Widgets
/// @{

/// @defgroup Grid
/// @{

#include <axEvent/axEvent.h>
#include "axPanel.h"
#include "axColor.h"
#include "axGC.h"
#include "axImage.h"

#include <fstream>

typedef ax::Utils::Point2D<int> axArrayIndex;
//typedef axTemplate2DPoint<int> axArrayIndex;

class axGrid;

class axGridMsg
{
public:
	axGridMsg()
	{
		_sender = nullptr;
	}

    axGridMsg(axGridMsg* sender, const std::string& msg)
	{
		_sender = sender;
		_msg = msg;
	}

	axGridMsg* GetSender() const
	{
		return _sender;
	}

    std::string GetMsg() const
	{
		return _msg;
	}

private:
	axGridMsg* _sender;
    std::string _msg;
};

struct axGridEvents
{
	std::function<void (axGridMsg)> move_element;
	std::function<void (axGridMsg)> new_element;
	
	axGridEvents(){}
	axGridEvents(std::function<void (axGridMsg)>& move, 
				   std::function<void (axGridMsg)>& new_elem)
	{ 
		move_element = move;
		new_elem = new_elem;
	}
};

struct axGridInfo
{
	axColor normal;
	axColor hover;
	axColor clicking;
	axColor selected;
	axColor contour;
	axColor font_color;

	axGridInfo(){}
	axGridInfo(
		const axColor& normal_color,
		const axColor& hover_color,
		const axColor& clicked_color,
		const axColor& selected_color,
		const axColor& contour_color,
		const axColor& font_color_) :
		normal(normal_color),
		hover(hover_color),
		clicking(clicked_color),
		selected(selected_color),
		contour(contour_color),
		font_color(font_color_){}

	axGridInfo(const std::string& info_path)
	{
        std::ifstream file;
		file.open(info_path);

		if (file.fail())
		{
			std::cerr << "Problem opening file " << info_path << std::endl;
		}
		else
		{
			std::string line;

			axColor* ptr = &normal;
			while (file.good())
			{
				getline(file, line);
				*ptr++ = axColor(line);
			}
		}
	}
};

class axGrid : public axPanel
{
public:
	axGrid(axWindow* parent,
		const ax::Rect& rect,
		const axGridEvents& events,
		const axGridInfo& info,
		ax::Size grid_dimension,
		//string label = "",
		axFlag flags = 0,
		std::string msg = "");

	void SetBackgroundAlpha(const float& alpha);
	void SetElementColor(const axColor& color);
	void SetMsg(const std::string& msg);
	void SetSelected(const bool& selected);

private:
	axGridEvents _events;
	axGridInfo _info;
	//string _label;
	std::string _msg;
	
	axFlag _flags;
	ax::Size _dimension;

	int _nCurrentImg;

	int nGridElement;

	struct axGridElement
	{
		bool on;
		ax::Point position;
		axColor color;
	};

	axColor _currentElementColor;
	std::vector<std::vector<axGridElement>> _gridElements;
	
	void AddElement(const int& row, const int& col);
	axArrayIndex GetElementIndexFromMouse(const ax::Point& pos);
	ax::Point GetPositionOfElement(const axArrayIndex& index);

	axArrayIndex _selectedElement;

	virtual void OnPaint();
	//virtual void OnMouseMotion(){}
	virtual void OnMouseLeftDown(const ax::Point& pos);
	virtual void OnMouseLeftUp(const ax::Point& pos);
	// virtual void OnMouseRightDown();
	virtual void OnMouseEnter();
	virtual void OnMouseLeave();
};

/// @}
/// @}
#endif //__AX_GRID__

