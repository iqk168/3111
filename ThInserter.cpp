// ThInserter.cpp : implementation file
//

#include "stdafx.h"
#include "deer.h"
#include "ThInserter.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CThInserter

IMPLEMENT_DYNCREATE(CThInserter, CWinThread)

CThInserter::CThInserter()
{
	m_bStatus = enIdle;	
	m_bInitialized = false;
	m_bInitialRequest = false;

	m_iRunError = enCodeRunOK;

	TestSiteLog.csCode = "";
	TestSiteLog.iBin = -1;
	TestSiteLog.iSetTemperature  = -1;
	TestSiteLog.iBooking = -1;
	TestSiteLog.iTray = -1;
	TestSiteLog.iPF = -1;
	// Test Site Log default value

	m_TSZWithIC	= false;

	ICDropInd = false;

	m_bMissionOnTheGo = false;
}

CThInserter::~CThInserter()
{
	TRACE("~CThInserter\n");
}

BOOL CThInserter::InitInstance()
{
	f.IncraseThreadCount();
	m.ThStatus.InserterCtrl.times = 1;
	while(m.Info.bRunning)
	{
		m.ThStatus.InserterCtrl.times++;
		Running();
		Sleep(_Wait);
	}
	f.ReduceThreadCount();
	f.m_Log.AddLogEvent( "Thread Inserter Finish" );

	return TRUE;
}
void CThInserter::RemoteControlMessageArmReady()
{
	CString cs = _T("");
	::SendMessage( theApp.m_DlgRemoteControlCustom->GetSafeHwnd(), 
		WM_REMOTE_PICK_IC,  (WPARAM)&cs , (LPARAM)&cs );
}
void CThInserter::RemoteControlMessageReleaseIC()
{	
	CString cs = _T("");
	::SendMessage( theApp.m_DlgRemoteControlCustom->GetSafeHwnd(), 
		WM_REMOTE_RELEASE_IC,  (WPARAM)&cs , (LPARAM)&cs );
}
void CThInserter::RemoteControlMessageICReady()
{
	CString cs = _T("");
	::SendMessage( theApp.m_DlgRemoteControlCustom->GetSafeHwnd(), 
		WM_REMOTE_READY,  (WPARAM)&cs , (LPARAM)&cs );
}
void CThInserter::SaveTSCounter()
{
	if( m.Site.iRunMode == theApp.enOnLine || m.Site.iRunMode == theApp.enOffLine )
	{
		m.m_ContactCounterValue.lContactConter++;

		//
		f.SaveContactCounter();

		//
		f.TSMessageCounter();	// updata ts counter
	}
}
void CThInserter::InitHeaterValue()
{
	m_TsSoak.lSoakStart = 0;
}
void CThInserter::SetHeaterStart()
{
	m_TsSoak.lSoakStart = ::GetTickCount();
}
bool CThInserter::WaitHeaterSoakOK()
{
	double dSoakTime = m.m_West.dSoakTime;
	// Repeat tray control from table
	if( m.m_RepeatTrayCtrl.m_iRepeatTrayMode == theApp.enRepeatTrayInOutCtrl )
	{
		int iSize = m.m_RepeatTrayTemperData.GetSize();
		if( iSize > m.m_RepeatTrayDATA.m_NowCount )
			dSoakTime = m.m_RepeatTrayTemperData.GetAt( m.m_RepeatTrayDATA.m_NowCount ).m_dSoakingTime;
	}

	//
	long m_lNowTime = ::GetTickCount();
	long m_lResultTime = ( m_lNowTime - m_TsSoak.lSoakStart );
	double dWaitTime = m_lResultTime / 1000.;
	if( dWaitTime > dSoakTime )
		return true;
	else
		return false;
}
void CThInserter::ClearHeaterValue()
{
	m_TsSoak.lSoakStart = 0;
}
void CThInserter::UPHTSDataAdd()
{
	long lTSData = ::GetTickCount();
	m.m_UPHData.m_TSCalc.Add( lTSData );

	//
	f.UPHMessageForTs();
}
bool CThInserter::ShuttleMoveLogJam()
{
	// Jam return true
	// Not Jam return false
	bool bJam = false;
#ifdef _Demo
	bJam = true;
	return bJam;
#else
	if( m.InStatus.ShuttleInputJam == _ShuttleJamOn )
		bJam = true;
	else
		bJam = false;
#endif
	return bJam;
}
bool CThInserter::CheckShuttleInputJam()
{
	// Jam return true
	// Not Jam return false
	bool bJam = false;
#ifdef _Demo
	bJam = false;
	return bJam;
#else
	if( m.InStatus.ShuttleInputJam == _ShuttleJamOn )
		bJam = true;
	else
		bJam = false;
#endif
	return bJam;
}
bool CThInserter::ShuttleMovePickPlace()		// Shuttle move to testSite pick / place position
{
	bool bMovePick = false;
#ifdef _Demo
	bMovePick = true;
#else

	m.OutSet.Shuttle = true;
	int iStart = ::GetTickCount();
	while(1)
	{
		if( m.InStatus.ShuttleNLmt == _ShuttleNLmtOff && m.InStatus.ShuttlePLmt == _ShuttlePLmtOn )
		{
			bMovePick = true;
			break;
		}
		else if(f.IsPause())
		{
			bMovePick = false;
			break;
		}
		else if(!m.Info.bRunning)
		{
			bMovePick = false;
			break;
		}
		else if( (::GetTickCount() - iStart ) > m.TimerSetting.iShuttlePickTimeout )
		{
			bMovePick = false;
			break;
		}
		else
			; // Wait here.	

		// 1.0Ab
		if( ShuttleMoveLogJam())
			f.ShuttleJamLog("Shuttle move to ts pick jam");

		Sleep(1);
	}
#endif
	return bMovePick;
}
bool CThInserter::ShuttleMoveHome()		// Shuttle move to arm pick / place position
{
	bool bMoveHome = false;
#ifdef _Demo
	bMoveHome = true;
#else

	m.OutSet.Shuttle = false;
	int iStart = ::GetTickCount();
	while(1)
	{
		if( m.InStatus.ShuttleNLmt == _ShuttleNLmtOn && m.InStatus.ShuttlePLmt == _ShuttlePLmtOff )
		{
			bMoveHome = true;
			break;
		}
		else if(f.IsPause())
		{
			bMoveHome = false;
			break;
		}
		else if(!m.Info.bRunning)
		{
			bMoveHome = false;
			break;
		}
		else if( (::GetTickCount() - iStart ) > m.TimerSetting.iShuttleHomeTimeout )
		{
			bMoveHome = false;
			break;
		}
		else
			; // Wait here.

		Sleep(1);
	}
#endif
	return bMoveHome;
}
bool CThInserter::CheckShuttlePickPlaceOK()	// Check shuttle move to pick / place position ok
{
	bool bMovePickOK = false;
#ifdef _Demo
	bMovePickOK = true;
#else	
	if( m.InStatus.ShuttleNLmt == _ShuttleNLmtOff && m.InStatus.ShuttlePLmt == _ShuttlePLmtOn )
		bMovePickOK = true;
	else
		bMovePickOK	= false;
#endif
	return bMovePickOK;
}
bool CThInserter::CheckShuttleHomeOK()	// Check shuttle move to home / pick / place position ok
{
	bool bMoveHomeOK = false;
#ifdef _Demo
	bMoveHomeOK = true;
#else
	if( m.InStatus.ShuttleNLmt == _ShuttleNLmtOn && m.InStatus.ShuttlePLmt == _ShuttlePLmtOff )
		bMoveHomeOK = true;
	else
		bMoveHomeOK	= false;
#endif
	return bMoveHomeOK;
}
bool CThInserter::CheckTSArmZIC(unsigned char* Vacc, unsigned char* pSensor, long dTimeout)
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
		if (*pSensor == _TSVacOn )
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
bool CThInserter::CheckTSZVaccSensor()
{
	bool bVacc = false;
#ifdef _Demo
	bVacc = true;
#else
	if( m.InStatus.TestSiteZVaccSensor == _TSVacOn )
		bVacc = true;
	else
		bVacc = false;
#endif

	return bVacc;
}
bool CThInserter::VaccOff(unsigned char* Vacc)
{
	*Vacc = 0;		// Turn off vacuum.
	return true;
}
bool CThInserter::Vacc(unsigned char* Vacc, unsigned char* pSensor, double dTimeout )
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
		if (*pSensor == _TSVacOn)
		{
			// Do a debounce on the sensor.
			Sleep(10);
			if (*pSensor == _TSVacOn)
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
	if (*pSensor == _TSVacOn)
		return true;

	// Something wrong - turn it off.
	*Vacc = 0;

	return false;
}
bool CThInserter::Blow(unsigned char* Vacc, unsigned char* Puff, unsigned char* pSensor, double dTimeout )
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

void CThInserter::ClearTestSiteLog()
{
	TestSiteLog.csCode = "";
	TestSiteLog.iBin = -1;
	TestSiteLog.iSetTemperature = -1;
	TestSiteLog.iBooking = -1;
	TestSiteLog.dTestTime = 0.0;
	TestSiteLog.bError = false;
	TestSiteLog.iTray = -1;
	TestSiteLog.iPF = -1;
	// Clear information.
}

void CThInserter::InitialStart()
{
	m_bInitialRequest = true;
}

void CThInserter::Initialize()
{
	// 1.0Aj
	// Bypass Initial
#ifdef _Demo

	// Initial Shuttle
	InitShuttleStatus();

	// Heater 
	InitHeaterValue();

	// IC Drop
	InitICDropInd();

	// Initial Remote
	InitialMissionOnTheGo();

	// Initial 結束
	m.MotorStatus.InserterInitialed = true;
	m.InterLock.InserterEnd = true;
	m.MotorStatus.Inserter = _T("Test Site Initial OK.");
	m_bInitialized = true;	

	return;

#endif

	m_bInitialized = false;
	m.MotorStatus.Inserter = _T("Initialing.");	
	f.CWinMessage( "TestSiteS:Test Site Start", theApp.enDTestSite );

	// Initial Shuttle
	InitShuttleStatus();

	// Heater 
	InitHeaterValue();

	// IC Drop
	InitICDropInd();

	// Initial Remote
	InitialMissionOnTheGo();
	
	////// Initial Process
	// Test Site 	
	// 清除錯誤
	f.Motor.ClearMotorAlarm( &m.m_Motor.Inserter );	
	f.Wait(2000);
	f.Motor.ClearMotorError( &m.m_Motor.Inserter );
	f.Wait(2000);
	f.Motor.Servo( &m.m_Motor.Inserter, true );

	bool bTestArmHaveIC = false;
	bTestArmHaveIC = CheckTSArmZIC( &m.OutSet.TestSiteVacc, &m.InStatus.TestSiteZVaccSensor, 
		m.TimerSetting.iArmZCheckTime );

	// If not Initial. return this function. User want to stop.
	// if fail. It won't not set the error code.
	if( m.Info.iStatus != theApp.enInitial )
		return;

	// 載入 飄移速度..飄到 sensor 那邊去 Load Driff Speed for move to nLmt
	f.Motor.LoadDriftSpeed( &m.m_Motor.Inserter );
	m_iRunError = f.Motor.MotorMovetonNLimt( m.m_Motor.Inserter, _InitialTestSiteTimeout );

	// Move to nLmt (1 in)
	if ( IsInitialError( m_iRunError, f.Motor.GetMotorID( &m.m_Motor.Inserter ) ))
		return;
	if( m.Info.iStatus != theApp.enInitial )
		return;
	m.MotorStatus.Inserter = "Move to Lmt OK.";	/* 第一次尋找 snesor 成功 */

	// 清除 Encoder
	f.Wait( _WaitLmt );		
	f.Motor.MotorClearCount( &m.m_Motor.Inserter );
	f.Wait( _WaitLmt );		

	// 載入搜索速度, 離開 sneosr
	f.Motor.LoadSearchSpeed( &m.m_Motor.Inserter );
	m.MotorStatus.Inserter = "Search Home.";	

	m_iRunError = f.Motor.MotorRunAnyway( &m.m_Motor.Inserter, ( _InitialTestSite * m.m_Ratio.Inserter_GearRation ), 
		false, m.TimerSetting.iMotorRunTimeout );

	if ( IsInitialError( m_iRunError, f.Motor.GetMotorID( &m.m_Motor.Inserter ) ))
		return;
	if( m.Info.iStatus != theApp.enInitial )
		return;
	m.MotorStatus.Inserter = "Search Home OK.";	/* 第一次離開 snesor 成功 */

	f.Wait( _WaitLmt );		// Wait for few time.

	// 載入搜索速度, 近距離尋找 sneosr
	f.Motor.LoadSearchSpeed( &m.m_Motor.Inserter );
	m.MotorStatus.Inserter = "Move to Lmt.";
	m_iRunError = f.Motor.MotorMovetonLimt( &m.m_Motor.Inserter, _InitialTestSiteTimeout );

	if ( IsInitialError( m_iRunError, f.Motor.GetMotorID( &m.m_Motor.Inserter ) ))
		return;
	if( m.Info.iStatus != theApp.enInitial )
		return;
	m.MotorStatus.Inserter = "Move to Lmt OK.";	/* 第二次尋找 snesor 成功 */

	f.Wait( _WaitLmt );		// Wait for few time.

	// 載入搜索速度, 離開 sneosr
	f.Motor.LoadSearchSpeed( &m.m_Motor.Inserter );
	// 清除 Encoder
	f.Wait( _WaitLmt );		
	f.Motor.MotorClearCount( &m.m_Motor.Inserter );
	f.Wait( _WaitLmt );	
	//
	m.MotorStatus.Inserter = "Search Home.";
	m_iRunError = f.Motor.MotorRunAnyway( &m.m_Motor.Inserter, ( _InitialTestSite * m.m_Ratio.Inserter_GearRation ), 
		false, m.TimerSetting.iMotorRunTimeout );

	if ( IsInitialError( m_iRunError, f.Motor.GetMotorID( &m.m_Motor.Inserter ) ))
		return;
	if( m.Info.iStatus != theApp.enInitial )
		return;
	m.MotorStatus.Inserter = "Search Home OK.";	/* 第二次離開 snesor 成功 */

	// 等一點時間, 然後清除 RCount, LCount
	f.Wait( _ClearCountWait );
	f.Motor.MotorClearCount( &m.m_Motor.Inserter );
	// 離開  _InitialZHome mm 距離, 避免回 Home Overheat
	
	if( !bTestArmHaveIC )
		m.Err.Inserter.Code = enCodeTSArmZInitialhaveIC;

	f.Wait( 500 );
	if( m.Info.iStatus != theApp.enInitial )
		return;

	// 設定 flag, 讓 Arm 開始 Initial
	m.InitialInterLock.InitialTSUpOK = true;

	// 1.0Ac
	// Torque Status
	InitTorqueInitialLoad();

	// 終於 Initial 結束
	m.MotorStatus.InserterInitialed = true;
	m.InterLock.InserterEnd = true;
	m.MotorStatus.Inserter = _T("Test Site Initial OK.");
	m_bInitialized = true;	

	f.CWinMessage( "TestSiteS:Test Site OK", theApp.enDTestSite );
}
void CThInserter::InitShuttleStatus()
{

}
bool CThInserter::IsInitialError(long err, long id)
{
	if(err != enCodeRunOK)
	{
		f.Motor.MotorStop( &m.m_Motor.Inserter );

		// stop all motor 
		m_bStatus = enIdle;
	
		m.MotorStatus.Inserter = "Cancel.";
//		m.Err.Inserter.Code = err + id;
		m.Err.Inserter.Code = err;
		// Set error 

		return true;
	}

	return false;
}

void CThInserter::Running()
{
	if(!m_bInitialized && m.Info.iStatus != theApp.enInitial)
	{
		m_bStatus = enIdle;
		m.ThStatus.InserterCtrl.line = m_bStatus;
		return;
	}
	// If Handler status is Uninitial. We force it to return and keep m_bStatus in enIdle.
	// Notes : In Thread Monitior. Uninitial will always be enIdle
	
	if( m_bInitialRequest )
	{
		f.CWinMessage( "TestSite:enInitialize R", theApp.enDTestSite );
		m_bInitialRequest = false;
		m_bStatus = enInitialize;
	}

	m.ThStatus.InserterCtrl.line = m_bStatus;
	switch(m_bStatus)
	{			
	case enInitialize:
		Initialize();
		NextStatus();
		break;
	case enIdle:		
		NextStatus();
		break;
	case enShuttleHome:
		{
			ShuttleMoveHome();
			f.Wait( m.TimerSetting.iShuttleStableTime );
		}
		NextStatus();
		break;
	case enShuttleHomeStandy:		// Shuttle move to home standy
		{
		
		}
		NextStatus();
		break;
	case enShuttleRestart:			// Test Pick From Socket Fail. Re-set it, ask Arm move to input again
		{
		
		}
		NextStatus();
		break;
	case enShuttleRestartDrop:		// Test Down Place to Socket. But IC Missing
		{
		
		}
		NextStatus();
		break;

	///////////////////////////////
	case enShuttleInput:				// Shuttle move to input 
		{
			ShuttleMovePickPlace();
			f.Wait( m.TimerSetting.iShuttleStableTime );
		}
		NextStatus();
		break;
	case enShuttleInputJam:				// Shuttle move to input, and check jam again
		{
		
		}
		NextStatus();
		break;
	case enShutlleInputEnd:				// Shuttle move to input end
		{
		}
		NextStatus();
		break;
	//
	case enTestSitePickForVacc:			// Test site down to pick
		{
			m_iRunError = f.Motor.MotorRun(&m.m_Motor.Inserter, 
				m.m_Align.TestSite.pick + ( m.m_Offset.TestSite.pick * m.m_Ratio.Inserter_GearRation ), 
				false, m.TimerSetting.iMotorRunTimeout );
		}
		NextStatus();
		break;
	case enTestSiteVaccForUp:			// Test site turn on the vacc
		{
#ifdef _Demo
			m_TSZWithIC = true;
#else
			m_TSZWithIC = Vacc( &m.OutSet.TestSiteVacc, &m.InStatus.TestSiteZVaccSensor, m.Timer.m_dInsertPick );
#endif			
		}
		NextStatus();
		break;
	case enTestSiteUpForContact:		// Test site up for contact
		{
			m_iRunError = f.Motor.MotorRun(&m.m_Motor.Inserter, 
				( m.m_Align.TestSite.home + ( m.m_Offset.TestSite.home * m.m_Ratio.Inserter_GearRation ) + ( m.Setting.m_dTestSiteStandbyPosition * m.m_Ratio.Inserter_GearRation)), 
				false, m.TimerSetting.iMotorRunTimeout );
		}
		NextStatus();
		break;
	case enShuttleHomeForContact:		// Shuttle move to home
		{
			ShuttleMoveHome();
			f.Wait( m.TimerSetting.iShuttleStableTime );
		}
		NextStatus();
		break;
	case enTestSiteDownForContact:		// Test site down to place ic to socket (fast)
		{
			if( m.Setting.m_dTestSiteSocketStandyPos != 0 )
			{				
				m_iRunError = f.Motor.MotorSoftRun(&m.m_Motor.Inserter, 
					( m.m_Align.TestSite.contact + 
					( m.m_Offset.TestSite.contact * m.m_Ratio.Inserter_GearRation ) +
					( m.Setting.m_dTestSiteSocketStandyPos * m.m_Ratio.Inserter_GearRation )), 
					false, m.TimerSetting.iMotorRunTimeout );
			}
		}
		NextStatus();
		break;
	case enTestSiteToDrop:				// Test site drop mode
		{
			// 1.0Ah
			// Remove this and re-build new
			/*
			m_iRunError = f.Motor.MotorRun(&m.m_Motor.Inserter, 
				m.m_Align.TestSite.contact + ( m.m_Offset.TestSite.contact * m.m_Ratio.Inserter_GearRation ) - 
				( m.YieldSetting.dDropHigh * m.m_Ratio.Inserter_GearRation ), 
				false, m.TimerSetting.iMotorRunTimeout );
			*/
			m_iRunError = f.Motor.MotorRunTSCheckICDrop(&m.m_Motor.Inserter, 
				m.m_Align.TestSite.contact + ( m.m_Offset.TestSite.contact * m.m_Ratio.Inserter_GearRation ) - 
				( m.YieldSetting.dDropHigh * m.m_Ratio.Inserter_GearRation ), 
				false, m.TimerSetting.iMotorRunTimeout );

			// IC Missing
			if( m_iRunError == enCodeTestSiteMoveICMissing )
			{
				m_iRunError = enCodeRunOK;
				SetICDropInd( true );
			}
		}
		NextStatus();
		break;
	case enTestSiteDropDevice:			// Test site drop mode blow 
		{
			m_TSZWithIC = Blow( &m.OutSet.TestSiteVacc, &m.OutSet.TestSiteBlow,
				&m.InStatus.TestSiteZVaccSensor, m.YieldSetting.dDropTimer );
		}
		NextStatus();
		break;

	case enTestSiteContact:				// Test site contact 
		{
			// 1.0Ah
			// Remove this and re-build new
			/*
			m_iRunError = f.Motor.MotorRunTLC(&m.m_Motor.Inserter, 
				m.m_Align.TestSite.contact + ( m.m_Offset.TestSite.contact * m.m_Ratio.Inserter_GearRation ), 
				false, m.TimerSetting.iMotorRunTimeout );
			*/

			m_iRunError = f.Motor.MotorRunTLCCheckICDrop(&m.m_Motor.Inserter, 
				m.m_Align.TestSite.contact + ( m.m_Offset.TestSite.contact * m.m_Ratio.Inserter_GearRation ), 
				false, m.TimerSetting.iMotorRunTimeout );

			// IC Missing
			if( m_iRunError == enCodeTestSiteMoveICMissing )
			{
				m_iRunError = enCodeRunOK;
				SetICDropInd( true );
			}

		}
		NextStatus();
		break;
	case enTestStteContactEnd:
		{
			if( m.TraySkip.TestSiteVacc == 0 )	// Turn off vacc, avoid the pump noise.
				VaccOff(&m.OutSet.TestSiteVacc);
		}
		NextStatus();
		break;
	case enTestSiteRemoteSendMsg:
		{
		
		}
		NextStatus();
		break;
	case enTestSiteRemoteWaitCmd:
		{
		}
		NextStatus();
		break;
	///////////////////////////////
	// Test Site / Drop Alarm
	case enTestSiteICDropBackHome:		// Test site down to drop or contact position, but IC drop
		{
			m_iRunError = f.Motor.MotorRun(&m.m_Motor.Inserter, 
				( m.m_Align.TestSite.home + ( m.m_Offset.TestSite.home * m.m_Ratio.Inserter_GearRation ) + ( m.Setting.m_dTestSiteStandbyPosition * m.m_Ratio.Inserter_GearRation)), 
				false, m.TimerSetting.iMotorRunTimeout );		
		}
		NextStatus();
		break;
	case enTestSiteICDropAlarm:			// Test site back home, alarm it
		{
		
		}
		NextStatus();
		break;

	///////////////////////////////
	// Test Site / Remote Control
	case enTestSiteRemoteCtrl:			// Test site in remote control
		{
		
		}
		NextStatus();
		break;
	case enTestSiteRemoteStandy:		//Test site in remote control standby
		{
			// Send Message to dialog
			RemoteControlMessageICReady();
		}
		NextStatus();
		break;
	case enTestSiteRemoteRelease:		// Test site in remote control Release
		{
			// Send Message to dialog
			RemoteControlMessageReleaseIC();
		}
		NextStatus();
		break;
	///////////////////////////////
	// Test Site / Wait Heater
	case enTestSiteHeaterStart:			// Test Site Wait Heater
		NextStatus();
		break;
	case enTestSiteHeaterWait:			// Test Site Wait 
		NextStatus();
		break;
	case enTestSiteHeaterEnd:			// Test Site Wait End
		NextStatus();
		break;
	///////////////////////////////
	// Test Site / Testing
	case enTestSiteTestStart:			// Test Start
		{
		}
		NextStatus();
		break;
	case enTestSiteTesting:				// Testing 
		{
		}
		NextStatus();
		break;
	case enTestSiteTestEnd:				// Test End
		{
		}
		NextStatus();
		break;
	case enTestSiteYield:				// Test Yield Control
		{
		}
		NextStatus();
		break;
	///////////////////////////////
	// Test Site / Output 
	case enTestSiteVaccStart:			// Test Site ready turn on the vacc
		{

		}
		NextStatus();
		break;
	case enTestSiteVacc:				// Test Site turn on the vacc
		{
			if( m.YieldSetting.bDropMode == 1 )	// Drop Mode, We need to turn on the vacc
				m_TSZWithIC = Vacc( &m.OutSet.TestSiteVacc, &m.InStatus.TestSiteZVaccSensor, m.Timer.m_dInsertPick );

			if( m.TraySkip.TestSiteVacc == 0 ) // Test Site Turn off vacc
				m_TSZWithIC = Vacc( &m.OutSet.TestSiteVacc, &m.InStatus.TestSiteZVaccSensor, m.Timer.m_dInsertPick );
		}
		NextStatus();	
		break;
	case enTestSiteVaccEnd:				// Test Site turn on the vacc end 
		{
		}
		NextStatus();	
		break;
	case enTestSiteUpForPlace:			// Test Site up for place ic to shuttle output 
		{
			m_iRunError = f.Motor.MotorRun(&m.m_Motor.Inserter, 
				( m.m_Align.TestSite.home + 
				( m.m_Offset.TestSite.home * m.m_Ratio.Inserter_GearRation ) +
				( m.Setting.m_dTestSiteStandbyPosition * m.m_Ratio.Inserter_GearRation )), 
				false, m.TimerSetting.iMotorRunTimeout );
		}
		NextStatus();	
		break;
	case enShuttleOutput:				// Shuttle move to pick place, test site can put ic to shuttle 
		{
			ShuttleMovePickPlace();
			f.Wait( m.TimerSetting.iShuttleStableTime );
		}
		NextStatus();	
		break;
	case enTestSitePlace:				// Test Site down to place IC to shuttle 
		{
			m_iRunError = f.Motor.MotorRun(&m.m_Motor.Inserter, 
				m.m_Align.TestSite.place + ( m.m_Offset.TestSite.place * m.m_Ratio.Inserter_GearRation ), 
				false, m.TimerSetting.iMotorRunTimeout );
		}
		NextStatus();		
		break;
	case enTestSitePlaceBlow:			// Test Site turn on the blow 
		{
			m_TSZWithIC = Blow( &m.OutSet.TestSiteVacc, &m.OutSet.TestSiteBlow,
				&m.InStatus.TestSiteZVaccSensor, m.Timer.m_dInsertPuff );
		}
		NextStatus();
		break;
	case enTestSiteUpForOut:			// Test Up for shuttle move home, Arm can pick ic from shuttle
		{
			m_iRunError = f.Motor.MotorRun(&m.m_Motor.Inserter, 
				( m.m_Align.TestSite.home + 
				( m.m_Offset.TestSite.home * m.m_Ratio.Inserter_GearRation ) + 
				( m.Setting.m_dTestSiteStandbyPosition  * m.m_Ratio.Inserter_GearRation )), 
				false, m.TimerSetting.iMotorRunTimeout );
		}
		NextStatus();	
		break;
	case enShuttleHomeForOutput:		// Shuttle move to home
		{
			ShuttleMoveHome();
			f.Wait( m.TimerSetting.iShuttleStableTime );
		}
		NextStatus();	
		break;
	///////////////////////////////
	// Test Site CCD Socket 
	case enTestSiteCCDSocketStart:		// CCD Socket Start
		{
		}
		NextStatus();
		break;
	case enTestSiteCCDSocketGrab:		// CCD Grab
		{
		}
		NextStatus();
		break;
	case enTestSiteCCDSocketMatch:		// CCD Match
		{
		}
		NextStatus();
		break;
	case enTestSiteCCDSocketMatchEnd:	// CCD Match End (Check Error or not )
		{
		}
		NextStatus();
		break;
	case enTestSiteCCDSocketEnd:		// CCD Socket End
		{
		}
		NextStatus();
		break;

	///////////////////////////////	
	// Error status
	case enShuttleHomeError:			// Shuttle move to home fail	
		NextStatus();
		break;
	case enShuttleInputError:			// Shuttle move to pick fail	
		NextStatus();
		break;
	case enTestSiteUpForContactError:	// Test Site Pick IC fail ( pick form shuttle input )
		NextStatus();
		break;
	case enShuttleHomeForContactError:	// Shuttle move to Home fail.
		NextStatus();
		break;
	case enShuttleOutputError:			// Shuttle move to place fail.
		NextStatus();
		break;
	case enShuttleHomeForOutputError:	// Shuttle move to home fail.
		NextStatus();
		break;
	case enTestSiteUpForPlaceError:		// Test Site Pick IC fail ( pick form socket )
		NextStatus();
		break;
	case enShuttleInputJamError:		// Shuttle move to input, then check jam fail
		NextStatus();
		break;
	case enTestSiteICDropError:			// Test Site IC Drop
		NextStatus();
		break;
	///////////////////////////////	
	// Error status (Yield Control)
	case enTesYieldContFailError:
		NextStatus();
		break;
	case enTesYieldYieldRateError:
		NextStatus();
		break;
	default:
		CheckRestart();
		break;
	}
}

void CThInserter::CheckRestart()
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
bool CThInserter::IsPause()
{
	if((m_bStatus & 0x1) || m_bStatus == enIdle)
		return true;
	else
		return false;
}
void CThInserter::NextStatus()
{
	if(m_iRunError != enCodeRunOK)
	{
		m.Info.iStatus = theApp.enUninitial;
		m.Err.Inserter.Code = m_iRunError;

		// Jim 建議強迫指定到 Idle 避免又回到原狀態再繼續執行
		m_bStatus = enIdle;
		m_iRunError = enCodeRunOK;
	}

	if( f.IsPause())
		m_bStatus = m_bStatus | 0x1;

	// here for change status
	switch(m_bStatus)
	{
	case enInitialize:
		m_lRemoteStatus = enNoDevice;
		f.CWinMessage( "TestSiteS:enInitialize", theApp.enDTestSite );
		m_bStatus = enIdle;
		break;
	case enIdle:	
		{
			m_lRemoteStatus = enNoDevice;
			if( ( m.Info.iStatus == theApp.enCycle 
				|| m.Info.iStatus == theApp.enOneCycle 
				|| m.Info.iStatus == theApp.enOverride ) 
				&& m_bInitialized )
			{
				m_bStatus = enShuttleHome;
			}
			else
				m_bStatus = enIdle;
		}
		break;
	///////////////////////////////
	case enShuttleHome:
		f.CWinMessage( "TestSiteS:enShuttleHome", theApp.enDTestSite );
		{
			m_lRemoteStatus = enNoDevice;
			if( CheckShuttleHomeOK() )
			{
				m.InterLock.ShuttleHome = true;
				m_bStatus = enShuttleHomeStandy;
			}
			else
			{
				// Ops: Shuttle Move to Home Fail.
				m.Err.Inserter.Code = enCodeShuttleMoveToHomeFail;
				m_bStatus = enShuttleHomeError;
				m_lRemoteStatus = enError;
			}
		}
		break;
	case enShuttleHomeStandy:			// Shuttle move to home standy
		f.CWinMessage( "TestSiteS:enShuttleHomeStandy", theApp.enDTestSite );
		{
			m_lRemoteStatus = enNoDevice;
			if( m.InterLock.ShuttleInputICOK && m.InterLock.ShuttleWithIC )
			{
				m.InterLock.ShuttleInputICOK = false;
				m.InterLock.ShuttleHome = false;
				m_bStatus = enShuttleInput;
			}
			else
				; // 
		}
		break;

	case enShuttleRestart:				// Test Pick From Socket Fail. Re-set it, ask Arm move to input again
		f.CWinMessage( "TestSiteS:enShuttleRestart", theApp.enDTestSite );
		{
			m_lRemoteStatus = enNoDevice;
			m.InterLock.ShuttleResetInput = true;
			m_bStatus = enShuttleHomeStandy;
		}
		break;
	case enShuttleRestartDrop:			// Test Down Place to Socket. But IC Missing
		f.CWinMessage( "TestSiteS:enShuttleRestartDrop", theApp.enDTestSite );
		{
			m_lRemoteStatus = enNoDevice;
			m.InterLock.ShuttleResetInput = true;
			m_bStatus = enShuttleHomeStandy;
		}
		break;
	///////////////////////////////
	case enShuttleInput:				// Shuttle move to input 
		f.CWinMessage( "TestSiteS:enShuttleInput", theApp.enDTestSite );
		{
			m_lRemoteStatus = enNoDevice;
			if( CheckShuttlePickPlaceOK() )
			{
//				m_bStatus = enShutlleInputEnd;
				m_bStatus = enShuttleInputJam;
			}
			else
			{
				// Ops: Shuttle Move to Pick Fail
				m.Err.Inserter.Code = enCodeShuttleMoveToPickFail;
				m_bStatus = enShuttleInputError;
				m_lRemoteStatus = enError;
			}
		}
		break;
	case enShuttleInputJam:				// Shuttle move to input, and check jam again
		f.CWinMessage( "TestSiteS:enShuttleInputJam", theApp.enDTestSite );
		{
			m_lRemoteStatus = enNoDevice;
			if( CheckShuttleInputJam() )
			{
				if( m.Setting.m_bByPassShuttleAlarm )
				{
					// Jam Fail but bypass
					m_bStatus = enShutlleInputEnd;
				}
				else
				{
					// Ops: Shuttle Move to input(under test site)
					m.Err.Inserter.Code = enCodeShuttleInputJamFail;
					m_bStatus = enShuttleInputJamError;
					m_lRemoteStatus = enError;
				}
			}
			else
			{
				m_bStatus = enShutlleInputEnd;
			}
		}
		break;
	case enShutlleInputEnd:				// Shuttle move to input end
		f.CWinMessage( "TestSiteS:enShutlleInputEnd", theApp.enDTestSite );
		{
			m_lRemoteStatus = enNoDevice;
			m_bStatus = enTestSitePickForVacc;
		}
		break;
	//
	case enTestSitePickForVacc:			// Test site down to pick
		f.CWinMessage( "TestSiteS:enTestSitePickForVacc", theApp.enDTestSite );
		{
			m_lRemoteStatus = enNoDevice;
			m_bStatus = enTestSiteVaccForUp;
		}
		break;
	case enTestSiteVaccForUp:			// Test site turn on the vacc
		f.CWinMessage( "TestSiteS:enTestSiteVaccForUp", theApp.enDTestSite );
		{
			if( m_TSZWithIC )
				UPHTSDataAdd();
		m_lRemoteStatus = enNoDevice;
			m_bStatus = enTestSiteUpForContact;
		}
		break;
	case enTestSiteUpForContact:		// Test site up for contact
		f.CWinMessage( "TestSiteS:enTestSiteUpForContact", theApp.enDTestSite );
		{
			m_TSZWithIC = CheckTSZVaccSensor();
			m_lRemoteStatus = enDeviceInTestsite;
			if( m_TSZWithIC )
			{
				// 吸到 IC 後.!
				m.InterLock.ShuttleWithIC = false;
				m_bStatus = enShuttleHomeForContact;
			}
			else
			{
				if( m.Setting.m_bByPassTestVacc == 1 )
				{
					// 吸到 IC 後.!
					m.InterLock.ShuttleWithIC = false;
					m_bStatus = enShuttleHomeForContact;
				}
				else
				{					
					// Ops: Test Site Pick IC from shuttle input
					m.Err.Inserter.Code = enCodeTestPickICFromSHFail;
					m_bStatus = enTestSiteUpForContactError;
					m_lRemoteStatus = enError;
				}
			}
		}
		break;
	case enShuttleHomeForContact:		// Shuttle move to home
		f.CWinMessage( "TestSiteS:enShuttleHomeForContact", theApp.enDTestSite );
		{
			m_lRemoteStatus = enDeviceInTestsite;
			if( CheckShuttleHomeOK() )
			{		
				m.InterLock.ShuttleHome = true;
				if( m.Setting.m_bEnableCCDSocket == 1 && m.m_TestSetting.m_CCDSocketUse == 1 )
					m_bStatus = enTestSiteCCDSocketStart;
				else
					m_bStatus = enTestSiteDownForContact;
			}
			else
			{
				// Ops: Shuttle Move to Home Fail.
				m.Err.Inserter.Code = enCodeShuttleMoveToHomeFail;
				m_bStatus = enShuttleHomeForContactError;
				m_lRemoteStatus = enError;
			}
		}
		break;
	case enTestSiteDownForContact:		// Test site down to place ic to socket (fast)
		f.CWinMessage( "TestSiteS:enTestSiteDownForContact", theApp.enDTestSite );
		{
			if(m.YieldSetting.bDropMode == 1)
				m_bStatus = enTestSiteToDrop;
			else
				m_bStatus = enTestSiteContact;
				m_lRemoteStatus = enDeviceInTestsite;
		}
		break;
	// 1.0Ah
	// Remove this and re-build new one (For IC drop)
	/*
	case enTestSiteToDrop:				// Test site drop mode
		f.CWinMessage( "TestSiteS:enTestSiteToDrop", theApp.enDTestSite );
		{
			m_bStatus = enTestSiteDropDevice;
		}
		break;
	*/
	case enTestSiteToDrop:				// Test site drop mode
		f.CWinMessage( "TestSiteS:enTestSiteToDrop", theApp.enDTestSite );
		{
			if( GetICDropInd() )
			{
				SetICDropInd( false );
				VaccOff(&m.OutSet.TestSiteVacc);

				// Move the Test site to home
				m_bStatus = enTestSiteICDropBackHome;
			}
			else
				m_bStatus = enTestSiteDropDevice;

			m_lRemoteStatus = enDeviceInTestsite;
		}
		break;
	case enTestSiteDropDevice:
		f.CWinMessage( "TestSiteS:enTestSiteDropDevice", theApp.enDTestSite );
		{
			m_bStatus = enTestSiteContact;
			m_lRemoteStatus = enDeviceInTestsite;
		}
		break;
	// 1.0Ah
	// Remove this and re-build new
	/*
	case enTestSiteContact:				// Test site contact 
		f.CWinMessage( "TestSiteS:enTestSiteContact", theApp.enDTestSite );
		{
			SaveTSCounter();
			if( m.RemoteInterlock.IsRemoteControlMode )
			{
				// Remote Enter Point
				m_bStatus = enTestSiteRemoteCtrl;
			}
			else
			{	
				// Cycle Enter Point
				m_bStatus = enTestStteContactEnd;
			}
		}
		break;
	*/
	case enTestSiteContact:				// Test site contact 
		f.CWinMessage( "TestSiteS:enTestSiteContact", theApp.enDTestSite );
		{
			SaveTSCounter();
			if( m.RemoteInterlock.IsRemoteControlMode )
			{
				// Remote Enter Point
				m_bStatus = enTestSiteRemoteCtrl;
			}
			else if( GetRemoteCoordRequest() )
			{
				// Remote SLT Protocol Enter Point
//				m_bStatus = enTestSiteRemoteWaitCmd;
				m_bStatus = enTestSiteRemoteSendMsg;				
			}
			else
			{	
				if( GetICDropInd() )
				{
					SetICDropInd( false );
					VaccOff(&m.OutSet.TestSiteVacc);
					
					// Move the Test site to home
					m_bStatus = enTestSiteICDropBackHome;
				}
				else
				{
					// Cycle Enter Point
					m_bStatus = enTestStteContactEnd;
				}
			}
			m_lRemoteStatus = enDeviceInSocket;
		}
		break;
	case enTestStteContactEnd:
		f.CWinMessage( "TestSiteS:enTestStteContactEnd", theApp.enDTestSite );
		{
			// Cycle Enter Point
			if( f.HeaterOnNeed() )
				m_bStatus = enTestSiteHeaterStart;
			else
				m_bStatus = enTestSiteTestStart;

				m_lRemoteStatus = enDeviceInSocket;
		}
		break;
	case enTestSiteRemoteSendMsg:
		f.CWinMessage( "TestSiteS:enTestSiteRemoteSendMsg", theApp.enDTestSite );
		{
			f.RemoteSetCoordnationDone();
			m_bStatus = enTestSiteRemoteWaitCmd;
			m_lRemoteStatus = enDeviceInSocket;
		}
		break;
	case enTestSiteRemoteWaitCmd:
		f.CWinMessage( "TestSiteS:enTestSiteRemoteWaitCmd", theApp.enDTestSite );
		{
			// Wait..
			if( !GetRemoteCoordRequest() )
				m_bStatus = enTestSiteVaccStart;
			m_lRemoteStatus = enDeviceInSocket;
		}
		break;

	///////////////////////////////
	// Test Site / Drop Alarm
	case enTestSiteICDropBackHome:		// Test site down to drop or contact position, but IC drop
		f.CWinMessage( "TestSiteS:enTestSiteICDropBackHome", theApp.enDTestSite );
		{
			m_bStatus = enTestSiteICDropAlarm;
			m_lRemoteStatus = enDeviceInSocket;
		}
		break;
	case enTestSiteICDropAlarm:			// Test site back home, alarm it
		f.CWinMessage( "TestSiteS:enTestSiteICDropAlarm", theApp.enDTestSite );
		{
			m.Err.Inserter.Code = enCodeTestSiteMoveICMissing;
			m_bStatus = enTestSiteICDropError;
			m_lRemoteStatus = enError;
		}
		break;
		

	///////////////////////////////
	// Test Site / Remote Control
	case enTestSiteRemoteCtrl:			// Test site in remote control
		f.CWinMessage( "TestSiteS:enTestSiteRemoteCtrl", theApp.enDTestSite );
		{
			m_bStatus = enTestSiteRemoteStandy;
			m_lRemoteStatus = enDeviceInSocket;
		}
		break;
	case enTestSiteRemoteStandy:		//Test site in remote control standby
		f.CWinMessage( "TestSiteS:enTestSiteRemoteStandy", theApp.enDTestSite );
		{
			if( m.RemoteInterlock.ReleaseIC )
				m_bStatus = enTestSiteRemoteRelease;

			else
			{
				// Wait here for release IC...
			}
			m_lRemoteStatus = enDeviceInSocket;
		}
		break;
	case enTestSiteRemoteRelease:		// Test site in remote control Release
		f.CWinMessage( "TestSiteS:enTestSiteRemoteRelease", theApp.enDTestSite );
		{
			m_bStatus = enTestSiteVaccStart;
			m_lRemoteStatus = enDeviceInSocket;
			// Remote Control... byPass Testing...
		}
		break;

	///////////////////////////////
	// Test Site / Wait Heater
	case enTestSiteHeaterStart:			// Test Site Wait Heater
		f.CWinMessage( "TestSiteS:enTestSiteHeaterStart", theApp.enDTestSite );
		{
			SetHeaterStart();
			m_bStatus = enTestSiteHeaterWait;
			m_lRemoteStatus = enDeviceInSocket;
		}
		break;
	case enTestSiteHeaterWait:			// Test Site Wait 
		f.CWinMessage( "TestSiteS:enTestSiteHeaterWait", theApp.enDTestSite );
		{
			if( WaitHeaterSoakOK() )
			{
				m_bStatus = enTestSiteHeaterEnd;
				m_lRemoteStatus = enDeviceInSocket;
			}
			else
			{
				// Wait Soak Time OK..
			}
		}
		break;
	case enTestSiteHeaterEnd:			// Test Site Wait End
		f.CWinMessage( "TestSiteS:enTestSiteHeaterEnd", theApp.enDTestSite );
		{
			ClearHeaterValue();
			m_bStatus = enTestSiteTestStart;
			m_lRemoteStatus = enDeviceInSocket;
		}
		break;

	///////////////////////////////
	// Test Site / Testing
	case enTestSiteTestStart:			// Test Start
		f.CWinMessage( "TestSiteS:enTestSiteTestStart", theApp.enDTestSite );
		{
			theApp.m_tTester.TesterLog = theApp.m_tInserter.TestSiteLog;
			theApp.m_tInserter.ClearTestSiteLog();

			m.InterLock.TestingGo	= true;
			m.InterLock.Testing		= true;
			m.InterLock.TestingOK	= false;

			m_bStatus = enTestSiteTesting;
			m_lRemoteStatus = enTesting;
		}
		break;
	case enTestSiteTesting:				// Testing 
		f.CWinMessage( "TestSiteS:enTestSiteTesting", theApp.enDTestSite );
		{
			if( m.InterLock.TestingOK )
			{
				m.InterLock.TestingOK = false;
				m_bStatus = enTestSiteTestEnd;
				m_lRemoteStatus = enTesting;
			}
			else
				;	// Wait for testing complete
		}
		break;
	case enTestSiteTestEnd:				// Test End
		f.CWinMessage( "TestSiteS:enTestSiteTestEnd", theApp.enDTestSite );
		{
			m_bStatus = enTestSiteYield;
			m_lRemoteStatus = enTesting;
		}
		break;
	case enTestSiteYield:				// Test Yield Control
		f.CWinMessage( "TestSiteS:enTestSiteYield", theApp.enDTestSite );
		{
			if( IsYieldContinueFail() )
			{
				m.Err.Inserter.Code = enCodeContinueFail;
				m_bStatus = enTesYieldContFailError;
			}
			else if( IsYieldFailRateFail() )
			{
				m.Err.Inserter.Code = enCodeLowYieldFail;
				m_bStatus = enTesYieldYieldRateError;				
			}
			else if( IsYieldRetestNeed() )
			{
				// Retest
				m_bStatus = enTestSiteTestStart;
			}
			else
			{
				ClearYieldControlTested();	// test done
				theApp.m_tTester.FTSetWaitSendStartDelay( false );
				m_bStatus = enTestSiteVaccStart;
			}
			m_lRemoteStatus = enTesting;
		}
		break;
	///////////////////////////////
	// Test Site / Output 
	case enTestSiteVaccStart:			// Test Site ready turn on the vacc
		f.CWinMessage( "TestSiteS:enTestSiteVaccStart", theApp.enDTestSite );
		{
			m_bStatus = enTestSiteVacc;
			m_lRemoteStatus = enDeviceOutSocket;
		}
		break;
	case enTestSiteVacc:				// Test Site turn on the vacc
		f.CWinMessage( "TestSiteS:enTestSiteVacc", theApp.enDTestSite );
		{
			m_bStatus = enTestSiteVaccEnd;
			m_lRemoteStatus = enDeviceOutSocket;
		}	
		break;
	case enTestSiteVaccEnd:				// Test Site turn on the vacc end 
		f.CWinMessage( "TestSiteS:enTestSiteVaccEnd", theApp.enDTestSite );
		{
			m_bStatus = enTestSiteUpForPlace;
			m_lRemoteStatus = enDeviceOutSocket;
		}
		break;
	case enTestSiteUpForPlace:			// Test Site up for place ic to shuttle output 
		f.CWinMessage( "TestSiteS:enTestSiteUpForPlace", theApp.enDTestSite );
		{
			m_TSZWithIC = CheckTSZVaccSensor();
			m_lRemoteStatus = enDeviceOutSocket;
			if(m.m_TestInterface.m_bRemoteRetest > 0)
			{
				m_bStatus = enTestSiteDownForContact;
				m.m_TestInterface.m_bRemoteRetest--;
			
			}
			else if( m_TSZWithIC )
			{
				m.InterLock.ShuttleHome = false;
				m_bStatus = enShuttleOutput;
			}
			else
			{
				if( m.Setting.m_bByPassTestVacc == 1 )
				{
					m.InterLock.ShuttleHome = false;
					m_bStatus = enShuttleOutput;
				}
				else
				{					
					// Ops: Test Site Pick IC fail from socket 
					m.Err.Inserter.Code = m.Err.Inserter.Code = enCodeTestPickICFromSocketFail;
					m_bStatus = enTestSiteUpForPlaceError;
					m_lRemoteStatus = enError;
				}
			}
		}
		break;
	case enShuttleOutput:				// Shuttle move to pick, test site can put ic to shuttle 
		f.CWinMessage( "TestSiteS:enShuttleOutput", theApp.enDTestSite );
		{
			m_lRemoteStatus = enDeviceOutSocket;
			if( CheckShuttlePickPlaceOK() )
			{
				m_bStatus = enTestSitePlace;
			}
			else
			{
				// Ops: Shuttle Move to place fail.
				m.Err.Inserter.Code = enCodeShuttleMoveToPlaceFail;
				m_bStatus = enShuttleOutputError;
				m_lRemoteStatus = enError;
			}
		}	
		break;
	case enTestSitePlace:				// Test Site down to place IC to shuttle 
		f.CWinMessage( "TestSiteS:enTestSitePlace", theApp.enDTestSite );
		{
			m_bStatus = enTestSitePlaceBlow;
			m_lRemoteStatus = enDeviceOutSocket;
		}
		break;
	case enTestSitePlaceBlow:			// Test Site turn on the blow 
		f.CWinMessage( "TestSiteS:enTestSitePlaceBlow", theApp.enDTestSite );
		{
			m_bStatus = enTestSiteUpForOut;
			m_lRemoteStatus = enDeviceOutSocket;
		}
		break;
	case enTestSiteUpForOut:			// Test Up for shuttle move home, Arm can pick ic from shuttle
		f.CWinMessage( "TestSiteS:enTestSiteUpForOut", theApp.enDTestSite );
		{
			m_bStatus = enShuttleHomeForOutput;
			m_lRemoteStatus = enDeviceOutSocket;
		}
		break;
	case enShuttleHomeForOutput:		// Shuttle move to home
		f.CWinMessage( "TestSiteS:enShuttleHomeForOutput", theApp.enDTestSite );
		{
			if( CheckShuttleHomeOK() )
			{
				m.InterLock.ShuttleHome = true;
				m.InterLock.ShuttleOutputICOK = true;
				m_bStatus = enShuttleHome;
				m_lRemoteStatus = enNoDevice;
			}
			else
			{
				// Ops: Shuttle Move to Home 
				m.Err.Inserter.Code = enCodeShuttleMoveToPlaceFail;
				m_bStatus = enShuttleHomeForOutputError;
				m_lRemoteStatus = enError;
			}
		}	
		break;

		///////////////////////////////
		// Test Site CCD Socket 
	case enTestSiteCCDSocketStart:		// CCD Socket Start
		f.CWinMessage( "TestSiteS:enTestSiteCCDSocketStart", theApp.enDTestSite );
		{
			m_bStatus = enTestSiteCCDSocketGrab;
			m_lRemoteStatus = enDeviceInTestsite;
		}
		break;
	case enTestSiteCCDSocketGrab:		// CCD Grab
		f.CWinMessage( "TestSiteS:enTestSiteCCDSocketGrab", theApp.enDTestSite );
		{
			m_bStatus = enTestSiteCCDSocketMatch;
			m_lRemoteStatus = enDeviceInTestsite;
		}
		break;
	case enTestSiteCCDSocketMatch:		// CCD Match
		f.CWinMessage( "TestSiteS:enTestSiteCCDSocketMatch", theApp.enDTestSite );
		{
			m_bStatus = enTestSiteCCDSocketMatchEnd;
			m_lRemoteStatus = enDeviceInTestsite;
		}
		break;
	case enTestSiteCCDSocketMatchEnd:	// CCD Match End (Check Error or not )
		f.CWinMessage( "TestSiteS:enTestSiteCCDSocketMatchEnd", theApp.enDTestSite );
		{
			m_bStatus = enTestSiteCCDSocketEnd;
			m_lRemoteStatus = enDeviceInTestsite;
		}
		break;
	case enTestSiteCCDSocketEnd:		// CCD Socket End
		f.CWinMessage( "TestSiteS:enTestSiteCCDSocketEnd", theApp.enDTestSite );
		{
			m_bStatus = enTestSiteDownForContact;
			m_lRemoteStatus = enDeviceInTestsite;
		}
		break;

	///////////////////////////////	
	// Error status
	case enShuttleHomeError:			// Shuttle move to home fail	
		f.CWinMessage( "TestSiteS:enShuttleHomeError", theApp.enDTestSite );
		{
			if( m.Err.Inserter.Code == 0 )
			{
				if( m.Err.Inserter.Result == theApp.ActionRetry )
				{
					// Retry 就再回 Home 一次
					m_bStatus = enShuttleHome;
				}
				else if( m.Err.Inserter.Result == theApp.ActionSkip )
				{
					// Skip 就再回 Home 一次, 因為不得略過
					m_bStatus = enShuttleHome;
				}
				else
					;	// Nerver be here.
			}
		}		
		break;
	case enShuttleInputError:			// Shuttle move to home fail	
		f.CWinMessage( "TestSiteS:enShuttleInputError", theApp.enDTestSite );
		{
			if( m.Err.Inserter.Code == 0 )
			{
				if( m.Err.Inserter.Result == theApp.ActionRetry )
				{
					// Retry 就再回 Pick 一次
					m_bStatus = enShuttleInput;
				}
				else if( m.Err.Inserter.Result == theApp.ActionSkip )
				{
					// Skip 就再回 Pick 一次, 因為不得略過
					m_bStatus = enShuttleInput;
				}
				else
					;	// Nerver be here.
			}
		}		
		break;
	case enTestSiteUpForContactError:
		f.CWinMessage( "TestSiteS:enTestSiteUpForContactError", theApp.enDTestSite );
		{
			if( m.Err.Inserter.Code == 0 )
			{
				if( m.Err.Inserter.Result == theApp.ActionRetry )
				{
					// Retry 就再下去吸一次
					m_bStatus = enTestSitePickForVacc;
				}
				else if( m.Err.Inserter.Result == theApp.ActionSkip )
				{
					// Skip 要重新入料
					m.InterLock.ShuttleWithIC = false;
					m.InterLock.ShuttleResetInput = true;
					m_bStatus = enShuttleHome;
				}
				else if( m.Err.Inserter.Result == theApp.ActionTSSkip )
				{
					// Skip 要重新入料
					m.InterLock.ShuttleWithIC = false;
					m.InterLock.ShuttleResetInput = true;
					m_bStatus = enShuttleHome;				
				}
				else
					; // Nerver be here.
			}
		}
		break;
	case enShuttleHomeForContactError:
		f.CWinMessage( "TestSiteS:enShuttleHomeForContactError", theApp.enDTestSite );
		{
			if( m.Err.Inserter.Code == 0 )
			{
				if( m.Err.Inserter.Result == theApp.ActionRetry )
				{
					// Retry 就重新再回一次 Home
					m_bStatus = enShuttleHomeForContact;
				}
				else if( m.Err.Inserter.Result == theApp.ActionSkip )
				{
					// Skip 就重新再回一次 Home
					m_bStatus = enShuttleHomeForContact;
				}
				else
					; // Nerver be here.
			}
		}
		break;
	case enShuttleOutputError:
		f.CWinMessage( "TestSiteS:enShuttleOutputError", theApp.enDTestSite );
		{
			if( m.Err.Inserter.Code == 0 )	
			{
				if( m.Err.Inserter.Result == theApp.ActionRetry )
				{
					m_bStatus = enShuttleOutput;
				}
				else if( m.Err.Inserter.Result == theApp.ActionSkip )
				{
					m_bStatus = enShuttleOutput;
				}
				else
					; // Nerver be here
			}
		}
		break;
	case enShuttleHomeForOutputError:
		f.CWinMessage( "TestSiteS:enShuttleHomeForOutputError", theApp.enDTestSite );
		{
			if( m.Err.Inserter.Code == 0 )	
			{
				if( m.Err.Inserter.Result == theApp.ActionRetry )
				{
					m_bStatus = enShuttleHomeForOutput;
				}
				else if( m.Err.Inserter.Result == theApp.ActionSkip )
				{
					m_bStatus = enShuttleHomeForOutput;
				}
				else
					; // Nerver be here
			}
		}
		break;
	case enTestSiteUpForPlaceError:
		f.CWinMessage( "TestSiteS:enTestSiteUpForPlaceError", theApp.enDTestSite );
		{
			if( m.Err.Inserter.Code == 0 )	
			{
				if( m.Err.Inserter.Result == theApp.ActionRetry )
				{
					m_bStatus = enShuttleRestart;
				}
				else if( m.Err.Inserter.Result == theApp.ActionSkip )
				{
					m_bStatus = enShuttleRestart;
				}
				else if( m.Err.Inserter.Result == theApp.ActionTSSkip )
				{
					m_bStatus = enShuttleRestart;
				}
				else
					; // Nerver be here
			}
		}
		break;
	case enShuttleInputJamError:
		f.CWinMessage( "TestSiteS:enShuttleInputJamError", theApp.enDTestSite );
		{
			if( m.Err.Inserter.Code == 0 )	
			{
				if( m.Err.Inserter.Result == theApp.ActionRetry )
				{
					// Retry 要再檢查一次 Jam
					m_bStatus = enShuttleInputJam;
				}
				else if( m.Err.Inserter.Result == theApp.ActionSkip )
				{
					// Skip 要重新入料
					m.InterLock.ShuttleWithIC = false;
					m.InterLock.ShuttleResetInput = true;
					m_bStatus = enShuttleHome;
				}
				else if( m.Err.Inserter.Result == theApp.ActionTSSkip )
				{
					// Skip 要重新入料
					m.InterLock.ShuttleWithIC = false;
					m.InterLock.ShuttleResetInput = true;
					m_bStatus = enShuttleHome;
				}
				else
					;	// Nerver be here
			}
		}
		break;
	case enTestSiteICDropError:			// Test Site IC Drop
		f.CWinMessage( "TestSiteS:enTestSiteICDropError", theApp.enDTestSite );
		{
			if( m.Err.Inserter.Code == 0 )	
			{
				if( m.Err.Inserter.Result == theApp.ActionRetry )
				{
					// Retry 要重新入料
					m_bStatus = enShuttleRestartDrop;
				}
				else if( m.Err.Inserter.Result == theApp.ActionSkip )
				{
					// Skip 要重新入料
					m_bStatus = enShuttleRestartDrop;
				}
				else if( m.Err.Inserter.Result == theApp.ActionTSSkip )
				{
					// Skip 要重新入料
					m_bStatus = enShuttleRestartDrop;
				}
				else
					; // Nerver be here
			}
		}
		break;

	///////////////////////////////	
	// Error status (Yield Control)
	case enTesYieldContFailError:
		f.CWinMessage( "TestSiteS:enTesYieldContFailError", theApp.enDTestSite );
		if( m.Err.Inserter.Code == 0 )	
		{
			m.m_YieldCtrl.m_lContinueFail = 0; // Clear Value
			if( m.Err.Inserter.Result == theApp.ActionRetry )
			{
				m_bStatus = enTestSiteVaccStart;
			}
			else if( m.Err.Inserter.Result == theApp.ActionSkip )
			{
				m_bStatus = enTestSiteVaccStart;
			}
			else
				; // Nerver be here
		}			
		break;
	case enTesYieldYieldRateError:
		f.CWinMessage( "TestSiteS:enTesYieldYieldRateError", theApp.enDTestSite );
		if( m.Err.Inserter.Code == 0 )	
		{
			m.m_YieldCtrl.m_iPFArray.RemoveAll();
			m.m_YieldCtrl.m_dFailRate = 0; // Clear Value
			if( m.Err.Inserter.Result == theApp.ActionRetry )
			{
				m_bStatus = enTestSiteVaccStart;
			}
			else if( m.Err.Inserter.Result == theApp.ActionSkip )
			{
				m_bStatus = enTestSiteVaccStart;
			}
			else
				; // Nerver be here
		}			
		break;

	}// switch..


	if(f.IsPause())
	{
		if(m_bStatus != enIdle)
			m_bStatus = m_bStatus | 0x1;
		return;
	}
}
bool CThInserter::IsYieldRetestNeed()
{
	bool bNeedRetest = false;

	if( m.YieldSetting.iRetestCount != 0 )
	{
		if( IsYieldPassFail( TestSiteLog.csCode ) )
		{
			// Pass		
		}	
		else
		{
			// Fail
			if( m.m_YieldCtrl.m_lTested >= m.YieldSetting.iRetestCount )
			{
				// No Need
			}
			else
			{
				// Need
				m.m_YieldCtrl.m_lTested++;
				bNeedRetest = true;
			}
		}
	}

	return bNeedRetest;
}
void CThInserter::ClearYieldControlTested()
{
	m.m_YieldCtrl.m_lTested = 0;
}
bool CThInserter::IsYieldFailRateFail()
{
	bool bFailRateFail = false;

	if( m.YieldSetting.bYieldControlEnable == 1 )
	{
		int iSize = m.m_YieldCtrl.m_iPFArray.GetSize();
		if( iSize < m.YieldSetting.iYieldWindow )
		{
			// lower then window
			int m_iPF = 0;
			if( IsYieldPassFail( TestSiteLog.csCode ) )
				m_iPF = 1; // Pass
			else
				m_iPF = 0; // Fail

			m.m_YieldCtrl.m_iPFArray.Add(m_iPF); 
		}
		else
		{
			// high then window
			int m_iPF = 0;
			if( IsYieldPassFail( TestSiteLog.csCode ) )
				m_iPF = 1;
			else
				m_iPF = 0;
			
			m.m_YieldCtrl.m_iPFArray.RemoveAt(0);
			m.m_YieldCtrl.m_iPFArray.Add(m_iPF);
		}

		// Check Rate
		int iCSize = m.m_YieldCtrl.m_iPFArray.GetSize();
		int iPF = 0;
		double dTotalFail = 0;
		for(int i=0;i<iCSize;i++)
		{
			iPF = m.m_YieldCtrl.m_iPFArray.GetAt(i);
			if(iPF == 0)
				dTotalFail++;
		}

		if( dTotalFail != 0 && iCSize != 0 )
		{
			m.m_YieldCtrl.m_dFailRate = dTotalFail / iCSize;

			if( m.m_YieldCtrl.m_dFailRate > ( m.YieldSetting.dYieldLimit / 100.) )
				bFailRateFail = true;
		}
	}

	return bFailRateFail;
}
bool CThInserter::IsYieldPassFail(CString csCode)
{
	bool bPassFail = true;
	CArray <tagBinMapping, tagBinMapping> YiledBinMap; // Bin Use
	YiledBinMap.Copy( m.BinMap );

	int iSize = YiledBinMap.GetSize();
	bool bFind = false;
	for(int i=0;i<iSize;i++)
	{
		if( YiledBinMap.GetAt(i).code == csCode )
		{
			bPassFail = YiledBinMap.GetAt(i).pass == true ? 1 : 0;
			bFind = true;
			break;
		}
	}

	if(!bFind)
		bPassFail = false; // Other

	return bPassFail;
}
bool CThInserter::IsYieldContinueFail()
{
	bool bContinueFail = false;
	if( m.YieldSetting.bContinueFailEnable == 1 )
	{
		if( IsYieldPassFail( TestSiteLog.csCode ) )
			m.m_YieldCtrl.m_lContinueFail = 0;
		else
			m.m_YieldCtrl.m_lContinueFail++;
		
		// Continue Fail > Setting Value
		if( m.m_YieldCtrl.m_lContinueFail >= m.YieldSetting.iFailCount )
			bContinueFail = true;
	}
	
	return bContinueFail;
}
void CThInserter::InitTorqueInitialLoad()
{
	if( m.Setting.m_bEnableTorqueStatus == 1 )
	{
		// 停一秒等 Torque 更新
		Sleep(1000);
		m.m_DriveMotorTorque.SetInitialLoad(0);
		m.m_DriveMotorTorque.SetForceTorqueRatio(m.m_TorqueStatusPar.dTorqueRation);
	}
}
// 1.0Ah
void CThInserter::InitICDropInd()
{
	ICDropInd = false;
}
void CThInserter::SetICDropInd(bool bInd)
{
	ICDropInd = bInd;
}
bool CThInserter::GetICDropInd()
{
	return ICDropInd;
}
void CThInserter::InitialMissionOnTheGo()
{
	m_bMissionOnTheGo = false;
}
void CThInserter::SetRemoteCoordRequest( bool bMissionGo )
{
	m_bMissionOnTheGo = bMissionGo;
}
bool CThInserter::GetRemoteCoordRequest()
{
	return m_bMissionOnTheGo;
}
void CThInserter::SetRemoteCoordRequestReturn( bool bMissionGo )
{
	m_bMissionOnTheGo = bMissionGo;
}
bool CThInserter::GetRemoteCoordRequestReturn()
{
	return m_bMissionOnTheGo;
}
int CThInserter::GetThreadMotionStatus()
{
	return m_bStatus;
}
int CThInserter::ExitInstance()
{
	TRACE("CThInserter\n");
	// TODO:  perform any per-thread cleanup here
	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(CThInserter, CWinThread)
	//{{AFX_MSG_MAP(CThInserter)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CThInserter message handlers
