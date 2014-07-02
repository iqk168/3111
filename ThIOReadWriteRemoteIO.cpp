// ThIOReadWriteRemoteIO.cpp : implementation file
//

#include "stdafx.h"
#include "deer.h"
#include "ThIOReadWriteRemoteIO.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CThIOReadWriteRemoteIO

IMPLEMENT_DYNCREATE(CThIOReadWriteRemoteIO, CWinThread)

CThIOReadWriteRemoteIO::CThIOReadWriteRemoteIO()
{
	m_hComm = NULL;

	m_dTorqueValue = 0.0;
	m_dOldTorqueValue = 0.0;
}

CThIOReadWriteRemoteIO::~CThIOReadWriteRemoteIO()
{
	Close();

	TRACE("~CThIOReadWriteRemoteIO\n");
}
bool CThIOReadWriteRemoteIO::Init()
{
	bool bOK = true;
#ifdef _Demo
#else
	if( !Open( m.m_HandlerComPort.iPortIOModule ))
	{
		bOK = false;
	}
#endif
	return bOK;
}
bool CThIOReadWriteRemoteIO::Open(int ComNo, int BaudRate)
{
	ret = ND_ReleaseComm(ComNo);
    ret = ND_InitialComm(ComNo, BAUDRATE_9600, 8, 0, 0);

	return true;
}
void CThIOReadWriteRemoteIO::Clear()
{
	PurgeComm(m_hComm, PURGE_TXCLEAR | PURGE_RXCLEAR
		| PURGE_TXABORT | PURGE_RXABORT);
}
bool CThIOReadWriteRemoteIO::Close()
{
	if(m_hComm == INVALID_HANDLE_VALUE || m_hComm == NULL)
	{
		m_hComm = NULL;
		return true;
	}

	bool b = ::CloseHandle(m_hComm) == 0 ? false : true;
	if(b)
		m_hComm = NULL;

	return b;
}
bool CThIOReadWriteRemoteIO::ReadInput()
{
	unsigned char*  in = (unsigned char *)&m.RemoteInStatus;
	unsigned short	i;
	unsigned long inputData;
	Ret = ND_ReadDI(m.m_HandlerComPort.iPortIOModule, m.m_HandlerComPort.iIDIOModuleIDIn, &inputData, 6054);
	long m_lStart = ::GetTickCount();
	if( Ret != 0 )
	{
		m.DebugError.ReadRemoteErr++;
		TRACE("ND_ReadDI Error\n");
	}
	else
	{
		int iSize = sizeof(m.RemoteInStatus);
		for ( i = 0; i < iSize ; i++ )
			in[i] = (unsigned char)( ( inputData >> i ) & 0x00000001);
	}
	m.DebugError.ReadRemoteSpendTime += ::GetTickCount() - m_lStart;
	m.DebugError.ReadRemoteCount++;

	return true;
}
bool CThIOReadWriteRemoteIO::SetOutput()
{
#ifdef _Demo
	return true;
#endif

	int i = 0;
	unsigned char*	outStatus = (unsigned char *)&m.RemoteOutStatus;
	unsigned char*	outputWrite = (unsigned char *)&m.RemoteOutWrite;
	unsigned short	outputValue = 0;

	// Protect IO Setting 
	m.RemoteOutWrite = m.RemoteOutSet;

	int iSize = sizeof(m.RemoteOutSet);
	for (i = 0; i <iSize; i++)
	{
		outputValue |= (outputWrite[i] << i);	
		outStatus[i] = outputWrite[i];	
	}	
	
	U16 output;
	output = outputValue;

	ret = ND_WriteDOPort(m.m_HandlerComPort.iPortIOModule, m.m_HandlerComPort.iIDIOModuleIDOut, 0, (output & 0xff), 6056);
	if( ret != 0 )
	{
		TRACE("ND_WriteDOPort Error1\n");
	}

	ret = ND_WriteDOPort(m.m_HandlerComPort.iPortIOModule, m.m_HandlerComPort.iIDIOModuleIDOut, 1, (output >> 0x8), 6056);
	if( ret != 0 )
	{
		TRACE("ND_WriteDOPort Error2\n");
	}
	
	// 1.0Af
	// Remove this
	/*
	ret = ND_ReadBackDO(m.m_HandlerComPort.iPortIOModule, m.m_HandlerComPort.iIDIOModuleIDOut, &output, 6056);
	if( ret != 0 )
	{
		TRACE("ND_ReadBackDO Error\n");
	}
	*/

	return true;
}
void CThIOReadWriteRemoteIO::SetTorqueValue( double dValue)
{
	m_dTorqueValue = dValue;
}
void CThIOReadWriteRemoteIO::GetTorqueValue( double &dValue)
{
	dValue = m_dTorqueValue;
}
void CThIOReadWriteRemoteIO::CloseAllIOOutput()
{
	m.RemoteOutSet.BtnStartOn		= false; // 00	Set Panel Start light on
	m.RemoteOutSet.BtnStopOn		= false; // 01	Set Panel Stop light on
	m.RemoteOutSet.BtnSkipOn		= false; // 02	Set Panel Skip light on
	m.RemoteOutSet.BtnRetryOn		= false; // 03	Set Panel Retry light on
	m.RemoteOutSet.BtnResetOn		= false; // 04	Set Panel Reset light on
	m.RemoteOutSet.BtnInitialOn		= false; // 05	Set Panel Initial light onOne Cycel light on
	m.RemoteOutSet.BtnOneCycleOn	= false; // 06	Set Panel One Cycel light on
	m.RemoteOutSet.Rotator			= false; // 07	Set Rotator
	m.RemoteOutSet.HeaterOn			= false; // 08	Heater On
	m.RemoteOutSet.Unuse09			= false; // 09	Unuse
	m.RemoteOutSet.Unuse10			= false; // 10	Unuse
	m.RemoteOutSet.Unuse11			= false; // 11	Unuse
	m.RemoteOutSet.Unuse12			= false; // 12	Unuse
	m.RemoteOutSet.Unuse13			= false; // 13	Unuse
	m.RemoteOutSet.Unuse14			= false; // 14	Unuse
}

// 1.0Af
// Remove this, and re-build new one
/*
bool CThIOReadWriteRemoteIO::SetTorque()
{
	if( m_dOldTorqueValue != m_dTorqueValue )
	{	
		CString csMsg = _T("");
		csMsg.Format("Change Torque: %7.3f", m_dTorqueValue);
		f.CWinMessage(csMsg, theApp.enDManual );
		m_dOldTorqueValue = m_dTorqueValue;
		CString csValue = _T("");
		csValue.Format("+0%.3lf\r", m_dTorqueValue);
		ret = ND_WriteChanAO( m.m_HandlerComPort.iPortPIDValue, m.m_HandlerComPort.iIDPIDValue, 0, csValue.GetBuffer(csValue.GetLength()) );
		
		if( ret != 0 )
			return false;
		else
			return true;		
	}
	return true;
}
*/
bool CThIOReadWriteRemoteIO::SetTorque()
{
#ifdef _Demo
	return true;
#endif

	if( m_dOldTorqueValue != m_dTorqueValue )
	{	
		CString csMsg = _T("");
		csMsg.Format("Change Torque: %7.3f", m_dTorqueValue);
		f.CWinMessage(csMsg, theApp.enDManual );
		m_dOldTorqueValue = m_dTorqueValue;
		CString csValue = _T("");

		if( m_dTorqueValue >= 10 )
			csValue.Format("+10.0\r", m_dTorqueValue);
		else
			csValue.Format("+0%.3lf\r", m_dTorqueValue);
//		csValue.Format("+0%.3lf\r", m_dTorqueValue);
		ret = ND_WriteChanAO( m.m_HandlerComPort.iPortPIDValue, m.m_HandlerComPort.iIDPIDValue, 0, csValue.GetBuffer(csValue.GetLength()) );
		
		if( ret != 0 )
			return false;
		else
			return true;		
	}
	return true;
}
BOOL CThIOReadWriteRemoteIO::InitInstance()
{
	if(!Init())
	{
		CString csMsg = _T("");
		csMsg.Format("Remote IO Module Open Fail");
		f.DMsg.DMsg( csMsg + _DMsgMark, false );
#ifdef _Demo
#else
		// Remote IO Open Fail
		if( m.Setting.m_bEnableProgramInitialStart == 1 )
		{
		}
		else
			AfxMessageBox( csMsg );
#endif
		m.InterLock.IsRemoteIODone = true;
		return TRUE;
	}
	else
	{
		// Remote IO Open OK
		CString csMsg = _T("");
		csMsg.Format("Remote IO Module Open Success");
		f.DMsg.DMsg( csMsg );
	}

	//
	m.InterLock.IsRemoteIODone = true;

	while(m.Info.bRunning)
	{
#ifdef _Demo
#else		
		ReadInput();	// Nudm - 6054		
		SetOutput();	// Nudm - 6056		
		SetTorque();	// Nudm - 6024
#endif
		Sleep(_Wait);
	}

	//
	m_dTorqueValue = 0.0;
	SetTorque();

	CloseAllIOOutput();
	SetOutput();

	return TRUE;
}

int CThIOReadWriteRemoteIO::ExitInstance()
{
	TRACE("CThIOReadWriteRemoteIO\n");
	// TODO:  perform any per-thread cleanup here
	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(CThIOReadWriteRemoteIO, CWinThread)
	//{{AFX_MSG_MAP(CThIOReadWriteRemoteIO)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CThIOReadWriteRemoteIO message handlers
