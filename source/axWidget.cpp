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
#include "axWidget.h"
#include "axConfig.h"

#include "axEditorButton.h"



axWidget::axWidget(axWindow* parent, const axRect& rect, axInfo* info):
axPanel(parent, rect),
_info(info)
{
    #ifdef _axDebugEditor_
    _editorBtn = new axDebugButton(this);
    #endif // _axDebugEditor_
}

axWidget::axWidget(int f, axWindow* parent, const axRect& rect):
axPanel(f, parent, rect),
_info(nullptr)
{
    #ifdef _axDebugEditor_
    _editorBtn = new axDebugButton(this);
    #endif // _axDebugEditor_
}

axWindow::axWindowType axWidget::GetWindowType()
{
    return axWindow::axWindowType::axWINDOW_TYPE_WIDGET;
}

void axWidget::SetInfo(const ax::StringPairVector& attributes)
{
    _info->SetAttributes(attributes);
    Update();
}

void axWidget::SetBuilderAttributes(const ax::StringPairVector& attributes)
{
    _builderAttributes = attributes;
}

ax::StringPairVector axWidget::GetBuilderAttributes() const
{
    return _builderAttributes;
}

axInfo* axWidget::GetInfo()
{
    return _info;
}

