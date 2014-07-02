// DlgYieldMonitor.cpp : implementation file
//

#include "stdafx.h"
#include "deer.h"
#include "DlgYieldMonitor.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgYieldMonitor dialog


CDlgYieldMonitor::CDlgYieldMonitor(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgYieldMonitor::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgYieldMonitor)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgYieldMonitor::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgYieldMonitor)
	DDX_Control(pDX, IDC_E_TESTED,			m_wndTested);
	DDX_Control(pDX, IDC_E_FAIL_RATE,		m_wndFailRate);
	DDX_Control(pDX, IDC_E_CONTINUE_FAIL,	m_wndContinueFailStatus);
	DDX_Control(pDX, IDOK,					m_btnOK);
	DDX_Control(pDX, IDCANCEL,				m_btnCancel);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgYieldMonitor, CDialog)
	//{{AFX_MSG_MAP(CDlgYieldMonitor)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgYieldMonitor message handlers

BOOL CDlgYieldMonitor::PreTranslateMessage(MSG* pMsg) 
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

BOOL CDlgYieldMonitor::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// init button 
	m_btnOK.SetIcon(IDI_OK);
	m_btnOK.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnOK.SetFlat(FALSE);
	
	m_btnCancel.SetIcon(IDI_CANCEL);
	m_btnCancel.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnCancel.SetFlat(FALSE);
	
	//
	InitTips();

	//
	InitValue();

	SetTimer( ID_TIME_YIELD_MONITOR, 600, NULL );

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
void CDlgYieldMonitor::YieldStatus()
{
	// Continue Fail
	CString csContinueFail = _T("");
	csContinueFail.Format(" %d / %d", 
		m.m_YieldCtrl.m_lContinueFail, m.YieldSetting.iFailCount );
	m_wndContinueFailStatus.SetWindowText( csContinueFail );

	// Yield Rate
	CString csFailRate = _T("");
	int iCSize = m.m_YieldCtrl.m_iPFArray.GetSize();
	csFailRate.Format(" %5.2f, Counter: %d [%5.2f]", 
		m.m_YieldCtrl.m_dFailRate, iCSize, m.YieldSetting.dYieldLimit );
	m_wndFailRate.SetWindowText( csFailRate );

	// Tested 
	CString csTested = _T("");
	csTested.Format(" %d", m.m_YieldCtrl.m_lTested );
	m_wndTested.SetWindowText( csTested );
}
void CDlgYieldMonitor::InitTips()
{

}
void CDlgYieldMonitor::InitValue()
{
	
}
void CDlgYieldMonitor::OnTimer(UINT nIDEvent) 
{
	switch(nIDEvent)
	{
	case ID_TIME_YIELD_MONITOR:
		{
			YieldStatus();
		}
		break;
	}		
	CDialog::OnTimer(nIDEvent);
}

void CDlgYieldMonitor::OnOK() 
{
	
	CDialog::OnOK();
}

void CDlgYieldMonitor::OnCancel() 
{
	
	CDialog::OnCancel();
}
