// DlgTowerSetting.cpp : implementation file
//

#include "stdafx.h"
#include "deer.h"
#include "DlgTowerSetting.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgTowerSetting dialog


CDlgTowerSetting::CDlgTowerSetting(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgTowerSetting::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgTowerSetting)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	m_TowerSetupSetting = m.m_TowerSetupSetting;
}


void CDlgTowerSetting::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgTowerSetting)
	DDX_Control(pDX, IDC_C_READY_YELLOW,			m_btnReadyYellow);
	DDX_Control(pDX, IDC_C_READY_RED,				m_btnReadyRed);
	DDX_Control(pDX, IDC_C_READY_GREEN,				m_btnReadyGreen);
	DDX_Control(pDX, IDC_C_OVERRIDE_STOP_YELLOW,	m_btnOverrideStopYellow);
	DDX_Control(pDX, IDC_C_OVERRIDE_STOP_RED,		m_btnOverrideStopRed);
	DDX_Control(pDX, IDC_C_OVERRIDE_STOP_GREEN,		m_btnOverrideStopGreen);
	DDX_Control(pDX, IDC_C_OVERRIDE_YELLOW,			m_btnOverrideYellow);
	DDX_Control(pDX, IDC_C_OVERRIDE_RED,			m_btnOverrideRed);
	DDX_Control(pDX, IDC_C_OVERRIDE_GREEN,			m_btnOverrideGreen);
	DDX_Control(pDX, IDC_C_ONE_CYCLE_STOP_YELLOW,	m_btnOneCycleStopYellow);
	DDX_Control(pDX, IDC_C_ONE_CYCLE_STOP_RED,		m_btnOneCycleStopRed);
	DDX_Control(pDX, IDC_C_ONE_CYCLE_STOP_GREEN,	m_btnOneCycleStopGreen);
	DDX_Control(pDX, IDC_C_ONE_CYCLE_YELLOW,		m_btnOneCycleYellow);
	DDX_Control(pDX, IDC_C_ONE_CYCLE_RED,			m_btnOneCycleRed);
	DDX_Control(pDX, IDC_C_ONE_CYCLE_GREEN,			m_btnOneCycleGreen);
	DDX_Control(pDX, IDC_C_MANUAL_STOP_YELLOW,		m_btnManualStopYellow);
	DDX_Control(pDX, IDC_C_MANUAL_STOP_RED,			m_btnManualStopRed);
	DDX_Control(pDX, IDC_C_MANUAL_STOP_GREEN,		m_btnManualStopGreen);
	DDX_Control(pDX, IDC_C_MANUAL_YELLOW,			m_btnManualYellow);
	DDX_Control(pDX, IDC_C_MANUAL_RED,				m_btnManualRed);
	DDX_Control(pDX, IDC_C_MANUAL_GREEN,			m_btnManualGreen);
	DDX_Control(pDX, IDC_C_INITIAL_YELLOW,			m_btnInitialYellow);
	DDX_Control(pDX, IDC_C_INITIAL_RED,				m_btnInitialRed);
	DDX_Control(pDX, IDC_C_INITIAL_GREEN,			m_btnInitialGreen);
	DDX_Control(pDX, IDC_C_CYCLE_STOP_YELLOW,		m_btnCycleStopYellow);
	DDX_Control(pDX, IDC_C_CYCLE_STOP_RED,			m_btnCycleStopRed);
	DDX_Control(pDX, IDC_C_CYCLE_STOP_GREEN,		m_btnCycleStopGreen);
	DDX_Control(pDX, IDC_C_CYCLE_YELLOW,			m_btnCycleYellow);
	DDX_Control(pDX, IDC_C_CYCLE_RED,				m_btnCycleRed);
	DDX_Control(pDX, IDC_C_CYCLE_GREEN,				m_btnCycleGreen);
	DDX_Control(pDX, IDC_C_UNINITIAL_GREEN,			m_btnUninitialGreen);
	DDX_Control(pDX, IDC_C_UNINITIAL_YELLOW,		m_btnUninitialYellow);
	DDX_Control(pDX, IDC_C_UNINITIAL_RED,			m_btnUninitialRed);
	DDX_Control(pDX, IDC_C_BLINK_TIME,				m_wndBlinkTime);
	DDX_Control(pDX, IDC_C_BLINK_LIST,				m_coBlinkList);
	DDX_Control(pDX, IDC_T_GREEN,					m_wndTowerGreen);
	DDX_Control(pDX, IDC_T_YELLOW,					m_wndTowerYellow);
	DDX_Control(pDX, IDC_T_RED,						m_wndTowerRed);
	DDX_Control(pDX, IDCANCEL,						m_btnCancel);
	DDX_Control(pDX, IDOK,							m_btnOK);
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgTowerSetting, CDialog)
	//{{AFX_MSG_MAP(CDlgTowerSetting)
	ON_BN_CLICKED(IDC_C_SET_BLINK,					OnCSetBlink)
	ON_CBN_SELCHANGE(IDC_C_BLINK_LIST,				OnSelchangeCBlinkList)
	ON_BN_CLICKED(IDC_C_UNINITIAL_RED,				OnCUninitialRed)
	ON_BN_CLICKED(IDC_C_UNINITIAL_YELLOW,			OnCUninitialYellow)
	ON_BN_CLICKED(IDC_C_UNINITIAL_GREEN,			OnCUninitialGreen)
	ON_BN_CLICKED(IDC_C_INITIAL_RED,				OnCInitialRed)
	ON_BN_CLICKED(IDC_C_INITIAL_YELLOW,				OnCInitialYellow)
	ON_BN_CLICKED(IDC_C_INITIAL_GREEN,				OnCInitialGreen)
	ON_BN_CLICKED(IDC_C_READY_RED,					OnCReadyRed)
	ON_BN_CLICKED(IDC_C_READY_YELLOW,				OnCReadyYellow)
	ON_BN_CLICKED(IDC_C_READY_GREEN,				OnCReadyGreen)
	ON_BN_CLICKED(IDC_C_CYCLE_RED,					OnCCycleRed)
	ON_BN_CLICKED(IDC_C_CYCLE_YELLOW,				OnCCycleYellow)
	ON_BN_CLICKED(IDC_C_CYCLE_GREEN,				OnCCycleGreen)
	ON_BN_CLICKED(IDC_C_CYCLE_STOP_RED,				OnCCycleStopRed)
	ON_BN_CLICKED(IDC_C_CYCLE_STOP_YELLOW,			OnCCycleStopYellow)
	ON_BN_CLICKED(IDC_C_CYCLE_STOP_GREEN,			OnCCycleStopGreen)
	ON_BN_CLICKED(IDC_C_ONE_CYCLE_RED,				OnCOneCycleRed)
	ON_BN_CLICKED(IDC_C_ONE_CYCLE_YELLOW,			OnCOneCycleYellow)
	ON_BN_CLICKED(IDC_C_ONE_CYCLE_GREEN,			OnCOneCycleGreen)
	ON_BN_CLICKED(IDC_C_ONE_CYCLE_STOP_RED,			OnCOneCycleStopRed)
	ON_BN_CLICKED(IDC_C_ONE_CYCLE_STOP_YELLOW,		OnCOneCycleStopYellow)
	ON_BN_CLICKED(IDC_C_ONE_CYCLE_STOP_GREEN,		OnCOneCycleStopGreen)
	ON_BN_CLICKED(IDC_C_OVERRIDE_RED,				OnCOverrideRed)
	ON_BN_CLICKED(IDC_C_OVERRIDE_YELLOW,			OnCOverrideYellow)
	ON_BN_CLICKED(IDC_C_OVERRIDE_GREEN,				OnCOverrideGreen)
	ON_BN_CLICKED(IDC_C_OVERRIDE_STOP_RED,			OnCOverrideStopRed)
	ON_BN_CLICKED(IDC_C_OVERRIDE_STOP_YELLOW,		OnCOverrideStopYellow)
	ON_BN_CLICKED(IDC_C_OVERRIDE_STOP_GREEN,		OnCOverrideStopGreen)
	ON_BN_CLICKED(IDC_C_MANUAL_RED,					OnCManualRed)
	ON_BN_CLICKED(IDC_C_MANUAL_YELLOW,				OnCManualYellow)
	ON_BN_CLICKED(IDC_C_MANUAL_GREEN,				OnCManualGreen)
	ON_BN_CLICKED(IDC_C_MANUAL_STOP_RED,			OnCManualStopRed)
	ON_BN_CLICKED(IDC_C_MANUAL_STOP_YELLOW,			OnCManualStopYellow)
	ON_BN_CLICKED(IDC_C_MANUAL_STOP_GREEN,			OnCManualStopGreen)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgTowerSetting message handlers

BOOL CDlgTowerSetting::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m.Info.bSubDlgOpen = true;
	f.UpdateButtonState();
	
	// init button 
	m_btnOK.SetIcon(IDI_SAVE);;
	m_btnOK.SetAlign(CButtonST::ST_ALIGN_VERT);;
	m_btnOK.SetFlat(FALSE);
	
	m_btnCancel.SetIcon(IDI_CANCEL);
	m_btnCancel.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnCancel.SetFlat(FALSE);

	//
	InitUI();

	//
	InitTips();

	//
	InitBlink();

	//
	InitValue();

	//
	f.SetTitleExtend(this, theApp.enTtileMachineFile );
	
	//
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
void CDlgTowerSetting::InitUI()
{
	m_wndTowerRed.SetNewBkColor(ST_RED);
	m_wndTowerRed.SetText("Red", 12, "Arial Black", DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	m_wndTowerYellow.SetNewBkColor(ST_YELLOW);
	m_wndTowerYellow.SetText("Yellow", 12, "Arial Black", DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	m_wndTowerGreen.SetNewBkColor(ST_GREEN);
	m_wndTowerGreen.SetText("Green", 12, "Arial Black", DT_CENTER | DT_VCENTER | DT_SINGLELINE);
}
void CDlgTowerSetting::InitBlink()
{
	for(int i=0;i<_MaxTowerBlink;i++)
	{
		CString csMsg = _T("");
		csMsg.Format("%s %.2d", _MaxTowerDesc, i+1);
		m_coBlinkList.AddString(csMsg);
	}
	m_coBlinkList.SetCurSel(0);
}
void CDlgTowerSetting::InitTips()
{
	// Init Tips
	m_ToolTip.Create(this);
	m_ToolTip.SetMaxTipWidth(800);
	m_ToolTip.SetDelayTime( TTDT_AUTOPOP, 10000 );
	m_ToolTip.SetDelayTime( TTDT_INITIAL, 25 );
	m_ToolTip.EnableToolTips(true);

	m_ToolTip.AddTool( GetDlgItem(IDC_STATIC_UNINITIAL),	
		_T("Uninitial-Handler power on\n") );
	m_ToolTip.AddTool( GetDlgItem(IDC_STATIC_INITIAL),		
		_T("Initial-Handler try to find the work position\n") );
	m_ToolTip.AddTool( GetDlgItem(IDC_STATIC_READY),		
		_T("Ready-Handler complete initial\nWait for operation") );
	m_ToolTip.AddTool( GetDlgItem(IDC_STATIC_CYCLE),		
		_T("Cycle-Handler in operationing") );
	m_ToolTip.AddTool( GetDlgItem(IDC_STATIC_CYCLE_STOP),	
		_T("Cycle-Handler operation stop\nWait for operation") );
	m_ToolTip.AddTool( GetDlgItem(IDC_STATIC_ONE_CYCLE),	
		_T("One Cycle-Handler clear all ic with all position\n") );
	m_ToolTip.AddTool( GetDlgItem(IDC_STATIC_ONE_CYCLE_STOP),	
		_T("One Cycle-Handler clear all ic with all position\nOperation stop\nWait for operation") );
	m_ToolTip.AddTool( GetDlgItem(IDC_STATIC_OVERRIDE),	
		_T("Override-Handler clear all ic with all position(heating)\nOperation stop\nWait for operation") );
	m_ToolTip.AddTool( GetDlgItem(IDC_STATIC_OVERRIDE_STOP),	
		_T("Override Stop-Handler clear all ic with all position(heating)\nOperation stop\nWait for operation") );
	m_ToolTip.AddTool( GetDlgItem(IDC_STATIC_MANUAL),	
		_T("Manual-Handler manual operation") );
	m_ToolTip.AddTool( GetDlgItem(IDC_STATIC_MANUAL_STOP),	
		_T("Manual-Handler manual operation stop") );

}
bool CDlgTowerSetting::SaveData()
{
	m.m_TowerSetupSetting = m_TowerSetupSetting;

	f.SavetowerSetting();

	return true;
}
void CDlgTowerSetting::InitValue()
{
	// Blink
	m_coBlinkList.SetCurSel(0);
	double dBlink = 0.0;
	CString csBlink = _T("");	

	dBlink = m_TowerSetupSetting.dBlinkTime[0];
	csBlink.Format("%5.2f", dBlink);
	csBlink.TrimLeft();
	csBlink.TrimRight();
	m_wndBlinkTime.SetWindowText(csBlink);

	// Tower Setting
	// Uninitial 
	SetChoiseTitle( m_btnUninitialRed, m_TowerSetupSetting.Uninitial.LightRedChoise );				// Red
	SetChoiseTitle( m_btnUninitialYellow, m_TowerSetupSetting.Uninitial.LightYellowChoise );		// Yellow
	SetChoiseTitle( m_btnUninitialGreen, m_TowerSetupSetting.Uninitial.LightGreenChoise );			// Green

	// Initial
	SetChoiseTitle( m_btnInitialRed, m_TowerSetupSetting.Initial.LightRedChoise );					// Red
	SetChoiseTitle( m_btnInitialYellow, m_TowerSetupSetting.Initial.LightYellowChoise );			// Yellow
	SetChoiseTitle( m_btnInitialGreen, m_TowerSetupSetting.Initial.LightGreenChoise );				// Green

	// Ready 
	SetChoiseTitle( m_btnReadyRed, m_TowerSetupSetting.Ready.LightRedChoise );						// Red
	SetChoiseTitle( m_btnReadyYellow, m_TowerSetupSetting.Ready.LightYellowChoise );				// Yellow
	SetChoiseTitle( m_btnReadyGreen, m_TowerSetupSetting.Ready.LightGreenChoise );					// Green

	// Cycle 
	SetChoiseTitle( m_btnCycleRed, m_TowerSetupSetting.Cycle.LightRedChoise );						// Red
	SetChoiseTitle( m_btnCycleYellow, m_TowerSetupSetting.Cycle.LightYellowChoise );				// Yellow
	SetChoiseTitle( m_btnCycleGreen, m_TowerSetupSetting.Cycle.LightGreenChoise );					// Green

	// Cycle Stop
	SetChoiseTitle( m_btnCycleStopRed, m_TowerSetupSetting.CycleStop.LightRedChoise );				// Red
	SetChoiseTitle( m_btnCycleStopYellow, m_TowerSetupSetting.CycleStop.LightYellowChoise );		// Yellow
	SetChoiseTitle( m_btnCycleStopGreen, m_TowerSetupSetting.CycleStop.LightGreenChoise );			// Green

	// One Cycle 
	SetChoiseTitle( m_btnOneCycleRed, m_TowerSetupSetting.OneCycle.LightRedChoise );				// Red
	SetChoiseTitle( m_btnOneCycleYellow, m_TowerSetupSetting.OneCycle.LightYellowChoise );			// Yellow
	SetChoiseTitle( m_btnOneCycleGreen, m_TowerSetupSetting.OneCycle.LightGreenChoise );			// Green

	// One Cycle Stop
	SetChoiseTitle( m_btnOneCycleStopRed, m_TowerSetupSetting.OneCycleStop.LightRedChoise );		// Red
	SetChoiseTitle( m_btnOneCycleStopYellow, m_TowerSetupSetting.OneCycleStop.LightYellowChoise );	// Yellow
	SetChoiseTitle( m_btnOneCycleStopGreen, m_TowerSetupSetting.OneCycleStop.LightGreenChoise );	// Green

	// Override
	SetChoiseTitle( m_btnOverrideRed, m_TowerSetupSetting.Override.LightRedChoise );				// Red
	SetChoiseTitle( m_btnOverrideYellow, m_TowerSetupSetting.Override.LightYellowChoise );			// Yellow
	SetChoiseTitle( m_btnOverrideGreen, m_TowerSetupSetting.Override.LightGreenChoise );			// Green

	// Override Stop
	SetChoiseTitle( m_btnOverrideStopRed, m_TowerSetupSetting.OverrideStop.LightRedChoise );		// Red
	SetChoiseTitle( m_btnOverrideStopYellow, m_TowerSetupSetting.OverrideStop.LightYellowChoise );	// Yellow
	SetChoiseTitle( m_btnOverrideStopGreen, m_TowerSetupSetting.OverrideStop.LightGreenChoise );	// Green

	// Manual 
	SetChoiseTitle( m_btnManualRed, m_TowerSetupSetting.Manual.LightRedChoise );					// Red	
	SetChoiseTitle( m_btnManualYellow, m_TowerSetupSetting.Manual.LightYellowChoise );				// Yellow
	SetChoiseTitle( m_btnManualGreen, m_TowerSetupSetting.Manual.LightGreenChoise );				// Green

	// Manual Stop
	SetChoiseTitle( m_btnManualStopRed, m_TowerSetupSetting.ManualStop.LightRedChoise );			// Red
	SetChoiseTitle( m_btnManualStopYellow, m_TowerSetupSetting.ManualStop.LightYellowChoise );		// Yellow
	SetChoiseTitle( m_btnManualStopGreen, m_TowerSetupSetting.ManualStop.LightGreenChoise );		// Green
}
bool CDlgTowerSetting::CheckValue()
{
	bool bOK = true;

//	if( _MinTowerBlinkTime

	return bOK;
} 
BOOL CDlgTowerSetting::PreTranslateMessage(MSG* pMsg) 
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

void CDlgTowerSetting::OnOK() 
{
	//
	SaveData();

	//
	m.Info.bSubDlgOpen = false;
	f.UpdateButtonState();
	
	CDialog::OnOK();
}

void CDlgTowerSetting::OnCancel() 
{
	m.Info.bSubDlgOpen = false;
	f.UpdateButtonState();
	
	CDialog::OnCancel();
}
void CDlgTowerSetting::OnCSetBlink() 
{
	int iSel = m_coBlinkList.GetCurSel();
	CString csValue = _T("");
	m_wndBlinkTime.GetWindowText( csValue );
	csValue.TrimLeft();
	csValue.TrimRight();

	double dBlink = 0.0;
	dBlink = atof( csValue );

	if( dBlink > _MaxTowerBlinkTime || dBlink < _MinTowerBlinkTime )
	{
		CString csErr = _T("");
		csErr.Format("out of range, [%5.2f~%5.2f", _MinTowerBlinkTime, _MaxTowerBlinkTime );
		AfxMessageBox( csErr );
		return;
	}

	m_TowerSetupSetting.dBlinkTime[iSel] = dBlink;
}

void CDlgTowerSetting::OnSelchangeCBlinkList() 
{
	int iSel = m_coBlinkList.GetCurSel();
	
	// Debug 
	CString csMsg = _T("");
	csMsg.Format("Blink: %d\n", iSel);
	TRACE(csMsg);

	//
	double dBlink = 0.0;
	dBlink = m_TowerSetupSetting.dBlinkTime[iSel];
	CString csBlink = _T("");
	csBlink.Format("%5.2f", dBlink);
	csBlink.TrimLeft();
	csBlink.TrimRight();
	m_wndBlinkTime.SetWindowText(csBlink);
}
void CDlgTowerSetting::SetCtrlColor(CButtonST &ctrl, COLORREF cc)
{
	ctrl.SetColor(CButtonST::BTNST_COLOR_BK_IN, cc);
	ctrl.SetColor(CButtonST::BTNST_COLOR_BK_OUT, cc);
	ctrl.SetColor(CButtonST::BTNST_COLOR_BK_FOCUS, cc);
	ctrl.SetColor(CButtonST::BTNST_COLOR_FG_IN, (~cc & 0xFFFFFF));
	ctrl.SetColor(CButtonST::BTNST_COLOR_FG_OUT, (~cc & 0xFFFFFF));
	ctrl.SetColor(CButtonST::BTNST_COLOR_FG_FOCUS, (~cc & 0xFFFFFF));
}
void CDlgTowerSetting::SetChoiseTitle(CButtonST &ctrl, int iChoise)
{
	CString csTitle = _T("");
	if( iChoise == theApp.enTowerChoiseDisable )
		csTitle.Format("%s", _TowerLightOff );
	else if( iChoise == theApp.enTowerChoiseEnable )
		csTitle.Format("%s", _TowerLightOn );
	else if( iChoise == theApp.enTowerChoiseBlink1 )
		csTitle.Format("%s", _TowerLightBlink1 );
	else if( iChoise == theApp.enTowerChoiseBlink2 )
		csTitle.Format("%s", _TowerLightBlink2 );
	else if( iChoise == theApp.enTowerChoiseBlink3 )
		csTitle.Format("%s", _TowerLightBlink3 );
	else if( iChoise == theApp.enTowerChoiseBlink4 )
		csTitle.Format("%s", _TowerLightBlink4 );
	else if( iChoise == theApp.enTowerChoiseBlink5 )
		csTitle.Format("%s", _TowerLightBlink5 );
	else
	{
		// Nerver be here
	}

	//
	ctrl.SetWindowText( csTitle );
}

void CDlgTowerSetting::NextChoise(int &iChoise)
{
/*
	enTowerChoiseDisable	= 0,
	enTowerChoiseEnable		= 1,
	enTowerChoiseBlink1		= 2,
	enTowerChoiseBlink2		= 3,
	enTowerChoiseBlink3		= 4,
	enTowerChoiseBlink4		= 5,
	enTowerChoiseBlink5		= 6,
*/
	if( iChoise == theApp.enTowerChoiseDisable )
		iChoise = theApp.enTowerChoiseEnable;
	else if( iChoise == theApp.enTowerChoiseEnable )
		iChoise = theApp.enTowerChoiseBlink1;
	else if( iChoise == theApp.enTowerChoiseBlink1 )
		iChoise = theApp.enTowerChoiseBlink2;
	else if( iChoise == theApp.enTowerChoiseBlink2 )
		iChoise = theApp.enTowerChoiseBlink3;
	else if( iChoise == theApp.enTowerChoiseBlink3 )
		iChoise = theApp.enTowerChoiseBlink4;
	else if( iChoise == theApp.enTowerChoiseBlink4 )
		iChoise = theApp.enTowerChoiseBlink5;
	else if( iChoise == theApp.enTowerChoiseBlink5 )
		iChoise = theApp.enTowerChoiseDisable;
	else
		; // Nerver be here
}

// Button - Uninitial
void CDlgTowerSetting::OnCUninitialRed() 
{
	NextChoise( m_TowerSetupSetting.Uninitial.LightRedChoise );
	SetChoiseTitle( m_btnUninitialRed, m_TowerSetupSetting.Uninitial.LightRedChoise );
}
void CDlgTowerSetting::OnCUninitialYellow() 
{
	NextChoise( m_TowerSetupSetting.Uninitial.LightYellowChoise );
	SetChoiseTitle( m_btnUninitialYellow, m_TowerSetupSetting.Uninitial.LightYellowChoise );
}
void CDlgTowerSetting::OnCUninitialGreen() 
{
	NextChoise( m_TowerSetupSetting.Uninitial.LightGreenChoise );
	SetChoiseTitle( m_btnUninitialGreen, m_TowerSetupSetting.Uninitial.LightGreenChoise );	
}
// Button - Initial
void CDlgTowerSetting::OnCInitialRed() 
{
	NextChoise( m_TowerSetupSetting.Initial.LightRedChoise );
	SetChoiseTitle( m_btnInitialRed, m_TowerSetupSetting.Initial.LightRedChoise );
}
void CDlgTowerSetting::OnCInitialYellow() 
{
	NextChoise( m_TowerSetupSetting.Initial.LightYellowChoise );
	SetChoiseTitle( m_btnInitialYellow, m_TowerSetupSetting.Initial.LightYellowChoise );	
}
void CDlgTowerSetting::OnCInitialGreen() 
{
	NextChoise( m_TowerSetupSetting.Initial.LightGreenChoise );
	SetChoiseTitle( m_btnInitialGreen, m_TowerSetupSetting.Initial.LightGreenChoise );		
}
// Button - Ready
void CDlgTowerSetting::OnCReadyRed() 
{
	NextChoise( m_TowerSetupSetting.Ready.LightRedChoise );
	SetChoiseTitle( m_btnReadyRed, m_TowerSetupSetting.Ready.LightRedChoise );
}
void CDlgTowerSetting::OnCReadyYellow() 
{
	NextChoise( m_TowerSetupSetting.Ready.LightYellowChoise );
	SetChoiseTitle( m_btnReadyYellow, m_TowerSetupSetting.Ready.LightYellowChoise );	
}
void CDlgTowerSetting::OnCReadyGreen() 
{
	NextChoise( m_TowerSetupSetting.Ready.LightGreenChoise );
	SetChoiseTitle( m_btnReadyGreen, m_TowerSetupSetting.Ready.LightGreenChoise );		
}
// Button - Cycle
void CDlgTowerSetting::OnCCycleRed() 
{
	NextChoise( m_TowerSetupSetting.Cycle.LightRedChoise );
	SetChoiseTitle( m_btnCycleRed, m_TowerSetupSetting.Cycle.LightRedChoise );
}
void CDlgTowerSetting::OnCCycleYellow() 
{
	NextChoise( m_TowerSetupSetting.Cycle.LightYellowChoise );
	SetChoiseTitle( m_btnCycleYellow, m_TowerSetupSetting.Cycle.LightYellowChoise );	
}
void CDlgTowerSetting::OnCCycleGreen() 
{
	NextChoise( m_TowerSetupSetting.Cycle.LightGreenChoise );
	SetChoiseTitle( m_btnCycleGreen, m_TowerSetupSetting.Cycle.LightGreenChoise );	
}
// Button - Cycle Stop
void CDlgTowerSetting::OnCCycleStopRed() 
{
	NextChoise( m_TowerSetupSetting.CycleStop.LightRedChoise );
	SetChoiseTitle( m_btnCycleStopRed, m_TowerSetupSetting.CycleStop.LightRedChoise );
}
void CDlgTowerSetting::OnCCycleStopYellow() 
{
	NextChoise( m_TowerSetupSetting.CycleStop.LightYellowChoise );
	SetChoiseTitle( m_btnCycleStopYellow, m_TowerSetupSetting.CycleStop.LightYellowChoise );	
}
void CDlgTowerSetting::OnCCycleStopGreen() 
{
	NextChoise( m_TowerSetupSetting.CycleStop.LightGreenChoise );
	SetChoiseTitle( m_btnCycleStopGreen, m_TowerSetupSetting.CycleStop.LightGreenChoise );		
}
// Button - OneCycle
void CDlgTowerSetting::OnCOneCycleRed() 
{
	NextChoise( m_TowerSetupSetting.OneCycle.LightRedChoise );
	SetChoiseTitle( m_btnOneCycleRed, m_TowerSetupSetting.OneCycle.LightRedChoise );
}
void CDlgTowerSetting::OnCOneCycleYellow() 
{
	NextChoise( m_TowerSetupSetting.OneCycle.LightYellowChoise );
	SetChoiseTitle( m_btnOneCycleYellow, m_TowerSetupSetting.OneCycle.LightYellowChoise );	
}
void CDlgTowerSetting::OnCOneCycleGreen() 
{
	NextChoise( m_TowerSetupSetting.OneCycle.LightGreenChoise );
	SetChoiseTitle( m_btnOneCycleGreen, m_TowerSetupSetting.OneCycle.LightGreenChoise );	
}
// Button - OneCycleStop
void CDlgTowerSetting::OnCOneCycleStopRed() 
{
	NextChoise( m_TowerSetupSetting.OneCycleStop.LightRedChoise );
	SetChoiseTitle( m_btnOneCycleStopRed, m_TowerSetupSetting.OneCycleStop.LightRedChoise );
}
void CDlgTowerSetting::OnCOneCycleStopYellow() 
{
	NextChoise( m_TowerSetupSetting.OneCycleStop.LightYellowChoise );
	SetChoiseTitle( m_btnOneCycleStopYellow, m_TowerSetupSetting.OneCycleStop.LightYellowChoise );	
}
void CDlgTowerSetting::OnCOneCycleStopGreen() 
{
	NextChoise( m_TowerSetupSetting.OneCycleStop.LightGreenChoise );
	SetChoiseTitle( m_btnOneCycleStopGreen, m_TowerSetupSetting.OneCycleStop.LightGreenChoise );	
}
// Button - Override
void CDlgTowerSetting::OnCOverrideRed() 
{
	NextChoise( m_TowerSetupSetting.Override.LightRedChoise );
	SetChoiseTitle( m_btnOverrideRed, m_TowerSetupSetting.Override.LightRedChoise );
}
void CDlgTowerSetting::OnCOverrideYellow() 
{
	NextChoise( m_TowerSetupSetting.Override.LightYellowChoise );
	SetChoiseTitle( m_btnOverrideYellow, m_TowerSetupSetting.Override.LightYellowChoise );	
}
void CDlgTowerSetting::OnCOverrideGreen() 
{
	NextChoise( m_TowerSetupSetting.Override.LightGreenChoise );
	SetChoiseTitle( m_btnOverrideGreen, m_TowerSetupSetting.Override.LightGreenChoise );	
}
// Button - Override Stop
void CDlgTowerSetting::OnCOverrideStopRed() 
{
	NextChoise( m_TowerSetupSetting.OverrideStop.LightRedChoise );
	SetChoiseTitle( m_btnOverrideStopRed, m_TowerSetupSetting.OverrideStop.LightRedChoise );	
}
void CDlgTowerSetting::OnCOverrideStopYellow() 
{
	NextChoise( m_TowerSetupSetting.OverrideStop.LightYellowChoise );
	SetChoiseTitle( m_btnOverrideStopYellow, m_TowerSetupSetting.OverrideStop.LightYellowChoise );		
}
void CDlgTowerSetting::OnCOverrideStopGreen() 
{
	NextChoise( m_TowerSetupSetting.OverrideStop.LightGreenChoise );
	SetChoiseTitle( m_btnOverrideStopGreen, m_TowerSetupSetting.OverrideStop.LightGreenChoise );	
}
// Button - Manual
void CDlgTowerSetting::OnCManualRed() 
{
	NextChoise( m_TowerSetupSetting.Manual.LightRedChoise );
	SetChoiseTitle( m_btnManualRed, m_TowerSetupSetting.Manual.LightRedChoise );	
}
void CDlgTowerSetting::OnCManualYellow() 
{
	NextChoise( m_TowerSetupSetting.Manual.LightYellowChoise );
	SetChoiseTitle( m_btnManualYellow, m_TowerSetupSetting.Manual.LightYellowChoise );		
}
void CDlgTowerSetting::OnCManualGreen() 
{
	NextChoise( m_TowerSetupSetting.Manual.LightGreenChoise );
	SetChoiseTitle( m_btnManualGreen, m_TowerSetupSetting.Manual.LightGreenChoise );		
}
// Button - Manual Stop
void CDlgTowerSetting::OnCManualStopRed() 
{
	NextChoise( m_TowerSetupSetting.ManualStop.LightRedChoise );
	SetChoiseTitle( m_btnManualStopRed, m_TowerSetupSetting.ManualStop.LightRedChoise );	
}
void CDlgTowerSetting::OnCManualStopYellow() 
{
	NextChoise( m_TowerSetupSetting.ManualStop.LightYellowChoise );
	SetChoiseTitle( m_btnManualStopYellow, m_TowerSetupSetting.ManualStop.LightYellowChoise );		
}
void CDlgTowerSetting::OnCManualStopGreen() 
{
	NextChoise( m_TowerSetupSetting.ManualStop.LightGreenChoise );
	SetChoiseTitle( m_btnManualStopGreen, m_TowerSetupSetting.ManualStop.LightGreenChoise );	
}

