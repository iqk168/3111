// DlgRepeatTrayEnable.cpp : implementation file
//

#include "stdafx.h"
#include "deer.h"
#include "DlgRepeatTrayEnable.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgRepeatTrayEnable dialog


CDlgRepeatTrayEnable::CDlgRepeatTrayEnable(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgRepeatTrayEnable::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgRepeatTrayEnable)
	m_bInputOutCtrl = FALSE;
	m_bBiningFunctionCtrl = FALSE;
	m_bNoneCtrl = FALSE;
	//}}AFX_DATA_INIT

	m_EnableRepeatTrayFun = m.m_EnableRepeatTrayFun;
}


void CDlgRepeatTrayEnable::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgRepeatTrayEnable)
	DDX_Control(pDX, IDOK,					m_btnOK);
	DDX_Control(pDX, IDCANCEL,				m_btnCancel);
	DDX_Check(pDX, IDC_E_INOUT_CTRL,		m_bInputOutCtrl);
	DDX_Check(pDX, IDC_E_BINNING_CTRL,		m_bBiningFunctionCtrl);
	DDX_Check(pDX, IDC_E_NONE, m_bNoneCtrl);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgRepeatTrayEnable, CDialog)
	//{{AFX_MSG_MAP(CDlgRepeatTrayEnable)
	ON_WM_SHOWWINDOW()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgRepeatTrayEnable message handlers

BOOL CDlgRepeatTrayEnable::PreTranslateMessage(MSG* pMsg) 
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

void CDlgRepeatTrayEnable::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);	
}

BOOL CDlgRepeatTrayEnable::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m.Info.bSubDlgOpen = true;
	f.UpdateButtonState();	

	// init button 
	m_btnOK.SetIcon(IDI_SAVE);
	m_btnOK.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnOK.SetFlat(FALSE);

	m_btnCancel.SetIcon(IDI_CANCEL);;
	m_btnCancel.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnCancel.SetFlat(FALSE);

	InitValue();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
void CDlgRepeatTrayEnable::InitValue()
{
	m_bInputOutCtrl			= m_EnableRepeatTrayFun.m_bInOutCtrl;
	m_bBiningFunctionCtrl	= m_EnableRepeatTrayFun.m_bTrayBinningCtrl;
	m_bNoneCtrl				= m_EnableRepeatTrayFun.m_bNone;

	UpdateData( FALSE );
}
void CDlgRepeatTrayEnable::SaveData()
{
	UpdateData();

	m_EnableRepeatTrayFun.m_bInOutCtrl			= m_bInputOutCtrl == 1 ? true : false;
	m_EnableRepeatTrayFun.m_bTrayBinningCtrl	= m_bBiningFunctionCtrl == 1 ? true : false;
	m_EnableRepeatTrayFun.m_bNone				= m_bNoneCtrl == 1 ? true : false;

	m.m_EnableRepeatTrayFun = m_EnableRepeatTrayFun;
	f.SaveRepeatTrayFunEnable();
}
void CDlgRepeatTrayEnable::OnOK() 
{
	SaveData();

	m.Info.bSubDlgOpen = false;
	f.UpdateButtonState();	
	
	CDialog::OnOK();
}

void CDlgRepeatTrayEnable::OnCancel() 
{
	m.Info.bSubDlgOpen = false;
	f.UpdateButtonState();	
	
	CDialog::OnCancel();
}
