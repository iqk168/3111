// DlgTorqueControl.cpp : implementation file
//

#include "stdafx.h"
#include "deer.h"
#include "DlgTorqueControl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgTorqueControl dialog


CDlgTorqueControl::CDlgTorqueControl(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgTorqueControl::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgTorqueControl)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	m_fChange = false;
}


void CDlgTorqueControl::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgTorqueControl)
	DDX_Control(pDX, IDC_POWER,		m_wndPowerValue);
	DDX_Control(pDX, IDCANCEL,		m_btnCancel);
	DDX_Control(pDX, IDOK,			m_btnOK);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgTorqueControl, CDialog)
	//{{AFX_MSG_MAP(CDlgTorqueControl)
	ON_EN_CHANGE(IDC_POWER, OnChangePower)
	ON_BN_CLICKED(IDC_SET, OnSet)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgTorqueControl message handlers

void CDlgTorqueControl::OnOK() 
{
	if( !SaveData() )
	{
		AfxMessageBox("Value is out of range.!");
		return;
	}

	CDialog::OnOK();
}

void CDlgTorqueControl::OnCancel() 
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

//	CDialog::OnCancel();
}

BOOL CDlgTorqueControl::PreTranslateMessage(MSG* pMsg) 
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
void CDlgTorqueControl::InitValue()
{
	CString csPowerValue = _T("");
	csPowerValue.Format("%d", m.m_ContactForce.lPower );

	m_wndPowerValue.SetWindowText( csPowerValue );
}
bool CDlgTorqueControl::SaveData()
{
	CString csPowerValue = _T("");
	m_wndPowerValue.GetWindowText( csPowerValue );	
	
	long lpower = atoi( csPowerValue );
	if( lpower > 20000000 || lpower < 0 )
		return false;

	m.m_ContactForce.lPower = lpower;

	f.SaveContactForce();

	return true;

}
BOOL CDlgTorqueControl::OnInitDialog() 
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
	
	//
	InitValue();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgTorqueControl::OnChangePower() 
{
	m_fChange = true;	
}

void CDlgTorqueControl::OnSet() 
{	
	CString csPowerValue = _T("");
	m_wndPowerValue.GetWindowText( csPowerValue );	
	
	double dPower = atof( csPowerValue );

	theApp.m_tIORemote.SetTorqueValue( dPower );
}
