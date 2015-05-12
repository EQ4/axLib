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
#include "axGrid.h"

axGrid::axGrid(axWindow* parent,
               const ax::Rect& rect,
               const axGridEvents& events,
               const axGridInfo& info,
               ax::Size grid_dimension,
               //string label,
               axFlag flags,
               string msg) :
// Heritage.
axPanel(parent, rect),
// Members.
_events(events),
_info(info),
//_label(label),
_flags(flags),
_msg(msg),
_dimension(grid_dimension),
nGridElement(0),
_currentElementColor(0.0, 0.8, 0.0)
{
	_gridElements.resize(_dimension.y);

	for(int j = 0; j < _dimension.y; j++)
	{
		_gridElements[j].resize(_dimension.x);
	}

	// _gridElements[4][3].on = true;
	// _gridElements[4][3].color = axColor(0.0, 0.4, 0.0);
	// _gridElements[4][3].position = ax::Point((double(4) / _dimension.x) * rect.size.x,
	// 									   (double(3) / _dimension.y) * rect.size.y);

	_selectedElement(0, 0);
}

void axGrid::SetMsg(const string& msg)
{
	//_msg = msg;
}

void axGrid::SetSelected(const bool& selected)
{
	// if (_selected != selected)
	// {
	// 	_selected = selected;

	// 	if (_selected == true)
	// 	{
	// 		if (_currentColor == &_info.normal)
	// 		{
	// 			_currentColor = &_info.selected;
	// 			Update();
	// 		}
	// 	}
	// 	else
	// 	{
	// 		if (_currentColor == &_info.selected)
	// 		{
	// 			_currentColor = &_info.normal;
	// 			Update();
	// 		}
	// 	}
	// }
}

void axGrid::SetBackgroundAlpha(const float& alpha)
{
	// _bgAlpha = alpha;
	// Update();
}

void axGrid::SetElementColor(const axColor& color)
{
	_currentElementColor = color;
}

void axGrid::AddElement(const int& row, const int& col)
{
	ax::Rect rect(GetRect());
	_gridElements[row][col].on = true;
	_gridElements[row][col].color = _currentElementColor;
	_gridElements[row][col].position = ax::Point(floor(double(col) / _dimension.x * rect.size.x),
										   (double(row) / _dimension.y) * rect.size.y);
}
 
 ax::Point axGrid::GetPositionOfElement(const axArrayIndex& index)
 {
 	ax::Rect rect = GetRect();
 	return ax::Point((double(index.x) / _dimension.x) * rect.size.x,
										   (double(index.y) / _dimension.y) * rect.size.y);
 }

 ax::Point axGrid::GetElementIndexFromMouse(const ax::Point& pos)
 {
 	ax::Rect rect = GetRect();
 	return ax::Size(floor(((double)pos.x / rect.size.x)  * _dimension.x),
 				  floor(((double)pos.y / rect.size.y)  * _dimension.y));
 }

void axGrid::OnMouseLeftDown(const ax::Point& pos)
{
	cout << "LEFT_DOWN" << endl;
	ax::Rect rect = GetAbsoluteRect();
	ax::Point position = pos - rect.position;
	axArrayIndex index = GetElementIndexFromMouse(position);

	cout << index.x << " " << index.y << endl;
	

	if(_gridElements[index.y][index.x].on == false)
	{
		AddElement(index.y, index.x);
	}
	_selectedElement = index;

	Update();
}

// void axGrid::OnMouseRightDown()
// {
	
// }

void axGrid::OnMouseLeftUp(const ax::Point& pos)
{
}

void axGrid::OnMouseEnter()
{
}

void axGrid::OnMouseLeave()
{
}

void axGrid::OnPaint()
{
	axGC* gc = GetGC();
	ax::Rect rect(GetRect());
	ax::Rect rect0(ax::Point(0, 0), rect.size);

	gc->SetColor(_info.normal, 1.0);
	gc->DrawRectangle(rect0);

	gc->SetColor(_info.contour, 1.0);

	int y = 0;
	glLineWidth(1.0);
	for(int j = 0; j <= _dimension.y; j++)
	{
		int y = (double(j) / _dimension.y) * rect.size.y;
		gc->DrawLine(ax::Point(0, y), ax::Point(rect.size.x, y));
	}

	int x = 0;
	for(int i = 0; i <= _dimension.x; i++)
	{
		int x = (double(i) / _dimension.x) * rect.size.x;
		gc->DrawLine(ax::Point(x, 0), ax::Point(x, rect.size.y));
	}

	ax::Size element_size(1.0 / _dimension.x * rect.size.x - 1, 
						1.0 / _dimension.y * rect.size.y - 1);
	for(int j = 0;j < _dimension.y; j++)
	{
		for(int i = 0; i < _dimension.x; i++)
		{
			if(_gridElements[j][i].on)
			{
				gc->SetColor(_gridElements[j][i].color);

				ax::Size elem_size(floor((double(i+1)/ _dimension.x * rect.size.x)) - 
								 floor((double(i) / _dimension.x * rect.size.x)) - 1,
								1.0 / _dimension.y * rect.size.y - 1);
				gc->DrawRectangle(ax::Rect(_gridElements[j][i].position, elem_size));
			}
		}
	}



	//_selectedElement
	gc->SetColor(axColor(0.0, 0.0, 1.0));
	//glLineWidth(4.0);
	gc->DrawRectangleContour(ax::Rect(GetPositionOfElement(_selectedElement), element_size), 2);

	// glLineWidth(1.0);

	// gc->DrawCircle(ax::Point(50, 50), 10, 500);

}


