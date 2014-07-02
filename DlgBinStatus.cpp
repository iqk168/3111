// DlgBinStatus.cpp : implementation file
//

#include "stdafx.h"
#include "deer.h"
#include "DlgBinStatus.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgBinStatus dialog


CDlgBinStatus::CDlgBinStatus(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgBinStatus::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgBinStatus)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgBinStatus::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgBinStatus)
	DDX_Control(pDX, IDC_E_TESTER_BIN,			m_wndTesterBin);
	DDX_Control(pDX, IDC_E_ARM_BIN,				m_wndArmBin);
	DDX_Control(pDX, IDCANCEL,					m_btnCancel);
	DDX_Control(pDX, IDOK,						m_btnOK);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgBinStatus, CDialog)
	//{{AFX_MSG_MAP(CDlgBinStatus)
	ON_WM_TIMER()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgBinStatus message handlers

BOOL CDlgBinStatus::PreTranslateMessage(MSG* pMsg) 
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

BOOL CDlgBinStatus::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// init button 
	m_btnOK.SetIcon(IDI_OK);;
	m_btnOK.SetAlign(CButtonST::ST_ALIGN_VERT);;
	m_btnOK.SetFlat(FALSE);
	
	m_btnCancel.SetIcon(IDI_CANCEL);
	m_btnCancel.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnCancel.SetFlat(FALSE);	

	SetTimer(ID_TIME_BIN_STATUS, 250 , NULL);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgBinStatus::OnTimer(UINT nIDEvent) 
{
	switch(nIDEvent)
	{
	case ID_TIME_BIN_STATUS:
		UpdateBinStatus();
		break;
	}		
	CDialog::OnTimer(nIDEvent);
}
void CDlgBinStatus::UpdateBinStatus() 
{
	// Arm
	CString csArmBin = _T("");
	csArmBin.Format("Code :[%s], Bookinh: %d", 
		theApp.m_tArm.ArmLog.csCode,
		theApp.m_tArm.ArmLog.iBooking );
	m_wndArmBin.SetWindowText( csArmBin );

	// Tester
	CString csTesterBin = _T("");
	csTesterBin.Format("Code :[%s], Bookinh: %d", 
		theApp.m_tTester.TesterLog.csCode,
		theApp.m_tTester.TesterLog.iBooking);
	m_wndTesterBin.SetWindowText( csTesterBin );
}
void CDlgBinStatus::OnOK() 
{
	
	CDialog::OnOK();
}

void CDlgBinStatus::OnCancel() 
{
	
	CDialog::OnCancel();
}

void CDlgBinStatus::OnDestroy() 
{
	KillTimer( ID_TIME_BIN_STATUS );

	CDialog::OnDestroy();	
}
