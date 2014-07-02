// DlgMotorStatus.cpp : implementation file
//

#include "stdafx.h"
#include "deer.h"
#include "DlgMotorStatus.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgMotorStatus dialog


CDlgMotorStatus::CDlgMotorStatus(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgMotorStatus::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgMotorStatus)
	m_csArmX = _T("");
	m_csArmY = _T("");
	m_csArmZ = _T("");
	m_csInserter = _T("");
	//
	m_csArmX2 = _T("");
	m_csArmY2 = _T("");
	m_csArmZ2 = _T("");
	m_csInserter2 = _T("");
	//}}AFX_DATA_INIT
}


void CDlgMotorStatus::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgMotorStatus)
	DDX_Control(pDX, IDCANCEL,					m_btnCancel);
	DDX_Control(pDX, IDOK,						m_btnOK);
	DDX_Text(pDX, IDC_STATUS_ARM_X,				m_csArmX);
	DDX_Text(pDX, IDC_STATUS_ARM_Y,				m_csArmY);
	DDX_Text(pDX, IDC_STATUS_ARM_Z,				m_csArmZ);
	DDX_Text(pDX, IDC_STATUS_INSERTER,			m_csInserter);
	DDX_Text(pDX, IDC_STATUS_ARM_X2,			m_csArmX2);				  
	DDX_Text(pDX, IDC_STATUS_ARM_Y2,			m_csArmY2);
	DDX_Text(pDX, IDC_STATUS_ARM_Z2,			m_csArmZ2);
	DDX_Text(pDX, IDC_STATUS_INSERTER2,			m_csInserter2);

	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgMotorStatus, CDialog)
	//{{AFX_MSG_MAP(CDlgMotorStatus)
	ON_WM_TIMER()
	ON_WM_DESTROY()
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgMotorStatus message handlers

void CDlgMotorStatus::OnOK() 
{
	m.Info.bSubDlgOpen = false;
	f.UpdateButtonState();

	KillTimer(ID_TIME_GET_STATUS);
	
	CDialog::OnOK();
}

void CDlgMotorStatus::OnCancel() 
{
	m.Info.bSubDlgOpen = false;
	f.UpdateButtonState();

	KillTimer(ID_TIME_GET_STATUS);

	CDialog::OnCancel();
}

BOOL CDlgMotorStatus::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// init button 
	m_btnOK.SetIcon(IDI_OK);;
	m_btnOK.SetAlign(CButtonST::ST_ALIGN_VERT);;
	m_btnOK.SetFlat(FALSE);
	
	m_btnCancel.SetIcon(IDI_CANCEL);
	m_btnCancel.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnCancel.SetFlat(FALSE);

	SelectMotor();
	// We need Selet Motor first then SetTimer

	SetTimer(ID_TIME_GET_STATUS, 350, NULL);

	m.Info.bSubDlgOpen = true;
	f.UpdateButtonState();

	f.ChangeLanguage(GetSafeHwnd());
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgMotorStatus::OnTimer(UINT nIDEvent) 
{
	switch(nIDEvent)
	{
	case ID_TIME_GET_STATUS:
		{
			UpdataMotorStatus();
			UpdataMotorSpeedStatus();
		}
		break;
	default:
		break;
	}	
	CDialog::OnTimer(nIDEvent);
}

void CDlgMotorStatus::SelectMotor() 
{	
	// Board 0
	InserterMotor	= &m.m_Motor.Inserter;
	ArmXMotor		 = &m.m_Motor.ArmX;
	ArmYMotor		 = &m.m_Motor.ArmY;	
	ArmZMotor		= &m.m_Motor.ArmZ;	
}


void CDlgMotorStatus::UpdataMotorSpeedStatus() 
{
	//
	CString	csArmX2, csArmY2, csArmZ2 ,csInserter2, csShuttle2;

	csArmX2.Format(" Search: %d, Dift: %d, Speed: %d, Acc: %d, Jerk: %d, Max: %d, Start: %d", 
		ArmXMotor->SearchSpeed, ArmXMotor->DrifSpeed, ArmXMotor->Speed, ArmXMotor->Accelerate, ArmXMotor->Jerk, ArmXMotor->MaxSpeed, ArmXMotor->Start );
	// Arm X 

	csArmY2.Format(" Search: %d, Dift: %d, Speed: %d, Acc: %d, Jerk: %d, Max: %d, Start: %d", 
		ArmYMotor->SearchSpeed, ArmYMotor->DrifSpeed, ArmYMotor->Speed, ArmYMotor->Accelerate, ArmYMotor->Jerk, ArmYMotor->MaxSpeed, ArmYMotor->Start );
	// Arm Y

	csArmZ2.Format(" Search: %d, Dift: %d, Speed: %d, Acc: %d, Jerk: %d, Max: %d, Start: %d", 
		ArmZMotor->SearchSpeed, ArmZMotor->DrifSpeed, ArmZMotor->Speed, ArmZMotor->Accelerate, ArmZMotor->Jerk, ArmZMotor->MaxSpeed, ArmZMotor->Start );
	// Arm Z

	csInserter2.Format(" Search: %d, Dift: %d, Speed: %d, Acc: %d, Jerk: %d, Max: %d, Start: %d", 
		InserterMotor->SearchSpeed, InserterMotor->DrifSpeed, InserterMotor->Speed, InserterMotor->Accelerate, InserterMotor->Jerk, InserterMotor->MaxSpeed, InserterMotor->Start );
	// Test Site

	m_csArmZ2 = csArmZ2;
	m_csInserter2 = csInserter2;
	m_csArmX2 = csArmX2;
	m_csArmY2 = csArmY2;

	UpdateData(FALSE);

}
void CDlgMotorStatus::UpdataMotorStatus() 
{
	f.Motor.GetMotorStatus(InserterMotor);
	f.Motor.GetMotorStatus(ArmXMotor);
	f.Motor.GetMotorStatus(ArmYMotor);
	f.Motor.GetMotorStatus(ArmZMotor);

	CString csArmX, csArmY,	csArmZ,	csInserter, csShuttle;

	csArmX.Format("LCount = %d, RCount = %d, Inpos = %d, nLMT = %d, pLMT = %d, TLC = %d, ZeroSpeed = %d", 
		ArmXMotor->LCount,
		ArmXMotor->RCount,
		ArmXMotor->InPos,
		ArmXMotor->nLMT,
		ArmXMotor->pLMT,
		ArmXMotor->TLC,
		ArmXMotor->ZeroSpeed
		);
	// Arm X

	csArmY.Format("LCount = %d, RCount = %d, Inpos = %d, nLMT = %d, pLMT = %d, TLC = %d, ZeroSpeed = %d",
		ArmYMotor->LCount,
		ArmYMotor->RCount,
		ArmYMotor->InPos,
		ArmYMotor->nLMT,
		ArmYMotor->pLMT,
		ArmYMotor->TLC,
		ArmYMotor->ZeroSpeed
		);
	// Arm Y

	csArmZ.Format("LCount = %d, RCount = %d, Inpos = %d, nLMT = %d, pLMT = %d, TLC = %d, ZeroSpeed = %d",
		ArmZMotor->LCount,
		ArmZMotor->RCount,
		ArmZMotor->InPos,
		ArmZMotor->nLMT,
		ArmZMotor->pLMT,
		ArmZMotor->TLC,
		ArmZMotor->ZeroSpeed
		);
	// Arm Z

	csInserter.Format("LCount = %d, RCount = %d, Inpos = %d, nLMT = %d, pLMT = %d, TLC = %d, ZeroSpeed = %d",
		InserterMotor->LCount,
		InserterMotor->RCount,
		InserterMotor->InPos,
		InserterMotor->nLMT,
		InserterMotor->pLMT,
		InserterMotor->TLC,
		InserterMotor->ZeroSpeed
		);
	// Inserter

	m_csArmX		= csArmX;
	m_csArmY		= csArmY;
	m_csArmZ		= csArmZ;
	m_csInserter	= csInserter;

	UpdateData(FALSE);
}

void CDlgMotorStatus::OnDestroy() 
{
	m.Info.bSubDlgOpen = false;
	f.UpdateButtonState();

	KillTimer(ID_TIME_GET_STATUS);

	CDialog::OnDestroy();
}

void CDlgMotorStatus::OnClose() 
{
	m.Info.bSubDlgOpen = false;
	f.UpdateButtonState();

	KillTimer(ID_TIME_GET_STATUS);
	
	CDialog::OnClose();
}

BOOL CDlgMotorStatus::PreTranslateMessage(MSG* pMsg) 
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
