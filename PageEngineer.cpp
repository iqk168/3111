// PageEngineer.cpp : implementation file
//

#include "stdafx.h"
#include "Deer.h"
#include "DeerDlg.h"
#include "PageEngineer.h"


// Dlg 
#include "DlgSpeed.h"
#include "DlgBinMapping.h"
#include "DlgTrayFile.h"
#include "DlgTrayFileNoHeater.h"
#include "DlgMotorMontior.h"
#include "DlgIOMontior.h"
#include "DlgPasswordNeed.h"
#include "DlgEvent.h"
#include "DlgContactCounter.h"
#include "DlgAlignment.h"
#include "DlgMail.h"
//

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPageEngineer dialog

CPageEngineer::CPageEngineer(CWnd* pParent /*=NULL*/)
	: CDialog(CPageEngineer::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPageEngineer)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CPageEngineer::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPageEngineer)
	DDX_Control(pDX, IDC_ALARM_MAIL,				m_btnAlarmMail);
	DDX_Control(pDX, IDC_LOOP_TEST,					m_btnLoopTest);
	DDX_Control(pDX, IDC_CCD_DOUBLE_DETECT,			m_btnSocketCCDSetup);
	DDX_Control(pDX, IDC_CONTACT_COUNTER2,			m_btnContactCounter);
	DDX_Control(pDX, IDC_EVENT_LOG,					m_btnEventLog);
	DDX_Control(pDX, IDC_MOTOR_MONTIOR,				m_btnMotorMonitor);
	DDX_Control(pDX, IDC_SPEED,						m_btnSpeed);
	DDX_Control(pDX, IDC_CHANGE_FILE,				m_btnChangeFile);
	DDX_Control(pDX, IDC_IO_MONTIOR,				m_btnIOMonitor);
	DDX_Control(pDX, IDC_ALIGNMENT_SETUP,			m_btnAlignment);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CPageEngineer, CDialog)
	//{{AFX_MSG_MAP(CPageEngineer)
	ON_BN_CLICKED(IDC_SPEED,						OnSpeed)
	ON_BN_CLICKED(IDC_CHANGE_FILE,					OnChangeFile)
	ON_BN_CLICKED(IDC_MOTOR_MONTIOR,				OnMotorMontior)
	ON_BN_CLICKED(IDC_IO_MONTIOR,					OnIoMontior)
	ON_BN_CLICKED(IDC_ALIGNMENT_SETUP,				OnAlignmentSetup)
	ON_BN_CLICKED(IDC_EVENT_LOG,					OnEventLog)
	ON_BN_CLICKED(IDC_CONTACT_COUNTER2,				OnContactCounter2)
	ON_WM_SHOWWINDOW()
	ON_BN_CLICKED(IDC_CCD_DOUBLE_DETECT,			OnCcdDoubleDetect)
	ON_BN_CLICKED(IDC_LOOP_TEST,					OnLoopTest)
	ON_BN_CLICKED(IDC_ALARM_MAIL,					OnAlarmMail)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPageEngineer message handlers

BOOL CPageEngineer::OnInitDialog() 
{
	CDialog::OnInitDialog();

	// init button
	m_btnChangeFile.SetIcon(IDI_FILE);;
	m_btnChangeFile.SetAlign(CButtonST::ST_ALIGN_VERT);;
	m_btnChangeFile.SetFlat(FALSE);
	
	m_btnSpeed.SetIcon(IDI_SPEED);;
	m_btnSpeed.SetAlign(CButtonST::ST_ALIGN_VERT);;
	m_btnSpeed.SetFlat(FALSE);

	m_btnMotorMonitor.SetIcon(IDI_SERVO_MOTOR);
	m_btnMotorMonitor.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnMotorMonitor.SetFlat(FALSE);

	m_btnIOMonitor.SetIcon(IDI_IO);
	m_btnIOMonitor.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnIOMonitor.SetFlat(FALSE);

	m_btnAlignment.SetIcon(IDI_ALIGNMENT);
	m_btnAlignment.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnAlignment.SetFlat(FALSE);

	m_btnEventLog.SetIcon(IDI_EVENT_LOG);
	m_btnEventLog.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnEventLog.SetFlat(FALSE);

	m_btnContactCounter.SetIcon(IDI_CONTACT_COUNTER);
	m_btnContactCounter.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnContactCounter.SetFlat(FALSE);

	m_btnSocketCCDSetup.SetIcon(IDI_CCD_SOCKET_SETUP);
	m_btnSocketCCDSetup.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnSocketCCDSetup.SetFlat(FALSE);

	m_btnLoopTest.SetIcon(IDI_LOOP_TEST);
	m_btnLoopTest.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnLoopTest.SetFlat(FALSE);

	m_btnAlarmMail.SetIcon(IDI_MAIL);
	m_btnAlarmMail.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnAlarmMail.SetFlat(FALSE);

	InitTips();

	// Note: We need set the Text by myself
	SetWindowText("Enigneer");

	f.ChangeLanguage(GetSafeHwnd());

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
void CPageEngineer::InitTips()
{
	// Init Tips
	m_ToolTip.Create(this);
	m_ToolTip.SetMaxTipWidth(800);
	m_ToolTip.SetDelayTime( TTDT_AUTOPOP, 10000 );
	m_ToolTip.SetDelayTime( TTDT_INITIAL, 25 );
	m_ToolTip.EnableToolTips(true);

	//
	m_ToolTip.AddTool( GetDlgItem(IDC_MOTOR_MONTIOR),				_T("Motor Monitor / Check Motor Status") );
	m_ToolTip.AddTool( GetDlgItem(IDC_IO_MONTIOR),					_T("IO Monitor / Check IO Status / Set IO Output") );
	m_ToolTip.AddTool( GetDlgItem(IDC_ALIGNMENT_SETUP),				_T("Alignment") );
	m_ToolTip.AddTool( GetDlgItem(IDC_EVENT_LOG),					_T("Handler Event Log") );
	m_ToolTip.AddTool( GetDlgItem(IDC_CONTACT_COUNTER2),			_T("Test Site Contact Socket Counter") );
	m_ToolTip.AddTool( GetDlgItem(IDC_SPEED),						_T("Speed Setting") );
	m_ToolTip.AddTool( GetDlgItem(IDC_CHANGE_FILE),					_T("Tray File") );
	m_ToolTip.AddTool( GetDlgItem(IDC_CCD_DOUBLE_DETECT),			_T("CCD Socket") );
	m_ToolTip.AddTool( GetDlgItem(IDC_LOOP_TEST),					_T("Loop Test") );
	m_ToolTip.AddTool( GetDlgItem(IDC_ALARM_MAIL),					_T("Alarm Mail") );
}
void CPageEngineer::OnSpeed() 
{
	f.m_Log.AddEvent(enCodeEngPageSpeed);	// Add Event

	CDlgSpeed dlg;
	dlg.DoModal();
}

void CPageEngineer::OnChangeFile() 
{
	// 如果運行中停止,不可以變更參數 功能
	// Ready 只有有 Cycle Finish 和剛 Initial 完才會有

	if( m.Info.iStatus == theApp.enCycleStop )
	{
		AfxMessageBox("Please Press [One Cycle] to clear IC in handler.!");
		return;
	}

	if( m.Info.iStatus == theApp.enOverrideStop )
	{
		AfxMessageBox("Please Press [One Cycle] to clear IC in handler.!");
		return;
	}
		

	f.m_Log.AddEvent(enCodeEngPageTrayFile);	// Add Event

	CDlgTrayFileNoHeater dlg;
	dlg.DoModal();
}

void CPageEngineer::OnMotorMontior() 
{
	f.m_Log.AddEvent(enCodeEngPageMotorMonitor);	// Add Event

	CDlgMotorMontior dlg(false, false, true);
	dlg.DoModal();
}


void CPageEngineer::OnIoMontior() 
{
	f.m_Log.AddEvent(enCodeEngPageIOMonitor);		// Add Event

	CDlgIOMontior dlg;
	dlg.DoModal();
}

void CPageEngineer::OnAlignmentSetup() 
{
	if( f.CheckInitialNeed())
		return;

	f.m_Log.AddEvent(enCodeEngPageAlignment);		// Add Event

	CDlgAlignment dlg;
	dlg.DoModal();
}

BOOL CPageEngineer::PreTranslateMessage(MSG* pMsg) 
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

void CPageEngineer::OnEventLog() 
{
	f.m_Log.AddEvent(enCodeEngPageEventLog);		// Add Event

	CDlgEvent dlg;
	dlg.DoModal();	
}

void CPageEngineer::OnContactCounter2() 
{
	// 如果 dlg 設定 false, 那麼打開表單後, 就無法 Clear
	// 如果 dlg 設定為 true, 那麼打開表單後, 就可以 Clear
	f.m_Log.AddEvent(enCodeEngPageContactCounter);		// Add Event
	CDlgContactCounter dlg(true);
	dlg.DoModal();
}
void CPageEngineer::GetButtonDistance(int &Width, int &Height, int &WDistance, int &HDistance)
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
void CPageEngineer::ReDrawUI()
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

	// Motor Monitor
	if( m.m_EngineerPageEnable.m_bEnableMotorMon )
	{
		m_btnMotorMonitor.ShowWindow( TRUE );
		for(i=0;i<_ICON_Max;i++)
		{
			if( !rtUse[i] )
			{
				rtUse[i] = true;
				m_btnMotorMonitor.MoveWindow(&rtW[i]);
				break;
			}
		}
	}
	else
		m_btnMotorMonitor.ShowWindow( FALSE );

	// IO Monitor
	if( m.m_EngineerPageEnable.m_bEnableIOMonitor )
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
	if( m.m_EngineerPageEnable.m_bEnableAlignment )
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

	// Event Log
	if( m.m_EngineerPageEnable.m_bEnableEventLog )
	{
		m_btnEventLog.ShowWindow( TRUE );
		for(i=0;i<_ICON_Max;i++)
		{
			if( !rtUse[i] )
			{
				rtUse[i] = true;
				m_btnEventLog.MoveWindow(&rtW[i]);
				break;
			}
		}
	}
	else
		m_btnEventLog.ShowWindow( FALSE );

	// Socket CCD
	if( m.m_EngineerPageEnable.m_bEnableSocketCCD )
	{
		m_btnSocketCCDSetup.ShowWindow( TRUE );
		for(i=0;i<_ICON_Max;i++)
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
		m_btnSocketCCDSetup.ShowWindow( FALSE );

	// Speed
	if( m.m_EngineerPageEnable.m_bEnableSpeed )
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

	// TS Counter
	if( m.m_EngineerPageEnable.m_bEnableTSCounter )
	{
		m_btnContactCounter.ShowWindow( TRUE );
		for(i=0;i<_ICON_Max;i++)
		{
			if( !rtUse[i] )
			{
				rtUse[i] = true;
				m_btnContactCounter.MoveWindow(&rtW[i]);
				break;
			}
		}
	}
	else
		m_btnContactCounter.ShowWindow( FALSE );

	// Tray File
	if( m.m_EngineerPageEnable.m_bEnableChangeFile )
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

	// Loop Test
	if( m.m_EngineerPageEnable.m_bEnableLoopTest )
	{
		m_btnLoopTest.ShowWindow( TRUE );
		for(i=0;i<_ICON_Max;i++)
		{
			if( !rtUse[i] )
			{
				rtUse[i] = true;
				m_btnLoopTest.MoveWindow(&rtW[i]);
				break;
			}
		}
	}
	else
		m_btnLoopTest.ShowWindow( FALSE );

	// Alarm Mail
	if( m.m_EngineerPageEnable.m_bEnableAlarmMail )
	{
		m_btnAlarmMail.ShowWindow( TRUE );
		for(i=0;i<_ICON_Max;i++)
		{
			if( !rtUse[i] )
			{
				rtUse[i] = true;
				m_btnAlarmMail.MoveWindow(&rtW[i]);
				break;
			}
		}
	}
	else
		m_btnAlarmMail.ShowWindow( FALSE );
}

void CPageEngineer::OnCcdDoubleDetect() 
{
	f.m_Log.AddEvent(enCodeEngPageCCDSetup);	// Add Event

}

void CPageEngineer::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	if( bShow )
		ReDrawUI();

	CDialog::OnShowWindow(bShow, nStatus);	
}

void CPageEngineer::OnLoopTest() 
{
	f.m_Log.AddEvent(enCodeEngPageLoopTest);	// Add Event
}

void CPageEngineer::OnAlarmMail() 
{
	CDlgMail dlg;
	dlg.DoModal();
	f.m_Log.AddEvent(enCodeEngPageAlarmMail);	// Add Event
}
