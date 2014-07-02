// DlgIOMontiorHandler.cpp : implementation file
//

#include "stdafx.h"
#include "deer.h"
#include "DlgIOMontiorHandler.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgIOMontiorHandler dialog


CDlgIOMontiorHandler::CDlgIOMontiorHandler(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgIOMontiorHandler::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgIOMontiorHandler)
	//}}AFX_DATA_INIT

	m_bOnlyShow = false;
}


void CDlgIOMontiorHandler::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgIOMontiorHandler)
	DDX_Control(pDX, IDC_LED_TS_ATX,			m_ledTSATX);
	DDX_Control(pDX, IDC_LED_TS_Z_BLOW_GO,		m_ledTSBlowGo);
	DDX_Control(pDX, IDC_LED_TESTER,			m_ledTester);
	DDX_Control(pDX, IDC_LED_TS_SKIP_PRESS,		m_ledTSSkipPress);
	DDX_Control(pDX, IDC_LED_TS_SKIP_ON,		m_ledTSSkipOn);
	DDX_Control(pDX, IDC_LED_HEATER,			m_ledHeater);
	DDX_Control(pDX, IDC_LED_SHUTTLE_JAM,		m_ledShuttleJam);
	DDX_Control(pDX, IDC_LED_SHUTTLE_PLMT,		m_ledShuttlepLmt);
	DDX_Control(pDX, IDC_LED_SHUTTLE_NLMT,		m_ledShuttlenLmt);
	DDX_Control(pDX, IDC_LED_SHUTTLE,			m_ledShuttle);
	DDX_Control(pDX, IDC_LED_TS_Z_BLOW,			m_ledTSBlow);
	DDX_Control(pDX, IDC_LED_TS_Z_VACC_SENSOR,	m_ledTSVaccSensor);
	DDX_Control(pDX, IDC_LED_TS_Z_VACC,			m_ledTSVacc);
	DDX_Control(pDX, IDC_DEBUG_COUNT,			m_wndDebugCount);
	DDX_Control(pDX, IDC_LED_SYSTEM_EMG,		m_ledSystemEmg);
	DDX_Control(pDX, IDC_LED_SYSTEM_DOOR,		m_ledSystemDoor);
	DDX_Control(pDX, IDC_LED_SYSTEM_ION,		m_ledSystemION);
	DDX_Control(pDX, IDC_LED_SYSTEM_AIR_SOURCE, m_ledSystemAirSource);
	DDX_Control(pDX, IDC_E_ROTATOR_GRP,			m_wndRotatorGroup);
	DDX_Control(pDX, IDC_LED_ROTATE_MISSING,	m_ledRotatorMissing);
	DDX_Control(pDX, IDC_LED_ROTATE_JAM,		m_ledRotatorJam);
	DDX_Control(pDX, IDC_LED_ROTATE_N_LMT,		m_ledRotatorNLmt);
	DDX_Control(pDX, IDC_LED_ROTATE_P_LMT,		m_ledRotatorPLmt);
	DDX_Control(pDX, IDC_LED_ROTATE,			m_ledRotatorRotate);
	DDX_Control(pDX, IDC_LED_TRAY_OUTPUT,		m_ledTrayOutput);
	DDX_Control(pDX, IDC_LED_TRAY_INPUT,		m_ledTrayInput);
	DDX_Control(pDX, IDC_LED_Z_BLOW,			m_ledZBlow);
	DDX_Control(pDX, IDC_LED_Z_VACC,			m_ledZVacc);
	DDX_Control(pDX, IDC_LED_Z_VACC_SENSOR,		m_ledZVaccSensor);
	DDX_Control(pDX, IDC_LED_TOWER_YELLOW,		m_ledTowerYellow);
	DDX_Control(pDX, IDC_LED_TOWER_RED,			m_ledTowerRed);
	DDX_Control(pDX, IDC_LED_TOWER_GREEN,		m_ledTowerGreen);
	DDX_Control(pDX, IDC_LED_TOWER_BUZZER,		m_ledTowerBuzzer);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgIOMontiorHandler, CDialog)
	//{{AFX_MSG_MAP(CDlgIOMontiorHandler)
	ON_WM_TIMER()
	ON_WM_DESTROY()
	ON_WM_SHOWWINDOW()
	ON_BN_CLICKED(IDC_LED_Z_VACC,				OnLedZVacc)
	ON_BN_CLICKED(IDC_LED_Z_BLOW,				OnLedZBlow)
	ON_BN_CLICKED(IDC_LED_TSZ_SET,				OnLedTszSet)
	ON_BN_CLICKED(IDC_LED_TOWER_RED,			OnLedTowerRed)
	ON_BN_CLICKED(IDC_LED_TOWER_YELLOW,			OnLedTowerYellow)
	ON_BN_CLICKED(IDC_LED_TOWER_GREEN,			OnLedTowerGreen)
	ON_BN_CLICKED(IDC_LED_TOWER_BUZZER,			OnLedTowerBuzzer)
	ON_BN_CLICKED(IDC_LED_ROTATE,				OnLedRotate)
	ON_BN_CLICKED(IDC_E_ROTATOR_GRP,			OnERotatorGrp)
	ON_BN_CLICKED(IDC_DE,						OnDe)
	ON_BN_CLICKED(IDC_LED_HEATER,				OnLedHeater)
	ON_BN_CLICKED(IDC_LED_TS_SKIP_PRESS,		OnLedTsSkipPress)
	ON_BN_CLICKED(IDC_LED_TS_Z_VACC,			OnLedTsZVacc)
	ON_BN_CLICKED(IDC_LED_TS_Z_BLOW,			OnLedTsZBlow)
	ON_BN_CLICKED(IDC_LED_TS_SKIP_ON,			OnLedTsSkipOn)
	ON_BN_CLICKED(IDC_LED_TESTER,				OnLedTester)
	ON_BN_CLICKED(IDC_LED_SHUTTLE,				OnLedShuttle)
	ON_BN_CLICKED(IDC_LED_TS_Z_BLOW_GO,			OnLedTsZBlowGo)
	ON_BN_CLICKED(IDC_LED_TS_ATX,				OnLedTsAtx)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgIOMontiorHandler message handlers

BOOL CDlgIOMontiorHandler::OnInitDialog() 
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
void CDlgIOMontiorHandler::InitLed()
{
	// Tower
	m_ledTowerYellow.SetLed(CLed::LED_COLOR_YELLOW);
	m_ledTowerRed.SetLed(CLed::LED_COLOR_RED);
	m_ledTowerGreen.SetLed(CLed::LED_COLOR_GREEN);
	m_ledTowerBuzzer.SetLed(CLed::LED_COLOR_GREEN);

	// Heater 
	m_ledHeater.SetLed(CLed::LED_COLOR_GREEN);

	// Tester 
	m_ledTester.SetLed(CLed::LED_COLOR_GREEN);

	// Shuttle 
	m_ledShuttle.SetLed(CLed::LED_COLOR_GREEN);
	m_ledShuttlenLmt.SetLed(CLed::LED_COLOR_RED);
	m_ledShuttlepLmt.SetLed(CLed::LED_COLOR_RED);
	m_ledShuttleJam.SetLed(CLed::LED_COLOR_RED);

	// Arm Z
	m_ledZBlow.SetLed(CLed::LED_COLOR_GREEN);
	m_ledZVacc.SetLed(CLed::LED_COLOR_GREEN);
	m_ledZVaccSensor.SetLed(CLed::LED_COLOR_RED);

	// Tray
	m_ledTrayOutput.SetLed(CLed::LED_COLOR_RED);
	m_ledTrayInput.SetLed(CLed::LED_COLOR_RED);

	// Rotator
	m_ledRotatorMissing.SetLed(CLed::LED_COLOR_RED);
	m_ledRotatorJam.SetLed(CLed::LED_COLOR_RED);
	m_ledRotatorNLmt.SetLed(CLed::LED_COLOR_RED);
	m_ledRotatorPLmt.SetLed(CLed::LED_COLOR_RED);
	m_ledRotatorRotate.SetLed(CLed::LED_COLOR_GREEN);

	// System 
	m_ledSystemAirSource.SetLed(CLed::LED_COLOR_RED);
	m_ledSystemION.SetLed(CLed::LED_COLOR_RED);

	//
	m_ledSystemEmg.SetLed(CLed::LED_COLOR_RED);
	m_ledSystemDoor.SetLed(CLed::LED_COLOR_RED);

	//
	m_ledSystemDoor.SetLed(CLed::LED_COLOR_RED);

	// TS
	m_ledTSVacc.SetLed(CLed::LED_COLOR_GREEN);
	m_ledTSVaccSensor.SetLed(CLed::LED_COLOR_RED);
	m_ledTSBlow.SetLed(CLed::LED_COLOR_GREEN);
	m_ledTSSkipOn.SetLed(CLed::LED_COLOR_GREEN);
	m_ledTSSkipPress.SetLed(CLed::LED_COLOR_RED);
	m_ledTSBlowGo.SetLed(CLed::LED_COLOR_GREEN);
	m_ledTSATX.SetLed(CLed::LED_COLOR_GREEN);
}
void CDlgIOMontiorHandler::InitTips()
{
	// Tips // Init Tips
	m_ToolTip.Create(this);
	m_ToolTip.SetMaxTipWidth(800);
	m_ToolTip.SetDelayTime( TTDT_AUTOPOP, 10000 );
	m_ToolTip.SetDelayTime( TTDT_INITIAL, 25 );
	m_ToolTip.EnableToolTips(true);

	// System
	m_ToolTip.AddTool( GetDlgItem(IDC_LED_SYSTEM_EMG),			_T("I1-00") );
	m_ToolTip.AddTool( GetDlgItem(IDC_LED_SYSTEM_ION),			_T("I1-07") );	

	// System
	m_ToolTip.AddTool( GetDlgItem(IDC_LED_SYSTEM_DOOR),			_T("I1-03") );
	m_ToolTip.AddTool( GetDlgItem(IDC_LED_SYSTEM_AIR_SOURCE),	_T("I1-02") );

	//
	m_ToolTip.AddTool( GetDlgItem(IDC_E_ROTATOR_GRP),			_T("") );

	// Heater 
	m_ToolTip.AddTool( GetDlgItem(IDC_LED_HEATER),				_T("R-O1-08") );

	// Tester 
	m_ToolTip.AddTool( GetDlgItem(IDC_LED_TESTER),				_T("O1-11") );

	// Rotator
	m_ToolTip.AddTool( GetDlgItem(IDC_LED_ROTATE_MISSING),		_T("R-I1-07") );
	m_ToolTip.AddTool( GetDlgItem(IDC_LED_ROTATE_JAM),			_T("R-I1-08") );
	m_ToolTip.AddTool( GetDlgItem(IDC_LED_ROTATE_N_LMT),		_T("R-I1-10") );
	m_ToolTip.AddTool( GetDlgItem(IDC_LED_ROTATE_P_LMT),		_T("R-I1-09") );
	m_ToolTip.AddTool( GetDlgItem(IDC_LED_ROTATE),				_T("R-I1-07") );
	
	// Fix Input / Output
	m_ToolTip.AddTool( GetDlgItem(IDC_LED_TRAY_OUTPUT),			_T("I1-11") );
	m_ToolTip.AddTool( GetDlgItem(IDC_LED_TRAY_INPUT),			_T("I1-10") );
	
	// Arm Z
	m_ToolTip.AddTool( GetDlgItem(IDC_LED_Z_BLOW),				_T("O1-01") );	
	m_ToolTip.AddTool( GetDlgItem(IDC_LED_Z_VACC),				_T("O1-00") );		
	m_ToolTip.AddTool( GetDlgItem(IDC_LED_Z_VACC_SENSOR),		_T("I1-01") );
	
	// Test Site Z
	m_ToolTip.AddTool( GetDlgItem(IDC_LED_TS_Z_BLOW),			_T("O1-03") );
	m_ToolTip.AddTool( GetDlgItem(IDC_LED_TS_Z_BLOW_GO),		_T("O1-03") );	
	m_ToolTip.AddTool( GetDlgItem(IDC_LED_TS_Z_VACC),			_T("O1-02") );		
	m_ToolTip.AddTool( GetDlgItem(IDC_LED_TS_Z_VACC_SENSOR),	_T("I1-04") );
	m_ToolTip.AddTool( GetDlgItem(IDC_LED_TS_SKIP_PRESS),		_T("I1-06") );
	m_ToolTip.AddTool( GetDlgItem(IDC_LED_TS_SKIP_ON),			_T("IO-05") );
	m_ToolTip.AddTool( GetDlgItem(IDC_LED_TS_ATX),				_T("IO-10") );

	// Shuttle 
	m_ToolTip.AddTool( GetDlgItem(IDC_LED_SHUTTLE_JAM),			_T("I1-05") );	
	m_ToolTip.AddTool( GetDlgItem(IDC_LED_SHUTTLE_PLMT),		_T("I1-08") );	
	m_ToolTip.AddTool( GetDlgItem(IDC_LED_SHUTTLE_NLMT),		_T("I1-09") );	
	m_ToolTip.AddTool( GetDlgItem(IDC_LED_SHUTTLE),				_T("O1-04") );	
	
	// Tower
	m_ToolTip.AddTool( GetDlgItem(IDC_LED_TOWER_RED),			_T("O1-06") );
	m_ToolTip.AddTool( GetDlgItem(IDC_LED_TOWER_YELLOW),		_T("O1-07") );
	m_ToolTip.AddTool( GetDlgItem(IDC_LED_TOWER_GREEN),			_T("O1-08") );	
	m_ToolTip.AddTool( GetDlgItem(IDC_LED_TOWER_BUZZER),		_T("O1-09") );
}
void CDlgIOMontiorHandler::IOQuery()
{
#ifdef _Demo

	// System
	m_ledSystemAirSource	= true;
	m_ledSystemEmg			= true;
	
	// Rotator
	m_ledRotatorMissing		= false;	
	m_ledRotatorJam			= false;
	m_ledRotatorNLmt		= false;	
	m_ledRotatorPLmt		= true;	
	m_ledRotatorRotate		= true;	

	// Tester 
	m_ledTester				= true;	

	// Heater 
	m_ledHeater				= false;

	// Tray
	m_ledTrayOutput			= true;	
	m_ledTrayInput			= true;	

	// Test Site
	m_ledTSSkipPress		= false;	
	m_ledTSSkipOn			= false;	
	m_ledTSBlow				= false;
	m_ledTSVaccSensor		= false;
	m_ledTSVacc				= false;
	m_ledTSATX				= false;

	// Arm Z
	m_ledZBlow				= false;	
	m_ledZVacc				= false;	
	m_ledZVaccSensor		= false;	

	// Tower
	m_ledTowerYellow		= true;	
	m_ledTowerRed			= false;	
	m_ledTowerGreen			= false;	
	m_ledTowerBuzzer		= false;	

	m_ledShuttle			= true;
	m_ledShuttlenLmt		= true;
	m_ledShuttlepLmt		= false;
	m_ledShuttleJam			= false;

	m_ledSystemDoor			= true;

#else
	// Door
	m_ledSystemDoor			= m.InStatus.DoorSensor				== _DoorNoClose ? false : true;

	// System
	m_ledSystemAirSource	= m.InStatus.AirSourceDetect 		== _AirNoSource ? false : true;	
	
	// Rotator
	m_ledRotatorMissing		= m.RemoteInStatus.RotatorICMissing	== 0 ? false : true;	
	m_ledRotatorJam			= m.RemoteInStatus.RotatorICJam		== 0 ? false : true;	
	m_ledRotatorNLmt		= m.RemoteInStatus.RotatenLmt		== 0 ? false : true;	
	m_ledRotatorPLmt		= m.RemoteInStatus.RotatepLmt		== 0 ? false : true;	
	m_ledRotatorRotate		= m.RemoteOutStatus.Rotator			== 0 ? false : true;	

	// Tester 
	m_ledTester				= m.OutStatus.Tester				== 0 ? false : true;	

	// Heater 
	m_ledHeater				= m.RemoteOutStatus.HeaterOn		== 0 ? false : true;

	// Tray
	m_ledTrayOutput			= m.InStatus.OutputTrayInPos		== _TrayInPosOff ? false : true;	
	m_ledTrayInput			= m.InStatus.InputTrayInPos			== _TrayInPosOff ? false : true;	

	// Test Site
	m_ledTSSkipPress		= m.InStatus.TestSiteSkip			== _TSSkipOff ? false : true;	
	m_ledTSSkipOn			= m.OutStatus.TestSiteSkip			== 0 ? false : true;	
	m_ledTSBlow				= m.OutStatus.TestSiteBlow			== 0 ? false : true;
	m_ledTSBlowGo			= m.OutStatus.TestSiteBlow			== 0 ? false : true;
	m_ledTSVaccSensor		= m.InStatus.TestSiteZVaccSensor	== _TSVacOff ? false : true;
	m_ledTSVacc				= m.OutStatus.TestSiteVacc			== 0 ? false : true;
	m_ledTSATX				= m.OutStatus.ATXPower				== 0 ? false : true;

	// Arm Z
	m_ledZBlow				= m.OutStatus.ArmBlow				== 0 ? false : true;	
	m_ledZVacc				= m.OutStatus.ArmVacc				== 0 ? false : true;	
	m_ledZVaccSensor		= m.InStatus.ArmZVaccSensor			== _ArmZVacOff ? false : true;	

	// Tower
	m_ledTowerYellow		= m.OutStatus.TowerYellowOn			== 0 ? false : true;	
	m_ledTowerRed			= m.OutStatus.TowerRedOn			== 0 ? false : true;	
	m_ledTowerGreen			= m.OutStatus.TowerGreenOn			== 0 ? false : true;	
	m_ledTowerBuzzer		= m.OutStatus.TowerBuzzerOn			== 0 ? false : true;	

	// Shuttle 
	m_ledShuttle			= m.OutStatus.Shuttle				== 0 ? false : true;
	m_ledShuttlenLmt		= m.InStatus.ShuttleNLmt			== _ShuttleNLmtOff ? false : true;
	m_ledShuttlepLmt		= m.InStatus.ShuttlePLmt			== _ShuttlePLmtOff ? false : true;
	m_ledShuttleJam			= m.InStatus.ShuttleInputJam		== _ShuttleJamOff ? false : true;

	// Emg
	m_ledSystemEmg			= m.InStatus.Emg					== _EmgNoError ? false : true;	

#endif

}
void CDlgIOMontiorHandler::OnTimer(UINT nIDEvent) 
{
	switch(nIDEvent)
	{
	case ID_TIME_GET_STATUS:
		{
			IOQuery();
			QueryCount();
		}
		break;
	}	
	CDialog::OnTimer(nIDEvent);
}
void CDlgIOMontiorHandler::QueryCount() 
{
	CString csInfo = _T("");
	csInfo.Format("ErrCount / Read Count.. %d / %d", m.DebugError.ReadErr, m.DebugError.ReadCount );
	m_wndDebugCount.SetWindowText( csInfo );
}
BOOL CDlgIOMontiorHandler::PreTranslateMessage(MSG* pMsg) 
{
	// Tips
	m_ToolTip.RelayEvent(pMsg);
	
	return CDialog::PreTranslateMessage(pMsg);
}

void CDlgIOMontiorHandler::OnDestroy() 
{
	KillTimer( ID_TIME_GET_STATUS );

	CDialog::OnDestroy();	
}
void CDlgIOMontiorHandler::ReDrawUI()
{
	// Rotator
	if( m.Setting.m_bRotatoUse == 1 )
		m_wndRotatorGroup.ShowWindow( TRUE );
	else
		m_wndRotatorGroup.ShowWindow( FALSE );

	// ION Fan
	if( m.Setting.m_bIONAlarm == 1 )
	{
		GetDlgItem( IDC_STATIC_ION_ALARM )->ShowWindow( TRUE );
		GetDlgItem( IDC_LED_SYSTEM_ION )->ShowWindow( TRUE );
	}
	else
	{
		GetDlgItem( IDC_STATIC_ION_ALARM )->ShowWindow( FALSE );
		GetDlgItem( IDC_LED_SYSTEM_ION )->ShowWindow( FALSE );
	}
}
void CDlgIOMontiorHandler::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);
	
	if(bShow)
		ReDrawUI();
}
void CDlgIOMontiorHandler::SetOnlyShow(bool bOnlyShow)
{
	m_bOnlyShow = bOnlyShow;
}
void CDlgIOMontiorHandler::OnLedZVacc() 
{
	if(m_bOnlyShow)
		return;

	m.OutSet.ArmVacc = !m.OutStatus.ArmVacc;
}

void CDlgIOMontiorHandler::OnLedZBlow() 
{
	if(m_bOnlyShow)
		return;

	m.OutSet.ArmBlow = !m.OutStatus.ArmBlow;	
}

void CDlgIOMontiorHandler::OnLedTszSet() 
{
	if(m_bOnlyShow)
		return;

//	m.OutSet.TestSite = !m.OutStatus.TestSite;	
}

void CDlgIOMontiorHandler::OnLedTowerRed() 
{
	if(m_bOnlyShow)
		return;

	m.OutSet.TowerRedOn = !m.OutStatus.TowerRedOn;	
}

void CDlgIOMontiorHandler::OnLedTowerYellow() 
{
	if(m_bOnlyShow)
		return;

	m.OutSet.TowerYellowOn = !m.OutStatus.TowerYellowOn;	
}

void CDlgIOMontiorHandler::OnLedTowerGreen() 
{
	if(m_bOnlyShow)
		return;

	m.OutSet.TowerGreenOn = !m.OutStatus.TowerGreenOn;	
}

void CDlgIOMontiorHandler::OnLedTowerBuzzer() 
{
	if(m_bOnlyShow)
		return;

	m.OutSet.TowerBuzzerOn = !m.OutStatus.TowerBuzzerOn;	
}

void CDlgIOMontiorHandler::OnLedRotate() 
{
	if(m_bOnlyShow)
		return;

	m.RemoteOutSet.Rotator = !m.RemoteOutStatus.Rotator;
}
void CDlgIOMontiorHandler::OnLedHeater() 
{
	if(m_bOnlyShow)
		return;

	m.RemoteOutSet.HeaterOn = !m.RemoteOutStatus.HeaterOn;
}
void CDlgIOMontiorHandler::OnLedTsSkipPress() 
{
	if(m_bOnlyShow)
		return;	

	m.OutSet.TestSiteSkip = !m.OutStatus.TestSiteSkip;
}
void CDlgIOMontiorHandler::OnLedTsZVacc() 
{
	if(m_bOnlyShow)
		return;	
	
	m.OutSet.TestSiteVacc = !m.OutStatus.TestSiteVacc;
}
void CDlgIOMontiorHandler::OnLedTsZBlow() 
{
	if(m_bOnlyShow)
		return;		

	m.OutSet.TestSiteBlow = !m.OutStatus.TestSiteBlow;
}

void CDlgIOMontiorHandler::OnLedTsSkipOn() 
{
	if(m_bOnlyShow)
		return;
	
	m.OutSet.TestSiteSkip = !m.OutStatus.TestSiteSkip;
}
void CDlgIOMontiorHandler::OnERotatorGrp() 
{
	m_wndDebugCount.ShowWindow( TRUE );
}

void CDlgIOMontiorHandler::OnDe() 
{
	m_wndDebugCount.ShowWindow( TRUE );	
}

void CDlgIOMontiorHandler::OnLedTester() 
{
	if(m_bOnlyShow)
		return;
	
	m.OutSet.Tester = !m.OutStatus.Tester;
}

void CDlgIOMontiorHandler::OnLedShuttle() 
{
	if(m_bOnlyShow)
		return;
	
	m.OutSet.Shuttle = !m.OutStatus.Shuttle;
}

void CDlgIOMontiorHandler::OnLedTsZBlowGo() 
{
	if(m_bOnlyShow)
		return;		

	m.OutSet.TestSiteBlow = !m.OutStatus.TestSiteBlow;	
}

void CDlgIOMontiorHandler::OnLedTsAtx() 
{
	if(m_bOnlyShow)
		return;		

	m.OutSet.ATXPower = !m.OutStatus.ATXPower;
}
