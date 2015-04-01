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
                   const axRect& rect,
                   const std::string& label);
    
    void SetMsg(const std::string& msg);
    
    void SetSelected(const bool& selected);
    
    void SetLabel(const std::string& label);
    
protected:
    axButton::Events _events;
    axButton::Info _info;
    std::string _label, _msg;
    axFlag _flags;
    axFont _font;
    
    axColor* _currentColor;
    bool _selected;
    
    virtual void OnPaint();
    virtual void OnMouseLeftDown(const axPoint& pos);
    virtual void OnMouseLeftDragging(const axPoint &pos);
    virtual void OnMouseLeftUp(const axPoint& pos);
    
    virtual void OnMouseRightDown(const axPoint& pos);
    
    virtual void OnMouseEnter();
    virtual void OnMouseLeave();
    
    bool _isEditing;
};

#endif /* defined(__axLib__axEditorWidget__) */
