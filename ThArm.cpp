// ThArm.cpp : implementation file
//

#include "stdafx.h"
#include "deer.h"
#include "ThArm.h"

// 
#include "Motor.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CThArm

IMPLEMENT_DYNCREATE(CThArm, CWinThread)

CThArm::CThArm()
{
	m_bStatus								= enIdle;	
	m_iRunError								= enCodeRunOK;
	m_bInitialized							= false;
	m_bInitialRequest						= false;

	m_ZWithIC								= false;

	ArmLog.csCode							= "";
	ArmLog.iBin								= -1;
	ArmLog.iSetTemperature					= -1;
	ArmLog.iBooking							= -1;
	ArmLog.iTray							= -1;
	ArmLog.iPF								= -1;
	// Arm Log default value

	RotatorNOK								= false;
	RotatorPOK								= false;

	m_lArmRetryCounter						= 0;

	m_bFix1TrayFull							= false;

	m_bInputEmpty							= false;

	bRepeatInputEmpty						= false;

	m_bInTrayMissingError					= false;

	m_bTSRemainICEnable						= false;

	m_TSRemainWithIC						= false;

	m_bHeaterStableNeed						= false;
	m_bWaitHeaterOK							= false;
	m_bWaitHeaterStableOK					= false;

	bCCDPin1MatchOK							= false;
	
	bRepeatTray2OutputFull					= false;
	bRepeatTray1OutputFull					= false;

	m_bMissionOnTheGo						= false;
	m_RemoteArmTray.m_iRemoteBooking		= 0;
	m_RemoteArmTray.m_iRemoteTray			= 0;
}

CThArm::~CThArm()
{
	TRACE("~CThArm\n");	
}

BOOL CThArm::InitInstance()
{
	f.IncraseThreadCount();
	m.ThStatus.ArmCtrl.times = 1;
	while(m.Info.bRunning)
	{
		m.ThStatus.ArmCtrl.times++;
		Running();
		Sleep(_Wait);
	}
	f.ReduceThreadCount();
	f.m_Log.AddLogEvent( "Thread Arm Finish" );

	return TRUE;
}

void CThArm::InitialStart()
{
	m_bInitialRequest = true;
}

void CThArm::InitFlag()
{
	//
	bRepeatTray2OutputFull	= false;
	bRepeatTray1OutputFull	= false;
	bRepeatInputEmpty		= false;
	m_bInputEmpty			= false;
	m_bInTrayMissingError	= false;
	m_bTSRemainICEnable		= false;
	m_bHeaterStableNeed		= false;
	m_bWaitHeaterOK			= false;
	m_bWaitHeaterStableOK	= false;
	//

	bCCDPin1MatchOK			= false;
}
void CThArm::Initialize()
{
	// 1.0Aj
	// Bypass Initial
#ifdef _Demo

	// Initial Remote Control
	InitialMissionOnTheGo();

	// Initial Arm Auto Retry 
	InitAutoRetry();

	// Initial Arm flag
	InitFlag();

	// ArmZ
	m.InterLock.InitialArmZEnd = true;
	m.MotorStatus.ArmZInitialed = true;
	m.MotorStatus.ArmZ = _T("Arm Z Initial OK.");
	m.InitialInterLock.InitialArmZUpOK	= true;

	// Arm Y
	m.InterLock.InitialArmYEnd = true;
	m.MotorStatus.ArmYInitialed = true;
	m.MotorStatus.ArmY = _T("Arm Y Initial OK.");
	m_bInitialized = true;

	return;
#endif


	m_bInitialized = false;
	m.MotorStatus.ArmY = _T("Initialing, Wait for TS OK.");
	m.MotorStatus.ArmZ = _T("Initialing, Wait for TS OK.");

	// Initial Remote Control
	InitialMissionOnTheGo();

	// Initial Arm Auto Retry 
	InitAutoRetry();

	// Initial Arm flag
	InitFlag();

	// 清除錯誤
	f.Motor.ClearMotorAlarm( &m.m_Motor.ArmX );
	f.Wait(2000);
	f.Motor.ClearMotorAlarm( &m.m_Motor.ArmY );
	f.Wait(2000);
	f.Motor.ClearMotorAlarm( &m.m_Motor.ArmZ );
	f.Wait(2000);
	
	f.Motor.ClearMotorError( &m.m_Motor.ArmX );
	f.Wait(2000);
	f.Motor.ClearMotorError( &m.m_Motor.ArmY );
	f.Wait(2000);
	f.Motor.ClearMotorError( &m.m_Motor.ArmZ );	
	f.Wait(2000);

	// Initial 要把 InPos Range 範圍縮小, 不是 Initial 要再重新設定回來.!
	long oldYInPos = m.m_Motor.ArmY.InPosRange;
	m.m_Motor.ArmY.InPosRange = _InitialInPosRange;
	long oldZInPos = m.m_Motor.ArmZ.InPosRange;
	m.m_Motor.ArmZ.InPosRange = _InitialInPosRange;

	//
	if( m.Info.iStatus != theApp.enInitial )
		return;
	// If not Initial. return this function. User want to stop.
	// if fail. It won't not set the error code.

	f.Motor.Servo( &m.m_Motor.ArmX, true );
	f.Motor.Servo( &m.m_Motor.ArmY, true );
	f.Motor.Servo( &m.m_Motor.ArmZ, true );

	while(1)
	{
		// Test Site Up 結束, 可以開始 Arm XY Initial 
		if( m.InitialInterLock.InitialTSUpOK )
			break;
		// 使用者按下 Stop  中止 Initial 
		else if( f.IsPause() )
			break;
		// 程式都關掉了 
		if( !m.Info.bRunning  )
			return;
		else
			; // 等待條件達成	
	}

	// 使用者按下 Stop, 就直接 return
	// If not Initial. return this function. User want to stop.
	if( m.Info.iStatus != theApp.enInitial )
		return;

	m.MotorStatus.ArmY = _T("Initialing, Wait for Arm Z OK.");
	m.MotorStatus.ArmZ = _T("Initialing.");

	// 開真空, 確認 Arm Z 吸嘴上面沒有 IC
	// Check Arm Z have IC or Not, Make sure Arm Z have no IC	
	bool ArmOK = CheckArmZIC( &m.OutSet.ArmVacc , &m.InStatus.ArmZVaccSensor, 
		m.TimerSetting.iArmZCheckTime );

	//
	if( m.Info.iStatus != theApp.enInitial )
		return;

	//
	long iStart = 0;

	////// Initial Process
	// Arm Z
	// 載入飄移速度 , 飄到 sensor 那邊去 
	f.Motor.LoadDriftSpeed( &m.m_Motor.ArmZ );	
	m.MotorStatus.ArmZ = "Move to Lmt.";
	m_iRunError = f.Motor.MotorMovetonNLimt( m.m_Motor.ArmZ, _InitialArmZTimeout );
	// Move to nLmt (1 in)

	if ( IsInitialError( m_iRunError, f.Motor.GetMotorID( &m.m_Motor.ArmZ ) ))
		return;	
	if( m.Info.iStatus != theApp.enInitial )
		return;
	m.MotorStatus.ArmZ = "Move to Lmt OK."; /* 第一次移動到 snesor 結束 */

	// 載入搜索速度, 離開 snesor 
	f.Motor.LoadSearchSpeed( &m.m_Motor.ArmZ );
	m.MotorStatus.ArmZ = "Move off Lmt.";
	m_iRunError = f.Motor.MoveOffnNLimit( &m.m_Motor.ArmZ, _InitialArmZTimeout );
	// Move off nLmt (1 out)
	
	if ( IsInitialError( m_iRunError, f.Motor.GetMotorID( &m.m_Motor.ArmZ ) ))
		return;
	if( m.Info.iStatus != theApp.enInitial )
		return;
	m.MotorStatus.ArmZ = "Move off Lmt OK."; /* 第一次離開 snesor 結束 */
	
	f.Wait( _WaitLmt );
	// Wait for few time.

	// 載入飄移速度 , 飄到 sensor 那邊去 
	f.Motor.LoadDriftSpeed( &m.m_Motor.ArmZ );
	m.MotorStatus.ArmZ = "Move to Lmt.";
	m_iRunError = f.Motor.MotorMovetonNLimt( m.m_Motor.ArmZ, _InitialArmZTimeout );
	// Move to nLmt (2 in)

	if ( IsInitialError( m_iRunError, f.Motor.GetMotorID( &m.m_Motor.ArmZ ) ))
		return;
	if( m.Info.iStatus != theApp.enInitial )
		return;
	m.MotorStatus.ArmZ = "Move to Lmt OK."; /* 第二次移動到 snesor 結束 */
	
	f.Wait( _WaitLmt );
	// Wait for few time.
	
	// 載入搜索速度, 離開 snesor
	f.Motor.LoadSearchSpeed( &m.m_Motor.ArmZ );
	// Load Search Speed for move off nLmt		
	m.MotorStatus.ArmZ = "Move off Lmt.";
	m_iRunError = f.Motor.MoveOffnNLimit( &m.m_Motor.ArmZ, _InitialArmZTimeout );
	// Move off nLmt (2 out)
		
	if ( IsInitialError( m_iRunError, f.Motor.GetMotorID( &m.m_Motor.ArmZ ) ))
			return;
	if( m.Info.iStatus != theApp.enInitial )
			return;
	m.MotorStatus.ArmZ = "Move off Lmt OK."; /* 第二次離開 snesor 結束 */

	f.Wait( _WaitLmt );
	// Wait for few time.

	f.Motor.MotorClearCount( &m.m_Motor.ArmZ );
	// Clear Driver count 
	// Set RCount to 0, Set LCount to Zero
		
	f.Wait( _WaitLmt );
	// Wait for few time.
	
	m_iRunError = f.Motor.MotorRun( &m.m_Motor.ArmZ, ( _InitialZHome * m.m_Ratio.Z_GearRation ), 
			false, m.TimerSetting.iMotorRunTimeout );
	// 離開  _InitialZHome mm 距離, 避免回 Home Overheat

	if ( IsInitialError( m_iRunError, f.Motor.GetMotorID( &m.m_Motor.ArmZ ) ))
		return;
	if( m.Info.iStatus != theApp.enInitial )
		return;

	//
	m.InterLock.InitialArmZEnd = true;
	m.MotorStatus.ArmZInitialed = true;
	m.MotorStatus.ArmZ = _T("Arm Z Initial OK.");

	// 設定 Arm Z OK. 讓 Arm X, 可以開始 Initial
	m.InitialInterLock.InitialArmZUpOK	= true;

	// Arm Y
	m.MotorStatus.ArmY = _T("Initialing.");

	// 載入飄移速度 , 飄到 sensor 那邊去 
	f.Motor.LoadDriftSpeed( &m.m_Motor.ArmY );	
	m.MotorStatus.ArmY = "Move to Lmt.";

	m_iRunError = f.Motor.MotorMovetonNLimt( m.m_Motor.ArmY, _InitialArmYTimeout );
	// Move to nLmt (1 in)	
	if ( IsInitialError( m_iRunError, f.Motor.GetMotorID( &m.m_Motor.ArmY ) ))
		return;
	if( m.Info.iStatus != theApp.enInitial )
		return;	
	m.MotorStatus.ArmY = "Move to Lmt OK.";	/* 第一次移動到 sensor 成功 */

	// 載入搜索速度 , 離開 snesor
	f.Motor.LoadSearchSpeed( &m.m_Motor.ArmY );
	// 清除 Encoder
	f.Wait( _WaitLmt );
	f.Motor.MotorClearCount( &m.m_Motor.ArmY );
	f.Wait( _WaitLmt );

	//
	m.MotorStatus.ArmY = "Search Home.";
	m_iRunError = f.Motor.MotorRunAnyway( &m.m_Motor.ArmY, ( _InitialYHome * m.m_Ratio.Y_GearRation ), false, m.TimerSetting.iMotorRunTimeout );
	if ( IsInitialError( m_iRunError, f.Motor.GetMotorID( &m.m_Motor.ArmY ) ))
		return;
	if( m.Info.iStatus != theApp.enInitial )
		return;
	m.MotorStatus.ArmY = "Search Home OK.";	/* 第一次離開 sensor 成功 */

	//
	f.Wait( _WaitLmt );

	//
	f.Motor.LoadSearchSpeed( &m.m_Motor.ArmY );
	m.MotorStatus.ArmY = "Move to Lmt.";
	m_iRunError = f.Motor.MotorMovetonNLimt( m.m_Motor.ArmY, _InitialArmYTimeout );
	if ( IsInitialError( m_iRunError, f.Motor.GetMotorID( &m.m_Motor.ArmY ) ))
		return;
	if( m.Info.iStatus != theApp.enInitial )
		return;
	m.MotorStatus.ArmY = "Move to Lmt OK.";	/* 第二次移動到 sensor 成功 */

	f.Wait( _WaitLmt );
	// Wait for few time.

	//
	f.Wait( _ClearCountWait );
	f.Motor.MotorClearCount( &m.m_Motor.ArmY );
	f.Wait( _ClearCountWait );

	m.MotorStatus.ArmY = "Search Home.";
	m_iRunError = f.Motor.MotorRunAnyway( &m.m_Motor.ArmY, ( _InitialYHome * m.m_Ratio.Y_GearRation ), false, m.TimerSetting.iMotorRunTimeout );
	if ( IsInitialError( m_iRunError, f.Motor.GetMotorID( &m.m_Motor.ArmY ) ))
		return;	
	if( m.Info.iStatus != theApp.enInitial )
		return;
	m.MotorStatus.ArmY = "Search Home OK."; /* 第二次離開 sensor 成功 */

	f.Wait( _WaitLmt );
	// Wait for few time.

	//
	f.Wait( _ClearCountWait );
	f.Motor.MotorClearCount( &m.m_Motor.ArmY );
	// 離開  _InitialZHome mm 距離, 避免回 Home Overheat

	if ( IsInitialError( m_iRunError, f.Motor.GetMotorID( &m.m_Motor.ArmY ) ))
		return;
	if( m.Info.iStatus != theApp.enInitial )
		return;

	// Arm Y 移動到待命位置 
	
	// 如果一開始開真空, 發現吸嘴上面有 IC, 那麼到 Arm XY 移動到待命位置的時候.
	// 我就必須讓機台發出 Alarm.
	if( !ArmOK )
		m.Err.Arm.Code = enCodeArmZInitialhaveIC;

	f.Wait( _WaitLmt );
	
	if( m.Info.iStatus != theApp.enInitial )
		return;
	// If not Initial. return this function. User want to stop.

	//
	f.Wait(100);
	m.InterLock.InitialArmYEnd = true;
	m.MotorStatus.ArmYInitialed = true;
	m.MotorStatus.ArmY = _T("Arm Y Initial OK.");
	m_bInitialized = true;
	f.CWinMessage( "Arm:Arm X OK", theApp.enDArm );
}
/////////////////////////////////////
// Repeat Tray Function
void CThArm::RepeatTrayYieldRate()
{
	// (1) Input->Output
	//////////////////////////////////////////////////////////////////////////////////////////
	if( f.GetRepeatTrayModeMoation() == theApp.enRepeatTray1ToTray2 )
	{
		if( f.GetNowMoation( m.m_RepeatTrayDATA.m_NowCount ) == theApp.enRepeatTrayMation1 )
		{
			// 到Tray1取料, 放到Tray2
		}
		else if( f.GetNowMoation( m.m_RepeatTrayDATA.m_NowCount ) == theApp.enRepeatTrayMation2 )
		{
			// 到Tray2取料, 放到Tray1
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
		}
		else if( f.GetNowMoation( m.m_RepeatTrayDATA.m_NowCount ) == theApp.enRepeatTrayMation2 )
		{
			// 到Tray1取料, 放到Tray2
		}
		else 
			;	
	}
	// (3) Both, Disable
	//////////////////////////////////////////////////////////////////////////////////////////
	else if( f.GetRepeatTrayModeMoation() == theApp.enRepeatTray1AndDisable )
	{
		// 到Tray1取料, 放到Tray1
		InsertOutputYield( theApp.m_tArm.ArmLog.csCode );
	}
	// (4) Disable, Both
	//////////////////////////////////////////////////////////////////////////////////////////
	else if( f.GetRepeatTrayModeMoation() == theApp.enRepeatDisableAndTray2 )
	{
		// 到Tray2取料, 放到Tray2
		InsertOutputYield( theApp.m_tArm.ArmLog.csCode );
	}	
	// (5) Both, Both
	//////////////////////////////////////////////////////////////////////////////////////////
	else if( f.GetRepeatTrayModeMoation() == theApp.enRepeatTray1AndTray2 )
	{
		CString csMsg = _T("");
		if( m.m_RepeatTrayDATA.m_bRepeatIsTray1 == true )
		{
			// 輪到 Tray 1 被放 (Both)Tray 1
			InsertOutputYield( theApp.m_tArm.ArmLog.csCode );
		}
		else
		{
			// 輪到 Tray 2 被放 (Both)Tray 2
			InsertOutputYield( theApp.m_tArm.ArmLog.csCode );
		}
	}
	// (6) Pass, Fail
	//////////////////////////////////////////////////////////////////////////////////////////
	else if( f.GetRepeatTrayModeMoation() == theApp.enRepeatPass1AndFail2 )
	{

	}
	// (7) Fail, Pass
	//////////////////////////////////////////////////////////////////////////////////////////
	else if( f.GetRepeatTrayModeMoation() == theApp.enRepeatFail1AndPass2 )
	{

	}
	else
	{
	}
}
void CThArm::RepeatTrayMap()
{
	// (1) Input->Output
	//////////////////////////////////////////////////////////////////////////////////////////
	if( f.GetRepeatTrayModeMoation() == theApp.enRepeatTray1ToTray2 )
	{
		if( f.GetNowMoation( m.m_RepeatTrayDATA.m_NowCount ) == theApp.enRepeatTrayMation1 )
		{
			// 到Tray1取料, 放到Tray2
		}
		else if( f.GetNowMoation( m.m_RepeatTrayDATA.m_NowCount ) == theApp.enRepeatTrayMation2 )
		{
			// 到Tray2取料, 放到Tray1
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
		}
		else if( f.GetNowMoation( m.m_RepeatTrayDATA.m_NowCount ) == theApp.enRepeatTrayMation2 )
		{
			// 到Tray1取料, 放到Tray2
		}
		else 
			;	
	}
	// (3) Both, Disable
	//////////////////////////////////////////////////////////////////////////////////////////
	else if( f.GetRepeatTrayModeMoation() == theApp.enRepeatTray1AndDisable )
	{
		// 到Tray1取料, 放到Tray1
		CPoint p = theApp.m_Tray1.GetIndex();
		f.AddTrayMapRepeat( theApp.enBin1, 
			theApp.m_tArm.ArmLog.csCode, p, 0, 0.0 );
		f.SaveTrayMapRepeat();
	}
	// (4) Disable, Both
	//////////////////////////////////////////////////////////////////////////////////////////
	else if( f.GetRepeatTrayModeMoation() == theApp.enRepeatDisableAndTray2 )
	{
		// 到Tray2取料, 放到Tray2
		CPoint p = theApp.m_Tray2.GetIndex();
		f.AddTrayMapRepeat( theApp.enBin2, 
			theApp.m_tArm.ArmLog.csCode, p, 0, 0.0 );
		f.SaveTrayMapRepeat();
	}	
	// (5) Both, Both
	//////////////////////////////////////////////////////////////////////////////////////////
	else if( f.GetRepeatTrayModeMoation() == theApp.enRepeatTray1AndTray2 )
	{
		CString csMsg = _T("");
		if( m.m_RepeatTrayDATA.m_bRepeatIsTray1 == true )
		{
			// 輪到 Tray 1 被放 (Both)Tray 1
			CPoint p = theApp.m_Tray1.GetIndex();
			f.AddTrayMapRepeat( theApp.enBin1, 
				theApp.m_tArm.ArmLog.csCode, p, 0, 0.0 );
			f.SaveTrayMapRepeat();
		}
		else
		{
			// 輪到 Tray 2 被放 (Both)Tray 2
			CPoint p = theApp.m_Tray2.GetIndex();
			f.AddTrayMapRepeat( theApp.enBin2, 
				theApp.m_tArm.ArmLog.csCode, p, 0, 0.0 );
			f.SaveTrayMapRepeat();
		}
	}
	// (6) Pass, Fail
	//////////////////////////////////////////////////////////////////////////////////////////
	else if( f.GetRepeatTrayModeMoation() == theApp.enRepeatPass1AndFail2 )
	{

	}
	// (7) Fail, Pass
	//////////////////////////////////////////////////////////////////////////////////////////
	else if( f.GetRepeatTrayModeMoation() == theApp.enRepeatFail1AndPass2 )
	{

	}
	else
	{
	}
}
void CThArm::RepeatTrayReport()
{

	if( f.GetRepeatTrayModeMoation() == theApp.enRepeatTray1AndDisable )
	{
		f.Report.InsertBinLog( theApp.m_tArm.ArmLog );
		theApp.m_tArm.ClearArmLog();
	}
	else if( f.GetRepeatTrayModeMoation() == theApp.enRepeatDisableAndTray2 )
	{
		f.Report.InsertBinLog( theApp.m_tArm.ArmLog );
		theApp.m_tArm.ClearArmLog();
	}
	else if( f.GetRepeatTrayModeMoation() == theApp.enRepeatTray1AndTray2 )
	{
		f.Report.InsertBinLog( theApp.m_tArm.ArmLog );
		theApp.m_tArm.ClearArmLog();
	}
	else
	{
		f.Report.InsertBinLog( theApp.m_tArm.ArmLog );
		theApp.m_tArm.ClearArmLog();
	}
}
int CThArm::GetTestLogPassFail(tagTestLog ttLog)
{
	int iPF = -1;

	if( ttLog.iPF == 1 )
		iPF = 1;
	else
		iPF = 0;

	return iPF;
}
void CThArm::ResetInputStatus()
{
	theApp.m_InputTray.ChangeTray();
}
long CThArm::RepeatMationOutput()
{
	long m_iRepeatRunError;
	m_iRepeatRunError = enCodeRunOK;

	// (1) Input->Output
	//////////////////////////////////////////////////////////////////////////////////////////
	if( f.GetRepeatTrayModeMoation() == theApp.enRepeatTray1ToTray2 )
	{
		// Tray1->Tray2 (Input->Output)
		if( f.GetNowMoation( m.m_RepeatTrayDATA.m_NowCount ) == theApp.enRepeatTrayMation1 )
		{
			// 到Tray1取料, 放到Tray2
			int iBooking = -1;
			CPoint px;
			iBooking = theApp.m_Tray2.LocationBooking();
			px = theApp.m_Tray2.GetCoordinate( iBooking );
			theApp.m_Tray2.LocationMove();

			theApp.m_tArm.ClearArmLog();
			ArmLog.iBooking = iBooking;

			m_iRepeatRunError = f.Motor.MotorRunLine(
					m.m_Motor.ArmX, px.x + ( m.m_Offset.Output1.x * m.m_Ratio.X_GearRation ),
					m.m_Motor.ArmY, px.y + ( m.m_Offset.Output1.y * m.m_Ratio.Y_GearRation ),
					true, m.TimerSetting.iMotorRunlineTimeout );
		}
		else if( f.GetNowMoation( m.m_RepeatTrayDATA.m_NowCount ) == theApp.enRepeatTrayMation2 )
		{
			// 到Tray2取料, 放到Tray1
			int iBooking = -1;
			CPoint px;
			iBooking = theApp.m_Tray1.LocationBooking();
			px = theApp.m_Tray1.GetCoordinate( iBooking );
			theApp.m_Tray1.LocationMove();

			theApp.m_tArm.ClearArmLog();
			ArmLog.iBooking = iBooking;

			m_iRepeatRunError = f.Motor.MotorRunLine(
					m.m_Motor.ArmX, px.x + ( m.m_Offset.Input.x * m.m_Ratio.X_GearRation ),
					m.m_Motor.ArmY, px.y + ( m.m_Offset.Input.y * m.m_Ratio.Y_GearRation ),
					true, m.TimerSetting.iMotorRunlineTimeout );
		}
		else
			; // Nerver be here
	}
	// (2) Output->Input
	//////////////////////////////////////////////////////////////////////////////////////////
	else if( f.GetRepeatTrayModeMoation() == theApp.enRepeatTray2ToTray1 )
	{
		// Tray2->Tray1 (Output->Input)
		if( f.GetNowMoation( m.m_RepeatTrayDATA.m_NowCount ) == theApp.enRepeatTrayMation1 )
		{
			// 到Tray2取料, 放到Tray1
			int iBooking = -1;
			CPoint px;
			iBooking = theApp.m_Tray1.LocationBooking();
			px = theApp.m_Tray1.GetCoordinate( iBooking );
			theApp.m_Tray1.LocationMove();

			theApp.m_tArm.ClearArmLog();
			ArmLog.iBooking = iBooking;

			m_iRepeatRunError = f.Motor.MotorRunLine(
					m.m_Motor.ArmX, px.x + ( m.m_Offset.Input.x * m.m_Ratio.X_GearRation ),
					m.m_Motor.ArmY, px.y + ( m.m_Offset.Input.y * m.m_Ratio.Y_GearRation ),
					true, m.TimerSetting.iMotorRunlineTimeout );
		}
		else if( f.GetNowMoation( m.m_RepeatTrayDATA.m_NowCount ) == theApp.enRepeatTrayMation2 )
		{
			// 到Tray1取料, 放到Tray2
			int iBooking = -1;
			CPoint px;
			iBooking = theApp.m_Tray2.LocationBooking();
			px = theApp.m_Tray2.GetCoordinate( iBooking );
			theApp.m_Tray2.LocationMove();

			theApp.m_tArm.ClearArmLog();
			ArmLog.iBooking = iBooking;

			m_iRepeatRunError = f.Motor.MotorRunLine(
					m.m_Motor.ArmX, px.x + ( m.m_Offset.Output1.x * m.m_Ratio.X_GearRation ),
					m.m_Motor.ArmY, px.y + ( m.m_Offset.Output1.y * m.m_Ratio.Y_GearRation ),
					true, m.TimerSetting.iMotorRunlineTimeout );
		}
		else
			; // Nerver be here
	}
	// (3) Both, Disable
	//////////////////////////////////////////////////////////////////////////////////////////
	else if( f.GetRepeatTrayModeMoation() == theApp.enRepeatTray1AndDisable )
	{
		CPoint px;
		px = theApp.m_Tray1.GetCoordinate( ArmLog.iBooking );	
		m_iRepeatRunError = f.Motor.MotorRunLine(
			m.m_Motor.ArmX, px.x + ( m.m_Offset.Input.x * m.m_Ratio.X_GearRation ),
			m.m_Motor.ArmY, px.y + ( m.m_Offset.Input.y * m.m_Ratio.Y_GearRation ),
			true, m.TimerSetting.iMotorRunlineTimeout );	
	}
	// (4) Disable, Both
	//////////////////////////////////////////////////////////////////////////////////////////
	else if( f.GetRepeatTrayModeMoation() == theApp.enRepeatDisableAndTray2 )
	{
		CPoint px;
		px = theApp.m_Tray2.GetCoordinate( ArmLog.iBooking );	
		m_iRepeatRunError = f.Motor.MotorRunLine(
			m.m_Motor.ArmX, px.x + ( m.m_Offset.Output1.x * m.m_Ratio.X_GearRation ),
			m.m_Motor.ArmY, px.y + ( m.m_Offset.Output1.y * m.m_Ratio.Y_GearRation ),
			true, m.TimerSetting.iMotorRunlineTimeout );	
	}	
	// (5) Both, Both
	//////////////////////////////////////////////////////////////////////////////////////////
	else if( f.GetRepeatTrayModeMoation() == theApp.enRepeatTray1AndTray2 )
	{
		// 目前是 Tray1, 所以放回 Tray1
		if( m.m_RepeatTrayDATA.m_bRepeatIsTray1 )
		{
			CPoint px;
			px = theApp.m_Tray1.GetCoordinate( ArmLog.iBooking );	
			m_iRepeatRunError = f.Motor.MotorRunLine(
				m.m_Motor.ArmX, px.x + ( m.m_Offset.Input.x * m.m_Ratio.X_GearRation ),
				m.m_Motor.ArmY, px.y + ( m.m_Offset.Input.y * m.m_Ratio.Y_GearRation ),
				true, m.TimerSetting.iMotorRunlineTimeout );
		}
		// 目前是 Tray2, 所以放回 Tray2
		else
		{
			CPoint px;
			px = theApp.m_Tray2.GetCoordinate( ArmLog.iBooking );	
			m_iRepeatRunError = f.Motor.MotorRunLine(
				m.m_Motor.ArmX, px.x + ( m.m_Offset.Output1.x * m.m_Ratio.X_GearRation ),
				m.m_Motor.ArmY, px.y + ( m.m_Offset.Output1.y * m.m_Ratio.Y_GearRation ),
				true, m.TimerSetting.iMotorRunlineTimeout );		
		}
	}
	// (6) Pass->Fail
	//////////////////////////////////////////////////////////////////////////////////////////
	else if( f.GetRepeatTrayModeMoation() == theApp.enRepeatPass1AndFail2 )
	{
		// 現在在 Tray1 取料, Pass 放到 Tray1, Fail 放到 Tray2

		// 如果是 Pass ( Tray1 )
		if( GetTestLogPassFail( ArmLog ) == 1 )
		{			
			if( theApp.m_InputTray.LocationQuery() != CTrayFile::enEOF )
			{
				int iBooking = -1;
				CPoint px;
				iBooking = theApp.m_InputTray.LocationBooking();
				px = theApp.m_InputTray.GetCoordinate( iBooking );
				theApp.m_InputTray.LocationMove();

				m_iRepeatRunError = f.Motor.MotorRunLine(
					m.m_Motor.ArmX, px.x + ( m.m_Offset.Input.x * m.m_Ratio.X_GearRation ),
					m.m_Motor.ArmY, px.y + ( m.m_Offset.Input.y * m.m_Ratio.Y_GearRation ),
					true, m.TimerSetting.iMotorRunlineTimeout );
			}
			else
			{
				// Nerver be here, Because output numbers nerver > input numbers				
			}
		}
		// 如果是 Fail ( Tray2 )
		else
		{
			if( theApp.m_OutputTray.LocationQuery() != CTrayFile::enEOF )
			{
				int iBooking = -1;
				CPoint px;
				iBooking = theApp.m_OutputTray.LocationBooking();
				px = theApp.m_OutputTray.GetCoordinate( iBooking );
				theApp.m_OutputTray.LocationMove();

				m_iRepeatRunError = f.Motor.MotorRunLine(
					m.m_Motor.ArmX, px.x + ( m.m_Offset.Output1.x * m.m_Ratio.X_GearRation ),
					m.m_Motor.ArmY, px.y + ( m.m_Offset.Output1.y * m.m_Ratio.Y_GearRation ),
					true, m.TimerSetting.iMotorRunlineTimeout );
			}
			else
			{
				// Nerver be here, Because output numbers nerver > input numbers
				bRepeatTray2OutputFull = true;
			}
		}
	}
	// (7) Fail<-Pass
	//////////////////////////////////////////////////////////////////////////////////////////
	else if( f.GetRepeatTrayModeMoation() == theApp.enRepeatFail1AndPass2 )
	{
		// 現在在 Tray2 取料, 放到 Tray1

	}
	else
		;

	//
	return m_iRepeatRunError;
}
bool CThArm::GetRepeatTemperatureConfim(tagRepeatTemperData &m_Data, int book)
{
	double dGetSV = _RepeatErrorTemp;
	CString csCommand = _T("");
	CString csManualMsg = _T("");

#ifdef _Demo
	theApp.m_tTester.m_bSeralOpen = true;
#endif

	if( theApp.m_tTester.m_bSeralOpen )
	{
		CString csCmd = _T("");
		CString csBook = _T("");
		CString csSV = _T("");
		CString csSoakTime = _T("");
		CString csStableTime = _T("");
		CString csTolerance = _T("");
		csBook.Format("%d", book);
		csSV.Format("%5.2f", m_Data.m_dSV );
		csSoakTime.Format("%5.2f", m_Data.m_dSoakingTime );
		csStableTime.Format("%5.2f", m_Data.m_dStableTime );
		csTolerance.Format("%5.2f", m_Data.m_dTolerance );

		//
		csBook.TrimLeft(); csBook.TrimRight();
		csSV.TrimLeft(); csSV.TrimRight();
		csSoakTime.TrimLeft(); csSoakTime.TrimRight();
		csStableTime.TrimLeft(); csStableTime.TrimRight();
		csTolerance.TrimLeft(); csTolerance.TrimRight();
		
		//
		csCmd = m.m_InterfaceSetting.m_csCmdHeader + 
//			m.m_RepeatConfimCmd.m_csBook + csBook + "," +
			m.m_RepeatConfimCmd.m_csSV + csSV + "," +
			m.m_RepeatConfimCmd.m_csSoakTime + csSoakTime + "," +
			m.m_RepeatConfimCmd.m_csStableTime + csStableTime + "," +
			m.m_RepeatConfimCmd.m_csTolerance + csTolerance +
			m.m_InterfaceSetting.m_csCmdTailHeader;
		
		theApp.m_tTester.m_Interface.WriteString(csCmd.GetBuffer(0), csCmd.GetLength());
		int iStartTime = ::GetTickCount();
		while(1)	
		{
			char buff[1000] = {0};
			int read;
			read = theApp.m_tTester.m_Interface.GetString(buff);
			if(read > 0)
			{
				for(int i=0; i<read; i++)
					csCommand += buff[i];	// Get value
				
				csManualMsg.Format("Recv: %s", csCommand);
				f.CommLog( csManualMsg );
			}//read
			
			int iStart = csCommand.Find( m.m_InterfaceSetting.m_csCmdHeader );			  // <<
			int iEnd = csCommand.Find(	m.m_InterfaceSetting.m_csCmdTailHeader, iStart);  // >>
			
			if (iStart == -1 || iEnd == -1) 
			{
				// No find.
				csManualMsg.Format("Recv: %s", csCommand);
				f.CommLog( csManualMsg );
			}
			else
			{
				// If find command, start to process it
				int HeaderLength = m.m_InterfaceSetting.m_csCmdHeader.GetLength();
				int TailHeaderLength = m.m_InterfaceSetting.m_csCmdTailHeader.GetLength();
				
				// Get really command
				CString csResult = _T("");
				csResult = csCommand.Mid(iStart + HeaderLength, iEnd - TailHeaderLength);
				
				
				CString csRevCommand = _T("");
				csRevCommand = csResult;
				
				CArray<CString, CString&> m_Cmd;
				m_Cmd.RemoveAll();
				char seps[]   = ",";
				char *token;
				token = strtok( csRevCommand.GetBuffer(0), seps );
				while( token != NULL )
				{
					// Get next token
					CString csValue = _T("");
					csValue.Format("%s", token );
					m_Cmd.Add(csValue);
					token = strtok( NULL, seps );
				}//token
				
				//
				CArray<double, double&> m_CmdValue;
				m_CmdValue.RemoveAll();
				int iSize = m_Cmd.GetSize();
				if( iSize != 4 )
				{
					break;	// break will return false
				}
				for(int i=0;i<iSize;i++)
				{
					CString csCmd = _T("");
					csCmd = m_Cmd.GetAt(i);
					int iFind = csCmd.Find("=", 0);
					int iSubTotal = csCmd.GetLength();
					csCmd = csCmd.Right( iSubTotal - (iFind + 1) );
					double dValue = 0.0;
					dValue = atof(csCmd);
					m_CmdValue.Add(dValue);
				}//cmd

				int iFinalSize = m_CmdValue.GetSize();
				if( iFinalSize != 4 )
				{
					break;	// break will return false
				}
				else
				{
					// ex: <<Book=-1,SV=35.00,SoakTime=30.00,StableTime=35.00,Tolerance= 3.00>>
					tagRepeatTemperData m_RevCmd;
					m_RevCmd.m_dSV = m_CmdValue.GetAt(0);	// sv
					m_RevCmd.m_dSoakingTime = m_CmdValue.GetAt(1);
					m_RevCmd.m_dStableTime = m_CmdValue.GetAt(2);
					m_RevCmd.m_dTolerance = m_CmdValue.GetAt(3);

					if( m_RevCmd.m_dSV < _MinHeaterTemp || m_RevCmd.m_dSV > _MaxHeaterTemp )
					{
						// error range
						break; // break will return false
					}

					// data ok
					m_Data = m_RevCmd;
					return true;
				}
			}//find				
			
			if( ::GetTickCount() - iStart > (m.m_RepeatConfimCmd.m_dTimeout*1000) )
			{
				break; // break will return false.
			}	
			
			if( !m.Info.bRunning )
			{
				break; // program close, break will return false.
			}

		}//while
	}//open
	else
	{
		//open fail
		return false;
	}

	return false;
}
bool CThArm::IsRepeatTrayComplete()
{
	// complete return true
	bool bComplete = false;
	int iRepeatTimesSetting = f.GetRepeatTrayTimes();
	if( iRepeatTimesSetting == 0 )
		bComplete = false;
	else if( iRepeatTimesSetting == m.m_RepeatTrayDATA.m_NowCount )
		bComplete = true;

	return bComplete;
}
void CThArm::RepeatMationOutputDone()
{
	// (1) Input->Output
	//////////////////////////////////////////////////////////////////////////////////////////
	if( f.GetRepeatTrayModeMoation() == theApp.enRepeatTray1ToTray2 )
	{
		// Tray1->Tray2 (Input->Output)
		if( f.GetNowMoation( m.m_RepeatTrayDATA.m_NowCount ) == theApp.enRepeatTrayMation1 )
		{
			// 到Tray1取料, 放到Tray2
			theApp.m_Tray2.LocationDone();
		}
		else if( f.GetNowMoation( m.m_RepeatTrayDATA.m_NowCount ) == theApp.enRepeatTrayMation2 )
		{
			// 到Tray2取料, 放到Tray1
			theApp.m_Tray1.LocationDone();
		}
		else
			; // Nerver be here
	}
	// (2) Output->Input
	//////////////////////////////////////////////////////////////////////////////////////////
	else if( f.GetRepeatTrayModeMoation() == theApp.enRepeatTray2ToTray1 )
	{
		// Tray2->Tray1 (Output->Input)
		if( f.GetNowMoation( m.m_RepeatTrayDATA.m_NowCount ) == theApp.enRepeatTrayMation1 )
		{
			// 到Tray2取料, 放到Tray1
			theApp.m_Tray1.LocationDone();
		}
		else if( f.GetNowMoation( m.m_RepeatTrayDATA.m_NowCount ) == theApp.enRepeatTrayMation2 )
		{
			// 到Tray1取料, 放到Tray2
			theApp.m_Tray2.LocationDone();
		}
		else
			; // Nerver be here	
	}
	// (3) Both, Disable
	//////////////////////////////////////////////////////////////////////////////////////////
	else if( f.GetRepeatTrayModeMoation() == theApp.enRepeatTray1AndDisable )
	{
	
	}
	// (4) Disable, Both
	//////////////////////////////////////////////////////////////////////////////////////////
	else if( f.GetRepeatTrayModeMoation() == theApp.enRepeatDisableAndTray2 )
	{
	
	}	
	// (5) Both, Both
	//////////////////////////////////////////////////////////////////////////////////////////
	else if( f.GetRepeatTrayModeMoation() == theApp.enRepeatTray1AndTray2 )
	{
	
	}
	// (6) Pass->Fail
	//////////////////////////////////////////////////////////////////////////////////////////
	else if( f.GetRepeatTrayModeMoation() == theApp.enRepeatPass1AndFail2 )
	{
		// 如果是 Pass ( Tray1 )
		if( GetTestLogPassFail( ArmLog ) == 1 )
		{
			theApp.m_InputTray.LocationDone();
		}
		// 如果是 Fail ( Tray2 )
		else
		{
			theApp.m_OutputTray.LocationDone();
		}
	}
	// (7) Fail<-Pass
	//////////////////////////////////////////////////////////////////////////////////////////
	else if( f.GetRepeatTrayModeMoation() == theApp.enRepeatFail1AndPass2 )
	{
	
	}
	else
		;
}
CString CThArm::GetCurrentTray()
{
	int iCurrent = -1;
	CString csCurrentTray = _T("");

	//
	// 如果取料是 Tray 1 則顯示 Tray1, iCurrent = 0
	// 如果取料是 Tray 2 則顯示 Tray2, iCurrent = 1

	// (1) Input->Output
	//////////////////////////////////////////////////////////////////////////////////////////
	if( f.GetRepeatTrayModeMoation() == theApp.enRepeatTray1ToTray2 )
	{
		// Tray1->Tray2 (Input->Output)
		if( f.GetNowMoation( m.m_RepeatTrayDATA.m_NowCount ) == theApp.enRepeatTrayMation1 )
		{			
			iCurrent = 0;		// 到Tray1取料, 放到Tray2
		}
		else if( f.GetNowMoation( m.m_RepeatTrayDATA.m_NowCount ) == theApp.enRepeatTrayMation2 )
		{
			iCurrent = 1;		// 到Tray2取料, 放到Tray1
		}
	}
	// (2) Output->Input
	//////////////////////////////////////////////////////////////////////////////////////////
	else if( f.GetRepeatTrayModeMoation() == theApp.enRepeatTray2ToTray1 )
	{
		// Tray2->Tray1 (Output->Input)
		if( f.GetNowMoation( m.m_RepeatTrayDATA.m_NowCount ) == theApp.enRepeatTrayMation1 )
		{
			iCurrent = 0;		// 到Tray1取料, 放到Tray2
		}
		else if( f.GetNowMoation( m.m_RepeatTrayDATA.m_NowCount ) == theApp.enRepeatTrayMation2 )
		{
			iCurrent = 1;		// 到Tray2取料, 放到Tray1
		}
		else
			; // Nerver be here
	}
	// (3) Both, Disable
	//////////////////////////////////////////////////////////////////////////////////////////
	else if( f.GetRepeatTrayModeMoation() == theApp.enRepeatTray1AndDisable )
	{
		// 到Tray1取料, 放到Tray1
		iCurrent = 0;
	}
	// (4) Disable, Both
	//////////////////////////////////////////////////////////////////////////////////////////
	else if( f.GetRepeatTrayModeMoation() == theApp.enRepeatDisableAndTray2 )
	{
		// 到Tray2取料, 放到Tray2
		iCurrent = 1;
	}	
	// (5) Both, Both
	//////////////////////////////////////////////////////////////////////////////////////////
	else if( f.GetRepeatTrayModeMoation() == theApp.enRepeatTray1AndTray2 )
	{
		// 現在在 Tray1
		if( theApp.m_Tray1.LocationQuery() != CTrayFile::enEOF )
		{
			iCurrent = 0;
		}
		// 現在在 Tray2
		else if( theApp.m_Tray2.LocationQuery() != CTrayFile::enEOF )
		{
			iCurrent = 1;
		}
		else
		{

		}
	}
	else
		;

	//
	if( iCurrent == 0 )
		csCurrentTray = _ArmLogICTray1;
	else if( iCurrent == 1 )
		csCurrentTray = _ArmLogICTray2;
	else
		csCurrentTray = "";		

	return csCurrentTray;
}
long CThArm::RepeatMationInput()
{
	long m_iRepeatRunError;
	m_iRepeatRunError = enCodeRunOK;

	// (1) Input->Output
	//////////////////////////////////////////////////////////////////////////////////////////
	if( f.GetRepeatTrayModeMoation() == theApp.enRepeatTray1ToTray2 )
	{
		// Tray1->Tray2 (Input->Output)
		if( f.GetNowMoation( m.m_RepeatTrayDATA.m_NowCount ) == theApp.enRepeatTrayMation1 )
		{
			if( theApp.m_Tray1.LocationQuery() != CTrayFile::enEOF )
			{
				// 到Tray1取料, 放到Tray2
				int iBooking = -1;
				CPoint px;
				iBooking = theApp.m_Tray1.LocationBooking();
				px = theApp.m_Tray1.GetCoordinate( iBooking );
				theApp.m_Tray1.LocationMove();
				
				theApp.m_tArm.ClearArmLog();
				ArmLog.iBooking = iBooking;
				ArmLog.iTray = theApp.enTray1;
				
				m_iRepeatRunError = f.Motor.MotorRunLine(
					m.m_Motor.ArmX, px.x + ( m.m_Offset.Input.x * m.m_Ratio.X_GearRation ),
					m.m_Motor.ArmY, px.y + ( m.m_Offset.Input.y * m.m_Ratio.Y_GearRation ),
					true, m.TimerSetting.iMotorRunlineTimeout );
			}
			else 
			{
				bRepeatInputEmpty = true;
			}
		}
		else if( f.GetNowMoation( m.m_RepeatTrayDATA.m_NowCount ) == theApp.enRepeatTrayMation2 )
		{
			if( theApp.m_Tray2.LocationQuery() != CTrayFile::enEOF )
			{
				// 到Tray2取料, 放到Tray1
				int iBooking = -1;
				CPoint px;
				iBooking = theApp.m_Tray2.LocationBooking();
				px = theApp.m_Tray2.GetCoordinate( iBooking );
				theApp.m_Tray2.LocationMove();
				
				theApp.m_tArm.ClearArmLog();
				ArmLog.iBooking = iBooking;
				ArmLog.iTray = theApp.enTray2;
				
				m_iRepeatRunError = f.Motor.MotorRunLine(
					m.m_Motor.ArmX, px.x + ( m.m_Offset.Output1.x * m.m_Ratio.X_GearRation ),
					m.m_Motor.ArmY, px.y + ( m.m_Offset.Output1.y * m.m_Ratio.Y_GearRation ),
					true, m.TimerSetting.iMotorRunlineTimeout );
			}
			else 
			{
				bRepeatInputEmpty = true;
			}
		}
		else
			; // Nerver be here
	}
	// (2) Output->Input
	//////////////////////////////////////////////////////////////////////////////////////////
	else if( f.GetRepeatTrayModeMoation() == theApp.enRepeatTray2ToTray1 )
	{
		// Tray2->Tray1 (Output->Input)
		if( f.GetNowMoation( m.m_RepeatTrayDATA.m_NowCount ) == theApp.enRepeatTrayMation1 )
		{
			if( theApp.m_Tray2.LocationQuery() != CTrayFile::enEOF )
			{
				// 到Tray1取料, 放到Tray2
				int iBooking = -1;
				CPoint px;
				iBooking = theApp.m_Tray2.LocationBooking();
				px = theApp.m_Tray2.GetCoordinate( iBooking );
				theApp.m_Tray2.LocationMove();
				
				theApp.m_tArm.ClearArmLog();
				ArmLog.iBooking = iBooking;
				ArmLog.iTray = theApp.enTray1;
				
				m_iRepeatRunError = f.Motor.MotorRunLine(
					m.m_Motor.ArmX, px.x + ( m.m_Offset.Output1.x * m.m_Ratio.X_GearRation ),
					m.m_Motor.ArmY, px.y + ( m.m_Offset.Output1.y * m.m_Ratio.Y_GearRation ),
					true, m.TimerSetting.iMotorRunlineTimeout );
			}
			else 
			{
				bRepeatInputEmpty = true;
			}
		}
		else if( f.GetNowMoation( m.m_RepeatTrayDATA.m_NowCount ) == theApp.enRepeatTrayMation2 )
		{
			if( theApp.m_Tray1.LocationQuery() != CTrayFile::enEOF )
			{
				// 到Tray2取料, 放到Tray1
				int iBooking = -1;
				CPoint px;
				iBooking = theApp.m_Tray1.LocationBooking();
				px = theApp.m_Tray1.GetCoordinate( iBooking );
				theApp.m_Tray1.LocationMove();
				
				theApp.m_tArm.ClearArmLog();
				ArmLog.iBooking = iBooking;
				ArmLog.iTray = theApp.enTray2;
				
				m_iRepeatRunError = f.Motor.MotorRunLine(
					m.m_Motor.ArmX, px.x + ( m.m_Offset.Input.x * m.m_Ratio.X_GearRation ),
					m.m_Motor.ArmY, px.y + ( m.m_Offset.Input.y * m.m_Ratio.Y_GearRation ),
					true, m.TimerSetting.iMotorRunlineTimeout );
			}
			else 
			{
				bRepeatInputEmpty = true;
			}
		}
		else
			; // Nerver be here
	}
	// (3) Both, Disable
	//////////////////////////////////////////////////////////////////////////////////////////
	else if( f.GetRepeatTrayModeMoation() == theApp.enRepeatTray1AndDisable )
	{
		if( theApp.m_Tray1.LocationQuery() != CTrayFile::enEOF )
		{
			// 到Tray1取料, 放到Tray1
			int iBooking = -1;
			CPoint px;
			iBooking = theApp.m_Tray1.LocationBooking();
			px = theApp.m_Tray1.GetCoordinate( iBooking );
			theApp.m_Tray1.LocationMove();
			
			theApp.m_tArm.ClearArmLog();
			ArmLog.iBooking = iBooking;
			ArmLog.iTray = theApp.enTray1;
			
			m_iRepeatRunError = f.Motor.MotorRunLine(
				m.m_Motor.ArmX, px.x + ( m.m_Offset.Input.x * m.m_Ratio.X_GearRation ),
				m.m_Motor.ArmY, px.y + ( m.m_Offset.Input.y * m.m_Ratio.Y_GearRation ),
				true, m.TimerSetting.iMotorRunlineTimeout );
		}
		else 
		{
			bRepeatInputEmpty = true;
		}	
	}
	// (4) Disable, Both
	//////////////////////////////////////////////////////////////////////////////////////////
	else if( f.GetRepeatTrayModeMoation() == theApp.enRepeatDisableAndTray2 )
	{
		if( theApp.m_Tray2.LocationQuery() != CTrayFile::enEOF )
		{
			// 到Tray2取料, 放到Tray2
			int iBooking = -1;
			CPoint px;
			iBooking = theApp.m_Tray2.LocationBooking();
			px = theApp.m_Tray2.GetCoordinate( iBooking );
			theApp.m_Tray2.LocationMove();
			
			theApp.m_tArm.ClearArmLog();
			ArmLog.iBooking = iBooking;
			ArmLog.iTray = theApp.enTray2;
			
			m_iRepeatRunError = f.Motor.MotorRunLine(
				m.m_Motor.ArmX, px.x + ( m.m_Offset.Output1.x * m.m_Ratio.X_GearRation ),
				m.m_Motor.ArmY, px.y + ( m.m_Offset.Output1.y * m.m_Ratio.Y_GearRation ),
				true, m.TimerSetting.iMotorRunlineTimeout );
		}
		else 
		{
			bRepeatInputEmpty = true;
		}		
	}	
	// (5) Both, Both
	//////////////////////////////////////////////////////////////////////////////////////////
	else if( f.GetRepeatTrayModeMoation() == theApp.enRepeatTray1AndTray2 )
	{
		// 現在在 Tray1
		if( theApp.m_Tray1.LocationQuery() != CTrayFile::enEOF )
		{
			m.m_RepeatTrayDATA.m_bRepeatIsTray1 = true;
			
			// updata run page information
			m.Page.Run.UpdataRepeatMation();

			//
			int iBooking = -1;
			CPoint px;
			iBooking = theApp.m_Tray1.LocationBooking();
			px = theApp.m_Tray1.GetCoordinate( iBooking );
			theApp.m_Tray1.LocationMove();
			
			theApp.m_tArm.ClearArmLog();
			ArmLog.iBooking = iBooking;
			ArmLog.iTray = theApp.enTray1;
			
			m_iRepeatRunError = f.Motor.MotorRunLine(
				m.m_Motor.ArmX, px.x + ( m.m_Offset.Input.x * m.m_Ratio.X_GearRation ),
				m.m_Motor.ArmY, px.y + ( m.m_Offset.Input.y * m.m_Ratio.Y_GearRation ),
				true, m.TimerSetting.iMotorRunlineTimeout );		
		}
		// 現在在 Tray2
		else if( theApp.m_Tray2.LocationQuery() != CTrayFile::enEOF )
		{
			m.m_RepeatTrayDATA.m_bRepeatIsTray1 = false;

			// updata run page information
			m.Page.Run.UpdataRepeatMation();
			
			//
			int iBooking = -1;
			CPoint px;
			iBooking = theApp.m_Tray2.LocationBooking();
			px = theApp.m_Tray2.GetCoordinate( iBooking );
			theApp.m_Tray2.LocationMove();
			
			theApp.m_tArm.ClearArmLog();
			ArmLog.iBooking = iBooking;
			ArmLog.iTray = theApp.enTray2;
			
			m_iRepeatRunError = f.Motor.MotorRunLine(
				m.m_Motor.ArmX, px.x + ( m.m_Offset.Output1.x * m.m_Ratio.X_GearRation ),
				m.m_Motor.ArmY, px.y + ( m.m_Offset.Output1.y * m.m_Ratio.Y_GearRation ),
				true, m.TimerSetting.iMotorRunlineTimeout );
		}
		else
		{
			m.m_RepeatTrayDATA.m_bRepeatIsTray1 = true;			
			// updata run page information
			m.Page.Run.UpdataRepeatMation();

			// Tray1, Tray2 都沒有IC, 準備換回 Tray1
			bRepeatInputEmpty = true;
		}
	}
	// (6) Pass->Fail
	//////////////////////////////////////////////////////////////////////////////////////////
	else if( f.GetRepeatTrayModeMoation() == theApp.enRepeatPass1AndFail2 )
	{
		// 現在在 Tray1
		if( theApp.m_Tray1.LocationQuery() != CTrayFile::enEOF )
		{
			// 到Tray1取料, 放到Tray2 (Tray1 是Pass, Tray2 是Fail)
			int iBooking = -1;
			CPoint px;
			iBooking = theApp.m_Tray1.LocationBooking();
			px = theApp.m_Tray1.GetCoordinate( iBooking );
			theApp.m_Tray1.LocationMove();
			
			theApp.m_tArm.ClearArmLog();
			ArmLog.iBooking = iBooking;
			ArmLog.iTray = theApp.enTray1;
			
			m_iRepeatRunError = f.Motor.MotorRunLine(
				m.m_Motor.ArmX, px.x + ( m.m_Offset.Input.x * m.m_Ratio.X_GearRation ),
				m.m_Motor.ArmY, px.y + ( m.m_Offset.Input.y * m.m_Ratio.Y_GearRation ),
				true, m.TimerSetting.iMotorRunlineTimeout );
		}
		else 
		{
			bRepeatInputEmpty = true;
		}
	}
	// (7) Fail<-Pass
	//////////////////////////////////////////////////////////////////////////////////////////
	else if( f.GetRepeatTrayModeMoation() == theApp.enRepeatFail1AndPass2 )
	{
		// 現在在 Tray2
		if( theApp.m_Tray2.LocationQuery() != CTrayFile::enEOF )
		{
			// 到Tray2取料, 放到Tray1
			int iBooking = -1;
			CPoint px;
			iBooking = theApp.m_Tray2.LocationBooking();
			px = theApp.m_Tray2.GetCoordinate( iBooking );
			theApp.m_Tray2.LocationMove();
			
			theApp.m_tArm.ClearArmLog();
			ArmLog.iBooking = iBooking;
			ArmLog.iTray = theApp.enTray2;
			
			m_iRepeatRunError = f.Motor.MotorRunLine(
				m.m_Motor.ArmX, px.x + ( m.m_Offset.Output1.x * m.m_Ratio.X_GearRation ),
				m.m_Motor.ArmY, px.y + ( m.m_Offset.Output1.y * m.m_Ratio.Y_GearRation ),
				true, m.TimerSetting.iMotorRunlineTimeout );
		}
		else 
		{
			bRepeatInputEmpty = true;
		}
	}
	else
		;

	//
	return m_iRepeatRunError;
}
void CThArm::RepeatMationInputDone()
{
	// (1) Input->Output
	//////////////////////////////////////////////////////////////////////////////////////////
	if( f.GetRepeatTrayModeMoation() == theApp.enRepeatTray1ToTray2 )
	{
		// Tray1->Tray2 (Input->Output)
		if( f.GetNowMoation( m.m_RepeatTrayDATA.m_NowCount ) == theApp.enRepeatTrayMation1 )
		{
			// 到Tray1取料, 放到Tray2
			theApp.m_Tray1.LocationDone();
		}
		else if( f.GetNowMoation( m.m_RepeatTrayDATA.m_NowCount ) == theApp.enRepeatTrayMation2 )
		{
			// 到Tray2取料, 放到Tray1
			theApp.m_Tray2.LocationDone();
		}
		else
			; // Nerver be here
	}
	// (2) Output->Input
	//////////////////////////////////////////////////////////////////////////////////////////
	else if( f.GetRepeatTrayModeMoation() == theApp.enRepeatTray2ToTray1 )
	{
		// Tray2->Tray1 (Output->Input)
		if( f.GetNowMoation( m.m_RepeatTrayDATA.m_NowCount ) == theApp.enRepeatTrayMation1 )
		{
			// 到Tray2取料, 放到Tray1
			theApp.m_Tray2.LocationDone();
		}
		else if( f.GetNowMoation( m.m_RepeatTrayDATA.m_NowCount ) == theApp.enRepeatTrayMation2 )
		{
			// 到Tray1取料, 放到Tray2
			theApp.m_Tray1.LocationDone();
		}
		else
			; // Nerver be here
	}
	// (3) Both, Disable
	//////////////////////////////////////////////////////////////////////////////////////////
	else if( f.GetRepeatTrayModeMoation() == theApp.enRepeatTray1AndDisable )
	{
		// 到Tray1取料, 放到Tray1
		theApp.m_Tray1.LocationDone();	
	}
	// (4) Disable, Both
	//////////////////////////////////////////////////////////////////////////////////////////
	else if( f.GetRepeatTrayModeMoation() == theApp.enRepeatDisableAndTray2 )
	{
		// 到Tray2取料, 放到Tray2
		theApp.m_Tray2.LocationDone();	
	}	
	// (5) Both, Both
	//////////////////////////////////////////////////////////////////////////////////////////
	else if( f.GetRepeatTrayModeMoation() == theApp.enRepeatTray1AndTray2 )
	{
		if( m.m_RepeatTrayDATA.m_bRepeatIsTray1 )
			theApp.m_Tray1.LocationDone();
		else
			theApp.m_Tray2.LocationDone();	
	}
	// (6) Pass->Fail
	//////////////////////////////////////////////////////////////////////////////////////////
	else if( f.GetRepeatTrayModeMoation() == theApp.enRepeatPass1AndFail2 )
	{
		theApp.m_Tray1.LocationDone();
	}
	// (7) Fail<-Pass
	//////////////////////////////////////////////////////////////////////////////////////////
	else if( f.GetRepeatTrayModeMoation() == theApp.enRepeatFail1AndPass2 )
	{
		theApp.m_Tray2.LocationDone();
	}
	else
		;
}
long CThArm::RepeatMationInputZDown()
{
	long m_iRepeatRunError;
	m_iRepeatRunError = enCodeRunOK;

	// (1) Input->Output
	//////////////////////////////////////////////////////////////////////////////////////////
	if( f.GetRepeatTrayModeMoation() == theApp.enRepeatTray1ToTray2 )
	{
		// Tray1->Tray2 (Input->Output)
		if( f.GetNowMoation( m.m_RepeatTrayDATA.m_NowCount ) == theApp.enRepeatTrayMation1 )
		{
			// 到Tray1取料, 放到Tray2
			m_iRepeatRunError = f.Motor.MotorRun(&m.m_Motor.ArmZ, 
				m.m_Align.Input.z + ( m.m_Offset.Input.z * m.m_Ratio.Z_GearRation ), false, m.TimerSetting.iMotorRunTimeout );
		}
		else if( f.GetNowMoation( m.m_RepeatTrayDATA.m_NowCount ) == theApp.enRepeatTrayMation2 )
		{
			// 到Tray2取料, 放到Tray1
			m_iRepeatRunError = f.Motor.MotorRun(&m.m_Motor.ArmZ, 
				m.m_Align.Output1.z + ( m.m_Offset.Output1.z * m.m_Ratio.Z_GearRation ), false, m.TimerSetting.iMotorRunTimeout );
		}
		else
			; // Nerver
	}
	// (2) Output->Input
	//////////////////////////////////////////////////////////////////////////////////////////
	else if( f.GetRepeatTrayModeMoation() == theApp.enRepeatTray2ToTray1 )
	{
		// Tray2->Tray1 (Output->Input)
		if( f.GetNowMoation( m.m_RepeatTrayDATA.m_NowCount ) == theApp.enRepeatTrayMation1 )
		{
			// 到Tray2取料, 放到Tray1
			m_iRepeatRunError = f.Motor.MotorRun(&m.m_Motor.ArmZ, 
				m.m_Align.Output1.z + ( m.m_Offset.Output1.z * m.m_Ratio.Z_GearRation ), false, m.TimerSetting.iMotorRunTimeout );
		}
		else if( f.GetNowMoation( m.m_RepeatTrayDATA.m_NowCount ) == theApp.enRepeatTrayMation2 )
		{
			// 到Tray1取料, 放到Tray2
			m_iRepeatRunError = f.Motor.MotorRun(&m.m_Motor.ArmZ, 
				m.m_Align.Input.z + ( m.m_Offset.Input.z * m.m_Ratio.Z_GearRation ), false, m.TimerSetting.iMotorRunTimeout );
		}
		else
			; // Nerver be here
	}
	// (3) Both, Disable
	//////////////////////////////////////////////////////////////////////////////////////////
	else if( f.GetRepeatTrayModeMoation() == theApp.enRepeatTray1AndDisable )
	{
		m_iRepeatRunError = f.Motor.MotorRun(&m.m_Motor.ArmZ, 
			m.m_Align.Input.z + ( m.m_Offset.Input.z * m.m_Ratio.Z_GearRation ), false, m.TimerSetting.iMotorRunTimeout );
	}
	// (4) Disable, Both
	//////////////////////////////////////////////////////////////////////////////////////////
	else if( f.GetRepeatTrayModeMoation() == theApp.enRepeatDisableAndTray2 )
	{
		m_iRepeatRunError = f.Motor.MotorRun(&m.m_Motor.ArmZ, 
			m.m_Align.Output1.z + ( m.m_Offset.Output1.z * m.m_Ratio.Z_GearRation ), false, m.TimerSetting.iMotorRunTimeout );
	}	
	// (5) Both, Both
	//////////////////////////////////////////////////////////////////////////////////////////
	else if( f.GetRepeatTrayModeMoation() == theApp.enRepeatTray1AndTray2 )
	{
		if( m.m_RepeatTrayDATA.m_bRepeatIsTray1 )
		{
			// Tray1 Z Down
			m_iRepeatRunError = f.Motor.MotorRun(&m.m_Motor.ArmZ, 
				m.m_Align.Input.z + ( m.m_Offset.Input.z * m.m_Ratio.Z_GearRation ), false, m.TimerSetting.iMotorRunTimeout );
		}
		else 
		{
			// Tray2 Z Down
			m_iRepeatRunError = f.Motor.MotorRun(&m.m_Motor.ArmZ, 
				m.m_Align.Output1.z + ( m.m_Offset.Output1.z * m.m_Ratio.Z_GearRation ), false, m.TimerSetting.iMotorRunTimeout );
		}
	}
	// (6) Pass->Fail
	//////////////////////////////////////////////////////////////////////////////////////////
	else if( f.GetRepeatTrayModeMoation() == theApp.enRepeatPass1AndFail2 )
	{
		// Tray1 Z Down
		m_iRepeatRunError = f.Motor.MotorRun(&m.m_Motor.ArmZ, 
			m.m_Align.Input.z + ( m.m_Offset.Input.z * m.m_Ratio.Z_GearRation ), false, m.TimerSetting.iMotorRunTimeout );
	}
	// (7) Fail<-Pass
	//////////////////////////////////////////////////////////////////////////////////////////
	else if( f.GetRepeatTrayModeMoation() == theApp.enRepeatFail1AndPass2 )
	{
		// Tray2 Z Down
		m_iRepeatRunError = f.Motor.MotorRun(&m.m_Motor.ArmZ, 
			m.m_Align.Output1.z + ( m.m_Offset.Output1.z * m.m_Ratio.Z_GearRation ), false, m.TimerSetting.iMotorRunTimeout );
	}
	else
	{
	
	}

	return m_iRepeatRunError;
}
long CThArm::RepeatMationOutputZDown()
{
	long m_iRepeatRunError;
	m_iRepeatRunError = enCodeRunOK;

	// (1) Input->Output
	//////////////////////////////////////////////////////////////////////////////////////////
	if( f.GetRepeatTrayModeMoation() == theApp.enRepeatTray1ToTray2 )
	{
		// Tray1->Tray2 (Input->Output)
		if( f.GetNowMoation( m.m_RepeatTrayDATA.m_NowCount ) == theApp.enRepeatTrayMation1 )
		{
			// 到Tray1取料, 放到Tray2
			m_iRepeatRunError = f.Motor.MotorRun(&m.m_Motor.ArmZ, 
				m.m_Align.Output1.z + ( m.m_Offset.Output1.z2 * m.m_Ratio.Z_GearRation ), false, m.TimerSetting.iMotorRunTimeout );
		}
		else if( f.GetNowMoation( m.m_RepeatTrayDATA.m_NowCount ) == theApp.enRepeatTrayMation2 )
		{
			// 到Tray2取料, 放到Tray1
			m_iRepeatRunError = f.Motor.MotorRun(&m.m_Motor.ArmZ, 
				m.m_Align.Input.z + ( m.m_Offset.Input.z2 * m.m_Ratio.Z_GearRation ), false, m.TimerSetting.iMotorRunTimeout );
		}
		else
			; // Nerver be here
	}
	// (2) Output->Input
	//////////////////////////////////////////////////////////////////////////////////////////
	else if( f.GetRepeatTrayModeMoation() == theApp.enRepeatTray2ToTray1 )
	{
		// Tray2->Tray1 (Output->Input)
		if( f.GetNowMoation( m.m_RepeatTrayDATA.m_NowCount ) == theApp.enRepeatTrayMation1 )
		{
			// 到Tray2取料, 放到Tray1
			m_iRepeatRunError = f.Motor.MotorRun(&m.m_Motor.ArmZ, 
				m.m_Align.Input.z + ( m.m_Offset.Input.z2 * m.m_Ratio.Z_GearRation ), false, m.TimerSetting.iMotorRunTimeout );
		}
		else if( f.GetNowMoation( m.m_RepeatTrayDATA.m_NowCount ) == theApp.enRepeatTrayMation2 )
		{
			// 到Tray1取料, 放到Tray2
			m_iRepeatRunError = f.Motor.MotorRun(&m.m_Motor.ArmZ, 
				m.m_Align.Output1.z + ( m.m_Offset.Output1.z2 * m.m_Ratio.Z_GearRation ), false, m.TimerSetting.iMotorRunTimeout );
		}
		else
			; // Nerver be here	
	}
	// (3) Both, Disable
	//////////////////////////////////////////////////////////////////////////////////////////
	else if( f.GetRepeatTrayModeMoation() == theApp.enRepeatTray1AndDisable )
	{
		m_iRepeatRunError = f.Motor.MotorRun(&m.m_Motor.ArmZ, 
			m.m_Align.Input.z + ( m.m_Offset.Input.z2 * m.m_Ratio.Z_GearRation ), false, m.TimerSetting.iMotorRunTimeout );
	}
	// (4) Disable, Both
	//////////////////////////////////////////////////////////////////////////////////////////
	else if( f.GetRepeatTrayModeMoation() == theApp.enRepeatDisableAndTray2 )
	{
		m_iRepeatRunError = f.Motor.MotorRun(&m.m_Motor.ArmZ, 
			m.m_Align.Output1.z + ( m.m_Offset.Output1.z2 * m.m_Ratio.Z_GearRation ), false, m.TimerSetting.iMotorRunTimeout );
	}	
	// (5) Both, Both
	//////////////////////////////////////////////////////////////////////////////////////////
	else if( f.GetRepeatTrayModeMoation() == theApp.enRepeatTray1AndTray2 )
	{
		// 目前是 Tray1
		if( m.m_RepeatTrayDATA.m_bRepeatIsTray1 )
		{
			m_iRepeatRunError = f.Motor.MotorRun(&m.m_Motor.ArmZ, 
				m.m_Align.Input.z + ( m.m_Offset.Input.z2 * m.m_Ratio.Z_GearRation ), false, m.TimerSetting.iMotorRunTimeout );
		}
		// 目前是 Tray2
		else
		{
			m_iRepeatRunError = f.Motor.MotorRun(&m.m_Motor.ArmZ, 
				m.m_Align.Output1.z + ( m.m_Offset.Output1.z2 * m.m_Ratio.Z_GearRation ), false, m.TimerSetting.iMotorRunTimeout );
		}
	}
	// (6) Pass->Fail
	//////////////////////////////////////////////////////////////////////////////////////////
	else if( f.GetRepeatTrayModeMoation() == theApp.enRepeatPass1AndFail2 )
	{
		// 如果是 Pass ( Tray1 )
		if( GetTestLogPassFail( ArmLog ) == 1 )
		{
			m_iRepeatRunError = f.Motor.MotorRun(&m.m_Motor.ArmZ, 
				m.m_Align.Input.z + ( m.m_Offset.Input.z2 * m.m_Ratio.Z_GearRation ), false, m.TimerSetting.iMotorRunTimeout );
		}
		// 如果是 Fail ( Tray2 )
		else
		{
			m_iRepeatRunError = f.Motor.MotorRun(&m.m_Motor.ArmZ, 
				m.m_Align.Output1.z + ( m.m_Offset.Output1.z2 * m.m_Ratio.Z_GearRation ), false, m.TimerSetting.iMotorRunTimeout );	
		}	
	}
	// (7) Fail<-Pass
	//////////////////////////////////////////////////////////////////////////////////////////
	else if( f.GetRepeatTrayModeMoation() == theApp.enRepeatFail1AndPass2 )
	{
	
	}
	else
		;

	return m_iRepeatRunError;
}
/////////////////////////////////////
void CThArm::InitAutoRetry()
{
	m_lArmRetryCounter = 0;
}
bool CThArm::IsInitialError(long err, long id)
{
	if(err != enCodeRunOK)
	{
		f.Motor.MotorStop( &m.m_Motor.ArmX  );
		f.Motor.MotorStop( &m.m_Motor.ArmY  );
		f.Motor.MotorStop( &m.m_Motor.ArmZ  );

		// stop all motor 
		m_bStatus = enIdle;
		m.MotorStatus.ArmX = "Cancel.";
		m.MotorStatus.ArmY = "Cancel.";
		m.MotorStatus.ArmZ = "Cancel.";
		m.Err.Arm.Code = err;
		// Set error 

		return true;
	}
	return false;
}
bool CThArm::CheckDoubleArmZCheckVacc()
{
	bool bOK = false;
#ifdef _Demo
	bOK = true;
#else

	if( m.InStatus.ArmZVaccSensor == _ArmZVaccOn )
		bOK = true;
	else
		bOK = false;
#endif

	return bOK;
}
bool CThArm::CheckArmZVaccSensor()
{
	bool bOK = false;

#ifdef _Demo
	bOK = true;
#else

	if( m.InStatus.ArmZVaccSensor == _ArmZVaccOn )
		bOK = true;
	else
		bOK = false;
#endif

	return bOK;
}
bool CThArm::ManualVacc(unsigned char* Vacc, unsigned char* pSensor, double dTimeout )
{
	// Note : This function for Pick IC.
	// 1: Turn on the Vacc
	// 2: Wait for Vacc sensor On
	// 3: check Timeout.
	// 4: Pick success. Move to next ststus.
	// 5: check sensor again when Arm Z up.

	int	iStart;

	*Vacc = 1;		// Turn on vacuum.
	iStart = ::GetTickCount();
	while (1)
	{
		if ( (::GetTickCount() - iStart ) >= dTimeout * 1000 )
		{
			// Error - stop vacuum.
			*Vacc = 0;	
			return false;
		}

		// Check the vacuum sensor.
		if (*pSensor == _ArmZVaccOn)
		{
			// Do a debounce on the sensor.
			Sleep(10);
			if (*pSensor == _ArmZVaccOn)
				break;
			// check 2 times.
		}

		if(!m.Info.bRunning)
			return false;

		Sleep(_Wait);
	}

	// Check it one more time.
	if (*pSensor == _ArmZVaccOn)
		return true;

	// Something wrong - turn it off.
	*Vacc = 0;
	return false;
}
// 1.0Ac
void CThArm::ClearHeaterStable()
{
	m.m_heaterCtrl.m_lHeaterStart = 0;
	m.m_heaterCtrl.m_bHeaterTempOK = false;
	m.m_heaterCtrl.m_bHeaterIsStable = false;
}
bool CThArm::WaitHeaterStableOK()
{
	bool bHeaterStable = false;

	while(1)
	{
		double dSpendTime = 0.0;
		if( f.HeaterIsStable(dSpendTime) )
		{			
			bHeaterStable = true;
			m.m_heaterCtrl.m_lHeaterStart = 0;
			break;
		}
		else if( f.IsPause() )
		{
			bHeaterStable = false;
			break;
		}
		else if( !m.Info.bRunning )
		{
			bHeaterStable = false;
			break;
		}	
		Sleep(1);
	}

	return bHeaterStable;
}
bool CThArm::WaitHeaterOK()
{
	bool bHeaterOK = false;
	m.RemoteOutSet.HeaterOn = true;

	// 
	double dSetSV = m.m_West.dSetPoint;
	double dTolerance = m.m_West.dTolerance;
	double dStableTime = m.m_West.dStableTime;
	double dSoaking	= m.m_West.dSoakTime;
	// 1.0Ac
	// Repeat Tray Temperature
	if( m.m_RepeatTrayCtrl.m_iRepeatTrayMode == theApp.enRepeatTrayInOutCtrl )
	{
		int iSize = m.m_RepeatTrayTemperData.GetSize();
		if( iSize > m.m_RepeatTrayDATA.m_NowCount )
		{
			dSetSV = m.m_RepeatTrayTemperData.GetAt( m.m_RepeatTrayDATA.m_NowCount ).m_dSV;
			dTolerance = m.m_RepeatTrayTemperData.GetAt( m.m_RepeatTrayDATA.m_NowCount ).m_dTolerance;
			dSoaking = m.m_RepeatTrayTemperData.GetAt( m.m_RepeatTrayDATA.m_NowCount ).m_dSoakingTime;
			dStableTime = m.m_RepeatTrayTemperData.GetAt( m.m_RepeatTrayDATA.m_NowCount ).m_dStableTime;
			CString csWestMsg = _T("");
			csWestMsg.Format("Count = %d, SV = %5.2f, Tolerance = %5.2f", m.m_RepeatTrayDATA.m_NowCount, dSetSV, dTolerance );
			f.CWinMessage( csWestMsg, theApp.enDArm );
		}

		// If user want to control from communication
		if( m.m_RepeatInOutCtrl.m_iRepeatConfimFromComm == 1 )
		{
			double m_dCommGetSV = _RepeatErrorTemp;
			tagRepeatTemperData m_Data;
			m_Data.m_dSV = dSetSV;
			m_Data.m_dTolerance = dTolerance;
			m_Data.m_dSoakingTime = dSoaking;
			m_Data.m_dStableTime = dStableTime;
			if( GetRepeatTemperatureConfim(m_Data, ArmLog.iBooking ) )
			{
				// data ok
				dSetSV		= m_Data.m_dSV;
				dTolerance	= m_Data.m_dTolerance;
				dStableTime = m_Data.m_dStableTime;
				dSoaking	= m_Data.m_dSoakingTime;
			}

			// If get temperature success. reset temperature
			if( m_dCommGetSV != _RepeatErrorTemp )
				dSetSV = m_dCommGetSV;
		}
	}

#ifdef _Demo
	f.Wait( 5000 );
	bHeaterOK = true;
#else
	
	double dSV[_MaxWestDevice];
	double dPV[_MaxWestDevice];
	int m_iID = m.m_HandlerComPort.iPortWestHeaterID;
	// set sv
	m.m_DriveWest.AddCmd( m_iID, enSV, dSetSV );
	// set offset
	CString csSV = _T("");
	csSV.Format("%5.2f", dSetSV );
	CString csGetProt = _T("");
	csGetProt.Format("Test Site");
	double dOffset = 0.0;
	f.GetWestLoopupTableTemperature( csSV, csGetProt, dOffset );
	m.m_DriveWest.AddCmd( m_iID, enOffset, dOffset );
	//

	Sleep(350);
	int m_iValueID = m_iID;
	while(1)
	{				
		m.m_DriveWest.GetValue( dPV, dSV );

		bool bSetSVOK = false;
		if( dSV[m_iValueID] == dSetSV )
			bSetSVOK = true;

		double m_dRange = (dSV[m_iValueID] - dPV[m_iValueID]);
		double m_dRangeAbs = fabs( m_dRange );
		if( m_dRangeAbs <= dTolerance && bSetSVOK )
		{
			CString csWestMsg = _T("");
			csWestMsg.Format("SV: %5.2f, PV: %5.2f, Range: %5.2f", dSV[m_iValueID], dPV[m_iValueID], m_dRangeAbs );
			f.CWinMessage( csWestMsg, theApp.enDArm );
			bHeaterOK = true;
			break;
		}
		else if( f.IsPause() )
		{
			bHeaterOK = false;
			break;
		}
		else if( !m.Info.bRunning )
		{
			bHeaterOK = false;
			break;
		}
		Sleep(1);
	}
#endif
	return bHeaterOK;
}
/*
bool CThArm::WaitHeaterOK()
{
	bool bHeaterOK = false;
	m.RemoteOutSet.HeaterOn = true;

#ifdef _Demo
	f.Wait( 5000 );
	bHeaterOK = true;
#else
	
	double dSV[_MaxWestDevice];
	double dPV[_MaxWestDevice];
	double dSetSV = m.m_West.dSetPoint;
	int m_iID = m.m_HandlerComPort.iPortWestHeaterID;
	// set sv
	m.m_DriveWest.AddCmd( m_iID, enSV, dSetSV );
	// set offset
	CString csSV = _T("");
	csSV.Format("%5.2f", dSetSV );
	CString csGetProt = _T("");
	csGetProt.Format("Test Site");
	double dOffset = 0.0;
	f.GetWestLoopupTableTemperature( csSV, csGetProt, dOffset );
	m.m_DriveWest.AddCmd( m_iID, enOffset, dOffset );
	//

	Sleep(150);
	int m_iValueID = m_iID;
	while(1)
	{				
		m.m_DriveWest.GetValue( dPV, dSV );
		double m_dRange = (dSV[m_iValueID] - dPV[m_iValueID]);
		double m_dRangeAbs = fabs( m_dRange );
		if( m_dRangeAbs <= m.m_West.dTolerance )
		{
			bHeaterOK = true;
			break;
		}
		else if( f.IsPause() )
		{
			bHeaterOK = false;
			break;
		}
		else if( !m.Info.bRunning )
		{
			bHeaterOK = false;
			break;
		}
		Sleep(1);
	}
#endif
	return bHeaterOK;
}
*/
bool CThArm::TSRemainICVaccOff(unsigned char* Vacc )
{
	*Vacc = 0;		// Turn on vacuum.
	return true;
}
bool CThArm::TSRemainICDoubleCheck(unsigned char* pSensor )
{
#ifdef _Demo
	return false;
#endif

	if( pSensor == _TSVacOn )
		return true;
	else
		return false;
}
bool CThArm::TSRemainICVacc(unsigned char* Vacc, unsigned char* pSensor, double dTimeout )
{
	// Note : This function for TS Remain IC Check.
	// 1: Turn on the Vacc
	// 2: Wait for Vacc sensor On
	// 3: check Timeout.
	// 4: if true. Oh.Socket IC Exist.We need to Alarm.
	// 5: check sensor again when TS up.
#ifdef _Demo
	return false;
#endif

	int	iStart;

	*Vacc = 1;		// Turn on vacuum.
	iStart = ::GetTickCount();
	while (1)
	{
		if ( (::GetTickCount() - iStart ) >= dTimeout * 1000 )
		{
			// Error - stop vacuum.
			if( m.m_TSRemainICParameter.iTSRemainICAlwaysOn == 0 )
				*Vacc = 0;	
			return false;
		}

		if(f.IsPause())
			return false;
		// if System Pause. Do not turn off

		if(!m.Info.bRunning)
			return false;

		Sleep(_Wait);
	}

	// Something wrong - turn it off.
	if( m.m_TSRemainICParameter.iTSRemainICAlwaysOn == 0 )
		*Vacc = 0;

	return false;
}
bool CThArm::Vacc(unsigned char* Vacc, unsigned char* pSensor, double dTimeout )
{
	// Note : This function for Pick IC.
	// 1: Turn on the Vacc
	// 2: Wait for Vacc sensor On
	// 3: check Timeout.
	// 4: Pick success. Move to next ststus.
	// 5: check sensor again when Arm Z up.

	int	iStart;

	*Vacc = 1;		// Turn on vacuum.
	iStart = ::GetTickCount();
	while (1)
	{
		if ( (::GetTickCount() - iStart ) >= dTimeout * 1000 )
		{
			// Error - stop vacuum.
			*Vacc = 0;	
			return false;
		}

		// Check the vacuum sensor.
		if (*pSensor == _ArmZVaccOn)
		{
			// Do a debounce on the sensor.
			Sleep(10);
			if (*pSensor == _ArmZVaccOn)
				break;
			// check 2 times.
		}

		if(f.IsPause())
			return false;
		// if System Pause. Do not turn off

		if(!m.Info.bRunning)
			return false;

		Sleep(_Wait);
	}

	// Check it one more time.
	if (*pSensor == _ArmZVaccOn)
		return true;

	// Something wrong - turn it off.
	*Vacc = 0;
	return false;
}
bool CThArm::Blow(unsigned char* Vacc, unsigned char* Puff, unsigned char* pSensor, double dTimeout )
{
	// Note : This function for Puff IC.
	// 1: Turn on the Puff
	// 2: wait for Puff sensor On
	// 3: check Timeout 
	// 4: Place success. Move to next status.
	// 5: check sensor again when Arm Z up

	int iStart = ::GetTickCount();

	*Vacc = 0;	// Vacuum off
	*Puff = 1;		// Puff on

	while (1)
	{
		if ( (::GetTickCount() - iStart) >= (dTimeout * 1000.) )
			break;

		if(f.IsPause())
		{
			 *Puff = 0;
			 return true;
		}

		if(!m.Info.bRunning)
			return false;
		
		Sleep(_Wait);
	}

	if(*pSensor)
	{
		*Puff = 0;
		return false;
	}
	// Before return this function. 
	// We check Arm Z have IC or Not.
	// If there have IC, Puff fail

    // Turn puff off.    
    *Puff = 0;
	return true;
}

// Rotator
bool CThArm::RotatorN(unsigned char* Turn,	unsigned char* pSensor, unsigned char* nSensor, double dTimeout)
{
#ifdef _Demo
	return true;
#endif 

	// -90
	// 1. Set Output 
	// 2. Set Timer
	// 3. Check lmt OK
	// 4. return

	int iStart = ::GetTickCount();
	*Turn = 0;	// set to false, to find P lmt

	while (1)
	{
		if ( (::GetTickCount() - iStart) >= (dTimeout) )
			return false;	// Timeout
		else if( *pSensor == 0 && *nSensor == 1 )
			return true;	// InPos	// Make in nlmt and leave plmt
		else if( f.IsPause() )
			return false;

		Sleep(_Wait);
	}

	return false;
}
bool CThArm::RotatorP(unsigned char* Turn,	unsigned char* pSensor, unsigned char* nSensor, double dTimeout)	
{
#ifdef _Demo
	return true;
#endif 

	// 90
	// 1. Set Output 
	// 2. Set Timer
	// 3. Check lmt OK
	// 4. return

	int iStart = ::GetTickCount();
	*Turn = 1;	// set to false, to find P lmt

	while (1)
	{
		if ( (::GetTickCount() - iStart) >= (dTimeout) )
			return false;	// Timeout
		else if( *pSensor == 1 && *nSensor == 0 )
			return true;	// InPos	// Make in plmt and leave nlmt
		else if( f.IsPause() )
			return false;

		Sleep(_Wait);
	}

	return false;
}
bool CThArm::RotatoeICExist( unsigned char* pSensor )	
{
	// IC Exist return true
	// IC Missing return false

#ifdef _Demo
	return true;
#endif

	if( *pSensor == _RotatorExistOn )
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool CThArm::RotatorCheckJam( unsigned char* pSensor )	
{
	// Jam return true
#ifdef _Demo
	return false;
#endif
	
	if( *pSensor == _RotatorJamOn )
	{
		return true;
	}
	else
	{
		return false;
	}
}
void CThArm::InsertOutputYield(CString csCode)
{
	CString m_csCode = _T("");
	m_csCode = csCode;

	int iSize = m.m_OutputYieldCounter.GetSize();
	bool bFind = false;
	for(int i=0;i<iSize;i++)
	{
		CString m_csGetCode = _T("");
		m_csGetCode = m.m_OutputYieldCounter.GetAt(i).m_csCode;
		long m_lCounter = 0;
		m_lCounter = m.m_OutputYieldCounter.GetAt(i).m_lCodeCounter;
		if( m_csCode == m_csGetCode )
		{
			tagOutputYield m_set;
			m_set.m_csCode = m_csGetCode;
			m_lCounter++;
			m_set.m_lCodeCounter = m_lCounter;
			m.m_OutputYieldCounter.SetAt(i, m_set);
			bFind = true;
			break;
		}
	}

	if( !bFind )
	{
		// Other
		int iIndex = iSize-1;
		tagOutputYield m_set;
		m_set.m_csCode = _BinDescOther;
		long m_lCounter = 0;
		m_lCounter = m.m_OutputYieldCounter.GetAt(iIndex).m_lCodeCounter;
		m_lCounter++;
		m_set.m_lCodeCounter = m_lCounter;
		m.m_OutputYieldCounter.SetAt(iIndex, m_set);
		bFind = true;
	}

	//
	f.SaveOutputYieldValue();
}

void CThArm::AutoInputTray()
{
	if( m_bInputEmpty )
	{
		m_bInputEmpty = false;
		theApp.m_InputTray.ChangeTray();
	}
}
void CThArm::Running()
{
	if(!m_bInitialized && m.Info.iStatus != theApp.enInitial)
	{
		m_bStatus = enIdle;
		m.ThStatus.ArmCtrl.line = m_bStatus;
		return;
	}
	// If Handler status is Uninitial. We force it to return and keep m_bStatus in enIdle.
	// Notes : In Thread Monitior. Uninitial will always be enIdle
	
	if( m_bInitialRequest )
	{
		f.CWinMessage( "Arm:enInitialize R", theApp.enDArm );
		m_bInitialRequest = false;
		m_bStatus = enInitialize;
	}

	m.ThStatus.ArmCtrl.line = m_bStatus;
	switch(m_bStatus)
	{			
	case enInitialize:	
		{
			//
			long oldYInPos = m.m_Motor.ArmY.InPosRange;
			long oldZInPos = m.m_Motor.ArmZ.InPosRange;

			Initialize();

			//
			m.m_Motor.ArmY.InPosRange = oldYInPos;
			m.m_Motor.ArmZ.InPosRange = oldZInPos;
		}
		NextStatus();
		break;
	case enIdle:		
		NextStatus();
		break;

	// Cycle
	///////////////////////////////
	// Input Get IC
	case enToInput:							// Arm XY move to Input stack
		if(m.Setting.m_bEnableSemiAuto)//Semi Auto
		{
		
		}
		else
		{

			m_bInTrayMissingError = false;
			m_bTSRemainICEnable = false;
			//
			if( GetRemoteCoordRequest() )
			{
				
			}
			else if( m.Info.iStatus == theApp.enOneCycle )
			{
			
			}
			else if( m.Info.iStatus == theApp.enOverride )
			{
			
			}
			else if( f.HeaterOnNeed() && !m.m_heaterCtrl.m_bHeaterIsStable )
			{
				m_bHeaterStableNeed = true;
			}
			else if (!CheckInputExit())
			{
				m_bInTrayMissingError = true;
				//////////////////////////////////////////////////////////
				// Input Tray Missing
			}
			else if( m.RemoteInterlock.IsRemoteControlMode == true )
			{
				CString csRemoteControlMsg = _T("");
				csRemoteControlMsg.Format("Arm:enToInput Remote Position: %d", m.RemoteInterlock.RemotePosition );
 				f.CWinMessage( csRemoteControlMsg, theApp.enDArm );

				//////////////////////////////////////////////////////////
				// Remote Control Mode
				CPoint px;
				px = theApp.m_InputTray.GetCoordinate( m.RemoteInterlock.RemotePosition );

				m_iRunError = f.Motor.MotorRunLine(
					m.m_Motor.ArmX, px.x + ( m.m_Offset.Input.x * m.m_Ratio.X_GearRation ),
					m.m_Motor.ArmY, px.y + ( m.m_Offset.Input.y * m.m_Ratio.Y_GearRation ),
					true, m.TimerSetting.iMotorRunlineTimeout );
			}
			else if( m.Setting.m_bEnableTSRemainIC == 1 && 
				!m.m_TSRemainICParameter.bTSRemainICflag )
			{
				m.m_TSRemainICParameter.bTSRemainICflag = true;
				m_bTSRemainICEnable = true;
			}
			else if( m.m_RepeatTrayCtrl.m_iRepeatTrayMode == theApp.enRepeatTrayInOutCtrl )
			{
				// Repeat Tray Mode
			}
			else if( theApp.m_InputTray.LocationQuery() != CTrayFile::enEOF )
			{
				//////////////////////////////////////////////////////////
				// Normal Mode
				int iBooking = -1;
				//
				CPoint px;
				iBooking = theApp.m_InputTray.LocationBooking();
				px = theApp.m_InputTray.GetCoordinate( iBooking );
				theApp.m_InputTray.LocationMove();

				//
				CString csNormalMsg = _T("");
				csNormalMsg.Format("Arm:enToInput Position: %d", iBooking );
				f.CWinMessage( csNormalMsg, theApp.enDArm );

				// 
				theApp.m_tArm.ClearArmLog();
				ArmLog.iBooking = iBooking;

				//
				m_iRunError = f.Motor.MotorRunLine(
					m.m_Motor.ArmX, px.x + ( m.m_Offset.Input.x * m.m_Ratio.X_GearRation ),
					m.m_Motor.ArmY, px.y + ( m.m_Offset.Input.y * m.m_Ratio.Y_GearRation ),
					true, m.TimerSetting.iMotorRunlineTimeout );
			}
			else
			{
				// Input Tray 已經沒有料了
				// 吸完回到待命位置....準備去吸最後一顆 IC, 然後 Cycle Finish
				m.InterLock.ArmEnd = true;
				m_bInputEmpty = true;
			}
		}
		NextStatus();
		break;
	case enPickIC:							// Arm Z down to pick IC
		{
			//
			double dExterndAdjustValue = 0.0;
			dExterndAdjustValue = AutoRetryAdjustValue( m_lArmRetryCounter );
			//

			m_iRunError = f.Motor.MotorRun(&m.m_Motor.ArmZ, 
				( m.m_Align.Input.z + ( m.m_Offset.Input.z * m.m_Ratio.Z_GearRation ) + 
				( dExterndAdjustValue * m.m_Ratio.Z_GearRation ) ), false, 
				m.TimerSetting.iMotorRunTimeout );		
		}
		NextStatus();
		break;
	case enVacuumStart:						// Arm Z ready to turn on Vacc
		{
		
		}
		NextStatus();
		break;
	case enVacuum:							// Arm Z turn on Vacc
		{
			m_ZWithIC = Vacc( &m.OutSet.ArmVacc, &m.InStatus.ArmZVaccSensor, m.Timer.m_dPickPick );
		}
		NextStatus();
		break;
	case enVacuumEnd:						// Arm Z turn on Vacc and check pick ok or not.
		{
		
		}
		NextStatus();
		break;
	case enToHome:							// Arm Z pick IC ok, Arm Z up to home
		{
			m_iRunError = f.Motor.MotorRun( 
				&m.m_Motor.ArmZ, ( _InitialZHome * m.m_Ratio.Z_GearRation ), true, 
				m.TimerSetting.iMotorRunTimeout );		
		}
		NextStatus();
		break;
	case enToHomeEnd:						// Arm Z back to home ok, ( check go to rotator or shuttle in)
		NextStatus();
		break;
	///////////////////////////////
	// Rotator Input
	case enRotatorInCheckSetting:			// Rotator check rotator setting.
		NextStatus();
		break;
	case enRotatorInRamin:					// After check rotator, Make sure rotator have no IC
		NextStatus();
		break;
	case enRotatorInGoToRotator:			// Arm XY move to rotator position
		{
			m_iRunError = f.Motor.MotorRunLine( 
				m.m_Motor.ArmX, m.m_Align.Rotator.x + ( m.m_Offset.Rotator.x * m.m_Ratio.X_GearRation ),
				m.m_Motor.ArmY, m.m_Align.Rotator.y + ( m.m_Offset.Rotator.y * m.m_Ratio.Y_GearRation ), true, m.TimerSetting.iMotorRunlineTimeout );
		}
		NextStatus();
		break;
	case enRotatorInCheckReadyForInput:		// Rotator turn for input IC
		{
			if( m.m_TestSetting.m_Angle == 1 )			// +90
			{	
				RotatorNOK = RotatorN( 
					&m.RemoteOutSet.Rotator,
					&m.RemoteInStatus.RotatepLmt,
					&m.RemoteInStatus.RotatenLmt,
					m.TimerSetting.iRotatorTimeout );

				f.Wait( m.TimerSetting.iRotatorTime );	// Stable time				
			}
			else if( m.m_TestSetting.m_Angle == 0 )		// -90
			{
				RotatorPOK = RotatorP( 
					&m.RemoteOutSet.Rotator,
					&m.RemoteInStatus.RotatepLmt,
					&m.RemoteInStatus.RotatenLmt,
					m.TimerSetting.iRotatorTimeout );
				
				f.Wait( m.TimerSetting.iRotatorTime );	// Stable time
			}
			// Pre-Guide
			else if( m.m_TestSetting.m_Angle == 2 )		// 0 for Pre-Guide
			{
				RotatorNOK = RotatorN( 
					&m.RemoteOutSet.Rotator,
					&m.RemoteInStatus.RotatepLmt,
					&m.RemoteInStatus.RotatenLmt,
					m.TimerSetting.iRotatorTimeout );
				
				f.Wait( m.TimerSetting.iRotatorTime );	// Stable time	
			}
		}
		NextStatus();
		break;
	case enRotatorInBlowDown:				// Arm Z down to place IC
		{
			m_iRunError = f.Motor.MotorRun(&m.m_Motor.ArmZ, 
				m.m_Align.Rotator.z + ( m.m_Offset.Rotator.z2 * m.m_Ratio.Z_GearRation ), false, m.TimerSetting.iMotorRunTimeout );
		}
		NextStatus();
		break;
	case enRotatorInBlow:					// Arm Z turn on blow 
		{
			m_ZWithIC = Blow( 
				&m.OutSet.ArmVacc, 
				&m.OutSet.ArmBlow, 
				&m.InStatus.ArmZVaccSensor, 
				m.Timer.m_dPickPuff );
		}
		NextStatus();
		break;
	case enRotatorInBlowUp:					// Arm Z place IC to Rotator ok, Arm Z up 
		{
			m_iRunError = f.Motor.MotorRun( 
				&m.m_Motor.ArmZ, ( _InitialZHome * m.m_Ratio.Z_GearRation ), true, 
				m.TimerSetting.iMotorRunTimeout );	
		}
		NextStatus();
		break;
	case enRotatorInCheckJamForBlow:		// After IC Place to Rotator. Check Jam
		NextStatus();
		break;
	case enRotatorInTurn:					// Rotator change IC pin1 
		{
			if( m.m_TestSetting.m_Angle == 1 )				// +90
			{
				RotatorPOK = RotatorP( 
					&m.RemoteOutSet.Rotator,
					&m.RemoteInStatus.RotatepLmt,
					&m.RemoteInStatus.RotatenLmt,
					m.TimerSetting.iRotatorTimeout );
				
				f.Wait( m.TimerSetting.iRotatorTime );	// Stable time	
			}
			else if( m.m_TestSetting.m_Angle == 0 )			// -90
			{
				RotatorNOK = RotatorN( 
					&m.RemoteOutSet.Rotator,
					&m.RemoteInStatus.RotatepLmt,
					&m.RemoteInStatus.RotatenLmt,
					m.TimerSetting.iRotatorTimeout );
				
				f.Wait( m.TimerSetting.iRotatorTime );	// Stable time	
			}
			else if( m.m_TestSetting.m_Angle == 2 )			// 0
			{
				// Pre - Guide 不旋轉	

			}
			else
				; // Never be here.		
		}
		NextStatus();
		break;
	case enRotatorInCheckJamForPick:		// Before Arm Z Pick IC	check Jam
		{
		
		}
		NextStatus();
		break;
	case enRotatorInPickDown:				// Rotator change ok, Arm Z down to pick IC
		{
			m_iRunError = f.Motor.MotorRun(&m.m_Motor.ArmZ, 
				m.m_Align.Rotator.z + ( m.m_Offset.Rotator.z * m.m_Ratio.Z_GearRation ), false, m.TimerSetting.iMotorRunTimeout );
		}
		NextStatus();
		break;
	case enRotatorInPick:					// Arm Z Vacc turn on
		{
			m_ZWithIC = Vacc( &m.OutSet.ArmVacc, &m.InStatus.ArmZVaccSensor, m.Timer.m_dPickPick );
		}
		NextStatus();
		break;
	case enRotatorInPickUp:					// Arm Z up  
		{
			m_iRunError = f.Motor.MotorRun( 
				&m.m_Motor.ArmZ, ( _InitialZHome * m.m_Ratio.Z_GearRation ), false, 
				m.TimerSetting.iMotorRunTimeout );	
		}
		NextStatus();
		break;
	case enRotatorInEnd:					// Rorator In complete. ( IC in ArmZ, ok go to shuttle )
		NextStatus();		
		break;

	case enRotatorInPickReset:
		{
			m_iRunError = f.Motor.MotorRunLine( 
				m.m_Motor.ArmX, m.m_Align.Rotator.x + ( m.m_Offset.Rotator.x * m.m_Ratio.X_GearRation ),
				m.m_Motor.ArmY, m.m_Align.Rotator.y + ( m.m_Offset.Rotator.y * m.m_Ratio.Y_GearRation ), true, m.TimerSetting.iMotorRunlineTimeout );
		}
		NextStatus();		
		break;
	///////////////////////////////
	// To Shuttle Place IC
	case enToShuttle:						// Arm XY move to shuttle 
		{
			m_iRunError = f.Motor.MotorRunLine( 
				m.m_Motor.ArmX, m.m_Align.DutIn.x + ( m.m_Offset.DutIn.x * m.m_Ratio.X_GearRation ),
				m.m_Motor.ArmY, m.m_Align.DutIn.y + ( m.m_Offset.DutIn.y * m.m_Ratio.Y_GearRation ), true, m.TimerSetting.iMotorRunlineTimeout );
		}
		NextStatus();
		break;
	case enShuttlePlaceIC:					// Arm Z down to place IC
		{
			m_iRunError = f.Motor.MotorRun(&m.m_Motor.ArmZ, 
				m.m_Align.DutIn.z2 + ( m.m_Offset.DutIn.z2 * m.m_Ratio.Z_GearRation ), false, m.TimerSetting.iMotorRunTimeout );
		}
		NextStatus();
		break;
	case enShuttleBlow:						// Arm Z turn on the blow
		{
			m_ZWithIC = Blow( 
				&m.OutSet.ArmVacc, 
				&m.OutSet.ArmBlow, 
				&m.InStatus.ArmZVaccSensor, 
				m.Timer.m_dPickPuff );
		}
		NextStatus();
		break;
	case enShuttleUp:						// Arm Z up
		{
			m_iRunError = f.Motor.MotorRun( 
				&m.m_Motor.ArmZ, ( _InitialZHome * m.m_Ratio.Z_GearRation ), false, 
				m.TimerSetting.iMotorRunTimeout );	
		}
		NextStatus();
		break;

	case enShuttleCheckJam:
		{
		
		}
		NextStatus();
		break;
	case enShuttleCheckJamOK:
		{
		
		}
		NextStatus();
		break;
	case enShuttleDoubleCheckJam:
		{
		
		}
		NextStatus();
		break;
	case enShuttleJamGoStandy:
		{
			m_iRunError = f.Motor.MotorRunLine( 
				m.m_Motor.ArmX, m.m_Align.StandyBy.x + ( m.m_Offset.StandyBy.x * m.m_Ratio.X_GearRation ) + ( m.Setting.m_dStandyX * m.m_Ratio.X_GearRation ),
				m.m_Motor.ArmY, m.m_Align.StandyBy.y + ( m.m_Offset.StandyBy.y * m.m_Ratio.Y_GearRation ) + ( m.Setting.m_dStandyY * m.m_Ratio.Y_GearRation ), 
				true, m.TimerSetting.iMotorRunlineTimeout );		
		}
		NextStatus();
		break;

	///////////////////////////////
	// CCD Pin1 
	case enShuttleCCDPin1Start:				// CCD Pin1
		{
		
		}
		NextStatus();
		break;
	case enShuttleCCDPin1Grab:				// CCD Grab
		{
			//取像 Jerome
		}
		NextStatus();
		break;
	case enShuttleCCDMatch:					// CCD Grab Match
		{
		
		}
		NextStatus();
		break;
	case enShuttleCCDMatchEnd:				// CCD Grab Match complete.
		{
		
		}
		NextStatus();
		break;

	///////////////////////////////
	// CCD Arm Log Image
	case enArmLogImageStart:				// Image Log Arm
		{
		
		}
		NextStatus();
		break;
	case enArmLogImageStable:				// Image Log Arm, Wait Motor Stable
		{
#ifdef _Demo
#else
			f.Wait( m.m_ArmLogICImage.dCaptureStableTime * 1000. );
#endif
		}
		NextStatus();
		break;
	case enArmLogImageGrabMove:					// Image Log Arm, Ready to grab image
		{
			// Arm move to CCD Position
			double m_dArmX = m.m_Align.DutIn.x 
				+ ( m.m_Offset.DutIn.x * m.m_Ratio.X_GearRation) + ( _ArmZToCCD_X * m.m_Ratio.X_GearRation);
			double m_dArmY = m.m_Align.DutIn.y 
				+ ( m.m_Offset.DutIn.y * m.m_Ratio.Y_GearRation) + ( _ArmZToCCD_Y * m.m_Ratio.Y_GearRation);

			//
			f.Motor.MotorRunLine( 
				m.m_Motor.ArmX, m_dArmX,
				m.m_Motor.ArmY, m_dArmY, 
				true, m.TimerSetting.iMotorRunlineTimeout );
		}
		NextStatus();
		break;
	case enArmLogImageDirectory:			// Image Log Arm, Is Directory Exist
		{
			// Function root folder
			IsArmLogRootFolderMissing();

			// Lot Image folder
			IsArmLogICImageFolderMissing();
		}
		NextStatus();
		break;
	case enArmLogImageGrab:					// Image Log Arm, Ready to grab image
		{
			CameraCapture();
		}
		NextStatus();
		break;
	case enArmLogImageSaveIage:				// Image Log Arm, Save the Image
		{
			
		}
		NextStatus();
		break;
	case enArmLogImageWaitStable:			// Image Log Arm, Wait Motor Stable
		{
		}
		NextStatus();
		break;
	case enArmLogImageEnd:					// Image Log Arm, Save the Image
		{
		
		}
		NextStatus();
		break;
	///////////////////////////////
	// Standy 
	case enToStandyStart:
		{
		
		}
		NextStatus();
		break;
	case enToStandy:						// Arm XY move to standy 
		{
			m_iRunError = f.Motor.MotorRunLine( 
				m.m_Motor.ArmX, m.m_Align.StandyBy.x + ( m.m_Offset.StandyBy.x * m.m_Ratio.X_GearRation ) + ( m.Setting.m_dStandyX * m.m_Ratio.X_GearRation ),
				m.m_Motor.ArmY, m.m_Align.StandyBy.y + ( m.m_Offset.StandyBy.y * m.m_Ratio.Y_GearRation ) + ( m.Setting.m_dStandyY * m.m_Ratio.Y_GearRation ), 
				true, m.TimerSetting.iMotorRunlineTimeout );
		}
		NextStatus();
		break;
	case enToStandyEnd:						// Arm XY move to standy OK
		{
		
		}
		NextStatus();
		break;
	case enToStandyWait:					// Arm XY move to standy wait for output
		{
		
		}
		NextStatus();
		break;
	///////////////////////////////
	// Rotator Output
	case enRotatorOutCheckSetting:			// Rotator check rotator setting
		NextStatus();
		break;
	case enRotatorOutRamin:					// After check rotator, Make sure rotator have no IC
		NextStatus();
		break;
	case enRotatorOutGotoRotator:			// Arm XY move to rotator
		{
			m_iRunError = f.Motor.MotorRunLine( 
				m.m_Motor.ArmX, m.m_Align.Rotator.x + ( m.m_Offset.Rotator.x * m.m_Ratio.X_GearRation ),
				m.m_Motor.ArmY, m.m_Align.Rotator.y + ( m.m_Offset.Rotator.y * m.m_Ratio.Y_GearRation ), true, m.TimerSetting.iMotorRunlineTimeout );
		}
		NextStatus();
		break;
	case enRotatorOutCheckReadyForOutput:	// Turn the Rotator, then Arm can place IC to rotator
		{
			if( m.m_TestSetting.m_Angle == 1 )				// +90
			{
				RotatorPOK = RotatorP( 
					&m.RemoteOutSet.Rotator,
					&m.RemoteInStatus.RotatepLmt,
					&m.RemoteInStatus.RotatenLmt,
					m.TimerSetting.iRotatorTimeout );
				
				f.Wait( m.TimerSetting.iRotatorTime );	// Stable time			
			}
			else if( m.m_TestSetting.m_Angle == 0 )			// -90
			{

				RotatorNOK = RotatorN( 
					&m.RemoteOutSet.Rotator,
					&m.RemoteInStatus.RotatepLmt,
					&m.RemoteInStatus.RotatenLmt,
					m.TimerSetting.iRotatorTimeout );
				
				f.Wait( m.TimerSetting.iRotatorTime );	// Stable time	
			}
			else
				;	// Never be here
		}
		NextStatus();
		break;
	case enRotatorOutBlowDown:				// Arm Z down to place IC
		{
			m_iRunError = f.Motor.MotorRun(&m.m_Motor.ArmZ, 
				m.m_Align.Rotator.z + ( m.m_Offset.Rotator.z2 * m.m_Ratio.Z_GearRation ), false, m.TimerSetting.iMotorRunTimeout );
		}
		NextStatus();
		break;
	case enRotatorOutBlow:					// Arm Z down and turn on the blow 
		{
			m_ZWithIC = Blow( 
				&m.OutSet.ArmVacc, 
				&m.OutSet.ArmBlow, 
				&m.InStatus.ArmZVaccSensor, 
				m.Timer.m_dPickPuff
				);	
		}
		NextStatus();
		break;
	case enRotatorOutBlowUp:				// Arm Z up
		{
			m_iRunError = f.Motor.MotorRun( 
				&m.m_Motor.ArmZ, ( _InitialZHome * m.m_Ratio.Z_GearRation ), true, 
				m.TimerSetting.iMotorRunTimeout );	
		}
		NextStatus();
		break;
	case enRotatorOutCheckJamForBlow:		// After place the IC, check Jam
		NextStatus();
		break;
	case enRotatorOutTurn:					// Turn the rotator
		{
			if( m.m_TestSetting.m_Angle == 1 )			// +90
			{
				RotatorNOK = RotatorN( 
					&m.RemoteOutSet.Rotator,
					&m.RemoteInStatus.RotatepLmt,
					&m.RemoteInStatus.RotatenLmt,
					m.TimerSetting.iRotatorTimeout );
				
				f.Wait( m.TimerSetting.iRotatorTime );	// Stable time	
			}
			else if( m.m_TestSetting.m_Angle == 0 )		// -90
			{

				RotatorPOK = RotatorP( 
					&m.RemoteOutSet.Rotator,
					&m.RemoteInStatus.RotatepLmt,
					&m.RemoteInStatus.RotatenLmt,
					m.TimerSetting.iRotatorTimeout );
				
				f.Wait( m.TimerSetting.iRotatorTime );	// Stable time	
			}		
		}
		NextStatus();
		break;
	case enRotatorOutCheckJamForPick:		// Before Arm Z Pick IC	check Jam
		NextStatus();
		break;
	case enRotatorOutPickDown:				// Arm Z down to pick IC
		{
			m_iRunError = f.Motor.MotorRun(&m.m_Motor.ArmZ, 
				m.m_Align.Rotator.z + ( m.m_Offset.Rotator.z * m.m_Ratio.Z_GearRation ), false, m.TimerSetting.iMotorRunTimeout );
		}
		NextStatus();
		break;
	case enRotatorOutPick:					// Arm Z turn on the Vacuum
		{
			m_ZWithIC = Vacc( &m.OutSet.ArmVacc, &m.InStatus.ArmZVaccSensor, m.Timer.m_dPickPick );
		}
		NextStatus();
		break;
	case enRotatorOutPickUp:				// Arm Z up
		{
			m_iRunError = f.Motor.MotorRun( 
				&m.m_Motor.ArmZ, ( _InitialZHome * m.m_Ratio.Z_GearRation ), true, 
				m.TimerSetting.iMotorRunTimeout );			
		}
		NextStatus();
		break;
	case enRotatorOutPickEnd:				// Rotator Out complete ( IC in ArmZ, ok go to bining )
		NextStatus();
		break;
	case enRotatorOutputReset:
		{
			m_iRunError = f.Motor.MotorRunLine( 
				m.m_Motor.ArmX, m.m_Align.Rotator.x + ( m.m_Offset.Rotator.x * m.m_Ratio.X_GearRation ),
				m.m_Motor.ArmY, m.m_Align.Rotator.y + ( m.m_Offset.Rotator.y * m.m_Ratio.Y_GearRation ), true, m.TimerSetting.iMotorRunlineTimeout );
		}
		NextStatus();
		break;
	///////////////////////////////
	// Shuttle (Output)
	case enToShuttleOutput:					// Arm XY move to shuttle 
		{
			m_iRunError = f.Motor.MotorRunLine( 
				m.m_Motor.ArmX, m.m_Align.DutOut.x + ( m.m_Offset.DutOut.x * m.m_Ratio.X_GearRation ),
				m.m_Motor.ArmY, m.m_Align.DutOut.y + ( m.m_Offset.DutOut.y * m.m_Ratio.Y_GearRation ), true, m.TimerSetting.iMotorRunlineTimeout );
		}
		NextStatus();
		break;
	case enToShuttlePick:					// Arm Z down to pick
		{
			m_iRunError = f.Motor.MotorRun(&m.m_Motor.ArmZ, 
				m.m_Align.DutOut.z + ( m.m_Offset.DutOut.z * m.m_Ratio.Z_GearRation ), false, m.TimerSetting.iMotorRunTimeout );
		}
		NextStatus();
		break;
	case enToShuttlePickVaccStart:			// Arm Z ready to turn on the vacc
		{
		
		}
		NextStatus();
		break;
	case enToShuttlePickVacc:				// Arm Z turn on the vacc
		{
			m_ZWithIC = Vacc( &m.OutSet.ArmVacc, &m.InStatus.ArmZVaccSensor, m.Timer.m_dPickPick );
		}
		NextStatus();
		break;
	case enToShuttlePickVaccEnd:			// Arm Z vacc end
		{
		
		}
		NextStatus();
		break;
	case enToShuttleUpForOutput:			// Arm Z up for output 
		{
			m_iRunError = f.Motor.MotorRun( &m.m_Motor.ArmZ, ( _InitialZHome * m.m_Ratio.Z_GearRation ), true, 
				m.TimerSetting.iMotorRunTimeout );	
		}
		NextStatus();
		break;

	///////////////////////////////
	// Output Place IC
	// Bin
	case enToOutputCheckFix:				// Check Fix1 
		{
		
		}
		NextStatus();
		break;
	case enToOutput:						// Arm XY Move to Output area, ready to place IC
		{
			if( GetRemoteCoordRequest() )
			{
			}
			else if( theApp.m_OutputTray.LocationQuery() != CTrayFile::enEOF )
			{
				int iBooking = -1;
				//
				CPoint px;
				iBooking = theApp.m_OutputTray.LocationBooking();
				px = theApp.m_OutputTray.GetCoordinate( iBooking );
				theApp.m_OutputTray.LocationMove();

				//
				m_bFix1TrayFull = false;

				//
				m_iRunError = f.Motor.MotorRunLine( 
					m.m_Motor.ArmX, px.x + ( m.m_Offset.Output1.x * m.m_Ratio.X_GearRation ),
					m.m_Motor.ArmY, px.y + ( m.m_Offset.Output1.y * m.m_Ratio.Y_GearRation ), true, m.TimerSetting.iMotorRunlineTimeout );
			}
			else
			{
				// Ops: Fix Tray is full....
				m_bFix1TrayFull = true;
			}
		}
		NextStatus();
		break;
	case enToOutputPlaceIC:					// Arm Z down to place IC
		{
			m_iRunError = f.Motor.MotorRun(&m.m_Motor.ArmZ, 
				m.m_Align.Output1.z + ( m.m_Offset.Output1.z2 * m.m_Ratio.Z_GearRation ), 
				false, m.TimerSetting.iMotorRunTimeout );	
		}
		NextStatus();
		break;
	case enToOutputPlaceBlow:				// Arm Z turn on the Blow
		{
			m_ZWithIC = Blow( 
				&m.OutSet.ArmVacc, 
				&m.OutSet.ArmBlow, 
				&m.InStatus.ArmZVaccSensor, 
				m.Timer.m_dPickPuff
				);
		}
		NextStatus();
		break;
	case enToOutputHome:					// Arm up to home
		{
			theApp.m_OutputTray.LocationDone();

			//
			m_iRunError = f.Motor.MotorRun( 
				&m.m_Motor.ArmZ, ( _InitialZHome * m.m_Ratio.Z_GearRation ), true, 
				m.TimerSetting.iMotorRunTimeout );	
		}
		NextStatus();
		break;
	case enToOutputHomeEnd:					// Arm up to home OK. ready to input again.
		{
			// Insert Test Log
			/*
			f.Report.InsertBinLog( theApp.m_tInserter.TestSiteLog );
			theApp.m_tInserter.ClearTestSiteLog();
			theApp.m_tArm.ClearArmLog();
			f.InsertJamRateTotalCounter();
			*/
			// 1.0Aj
			f.Report.InsertBinLog( theApp.m_tArm.ArmLog );
			theApp.m_tArm.ClearArmLog();
			f.InsertJamRateTotalCounter();
		}
		NextStatus();
		break;
	case enToOutputChangeTray:				// Change Tray, Clear Fix Tray
		{
		
		}
		NextStatus();
		break;
	///////////////////////////////
	// Remote Control
	case enRemoteControlToInput:			// To Input Place IC
		{
			CString csRemoteControlMsg = _T("");
			csRemoteControlMsg.Format("Arm:enToInput Remote Position: %d", m.RemoteInterlock.RemotePosition );
			f.CWinMessage( csRemoteControlMsg, theApp.enDArm );
			
			//////////////////////////////////////////////////////////
			// Remote Control Mode
			CPoint px;
			px = theApp.m_InputTray.GetCoordinate( m.RemoteInterlock.RemotePosition );
			
			m_iRunError = f.Motor.MotorRunLine(
				m.m_Motor.ArmX, px.x + ( m.m_Offset.Input.x * m.m_Ratio.X_GearRation ),
				m.m_Motor.ArmY, px.y + ( m.m_Offset.Input.y * m.m_Ratio.Y_GearRation ),
				true, m.TimerSetting.iMotorRunlineTimeout );		
		}
		NextStatus();
		break;
	case enRemoteControlPlaceIC:			// Arm Z down to place IC
		{
			m_iRunError = f.Motor.MotorRun(&m.m_Motor.ArmZ, 
			m.m_Align.Input.z2 + ( m.m_Offset.Input.z2 * m.m_Ratio.Z_GearRation ), false, m.TimerSetting.iMotorRunTimeout );
		}
		NextStatus();
		break;
	case enRemoteControlBlow:				// Blow
		{
			m_ZWithIC = Blow( 
				&m.OutSet.ArmVacc, 
				&m.OutSet.ArmBlow, 
				&m.InStatus.ArmZVaccSensor, 
				m.Timer.m_dPickPuff
				);
		}
		NextStatus();
		break;
	case enRemoteControlHome:				// Home
		{
			m_iRunError = f.Motor.MotorRun( 
				&m.m_Motor.ArmZ, ( _InitialZHome * m.m_Ratio.Z_GearRation ), true, 
				m.TimerSetting.iMotorRunTimeout );				
		}
		NextStatus();
		break;
	case enRemoteControlHomeEnd:			// Home End
		{
		}
		NextStatus();
		break;
	case enRemoteControlWaitPick:
		{
		
		}
		NextStatus();
		break;

	///////////////////////////////	
	// Cycle Finish
	case enCycleStandy:
		{
			m_iRunError = f.Motor.MotorRunLine( 
				m.m_Motor.ArmX, m.m_Align.StandyBy.x + ( m.m_Offset.StandyBy.x * m.m_Ratio.X_GearRation ) + ( m.Setting.m_dStandyX * m.m_Ratio.X_GearRation ),
				m.m_Motor.ArmY, m.m_Align.StandyBy.y + ( m.m_Offset.StandyBy.y * m.m_Ratio.Y_GearRation ) + ( m.Setting.m_dStandyY * m.m_Ratio.Y_GearRation ), 
				true, m.TimerSetting.iMotorRunlineTimeout );
		}
		NextStatus();
		break;
	case enCycleEnd:						// Cycle Finish
		NextStatus();
		break;
	///////////////////////////////
	// Heater
	case enHeaterWaitStableStart:		// Heater Wait Stable Start
		{
		
		}
		NextStatus();
		break;
	case enHeaterWaitTemper:			// Heater Wait Stable
		{
			if( m.Info.iStatus == theApp.enOneCycle )
			{
			}
			else if( m.Info.iStatus == theApp.enOverride )
			{			
			}
			else
				m_bWaitHeaterOK = WaitHeaterOK();
		}
		NextStatus();
		break;
	case enHeaterWaitStable:
		{			
			if( m.Info.iStatus == theApp.enOneCycle )
			{
			}
			else if( m.Info.iStatus == theApp.enOverride )
			{			
			}
			else
				m_bWaitHeaterStableOK = WaitHeaterStableOK();
		}
		NextStatus();
		break;
	case enHeaterWaitStableEnd:			// Heater Wait Stable end
		{
		
		}
		NextStatus();
		break;
	///////////////////////////////
	// TS Remain IC
	case enTSRemainICStart:					// TS Remain IC Start
		{

		}
		NextStatus();
		break;
	case enTSRemainICContactHome:			// TS Remain IC Chamber Contact Move to Home
		{
		
		}
		NextStatus();
		break;
	case enTSRemainICDryHome:				// TS Remain IC Dry Shuttle Move to Home
		{
		
		}
		NextStatus();
		break;
	case enTSRemainICTSDown:				// TS Remain IC TS Down 
		{
			m_iRunError = f.Motor.MotorRunTSRemainIC(&m.m_Motor.Inserter, 
				m.m_Align.TestSite.contact + ( m.m_Offset.TestSite.contact * m.m_Ratio.Inserter_GearRation ), 
				false, m.TimerSetting.iMotorRunTimeout, m.m_TSRemainICParameter.iTSRemainICSpeed );		
		}
		NextStatus();
		break;
	case enTSRemainICTSVaccOn:				// TS Remain IC Turn IC
		{
			m_TSRemainWithIC = TSRemainICVacc( &m.OutSet.TestSiteVacc, &m.InStatus.TestSiteZVaccSensor, 
				m.m_TSRemainICParameter.dTSRemainICVacc );
		}
		NextStatus();
		break;
	case enTSRemainICTSVaccEnd:				// TS Remain IC Vacc End ( Check do we need to turn off Vacc )
		{
		
		}
		NextStatus();
		break;
	case enTSRemainICTSUp:					// TS Remain IC TS Up
		{
			m_iRunError = f.Motor.MotorRun(&m.m_Motor.Inserter, 
				( m.m_Align.TestSite.home + 
				( m.m_Offset.TestSite.home * m.m_Ratio.Inserter_GearRation ) +
				( m.Setting.m_dTestSiteStandbyPosition * m.m_Ratio.Inserter_GearRation )), 
				false, m.TimerSetting.iMotorRunTimeout );		
		}
		NextStatus();
		break;
	case enTSRemainICCheck:					// TS Remain IC Check Pass Or Fail
		{
		
		}
		NextStatus();
		break;
	case enTSRemainICEnd:					// TS Remain IC End..
		{
			TSRemainICVaccOff( &m.OutSet.TestSiteVacc );
		}
		NextStatus();
		break;

	///////////////////////////////	
	// Repeat Tray / Input / Output Ctrl
	// Get IC
	case enRepeatToInput:
		{
			if( m.Info.iStatus == theApp.enOneCycle )
			{
				
			}
			else if( m.Info.iStatus == theApp.enOverride )
			{
				
			}
			else
				m_iRunError = RepeatMationInput();
		}
		NextStatus();
		break;
	case enRepeatPickIC:
		{
			m_iRunError = RepeatMationInputZDown();
		}
		NextStatus();
		break;
	case enRepeatVacc:
		{
			m_ZWithIC = Vacc( &m.OutSet.ArmVacc, &m.InStatus.ArmZVaccSensor, m.Timer.m_dPickPick );
		}
		NextStatus();
		break;
	case enRepeatVaccEnd:
		{
		
		}
		NextStatus();
		break;
	case enRepeatInToHome:
		{
			m_iRunError = f.Motor.MotorRun( 
				&m.m_Motor.ArmZ, ( _InitialZHome * m.m_Ratio.Z_GearRation ), true, 
				m.TimerSetting.iMotorRunTimeout );			
		}
		NextStatus();
		break;
	case enRepeatInToHomeEnd:
		{
		
		}
		NextStatus();
		break;
	case enRepeatInToHomeEndEnd:
		{
			
		}
		NextStatus();
		break;
	// Put IC
	case enRepeatToOutput:
		{
			m_iRunError = RepeatMationOutput();
		}
		NextStatus();
		break;
	case enRepeatOutTray2Clear:
		{
		
		}
		NextStatus();
		break;
	case enRepeatOutTray1Clear:
		{
		
		}
		NextStatus();
		break;
	case enRepeatPlacIC:
		{
			// 1.0Ae
//			m_iRunError = RepeatMationInputZDown();
			m_iRunError = RepeatMationOutputZDown();
		}
		NextStatus();
		break;
	case enRepeatBlow:
		{
			m_ZWithIC = Blow( 
				&m.OutSet.ArmVacc, 
				&m.OutSet.ArmBlow, 
				&m.InStatus.ArmZVaccSensor, 
				m.Timer.m_dPickPuff );		
		}
		NextStatus();
		break;
	case enRepeatBlowEnd:
		{
		
		}
		NextStatus();
		break;
	case enRepeatOutToHome:
		{
			m_iRunError = f.Motor.MotorRun( 
				&m.m_Motor.ArmZ, ( _InitialZHome * m.m_Ratio.Z_GearRation ), true, 
				m.TimerSetting.iMotorRunTimeout );			
		}
		NextStatus();
		break;
	case enRepeatOutToHomeEnd:
		{
			RepeatMationOutputDone();
		}
		NextStatus();
		break;
	case enRepeatOutToHomeEndEnd:
		{
			theApp.m_tArm.ClearArmLog();	//
		}
		NextStatus();
		break;
	// Cycle Finish
	case enRepeatCheckComplete:		// Repeat tray check complete
		{
		}
		NextStatus();
		break;
	case enRepeatCycleStandy:		// Repeat tray arm xy move to standby
		{
			m_iRunError = f.Motor.MotorRunLine( 
				m.m_Motor.ArmX, m.m_Align.StandyBy.x + ( m.m_Offset.StandyBy.x * m.m_Ratio.X_GearRation ) + ( m.Setting.m_dStandyX * m.m_Ratio.X_GearRation ),
				m.m_Motor.ArmY, m.m_Align.StandyBy.y + ( m.m_Offset.StandyBy.y * m.m_Ratio.Y_GearRation ) + ( m.Setting.m_dStandyY * m.m_Ratio.Y_GearRation ), 
				true, m.TimerSetting.iMotorRunlineTimeout );
		}
		NextStatus();
		break;
	case enRepeatCycleFinish:		// Repeat tray arm xy cycle finish
		{
		}
		NextStatus();
		break;

	///////////////////////////////	
	// Remote, SLT Protocol
	// Input
	case enRemoteProtocolInput:		// SLT Protocol Input
		{
			m_iRunError = RemoteMationInput();
		}
		NextStatus();
		break;
	case enRemoteProtocolPick:		// SLT Protocol Pick IC
		{
			m_iRunError = RemoteMationInputZDown();
		}
		NextStatus();
		break;
	case enRemoteProtocolVacc:		// SLT Protocol Vacc
		{
			m_ZWithIC = Vacc( &m.OutSet.ArmVacc, &m.InStatus.ArmZVaccSensor, m.Timer.m_dPickPick );
		}
		NextStatus();
		break;
	case enRemoteProtocolVaccEnd:	// SLT Protocol Vacc End
		{

		}
		NextStatus();
		break;
	case enRemoteProtocolInHome:	// SLT Protocol Arm Z Home
		{
			m_iRunError = f.Motor.MotorRun( 
				&m.m_Motor.ArmZ, ( _InitialZHome * m.m_Ratio.Z_GearRation ), true, 
				m.TimerSetting.iMotorRunTimeout );
		}
		NextStatus();
		break;
	case enRemoteProtocolInHomeEnd:	// SLT Protocol Arm Z Home End
		{

		}
		NextStatus();
		break;
	// Output
	case enRemoteProtocolOutput:	// SLT Protocol Output
		{
			m_iRunError = RemoteMationOutput();
		}
		NextStatus();
		break;
	case enRemoteProtocolPlace:		// SLT Protocol Place IC
		{
			m_iRunError = RemoteMationOutputZDown();
		}
		NextStatus();
		break;
	case enRemoteProtocolBlow:		// SLT Protocol Blow
		{
			m_ZWithIC = Blow( 
				&m.OutSet.ArmVacc, 
				&m.OutSet.ArmBlow, 
				&m.InStatus.ArmZVaccSensor, 
				m.Timer.m_dPickPuff );		
		}
		NextStatus();
		break;
	case enRemoteProtocolBlowEnd:	// SLT Protocol Blow End
		{
		
		}
		NextStatus();
		break;
	case enRemoteProtocolOutHome:	// SLT Protocol Arm Z Home
		{
			m_iRunError = f.Motor.MotorRun( 
				&m.m_Motor.ArmZ, ( _InitialZHome * m.m_Ratio.Z_GearRation ), true, 
				m.TimerSetting.iMotorRunTimeout );
		}
		NextStatus();
		break;
	case enRemoteProtocolOutHomeEnd:// SLT Protocol Arm Z Home End
		{
		
		}
		NextStatus();
		break;
	// Finish
	case enRemoteStandy:			// SLT Protocol Arm move to stand by
		{
			m_iRunError = f.Motor.MotorRunLine( 
				m.m_Motor.ArmX, m.m_Align.StandyBy.x + ( m.m_Offset.StandyBy.x * m.m_Ratio.X_GearRation ) + ( m.Setting.m_dStandyX * m.m_Ratio.X_GearRation ),
				m.m_Motor.ArmY, m.m_Align.StandyBy.y + ( m.m_Offset.StandyBy.y * m.m_Ratio.Y_GearRation ) + ( m.Setting.m_dStandyY * m.m_Ratio.Y_GearRation ), 
				true, m.TimerSetting.iMotorRunlineTimeout );		
		}
		NextStatus();
		break;
	case enRemoteEnd:				// SLT Protocol End
		{
		
		}
		NextStatus();
		break;
	///////////////////////////////	
	// Error status
	case enRotatorInCheckReadyForInputError:
		NextStatus();
		break;
	case enRotatorInCheckJamForBlowError:
		NextStatus();
		break;
	case enRotatorInCheckMissingForBlowError:
		NextStatus();
		break;
	case enRotatorInTurnError:
		NextStatus();
		break;
	case enRotatorInCheckMissingForPickError:
		NextStatus();
		break;
	case enRotatorInPickError:
		NextStatus();
		break;
	case enRotatorOutCheckReadyForOutputError:
		NextStatus();
		break;
	case enRotatorOutRaminError:
		NextStatus();
		break;
	case enRotatorOutCheckJamForBlowError:
		NextStatus();
		break;
	case enRotatorOutCheckMissingForBlowError:
		NextStatus();
		break;
	case enRotatorOutTurnError:
		NextStatus();
		break;
	case enRotatorOutCheckMissingForPickError:
		NextStatus();
		break;
	case enRotatorOutPickError:
		NextStatus();
		break;
	//////////////////////////////////////////////////////////////////////////////////////////////////
	case enToHomeEndError:
		NextStatus();
		break;	
	case enToShuttleUpForOutputError:
		NextStatus();
		break;	
	case enToOutputCheckFixError:
		NextStatus();
		break;
	case enToOutputError:
		NextStatus();
		break;
	case enInputTrayMissingError:
		NextStatus();
		break;
	case enShuttleCheckJamError:
		NextStatus();
		break;
	case enShuttleCCDMatchError:
		NextStatus();
		break;
	// TS Remain IC
	case enTSRemainICCheckError:
		NextStatus();
		break;
	// Repeat Tray
	case enRepeatInToHomeEndEndError:
		NextStatus();
		break;
	case enRepeatToOutput2FullError:
		NextStatus();
		break;
	case enRepeatToOutput1FullError:
		NextStatus();
		break;
	// Remote Ctrl
	case enRemoteProtocolInHomeEndError:
		NextStatus();
		break;
	//////////////////////////////////////////////////////////////////////////////////////////////////
	
	default:
		CheckRestart();
		break;
	}
}
void CThArm::CheckRestart()
{
	// initialize
	if(m.Info.iStatus == theApp.enInitial)
		return;

	if( m.Info.iStatus == theApp.enCycle || 
		m.Info.iStatus == theApp.enOneCycle ||
		m.Info.iStatus == theApp.enManual || 
		m.Info.iStatus == theApp.enOverride )
		m_bStatus = m_bStatus & 0xfff0;
}
bool CThArm::IsPause()
{
	if((m_bStatus & 0x1) || m_bStatus == enIdle)
		return true;
	else
		return false;
}
void CThArm::NextStatus()
{
	if(m_iRunError != enCodeRunOK)
	{
		m.Info.iStatus = theApp.enUninitial;
		m.Err.Arm.Code = m_iRunError;
		
		m_bStatus = enIdle;
		m_iRunError = enCodeRunOK;
	}

	if( f.IsPause())
		m_bStatus = m_bStatus | 0x1;

	// here for change status
	switch(m_bStatus)
	{
	case enInitialize:
		f.CWinMessage( "Arm:enInitialize", theApp.enDArm );
		m_bStatus = enIdle;
		break;
	case enIdle:
		{
			if( ( m.Info.iStatus == theApp.enCycle 
				|| m.Info.iStatus == theApp.enOneCycle 
				|| m.Info.iStatus == theApp.enOverride ) 
				&& m_bInitialized )
			{
				m_bStatus = enToInput;
			}
			else
				m_bStatus = enIdle;
		}
		break;

	// Cycle
	///////////////////////////////
	// Input Get IC
	case enToInput:							// Arm XY move to Input stack
		f.CWinMessage( "Arm:enToInput", theApp.enDArm );
		{
			if( GetRemoteCoordRequest() )
			{
				if( GetRemoteCoodrClearRequest() )
				{
					// Clear Go
					SetRemoteCoordRequest( false );
					m_bStatus = enRemoteStandy;
				}
				else
				{
					CString csRemotePos = _T(""); 
					csRemotePos.Format("##### Booking> %.4d, Tray> (%d)\n", 
						m_RemoteArmTray.m_iRemoteBooking,
						m_RemoteArmTray.m_iRemoteTray );
					// Remote Go
					m_bStatus = enRemoteProtocolInput;	TRACE( csRemotePos );
				}
			}
			else if( m.Info.iStatus == theApp.enOneCycle )
			{
				m_bStatus = enCycleStandy;
			}
			else if( m.Info.iStatus == theApp.enOverride )
			{
				m_bStatus = enCycleStandy;
			}
			else if( m_bHeaterStableNeed ) //高溫模式
			{
				m_bHeaterStableNeed = false;
				m_bStatus = enHeaterWaitStableStart;
			}
			else if( m_bTSRemainICEnable )
			{
				m_bTSRemainICEnable = false;
				m_bStatus = enTSRemainICStart;
			}
			else if( m.m_RepeatTrayCtrl.m_iRepeatTrayMode == theApp.enRepeatTrayInOutCtrl )
			{
				m_bStatus = enRepeatToInput;
			}
			else if( m.InterLock.ArmEnd )
			{
				m_bStatus = enCycleStandy;
			}
			else if( m_bInTrayMissingError )
			{
				m_bInTrayMissingError = false;
				m.Err.Arm.Code = enCodeArmInputTrayMissing;
				m_bStatus = enInputTrayMissingError;
			}
			else
			{
				m_bStatus = enPickIC; 
			}
		}
		break;
	case enPickIC:							// Arm Z down to pick IC
		f.CWinMessage( "Arm:enPickIC", theApp.enDArm );
		{
			m_bStatus = enVacuumStart;
		}
		break;
	case enVacuumStart:						// Arm Z ready to turn on Vacc
		f.CWinMessage( "Arm:enVacuumStart", theApp.enDArm );
		{
			m_bStatus = enVacuum;
		}
		break;
	case enVacuum:							// Arm Z turn on Vacc
		f.CWinMessage( "Arm:enVacuum", theApp.enDArm );
		{
			m_bStatus = enVacuumEnd;
		}
		break;
	case enVacuumEnd:						// Arm Z turn on Vacc and check pick ok or not.
		f.CWinMessage( "Arm:enVacuumEnd", theApp.enDArm );
		{
			m_bStatus = enToHome;
		}
		break;
	case enToHome:							// Arm Z pick IC ok, Arm Z up to home
		f.CWinMessage( "Arm:enToHome", theApp.enDArm );
		{
			m_bStatus = enToHomeEnd;
		}
		break;
	case enToHomeEnd:						// Arm Z back to home ok, ( check go to rotator or shuttle in)
		f.CWinMessage( "Arm:enToHomeEnd", theApp.enDArm );
		{
			m_ZWithIC = CheckArmZVaccSensor();
			int iStart = ::GetTickCount();
		
			if( m_ZWithIC ) //吸到IC
			{
				//
				COleDateTime time = COleDateTime::GetCurrentTime();
				m.m_DeviceInfo.csDeviceID.Format("%d%02d%02d%02d%02d%02d",
					time.GetYear(),
					time.GetMonth(),
					time.GetDay(),
					time.GetHour(),
					time.GetMinute(),
					time.GetSecond());
				m_lArmRetryCounter = 0;
				theApp.m_InputTray.LocationDone();			// Pick OK
				m_bStatus = enRotatorInCheckSetting;
			}
			else
			{
				if( m.Setting.m_iAutoRetrySetting != 0 && 
					m_lArmRetryCounter < m.Setting.m_iAutoRetrySetting )
				{
					// Arm Z Auto Retry
					m_lArmRetryCounter++;
					m_bStatus = enToInput;
				}
				else
				{					
					if( m.Setting.m_bByPassVacc == 1 )
					{
						m_lArmRetryCounter = 0;
						theApp.m_InputTray.LocationDone();			// Pick OK
						m_bStatus = enRotatorInCheckSetting;
					}
					else if( m.TraySkip.AutoSkip == 1 )
					{
						// Ops; Pick IC Fail. But AutoSkip
						m_lArmRetryCounter = 0;
						theApp.m_InputTray.LocationDone();			// Pick Fail AutoSkip
						m_bStatus = enToInput;
					}
					else
					{
						// Ops: Pick IC Fail...
						m.Err.Arm.Code = enCodeArmPickICFail;
						m_bStatus = enToHomeEndError;
					}
				}
			}
		}
		break;
	///////////////////////////////
	// Rotator Input
	case enRotatorInCheckSetting:			// Rotator check rotator setting.
		f.CWinMessage( "Arm:enRotatorInCheckSetting", theApp.enDArm );
		{
			if( m.Setting.m_bRotatoUse == 1 && m.m_TestSetting.m_RotatorUse == 1 )
				m_bStatus = enRotatorInGoToRotator;
			else
				m_bStatus = enRotatorInEnd;
		}
		break;
	case enRotatorInRamin:					// After check rotator, Make sure rotator have no IC
		f.CWinMessage( "Arm:enRotatorInRamin", theApp.enDArm );
		{
			m_bStatus = enRotatorInBlowDown;
		}
		break;
	case enRotatorInGoToRotator:			// Arm XY move to rotator position
		f.CWinMessage( "Arm:enRotatorInGoToRotator", theApp.enDArm );
		{
			m_bStatus = enRotatorInCheckReadyForInput;
		}
		break;
	case enRotatorInCheckReadyForInput:		// Rotator turn for input IC		
		f.CWinMessage( "Arm:enRotatorInCheckReadyForInput", theApp.enDArm );
		{
			if( m.m_TestSetting.m_Angle == 1 )			// +90
			{
				if( RotatorNOK )	// Check N lmt	
					m_bStatus = enRotatorInRamin;
				else
				{
					// Ops: Rotator InPos Error Alarm it.!
					m.Err.Arm.Code = enCodeArmRotatorInPosFail;
					m_bStatus = enRotatorInCheckReadyForInputError;
				}
			}
			else if( m.m_TestSetting.m_Angle == 0 )		// -90
			{
				if( RotatorPOK )	// Check P lmt
					m_bStatus = enRotatorInBlowDown;
				else
				{
					// Ops: Rotator InPos Error Alarm it.!
					m.Err.Arm.Code = enCodeArmRotatorInPosFail;
					m_bStatus = enRotatorInCheckReadyForInputError;
				}			
			}
			else if( m.m_TestSetting.m_Angle == 2 )		// 0
			{
				if( RotatorNOK )	// Check N lmt	
					m_bStatus = enRotatorInRamin;
				else
				{
					// Ops: Rotator InPos Error Alarm it.!
					m.Err.Arm.Code = enCodeArmRotatorInPosFail;
					m_bStatus = enRotatorInCheckReadyForInputError;
				}
			}
			else 
				; // Never be here.!	
		}
		break;
	case enRotatorInBlowDown:				// Arm Z down to place IC
		f.CWinMessage( "Arm:enRotatorInBlowDown", theApp.enDArm );
		{
			m_bStatus = enRotatorInBlow;
		}
		break;
	case enRotatorInBlow:					// Arm Z turn on blow 
		f.CWinMessage( "Arm:enRotatorInBlow", theApp.enDArm );
		{
			m_bStatus = enRotatorInBlowUp;
		}
		break;
	case enRotatorInBlowUp:					// Arm Z place IC to Rotator ok, Arm Z up 
		f.CWinMessage( "Arm:enRotatorInBlowUp", theApp.enDArm );
		{
			m_bStatus = enRotatorInCheckJamForBlow;
		}
		break;
	case enRotatorInCheckJamForBlow:		// After IC Place to Rotator. Check Jam
		f.CWinMessage( "Arm:enRotatorInCheckJamForBlow", theApp.enDArm );
		{
			if( m.Setting.m_bByPassRotatorAlarm == 1 )
			{
				m_bStatus = enRotatorInTurn;
			}
			else 
			{
				if( m.m_TestSetting.m_Angle == 1 )			// +90, In N Lmt need check Jam and Missing.
				{
					if( RotatorCheckJam( &m.RemoteInStatus.RotatorICJam ) )
					{
						// Check IC Jam. ( Enable = 0, Lmt = N )
						// Ops: IC Jam
						m.Err.Arm.Code = enCodeArmInRotatorJamFail;
						m_bStatus = enRotatorInCheckJamForBlowError;
					}
					else
					{
						if( !RotatoeICExist( &m.RemoteInStatus.RotatorICMissing ) )
						{					
							// Ops: IC Missing
							m.Err.Arm.Code = enCodeArmInRotatorICMissing;
							m_bStatus = enRotatorInCheckMissingForBlowError;
						}
						else
							m_bStatus = enRotatorInTurn;
					}

				}
				else if( m.m_TestSetting.m_Angle == 0 )			// -90
				{
					m_bStatus = enRotatorInTurn;
				}
				else if( m.m_TestSetting.m_Angle == 2 )			// 0
				{			
					m_bStatus = enRotatorInTurn;
				}
			}			
		}
		break;
	case enRotatorInTurn:					// Rotator change IC pin1 
		f.CWinMessage( "Arm:enRotatorInTurn", theApp.enDArm );
		{
			if( m.m_TestSetting.m_Angle == 1 )				// +90
			{
				if( RotatorPOK )
					m_bStatus = enRotatorInCheckJamForPick;
				else
				{
					m.Err.Arm.Code = enCodeArmRotatorInPosFail;
					m_bStatus = enRotatorInTurnError;
				}
			}
			else if( m.m_TestSetting.m_Angle == 0 )			// -90
			{
				if( RotatorNOK )
					m_bStatus = enRotatorInCheckJamForPick;
				else
				{
					m.Err.Arm.Code = enCodeArmRotatorInPosFail;
					m_bStatus = enRotatorInTurnError;
				}				
			}
			else if( m.m_TestSetting.m_Angle == 2 )			// 0 Pre-Guide
			{
				// 因為不旋轉, 所以也不檢查到位
				m_bStatus = enRotatorInCheckJamForPick;							
			}
		}
		break;
	case enRotatorInCheckJamForPick:		// Before Arm Z Pick IC	check Jam
		f.CWinMessage( "Arm:enRotatorInCheckJamForPick", theApp.enDArm );
		{
			if( m.Setting.m_bByPassRotatorAlarm == 1 )
			{
				m_bStatus = enRotatorInPickDown;				
			}
			else if( m.m_TestSetting.m_Angle == 1 )			// +90
			{
				m_bStatus = enRotatorInPickDown;
			}
			else if( m.m_TestSetting.m_Angle == 0 )			// -90
			{
				if( RotatorCheckJam( &m.RemoteInStatus.RotatorICJam ) )
				{
					// Ops: IC Jam
					m.Err.Arm.Code = enCodeArmInRotatorJamFail;
					m_bStatus = enRotatorInCheckMissingForPickError;
				}
				else
				{
					if( !RotatoeICExist( &m.RemoteInStatus.RotatorICMissing ) )
					{
						// Ops: IC Missing
						m.Err.Arm.Code = enCodeArmInRotatorICMissing;
						m_bStatus = enRotatorInCheckMissingForPickError;
					}
					else
						m_bStatus = enRotatorInPickDown;
				}
			}
			else if( m.m_TestSetting.m_Angle == 2 )			// 0 Pre-Guide
			{
				m_bStatus = enRotatorInPickDown;
			}
		}
		break;
	case enRotatorInPickDown:				// Rotator change ok, Arm Z down to pick IC
		f.CWinMessage( "Arm:enRotatorInPickDown", theApp.enDArm );
		{
			m_bStatus = enRotatorInPick;
		}
		break;
	case enRotatorInPick:					// Arm Z Vacc turn on
		f.CWinMessage( "Arm:enRotatorInPick", theApp.enDArm );
		{
			m_bStatus = enRotatorInPickUp;
		}
		break;
	case enRotatorInPickUp:					// Arm Z up 
		f.CWinMessage( "Arm:enRotatorInPickUp", theApp.enDArm );
		{
			m_ZWithIC = CheckArmZVaccSensor();
			// 避免假真空現象

			if( m_ZWithIC )
			{
				m_bStatus = enRotatorInEnd;	
			}
			else
			{
				if( m.Setting.m_bByPassVacc == 1 )
				{
					m_bStatus = enRotatorInEnd;
				}
				else
				{
					// Ops : Pick IC from Rotator Fail.! Alarm it.!
					m.Err.Arm.Code = enCodeArmPickICFailWithRotator;
					m_bStatus = enRotatorInPickError;
				}
			}
		}
		break;
	case enRotatorInEnd:					// Rorator In complete. ( IC in ArmZ, ok go to shuttle )
		f.CWinMessage( "Arm:enRotatorInEnd", theApp.enDArm );
		{
//			m_bStatus = enTestSiteUpSafe;
			m_bStatus = enToShuttle;
		}
		break;
	case enRotatorInPickReset:
		f.CWinMessage( "Arm:enRotatorInPickReset", theApp.enDArm );
		{
			m_bStatus = enRotatorInPickDown;
		}
		break;
	//
	case enToShuttle:						// Arm XY move to shuttle 
		f.CWinMessage( "Arm:enToShuttle", theApp.enDArm );
		{
			if( m.InterLock.ShuttleHome )
				m_bStatus = enShuttlePlaceIC;
		}
		break;
	case enShuttlePlaceIC:					// Arm Z down to place IC
		f.CWinMessage( "Arm:enShuttlePlaceIC", theApp.enDArm );
		{
			m_bStatus = enShuttleBlow;
		}
		break;
	case enShuttleBlow:						// Arm Z turn on the blow
		f.CWinMessage( "Arm:enShuttleBlow", theApp.enDArm );
		{
			m_bStatus = enShuttleUp;
		}
		break;
	case enShuttleUp:						// Arm Z up
		f.CWinMessage( "Arm:enShuttleUp", theApp.enDArm );
		{
			theApp.m_tInserter.TestSiteLog = theApp.m_tArm.ArmLog;
			theApp.m_tArm.ClearArmLog();			

			m_bStatus = enShuttleCheckJam;
		}
		break;
	case enShuttleCheckJam:
		f.CWinMessage( "Arm:enShuttleCheckJam", theApp.enDArm );
		{
			if( CheckArmJam() )
			{
				if( m.Setting.m_bByPassShuttleAlarm )
				{
					// Jam Fail but bypass
					m_bStatus = enShuttleCheckJamOK;
				}
				else
				{
					// Jam Fail
					m_bStatus = enShuttleJamGoStandy;
				}
			}
			else
			{
				// No Jam
				m_bStatus = enShuttleCheckJamOK;
			}
		}
		break;
	case enShuttleCheckJamOK:
		f.CWinMessage( "Arm:enShuttleCheckJamOK", theApp.enDArm );
		{
			if( m.Setting.m_bEnableCCDPin1 == 1 && 
				m.m_TestSetting.m_CCDUse == 1 )
			{
				m_bStatus = enShuttleCCDPin1Start;
			}
			else if ( m.Setting.m_bEnableCCDLogICImage == 1 && 
				m.m_ArmLogICImage.bEnableArmLogICImage == 1  )
			{
				m_bStatus = enArmLogImageStart;
			}
			else
			{
				m_bStatus = enToStandyStart;		
			}
		}
		break;
	case enShuttleDoubleCheckJam:
		f.CWinMessage( "Arm:enShuttleDoubleCheckJam", theApp.enDArm );
		{
			if( CheckArmJam() )
			{
				if( m.Setting.m_bByPassShuttleAlarm )
				{
					// Jam Fail but bypass
					m_bStatus = enToInput;
				}
				else
				{
					// Jam Fail
					m_bStatus = enShuttleJamGoStandy;
				}
			}
			else
			{
				// No Jam OK
				m_bStatus = enToInput;
			}			
		}
		break;
	/*
	case enShuttleDoubleCheckJam:
		f.CWinMessage( "Arm:enShuttleDoubleCheckJam", theApp.enDArm );
		{
			if( CheckArmJam() )
			{
				if( m.Setting.m_bByPassShuttleAlarm )
				{
					// Jam Fail but bypass
					m_bStatus = enToInput;
				}
				else
				{
					// Jam Fail
					m_bStatus = enShuttleJamGoStandy;
				}
			}
			else
			{
				if( GetRemoteCoordRequest() )
				{
					// Remote, No Jam OK
					m_bStatus = enRemoteStandy;
				}
				else
				{
					// No Jam OK
					m_bStatus = enToInput;
				}
			}			
		}
		break;
	*/
	case enShuttleJamGoStandy:
		f.CWinMessage( "Arm:enShuttleJamGoStandy", theApp.enDArm );
		{
			m.Err.Arm.Code = enCodeArmInputShuttleJam;
			m_bStatus = enShuttleCheckJamError;		
		}
		break;

	///////////////////////////////
	// CCD Pin1 
	case enShuttleCCDPin1Start:				// CCD Pin1
		f.CWinMessage( "Arm:enShuttleCCDPin1Start", theApp.enDArm );
		{
			bCCDPin1MatchOK = true;
			m_bStatus = enShuttleCCDPin1Grab;
		}
		break;
	case enShuttleCCDPin1Grab:				// CCD Grab
		f.CWinMessage( "Arm:enShuttleCCDPin1Grab", theApp.enDArm );
		{
			
			m_bStatus = enShuttleCCDMatch;
		}
		break;
	case enShuttleCCDMatch:					// CCD Grab Match
		f.CWinMessage( "Arm:enShuttleCCDMatch", theApp.enDArm );
		{
			//比對Jerome
			if( bCCDPin1MatchOK )
				m_bStatus = enShuttleCCDMatchEnd;
			else
			{
				// Ops: CCD Match Fail
				m.Err.Arm.Code = enCodeArmCCDMatchFail;
				m_bStatus = enShuttleCCDMatchError;
			}
		}
		break;
	case enShuttleCCDMatchEnd:				// CCD Grab Match complete.
		f.CWinMessage( "Arm:enShuttleCCDMatchEnd", theApp.enDArm );
		{
			if( m.Setting.m_bEnableCCDLogICImage == 1 && 
				m.m_ArmLogICImage.bEnableArmLogICImage == 1 )
			{
				// Before Testing, Take a picture
				m_bStatus = enArmLogImageStart;
			}
			else
				m_bStatus = enToStandyStart;
		}
		break;

	///////////////////////////////
	// CCD Arm Log Image
	case enArmLogImageStart:				// Image Log Arm
		f.CWinMessage( "Arm:enArmLogImageStart", theApp.enDArm );
		{
			m_bStatus = enArmLogImageGrabMove;
		}
		break;
	case enArmLogImageGrabMove:				// Image Log Arm, Ready to grab image
		f.CWinMessage( "Arm:enArmLogImageGrabMove", theApp.enDArm );
		{
			m_bStatus = enArmLogImageStable;
		}
		break;
	case enArmLogImageStable:				// Image Log Arm, Wait Motor Stable
		f.CWinMessage( "Arm:enArmLogImageStable", theApp.enDArm );
		{
			m_bStatus = enArmLogImageDirectory;
		}
		break;
	case enArmLogImageDirectory:			// Image Log Arm, Is Directory Exist
		f.CWinMessage( "Arm:enArmLogImageDirectory", theApp.enDArm );
		{
			m_bStatus = enArmLogImageGrab;		
		}		
		break;
	case enArmLogImageGrab:					// Image Log Arm, Ready to grab image
		f.CWinMessage( "Arm:enArmLogImageGrab", theApp.enDArm );
		{
			m_bStatus = enArmLogImageSaveIage;
		}
		break;
	case enArmLogImageSaveIage:				// Image Log Arm, Save the Image
		f.CWinMessage( "Arm:enArmLogImageSaveIage", theApp.enDArm );
		{
			m_bStatus = enArmLogImageWaitStable;
		}
		break;
	case enArmLogImageWaitStable:				// Image Log Arm, Wait Motor Stable
		f.CWinMessage( "Arm:enArmLogImageWaitStable", theApp.enDArm );
		{
			m_bStatus = enArmLogImageEnd;
		}
		break;
	case enArmLogImageEnd:					// Image Log Arm, Save the Image
		f.CWinMessage( "Arm:enArmLogImageEnd", theApp.enDArm );
		{
			m_bStatus = enToStandyStart;
		}
		break;
	///////////////////////////////
	// Standy 
	case enToStandyStart:
		{
			m.InterLock.ShuttleInputICOK = true;
			m.InterLock.ShuttleWithIC = true;
			m_bStatus = enToStandy;
		}
		break;
	case enToStandy:						// Arm XY move to standy 
		f.CWinMessage( "Arm:enToStandy", theApp.enDArm );
		{
			m_bStatus = enToStandyEnd;
		}
		break;
	case enToStandyEnd:						// Arm XY move to standy OK
		f.CWinMessage( "Arm:enToStandyEnd", theApp.enDArm );
		{
//			m.InterLock.ShuttleInputICOK = true;
//			m.InterLock.ShuttleWithIC = true;
			m_bStatus = enToStandyWait;
		}
		break;
	case enToStandyWait:
		f.CWinMessage( "Arm:enToStandyWait", theApp.enDArm );
		{
			if( m.InterLock.ShuttleOutputICOK )
			{
				m.InterLock.ShuttleOutputICOK = false;
				m_bStatus = enToShuttleOutput;
			}
			else if( m.InterLock.ShuttleResetInput )
			{
				m.InterLock.ShuttleResetInput = false;
				m_bStatus = enToInput;
			}
			else
				;
		}
		break;

	///////////////////////////////
	// Rotator Output
	case enRotatorOutCheckSetting:			// Rotator check rotator setting.
		f.CWinMessage( "Arm:enRotatorOutCheckSetting", theApp.enDArm );
		{
			if( m.Setting.m_bRotatoUse == 1 && m.m_TestSetting.m_RotatorUse == 1 )
			{			
				// Pre-Guide
				// 如果角度是 0 當作 Pre Guide 來用. 那麼就不回到 Rotator 旋轉了
				// 直接到 Output 
				if( m.m_TestSetting.m_Angle == 2 )
					m_bStatus = enRotatorOutPickEnd;
				else
					m_bStatus = enRotatorOutGotoRotator;
			}
			else
			{
				// 沒有使用 Rotator
				m_bStatus = enRotatorOutPickEnd;
			}
		}
		break;
	case enRotatorOutRamin:					// After check rotator, Make sure rotator have no IC
		f.CWinMessage( "Arm:enRotatorOutRamin", theApp.enDArm );
		{

			if( m.Setting.m_bByPassRotatorAlarm == 1 )
			{
				m_bStatus = enRotatorOutBlowDown;
			}
			else if( RotatoeICExist( &m.RemoteInStatus.RotatorICMissing ) )
			{
				// Ops : Rotator detect IC exist, Before Place IC. Alarm it.!
				m.Err.Arm.Code = enCodeArmOutRotatorRemainFail; 
				m_bStatus = enRotatorOutRaminError;
			}
			else
				m_bStatus = enRotatorOutBlowDown;

		}
		break;
	case enRotatorOutGotoRotator:			// Arm XY move to rotator
		f.CWinMessage( "Arm:enRotatorOutGotoRotator", theApp.enDArm );
		{
			m_bStatus = enRotatorOutCheckReadyForOutput;
		}
		break;
	case enRotatorOutCheckReadyForOutput:	// Turn the Rotator, then Arm can place IC to rotator
		f.CWinMessage( "Arm:enRotatorOutCheckReadyForOutput", theApp.enDArm );
		{
			if( m.m_TestSetting.m_Angle == 1 )		// +90
			{
				// Check nlmt
				if( RotatorPOK )
					m_bStatus = enRotatorOutBlowDown;
				else
				{
					// Ops: Rotator InPos Error Alarm it.!
					m.Err.Arm.Code = enCodeArmRotatorInPosFail;
					m_bStatus = enRotatorOutCheckReadyForOutputError;
				}				
			}
			else if( m.m_TestSetting.m_Angle == 0 )	// -90
			{
				// Check plmt
				if( RotatorNOK )
					m_bStatus = enRotatorOutRamin;
				else
				{
					// Ops: Rotator InPos Error Alarm it.!
					m.Err.Arm.Code = enCodeArmRotatorInPosFail;
					m_bStatus = enRotatorOutCheckReadyForOutputError;
				}				
			}
			else
				; // Nerver
		}
		break;
	case enRotatorOutBlowDown:				// Arm Z down to place IC
		f.CWinMessage( "Arm:enRotatorOutBlowDown", theApp.enDArm );
		{
			m_bStatus = enRotatorOutBlow;
		}
		break;
	case enRotatorOutBlow:					// Arm Z down and turn on the blow 
		f.CWinMessage( "Arm:enRotatorOutBlow", theApp.enDArm );
		{
			m_bStatus = enRotatorOutBlowUp;
		}
		break;
	case enRotatorOutBlowUp:				// Arm Z up
		f.CWinMessage( "Arm:enRotatorOutBlowUp", theApp.enDArm );
		{
			m_bStatus = enRotatorOutCheckJamForBlow;						
		}
		break;
	case enRotatorOutCheckJamForBlow:		// After place the IC, check Jam
		f.CWinMessage( "Arm:enRotatorOutCheckJamForBlow", theApp.enDArm );
		{
			if( m.Setting.m_bByPassRotatorAlarm == 1 )
			{
				m_bStatus = enRotatorOutTurn;
			}
			else
			{
				if( m.m_TestSetting.m_Angle == 1 )		// +90
				{
					m_bStatus = enRotatorOutTurn;
				}
				else if( m.m_TestSetting.m_Angle == 0 )	// -90
				{

					if( RotatorCheckJam( &m.RemoteInStatus.RotatorICJam ) )
					{
						// Ops: IC Jam
						m.Err.Arm.Code = enCodeArmOutRotatorJamFail;
						m_bStatus = enRotatorOutCheckJamForBlowError;
					}
					else
					{
						if( !RotatoeICExist( &m.RemoteInStatus.RotatorICMissing ) )
						{
							// Ops: IC Missing
							m.Err.Arm.Code = enCodeArmOutRotatorICMissing;
							m_bStatus = enRotatorOutCheckMissingForBlowError;
						}
						else
							m_bStatus = enRotatorOutTurn;
					}
				}
			}
		}
		break;
	case enRotatorOutTurn:					// Turn the rotator
		f.CWinMessage( "Arm:enRotatorOutTurn", theApp.enDArm );
		{
			if( m.m_TestSetting.m_Angle == 1 )			// +90
			{
				// Check plmt
				if(RotatorNOK)
					m_bStatus = enRotatorOutCheckJamForPick;
				else
				{
					// Ops: Rotator InPos Error Alarm it.!
					m.Err.Arm.Code = enCodeArmRotatorInPosFail;
					m_bStatus = enRotatorOutTurnError;
				}
			}
			else if( m.m_TestSetting.m_Angle == 0 )		// -90
			{
				// Check nlmt
				if(RotatorPOK)
					m_bStatus = enRotatorOutCheckJamForPick;									
				else
				{
					// Ops: Rotator InPos Error Alarm it.!
					m.Err.Arm.Code = enCodeArmRotatorInPosFail;
					m_bStatus = enRotatorOutTurnError;
				}
			}
		}
		break;
	case enRotatorOutCheckJamForPick:		// Before Arm Z Pick IC	check Jam
		f.CWinMessage( "Arm:enRotatorOutCheckJamForPick", theApp.enDArm );
		{
			if( m.Setting.m_bByPassRotatorAlarm == 1 )
			{
				m_bStatus = enRotatorOutPickDown;
			}
			else if( m.m_TestSetting.m_Angle == 1 )		// +90
			{	
				if( RotatorCheckJam( &m.RemoteInStatus.RotatorICJam ) )
				{
					// Ops: IC Jam
					m.Err.Arm.Code = enCodeArmOutRotatorJamFail;
					m_bStatus = enRotatorOutCheckMissingForPickError;
				}
				else 
				{
					if( !RotatoeICExist( &m.RemoteInStatus.RotatorICMissing ) )
					{
						// Ops: IC Missing.
						m.Err.Arm.Code = enCodeArmOutRotatorICMissing;
						m_bStatus = enRotatorOutCheckMissingForPickError;
					}
					else
						m_bStatus = enRotatorOutPickDown;
				}
			}
			else if( m.m_TestSetting.m_Angle == 0 )		// -90
			{
				m_bStatus = enRotatorOutPickDown;
			}
		}
		break;
	case enRotatorOutPickDown:				// Arm Z down to pick IC
		f.CWinMessage( "Arm:enRotatorOutPickDown", theApp.enDArm );
		{
			m_bStatus = enRotatorOutPick;
		}
		break;
	case enRotatorOutPick:					// Arm Z turn on the Vacuum
		f.CWinMessage( "Arm:enRotatorOutPick", theApp.enDArm );
		{
			m_bStatus = enRotatorOutPickUp;
		}
		break;
	case enRotatorOutPickUp:				// Arm Z up
		f.CWinMessage( "Arm:enRotatorOutPickUp", theApp.enDArm );
		{
			m_ZWithIC = CheckArmZVaccSensor();
			// 避免假真空現象

			if( m_ZWithIC )
			{
				m_bStatus = enRotatorOutPickEnd;				
			}
			else
			{
				// Ops: Pick IC From Rotator Fail.!
				if( m.Setting.m_bByPassVacc == 1 )
				{		
					m_bStatus = enRotatorOutPickEnd;					
				}
				else
				{
					m.Err.Arm.Code = enCodeArmPickICFailWithRotator;
					m_bStatus = enRotatorOutPickError;
				}
			}
		}
		break;
	case enRotatorOutPickEnd:				// Rotator Out complete ( IC in ArmZ, ok go to bining )
		f.CWinMessage( "Arm:enRotatorOutPickEnd", theApp.enDArm );
		{
			if( m.RemoteInterlock.IsRemoteControlMode == true && 
				m.RemoteInterlock.ReleaseIC ==  true )
			{
				m_bStatus = enRemoteControlToInput;
			}
			// Remote SLT
			if( GetRemoteCoordRequest() )
			{
				m_bStatus = enRemoteProtocolOutput;
			}
			// Repeat Tray 
			else if( m.m_RepeatTrayCtrl.m_iRepeatTrayMode == theApp.enRepeatTrayInOutCtrl )
			{
				m_bStatus = enRepeatToOutput;
			}
			else
				m_bStatus = enToOutputCheckFix;
		}
		break;
	case enRotatorOutputReset:
		f.CWinMessage( "Arm:enRotatorOutputReset", theApp.enDArm );
		{
			m_bStatus = enRotatorOutPickDown;
		}
		break;
	///////////////////////////////
	// Shuttle (Output)
	case enToShuttleOutput:					// Arm XY move to shuttle 
		f.CWinMessage( "Arm:enToShuttleOutput", theApp.enDArm );
		{
			if( m.InterLock.ShuttleHome )
				m_bStatus = enToShuttlePick;
		}
		break;
	case enToShuttlePick:					// Arm Z down to pick
		f.CWinMessage( "Arm:enToShuttlePick", theApp.enDArm );
		{
			m_bStatus = enToShuttlePickVaccStart;
		}
		break;
	case enToShuttlePickVaccStart:			// Arm Z ready to turn on the vacc
		f.CWinMessage( "Arm:enToShuttlePickVaccStart", theApp.enDArm );
		{
			m_bStatus = enToShuttlePickVacc;
		}
		break;
	case enToShuttlePickVacc:				// Arm Z turn on the vacc
		f.CWinMessage( "Arm:enToShuttlePickVacc", theApp.enDArm );
		{
			m_bStatus = enToShuttlePickVaccEnd;
		}
		break;
	case enToShuttlePickVaccEnd:			// Arm Z vacc end
		f.CWinMessage( "Arm:enToShuttlePickVaccEnd", theApp.enDArm );
		{
			m_bStatus = enToShuttleUpForOutput;
		}
		break;
	/*
	case enToShuttleUpForOutput:			// Arm Z up for output
		f.CWinMessage( "Arm:enToShuttleUpForOutput", theApp.enDArm );
		{
			m_ZWithIC = CheckArmZVaccSensor();

			theApp.m_tArm.ArmLog = theApp.m_tInserter.TestSiteLog ;
			theApp.m_tInserter.ClearTestSiteLog();

			if( m_ZWithIC )
			{
				// Shuttle Pick IC OK..
				m_bStatus = enRotatorOutCheckSetting;
			}
			else
			{
				if( m.Setting.m_bByPassVacc == 1 )
				{
					// Shuttle Pick IC OK..
					m_bStatus = enRotatorOutCheckSetting;
				}
				else
				{					
					// Shuttle Pick IC Fail.
					m.Err.Arm.Code = enCodeArmPickICFailWithShuttle;
					m_bStatus = enToShuttleUpForOutputError;
				}
			}
		}
		break;
	*/
	case enToShuttleUpForOutput:			// Arm Z up for output
		f.CWinMessage( "Arm:enToShuttleUpForOutput", theApp.enDArm );
		{
			m_ZWithIC = CheckArmZVaccSensor();

			if( m_ZWithIC )
			{
				theApp.m_tArm.ArmLog = theApp.m_tInserter.TestSiteLog;
				theApp.m_tInserter.ClearTestSiteLog();
				m.m_DeviceInfo.csDeviceID = _T("");
				m_lArmRetryCounter = 0;
				// Shuttle Pick IC OK..
				m_bStatus = enRotatorOutCheckSetting;
			}
			else
			{
				if( m.Setting.m_bByPassVacc == 1 )
				{
					theApp.m_tArm.ArmLog = theApp.m_tInserter.TestSiteLog;
					theApp.m_tInserter.ClearTestSiteLog();

					// Shuttle Pick IC OK..
					m_bStatus = enRotatorOutCheckSetting;
				}
				else
				{					
					// Shuttle Pick IC Fail.
					m.Err.Arm.Code = enCodeArmPickICFailWithShuttle;
					m_bStatus = enToShuttleUpForOutputError;
				}
			}
		}
		break;

	///////////////////////////////
	// Output Place IC
	// Bin
	case enToOutputCheckFix:				// Check Fix1
		f.CWinMessage( "Arm:enToOutputCheckFix", theApp.enDArm );
		{
			if( CheckFixExist() )
				m_bStatus = enToOutput;
			else
			{
				if( m.Setting.m_bByPassTrayInPos == 1 )
				{
					m_bStatus = enToOutput;
				}
				else
				{
					// Ops: Output Fix1 Fail...(Missing)
					m.Err.Arm.Code = enCodeArmFix1TrayMissing;
					m_bStatus = enToOutputCheckFixError;
				}
			}
		}
		break;
	case enToOutput:						// Arm XY Move to Output area, ready to place IC
		f.CWinMessage( "Arm:enToOutput", theApp.enDArm );
		{
			if(!m_bFix1TrayFull)
				m_bStatus = enToOutputPlaceIC;
			else
			{
				// Ops: Fix1 Tray Full.
				m_bFix1TrayFull = false;
				m.Err.Arm.Code = enCodeArmFix1TrayFull;
				m_bStatus = enToOutputError;
			}
		}
		break;
	case enToOutputPlaceIC:					// Arm Z down to place IC
		f.CWinMessage( "Arm:enToOutputPlaceIC", theApp.enDArm );
		{
			m_bStatus = enToOutputPlaceBlow;
		}
		break;
	case enToOutputPlaceBlow:				// Arm Z turn on the Blow
		f.CWinMessage( "Arm:enToOutputPlaceBlow", theApp.enDArm );
		{
			m_bStatus = enToOutputHome;
		}
		break;
	case enToOutputHome:					// Arm up to home
		f.CWinMessage( "Arm:enToOutputHome", theApp.enDArm );
		{
			// Tray Map
			CPoint p = theApp.m_OutputTray.GetIndex();
			f.AddTrayMap( theApp.enBin1, 
				theApp.m_tArm.ArmLog.csCode, p, 0, 0.0 );
			f.SaveTrayMap();

			// Output Yield 
			InsertOutputYield( theApp.m_tArm.ArmLog.csCode );

			//
			ConventSiteCounter(0);

			//
			m_bStatus = enToOutputHomeEnd;
		}
		break;
	case enToOutputHomeEnd:					// Arm up to home OK. ready to input again.
		f.CWinMessage( "Arm:enToOutputHomeEnd", theApp.enDArm );
		{
			m_bStatus = enToInput;
		}
		break;
	case enToOutputChangeTray:				// Change Tray, Clear Fix Tray
		{
			// Clear data
			theApp.m_OutputTray.ChangeTray();

			// date be clear, 
			m_bStatus = enToOutput;
		}
		break;
	///////////////////////////////
	// Remote Control
	case enRemoteControlToInput:			// To Input Place IC	
		f.CWinMessage( "Arm:enRemoteControlToInput", theApp.enDArm );
		{
			m_bStatus = enRemoteControlPlaceIC;
		}
		break;
	case enRemoteControlPlaceIC:			// Arm Z down to place IC
		f.CWinMessage( "Arm:enRemoteControlPlaceIC", theApp.enDArm );
		{
			m_bStatus = enRemoteControlBlow;
		}
		break;
	case enRemoteControlBlow:				// Blow		
		f.CWinMessage( "Arm:enRemoteControlBlow", theApp.enDArm );
		{
			m_bStatus = enRemoteControlHome;
		}
		break;
	case enRemoteControlHome:				// Home		
		f.CWinMessage( "Arm:enRemoteControlHome", theApp.enDArm );
		{
			m_bStatus = enRemoteControlHomeEnd;
		}
		break;
	case enRemoteControlHomeEnd:				// Home		
		f.CWinMessage( "Arm:enRemoteControlHomeEnd", theApp.enDArm );
		{
			RemoteControlMessageArmReady();

			f.CWinMessage( "Arm:IC Place OK. Wait for Pick IC", theApp.enDArm );

			m_bStatus = enRemoteControlWaitPick;
		}
		break;

	case enRemoteControlWaitPick:
//		f.CWinMessage( "Arm:enRemoteControlWaitPick", theApp.enDArm );
		{
			if( m.RemoteInterlock.PickIC == true )
			{
				m_bStatus = enToInput;
			}
			else
				; // Wait here for user press pick IC
		}
		break;

	///////////////////////////////	
	// Cycle Finish
	case enCycleStandy:
		f.CWinMessage( "Arm:enCycleStandy", theApp.enDArm );
		{
			m_bStatus = enCycleEnd;
		}
		break;
	case enCycleEnd:						// Cycle Finish
		f.CWinMessage( "Arm:enCycleEnd", theApp.enDArm );
		{
			//
			AutoInputTray();

			//
			f.CycleFinish();

			//
			f.CycleFinishDone();

			//
			f.CycleRepeatFinishDone();
			
			//
			m_bStatus = enIdle;
		}
		break;
	///////////////////////////////
	// Heater
	case enHeaterWaitStableStart:		// Heater Wait Stable Start
		f.CWinMessage( "Arm:enHeaterWaitStableStart", theApp.enDArm );
		{
			m_bStatus = enHeaterWaitTemper;
		}
		break;
	case enHeaterWaitTemper:			// Heater Wait Stable
		f.CWinMessage( "Arm:enHeaterWaitTemper", theApp.enDArm );
		{
			if( m_bWaitHeaterOK )
			{
				m_bWaitHeaterOK = false;
				m.m_heaterCtrl.m_bHeaterTempOK = true;
				m_bStatus = enHeaterWaitStable;
			}
			else
				m_bStatus = enToInput;
		}
		break;
	case enHeaterWaitStable:
		f.CWinMessage( "Arm:enHeaterWaitStable", theApp.enDArm );
		{		
			if( m_bWaitHeaterStableOK )
			{
				m_bWaitHeaterStableOK = false;
				m_bStatus = enHeaterWaitStableEnd;
			}
			else 
				m_bStatus = enToInput;
		}
		break;
	case enHeaterWaitStableEnd:			// Heater Wait Stable end
		f.CWinMessage( "Arm:enHeaterWaitStableEnd", theApp.enDArm );
		{
			m_bStatus = enToInput;
		}
		break;
	///////////////////////////////
	// TS Remain IC
	case enTSRemainICStart:					// TS Remain IC Start
		f.CWinMessage( "Arm:enTSRemainICStart", theApp.enDArm );
		{
			m_bStatus = enTSRemainICContactHome;
		}
		break;
	case enTSRemainICContactHome:			// TS Remain IC Chamber Contact Move to Home
		f.CWinMessage( "Arm:enTSRemainICContactHome", theApp.enDArm );
		{
			m_bStatus = enTSRemainICDryHome;
		}
		break;
	case enTSRemainICDryHome:				// TS Remain IC Dry Shuttle Move to Home
		f.CWinMessage( "Arm:enTSRemainICDryHome", theApp.enDArm );
		{
			m_bStatus = enTSRemainICTSDown;
		}
		break;
	case enTSRemainICTSDown:				// TS Remain IC TS Down 
		f.CWinMessage( "Arm:enTSRemainICTSDown", theApp.enDArm );
		{
			m_bStatus = enTSRemainICTSVaccOn;
		}
		break;
	case enTSRemainICTSVaccOn:				// TS Remain IC Turn IC
		f.CWinMessage( "Arm:enTSRemainICTSVaccOn", theApp.enDArm );
		{
			m_bStatus = enTSRemainICTSVaccEnd;
		}
		break;
	case enTSRemainICTSVaccEnd:				// TS Remain IC Vacc End ( Check do we need to turn off Vacc )
		f.CWinMessage( "Arm:enTSRemainICTSVaccEnd", theApp.enDArm );
		{
			m_bStatus = enTSRemainICTSUp;
		}
		break;
	case enTSRemainICTSUp:					// TS Remain IC TS Up
		f.CWinMessage( "Arm:enTSRemainICTSUp", theApp.enDArm );
		{
			m_bStatus = enTSRemainICCheck;
		}
		break;
	case enTSRemainICCheck:					// TS Remain IC Check Pass Or Fail
		f.CWinMessage( "Arm:enTSRemainICCheck", theApp.enDArm );
		{			
			if( TSRemainICDoubleCheck( &m.InStatus.TestSiteZVaccSensor ) )
				m_TSRemainWithIC = true;
			else
				m_TSRemainWithIC = false;

			// 如果是 Demo...
			if( m.Setting.m_bByPassTestVacc )
				m_TSRemainWithIC = false;

			if( m_TSRemainWithIC )
			{
				// Error 
				m.Err.Arm.Code = enCodeTSRemainICFail;
				m_bStatus = enTSRemainICCheckError;
			}
			else
				m_bStatus = enTSRemainICEnd;
		}
		break;
	case enTSRemainICEnd:					// TS Remain IC End
		f.CWinMessage( "Arm:enTSRemainICEnd", theApp.enDArm );
		{
			m_bStatus = enToInput;
		}
		break;

	///////////////////////////////	
	// Repeat Tray / Input / Output Ctrl
	// Get IC
	case enRepeatToInput:
		f.CWinMessage( "Arm:enRepeatToInput", theApp.enDArm );
		{
			if( m.Info.iStatus == theApp.enOneCycle )
			{
				m_bStatus = enRepeatCycleStandy;
			}
			else if( m.Info.iStatus == theApp.enOverride )
			{
				m_bStatus = enRepeatCycleStandy;
			}
			else if( bRepeatInputEmpty )
			{
				// 換方向
				bRepeatInputEmpty = false;
				m.m_RepeatTrayDATA.m_NowCount++;
				f.SaveNowMoation();

				// Reset InputTrayStatus - Pass/Fail Mode
				ResetInputStatus();

				// updata run page information
				m.Page.Run.UpdataRepeatInformation();

				//
				m_bStatus = enRepeatCheckComplete;
			}
			else
				m_bStatus = enRepeatPickIC;
		}
		break;
	case enRepeatPickIC:
		f.CWinMessage( "Arm:enRepeatPickIC", theApp.enDArm );
		{
			m_bStatus = enRepeatVacc;
		}
		break;
	case enRepeatVacc:
		f.CWinMessage( "Arm:enRepeatVacc", theApp.enDArm );
		{
			m_bStatus = enRepeatVaccEnd;
		}
		break;
	case enRepeatVaccEnd:
		f.CWinMessage( "Arm:enRepeatVaccEnd", theApp.enDArm );
		{
			m_bStatus = enRepeatInToHome;
		}
		break;
	case enRepeatInToHome:
		f.CWinMessage( "Arm:enRepeatInToHome", theApp.enDArm );
		{
			m_bStatus = enRepeatInToHomeEnd;
		}
		break;
	case enRepeatInToHomeEnd:
		f.CWinMessage( "Arm:enRepeatInToHomeEnd", theApp.enDArm );
		{
			m_bStatus = enRepeatInToHomeEndEnd;
		}
		break;
	case enRepeatInToHomeEndEnd: 
		f.CWinMessage( "Arm:enRepeatInToHomeEnd", theApp.enDArm );
		{
			m_ZWithIC = CheckArmZVaccSensor();	
			if( m_ZWithIC )
			{
				COleDateTime time = COleDateTime::GetCurrentTime();
				m.m_DeviceInfo.csDeviceID.Format("%d%02d%02d%02d%02d%02d",
					time.GetYear(),
					time.GetMonth(),
					time.GetDay(),
					time.GetHour(),
					time.GetMinute(),
					time.GetSecond());
				m_lArmRetryCounter = 0;
				RepeatMationInputDone();
				m_bStatus = enRotatorInCheckSetting;
			}
			else
			{
				if( m.Setting.m_bByPassVacc == 1 )
				{
					RepeatMationInputDone();
					m_bStatus = enRotatorInCheckSetting;
				}
				else
				{
					// Auto Retry
					if( m.Setting.m_iAutoRetrySetting != 0 && 
						m_lArmRetryCounter < m.Setting.m_iAutoRetrySetting )
					{
						m_lArmRetryCounter++;
						m_bStatus = enRepeatToInput;
					}
					// Auto Skip
					else if( m.TraySkip.AutoSkip == 1 )
					{
						m_lArmRetryCounter = 0;
						RepeatMationInputDone();
						m_bStatus = enRepeatToInput;
					}
					// Pick Error
					else
					{
						// Ops: Repeat Tray Pick IC Fail
						m.Err.Arm.Code = enCodeArmPickICFail;
						m_bStatus = enRepeatInToHomeEndEndError;
					}
				}
			}
		}
		break;

	// Put IC
	// 1.0Ah
	// Remove this and re-build new one
	/*
	case enRepeatToOutput:
		f.CWinMessage( "Arm:enRepeatToOutput", theApp.enDArm );
		{
			m_bStatus = enRepeatPlacIC;
		}
		break;
	*/
	case enRepeatToOutput:
		f.CWinMessage( "Arm:enRepeatToOutput", theApp.enDArm );
		{
			if( bRepeatTray2OutputFull )
			{
				// Tray2 Fail Full
				bRepeatTray2OutputFull = false;
				m.Err.Arm.Code = enCodeArmOutputTray2Full;
				m_bStatus = enRepeatToOutput2FullError;
			}
			else if( bRepeatTray1OutputFull )
			{
				// Tray1 Fail Full
				bRepeatTray1OutputFull = false;
				m.Err.Arm.Code = enCodeArmOutputTray1Full;
				m_bStatus = enRepeatToOutput1FullError;				
			}
			else
				m_bStatus = enRepeatPlacIC;
		}
		break;
	case enRepeatOutTray2Clear:
		f.CWinMessage( "Arm:enRepeatOutTray2Clear", theApp.enDArm );
		{
			m_bStatus = enRepeatToOutput;
		}
		break;
	case enRepeatOutTray1Clear:
		f.CWinMessage( "Arm:enRepeatOutTray1Clear", theApp.enDArm );
		{
			m_bStatus = enRepeatToOutput;
		}
		break;
	case enRepeatPlacIC:
		f.CWinMessage( "Arm:enRepeatPlacIC", theApp.enDArm );
		{
			m_bStatus = enRepeatBlow;
		}
		break;
	case enRepeatBlow:
		f.CWinMessage( "Arm:enRepeatBlow", theApp.enDArm );
		{
			m_bStatus = enRepeatBlowEnd;
		}
		break;
	case enRepeatBlowEnd:
		f.CWinMessage( "Arm:enRepeatBlowEnd", theApp.enDArm );
		{
			m_bStatus = enRepeatOutToHome;
		}
		break;
	case enRepeatOutToHome:
		f.CWinMessage( "Arm:enRepeatOutToHome", theApp.enDArm );
		{
			m_bStatus = enRepeatOutToHomeEnd;
		}
		break;
	case enRepeatOutToHomeEnd:
		f.CWinMessage( "Arm:enRepeatOutToHomeEnd", theApp.enDArm );
		{
			// 1.0As
			RepeatTrayYieldRate();

			// 1.0As
			ConventSiteCounter(0);

			// 1.0An
			RepeatTrayMap();

			// 1.0Am
			RepeatTrayReport();

			//
			f.InsertJamRateTotalCounter();
			m_bStatus = enRepeatOutToHomeEndEnd;
		}
		break;
	case enRepeatOutToHomeEndEnd:
		f.CWinMessage( "Arm:enRepeatOutToHomeEndEnd", theApp.enDArm );
		{
			m_bStatus = enToInput;
		}
		break;
	// Cycle Finish
	case enRepeatCheckComplete:		// Repeat tray check complete
		f.CWinMessage( "Arm:enRepeatCheckComplete", theApp.enDArm );
		{
			if( IsRepeatTrayComplete() )
			{
				// Clear Tray
				theApp.m_Tray1.ChangeTray();
				theApp.m_Tray2.ChangeTray();

				m_bStatus = enRepeatCycleStandy;
			}
			else
			{
				// Clear Tray
				theApp.m_Tray1.ChangeTray();
				theApp.m_Tray2.ChangeTray();

				// Clear Stable
				ClearHeaterStable();

//				m_bStatus = enRepeatToInput;
				m_bStatus = enToInput;
			}
		}
		break;
	case enRepeatCycleStandy:		// Repeat tray arm xy move to standby
		f.CWinMessage( "Arm:enRepeatCycleStandy", theApp.enDArm );
		{
			m_bStatus = enRepeatCycleFinish;
		}
		break;
	case enRepeatCycleFinish:		// Repeat tray arm xy cycle finish
		f.CWinMessage( "Arm:enRepeatCycleFinish", theApp.enDArm );
		{
			//
			f.CycleFinish();

			//
			f.CycleFinishDone();

			//
			f.CycleRepeatFinishDone();

			//
			m_bStatus = enIdle;
		}
		break;

	///////////////////////////////	
	// Remote, SLT Protocol
	case enRemoteProtocolInput:		// SLT Protocol Input
		f.CWinMessage( "Arm:enRemoteProtocolInput", theApp.enDArm );
		{
			m_bStatus = enRemoteProtocolPick;
		}
		break;
	case enRemoteProtocolPick:		// SLT Protocol Pick IC
		f.CWinMessage( "Arm:enRemoteProtocolPick", theApp.enDArm );
		{
			m_bStatus = enRemoteProtocolVacc;
		}
		break;
	case enRemoteProtocolVacc:		// SLT Protocol Vacc
		f.CWinMessage( "Arm:enRemoteProtocolVacc", theApp.enDArm );
		{
			m_bStatus = enRemoteProtocolVaccEnd;
		}
		break;
	case enRemoteProtocolVaccEnd:	// SLT Protocol Vacc End
		f.CWinMessage( "Arm:enRemoteProtocolVaccEnd", theApp.enDArm );
		{
			m_bStatus = enRemoteProtocolInHome;
		}
		break;
	case enRemoteProtocolInHome:	// SLT Protocol Arm Z Home
		f.CWinMessage( "Arm:enRemoteProtocolInHome", theApp.enDArm );
		{
			m_bStatus = enRemoteProtocolInHomeEnd;
//			m_bStatus = enRemoteStandy;
		}
		break;
	case enRemoteProtocolInHomeEnd:	// SLT Protocol Arm Z Home End
		f.CWinMessage( "Arm:enRemoteProtocolInHomeEnd", theApp.enDArm );
		{
			m_ZWithIC = CheckArmZVaccSensor();
			if( m_ZWithIC )
			{
				// Pick OK
				m_lArmRetryCounter = 0;
				m_bStatus = enRotatorInCheckSetting;
			}
			else
			{
				if( m.Setting.m_bByPassVacc == 1 )
				{
					// Pick OK (Demo)
					m_bStatus = enRotatorInCheckSetting;
				}
				else
				{
					// Pick Fail (AutoRetry)
					if( m.Setting.m_iAutoRetrySetting != 0 && 
						m_lArmRetryCounter < m.Setting.m_iAutoRetrySetting )
					{
						m_lArmRetryCounter++;
						m_bStatus = enRemoteProtocolInput;
					}
					// Pick Fail, Alarm
					else
					{
						m.Err.Arm.Code = enCodeArmPickICFail;
						m_bStatus = enRemoteProtocolInHomeEndError;
					}
				}
			}
		}
		break;
	// Output
	case enRemoteProtocolOutput:	// SLT Protocol Output
		f.CWinMessage( "Arm:enRemoteProtocolOutput", theApp.enDArm );
		{
			m_bStatus = enRemoteProtocolPlace;
		}
		break;
	case enRemoteProtocolPlace:		// SLT Protocol Place IC
		f.CWinMessage( "Arm:enRemoteProtocolPlace", theApp.enDArm );
		{
			m_bStatus = enRemoteProtocolBlow;
		}
		break;
	case enRemoteProtocolBlow:		// SLT Protocol Blow
		f.CWinMessage( "Arm:enRemoteProtocolBlow", theApp.enDArm );
		{
			m_bStatus = enRemoteProtocolBlowEnd;
		}
		break;
	case enRemoteProtocolBlowEnd:	// SLT Protocol Blow End
		f.CWinMessage( "Arm:enRemoteProtocolBlowEnd", theApp.enDArm );
		{
			m_bStatus = enRemoteProtocolOutHome;
		}
		break;
	case enRemoteProtocolOutHome:	// SLT Protocol Arm Z Home
		f.CWinMessage( "Arm:enRemoteProtocolOutHome", theApp.enDArm );
		{
			m_bStatus = enRemoteProtocolOutHomeEnd;
		}
		break;
	case enRemoteProtocolOutHomeEnd:// SLT Protocol Arm Z Home End
		f.CWinMessage( "Arm:enRemoteProtocolOutHomeEnd", theApp.enDArm );
		{
			m_bStatus = enRemoteStandy;
		}
		break;
	// Finish
	case enRemoteStandy:			// SLT Protocol Arm move to stand by
		f.CWinMessage( "Arm:enRemoteStandy", theApp.enDArm );
		{
			m_bStatus = enRemoteEnd;
		}
		break;
	case enRemoteEnd:				// SLT Protocol End
		f.CWinMessage( "Arm:enRemoteEnd", theApp.enDArm );
		{		
			// Reset the the thread to Idle
			f.CycleRemoteFinish();

			// Change to Idle
			m_bStatus = enIdle;

			// Auto Stop
			f.ButtonStop();

			// Coordnation is done
			SetRemoteCoordRequest( false );

			// Coordnarion clear
			SetRemoteCoordClearRequest( false );

			// Coordnation is done(ts)
			theApp.m_tInserter.SetRemoteCoordRequest( false );

			// Send Message
			f.RemoteSetCoordnationReturnDone();
		}
		break;
	///////////////////////////////	
	// Error status
	case enRotatorInCheckReadyForInputError:
		f.CWinMessage( "Arm:enRotatorInCheckReadyForInputError", theApp.enDArm );
		{
			if( m.Err.Arm.Code == 0 )
			{
				if( m.Err.Arm.Result == theApp.ActionRetry )
					m_bStatus = enRotatorInCheckReadyForInput;	// Re-Move Rotator
				else if( m.Err.Arm.Result == theApp.ActionSkip )
					m_bStatus = enRotatorInCheckReadyForInput;	// Re-Move Rotator		
				else
					; // Nerver be here
			}
		}
		break;
	case enRotatorInCheckJamForBlowError:
		f.CWinMessage( "Arm:enRotatorInCheckJamForBlowError", theApp.enDArm );
		{
			if( m.Err.Arm.Code == 0 )
			{
				if( m.Err.Arm.Result == theApp.ActionRetry )
					m_bStatus = enRotatorInBlowUp;					// +90,Check Jam again
				else if( m.Err.Arm.Result == theApp.ActionSkip )
				{
					m_bStatus = enRotatorInBlowUp;					// +90,Check Jam again		
				}
				else
					; // Nerver be here
			}
		}
		break;
	case enRotatorInCheckMissingForBlowError:
		f.CWinMessage( "Arm:enRotatorInCheckMissingForBlowError", theApp.enDArm );
		{
			if( m.Err.Arm.Code == 0 )
			{
				if( m.Err.Arm.Result == theApp.ActionRetry )
					m_bStatus = enRotatorInBlowUp;					// +90,Check Missing again
				else if( m.Err.Arm.Result == theApp.ActionSkip )
				{
//					m_bStatus = enRotatorInBlowUp;					// +90,Check Missing again
					m_bStatus = enToInput;
				}
				else
					; // Nerver be here
			}
		}
		break;
	case enRotatorInTurnError:
		f.CWinMessage( "Arm:enRotatorInTurnError", theApp.enDArm );
		{
			if( m.Err.Arm.Code == 0 )
			{
				if( m.Err.Arm.Result == theApp.ActionRetry )
					m_bStatus = enRotatorInTurn;
				else if( m.Err.Arm.Result == theApp.ActionSkip )
					m_bStatus = enRotatorInTurn;		
				else
					; // Nerver be here
			}
		}
		break;
	case enRotatorInCheckMissingForPickError:
		f.CWinMessage( "Arm:enRotatorInCheckMissingForPickError", theApp.enDArm );
		{
			if( m.Err.Arm.Code == 0 )
			{
				if( m.Err.Arm.Result == theApp.ActionRetry )
					m_bStatus = enRotatorInCheckJamForPick;
				else if( m.Err.Arm.Result == theApp.ActionSkip )
				{
//					m_bStatus = enRotatorInCheckJamForPick;	
					m_bStatus = enToInput;	
				}
				else
					; // Nerver be here
			}
		}
		break;
	case enRotatorInPickError:
		f.CWinMessage( "Arm:enRotatorInPickError", theApp.enDArm );
		{
			if( m.Err.Arm.Code == 0 )
			{
				if( m.Err.Arm.Result == theApp.ActionRetry )
				{
					m_bStatus = enRotatorInPickReset;
				}
				else if( m.Err.Arm.Result == theApp.ActionSkip )
				{
					m_bStatus = enToInput;
				}		
				else
					; // Nerver be here
			}
		}
		break;
	case enRotatorOutCheckReadyForOutputError:
		f.CWinMessage( "Arm:enRotatorOutCheckReadyForOutputError", theApp.enDArm );
		{
			if( m.Err.Arm.Code == 0 )
			{
				if( m.Err.Arm.Result == theApp.ActionRetry )
					m_bStatus = enRotatorOutCheckReadyForOutput;
				else if( m.Err.Arm.Result == theApp.ActionSkip )
					m_bStatus = enRotatorOutCheckReadyForOutput;		
				else
					; // Nerver be here
			}
		}
		break;
	case enRotatorOutRaminError:
		f.CWinMessage( "Arm:enRotatorOutRaminError", theApp.enDArm );
		{
			if( m.Err.Arm.Code == 0 )
			{
				if( m.Err.Arm.Result == theApp.ActionRetry )
					m_bStatus = enRotatorOutRamin;
				else if( m.Err.Arm.Result == theApp.ActionSkip )
					m_bStatus = enRotatorOutRamin;		
				else
					; // Nerver be here
			}
		}
		break;
	case enRotatorOutCheckJamForBlowError:
		f.CWinMessage( "Arm:enRotatorOutCheckJamForBlowError", theApp.enDArm );
		{
			if( m.Err.Arm.Code == 0 )
			{
				if( m.Err.Arm.Result == theApp.ActionRetry )
					m_bStatus = enRotatorOutCheckJamForBlow;
				else if( m.Err.Arm.Result == theApp.ActionSkip )
				{
					m_bStatus = enRotatorOutCheckJamForBlow;		
				}
				else
					; // Nerver be here
			}
		}
		break;
	case enRotatorOutCheckMissingForBlowError:
		f.CWinMessage( "Arm:enRotatorOutCheckMissingForBlowError", theApp.enDArm );
		{
			if( m.Err.Arm.Code == 0 )
			{
				if( m.Err.Arm.Result == theApp.ActionRetry )
				{
					m_bStatus = enRotatorOutCheckJamForBlow;
				}
				else if( m.Err.Arm.Result == theApp.ActionSkip )
				{
					m_bStatus = enToInput;
				}
				else
					; // Nerver be here
			}
		}
		break;
	case enRotatorOutTurnError:
		f.CWinMessage( "Arm:enRotatorOutTurnError", theApp.enDArm );
		{
			if( m.Err.Arm.Code == 0 )
			{
				if( m.Err.Arm.Result == theApp.ActionRetry )
					m_bStatus = enRotatorOutTurn;
				else if( m.Err.Arm.Result == theApp.ActionSkip )
					m_bStatus = enRotatorOutTurn;		
				else
					; // Nerver be here
			}
		}
		break;
	case enRotatorOutCheckMissingForPickError:
		f.CWinMessage( "Arm:enRotatorOutCheckMissingForPickError", theApp.enDArm );
		{
			if( m.Err.Arm.Code == 0 )
			{
				if( m.Err.Arm.Result == theApp.ActionRetry )
					m_bStatus = enRotatorOutCheckJamForPick;
				else if( m.Err.Arm.Result == theApp.ActionSkip )
				{
//					m_bStatus = enRotatorOutCheckJamForPick;
					m_bStatus = enToInput;
				}
				else
					; // Nerver be here
			}
		}
		break;
	case enRotatorOutPickError:
		f.CWinMessage( "Arm:enRotatorOutPickError", theApp.enDArm );
		{
			if( m.Err.Arm.Code == 0 )
			{
				if( m.Err.Arm.Result == theApp.ActionRetry )
				{
					m_bStatus = enRotatorOutputReset;
				}
				else if( m.Err.Arm.Result == theApp.ActionSkip )
				{
					m_bStatus = enRotatorOutputReset;		
				}
				else
					; // Nerver be here
			}
		}
		break;
	//////////////////////////////////////////////////////////////////////////////////////////////////
	case enToHomeEndError:
		f.CWinMessage( "Arm:enToHomeEndError", theApp.enDArm );
		{
			if( m.Err.Arm.Code == 0 )
			{
				m_lArmRetryCounter = 0;
				if( m.Err.Arm.Result == theApp.ActionRetry )
				{
					// 重新回到 Input 狀態, 才會讀取 Offset, 然後重新再吸一次
					m_bStatus = enToInput;	
				}
				else if( m.Err.Arm.Result == theApp.ActionSkip )
				{
					// 把那個位置設定為完成, 再回到 Input 狀態, 就會跳到下一顆
					theApp.m_InputTray.LocationDone();			
					m_bStatus = enToInput;
				}
				else
					;	// Nerver be here.
			}
		}
		break;	
	case enToShuttleUpForOutputError:
		f.CWinMessage( "Arm:enToShuttleUpForOutputError", theApp.enDArm );
		{
			if( m.Err.Arm.Code == 0 )
			{
				if( m.Err.Arm.Result == theApp.ActionRetry )
				{
					m_bStatus = enToShuttleOutput;
				}
				else if( m.Err.Arm.Result == theApp.ActionSkip )
				{
					m_bStatus = enToInput;
				}
				else
					; // Nerver be here
			}
		}	
		break;
	case enToOutputCheckFixError:
		f.CWinMessage( "Arm:enToOutputCheckFixError", theApp.enDArm );
		{			
			if( m.Err.Arm.Code == 0 )
			{
				if( m.Err.Arm.Result == theApp.ActionRetry )
				{
					m_bStatus = enToOutputCheckFix;
				}
				else if( m.Err.Arm.Result == theApp.ActionSkip )
				{
					m_bStatus = enToOutputCheckFix;
				}
				else
					; // Nerver be here
			}
		}
		break;
	case enToOutputError:
		f.CWinMessage( "Arm:enToOutputError", theApp.enDArm );
		{			
			if( m.Err.Arm.Code == 0 )
			{
				if( m.Err.Arm.Result == theApp.ActionRetry )
				{
					m_bStatus = enToOutputChangeTray;
				}
				else if( m.Err.Arm.Result == theApp.ActionSkip )
				{
					m_bStatus = enToOutputChangeTray;
				}
				else
					; // Nerver be here
			}
		}
		break;
	case enInputTrayMissingError:
		f.CWinMessage( "Arm:enInputTrayMissingError", theApp.enDArm );
		{			
			if( m.Err.Arm.Code == 0 )
			{
				if( m.Err.Arm.Result == theApp.ActionRetry )
				{
					m_bStatus = enToInput;
				}
				else if( m.Err.Arm.Result == theApp.ActionSkip )
				{
					m_bStatus = enToInput;
				}
				else
					; // Nerver be here
			}
		}
		break;
	case enShuttleCheckJamError:
		f.CWinMessage( "Arm:enShuttleCheckJamError", theApp.enDArm );
		{			
			if( m.Err.Arm.Code == 0 )
			{
				if( m.Err.Arm.Result == theApp.ActionRetry )
				{
					m_bStatus = enShuttleCheckJam;
				}
				else if( m.Err.Arm.Result == theApp.ActionSkip )
				{
					m_bStatus = enShuttleDoubleCheckJam;
				}
				else
					; // Nerver be here
			}
		}
		break;
	// TS Remain IC
	case enTSRemainICCheckError:
		f.CWinMessage( "Arm:enTSRemainICCheckError", theApp.enDArm );
		{
			if( m.Err.Arm.Code == 0 )
			{
				if( m.Err.Arm.Result == theApp.ActionRetry )
				{	
					m_bStatus = enTSRemainICStart;
				}
				else if( m.Err.Arm.Result == theApp.ActionSkip )
				{
					m_bStatus = enTSRemainICEnd;
				}
				else
					; // Nerver be here
			}
		}
		break;
	// CCD Pin1
	case enShuttleCCDMatchError:
		f.CWinMessage( "Arm:enShuttleCCDMatchError", theApp.enDArm );
		{
			if( m.Err.Arm.Code == 0 )
			{
				if( m.Err.Arm.Result == theApp.ActionRetry )
				{	
					m_bStatus = enShuttleCCDPin1Start;
				}
				else if( m.Err.Arm.Result == theApp.ActionSkip )
				{
					m_bStatus = enShuttleCCDPin1Start;
				}
				else
					; // Nerver be here
			}
		}
		break;
	// Repeat Tray
	case enRepeatToOutput2FullError:
		f.CWinMessage( "Arm:enRepeatToOutput2FullError", theApp.enDArm );
		{
			if( m.Err.Arm.Code == 0 )
			{
				if( m.Err.Arm.Result == theApp.ActionRetry )
				{	
					m_bStatus = enRepeatOutTray2Clear;
				}
				else if( m.Err.Arm.Result == theApp.ActionSkip )
				{
					m_bStatus = enRepeatOutTray2Clear;
				}
			}
		}
		break;
	case enRepeatToOutput1FullError:
		f.CWinMessage( "Arm:enRepeatToOutput1FullError", theApp.enDArm );
		{
			if( m.Err.Arm.Code == 0 )
			{
				if( m.Err.Arm.Result == theApp.ActionRetry )
				{	
					m_bStatus = enRepeatOutTray1Clear;
				}
				else if( m.Err.Arm.Result == theApp.ActionSkip )
				{
					m_bStatus = enRepeatOutTray1Clear;
				}
			}		
		}
		break;
	case enRepeatInToHomeEndEndError:
		f.CWinMessage( "Arm:enRepeatInToHomeEndEndError", theApp.enDArm );
		{
			if( m.Err.Arm.Code == 0 )
			{
				m_lArmRetryCounter = 0;
				if( m.Err.Arm.Result == theApp.ActionRetry )
				{	
					m_bStatus = enRepeatToInput;
				}
				else if( m.Err.Arm.Result == theApp.ActionSkip )
				{
					RepeatMationInputDone();
					m_bStatus = enRepeatToInput;
				}
				else
					; // Nerver be here
			}
		}
		break;
	// Remote Ctrl
	case enRemoteProtocolInHomeEndError:
		f.CWinMessage( "Arm:enRemoteProtocolInHomeEndError", theApp.enDArm );
		{
			if( m.Err.Arm.Code == 0 )
			{
				m_lArmRetryCounter = 0;
				if( m.Err.Arm.Result == theApp.ActionRetry )
				{	
					m_bStatus = enRemoteProtocolInput;
				}
				else if( m.Err.Arm.Result == theApp.ActionSkip )
				{
					m_bStatus = enRemoteStandy;
				}
				else
					;	// Nerver be here
			}			
		}
		break;
	//////////////////////////////////////////////////////////////////////////////////////////////////

	}

	if(f.IsPause())
	{
		if(m_bStatus != enIdle)
			m_bStatus = m_bStatus | 0x1;
		return;
	}
}


void CThArm::ClearArmLog()
{
	ArmLog.csCode			= "";
	ArmLog.iBin				= -1;
	ArmLog.iSetTemperature	= -1;
	ArmLog.iBooking			= -1;
	ArmLog.dTestTime		= 0.0;
	ArmLog.bError			= false;
	ArmLog.iTray			= -1;
	ArmLog.iPF				= -1;
	// Clear information.
}
bool CThArm::IsArmLogRootFolderMissing()
{
	bool bFolderMissing = true;

	// Create Arm Log IC Missing root folder anyway
	if( m.m_ArmLogICImage.bEnableArmLogICImage == 1 )
		f.AutoCreateFolder( m.FilePath.ArmLogICImagePath );

	return bFolderMissing;
}
bool CThArm::IsArmLogICImageFolderMissing()
{
	bool bFolderMissing = false;
	
	if( m.m_ArmLogICImage.bEnableArmLogICImage == 1 )
	{		
		CString csFilePath = _T("");
		csFilePath = m.FilePath.ArmLogICImagePath;
		CFileFind finder;											//建立搜尋用的CFileFind物件
		BOOL bResult = finder.FindFile( csFilePath  + "*.*" );		//尋找第一個檔案
		while(bResult)
		{
			bResult = finder.FindNextFile();						//尋找下一個檔案
			if(!finder.IsDots() && finder.IsDirectory())
			{
				CString csFileDirectory = _T("");
				csFileDirectory.Format("%s", finder.GetFileTitle() );
				
				CString csFilePath = _T("");
				csFilePath = m.FilePath.ArmLogICImagePath + "\\" + csFileDirectory;
				
				CString csMsg = _T("");
				csMsg.Format("IsImageFolder Missig, %s, %s\n", csFilePath, m.m_ArmLogICImage.csImageFilePath );
				//			TRACE( csMsg );
				
				//
				if( csFilePath == m.m_ArmLogICImage.csImageFilePath )
				{
					TRACE("IsImageFolder Missig: TRUE\n");
					bFolderMissing = true;
					break;
				}
			}
		}
		
		if(!bFolderMissing)
		{
			TRACE("IsImageFolder Missig: FALSE (Missing)\n");
			f.AutoCreateFolder( m.m_ArmLogICImage.csImageFilePath );
		}
	}

	return bFolderMissing;
}
void CThArm::CameraCapture()
{
	CString csImagePath = _T("");
	CString csImageJpgPath = _T("");

#ifdef _Demo

	// Booking
	int iBooking = theApp.m_tInserter.TestSiteLog.iBooking;
	CString csBook = _T("");
	csBook.Format("%.3d", iBooking+1 );

	// Tray (Tray1, Tray2)
	CString csCurrentTray = _T("");
	csCurrentTray.Format("%s", GetCurrentTray() );

	// Repeat counter
	CString csCurrentRepeatTime = _T("");
	csCurrentRepeatTime.Format("%.3d", m.m_RepeatTrayDATA.m_NowCount+1 );

	// New Image file name ( Grab image file location )
	csImagePath = m.m_ArmLogICImage.csImageFilePath + "\\" + "1" + _ArmLogICImage;
	
	CString csExt = _T("");
	// Convert Image
	csImageJpgPath = m.m_ArmLogICImage.csImageFilePath + "\\" +
		csBook + "_" +
		csCurrentTray + "_" + 
		csCurrentRepeatTime + csExt + _ArmLogICImageJpg;
		
	// Convert Bitmap to Jpeg
	f.ConvertFile(csImagePath, csImageJpgPath);

#else

	// Booking
	int iBooking = theApp.m_tInserter.TestSiteLog.iBooking;
	CString csBook = _T("");
	csBook.Format("%.3d", iBooking+1 );

	// Tray (Tray1, Tray2)
	CString csCurrentTray = _T("");
	csCurrentTray.Format("%s", GetCurrentTray() );

	// Repeat counter
	CString csCurrentRepeatTime = _T("");
	csCurrentRepeatTime.Format("%.3d", m.m_RepeatTrayDATA.m_NowCount+1 );

	// New Image file name ( Grab image file location )
	csImagePath = m.m_ArmLogICImage.csImageFilePath + "\\" +
		csBook + "_" +
		csCurrentTray + "_" + 
		csCurrentRepeatTime + _ArmLogICImage;

	CString csExtendImage = _T("");

	// Convert Image
	csImageJpgPath = m.m_ArmLogICImage.csImageFilePath + "\\" +
		csBook + "_" +
		csCurrentTray + "_" + 
		csCurrentRepeatTime + csExtendImage + _ArmLogICImageJpg;
		
	// Grab image 截圖
// 	if(m.m_Vision.CameraGrabSave(m.m_CCDPin1Control.iCCDUse, csImagePath))
// 	{
// 		
// 	}
// 	else
// 	{
// 		TRACE("Grab Error\n");
// 	}
		
	// Convert Bitmap to Jpeg
	f.ConvertFile(csImagePath, csImageJpgPath);
		
	// Delete Bitmap 
	::DeleteFile( csImagePath );

#endif
}
bool CThArm::CheckArmJam()
{
	// Jam return true
	// Not Jam return false
	bool bJam = false;
#ifdef _Demo
	bJam = false;	// zz
	return bJam;
#else
	if( m.InStatus.ShuttleInputJam == _ShuttleJamOn )
		bJam = true;
	else
		bJam = false;
#endif
	return bJam;
}
bool CThArm::CheckInputExit()
{
	bool bExist = true;
#ifdef _Demo
	bExist = true;
#else
	if( m.Setting.m_bByPassTrayInPos == 1 )
	{
		bExist = true;
	}
	else
	{		
		if( m.InStatus.InputTrayInPos == _TrayInPosOn )
			bExist = true;
		else
			bExist = false;
	}
#endif

	return bExist;
}
bool CThArm::CheckFixExist()
{
	bool bExist = true;
#ifdef _Demo
	bExist = true;
#else
	
	if( m.InStatus.OutputTrayInPos == _TrayInPosOn )
		bExist = true;
	else
		bExist = false;
#endif

	return bExist;
}
bool CThArm::CheckArmZIC(unsigned char* Vacc, unsigned char* pSensor, long dTimeout)
{
	// if have IC return false;
	// if have No IC, OK return true;

	int	iStart;

	*Vacc = 1;		// Turn on vacuum.
	iStart = ::GetTickCount();
	while (1)
	{
		if ( (::GetTickCount() - iStart ) >= dTimeout )
		{
			// Timeout, It mean there have no IC
			*Vacc = 0;
			return true;
		}

		// Check the vacuum sensor.
		if (*pSensor == _ArmZVaccOn)
		{
			// No, There have IC
			return false;
		}

		if(f.IsPause())
		{
			*Vacc = 0;
			return false;
		}

		Sleep(_Wait);
	}

	*Vacc = 0;
	return false;
}

double CThArm::AutoRetryAdjustValue(int iCount)
{
	double value = 0.0; //mm

	if( m.Setting.m_bArmZAutoRetry == 1 && 
		m.Setting.m_iAutoRetrySetting != 0 )
	{
		if( m.m_AutoRetryAjsutValue.iAlwaysAdjsut == 1 )
		{					
			value = ( m.m_AutoRetryAjsutValue.dAdjustValue * iCount );	// 每次都要加
		}
		else
		{			
			if( iCount > 0 )
				value = m.m_AutoRetryAjsutValue.dAdjustValue;			// 只加第一次
		}

		//
		CString csMsg = _T("");
		csMsg.Format("Auto Retry Adjust (mm): %5.2f", value );
		f.CWinMessage( "Arm:enPickIC->" + csMsg, theApp.enDArm );
		//
	}

	return value;
}
void CThArm::ConventSiteCounter(int Stack)
{
	if( Stack == 0 )
		f.Counter( theApp.enBin1 );
}
void CThArm::RemoteControlMessageArmReady()
{
	CString cs = _T("");
	::SendMessage( theApp.m_DlgRemoteControlCustom->GetSafeHwnd(), 
		WM_REMOTE_PICK_IC,  (WPARAM)&cs , (LPARAM)&cs );
}
void CThArm::RemoteControlMessageReleaseIC()
{	
	CString cs = _T("");
	::SendMessage( theApp.m_DlgRemoteControlCustom->GetSafeHwnd(), 
		WM_REMOTE_RELEASE_IC,  (WPARAM)&cs , (LPARAM)&cs );
}
void CThArm::RemoteControlMessageICReady()
{
	CString cs = _T("");
	::SendMessage( theApp.m_DlgRemoteControlCustom->GetSafeHwnd(), 
		WM_REMOTE_READY,  (WPARAM)&cs , (LPARAM)&cs );
}
// SLT Protocol
void CThArm::InitialMissionOnTheGo()
{
	m_bMissionOnTheGo = false;
	m_bMissionOnTheClearGo = false;
	m_RemoteArmTray.m_iRemoteBooking = 0;
	m_RemoteArmTray.m_iRemoteTray = 0;
}
void CThArm::SetRemoteCoordRequest( bool bMissionGo )
{
	m_bMissionOnTheGo = bMissionGo;
}
void CThArm::SetRemoteCoordPosition(int iBooking, int iTray)
{
	m_RemoteArmTray.m_iRemoteBooking = iBooking;
	m_RemoteArmTray.m_iRemoteTray = iTray;
}
bool CThArm::GetRemoteCoordRequest()
{
	return m_bMissionOnTheGo;
}
void CThArm::SetRemoteCoordClearRequest( bool bMissionClearGo )
{
	m_bMissionOnTheClearGo = bMissionClearGo;
}
bool CThArm::GetRemoteCoodrClearRequest()
{
	return m_bMissionOnTheClearGo;
}
long CThArm::RemoteMationInput()
{
	long m_iRemoteRunError = enCodeRunOK;
	if( m_RemoteArmTray.m_iRemoteTray == theApp.enRemoteTrayMation1 )
	{
		// 通訊指向 Tray1
		int iBooking = -1;
		iBooking = m_RemoteArmTray.m_iRemoteBooking;
		CPoint px;
		px = theApp.m_Tray1.GetCoordinate( iBooking );
		
		theApp.m_tArm.ClearArmLog();
		ArmLog.iBooking = iBooking;
		ArmLog.iTray = theApp.enTray1;
		
		m_iRemoteRunError = f.Motor.MotorRunLine(
			m.m_Motor.ArmX, px.x + ( m.m_Offset.Input.x * m.m_Ratio.X_GearRation ),
			m.m_Motor.ArmY, px.y + ( m.m_Offset.Input.y * m.m_Ratio.Y_GearRation ),
			true, m.TimerSetting.iMotorRunlineTimeout );
		
		// Debug 
		CString csMsg = _T("");
		csMsg.Format("Remote Input > Booking-> %.3d, Tray-> %.2d\n", ArmLog.iBooking, ArmLog.iTray );
		TRACE( csMsg );
	}
	else if( m_RemoteArmTray.m_iRemoteTray == theApp.enRemoteTrayMation2 )
	{
		// 通訊指向 Tray2
		int iBooking = -1;
		iBooking = m_RemoteArmTray.m_iRemoteBooking;
		CPoint px;
		px = theApp.m_Tray2.GetCoordinate( iBooking );
				
		theApp.m_tArm.ClearArmLog();
		ArmLog.iBooking = iBooking;
		ArmLog.iTray = theApp.enTray2;
				
		m_iRemoteRunError = f.Motor.MotorRunLine(
			m.m_Motor.ArmX, px.x + ( m.m_Offset.Output1.x * m.m_Ratio.X_GearRation ),
			m.m_Motor.ArmY, px.y + ( m.m_Offset.Output1.y * m.m_Ratio.Y_GearRation ),
			true, m.TimerSetting.iMotorRunlineTimeout );

		// Debug 
		CString csMsg = _T("");
		csMsg.Format("Remote Input > Booking-> %.3d, Tray-> %.2d\n", ArmLog.iBooking, ArmLog.iTray );
		TRACE( csMsg );
	}
	else
		; // Nerver be here

	return m_iRemoteRunError;
}
long CThArm::RemoteMationInputZDown()
{
	long m_iRemoteRunError = enCodeRunOK;
	if( m_RemoteArmTray.m_iRemoteTray == theApp.enRemoteTrayMation1 )
	{
		m_iRemoteRunError = f.Motor.MotorRun(&m.m_Motor.ArmZ, 
			m.m_Align.Input.z + ( m.m_Offset.Input.z * m.m_Ratio.Z_GearRation ), false, m.TimerSetting.iMotorRunTimeout );
	}
	else if( m_RemoteArmTray.m_iRemoteTray == theApp.enRemoteTrayMation2 )
	{
		m_iRemoteRunError = f.Motor.MotorRun(&m.m_Motor.ArmZ, 
			m.m_Align.Output1.z + ( m.m_Offset.Output1.z * m.m_Ratio.Z_GearRation ), false, m.TimerSetting.iMotorRunTimeout );
	}
	else
		; // Nerver be here

	return m_iRemoteRunError;
}
long CThArm::RemoteMationOutput()
{
	long m_iRemoteRunError = enCodeRunOK;
	if( m_RemoteArmTray.m_iRemoteTray == theApp.enRemoteTrayMation1 )
	{
		// 通訊指向 Tray1
		int iBooking = -1;
		iBooking = m_RemoteArmTray.m_iRemoteBooking;
		CPoint px;
		px = theApp.m_Tray1.GetCoordinate( iBooking );		
		
		m_iRemoteRunError = f.Motor.MotorRunLine(
			m.m_Motor.ArmX, px.x + ( m.m_Offset.Input.x * m.m_Ratio.X_GearRation ),
			m.m_Motor.ArmY, px.y + ( m.m_Offset.Input.y * m.m_Ratio.Y_GearRation ),
			true, m.TimerSetting.iMotorRunlineTimeout );
		
		// Debug 
		CString csMsg = _T("");
		csMsg.Format("Remote Output > Booking-> %.3d, Tray-> %.2d\n", ArmLog.iBooking, ArmLog.iTray );
		TRACE( csMsg );	
	}
	else if( m_RemoteArmTray.m_iRemoteTray == theApp.enRemoteTrayMation2 )
	{
		// 通訊指向 Tray2
		int iBooking = -1;
		iBooking = m_RemoteArmTray.m_iRemoteBooking;
		CPoint px;
		px = theApp.m_Tray2.GetCoordinate( iBooking );
	
		m_iRemoteRunError = f.Motor.MotorRunLine(
			m.m_Motor.ArmX, px.x + ( m.m_Offset.Output1.x * m.m_Ratio.X_GearRation ),
			m.m_Motor.ArmY, px.y + ( m.m_Offset.Output1.y * m.m_Ratio.Y_GearRation ),
			true, m.TimerSetting.iMotorRunlineTimeout );

		// Debug 
		CString csMsg = _T("");
		csMsg.Format("Remote Output > Booking-> %.3d, Tray-> %.2d\n", ArmLog.iBooking, ArmLog.iTray );
		TRACE( csMsg );	
	}
	else
		; // Nerver be here

	return m_iRemoteRunError;
}
long CThArm::RemoteMationOutputZDown()
{
	long m_iRemoteRunError = enCodeRunOK;
	if( m_RemoteArmTray.m_iRemoteTray == theApp.enRemoteTrayMation1 )
	{
		// 通訊指向 Tray1
		m_iRemoteRunError = f.Motor.MotorRun(&m.m_Motor.ArmZ, 
			m.m_Align.Input.z + ( m.m_Offset.Input.z2 * m.m_Ratio.Z_GearRation ), false, m.TimerSetting.iMotorRunTimeout );
	}
	else if( m_RemoteArmTray.m_iRemoteTray == theApp.enRemoteTrayMation2 )
	{
		// 通訊指向 Tray2
		m_iRemoteRunError = f.Motor.MotorRun(&m.m_Motor.ArmZ, 
			m.m_Align.Output1.z + ( m.m_Offset.Output1.z2 * m.m_Ratio.Z_GearRation ), false, m.TimerSetting.iMotorRunTimeout );
	}
	else
		; // Nerver be here

	return m_iRemoteRunError;
}

int CThArm::GetThreadMotionStatus()
{
	return m_bStatus;
}

int CThArm::ExitInstance()
{
	TRACE("CThArm\n");
	// TODO:  perform any per-thread cleanup here
	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(CThArm, CWinThread)
	//{{AFX_MSG_MAP(CThArm)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CThArm message handlers
