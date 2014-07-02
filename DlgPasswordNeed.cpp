// DlgPasswordNeed.cpp : implementation file
//

#include "stdafx.h"
#include "deer.h"
#include "DlgPasswordNeed.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgPasswordNeed dialog


CDlgPasswordNeed::CDlgPasswordNeed(bool bEngineer,bool bDebuger, CWnd* pParent /*=NULL*/)
	: CDialog(CDlgPasswordNeed::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgPasswordNeed)
	m_csPassword = _T("");
	//}}AFX_DATA_INIT
	m_bEngineer = bEngineer;
	m_bDebuger	= bDebuger;
	// if true. It it enigneer mode.
}


void CDlgPasswordNeed::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgPasswordNeed)
	DDX_Control(pDX, IDC_MSG, m_wndMsg);
	DDX_Control(pDX, IDOK, m_btnOK);
	DDX_Control(pDX, IDCANCEL, m_btnCancel);
	DDX_Text(pDX, IDC_PASSWORD, m_csPassword);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgPasswordNeed, CDialog)
	//{{AFX_MSG_MAP(CDlgPasswordNeed)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgPasswordNeed message handlers

void CDlgPasswordNeed::OnOK() 
{
	UpdateData();

	if( m_bDebuger )
	{
		if(m_csPassword == "ken" )
			CDialog::OnOK();
		else if(m_csPassword == "denny" )
			CDialog::OnOK();
		else if(m_csPassword == "terence" )
			CDialog::OnOK();
		else
			AfxMessageBox("Password Error.!");
	}
	else
	{
		if(m_bEngineer)
		{
			if(m_csPassword == m.UI.PasswordEngineer)
				CDialog::OnOK();
			else
				AfxMessageBox("Password Error.!");
			// It only check Enigneer Password.
		}else
		{
			if(m_csPassword == m.UI.PasswordSetup)
				CDialog::OnOK();
			else
				AfxMessageBox("Password Error.!");
			// It only check Setup Password. Or Super User Code "3110"
		}
	}

//	CDialog::OnOK();
}

void CDlgPasswordNeed::OnCancel() 
{
	
	CDialog::OnCancel();
}

void CDlgPasswordNeed::OnDestroy() 
{
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here	
}

BOOL CDlgPasswordNeed::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// init button 
	m_btnOK.SetIcon(IDI_OK);;
	m_btnOK.SetAlign(CButtonST::ST_ALIGN_VERT);;
	m_btnOK.SetFlat(FALSE);
	
	m_btnCancel.SetIcon(IDI_CANCEL);
	m_btnCancel.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnCancel.SetFlat(FALSE);

	// set different message
	if( m_bDebuger )
	{
		m_wndMsg.SetWindowText( "Please Input Debug Password." );
	}
	else
	{
		if( m_bEngineer )
			m_wndMsg.SetWindowText( "Please Input Engineer Password." );
		else
			m_wndMsg.SetWindowText("Please Input Setup Password above.");
	}

	f.ChangeLanguage(GetSafeHwnd());
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CDlgPasswordNeed::PreTranslateMessage(MSG* pMsg) 
{
	// z avoid ESC / Enter to crash the software
	if(pMsg->message  == WM_KEYDOWN)   
	{
		int nVirtKey = (int)pMsg->wParam;    
		if( nVirtKey == VK_ESCAPE )
			return   TRUE;   
//		if( nVirtKey == VK_RETURN )   
//			return   TRUE;   
	}
	return CDialog::PreTranslateMessage(pMsg);
}
