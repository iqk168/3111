// DlgDebugFunction.cpp : implementation file
//

#include "stdafx.h"
#include "Deer.h"
#include "DlgDebugFunction.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgDebugFunction dialog


CDlgDebugFunction::CDlgDebugFunction(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgDebugFunction::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgDebugFunction)


	//}}AFX_DATA_INIT
}


void CDlgDebugFunction::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgDebugFunction)
	DDX_Control(pDX, IDC_F_ENABLE_TS_REMAIN_IC,			m_btnTSRemainIC);
	DDX_Control(pDX, IDC_F_BYPASS_SHUTTLE,				m_btnByPassShuttleError);
	DDX_Control(pDX, IDC_F_BYPASS_TRAY_INPOS,			m_btnByPassTrayInPos);
	DDX_Control(pDX, IDC_F_ENABLE_TORQUE,				m_btnTorqueCtrl);
	DDX_Control(pDX, IDC_F_ENABLE_CUSTOM_INPUTTRAY,		m_btnEnableCustomInput);
	DDX_Control(pDX, IDC_F_ENABLE_INPUT_TRAY_INFO,		m_btnEnableInputTrayInfo);
	DDX_Control(pDX, IDC_F_ENABLE_INPUT_TRAY_NUMBER,	m_btnEnableInputTrayNumber);
	DDX_Control(pDX, IDC_F_TTL,							m_btnEnableTTL);
	DDX_Control(pDX, IDC_F_TCP,							m_btnEnableTcp);
	DDX_Control(pDX, IDC_F_RS232,						m_btnEnableRs232);
	DDX_Control(pDX, IDC_F_GPIB,						m_btnEnableGPIB);
	DDX_Control(pDX, IDC_F_PTC_MODULE,					m_btnPTCModule);
	DDX_Control(pDX, IDC_F_REMOTE_CONTROL,				m_btnRemoteControl);
	DDX_Control(pDX, IDC_F_HEATER_MODULE,				m_btnHeaterModule);
	DDX_Control(pDX, IDC_F_TRITEMPERATUE_MODULE,		m_btnTriTemperatureModule);
	DDX_Control(pDX, IDC_F_CCD_SOCKET,					m_btnCCDSocket);
	DDX_Control(pDX, IDC_F_CCD_PIN1,					m_btnCCDPin1);
	DDX_Control(pDX, IDC_F_ATC_MODULE,					m_btnATCModule);
	DDX_Control(pDX, IDC_F_REMOTE_IO,					m_btnRemoteIO);
	DDX_Control(pDX, IDC_F_ENABLE_INPUT_TRAY_TIPS,		m_btnInputTrayTips);
	DDX_Control(pDX, IDC_F_ENABLE_IC_MISSING,			m_btnEnableICMissingDetect);
	DDX_Control(pDX, IDC_ENABLE_SUMMARY_REPORT,			m_btnEnableSummaryReport);
	DDX_Control(pDX, IDC_ENABLE_ROTATOR_TURN,			m_btnEnableRotatorTurn);
	DDX_Control(pDX, IDC_ROTATOR_PRE_GUIDE,				m_btnEnableRotatorPreGuide);
	DDX_Control(pDX, IDC_F_ION_FAN_ALAM,				m_btnIONFanAlarmDetect);
	DDX_Control(pDX, IDC_F_CUSTOM_ALARM_MAIL,			m_btnAlarmMail);
	DDX_Control(pDX, IDC_F_ENABLE_INITIAL_PRE_MOVE,		m_btnInitialPreMove);			
	DDX_Control(pDX, IDC_F_SIMPLIFIED,					m_btnEnableSimplified);			
	DDX_Control(pDX, IDC_F_DISPLAY_CONTACT_COUNTER,		m_btnShowContactCounter);
	DDX_Control(pDX, IDC_F_ENABLE_CHIP_TRAY,			m_btnEnableChipTray);			
	DDX_Control(pDX, IDC_F_BYPASS_TEST_VACC,			m_btnByPassTestVacc );
	DDX_Control(pDX, IDC_F_ENABLE_IO_MONITOR_RECOVERY,	m_btnByPassEnableIORecovery );
	DDX_Control(pDX, IDC_F_ENABLE_ROTATOR_ERROR,		m_btnByEnableRotatorError );
	DDX_Control(pDX, IDC_F_ROTATO_USE_FUNCTION,			m_btnRotatoUse);
	DDX_Control(pDX, IDC_F_DOOR_SENSOR,					m_btnEnableDoorSensor);
	DDX_Control(pDX, IDC_F_BYPASS_VACC,					m_btnByPassVacc);
	DDX_Control(pDX, IDC_F_ENABLE_ALARM,				m_btnEnableAlarm);
	DDX_Control(pDX, IDC_F_ENABLE_SET_BY_MODE,			m_btnSetByMode);
	DDX_Control(pDX, IDC_F_ENABLE_SAVE_SITE_SETTING,	m_btnEnableSaveSiteSetting );	
	DDX_Control(pDX, IDCANCEL,							m_btnCancel);
	DDX_Control(pDX, IDOK,								m_btnOK);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgDebugFunction, CDialog)
	//{{AFX_MSG_MAP(CDlgDebugFunction)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgDebugFunction message handlers

BOOL CDlgDebugFunction::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// init button 
	m_btnOK.SetIcon(IDI_OK);;
	m_btnOK.SetAlign(CButtonST::ST_ALIGN_VERT);;
	m_btnOK.SetFlat(FALSE);
	
	m_btnCancel.SetIcon(IDI_CANCEL);
	m_btnCancel.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnCancel.SetFlat(FALSE);

	// init debug setting
	InitValue();

	//
	InitInterfaceEnable();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
void CDlgDebugFunction::SaveInterfaceEnable() 
{
	int Sensor = 0;

	Sensor = m_btnEnableTcp.GetCheck();
	if(Sensor)
		m.m_InterfaceEnable.m_bEnableTcp = 1;
	else
		m.m_InterfaceEnable.m_bEnableTcp = 0;

	Sensor = m_btnEnableRs232.GetCheck();
	if(Sensor)
		m.m_InterfaceEnable.m_bEnableRs232 = 1;
	else
		m.m_InterfaceEnable.m_bEnableRs232 = 0;

	Sensor = m_btnEnableGPIB.GetCheck();
	if(Sensor)
		m.m_InterfaceEnable.m_bEnableGpib = 1;
	else
		m.m_InterfaceEnable.m_bEnableGpib = 0;

	Sensor = m_btnEnableTTL.GetCheck();
	if(Sensor)
		m.m_InterfaceEnable.m_bEnableTTL = 1;
	else
		m.m_InterfaceEnable.m_bEnableTTL = 0;

	f.SaveInterfaceEnable();
}
void CDlgDebugFunction::InitInterfaceEnable() 
{
	if( m.m_InterfaceEnable.m_bEnableTcp == 1 )
		m_btnEnableTcp.SetCheck(1);
	else
		m_btnEnableTcp.SetCheck(0);

	if( m.m_InterfaceEnable.m_bEnableRs232 == 1 )
		m_btnEnableRs232.SetCheck(1);
	else
		m_btnEnableRs232.SetCheck(0);

	if( m.m_InterfaceEnable.m_bEnableGpib == 1 )
		m_btnEnableGPIB.SetCheck(1);
	else
		m_btnEnableGPIB.SetCheck(0);

	if( m.m_InterfaceEnable.m_bEnableTTL == 1 )
		m_btnEnableTTL.SetCheck(1);
	else
		m_btnEnableTTL.SetCheck(0);
}
/////////////////////////////////////////////////////////////////
// 確認 Tri-Temperature / ATC Module / PTC Module 一次只能選一個
bool CDlgDebugFunction::CheckModuleValid()
{
	bool bOK = true;
	int iCount = 0;
	int Module[3];

	Module[0] = m_btnPTCModule.GetCheck();
	Module[1] = m_btnTriTemperatureModule.GetCheck();
	Module[2] = m_btnATCModule.GetCheck();

	for(int i=0;i<3;i++)
	{
		if( Module[i] == 1 )
			iCount++;
	}

	if( iCount >= 2 )
		bOK = false;

	return bOK;
}

void CDlgDebugFunction::InitValue() 
{
	if( m.Setting.m_bEnableAlarm )
		m_btnEnableAlarm.SetCheck(1);
	else
		m_btnEnableAlarm.SetCheck(0);

	if( m.Setting.m_bRotatoUse )
		m_btnRotatoUse.SetCheck(1);
	else
		m_btnRotatoUse.SetCheck(0);

	if(m.Setting.m_bEnableDoorSensor)
		m_btnEnableDoorSensor.SetCheck(1);
	else
		m_btnEnableDoorSensor.SetCheck(0);
	
	if( m.Setting.m_bCustomAlarmMail )
		m_btnAlarmMail.SetCheck(1);
	else
		m_btnAlarmMail.SetCheck(0);

	if( m.Setting.m_bInitialPreMove )
		m_btnInitialPreMove.SetCheck(1);
	else
		m_btnInitialPreMove.SetCheck(0);

	if( m.Setting.m_bByPassVacc )
		m_btnByPassVacc.SetCheck(1);
	else
		m_btnByPassVacc.SetCheck(0);

	if( m.Setting.m_bByPassTestVacc )
		m_btnByPassTestVacc.SetCheck(1);
	else
		m_btnByPassTestVacc.SetCheck(0);
	
	if( m.Setting.m_bEnableSimplified )
		m_btnEnableSimplified.SetCheck(1);
	else
		m_btnEnableSimplified.SetCheck(0);

	if( m.Setting.m_bShowContactCounter )
		m_btnShowContactCounter.SetCheck(1);
	else
		m_btnShowContactCounter.SetCheck(0);

	if( m.Setting.m_bSummaryReport )
		m_btnEnableSummaryReport.SetCheck(1);
	else
		m_btnEnableSummaryReport.SetCheck(0);

	if( m.Setting.m_bEnableChipTray )
		m_btnEnableChipTray.SetCheck(1);
	else
		m_btnEnableChipTray.SetCheck(0);

	if( m.Setting.m_bEnableRotatorPreGuide )
		m_btnEnableRotatorPreGuide.SetCheck(1);
	else
		m_btnEnableRotatorPreGuide.SetCheck(0);

	if( m.Setting.m_bByPassEnableIORecovery )
		m_btnByPassEnableIORecovery.SetCheck(1);
	else
		m_btnByPassEnableIORecovery.SetCheck(0);

	if( m.Setting.m_bByPassTrayInPos )
		m_btnByPassTrayInPos.SetCheck(1);
	else
		m_btnByPassTrayInPos.SetCheck(0);

	if( m.Setting.m_bByPassShuttleAlarm )
		m_btnByPassShuttleError.SetCheck(1);
	else
		m_btnByPassShuttleError.SetCheck(0);

	if( m.Setting.m_bByPassRotatorAlarm )
		m_btnByEnableRotatorError.SetCheck(1);
	else
		m_btnByEnableRotatorError.SetCheck(0);

	if( m.Setting.m_bEnableSaveSiteSetting )
		m_btnEnableSaveSiteSetting.SetCheck(1);
	else
		m_btnEnableSaveSiteSetting.SetCheck(0);

	if( m.Setting.m_bSetByMode )
		m_btnSetByMode.SetCheck(1);
	else
		m_btnSetByMode.SetCheck(0);

	if( m.Setting.m_bIONAlarm )
		m_btnIONFanAlarmDetect.SetCheck(1);
	else
		m_btnIONFanAlarmDetect.SetCheck(0);

	if( m.Setting.m_bEnableRotatorTurn )
		m_btnEnableRotatorTurn.SetCheck(1);
	else
		m_btnEnableRotatorTurn.SetCheck(0);

	if( m.Setting.m_bEnableICMissingDetect )
		m_btnEnableICMissingDetect.SetCheck(1);
	else
		m_btnEnableICMissingDetect.SetCheck(0);

	if( m.Setting.m_bInputTrayTips )
		m_btnInputTrayTips.SetCheck(1);
	else
		m_btnInputTrayTips.SetCheck(0);

	if( m.Setting.m_bInputTrayTipsNumber )
		m_btnEnableInputTrayNumber.SetCheck(1);
	else
		m_btnEnableInputTrayNumber.SetCheck(0);

	if( m.Setting.m_bInputTrayInfo )
		m_btnEnableInputTrayInfo.SetCheck(1);
	else
		m_btnEnableInputTrayInfo.SetCheck(0);

	if( m.Setting.m_bEnableRemoteIO )
		m_btnRemoteIO.SetCheck(1);
	else
		m_btnRemoteIO.SetCheck(0);

	if( m.Setting.m_bEnableATCModule )
		m_btnATCModule.SetCheck(1);
	else
		m_btnATCModule.SetCheck(0);

	if( m.Setting.m_bEnablePTCModule )
		m_btnPTCModule.SetCheck(1);
	else
		m_btnPTCModule.SetCheck(0);

	if( m.Setting.m_bEnableHeaterModule )
		m_btnHeaterModule.SetCheck(1);
	else
		m_btnHeaterModule.SetCheck(0);

	if( m.Setting.m_bEnableTriTempModule )
		m_btnTriTemperatureModule.SetCheck(1);
	else
		m_btnTriTemperatureModule.SetCheck(0);

	if( m.Setting.m_bEnableCCDPin1 == 1 )
		m_btnCCDPin1.SetCheck(1);
	else
		m_btnCCDPin1.SetCheck(0);

	if( m.Setting.m_bEnableCCDSocket == 1 )
		m_btnCCDSocket.SetCheck(1);
	else
		m_btnCCDSocket.SetCheck(0);

	if( m.Setting.m_bEnableRemoteControl == 1 )
		m_btnRemoteControl.SetCheck(1);
	else
		m_btnRemoteControl.SetCheck(0);

	if( m.Setting.m_bRemoteCustomInput == 1 )
		m_btnEnableCustomInput.SetCheck(1);
	else
		m_btnEnableCustomInput.SetCheck(0);

	if( m.Setting.m_bEnableTorqueCtrl == 1 )
		m_btnTorqueCtrl.SetCheck(1);
	else
		m_btnTorqueCtrl.SetCheck(0);

	if( m.Setting.m_bEnableTSRemainIC == 1 )
		m_btnTSRemainIC.SetCheck(1);
	else
		m_btnTSRemainIC.SetCheck(0);

	UpdateData(FALSE);
}
void CDlgDebugFunction::SaveData()
{
	UpdateData();

	int Sensor = 0;

	Sensor = m_btnEnableDoorSensor.GetCheck();
	if(Sensor)
		m.Setting.m_bEnableDoorSensor = 1;
	else
		m.Setting.m_bEnableDoorSensor = 0;

	Sensor = m_btnRotatoUse.GetCheck();
	if(Sensor)
		m.Setting.m_bRotatoUse = 1;
	else
		m.Setting.m_bRotatoUse = 0;

	Sensor = m_btnEnableAlarm.GetCheck();
	if( Sensor )
		m.Setting.m_bEnableAlarm = 1;
	else
		m.Setting.m_bEnableAlarm = 0;

	Sensor = m_btnByPassTestVacc.GetCheck();
	if(Sensor)
		m.Setting.m_bByPassTestVacc = 1;
	else
		m.Setting.m_bByPassTestVacc = 0;

	Sensor = m_btnByPassEnableIORecovery.GetCheck();
	if(Sensor)
		m.Setting.m_bByPassEnableIORecovery = 1;
	else
		m.Setting.m_bByPassEnableIORecovery = 0;

	Sensor = m_btnByEnableRotatorError.GetCheck();
	if(Sensor)
		m.Setting.m_bByPassRotatorAlarm = 1;
	else
		m.Setting.m_bByPassRotatorAlarm = 0;

	Sensor = m_btnEnableSaveSiteSetting.GetCheck();
	if(Sensor)
		m.Setting.m_bEnableSaveSiteSetting = 1;
	else
		m.Setting.m_bEnableSaveSiteSetting = 0;

	Sensor = m_btnSetByMode.GetCheck();
	if(Sensor)
		m.Setting.m_bSetByMode = 1;
	else
		m.Setting.m_bSetByMode = 0;

	Sensor = m_btnByPassVacc.GetCheck();
	if(Sensor)
		m.Setting.m_bByPassVacc = 1;
	else
		m.Setting.m_bByPassVacc = 0;
	
	Sensor = m_btnByPassTrayInPos.GetCheck();
	if(Sensor)
		m.Setting.m_bByPassTrayInPos = 1;
	else
		m.Setting.m_bByPassTrayInPos = 0;

	Sensor = m_btnByPassShuttleError.GetCheck();
	if(Sensor)
		m.Setting.m_bByPassShuttleAlarm = 1;
	else
		m.Setting.m_bByPassShuttleAlarm = 0;

	Sensor = m_btnEnableSimplified.GetCheck();	
	if(Sensor)
		m.Setting.m_bEnableSimplified = 1;
	else
		m.Setting.m_bEnableSimplified = 0;

	Sensor = m_btnShowContactCounter.GetCheck();
	if(Sensor)
		m.Setting.m_bShowContactCounter = 1;
	else
		m.Setting.m_bShowContactCounter = 0;

	Sensor = m_btnEnableSummaryReport.GetCheck();
	if(Sensor)
		m.Setting.m_bSummaryReport = 1;
	else
		m.Setting.m_bSummaryReport = 0;

	Sensor = m_btnEnableChipTray.GetCheck();
	if(Sensor)
		m.Setting.m_bEnableChipTray = 1;
	else
		m.Setting.m_bEnableChipTray = 0;

	Sensor = m_btnEnableRotatorPreGuide.GetCheck();
	if( Sensor )
		m.Setting.m_bEnableRotatorPreGuide = 1;
	else
		m.Setting.m_bEnableRotatorPreGuide = 0;

	Sensor = m_btnEnableRotatorTurn.GetCheck();
	if( Sensor )
		m.Setting.m_bEnableRotatorTurn = 1;
	else
		m.Setting.m_bEnableRotatorTurn = 0;

	Sensor = m_btnATCModule.GetCheck();
	if( Sensor )
		m.Setting.m_bEnableATCModule = 1;
	else
		m.Setting.m_bEnableATCModule = 0;

	Sensor = m_btnPTCModule.GetCheck();
	if( Sensor )
		m.Setting.m_bEnablePTCModule = 1;
	else
		m.Setting.m_bEnablePTCModule = 0;

	Sensor = m_btnHeaterModule.GetCheck();
	if( Sensor )
		m.Setting.m_bEnableHeaterModule = 1;
	else
		m.Setting.m_bEnableHeaterModule = 0;

	Sensor = m_btnTriTemperatureModule.GetCheck();
	if( Sensor )
		m.Setting.m_bEnableTriTempModule = 1;
	else
		m.Setting.m_bEnableTriTempModule = 0;

	Sensor = m_btnRemoteIO.GetCheck();
	if( Sensor )
		m.Setting.m_bEnableRemoteIO = 1;
	else
		m.Setting.m_bEnableRemoteIO	= 0;

	Sensor = m_btnInitialPreMove.GetCheck();
	if(Sensor)
		m.Setting.m_bInitialPreMove = 1;
	else
		m.Setting.m_bInitialPreMove = 0;

	Sensor = m_btnAlarmMail.GetCheck();
	if(Sensor)
		m.Setting.m_bCustomAlarmMail = 1;
	else
		m.Setting.m_bCustomAlarmMail = 0;

	Sensor = m_btnIONFanAlarmDetect.GetCheck();
	if(Sensor)
		m.Setting.m_bIONAlarm = 1;
	else
		m.Setting.m_bIONAlarm = 0;

	Sensor = m_btnEnableICMissingDetect.GetCheck();
	if(Sensor)
		m.Setting.m_bEnableICMissingDetect = 1;
	else
		m.Setting.m_bEnableICMissingDetect = 0;

	Sensor = m_btnInputTrayTips.GetCheck();
	if(Sensor)
		m.Setting.m_bInputTrayTips = 1;
	else
		m.Setting.m_bInputTrayTips = 0;

	Sensor = m_btnCCDPin1.GetCheck();
	if(Sensor)
		m.Setting.m_bEnableCCDPin1 = 1;
	else
		m.Setting.m_bEnableCCDPin1 = 0;

	Sensor = m_btnCCDSocket.GetCheck();
	if(Sensor)
		m.Setting.m_bEnableCCDSocket = 1;
	else
		m.Setting.m_bEnableCCDSocket = 0;

	Sensor = m_btnRemoteControl.GetCheck();
	if(Sensor)
		m.Setting.m_bEnableRemoteControl = 1;
	else
		m.Setting.m_bEnableRemoteControl = 0;

	Sensor = m_btnEnableInputTrayNumber.GetCheck();
	if(Sensor)
		m.Setting.m_bInputTrayTipsNumber = 1;
	else
		m.Setting.m_bInputTrayTipsNumber = 0;

	Sensor = m_btnEnableInputTrayInfo.GetCheck();
	if(Sensor)
		m.Setting.m_bInputTrayInfo = 1;
	else
		m.Setting.m_bInputTrayInfo = 0;

	Sensor = m_btnEnableCustomInput.GetCheck();
	if(Sensor)
		m.Setting.m_bRemoteCustomInput = 1;
	else
		m.Setting.m_bRemoteCustomInput = 0;

	Sensor = m_btnTorqueCtrl.GetCheck();
	if(Sensor)
		m.Setting.m_bEnableTorqueCtrl = 1;
	else
		m.Setting.m_bEnableTorqueCtrl = 0;

	Sensor = m_btnTSRemainIC.GetCheck();
	if(Sensor)
		m.Setting.m_bEnableTSRemainIC = 1;
	else
		m.Setting.m_bEnableTSRemainIC = 0;

	f.SaveSystemSetting();
	f.LoadMotorParameter();	// for motor reload. FT / SLT mode.
}
void CDlgDebugFunction::OnOK() 
{
	if( !CheckModuleValid())
	{
		CString csError = _T("");
		csError.Format("Tri-Temperature Module / ATC Module / PTC Module, You can only choise one.!");
		AfxMessageBox( csError );
		return;
	}

	SaveData();

	SaveInterfaceEnable();

	CDialog::OnOK();
}

void CDlgDebugFunction::OnCancel() 
{	
	CDialog::OnCancel();
}

BOOL CDlgDebugFunction::PreTranslateMessage(MSG* pMsg) 
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

