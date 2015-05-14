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



axWidget::axWidget(axWindow* parent, const ax::Rect& rect, axInfo* info):
axPanel(parent, rect),
_info(info)
{
    #ifdef _axDebugEditor_
    _editorBtn = new axDebugButton(this);
    #endif // _axDebugEditor_
}

axWidget::axWidget(const int& type, ax::App* app, const ax::Rect& rect):
axPanel(type, app, rect),
_info(nullptr)
{
    #ifdef _axDebugEditor_
    _editorBtn = new axDebugButton(this);
    #endif // _axDebugEditor_
}

//axWindow::axWindowType axWidget::GetWindowType()
//{
//    return axWindow::axWindowType::axWINDOW_TYPE_WIDGET;
//}

//void axPanel::Update()
//{
////    if(ax::App::GetMainApp()->_widgetSelector != nullptr &&
////       ax::App::GetMainApp()->_widgetSelector->GetSelectedWidget() == this)
////    {
////        if(ax::App::GetMainApp()->IsDebugEditorActive())
////        {
////            ax::App::GetMainApp()->_widgetSelector->SetSelectedWidget(this);
////        }
////
////    }
////    SetNeedUpdate();
////	UpdateAll();
//}

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

