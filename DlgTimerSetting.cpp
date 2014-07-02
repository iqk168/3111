// DlgTimerSetting.cpp : implementation file
//

#include "stdafx.h"
#include "deer.h"
#include "DlgTimerSetting.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgTimerSetting dialog


CDlgTimerSetting::CDlgTimerSetting(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgTimerSetting::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgTimerSetting)
	m_iShuttleHomeTimeout = 0;
	m_iShuttlePickTimeout = 0;
	m_iShuttleStableTime = 0;
	//}}AFX_DATA_INIT

	// Timer setting
	m_iInitialEachMotorWaitTime				= m.TimerSetting.iInitialEachMotorWaitTime;		// For Initial Sleep use
	m_iMotorRunlineTimeout					= m.TimerSetting.iMotorRunlineTimeout;			// For Motor RunLine function time out
	m_iMotorRunTimeout						= m.TimerSetting.iMotorRunTimeout;				// For Single Motor Run Function time out
	m_iInitialZWaitTime						= m.TimerSetting.iInitialZMotorWaitTime;		// For Initial Z Time out 
	m_iInitialTimeout						= m.TimerSetting.iInitialTimeout;				// For Initialing Time out
	m_iCommectionTimeout					= m.TimerSetting.iCommectionTimeout;			// For Communction Time out
	m_iBinLogInsertTimeout					= m.TimerSetting.iBinLogInsertTimeout;			// For Bin Log Insert to dBase time out
	m_iScanTrayStatus						= m.TimerSetting.iScanTrayStatus;				// For Scan Tray Status
	m_iArmZCheckTime						= m.TimerSetting.iArmZCheckTime;				// For Arm Z initial check IC timer
	m_iRotatorTime							= m.TimerSetting.iRotatorTime;					// For Rotator Stable Time
	m_iRotatorTimeout						= m.TimerSetting.iRotatorTimeout;				// For Rotator Timeout
	m_iShuttleHomeTimeout					= m.TimerSetting.iShuttleHomeTimeout;			// For Shuttle Home timeout
	m_iShuttlePickTimeout					= m.TimerSetting.iShuttlePickTimeout;			// For Shuttle Pick timeout
	m_iShuttleStableTime					= m.TimerSetting.iShuttleStableTime;			// For Shuttle Move Stable Time
}


void CDlgTimerSetting::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgTimerSetting)
	DDX_Control(pDX, IDC_MODIFY_PARAMETER,			m_btnModify);
	DDX_Control(pDX, IDOK,							m_btnOK);
	DDX_Control(pDX, IDCANCEL,						m_btnCancel);
	DDX_Text(pDX, IDC_INITIAL_EACH_MOTOR_TIME,		m_iInitialEachMotorWaitTime);
	DDX_Text(pDX, IDC_RUN_LINE_TIMEOUT,				m_iMotorRunlineTimeout);
	DDX_Text(pDX, IDC_RUN_TIMEOUT,					m_iMotorRunTimeout);
	DDX_Text(pDX, IDC_INITIAL_Z_WAIT_TIME,			m_iInitialZWaitTime);
	DDX_Text(pDX, IDC_INITIAL_TIMEOUT,				m_iInitialTimeout);
	DDX_Text(pDX, IDC_COMMECTION_TIMEOUT,			m_iCommectionTimeout);
	DDX_Text(pDX, IDC_BINLOG_INSERT_TIMEOUT,		m_iBinLogInsertTimeout);
	DDX_Text(pDX, IDC_TRAY_SCAN,					m_iScanTrayStatus);
	DDX_Text(pDX, IDC_ARM_Z_CHECK_TIME,				m_iArmZCheckTime);	
	DDX_Text(pDX, IDC_ROTATOR_TIME,					m_iRotatorTime);
	DDX_Text(pDX, IDC_ROTATOR_TIMEOUT,				m_iRotatorTimeout);
	DDX_Text(pDX, IDC_SHUTTLE_HOME_TIMEOUT,			m_iShuttleHomeTimeout);
	DDX_Text(pDX, IDC_SHUTTLE_PICK_TIMEOUT,			m_iShuttlePickTimeout);
	DDX_Text(pDX, IDC_SHUTTLE_STABLE_TIME,			m_iShuttleStableTime);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgTimerSetting, CDialog)
	//{{AFX_MSG_MAP(CDlgTimerSetting)
	ON_WM_CLOSE()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_MODIFY_PARAMETER, OnModifyParameter)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgTimerSetting message handlers

void CDlgTimerSetting::OnModifyParameter() 
{
	UpdateData();

	// Timer Setting for all handler
	m.TimerSetting.iInitialEachMotorWaitTime			= m_iInitialEachMotorWaitTime;	// For Initial Sleep use
	m.TimerSetting.iMotorRunlineTimeout					= m_iMotorRunlineTimeout;		// For Motor RunLine function time out
	m.TimerSetting.iMotorRunTimeout						= m_iMotorRunTimeout;			// For Single Motor Run Function time out
	m.TimerSetting.iInitialZMotorWaitTime				= m_iInitialZWaitTime;			// For Initial Z Time out 
	m.TimerSetting.iInitialTimeout						= m_iInitialTimeout;			// For Initialing Time out
	m.TimerSetting.iCommectionTimeout					= m_iCommectionTimeout;			// For Communction Time out
	m.TimerSetting.iBinLogInsertTimeout					= m_iBinLogInsertTimeout;		// For Bin Log Insert to dBase time out
	m.TimerSetting.iScanTrayStatus						= m_iScanTrayStatus;			// For Tray Status updata.
	m.TimerSetting.iArmZCheckTime						= m_iArmZCheckTime;				// For Arm Z initial check IC or not
	m.TimerSetting.iRotatorTime							= m_iRotatorTime;				// For Rotator stable time
	m.TimerSetting.iRotatorTimeout						= m_iRotatorTimeout;			// For Rotator stable timeout	
	m.TimerSetting.iShuttleHomeTimeout 					= m_iShuttleHomeTimeout;		// For Shuttle Home timeout
	m.TimerSetting.iShuttlePickTimeout 					= m_iShuttlePickTimeout;		// For Shuttle Pick timeout
	m.TimerSetting.iShuttleStableTime					= m_iShuttleStableTime;			// For Shuttle Move Stable Time

	f.SaveTimerSetting();

	CDialog::OnOK();
}

void CDlgTimerSetting::OnOK() 
{
	m.Info.bSubDlgOpen = false;
	f.UpdateButtonState();

	CDialog::OnOK();
}

void CDlgTimerSetting::OnCancel() 
{
	m.Info.bSubDlgOpen = false;
	f.UpdateButtonState();
	
	CDialog::OnCancel();
}

void CDlgTimerSetting::OnClose() 
{
	m.Info.bSubDlgOpen = false;
	f.UpdateButtonState();
	
	CDialog::OnClose();
}

void CDlgTimerSetting::OnDestroy() 
{
	m.Info.bSubDlgOpen = false;
	f.UpdateButtonState();

	CDialog::OnDestroy();	
}

BOOL CDlgTimerSetting::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// init button 
	m_btnOK.SetIcon(IDI_OK);;
	m_btnOK.SetAlign(CButtonST::ST_ALIGN_VERT);;
	m_btnOK.SetFlat(FALSE);
	
	m_btnCancel.SetIcon(IDI_CANCEL);
	m_btnCancel.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnCancel.SetFlat(FALSE);

	m_btnModify.SetIcon(IDI_SAVE);
	m_btnModify.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnModify.SetFlat(FALSE);

	m.Info.bSubDlgOpen = true;
	f.UpdateButtonState();

	//
	InitTips();

	f.ChangeLanguage(GetSafeHwnd());
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
void CDlgTimerSetting::InitTips()
{
	// Init Tips
	m_ToolTip.Create(this);
	m_ToolTip.SetMaxTipWidth(800);
	m_ToolTip.SetDelayTime( TTDT_AUTOPOP, 10000 );
	m_ToolTip.SetDelayTime( TTDT_INITIAL, 25 );
	m_ToolTip.EnableToolTips(true);

	//
	m_ToolTip.AddTool( GetDlgItem(IDC_STATIC_TI_INIT_MOT_WAIT_TIME),		_T("For Initial Sleep use") );
	m_ToolTip.AddTool( GetDlgItem(IDC_STATIC_TI_MOTOR_Z_WAIT_TIME),			_T("For Initial Z Time out") );
	m_ToolTip.AddTool( GetDlgItem(IDC_STATIC_TI_MOTOR_RUN_LINE_TIMEOUT),	_T("For Motor RunLine function time out") );
	m_ToolTip.AddTool( GetDlgItem(IDC_STATIC_TI_MOTOR_RUN_TIMEOUT),			_T("For Single Motor Run Function time out") );
	m_ToolTip.AddTool( GetDlgItem(IDC_STATIC_TI_INITIAL_TIMEOUT),			_T("For Initialing Time out") );
	m_ToolTip.AddTool( GetDlgItem(IDC_STATIC_TI_COMM_TIMEOUT),				_T("#UnUse For Communction Time out") );
	m_ToolTip.AddTool( GetDlgItem(IDC_STATIC_TI_ARMZ_CHECK_TIME),			_T("For Arm Z initial check IC vacc timer, ex: Initial Arm Z turn on Vacc check IC exist") );
	//
	m_ToolTip.AddTool( GetDlgItem(IDC_STATIC_TI_ROTATOR),					_T("For Rotator stable time, ex: Rotator rota->stable time->check InPos sensor") );
	m_ToolTip.AddTool( GetDlgItem(IDC_STATIC_TI_BIN_TIMEOUT),				_T("#UnUse For Bin Log Insert to dBase time out") );
	m_ToolTip.AddTool( GetDlgItem(IDC_STATIC_ROTATOR_TIMEOUT),				_T("For Rotator stable timeout") );
	m_ToolTip.AddTool( GetDlgItem(IDC_STATIC_TI_TRAY_MAP_SCAN),				_T("TrayMap Dialog Updata Status timer") );
	//
	m_ToolTip.AddTool( GetDlgItem(IDC_STATIC_SHUTTLE_PICK),					_T("Shuttle move to test site pick/place (pLmt) position time out") );
	m_ToolTip.AddTool( GetDlgItem(IDC_STATIC_SHUTTLE_HOME),					_T("Shuttle move to arm z pick/place (nLmt) position time out") );
	m_ToolTip.AddTool( GetDlgItem(IDC_STATIC_SHUTTLE_STABLE),				_T("Shuttle move, after lmt on, wait few time for cylinder stable") );

}
BOOL CDlgTimerSetting::PreTranslateMessage(MSG* pMsg) 
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
