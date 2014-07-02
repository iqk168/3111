// DlgAutoRetrySetting.cpp : implementation file
//

#include "stdafx.h"
#include "deer.h"
#include "DlgAutoRetrySetting.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgAutoRetrySetting dialog


CDlgAutoRetrySetting::CDlgAutoRetrySetting(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgAutoRetrySetting::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgAutoRetrySetting)
	m_dAdjustValue = 0.0;
	//}}AFX_DATA_INIT
}


void CDlgAutoRetrySetting::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgAutoRetrySetting)
	DDX_Control(pDX, IDC_E_LED_ENABLE,		m_ledEnableAutoRetry);
	DDX_Control(pDX, IDC_E_ALWAYS_ADJUST,	m_btnAlwaysAdjust);
	DDX_Control(pDX, IDCANCEL,				m_btnCancel);
	DDX_Control(pDX, IDOK,					m_btnOK);
	DDX_Text(pDX, IDC_E_ADJUST_VALUE,		m_dAdjustValue);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgAutoRetrySetting, CDialog)
	//{{AFX_MSG_MAP(CDlgAutoRetrySetting)
	ON_BN_CLICKED(IDC_E_LED_ENABLE, OnELedEnable)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgAutoRetrySetting message handlers

BOOL CDlgAutoRetrySetting::PreTranslateMessage(MSG* pMsg) 
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

BOOL CDlgAutoRetrySetting::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// init button 
	m_btnOK.SetIcon(IDI_SAVE);;
	m_btnOK.SetAlign(CButtonST::ST_ALIGN_VERT);;
	m_btnOK.SetFlat(FALSE);
	
	m_btnCancel.SetIcon(IDI_CANCEL);
	m_btnCancel.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnCancel.SetFlat(FALSE);
	
	//
	InitValue();

	//
	DisplayEnableStatus();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
void CDlgAutoRetrySetting::DisplayEnableStatus()
{
	m_ledEnableAutoRetry = m.Setting.m_bArmZAutoRetry  == 0 ? false : true;	
}
void CDlgAutoRetrySetting::InitValue()
{
	// Enable Status
	m_ledEnableAutoRetry.SetLed(CLed::LED_COLOR_GREEN);

	//
	if( m.m_AutoRetryAjsutValue.iAlwaysAdjsut == 1 )
		m_btnAlwaysAdjust.SetCheck(1);
	else
		m_btnAlwaysAdjust.SetCheck(0);
	m_dAdjustValue = m.m_AutoRetryAjsutValue.dAdjustValue;
	UpdateData( FALSE );
}
bool CDlgAutoRetrySetting::SaveData()
{
	//
	UpdateData();

	if( m_dAdjustValue <=0 || m_dAdjustValue > _MaxAutoRetry )
	{
		CString csMsg = _T("");
		int iMax = _MaxAutoRetry;
		csMsg.Format("Out of range..[0~%d]", iMax );
		AfxMessageBox( csMsg );
		return false;
	}

	//
	int Sensor = m_btnAlwaysAdjust.GetCheck();
	if(Sensor)
		m.m_AutoRetryAjsutValue.iAlwaysAdjsut = 1;
	else
		m.m_AutoRetryAjsutValue.iAlwaysAdjsut = 0;

	m.m_AutoRetryAjsutValue.dAdjustValue = m_dAdjustValue;

	//
	f.SaveAutoRetryExterndValue();

	return true;
}
void CDlgAutoRetrySetting::OnCancel() 
{
	
	CDialog::OnCancel();
}

void CDlgAutoRetrySetting::OnOK() 
{
	//
	if( !SaveData() )
		return;
	
	CDialog::OnOK();
}

void CDlgAutoRetrySetting::OnELedEnable() 
{
	//
	if( m.Setting.m_bArmZAutoRetry == 1 )
		m.Setting.m_bArmZAutoRetry = 0;
	else
		m.Setting.m_bArmZAutoRetry = 1;

	//
	DisplayEnableStatus();

	//
	f.SaveAutoRetryEnable();
}
