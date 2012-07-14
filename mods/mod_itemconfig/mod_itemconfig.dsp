# Microsoft Developer Studio Project File - Name="mod_itemconfig" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=mod_itemconfig - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "mod_itemconfig.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "mod_itemconfig.mak" CFG="mod_itemconfig - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "mod_itemconfig - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "mod_itemconfig - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "mod_itemconfig - Win32 Release"

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
# ADD CPP /nologo /MD /W3 /GX /O2 /I "..\..\sdk" /I "C:\Documents and Settings\Owner\My Documents\Xerces\xerces-c-src_2_8_0\src" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x415 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x415 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 xerces.lib /nologo /subsystem:windows /dll /machine:I386 /out:"../mod_itemconfig.dll" /libpath:"C:\Documents and Settings\Owner\My Documents\TibiaAuto\tibiaauto-kernel" /libpath:"e:\projects\tibiaauto-pub"
# SUBTRACT LINK32 /nodefaultlib

!ELSEIF  "$(CFG)" == "mod_itemconfig - Win32 Debug"

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
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\..\sdk" /D "WINVER 0x600" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x415 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x415 /i "C:\Documents and Settings\Owner\Desktop\xercesc\xerces-c-src_2_8_0\src" /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "mod_itemconfig - Win32 Release"
# Name "mod_itemconfig - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
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

SOURCE=.\exports.cpp
# End Source File
# Begin Source File

SOURCE=..\..\sdk\GroupBoxEx.cpp
# End Source File
# Begin Source File

SOURCE=.\ItemConfig.cpp
# End Source File
# Begin Source File

SOURCE=.\mod_itemconfig.cpp
# End Source File
# Begin Source File

SOURCE=.\mod_itemconfig.def
# End Source File
# Begin Source File

SOURCE=.\mod_itemconfig.rc
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

SOURCE=.\ToolItemConfig.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\ConfigData.h
# End Source File
# Begin Source File

SOURCE=..\..\sdk\GroupBoxEx.h
# End Source File
# Begin Source File

SOURCE=.\ItemConfig.h
# End Source File
# Begin Source File

SOURCE=.\mod_itemconfig.h
# End Source File
# Begin Source File

SOURCE=..\..\sdk\MyDialog.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=..\..\sdk\TibiaStructures.h
# End Source File
# Begin Source File

SOURCE=.\ToolItemConfig.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\bitmap1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00001.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00002.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00003.bmp
# End Source File
# Begin Source File

SOURCE=.\check.bmp
# End Source File
# Begin Source File

SOURCE=.\res\checks.bmp
# End Source File
# Begin Source File

SOURCE=.\halfchec.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Items.bmp
# End Source File
# Begin Source File

SOURCE=.\res\map_self.bmp
# End Source File
# Begin Source File

SOURCE=.\res\mod_itemconfig.rc2
# End Source File
# Begin Source File

SOURCE=.\uncheck.bmp
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
