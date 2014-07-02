// TorqueCtrl.cpp: implementation of the CTorqueCtrl class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "deer.h"
#include "TorqueCtrl.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTorqueCtrl::CTorqueCtrl()
{
	//
	m_hComm		= NULL;

	m_iComNo	= 0;
	m_iBaudRate = 0;
	m_iByteSize = 0;
	m_iParity	= 0;
	m_iStopBit	= 0;

	OutputPort	= 0;
}

CTorqueCtrl::~CTorqueCtrl()
{

}
bool CTorqueCtrl::FlowControlApi(double dValue, int &iReturnCode)
{
	I16 ret;
	ret = ND_ReleaseComm(m.m_HandlerComPort.iPortPIDValue);
    ret = ND_InitialComm(m.m_HandlerComPort.iPortPIDValue, BAUDRATE_9600, 8, 0, 0);

	CString csValue = _T("");
	csValue.Format("+0%.3lf\r", dValue);

	ret = ND_WriteChanAO( m.m_HandlerComPort.iPortPIDValue, m.m_HandlerComPort.iIDPIDValue, 0, csValue.GetBuffer(csValue.GetLength()) );

	iReturnCode = ret;

	if(ret != 0 )
		return false;
	else
		return true;
}
void CTorqueCtrl::FlowControl(long iPower)
{
	if( OutputPort == 0 )
		return;

	double OutVoltage = iPower * 0.111;

	// Debug 
	CString csMsg = _T("");
	csMsg.Format("Power = %7.3f", OutVoltage );
	AfxMessageBox( csMsg );
	
	// 寫入電空比例閥內
	if (OpenFlowControl( OutputPort ))
	{	
		char torqueForceCommand[18];
		char tempBuff[80];
		
		int m_addr = 1;
		int station_id = 0 + 'A'; 
		
		double lfValue = OutVoltage;
		
		CString cs;
		_snprintf(torqueForceCommand, sizeof(torqueForceCommand), "#%2.2d%c%+07.3lf\r", m_addr, station_id, lfValue);
		cs = torqueForceCommand;
		
		bool setDone = false;
		int retryTimes = 0;
		
		// 清除rx的buffer
		ConGetString(tempBuff, 80);
		ConWriteString(cs);
		
		Close();
	}
}

bool CTorqueCtrl::Close()
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

long CTorqueCtrl::ConGetString(char *buffer, int iMaxRead)
{
	CSingleLock L(&object);
	L.Lock();
	
	unsigned long ulNumRead = 0;
	if(L.IsLocked())
	{
		::ReadFile(m_hComm, buffer, iMaxRead, &ulNumRead, NULL);
		
		L.Unlock();
	}
	
	return ulNumRead;
}
long CTorqueCtrl::ConWriteString(CString cs)
{
	CSingleLock L(&object);
	L.Lock();
	
	unsigned long iLength = 0;
	
	WriteFile(m_hComm, cs.GetBuffer(0), cs.GetLength(), &iLength, NULL);
	
	L.Unlock();

	return iLength;
}
bool CTorqueCtrl::OpenFlowControl(int ComNo, int BaudRate)
{
	if(m_hComm != NULL)
		Close();

	m_iComNo		= ComNo;  
	m_iBaudRate		= BaudRate;
	m_iByteSize		= 8;
	m_iParity		= NOPARITY;
	m_iStopBit		= ONESTOPBIT;

	DCB PortDCB;
	COMMTIMEOUTS CommTimeouts;
	CString cs;

	if(m_iComNo < 1 && m_iComNo > 30)
		m_iComNo = 1;
	if (m_iComNo < 10)
		cs.Format("COM%d", m_iComNo);
	else
		cs.Format("\\\\.\\COM%d", m_iComNo);
	// Open the serial port.
	m_hComm = CreateFile(cs, // Pointer to the name of the port
		GENERIC_READ | GENERIC_WRITE, // Access (read/write) mode
		0,            // Share mode
		NULL,         // Pointer to the security attribute
		OPEN_EXISTING,// How to open the serial port
		0,            // Port attributes
		NULL);        // Handle to port with attribute
	
	// If it fails to open the port, return FALSE.
	if(m_hComm == INVALID_HANDLE_VALUE) 
	{
		CString cs = _T("");
		cs.Format("Open RS232 Error !!.\n Please check interface 'Com Port %d' setting and try again.\n", m_iComNo);
//		AfxMessageBox(cs);
		return false;
	}
	
	PortDCB.DCBlength = sizeof (DCB);     
	
	// Get the default port setting information.
	GetCommState (m_hComm, &PortDCB);
	
	// Change the DCB structure settings.
	PortDCB.BaudRate = m_iBaudRate;				// Current baud 
	PortDCB.ByteSize = m_iByteSize;				// Number of bits/bytes, 4-8 (Bit Length)
	PortDCB.Parity = m_iParity;					// 0-4=no,odd,even,mark,space 
	PortDCB.StopBits = m_iStopBit;				// 0,1,2 = 1, 1.5, 2  //ONESTOPBIT

	if(m_iParity >0) 
		PortDCB.fParity = TRUE;               // Enable parity checking. 
	else
		PortDCB.fParity = FALSE;               // Enable parity checking. 
	
	PortDCB.fBinary = FALSE;               // Binary mode; no EOF check 
	PortDCB.fOutxCtsFlow = FALSE;         // No CTS output flow control 
	PortDCB.fOutxDsrFlow = FALSE;         // No DSR output flow control 
	PortDCB.fDtrControl = DTR_CONTROL_DISABLE; 
	// DTR flow control type 
	PortDCB.fDsrSensitivity = FALSE;      // DSR sensitivity 
	PortDCB.fTXContinueOnXoff = FALSE;     // XOFF continues Tx 
	PortDCB.fOutX = FALSE;                // No XON/XOFF out flow control 
	PortDCB.fInX = FALSE;                 // No XON/XOFF in flow control 
	PortDCB.fErrorChar = FALSE;           // Disable error replacement. 
	PortDCB.fNull = TRUE;                // Disable null stripping. 
	PortDCB.fRtsControl = RTS_CONTROL_DISABLE; 
	// RTS flow control 
	PortDCB.fAbortOnError = FALSE;        // Do not abort reads/writes on 
	// error.

	// Configure the port according to the specifications of the DCB 
	// structure.
	if (!SetCommState (m_hComm, &PortDCB))
	{
		Close();
		AfxMessageBox("Open RS232 Error !!.\n Please check interface 'Com Port' setting and try again.\n");
		return false;
	}

	// Retrieve the time-out parameters for all read and write operations
	// on the port. 
	GetCommTimeouts(m_hComm, &CommTimeouts);
	
	// Change the COMMTIMEOUTS structure settings.
	CommTimeouts.ReadIntervalTimeout = 1000; // MAXDWORD  
	CommTimeouts.ReadTotalTimeoutMultiplier = 3;  //0, Microsoft : 3
	CommTimeouts.ReadTotalTimeoutConstant = 3;    //0, Microsoft : 3
	CommTimeouts.WriteTotalTimeoutMultiplier = 20;	// 10  , Microsoft : 20
	CommTimeouts.WriteTotalTimeoutConstant = 1000;		// 1000    
		

	// Set the time-out parameters for all read and write operations
	// on the port. 
	if (!SetCommTimeouts(m_hComm, &CommTimeouts))
	{
		Close();
		AfxMessageBox("Open RS232 Error !!.\n Please check interface 'Com Port' setting and try again.\n");
		return false;
	}
	
	// Direct the port to perform extended functions SETDTR and SETRTS.
	// SETDTR: Sends the DTR (data-terminal-ready) signal.
	// SETRTS: Sends the RTS (request-to-send) signal. 
	EscapeCommFunction(m_hComm, SETDTR);
	EscapeCommFunction(m_hComm, SETRTS);

	OutputPort = ComNo;

	Clear();

	return true;
}
void CTorqueCtrl::Clear()
{
	PurgeComm(m_hComm, PURGE_TXCLEAR | PURGE_RXCLEAR
		| PURGE_TXABORT | PURGE_RXABORT);
}