// DlgVisualButton.cpp : implementation file
//

#include "stdafx.h"
#include "Deer.h"
#include "DlgVisualButton.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgVisualButton dialog


CDlgVisualButton::CDlgVisualButton(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgVisualButton::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgVisualButton)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgVisualButton::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgVisualButton)
	//
	DDX_Control(pDX, IDC_WARM,				m_wndMainMsg);
	//
	DDX_Control(pDX, IDOK,					m_btnOK);
	DDX_Control(pDX, IDCANCEL,				m_btnCancel);
	//
	DDX_Control(pDX, IDC_STOP_LED,			m_wndStop);
	DDX_Control(pDX, IDC_START_LED,			m_wndStart);
	DDX_Control(pDX, IDC_SKIP_LED,			m_wndSkip);
	DDX_Control(pDX, IDC_RETRY_LED,			m_wndRetry);
	DDX_Control(pDX, IDC_ONE_CYCLE_LED,		m_wndOneCycle);
	DDX_Control(pDX, IDC_INITIAL_LED,		m_wndInitial);
	DDX_Control(pDX, IDC_RESET_LED,			m_wndReset);
	//
	DDX_Control(pDX, IDC_TOWNER_RED,		m_wndTownerRed);
	DDX_Control(pDX, IDC_TOWNER_YELLOW,		m_wndTownerYellow);
	DDX_Control(pDX, IDC_TOWNER_GREEN,		m_wndTownerGreen);
	DDX_Control(pDX, IDC_TOWNER_BUZZER,		m_wndTownerBuzzer);
	//
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDlgVisualButton, CDialog)
	//{{AFX_MSG_MAP(CDlgVisualButton)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_START,		OnStart)
	ON_BN_CLICKED(IDC_STOP,			OnStop)
	ON_BN_CLICKED(IDC_RETRY,		OnRetry)
	ON_BN_CLICKED(IDC_SKIP,			OnSkip)
	ON_BN_CLICKED(IDC_INITIAL,		OnInitial)
	ON_BN_CLICKED(IDC_FLUSH,		OnFlush)
	ON_BN_CLICKED(IDC_RESET,		OnReset)	
	//
	ON_WM_SHOWWINDOW()

	//}}AFX_MSG_MAP

END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgVisualButton message handlers

BOOL CDlgVisualButton::OnInitDialog() 
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

	m_wndMainMsg.SetNewBkColor(ST_RED);
	m_wndMainMsg.SetNewTextColor(ST_WHITE);
	m_wndMainMsg.SetText("Please Make Sure, Handler Area Is Clear.!", 14, "Arial Black", DT_CENTER | DT_VCENTER);
	
	// if new panel OK
	// if not new panel. uvisable some buttone

	SetTimer(ID_TIME_BUTTON, 10, NULL);	// 更新畫面可以不用很快, 但是按鈕要快一點
	
	f.ChangeLanguage(GetSafeHwnd());
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgVisualButton::OnTimer(UINT nIDEvent) 
{
	switch(nIDEvent)
	{
	case ID_TIME_BUTTON:
		UpdateDisplay();	
		break;
	default:
		break;
	}
	CDialog::OnTimer(nIDEvent);
}
void CDlgVisualButton::UpdateDisplay()
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

bool CDlgVisualButton::CheckSafe()
{
	// Note: if Door sensor be disable. return false;
	// if Door sensor be enable. return true.

	bool bOK = false;
	if( m.Setting.m_bEnableDoorSensor == 1 )
	{
		CString csMsg = _T("");
		csMsg.Format(" Please enable the door sensor .!");
		AfxMessageBox( csMsg );
		bOK = false;
	}
	else 
		bOK = true;

	return bOK;
}

///////////////////////////////////////////////////////////////////////////////
// Button
void CDlgVisualButton::OnInitial() 
{
	if(!CheckSafe())
		return;

	m.PanelButton.BtnInitPushed = true;
}
void CDlgVisualButton::OnStart() 
{
	if(!CheckSafe())
		return;

	m.PanelButton.BtnStartPushed = true;   
}
void CDlgVisualButton::OnFlush()
{
	if(!CheckSafe())
		return;

	m.PanelButton.BtnOneCyclePushed = true;
}
void CDlgVisualButton::OnSkip()
{
	// Skip / Retry / Stop No need
	m.PanelButton.BtnSkipPushed = true;
}
void CDlgVisualButton::OnRetry()
{
	// Skip / Retry / Stop No need
	m.PanelButton.BtnRetryPushed = true;
}
void CDlgVisualButton::OnStop()
{
	// Skip / Retry / Stop No need
	m.PanelButton.BtnStopPushed = true;
}

void CDlgVisualButton::OnOK() 
{
	KillTimer(ID_TIME_BUTTON);

	CDialog::OnOK();
}

void CDlgVisualButton::OnReset()
{
	// Skip / Retry / Stop No need
	m.PanelButton.BtnResetPushed = true;
}

// Dialog.
void CDlgVisualButton::OnCancel() 
{
	KillTimer(ID_TIME_BUTTON);

	CDialog::OnCancel();
}

void CDlgVisualButton::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);
	
	KillTimer(ID_TIME_BUTTON);
	// 開啟後再設一次 Timer
	SetTimer(ID_TIME_BUTTON, 300, NULL);	// 更新畫面可以不用很快, 但是按鈕要快一點
}

BOOL CDlgVisualButton::PreTranslateMessage(MSG* pMsg) 
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

