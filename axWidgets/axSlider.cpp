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
#include "axSlider.h"

axSlider::axSlider(axWindow* parent,
	const ax::Rect& rect,
	const axSliderEvents& events,
	const axSliderInfo& info,
	//string img_path,
	//string label,
    ax::Flag flags) :
	// Heritage.
	axPanel(parent, rect),
	// Members.
	_events(events),
	_info(info),
	_currentBgColor(info.bgColorNormal),
	_currentSliderColor(info.sliderColorNormal),
	_btnImg(info.img_path.c_str()),
	_nCurrentImg(axBTN_NORMAL),
	_delta_click(0),
	_sliderValue(0.0),
	_flags(flags),
	_bg_alpha(1.0)
{
	_sliderPosition = 0;
    
    if(_events.slider_value_change)
    {
        AddConnection(axSliderEvents::VALUE_CHANGE,
                      _events.slider_value_change);
    }

    if (ax::IsFlag(axSLIDER_FLAG_VERTICAL, _flags))
	{
		_sliderYPos = (GetSize().x - _info.slider_width) * 0.5;
		_btnYPos = (GetSize().x - _info.btn_size.x) * 0.5;

        if (ax::IsFlag(axSLIDER_FLAG_RIGHT_ALIGN, _flags))
		{
			_sliderPosition = GetSize().y - _info.btn_size.y;
		}
	}
	else
	{
		_sliderYPos = (GetSize().y - _info.slider_width) * 0.5;
		_btnYPos = (GetSize().y - _info.btn_size.y) * 0.5;

		if (ax::IsFlag(axSLIDER_FLAG_RIGHT_ALIGN, _flags))
		{
			_sliderPosition = GetSize().x - _info.btn_size.x;
		}
	}
	//SendPaintEvent();
	Update();
}

void axSlider::SetValue(const double& value)
{
	_sliderValue = value;

    if (ax::IsFlag(axSLIDER_FLAG_VERTICAL, _flags))
	{
        if (ax::IsFlag(axSLIDER_FLAG_RIGHT_ALIGN, _flags))
        {
            _sliderPosition = double(GetSize().y - _info.btn_size.y ) * (_sliderValue);
        }
        else
        {
            _sliderPosition = double(GetSize().y - _info.btn_size.y ) * (1.0 - _sliderValue);
        }
		
	}
	 else
	 {
         _sliderPosition = double(GetSize().x - _info.btn_size.x - 2) * (_sliderValue);
//	 	_sliderValue = (_sliderPosition - 1) /
//	 		double(GetSize().x - _info.btn_size.x - 2);
	 }
	Update();
}

void axSlider::OnMouseLeftDown(const ax::Point& mousePos)
{
	ax::Point pos = mousePos - GetAbsoluteRect().position;

	ax::Rect sliderBtnRect;
    if (ax::IsFlag(axSLIDER_FLAG_VERTICAL, _flags))
	{
		sliderBtnRect = ax::Rect(ax::Point(_btnYPos, _sliderPosition),
			_info.btn_size);
	}
	else
	{
		sliderBtnRect = ax::Rect(ax::Point(_sliderPosition, _btnYPos),
			_info.btn_size);
	}


    if (ax::IsFlag(axSLIDER_FLAG_CLICK_ANYWHERE, _flags))
	{
		_nCurrentImg = axBTN_DOWN;
		_currentSliderColor = _info.sliderColorClicked;
		
        if (ax::IsFlag(axSLIDER_FLAG_VERTICAL, _flags))//IsMouseHoverRect( sliderBtnRect ) && m_nCurrentImg != axBTN_DOWN )
		{
			_delta_click = -_info.btn_size.y * 0.5;
		}
		else
		{
			_delta_click = -_info.btn_size.x * 0.5;
		}

		blockSliderPosition(pos);
		GrabMouse();

//		if (_events.slider_value_change)
//		{
//			_events.slider_value_change(axSliderMsg(_sliderValue));
//		}
        PushEvent(axSliderEvents::VALUE_CHANGE,
                  new_ axSliderMsg(_sliderValue));
		Update();
	}
	// Click on boutton to move.
	else
	{

		std::cout << "ELSE" << std::endl;
		if (sliderBtnRect.IsPointInside(pos) && _nCurrentImg != axBTN_DOWN)
		{
			std::cout << "ELSE IN" << std::endl;
			_nCurrentImg = axBTN_DOWN;
			_currentSliderColor = _info.sliderColorClicked;

            if (ax::IsFlag(axSLIDER_FLAG_VERTICAL, _flags))
			{
				_delta_click = sliderBtnRect.position.y - pos.y;
			}
			else
			{
				_delta_click = sliderBtnRect.position.x - pos.x;
			}

			std::cout << "MOUSE GRAB before" << std::endl;
			GrabMouse();

			std::cout << "MOUSE GRAB" << std::endl;

			// Send value change event.
//			if (_events.slider_value_change)
//			{
//				_events.slider_value_change(axSliderMsg(_sliderValue));
//			}
            PushEvent(axSliderEvents::VALUE_CHANGE,
                      new_ axSliderMsg(_sliderValue));
			Update();
		}
	}
}

void axSlider::OnMouseLeftUp(const ax::Point& p)
{
	
	ax::Point pos = p - GetAbsoluteRect().position;

	if (IsGrabbed())
	{
		UnGrabMouse();
		blockSliderPosition(pos);
		_nCurrentImg = axBTN_NORMAL;
		_currentSliderColor = _info.sliderColorNormal;

		Update();
	}
}

void axSlider::OnMouseLeftDragging(const ax::Point& p)
{
	std::cout << "Drag" << std::endl;
	//DSTREAM << "DRAG" << endl;
	ax::Point pos = p - GetAbsoluteRect().position;

	blockSliderPosition(pos);

//	if (_events.slider_value_change)
//	{
//		_events.slider_value_change(axSliderMsg(_sliderValue));
//	}
    
    PushEvent(axSliderEvents::VALUE_CHANGE,
              new_ axSliderMsg(_sliderValue));
	
	Update();
}

void axSlider::blockSliderPosition(const ax::Point& pos)
{
	//ax::Point pos = p - GetRect().position;

    if (ax::IsFlag(axSLIDER_FLAG_VERTICAL, _flags))
	{
		int pos_y = pos.y + _delta_click;

        pos_y = ax::Utils::Clamp<double>(pos_y, 1, GetSize().y - _info.btn_size.y - 1);
		//axCLIP(pos_y, 1, GetSize().y - _info.btn_size.y - 1);

		_sliderPosition = pos_y;
	}
	else
	{
		int pos_x = pos.x + _delta_click;

//		axCLIP(pos_x, 1, GetSize().x - _info.btn_size.x - 1);
        pos_x = ax::Utils::Clamp<double>(pos_x, 1, GetSize().x - _info.btn_size.x - 1);

		_sliderPosition = pos_x;
	}

	updateSliderValue();
}

void axSlider::updateSliderValue()
{
    if (ax::IsFlag(axSLIDER_FLAG_VERTICAL, _flags))
	{
		_sliderValue = (_sliderPosition - 1) /
			double(GetSize().y - _info.btn_size.y - 2);
	}
	else
	{
		_sliderValue = (_sliderPosition - 1) /
			double(GetSize().x - _info.btn_size.x - 2);
	}
}

void axSlider::OnMouseMotion(const ax::Point& p)
{
	ax::Point pos = p - GetAbsoluteRect().position;

	ax::Rect sliderBtnRect;
    if (ax::IsFlag(axSLIDER_FLAG_VERTICAL, _flags))
	{
		sliderBtnRect = ax::Rect(ax::Point(_btnYPos, _sliderPosition),
			_info.btn_size);
	}
	else
	{
		sliderBtnRect = ax::Rect(ax::Point(_sliderPosition, _btnYPos),
			_info.btn_size);
	}

	if (sliderBtnRect.IsPointInside(pos))
	{
		if (_nCurrentImg != axBTN_HOVER)
		{
			_nCurrentImg = axBTN_HOVER;
			Update();
		}
	}
	else // Mouse is not hover slider button.
	{
		if (_nCurrentImg != axBTN_NORMAL)
		{
			_nCurrentImg = axBTN_NORMAL;
			Update();
		}
	}
}

void axSlider::OnMouseEnter(const ax::Point& p)
{
	// cout << "Enter" << endl;
	ax::Point pos = p - GetAbsoluteRect().position;

    if (ax::IsFlag(axSLIDER_FLAG_LEFT_CLICK_ENTER, _flags))
	{
		//if (GetParent()->LeftIsDown())
		//{
			ax::Rect sliderBtnRect(ax::Point(_sliderPosition, _btnYPos),
				_info.btn_size);

			_nCurrentImg = axBTN_DOWN;
			_currentSliderColor = _info.sliderColorClicked;
            if (ax::IsFlag(axSLIDER_FLAG_VERTICAL, _flags))
			{
				_delta_click = sliderBtnRect.position.y - pos.y;
			}
			else
			{
				_delta_click = sliderBtnRect.position.x - pos.x;
			}
			GrabMouse();
			//SendPaintEvent();
			Update();
		//}
	}
}

void axSlider::OnMouseLeave(const ax::Point& p)
{
	ax::Point pos = p - GetAbsoluteRect().position;

    if (ax::IsFlag(axSLIDER_FLAG_RELEASE_ON_LEAVE, _flags))
	{
		if (IsGrabbed())
		{
			UnGrabMouse();
			blockSliderPosition(pos);
			_nCurrentImg = axBTN_NORMAL;
			_currentSliderColor = _info.sliderColorNormal;
			//SendPaintEvent();
			Update();
		}
	}
}

void axSlider::DrawLineBehindSlider_Vertical(ax::GC* gc, const ax::Rect& rect0)
{
	int half_btn_size = _info.btn_size.y * 0.5;

	ax::Rect slider_rect;
    if (ax::IsFlag(axSLIDER_FLAG_RIGHT_ALIGN, _flags))
	{
		// slider_rect = ax::Rect(_sliderYPos, _sliderPosition + half_btn_size,
		// 					 12,// _info.slider_width,
		// 					 GetSize().y - _sliderPosition - half_btn_size);

		slider_rect = ax::Rect(_sliderYPos, _sliderPosition + half_btn_size,
							 _info.slider_width,
							 GetSize().y - _sliderPosition - half_btn_size);
	}
	else
	{
		slider_rect = ax::Rect(_sliderYPos, 0,
							 _info.slider_width,
							 _sliderPosition + half_btn_size);
	}

	gc->SetColor(_currentSliderColor);
	gc->DrawRectangle(slider_rect);

	gc->SetColor(_info.sliderContourColor);
	// gc->DrawRectangleContour(slider_rect);
}

void axSlider::DrawVerticalSlider(ax::GC* gc, const ax::Rect& rect0)
{
//	ax::Size size(rect0.size);
//	int half_btn_size = _info.btn_size.y * 0.5;

	// if (IsFlag(axSLIDER_FLAG_BACK_SLIDER, _flags))
	// {
	// 	// Back slider.
	// 	ax::Rect back_slider(_sliderYPos, 0, _info.slider_width, size.y);

	// 	gc->SetColor(_info.backSliderColor, 1.0);
	// 	gc->DrawRectangle(back_slider);

	// 	gc->SetColor(_info.backSliderContourColor);
	// 	gc->DrawRectangleContour(back_slider);
	// }

	// Draw line behind the slider.
    if (!ax::IsFlag(axSLIDER_FLAG_NO_SLIDER_LINE, _flags))
	{
		DrawLineBehindSlider_Vertical(gc, rect0);
	}


	gc->SetColor(_info.contourColor);
	gc->DrawRectangleContour(rect0);

	if (_btnImg.IsImageReady())
	{
		gc->DrawPartOfImage(&_btnImg,
			ax::Point(0, _nCurrentImg * _info.btn_size.y),
			_info.btn_size,
			ax::Point(_btnYPos, _sliderPosition));
	}
}

void axSlider::OnPaint()
{
    ax::GC gcs = ax::GC();
    ax::GC* gc = &gcs;
	ax::Size size = GetSize();
//	ax::Rect rect0(0, 0, size.x, size.y);
    
    int radius = _info.contour_round_radius;
    ax::Rect rect0(GetDrawingRect());

    
    if(radius > 1)
    {
        gc->SetColor(_currentBgColor);
        gc->DrawRoundedRectangle(rect0, radius);
    }
    else
    {
        gc->SetColor(_currentBgColor);
        gc->DrawRectangle(rect0);
    }


	// VERTICAL SLIDER.
    if (ax::IsFlag(axSLIDER_FLAG_VERTICAL, _flags))
	{
		DrawVerticalSlider(gc, rect0);
	}

	// HORIZONTAL SLIDER.
	else
	{
        if (ax::IsFlag(axSLIDER_FLAG_BACK_SLIDER, _flags))
		{
			// Back slider.
			ax::Rect back_slider(0, _sliderYPos, size.x,
				_info.slider_width);

			gc->SetColor(_info.backSliderColor);
			gc->DrawRectangle(back_slider);

			gc->SetColor(_info.backSliderContourColor);
			gc->DrawRectangleContour(back_slider);
		}

		int half_btn_size = _info.btn_size.x * 0.5;

        if (!ax::IsFlag(axSLIDER_FLAG_NO_SLIDER_LINE, _flags))
		{
			ax::Rect slider_rect(0, _sliderYPos,
				_sliderPosition + half_btn_size,
				_info.slider_width);

            if (ax::IsFlag(axSLIDER_FLAG_RIGHT_ALIGN, _flags))
			{
				slider_rect = ax::Rect(_sliderPosition,
					_sliderYPos,
					GetSize().x - _sliderPosition + half_btn_size,
					_info.slider_width);
			}
			else
			{
				slider_rect = ax::Rect(0, _sliderYPos,
					_sliderPosition + half_btn_size,
					_info.slider_width);
			}
            
            
            
            if(radius > 1)
            {
                gc->SetColor(_currentSliderColor);
                gc->DrawRoundedRectangle(slider_rect, radius);
                
                gc->SetColor(_info.sliderContourColor);
                gc->DrawRoundedRectangleContour(slider_rect, radius);
            }
            else
            {
                gc->SetColor(_currentSliderColor);
                gc->DrawRectangle(slider_rect);
                
                gc->SetColor(_info.sliderContourColor);
                gc->DrawRectangleContour(slider_rect);
            }

		}

        if(radius > 1)
        {
            gc->SetColor(_info.contourColor);
            gc->DrawRoundedRectangleContour(rect0, radius);
        }
        else
        {
            gc->SetColor(_info.contourColor);
            gc->DrawRectangleContour(rect0);
        }


		if (_btnImg.IsImageReady())
		{
			gc->DrawPartOfImage(&_btnImg,
				ax::Point(0, _nCurrentImg * _info.btn_size.y),
				_info.btn_size,
				ax::Point(_sliderPosition, _btnYPos));
		}
	}

}

