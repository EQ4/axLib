#include "axEditorAttributes.h"

axEditorAttributes::axEditorAttributes(axWindow* parent, const axRect& rect) :
axPanel(parent, rect),
_font(0),
_widget(nullptr)
{
    _font.SetFontSize(14);
    SetBlockDrawing(true);
}

void axEditorAttributes::SetEditingWidget(axWidget* widget)
{
    _widget = widget;
    
    axTextBox::Events txtEvents;
    txtEvents.enter_click = GetOnAttributeEdit();
    
    axTextBox::Info txtInfo;
    txtInfo.normal = axColor(1.0, 1.0, 1.0, 1.0);
    txtInfo.hover = axColor(1.0, 1.0, 1.0, 1.0);
    txtInfo.selected = axColor(1.0, 1.0, 1.0, 1.0);
    txtInfo.highlight = axColor(0.4, 0.4, 0.6, 1.0);
    txtInfo.contour = axColor(0.0, 0.0, 0.0, 1.0);
    txtInfo.cursor = axColor(1.0, 0.0, 0.0, 1.0);
    txtInfo.selected_shadow = axColor(0.8, 0.8, 0.8, 0.2);
    
    axLabel::Info labelInfo;
    labelInfo.normal = axColor(0.8, 0.8, 0.8, 1.0);
    labelInfo.contour = axColor(0.0, 0.0, 0.0, 1.0);
    labelInfo.font_color = axColor(0.0, 0.0, 0.0, 1.0);
    labelInfo.font_size = 12;
    labelInfo._alignement = axAlignement::axALIGN_CENTER;
    
    
    axLabel::Info labelInfoWindow;
    labelInfoWindow.normal = axColor(0.4, 0.4, 0.4, 1.0);
    labelInfoWindow.contour = axColor(0.0, 0.0, 0.0, 1.0);
    labelInfoWindow.font_color = axColor(0.8, 0.8, 0.8, 1.0);
    labelInfoWindow.font_size = 12;
    labelInfoWindow._alignement = axAlignement::axALIGN_CENTER;
    
    axStringVector attributes = widget->GetInfo()->GetParamNameList();
    axInfo* info = widget->GetInfo();
    
    
    for(int i = 0; i < _infoEditor.size(); i++)
    {
        axApp::GetInstance()->GetCore()->GetPopupManager()->GetWindowTree()->
        DeleteWindow( std::get<1>(_infoEditor[i]) );
        
        if(std::get<2>(_infoEditor[i]) != nullptr)
        {
            axApp::GetInstance()->GetCore()->GetPopupManager()->GetWindowTree()->
            DeleteWindow( std::get<2>(_infoEditor[i]) );
        }
    }
    _infoEditor.clear();
    
    AddEditorLabel("Runtime Info", labelInfoWindow);
    AddEditorAttribute(axStringPair("object id",
                                    std::to_string(_widget->GetId())),
                       labelInfo, txtInfo, axTextBox::Events());
    
    axRect rel_rect(_widget->GetRect());
    std::string relative_rect = std::to_string(rel_rect.position.x) + ", " +
    std::to_string(rel_rect.position.y) + ", " +
    std::to_string(rel_rect.size.x) + ", " +
    std::to_string(rel_rect.size.y);
    
    AddEditorAttribute(axStringPair("relative rectangle", relative_rect),
                       labelInfo, txtInfo, axTextBox::Events());
    
    axRect abs_rect(_widget->GetAbsoluteRect());
    std::string absolute_rect = std::to_string(abs_rect.position.x) + ", " +
    std::to_string(abs_rect.position.y) + ", " +
    std::to_string(abs_rect.size.x) + ", " +
    std::to_string(abs_rect.size.y);
    
    AddEditorAttribute(axStringPair("absolute rectangle", absolute_rect),
                       labelInfo, txtInfo, axTextBox::Events());
    
    AddEditorLabel("Builder Info", labelInfoWindow);
    //    axStringVector builder_list = widget->GetParamNameList();
    axVectorPairString builder_attributes = widget->GetBuilderAttributes();
    
    for(auto& n : builder_attributes)
    {
        if(n.first == "rect")
        {
            n.first = "start rectangle";
        }
        AddEditorAttribute(n, labelInfo, txtInfo, axTextBox::Events());
    }
    
    AddEditorLabel("Widget Info", labelInfoWindow);
    
    AddEditorAttribute(axStringPair("info path", info->GetPath()),
                       labelInfo, txtInfo, axTextBox::Events());
    
    for(auto& n : attributes)
    {
        AddEditorAttribute(axStringPair(n, info->GetAttributeValue(n)),
                           labelInfo, txtInfo, txtEvents);
    }
    
    axRect lastRect = std::get<1>(_infoEditor[_infoEditor.size()-1])->GetRect();
    axSize newSize(GetRect().size.x, lastRect.position.y + lastRect.size.y);
    SetSizeNoShowRect(newSize);
    
    axScrollBar* scrollBar = GetScrollBar();
    if(scrollBar != nullptr)
    {
        scrollBar->SetPanelSize(newSize);
    }
    
    Update();
}

void axEditorAttributes::AddEditorAttribute(const axStringPair& att,
                                      const axLabel::Info& labelInfo,
                                      const axTextBox::Info& txtInfo,
                                      const axTextBox::Events& evt)
{
    axPoint pos(0, 0);
    
    if(_infoEditor.size())
    {
        pos = std::get<1>(_infoEditor[_infoEditor.size() - 1])->GetNextPosDown(0);
    }
    
    axLabel* label = new_ axLabel(this, axRect(pos, axSize(120, 25)),
                                  labelInfo, att.first);
    
    axTextBox* txtBox = new_ axTextBox(this, axRect(label->GetNextPosRight(0),
                                                    axSize(180, 25)),
                                       evt, txtInfo, "",
                                       att.second);
    
    _infoEditor.push_back(axEditorTuple(att.first, label, txtBox));
    
    label->SetEditingWidget(true);
    txtBox->SetEditingWidget(true);
    label->SetEditable(false);
    txtBox->SetEditable(false);
}

void axEditorAttributes::AddEditorLabel(const std::string& name,
                                  const axLabel::Info& labelInfo)
{
    axPoint pos(0, 00);
    
    if(_infoEditor.size())
    {
        pos = std::get<1>(_infoEditor[_infoEditor.size() - 1])->GetNextPosDown(0);
    }
    
    axLabel* label = new_ axLabel(this, axRect(pos, axSize(300, 25)),
                                  labelInfo, name);
    
    _infoEditor.push_back(axEditorTuple(name, label, nullptr));
    
    label->SetEditingWidget(true);
    label->SetEditable(false);
}

void axEditorAttributes::OnAttributeEdit(const axTextBox::Msg& msg)
{    
    if(_widget != nullptr)
    {
        axVectorPairString attributes;
        
        for(auto& n : _infoEditor)
        {
            if(std::get<2>(n) != nullptr)
            {
                std::string name = std::get<0>(n);
                std::string value = std::get<2>(n)->GetLabel();
                attributes.push_back(axStringPair(name, value));
            }
        }
        
        _widget->SetInfo(attributes);
    }
}

void axEditorAttributes::UpdateAttribute(const axStringPair& att)
{
    for(auto& n : _infoEditor)
    {
        if(std::get<0>(n) == att.first &&
           std::get<2>(n)->GetLabel() != att.second)
        {
            std::get<2>(n)->SetLabel(att.second);
            break;
        }
    }
}

void axEditorAttributes::UpdateInfo()
{
    axStringVector attributes = _widget->GetInfo()->GetParamNameList();
    axInfo* info = _widget->GetInfo();
    
    UpdateAttribute(axStringPair("object id", std::to_string(_widget->GetId())));
    
    axRect rel_rect(_widget->GetRect());
    std::string relative_rect = std::to_string(rel_rect.position.x) + ", " +
    std::to_string(rel_rect.position.y) + ", " +
    std::to_string(rel_rect.size.x) + ", " +
    std::to_string(rel_rect.size.y);
    
    UpdateAttribute(axStringPair("relative rectangle", relative_rect));
    
    
    axRect abs_rect(_widget->GetAbsoluteRect());
    std::string absolute_rect = std::to_string(abs_rect.position.x) + ", " +
    std::to_string(abs_rect.position.y) + ", " +
    std::to_string(abs_rect.size.x) + ", " +
    std::to_string(abs_rect.size.y);
    
    UpdateAttribute(axStringPair("absolute rectangle", absolute_rect));
    
    
    for(auto& n : attributes)
    {
        UpdateAttribute(axStringPair(n, info->GetAttributeValue(n)));
    }
}

void axEditorAttributes::OnPaint()
{
    axGC gc(this);
    axRect rect(GetDrawingRect());
    
    gc.DrawRectangleColorFade(rect, axColor(0.5), axColor(0.6));
}