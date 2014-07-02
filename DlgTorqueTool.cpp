// DlgTorqueTool.cpp : implementation file
//

#include "stdafx.h"
#include "deer.h"
#include "DlgTorqueTool.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgTorqueTool dialog


CDlgTorqueTool::CDlgTorqueTool(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgTorqueTool::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgTorqueTool)
	m_dSetA = 0.0;
	m_dSetB = 0.0;
	m_dSetTorque = 0.0;
	//}}AFX_DATA_INIT
}


void CDlgTorqueTool::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgTorqueTool)
	DDX_Control(pDX, IDC_SET,		m_btnSet);
	DDX_Control(pDX, IDC_S_RESULT,	m_wndResult);
	DDX_Control(pDX, IDCANCEL,		m_btnCancel);
	DDX_Control(pDX, IDOK,			m_btnOK);
	DDX_Text(pDX, IDC_S_A,			m_dSetA);
	DDX_Text(pDX, IDC_S_B,			m_dSetB);
	DDX_Text(pDX, IDC_S_TORQUE,		m_dSetTorque);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgTorqueTool, CDialog)
	//{{AFX_MSG_MAP(CDlgTorqueTool)
	ON_BN_CLICKED(IDC_SET, OnSet)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgTorqueTool message handlers

void CDlgTorqueTool::OnOK() 
{
	m.Info.bSubDlgOpen = false;
	f.UpdateButtonState();
	
	CDialog::OnOK();
}

void CDlgTorqueTool::OnCancel() 
{
	m.Info.bSubDlgOpen = false;
	f.UpdateButtonState();
	
	CDialog::OnCancel();
}

BOOL CDlgTorqueTool::PreTranslateMessage(MSG* pMsg) 
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

BOOL CDlgTorqueTool::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m.Info.bSubDlgOpen = true;
	f.UpdateButtonState();

	// init button 
	m_btnOK.SetIcon(IDI_SAVE);
	m_btnOK.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnOK.SetFlat(FALSE);
	
	m_btnCancel.SetIcon(IDI_CANCEL);
	m_btnCancel.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnCancel.SetFlat(FALSE);

	m_btnSet.SetIcon(IDI_DEBUG);
	m_btnSet.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnSet.SetFlat(FALSE);
	
	//
	InitValue();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
void CDlgTorqueTool::InitValue() 
{
	m_dSetA = m.m_TorqueToolSet.daValue;
	m_dSetB = m.m_TorqueToolSet.dbValue;
	UpdateData(FALSE);	
}
void CDlgTorqueTool::OnSet() 
{
	UpdateData();	

	double m_dTorque = ( m_dSetTorque - m_dSetB ) / m_dSetA;
	m_dTorque = m_dTorque * 20;

	CString m_csResult = _T("");
	m_csResult.Format("%5.2f, Torque: %5.2f, a: %5.2f, b: %5.2f",
		m_dTorque, m_dSetTorque, m_dSetA, m_dSetB );
	m_wndResult.SetWindowText( m_csResult );
#ifdef _Demo
#else
	theApp.m_tIORemote.SetTorqueValue( m_dTorque );
#endif

	m.m_TorqueToolSet.daValue = m_dSetA;
	m.m_TorqueToolSet.dbValue = m_dSetB;
	f.SaveTorqueToolSet();
}
