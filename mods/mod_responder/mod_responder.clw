; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CToolAutoRespond
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "mod_responder.h"
LastPage=0

ClassCount=2
Class1=CMod_responderApp
Class2=CToolAutoRespond

ResourceCount=2
Resource1=IDR_SHOWMAP_MENU (Polish)
Resource2=IDD_TOOL_AUTORESPOND (Polish)

[CLS:CMod_responderApp]
Type=0
BaseClass=CWinApp
HeaderFile=mod_responder.h
ImplementationFile=mod_responder.cpp
LastObject=IDC_AUTORESPOND_MSGHISTORY

[CLS:CToolAutoRespond]
Type=0
BaseClass=CDialog
HeaderFile=ToolAutoRespond.h
ImplementationFile=ToolAutoRespond.cpp
Filter=D
VirtualFilter=dWC
LastObject=IDC_AUTORESPOND_ENABLE

[DLG:IDD_TOOL_AUTORESPOND]
Type=1
Class=CToolAutoRespond

[MNU:IDR_SHOWMAP_MENU (Polish)]
Type=1
Class=?
Command1=ID_SHOWMAPOPTIONS_CLEAR
Command2=ID_SHOWMAPOPTIONS_AVAILABLE
Command3=ID_SHOWMAPOPTIONS_UP
Command4=ID_SHOWMAPOPTIONS_DOWN
CommandCount=4

[DLG:IDD_TOOL_AUTORESPOND (Polish)]
Type=1
Class=?
ControlCount=13
Control1=IDC_FRAME_RESPONDER_LOGS,button,1342177287
Control2=IDOK,button,1342242817
Control3=IDC_AUTORESPOND_MSGHISTORY,SysListView32,1350631429
Control4=IDC_AUTORESPOND_ACTIONLOG,SysListView32,1350631429
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352
Control7=IDC_AUTORESPOND_ENABLE,button,1342246915
Control8=IDC_AUTORESPOND_SCRIPT,edit,1353779396
Control9=IDC_AUTORESPOND_CLEAR,button,1342242816
Control10=IDC_AUTORESPOND_THREADSTATUS,SysListView32,1350631429
Control11=IDC_STATIC,static,1342308352
Control12=IDC_AUTORESPOND_ENABLEDEBUG,button,1342242819
Control13=IDC_AUTORESPOND_LOCALECHO,button,1342242819

