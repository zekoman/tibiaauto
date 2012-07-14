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


// mod_login.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include "mod_login.h"

#include "ConfigDialog.h"
#include "ConfigData.h"
#include "TibiaContainer.h"
#include "MemConstData.h"

#include "MemReaderProxy.h"
#include "PackSenderProxy.h"
#include "TibiaItemProxy.h"
#include "SendKeys.h"
#include <queue>
#include <time.h>
#include "ModuleUtil.h"
using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


int loginTime=0;
/////////////////////////////////////////////////////////////////////////////
// CMod_loginApp

BEGIN_MESSAGE_MAP(CMod_loginApp, CWinApp)
	//{{AFX_MSG_MAP(CMod_loginApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


extern CRITICAL_SECTION QueueCriticalSection;
extern std::queue<char *> queue2;

/////////////////////////////////////////////////////////////////////////////
// Tool thread function

int toolThreadShouldStop=0;
HANDLE toolThreadHandle;

void registerDebug(char *msg)
{
	if (QueueCriticalSection.OwningThread!=0){
		char *newMsg = (char *)malloc(strlen(msg)+1);
		sprintf(newMsg,"%s",msg);
		EnterCriticalSection(&QueueCriticalSection);
		queue2.push(newMsg);
		LeaveCriticalSection(&QueueCriticalSection);
	}
}

// wait on "Please wait" and "" windows up to 60 seconds
int waitOnConnecting()
{
	CMemReaderProxy reader;
	int i;
	registerDebug("Waiting on 'Connecting' window up to 10 seconds");
	for (i=0;i<100;i++)
	{		
		if (strcmp(reader.getOpenWindowName(),"Connecting")!=0) return 0;
		Sleep(100);
		if (toolThreadShouldStop) return 1;
	}
	registerDebug("WARN: Waiting on 'Connecting' window failed");
	return 1;
}

int waitForWindow(char *name, int secs=10, int doEsc=0)
{
	CMemReaderProxy reader;
	CSendKeys sk;
	int i;

	char buf[128];
	sprintf(buf,"Waiting for window '%s' up to %d seconds",name,secs);
	registerDebug(buf);
	for (i=0;i<secs*10;i++)
	{
		if (strcmp(reader.getOpenWindowName(),name)) 
		{
			if (doEsc) sk.SendKeys("{ESC}",true);
			Sleep(100);
		} else {			
			return 0;
		}
		if (toolThreadShouldStop) return 1;
	}
	registerDebug("WARN: Waiting for window failed");
	return 1;
}

HWND tibiaWindowHwnd=0;
BOOL CALLBACK EnumWindowsProcTibiaWindow(      

    HWND hwnd,
    LPARAM lParam
	)
{
	DWORD procId;
	GetWindowThreadProcessId(hwnd,&procId);
	if (lParam==procId)
	{
		tibiaWindowHwnd=hwnd;
		return 0;
	}
	return 1;
}

HWND getTibiaWindow(int procId)
{
	tibiaWindowHwnd=0;
	EnumWindows(&EnumWindowsProcTibiaWindow,(long)procId);
	return tibiaWindowHwnd;
}

int ensureForeground(HWND hwnd)
{
	CRect rect;
	GetWindowRect(hwnd,rect);
	SetWindowPos(hwnd,HWND_TOP, rect.left, rect.top, rect.Width(),  rect.Height(), SWP_SHOWWINDOW);

		int i;
	if (::IsIconic(hwnd)) return 1;
	if (::GetForegroundWindow()==hwnd) return 0;
	//SPI_SETFOREGROUNDLOCKTIMEOUT prevents window from flashing and simply displays the window
	int timeout;
	::SystemParametersInfo(0x2000/*SPI_GETFOREGROUNDLOCKTIMEOUT*/, 0, &timeout, SPIF_SENDWININICHANGE | SPIF_UPDATEINIFILE);
	::SystemParametersInfo(0x2001/*SPI_SETFOREGROUNDLOCKTIMEOUT*/, 0, (LPVOID)0, SPIF_SENDWININICHANGE | SPIF_UPDATEINIFILE);
	::SetForegroundWindow(hwnd);
	::SystemParametersInfo(0x2001/*SPI_SETFOREGROUNDLOCKTIMEOUT*/, timeout, (LPVOID)0, SPIF_SENDWININICHANGE | SPIF_UPDATEINIFILE);

	for (i=0;i<100;i++)
	{						
		
		if (::GetForegroundWindow()==hwnd) break;						
		if (toolThreadShouldStop) break;
		Sleep(100);
	}
	if (i>=100) return 2;

	return 0;
}

int getSelfExp()
{
	CMemReaderProxy reader;
	CTibiaCharacter *self = reader.readSelfCharacter();
	int retExp=self->exp;
	delete self;	
	return retExp;
}

DWORD WINAPI toolThreadProc( LPVOID lpParam )
{	
	int i;
	CMemReaderProxy reader;
	CPackSenderProxy sender;
	CTibiaItemProxy itemProxy;
	CMemConstData memConstData = reader.getMemConstData();
	CConfigData *config = (CConfigData *)lpParam;
	int origExp=getSelfExp();
	long prevCount;

	int shouldBeOpenedContainers=0;
	if (config->openMain) shouldBeOpenedContainers++;
	if (config->openCont1) shouldBeOpenedContainers++;
	if (config->openCont2) shouldBeOpenedContainers++;
	if (config->openCont3) shouldBeOpenedContainers++;
	if (config->openCont4) shouldBeOpenedContainers++;
	if (config->openCont5) shouldBeOpenedContainers++;
	if (config->openCont6) shouldBeOpenedContainers++;
	if (config->openCont7) shouldBeOpenedContainers++;
	if (config->openCont8) shouldBeOpenedContainers++;

	HANDLE hSemaphore = OpenSemaphore(SEMAPHORE_ALL_ACCESS,true,"TibiaAuto_modLogin_semaphore");
	if (hSemaphore==NULL)
	{
		hSemaphore = CreateSemaphore(NULL,1,1,"TibiaAuto_modLogin_semaphore");
	}

	while (!toolThreadShouldStop)
	{					
		Sleep(100);
		
		int connectionState = reader.getConnectionState();
		
		if (connectionState!=8)
		{	
			char buf[128];
			sprintf(buf,"Connection Status Changed to:%d",connectionState);
			registerDebug(buf);

			registerDebug("No connection: entering wait area");
			if (!loginTime) loginTime = time(NULL)+config->loginDelay;
			while (loginTime>time(NULL) && reader.getConnectionState()!=8){
				if (toolThreadShouldStop){
					registerDebug("Forced Exit. Module stopped.");
					goto exitFunction;
				}
				Sleep(500);
			}
		}
		connectionState = reader.getConnectionState();
		if (connectionState!=8)
		{	
			registerDebug("No connection: entering relogin mode");

			if (origExp>getSelfExp()) 
			{
				registerDebug("ERROR: exp dropped? was I killed?");
				Sleep(1000);
				while (reader.getConnectionState()!=8){
					if (toolThreadShouldStop){
						goto exitFunction;
					}
					Sleep(1000);
				}
				continue;
			}
			if (hSemaphore)
			{
				registerDebug("Waiting on global login semaphore");
			
				WaitForSingleObject(hSemaphore,INFINITE);
				registerDebug("Got on semaphore");
			}

			CRect wndRect;
			
			CSendKeys sk;
			HWND  hwnd=getTibiaWindow(reader.getProcessId());
			
			
			
			reader.setGlobalVariable("walking_control","login");
			reader.setGlobalVariable("walking_priority","10");

			int wndIconic=::IsIconic(hwnd);
			int wndMaximized=::IsZoomed(hwnd);
			int wndTrayed=!::IsWindowVisible(hwnd);
			if (wndTrayed){
				::ShowWindow(hwnd,SW_SHOW);
				// wait 5s for the window to show
				for (i=0;i<50;i++)
				{
					if (::IsWindowVisible(hwnd)) break;
					if (toolThreadShouldStop) break;
					Sleep(100);
				}
			}
			if (wndIconic || !wndMaximized)
			{	
				::ShowWindow(hwnd,SW_SHOWMAXIMIZED);
				
				// wait 5s for the window to restore
				for (i=0;i<50;i++)
				{
					if (!::IsIconic(hwnd) && wndIconic || ::IsZoomed(hwnd) && wndMaximized) break;
					if (toolThreadShouldStop) break;
					Sleep(100);
				}
				if (::IsIconic(hwnd) && wndIconic || !::IsZoomed(hwnd) && wndMaximized) 
				{				
					registerDebug("ERROR: tibia window is still not maximized but it should be");
					ReleaseSemaphore(hSemaphore,1,&prevCount);
					continue;
				}
			}
			if (toolThreadShouldStop) 
			{
				ReleaseSemaphore(hSemaphore,1,&prevCount);
				continue;
			}

						
			
			POINT prevCursorPos;
			GetCursorPos(&prevCursorPos);
						
			if (ensureForeground(hwnd)) 
			{
				ReleaseSemaphore(hSemaphore,1,&prevCount);
				continue;
			}
			if (toolThreadShouldStop) 
			{
				ReleaseSemaphore(hSemaphore,1,&prevCount);
				continue;			
			}
			
		
			
			::GetWindowRect(hwnd,&wndRect);
			
			
			
			// STEP0: make sure no window is open
			waitForWindow("",2,1);
			
			// STEP1: show login window
			if (ensureForeground(hwnd)) 
			{
				ReleaseSemaphore(hSemaphore,1,&prevCount);
				continue;
			}
			SetCursorPos(wndRect.left+125,wndRect.bottom-223);
			mouse_event(MOUSEEVENTF_LEFTDOWN,0,0,0,0);
			mouse_event(MOUSEEVENTF_LEFTUP,0,0,0,0);
			if (waitOnConnecting() || waitForWindow("Enter Game",5) || ensureForeground(hwnd))
			{
				ReleaseSemaphore(hSemaphore,1,&prevCount);
				continue;
			}
			
			// STEP2: enter user and pass
			char accNum[33];
			char pass[33];
			accNum[32]=0;
			pass[32]=0;
			if (config->autopass){
				CTibiaItemProxy itemProxy;
				int addr=itemProxy.getValueForConst("addrConnectionState");
				reader.getMemRange(addr-0x24,addr-0x24+32,accNum);
				reader.getMemRange(addr-0x44,addr-0x44+32,pass);
			} else {
				strncpy(accNum,config->accountNumber,32);
				strncpy(pass,config->password,32);
			}
			sk.SendKeys(accNum,true);
			SetCursorPos(wndRect.left+(wndRect.right-wndRect.left)/2+50,wndRect.top+(wndRect.bottom-wndRect.top)/2-15);
			mouse_event(MOUSEEVENTF_LEFTDOWN,0,0,0,0);
			mouse_event(MOUSEEVENTF_LEFTUP,0,0,0,0);
			sk.SendKeys(pass,true);
			SetCursorPos(wndRect.left+(wndRect.right-wndRect.left)/2+50-20,wndRect.top+(wndRect.bottom-wndRect.top)/2-15+90);
			mouse_event(MOUSEEVENTF_LEFTDOWN,0,0,0,0);
			mouse_event(MOUSEEVENTF_LEFTUP,0,0,0,0);
			waitOnConnecting();
			if (waitForWindow("Select Character",2) && !waitForWindow("Message of the Day",5))
				sk.SendKeys("~",true);

			
			// STEP3: select char
			if (waitForWindow("Select Character",5) || ensureForeground(hwnd)) 
			{
				ReleaseSemaphore(hSemaphore,1,&prevCount);
				continue;
			}

			if (!config->autopass){
				sk.SendKeys("a");// goes to beginning of list
				for (int i=1;i<config->charPos;i++){
					sk.SendKeys("{DOWN}");
				}
			}
			SetCursorPos(wndRect.left+(wndRect.right-wndRect.left)/2+50-20,wndRect.top+(wndRect.bottom-wndRect.top)/2-15-70+217);				
			mouse_event(MOUSEEVENTF_LEFTDOWN,0,0,0,0);
			mouse_event(MOUSEEVENTF_LEFTUP,0,0,0,0);
			
			registerDebug("Waiting fo establishing connection up to 15s");
			for (i=0;i<150;i++)
			{
				if (reader.getConnectionState()==8) break;
				if (toolThreadShouldStop) break;
				Sleep(100);
			}
			//SetCursorPos(prevCursorPos.x,prevCursorPos.y);

			//Click on the X of Possibly open skills/battle windows
			for (i=0;i<4;i++){
				SetCursorPos(wndRect.right-15,wndRect.top+387);//inventory maximized
				mouse_event(MOUSEEVENTF_LEFTDOWN,0,0,0,0);
				mouse_event(MOUSEEVENTF_LEFTUP,0,0,0,0);			
				SetCursorPos(wndRect.right-15,wndRect.top+382);//inventory minimized
				mouse_event(MOUSEEVENTF_LEFTDOWN,0,0,0,0);
				mouse_event(MOUSEEVENTF_LEFTUP,0,0,0,0);
				Sleep(100);
			}
			// finalize
			if (reader.getConnectionState()==8&&config->openMain) {	
				
				// open the main backpack flow

				//Comemnted out checking number of backpacks open.  Assume infalliability.
				//This portion is not needed and has caused problems regarding closing already opened backpacks and never reopening them
				/*
				int openContainersCount=0;
				for (i=0;i<7;i++)
				{
					CTibiaContainer *cont = reader.readContainer(i);
					if (cont->flagOnOff) openContainersCount++;
					delete cont;
				}
				if (openContainersCount!=shouldBeOpenedContainers)
				{
					int pos;
					// no open containers found; proceed.
					// first: close existing containers
					for (pos=0;pos<memConstData.m_memMaxContainers;pos++)
					{
						CTibiaContainer *cont = reader.readContainer(pos);
						if (cont->flagOnOff)
						{
							sender.closeContainer(pos);
							CModuleUtil::waitForOpenContainer(pos,0);
						}

						delete cont;
					}
					*/
				// now open containers
				
				CTibiaItem *item = reader.readItem(itemProxy.getValueForConst("addrBackpack"));
				sender.openContainerFromContainer(item->objectId,0x03,0,0);
				delete item;
				CModuleUtil::waitForOpenContainer(0,1);

				//Double click on the main bar of the container
				SetCursorPos(wndRect.right-100,wndRect.top+387);
				mouse_event(MOUSEEVENTF_LEFTDOWN,0,0,0,0);
				mouse_event(MOUSEEVENTF_LEFTUP,0,0,0,0);			
				mouse_event(MOUSEEVENTF_LEFTDOWN,0,0,0,0);
				mouse_event(MOUSEEVENTF_LEFTUP,0,0,0,0);			
				SetCursorPos(wndRect.right-100,wndRect.top+282);
				mouse_event(MOUSEEVENTF_LEFTDOWN,0,0,0,0);
				mouse_event(MOUSEEVENTF_LEFTUP,0,0,0,0);			
				mouse_event(MOUSEEVENTF_LEFTDOWN,0,0,0,0);
				mouse_event(MOUSEEVENTF_LEFTUP,0,0,0,0);

				CTibiaContainer *cont = reader.readContainer(0);
				if (cont->flagOnOff)
				{
					int foundContNr=1;
					int foundContOpenNr=1;
					for (int pos=0;pos<cont->itemsInside;pos++)
					{
						CTibiaItem *itemInside = (CTibiaItem *)cont->items.GetAt(pos);
						CTibiaTile *itemTile = reader.getTibiaTile(itemInside->objectId);
						if (itemTile->isContainer)
						{
							int doOpen=0;
							if (foundContNr==1&&config->openCont1) doOpen=1;
							if (foundContNr==2&&config->openCont2) doOpen=1;
							if (foundContNr==3&&config->openCont3) doOpen=1;
							if (foundContNr==4&&config->openCont4) doOpen=1;
							if (foundContNr==5&&config->openCont5) doOpen=1;
							if (foundContNr==6&&config->openCont6) doOpen=1;
							if (foundContNr==7&&config->openCont7) doOpen=1;
							if (foundContNr==8&&config->openCont8) doOpen=1;
							if (doOpen)
							{
								sender.openContainerFromContainer(itemInside->objectId,0x40,pos,foundContOpenNr);
								CModuleUtil::waitForOpenContainer(foundContOpenNr,1);

								//Double click on main bar of open container(each container heign =19
								SetCursorPos(wndRect.right-100,wndRect.top+387+19*foundContOpenNr);
								mouse_event(MOUSEEVENTF_LEFTDOWN,0,0,0,0);
								mouse_event(MOUSEEVENTF_LEFTUP,0,0,0,0);			
								mouse_event(MOUSEEVENTF_LEFTDOWN,0,0,0,0);
								mouse_event(MOUSEEVENTF_LEFTUP,0,0,0,0);			
								SetCursorPos(wndRect.right-100,wndRect.top+282+19*foundContOpenNr);
								mouse_event(MOUSEEVENTF_LEFTDOWN,0,0,0,0);
								mouse_event(MOUSEEVENTF_LEFTUP,0,0,0,0);			
								mouse_event(MOUSEEVENTF_LEFTDOWN,0,0,0,0);
								mouse_event(MOUSEEVENTF_LEFTUP,0,0,0,0);			
								
								foundContOpenNr++;
							}
							foundContNr++;
						}
					}
				} else {
					// something went wrong
					sender.closeContainer(0);
				}				
				delete cont;
				
				//}  Comemnted out checking number of backpacks open.
				
			}
			Sleep(100);//Wait for clicks to finish
			//reset window back to original state
			if (wndIconic)//prioritize wndIconic over !wndMaxmized
			{
				::ShowWindow(hwnd,SW_MINIMIZE);
				// wait 5s for the window to minimize
				for (i=0;i<50;i++)
				{
					if (::IsIconic(hwnd)) break;
					if (toolThreadShouldStop) break;
					Sleep(100);
				}
			} else if (!wndMaximized){
				::ShowWindow(hwnd,SW_RESTORE);
				// wait 5s for the window to minimize
				for (i=0;i<50;i++)
				{
					if (!::IsZoomed(hwnd)) break;
					if (toolThreadShouldStop) break;
					Sleep(100);
				}
			}
			if (wndTrayed)
			{
				::ShowWindow(hwnd,SW_HIDE);
				// wait 5s for the window to minimize
				for (i=0;i<50;i++)
				{
					if (!::IsWindowVisible(hwnd)) break;
					if (toolThreadShouldStop) break;
					Sleep(100);
				}
			}
			SetCursorPos(prevCursorPos.x,prevCursorPos.y);
			ReleaseSemaphore(hSemaphore,1,&prevCount);
			registerDebug("Relogin procedure completed.");
			loginTime=0;
			reader.setGlobalVariable("walking_control","");
			reader.setGlobalVariable("walking_priority","0");

		} // if (connectionState!=8)
		else loginTime=0;
	}
exitFunction:
	if (hSemaphore)
	{
		CloseHandle(hSemaphore);
	}
	toolThreadShouldStop=0;
	loginTime=0;
	return 0;
}


/////////////////////////////////////////////////////////////////////////////
// CMod_loginApp construction

CMod_loginApp::CMod_loginApp()
{
	m_configDialog =NULL;
	m_started=0;
	m_configData = new CConfigData();	
}

CMod_loginApp::~CMod_loginApp()
{
	if (m_configDialog)
	{
		delete m_configDialog;
	}
	delete m_configData;	
}

char * CMod_loginApp::getName()
{
	return "Auto relogin";
}


int CMod_loginApp::isStarted()
{
	return m_started;
}


void CMod_loginApp::start()
{	
	superStart();
	if (m_configDialog)
	{
		m_configDialog->disableControls();
		m_configDialog->activateEnableButton(true);
	}

	DWORD threadId;
		
	toolThreadShouldStop=0;
	toolThreadHandle =  ::CreateThread(NULL,0,toolThreadProc,m_configData,0,&threadId);				
	m_started=1;
}

void CMod_loginApp::stop()
{
	toolThreadShouldStop=1;
	while (toolThreadShouldStop) {
		Sleep(50);
	};
	m_started=0;
	
	if (m_configDialog)
	{
		m_configDialog->enableControls();
		m_configDialog->activateEnableButton(false);
	}
} 

void CMod_loginApp::showConfigDialog()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());	

	if (!m_configDialog)
	{
		m_configDialog = new CConfigDialog(this);
		m_configDialog->Create(IDD_CONFIG);
		configToControls();
		if (m_started) disableControls();
		else enableControls();
		m_configDialog->m_enable.SetCheck(m_started);
	}
	m_configDialog->ShowWindow(SW_SHOW);
}


void CMod_loginApp::configToControls()
{
	if (m_configDialog)
	{		
		
		m_configDialog->configToControls(m_configData);
	}
}


void CMod_loginApp::controlsToConfig()
{
	if (m_configDialog)
	{
		delete m_configData;
		m_configData = m_configDialog->controlsToConfig();
	}
}


void CMod_loginApp::disableControls()
{
	if (m_configDialog)
	{
		m_configDialog->disableControls();
	}
}

void CMod_loginApp::enableControls()
{
	if (m_configDialog)
	{
		m_configDialog->enableControls();
	}
}


char *CMod_loginApp::getVersion()
{
	return "1.0";
}


int CMod_loginApp::validateConfig(int showAlerts)
{
	if (!m_configData->autopass && strlen(m_configData->accountNumber)==0)
	{
		if (showAlerts) AfxMessageBox("Account number must be filled in!");
		return 0;
	}
	if (!m_configData->autopass && strlen(m_configData->password)==0)
	{
		if (showAlerts) AfxMessageBox("Password must be filled in!");
		return 0;
	}
	if (!m_configData->autopass && (m_configData->charPos<=0||m_configData->charPos>20))
	{
		if (showAlerts) AfxMessageBox("Character position must be between 1 and 20.");
		return 0;
	}
	if (m_configData->openCont1||m_configData->openCont2||m_configData->openCont3||m_configData->openCont4
		||m_configData->openCont5||m_configData->openCont6||m_configData->openCont7||m_configData->openCont8)
	{
		if (!m_configData->openMain)
		{
			if (showAlerts) AfxMessageBox("If you choose to open container, you must also choose to open the main backpack!");
			return 0;
		}
	}
	if (m_configData->loginDelay<0)
	{
		if (showAlerts) AfxMessageBox("Login delay must not be less than 0.");
		return 0;
	}
	
	
	return 1;
}

void CMod_loginApp::resetConfig()
{
	m_configData = new CConfigData();
}

void CMod_loginApp::loadConfigParam(char *paramName,char *paramValue)
{
	if (!strcmp(paramName,"open/main")) m_configData->openMain=atoi(paramValue);
	if (!strcmp(paramName,"open/cont1")) m_configData->openCont1=atoi(paramValue);
	if (!strcmp(paramName,"open/cont2")) m_configData->openCont2=atoi(paramValue);
	if (!strcmp(paramName,"open/cont3")) m_configData->openCont3=atoi(paramValue);
	if (!strcmp(paramName,"open/cont4")) m_configData->openCont4=atoi(paramValue);
	if (!strcmp(paramName,"open/cont5")) m_configData->openCont5=atoi(paramValue);
	if (!strcmp(paramName,"open/cont6")) m_configData->openCont6=atoi(paramValue);
	if (!strcmp(paramName,"open/cont7")) m_configData->openCont7=atoi(paramValue);
	if (!strcmp(paramName,"open/cont8")) m_configData->openCont8=atoi(paramValue);
	if (!strcmp(paramName,"loginDelay")) m_configData->loginDelay=atoi(paramValue);
	if (!strcmp(paramName,"autopass")) m_configData->autopass=atoi(paramValue);
	if (!strcmp(paramName,"accountname")) strncpy(m_configData->accountNumber,paramValue,64);
	if (!strcmp(paramName,"accountpass")) strncpy(m_configData->password,paramValue,64);
}

char *CMod_loginApp::saveConfigParam(char *paramName)
{
	static char buf[1024];
	buf[0]=0;
	
	if (!strcmp(paramName,"open/main")) sprintf(buf,"%d",m_configData->openMain);
	if (!strcmp(paramName,"open/cont1")) sprintf(buf,"%d",m_configData->openCont1);
	if (!strcmp(paramName,"open/cont2")) sprintf(buf,"%d",m_configData->openCont2);
	if (!strcmp(paramName,"open/cont3")) sprintf(buf,"%d",m_configData->openCont3);
	if (!strcmp(paramName,"open/cont4")) sprintf(buf,"%d",m_configData->openCont4);
	if (!strcmp(paramName,"open/cont5")) sprintf(buf,"%d",m_configData->openCont5);
	if (!strcmp(paramName,"open/cont6")) sprintf(buf,"%d",m_configData->openCont6);
	if (!strcmp(paramName,"open/cont7")) sprintf(buf,"%d",m_configData->openCont7);
	if (!strcmp(paramName,"open/cont8")) sprintf(buf,"%d",m_configData->openCont8);
	if (!strcmp(paramName,"loginDelay")) sprintf(buf,"%d",m_configData->loginDelay);
	if (!strcmp(paramName,"autopass")) sprintf(buf,"%d",m_configData->autopass);
	if (!strcmp(paramName,"accountname")) sprintf(buf,"***censored***");
	if (!strcmp(paramName,"accountpass")) sprintf(buf,"***censored***");

	return buf;
}

char *CMod_loginApp::getConfigParamName(int nr)
{
	switch (nr)
	{
	case 0: return "open/main";
	case 1: return "open/cont1";
	case 2: return "open/cont2";
	case 3: return "open/cont3";
	case 4: return "open/cont4";
	case 5: return "open/cont5";
	case 6: return "open/cont6";
	case 7: return "open/cont7";
	case 8: return "open/cont8";
	case 9: return "loginDelay";
	case 10: return "autopass";
	case 11: return "accountname";
	case 12: return "accountpass";
	default:
		return NULL;
	}
}

void CMod_loginApp::getNewSkin(CSkin newSkin) {
	skin = newSkin;
	skin.SetButtonSkin(	m_configDialog->m_enable);
	skin.SetButtonSkin(	m_configDialog->m_OK);

	AFX_MANAGE_STATE(AfxGetStaticModuleState());			
	if (m_configDialog)
		m_configDialog->Invalidate();
}
