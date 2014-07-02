// DlgLotInformationDone.cpp : implementation file
//

#include "stdafx.h"
#include "deer.h"
#include "DlgLotInformationDone.h"
#include "DlgLotInformationProgress.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgLotInformationDone dialog


CDlgLotInformationDone::CDlgLotInformationDone(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgLotInformationDone::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgLotInformationDone)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgLotInformationDone::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgLotInformationDone)
	DDX_Control(pDX, IDC_LOT_DEVICE_ID, m_wndLotDeviceID);
	DDX_Control(pDX, IDC_LOT_MACHINE, m_wndLotMachineID);
	DDX_Control(pDX, IDC_LOT_NO, m_wndLotNo);
	DDX_Control(pDX, IDC_LOT_OPERATER, m_wndLotOperator);
	DDX_Control(pDX, IDC_LOT_PROGRAM_ID, m_wndLotProgramerID);
	DDX_Control(pDX, IDCANCEL, m_btnCancel);
	DDX_Control(pDX, IDOK, m_btnOK);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgLotInformationDone, CDialog)
	//{{AFX_MSG_MAP(CDlgLotInformationDone)
	ON_WM_DESTROY()
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgLotInformationDone message handlers

void CDlgLotInformationDone::OnDestroy() 
{
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here
	
}

BOOL CDlgLotInformationDone::OnInitDialog() 
{
	CDialog::OnInitDialog();

	m.Info.bSubDlgOpen = true;
	f.UpdateButtonState();
	
	// init button 
	m_btnOK.SetIcon(IDI_OK);;
	m_btnOK.SetAlign(CButtonST::ST_ALIGN_VERT);;
	m_btnOK.SetFlat(FALSE);
	
	m_btnCancel.SetIcon(IDI_CANCEL);
	m_btnCancel.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnCancel.SetFlat(FALSE);

	UpdataValue();
	// Updata UI.

	UpdataUI(FALSE);
	// Disable = FALSE
	// Enable  = TRUE

	f.ChangeLanguage(GetSafeHwnd());
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgLotInformationDone::OnClose() 
{
	m.Info.bSubDlgOpen = false;
	f.UpdateButtonState();
	
	CDialog::OnClose();
}

void CDlgLotInformationDone::OnOK() 
{
	if( m.Setting.m_bEnableLotDoneProgress )
	{
		CDlgLotInformationProgress dlg;
		dlg.DoModal();

		m.Info.bSubDlgOpen = false;
		f.UpdateButtonState();
	}
	else
	{
		f.LotDone();	
		m.Info.bSubDlgOpen = false;
		f.UpdateButtonState();
	}

	//
	f.AutoSeletLastTrayFile();

	//
	CDialog::OnOK();
}

void CDlgLotInformationDone::OnCancel() 
{
	m.Info.bSubDlgOpen = false;
	f.UpdateButtonState();

	CDialog::OnCancel();
}

void CDlgLotInformationDone::UpdataUI(bool ui)
{
	bool bEnable = false;

	bEnable = ui;

	m_wndLotDeviceID.EnableWindow(bEnable);
	m_wndLotMachineID.EnableWindow(bEnable);
	m_wndLotNo.EnableWindow(bEnable);
	m_wndLotOperator.EnableWindow(bEnable);
	m_wndLotProgramerID.EnableWindow(bEnable);
}

void CDlgLotInformationDone::UpdataValue() 
{
	// Init value
	CString LotInfoDeviceID		= "";
	CString LotInfoMachineID	= "";
	CString LotInfoNo			= "";
	CString LotInfoOperator		= "";
	CString LotInfoProgramerID	= "";

	LotInfoDeviceID					= m.LotInfo.LotInfoDeviceID;
	LotInfoMachineID				= m.LotInfo.LotInfoMachineID;
	LotInfoNo						= m.LotInfo.LotInfoNo;
	LotInfoOperator					= m.LotInfo.LotInfoOperator; 
	LotInfoProgramerID				= m.LotInfo.LotInfoProgramerID;

	m_wndLotDeviceID.SetWindowText(LotInfoDeviceID);
	m_wndLotMachineID.SetWindowText(LotInfoMachineID);
	m_wndLotNo.SetWindowText(LotInfoNo);
	m_wndLotOperator.SetWindowText(LotInfoOperator);
	m_wndLotProgramerID.SetWindowText(LotInfoProgramerID);
}

BOOL CDlgLotInformationDone::PreTranslateMessage(MSG* pMsg) 
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
