// mod_fps.h : main header file for the mod_fps DLL
//

extern HWND hTibiaWnd;
extern DWORD addrFps;


#if !defined(AFX_mod_light_H__D1220A19_D7FC_4B51_900D_224C2CAC1CB8__INCLUDED_)
#define AFX_mod_light_H__D1220A19_D7FC_4B51_900D_224C2CAC1CB8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols
#include <IModuleInterface.h>
#include "ConfigDialog.h"

/////////////////////////////////////////////////////////////////////////////
// Cmod_fpsApp
// See mod_fps.cpp for the implementation of this class
//

class Cmod_fpsApp : public CWinApp, public IModuleInterface
{
public:
	Cmod_fpsApp();
	~Cmod_fpsApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Cmod_lightApp)
	//}}AFX_VIRTUAL

	//{{AFX_MSG(Cmod_lightApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:		
	void getNewSkin(CSkin);
	int validateConfig(int showAlerts);
	// functions from IModuleInterface
	char * getName();
	int isStarted();
	void start();
	void stop();
	void showConfigDialog();
	void configToControls();
	void controlsToConfig();
	void disableControls();
	void enableControls();		
	char *getVersion();
	void resetConfig();
	void loadConfigParam(char *paramName,char *paramValue);
	char *saveConfigParam(char *paramName);
	char *getConfigParamName(int nr);
private:	
	int m_started;
	CConfigDialog * m_configDialog;
	CConfigData *m_configData;
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_mod_light_H__D1220A19_D7FC_4B51_900D_224C2CAC1CB8__INCLUDED_)
