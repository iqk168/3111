// DlgRemoteRecover.cpp : implementation file
//

#include "stdafx.h"
#include "deer.h"
#include "DlgRemoteRecover.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgRemoteRecover dialog


CDlgRemoteRecover::CDlgRemoteRecover(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgRemoteRecover::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgRemoteRecover)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgRemoteRecover::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgRemoteRecover)
	DDX_Control(pDX, IDOK,		m_btnOK);
	DDX_Control(pDX, IDCANCEL,	m_btnCancel);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgRemoteRecover, CDialog)
	//{{AFX_MSG_MAP(CDlgRemoteRecover)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgRemoteRecover message handlers

BOOL CDlgRemoteRecover::PreTranslateMessage(MSG* pMsg) 
{	
//	m_ToolTip.RelayEvent(pMsg); 
	// z avoid ESC / Enter to crash the software
	if(pMsg->message  == WM_KEYDOWN)   
	{
		int nVirtKey = (int)pMsg->wParam;    
		if( nVirtKey == VK_ESCAPE )
			return   TRUE;   
		if( nVirtKey == VK_RETURN )   
			return   TRUE;   
	}	
	return CDialog::PreTranslateMessage(pMsg);
}

BOOL CDlgRemoteRecover::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// init button 
	m_btnOK.SetIcon(IDI_OK);
	m_btnOK.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnOK.SetFlat(FALSE);

	m_btnCancel.SetIcon(IDI_CANCEL);;
	m_btnCancel.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnCancel.SetFlat(FALSE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgRemoteRecover::OnOK() 
{
	
	CDialog::OnOK();
}

void CDlgRemoteRecover::OnCancel() 
{
	
	CDialog::OnCancel();
}
