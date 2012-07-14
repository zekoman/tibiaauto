// ToolContainercontent.cpp : implementation file
//

#include "stdafx.h"
#include "mod_runemaker.h"
#include "ToolContainerContent.h"
#include "MemReaderProxy.h"
#include "TibiaItemProxy.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CToolContainerContent dialog


CToolContainerContent::CToolContainerContent(int containerNr,CWnd* pParent /*=NULL*/)
	: MyDialog(CToolContainerContent::IDD, pParent)
{
	//{{AFX_DATA_INIT(CToolContainerContent)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_containerNr=containerNr;
}


void CToolContainerContent::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CToolContainerContent)
	DDX_Control(pDX, IDOK, m_OK);
	DDX_Control(pDX, IDC_FRAME_BACKPACK_CONTENTS, m_BackpackContainerFrame);
	DDX_Control(pDX, IDC_CONTAINERCONTENT_LIST, m_list);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CToolContainerContent, CDialog)
	//{{AFX_MSG_MAP(CToolContainerContent)
	ON_WM_ERASEBKGND()
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CToolContainerContent message handlers

BOOL CToolContainerContent::OnInitDialog() 
{
	CMemReaderProxy reader;
	CTibiaItemProxy itemProxy;
	CDialog::OnInitDialog();
	skin.SetButtonSkin(	m_OK);
	int i;
	char buf[256];

	
	m_list.InsertColumn(0,"Object ID",LVCFMT_LEFT,60);	
	m_list.InsertColumn(1,"Name",LVCFMT_LEFT,122);
	m_list.InsertColumn(2,"Quantity",LVCFMT_LEFT,60);	

	m_list.SetExtendedStyle(m_list.GetExtendedStyle()|LVS_EX_FULLROWSELECT);

	CTibiaContainer *container = reader.readContainer(m_containerNr);

	for (i=0;i<container->itemsInside;i++)
	{
		CTibiaItem *item=(CTibiaItem *)container->items.GetAt(i);
		sprintf(buf,"%d",item->objectId);
		m_list.InsertItem(i,buf);
		sprintf(buf,"%s",itemProxy.getItemName(item->objectId));
		m_list.SetItemText(i,1,buf);
		sprintf(buf,"%d",item->quantity);
		m_list.SetItemText(i,2,buf);
	};

	delete container;
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
