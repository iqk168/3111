// DlgCustomPageFunction.cpp : implementation file
//

#include "stdafx.h"
#include "deer.h"
#include "DlgCustomPageFunction.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgCustomPageFunction dialog


CDlgCustomPageFunction::CDlgCustomPageFunction(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgCustomPageFunction::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgCustomPageFunction)
	m_bUserSummaryReport = FALSE;
	m_bUserVisualPanel = FALSE;
	m_bUserSiteSetting = FALSE;
	m_bUserManualContact = FALSE;
	m_bUserLotInfomation = FALSE;
	m_bUserDeviceSetup = FALSE;
	m_bUserAutoSkip = FALSE;
	m_bUserYieldControl = FALSE;
	m_bUserArmLogICImage = FALSE;
	m_bUserSLTProtocol = FALSE;
	m_bUserIfTesting = FALSE;
	m_bUserTrayMapReport = FALSE;
	m_bUserTestSiteVacc = FALSE;
	m_bSetupAlignment = FALSE;
	m_bSetupAutoRetry = FALSE;
	m_bSetupCatoregy = FALSE;
	m_bSetupDeviceSetup = FALSE;
	m_bSetupEventLog = FALSE;
	m_bSetupIFTesting = FALSE;
	m_bSetupInputTray = FALSE;
	m_bSetupInterface = FALSE;
	m_bSetupIOMonitor = FALSE;
	m_bSetupOffset = FALSE;
	m_bSetupOutputTray = FALSE;
	m_bSetupRemoteControl = FALSE;
	m_bSetupRemoteInput = FALSE;
	m_bSetupSiteSetting = FALSE;
	m_bSetupSpeed = FALSE;
	m_bSetupTimer = FALSE;
	m_bSetupTrayFile = FALSE;
	m_bSetupYieldCtrl = FALSE;
	m_bTrayMapSetting = FALSE;
	m_btnEngAlignment = FALSE;
	m_btnEngCCDSocket = FALSE;
	m_btnEngChangeFile = FALSE;
	m_btnEventLog = FALSE;
	m_btnEngIOMonitor = FALSE;
	m_btnEngMotorMonitor = FALSE;
	m_btnEngSpeed = FALSE;
	m_btnEngTSCounter = FALSE;
	m_btnLoopTest = FALSE;
	m_btnEngAlarmMail = FALSE;
	m_bTestResultReport = FALSE;
	m_bSetupRepeatTray = FALSE;
	m_bRepeatTrayStatus = FALSE;
	m_bUserTrayDefColor = FALSE;
	m_bSetupTowerSetting = FALSE;
	//}}AFX_DATA_INIT

	m_UserPageEnable = m.m_UserPageEnable;
	m_SetupPageEnable = m.m_SetupPageEnable;
	m_EngineerPageEnable = m.m_EngineerPageEnable;
}


void CDlgCustomPageFunction::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgCustomPageFunction)
	DDX_Control(pDX, IDOK,						m_btnOK);
	DDX_Control(pDX, IDCANCEL,					m_btnCancel);
	DDX_Check(pDX, IDC_USER_SUMMMARY,			m_bUserSummaryReport);
	DDX_Check(pDX, IDC_USER_VISUAL_PANEL,		m_bUserVisualPanel);
	DDX_Check(pDX, IDC_USER_SITE_SETTING,		m_bUserSiteSetting);
	DDX_Check(pDX, IDC_USER_MANUAL_CONTACT,		m_bUserManualContact);
	DDX_Check(pDX, IDC_USER_LOT_INFOTMATION,	m_bUserLotInfomation);
	DDX_Check(pDX, IDC_USER_DEVICE_SETUP,		m_bUserDeviceSetup);
	DDX_Check(pDX, IDC_USER_AUTO_SKIP,			m_bUserAutoSkip);
	DDX_Check(pDX, IDC_USER_YIELD_CONTROL,		m_bUserYieldControl);
	DDX_Check(pDX, IDC_USER_REPEAT_TRAY_STATUS, m_bRepeatTrayStatus);
	DDX_Check(pDX, IDC_USER_TRAY_DEF_COLOR,		m_bUserTrayDefColor);
	DDX_Check(pDX, IDC_USER_IF_TESTING,			m_bUserIfTesting);
	DDX_Check(pDX, IDC_USER_TRAYMAP_REPORT,		m_bUserTrayMapReport);
	DDX_Check(pDX, IDC_USER_TESTSITE_VACC,		m_bUserTestSiteVacc);
	DDX_Check(pDX, IDC_USER_TEST_RESULT,		m_bTestResultReport);
	DDX_Check(pDX, IDC_USER_ARM_LOG_ICIMAGE,	m_bUserArmLogICImage);
	DDX_Check(pDX, IDC_USER_SLT_PROTOCOL,		m_bUserSLTProtocol);
	DDX_Check(pDX, IDC_SETUP_ALIGNMENT,			m_bSetupAlignment);
	DDX_Check(pDX, IDC_SETUP_AUTO_RETRY,		m_bSetupAutoRetry);
	DDX_Check(pDX, IDC_SETUP_CATOREGY,			m_bSetupCatoregy);
	DDX_Check(pDX, IDC_SETUP_DEVICE_SETUP,		m_bSetupDeviceSetup);
	DDX_Check(pDX, IDC_SETUP_EVENT_LOG,			m_bSetupEventLog);
	DDX_Check(pDX, IDC_SETUP_IF_TESTING,		m_bSetupIFTesting);
	DDX_Check(pDX, IDC_SETUP_INPUT_TRAY,		m_bSetupInputTray);
	DDX_Check(pDX, IDC_SETUP_INTERFACE,			m_bSetupInterface);
	DDX_Check(pDX, IDC_SETUP_IO_MONITOR,		m_bSetupIOMonitor);
	DDX_Check(pDX, IDC_SETUP_OFFSET,			m_bSetupOffset);
	DDX_Check(pDX, IDC_SETUP_OUTPUT_TRAY,		m_bSetupOutputTray);
	DDX_Check(pDX, IDC_SETUP_REMOTE,			m_bSetupRemoteControl);
	DDX_Check(pDX, IDC_SETUP_REMOTE_INPUT,		m_bSetupRemoteInput);
	DDX_Check(pDX, IDC_SETUP_SITE_SET,			m_bSetupSiteSetting);
	DDX_Check(pDX, IDC_SETUP_SPEED,				m_bSetupSpeed);
	DDX_Check(pDX, IDC_SETUP_TIMER,				m_bSetupTimer);
	DDX_Check(pDX, IDC_SETUP_TRAYFILE,			m_bSetupTrayFile);
	DDX_Check(pDX, IDC_SETUP_YIELD,				m_bSetupYieldCtrl);
	DDX_Check(pDX, IDC_SETUP_TRAYMAP_SETTING,	m_bTrayMapSetting);
	DDX_Check(pDX, IDC_ENG_ALIGNMENT,			m_btnEngAlignment);
	DDX_Check(pDX, IDC_ENG_CCD_SOCKET,			m_btnEngCCDSocket);
	DDX_Check(pDX, IDC_ENG_CHANGE_FILE,			m_btnEngChangeFile);
	DDX_Check(pDX, IDC_ENG_EVENT_LOG,			m_btnEventLog);
	DDX_Check(pDX, IDC_ENG_IO_MONITOR,			m_btnEngIOMonitor);
	DDX_Check(pDX, IDC_ENG_MOTOR_MONITOR,		m_btnEngMotorMonitor);
	DDX_Check(pDX, IDC_ENG_SPEED,				m_btnEngSpeed);
	DDX_Check(pDX, IDC_ENG_TS_COUNTER,			m_btnEngTSCounter);
	DDX_Check(pDX, IDC_ENG_LOOP_TEST,			m_btnLoopTest);
	DDX_Check(pDX, IDC_ENG_ALARM_MAIL,			m_btnEngAlarmMail);
	DDX_Check(pDX, IDC_SETUP_REPEAT_TRAY,		m_bSetupRepeatTray);
	DDX_Check(pDX, IDC_SETUP_TOWER_SETTING,		m_bSetupTowerSetting);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgCustomPageFunction, CDialog)
	//{{AFX_MSG_MAP(CDlgCustomPageFunction)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgCustomPageFunction message handlers

BOOL CDlgCustomPageFunction::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m.Info.bSubDlgOpen = true;
	f.UpdateButtonState();

	// init button 
	m_btnOK.SetIcon(IDI_OK);;
	m_btnOK.SetAlign(CButtonST::ST_ALIGN_VERT);;
	m_btnOK.SetFlat(FALSE);
	
	m_btnCancel.SetIcon(IDI_CANCEL);
	m_btnCancel.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnCancel.SetFlat(FALSE);	

	//
	InitOption();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
void CDlgCustomPageFunction::InitOption()
{
	// User Page
	m_bUserSummaryReport	= m_UserPageEnable.m_bEnableSummaryReport;
	m_bUserVisualPanel		= m_UserPageEnable.m_bEnableVisualPanel;
	m_bUserSiteSetting		= m_UserPageEnable.m_bEnableSiteSetting;
	m_bUserManualContact	= m_UserPageEnable.m_bEnableManualContact;
	m_bUserLotInfomation	= m_UserPageEnable.m_bEnableLotInformation;
	m_bUserDeviceSetup		= m_UserPageEnable.m_bEnableDeviceSetup;
	m_bUserAutoSkip			= m_UserPageEnable.m_bEnableAutoSkip;
	m_bUserYieldControl		= m_UserPageEnable.m_bEnableYieldCtrl;
	m_bUserIfTesting		= m_UserPageEnable.m_bEnableIfTesting;
	m_bUserTrayMapReport	= m_UserPageEnable.m_bEnableTrayMapReport;
	m_bUserTestSiteVacc		= m_UserPageEnable.m_bTestSiteVaccOn;
	m_bTestResultReport		= m_UserPageEnable.m_bTestResultReport;
	m_bRepeatTrayStatus		= m_UserPageEnable.m_bRepeatTrayStatus;
	m_bUserTrayDefColor		= m_UserPageEnable.m_bTrayDefColor;
	m_bUserArmLogICImage	= m_UserPageEnable.m_bArmLogICImage;
	m_bUserSLTProtocol		= m_UserPageEnable.m_bSLTProtocol;

	// Setup Page
	m_bSetupAlignment		= m_SetupPageEnable.m_bEnableAlignment;
	m_bSetupAutoRetry		= m_SetupPageEnable.m_bEnableAutoRetry;
	m_bSetupCatoregy		= m_SetupPageEnable.m_bEnableCatoregy;
	m_bSetupDeviceSetup		= m_SetupPageEnable.m_bEnableDeviceSetup;
	m_bSetupEventLog		= m_SetupPageEnable.m_bEnableEventLog;
	m_bSetupIFTesting		= m_SetupPageEnable.m_bEnableIfTesting;
	m_bSetupInputTray		= m_SetupPageEnable.m_bEnableInputTray;
	m_bSetupInterface		= m_SetupPageEnable.m_bEnableInterface;
	m_bSetupIOMonitor		= m_SetupPageEnable.m_bEnableIOMonitor;
	m_bSetupOffset			= m_SetupPageEnable.m_bEnableOffset;
	m_bSetupOutputTray		= m_SetupPageEnable.m_bEnableOutputTray;
	m_bSetupRemoteControl	= m_SetupPageEnable.m_bEnableRemoteControl;
	m_bSetupRemoteInput		= m_SetupPageEnable.m_bEnableRemoteInput;
	m_bSetupSiteSetting		= m_SetupPageEnable.m_bEnableSiteSetting;
	m_bSetupSpeed			= m_SetupPageEnable.m_bEnableSpeed;
	m_bSetupTimer			= m_SetupPageEnable.m_bEnableTimer;
	m_bSetupTrayFile		= m_SetupPageEnable.m_bEnableTrayFile;
	m_bSetupYieldCtrl		= m_SetupPageEnable.m_bEnableYieldCtrl;
	m_bTrayMapSetting		= m_SetupPageEnable.m_bEnableInOutTray;
	m_bSetupRepeatTray		= m_SetupPageEnable.m_bEnableRepeatTray;
	m_bSetupTowerSetting	= m_SetupPageEnable.m_bEnableTowerSetting;
	
	// Engineer Page
	m_btnEngAlignment		= m_EngineerPageEnable.m_bEnableAlignment;
	m_btnEngCCDSocket		= m_EngineerPageEnable.m_bEnableSocketCCD;
	m_btnEngChangeFile		= m_EngineerPageEnable.m_bEnableChangeFile;
	m_btnEventLog			= m_EngineerPageEnable.m_bEnableEventLog;
	m_btnEngIOMonitor		= m_EngineerPageEnable.m_bEnableIOMonitor;
	m_btnEngMotorMonitor	= m_EngineerPageEnable.m_bEnableMotorMon;
	m_btnEngSpeed			= m_EngineerPageEnable.m_bEnableSpeed;
	m_btnEngTSCounter		= m_EngineerPageEnable.m_bEnableTSCounter;
	m_btnLoopTest			= m_EngineerPageEnable.m_bEnableLoopTest;
	m_btnEngAlarmMail		= m_EngineerPageEnable.m_bEnableAlarmMail;

	UpdateData( FALSE );
}
void CDlgCustomPageFunction::SaveOption()
{
	UpdateData();

	// User Page
	m_UserPageEnable.m_bEnableSummaryReport		= m_bUserSummaryReport	== 1 ? true : false;
	m_UserPageEnable.m_bEnableSummaryReport		= m_bUserSummaryReport	== 1 ? true : false;
	m_UserPageEnable.m_bEnableVisualPanel		= m_bUserVisualPanel	== 1 ? true : false;
	m_UserPageEnable.m_bEnableSiteSetting		= m_bUserSiteSetting    == 1 ? true : false;
	m_UserPageEnable.m_bEnableManualContact		= m_bUserManualContact	== 1 ? true : false;
	m_UserPageEnable.m_bEnableLotInformation	= m_bUserLotInfomation	== 1 ? true : false;
	m_UserPageEnable.m_bEnableDeviceSetup		= m_bUserDeviceSetup	== 1 ? true : false;
	m_UserPageEnable.m_bEnableAutoSkip			= m_bUserAutoSkip		== 1 ? true : false;
	m_UserPageEnable.m_bEnableYieldCtrl			= m_bUserYieldControl	== 1 ? true : false;
	m_UserPageEnable.m_bEnableIfTesting			= m_bUserIfTesting		== 1 ? true : false; 
	m_UserPageEnable.m_bEnableTrayMapReport		= m_bUserTrayMapReport	== 1 ? true : false;
	m_UserPageEnable.m_bTestSiteVaccOn			= m_bUserTestSiteVacc	== 1 ? true : false;
	m_UserPageEnable.m_bTestResultReport		= m_bTestResultReport	== 1 ? true : false;
	m_UserPageEnable.m_bRepeatTrayStatus		= m_bRepeatTrayStatus	== 1 ? true : false;
	m_UserPageEnable.m_bTrayDefColor			= m_bUserTrayDefColor	== 1 ? true : false;
	m_UserPageEnable.m_bArmLogICImage			= m_bUserArmLogICImage	== 1 ? true : false;
	m_UserPageEnable.m_bSLTProtocol				= m_bUserSLTProtocol	== 1 ? true : false;

	m.m_UserPageEnable = m_UserPageEnable;

	// Setup Page
	m_SetupPageEnable.m_bEnableAlignment		= m_bSetupAlignment		== 1 ? true : false;
	m_SetupPageEnable.m_bEnableAutoRetry		= m_bSetupAutoRetry		== 1 ? true : false;
	m_SetupPageEnable.m_bEnableCatoregy			= m_bSetupCatoregy		== 1 ? true : false;
	m_SetupPageEnable.m_bEnableDeviceSetup		= m_bSetupDeviceSetup	== 1 ? true : false;
	m_SetupPageEnable.m_bEnableEventLog			= m_bSetupEventLog		== 1 ? true : false;
	m_SetupPageEnable.m_bEnableIfTesting		= m_bSetupIFTesting		== 1 ? true : false;
	m_SetupPageEnable.m_bEnableInputTray		= m_bSetupInputTray		== 1 ? true : false;
	m_SetupPageEnable.m_bEnableInterface		= m_bSetupInterface		== 1 ? true : false;
	m_SetupPageEnable.m_bEnableIOMonitor		= m_bSetupIOMonitor		== 1 ? true : false;
	m_SetupPageEnable.m_bEnableOffset			= m_bSetupOffset		== 1 ? true : false;
	m_SetupPageEnable.m_bEnableOutputTray		= m_bSetupOutputTray	== 1 ? true : false;
	m_SetupPageEnable.m_bEnableRemoteControl	= m_bSetupRemoteControl	== 1 ? true : false;
	m_SetupPageEnable.m_bEnableRemoteInput		= m_bSetupRemoteInput	== 1 ? true : false;
	m_SetupPageEnable.m_bEnableSiteSetting		= m_bSetupSiteSetting	== 1 ? true : false;
	m_SetupPageEnable.m_bEnableSpeed			= m_bSetupSpeed			== 1 ? true : false;
	m_SetupPageEnable.m_bEnableTimer			= m_bSetupTimer			== 1 ? true : false;
	m_SetupPageEnable.m_bEnableTrayFile			= m_bSetupTrayFile		== 1 ? true : false;
	m_SetupPageEnable.m_bEnableYieldCtrl		= m_bSetupYieldCtrl		== 1 ? true : false;
	m_SetupPageEnable.m_bEnableInOutTray		= m_bTrayMapSetting		== 1 ? true : false;
	m_SetupPageEnable.m_bEnableRepeatTray		= m_bSetupRepeatTray	== 1 ? true : false;
	m_SetupPageEnable.m_bEnableTowerSetting		= m_bSetupTowerSetting	== 1 ? true : false;

	m.m_SetupPageEnable = m_SetupPageEnable;

	// Engineer Page
	m_EngineerPageEnable.m_bEnableAlignment		= m_btnEngAlignment		== 1 ? true : false;
	m_EngineerPageEnable.m_bEnableSocketCCD		= m_btnEngCCDSocket		== 1 ? true : false;
	m_EngineerPageEnable.m_bEnableChangeFile	= m_btnEngChangeFile	== 1 ? true : false;
	m_EngineerPageEnable.m_bEnableEventLog		= m_btnEventLog			== 1 ? true : false;
	m_EngineerPageEnable.m_bEnableIOMonitor		= m_btnEngIOMonitor		== 1 ? true : false;
	m_EngineerPageEnable.m_bEnableMotorMon		= m_btnEngMotorMonitor	== 1 ? true : false;
	m_EngineerPageEnable.m_bEnableSpeed			= m_btnEngSpeed			== 1 ? true : false;
	m_EngineerPageEnable.m_bEnableTSCounter		= m_btnEngTSCounter		== 1 ? true : false;
	m_EngineerPageEnable.m_bEnableLoopTest		= m_btnLoopTest			== 1 ? true : false;
	m_EngineerPageEnable.m_bEnableAlarmMail		= m_btnEngAlarmMail		== 1 ? true : false;

	m.m_EngineerPageEnable = m_EngineerPageEnable;
}

BOOL CDlgCustomPageFunction::PreTranslateMessage(MSG* pMsg) 
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

void CDlgCustomPageFunction::OnOK() 
{
	SaveOption();

	f.SavePageEnable();

	m.Info.bSubDlgOpen = false;
	f.UpdateButtonState();

	CDialog::OnOK();
}

void CDlgCustomPageFunction::OnCancel() 
{
	m.Info.bSubDlgOpen = false;
	f.UpdateButtonState();

	CDialog::OnCancel();
}
