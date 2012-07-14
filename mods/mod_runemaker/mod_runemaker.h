// mod_runemaker.h : main header file for the MOD_RUNEMAKER DLL
//

#if !defined(AFX_MOD_RUNEMAKER_H__D1220A19_D7FC_4B51_900D_224C2CAC1CB8__INCLUDED_)
#define AFX_MOD_RUNEMAKER_H__D1220A19_D7FC_4B51_900D_224C2CAC1CB8__INCLUDED_

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
// CMod_runemakerApp
// See mod_runemaker.cpp for the implementation of this class
//

class CMod_runemakerApp : public CWinApp, public IModuleInterface
{
public:
	CMod_runemakerApp();
	~CMod_runemakerApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMod_runemakerApp)
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CMod_runemakerApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:		
	void getNewSkin(CSkin);
	void resetMultiParamAccess(char *paramName);
	int isMultiParam(char *paramName);
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
	void makeNow(int enable);
	char *getVersion();
	void resetConfig();
	void loadConfigParam(char *paramName,char *paramValue);
	char *saveConfigParam(char *paramName);
	char *getConfigParamName(int nr);
private:	
	int m_started;
	CConfigDialog * m_configDialog;
	CConfigData *m_configData;
	int m_currentSpellNr;
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MOD_RUNEMAKER_H__D1220A19_D7FC_4B51_900D_224C2CAC1CB8__INCLUDED_)
