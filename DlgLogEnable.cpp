// DlgLogEnable.cpp : implementation file
//

#include "stdafx.h"
#include "deer.h"
#include "DlgLogEnable.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgLogEnable dialog


CDlgLogEnable::CDlgLogEnable(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgLogEnable::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgLogEnable)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgLogEnable::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgLogEnable)
	DDX_Control(pDX, IDC_LOG_SHUTTLE_JAM,			m_btnShuttleJamLog);
	DDX_Control(pDX, IDC_LOG_UPH_DATA,				m_btnEnableUPHDataLog);
	DDX_Control(pDX, IDC_LOG_JAM_RATE_REPORT,		m_btnEnableJamReport);
	DDX_Control(pDX, IDC_LOG_CCD_SOCKET_LOG,		m_btnEnableCCDSocketLog);
	DDX_Control(pDX, IDC_LOG_STATUS_REPORT_LOG,		m_btnStatusReportLog);
	DDX_Control(pDX, IDC_LOG_MOATION_CARD,			m_btnMotorLog);
	DDX_Control(pDX, IDC_LOG_DUAL_MOTOR,			m_btnDualMotorLog);
	DDX_Control(pDX, IDC_LOG_SINGLE_MOTOR,			m_btnSingleMotorLog);
	DDX_Control(pDX, IDC_LOG_COMM,					m_btnEnableCommLog);
	DDX_Control(pDX, IDOK,							m_btnOK);
	DDX_Control(pDX, IDCANCEL,						m_btnCancel);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgLogEnable, CDialog)
	//{{AFX_MSG_MAP(CDlgLogEnable)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgLogEnable message handlers

BOOL CDlgLogEnable::PreTranslateMessage(MSG* pMsg) 
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

BOOL CDlgLogEnable::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// init button 
	m_btnOK.SetIcon(IDI_SAVE);
	m_btnOK.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnOK.SetFlat(FALSE);
	
	m_btnCancel.SetIcon(IDI_CANCEL);
	m_btnCancel.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnCancel.SetFlat(FALSE);
	
	//
	InitValue();

	//
	f.ChangeLanguage(GetSafeHwnd());

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
void CDlgLogEnable::InitValue()
{
	// Communication Log
	if( m.Setting.m_bEnableCommLog )
		m_btnEnableCommLog.SetCheck(1);
	else
		m_btnEnableCommLog.SetCheck(0);

	// Single Motor Log
	if( m.Setting.m_bEnableSingleMotorLog )
		m_btnSingleMotorLog.SetCheck(1);
	else
		m_btnSingleMotorLog.SetCheck(0);

	// Dual Motor Log
	if( m.Setting.m_bEnableDualMotorLog )
		m_btnDualMotorLog.SetCheck(1);
	else
		m_btnDualMotorLog.SetCheck(0);

	// Moation Card Log
	if( m.Setting.m_bEnableMotorLog )
		m_btnMotorLog.SetCheck(1);
	else
		m_btnMotorLog.SetCheck(0);

	// Status Report
	if( m.Setting.m_bEnableStatusReportLog )
		m_btnStatusReportLog.SetCheck(1);
	else
		m_btnStatusReportLog.SetCheck(0);

	// CCD Socket Log
	if( m.Setting.m_bEnableCCDSocketLog )
		m_btnEnableCCDSocketLog.SetCheck(1);
	else
		m_btnEnableCCDSocketLog.SetCheck(0);

	// Jam Rate Report
	if( m.Setting.m_bEnableJamRateReport )
		m_btnEnableJamReport.SetCheck(1);
	else
		m_btnEnableJamReport.SetCheck(0);

	// UPH Log
	if( m.Setting.m_bEnableUPHLog )
		m_btnEnableUPHDataLog.SetCheck(1);
	else
		m_btnEnableUPHDataLog.SetCheck(0);

	// Shuttle Jam Log
	if( m.Setting.m_bEnableShuttleJamLog )
		m_btnShuttleJamLog.SetCheck(1);
	else
		m_btnShuttleJamLog.SetCheck(0);
}
void CDlgLogEnable::SaveData()
{
	int bOK = 0;
	// Communication Log
	bOK = m_btnEnableCommLog.GetCheck();
	if( bOK )
		m.Setting.m_bEnableCommLog = 1;
	else
		m.Setting.m_bEnableCommLog = 0;
	
	// Single Motor Log
	bOK = m_btnSingleMotorLog.GetCheck();
	if( bOK )
		m.Setting.m_bEnableSingleMotorLog = 1;
	else
		m.Setting.m_bEnableSingleMotorLog = 0;

	// Dual Motor Log
	bOK = m_btnDualMotorLog.GetCheck();
	if( bOK )
		m.Setting.m_bEnableDualMotorLog = 1;
	else
		m.Setting.m_bEnableDualMotorLog	= 0;

	// Motor Log
	bOK = m_btnMotorLog.GetCheck();
	if( bOK )
		m.Setting.m_bEnableMotorLog = 1;
	else
		m.Setting.m_bEnableMotorLog = 0;

	// Status Report
	bOK = m_btnStatusReportLog.GetCheck();
	if( bOK )
		m.Setting.m_bEnableStatusReportLog = 1;
	else
		m.Setting.m_bEnableStatusReportLog = 0;

	// CCD Socket
	bOK = m_btnEnableCCDSocketLog.GetCheck();
	if( bOK )
		m.Setting.m_bEnableCCDSocketLog = 1;
	else
		m.Setting.m_bEnableCCDSocketLog = 0;

	// Jam Rate Report
	bOK = m_btnEnableJamReport.GetCheck();
	if( bOK )
		m.Setting.m_bEnableJamRateReport = 1;
	else
		m.Setting.m_bEnableJamRateReport = 0;

	// UPH Log
	bOK = m_btnEnableUPHDataLog.GetCheck();
	if( bOK )
		m.Setting.m_bEnableUPHLog = 1;
	else
		m.Setting.m_bEnableUPHLog = 0;

	// Shuttle Jam Log
	bOK = m_btnShuttleJamLog.GetCheck();
	if( bOK )
		m.Setting.m_bEnableShuttleJamLog = 1;
	else
		m.Setting.m_bEnableShuttleJamLog = 0;

	//
	f.SaveSystemSetting();
}
void CDlgLogEnable::OnOK() 
{
	//
	SaveData();
	
	CDialog::OnOK();
}

void CDlgLogEnable::OnCancel() 
{
	
	CDialog::OnCancel();
}
