// PageInitial.cpp : implementation file
//

#include "stdafx.h"
#include "Deer.h"
#include "DeerDlg.h"
#include "PageInitial.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPageInitial dialog


CPageInitial::CPageInitial(CWnd* pParent /*=NULL*/)
	: CDialog(CPageInitial::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPageInitial)
	//}}AFX_DATA_INIT

	csLmt = "";
}


void CPageInitial::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPageInitial)
	DDX_Control(pDX, IDC_M_INSERTER,		m_wndInserter);
	DDX_Control(pDX, IDC_M_ARM_Z,			m_wndArmZ);
	DDX_Control(pDX, IDC_M_ARM_Y,			m_wndArmY);
	DDX_Control(pDX, IDC_M_ARM_X,			m_wndArmX);
	DDX_Control(pDX, IDC_ARM_X_MOTOR,		m_wndArmXMotor);
	DDX_Control(pDX, IDC_ARM_Y_MOTOR,		m_wndArmYMotor);
	DDX_Control(pDX, IDC_ARM_Z_MOTOR,		m_wndArmZMotor);
	DDX_Control(pDX, IDC_TESTSITE_MOTOR,	m_wndTestSiteMotor);

	DDX_Control(pDX, IDC_LED_INSERTER,		m_ledInserter);
	DDX_Control(pDX, IDC_LED_ARM_Z,			m_ledArmZ);
	DDX_Control(pDX, IDC_LED_ARM_Y,			m_ledArmY);
	DDX_Control(pDX, IDC_LED_ARM_X,			m_ledArmX);

	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPageInitial, CDialog)
	//{{AFX_MSG_MAP(CPageInitial)
	ON_WM_TIMER()
	ON_WM_CLOSE()
	ON_WM_DESTROY()
	ON_WM_SHOWWINDOW()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPageInitial message handlers

BOOL CPageInitial::OnInitDialog() 
{
	CDialog::OnInitDialog();

	// Init UI Led icon
	InitLed();

	// Note: We need set the Text by myself
	SetWindowText("Initial");

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPageInitial::InitLed()
{
	// Motor
	m_ledArmX.SetLed(CLed::LED_COLOR_GREEN, CLed::LED_OFF);
	m_ledInserter.SetLed(CLed::LED_COLOR_GREEN, CLed::LED_OFF);
	m_ledArmZ.SetLed(CLed::LED_COLOR_GREEN, CLed::LED_OFF);
	m_ledArmY.SetLed(CLed::LED_COLOR_GREEN, CLed::LED_OFF);	
}

void CPageInitial::SetTimeClock()
{
//	SetTimer( ID_TIME_SET_INITIAL_STATUS, 500, NULL);
}

void CPageInitial::UpdateInitialStatus()
{
	// Updata Motor RCount Status
	f.Motor.GetMotorStatus( &m.m_Motor.ArmX );
	f.Motor.GetMotorStatus( &m.m_Motor.ArmY );
	f.Motor.GetMotorStatus( &m.m_Motor.ArmZ );
	f.Motor.GetMotorStatus( &m.m_Motor.Inserter );
	
	m.MotorStatus.ArmXRCount = m.m_Motor.ArmX.RCount;	
	m.MotorStatus.ArmYRCount = m.m_Motor.ArmY.RCount;	
	m.MotorStatus.ArmZRCount = m.m_Motor.ArmZ.RCount;	
	m.MotorStatus.InserterRCount = m.m_Motor.Inserter.RCount;
	
	CString csR;

	csR.Format("(%d)", m.MotorStatus.ArmXRCount );
	m_wndArmX.SetWindowText( m.MotorStatus.ArmX + csR );

	csR.Format("(%d)", m.MotorStatus.ArmYRCount );
	m_wndArmY.SetWindowText( m.MotorStatus.ArmY + csR );

	csR.Format("(%d)", m.MotorStatus.ArmZRCount );
	m_wndArmZ.SetWindowText( m.MotorStatus.ArmZ + csR );

	csR.Format("(%d)", m.MotorStatus.InserterRCount );
	m_wndInserter.SetWindowText( m.MotorStatus.Inserter + csR );

	// Updata Motor Status 
	// if Initial Pass. Let green light on.
	m_ledInserter = m.MotorStatus.InserterInitialed == 0 ? false : true;
	m_ledArmZ =		m.MotorStatus.ArmZInitialed == 0 ? false : true;
	m_ledArmY =		m.MotorStatus.ArmYInitialed == 0 ? false : true;
	m_ledArmX =		m.MotorStatus.ArmXInitialed == 0 ? false : true;	

	if(	 
		 m.MotorStatus.ArmXInitialed == true && 
		 m.MotorStatus.ArmYInitialed == true && 
		 m.MotorStatus.ArmZInitialed == true && 		 
		 m.MotorStatus.InserterInitialed == true && 
		 m.MotorStatus.TesterInitialed == true && 
		 m.MotorStatus.InspectInitialed == true &&
		 m.MotorStatus.ManualCtrlInitialed == true )
	{		

		// Initial Complete and Success.
		// We get to something.
		m.Info.iStatus = theApp.enReady;
		f.UpdateButtonState();
		// We set handler status.

		CDeerDlg *p = (CDeerDlg *) theApp.m_pMainWnd;
#ifdef _Demo
//		m.Info.user = enLevelSuperUser;
//		m.Info.user = enLevelUser;
#else
#endif
		p->SetUserPage(m.Info.user);			
		// We set level to default (User)
		
		KillTimer(ID_TIME_SET_INITIAL_STATUS);

		f.RemoteSetStateInitialDone();
		// Remote Protocol
	}
	// Check Each Motor Initial complete or not.
	// If Initial success we set it to User page.
}

void CPageInitial::OnTimer(UINT nIDEvent) 
{
	switch(nIDEvent)
	{
	case ID_TIME_SET_INITIAL_STATUS:
		UpdateInitialStatus();
		break;
	default:
		break;
	}
	
	CDialog::OnTimer(nIDEvent);
}

void CPageInitial::OnClose() 
{
	KillTimer(ID_TIME_SET_INITIAL_STATUS);
	
	CDialog::OnClose();
}

void CPageInitial::OnDestroy() 
{
	CDialog::OnDestroy();
	
	KillTimer(ID_TIME_SET_INITIAL_STATUS);
	
}

BOOL CPageInitial::PreTranslateMessage(MSG* pMsg) 
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

void CPageInitial::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);
	
	if (bShow)
		SetTimer( ID_TIME_SET_INITIAL_STATUS, 100, NULL);
	else 
		KillTimer( ID_TIME_SET_INITIAL_STATUS );
}
