# Microsoft Developer Studio Project File - Name="mod_autogo" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=mod_autogo - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "mod_autogo.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "mod_autogo.mak" CFG="mod_autogo - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "mod_autogo - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "mod_autogo - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName "mod_autogo"
# PROP Scc_LocalPath "."
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "mod_autogo - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /I "..\..\sdk" /I "E:\Program Files\Microsoft Visual Studio 8\PlatformSDK\Include" /I "C:\Documents and Settings\Owner\My Documents\Xerces\xerces-c-src_2_8_0\src" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x415 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x415 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 WINMM.LIB xerces.lib /nologo /subsystem:windows /dll /machine:I386 /out:"../mod_autogo.dll" /libpath:"C:\Documents and Settings\Owner\My Documents\TibiaAuto\tibiaauto-kernel" /libpath:"e:\projects\tibiaauto-pub"
# SUBTRACT LINK32 /nodefaultlib

!ELSEIF  "$(CFG)" == "mod_autogo - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\..\sdk" /I "E:\Program Files\Microsoft Visual Studio 8\PlatformSDK\Include" /D "WINVER 0x600" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x415 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x415 /i "C:\Documents and Settings\Owner\Desktop\xercesc\xerces-c-src_2_8_0\src" /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 WINMM.LIB /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "mod_autogo - Win32 Release"
# Name "mod_autogo - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\Alarm.cpp
# End Source File
# Begin Source File

SOURCE=.\alarmdialog.cpp
# End Source File
# Begin Source File

SOURCE=..\..\sdk\BtnST.cpp
# End Source File
# Begin Source File

SOURCE=..\..\sdk\ComboBoxSuper.cpp
# End Source File
# Begin Source File

SOURCE=.\ConfigData.cpp
# End Source File
# Begin Source File

SOURCE=.\ConfigDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\CustomSpellDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\exports.cpp
# End Source File
# Begin Source File

SOURCE=.\GeneralConfigDialog.cpp
# End Source File
# Begin Source File

SOURCE=..\..\sdk\GroupBoxEx.cpp
# End Source File
# Begin Source File

SOURCE=.\ImageButtonWithStyle.cpp
# End Source File
# Begin Source File

SOURCE=.\mod_autogo.cpp
# End Source File
# Begin Source File

SOURCE=.\mod_autogo.def
# End Source File
# Begin Source File

SOURCE=.\mod_autogo.rc
# End Source File
# Begin Source File

SOURCE=..\..\sdk\MyDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\proxy.cpp
# End Source File
# Begin Source File

SOURCE=..\..\sdk\Skin.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\TibiaItem_impl.cpp
# End Source File
# Begin Source File

SOURCE=.\Trigger.cpp
# End Source File
# Begin Source File

SOURCE=.\VisualStylesXP.cpp
# End Source File
# Begin Source File

SOURCE=.\WhiteList.cpp
# End Source File
# Begin Source File

SOURCE=..\..\sdk\XTabCtrl.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\Alarm.h
# End Source File
# Begin Source File

SOURCE=.\alarmdialog.h
# End Source File
# Begin Source File

SOURCE=..\..\sdk\ComboBoxSuper.h
# End Source File
# Begin Source File

SOURCE=.\ConfigData.h
# End Source File
# Begin Source File

SOURCE=.\ConfigDialog.h
# End Source File
# Begin Source File

SOURCE=.\CustomSpellDialog.h
# End Source File
# Begin Source File

SOURCE=.\Enumerations.h
# End Source File
# Begin Source File

SOURCE=.\GeneralConfigDialog.h
# End Source File
# Begin Source File

SOURCE=.\ImageButtonWithStyle.h
# End Source File
# Begin Source File

SOURCE=.\mod_autogo.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\tmschema.h
# End Source File
# Begin Source File

SOURCE=.\Trigger.h
# End Source File
# Begin Source File

SOURCE=.\uxtheme.h
# End Source File
# Begin Source File

SOURCE=.\VisualStylesXP.h
# End Source File
# Begin Source File

SOURCE=.\WhiteList.h
# End Source File
# Begin Source File

SOURCE=..\..\sdk\XTabCtrl.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\Attack.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Attack.bmp
# End Source File
# Begin Source File

SOURCE=.\Audio.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Audio.bmp
# End Source File
# Begin Source File

SOURCE=.\Blank.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Blank.bmp
# End Source File
# Begin Source File

SOURCE=.\CastSpell.bmp
# End Source File
# Begin Source File

SOURCE=.\res\CastSpell.bmp
# End Source File
# Begin Source File

SOURCE=.\Columns.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Columns.bmp
# End Source File
# Begin Source File

SOURCE=.\condition_burning.bmp
# End Source File
# Begin Source File

SOURCE=.\res\condition_burning.bmp
# End Source File
# Begin Source File

SOURCE=.\res\condition_electrified.bmp
# End Source File
# Begin Source File

SOURCE=.\res\condition_logoutblock.bmp
# End Source File
# Begin Source File

SOURCE=.\res\condition_poisoned.bmp
# End Source File
# Begin Source File

SOURCE=.\Depot.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Depot.bmp
# End Source File
# Begin Source File

SOURCE=.\general.bmp
# End Source File
# Begin Source File

SOURCE=.\res\general.bmp
# End Source File
# Begin Source File

SOURCE=.\Items.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Items.bmp
# End Source File
# Begin Source File

SOURCE=.\KillTibia.bmp
# End Source File
# Begin Source File

SOURCE=.\res\KillTibia.bmp
# End Source File
# Begin Source File

SOURCE=.\LogEvents.bmp
# End Source File
# Begin Source File

SOURCE=.\res\LogEvents.bmp
# End Source File
# Begin Source File

SOURCE=.\LogOut.bmp
# End Source File
# Begin Source File

SOURCE=.\res\LogOut.bmp
# End Source File
# Begin Source File

SOURCE=.\MaximizeWindow.bmp
# End Source File
# Begin Source File

SOURCE=.\res\MaximizeWindow.bmp
# End Source File
# Begin Source File

SOURCE=.\res\mod_autogo.rc2
# End Source File
# Begin Source File

SOURCE=.\proximity.bmp
# End Source File
# Begin Source File

SOURCE=.\res\proximity.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Runaway.bmp
# End Source File
# Begin Source File

SOURCE=.\Runaway.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ShutdownComputer.bmp
# End Source File
# Begin Source File

SOURCE=.\ShutdownComputer.bmp
# End Source File
# Begin Source File

SOURCE=.\res\skull_black.bmp
# End Source File
# Begin Source File

SOURCE=.\res\skull_green.bmp
# End Source File
# Begin Source File

SOURCE=.\res\skull_red.bmp
# End Source File
# Begin Source File

SOURCE=.\res\skull_white.bmp
# End Source File
# Begin Source File

SOURCE=.\res\skull_yellow.bmp
# End Source File
# Begin Source File

SOURCE=.\res\speaker.ico
# End Source File
# Begin Source File

SOURCE=.\res\speaker2.ico
# End Source File
# Begin Source File

SOURCE=.\res\Start.bmp
# End Source File
# Begin Source File

SOURCE=.\Start.bmp
# End Source File
# Begin Source File

SOURCE=.\res\StartModule.bmp
# End Source File
# Begin Source File

SOURCE=.\StartModule.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Stop.bmp
# End Source File
# Begin Source File

SOURCE=.\Stop.bmp
# End Source File
# Begin Source File

SOURCE=.\res\SuspendModule.bmp
# End Source File
# Begin Source File

SOURCE=.\SuspendModule.bmp
# End Source File
# Begin Source File

SOURCE=.\res\TakeScreenshot.bmp
# End Source File
# Begin Source File

SOURCE=.\TakeScreenshot.bmp
# End Source File
# Begin Source File

SOURCE=.\res\vip.bmp
# End Source File
# Begin Source File

SOURCE=.\vip.bmp
# End Source File
# End Group
# Begin Source File

SOURCE=.\sound\incorrec.wav
# End Source File
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
