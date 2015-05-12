//
//  axEditorAtrributes.h
//  axLib
//
//  Created by Alexandre Arsenault on 2015-03-30.
//  Copyright (c) 2015 Alexandre Arsenault. All rights reserved.
//

#ifndef __axLib__axEditorAtrributes__
#define __axLib__axEditorAtrributes__

#include "axLib.h"

class axEditorAttributes : public axPanel
{
public:
    axEditorAttributes(axWindow* parent, const ax::Rect& rect);
    
    void SetEditingWidget(axWidget* widget);
    
    void UpdateInfo();
    void UpdateAttribute(const ax::StringPair& att);
    
    // axEvents.
    axEVENT_ACCESSOR(axTextBox::Msg, OnAttributeEdit);
    
private:
    axFont _font;
//    std::vector<WidgetFolder*> _folders;
    
    typedef std::tuple<std::string, axLabel*, axTextBox*> axEditorTuple;
    std::vector<axEditorTuple> _infoEditor;
    
    void OnAttributeEdit(const axTextBox::Msg& msg);
    
    void AddEditorAttribute(const ax::StringPair& att,
                            const axLabel::Info& labelInfo,
                            const axTextBox::Info& txtInfo,
                            const axTextBox::Events& evt);
    
    void AddEditorLabel(const std::string& name,
                        const axLabel::Info& labelInfo);
    
    axWidget* _widget;
    
    virtual void OnPaint();
};

#endif /* defined(__axLib__axEditorAtrributes__) */
