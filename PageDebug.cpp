// PageDebug.cpp : implementation file
//

#include "stdafx.h"
#include "Deer.h"
#include "DeerDlg.h"
#include "PageDebug.h"

// Dlg
#include "DlgDebugFunction.h"
#include "DlgGearRation.h"
#include "DlgLotInformation.h"
#include "DlgLotInformationDone.h"
#include "DlgSiteSetting.h"
#include "DlgSetting.h"
#include "DlgTimer.h"
#include "DlgTimerSetting.h"
#include "DlgTrayFile.h"
#include "DlgTrayFileNoHeater.h"
#include "DlgFilePath.h"
#include "DlgTrayMapUI.h"
#include "DlgHotKey.h"
#include "DlgContactCounter.h"					 
#include "DlgMail.h"							 
#include "DlgPasswordRead.h"
#include "DlgAlignment.h"
#include "DlgAlignmentPw.h"
#include "DlgBasicSetting.h"
#include "DlgATCMonitor.h"
#include "DlgHandlerComPort.h"
#include "DlgCameraSetting.h"
#include "DlgTorqueControl.h"
#include "DlgAlignmentCheck.h"
#include "DlgUPHTool.h"
#include "DlgCustomPageFunction.h"
#include "DlgTorqueControl.h"
#include "DlgCommunication.h"
#include "DlgCustomMCFunction.h"
#include "DlgTorqueTool.h"
#include "DlgRepeatTrayEnable.h"
#include "DlgTrayDef.h"
#include "DlgArmLogICImage.h"
//

#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <io.h>
#include <stdio.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPageDebug dialog


CPageDebug::CPageDebug(CWnd* pParent /*=NULL*/)
	: CDialog(CPageDebug::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPageDebug)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CPageDebug::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPageDebug)
	DDX_Control(pDX, IDC_ARM_LOGIC,						m_btnArmLogIC);
	DDX_Control(pDX, IDC_TRAY_COLOR,					m_btnTrayDefColor);
	DDX_Control(pDX, IDC_REPEAT_TRAY_ENABLE,			m_btnRepeatTrayEnable);
	DDX_Control(pDX, IDC_MANUAL_ENABLE,					m_btnManualEnable);
	DDX_Control(pDX, IDC_PAGE_FUNCTION,					m_btnPageFunction);
	DDX_Control(pDX, IDC_PID_CONTROL,					m_btnTSPIDValve);
	DDX_Control(pDX, IDC_ATC_MONITOR,					m_btnATCMonitor);
	DDX_Control(pDX, IDC_CCD_CAMERA,					m_btnCameraSetting);
	DDX_Control(pDX, IDC_TRAY_UI,						m_btnTrayMapUI);
	DDX_Control(pDX, IDC_HANDLER_COM_SETTING,			m_btnHandlerComPortSetting);
	DDX_Control(pDX, IDC_FILE_PATH,						m_btnFilePath);
	DDX_Control(pDX, IDC_COMMUNICATION,					m_btnCommunication);
	DDX_Control(pDX, IDC_BASIC_SETTING,					m_btnBasicSetting);
	DDX_Control(pDX, IDC_UPH,							m_btnUPH);
	DDX_Control(pDX, IDC_ALIGNMENT,						m_btnAlignmentCheck);
	DDX_Control(pDX, IDC_INPUT_TRAY_CHIP,				m_btnChipTrayMapInput);
	DDX_Control(pDX, IDC_MAIL,							m_btnMail);
	DDX_Control(pDX, IDC_TEST_PROGRAM,					m_btnSLTFile);
	DDX_Control(pDX, IDC_TORQUE_SETUP,					m_btnTorqueSetup);
	DDX_Control(pDX, IDC_ALIGNMENT_SETUP,				m_btnAlignment);
	DDX_Control(pDX, IDC_TIMER_SETTING,					m_btnTimerSetting);
	DDX_Control(pDX, IDC_TIMER,							m_btnTimer);
	DDX_Control(pDX, IDC_HANDLER_SETTING,				m_btnSetting);
	DDX_Control(pDX, IDC_LANGUAGE,						m_btnLanguage);
	DDX_Control(pDX, IDC_GEAR_RATION,					m_btnGearRation);
	DDX_Control(pDX, IDC_DEBUG_FUNCTION,				m_btnDebugFunction);
	DDX_Control(pDX, IDC_CHANGE_FILE2,					m_btnChangeFile);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CPageDebug, CDialog)
	//{{AFX_MSG_MAP(CPageDebug)
	ON_BN_CLICKED(IDC_DEBUG_FUNCTION,					OnDebugFunction)
	ON_BN_CLICKED(IDC_LANGUAGE,							OnLanguage)
	ON_BN_CLICKED(IDC_GEAR_RATION,						OnGearRation)
	ON_BN_CLICKED(IDC_HANDLER_SETTING,					OnHandlerSetting)
	ON_BN_CLICKED(IDC_TIMER,							OnTimer)
	ON_BN_CLICKED(IDC_TIMER_SETTING,					OnTimerSetting)	
	ON_BN_CLICKED(IDC_ALIGNMENT_SETUP,					OnAlignmentSetup)
	ON_BN_CLICKED(IDC_CHANGE_FILE2,						OnChangeFile)
	ON_BN_CLICKED(IDC_TORQUE_SETUP,						OnTorqueSetup)
	ON_BN_CLICKED(IDC_TEST_PROGRAM,						OnTestProgram)
	ON_BN_CLICKED(IDC_MAIL,								OnMail)
	ON_BN_CLICKED(IDC_INPUT_TRAY_CHIP,					OnInputTrayChip)
	ON_BN_CLICKED(IDC_ALIGNMENT,						OnAlignment)
	ON_BN_CLICKED(IDC_UPH,								OnUph)
	ON_BN_CLICKED(IDC_BASIC_SETTING,					OnBasicSetting)
	ON_BN_CLICKED(IDC_COMMUNICATION,					OnCommunication)
	ON_BN_CLICKED(IDC_FILE_PATH,						OnFilePath)
	ON_BN_CLICKED(IDC_HANDLER_COM_SETTING,				OnHandlerComSetting)
	ON_BN_CLICKED(IDC_TRAY_UI,							OnTrayUi)
	ON_BN_CLICKED(IDC_CCD_CAMERA,						OnCcdCamera)
	ON_BN_CLICKED(IDC_HOT_KEY,							OnHotKey)
	ON_BN_CLICKED(IDC_PW,								OnPw)
	ON_BN_CLICKED(IDC_ATC_MONITOR,						OnAtcMonitor)
	ON_BN_CLICKED(IDC_PID_CONTROL,						OnPidControl)
	ON_WM_SHOWWINDOW()
	ON_BN_CLICKED(IDC_PAGE_FUNCTION,					OnPageFunction)
	ON_BN_CLICKED(IDC_MANUAL_ENABLE,					OnManualEnable)
	ON_BN_CLICKED(IDC_REPEAT_TRAY_ENABLE,				OnRepeatTrayEnable)
	ON_BN_CLICKED(IDC_TRAY_COLOR,						OnTrayColor)
	ON_BN_CLICKED(IDC_ARM_LOGIC,						OnArmLogic)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPageDebug message handlers

BOOL CPageDebug::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// init button
	m_btnChangeFile.SetIcon(IDI_FILE);;
	m_btnChangeFile.SetAlign(CButtonST::ST_ALIGN_VERT);;
	m_btnChangeFile.SetFlat(FALSE);

	m_btnDebugFunction.SetIcon(IDI_DEBUG);
	m_btnDebugFunction.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnDebugFunction.SetFlat(FALSE);

	m_btnGearRation.SetIcon(IDI_GEAR_RATION);
	m_btnGearRation.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnGearRation.SetFlat(FALSE);

	m_btnLanguage.SetIcon(IDI_LANGUAGE);
	m_btnLanguage.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnLanguage.SetFlat(FALSE);

	m_btnSetting.SetIcon(IDI_SETTING);
	m_btnSetting.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnSetting.SetFlat(FALSE);	

	m_btnTimer.SetIcon(IDI_TIMER);
	m_btnTimer.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnTimer.SetFlat(FALSE);
	
	m_btnTimerSetting.SetIcon(IDI_SPEED);
	m_btnTimerSetting.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnTimerSetting.SetFlat(FALSE);

	m_btnAlignment.SetIcon(IDI_ALIGNMENT);
	m_btnAlignment.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnAlignment.SetFlat(FALSE);

	m_btnSLTFile.SetIcon(IDI_TEST_PROGRAM);
	m_btnSLTFile.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnSLTFile.SetFlat(FALSE);

	m_btnTorqueSetup.SetIcon(IDI_MANUAL_TORQUE);
	m_btnTorqueSetup.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnTorqueSetup.SetFlat(FALSE);

	m_btnBasicSetting.SetIcon(IDI_BASIC_SETTING);
	m_btnBasicSetting.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnBasicSetting.SetFlat(FALSE);

	// 
	m_btnMail.SetIcon(IDI_MAIL);
	m_btnMail.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnMail.SetFlat(FALSE);

	// 
	m_btnChipTrayMapInput.SetIcon(IDI_INPUT_TRAY);
	m_btnChipTrayMapInput.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnChipTrayMapInput.SetFlat(FALSE);

	// 
	m_btnAlignmentCheck.SetIcon(IDI_ALIGNMENT_CHECK);
	m_btnAlignmentCheck.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnAlignmentCheck.SetFlat(FALSE);

	// 
	m_btnUPH.SetIcon(IDI_UPH);
	m_btnUPH.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnUPH.SetFlat(FALSE);

	m_btnCommunication.SetIcon(IDI_COMMICATION_SET);
	m_btnCommunication.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnCommunication.SetFlat(FALSE);

	m_btnFilePath.SetIcon(IDI_FILE_PATH);
	m_btnFilePath.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnFilePath.SetFlat(FALSE);

	m_btnHandlerComPortSetting.SetIcon(IDI_PXE);
	m_btnHandlerComPortSetting.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnHandlerComPortSetting.SetFlat(FALSE);

	m_btnTrayMapUI.SetIcon(IDI_TRAYMAP_UI);
	m_btnTrayMapUI.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnTrayMapUI.SetFlat(FALSE);

	m_btnCameraSetting.SetIcon(IDI_CCD_SOCKET_SETTING);
	m_btnCameraSetting.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnCameraSetting.SetFlat(FALSE);

	m_btnATCMonitor.SetIcon(IDI_TEMPTERTURE);
	m_btnATCMonitor.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnATCMonitor.SetFlat(FALSE);

	m_btnTSPIDValve.SetIcon(IDI_TORQUE);
	m_btnTSPIDValve.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnTSPIDValve.SetFlat(FALSE);

	m_btnPageFunction.SetIcon(IDI_PAGE_FUNCTION);
	m_btnPageFunction.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnPageFunction.SetFlat(FALSE);

	m_btnManualEnable.SetIcon(IDI_MANUL_ENABLE);
	m_btnManualEnable.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnManualEnable.SetFlat(FALSE);

	m_btnRepeatTrayEnable.SetIcon(IDI_REPEAT_TRAY_ENB);
	m_btnRepeatTrayEnable.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnRepeatTrayEnable.SetFlat(FALSE);

	m_btnTrayDefColor.SetIcon(IDI_TRAY_COLOR);
	m_btnTrayDefColor.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnTrayDefColor.SetFlat(FALSE);

	m_btnArmLogIC.SetIcon(IDI_ARM_LOG_ICIMG);
	m_btnArmLogIC.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnArmLogIC.SetFlat(FALSE);
		
	// This is for show currect symbol
	if(m.UI.Language == m.enEnglish)
		m_btnLanguage.SetWindowText("English");		// Show English
	else if(m.UI.Language == m.enChinese)
		m_btnLanguage.SetWindowText("Chinese");		// Show Chinese

	InitTips();

	// Note: We need set the Text by myself
	SetWindowText("Debug");

	f.ChangeLanguage(GetSafeHwnd());

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
void CPageDebug::InitTips()
{
	// Init Tips
	m_ToolTip.Create(this);
	m_ToolTip.SetMaxTipWidth(800);
	m_ToolTip.SetDelayTime( TTDT_AUTOPOP, 10000 );
	m_ToolTip.SetDelayTime( TTDT_INITIAL, 25 );
	m_ToolTip.EnableToolTips(true);

	m_ToolTip.AddTool( GetDlgItem(IDC_GEAR_RATION),			_T("GearRation Information") );
	m_ToolTip.AddTool( GetDlgItem(IDC_LANGUAGE),			_T("Langeuage Change") );
	m_ToolTip.AddTool( GetDlgItem(IDC_DEBUG_FUNCTION),		_T("Debug Function") );
	m_ToolTip.AddTool( GetDlgItem(IDC_BASIC_SETTING),		_T("Basic Setting") );
	m_ToolTip.AddTool( GetDlgItem(IDC_TIMER),				_T("Timer") );
	m_ToolTip.AddTool( GetDlgItem(IDC_TIMER_SETTING),		_T("Timer Setting") );
	m_ToolTip.AddTool( GetDlgItem(IDC_CHANGE_FILE2),		_T("Change File / Tray File") );
	m_ToolTip.AddTool( GetDlgItem(IDC_HANDLER_SETTING),		_T("Handler Setting") );
	m_ToolTip.AddTool( GetDlgItem(IDC_TORQUE_SETUP),		_T("Torque Control / Test Control Parameter") );
	m_ToolTip.AddTool( GetDlgItem(IDC_ALIGNMENT_SETUP),		_T("Alignment") );
	m_ToolTip.AddTool( GetDlgItem(IDC_TEST_PROGRAM),		_T("SLT Test Program") );
	m_ToolTip.AddTool( GetDlgItem(IDC_INPUT_TRAY_CHIP),		_T("Chip Tray Input Control") );
	m_ToolTip.AddTool( GetDlgItem(IDC_ALIGNMENT),			_T("Alignment Check") );
	m_ToolTip.AddTool( GetDlgItem(IDC_MAIL),				_T("Mail Control Setup") );
	m_ToolTip.AddTool( GetDlgItem(IDC_UPH),					_T("UPH Control Tool") );
	m_ToolTip.AddTool( GetDlgItem(IDC_COMMUNICATION),		_T("Handler Communication Setup") );
	m_ToolTip.AddTool( GetDlgItem(IDC_FILE_PATH),			_T("File Path") );
	m_ToolTip.AddTool( GetDlgItem(IDC_CCD_CAMERA),			_T("CCD Camera Setting") );
	m_ToolTip.AddTool( GetDlgItem(IDC_TRAY_UI),				_T("Tray Map Display Setting") );
	m_ToolTip.AddTool( GetDlgItem(IDC_HANDLER_COM_SETTING),	_T("Handler Com Port") );
	m_ToolTip.AddTool( GetDlgItem(IDC_ATC_MONITOR),			_T("ATC Monitor") );
	m_ToolTip.AddTool( GetDlgItem(IDC_INPUT_TRAY_CHIP),		_T("Input tray for chip tray") );
	m_ToolTip.AddTool( GetDlgItem(IDC_MANUAL_ENABLE),		_T("Manual Enable") );
	m_ToolTip.AddTool( GetDlgItem(IDC_PAGE_FUNCTION),		_T("Page function enable") );
	m_ToolTip.AddTool( GetDlgItem(IDC_PID_CONTROL),			_T("PID Control") );
	m_ToolTip.AddTool( GetDlgItem(IDC_REPEAT_TRAY_ENABLE),	_T("Repeat Tray Function Enable") );
	m_ToolTip.AddTool( GetDlgItem(IDC_TRAY_COLOR),			_T("Tray Color Define") );

	//
}
void CPageDebug::OnDebugFunction() 
{
	f.m_Log.AddEvent(enCodeDebugPageFunction);	// Add Event

	CDlgDebugFunction dlg;
	dlg.DoModal();
}

void CPageDebug::OnLanguage() 
{
	f.m_Log.AddEvent(enCodeDebugPageLanguage);	// Add Event

	if(m.UI.Language == m.enEnglish)
		m.UI.Language = m.enChinese;
	else
		m.UI.Language = m.enEnglish;

	// show now language

	if(m.UI.Language == m.enEnglish)
		m_btnLanguage.SetWindowText("English");		// Show English
	else if(m.UI.Language == m.enChinese)
		m_btnLanguage.SetWindowText("Chinese");		// Show Chinese

	f.SaveUI();
	f.LoadUI();

	f.ChangeLanguage(GetSafeHwnd());
	f.ChangeLanguage(theApp.GetMainWnd()->GetSafeHwnd());
	f.ChangeLanguage(m.Page.Initial.GetSafeHwnd());
	f.ChangeLanguage(m.Page.Debug.GetSafeHwnd());
	f.ChangeLanguage(m.Page.Run.GetSafeHwnd());
	f.ChangeLanguage(m.Page.User.GetSafeHwnd());
	f.ChangeLanguage(m.Page.Setup.GetSafeHwnd());
	f.ChangeLanguage(m.Page.Enginner.GetSafeHwnd());
	
//	f.m_Log.AddEvent(enCodeDlgLanguage);
}

void CPageDebug::OnGearRation() 
{
	f.m_Log.AddEvent(enCodeDebugPageGearRation);	// Add Event

	CDlgGearRation dlg;
	dlg.DoModal();
}

void CPageDebug::OnHandlerSetting() 
{
	f.m_Log.AddEvent(enCodeDebugPageHandler);	// Add Event

	CDlgSetting dlg;
	dlg.DoModal();
}

void CPageDebug::OnTimer() 
{
	f.m_Log.AddEvent(enCodeDebugPageTimer);	// Add Event

	CDlgTimer dlg;
	dlg.DoModal();
}

void CPageDebug::OnTimerSetting() 
{
	f.m_Log.AddEvent(enCodeDebugPageTimerSetting );	// Add Event

	CDlgTimerSetting dlg;
	dlg.DoModal();
}

void CPageDebug::OnAlignmentSetup() 
{
	CDlgAlignmentPw Pwdlg;
	if(Pwdlg.DoModal() != IDOK) 
		return;

	f.m_Log.AddEvent(enCodeDebugPageAlignment );	// Add Event

	CDlgAlignment dlg(true);
	dlg.DoModal();
}

BOOL CPageDebug::PreTranslateMessage(MSG* pMsg) 
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

void CPageDebug::OnChangeFile() 
{
	f.m_Log.AddEvent(enCodeDebugPageTrayFile);	// Add Event

	CDlgTrayFile dlg;
	dlg.DoModal();

}

void CPageDebug::OnTorqueSetup() 
{
//	CDlgTorqueControl dlg;
	CDlgTorqueTool dlg;
	dlg.DoModal();
}

void CPageDebug::OnTestProgram() 
{

}

void CPageDebug::OnMail() 
{
	CDlgMail dlg;
	dlg.DoModal();
}

void CPageDebug::OnInputTrayChip() 
{

}

void CPageDebug::OnAlignment() 
{
	CDlgAlignmentCheck dlg;
	dlg.DoModal();
}

void CPageDebug::OnUph() 
{
	CDlgUPHTool dlg;
	dlg.DoModal();
}

void CPageDebug::OnBasicSetting() 
{
	CDlgBasicSetting dlg;
	dlg.DoModal();
}

void CPageDebug::OnCommunication() 
{
	CDlgCommunication	dlg;
	dlg.DoModal();
}

void CPageDebug::OnFilePath() 
{
	CDlgFilePath dlg;
	dlg.DoModal();
}

void CPageDebug::OnHandlerComSetting() 
{
	CDlgHandlerComPort dlg;
	dlg.DoModal();
}

void CPageDebug::OnTrayUi() 
{
	CDlgTrayMapUI dlg;
	dlg.DoModal();
}

void CPageDebug::OnCcdCamera() 
{
	CDlgCameraSetting dlg;
	dlg.DoModal();
}

void CPageDebug::OnHotKey() 
{
	CDlgHotKey dlg;
	dlg.DoModal();
}

void CPageDebug::OnPw() 
{
	CDlgPasswordRead dlg;
	dlg.DoModal();
}

void CPageDebug::OnAtcMonitor() 
{
	CDlgATCMonitor dlg;
	dlg.DoModal();	
}

void CPageDebug::OnPidControl() 
{
	CDlgTorqueControl dlg;
	dlg.DoModal();	
}
void CPageDebug::GetButtonDistance(int &Width, int &Height, int &WDistance, int &HDistance)
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
void CPageDebug::ReDrawUIHandlerModule()
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

	// Communication 
	if(1)
	{
		m_btnCommunication.ShowWindow( TRUE );
		for(i=_ICON_Handler*_ICON_Max_Row;i<_ICON_Max;i++)
		{
			if( !rtUse[i] )
			{
				rtUse[i] = true;
				m_btnCommunication.MoveWindow(&rtW[i]);
				break;
			}
		}
	}
	else
		m_btnCommunication.ShowWindow( FALSE );	

	// TrayMap UI
	if(1)
	{
		m_btnTrayMapUI.ShowWindow( TRUE );
		for(i=_ICON_Handler*_ICON_Max_Row;i<_ICON_Max;i++)
		{
			if( !rtUse[i] )
			{
				rtUse[i] = true;
				m_btnTrayMapUI.MoveWindow(&rtW[i]);
				break;
			}
		}
	}
	else
		m_btnTrayMapUI.ShowWindow( FALSE );	

	// FilePath 
	if(1)
	{
		m_btnFilePath.ShowWindow( TRUE );
		for(i=_ICON_Handler*_ICON_Max_Row;i<_ICON_Max;i++)
		{
			if( !rtUse[i] )
			{
				rtUse[i] = true;
				m_btnFilePath.MoveWindow(&rtW[i]);
				break;
			}
		}
	}
	else
		m_btnFilePath.ShowWindow( FALSE );	
	
	// Com Port
	if(1)
	{
		m_btnHandlerComPortSetting.ShowWindow( TRUE );
		for(i=_ICON_Handler*_ICON_Max_Row;i<_ICON_Max;i++)
		{
			if( !rtUse[i] )
			{
				rtUse[i] = true;
				m_btnHandlerComPortSetting.MoveWindow(&rtW[i]);
				break;
			}
		}
	}
	else
		m_btnHandlerComPortSetting.ShowWindow( FALSE );	

	// Basic Setting
	if(1)
	{
		m_btnBasicSetting.ShowWindow( TRUE );
		for(i=_ICON_Handler*_ICON_Max_Row;i<_ICON_Max;i++)
		{
			if( !rtUse[i] )
			{
				rtUse[i] = true;
				m_btnBasicSetting.MoveWindow(&rtW[i]);
				break;
			}
		}
	}
	else
		m_btnBasicSetting.ShowWindow( FALSE );	

	// Camera
	if(1)
	{
		m_btnCameraSetting.ShowWindow( TRUE );
		for(i=_ICON_Handler*_ICON_Max_Row;i<_ICON_Max;i++)
		{
			if( !rtUse[i] )
			{
				rtUse[i] = true;
				m_btnCameraSetting.MoveWindow(&rtW[i]);
				break;
			}
		}
	}
	else
		m_btnCameraSetting.ShowWindow( FALSE );	
	
	// Page Function
	if(1)
	{
		m_btnPageFunction.ShowWindow( TRUE );
		for(i=_ICON_Handler*_ICON_Max_Row;i<_ICON_Max;i++)
		{
			if( !rtUse[i] )
			{
				rtUse[i] = true;
				m_btnPageFunction.MoveWindow(&rtW[i]);
				break;
			}
		}
	}
	else
		m_btnPageFunction.ShowWindow( FALSE );	
}
void CPageDebug::ReDrawUI()
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

	// Tray File
	if(1)
	{
		m_btnChangeFile.ShowWindow( TRUE );
		for(i=0;i<_ICON_Max;i++)
		{
			if( !rtUse[i] )
			{
				rtUse[i] = true;
				m_btnChangeFile.MoveWindow(&rtW[i]);
				break;
			}
		}
	}
	else
		m_btnChangeFile.ShowWindow( FALSE );

	// Gear Ration
	if(1)
	{
		m_btnGearRation.ShowWindow( TRUE );
		for(i=0;i<_ICON_Max;i++)
		{
			if( !rtUse[i] )
			{
				rtUse[i] = true;
				m_btnGearRation.MoveWindow(&rtW[i]);
				break;
			}
		}
	}
	else
		m_btnGearRation.ShowWindow( FALSE );

	// Debug Function
	if(1)
	{
		m_btnDebugFunction.ShowWindow( TRUE );
		for(i=0;i<_ICON_Max;i++)
		{
			if( !rtUse[i] )
			{
				rtUse[i] = true;
				m_btnDebugFunction.MoveWindow(&rtW[i]);
				break;
			}
		}
	}
	else
		m_btnDebugFunction.ShowWindow( FALSE );

	// Torque Setup
	if(1)
	{
		m_btnTorqueSetup.ShowWindow( TRUE );
		for(i=0;i<_ICON_Max;i++)
		{
			if( !rtUse[i] )
			{
				rtUse[i] = true;
				m_btnTorqueSetup.MoveWindow(&rtW[i]);
				break;
			}
		}
	}
	else
		m_btnTorqueSetup.ShowWindow( FALSE );

	// Handler Setting
	if(1)
	{
		m_btnSetting.ShowWindow( TRUE );
		for(i=0;i<_ICON_Max;i++)
		{
			if( !rtUse[i] )
			{
				rtUse[i] = true;
				m_btnSetting.MoveWindow(&rtW[i]);
				break;
			}
		}
	}
	else
		m_btnSetting.ShowWindow( FALSE );

	// Language
	if(1)
	{
		m_btnLanguage.ShowWindow( TRUE );
		for(i=0;i<_ICON_Max;i++)
		{
			if( !rtUse[i] )
			{
				rtUse[i] = true;
				m_btnLanguage.MoveWindow(&rtW[i]);
				break;
			}
		}
	}
	else
		m_btnLanguage.ShowWindow( FALSE );

	// UPH
	if(1)
	{
		m_btnUPH.ShowWindow( TRUE );
		for(i=0;i<_ICON_Max;i++)
		{
			if( !rtUse[i] )
			{
				rtUse[i] = true;
				m_btnUPH.MoveWindow(&rtW[i]);
				break;
			}
		}
	}
	else
		m_btnUPH.ShowWindow( FALSE );

	// Timer Setting
	if(1)
	{
		m_btnTimerSetting.ShowWindow( TRUE );
		for(i=0;i<_ICON_Max;i++)
		{
			if( !rtUse[i] )
			{
				rtUse[i] = true;
				m_btnTimerSetting.MoveWindow(&rtW[i]);
				break;
			}
		}
	}
	else
		m_btnTimerSetting.ShowWindow( FALSE );

	// Timer 
	if(1)
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

	// SLT Program
	if(1)
	{
		m_btnSLTFile.ShowWindow( TRUE );
		for(i=0;i<_ICON_Max;i++)
		{
			if( !rtUse[i] )
			{
				rtUse[i] = true;
				m_btnSLTFile.MoveWindow(&rtW[i]);
				break;
			}
		}
	}
	else
		m_btnSLTFile.ShowWindow( FALSE );

	// ATC Monitor 
	if(1)
	{
		m_btnATCMonitor.ShowWindow( TRUE );
		for(i=0;i<_ICON_Max;i++)
		{
			if( !rtUse[i] )
			{
				rtUse[i] = true;
				m_btnATCMonitor.MoveWindow(&rtW[i]);
				break;
			}
		}
	}
	else
		m_btnATCMonitor.ShowWindow( FALSE );

	// Mail
	if(1)
	{
		m_btnMail.ShowWindow( TRUE );
		for(i=0;i<_ICON_Max;i++)
		{
			if( !rtUse[i] )
			{
				rtUse[i] = true;
				m_btnMail.MoveWindow(&rtW[i]);
				break;
			}
		}
	}
	else
		m_btnMail.ShowWindow( FALSE );

	// PID Value
	if(1)
	{
		m_btnTSPIDValve.ShowWindow( TRUE );
		for(i=0;i<_ICON_Max;i++)
		{
			if( !rtUse[i] )
			{
				rtUse[i] = true;
				m_btnTSPIDValve.MoveWindow(&rtW[i]);
				break;
			}
		}
	}
	else
		m_btnTSPIDValve.ShowWindow( FALSE );

	// Chip Tray
	if(1)
	{
		m_btnChipTrayMapInput.ShowWindow( TRUE );
		for(i=0;i<_ICON_Max;i++)
		{
			if( !rtUse[i] )
			{
				rtUse[i] = true;
				m_btnChipTrayMapInput.MoveWindow(&rtW[i]);
				break;
			}
		}
	}
	else
		m_btnChipTrayMapInput.ShowWindow( FALSE );

	// Alignment
	if(1)
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

	// Alignment Check
	if(1)
	{
		m_btnAlignmentCheck.ShowWindow( TRUE );
		for(i=0;i<_ICON_Max;i++)
		{
			if( !rtUse[i] )
			{
				rtUse[i] = true;
				m_btnAlignmentCheck.MoveWindow(&rtW[i]);
				break;
			}
		}
	}
	else
		m_btnAlignmentCheck.ShowWindow( FALSE );

	// Manual Enable
	if(1)
	{
		m_btnManualEnable.ShowWindow( TRUE );
		for(i=0;i<_ICON_Max;i++)
		{
			if( !rtUse[i] )
			{
				rtUse[i] = true;
				m_btnManualEnable.MoveWindow(&rtW[i]);
				break;
			}
		}
	}
	else
		m_btnManualEnable.ShowWindow( FALSE );

	// Repeat Enable
	if(1)
	{
		m_btnRepeatTrayEnable.ShowWindow( TRUE );
		for(i=0;i<_ICON_Max;i++)
		{
			if( !rtUse[i] )
			{
				rtUse[i] = true;
				m_btnRepeatTrayEnable.MoveWindow(&rtW[i]);
				break;
			}
		}
	}
	else
		m_btnRepeatTrayEnable.ShowWindow( FALSE );

	// Tray Color
	if(1)
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

	// Arm Log IC
	if(1)
	{
		m_btnArmLogIC.ShowWindow( TRUE );
		for(i=0;i<_ICON_Max;i++)
		{
			if( !rtUse[i] )
			{
				rtUse[i] = true;
				m_btnArmLogIC.MoveWindow(&rtW[i]);
				break;
			}
		}
	}
	else
		m_btnArmLogIC.ShowWindow( FALSE );
}
void CPageDebug::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	if(bShow)
		ReDrawUI();

	if(bShow)
		ReDrawUIHandlerModule();

	CDialog::OnShowWindow(bShow, nStatus);	
}

void CPageDebug::OnPageFunction() 
{
	CDlgCustomPageFunction dlg;
	dlg.DoModal();
}

void CPageDebug::OnManualEnable() 
{
	CDlgCustomMCFunction dlg;
	dlg.DoModal();
}

void CPageDebug::OnRepeatTrayEnable() 
{
	CDlgRepeatTrayEnable dlg;
	dlg.DoModal();
}

void CPageDebug::OnTrayColor() 
{
	CDlgTrayDef dlg;
	dlg.DoModal();
}

void CPageDebug::OnArmLogic() 
{
	CDlgArmLogICImage dlg;
	dlg.DoModal();
}
