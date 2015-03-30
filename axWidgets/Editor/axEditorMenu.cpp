#include "axEditorMenu.h"
#include "axWidget.h"


WidgetFolder::WidgetFolder(axWindow* parent,
	const axRect& rect) :
axPanel(parent, rect),
_font(0)
{
	_font.SetFontSize(12);

//	_folderName = new LessonFolderName(this, 
//		axRect(0, 0, rect.size.x, 40), 
//		axToggle::Events(),
//		info.name, info.author);

//	axPoint next_pos(0, 40);
//	for (auto& n : info.lessons_info)
//	{
//		Lesson* lesson = new Lesson(this, axRect(next_pos, axSize(rect.size.x, 40)),
//			axToggle::Events(), n.lesson_index, n.lesson_name, n.lesson_length);
//		_lessons.push_back(lesson);
//
//		next_pos = lesson->GetNextPosDown(0);
//	}

//	SetSize(axSize(rect.size.x, 40 + 40 * _lessons.size()));
}

void WidgetFolder::Resize(const axSize& size)
{
//	axSize current_size(GetSize());
//	SetSize(axSize(size.x, current_size.y));
//
//	//_folderName->SetSize(axSize(size.x, 40));
//
//	for (auto& n : _lessons)
//	{
//		n->SetSize(axSize(size.x, 40));
//	}
}

void WidgetFolder::OnPaint()
{
	axGC gc(this);
	axRect rect(GetDrawingRect());

	gc.DrawRectangleColorFade(rect, axColor(0.8), axColor(0.9));
}


axEditorMenu::axEditorMenu(const axRect& rect) :
axPanel(3, nullptr, rect),
_font(0),
_widget(nullptr)
{
	_font.SetFontSize(14);

//	axPoint next_pos(0, 40);
//	for (auto& n : folders_info)
//	{
//		WidgetFolder* folder = new WidgetFolder(this,
//			axRect(next_pos, axSize(rect.size.x, 40)), n);
//
//		_folders.push_back(folder);
//
//		next_pos = folder->GetNextPosDown(0);
//	}
}

void axEditorMenu::Resize(const axSize& size)
{
//	SetSize(size);
//	for (auto& n : _folders)
//	{
//		n->Resize(size);
//	}
}

void axEditorMenu::SetEditingWidget(axWidget* widget)
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
    
    int i = 0;
    axLabel* label = nullptr;
    axTextBox* txtBox = nullptr;
    

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
    
    AddEditorLabel("Builder Info", labelInfoWindow);
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
    
    AddEditorLabel("Widget Info", labelInfoWindow);
    for(auto& n : attributes)
    {
        AddEditorAttribute(axStringPair(n, info->GetAttributeValue(n)),
                           labelInfo, txtInfo, txtEvents);
    }

    
    Update();
}

void axEditorMenu::AddEditorAttribute(const axStringPair& att,
                                      const axLabel::Info& labelInfo,
                                      const axTextBox::Info& txtInfo,
                                      const axTextBox::Events& evt)
{
    axPoint pos(0, 40);
    
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

void axEditorMenu::AddEditorLabel(const std::string& name,
                                  const axLabel::Info& labelInfo)
{
    axPoint pos(0, 40);
    
    if(_infoEditor.size())
    {
        pos = std::get<1>(_infoEditor[_infoEditor.size() - 1])->GetNextPosDown(0);
    }
    
    axLabel* label = new_ axLabel(this, axRect(pos, axSize(300, 25)),
                                  labelInfo, name);
    
    _infoEditor.push_back(axEditorTuple(name, label, nullptr));
    
    label->SetEditingWidget(true);
    //txtBox->SetEditingWidget(true);
    label->SetEditable(false);
    //txtBox->SetEditable(false);
}

void axEditorMenu::OnAttributeEdit(const axTextBox::Msg& msg)
{
//    axWidget* widget = static_cast<axWidget*>(GetParent());
    
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

void axEditorMenu::UpdateAttribute(const axStringPair& att)
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

void axEditorMenu::UpdateInfo()
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

void axEditorMenu::OnPaint()
{
	axGC gc(this);
	axRect rect(GetDrawingRect());

	gc.DrawRectangleColorFade(rect, axColor(0.5), axColor(0.6));
	gc.DrawRectangleColorFade(axRect(0, 0, rect.size.x, 40),
                              axColor(0.15), axColor(0.3));

	gc.SetColor(axColor(0.7));
	gc.DrawStringAlignedCenter(_font, "List of axWidgets",
                               axRect(0, 0, rect.size.x, 40));
    
    if(_widget != nullptr)
    {
        gc.SetColor(axColor::axBlackColor);
        gc.DrawString(_font, std::to_string(_widget->GetId()), axPoint(50, 50));
    }
    else
    {
        gc.SetColor(axColor::axBlackColor);
        gc.DrawString(_font, "None", axPoint(50, 50));
    }
    
}