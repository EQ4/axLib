#include "axLib.h"
#include "axEditorAttributes.h"
#include "axEditorToolbar.h"
#include "axEditorWidgetsPanel.h"

class axWidget;

class axEditorMenu : public axPanel
{
public:
	axEditorMenu(const ax::Rect& rect);

    void SetEditingWidget(axWidget* widget);
    
    void UpdateInfo();
    void UpdateAttribute(const ax::StringPair& att);
    
    axEVENT_ACCESSOR(axButton::Msg, OnEditorToolbar);
    
private:
	axFont _font;
    axEditorAttributes* _editorAttributesPanel;
    axEditorWidgetsPanel* _editorWidgetPanel;
    axEditorToolbar* _toolbar;
    
    void OnEditorToolbar(const axButton::Msg& msg);
    
	virtual void OnPaint();
};