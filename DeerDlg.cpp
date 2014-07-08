// DeerDlg.cpp : implementation file
//

#include "stdafx.h"

#include <afxmt.h>
#include <math.h>

// Dlg
#include "DlgPassword.h"
#include "DlgIOMontior.h"
#include "DlgMotorStatus.h"
#include "DlgMotorMontior.h"
#include "DlgThreadMontior.h"
#include "DlgPasswordNeed.h"
#include "DlgLogEnable.h"
#include "DlgDebugError.h"
#include "DlgSummaryReport.h"
#include "DlgDebugErrorList.h"
#include "DlgHandlerStatusList.h"
#include "DlgJamRateReportTool.h"
#include "DlgAutoRetrySetting.h"
#include "DlgButton.h"
#include "DlgTrayStatus.h"
#include "DlgBinStatus.h"
#include "DlgSocketVisionCam.h"
#include "DlgCylinderLifeTimeTool.h"
#include "DlgWestTool.h"
#include "DlgTSRemainIC.h"
#include "DlgTorqueTool.h"

//
#include "BtnST.h"
#include "Deer.h"
#include "DeerDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDeerDlg dialog

CDeerDlg::CDeerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDeerDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDeerDlg)
	m_csMachine = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32

	m_bShowMainMsg = false;

//	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_hIcon = AfxGetApp()->LoadIcon(IDI_MAINFRAME);
	
}

void CDeerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDeerDlg)
	DDX_Control(pDX, IDC_MAIN_MSG,		m_wndMainMsg);
	DDX_Control(pDX, IDC_TIME,			m_wndTime);
	DDX_Control(pDX, IDC_SHUT_DOWN,		m_btnShutDown);
	DDX_Control(pDX, IDC_USER,			m_btnUser);
	DDX_Control(pDX, IDC_VIEW_TABLE,	m_MainTab);
	DDX_Text(pDX, IDC_MACHINE,			m_csMachine);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDeerDlg, CDialog)
	//{{AFX_MSG_MAP(CDeerDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND(IDV_DEBUG,						OnDebug)		
	ON_COMMAND(IDV_VISUAL,						OnVisualPanel)
	ON_BN_CLICKED(IDC_USER,						OnUser)
	ON_COMMAND(IDV_TAB,							OnTab)
	ON_COMMAND(IDV_IO_MONITOR,					OnIOMontior)
	ON_COMMAND(IDV_MOTOR_MONTIOR,				OnMotorMontior)
	ON_COMMAND(IDV_THREAD_MONTIOR,				OnThreadMontior)
	ON_COMMAND(IDV_THREAD,						OnThread)	
	ON_COMMAND(IDV_MOTOR_STATUS,				OnMotorStatus)
	ON_COMMAND(IDV_BUTTON,						OnButton)
	ON_COMMAND(IDV_BIN_STATUS,					OnBinStatus)
	ON_COMMAND(IDV_MOTOR_SIMPLE,				OnMotorSimpleStatus)
	ON_COMMAND(IDV_FILE,						OnReLoadFile)
	ON_COMMAND(IDV_LOG_ENABLE,					OnLogEnable)
	ON_COMMAND(IDV_DATA,						OnDataUsing)
	ON_COMMAND(IDV_DEBUG_ERROR,					OnDebugError)
	ON_COMMAND(IDV_SUMMARY_REPORT,				OnSummaryReport)
	ON_COMMAND(IDV_ERROR_LIST,					OnErrorList)
	ON_COMMAND(IDV_HANDLER_STATUS_REPORT,		OnHandlerStatusReport)
	ON_COMMAND(IDV_JAM_RATE_REPORT,				OnJamRateReport)
	ON_COMMAND(IDV_AUTO_RETRY_SETTING,			OnAutoRetrySetting)
	ON_COMMAND(IDV_TRAY_STATUS,					OnTrayStatus)
	ON_COMMAND(IDV_BIN_COLOR,					OnBinColor)
	ON_COMMAND(IDV_CCD_LIST,					OnCCDList)
	ON_COMMAND(IDV_YIELD_MONITOR,				OnYieldMonitor)
	ON_COMMAND(IDV_UPH_DATA,					OnUPHData)
	ON_COMMAND(IDV_CYLINDER_LIFE,				OnCylinderLifeTimeTool)
	ON_COMMAND(IDV_WEST_TOOL,					OnWestCtrlTool)
	ON_COMMAND(IDV_TS_REMAIN_IC,				OnTSRemainIC)
	ON_COMMAND(IDV_TORQUE_TOOL,					OnTorqueCtrlTool)
	ON_COMMAND(IDV_COMMUNICATION_TOOL,			OnCommunicationTool)
	ON_COMMAND(IDV_REMOTE_COMM,					OnRemoteComm)

	ON_MESSAGE(WM_HANDLER_ID,					OnHandlerID) // UI
	ON_NOTIFY(TCN_SELCHANGE, IDC_VIEW_TABLE,	OnSelchangeViewTable)
	ON_MESSAGE(WM_ERROR_CLOSE,					OnErrorClose)
	ON_MESSAGE(WM_ERROR_OPEN,					OnError)
	ON_BN_CLICKED(IDC_SHUT_DOWN,				OnShutDown)
	ON_WM_TIMER()
	ON_WM_DESTROY()
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDeerDlg message handlers

BOOL CDeerDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m.Info.iStatus = theApp.enUninitial;

	f.m_Log.AddLogEvent( "Deer OnInitDialog" );
	

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}
	f.m_Log.AddLogEvent( "Deer OnInitDialog Menu OK" );

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// Socket CCD
	if( m.Setting.m_bSocketCCDDoubleDetect == 1 )
	{
		if( !f.InitCCDSocket() )
			m.Setting.m_bSocketCCDDoubleDetect = 0;			
		// 如果 CCD 啟動失敗, 那麼就關掉 CCD Socket 的功能
		TRACE("# InitSokcetCCD\n");
	}
	// Pin1 CCD
	if( m.Setting.m_bPin1CCDDoubleDetect == 1 )
	{
		if( !f.InitCCDPin1() )
			m.Setting.m_bPin1CCDDoubleDetect = 0;			
		// 如果 CCD 啟動失敗, 那麼就關掉 CCD Socket 的功能
		TRACE("# InitPin1CCD\n");
	}

	// Create Thread
	theApp.m_tArm.CreateThread();							TRACE("# m_tArm\n");
	theApp.m_tInspect.CreateThread();						TRACE("# m_tInspect\n");
	theApp.m_tTester.CreateThread();						TRACE("# m_tTester\n");
	theApp.m_tInserter.CreateThread();						TRACE("# m_tInserter\n");
	theApp.m_tManualCtrl.CreateThread();					TRACE("# m_tManualCtrl\n");
	theApp.m_thInitialArm.CreateThread();					TRACE("# m_thInitialArm\n");

	//
	f.m_Log.AddLogEvent( "Deer Create Thread Finish" );

	TRACE("# Initial CreatThread Done\n");

	// --------------------------------------------------------------------------------------------
	// Deer Dialog. 
	//設定視窗重繪結構參數	
	CRect ir,cr;
	m_MainTab.GetItemRect(0, &ir);
	m_MainTab.GetClientRect(&cr);

	//建立PageInitial視窗及畫面大小重新調整
	m.Page.Initial.Create(CPageInitial::IDD, &m_MainTab);
	m.Page.Initial.SetWindowPos(NULL, ir.left + 2, ir.bottom + 5, cr.right -5, cr.bottom - 35, SWP_NOZORDER);
	m.Page.Initial.ShowWindow(SW_HIDE);	

	//建立PageRun視窗及畫面大小重新調整
	m.Page.Run.Create(CPageRun::IDD, &m_MainTab);
	m.Page.Run.SetWindowPos(NULL, ir.left + 2, ir.bottom + 5, cr.right -5, cr.bottom - 35, SWP_NOZORDER);
	m.Page.Run.ShowWindow(SW_HIDE);

	//建立PageUser視窗及畫面大小重新調整
	m.Page.User.Create(CPageUser::IDD, &m_MainTab);
	m.Page.User.SetWindowPos(NULL, ir.left + 2, ir.bottom + 5, cr.right -5, cr.bottom - 35, SWP_NOZORDER);
	m.Page.User.ShowWindow(SW_HIDE);

	//建立PageSetup視窗及畫面大小重新調整
	m.Page.Setup.Create(CPageSetup::IDD, &m_MainTab);
	m.Page.Setup.SetWindowPos(NULL, ir.left + 2, ir.bottom + 5, cr.right -5, cr.bottom - 35, SWP_NOZORDER);
	m.Page.Setup.ShowWindow(SW_HIDE);

	//建立PageEnginner視窗及畫面大小重新調整
	m.Page.Enginner.Create(CPageEngineer::IDD, &m_MainTab);
	m.Page.Enginner.SetWindowPos(NULL, ir.left + 2, ir.bottom + 5, cr.right -5, cr.bottom - 35, SWP_NOZORDER);
	m.Page.Enginner.ShowWindow(SW_HIDE);

	//建立PageDebug視窗及畫面大小重新調整
	m.Page.Debug.Create(CPageDebug::IDD, &m_MainTab);
	m.Page.Debug.SetWindowPos(NULL, ir.left + 2, ir.bottom + 5, cr.right -5, cr.bottom - 35, SWP_NOZORDER);
	m.Page.Debug.ShowWindow(SW_HIDE);
	
	// init button
	m_btnUser.SetIcon(IDI_LEVEL_USER);
	m_btnUser.SetAlign(CButtonST::ST_ALIGN_VERT);
	
	m_btnShutDown.SetIcon(IDI_SHUT_DWON);
	m_btnShutDown.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnShutDown.SetFlat(FALSE);

	// Init object
	m_pErrDlg = NULL;

	CDeerDlg *p = (CDeerDlg *) theApp.m_pMainWnd;
	// Insert User page
	m.Info.user = enLevelUser;
	p->SetUserPage(enLevelUser);

	//更新畫面時間模組啟動
	SetTimer(ID_TIME_SECOND, _TimeUpdate, NULL);

	//更新畫面的 UPH
	SetTimer(ID_TIME_UPH, 1000, NULL);

	//更新訊息
	SetTimer(ID_TIME_CHECK, 1000, NULL);

	//更新Torque狀態
	SetTimer(ID_TIME_REAL_TORQUE_STATUS, 250, NULL);

	//設定主畫面 版本資訊
	SetHandlerInfo();

	// 顯示 目前的 Machine ID
	SetMachineInfo();

	m_wndMainMsg.SetText("", 12, "Arial Black", DT_CENTER | DT_VCENTER);
	m_wndMainMsg.SetNewTextColor(ST_WHITE);

	//更新機台實體按鈕
	f.UpdateButtonState();

	theApp.m_tErr.CreateThread();
	// Note : Error Thread. Create for last.

	f.MotorServoOnAll();
	// Power On all Motor.

	f.DeleteOldFile(".\\Log\\*.txt", _MaxDaysLog );
	// Delete all log, avoid log file too larger.!

	f.DeleteOldFile(".\\Log\\*.csv", _MaxDaysLog );

#if _Demo
	// 單機 Demo 懶的按密碼
	m.Info.user = enLevelSuperUser;
//	m.Info.user = enLevelUser;
	p->SetUserPage(m.Info.user);
#endif
	// Note: if Demo mode, Open All page 

	f.ChangeLanguage(GetSafeHwnd());

	//
	f.DMsg.DMsgEnd();
	TRACE("# Main Dialog Complete\n");

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CDeerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CDeerDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CDeerDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}


static CMutex MutexInsertPage;
void CDeerDlg::SetUserPage(int level, int page)
{
	CSingleLock Lock(&MutexInsertPage);
	Lock.Lock();

	//清除TAB上所有ITEM
 	while(!m_MainTab.DeleteAllItems());

	//依據權限插入頁面
	switch(level)
	{
	case enLevelInitial:
		m_MainTab.InsertItem(TCIF_TEXT | TCIF_PARAM, 0, "Initial",
			-1, (LPARAM)&m.Page.Initial);
		m_MainTab.SetCurSel(page);//設定作用選擇視窗
		m.Page.Initial.SetTimeClock();
		break;
	case enLevelRun:
		m_MainTab.InsertItem(TCIF_TEXT | TCIF_PARAM, 0, "Run",
			-1, (LPARAM)&m.Page.Run);
		m_MainTab.SetCurSel(page);//設定作用選擇視窗
		break;
	case enLevelUser:
		m_MainTab.InsertItem(TCIF_TEXT | TCIF_PARAM, 0, "Run",
			-1, (LPARAM)&m.Page.Run);
		m_MainTab.InsertItem(TCIF_TEXT | TCIF_PARAM, 1, "User",
			-1, (LPARAM)&m.Page.User);
		m_MainTab.SetCurSel(page);//設定作用選擇視窗
		m_btnUser.SetIcon(IDI_LEVEL_USER);
		m_btnUser.SetWindowText("User");
		break;
	case enLevelSetup:
		m_MainTab.InsertItem(TCIF_TEXT | TCIF_PARAM, 0, "Run",
			-1, (LPARAM)&m.Page.Run);
		m_MainTab.InsertItem(TCIF_TEXT | TCIF_PARAM, 1, "User",
			-1, (LPARAM)&m.Page.User);
		m_MainTab.InsertItem(TCIF_TEXT | TCIF_PARAM, 2, "Setup",
			-1, (LPARAM)&m.Page.Setup);
		m_MainTab.SetCurSel(page);//設定作用選擇視窗
		m_btnUser.SetIcon(IDI_LEVEL_SETUP);
		m_btnUser.SetWindowText("Setup");
		break;
	case enLevelEngineer:
		m_MainTab.InsertItem(TCIF_TEXT | TCIF_PARAM, 0, "Run",
			-1, (LPARAM)&m.Page.Run);
		m_MainTab.InsertItem(TCIF_TEXT | TCIF_PARAM, 1, "User",
			-1, (LPARAM)&m.Page.User);
		m_MainTab.InsertItem(TCIF_TEXT | TCIF_PARAM, 2, "Setup",
			-1, (LPARAM)&m.Page.Setup);
		m_MainTab.InsertItem(TCIF_TEXT | TCIF_PARAM, 3, "Engineer",
			-1, (LPARAM)&m.Page.Enginner);
		m_MainTab.SetCurSel(page);//設定作用選擇視窗
		m_btnUser.SetIcon(IDI_LEVEL_ENGINEER);
		m_btnUser.SetWindowText("Engineer");
		break;
	case enLevelSuperUser:
		m_MainTab.InsertItem(TCIF_TEXT | TCIF_PARAM, 0, "Run",
			-1, (LPARAM)&m.Page.Run);
		m_MainTab.InsertItem(TCIF_TEXT | TCIF_PARAM, 1, "User",
			-1, (LPARAM)&m.Page.User);
		m_MainTab.InsertItem(TCIF_TEXT | TCIF_PARAM, 2, "Setup",
			-1, (LPARAM)&m.Page.Setup);
		m_MainTab.InsertItem(TCIF_TEXT | TCIF_PARAM, 3, "Engineer",
			-1, (LPARAM)&m.Page.Enginner);
		m_MainTab.InsertItem(TCIF_TEXT | TCIF_PARAM, 4, "Debug",
			-1, (LPARAM)&m.Page.Debug);
		m_MainTab.SetCurSel(page);//設定作用選擇視窗
		m_btnUser.SetIcon(IDI_LEVEL_ENGINEER);
		m_btnUser.SetWindowText("SuperUser");
		break;
	}
	//將目前畫面隱藏
	if(m.Page.m_Page.lParam != NULL)
	{
		((CDialog *)(m.Page.m_Page.lParam))->ShowWindow(SW_HIDE);
	}

	m.Page.m_Page.mask = TCIF_PARAM;
	m_MainTab.GetItem(m_MainTab.GetCurSel(), &m.Page.m_Page);
	//將目前作用選擇視窗顯示
	((CDialog *)(m.Page.m_Page.lParam))->ShowWindow(SW_SHOW);

	//////////////////////////////////////////////////////////////////////////
	// 為會解決 Double Page 問題所增加的程式碼(超過 5 個 Page 就重新 Load Page).
// 	if (m_MainTab.GetItemCount() > 5)
// 	{
// 		while(!m_MainTab.DeleteAllItems());
// 		SetUserPage(level, page);
// 	}	
	m_MainTab.RedrawWindow();

	Lock.Unlock();
}

void CDeerDlg::OnUser() 
{
	CDlgPassword dlg;
	dlg.DoModal();

	int page=0;
	switch(m.Info.user)
	{
	case enLevelEngineer:
		page=3;
		break;
	case enLevelSetup:
		page=2;
		break;
	case enLevelUser:
		page=1;
		break;
	}
	SetUserPage(m.Info.user, page);

	f.ChangeLanguage(GetSafeHwnd()); // 
}

void CDeerDlg::OnSelchangeViewTable(NMHDR* pNMHDR, LRESULT* pResult) 
{
	//套用CMember->Page成員
	((CDialog *)(m.Page.m_Page.lParam))->ShowWindow(SW_HIDE); //將目前點畫面隱藏
	m.Page.m_Page.mask = TCIF_PARAM;
	m_MainTab.GetItem(m_MainTab.GetCurSel(), &m.Page.m_Page); //將目前點選畫面參數儲存

	int iItem = m_MainTab.GetCurSel();
	m_MainTab.GetItem(iItem, &m.Page.m_Page );

	((CDialog *)(m.Page.m_Page.lParam))->ShowWindow(SW_SHOW); //將目前點選畫面顯示
	
	*pResult = 0;
}

//////////////////////////////////////////////////////////
// Show Error Dlg
LRESULT CDeerDlg::OnError(WPARAM p, LPARAM l)
{
	if(m_pErrDlg != NULL)
	{
		m_pErrDlg->Close();
		delete m_pErrDlg;
	}
	m_pErrDlg = new CDlgError((tagErrorMsg *)p);
	m_pErrDlg->Create(CDlgError::IDD);
	m_pErrDlg->ShowWindow(SW_SHOW);	

	return true;
}

//////////////////////////////////////////////////////////
// Close Error Dlg
LRESULT CDeerDlg::OnErrorClose(WPARAM p, LPARAM l)
{
	m_pErrDlg->DestroyWindow();
	m_pErrDlg = NULL;
	return true;
}

void CDeerDlg::OnErrorClear(void)
{
	if(m_pErrDlg != NULL)
	{
		// Each Thread Error Code
		m.Err.IO.Code = 0;
		m.Err.System.Code = 0;	
		m.Err.Arm.Code = 0;
		m.Err.Inserter.Code = 0;
		m.Err.Inspect.Code = 0;
		m.Err.Tester.Code = 0;

		// Info Status
		m.Info.bError = false;			// this line should be upper then next line
		m.Info.ErrorCode = 0;
		m.OutSet.TowerGreenOn = false;	// Close Buzzer output.
		m.Info.bError = false;			// Use F2 close buzzer.
		m.EnginnerCloseErr = true;
	}
}
//////////////////////////////////////////////////////////
// Accelerator
void CDeerDlg::OnVisualPanel()
{
	if(theApp.m_DlgVisualButton.GetSafeHwnd() != NULL)
	{
		theApp.m_DlgVisualButton.DestroyWindow(); // Destory it 
		delete theApp.m_DlgVisualButton; 
	}
	// We need create again. Because sometimes Error Dialog will cover it.!

	if(theApp.m_DlgVisualButton.GetSafeHwnd() == NULL)
		theApp.m_DlgVisualButton.Create(CDlgVisualButton::IDD);
	
	theApp.m_DlgVisualButton.ShowWindow(SW_SHOW);
}

void CDeerDlg::OnDebug()
{
	// 
	OnErrorClear();
}

void CDeerDlg::OnTab()
{
	// 如果使用者按下 Ctrl + Shift + Alt + F9 需要密碼, 避免被客戶按出
	CDlgPasswordNeed d(false, true);
	if(d.DoModal() != IDOK)
		return;
	//

	// Insert Super user to Debug .
	CDeerDlg *p = (CDeerDlg *) theApp.m_pMainWnd;
	m.Info.user = enLevelSuperUser;
	p->SetUserPage(enLevelSuperUser);	
}

void CDeerDlg::OnIOMontior()
{
	CDlgIOMontior dlg;
	dlg.DoModal();
}

void CDeerDlg::OnMotorMontior()
{
	CDlgMotorMontior dlg;
	dlg.DoModal();
}
void CDeerDlg::OnThreadMontior()
{
	CDlgThreadMontior dlg;
	dlg.DoModal();
}

void CDeerDlg::OnThread()
{
	if(theApp.m_DlgThreadMonitor.GetSafeHwnd() == NULL)
		theApp.m_DlgThreadMonitor.Create(CDlgThreadMontior::IDD);
	
	theApp.m_DlgThreadMonitor.ShowWindow(SW_SHOW);	
}

void CDeerDlg::OnButton()
{
	if(theApp.m_DlgButton.GetSafeHwnd() == NULL)
		theApp.m_DlgButton.Create(CDlgButton::IDD);
	
	theApp.m_DlgButton.ShowWindow(SW_SHOW);	
}

void CDeerDlg::OnDebugError()
{
	CDlgDebugError dlg;
	dlg.DoModal();
}

void CDeerDlg::OnSummaryReport()
{
	CDlgSummaryReport dlg;
	dlg.DoModal();
}

void CDeerDlg::OnJamRateReport()
{
	CDlgJamRateReportTool dlg;
	dlg.DoModal();	
}
void CDeerDlg::OnCCDList()
{
	CDlgSocketVisionCam dlg;
	dlg.DoModal();
}
void CDeerDlg::OnYieldMonitor()
{
	if(theApp.m_DlgYieldMonitor.GetSafeHwnd() == NULL)
		theApp.m_DlgYieldMonitor.Create(CDlgYieldMonitor::IDD);
	
	theApp.m_DlgYieldMonitor.ShowWindow(SW_SHOW);
}

void CDeerDlg::OnBinColor()
{
//	if(theApp.m_DlgBinColor.GetSafeHwnd() == NULL)
//		theApp.m_DlgBinColor.Create(CDlgBinColor::IDD);
//	
//	theApp.m_DlgBinColor.ShowWindow(SW_SHOW);

	CDlgBinColor dlg;
	dlg.DoModal();
}
void CDeerDlg::OnTrayStatus()
{
//	CDlgTrayStatus dlg;
//	dlg.DoModal();
	
	if(theApp.m_DlgTrayStatus.GetSafeHwnd() == NULL)
		theApp.m_DlgTrayStatus.Create(CDlgTrayStatus::IDD);
	
	theApp.m_DlgTrayStatus.ShowWindow(SW_SHOW);	

}
void CDeerDlg::OnAutoRetrySetting()
{
	CDlgAutoRetrySetting dlg;
	dlg.DoModal();
}
void CDeerDlg::OnHandlerStatusReport()
{
	CDlgHandlerStatusList dlg;
	dlg.DoModal();
}

void CDeerDlg::OnErrorList()
{
	CDlgDebugErrorList dlg;
	dlg.DoModal();
}
void CDeerDlg::OnDataUsing()
{

}
void CDeerDlg::OnTorqueCtrlTool()
{
	CDlgTorqueTool dlg;
	dlg.DoModal();
}
void CDeerDlg::OnTSRemainIC()
{
	CDlgTSRemainIC dlg;
	dlg.DoModal();
}
void CDeerDlg::OnWestCtrlTool()
{
	CDlgWestTool dlg;
	dlg.DoModal();
}
void CDeerDlg::OnCylinderLifeTimeTool()
{
	if(theApp.m_DlgCylinderLifeTimeTool.GetSafeHwnd() == NULL)
		theApp.m_DlgCylinderLifeTimeTool.Create(CDlgCylinderLifeTimeTool::IDD);
	
	theApp.m_DlgCylinderLifeTimeTool.ShowWindow(SW_SHOW);
}
void CDeerDlg::OnRemoteComm()
{
	if(theApp.m_DlgRemoteComm.GetSafeHwnd() == NULL)
		theApp.m_DlgRemoteComm.Create(CDlgRemoteCommunication::IDD);
	
	theApp.m_DlgRemoteComm.ShowWindow(SW_SHOW);
}
void CDeerDlg::OnCommunicationTool()
{
	if(theApp.m_DlgCommunicationInfo.GetSafeHwnd() == NULL)
		theApp.m_DlgCommunicationInfo.Create(CDlgCommunicationInfo::IDD);
	
	theApp.m_DlgCommunicationInfo.ShowWindow(SW_SHOW);
}
void CDeerDlg::OnUPHData()
{
	if(theApp.m_DlgUPHData.GetSafeHwnd() == NULL)
		theApp.m_DlgUPHData.Create(CDlgUPHTool::IDD);
	
	theApp.m_DlgUPHData.ShowWindow(SW_SHOW);
}

void CDeerDlg::OnLogEnable()
{
	CDlgLogEnable dlg;
	dlg.DoModal();
}


void CDeerDlg::OnReLoadFile()
{
	if(theApp.m_DlgReloadFile.GetSafeHwnd() == NULL)
		theApp.m_DlgReloadFile.Create(CDlgReLoadFile::IDD);
	
	theApp.m_DlgReloadFile.ShowWindow(SW_SHOW);
}

void CDeerDlg::OnMotorSimpleStatus()
{
	if(theApp.m_DlgMotorSimpleStatus.GetSafeHwnd() == NULL)
		theApp.m_DlgMotorSimpleStatus.Create(CDlgMotorSimpleStatus::IDD);
	
	theApp.m_DlgMotorSimpleStatus.ShowWindow(SW_SHOW);
}

void CDeerDlg::OnBinStatus()
{
	if(theApp.m_DlgBinStatus.GetSafeHwnd() == NULL)
		theApp.m_DlgBinStatus.Create(CDlgBinStatus::IDD);
	
	theApp.m_DlgBinStatus.ShowWindow(SW_SHOW);
}

void CDeerDlg::OnMotorStatus()
{
	CDlgMotorStatus dlg;
	dlg.DoModal();
}
LRESULT CDeerDlg::OnHandlerID(WPARAM p, LPARAM l)
{
	SetMachineInfo();

	return true; 
}
void CDeerDlg::OnShutDown() 
{
	// Delete need Password.
	CDlgPasswordNeed dlg(false, false);
	if(dlg.DoModal() != IDOK)
		return;

	f.MotorServoOffAll();
	f.m_Log.AddLogEvent( "Servo Off All Finish" );
	f.CloseAllOutput();
	f.m_Log.AddLogEvent( "Close All IO Finish" );
	Sleep( 100 );
	f.ShutDown();
	f.m_Log.AddLogEvent( "Shut Down Finish" );

//	PostMessage(WM_CLOSE, 0, 0 );
	CDialog::OnOK();
//	CDialog::OnCancel();
}
	
void CDeerDlg::SetMachineInfo()
{
	// 顯示 目前的 Machine ID
	m_csMachine = m.UI.MachineID;

	UpdateData(FALSE);
}

void CDeerDlg::SetHandlerInfo()
{
	// 取得本 exe 檔的路徑、名稱
	//
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
void CDeerDlg::UpdataTorqueStatus()
{
	if( m.Setting.m_bEnableTorqueStatus == 1 )
	{
		CString cs = _T("");
		cs.Format("--");
		int i = 0; // single site
		if(m.Info.iStatus == theApp.enUninitial)
		{
			cs.Format("--");
		}
		else
		{
			if( m.m_DriveMotorTorque.GetOpenOK() )
			{
				cs.Format("%5.2f%%/%5.2fkg", 
					m.m_DriveMotorTorque.GetTorque(i), m.m_DriveMotorTorque.GetForce(i));
			}
		}
		m.Page.Run.m_wndTorqueStatus.SetNewText(cs);
	}
}

// 1.0Af
// Remove this function and re-build new one
/*
void CDeerDlg::UpdataMainMsg()
{
	if( m.Setting.m_bEnableDoorSensor == 1 )
	{	
		m_wndMainMsg.SetNewBkColor(ST_RED);
		m_wndMainMsg.ShowWindow( SW_SHOW );
		m_wndMainMsg.SetWindowText(" DOOR SAFTY DISABLE.!!! "); // Show msg	
	}
	else
	{
		m_wndMainMsg.ShowWindow( SW_HIDE );
		m_wndMainMsg.SetWindowText("");
		// Clear msg
	}
}
*/
void CDeerDlg::UpdataMainMsg()
{
	m_bShowMainMsg = !m_bShowMainMsg;
	if( m.Setting.m_bEnableDoorSensor == 1 && m_bShowMainMsg )
	{	
		m_wndMainMsg.SetNewBkColor(ST_RED);
		m_wndMainMsg.ShowWindow( SW_SHOW );
		m_wndMainMsg.SetWindowText(" DOOR SAFTY DISABLE.!!! "); // Show msg	
	}
	else
	{
		m_wndMainMsg.ShowWindow( SW_HIDE );
		m_wndMainMsg.SetWindowText("");
		// Clear msg
	}
}

void CDeerDlg::UpdataButton()
{
	if(f.IsPause())
	{
		m_btnShutDown.ShowWindow(SW_SHOW);	// 系統暫停顯示關機
		m_btnUser.ShowWindow(SW_SHOW);
	}
	else
	{
		m_btnShutDown.ShowWindow(SW_HIDE);	// 系統暫停不顯示關機
		m_btnUser.ShowWindow(SW_HIDE);
	}
}
void CDeerDlg::UpdateJamRateCycleTime() 
{
	if( m.Setting.m_bShowHandlerStatus == 1 )
	{		
		if( m.Info.iStatus == theApp.enCycle || 
			m.Info.iStatus == theApp.enOneCycle ||
			m.Info.iStatus == theApp.enOverride )
		{
			m.m_JamRateInfo.m_lCycleTime++;
			f.SaveJamRateCycleTimeInfo();
		}
	}
}
void CDeerDlg::UpdateCycleTime() 
{
//	if( m.Info.iStatus == theApp.enCycle )	// 沒有計算到 OneCycle / Override 的秒數
	if( m.Info.iStatus == theApp.enCycle || 
		m.Info.iStatus == theApp.enOneCycle ||
		m.Info.iStatus == theApp.enOverride )
		m.UPH.CycleTime++; // one second by settimer.!
	// UPH debug.
}
void CDeerDlg::UpdateTime() 
{
//	COleDateTime t = COleDateTime::GetCurrentTime();
//	m_wndTime.SetWindowText(t.Format("%Y/%m/%d %H:%M:%S"));

	CTime t = CTime::GetCurrentTime();
	m_wndTime.SetWindowText(t.Format("%Y/%m/%d %H:%M:%S"));
}

void CDeerDlg::OnTimer(UINT nIDEvent) 
{
	switch(nIDEvent)
	{
	case ID_TIME_SECOND:
		UpdateTime();			// 更新畫面時間
		break;
	case ID_TIME_UPH:
		{
			UpdateCycleTime();
			UpdateJamRateCycleTime();
		}
		break;
	case ID_TIME_CHECK:
		{
			UpdataButton();
			UpdataMainMsg();
		}
		break;
	case ID_TIME_REAL_TORQUE_STATUS:
		{
			UpdataTorqueStatus();
		}
		break;
	}
	
	if(!m.Info.bRunning)
	{
		KillTimer(ID_TIME_SECOND);
		KillTimer(ID_TIME_UPH);		
	}
	// if ShutDown. We Kill Timer

	CDialog::OnTimer(nIDEvent);
}

BOOL CDeerDlg::PreTranslateMessage(MSG* pMsg) 
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

//	TRACE("%x\n", m.m_InterfaceTcp.m_tail.operator LPCTSTR());
	return CDialog::PreTranslateMessage(pMsg);
}

void CDeerDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	
	m.Page.Debug.DestroyWindow();
	m.Page.Enginner.DestroyWindow();
	m.Page.Initial.DestroyWindow();
	m.Page.Run.DestroyWindow();
	m.Page.Run.DestroyWindow();
	m.Page.Setup.DestroyWindow();
	m.Page.User.DestroyWindow();

	if( theApp.m_DlgVisualButton.GetSafeHwnd() != NULL )
		delete theApp.m_DlgVisualButton;
	// Delete Visual Button dialog

	if( theApp.m_DlgButton.GetSafeHwnd() != NULL )
		delete theApp.m_DlgButton;
	// Delete Button dialog

	if( theApp.m_DlgTrayStatus.GetSafeHwnd() != NULL )
		delete theApp.m_DlgTrayStatus;
	// Delete Tray Status dialog

	if( theApp.m_DlgMotorSimpleStatus.GetSafeHwnd() != NULL )
		delete theApp.m_DlgMotorSimpleStatus;
	// Delete Motor Simple Status dialog

	if( theApp.m_DlgReloadFile.GetSafeHwnd() != NULL )
		delete theApp.m_DlgReloadFile;
	// Delete Re-Load File dialog

	if( theApp.m_DlgBinStatus.GetSafeHwnd() != NULL )
		delete theApp.m_DlgBinStatus;
	// Delete Bin Status  dialog

	if( theApp.m_DlgBinColor.GetSafeHwnd() != NULL )
		delete theApp.m_DlgBinColor;
	// Delete Bin Color dialog

	if( theApp.m_DlgYieldMonitor.GetSafeHwnd() != NULL )
		delete theApp.m_DlgYieldMonitor;
	// Delete Yield Monitor	

	if( theApp.m_DlgUPHData.GetSafeHwnd() != NULL )
		delete theApp.m_DlgUPHData;
	// Delete UPH Data

	if( theApp.m_DlgCylinderLifeTimeTool.GetSafeHwnd() != NULL )
		delete theApp.m_DlgCylinderLifeTimeTool;
	// Delete Cylinder Life Time Tool

	if( theApp.m_DlgManualContact != NULL )
	{
		theApp.m_DlgManualContact = NULL;
		delete theApp.m_DlgManualContact;
	}
	// Delete Manual Contact 

	if( theApp.m_DlgManualContactRecover != NULL )
	{
		theApp.m_DlgManualContactRecover = NULL;
		delete theApp.m_DlgManualContactRecover;
	}
	// Delete Manual Contact Recover

	if( theApp.m_DlgTesting != NULL )
	{
		theApp.m_DlgTesting = NULL;
		delete theApp.m_DlgTesting;
	}
	// Delete Testing

	if( theApp.m_DlgSLTProtocol != NULL )
	{
		theApp.m_DlgSLTProtocol = NULL;
		delete theApp.m_DlgSLTProtocol;
	}
	// Delete SLT Protocol

	if( theApp.m_DlgRemoteControlCustom != NULL )
	{
		theApp.m_DlgRemoteControlCustom = NULL;
		delete theApp.m_DlgRemoteControlCustom;
	}
	// Delete Remote Control 

	if( theApp.m_DlgOutputYield.GetSafeHwnd() != NULL )
		delete theApp.m_DlgOutputYield;
	// Delete Output Yield Rate

	if( theApp.m_DlgTrayRepeatStatus.GetSafeHwnd() != NULL )
		delete theApp.m_DlgTrayRepeatStatus;
	// Delete Repeat Tray Status

	if( theApp.m_DlgCommunicationInfo.GetSafeHwnd() != NULL )
		delete theApp.m_DlgCommunicationInfo;
	// Delete Communication Information

	if( theApp.m_DlgRemoteComm.GetSafeHwnd() != NULL )
		delete theApp.m_DlgRemoteComm;
	// Delete Remote Comm

	if( theApp.m_DlgProgramStartInitial->GetSafeHwnd() != NULL )
	{
		theApp.m_DlgProgramStartInitial->DestroyWindow();
		delete theApp.m_DlgProgramStartInitial;
	}
	// Delete Program Start Initial
}	

void CDeerDlg::OnClose() 
{
	
	CDialog::OnClose();
}
