// DlgMotorSimpleStatus.cpp : implementation file
//

#include "stdafx.h"
#include "deer.h"
#include "DlgMotorSimpleStatus.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgMotorSimpleStatus dialog


CDlgMotorSimpleStatus::CDlgMotorSimpleStatus(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgMotorSimpleStatus::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgMotorSimpleStatus)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgMotorSimpleStatus::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgMotorSimpleStatus)
	DDX_Control(pDX, IDC_LED_TS_TLC,		m_ledTSTLC);
	DDX_Control(pDX, IDC_E_ARMZ_RCOUNT,		m_wndArmZRCount);
	DDX_Control(pDX, IDC_E_ARMZ_PLMT,		m_wndArmZpLmt);
	DDX_Control(pDX, IDC_E_ARMZ_NLMT,		m_wndArmZnLmt);
	DDX_Control(pDX, IDC_E_ARMZ_LCOUNT,		m_wndArmZLCount);
	DDX_Control(pDX, IDC_E_ARMX_RCOUNT,		m_wndArmXRCount);
	DDX_Control(pDX, IDC_E_ARMX_PLMT,		m_wndArmXpLmt);
	DDX_Control(pDX, IDC_E_ARMX_NLMT,		m_wndArmXnLmt);
	DDX_Control(pDX, IDC_E_ARMX_LCOUNT,		m_wndArmXLCount);
	DDX_Control(pDX, IDC_E_TS_RCOUNT,		m_wndTSRCount);
	DDX_Control(pDX, IDC_E_TS_PLMT,			m_wndTSpLmt);
	DDX_Control(pDX, IDC_E_TS_NLMT,			m_wndTSnLmt);
	DDX_Control(pDX, IDC_E_TS_LCOUNT,		m_wndTSLCount);
	DDX_Control(pDX, IDC_E_ARMY_RCOUNT,		m_wndArmYRCount);
	DDX_Control(pDX, IDC_E_ARMY_PLMT,		m_wndArmYpLmt);
	DDX_Control(pDX, IDC_E_ARMY_NLMT,		m_wndArmYnLmt);
	DDX_Control(pDX, IDC_E_ARMY_LCOUNT,		m_wndArmYLCount);
	DDX_Control(pDX, IDOK,					m_btnOK);
	DDX_Control(pDX, IDCANCEL,				m_btnCancel);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgMotorSimpleStatus, CDialog)
	//{{AFX_MSG_MAP(CDlgMotorSimpleStatus)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgMotorSimpleStatus message handlers

void CDlgMotorSimpleStatus::OnOK() 
{
	
	CDialog::OnOK();
}

void CDlgMotorSimpleStatus::OnCancel() 
{
	
	CDialog::OnCancel();
}

BOOL CDlgMotorSimpleStatus::PreTranslateMessage(MSG* pMsg) 
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

BOOL CDlgMotorSimpleStatus::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// init button 
	m_btnOK.SetIcon(IDI_OK);;
	m_btnOK.SetAlign(CButtonST::ST_ALIGN_VERT);;
	m_btnOK.SetFlat(FALSE);
	
	m_btnCancel.SetIcon(IDI_CANCEL);
	m_btnCancel.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnCancel.SetFlat(FALSE);
	
	//
	InitLed();

	//
	SelectMotor();

	//
	SetTimer(ID_TIME_GET_STATUS, 150, NULL);
	
	//
	CenterWindow();

	//
	f.ChangeLanguage(GetSafeHwnd());

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
void CDlgMotorSimpleStatus::InitLed()
{
	m_ledTSTLC.SetLed(CLed::LED_COLOR_RED, CLed::LED_OFF);
}
void CDlgMotorSimpleStatus::SelectMotor()
{
	// Board 0
	InserterMotor	 = &m.m_Motor.Inserter;
	ArmYMotor		 = &m.m_Motor.ArmY;	
	ArmXMotor		 = &m.m_Motor.ArmX;	
	ArmZMotor		 = &m.m_Motor.ArmZ;	
}

void CDlgMotorSimpleStatus::MototStatusQuery()
{
	// Get Motor Status
	f.Motor.GetMotorStatus(InserterMotor);
	f.Motor.GetMotorStatus(ArmYMotor);
	f.Motor.GetMotorStatus(ArmXMotor);
	f.Motor.GetMotorStatus(ArmZMotor);

	// Arm X
	CString csArmXLCount = _T(""), csArmXnLmt = _T(""), csArmXpLmt = _T(""), csArmXRCount = _T("");
	csArmXLCount.Format("%d", ArmXMotor->LCount );
	csArmXRCount.Format("%d", ArmXMotor->RCount );
	csArmXnLmt.Format("%d", m.m_LmtCounter.iXnLmtCounter );
	csArmXpLmt.Format("%d", m.m_LmtCounter.iXpLmtCounter );
		
	m_wndArmXLCount.SetWindowText( csArmXLCount );
	m_wndArmXnLmt.SetWindowText( csArmXnLmt );
	m_wndArmXpLmt.SetWindowText( csArmXpLmt );
	m_wndArmXRCount.SetWindowText( csArmXRCount );

	// Arm Y
	CString csArmYLCount = _T(""), csArmYnLmt = _T(""), csArmYpLmt = _T(""), csArmYRCount = _T("");
	csArmYLCount.Format("%d",	ArmYMotor->LCount );
	csArmYRCount.Format("%d",	ArmYMotor->RCount );
	csArmYnLmt.Format("%d",		m.m_LmtCounter.iYnLmtCounter );
	csArmYpLmt.Format("%d",		m.m_LmtCounter.iYpLmtCounter );	// Initial Direction

	m_wndArmYLCount.SetWindowText(csArmYLCount);
	m_wndArmYnLmt.SetWindowText(csArmYnLmt);
	m_wndArmYpLmt.SetWindowText(csArmYpLmt);
	m_wndArmYRCount.SetWindowText(csArmYRCount);

	// Arm Z
	CString csArmZLCount = _T(""), csArmZnLmt = _T(""), csArmZpLmt = _T(""), csArmZRCount = _T("");
	csArmZLCount.Format("%d", ArmZMotor->LCount );
	csArmZRCount.Format("%d", ArmZMotor->RCount );
	csArmZnLmt.Format("%d", m.m_LmtCounter.iZnLmtCounter );
	csArmZpLmt.Format("%d", m.m_LmtCounter.iZpLmtCounter );
		
	m_wndArmZLCount.SetWindowText( csArmZLCount );
	m_wndArmZnLmt.SetWindowText( csArmZnLmt );
	m_wndArmZpLmt.SetWindowText( csArmZpLmt );
	m_wndArmZRCount.SetWindowText( csArmZRCount );

	// TS
	CString csTSLCount = _T(""), csTSnLmt = _T(""), csTSpLmt = _T(""), csTSRCount = _T("");
	csTSLCount.Format("%d",		InserterMotor->LCount );
	csTSRCount.Format("%d",		InserterMotor->RCount );
	csTSnLmt.Format("%d",		m.m_LmtCounter.iTSnLmtCounter );	// Initial Direction
	csTSpLmt.Format("%d",		m.m_LmtCounter.iTSpLmtCounter );

	m_wndTSLCount.SetWindowText( csTSLCount );
	m_wndTSnLmt.SetWindowText( csTSnLmt );
	m_wndTSpLmt.SetWindowText( csTSpLmt );
	m_wndTSRCount.SetWindowText( csTSRCount );

	m_ledTSTLC		= InserterMotor->TLC;
}

void CDlgMotorSimpleStatus::OnTimer(UINT nIDEvent) 
{
	switch(nIDEvent)
	{
	case ID_TIME_GET_STATUS:
		{
			MototStatusQuery();
		}
		break;
	default:
		break;
	}	
	CDialog::OnTimer(nIDEvent);
}
