// ThIOReadWrite.cpp : implementation file
//

#include "stdafx.h"
#include "deer.h"
#include "ThIOReadWrite.h"

//
//#include "matrix_gpio.h"
#include "Dask.h"

// Motor Lib
#include "MC8141P.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CThIOReadWrite

IMPLEMENT_DYNCREATE(CThIOReadWrite, CWinThread)

CThIOReadWrite::CThIOReadWrite()
{
	card_number = 0;
	card		= -1;
}

CThIOReadWrite::~CThIOReadWrite()
{
#ifdef _Demo
#else

	/*
	// MXC-4000
	Release_Card(card);
	*/


#endif

	TRACE("~CThIOReadWrite\n");
}
void CThIOReadWrite::CloseAllIOOutputProtuctShuttle()
{
	if( m.InStatus.ShuttlePLmt == _ShuttlePLmtOn )
	{
		m.OutSet.Shuttle = true;
	}
}
void CThIOReadWrite::CloseAllIOOutput()
{
	m.OutSet.ArmVacc = false;			// 00	Set Arm Vacc turn on, 1 is turn on, 0 is turn off
	m.OutSet.ArmBlow = false;			// 01	Set Arm Blow turn on, 1 is turn on, 0 is turn off
	m.OutSet.TestSiteVacc = false;		// 02	Set Test Site Z Vacc turn on, 1 is turn on, 0 is turn off
	m.OutSet.TestSiteBlow = false;		// 03	Set Test Site Z Blow turn on, 1 is turn on, 0 is turn off
	m.OutSet.Shuttle = false;			// 04	Set Shuttle active				  
	m.OutSet.TestSiteSkip = false;		// 05	Set TestSite Skip Button Led On
	m.OutSet.TowerRedOn = false;		// 06	Set Tower Red light on
	m.OutSet.TowerYellowOn = false;		// 07	Set Tower Yellow light on
	m.OutSet.TowerGreenOn = false;		// 08	Set Tower Green light on
	m.OutSet.TowerBuzzerOn = false;		// 09	Set Tower Buzzer light on
	m.OutSet.ATXPower = false;			// 10	Set ATX Power
	m.OutSet.Tester = false;			// 11	Set Tester active
}

BOOL CThIOReadWrite::InitInstance()
{
#ifdef _Demo	
#else
	Init();
#endif//Dmo

	//
	m.InterLock.IsIODone = true;

	// 1.0Af
	// Lamp Setup
	BlinkInit();

	f.IncraseThreadCount();
	m.ThStatus.IO.times = 1;
	while(m.Info.bRunning)
	{
		m.ThStatus.IO.times++;
#ifdef _Demo
		// Demo ¼Ò¦¡
		ReadInput();
		SetLimitation();
		SetOutput();

		Sleep(_Wait);
#else		
		// Release ¼Ò¦¡
		ReadInput();
		SetLimitation();
		SetOutput();

		Sleep(_Wait);
#endif
	}

	//
	CloseAllIOOutput();
	CloseAllIOOutputProtuctShuttle();
	SetOutput();
	f.ReduceThreadCount();
	f.m_Log.AddLogEvent( "Thread IOReadWrite Finish" );

	return TRUE;
}

int CThIOReadWrite::ExitInstance()
{
	TRACE("CThIOReadWrite\n");
	// TODO:  perform any per-thread cleanup here
	return CWinThread::ExitInstance();
}

////////////////////////////////////////////////////////////////////////////////////
// 3111
bool CThIOReadWrite::Init()
{
	// MXC-4000
	bool bInitOK = true;
	card_Info.cardType = GPIO_Init();

	CString strTmp = _T("");
	if( card_Info.cardType != 0 )
	{
		// Open Success
		strTmp.Format( TEXT("MXC4000 Super IO GPIO -- IT%x"), card_Info.cardType );

		CString csMsg = _T("");
		csMsg.Format("MXC4000 Super IO GPIO -- IT%x)", card_Info.cardType);
		f.DMsg.DMsg( csMsg );
	}
	else
	{
		// Open IO Card Fail....
		strTmp.Format( TEXT("MXC4000 GPIO INIT ERR"));
		bInitOK = false;

		CString csMsg = _T("");
		csMsg.Format("MXC4000(IO Card) GPIO INIT ERR");
		f.DMsg.DMsg( csMsg + _DMsgMark, false );
#ifdef _Demo
#else
		if( m.Setting.m_bEnableProgramInitialStart == 1 )
		{
		}
		else
			AfxMessageBox( strTmp );
#endif
	}

	/*
	// MXC-6000
	if ((card=Register_Card(PCI_7230, card_number)) < 0)
	{
		// Init 7230 Error.
		CString csError = _T("");
		csError.Format("IO 7230 Initial Fail - %d", card );
		AfxMessageBox( csError );
		return false;
	}
	*/

	ReadInput();
	SetOutput();

	return true;
}

// 1.0Af
// Lamp Setup
void CThIOReadWrite::BlinkInit()
{
	long lStart = ::GetTickCount();
	m.m_TowerBlinkTimer.lBlink1Start = lStart;
	m.m_TowerBlinkTimer.lBlink2Start = lStart;
	m.m_TowerBlinkTimer.lBlink3Start = lStart;
	m.m_TowerBlinkTimer.lBlink4Start = lStart;
	m.m_TowerBlinkTimer.lBlink5Start = lStart;
}
void CThIOReadWrite::BlinkConvert()
{
	if( 1 )
	{
		// Blink1
		if( ( ::GetTickCount()) - m.m_TowerBlinkTimer.lBlink1Start > 
			( m.m_TowerSetupSetting.dBlinkTime[0] * 1000 ) )
		{
			m.m_TowerBlinkTimer.lBlink1Start = ::GetTickCount();
			m.m_TowerBlinkTimer.bBlink1 = !m.m_TowerBlinkTimer.bBlink1;
		}
		// Blink2
		if( ( ::GetTickCount()) - m.m_TowerBlinkTimer.lBlink2Start > 
			( m.m_TowerSetupSetting.dBlinkTime[1] * 1000 ) )
		{
			m.m_TowerBlinkTimer.lBlink2Start = ::GetTickCount();
			m.m_TowerBlinkTimer.bBlink2 = !m.m_TowerBlinkTimer.bBlink2;
		}
		// Blink3
		if( ( ::GetTickCount()) - m.m_TowerBlinkTimer.lBlink3Start > 
			( m.m_TowerSetupSetting.dBlinkTime[2] * 1000 ) )
		{
			m.m_TowerBlinkTimer.lBlink3Start = ::GetTickCount();
			m.m_TowerBlinkTimer.bBlink3 = !m.m_TowerBlinkTimer.bBlink3;
		}
		// Blink4
		if( ( ::GetTickCount()) - m.m_TowerBlinkTimer.lBlink4Start > 
			( m.m_TowerSetupSetting.dBlinkTime[3] * 1000 ) )
		{
			m.m_TowerBlinkTimer.lBlink4Start = ::GetTickCount();
			m.m_TowerBlinkTimer.bBlink4 = !m.m_TowerBlinkTimer.bBlink4;
		}
		// Blink5
		if( ( ::GetTickCount()) - m.m_TowerBlinkTimer.lBlink5Start > 
			( m.m_TowerSetupSetting.dBlinkTime[4] * 1000 ) )
		{
			m.m_TowerBlinkTimer.lBlink5Start = ::GetTickCount();
			m.m_TowerBlinkTimer.bBlink5 = !m.m_TowerBlinkTimer.bBlink5;
		}
	}
}
bool CThIOReadWrite::BlinkFlash(int iChoise)
{
	bool bEnable = false;
	if( iChoise == theApp.enTowerChoiseDisable )
		bEnable = false;
	else if( iChoise == theApp.enTowerChoiseEnable )
		bEnable = true;
	else if( iChoise == theApp.enTowerChoiseBlink1 )
		bEnable = m.m_TowerBlinkTimer.bBlink1;
	else if( iChoise == theApp.enTowerChoiseBlink2 )
		bEnable = m.m_TowerBlinkTimer.bBlink2;
	else if( iChoise == theApp.enTowerChoiseBlink3 )
		bEnable = m.m_TowerBlinkTimer.bBlink3;
	else if( iChoise == theApp.enTowerChoiseBlink4 )
		bEnable = m.m_TowerBlinkTimer.bBlink4;
	else if( iChoise == theApp.enTowerChoiseBlink5 )
		bEnable = m.m_TowerBlinkTimer.bBlink5;
	else
	{
		// Nerver be here
	}

	return bEnable;
}
void CThIOReadWrite::ReadInput()
{
/*
	unsigned char*  in = (unsigned char *)&m.InStatus;
	unsigned short	i;
	unsigned long inputData;
	err = DI_ReadPort(card, 0, &inputData);
*/
#ifdef _Demo
#else

	unsigned char*  in = (unsigned char *)&m.InStatus;
	unsigned short	i, inputData;

	err = GPI_Read( &inputData );

	m.DebugError.ReadCount++;
	if( err != NoError )
	{
		m.DebugError.ReadErr++;
	}
	else
	{
		for ( i = 0; i < 12 ; i++ )
			in[i] = (unsigned char)( ( inputData >> i ) & 0x00000001);
	}

#endif
	m.InterLock.IsIORead = true;
	// Note: When IO Read. Then Check Error
}
void CThIOReadWrite::SetOutput()
{
#ifdef _Demo
#else

	int i = 0;
	unsigned char*	outStatus = (unsigned char *)&m.OutStatus;
	unsigned char*	outputWrite = (unsigned char *)&m.OutWrite;
	unsigned int	outputValue = 0;

	// Protect IO Setting 
	m.OutWrite = m.OutSet;

	int iSize = sizeof(m.OutSet);

	for (i = 0; i < iSize; i++)
	{
		outputValue |= outputWrite[i] << i;	
		outStatus[i] = outputWrite[i];
	}

	GPO_Write( outputValue );
//	DO_WritePort(card,0, outputValue);

#endif
}
void CThIOReadWrite::SetLimitation()
{
	// 1.0Af
	// Lamp Setup
	BlinkConvert();

	if(m.Info.bIOMonitor)
		return;
	// Note : if IO Montior Open. No setting by this function.

	if(m.Info.bError)
	{				
		m.OutWrite.TowerGreenOn		= m.OutSet.TowerGreenOn		= false;
		m.OutWrite.TowerYellowOn	= m.OutSet.TowerYellowOn	= false;
		m.OutWrite.TowerBuzzerOn	= m.OutSet.TowerBuzzerOn	= m.Info.bAlarmTimer;
		if( m.Info.bBuzzer )
			m.OutWrite.TowerBuzzerOn = m.OutSet.TowerBuzzerOn = m.Info.bAlarmTimer;
		else
			m.OutWrite.TowerBuzzerOn = m.OutSet.TowerBuzzerOn = false;
		
		m.OutWrite.TowerRedOn = m.OutSet.TowerRedOn = m.Info.bAlarmTimer;
		return;
	}
	// Note : there have a error
	// Then We set alarm output and return.

	// 1.0Af
	// Lamp Setup
	////////////////////////////////////////////////////////////////////////////////////////
	if( 1 )
	{
		///////////////////////
		// Enable Tower Setup
		if( m.Info.iStatus == theApp.enReady )
		{
			m.OutWrite.TowerRedOn = m.OutSet.TowerRedOn
				= BlinkFlash( m.m_TowerSetupSetting.Ready.LightRedChoise );				// Red
			m.OutWrite.TowerYellowOn = m.OutSet.TowerYellowOn
				= BlinkFlash( m.m_TowerSetupSetting.Ready.LightYellowChoise );			// Yellow
			m.OutWrite.TowerGreenOn	= m.OutSet.TowerGreenOn
				= BlinkFlash( m.m_TowerSetupSetting.Ready.LightGreenChoise );			// Green
		}
		else if( m.Info.iStatus == theApp.enInitial )
		{
			m.OutWrite.TowerRedOn = m.OutSet.TowerRedOn
				= BlinkFlash( m.m_TowerSetupSetting.Initial.LightRedChoise );			// Red
			m.OutWrite.TowerYellowOn = m.OutSet.TowerYellowOn
				= BlinkFlash( m.m_TowerSetupSetting.Initial.LightYellowChoise );		// Yellow
			m.OutWrite.TowerGreenOn	= m.OutSet.TowerGreenOn
				= BlinkFlash( m.m_TowerSetupSetting.Initial.LightGreenChoise );			// Green
		}
		else if( m.Info.iStatus == theApp.enUninitial )
		{
			m.OutWrite.TowerRedOn = m.OutSet.TowerRedOn
				= BlinkFlash( m.m_TowerSetupSetting.Uninitial.LightRedChoise );			// Red
			m.OutWrite.TowerYellowOn = m.OutSet.TowerYellowOn
				= BlinkFlash( m.m_TowerSetupSetting.Uninitial.LightYellowChoise );		// Yellow
			m.OutWrite.TowerGreenOn	= m.OutSet.TowerGreenOn
				= BlinkFlash( m.m_TowerSetupSetting.Uninitial.LightGreenChoise );		// Green		
		}
		else if( m.Info.iStatus == theApp.enCycle )
		{
			m.OutWrite.TowerRedOn = m.OutSet.TowerRedOn
				= BlinkFlash( m.m_TowerSetupSetting.Cycle.LightRedChoise );				// Red
			m.OutWrite.TowerYellowOn = m.OutSet.TowerYellowOn
				= BlinkFlash( m.m_TowerSetupSetting.Cycle.LightYellowChoise );			// Yellow
			m.OutWrite.TowerGreenOn	= m.OutSet.TowerGreenOn
				= BlinkFlash( m.m_TowerSetupSetting.Cycle.LightGreenChoise );			// Green		
		}
		else if( m.Info.iStatus == theApp.enCycleStop )
		{
			m.OutWrite.TowerRedOn = m.OutSet.TowerRedOn
				= BlinkFlash( m.m_TowerSetupSetting.CycleStop.LightRedChoise );			// Red
			m.OutWrite.TowerYellowOn = m.OutSet.TowerYellowOn
				= BlinkFlash( m.m_TowerSetupSetting.CycleStop.LightYellowChoise );		// Yellow
			m.OutWrite.TowerGreenOn	= m.OutSet.TowerGreenOn
				= BlinkFlash( m.m_TowerSetupSetting.CycleStop.LightGreenChoise );		// Green		
		}
		else if( m.Info.iStatus == theApp.enOneCycle )
		{
			m.OutWrite.TowerRedOn = m.OutSet.TowerRedOn
				= BlinkFlash( m.m_TowerSetupSetting.OneCycle.LightRedChoise );			// Red
			m.OutWrite.TowerYellowOn = m.OutSet.TowerYellowOn
				= BlinkFlash( m.m_TowerSetupSetting.OneCycle.LightYellowChoise );		// Yellow
			m.OutWrite.TowerGreenOn	= m.OutSet.TowerGreenOn
				= BlinkFlash( m.m_TowerSetupSetting.OneCycle.LightGreenChoise );		// Green			
		}
		else if( m.Info.iStatus == theApp.enOneCycleStop )
		{
			m.OutWrite.TowerRedOn = m.OutSet.TowerRedOn
				= BlinkFlash( m.m_TowerSetupSetting.OneCycleStop.LightRedChoise );		// Red
			m.OutWrite.TowerYellowOn = m.OutSet.TowerYellowOn
				= BlinkFlash( m.m_TowerSetupSetting.OneCycleStop.LightYellowChoise );	// Yellow
			m.OutWrite.TowerGreenOn	= m.OutSet.TowerGreenOn
				= BlinkFlash( m.m_TowerSetupSetting.OneCycleStop.LightGreenChoise );	// Green		
		}
		else if( m.Info.iStatus == theApp.enOverride )
		{
			m.OutWrite.TowerRedOn = m.OutSet.TowerRedOn
				= BlinkFlash( m.m_TowerSetupSetting.Override.LightRedChoise );			// Red
			m.OutWrite.TowerYellowOn = m.OutSet.TowerYellowOn
				= BlinkFlash( m.m_TowerSetupSetting.Override.LightYellowChoise );		// Yellow
			m.OutWrite.TowerGreenOn	= m.OutSet.TowerGreenOn
				= BlinkFlash( m.m_TowerSetupSetting.Override.LightGreenChoise );		// Green		
		}
		else if( m.Info.iStatus == theApp.enOverrideStop )
		{
			m.OutWrite.TowerRedOn = m.OutSet.TowerRedOn
				= BlinkFlash( m.m_TowerSetupSetting.OverrideStop.LightRedChoise );		// Red
			m.OutWrite.TowerYellowOn = m.OutSet.TowerYellowOn
				= BlinkFlash( m.m_TowerSetupSetting.OverrideStop.LightYellowChoise );	// Yellow
			m.OutWrite.TowerGreenOn	= m.OutSet.TowerGreenOn
				= BlinkFlash( m.m_TowerSetupSetting.OverrideStop.LightGreenChoise );	// Green		
		}
		else if( m.Info.iStatus == theApp.enManual )
		{
			m.OutWrite.TowerRedOn = m.OutSet.TowerRedOn
				= BlinkFlash( m.m_TowerSetupSetting.Manual.LightRedChoise );			// Red
			m.OutWrite.TowerYellowOn = m.OutSet.TowerYellowOn
				= BlinkFlash( m.m_TowerSetupSetting.Manual.LightYellowChoise );			// Yellow
			m.OutWrite.TowerGreenOn	= m.OutSet.TowerGreenOn
				= BlinkFlash( m.m_TowerSetupSetting.Manual.LightGreenChoise );			// Green		
		}
		else if( m.Info.iStatus == theApp.enManualStop )
		{
			m.OutWrite.TowerRedOn = m.OutSet.TowerRedOn
				= BlinkFlash( m.m_TowerSetupSetting.ManualStop.LightRedChoise );		// Red
			m.OutWrite.TowerYellowOn = m.OutSet.TowerYellowOn
				= BlinkFlash( m.m_TowerSetupSetting.ManualStop.LightYellowChoise );		// Yellow
			m.OutWrite.TowerGreenOn	= m.OutSet.TowerGreenOn
				= BlinkFlash( m.m_TowerSetupSetting.ManualStop.LightGreenChoise );		// Green	
		}
		else
		{
			// Nerver be here
		}
	}
}

// 1.0Af
// Rmove this function, and re-build new one
/*
void CThIOReadWrite::SetLimitation()
{
	if(m.Info.bIOMonitor)
		return;
	// Note : if IO Montior Open. No setting by this function.

	if(m.Info.bError)
	{				
		m.OutWrite.TowerGreenOn		= m.OutSet.TowerGreenOn		= false;
		m.OutWrite.TowerYellowOn	= m.OutSet.TowerYellowOn	= false;
		m.OutWrite.TowerBuzzerOn	= m.OutSet.TowerBuzzerOn	= m.Info.bAlarmTimer;
		if( m.Info.bBuzzer )
			m.OutWrite.TowerBuzzerOn = m.OutSet.TowerBuzzerOn = m.Info.bAlarmTimer;
		else
			m.OutWrite.TowerBuzzerOn = m.OutSet.TowerBuzzerOn = false;
		
		m.OutWrite.TowerRedOn = m.OutSet.TowerRedOn = m.Info.bAlarmTimer;
		return;
	}
	// Note : there have a error
	// Then We set alarm output and return.

	// Set lamp
	if( m.Info.iStatus == theApp.enInitial )
	{		
		m.OutWrite.TowerRedOn = m.OutSet.TowerRedOn = true;
		m.OutWrite.TowerYellowOn = m.OutSet.TowerYellowOn = false;
		m.OutWrite.TowerGreenOn	= m.OutSet.TowerGreenOn = true;
		// turn on Green, Others turn off
	}
	else if( m.Info.iStatus == theApp.enUninitial )
	{
		m.OutWrite.TowerRedOn = m.OutSet.TowerRedOn = false;
		m.OutWrite.TowerYellowOn = m.OutSet.TowerYellowOn = true;
		m.OutWrite.TowerGreenOn	= m.OutSet.TowerGreenOn = false;
	}
	else if( !f.IsPause() )
	{
		// Note : In Action
		// @1: enCycle.
		// @2: enManual.
		// @3: enOneCycle.
		// @4: enOverride.
		m.OutWrite.TowerRedOn = m.OutSet.TowerRedOn = false;
		m.OutWrite.TowerYellowOn = m.OutSet.TowerYellowOn = false;
		m.OutWrite.TowerGreenOn	= m.OutSet.TowerGreenOn = true;	
	}
	else
	{
		// Note : Not In Action
		// The handler is STOP
		m.OutWrite.TowerRedOn = m.OutSet.TowerRedOn = false;
		m.OutWrite.TowerYellowOn = m.OutSet.TowerYellowOn = true;
		m.OutWrite.TowerGreenOn	= m.OutSet.TowerGreenOn = false;	
	}
}
*/

BEGIN_MESSAGE_MAP(CThIOReadWrite, CWinThread)
	//{{AFX_MSG_MAP(CThIOReadWrite)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CThIOReadWrite message handlers
