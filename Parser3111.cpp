// Parser3111.cpp: implementation of the CParser3111 class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "deer.h"
#include "Parser3111.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CParser3111::CParser3111()
{

}

CParser3111::~CParser3111()
{

}

CString CParser3111::Connect()
{
	CString csResult = _T("");
	csResult.Format("<<*%%CONNECT%%%s>>","3111;" + m.UI.MachineID);
	return csResult;
}


CString CParser3111::GetVersion()
{
	CString csResult = _T("");
	TCHAR szTemp[_MAX_PATH];
	TCHAR szVersion[16]; 
	if (GetModuleFileName(NULL, szTemp, _MAX_PATH))
	{
		// 利用取得的 exe 檔案的路徑名稱來取得它的版本
		f.MyGetVersion(szTemp, szVersion, sizeof(szVersion) / sizeof(szVersion[0]));
		_stprintf(szTemp, "3111 V%s", szVersion);
	}
	csResult.Format("<<*%%GETVERSION%%%s>>",szTemp);
	return csResult;
}


CString CParser3111::Disconnect()
{
	CString csResult = _T("");
	csResult.Format("<<*%%DISCONNECT%%BYE>>");
	return csResult;
}


CString CParser3111::LoadSetup(CString msg)
{
	CString csResult = _T("");
	//取出副檔名 (.Tray, .Offset )	
	CString csFile = msg;
	csFile.MakeUpper();
	if(csFile.Find(".TRAY"))
	{
		csFile = m.FilePath.TrayFilesPath + msg;
		CFileFind find;
		if(find.FindFile(csFile))
		{
			m.UI.FileMain = msg;
			f.LoadTraySpec();
			csResult.Format("<<*%%LOADSETUP%%ACK>>");
			return csResult;
		}
		csResult.Format("<<*%%LOADSETUP%%NAK:File not found>>");
		return csResult;
	}
	else if(csFile.Find(".OFFSET"))
	{
		msg.MakeUpper();
		msg.Replace(".OFFSET", ".TRAY");
		csFile = m.FilePath.TrayFilesPath + msg;
		CFileFind find;
		if(find.FindFile(csFile))
		{
			m.UI.FileMain = msg;
			f.LoadOffset();
			csResult.Format("<<*%%LOADSETUP%%ACK>>");
			return csResult;
		}
		csResult.Format("<<*%%LOADSETUP%%NAK:File not found>>");
		return csResult;
	}

	csResult.Format("<<*%%LOADSETUP%%NAK:File extension incorrect>>");
	return csResult;
}

CString CParser3111::SaveSetup(CString msg)
{
	CString csResult = _T("");
	//將數值寫到檔案中
	f.SaveTimer();
	f.SaveSpeed();
	f.SaveOffset();
	csResult.Format("<<*%%SAVESETUP%%ACK>>");
	return csResult;
}

CString CParser3111::Start()
{
	CString csResult = _T("");
	if(m.m_TestInterface.GetButtonOneCycleStatus() && !m.m_TestInterface.GetButtonStartStatus())
	{
		m.PanelButton.BtnOneCyclePushed = false;
		m.RemoteOutSet.BtnOneCycleOn = false;
		f.ButtonOneCycle();
		csResult.Format("<<*%%START%%ONECYCLE>>");
		return csResult;
	}
	
	if(m.m_TestInterface.GetButtonStartStatus())
	{
		m.PanelButton.BtnStartPushed = false;
		m.RemoteOutSet.BtnStartOn = false;
		f.ButtonStart();
		csResult.Format("<<*%%START%%CYCLE>>");
		return csResult;
	}
	
	if(m.m_TestInterface.GetButtonInitialStatus())
	{
		m.PanelButton.BtnInitPushed = false;
		m.RemoteOutSet.BtnInitialOn = false;
		f.ButtonInitial();
		csResult.Format("<<*%%START%%INITIAL>>");
		return csResult;
	}
	
	csResult.Format("<<*%%START%%NAK>>");
	return csResult;
}

CString CParser3111::Stop()
{
	CString csResult = _T("");
	if(m.m_TestInterface.GetButtonStopStatus())
	{
		m.PanelButton.BtnStopPushed = false;
		m.RemoteOutSet.BtnStopOn = false;
		f.ButtonStop();
		csResult.Format("<<*%%STOP%%ACK>>");
		return csResult;
	}
	return csResult;
}

CString CParser3111::Retry()
{
	CString csResult = _T("");
	if(m.m_TestInterface.GetButtonRetryStatus())
	{
		m.PanelButton.BtnRetryPushed = false;
		m.RemoteOutSet.BtnRetryOn = false;
		f.ButtonRetry();
		csResult.Format("<<*%%RETRY%%ACK>>");
		return csResult;
	}
	csResult.Format("<<*%%RETRY%%NAK>>");
	return csResult;
}

CString CParser3111::Skip()
{
	CString csResult = _T("");
	if(m.m_TestInterface.GetButtonSkipStatus())
	{
		m.PanelButton.BtnSkipPushed = false;
		m.RemoteOutSet.BtnSkipOn = false;
		f.ButtonSkip();
		csResult.Format("<<*%%SKIP%%ACK>>");
		return csResult;
	}
	csResult.Format("<<*%%SKIP%%NAK>>");
	return csResult;
}

CString CParser3111::TrayChange()
{
	CString csResult = _T("");//無功能
		return csResult;
}

CString CParser3111::StackUnload()
{
	CString csResult = _T("");//無功能
		return csResult;
}

CString CParser3111::Reset()
{
	CString csResult = _T("");
	if(m.m_TestInterface.GetButtonResetStatus())
	{
		m.PanelButton.BtnResetPushed = false;
		m.RemoteOutSet.BtnResetOn = false;
		f.ButtonReset();
		csResult.Format("<<*%%RESET%%ACK>>");
		return csResult;
	}
	csResult.Format("<<*%%RESET%%NAK>>");
		return csResult;
}

CString CParser3111::Initial()
{
	CString csResult = _T("");
	if(m.m_TestInterface.GetButtonInitialStatus())
	{
		m.PanelButton.BtnInitPushed = false;
		m.RemoteOutSet.BtnInitialOn = false;
		f.ButtonInitial();
		csResult.Format("<<*%%INITIAL%%ACK>>");
		return csResult;
	}
	csResult.Format("<<*%%INITIAL%%NAK>>");
	return csResult;
}

CString CParser3111::OneCycle()
{
	CString csResult = _T("");
	if(m.m_TestInterface.GetButtonOneCycleStatus())
	{
		m.PanelButton.BtnOneCyclePushed = false;
		m.RemoteOutSet.BtnOneCycleOn = false;
		f.ButtonOneCycle();
		csResult.Format("<<*%%ONECYCLE%%ACK>>");
		return csResult;
	}
	csResult.Format("<<*%%ONECYCLE%%NAK>>");
	return csResult;
}

CString CParser3111::SetTestResult(CString msg)
{
	CString csResult = _T("");
	m.m_RemoteTestResult = msg;
	return csResult;
}
void CParser3111::GetTestResult(CString &msg)
{
	CString csResult = _T("");
	msg = m.m_RemoteTestResult;

}
CString CParser3111::Retest(CString count)
{
	CString csResult = _T("");
	if(count == "*" || count == "")//沒有命令 預設 1 次
		m.m_TestInterface.m_bRemoteRetest = 1;
	else
		m.m_TestInterface.m_bRemoteRetest = atoi(count);
	csResult.Format("<<*%%RETEST%%ACK>>");
	//更改 Reset Flag
	return csResult;
}

CString CParser3111::PurgeDevices()
{
	CString csResult = _T("");
	if(!m.m_TestInterface.m_bRemotePurgeDevices)
	{
		csResult.Format("<<*%%AUTOSKIP%%ACK>>");
		//強制OneCycle
		f.ButtonOneCycle();
	}
	else
		csResult.Format("<<*%%AUTOSKIP%%NAK>>");
	return csResult;
}

CString CParser3111::AutoSkip(bool enable)
{
	CString csResult = _T("");
	if(enable == 1)
	{
		csResult.Format("<<*%%AUTOSKIP%%ACK;1>>");
		m.TraySkip.AutoSkip = 1;
		return csResult;
	}
	else
		csResult.Format("<<*%%AUTOSKIP%%NAK;0>>");
		m.TraySkip.AutoSkip = 0;
		return csResult;
	
}

CString CParser3111::SendEventEnable(bool Enable)
{
	CString csResult = _T("");
	if(Enable)
	{
		m.m_TestInterface.m_bRemoteSendEvent = true;
		csResult.Format("<<*%%SENDEVENTENABLE%%ACK;1>>");
	}
	else
	{
		m.m_TestInterface.m_bRemoteSendEvent = false;
		csResult.Format("<<*%%SENDEVENTENABLE%%NAK;0>>");
	}
	return csResult;
}

CString CParser3111::GetRunMode()
{
	CString csResult = _T("");
	if(m.Site.iRunMode == theApp.enOnLine)
	{
		csResult.Format("<<*%%GETRUNMODE%%ONLINE>>");
		return csResult;
	}
	else if(m.Site.iRunMode == theApp.enOffLine)
	{
		csResult.Format("<<*%%GETRUNMODE%%OFFLINE>>");
		return csResult;
	}
	else if(m.Site.iRunMode == theApp.enDemo)
		csResult.Format("<<*%%GETRUNMODE%%DEMO>>");
	return csResult;
	
}

CString CParser3111::SetRunMode(CString mode)
{
	CString csResult = _T("");
	mode.MakeUpper();
	if(mode == "ONLINE")
	{
		csResult.Format("<<*%%SETRUNMODE%%ACK>>");
		m.Site.iRunMode = theApp.enOnLine;
		return csResult;
	}
	else if(mode == "OFFLINE")
	{
		csResult.Format("<<*%%SETRUNMODE%%ACK>>");
		m.Site.iRunMode = theApp.enOffLine;
		return csResult;
	}
	else if(mode == "DEMO")
	{
		csResult.Format("<<*%%SETRUNMODE%%ACK>>");
		m.Site.iRunMode = theApp.enDemo;
		return csResult;
	}
	else
		csResult.Format("<<*%%SETRUNMODE%%NAK>>");
	return csResult;
}

CString CParser3111::GetTimeOut()
{
	CString csResult = _T("");
	if(m.m_TestSetting.m_TestType == theApp.enRS232)
	{
		csResult.Format("<<*%%GETTIMEOUT%%%.2f>>",m.m_InterfaceSetting.m_dCmdTimeout);
		return csResult;
	}
	else if( m.m_TestSetting.m_TestType == theApp.enTCP )
	{
		csResult.Format("<<*%%GETTIMEOUT%%%.2f>>",m.m_TcpipInterfaceSetting.m_dCmdTimeout);
		return csResult;		
	}
	else if( m.m_TestSetting.m_TestType == theApp.enTTL )	// 在這裡處理 TTL 的通訊
	{
		return csResult;
	}
	else if( m.m_TestSetting.m_TestType == theApp.enGPIB )
	{
		return csResult;
	}
	return csResult;
}

CString CParser3111::SetTimeOut(CString time)
{
	CString csResult = _T("");
	double dTimeOut =  atof(time);
	if(m.m_TestSetting.m_TestType == theApp.enRS232)
	{
		m.m_InterfaceSetting.m_dCmdTimeout = dTimeOut;
		csResult.Format("<<*%%SETTIMEOUT%%ACK>>");
		return csResult;
	}
	else if( m.m_TestSetting.m_TestType == theApp.enTCP )
	{	
		m.m_TcpipInterfaceSetting.m_dCmdTimeout = dTimeOut;	
		csResult.Format("<<*%%SETTIMEOUT%%ACK>>");
		return csResult;		
	}
	else if( m.m_TestSetting.m_TestType == theApp.enTTL )	// 在這裡處理 TTL 的通訊
	{
		return csResult;
	}
	else if( m.m_TestSetting.m_TestType == theApp.enGPIB )
	{
		return csResult;
	}
	csResult.Format("<<*%%SETTIMEOUT%%NAK>>");
	return csResult;
}

CString CParser3111::GetSiteTemp()
{
	CString csResult = _T("");
	double dPV[_MaxWestDevice];
	double dSV[_MaxWestDevice];
	m.m_DriveWest.GetValue( dPV, dSV );
	csResult.Format("<<*%%GETSITETEMP%%%.2f>>",dPV[m.m_HandlerComPort.iPortWestHeaterID]);
	return csResult;
}

CString CParser3111::SetSiteTemp(CString Temper)
{
	CString csResult = _T("");
	double dTemper = atof(Temper);	
	m.m_DriveWest.AddCmd( m.m_HandlerComPort.iPortWestHeaterID, enSV, dTemper);
	csResult.Format("<<*%%SETSITETEMP%%%.2f>>",dTemper);
	return csResult;
}

CString CParser3111::GetSiteSetTemp()
{
	CString csResult = _T("");
	double dPV[_MaxWestDevice];
	double dSV[_MaxWestDevice];
	m.m_DriveWest.GetValue( dPV, dSV );
	csResult.Format("<<*%%SETSITESETTEMP%%%.2f>>",dSV[m.m_HandlerComPort.iPortWestHeaterID]);
	return csResult;
}

CString CParser3111::GetStatus()
{
	CString csResult = _T("");
	int iStatus = m.Info.iStatus;
	switch(m.Info.iStatus)
	{
	case theApp.enCycle:
		csResult.Format("<<*%%GETSTATUS%%CYCLE>>");
		break;
	case theApp.enCycleStop:
		csResult.Format("<<*%%GETSTATUS%%CYCLESTOP>>");
		break;
	case theApp.enOneCycle:
		csResult.Format("<<*%%GETSTATUS%%ONECYCLE>>");
		break;
	case theApp.enOneCycleStop:
		csResult.Format("<<*%%GETSTATUS%%CYCLESTOP>>");
		break;
	case theApp.enOverride:
		csResult.Format("<<*%%GETSTATUS%%OVERRIDE>>");
		break;
	case theApp.enOverrideStop:
		csResult.Format("<<*%%GETSTATUS%%OVERRIDESTOP>>");
		break;
	case theApp.enManual:
		csResult.Format("<<*%%GETSTATUS%%MAUNAL>>");
		break;
	case theApp.enManualStop:
		csResult.Format("<<*%%GETSTATUS%%MAUNALSTOP>>");
		break;
	case theApp.enDemoRun:
		csResult.Format("<<*%%GETSTATUS%%DEMORUN>>");
		break;
	case theApp.enDemoStop:
		csResult.Format("<<*%%GETSTATUS%%DEMOSTOP>>");
		break;
	case theApp.enOfflineRun:
		csResult.Format("<<*%%GETSTATUS%%OFFLINERUN>>");
		break;
	case theApp.enOfflineStop:
		csResult.Format("<<*%%GETSTATUS%%OFFLINESTOP>>");
		break;
	case theApp.enUninitial:
		csResult.Format("<<*%%GETSTATUS%%UNINITIAL>>");
		break;
	case theApp.enReady:
		csResult.Format("<<*%%GETSTATUS%%READY>>");
		break;
	case theApp.enError:
		csResult.Format("<<*%%GETSTATUS%%ERROR>>");
		break;
	case theApp.enInitial:
		csResult.Format("<<*%%GETSTATUS%%INITIAL>>");
		break;
	case theApp.enAbotring:
		csResult.Format("<<*%%GETSTATUS%%ABORTING>>");
		break;
	case theApp.enWaitTempStable:
		csResult.Format("<<*%%GETSTATUS%%WAITTEMPSTABLE>>");
		break;
	default:
		csResult.Format("<<*%%GETSTATUS%%STOP>>");
		break;
	}
	return csResult;
}

CString CParser3111::GetSiteStatus()
{
	CString csResult = _T("");
	//狀態轉字串
	if(theApp.m_tInserter.m_lRemoteStatus == enError)
		csResult.Format("<<*%%GETSITESTATUS%%ERROR>>");
	else if(theApp.m_tInserter.m_lRemoteStatus == enManual)
		csResult.Format("<<*%%GETSITESTATUS%%MANUAL>>");
	else if(theApp.m_tInserter.m_lRemoteStatus == enTesting)
		csResult.Format("<<*%%GETSITESTATUS%%TESTING>>");
	else if(theApp.m_tInserter.m_lRemoteStatus == enDeviceInTestsite)
		csResult.Format("<<*%%GETSITESTATUS%%DEVICEINTESTSITE>>");
	else if(theApp.m_tInserter.m_lRemoteStatus == enDeviceInSocket)
		csResult.Format("<<*%%GETSITESTATUS%%DEVICEINSOCKET>>");
	else if(theApp.m_tInserter.m_lRemoteStatus == enDeviceOutSocket)
		csResult.Format("<<*%%GETSITESTATUS%%DEVICEOUTSOCKET>>");
	else if(theApp.m_tInserter.m_lRemoteStatus == enNoDevice)
		csResult.Format("<<*%%GETSITESTATUS%%NODEVICE>>");
	return csResult;
}
void CParser3111::TestEvent()
{
	CString csResult = _T("");
	m.m_RemoteTestEvent = enSOT;
	f.RemoteSendTestEvent(m.m_RemoteTestEvent);

}
