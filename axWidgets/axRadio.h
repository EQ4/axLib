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

#ifndef __AX_RADIO__
#define __AX_RADIO__

/*******************************************************************************
 * @file    axRadio
 * @author  Alexandre Arsenault <alx.arsenault@gmail.com>
 * @brief   axToggle.
 * @date    16/04/2015
 ******************************************************************************/

/// @defgroup Widgets
/// @{

/// @defgroup Radio
/// @{

#include "axToggle.h"

/*******************************************************************************
 * axRadio.
 ******************************************************************************/
class axRadio : public axToggle
{
public:
    
    typedef axToggle::Info Info;
    typedef axToggle::Events Events;
    
    /***************************************************************************
     * axRadio::axRadio.
     **************************************************************************/
    axRadio(axWindow* parent,
            const ax::Rect& rect,
            const axRadio::Events& events,
            const axRadio::Info& info,
            std::string img_path = "",
            std::string label = "",
            ax::Flag flags = 0,
            std::string msg = "");
    
    void SetMsg(const std::string& msg);
    void SetSelected(const bool& selected);

private:
    // Events.
	virtual void OnPaint();
//	virtual void OnMouseLeftDown(const ax::Point& pos);
//	virtual void OnMouseLeftUp(const ax::Point& pos);
//	virtual void OnMouseEnter();
//	virtual void OnMouseLeave();
};

/// @}
/// @}
#endif //__AX_TOGGLE__

