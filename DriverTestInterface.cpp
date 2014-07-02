// DriverTestInterface.cpp: implementation of the CDriverTestInterface class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "deer.h"
#include "DriverTestInterface.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
UINT CDriverTestInterface::ThreadTestInterfaceExcute(LPVOID p)
{
	CDriverTestInterface *dr = (CDriverTestInterface *)p;

	while(1)
	{
		// Write
		dr->ProcessCommand();
	
		// Make sure program close. Thread will be close
		if( !m.Info.bRunning )
			break;	
	
		Sleep(1);
	}

	AfxEndThread(0);
	return 0;	
}
UINT CDriverTestInterface::ThreadTestInterfaceWrite(LPVOID p)
{
	CDriverTestInterface *dr = (CDriverTestInterface *)p;

	while(1)
	{
		// Write
		dr->Write();
	
		// Make sure program close. Thread will be close
		if( !m.Info.bRunning )
			break;	
	
		Sleep(1);
	}

	AfxEndThread(0);
	return 0;	
}
UINT CDriverTestInterface::ThreadTestInterfaceRead(LPVOID p)
{
	CDriverTestInterface *dr = (CDriverTestInterface *)p;

	while(1)
	{
		// Read
		dr->Read();

		// 1.0Ap
		// Remove this one and re-build with "ThreadTestInterfaceExcute"
		/*
		// Excute
		dr->ProcessCommand();
		*/
	
		// Make sure program close. Thread will be close
		if( !m.Info.bRunning )
			break;	
	
		Sleep(1);
	}

	AfxEndThread(0);
	return 0;
}
// 1.0Ao
UINT CDriverTestInterface::ThreadTestInterfaceReadTCP(LPVOID p)
{
	CDriverTestInterface *dr = (CDriverTestInterface *)p;

	while(1)
	{
		dr->ReadTCP();

		// Make sure program close. Thread will be close
		if( !m.Info.bRunning )
			break;	
		
		Sleep(1);
	}

	AfxEndThread(0);
	return 0;
}
UINT CDriverTestInterface::ThreadTestInterfaceWriteTCP(LPVOID p)
{
	CDriverTestInterface *dr = (CDriverTestInterface *)p;

	while(1)
	{
		dr->WriteTCP();

		// Make sure program close. Thread will be close
		if( !m.Info.bRunning )
			break;
		
		Sleep(1);
	}

	AfxEndThread(0);
	return 0;
}

bool CDriverTestInterface::OpenTCP(int iPort)
{
	// Server
	m_TesterInterfaceTcp.Create(iPort, SOCK_STREAM);
	m_TesterInterfaceTcp.Listen();

	return true;
}
void CDriverTestInterface::GetEthernet(CString &csEthernetIP, CString &csEthernetPort)
{
	CString csIP = _T("");
	CString csPort = _T("");
	unsigned int iPort = 0;

	m_TesterInterfaceTcp.GetServerSocketName(csIP, iPort);
	csPort.Format("%d", iPort);

	//
	csEthernetIP	= csIP;
	csEthernetPort	= csPort;
}
void CDriverTestInterface::CloseTCP()
{
	m_TesterInterfaceTcp.CloseTCP();
}

void CDriverTestInterface::CloseExcute()
{
	MSG				msg;
	LARGE_INTEGER	start, end, freq;
	DWORD			nThreadExitCode = 0;
	BOOL			bSuccess = FALSE;

	::QueryPerformanceFrequency(&freq);
	::QueryPerformanceCounter(&start);
	if(hProcessRead != NULL)
	{
	do
	{
		bSuccess = GetExitCodeThread(hProcessExcute, &nThreadExitCode);
		::QueryPerformanceCounter(&end);

		if(::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			::TranslateMessage(&msg);
			::DispatchMessage(&msg);
		}
	}while(bSuccess && nThreadExitCode == STILL_ACTIVE && (end.QuadPart - start.QuadPart) / freq.QuadPart < 10);  //10秒表示等10s, 可依據需求修改
	}
}

void CDriverTestInterface::CloseReadTCP()
{
	MSG				msg;
	LARGE_INTEGER	start, end, freq;
	DWORD			nThreadExitCode = 0;
	BOOL			bSuccess = FALSE;

	::QueryPerformanceFrequency(&freq);
	::QueryPerformanceCounter(&start);
	if(hProcessRead != NULL)
	{
	do
	{
		bSuccess = GetExitCodeThread(hProcessReadTCP, &nThreadExitCode);
		::QueryPerformanceCounter(&end);

		if(::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			::TranslateMessage(&msg);
			::DispatchMessage(&msg);
		}
	}while(bSuccess && nThreadExitCode == STILL_ACTIVE && (end.QuadPart - start.QuadPart) / freq.QuadPart < 10);  //10秒表示等10s, 可依據需求修改
	}
}
void CDriverTestInterface::CloseWriteTCP()
{
	MSG				msg;
	LARGE_INTEGER	start, end, freq;
	DWORD			nThreadExitCode = 0;
	BOOL			bSuccess = FALSE;

	::QueryPerformanceFrequency(&freq);
	::QueryPerformanceCounter(&start);
	if(hProcessWrite != NULL)
	{
	do
	{
		bSuccess = GetExitCodeThread(hProcessWriteTCP, &nThreadExitCode);
		::QueryPerformanceCounter(&end);

		if(::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			::TranslateMessage(&msg);
			::DispatchMessage(&msg);
		}
	}while(bSuccess && nThreadExitCode == STILL_ACTIVE && (end.QuadPart - start.QuadPart) / freq.QuadPart < 10);  //10秒表示等10s, 可依據需求修改
	}
}
void CDriverTestInterface::WriteTCP()
{
	bool result = true;
	if( m_SendTCPCmd.GetSize() > 0 )
	{
		CString cs = m_SendTCPCmd.GetAt(0);
		m_TesterInterfaceTcp.SendToClient( cs );

		//
		RemoteRawMsg( cs );
	
		if(result)
			m_SendTCPCmd.RemoveAt(0);	
	}
}
void CDriverTestInterface::ReadTCP()
{
	CString csRecvBuffer = _T("");
	m_TesterInterfaceTcp.GetTotalBufferData( csRecvBuffer );
	if( csRecvBuffer != "" )
	{
		CString cs = csRecvBuffer;
		cs.TrimRight(); cs.TrimLeft();
		csTCPBuffer += cs;

		// Log to dialog
		RemoteRawMsg( cs );
	}

	int iStart = 0, iEnd = 0;
	CString csTelegram = _T("");
	iStart = csTCPBuffer.Find( _STX );	// "<<"
	while(iStart > -1)
	{
		iEnd = csTCPBuffer.Find( _ETX, iStart);	// ">>"
		if(iEnd > iStart)
		{
			CString csTail = _T("");
			csTail.Format("%s", _ETX );
			csTelegram = csTCPBuffer.Mid(iStart, iEnd-iStart+csTail.GetLength());
			// 不管 iStart 是多少，都從第一個開始刪掉

			csTCPBuffer.Delete(0, iEnd+csTail.GetLength());
			// 刪除命令, 避開雜訊

			Log( csTelegram );
			// 記錄讀取成功的字串
			
			tagTestProtocol result = GetProtocol(csTelegram);
			AddReadCmd(result);
			// 新增 Command 到 Queue

			iStart = csTCPBuffer.Find( _STX );
			// 繼續下一個 message
		}
		else
			break;
	}
}
// 1.0Ar
// Remove this and re-build new one
/*
void CDriverTestInterface::ReadTCP()
{
	CString csRecvBuffer = _T("");
	m_TesterInterfaceTcp.GetTotalBufferData( csRecvBuffer );
	if( csRecvBuffer != "" )
	{
		CString cs = csRecvBuffer;
		cs.TrimRight(); cs.TrimLeft();
		csBuffer += cs;

		// Log to dialog
		RemoteRawMsg( cs );
	}

	int iStart = 0, iEnd = 0;
	CString csTelegram = _T("");
	iStart = csBuffer.Find( _STX );	// "<<"
	while(iStart > -1)
	{
		iEnd = csBuffer.Find( _ETX, iStart);	// ">>"
		if(iEnd > iStart)
		{
			CString csTail = _T("");
			csTail.Format("%s", _ETX );
			csTelegram = csBuffer.Mid(iStart, iEnd-iStart+csTail.GetLength());
			// 不管 iStart 是多少，都從第一個開始刪掉

			csBuffer.Delete(0, iEnd+csTail.GetLength());
			// 刪除命令, 避開雜訊

			Log( csTelegram );
			// 記錄讀取成功的字串
			
			tagTestProtocol result = GetProtocol(csTelegram.GetBuffer(0));
			AddReadCmd(result);
			// 新增 Command 到 Queue

			iStart = csBuffer.Find( _STX );
			// 繼續下一個 message
		}
		else
			break;
	}
}
*/
//
bool CDriverTestInterface::GetReadyReturnCommand(CString &csNoReturnReason )
{
	bool bSystemReady = false;
	csNoReturnReason = _T("");

	// 確認是有 IC 在 Socket
	if( GetCoordnationGoStatusReady() )
		bSystemReady = true;
	else
		bSystemReady = false;	// No IC

	return bSystemReady;
}
bool CDriverTestInterface::GetReadyCommand(CString &csNoReadyReason )
{
	bool bSystemReady = false;
	csNoReadyReason = _T("");
	
	// 確認是否門被開啟
	if( !GetDoorStatus() )
	{
		tagErrorMsg e = f.GetErrorMsg(enCodeFrontDoor);
		csNoReadyReason.Format("NAK;%s", e.Eng);
		return bSystemReady;
	}
	
	// 確認緊急停止鈕
	if( !GetEStopStatus() )
	{
		tagErrorMsg e = f.GetErrorMsg(enCodeEStop);
		csNoReadyReason.Format("NAK;%s", e.Eng);		
		return bSystemReady;
	}

	// 確認系統準備好
	if( !GetSystemReady() )
	{
		csNoReadyReason.Format("NAK;%s", "System No Ready");
		return bSystemReady;
	}

	// 確認是否有建立工單
	if( !GetLotCreate() )
	{		
		csNoReadyReason.Format("NAK;LoadSetup Is Required");
		return bSystemReady;
	}

	// 確認已經設定 Coordnation
	if( !GetCoordnationReady() )
	{
		csNoReadyReason.Format("NAK;Tray No Match");
		return bSystemReady;
	}

	// 確認是否已經有 IC 在裡面
	if( GetCoordnationGoStatusReady() )
	{
		csNoReadyReason.Format("NAK;Mission already on the go");
		return bSystemReady;
	}

	bSystemReady = true;
	return bSystemReady;
}
void CDriverTestInterface::GetSendCommand(int iCode, CString &csSendCmd, CString csExtMsg  )
{
	if( iCode == enReturnErrMessage )
	{
		// <<*%%ERRORMESSAGE%%%s>>", e.Eng
		CString csErrorMsg = _T("");
		csErrorMsg.Format("%sERRORMESSAGE%s%s%s", _STX, _MTX, csExtMsg, _ETX );
		csSendCmd = csErrorMsg;
	}
	else if( iCode == enReturnSetCoordnationDone )
	{
		// <<SetCoordinatesGo: DONE>>
		CString csSetCoordnationDone = _T("");
		csSetCoordnationDone.Format("%sSETCOORDINATESGO%s%s%s", _STX, _MTX, _STDONE, _ETX );
		csSendCmd = csSetCoordnationDone;
	}
	else if( iCode == enReturnSetCoordnationReturnDone )
	{
		// <<SetCoordinatesReturn: DONE>>
		CString csSetCoordnationDone = _T("");
		csSetCoordnationDone.Format("%sSETCOORDINATESRETURN%s%s%s", _STX, _MTX, _STDONE, _ETX );
		csSendCmd = csSetCoordnationDone;	
	}
	else if( iCode == enReturnSetStateErrorCtrl )
	{
		// <<SetState: DONE>>
		CString csSetStateErrorDone = _T("");
		csSetStateErrorDone.Format("%sSETSTATE%s%s%s", _STX, _MTX, _STDONE, _ETX );
		csSendCmd = csSetStateErrorDone;		
	}
	else if( iCode == enReturnSetStateInitial )
	{
		// <<SetState: DONE>>
		CString csSetStateInitialDone = _T("");
		csSetStateInitialDone.Format("%sSETSTATE%s%s%s", _STX, _MTX, _STDONE, _ETX );
		csSendCmd = csSetStateInitialDone;	
	}
	else if( iCode == enReturnSetStateRetry )
	{
		// <<SetState: DONE>>
		CString csSetStateRetryDone = _T("");
		csSetStateRetryDone.Format("%sSETSTATE%s%s%s", _STX, _MTX, _STDONE, _ETX );
		csSendCmd = csSetStateRetryDone;		
	}
	else if( iCode == enReturnSetStateSkip )
	{
		// <<SetState: DONE>>
		CString csSetStateSkipDone = _T("");
		csSetStateSkipDone.Format("%sSETSTATE%s%s%s", _STX, _MTX, _STDONE, _ETX );
		csSendCmd = csSetStateSkipDone;	
	}
	else if( iCode == enReturnSetError )
	{
		// <<SetState: ERROR>>
		CString csSetStateError = _T("");
		csSetStateError.Format("%sSETSTATE%s%s%s", _STX, _MTX, _STERROR, _ETX );
		csSendCmd = csSetStateError;	
	}
	else if( iCode == enReturnSetStateReset )
	{
		// <<SetState: DONE>>
		CString csSetStateResetDone = _T("");
		csSetStateResetDone.Format("%sSETSTATE%s%s%s", _STX, _MTX, _STDONE, _ETX );
		csSendCmd = csSetStateResetDone;	
	}
	else if( iCode == enReturnSetStateOneCycle )
	{
		// <<SetState: DONE>>
		CString csSetStateOneCycleDone = _T("");
		csSetStateOneCycleDone.Format("%sSETSTATE%s%s%s", _STX, _MTX, _STDONE, _ETX );
		csSendCmd = csSetStateOneCycleDone;
	}
	else if( iCode == enReturnSetCoordnationGoError )
	{
		// <<SetState: ERROR>>
	}
	else if( iCode == enReturnSetCoordnationReturnError )
	{
		// <<SetState: ERROR>>
	}
}
void CDriverTestInterface::GetReturnCommand(tagTestProtocol msg, CString &csReturnCmd, 
											int &iReturnCode, bool &bNeedReturn)
{
	bool bCommandNeedReturn = true;


#if 1

	
#else
	if(msg.cmd == "GETHELP?")
	{
		// <<GetHelp?:>>
		// <<GetHelp?: RemoteCommand1, RemoteCommand2,..... >>
		CString csHelp = _T("");
		GetHelpFile( csHelp );
		csReturnCmd.Format("%sGETHELP?%s%s%s", _STX, _MTX, csHelp, _ETX );
		iReturnCode = enReturnGetHelp;
	}
	else if( msg.cmd == "GETVERSION?")
	{
		// <<GetVersion?:>>
		// <<GetVersion?: CHROMA,3111,REV1,V0.1AJ>>
		CString csVersion = _T("");
		csVersion = GetProgramVersion();
		csReturnCmd.Format("%sGETVERSION?%s %s%s", _STX, _MTX, csVersion, _ETX );
		iReturnCode = enReturnVersion;	
	}
	else if( msg.cmd == "GETLOT?")
	{
		// <<GetLot?:>>
		// <<GETLOT?: ProgramID>>
		CString csGetLot = _T("");
		CString csGetLotParameter = msg.parameter;
		csGetLotParameter.TrimLeft(); csGetLotParameter.TrimRight();
		int iLotFiled = atoi(csGetLotParameter);
		CString csLotInfo = _T("");
		if( iLotFiled == enLotFieldLotNo )
			GetLotInfo(enLotFieldLotNo, csLotInfo);
		else if( iLotFiled == enLotFieldMachineNo )
			GetLotInfo(enLotFieldMachineNo, csLotInfo);
		else if( iLotFiled == enLotFieldOperatorID )
			GetLotInfo(enLotFieldOperatorID, csLotInfo);
		else if( iLotFiled == enLotFieldDeviceID )
			GetLotInfo(enLotFieldDeviceID, csLotInfo);
		else if( iLotFiled == enLotFieldProgramID )
			GetLotInfo(enLotFieldProgramID, csLotInfo);
		else
		{
			csLotInfo.Format("%s", _STERROR );
		}
		csGetLot.Format("%sGETLOT?%s%s%s", _STX, _MTX, csLotInfo, _ETX);

		csReturnCmd = csGetLot;
		iReturnCode = enReturnGetLotNo;
	}
	else if(msg.cmd == "SETLOT")
	{
		// <<SetLot:0,LotNo>>
		// <<SETLOT: DONE>>
		CString csSetLot = _T("");
		CString csSetLotParameter = _T("");
		csSetLotParameter = msg.parameter;
		csSetLotParameter.TrimLeft(); csSetLotParameter.TrimRight();
		tagRemoteLotInfo reLotInfo;
		bool LotOK = VerifyLotInfo(csSetLotParameter, reLotInfo );
		if( LotOK )
		{
			if( reLotInfo.iFiled <= enLotFieldProgramID )
			{
				SetLotInfo( reLotInfo.iFiled, reLotInfo.csLotInfo );
				csSetLot.Format("%sSETLOT%s%s%s", _STX, _MTX, _STDONE, _ETX);
			}
			else
				csSetLot.Format("%sSETLOT%s%s%s", _STX, _MTX, _STERROR, _ETX);
		}
		else
			csSetLot.Format("%sSETLOT%s%s%s", _STX, _MTX, _STERROR, _ETX);

		csReturnCmd = csSetLot;
		iReturnCode = enReturnSetLotNo;
	}
	else if(msg.cmd == "SETRUNMODE")
	{
		// <<SetRunMode: 1>>
		// <<SETRUNMODE: DONE>>
		CString csSetRunMode = _T("");
		CString csSetRunModeParameter = msg.parameter;
		csSetRunModeParameter.TrimLeft(); csSetRunModeParameter.TrimRight();
		int iRunMode = atoi(csSetRunModeParameter);
		if( iRunMode == 0 )
		{
			SetRunMode( iRunMode ); // OnLine
			csSetRunMode.Format("%sSETRUNMODE%s%s%s", _STX, _MTX, _STDONE, _ETX);
		}
		else if( iRunMode == 1 )
		{
			SetRunMode( iRunMode ); // Offline
			csSetRunMode.Format("%sSETRUNMODE%s%s%s", _STX, _MTX, _STDONE, _ETX);
		}
		else if( iRunMode == 2 )
		{
			SetRunMode( iRunMode ); // Demo
			csSetRunMode.Format("%sSETRUNMODE%s%s%s", _STX, _MTX, _STDONE, _ETX);
		}
		else
			csSetRunMode.Format("%sSETRUNMODE%s%s%s", _STX, _MTX, _STERROR, _ETX);

		csReturnCmd = csSetRunMode;
		iReturnCode = enReturnSetRunMode;		
	}
	else if(msg.cmd == "GETRUNMODE?")
	{
		// <<GetRunMode?:>>
		// <<GETRUNMODE?: 1>>
		CString csGetRunMode = _T("");
		CString csRunMode = _T("");
		int iRunMode = 0;
		csRunMode = GetRunMode(iRunMode);
		csGetRunMode.Format("%sGETRUNMODE?%s%s%s", _STX, _MTX, csRunMode, _ETX);

		csReturnCmd = csGetRunMode;
		iReturnCode = enReturnGetRunMode;
	}
	else if(msg.cmd == "GETSTATE?")
	{
		// <<GetState?:>>
		// <<GetState?: UNINITIAL>>
        // <<GetState?: READY>>
        // <<GetState?: STOP>>
		CString csGetStatus = _T("");
		csGetStatus.Format("%sGETSTATE?%s%s%s", _STX, _MTX, GetSystemStatus(), _ETX);

		csReturnCmd = csGetStatus;
		iReturnCode = enReturnGetState;
	}
	else if(msg.cmd == "SETSTATE")
	{
		CString csSetState = _T("");
		CString csparameter = _T("");
		csparameter = msg.parameter;
		csparameter.TrimLeft(); csparameter.TrimRight();
		bool bSetState = true;
		if( csparameter == "INITIALIZE")
			bSetState = SetState( enSetStateInitial );
		else if( csparameter == "START")
		{
			bSetState = SetState( enSetStateStart );
			if( m_bReturnError )
			{
				m_bReturnError = false;
				RequestCoordnationMissionReturn(); // return
			}
		}
		else if( csparameter == "STOP")
			bSetState = SetState( enSetStateStop );
		else if( csparameter == "RETRY" )
			bSetState = SetState( enSetStateRetry );
		else if( csparameter == "RESET" )
			bSetState = SetState( enSetStateReset );
		else if( csparameter == "SKIP" )
			bSetState = SetState( enSetStateSkip );
		else if( csparameter == "ONECYCLE" )
			bSetState = SetState( enSetStateOneCycle );
		else
		{
		}	

		if(!bSetState)
		{
			// ststus won't allow access
			csSetState.Format("%sSETSTATE%s%s%s", _STX, _MTX, _STERROR, _ETX);
			csReturnCmd = csSetState;
			iReturnCode = enReturnSetState;
		}
	}
	else if(msg.cmd == "SETPRESSURE")
	{
		// <<SetPressure: 8>>
		// <<SetPressure: DONE>>
        // <<SetPressure: ERROR>>		
		double dMaxTorqueMax = 0.0;
		double dMinTorqueMin = 0.0;
		GetTorqueMaxMin(dMaxTorqueMax, dMinTorqueMin);
		double dAirPressure = atof(msg.parameter);

		if( dAirPressure > dMaxTorqueMax || dAirPressure < dMinTorqueMin )
		{
			csReturnCmd.Format("%sSETPRESSURE?%s%s%s", _STX, _MTX, _STERROR, _ETX);	
		}
		else
		{
			SetAirPressure( dAirPressure );
			csReturnCmd.Format("%sSETPRESSURE?%s%s%s", _STX, _MTX, _STDONE, _ETX);	
		}
	}
	else if(msg.cmd == "GETPRESSURE?" )
	{
		// <<GetPressure?:>>
		// <<GetPressure?: 8>>
        // <<GetPressure?: ERROR>>	
		if( GetAirPressureEnable() )
		{
			CString csGetAirPressure = _T("");
			double dGetAirPressure = 0.0;
			csGetAirPressure = GetAirPressure(dGetAirPressure);
			csReturnCmd.Format("%sGETPRESSURE?%s%s%s", _STX, _MTX, csGetAirPressure, _ETX);		
		}
		else
		{
			csReturnCmd.Format("%sGETPRESSURE?%s%s%s", _STX, _MTX, _STERROR, _ETX);		
		}

		iReturnCode = enReturnGetAirPressure;
	}
	else if(msg.cmd == "GETSITETEMP?")
	{
		// <<GetSiteTemp?:>>
		// <<GetSiteTemp?: 34.0>>
		CString csGetSiteTemp = _T("");
		csGetSiteTemp = GetSiteTemp();

		CString csDeviceErr = _T("");
		csDeviceErr.Format("%d", _Device_Error );

		if(csGetSiteTemp != csDeviceErr && csGetSiteTemp != "" )
			csReturnCmd.Format("%sGETSITETEMP?%s%s%s", _STX, _MTX, csGetSiteTemp, _ETX );
		else
			csReturnCmd.Format("%sGETSITETEMP?%s%s%s", _STX, _MTX, _STERROR, _ETX);

		iReturnCode = enReturnGetTemp;
	}
	else if(msg.cmd == "GETSITESETTEMP?")
	{
		// <<GetSiteSetTemp?:>>
		// <<GetSiteSetTemp?: 85.0>>
		CString csGetSiteSetTemp = _T("");
		csGetSiteSetTemp = GetSiteSetTemp();

		CString csDeviceErr = _T("");
		csDeviceErr.Format("%d", _Device_Error );

		if(csGetSiteSetTemp != csDeviceErr && csGetSiteSetTemp != "" )
			csReturnCmd.Format("%sGETSITESETTEMP?%s%s%s", _STX, _MTX, csGetSiteSetTemp, _ETX );
		else
			csReturnCmd.Format("%sGETSITESETTEMP?%s%s%s", _STX, _MTX, _STERROR, _ETX);

		iReturnCode = enReturnGetSetTemp;
	}
	else if(msg.cmd == "SETSITETEMP")
	{
		// <<SetSiteTemp: 85.0>>
		// <<SetSiteTemp: DONE>>
		// <<SetSiteTemp: ERROR>>
		CString csSetSiteTemp = _T("");
		double dSetTemp = atof( msg.parameter );
		
		double dMaxTemp = 0.0;
		double dMinTemp = 0.0;
		GetTempMaxMin( dMaxTemp, dMinTemp );
		double dparameter = atof(msg.parameter);

		if( dparameter > dMaxTemp || dparameter < dMinTemp )
			csSetSiteTemp.Format("%sSETSITETEMP%s%s%s", _STX, _MTX, _STERROR, _ETX);
		else
		{
			SetSiteTemp( dSetTemp );
			csSetSiteTemp.Format("%sSETSITETEMP%s%s%s", _STX, _MTX, _STDONE, _ETX);
		}

		csReturnCmd = csSetSiteTemp;
		iReturnCode = enReturnSetTemp;
	}
	else if(msg.cmd == "GETSTATUS?")
	{
		// <<GETSTATUS?:>>
		CString csGetStatus = _T("");
		CString csStatus = GetStatusContent();

		csGetStatus.Format("%sGETSTATUS?%s%s%s", _STX, _MTX, csStatus, _ETX);
		csReturnCmd = csGetStatus;
		iReturnCode = enReturnGetStatus;
	}
	else if(msg.cmd == "ENABLETEMP")
	{
		CString csEnableTemp = _T("");
		if(msg.parameter == "1") // enable hot test
		{
			// <<EnableTemp: DONE>>
			EnableTemp(true);
			csEnableTemp.Format("%sENABLETEMP%s%s%s", _STX, _MTX, _STDONE, _ETX);
			csReturnCmd = csEnableTemp;		
			iReturnCode = enReturnEnableTemp;
		}
		else if(msg.parameter == "0") // disable hot test
		{
			// <<EnableTemp: DONE>>
			EnableTemp(false);
			csEnableTemp.Format("%sENABLETEMP%s%s%s", _STX, _MTX, _STDONE, _ETX);
			csReturnCmd = csEnableTemp;		
			iReturnCode = enReturnEnableTemp;
		}
		else
		{
			// <<EnableTemp: ERROR>>
			EnableTemp(false);
			csEnableTemp.Format("%sENABLETEMP%s%s%s", _STX, _MTX, _STERROR, _ETX);			
			csReturnCmd = csEnableTemp;		
			iReturnCode = enReturnEnableTemp;
		}
	}
	else if(msg.cmd == "GETROTATORDEGREE?")
	{
		// <<GetRotatorDegree?:>>
		// <<GetRotatorDegree?: 1>>
		CString csGetRotator = _T("");
		int iDegree = 0;
		GetRotator( iDegree );

		CString csRotator = _T("");
		csRotator.Format("%d", iDegree);

		csReturnCmd.Format("%sGETROTATORDEGREE?%s%s%s", _STX, _MTX, csRotator, _ETX );
		iReturnCode = enReturnChangeRotatorStatus;
	}
	else if(msg.cmd == "ENABLEROTATOR")
	{
		// <<EnableRotator: 1>>
		// <<EnableRotator: DONE>>
		// <<EnableRotator: ERROR>>
		CString csEnableRotator = _T("");
		if(msg.parameter == "1") // enable rotator
		{
			EnableRotator(true);			
			csEnableRotator.Format("%sENABLEROTATOR%s%s%s", _STX, _MTX, _STDONE, _ETX);
			csReturnCmd = csEnableRotator;		
			iReturnCode = enReturnEnableRotator;
		}
		else if(msg.parameter == "0") // disable rotator
		{
			EnableRotator(false);
			csEnableRotator.Format("%sENABLEROTATOR%s%s%s", _STX, _MTX, _STDONE, _ETX);
			csReturnCmd = csEnableRotator;		
			iReturnCode = enReturnEnableRotator;	
		}
		else
		{
			EnableTemp(false);
			csEnableRotator.Format("%sENABLEROTATOR%s%s%s", _STX, _MTX, _STERROR, _ETX);
			csReturnCmd = csEnableRotator;		
			iReturnCode = enReturnEnableRotator;
		}
	}
	else if(msg.cmd == "ENABLECCDLOG")
	{
		// <<EnableCCDLog: 1>>
		// <<EnableCCDLog: DONE>>
        // <<EnableCCDLog: ERROR>>
		CString csEnableCCDLogIC = _T("");
		if(msg.parameter == "1") // enable ccd log ic
		{
			// <<EnableCCDLog: DONE>>
			EnableCCDLogIC(true);			
			csEnableCCDLogIC.Format("%sENABLECCDLOG%s%s%s", _STX, _MTX, _STDONE, _ETX);
			csReturnCmd = csEnableCCDLogIC;
			iReturnCode = enReturnCCDLogIC;
		}
		else if(msg.parameter == "0") // disable ccd log ic
		{
			EnableCCDLogIC(false);			
			csEnableCCDLogIC.Format("%sENABLECCDLOG%s%s%s", _STX, _MTX, _STDONE, _ETX);
			csReturnCmd = csEnableCCDLogIC;
			iReturnCode = enReturnCCDLogIC;
		}
		else
		{
			EnableCCDLogIC(false);
			csEnableCCDLogIC.Format("%sENABLECCDLOG%s%s%s", _STX, _MTX, _STERROR, _ETX);
			csReturnCmd = csEnableCCDLogIC;
			iReturnCode = enReturnCCDLogIC;		
		}
	}
	else if(msg.cmd == "SETROTATORDEGREE")
	{
		// <<SetRotatorDegree:3>>
		// <<SetRotatorDegree: DONE>>
        // <<SetRotatorDegree: ERROR>>
		CString csChangeRotator = _T("");
		CString csRotatorCmdP = _T("");
		CString csRotatorCmdN = _T("");
		CString csRotatorCmdZ = _T("");
		CString csRotatorCmdU = _T("");

		csRotatorCmdP.Format("%d", enRotatorModeP ); // +90
		csRotatorCmdN.Format("%d", enRotatorModeN ); // -90
		csRotatorCmdZ.Format("%d", enRotatorModeZ ); // 0
		csRotatorCmdU.Format("%d", enRotatorModeU ); // +180

		if( msg.parameter == csRotatorCmdP )
		{
			// +90
			// <<SetRotatorDegree: DONE>>
			SetRotator(enRotatorModeP);			
			csChangeRotator.Format("%sSETROTATORDEGREE%s%s%s", _STX, _MTX, _STDONE, _ETX);
			csReturnCmd = csChangeRotator;		
			iReturnCode = enReturnEnableRotator;
		}
		else if( msg.parameter == csRotatorCmdN )
		{
			// -90
			// <<SetRotatorDegree: DONE>>
			SetRotator(enRotatorModeN);
			csChangeRotator.Format("%sSETROTATORDEGREE%s%s%s", _STX, _MTX, _STDONE, _ETX);
			csReturnCmd = csChangeRotator;		
			iReturnCode = enReturnEnableRotator;
		}
		else if( msg.parameter == csRotatorCmdZ )
		{
			// 0
			SetRotator(enRotatorModeZ);
			csChangeRotator.Format("%sSETROTATORDEGREE%s%s%s", _STX, _MTX, _STDONE, _ETX);
			csReturnCmd = csChangeRotator;		
			iReturnCode = enReturnEnableRotator;
		}
		else if( msg.parameter == csRotatorCmdU )
		{				
			// 180
			SetRotator(enRotatorModeU);
			csChangeRotator.Format("%sSETROTATORDEGREE%s%s%s", _STX, _MTX, _STDONE, _ETX);
			csReturnCmd = csChangeRotator;		
			iReturnCode = enReturnEnableRotator;
		}
		else
		{
			// Err
			SetRotator( enRotatorModeP );
			csChangeRotator.Format("%sSETROTATORDEGREE%s%s%s", _STX, _MTX, _STERROR, _ETX);
			csReturnCmd = csChangeRotator;
			iReturnCode = enReturnChangeRotator;		
		}
	}
	else if(msg.cmd == "GETCOORDINATES?")
	{
		// <<GetCoordinates?:>>
		// <<GetCoordinates?: 0.1,2>>
        // <<GetCoordinates?: ERROR>>
		CString csGetCordnation = _T("");
		CString csCoordnation = _T("");
		csCoordnation.Format("%d%s%d%s%d", m_RemoteTray.iTray, _CMTX, m_RemoteTray.iCol, _CMTX, m_RemoteTray.iRow );

		csGetCordnation.Format("%sGETCOORDINATES?%s%s%s", _STX, _MTX, csCoordnation, _ETX );	

		csReturnCmd = csGetCordnation;
		iReturnCode = enReturnGetCoordnation;
	}
	else if(msg.cmd == "SETCOORDINATES")
	{
		// <<SetCoordinates: 0,1,2>>
		// <<SetCoordinates: DONE>>
        // <<SetCoordinates: ERROR>>
		CString csSetCordnation = _T("");	
		CString csTrayParameter = _T("");
		csTrayParameter = msg.parameter;

		tagRemoteCoord reTray;
		bool bCoordOK = VerifyCoord( csTrayParameter, reTray );

		if(bCoordOK)
		{
			int iCol = -1;
			int iRow = -1;
			GetTraySpec( iCol, iRow );

			if( reTray.iCol > (iCol-1) || reTray.iRow > (iRow-1) )
			{
				// spec out of range
				csSetCordnation.Format("%sSETCOORDINATES%s%s%s", _STX, _MTX, _STERROR, _ETX);
			}
			else
			{
				// set ok
				csSetCordnation.Format("%sSETCOORDINATES%s%s%s", _STX, _MTX, _STDONE, _ETX);
				m_RemoteTray = reTray;
				SetCoord( m_RemoteTray.iTray, m_RemoteTray.iCol, m_RemoteTray.iRow);
			}
		}
		else
		{
			// parameter error
			csSetCordnation.Format("%sSETCOORDINATES%s%s%s", _STX, _MTX, _STERROR, _ETX);
			ClearRemoteTray();
			SetCoord( m_RemoteTray.iTray, m_RemoteTray.iCol, m_RemoteTray.iRow);
		}

		csReturnCmd = csSetCordnation;
		iReturnCode = enReturnSetCoordnation;
	}
	else if(msg.cmd == "SETAUTOSKIP")
	{
		// <<AutoSkip: 0>>
		CString csAutoSkip = _T("");
		if(msg.parameter == "1") // no auto skip
		{
			csAutoSkip.Format("%sSETAUTOSKIP%s%s%s", _STX, _MTX, _STDONE, _ETX);
			SetAutoSkip( false );
			iReturnCode = enReturnAutoSkip;
			csReturnCmd = csAutoSkip;
		}
		else if(msg.parameter == "0" ) // auto skip
		{
			csAutoSkip.Format("%sSETAUTOSKIP%s%s%s", _STX, _MTX, _STDONE, _ETX);
			SetAutoSkip( true );
			iReturnCode = enReturnAutoSkip;
			csReturnCmd = csAutoSkip;		
		}
		else
		{
			// Err
			csAutoSkip.Format("%sSETAUTOSKIP%s%s%s", _STX, _MTX, _STERROR, _ETX);
			SetAutoSkip( false );
			csReturnCmd = csAutoSkip;
			iReturnCode = enReturnAutoSkip;		
		}
	}
	else if(msg.cmd == "GETAUTOSKIP?")
	{
		// <<GetAutoSkip?:>>
		CString csGetAutoSkip = _T("");
		CString csGetAutoStatus = _T("");
		bool bEnableAutoSkip = false;
		csGetAutoStatus = GetAutoSkip( bEnableAutoSkip );
		if( bEnableAutoSkip )
			csGetAutoSkip.Format( "%sGETAUTOSKIP%s%s%s", _STX, _MTX, csGetAutoStatus, _ETX );
		else
			csGetAutoSkip.Format( "%sGETAUTOSKIP%s%s%s", _STX, _MTX, csGetAutoStatus, _ETX );

		//
		csReturnCmd = csGetAutoSkip;
		iReturnCode = enReturnGetAutoSkip;	
	}
	else if( msg.cmd == "SETTSVACC" )
	{
		// <<SetTsVacc: 1>>
		// <<SETTSVACC: DONE>>
		CString csTsVacc = _T("");
		if( msg.parameter == "1" )
		{
			csTsVacc.Format("%sSETTSVACC%s%s%s", _STX, _MTX, _STDONE, _ETX);
			SetTsVacc( true );
			csReturnCmd = csTsVacc;
			iReturnCode = enReturnSetTsVacc;
		}
		else if( msg.parameter == "0" )
		{
			csTsVacc.Format("%sSETTSVACC%s%s%s", _STX, _MTX, _STDONE, _ETX);
			SetTsVacc( false );
			csReturnCmd = csTsVacc;
			iReturnCode = enReturnSetTsVacc;		
		}
		else 
		{
			csTsVacc.Format("%sSETTSVACC%s%s%s", _STX, _MTX, _STERROR, _ETX);
			SetTsVacc( false );
			csReturnCmd = csTsVacc;
			iReturnCode = enReturnSetTsVacc;		
		}
	}
	else if( msg.cmd == "GETTSVACC?" )
	{
		// <<GetVacc?:>>
		CString csTsVacc = _T("");
		CString csGetTsVaccStatus = _T("");
		bool bTsVaccEnable = false;
		csGetTsVaccStatus = GetTsVacc( bTsVaccEnable );
		if( bTsVaccEnable )
			csTsVacc.Format( "%sGETTSVACC?%s%s%s", _STX, _MTX, csGetTsVaccStatus, _ETX );
		else
			csTsVacc.Format( "%sGETTSVACC?%s%s%s", _STX, _MTX, csGetTsVaccStatus, _ETX );

		csReturnCmd = csTsVacc;
		iReturnCode = enReturnGetTsVacc;
	}
	else if( msg.cmd == "GETTRAYSPEC?" )
	{
		// <<GetTraySpec?:>>
		// <<GetTraySpec?: 10,26>>
		CString csGetTraySpec = _T("");
		int iCol = 0;
		int iRow = 0;

		GetTraySpec( iCol, iRow );
		CString csTraySpec = _T("");
		csTraySpec.Format("%d,%d", iCol, iRow);

		csGetTraySpec.Format( "%sGETTRAYSPEC?%s%s%s", _STX, _MTX, csTraySpec, _ETX );
		csReturnCmd = csGetTraySpec;
		iReturnCode = enReturnGetTraySpec;
	}
	else if(msg.cmd == "SETCOORDINATESGO")
	{
		// <<SetCoordinatesGo:>>
		// <<SetCoordinatesGo: DONE>>
        // <<SetCoordinatesGo: ERROR>>
		CString csSetCoordnationGo = _T("");
		CString csSetCoordnationGoNoReady = _T("");
		if( GetReadyCommand( csSetCoordnationGoNoReady ) )
		{
			bCommandNeedReturn = false; // No reply message
			csSetCoordnationGo.Format("%sSETCORDNATIONGO%s%s%s", _STX, _MTX, _STDONE, _ETX);
			RequestCoordnationMissionGo();
		}
		else
		{
			csSetCoordnationGoNoReady.Format("%s", _STERROR);
			csSetCoordnationGo.Format("%sSETCORDNATIONGO%s%s%s", _STX, _MTX, csSetCoordnationGoNoReady, _ETX);
		}

		bNeedReturn = bCommandNeedReturn;
		csReturnCmd = csSetCoordnationGo;
		iReturnCode = enReturnSetCoordnationGo;	
	}
	else if(msg.cmd == "SETCOORDINATESCLEARGO")
	{
		// <<SetCoordinatesClearGo:>>
		CString csSetCoordnationClearGo = _T("");
		csSetCoordnationClearGo.Format("%sSETCOORDINATESCLEARGO%s%s%s", _STX, _MTX, _STDONE, _ETX);
		RequestCoordnationMissionClearGo();

		csReturnCmd = csSetCoordnationClearGo;
		iReturnCode = enReturnSetCoordnationClearGo;
	}
	else if(msg.cmd == "SETCOORDINATESRETURN")
	{
		// <<SetCoordinatesReturn:>>
		// <<SetCoordinatesReturn: DONE>>
        // <<SetCoordinatesReturn: ERROR>>
		CString csCoordnationReturn = _T("");
		CString csCoordnationNoReturnReason = _T("");
		if( GetReadyReturnCommand( csCoordnationNoReturnReason ) && !GetSystemError() )
		{
			bCommandNeedReturn = false; // No reply message
			csCoordnationReturn.Format("%sSETCORDNATIONRETURN%s%s%s", _STX, _MTX, _STDONE, _ETX);
			RequestCoordnationMissionReturn(); // return
		}
		else
		{
			if( GetSystemError() )
				m_bReturnError = true;

			csCoordnationNoReturnReason.Format("%s", _STERROR);
			csCoordnationReturn.Format("%sSETCORDNATIONRETURN%s%s%s", _STX, _MTX, csCoordnationNoReturnReason, _ETX);
		}

		bNeedReturn = bCommandNeedReturn;
		csReturnCmd = csCoordnationReturn;
		iReturnCode = enReturnSetCoordnationReturn;
	}
#endif

}
void CDriverTestInterface::ProcessCommand()
{
	if( m_ReviceCmd.GetSize() > 0 )
	{	
		tagTestProtocol tagCmd = m_ReviceCmd.GetAt(0);
	
		// Command
		///////////////////////////////////////////////////////////
		// 執行命令命令
		CString csCmd = _T("");
		csCmd.Format("%s", tagCmd.cmd );
		tagCmd.cmd.MakeUpper(); tagCmd.cmd.TrimLeft(); tagCmd.cmd.TrimRight();

		CString csReply = _T("");
		int iReply = 0;
		bool bNeedReturn = true;
		GetReturnCommand( tagCmd, csReply, iReply, bNeedReturn );

		///////////////////////////////////////////////////////////
		// 回復命令
		AddReplyCmd( csReply, bNeedReturn );
	
		///////////////////////////////////////////////////////////
		// 記錄命令
		// Log command
		RemoteCommMsgCmd( csCmd );

		///////////////////////////////////////////////////////////
		// 移除命令
		// Remove command
		m_ReviceCmd.RemoveAt(0);
	}
}

tagTestProtocol CDriverTestInterface::GetProtocol(CString &csTelegram)
{	
	tagTestProtocol result;
	
	// 如果 return site <= 0 表示沒有收到正確的 protocol
	// 如果 site = -1, 表示只有一個 %
	// 如果 site = 0, 表示沒有收到 %
	result.site = 0;
	
	int iStart = csTelegram.Find( _STX , 0);

	if(iStart == -1)
		return result;

	// 找 >> 
	int iEnd = csTelegram.Find(_ETX);
	if(iEnd < iStart)
	{
		csTelegram.Empty();
		return result;
	}
	CString cs;
	cs = csTelegram.Mid(iStart, iEnd - iStart + sizeof(_ETX));
	csTelegram.Delete(0, iEnd + sizeof(_ETX));

	// 將字首字尾拿掉
	cs.Replace( _STX, ""); cs.Replace( _ETX, "");
	
	// SiteNo%Command%Parameter
	// 找第一個 %
	iStart = cs.Find( _MTX );
	if(iStart == -1)
	{
		result.site = 0;
	}
	
	// 找第二個 %
	int iSecond = cs.Find( _MTX, iStart+1);
	if(iSecond == -1)
	{
		result.site = -1;
	}
	
	// 取出 Site
	CString cc = _T("");
	cc = cs.Mid(0, iStart);
	
	result.site = atoi(cc.GetBuffer(0));
	if(result.site > 6 || result.site < 1)
		result.site = 7; // all sites

	result.csSite = cc;
	
	cs.Delete(0, iStart+1);
	
	// 取出 command
	cc = cs.Mid(0, iSecond-iStart-1);
	result.cmd = cc;
	cs.Delete(0, iSecond-iStart);
	
	// 取出 parameter
	result.parameter = cs;
	result.cmd.MakeUpper();
	return result;
}

void CDriverTestInterface::Read()
{
	// 將 RS232 的值讀到 Buffer
	byte receive[4096] = {0};
	unsigned long ulNumRead = 0;

	::ReadFile(m_hComm, receive, sizeof(receive), &ulNumRead, NULL);
	if(ulNumRead > 0)
	{
		CString cs = receive;
		cs.TrimRight(); cs.TrimLeft();
		csBuffer += cs;

		// Log to dialog
		RemoteRawMsg( cs );
	}

#ifdef _Demo
	if( m_csSimBuffer != "" )
	{
		csBuffer = m_csSimBuffer;
		RemoteCommAddBuffer("");
	}
#endif

	// 1.0Al
	// Remove this and re-build new one
	/*
	// 將 Buffer 的值拆解成 Protocol
	int iStart = 0, iEnd = 0;
	CString csTelegram = _T("");
	iStart = csBuffer.Find( _STX );	// "<<"
	while(iStart > -1)
	{
		iEnd = csBuffer.Find( _ETX, iStart);	// ">>"
		if(iEnd > iStart)
		{
			csTelegram = csBuffer.Mid(iStart, iEnd-iStart+2);
			// 不管 iStart 是多少，都從第一個開始刪掉

			csBuffer.Delete(0, iEnd+2);
			// 如果 result.site = -1, 表示只有一個 %
			// 如果 result.site = 0, 表示沒有收到 %

			Log( csTelegram );
			// 記錄讀取成功的字串
			
			tagTestProtocol result = GetProtocol(csTelegram.GetBuffer(0));
			if(result.site > 0)
				AddReadCmd(result);
			else // 回應 Format Error
			{
				CString csReply = _T("");
				csTelegram.Replace( _STX, ""); csTelegram.Replace( _ETX, "");
				if(result.site == 0)
					csReply.Format("%s%s%sNAK;Format Error%s", _STX, _MTX, csTelegram, _ETX);
				else
					csReply.Format("%s%s%sNAK;Format Error%s", _STX, _MTX, csTelegram, _ETX);

				//
				AddReplyCmd(csReply);
			}

			// 繼續下一個 message
			iStart = csBuffer.Find( _STX );
		}
		else
			break;
	}
	*/
	// 將 Buffer 的值拆解成 Protocol
	int iStart = 0, iEnd = 0;
	CString csTelegram = _T("");
	iStart = csBuffer.Find( _STX );	// "<<"
	while(iStart > -1)
	{
		iEnd = csBuffer.Find( _ETX, iStart);	// ">>"
		if(iEnd > iStart)
		{
			CString csTail = _T("");
			csTail.Format("%s", _ETX );
			csTelegram = csBuffer.Mid(iStart, iEnd-iStart+csTail.GetLength());
			// 不管 iStart 是多少，都從第一個開始刪掉

			csBuffer.Delete(0, iEnd+csTail.GetLength());
			// 刪除命令, 避開雜訊

			Log( csTelegram );
			// 記錄讀取成功的字串
			
			tagTestProtocol result = GetProtocol(csTelegram);
			AddReadCmd(result);
			// 新增 Command 到 Queue

			iStart = csBuffer.Find( _STX );
			// 繼續下一個 message
		}
		else
			break;
	}
}
void CDriverTestInterface::AddReadCmd(tagTestProtocol tagReadCmd)
{
	m_ReviceCmd.Add( tagReadCmd );
}
void CDriverTestInterface::Write()
{
	bool result = true;
	unsigned long iLength = 0;

	if( m_SendCmd.GetSize() > 0)
	{
		CString cs = m_SendCmd.GetAt(0);		
		result = WriteFile(m_hComm, cs, cs.GetLength(), &iLength, NULL) == 0 ? false : true;
		if(result)
			m_SendCmd.RemoveAt(0);
	}
}
void CDriverTestInterface::AddReplyCmd(CString csReplyCmd, bool bAddCommand)
{
	csReplyCmd.TrimLeft();
	csReplyCmd.TrimRight();

	//
	if( csReplyCmd != "" && bAddCommand )
	{
		m_SendCmd.Add( csReplyCmd );

		m_SendTCPCmd.Add( csReplyCmd );

		RemoteSendMsdCmd( csReplyCmd );
	}
}
CMutex MutexChangeString;
void CDriverTestInterface::RemoteCommAddBuffer(CString csSimBuffer)
{
	CSingleLock Lock(&MutexChangeString);
	Lock.Lock();

	m_csSimBuffer = csSimBuffer;

	Lock.Unlock();
}
void CDriverTestInterface::RemoteSendMsdCmd(CString csMsg)
{
	//
	csMsg.TrimLeft();
	csMsg.TrimRight();

	//
	if( theApp.m_DlgRemoteComm.GetSafeHwnd())
	{
		::SendMessage( theApp.m_DlgRemoteComm.GetSafeHwnd(), 
			WM_REMOTE_SEND,  (WPARAM)&csMsg , (LPARAM)&csMsg );
	}

	//
	LogRaw( csMsg );

	//
	Log( csMsg );
}

static CMutex MutexRemoteRawBinLog;
void CDriverTestInterface::RemoteRawMsg(CString csMsg)
{
	CSingleLock Lock(&MutexRemoteRawBinLog);
	Lock.Lock();

	//
	csMsg.TrimLeft();
	csMsg.TrimRight();

	//
	if( theApp.m_DlgRemoteComm.GetSafeHwnd())
	{
		::SendMessage( theApp.m_DlgRemoteComm.GetSafeHwnd(), 
			WM_REMOTE_RECV_RAW,  (WPARAM)&csMsg , (LPARAM)&csMsg );
	}

	// 1.0Ao
	// TCP/IP
	if( theApp.m_DlgSLTProtocol->GetSafeHwnd())
	{
		::SendMessage( theApp.m_DlgSLTProtocol->GetSafeHwnd(), 
			WM_SLT_PROTOCOL_MSG,  (WPARAM)&csMsg , (LPARAM)&csMsg );	
	}

	//
	LogRaw( csMsg );

	//
	Lock.Unlock();
}
void CDriverTestInterface::RemoteCommMsgCmd(CString csMsg)
{
	//
	csMsg.TrimLeft();
	csMsg.TrimRight();

	//
	if( theApp.m_DlgRemoteComm.GetSafeHwnd())
	{
		::SendMessage( theApp.m_DlgRemoteComm.GetSafeHwnd(), 
			WM_REMOTE_RECV,  (WPARAM)&csMsg , (LPARAM)&csMsg );
	}
}
bool CDriverTestInterface::Open(int iPort, int iBaudRate )
{
	bool bOpenOK = false;

	m_iBaudRate = iBaudRate;

#ifdef _Demo
	bOpenOK = true;
	return bOpenOK;
#endif

	if(iPort < 0)
	{
		bOpenOK =  false;
		return bOpenOK;
	}

	if(m_hComm != NULL)
	{
		bOpenOK = true;
		return bOpenOK;
	}

	DCB PortDCB;
	COMMTIMEOUTS CommTimeouts;
	CString cs = _T("");

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
//		AfxMessageBox((LPCTSTR)lpMsgBuf);
		// Free the buffer.
		LocalFree( lpMsgBuf );
		
		bOpenOK = false;
		return bOpenOK;
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
	
	/*
	PortDCB.fOutX = TRUE;                // No XON/XOFF out flow control 
	PortDCB.fInX = TRUE;                 // No XON/XOFF in flow control 
	PortDCB.fOutxCtsFlow = FALSE;         // No CTS output flow control 
	PortDCB.fOutxDsrFlow = FALSE;         // No DSR output flow control 
	PortDCB.fDtrControl = DTR_CONTROL_DISABLE; 
	PortDCB.fTXContinueOnXoff = FALSE;     // XOFF continues Tx 
	PortDCB.fRtsControl = RTS_CONTROL_DISABLE; 
	*/

/*
	PortDCB.fBinary = FALSE;               // Binary mode; no EOF check 
	// DTR flow control type 
	PortDCB.fDsrSensitivity = FALSE;      // DSR sensitivity 
	PortDCB.fErrorChar = FALSE;           // Disable error replacement. 
	PortDCB.fNull = TRUE;                // Disable null stripping. 
	// RTS flow control 
	PortDCB.fAbortOnError = FALSE;        // Do not abort reads/writes on 
	// error.
*/	
	// Configure the port according to the specifications of the DCB 
	// structure.
	if (!SetCommState (m_hComm, &PortDCB))
	{
		Close();
		bOpenOK = false;
		return bOpenOK;
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
		bOpenOK = false;
		return bOpenOK;
	}

	bOpenOK = true;

	return bOpenOK;
}
bool CDriverTestInterface::SetOpen(HANDLE m_hCommOther)
{

	return true;
}
void CDriverTestInterface::InitCommandSetup()
{
	m_RemoteCommandList.m_RemoteCommand.RemoveAll();
	int iCommandID = 0;
	tagRemoteCommand m_pCommandData;

	// <<GetHelp?:>>
	m_pCommandData.m_iRemoteCommandID = iCommandID; iCommandID++;
	m_pCommandData.m_csRemoteCommandName = "<<GetHelp?:>>";
	m_pCommandData.m_csRemoteFunction = "None";
	m_RemoteCommandList.m_RemoteCommand.Add( m_pCommandData );

	// <<GetVersion?:>>
	m_pCommandData.m_iRemoteCommandID = iCommandID; iCommandID++;
	m_pCommandData.m_csRemoteCommandName = "<<GetVersion?:>>";
	m_pCommandData.m_csRemoteFunction = "None";
	m_RemoteCommandList.m_RemoteCommand.Add( m_pCommandData );

	// <<GetState?:>>
	m_pCommandData.m_iRemoteCommandID = iCommandID; iCommandID++;
	m_pCommandData.m_csRemoteCommandName = "<<GetState?:>>";
	m_pCommandData.m_csRemoteFunction = "None";
	m_RemoteCommandList.m_RemoteCommand.Add( m_pCommandData );

	// <<SetState: INITIALIZE>>
	m_pCommandData.m_iRemoteCommandID = iCommandID; iCommandID++;
	m_pCommandData.m_csRemoteCommandName = "<<SetState: _>>";
	m_pCommandData.m_csRemoteFunction = "None";
	m_RemoteCommandList.m_RemoteCommand.Add( m_pCommandData );

	// <<GetStatus?:>>
	m_pCommandData.m_iRemoteCommandID = iCommandID; iCommandID++;
	m_pCommandData.m_csRemoteCommandName = "<<GetStatus?:>>";
	m_pCommandData.m_csRemoteFunction = "None";
	m_RemoteCommandList.m_RemoteCommand.Add( m_pCommandData );

	// <<GetTraySpec?:>>
	m_pCommandData.m_iRemoteCommandID = iCommandID; iCommandID++;
	m_pCommandData.m_csRemoteCommandName = "<<GetTraySpec?:>>";
	m_pCommandData.m_csRemoteFunction = "None";
	m_RemoteCommandList.m_RemoteCommand.Add( m_pCommandData );

	// <<EnableTemp: 1>>
	m_pCommandData.m_iRemoteCommandID = iCommandID; iCommandID++;
	m_pCommandData.m_csRemoteCommandName = "<<EnableTemp: _>>";
	m_pCommandData.m_csRemoteFunction = "None";
	m_RemoteCommandList.m_RemoteCommand.Add( m_pCommandData );

	// <<SetSiteTemp: 85.0>>
	m_pCommandData.m_iRemoteCommandID = iCommandID; iCommandID++;
	m_pCommandData.m_csRemoteCommandName = "<<SetSiteTemp: _>>";
	m_pCommandData.m_csRemoteFunction = "None";
	m_RemoteCommandList.m_RemoteCommand.Add( m_pCommandData );

	// <<GetSiteSetTemp?:>>
	m_pCommandData.m_iRemoteCommandID = iCommandID; iCommandID++;
	m_pCommandData.m_csRemoteCommandName = "<<GetSiteSetTemp?:>>";
	m_pCommandData.m_csRemoteFunction = "None";
	m_RemoteCommandList.m_RemoteCommand.Add( m_pCommandData );

	// <<GetSiteTemp?:>>
	m_pCommandData.m_iRemoteCommandID = iCommandID; iCommandID++;
	m_pCommandData.m_csRemoteCommandName = "<<GetSiteTemp?:>>";
	m_pCommandData.m_csRemoteFunction = "None";
	m_RemoteCommandList.m_RemoteCommand.Add( m_pCommandData );

	// <<EnableRotator: 1>>
	m_pCommandData.m_iRemoteCommandID = iCommandID; iCommandID++;
	m_pCommandData.m_csRemoteCommandName = "<<EnableRotator: _>>";
	m_pCommandData.m_csRemoteFunction = "None";
	m_RemoteCommandList.m_RemoteCommand.Add( m_pCommandData );

	// <<SetRotatorDegree: 1>>
	m_pCommandData.m_iRemoteCommandID = iCommandID; iCommandID++;
	m_pCommandData.m_csRemoteCommandName = "<<SetRotatorDegree: _>>";
	m_pCommandData.m_csRemoteFunction = "None";
	m_RemoteCommandList.m_RemoteCommand.Add( m_pCommandData );

	// <<GetRotatorDegree?:>>
	m_pCommandData.m_iRemoteCommandID = iCommandID; iCommandID++;
	m_pCommandData.m_csRemoteCommandName = "<<GetRotatorDegree?:>>";
	m_pCommandData.m_csRemoteFunction = "None";
	m_RemoteCommandList.m_RemoteCommand.Add( m_pCommandData );

	// <<EnableCCDLog: 1>>
	m_pCommandData.m_iRemoteCommandID = iCommandID; iCommandID++;
	m_pCommandData.m_csRemoteCommandName = "<<EnableCCDLog: _>>";
	m_pCommandData.m_csRemoteFunction = "None";
	m_RemoteCommandList.m_RemoteCommand.Add( m_pCommandData );

	// <<SetCoordinates: 0,1,2>>
	m_pCommandData.m_iRemoteCommandID = iCommandID; iCommandID++;
	m_pCommandData.m_csRemoteCommandName = "<<SetCoordinates: _,_,_>>";
	m_pCommandData.m_csRemoteFunction = "None";
	m_RemoteCommandList.m_RemoteCommand.Add( m_pCommandData );

	// <<GetCoordinates?:>>
	m_pCommandData.m_iRemoteCommandID = iCommandID; iCommandID++;
	m_pCommandData.m_csRemoteCommandName = "<<GetCoordinates?:>>";
	m_pCommandData.m_csRemoteFunction = "None";
	m_RemoteCommandList.m_RemoteCommand.Add( m_pCommandData );

	// <<SetCoordinatesGo:>>
	m_pCommandData.m_iRemoteCommandID = iCommandID; iCommandID++;
	m_pCommandData.m_csRemoteCommandName = "<<SetCoordinatesGo:>>";
	m_pCommandData.m_csRemoteFunction = "None";
	m_RemoteCommandList.m_RemoteCommand.Add( m_pCommandData );

	// <<SetCoordinatesReturn:>>
	m_pCommandData.m_iRemoteCommandID = iCommandID; iCommandID++;
	m_pCommandData.m_csRemoteCommandName = "<<SetCoordinatesReturn:>>";
	m_pCommandData.m_csRemoteFunction = "None";
	m_RemoteCommandList.m_RemoteCommand.Add( m_pCommandData );

	// <<SetPressure: 8>>
	m_pCommandData.m_iRemoteCommandID = iCommandID; iCommandID++;
	m_pCommandData.m_csRemoteCommandName = "<<SetPressure: _>>";
	m_pCommandData.m_csRemoteFunction = "None";
	m_RemoteCommandList.m_RemoteCommand.Add( m_pCommandData );

	// <<GetPressur?e:>>
	m_pCommandData.m_iRemoteCommandID = iCommandID; iCommandID++;
	m_pCommandData.m_csRemoteCommandName = "<<GetPressure?:>>";
	m_pCommandData.m_csRemoteFunction = "None";
	m_RemoteCommandList.m_RemoteCommand.Add( m_pCommandData );

}
// 1.0Ao
// Remove this, and re-build new one
/*
bool CDriverTestInterface::InitTestInterface(int iPort)
{
	bool bOK = false;

	//
	InitCommandSetup();

	//
	CString csHelpFile = _T("");
	GetHelpFile( csHelpFile );

	//
	// Serial Port Layer
	if( Open(iPort) )
	{		
		//
		hProcessWrite		= NULL;
		hProcessRead		= NULL;
		
		CWinThread *pWindThreadWrite = NULL;
		CWinThread *pWindThreadRead = NULL;
		
		// Write
		pWindThreadWrite = AfxBeginThread(ThreadTestInterfaceWrite, this);
		if(pWindThreadWrite)
			hProcessWrite = pWindThreadWrite->m_hThread;
		
		// Read
		pWindThreadRead = AfxBeginThread(ThreadTestInterfaceRead, this);
		if(pWindThreadRead)
			hProcessRead = pWindThreadRead->m_hThread;

		bOK = true;
	}
	else
		bOK = false;

	return bOK;
}
*/
bool CDriverTestInterface::InitTestInterface(int iPort)
{
	bool bOK = false;

	//
	InitCommandSetup();

	//
	CString csHelpFile = _T("");
	GetHelpFile( csHelpFile );

	/////////////////////////////////////////////////////////////////
	// Serial Port Layer
	if( Open(iPort) )
	{		
		//
		hProcessWrite		= NULL;
		hProcessRead		= NULL;
		
		CWinThread *pWindThreadWrite = NULL;
		CWinThread *pWindThreadRead = NULL;
		
		// Write
		pWindThreadWrite = AfxBeginThread(ThreadTestInterfaceWrite, this);
		if(pWindThreadWrite)
			hProcessWrite = pWindThreadWrite->m_hThread;
		
		// Read
		pWindThreadRead = AfxBeginThread(ThreadTestInterfaceRead, this);
		if(pWindThreadRead)
			hProcessRead = pWindThreadRead->m_hThread;

		bOK = true;
	}
	else
		bOK = false;


	return bOK;
}
void CDriverTestInterface::InitTestInterfaceTCP()
{
	/////////////////////////////////////////////////////////////////
	// Ethernet(TCP/IP) Layer
	if( OpenTCP( 3000 ) )
	{
		hProcessWriteTCP = NULL;
		hProcessReadTCP	= NULL;

		CWinThread *pWindThreadWriteTCP = NULL;
		CWinThread *pWindThreadReadTCP = NULL;

		// Write
		pWindThreadWriteTCP = AfxBeginThread(ThreadTestInterfaceWriteTCP, this);
		if(pWindThreadWriteTCP)
			hProcessWriteTCP = pWindThreadWriteTCP->m_hThread;

		// Read
		pWindThreadReadTCP = AfxBeginThread(ThreadTestInterfaceReadTCP, this);
		if(pWindThreadReadTCP)
			hProcessReadTCP = pWindThreadReadTCP->m_hThread;
	}
}
void CDriverTestInterface::InitTestInterfaceExcute()
{
	hProcessExcute = NULL;
	
	CWinThread *pWindThreadWriteExcute = NULL;
	// Write
	pWindThreadWriteExcute = AfxBeginThread(ThreadTestInterfaceExcute, this);
	if(pWindThreadWriteExcute)
		hProcessExcute = pWindThreadWriteExcute->m_hThread;
}
void CDriverTestInterface::CloseWrite()
{
	MSG				msg;
	LARGE_INTEGER	start, end, freq;
	DWORD			nThreadExitCode = 0;
	BOOL			bSuccess = FALSE;

	::QueryPerformanceFrequency(&freq);
	::QueryPerformanceCounter(&start);
	if(hProcessWrite != NULL)
	{
	do
	{
		bSuccess = GetExitCodeThread(hProcessWrite, &nThreadExitCode);
		::QueryPerformanceCounter(&end);

		if(::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			::TranslateMessage(&msg);
			::DispatchMessage(&msg);
		}
	}while(bSuccess && nThreadExitCode == STILL_ACTIVE && (end.QuadPart - start.QuadPart) / freq.QuadPart < 10);  //10秒表示等10s, 可依據需求修改
	}
}
bool CDriverTestInterface::Close()
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
void CDriverTestInterface::CloseRead()
{
	MSG				msg;
	LARGE_INTEGER	start, end, freq;
	DWORD			nThreadExitCode = 0;
	BOOL			bSuccess = FALSE;

	::QueryPerformanceFrequency(&freq);
	::QueryPerformanceCounter(&start);
	if(hProcessRead != NULL)
	{
	do
	{
		bSuccess = GetExitCodeThread(hProcessRead, &nThreadExitCode);
		::QueryPerformanceCounter(&end);

		if(::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			::TranslateMessage(&msg);
			::DispatchMessage(&msg);
		}
	}while(bSuccess && nThreadExitCode == STILL_ACTIVE && (end.QuadPart - start.QuadPart) / freq.QuadPart < 10);  //10秒表示等10s, 可依據需求修改
	}
}
//
bool CDriverTestInterface::GetIOMonitorOpen()
{
	// 確認 IO Monitor 是否被打開
	bool bIOMonitorOpen = false;

	if( m.Info.bIOMonitor || m.Info.bSubDlgOpen )
		bIOMonitorOpen = true;

	return bIOMonitorOpen;
}
bool CDriverTestInterface::GetButtonStartStatus()
{
	// 確認 Panel Start 是否可以被按下
	bool bButtonStart = true;
	if( GetIOMonitorOpen() )
		bButtonStart = false;
	if( m.RemoteOutSet.BtnStartOn == 0 )
		bButtonStart = false;

	return bButtonStart;
}
bool CDriverTestInterface::GetButtonStopStatus()
{
	// 確認 Panel Stop 是否可以被按下
	bool bButtonStop = true;
	if( GetIOMonitorOpen() )
		bButtonStop = false;
	if( m.RemoteOutSet.BtnStopOn == 0 )
		bButtonStop = false;

	return bButtonStop;
}
bool CDriverTestInterface::GetButtonInitialStatus()
{
	// 確認 Panel Initial 是否可以被按下
	bool bButtonInitial = true;
	if( GetIOMonitorOpen() )
		bButtonInitial = false;
	if( m.RemoteOutSet.BtnInitialOn == 0 )
		bButtonInitial = false;

	return bButtonInitial;
}
bool CDriverTestInterface::GetButtonRetryStatus()
{
	// 確認 Panel Retry 是否可以被按下
	bool bButtonRetry = true;
	if( GetIOMonitorOpen() )
		bButtonRetry = false;
	if( m.RemoteOutSet.BtnRetryOn == 0 )
		bButtonRetry = false;

	return bButtonRetry;
}
bool CDriverTestInterface::GetButtonSkipStatus()
{
	// 確認 Panel Skip 是否可以被按下
	bool bButtonSkip = true;
	if( GetIOMonitorOpen() )
		bButtonSkip = false;
	if( m.RemoteOutSet.BtnSkipOn == 0 )
		bButtonSkip = false;

	return bButtonSkip;
}
bool CDriverTestInterface::GetButtonResetStatus()
{
	// 確認 Panel Reset 是否可以被按下
	bool bButtonReset = true;
	if( GetIOMonitorOpen() )
		bButtonReset = false;
	if( m.RemoteOutSet.BtnResetOn == 0 )
		bButtonReset = false;

	return bButtonReset;
}
bool CDriverTestInterface::GetButtonOneCycleStatus()
{
	// 確認 Panel OneCycle 是否可以被按下
	bool bButtonOneCycle = true;
	if( GetIOMonitorOpen() )
		bButtonOneCycle = false;
	if( m.RemoteOutSet.BtnOneCycleOn == 0 )
		bButtonOneCycle = false;

	return bButtonOneCycle;
}
bool CDriverTestInterface::GetNewLot()
{
	// 確認是否可以建立 New Lot
	bool bNewLotReady = false;

	return bNewLotReady;
}
bool CDriverTestInterface::GetLotDone()
{
	// 確認是否可以建立 Lot Done
	bool bLotDone = false;

	return bLotDone;
}
//
bool CDriverTestInterface::GetRemoteMode()
{
	return m_bRemoteMode;
}
void CDriverTestInterface::SetRemoteMode(bool bRemote)
{
	m_bRemoteMode = bRemote;
}
CDriverTestInterface::CDriverTestInterface()
{
	m_csSimBuffer						= _T("");

	// 1.0Ao
	// Remove this and re-build new one
	/*
	//
	m_RemoteTray.iCol					= -1;
	m_RemoteTray.iRow					= -1;
	m_RemoteTray.iTray					= -1;
	*/

	// 1.0Ao
	m_RemoteTray.iCol					= 0;
	m_RemoteTray.iRow					= 0;
	m_RemoteTray.iTray					= 0;

	//
	m_csLogPath							= _T("");

	//
	m_RemoteReturnCmd.csConnect			= _T("");
	m_RemoteReturnCmd.csDisconnect		= _T("");
	m_RemoteReturnCmd.csVersion			= _T("");

	//
	m_bRemoteMode						= false;
	hProcessWrite						= NULL;
	hProcessRead						= NULL;

	m_hComm								= NULL;

	csBuffer							= _T("");

	m_MachineStatus						= 0;
	m_MachineStatusCode					= 0;

	m_bInSocket							= false;
	m_bReturnError						= false;

	m_iBaudRate							= 0;

	// 1.0Ap
	hProcessExcute						= NULL;

	// 1.0Ao
	// TCP/IP
	hProcessWriteTCP					= NULL;
	hProcessReadTCP						= NULL;
	csTCPBuffer							= _T("");
	m_SendTCPCmd.RemoveAll();

	m_ReviceCmd.RemoveAll();
	m_SendCmd.RemoveAll();
}
// 取得資訊
void CDriverTestInterface::GetBaudRate(int &BaudRate)
{
	BaudRate = m_iBaudRate;
}

// 記錄通訊
void CDriverTestInterface::SetLogPath(CString csPath)
{
	m_csLogPath = csPath;
}
CString CDriverTestInterface::GetLogPath()
{
	return m_csLogPath;
}
static CMutex MutexLogRemoteRaw;
void CDriverTestInterface::LogRaw(CString csLog)
{
	if( m_csLogPath != "" )
	{		
		CSingleLock Lock(&MutexLogRemoteRaw);
		Lock.Lock();

		CString csFile = _T("");
		csFile = m_csLogPath + _RemoteRawLog;		
		CFile file;
		if( file.Open( csFile , CFile::modeCreate | CFile::modeWrite
			| CFile::modeNoTruncate | CFile::shareDenyNone, NULL) )
		{		
			CString cs = _T("");
			cs.Format("%s\r\n", csLog );

			file.SeekToEnd();		
			file.Write(cs.GetBuffer(0), cs.GetLength());
			file.Close();
		}		
		Lock.Unlock();
	}
}
static CMutex MutexLogRemoteCmd;
void CDriverTestInterface::Log(CString csLog)
{
	if( m_csLogPath != "" )
	{		
		CSingleLock Lock(&MutexLogRemoteCmd);
		Lock.Lock();		
		
		CString csFile = _T("");
		csFile = m_csLogPath + _RemoteLog;		
		CFile file;
		if( file.Open( csFile , CFile::modeCreate | CFile::modeWrite
			| CFile::modeNoTruncate | CFile::shareDenyNone, NULL) )
		{		
			CString cs = _T("");
			cs.Format("%s\r\n", csLog );

			file.SeekToEnd();
			file.Write(cs.GetBuffer(0), cs.GetLength());
			file.Close();
		}
		Lock.Unlock();		
	}
}

CDriverTestInterface::~CDriverTestInterface()
{
	CloseWrite();		TRACE("~CDriverTestInterface - CloseWrite\n");
	CloseRead();		TRACE("~CDriverTestInterface - CloseRead\n");
	Close();			TRACE("~CDriverTestInterface - CloseComPort\n");

	// 1.0Ao
	// TCP/IP
	CloseTCP();			TRACE("~CDriverTestInterface - TCP Communication\n");
	CloseReadTCP();		TRACE("~CDriverTestInterface - TCP Close Read\n");
	CloseWriteTCP();	TRACE("~CDriverTestInterface - TCP Close Write\n");

	// 1.Ap
	CloseExcute();		TRACE("~CDriverTestInterface - Close Excute\n");

	TRACE("~CDriverTestInterface\n");
}
CString CDriverTestInterface::GetHelpFile(CString &csHelpFile)
{
	// 取得 Help File 字串
	CString csGetHelpFile = _T("");

	CString csTempGetHelpFile = _T("");
	int iSize = m_RemoteCommandList.m_RemoteCommand.GetSize();
	int i = 0;
	for(i=0;i<iSize;i++)
	{
		csTempGetHelpFile.Format("%s", 
			m_RemoteCommandList.m_RemoteCommand.GetAt(i).m_csRemoteCommandName );
		csGetHelpFile.Insert(csGetHelpFile.GetLength(), csTempGetHelpFile);

		CString csBreak = _T("");
		if( i< (iSize-1) )
			csBreak.Format(",\r\n");

		csGetHelpFile.Insert(csGetHelpFile.GetLength(), csBreak);
	}

	csHelpFile = csGetHelpFile;

	return csGetHelpFile;
}
CString CDriverTestInterface::SetStatus(int iStatus, int iCode)
{
	// 設定 目前的狀態 (Remote)
	CString csSetStatus = _T("");

	m_MachineStatus		= iStatus;
	m_MachineStatusCode	= iCode;

	return csSetStatus;
}
CString CDriverTestInterface::GetStatus(int &iStatus, int &iCode)
{
	// 取得 目前的狀態 (Remote)
	CString csSetStatus = _T("");

	iStatus				= m_MachineStatus;
	iCode				= m_MachineStatusCode;

	return csSetStatus;
}
CString CDriverTestInterface::SetButtonInitial()
{
	// 設定 Button Initial
	CString csButtonInitial = _T("");
	m.PanelButton.BtnInitPushed = true;
	return csButtonInitial;
}

CString CDriverTestInterface::GetStatusContent()
{
	CString csGetStatusContent			= _T("");
	CString csGetStatusContentErrorCode = _T("");
	if( m_MachineStatusCode != 0 )
	{
		// Error
		bool bErrorCodeFind = false;
		for(int i=0; i<_Max_Error; i++)
		{
			csGetStatusContentErrorCode.Format("None");
			if(m.Msg[i].Code == m_MachineStatusCode )
			{
				csGetStatusContentErrorCode.Format("%s", m.Msg[i].Eng );
				bErrorCodeFind = true;
				i = _Max_Error;
			}
		}

		if( !bErrorCodeFind )
			csGetStatusContentErrorCode.Format("No Define");
	}
	else if( m_MachineStatusCode == 0 )
	{
		// OK
		csGetStatusContentErrorCode.Format("%s", _STOK );
	}

	csGetStatusContent.Format("%d,%d,%s", 
		m_MachineStatus, m_MachineStatusCode, csGetStatusContentErrorCode );
	return csGetStatusContent;
}
CString CDriverTestInterface::SetButtonStart()
{
	// 設定 Button Start
	CString csButtonStart = _T("");
	m.PanelButton.BtnStartPushed = true;
	return csButtonStart;
}
CString CDriverTestInterface::SetButtonStop()
{
	// 設定 Button Stop
	CString csButtonStop = _T("");
	m.PanelButton.BtnStopPushed = true;
	return csButtonStop;
}
CString CDriverTestInterface::SetButtonOneCycle()
{
	// 設定 Button OneCycle
	CString csButtonOneCycle = _T("");
	m.PanelButton.BtnOneCyclePushed = true;
	return csButtonOneCycle;
}
CString CDriverTestInterface::SetButtonRetry()
{
	// 設定 Button Retry
	CString csButtonRetry = _T("");
	m.PanelButton.BtnRetryPushed = true;
	return csButtonRetry;
}
CString CDriverTestInterface::SetButtonSkip()
{
	// 設定 Button Skip
	CString csButtonSkip = _T("");
	m.PanelButton.BtnSkipPushed = true;
	return csButtonSkip;
}
CString CDriverTestInterface::SetButtonReset()
{
	// 設定 Button Reset
	CString csButtonReset = _T("");
	m.PanelButton.BtnResetPushed = true;
	return csButtonReset;
}
CString CDriverTestInterface::SetRunMode(int iMode)
{
	CString csSetRunMode = _T("");
	m.Site.iRunMode = iMode;
	m.Page.Run.UpdateHandlerRunModeStatusInformation();	// updata run page run mode
	return csSetRunMode;
}
CString CDriverTestInterface::GetRunMode(int &iMode)
{
	CString csGetRunMode = _T("");
	iMode = m.Site.iRunMode;
	csGetRunMode.Format("%d", iMode);
	return csGetRunMode;
}
CString CDriverTestInterface::SetLotInfo(int iLotField, CString csInfo)
{
	// 設定 Lot Information
	CString csSetInfo = _T("");
	csInfo.TrimLeft(); csInfo.TrimRight();
	csSetInfo = csInfo;
	if( iLotField == enLotFieldLotNo )
	{
		if( m.LotInfo.LotInfoIsLotStart == 1 )
			m.LotInfo.LotInfoNo = csSetInfo;
		else
			m.LotInfo.OldLotInfoNo = csSetInfo;
	}
	else if( iLotField == enLotFieldMachineNo )
	{
		if( m.LotInfo.LotInfoIsLotStart == 1 )
			m.LotInfo.LotInfoMachineID = csSetInfo;
		else
			m.LotInfo.OldLotInfoMachineID = csSetInfo;
	}
	else if( iLotField == enLotFieldOperatorID )
	{	
		if( m.LotInfo.LotInfoIsLotStart == 1 )
			m.LotInfo.LotInfoOperator = csSetInfo;
		else
			m.LotInfo.OldLotInfoOperator = csSetInfo;
	}
	else if( iLotField == enLotFieldDeviceID )
	{	
		if( m.LotInfo.LotInfoIsLotStart == 1 )
			m.LotInfo.LotInfoDeviceID = csSetInfo;
		else
			m.LotInfo.OldLotInfoDeviceID = csSetInfo;
	}
	else if( iLotField == enLotFieldProgramID )
	{
		if( m.LotInfo.LotInfoIsLotStart == 1 )
			m.LotInfo.LotInfoProgramerID = csSetInfo;
		else
			m.LotInfo.OldLotInfoProgramerID = csSetInfo;
	}
	else
	{
	}

	return csSetInfo;
}
CString CDriverTestInterface::GetLotInfo(int iLotFiled, CString &csInfo)
{
	// 如果 Lot Start == 1, 則表示在運行中, 則如果要取得 Lot Information, 要送出現行的
	// 如果 Lot Start == 0, 則表示已結批, 則如果要取得 Lot Information, 要送出前一次的

	// 取得 Lot Information
	CString csGetInfo = _T("");
	if( iLotFiled == enLotFieldLotNo )
	{
		if( m.LotInfo.LotInfoIsLotStart == 1 )
			csInfo = m.LotInfo.LotInfoNo;
		else
			csInfo = m.LotInfo.OldLotInfoNo;
	}
	else if( iLotFiled == enLotFieldMachineNo )
	{	
		if( m.LotInfo.LotInfoIsLotStart == 1 )
			csInfo = m.LotInfo.LotInfoMachineID;
		else
			csInfo = m.LotInfo.OldLotInfoMachineID;
	}
	else if( iLotFiled == enLotFieldOperatorID )
	{	
		if( m.LotInfo.LotInfoIsLotStart == 1 )
			csInfo = m.LotInfo.LotInfoOperator;
		else
			csInfo = m.LotInfo.OldLotInfoOperator;
	}
	else if( iLotFiled == enLotFieldDeviceID )
	{	
		if( m.LotInfo.LotInfoIsLotStart == 1 )
			csInfo = m.LotInfo.LotInfoDeviceID;
		else
			csInfo = m.LotInfo.OldLotInfoDeviceID;
	}
	else if( iLotFiled == enLotFieldProgramID )
	{
		if( m.LotInfo.LotInfoIsLotStart == 1 )
			csInfo = m.LotInfo.LotInfoProgramerID;
		else
			csInfo = m.LotInfo.OldLotInfoProgramerID;
	}
	else
	{
	}

	return csGetInfo;
}
//
CString CDriverTestInterface::GetTempMaxMin(double &dMax, double &dMin )
{
	// 取得系統最高最低溫限制
	CString csGetTempMaxMin = _T("");

	dMax = _MaxHeaterTemp;
	dMin = _MinHeaterTemp;

	return csGetTempMaxMin;
}
CString CDriverTestInterface::GetTorqueMaxMin(double &dMax, double &dMin)
{
	CString csGetTorqueMaxMin = _T("");

	dMax = m.Setting.m_iTorqueHighLimit;
	dMin = m.Setting.m_iTorqueLowLimit;

	return csGetTorqueMaxMin;
}
CString CDriverTestInterface::GetProgramVersion()
{
	// 取得版本
	TCHAR szTemp[_MAX_PATH];
	TCHAR szVersion[16]; 
	CString csPorgramVersion = _T("");
	if (GetModuleFileName(NULL, szTemp, _MAX_PATH))
	{
		// CHROMA,3111,REV1,V0.1AJ
		f.MyGetVersion(szTemp, szVersion, sizeof(szVersion) / sizeof(szVersion[0]));
		_stprintf(szTemp, "CHROMA,3111,REV1,V%s", szVersion);
		
		csPorgramVersion.Format( "%s", szTemp );
	}

	return csPorgramVersion;
}
CString CDriverTestInterface::GetSiteSetTemp()
{
	// 取得溫度
	CString csGetSite = _T("");
	double dGetTemp = 0.0;

#ifdef _Demo
	dGetTemp = 62.2;
#else
	double dPV[_MaxWestDevice];
	double dSV[_MaxWestDevice];
	m.m_DriveWest.GetValue( dPV, dSV );

	int m_iDevID = m.m_HandlerComPort.iPortWestHeaterID;
	dGetTemp = dSV[m_iDevID];
#endif

	csGetSite.Format("%5.2f", dGetTemp );

	return csGetSite;
}
CString CDriverTestInterface::GetSiteTemp()
{	
	// 取得溫度
	CString csGetSite = _T("");
	double dGetTemp = 0.0;

#ifdef _Demo
	dGetTemp = 52.2;
#else
	double dPV[_MaxWestDevice];
	double dSV[_MaxWestDevice];
	m.m_DriveWest.GetValue( dPV, dSV );

	int m_iDevID = m.m_HandlerComPort.iPortWestHeaterID;
	dGetTemp = dPV[m_iDevID];
#endif

	csGetSite.Format("%5.2f", dGetTemp );

	return csGetSite;
}
CString CDriverTestInterface::SetSiteTemp(double dTemp)
{
	// 設定溫度
	CString csSetSiteTemp = _T("");

	int m_WestID = m.m_HandlerComPort.iPortWestHeaterID;
	m.m_DriveWest.AddCmd( m_WestID, enSV, dTemp );

	return csSetSiteTemp;
}
CString CDriverTestInterface::EnableTemp(bool bEnable)
{
	// 啟動溫度
	CString csEnableTemp = _T("");

	if( bEnable )
		m.RemoteOutSet.HeaterOn = true;
	else
		m.RemoteOutSet.HeaterOn = false;

	return csEnableTemp;
}
CString CDriverTestInterface::EnableRotator(bool bEnable)
{	
	// 設定是否使用 Rotator
	CString csEnableRotator = _T("");

	if( bEnable )
		m.m_TestSetting.m_RotatorUse = 1; // enable rotator
	else
		m.m_TestSetting.m_RotatorUse = 0; // no enable rotator

	return csEnableRotator;
}
CString CDriverTestInterface::EnableCCDLogIC(bool bEnable)
{
	// 設定啟動CCD記錄 IC
	CString csEnableCCDLogIC = _T("");

	if( bEnable )
		m.m_ArmLogICImage.bEnableArmLogICImage = 1; // enable arm log ic
	else
		m.m_ArmLogICImage.bEnableArmLogICImage = 0; // no enable arm log ic

	return csEnableCCDLogIC;
}
bool CDriverTestInterface::GetAirPressureEnable()
{
	// 取得是否啟動 電控比例閥
	bool bEnable = false;
	if( m.Setting.m_bEnableRemoteIO == 1 )
		bEnable = true;
	else
		bEnable = false;

	return bEnable;
}
CString CDriverTestInterface::SetAirPressure(double dAirPressure)
{
	// 設定 Air Pressure 數值
	CString csAirPressure = _T("");
	// dAirPressure

	double m_dSetTorque = dAirPressure;
	double m_dTorque = ( m_dSetTorque - m.m_TorqueToolSet.dbValue ) / m.m_TorqueToolSet.daValue;
	m_dTorque = m_dTorque * 20;

	m.m_TsFolatingParameter.iPogoTorqueForce = dAirPressure;
	theApp.m_tIORemote.SetTorqueValue(m_dTorque);

	return csAirPressure;
}
CString CDriverTestInterface::GetAirPressure(double &dAirPressure)
{
	// 取得 Air Pressure 數值
	CString csAirPressure = _T("");
	dAirPressure = 0.0;
	csAirPressure.Format("%d", m.m_TsFolatingParameter.iPogoTorqueForce );
	dAirPressure = atof(csAirPressure);	

	return csAirPressure;
}
CString CDriverTestInterface::SetRotator(int iDegree)
{
	// 設定 Rotator 角度
	CString csSetRotator = _T("");
/*
	// Rotator 模式
	enRotatorModeN				= 0,	// -90
	enRotatorModeP				= 1,	// +90
	enRotatorModeZ				= 2,	// 0
	enRotatorModeU				= 3,	// 180
*/
/*
	m_TestSetting.m_Angle = m_iAngle;	// 0 (-90)
	m_TestSetting.m_Angle = m_iAngle;	// 1 (+90)
	m_TestSetting.m_Angle = m_iAngle;	// 2 (0)
	m_TestSetting.m_Angle = m_iAngle;	// 3 (180)
*/
	m.m_TestSetting.m_Angle = iDegree;

	//
	return csSetRotator;
}
CString CDriverTestInterface::GetRotator(int &iDegree)
{
	// 設定 Rotator 角度
	CString csGetRotator = _T("");
/*
	// Rotator 模式
	enRotatorModeN				= 0,	// -90
	enRotatorModeP				= 1,	// +90
	enRotatorModeZ				= 2,	// 0
	enRotatorModeU				= 3,	// 180
*/
/*
	m_TestSetting.m_Angle = m_iAngle;	// 0 (-90)
	m_TestSetting.m_Angle = m_iAngle;	// 1 (+90)
	m_TestSetting.m_Angle = m_iAngle;	// 2 (0)
	m_TestSetting.m_Angle = m_iAngle;	// 3 (180)
*/
	iDegree = m.m_TestSetting.m_Angle;

	//
	return csGetRotator;
}
CString CDriverTestInterface::SetAutoSkip(bool bEnable)
{
	// 設定 AutoSkip 狀態
	CString csSetAutoSkip = _T("");

	if( bEnable )
		m.TraySkip.AutoSkip = 0;	// auto skip
	else
		m.TraySkip.AutoSkip = 1;	// no auto skip

	return csSetAutoSkip;
}
CString CDriverTestInterface::GetAutoSkip(bool &bEnable)
{
	// 取得 Auto Skip 狀態
	CString csSetAutoSkip = _T("");

	if( m.TraySkip.AutoSkip == 0 )
		bEnable = true;		// auto skip
	else
		bEnable = false;	// no auto skip
	//
	if( bEnable )
		csSetAutoSkip = "0";
	else
		csSetAutoSkip = "1";

	return csSetAutoSkip;
}
CString CDriverTestInterface::SetTsVacc(bool bEnable)
{
	// 設定 Test Site vacc 狀態
	CString csSetTsVacc = _T("");
	if( bEnable )
		m.TraySkip.TestSiteVacc = 1; // 不關掉
	else 
		m.TraySkip.TestSiteVacc = 0; // 關掉

	return csSetTsVacc;
}
CString CDriverTestInterface::GetTsVacc(bool &bEnable)
{
	// 取得 Test Site vacc 狀態
	CString csGetTsVacc = _T("");
	if( m.TraySkip.TestSiteVacc == 0 )
		bEnable = false;
	else
		bEnable = true;

	if( bEnable )
		csGetTsVacc = "1";
	else
		csGetTsVacc = "0";

	return csGetTsVacc;
}
CString CDriverTestInterface::GetTraySpec(int &iCol, int &iRow)
{
	// 取得 TraySpec
	CString csGetTraySpec = _T("");

	iCol = m.TraySpec.Column;
	iRow = m.TraySpec.Row;

	return csGetTraySpec;
}
void CDriverTestInterface::ClearRemoteTray()
{
	m_RemoteTray.iCol					= -1;
	m_RemoteTray.iRow					= -1;
	m_RemoteTray.iTray					= -1;
}
bool CDriverTestInterface::VerifyCoord(CString csCmd, tagRemoteCoord &t)
{
	t.iCol = -1;
	t.iRow = -1;
	t.iTray = -1;

	if( csCmd == "" )
		return false;

	char delim[]   = _CMTX;
	char *pch;

	CArray < CString, CString > m_Parameter;
	m_Parameter.RemoveAll();
	pch = strtok( csCmd.GetBuffer(0) ,delim);
	while (pch != NULL)
	{
		m_Parameter.Add( pch );
		pch = strtok (NULL, delim);
	}

	int iSize = m_Parameter.GetSize();
	if( iSize != 3 )
		return false;

	// Debug
	/*
	for(int i=0;i<iSize;i++)
	{
		CString cs = _T("");
		cs.Format("%s\n", m_Parameter.GetAt(i));
		TRACE( cs );
	}
	*/

	int iTray = atoi( m_Parameter.GetAt(0));	// tray
	int iCol  = atoi( m_Parameter.GetAt(1));	// col
	int iRow  = atoi( m_Parameter.GetAt(2));	// row

	if( iTray > 1 || iTray < 0 || 
		iCol < 0 ||	iCol > _MaxCol ||
		iRow < 0 || iRow > _MaxRow )
	{
		return false;
	}

	t.iCol = iCol;
	t.iRow = iRow;
	t.iTray = iTray;

	return true;;
}
void CDriverTestInterface::GetCurrentCoord(int &iTray, int &iCol, int &iRow)
{
	// 取得目前的 Coordnation
}
CString CDriverTestInterface::SetCoord(int iTray, int iX, int iY)			
{
	// 設定 Coordnation
	CString csSetCoord = _T("");

	return csSetCoord;
}
CString CDriverTestInterface::GetCoord(int &iTray, int &iX, int &iY)
{
	// 取得 Coordnation
	CString csGetCoord = _T("");

	return csGetCoord;
}
bool CDriverTestInterface::VerifyLotInfo(CString csCmd, tagRemoteLotInfo &lot)
{
	lot.csLotInfo = _T("");
	lot.iFiled = -1;

	if( csCmd == "" )
		return false;

	char delim[]   = _CMTX;
	char *pch;

	CArray < CString, CString > m_Parameter;
	m_Parameter.RemoveAll();
	pch = strtok( csCmd.GetBuffer(0) ,delim);
	while (pch != NULL)
	{
		m_Parameter.Add( pch );
		pch = strtok (NULL, delim);
	}

	int iSize = m_Parameter.GetSize();
	if( iSize != 2 )
		return false;

	lot.iFiled = atoi( m_Parameter.GetAt(0));
	lot.csLotInfo = m_Parameter.GetAt(1);

	//
	return true;
}
CString CDriverTestInterface::SetErrorMessage(int iCode, CString csMsg)
{
	// 設定 ErrorMessage (Code)
	CString csSetErrorMessage = _T("");
	CString csSendMessage = _T("");

#ifdef _Demo
#else
	if(m_hComm == NULL)
		return _T("");
#endif

#ifdef _Demo
	// 1.0Am
	if(!GetRemoteMode())
		return _T("");
#else
	if(!GetRemoteMode())
		return _T("");
#endif



	// 取得傳送命令
	GetSendCommand( enReturnErrMessage, csSendMessage, csMsg );

	// 把命令排入序列
	AddReplyCmd( csSendMessage );

	//
	return csSetErrorMessage;
}
CString CDriverTestInterface::SetStateInitialDone()
{
	CString csSetStateInitialDone = _T("");
	CString csSendMessage = _T("");

	// 取得傳送命令
	GetSendCommand( enReturnSetStateInitial, csSendMessage );

	// 把命令排入序列
	AddReplyCmd( csSendMessage );

	return csSetStateInitialDone;
}
CString CDriverTestInterface::SetStateRetryDone()
{
	// 設定 Retry Done
	CString csSetStateRetryDone = _T("");
	CString csSendMessage = _T("");

	// 取得傳送命令
	GetSendCommand( enReturnSetStateRetry, csSendMessage );

	// 把命令排入序列
	AddReplyCmd( csSendMessage );

	return csSetStateRetryDone;
}
CString CDriverTestInterface::SetStateSkipDone()
{
	// 設定 Skip Done
	CString csSetStateSkipDone = _T("");
	CString csSendMessage = _T("");

	// 取得傳送命令
	GetSendCommand( enReturnSetStateSkip, csSendMessage );

	// 把命令排入序列
	AddReplyCmd( csSendMessage );

	return csSetStateSkipDone;
}
CString CDriverTestInterface::SetStateStartDone()
{
	// 設定 Start Done
	CString csSetStateStartDone = _T("");
	CString csSendMessage = _T("");

	// 取得傳送命令
	GetSendCommand( enReturnSetStateStart, csSendMessage );

	// 把命令排入序列
	AddReplyCmd( csSendMessage );

	return csSetStateStartDone;
}
CString CDriverTestInterface::SetStateStopDone()
{
	// 設定 Stop Done
	CString csSetStateStopDone = _T("");
	CString csSendMessage = _T("");

	// 取得傳送命令
	GetSendCommand( enReturnSetStateStop, csSendMessage );

	// 把命令排入序列
	AddReplyCmd( csSendMessage );

	return csSetStateStopDone;
}
CString CDriverTestInterface::SetStateResetDone()
{
	// 設定 Reset Done
	CString csSetStateResetDone = _T("");
	CString csSendMessage = _T("");

	// 取得傳送命令
	GetSendCommand( enReturnSetStateReset, csSendMessage );

	// 把命令排入序列
	AddReplyCmd( csSendMessage );

	return csSetStateResetDone;
}
CString CDriverTestInterface::SetStateOneCycleDone()
{
	// 設定 OneCycle Done
	CString csSetStateOneCycleDone = _T("");
	CString csSendMessage = _T("");

	// 取得傳送命令
	GetSendCommand( enReturnSetStateOneCycle, csSendMessage );

	// 把命令排入序列
	AddReplyCmd( csSendMessage );

	return csSetStateOneCycleDone;
}
CString CDriverTestInterface::SetCoordnationReturnDone()
{
	CString csSetCoordnationReturnDone = _T("");
	CString csSendMessage = _T("");

	m_bInSocket = false;
	m_bReturnError = false;

	// 取得傳送命令
	GetSendCommand( enReturnSetCoordnationReturnDone, csSendMessage );

	// 把命令排入序列
	AddReplyCmd( csSendMessage );

	return csSetCoordnationReturnDone;
}
CString CDriverTestInterface::SetStateErrorCtrlDone()
{
	CString csSetInterfaceErrorCtrlDone = _T("");
	CString csSendMessage = _T("");

	// 取得傳送命令
	GetSendCommand( enReturnSetStateErrorCtrl, csSendMessage );

	// 把命令排入序列
	AddReplyCmd( csSendMessage );

	return csSetInterfaceErrorCtrlDone;
}
CString CDriverTestInterface::SetStateError()
{
	CString csError = _T("");
	CString csSendMessage = _T("");

	if( m_bInSocket )
		return csError;

	// 取得傳送命令
	GetSendCommand( enReturnSetError, csSendMessage );

	// 把命令排入序列
	AddReplyCmd( csSendMessage );

	return csError;
}
CString CDriverTestInterface::SetCoordnationDone()
{
	CString csSetCoordnationDone = _T("");
	CString csSendMessage = _T("");

	m_bInSocket = true;

	// 取得傳送命令
	GetSendCommand( enReturnSetCoordnationDone, csSendMessage );

	// 把命令排入序列
	AddReplyCmd( csSendMessage );

	return csSetCoordnationDone;
}

CString CDriverTestInterface::GetSystemStatus()
{
	// 取得系統狀態
	CString csGetSystemStatus = _T("");
	
	/*
	ERROR: Handler is paused by error.
	UNINITIAL: The handler is not ready for running.
	INITIALIZING: Handler is doing Homing now.
	ABORTING: Handler gets the PurgeDevices command from tester.
	READY: The handler is ready for run.
	CYCLE: The handler is in running mode. 
		The arm will pick up the device from Input Stack to Test Arm for testing until Input Stack empty.
	CYCLESTOP: The handler is paused when mode is in CYCLE.
	ONECYCLE: The handler is in running mode. 
		The arm stops picking the device from Input Stack and Pre-Heater Plate. 
		All of the devices in Shuttle, Test Arm will be tested and sort to Output Stack.
	ONECYCLESTOP: The handler is paused when mode is in ONECYCLE.
	OVERRIDE: The handler is in running mode. 
		The arm stops picking the device from input stack. 
		All of the devices in Pre-Heater Plate, Shuttle, 
		Test Arm will be tested and sort to Output Stack.
	OVERRIDESTOP: The handler is paused when mode is in OVERRIDE.
	DEMORUN: The handler is running without device. This function is for motion check only.
	DEMOSTOP: The handler is paused when it is in DEMO RUN mode.
	OFFLINERUN: The handler is running with device but skip test process.
	OFFLINESTOP: The handler is paused when it is in OFFLINERUN mode.
	*/

	if( m.Info.iStatus == theApp.enReady )
		csGetSystemStatus = "READY";
	else if( m.Info.iStatus == theApp.enInitial  )
		csGetSystemStatus = "INITIAL";
	else if( m.Info.iStatus == theApp.enUninitial )
		csGetSystemStatus = "UNINITIAL";
	else if( m.Info.iStatus == theApp.enCycle )
		csGetSystemStatus = "CYCLE";
	else if( m.Info.iStatus == theApp.enCycleStop )
		csGetSystemStatus = "CYCLESTOP";
	else if( m.Info.iStatus == theApp.enOneCycle )
		csGetSystemStatus = "ONECYCLE";
	else if( m.Info.iStatus == theApp.enOneCycleStop )
		csGetSystemStatus = "CYCLESTOP";
	else if( m.Info.iStatus == theApp.enOverride )
		csGetSystemStatus = "OVERRIDE";
	else if( m.Info.iStatus == theApp.enOverrideStop )
		csGetSystemStatus = "OVERRIDESTOP";
	else if( m.Info.iStatus == theApp.enManual )
		csGetSystemStatus = "READY";
	else if( m.Info.iStatus == theApp.enManualStop )
		csGetSystemStatus = "READY";
	else
		; // Nerver be here

	return csGetSystemStatus;
}
bool CDriverTestInterface::SetState(int iState)
{
	bool SetStateOK = false;
	if( iState == enSetStateInitial )
	{
		// Initial
		if( GetButtonInitialStatus() )
		{
			SetStateOK = true;
			SetButtonInitial();
		}
	}
	else if( iState == enSetStateStart )
	{
		// Start
		if( GetButtonStartStatus() )
		{
			SetStateOK = true;
			SetButtonStart();
		}
	}
	else if( iState == enSetStateStop )
	{
		// Stop
		if( GetButtonStopStatus() )
		{
			SetStateOK = true;
			SetButtonStop();
		}
	}
	else if( iState == enSetStateRetry )
	{
		// Retry
		if( GetButtonRetryStatus() )
		{
			SetStateOK = true;
			SetButtonRetry();
		}
	}
	else if( iState == enSetStateSkip )
	{
		// Skip
		if( GetButtonSkipStatus() )
		{
			SetStateOK = true;
			SetButtonSkip();
		}
	}
	else if( iState == enSetStateReset )
	{
		// Reset
		if( GetButtonResetStatus() )
		{
			SetStateOK = true;
			SetButtonReset();
		}
	}
	else if( iState == enSetStateOneCycle )
	{
		// One Cycle
		if( GetButtonOneCycleStatus() )
		{
			SetStateOK = true;
			SetButtonOneCycle();
		}	
	}
	else
	{
		
	}

	return SetStateOK;
}
//
bool CDriverTestInterface::GetLotCreate()
{
	// 確認是否有建立工單
	bool bLotReady = false;
	if( m.LotInfo.LotInfoIsLotStart == 1 )
		bLotReady = true;

	return bLotReady;
}
bool CDriverTestInterface::GetDoorStatus()
{
	// 確認是否門被開啟
	bool bDoorReady = false;
	if( m.InStatus.DoorSensor == _DoorNoClose && !m.Setting.m_bEnableDoorSensor )
		bDoorReady = false;	// door no close
	else
		bDoorReady = true;	// door close

	// Debug
//#ifdef _Demo
//	bDoorReady = false;
//#endif

	return bDoorReady;
}
bool CDriverTestInterface::GetEStopStatus()
{
	// 確認緊急停止鈕
	bool bEStopReady = false;
	if( m.InStatus.Emg == _EmgError )
		bEStopReady = false;
	else
		bEStopReady = true;

	// Debug
//#ifdef _Demo
//	bEStopReady = false;
//#endif

	return bEStopReady;
}
bool CDriverTestInterface::GetCoordnationReady()
{
	bool bCoordnationReady = false;
	if( m_RemoteTray.iCol == -1 || m_RemoteTray.iRow == -1 || m_RemoteTray.iTray == -1 )
		bCoordnationReady = false;
	else
		bCoordnationReady = true;

	return bCoordnationReady;
}
bool CDriverTestInterface::GetTrayFileMatchNow()
{
	// 確認最後一份 TrayFileSpec Match
	bool bTrayFileMatchReady = false;
	int iCol = -1;
	int iRow = -1;
	int iTray = -1;

	GetTraySpec( iCol, iRow );
	if( m_RemoteTray.iCol > (iCol-1) ||	m_RemoteTray.iCol < 0 ||
		m_RemoteTray.iRow > (iRow-1) || m_RemoteTray.iRow < 0 ||
		m_RemoteTray.iTray > 1 || m_RemoteTray.iTray < 0 )
	{
		bTrayFileMatchReady = false;
	}
	else
	{
		bTrayFileMatchReady = true;
	}

	return bTrayFileMatchReady;
}
bool CDriverTestInterface::GetSystemReady()
{
	// 確認系統準備好
	bool bSystemReady = false;
	if( m.Info.iStatus == theApp.enReady )
		bSystemReady = true;
	else
		bSystemReady = false;

	return bSystemReady;
}
bool CDriverTestInterface::GetSystemError()
{
	return m.Info.bError;
}
bool CDriverTestInterface::GetCoordnationGoStatusReady()
{
	bool bGetCoordnationGoStatus = false;
	bGetCoordnationGoStatus = theApp.m_tArm.GetRemoteCoordRequest();	// Get status from m_tArm thread
	return bGetCoordnationGoStatus;
}
// Mission
void CDriverTestInterface::RequestCoordnationMissionReturn()
{
	theApp.m_tInserter.SetRemoteCoordRequest( false );
}
void CDriverTestInterface::RequestCoordnationMissionClearGo()
{
	theApp.m_tArm.SetRemoteCoordClearRequest( true );
}
void CDriverTestInterface::RequestCoordnationMissionInitial()
{
	m_bInSocket = false;
	m_bReturnError = false;
}
void CDriverTestInterface::RequestCoordnationMissionGo()
{
	int iBooking = 0;
	int iTray = 0;

	//
	int iCol = 0;
	int iRow = 0;
	GetTraySpec(iCol, iRow);
	iBooking = ( m_RemoteTray.iRow * iCol ) + m_RemoteTray.iCol;
	iTray = m_RemoteTray.iTray;

	// Debug
	CString csMsg = _T("");
	csMsg.Format( "RequestCoordnationMissionGo >> Booking: %.3d, Tray: %.2d\n",
		iBooking, iTray );
	TRACE( csMsg );

	//
	theApp.m_tArm.SetRemoteCoordPosition( iBooking, iTray );
	theApp.m_tArm.SetRemoteCoordRequest( true );
	theApp.m_tInserter.SetRemoteCoordRequest( true );

	// Make sure the system be start
	f.ButtonStart();
}
//////////////////////////////////////////////////////////////////////////////
// Send Event
//
bool CDriverTestInterface::GetSendEventEnable()
{
	return m_bRemoteSendEvent;
}
void CDriverTestInterface::SetSendEventEnable(bool bEnable)
{
	m_bRemoteSendEvent = bEnable;
}
//////////////////////////////////////////////////////////////////////////////
// Remote Purge Device
bool CDriverTestInterface::GetRemotePurgeDevices()
{
	return m_bRemotePurgeDevices;
}
void CDriverTestInterface::SetRemotePurgeDevices(bool bPurgeDevices)
{
	m_bRemotePurgeDevices = bPurgeDevices;
}


CString CDriverTestInterface::CommandRun(tagTestProtocol telegram)
{
	CString csResult = _T("");
	
	if(telegram.cmd == "CONNECT")
	{
		csResult = ps.Connect();
		SetRemoteMode(true);
	}
	else if(telegram.cmd == "DISCONNET")
	{
		csResult = ps.Disconnect();
		SetRemoteMode(false);
	}
	else if(telegram.cmd == "GETVERSION")
	{
		csResult = ps.GetVersion();
	}
	else if(telegram.cmd == "LOADSETUP")
	{
		csResult = ps.LoadSetup(telegram.parameter);
	}
	else if(telegram.cmd == "SAVESETUP")
	{
		//	csResult = ps.SaveSetup(telegram.parameter);
	}
	else if(telegram.cmd == "START")
	{
		csResult = ps.Start();
	}
	else if(telegram.cmd == "STOP")
	{
		csResult = ps.Stop();
	}
	else if(telegram.cmd == "RETRY")
	{
		csResult = ps.Retry();
	}
	else if(telegram.cmd == "SKIP")
	{
		csResult = ps.Skip();
	}
	else if(telegram.cmd == "TRAYCHANGE")
	{
		csResult = ps.TrayChange(); //無功能
	}
	else if(telegram.cmd == "STACKUNLOAD")
	{
		csResult = ps.StackUnload(); //無功能
	}
	else if(telegram.cmd == "RESET")
	{
		csResult = ps.Reset();
	}
	else if(telegram.cmd == "INITIAL")
	{
		csResult = ps.Initial();
	}
	else if(telegram.cmd == "ONECYCLE")
	{
		csResult = ps.OneCycle();
	}
	else if(telegram.cmd == "SETTESTRESULT")
	{
		csResult = ps.SetTestResult(telegram.parameter, true);
	}
	else if(telegram.cmd == "RETEST")
	{
		csResult = ps.Retest();
	}
	else if(telegram.cmd == "PURGEDEVICES")
	{
		csResult = ps.PurgeDevices();
	}
	else if(telegram.cmd == "AUTOSKIP")
	{
		csResult = ps.AutoSkip();
	}
	else if(telegram.cmd == "SENDEVENTENABLE")
	{	
		bool bEnableEvent = false;
		int iEnableEvent = atoi(telegram.parameter);
		if(iEnableEvent == 1)
			bEnableEvent = true;
		else
			bEnableEvent = false;

		SetSendEventEnable(bEnableEvent);
		csResult = ps.SendEventEnable();
	}
	else if(telegram.cmd == "GETRUNMODE")
	{
		csResult = ps.GetRunMode();
	}
	else if(telegram.cmd == "SETRUNMODE")
	{
	
		csResult = ps.SetRunMode(telegram.parameter);
	}
	else if(telegram.cmd == "GETTIMEOUT")
	{
		csResult = ps.GetTimeOut();
	}
	else if(telegram.cmd == "SETTIMEOUT")
	{
		//csResult = ps.SetTimeOut();
	}
	else if(telegram.cmd == "GETSITETEMP")
	{
		csResult = ps.GetSiteTemp();
	}
	else if(telegram.cmd == "SETSITETEMP")
	{
		csResult = ps.SetSiteTemp(telegram.parameter);
	}
	else if(telegram.cmd == "GETSITESETTEMP")
	{
		csResult = ps.GetSiteSetTemp();
	}
	else if(telegram.cmd == "GETSTATUS")
	{
		csResult = ps.GetStatus();
	}
	else if(telegram.cmd == "GETSITESTATUS")
	{
		csResult = ps.GetSiteStatus();
	}
	else if(telegram.cmd == "SENDEVENT")
	{
		csResult = ps.SendEvent();
	}
	else if(telegram.cmd == "ERRORMESSAGE")
	{
	
		csResult = ps.ErrorMessage();
	}
	else if(telegram.cmd == "LOCATION")
	{
		csResult = ps.Location();
	}
	else if(telegram.cmd == "TESTEVENT")
	{
		csResult = ps.TestEvent();
	}
	return csResult;
}
