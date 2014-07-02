// DlgButton.cpp : implementation file
//

#include "stdafx.h"
#include "deer.h"
#include "DlgButton.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgButton dialog


CDlgButton::CDlgButton(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgButton::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgButton)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgButton::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgButton)
	DDX_Control(pDX, IDC_D_WEST,			m_btnDLWest);
	DDX_Control(pDX, IDC_D_MANUAL,			m_btnDManual);
	DDX_Control(pDX, IDC_D_TESTER,			m_btnDLTester);
	DDX_Control(pDX, IDC_D_INSPECT,			m_btnDLInspect);
	DDX_Control(pDX, IDC_D_TS,				m_btnDLTestSite);
	DDX_Control(pDX, IDC_D_ARM,				m_btnDLArm);
	DDX_Control(pDX, IDC_M,					m_list);
	DDX_Control(pDX, IDOK,					m_btnOK);
	DDX_Control(pDX, IDCANCEL,				m_btnCancel);
	DDX_Control(pDX, IDC_STOP_LED,			m_wndStop);
	DDX_Control(pDX, IDC_START_LED,			m_wndStart);
	DDX_Control(pDX, IDC_SKIP_LED,			m_wndSkip);
	DDX_Control(pDX, IDC_RETRY_LED,			m_wndRetry);
	DDX_Control(pDX, IDC_ONE_CYCLE_LED,		m_wndOneCycle);
	DDX_Control(pDX, IDC_INITIAL_LED,		m_wndInitial);
	DDX_Control(pDX, IDC_RESET_LED,			m_wndReset);
	DDX_Control(pDX, IDC_TOWNER_RED,		m_wndTownerRed);
	DDX_Control(pDX, IDC_TOWNER_YELLOW,		m_wndTownerYellow);
	DDX_Control(pDX, IDC_TOWNER_GREEN,		m_wndTownerGreen);
	DDX_Control(pDX, IDC_TOWNER_BUZZER,		m_wndTownerBuzzer);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgButton, CDialog)
	//{{AFX_MSG_MAP(CDlgButton)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_START,				OnStart)
	ON_BN_CLICKED(IDC_FLUSH,				OnFlush)
	ON_BN_CLICKED(IDC_STOP,					OnStop)
	ON_BN_CLICKED(IDC_RESET,				OnReset)
	ON_BN_CLICKED(IDC_RETRY,				OnRetry)
	ON_BN_CLICKED(IDC_SKIP,					OnSkip)
	ON_BN_CLICKED(IDC_INITIAL,				OnInitial)
	ON_BN_CLICKED(IDC_SET,					OnSet)
	ON_BN_CLICKED(IDC_CLEAR,				OnClear)
	ON_MESSAGE(WM_TEST_MESSAGE,				OnShowMessage)
	ON_LBN_DBLCLK(IDC_M, OnDblclkM)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgButton message handlers

BOOL CDlgButton::PreTranslateMessage(MSG* pMsg) 
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

BOOL CDlgButton::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// Set Towner default setting.
	m_wndTownerRed.SetNewBkColor(ST_WHITE);
	m_wndTownerYellow.SetNewBkColor(ST_WHITE);
	m_wndTownerGreen.SetNewBkColor(ST_WHITE);
	m_wndTownerBuzzer.SetNewBkColor(ST_WHITE);

	// Set Button default setting 
	m_wndStop.SetNewBkColor(ST_WHITE);
	m_wndStart.SetNewBkColor(ST_WHITE);
	m_wndSkip.SetNewBkColor(ST_WHITE);
	m_wndRetry.SetNewBkColor(ST_WHITE);
	m_wndOneCycle.SetNewBkColor(ST_WHITE);
	m_wndInitial.SetNewBkColor(ST_WHITE);

	// init button 
	m_btnOK.SetIcon(IDI_OK);;
	m_btnOK.SetAlign(CButtonST::ST_ALIGN_VERT);;
	m_btnOK.SetFlat(FALSE);
	
	m_btnCancel.SetIcon(IDI_CANCEL);
	m_btnCancel.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnCancel.SetFlat(FALSE);

	InitValue();	
	
	InitTips();

	SetTimer(ID_TIME_BUTTON, 10, NULL);	// 更新畫面可以不用很快, 但是按鈕要快一點

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
static CMutex MutexMsg;
LRESULT CDlgButton::OnShowMessage(WPARAM p, LPARAM l) 
{
	CSingleLock Lock(&MutexMsg);
	Lock.Lock();

	CString cs = *(CString *)p;
	CTime time = CTime::GetCurrentTime();
	// Time
	CString cstime = _T("");
	SYSTEMTIME ti; 
	GetLocalTime(&ti);
	cstime.Format("%d/%d %d:%d:%5.3f", 
		ti.wMonth, ti.wDay, ti.wHour, ti.wMinute, ti.wSecond + ( ti.wMilliseconds / 1000. ) );
	// Msg
	CString csMsg;
	csMsg.Format("%s: %s", cstime, cs );
	m_list.InsertString( m_list.GetCount(), csMsg );
	m_list.SetCurSel( m_list.GetCount() - 1 );

	Lock.Unlock();

	return true;
}
void CDlgButton::InitValue()
{
	// Tester
	if( m.Simulation.m_bDLTester == 1 )
		m_btnDLTester.SetCheck(1);
	else
		m_btnDLTester.SetCheck(0);

	// West 
	if( m.Simulation.m_bDLWest == 1 )
		m_btnDLWest.SetCheck(1);
	else
		m_btnDLWest.SetCheck(0);

	// Inspect
	if( m.Simulation.m_bDLInspect == 1 )
		m_btnDLInspect.SetCheck(1);
	else
		m_btnDLInspect.SetCheck(0);

	// Test Site
	if( m.Simulation.m_bDLTestSite == 1 )
		m_btnDLTestSite.SetCheck(1);
	else
		m_btnDLTestSite.SetCheck(0);

	// Arm
	if( m.Simulation.m_bDLArm == 1 )
		m_btnDLArm.SetCheck(1);
	else
		m_btnDLArm.SetCheck(0);

	// Manual 
	if( m.Simulation.m_bDLManual == 1 )
		m_btnDManual.SetCheck(1);
	else
		m_btnDManual.SetCheck(0);

}
void CDlgButton::InitTips()
{
	// Tips 
	// Init Tips
	m_ToolTip.Create(this);
	m_ToolTip.SetMaxTipWidth(800);
	m_ToolTip.SetDelayTime( TTDT_AUTOPOP, 10000 );
	m_ToolTip.SetDelayTime( TTDT_INITIAL, 25 );
	m_ToolTip.EnableToolTips(true);

//	m_ToolTip.AddTool( GetDlgItem(IDC_ALIGNMENT_INPUT_READ),	_T("Read ArmXYZ Motor RCount Value With Input Alignment Position") );

}
void CDlgButton::ButtonQuery()
{
	// Change the button status.
	if( m.RemoteOutSet.BtnStartOn == 1 )
		m_wndStart.SetNewBkColor(ST_RED);
	else
		m_wndStart.SetNewBkColor(ST_WHITE);

	if( m.RemoteOutSet.BtnStopOn == 1	)
		m_wndStop.SetNewBkColor(ST_RED);
	else
		m_wndStop.SetNewBkColor(ST_WHITE);

	if( m.RemoteOutSet.BtnRetryOn == 1	)
		m_wndRetry.SetNewBkColor(ST_RED);
	else
		m_wndRetry.SetNewBkColor(ST_WHITE);

	if( m.RemoteOutSet.BtnSkipOn == 1	)
		m_wndSkip.SetNewBkColor(ST_RED);
	else
		m_wndSkip.SetNewBkColor(ST_WHITE);

    if( m.RemoteOutSet.BtnInitialOn == 1	)
		m_wndInitial.SetNewBkColor(ST_RED);
	else
		m_wndInitial.SetNewBkColor(ST_WHITE);

	if( m.RemoteOutSet.BtnOneCycleOn	== 1 )
		m_wndOneCycle.SetNewBkColor(ST_RED);
	else
		m_wndOneCycle.SetNewBkColor(ST_WHITE);

	if( m.RemoteOutSet.BtnResetOn )
		m_wndReset.SetNewBkColor(ST_RED);
	else
		m_wndReset.SetNewBkColor(ST_WHITE);

	// Change the Towner status.
	if( m.OutSet.TowerRedOn == 1 )
		m_wndTownerRed.SetNewBkColor(ST_RED);
	else
		m_wndTownerRed.SetNewBkColor(ST_WHITE);

	if( m.OutSet.TowerYellowOn == 1 )
		m_wndTownerYellow.SetNewBkColor(ST_YELLOW);
	else
		m_wndTownerYellow.SetNewBkColor(ST_WHITE);

	if( m.OutSet.TowerGreenOn == 1 )
		m_wndTownerGreen.SetNewBkColor(ST_GREEN);
	else
		m_wndTownerGreen.SetNewBkColor(ST_WHITE);

	if( m.OutSet.TowerBuzzerOn == 1 )
		m_wndTownerBuzzer.SetNewBkColor(ST_GRAY);
	else
		m_wndTownerBuzzer.SetNewBkColor(ST_WHITE);
}
void CDlgButton::OnTimer(UINT nIDEvent) 
{
	switch(nIDEvent)
	{
	case ID_TIME_BUTTON:
		ButtonQuery();	
		break;
	default:
		break;
	}	
	CDialog::OnTimer(nIDEvent);
}

void CDlgButton::OnOK() 
{
	
	CDialog::OnOK();
}
void CDlgButton::OnCancel() 
{
	
	CDialog::OnCancel();
}
void CDlgButton::OnStart() 
{
	m.PanelButton.BtnStartPushed = true;   
}
void CDlgButton::OnFlush() 
{
	m.PanelButton.BtnOneCyclePushed = true;
}
void CDlgButton::OnStop() 
{
	m.PanelButton.BtnStopPushed = true;
}
void CDlgButton::OnReset() 
{
	m.PanelButton.BtnResetPushed = true;
}
void CDlgButton::OnRetry() 
{
	m.PanelButton.BtnRetryPushed = true;
}
void CDlgButton::OnSkip() 
{
	m.PanelButton.BtnSkipPushed = true;
}
void CDlgButton::OnInitial() 
{
	m.PanelButton.BtnInitPushed = true;
}
void CDlgButton::SaveData() 
{
	int b;

	b = m_btnDLArm.GetCheck();
	if(b)
		m.Simulation.m_bDLArm = 1;
	else
		m.Simulation.m_bDLArm = 0;

	b = m_btnDLTestSite.GetCheck();
	if(b)
		m.Simulation.m_bDLTestSite = 1;
	else
		m.Simulation.m_bDLTestSite = 0;

	b = m_btnDLInspect.GetCheck();
	if(b)
		m.Simulation.m_bDLInspect = 1;
	else
		m.Simulation.m_bDLInspect = 0;

	b = m_btnDLTester.GetCheck();
	if(b)
		m.Simulation.m_bDLTester = 1;
	else
		m.Simulation.m_bDLTester = 0;

	b = m_btnDManual.GetCheck();
	if(b)
		m.Simulation.m_bDLManual = 1;
	else
		m.Simulation.m_bDLManual = 0;

	b = m_btnDLWest.GetCheck();
	if(b)
		m.Simulation.m_bDLWest = 1;
	else
		m.Simulation.m_bDLWest = 0;

	f.SaveSimulation();
}
void CDlgButton::OnSet() 
{
	SaveData();
}

void CDlgButton::OnClear() 
{
	m_list.ResetContent();
}

void CDlgButton::OnDblclkM() 
{
	
}
