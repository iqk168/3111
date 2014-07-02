// Interface.cpp: implementation of the CInterface class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Interface.h"
#include "ComInterface.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

UINT ReadThread(LPVOID p)
{
	char buff[100] = {0};
	long read;
	CString csBuffer;

	while(m.Com.IsOpen())
	{
		read = m.Com.GetString(buff);
		if(read > 0)
		{
			csBuffer += buff;
			if((csBuffer.Find("<<Ready>>", 0)) != -1)
			{
				csBuffer.Empty(); //Clear String 
				csBuffer = _T("<<Start>>");
				m.Com.WriteString(csBuffer.GetBuffer(0), csBuffer.GetLength());
				csBuffer.Empty(); //Clear String 
			}
			else if((csBuffer.Find("<<Go>>", 0)) != -1)
			{
				csBuffer.Empty(); //Clear String 
//				csBuffer = _T("<<Bin=E1>>");
				csBuffer.Format("<<Bin=E%d>>", m.iValue );
				m.Com.WriteString(csBuffer.GetBuffer(0), csBuffer.GetLength());
				csBuffer.Empty(); //Clear String 	
				
				m.Count++;
			}
			else if((csBuffer.Find("<<SV=45.00,SoakTime=8.00,StableTime=15.00,Tolerance=1.00>>", 0)) != -1)
			{
				// <<SV=45.00,SoakTime=8.00,StableTime=15.00,Tolerance=1.00>>
				csBuffer.Empty(); //Clear String 
				csBuffer = "<<SV=46.00,SoakTime=30.00,StableTime=35.00,Tolerance= 3.00>>";
				m.Com.WriteString(csBuffer.GetBuffer(0), csBuffer.GetLength());
				csBuffer.Empty(); //Clear String			
			}

			//將收到的資料Show到螢幕上
			theApp.Add(buff, read);
			memset(buff, 0, sizeof(buff)); // Clear buffer
		}
		Sleep(20);
	}

	AfxEndThread(0);
	return 0;
}

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

bool CInterface::Open(int iComNo, int iBaudRate, int iDataBit, 
					  int iStopBit, int iParityCheck)
{
	if(m_hComm != NULL)
		Close();

	iComNo++; // Com Port 由 1 開始
	if(iComNo < 1 && iComNo > 10)
		iComNo = 1;

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

	switch(iDataBit)
	{
	case 0:
		iDataBit = 7;
		break;
	default:
		iDataBit = 8;
		break;
	}

	DCB PortDCB;
	COMMTIMEOUTS CommTimeouts;
	CString cs;

	// if(m.Com.Open(m_iPortNo, m_iBaudRate, m_iDataBit, m_iStopBit, m_iParityCheck))

	cs.Format("COM%d", iComNo);
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
	PortDCB.ByteSize = iDataBit;						// Number of bits/bytes, 4-8 
	PortDCB.Parity = iParityCheck;			// 0-4=no,odd,even,mark,space 
	PortDCB.StopBits = iStopBit;				// 0,1,2 = 1, 1.5, 2 
	
	if(iParityCheck > 0)
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
		return false;
	}

	// Retrieve the time-out parameters for all read and write operations
	// on the port. 
	GetCommTimeouts(m_hComm, &CommTimeouts);
	
	// Change the COMMTIMEOUTS structure settings.
	CommTimeouts.ReadIntervalTimeout = MAXDWORD;  
	CommTimeouts.ReadTotalTimeoutMultiplier = 0;  
	CommTimeouts.ReadTotalTimeoutConstant = 0;    
	CommTimeouts.WriteTotalTimeoutMultiplier = 10;	// 10  
	CommTimeouts.WriteTotalTimeoutConstant = 1000;		// 1000    
	
	// Set the time-out parameters for all read and write operations
	// on the port. 
	if (!SetCommTimeouts(m_hComm, &CommTimeouts))
	{
		Close();
		return false;
	}
	
	// Direct the port to perform extended functions SETDTR and SETRTS.
	// SETDTR: Sends the DTR (data-terminal-ready) signal.
	// SETRTS: Sends the RTS (request-to-send) signal. 
	EscapeCommFunction(m_hComm, SETDTR);
	EscapeCommFunction(m_hComm, SETRTS);

	Clear();

	return true;
}

void CInterface::Clear()
{
	PurgeComm(m_hComm, PURGE_TXCLEAR | PURGE_RXCLEAR
		| PURGE_TXABORT | PURGE_RXABORT);
}

long CInterface::GetString(char *buffer)
{
	unsigned long ulNumRead = 0;
	::ReadFile(m_hComm, buffer, 100, &ulNumRead, NULL);
	
	return ulNumRead;
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

bool CInterface::IsOpen()
{
	if(m_hComm != NULL)
		return true;
	else
		return false;
}
