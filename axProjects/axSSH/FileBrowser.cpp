//
//  axFileBrowser.cpp
//  axSSH
//
//  Created by Alexandre Arsenault on 2015-04-20.
//  Copyright (c) 2015 Alexandre Arsenault. All rights reserved.
//

#include "FileBrowser.h"

FileBrowser::FileBrowser(axWindow* parent, const axRect& rect):
// Parent.
axPanel(parent, rect)
//_ssh(nullptr)
{
    AddEventFunction("OnButtonClick", GetOnButtonClick());
    
    axPoint folderPos(0, 0);
    axSize folderSize(183, rect.size.y);
    
    for(int i = 0; i < 3; i++)
    {
        axRect folderRect(folderPos, folderSize);
        
        FileBrowserFolder* folder = new FileBrowserFolder(this, folderRect);
        folder->SetBlockDrawing(true);
        
        _folders.push_back(folder);
        
        folderPos = folder->GetNextPosRight(0);
    }
}

void FileBrowser::OnButtonClick(const axButton::Msg& msg)
{
    axPrint(msg.GetMsg());
    ListFile(msg.GetMsg());
}

void FileBrowser::ListFile(const std::string& path)
{
    axStringVector folders = GetVectorFromStringDelimiter(path, "/");
    axStringVector format_folders;
    
    for(auto& n : folders)
    {
        if(n != "" && n != " ")
        {
            format_folders.push_back(n);
        }
    }
    
//    axPrint("FOLDERS:");
//    for(auto& n : format_folders)
//    {
//        axPrint(n);
//    }
    
//    axPrint(format_folders.size());
    
    if(format_folders.size() == 1)
    {
        std::string f1 = "/" + format_folders[0] + "/";

        _folders[0]->ListFile(f1, "");
        _folders[1]->ListFile("", "");
        _folders[2]->ListFile("", "");
    }
    else if(format_folders.size() == 2)
    {
        std::string f1 = "/" + format_folders[0] + "/";
        std::string f2 = f1 + format_folders[1] + "/";
        axPrint(f1, f2);
        
        _folders[0]->ListFile(f1, format_folders[1]);
        _folders[1]->ListFile(f2, "");
        _folders[2]->ListFile("", "");
    }
    else if(format_folders.size() == 3)
    {
        std::string f1 = "/" + format_folders[0] + "/";
        std::string f2 = f1 + format_folders[1] + "/";
        std::string f3 = f2 + format_folders[2] + "/";
        
        _folders[0]->ListFile(f1, format_folders[1]);
        _folders[1]->ListFile(f2, format_folders[2]);
        _folders[2]->ListFile(f3, "");
    }
    else if(format_folders.size() > 3)
    {
        std::size_t last_index = format_folders.size() - 1;
        
        std::string pre_folder = "";
        
        for(int i = 0; i < last_index - 2; i++)
        {
            pre_folder += "/" + format_folders[i];
        }
        
        std::string f1 = pre_folder + "/" + format_folders[last_index - 2] + "/";
        std::string f2 = f1 + format_folders[last_index - 1] + "/";
        std::string f3 = f2 + format_folders[last_index] + "/";
        
        _folders[0]->ListFile(f1, format_folders[last_index - 1]);
        _folders[1]->ListFile(f2, format_folders[last_index]);
        _folders[2]->ListFile(f3, "");
    }
}

//void FileBrowser::SetSSHHandle(axSSH* ssh)
//{
//    _ssh = ssh;
//    
//    for(auto& n : _folders)
//    {
//        n->SetSSHHandle(ssh);
//    }
//    
//    Update();
//}

void FileBrowser::OnPaint()
{
    axGC* gc = GetGC();
    axRect rect(GetRect());
    axRect rect0(axPoint(0, 0), rect.size);
    
    gc->SetColor(axColor(0.93));
    gc->DrawRectangle(rect0);
}