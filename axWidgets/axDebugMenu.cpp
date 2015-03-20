#include "axDebugMenu.h"

//axWindow* parent,
//const axRect& rect,
//const axToggle::Events& events,
//const axToggle::Info& info

//Lesson::Lesson(axWindow* parent, 
//	const axRect& rect, 
//	const axToggle::Events& events,
//	const int& lesson_index,
//	const std::string& lesson_name,
//	const std::string& lesson_length) :
//axToggle(parent, rect, events, 
//		 axToggle::Info(), "", "", 
//		 axToggle::Flags::CANT_UNSELECT_WITH_MOUSE),
//_index(lesson_index),
//_name(lesson_name),
//_time_length(lesson_length),
//_font(0)
//{
//}
//
//void Lesson::OnPaint()
//{
//	axGC gc(this);
//	axRect rect(GetDrawingRect());
//
//	switch (_nCurrentImg)
//	{
//	case axTOG_NORMAL:
//		gc.DrawRectangleColorFade(rect, axColor(0.8), axColor(0.9));
//		break;
//
//	case axTOG_HOVER:
//		gc.DrawRectangleColorFade(rect, axColor(0.9), axColor(0.8));
//		break;
//
//	case axTOG_CLICK:
//		gc.DrawRectangleColorFade(rect, axColor(0.85), axColor(0.75));
//		break;
//
//	case axTOG_SEL_NORMAL:
//	case axTOG_SEL_CLICK:
//	case axTOG_SEL_HOVER:
//		gc.DrawRectangleColorFade(rect, axColor(0.9), axColor(1.0));
//		break;
//	}
//	
//	_font.SetFontSize(14);
//	gc.SetColor(axColor(0.1));
//	gc.DrawStringAlignedCenter(_font, to_string(_index), axRect(0, 0, 30, rect.size.y));
//
//	_font.SetFontSize(12);
//	gc.SetColor(axColor(0.1));
//	gc.DrawString(_font, _name, axPoint(30, 5));
//
//	//std::string time_length("02:56");
//	gc.SetColor(axColor(0.3));
//	gc.DrawString(_font, std::string("Duree :   ") + _time_length, axPoint(30, 20));
//
//	gc.SetColor(axColor(0.4));
//	gc.DrawLine(axPoint(0, 0), axPoint(rect.size.x, 0));
//	gc.DrawLine(axPoint(0, rect.size.y), axPoint(rect.size.x, rect.size.y));	
//}
//
//
//LessonFolderName::LessonFolderName(axWindow* parent, 
//	const axRect& rect, 
//	const axToggle::Events& events,
//	const std::string lesson_name,
//	const std::string& author_name) :
//axToggle(parent, rect, events, axToggle::Info()),
////axPanel(parent, rect),
//_font(0),
//_name(lesson_name),
//_author(author_name)
//{
//}
//
//void LessonFolderName::OnPaint()
//{
//	axGC gc(this);
//	axRect rect(GetDrawingRect());
//
//	switch (_nCurrentImg)
//	{
//	case axTOG_NORMAL:
//		gc.DrawRectangleColorFade(rect, axColor(0.5), axColor(0.6));
//		//gc.DrawRectangleColorFade(rect, axColor(0.8), axColor(0.9));
//		break;
//
//	case axTOG_HOVER:
//		gc.DrawRectangleColorFade(rect, axColor(0.6), axColor(0.5));
//		break;
//
//	case axTOG_CLICK:
//		gc.DrawRectangleColorFade(rect, axColor(0.55), axColor(0.65));
//		break;
//
//	case axTOG_SEL_NORMAL:
//	case axTOG_SEL_CLICK:
//	case axTOG_SEL_HOVER:
//		gc.DrawRectangleColorFade(rect, axColor(0.9), axColor(1.0));
//		break;
//	}
//
//	_font.SetFontSize(14);
//	gc.SetColor(axColor(0.1));
//	gc.DrawString(_font, _name, axPoint(8, 3));
//
//	_font.SetFontSize(12);
//	gc.SetColor(axColor(0.3));
//	gc.DrawString(_font, std::string("Auteur : ") + _author, axPoint(8, 17));
//
//	gc.SetColor(axColor(0.4));
//	gc.DrawLine(axPoint(0, 0), axPoint(rect.size.x, 0));
//	gc.DrawLine(axPoint(0, rect.size.y), axPoint(rect.size.x, rect.size.y));
//}

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


axDebugMenu::axDebugMenu(const axRect& rect) :
axPanel(3, nullptr, rect),
_font(0)
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

void axDebugMenu::Resize(const axSize& size)
{
//	SetSize(size);
//	for (auto& n : _folders)
//	{
//		n->Resize(size);
//	}
}

void axDebugMenu::OnPaint()
{
	axGC gc(this);
	axRect rect(GetDrawingRect());

	gc.DrawRectangleColorFade(rect, axColor(0.5), axColor(0.6));
	gc.DrawRectangleColorFade(axRect(0, 0, rect.size.x, 40),
                              axColor(0.15), axColor(0.3));

	gc.SetColor(axColor(0.7));
	gc.DrawStringAlignedCenter(_font, "List of axWidgets",
                               axRect(0, 0, rect.size.x, 40));
}