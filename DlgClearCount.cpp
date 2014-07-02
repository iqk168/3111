// DlgClearCount.cpp : implementation file
//

#include "stdafx.h"
#include "deer.h"
#include "DlgClearCount.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgClearCount dialog


CDlgClearCount::CDlgClearCount(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgClearCount::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgClearCount)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgClearCount::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgClearCount)
	DDX_Control(pDX, IDC_CLEAR,		m_btnClear);
	DDX_Control(pDX, IDC_COUNT,		m_wndCount);
	DDX_Control(pDX, IDOK,			m_btnOK);
	DDX_Control(pDX, IDCANCEL,		m_btnCancel);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgClearCount, CDialog)
	//{{AFX_MSG_MAP(CDlgClearCount)
	ON_WM_DESTROY()
	ON_WM_CLOSE()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_CLEAR, OnClear)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgClearCount message handlers

BOOL CDlgClearCount::OnInitDialog() 
{
	CDialog::OnInitDialog();

	m.Info.bSubDlgOpen = true;
	f.UpdateButtonState();

	// init button 
	m_btnClear.SetIcon(IDI_CLEAR_COUNT);;
	m_btnClear.SetAlign(CButtonST::ST_ALIGN_VERT);;
	m_btnClear.SetFlat(FALSE);

	m_btnOK.SetIcon(IDI_OK);;
	m_btnOK.SetAlign(CButtonST::ST_ALIGN_VERT);;
	m_btnOK.SetFlat(FALSE);
	
	m_btnCancel.SetIcon(IDI_CANCEL);
	m_btnCancel.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnCancel.SetFlat(FALSE);	

	// ³]©w Count ªì©l­È.
	m_wndCount.SetText("--", 10, "Arial Black", DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	m_wndCount.SetNewBkColor(ST_YELLOW);

	// Counter
	InitValue();

	f.ChangeLanguage(GetSafeHwnd());

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
void CDlgClearCount::InitValue()
{
	int i = 0;
	int total = 0;
	for(i=0; i<_Output_Stack_No; i++)
		total += m.Counter.OutputCount[i];

	CString csCount;
	csCount.Format("%d", total );
	m_wndCount.SetWindowText( csCount );
}
void CDlgClearCount::OnDestroy() 
{
	m.Info.bSubDlgOpen = false;
	f.UpdateButtonState();

	CDialog::OnDestroy();		
}

void CDlgClearCount::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	
	CDialog::OnClose();
}

void CDlgClearCount::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	
	CDialog::OnTimer(nIDEvent);
}

void CDlgClearCount::OnOK() 
{
	m.Info.bSubDlgOpen = false;
	f.UpdateButtonState();	

	CDialog::OnOK();
}

void CDlgClearCount::OnCancel() 
{
	m.Info.bSubDlgOpen = false;
	f.UpdateButtonState();

	CDialog::OnCancel();
}

void CDlgClearCount::OnClear() 
{
	int i = 0;
	for(i=0; i<_Output_Stack_No; i++)
		m.Counter.OutputCount[i] = 0;	
	// Clear all counter. 

	f.SaveCounter();
}

BOOL CDlgClearCount::PreTranslateMessage(MSG* pMsg) 
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
