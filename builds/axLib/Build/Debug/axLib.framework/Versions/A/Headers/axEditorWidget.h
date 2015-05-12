//
//  axEditorWidget.h
//  axLib
//
//  Created by Alexandre Arsenault on 2015-04-01.
//  Copyright (c) 2015 Alexandre Arsenault. All rights reserved.
//

#ifndef __axLib__axEditorWidget__
#define __axLib__axEditorWidget__

#include "axPanel.h"
#include "axButton.h"
#include "axLabel.h"
#include "axTextBox.h"

class axEditorWidget : public axPanel
{
public:
    axEditorWidget(axWindow* parent,
                   const ax::Rect& rect,
                   const std::string& label);
    
    void SetMsg(const std::string& msg);
    
    void SetSelected(const bool& selected);
    
    void SetLabel(const std::string& label);
    
protected:
    ax::Button::Events _events;
    ax::Button::Info _info;
    std::string _label, _msg;
    axFlag _flags;
    axFont _fontBold, _font;
    
    axColor* _currentColor;
    bool _selected;
    
    virtual void OnPaint();
    virtual void OnMouseLeftDown(const ax::Point& pos);
    virtual void OnMouseLeftDragging(const ax::Point &pos);
    virtual void OnMouseLeftUp(const ax::Point& pos);
    
    virtual void OnMouseRightDown(const ax::Point& pos);
    
    virtual void OnMouseEnter();
    virtual void OnMouseLeave();
    
    bool _isEditing;
};

#endif /* defined(__axLib__axEditorWidget__) */
