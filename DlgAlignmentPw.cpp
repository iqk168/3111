// DlgAlignmentPw.cpp : implementation file
//

#include "stdafx.h"
#include "deer.h"
#include "DlgAlignmentPw.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgAlignmentPw dialog


CDlgAlignmentPw::CDlgAlignmentPw(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgAlignmentPw::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgAlignmentPw)
	m_csPw = _T("");
	//}}AFX_DATA_INIT
}


void CDlgAlignmentPw::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgAlignmentPw)
	DDX_Text(pDX, IDC_PW, m_csPw);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgAlignmentPw, CDialog)
	//{{AFX_MSG_MAP(CDlgAlignmentPw)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgAlignmentPw message handlers

BOOL CDlgAlignmentPw::PreTranslateMessage(MSG* pMsg) 
{
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

BOOL CDlgAlignmentPw::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgAlignmentPw::OnOK() 
{
	UpdateData();

	if( m_csPw != "xxx" )
	{
		AfxMessageBox("Please try again.!");
		return;
	}
	CDialog::OnOK();
}

void CDlgAlignmentPw::OnCancel() 
{
	
	CDialog::OnCancel();
}
