// DlgSetting.cpp : implementation file
//

#include "stdafx.h"
#include "deer.h"
#include "DlgSetting.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgSetting dialog


CDlgSetting::CDlgSetting(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgSetting::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgSetting)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgSetting::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgSetting)
	DDX_Control(pDX, IDCANCEL,		m_btnCancel);
	DDX_Control(pDX, IDOK,			m_btnOK);
	DDX_Text(pDX, IDC_MACHINE_ID,	m_csMachine);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgSetting, CDialog)
	//{{AFX_MSG_MAP(CDlgSetting)
	ON_WM_DESTROY()
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgSetting message handlers

void CDlgSetting::SetHandlerInfo()
{
	// 取得本 exe 檔的路徑、名稱	//
	TCHAR szTemp[_MAX_PATH];
	TCHAR szVersion[16]; 
	if (GetModuleFileName(NULL, szTemp, _MAX_PATH))
	{
		// 利用取得的 exe 檔案的路徑名稱來取得它的版本
		f.MyGetVersion(szTemp, szVersion, sizeof(szVersion) / sizeof(szVersion[0]));
		_stprintf(szTemp, "3111 V%s", szVersion);

		::SetDlgItemText(GetSafeHwnd(), IDC_HANDLER_ID, szTemp);
	}
}

void CDlgSetting::OnOK() 
{		
	UpdateData();

	CString csMachineID;
	csMachineID = m_csMachine;

	if( csMachineID == "" )
	{
		AfxMessageBox("Please input Machine ID.!");
		return;
	}
	// User must input Machine ID.
	// So if Empty. Alert and return

	m.UI.MachineID = csMachineID;

	f.SaveMachineID();
	// Save in UI.UI

	::SendMessage(theApp.m_pMainWnd->GetSafeHwnd(), WM_HANDLER_ID, NULL, NULL);
	// Send a message to Main Dialog for change handler ID

	m.Info.bSubDlgOpen = false;
	f.UpdateButtonState();

	CDialog::OnOK();
}

void CDlgSetting::OnCancel() 
{
	m.Info.bSubDlgOpen = false;
	f.UpdateButtonState();

	CDialog::OnCancel();
}

BOOL CDlgSetting::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// init button 
	m_btnOK.SetIcon(IDI_SAVE);
	m_btnOK.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnOK.SetFlat(FALSE);

	m_btnCancel.SetIcon(IDI_CANCEL);;
	m_btnCancel.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnCancel.SetFlat(FALSE);

	// 設定 目前的軟體版本.與主畫面的功能相同
	SetHandlerInfo();

	// 顯示 目前的 Machine ID
	SetMachineInfo();
	
	m.Info.bSubDlgOpen = true;
	f.UpdateButtonState();

	f.ChangeLanguage(GetSafeHwnd());

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgSetting::SetMachineInfo()
{
	m_csMachine = m.UI.MachineID;

	UpdateData(FALSE);
}

void CDlgSetting::OnDestroy() 
{
	m.Info.bSubDlgOpen = false;
	f.UpdateButtonState();

	CDialog::OnDestroy();
}

void CDlgSetting::OnClose() 
{
	m.Info.bSubDlgOpen = false;
	f.UpdateButtonState();
	
	CDialog::OnClose();
}

BOOL CDlgSetting::PreTranslateMessage(MSG* pMsg) 
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
