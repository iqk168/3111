// DlgRepeatTrayBinCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "deer.h"
#include "DlgRepeatTrayBinCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgRepeatTrayBinCtrl dialog


CDlgRepeatTrayBinCtrl::CDlgRepeatTrayBinCtrl(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgRepeatTrayBinCtrl::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgRepeatTrayBinCtrl)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgRepeatTrayBinCtrl::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgRepeatTrayBinCtrl)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgRepeatTrayBinCtrl, CDialog)
	//{{AFX_MSG_MAP(CDlgRepeatTrayBinCtrl)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgRepeatTrayBinCtrl message handlers

BOOL CDlgRepeatTrayBinCtrl::PreTranslateMessage(MSG* pMsg) 
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

BOOL CDlgRepeatTrayBinCtrl::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
