// DlgManualContact.cpp : implementation file
//

#include "stdafx.h"
#include "deer.h"
#include "DlgManualContact.h"
#include "DlgOffsetTS.h"
#include "DlgTestTesting.h"
#include "DlgManualContactRecover.h"
#include "DlgManualContactTorque.h"
#include "DlgManualContactTorqueKgf.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgManualContact dialog


CDlgManualContact::CDlgManualContact(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgManualContact::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgManualContact)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	m_bUpOK				= true;
	m_bAlarm			= false;

	bManualUpStatus		= FALSE;
	bManualDownStatus	= FALSE;
	bManualMoveStatus	= FALSE;
}

void CDlgManualContact::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgManualContact)
	DDX_Control(pDX, IDC_NOTE, m_wndManualContactNote);
	DDX_Control(pDX, IDC_F_TS_VACC,					m_btnTestSiteVacc);
	DDX_Control(pDX, IDC_F_TS_MODE,					m_btnTestSiteMode);
	DDX_Control(pDX, IDC_F_CONTINUE,				m_btnFContinue);
	DDX_Control(pDX, IDC_F_TORQUE,					m_btnTorqueControl);
	DDX_Control(pDX, IDC_R_RESULT,					m_wndResult);
	DDX_Control(pDX, IDC_R_CURRENT_HEIGHT,			m_wndCurrentHeight);
	DDX_Control(pDX, IDC_R_COMMAND_CONTACT_HEIGHT,	m_wndCommandContactHeight);
	DDX_Control(pDX, IDC_F_UP,						m_btnFUp);
	DDX_Control(pDX, IDC_F_MOVE,					m_btnFMove);
	DDX_Control(pDX, IDC_F_DOWN,					m_btnFDown);
	DDX_Control(pDX, IDC_F_TEMPERATURE,				m_btnTemperature);
	DDX_Control(pDX, IDC_F_OFFSET,					m_btnOffset);
	DDX_Control(pDX, IDC_F_INTERFACE_TESTING,		m_btnInterfaceTesting);
	DDX_Control(pDX, IDCANCEL,						m_btnCancel);
	DDX_Control(pDX, IDOK,							m_btnOK);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgManualContact, CDialog)
	//{{AFX_MSG_MAP(CDlgManualContact)
	ON_WM_TIMER()
	ON_WM_SHOWWINDOW()
	ON_BN_CLICKED(IDC_F_TEMPERATURE,				OnFTemperature)
	ON_BN_CLICKED(IDC_F_INTERFACE_TESTING,			OnFInterfaceTesting)
	ON_BN_CLICKED(IDC_F_OFFSET,						OnFOffset)
	ON_BN_CLICKED(IDC_F_UP,							OnFUp)
	ON_BN_CLICKED(IDC_F_DOWN,						OnFDown)
	ON_BN_CLICKED(IDC_F_MOVE,						OnFMove)
	ON_MESSAGE( WM_MANUAL_CT_DONE,					OnTSContacted )
	ON_MESSAGE( WM_MANUAL_UP_DONE,					OnTSUped )
	ON_MESSAGE( WM_MANUAL_MV_DONE,					OnTSMved )
	ON_MESSAGE( WM_MANUAL_ALARM,					OnAlarm )
	ON_BN_CLICKED(IDC_F_TORQUE,						OnFTorque)
	ON_BN_CLICKED(IDC_F_CONTINUE,					OnFContinue)
	ON_BN_CLICKED(IDC_F_TS_MODE,					OnFTsMode)
	ON_BN_CLICKED(IDC_F_TS_VACC, OnFTsVacc)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgManualContact message handlers

BOOL CDlgManualContact::PreTranslateMessage(MSG* pMsg) 
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

BOOL CDlgManualContact::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m.Info.bSubDlgOpen = true;
	f.UpdateButtonState();

	m.ManualInterlok.IsManualControlMode = true;

	// init button 
	m_btnOK.SetIcon(IDI_OK);;
	m_btnOK.SetAlign(CButtonST::ST_ALIGN_VERT);;
	m_btnOK.SetFlat(FALSE);
	
	m_btnCancel.SetIcon(IDI_CANCEL);
	m_btnCancel.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnCancel.SetFlat(FALSE);
	
	m_btnInterfaceTesting.SetIcon(IDI_INTER_FACE_TESTING);
	m_btnInterfaceTesting.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnInterfaceTesting.SetFlat(FALSE);

	m_btnOffset.SetIcon(IDI_OFF_SET);
	m_btnOffset.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnOffset.SetFlat(FALSE);

	m_btnTemperature.SetIcon(IDI_CDS_TEMPERATURE);
	m_btnTemperature.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnTemperature.SetFlat(FALSE);

	m_btnTorqueControl.SetIcon(IDI_TORQUE);
	m_btnTorqueControl.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnTorqueControl.SetFlat(FALSE);

	m_btnTestSiteMode.SetIcon(IDI_TS_MODE_DIRECT);
	m_btnTestSiteMode.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnTestSiteMode.SetFlat(FALSE);

	m_btnTestSiteVacc.SetIcon(IDI_SOCKET_VACC);
	m_btnTestSiteVacc.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnTestSiteVacc.SetFlat(FALSE);

	//
	m_btnFMove.SetIcon(IDI_DOWN);
	m_btnFMove.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnFMove.SetFlat(FALSE);

	m_btnFUp.SetIcon(IDI_UP);
	m_btnFUp.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnFUp.SetFlat(FALSE);

	m_btnFDown.SetIcon(IDI_DOWN);
	m_btnFDown.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnFDown.SetFlat(FALSE);

	m_btnFContinue.SetIcon(IDI_DEBUG);
	m_btnFContinue.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnFContinue.SetFlat(FALSE);

	//
	InitUI();

	//
	InitTips();

	//
	InitManualContactNote();

	//
	UIUnLockForUPed(); // default

	//
	ReDrawForTsMode();

	//
	ReDrawForTsVacc();

	//
	SetTimer( ID_TIME_MANUAL_CONTACT_STATUS, 100, NULL);

	//
	f.ChangeLanguage(GetSafeHwnd());

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
void CDlgManualContact::InitManualContactNote()
{
	CString csManualNote = _T("");
	csManualNote = f.GetManualContactNote();

	//
	csManualNote.TrimLeft();
	csManualNote.TrimRight();

	//
	csManualNote.Replace("\\r\\n", "\r\n");

	//
	if( csManualNote != "" )
	{
		m_wndManualContactNote.ShowWindow( TRUE );
		m_wndManualContactNote.SetWindowText( csManualNote );
	}
	else
		m_wndManualContactNote.ShowWindow( FALSE );
}
void CDlgManualContact::InitUI()
{
	// Alignment Value
	CString csAlignmentValue = _T("");
	csAlignmentValue.Format("%d", int( m.m_Align.TestSite.contact + m.m_Offset.TestSite.contact * m.m_Ratio.Inserter_GearRation ) );
	m_wndCommandContactHeight.SetText(csAlignmentValue, 11, "Arial", DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	m_wndCommandContactHeight.SetNewBkColor(ST_LIGHTGREEN);
	
	// Motor LCount Value
	m_wndResult.SetText("--", 10, "Arial", DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	m_wndResult.SetNewBkColor(ST_LIGHTGREEN);

	// Motor RCount
	m_wndCurrentHeight.SetText("--", 11, "Arial", DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	m_wndCurrentHeight.SetNewBkColor(ST_LIGHTGREEN);

	//
	m_btnFContinue.EnableWindow( FALSE );
}
void CDlgManualContact::InitTips()
{
	// Init Tips
	m_ToolTip.Create(this);
	m_ToolTip.SetMaxTipWidth(800);
	m_ToolTip.SetDelayTime( TTDT_AUTOPOP, 10000 );
	m_ToolTip.SetDelayTime( TTDT_INITIAL, 25 );
	m_ToolTip.EnableToolTips(true);

	//
	m_ToolTip.AddTool( GetDlgItem(IDC_R_CURRENT_HEIGHT),			_T("Current Height") );
	m_ToolTip.AddTool( GetDlgItem(IDC_R_COMMAND_CONTACT_HEIGHT),	_T("Command Contact Height") );
	m_ToolTip.AddTool( GetDlgItem(IDC_R_RESULT),					_T("Height Result") );

	//
	m_ToolTip.AddTool( GetDlgItem(IDC_F_TEMPERATURE),				_T("Temperature Control") );
	m_ToolTip.AddTool( GetDlgItem(IDC_F_INTERFACE_TESTING),			_T("Interface Testing") );
	m_ToolTip.AddTool( GetDlgItem(IDC_F_OFFSET),					_T("Offset Adjust") );
	m_ToolTip.AddTool( GetDlgItem(IDC_F_TORQUE),					_T("Contact force Adjust") );
	m_ToolTip.AddTool( GetDlgItem(IDC_F_TS_MODE),					_T("Test Site Mode") );
	m_ToolTip.AddTool( GetDlgItem(IDC_F_TS_VACC),					_T("Test Site Vacuum Mode") );

	//
	m_ToolTip.AddTool( GetDlgItem(IDC_F_UP),						_T("Move Up - return IC to shuttle") );
	m_ToolTip.AddTool( GetDlgItem(IDC_F_DOWN),						_T("Move Down - move the IC to socket") );
	m_ToolTip.AddTool( GetDlgItem(IDC_F_MOVE),						_T("Move - move test site up or down (adjust position by offset)") );
	m_ToolTip.AddTool( GetDlgItem(IDC_F_CONTINUE),					_T("Continue, After Error. Recover") );
}
void CDlgManualContact::OnTimer(UINT nIDEvent) 
{
	switch(nIDEvent)
	{
	case ID_TIME_MANUAL_CONTACT_STATUS:
		{
			UpdateMotorStatus();
			UpdatePositionStatus();
		}
		break;
	}	
	CDialog::OnTimer(nIDEvent);
}
void CDlgManualContact::UpdateMotorStatus()
{
	f.Motor.GetMotorStatus( &m.m_Motor.Inserter );

	// RCount 
	CString csMotorRCount = _T("");
	csMotorRCount.Format("%d", m.m_Motor.Inserter.RCount );
	m_wndCurrentHeight.SetNewText( csMotorRCount );

	// LCount
	CString csMotorLCount = _T("");
	csMotorLCount.Format("%d", m.m_Motor.Inserter.LCount );
	m_wndResult.SetNewText( csMotorLCount );
}
void CDlgManualContact::UpdatePositionStatus()
{
	CString csAlignment = _T("");
	csAlignment.Format("%d", (int)m.m_Align.TestSite.contact );
	m_wndCommandContactHeight.SetNewText( csAlignment );
}
void CDlgManualContact::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	//
	if(bShow)
		ReDrawUI();

	// 1.0Ab
	if(bShow)
		ReDrawForTsMode();

	// 1.0Ab
	if(bShow)
		ReDrawForTsVacc();

	CDialog::OnShowWindow(bShow, nStatus);	
}
void CDlgManualContact::ReDrawForTsVacc()
{
	if( m.m_ManualContactMode.bIsTsKeepVaccOn == 1 )
		m_btnTestSiteVacc.SetIcon(IDI_SOCKET_NO_VACC);
	else
		m_btnTestSiteVacc.SetIcon(IDI_SOCKET_VACC);;
}
void CDlgManualContact::ReDrawForTsMode()
{
	if( m.m_ManualContactMode.bIsTsDirectContact == 1 )
		m_btnTestSiteMode.SetIcon(IDI_TS_MODE_DIRECT);		// Direct Contact
	else
		m_btnTestSiteMode.SetIcon(IDI_TS_MODE_NO_DIRECT);	// No Direct Contact
}
void CDlgManualContact::GetButtonDistance(int &Width, int &Height, int &WDistance, int &HDistance)
{
	// 取得 Option Button 的寬度, 和兩個按鈕之間的距離.
	CRect Rect;
	GetDlgItem(IDC_INDEX1)->GetClientRect( &Rect );
	Width = Rect.right - Rect.left;
	Height = Rect.bottom - Rect.top;

	//	
	CRect Rect1;
	GetDlgItem(IDC_INDEX1)->GetWindowRect( &Rect1 );
	WDistance = _MC_ICON_W;
	HDistance = _MC_ICON_H;
//	Distance = Rect.right - Rect.left + 5;
}
void CDlgManualContact::ReDrawUI() 
{
	//////////////////////////////////////////////////////////////////////
	// 重設介面
	RECT rt;
	::GetWindowRect(::GetDlgItem(m_hWnd, IDC_INDEX1), &rt);
	::MapWindowPoints(NULL, m_hWnd, (LPPOINT)&rt, 2);	
	
	RECT rtW[_MC_ICON_Max];
	bool rtUse[_MC_ICON_Max];
	for(int i=0;i<_MC_ICON_Max;i++)
		rtUse[i] = false;

	//
	for(i=0;i<_MC_ICON_Max;i++)
		rtW[i] = rt;
	
	//
	int iButtonWidth		= 0;
	int iButtonHeight		= 0;
	int iButtonWDistance	= 0;
	int iButtonHDistance	= 0;
	GetButtonDistance( iButtonWidth, iButtonHeight, iButtonWDistance, iButtonHDistance );
	//
	for(i=0;i<_MC_ICON_Max;i++)
	{
		int x = i % _MC_ICON_Max_Row;
		int y = i / _MC_ICON_Max_Row;
		rtW[i].left		= rt.left + ( iButtonWidth * x ) + ( iButtonWDistance * x );
		rtW[i].right	= rt.right	+ ( iButtonWidth * x ) + ( iButtonWDistance * x );

		rtW[i].top		= rt.top + ( iButtonHeight * y ) + ( iButtonHDistance * y );
		rtW[i].bottom	= rt.bottom + ( iButtonHeight * y ) + ( iButtonHDistance * y );
	}

	// Torque
	if( m.m_MCFunction.m_bEnableTorqueControl == 1 )
	{
		m_btnTorqueControl.ShowWindow( TRUE );
		for(i=0;i<_MC_ICON_Max;i++)
		{
			if( !rtUse[i] )
			{
				rtUse[i] = true;
				m_btnTorqueControl.MoveWindow(&rtW[i]);
				break;
			}
		}
	}
	else
		m_btnTorqueControl.ShowWindow( FALSE );

	// Temperature 
	if( m.m_MCFunction.m_bEnableTemperatureControl == 1 )
	{
		m_btnTemperature.ShowWindow( TRUE );
		for(i=0;i<_MC_ICON_Max;i++)
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
		m_btnTemperature.ShowWindow( FALSE );

	// Interface Testing
	if( m.m_MCFunction.m_bEnableInterfaceTesting == 1 )
	{
		m_btnInterfaceTesting.ShowWindow( TRUE );
		for(i=0;i<_MC_ICON_Max;i++)
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

	// Offset 	
	if( m.m_MCFunction.m_bEnableOffsetControl == 1 )
	{
		m_btnOffset.ShowWindow( TRUE );
		for(i=0;i<_MC_ICON_Max;i++)
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

	// Manual Contact Test Site Contact Mode
	if( m.m_MCFunction.m_bEnableTestDirectContact == 1 )
	{
		m_btnTestSiteMode.ShowWindow( TRUE );
		for(i=0;i<_MC_ICON_Max;i++)
		{
			if( !rtUse[i] )
			{
				rtUse[i] = true;
				m_btnTestSiteMode.MoveWindow(&rtW[i]);
				break;
			}
		}
	}
	else
		m_btnTestSiteMode.ShowWindow( FALSE );

	// Manual Contact Test Vacc
	if( m.m_MCFunction.m_bEnableTestSiteVacc == 1 )
	{
		m_btnTestSiteVacc.ShowWindow( TRUE );
		for(i=0;i<_MC_ICON_Max;i++)
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
}
void CDlgManualContact::OnOK() 
{
	m.Info.bSubDlgOpen = false;
	f.UpdateButtonState();
	
	CDialog::OnOK();
}

void CDlgManualContact::OnCancel() 
{
	if( m_bAlarm )
	{
		// Up uncomplete
		m.Info.iStatus = theApp.enUninitial;
		m.Info.bSubDlgOpen = false;
		f.UpdateButtonState();		
	}
	else
	{		
		if( m_bUpOK )
		{
			// Up OK
			m.Info.iStatus = theApp.enReady;
			m.Info.bSubDlgOpen = false;
			f.UpdateButtonState();
		}
		else
		{
			// Call Up
			OnFUp();
			
			// Auto Up
			CDlgManualContactRecover dlg;
			theApp.m_DlgManualContactRecover = &dlg;
			if( IDOK == dlg.DoModal() )
			{
				// Up complete
				m.Info.iStatus = theApp.enReady;
				m.Info.bSubDlgOpen = false;
				f.UpdateButtonState();
			}
			else
			{
				// Up uncomplete
				m.Info.iStatus = theApp.enUninitial;
				m.Info.bSubDlgOpen = false;
				f.UpdateButtonState();
			}
		}
	}

	CDialog::OnCancel();
}

void CDlgManualContact::OnFTemperature() 
{
	
}

void CDlgManualContact::OnFInterfaceTesting() 
{
	CDlgTestTesting dlg;
	theApp.m_DlgTesting = &dlg;
	dlg.DoModal();

	m.Info.bSubDlgOpen = true;
	f.UpdateButtonState();
}

void CDlgManualContact::OnFOffset() 
{
	CDlgOffsetTS dlg;
	dlg.DoModal();
	m.Info.bSubDlgOpen = true;
	f.UpdateButtonState();
}
void CDlgManualContact::OnFTsMode() 
{
	if( m.m_ManualContactMode.bIsTsDirectContact == 1 )
		m.m_ManualContactMode.bIsTsDirectContact = 0;
	else
		m.m_ManualContactMode.bIsTsDirectContact = 1;

	f.SaveManualContactTsMode();

	//
	ReDrawForTsMode();
}
void CDlgManualContact::OnFTsVacc() 
{
	if( m.m_ManualContactMode.bIsTsKeepVaccOn == 1 )
		m.m_ManualContactMode.bIsTsKeepVaccOn = 0;
	else
		m.m_ManualContactMode.bIsTsKeepVaccOn = 1;

	f.SaveManualContactTsMode();

	//
	ReDrawForTsVacc();
}
void CDlgManualContact::UILockForContact()
{
	BOOL m_bEnable = FALSE;
	m_btnFUp.EnableWindow( m_bEnable );
	m_btnFMove.EnableWindow( m_bEnable );
	m_btnFDown.EnableWindow( m_bEnable );
}
void CDlgManualContact::UILockForUp()
{
	BOOL m_bEnable = FALSE;
	m_btnFUp.EnableWindow( m_bEnable );
	m_btnFMove.EnableWindow( m_bEnable );
	m_btnFDown.EnableWindow( m_bEnable );
}
void CDlgManualContact::UIUnLockForContacted()
{
	BOOL m_bEnable = FALSE;
	m_btnFUp.EnableWindow( !m_bEnable );
	m_btnFMove.EnableWindow( !m_bEnable );
	m_btnFDown.EnableWindow( m_bEnable );
}
void CDlgManualContact::UIUnLockForUPed()
{
	BOOL m_bEnable = FALSE;
	m_btnFUp.EnableWindow( m_bEnable );
	m_btnFMove.EnableWindow( m_bEnable );
	m_btnFDown.EnableWindow( !m_bEnable );
}
void CDlgManualContact::OnFUp() 
{
	UILockForContact();
	UILockFunction();
	m.Info.iStatus = theApp.enManual;
	f.UpdateButtonState();
	theApp.m_tManualCtrl.RequestUp();
}
void CDlgManualContact::OnFDown() 
{
	UILockForUp();
	UILockFunction();
	m.Info.iStatus = theApp.enManual;
	f.UpdateButtonState();
	m_bUpOK = false;
	theApp.m_tManualCtrl.RequestContact();
}

void CDlgManualContact::OnFMove() 
{
	UILockForContact();
	UILockFunction();
	m.Info.iStatus = theApp.enManual;
	f.UpdateButtonState();
	theApp.m_tManualCtrl.RequestMove();
}
void CDlgManualContact::UILockFunction()
{
	BOOL m_bEnable = FALSE;
	m_btnTemperature.EnableWindow( m_bEnable );
	m_btnOffset.EnableWindow( m_bEnable );
	m_btnInterfaceTesting.EnableWindow( m_bEnable );
	m_btnTorqueControl.EnableWindow( m_bEnable );
	m_btnTestSiteMode.EnableWindow( m_bEnable );
	m_btnTestSiteVacc.EnableWindow( m_bEnable );
	m_btnCancel.EnableWindow( m_bEnable );
	m_btnOK.EnableWindow( m_bEnable );
}
void CDlgManualContact::UIUnLockFunction()
{
	BOOL m_bEnable = TRUE;
	m_btnTemperature.EnableWindow( m_bEnable );
	m_btnTorqueControl.EnableWindow( m_bEnable );
	m_btnTestSiteMode.EnableWindow( m_bEnable );
	m_btnTestSiteVacc.EnableWindow( m_bEnable );
	m_btnOffset.EnableWindow( m_bEnable );
	m_btnInterfaceTesting.EnableWindow( m_bEnable );
	m_btnCancel.EnableWindow( m_bEnable );
	m_btnOK.EnableWindow( m_bEnable );
}
void CDlgManualContact::UIContactedLockFunction()
{
	BOOL m_bEnable = FALSE;
	m_btnTestSiteMode.EnableWindow( m_bEnable );
	m_btnTestSiteVacc.EnableWindow( m_bEnable );
}
void CDlgManualContact::UIUpUnLockFunction()
{
	BOOL m_bEnable = TRUE;
	m_btnTestSiteMode.EnableWindow( m_bEnable );
	m_btnTestSiteVacc.EnableWindow( m_bEnable );
}
LRESULT CDlgManualContact::OnTSContacted(WPARAM p, LPARAM l)
{
	UIUnLockForContacted();
	UIUnLockFunction();
	UIContactedLockFunction();
	f.ButtonStop();
	return TRUE;
}
LRESULT CDlgManualContact::OnTSUped(WPARAM p, LPARAM l)
{
	UIUnLockForUPed();
	UIUnLockFunction();
	UIUpUnLockFunction();
	m_bUpOK = true;
	f.ButtonStop();
	return TRUE;
}
LRESULT CDlgManualContact::OnTSMved(WPARAM p, LPARAM l)
{
	UIUnLockForContacted();
	UIUnLockFunction();
	UIContactedLockFunction();
	f.ButtonStop();
	return TRUE;
}
LRESULT CDlgManualContact::OnAlarm(WPARAM p, LPARAM l)
{
	m_bAlarm = true;
	ErrorBackupUI();
	return TRUE;
}
void CDlgManualContact::ErrorBackupUI()
{
	bManualUpStatus		= m_btnFUp.IsWindowEnabled();
	bManualDownStatus	= m_btnFDown.IsWindowEnabled();
	bManualMoveStatus	= m_btnFMove.IsWindowEnabled();

	m_btnFUp.EnableWindow( FALSE );
	m_btnFDown.EnableWindow( FALSE );
	m_btnFMove.EnableWindow( FALSE );
	m_btnCancel.EnableWindow( TRUE );
	m_btnFContinue.EnableWindow( TRUE );

}
void CDlgManualContact::ErrorRecoverUI()
{
	m_btnFUp.EnableWindow( bManualUpStatus );
	m_btnFDown.EnableWindow( bManualDownStatus );
	m_btnFMove.EnableWindow( bManualMoveStatus );
	m_btnCancel.EnableWindow( FALSE );
}
void CDlgManualContact::OnFTorque() 
{
//	CDlgManualContactTorque dlg;
//	dlg.DoModal();

	CDlgManualContactTorqueKgf dlg;
	dlg.DoModal();
}

void CDlgManualContact::OnFContinue() 
{
	m_btnFContinue.EnableWindow( FALSE );
	m_bAlarm = false;
	ErrorRecoverUI();
	f.ButtonStart();
}


