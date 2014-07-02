// DlgATCMonitor.cpp : implementation file
//

#include "stdafx.h"
#include "deer.h"
#include "DlgATCMonitor.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgATCMonitor dialog


CDlgATCMonitor::CDlgATCMonitor(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgATCMonitor::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgATCMonitor)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

void CDlgATCMonitor::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgATCMonitor)
	DDX_Control(pDX, IDC_E_PV,			m_wndPV);
	DDX_Control(pDX, IDC_E_SV,			m_wndSV);
	DDX_Control(pDX, IDC_LED_ENABLE,	m_ledEnable);
	DDX_Control(pDX, IDCANCEL,			m_btnCancel);
	DDX_Control(pDX, IDOK,				m_btnOK);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgATCMonitor, CDialog)
	//{{AFX_MSG_MAP(CDlgATCMonitor)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_SET, OnSet)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgATCMonitor message handlers

BOOL CDlgATCMonitor::PreTranslateMessage(MSG* pMsg) 
{
	m_ToolTip.RelayEvent(pMsg);

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

BOOL CDlgATCMonitor::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m.Info.bSubDlgOpen = true;
	f.UpdateButtonState();

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

	//
	InitLed();

	SetTimer(ID_TIME_ATC_MONITOR, 80, NULL);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgATCMonitor::InitValue()
{
	CString csSV = _T("");
	csSV.Format("%5.2f", m.m_ATCMonitor.sv );
	
	m_wndSV.SetWindowText( csSV );
}
void CDlgATCMonitor::InitLed()
{
	m_ledEnable.SetLed(CLed::LED_COLOR_GREEN, CLed::LED_OFF);
}
void CDlgATCMonitor::InitTips()
{
	// Tips // Init Tips
	m_ToolTip.Create(this);
	m_ToolTip.SetMaxTipWidth(800);
	m_ToolTip.SetDelayTime( TTDT_AUTOPOP, 10000 );
	m_ToolTip.SetDelayTime( TTDT_INITIAL, 25 );
	m_ToolTip.EnableToolTips(true);
}
void CDlgATCMonitor::UpdateATCStatus() 
{
	CString csPV = _T("");
	double dPV = 0.0;

	csPV.Format("%5.2f", dPV );
	m_wndPV.SetWindowText( csPV );
}
void CDlgATCMonitor::OnTimer(UINT nIDEvent) 
{
	switch(nIDEvent)
	{
	case ID_TIME_ATC_MONITOR:
		UpdateATCStatus();	
		break;
	default:
		break;
	}	
	CDialog::OnTimer(nIDEvent);
}

void CDlgATCMonitor::OnOK() 
{
	KillTimer( ID_TIME_ATC_MONITOR );

	m.Info.bSubDlgOpen = false;
	f.UpdateButtonState();	

	CDialog::OnOK();
}

void CDlgATCMonitor::OnCancel() 
{
	KillTimer( ID_TIME_ATC_MONITOR );

	m.Info.bSubDlgOpen = false;
	f.UpdateButtonState();
	
	CDialog::OnCancel();
}

void CDlgATCMonitor::OnSet() 
{
	CString csSV = _T("");
	m_wndSV.GetWindowText( csSV );	

	//
	m.m_ATCMonitor.sv = atof( csSV );
	f.SaveATCMonitor();
}
