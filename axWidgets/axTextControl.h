/// @defgroup Widgets 
/// @{

#ifndef __AX_BUTTON__
#define __AX_BUTTON__

#include "axEvent.h"
#include "axPanel.h"
#include "axColor.h"
#include "axGC.h"
#include "axImage.h"
#include "axMsg.h"
//#include <fstream>

/**************************************************************************//**
 * axButtonFlags.
******************************************************************************/
#define axBUTTON_SINGLE_IMG	axFLAG_1
#define axBUTTON_IMG_RESIZE	axFLAG_2
#define axBUTTON_CAN_SELECTED axFLAG_3 // Not implemented yet.

class axButton;

class axButtonMsg : public axMsg
{
public:
    axButtonMsg()
    {
        _sender = nullptr;
    }
    
    axButtonMsg(axButton* sender, const string& msg)
    {
        _sender = sender;
        _msg = msg;
    }
    
    axButton* GetSender() const
    {
        return _sender;
    }
    
    string GetMsg() const
    {
        return _msg;
    }
    
    axMsg* GetCopy()
    {
        return new axButtonMsg(*this);
    }
    
private:
    axButton* _sender;
    string _msg;
};

struct axButtonEvents
{
    enum : axEventId { BUTTON_CLICK };
    
	axButtonEvents(){}
    axButtonEvents(axEventFunction& fct){ button_click = fct; }
    
    axEventFunction button_click;
};

struct axButtonInfo
{
	axColor normal;
	axColor hover;
	axColor clicking;
	axColor selected;
	axColor contour;
	axColor font_color;

	axButtonInfo(){}
	axButtonInfo(
		const axColor& normal_color,
		const axColor& hover_color,
		const axColor& clicked_color,
		const axColor& selected_color,
		const axColor& contour_color,
		const axColor& font_color_) :
		normal(normal_color),
		hover(hover_color),
		clicking(clicked_color),
		selected(selected_color),
		contour(contour_color),
		font_color(font_color_){}
    
    axButtonInfo(const std::string& path)
    {
        SerializeInput(path);
    }

    void SerializeOutput(const std::string& path)
    {
        fstream file;
        file.open(path, std::fstream::out | std::fstream::binary);

        if (file.fail())
        {
            std::cerr << "Problem opening file " << path << std::endl;
        }
        else
        {
            normal.SerializeOutput(file);
            hover.SerializeOutput(file);
            clicking.SerializeOutput(file);
            selected.SerializeOutput(file);
            contour.SerializeOutput(file);
            font_color.SerializeOutput(file);
        }

    }
    
    void SerializeInput(const std::string& path)
    {
        fstream file;
        file.open(path, std::fstream::in | std::fstream::binary);
        
        if (file.fail())
        {
            std::cerr << "Problem opening file " << path << std::endl;
        }
        else
        {
            normal.SerializeInput(file);
            hover.SerializeInput(file);
            clicking.SerializeInput(file);
            selected.SerializeInput(file);
            contour.SerializeInput(file);
            font_color.SerializeInput(file);
        }
    }
};

#define axSTANDARD_BUTTON 	axButtonInfo( \
							axColor(0.5, 0.5, 0.5),\
							axColor(0.6, 0.6, 0.6),\
							axColor(0.4, 0.4, 0.4),\
							axColor(0.5, 0.5, 0.5),\
							axColor(0.0, 0.0, 0.0),\
							axColor(0.0, 0.0, 0.0)) 

#define axBUTTON_TRANSPARENT 	axButtonInfo( \
axColor(0.0, 0.0, 0.0, 0.0),\
axColor(0.0, 0.0, 0.0, 0.0),\
axColor(0.0, 0.0, 0.0, 0.0),\
axColor(0.0, 0.0, 0.0, 0.0),\
axColor(0.0, 0.0, 0.0, 0.0),\
axColor(0.0, 0.0, 0.0, 1.0))

class axButton : public axPanel
{
public:
	axButton(axWindow* parent,
		const axRect& rect,
		const axButtonEvents& events,
		const axButtonInfo& info,
		string img_path = "",
		string label = "",
		axFlag flags = 0,
		string msg = "");

	axButton(axWindow* parent,
			 const axButtonEvents& events,
			 const string& path);

    // Should be there since update axColor with alpha component.
//	void SetBackgroundAlpha(const float& alpha);

	void SetMsg(const string& msg);
    
	void SetSelected(const bool& selected);
    
    void SetLabel(const std::string& label);

    
protected:
    axButtonEvents _events;
    axButtonInfo _info;
    string _label;
    axImage* _btnImg;
    axFlag _flags;
    string _msg;
    
    axColor* _currentColor;
    bool _selected;
    int _nCurrentImg;
    axColor test; // Should be remove.
    axFloat _bgAlpha; // Should be remove.
    
    enum axButtonState
    {
        axBTN_NORMAL,
        axBTN_HOVER,
        axBTN_DOWN,
        axBTN_SELECTED
    };
    
	virtual void OnPaint();
	virtual void OnMouseLeftDown(const axPoint& pos);
	virtual void OnMouseLeftUp(const axPoint& pos);
	virtual void OnMouseEnter();
	virtual void OnMouseLeave();
};

#endif //__AX_BUTTON__

/// @}


