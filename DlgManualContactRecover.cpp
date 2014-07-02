// DlgManualContactRecover.cpp : implementation file
//

#include "stdafx.h"
#include "deer.h"
#include "DlgManualContactRecover.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgManualContactRecover dialog


CDlgManualContactRecover::CDlgManualContactRecover(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgManualContactRecover::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgManualContactRecover)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgManualContactRecover::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgManualContactRecover)
	DDX_Control(pDX, IDC_MSG,		m_wndMsg);
	DDX_Control(pDX, IDOK,			m_btnOK);
	DDX_Control(pDX, IDCANCEL,		m_btnCancel);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgManualContactRecover, CDialog)
	//{{AFX_MSG_MAP(CDlgManualContactRecover)
	ON_MESSAGE( WM_MANUAL_UP_DONE,					OnTSUped )
	ON_MESSAGE( WM_MANUAL_ALARM,					OnAlarm )

	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgManualContactRecover message handlers

void CDlgManualContactRecover::OnOK() 
{
	m.ManualInterlok.IsManualControlMode = false;

	CDialog::OnOK();
}

void CDlgManualContactRecover::OnCancel() 
{
	m.ManualInterlok.IsManualControlMode = false;

	CDialog::OnCancel();
}

BOOL CDlgManualContactRecover::PreTranslateMessage(MSG* pMsg) 
{
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
LRESULT CDlgManualContactRecover::OnTSUped(WPARAM p, LPARAM l)
{
	m_btnOK.ShowWindow( TRUE );
	m_wndMsg.SetWindowText("Recover complete.\r\nPlease click [OK] to close manual contact");
	return TRUE;
}
LRESULT CDlgManualContactRecover::OnAlarm(WPARAM p, LPARAM l)
{
	m_btnCancel.ShowWindow( TRUE );
	m_wndMsg.SetWindowText("Recover fail.\r\nPlease click[Cancel] to close manual contact\r\nAnd initial again");
	return TRUE;
}
BOOL CDlgManualContactRecover::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// init button 
	m_btnOK.SetIcon(IDI_OK);
	m_btnOK.SetAlign(CButtonST::ST_ALIGN_VERT);;
	m_btnOK.SetFlat(FALSE);
	
	m_btnCancel.SetIcon(IDI_CANCEL);
	m_btnCancel.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnCancel.SetFlat(FALSE);

	m_btnOK.ShowWindow( FALSE );
	m_btnCancel.ShowWindow( FALSE );

	m_wndMsg.SetWindowText("Wait for recover complete");
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
