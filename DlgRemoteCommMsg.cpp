// DlgRemoteCommMsg.cpp : implementation file
//

#include "stdafx.h"
#include "deer.h"
#include "DlgRemoteCommMsg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgRemoteCommMsg dialog


CDlgRemoteCommMsg::CDlgRemoteCommMsg(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgRemoteCommMsg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgRemoteCommMsg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	m_bCommandLoopRun = false;

	hProcess = NULL;

	tSpend = COleDateTime::GetCurrentTime();
}


void CDlgRemoteCommMsg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgRemoteCommMsg)
	DDX_Control(pDX, IDC_STATIC_SPEND_TIME,		m_wndSpendTime);
	DDX_Control(pDX, IDC_F_CORDNATION_ROW,		m_cbxCoordnationRow);
	DDX_Control(pDX, IDC_F_CORDNATION_COL,		m_cbxCoordnationCol);
	DDX_Control(pDX, IDC_F_CORDNATION_TRAY,		m_cbxCoordnationTray);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDlgRemoteCommMsg, CDialog)
	//{{AFX_MSG_MAP(CDlgRemoteCommMsg)
	ON_BN_CLICKED(IDC_F_GETSTATUS,				OnFGetstatus)
	ON_BN_CLICKED(IDC_F_VERSION,				OnFVersion)
	ON_BN_CLICKED(IDC_F_GETSITE_TEMP,			OnFGetsiteTemp)
	ON_BN_CLICKED(IDC_F_SETSITE_TEMP,			OnFSetsiteTemp)
	ON_BN_CLICKED(IDC_F_ENABLE_TEMP,			OnFEnableTemp)
	ON_BN_CLICKED(IDC_F_ENABLE_TEMP2,			OnFEnableTemp2)
	ON_BN_CLICKED(IDC_F_ENABLE_ROTA,			OnFEnableRota)
	ON_BN_CLICKED(IDC_F_ENABLE_ROTA2,			OnFEnableRota2)
	ON_BN_CLICKED(IDC_F_CHANGE_ROTA,			OnFChangeRota)
	ON_BN_CLICKED(IDC_F_CHANGE_ROTA2,			OnFChangeRota2)
	ON_BN_CLICKED(IDC_F_CHANGE_ROTA3,			OnFChangeRota3)
	ON_BN_CLICKED(IDC_F_CHANGE_ROTA4,			OnFChangeRota4)
	ON_BN_CLICKED(IDC_F_ENABLE_CCD,				OnFEnableCcd)
	ON_BN_CLICKED(IDC_F_ENABLE_CCD2,			OnFEnableCcd2)
	ON_BN_CLICKED(IDC_F_SET_COORDNATION,		OnFSetCoordnation)
	ON_BN_CLICKED(IDC_F_GET_COORDNATION,		OnFGetCoordnation)
	ON_BN_CLICKED(IDC_F_CHANGE_AUTOSKIP,		OnFChangeAutoskip)
	ON_BN_CLICKED(IDC_F_CHANGE_AUTOSKIP2,		OnFChangeAutoskip2)
	ON_BN_CLICKED(IDC_F_GET_AUTOSKIP,			OnFGetAutoskip)
	ON_BN_CLICKED(IDC_F_GET_TRAYSPEC,			OnFGetTrayspec)
	ON_BN_CLICKED(IDC_F_SET_COORDNATION2,		OnFSetCoordnation2)
	ON_BN_CLICKED(IDC_F_SET_CUSTOM_COORDNATION, OnFSetCustomCoordnation)
	ON_BN_CLICKED(IDC_F_GET_COORDNATION_GO,		OnFGetCoordnationGo)
	ON_BN_CLICKED(IDC_F_GET_COORDNATION_RETURN, OnFGetCoordnationReturn)
	ON_BN_CLICKED(IDC_F_PICK_LOOP_START,		OnFPickLoopStart)
	ON_BN_CLICKED(IDC_F_PICK_LOOP_STOP,			OnFPickLoopStop)
	ON_BN_CLICKED(IDC_F_GETSITE_TEMP_MEAS,		OnFGetsiteTempMeas)
	ON_BN_CLICKED(IDC_F_SET_SETCOORDNATION_CLEAR_GO, OnFSetSetcoordnationClearGo)
	ON_BN_CLICKED(IDC_F_GETSTATE,				OnFGetstate)
	ON_BN_CLICKED(IDC_F_GETHELP,				OnFGethelp)
	ON_BN_CLICKED(IDC_F_GET_ROTA,				OnFGetRota)
	ON_BN_CLICKED(IDC_F_SET_PRESSURE,			OnFSetPressure)
	ON_BN_CLICKED(IDC_F_GET_PRESSURE,			OnFGetPressure)
	ON_BN_CLICKED(IDC_F_BUTTON_INITIAL,			OnFButtonInitial)
	ON_BN_CLICKED(IDC_F_BUTTON_START,			OnFButtonStart)
	ON_BN_CLICKED(IDC_F_BUTTON_STOP,			OnFButtonStop)
	ON_BN_CLICKED(IDC_F_BUTTON_RETRY,			OnFButtonRetry)
	ON_BN_CLICKED(IDC_F_BUTTON_SKIP,			OnFButtonSkip)
	ON_BN_CLICKED(IDC_F_BUTTON_RESET,			OnFButtonReset)
	ON_BN_CLICKED(IDC_F_BUTTON_ONECYCLE,		OnFButtonOnecycle)
	ON_BN_CLICKED(IDC_F_SET_TS_VACC,			OnFSetTsVacc)
	ON_BN_CLICKED(IDC_F_SET_TS_VACC2,			OnFSetTsVacc2)
	ON_BN_CLICKED(IDC_F_GET_TS_VACC,			OnFGetTsVacc)

	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgRemoteCommMsg message handlers

BOOL CDlgRemoteCommMsg::PreTranslateMessage(MSG* pMsg) 
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

BOOL CDlgRemoteCommMsg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	InitCustomCoordnation();

	LockUI( true );
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
void CDlgRemoteCommMsg::InitCustomCoordnation()
{
	// Tray
	m_cbxCoordnationTray.InsertString(0, "0");
	m_cbxCoordnationTray.InsertString(1, "1");
	m_cbxCoordnationTray.SetCurSel(0);

	// Col
	for(int i=0;i<50;i++)
	{
		CString csCol = _T("");
		csCol.Format("%d", i);
		m_cbxCoordnationCol.InsertString(i, csCol );
	}
	m_cbxCoordnationCol.SetCurSel(0);

	// Row
	for(int j=0;j<50;j++)
	{
		CString csRow = _T("");
		csRow.Format("%d", j);
		m_cbxCoordnationRow.InsertString(j, csRow);
	}
	m_cbxCoordnationRow.SetCurSel(0);
}
UINT CDlgRemoteCommMsg::ThreadCommandLoopThread(LPVOID p)
{
	CDlgRemoteCommMsg *pt = (CDlgRemoteCommMsg *)p;

	long iCommandCount = 0;
	bool bIsGo = false;
	while(1)
	{
		// Test Communication Command
		//////////////////////////////////////////////////////////
		if( m.Info.iStatus == theApp.enReady && !bIsGo )
		{
			Sleep(700);
			/* Arm Ready to Pick IC */
			bIsGo = true;
			m.m_TestInterface.RemoteCommAddBuffer( "<<SetCoordinatesGo:>>" );
		}
		else if( theApp.m_tInserter.GetThreadMotionStatus() == theApp.m_tInserter.enTestSiteRemoteWaitCmd )
		{
			/* Arm return IC to tray */
			Sleep(10);
			m.m_TestInterface.RemoteCommAddBuffer( "<<SetCoordinatesReturn:>>" );

			bIsGo = false;
			
			// Debug
			CString csMsg = _T("");
			csMsg.Format("Command Thread Running #%.5d\n", iCommandCount );	iCommandCount++;
			TRACE( csMsg );
		}
		else 
			; // Nerver be here
		
		// Show Time
		COleDateTimeSpan t = COleDateTime::GetCurrentTime() - pt->tSpend;
		long spent = (long)t.GetTotalSeconds();
		CString csRunTime = _T("");
		csRunTime.Format("%s, (%d))", pt->GetRunTimeTime( spent ), iCommandCount );;
		pt->m_wndSpendTime.SetWindowText( csRunTime );

		// Exit Thread
		if( pt->m_bCommandLoopRun == false )
			break;

		// Exit Program
		if( !m.Info.bRunning)
			break;

		Sleep(25);
	}

	TRACE("~CommandThread\n");
	AfxEndThread(0);
	return 0;
}
CString CDlgRemoteCommMsg::GetRunTimeTime(long lsecs)
{
	CString csRunTime = _T("");
	int ihh = 0;	// hours
	int imm = 0;	// min
	int iss = 0;	// sec
	int idd	= 0;	// day

	if( lsecs != 0 )
	{		
		int s = 0;
		int min2 = 0;
		int s2 = 0;
		int h2 = 0;

		// secs
		iss = lsecs % 60;

		// mins
		s2 = lsecs / 60;
		imm = s2 % 60;

		// hours
		min2 = s2 / 60;
		ihh = min2 % 24;

		// day
		h2 = min2 / 24;
		idd = h2 % 24;
	}

	csRunTime.Format("%.3d:%.2d:%.2d:%.2d", idd, ihh, imm, iss );	

	return csRunTime;
}
void CDlgRemoteCommMsg::LockUI(bool bEnable)
{
	BOOL bEnableUI = FALSE;
	if( bEnable )
		bEnableUI = TRUE;
	else
		bEnableUI = FALSE;

	GetDlgItem(IDC_F_BUTTON_INITIAL )->EnableWindow( bEnableUI );
	GetDlgItem(IDC_F_BUTTON_START )->EnableWindow( bEnableUI );
	GetDlgItem(IDC_F_BUTTON_STOP )->EnableWindow( bEnableUI );
	GetDlgItem(IDC_F_BUTTON_RETRY )->EnableWindow( bEnableUI );
	GetDlgItem(IDC_F_BUTTON_SKIP )->EnableWindow( bEnableUI );
	GetDlgItem(IDC_F_BUTTON_RESET )->EnableWindow( bEnableUI );
	GetDlgItem(IDC_F_BUTTON_ONECYCLE )->EnableWindow( bEnableUI );
	GetDlgItem(IDC_F_GET_ROTA )->EnableWindow( bEnableUI );
	GetDlgItem(IDC_F_GETSTATE )->EnableWindow( bEnableUI );
	GetDlgItem(IDC_F_GETHELP )->EnableWindow( bEnableUI );
	GetDlgItem(IDC_F_GETSTATUS )->EnableWindow( bEnableUI );
	GetDlgItem(IDC_F_VERSION )->EnableWindow( bEnableUI );
	GetDlgItem(IDC_F_GETSITE_TEMP )->EnableWindow( bEnableUI );
	GetDlgItem(IDC_F_SETSITE_TEMP )->EnableWindow( bEnableUI );
	GetDlgItem(IDC_F_GETSITE_TEMP_MEAS )->EnableWindow( bEnableUI );
	GetDlgItem(IDC_F_SET_SETCOORDNATION_CLEAR_GO )->EnableWindow( bEnableUI );
	GetDlgItem(IDC_F_ENABLE_TEMP )->EnableWindow( bEnableUI );
	GetDlgItem(IDC_F_ENABLE_TEMP2 )->EnableWindow( bEnableUI );
	GetDlgItem(IDC_F_ENABLE_ROTA )->EnableWindow( bEnableUI );
	GetDlgItem(IDC_F_ENABLE_ROTA2 )->EnableWindow( bEnableUI );
	GetDlgItem(IDC_F_CHANGE_ROTA )->EnableWindow( bEnableUI );
	GetDlgItem(IDC_F_CHANGE_ROTA2 )->EnableWindow( bEnableUI );
	GetDlgItem(IDC_F_CHANGE_ROTA3 )->EnableWindow( bEnableUI );
	GetDlgItem(IDC_F_CHANGE_ROTA4 )->EnableWindow( bEnableUI );
	GetDlgItem(IDC_F_ENABLE_CCD )->EnableWindow( bEnableUI );
	GetDlgItem(IDC_F_ENABLE_CCD2 )->EnableWindow( bEnableUI );
	GetDlgItem(IDC_F_SET_COORDNATION )->EnableWindow( bEnableUI );
	GetDlgItem(IDC_F_GET_COORDNATION )->EnableWindow( bEnableUI );
	GetDlgItem(IDC_F_CHANGE_AUTOSKIP )->EnableWindow( bEnableUI );
	GetDlgItem(IDC_F_CHANGE_AUTOSKIP2 )->EnableWindow( bEnableUI );
	GetDlgItem(IDC_F_GET_AUTOSKIP )->EnableWindow( bEnableUI );
	GetDlgItem(IDC_F_GET_TRAYSPEC )->EnableWindow( bEnableUI );
	GetDlgItem(IDC_F_SET_COORDNATION2 )->EnableWindow( bEnableUI );
	GetDlgItem(IDC_F_SET_CUSTOM_COORDNATION )->EnableWindow( bEnableUI );
	GetDlgItem(IDC_F_GET_COORDNATION_GO )->EnableWindow( bEnableUI );
	GetDlgItem(IDC_F_GET_COORDNATION_RETURN )->EnableWindow( bEnableUI );
	GetDlgItem(IDC_F_PICK_LOOP_START )->EnableWindow( bEnableUI );
	GetDlgItem(IDC_F_CORDNATION_TRAY )->EnableWindow( bEnableUI );
	GetDlgItem(IDC_F_CORDNATION_COL )->EnableWindow( bEnableUI );
	GetDlgItem(IDC_F_CORDNATION_ROW )->EnableWindow( bEnableUI );
	GetDlgItem(IDC_F_SET_PRESSURE )->EnableWindow( bEnableUI );
	GetDlgItem(IDC_F_GET_PRESSURE )->EnableWindow( bEnableUI );
	GetDlgItem(IDC_F_SET_TS_VACC )->EnableWindow( bEnableUI );
	GetDlgItem(IDC_F_SET_TS_VACC2 )->EnableWindow( bEnableUI );
	GetDlgItem(IDC_F_GET_TS_VACC )->EnableWindow( bEnableUI );
	GetDlgItem(IDC_F_PICK_LOOP_STOP )->EnableWindow( !bEnableUI );
}
void CDlgRemoteCommMsg::CloseCommandThread()
{
	m_bCommandLoopRun = false;


	MSG				msg;
	LARGE_INTEGER	start, end, freq;
	DWORD			nThreadExitCode = 0;
	BOOL			bSuccess = FALSE;

	::QueryPerformanceFrequency(&freq);
	::QueryPerformanceCounter(&start);
	if(hProcess != NULL)
	{
	do
	{
		bSuccess = GetExitCodeThread(hProcess, &nThreadExitCode);
		::QueryPerformanceCounter(&end);

		if(::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			::TranslateMessage(&msg);
			::DispatchMessage(&msg);
		}
	}while(bSuccess && nThreadExitCode == STILL_ACTIVE && (end.QuadPart - start.QuadPart) / freq.QuadPart < 10);  //10秒表示等10s, 可依據需求修改
	}
}
void CDlgRemoteCommMsg::OnFPickLoopStart() 
{
	LockUI( false );
	m_bCommandLoopRun = true;
	tSpend = COleDateTime::GetCurrentTime();

	CWinThread *pWindThread = NULL;
	pWindThread = AfxBeginThread(ThreadCommandLoopThread, this);

	if(pWindThread)
		hProcess = pWindThread->m_hThread;
}

void CDlgRemoteCommMsg::OnFPickLoopStop() 
{
	CloseCommandThread();
	LockUI( true );	// unlock the UI
}
void CDlgRemoteCommMsg::OnFGetstatus() 
{
	m.m_TestInterface.RemoteCommAddBuffer( "<<GetStatus?:>>" );	
}

void CDlgRemoteCommMsg::OnFVersion() 
{
	m.m_TestInterface.RemoteCommAddBuffer( "<<GetVersion?:>>" );
}
void CDlgRemoteCommMsg::OnFGetstate() 
{
	m.m_TestInterface.RemoteCommAddBuffer( "<<GetState?:>>" );		
}

void CDlgRemoteCommMsg::OnFGethelp() 
{
	m.m_TestInterface.RemoteCommAddBuffer( "<<GetHelp?:>>" );
}

void CDlgRemoteCommMsg::OnFGetsiteTemp() 
{
	CString csSiteTemp = _T("");
	csSiteTemp.Format("<<GetSiteTemp?:>>");
	m.m_TestInterface.RemoteCommAddBuffer( csSiteTemp );
}
void CDlgRemoteCommMsg::OnFGetsiteTempMeas() 
{
	CString csSiteTemp = _T("");
	csSiteTemp.Format("<<GetSiteSetTemp?:>>");
	m.m_TestInterface.RemoteCommAddBuffer( csSiteTemp );	
}
void CDlgRemoteCommMsg::OnFSetsiteTemp() 
{
	CString csSiteTemp = _T("");
	CString csTemp = _T("");
	double dTemp = 80.0;
	csTemp.Format("%5.2f", dTemp );

//	csSiteTemp.Format("<<SetSiteTemp: %s>>", csTemp );
	csSiteTemp.Format("<<SEtsiteTEmP: %s>>", csTemp );
	m.m_TestInterface.RemoteCommAddBuffer( csSiteTemp );
}

void CDlgRemoteCommMsg::OnFEnableTemp() 
{
	// Enable Heater
	m.m_TestInterface.RemoteCommAddBuffer( "<<EnableTemp:1>>" );	
}

void CDlgRemoteCommMsg::OnFEnableTemp2() 
{
	// Disable Heater
	m.m_TestInterface.RemoteCommAddBuffer( "<<EnableTemp:0>>" );		
}

void CDlgRemoteCommMsg::OnFEnableRota() 
{
	// Enable Rotator
	m.m_TestInterface.RemoteCommAddBuffer( "<<EnableRotator: 1>>" );		
}

void CDlgRemoteCommMsg::OnFEnableRota2() 
{
	// Disable Rotator
	m.m_TestInterface.RemoteCommAddBuffer( "<<EnableRotator: 0>>" );		
}

void CDlgRemoteCommMsg::OnFChangeRota() 
{
	// Change Rotator +90
//	m.m_TestInterface.RemoteCommAddBuffer( "<<*%ChangeRotator%1>>" );
	m.m_TestInterface.RemoteCommAddBuffer( "<<SetRotatorDegree:1>>" );
}

void CDlgRemoteCommMsg::OnFChangeRota2()
{
	// Change Rotator -90
//	m.m_TestInterface.RemoteCommAddBuffer( "<<*%ChangeRotator%0>>" );
	m.m_TestInterface.RemoteCommAddBuffer( "<<SetRotatorDegree:0>>" );
}

void CDlgRemoteCommMsg::OnFChangeRota3() 
{
	// Change Rotator 0
//	m.m_TestInterface.RemoteCommAddBuffer( "<<*%ChangeRotator%2>>" );
	m.m_TestInterface.RemoteCommAddBuffer( "<<SetRotatorDegree:2>>" );
}

void CDlgRemoteCommMsg::OnFChangeRota4() 
{
	// Change Rotator 180
//	m.m_TestInterface.RemoteCommAddBuffer( "<<*%ChangeRotator%3>>" );
	m.m_TestInterface.RemoteCommAddBuffer( "<<SetRotatorDegree:3>>" );
}

void CDlgRemoteCommMsg::OnFEnableCcd() 
{
	// Enable CCD
//	m.m_TestInterface.RemoteCommAddBuffer( "<<*%EnableCCDLogIC%1>>" );
	m.m_TestInterface.RemoteCommAddBuffer( "<<EnableCCDLog: 1>>" );
}

void CDlgRemoteCommMsg::OnFEnableCcd2() 
{
	// Enable CCD
//	m.m_TestInterface.RemoteCommAddBuffer( "<<*%EnableCCDLogIC%0>>" );
	m.m_TestInterface.RemoteCommAddBuffer( "<<EnableCCDLog: 0>>" );	
}

void CDlgRemoteCommMsg::OnFGetRota() 
{
	m.m_TestInterface.RemoteCommAddBuffer( "<<GetRotatorDegree?:>>" );
}

void CDlgRemoteCommMsg::OnFSetCoordnation() 
{
	// Set Coordnation
//	m.m_TestInterface.RemoteCommAddBuffer( "<<*%SetCoordnation%0,7,5>>" ); // tray1, col=2, row=5
	m.m_TestInterface.RemoteCommAddBuffer( "<<SetCoordinates: 0,7,5>>" ); // tray1, col=2, row=5
}
void CDlgRemoteCommMsg::OnFSetCoordnation2() 
{
//	m.m_TestInterface.RemoteCommAddBuffer( "<<*%SetCoordnation%0,1,2>>" ); // tray1, col=2, row=5
	m.m_TestInterface.RemoteCommAddBuffer( "<<SetCoordinates: 0,1,2>>" ); // tray1, col=2, row=5
}
void CDlgRemoteCommMsg::OnFGetCoordnation() 
{
	// Get Coordnation
//	m.m_TestInterface.RemoteCommAddBuffer( "<<*%GetCoordnation%>>" );
	m.m_TestInterface.RemoteCommAddBuffer( "<<GetCoordinates?:>>" );
}

void CDlgRemoteCommMsg::OnFChangeAutoskip() 
{
	// Enable AutoSkip
	m.m_TestInterface.RemoteCommAddBuffer( "<<SetAutoSkip: 1>>" );	
}

void CDlgRemoteCommMsg::OnFChangeAutoskip2() 
{
	// Disable AutoSkip
	m.m_TestInterface.RemoteCommAddBuffer( "<<SetAutoSkip: 0>>" );	
}

void CDlgRemoteCommMsg::OnFGetAutoskip() 
{
	// Get AutoSkip
	m.m_TestInterface.RemoteCommAddBuffer( "<<GetAutoSkip?:>>" );	
}

void CDlgRemoteCommMsg::OnFGetTrayspec() 
{
	// Get TraySpec
	m.m_TestInterface.RemoteCommAddBuffer( "<<GetTraySpec?:>>" );	
}

void CDlgRemoteCommMsg::OnFSetCustomCoordnation() 
{
	CString csGetTray = _T("");
	CString csGetCol = _T("");
	CString csGetRow = _T("");

	int iGetTray = m_cbxCoordnationTray.GetCurSel();
	m_cbxCoordnationTray.GetLBText(iGetTray, csGetTray );

	int iGetCol = m_cbxCoordnationCol.GetCurSel();
	m_cbxCoordnationCol.GetLBText(iGetCol, csGetCol );

	int iGetRow = m_cbxCoordnationRow.GetCurSel();
	m_cbxCoordnationRow.GetLBText(iGetRow, csGetRow);

	CString csCoordnationPos = _T("");
	csCoordnationPos.Format("%s,%s,%s", csGetTray, csGetCol, csGetRow);

	// Debug
	/*
	CString csMsg = _T(""); csMsg.Format( "%s\n", csCoordnationPos );
	TRACE( csMsg );
	*/

	CString csMessage = _T("");
//	csMessage.Format( "<<*%%SetCoordnation%%%s>>", csCoordnationPos );
	// <<SetCoordinates: 0,1,2>>
	csMessage.Format( "<<SetCoordinates:%s>>", csCoordnationPos );
	m.m_TestInterface.RemoteCommAddBuffer( csMessage );
}

void CDlgRemoteCommMsg::OnFGetCoordnationGo() 
{
//	m.m_TestInterface.RemoteCommAddBuffer( "<<*%SetCoordnationGo%>>" );
	m.m_TestInterface.RemoteCommAddBuffer( "<<SetCoordinatesGo:>>" );
}
void CDlgRemoteCommMsg::OnFSetSetcoordnationClearGo() 
{
	m.m_TestInterface.RemoteCommAddBuffer( "<<SetCoordinatesClearGo:>>" );
}

void CDlgRemoteCommMsg::OnFGetCoordnationReturn() 
{
//	m.m_TestInterface.RemoteCommAddBuffer( "<<*%SetCoordnationReturn%>>" );
	m.m_TestInterface.RemoteCommAddBuffer( "<<SetCoordinatesReturn:>>" );
}
void CDlgRemoteCommMsg::OnFSetPressure() 
{
	m.m_TestInterface.RemoteCommAddBuffer( "<<SetPressure: 8>>" );
}

void CDlgRemoteCommMsg::OnFGetPressure() 
{
	m.m_TestInterface.RemoteCommAddBuffer( "<<GetPressure?:>>" );
}
void CDlgRemoteCommMsg::OnFButtonInitial() 
{
	m.m_TestInterface.RemoteCommAddBuffer( "<<SetState: INITIALIZE>>" );
}

void CDlgRemoteCommMsg::OnFButtonStart() 
{
	m.m_TestInterface.RemoteCommAddBuffer( "<<SetState: START>>" );
}

void CDlgRemoteCommMsg::OnFButtonStop() 
{
	m.m_TestInterface.RemoteCommAddBuffer( "<<SetState: STOP>>" );
}

void CDlgRemoteCommMsg::OnFButtonRetry() 
{
	m.m_TestInterface.RemoteCommAddBuffer( "<<SetState: RETRY>>" );
}

void CDlgRemoteCommMsg::OnFButtonSkip() 
{
	m.m_TestInterface.RemoteCommAddBuffer( "<<SetState: SKIP>>" );
}

void CDlgRemoteCommMsg::OnFButtonReset() 
{
	m.m_TestInterface.RemoteCommAddBuffer( "<<SetState: RESET>>" );
}

void CDlgRemoteCommMsg::OnFButtonOnecycle() 
{
	m.m_TestInterface.RemoteCommAddBuffer( "<<SetState: ONECYCLE>>" );
}

void CDlgRemoteCommMsg::OnFSetTsVacc() 
{
	m.m_TestInterface.RemoteCommAddBuffer( "<<SetTsVacc: 1>>" );
}

void CDlgRemoteCommMsg::OnFSetTsVacc2() 
{
	m.m_TestInterface.RemoteCommAddBuffer( "<<SetTsVacc: 0>>" );
}

void CDlgRemoteCommMsg::OnFGetTsVacc() 
{
	m.m_TestInterface.RemoteCommAddBuffer( "<<GetTsVacc?:>>" );
}


