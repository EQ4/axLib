#include "axEditorMenu.h"
#include "axWidget.h"
#include <axUtils/axUtils.h>

axEditorMenu::axEditorMenu(const ax::Rect& rect) :
axPanel(3, nullptr, rect),
_font(0)
{
	_font.SetFontSize(14);
    
    _toolbar = new axEditorToolbar(this, ax::Rect(0, 0, rect.size.x, 40),
                                   ax::Button::Events(GetOnEditorToolbar()));
    
    
    axScrollBarEvents scrollEvents;
    axScrollBarInfo scroll_info;
    scroll_info.normal = ax::Color(0.8, 0.8, 0.8);
    scroll_info.hover = ax::Color(0.9, 0.9, 0.9);
    scroll_info.clicking = ax::Color(0.7, 0.7, 0.7);
    scroll_info.contour = ax::Color(0.0, 0.0, 0.0);
    scroll_info.bg_top = ax::Color(0.45);
    scroll_info.bg_bottom  = ax::Color(0.4);
    //    scroll_info.selected = scroll_info.normal;
    
 

    ax::Rect attPanelRect(0, 40, rect.size.x - 8, rect.size.y - 40);
    _editorAttributesPanel = new axEditorAttributes(this, attPanelRect);
    
    ax::Point pos(rect.size.x - 8, 39);
    axScrollBar* _scrollBar = new axScrollBar(this,
                                              _editorAttributesPanel,
                                              ax::Rect(pos,
                                                     ax::Size(8, rect.size.y - 40)),
                                              scrollEvents,
                                              scroll_info);
    
    _editorAttributesPanel->SetScrollBar(_scrollBar);
    
    
    _editorWidgetPanel = new axEditorWidgetsPanel(this, attPanelRect);
    _editorWidgetPanel->Hide();
    
//    _editorWidgetPanel->SetEditingWidget(true);
//    _editorWidgetPanel->SetEditable(false);
}

void axEditorMenu::SetEditingWidget(axWidget* widget)
{
    _editorAttributesPanel->SetEditingWidget(widget);

}

void axEditorMenu::UpdateAttribute(const ax::StringPair& att)
{
    _editorAttributesPanel->UpdateAttribute(att);
}

void axEditorMenu::UpdateInfo()
{
    _editorAttributesPanel->UpdateInfo();
}

void axEditorMenu::OnEditorToolbar(const ax::Button::Msg& msg)
{
    if(msg.GetMsg() == "Widgets")
    {
        _editorAttributesPanel->Hide();
        _editorWidgetPanel->Show();
    }
    else if(msg.GetMsg() == "Attributes")
    {
        _editorAttributesPanel->Show();
        _editorWidgetPanel->Hide();
    }
    
    Update();
}

void axEditorMenu::OnPaint()
{
    ax::GC gc;
	ax::Rect rect(GetDrawingRect());

	//gc.DrawRectangleColorFade(rect, ax::Color(0.5), ax::Color(0.6));
}