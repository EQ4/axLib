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
#include "axPopupMenu.h"
#include <axGL/axGC.h>

axPopupMenu::axPopupMenu(axWindow* parent,
                         const ax::Rect& rect,
                         const axPopupMenuEvents& events,
                         const axPopupMenuInfo& info,
                         const std::vector<std::string>& labels,
                         std::string bgImg,
                         ax::Flag flag) :
// Heritage.
axPanel(3, nullptr, rect),
// members.
_events(events),
_info(info),
_flag(flag),
_index(-1),
_labels(labels),
_lastSelected(nullptr)
{
    ax::Size tog_size(rect.size.x, LABEL_HEIGHT);

    axToggle::Events tog_event;
//    tog_event.button_click = GetOnButtonClick();
    
    axToggle::Info tog_info;
    tog_info.normal = ax::Color(0.8, 0.8, 0.8, 0.6);
    tog_info.hover = ax::Color(0.9, 0.9, 0.9, 0.6);
    tog_info.clicking = ax::Color(0.7, 0.7, 0.7, 0.6);
    
    tog_info.selected = ax::Color(0.8, 0.4, 0.4, 0.6);
    tog_info.selected_hover = ax::Color(0.9, 0.4, 0.4, 0.6);
    tog_info.selected_clicking = ax::Color(0.7, 0.4, 0.4, 0.6);
    
    tog_info.contour = ax::Color(0.0, 0.0, 0.0, 0.0);
    tog_info.font_color = ax::Color(0.0, 0.0, 0.0, 1.0);
    
	for (int i = 0; i < _labels.size(); i++)
	{
		_btns.push_back(new_ axToggle(this,
						ax::Rect(ax::Point(0, i * LABEL_HEIGHT), tog_size),
						tog_event, tog_info, bgImg, _labels[i],
                                     axToggle::Flags::CANT_UNSELECT_WITH_MOUSE,
                        _labels[i]));
	}

	SetSize(ax::Size(tog_size.x, (int)_btns.size() * LABEL_HEIGHT));
    SetShownRect(GetRect());
    
    if(_events.selection_change)
    {
        AddConnection(axPopupMenuEvents::SELECTION_CHANGE,
                      _events.selection_change);
    }
}

void axPopupMenu::SetSelectedIndex(const int& index)
{
    if(index >= 0 && index < _btns.size())
    {
        _btns[index]->SetSelected(true);
        
        if (_lastSelected == nullptr)
        {
            _lastSelected = _btns[index];
        }
        else if (_btns[index] != _lastSelected)
        {
            _lastSelected->SetSelected(false);
            _lastSelected = _btns[index];
        }
    }
    else
    {
        std::cerr << "ERROR : axPopupMenu : INDEX OUT OF RANGE" << std::endl;
    }

}

void axPopupMenu::OnButtonClick(const axToggle::Msg& msg)
{
	if (_lastSelected == nullptr)
    {
		_lastSelected = msg.GetSender();
    }
	else if (msg.GetSender() != _lastSelected)
	{
		_lastSelected->SetSelected(false);
		_lastSelected = msg.GetSender();
	}
    
    PushEvent(axPopupMenuEvents::SELECTION_CHANGE,
              new_ axPopupMenuMsg(msg.GetMsg()));
    
//    if(_events.selection_change)
//    {
//        _events.selection_change(axPopupMenuMsg(msg.GetMsg()));
//    }
}



void axPopupMenu::OnMouseMotion(const ax::Point& pos)
{
	/*if (!IsGrabbed())
	{
		GrabMouse();
	}*/

	//if ()

	/*for (unsigned int i = 0; i < _labels.size(); ++i)
	{
		ax::Rect rect(0, i * LABEL_HEIGHT, GetSize().x, LABEL_HEIGHT);
		ax::Rect r(rect + GetAbsoluteRect().position);

		if (r.IsPointInside(pos))
		{
			if (_index != i)
			{
				_index = i;
				Update();
			}
			break;
		}
	}*/
}

void axPopupMenu::OnMouseLeftUp(const ax::Point& pos)
{
	//UnGrabMouse();
	////m_parent->TriggerEvent(m_eventID.valueChange);
	//if (_events.selection_change)
	//{
	//	_events.selection_change(axPopupMenuMsg(_labels[_index]));
	//}
}

void axPopupMenu::OnPaint()
{
	//Resize(ax::Size(GetSize().x, m_labels.size() * LABEL_HEIGHT));

	///axGC gc(GetBackBuffer());
    ax::GC gcs = ax::GC();
    ax::GC* gc = &gcs;
	//ax::Size size = GetSize();
	ax::Rect rect0(ax::Point(0, 0), GetRect().size);

	gc->SetColor(_info.bgColorNormal);
	gc->DrawRectangle(rect0);

	gc->SetColor(_info.contourColor);
	gc->DrawRectangleContour(rect0);

	//ax::Size label_size(size.x, LABEL_HEIGHT);
	//for (unsigned int i = 0, pos_y = 0; i < _labels.size(); ++i, pos_y += LABEL_HEIGHT)
	//{
	//	if (i == _index)
	//	{
	//		gc->SetColor(_info.bgColorSelected);
	//		ax::Rect selected_rect(ax::Point(2, pos_y + 2), label_size - ax::Size(4, 4));

	//		gc->DrawRectangle(selected_rect);

	//		gc->SetColor(_info.fontColor);
	//		gc->DrawStringAlignedCenter(_labels[i], selected_rect);
	//	}

	//	else
	//	{
	//		gc->SetColor(_info.bgColorNormal);
	//		ax::Rect selected_rect(ax::Point(2, pos_y + 2), label_size - ax::Size(4, 4));

	//		gc->DrawRectangle(selected_rect);

	//		gc->SetColor(_info.fontColor);
	//		gc->DrawStringAlignedCenter(_labels[i], 
	//			ax::Rect(ax::Point(0, pos_y), label_size));

	///*		gc.DrawTextAligned(m_labels[i], axTEXT_CENTER,
	//			m_info.bgColorNormal.GetColorRGB(),
	//			"8",
	//			ax::Rect(ax::Point(0, pos_y), label_size));*/
	//	}
	//}

	////FlipScreen(gc);
}
