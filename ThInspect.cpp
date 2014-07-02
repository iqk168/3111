// ThInspect.cpp : implementation file
//

#include "stdafx.h"
#include "deer.h"
#include "ThInspect.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CThInspect

IMPLEMENT_DYNCREATE(CThInspect, CWinThread)

CThInspect::CThInspect()
{
	m_bStatus = enIdle;	
	m_iRunError = enCodeRunOK;	
	m_bInitialized = false;
	m_bInitialRequest = false;
}

CThInspect::~CThInspect()
{
	TRACE("~CThInspect\n");
}

BOOL CThInspect::InitInstance()
{
	f.IncraseThreadCount();
	m.ThStatus.InspectCtrl.times = 1;
	while(m.Info.bRunning)
	{
		m.ThStatus.InspectCtrl.times++;
		Running();
		Sleep(_Wait);
	}
	f.ReduceThreadCount();
	f.m_Log.AddLogEvent( "Thread Inspect Finish" );

	return TRUE;
}

void CThInspect::InitialStart()
{
	m_bInitialRequest = true;
}

void CThInspect::Initialize()
{
	m_bInitialized = false;
	if( m.Info.iStatus != theApp.enInitial )
		return;
	// If not Initial. return this function. User want to stop.

	m.MotorStatus.Inspect = "Initialing.";
	m.MotorStatus.Inspect = "Inspect OK.";
	m.MotorStatus.InspectInitialed = true;
	m.InterLock.InspectEnd = true;
	m_bInitialized = true;
}

bool CThInspect::IsInitialError()
{
	if( m.Info.iStatus == theApp.enUninitial )
		return false;
	if( m_iRunError != enCodeRunOK )
		return false;

	return true;
}

void CThInspect::Running()
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
		f.CWinMessage( "Inspect:enInitialize R", theApp.enDInspect );
		m_bInitialRequest = false;
		m_bStatus = enInitialize;
	}

	m.ThStatus.InspectCtrl.line = m_bStatus;
	switch(m_bStatus)
	{			
	case enInitialize:
		Initialize();
		NextStatus();
		break;
	case enIdle:		
		NextStatus();
		break;
	default:
		CheckRestart();
		break;
	}
}
void CThInspect::CheckRestart()
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
bool CThInspect::IsPause()
{
//	if( (m_bStatus & 0x1) )
	if((m_bStatus & 0x1) || m_bStatus == enIdle)
		return true;
	else
		return false;
}
void CThInspect::NextStatus()
{
	if(m_iRunError != enCodeRunOK)
	{
		m.Info.iStatus = theApp.enUninitial;
		m.Err.Inspect.Code = m_iRunError;

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
	}
}

int CThInspect::ExitInstance()
{
	TRACE("CThInspect\n");
	// TODO:  perform any per-thread cleanup here
	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(CThInspect, CWinThread)
	//{{AFX_MSG_MAP(CThInspect)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CThInspect message handlers
