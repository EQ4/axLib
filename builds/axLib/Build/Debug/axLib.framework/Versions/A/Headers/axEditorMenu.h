#include "axLib.h"

//struct LessonInfo
//{
//	LessonInfo(){}
//
//	LessonInfo(const int& index,
//		const std::string& name,
//		const std::string& length):
//		lesson_index(index),
//		lesson_name(name),
//		lesson_length(length)
//	{
//
//	}
//
//	int lesson_index;
//	std::string lesson_name;
//	std::string lesson_length;
//};
//
//struct WidgetInfo
//{
//	FolderInfo(){}
//
//	FolderInfo(const std::string& folder_name,
//		const std::string& author_name,
//		const std::vector<LessonInfo>& lessons) :
//		name(folder_name),
//		author(author_name),
//		lessons_info(lessons)
//	{
//
//	}
//
//	std::string name, author;
//	std::vector<LessonInfo> lessons_info;
//};
//
//class Lesson : public axToggle
//{
//public:
//	Lesson(axWindow* parent, 
//		const axRect& rect, 
//		const axToggle::Events& events,
//		const int& lesson_index,
//		const std::string& lesson_name,
//		const std::string& lesson_length);
//
//
//private:
//	axFont _font;
//	std::string _name, _time_length;
//	int _index;
//
//	virtual void OnPaint();
//};
//
//class LessonFolderName : public axToggle
//{
//public:
//	LessonFolderName(axWindow* parent, 
//		const axRect& rect, 
//		const axToggle::Events& events,
//		const std::string folder_name,
//		const std::string& author_name);
//
//
//private:
//	axFont _font;
//	std::string _name, _author;
//
//	virtual void OnPaint();
//};
class axWidget;

class WidgetFolder : public axPanel
{
public:
	WidgetFolder(axWindow* parent,
                 const axRect& rect);

	void Resize(const axSize& size);
    
private:

	axFont _font;

	virtual void OnPaint();
};

class axEditorMenu : public axPanel
{
public:
	axEditorMenu(const axRect& rect);

	void Resize(const axSize& size);
    
    void SetEditingWidget(axWidget* widget);
    
    void UpdateInfo();
    void UpdateAttribute(const axStringPair& att);
    
    // axEvents.
    axEVENT_ACCESSOR(axTextBox::Msg, OnAttributeEdit);

private:
	axFont _font;
	std::vector<WidgetFolder*> _folders;
    
    
    typedef std::tuple<std::string, axLabel*, axTextBox*> axEditorTuple;
    std::vector<axEditorTuple> _infoEditor;
    
    void OnAttributeEdit(const axTextBox::Msg& msg);
    
    void AddEditorAttribute(const axStringPair& att,
                            const axLabel::Info& labelInfo,
                            const axTextBox::Info& txtInfo,
                            const axTextBox::Events& evt);
    
    void AddEditorLabel(const std::string& name,
                            const axLabel::Info& labelInfo);
    
    axWidget* _widget;
    
	virtual void OnPaint();
};