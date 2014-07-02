// DlgMotorMove.cpp : implementation file
//

#include "stdafx.h"
#include "deer.h"
#include "DlgMotorMove.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgMotorMove dialog


CDlgMotorMove::CDlgMotorMove(long now, CWnd* pParent /*=NULL*/)
	: CDialog(CDlgMotorMove::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgMotorMove)
	m_New = 0;
	m_NewGo = 0;
	m_Now = now;
	//}}AFX_DATA_INIT
}


void CDlgMotorMove::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgMotorMove)
	DDX_Control(pDX, IDC_NEW, m_wndMotorNew);
	DDX_Control(pDX, IDOK, m_btnOK);
	DDX_Control(pDX, IDCANCEL, m_btnCancel);
	DDX_Text(pDX, IDC_NEW, m_New);
	DDX_Text(pDX, IDC_NOW, m_Now);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgMotorMove, CDialog)
	//{{AFX_MSG_MAP(CDlgMotorMove)
	ON_WM_DESTROY()
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgMotorMove message handlers

void CDlgMotorMove::OnOK() 
{
	UpdateData();	
	
//	m_NewGo = m_New + m_Now;
	m_NewGo = m_New;
	
	UpdateData(FALSE);

	CDialog::OnOK();
}

void CDlgMotorMove::OnCancel() 
{
	
	CDialog::OnCancel();
}

BOOL CDlgMotorMove::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// init button 
	m_btnOK.SetIcon(IDI_OK);;
	m_btnOK.SetAlign(CButtonST::ST_ALIGN_VERT);;
	m_btnOK.SetFlat(FALSE);
	
	m_btnCancel.SetIcon(IDI_CANCEL);
	m_btnCancel.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnCancel.SetFlat(FALSE);

	// Set fouces
	m_wndMotorNew.SetFocus();

	f.ChangeLanguage(GetSafeHwnd());

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgMotorMove::OnDestroy() 
{
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here

}

void CDlgMotorMove::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	
	CDialog::OnClose();
}

BOOL CDlgMotorMove::PreTranslateMessage(MSG* pMsg) 
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
