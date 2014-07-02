// DriveWest.cpp: implementation of the CDriveWest class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "deer.h"
#include "DriveWest.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDriveWest::CDriveWest()
{
	hProcess = NULL;

	m_hComm = NULL;

	for(int i=0; i<_MaxWestDevice; i++)
	{
		dPV[i] = _Device_Error;
		dSV[i] = _Device_Error;
		dOffSet[i] = _Device_Error;
	}
}

CDriveWest::~CDriveWest()
{
	Close();
}
UINT CDriveWest::WestCtrlThread(LPVOID p)
{
	CDriveWest *dr = (CDriveWest *)p;

	int err = 0;
	while(dr->IsConnected())
	{
		if(dr->CmdSet.GetSize() > 0)
		{			
			short addr = dr->CmdSet.GetAt(0).addr;
			if( addr == enSV )
			{
				int iDevice = dr->CmdSet.GetAt(0).id;
				double dSV = dr->CmdSet.GetAt(0).value;
				if(!dr->SetTemperature( iDevice, dSV ))
					err++;
				else
				{	err = 0;
					dr->CmdSet.RemoveAt(0);
				}
			}
			else if( addr == enOffset )
			{
				int iDevice = dr->CmdSet.GetAt(0).id;
				double dOffset = dr->CmdSet.GetAt(0).value;
				if(!dr->SetOffsetTemperature( iDevice, dOffset ))
					err++;
				else
				{	err = 0;
					dr->CmdSet.RemoveAt(0);
				}
			}

			if(err > 3)
				dr->CmdSet.RemoveAt(0);
		}
		else
		{
			int i = 0;
			// PV
			for(i=1; i<_MaxWestDevice; i++)
			{
				if(dr->IsConnected())
				{
					dr->dPV[i] = dr->ReadDisplayTemperature(i);
				}
				else
					dr->dPV[i] = _Device_Error;
			}
			// SV
			for(i=1; i<_MaxWestDevice; i++)
			{
				if(dr->IsConnected())
				{
					dr->dSV[i] = dr->ReadSettingTemperature(i);
				}
				else 
					dr->dSV[i] = _Device_Error;
			}
			// Offset
			for(i=1; i<_MaxWestDevice; i++)
			{
				if(dr->IsConnected())
				{
					dr->dOffSet[i] = dr->ReadOffsetTemperature(i);
				}
				else
					dr->dOffSet[i] = _Device_Error;
			}
		}

		// Make sure program close. Thread will be close
		if( !m.Info.bRunning )
			break;

		Sleep(1);
	}

	dr->threadEvent.PulseEvent();
	AfxEndThread(0);
	return 0;
}
void CDriveWest::AddCmd(byte id, short addr, double value)
{
	tagCmd p;
	p.id = id;
	
	p.addr = addr;
	p.value = value;
	CmdSet.Add(p);
}
void CDriveWest::GetValue(double *pPV, double *pSV)
{
	for(int i=0; i<_MaxWestDevice; i++)
	{
		pPV[i] = dPV[i];
		pSV[i] = dSV[i];
	}
}
void CDriveWest::GetOffsetValue(double *pOffset)
{
	for(int i=0; i<_MaxWestDevice; i++)
	{
		pOffset[i] = dOffSet[i];
	}
}
bool CDriveWest::Close()
{
	MSG				msg;
	LARGE_INTEGER	start, end, freq;
	DWORD			nThreadExitCode = 0;
	BOOL			bSuccess = FALSE;

	if(m_hComm == INVALID_HANDLE_VALUE || m_hComm == NULL)
	{
		m_hComm = NULL;
		return true;
	}

	bool b = ::CloseHandle(m_hComm) == 0 ? false : true;
	if(b)
		m_hComm = NULL;

	::QueryPerformanceFrequency(&freq);
	::QueryPerformanceCounter(&start);
	if(hProcess != NULL)
	{
	do
	{
		bSuccess = GetExitCodeThread(hProcess, &nThreadExitCode);
		::QueryPerformanceCounter(&end);

		if(::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			::TranslateMessage(&msg);
			::DispatchMessage(&msg);
		}
	}while(bSuccess && nThreadExitCode == STILL_ACTIVE && (end.QuadPart - start.QuadPart) / freq.QuadPart < 10);  //10ボ单10s, ㄌ沮惠―э
	}
	return b;
}
double CDriveWest::_RetrieveTemperature(CString &csValue)
{
	// return message : 'L', iDevice, 'M', "xxxx", format, "A*"
	// char NO:			 0     12      3    4567      8     9a
	if(csValue.GetLength() < 10) return _Device_Error;

	switch(csValue[8])
	{
	case '0':
		return atoi(csValue.Mid(4, 4));
		break;
	case '1':
		return atoi(csValue.Mid(4, 4)) / 10.0;
		break;
	case '2':
		return atoi(csValue.Mid(4, 4)) / 100.0;
		break;
	case '3':
		return atoi(csValue.Mid(4, 4)) / 1000.0;
		break;
	case '5':
		return -atoi(csValue.Mid(4, 4));
		break;
	case '6':
		return -atoi(csValue.Mid(4, 4)) / 10.0;
		break;
	case '7':
		return -atoi(csValue.Mid(4, 4)) / 100.0;
		break;
	case '8':
		return -atoi(csValue.Mid(4, 4)) / 1000.0;
		break;
	}
	return _Device_Error;
}
CString CDriveWest::_Send(CString cs)
{
	if(!m_bConnectStatus) 
		return _T("");

	unsigned long iLength;
	CString csResult = _T("");

	WriteFile(m_hComm, cs.GetBuffer(0), cs.GetLength(),
		&iLength, NULL);

	char cTemp[12] = {0};
	int iStart = ::GetTickCount();
	while(1)
	{
		if(!m.Info.bRunning)
			break;
		memset(cTemp, 0, sizeof(cTemp));
		ReadFile(m_hComm, cTemp, sizeof(cTemp)-1, &iLength, NULL);
		if(iLength != 0)
			csResult += cTemp;
		
		if(csResult.Find("*") != -1)
			return csResult;

		if((::GetTickCount() - iStart) > 200)
			return _T("");

		Sleep(_Wait);
	}

	return _T("");
}
CString CDriveWest::_Send(unsigned char *data, int len)
{
	CString cs;

	if(m_hComm == INVALID_HANDLE_VALUE) return _T("");

	unsigned long iLength;
	CString csResult = _T("");

	::WriteFile(m_hComm, (char *) data, len, &iLength, NULL);

	char cTemp[12] = {0};
	int iStart = ::GetTickCount();
	while(1)
	{
		if(0)
			break;
		memset(cTemp, 0, sizeof(cTemp));
		::ReadFile(m_hComm, cTemp, sizeof(cTemp)-1, &iLength, NULL);
		if(iLength != 0)
			csResult += cTemp;
		
		if(csResult.Find("*") != -1)
			return csResult;

		if((::GetTickCount() - iStart) > 200)
			return _T("");

		Sleep(_Wait);
	}

	return _T("");
}
/////////////////////////////////////////////////////////////
// 弄 Device 砆砞﹚ Offset 
// iDevice = 1, 2, 3,...
// Return :
//		degree of Centigrade
//	or
//		DEVICE_ERROR (_Device_Error) when Error
double CDriveWest::ReadOffsetTemperature(int iDevice)
{
	CString cs, cs1;
	cs1.Format("L%02dv?*", iDevice);
	cs = _Send((unsigned char *) cs1.GetBuffer(0), cs1.GetLength());
	if(cs.Find("A*") != -1)
		return _RetrieveTemperature(cs);

	return _Device_Error;
}
/*
double CDriveWest::ReadOffsetTemperature(int iDevice)
{
	CString cs, cs1;
	cs1.Format("L%02dv?*", iDevice);
	cs = _Send(cs1);
	if(cs.Find("A*") != -1)
		return _RetrieveTemperature(cs);

	return _Device_Error;
}
*/
/////////////////////////////////////////////////////////////
// 弄 Device 砆砞﹚璶笷放
// iDevice = 1, 2, 3,...
// Return :
//		degree of Centigrade
//	or
//		DEVICE_ERROR (_Device_Error) when Error
double CDriveWest::ReadSettingTemperature(int iDevice)
{
	CString cs, cs1;
	cs1.Format("L%02dS?*", iDevice);
	cs = _Send((unsigned char *) cs1.GetBuffer(0), cs1.GetLength());
	if(cs.Find("A*") != -1)
		return _RetrieveTemperature(cs);

	return _Device_Error;
}
double CDriveWest::ReadDisplayTemperature(int iDevice)
{
	CString cs, cs1;

	cs1.Format("L%02dM?*", iDevice);
	cs = _Send(cs1);
	if(cs == _T("") || cs.Find("??") > -1) return _Device_Error;

	return _RetrieveTemperature(cs);
}
BOOL CDriveWest::SetTemperature(int iDevice, double dTemperature)
{
	CString cs1, cs2;

	// Debug 
	CString csMsg = _T("");
	csMsg.Format("Device: %d ,Sv %5.2f", iDevice, dTemperature );
	f.CWinMessage( csMsg, theApp.enDWest );

	// 场糶计1, modify, Jeff.Su, 20120418
 	if (dTemperature>=0)
 	{
		if (dTemperature < 10) 
			cs1.Format("00%02.0f1*", dTemperature*10);
		else if (dTemperature < 100) 
			cs1.Format("0%3.0f1*", dTemperature*10);
		else if (dTemperature < 1000) 
			cs1.Format("%4.0f1*", dTemperature*10);
		else
			return FALSE;
	} 
	else
	{
		if (dTemperature > -10) 
			cs1.Format("00%02.0f6*", -dTemperature*10);
		else if (dTemperature > -100) 
			cs1.Format("0%3.0f6*", -dTemperature*10);
		else if (dTemperature > -1000) 
			cs1.Format("%4.0f6*", -dTemperature*10);
		else
			return FALSE;		
	}

	cs2.Format("L%02dS#", iDevice);		// L --> Controller, N --> iDevice, S --> Setpoint Ident, # --> indicate DATA is in following, * --> end char
	cs2 += cs1;							// LNS# + {DATA} --> type 3 messeage
	cs1 = _Send((unsigned char *) cs2.GetBuffer(0), cs2.GetLength());

	if(cs1.Find("I*") != -1)					// =-1 --> doesn't find the character
	{
		cs2.Format("L%02dSI*", iDevice);		// type 4 messeage
		cs1 = _Send((unsigned char *) cs2.GetBuffer(0), cs2.GetLength());
		if(cs1.Find("A*") != -1) return TRUE;
	} 

	return FALSE;
}

/*
BOOL CDriveWest::SetTemperature(int iDevice, double dTemperature)
{
	CString cs1, cs2;

	// Debug 
	CString csMsg = _T("");
	csMsg.Format("Device: %d ,Sv %5.2f", iDevice, dTemperature );
	f.CWinMessage( csMsg, theApp.enDWest );

	// 砞﹚放﹃ L%02dS#%d*, iDevice, iTemperature
	if (dTemperature < 10) 
		cs1.Format("00%d01*", dTemperature);
	else if (dTemperature < 100) 
		cs1.Format("0%2d01*", dTemperature);
	else if (dTemperature < 1000) 
		cs1.Format("%3d01*", dTemperature);
	else
		return FALSE;

	cs2.Format("L%02dS#", iDevice);
	cs2 += cs1;
	cs1 = _Send(cs2);

	if(cs1.Find("I*") != -1)
	{
		cs2.Format("L%02dSI*", iDevice);
		cs1 = _Send(cs2);
		if(cs1.Find("A*") != -1) return TRUE;
	}

	return FALSE;
}
*/
BOOL CDriveWest::SetOffsetTemperature(int iDevice, double dNewOffset)
{
	CString cs, cs1;

	// Debug 
	CString csMsg = _T("");
	csMsg.Format("Device: %d ,Offset %5.2f", iDevice, dNewOffset );
	f.CWinMessage( csMsg, theApp.enDWest );

	// 场砞计翴1, modify, Jeff.Su, 20120418
	if (dNewOffset >= 0)
	{
		if (dNewOffset < 10) 
			cs.Format("L%02dv#00%02.0f1*", iDevice, dNewOffset*10);	// L --> Controller, N --> iDevice, v --> PV offset, #, {DATA}
		else if (dNewOffset < 100)
			cs.Format("L%02dv#0%3.0f1*", iDevice, dNewOffset*10);
		else if (dNewOffset < 1000)
			cs.Format("L%02dv#%4.0f1*", iDevice, dNewOffset*10);
		else
			return FALSE;
	}
	else
	{
		if (dNewOffset > -10) 
			cs.Format("L%02dv#00%02.0f6*", iDevice, -dNewOffset*10);
		else if (dNewOffset > -100)
			cs.Format("L%02dv#0%3.0f6*", iDevice, -dNewOffset*10);
		else if (dNewOffset > -1000)
			cs.Format("L%02dv#%4.0f6*", iDevice, -dNewOffset*10);
		else
			return FALSE;
	}

	cs1 = _Send((unsigned char *) cs.GetBuffer(0), cs.GetLength());		// send type 3 messeage
	if(cs1.Find("I*") != -1)
	{
		cs.Format("L%02dvI*", iDevice);			// send type 4 messeage
		cs1 = _Send((unsigned char *) cs.GetBuffer(0), cs.GetLength());
		if(cs1.Find("A*") != -1)
			return TRUE;
	}
	return FALSE;
}
/*
BOOL CDriveWest::SetOffsetTemperature(int iDevice, double dNewOffset)
{
	// Debug 
	CString csMsg = _T("");
	csMsg.Format("Device: %df ,Offset %5.2f", iDevice, dNewOffset );
	f.CWinMessage( csMsg, theApp.enDWest );

	CString cs, cs1;

	if (dNewOffset > 0)
	{
		if (dNewOffset < 10) 
			cs.Format("L%02dv#00%d01*", iDevice, dNewOffset);
		else if (dNewOffset < 100)
			cs.Format("L%02dv#0%2d01*", iDevice, dNewOffset);
		else if (dNewOffset < 1000)
			cs.Format("L%02dv#%3d01*", iDevice, dNewOffset);
		else
			return FALSE;
	}
	else
	{
		dNewOffset = -dNewOffset;
		if (dNewOffset < 10) 
			cs.Format("L%02dv#00%d06*", iDevice, dNewOffset);
		else if (dNewOffset < 100)
			cs.Format("L%02dv#0%2d06*", iDevice, dNewOffset);
		else if (dNewOffset < 1000)
			cs.Format("L%02dv#%3d06*", iDevice, dNewOffset);
		else
			return FALSE;
	}

	cs1 = _Send(cs);
	if(cs1.Find("I*") != -1)
	{
		cs.Format("L%02dvI*", iDevice);
		cs1 = _Send(cs);
		if(cs1.Find("A*") != -1)
			return TRUE;
	}
	return FALSE;
}
*/
void CDriveWest::ShowErrorMessage(int iErrorCode)
{
	LPVOID lpMsgBuf;
	FormatMessage( 
		FORMAT_MESSAGE_ALLOCATE_BUFFER | 
		FORMAT_MESSAGE_FROM_SYSTEM | 
		FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL,
		iErrorCode,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
		(LPTSTR) &lpMsgBuf,
		0,
		NULL 
		);
	// Process any inserts in lpMsgBuf.
	// ...
	// Display the string.
//	AfxMessageBox((LPCTSTR)lpMsgBuf);
	// Free the buffer.
	LocalFree( lpMsgBuf );
}
bool CDriveWest::IsConnected()
{
	if(m_hComm == NULL)
		return false;

	return true;
}
BOOL CDriveWest::Open(int iWestComPortNo)
{
	DCB PortDCB;
	COMMTIMEOUTS CommTimeouts;
	CString cs;

	m_bConnectStatus = FALSE;

	cs.Format("COM%d", iWestComPortNo);

	char	 mystr[5];
	memset(mystr,0,5);
	strcpy(mystr,(const char*)cs);

	CWinThread *pWindThread = NULL;

	// Open the serial port.
	m_hComm = CreateFile ((LPCTSTR) mystr, // Pointer to the name of the port
		GENERIC_READ | GENERIC_WRITE,
		// Access (read/write) mode
		0,            // Share mode
		NULL,         // Pointer to the security attribute
		OPEN_EXISTING,// How to open the serial port
		0,            // Port attributes
		NULL);        // Handle to port with attribute
	// to copy

	// If it fails to open the port, return FALSE.
	if ( m_hComm == INVALID_HANDLE_VALUE ) 
	{
		// Could not open the port.
		ShowErrorMessage(GetLastError());
		return FALSE;
	}
	
	PortDCB.DCBlength = sizeof (DCB);     
	
	// Get the default port setting information.
	GetCommState (m_hComm, &PortDCB);
	// Change the DCB structure settings.
	PortDCB.BaudRate = 9600;              // Current baud 
	PortDCB.fBinary = TRUE;               // Binary mode; no EOF check 
	PortDCB.fParity = TRUE;               // Enable parity checking. 
	PortDCB.fOutxCtsFlow = FALSE;         // No CTS output flow control 
	PortDCB.fOutxDsrFlow = FALSE;         // No DSR output flow control 
	PortDCB.fDtrControl = DTR_CONTROL_ENABLE; 
	// DTR flow control type 
	PortDCB.fDsrSensitivity = FALSE;      // DSR sensitivity 
	PortDCB.fTXContinueOnXoff = TRUE;     // XOFF continues Tx 
	PortDCB.fOutX = FALSE;                // No XON/XOFF out flow control 
	PortDCB.fInX = FALSE;                 // No XON/XOFF in flow control 
	PortDCB.fErrorChar = FALSE;           // Disable error replacement. 
	PortDCB.fNull = TRUE;                // Disable null stripping. 
	PortDCB.fRtsControl = RTS_CONTROL_ENABLE; 
	// RTS flow control 
	PortDCB.fAbortOnError = FALSE;        // Do not abort reads/writes on 
	// error.
	PortDCB.ByteSize = 7;                 // Number of bits/bytes, 4-8 
	PortDCB.Parity = 2;            // 0-4=no,odd,even,mark,space 
	PortDCB.StopBits = ONESTOPBIT;        // 0,1,2 = 1, 1.5, 2 

	// Configure the port according to the specifications of the DCB 
	// structure.
	if (!SetCommState (m_hComm, &PortDCB))
	{
		// Could not create the read thread.
		ShowErrorMessage(GetLastError());
		return FALSE;
	}
	
	// Retrieve the time-out parameters for all read and write operations
	// on the port. 
	GetCommTimeouts (m_hComm, &CommTimeouts);
	
	// Change the COMMTIMEOUTS structure settings.
	CommTimeouts.ReadIntervalTimeout = MAXDWORD;  
	CommTimeouts.ReadTotalTimeoutMultiplier = 0;  
	CommTimeouts.ReadTotalTimeoutConstant = 0;    
	CommTimeouts.WriteTotalTimeoutMultiplier = 10;  
	CommTimeouts.WriteTotalTimeoutConstant = 1000;    
	
	// Set the time-out parameters for all read and write operations
	// on the port. 
	if (!SetCommTimeouts (m_hComm, &CommTimeouts))
	{
		// Could not create the read thread.
		ShowErrorMessage(GetLastError());
		return FALSE;
	}
	
	// Direct the port to perform extended functions SETDTR and SETRTS.
	// SETDTR: Sends the DTR (data-terminal-ready) signal.
	// SETRTS: Sends the RTS (request-to-send) signal. 
	EscapeCommFunction (m_hComm, SETDTR);
	EscapeCommFunction (m_hComm, SETRTS);

	m_bConnectStatus = TRUE;
/*
	AfxBeginThread(WestCtrlThread, this);
*/
	pWindThread = AfxBeginThread(WestCtrlThread, this);

	if(pWindThread)
		hProcess = pWindThread->m_hThread;

	return TRUE;
}