#include "axEditorMenu.h"
#include "axWidget.h"

axEditorMenu::axEditorMenu(const axRect& rect) :
axPanel(3, nullptr, rect),
_font(0)
{
	_font.SetFontSize(14);
    
    _toolbar = new axEditorToolbar(this, axRect(0, 0, rect.size.x, 40),
                                   axButton::Events(GetOnEditorToolbar()));
    
    
    axScrollBarEvents scrollEvents;
    axScrollBarInfo scroll_info;
    scroll_info.normal = axColor(0.8, 0.8, 0.8);
    scroll_info.hover = axColor(0.9, 0.9, 0.9);
    scroll_info.clicking = axColor(0.7, 0.7, 0.7);
    scroll_info.contour = axColor(0.0, 0.0, 0.0);
    scroll_info.bg_top = axColor(0.45);
    scroll_info.bg_bottom  = axColor(0.4);
    //    scroll_info.selected = scroll_info.normal;
    
 

    axRect attPanelRect(0, 40, rect.size.x - 8, rect.size.y - 40);
    _editorAttributesPanel = new axEditorAttributes(this, attPanelRect);
    
    axPoint pos(rect.size.x - 8, 39);
    axScrollBar* _scrollBar = new axScrollBar(this,
                                              _editorAttributesPanel,
                                              axRect(pos,
                                                     axSize(8, rect.size.y - 40)),
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

void axEditorMenu::UpdateAttribute(const axStringPair& att)
{
    _editorAttributesPanel->UpdateAttribute(att);
}

void axEditorMenu::UpdateInfo()
{
    _editorAttributesPanel->UpdateInfo();
}

void axEditorMenu::OnEditorToolbar(const axButton::Msg& msg)
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
	axGC gc(this);
	axRect rect(GetDrawingRect());

	gc.DrawRectangleColorFade(rect, axColor(0.5), axColor(0.6));
}