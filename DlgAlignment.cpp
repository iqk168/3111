// DlgAlignment.cpp : implementation file
//

#include "stdafx.h"
#include "deer.h"
#include "DlgAlignment.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgAlignment dialog


CDlgAlignment::CDlgAlignment(bool key, CWnd* pParent /*=NULL*/)
	: CDialog(CDlgAlignment::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgAlignment)
	m_iAlignmentInputArmX = 0;
	m_iAlignmentInputArmY = 0;
	m_iAlignmentInputArmZ = 0;
	m_iAlignmentOutputArmX = 0;
	m_iAlignmentOutputArmY = 0;
	m_iAlignmentOutputArmZ = 0;
	m_iAlignmentRotatorArmX = 0;
	m_iAlignmentRotatorArmY = 0;
	m_iAlignmentRotatorArmZ = 0;
	m_iAlignmentSocketArmX = 0;
	m_iAlignmentSocketArmY = 0;
	m_iAlignmentSocketArmZ = 0;
	m_iAlignmentShuttleArmX = 0;
	m_iAlignmentShuttleArmY = 0;
	m_iAlignmentShuttleArmZ = 0;
	m_iAlignmentTSPick = 0;
	m_iAlignmentTSContact = 0;
	//}}AFX_DATA_INIT

	// Init dialog value 
	m_Align = m.m_Align;	// only change by read motor.!

	m_fChange = false;	

	m_key = key;

	m_bAlignmentAlive = false;

	m_lAlignmentPosition = 0;

	m_lAlignmentGoPosition = 100;
}


void CDlgAlignment::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgAlignment)
	DDX_Control(pDX, IDC_P_LMT,						m_ledShuttlePLmt);
	DDX_Control(pDX, IDC_N_LMT,						m_ledShuttleNLmt);
	DDX_Control(pDX, IDC_LED_SHUTTLE,				m_ledShuttle);
	DDX_Control(pDX, IDC_ROTATOR_GRP,				m_wndRotatorGrp);
	DDX_Control(pDX, IDOK,							m_btnOK);
	DDX_Control(pDX, IDCANCEL,						m_btnCancel);
	DDX_Text(pDX, IDC_ALIGNMENT_INPUT_ARM_X,		m_iAlignmentInputArmX);
	DDX_Text(pDX, IDC_ALIGNMENT_INPUT_ARM_Y,		m_iAlignmentInputArmY);
	DDX_Text(pDX, IDC_ALIGNMENT_INPUT_ARM_Z,		m_iAlignmentInputArmZ);
	DDX_Text(pDX, IDC_ALIGNMENT_OUTPUT_ARM_X,		m_iAlignmentOutputArmX);
	DDX_Text(pDX, IDC_ALIGNMENT_OUTPUT_ARM_Y,		m_iAlignmentOutputArmY);
	DDX_Text(pDX, IDC_ALIGNMENT_OUTPUT_ARM_Z,		m_iAlignmentOutputArmZ);
	DDX_Text(pDX, IDC_ALIGNMENT_ROTATOR_ARM_X,		m_iAlignmentRotatorArmX);
	DDX_Text(pDX, IDC_ALIGNMENT_ROTATOR_ARM_Y,		m_iAlignmentRotatorArmY);
	DDX_Text(pDX, IDC_ALIGNMENT_ROTATOR_ARM_Z,		m_iAlignmentRotatorArmZ);
	DDX_Text(pDX, IDC_ALIGNMENT_SOCKET_ARM_X,		m_iAlignmentSocketArmX);
	DDX_Text(pDX, IDC_ALIGNMENT_SOCKET_ARM_Y,		m_iAlignmentSocketArmY);
	DDX_Text(pDX, IDC_ALIGNMENT_SOCKET_ARM_Z,		m_iAlignmentSocketArmZ);
	DDX_Text(pDX, IDC_ALIGNMENT_SHUTTLE_ARM_X,		m_iAlignmentShuttleArmX);
	DDX_Text(pDX, IDC_ALIGNMENT_SHUTTLE_ARM_Y,		m_iAlignmentShuttleArmY);
	DDX_Text(pDX, IDC_ALIGNMENT_SHUTTLE_ARM_Z,		m_iAlignmentShuttleArmZ);
	DDX_Text(pDX, IDC_ALIGNMENT_TS_PICK,			m_iAlignmentTSPick);
	DDX_Text(pDX, IDC_ALIGNMENT_TS_CONT,			m_iAlignmentTSContact);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgAlignment, CDialog)
	//{{AFX_MSG_MAP(CDlgAlignment)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_ALIGNMENT_INPUT_READ,			OnAlignmentInputRead)
	ON_BN_CLICKED(IDC_ALIGNMENT_OUTPUT_READ,		OnAlignmentOutputRead)
	ON_BN_CLICKED(IDC_ALIGNMENT_SOCKET_READ,		OnAlignmentSocketRead)
	ON_BN_CLICKED(IDC_ALIGNMENT_ROTATOR_READ,		OnAlignmentRotatorRead)
	ON_WM_SHOWWINDOW()
	ON_EN_CHANGE(IDC_ALIGNMENT_INPUT_ARM_X,			OnChangeAlignmentInputArmX)
	ON_EN_CHANGE(IDC_ALIGNMENT_INPUT_ARM_Y,			OnChangeAlignmentInputArmY)
	ON_EN_CHANGE(IDC_ALIGNMENT_INPUT_ARM_Z,			OnChangeAlignmentInputArmZ)
	ON_EN_CHANGE(IDC_ALIGNMENT_OUTPUT_ARM_X,		OnChangeAlignmentOutputArmX)
	ON_EN_CHANGE(IDC_ALIGNMENT_OUTPUT_ARM_Y,		OnChangeAlignmentOutputArmY)
	ON_EN_CHANGE(IDC_ALIGNMENT_OUTPUT_ARM_Z,		OnChangeAlignmentOutputArmZ)
	ON_EN_CHANGE(IDC_ALIGNMENT_SOCKET_ARM_X,		OnChangeAlignmentSocketArmX)
	ON_EN_CHANGE(IDC_ALIGNMENT_SOCKET_ARM_Y,		OnChangeAlignmentSocketArmY)
	ON_EN_CHANGE(IDC_ALIGNMENT_SOCKET_ARM_Z,		OnChangeAlignmentSocketArmZ)
	ON_EN_CHANGE(IDC_ALIGNMENT_ROTATOR_ARM_X,		OnChangeAlignmentRotatorArmX)
	ON_EN_CHANGE(IDC_ALIGNMENT_ROTATOR_ARM_Y,		OnChangeAlignmentRotatorArmY)
	ON_EN_CHANGE(IDC_ALIGNMENT_ROTATOR_ARM_Z,		OnChangeAlignmentRotatorArmZ)
	ON_BN_CLICKED(IDC_ALIGNMENT_SHUTTLE_READ,		OnAlignmentShuttleRead)
	ON_BN_CLICKED(IDC_ALIGNMENT_TS_SH_READ,			OnAlignmentTsShRead)
	ON_BN_CLICKED(IDC_ALIGNMENT_TS_CO_READ,			OnAlignmentTsCoRead)
	ON_EN_CHANGE(IDC_ALIGNMENT_SHUTTLE_ARM_X,		OnChangeAlignmentShuttleArmX)
	ON_EN_CHANGE(IDC_ALIGNMENT_SHUTTLE_ARM_Y,		OnChangeAlignmentShuttleArmY)
	ON_EN_CHANGE(IDC_ALIGNMENT_SHUTTLE_ARM_Z,		OnChangeAlignmentShuttleArmZ)
	ON_EN_CHANGE(IDC_ALIGNMENT_TS_PICK,				OnChangeAlignmentTsPick)
	ON_EN_CHANGE(IDC_ALIGNMENT_TS_CONT,				OnChangeAlignmentTsCont)
	ON_BN_CLICKED(IDC_LED_SHUTTLE, OnLedShuttle)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgAlignment message handlers

void CDlgAlignment::SaveData()
{
	// copy the dialog value to golbal parameter.
	m.m_Align = m_Align;

	//
	f.SaveAlignment();

	//
	f.SetTrayData();
}
void CDlgAlignment::GetValueFromUI()
{
	if( !m_key)
		return;

	UpdateData();

	// Input
	m_Align.Input.x			= m_iAlignmentInputArmX;
	m_Align.Input.y			= m_iAlignmentInputArmY;
	m_Align.Input.z			= m_iAlignmentInputArmZ;
	m_Align.Input.z2		= m_iAlignmentInputArmZ;

	// Output
	m_Align.Output1.x		= m_iAlignmentOutputArmX;
	m_Align.Output1.y		= m_iAlignmentOutputArmY;
	m_Align.Output1.z		= m_iAlignmentOutputArmZ;
	m_Align.Output1.z2		= m_iAlignmentOutputArmZ;;

	// Rotator
	m_Align.Rotator.x		= m_iAlignmentRotatorArmX;
	m_Align.Rotator.y		= m_iAlignmentRotatorArmY;
	m_Align.Rotator.z		= m_iAlignmentRotatorArmZ;
	m_Align.Rotator.z2		= m_iAlignmentRotatorArmZ;

	// Socket
	m_Align.Socket.x		= m_iAlignmentSocketArmX;
	m_Align.Socket.y		= m_iAlignmentSocketArmY;
	m_Align.Socket.z		= m_iAlignmentSocketArmZ;
	m_Align.Socket.z2		= m_iAlignmentSocketArmZ;

	// Shuttle In / Output
	m_Align.Shuttle.x		= m_iAlignmentShuttleArmX;
	m_Align.Shuttle.y		= m_iAlignmentShuttleArmY;
	m_Align.Shuttle.z		= m_iAlignmentShuttleArmZ;
	m_Align.Shuttle.z2		= m_iAlignmentShuttleArmZ;

	// 計算 Shuttle input
	m_Align.DutIn.x			= m_Align.Shuttle.x;
	m_Align.DutIn.y			= m_Align.Shuttle.y;
	m_Align.DutIn.z			= m_Align.Shuttle.z;
	m_Align.DutIn.z2		= m_Align.Shuttle.z2;

	// 計算 Shuttle output
	m_Align.DutOut.x		= m_Align.Shuttle.x;
	m_Align.DutOut.y		= m_Align.Shuttle.y;
	m_Align.DutOut.z		= m_Align.Shuttle.z;
	m_Align.DutOut.z2		= m_Align.Shuttle.z2;	

	// Test Site
	// 計算 
	m_Align.TestSite.pick	= m_iAlignmentTSPick;
	m_Align.TestSite.place	= m_iAlignmentTSPick;
	m_Align.TestSite.home	= m_iAlignmentTSPick;
	m_Align.TestSite.contact = m_iAlignmentTSContact;
}
void CDlgAlignment::OnOK() 
{
//	GetValueFromUI();
	
	SaveData();

	//
	m.Info.bSubDlgOpen = false;
	m.Info.bAlignment = false;
	f.UpdateButtonState();
	
	CDialog::OnOK();
}

void CDlgAlignment::OnCancel() 
{
	if(m_fChange)
	{
		if(IDYES != AfxMessageBox("Data is modified. Save?\n",
			MB_YESNO|MB_ICONEXCLAMATION))
		{
			m.Info.bSubDlgOpen = false;
			m.Info.bAlignment = false;
			f.UpdateButtonState();
			CDialog::OnCancel();
		}
		else
			OnOK();
	}
	else
	{
		m.Info.bSubDlgOpen = false;
		m.Info.bAlignment = false;
		f.UpdateButtonState();
		CDialog::OnCancel();		
	}

	CDialog::OnCancel();
}

BOOL CDlgAlignment::PreTranslateMessage(MSG* pMsg) 
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

BOOL CDlgAlignment::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m.Info.bSubDlgOpen = true;
	m.Info.bAlignment = true;
	f.UpdateButtonState();

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
	InitTips();

	//
	InitMotor();

	//
	InitTimer();

	//
	InitLed();

	//
	f.SetTitleExtend(this, theApp.enTtileMachineFile );

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
UINT CDlgAlignment::TestSiteMoveThread(LPVOID p)
{
	CDlgAlignment *pt = (CDlgAlignment *)p;
	pt->m_bAlignmentAlive = true;

	m.RemoteOutSet.BtnRetryOn = true;
	m.RemoteOutSet.BtnSkipOn = true;

	long m_iRunError = enCodeRunOK;

	while(1)
	{
		// Down
		if( m.RemoteOutSet.BtnSkipOn && 
			(m.RemoteInStatus.BtnSkipPushed == _IOButtonOn || m.PanelButton.BtnSkipPushed ))
		{
			m.RemoteOutSet.BtnSkipOn = false;
			m.RemoteOutSet.BtnRetryOn = false;
			m.PanelButton.BtnSkipPushed = false;

			//
			m_iRunError = f.Motor.ManualMotorRunSoftTLC(&m.m_Motor.Inserter, 
				1000, false, m.TimerSetting.iMotorRunTimeout );

			//
			m.RemoteOutSet.BtnSkipOn = true;
			m.RemoteOutSet.BtnRetryOn = true;
		}
		// Up
		else if( m.RemoteOutSet.BtnRetryOn && 
			(m.RemoteInStatus.BtnRetryPushed == _IOButtonOn || m.PanelButton.BtnRetryPushed ))
		{
			m.RemoteOutSet.BtnSkipOn = false;
			m.RemoteOutSet.BtnRetryOn = false;
			m.PanelButton.BtnRetryPushed = false;

			AfxMessageBox("Up");

			m.RemoteOutSet.BtnSkipOn = true;
			m.RemoteOutSet.BtnRetryOn = true;		
		}
		
		if( !m.Info.bRunning )
			break;

		if( pt->m_bAlignmentAlive == false )
			break;

		Sleep(1);
	}

//	AfxMessageBox("Thread Close");

	return 0;
}
void CDlgAlignment::InitValue()
{
	// Input
	m_iAlignmentInputArmX	= m_Align.Input.x;
	m_iAlignmentInputArmY	= m_Align.Input.y;
	m_iAlignmentInputArmZ	= m_Align.Input.z;

	// Output
	m_iAlignmentOutputArmX	= m_Align.Output1.x;
	m_iAlignmentOutputArmY	= m_Align.Output1.y;
	m_iAlignmentOutputArmZ	= m_Align.Output1.z;

	// Rotator
	m_iAlignmentRotatorArmX = m_Align.Rotator.x;
	m_iAlignmentRotatorArmY = m_Align.Rotator.y;
	m_iAlignmentRotatorArmZ = m_Align.Rotator.z;

	// Socket
	m_iAlignmentSocketArmX	= m_Align.Socket.x;
	m_iAlignmentSocketArmY	= m_Align.Socket.y;
	m_iAlignmentSocketArmZ	= m_Align.Socket.z;

	// Shuttle Input / Output 
	m_iAlignmentShuttleArmX = m_Align.Shuttle.x;
	m_iAlignmentShuttleArmY = m_Align.Shuttle.y;
	m_iAlignmentShuttleArmZ = m_Align.Shuttle.z;

	// Test Site 
	m_iAlignmentTSPick		= m_Align.TestSite.pick;
	m_iAlignmentTSContact	= m_Align.TestSite.contact;

	UpdateData(FALSE);

	m_fChange = false;	
}
void CDlgAlignment::InitMotor()
{
//	if( m.Setting.m_bEnableRemoteIO == 1 )
//		f.MotorServoOffForAlignmentNoTs();
//	else
		f.MotorServoOffForAlignment();
}
void CDlgAlignment::InitLed()
{
	m_ledShuttle.SetLed(CLed::LED_COLOR_GREEN);
	m_ledShuttleNLmt.SetLed(CLed::LED_COLOR_RED);
	m_ledShuttlePLmt.SetLed(CLed::LED_COLOR_RED);
}
void CDlgAlignment::InitTips()
{
	// Tips 
	// Init Tips
	m_ToolTip.Create(this);
	m_ToolTip.SetMaxTipWidth(800);
	m_ToolTip.SetDelayTime( TTDT_AUTOPOP, 10000 );
	m_ToolTip.SetDelayTime( TTDT_INITIAL, 25 );
	m_ToolTip.EnableToolTips(true);

	//
	m_ToolTip.AddTool( GetDlgItem(IDC_ALIGNMENT_INPUT_READ),	_T("Read ArmXYZ Motor RCount Value With Input Alignment Position") );
	m_ToolTip.AddTool( GetDlgItem(IDC_ALIGNMENT_OUTPUT_READ),	_T("Read ArmXYZ Motor RCount Value With Output Alignment Position") );
	m_ToolTip.AddTool( GetDlgItem(IDC_ALIGNMENT_SOCKET_READ),	_T("Read ArmXYZ Motor RCount Value With Socket Alignment Position") );
	m_ToolTip.AddTool( GetDlgItem(IDC_ALIGNMENT_ROTATOR_READ),	_T("Read ArmXYZ Motor RCount Value With Rotator Alignment Position") );
	m_ToolTip.AddTool( GetDlgItem(IDC_ALIGNMENT_SHUTTLE_READ),	_T("Read ArmXYZ Motor RCount Value With Shuttle Alignment Position") );
	m_ToolTip.AddTool( GetDlgItem(IDC_ALIGNMENT_TS_SH_READ),	_T("Read ArmXYZ Motor RCount Value With TestSite/Pick Alignment Position") );
	m_ToolTip.AddTool( GetDlgItem(IDC_ALIGNMENT_TS_CO_READ),	_T("Read ArmXYZ Motor RCount Value With TestSite/Contact Alignment Position") );

	//
	m_ToolTip.AddTool( GetDlgItem(IDC_STATIC_STACK_X),	_T("Arm x stack motor encoder value") );
	m_ToolTip.AddTool( GetDlgItem(IDC_STATIC_STACK_Y),	_T("Arm y stack motor encoder value") );
	m_ToolTip.AddTool( GetDlgItem(IDC_STATIC_STACK_Z),	_T("Arm z stack motor encoder value") );

	m_ToolTip.AddTool( GetDlgItem(IDC_STATIC_SH_X),		_T("Arm x shuttle motor encoder value") );
	m_ToolTip.AddTool( GetDlgItem(IDC_STATIC_SH_Y),		_T("Arm y shuttle motor encoder value") );
	m_ToolTip.AddTool( GetDlgItem(IDC_STATIC_SH_Z),		_T("Arm z shuttle motor encoder value") );
	
	m_ToolTip.AddTool( GetDlgItem(IDC_STATIC_TS_SH),	_T("Test site motor encoder value(shuttle)") );
	m_ToolTip.AddTool( GetDlgItem(IDC_STATIC_TS_CT),	_T("Test site motor encoder value(socket)") );
}

void CDlgAlignment::InitTimer()
{
	SetTimer( ID_TIME_ALIGNMENT_IO, 100, NULL);
}
void CDlgAlignment::IOQuery()
{
#ifdef _Demo
	
	m_ledShuttle = m.OutSet.Shuttle			== 0 ? false : true;

	if( m.OutSet.Shuttle )
	{
		m_ledShuttleNLmt = m.InStatus.ShuttleNLmt	= false;
		m_ledShuttlePLmt = m.InStatus.ShuttlePLmt	= true;
	}
	else
	{
		m_ledShuttleNLmt = m.InStatus.ShuttleNLmt	= true;
		m_ledShuttlePLmt = m.InStatus.ShuttlePLmt	= false;
	}
#else
	m_ledShuttle = m.OutStatus.Shuttle			== 0 ? false : true;
	m_ledShuttleNLmt = m.InStatus.ShuttleNLmt	== _ShuttleNLmtOff ? false : true;
	m_ledShuttlePLmt = m.InStatus.ShuttlePLmt	== _ShuttlePLmtOff ? false : true;
#endif
}
void CDlgAlignment::ReDrawUIForKeyIn()
{
	if(m_key)
	{	
		// Input 
		GetDlgItem(IDC_ALIGNMENT_INPUT_ARM_X)->EnableWindow( TRUE );
		GetDlgItem(IDC_ALIGNMENT_INPUT_ARM_Y)->EnableWindow( TRUE );
		GetDlgItem(IDC_ALIGNMENT_INPUT_ARM_Z)->EnableWindow( TRUE );
		// Output
		GetDlgItem(IDC_ALIGNMENT_OUTPUT_ARM_X)->EnableWindow( TRUE );
		GetDlgItem(IDC_ALIGNMENT_OUTPUT_ARM_Y)->EnableWindow( TRUE );
		GetDlgItem(IDC_ALIGNMENT_OUTPUT_ARM_Z)->EnableWindow( TRUE );
		// Rotator
		GetDlgItem(IDC_ALIGNMENT_ROTATOR_ARM_X)->EnableWindow( TRUE );	
		GetDlgItem(IDC_ALIGNMENT_ROTATOR_ARM_Y)->EnableWindow( TRUE );	
		GetDlgItem(IDC_ALIGNMENT_ROTATOR_ARM_Z)->EnableWindow( TRUE );	
		// Socket
		GetDlgItem(IDC_ALIGNMENT_SOCKET_ARM_X)->EnableWindow( TRUE );
		GetDlgItem(IDC_ALIGNMENT_SOCKET_ARM_Y)->EnableWindow( TRUE );	
		GetDlgItem(IDC_ALIGNMENT_SOCKET_ARM_Z)->EnableWindow( TRUE );
		// Shuttle
		GetDlgItem(IDC_ALIGNMENT_SHUTTLE_ARM_X)->EnableWindow( TRUE );
		GetDlgItem(IDC_ALIGNMENT_SHUTTLE_ARM_Y)->EnableWindow( TRUE );
		GetDlgItem(IDC_ALIGNMENT_SHUTTLE_ARM_Z)->EnableWindow( TRUE );

		// Test Site
		GetDlgItem(IDC_ALIGNMENT_TS_PICK)->EnableWindow( TRUE );
		GetDlgItem(IDC_ALIGNMENT_TS_CONT)->EnableWindow( TRUE );
	}
}
void CDlgAlignment::ReDrawUI()
{
	if( m.Setting.m_bRotatoUse == 1 )
		m_wndRotatorGrp.ShowWindow( TRUE );
	else
		m_wndRotatorGrp.ShowWindow( FALSE );
}
void CDlgAlignment::GetMotorPosition()
{
	f.Motor.GetMotorStatus( &m.m_Motor.ArmX );
	f.Motor.GetMotorStatus( &m.m_Motor.ArmY );
	f.Motor.GetMotorStatus( &m.m_Motor.ArmZ );
	f.Motor.GetMotorStatus( &m.m_Motor.Inserter );
}
void CDlgAlignment::CheckSuperUser()
{

}
void CDlgAlignment::OnTimer(UINT nIDEvent) 
{
	switch(nIDEvent)
	{
	case ID_TIME_ALIGNMENT_IO:
		IOQuery();	
		break;
	default:
		break;
	}	
	CDialog::OnTimer(nIDEvent);
}

void CDlgAlignment::OnAlignmentInputRead() 
{
	GetMotorPosition();

	m_iAlignmentInputArmX = m.m_Motor.ArmX.RCount;
	m_iAlignmentInputArmY = m.m_Motor.ArmY.RCount;
	m_iAlignmentInputArmZ = m.m_Motor.ArmZ.RCount;

	m_Align.Input.x		  = m_iAlignmentInputArmX;
	m_Align.Input.y		  = m_iAlignmentInputArmY;
	m_Align.Input.z		  = m_iAlignmentInputArmZ + ( _FixInputOuputZ * m.m_Ratio.Z_GearRation );
	m_Align.Input.z2	  = m_iAlignmentInputArmZ + ( _FixInputOuputZ * m.m_Ratio.Z_GearRation ) + ( _ArmZPlace * m.m_Ratio.Z_GearRation );

	UpdateData(FALSE);
}

void CDlgAlignment::OnAlignmentOutputRead() 
{
	GetMotorPosition();

	m_iAlignmentOutputArmX = m.m_Motor.ArmX.RCount;
	m_iAlignmentOutputArmY = m.m_Motor.ArmY.RCount;
	m_iAlignmentOutputArmZ = m.m_Motor.ArmZ.RCount;
	
	m_Align.Output1.x	   = m_iAlignmentOutputArmX;
	m_Align.Output1.y	   = m_iAlignmentOutputArmY;
	m_Align.Output1.z	   = m_iAlignmentOutputArmZ + ( _FixInputOuputZ * m.m_Ratio.Z_GearRation );
	m_Align.Output1.z2	   = m_iAlignmentOutputArmZ + ( _FixInputOuputZ * m.m_Ratio.Z_GearRation ) + ( _ArmZPlace * m.m_Ratio.Z_GearRation );

	UpdateData(FALSE);
}

void CDlgAlignment::OnAlignmentSocketRead() 
{
	GetMotorPosition();

	m_iAlignmentSocketArmX = m.m_Motor.ArmX.RCount;
	m_iAlignmentSocketArmY = m.m_Motor.ArmY.RCount;
	m_iAlignmentSocketArmZ = m.m_Motor.ArmZ.RCount;

	m_Align.Socket.x	   = m_iAlignmentSocketArmX;
	m_Align.Socket.y	   = m_iAlignmentSocketArmY;
	m_Align.Socket.z	   = m_iAlignmentSocketArmZ;
	m_Align.Socket.z2	   = m_iAlignmentSocketArmZ + ( _ArmZPlace * m.m_Ratio.Z_GearRation );

	UpdateData(FALSE);
}

void CDlgAlignment::OnAlignmentRotatorRead() 
{
	GetMotorPosition();

	m_iAlignmentRotatorArmX = m.m_Motor.ArmX.RCount;
	m_iAlignmentRotatorArmY = m.m_Motor.ArmY.RCount;
	m_iAlignmentRotatorArmZ = m.m_Motor.ArmZ.RCount;

	m_Align.Rotator.x		= m_iAlignmentRotatorArmX;
	m_Align.Rotator.y		= m_iAlignmentRotatorArmY;
	m_Align.Rotator.z		= m_iAlignmentRotatorArmZ + ( _ArmRotaotr * m.m_Ratio.Z_GearRation );
	m_Align.Rotator.z2		= m_iAlignmentRotatorArmZ + ( _ArmRotaotr * m.m_Ratio.Z_GearRation) + ( _ArmZPlace * m.m_Ratio.Z_GearRation );

	UpdateData(FALSE);
}
void CDlgAlignment::OnAlignmentShuttleRead() 
{
	GetMotorPosition();

	m_iAlignmentShuttleArmX = m.m_Motor.ArmX.RCount;
	m_iAlignmentShuttleArmY = m.m_Motor.ArmY.RCount;
	m_iAlignmentShuttleArmZ = m.m_Motor.ArmZ.RCount;

	m_Align.Shuttle.x		= m_iAlignmentShuttleArmX;
	m_Align.Shuttle.y		= m_iAlignmentShuttleArmY + ( _ShuttleOutput * m.m_Ratio.Y_GearRation );
	m_Align.Shuttle.z		= m_iAlignmentShuttleArmZ + ( _ShuttleOutputZ * m.m_Ratio.Z_GearRation );
	m_Align.Shuttle.z2		= m_iAlignmentShuttleArmZ + ( _ArmZPlace * m.m_Ratio.Z_GearRation ) + ( _ShuttleOutputZ * m.m_Ratio.Z_GearRation );

	// 計算 Shuttle input
	m_Align.DutIn.x			= m_Align.Shuttle.x;
	m_Align.DutIn.y			= m_Align.Shuttle.y;
	m_Align.DutIn.z			= m_Align.Shuttle.z;
	m_Align.DutIn.z2		= m_Align.Shuttle.z2;

	// 計算 Shuttle output
	m_Align.DutOut.x		= m_Align.Shuttle.x;
	m_Align.DutOut.y		= m_Align.Shuttle.y;
	m_Align.DutOut.z		= m_Align.Shuttle.z;
	m_Align.DutOut.z2		= m_Align.Shuttle.z2;

	UpdateData(FALSE);
}

void CDlgAlignment::OnAlignmentTsShRead() 
{
	GetMotorPosition();

	m_iAlignmentTSPick = m.m_Motor.Inserter.RCount;

	// 計算 
	m_Align.TestSite.pick	= m_iAlignmentTSPick;
	m_Align.TestSite.place	= m_iAlignmentTSPick + ( _TestSitePickToPlace * m.m_Ratio.Inserter_GearRation );
	m_Align.TestSite.home	= m_iAlignmentTSPick + ( _TestSitePickToHome * m.m_Ratio.Inserter_GearRation );

	UpdateData(FALSE);
}

void CDlgAlignment::OnAlignmentTsCoRead() 
{
	GetMotorPosition();

	m_iAlignmentTSContact = m.m_Motor.Inserter.RCount;
	
	m_Align.TestSite.contact = m_iAlignmentTSContact;

	UpdateData(FALSE);
}

void CDlgAlignment::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	if(bShow)
		ReDrawUI();

	if(bShow)
		ReDrawUIForKeyIn();

	CDialog::OnShowWindow(bShow, nStatus);	
}
void CDlgAlignment::OnChangeAlignmentInputArmX() 
{
	m_fChange = true;	
}
void CDlgAlignment::OnChangeAlignmentInputArmY() 
{
	m_fChange = true;	
}
void CDlgAlignment::OnChangeAlignmentInputArmZ() 
{
	m_fChange = true;	
}
void CDlgAlignment::OnChangeAlignmentOutputArmX() 
{
	m_fChange = true;	
}
void CDlgAlignment::OnChangeAlignmentOutputArmY() 
{	
	m_fChange = true;	
}
void CDlgAlignment::OnChangeAlignmentOutputArmZ() 
{
	m_fChange = true;	
}
void CDlgAlignment::OnChangeAlignmentSocketArmX() 
{
	m_fChange = true;	
}
void CDlgAlignment::OnChangeAlignmentSocketArmY() 
{
	m_fChange = true;	
}
void CDlgAlignment::OnChangeAlignmentSocketArmZ() 
{
	m_fChange = true;	
}
void CDlgAlignment::OnChangeAlignmentRotatorArmX() 
{
	m_fChange = true;	
}
void CDlgAlignment::OnChangeAlignmentRotatorArmY() 
{
	m_fChange = true;	
}
void CDlgAlignment::OnChangeAlignmentRotatorArmZ() 
{
	m_fChange = true;	
}
void CDlgAlignment::OnChangeAlignmentShuttleArmX() 
{
	m_fChange = true;	
}
void CDlgAlignment::OnChangeAlignmentShuttleArmY() 
{
	m_fChange = true;	
}
void CDlgAlignment::OnChangeAlignmentShuttleArmZ() 
{
	m_fChange = true;	
}
void CDlgAlignment::OnChangeAlignmentTsPick() 
{
	m_fChange = true;	
}
void CDlgAlignment::OnChangeAlignmentTsCont() 
{
	m_fChange = true;	
}

void CDlgAlignment::OnLedShuttle() 
{
	long m_iNowAlignmentTSPosition = m.m_Motor.Inserter.RCount;
	if( m_iNowAlignmentTSPosition > ( m.Setting.m_dTestSiteProf ) )
	{
		CString csMsg = _T("");
		csMsg.Format("Test site head position maybe too lower, Please make sure safty? If OK then click Yes\n");
		if(IDYES != AfxMessageBox(csMsg, MB_YESNO|MB_ICONEXCLAMATION))
		{
			return;
		}	
	}

	m.OutSet.Shuttle = !m.OutStatus.Shuttle;
}
