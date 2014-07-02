// ThManualCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "deer.h"
#include "ThManualCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CThManualCtrl

IMPLEMENT_DYNCREATE(CThManualCtrl, CWinThread)

CThManualCtrl::CThManualCtrl()
{
	m_bStatus				= enIdle;	
	m_iRunError				= enCodeRunOK;
	m_bInitialized			= false;
	m_bInitialRequest		= false;

	//
	m_bRequestContact		= false;
	m_bRequestUp			= false;
	m_bRequestMove			= false;

	//
	m_TSZWithIC				= false;
}

CThManualCtrl::~CThManualCtrl()
{
	TRACE("~CThManualCtrl\n");
}

BOOL CThManualCtrl::InitInstance()
{
	f.IncraseThreadCount();
	m.ThStatus.ManualCtrl.times = 1;
	while(m.Info.bRunning)
	{
		m.ThStatus.ManualCtrl.times++;
		Running();
		Sleep(_Wait);
	}
	f.ReduceThreadCount();
	f.m_Log.AddLogEvent( "Thread Manual Finish" );
	
	return TRUE;
}
bool CThManualCtrl::VaccOff(unsigned char* Vacc)
{
	*Vacc = 0;		// Turn off vacuum.
	return true;
}
void CThManualCtrl::InitialStart()
{
	m_bInitialRequest = true;
}
void CThManualCtrl::Initialize()
{
	m_bInitialized = false;
	if( m.Info.iStatus != theApp.enInitial )
		return;
	// If not Initial. return this function. User want to stop.

	m.MotorStatus.ManualCtrl = "Initialing.";
	m.MotorStatus.ManualCtrl = "Manual OK.";
	m.MotorStatus.ManualCtrlInitialed = true;
	m.InterLock.ManualCtrlEnd = true;
	m_bInitialized = true;
}
void CThManualCtrl::InitialRequest()
{
	m_bRequestContact		= false;
	m_bRequestUp			= false;
	m_bRequestMove			= false;
}
void CThManualCtrl::RequestContact()
{
	m_bRequestContact		= true;
}
void CThManualCtrl::RequestUp()
{
	m_bRequestUp			= true;
}
void CThManualCtrl::RequestMove()
{
	m_bRequestMove			= true;
}
void CThManualCtrl::ManualContactCtDone()
{
	CString cs = _T("");
	::SendMessage( theApp.m_DlgManualContact->GetSafeHwnd(), 
		WM_MANUAL_CT_DONE,  (WPARAM)&cs , (LPARAM)&cs );
}
void CThManualCtrl::ManualContactUpDone()
{
	CString cs = _T("");
	::SendMessage( theApp.m_DlgManualContact->GetSafeHwnd(), 
		WM_MANUAL_UP_DONE,  (WPARAM)&cs , (LPARAM)&cs );

	::SendMessage( theApp.m_DlgManualContactRecover->GetSafeHwnd(), 
		WM_MANUAL_UP_DONE,  (WPARAM)&cs , (LPARAM)&cs );
}
void CThManualCtrl::ManualContactMvDone()
{
	CString cs = _T("");
	::SendMessage( theApp.m_DlgManualContact->GetSafeHwnd(), 
		WM_MANUAL_MV_DONE,  (WPARAM)&cs , (LPARAM)&cs );
}
void CThManualCtrl::Running()
{
	if(!m_bInitialized && m.Info.iStatus != theApp.enInitial)
	{
		m_bStatus = enIdle;
		return;
	}
	// If Handler status is Uninitial. We force it to return and keep m_bStatus in enIdle.
	// Notes : In Thread Monitior. Uninitial will always be enIdle

	if( m_bInitialRequest )
	{
		f.CWinMessage( "Manual:enInitialize R", theApp.enDManual );
		m_bInitialRequest = false;
		m_bStatus = enInitialize;
	}
	else if( m_bRequestContact )
	{
		f.CWinMessage( "Manual:enManualContact R", theApp.enDManual );
		m_bRequestContact = false;
		m_bStatus = enManualStart;
	
	}
	else if( m_bRequestUp )
	{
		f.CWinMessage( "Manual:enManualUp R", theApp.enDManual );
		m_bRequestUp = false;
//		m_bStatus = enManualTSUpForPlace;
		m_bStatus = enManualUpStart;
	}
	else if( m_bRequestMove )
	{
		f.CWinMessage( "Manual:enManualMove R", theApp.enDManual );
		m_bRequestMove = false;
		m_bStatus = enManualTSMoveStart;
	}

	m.ThStatus.ManualCtrl.line = m_bStatus;
	switch(m_bStatus)
	{			
	case enInitialize:
		Initialize();
		NextStatus();
		break;
	case enIdle:		
		NextStatus();
		break;

	// IC into Socket
	case enManualStart:				// Manual Contact Start
		{
		
		}
		NextStatus();
		break;
	case enManualShMoveToInStart:	// Manual Shuttle move to PP start
		{
		
		}
		NextStatus();
		break;
	case enManualShCheckJam:
		NextStatus();
		break;
	case enManualShMoveToIn:		// Manual Shuttle move to PP (Testsite pick)
		{
			f.ShuttleMovePickPlace();
			f.Wait( m.TimerSetting.iShuttleStableTime );
		}
		NextStatus();
		break;
	case enManualShMoveToInEnd:		// Manual Shuttle move to PP end
		{
		
		}
		NextStatus();
		break;
	case enManualTSPick:			// Manual Test Site Down to Pick
		{
			m_iRunError = f.Motor.MotorRun(&m.m_Motor.Inserter, 
				m.m_Align.TestSite.pick + ( m.m_Offset.TestSite.pick * m.m_Ratio.Inserter_GearRation ), 
				false, m.TimerSetting.iMotorRunTimeout );			
		}
		NextStatus();
		break;
	case enManualTSVacc:			// Manual Test Site Vacc
		{
#ifdef _Demo
			m_TSZWithIC = true;
#else
			m_TSZWithIC = f.Vacc( &m.OutSet.TestSiteVacc, &m.InStatus.TestSiteZVaccSensor, m.Timer.m_dInsertPick );
#endif		
		}
		NextStatus();
		break;
	case enManualTSVaccEnd:			// Manual Test Site Vacc End
		{
		
		}
		NextStatus();
		break;
	case enManualTSUpForContact:	// Manual Test Site Up For contact
		{
			m_iRunError = f.Motor.MotorRun(&m.m_Motor.Inserter, 
				( m.m_Align.TestSite.home + ( m.m_Offset.TestSite.home * m.m_Ratio.Inserter_GearRation ) + ( m.Setting.m_dTestSiteStandbyPosition * m.m_Ratio.Inserter_GearRation)), 
				false, m.TimerSetting.iMotorRunTimeout );		
		}
		NextStatus();
		break;
	case enManualShuttleMoveHome:	// Manual Shuttle move to home ( Testsite ready down to contact )
		{
			f.ShuttleMoveHome();
			f.Wait( m.TimerSetting.iShuttleStableTime );
		}
		NextStatus();
		break;
	case enManualTSDownToContact:	// Manual Test site down to socket
		{
			m_iRunError = f.Motor.MotorRun(&m.m_Motor.Inserter, 
				m.m_Align.TestSite.contact + ( m.m_Offset.TestSite.contact * m.m_Ratio.Inserter_GearRation ), 
				false, m.TimerSetting.iMotorRunTimeout );
			
			// 1.0Ab
			if( m.m_ManualContactMode.bIsTsKeepVaccOn == 1 )
				VaccOff(&m.OutSet.TestSiteVacc);
		}
		NextStatus();
		break;
	case enManualTSStandy:			// Manual Test site stanyby ( wait for up )
		{
		
		}
		NextStatus();
		break;

	// IC return Shuttle position
	case enManualUpStart:			// Manual Return IC Start
		{
		
		}		
		NextStatus();
		break;
	case enManualUpTsVacc:			// Manual Return IC, Vacc On
		{
#ifdef _Demo
			m_TSZWithIC = true;
#else
			m_TSZWithIC = f.Vacc( &m.OutSet.TestSiteVacc, &m.InStatus.TestSiteZVaccSensor, m.Timer.m_dInsertPick );
#endif		
		}
		NextStatus();
		break;
	case enManualTSUpForPlace:		// Manual TS Up for place
		{
			m_iRunError = f.Motor.MotorRun(&m.m_Motor.Inserter, 
				( m.m_Align.TestSite.home + 
				( m.m_Offset.TestSite.home * m.m_Ratio.Inserter_GearRation ) +
				( m.Setting.m_dTestSiteStandbyPosition * m.m_Ratio.Inserter_GearRation )), 
				false, m.TimerSetting.iMotorRunTimeout );
		}
		NextStatus();
		break;
	case enManualShMovetoOutStart:	// Manual Shuttle move to output start
		{
		
		}
		NextStatus();
		break;
	case enManualShMoveToOut:		// Manual Shuttle move to output
		{
			f.ShuttleMovePickPlace();
			f.Wait( m.TimerSetting.iShuttleStableTime );
		}
		NextStatus();
		break;
	case enManualShMoveToOutEnd:	// Manual Shuttle move to output end
		{
		
		}
		NextStatus();
		break;
	case enManualTSPlace:			// Manual Test Site Down to Place
		{
			m_iRunError = f.Motor.MotorRun(&m.m_Motor.Inserter, 
				m.m_Align.TestSite.place + ( m.m_Offset.TestSite.place * m.m_Ratio.Inserter_GearRation ), 
				false, m.TimerSetting.iMotorRunTimeout );
		}
		NextStatus();
		break;
	case enManualTSBlow:			// Manual Test Site Blow
		{
			m_TSZWithIC = f.Blow( &m.OutSet.TestSiteVacc, &m.OutSet.TestSiteBlow,
				&m.InStatus.TestSiteZVaccSensor, m.Timer.m_dInsertPuff );
		}
		NextStatus();
		break;
	case enManualTSUpForReady:		// Manual Test Site Up For Ready
		{
			m_iRunError = f.Motor.MotorRun(&m.m_Motor.Inserter, 
				( m.m_Align.TestSite.home + 
				( m.m_Offset.TestSite.home * m.m_Ratio.Inserter_GearRation ) +
				( m.Setting.m_dTestSiteStandbyPosition * m.m_Ratio.Inserter_GearRation )), 
				false, m.TimerSetting.iMotorRunTimeout );
		}
		NextStatus();
		break;
	case enManualShutleMoveToStandy:// Manual Shuttle move to Standy (Home)
		{
			f.ShuttleMoveHome();
			f.Wait( m.TimerSetting.iShuttleStableTime );
		}
		NextStatus();
		break;
	case enManualEnd:				// Manual Shuttle move to Home (back to Idle)
		{
		
		}
		NextStatus();
		break;
	// TS Pick IC Fail. Recover 
	case enManualReTSUpForReadyStart:		// Manual TS up move to Ready start 
		{
	
		}
		NextStatus();
		break;
	case enManualReTSUpForReady:			// Manual TS up move to Ready
		{
			m_iRunError = f.Motor.MotorRun(&m.m_Motor.Inserter, 
				( m.m_Align.TestSite.home + 
				( m.m_Offset.TestSite.home * m.m_Ratio.Inserter_GearRation ) +
				( m.Setting.m_dTestSiteStandbyPosition * m.m_Ratio.Inserter_GearRation )), 
				false, m.TimerSetting.iMotorRunTimeout );			
		}
		NextStatus();
		break;
	case enManualReShuttleHomeForReady:	// Manual Shuttle Home to Ready
		{
			f.ShuttleMoveHome();
			f.Wait( m.TimerSetting.iShuttleStableTime );		
		}
		NextStatus();
		break;
	case enManualReShuttleEnd:			// Manual Shuttle Home end
		{
		
		}
		NextStatus();
		break;
	// Adjust Contact
	case enManualTSMoveStart:		// Manual Adjust TS Contact Position Start
		{
		
		}
		NextStatus();
		break;
	case enManualTSMove:			// Manual Adjust TS Contact Position 
		{
			m_iRunError = f.Motor.MotorRun(&m.m_Motor.Inserter, 
				m.m_Align.TestSite.contact + ( m.m_Offset.TestSite.contact * m.m_Ratio.Inserter_GearRation ), 
				false, m.TimerSetting.iMotorRunTimeout );	
		}
		NextStatus();
		break;
	case enManualTSMoveEnd:			// Manual Adjust TS Contact Position End
		{
		
		}
		NextStatus();
		break;

	// Test Down, Direcit Contact
	case enManualTsDirectContactStart:		// Manual Contact, Test Site Direct Contact Start
		{
		
		}
		NextStatus();
		break;
	case enManualTsDirectContactDown:		// Manual Contact, Test Site Direct Contact Down
		{
			m_iRunError = f.Motor.MotorRun(&m.m_Motor.Inserter, 
				m.m_Align.TestSite.contact + ( m.m_Offset.TestSite.contact * m.m_Ratio.Inserter_GearRation ), 
				false, m.TimerSetting.iMotorRunTimeout );		
		}
		NextStatus();
		break;
	case enManualTsDirectContactEnd:		// Manual Contact, Test Site Direct Contact Down End
		{
		
		}
		NextStatus();
		break;

	// Test Up, Direct Contact
	case enManualTsDirectContactUpStart:	// Manual Contact, Test Site Direct Contact Up Start
		{
		}
		NextStatus();
		break;
	case enManualTsDirectContactUp:			// Manual Contact, Test Site Direct Contact Up
		{
			m_iRunError = f.Motor.MotorRun(&m.m_Motor.Inserter, 
				( m.m_Align.TestSite.home + 
				( m.m_Offset.TestSite.home * m.m_Ratio.Inserter_GearRation ) +
				( m.Setting.m_dTestSiteStandbyPosition * m.m_Ratio.Inserter_GearRation )), 
				false, m.TimerSetting.iMotorRunTimeout );
		}
		NextStatus();
		break;
	case enManualTsDirectContactUpEnd:		// Manual Contact, Test Site Direct Contact Up End
		{
		}
		NextStatus();
		break;

	// Error 
	case enManualShMoveToInError:			// Manual Move to Shuttle Pick Fail
		{
		
		}
		NextStatus();
		break;
	case enManualTSUpForContactError:		// Manual Test Site Pick IC Fail
		{
		
		}
		NextStatus();
		break;
	case enManualShuttleMoveHomeError:		// Manual Test Site Move to Home Fail
		{
		
		}
		NextStatus();
		break;
	case enManualShMoveToOutError:			// Manual Move to Shuttle Place Fail
		{
		
		}
		NextStatus();
		break;
	case enManualShutleMoveToStandyError:	// Manual Move to Shuttle Standy Fail
		{
		
		}
		NextStatus();
		break;
	case enManualShCheckJamError:			// Manual Check Jam
		{

		}
		NextStatus();
		break;
	default:
		CheckRestart();
		break;
	}
}
void CThManualCtrl::CheckRestart()
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
void CThManualCtrl::NextStatus()
{
	if(m_iRunError != enCodeRunOK)
	{
		m.Info.iStatus = theApp.enUninitial;
		m.Err.Manual.Code = m_iRunError;

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
		m_bStatus = enIdle;
		break;
	case enIdle:
		m_bStatus = enIdle;
		break;

	// IC into Socket
	case enManualStart:				// Manual Contact Start
		f.CWinMessage( "Manual:enManualStart", theApp.enDManual );
		{
			m_bStatus = enManualShMoveToInStart;
			
			// 1.0Ab
			// Test Site Down for direct contact - down
			if( m.m_ManualContactMode.bIsTsDirectContact == 1 )
			{
				m_bStatus = enManualTsDirectContactStart;
			}
		}
		break;
	case enManualShMoveToInStart:	// Manual Shuttle move to PP start
		f.CWinMessage( "Manual:enManualShMoveToInStart", theApp.enDManual );
		{
			m_bStatus = enManualShCheckJam;
		}
		break;
	case enManualShCheckJam:
		f.CWinMessage( "Manual:enManualShCheckJam", theApp.enDManual );
		{
			if( !f.CheckShuttleJam() )
				m_bStatus = enManualShMoveToIn;
			else
			{
				// Ops; Shuttle Jam
				m.Err.Manual.Code = enCodeManualShuttleJamFail;
				m_bStatus = enManualShCheckJamError;
			}
		}
		break;
	case enManualShMoveToIn:		// Manual Shuttle move to PP (Testsite pick)
		f.CWinMessage( "Manual:enManualShMoveToIn", theApp.enDManual );
		{
			if( f.CheckShuttlePickPlaceOK() )
				m_bStatus = enManualShMoveToInEnd;
			else
			{
				// Ops: Shuttle Move To PickPlace Fail
				m.Err.Manual.Code = enCodeManualShuttleInFail;
				m_bStatus = enManualShMoveToInError;
			}
		}
		break;
	case enManualShMoveToInEnd:		// Manual Shuttle move to PP end
		f.CWinMessage( "Manual:enManualShMoveToInEnd", theApp.enDManual );
		{
			m_bStatus = enManualTSPick;
		}
		break;
	case enManualTSPick:			// Manual Test Site Down to Pick
		f.CWinMessage( "Manual:enManualTSPick", theApp.enDManual );
		{
			m_bStatus = enManualTSVacc;
		}
		break;
	case enManualTSVacc:			// Manual Test Site Vacc
		f.CWinMessage( "Manual:enManualTSVacc", theApp.enDManual );
		{
			m_bStatus = enManualTSVaccEnd;
		}
		break;
	case enManualTSVaccEnd:			// Manual Test Site Vacc End
		f.CWinMessage( "Manual:enManualTSVaccEnd", theApp.enDManual );
		{
			m_bStatus = enManualTSUpForContact;
		}
		break;
	case enManualTSUpForContact:	// Manual Test Site Up For contact
		f.CWinMessage( "Manual:enManualTSUpForContact", theApp.enDManual );
		{
			m_TSZWithIC = f.CheckTSZVaccSensor();

			if( m_TSZWithIC )
				m_bStatus = enManualShuttleMoveHome;
			else
			{
				// Ops: Test Site Pick IC Fail
				m.Err.Manual.Code = enCodeManuelTestPickICFail;
				m_bStatus = enManualTSUpForContactError;
			}
		}
		break;
	case enManualShuttleMoveHome:	// Manual Shuttle move to home ( Testsite ready down to contact )
		f.CWinMessage( "Manual:enManualShuttleMoveHome", theApp.enDManual );
		{
			if( f.CheckShuttleHomeOK() )
				m_bStatus = enManualTSDownToContact;
			else
			{
				// Ops: Shuttle Move to Home Fail.
				m.Err.Manual.Code = enCodeManualShuttleHomeFail;
				m_bStatus = enManualShuttleMoveHomeError;
			}
		}
		break;
	case enManualTSDownToContact:	// Manual Test site down to socket
		f.CWinMessage( "Manual:enManualTSDownToContact", theApp.enDManual );
		{
			m_bStatus = enManualTSStandy;
		}
		break;
	case enManualTSStandy:			// Manual Test site stanyby ( wait for up )
		f.CWinMessage( "Manual:enManualTSStandy", theApp.enDManual );
		{
			ManualContactCtDone();
			m_bStatus = enIdle;
		}
		break;

	// IC return Shuttle position
	case enManualUpStart:			// Manual Return IC Start
		f.CWinMessage( "Manual:enManualUpStart", theApp.enDManual );
		{
			m_bStatus = enManualUpTsVacc;

			// 1.0Ab
			// Test Site Down for direct contact - up
			if( m.m_ManualContactMode.bIsTsDirectContact == 1 )
			{
				m_bStatus = enManualTsDirectContactUpStart;
			}
		}
		break;
	case enManualUpTsVacc:			// Manual Return IC, Vacc On
		f.CWinMessage( "Manual:enManualUpTsVacc", theApp.enDManual );
		{
			m_bStatus = enManualTSUpForPlace;
		}
		break;
	case enManualTSUpForPlace:		// Manual TS Up for place
		f.CWinMessage( "Manual:enManualTSUpForPlace", theApp.enDManual );
		{
			m_bStatus = enManualShMovetoOutStart;
		}
		break;
	case enManualShMovetoOutStart:	// Manual Shuttle move to output start
		f.CWinMessage( "Manual:enManualShMovetoOutStart", theApp.enDManual );
		{
			m_bStatus = enManualShMoveToOut;
		}
		break;
	case enManualShMoveToOut:		// Manual Shuttle move to output
		f.CWinMessage( "Manual:enManualShMoveToOut", theApp.enDManual );
		{
			if( f.CheckShuttlePickPlaceOK() )
				m_bStatus = enManualShMoveToOutEnd;
			else
			{
				// Ops: Shuttle Move to Place Fail
				m.Err.Manual.Code = enCodeManualShuttleOutFail;
				m_bStatus = enManualShMoveToOutError;
			}
		}
		break;
	case enManualShMoveToOutEnd:	// Manual Shuttle move to output end
		f.CWinMessage( "Manual:enManualShMoveToOutEnd", theApp.enDManual );
		{
			m_bStatus = enManualTSPlace;
		}
		break;
	case enManualTSPlace:			// Manual Test Site Down to Place
		f.CWinMessage( "Manual:enManualTSPlace", theApp.enDManual );
		{
			m_bStatus = enManualTSBlow;
		}
		break;
	case enManualTSBlow:			// Manual Test Site Blow
		f.CWinMessage( "Manual:enManualTSBlow", theApp.enDManual );
		{
			m_bStatus = enManualTSUpForReady;
		}
		break;
	case enManualTSUpForReady:		// Manual Test Site Up For Ready
		f.CWinMessage( "Manual:enManualTSUpForReady", theApp.enDManual );
		{
			m_bStatus = enManualShutleMoveToStandy;
		}
		break;
	case enManualShutleMoveToStandy:// Manual Shuttle move to Standy (Home)
		f.CWinMessage( "Manual:enManualShutleMoveToStandy", theApp.enDManual );
		{
			if( f.CheckShuttleHomeOK() )
				m_bStatus = enManualEnd;
			else
			{
				// Ops: Shuttle Home Fail
				m.Err.Manual.Code = enCodeManualShuttleStandyFail;
				m_bStatus = enManualShutleMoveToStandyError;
			}
		}
		break;
	case enManualEnd:				// Manual Shuttle move to Home (back to Idle)
		f.CWinMessage( "Manual:enManualEnd", theApp.enDManual );
		{
			ManualContactUpDone();
			m_bStatus = enIdle;
		}
		break;
	// TS Pick IC Fail. Recover 
	case enManualReTSUpForReadyStart:		// Manual TS up move to Ready start 
		f.CWinMessage( "Manual:enReManualTSUpForReadyStart", theApp.enDManual );
		{
			m_bStatus = enManualReTSUpForReady;
		}
		break;
	case enManualReTSUpForReady:			// Manual TS up move to Ready
		f.CWinMessage( "Manual:enManualReTSUpForReady", theApp.enDManual );
		{
			m_bStatus = enManualReShuttleHomeForReady;
		}
		break;
	case enManualReShuttleHomeForReady:	// Manual Shuttle Home to Ready
		f.CWinMessage( "Manual:enManualReShuttleHomeForReady", theApp.enDManual );
		{
			m_bStatus = enManualReShuttleEnd;
		}
		break;
	case enManualReShuttleEnd:			// Manual Shuttle Home end
		f.CWinMessage( "Manual:enManualReShuttleEnd", theApp.enDManual );
		{
			m_bStatus = enManualEnd;
		}
		break;
	// Adjust Contact
	case enManualTSMoveStart:		// Manual Adjust TS Contact Position Start
		f.CWinMessage( "Manual:enManualTSMoveStart", theApp.enDManual );
		{
			m_bStatus = enManualTSMove;
		}
		break;
	case enManualTSMove:			// Manual Adjust TS Contact Position 
		f.CWinMessage( "Manual:enManualTSMove", theApp.enDManual );
		{
			m_bStatus = enManualTSMoveEnd;
		}
		break;
	case enManualTSMoveEnd:			// Manual Adjust TS Contact Position End
		f.CWinMessage( "Manual:enManualTSMoveEnd", theApp.enDManual );
		{
			ManualContactMvDone();
			m_bStatus = enIdle;
		}
		break;

	// Test Down, Direcit Contact
	case enManualTsDirectContactStart:		// Manual Contact, Test Site Direct Contact Start
		f.CWinMessage( "Manual:enManualTsDirectContactStart", theApp.enDManual );
		{
			m_bStatus = enManualTsDirectContactDown;
		}
		break;
	case enManualTsDirectContactDown:		// Manual Contact, Test Site Direct Contact Down
		f.CWinMessage( "Manual:enManualTsDirectContactDown", theApp.enDManual );
		{
			m_bStatus = enManualTsDirectContactEnd;
		}
		break;
	case enManualTsDirectContactEnd:		// Manual Contact, Test Site Direct Contact Down End
		f.CWinMessage( "Manual:enManualTsDirectContactEnd", theApp.enDManual );
		{
			m_bStatus = enManualTSStandy;
		}
		break;

	// Test Up, Direct Contact
	case enManualTsDirectContactUpStart:	// Manual Contact, Test Site Direct Contact Up Start
		f.CWinMessage( "Manual:enManualTsDirectContactUpStart", theApp.enDManual );
		{
			m_bStatus = enManualTsDirectContactUp;
		}
		break;
	case enManualTsDirectContactUp:			// Manual Contact, Test Site Direct Contact Up
		f.CWinMessage( "Manual:enManualTsDirectContactUp", theApp.enDManual );
		{
			m_bStatus = enManualTsDirectContactUpEnd;
		}
		break;
	case enManualTsDirectContactUpEnd:		// Manual Contact, Test Site Direct Contact Up End
		f.CWinMessage( "Manual:enManualTsDirectContactUpEnd", theApp.enDManual );
		{
			m_bStatus = enManualEnd;
		}
		break;

	// Error
	case enManualShMoveToInError:			// Manual Move to Shuttle Pick Fail
		f.CWinMessage( "Manual:enManualShMoveToInError", theApp.enDManual );
		{
			if( m.Err.Manual.Code == 0 )
			{
				if( m.Err.Manual.Result == theApp.ActionSkip )
				{
					m_bStatus = enManualShMoveToInEnd;
				}
				else if( m.Err.Manual.Result == theApp.ActionRetry )
				{
					m_bStatus = enManualShMoveToIn;
				}
				else
					;
			}
		}
		break;
	case enManualTSUpForContactError:		// Manual Test Site Pick IC Fail
		f.CWinMessage( "Manual:enManualTSUpForContactError", theApp.enDManual );
		{
			if( m.Err.Manual.Result == theApp.ActionSkip )
			{
				m_bStatus = enManualShuttleMoveHome;
//				m_bStatus = enManualReTSUpForReadyStart;
			}
			else if( m.Err.Manual.Result == theApp.ActionTSSkip )
			{
//				m_bStatus = enManualShuttleMoveHome;
				m_bStatus = enManualReTSUpForReadyStart;
			}
			else if( m.Err.Manual.Result == theApp.ActionRetry )
			{
				m_bStatus = enManualTSPick;
			}
			else
				;
		}
		break;
	case enManualShuttleMoveHomeError:		// Manual Test Site Move to Home Fail
		f.CWinMessage( "Manual:enManualShuttleMoveHomeError", theApp.enDManual );
		{
			if( m.Err.Manual.Result == theApp.ActionSkip )
			{
				m_bStatus = enManualTSDownToContact;
			}
			else if( m.Err.Manual.Result == theApp.ActionRetry )
			{
				m_bStatus = enManualShuttleMoveHome;
			}
			else
				;
		}
		break;
	case enManualShMoveToOutError:			// Manual Move to Shuttle Place Fail
		f.CWinMessage( "Manual:enManualShMoveToOutError", theApp.enDManual );
		{
			if( m.Err.Manual.Result == theApp.ActionSkip )
			{
				m_bStatus = enManualShMoveToOutEnd;
			}
			else if( m.Err.Manual.Result == theApp.ActionRetry )
			{
				m_bStatus = enManualShMoveToOut;
			}
			else
				;
		}
		break;
	case enManualShutleMoveToStandyError:	// Manual Move to Shuttle Standy Fail
		f.CWinMessage( "Manual:enManualShutleMoveToStandyError", theApp.enDManual );
		{
			if( m.Err.Manual.Result == theApp.ActionSkip )
			{
				m_bStatus = enManualEnd;
			}
			else if( m.Err.Manual.Result == theApp.ActionRetry )
			{
				m_bStatus = enManualShutleMoveToStandy;
			}
			else
				;
		}
		break;
	case enManualShCheckJamError:			// Manual Check Jam
		f.CWinMessage( "Manual:enManualShCheckJamError", theApp.enDManual );
		{
			if( m.Err.Manual.Result == theApp.ActionSkip )
			{
				m_bStatus = enManualShCheckJam;
			}
			else if( m.Err.Manual.Result == theApp.ActionRetry )
			{
				m_bStatus = enManualShCheckJam;
			}
			else
				;
		}
		break;
	}
}
bool CThManualCtrl::IsPause()
{
	if((m_bStatus & 0x1) || m_bStatus == enIdle)
		return true;
	else
		return false;
}
int CThManualCtrl::ExitInstance()
{
	TRACE("CThManualCtrl\n");
	// TODO:  perform any per-thread cleanup here
	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(CThManualCtrl, CWinThread)
	//{{AFX_MSG_MAP(CThManualCtrl)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CThManualCtrl message handlers
