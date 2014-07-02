// DlgPasswordRead.cpp : implementation file
//

#include "stdafx.h"
#include "deer.h"
#include "DlgPasswordRead.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgPasswordRead dialog


CDlgPasswordRead::CDlgPasswordRead(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgPasswordRead::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgPasswordRead)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgPasswordRead::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgPasswordRead)
	DDX_Control(pDX, IDC_E_ENGINEER,		m_wndEngineerPw);
	DDX_Control(pDX, IDC_E_SETUP,			m_wndSetupPw);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgPasswordRead, CDialog)
	//{{AFX_MSG_MAP(CDlgPasswordRead)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgPasswordRead message handlers

BOOL CDlgPasswordRead::PreTranslateMessage(MSG* pMsg) 
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

BOOL CDlgPasswordRead::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	//
	InitValue();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
void CDlgPasswordRead::InitValue()
{
	m_wndEngineerPw.SetWindowText( " " + m.UI.PasswordEngineer );

	m_wndSetupPw.SetWindowText( " " + m.UI.PasswordSetup );
}
void CDlgPasswordRead::OnOK() 
{
	
	CDialog::OnOK();
}

void CDlgPasswordRead::OnCancel() 
{
	
	CDialog::OnCancel();
}
