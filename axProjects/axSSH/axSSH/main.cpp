#include "main.h"
#include "axSSH.h"
#include "FileBrowser.h"
#include "MenuBar.h"

MainPanel::MainPanel(axWindow* parent, const axRect& rect):
// Parent.
axPanel(parent, rect)
{
    _menuBar = new MenuBar(this, axRect(0, 0, rect.size.x, 40));
    _menuBar->Hide();
    
//    axApp* app = GetApp();
//    std::string btnInfoPath(app->GetResourceFile("axButtonBlueInfo.axobj"));
//    
//    _bgImg = new axImage("Untitled-2.png");
    
//    _connectionPanel = new axPanel(this, GetDrawingRect());
//    
//    axTextBox::Events txtEvents;
//    axTextBox::Info txtInfo;
//    txtInfo.normal = axColor(0.9, 0.9, 0.9);
//    txtInfo.hover = axColor(0.9, 0.9, 0.9);
//    txtInfo.selected = axColor(1.0, 1.0, 1.0);
//    txtInfo.highlight = axColor(0.4, 0.4, 0.6, 0.4);
//    txtInfo.contour = axColor(0.0, 0.0, 0.0);
//    txtInfo.cursor = axColor(1.0, 0.0, 0.0);
//    txtInfo.selected_shadow = axColor(0.8, 0.8, 0.8, 0.3);
//    
//    _ipTxtBox = new axTextBox(_connectionPanel,
//                              axRect(190, 224, 180, 25),
//                              txtEvents,
//                              txtInfo,
//                              "",
//                              "192.168.0.105",
//                              axTextBox::Flags::CONTOUR_HIGHLIGHT|
//                              axTextBox::Flags::FLASHING_CURSOR);
//    
//    _pwordtxtBox = new axTextBox(_connectionPanel,
//                                 axRect(190, 262, 180, 25),
//                                 txtEvents,
//                                 txtInfo,
//                                 "",
//                                 "swisshunter234",
//                                 axTextBox::Flags::CONTOUR_HIGHLIGHT|
//                                 axTextBox::Flags::FLASHING_CURSOR |
//                                 axTextBox::Flags::HIDDEN_TEXT);
//
//    axButton* btn = new axButton(_connectionPanel, axRect(251, 312, 60, 25),
//                                 axButton::Events(GetOnConnectButton()),
//                                 axButton::Info(btnInfoPath),
//                                 "",
//                                 "Connect");
    
    _fileBrowser = new FileBrowser(this ,
                                   axRect(0, 40, rect.size.x, rect.size.y - 40));
//    _fileBrowser->Hide();
}


//void MainPanel::OnConnectButton(const axButton::Msg& msg)
//{
//    _ssh = new axSSH();
//    
//    if(_ssh->Connect(_ipTxtBox->GetLabel(), _pwordtxtBox->GetLabel()))
//    {
//        axPrint("Connected");
//        _connectionPanel->Hide();
//        _fileBrowser->Show();
//        _menuBar->Show();
//        
//        _fileBrowser->SetSSHHandle(_ssh);
//        
//        _fileBrowser->ListFile("/usr/");
//    }
//}

void MainPanel::OnPaint()
{
    axGC* gc = GetGC();
    axRect rect(GetRect());
    axRect rect0(axPoint(0, 0), rect.size);
    
//    gc->DrawImage(_bgImg, axPoint(0, 0));
}

int main(int argc, char* argv[])
{
    axApp* app = axApp::CreateApp(axSize(550, 500));
    
    app->AddMainEntry([]()
                      {
                          MainPanel* mainPanel =
                                new MainPanel(nullptr, axRect(0, 0, 550, 500));
                      });
    
    app->MainLoop();
    return 0;
}