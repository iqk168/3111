// ThErrorCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "deer.h"
#include "ThErrorCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

static bStop = false;

/////////////////////////////////////////////////////////////////////////////
// CThErrorCtrl

IMPLEMENT_DYNCREATE(CThErrorCtrl, CWinThread)

CThErrorCtrl::CThErrorCtrl()
{
	
}

CThErrorCtrl::~CThErrorCtrl()
{
	TRACE("~CThErrorCtrl\n");
}

BOOL CThErrorCtrl::InitInstance()
{
	f.IncraseThreadCount();
	m.ThStatus.ErrCtrl.times = 1;
	while(m.Info.bRunning)
	{
		m.ThStatus.ErrCtrl.times++;

		Running();
		Sleep(_Wait);
	}
	f.ReduceThreadCount();
	f.m_Log.AddLogEvent( "Thread ErrorCtrl Finish" );

	return TRUE;
}

bool CThErrorCtrl::CheckIO(bool button)
{
#ifdef _Demo
	
	return true;
	// In Demo mode.
	// We did not check IO error.
#endif

#ifdef _DEBUG
//	return true;
#endif

	if(button)
	{	
		//z
		if( m.InStatus.Emg == _EmgError )
			m.Err.IO.Code = enCodeEStop;// If E-Stop Pushed. Alarm it.	
		// Handler Door
		else if( m.InStatus.DoorSensor == _DoorNoClose && !m.Setting.m_bEnableDoorSensor )
			m.Err.IO.Code = enCodeFrontDoor;
		else if( m.InStatus.AirSourceDetect == _AirNoSource )
			m.Err.IO.Code = enErrorAirPressureFail;
		else
		{
		
		}
	}
	else
	{	
		// If normal cycle 
		// We only need to check door sensor.
		if( m.InStatus.Emg == _EmgError )
			m.Err.IO.Code = enCodeEStop; // If E-Stop Pushed. Alarm it.		
		if(!f.IsPause())
		{
			 // Note : If IsPause return false.
			// Handler Door
			if( m.InStatus.DoorSensor == _DoorNoClose && !m.Setting.m_bEnableDoorSensor )
				m.Err.IO.Code = enCodeFrontDoor;
			else if( m.InStatus.AirSourceDetect == _AirNoSource )
				m.Err.IO.Code = enErrorAirPressureFail;
			else
				;
		}
	}


	///////////////////////////////////////////////////////////////////////////////////////
	// ION Fan, ION Alarm
#if 1
	if( m.Setting.m_bIONAlarm == 1 && !m.Info.bIOMonitor )
	{
		// 如果讀到 ION Alarm 的 IO 就設定 Timer.....
		if( m.InStatus.IONAlarm && !m.IONFanAlarm )
		{
			m.IONFanAlarm = true;
			m.IONFanAlarmStart = ::GetTickCount();
		}

		// 如果讀到ION Alarm的IO, 設定過 Timer期間, 如果Alarm有消失,那表示應該是雜訊
		// 那就重設 Timer 的 flag
		if( m.IONFanAlarm )
		{
			if( !m.InStatus.IONAlarm )
			{
				m.IONFanAlarm = false;
				m.IONFanAlarmStart = 0;
			}
		}
	
		// 如果有設定過 Timer, 兩秒後還是讀到那麼就要 Alarm....
		if( m.IONFanAlarm && m.IONFanAlarmStart != 0 &&
			(::GetTickCount() - m.IONFanAlarmStart ) > _IONAlarmCheckTime )
		{
			// 兩秒後還是讀到..那就 Alarm...
			if( m.InStatus.IONAlarm )
			{
				m.IONFanAlarm = false;
				m.IONFanAlarmStart = 0;
				m.Err.IO.Code = enErrorIONAlarmFail;
			}
			else
			{
				// 兩秒後沒有讀到.. 就沒事
				m.IONFanAlarm = false;
				m.IONFanAlarmStart = 0;
			}
		}
	}
#endif
	///////////////////////////////////////////////////////////////////////////////////////

	if (m.Err.IO.Code != 0)
	{
		CheckError(m.Err.IO);
		return false;
	}
	else
		return true;
}

long CThErrorCtrl::CheckErrorHandle()
{
	if( m.RemoteOutSet.BtnInitialOn && ( m.RemoteInStatus.BtnInitialPushed == _IOButtonOn || m.PanelButton.BtnInitPushed ))
	{
		m.PanelButton.BtnInitPushed = false;
		m.RemoteOutSet.BtnInitialOn = false;
		return enBtnInitial;
	}
	// This is for Initial
	
	if( m.RemoteOutSet.BtnStartOn && ( m.RemoteInStatus.BtnStartPushed == _IOButtonOn || m.PanelButton.BtnStartPushed ))
	{
		m.PanelButton.BtnStartPushed = false;
		m.RemoteOutSet.BtnStartOn = false;
		return enBtnStart;
	}
	// This is for Start
	
	if( m.RemoteOutSet.BtnStopOn && ( m.RemoteInStatus.BtnStopPushed == _IOButtonOn || m.PanelButton.BtnStopPushed ))
	{
		m.PanelButton.BtnStopPushed = false;
		m.RemoteOutSet.BtnStopOn = false;
		return enBtnStop;
	}
	// This is for Stop

	if( m.RemoteOutSet.BtnOneCycleOn && ( m.RemoteInStatus.BtnOneCyclePushed == _IOButtonOn || m.PanelButton.BtnOneCyclePushed ))
	{
		m.PanelButton.BtnOneCyclePushed = false;
		m.RemoteOutSet.BtnOneCycleOn = false;
		return enBtnOncycle;
	}
	// This is for One Cycle

	if( m.RemoteOutSet.BtnSkipOn && ( m.RemoteInStatus.BtnSkipPushed == _IOButtonOn || m.PanelButton.BtnSkipPushed ))
	{
		m.PanelButton.BtnSkipPushed = false;
		m.RemoteOutSet.BtnSkipOn = false;
		return enBtnSkip;
	}
	// This is for Skip

	if( m.RemoteOutSet.BtnRetryOn && ( m.RemoteInStatus.BtnRetryPushed == _IOButtonOn || m.PanelButton.BtnRetryPushed ))
	{
		m.PanelButton.BtnRetryPushed = false;
		m.RemoteOutSet.BtnRetryOn = false;
		return enBtnRetry;
	}
	// This is for Retry

	if( m.RemoteOutSet.BtnResetOn && ( m.RemoteInStatus.BtnResetPushed == _IOButtonOn || m.PanelButton.BtnResetPushed ))
	{
		m.PanelButton.BtnResetPushed = false;
		m.RemoteOutSet.BtnResetOn = false;
		return enBtnReset;
	}
	// This is for Reset

	if( m.OutSet.TestSiteSkip && ( m.InStatus.TestSiteSkip == _IOBtnTSPress || m.PanelButton.BtnTestSiteSkip ))
	{
		m.PanelButton.BtnTestSiteSkip = false;
		m.OutSet.TestSiteSkip = false;
		return enBtnTestSiteSkip;
	}
	// This is for TestSkip
	/////////////////////////////////////////////////////////////

	if( m.EnginnerCloseErr )
	{
		m.EnginnerCloseErr = false;
		return enBtnSkip;
	}

	return -1;
}
void CThErrorCtrl::ManualControlMessageAlarm(int code)
{
	if( code <= 0 )
		return;

	CString cs = _T("");
	::SendMessage( theApp.m_DlgManualContact->GetSafeHwnd(), 
		WM_MANUAL_ALARM,  (WPARAM)&cs , (LPARAM)&cs );	

	::SendMessage( theApp.m_DlgManualContactRecover->GetSafeHwnd(), 
		WM_MANUAL_ALARM,  (WPARAM)&cs , (LPARAM)&cs );	
}
void CThErrorCtrl::RemoteControlMessageAlarm(int code)
{
	if( code <= 0 )
		return;

	CString cs = _T("");
	::SendMessage( theApp.m_DlgRemoteControlCustom->GetSafeHwnd(), 
		WM_REMOTE_ALARM,  (WPARAM)&cs , (LPARAM)&cs );	
}
/*
void CThErrorCtrl::AirErrorCheck(tagErrorParam &err)
{
	if( err.Code == enErrorAirPressureFail )
	{
		theApp.m_tIORemote.SetTorqueValue(0);
	}
}
void CThErrorCtrl::AirErrorRecover()
{
	if( m.UI.FileMain != "" )
		f.LoadPogoParameter();
	else
		f.LoadContactForce();
}
*/
bool CThErrorCtrl::CheckError(tagErrorParam &err)
{
	if(err.Code == 0) return true;
	err.Result = enAbort;

	m.Info.bError = true;
	m.Info.ErrorCode = err.Code;

	//
	f.InsertJamRateCounter(err.Code);

	///主動回傳
	f.m_Log.AddEvent(err.Code);

	//
	f.ErrorRateControl(err.Code);

	//
//	f.RemoteSetStateError();

	//回傳錯誤加在AddEvent
//	f.RemoteSetStatus( enRemoteCommandStatusError, err.Code);

	//
	if( m.RemoteInterlock.IsRemoteControlMode == true )
		RemoteControlMessageAlarm( err.Code );

	//
	if( m.ManualInterlok.IsManualControlMode == true )
		ManualControlMessageAlarm( err.Code );

	//
//	AirErrorCheck( err );

	// Error handling
	// Show error box
	tagErrorMsg e = f.GetErrorMsg(err.Code);
	f.SendAlarmMail(err.Code, e.Eng );
	if(e.Code == -1)
	{
		// Motion stop
		f.ButtonStop();
		CString cs = _T("");
		cs.Format("Error code not define: 0x%x", err.Code);
		AfxMessageBox(cs);
		err.Result = enAbort;
		err.Code = 0;
		m.Info.bError = false;
		m.Info.ErrorCode = 0;
		f.UpdateButtonState();
		return false;
	}
	if(e.InitialNeed)
		m.Info.iStatus = theApp.enUninitial;
	// 判斷 Handler 是否停止
	m.ThStatus.ErrCtrl.line = 1 & (err.Code << 4);
	if(e.Stop)
		f.ButtonStop();

	// Refer Error DataBase to enable button
	// -----------------------------------------------------

	m.RemoteOutSet.BtnOneCycleOn	= e.BOneCycle;
	m.RemoteOutSet.BtnInitialOn		= e.BInitial;
	m.RemoteOutSet.BtnRetryOn		= e.BRetry;
	m.RemoteOutSet.BtnSkipOn		= e.BSkip;
	m.RemoteOutSet.BtnStartOn		= e.BStart;
	m.RemoteOutSet.BtnStopOn		= e.BStop;
	m.OutSet.TestSiteSkip			= e.BTestSiteSkip;

	if( e.BRetry == 0 && e.BSkip == 0 && e.BTestSiteSkip == 0 )
		m.RemoteOutSet.BtnResetOn = true;

	if( m.Setting.m_bEnableAlarm == 1 )
		m.Info.bBuzzer = e.Alarm; // Turn on the Buzzer or not.
	// 我們可以透過 Debug Dialog 把全機的 Alarm 都關掉.!

	// -----------------------------------------------------
	m.ThStatus.ErrCtrl.line = 2 & (err.Code << 4);
	::SendMessage(theApp.m_pMainWnd->GetSafeHwnd(), WM_ERROR_OPEN, (WPARAM)&e, NULL);

	m.ThStatus.ErrCtrl.line = 3 & (err.Code << 4);
	// check response
	bool bOK = false;
	bool bBuzzerOff = false; // if true buzzer is off. else buzzer is on

	while(!bOK)
	{
		switch(CheckErrorHandle())
		{
		case enBtnInitial:
			{
				f.m_Log.AddEvent(enButtonInitialPushed);	// Add Event
				m.OutSet.TowerBuzzerOn = false;				// Trun off the Buzzer
				m.Info.bBuzzer = false; 
				err.Result = theApp.ActionInitial;
				bOK = true;
			}
			break;
		//

		case enBtnStart:
			{
				f.m_Log.AddEvent(enButtonStartPushed);		// Add Event
				m.OutSet.TowerBuzzerOn = false;				// Trun off the Buzzer
				m.Info.bBuzzer = false; 
				err.Result = theApp.ActionStart;
				bOK = true;
			}
			break;
		//

		case enBtnReset:
			{
				f.m_Log.AddEvent(enButtonResetPushed);		// Add Event
				m.OutSet.TowerBuzzerOn = false;				// Trun off the Buzzer
				m.Info.bBuzzer = false; 
//				err.Result = theApp.ActionReset;
				err.Result = theApp.ActionSkip;
				bOK = true;
			}
			break;
		//

		case enBtnStop:
			{
				f.m_Log.AddEvent(enButtonStopPushed);		// Add Event
				m.Info.bBuzzer = false; 
				m.OutSet.TowerBuzzerOn = false;		
			}
			break;
		//

		case enBtnOncycle:
			{
				f.m_Log.AddEvent(enButtonOneCyclePushed);	// Add Event
				m.OutSet.TowerBuzzerOn = false;				// Trun off the Buzzer
				m.Info.bBuzzer = false; 
				err.Result = theApp.ActionOneCycle;
				bOK = true;
			}
			break;
		//

		case enBtnSkip:
			{
				f.m_Log.AddEvent(enButtonSkipPushed);		// Add Event
				m.OutSet.TowerBuzzerOn = false;					// Trun off the Buzzer
				m.Info.bBuzzer = false; 
				err.Result = theApp.ActionSkip;
				bOK = true;
			}
			break;
		//
		case enBtnTestSiteSkip:
			{
				f.m_Log.AddEvent(enButtonSkipPushed);		// Add Event
				m.OutSet.TowerBuzzerOn = false;				// Trun off the Buzzer
				m.Info.bBuzzer = false; 
				err.Result = theApp.ActionTSSkip;
				bOK = true;
			}
			break;
		case enBtnRetry:
			{
				f.m_Log.AddEvent(enButtonRetryPushed);		// Add Event
				m.OutSet.TowerBuzzerOn = false;				// Trun off the Buzzer
				m.Info.bBuzzer = false; 
				err.Result = theApp.ActionRetry;
				bOK = true;
			}
			break;
		//

		default:
			break;
		}
		Sleep(_Wait);
	}

	err.Code = 0;
	
	m.Info.bError = false;			// this line should be upper then next line

	m.Info.bAlarmTimer = false;		// Make sure Buzzer will not buzzer again
	m.OutSet.TowerBuzzerOn = false;	// Make sure when error dialog close. Buzzer will be close too.!
	m.Info.ErrorCode = 0;
	
	::SendMessage(theApp.m_pMainWnd->GetSafeHwnd(), WM_ERROR_CLOSE, NULL, NULL);
	f.UpdateButtonState();

	// 回傳錯誤加在AddEvent
//	f.RemoteSetStatus( enRemoteCommandStatusOK, err.Code);

	//
//	f.RemoteSetStateErrorCtrl();

	return false;
}
long CThErrorCtrl::CheckButton()
{
	// If in IO Monitor page or in Manual contact page, we will
	//	use the buttons for other function.
	if(m.Info.bIOMonitor)
		return -1;

	if(m.Info.bAlignment)
		return -1;

	if( m.RemoteOutSet.BtnOneCycleOn && ( m.RemoteInStatus.BtnOneCyclePushed == _IOButtonOn || m.PanelButton.BtnOneCyclePushed ))
	{
		m.PanelButton.BtnOneCyclePushed = false;
		m.RemoteOutSet.BtnOneCycleOn = false;
		f.ButtonOneCycle();
		return enBtnOncycle;
	}
	// It is for One Cycle, But We call it "Flush"	

	if( m.RemoteOutSet.BtnStartOn && ( m.RemoteInStatus.BtnStartPushed == _IOButtonOn || m.PanelButton.BtnStartPushed ))
	{
		TRACE("Button: Start\n");
		m.PanelButton.BtnStartPushed = false;
		m.RemoteOutSet.BtnStartOn = false;
		f.ButtonStart();
		return enBtnStart;
	}
	// It is for Start
	// It will go to @1: Cycle @2: Manual @3: One Cycle	

	if( m.RemoteOutSet.BtnStopOn && ( m.RemoteInStatus.BtnStopPushed == _IOButtonOn || m.PanelButton.BtnStopPushed ))
	{
		TRACE("Button: Stop\n");
		m.PanelButton.BtnStopPushed = false;
		m.RemoteOutSet.BtnStopOn = false;
		f.ButtonStop();
		return enBtnStop;
	}
	// It is for Stop
	// It will go to @1: Cycle Stop @2 Manual Stop @3: One Cycle Stop
	// It is also control by Error

	if( m.RemoteOutSet.BtnInitialOn && ( m.RemoteInStatus.BtnInitialPushed == _IOButtonOn || m.PanelButton.BtnInitPushed ))
	{
		m.PanelButton.BtnInitPushed = false;
		m.RemoteOutSet.BtnInitialOn = false;
		f.ButtonInitial();
		return enBtnInitial;		
	}
	// It is for Stop
	// It will go to @1: Initial @2: Uninitial

	if( m.RemoteOutSet.BtnSkipOn && ( m.RemoteInStatus.BtnSkipPushed == _IOButtonOn || m.PanelButton.BtnSkipPushed ))
	{
		m.PanelButton.BtnSkipPushed = false;
		m.RemoteOutSet.BtnSkipOn = false;
		f.ButtonSkip();
		return enBtnSkip;
	}
	// It is for Skip
	// It is control by Error

	if( m.RemoteOutSet.BtnRetryOn && ( m.RemoteInStatus.BtnRetryPushed == _IOButtonOn || m.PanelButton.BtnRetryPushed ))
	{
		m.PanelButton.BtnRetryPushed = false;
		m.RemoteOutSet.BtnRetryOn = false;
		f.ButtonRetry();
		return enBtnRetry;
	}
	// It is for Retry
	// It is control by Error

	if( m.RemoteOutSet.BtnResetOn && ( m.RemoteInStatus.BtnResetPushed == _IOButtonOn || m.PanelButton.BtnResetPushed ))
	{
		m.PanelButton.BtnResetPushed = false;
		m.RemoteOutSet.BtnResetOn = false;
		f.ButtonReset();
		return enBtnReset;
	}
	// This for clear error dialog

	return -1;
}
void CThErrorCtrl::Running()
{
#ifdef _Demo
#else
//	if(!m.InterLock.IsIORead)
//		return;
#endif
	// Note : When IO read . Then we can check Error.
	// Give sometime to read IO.

	// 1. Wait until other thread errors are cleared
	m.ThStatus.ErrCtrl.line = 0x100;
	CheckError(m.Err.System);	

	m.ThStatus.ErrCtrl.line = 0x200;
	CheckError(m.Err.Arm );	
	// Check Arm Error

	m.ThStatus.ErrCtrl.line = 0x300;
	CheckError( m.Err.Inserter );	
	// Check Inserter Error

	m.ThStatus.ErrCtrl.line = 0x400;
	CheckError(m.Err.Inspect );	
	// Check Inspect Error

	m.ThStatus.ErrCtrl.line = 0x500;
	CheckError(m.Err.Tester );	
	// Check Tester Error

	m.ThStatus.ErrCtrl.line = 0x600;
	CheckError(m.Err.Manual );
	// Check Manual Error

	// 2. Check Door and E-Stop
	m.ThStatus.ErrCtrl.line = 0x700;
	CheckIO(false);

	// 3. Check button if it is pressed
	m.ThStatus.ErrCtrl.line = 0x800;
	CheckButton();

	m.ThStatus.ErrCtrl.line = 0;
}

int CThErrorCtrl::ExitInstance()
{
	TRACE("CThErrorCtrl\n");
	// TODO:  perform any per-thread cleanup here
	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(CThErrorCtrl, CWinThread)
	//{{AFX_MSG_MAP(CThErrorCtrl)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CThErrorCtrl message handlers
