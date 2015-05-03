//
//  FileBrowser.cpp
//  axSSH
//
//  Created by Alexandre Arsenault on 2015-04-20.
//  Copyright (c) 2015 Alexandre Arsenault. All rights reserved.
//

#include "FileBrowserFolder.h"
#include "FileBrowserElements.h"
#include <dirent.h>


FileBrowserFolder::FileBrowserFolder(axWindow* parent, const axRect& rect):
// Parent.
axPanel(parent, rect),
//_ssh(nullptr),
_font(0)
{
    axRect scrollPanelRect(0, 0, rect.size.x - 8, rect.size.y);
    _scrolled_panel = new axPanel(this, scrollPanelRect);
    _scrolled_panel->SetBlockDrawing(true);
    
//    axPrint("Scroll panel id :", _scrolled_panel->GetId());
    
    axScrollBarEvents scrollEvents;
    
    axScrollBarInfo scroll_info;
    scroll_info.normal = axColor(0.6);
    scroll_info.hover = axColor(0.67);
    scroll_info.clicking = axColor(0.62);
    scroll_info.contour = axColor(0.93);
    scroll_info.bg_top = axColor(0.93);
    scroll_info.bg_bottom  = axColor(0.90);
    
    axPoint pos(rect.size.x - 8, 0);
    
    axScrollBar* scrollBar = new axScrollBar(this,
                                             _scrolled_panel,
                                             axRect(pos,
                                                    axSize(8, rect.size.y)),
                                             scrollEvents,
                                             scroll_info);
    
    _scrolled_panel->SetScrollBar(scrollBar);
}

axStringVector ListFileInFolder(const std::string& folder_path)
{
    DIR *dir;
    struct dirent *ent;
    
    axStringVector elem_list;
    
    if ((dir = opendir (folder_path.c_str())) == NULL)
    {
        return elem_list;
    }
    
    // Print all the files and directories within directory.
    while ((ent = readdir (dir)) != NULL)
    {
        elem_list.push_back(ent->d_name);
    }
    
    closedir (dir);
    return elem_list;
}

void FileBrowserFolder::ListFile(const std::string& path,
                                 const std::string& selected_folder)
{
    axStringVector files = ListFileInFolder(path);
    
    
    _files.clear();
    for(int i = 0; i < _folders.size(); i++)
    {
        axApp::GetInstance()->GetCore()->GetWindowManager()->GetWindowTree()->
        DeleteWindow(_folders[i]);
    }
    _folders.clear();
    
    _files = files;
    
    axPoint pos(0, 0);
    axSize size(GetRect().size.x - 8, 20);
    
    axButton::Info btn_info;
    btn_info.normal = axColor(0.97);
    btn_info.hover = axColor(0.99);
    btn_info.clicking = axColor(0.98);
    btn_info.contour = axColor(0.93);
    btn_info.selected = btn_info.normal;
    btn_info.round_corner_radius = 0;
    btn_info.font_color = axColor(0.0);
    
    axButton::Info btn_info_selected;
    //            btn_info_selected.normal = axColor("#35A6EE");
    btn_info_selected.normal = axColor(0.20784313725490197,
                                       0.6509803921568628,
                                       0.9333333333333333);
    btn_info_selected.hover = btn_info_selected.normal;
    btn_info_selected.clicking = btn_info_selected.normal;
    btn_info_selected.contour = axColor(0.93);
    btn_info_selected.selected = btn_info_selected.normal;
    btn_info_selected.round_corner_radius = 0;
    btn_info_selected.font_color = axColor(1.0);
    
    
    for(auto& k : _files)
    {
        axButton::Info info = btn_info;
        
        if(k == (selected_folder + "/"))
        {
            //                    axPrint("same folder");
            info = btn_info_selected;
        }
        std::string file_type = axGetExtension(k);
        
        std::string fileImg("file.png");
        
        if(file_type == "")
        {
            fileImg = "folder1.png";
        }
        
        axEventFunction fct = GetParent()->GetEventFunction("OnButtonClick");
        
        FileBrowserElement* btn =
        new FileBrowserElement(_scrolled_panel,
                               axRect(pos, size),
                               axButton::Events(fct),
                               info,
                               fileImg, k,
                               axNO_FLAG,
                               path + k);
        
        _folders.push_back(btn);
        
        pos = btn->GetNextPosDown(0);
    }
    
    axSize newSize(GetRect().size.x,
                   _folders[_folders.size() - 1]->GetNextPosDown(0).y);
    
    _scrolled_panel->SetSizeNoShowRect(newSize);
    
    axScrollBar* scrollBar = _scrolled_panel->GetScrollBar();
    if(scrollBar != nullptr)
    {
        scrollBar->SetPanelSize(newSize);
    }


    
//    if(_ssh != nullptr && _ssh->IsConnected())
//    {
//
////        axPrint("Before ssh request");
//        std::string request_command = "ls --file-type --almost-all " + path;
////        axPrint("Request :", request_command);
//        std::string answer = _ssh->Request(request_command);
////        axPrint("After ssh request");
//
//
//        if(answer == "Error")
//        {
//            axPrint("ANSWER :", answer);
//            return;
//        }
//
//        _files.clear();
//
//        for(int i = 0; i < _folders.size(); i++)
//        {
//            axApp::GetInstance()->GetCore()->GetWindowManager()->GetWindowTree()->
//            DeleteWindow(_folders[i]);
//        }
//        _folders.clear();
//        
//        
//        if(path == "")
//        {
//            return;
//        }
//        
//        // @todo Replace with an exception in axSSH::Request.
//        if(answer != "Error")
//        {
//            
//            _files = GetVectorFromStringDelimiter(answer, "\n");
////            axStringVector files;// = GetVectorFromStringDelimiter(answer, "\n");
////            
////            for(auto& f : _files)
////            {
////                if(f != "" && f != " ")
////                {
////                    files.push_back(f);
////                }
////            }
////            
////            _files = files;
//            
//            axPoint pos(0, 0);
//            axSize size(GetRect().size.x - 8, 20);
//            
//            axButton::Info btn_info;
//            btn_info.normal = axColor(0.97);
//            btn_info.hover = axColor(0.99);
//            btn_info.clicking = axColor(0.98);
//            btn_info.contour = axColor(0.93);
//            btn_info.selected = btn_info.normal;
//            btn_info.round_corner_radius = 0;
//            btn_info.font_color = axColor(0.0);
//            
//            axButton::Info btn_info_selected;
////            btn_info_selected.normal = axColor("#35A6EE");
//            btn_info_selected.normal = axColor(0.20784313725490197,
//                                               0.6509803921568628,
//                                               0.9333333333333333);
//            btn_info_selected.hover = btn_info_selected.normal;
//            btn_info_selected.clicking = btn_info_selected.normal;
//            btn_info_selected.contour = axColor(0.93);
//            btn_info_selected.selected = btn_info_selected.normal;
//            btn_info_selected.round_corner_radius = 0;
//            btn_info_selected.font_color = axColor(1.0);
//            
//            
//            for(auto& k : _files)
//            {
//                axButton::Info info = btn_info;
//                
//                if(k == (selected_folder + "/"))
//                {
////                    axPrint("same folder");
//                    info = btn_info_selected;
//                }
//                std::string file_type = axGetExtension(k);
//                
//                std::string fileImg("file.png");
//                
//                if(file_type == "")
//                {
//                    fileImg = "folder1.png";
//                }
//                
//                axEventFunction fct = GetParent()->GetEventFunction("OnButtonClick");
//                
//                FileBrowserElement* btn =
//                        new FileBrowserElement(_scrolled_panel,
//                                               axRect(pos, size),
//                                               axButton::Events(fct),
//                                               info,
//                                               fileImg, k,
//                                               axNO_FLAG,
//                                               path + k);
//                
//                _folders.push_back(btn);
//                
//                pos = btn->GetNextPosDown(0);
//            }
//            
//            axSize newSize(GetRect().size.x,
//                           _folders[_folders.size() - 1]->GetNextPosDown(0).y);
//            
//            _scrolled_panel->SetSizeNoShowRect(newSize);
//            
//            axScrollBar* scrollBar = _scrolled_panel->GetScrollBar();
//            if(scrollBar != nullptr)
//            {
//                scrollBar->SetPanelSize(newSize);
//            }
//        }
//    }
}

//void FileBrowserFolder::SetSSHHandle(axSSH* ssh)
//{
//    _ssh = ssh;
//    Update();
//}

void FileBrowserFolder::OnPaint()
{
    axGC* gc = GetGC();
    axRect rect(GetRect());
    axRect rect0(axPoint(0, 0), rect.size);
    
    gc->SetColor(axColor(0.97));
    gc->DrawRectangle(rect0);
}