// PageRun.cpp : implementation file
//

#include "stdafx.h"
#include "Deer.h"
#include "DeerDlg.h"
#include "PageRun.h"

#include "ColorFontStatic.h"

// Dlg 
#include "DlgYieldControl.h"
#include "DlgIOMontior.h"
#include "DlgEvent.h"
#include "DlgLotInformation.h"
#include "DlgLotInformationDone.h"
#include "DlgMotorMontior.h"
#include "DlgClearCount.h"
#include "DlgTrayMap.h"
#include "DlgTrayMapRepeat.h"
#include "DlgOutputYield.h"
#include "DlgRepeatTrayTemp.h"
#include "DlgDeviceSetup.h"
#include "DlgRepeatTray.h"
#include "DlgContactCounter.h"
#include "DlgGrabShow.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPageRun dialog

CPageRun::CPageRun(CWnd* pParent /*=NULL*/)
	: CDialog(CPageRun::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPageRun)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	lOutputColor = 0;

	m_bRemoteFlash = false;
}

void CPageRun::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPageRun)	
	
	// Dynamic ICON
	DDX_Control(pDX, IDC_TS_VACC_OFF,				m_btnTestSiteVacc);
	DDX_Control(pDX, IDC_ROTATOR_STATUS,			m_btnRotatorStstus);
	DDX_Control(pDX, IDC_CCD,						m_btnCCD);
	DDX_Control(pDX, IDC_CCD_SOCKET,				m_btnCCDSocket);

	// Color Category
	DDX_Control(pDX, IDC_DATA,						m_listData);

	// Category
	DDX_Control(pDX, IDC_CATEGORY1,					m_wndCategory[0]);
//	DDX_Control(pDX, IDC_CATEGORY2,					m_wndCategory[1]);
//	DDX_Control(pDX, IDC_CATEGORY3,					m_wndCategory[2]);		
//	DDX_Control(pDX, IDC_CATEGORY4,					m_wndCategory[3]);		
	//
	// Output 
	DDX_Control(pDX, IDC_OUTPUT1,					m_wndOutput[0]);
//	DDX_Control(pDX, IDC_OUTPUT2,					m_wndOutput[1]);
//	DDX_Control(pDX, IDC_OUTPUT3,					m_wndOutput[2]);
//	DDX_Control(pDX, IDC_OUTPUT4,					m_wndOutput[3]);
	//
	// Count
	DDX_Control(pDX, IDC_OUTPUT_COUNT1,				m_wndOutputCount[0]);
//	DDX_Control(pDX, IDC_OUTPUT_COUNT2,				m_wndOutputCount[1]);
//	DDX_Control(pDX, IDC_OUTPUT_COUNT3,				m_wndOutputCount[2]);
//	DDX_Control(pDX, IDC_OUTPUT_COUNT4,				m_wndOutputCount[3]);
	//
	DDX_Control(pDX, IDC_WND_UPH,					m_wndUPH);
	DDX_Control(pDX, IDC_TOTAL,						m_wndTotal);
	DDX_Control(pDX, IDC_SITECOUNT,					m_wndSiteCount[0]);
	DDX_Control(pDX, IDC_STATICIDC_YIELD,			m_wndYield);
	//
	DDX_Control(pDX, IDC_H_STABLE_TIME,				m_wndHeaterStableTime);
	DDX_Control(pDX, IDC_H_SOAK_TIME,				m_wndHeaterSoakTine);
	DDX_Control(pDX, IDC_H_DIS_SOAK_TIME,			m_wndHeaterDisSoakTine);
	DDX_Control(pDX, IDC_H_SET_POINT,				m_wndHeaterSetPoint);
	DDX_Control(pDX, IDC_H_STABLE_REMAIN,			m_wndHeaterStableRemain);
	DDX_Control(pDX, IDC_STATIC_HEATER_GUP,			m_HeaterModuleGrp);
	//
	DDX_Control(pDX, IDC_RESULT_DISPLAY,			m_ContinueFail);
	//
	DDX_Control(pDX, IDC_TESTING,					m_wndTesting);
	DDX_Control(pDX, IDC_CONTACT_MODE,				m_btnContactMode);
	//
	DDX_Control(pDX, IDC_REPEAT_TRAY_STAT,			m_btnRepeatTrayInOutCtrl);
	DDX_Control(pDX, IDC_VISUAL_PANEL,				m_btnVisualPanel);

	//
	DDX_Control(pDX, IDC_LOT_INFORMATION,			m_btnLotInformation);
	DDX_Control(pDX, IDC_LOT_DONE,					m_btnLotDone);
	DDX_Control(pDX, IDC_TRAY_MAP,					m_btnTrayMap);
	DDX_Control(pDX, IDC_CLEAR_COUNT,				m_btnClearCount);
	//
	DDX_Control(pDX, IDC_IO_MONTIOR,				m_btnIOMonitor);
	DDX_Control(pDX, IDC_YIELD_CTRL,				m_btnYieldCTRL);
	DDX_Control(pDX, IDC_EVENT_LOG,					m_btnEvent);
	//
	DDX_Control(pDX, IDC_CONTINUE_FAIL,				m_wndContinueFail);
	DDX_Control(pDX, IDC_YIELD_LIMIT,				m_wndYieldLimit);
	DDX_Control(pDX, IDC_RETEST_TIMES,				m_wndRetestTimes);
	DDX_Control(pDX, IDC_FILE,						m_wndFile);
	DDX_Control(pDX, IDC_RUN_STATUS,				m_wndRunStatus);
	DDX_Control(pDX, IDC_RUN_MODE,					m_wndRunMode);
	//
	DDX_Control(pDX, IDC_TE_TS_TEMP,				m_wndTempTS);
	//
	DDX_Control(pDX, IDC_LED_RETEST,				m_ledRetest);
	DDX_Control(pDX, IDC_LED_CONTINUE_FAIL,			m_ledContinueFail);
	DDX_Control(pDX, IDC_LED_YIELD_CONTROL,			m_ledYieldControl);
	// Heater 
	DDX_Control(pDX, IDC_LED_HEATER,				m_ledHeater);
	DDX_Control(pDX, IDC_LED_STABLE,				m_ledHeaterStable);
	//
	DDX_Control(pDX, IDC_TEST_TIME,					m_wndTestTime);
	// Test Site Contact Counter
	DDX_Control(pDX, IDC_W_TS_COUNTER,				m_wndContactCounterr);
	// Auto Skip
	DDX_Control(pDX, IDC_TRAY_AUTO_SKIP,			m_btnAutoSkip);	
	// Torque Mode
	DDX_Control(pDX, IDC_TS_TORQUE_STATUS,			m_wndTorqueStatus);	
	// Repeat Tray Mode
	DDX_Control(pDX, IDC_REPEAT_MSG,				m_wndRepeatTrayStatus);
	// Jam rate report
	DDX_Control(pDX, IDC_HANDLER_STATUS,			m_wndHandlerStatus);
	//
	DDX_Control(pDX, IDC_NOW_TEMP,					m_wndNowTemperature);
	DDX_Control(pDX, IDC_REPEAT_MAT_MSG,			m_wndNowMoation);
	// Current Status
	DDX_Control(pDX, IDC_W_STATUS,					m_wndCurrentRepeatTrayStatus);

	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CPageRun, CDialog)
	//{{AFX_MSG_MAP(CPageRun)
	ON_WM_SHOWWINDOW()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_TS_VACC_OFF,			OnTestSiteVaccOff)
	ON_BN_CLICKED(IDC_TRAY_AUTO_SKIP,		OnTrayAutoSkip)
	ON_BN_CLICKED(IDC_YIELD_CTRL,			OnYieldCtrl)
	ON_BN_CLICKED(IDC_IO_MONTIOR,			OnIoMontior)
	ON_BN_CLICKED(IDC_EVENT_LOG,			OnEventLog)
	ON_BN_CLICKED(IDC_CLEAR_COUNT,			OnClearCount)
	ON_BN_CLICKED(IDC_TRAY_MAP,				OnTrayMap)
	ON_BN_CLICKED(IDC_LOT_DONE,				OnLotDone)
	ON_BN_CLICKED(IDC_LOT_INFORMATION,		OnLotInformation)
	ON_BN_CLICKED(IDC_CONTACT_MODE,			OnContactMode)
	ON_BN_CLICKED(IDC_REPEAT_TRAY_STAT,		OnRepeatTrayInOutCtrl)
	ON_BN_CLICKED(IDC_VISUAL_PANEL,			OnVisualPanel)
	ON_BN_CLICKED(IDC_CCD,					OnCCD)
	ON_BN_CLICKED(IDC_OUTPUT_COUNT1,		OnOutputYield)
	ON_BN_CLICKED(IDC_DATA,					OnOutputYield)
	ON_BN_CLICKED(IDC_OUTPUT1,				OnOutputYield)
	ON_BN_CLICKED(IDC_RUN_MODE,				OnRunMode)
	ON_BN_CLICKED(IDC_NOW_TEMP,				OnRepeatTrayTemper)
	ON_BN_CLICKED(IDC_FILE,					OnFileDeviceSetup)
	ON_BN_CLICKED(IDC_REPEAT_MSG,			OnFileRepeatTraySetup)
	ON_BN_CLICKED(IDC_W_TS_COUNTER,			OnTsCounter)

	ON_NOTIFY(LVN_GETDISPINFO, IDC_DATA,	OnGetdispinfoData)
	ON_MESSAGE(WM_HEATER_ON,				OnHeaterOn )
	ON_MESSAGE(WM_UPDATA_TS_COUNTER,		OnUpdataTsCounter)
	
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPageRun message handlers

BOOL CPageRun::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	//
	InitColorCatoregyFormat();

	//
	InitUI();

	//
	InitTips();

	//
	InitStatus();

	//
	InitOutput();

	//
	InitOutputColor();

	// 設定工單資訊
	UpdateSetting();
	UpdateSiteCounter();

	//
	InitYield();

	// Display UI setting
	UpdateSetting();

	//
	UpdataNowTemperature();

	// Set Timer for get run page status
	// 1: Pre-heater IO status. Run Page led inducation.
	SetTimer(ID_TIME_STATUS, _Status_Timer, NULL);
	SetTimer(ID_TIME_TS_TEMPERATURE, _Status_Timer, NULL);
	SetTimer(ID_TIME_TEMP_STABLE, 250, NULL);
	SetTimer(ID_TIME_TEMP_SOAK, 250, NULL);
	SetTimer(ID_TIME_PAGE_OUTPUT_YIELD, 700, NULL);
	SetTimer(ID_TIME_JAM_RATE_INFO, 500, NULL);
	SetTimer(ID_TIME_NOW_TEMPERATURE, 2500, NULL);
	SetTimer(ID_TIME_REMOTE_STATUS, 1500, NULL);


	// Note: We need set the Text by myself
	SetWindowText("Run");

	//
	f.ChangeLanguage(GetSafeHwnd());

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
void CPageRun::InitOutputColor()
{
	COLORREF color = RGB( m.m_RunPageOutputColor.R, m.m_RunPageOutputColor.G, m.m_RunPageOutputColor.B );
	lOutputColor = color;
	m_wndOutput[0].SetNewBkColor( lOutputColor );
}
void CPageRun::InitYield()
{
	// 顯示良率數字 / 給預設值用
	CString csYield;	
	if( m.Counter.SitePass == 0 )
	{
		csYield.Format("0.0%% / %d", m.Counter.SiteTotal);
	}else
	{
		csYield.Format("%3.1f%% / %d", 	m.Counter.SitePass * 100. / m.Counter.SiteTotal,
			m.Counter.SiteTotal);
	}
	m.Page.Run.m_wndYield.SetWindowText( csYield );
}
void CPageRun::InitOutput()
{
	int i = 0;
	CString cs;
	for(i=0; i<_Output_Stack_No; i++)
	{		
		{
			cs.Format("Output %d", i+1);
			m_wndOutput[i].SetText(cs, 12, "Arial Black", DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			m_wndOutputCount[i].SetText("", 12, "Arial", DT_CENTER | DT_VCENTER | DT_SINGLELINE);	
			m_wndOutputCount[i].SetNewBkColor(ST_WHITE);
		}
	}
	// Service Request, Auto 2 and Fix 2
}
void CPageRun::InitStatus()
{
	// 設定 Contact 初始的顯示狀態.
	if( m.YieldSetting.bDropMode == 1 )
	{
		m_btnContactMode.SetIcon(IDI_DROP_MODE);		// Note : If value == 1. It will enable IC Drop Mode.		
	}
	else 
	{
		m_btnContactMode.SetIcon(IDI_DIRECT_CONTACT);	// Note : If value == 0. It will let IC direct contact to socket.
	}

	// 設定 AutoSkip 顯示狀態.
	if( m.TraySkip.AutoSkip == 0 )
		m_btnAutoSkip.SetIcon(IDI_TRAY_AUTO_SKIP);
	else
		m_btnAutoSkip.SetIcon(IDI_TRAY_NOT_AUTO_SKIP);
}
void CPageRun::UpdataICONButton()
{
	//////////////////////////////////////////////////////////////////////
	// 重設介面
	RECT rt;
	::GetWindowRect(::GetDlgItem(m_hWnd, IDC_IO_MONTIOR), &rt);
	::MapWindowPoints(NULL, m_hWnd, (LPPOINT)&rt, 2);	
	
	RECT rtW[_ICON_Count];
	bool rtUse[_ICON_Count];
	for(int i=0;i<_ICON_Count;i++)
		rtUse[i] = false;

	//
	for(i=0;i<_ICON_Count;i++)
		rtW[i] = rt;
	
	//
	for(i=0;i<_ICON_Count;i++)
	{
		rtW[i].left		= ( rt.right - rt.left ) + rt.left	+ ( 50 * i ) + 10;
		rtW[i].right	= ( rt.right - rt.left ) + rt.right	+ ( 50 * i ) + 10;
	}

	// 判斷是否使用 CCD Pin1
	if( m.Setting.m_bEnableCCDPin1 == 1 )
	{
		m_btnCCD.ShowWindow( TRUE );
		for(i=0;i<_ICON_Count;i++)
		{
			if( !rtUse[i] )
			{
				rtUse[i] = true;
				m_btnCCD.MoveWindow(&rtW[i]);
				break;
			}
		}
	}
	else
	{
		m_btnCCD.ShowWindow( FALSE );
	}

	// 判斷是否使用 CCD Socket 
	if( m.Setting.m_bEnableCCDSocket == 1 )
	{
		m_btnCCDSocket.ShowWindow( TRUE );
		for(i=0;i<_ICON_Count;i++)
		{
			if( !rtUse[i] )
			{
				rtUse[i] = true;
				m_btnCCDSocket.MoveWindow(&rtW[i]);
				break;
			}
		}
	}
	else
	{
		m_btnCCDSocket.ShowWindow( FALSE );
	}

	// 判斷是否使用 Rotator
	if( m.Setting.m_bRotatoUse == 1 )
	{
		m_btnRotatorStstus.ShowWindow( TRUE );
		for(i=0;i<_ICON_Count;i++)
		{
			if( !rtUse[i] )
			{
				rtUse[i] = true;
				m_btnRotatorStstus.MoveWindow(&rtW[i]);
				break;
			}
		}
	}
	else
	{
		m_btnRotatorStstus.ShowWindow( FALSE );
	}

	// 判斷是否顯示 Contact Mode
	if( 1 )
	{
		m_btnContactMode.ShowWindow( TRUE );
		for(i=0;i<_ICON_Count;i++)
		{
			if( !rtUse[i] )
			{
				rtUse[i] = true;
				m_btnContactMode.MoveWindow(&rtW[i]);
				break;
			}
		}
	}
	else
	{
		m_btnContactMode.ShowWindow( FALSE );
	}

	// 判斷是否顯示 Repeat Tray Stat
	if( m.m_RepeatTrayCtrl.m_iRepeatTrayMode == theApp.enRepeatTrayInOutCtrl  )
	{
		m_btnRepeatTrayInOutCtrl.ShowWindow( TRUE );
		for(i=0;i<_ICON_Count;i++)
		{
			if( !rtUse[i] )
			{
				rtUse[i] = true;
				m_btnRepeatTrayInOutCtrl.MoveWindow(&rtW[i]);
				break;
			}
		}
	}
	else
	{
		m_btnRepeatTrayInOutCtrl.ShowWindow( FALSE );
	}

	// 判斷是否顯示 Visual Panel
	if( 1 )
	{
		m_btnVisualPanel.ShowWindow( TRUE );
		for(i=0;i<_ICON_Count;i++)
		{
			if( !rtUse[i] )
			{
				rtUse[i] = true;
				m_btnVisualPanel.MoveWindow(&rtW[i]);
				break;
			}
		}
	}
	else
	{
		m_btnVisualPanel.ShowWindow( FALSE );
	}

	// 判斷是否顯示 Ts Vacc OFF
#ifdef _Demo
	if(1)
	{
		m_btnTestSiteVacc.ShowWindow( TRUE );
		for(i=0;i<_ICON_Count;i++)
		{
			if( !rtUse[i] )
			{
				rtUse[i] = true;
				m_btnTestSiteVacc.MoveWindow(&rtW[i]);
				break;
			}
		}
	}
	else
	{
		m_btnTestSiteVacc.ShowWindow( FALSE );
	}
#endif
}
void CPageRun::InitColorCatoregyFormat()
{
	LONG lStyle;
	lStyle = GetWindowLong(m_listData.m_hWnd, GWL_STYLE);
	lStyle &= ~LVS_TYPEMASK; 
	lStyle |= LVS_REPORT; 
	SetWindowLong(m_listData.m_hWnd, GWL_STYLE, lStyle);
	
	DWORD dwStyle = m_listData.GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT;
	dwStyle |= LVS_EX_GRIDLINES;
//	dwStyle |= LVS_EX_CHECKBOXES;
	m_listData.SetExtendedStyle(dwStyle); 

	// 設定顯示參數
	COLORREF crBkColor = ::GetSysColor(COLOR_3DFACE);
	m_listData.SetTextColor(ST_BLACK);

	// 清掉全部的 Item
	if(!m_listData.DeleteAllItems())
		return;

	// 先清掉全部的資料
	theApp.DoWaitCursor(1);
	while(m_listData.DeleteColumn(0));
	
	// 新增 標頭
	{
		m_listData.InsertColumn(0, "Item");  
		m_listData.InsertColumn(1, "S/W Number");
		m_listData.InsertColumn(2, "Code");   
		m_listData.InsertColumn(3, "P/F");
		m_listData.InsertColumn(4, "Rate(%)");
	}

	// 設定預設寬度
	m_listData.SetColumnWidth(0, 50);
	m_listData.SetColumnWidth(1, 100);
	m_listData.SetColumnWidth(2, 150);
	m_listData.SetColumnWidth(3, 100);
	m_listData.SetColumnWidth(4, 100);

	theApp.DoWaitCursor(0);

}
void CPageRun::OnGetdispinfoData(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LV_DISPINFO* pDispInfo = (LV_DISPINFO*)pNMHDR;
	LV_ITEM* pItem= &(pDispInfo)->item;
	tagCatoregyRunPageItem rLabel = m_Source.ElementAt(pItem->iItem);

	if (pItem->mask & LVIF_TEXT) //valid text buffer?
	{
		// then display the appropriate column
		switch(pItem->iSubItem)
		{
		case 0:
			sprintf(pItem->pszText, "%d",	rLabel.item );			
			break;
		case 1:
			sprintf(pItem->pszText, "%s",	rLabel.software );		
			break;
		case 2:
			sprintf(pItem->pszText, "%s",	rLabel.code );
			break;
		case 3:
			sprintf(pItem->pszText, "%d",	rLabel.pf );
			break;
		case 4:
			{
				double dRate = 0.0;
				dRate = GetOutputYieldValue( rLabel.code );
				sprintf(pItem->pszText, "%5.2f",	dRate );
			}
			break;
		default:
			ASSERT(0);
			break;
		}
	}	
	*pResult = 0;
}
void CPageRun::InitTips()
{
	// Tips 
	// Init Tips
	m_ToolTip.Create(this);
	m_ToolTip.SetMaxTipWidth(800);
	m_ToolTip.SetDelayTime( TTDT_AUTOPOP, 10000 );
	m_ToolTip.SetDelayTime( TTDT_INITIAL, 25 );
	m_ToolTip.EnableToolTips(true);

	// Function information
	m_ToolTip.AddTool( GetDlgItem(IDC_TRAY_MAP),				_T("Tray Map") );
	m_ToolTip.AddTool( GetDlgItem(IDC_LOT_INFORMATION),			_T("New Lot / Lot Information") );
	m_ToolTip.AddTool( GetDlgItem(IDC_LOT_DONE),				_T("Lot Done") );
	m_ToolTip.AddTool( GetDlgItem(IDC_YIELD_CTRL),				_T("Yield Control") );
	m_ToolTip.AddTool( GetDlgItem(IDC_IO_MONTIOR),				_T("IO Monitor") );
	m_ToolTip.AddTool( GetDlgItem(IDC_EVENT_LOG),				_T("Event Log") );
	m_ToolTip.AddTool( GetDlgItem(IDC_CLEAR_COUNT),				_T("Clear Count") );
	m_ToolTip.AddTool( GetDlgItem(IDC_CONTACT_MODE),			_T("Contact Mode") );	
	m_ToolTip.AddTool( GetDlgItem(IDC_CCD),						_T("CCD Pin1 Detect") );	
	m_ToolTip.AddTool( GetDlgItem(IDC_CCD_SOCKET),				_T("CCD Socket") );	
	m_ToolTip.AddTool( GetDlgItem(IDC_REPEAT_TRAY_STAT),		_T("Repeat Tray") );	

	// handler status
	m_ToolTip.AddTool( GetDlgItem(IDC_ROTATOR_STATUS),			_T("Rotator Status") );
	m_ToolTip.AddTool( GetDlgItem(IDC_RUN_STATUS),				_T("This handler status.") ); 
	m_ToolTip.AddTool( GetDlgItem(IDC_RUN_MODE),				_T("This handler mode (OnLine / OffLine / Demo).") ); 	
	m_ToolTip.AddTool( GetDlgItem(IDC_TRAY_AUTO_SKIP),			_T("Auto Skip Control Status") );

	// testing information
	m_ToolTip.AddTool( GetDlgItem(IDC_TESTING),					_T("Testing (Bin Value / Category)") );
	m_ToolTip.AddTool( GetDlgItem(IDC_TEST_TIME),				_T("Testing (Test Times)") );
	m_ToolTip.AddTool( GetDlgItem(IDC_STATICIDC_YIELD),			_T("Testing (Yield rate)") );
	m_ToolTip.AddTool( GetDlgItem(IDC_SITECOUNT),				_T("Testing (Site Counter )") );

	// heater Information
	m_ToolTip.AddTool( GetDlgItem(IDC_TE_TS_TEMP),				_T("Test Site Temperature") );

	// yield control information
	m_ToolTip.AddTool( GetDlgItem(IDC_LED_YIELD_CONTROL),		_T("Yield Control\r\nif yield lower the this value, It will alarm") );
	m_ToolTip.AddTool( GetDlgItem(IDC_LED_CONTINUE_FAIL),		_T("Yield Control\r\nif fail continue, the counter over this value, It will alarm") );
	m_ToolTip.AddTool( GetDlgItem(IDC_LED_RETEST),				_T("Yield Control\r\nif fail, It will auto retest. this value is times") );

	// test file setting
	m_ToolTip.AddTool( GetDlgItem(IDC_FILE),					_T("Test file setting\r\nTrayFile\r\nInterface") );

	// counter
	m_ToolTip.AddTool( GetDlgItem(IDC_TOTAL),					_T("Total test counter") );
	m_ToolTip.AddTool( GetDlgItem(IDC_WND_UPH),					_T("UPH\r\nUPH, It is per hour output ic counter\r\nCyc, It is for each avg cycle times") );
	
	// remote
	m_ToolTip.AddTool( GetDlgItem(IDC_VISUAL_PANEL),			_T("Visual Panel\r\nVisual, It is for remote panel") );

}
void CPageRun::InitUI()
{
	/////////////////////////////////////////////////////////////////////////////
	m_btnYieldCTRL.SetIcon(IDI_FLOW_CHAR);
	m_btnYieldCTRL.SetAlign(CButtonST::ST_ALIGN_VERT);

	m_btnIOMonitor.SetIcon(IDI_IO);
	m_btnIOMonitor.SetAlign(CButtonST::ST_ALIGN_VERT);

	m_btnEvent.SetIcon(IDI_EVENT_LOG);
	m_btnEvent.SetAlign(CButtonST::ST_ALIGN_VERT);

	m_btnTrayMap.SetIcon(IDI_TRAY_MAP);
	m_btnTrayMap.SetAlign(CButtonST::ST_ALIGN_VERT);
	
	m_btnLotDone.SetIcon(IDI_LOT_DONE);;
	m_btnLotDone.SetAlign(CButtonST::ST_ALIGN_VERT);

	m_btnLotInformation.SetIcon(IDI_CHECK_BOOK);
	m_btnLotInformation.SetAlign(CButtonST::ST_ALIGN_VERT);

	m_btnClearCount.SetIcon(IDI_CLEAR_COUNT);
	m_btnClearCount.SetAlign(CButtonST::ST_ALIGN_VERT);

	m_btnCCD.SetIcon(IDI_RT_IMAGE);
	m_btnCCDSocket.SetIcon(IDI_CCD_SOCKET_SETUP);

	m_btnRepeatTrayInOutCtrl.SetIcon(IDI_REPEAT_TRAY_STATUS);

	m_btnVisualPanel.SetIcon(IDI_VISUAL_PANEL1);

	//
	m_wndRunMode.SetText("", 14, "Arial Black", DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	m_wndRunStatus.SetText("", 12, "Arial Black", DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	m_wndFile.SetText("", 10, "Arial Black", DT_LEFT);

	// Torque Status
	m_wndTorqueStatus.SetText("", 10, "Arial",  DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	m_wndTorqueStatus.SetNewBkColor(ST_WHITE);

	// Repeat Tray Information
	m_wndRepeatTrayStatus.SetText("--", 10, "Arial Black",  DT_LEFT | DT_VCENTER);
	m_wndRepeatTrayStatus.SetNewBkColor(ST_WHITE);

	// Handler Status Information
	m_wndHandlerStatus.SetText("--", 10, "Arial Black",  DT_LEFT | DT_VCENTER );
	m_wndHandlerStatus.SetNewBkColor(ST_WHITE);

	// Now Temperature
	m_wndNowTemperature.SetText("--", 12, "Arial Black",  DT_CENTER | DT_VCENTER | DT_SINGLELINE );
	m_wndNowTemperature.SetNewBkColor(ST_WHITE);

	// Now Moation
	m_wndNowMoation.SetText("--", 10, "Arial Black",  DT_CENTER | DT_VCENTER | DT_SINGLELINE );
	m_wndNowMoation.SetNewBkColor(ST_WHITE);

	// Now Moation
	m_wndCurrentRepeatTrayStatus.SetText("--", 10, "Arial Black",  DT_CENTER | DT_VCENTER | DT_SINGLELINE );
	m_wndCurrentRepeatTrayStatus.SetNewBkColor(ST_WHITE);

	//
	m_wndTempTS.SetText("", 10, "Arial Black", DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	// 設定 LED 初始狀態
	m_ledYieldControl.SetLed(CLed::LED_COLOR_GREEN);
	m_ledContinueFail.SetLed(CLed::LED_COLOR_GREEN);
	m_ledRetest.SetLed(CLed::LED_COLOR_GREEN);

	//
	m_ledHeater.SetLed(CLed::LED_COLOR_RED);
	m_ledHeaterStable.SetLed(CLed::LED_COLOR_RED);

	/////////////////////////////////////////////////////////////////////////////
	// 設定工單資訊的格式
	m_wndTotal.SetText("", 14, "Arial Black", DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	m_wndTotal.SetNewBkColor(ST_WHITE);
	m_wndUPH.SetText("", 10, "Arial Black", DT_CENTER | DT_VCENTER);
	m_wndUPH.SetNewBkColor(ST_MAGENTA);
	m_wndUPH.SetNewText("UPH = 0\nCyc = 0");

	// 設定 Site 的初始資訊
	m_wndTesting.SetText("--", 10, "Arial Black", DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	m_ContinueFail.SetShowText(FALSE);
	m_ContinueFail.SetLimitation(m.YieldSetting.iFailCount);
	m_ContinueFail.SetBkColour(ST_WHITE);
	m_wndTestTime.SetText("Test 0.0s", 8, "Arial", DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	LOGFONT lf;
	memset(&lf, 0, sizeof(LOGFONT));       // clear out structure.
	lf.lfHeight = 80;                     
	strcpy(lf.lfFaceName, "Arial");
	CClientDC dc(this);
	CFont font;
	VERIFY(font.CreatePointFontIndirect(&lf, &dc));  
	m_wndTestTime.SetFont( &font, FALSE );
	m_wndTestTime.SetNewBkColor(ST_LIGHTYELLOW);
	m_wndYield.SetText("--", 9, "Arial", DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	for(int i=0;i<_Site_Count;i++)
		m_wndSiteCount[i].SetText("--", 9, "Arial Black", DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	/////////////////////////////////////////////////////////////////////////////
}
LRESULT CPageRun::OnUpdataTsCounter(WPARAM p, LPARAM l)
{	
	if( m.Setting.m_bShowContactCounter == 1 )
	{		
		CString cs = _T("");
		cs.Format("Contact Counter: %d", m.m_ContactCounterValue.lContactConter );
		m_wndContactCounterr.SetWindowText( cs );
	}	

	return true;
}
LRESULT CPageRun::OnHeaterOn(WPARAM p, LPARAM l)
{
	CString csHeaterOn = _T("");
	csHeaterOn.Format("Heating");
//	m_wndHeaterStableRemain.SetWindowText( csHeaterOn );
	return true;
}
void CPageRun::OnTsCounter() 
{
	if( m.Info.user > enLevelUser && f.IsPause() )
	{
		CDlgContactCounter dlg(true);
		dlg.DoModal();
	}
}
void CPageRun::OnFileRepeatTraySetup() 
{
	if( m.LotInfo.LotInfoIsLotStart == 0 )
	{
		CDlgRepeatTray dlg;
		dlg.DoModal();
	}
}
void CPageRun::OnFileDeviceSetup() 
{
	CString csTrayFile = _T("");
	csTrayFile = m.UI.FileMain;
//	if( csTrayFile == "" && m.LotInfo.LotInfoIsLotStart == 0 )
	if( m.LotInfo.LotInfoIsLotStart == 0 )
	{		
		CDlgDeviceSetup dlg;
		dlg.DoModal();
	}
}
void CPageRun::OnRepeatTrayTemper() 
{
	CDlgRepeatTrayTemp dlg;
	dlg.DoModal();
}
void CPageRun::OnRunMode() 
{
	CString csTrayFile = _T("");
	csTrayFile = m.UI.FileMain;
	if( csTrayFile != "" && m.LotInfo.LotInfoIsLotStart == 0 )
	{
		// 有選 TrayFile 但是沒有建立新的 Lot
		if( m.Site.iRunMode == theApp.enOnLine )
			m.Site.iRunMode = theApp.enOffLine;
		else if( m.Site.iRunMode == theApp.enOffLine )
			m.Site.iRunMode = theApp.enDemo;
		else if( m.Site.iRunMode == theApp.enDemo )
			m.Site.iRunMode = theApp.enOnLine;
		else
			; // Nerver be here

		f.SaveSiteSettingRunMode();
		UpdateHandlerRunModeStatusInformation();
	}
}
/////////////////////////////////////////////////////////////////////////
// Run Page button function
void CPageRun::OnOutputYield() 
{
	CDlgOutputYield dlg;
	dlg.DoModal();

#if 0
	if(theApp.m_DlgOutputYield.GetSafeHwnd() == NULL)
		theApp.m_DlgOutputYield.Create(CDlgOutputYield::IDD);
	
	theApp.m_DlgOutputYield.ShowWindow(SW_SHOW);
#endif
}
void CPageRun::OnVisualPanel() 
{
	if(theApp.m_DlgVisualButton.GetSafeHwnd() == NULL)
		theApp.m_DlgVisualButton.Create(CDlgVisualButton::IDD);
	
	theApp.m_DlgVisualButton.ShowWindow(SW_SHOW);
}
void CPageRun::OnRepeatTrayInOutCtrl() 
{
	if(theApp.m_DlgTrayRepeatStatus.GetSafeHwnd() == NULL)
		theApp.m_DlgTrayRepeatStatus.Create(CDlgTrayRepeatStatus::IDD);
	
	theApp.m_DlgTrayRepeatStatus.ShowWindow(SW_SHOW);
}
void CPageRun::OnContactMode() 
{
	// This button only for display Drop Mode
	// DROP MODE Or CONTACT MODE. So. When User press it. 
	// We do not do anything.!
}
void CPageRun::OnTestSiteVaccOff() 
{
	if( m.TraySkip.TestSiteVacc == 1 )
		m.TraySkip.TestSiteVacc = 0;
	else
		m.TraySkip.TestSiteVacc = 1;

	//
	if( m.TraySkip.TestSiteVacc == 1 )
		m_btnTestSiteVacc.SetIcon(IDI_SOCKET_VACC);
	else
		m_btnTestSiteVacc.SetIcon(IDI_SOCKET_NO_VACC);

	f.SaveSetting();

	// Note: m.TraySkip.TestSiteVacc == 0 表示會 Direct Contact, 要先關掉 
	// 如果 m.TraySkip.TestSiteVacc == 1 表示會 Driect Contact 要持續開 Vacc
}
void CPageRun::OnTrayAutoSkip() 
{
	if( m.TraySkip.AutoSkip == 0 )
	{		
		f.m_Log.AddEvent(enCodeUserPageTrayNoSkip);	// Add Event
		m.TraySkip.AutoSkip = 1;
		// Ebable the function of Input Stack Auto Skip
	}
	else
	{
		f.m_Log.AddEvent(enCodeUserPageTrayAutoSkip);	// Add Event		
		m.TraySkip.AutoSkip = 0;
		// Disable the function of Input Stack Auto Skip
	}
	// Note: Reset the setting

	if( m.TraySkip.AutoSkip == 0 )
		m_btnAutoSkip.SetIcon(IDI_TRAY_AUTO_SKIP);
	else
		m_btnAutoSkip.SetIcon(IDI_TRAY_NOT_AUTO_SKIP);
	// Note: Change the icon image

	f.SaveSetting();
	// Note: m.TraySkip.AutoSkip == 0 表示會 Auto Skip, 
	// 如果 m.TraySkip.AutoSkip == 1 表示會 Alarm
}

void CPageRun::OnCCD()
{

}

void CPageRun::OnYieldCtrl()
{
	f.m_Log.AddEvent(enCodeRunPageYieldControl);	// Add Event

	CDlgYieldControl dlg;
	dlg.DoModal();
}
void CPageRun::OnIoMontior()
{
	f.m_Log.AddEvent(enCodeRunPageIOMonitor);	// Add Event

	CDlgIOMontior dlg(true);
	dlg.DoModal();
	// User Page only show IO setting status
	// User can not modify function
}
void CPageRun::OnEventLog()
{
	f.m_Log.AddEvent(enCodeRunPageEventLog);	// Add Event

	CDlgEvent dlg;
	dlg.DoModal();
}

void CPageRun::OnClearCount()
{
	f.m_Log.AddEvent(enCodeRunPageClearCount);	// Add Event

	CDlgClearCount dlg;
	dlg.DoModal();
}

void CPageRun::OnTrayMap()
{
	f.m_Log.AddEvent(enCodeRunPageTrayMap);	// Add Event

// 1.0An
	// Remove this and re-build new one blow
	// CDlgTrayMap dlg;
	// dlg.DoModal();

// 1.0An
	if( m.m_RepeatTrayCtrl.m_iRepeatTrayMode == theApp.enRepeatTrayInOutCtrl )
	{
		// Repeat Tray Mode
		CDlgTrayMapRepeat dlg;
		dlg.DoModal();
	}
	else if( m.m_RepeatTrayCtrl.m_iRepeatTrayMode == theApp.enRepeatTrayNone )
	{
		// Normal Mode
		CDlgTrayMap dlg;
		dlg.DoModal();
	}
	else if( m.m_RepeatTrayCtrl.m_iRepeatTrayMode == theApp.enRepeatTrayBinningCtrl )
	{
		// Pass/Fail Mode
		CDlgTrayMap dlg;
		dlg.DoModal();
	}
	else
	{
		CDlgTrayMap dlg;
		dlg.DoModal();
	}
}
void CPageRun::OnLotDone()
{
	f.m_Log.AddEvent(enCodeRunPageLotDone);	// Add Event

	CDlgLotInformationDone dlg;
	dlg.DoModal();

	// We need to updata UI information.
	UpdateSetting();
	ReDrawHeaterModule();
}
void CPageRun::OnLotInformation()
{
	f.m_Log.AddEvent(enCodeRunPageLotInformation);	// Add Event

	CDlgLotInformation dlg;
	dlg.DoModal();

	// We need to updata UI information.
	UpdateSetting();
	ReDrawHeaterModule();
}

/////////////////////////////////////////////////////////////////////////

// 1.0Af
// Remove this function and re-build new one
/*
void CPageRun::UpdateUPHCycle()
{
	double HH = (double)m.UPH.CycleTime / 3600; // Per Hours
	int iUPH = (int)( (double)( m.UPH.ICTested / HH ) );
	m.CalcInfo.UPH = iUPH;

	// m_wndUPH.SetNewText("UPH = 0\nCyc = 0");
	CString cs = _T("");

	double cyc = 0.0;
	if( m.UPH.CycleTime != 0 && m.UPH.ICTested != 0 )
	{
		cyc = double(m.UPH.CycleTime / m.UPH.ICTested );
	}
	if( cyc < 0 )
		cyc = 0.0;

	cs.Format("UPH = %d\nCyc = %5.2f secs", m.CalcInfo.UPH, cyc );
	m_wndUPH.SetNewText( cs );

	//
	f.SaveUPHInfo();
}
*/
void CPageRun::UpdateUPHCycle()
{
	double HH = (double)m.UPH.CycleTime / 3600; // Per Hours
	int iUPH = (int)( (double)( m.UPH.ICTested / HH ) );
	m.CalcInfo.UPH = iUPH;

	// m_wndUPH.SetNewText("UPH = 0\nCyc = 0");
	CString cs = _T("");

	double cyc = 0.0;
	double dCycleTime = double(m.UPH.CycleTime);
	double dTestedUnit = double(m.UPH.ICTested);
	if( m.UPH.CycleTime != 0 && m.UPH.ICTested != 0 )
	{
		cyc = dCycleTime / dTestedUnit;
	}
	if( cyc < 0 )
		cyc = 0.0;

	cs.Format("UPH = %d\nCyc = %5.2f secs", m.CalcInfo.UPH, cyc );
	m_wndUPH.SetNewText( cs );

	//
	f.SaveUPHInfo();
}
void CPageRun::UpdateHeaterStatus()
{
#ifdef _Demo
	m_ledHeater	= m.RemoteOutSet.HeaterOn == 1 ? true : false;	
#else	
	m_ledHeater	= m.RemoteOutStatus.HeaterOn == 1 ? true : false;
#endif
	m_ledHeaterStable = m.m_heaterCtrl.m_bHeaterIsStable == true ? true : false;
}
double CPageRun::GetOutputYieldValue(CString csCode)
{
	if( csCode == "" )
		return 0;

	int iSize = m.m_OutputYieldCounter.GetSize();

	// get total
	long m_lTotal = 0;
	for(int i=0;i<iSize;i++)
	{
		long m_lCounter = m.m_OutputYieldCounter.GetAt(i).m_lCodeCounter;
		m_lTotal += m_lCounter;
	}

	// display data
	CString m_csRate = _T("");
	for( i=0;i<iSize;i++)
	{
		tagOutputYield m_data;
		m_data.m_lCodeCounter = m.m_OutputYieldCounter.GetAt(i).m_lCodeCounter;
		m_data.m_csCode		  = m.m_OutputYieldCounter.GetAt(i).m_csCode;

		if( m_data.m_csCode == csCode )
		{			
			// rate
			if( m_data.m_lCodeCounter != 0 && m_lTotal != 0 )
			{
				double m_dCounter = m_data.m_lCodeCounter;
				double m_dTotal = m_lTotal;
				m_csRate.Format("%5.2f", (m_dCounter / m_dTotal) * 100 );
				break;
			}
			else
				m_csRate.Format("%5.2f", 0.0);
		}
		else
			m_csRate.Format("%5.2f", 0.0);
	}

	double dRate = 0.0;
	dRate = atof( m_csRate );
	return dRate;
}

void CPageRun::UpdateHeaterSoakTimeStatus()
{
	if( theApp.m_tInserter.m_TsSoak.lSoakStart != 0 )
	{
		// already enter soak time
		double m_dRemainTime = 0.0;
		long m_lNowTime = ::GetTickCount();

		// Repeat tray control from table
		double dSoakTime = m.m_West.dSoakTime;
		if( m.m_RepeatTrayCtrl.m_iRepeatTrayMode == theApp.enRepeatTrayInOutCtrl )
		{
			int iSize = m.m_RepeatTrayTemperData.GetSize();
			if( iSize > m.m_RepeatTrayDATA.m_NowCount )
				dSoakTime = m.m_RepeatTrayTemperData.GetAt( m.m_RepeatTrayDATA.m_NowCount ).m_dSoakingTime;
		}
		

		long m_lResultTime = m_lNowTime - theApp.m_tInserter.m_TsSoak.lSoakStart;
		m_dRemainTime = m_lResultTime / 1000.;
		CString m_csRemainTime = _T("");
//		double m_dShowRemainTime = m.m_West.dSoakTime - m_dRemainTime;
		double m_dShowRemainTime = dSoakTime - m_dRemainTime;
		if( m_dShowRemainTime < 0 )
			m_dShowRemainTime = 0;
		m_csRemainTime.Format("Soaking %5.2f secs", m_dShowRemainTime);
		m_wndHeaterDisSoakTine.SetWindowText( m_csRemainTime );
	}
	else if( theApp.m_tInserter.m_TsSoak.lSoakStart == 0 )
	{
		m_wndHeaterDisSoakTine.SetWindowText("");
	}
}
void CPageRun::UpdateHeaterStableStatus()
{
	if( m.m_heaterCtrl.m_bHeaterTempOK )
	{
		m.m_heaterCtrl.m_bHeaterTempOK = false;
		m.m_heaterCtrl.m_lHeaterStart = ::GetTickCount();
	}

	// 1.0Ac
	double dStableTime = m.m_West.dStableTime;
	if( m.m_RepeatTrayCtrl.m_iRepeatTrayMode == theApp.enRepeatTrayInOutCtrl )
	{	
		int iSize = m.m_RepeatTrayTemperData.GetSize();
		if( iSize > m.m_RepeatTrayDATA.m_NowCount )
			dStableTime = m.m_RepeatTrayTemperData.GetAt( m.m_RepeatTrayDATA.m_NowCount ).m_dStableTime;
	}
	//
	
	double dSpednTime = 0.0;
	f.HeaterIsStable(dSpednTime);
	if( m.m_heaterCtrl.m_lHeaterStart != 0 )
	{
		double m_dSpendTime = (::GetTickCount() - m.m_heaterCtrl.m_lHeaterStart ) / 1000.;
		CString csRemain = _T("");
		double m_dRemainTime = 0.0;
		m_dRemainTime = ( dStableTime - m_dSpendTime );
		if( m_dRemainTime < 0 )
		{
			m_dRemainTime = 0;
		}
		CString m_csRemainTime = _T("");
		m_csRemainTime.Format("%5.2f secs", m_dRemainTime);
		m_wndHeaterStableRemain.SetWindowText( m_csRemainTime );
	}
	else if( m.m_heaterCtrl.m_lHeaterStart == 0 )
	{
		m_wndHeaterStableRemain.SetWindowText("");
	}
}
void CPageRun::UpdateTSTemperature()
{
	double dPV[_MaxWestDevice];
	double dSV[_MaxWestDevice];
	m.m_DriveWest.GetValue( dPV, dSV );
	
	CString csTemp = _T("");
	double dTolerance = m.m_West.dTolerance;
	// 1.0Ac
	if( m.m_RepeatTrayCtrl.m_iRepeatTrayMode == theApp.enRepeatTrayInOutCtrl )
	{	
		int iSize = m.m_RepeatTrayTemperData.GetSize();
		if( iSize > m.m_RepeatTrayDATA.m_NowCount )
			dTolerance = m.m_RepeatTrayTemperData.GetAt( m.m_RepeatTrayDATA.m_NowCount ).m_dTolerance;
	}
	
	if( dPV[m.m_HandlerComPort.iPortWestHeaterID ] == _Device_Error )
	{
#ifdef _Demo
		csTemp.Format("25.5");
		m_wndTempTS.SetWindowText( csTemp );
		m_wndTempTS.SetNewBkColor(ST_GREEN);
#else
		csTemp.Format("Err");
		m_wndTempTS.SetWindowText( csTemp );
		m_wndTempTS.SetNewBkColor(ST_RED);
#endif
	}
	else
	{		
		int m_iDevID = m.m_HandlerComPort.iPortWestHeaterID;
		csTemp.Format("%5.2f", dPV[m_iDevID]);
		m_wndTempTS.SetWindowText( csTemp );
		
		double dTemperatureTolance = dTolerance;
		double dReadSV = 0.0;
		double dReadPV = 0.0;
		dReadSV = dSV[m_iDevID];
		dReadPV = dPV[m_iDevID];
		double dRange = (dReadSV) - (dReadPV);
		if( fabs(dRange) > dTemperatureTolance )
			m_wndTempTS.SetNewBkColor(ST_RED);
		else
			m_wndTempTS.SetNewBkColor(ST_GREEN);
	}
}
void CPageRun::UpdateSingleSiteCounter(int iSite)
{
	if(iSite < 0 || iSite >= _Site_Count )
		return;

	long lCount = m.CalcInfo.TestedIC;
	CString csCount = _T("");
	csCount.Format("%d", lCount );
	m_wndSiteCount[iSite].SetWindowText( csCount );
}
void CPageRun::UpdateSiteCounter()
{
	//////////////////////////////////////
	// 統計總數量. 統計方法 = Output 區的數量的加總.
	long total = 0;
	int i = 0;
	for(i=0; i<_Output_Stack_No; i++)
		total += m.Counter.OutputCount[i];

	CString cs = _T("");
	if(total > 0)
	// Note : If Total Tested IC > 0 . Then We show inforamtion.
	{
		cs.Format("Total = %d", total);
		m_wndTotal.SetNewText(cs);
		// Show total Tested IC counts.

		for(i=0; i<_Output_Stack_No; i++)
		{
			cs.Format("%d (%3.2f%%)",
				m.Counter.OutputCount[i], m.Counter.OutputCount[i] * 100. / total);
			m_wndOutputCount[i].SetWindowText(cs);
			// Show each Output Tested IC counts. And % of total tested IC counts.
			// #1: Output total tested IC counts #2: Output total tested IC / total tested IC.
		}
	}
	else
	// Note : If Total Tested IC < 0 . 
	{
		m_wndTotal.SetWindowText("Total = 0");

		for(i=0; i<_Output_Stack_No; i++)
		{
			cs = "0 ( 0 %)";
			m_wndOutputCount[i].SetWindowText(cs);
			// Show each Output Tested IC counts. And % of total tested IC counts.
			// #1: Output total tested IC counts #2: Output total tested IC / total tested IC.
		}
	}
	//////////////////////////////////////

	// 把記錄存到 3111.UI 裡面
	f.SaveCounter();
}

void CPageRun::UpdataLot()
{
	/*
	if( m.Info.iStatus == theApp.enCycle || m.Info.iStatus == theApp.enCycleStop || 
		m.Info.iStatus == theApp.enOverride || m.Info.iStatus == theApp.enOverrideStop ||
		m.Info.iStatus == theApp.enOneCycle || m.Info.iStatus == theApp.enOneCycleStop )
	{
		// 如果 在 Cycle Status
		// 不准使用 Lot Done 和 New Lot
		m_btnLotInformation.EnableWindow( FALSE );
		m_btnLotDone.EnableWindow( FALSE );
	}
	else if( m.InterLock.IsCycleFinishOK || m.LotInfo.LotInfoIsLotStart == 1 )
	{
		// 如果沒有 Cycle Finish 不可以使用 Lot Done.
		// 表示如果沒有 New Lot 就不會進入 Cycle.
		m.InterLock.IsCycleFinishOK = false;
		m_btnLotInformation.EnableWindow( FALSE );
		m_btnLotDone.EnableWindow( TRUE );	
	}
	else if( m.LotInfo.LotInfoIsLotStart == 0 )
	{
		// 如果沒有建過 New Lot 就 啟動 New Lot 按鈕, 和 關掉 Lot Done 的按鈕
		m_btnLotInformation.EnableWindow( TRUE );
		m_btnLotDone.EnableWindow( FALSE );
	}
	else
		; // Never be here.!
	//
	*/

	// 1.0Am
	// 增加判斷, 避免按鈕閃爍
	if( m.Info.iStatus == theApp.enCycle || m.Info.iStatus == theApp.enCycleStop || 
		m.Info.iStatus == theApp.enOverride || m.Info.iStatus == theApp.enOverrideStop ||
		m.Info.iStatus == theApp.enOneCycle || m.Info.iStatus == theApp.enOneCycleStop )
	{
		// 如果 在 Cycle Status
		// 不准使用 Lot Done 和 New Lot
		BOOL bLotInformation = m_btnLotInformation.IsWindowEnabled();
		if( bLotInformation == FALSE )
		{
		}
		else
			m_btnLotInformation.EnableWindow( FALSE );
		
		BOOL bLotDone = m_btnLotDone.IsWindowEnabled();
		if( bLotDone == FALSE )
		{
		}
		else
			m_btnLotDone.EnableWindow( FALSE );
	}
	else if( m.InterLock.IsCycleFinishOK || m.LotInfo.LotInfoIsLotStart == 1 )
	{
		// 如果沒有 Cycle Finish 不可以使用 Lot Done.
		// 表示如果沒有 New Lot 就不會進入 Cycle.
		m.InterLock.IsCycleFinishOK = false;

		BOOL bLotInformation = m_btnLotInformation.IsWindowEnabled();
		if( bLotInformation == FALSE )
		{
		}
		else
			m_btnLotInformation.EnableWindow( FALSE );

		BOOL bLotDone = m_btnLotDone.IsWindowEnabled();
		if( bLotDone == TRUE )
		{
		}
		else
			m_btnLotDone.EnableWindow( TRUE );	
	}
	else if( m.LotInfo.LotInfoIsLotStart == 0 )
	{
		// 如果沒有建過 New Lot 就 啟動 New Lot 按鈕, 和 關掉 Lot Done 的按鈕
		BOOL bLotInformation = m_btnLotInformation.IsWindowEnabled();
		if( bLotInformation == TRUE )
		{
		}
		else
			m_btnLotInformation.EnableWindow( TRUE );
		
		BOOL bLotDone = m_btnLotDone.IsWindowEnabled();
		if( bLotDone == FALSE )
		{
		}
		else
			m_btnLotDone.EnableWindow( FALSE );
	}
	else
		; // Never be here.!
	//
}

void CPageRun::UpdateLotInformation()
{
	// UI status
	// Tray File
	// Mapping File
	// InterFace File
	CString UIStatus;
	if( m.LotInfo.LotInfoIsLotStart == 0 )
	{
		UIStatus.Format(
			"Tray File: %s\n"
			"MappingFIle: %s\n",

			m.UI.FileMain, 		
			m.UI.FileMainMapping

			);
			// Not New Lot (No Lot Info)
	}
	else
	{
		UIStatus.Format(
			"Lot ID : %s\n"
			"Lot Program ID : %s\n"
			"Lot Device ID : %s\n"

			"Tray File: %s\n"
			"MappingFIle: %s\n",
			
			m.LotInfo.LotInfoNo,
			m.LotInfo.LotInfoProgramerID,
			m.LotInfo.LotInfoDeviceID,

			m.UI.FileMain, 		
			m.UI.FileMainMapping	

			);
		// Operator already bulid a new lot
		// Not New Lot (No Lot Info)
	}
	m_wndFile.SetNewText(UIStatus);
}
void CPageRun::UpdateYieldSettingInformation()
{
	/// Yield Control Status
	// 更新 LED 狀態
	if(m.YieldSetting.iRetestCount == 0)
	{
		m_ledRetest = false;
		m_wndRetestTimes.ShowWindow(SW_HIDE);
	}
	else
	{
		m_ledRetest = true;
		m_wndRetestTimes.ShowWindow(SW_SHOW);
		CString cs;
		cs.Format("%d Times", m.YieldSetting.iRetestCount);
		m_wndRetestTimes.SetWindowText(cs);
	}
	// Reset Times

	if(m.YieldSetting.bYieldControlEnable == 1)
	{
		m_ledYieldControl = true;
		// set UI led

		m_wndYieldLimit.ShowWindow(SW_SHOW);
		CString y;
		y.Format("> %3.1f%%", m.YieldSetting.dYieldLimit);
		m_wndYieldLimit.SetWindowText(y);
	}
	else
	{
		m_ledYieldControl = false;
		m_wndYieldLimit.ShowWindow(SW_HIDE);
	}
	// Yield Control Enable / Disable

	if(m.YieldSetting.bContinueFailEnable == 1)
	{
		m_ledContinueFail = true;
		// set UI led

		m_wndContinueFail.ShowWindow(SW_SHOW);
		CString c;
		c.Format("< %d", m.YieldSetting.iFailCount);
		m_wndContinueFail.SetWindowText(c);
	}
	else
	{
		m_ledContinueFail = false;
		m_wndContinueFail.ShowWindow(SW_HIDE);
	}
	// Yield Control Contiune Fail Enable / Disable
}
void CPageRun::UpdataTsVaccOffStatusInformation()
{
	// Test Site Vacc
	if( m.TraySkip.TestSiteVacc == 1 )
		m_btnTestSiteVacc.SetIcon(IDI_SOCKET_VACC);
	else
		m_btnTestSiteVacc.SetIcon(IDI_SOCKET_NO_VACC);
}
void CPageRun::UpdateAutoSkipStatusInformation()
{
	if( m.TraySkip.AutoSkip == 0 )
		m_btnAutoSkip.SetIcon(IDI_TRAY_AUTO_SKIP);
	else
		m_btnAutoSkip.SetIcon(IDI_TRAY_NOT_AUTO_SKIP);
}
void CPageRun::UpdataRepeatMation()
{
	if( m.m_RepeatTrayCtrl.m_iRepeatTrayMode != theApp.enRepeatTrayInOutCtrl )
	{
		m_wndNowMoation.ShowWindow( FALSE );
		return;
	}
	else
		m_wndNowMoation.ShowWindow( TRUE );

	// (1) Input->Output
	//////////////////////////////////////////////////////////////////////////////////////////
	if( f.GetRepeatTrayModeMoation() == theApp.enRepeatTray1ToTray2 )
	{
		if( f.GetNowMoation( m.m_RepeatTrayDATA.m_NowCount ) == theApp.enRepeatTrayMation1 )
		{
			// 到Tray1取料, 放到Tray2
			CString csMsg = _T("");
			csMsg.Format("Tray1->Tray2");
			m_wndNowMoation.SetWindowText(csMsg);

		}
		else if( f.GetNowMoation( m.m_RepeatTrayDATA.m_NowCount ) == theApp.enRepeatTrayMation2 )
		{
			// 到Tray2取料, 放到Tray1
			CString csMsg = _T("");
			csMsg.Format("Tray2->Tray1");
			m_wndNowMoation.SetWindowText(csMsg);
		}
		else 
			;
	}
	// (2) Output->Input
	//////////////////////////////////////////////////////////////////////////////////////////
	else if( f.GetRepeatTrayModeMoation() == theApp.enRepeatTray2ToTray1 )
	{
		if( f.GetNowMoation( m.m_RepeatTrayDATA.m_NowCount ) == theApp.enRepeatTrayMation1 )
		{
			// 到Tray2取料, 放到Tray1
			CString csMsg = _T("");
			csMsg.Format("Tray2->Tray1");
			m_wndNowMoation.SetWindowText(csMsg);

		}
		else if( f.GetNowMoation( m.m_RepeatTrayDATA.m_NowCount ) == theApp.enRepeatTrayMation2 )
		{
			// 到Tray1取料, 放到Tray2
			CString csMsg = _T("");
			csMsg.Format("Tray1->Tray2");
			m_wndNowMoation.SetWindowText(csMsg);
		}
		else 
			;	
	}
	// (3) Both, Disable
	//////////////////////////////////////////////////////////////////////////////////////////
	else if( f.GetRepeatTrayModeMoation() == theApp.enRepeatTray1AndDisable )
	{
		// 到Tray1取料, 放到Tray1
		CString csMsg = _T("");
		csMsg.Format("Tray1(Both)");
		m_wndNowMoation.SetWindowText(csMsg);	
	}
	// (4) Disable, Both
	//////////////////////////////////////////////////////////////////////////////////////////
	else if( f.GetRepeatTrayModeMoation() == theApp.enRepeatDisableAndTray2 )
	{
		// 到Tray2取料, 放到Tray2
		CString csMsg = _T("");
		csMsg.Format("Tray2(Both)");
		m_wndNowMoation.SetWindowText(csMsg);		
	}	
	// (5) Both, Both
	//////////////////////////////////////////////////////////////////////////////////////////
	else if( f.GetRepeatTrayModeMoation() == theApp.enRepeatTray1AndTray2 )
	{
		CString csMsg = _T("");
		if( m.m_RepeatTrayDATA.m_bRepeatIsTray1 == true )
			csMsg.Format("(Both)Tray 1");
		else
			csMsg.Format("(Both)Tray 2");

		m_wndNowMoation.SetWindowText(csMsg);
	}
	// (6) Pass, Fail
	//////////////////////////////////////////////////////////////////////////////////////////
	else if( f.GetRepeatTrayModeMoation() == theApp.enRepeatPass1AndFail2 )
	{
		CString csMsg = _T("");
		csMsg.Format("Tray1(P)/Tray2(F)");
		m_wndNowMoation.SetWindowText(csMsg);
	}
	// (7) Fail, Pass
	//////////////////////////////////////////////////////////////////////////////////////////
	else if( f.GetRepeatTrayModeMoation() == theApp.enRepeatFail1AndPass2 )
	{
		CString csMsg = _T("");
		csMsg.Format("Tray1(F)/Tray2(P)");
		m_wndNowMoation.SetWindowText(csMsg);
	}
	else
		;
}
void CPageRun::UpdataRemoteModeStatus()
{
	if( m.m_TestInterface.GetRemoteMode() )
	{
		m_bRemoteFlash = !m_bRemoteFlash;
		if( m_bRemoteFlash )
			m_wndNowTemperature.SetNewBkColor( ST_GREEN );
		else
			m_wndNowTemperature.SetNewBkColor( ST_RED );
	}
	else
		m_wndNowTemperature.SetNewBkColor( ST_WHITE );
}
void CPageRun::UpdataNowTemperature()
{
	if( m.Setting.m_bShowHandlerStatus == 1 )
	{
		bool bNeed = f.IsTrayFileNeedTemperature();
		if(bNeed)
		{
			double dNowTemperature = 0.0;
			dNowTemperature = f.GetNowTemperature( m.m_RepeatTrayDATA.m_NowCount );
			CString csNowTemperature = _T("");
			if( dNowTemperature == 0.0 )
				csNowTemperature.Format("None deg");
			else
				csNowTemperature.Format("%5.2f deg", dNowTemperature );
			m_wndNowTemperature.SetWindowText( csNowTemperature );
		}
		else
		{
			// 1.0Af
			if( m.TraySpec.Heating == theApp.enRemote )
			{
				CString csNowTemperature = _T(""); 
				csNowTemperature.Format("Remote");
				m_wndNowTemperature.SetWindowText( csNowTemperature );
			}
			else
			{
				CString csNowTemperature = _T(""); 
				csNowTemperature.Format("Ambient");
				m_wndNowTemperature.SetWindowText( csNowTemperature );
			}
		}
	}
}
void CPageRun::UpdataHandlerStatusInfo()
{
	if( m.Setting.m_bShowHandlerStatus == 1 )
	{
		CString csJamRate = _T("");
		CString csRunTime = _T("");

		csRunTime = f.GetRunTimeFromCycleTime( m.m_JamRateInfo.m_lCycleTime );
		long lTotal = m.m_JamRateInfo.m_lCycleTime;
		long lJamRate = m.m_JamRateInfo.m_lJamError;
		long lTotalUnit = m.m_JamRateInfo.m_lTotalUnit;

		if( m.LotInfo.LotInfoIsLotStart == 1 )
		{
			// 有建立 Lot, 所以多顯示 TrayFile
			CString csTrayMode = _T("");
			csTrayMode = f.GetTrayFileNowMode();
			csJamRate.Format(" Run Time: %s, Total: %d s\r\n Jam Rate: %d/%d\r\n Temperature Mode: %s",
				csRunTime, lTotal, lJamRate, lTotalUnit, csTrayMode );
		}
		else
		{			
			csJamRate.Format("\r\n Run Time: %s, Total: %d s\r\n Jam Rate: %d/%d",
				csRunTime, lTotal, lJamRate, lTotalUnit );
		}
		m_wndHandlerStatus.SetWindowText( csJamRate );
	}
}
void CPageRun::UpdataRepeatTrayStatus()
{

}
void CPageRun::UpdateYieldContactModeInformation()
{
	if( m.YieldSetting.bDropMode == 1 )
	{
		m_btnContactMode.SetIcon(IDI_DROP_MODE);
		m_btnContactMode.SetAlign(CButtonST::ST_ALIGN_VERT);
		// Note : If value == 1. It will enable IC Drop Mode.
	}
	else 
	{
		m_btnContactMode.SetIcon(IDI_DIRECT_CONTACT);
		m_btnContactMode.SetAlign(CButtonST::ST_ALIGN_VERT);
		// Note : If value == 0. It will let IC direct contact to socket.
	}
}
void CPageRun::UpdateColorCatoregyInformation()
{		
	//
	m_listData.ResetColors();
	m_listData.DeleteAllItems();

	//
	RunBinMap.Copy( m.BinMap );
	int iBinSize = RunBinMap.GetSize();
	if( iBinSize == 0 || m.LotInfo.LotInfoIsLotStart == 0 )
		return;

	theApp.DoWaitCursor(1);

	// 顯示資料
	theApp.DoWaitCursor(1);
	int iCount = 0;
	tagCatoregyRunPageItem Label;
	int iSize = 0;
	iSize = RunBinMap.GetSize();
	int isoftware = 0;
	for(int i=0;i<iSize;i++)
	{
		iCount++;
		Label.item			= iCount;
		Label.software		= RunBinMap.GetAt(i).software;
		isoftware			= atoi( RunBinMap.GetAt(i).software );
		Label.code			= RunBinMap.GetAt(i).code;
		Label.pf			= RunBinMap.GetAt(i).pass == true ? 1 : 0;

		m_listData.SetCellColor( RunBinMap.GetAt(i).color, i, 2);
		m_Source.SetAtGrow(iCount-1, Label);
	}

	isoftware			= 999;
	CString csTimeout	= _T("");
	csTimeout.Format("%d", isoftware);
	CString csOther		= _T("");
	csOther.Format("%d", isoftware);
	COLORREF ColorRef	= ST_GRAY;

	// Timeout
	iCount++;
	Label.item			= iCount;
	Label.software		= csTimeout;
	Label.code			= _BinDescTimeout;
	Label.pf			= 0;
	m_listData.SetCellColor( ColorRef, i++, 2);
	m_Source.SetAtGrow(iCount-1, Label);

	// Other
	iCount++;
	Label.item			= iCount;
	Label.software		= csOther;
	Label.code			= _BinDescOther;
	Label.pf			= 0;
	m_listData.SetCellColor( ColorRef, i++, 2);
	m_Source.SetAtGrow(iCount-1, Label);

	// 更新資料
	m_listData.SetItemCountEx(iCount);
	m_listData.Invalidate();

	theApp.DoWaitCursor(0);
	//
}
void CPageRun::UpdateCatoregyStatus()
{

}
void CPageRun::UpdateCCDPin1Status()
{
	if( m.Setting.m_bEnableCCDPin1 == 1 )
	{
		m_btnCCD.ShowWindow( TRUE );
		if( m.m_TestSetting.m_CCDUse == 1 )
			m_btnCCD.SetIcon(IDI_RT_IMAGE);
		else
			m_btnCCD.SetIcon(IDI_RT_IMAGE_DISABLE);
	}
	else
	{
		m_btnCCD.SetIcon(IDI_RT_IMAGE);
		m_btnCCD.ShowWindow( FALSE );
	}
}
void CPageRun::UpdataCCDSocketStatus()
{
	if( m.Setting.m_bEnableCCDSocket == 1 )
	{
		m_btnCCDSocket.ShowWindow( TRUE );
		if( m.m_TestSetting.m_CCDSocketUse == 1 )
			m_btnCCDSocket.SetIcon( IDI_CCD_SOCKET_SETUP );
		else
			m_btnCCDSocket.SetIcon( IDI_CCD_SOCKET_SETUP_CLOSE );
	}
	else
	{
		m_btnCCDSocket.SetIcon( IDI_CCD_SOCKET_SETUP );
		m_btnCCDSocket.ShowWindow( FALSE );
	}
}
void CPageRun::UpdateRotatorStatus()
{
	if( m.Setting.m_bRotatoUse == 1 )
	{
		m_btnRotatorStstus.ShowWindow( TRUE );
		if( m.m_TestSetting.m_RotatorUse == 1 )
		{			
			if( m.m_TestSetting.m_Angle == 0 )	
				m_btnRotatorStstus.SetIcon(IDI_ROTATOR_STATUS_P);// -90
			else if( m.m_TestSetting.m_Angle == 1 )			
				m_btnRotatorStstus.SetIcon(IDI_ROTATOR_STATUS_N);// +90
			else if( m.m_TestSetting.m_Angle == 2 )
				m_btnRotatorStstus.SetIcon(IDI_ROTATOR_STATUS_O);// 0
			else 
				m_btnRotatorStstus.SetIcon(IDI_ROTATOR_STATUS_O);// Nerver be here
		}
		else 
		{
			m_btnRotatorStstus.SetIcon(IDI_ROTATOR_STATUS_D);// Disable
		}
	}
	else
	{
		m_btnRotatorStstus.ShowWindow( FALSE );
	}
}
void CPageRun::UpdateHandlerRunModeStatusInformation()
{
	/*
	enOnLine = 0, 
	enOffLine = 1, 
	enDemo = 2, 
	enRunModeEnd = 3
	*/
	///////////////////////////////////////
	/// Handler Status
	CString csTestStatus;
	switch(m.Site.iRunMode)
	{
	case theApp.enOnLine:		
		{
			csTestStatus.Format("On Line");
			m_wndRunMode.SetNewTextColor(ST_BLACK);
			m_wndRunMode.SetNewBkColor(ST_GREEN);
		}
		break;
	case theApp.enOffLine:
		{
			csTestStatus.Format("Off Line");
			m_wndRunMode.SetNewTextColor(ST_BLACK);
			m_wndRunMode.SetNewBkColor(ST_YELLOW);
		}
		break;
	case theApp.enDemo:
		{
			csTestStatus.Format("Demo");
			m_wndRunMode.SetNewTextColor(ST_WHITE);
			m_wndRunMode.SetNewBkColor(ST_RED);
		}
		break;
	}
	m_wndRunMode.SetNewText(csTestStatus);
}
void CPageRun::ReDrawTsCounterStatus()
{
	if( m.Setting.m_bShowContactCounter == 1 )
	{		
		CString cs = _T("");
		cs.Format("Contact Counter: %d", m.m_ContactCounterValue.lContactConter );
		m_wndContactCounterr.SetWindowText( cs );
		m_wndContactCounterr.ShowWindow( TRUE );
	}
	else
		m_wndContactCounterr.ShowWindow( FALSE );
}
void CPageRun::ReDrawRepeatTrayICStatus()
{
	if( m.m_RepeatTrayCtrl.m_iRepeatTrayMode == theApp.enRepeatTrayNone )
		m_wndCurrentRepeatTrayStatus.ShowWindow( FALSE );
	else
		m_wndCurrentRepeatTrayStatus.ShowWindow( TRUE );
}
void CPageRun::ReDrawNowTemperature()
{
//	bool bIsNeed = f.IsTrayFileNeedTemperature();
//	if(bIsNeed)
//		m_wndNowTemperature.ShowWindow( TRUE );
//	else
//		m_wndNowTemperature.ShowWindow( FALSE );

	bool bIsNeed = false;
	if( m.m_RepeatTrayCtrl.m_iRepeatTrayMode == theApp.enRepeatTrayInOutCtrl )
		bIsNeed = true;
	if(bIsNeed)
		m_wndNowTemperature.ShowWindow( TRUE );
	else
		m_wndNowTemperature.ShowWindow( FALSE );

}
void CPageRun::ReDrawHandlerStatus()
{
	if( m.Setting.m_bShowHandlerStatus == 1 )
		m_wndHandlerStatus.ShowWindow( TRUE );
	else
		m_wndHandlerStatus.ShowWindow( FALSE );
}

void CPageRun::ReDrawRepeatTrayFileBkColor()
{
	COLORREF color = ST_WHITE;
	color = f.GetRepeatTrayFileColor( m.TraySpec.Heating );

	m_wndRepeatTrayStatus.SetNewBkColor( color );
}
void CPageRun::ReDrawRepeatTrayStatus()
{
	if( m.m_RepeatTrayCtrl.m_iRepeatTrayMode == theApp.enRepeatTrayNone )
		m_wndRepeatTrayStatus.ShowWindow( FALSE );
	else
		m_wndRepeatTrayStatus.ShowWindow( TRUE );
}
void CPageRun::ReDrawHeaterOption()
{

}
void CPageRun::ReDrawHeaterModule()
{
	if( m.Setting.m_bEnableHeaterModule == 1 && 
		m.UI.FileMain != "" && 
		m.TraySpec.Heating == theApp.enHeater )
	{
		m_HeaterModuleGrp.ShowWindow( TRUE );	
		CString csStableTime = _T("");
		csStableTime.Format("%5.2f secs", m.m_West.dStableTime );
		m_wndHeaterStableTime.SetWindowText( csStableTime );
		CString csSoakTime = _T("");
		csSoakTime.Format("%5.2f secs", m.m_West.dSoakTime );
		m_wndHeaterSoakTine.SetWindowText( csSoakTime );
		CString csSetPoint = _T("");
		csSetPoint.Format("%5.2f, +/-%5.2f(deg)", m.m_West.dSetPoint, m.m_West.dTolerance );
		m_wndHeaterSetPoint.SetWindowText( csSetPoint );
	}
	else
	{
		m_HeaterModuleGrp.ShowWindow( FALSE );
	}
}
void CPageRun::ReDrawTemperature()
{
	if( m.Setting.m_bEnableHeaterModule == 1 )
		m_wndTempTS.ShowWindow( TRUE );
	else
		m_wndTempTS.ShowWindow( FALSE );
}
void CPageRun::ReDrawTorqueStatus()
{
	if( m.Setting.m_bEnableTorqueStatus == 1 )
		m_wndTorqueStatus.ShowWindow( TRUE );
	else
		m_wndTorqueStatus.ShowWindow( FALSE );
}
void CPageRun::ReDrawOutputColor()
{
	COLORREF color = RGB( m.m_RunPageOutputColor.R, m.m_RunPageOutputColor.G, m.m_RunPageOutputColor.B);
	if( color != lOutputColor )
	{		
		lOutputColor = color;
		m_wndOutput[0].SetNewBkColor( lOutputColor );
	}
}
void CPageRun::UpdataRepeatInformation()
{
	//
	UpdateRepeatTrayDetailStatus();

	//
	UpdataRepeatMation();
}
void CPageRun::UpdateRepeatTrayDetailStatus()
{
	CString csFinalInfo = _T("");

	// Count
	int iRepeatTested = 0;
	iRepeatTested = f.GetRepeatTrayTimes();
	CString csCount = _T("");
	CString csNowCount = _T("");
	csNowCount.Format("(%d)", m.m_RepeatTrayDATA.m_NowCount );
	if( iRepeatTested == 0 )
			csCount.Format(" Repeat Times: %s, Repeat Timed: %s\r\n", _Infinity, csNowCount );
	else
		csCount.Format(" Repeat Times: %d, Repeat Timed: %s\r\n", iRepeatTested, csNowCount );
	csFinalInfo += csCount;

	// Mode
	CString csMode = _T("");
	csMode.Format( " Mode: %s\r\n", f.GetRepeatTrayMode());
	csFinalInfo += csMode;

	// Mation
	CString csMation = _T("");
	if( m.m_RepeatTrayCtrl.m_iRepeatTrayMode == theApp.enRepeatTrayInOutCtrl )
		csMation.Format("(%d)", f.GetRepeatTrayModeMoation());

	// Tray define 
	CString csTrayDefine = _T("");
	csTrayDefine.Format(" Tray 1:%s, Tray 2: %s %s\r\n", 
		f.GetRepeatTreyDefine(m.m_RepeatInOutCtrl.m_iTray1 ),
		f.GetRepeatTreyDefine(m.m_RepeatInOutCtrl.m_iTray2 ),
		csMation );
	csFinalInfo += csTrayDefine;

	m_wndRepeatTrayStatus.SetWindowText( csFinalInfo );
}
void CPageRun::UpdateSetting()
{	
	// 顯示工單資訊
	UpdateLotInformation();

	// 設定 Yiled Control 顯示狀態
	UpdateYieldSettingInformation();
	
	// 設定 Contact 顯示狀態.
	UpdateYieldContactModeInformation();

	// 設定 Repeat Tray 顯示狀態
	UpdataRepeatTrayStatus();

	// 設定 AutoSkip 顯示狀態.
	UpdateAutoSkipStatusInformation();

	// 設定 Test Site Vacc Off 顯示狀態
	UpdataTsVaccOffStatusInformation();

	// 設定 Run Mode 設定 (Demo / OffLine / OnLine )
	UpdateHandlerRunModeStatusInformation();

	// 設定 Rotator 顯示狀態
	UpdateRotatorStatus();

	// 設定 CCD Pin1 顯示狀態
	UpdateCCDPin1Status();

	// 設定 CCD Socket 顯示狀態
	UpdataCCDSocketStatus();

	// 設定 Catoregy 顯示狀態
	UpdateCatoregyStatus();

	// 設定 Catoregy Color 顯示狀態
	UpdateColorCatoregyInformation();

	// 重新設定 Buttont 狀態 
	UpdataICONButton();

	// 更新良率的狀態
	UpdateYieldSetting();
}
void CPageRun::UpdateYieldSetting()
{
	m_listData.Invalidate(FALSE);
}
void CPageRun::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);
	
	if(bShow)
		UpdateSetting();

	if(bShow)
		UpdateRepeatTrayDetailStatus();

	if(bShow)
		UpdataRepeatMation();

	if(bShow)
		ReDrawOutputColor();

	if(bShow)
		ReDrawTorqueStatus();

	if(bShow)
		ReDrawTemperature();

	if(bShow)
		ReDrawHeaterModule();

	if(bShow)
		ReDrawHeaterOption();

	if(bShow)
		ReDrawRepeatTrayStatus();

	if(bShow)
		ReDrawRepeatTrayFileBkColor();

	if(bShow)
		ReDrawHandlerStatus();

	if(bShow)
		ReDrawNowTemperature();

	if(bShow)
		ReDrawRepeatTrayICStatus();

	if(bShow)
		ReDrawTsCounterStatus();
}
			  
BOOL CPageRun::PreTranslateMessage(MSG* pMsg) 
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

void CPageRun::OnTimer(UINT nIDEvent) 
{
	switch(nIDEvent)
	{
	case ID_TIME_STATUS:
		{
			UpdateSiteCounter();			// Updata Test info
//			UpdateSingleSiteCounter(0);		// Updata Test info
			UpdateUPHCycle();				// Updata UPH and Cycle counter
			UpdataLot();					// Updata Lot Button status.
			UpdateHeaterStatus();			// Updata Heater IO status
		}
		break;
	case ID_TIME_MULIT_SV_UPDATA_PAGE:
		{
			
		}
		break;
	case ID_TIME_TS_TEMPERATURE:
		{
			UpdateTSTemperature();			// Ts Temperature
		}
		break;
	case ID_TIME_TEMP_STABLE:
		{
			UpdateHeaterStableStatus();		// Stable Status
		}
		break;
	case ID_TIME_TEMP_SOAK:
		{
			UpdateHeaterSoakTimeStatus();	// Soak Time Status
		}
		break;
	case ID_TIME_PAGE_OUTPUT_YIELD:
		{
			// 1.0Al
//			m_listData.Invalidate(FALSE);

			// 1.0As
			m_listData.Invalidate(FALSE);
		}
		break;
	case ID_TIME_JAM_RATE_INFO:
		{
			UpdataHandlerStatusInfo();
		}
		break;
	case ID_TIME_NOW_TEMPERATURE:
		{
			UpdataNowTemperature();
		}
		break;
	case ID_TIME_REMOTE_STATUS:
		{
			UpdataRemoteModeStatus();
		}
		break;
	}
	
	CDialog::OnTimer(nIDEvent);
}


