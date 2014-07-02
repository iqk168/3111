// DlgBasicSetting.cpp : implementation file
//

#include "stdafx.h"
#include "deer.h"
#include "DlgBasicSetting.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgBasicSetting dialog


CDlgBasicSetting::CDlgBasicSetting(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgBasicSetting::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgBasicSetting)
	m_iSpeedLowLimit = 0;
	m_iSpeedHighLimit = 0;
	m_dOffsetHighLimit = 0.0;
	m_dOffsetLowLimit = 0.0;
	m_dTimerHighLimit = 0.0;
	m_dTimerLowLimit = 0.0;
	m_iInitialPreMoveDistance = 0;
	m_dTestSiteStandbyPosition = 0.0;
	m_dTestSiteSocketStandyPos = 0.0;
	m_dStandyX = 0.0;
	m_dStandyY = 0.0;
	m_dTimeoutHighLimit = 0.0;
	m_dTimeoutLowLimit = 0.0;
	m_dBuzzerAutoClose = 0.0;
	m_dTorqueForceRation = 0.0;
	m_iRepeatTrayMaxValue = 0;
	//}}AFX_DATA_INIT

	m_fChange = false;
}


void CDlgBasicSetting::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgBasicSetting)
	DDX_Control(pDX, IDC_TORQ_FORCE_RATION,		m_wndTorqueForceRation);
	DDX_Control(pDX, IDC_TS_STANDY_POSITION2,	m_wndTestSiteSocketStandyPosition);
	DDX_Control(pDX, IDC_TS_STANDY_POSITION,	m_wndTestSitePosition);
	DDX_Control(pDX, IDC_E_OUTPUT_COLOR,		m_wndOutputColor);
	DDX_Control(pDX, IDC_E_OUTPUT_B,			m_wndOutputColorB);
	DDX_Control(pDX, IDC_E_OUTPUT_G,			m_wndOutputColorG);
	DDX_Control(pDX, IDC_E_OUTPUT_R,			m_wndOutputColorR);
	DDX_Control(pDX, IDOK,						m_btnOK);
	DDX_Control(pDX, IDCANCEL,					m_btnCancel);
	DDX_Text(pDX, IDC_SPEED_LOW_LIMIT,			m_iSpeedLowLimit);
	DDX_Text(pDX, IDC_SPEED_HIGH_LIMIT,			m_iSpeedHighLimit);
	DDX_Text(pDX, IDC_OFFSET_HIGH_LIMIT,		m_dOffsetHighLimit);
	DDX_Text(pDX, IDC_OFFSET_LOW_LIMIT,			m_dOffsetLowLimit);
	DDX_Text(pDX, IDC_TIMER_HIGH_LIMIT,			m_dTimerHighLimit);
	DDX_Text(pDX, IDC_TIMER_LOW_LIMIT,			m_dTimerLowLimit);
	DDX_Text(pDX, IDC_INITIAL_PRE_DISTANCE,		m_iInitialPreMoveDistance);
	DDX_Text(pDX, IDC_TS_STANDY_POSITION,		m_dTestSiteStandbyPosition);
	DDX_Text(pDX, IDC_TS_STANDY_POSITION2,		m_dTestSiteSocketStandyPos);
	DDX_Text(pDX, IDC_E_STANDY_X,				m_dStandyX);
	DDX_Text(pDX, IDC_E_STANDY_Y,				m_dStandyY);
	DDX_Text(pDX, IDC_TIMEOUT_LOW_LIMIT,		m_dTimeoutHighLimit);
	DDX_Text(pDX, IDC_TIMEROUT_HIGH_LIMIT,		m_dTimeoutLowLimit);
	DDX_Text(pDX, IDC_E_BUZZER_AUTO_CLOSE,		m_dBuzzerAutoClose);
	DDX_Text(pDX, IDC_TORQ_FORCE_RATION,		m_dTorqueForceRation);
	DDX_Text(pDX, IDC_REPEAT_MAX,				m_iRepeatTrayMaxValue);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgBasicSetting, CDialog)
	//{{AFX_MSG_MAP(CDlgBasicSetting)
	ON_WM_SHOWWINDOW()
	ON_EN_CHANGE(IDC_SPEED_LOW_LIMIT,		OnChangeSpeedLowLimit)
	ON_EN_CHANGE(IDC_SPEED_HIGH_LIMIT,		OnChangeSpeedHighLimit)
	ON_EN_CHANGE(IDC_OFFSET_LOW_LIMIT,		OnChangeOffsetLowLimit)
	ON_EN_CHANGE(IDC_OFFSET_HIGH_LIMIT,		OnChangeOffsetHighLimit)
	ON_EN_CHANGE(IDC_TIMER_LOW_LIMIT,		OnChangeTimerLowLimit)
	ON_EN_CHANGE(IDC_TIMER_HIGH_LIMIT,		OnChangeTimerHighLimit)
	ON_EN_CHANGE(IDC_INITIAL_PRE_DISTANCE,	OnChangeInitialPreDistance)
	ON_BN_CLICKED(IDC_E_OUTPUT_SET,			OnEOutputSet)
	ON_BN_CLICKED(IDC_E_OUTPUT_SAVE,		OnEOutputSave)
	ON_EN_CHANGE(IDC_E_OUTPUT_R,			OnChangeEOutputR)
	ON_EN_CHANGE(IDC_E_OUTPUT_G,			OnChangeEOutputG)
	ON_EN_CHANGE(IDC_E_OUTPUT_B,			OnChangeEOutputB)
	ON_BN_CLICKED(IDC_E_POSITION_STATIC,	OnEPositionStatic)
	ON_EN_CHANGE(IDC_TS_STANDY_POSITION,	OnChangeTsStandyPosition)
	ON_BN_CLICKED(IDC_E_POSITION_STATIC2,	OnEPositionStatic2)
	ON_BN_CLICKED(IDC_STATIC_TORQUE_RATION, OnStaticTorqueRation)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgBasicSetting message handlers

void CDlgBasicSetting::OnCancel() 
{
	if(m_fChange)
	{
		if(IDYES != AfxMessageBox("Data is modified. Save?\n",
			MB_YESNO|MB_ICONEXCLAMATION))
		{
			m.Info.bSubDlgOpen = false;
			f.UpdateButtonState();
			CDialog::OnCancel();
		}
		else
			OnOK();
	}
	else
	{
		m.Info.bSubDlgOpen = false;
		f.UpdateButtonState();
		CDialog::OnCancel();		
	}
}

void CDlgBasicSetting::OnOK() 
{
	//
//	if(!ChekcValue())
//		return;

	//
	SaveData();

	//
	m.Info.bSubDlgOpen = false;
	f.UpdateButtonState();	
	
	CDialog::OnOK();
}

BOOL CDlgBasicSetting::PreTranslateMessage(MSG* pMsg) 
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

BOOL CDlgBasicSetting::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	//
	m.Info.bSubDlgOpen = true;
	f.UpdateButtonState();	

	// init button 
	m_btnOK.SetIcon(IDI_SAVE);;
	m_btnOK.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnOK.SetFlat(FALSE);
	
	m_btnCancel.SetIcon(IDI_CANCEL);
	m_btnCancel.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnCancel.SetFlat(FALSE);

	//
	InitColor();

	//
	InitValue();

	//
	InitTips();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgBasicSetting::InitColor()
{
	CString csR = _T("");
	CString csG = _T("");
	CString csB = _T("");

	//
	csR.Format("%d", m.m_RunPageOutputColor.R );
	csG.Format("%d", m.m_RunPageOutputColor.G );
	csB.Format("%d", m.m_RunPageOutputColor.B );

	m_wndOutputColorR.SetWindowText( csR );
	m_wndOutputColorG.SetWindowText( csG );
	m_wndOutputColorB.SetWindowText( csB );

	//	
	COLORREF color = RGB( m.m_RunPageOutputColor.R, m.m_RunPageOutputColor.G, m.m_RunPageOutputColor.B );
	m_wndOutputColor.SetNewBkColor( color );
}
void CDlgBasicSetting::SaveColorData()
{
	CString csR = _T("");
	CString csG = _T("");
	CString csB = _T("");

	m_wndOutputColorR.GetWindowText( csR );
	m_wndOutputColorG.GetWindowText( csG );
	m_wndOutputColorB.GetWindowText( csB );

	m.m_RunPageOutputColor.R = atoi( csR );
	m.m_RunPageOutputColor.G = atoi( csG );
	m.m_RunPageOutputColor.B = atoi( csB );

	f.SaveOutputColor();
}
void CDlgBasicSetting::PreSetColor()
{
	CString csR = _T("");
	CString csG = _T("");
	CString csB = _T("");

	m_wndOutputColorR.GetWindowText( csR );
	m_wndOutputColorG.GetWindowText( csG );
	m_wndOutputColorB.GetWindowText( csB );

	long lR = atoi( csR );
	long lG = atoi( csG );
	long lB = atoi( csB );

	COLORREF color = RGB( lR, lG, lB );
	m_wndOutputColor.SetNewBkColor( color );
}
void CDlgBasicSetting::InitValue()
{
	// Initial Distance
	m_iInitialPreMoveDistance = m.Setting.m_iInitialPreMoveDistance;

	// Stnady 
	m_dStandyX				  = m.Setting.m_dStandyX;
	m_dStandyY				  = m.Setting.m_dStandyY;

	// Test Site Standy position
	m_dTestSiteStandbyPosition = m.Setting.m_dTestSiteStandbyPosition;
	m_dTestSiteSocketStandyPos = m.Setting.m_dTestSiteSocketStandyPos;

	// Speed
	m_iSpeedLowLimit	= m.Setting.m_iSpeedLowLimit;
	m_iSpeedHighLimit	= m.Setting.m_iSpeedHighLimit;

	// Offset
	m_dOffsetHighLimit	= m.Setting.m_dOffsetHighLimit;
	m_dOffsetLowLimit	= m.Setting.m_dOffsetLowLimit;

	// Timer
	m_dTimerHighLimit	= m.Setting.m_dTimerHighLimit;
	m_dTimerLowLimit	= m.Setting.m_dTimerLowLimit;

	// Timeout
	m_dTimeoutHighLimit	= m.Setting.m_dTimeoutHighLimit;
	m_dTimeoutLowLimit	= m.Setting.m_dTimeoutLowLimit;

	// Buzzer Auto Close
	m_dBuzzerAutoClose	= m.Setting.m_dBuzzerAutoClose;

	// Torque Status Ration
	m_dTorqueForceRation = m.m_TorqueStatusPar.dTorqueRation;

	// Repeat Tray
	m_iRepeatTrayMaxValue = m.Setting.m_iRepeatMaxiumValue;

	UpdateData(FALSE);
}
void CDlgBasicSetting::InitTips()
{
	// Tips 
	// Init Tips
	m_ToolTip.Create(this);
	m_ToolTip.SetMaxTipWidth(800);
	m_ToolTip.SetDelayTime( TTDT_AUTOPOP, 10000 );
	m_ToolTip.SetDelayTime( TTDT_INITIAL, 25 );
	m_ToolTip.EnableToolTips(true);

	// Speed
	m_ToolTip.AddTool( GetDlgItem(IDC_E_SPEED_L),	
		_T("Speed Low Limit") );
	m_ToolTip.AddTool( GetDlgItem(IDC_E_SPEED_H),	
		_T("Speed High Limit") );

	// Offset
	m_ToolTip.AddTool( GetDlgItem(IDC_E_OFFSET_L),	
		_T("Speed Low Limit") );
	m_ToolTip.AddTool( GetDlgItem(IDC_E_OFFSET_H),	
		_T("Speed High Limit") );

	// Timer
	m_ToolTip.AddTool( GetDlgItem(IDC_E_TIMER_L),	
		_T("Speed Low Limit") );
	m_ToolTip.AddTool( GetDlgItem(IDC_E_TIMER_H),	
		_T("Speed High Limit") );

	// Initial Distance
	m_ToolTip.AddTool( GetDlgItem(IDC_E_INITIAL_DIS),	
		_T("Initial PreMove Distance.") );

}
bool CDlgBasicSetting::ChekcValue()
{
	bool bOK = true;
	
	UpdateData();
	CString csMsg = _T("");
	if( m_dTestSiteSocketStandyPos > 0 || m_dTestSiteSocketStandyPos > _MaxSocketPos )
	{
		CString csTempMsg = _T("");
		csTempMsg.Format("Test site socket position out of range. [%5.2f~%5.2f]\r\n", 0, _MaxSocketPos );
		csMsg += csTempMsg;
		bOK = false;
	}

	//
	AfxMessageBox( csMsg );

	return bOK;
}
void CDlgBasicSetting::SaveData()
{
	UpdateData();

	// Initial Distance
	m.Setting.m_iInitialPreMoveDistance		= m_iInitialPreMoveDistance;

	// Stnady 
	m.Setting.m_dStandyX					= m_dStandyX;
	m.Setting.m_dStandyY					= m_dStandyY;

	// Test Site Standy position
	m.Setting.m_dTestSiteStandbyPosition	= m_dTestSiteStandbyPosition;
	m.Setting.m_dTestSiteSocketStandyPos	= m_dTestSiteSocketStandyPos;

	// Speed
	m.Setting.m_iSpeedLowLimit		= m_iSpeedLowLimit;
	m.Setting.m_iSpeedHighLimit		= m_iSpeedHighLimit;

	// Offset
	m.Setting.m_dOffsetHighLimit	= m_dOffsetHighLimit;
	m.Setting.m_dOffsetLowLimit		= m_dOffsetLowLimit;
	
	// Timer
	m.Setting.m_dTimerHighLimit		= m_dTimerHighLimit;
	m.Setting.m_dTimerLowLimit		= m_dTimerLowLimit;

	// Timeout
	m.Setting.m_dTimeoutHighLimit	= m_dTimeoutHighLimit;
	m.Setting.m_dTimeoutLowLimit	= m_dTimeoutLowLimit;

	// Buzzer Auto Close
	m.Setting.m_dBuzzerAutoClose	= m_dBuzzerAutoClose;

	// Torque Status
	m.m_TorqueStatusPar.dTorqueRation = m_dTorqueForceRation;

	// Repeat Tray
	m.Setting.m_iRepeatMaxiumValue = m_iRepeatTrayMaxValue;

	f.SaveSystemSetting();
	f.SaveTorqueParameter();
}

void CDlgBasicSetting::OnEOutputSet() 
{
	PreSetColor();
}

void CDlgBasicSetting::OnEOutputSave() 
{
	SaveColorData();
}

void CDlgBasicSetting::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);	
}
void CDlgBasicSetting::OnChangeSpeedLowLimit() 
{
	m_fChange = true;
}
void CDlgBasicSetting::OnChangeSpeedHighLimit() 
{
	m_fChange = true;
}
void CDlgBasicSetting::OnChangeOffsetLowLimit() 
{
	m_fChange = true;
}
void CDlgBasicSetting::OnChangeOffsetHighLimit() 
{
	m_fChange = true;
}
void CDlgBasicSetting::OnChangeTimerLowLimit() 
{
	m_fChange = true;	
}
void CDlgBasicSetting::OnChangeTimerHighLimit() 
{
	m_fChange = true;
}
void CDlgBasicSetting::OnChangeInitialPreDistance() 
{
	m_fChange = true;
}
void CDlgBasicSetting::OnChangeTsStandyPosition() 
{
	m_fChange = true;
}
void CDlgBasicSetting::OnChangeEOutputR() 
{
//	m_fChange = true;
}

void CDlgBasicSetting::OnChangeEOutputG() 
{
//	m_fChange = true;
}

void CDlgBasicSetting::OnChangeEOutputB() 
{
//	m_fChange = true;
}

void CDlgBasicSetting::OnEPositionStatic() 
{
	m_wndTestSitePosition.EnableWindow( TRUE );	
}

void CDlgBasicSetting::OnEPositionStatic2() 
{
	m_wndTestSiteSocketStandyPosition.EnableWindow( TRUE );
}

void CDlgBasicSetting::OnStaticTorqueRation() 
{
	m_wndTorqueForceRation.EnableWindow( TRUE );
}
