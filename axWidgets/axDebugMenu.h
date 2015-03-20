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

class WidgetFolder : public axPanel
{
public:
	WidgetFolder(axWindow* parent,
                 const axRect& rect);

	void Resize(const axSize& size);
    
private:
//	LessonFolderName* _folderName;
//	std::vector<Lesson*> _lessons;
	axFont _font;

	virtual void OnPaint();
};

class axDebugMenu : public axPanel
{
public:
	axDebugMenu(const axRect& rect);

	void Resize(const axSize& size);

private:
	axFont _font;
	std::vector<WidgetFolder*> _folders;
	//Lesson* _lesson;

	virtual void OnPaint();
};