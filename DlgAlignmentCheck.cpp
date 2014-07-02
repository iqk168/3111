// DlgAlignmentCheck.cpp : implementation file
//

#include "stdafx.h"
#include "deer.h"
#include "DlgAlignmentCheck.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgAlignmentCheck dialog


CDlgAlignmentCheck::CDlgAlignmentCheck(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgAlignmentCheck::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgAlignmentCheck)
	m_iInputPos = 0;
	m_iOutputPos = 0;
	//}}AFX_DATA_INIT

	m_ArmXPos = 0;
	m_ArmYPos = 0;
	m_ArmZPos = 0;
	m_TestSiteArmPos = 0;
	m_TestSiteArmHomePos = 0;
	m_ShuttlePos = 0; // default home
	px.x = 0;
	px.y = 0;
}


void CDlgAlignmentCheck::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgAlignmentCheck)
	DDX_Control(pDX, IDC_INPUT_MOVE,				m_btnMoveOutputPos);
	DDX_Control(pDX, IDC_OUTPUT_MOVE,				m_btnMoveInputPos);
	DDX_Control(pDX, IDC_SHUTTLE_PICKPLACE,			m_btnMoveShuttlePP);
	DDX_Control(pDX, IDC_SHUTTLE_HOME,				m_btnMoveShuttleHome);
	DDX_Control(pDX, IDC_M_TEST_SITE_PLACE,			m_btnMoveTSPlace);
	DDX_Control(pDX, IDC_M_TEST_SITE_PICK,			m_btnMoveTSPick);
	DDX_Control(pDX, IDC_M_TEST_SITE_CONTACT,		m_btnMoveTSContact);
	DDX_Control(pDX, IDC_M_MOVE_HOME,				m_btnMoveHome);
	DDX_Control(pDX, IDC_M_MOVE_SHUTTLE,			m_btnMoveShuttle);
	DDX_Control(pDX, IDC_M_MOVE_OUTPUT,				m_btnMoveOutput);
	DDX_Control(pDX, IDC_M_MOVE_INPUT,				m_btnMoveInput);
	DDX_Control(pDX, IDCANCEL,						m_btnCancel);
	DDX_Control(pDX, IDOK,							m_btnOK);
	DDX_Text(pDX, IDC_E_INPUT_POS,					m_iInputPos);
	DDX_Text(pDX, IDC_E_OUTPUT_POS,					m_iOutputPos);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgAlignmentCheck, CDialog)
	//{{AFX_MSG_MAP(CDlgAlignmentCheck)
	ON_WM_TIMER()
	ON_WM_SHOWWINDOW()
	ON_BN_CLICKED(IDC_M_MOVE_INPUT, OnMMoveInput)
	ON_BN_CLICKED(IDC_M_MOVE_OUTPUT, OnMMoveOutput)
	ON_BN_CLICKED(IDC_M_MOVE_SHUTTLE, OnMMoveShuttle)
	ON_BN_CLICKED(IDC_M_MOVE_HOME, OnMMoveHome)
	ON_BN_CLICKED(IDC_M_TEST_SITE_PICK, OnMTestSitePick)
	ON_BN_CLICKED(IDC_M_TEST_SITE_PLACE, OnMTestSitePlace)
	ON_BN_CLICKED(IDC_M_TEST_SITE_CONTACT, OnMTestSiteContact)
	ON_BN_CLICKED(IDC_SHUTTLE_HOME, OnShuttleHome)
	ON_BN_CLICKED(IDC_SHUTTLE_PICKPLACE, OnShuttlePickplace)
	ON_BN_CLICKED(IDC_INPUT_MOVE, OnInputMove)
	ON_BN_CLICKED(IDC_OUTPUT_MOVE, OnOutputMove)
	ON_BN_CLICKED(IDC_F_ARM_VACC, OnFArmVacc)
	ON_EN_CHANGE(IDC_E_INPUT_POS, OnChangeEInputPos)
	ON_EN_CHANGE(IDC_E_OUTPUT_POS, OnChangeEOutputPos)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgAlignmentCheck message handlers

BOOL CDlgAlignmentCheck::PreTranslateMessage(MSG* pMsg) 
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

BOOL CDlgAlignmentCheck::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m.Info.bSubDlgOpen = true;
	f.UpdateButtonState();

	// init button 
	m_btnOK.SetIcon(IDI_OK);
	m_btnOK.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnOK.SetFlat(FALSE);
	
	m_btnCancel.SetIcon(IDI_CANCEL);
	m_btnCancel.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnCancel.SetFlat(FALSE);

	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgAlignmentCheck::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	
	CDialog::OnTimer(nIDEvent);
}

void CDlgAlignmentCheck::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);
}

void CDlgAlignmentCheck::OnOK() 
{
	m.Info.bSubDlgOpen = false;
	f.UpdateButtonState();
	
	CDialog::OnOK();
}

void CDlgAlignmentCheck::OnCancel() 
{
	m.Info.bSubDlgOpen = false;
	f.UpdateButtonState();
	
	CDialog::OnCancel();
}
UINT CDlgAlignmentCheck::AlignmnetCheckOutputStackThread(LPVOID p)
{
	CDlgAlignmentCheck *pt = (CDlgAlignmentCheck *)p;

	//
	long m_iRunError = enCodeRunOK;

	// Arm Z Up
	m_iRunError = f.Motor.ManualMotorRun( 
		&m.m_Motor.ArmZ, ( _InitialZHome * m.m_Ratio.Z_GearRation ), true, 
		m.TimerSetting.iMotorRunTimeout );		

	// 
	if( m_iRunError != enCodeRunOK )
	{
		pt->LockUI( true );
		return 0;
	}

	// Arm XY 
	m_iRunError	= f.Motor.ManualMotorRunLine(
		&m.m_Motor.ArmX, pt->px.x + ( m.m_Offset.Output1.x * m.m_Ratio.X_GearRation ),
		&m.m_Motor.ArmY, pt->px.y + ( m.m_Offset.Output1.y * m.m_Ratio.Y_GearRation ),
		true, m.TimerSetting.iMotorRunlineTimeout );

	//
	if( m_iRunError != enCodeRunOK )
	{
		pt->LockUI( true );
		return 0;
	}

	// Arm Z Down
	m_iRunError = f.Motor.ManualMotorRun(&m.m_Motor.ArmZ, 
		( m.m_Align.Input.z + ( m.m_Offset.Output1.z * m.m_Ratio.Z_GearRation )), false, 
		m.TimerSetting.iMotorRunTimeout );

	//
	if( m_iRunError != enCodeRunOK )
	{
		pt->LockUI( true );
		return 0;
	}

	pt->LockUI( true );

	AfxEndThread(0);
	return 0;
}

UINT CDlgAlignmentCheck::AlignmnetCheckInputStackThread(LPVOID p)
{
	CDlgAlignmentCheck *pt = (CDlgAlignmentCheck *)p;

	//
	long m_iRunError = enCodeRunOK;

	// Arm Z Up
	m_iRunError = f.Motor.ManualMotorRun( 
		&m.m_Motor.ArmZ, ( _InitialZHome * m.m_Ratio.Z_GearRation ), true, 
		m.TimerSetting.iMotorRunTimeout );		

	// 
	if( m_iRunError != enCodeRunOK )
	{
		pt->LockUI( true );
		return 0;
	}

	// Arm XY 
	m_iRunError	= f.Motor.ManualMotorRunLine(
		&m.m_Motor.ArmX, pt->px.x + ( m.m_Offset.Input.x * m.m_Ratio.X_GearRation ),
		&m.m_Motor.ArmY, pt->px.y + ( m.m_Offset.Input.y * m.m_Ratio.Y_GearRation ),
		true, m.TimerSetting.iMotorRunlineTimeout );

	//
	if( m_iRunError != enCodeRunOK )
	{
		pt->LockUI( true );
		return 0;
	}

	// Arm Z Down
	m_iRunError = f.Motor.ManualMotorRun(&m.m_Motor.ArmZ, 
		( m.m_Align.Input.z + ( m.m_Offset.Input.z * m.m_Ratio.Z_GearRation )), false, 
		m.TimerSetting.iMotorRunTimeout );

	//
	if( m_iRunError != enCodeRunOK )
	{
		pt->LockUI( true );
		return 0;
	}

	pt->LockUI( true );

	AfxEndThread(0);
	return 0;
}
UINT CDlgAlignmentCheck::AlignmnetCheckShuttleThread(LPVOID p)
{
	CDlgAlignmentCheck *pt = (CDlgAlignmentCheck *)p;

	//
	long m_iRunError = enCodeRunOK;

	// Arm Z Up
	m_iRunError = f.Motor.ManualMotorRun( 
		&m.m_Motor.ArmZ, ( _InitialZHome * m.m_Ratio.Z_GearRation ), true, 
		m.TimerSetting.iMotorRunTimeout );		

	// 
	if( m_iRunError != enCodeRunOK )
	{
		pt->LockUI( true );
		return 0;
	}

	double m_dTestPos = pt->m_TestSiteArmHomePos;
	// Test Site Up
	m_iRunError = f.Motor.ManualMotorRun(&m.m_Motor.Inserter, 
		m_dTestPos, false, m.TimerSetting.iMotorRunTimeout );

	// 
	if( m_iRunError != enCodeRunOK )
	{
		pt->LockUI( true );
		return 0;
	}

	if( pt->m_ShuttlePos == 0 )
	{
		f.ShuttleMoveHome();
	}
	else if( pt->m_ShuttlePos == 1 )
	{
		f.ShuttleMovePickPlace();
	}
	else
		; // Nerver be here

	pt->LockUI( true );

	AfxEndThread(0);
	return 0;
}
UINT CDlgAlignmentCheck::AlignmnetCheckTSThread(LPVOID p)
{
	CDlgAlignmentCheck *pt = (CDlgAlignmentCheck *)p;

	//
	long m_iRunError = enCodeRunOK;
	double m_dTestPos = pt->m_TestSiteArmPos;

	m_iRunError = f.Motor.ManualMotorRun(&m.m_Motor.Inserter, 
		m_dTestPos, false, m.TimerSetting.iMotorRunTimeout );
		
	//
	pt->LockUI( true );

	AfxEndThread(0);
	return 0;
}
UINT CDlgAlignmentCheck::AlignmnetCheckThread(LPVOID p)
{
	CDlgAlignmentCheck *pt = (CDlgAlignmentCheck *)p;

	double m_dArmX = 0.0;
	double m_dArmY = 0.0;
	double m_dArmZ = 0.0;

	m_dArmX = pt->m_ArmXPos;
	m_dArmY = pt->m_ArmYPos;
	m_dArmZ = pt->m_ArmZPos;

	//
	long m_iRunError = enCodeRunOK;

	// Arm Z Up
	m_iRunError = f.Motor.ManualMotorRun( 
		&m.m_Motor.ArmZ, ( _InitialZHome * m.m_Ratio.Z_GearRation ), true, 
		m.TimerSetting.iMotorRunTimeout );		

	// 
	if( m_iRunError != enCodeRunOK )
	{
		pt->LockUI( true );
		return 0;
	}

	// Arm XY Run Line
	m_iRunError = f.Motor.ManualMotorRunLine(	
					&m.m_Motor.ArmX, m_dArmX, 
					&m.m_Motor.ArmY, m_dArmY,
					true, m.TimerSetting.iMotorRunlineTimeout );

	//
	if( m_iRunError != enCodeRunOK )
	{
		pt->LockUI( true );
		return 0;
	}

	// Arm Z Down
	m_iRunError = f.Motor.ManualMotorRun( 
		&m.m_Motor.ArmZ, m_dArmZ, true, 
		m.TimerSetting.iMotorRunTimeout );
	
	//
	if( m_iRunError != enCodeRunOK )
	{
		pt->LockUI( true );
		return 0;
	}

	pt->LockUI( true );
	AfxEndThread(0);
	return 0;
}
void CDlgAlignmentCheck::LockUI(bool bEnable)
{
	if( bEnable )
	{
		BOOL m_bEnable = TRUE;
		m_btnMoveTSPlace.EnableWindow( m_bEnable );
		m_btnMoveTSPick.EnableWindow( m_bEnable );
		m_btnMoveTSContact.EnableWindow( m_bEnable );
		m_btnMoveHome.EnableWindow( m_bEnable );
		m_btnMoveShuttle.EnableWindow( m_bEnable );
		m_btnMoveOutput.EnableWindow( m_bEnable );
		m_btnMoveInput.EnableWindow( m_bEnable );
		m_btnMoveOutputPos.EnableWindow( m_bEnable );
		m_btnMoveInputPos.EnableWindow( m_bEnable );
		m_btnMoveShuttlePP.EnableWindow( m_bEnable );
		m_btnMoveShuttleHome.EnableWindow( m_bEnable );
	}
	else
	{
		BOOL m_bEnable = FALSE;
		m_btnMoveTSPlace.EnableWindow( m_bEnable );
		m_btnMoveTSPick.EnableWindow( m_bEnable );
		m_btnMoveTSContact.EnableWindow( m_bEnable );
		m_btnMoveHome.EnableWindow( m_bEnable );
		m_btnMoveShuttle.EnableWindow( m_bEnable );
		m_btnMoveOutput.EnableWindow( m_bEnable );
		m_btnMoveInput.EnableWindow( m_bEnable );
		m_btnMoveOutputPos.EnableWindow( m_bEnable );
		m_btnMoveInputPos.EnableWindow( m_bEnable );
		m_btnMoveShuttlePP.EnableWindow( m_bEnable );
		m_btnMoveShuttleHome.EnableWindow( m_bEnable );
	}
}
void CDlgAlignmentCheck::OnMMoveInput() 
{
	m_ArmXPos = m.m_Align.Input.x;
	m_ArmYPos = m.m_Align.Input.y;
	m_ArmZPos = m.m_Align.Input.z;

	LockUI( false );
	AfxBeginThread(AlignmnetCheckThread, this);
}

void CDlgAlignmentCheck::OnMMoveOutput() 
{
	m_ArmXPos = m.m_Align.Output1.x;
	m_ArmYPos = m.m_Align.Output1.y;
	m_ArmZPos = m.m_Align.Output1.z;

	LockUI( false );
	AfxBeginThread(AlignmnetCheckThread, this);	
}

void CDlgAlignmentCheck::OnMMoveShuttle() 
{
	m_ArmXPos = m.m_Align.Shuttle.x;
	m_ArmYPos = m.m_Align.Shuttle.y;
	m_ArmZPos = m.m_Align.Shuttle.z;

	LockUI( false );
	AfxBeginThread(AlignmnetCheckThread, this);		
}

void CDlgAlignmentCheck::OnMMoveHome() 
{
	m_ArmXPos = m.m_Align.StandyBy.x;
	m_ArmYPos = m.m_Align.StandyBy.y;
	m_ArmZPos = m.m_Align.StandyBy.z;

	LockUI( false );
	AfxBeginThread(AlignmnetCheckThread, this);		
}

void CDlgAlignmentCheck::OnMTestSitePick() 
{
	m_TestSiteArmPos = m.m_Align.TestSite.pick;
	
	LockUI( false );
	
	AfxBeginThread(AlignmnetCheckTSThread, this);		
}

void CDlgAlignmentCheck::OnMTestSitePlace() 
{
	m_TestSiteArmPos = m.m_Align.TestSite.place;

	LockUI( false );
	
	AfxBeginThread(AlignmnetCheckTSThread, this);
}

void CDlgAlignmentCheck::OnMTestSiteContact() 
{
	m_TestSiteArmPos = m.m_Align.TestSite.contact;

	LockUI( false );

	AfxBeginThread(AlignmnetCheckTSThread, this);
}

void CDlgAlignmentCheck::OnShuttleHome() 
{
	m_ShuttlePos = 0; // home
	m_TestSiteArmHomePos = m.m_Align.TestSite.home;

	LockUI( false );
	AfxBeginThread(AlignmnetCheckShuttleThread, this);		
}

void CDlgAlignmentCheck::OnShuttlePickplace() 
{
	m_ShuttlePos = 1; // pick/place
	m_TestSiteArmHomePos = m.m_Align.TestSite.home;

	LockUI( false );
	AfxBeginThread(AlignmnetCheckShuttleThread, this);
}

void CDlgAlignmentCheck::OnInputMove() 
{
	UpdateData();
	int m_nSize = m.TraySpec.Column * m.TraySpec.Row;
	if( m_iInputPos > m_nSize || m_iInputPos < 0 )
	{
		CString csMsg = _T("");
		csMsg.Format("Out of range [%d~%d]", 0, m_nSize );
		AfxMessageBox( csMsg );
		return;
	}
	px = theApp.m_InputTray.GetCoordinate( m_iInputPos );	
	LockUI( false );
	AfxBeginThread(AlignmnetCheckInputStackThread, this);
}

void CDlgAlignmentCheck::OnOutputMove() 
{
	UpdateData();
	int m_nSize = m.TraySpec.Column * m.TraySpec.Row;
	if( m_iInputPos > m_nSize || m_iInputPos < 0 )
	{
		CString csMsg = _T("");
		csMsg.Format("Out of range [%d~%d]", 0, m_nSize );
		AfxMessageBox( csMsg );
		return;
	}
	px = theApp.m_OutputTray.GetCoordinate( m_iInputPos );	
	LockUI( false );
	AfxBeginThread(AlignmnetCheckOutputStackThread, this);
}

void CDlgAlignmentCheck::OnFArmVacc() 
{
	if( theApp.m_tArm.ManualVacc( &m.OutSet.ArmVacc, &m.InStatus.ArmZVaccSensor, m.Timer.m_dPickPick ) )
		AfxMessageBox("Pick OK");
	else
		AfxMessageBox("Pick Fail");
}

void CDlgAlignmentCheck::OnChangeEInputPos() 
{
	
}

void CDlgAlignmentCheck::OnChangeEOutputPos() 
{
	
}
