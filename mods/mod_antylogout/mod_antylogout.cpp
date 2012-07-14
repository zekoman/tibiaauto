/*
This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA
*/


// mod_antylogout.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include "mod_antylogout.h"

#include "ConfigData.h"
#include "TibiaContainer.h"

#include "MemReaderProxy.h"
#include "PackSenderProxy.h"
#include "ModuleUtil.h"
#include "MemConstData.h"
#include "TibiaItemProxy.h"
#include "ModuleUtil.h"
#include <time.h>

#include "commons.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//
//	Note!
//
//		If this DLL is dynamically linked against the MFC
//		DLLs, any functions exported from this DLL which
//		call into MFC must have the AFX_MANAGE_STATE macro
//		added at the very beginning of the function.
//
//		For example:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// normal function body here
//		}
//
//		It is very important that this macro appear in each
//		function, prior to any calls into MFC.  This means that
//		it must appear as the first statement within the 
//		function, even before any object variable declarations
//		as their constructors may generate calls into the MFC
//		DLL.
//
//		Please see MFC Technical Notes 33 and 58 for additional
//		details.
//

/////////////////////////////////////////////////////////////////////////////
// CMod_antylogoutApp

BEGIN_MESSAGE_MAP(CMod_antylogoutApp, CWinApp)
	//{{AFX_MSG_MAP(CMod_antylogoutApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Tool functions

int RandomTimeAntylogout(){
	return CModuleUtil::randomFormula(300,200);
}

/////////////////////////////////////////////////////////////////////////////
// Tool thread function

int toolThreadShouldStop=0;
HANDLE toolThreadHandle;



DWORD WINAPI toolThreadProc( LPVOID lpParam )
{			
	CMemReaderProxy reader;
	CPackSenderProxy sender;
	CConfigData *config = (CConfigData *)lpParam;
	int iter=0;
	int randomSeconds=RandomTimeAntylogout();
	
	while (!toolThreadShouldStop)
	{					
		Sleep(1000);
		if (reader.getConnectionState()!=8) continue; // do not proceed if not connected

		iter++;

		if (iter%(randomSeconds)==1){
			randomSeconds=RandomTimeAntylogout();

			CTibiaCharacter *self = reader.readSelfCharacter();
//			sender.ignoreLook(time(NULL)+1);
//			sender.look(self->x+rand()%15-7,self->y+rand()%11-5,self->z,0);

			
			if (self->lookDirection==0){
				sender.turnUp();
			}else if(self->lookDirection==1){
				sender.turnRight();
			}else if(self->lookDirection==2){				
				sender.turnDown();
			}else if(self->lookDirection==3){
				sender.turnLeft();
			}
			delete self;
		}
		
	}	

	toolThreadShouldStop=0;
	return 0;
}


/////////////////////////////////////////////////////////////////////////////
// CMod_antylogoutApp construction

CMod_antylogoutApp::CMod_antylogoutApp()
{	
	m_started=0;	
}

CMod_antylogoutApp::~CMod_antylogoutApp()
{
	
	delete m_configData;	
}

char * CMod_antylogoutApp::getName()
{
	return "Anty logout";
}


int CMod_antylogoutApp::isStarted()
{
	return m_started;
}

 
void CMod_antylogoutApp::start()
{	
	superStart();
	DWORD threadId;
		
	toolThreadShouldStop=0;
	toolThreadHandle =  ::CreateThread(NULL,0,toolThreadProc,m_configData,0,&threadId);				
	m_started=1;
}

void CMod_antylogoutApp::stop()
{
	toolThreadShouldStop=1;
	while (toolThreadShouldStop) {
		Sleep(50);
	};
	m_started=0;		
} 


char *CMod_antylogoutApp::getVersion()
{
	return "1.1";
}


