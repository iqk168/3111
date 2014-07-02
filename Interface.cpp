// Interface.cpp: implementation of the CInterface class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "deer.h"
#include "Interface.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#define CHECK_SITE			0x00000001
#define CHECK_CONNECT		0x00000002
#define CHECK_GETNEXTSTEP	0x00000004

#define TEST_SETSTEP		0x00000008
#define TEST_START			0x00000010
#define TEST_END			0x00000020
#define TEST_NOTIFY			0x00000040
#define TEST_READY			0x00000080

#define STEP_FINISH			0x00000100
#define TEST_FINISH		    0x00000200
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CInterface::CInterface()
{
	m_hComm = NULL;
}

CInterface::~CInterface()
{

}

bool CInterface::Close()
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
bool CInterface::Open(int iComNo, int iBaudRate, CString csHeader,
		CString csTail, int iDataBit, int iStopBit, int iParityCheck)
{
	if(m_hComm != NULL)
		Close();

	// 1.5
	m_csHeader = csHeader;
	m_csTail = csTail;

	DCB PortDCB;
	COMMTIMEOUTS CommTimeouts;

	switch(iBaudRate)
	{
	case 0:
		iBaudRate = 4800;
		break;
	case 1:
		iBaudRate = 9600;
		break;
	case 2:
		iBaudRate = 19200;
		break;
	case 3:
		iBaudRate = 38400;
		break;
	case 4:
		iBaudRate = 115200;
		break;
	default:
		iBaudRate = 9600;
		break;
	}
	// Reset Baud Rate
	switch(iDataBit)
	{
	case 0:
		iDataBit = 7;
		break;
	case 1:
		iDataBit = 8;
		break;
	default:
		iDataBit = 8;
		break;
	}
	// Reset Data Bit

	CString cs;

	cs.Format("\\\\.\\COM%d", iComNo);
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
		return FALSE;
	
	PortDCB.DCBlength = sizeof (DCB);     
	
	// Get the default port setting information.
	GetCommState (m_hComm, &PortDCB);
	
	// Change the DCB structure settings.
	PortDCB.BaudRate = iBaudRate;				// Current baud 
//	PortDCB.ByteSize = 8;						// Number of bits/bytes, 4-8 
	PortDCB.ByteSize = iDataBit;
//	PortDCB.Parity = 0;							// 0-4=no,odd,even,mark,space 
	PortDCB.Parity = iParityCheck;


//	PortDCB.StopBits = ONESTOPBIT;				// 0,1,2 = 1, 1.5, 2 
	PortDCB.StopBits = iStopBit;

//	PortDCB.fParity = FALSE;					// Enable parity checking. 
	if(iParityCheck > 0)
		PortDCB.fParity = TRUE;					// Enable parity checking. 
	else
		PortDCB.fParity = FALSE;				// Enable parity checking. 
	
	// Code
	PortDCB.fBinary = FALSE;              // Binary mode; no EOF check 
	PortDCB.fOutxCtsFlow = FALSE;         // No CTS output flow control 
	PortDCB.fOutxDsrFlow = FALSE;         // No DSR output flow control 
	PortDCB.fDtrControl = DTR_CONTROL_DISABLE; 
	// DTR flow control type 
	PortDCB.fDsrSensitivity = FALSE;      // DSR sensitivity 
	PortDCB.fTXContinueOnXoff = FALSE;    // XOFF continues Tx 
	PortDCB.fOutX = FALSE;                // No XON/XOFF out flow control 
	PortDCB.fInX = FALSE;                 // No XON/XOFF in flow control 
	PortDCB.fErrorChar = FALSE;           // Disable error replacement. 
	PortDCB.fNull = TRUE;				  // Disable null stripping. 
	PortDCB.fRtsControl = RTS_CONTROL_DISABLE; 
	// RTS flow control 
	PortDCB.fAbortOnError = FALSE;        // Do not abort reads/writes on 
	// error.
	// Code

	// Configure the port according to the specifications of the DCB 
	// structure.
	if (!SetCommState (m_hComm, &PortDCB))
	{
		Close();
		return false;
	}

	// Retrieve the time-out parameters for all read and write operations
	// on the port. 
	GetCommTimeouts(m_hComm, &CommTimeouts);
	
	// Change the COMMTIMEOUTS structure settings.
	// CommTimeouts.ReadIntervalTimeout = 1;//MAXDWORD;  
	CommTimeouts.ReadIntervalTimeout = MAXDWORD;//MAXDWORD;
	
	// CommTimeouts.ReadTotalTimeoutMultiplier = 1;  
	// CommTimeouts.ReadTotalTimeoutConstant = 1;    
	CommTimeouts.ReadTotalTimeoutMultiplier = 1;  
	CommTimeouts.ReadTotalTimeoutConstant = 1;  

	CommTimeouts.WriteTotalTimeoutMultiplier = 10;	// 10  
	CommTimeouts.WriteTotalTimeoutConstant = 1000;		// 1000    
	
	// Set the time-out parameters for all read and write operations
	// on the port. 
	if (!SetCommTimeouts(m_hComm, &CommTimeouts))
	{
		Close();
		return false;
	}
	
	// Code
	// Direct the port to perform extended functions SETDTR and SETRTS.
	// SETDTR: Sends the DTR (data-terminal-ready) signal.
	// SETRTS: Sends the RTS (request-to-send) signal. 
	EscapeCommFunction(m_hComm, SETDTR);
	EscapeCommFunction(m_hComm, SETRTS);
	// Code

	Clear();

	return true;
}

void CInterface::Clear()
{
	PurgeComm(m_hComm, PURGE_TXCLEAR | PURGE_RXCLEAR
		| PURGE_TXABORT | PURGE_RXABORT);
	m_csTelegramBuffer.Empty();
}

bool CInterface::GetTelegram(CString &csTelegram)
{	
	unsigned char cTemp[1001] = {0};
	unsigned long ulNumRead = 0;
	::ReadFile(m_hComm, cTemp, sizeof(cTemp), &ulNumRead, NULL);

	m_newData = false;
	m_newDataLength = 0;

	if(ulNumRead != 0)
	{
		for(unsigned int i=0; i<ulNumRead; i++)
		{
			m_csNewData[i] = cTemp[i];	
		}
		m_newData = true;
		m_newDataLength = ulNumRead;

		return true;
	}
	
	return false;

}

void CInterface::WriteString(char c, int iSize)
{
	unsigned long iLength = 0;
	char cSend[100] = {0};
	for(int i=0; i<iSize; i++)
		cSend[i] = c;

	i=0;
	while(WriteFile(m_hComm, cSend, iSize, &iLength, NULL) == 0)
	{
		i++;
		if(i>5) break;
		Sleep(1);
	}
}

long CInterface::GetString(char *buffer)
{
	unsigned long ulNumRead = 0;
	::ReadFile(m_hComm, buffer, 100, &ulNumRead, NULL);
	
	return ulNumRead;
}

void CInterface::WriteTelegram(CString tele)
{
	unsigned long iLength = 0;

	if(tele.Find(m_csHeader) == -1)
		tele = m_csHeader + tele;
	if(tele.Find(m_csTail) == -1)
		tele += m_csTail;

	int i=0;
	while(WriteFile(m_hComm, tele.GetBuffer(0), tele.GetLength(), &iLength, NULL) == 0)
	{
		i++;
		if(i>5) break;
		Sleep(100);
	}

	m_csTelegramBuffer.Empty();
}

void CInterface::WriteString(char *buffer, int iSize)
{
	unsigned long iLength = 0;

	int i=0;
	while(WriteFile(m_hComm, buffer, iSize, &iLength, NULL) == 0)
	{
		i++;
		if(i>5) break;
		Sleep(100);
	}
}

bool CInterface::PickupTelegram(CString &csTelegram)
{
	csTelegram = _T("");
	int iStart = m_csTelegramBuffer.Find(m_csHeader);
	int iEnd = m_csTelegramBuffer.Find(m_csTail, iStart);
	if(iStart == -1 || iEnd == -1) 
		return false;

	csTelegram = m_csTelegramBuffer.Mid(iStart+m_csHeader.GetLength(),
		iEnd-m_csHeader.GetLength()-iStart);
	m_csTelegramBuffer.Delete(0, iEnd + m_csTail.GetLength());

	m_csTelegramBuffer.FreeExtra();

	return true;
}
