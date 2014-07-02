// PageSetup.cpp : implementation file
//

#include "stdafx.h"
#include "Deer.h"
#include "DeerDlg.h"
#include "PageSetup.h"

// Dlg 
#include "DlgMotorMontior.h"
#include "DlgIOMontior.h"
#include "DlgEvent.h"
#include "DlgDeviceSetup.h"
#include "DlgSpeed.h"
#include "DlgTimer.h"
#include "DlgYieldControl.h"
#include "DlgTrayFile.h"
#include "DlgSiteSetting.h"
#include "DlgTrayFileNoHeater.h"
#include "DlgBinMapping.h"
#include "DlgInputTrayMap.h"
#include "DlgAutoRetry.h"
#include "DlgOffset.h"
#include "DlgExtendFunction.h"
#include "DlgRemoteControl.h"
#include "DlgRemoteControlCustom.h"
#include "DlgCategory.h"
#include "DlgSocketMatch.h"
#include "DlgVisionSetup.h"
#include "DlgATCModuleCalibration.h"
#include "DlgTestSetting.h"
#include "DlgTestTesting.h"
#include "DlgRemoteControlCustomInput.h"
#include "DlgATCModuleFile.h"
#include "DlgAlignment.h"
#include "DlgOutputTrayMap.h"
#include "DlgInOutputTrayMap.h"
#include "DlgTemperature.h"
#include "DlgRepeatTray.h"
#include "DlgTowerSetting.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPageSetup dialog


CPageSetup::CPageSetup(CWnd* pParent /*=NULL*/)
	: CDialog(CPageSetup::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPageSetup)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CPageSetup::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPageSetup)
	DDX_Control(pDX, IDC_TOWER_SETTING,				m_btnTowerSetting);
	DDX_Control(pDX, IDC_REPEAT_TRAY,				m_btnRepeatTray);
	DDX_Control(pDX, IDC_IN_OUT_TRAY,				m_btnInOutTray);
	DDX_Control(pDX, IDC_OUTPUT_TRAY,				m_btnOutputTrayMap);
	DDX_Control(pDX, IDC_TEMPERATURE,				m_btnTemperature);
	DDX_Control(pDX, IDC_ATC_MODULE,				m_btnATCModule);
	DDX_Control(pDX, IDC_REMOTE_INPUT,				m_btnRemoteInput);
	DDX_Control(pDX, IDC_INTERFACE_SETTING,			m_btnInterFaceSetting);
	DDX_Control(pDX, IDC_ATC_CALIBRATION,			m_btnATCCalibration);
	DDX_Control(pDX, IDC_CCD_SETUP,					m_btnCCDSetup);
	DDX_Control(pDX, IDC_CCD_SOCKET,				m_btnSocketCCDSetup);
	DDX_Control(pDX, IDC_CATOREGY,					m_btnCatoregy);
	DDX_Control(pDX, IDC_REMOTE_CONTROL,			m_btnRemoteControl);
	DDX_Control(pDX, IDC_EXTEND_FUNCTION,			m_btnExtendFunction);
	DDX_Control(pDX, IDC_AUTO_RETRY,				m_btnAutoRetry);
	DDX_Control(pDX, IDC_INPUT_TRAY,				m_btnInputTrayMap);
	DDX_Control(pDX, IDC_CHANGE_FILE3,				m_btnTrayFile2);
	DDX_Control(pDX, IDC_INTERFACE_TESTING,			m_btnInterfaceTesting);
	DDX_Control(pDX, IDC_YIELD_CTRL,				m_btnYieldCTRL);
	DDX_Control(pDX, IDC_SPEED,						m_btnSpeed);
	DDX_Control(pDX, IDC_TIMER,						m_btnTimer);
	DDX_Control(pDX, IDC_OFFSET,					m_btnOffset);
	DDX_Control(pDX, IDC_DEVICE_SETUP,				m_btnDeviceSetup);
	DDX_Control(pDX, IDC_ALIGNMENT_SETUP,			m_btnAlignment);
	DDX_Control(pDX, IDC_EVENT_LOG,					m_btnEvent);
	DDX_Control(pDX, IDC_IO_MONTIOR,				m_btnIOMonitor);
	DDX_Control(pDX, IDC_SITE_SETTING,				m_btnSiteSetting);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CPageSetup, CDialog)
	//{{AFX_MSG_MAP(CPageSetup)
	ON_BN_CLICKED(IDC_IO_MONTIOR,					OnIoMontior)
	ON_BN_CLICKED(IDC_EVENT_LOG,					OnEventLog)
	ON_BN_CLICKED(IDC_ALIGNMENT_SETUP,				OnAlignmentSetup)
	ON_BN_CLICKED(IDC_DEVICE_SETUP,					OnDeviceSetup)
	ON_BN_CLICKED(IDC_OFFSET,						OnOffset)
	ON_BN_CLICKED(IDC_SPEED,						OnSpeed)
	ON_BN_CLICKED(IDC_TIMER,						OnTimer)
	ON_BN_CLICKED(IDC_YIELD_CTRL,					OnYieldCtrl)
	ON_BN_CLICKED(IDC_INTERFACE_TESTING,			OnInterfaceTesting)
	ON_WM_SHOWWINDOW()
	ON_BN_CLICKED(IDC_SITE_SETTING,					OnSiteSeeing)
	ON_BN_CLICKED(IDC_INPUT_TRAY,					OnInputTray)
	ON_BN_CLICKED(IDC_AUTO_RETRY,					OnAutoRetry)
	ON_BN_CLICKED(IDC_CHANGE_FILE3,					OnChangeFile3)
	ON_BN_CLICKED(IDC_EXTEND_FUNCTION,				OnExtendFunction)
	ON_BN_CLICKED(IDC_REMOTE_CONTROL,				OnRemoteControl)
	ON_BN_CLICKED(IDC_CATOREGY,						OnCatoregy)
	ON_BN_CLICKED(IDC_CCD_SOCKET,					OnCcdSocket)
	ON_BN_CLICKED(IDC_CCD_SETUP,					OnCcdSetup)
	ON_BN_CLICKED(IDC_ATC_CALIBRATION,				OnAtcCalibration)
	ON_BN_CLICKED(IDC_INTERFACE_SETTING,			OnInterfaceSetting)
	ON_BN_CLICKED(IDC_REMOTE_INPUT,					OnRemoteInput)
	ON_BN_CLICKED(IDC_ATC_MODULE,					OnAtcModule)
	ON_BN_CLICKED(IDC_TEMPERATURE,					OnTemperature)
	ON_BN_CLICKED(IDC_OUTPUT_TRAY,					OnOutputTray)
	ON_BN_CLICKED(IDC_IN_OUT_TRAY,					OnInOutTray)
	ON_BN_CLICKED(IDC_REPEAT_TRAY,					OnRepeatTray)
	ON_BN_CLICKED(IDC_TOWER_SETTING,				OnTowerSetting)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPageSetup message handlers

BOOL CPageSetup::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// init Button
	m_btnIOMonitor.SetIcon(IDI_IO);
	m_btnIOMonitor.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnIOMonitor.SetFlat(FALSE);

	m_btnEvent.SetIcon(IDI_EVENT_LOG);
	m_btnEvent.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnEvent.SetFlat(FALSE);

	m_btnAlignment.SetIcon(IDI_ALIGNMENT);
	m_btnAlignment.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnAlignment.SetFlat(FALSE);

	m_btnDeviceSetup.SetIcon(IDI_DEVICE);
	m_btnDeviceSetup.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnDeviceSetup.SetFlat(FALSE);
	
	m_btnOffset.SetIcon(IDI_OFF_SET);
	m_btnOffset.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnOffset.SetFlat(FALSE);

	m_btnTimer.SetIcon(IDI_TIMER);
	m_btnTimer.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnTimer.SetFlat(FALSE);

	m_btnSpeed.SetIcon(IDI_SPEED);;
	m_btnSpeed.SetAlign(CButtonST::ST_ALIGN_VERT);;
	m_btnSpeed.SetFlat(FALSE);

	m_btnYieldCTRL.SetIcon(IDI_FLOW_CHAR);
	m_btnYieldCTRL.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnYieldCTRL.SetFlat(FALSE);

	m_btnInterfaceTesting.SetIcon(IDI_INTER_FACE_TESTING);
	m_btnInterfaceTesting.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnInterfaceTesting.SetFlat(FALSE);

	m_btnSiteSetting.SetIcon(IDI_SITE_SETTING);
	m_btnSiteSetting.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnSiteSetting.SetFlat(FALSE);
	
	m_btnInputTrayMap.SetIcon(IDI_INPUT_TRAY);
	m_btnInputTrayMap.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnInputTrayMap.SetFlat(FALSE);

	m_btnOutputTrayMap.SetIcon(IDI_OUTPUT_TRAY);
	m_btnOutputTrayMap.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnOutputTrayMap.SetFlat(FALSE);

	m_btnAutoRetry.SetIcon(IDI_AUTO_RETRY);
	m_btnAutoRetry.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnAutoRetry.SetFlat(FALSE);

	m_btnTrayFile2.SetIcon(IDI_FILE);;
	m_btnTrayFile2.SetAlign(CButtonST::ST_ALIGN_VERT);;
	m_btnTrayFile2.SetFlat(FALSE);
	
	m_btnExtendFunction.SetIcon(IDI_COUNTER);
	m_btnExtendFunction.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnExtendFunction.SetFlat(FALSE);

	m_btnRemoteControl.SetIcon(IDI_VISUAL_PANEL2);
	m_btnRemoteControl.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnRemoteControl.SetFlat(FALSE);

	m_btnCatoregy.SetIcon(IDI_CATEGORY);
	m_btnCatoregy.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnCatoregy.SetFlat(FALSE);

	m_btnSocketCCDSetup.SetIcon(IDI_CCD_SOCKET_SETUP);
	m_btnSocketCCDSetup.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnSocketCCDSetup.SetFlat(FALSE);

	m_btnCCDSetup.SetIcon(IDI_RT_IMAGE);
	m_btnCCDSetup.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnCCDSetup.SetFlat(FALSE);

	m_btnATCCalibration.SetIcon(IDI_CHAMBER_CALIBRATION);
	m_btnATCCalibration.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnATCCalibration.SetFlat(FALSE);

	m_btnInterFaceSetting.SetIcon(IDI_HEADER_TAIL);
	m_btnInterFaceSetting.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnInterFaceSetting.SetFlat(FALSE);

	m_btnRemoteInput.SetIcon(IDI_REMOTE_INPUT);
	m_btnRemoteInput.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnRemoteInput.SetFlat(FALSE);

	m_btnATCModule.SetIcon(IDI_CHAMBER_SETTING);
	m_btnATCModule.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnATCModule.SetFlat(FALSE);

	m_btnTemperature.SetIcon(IDI_TEMPTERTURE);
	m_btnTemperature.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnTemperature.SetFlat(FALSE);

	m_btnInOutTray.SetIcon(IDI_IN_OUT_TRAY);
	m_btnInOutTray.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnInOutTray.SetFlat(FALSE);

	m_btnRepeatTray.SetIcon(IDI_REPEAT_TRAY);
	m_btnRepeatTray.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnRepeatTray.SetFlat(FALSE);

	m_btnTowerSetting.SetIcon(IDI_TOWER);
	m_btnTowerSetting.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnTowerSetting.SetFlat(FALSE);	

	//
	InitTips();

	// Note: We need set the Text by myself
	SetWindowText("Setup");

	f.ChangeLanguage(GetSafeHwnd());

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
void CPageSetup::InitTips()
{
	// Init Tips
	m_ToolTip.Create(this);
	m_ToolTip.SetMaxTipWidth(800);
	m_ToolTip.SetDelayTime( TTDT_AUTOPOP, 10000 );
	m_ToolTip.SetDelayTime( TTDT_INITIAL, 25 );
	m_ToolTip.EnableToolTips(true);

	//
	m_ToolTip.AddTool( GetDlgItem(IDC_OFFSET),					_T("Handler OffSet Setting") );
	m_ToolTip.AddTool( GetDlgItem(IDC_SPEED),					_T("Handler Arm / Test Site Speed Setting") );
	m_ToolTip.AddTool( GetDlgItem(IDC_TIMER),					_T("Vacc / Cylinder / Tray Transfer Control") );
	m_ToolTip.AddTool( GetDlgItem(IDC_EVENT_LOG),				_T("Handler Event Log") );
	m_ToolTip.AddTool( GetDlgItem(IDC_SITE_SETTING),			_T("Site Setting / OnLine / OffLine / Demo") );
	m_ToolTip.AddTool( GetDlgItem(IDC_YIELD_CTRL),				_T("Yield Control Setting") );
	m_ToolTip.AddTool( GetDlgItem(IDC_DEVICE_SETUP),			_T("Set the Device Information / TrayFile / Catoregy / Interface") );
	m_ToolTip.AddTool( GetDlgItem(IDC_CHANGE_FILE3),			_T("Tray File") );
	m_ToolTip.AddTool( GetDlgItem(IDC_INTERFACE_TESTING),		_T("Communication with Tester Test") );
	m_ToolTip.AddTool( GetDlgItem(IDC_AUTO_RETRY),				_T("Arm Z Pick Auto Retry Setting") );
	m_ToolTip.AddTool( GetDlgItem(IDC_INPUT_TRAY),				_T("Input Tray Control") );
	m_ToolTip.AddTool( GetDlgItem(IDC_IO_MONTIOR),				_T("Handler IO Monitor / Check IO Status / Set IO Output") );
	m_ToolTip.AddTool( GetDlgItem(IDC_ALIGNMENT_SETUP),			_T("Alignment") );
	m_ToolTip.AddTool( GetDlgItem(IDC_EXTEND_FUNCTION),			_T("Extend Function / Rotator / CCD ") );
	m_ToolTip.AddTool( GetDlgItem(IDC_REMOTE_CONTROL),			_T("Remote Control") );
	m_ToolTip.AddTool( GetDlgItem(IDC_CCD_SOCKET),				_T("CCD Socket Setup") );
	m_ToolTip.AddTool( GetDlgItem(IDC_CCD_SETUP),				_T("CCD Pin1 Setup") );
	m_ToolTip.AddTool( GetDlgItem(IDC_ATC_CALIBRATION),			_T("ATC Module Calibration") );
	m_ToolTip.AddTool( GetDlgItem(IDC_ATC_MODULE),				_T("ATC Module") );
	m_ToolTip.AddTool( GetDlgItem(IDC_OUTPUT_TRAY),				_T("Output Tray Control") );
	m_ToolTip.AddTool( GetDlgItem(IDC_REMOTE_INPUT),			_T("Remote Input") );
	m_ToolTip.AddTool( GetDlgItem(IDC_CATOREGY),				_T("Catoregy") );
	m_ToolTip.AddTool( GetDlgItem(IDC_INTERFACE_SETTING),		_T("Interface Setting") );
	m_ToolTip.AddTool( GetDlgItem(IDC_IN_OUT_TRAY),				_T("Tray Mapping Setting") );
	m_ToolTip.AddTool( GetDlgItem(IDC_REPEAT_TRAY),				_T("Repeat Tray") );
	m_ToolTip.AddTool( GetDlgItem(IDC_TOWER_SETTING),			_T("Tower Setting") );
}
void CPageSetup::OnIoMontior() 
{
	f.m_Log.AddEvent(enCodeSetupPageIOMonitor);	// Add Event

	CDlgIOMontior dlg;
	dlg.DoModal();
}

void CPageSetup::OnEventLog() 
{
	f.m_Log.AddEvent(enCodeSetupPageEventLog);	// Add Event

	CDlgEvent dlg(true);
	dlg.DoModal();
}

void CPageSetup::OnAlignmentSetup() 
{
	f.m_Log.AddEvent(enCodeSetupPageAlignment);	// Add Event

	if( f.CheckInitialNeed())
		return;

	CDlgAlignment dlg;
	dlg.DoModal();
}

void CPageSetup::OnDeviceSetup() 
{
//	if( !f.CheckEnaleChange() )
//		return;

	f.m_Log.AddEvent(enCodeSetupPageDeviceSetup);	// Add Event

	CDlgDeviceSetup dlg;
	dlg.DoModal();

	// When we leave the setting page 
	// We have to reset the button status (Show or Hide)
	ReDrawUITrayModuleFunction();
}

void CPageSetup::OnOffset() 
{
	f.m_Log.AddEvent(enCodeSetupPageOffset);	// Add Event

	CDlgOffset dlg;
	dlg.DoModal();
}

void CPageSetup::OnSpeed() 
{
	f.m_Log.AddEvent(enCodeSetupPageSpeed);	// Add Event

	CDlgSpeed dlg;
	dlg.DoModal();
}

void CPageSetup::OnTimer() 
{
	f.m_Log.AddEvent(enCodeSetupPageTimer);	// Add Event

	CDlgTimer dlg;
	dlg.DoModal();
}

void CPageSetup::OnYieldCtrl() 
{
	f.m_Log.AddEvent(enCodeSetupPageYieldControl);	// Add Event

	CDlgYieldControl dlg(true);
	dlg.DoModal();
}

void CPageSetup::OnInterfaceTesting() 
{
	CDlgTestTesting dlg;
	theApp.m_DlgTesting = &dlg;
	dlg.DoModal();
}
void CPageSetup::ReDrawUITrayModuleFunction()
{
	//////////////////////////////////////////////////////////////////////
	// 重設介面 
	RECT rt;
	::GetWindowRect(::GetDlgItem(m_hWnd, IDC_INDEX1), &rt);
	::MapWindowPoints(NULL, m_hWnd, (LPPOINT)&rt, 2);	
	
	RECT rtW[_ICON_Max];
	bool rtUse[_ICON_Max];
	for(int i=0;i<_ICON_Max;i++)
		rtUse[i] = false;

	//
	for(i=0;i<_ICON_Max;i++)
		rtW[i] = rt;
	
	//
	int iButtonWidth		= 0;
	int iButtonHeight		= 0;
	int iButtonWDistance	= 0;
	int iButtonHDistance	= 0;
	GetButtonDistance( iButtonWidth, iButtonHeight, iButtonWDistance, iButtonHDistance );

	// 模組選配功能, 強迫從第5排開始排
	for(i=0;i<_ICON_Max;i++)
	{
		int x = i % _ICON_Max_Row;
		int y = i / _ICON_Max_Row;
		rtW[i].left		= rt.left + ( iButtonWidth * x ) + ( iButtonWDistance * x );
		rtW[i].right	= rt.right	+ ( iButtonWidth * x ) + ( iButtonWDistance * x );

		rtW[i].top		= rt.top + ( iButtonHeight * y ) + ( iButtonHDistance * y );
		rtW[i].bottom	= rt.bottom + ( iButtonHeight * y ) + ( iButtonHDistance * y );
	}

	if( m.UI.FileMain == "" )
	{
		// do not show anything
		m_btnATCModule.ShowWindow( FALSE );
		m_btnATCCalibration.ShowWindow( FALSE );
		m_btnTemperature.ShowWindow( FALSE );
	}
	else
	{
		// ATC Module
		///////////////////////////////////////////////////////////////
		if( m.Setting.m_bEnableATCModule == 1 && 
			m.TraySpec.Heating == theApp.enATCMoudle )
		{
			// ATC Module Setting
			m_btnATCModule.ShowWindow( TRUE );
			for(i=_ICON_Max_Row * _ICON_TrayMod;i<_ICON_Max;i++)
			{
				if( !rtUse[i] )
				{
					rtUse[i] = true;
					m_btnATCModule.MoveWindow(&rtW[i]);
					break;
				}
			}
			
			// ATC Module Calibration
			m_btnATCCalibration.ShowWindow( TRUE );
			for(i=_ICON_Max_Row * _ICON_TrayMod;i<_ICON_Max;i++)
			{
				if( !rtUse[i] )
				{
					rtUse[i] = true;
					m_btnATCCalibration.MoveWindow(&rtW[i]);
					break;
				}
			}
		}
		else
		{
			m_btnATCModule.ShowWindow( FALSE );
			m_btnATCCalibration.ShowWindow( FALSE );
		}	
		///////////////////////////////////////////////////////////////

		// Heater 
		///////////////////////////////////////////////////////////////
		if( m.Setting.m_bEnableHeaterModule == 1 && 
			m.TraySpec.Heating == theApp.enHeater )
		{
			m_btnTemperature.ShowWindow( TRUE );
			for(i=_ICON_Max_Row * _ICON_TrayMod;i<_ICON_Max;i++)
			{
				if( !rtUse[i] )
				{
					rtUse[i] = true;
					m_btnTemperature.MoveWindow(&rtW[i]);
					break;
				}
			}		
		}
		else
		{
			m_btnTemperature.ShowWindow( FALSE );
		}
		///////////////////////////////////////////////////////////////
	}
}
void CPageSetup::ReDrawUIOptionFunction()
{
	//////////////////////////////////////////////////////////////////////
	// 重設介面 
	RECT rt;
	::GetWindowRect(::GetDlgItem(m_hWnd, IDC_INDEX1), &rt);
	::MapWindowPoints(NULL, m_hWnd, (LPPOINT)&rt, 2);	
	
	RECT rtW[_ICON_Max];
	bool rtUse[_ICON_Max];
	for(int i=0;i<_ICON_Max;i++)
		rtUse[i] = false;

	//
	for(i=0;i<_ICON_Max;i++)
		rtW[i] = rt;
	
	//
	int iButtonWidth		= 0;
	int iButtonHeight		= 0;
	int iButtonWDistance	= 0;
	int iButtonHDistance	= 0;
	GetButtonDistance( iButtonWidth, iButtonHeight, iButtonWDistance, iButtonHDistance );

	// 模組選配功能, 強迫從第4排開始排
	for(i=0;i<_ICON_Max;i++)
	{
		int x = i % _ICON_Max_Row;
		int y = i / _ICON_Max_Row;
		rtW[i].left		= rt.left + ( iButtonWidth * x ) + ( iButtonWDistance * x );
		rtW[i].right	= rt.right	+ ( iButtonWidth * x ) + ( iButtonWDistance * x );

		rtW[i].top		= rt.top + ( iButtonHeight * y ) + ( iButtonHDistance * y );
		rtW[i].bottom	= rt.bottom + ( iButtonHeight * y ) + ( iButtonHDistance * y );
	}

	// CCD Socket
	// 判斷是否使用 CCD Socket
	if( m.Setting.m_bEnableCCDSocket == 1 )
	{
		m_btnSocketCCDSetup.ShowWindow( TRUE );
		for(i=_ICON_Max_Row * _ICON_Module;i<_ICON_Max;i++)
		{
			if( !rtUse[i] )
			{
				rtUse[i] = true;
				m_btnSocketCCDSetup.MoveWindow(&rtW[i]);
				break;
			}
		}
	}
	else
	{
		m_btnSocketCCDSetup.ShowWindow( FALSE );
	}

	// CCD Pin1
	// 判斷是否使用 CCD Pin1
	if( m.Setting.m_bEnableCCDPin1 == 1 )
	{
		m_btnCCDSetup.ShowWindow( TRUE );
		for(i=_ICON_Max_Row * _ICON_Module;i<_ICON_Max;i++)
		{
			if( !rtUse[i] )
			{
				rtUse[i] = true;
				m_btnCCDSetup.MoveWindow(&rtW[i]);
				break;
			}
		}
	}
	else
	{
		m_btnCCDSetup.ShowWindow( FALSE );
	}

	// Externd Function
	if( m.Setting.m_bEnableCCDPin1 == 1 || 
		m.Setting.m_bEnableCCDSocket == 1 ||
		m.Setting.m_bRotatoUse == 1 )
	{
		m_btnExtendFunction.ShowWindow( TRUE );	
		for(i=_ICON_Max_Row * _ICON_Module;i<_ICON_Max;i++)
		{
			if( !rtUse[i] )
			{
				rtUse[i] = true;
				m_btnExtendFunction.MoveWindow(&rtW[i]);
				break;
			}
		}

	}
	else
	{
		m_btnExtendFunction.ShowWindow( FALSE );
	}

//
/*
	CButtonST	m_btnATCModule;
	CButtonST	m_btnATCCalibration;
	CButtonST	m_btnCCDSetup;
	CButtonST	m_btnSocketCCDSetup;
	CButtonST	m_btnExtendFunction;
*/

/*
	// Calibration
	// 判斷是否使用 ATC Module 
	if( m.Setting.m_bEnableATCModule == 1 )
	{
		m_btnATCCalibration.ShowWindow( TRUE );
		for(i=0;i<_ICON_Option;i++)
		{
			if( !rtUse[i] )
			{
				rtUse[i] = true;
				m_btnATCCalibration.MoveWindow(&rtW[i]);
				break;
			}
		}
	}
	else
	{
		m_btnATCCalibration.ShowWindow( FALSE );
	}
*/
}
void CPageSetup::GetButtonDistance(int &Width, int &Height, int &WDistance, int &HDistance)
{
	// 取得 Option Button 的寬度, 和兩個按鈕之間的距離.
	CRect Rect;
	GetDlgItem(IDC_INDEX1)->GetClientRect( &Rect );
	Width = Rect.right - Rect.left;
	Height = Rect.bottom - Rect.top;

	//	
	CRect Rect1;
	GetDlgItem(IDC_INDEX1)->GetWindowRect( &Rect1 );
	WDistance = _ICON_W;
	HDistance = _ICON_H;
//	Distance = Rect.right - Rect.left + 5;
}
void CPageSetup::ReDrawUI()
{
	//////////////////////////////////////////////////////////////////////
	// 重設介面
	RECT rt;
	::GetWindowRect(::GetDlgItem(m_hWnd, IDC_INDEX1), &rt);
	::MapWindowPoints(NULL, m_hWnd, (LPPOINT)&rt, 2);	
	
	RECT rtW[_ICON_Max];
	bool rtUse[_ICON_Max];
	for(int i=0;i<_ICON_Max;i++)
		rtUse[i] = false;

	//
	for(i=0;i<_ICON_Max;i++)
		rtW[i] = rt;
	
	//
	int iButtonWidth		= 0;
	int iButtonHeight		= 0;
	int iButtonWDistance	= 0;
	int iButtonHDistance	= 0;
	GetButtonDistance( iButtonWidth, iButtonHeight, iButtonWDistance, iButtonHDistance );

	//
	for(i=0;i<_ICON_Max;i++)
	{
		int x = i % _ICON_Max_Row;
		int y = i / _ICON_Max_Row;
		rtW[i].left		= rt.left + ( iButtonWidth * x ) + ( iButtonWDistance * x );
		rtW[i].right	= rt.right	+ ( iButtonWidth * x ) + ( iButtonWDistance * x );

		rtW[i].top		= rt.top + ( iButtonHeight * y ) + ( iButtonHDistance * y );
		rtW[i].bottom	= rt.bottom + ( iButtonHeight * y ) + ( iButtonHDistance * y );
	}

	// Offset
	if( m.m_SetupPageEnable.m_bEnableOffset	 )
	{
		m_btnOffset.ShowWindow( TRUE );
		for(i=0;i<_ICON_Max;i++)
		{
			if( !rtUse[i] )
			{
				rtUse[i] = true;
				m_btnOffset.MoveWindow(&rtW[i]);
				break;
			}
		}
	}
	else
		m_btnOffset.ShowWindow( FALSE );

	// Speed
	if( m.m_SetupPageEnable.m_bEnableSpeed	 )
	{
		m_btnSpeed.ShowWindow( TRUE );
		for(i=0;i<_ICON_Max;i++)
		{
			if( !rtUse[i] )
			{
				rtUse[i] = true;
				m_btnSpeed.MoveWindow(&rtW[i]);
				break;
			}
		}
	}
	else
		m_btnSpeed.ShowWindow( FALSE );

	// Timer
	if( m.m_SetupPageEnable.m_bEnableTimer )
	{
		m_btnTimer.ShowWindow( TRUE );
		for(i=0;i<_ICON_Max;i++)
		{
			if( !rtUse[i] )
			{
				rtUse[i] = true;
				m_btnTimer.MoveWindow(&rtW[i]);
				break;
			}
		}
	}
	else
		m_btnTimer.ShowWindow( FALSE );

	// Event Log	
	if( m.m_SetupPageEnable.m_bEnableEventLog )
	{
		m_btnEvent.ShowWindow( TRUE );
		for(i=0;i<_ICON_Max;i++)
		{
			if( !rtUse[i] )
			{
				rtUse[i] = true;
				m_btnEvent.MoveWindow(&rtW[i]);
				break;
			}
		}
	}
	else
		m_btnEvent.ShowWindow( FALSE );

	// Sie Setting
	if( m.m_SetupPageEnable.m_bEnableSiteSetting )
	{
		m_btnSiteSetting.ShowWindow( TRUE );
		for(i=0;i<_ICON_Max;i++)
		{
			if( !rtUse[i] )
			{
				rtUse[i] = true;
				m_btnSiteSetting.MoveWindow(&rtW[i]);
				break;
			}
		}
	}
	else
		m_btnSiteSetting.ShowWindow( FALSE );

	// Yield Control
	if( m.m_SetupPageEnable.m_bEnableYieldCtrl )
	{
		m_btnYieldCTRL.ShowWindow( TRUE );
		for(i=0;i<_ICON_Max;i++)
		{
			if( !rtUse[i] )
			{
				rtUse[i] = true;
				m_btnYieldCTRL.MoveWindow(&rtW[i]);
				break;
			}
		}
	}
	else
		m_btnYieldCTRL.ShowWindow( FALSE );

	// Auto Retry
	if( m.m_SetupPageEnable.m_bEnableAutoRetry )
	{
		m_btnAutoRetry.ShowWindow( TRUE );
		for(i=0;i<_ICON_Max;i++)
		{
			if( !rtUse[i] )
			{
				rtUse[i] = true;
				m_btnAutoRetry.MoveWindow(&rtW[i]);
				break;
			}
		}
	}
	else
		m_btnAutoRetry.ShowWindow( FALSE );

	// Device Setup	
	if( m.m_SetupPageEnable.m_bEnableDeviceSetup )
	{
		m_btnDeviceSetup.ShowWindow( TRUE );
		for(i=0;i<_ICON_Max;i++)
		{
			if( !rtUse[i] )
			{
				rtUse[i] = true;
				m_btnDeviceSetup.MoveWindow(&rtW[i]);
				break;
			}
		}
	}
	else
		m_btnDeviceSetup.ShowWindow( FALSE );

	// Tray File
	if( m.m_SetupPageEnable.m_bEnableTrayFile )
	{
		m_btnTrayFile2.ShowWindow( TRUE );
		for(i=0;i<_ICON_Max;i++)
		{
			if( !rtUse[i] )
			{
				rtUse[i] = true;
				m_btnTrayFile2.MoveWindow(&rtW[i]);
				break;
			}
		}
	}
	else
		m_btnTrayFile2.ShowWindow( FALSE );

	// Interface Testing
	if( m.m_SetupPageEnable.m_bEnableIfTesting )
	{
		m_btnInterfaceTesting.ShowWindow( TRUE );
		for(i=0;i<_ICON_Max;i++)
		{
			if( !rtUse[i] )
			{
				rtUse[i] = true;
				m_btnInterfaceTesting.MoveWindow(&rtW[i]);
				break;
			}
		}
	}
	else
		m_btnInterfaceTesting.ShowWindow( FALSE );

	// Catoregy
	if( m.m_SetupPageEnable.m_bEnableCatoregy )
	{
		m_btnCatoregy.ShowWindow( TRUE );
		for(i=0;i<_ICON_Max;i++)
		{
			if( !rtUse[i] )
			{
				rtUse[i] = true;
				m_btnCatoregy.MoveWindow(&rtW[i]);
				break;
			}
		}
	}
	else
		m_btnCatoregy.ShowWindow( FALSE );

	// Interface
	if( m.m_SetupPageEnable.m_bEnableInterface )
	{
		m_btnInterFaceSetting.ShowWindow( TRUE );
		for(i=0;i<_ICON_Max;i++)
		{
			if( !rtUse[i] )
			{
				rtUse[i] = true;
				m_btnInterFaceSetting.MoveWindow(&rtW[i]);
				break;
			}
		}
	}
	else
		m_btnInterFaceSetting.ShowWindow( FALSE );

	// Remote Control
	if( m.m_SetupPageEnable.m_bEnableRemoteControl && m.Setting.m_bEnableRemoteControl == 1 )
	{
		m_btnRemoteControl.ShowWindow( TRUE );
		for(i=0;i<_ICON_Max;i++)
		{
			if( !rtUse[i] )
			{
				rtUse[i] = true;
				m_btnRemoteControl.MoveWindow(&rtW[i]);
				break;
			}
		}
	}
	else
		m_btnRemoteControl.ShowWindow( FALSE );

	// Remote Input 
	if( m.m_SetupPageEnable.m_bEnableRemoteInput && m.Setting.m_bRemoteCustomInput == 1 )
	{
		m_btnRemoteInput.ShowWindow( TRUE );
		for(i=0;i<_ICON_Max;i++)
		{
			if( !rtUse[i] )
			{
				rtUse[i] = true;
				m_btnRemoteInput.MoveWindow(&rtW[i]);
				break;
			}
		}
	}
	else
		m_btnRemoteInput.ShowWindow( FALSE );

	// Input Tray
	if( m.m_SetupPageEnable.m_bEnableInputTray )
	{
		m_btnInputTrayMap.ShowWindow( TRUE );
		for(i=0;i<_ICON_Max;i++)
		{
			if( !rtUse[i] )
			{
				rtUse[i] = true;
				m_btnInputTrayMap.MoveWindow(&rtW[i]);
				break;
			}
		}
	}
	else
		m_btnInputTrayMap.ShowWindow( FALSE );

	// Output Tray
	if( m.m_SetupPageEnable.m_bEnableOutputTray )
	{
		m_btnOutputTrayMap.ShowWindow( TRUE );
		for(i=0;i<_ICON_Max;i++)
		{
			if( !rtUse[i] )
			{
				rtUse[i] = true;
				m_btnOutputTrayMap.MoveWindow(&rtW[i]);
				break;
			}
		}
	}
	else
		m_btnOutputTrayMap.ShowWindow( FALSE );

	// Input Output Tray
	if( m.m_SetupPageEnable.m_bEnableInOutTray )
	{
		m_btnInOutTray.ShowWindow( TRUE );
		for(i=0;i<_ICON_Max;i++)
		{
			if( !rtUse[i] )
			{
				rtUse[i] = true;
				m_btnInOutTray.MoveWindow(&rtW[i]);
				break;
			}
		}
	}
	else
		m_btnInOutTray.ShowWindow( FALSE );

	// IO Monitor
	if( m.m_SetupPageEnable.m_bEnableIOMonitor )
	{
		m_btnIOMonitor.ShowWindow( TRUE );
		for(i=0;i<_ICON_Max;i++)
		{
			if( !rtUse[i] )
			{
				rtUse[i] = true;
				m_btnIOMonitor.MoveWindow(&rtW[i]);
				break;
			}
		}
	}
	else
		m_btnIOMonitor.ShowWindow( FALSE );

	// Alignment 
	if( m.m_SetupPageEnable.m_bEnableAlignment )
	{
		m_btnAlignment.ShowWindow( TRUE );
		for(i=0;i<_ICON_Max;i++)
		{
			if( !rtUse[i] )
			{
				rtUse[i] = true;
				m_btnAlignment.MoveWindow(&rtW[i]);
				break;
			}
		}
	}
	else
		m_btnAlignment.ShowWindow( FALSE );

	// Repeat Tray
	if( m.m_SetupPageEnable.m_bEnableRepeatTray )
	{
		m_btnRepeatTray.ShowWindow( TRUE );
		for(i=0;i<_ICON_Max;i++)
		{
			if( !rtUse[i] )
			{
				rtUse[i] = true;
				m_btnRepeatTray.MoveWindow(&rtW[i]);
				break;
			}
		}
	}
	else
		m_btnRepeatTray.ShowWindow( FALSE );

	// Tower Setting
	if( m.m_SetupPageEnable.m_bEnableTowerSetting )
	{
		m_btnTowerSetting.ShowWindow( TRUE );
		for(i=0;i<_ICON_Max;i++)
		{
			if( !rtUse[i] )
			{
				rtUse[i] = true;
				m_btnTowerSetting.MoveWindow(&rtW[i]);
				break;
			}
		}	
	}
	else
		m_btnTowerSetting.ShowWindow( FALSE );
}
void CPageSetup::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);
	
	if(bShow)
		ReDrawUI();

	// CCD Socket // CCD Pin1
	if(bShow)
		ReDrawUIOptionFunction();

	// Tray Function 
	if(bShow)
		ReDrawUITrayModuleFunction();
}

void CPageSetup::OnSiteSeeing() 
{
	f.m_Log.AddEvent(enCodeSetupPageSiteSetting);	// Add Event

	CDlgSiteSetting dlg;
	dlg.DoModal();	
}

BOOL CPageSetup::PreTranslateMessage(MSG* pMsg) 
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

void CPageSetup::OnInputTray() 
{
	f.m_Log.AddEvent(enCodeSetupPageInputTray);			// Add Event

	if( m.TraySpec.m_InputUseChipTray == 1 )
	{
		// Lance want chip tray 
		const int iSize = 
			( m.TraySpec.m_SubChipTrayColumn * m.TraySpec.m_SubChipTrayRow ) *
			( m.TraySpec.m_SubTrayColumn * m.TraySpec.m_SubTrayRow );
		int *pTray;
		pTray = new int[iSize];
		theApp.m_InputTray.GetStatus(pTray, iSize);
		int iColumn = m.TraySpec.m_SubChipTrayColumn * m.TraySpec.m_SubTrayColumn;
		int iRow	= m.TraySpec.m_SubChipTrayRow * m.TraySpec.m_SubTrayRow;
		CDlgInputTrayMap Dlg( iColumn, iRow, pTray);
		Dlg.DoModal();
		theApp.m_InputTray.SetStatus(pTray, iSize);

		// Clear Memory
		*pTray = NULL;
		delete pTray;
	}
	else
	{
		// Qulcomm want set the input tray.!
		const int iSize = m.TraySpec.Row * m.TraySpec.Column;
		int *pTray;
		pTray = new int[iSize];
		theApp.m_InputTray.GetStatus(pTray, iSize);
		CDlgInputTrayMap Dlg(m.TraySpec.Column, m.TraySpec.Row, pTray);
		Dlg.DoModal();
		theApp.m_InputTray.SetStatus(pTray, iSize);

		// Clear Memory
		*pTray = NULL;
		delete pTray;
	}
}

void CPageSetup::OnAutoRetry() 
{
	f.m_Log.AddEvent(enCodeSetupPageAutoRetry);	// Add Event

	CDlgAutoRetry dlg;
	dlg.DoModal();	
}

void CPageSetup::OnChangeFile3() 
{
	f.m_Log.AddEvent(enCodeSetupPageTrayFile);	// Add Event

	CDlgTrayFileNoHeater dlg;
	dlg.DoModal();
}

void CPageSetup::OnExtendFunction() 
{
	if( m.UI.FileMainTestSetting == "" )
	{
		// 如果還沒有做 Device Setup.! 則不允許打開
		AfxMessageBox("Please Build a new setting in [Device Setup].!");
		return;
	}

	f.m_Log.AddEvent(enCodeSetupPageFunction);	// Add Event

	CDlgExtendFunction dlg;
	dlg.DoModal();
}
bool CPageSetup::CheckRemoteControl() 
{
	bool bOK = true;

	// 機台一定要是建好 Lot 然後沒按下過 Start, 然後是 Initial 過
	/////////////////////////////////////////////////////////////////////////////////////

	if( f.CheckInitialNeed())
		bOK = false;;
	// 如果沒有 Initial 過

	if( m.LotInfo.LotInfoIsLotStart == 0 )
	{
		AfxMessageBox("Please create a new lot.!");
		bOK = false;
	}
	// 如果沒有建過工單

	return bOK;
}
void CPageSetup::OnRemoteControl() 
{
	if( !CheckRemoteControl() )
		return;

	CDlgRemoteControlCustom dlg;
	theApp.m_DlgRemoteControlCustom = &dlg;
	dlg.DoModal();
}

void CPageSetup::OnCatoregy() 
{
	if( m.UI.FileMainTestSetting == "" )
	{
		// 如果還沒有做 Device Setup.! 則不允許打開
		AfxMessageBox("Please Build a new setting in [Device Setup].!");
		return;
	}

	CDlgCategory dlg;
	dlg.DoModal();
}

void CPageSetup::OnCcdSocket() 
{
	CDlgSocketMatch dlg;
	dlg.DoModal();
}

void CPageSetup::OnCcdSetup() 
{
	CDlgVisionSetup dlg;
	dlg.DoModal();
}

void CPageSetup::OnAtcCalibration() 
{
	CDlgATCModuleCalibration dlg;
	dlg.DoModal();
}

void CPageSetup::OnInterfaceSetting() 
{	
	if( m.UI.FileMain == "" )
	{
		// 如果還沒有做 Device Setup.! 則不允許打開
		AfxMessageBox("Please Build a new setting in [Device Setup].!");
		return;
	}

	//
	CString csFile = _T("");
	csFile = m.UI.FileMain.Left( m.UI.FileMain.Find(_SubFileName2, 0));

	//
	CDlgTestSetting dlg( csFile );
	dlg.DoModal();
}

void CPageSetup::OnRemoteInput() 
{
	CDlgRemoteControlCustomInput dlg(m.TraySpec.Column, m.TraySpec.Row );
//	CDlgRemoteControlCustomInput dlg;
	dlg.DoModal();
}

void CPageSetup::OnAtcModule() 
{
	CDlgATCModuleFile dlg;
	dlg.DoModal();
}

void CPageSetup::OnTemperature() 
{
	CDlgTemperature dlg;
	dlg.DoModal();
}

void CPageSetup::OnOutputTray() 
{
	f.m_Log.AddEvent(enCodeSetupPageInputTray);			// Add Event

	if( m.TraySpec.m_InputUseChipTray == 1 )
	{
		// Lance want chip tray 
		const int iSize = 
			( m.TraySpec.m_SubChipTrayColumn * m.TraySpec.m_SubChipTrayRow ) *
			( m.TraySpec.m_SubTrayColumn * m.TraySpec.m_SubTrayRow );
		int *pTray;
		pTray = new int[iSize];
		theApp.m_OutputTray.GetStatus(pTray, iSize);
		int iColumn = m.TraySpec.m_SubChipTrayColumn * m.TraySpec.m_SubTrayColumn;
		int iRow	= m.TraySpec.m_SubChipTrayRow * m.TraySpec.m_SubTrayRow;
		CDlgOutputTrayMap Dlg( iColumn, iRow, pTray);
		Dlg.DoModal();
		theApp.m_OutputTray.SetStatus(pTray, iSize);

		// Clear Memory
		*pTray = NULL;
		delete pTray;
	}
	else
	{
		// Qulcomm want set the input tray.!
		const int iSize = m.TraySpec.Row * m.TraySpec.Column;
		int *pTray;
		pTray = new int[iSize];
		theApp.m_OutputTray.GetStatus(pTray, iSize);
		CDlgOutputTrayMap Dlg(m.TraySpec.Column, m.TraySpec.Row, pTray);
		Dlg.DoModal();
		theApp.m_OutputTray.SetStatus(pTray, iSize);

		// Clear Memory
		*pTray = NULL;
		delete pTray;
	}
}

void CPageSetup::OnInOutTray() 
{
	// 1.0At
	// Remove this and rebuild new one
	/*
	if( m.TraySpec.m_InputUseChipTray == 1 )
	{
		// Lance want chip tray 
		const int iSize = 
			( m.TraySpec.m_SubChipTrayColumn * m.TraySpec.m_SubChipTrayRow ) *
			( m.TraySpec.m_SubTrayColumn * m.TraySpec.m_SubTrayRow );
		int *InputpTray;
		int *OutputpTray;
		InputpTray = new int[iSize];
		OutputpTray = new int[iSize];

		theApp.m_InputTray.GetStatus(InputpTray, iSize);
		theApp.m_OutputTray.GetStatus(OutputpTray, iSize);
			
		int iColumn = m.TraySpec.m_SubChipTrayColumn * m.TraySpec.m_SubTrayColumn;
		int iRow	= m.TraySpec.m_SubChipTrayRow * m.TraySpec.m_SubTrayRow;
		CDlgInOutputTrayMap Dlg( iColumn, iRow, InputpTray, OutputpTray);
		Dlg.DoModal();
		theApp.m_InputTray.SetStatus(InputpTray, iSize);
		theApp.m_OutputTray.SetStatus(OutputpTray, iSize);

		// Clear Memory
		*InputpTray = NULL;
		*OutputpTray = NULL;
		delete InputpTray;
		delete OutputpTray;
	}
	else
	{
		// Qulcomm want set the input tray.!
		const int iSize = m.TraySpec.Row * m.TraySpec.Column;
		int *InputpTray;
		int *OutputpTray;
		InputpTray = new int[iSize];
		OutputpTray = new int[iSize];

		theApp.m_InputTray.GetStatus(InputpTray, iSize);
		theApp.m_OutputTray.GetStatus(OutputpTray, iSize);

		CDlgInOutputTrayMap Dlg(m.TraySpec.Column, m.TraySpec.Row, InputpTray, OutputpTray);
		Dlg.DoModal();
		theApp.m_InputTray.SetStatus(InputpTray, iSize);
		theApp.m_OutputTray.SetStatus(OutputpTray, iSize);

		// Clear Memory
		*InputpTray = NULL;
		*OutputpTray = NULL;
		delete InputpTray;
		delete OutputpTray;
	}
	*/

	if( m.TraySpec.m_InputUseChipTray == 1 )
	{
		// Lance want chip tray 
		const int iSize = 
			( m.TraySpec.m_SubChipTrayColumn * m.TraySpec.m_SubChipTrayRow ) *
			( m.TraySpec.m_SubTrayColumn * m.TraySpec.m_SubTrayRow );
		int *InputpTray;
		int *OutputpTray;
		InputpTray = new int[iSize];
		OutputpTray = new int[iSize];

		theApp.m_InputTray.GetStatus(InputpTray, iSize);
		theApp.m_OutputTray.GetStatus(OutputpTray, iSize);
			
		int iColumn = m.TraySpec.m_SubChipTrayColumn * m.TraySpec.m_SubTrayColumn;
		int iRow	= m.TraySpec.m_SubChipTrayRow * m.TraySpec.m_SubTrayRow;
		CDlgInOutputTrayMap Dlg( iColumn, iRow, InputpTray, OutputpTray);
		Dlg.DoModal();
		theApp.m_InputTray.SetStatus(InputpTray, iSize);
		theApp.m_OutputTray.SetStatus(OutputpTray, iSize);

		// Clear Memory
		*InputpTray = NULL;
		*OutputpTray = NULL;
		delete InputpTray;
		delete OutputpTray;
	}
	else
	{
		///////////////////////////////////////////////////////////////////////////////
		// Repeat Tray Mode
		if( m.m_RepeatTrayCtrl.m_iRepeatTrayMode == theApp.enRepeatTrayInOutCtrl )
		{
			// Repeat Tray
			// Input / Output
			const int iSize = m.TraySpec.Row * m.TraySpec.Column;
			int *Tray1;
			int *Tray2;
			Tray1 = new int[iSize];
			Tray2 = new int[iSize];
			
			theApp.m_Tray1.GetStatus(Tray1, iSize);
			theApp.m_Tray2.GetStatus(Tray2, iSize);
			
			CDlgInOutputTrayMap Dlg(m.TraySpec.Column, m.TraySpec.Row, Tray1, Tray2);
			Dlg.DoModal();
			theApp.m_Tray1.SetStatus(Tray1, iSize);
			theApp.m_Tray2.SetStatus(Tray2, iSize);
			
			// Clear Memory
			*Tray1 = NULL;
			*Tray2 = NULL;
			delete Tray1;
			delete Tray2;
		}
		else if( m.m_RepeatTrayCtrl.m_iRepeatTrayMode == theApp.enRepeatTrayNone )
		{
			// Repeat
			// None (Default)
			const int iSize = m.TraySpec.Row * m.TraySpec.Column;
			int *InputpTray;
			int *OutputpTray;
			InputpTray = new int[iSize];
			OutputpTray = new int[iSize];
			
			theApp.m_InputTray.GetStatus(InputpTray, iSize);
			theApp.m_OutputTray.GetStatus(OutputpTray, iSize);
			
			CDlgInOutputTrayMap Dlg(m.TraySpec.Column, m.TraySpec.Row, InputpTray, OutputpTray);
			Dlg.DoModal();
			theApp.m_InputTray.SetStatus(InputpTray, iSize);
			theApp.m_OutputTray.SetStatus(OutputpTray, iSize);
			
			// Clear Memory
			*InputpTray = NULL;
			*OutputpTray = NULL;
			delete InputpTray;
			delete OutputpTray;
		}
		else if( m.m_RepeatTrayCtrl.m_iRepeatTrayMode == theApp.enRepeatTrayBinningCtrl )
		{
			// Repeat
			// Pass / Fail
			const int iSize = m.TraySpec.Row * m.TraySpec.Column;
			int *InputpTray;
			int *OutputpTray;
			InputpTray = new int[iSize];
			OutputpTray = new int[iSize];
			
			theApp.m_InputTray.GetStatus(InputpTray, iSize);
			theApp.m_OutputTray.GetStatus(OutputpTray, iSize);
			
			CDlgInOutputTrayMap Dlg(m.TraySpec.Column, m.TraySpec.Row, InputpTray, OutputpTray);
			Dlg.DoModal();
			theApp.m_InputTray.SetStatus(InputpTray, iSize);
			theApp.m_OutputTray.SetStatus(OutputpTray, iSize);
			
			// Clear Memory
			*InputpTray = NULL;
			*OutputpTray = NULL;
			delete InputpTray;
			delete OutputpTray;
		}
		///////////////////////////////////////////////////////////////////////////////
		// Not Repeat Tray Mode
		else
		{
			// Default
			const int iSize = m.TraySpec.Row * m.TraySpec.Column;
			int *InputpTray;
			int *OutputpTray;
			InputpTray = new int[iSize];
			OutputpTray = new int[iSize];
			
			theApp.m_InputTray.GetStatus(InputpTray, iSize);
			theApp.m_OutputTray.GetStatus(OutputpTray, iSize);
			
			CDlgInOutputTrayMap Dlg(m.TraySpec.Column, m.TraySpec.Row, InputpTray, OutputpTray);
			Dlg.DoModal();
			theApp.m_InputTray.SetStatus(InputpTray, iSize);
			theApp.m_OutputTray.SetStatus(OutputpTray, iSize);
			
			// Clear Memory
			*InputpTray = NULL;
			*OutputpTray = NULL;
			delete InputpTray;
			delete OutputpTray;
		}
	}
}

void CPageSetup::OnRepeatTray() 
{
	CDlgRepeatTray dlg;
	dlg.DoModal();
}

void CPageSetup::OnTowerSetting() 
{
	CDlgTowerSetting dlg;
	dlg.DoModal();
}
