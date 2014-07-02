// DlgSiteSetting.cpp : implementation file
//

#include "stdafx.h"
#include "deer.h"
#include "DlgSiteSetting.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgSiteSetting dialog


CDlgSiteSetting::CDlgSiteSetting(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgSiteSetting::IDD, pParent)
{
	m_Site = m.Site;

	//{{AFX_DATA_INIT(CDlgSiteSetting)
	//}}AFX_DATA_INIT
}


void CDlgSiteSetting::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgSiteSetting)
	DDX_Control(pDX, IDC_BIN_FOR_CATORGY2,	m_edtDemoDummyForCatorgy2);
	DDX_Control(pDX, IDC_BIN_FOR_CATORGY,	m_edtDemoDummyForCatorgy);
	DDX_Control(pDX, IDC_SAVE,				m_btnSave);
	DDX_Control(pDX, IDC_DEMO_TEST_TIME,	m_edtDemoTestTime);
	DDX_Control(pDX, IDCANCEL,				m_btnCancel);
	DDX_Control(pDX, IDOK,					m_btnOK);
	//}}AFX_DATA_MAP

	DDX_Control(pDX, IDC_RUN_MODE1,			m_btnRunMode[0]);
	DDX_Control(pDX, IDC_RUN_MODE2,			m_btnRunMode[1]);
	DDX_Control(pDX, IDC_RUN_MODE3,			m_btnRunMode[2]);	

	DDX_Text(pDX, IDC_DEMO_TEST_TIME,		m_Site.dDemoTestTime );
	DDX_Text(pDX, IDC_BIN_FOR_CATORGY,		m_Site.iSiteDummyBinForCatorgy );	
	DDX_Text(pDX, IDC_BIN_FOR_CATORGY2,		m_Site.csSiteDummyBinForCatorgy );	

}

BEGIN_MESSAGE_MAP(CDlgSiteSetting, CDialog)
	//{{AFX_MSG_MAP(CDlgSiteSetting)
	ON_WM_DESTROY()
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_RUN_MODE1, OnRunMode1)
	ON_BN_CLICKED(IDC_RUN_MODE2, OnRunMode2)
	ON_BN_CLICKED(IDC_RUN_MODE3, OnRunMode3)
	ON_BN_CLICKED(IDC_SAVE,		 OnSave)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgSiteSetting message handlers

BOOL CDlgSiteSetting::OnInitDialog() 
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

	m_btnSave.SetIcon(IDI_SAVE);
	m_btnSave.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnSave.SetFlat(FALSE);

/*
IDI_MODE_OFFLINE
IDI_MODE_DEMO
IDI_MODE_ONLINE
*/

	// 設定圖案
	m_btnRunMode[0].SetIcon(IDI_MODE_ONLINE);
	m_btnRunMode[0].SetAlign(CButtonST::ST_ALIGN_VERT);
//	m_btnRunMode[0].SetFlat(FALSE);

	m_btnRunMode[1].SetIcon(IDI_MODE_OFFLINE);
	m_btnRunMode[1].SetAlign(CButtonST::ST_ALIGN_VERT);
//	m_btnRunMode[1].SetFlat(FALSE);

	m_btnRunMode[2].SetIcon(IDI_MODE_DEMO);
	m_btnRunMode[2].SetAlign(CButtonST::ST_ALIGN_VERT);
//	m_btnRunMode[2].SetFlat(FALSE);

	UpdateRunModeStatus( m.Site.iRunMode );
	CheckUIForRunMode( m.Site.iRunMode );
	// Set UI

	//
	InitTips();

	//
	f.SetTitleExtend(this, theApp.enTitleTrayFile );

	//
	f.ChangeLanguage(GetSafeHwnd());

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
void CDlgSiteSetting::InitTips() 
{
	// Init Tips
	m_ToolTip.Create(this);
	m_ToolTip.SetMaxTipWidth(800);
	m_ToolTip.SetDelayTime( TTDT_AUTOPOP, 10000 );
	m_ToolTip.SetDelayTime( TTDT_INITIAL, 25 );
	m_ToolTip.EnableToolTips(true);

	//
	m_ToolTip.AddTool( GetDlgItem(IDC_RUN_MODE1),	
		_T("On Line Mode\r\n#1 It will detect all error\r\n#2 It will send sot to tester and wait eot(bin value)") );
	m_ToolTip.AddTool( GetDlgItem(IDC_RUN_MODE2),	
		_T("Off Line Mode\r\n#1 It will detect all error\r\n#2 It won't send sot to tester)") );
	m_ToolTip.AddTool( GetDlgItem(IDC_RUN_MODE3),	
		_T("Demo Mode\r\n#1 It will bypass ic detect error\r\n#2 It won't send sot to tester)") );

	//
	m_ToolTip.AddTool( GetDlgItem(IDC_STATIC_SITE_SET_TT),	
		_T("Demo/Offline simulation test times") );

	m_ToolTip.AddTool( GetDlgItem(IDC_STATIC_SITE_BIN),	
		_T("Demo/Offline simulation test result") );
}
void CDlgSiteSetting::OnDestroy() 
{
	m.Info.bSubDlgOpen = false;
	f.UpdateButtonState();

	CDialog::OnDestroy();	
}

void CDlgSiteSetting::OnClose() 
{
	m.Info.bSubDlgOpen = false;
	f.UpdateButtonState();
	
	CDialog::OnClose();
}

void CDlgSiteSetting::OnOK() 
{
	UpdateData();

	CDialog::OnOK();
}

void CDlgSiteSetting::OnSave() 
{
	UpdateData();

	if( m_Site.iSiteDummyBinForCatorgy <= 0 || m_Site.iSiteDummyBinForCatorgy > 16 )
	{
		AfxMessageBox("Please re-set the value , Range 1~16");
		return;
	}	

	m.Site = m_Site;
	// Set Site Setting 

	f.SaveSiteSetting();
	// Save to current TrayFile

	CDialog::OnOK();
}
void CDlgSiteSetting::OnCancel() 
{
	m.Info.bSubDlgOpen = false;
	f.UpdateButtonState();
	
	CDialog::OnCancel();
}

void CDlgSiteSetting::OnRunMode1() 
{
	if( !f.CheckEnaleChange() )
	{
		m_Site.iRunMode = m.Site.iRunMode;
		UpdateRunModeStatus(m_Site.iRunMode);
		CheckUIForRunMode(m_Site.iRunMode);
	}
	else
	{
		m_Site.iRunMode = theApp.enOnLine;
		UpdateRunModeStatus(m_Site.iRunMode);
		CheckUIForRunMode(m_Site.iRunMode);
	}
}
void CDlgSiteSetting::OnRunMode2() 
{
	if( !f.CheckEnaleChange() )
	{
		m_Site.iRunMode = m.Site.iRunMode;
		UpdateRunModeStatus(m_Site.iRunMode);
		CheckUIForRunMode(m_Site.iRunMode);
	}
	else
	{
		m_Site.iRunMode = theApp.enOffLine;
		UpdateRunModeStatus(m_Site.iRunMode);
		CheckUIForRunMode(m_Site.iRunMode);
	}
}
void CDlgSiteSetting::OnRunMode3() 
{
	if( !f.CheckEnaleChange() )
	{
		m_Site.iRunMode = m.Site.iRunMode;
		UpdateRunModeStatus(m_Site.iRunMode);
		CheckUIForRunMode(m_Site.iRunMode);
	}
	else
	{
		m_Site.iRunMode = theApp.enDemo;
		UpdateRunModeStatus(m_Site.iRunMode);
		CheckUIForRunMode(m_Site.iRunMode);
	}
}

void CDlgSiteSetting::CheckUIForRunMode(int mode)
{
	// Serive Request, if Only disable the Dummy UI
	if( mode == theApp.enOnLine )
	{
		m_edtDemoTestTime.EnableWindow( FALSE );
		m_edtDemoDummyForCatorgy.EnableWindow( FALSE );
	}
	else
	{
		m_edtDemoTestTime.EnableWindow( TRUE );
		m_edtDemoDummyForCatorgy.EnableWindow( TRUE );
	}
}

void CDlgSiteSetting::UpdateRunModeStatus(int iMode)
{
	// 重新設定 Run Mode 按鈕的狀態
	for(int i=0;i<theApp.enRunModeEnd;i++)
	{
		if(i == iMode)
			m_btnRunMode[i].SetCheck(true);
		else
			m_btnRunMode[i].SetCheck(false);
	}
}


BOOL CDlgSiteSetting::PreTranslateMessage(MSG* pMsg) 
{
	m_ToolTip.RelayEvent(pMsg); 

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
