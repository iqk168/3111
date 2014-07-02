// DlgCustomMCFunction.cpp : implementation file
//

#include "stdafx.h"
#include "deer.h"
#include "DlgCustomMCFunction.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgCustomMCFunction dialog


CDlgCustomMCFunction::CDlgCustomMCFunction(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgCustomMCFunction::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgCustomMCFunction)
	m_bManualTorque = FALSE;
	m_bManualTemp = FALSE;
	m_bManualOffset = FALSE;
	m_bManualIFTesting = FALSE;
	m_bManualTsDirectContact = FALSE;
	m_bManualTestSieVacc = FALSE;
	//}}AFX_DATA_INIT

	m_MCFunction = m.m_MCFunction;
}


void CDlgCustomMCFunction::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgCustomMCFunction)
	DDX_Control(pDX, IDOK,						m_btnOK);
	DDX_Control(pDX, IDCANCEL,					m_btnCancel);
	DDX_Check(pDX, IDC_E_TORQUE,				m_bManualTorque);
	DDX_Check(pDX, IDC_E_TEMP,					m_bManualTemp);
	DDX_Check(pDX, IDC_E_OFFSET,				m_bManualOffset);
	DDX_Check(pDX, IDC_E_IF,					m_bManualIFTesting);
	DDX_Check(pDX, IDC_E_TEST_DIRECT_CONTACT,	m_bManualTsDirectContact);
	DDX_Check(pDX, IDC_E_TEST_SITE_VACC,		m_bManualTestSieVacc);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgCustomMCFunction, CDialog)
	//{{AFX_MSG_MAP(CDlgCustomMCFunction)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgCustomMCFunction message handlers

void CDlgCustomMCFunction::OnOK() 
{
	//
	SaveData();

	m.Info.bSubDlgOpen = false;
	f.UpdateButtonState();
	
	CDialog::OnOK();
}

void CDlgCustomMCFunction::OnCancel() 
{
	m.Info.bSubDlgOpen = false;
	f.UpdateButtonState();
	
	CDialog::OnCancel();
}

BOOL CDlgCustomMCFunction::PreTranslateMessage(MSG* pMsg) 
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

BOOL CDlgCustomMCFunction::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m.Info.bSubDlgOpen = true;
	f.UpdateButtonState();

	// init button 
	m_btnOK.SetIcon(IDI_SAVE);;
	m_btnOK.SetAlign(CButtonST::ST_ALIGN_VERT);;
	m_btnOK.SetFlat(FALSE);
	
	m_btnCancel.SetIcon(IDI_CANCEL);
	m_btnCancel.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnCancel.SetFlat(FALSE);	

	//
	InitOption();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
void CDlgCustomMCFunction::InitOption()
{
	m_bManualTorque				= m_MCFunction.m_bEnableTorqueControl;
	m_bManualTemp				= m_MCFunction.m_bEnableTemperatureControl;
	m_bManualIFTesting			= m_MCFunction.m_bEnableInterfaceTesting;
	m_bManualOffset				= m_MCFunction.m_bEnableOffsetControl;
	m_bManualTsDirectContact	= m_MCFunction.m_bEnableTestDirectContact;
	m_bManualTestSieVacc		= m_MCFunction.m_bEnableTestSiteVacc;

	UpdateData( FALSE );
}
void CDlgCustomMCFunction::SaveData()
{
	UpdateData();

	m_MCFunction.m_bEnableTorqueControl			= m_bManualTorque			== 1 ? true : false;
	m_MCFunction.m_bEnableTemperatureControl	= m_bManualTemp				== 1 ? true : false;
	m_MCFunction.m_bEnableInterfaceTesting		= m_bManualIFTesting		== 1 ? true : false;
	m_MCFunction.m_bEnableOffsetControl			= m_bManualOffset			== 1 ? true : false;
	m_MCFunction.m_bEnableTestDirectContact		= m_bManualTsDirectContact	== 1 ? true : false;
	m_MCFunction.m_bEnableTestSiteVacc			= m_bManualTestSieVacc		== 1 ? true : false;

	m.m_MCFunction = m_MCFunction;

	f.SaveMCEnable();
}
