// DlgSemiAutoFile.cpp : implementation file
//

#include "stdafx.h"
#include "deer.h"
#include "DlgSemiAutoFile.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgSemiAutoFile dialog


CDlgSemiAutoFile::CDlgSemiAutoFile(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgSemiAutoFile::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgSemiAutoFile)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgSemiAutoFile::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgSemiAutoFile)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgSemiAutoFile, CDialog)
	//{{AFX_MSG_MAP(CDlgSemiAutoFile)
	ON_BN_CLICKED(IDC_B_SET, OnBSet)
	ON_BN_CLICKED(IDC_B_ADD, OnBAdd)
	ON_BN_CLICKED(IDC_B_DELETE, OnBDelete)
	ON_BN_CLICKED(IDC_B_UP, OnBUp)
	ON_BN_CLICKED(IDC_B_DOWN, OnBDown)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgSemiAutoFile message handlers

void CDlgSemiAutoFile::OnBSet() 
{
	// TODO: Add your control notification handler code here
	
}

void CDlgSemiAutoFile::OnBAdd() 
{
	// TODO: Add your control notification handler code here
	
}

void CDlgSemiAutoFile::OnBDelete() 
{
	// TODO: Add your control notification handler code here
	
}

void CDlgSemiAutoFile::OnBUp() 
{
	// TODO: Add your control notification handler code here
	
}

void CDlgSemiAutoFile::OnBDown() 
{
	// TODO: Add your control notification handler code here
	
}

void CDlgSemiAutoFile::OnOK() 
{
	// TODO: Add extra validation here
	
	CDialog::OnOK();
}

void CDlgSemiAutoFile::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

BOOL CDlgSemiAutoFile::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	// Tips
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
