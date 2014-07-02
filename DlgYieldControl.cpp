// DlgYieldControl.cpp : implementation file
//

#include "stdafx.h"
#include "deer.h"
#include "DlgYieldControl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgYieldControl dialog


CDlgYieldControl::CDlgYieldControl(bool Mode, CWnd* pParent /*=NULL*/)
	: CDialog(CDlgYieldControl::IDD, pParent)
{
	m_YieldSetting = m.YieldSetting;
	//{{AFX_DATA_INIT(CDlgYieldControl)
	//}}AFX_DATA_INIT
	m_fChange = false;
	m_Mode = Mode;
}


void CDlgYieldControl::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgYieldControl)

	DDX_Control(pDX, IDC_CONTINUE_FAIL,			m_edtContineFail);
	DDX_Control(pDX, IDC_YIELD_WINDOW,			m_edtYieldWindow);
	DDX_Control(pDX, IDC_YIELD_LIMIT,			m_edtYieldLimit);
	DDX_Control(pDX, IDC_RETEST,				m_edtRetestCount);
	//
	DDX_Control(pDX, IDC_SAVE,					m_btnSave);
	DDX_Control(pDX, IDC_ENABLE_CONTINUE_FAIL,	m_btnContinueFail);
	DDX_Control(pDX, IDC_ENABLE_YIELD_CONTROL,	m_btnYieldControl);
	//
	DDX_Control(pDX, IDOK,						m_btnOK);
	DDX_Control(pDX, IDCANCEL,					m_btnCancel);
	//
	DDX_Control(pDX, IDC_DROP_MODE,				m_btnDropMode);	
	DDX_Control(pDX, IDC_DROP_TIMER,			m_edtDropTime);
	DDX_Control(pDX, IDC_DROP_HIGH,				m_edtDropHigh);
	DDX_Text(pDX, IDC_DROP_HIGH,				m_dDropHigh);
	DDX_Text(pDX, IDC_DROP_TIMER,				m_dDropTime);
	DDX_Text(pDX, IDC_RETEST,					iRetestCount);
	//}}AFX_DATA_MAP

	DDX_Text(pDX, IDC_YIELD_LIMIT,				m_YieldSetting.dYieldLimit);
	DDV_MinMaxDouble(pDX,						m_YieldSetting.dYieldLimit, 1., 100.);
	DDX_Text(pDX, IDC_YIELD_WINDOW,				m_YieldSetting.iYieldWindow);
	DDV_MinMaxLong(pDX,							m_YieldSetting.iYieldWindow, 2, 200);
	DDX_Text(pDX, IDC_CONTINUE_FAIL,			m_YieldSetting.iFailCount);
	DDV_MinMaxLong(pDX,							m_YieldSetting.iFailCount, 2, 100);
	DDX_Text(pDX, IDC_RETEST,					m_YieldSetting.iRetestCount);
	DDV_MinMaxLong(pDX,							m_YieldSetting.iRetestCount, 0, 5);

	// Drop
	DDX_Text(pDX, IDC_DROP_HIGH,				m_YieldSetting.dDropHigh);
	DDV_MinMaxDouble(pDX,						m_YieldSetting.dDropHigh, 1., 5.);
	DDX_Text(pDX, IDC_DROP_TIMER,				m_YieldSetting.dDropTimer);
	DDV_MinMaxDouble(pDX,						m_YieldSetting.dDropTimer, 0.2, 2.);
}


BEGIN_MESSAGE_MAP(CDlgYieldControl, CDialog)
	//{{AFX_MSG_MAP(CDlgYieldControl)
	ON_WM_DESTROY()
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_SAVE,						OnSave)
	ON_BN_CLICKED(IDC_ENABLE_YIELD_CONTROL,		OnEnableYieldControl)
	ON_BN_CLICKED(IDC_ENABLE_CONTINUE_FAIL,		OnEnableContinueFail)
	ON_EN_CHANGE(IDC_YIELD_LIMIT,				OnChangeYieldLimit)
	ON_EN_CHANGE(IDC_CONTINUE_FAIL,				OnChangeContinueFail)
	ON_EN_CHANGE(IDC_YIELD_WINDOW,				OnChangeYieldWindows)
	ON_EN_CHANGE(IDC_RETEST,					OnChangeReset)
	ON_BN_CLICKED(IDC_DROP_MODE,				OnDropMode)
	ON_WM_SHOWWINDOW()

	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgYieldControl message handlers

void CDlgYieldControl::OnOK() 
{	
	m.Info.bSubDlgOpen = false;
	f.UpdateButtonState();

	CDialog::OnOK();
}

void CDlgYieldControl::OnCancel() 
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
			OnSave();

		// Data already be modify.
		// So. 
		// If User say YES. We call OnOK() function to store alignment value
		// If User say NO. We did not do anything.
	}
	else
	{
		m.Info.bSubDlgOpen = false;
		f.UpdateButtonState();	
		CDialog::OnCancel();
		// Data not be modify.
		// Just Get out the Alignment dialog.
	}
}

BOOL CDlgYieldControl::OnInitDialog() 
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
	
	// UI Default status
	m_btnYieldControl.SetIcon(IDI_FLOW_CHAR);
	m_btnYieldControl.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnYieldControl.SetFlat(FALSE);

	m_btnContinueFail.SetIcon(IDI_CONTINUE_FAIL);
	m_btnContinueFail.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnContinueFail.SetFlat(FALSE);

	m_btnDropMode.SetIcon(IDI_DROP_MODE);
	m_btnDropMode.SetAlign(CButtonST::ST_ALIGN_VERT);	
	
	//
	UpdateStatus();

	//
	LevelControl();

	//
	InitTips();

	//
	f.SetTitleExtend(this, theApp.enTitleTrayFile );

	//
	f.ChangeLanguage(GetSafeHwnd());
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
void CDlgYieldControl::InitTips()
{
	// Init Tips
	m_ToolTip.Create(this);
	m_ToolTip.SetMaxTipWidth(800);
	m_ToolTip.SetDelayTime( TTDT_AUTOPOP, 10000 );
	m_ToolTip.SetDelayTime( TTDT_INITIAL, 25 );
	m_ToolTip.EnableToolTips(true);

	m_ToolTip.AddTool( GetDlgItem(IDC_ENABLE_YIELD_CONTROL),					
		_T("Yield control\r\nTotal fail ic / total ic\r\nIf value < Yield Limitation (%), It will alarm\r\nControl Window is number of samples") );
	m_ToolTip.AddTool( GetDlgItem(IDC_ENABLE_CONTINUE_FAIL),					
		_T("Continue fail\r\nIf continue fail counter > Fail Count (pcs)\r\nIt will alarm") );

}
void CDlgYieldControl::LevelControl()
{
	// Make a level .
	// If true. It mean setup level 
	// setup level can modify yield setting.
	if( !m_Mode )
	{
		BOOL bEnable = FALSE;
		m_btnYieldControl.EnableWindow( bEnable );
		m_btnContinueFail.EnableWindow( bEnable );

		m_edtYieldWindow.EnableWindow( bEnable );
		m_edtContineFail.EnableWindow( bEnable );
		m_edtYieldLimit.EnableWindow( bEnable );
		m_edtRetestCount.EnableWindow( bEnable );
		m_btnSave.ShowWindow( bEnable );
		m_btnDropMode.EnableWindow( bEnable );

		m_edtDropHigh.EnableWindow( bEnable );
		m_edtDropTime.EnableWindow( bEnable );
	}
	else
	{
		/*
		BOOL bEnable = TRUE;
		m_btnYieldControl.EnableWindow( bEnable );
		m_btnContinueFail.EnableWindow( bEnable );

		m_edtYieldWindow.EnableWindow( bEnable );
		m_edtContineFail.EnableWindow( bEnable );
		m_edtYieldLimit.EnableWindow( bEnable );
		m_edtRetestCount.EnableWindow( bEnable );
		m_btnSave.EnableWindow( bEnable );
		m_btnDropMode.EnableWindow( bEnable );

		m_edtDropHigh.EnableWindow( bEnable );
		m_edtDropTime.EnableWindow( bEnable );
		*/
	}
}
////////////////////////////////////////////////////////////////
// On Change
// Set flag to true.
void CDlgYieldControl::OnChangeYieldLimit()
{
	m_fChange = true;
}
void CDlgYieldControl::OnChangeContinueFail()
{
	m_fChange = true;
}
void CDlgYieldControl::OnChangeYieldWindows()
{
	m_fChange = true;
}
void CDlgYieldControl::OnChangeReset()
{
	m_fChange = true;
}
////////////////////////////////////////////////////////////////

void CDlgYieldControl::OnDestroy() 
{
	m.Info.bSubDlgOpen = false;
	f.UpdateButtonState();

	CDialog::OnDestroy();
}

void CDlgYieldControl::OnClose() 
{	
	m.Info.bSubDlgOpen = false;
	f.UpdateButtonState();
	
	CDialog::OnClose();
}

void CDlgYieldControl::OnSave() 
{
	if(UpdateData())
	{	
		// Drop Mode
		int DropMode = m_btnDropMode.GetCheck();
		if( DropMode == 1 )
			m_YieldSetting.bDropMode = 1;	// Drop Mode 
		else
			m_YieldSetting.bDropMode = 0;	// Direct Contact


		tagYieldSetting		m_OldYieldSetting;
		m_OldYieldSetting = m.YieldSetting;
		
		m.YieldSetting = m_YieldSetting;
		f.SaveYield();

		if( m_OldYieldSetting.iFailCount != m_YieldSetting.iFailCount ||
			m_OldYieldSetting.iYieldWindow != m_YieldSetting.iYieldWindow ||
			m_OldYieldSetting.dYieldLimit  != m_YieldSetting.dYieldLimit )
		{
			// Reset Yield Limit Windows
			theApp.m_tTester.ReSizeYieldLimit( m.YieldSetting.iYieldWindow );
			// 重新設定 Run Page 的顯示設定
			m.Page.Run.m_ContinueFail.Clear();	// 清除顯示
			m.Page.Run.m_ContinueFail.SetLimitation( m.YieldSetting.iFailCount );	// 清除顯示
			//
			// 如果有不一樣, 更動過, 我們才重新變更 Run Page 畫面.!
		}

		m.Info.bSubDlgOpen = false;
		f.UpdateButtonState();

		CDialog::OnOK();
	}
}

void CDlgYieldControl::OnEnableYieldControl() 
{
	if( m_YieldSetting.bYieldControlEnable == 1 )
		m_YieldSetting.bYieldControlEnable = 0;		
	else	
		m_YieldSetting.bYieldControlEnable = 1;

	m_fChange = true;

	UpdateStatus();
}

void CDlgYieldControl::OnDropMode()
{	
	if( m.YieldSetting.bDropMode == 1 )
		m.YieldSetting.bDropMode = 0;
	else
		m.YieldSetting.bDropMode = 1;

	UpdateStatus();

	m_fChange = true;

	f.ChangeLanguage(GetSafeHwnd());
}

void CDlgYieldControl::OnEnableContinueFail() 
{
	if( m_YieldSetting.bContinueFailEnable == 1 )
		m_YieldSetting.bContinueFailEnable = 0;
	else
		m_YieldSetting.bContinueFailEnable = 1;

	// 如果 m.YieldSetting.bContinueFailEnable == 1 
	// 表示有啟動

	m_fChange = true;

	UpdateStatus();
}

void CDlgYieldControl::UpdateStatus()
{
	bool bYieldControl = false;
	if ( m_YieldSetting.bYieldControlEnable == 1)
	{
		bYieldControl = true;
		m_btnYieldControl.SetIcon(IDI_FLOW_CHAR);
	}
	else
	{
		bYieldControl = false;
		m_btnYieldControl.SetIcon(IDI_YIELD_CANCEL);
	}
	// Enable Yield Control
	
	m_edtYieldLimit.EnableWindow( bYieldControl );
	m_edtYieldWindow.EnableWindow( bYieldControl );

	bool bContinueFail = false;
	if ( m_YieldSetting.bContinueFailEnable == 1)
	{
		bContinueFail = true;
		m_btnContinueFail.SetIcon(IDI_CONTINUE_FAIL);
	}
	else
	{
		bContinueFail = false;
		m_btnContinueFail.SetIcon(IDI_CONTINUE_FAIL_CANCLE);
	}
	// Enable Yield Control Continue fail.

	m_edtContineFail.EnableWindow( bContinueFail );

	if( m.YieldSetting.bDropMode == 1)
	{
		m_btnDropMode.SetIcon(IDI_DROP_MODE);
		m_btnDropMode.SetCheck(true);
		m_btnDropMode.SetWindowText("Drop Mode");

		m_edtDropHigh.EnableWindow( TRUE );
		m_edtDropTime.EnableWindow( TRUE );
	}
	else
	{
		m_btnDropMode.SetIcon(IDI_DIRECT_CONTACT);
		m_btnDropMode.SetCheck(false);
		m_btnDropMode.SetWindowText("Direct Contact");

		m_edtDropHigh.EnableWindow( FALSE );
		m_edtDropTime.EnableWindow( FALSE );	
	}
}

void CDlgYieldControl::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);	
}

BOOL CDlgYieldControl::PreTranslateMessage(MSG* pMsg) 
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

