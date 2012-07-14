// mod_team.h : main header file for the MOD_TEAM DLL
//

#if !defined(AFX_MOD_TEAM_H__D1220A19_D7FC_4B51_900D_224C2CAC1CB8__INCLUDED_)
#define AFX_MOD_TEAM_H__D1220A19_D7FC_4B51_900D_224C2CAC1CB8__INCLUDED_

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
// CMod_teamApp
// See mod_team.cpp for the implementation of this class
//

class CMod_teamApp : public CWinApp, public IModuleInterface
{
public:
	CMod_teamApp();
	~CMod_teamApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMod_teamApp)
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CMod_teamApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:		
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

#endif // !defined(AFX_MOD_TEAM_H__D1220A19_D7FC_4B51_900D_224C2CAC1CB8__INCLUDED_)
