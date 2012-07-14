#if !defined(AFX_CONFIGDIALOG_H__A38E1144_4FC4_4130_9D8B_A22DE0571AB2__INCLUDED_)
#define AFX_CONFIGDIALOG_H__A38E1144_4FC4_4130_9D8B_A22DE0571AB2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ConfigDialog.h : header file
//

#include "mod_cavebot.h"
#include "ConfigData.h"
#include "MyDialog.h"
#include "GroupBoxEx.h"
#include "BtnST.h"
#include <queue>
using namespace std;

class CMod_cavebotApp;


enum CToolAutoAttackStateAttack
{
	CToolAutoAttackStateAttack_notRunning,
	CToolAutoAttackStateAttack_macroPause,
	CToolAutoAttackStateAttack_attackingAlienFound,
	CToolAutoAttackStateAttack_attackingCreature,
};

enum CToolAutoAttackStateLoot
{
	CToolAutoAttackStateLoot_notRunning,
	CToolAutoAttackStateLoot_macroPause,
	CToolAutoAttackStateLoot_opening,
	CToolAutoAttackStateLoot_moveing,
	CToolAutoAttackStateLoot_closing,
	CToolAutoAttackStateLoot_openingBag,
};


enum CToolAutoAttackStateWalker
{
	CToolAutoAttackStateWalker_notRunning,
	CToolAutoAttackStateWalker_macroPause,		
	CToolAutoAttackStateWalker_noWaypoints,
	CToolAutoAttackStateWalker_ok,
	CToolAutoAttackStateWalker_noPathFound,
	CToolAutoAttackStateWalker_standing,
	CToolAutoAttackStateWalker_halfSleep,
	CToolAutoAttackStateWalker_fullSleep
};

enum CToolAutoAttackStateDepot
{
	CToolAutoAttackStateDepot_notRunning,
	CToolAutoAttackStateDepot_macroPause,
	CToolAutoAttackStateDepot_notFound,
	CToolAutoAttackStateDepot_noSpace,
	CToolAutoAttackStateDepot_walking,
	CToolAutoAttackStateDepot_opening,
	CToolAutoAttackStateDepot_depositing
};

enum CToolAutoAttackStateTraining
{
	CToolAutoAttackStateTraining_notRunning,
	CToolAutoAttackStateTraining_training,
	CToolAutoAttackStateTraining_trainingLessDef,
	CToolAutoAttackStateTraining_fighting,
	CToolAutoAttackStateTraining_switchingWeapon
};

struct PathfindParams{
	int x, y, z, x2, y2, z2;
	PathfindParams(int x,int y,int z,int x2,int y2,int z2){
		this->x=x;
		this->y=y;
		this->z=z;
		this->x2=x2;
		this->y2=y2;
		this->z2=z2;
	}
};

/////////////////////////////////////////////////////////////////////////////
// CConfigDialog dialog

class CConfigDialog : public MyDialog
{
// Construction
public:
	void reloadTrainingItems();
	void activateEnableButton(int enable);
	CConfigData * controlsToConfig();
	void configToControls(CConfigData *configData);
	void enableControls();
	void disableControls();
	CConfigDialog(CMod_cavebotApp *app,CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CConfigDialog)
	enum { IDD = IDD_CONFIG };
	CButton	m_addDelay;
	CGroupBoxEx	m_WaypointWalker;
	CGroupBoxEx	m_Training;
	CGroupBoxEx	m_MonsterAttacking;
	CGroupBoxEx	m_DepotWalker;
	CGroupBoxEx	m_Debugging;
	CGroupBoxEx	m_CorpseLooting;
	CEdit	m_depotCap;
	CButton	m_shareAlienBackattack;
	CEdit	m_ignore;
	CListBox	m_ignoreList;
	CButton	m_backattackRunes;
	CEdit	m_attackHpAbove;
	CButton	m_lootFromFloor;
	CButton	m_dropNotLooted;
	CButton	m_depotDropInsteadOfDepositon;
	CComboBox	m_weaponTrain;
	CComboBox	m_weaponFight;
	CStatic	m_trainingState;
	CButton	m_weaponHand;
	CButton	m_fightWhenSurrounded;
	CButton	m_fightWhenAlien;
	CComboBox	m_trainingMode;
	CButton	m_bloodHit;
	CButton	m_activate;
	CButton	m_debug;
	CEdit	m_depotWhen;
	CEdit	m_depotRemain;
	CComboBox	m_depotItemList;
	CListBox	m_depotEntryList;
	CStatic	m_stateDepot;
	CButton	m_gatherLootStats;
	CEdit	m_unreachableAfter;
	CEdit	m_suspendAfterUnreachable;
	CButton	m_attackOnlyAttacking;
	CEdit	m_standStill;
	CButton	m_forceAttackAfterAttack;
	CButton	m_stickToMonster;
	CButton	m_eatFromCorpse;
	CEdit	m_attackRange;
	CButton	m_lootCustom;
	CComboBox	m_waypointSelMode;
	CStatic	m_stateWalker;
	CStatic	m_stateLoot;
	CStatic	m_stateAttack;
	CButton	m_nomoveSuspended;
	CComboBox	m_mapUsed;
	CButton	m_lootinBags;
	CButton	m_lootWhileKill;
	CEdit	m_lootCapLimit;
	CButton	m_suspendOnEnemy;
	CButton	m_lootWorms;
	CComboBox	m_mode;
	CButton	m_lootGp;
	CButton	m_lootFood;
	CButton	m_logoutOnLevelChange;
	CEdit	m_curZ;
	CEdit	m_curY;
	CEdit	m_curX;
	CListBox	m_waypointList;
	CButton		m_autoFollow;
	CListBox	m_monsterList;
	CEdit		m_monster;
	CButton		m_dontAttackPlayers;
	CButton	m_pausingEnable;
	CButtonST	m_autoResearch;
	CButtonST	m_enable;
	CButtonST	m_depotEntryRemove;
	CButtonST	m_depotEntryAdd;
	CButtonST	m_OK;
	CButtonST	m_RemoveWaypoint;
	CButtonST	m_RemoveMonster;
	CButtonST	m_RemoveIgnore;
	CButtonST	m_AddWaypoint;
	CButtonST	m_AddMonster;
	CButtonST	m_AddIgnore;
	CButtonST	m_LoadMinimap;
	CButtonST	m_MonsterDown;
	CButtonST	m_MonsterUp;
	CEdit	m_radius;
	CButtonST	m_AddDelay;
	CEdit	m_delay;
	CButtonST	m_dropLootList;
	CComboBox m_depotModPriority;
	CButton m_stopByDepot;

	//}}AFX_DATA

	void reloadDepotItems();
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CConfigDialog)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CConfigDialog)
	virtual void OnOK();
	afx_msg void OnClose();
	afx_msg void OnEnable();
	afx_msg void OnTimer(UINT nIDEvent);
	virtual BOOL OnInitDialog();
	afx_msg void OnToolAutoattackRemoveMonster();
	afx_msg void OnToolAutoattackAddMonster();
	afx_msg void OnToolAutoattackRemoveWaypoint();
	afx_msg void OnToolAutoattackAddWaypoint();	
	afx_msg void OnDepotEntryadd();
	afx_msg void OnDepotEntryremove();
	afx_msg void OnToolAutoattackAddIgnore();
	afx_msg void OnToolAutoattackRemoveIgnore();
	afx_msg void OnLoadFromMinimap();
	afx_msg void OnMonsterAttackUp();
	afx_msg void OnMonsterAttackDown();
	afx_msg void OnAutoResearch();
	afx_msg void OnAddDelay();
	afx_msg void OnDropLootList();
	afx_msg void OnDropLoot();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	int cavebotFindpathStartedWaypoint;
	queue <PathfindParams*> pathfindPoints;
	CMod_cavebotApp * m_app;

	char virDropList[100][64];
	int virDropListCount;
	int virDropWhenCapacityLimitReached;
	int virDropOnlyLooted;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONFIGDIALOG_H__A38E1144_4FC4_4130_9D8B_A22DE0571AB2__INCLUDED_)
