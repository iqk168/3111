// DlgMotorMontior.cpp : implementation file
//

#include "stdafx.h"
#include "deer.h"
#include "DlgMotorMontior.h"

//
#include "DlgMotorMove.h"
#include "DlgTorqueTool.h"

// For 8141P Motor Run function.
#include "MC8141P.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgMotorMontior dialog


CDlgMotorMontior::CDlgMotorMontior(bool Mode, bool Show, bool Operator,
								   CWnd* pParent /*=NULL*/)
	: CDialog(CDlgMotorMontior::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgMotorMontior)
	m_lMotorPos1 = 0;
	m_lMotorPos2 = 0;
	m_lMotorPos3 = 0;
	m_lmsc = 0;
	//}}AFX_DATA_INIT
	m_iStartSpeed = 1;
	m_iAccelerate = 1;
	m_iMaxSpeed = 1;
	m_iMultiple = 1;
	m_iInPosRange = 1;
	m_iDriftSpeed = 1;
	m_iSearchSpeed = 1;
	m_iJerk = 1;

	m_iMotor = 0;

	m_fChange = false;

	// Display control / enable control
	m_Mode		= Mode;
	m_Show		= Show;
	m_Operator	= Operator;	

	m_bRunGo = false;
	m_bRunStop = true;
}


void CDlgMotorMontior::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgMotorMontior)
	DDX_Control(pDX, IDC_TORQUE, m_btnTorque);
	DDX_Control(pDX, IDC_MSG, m_wndMsg);
	DDX_Control(pDX, IDC_PRE_CHECK2,			m_btnPreCheckAll);
	DDX_Control(pDX, IDC_PRE_CHECK,				m_btnPreCheck);
	DDX_Control(pDX, IDC_CLEAR,					m_btnClearCount);
	DDX_Control(pDX, IDC_ALL_MOTOR_SERVO_OFF,	m_btnServoOffAll);
	DDX_Control(pDX, IDC_E_INPOS2,				m_wndInPos2);
	DDX_Control(pDX, IDC_IN_POS2,				m_ledInPos2);
	DDX_Control(pDX, IDC_E_LCOUNT,				m_wndELCount);
	DDX_Control(pDX, IDC_E_RCOUNT,				m_wndERCount);
	DDX_Control(pDX, IDC_E_ERR,					m_wndError);
	DDX_Control(pDX, IDC_E_ZPHASE,				m_wndZPhase);
	DDX_Control(pDX, IDC_E_ZERO_SPEED,			m_wndZeroSpeed);
	DDX_Control(pDX, IDC_E_TLC,					m_wndTLC);
	DDX_Control(pDX, IDC_E_PLMT,				m_wndPLmt);
	DDX_Control(pDX, IDC_E_NLMT,				m_wndNLmt);
	DDX_Control(pDX, IDC_E_EMG,					m_wndEmg);
	DDX_Control(pDX, IDC_STANDY,				m_wnddStandy);
	DDX_Control(pDX, IDC_D_POS3,				m_wnddPos3);
	DDX_Control(pDX, IDC_D_POS2,				m_wnddPos2);
	DDX_Control(pDX, IDC_D_POS1,				m_wnddPos1);
	DDX_Control(pDX, IDC_E_STANDY,				m_wndStandy);
	DDX_Control(pDX, IDC_E_POS3,				m_wndPos3);
	DDX_Control(pDX, IDC_E_POS2,				m_wndPos2);
	DDX_Control(pDX, IDC_E_POS1,				m_wndPos1);
	DDX_Control(pDX, IDC_GO,					m_btnGo);
	DDX_Control(pDX, IDC_STOP,					m_btnStop);
	DDX_Control(pDX, IDC_NORMAL,				m_btnNormalSetting);
	DDX_Control(pDX, IDC_MOTOR_PARAMETER,		m_wndWGroup);
	DDX_Control(pDX, IDC_W_START_SPEED,			m_wndWStartSpeed);
	DDX_Control(pDX, IDC_W_MAX_SPEED,			m_wndWMaxSpeed);
	DDX_Control(pDX, IDC_W_ACCL,				m_wndWAccl);
	DDX_Control(pDX, IDC_W_MULTIPLE,			m_wndWMulSpeed);
	DDX_Control(pDX, IDC_W_DRIFT_SPEED,			m_wndWDriftSpeed);
	DDX_Control(pDX, IDC_W_INPOS,				m_wndWInPos);
	DDX_Control(pDX, IDC_W_SEARCH_SPEED,		m_wndWSearchSpeed);
	DDX_Control(pDX, IDC_W_JERK,				m_wndWJerk);
	DDX_Control(pDX, IDC_L_COUNT,				m_wndLCount);
	DDX_Control(pDX, IDC_TLC,					m_TLC);
	DDX_Control(pDX, IDC_ZERO_SPEED,			m_ZeroSpeed);
	DDX_Control(pDX, IDC_MODIFY_PARAMETER,		m_btnModify);
	DDX_Control(pDX, IDCANCEL,					m_btnCancel);
	DDX_Control(pDX, IDOK,						m_btnOK);
	DDX_Control(pDX, IDC_CONNECTION,			m_Connection);
	DDX_Control(pDX, IDC_Z_PHASE,				m_ZPhase);
	DDX_Control(pDX, IDC_P_LMT,					m_pLMT);
	DDX_Control(pDX, IDC_N_LMT,					m_nLMT);
	DDX_Control(pDX, IDC_IN_POS,				m_InPos);
	DDX_Control(pDX, IDC_ERR,					m_Err);
	DDX_Control(pDX, IDC_EMG,					m_Emg);
	DDX_Control(pDX, IDC_DRV,					m_Drv);
	DDX_Control(pDX, IDC_ALARM,					m_Alarm);
	DDX_Control(pDX, IDC_SERVO,					m_Servo);
	DDX_Text(pDX, IDC_JERK_SPEED, m_iJerk);
	DDV_MinMaxInt(pDX, m_iJerk, 1, 20000000);
	DDX_Text(pDX, IDC_START_SPEED, m_iStartSpeed);
	DDV_MinMaxInt(pDX, m_iStartSpeed, 1, 20000000);
	DDX_Text(pDX, IDC_ACCELERATE, m_iAccelerate);
	DDV_MinMaxInt(pDX, m_iAccelerate, 1, 20000000);
	DDX_Text(pDX, IDC_MAX_SPEED, m_iMaxSpeed);
	DDV_MinMaxInt(pDX, m_iMaxSpeed, 1, 20000000);
	DDX_Text(pDX, IDC_MULTIPLE, m_iMultiple);
	DDV_MinMaxInt(pDX, m_iMultiple, 1, 20000000);
	DDX_Text(pDX, IDC_IN_POS_RANGE, m_iInPosRange);
	DDV_MinMaxInt(pDX, m_iInPosRange, 1, 20000000);
	DDX_Text(pDX, IDC_DRIFT_SPEED, m_iDriftSpeed);
	DDV_MinMaxInt(pDX, m_iDriftSpeed, 1, 20000000);
	DDX_Text(pDX, IDC_SEARCH_SPEED, m_iSearchSpeed);
	DDV_MinMaxInt(pDX, m_iSearchSpeed, 1, 20000000);
	DDX_Control(pDX, IDC_START_SPEED,	m_wndStartSpeed);
	DDX_Control(pDX, IDC_SEARCH_SPEED,	m_wndSearchSpeed);
	DDX_Control(pDX, IDC_MULTIPLE,		m_wndMultiple);
	DDX_Control(pDX, IDC_MAX_SPEED,		m_wndMaxSpeed);
	DDX_Control(pDX, IDC_IN_POS_RANGE,	m_wndInPosRange);
	DDX_Control(pDX, IDC_DRIFT_SPEED,	m_wndDriffSpeed);
	DDX_Control(pDX, IDC_ACCELERATE,	m_wndAccelerate);
	DDX_Control(pDX, IDC_JERK_SPEED,	m_wndJerk);
	DDX_Control(pDX, IDC_R_COUNT,		m_wndRCount);
	DDX_Radio(pDX, IDC_ARM_X, m_iMotor);
	DDX_Control(pDX, IDC_ARM_X, m_btnArmX);
	DDX_Control(pDX, IDC_ARM_Y, m_btnArmY);
	DDX_Control(pDX, IDC_ARM_Z, m_btnArmZ);
	DDX_Control(pDX, IDC_INSERTER,	m_btnArmInserter);
	DDX_Text(pDX, IDC_D_POS1, m_lMotorPos1);
	DDX_Text(pDX, IDC_D_POS2, m_lMotorPos2);
	DDX_Text(pDX, IDC_D_POS3, m_lMotorPos3);
	DDX_Text(pDX, IDC_STANDY, m_lmsc);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgMotorMontior, CDialog)
	//{{AFX_MSG_MAP(CDlgMotorMontior)
	ON_BN_CLICKED(IDC_L_COUNT, OnLCount)
	ON_BN_CLICKED(IDC_ALARM, OnAlarm)
	ON_BN_CLICKED(IDC_DRV, OnDrv)
	ON_BN_CLICKED(IDC_SERVO, OnServo)
	ON_BN_CLICKED(IDC_ERR, OnClearErr)
	ON_BN_CLICKED(IDC_R_COUNT, OnClearRCount)
	ON_BN_CLICKED(IDC_CLEAR, OnClear)
	ON_BN_CLICKED(IDC_ALL_MOTOR_SERVO_OFF, OnServoOffAllMotor)
	ON_WM_TIMER()
	ON_WM_CLOSE()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_MODIFY_PARAMETER, OnModifyParameter)
	ON_EN_CHANGE(IDC_START_SPEED, OnChangeStartSpeed)
	ON_EN_CHANGE(IDC_MAX_SPEED, OnChangeMaxSpeed)
	ON_EN_CHANGE(IDC_ACCELERATE, OnChangeAccel)
	ON_EN_CHANGE(IDC_MULTIPLE, OnChangeMul)
	ON_EN_CHANGE(IDC_DRIFT_SPEED, OnChangeDriftSpeed)
	ON_EN_CHANGE(IDC_SEARCH_SPEED, OnChangeSearchSpeed)
	ON_EN_CHANGE(IDC_JERK_SPEED, OnChangeJerk)
	ON_EN_CHANGE(IDC_IN_POS_RANGE, OnChangeInPosRange)
	ON_BN_CLICKED(IDC_GO, OnGo)
	ON_BN_CLICKED(IDC_STOP, OnStop)
	ON_BN_CLICKED(IDC_NORMAL, OnNormal)
	ON_WM_SHOWWINDOW()
	ON_BN_CLICKED(IDC_PRE_CHECK, OnPreCheck)
	ON_BN_CLICKED(IDC_PRE_CHECK2, OnPreCheck2)
	ON_BN_CLICKED(IDC_ARM_X,		OnSelect)
	ON_BN_CLICKED(IDC_ARM_Y,		OnSelect)
	ON_BN_CLICKED(IDC_ARM_Z,		OnSelect)
	ON_BN_CLICKED(IDC_INSERTER,		OnSelect)
	ON_BN_CLICKED(IDC_TORQUE, OnTorque)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgMotorMontior message handlers

BOOL CDlgMotorMontior::OnInitDialog() 
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

	m_btnModify.SetIcon(IDI_SAVE);
	m_btnModify.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnModify.SetFlat(FALSE);

	m_btnTorque.SetIcon(IDI_MANUAL_TORQUE);
	m_btnTorque.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnTorque.SetFlat(FALSE);

	m_bStop = false; 

	// Init Led 
	InitLed();

	// Init UI
	EnableUI();

	// Pre Select Motor
	OnSelect();

	// Set Timer for get Motor Status
	SetTimer(ID_TIME_GET_STATUS, _Status_Timer, NULL);

	// Pre set default value for each wnd
	UpdateData(FALSE);

	//
	f.SetTitleExtend(this, theApp.enTtileMachineFile );

	//
	f.ChangeLanguage(GetSafeHwnd());
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
void CDlgMotorMontior::QueryIO()
{
#ifdef _Demo
	m_Connection = true;

	m_InPos		= true;
	m_ZPhase	= false;
	m_pLMT		= false;
	m_nLMT		= false;
	m_Err		= false;
	m_Emg		= false;
	m_Drv		= false;
	m_Alarm		= false;
	m_Servo		= true;

	CString cs;
	cs.Format("%d", 0);
	m_wndRCount.SetWindowText(cs);
	cs.Format("%d", 0);
	m_wndLCount.SetWindowText(cs);

#else

	if(!m.Info.bCardStatus[Motor->BoardID])
	{
		m_Connection = false;
		return;
	}
	else
		m_Connection = true;
	// If LoadMotorAddress fail.
	// CardStatus will be false
	// So if Open Card fail. We just return. do nothing


	f.Motor.GetMotorStatus(Motor);

	m_InPos		= Motor->InPosReal;
	m_ZPhase	= Motor->ZPhase;
	m_pLMT		= Motor->pLMT;
	m_nLMT		= Motor->nLMT;
	m_Err		= Motor->ERRR;
	m_Emg		= Motor->EMG;
	m_Drv		= Motor->DRV;
	m_Alarm		= Motor->Alarm;
	m_Servo		= Motor->ServoOn;

	CString cs;
	cs.Format("%d", Motor->RCount);
	m_wndRCount.SetWindowText(cs);
	cs.Format("%d", Motor->LCount);
	m_wndLCount.SetWindowText(cs);
#endif
}

void CDlgMotorMontior::InitLed()
{
	m_Connection.SetLed(CLed::LED_COLOR_RED, CLed::LED_OFF);
	m_ZPhase.SetLed(CLed::LED_COLOR_RED, CLed::LED_OFF);
	m_pLMT.SetLed(CLed::LED_COLOR_RED, CLed::LED_OFF);
	m_nLMT.SetLed(CLed::LED_COLOR_RED, CLed::LED_OFF);
	m_InPos.SetLed(CLed::LED_COLOR_RED, CLed::LED_OFF);
	m_Err.SetLed(CLed::LED_COLOR_RED, CLed::LED_OFF);
	m_Emg.SetLed(CLed::LED_COLOR_RED, CLed::LED_OFF);
	m_Drv.SetLed(CLed::LED_COLOR_RED, CLed::LED_OFF);
	m_Alarm.SetLed(CLed::LED_COLOR_RED, CLed::LED_OFF);

	m_Servo.SetLed(CLed::LED_COLOR_GREEN, CLed::LED_OFF);

	m_TLC.SetLed(CLed::LED_COLOR_RED, CLed::LED_OFF);
	m_ZeroSpeed.SetLed(CLed::LED_COLOR_RED, CLed::LED_OFF);
	// 可以按的鈕為綠燈
	// 輸入訊號是紅燈

	m_ledInPos2.SetLed(CLed::LED_COLOR_RED, CLed::LED_OFF);
}

void CDlgMotorMontior::EnableUI() 
{
	// init control status . disable/enable, visable/unvisable
	BOOL bEnable;
	BOOL bShow;
	
	if( m.Info.user == enLevelSuperUser )
	{
		bEnable = true;
		bShow = true;

		m_Show = true;
		m_Mode = true;
	}
	else
	{
		bEnable = m_Mode;
		bShow = m_Show;
	}

	m_btnTorque.ShowWindow(bEnable);
	m_btnModify.ShowWindow(bEnable);
	m_wndStartSpeed.EnableWindow(bEnable);
	m_wndSearchSpeed.EnableWindow(bEnable);
	m_wndMultiple.EnableWindow(bEnable);
	m_wndMaxSpeed.EnableWindow(bEnable);
	m_wndInPosRange.EnableWindow(bEnable);
	m_wndDriffSpeed.EnableWindow(bEnable);
	m_wndAccelerate.EnableWindow(bEnable);
	m_wndJerk.EnableWindow(bEnable);
	m_btnClearCount.ShowWindow(bEnable);
	m_btnServoOffAll.ShowWindow(bEnable);
	// Enable Control

	m_btnTorque.ShowWindow(bShow);
	m_btnModify.ShowWindow(bShow);
	m_wndStartSpeed.ShowWindow(bShow);
	m_wndSearchSpeed.ShowWindow(bShow);
	m_wndMultiple.ShowWindow(bShow);
	m_wndMaxSpeed.ShowWindow(bShow);
	m_wndInPosRange.ShowWindow(bShow);
	m_wndDriffSpeed.ShowWindow(bShow);
	m_wndAccelerate.ShowWindow(bShow);
	m_wndJerk.ShowWindow(bShow);
	m_btnClearCount.ShowWindow(bShow);
	m_btnServoOffAll.ShowWindow(bShow);

	m_wndWStartSpeed.ShowWindow(bShow);
	m_wndWMaxSpeed.ShowWindow(bShow);
	m_wndWAccl.ShowWindow(bShow);
	m_wndWMulSpeed.ShowWindow(bShow);
	m_wndWDriftSpeed.ShowWindow(bShow);
	m_wndWInPos.ShowWindow(bShow);
	m_wndWSearchSpeed.ShowWindow(bShow);
	m_wndWJerk.ShowWindow(bShow);
	m_wndWGroup.ShowWindow(bShow);
	// Show Control

	m_wndStandy.ShowWindow(bShow);
	m_wndPos3.ShowWindow(bShow);
	m_wndPos2.ShowWindow(bShow);
	m_wndPos1.ShowWindow(bShow);
	m_btnGo.ShowWindow(bShow);
	m_btnStop.ShowWindow(bShow);

	m_wnddPos1.ShowWindow(bShow);
	m_wnddPos2.ShowWindow(bShow);
	m_wnddPos3.ShowWindow(bShow);
	m_wndStandy.ShowWindow(bShow);
	m_wnddStandy.ShowWindow(bShow);
	// Show Debug Control

	m_btnNormalSetting.ShowWindow(bShow);
	m_btnPreCheck.ShowWindow(bShow);
	m_btnPreCheckAll.ShowWindow(bShow);
}

void CDlgMotorMontior::OnSelect() 
{
	// The order depents on the order in rc
	UpdateData();

	switch(m_iMotor)
	{
	case 0:
		{
			Motor = &m.m_Motor.ArmX;
		}
		break;
	case 1:
		{
			Motor = &m.m_Motor.ArmY;
		}
		break;
	case 2:
		{
			Motor = &m.m_Motor.ArmZ;
		}
		break;
	case 3:
		{
			Motor = &m.m_Motor.Inserter;
		}
		break;
	case 4:
		{

		}
		break;
	default:
		break;
	}

	m_iInPosRange	=  Motor->InPosRange;
	m_iMaxSpeed		= Motor->MaxSpeed;
	m_iMultiple		= Motor->Multiple;
	m_iStartSpeed	= Motor->Start;
	m_iAccelerate	= Motor->Accelerate;
	m_iDriftSpeed	= Motor->DrifSpeed;
	m_iSearchSpeed	= Motor->SearchSpeed;
	m_iJerk			= Motor->Jerk;

	UpdateData(FALSE);
	Invalidate();

}

void CDlgMotorMontior::OnTimer(UINT nIDEvent) 
{
	switch(nIDEvent)
	{
	case ID_TIME_GET_STATUS:
		{
			QueryIO();		// for Motor status
		}
		break;
	default:
		break;
	}
	
	CDialog::OnTimer(nIDEvent);
}

void CDlgMotorMontior::OnClose() 
{
	KillTimer(ID_TIME_GET_STATUS);

	m.Info.bSubDlgOpen = false;
	f.UpdateButtonState();
	
	CDialog::OnClose();
}

void CDlgMotorMontior::OnDestroy() 
{
	KillTimer(ID_TIME_GET_STATUS);

	m.Info.bSubDlgOpen = false;
	f.UpdateButtonState();

	CDialog::OnDestroy();	
}

bool CDlgMotorMontior::MotorRun(long pulse)
{
#if _Demo
//	return true;
#endif

	// 判斷要用哪一種速度
	int bDriff;
	if( m_btnNormalSetting.GetCheck() )	// 如果要調參數. 就不使用 Driff
		bDriff = 1;
	else 
		bDriff = 0;
	
	//
	if( bDriff == 0 )
	{
		// 直接 Load Driff Speed. 用飄移速度直接跑
		f.Motor.LoadDriftSpeed( Motor );
	}
	else
	{
		bool bOK = f.Motor.LoadCycleSpeed( Motor );
		if(!bOK)
			return bOK;
	}

	int iStart = ::GetTickCount();
	int iPass = 0;

	// Wait for motor really stop
	f.Motor.GetMotorStatus(Motor);
	while(1)
	{
		if(!Motor->DRV) 
			break;

		iPass = ::GetTickCount() - iStart;
		if(!m.Info.bRunning
			|| m_bStop
			|| iPass > 30000)
		{
			return false;
		}
		f.Motor.GetMotorStatus(Motor);

		f.ThreadWait();
	}

	switch(Motor->AxisNo)
	{
	case X_Axis:
		MC8141PMotPtp(Motor->BoardID, X_Axis, 0, pulse, 0, 0, 0);
		break;
	case Y_Axis:
		MC8141PMotPtp(Motor->BoardID, Y_Axis, 0, 0, pulse, 0, 0);
		break;
	case Z_Axis:
		MC8141PMotPtp(Motor->BoardID, Z_Axis, 0, 0, 0, pulse, 0);
		break;
	case U_Axis:
		MC8141PMotPtp(Motor->BoardID, U_Axis, 0, 0, 0, 0, pulse);
		break;
	}

	iStart = ::GetTickCount();
	iPass = 0;
	// Wait for ready
	while(1)
	{
		f.Motor.GetMotorStatus(Motor);
		if(Motor->InPosReal)
			break;

		iPass = ::GetTickCount() - iStart;
		if(!m.Info.bRunning
			|| m_bStop
			|| iPass > 20000)
		{
			MC8141PMotStop(Motor->BoardID, Motor->AxisNo, Motor->AxisNo);
			return false;
		}
		else if( Motor->Alarm )
		{
			MC8141PMotStop(Motor->BoardID, Motor->AxisNo, Motor->AxisNo);
			return false;
		}

		f.ThreadWait();
	}

	return true;
}

void CDlgMotorMontior::OnOK() 
{
	if(m_fChange)
	{
		if(IDYES != AfxMessageBox("Data is modified. Save?\n",
			MB_YESNO|MB_ICONEXCLAMATION))
		{
			KillTimer(ID_TIME_GET_STATUS);
			m.Info.bSubDlgOpen = false;
			f.UpdateButtonState();
			CDialog::OnOK();
		}
		else
		{
			KillTimer(ID_TIME_GET_STATUS);
			OnModifyParameter();
			m.Info.bSubDlgOpen = false;
			f.UpdateButtonState();			
			CDialog::OnOK();
		}
		// Data already be modify.
		// So. 
		// If User say YES. We call OnOK() function to store alignment value
		// If User say NO. We did not do anything.
	}
	else
	{
		KillTimer(ID_TIME_GET_STATUS);
		m.Info.bSubDlgOpen = false;
		f.UpdateButtonState();
		CDialog::OnOK();
		// Data not be modify.
		// Just Get out the Alignment dialog.
	}	
}

void CDlgMotorMontior::OnCancel() 
{
	//
	if(m_fChange)
	{
		if(IDYES != AfxMessageBox("Data is modified. Save?\n",
			MB_YESNO|MB_ICONEXCLAMATION))
		{
			KillTimer(ID_TIME_GET_STATUS);
			m.Info.bSubDlgOpen = false;
			f.UpdateButtonState();
			CDialog::OnCancel();
		}
		else
		{
			KillTimer(ID_TIME_GET_STATUS);
			OnModifyParameter();
			m.Info.bSubDlgOpen = false;
			f.UpdateButtonState();			
			CDialog::OnCancel();
		}
		// Data already be modify.
		// So. 
		// If User say YES. We call OnOK() function to store alignment value
		// If User say NO. We did not do anything.
	}
	else
	{
		KillTimer(ID_TIME_GET_STATUS);
		m.Info.bSubDlgOpen = false;
		f.UpdateButtonState();
		CDialog::OnCancel();
		// Data not be modify.
		// Just Get out the Alignment dialog.
	}
}
////////////////////////////////////////////////////////
// On Change 
void CDlgMotorMontior::OnChangeInPosRange()
{
	m_fChange = true;
}
void CDlgMotorMontior::OnChangeStartSpeed()
{
	m_fChange = true;
}
void CDlgMotorMontior::OnChangeMaxSpeed()
{
	m_fChange = true;
}
void CDlgMotorMontior::OnChangeAccel()
{
	m_fChange = true;
}
void CDlgMotorMontior::OnChangeMul()
{
	m_fChange = true;
}
void CDlgMotorMontior::OnChangeDriftSpeed()
{
	m_fChange = true;
}
void CDlgMotorMontior::OnChangeSearchSpeed()
{
	m_fChange = true;
}
void CDlgMotorMontior::OnChangeJerk()
{
	m_fChange = true;
}
void CDlgMotorMontior::OnModifyParameter() 
{
	if( UpdateData() )
	{
		m_fChange = false;

		Motor->InPosRange		= m_iInPosRange;
		Motor->MaxSpeed			= m_iMaxSpeed;
		Motor->Multiple			= m_iMultiple;
		Motor->Start			= m_iStartSpeed;
		Motor->Accelerate		= m_iAccelerate;
		Motor->DrifSpeed		= m_iDriftSpeed;
		Motor->SearchSpeed		= m_iSearchSpeed;
		Motor->Jerk				= m_iJerk;
		
		f.SaveMotorParameter();
		
		UpdateData(FALSE);
	}
}

void CDlgMotorMontior::OnServoOffAllMotor()
{
	f.MotorServoOffAll();
	// Servo off all motor 
}
void CDlgMotorMontior::OnClear()
{
	f.Motor.MotorEncoder(Motor);
}
void CDlgMotorMontior::OnClearRCount()
{
	f.Motor.MotorEncoder(Motor);
}
void CDlgMotorMontior::OnClearErr() 
{
	if(!m_Operator)
		return;

	f.Motor.ClearMotorError(Motor);
}
void CDlgMotorMontior::OnServo()
{
	if(!m_Operator)
		return;

	f.Motor.Servo(Motor, !Motor->ServoOn);

}
void CDlgMotorMontior::OnDrv() 
{
	if(!m_Operator)
		return;

	m_bStop = true;
}
void CDlgMotorMontior::OnAlarm() 
{
	if(!m_Operator)
		return;

	f.Motor.ClearMotorAlarm(Motor);
	Sleep(1000);
	f.Motor.Servo(Motor, true);

}
void CDlgMotorMontior::OnLCount() 
{
	if(!m_Operator)
		return;

	if(Motor->DRV)
	{
		AfxMessageBox("Please wait for motor stop.");
		return;
	}

	CDlgMotorMove dlg(Motor->LCount);
	if(dlg.DoModal() != IDOK) return;

	m_bStop = false;
	bool bOK = false;
	bOK = MotorRun(dlg.m_NewGo);	
}

BOOL CDlgMotorMontior::PreTranslateMessage(MSG* pMsg) 
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

////////////////////////////////////////////////////////////////////
// Motor Run Debug Test
UINT CDlgMotorMontior::MotorMonitorThread(LPVOID p)
{
	CDlgMotorMontior *pt = (CDlgMotorMontior *)p;

	pt->m_bRunStop = false;
	pt->SetGoUI( true );

	///////////////////////////////////////
	// Set Basic Parameter
	long m_lPos1 = pt->m_lMotorPos1;
	long m_lPos2 = pt->m_lMotorPos2;
	long m_lPos3 = pt->m_lMotorPos3;
	long m_lStandy = pt->m_lmsc;
	///////////////////////////////////////

	long m_lRunner = enCodeRunOK;

	long iStatus = 0;
	while(1)
	{
		if( pt->m_bRunGo == false )
			break;
	
		if( !m.Info.bRunning )
			break;

		int iResult = iStatus % 4;
		if( iResult == 0 )
		{
			CString csPos = _T("");
			csPos.Format("Pos1: %d", m_lPos1);
			pt->m_wndMsg.SetWindowText(csPos);
			
			// 
			m_lRunner = f.Motor.ManualMotorRun( pt->Motor, m_lPos1 );
			if( m_lRunner != enCodeRunOK )
				break;

			Sleep( m_lStandy );
		}
		else if( iResult == 1 )
		{
			CString csPos = _T("");
			csPos.Format("Pos2: %d", m_lPos2);
			pt->m_wndMsg.SetWindowText(csPos);

			// 
			m_lRunner = f.Motor.ManualMotorRun( pt->Motor, m_lPos2 );
			if( m_lRunner != enCodeRunOK )
				break;

			Sleep( m_lStandy );
		}
		else if( iResult == 2 )
		{
			CString csPos = _T("");
			csPos.Format("Pos3: %d", m_lPos3);
			pt->m_wndMsg.SetWindowText(csPos);

			// 
			m_lRunner = f.Motor.ManualMotorRun( pt->Motor, m_lPos3 );
			if( m_lRunner != enCodeRunOK )
				break;

			Sleep( m_lStandy );
		}
		else if( iResult == 3 )
		{
			CString csStandy = _T("");
			csStandy.Format("Standy: %d", m_lStandy);
			pt->m_wndMsg.SetWindowText(csStandy);
			Sleep( m_lStandy );
		}
		else
			; // Nerver

		iStatus++;
		Sleep(1);
	}

	pt->SetGoUI( false );
	pt->m_bRunStop = true;	
	AfxEndThread(0);
	return 0;
}
void CDlgMotorMontior::SetGoUI(bool bGo)
{
	if( bGo )
	{
		m_btnGo.EnableWindow( FALSE );
		m_btnStop.EnableWindow( TRUE );
		m_wndPos1.EnableWindow( FALSE );
		m_wndPos2.EnableWindow( FALSE );
		m_wndPos3.EnableWindow( FALSE );
		m_wndStandy.EnableWindow( FALSE );
		m_btnCancel.EnableWindow( FALSE );
		m_btnModify.EnableWindow( FALSE );
		m_btnTorque.EnableWindow( FALSE );
	}
	else
	{
		m_btnGo.EnableWindow( TRUE );
		m_btnStop.EnableWindow( FALSE );
		m_wndPos1.EnableWindow( TRUE );
		m_wndPos2.EnableWindow( TRUE );
		m_wndPos3.EnableWindow( TRUE );
		m_wndStandy.EnableWindow( TRUE );
		m_btnCancel.EnableWindow( TRUE );
		m_btnModify.EnableWindow( TRUE );
		m_btnTorque.EnableWindow( TRUE );
	}
}
void CDlgMotorMontior::OnGo() 
{
	UpdateData();
	CString csMsg = _T("");
	csMsg.Format("[%d, %d, %d, %d msec]", m_lMotorPos1, m_lMotorPos2, m_lMotorPos3, m_lmsc );
	
	m_bRunGo = true;
	AfxBeginThread(MotorMonitorThread, this);
}

void CDlgMotorMontior::OnStop() 
{
	m_bRunGo = false;
}

BOOL CDlgMotorMontior::DestroyWindow() 
{	
	return CDialog::DestroyWindow();
}

void CDlgMotorMontior::OnNormal() 
{
	m_btnNormalSetting.Invalidate();
}

void CDlgMotorMontior::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	EnableUI(); // re-set UI
	CDialog::OnShowWindow(bShow, nStatus);	
}

void CDlgMotorMontior::OnPreCheck() 
{
	UpdateData();

	Motor->InPosRange		= m_iInPosRange;
	Motor->MaxSpeed			= m_iMaxSpeed;
	Motor->Multiple			= m_iMultiple;
	Motor->Start			= m_iStartSpeed;
	Motor->Accelerate		= m_iAccelerate;
	Motor->DrifSpeed		= m_iDriftSpeed;
	Motor->SearchSpeed		= m_iSearchSpeed;
	Motor->Jerk				= m_iJerk;
	
	long mul = (long)(Motor->Multiple * Motor->Speed / 100.);
//	MC8141PSetRange(Motor->BoardID, 0, 8000000);
	// SetSpeed

	LRESULT Res = MC8141PMotAxisParaSet(Motor->BoardID, 0,
		0xf,
		Motor->Start * mul,
		Motor->MaxSpeed * mul,
		Motor->MaxSpeed * mul,
		Motor->Accelerate * _pSpeed * mul,
		62500000 / Motor->Jerk * mul);	

	f.Motor.IsMotorErrorCode( Res );

	CString csStartSpeed = "";
	CString csMaxSpeed	 = "";
	CString csAcc		 = "";
	CString csAK		 = "";

	csStartSpeed.Format("%d", Motor->Start * mul );
	csMaxSpeed.Format("%d",   Motor->MaxSpeed * mul );
	csAcc.Format("%d", Motor->Accelerate * _pSpeed * mul );
	csAK.Format("%d", 62500000 / Motor->Jerk * mul );
	
	CString csResult = _T("");
	csResult.Format("Start: %s MaxSpeed: %s Acc: %s AK: %s",
					 csStartSpeed,
					 csMaxSpeed,
					 csAcc,
					 csAK );

//	AfxMessageBox( csResult );
}

void CDlgMotorMontior::OnPreCheck2() 
{
	for( int i=1;i<100;i++)
	{		
		UpdateData();
		
		Motor->InPosRange		= m_iInPosRange;
		Motor->MaxSpeed			= m_iMaxSpeed;
		Motor->Multiple			= m_iMultiple;
		Motor->Start			= m_iStartSpeed;
		Motor->Accelerate		= m_iAccelerate;
		Motor->DrifSpeed		= m_iDriftSpeed;
		Motor->SearchSpeed		= m_iSearchSpeed;
		Motor->Jerk				= m_iJerk;
		
		long mul = (long)(Motor->Multiple * i / 100.);
//		MC8141PSetRange(Motor->BoardID, 0, 8000000);
		// SetSpeed
		
		LRESULT Res = MC8141PMotAxisParaSet(Motor->BoardID, 0,
			0xf,
			Motor->Start * mul,
			Motor->MaxSpeed * mul,
			Motor->MaxSpeed * mul,
			Motor->Accelerate * _pSpeed * mul,
			62500000 / Motor->Jerk * mul);	
		
		f.Motor.IsMotorErrorCode( Res );

		if( Res != ERROR_SUCCESS )
		{
			CString cs;
			cs.Format("Prescent :%d", i );
			AfxMessageBox( cs );
//			break;
		}
	}
}

void CDlgMotorMontior::OnTorque() 
{
	CDlgTorqueTool dlg;
	dlg.DoModal();

	//
	m.Info.bSubDlgOpen = true;
	f.UpdateButtonState();
}
