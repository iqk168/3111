// PageUser.cpp : implementation file
//

#include "stdafx.h"
#include "Deer.h"
#include "DeerDlg.h"
#include "PageUser.h"

// Dlg
#include "DlgYieldControl.h"
#include "DlgLotInformation.h"
#include "DlgSiteSetting.h"
#include "DlgDeviceSetup.h"
#include "DlgSummaryReport.h"
#include "DlgBinMapping.h"
#include "DlgManualContact.h"
#include "DlgManualContactRecover.h"
#include "DlgTestTesting.h"
#include "DlgTrayMapReport.h"
#include "DlgTestResult.h"
#include "DlgTrayRepeatStatus.h"
#include "DlgTrayDef.h"
#include "DlgArmLogICImage.h"
#include "DlgSLTProtocol.h"
#include "DlgSemiAutoFile.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPageUser dialog


CPageUser::CPageUser(CWnd* pParent /*=NULL*/)
	: CDialog(CPageUser::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPageUser)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CPageUser::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPageUser)
	DDX_Control(pDX, IDC_SLT_PROTOCOL,			m_btnSLTProtocol);
	DDX_Control(pDX, IDC_ARM_LOG_IC_LIST,		m_btnArmLogICList);
	DDX_Control(pDX, IDC_ARM_LOG_IMAGE,			m_btnArmLogImage);
	DDX_Control(pDX, IDC_TRAY_DEF_COLOR,		m_btnTrayDefColor);
	DDX_Control(pDX, IDC_REPEAT_TRAY_STATUS,	m_btnRepeatTrayStatus);
	DDX_Control(pDX, IDC_TEST_RESULT,			m_btnTestResult);
	DDX_Control(pDX, IDC_TS_VACC,				m_btnTestSiteVacc);
	DDX_Control(pDX, IDC_TRAY_MAP_REPORT,		m_btnTrayMapReport);
	DDX_Control(pDX, IDC_INTERFACE_TESTING,		m_btnInterfaceTesting);
	DDX_Control(pDX, IDC_SUMMARY_REPORT,		m_btnSummaryReport);
	DDX_Control(pDX, IDC_MANUAL_CONTACT,		m_btnManualContact);
	DDX_Control(pDX, IDC_DEVICE_SETUP,			m_btnDeviceSetup);
	DDX_Control(pDX, IDC_SITE_SETTING,			m_btnSiteSetting);
	DDX_Control(pDX, IDC_VISUAL_PANEL,			m_btnVisualButton);
	DDX_Control(pDX, IDC_LOT_INFORMATION,		m_btnLotInformation);
	DDX_Control(pDX, IDC_TRAY_AUTO_SKIP,		m_btnAutoSkip);
	DDX_Control(pDX, IDC_YIELD_CTRL,			m_btnYieldCTRL);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPageUser, CDialog)
	//{{AFX_MSG_MAP(CPageUser)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_YIELD_CTRL,				OnYieldCtrl)
	ON_BN_CLICKED(IDC_TRAY_AUTO_SKIP,			OnTrayAutoSkip)
	ON_BN_CLICKED(IDC_LOT_INFORMATION,			OnLotInformation)
	ON_BN_CLICKED(IDC_VISUAL_PANEL,				OnVisualPanel)
	ON_BN_CLICKED(IDC_SITE_SETTING,				OnSiteSetting)
	ON_BN_CLICKED(IDC_DEVICE_SETUP,				OnDeviceSetup)
	ON_WM_SHOWWINDOW()
	ON_BN_CLICKED(IDC_SUMMARY_REPORT,			OnSummaryReport)
	ON_BN_CLICKED(IDC_MANUAL_CONTACT,			OnManualContact)
	ON_BN_CLICKED(IDC_INTERFACE_TESTING,		OnInterfaceTesting)
	ON_BN_CLICKED(IDC_TRAY_MAP_REPORT,			OnTrayMapReport)
	ON_BN_CLICKED(IDC_TS_VACC,					OnTsVacc)
	ON_BN_CLICKED(IDC_TEST_RESULT,				OnTestResult)
	ON_BN_CLICKED(IDC_REPEAT_TRAY_STATUS,		OnRepeatTrayStatus)
	ON_BN_CLICKED(IDC_TRAY_DEF_COLOR,			OnTrayDefColor)
	ON_BN_CLICKED(IDC_ARM_LOG_IMAGE,			OnArmLogImage)
	ON_BN_CLICKED(IDC_ARM_LOG_IC_LIST,			OnArmLogIcList)
	ON_BN_CLICKED(IDC_SLT_PROTOCOL,				OnSltProtocol)
	ON_BN_CLICKED(IDC_DEBUG, OnDebug)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPageUser message handlers

BOOL CPageUser::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// init button 
	m_btnYieldCTRL.SetIcon(IDI_FLOW_CHAR);
	m_btnYieldCTRL.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnYieldCTRL.SetFlat(FALSE);

	//
	InitICON();
	
	// Auto Skip
	m_btnAutoSkip.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnAutoSkip.SetFlat(FALSE);

	// LotInformation
	m_btnLotInformation.SetIcon(IDI_CHECK_BOOK);
	m_btnLotInformation.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnLotInformation.SetFlat(FALSE);

	// Visual Panel
	m_btnVisualButton.SetIcon(IDI_VISUAL_PANEL1);
	m_btnVisualButton.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnVisualButton.SetFlat(FALSE);
	
	// Site Setting
	m_btnSiteSetting.SetIcon(IDI_SITE_SETTING);
	m_btnSiteSetting.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnSiteSetting.SetFlat(FALSE);

	// Manual Contact
	m_btnManualContact.SetIcon(IDI_MANUAL_CONTACT);
	m_btnManualContact.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnManualContact.SetFlat(FALSE);

	// Device Setup
	m_btnDeviceSetup.SetIcon(IDI_DEVICE);
	m_btnDeviceSetup.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnDeviceSetup.SetFlat(FALSE);

	// Summary Report							   
	m_btnSummaryReport.SetIcon(IDI_SUMMARY_REPORT);
	m_btnSummaryReport.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnSummaryReport.SetFlat(FALSE);

	// Interface Testing
	m_btnInterfaceTesting.SetIcon(IDI_INTER_FACE_TESTING);
	m_btnInterfaceTesting.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnInterfaceTesting.SetFlat(FALSE);

	// Tray Map Report
	m_btnTrayMapReport.SetIcon(IDI_TRAY_MAP_REPORT);
	m_btnTrayMapReport.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnTrayMapReport.SetFlat(FALSE);

	// Test Site Vacc
//	m_btnTestSiteVacc.SetIcon(IDI_SOCKET_VACC);
	m_btnTestSiteVacc.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnTestSiteVacc.SetFlat(FALSE);

	// Test Result
	m_btnTestResult.SetIcon(IDI_TEST_RESULT);
	m_btnTestResult.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnTestResult.SetFlat(FALSE);

	// Repeat Tray Status
	m_btnRepeatTrayStatus.SetIcon(IDI_REPEAT_TRAY_STATUS);
	m_btnRepeatTrayStatus.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnRepeatTrayStatus.SetFlat(FALSE);
	
	// Tray Def Color
	m_btnTrayDefColor.SetIcon(IDI_TRAY_COLOR);
	m_btnTrayDefColor.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnTrayDefColor.SetFlat(FALSE);

	// Arm Log IC
//	m_btnArmLogImage.SetIcon(IDI_ARM_LOG_ICIMG);
	m_btnArmLogImage.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnArmLogImage.SetFlat(FALSE);

	// Arm Log IC List
	m_btnArmLogICList.SetIcon(IDI_ARM_LOG_ICIMG);
	m_btnArmLogICList.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnArmLogICList.SetFlat(FALSE);

	// SLT Protocol
	m_btnSLTProtocol.SetIcon(IDI_SLT_PROTOCOL);
	m_btnSLTProtocol.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnSLTProtocol.SetFlat(FALSE);

	//
	InitTips();
	
	SetWindowText("User");

	f.ChangeLanguage(GetSafeHwnd());
		
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
void CPageUser::InitICON()
{
	// Auto Skip
	if( m.TraySkip.AutoSkip == 1 )
		m_btnAutoSkip.SetIcon(IDI_TRAY_AUTO_SKIP);
	else
		m_btnAutoSkip.SetIcon(IDI_TRAY_NOT_AUTO_SKIP);

	// Test Site Vacc
	if( m.TraySkip.TestSiteVacc == 1 )
		m_btnTestSiteVacc.SetIcon(IDI_SOCKET_VACC);
	else
		m_btnTestSiteVacc.SetIcon(IDI_SOCKET_NO_VACC);

	// Arm Log IC
	if( m.m_ArmLogICImage.bEnableArmLogICImage == 1 )
		m_btnArmLogImage.SetIcon(IDI_ARM_LOG_ICIMG);
	else
		m_btnArmLogImage.SetIcon(IDI_ARM_LOG_ICIMG_NO);
}
void CPageUser::InitTips()
{
	// Init Tips
	m_ToolTip.Create(this);
	m_ToolTip.SetMaxTipWidth(800);
	m_ToolTip.SetDelayTime( TTDT_AUTOPOP, 10000 );
	m_ToolTip.SetDelayTime( TTDT_INITIAL, 25 );
	m_ToolTip.EnableToolTips(true);

	//
	m_ToolTip.AddTool( GetDlgItem(IDC_SITE_SETTING),				_T("Change Handler Mode / OnLine / OffLine / Demo") );
	m_ToolTip.AddTool( GetDlgItem(IDC_TRAY_AUTO_SKIP),				_T("Arm Pick IC Auto Skip Or Not") );
	m_ToolTip.AddTool( GetDlgItem(IDC_LOT_INFORMATION),				_T("Lot Information / Lot Detail Information") );
	m_ToolTip.AddTool( GetDlgItem(IDC_DEVICE_SETUP),				_T("Set the Device Information / TrayFile / Catoregy / Interface") );
	m_ToolTip.AddTool( GetDlgItem(IDC_MANUAL_CONTACT),				_T("Manual Contact") );
	m_ToolTip.AddTool( GetDlgItem(IDC_YIELD_CTRL),					_T("Yield Control Setting") );
	m_ToolTip.AddTool( GetDlgItem(IDC_VISUAL_PANEL),				_T("Handler Visual Panel") );
	m_ToolTip.AddTool( GetDlgItem(IDC_SUMMARY_REPORT),				_T("View Summary Report") );
	m_ToolTip.AddTool( GetDlgItem(IDC_INTERFACE_TESTING),			_T("Interface Testing") );
	m_ToolTip.AddTool( GetDlgItem(IDC_TRAY_MAP_REPORT),				_T("Tray Map Report") );
	m_ToolTip.AddTool( GetDlgItem(IDC_TS_VACC),						_T("Test Site Vaccuum Control") );
	m_ToolTip.AddTool( GetDlgItem(IDC_TEST_RESULT),					_T("Test Result Report") );
	m_ToolTip.AddTool( GetDlgItem(IDC_REPEAT_TRAY_STATUS),			_T("Repeat Tray Status") );
	m_ToolTip.AddTool( GetDlgItem(IDC_TRAY_DEF_COLOR),				_T("Tray Define Color") );
	m_ToolTip.AddTool( GetDlgItem(IDC_ARM_LOG_IMAGE),				_T("Arm Log Image") );
	m_ToolTip.AddTool( GetDlgItem(IDC_SLT_PROTOCOL),				_T("SLT Protocol") );
}
void CPageUser::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	
	CDialog::OnTimer(nIDEvent);
}
void CPageUser::GetButtonDistance(int &Width, int &Height, int &WDistance, int &HDistance)
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
void CPageUser::OnYieldCtrl() 
{
	f.m_Log.AddEvent(enCodeUserPageYieldControl);	// Add Event

	CDlgYieldControl dlg;
	dlg.DoModal();
}

void CPageUser::ResetUserPageAutoSkip()
{
	if( m.TraySkip.AutoSkip == 1 )
		m_btnAutoSkip.SetIcon(IDI_TRAY_AUTO_SKIP);
	else
		m_btnAutoSkip.SetIcon(IDI_TRAY_NOT_AUTO_SKIP);
	// Note: Change the icon image

	f.SaveSetting();
	// Note: m.TraySkip.AutoSkip == 1 表示會 Auto Skip, 
	// 如果 m.TraySkip.AutoSkip == 0 表示會 Alarm
}
void CPageUser::OnTrayAutoSkip() 
{
	if( m.TraySkip.AutoSkip == 1 )
	{		
		f.m_Log.AddEvent(enCodeUserPageTrayNoSkip);	// Add Event
		m.TraySkip.AutoSkip = 0;
		// Ebable the function of Input Stack Auto Skip
	}
	else
	{
		f.m_Log.AddEvent(enCodeUserPageTrayAutoSkip);	// Add Event		
		m.TraySkip.AutoSkip = 1;
		// Disable the function of Input Stack Auto Skip
	}
	// Note: Reset the setting

	if( m.TraySkip.AutoSkip == 1 )
		m_btnAutoSkip.SetIcon(IDI_TRAY_AUTO_SKIP);
	else
		m_btnAutoSkip.SetIcon(IDI_TRAY_NOT_AUTO_SKIP);
	// Note: Change the icon image

	f.SaveSetting();
	// Note: m.TraySkip.AutoSkip == 0 表示會 Auto Skip, 
	// 如果 m.TraySkip.AutoSkip == 1 表示會 Alarm
}

void CPageUser::OnLotInformation() 
{
	f.m_Log.AddEvent(enCodeUserPageLotInformation);	// Add Event

	CDlgLotInformation dlg;
	dlg.DoModal();
}

void CPageUser::OnVisualPanel() 
{
	if(theApp.m_DlgVisualButton.GetSafeHwnd() == NULL)
		theApp.m_DlgVisualButton.Create(CDlgVisualButton::IDD);
	
	theApp.m_DlgVisualButton.ShowWindow(SW_SHOW);
}

BOOL CPageUser::PreTranslateMessage(MSG* pMsg) 
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

void CPageUser::OnSiteSetting() 
{
	f.m_Log.AddEvent(enCodeDebugPageSiteSetting);	// Add Event

	CDlgSiteSetting dlg;
	dlg.DoModal();	
}

void CPageUser::OnDeviceSetup() 
{
	f.m_Log.AddEvent(enCodeUserPageDeviceSetup);	// Add Event

	CDlgDeviceSetup dlg;
	dlg.DoModal();	
}

void CPageUser::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);
	
	if(bShow)	
		ReDrawUI();

	if(bShow)
		ReDrawAutoSkip();

	if(bShow)
		ReDrawTestSiteVaccOff();
}
void CPageUser::ReDrawTestSiteVaccOff()
{
	if( m.TraySkip.TestSiteVacc == 1 )
		m_btnTestSiteVacc.SetIcon(IDI_SOCKET_VACC);
	else
		m_btnTestSiteVacc.SetIcon(IDI_SOCKET_NO_VACC);
}
void CPageUser::ReDrawAutoSkip()
{
	if( m.TraySkip.AutoSkip == 1 )
		m_btnAutoSkip.SetIcon(IDI_TRAY_AUTO_SKIP);
	else
		m_btnAutoSkip.SetIcon(IDI_TRAY_NOT_AUTO_SKIP);
}
void CPageUser::ReDrawUI()
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

	// Site setting
	if( m.m_UserPageEnable.m_bEnableSiteSetting )
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

	// Lot Infomation
	if( m.m_UserPageEnable.m_bEnableLotInformation )
	{
		m_btnLotInformation.ShowWindow( TRUE );
		for(i=0;i<_ICON_Max;i++)
		{
			if( !rtUse[i] )
			{
				rtUse[i] = true;
				m_btnLotInformation.MoveWindow(&rtW[i]);
				break;
			}
		}
	}
	else
		m_btnLotInformation.ShowWindow( FALSE );

	// Device Setup
	if( m.m_UserPageEnable.m_bEnableDeviceSetup )
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

	// Manual Contact
	if( m.m_UserPageEnable.m_bEnableManualContact )
	{
		m_btnManualContact.ShowWindow( TRUE );
		for(i=0;i<_ICON_Max;i++)
		{
			if( !rtUse[i] )
			{
				rtUse[i] = true;
				m_btnManualContact.MoveWindow(&rtW[i]);
				break;
			}
		}
	}
	else
		m_btnManualContact.ShowWindow( FALSE );

	// Yield Control
	if( m.m_UserPageEnable.m_bEnableYieldCtrl )
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

	// Visual Button
	if( m.m_UserPageEnable.m_bEnableVisualPanel )
	{
		m_btnVisualButton.ShowWindow( TRUE );
		for(i=0;i<_ICON_Max;i++)
		{
			if( !rtUse[i] )
			{
				rtUse[i] = true;
				m_btnVisualButton.MoveWindow(&rtW[i]);
				break;
			}
		}
	}
	else
		m_btnVisualButton.ShowWindow( FALSE );

	// Auto Skip Button
	if( m.m_UserPageEnable.m_bEnableAutoSkip )
	{
		m_btnAutoSkip.ShowWindow( TRUE );
		for(i=0;i<_ICON_Max;i++)
		{
			if( !rtUse[i] )
			{
				rtUse[i] = true;
				m_btnAutoSkip.MoveWindow(&rtW[i]);
				break;
			}
		}
	}
	else
		m_btnAutoSkip.ShowWindow( FALSE );

	// Summary Report
	if( m.m_UserPageEnable.m_bEnableSummaryReport && m.Setting.m_bSummaryReport == 1 )
	{
		m_btnSummaryReport.ShowWindow( TRUE );
		for(i=0;i<_ICON_Max;i++)
		{
			if( !rtUse[i] )
			{
				rtUse[i] = true;
				m_btnSummaryReport.MoveWindow(&rtW[i]);
				break;
			}
		}
	}
	else
		m_btnSummaryReport.ShowWindow( FALSE );

	// Interface Testing
	if( m.m_UserPageEnable.m_bEnableIfTesting )
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

	// Tray Map Report
	if( m.m_UserPageEnable.m_bEnableTrayMapReport )
	{
		m_btnTrayMapReport.ShowWindow( TRUE );
		for(i=0;i<_ICON_Max;i++)
		{
			if( !rtUse[i] )
			{
				rtUse[i] = true;
				m_btnTrayMapReport.MoveWindow(&rtW[i]);
				break;
			}
		}
	}
	else
		m_btnTrayMapReport.ShowWindow( FALSE );

	// Test Site Vacc
	if( m.m_UserPageEnable.m_bTestSiteVaccOn )
	{
		m_btnTestSiteVacc.ShowWindow( TRUE );
		for(i=0;i<_ICON_Max;i++)
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
		m_btnTestSiteVacc.ShowWindow( FALSE );

	// Test Site Result
	if( m.m_UserPageEnable.m_bTestResultReport )
	{
		m_btnTestResult.ShowWindow( TRUE );
		for(i=0;i<_ICON_Max;i++)
		{
			if( !rtUse[i] )
			{
				rtUse[i] = true;
				m_btnTestResult.MoveWindow(&rtW[i]);
				break;
			}
		}
	}
	else
		m_btnTestResult.ShowWindow( FALSE );
	
	// Repeat Tray Status
	if( m.m_UserPageEnable.m_bRepeatTrayStatus )
	{
		m_btnRepeatTrayStatus.ShowWindow( TRUE );
		for(i=0;i<_ICON_Max;i++)
		{
			if( !rtUse[i] )
			{
				rtUse[i] = true;
				m_btnRepeatTrayStatus.MoveWindow(&rtW[i]);
				break;
			}
		}
	}
	else
		m_btnRepeatTrayStatus.ShowWindow( FALSE );

	// Tray Def Color
	if( m.m_UserPageEnable.m_bTrayDefColor )
	{
		m_btnTrayDefColor.ShowWindow( TRUE );
		for(i=0;i<_ICON_Max;i++)
		{
			if( !rtUse[i] )
			{
				rtUse[i] = true;
				m_btnTrayDefColor.MoveWindow(&rtW[i]);
				break;
			}
		}
	}
	else
		m_btnTrayDefColor.ShowWindow( FALSE );

	// Arm Log Image
	if( m.m_UserPageEnable.m_bArmLogICImage )
	{
		m_btnArmLogImage.ShowWindow( TRUE );
		for(i=0;i<_ICON_Max;i++)
		{
			if( !rtUse[i] )
			{
				rtUse[i] = true;
				m_btnArmLogImage.MoveWindow(&rtW[i]);
				break;
			}
		}
	}
	else
		m_btnArmLogImage.ShowWindow( FALSE );

	/*
	// Arm Log IC List
	if( m.m_UserPageEnable.m_bArmLogICImage )
	{
		m_btnArmLogICList.ShowWindow( TRUE );
		for(i=0;i<_ICON_Max;i++)
		{
			if( !rtUse[i] )
			{
				rtUse[i] = true;
				m_btnArmLogICList.MoveWindow(&rtW[i]);
				break;
			}
		}
	}
	else
		m_btnArmLogICList.ShowWindow( FALSE );
	*/

	// SLT Protocol
	if( m.m_UserPageEnable.m_bSLTProtocol )
	{
		m_btnSLTProtocol.ShowWindow( TRUE );
		for(i=0;i<_ICON_Max;i++)
		{
			if( !rtUse[i] )
			{
				rtUse[i] = true;
				m_btnSLTProtocol.MoveWindow(&rtW[i]);
				break;
			}
		}	
	}
	else
		m_btnSLTProtocol.ShowWindow( FALSE );
}

void CPageUser::OnSummaryReport() 
{
	CDlgSummaryReport dlg;
	dlg.DoModal();
	f.m_Log.AddEvent(enCodeUserPageSummaryReport);	// Add Event
}

void CPageUser::OnManualContact() 
{
	f.m_Log.AddEvent(enCodeUserPageManualContact);	// Add Event
	// 1.0Ah
#ifdef _Demo
	CDlgManualContact dlg;
	theApp.m_DlgManualContact = &dlg;
	dlg.DoModal();
	return;
#endif


	if( !f.CheckInitialNeed())
	{
		CDlgManualContact dlg;
		theApp.m_DlgManualContact = &dlg;
		dlg.DoModal();
	}
	else
	{
		// System is not in Ready 
	}
}

void CPageUser::OnInterfaceTesting() 
{
	CDlgTestTesting dlg;
	theApp.m_DlgTesting = &dlg;
	dlg.DoModal();
	f.m_Log.AddEvent(enCodeUserPageInterfaceTest);	// Add Event
}

void CPageUser::OnTrayMapReport() 
{
	CDlgTrayMapReport dlg;
	dlg.DoModal();
	f.m_Log.AddEvent(enCodeUserPageTrayMapReport);	// Add Event
}

void CPageUser::OnTsVacc() 
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
	f.m_Log.AddEvent(enCodeUserPageTestSiteVcc);	// Add Event
}

void CPageUser::OnTestResult() 
{
	CDlgTestResult dlg;
	dlg.DoModal();
}

void CPageUser::OnRepeatTrayStatus() 
{
	if(theApp.m_DlgTrayRepeatStatus.GetSafeHwnd() == NULL)
		theApp.m_DlgTrayRepeatStatus.Create(CDlgTrayRepeatStatus::IDD);
	
	theApp.m_DlgTrayRepeatStatus.ShowWindow(SW_SHOW);
}

void CPageUser::OnTrayDefColor() 
{
	CDlgTrayDef dlg(true);
	dlg.DoModal();	
}

void CPageUser::OnArmLogImage() 
{
	if( m.m_ArmLogICImage.bEnableArmLogICImage == 1 )
		m.m_ArmLogICImage.bEnableArmLogICImage = 0;
	else
		m.m_ArmLogICImage.bEnableArmLogICImage = 1;

	if( m.m_ArmLogICImage.bEnableArmLogICImage == 1 )
		m_btnArmLogImage.SetIcon(IDI_ARM_LOG_ICIMG);
	else
		m_btnArmLogImage.SetIcon(IDI_ARM_LOG_ICIMG_NO);

	f.SaveArmLogICImage();
}

void CPageUser::OnArmLogIcList() 
{
	CDlgArmLogICImage dlg;
	dlg.DoModal();	
}

void CPageUser::OnSltProtocol() 
{
	CDlgSLTProtocol dlg;
	theApp.m_DlgSLTProtocol = &dlg;
	dlg.DoModal();
	f.m_Log.AddEvent(enCodeUserPageSLTProtocol);	// Add Event
}

void CPageUser::OnDebug() 
{
	// TODO: Add your control notification handler code here

// 	double score = f.CCDMatch(m.FilePath.CCDPin1ImagePath,m.UI.Pin1PatternName, m.m_CCDPin1Control.iCCDUse
// 		, m.CCDPin1.iMatchROIX, m.CCDPin1.iMatchROIY, m.CCDPin1.iMatchWidth
// 		, m.CCDPin1.iMatchHeight, m.CCDPin1.dMatchMinScore);
// 	double score1 = f.CCDMatch(m.FilePath.CCDSocketImagePath,m.UI.SocketPatternName, m.m_CCDSocketControl.iCCDUse
// 		, m.CCDSocket.iMatchROIX, m.CCDSocket.iMatchROIY, m.CCDSocket.iMatchWidth
// 		 , m.CCDSocket.iMatchHeight, m.CCDSocket.dMatchMinScore);

	
	CString csfile;
	m.FilePath.SemiAutoPath = ".\\SemiAuto\\a.log";
	m.CmdSet.RemoveAll();
	CString FileName = m.FilePath.SemiAutoPath;
	CStdioFile CSVFile;
	CFileException FileException;
	tagCmd tmp;	//暫存結構
	if(CSVFile.Open(FileName,CFile::typeText|CFile::modeRead),&FileException)//unicode使用typeBinary
	{
		CSVFile.SeekToBegin();
		CString str1,strSubString;
		while(CSVFile.ReadString(str1)!=0)
		{
			bool flag = false;
			flag = f.ReadSemiAutoCommand(str1,tmp);
			m.CmdSet.Add(tmp);	//依序加入CmdSet
			int numTemper = tmp.Temper.size();
			tmp.Temper.clear();		//清除所有暫存的溫度值
		}
	}
	else
	{
		AfxMessageBox(_T("Can't open file"));
	}
	CSVFile.Close();

	theApp.m_InputTray.ChangeTray();

// 	CDlgSemiAutoFile dlg;
// 	dlg.DoModal();
}
