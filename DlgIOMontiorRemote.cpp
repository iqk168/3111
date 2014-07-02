// DlgIOMontiorRemote.cpp : implementation file
//

#include "stdafx.h"
#include "deer.h"
#include "DlgIOMontiorRemote.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgIOMontiorRemote dialog


CDlgIOMontiorRemote::CDlgIOMontiorRemote(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgIOMontiorRemote::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgIOMontiorRemote)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	m_bOnlyShow = false;

	m_bShowEnable = FALSE;
}


void CDlgIOMontiorRemote::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgIOMontiorRemote)
	DDX_Control(pDX, IDC_DE_AVG,				m_wndDebugAvg);
	DDX_Control(pDX, IDC_DE_COUNT,				m_wndDebugCount);
	DDX_Control(pDX, IDC_DE_ERR_COUNT,			m_wndDebugError);
	DDX_Control(pDX, IDC_DE,					m_wndDebugGroup);
	DDX_Control(pDX, IDC_LED_P_OUT_STOP,		m_ledOutStop);
	DDX_Control(pDX, IDC_LED_P_OUT_START,		m_ledOutStart);
	DDX_Control(pDX, IDC_LED_P_OUT_SKIP,		m_ledOutSkip);
	DDX_Control(pDX, IDC_LED_P_OUT_RETRY,		m_ledOutRetry);
	DDX_Control(pDX, IDC_LED_P_OUT_RESET,		m_ledOutReset);
	DDX_Control(pDX, IDC_LED_P_OUT_ONECYCLE,	m_ledOutOneCycle);
	DDX_Control(pDX, IDC_LED_P_OUT_INITIAL,		m_ledOutInitial);
	DDX_Control(pDX, IDC_LED_P_IN_STOP,			m_ledPInStop);
	DDX_Control(pDX, IDC_LED_P_IN_START,		m_ledPInStart);
	DDX_Control(pDX, IDC_LED_P_IN_SKIP,			m_ledPInSkip);
	DDX_Control(pDX, IDC_LED_P_IN_RETRY,		m_ledPInRetry);
	DDX_Control(pDX, IDC_LED_P_IN_RESET,		m_ledPInReset);
	DDX_Control(pDX, IDC_LED_P_IN_ONECYCLE,		m_ledPInOneCycle);
	DDX_Control(pDX, IDC_LED_P_IN_INITIAL,		m_ledPInInitial);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgIOMontiorRemote, CDialog)
	//{{AFX_MSG_MAP(CDlgIOMontiorRemote)
	ON_WM_DESTROY()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_LED_P_OUT_START,			OnLedPOutStart)
	ON_BN_CLICKED(IDC_LED_P_OUT_ONECYCLE,		OnLedPOutOnecycle)
	ON_BN_CLICKED(IDC_LED_P_OUT_STOP,			OnLedPOutStop)
	ON_BN_CLICKED(IDC_LED_P_OUT_RESET,			OnLedPOutReset)
	ON_BN_CLICKED(IDC_LED_P_OUT_SKIP,			OnLedPOutSkip)
	ON_BN_CLICKED(IDC_LED_P_OUT_RETRY,			OnLedPOutRetry)
	ON_BN_CLICKED(IDC_LED_P_OUT_INITIAL,		OnLedPOutInitial)
	ON_BN_CLICKED(IDC_STATIC_DEBUG,				OnStaticDebug)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgIOMontiorRemote message handlers

BOOL CDlgIOMontiorRemote::PreTranslateMessage(MSG* pMsg) 
{
	// Tips
	m_ToolTip.RelayEvent(pMsg);
	
	return CDialog::PreTranslateMessage(pMsg);
}

void CDlgIOMontiorRemote::OnDestroy() 
{
	KillTimer( ID_TIME_GET_STATUS );

	CDialog::OnDestroy();	
}

BOOL CDlgIOMontiorRemote::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	//
	InitLed();

	//
	InitTips();

	// Set Timer for get IO Status
	SetTimer(ID_TIME_GET_STATUS, _Status_Timer, NULL);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgIOMontiorRemote::InitLed()
{
	m_ledPInStop.SetLed(CLed::LED_COLOR_RED);
	m_ledPInStart.SetLed(CLed::LED_COLOR_RED);
	m_ledPInSkip.SetLed(CLed::LED_COLOR_RED);
	m_ledPInRetry.SetLed(CLed::LED_COLOR_RED);
	m_ledPInReset.SetLed(CLed::LED_COLOR_RED);
	m_ledPInOneCycle.SetLed(CLed::LED_COLOR_RED);
	m_ledPInInitial.SetLed(CLed::LED_COLOR_RED);

	m_ledOutStop.SetLed(CLed::LED_COLOR_GREEN);
	m_ledOutStart.SetLed(CLed::LED_COLOR_GREEN);
	m_ledOutSkip.SetLed(CLed::LED_COLOR_GREEN);
	m_ledOutRetry.SetLed(CLed::LED_COLOR_GREEN);
	m_ledOutReset.SetLed(CLed::LED_COLOR_GREEN);
	m_ledOutOneCycle.SetLed(CLed::LED_COLOR_GREEN);
	m_ledOutInitial.SetLed(CLed::LED_COLOR_GREEN);
}
void CDlgIOMontiorRemote::InitTips()
{
	// Tips // Init Tips
	m_ToolTip.Create(this);
	m_ToolTip.SetMaxTipWidth(800);
	m_ToolTip.SetDelayTime( TTDT_AUTOPOP, 10000 );
	m_ToolTip.SetDelayTime( TTDT_INITIAL, 25 );
	m_ToolTip.EnableToolTips(true);

	//
	m_ToolTip.AddTool( GetDlgItem(IDC_LED_P_OUT_START),		_T("R-O1-00") );
	m_ToolTip.AddTool( GetDlgItem(IDC_LED_P_OUT_STOP),		_T("R-O1-01") );
	m_ToolTip.AddTool( GetDlgItem(IDC_LED_P_OUT_SKIP),		_T("R-O1-02") );
	m_ToolTip.AddTool( GetDlgItem(IDC_LED_P_OUT_RETRY),		_T("R-O1-03") );
	m_ToolTip.AddTool( GetDlgItem(IDC_LED_P_OUT_RESET),		_T("R-O1-04") );
	m_ToolTip.AddTool( GetDlgItem(IDC_LED_P_OUT_INITIAL),	_T("R-O1-05") );
	m_ToolTip.AddTool( GetDlgItem(IDC_LED_P_OUT_ONECYCLE),	_T("R-O1-06") );

	//
	m_ToolTip.AddTool( GetDlgItem(IDC_LED_P_IN_START),		_T("R-I1-00") );
	m_ToolTip.AddTool( GetDlgItem(IDC_LED_P_IN_STOP),		_T("R-I1-01") );	
	m_ToolTip.AddTool( GetDlgItem(IDC_LED_P_IN_SKIP),		_T("R-I1-02") );	
	m_ToolTip.AddTool( GetDlgItem(IDC_LED_P_IN_RETRY),		_T("R-I1-03") );
	m_ToolTip.AddTool( GetDlgItem(IDC_LED_P_IN_RESET),		_T("R-I1-04") );
	m_ToolTip.AddTool( GetDlgItem(IDC_LED_P_IN_INITIAL),	_T("R-I1-05") );
	m_ToolTip.AddTool( GetDlgItem(IDC_LED_P_IN_ONECYCLE),	_T("R-I1-06") );
}
void CDlgIOMontiorRemote::IODebug()
{
#ifdef _Demo
#else
	// Error
	CString csMsg = _T("");
	csMsg.Format("%d", m.DebugError.ReadRemoteErr );
	m_wndDebugError.SetWindowText( csMsg );

	// Total
	csMsg.Format("%d", m.DebugError.ReadRemoteCount );
	m_wndDebugCount.SetWindowText( csMsg );

	// Avg Spend Time
	csMsg.Format("%8.5f secs", 
		(( m.DebugError.ReadRemoteSpendTime / m.DebugError.ReadRemoteCount )) / 1000. );
	m_wndDebugAvg.SetWindowText( csMsg );
#endif
}
void CDlgIOMontiorRemote::IOQuery()
{
	// light
	m_ledOutStop		= m.RemoteOutStatus.BtnStopOn		== 0 ? false : true;
	m_ledOutStart		= m.RemoteOutStatus.BtnStartOn 		== 0 ? false : true;
	m_ledOutSkip		= m.RemoteOutStatus.BtnSkipOn		== 0 ? false : true;
	m_ledOutRetry		= m.RemoteOutStatus.BtnRetryOn		== 0 ? false : true;
	m_ledOutReset		= m.RemoteOutStatus.BtnResetOn 		== 0 ? false : true;
	m_ledOutOneCycle	= m.RemoteOutStatus.BtnOneCycleOn	== 0 ? false : true;
	m_ledOutInitial		= m.RemoteOutStatus.BtnInitialOn 	== 0 ? false : true;

	// Push
	m_ledPInStop		= m.RemoteInStatus.BtnStopPushed 	== 0 ? false : true;
	m_ledPInStart		= m.RemoteInStatus.BtnStartPushed 	== 0 ? false : true;
	m_ledPInSkip		= m.RemoteInStatus.BtnSkipPushed 	== 0 ? false : true;
	m_ledPInRetry		= m.RemoteInStatus.BtnRetryPushed 	== 0 ? false : true;
	m_ledPInReset		= m.RemoteInStatus.BtnResetPushed 	== 0 ? false : true;
	m_ledPInOneCycle	= m.RemoteInStatus.BtnOneCyclePushed== 0 ? false : true;
	m_ledPInInitial		= m.RemoteInStatus.BtnInitialPushed == 0 ? false : true;
}
void CDlgIOMontiorRemote::SetOnlyShow(bool bOnlyShow)
{
	m_bOnlyShow = bOnlyShow;
}
void CDlgIOMontiorRemote::ReDrawUI()
{

}

void CDlgIOMontiorRemote::OnTimer(UINT nIDEvent) 
{
	switch(nIDEvent)
	{
	case ID_TIME_GET_STATUS:
		{
			IOQuery();
			IODebug();
		}
		break;
	}		
	CDialog::OnTimer(nIDEvent);
}

void CDlgIOMontiorRemote::OnLedPOutStart() 
{
	if(m_bOnlyShow)
		return;
	
	m.RemoteOutSet.BtnStartOn = !m.RemoteOutStatus.BtnStartOn;
}

void CDlgIOMontiorRemote::OnLedPOutOnecycle() 
{
	if(m_bOnlyShow)
		return;

	m.RemoteOutSet.BtnOneCycleOn = !m.RemoteOutSet.BtnOneCycleOn;
}

void CDlgIOMontiorRemote::OnLedPOutStop() 
{
	if(m_bOnlyShow)
		return;

	m.RemoteOutSet.BtnStopOn = !m.RemoteOutSet.BtnStopOn;
}

void CDlgIOMontiorRemote::OnLedPOutReset() 
{
	if(m_bOnlyShow)
		return;

	m.RemoteOutSet.BtnResetOn = !m.RemoteOutSet.BtnResetOn;
}

void CDlgIOMontiorRemote::OnLedPOutSkip() 
{
	if(m_bOnlyShow)
		return;

	m.RemoteOutSet.BtnSkipOn = !m.RemoteOutSet.BtnSkipOn;
}

void CDlgIOMontiorRemote::OnLedPOutRetry() 
{
	if(m_bOnlyShow)
		return;

	m.RemoteOutSet.BtnRetryOn = !m.RemoteOutSet.BtnRetryOn;
}

void CDlgIOMontiorRemote::OnLedPOutInitial() 
{
	if(m_bOnlyShow)
		return;

	m.RemoteOutSet.BtnInitialOn = !m.RemoteOutSet.BtnInitialOn;
}

void CDlgIOMontiorRemote::OnStaticDebug() 
{	
	m_bShowEnable = !m_bShowEnable;
	m_wndDebugGroup.ShowWindow( m_bShowEnable );
}
