// DriverMotorTorqueControl.cpp: implementation of the CDriverMotorTorqueControl class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Deer.h"
#include "DriverMotorTorqueControl.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#define ENQ	0x05
#define EOT 0x04
#define ACK 0x06
#define NAK 0x15

#define T2	2000

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
UINT CDriverMotorTorqueControl::ThreadMotorTorqueControl(LPVOID p)
{
	CDriverMotorTorqueControl *dr = (CDriverMotorTorqueControl *)p;

	int id = 0;
	while(dr->IsConnected())
	{
		id = 0;
		dr->ProcessRead(id);
//		id++;
//		id = id % 6;

		dr->ProcessCmd();

		while(dr->pause)
		{
			dr->paused = true;
			Sleep(1);
		}

		dr->paused = false;
		Sleep(20);
	}

	AfxEndThread(0);
	return 0;
}

CDriverMotorTorqueControl::CDriverMotorTorqueControl()
{
	hProcess = NULL;

	m_hComm = NULL;

	pause = false;

	for(int i=0; i<6; i++)
	{
		tTorqueSetting[i] = 0;
		tTorque[i] = 0;
		iBaudRateTry[i] = 2;
		bBaudRateOK[i] = false;
	}
	iBaudRateNow = 5;

	iBaudRate[0] = 2400;
	iBaudRate[1] = 4800;
	iBaudRate[2] = 9600;
	iBaudRate[3] = 19200;
	iBaudRate[4] = 38400;
	iBaudRate[5] = 57600;

	bOpenOK = false;
}

CDriverMotorTorqueControl::~CDriverMotorTorqueControl()
{
	TRACE("~CDriverMotorTorqueControl\n");
}
/*
bool CDriverMotorTorqueControl::Close()
{
	if(m_hComm == INVALID_HANDLE_VALUE || m_hComm == NULL)
	{
		m_hComm = NULL;
		return true;
	}

	bool b = ::CloseHandle(m_hComm) == 0 ? false : true;
	if(b)
		m_hComm = NULL;

	WaitForSingleObject(hProcess, 10000);
	return b;
}
*/
/*
bool CDriverMotorTorqueControl::Close()
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
	}while(bSuccess && nThreadExitCode == STILL_ACTIVE && (end.QuadPart - start.QuadPart) / freq.QuadPart < 10);  //10秒表示等10s, 可依據需求修改
	}
	return b;
}
*/
bool CDriverMotorTorqueControl::Close()
{
	MSG				msg;
	LARGE_INTEGER	start, end, freq;
	DWORD			nThreadExitCode = 0;
	BOOL			bSuccess = FALSE;
	
	if(m_hComm == INVALID_HANDLE_VALUE || m_hComm == NULL)
	{
		m_hComm = NULL;
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
	}while(bSuccess && nThreadExitCode == STILL_ACTIVE && (end.QuadPart - start.QuadPart) / freq.QuadPart < 10);  //10秒表示等10s, 可依據需求修改
	}
	return b;
}
bool CDriverMotorTorqueControl::Open(int iPort, int iBaudRate, bool bReboot)
{	
	if(iPort < 0)
		return false;

	if(m_hComm != NULL)
		return true;

	DCB PortDCB;
	COMMTIMEOUTS CommTimeouts;
	CString cs;

	CWinThread *pWindThread = NULL;

	//Note the use of the string for the serial port name.  
	//The names "COM1".."COM9" work because there is a special hack in 
	//CreateFile that recognizes "C" "O" "M" followed by a single digit 
	//as being a special case.  If you want to open COM10, however, you 
	//have to specify it as \\.\COM10, which in a quoted string requires 
	//doubling the "\" character.

	if(iPort < 10)
		cs.Format("COM%d", iPort);
	else
		cs.Format("\\\\.\\COM%d", iPort);

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
		LPVOID lpMsgBuf;
		FormatMessage( 
			FORMAT_MESSAGE_ALLOCATE_BUFFER | 
			FORMAT_MESSAGE_FROM_SYSTEM | 
			FORMAT_MESSAGE_IGNORE_INSERTS,
			NULL,
			GetLastError(),
			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
			(LPTSTR) &lpMsgBuf,
			0,
			NULL 
			);
		// Process any inserts in lpMsgBuf.
		// ...
		// Display the string.
		CString t;
		t.Format("!!! Error: %s:%s", (LPCTSTR)lpMsgBuf, cs);

		// Free the buffer.
		LocalFree( lpMsgBuf );
		return false;
	}
	
	PortDCB.DCBlength = sizeof (DCB);     
	
	// Get the default port setting information.
	GetCommState (m_hComm, &PortDCB);
	
	// Change the DCB structure settings.
	PortDCB.BaudRate = iBaudRate;				// Current baud 
	PortDCB.ByteSize = 8;						// Number of bits/bytes, 4-8 
	PortDCB.Parity = 0;							// 0-4=no,odd,even,mark,space 
	PortDCB.StopBits = ONESTOPBIT;				// 0,1,2 = 1, 1.5, 2 
//	PortDCB.fParity = FALSE;               // Enable parity checking. 
	PortDCB.Parity = 0;							// 0-4=no,odd,even,mark,space 

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
	CommTimeouts.WriteTotalTimeoutMultiplier = 100;	// 10  
	CommTimeouts.WriteTotalTimeoutConstant = 1000;		// 1000    
	
	// Set the time-out parameters for all read and write operations
	// on the port. 
	if (!SetCommTimeouts(m_hComm, &CommTimeouts))
	{
		Close();
		return false;
	}
/*
	if(bReboot)
		hProcess = AfxBeginThread(ThreadMotorTorqueControl, this);
*/

	if(bReboot)
		pWindThread = AfxBeginThread(ThreadMotorTorqueControl, this);

	if(pWindThread)
		hProcess = pWindThread->m_hThread;

	bOpenOK = true;

	return true;
}

bool CDriverMotorTorqueControl::IsConnected()
{
	if(m_hComm == NULL)
		return false;

	return true;
}

void CDriverMotorTorqueControl::ProcessCmd()
{
	while(CmdQue.GetSize() > 0)
	{
		tagWriteCmd cmd = CmdQue.GetAt(0);
		if(WritePara(cmd))
			CmdQue.RemoveAt(0);

		Sleep(1);
	}
}

double CDriverMotorTorqueControl::GetTorqueSetting(int iSite)
{
	return tTorqueSetting[iSite];
}

bool CDriverMotorTorqueControl::SendCMD(unsigned char cmd)
{
	int iStart = ::GetTickCount();
	unsigned char cTemp[2] = {0};
	unsigned long ulNumWrite = 0;

	cTemp[0] = cmd;

	while(m_hComm && ulNumWrite < 1)
	{
		::WriteFile(m_hComm, cTemp, 1, &ulNumWrite, NULL);
		if(ulNumWrite == 1) return true;

		if((::GetTickCount() - iStart) > T2)
		{
			return false;
		}

	}
	return false;
}

bool CDriverMotorTorqueControl::WaitCMD(unsigned char cmd)
{
	int iStart = ::GetTickCount();
	unsigned char cTemp[1] = {0};
	unsigned long ulNumRead = 0;
	unsigned long iloop = 0;

	while(m_hComm)
	{
		Sleep(1);
		::ReadFile(m_hComm, cTemp, sizeof(cTemp), &ulNumRead, NULL);
		
		if(ulNumRead != 0)
		{
			if(cTemp[0] == cmd)
				return true;
			else if(cTemp[0] == NAK)
				break;
		}
			
		// Timeout 放長一點, 之前是 500ms, 有些舊的 Motor 有問題
		if((::GetTickCount() - iStart) > 6000)
		{
			break;
		}
	}

	PurgeComm();
	return false;
}

unsigned char CDriverMotorTorqueControl::CheckSum(unsigned char *pCmdWord, int iLength)
{
	unsigned char CHKSUM = { 0 };
	
	for(int i =0; i< iLength; i++)	
	{
		CHKSUM += pCmdWord[i];
	}

	return (0x100 - CHKSUM);
}

// 回復的資料格式
// Number of Data (1 Byte)
// Axis Number (1 Byte)
// Mode + Cmd (1 Byte)
// Data ... (Number of Data), 最後一個是 Error Code
// CheckSum (1 Byte)
bool CDriverMotorTorqueControl::_GetResponse(unsigned char *buffer)
{
	unsigned char b[30] = {0};
	int total = 0;
	int size = 0;
	unsigned long ulNumRead = 0;

	int iStart = ::GetTickCount();
	while(m_hComm && (total < size || size == 0))
	{
		Sleep(1);

		::ReadFile(m_hComm, b, sizeof(b), &ulNumRead, NULL);
		if(ulNumRead > 0)
		{
			for(int i=0; i<ulNumRead; i++)
			{
				buffer[total] = b[i];
				total++;
			}
			if(size == 0)
				size = buffer[0] + 4;
		}

		if(::GetTickCount() - iStart > 1200)
			return false;
	}

	if(size == 0)
		return false;

	if(buffer[size-1] == CheckSum(buffer, size-1))
		return true;
	
	return false;
}

void CDriverMotorTorqueControl::_WriteString(unsigned char *buffer, int size)
{
	unsigned long iLength = 0;

	int i=0;
	while(WriteFile(m_hComm, buffer, size, &iLength, NULL) == 0)
	{
		if(iLength == size)
			break;

		i++;
		if(i>5) break;
		Sleep(100);
	}
}

bool CDriverMotorTorqueControl::_GetTorque(int id)
{
	int size = sizeof(tagCmdTorque);
	unsigned char cTemp[128] = {'9'}; // 宣告夠大
	tagCmdTorque *cmd = (tagCmdTorque *)cTemp;

	// 我們要先檢查目前的 baudrate 是不是正確的
	if(iBaudRateNow != iBaudRateTry[id])
		SetBaudRate(iBaudRateTry[id]);

	SendCMD(ENQ);
	if(!WaitCMD(EOT))
		return false;

	cmd->DataNo = size - 4;
	cmd->AxisNo = id;
	cmd->ModeCmd = 0x52;
	cmd->CheckSum = CheckSum(cTemp, size - 1);

	_WriteString(cTemp, size);

	if(!WaitCMD(ACK)) 
		return false;

	if(!WaitCMD(ENQ))
		return false;

	if(!SendCMD(EOT)) 
		return false;

	//Read Data
	memset(cTemp, 0, sizeof(cTemp));
	if(!_GetResponse(cTemp)) 
		return false;
	if(!SendCMD(ACK)) 
		return false;

	tagResTorque *res = (tagResTorque *)cTemp;

	// 測試後發現有時候會送出錯誤的 protocol
	if(res->DataNo != 3)
		return false;

	if(res->Err != 0)
		return false;

	// t = 2000 達到 TorqueLimit;
	// 額定扭力:100%  額定扭力 = 2000換算，和 5e 參數無關
	// Data[0] = 0 ~ 255 不帶正負, Data[1] = -127 ~ 127 帶正負號
	int t = (res->Data[1]<<8) + ((unsigned char)res->Data[0]);
	tTorque[res->AxisNo] = 100.0 * t / 2000.;

	ParaRead[id][enParamTorque] = tTorque[res->AxisNo];

	return true;
}

double CDriverMotorTorqueControl::GetTorque(int iSite)
{
	return tTorque[iSite];
}

void CDriverMotorTorqueControl::ProcessRead(int id)
{
	if(tTorqueSetting[id] == 0)
	{
		int t = ReadPara(id, 0x5E);
		if(t == _Device_Error)
		{
			PurgeComm();
			if(!bBaudRateOK[id])
			{
				SwitchToNextBaudRate(id);
				return;
			}
		}
		else
		{
			if(!bBaudRateOK[id])
				bBaudRateOK[id] = true;
			tTorqueSetting[id] = t;
		}
	}

	if(!_GetTorque(id))
		PurgeComm();
}

void CDriverMotorTorqueControl::PurgeComm()
{
	::PurgeComm(m_hComm, PURGE_TXCLEAR | PURGE_RXCLEAR | PURGE_TXABORT | PURGE_RXABORT);
}

double CDriverMotorTorqueControl::GetForce(int site)
{
	// TestSite Initial Load 為負值 (向上)
	double force = (tTorque[site] - InitialLoad[site]) * ForceTorqueRatio;
	return force;
}

long CDriverMotorTorqueControl::GetBaudRate(int id)
{
	return iBaudRate[iBaudRateTry[id]];
}

long CDriverMotorTorqueControl::SwitchToNextBaudRate(int id)
{
	iBaudRateTry[id]++;
	if(iBaudRateTry[id] > 5)
		iBaudRateTry[id] = 0;
/*
	iBaudRateNow = iBaudRateTry[id];

	DCB PortDCB;
	CString cs;

	SetBaudRate(iBaudRateNow);
*/
	return iBaudRate[iBaudRateTry[id]];
}

long CDriverMotorTorqueControl::ReadPara(int id, int para)
{
	int size = sizeof(tagReadParameter);
	unsigned char cTemp[128]; // 宣告夠大
	tagReadParameter *cmd = (tagReadParameter *)cTemp;

	// 我們要先檢查目前的 baudrate 是不是正確的
	if(iBaudRateNow != iBaudRateTry[id])
		SetBaudRate(iBaudRateTry[id]);

	SendCMD(ENQ);

	if(!WaitCMD(EOT))
		return _Device_Error;

	cmd->DataNo = 1;
	cmd->AxisNo = id;
	cmd->ModeCmd = 0x08;
	cmd->ParamNo = para;
	cmd->CheckSum = CheckSum(cTemp, size - 1);

	_WriteString(cTemp, size);

	if(!WaitCMD(ACK)) 
		return _Device_Error;

	if(!WaitCMD(ENQ))
		return _Device_Error;
	if(!SendCMD(EOT)) 
		return _Device_Error;

	//Read Data
	memset(cTemp, 0, sizeof(cTemp));
	if(!_GetResponse(cTemp)) 
		return _Device_Error;
	if(!SendCMD(ACK)) 
		return _Device_Error;

	tagReadRes *res = (tagReadRes *)cTemp;

	return ((res->vHigh<<8) + ((unsigned char)res->vLow));
}

void CDriverMotorTorqueControl::AddWriteCmd(int id, int paraNo, long value)
{
	tagWriteCmd cmd;
	cmd.AxisNo = id;
	cmd.ParamNo = paraNo;
	cmd.value = value;
	CmdQue.Add(cmd);
}

bool CDriverMotorTorqueControl::WritePara(tagWriteCmd cmdWrite)
{
	int size = sizeof(tagWriteParameter);
	unsigned char cTemp[128]; // 宣告夠大
	tagWriteParameter *cmd = (tagWriteParameter *)cTemp;

	// 我們要先檢查目前的 baudrate 是不是正確的
	if(iBaudRateNow != iBaudRateTry[cmdWrite.AxisNo])
		SetBaudRate(iBaudRateTry[cmdWrite.AxisNo]);

	SendCMD(ENQ);
	if(!WaitCMD(EOT))
		return false;

	cmd->DataNo = 3;
	cmd->AxisNo = cmdWrite.AxisNo;
	cmd->ModeCmd = 0x18;
	cmd->ParamNo = cmdWrite.ParamNo;
	cmd->vLow = cmdWrite.value & 0xff;
	cmd->vHigh = (cmdWrite.value >> 8) & 0xff;
	cmd->CheckSum = CheckSum(cTemp, size - 1);

	_WriteString(cTemp, size);

	if(!WaitCMD(ACK)) 
		return false;

	if(!WaitCMD(ENQ))
		return false;
	if(!SendCMD(EOT)) 
		return false;

	//Read Data
	memset(cTemp, 0, sizeof(cTemp));
	if(!_GetResponse(cTemp)) 
		return false;
	if(!SendCMD(ACK)) 
		return false;

	tagWriteRes *res = (tagWriteRes *)cTemp;

	if(res->Err == 0)
	{
		if(cmdWrite.ParamNo == enParamTorque)
			tTorqueSetting[cmdWrite.AxisNo] = cmdWrite.value;
		return true;
	}

	return false;
}

bool CDriverMotorTorqueControl::IsWorking(int id)
{
	return bBaudRateOK[id];
}

// 存入每個馬達在靜止時的負載, 這時候 contact force = 0
// 將來的負載必須加上這個才是真正的 contact force
void CDriverMotorTorqueControl::SetInitialLoad(int id)
{
	InitialLoad[id] = GetTorque(id);
}

// x = Force / Torque
void CDriverMotorTorqueControl::SetForceTorqueRatio(double ratio)
{
	ForceTorqueRatio = ratio;
}

void CDriverMotorTorqueControl::SetBaudRate(long BaudRate)
{
	DCB PortDCB;
	CString cs;

	iBaudRateNow = BaudRate;

	// Get the default port setting information.
	GetCommState (m_hComm, &PortDCB);
	
	// Change the DCB structure settings.
	PortDCB.BaudRate = iBaudRate[BaudRate];				// Current baud 
	PortDCB.ByteSize = 8;						// Number of bits/bytes, 4-8 
	PortDCB.Parity = 0;							// 0-4=no,odd,even,mark,space 
	PortDCB.StopBits = ONESTOPBIT;				// 0,1,2 = 1, 1.5, 2 
//	PortDCB.fParity = FALSE;               // Enable parity checking. 
	PortDCB.Parity = 0;							// 0-4=no,odd,even,mark,space 
	SetCommState(m_hComm, &PortDCB);

	PurgeComm();
}

bool CDriverMotorTorqueControl::MotorParamWrite(int MotorID, int ParamNo, long data)
{
	int size = sizeof(tagWriteParameter);
	unsigned char cTemp[128]; // 宣告夠大
	tagWriteParameter *cmd = (tagWriteParameter *)cTemp;

	// 我們要先檢查目前的 baudrate 是不是正確的
	if(iBaudRateNow != iBaudRateTry[MotorID])
		SetBaudRate(iBaudRateTry[MotorID]);

	SendCMD(ENQ);
	if(!WaitCMD(EOT))
		return false;

	cmd->DataNo = 3;
	cmd->AxisNo = MotorID;
	cmd->ModeCmd = 0x18;
	cmd->ParamNo = ParamNo;
	cmd->vLow = data & 0xff;
	cmd->vHigh = (data >> 8) & 0xff;
	cmd->CheckSum = CheckSum(cTemp, size - 1);

	_WriteString(cTemp, size);

	if(!WaitCMD(ACK)) 
		return false;

	if(!WaitCMD(ENQ))
		return false;
	if(!SendCMD(EOT)) 
		return false;

	//Read Data
	memset(cTemp, 0, sizeof(cTemp));
	if(!_GetResponse(cTemp)) 
		return false;
	if(!SendCMD(ACK)) 
		return false;

	if(((tagWriteRes *)cTemp)->Err == 0)
		return true;

	return false;
}

bool CDriverMotorTorqueControl::MotorParamRead(int MotorID, int ParamNo, long &data)
{
	int v = ReadPara(MotorID, ParamNo);
	if(v == _Device_Error)
		return false;

	data = v;
	return true;
}

void CDriverMotorTorqueControl::SaveMotorParam()
{
	ThreadPause(true);
	long data[6][0x80] = {0};
	for(int motor=0; motor<6; motor++)
	{
		for(int page=0; page<8; page++)
		{
			long *p = (long *)(&data[motor][0]);
			if(!_PageRead(motor, page, p))
			{
				ThreadPause(false);
				return;
			}
		}
	}
	ThreadPause(false);

	CString csFile = ".\\System\\Motor.param";

	::DeleteFile(csFile);

	CString cs;
	CFile file;
	if(file.Open(csFile, CFile::modeCreate | CFile::modeWrite | CFile::shareDenyNone
		| CFile::modeNoTruncate, NULL) != 0)
	{
		for(motor=0; motor<6; motor++)
		{
			if(!bBaudRateOK[motor])
				continue;
			for(int i=0; i<0x7F; i++)
			{
				cs.Format("%d::%d::%d\r\n", motor, i, data[motor][i]); 
				file.Write(cs.GetBuffer(0), cs.GetLength());			
			}
		}
		file.Close();
	}
}

void CDriverMotorTorqueControl::DownloadMotorParam()
{
	long data[6][0x80] = {-1};

	CString csFile = ".\\System\\Motor.param";

	CString cs;
	CFile file;
	int first, second;
	if(file.Open(csFile, CFile::modeRead | CFile::shareDenyNone) != 0)
	{
		file.SeekToBegin();
		CArchive ar(&file, CArchive::load);
		while(ar.ReadString(cs))
		{
			first = cs.Find("::", 0);
			if(first == -1)
				continue;
			second = cs.Find("::", 2);
			if(second == -1)
				continue;

			int motor = atoi(cs.Left(first).GetBuffer(0));
			if(motor < 0 || motor >= 6)
				continue;
			if(!bBaudRateOK[motor])
				continue;

			int no = atoi(cs.Mid(first+2, second-first).GetBuffer(0));
			if(no < 0 || no >= 0x7F)
				continue;

			data[motor][no] = atoi(cs.Right(cs.GetLength() - second - 2));
		}

		ar.Close();
		file.Close();
	}
}

bool CDriverMotorTorqueControl::ThreadPause(bool stop)
{
	if(stop)
	{
		pause = true;
		while(!paused)
			Sleep(1);
	}
	else
	{
		pause = false;
		while(paused)
			Sleep(1);
	}

	return true;
}

bool CDriverMotorTorqueControl::_PageRead(int id, int page, long *data)
{
	int size = sizeof(tagReadParameter);
	unsigned char cTemp[150]; // 宣告夠大
	tagReadParameter *cmd = (tagReadParameter *)cTemp;

	// 我們要先檢查目前的 baudrate 是不是正確的
	if(iBaudRateNow != iBaudRateTry[id])
		SetBaudRate(iBaudRateTry[id]);

	SendCMD(ENQ);

	if(!WaitCMD(EOT))
		return false;

	cmd->DataNo = 1;
	cmd->AxisNo = id;
	cmd->ModeCmd = 0x1b;
	cmd->ParamNo = page;
	cmd->CheckSum = CheckSum(cTemp, size - 1);

	_WriteString(cTemp, size);

	if(!WaitCMD(ACK)) 
		return false;

	if(!WaitCMD(ENQ))
		return false;
	if(!SendCMD(EOT)) 
		return false;

	//Read Data
	memset(cTemp, 0, sizeof(cTemp));
	if(!_GetResponse(cTemp)) 
		return false;
	if(!SendCMD(ACK)) 
		return false;

	tagPageDataRead *res = (tagPageDataRead *)cTemp;

	for(int i=0; i<16; i++)
	{
		int no = page*16+i;
		*(data + no) = (res->Param[i].vHigh<<8) + ((unsigned char)res->Param[i].vLow);
	}

	return true;
}
bool CDriverMotorTorqueControl::GetOpenOK()
{
	return bOpenOK;
}