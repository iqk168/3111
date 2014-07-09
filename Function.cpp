// Function.cpp: implementation of the CFunction class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "deer.h"

// dlg for initial
#include "deerDlg.h"

#include "Member.h"
#include "Function.h"

// Motor Lib
#include "MC8141P.h"

#include "DlgLotInformation.h"

#include <map>
#include <vector>

// File Path
#include "Shlwapi.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CFunction::CFunction()
{
	
}

CFunction::~CFunction()
{

}
void CFunction::ClearUPHAllData()
{
	ClearUPHTSData();

	//
	f.UPHMessageForClear();
}
static CMutex UPHMutexLog;
void CFunction::ExportUPHLog(int item, double dTime)
{
	CSingleLock Lock(&UPHMutexLog);
	Lock.Lock();
	
	CString cs = _T("");
	CString cstime;
	CTime time = CTime::GetCurrentTime();
	cs.Format("%d, %5.2f\r\n", item, dTime);
	cstime.Format("%s",time.Format("%y-%m-%d"));
	
	CFile file;

	file.Open(".\\Log\\UPH_"+cstime+".txt", CFile::modeCreate | CFile::modeWrite
		| CFile::modeNoTruncate | CFile::shareDenyNone, NULL);
	
	file.SeekToEnd();
	
	file.Write(cs.GetBuffer(0), cs.GetLength());
	file.Close();
	
	Lock.Unlock();	
}
void CFunction::ClearUPHTSData()
{
	m.m_UPHData.m_TSCalc.RemoveAll();
}
// System Control
void CFunction::ThreadWait()
{
	Sleep(_Wait);

    MSG msg;
	if(::PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE))
		theApp.PumpMessage();
}
// West Lookup Table
void CFunction::GetWestLoopupTableTemperature(CString csSV, CString csProt, double &dOffset )
{
	CString csFile = _T("");
	csFile = m.FilePath.HeaterTempLkPath;
	GetSetting( csFile, csProt, csSV,  dOffset );
}
void CFunction::SetWestLoopupTableTemperature(CString csSV, CString csProt, CString csOffset)
{
	CString csFile = _T("");
	csFile = m.FilePath.HeaterTempLkPath;
	SaveSetting( csFile, csProt, csSV, csOffset);
}
void CFunction::DeleteWestLoopupTableTemperatureAll(CString csProt)
{	
	CString csFile = _T("");
	csFile = m.FilePath.HeaterTempLkPath;

	::WritePrivateProfileString(csProt,NULL,NULL,csFile);
	// Delete Section
}
void CFunction::DeleteWestLoopupTableTemperature(CString csSV, CString csProt, double &dOffset )
{
	CString csFile = _T("");
	csFile = m.FilePath.HeaterTempLkPath;
	DeleteSetting( csFile, csProt, csSV,  dOffset );
}
// dBase
void CFunction::DeleteErrorCode(int Code)
{
	CString csSQL = _T("");
	csSQL.Format( "DELETE FROM ErrorCodeLibrary WHERE CODE = %d", Code );
	_RecordsetPtr r = m.DB.ErrorCode.RAGetDisconnectedRs( csSQL );

	// After Delete. We must reload mdb. for updata error code array
	LoadErrorCode();	// Load ErrorCode
}
void CFunction::OpenDatabase()
{
	// Opne Language
	if(S_OK != m.DB.Language.RAConnect("Driver={Microsoft Access Driver (*.mdb)};"
			"Initial Catalog=" + m.FilePath.SystemPath + "Language.mdb"))
	{
		CString csMsg = _T("");
		csMsg = "Language Database Open Error";
		if( m.Setting.m_bEnableProgramInitialStart == 1 )
			f.DMsg.DMsg( csMsg + _DMsgMark, false );
		else
			AfxMessageBox( csMsg );
	}
	else
	{
		CString csMsg = _T("");
		csMsg = "Language Database Open Success";
		f.DMsg.DMsg( csMsg );
	}

	// Open Error Code
	if(S_OK != m.DB.ErrorCode.RAConnect("Driver={Microsoft Access Driver (*.mdb)};"
		"Initial Catalog=" + m.FilePath.SystemPath + "ErrorCode.mdb"))
	{
		CString csMsg = _T("");
		csMsg = "ErrorCode Database Open Error";
		if( m.Setting.m_bEnableProgramInitialStart == 1 )
			f.DMsg.DMsg( csMsg + _DMsgMark, false );
		else
			AfxMessageBox( csMsg );
	}
	else
	{
		CString csMsg = _T("");
		csMsg = "ErrorCode Database Open Success";
		f.DMsg.DMsg( csMsg );
	}
}
void CFunction::LoadErrorCode()
{
	m.LoadDatabase.bErrorCode = false;

	_RecordsetPtr r = m.DB.ErrorCode.RAGetDisconnectedRs("SELECT * FROM ErrorCodeLibrary");

	if(r)
	{
		int i=0;
		while(!r->adoEOF)
		{

			m.LoadDatabase.bErrorCode = true;
			m.DB.ErrorCode.GetFieldValue(r, "Code", m.Msg[i].Code);					// 0
			m.DB.ErrorCode.GetFieldValue(r, "Eng", m.Msg[i].Eng);					// 1
			m.DB.ErrorCode.GetFieldValue(r, "Chi", m.Msg[i].Chi);					// 2
			m.DB.ErrorCode.GetFieldValue(r, "x", m.Msg[i].p.x);						// 3
			m.DB.ErrorCode.GetFieldValue(r, "y", m.Msg[i].p.y);						// 4
			m.DB.ErrorCode.GetFieldValue(r, "Level", m.Msg[i].Level);				// 5
			m.DB.ErrorCode.GetFieldValue(r, "Alarm", m.Msg[i].Alarm);				// 6

			m.DB.ErrorCode.GetFieldValue(r, "InitialNeed", m.Msg[i].InitialNeed);	// 7
			m.DB.ErrorCode.GetFieldValue(r, "EngProcess", m.Msg[i].EngProcess);		// 8
			m.DB.ErrorCode.GetFieldValue(r, "ChiProcess", m.Msg[i].ChiProcess);		// 9
			m.DB.ErrorCode.GetFieldValue(r, "Stop", m.Msg[i].Stop);					// 10

			/// Enable / Disable Button.
//			m.DB.ErrorCode.GetFieldValue(r, "BReset",			m.Msg[i].BReset );
			m.DB.ErrorCode.GetFieldValue(r, "BStart",			m.Msg[i].BStart);
			m.DB.ErrorCode.GetFieldValue(r, "BStop",			m.Msg[i].BStop);
			m.DB.ErrorCode.GetFieldValue(r, "BRetry",			m.Msg[i].BRetry);
			m.DB.ErrorCode.GetFieldValue(r, "BSkip",			m.Msg[i].BSkip);
			m.DB.ErrorCode.GetFieldValue(r, "BTrayChange",		m.Msg[i].BTrayChange);
			m.DB.ErrorCode.GetFieldValue(r, "BInitial",			m.Msg[i].BInitial);
			m.DB.ErrorCode.GetFieldValue(r, "BOneCycle",		m.Msg[i].BOneCycle );
			m.DB.ErrorCode.GetFieldValue(r, "BOverride",		m.Msg[i].BOverride );
			m.DB.ErrorCode.GetFieldValue(r, "BTestSiteSkip",	m.Msg[i].BTestSiteSkip );
			//

			i++;
			r->MoveNext();
		}
		m.Msg[i].Code = -1;
	}
}
void CFunction::LoadLanguage()
{
	_RecordsetPtr r = m.DB.Language.RAGetDisconnectedRs("SELECT * FROM Language");
	if (r)
	{
		int i=0;
		while (!r->adoEOF)
		{
			m.DB.Language.GetFieldValue(r, "English", m.Language.eng[i]);

//			m.DB.Language.GetFieldValue(r, "Chinese", m.Language.chi[i]);
			// 支援簡體中文
			// 如果在 Debug 有打勾. 那載入中文就載入簡體中文
			if( m.Setting.m_bEnableSimplified == 1 )
				m.DB.Language.GetFieldValue(r, "SChinese", m.Language.chi[i]);
			else
				m.DB.Language.GetFieldValue(r, "Chinese", m.Language.chi[i]);

			i++;
			r->MoveNext();
		}
		m.Language.count = i;
	}
}

void CFunction::ChangeLanguage(HWND wnd)
{
	HWND pWnd;

	CString csValue;
	pWnd = ::FindWindowEx(wnd, NULL, NULL, NULL);
	while(pWnd != NULL)
	{
		char cBuffer[200] = {0};
		::GetWindowText(pWnd, cBuffer, 200);
		csValue = cBuffer;
		csValue.TrimLeft(); csValue.TrimRight();

		if(csValue == _T(""))
		{
			pWnd = ::FindWindowEx(wnd, pWnd, NULL, NULL);
			continue;
		}

		for(int i=0; i<m.Language.count; i++)
		{
			if(m.UI.Language == m.enEnglish)
			{
				if(csValue == m.Language.chi[i])
				{
					csValue = m.Language.eng[i];
					break;
				}
			}
			else
			{
				if(csValue == m.Language.eng[i])
				{
					csValue = m.Language.chi[i];
					break;
				}
			}
		}
		if(i<m.Language.count)
			::SetWindowText(pWnd, csValue);

		pWnd = ::FindWindowEx(wnd, pWnd, NULL, NULL);
	}
	CWnd *p = CWnd::FromHandle(wnd);
	p->Invalidate();
}

tagErrorMsg CFunction::GetErrorMsg(long Code)
{
	for(int i=0; i<_Max_Error; i++)
	{
		if(m.Msg[i].Code == -1 || m.Msg[i].Code == Code)
			return m.Msg[i];
	}

	return m.Msg[i];
}

bool CFunction::CheckEnaleChange()
{
	// 如果在有 Lot 的情況,要先 OneCycle / Override 
	// 不允許變更設定
	bool bOK = false;

	if( m.Info.iStatus == theApp.enCycle || m.Info.iStatus == theApp.enCycleStop || 
		m.Info.iStatus == theApp.enOverride || m.Info.iStatus == theApp.enOverrideStop )
	{
		// 如果 在 Cycle Status
		// 不准使用 Lot Done 和 New Lot
		AfxMessageBox("Please lot done first.!\n");
		bOK = false;
	}
	else if( m.InterLock.IsCycleFinishOK || m.LotInfo.LotInfoIsLotStart == 1 )
	{
		// 如果沒有 Cycle Finish 不可以使用 UI
		// 表示有建了 New Lot 而且並沒有 Lot Done
		AfxMessageBox("Please lot done first.!\n");
		bOK = false;
	}
	else if( m.LotInfo.LotInfoIsLotStart == 0 )
	{
		// 如果沒有建過 New Lot 就 可以變更
		bOK = true; 
	}
	else
		; // Never be here.!
	
	return bOK;
}
static CMutex MutexShuttleLog;
void CFunction::ShuttleJamLog(CString csLog)
{
	// Check Enable Communication Or Not.
	if( m.Setting.m_bEnableShuttleJamLog == 0 )
		return;
	//

	CSingleLock Lock(&MutexShuttleLog);
	Lock.Lock();
	
	CString cs;
	CString cstime;
	CTime time = CTime::GetCurrentTime();
	cs.Format("%s, [%s]\r\n", time.Format("%m/%d %H:%M:%S"), csLog);
	cstime.Format("%s",time.Format("%y-%m-%d"));
	
	CFile file;

	file.Open(".\\Log\\"+cstime+"_ShuttleJam.txt", CFile::modeCreate | CFile::modeWrite
		| CFile::modeNoTruncate | CFile::shareDenyNone, NULL);
	
	file.SeekToEnd();
	
	file.Write(cs.GetBuffer(0), cs.GetLength());
	file.Close();
	
	Lock.Unlock();
}
static CMutex MutexCommLog;
void CFunction::CommLog( CString csLog )
{
	// Check Enable Communication Or Not.
	if( m.Setting.m_bEnableCommLog == 0 )
		return;
	//

	CSingleLock Lock(&MutexCommLog);
	Lock.Lock();
	
	CString cs;
	CString cstime;
	CTime time = CTime::GetCurrentTime();
	cs.Format("%s, [%s]\r\n", time.Format("%m/%d %H:%M:%S"), csLog);
	cstime.Format("%s",time.Format("%y-%m-%d"));
	
	CFile file;

	file.Open(".\\Log\\"+cstime+"_Comm.txt", CFile::modeCreate | CFile::modeWrite
		| CFile::modeNoTruncate | CFile::shareDenyNone, NULL);
	
	file.SeekToEnd();
	
	file.Write(cs.GetBuffer(0), cs.GetLength());
	file.Close();
	
	Lock.Unlock();
}

//////////////////////////////////////////////////////////////////////
// 分析版本字串
// 這個 helper function 只有給 MyGetVersion 使用.
BOOL CFunction::ParseVersionString(LPSTR lpVersion, DWORD& dwMajor, DWORD& dwSecond, DWORD& dwThird, DWORD& dwFourth)
{
	BOOL bRet = FALSE;

	do
	{
		LPSTR token = NULL;

		// Get first token (Major version number)
		//
		token = _tcstok(lpVersion, TEXT(","));

		if (token == NULL)	// End of string
			break;	// String ended prematurely

		dwMajor = _ttoi(token);

		// Get second token (Minor version number)
		//
		token = _tcstok(NULL, TEXT(","));

		if (token == NULL)	// End of string
			break;	// String ended prematurely

		dwSecond = _ttoi(token);

		// Get third token (Build number)
		//
		token = _tcstok(NULL, TEXT(","));

		if (token == NULL)	// End of string
			break;	// String ended prematurely

		dwThird = _ttoi(token);

		// Get third token (Build number)
		//
		token = _tcstok(NULL, TEXT(","));

		if (token == NULL)	// End of string
			break;	// String ended prematurely

		dwFourth = _ttoi(token);

		bRet = TRUE;

	} while(FALSE);

	return bRet;
}

void CFunction::MyGetProductVersion()
{

}

//////////////////////////////////////////////////////////////////////
// 取得 EXE/DLL 版本，放到 lpszVersion
void CFunction::MyGetVersion(LPCTSTR lpszFileName, LPSTR lpszVersion, DWORD dwVerLen)
{
    LPVOID versionInfo = NULL;
	DWORD vLen;
	DWORD vSize = ::GetFileVersionInfoSize((char*)lpszFileName, &vLen);

	if (vSize)
    {
		LPVOID version;
		versionInfo = new BYTE[vSize + 1];

        if (::GetFileVersionInfo((char*)lpszFileName, vLen, vSize, versionInfo))
        {
			TCHAR fileVersion[256];

            _stprintf(fileVersion, _T("\\VarFileInfo\\Translation"));

            if (::VerQueryValue(versionInfo, fileVersion, &version, (UINT*)&vLen) && vLen == 4)
            {
				DWORD langD;
                CopyMemory(&langD, version, 4);
                _stprintf(fileVersion, _T("\\StringFileInfo\\%02X%02X%02X%02X\\FileVersion"),
					(langD & 0xFF00) >> 8, langD & 0xff, (langD & 0xFF000000) >> 24, (langD & 0xFF0000) >> 16);
            }
            else
			{
				_stprintf(fileVersion, _T("\\StringFileInfo\\%04X04B0\\FileVersion"), ::GetUserDefaultLangID());
            }

            if (::VerQueryValue(versionInfo, fileVersion, &version, (UINT*)&vLen))
			{
				if (vLen < dwVerLen)
				{
					_tcscpy(fileVersion, (LPSTR)version);
				}
				else
				{
					_tcsncpy(fileVersion, (LPSTR)version, dwVerLen - 1);
					fileVersion[dwVerLen - 1] = 0;
				}

			//	LPSTR lpszTemp;
				DWORD dwMajor, dwSecond, dwThird, dwFourth;
				if (ParseVersionString(fileVersion, dwMajor, dwSecond, dwThird, dwFourth))
				{
					if (dwThird == 0)
						_stprintf(lpszVersion, _T("%d.%d"), dwMajor, dwSecond);
					else if(dwFourth == 0)
						_stprintf(lpszVersion, _T("%d.%d%c"), dwMajor, dwSecond, dwThird + 'A'-1);
					else
						_stprintf(lpszVersion, _T("%d.%d%c%c"), dwMajor, dwSecond, dwThird+'A'-1, dwFourth+'a'-1);

				//	sprintf(lpszTemp, "%d.%d%d%d", dwMajor, dwSecond, dwThird, dwFourth);
				}
			}
        }
	}

	if (versionInfo)
		delete []versionInfo;
}
void CFunction::CycleFinishDone()
{
	m.m_heaterCtrl.m_lHeaterStart = 0;
	m.m_heaterCtrl.m_bHeaterTempOK = false;
	m.m_heaterCtrl.m_bHeaterIsStable = false;
	
	m.RemoteOutSet.HeaterOn = false;
}
void CFunction::CycleRepeatFinishDone()
{
	if( !m.m_RepeatTrayDATA.m_bIsOneCyclePress )
	{
		// 表示是自動 Cycle Finish(次數到達), 因此清除次數參數
		m.m_RepeatTrayDATA.m_bIsOneCyclePress = false;
		m.m_RepeatTrayDATA.m_NowCount = 0;
		f.SaveNowMoation();
	}
	else
		m.m_RepeatTrayDATA.m_bIsOneCyclePress = false;
}
void CFunction::CycleFinish()
{	
	m.InterLock.ArmEnd = false;

	// Cycle Finish. Tell Run Page can enable Lot Done.!
	m.InterLock.IsCycleFinishOK = true;

	// It is for Run Page using
	m.InterLock.IsCycleFinishOK = true;

	// Back to Ready 
	m.Info.iStatus = theApp.enReady;		// Cycle Finish. Force the system status to READY.

	// Code for cycle finish
	m.Err.System.Code = enCodeCycleFinish;	// Set a cycle finish error code.
}
void CFunction::CycleRemoteFinish()
{
	m.InterLock.ArmEnd = false;

	// Cycle Finish. Tell Run Page can enable Lot Done.!
	m.InterLock.IsCycleFinishOK = true;

	// It is for Run Page using
	m.InterLock.IsCycleFinishOK = true;

	// Back to Ready 
	m.Info.iStatus = theApp.enReady;		// Cycle Finish. Force the system status to READY.
}
/////////////////////////////////////////////////////
// Button Function.
void CFunction::UpdateButtonState()
{
	// Control by Error.
	if(m.Info.bError)
	{
		return;
	}

	if ( m.Info.iStatus == theApp.enReady )
	{
		m.RemoteOutSet.BtnStartOn		= true;		// 08	Set Panel Start light on
		m.RemoteOutSet.BtnStopOn		= false;	// 09	Set Panel Stop light on
		m.RemoteOutSet.BtnSkipOn		= false;	// 10	Set Panel Skip light on
		m.RemoteOutSet.BtnRetryOn		= false;	// 11	Set Panel Retry light on
		m.RemoteOutSet.BtnResetOn		= false;	// 13	Set Panel Reset light on
		m.RemoteOutSet.BtnInitialOn		= true;		// 14	Set Panel Initial light onOne Cycel light on
		m.RemoteOutSet.BtnOneCycleOn	= false;	// 15	Set Panel One Cycel light on
		m.OutSet.TestSiteSkip			= false;
	}
	// This is Handler "Ready" status
	// Note : Button control.
	
	if ( m.Info.iStatus == theApp.enInitial )
	{
		m.RemoteOutSet.BtnStartOn		= false;	// 08	Set Panel Start light on
		m.RemoteOutSet.BtnStopOn		= true;		// 09	Set Panel Stop light on
		m.RemoteOutSet.BtnSkipOn		= false;	// 10	Set Panel Skip light on
		m.RemoteOutSet.BtnRetryOn		= false;	// 11	Set Panel Retry light on
		m.RemoteOutSet.BtnResetOn		= false;	// 13	Set Panel Reset light on
		m.RemoteOutSet.BtnInitialOn		= false;	// 14	Set Panel Initial light onOne Cycel light on
		m.RemoteOutSet.BtnOneCycleOn	= false;	// 15	Set Panel One Cycel light on
		m.OutSet.TestSiteSkip			= false;
	}
	// This is Handler "Initial" status
	// Note : Button control.
		
	if ( m.Info.iStatus == theApp.enUninitial )
	{
		m.RemoteOutSet.BtnStartOn		= false;	// 08	Set Panel Start light on
		m.RemoteOutSet.BtnStopOn		= false;	// 09	Set Panel Stop light on
		m.RemoteOutSet.BtnSkipOn		= false;	// 10	Set Panel Skip light on
		m.RemoteOutSet.BtnRetryOn		= false;	// 11	Set Panel Retry light on
		m.RemoteOutSet.BtnResetOn		= false;	// 13	Set Panel Reset light on
		m.RemoteOutSet.BtnInitialOn		= true;		// 14	Set Panel Initial light onOne Cycel light on
		m.RemoteOutSet.BtnOneCycleOn	= false;	// 15	Set Panel One Cycel light on
		m.OutSet.TestSiteSkip			= false;
	}
	// This is Handler "Unitial" status
	// Note : Button control.
	
	if ( m.Info.iStatus == theApp.enCycle )
	{
		m.RemoteOutSet.BtnStartOn		= false;	// 08	Set Panel Start light on
		m.RemoteOutSet.BtnStopOn		= true;		// 09	Set Panel Stop light on
		m.RemoteOutSet.BtnSkipOn		= false;	// 10	Set Panel Skip light on
		m.RemoteOutSet.BtnRetryOn		= false;	// 11	Set Panel Retry light on
		m.RemoteOutSet.BtnResetOn		= false;	// 13	Set Panel Reset light on
		m.RemoteOutSet.BtnInitialOn		= false;	// 14	Set Panel Initial light onOne Cycel light on
		m.RemoteOutSet.BtnOneCycleOn	= false;	// 15	Set Panel One Cycel light on
		m.OutSet.TestSiteSkip			= false;
	}
	// This is Handler "Cycle" status
	// Note : Button control. IsPause will be false.
	
	if ( m.Info.iStatus == theApp.enCycleStop )
	{
		m.RemoteOutSet.BtnStartOn		= true;		// 08	Set Panel Start light on
		m.RemoteOutSet.BtnStopOn		= false;	// 09	Set Panel Stop light on
		m.RemoteOutSet.BtnSkipOn		= false;	// 10	Set Panel Skip light on
		m.RemoteOutSet.BtnRetryOn		= false;	// 11	Set Panel Retry light on
		m.RemoteOutSet.BtnResetOn		= false;	// 13	Set Panel Reset light on
		m.RemoteOutSet.BtnInitialOn		= true;		// 14	Set Panel Initial light onOne Cycel light on
		m.RemoteOutSet.BtnOneCycleOn	= true;		// 15	Set Panel One Cycel light on
		m.OutSet.TestSiteSkip			= false;
	}
	// This is Handler "Cycle Stop" status
	// Note : Button control. IsPause will be true.

	// One Cycle
	if ( m.Info.iStatus == theApp.enOneCycle )
	{
		m.RemoteOutSet.BtnStartOn		= false;	// 08	Set Panel Start light on
		m.RemoteOutSet.BtnStopOn		= true;		// 09	Set Panel Stop light on
		m.RemoteOutSet.BtnSkipOn		= false;	// 10	Set Panel Skip light on
		m.RemoteOutSet.BtnRetryOn		= false;	// 11	Set Panel Retry light on
		m.RemoteOutSet.BtnResetOn		= false;	// 13	Set Panel Reset light on
		m.RemoteOutSet.BtnInitialOn		= false;	// 14	Set Panel Initial light onOne Cycel light on
		m.RemoteOutSet.BtnOneCycleOn	= false;	// 15	Set Panel One Cycel light on
		m.OutSet.TestSiteSkip			= false;
	}
	// This is Handler "One Cycle" status
	// Note : Button control. IsPause will be true.

	if ( m.Info.iStatus == theApp.enOneCycleStop )
	{
		m.RemoteOutSet.BtnStartOn		= false;	// 08	Set Panel Start light on
		m.RemoteOutSet.BtnStopOn		= false;	// 09	Set Panel Stop light on
		m.RemoteOutSet.BtnSkipOn		= false;	// 10	Set Panel Skip light on
		m.RemoteOutSet.BtnRetryOn		= false;	// 11	Set Panel Retry light on
		m.RemoteOutSet.BtnResetOn		= false;	// 13	Set Panel Reset light on
		m.RemoteOutSet.BtnInitialOn		= true;		// 14	Set Panel Initial light onOne Cycel light on
		m.RemoteOutSet.BtnOneCycleOn	= true;		// 15	Set Panel One Cycel light on
		m.OutSet.TestSiteSkip			= false;

	}
	// This is Handler "One Cycle Stop" status
	// Note : Button control. IsPause will be true.
	
	if( m.Info.iStatus == theApp.enOverride )
	{
		m.RemoteOutSet.BtnStartOn		= false;	// 08	Set Panel Start light on
		m.RemoteOutSet.BtnStopOn		= true;		// 09	Set Panel Stop light on
		m.RemoteOutSet.BtnSkipOn		= false;	// 10	Set Panel Skip light on
		m.RemoteOutSet.BtnRetryOn		= false;	// 11	Set Panel Retry light on
		m.RemoteOutSet.BtnResetOn		= false;	// 13	Set Panel Reset light on
		m.RemoteOutSet.BtnInitialOn		= false;	// 14	Set Panel Initial light onOne Cycel light on
		m.RemoteOutSet.BtnOneCycleOn	= false;	// 15	Set Panel One Cycel light on
		m.OutSet.TestSiteSkip			= false;
	}
	// This is Handler "Override" status
	
	if( m.Info.iStatus == theApp.enOverrideStop )
	{
		m.RemoteOutSet.BtnStartOn		= false;	// 08	Set Panel Start light on
		m.RemoteOutSet.BtnStopOn		= false;	// 09	Set Panel Stop light on
		m.RemoteOutSet.BtnSkipOn		= false;	// 10	Set Panel Skip light on
		m.RemoteOutSet.BtnRetryOn		= false;	// 11	Set Panel Retry light on
		m.RemoteOutSet.BtnResetOn		= false;	// 13	Set Panel Reset light on
		m.RemoteOutSet.BtnInitialOn		= true;		// 14	Set Panel Initial light onOne Cycel light on
		m.RemoteOutSet.BtnOneCycleOn	= false;	// 15	Set Panel One Cycel light on
		m.OutSet.TestSiteSkip			= false;
	}
	// This is Handler "Override Stop" status
	
	if( m.Info.iStatus == theApp.enManual )
	{
		m.RemoteOutSet.BtnStartOn		= false;	// 08	Set Panel Start light on
		m.RemoteOutSet.BtnStopOn		= true;		// 09	Set Panel Stop light on
		m.RemoteOutSet.BtnSkipOn		= false;	// 10	Set Panel Skip light on
		m.RemoteOutSet.BtnRetryOn		= false;	// 11	Set Panel Retry light on
		m.RemoteOutSet.BtnResetOn		= false;	// 13	Set Panel Reset light on
		m.RemoteOutSet.BtnInitialOn		= false;	// 14	Set Panel Initial light onOne Cycel light on
		m.RemoteOutSet.BtnOneCycleOn	= false;	// 15	Set Panel One Cycel light on
		m.OutSet.TestSiteSkip			= false;
	}
	// This is Handler "Manual" status
	// In Manual Mode. User need initial again. Then He can go to "Cycle" status.
	// Note : Button control.
	
	if( m.Info.iStatus == theApp.enManualStop )
	{
		m.RemoteOutSet.BtnStartOn		= true;		// 08	Set Panel Start light on
		m.RemoteOutSet.BtnStopOn		= false;	// 09	Set Panel Stop light on
		m.RemoteOutSet.BtnSkipOn		= false;	// 10	Set Panel Skip light on
		m.RemoteOutSet.BtnRetryOn		= false;	// 11	Set Panel Retry light on
		m.RemoteOutSet.BtnResetOn		= false;	// 13	Set Panel Reset light on
		m.RemoteOutSet.BtnInitialOn		= true;		// 14	Set Panel Initial light onOne Cycel light on
		m.RemoteOutSet.BtnOneCycleOn	= false;	// 15	Set Panel One Cycel light on
		m.OutSet.TestSiteSkip			= false;
	}	
	// This is Handler "Manual Stop" status
	// Note : Button control.

	// If any SubDialog Open
	// Close all button
	if( m.Info.bSubDlgOpen )
	{
		m.RemoteOutSet.BtnStartOn		= false;	// 08	Set Panel Start light on
		m.RemoteOutSet.BtnStopOn		= false;	// 09	Set Panel Stop light on
		m.RemoteOutSet.BtnSkipOn		= false;	// 10	Set Panel Skip light on
		m.RemoteOutSet.BtnRetryOn		= false;	// 11	Set Panel Retry light on
		m.RemoteOutSet.BtnResetOn		= false;	// 13	Set Panel Reset light on
		m.RemoteOutSet.BtnInitialOn		= false;	// 14	Set Panel Initial light onOne Cycel light on
		m.RemoteOutSet.BtnOneCycleOn	= false;	// 15	Set Panel One Cycel light on
		m.OutSet.TestSiteSkip			= false;
	}

	switch(m.Info.iStatus)
	{
/*
	case theApp.enReady:		// Wait for Start
		m.Page.Run.m_wndRunStatus.SetNewBkColor(ST_YELLOW);
		m.Page.Run.m_wndRunStatus.SetNewTextColor(ST_BLACK);
		m.Page.Run.m_wndRunStatus.SetNewText("Ready");
		break;	
	case theApp.enInitial:
		m.Page.Run.m_wndRunStatus.SetNewBkColor(ST_RED);
		m.Page.Run.m_wndRunStatus.SetNewTextColor(ST_WHITE);
		m.Page.Run.m_wndRunStatus.SetNewText("Initial");
		break;
	case theApp.enUninitial:
		m.Page.Run.m_wndRunStatus.SetNewBkColor(ST_RED);
		m.Page.Run.m_wndRunStatus.SetNewTextColor(ST_WHITE);
		m.Page.Run.m_wndRunStatus.SetNewText("Uninitial");
		break;
*/
	case theApp.enCycle:
		m.Page.Run.m_wndRunStatus.SetNewBkColor(ST_GREEN);
		m.Page.Run.m_wndRunStatus.SetNewTextColor(ST_BLACK);
		m.Page.Run.m_wndRunStatus.SetNewText("Cycle");
		break;
	case theApp.enOneCycle:
		m.Page.Run.m_wndRunStatus.SetNewBkColor(ST_YELLOW);
		m.Page.Run.m_wndRunStatus.SetNewTextColor(ST_BLACK);
		m.Page.Run.m_wndRunStatus.SetNewText("One Cycle");
		break;
	case theApp.enCycleStop:
		m.Page.Run.m_wndRunStatus.SetNewBkColor(ST_YELLOW);
		m.Page.Run.m_wndRunStatus.SetNewTextColor(ST_BLACK);
		m.Page.Run.m_wndRunStatus.SetNewText("Cycle Stop");
		break;
	case theApp.enOverride:
		m.Page.Run.m_wndRunStatus.SetNewBkColor(ST_YELLOW);
		m.Page.Run.m_wndRunStatus.SetNewTextColor(ST_BLACK);
		m.Page.Run.m_wndRunStatus.SetNewText("Override");
		break;
	case theApp.enOverrideStop:
		m.Page.Run.m_wndRunStatus.SetNewBkColor(ST_YELLOW);
		m.Page.Run.m_wndRunStatus.SetNewTextColor(ST_BLACK);
		m.Page.Run.m_wndRunStatus.SetNewText("Override Stop");
		break;
	case theApp.enOneCycleStop:
		m.Page.Run.m_wndRunStatus.SetNewBkColor(ST_YELLOW);
		m.Page.Run.m_wndRunStatus.SetNewTextColor(ST_BLACK);
		m.Page.Run.m_wndRunStatus.SetNewText("Cycle Stop");
		break;
	case theApp.enManual:
		m.Page.Run.m_wndRunStatus.SetNewBkColor(ST_YELLOW);
		m.Page.Run.m_wndRunStatus.SetNewTextColor(ST_BLACK);
		m.Page.Run.m_wndRunStatus.SetNewText("Manual");
		break;
	case theApp.enManualStop:
		m.Page.Run.m_wndRunStatus.SetNewBkColor(ST_YELLOW);
		m.Page.Run.m_wndRunStatus.SetNewTextColor(ST_BLACK);
		m.Page.Run.m_wndRunStatus.SetNewText("Manual Stop");
		break;
	default:
		m.Page.Run.m_wndRunStatus.SetNewBkColor(ST_RED);
		m.Page.Run.m_wndRunStatus.SetNewTextColor(ST_WHITE);
		m.Page.Run.m_wndRunStatus.SetNewText("STOP");
		break;
	}
}

long CFunction::Wait(int msec)
{
	int iStart = 0;
	iStart = ::GetTickCount();
	while(1)
	{
		if((int)::GetTickCount() - iStart > msec)
			break;		
		if ( f.IsPause() )
			break;
		if (!m.Info.bRunning)
			break;

		Sleep(_Wait);
	}
	return enCodeRunOK;
}

bool CFunction::IsPause()
{
	return (m.Info.iStatus & 0x1) ? true : false;
}
void CFunction::ButtonInitial()
{
	// Insert Initial to Debug.
	m.Info.iStatus = theApp.enInitial;
	f.UpdateButtonState();

	// Initial all initial Repeat Tray data
	m.m_RepeatTrayDATA.m_bRepeatIsTray1		= true;
	m.m_RepeatTrayDATA.m_bIsOneCyclePress	= false;

	// Initial all initial interlock set to false
	m.MotorStatus.ArmXInitialed				= false;
	m.MotorStatus.ArmYInitialed				= false;
	m.MotorStatus.ArmZInitialed				= false;
	m.MotorStatus.InserterInitialed			= false;
	m.MotorStatus.TesterInitialed			= false;
	m.MotorStatus.InspectInitialed			= false;
	m.MotorStatus.ManualCtrlInitialed		= false;

	// Initial Interlock using. It is Each Axis initial complete
	// Set all interlock to false.
	m.InterLock.InitialArmZEnd				= false;			
	m.InterLock.InitialArmYEnd				= false;			
	m.InterLock.InitialArmXEnd				= false;			
	m.InterLock.InserterEnd					= false;				
	m.InterLock.TesterEnd					= false;					
	m.InterLock.InspectEnd					= false;	
	m.InterLock.ManualCtrlEnd				= false;

	//
	m.InterLock.TestingGo					= false;
	m.InterLock.Testing						= false;
	m.InterLock.TestingOK					= false;

	// Initial 清掉所有位置的 flag
	m.InterLock.TestSiteWithIC				= false;
	m.InterLock.SocketWithIC				= false;
	m.InterLock.RotatorWithIC				= false;
	m.InterLock.ShuttleWithIC				= false;
	m.InterLock.ShuttleHome					= false;
	//
	m.InterLock.ArmEnd						= false;

	//
	m.InterLock.ShuttleInputICOK			= false;
	m.InterLock.ShuttleOutputICOK			= false;
	m.InterLock.ShuttleResetInput			= false;
	
	// 
	// 當進行 Initial 要清除全部的 Button flag
	// 避免下一次 Initial 後的 Cycle 被上一次的 flag 影響到
	m.PanelButton.BtnInitPushed				= false;
	m.PanelButton.BtnOneCyclePushed			= false;
	m.PanelButton.BtnResetPushed			= false;
	m.PanelButton.BtnRetryPushed			= false;
	m.PanelButton.BtnSkipPushed				= false;
	m.PanelButton.BtnStartPushed			= false;
	m.PanelButton.BtnStopPushed				= false;
 
	// Initial 的 flag 的值要清調
	m.InitialInterLock.InitialTSUpOK		= false;
	m.InitialInterLock.InitialArmZUpOK		= false;

	//
	m.m_TSRemainICParameter.bTSRemainICflag	= false;

	// Initial 要清掉, 不然下一次就會取到前一次的數值
	m.m_ArmBook = -1;
	m.m_ArmPlaceBook = -1;

	// Insert Initial to Debug .
	////////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////////
	f.Motor.MotorLmtCounterClear();
	//
	f.RemoteSeCoordnationInitial();
	//

	// Start each CWinThread Initial status	
	theApp.m_tManualCtrl.InitialStart();
	theApp.m_tArm.InitialStart();
	theApp.m_tInspect.InitialStart();
	theApp.m_tTester.InitialStart();
	theApp.m_tInserter.InitialStart();
	theApp.m_thInitialArm.InitialStart();

	CDeerDlg *p = (CDeerDlg *) theApp.m_pMainWnd;
	p->SetUserPage(enLevelInitial);	
}

/*
Note :
	enReady = 0x11,							// After Initial. Wait for Start		
	enInitial = 0x20, enUninitial = 0x21,		
	enCycle = 0x30, enCycleStop = 0x31,
	enOneCycle = 0x40, enOneCycleStop = 0x41,
	enOverride 0x50, enOverrideStop = 0x51,
	enManual = 0x60, enManualStop = 0x61,
*/
void CFunction::ButtonStop()
{
	m.Info.iStatus = m.Info.iStatus | 0x1;
	
	bool bWait = true;
	while(bWait)
	{
		bWait = false;
	
		if( !theApp.m_tArm.IsPause())
			bWait = true;
		if( !theApp.m_tInspect.IsPause())
			bWait = true;
		if( !theApp.m_tInserter.IsPause())
			bWait = true;
		Sleep(1);			
	}
	// Wait All thread stop.
	
	CDeerDlg *p = (CDeerDlg *) theApp.m_pMainWnd;
	p->SetUserPage(m.Info.user);
	// We Insert the last level page.

	UpdateButtonState();
}
void CFunction::ButtonSkip()
{

}
void CFunction::ButtonStart()
{
	/////////////////////////////////////////////////////////
	// 手動控制使用
	if( m.Info.iStatus == theApp.enManualStop )
	{
		m.Info.iStatus = theApp.enManual;
		return;
	}
	/////////////////////////////////////////////////////////

	// 以下檢查 是否有建立工單
	if( CheckNewLot() )
	{
		// 有建立新的工單 / 就讓機台開始跑
	}
	else
	{
		// 沒有新工單
		ButtonStop();	// 把機台停止
		f.m_Log.AddEvent(enCodeRunPageLotInformation);	// Add Event

		CDlgLotInformation dlg;
		int nResponse = dlg.DoModal();
		if (nResponse == IDOK)
		{
			// We need to updata UI information.
			m.Page.Run.UpdateSetting();	
			return;
		}
		else if (nResponse == IDCANCEL)
		{
			return;
		}
	}
	// if Lot not create. Please return.
	/////////////////////////////////////////////////////////

	/////////////////////////////////////////////////////////
	// 以下強迫設定 ByPass 功能
	if( m.Setting.m_bSetByMode )
	{
		// 如果 Setting 打開這個選項, 就強迫用 Run Mode 設定
		if( m.Site.iRunMode == theApp.enOnLine )
		{
			m.Setting.m_bByPassRotatorAlarm = false;		//	檢查 Rotator 錯誤
			m.Setting.m_bByPassTestVacc = false;			//	檢查 TS Vacc 錯誤
			m.Setting.m_bByPassVacc = false;				//	檢查 Arm Vacc 錯誤
			m.Setting.m_bByPassTrayInPos = false;			//  檢查 Tray In Pos錯誤
			m.Setting.m_bByPassShuttleAlarm = false;		//  檢查 Shuttle 錯誤
			// 如果是 On Line 模式就不再ByPass任何檢查
		}
		else if( m.Site.iRunMode == theApp.enDemo )
		{
			m.Setting.m_bByPassRotatorAlarm = true;			// 不檢查 Rotator
			m.Setting.m_bByPassTestVacc = true;				// 不檢查 TS Vacc 錯誤
			m.Setting.m_bByPassVacc = true;					// 不檢查 Arm Vacc 錯誤
			m.Setting.m_bByPassTrayInPos = true;			// 不檢查 Tray In Pos錯誤
			m.Setting.m_bByPassShuttleAlarm = true;			// 不檢查 Shuttle 錯誤
			// 如果是 Demo 模式就 ByPass Vacc / Puff
		}
		else if( m.Site.iRunMode == theApp.enOffLine )
		{
			m.Setting.m_bByPassRotatorAlarm = false;		//	檢查 Rotator 錯誤
			m.Setting.m_bByPassTestVacc = false;			//	檢查 TS Vacc 錯誤
			m.Setting.m_bByPassVacc = false;				//	檢查 Arm Vacc 錯誤
			m.Setting.m_bByPassTrayInPos = false;			//  檢查 Tray In Pos錯誤
			m.Setting.m_bByPassShuttleAlarm = false;		//  檢查 Shuttle 錯誤
			// 如果是 Off Line 模式就不再ByPass任何檢查
		}
		else 
			; // Never be here.
	}

	/////////////////////////////////////////////////////////
	// Remote
	f.IsRepeatHeaterNeed();

	/////////////////////////////////////////////////////////
	// 以下把機台狀態設定為 Cycle  
	m.Info.iStatus = theApp.enCycle;		// Set Handler status

	CDeerDlg *p = (CDeerDlg *) theApp.m_pMainWnd;
	p->SetUserPage( enLevelRun );
	// We Insert the last level page.
	// Insert Run Page and disable others page.

	UpdateButtonState();
}
void CFunction::DeleteRemoteInputTrayData()
{
	CString csFile = _T("");
	int value = 0;
	csFile.Format("%s%d%s", _RemoteInputTrayFileDATA ,value, _RemoteInputTrayFileDATASub );

	::DeleteFile( m.FilePath.InputCustomInputPath + csFile );
}
bool CFunction::InitRemoteInputTrayData()
{
	bool bOK = true;

	// 建立相關目錄
	AutoCreateFolder( m.FilePath.InputCustomInputPath );

	return bOK;
}
void CFunction::InitTcp()
{
	if( m.m_InterfaceEnable.m_bEnableTcp == 1 )
	{
		//
		LoadTcpToObject();
		BOOL bCreate = m.m_InterfaceTcp.Create( _Tcp_If_Port, SOCK_STREAM );
		BOOL bListen = m.m_InterfaceTcp.Listen();

		m.m_InterfaceTcp.GetSockName(m.m_TcpInfo.csTesterIP, m.m_TcpInfo.iPort);

		//
		CString csMsg = _T("");
		csMsg.Format("Init TCP Success");
		f.DMsg.DMsg( csMsg  );
	}
}
void CFunction::InitATCModule()
{
	if( m.Setting.m_bEnableATCModule == 1 )
	{
		AutoCreateFolder( m.FilePath.AtcModuleSettingPath );	
	}
}
void CFunction::ButtonRetry()
{

}

void CFunction::ButtonOneCycle()
{
	/////////////////////////////////////////////////////////
	// Remote
	f.IsRepeatHeaterNeed();

	//
	m.Info.iStatus = theApp.enOneCycle;

	//
	m.m_RepeatTrayDATA.m_bIsOneCyclePress = true;

	CDeerDlg *p = (CDeerDlg *) theApp.m_pMainWnd;
	p->SetUserPage( enLevelRun );
	// We Insert the last level page.
	// Insert Run Page and disable others page.

	UpdateButtonState();
}

void CFunction::ButtonReset()
{

}


/////////////////////////////////////////////////////
// Basic Temperature. Control File
bool CFunction::EarseYieldValue(CString csFile, CString csSection, CString csProperty)
{
	::WritePrivateProfileString(csSection, csProperty, NULL, 
		csFile);
	// Delete Property

	::WritePrivateProfileString(csSection,NULL,NULL,csFile);
	// Delete Section

	return true;
}
bool CFunction::EarseTemperatureSetting(CString csFile, CString csSection, CString csProperty)
{
	::WritePrivateProfileString(csSection, csProperty, NULL, 
		csFile);
	// Delete Property

	::WritePrivateProfileString(csSection,NULL,NULL,csFile);
	// Delete Section

	return true;
}
bool CFunction::GetTemperatureSetting(CString csFile, CString csSection, CString csProperty, double &dValue)
{
	char cValue[200] = {0};
	::GetPrivateProfileString(csSection, csProperty, "NO_VALUE", 
		cValue, sizeof(cValue), csFile);
	char* pStop;
	double d = strtod(cValue, &pStop);
	CString csValue = cValue;
	if(csValue == "NO_VALUE")
	{
		return false;
	}
	else
		dValue = d;

	return true;
}
bool CFunction::GetTemperatureSetting(CString csFile, CString csSection, CString csProperty, int &iValue)
{
	int i = 
		::GetPrivateProfileInt(csSection, csProperty, -9999999, csFile);
	if(i == -9999999)
	{
		return false;
	}
	else
		iValue = i;

	return true;
}
bool CFunction::SaveTemperatureSetting(CString csFile, CString csSection, CString csProperty, double dValue)
{
	CString csValue;
	csValue.Format("%.15f", dValue);
	::WritePrivateProfileString(csSection, csProperty, csValue, 
		csFile);
	
	return true;
}
bool CFunction::SaveTemperatureSetting(CString csFile, CString csSection, CString csProperty, int iValue)
{
	CString csValue;
	csValue.Format("%d", iValue);
	::WritePrivateProfileString(csSection, csProperty, csValue, 
		 csFile);

	return true;
}

/////////////////////////////////////////////////////
// Basic Control File
void CFunction::GetSettingBinary(CString csFileName, CString csSection,	CString csProperty, int &iValue)
{
	char cValue[200] = {0};
	::GetPrivateProfileString(csSection, csProperty, "NO_VALUE", 
		cValue, sizeof(cValue), csFileName);
	CString csValue = cValue;
	if(csValue == "NO_VALUE")
	{
		csValue = "";
		int iTemp = iValue;
		for(int i=0; i < 16; iTemp = iTemp >> 1, i++)
		{
			if(iTemp & 0x1)
				csValue = '1' + csValue;
			else
				csValue = '0' + csValue;
		}
		::WritePrivateProfileString(csSection, csProperty,
			csValue, csFileName);
	}
	else
	{
		iValue = 0;
		for(int i=0; i<csValue.GetLength(); i++)
		{
			if(csValue[csValue.GetLength() - 1 - i] == '1')
				iValue += 1 << i;
		}
	}
}
void CFunction::GetSettingHex(CString csFileName, CString csSection,
							 CString csProperty, int &iValue)
{
	char cValue[200] = {0};
	::GetPrivateProfileString(csSection, csProperty, "NO_VALUE", 
		cValue, sizeof(cValue), csFileName);
	CString csValue = cValue;
	if(csValue == "NO_VALUE")
	{
		csValue.Format("0x%x", iValue);
		::WritePrivateProfileString(csSection, csProperty,
			csValue, csFileName);
	}
	else
	{
		iValue = 0;
		int j=0;
		for(int i=csValue.GetLength()-1; csValue[i] != 'x' && csValue[i] != 'X'; i--, j++)
		{
			switch(csValue[i])
			{
			case '0':
				break;
			case '1':
				iValue += (1 << (j*4));
				break;
			case '2':
				iValue += (2 << (j*4));
				break;
			case '3':
				iValue += (3 << (j*4));
				break;
			case '4':
				iValue += (4 << (j*4));
				break;
			case '5':
				iValue += (5 << (j*4));
				break;
			case '6':
				iValue += (6 << (j*4));
				break;
			case '7':
				iValue += (7 << (j*4));
				break;
			case '8':
				iValue += (8 << (j*4));
				break;
			case '9':
				iValue += (9 << (j*4));
				break;
			case 'a':
			case 'A':
				iValue += (10 << (j*4));
				break;
			case 'b':
			case 'B':
				iValue += (11 << (j*4));
				break;
			case 'c':
			case 'C':
				iValue += (12 << (j*4));
				break;
			case 'd':
			case 'D':
				iValue += (13 << (j*4));
				break;
			case 'e':
			case 'E':
				iValue += (14 << (j*4));
				break;
			case 'f':
			case 'F':
				iValue += (15 << (j*4));
				break;
			}
		}
	}
}

void CFunction::GetSettingDouble(CString csFileName, CString csSection,	CString csProperty, double &value)
{
	char cValue[200] = {0};
	::GetPrivateProfileString(csSection, csProperty, "NO_VALUE", 
		cValue, sizeof(cValue), csFileName);
	char* pStop;
	double d = strtod(cValue, &pStop);
	CString csValue = cValue;
	if(csValue == "NO_VALUE")
	{
		CString cs;
		cs.Format("%.15f", value);
		::WritePrivateProfileString(csSection, csProperty, cs, 
			csFileName);
	}
	else
		value = d;
}
void CFunction::GetSettingTrueFalse(CString csFileName, CString csSection, 
							   CString csProperty, int &iValue)
{
	int i = 
		::GetPrivateProfileInt(csSection, csProperty, -9999, csFileName);
	if(i == -9999)
	{
		CString cs;
		cs.Format("%d", iValue > 0 ? 1 : 0);
		::WritePrivateProfileString(csSection, csProperty, cs, csFileName);
	}
	else
		iValue = i > 0 ? 1 : 0;
}
void CFunction::DeleteSetting(CString csFile, CString csSection, CString csProperty, double dValue)
{
	::WritePrivateProfileString(csSection, csProperty, NULL, 
		csFile);
	// Delete Property
}
void CFunction::GetSetting(CString csFile, CString csSection,
							  CString csProperty, long &iValue)
{

	long i = 
		::GetPrivateProfileInt(csSection, csProperty, -9999999, 
			csFile);
	if(i == -9999999)
	{
		CString cs;
		cs.Format("%d", iValue);
		::WritePrivateProfileString(csSection, csProperty, cs,
			csFile);
	}
	else
		iValue = i;
}

void CFunction::GetSetting(CString csFile, CString csSection, CString csProperty, CString &csValue)
{
	char cValue[5000] = {0};

	GetPrivateProfileString(csSection, csProperty, "NO_VALUE", 
		cValue, sizeof(cValue), csFile);
	CString c = cValue;
	if(c == "NO_VALUE")
	{
		::WritePrivateProfileString(csSection, csProperty, csValue, 
			csFile);
	} 
	else
		csValue = c;
}

void CFunction::GetSetting(CString csFile, CString csSection, CString csProperty, double &dValue)
{
	char cValue[200] = {0};
	::GetPrivateProfileString(csSection, csProperty, "NO_VALUE", 
		cValue, sizeof(cValue), csFile);
	char* pStop;
	double d = strtod(cValue, &pStop);
	CString csValue = cValue;
	if(csValue == "NO_VALUE")
	{
		CString cs;
		cs.Format("%.15f", dValue);
		::WritePrivateProfileString(csSection, csProperty, cs, 
			csFile);
	}
	else
		dValue = d;
}
void CFunction::SaveSetting(CString csFile, CString csSection, 
							CString csProperty, double dValue)
{
	CString csValue;
	csValue.Format("%.15f", dValue);
	::WritePrivateProfileString(csSection, csProperty, csValue, 
		csFile);
}
void CFunction::SaveSetting(CString csFile, CString csSection, 
							CString csProperty, CString csValue)
{
	::WritePrivateProfileString(csSection, csProperty, csValue, 
		csFile);
}
void CFunction::SaveSetting(CString csFile, CString csSection, 
							CString csProperty, long iValue)
{
	CString csValue;
	csValue.Format("%d", iValue);
	::WritePrivateProfileString(csSection, csProperty, csValue, 
		csFile);
}
void CFunction::SaveSettingBinary(CString csFileName, CString csSection,
								CString csProperty, int iValue)
{
	CString csValue;
	for(int i=15; i>=0; i--)
		csValue += ((iValue & 1 << i) ? "1" : "0");
	::WritePrivateProfileString(csSection, csProperty,
		csValue, csFileName);
}
void CFunction::SaveSettingDouble(CString csFileName, CString csSection,
								CString csProperty, double dValue)
{
	CString csValue;
	csValue.Format("%.15f", dValue);
	::WritePrivateProfileString(csSection, csProperty, csValue, 
		csFileName);
}
void CFunction::SaveSettingTrueFalse(CString csFileName, CString csSection, 
							   CString csProperty, int iValue)
{
	CString csValue;
	csValue.Format("%d", iValue > 0 ? 1 : 0);
	::WritePrivateProfileString(csSection, csProperty,
		csValue, csFileName);
}
void CFunction::SaveSetting(CString csFile, CString csSection, CString csProperty, bool bValue)
{
		CString cs;
		cs.Format("%d", bValue ? 1 : 0);
		::WritePrivateProfileString(csSection, csProperty, cs,
			csFile);

}
void CFunction::SaveSettingHex(CString csFileName, CString csSection,
							 CString csProperty, int iValue)
{
	CString csValue;
	csValue.Format("0x%x", iValue);
	::WritePrivateProfileString(csSection, csProperty,
		csValue, csFileName);
}
void CFunction::GetSetting(CString csFile, CString csSection,
						   CString csProperty, tagMotorParam &Param)
{
	// Accelerate
	GetSetting(csFile, csSection, csProperty + " Accelerate", Param.Accelerate);

	// MaxSpeed
	Param.MaxSpeed = 2000;
	GetSetting(csFile, csSection, csProperty + " MaxSpeed", Param.MaxSpeed);
	// Multiple
	Param.Multiple = 100;
	GetSetting(csFile, csSection, csProperty + " Multiple", Param.Multiple);
	// Start
	Param.Start = 30;
	GetSetting(csFile, csSection, csProperty + " Start", Param.Start);
	// In Position Range
	Param.InPosRange = 2;
	GetSetting(csFile, csSection, csProperty + " In Position Range", Param.InPosRange);
	// Drift Speed	
	GetSetting(csFile, csSection, csProperty + " Drift Speed", Param.DrifSpeed);
	// Search Speed
	if(csProperty.Find("Shuttle")>-1)
		Param.SearchSpeed = 500;
	else 
		Param.SearchSpeed = 100;
	GetSetting(csFile, csSection, csProperty + " Search Speed", Param.SearchSpeed);
	// Speed
//	GetSetting(csFile, csSection, csProperty + " Speed", Param.Speed = 50);

	// Jerk
	GetSetting(csFile, csSection, csProperty + " Jerk", Param.Jerk = 50);
}
void CFunction::SaveSetting(CString csFile, CString csSection, CString csProperty, int iValue)
{
	CString csValue;
	csValue.Format("%d", iValue);
	::WritePrivateProfileString(csSection, csProperty, csValue, 
		 csFile);
}
void CFunction::GetSetting(CString csFile, CString csSection, CString csProperty, COLORREF &iValue)
{
	long i = 
		::GetPrivateProfileInt(csSection, csProperty, -9999999, 
			csFile);
	if(i == -9999999)
	{
		CString cs;
		cs.Format("%d", iValue);
		::WritePrivateProfileString(csSection, csProperty, cs,
			csFile);
	}
	else
		iValue = (COLORREF)i;
}
void CFunction::SaveSetting(CString csFile, CString csSection, CString csProperty, COLORREF iValue)
{
	CString csValue;
	csValue.Format("%d", iValue);
	::WritePrivateProfileString(csSection, csProperty, csValue, 
		csFile);
}
void CFunction::GetSetting(CString csFile, CString csSection, CString csProperty, int &iValue)
{
	int i = 
		::GetPrivateProfileInt(csSection, csProperty, -9999999, 
			 csFile);
	if(i == -9999999)
	{
		CString cs;
		cs.Format("%d", iValue);
		::WritePrivateProfileString(csSection, csProperty, cs,
			csFile);
	}
	else
		iValue = i;
}

void CFunction::GetSetting(CString csFile, CString csSection, CString csProperty, bool &bValue)
{
	long i = 
		::GetPrivateProfileInt(csSection, csProperty, -9999999, 
			csFile );
	if(i == -9999999)
	{
		CString cs;
		cs.Format("%d", bValue ? 1 : 0);
		::WritePrivateProfileString(csSection, csProperty, cs,
			csFile );
	}
	else
	{

		if( i >0 )
			bValue = true;
		else
			bValue = false;

	}
}

void CFunction::SaveSetting(CString csFile, CString csSection,
							CString csProperty, tagMotorParam Param)
{
	// Accelerate
	SaveSetting(csFile, csSection, csProperty + " Accelerate", Param.Accelerate);
	// MaxSpeed
	SaveSetting(csFile, csSection, csProperty + " MaxSpeed", Param.MaxSpeed);
	// Multiple
	SaveSetting(csFile, csSection, csProperty + " Multiple", Param.Multiple);
	// Start
	SaveSetting(csFile, csSection, csProperty + " Start", Param.Start);
	// In Position Range
	SaveSetting(csFile, csSection, csProperty + " In Position Range", Param.InPosRange);
	// Drift Speed
	SaveSetting(csFile, csSection, csProperty + " Drift Speed", Param.DrifSpeed);
	// Search Speed
	SaveSetting(csFile, csSection, csProperty + " Search Speed", Param.SearchSpeed);
	// Speed
	// SaveSetting(csFile, csSection, csProperty + " Speed", Param.Speed);	

	// Jerk
	SaveSetting(csFile, csSection, csProperty + " Jerk", Param.Jerk);
}

/////////////////////////////////////////////////////
// Offset 
void CFunction::LoadOffset()
{
	// 如果 Lot Done 完, 然後沒有選過 TrayFile
	// 會造成 Offset 在 Load File 產生 .offset 檔案
	// 所以只要發現 沒有 TrayFile 的紀錄, 就直接 return
	if( m.UI.FileMain == "" )
		return;

	CString csFile;
	csFile = m.FilePath.TrayFilesPath + m.UI.FileMain.Left( m.UI.FileMain.Find(_SubFileName2, 0)) + _SubOffsetName2;

	//////////////////////////////////////////
	// Arm Offset below.
	// Input 
	GetSetting(csFile, "Offset", "Input x",				m.m_Offset.Input.x );
	GetSetting(csFile, "Offset", "Input y",				m.m_Offset.Input.y );
	GetSetting(csFile, "Offset", "Input z",				m.m_Offset.Input.z );
	GetSetting(csFile, "Offset", "Input z2",			m.m_Offset.Input.z2 );

	// Arm In Output1
	GetSetting(csFile, "Offset", "Output1 x",			m.m_Offset.Output1.x );
	GetSetting(csFile, "Offset", "Output1 y",			m.m_Offset.Output1.y );
	GetSetting(csFile, "Offset", "Output1 z",			m.m_Offset.Output1.z );
	GetSetting(csFile, "Offset", "Output1 z2",			m.m_Offset.Output1.z2 );

	// Rotator
	GetSetting(csFile, "Offset", "Rotator x",			m.m_Offset.Rotator.x );
	GetSetting(csFile, "Offset", "Rotator y",			m.m_Offset.Rotator.y );
	GetSetting(csFile, "Offset", "Rotator z",			m.m_Offset.Rotator.z );
	GetSetting(csFile, "Offset", "Rotator z2",			m.m_Offset.Rotator.z2 );

	// Socket
	GetSetting(csFile, "Offset", "Socket x",			m.m_Offset.Socket.x );
	GetSetting(csFile, "Offset", "Socket y",			m.m_Offset.Socket.y );
	GetSetting(csFile, "Offset", "Socket z",			m.m_Offset.Socket.z );
	GetSetting(csFile, "Offset", "Socket z2",			m.m_Offset.Socket.z2 );

	//////////////////////////////////////////
	// Shuttle 
	GetSetting(csFile, "Offset", "Shuttlt In x",		m.m_Offset.DutIn.x );
	GetSetting(csFile, "Offset", "Shuttlt In y",		m.m_Offset.DutIn.y );
	GetSetting(csFile, "Offset", "Shuttlt In z",		m.m_Offset.DutIn.z );
	GetSetting(csFile, "Offset", "Shuttlt In z2",		m.m_Offset.DutIn.z2 );

	GetSetting(csFile, "Offset", "Shuttlt Out x",		m.m_Offset.DutOut.x );
	GetSetting(csFile, "Offset", "Shuttlt Out y",		m.m_Offset.DutOut.y );
	GetSetting(csFile, "Offset", "Shuttlt Out z",		m.m_Offset.DutOut.z );
	GetSetting(csFile, "Offset", "Shuttlt Out z2",		m.m_Offset.DutOut.z2 );

	//////////////////////////////////////////
	// Test Area Offset below.
	GetSetting(csFile, "Offset", "TestSite contact",	m.m_Offset.TestSite.contact );
	GetSetting(csFile, "Offset", "TestSite home",		m.m_Offset.TestSite.home );
	GetSetting(csFile, "Offset", "TestSite pick",		m.m_Offset.TestSite.pick );
	GetSetting(csFile, "Offset", "TestSite place",		m.m_Offset.TestSite.place );
}	

void CFunction::SaveOffset()
{
	// 如果 Lot Done 完, 然後沒有選過 TrayFile
	// 會造成 Offset 在 Load File 產生 .offset 檔案
	// 所以只要發現 沒有 TrayFile 的紀錄, 就直接 return
	if( m.UI.FileMain == "" )
		return;

	CString csFile;
	csFile = m.FilePath.TrayFilesPath + m.UI.FileMain.Left( m.UI.FileMain.Find(_SubFileName2, 0)) + _SubOffsetName2;

	//////////////////////////////////////////
	// Arm Offset below.
	// Input
	SaveSetting(csFile, "Offset", "Input x",			m.m_Offset.Input.x );
	SaveSetting(csFile, "Offset", "Input y",			m.m_Offset.Input.y );
	SaveSetting(csFile, "Offset", "Input z",			m.m_Offset.Input.z );
	SaveSetting(csFile, "Offset", "Input z2",			m.m_Offset.Input.z2 );

	// Arm In Output1
	SaveSetting(csFile, "Offset", "Output1 x",			m.m_Offset.Output1.x );
	SaveSetting(csFile, "Offset", "Output1 y",			m.m_Offset.Output1.y );
	SaveSetting(csFile, "Offset", "Output1 z",			m.m_Offset.Output1.z );
	SaveSetting(csFile, "Offset", "Output1 z2",			m.m_Offset.Output1.z2 );

	// Rotator
	SaveSetting(csFile, "Offset", "Rotator x",			m.m_Offset.Rotator.x );
	SaveSetting(csFile, "Offset", "Rotator y",			m.m_Offset.Rotator.y );
	SaveSetting(csFile, "Offset", "Rotator z",			m.m_Offset.Rotator.z );
	SaveSetting(csFile, "Offset", "Rotator z2",			m.m_Offset.Rotator.z2 );

	// Socket
	SaveSetting(csFile, "Offset", "Socket x",			m.m_Offset.Socket.x );
	SaveSetting(csFile, "Offset", "Socket y",			m.m_Offset.Socket.y );
	SaveSetting(csFile, "Offset", "Socket z",			m.m_Offset.Socket.z );
	SaveSetting(csFile, "Offset", "Socket z2",			m.m_Offset.Socket.z2 );

	//////////////////////////////////////////
	// Shuttle 
	SaveSetting(csFile, "Offset", "Shuttlt In x",		m.m_Offset.DutIn.x );
	SaveSetting(csFile, "Offset", "Shuttlt In y",		m.m_Offset.DutIn.y );
	SaveSetting(csFile, "Offset", "Shuttlt In z",		m.m_Offset.DutIn.z );
	SaveSetting(csFile, "Offset", "Shuttlt In z2",		m.m_Offset.DutIn.z2 );

	SaveSetting(csFile, "Offset", "Shuttlt Out x",		m.m_Offset.DutOut.x );
	SaveSetting(csFile, "Offset", "Shuttlt Out y",		m.m_Offset.DutOut.y );
	SaveSetting(csFile, "Offset", "Shuttlt Out z",		m.m_Offset.DutOut.z );
	SaveSetting(csFile, "Offset", "Shuttlt Out z2",		m.m_Offset.DutOut.z2 );

	//////////////////////////////////////////
	// Test Area Offset below.
	SaveSetting(csFile, "Offset", "TestSite contact",	m.m_Offset.TestSite.contact );
	SaveSetting(csFile, "Offset", "TestSite home",		m.m_Offset.TestSite.home );
	SaveSetting(csFile, "Offset", "TestSite pick",		m.m_Offset.TestSite.pick );
	SaveSetting(csFile, "Offset", "TestSite place",		m.m_Offset.TestSite.place );
}	


/////////////////////////////////////////////////////
// Lot Information
void CFunction::LoadLotInfo()
{
  CString cs, csFile;
  csFile = m.FilePath.UIPath;

  GetSetting(csFile, "Lot Info", "Lot Number",			m.LotInfo.LotInfoNo );			//目前工單
  GetSetting(csFile, "Lot Info", "Lot Operater",		m.LotInfo.LotInfoOperator );	//目前作業員
  GetSetting(csFile, "Lot Info", "Lot Device ID",		m.LotInfo.LotInfoDeviceID );	//目前DeviceID
  GetSetting(csFile, "Lot Info", "Lot Program ID",		m.LotInfo.LotInfoProgramerID );	//目前ProgramID
  GetSetting(csFile, "Lot Info", "Lot Machine ID",		m.LotInfo.LotInfoMachineID );	//目前Machine ID

  GetSetting(csFile, "Lot Info", "Lot Is Start",		m.LotInfo.LotInfoIsLotStart );	//目前Lot是否是NewLot

  GetSetting(csFile, "Lot Info", "Lot Is Start Time",	m.LotInfo.LotStartTime );	//目前Lot開始時間
 
  // Backup last lot information
  // It is for lot information dialog using. Copy last function
  GetSetting(csFile, "Lot Info", "Old Lot Number",		m.LotInfo.OldLotInfoNo );			// 上一筆目前工單
  GetSetting(csFile, "Lot Info", "Old Lot Operater",	m.LotInfo.OldLotInfoOperator );		// 上一筆目前作業員
  GetSetting(csFile, "Lot Info", "Old Lot Device ID",	m.LotInfo.OldLotInfoDeviceID );		// 上一筆目前DeviceID
  GetSetting(csFile, "Lot Info", "Old Lot Program ID",  m.LotInfo.OldLotInfoProgramerID );	// 上一筆目前ProgramID
  GetSetting(csFile, "Lot Info", "Old Lot Machine ID",  m.LotInfo.OldLotInfoMachineID );	// 上一筆目前Machine ID  

  GetSetting(csFile, "Lot Info", "Test Mode",			m.LotInfo.TestItem);
}
void CFunction::AddNewArmLogICFolder(CString csLotName)
{
	if( m.Setting.m_bEnableCCDLogICImage == 1 )
	{
		CString csFolderName = _T("");
		CString csFilePath = _T("");

		// Time for filename
		CTime time = CTime::GetCurrentTime();
		CString csTime = _T("");		
		csTime.Format("%.4d_%.2d_%.2d_%.2d%.2d%.2d", 
			time.GetYear(), time.GetMonth(), time.GetDay(), time.GetHour(), time.GetMinute(), time.GetSecond() );

		// Create the folder
		csFolderName.Format("%s_%s", csTime, csLotName );
		csFilePath = m.FilePath.ArmLogICImagePath + "" + csFolderName;

		// Save the file path
		m.m_ArmLogICImage.csImageFilePath = csFilePath;
		SaveArmLogICImagePath();
	
		// Create phyical folder
		if( m.m_ArmLogICImage.bEnableArmLogICImage == 1 )
			AutoCreateFolder( csFilePath );
	}
}
void CFunction::SaveLotInfo()
{
  CString cs, csFile;
  csFile = m.FilePath.UIPath;

  SaveSetting(csFile, "Lot Info", "Lot Number",		m.LotInfo.LotInfoNo );			//目前工單
  SaveSetting(csFile, "Lot Info", "Lot Operater",	m.LotInfo.LotInfoOperator );	//目前作業員
  SaveSetting(csFile, "Lot Info", "Lot Device ID",	m.LotInfo.LotInfoDeviceID );	//目前DeviceID
  SaveSetting(csFile, "Lot Info", "Lot Program ID", m.LotInfo.LotInfoProgramerID );	//目前ProgramID
  SaveSetting(csFile, "Lot Info", "Lot Machine ID", m.LotInfo.LotInfoMachineID );	//目前Machine ID
  SaveSetting(csFile, "Lot Info", "Lot Is Start",	m.LotInfo.LotInfoIsLotStart );	//目前Lot是否是NewLot 
  SaveSetting(csFile, "Lot Info", "Lot Is Start Time",	m.LotInfo.LotStartTime );	//目前Lot開始時間
  
  // Backup last lot information
  // It is for lot information dialog using. Copy last function
  SaveSetting(csFile, "Lot Info", "Old Lot Number",		m.LotInfo.OldLotInfoNo );			// 上一筆目前工單
  SaveSetting(csFile, "Lot Info", "Old Lot Operater",	m.LotInfo.OldLotInfoOperator );		// 上一筆目前作業員
  SaveSetting(csFile, "Lot Info", "Old Lot Device ID",	m.LotInfo.OldLotInfoDeviceID );		// 上一筆目前DeviceID
  SaveSetting(csFile, "Lot Info", "Old Lot Program ID", m.LotInfo.OldLotInfoProgramerID );	// 上一筆目前ProgramID
  SaveSetting(csFile, "Lot Info", "Old Lot Machine ID", m.LotInfo.OldLotInfoMachineID );	// 上一筆目前Machine ID  

  SaveSetting(csFile, "Lot Info", "Test Item", (long)m.LotInfo.TestItem);
	
  // 
}

bool CFunction::CheckNewLot()
{
	// 如果沒有建立工單, 就表示是 false
	bool bIsNewLot = false;

	if( m.LotInfo.LotInfoIsLotStart == 0 )
		bIsNewLot = false;	// 表示沒有工單
	else
		bIsNewLot = true;	// 表示有建立工單

	return bIsNewLot;
}
void CFunction::LotDoneResetRunPageUI()
{
	m.Counter.SitePass = 0;
	m.Counter.SiteTotal = 0;
	//
	CString csYield;
	csYield.Format("0.0%% / 0");
	m.Page.Run.m_wndYield.SetWindowText( csYield );
	// Denny 說 Lot Done 要清除資料.!, 所以 Lot Done 也要更新畫面, 

	m.Page.Run.m_wndTesting.SetWindowText("-");
	m.Page.Run.m_ContinueFail.Clear();
	m.Page.Run.m_ContinueFail.SetBkColour(ST_WHITE);
	CString csTestTime;
	double TestTime = 0.0;
	csTestTime = 0.0;
	csTestTime.Format("%5.2f", TestTime );
	m.Page.Run.m_wndTestTime.SetWindowText( csTestTime );
	m.Page.Run.m_wndTestTime.SetNewBkColor(ST_LIGHTYELLOW);
}
void CFunction::LotDoneClearCoord()
{
	// Coord
	::DeleteFile( m.FilePath.InputCoordPath );		// Input Coord
	::DeleteFile( m.FilePath.Output1CoordPath );	// Output1 Coord 

	::DeleteFile( m.FilePath.Tray1CoordPath );		// Tray 1 Coord
	::DeleteFile( m.FilePath.Tray2CoordPath );		// Tray 2 Coord

	f.SetCoord(); // Lot Done 後,重設全部的狀態.
}
void CFunction::LotDoneCopyInfo()
{
	// 把 Lot 資訊 copy 到舊的 Lot Information. 給下一次使用
	m.LotInfo.OldLotInfoDeviceID	= m.LotInfo.LotInfoDeviceID;
	m.LotInfo.OldLotInfoMachineID	= m.LotInfo.LotInfoMachineID;
	m.LotInfo.OldLotInfoNo			= m.LotInfo.LotInfoNo;
	m.LotInfo.OldLotInfoOperator	= m.LotInfo.LotInfoOperator;
	m.LotInfo.OldLotInfoProgramerID = m.LotInfo.LotInfoProgramerID;
	//
}
void CFunction::LotDoneClearInfo()
{
	m.LotInfo.LotStartTime			= "";
	m.LotInfo.LotInfoDeviceID		= "";
	m.LotInfo.LotInfoMachineID		= "";
	m.LotInfo.LotInfoNo				= "";
	m.LotInfo.LotInfoOperator		= "";
	m.LotInfo.LotInfoProgramerID	= "";
	m.LotInfo.LotInfoIsLotStart 	= 0;
	m.m_RemoteTestEvent = enLotDone;
	if(m.m_TestInterface.m_bRemoteMode)
		f.RemoteSendTestEvent(m.m_RemoteTestEvent);
}
void CFunction::LotDoneClearSetting()
{
	// Before Delete backup it first
	m.m_LastTrayData.FileMain				= m.UI.FileMain;
	m.m_LastTrayData.FileMainMapping		= m.UI.FileMainMapping;
	m.m_LastTrayData.FileMainTestSetting	= m.UI.FileMainTestSetting;
	m.m_LastTrayData.VisionOcrPatternName	= m.TraySpec.VisionOcrPatternName;
	m.m_LastTrayData.VisionPatternName		= m.TraySpec.VisionPatternName;

	//
	m.UI.FileMain							= "";
	m.UI.FileMainMapping					= "";
	m.UI.FileMainTestSetting				= "";
	
	m.TraySpec.VisionPatternName			= "";
	m.TraySpec.VisionOcrPatternName			= "";
	
	f.SaveUI();
	f.SaveLastTrayData();
}
// RepeatTray TrayMap
void CFunction::LotDoneClearTrayMapRepeat()
{
	CString csFile = _T("");
	csFile = m.FilePath.TrayMapPath;
	for(int i=0; i<_Output_Stack_Number; i++)
	{
		CString csTrayMapFileName = _T("");
		csTrayMapFileName.Format("\\TrayMap%d.txt", i);
		::DeleteFile( csFile + csTrayMapFileName );	
	}

	for(i=0;i<_Output_Stack_Number;i++)
		m.TrayMapRepeat[i].clear();					// 清除資料 


	f.SaveTrayMapRepeat();							// 產生新的 TrayMap
	f.LoadTrayMapRepeat();							// 重新產生文字檔
}
void CFunction::LotDoneClearTrayMap()
{
	CString csFile = _T("");
	csFile = m.FilePath.TrayMapPath;
	for(int i=0; i<_Output_Stack_No; i++)
	{
		CString csTrayMapFileName = _T("");
		csTrayMapFileName.Format("\\TrayMap%d.txt", i);
		::DeleteFile( csFile + csTrayMapFileName );	
	}

	for(i=0;i<_Output_Stack_No;i++)
		m.TrayMap[i].clear();						// 清除資料 


	f.SaveTrayMap();								// 產生新的 TrayMap
	f.LoadTrayMap();								// 重新產生文字檔
}
void CFunction::LotDoneClearUPH()
{
	m.UPH.ICTested = 0;
	m.UPH.CycleTime = 0;
	m.UPH.CycleStartTime = 0;
	m.UPH.iUPH = 0;
}
void CFunction::LotDone()
{
	// 清除 Interlock
	m.m_TSRemainICParameter.bTSRemainICflag = false;

	//
	m.m_LotInfoProg.m_csLotInformationInfo = "Lot Done Start";

	// Error Report
	f.ExportErrorRateReport();

	// Yield Ctrl
	f.ClearYieldCtrl();

	// Clear UPH value
	f.LotDoneClearUPH();

	// Clear Yield Value
	f.LotDoneClearYieldValue();

	// Clear Output Yield Rate
	f.LotDoneClearOutputYieldCounter();

	// Copy Lot Information to Old Lot Information
	f.LotDoneCopyInfo();

	//
	m.m_LotInfoProg.m_csLotInformationInfo = "Copy Bin Log";
	
	// 把 TempBin 的 Copy 到 Bin Log
	// 可能不足一盤, 或是 OneCycle / Override 
	f.Report.CopyBinLog();

	//
	m.m_LotInfoProg.m_csLotInformationInfo = "Export Summary Report";

	//
	f.ExportSummaryReport();

	//
	f.LotDoneClearInfo();

	//
	m.m_LotInfoProg.m_csLotInformationInfo = "Save Lot Info";

	// Clear UI.UI about Lot info
	f.SaveLotInfo();
	
	//
	m.m_LotInfoProg.m_csLotInformationInfo = "Earse Temp Bin Log";

	// 清除 Bin Log 資料庫資料.
	f.Report.EarseReport_BinLog();

	// 清除 Temp Bin Log 資料庫資料.
	f.Report.EarseTempReport_BinLog();

	// 清除 TrayMap
	// (TrayMap 資料夾)
	f.LotDoneClearTrayMap();

	// 清除 TrayMap Repeat
	// (TrayMap 資料夾)
	f.LotDoneClearTrayMapRepeat();

	// 清除 Coord 資料夾
	f.LotDoneClearCoord();

	// 清除 Remote Input 檔案
	f.DeleteRemoteInputTrayData();

	// 清除 UPH 資料
	f.ClearUPHAllData();

	// 清除全部的資料 Jam Rate
	f.ClearJamRateInfo();

	// 清除全部的資料 Repeat tray
	f.ClearRepeatTrayDATA();

	//
	m.m_LotInfoProg.m_csLotInformationInfo = "Clear Data";

	// 清除 Run Page 資訊
	// Output Counter 歸零. 然後在 Run Page 會自己存起來
	int i=0;
	for(i=0; i<_Output_Stack_No; i++)
		m.Counter.OutputCount[i] = 0;

	// Lot Done 的值沒有清掉
	f.SaveCounter();

	// 清除設定檔
	f.LotDoneClearSetting();

	// Clear Run Page 畫面 / 和相關數值
	f.LotDoneResetRunPageUI();

	//
	m.m_LotInfoProg.m_csLotInformationInfo = "Clear Tray Data";

	// Lot Done
	theApp.m_InputTray.ChangeTray();
	theApp.m_OutputTray.SetFull();

	// Lot Done / Repeat Tray
	theApp.m_Tray1.ChangeTray();
	theApp.m_Tray2.ChangeTray();
	
	// Lot Done 清除 PreHeater 的狀態, 下一次由第一顆開始
	theApp.m_PreHeaterTray.ClearBuffer();

	// Lot Done Complete
	m.m_LotInfoProg.m_csLotInformationInfo = "Lot Done Complete";
	m.m_LotInfoProg.m_bLotInformationDone = true;
}

/////////////////////////////////////////////////////
// Tray Spec
void CFunction::LoadTraySpec()
{
	CString csFile = _T("");

	csFile = m.FilePath.TrayFilesPath + m.UI.FileMain;

	// Load Tray Spec
	m.TraySpec.A = m.TraySpec.B = m.TraySpec.C = m.TraySpec.D = 10;
	m.TraySpec.Column = m.TraySpec.Row = 3;

	GetSetting( csFile, "Tray Spec", "A",		m.TraySpec.A);
	GetSetting( csFile, "Tray Spec", "B",		m.TraySpec.B);
	GetSetting( csFile, "Tray Spec", "C",		m.TraySpec.C);
	GetSetting( csFile, "Tray Spec", "D",		m.TraySpec.D);
	GetSetting( csFile, "Tray Spec", "Column",	m.TraySpec.Column);
	GetSetting( csFile, "Tray Spec", "Row",		m.TraySpec.Row);
	GetSetting( csFile, "Tray Spec", "Thick Tray",	m.TraySpec.ThickTrayMode );
	GetSetting( csFile, "Tray Spec", "Tray Height",	m.TraySpec.TrayHeight );

	// Load Preheater
	m.TraySpec.PlateA = m.TraySpec.PlateB = m.TraySpec.PlateC 
		= m.TraySpec.PlateD = 10;
	m.TraySpec.PlateColumn = m.TraySpec.PlateRow = 3;

	GetSetting(csFile, "Preheater Spec", "Plate A", m.TraySpec.PlateA);
	GetSetting(csFile, "Preheater Spec", "Plate B", m.TraySpec.PlateB);
	GetSetting(csFile, "Preheater Spec", "Plate C", m.TraySpec.PlateC);
	GetSetting(csFile, "Preheater Spec", "Plate D", m.TraySpec.PlateD);
	GetSetting(csFile, "Preheater Spec", "Plate Column", m.TraySpec.PlateColumn);
	GetSetting(csFile, "Preheater Spec", "Plate Row", m.TraySpec.PlateRow);

	// Load Temperature
	GetSetting(csFile, "Temperature",	"High Temperature Enable",	m.TraySpec.Heating);
	GetSetting(csFile, "Temperature", "Cooling",					m.TraySpec.Cooling);

	// Sort Mode
	GetSetting(csFile, "Temperature", "Sort Mode",				 m.TraySpec.SortMode);	

	// Vision Pattern
	GetSetting(csFile, "Vision Pattern", "File",			m.TraySpec.VisionPatternName);
	GetSetting(csFile, "Mapping",		 "MappingFile",		m.TraySpec.MappingName);
	GetSetting(csFile, "Testing",		 "TestFile",		m.TraySpec.TestingName);

	// Ocr feature
	GetSetting(csFile, "Vision Pattern", "OCR File",		m.TraySpec.VisionOcrPatternName);

	//
	m.TraySpec.m_SubTrayColumn = 2;
	m.TraySpec.m_SubTrayRow = 5;
	GetSetting(csFile, "Sub Tray",		 "Sub Tray Column",		m.TraySpec.m_SubTrayColumn);
	GetSetting(csFile, "Sub Tray",		 "Sub Tray Row",		m.TraySpec.m_SubTrayRow);

	m.TraySpec.m_SubTrayA =	m.TraySpec.m_SubTrayB = 
		m.TraySpec.m_SubTrayC = m.TraySpec.m_SubTrayD = 3;
	GetSetting(csFile, "Sub Tray",		 "Sub Tray A",		m.TraySpec.m_SubTrayA);
	GetSetting(csFile, "Sub Tray",		 "Sub Tray B",		m.TraySpec.m_SubTrayB);
	GetSetting(csFile, "Sub Tray",		 "Sub Tray C",		m.TraySpec.m_SubTrayC);
	GetSetting(csFile, "Sub Tray",		 "Sub Tray D",		m.TraySpec.m_SubTrayD);

	m.TraySpec.m_SubChipTrayColumn = 12;
	m.TraySpec.m_SubChipTrayRow = 13;
	GetSetting(csFile, "Chip Tray",		 "Chip Tray Column",	m.TraySpec.m_SubChipTrayColumn);
	GetSetting(csFile, "Chip Tray",		 "Chip Tray Row",		m.TraySpec.m_SubChipTrayRow);


	m.TraySpec.m_SubChipTrayA = m.TraySpec.m_SubChipTrayB 
		= m.TraySpec.m_SubChipTrayC = m.TraySpec.m_SubChipTrayD = 2;
	GetSetting(csFile, "Chip Tray",		 "Chip Tray A",		m.TraySpec.m_SubChipTrayA);
	GetSetting(csFile, "Chip Tray",		 "Chip Tray B",		m.TraySpec.m_SubChipTrayB);
	GetSetting(csFile, "Chip Tray",		 "Chip Tray C",		m.TraySpec.m_SubChipTrayC);
	GetSetting(csFile, "Chip Tray",		 "Chip Tray D",		m.TraySpec.m_SubChipTrayD);

	m.TraySpec.m_InputUseChipTray =	m.TraySpec.m_OutputUseChipTray =
		m.TraySpec.m_FixUseChipTray = false;
	GetSetting(csFile, "Chip Tray Enable",		 "Chip Tray Input Enable",		m.TraySpec.m_InputUseChipTray);
	GetSetting(csFile, "Chip Tray Enable",		 "Chip Tray Output ENable",		m.TraySpec.m_OutputUseChipTray);
	GetSetting(csFile, "Chip Tray Enable",		 "Chip Tray Fix Enable",		m.TraySpec.m_FixUseChipTray);
}

void CFunction::SaveTraySpec()
{
	CString csFile;
	csFile = m.FilePath.TrayFilesPath + m.UI.FileMain;

	// Save TraySpec
	SaveSetting( csFile, "Tray Spec", "A",		m.TraySpec.A);
	SaveSetting( csFile, "Tray Spec", "B",		m.TraySpec.B);
	SaveSetting( csFile, "Tray Spec", "C",		m.TraySpec.C);
	SaveSetting( csFile, "Tray Spec", "D",		m.TraySpec.D);
	SaveSetting( csFile, "Tray Spec", "Column",	m.TraySpec.Column);
	SaveSetting( csFile, "Tray Spec", "Row",	m.TraySpec.Row);
	SaveSetting( csFile, "Tray Spec", "Thick Tray",		m.TraySpec.ThickTrayMode );
	SaveSetting( csFile, "Tray Spec", "Tray Height",	m.TraySpec.TrayHeight );	// 

	// Save Preheater
	SaveSetting(csFile, "Preheater Spec", "Plate A", m.TraySpec.PlateA);
	SaveSetting(csFile, "Preheater Spec", "Plate B", m.TraySpec.PlateB);
	SaveSetting(csFile, "Preheater Spec", "Plate C", m.TraySpec.PlateC);
	SaveSetting(csFile, "Preheater Spec", "Plate D", m.TraySpec.PlateD);
	SaveSetting(csFile, "Preheater Spec", "Plate Column", m.TraySpec.PlateColumn);
	SaveSetting(csFile, "Preheater Spec", "Plate Row", m.TraySpec.PlateRow);

	// Load Temperature
	SaveSetting(csFile, "Temperature", "High Temperature Enable",	m.TraySpec.Heating);
	SaveSetting(csFile, "Temperature", "Cooling",					m.TraySpec.Cooling);

	// Sort Mode
	SaveSetting(csFile, "Temperature", "Sort Mode",				 m.TraySpec.SortMode);	

	// Vision Pattern
	SaveSetting(csFile, "Vision Pattern", "File",			m.TraySpec.VisionPatternName);
	SaveSetting(csFile, "Mapping",		  "MappingFile",	m.TraySpec.MappingName);
	SaveSetting(csFile, "Testing",		  "TestFile",		m.TraySpec.TestingName);

	// Ocr feature
	SaveSetting(csFile, "Vision Pattern", "OCR File",		m.TraySpec.VisionOcrPatternName);


	// 
	SaveSetting(csFile, "Sub Tray",		 "Sub Tray Column",		m.TraySpec.m_SubTrayColumn);
	SaveSetting(csFile, "Sub Tray",		 "Sub Tray Row",		m.TraySpec.m_SubTrayRow);

	SaveSetting(csFile, "Sub Tray",		 "Sub Tray A",		m.TraySpec.m_SubTrayA);
	SaveSetting(csFile, "Sub Tray",		 "Sub Tray B",		m.TraySpec.m_SubTrayB);
	SaveSetting(csFile, "Sub Tray",		 "Sub Tray C",		m.TraySpec.m_SubTrayC);
	SaveSetting(csFile, "Sub Tray",		 "Sub Tray D",		m.TraySpec.m_SubTrayD);

	SaveSetting(csFile, "Chip Tray",		 "Chip Tray Column",	m.TraySpec.m_SubChipTrayColumn);
	SaveSetting(csFile, "Chip Tray",		 "Chip Tray Row",		m.TraySpec.m_SubChipTrayRow);

	SaveSetting(csFile, "Chip Tray",		 "Chip Tray A",		m.TraySpec.m_SubChipTrayA);
	SaveSetting(csFile, "Chip Tray",		 "Chip Tray B",		m.TraySpec.m_SubChipTrayB);
	SaveSetting(csFile, "Chip Tray",		 "Chip Tray C",		m.TraySpec.m_SubChipTrayC);
	SaveSetting(csFile, "Chip Tray",		 "Chip Tray D",		m.TraySpec.m_SubChipTrayD);

	SaveSetting(csFile, "Chip Tray Enable",		 "Chip Tray Input Enable",		m.TraySpec.m_InputUseChipTray);
	SaveSetting(csFile, "Chip Tray Enable",		 "Chip Tray Output ENable",		m.TraySpec.m_OutputUseChipTray);
	SaveSetting(csFile, "Chip Tray Enable",		 "Chip Tray Fix Enable",		m.TraySpec.m_FixUseChipTray);
}
void CFunction::LoadTemperatureSetting()
{
	CString csFile = _T("");
	csFile = m.FilePath.HeaterTempSetPath;

	GetSetting(csFile, "Heater", "Set Point",		m.m_West.dSetPoint);
	GetSetting(csFile, "Heater", "Stable Time",		m.m_West.dStableTime);
	GetSetting(csFile, "Heater", "Soak Time",		m.m_West.dSoakTime);
	GetSetting(csFile, "Heater", "Tolerance",		m.m_West.dTolerance);
}
void CFunction::SaveTemperatureSetting()
{
	CString csFile = _T("");
	csFile = m.FilePath.HeaterTempSetPath;

	SaveSetting(csFile, "Heater", "Set Point",		m.m_West.dSetPoint);
	SaveSetting(csFile, "Heater", "Stable Time",	m.m_West.dStableTime);
	SaveSetting(csFile, "Heater", "Soak Time",		m.m_West.dSoakTime);
	SaveSetting(csFile, "Heater", "Tolerance",		m.m_West.dTolerance);
}
/////////////////////////////////////////////////////
// Vision Setting function
void CFunction::LoadVisionSet()
{
	CString csFile = _T("");
	csFile = m.FilePath.SystemSettingPath;

	GetSetting(csFile, "Vision Setup", "Pick Dut(default)",	 m.m_VisionSet.lVisionPickDut = 1);
}
void CFunction::SaveVisionSet()
{
	CString csFile = _T("");
	csFile = m.FilePath.SystemSettingPath;

	SaveSetting(csFile, "Vision Setup", "Pick Dut(default)", m.m_VisionSet.lVisionPickDut);
}
/////////////////////////////////////////////////////
// TS Torque function
void CFunction::LoadTorqueToolSet()
{
	CString csFile = _T("");
	csFile = m.FilePath.SystemSettingPath;

	GetSetting( csFile, "Ts Torque Debug", "a Value",	m.m_TorqueToolSet.daValue );		// 
	GetSetting( csFile, "Ts Torque Debug", "b Value",	m.m_TorqueToolSet.dbValue );		// 
}
void CFunction::SaveTorqueToolSet()
{
	CString csFile = _T("");
	csFile = m.FilePath.SystemSettingPath;

	SaveSetting( csFile, "Ts Torque Debug", "a Value",	m.m_TorqueToolSet.daValue );		// 
	SaveSetting( csFile, "Ts Torque Debug", "b Value",	m.m_TorqueToolSet.dbValue );		// 
}
/////////////////////////////////////////////////////
// TS Floating function
void CFunction::LoadTsFolatingConvert()
{
	CString csFile = _T("");
	csFile = m.FilePath.UIPath;
	GetSetting( csFile, "Ts Floating Convert", "Kg to Volt",	m.m_TsFolatingConvert.dTsFloatingConvert = 0.111 );		// 
}
void CFunction::SaveTsFloatingConvert()
{
	CString csFile = _T("");
	csFile = m.FilePath.UIPath;
	SaveSetting( csFile, "Ts Floating Convert", "Kg to Volt",	m.m_TsFolatingConvert.dTsFloatingConvert );		// 
}
/////////////////////////////////////////////////////
// TS Remain IC function
void CFunction::LoadTSRemainICParameter()
{
	CString csFile;
	csFile = m.FilePath.TSRemainICParamPath;

	GetSetting( csFile, "TS Remain IC Condition", "Vacc On",			m.m_TSRemainICParameter.dTSRemainICVacc = 3 );		// 
	GetSetting( csFile, "TS Remain IC Condition", "Speed",				m.m_TSRemainICParameter.iTSRemainICSpeed = 40 );	// 
	GetSetting( csFile, "TS Remain IC Condition", "Vacc On Condition",  m.m_TSRemainICParameter.iTSRemainICAlwaysOn = 1);	// 
}
void CFunction::SaveTSRemainICParameter()
{
	CString csFile;
	csFile = m.FilePath.TSRemainICParamPath;

	SaveSetting( csFile, "TS Remain IC Condition", "Vacc On",				m.m_TSRemainICParameter.dTSRemainICVacc );		// 
	SaveSetting( csFile, "TS Remain IC Condition", "Vacc On Condition",		m.m_TSRemainICParameter.iTSRemainICAlwaysOn );	// 
	SaveSetting( csFile, "TS Remain IC Condition", "Speed",					m.m_TSRemainICParameter.iTSRemainICSpeed );	//
}
/////////////////////////////////////////////////////
// Alignment function
void CFunction::SaveAlignment()
{
	CString cs, csFile;
	csFile = m.FilePath.AlignmentPath;

	// Store Alignment current time.
	CTime time = CTime::GetCurrentTime();
	CString T;
	T.Format("%d.%d.%d.%d.%d", time.GetYear(), time.GetMonth(), time.GetDay(), time.GetHour(), time.GetMinute() );
	SaveSetting(csFile , "Alignment Time", "Modify Time",	T );

	// Input
	SaveSetting(csFile , "Alignment", "Input stack x",		m.m_Align.Input.x );
	SaveSetting(csFile , "Alignment", "Input stack y",		m.m_Align.Input.y );
	SaveSetting(csFile , "Alignment", "Input stack z",		m.m_Align.Input.z );
	SaveSetting(csFile , "Alignment", "Input stack z2",		m.m_Align.Input.z2 );

	// Output 
	SaveSetting(csFile , "Alignment", "Output1 stack x",	m.m_Align.Output1.x );
	SaveSetting(csFile , "Alignment", "Output1 stack y",	m.m_Align.Output1.y );
	SaveSetting(csFile , "Alignment", "Output1 stack z",	m.m_Align.Output1.z );
	SaveSetting(csFile , "Alignment", "Output1 stack z2",	m.m_Align.Output1.z2 );

	// Rotator
	SaveSetting(csFile , "Alignment", "Rotator x",			m.m_Align.Rotator.x );
	SaveSetting(csFile , "Alignment", "Rotator y",			m.m_Align.Rotator.y );
	SaveSetting(csFile , "Alignment", "Rotator z",			m.m_Align.Rotator.z );		// pick
	SaveSetting(csFile , "Alignment", "Rotator z2",			m.m_Align.Rotator.z2 );		// place

	// Socket
	SaveSetting(csFile , "Alignment", "Socket x",			m.m_Align.Socket.x );
	SaveSetting(csFile , "Alignment", "Socket y",			m.m_Align.Socket.y );
	SaveSetting(csFile , "Alignment", "Socket z",			m.m_Align.Socket.z );
	SaveSetting(csFile , "Alignment", "Socket z2",			m.m_Align.Socket.z2 );

	// Shuttle Input / Output 
	SaveSetting(csFile , "Alignment", "Shuttle x",			m.m_Align.Shuttle.x );
	SaveSetting(csFile , "Alignment", "Shuttle y",			m.m_Align.Shuttle.y );
	SaveSetting(csFile , "Alignment", "Shuttle z",			m.m_Align.Shuttle.z );
	SaveSetting(csFile , "Alignment", "Shuttle z2",			m.m_Align.Shuttle.z2 );
	// In
	SaveSetting(csFile , "Alignment", "Shuttle In x",		m.m_Align.DutIn.x );
	SaveSetting(csFile , "Alignment", "Shuttle In y",		m.m_Align.DutIn.y );
	SaveSetting(csFile , "Alignment", "Shuttle In z",		m.m_Align.DutIn.z );
	SaveSetting(csFile , "Alignment", "Shuttle In z2",		m.m_Align.DutIn.z2 );
	// Out
	SaveSetting(csFile , "Alignment", "Shuttle Out x",		m.m_Align.DutOut.x );
	SaveSetting(csFile , "Alignment", "Shuttle Out y",		m.m_Align.DutOut.y );
	SaveSetting(csFile , "Alignment", "Shuttle Out z",		m.m_Align.DutOut.z );
	SaveSetting(csFile , "Alignment", "Shuttle Out z2",		m.m_Align.DutOut.z2 );
	// Test site.
	SaveSetting(csFile , "Alignment", "Test site home",		m.m_Align.TestSite.home );
	SaveSetting(csFile , "Alignment", "Test site contact",	m.m_Align.TestSite.contact );
	SaveSetting(csFile , "Alignment", "Test site pick",		m.m_Align.TestSite.pick );
	SaveSetting(csFile , "Alignment", "Test site place",	m.m_Align.TestSite.place );
}
void CFunction::LoadAlignment()
{
	CString cs, csFile;
	csFile = m.FilePath.AlignmentPath;

	CString T;
	SaveSetting(csFile , "Alignment Time", "Modify Time",	T );

	// Input
	GetSetting(csFile , "Alignment", "Input stack x",		m.m_Align.Input.x );
	GetSetting(csFile , "Alignment", "Input stack y",		m.m_Align.Input.y );
	GetSetting(csFile , "Alignment", "Input stack z",		m.m_Align.Input.z );
	GetSetting(csFile , "Alignment", "Input stack z2",		m.m_Align.Input.z2 );

	// Output 1
	GetSetting(csFile , "Alignment", "Output1 stack x",		m.m_Align.Output1.x );
	GetSetting(csFile , "Alignment", "Output1 stack y",		m.m_Align.Output1.y );
	GetSetting(csFile , "Alignment", "Output1 stack z",		m.m_Align.Output1.z );
	GetSetting(csFile , "Alignment", "Output1 stack z2",	m.m_Align.Output1.z2 );

	// Rotator
	GetSetting(csFile , "Alignment", "Rotator x",			m.m_Align.Rotator.x );
	GetSetting(csFile , "Alignment", "Rotator y",			m.m_Align.Rotator.y );
	GetSetting(csFile , "Alignment", "Rotator z",			m.m_Align.Rotator.z );
	GetSetting(csFile , "Alignment", "Rotator z2",			m.m_Align.Rotator.z2 );

	// Socket
	GetSetting(csFile , "Alignment", "Socket x",			m.m_Align.Socket.x );
	GetSetting(csFile , "Alignment", "Socket y",			m.m_Align.Socket.y );
	GetSetting(csFile , "Alignment", "Socket z",			m.m_Align.Socket.z );
	GetSetting(csFile , "Alignment", "Socket z2",			m.m_Align.Socket.z2 );

	// Shuttle Input / Output 
	GetSetting(csFile , "Alignment", "Shuttle x",			m.m_Align.Shuttle.x );
	GetSetting(csFile , "Alignment", "Shuttle y",			m.m_Align.Shuttle.y );
	GetSetting(csFile , "Alignment", "Shuttle z",			m.m_Align.Shuttle.z );
	GetSetting(csFile , "Alignment", "Shuttle z2",			m.m_Align.Shuttle.z2 );
	// In
	GetSetting(csFile , "Alignment", "Shuttle In x",		m.m_Align.DutIn.x );
	GetSetting(csFile , "Alignment", "Shuttle In y",		m.m_Align.DutIn.y );
	GetSetting(csFile , "Alignment", "Shuttle In z",		m.m_Align.DutIn.z );
	GetSetting(csFile , "Alignment", "Shuttle In z2",		m.m_Align.DutIn.z2 );
	// Out
	GetSetting(csFile , "Alignment", "Shuttle Out x",		m.m_Align.DutOut.x );
	GetSetting(csFile , "Alignment", "Shuttle Out y",		m.m_Align.DutOut.y );
	GetSetting(csFile , "Alignment", "Shuttle Out z",		m.m_Align.DutOut.z );
	GetSetting(csFile , "Alignment", "Shuttle Out z2",		m.m_Align.DutOut.z2 );

	// Test site.
	GetSetting(csFile , "Alignment", "Test site home",		m.m_Align.TestSite.home );
	GetSetting(csFile , "Alignment", "Test site contact",	m.m_Align.TestSite.contact );
	GetSetting(csFile , "Alignment", "Test site pick",		m.m_Align.TestSite.pick );
	GetSetting(csFile , "Alignment", "Test site place",		m.m_Align.TestSite.place );
}

/////////////////////////////////////////////////////
// Password function
void CFunction::SavePassword()
{
	CString cs, csFile;
//	csFile = ".\\System\\3110.id";
	csFile = m.FilePath.PasswordPath;

	// Load System Name & Password
	CString csSetupPw = m.UI.PasswordSetup;
	Encryption(&csSetupPw);
	SaveSetting(csFile, "Password", "Setup Page", csSetupPw);

	CString csEngineerPw = m.UI.PasswordEngineer;
	Encryption(&csEngineerPw);
	SaveSetting(csFile, "Password", "Engineer Page", csEngineerPw);

	CString csDebugPw = m.UI.PasswordDebug;
	Encryption(&csDebugPw);
	SaveSetting(csFile, "Password", "Debug Page", csDebugPw);
}

void CFunction::LoadPassword()
{
	CString cs, csFile;
//	csFile = ".\\System\\3111.id";
	csFile = m.FilePath.PasswordPath;

//	m.UI.PasswordSetup = "3111";
	Encryption(&m.UI.PasswordSetup);
	GetSetting(csFile, "Password", "Setup Page",  m.UI.PasswordSetup);
	Decryption(&m.UI.PasswordSetup);
	
//	m.UI.PasswordEngineer = "ovt";
	Encryption(&m.UI.PasswordEngineer);
	GetSetting(csFile, "Password", "Engineer Page", m.UI.PasswordEngineer);
	Decryption(&m.UI.PasswordEngineer);

//	m.UI.PasswordDebug = "task";
	Encryption(&m.UI.PasswordDebug);
	GetSetting(csFile, "Password", "Debug Page", m.UI.PasswordDebug);
	Decryption(&m.UI.PasswordDebug);

//	m.UI.PasswordSuperUser = "3111";
}
/////////////////////////////////////////////////////
// GearRation
void CFunction::SaveGearRationParameter()
{
	CString cs, csFile;
	csFile = m.FilePath.SystemSettingPath;
	
	SaveSetting(csFile, "Gear Ration", "X GearRation",			m.m_Ratio.X_GearRation );
	SaveSetting(csFile, "Gear Ration", "Y GearRation",			m.m_Ratio.Y_GearRation );
	SaveSetting(csFile, "Gear Ration", "Z GearRation",			m.m_Ratio.Z_GearRation );  
	SaveSetting(csFile, "Gear Ration", "Inserter GearRation",	m.m_Ratio.Inserter_GearRation );  
}
void CFunction::LoadGearRationParameter()
{
	CString cs, csFile;
	csFile = m.FilePath.SystemSettingPath;
	
	GetSetting(csFile, "Gear Ration", "X GearRation",			m.m_Ratio.X_GearRation );
	GetSetting(csFile, "Gear Ration", "Y GearRation",			m.m_Ratio.Y_GearRation );
	GetSetting(csFile, "Gear Ration", "Z GearRation",			m.m_Ratio.Z_GearRation );  
	GetSetting(csFile, "Gear Ration", "Inserter GearRation",	m.m_Ratio.Inserter_GearRation );
}
/////////////////////////////////////////////////////
// Site setting
void CFunction::LoadSiteSetting()
{
	CString csFile = _T("");
	csFile = m.FilePath.TrayFilesPath + m.UI.FileMain;

	m.Site.dDemoTestTime = 5.0;
	// Set default

	m.Site.iRunMode = theApp.enOnLine; // default value for start up.
	// 預設是 OnLine 如果有被啟動儲存功能, 我們才真的讀出資料.

	GetSetting(csFile, "Site Setting", "Demo Test Time",			m.Site.dDemoTestTime);
	GetSetting(csFile, "Site Setting", "Dummy Bin For Catorgy",		m.Site.iSiteDummyBinForCatorgy );
	GetSetting(csFile, "Site Setting", "Dummy Bin For Catorgy2",	m.Site.csSiteDummyBinForCatorgy );

	if( m.Setting.m_bEnableSaveSiteSetting == 1 )
		GetSetting(csFile, "Site Setting", "Site Setting", m.Site.iRunMode );
}
void CFunction::SaveSiteSetting()
{
	CString csFile = _T("");
	csFile = m.FilePath.TrayFilesPath + m.UI.FileMain;

	SaveSetting(csFile, "Site Setting", "Demo Test Time",				m.Site.dDemoTestTime );
	SaveSetting(csFile, "Site Setting", "Dummy Bin For Catorgy",		m.Site.iSiteDummyBinForCatorgy );
	SaveSetting(csFile, "Site Setting", "Dummy Bin For Catorgy2",		m.Site.csSiteDummyBinForCatorgy );

	if( m.Setting.m_bEnableSaveSiteSetting == 1 )
		SaveSetting(csFile, "Site Setting", "Site Setting", m.Site.iRunMode );
}


////////////////////////////////////////////////////
// System Control 
void CFunction::ShutDown()
{
	m.Info.bRunning = false;

	while(m.Info.iThreadCount > 0)
		f.ThreadWait();

	f.m_Log.AddEvent(enCodeSystemShutDown);		
}
/////////////////////////////////////////////////////
// SLT Function.
void CFunction::LoadSLT()
{

}
void CFunction::SaveSLT()
{

}
/////////////////////////////////////////////////////
// Pogo Pin Parameter
void CFunction::SavePogoParameter()
{
	CString csFile;
	csFile = m.FilePath.TrayFilesPath + m.UI.FileMain;

	SaveSetting(csFile, "Ts Floating", "Pogo Counter",		m.m_TsFolatingParameter.iPogoCount );
	SaveSetting(csFile, "Ts Floating", "Pogo Force(g.)",	m.m_TsFolatingParameter.iPogoForce );
	SaveSetting(csFile, "Ts Floating", "Pogo Force(kgf.)",	m.m_TsFolatingParameter.iPogoTorqueForce );
}
void CFunction::LoadPogoParameter()
{
	CString csFile;
	csFile = m.FilePath.TrayFilesPath + m.UI.FileMain;

	GetSetting(csFile, "Ts Floating", "Pogo Counter",		m.m_TsFolatingParameter.iPogoCount = 0 );
	GetSetting(csFile, "Ts Floating", "Pogo Force(g.)",		m.m_TsFolatingParameter.iPogoForce = 0 );
	GetSetting(csFile, "Ts Floating", "Pogo Force(kgf.)",	m.m_TsFolatingParameter.iPogoTorqueForce = 2 );
/*
	// Reset Torque For Tray File
	if( m.m_TsFolatingParameter.iPogoCount != 0 && 
		m.m_TsFolatingParameter.iPogoForce != 0 )
	{
		double dTorqueValue = 0.0;
		dTorqueValue = ( m.m_TsFolatingParameter.iPogoCount * m.m_TsFolatingParameter.iPogoForce );
		dTorqueValue = dTorqueValue * m.m_TsFolatingConvert.dTsFloatingConvert;
		theApp.m_tIORemote.SetTorqueValue( dTorqueValue );	
	}
*/

	if( m.UI.FileMain != "" )
	{
		if( m.m_TsFolatingParameter.iPogoTorqueForce != 0 )
		{
			double dTorqueValue = m.m_TsFolatingParameter.iPogoTorqueForce;
			double m_dTorque = ( dTorqueValue - m.m_TorqueToolSet.dbValue ) / m.m_TorqueToolSet.daValue;
			m_dTorque = m_dTorque * 20;
			theApp.m_tIORemote.SetTorqueValue( m_dTorque );
		}
	}
}
/////////////////////////////////////////////////////
// Speed
void CFunction::SaveSpeed()
{
	CString csFile;
	csFile = m.FilePath.TrayFilesPath + m.UI.FileMain;

	SaveSetting(csFile, "Speed Parameter", "ArmX",			m.m_Motor.ArmX.Speed);	
	SaveSetting(csFile, "Speed Parameter", "ArmY",			m.m_Motor.ArmY.Speed);
	SaveSetting(csFile, "Speed Parameter", "ArmZ",			m.m_Motor.ArmZ.Speed);
	SaveSetting(csFile, "Speed Parameter", "Inserter",		m.m_Motor.Inserter.Speed);
}
void CFunction::LoadSpeed()
{
	CString csFile;
	csFile = m.FilePath.TrayFilesPath + m.UI.FileMain;

	GetSetting(csFile, "Speed Parameter", "ArmX",			m.m_Motor.ArmX.Speed = 10);	
	GetSetting(csFile, "Speed Parameter", "ArmY",			m.m_Motor.ArmY.Speed = 10);
	GetSetting(csFile, "Speed Parameter", "ArmZ",			m.m_Motor.ArmZ.Speed = 10);
	GetSetting(csFile, "Speed Parameter", "Inserter",		m.m_Motor.Inserter.Speed = 10);
}

/////////////////////////////////////////////////////
// Setting
void CFunction::SaveSetting()
{
	CString csFile = _T("");
	csFile = m.FilePath.SystemSettingPath;

	SaveSetting(csFile, "Setting", "Auto Skip",			m.TraySkip.AutoSkip );
	SaveSetting(csFile, "Setting", "Test Site Vacc",	m.TraySkip.TestSiteVacc );
}
void CFunction::LoadSetting()
{
	CString csFile = _T("");
	csFile = m.FilePath.SystemSettingPath;

	GetSetting(csFile, "Setting", "Auto Skip",	m.TraySkip.AutoSkip );
	GetSetting(csFile, "Setting", "Test Site Vacc",	m.TraySkip.TestSiteVacc );
}

/////////////////////////////////////////////////////
// Timer
void CFunction::SaveTimer()
{
	CString csFile;
	csFile = m.FilePath.TrayFilesPath + m.UI.FileMain;

	SaveSetting(csFile, "Timer", "InsertPuff",	m.Timer.m_dInsertPuff);	
	SaveSetting(csFile, "Timer", "InsertPick",	m.Timer.m_dInsertPick);
	SaveSetting(csFile, "Timer", "Pick",		m.Timer.m_dPickPuff);
	SaveSetting(csFile, "Timer", "Place",		m.Timer.m_dPickPick);
}
void CFunction::LoadTimer()
{
	CString csFile;
	csFile = m.FilePath.TrayFilesPath + m.UI.FileMain;

	GetSetting(csFile, "Timer", "InsertPuff",	m.Timer.m_dInsertPuff);	
	GetSetting(csFile, "Timer", "InsertPick",	m.Timer.m_dInsertPick);
	GetSetting(csFile, "Timer", "Pick",			m.Timer.m_dPickPuff);
	GetSetting(csFile, "Timer", "Place",		m.Timer.m_dPickPick);	
}
/////////////////////////////////////////////////////
// Yield Control
void CFunction::LoadYield()
{
	CString csFile;
	csFile = m.FilePath.TrayFilesPath + m.UI.FileMain;
	
	// Enable Or Disable
//	GetSetting(csFile, "Yield", "Yield Control Enable", m.YieldSetting.bYieldControlEnable = 1);
//	GetSetting(csFile, "Yield", "Continue Fail Enable", m.YieldSetting.bContinueFailEnable = 1);
//	GetSetting(csFile, "Yield", "Fail Count", m.YieldSetting.iFailCount = 10);
//	GetSetting(csFile, "Yield", "Retest Count", m.YieldSetting.iRetestCount = 1);

	GetSetting(csFile, "Yield", "Yield Control Enable", m.YieldSetting.bYieldControlEnable = 0);
	GetSetting(csFile, "Yield", "Continue Fail Enable", m.YieldSetting.bContinueFailEnable = 0);
	GetSetting(csFile, "Yield", "Fail Count", m.YieldSetting.iFailCount = 10);
	GetSetting(csFile, "Yield", "Retest Count", m.YieldSetting.iRetestCount = 0);
	GetSetting(csFile, "Yield", "Yield Limitation", m.YieldSetting.dYieldLimit = 95.0);
	GetSetting(csFile, "Yield", "Yield Window", m.YieldSetting.iYieldWindow = 200);
	GetSetting(csFile, "Yield", "Drop Mode", m.YieldSetting.bDropMode = 1);
	GetSetting(csFile, "Yield", "Drop High", m.YieldSetting.dDropHigh = 5.0);
	GetSetting(csFile, "Yield", "Drop Timer", m.YieldSetting.dDropTimer = 1.0);
}
void CFunction::SaveYield()
{
	CString csFile;
	csFile = m.FilePath.TrayFilesPath + m.UI.FileMain;

	// Enable Or Disable
	SaveSetting(csFile, "Yield", "Yield Control Enable", m.YieldSetting.bYieldControlEnable );
	SaveSetting(csFile, "Yield", "Continue Fail Enable", m.YieldSetting.bContinueFailEnable );

	SaveSetting(csFile, "Yield", "Yield Limitation", m.YieldSetting.dYieldLimit );
	SaveSetting(csFile, "Yield", "Yield Window", m.YieldSetting.iYieldWindow );

	SaveSetting(csFile, "Yield", "Fail Count", m.YieldSetting.iFailCount );
	SaveSetting(csFile, "Yield", "Retest Count", m.YieldSetting.iRetestCount );

	SaveSetting(csFile, "Yield", "Drop Mode", m.YieldSetting.bDropMode);
	SaveSetting(csFile, "Yield", "Drop High", m.YieldSetting.dDropHigh);
	SaveSetting(csFile, "Yield", "Drop Timer", m.YieldSetting.dDropTimer);
}
/////////////////////////////////////////////////////
// Timer setting
void CFunction::SaveTimerSetting()
{
	CString csFile;
	csFile = m.FilePath.SystemSettingPath;

	SaveSetting(csFile, "Timer", "InitialEachMotorWaitTime", m.TimerSetting.iInitialEachMotorWaitTime);	
	SaveSetting(csFile, "Timer", "MotorRunlineTimeout",		 m.TimerSetting.iMotorRunlineTimeout);
	SaveSetting(csFile, "Timer", "MotorRunTimeout",			 m.TimerSetting.iMotorRunTimeout);
	SaveSetting(csFile, "Timer", "MotorZWaitTime",			 m.TimerSetting.iInitialZMotorWaitTime);	
	SaveSetting(csFile, "Timer", "Initial Timeout",			 m.TimerSetting.iInitialTimeout);
	SaveSetting(csFile, "Timer", "Commection Timeout",		 m.TimerSetting.iCommectionTimeout);
	SaveSetting(csFile, "Timer", "BinLog Timeout",			 m.TimerSetting.iBinLogInsertTimeout);
	SaveSetting(csFile, "Timer", "Scan Tray",				 m.TimerSetting.iScanTrayStatus);
	SaveSetting(csFile, "Timer", "Arm Z Check Timer",		 m.TimerSetting.iArmZCheckTime);	
	SaveSetting(csFile, "Timer", "Rotator Timer",			 m.TimerSetting.iRotatorTime );	
	SaveSetting(csFile, "Timer", "Rotator Timeout",			 m.TimerSetting.iRotatorTimeout );	
	SaveSetting(csFile, "Timer", "Shuttle Pick Timeout",	 m.TimerSetting.iShuttlePickTimeout );
	SaveSetting(csFile, "Timer", "Shuttle Home Timeout",	 m.TimerSetting.iShuttleHomeTimeout );
	SaveSetting(csFile, "Timer", "Shuttle Move Stable Time", m.TimerSetting.iShuttleStableTime );

}
void CFunction::LoadTimerSetting()
{
	CString csFile;
	csFile = m.FilePath.SystemSettingPath;

	GetSetting(csFile, "Timer", "InitialEachMotorWaitTime", m.TimerSetting.iInitialEachMotorWaitTime);
	GetSetting(csFile, "Timer", "MotorRunlineTimeout",		m.TimerSetting.iMotorRunlineTimeout);
	GetSetting(csFile, "Timer", "MotorRunTimeout",			m.TimerSetting.iMotorRunTimeout);
	GetSetting(csFile, "Timer", "MotorZWaitTime",			m.TimerSetting.iInitialZMotorWaitTime);
	GetSetting(csFile, "Timer", "Initial Timeout",			m.TimerSetting.iInitialTimeout);
	GetSetting(csFile, "Timer", "Commection Timeout",		m.TimerSetting.iCommectionTimeout);
	GetSetting(csFile, "Timer", "BinLog Timeout",			m.TimerSetting.iBinLogInsertTimeout);
	GetSetting(csFile, "Timer", "Scan Tray",				m.TimerSetting.iScanTrayStatus);
	GetSetting(csFile, "Timer", "Arm Z Check Timer",		m.TimerSetting.iArmZCheckTime);
	GetSetting(csFile, "Timer", "Rotator Timer",			m.TimerSetting.iRotatorTime );	
	GetSetting(csFile, "Timer", "Rotator Timeout",			m.TimerSetting.iRotatorTimeout );
	GetSetting(csFile, "Timer", "Shuttle Pick Timeout",		m.TimerSetting.iShuttlePickTimeout );
	GetSetting(csFile, "Timer", "Shuttle Home Timeout",		m.TimerSetting.iShuttleHomeTimeout );
	GetSetting(csFile, "Timer", "Shuttle Move Stable Time", m.TimerSetting.iShuttleStableTime );
}

/////////////////////////////////////////////////////
// System setting
void CFunction::SaveSystemSetting()
{
	CString csFile;
	csFile = m.FilePath.SystemSettingPath;
	
	SaveSetting(csFile, "Setting", "Enavle Door Sensor",				m.Setting.m_bEnableDoorSensor );
	SaveSetting(csFile, "Setting", "Enable Alarm",						m.Setting.m_bEnableAlarm );
	SaveSetting(csFile, "Setting", "EnalbeIOMonitorRecovery",			m.Setting.m_bByPassEnableIORecovery );
	SaveSetting(csFile, "Setting", "EbableSaveSiteSetting",				m.Setting.m_bEnableSaveSiteSetting );
	SaveSetting(csFile, "Setting", "Set By Mode",						m.Setting.m_bSetByMode );	

	// Rotator
	SaveSetting(csFile, "Setting", "Enable SLT Rotota",					m.Setting.m_bRotatoUse );
	SaveSetting(csFile, "Setting", "Enable Rotator Pre-Guide",			m.Setting.m_bEnableRotatorPreGuide );
	SaveSetting(csFile, "Setting", "Enable Rotator 180",				m.Setting.m_bEnableRotatorTurn );

	// CCD
	SaveSetting(csFile, "Setting", "Enable CCD Pin1",					m.Setting.m_bEnableCCDPin1 );
	SaveSetting(csFile, "Setting", "Enable CCD Socket",					m.Setting.m_bEnableCCDSocket );
	SaveSetting(csFile, "Setting", "Enable CCD Log IC",					m.Setting.m_bEnableCCDLogICImage );

	// Remote Control
	SaveSetting(csFile, "Setting", "Enable Remote Control",				m.Setting.m_bEnableRemoteControl );
	
	// Lot Information Progress
	SaveSetting(csFile, "Setting", "Enable Lot Progress",				m.Setting.m_bEnableLotDoneProgress );

	// Remote IO
	SaveSetting(csFile, "Setting", "Enable Remote IO",					m.Setting.m_bEnableRemoteIO );

	// Module
	SaveSetting(csFile, "Setting", "Enable ATC Module",					m.Setting.m_bEnableATCModule );
	SaveSetting(csFile, "Setting", "Enable PTC Module",					m.Setting.m_bEnablePTCModule );
	SaveSetting(csFile, "Setting", "Enable Heater Module",				m.Setting.m_bEnableHeaterModule );
	SaveSetting(csFile, "Setting", "Enable TriTemp Module",				m.Setting.m_bEnableTriTempModule );
	SaveSetting(csFile, "Setting", "Enable Remote Module",				m.Setting.m_bEnableRemoteModule );

	// Log
	SaveSetting(csFile, "Setting", "Enable UPH Log",					m.Setting.m_bEnableUPHLog );
	SaveSetting(csFile, "Setting", "Enable Comm Log",					m.Setting.m_bEnableCommLog );
	SaveSetting(csFile, "Setting", "Enable SingleMotor Log",			m.Setting.m_bEnableSingleMotorLog );
	SaveSetting(csFile, "Setting", "Enable DualMotor Log",				m.Setting.m_bEnableDualMotorLog );
	SaveSetting(csFile, "Setting", "Enable Motor Log",					m.Setting.m_bEnableMotorLog );
	SaveSetting(csFile, "Setting", "Enable Status Report Log",			m.Setting.m_bEnableStatusReportLog );
	SaveSetting(csFile, "Setting", "Enable CCD Socket Log",				m.Setting.m_bEnableCCDSocketLog );
	SaveSetting(csFile, "Setting", "Enable Jam Rate Log",				m.Setting.m_bEnableJamRateReport );
	SaveSetting(csFile, "Setting", "Enable Shuttle Jam Log",			m.Setting.m_bEnableShuttleJamLog );

	// ByPass
	SaveSetting(csFile, "Setting", "ByPassTestSiteVacc",				m.Setting.m_bByPassTestVacc );
	SaveSetting(csFile, "Setting", "ByPassRotatorAlarm",				m.Setting.m_bByPassRotatorAlarm );
	SaveSetting(csFile, "Setting", "ByPassVacc",						m.Setting.m_bByPassVacc );	
	SaveSetting(csFile, "Setting", "ByPassTrayInPos",					m.Setting.m_bByPassTrayInPos );	
	SaveSetting(csFile, "Setting", "ByPassShuttle",						m.Setting.m_bByPassShuttleAlarm );	

	// Function
	SaveSetting(csFile, "Setting", "Simplified Chinese",				m.Setting.m_bEnableSimplified );
	
	// System Setting 
	SaveSetting(csFile, "Setting", "Speed Low Limit",					m.Setting.m_iSpeedLowLimit );		
	SaveSetting(csFile, "Setting", "Speed High Limit",					m.Setting.m_iSpeedHighLimit );		
	SaveSetting(csFile, "Setting", "Offset Low Limit",					m.Setting.m_dOffsetLowLimit );
	SaveSetting(csFile, "Setting", "Offset High Limit",					m.Setting.m_dOffsetHighLimit );	
	SaveSetting(csFile, "Setting", "Timer Low Limit",					m.Setting.m_dTimerLowLimit );
	SaveSetting(csFile, "Setting", "Timer High Limit",					m.Setting.m_dTimerHighLimit );
	SaveSetting(csFile, "Setting", "Timeout Low Limit",					m.Setting.m_dTimeoutLowLimit );
	SaveSetting(csFile, "Setting", "Timeout High Limit",				m.Setting.m_dTimeoutHighLimit );
	
	// Buzzer Auto Close
	SaveSetting(csFile, "Setting", "Buzzer Auto Close",					m.Setting.m_dBuzzerAutoClose );

	// Tray Map UI
	SaveSetting(csFile, "Setting", "Tray Left",							m.Setting.m_dTraySpecLeftSide );
	SaveSetting(csFile, "Setting", "Tray Top",							m.Setting.m_dTraySpecTopSide );	
	SaveSetting(csFile, "Setting", "Tray IC Side",						m.Setting.m_dTraySpecICSide );	
	SaveSetting(csFile, "Setting", "Tray Text Up Side",					m.Setting.m_dTraySpecTextUpSide );	
	SaveSetting(csFile, "Setting", "Tray Text Left Side",				m.Setting.m_dTraySpecTextLeftSide );
	SaveSetting(csFile, "Setting", "Tray Text Size",					m.Setting.m_iTraySpecTextSize );
	SaveSetting(csFile, "Setting", "Tray Text Break",					m.Setting.m_iTraySpecTextBreak );
	SaveSetting(csFile, "Setting", "Tray Bk Color",						m.Setting.m_iTraySpecBkColor );
	//
	SaveSetting(csFile, "Setting", "Show Contact Counter",				m.Setting.m_bShowContactCounter );
	SaveSetting(csFile, "Setting", "Show Summary Report",				m.Setting.m_bSummaryReport );
	SaveSetting(csFile, "Setting", "Chip Tray",							m.Setting.m_bEnableChipTray );
	SaveSetting(csFile, "Setting", "Alarm Mail",						m.Setting.m_bCustomAlarmMail );	
	SaveSetting(csFile, "Setting", "Initial Pre Move",					m.Setting.m_bInitialPreMove );	
	SaveSetting(csFile, "Setting", "Initial Pre Move Distance",			m.Setting.m_iInitialPreMoveDistance );
	SaveSetting(csFile, "Setting", "Test Site Standy Position",			m.Setting.m_dTestSiteStandbyPosition );
	SaveSetting(csFile, "Setting", "Test Site Standy Position Socket",	m.Setting.m_dTestSiteSocketStandyPos );
	//
	SaveSetting(csFile, "Setting", "Standy X Move Distance",			m.Setting.m_dStandyX );
	SaveSetting(csFile, "Setting", "Standy Y Move Distance",			m.Setting.m_dStandyY );

	SaveSetting(csFile, "Setting", "Test Site Standby Shuttle",			m.Setting.m_iTestSiteStandByDistance );
	SaveSetting(csFile, "Setting", "Arm Z Auot Retry",					m.Setting.m_bArmZAutoRetry );
	SaveSetting(csFile, "Setting", "TS Remain IC",						m.Setting.m_bEnableTSRemainIC );
	SaveSetting(csFile, "Setting", "ION Alarm",							m.Setting.m_bIONAlarm );
	SaveSetting(csFile, "Setting", "PreMove",							m.Setting.m_bPreMove );
	SaveSetting(csFile, "Setting", "PreMove Distance",					m.Setting.m_iPreMoveDistance );		

	//
	SaveSetting(csFile, "Setting", "Enable IC Missing Detect",			m.Setting.m_bEnableICMissingDetect );
	SaveSetting(csFile, "Setting", "Enable Input Tray Tips",			m.Setting.m_bInputTrayTips );
	SaveSetting(csFile, "Setting", "Enable Input Tray Number",			m.Setting.m_bInputTrayTipsNumber );
	SaveSetting(csFile, "Setting", "Enable Input Tray Info",			m.Setting.m_bInputTrayInfo );
	SaveSetting(csFile, "Setting", "Enable Remote Control Input",		m.Setting.m_bRemoteCustomInput );
	SaveSetting(csFile, "Setting", "Enable Torque Control",				m.Setting.m_bEnableTorqueCtrl );
	SaveSetting(csFile, "Setting", "Enable Torque Status",				m.Setting.m_bEnableTorqueStatus );
	SaveSetting(csFile, "Setting", "Enable Double Check",				m.Setting.m_bCancelDoubleChkChange );
	SaveSetting(csFile, "Setting", "Enable Show Handler Status",		m.Setting.m_bShowHandlerStatus );
	SaveSetting(csFile, "Setting", "Repeat Tray Maxium",				m.Setting.m_iRepeatMaxiumValue );
	SaveSetting(csFile, "Setting", "Enable Auto Sel TrayFile",			m.Setting.m_bEnableAutoSelLastTrayFile );
	SaveSetting(csFile, "Setting", "Enable Auto Copy Last Lot",			m.Setting.m_bEnableAutoCopyLastLotInfo );

	//
}

void CFunction::LoadSystemSetting()
{
	CString csFile;
	csFile = m.FilePath.SystemSettingPath;

	GetSetting(csFile, "Setting", "Enavle Door Sensor",					m.Setting.m_bEnableDoorSensor );
	GetSetting(csFile, "Setting", "Enable Alarm",						m.Setting.m_bEnableAlarm );
	GetSetting(csFile, "Setting", "EnalbeIOMonitorRecovery",			m.Setting.m_bByPassEnableIORecovery );
	GetSetting(csFile, "Setting", "EbableSaveSiteSetting",				m.Setting.m_bEnableSaveSiteSetting );
	GetSetting(csFile, "Setting", "Set By Mode",						m.Setting.m_bSetByMode );

	// Rotator
	GetSetting(csFile, "Setting", "Enable SLT Rotota",					m.Setting.m_bRotatoUse );
	GetSetting(csFile, "Setting", "Enable Rotator Pre-Guide",			m.Setting.m_bEnableRotatorPreGuide = 1 );
	GetSetting(csFile, "Setting", "Enable Rotator 180",					m.Setting.m_bEnableRotatorTurn );

	// CCD
	GetSetting(csFile, "Setting", "Enable CCD Pin1",					m.Setting.m_bEnableCCDPin1 );
	GetSetting(csFile, "Setting", "Enable CCD Socket",					m.Setting.m_bEnableCCDSocket );
	GetSetting(csFile, "Setting", "Enable CCD Log IC",					m.Setting.m_bEnableCCDLogICImage );
	//3111.System 的Setting新增Enable Socket CCD Detect Double=1
	//	與Enable Pin1 CCD Detect Double = 1
	GetSetting(csFile, "Setting", "Enable Socket CCD Detect Double",			m.Setting.m_bSocketCCDDoubleDetect );	
	GetSetting(csFile, "Setting", "Enable Pin1 CCD Detect Double",			m.Setting.m_bPin1CCDDoubleDetect );	

	// Remote Control
	GetSetting(csFile, "Setting", "Enable Remote Control",				m.Setting.m_bEnableRemoteControl );

	// Lot Information Progress
	GetSetting(csFile, "Setting", "Enable Lot Progress",				m.Setting.m_bEnableLotDoneProgress );

	// Remote IO
	GetSetting(csFile, "Setting", "Enable Remote IO",					m.Setting.m_bEnableRemoteIO );

	// Module
	GetSetting(csFile, "Setting", "Enable ATC Module",					m.Setting.m_bEnableATCModule );
	GetSetting(csFile, "Setting", "Enable PTC Module",					m.Setting.m_bEnablePTCModule );
	GetSetting(csFile, "Setting", "Enable Heater Module",				m.Setting.m_bEnableHeaterModule );
	GetSetting(csFile, "Setting", "Enable TriTemp Module",				m.Setting.m_bEnableTriTempModule );
	GetSetting(csFile, "Setting", "Enable Remote Module",				m.Setting.m_bEnableRemoteModule );

	// Log
	GetSetting(csFile, "Setting", "Enable UPH Log",						m.Setting.m_bEnableUPHLog );
	GetSetting(csFile, "Setting", "Enable Comm Log",					m.Setting.m_bEnableCommLog );
	GetSetting(csFile, "Setting", "Enable SingleMotor Log",				m.Setting.m_bEnableSingleMotorLog );
	GetSetting(csFile, "Setting", "Enable DualMotor Log",				m.Setting.m_bEnableDualMotorLog );
	GetSetting(csFile, "Setting", "Enable Motor Log",					m.Setting.m_bEnableMotorLog );
	GetSetting(csFile, "Setting", "Enable Status Report Log",			m.Setting.m_bEnableStatusReportLog );
	GetSetting(csFile, "Setting", "Enable CCD Socket Log",				m.Setting.m_bEnableCCDSocketLog );
	GetSetting(csFile, "Setting", "Enable Jam Rate Log",				m.Setting.m_bEnableJamRateReport );
	GetSetting(csFile, "Setting", "Enable Shuttle Jam Log",				m.Setting.m_bEnableShuttleJamLog = 1 );
	
	// ByPass
	GetSetting(csFile, "Setting", "ByPassTestSiteVacc",					m.Setting.m_bByPassTestVacc );
	GetSetting(csFile, "Setting", "ByPassRotatorAlarm",					m.Setting.m_bByPassRotatorAlarm );
	GetSetting(csFile, "Setting", "ByPassVacc",							m.Setting.m_bByPassVacc ); 	//
	GetSetting(csFile, "Setting", "ByPassTrayInPos",					m.Setting.m_bByPassTrayInPos );	
	GetSetting(csFile, "Setting", "ByPassShuttle",						m.Setting.m_bByPassShuttleAlarm );	

	// Function
	GetSetting(csFile, "Setting", "Simplified Chinese",					m.Setting.m_bEnableSimplified );
	
	// System Setting
	GetSetting(csFile, "Setting", "Speed Low Limit",					m.Setting.m_iSpeedLowLimit );		
	GetSetting(csFile, "Setting", "Speed High Limit",					m.Setting.m_iSpeedHighLimit );
	GetSetting(csFile, "Setting", "Offset Low Limit",					m.Setting.m_dOffsetLowLimit );
	GetSetting(csFile, "Setting", "Offset High Limit",					m.Setting.m_dOffsetHighLimit );	
	GetSetting(csFile, "Setting", "Timer Low Limit",					m.Setting.m_dTimerLowLimit = 0.1 );
	GetSetting(csFile, "Setting", "Timer High Limit",					m.Setting.m_dTimerHighLimit = 5 );
	GetSetting(csFile, "Setting", "Timeout Low Limit",					m.Setting.m_dTimeoutLowLimit );
	GetSetting(csFile, "Setting", "Timeout High Limit",					m.Setting.m_dTimeoutHighLimit = 15 );
	
	// Buzzer Auto Close
	GetSetting(csFile, "Setting", "Buzzer Auto Close",					m.Setting.m_dBuzzerAutoClose );

	// Tray Map UI
	GetSetting(csFile, "Setting", "Tray Left",							m.Setting.m_dTraySpecLeftSide );
	GetSetting(csFile, "Setting", "Tray Top",							m.Setting.m_dTraySpecTopSide );
	GetSetting(csFile, "Setting", "Tray IC Side",						m.Setting.m_dTraySpecICSide );
	GetSetting(csFile, "Setting", "Tray Text Up Side",					m.Setting.m_dTraySpecTextUpSide );	
	GetSetting(csFile, "Setting", "Tray Text Left Side",				m.Setting.m_dTraySpecTextLeftSide );
	GetSetting(csFile, "Setting", "Tray Text Size",						m.Setting.m_iTraySpecTextSize );
	GetSetting(csFile, "Setting", "Tray Text Break",					m.Setting.m_iTraySpecTextBreak );
	GetSetting(csFile, "Setting", "Tray Bk Color",						m.Setting.m_iTraySpecBkColor );
	// 
	GetSetting(csFile, "Setting", "Show Contact Counter",				m.Setting.m_bShowContactCounter );
	GetSetting(csFile, "Setting", "Show Summary Report",				m.Setting.m_bSummaryReport );
	GetSetting(csFile, "Setting", "Chip Tray",							m.Setting.m_bEnableChipTray );
	GetSetting(csFile, "Setting", "Alarm Mail",							m.Setting.m_bCustomAlarmMail );	
	GetSetting(csFile, "Setting", "Initial Pre Move",					m.Setting.m_bInitialPreMove );	
	GetSetting(csFile, "Setting", "Initial Pre Move Distance",			m.Setting.m_iInitialPreMoveDistance );	
	GetSetting(csFile, "Setting", "Test Site Standy Position",			m.Setting.m_dTestSiteStandbyPosition );
	GetSetting(csFile, "Setting", "Test Site Standy Position Socket",	m.Setting.m_dTestSiteSocketStandyPos );
	GetSetting(csFile, "Setting", "Test Site Standby Shuttle",			m.Setting.m_iTestSiteStandByDistance );
	GetSetting(csFile, "Setting", "Arm Z Auot Retry",					m.Setting.m_bArmZAutoRetry );
	GetSetting(csFile, "Setting", "TS Remain IC",						m.Setting.m_bEnableTSRemainIC = 1 );
	GetSetting(csFile, "Setting", "ION Alarm",							m.Setting.m_bIONAlarm );
	GetSetting(csFile, "Setting", "PreMove",							m.Setting.m_bPreMove );
	GetSetting(csFile, "Setting", "PreMove Distance",					m.Setting.m_iPreMoveDistance );		
	GetSetting(csFile, "Setting", "Standy X Move Distance",				m.Setting.m_dStandyX );
	GetSetting(csFile, "Setting", "Standy Y Move Distance",				m.Setting.m_dStandyY );
	

	//
	GetSetting(csFile, "Setting", "Enable IC Missing Detect",			m.Setting.m_bEnableICMissingDetect );
	GetSetting(csFile, "Setting", "Enable Input Tray Tips",				m.Setting.m_bInputTrayTips = 1 );
	GetSetting(csFile, "Setting", "Enable Input Tray Number",			m.Setting.m_bInputTrayTipsNumber );
	GetSetting(csFile, "Setting", "Enable Input Tray Info",				m.Setting.m_bInputTrayInfo );	
	GetSetting(csFile, "Setting", "Enable Remote Control Input",		m.Setting.m_bRemoteCustomInput );
	GetSetting(csFile, "Setting", "Enable Torque Control",				m.Setting.m_bEnableTorqueCtrl );
	GetSetting(csFile, "Setting", "Enable Torque Status",				m.Setting.m_bEnableTorqueStatus );
	GetSetting(csFile, "Setting", "Enable Double Check",				m.Setting.m_bCancelDoubleChkChange = 1 );
	GetSetting(csFile, "Setting", "Enable Show Handler Status",			m.Setting.m_bShowHandlerStatus );
	GetSetting(csFile, "Setting", "Repeat Tray Maxium",					m.Setting.m_iRepeatMaxiumValue = 50 );
	GetSetting(csFile, "Setting", "Enable Auto Sel TrayFile",			m.Setting.m_bEnableAutoSelLastTrayFile = 1 );
	GetSetting(csFile, "Setting", "Enable Auto Copy Last Lot",			m.Setting.m_bEnableAutoCopyLastLotInfo = 1 );

	//
}

//////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////
void CFunction::LoadMachineID()
{
	CString cs, csFile;
	csFile = m.FilePath.UIPath;

	GetSetting(csFile, "UI", "Machine ID", m.UI.MachineID ); //目前 Handler Machine ID
}

void CFunction::SaveMachineID()
{
	CString cs, csFile;
	csFile = m.FilePath.UIPath;

	SaveSetting(csFile, "UI", "Machine ID", m.UI.MachineID ); //目前 Handler Machine ID
}


/////////////////////////////////////////////////////
// Motor parameter
void CFunction::SaveMotorParameter()
{
	CString cs, csFile;
	csFile = m.FilePath.MotorNamePath;

	SaveSetting(csFile, "Motor Parameter", "ArmX",			m.m_Motor.ArmX );
	SaveSetting(csFile, "Motor Parameter", "ArmY",			m.m_Motor.ArmY );
	SaveSetting(csFile, "Motor Parameter", "ArmZ",			m.m_Motor.ArmZ );
	SaveSetting(csFile, "Motor Parameter", "Inserter",		m.m_Motor.Inserter );
}
void CFunction::LoadMotorParameter()
{
	CString cs, csFile;
	csFile = m.FilePath.MotorNamePath;

	GetSetting(csFile, "Motor Parameter", "ArmX",			m.m_Motor.ArmX );
	GetSetting(csFile, "Motor Parameter", "ArmY",			m.m_Motor.ArmY );
	GetSetting(csFile, "Motor Parameter", "ArmZ",			m.m_Motor.ArmZ );
	GetSetting(csFile, "Motor Parameter", "Inserter",		m.m_Motor.Inserter );
}
/////////////////////////////////////////////////////
// UI
void CFunction::LoadCounter()
{
	CString csFile = _T("");
	csFile = m.FilePath.UIPath;

	for(int i=0; i<_Output_Stack_No; i++)
	{
		CString c;
		c.Format("Output %d", i+1 );
		GetSetting( csFile, "Count", c, m.Counter.OutputCount[i]);
		m.Counter.SiteTotal += m.Counter.OutputCount[i];
	}
	// 重新把值指定回去
	
	m.Counter.SitePass = m.Counter.OutputCount[0];

	// 1.0Af
//	GetSetting( csFile, "Count", "Output 1", m.Counter.OutputCount[0]);
//	GetSetting( csFile, "Count", "Output 2", m.Counter.OutputCount[1]);
//	GetSetting( csFile, "Count", "Output 3", m.Counter.OutputCount[2]);
//	GetSetting( csFile, "Count", "Output 4", m.Counter.OutputCount[3]);
}
void CFunction::SaveCounter()
{
	CString csFile = _T("");
	csFile = m.FilePath.UIPath;

	for(int i=0; i<_Output_Stack_No; i++)
	{
		CString c;
		c.Format("Output %d", i+1 );
		SaveSetting( csFile, "Count", c, m.Counter.OutputCount[i]);
	}

	// 1.0Af
//	SaveSetting( csFile, "Count", "Output 1", m.Counter.OutputCount[0]);
//	SaveSetting( csFile, "Count", "Output 2", m.Counter.OutputCount[1]);
//	SaveSetting( csFile, "Count", "Output 3", m.Counter.OutputCount[2]);
//	SaveSetting( csFile, "Count", "Output 4", m.Counter.OutputCount[3]);
}
void CFunction::LoadUI()
{
	CString cs, csFile = _T("");
	csFile = m.FilePath.UIPath;

	GetSetting(csFile, "UI", "Language",				m.UI.Language );						//目前使用語言

	GetSetting(csFile, "UI", "TEST FILE",				m.UI.FileMainTestSetting);				//目前的測試檔案
	GetSetting(csFile, "UI", "MAPPING",					m.UI.FileMainMapping );					//目前的MAPPING檔案
	GetSetting(csFile, "UI", "TRAY FILE",				m.UI.FileMain );						//目前的TRAYFILE檔案

	// BaseFile
	GetSetting(csFile, "UI", "TEST BASE FILE",			m.UI.FileMainBaseTestSetting);			//目前的測試 BASE 檔案	
	GetSetting(csFile, "UI", "MAPPING BASE FILE",		m.UI.FileMainBaseMapping );				//目前的 MAPPING BASE FILE 檔案 
	GetSetting(csFile, "UI", "TRAY BASE FILE",			m.UI.FileBaseFile);						//目前的 TRAYTFILE BASE FILE 檔案 
}
void CFunction::SaveUI()
{
	CString cs, csFile = _T("");
	csFile = m.FilePath.UIPath;

	SaveSetting(csFile, "UI", "Language",			m.UI.Language );							//目前使用語言

	SaveSetting(csFile, "UI", "TEST FILE",			m.UI.FileMainTestSetting);					//目前的測試檔案
	SaveSetting(csFile, "UI", "MAPPING",			m.UI.FileMainMapping );						//目前的MAPPING檔案
	SaveSetting(csFile, "UI", "TRAY FILE",			m.UI.FileMain );							//目前的TRAYFILE檔案

	// Base File
	SaveSetting(csFile, "UI", "TEST BASE FILE",		m.UI.FileMainBaseTestSetting);				//目前的測試 BASE 檔案	
	SaveSetting(csFile, "UI", "MAPPING BASE FILE",	m.UI.FileMainBaseMapping );					//目前的 MAPPING BASE FILE 檔案 
	SaveSetting(csFile, "UI", "TRAY BASE FILE",		m.UI.FileBaseFile);							//目前的 TRAYTFILE BASE FILE 檔案 
}
/////////////////////////////////////////////////////
// LoadFile Function.
void CFunction::Decryption(CString *csCode)
{
	for(int i=0; i<csCode->GetLength(); i++)
		csCode->SetAt(i, csCode->GetAt(i) & 0x7f);
}
void CFunction::Encryption(CString *csCode)
{
	for(int i=0; i<csCode->GetLength(); i++)
		csCode->SetAt(i, csCode->GetAt(i) | 0x80);
}

/////////////////////////////////////////////////////
// Initial Motor Card
void CFunction::LoadMotorAddress()
{

	m.m_Motor.Inserter.BoardID = 
		m.m_Motor.ArmX.BoardID = 
		m.m_Motor.ArmY.BoardID = 
		m.m_Motor.ArmZ.BoardID = 0;

	m.m_Motor.Inserter.AxisNo	 = U_Axis;
	m.m_Motor.ArmX.AxisNo		 = X_Axis;
	m.m_Motor.ArmY.AxisNo		 = Y_Axis;
	m.m_Motor.ArmZ.AxisNo		 = Z_Axis;


	// Init 8141P Moation Card
	int             cardNo;
    unsigned long   returnCode, lReturnBoardStatus = 0;
	// returnCode	用來記錄 8141P	軸卡回傳訊息 Success 或 Fail Code
	// cardNo		用來指定 cardNo 卡號.害 returnCode 做比對,確認軸卡都被安裝

	returnCode = (unsigned long)MC8141PMotDevAvailable( &lReturnBoardStatus );
 
	cardNo = 0x3;       // Board ID 0 and 1

	if(returnCode != 0)
	{
		m.Info.csError += "無法找到可用的軸卡\n";
		return;
	}
	else if(lReturnBoardStatus != (unsigned long)cardNo)
	{
		CString cs;
		cs.Format("部分軸卡不存在, 已找到的軸卡:%x\n", lReturnBoardStatus);
		m.Info.csError += cs;
	}
	// 確認目前軸卡的安裝狀態


	// For both motor control boards.
	// Card 0 

	int s = 1;
	for ( int i = 0; i < s; i++ )
    {
        m.Info.bCardStatus[i] = false;
		if ( ( lReturnBoardStatus & (1 << i)) > 0 ) 
		{
			if ( MC8141PMotDevOpen(i) != ERROR_SUCCESS )
			{	
				m.Err.System.Code = enErrorCodeMotorCard1Fail;	
			}
			else
				m.Info.bCardStatus[i] = true;
		}
	}
	// 啟動軸卡
	
	// Write reg to Motor Card
	// MC8141PMotWrReg( 
	//	BYTE byBoard_ID, 
	//	BYTE byWriteAxis, 
	//	WORD wCommandCode, 
	//	DWORD dwWriteValue );

	if ( m.Info.bCardStatus[m.m_Motor.ArmX.BoardID] )
	{
		// No interrupt modes now. We enable interrupts on IN0 only when homing.
        MC8141PMotWrReg( m.m_Motor.ArmX.BoardID, m.m_Motor.ArmX.AxisNo, WR1, 0x0000 );
		MC8141PMotWrReg( m.m_Motor.ArmX.BoardID, m.m_Motor.ArmX.AxisNo, WR2, 0x305c );
		MC8141PMotWrReg( m.m_Motor.ArmX.BoardID, m.m_Motor.ArmX.AxisNo, WR3, 0x0000 );
		MC8141PMotWrReg( m.m_Motor.ArmX.BoardID, m.m_Motor.ArmX.AxisNo, WR4, 0x0000 );
		MC8141PMotWrReg( m.m_Motor.ArmX.BoardID, m.m_Motor.ArmX.AxisNo, WR5, 0x4024 );		
		MC8141PMotWrReg( m.m_Motor.ArmX.BoardID, m.m_Motor.ArmX.AxisNo, PLmt, 2000000000 );
		MC8141PMotWrReg( m.m_Motor.ArmX.BoardID, m.m_Motor.ArmX.AxisNo, NLmt, -2000000000 );
		MC8141PMotDO( m.m_Motor.ArmX.BoardID,    m.m_Motor.ArmX.AxisNo, 0x08 );		
		m.m_Motor.ArmX.Reverse = true;
	}
	// Arm X 寫入參數. 1

	if ( m.Info.bCardStatus[m.m_Motor.ArmY.BoardID] )
	{
		// No interrupt modes now. We enable interrupts on IN0 only when homing.
		MC8141PMotWrReg( m.m_Motor.ArmY.BoardID, m.m_Motor.ArmY.AxisNo, WR1, 0x0000 );
		MC8141PMotWrReg( m.m_Motor.ArmY.BoardID, m.m_Motor.ArmY.AxisNo, WR2, 0x305c );
		MC8141PMotWrReg( m.m_Motor.ArmY.BoardID, m.m_Motor.ArmY.AxisNo, WR3, 0x0000 );
		MC8141PMotWrReg( m.m_Motor.ArmY.BoardID, m.m_Motor.ArmY.AxisNo, WR4, 0x0000 );
		MC8141PMotWrReg( m.m_Motor.ArmY.BoardID, m.m_Motor.ArmY.AxisNo, WR5, 0x4024 );		
		MC8141PMotWrReg( m.m_Motor.ArmY.BoardID, m.m_Motor.ArmY.AxisNo, PLmt, 2000000000 );
		MC8141PMotWrReg( m.m_Motor.ArmY.BoardID, m.m_Motor.ArmY.AxisNo, NLmt, -2000000000 );
		MC8141PMotDO( m.m_Motor.ArmY.BoardID,    m.m_Motor.ArmY.AxisNo, 0x08 );
		m.m_Motor.ArmY.Reverse = true;
	}
	// Arm Y 寫入參數. 2

	if ( m.Info.bCardStatus[m.m_Motor.ArmZ.BoardID] )
	{
		MC8141PMotWrReg( m.m_Motor.ArmZ.BoardID, m.m_Motor.ArmZ.AxisNo, WR1, 0x0000 );
		
		// Bit 6 = 1-pulse, 1-direction type for Mitsubishi
		// Bit 8 = +Direction = high
		MC8141PMotWrReg( m.m_Motor.ArmZ.BoardID, m.m_Motor.ArmZ.AxisNo, WR2, 0x3154 );
		MC8141PMotWrReg( m.m_Motor.ArmZ.BoardID, m.m_Motor.ArmZ.AxisNo, WR3, 0x0004 );
		MC8141PMotWrReg( m.m_Motor.ArmZ.BoardID, m.m_Motor.ArmZ.AxisNo, WR4, 0x0000 );
        MC8141PMotWrReg( m.m_Motor.ArmZ.BoardID, m.m_Motor.ArmZ.AxisNo, WR5, 0x4024 );			
		MC8141PMotWrReg( m.m_Motor.ArmZ.BoardID, m.m_Motor.ArmZ.AxisNo, PLmt, 2000000000 );
		MC8141PMotWrReg( m.m_Motor.ArmZ.BoardID, m.m_Motor.ArmZ.AxisNo, NLmt, -2000000000 );
		MC8141PMotDO( m.m_Motor.ArmZ.BoardID,    m.m_Motor.ArmZ.AxisNo, 0x08 );	
        m.m_Motor.ArmZ.Reverse = false;
	}
	// Arm Z 寫入參數. 3 

    if ( m.Info.bCardStatus[m.m_Motor.Inserter.BoardID] )
	{
		MC8141PMotWrReg( m.m_Motor.Inserter.BoardID, m.m_Motor.Inserter.AxisNo, WR1, 0x0000 );
		MC8141PMotWrReg( m.m_Motor.Inserter.BoardID, m.m_Motor.Inserter.AxisNo, WR2, 0x305c );
		MC8141PMotWrReg( m.m_Motor.Inserter.BoardID, m.m_Motor.Inserter.AxisNo, WR3, 0x0000 );
		MC8141PMotWrReg( m.m_Motor.Inserter.BoardID, m.m_Motor.Inserter.AxisNo, WR4, 0x0000 );
		MC8141PMotWrReg( m.m_Motor.Inserter.BoardID, m.m_Motor.Inserter.AxisNo, WR5, 0x4024 );        		
		MC8141PMotWrReg( m.m_Motor.Inserter.BoardID, m.m_Motor.Inserter.AxisNo, PLmt, 2000000000 );
		MC8141PMotWrReg( m.m_Motor.Inserter.BoardID, m.m_Motor.Inserter.AxisNo, NLmt, -2000000000 );
		MC8141PMotDO( m.m_Motor.Inserter.BoardID,	 m.m_Motor.Inserter.AxisNo, 0x08 );
        m.m_Motor.Inserter.Reverse = true;
	}
	// Inserter 寫入參數. 6


	MotorServoOnAll();
}
/////////////////////////////////////////////////////
// Basic Control File
/////////////////////////////////////////////////////
// Load Bin
bool CFunction::SaveBinMapping(CString csFile, CArray <tagBinMapping, tagBinMapping>* TempBinMap)
{
	// 將 Category 存入 .mapping 中
	CFile File;
	CString Temp = _T("");
	if(File.Open(m.FilePath.CategoryPath + csFile,
		CFile::modeCreate  | CFile::modeWrite, NULL) != 0)
	{
		// 插入標題
		Temp = _T("Software\tStack\tCode\tDescription\tPass\tcolor\r\n");
		File.Write(Temp, Temp.GetLength());

		// 將所下載的 Bin Map 存入檔案中
		for(int i=0;i<TempBinMap->GetSize();i++)
		{
			Temp.Format("%s\t", TempBinMap->ElementAt(i).software );
			File.Write(Temp, Temp.GetLength());

			Temp.Format("%d\r\n", TempBinMap->ElementAt(i).hardware);
			File.Write(Temp, Temp.GetLength());

			Temp.Format("%s\t", TempBinMap->ElementAt(i).code);
			File.Write(Temp, Temp.GetLength());

			Temp.Format("%s\t", TempBinMap->ElementAt(i).description);
			File.Write(Temp, Temp.GetLength());

			Temp.Format("%d\t", TempBinMap->ElementAt(i).pass);
			File.Write(Temp, Temp.GetLength());

			Temp.Format("%d\t", TempBinMap->ElementAt(i).color);
			File.Write(Temp, Temp.GetLength());
		}
		File.Close();

	}
	else
		return false;

	return true;
}

bool CFunction::ReadBinMappingFile(CString csFile, CArray<CString, CString> &array)
{
	CFile file;
	if(!file.Open(csFile, CFile::modeRead))
		return false;

	BYTE buffer[100];
    DWORD dwRead = 1;
	CString temp, content;

	int item = 0;
	while(dwRead > 0)
	{
		dwRead = file.Read(buffer, sizeof(buffer));
		if(dwRead > 0)
		{
			CString ppp;
			memcpy(ppp.GetBufferSetLength(dwRead), buffer, dwRead);
			temp += ppp;
			while(1)
			{
				int k = 1;
				int i = -1;
				int a ;
				a = temp.Find("\r\n", 0);
				if((i == -1 && a > i) || (i > -1 && a < i && a > -1))
				{
					k = 2;
					i = a;
				}
				a = temp.Find("\t", 0);
				if((i == -1 && a > i) || (i > -1 && a < i && a > -1))
				{
					i = a;
					k = 1;
				}
				if(i>-1)
				{
					content = temp.Left(i);
					array.Add(content);
					temp.Delete(0, i+k); temp.FreeExtra();
				}
				else
					break;
			}
		}
	}

	if(temp.GetLength() > 0)
	{
		content = temp;
		array.Add(content);
	}

	return true;
}

tagBinMapping CFunction::GetBinMapping(CString code)
{
	tagBinMapping map;

	return map;
}
void CFunction::LoadBinMapping()
{
	// Update m.BinMap
	CFileFind file;
	if(!file.FindFile( m.FilePath.CategoryPath + "\\" + m.UI.FileMainMapping))
	{		
		return;
	}

	CArray<CString, CString> array;
	ReadBinMappingFile( m.FilePath.CategoryPath + "\\" + m.UI.FileMainMapping, array);

	m.BinMap.RemoveAll();
	tagBinMapping bin;

	// 6 is item count 

	for(int i=1; i<array.GetSize() / 6; i++)
	{
//		if(atoi(array[i*6+1].GetBuffer(0)) != 1)	//
		{
			bin.software		= array[i*6+0];
			bin.hardware		= atoi(array[i*6+1]);
			bin.code			= array[i*6+2];
			bin.description		= array[i*6+3];
			bin.pass			= array[i*6+4] == "1" ? true : false;
			bin.color			= atoi(array[i*6+5]);

			m.BinMap.Add(bin);
		}	
	}
}

void CFunction::LoadInterfaceTesting()
{
  CString cs, csFile;
  csFile = m.FilePath.UIPath;

  // It is for Interface Testing dialog using data.
  // For the combo box.
  GetSetting(csFile, "Interface Testing", "T1", m.InterfaceData.T1 );
  GetSetting(csFile, "Interface Testing", "T2", m.InterfaceData.T2 );
  GetSetting(csFile, "Interface Testing", "T3", m.InterfaceData.T3 );
  GetSetting(csFile, "Interface Testing", "T4", m.InterfaceData.T4 );

  GetSetting(csFile, "Interface Testing", "N1", m.InterfaceData.N1 );
  GetSetting(csFile, "Interface Testing", "N2", m.InterfaceData.N2 );
  GetSetting(csFile, "Interface Testing", "N3", m.InterfaceData.N3 );
  GetSetting(csFile, "Interface Testing", "N4", m.InterfaceData.N4 );
}

/////////////////////////////////////////////////////
// Test Setting 
void CFunction::LoadTestSetting()
{
	CString csFile = _T("");
	csFile = m.FilePath.TestSettingPath + m.UI.FileMainTestSetting;

//	GetSetting(csFile, "Test Type", "Type",				m.m_TestSetting.m_TestType );
	GetSetting(csFile, "Test Extend", "CCD",			m.m_TestSetting.m_CCDUse );
	GetSetting(csFile, "Test Extend", "ROTATOR",		m.m_TestSetting.m_RotatorUse );
	GetSetting(csFile, "Test Extend", "Angle",			m.m_TestSetting.m_Angle );

	// CCD Socket
	GetSetting(csFile, "Test Extend", "CCD Socket",		m.m_TestSetting.m_CCDSocketUse );

	// Interface Type
	GetSetting(csFile, "Interface Selected", "Selected",	m.m_TestSetting.m_TestType );
}
void CFunction::SaveTestSetting()
{
	CString csFile = _T("");
	csFile = m.FilePath.TestSettingPath + m.UI.FileMainTestSetting;

	SaveSetting(csFile, "Test Type", "Type",			m.m_TestSetting.m_TestType );
	SaveSetting(csFile, "Test Extend", "CCD",			m.m_TestSetting.m_CCDUse );
	SaveSetting(csFile, "Test Extend", "ROTATOR",		m.m_TestSetting.m_RotatorUse );
	SaveSetting(csFile, "Test Extend", "Angle",			m.m_TestSetting.m_Angle );

	// CCD Socket
	SaveSetting(csFile, "Test Extend", "CCD Socket",	m.m_TestSetting.m_CCDSocketUse );
}

void CFunction::SavePath()
{
	CString csFile = _T("");
	csFile = m.FilePath.CustomFilePath;
	
	// Multi SV
	SaveSetting(csFile, "Multi SV", "Program Excel Path",	m.CustomFilePath.MultiSVProgramExportPath );
	SaveSetting(csFile, "Multi SV", "Test Path",			m.CustomFilePath.MultiSVTestReportPath );
	SaveSetting(csFile, "Multi SV", "TrayMap Path",			m.CustomFilePath.MultiSVTrayMapFilePath );
	// Loop Test	
	SaveSetting(csFile, "Loop Test", "Test Result Path",	m.CustomFilePath.LoopTestResultReportPath );
	// Event Log
	SaveSetting(csFile, "Event Log", "Event Log Path",		m.CustomFilePath.EventLogReportPath );
	// Tray Map Report
	SaveSetting(csFile, "TrayMap Log", "Tray Map Path",		m.CustomFilePath.TrayMapReportPath );
	// UPH Report
	SaveSetting(csFile, "UPH", "UPH Report",				m.CustomFilePath.UPHReportPath );
	// SLT Protocol
	SaveSetting(csFile, "SLT Protocol Log", "SLT Log",		m.CustomFilePath.SLTProtocolPath );
}
void CFunction::LoadPath()
{
	CString csFile = _T("");
	csFile = m.FilePath.CustomFilePath;
	
	// Multi SV
	GetSetting(csFile, "Multi SV", "Program Excel Path",	m.CustomFilePath.MultiSVProgramExportPath );
	GetSetting(csFile, "Multi SV", "Test Path",				m.CustomFilePath.MultiSVTestReportPath );
	GetSetting(csFile, "Multi SV", "TrayMap Path",			m.CustomFilePath.MultiSVTrayMapFilePath );
	// Loop Test	
	GetSetting(csFile, "Loop Test", "Test Result Path",		m.CustomFilePath.LoopTestResultReportPath );
	// Event Log
	GetSetting(csFile, "Event Log", "Event Log Path",		m.CustomFilePath.EventLogReportPath );
	GetSetting(csFile, "TrayMap Log", "Tray Map Path",		m.CustomFilePath.TrayMapReportPath );
	// UPH
	GetSetting(csFile, "UPH", "UPH Report",					m.CustomFilePath.UPHReportPath );
	// SLT Protocol
	GetSetting(csFile, "SLT Protocol Log", "SLT Log",		m.CustomFilePath.SLTProtocolPath );

	bool bCheck[8];
	bool bAllCheck = false;
	for(int i=0;i<8;i++)
		bCheck[i] = false;

	// 如果沒有設定過, 那麼就指定到 D:
	if( m.CustomFilePath.MultiSVProgramExportPath == "" )
	{
		bCheck[0] = true;
		m.CustomFilePath.MultiSVProgramExportPath = "D:\\\\";
	}
	if( m.CustomFilePath.MultiSVTestReportPath == "" )
	{
		bCheck[1] = true;
		m.CustomFilePath.MultiSVTestReportPath = "D:\\\\";
	}
	if( m.CustomFilePath.LoopTestResultReportPath == "" )
	{
		bCheck[2] = true;
		m.CustomFilePath.LoopTestResultReportPath = "D:\\\\";
	}
	if( m.CustomFilePath.EventLogReportPath == "" )
	{
		bCheck[3] = true;
		m.CustomFilePath.EventLogReportPath = "D:\\\\";
	}
	if( m.CustomFilePath.MultiSVTrayMapFilePath == "" )
	{
		bCheck[4] = true;
		m.CustomFilePath.MultiSVTrayMapFilePath = "D:\\\\";
	}
	if( m.CustomFilePath.TrayMapReportPath == "" )
	{
		bCheck[5] = true;
		m.CustomFilePath.TrayMapReportPath = "D:\\\\";
	}
	if( m.CustomFilePath.UPHReportPath == "" )
	{
		bCheck[6] = true;
		m.CustomFilePath.UPHReportPath = "D:\\\\";
	}
	if( m.CustomFilePath.SLTProtocolPath == "" )
	{
		bCheck[7] = true;
		m.CustomFilePath.SLTProtocolPath = "D:\\\\";
	}

	// 檢查一下有沒有空字串
	for(i=0;i<8;i++)
	{
		if( bCheck[i] == true )
			bAllCheck = true;
	}

	// 如果有其中一個沒有設定過, 那麼就要重新儲存
	if( bAllCheck )
	{
		SavePath();
	}
}
void CFunction::LoadCoord()
{
	// Load Input Coord.
}

void CFunction::LoadDebugNote()
{
	CString csFile;
	csFile = m.FilePath.DebugNotePath;

	unsigned char cTemp[1001] = {0};
	unsigned long ulNumRead = 0;
	HANDLE	m_hComm = NULL;

	m_hComm = CreateFile (  csFile,// Pointer to the name of the port
		GENERIC_READ | GENERIC_WRITE,
		// Access (read/write) mode
		0,            // Share mode
		NULL,         // Pointer to the security attribute
		OPEN_EXISTING,// How to open the serial port
		0,            // Port attributes
		NULL);        // Handle to port with attribute

	while(1)
	{
		::ReadFile(m_hComm, cTemp, sizeof(cTemp), &ulNumRead, NULL);
		if(ulNumRead == 0)
			break;
		// No more data. break.
		
		for(int i=0;i<ulNumRead;i++ )
			m.ReleaseNote.csDebugNote += cTemp[i];
	}

	::CloseHandle(m_hComm);
	m_hComm = NULL;
}
void CFunction::LoadOffsetNote()
{
	CString csFile;
	csFile = m.FilePath.OffsetNotePath;

//	GetSetting(csFile, "Offset Note", "Offset Note", m.ReleaseNote.csOffsetNote );

	unsigned char cTemp[1001] = {0};
	unsigned long ulNumRead = 0;
	HANDLE	m_hComm = NULL;

	m_hComm = CreateFile (  csFile,// Pointer to the name of the port
		GENERIC_READ | GENERIC_WRITE,
		// Access (read/write) mode
		0,            // Share mode
		NULL,         // Pointer to the security attribute
		OPEN_EXISTING,// How to open the serial port
		0,            // Port attributes
		NULL);        // Handle to port with attribute

	while(1)
	{
		::ReadFile(m_hComm, cTemp, sizeof(cTemp), &ulNumRead, NULL);
		if(ulNumRead == 0)
			break;
		// No more data. break.
		
		for(int i=0;i<ulNumRead;i++ )
			m.ReleaseNote.csOffsetNote += cTemp[i];
	}

	::CloseHandle(m_hComm);
	m_hComm = NULL;

}
void CFunction::LoadFile()
{
	f.LoadUI();
	f.LoadSystemSetting();
	f.LoadSimulation();
	f.LoadBinColor();
	f.LoadATCMonitor();
	f.LoadHandlerComPort();
	f.LoadOutputColor();
	f.LoadCCDSocketControl();
	f.LoadCCDPin1Control();
	f.LoadInterfaceEnable();
	f.LoadUPHInfo();
	f.LoadContactForce();
	f.LoadSocketPattern();
	f.LoadATCModuleMultiSVFile();
	f.LoadATCModuleMultiSVSetting();
	f.LoadTextOffsetNote();
	f.LoadTorqueParameter();
	f.LoadRepeatTrayFunEnable();
	f.LoadRepeatTraySetting();
	f.LoadRepeatTrayInOut();
	f.LoadRepeatTrayTemper();
	f.LoadTrayFileDefColor();
	f.LoadJamRateInfo();
	f.LoadNowMoation();
	f.LoadRepeaterTrayCommand();
	f.LoadArmLogICImage();
	f.LoadArmLogICImagePath();
	f.LoadLastTrayFile();
	f.LoadTitleExtend();

	f.LoadTraySpec();
	f.LoadPassword();
	f.LoadSetting();
	f.LoadLotInfo();
	f.LoadGearRationParameter();
	f.LoadTSRemainICParameter();
	f.LoadTsFolatingConvert();
	f.LoadTorqueToolSet();
	f.LoadJamRateCycleTimeInfo();
	f.LoadLastTrayData();

	f.LoadYield();			// We need LoadUI First. Then loadYield.
	f.LoadSpeed();			// We need LoadUI First. Then Speed.(Speed store in TrayFile )
	f.LoadTimer();			// We need LoadUI First. Then Timer.(Timer store in TrayFile )
	f.LoadOffset();			// We need LoadUI First. Then Offset.(Offset store in TrayFile)
	f.LoadTestSetting();	// We need LoadUI First. Then Testing Setting / CCD / CCD Socket / Rotator 
	f.LoadInterface();
	f.LoadInterFaceRs232();
	f.LoadInterFaceTcp();
	f.LoadTcpToObject();
	f.LoadSiteSetting();
	f.LoadPogoParameter();
	f.LoadLoopTest();
	f.LoadVisionSet();
	//
	f.LoadCounter();
	f.LoadTemperatureSetting();
	//
	f.LoadTrayMap();
	f.LoadTrayMapRepeat();
	//
	f.LoadAlignment();
	f.LoadInterfaceTesting();
	f.LoadMotorParameter();		// We need Load Alignment first. Then load Motor Because We need to refer TestSite Conact.!
	f.LoadBinMapping();			//
	f.LoadOutputYield();
	f.LoadOutputYieldValue();
	f.LoadMachineID();
	f.LoadTimerSetting();
	f.LoadTorqueCtrlLimit();
	//
	f.LoadCoord();
	f.LoadPath();
	//
	f.LoadDebugNote();
	f.LoadOffsetNote();
	// Record Test Counter
	f.LoadContactCounter();
	// Load SMTP Setting
	f.LoadSMTPSetting();
	// Load Custom Catoregy Color
	f.LoadCatoregyColor();
	// Load Custom For each Customer Setting ex. Report Or Dialog.
	f.LoadAutoRetrySetting();
	f.LoadAutoRetryExterndValue();
	//	
	f.LoadAlignmentProf();
	f.LoadJamRateCode();
	f.LoadJamRateData();
	//
	f.LoadPageEnable();
	f.LoadMCEnable();
	f.LoadManualContactTsMode();
	f.LoadIf();
	f.LoadTowerSetting();
	//
	f.m_Log.AddLogEvent( "Deer Load txt Finish" );
	//
	// Note : LoadUI First then loadYield 
	// Because Yield Control store in TrayFile.
	// Call the LoadUI to load TrayFile.

	f.LoadMotorAddress();
	// It will init Card. DeviceOpen.

	f.m_Log.AddLogEvent( "Deer Load Motor Finish" );
}

void CFunction::LoadSimulation()
{
	CString csFile;
	csFile = m.FilePath.SimulationPath;

	// Debug Option.!
	GetSetting(csFile, "Simulation", "Arm",			m.Simulation.m_bDLArm );
	GetSetting(csFile, "Simulation", "Inspect",		m.Simulation.m_bDLInspect );
	GetSetting(csFile, "Simulation", "TestSite",	m.Simulation.m_bDLTestSite );
	GetSetting(csFile, "Simulation", "Tester",		m.Simulation.m_bDLTester );
	GetSetting(csFile, "Simulation", "Manual",		m.Simulation.m_bDLManual );
	GetSetting(csFile, "Simulation", "West",		m.Simulation.m_bDLWest );

}
void CFunction::SaveSimulation()
{
	CString csFile;
	csFile = m.FilePath.SimulationPath;

	// Debug Option.!
	SaveSetting(csFile, "Simulation", "Arm",		m.Simulation.m_bDLArm );
	SaveSetting(csFile, "Simulation", "Inspect",	m.Simulation.m_bDLInspect );
	SaveSetting(csFile, "Simulation", "TestSite",	m.Simulation.m_bDLTestSite );
	SaveSetting(csFile, "Simulation", "Tester",		m.Simulation.m_bDLTester );
	SaveSetting(csFile, "Simulation", "Manual",		m.Simulation.m_bDLManual );
	SaveSetting(csFile, "Simulation", "West",		m.Simulation.m_bDLWest );

}

// For CWinThread Status debug
void CFunction::CWinMessage(CString msg, int value)
{
	// set false enable the thread message
	bool enDArm;
	bool enDTestSite;
	bool enDInspect;
	bool enDTester;
	bool enDManual;
	bool enDWest;

	//
	f.LogCSV( msg, value );
	//

	if( m.Simulation.m_bDLArm == 1 )
		enDArm = false;
	else
		enDArm = true;

	if( m.Simulation.m_bDLTestSite == 1)
		enDTestSite = false;
	else
		enDTestSite = true;

	if( m.Simulation.m_bDLInspect == 1 )
		enDInspect = false;
	else
		enDInspect = true;

	if( m.Simulation.m_bDLTester == 1)
		enDTester = false;
	else
		enDTester = true;

	if( m.Simulation.m_bDLManual == 1 )
		enDManual = false;
	else
		enDManual = true;

	if( m.Simulation.m_bDLWest == 1 )
		enDWest = false;
	else
		enDWest = true;

	// Disable Message
	if( value == theApp.enDArm && enDArm)
		return;
	if( value == theApp.enDTestSite && enDTestSite)
		return;
	if( value == theApp.enDInspect && enDInspect)
		return;
	if( value == theApp.enDTester && enDTester)
		return;
	if( value == theApp.enDManual && enDManual )
		return;
	if( value == theApp.enDWest && enDWest )
		return;

	// Visual Panel
	if( !theApp.m_DlgVisualButton.GetSafeHwnd() )
		;
	else
	{
		CString cs = msg;
		::SendMessage(theApp.m_DlgVisualButton.GetSafeHwnd(), WM_TEST_MESSAGE, (WPARAM)&cs, NULL);
	}

	// Debug Button
	if(!theApp.m_DlgButton.GetSafeHwnd())
		;
	else
	{
		CString cs = msg;
		::SendMessage(theApp.m_DlgButton.GetSafeHwnd(), WM_TEST_MESSAGE, (WPARAM)&cs, NULL);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////
// Tray Map Function

static CMutex MutexTrayMap;
void CFunction::AddTrayMap(int stack, CString code, CPoint point, int site, double temperature)
{
	CSingleLock Lock(&MutexTrayMap);
	Lock.Lock();

	tagTrayMap map;
	map.code = code;
	map.StackNo = stack;
	map.pos = point;
	map.site = site;
	map.temperature = temperature;
	m.TrayMap[stack].push_front(map);
	if(m.TrayMap[stack].size() > _Max_Tray_Map_Size)
		m.TrayMap[stack].pop_back();

	Lock.Unlock();
}

void CFunction::AddTrayMap(int stack, int bin, CPoint point, int site, double temperature)
{
	CSingleLock Lock(&MutexTrayMap);
	Lock.Lock();

	tagTrayMap map;
	map.code.Format("%d", bin);
	map.StackNo = stack;
	map.pos = point;
	map.site = site;
	map.temperature = temperature;
	m.TrayMap[stack].push_front(map);
	if(m.TrayMap[stack].size() > _Max_Tray_Map_Size)
		m.TrayMap[stack].pop_back();

	Lock.Unlock();
}
static CMutex csMutexTrayMapCSVLog;
void CFunction::LogTrayMapCSV(CString csTrayMap)
{
	CSingleLock Lock(&csMutexTrayMapCSVLog);
	Lock.Lock();

	// Get Systme Time...
	SYSTEMTIME Time;
	::GetLocalTime(&Time);

	// Convert Time Format
	CString csMounth	= "";
	CString csDay		= "";
	CString csHour		= "";
	CString csMin		= "";

	if( Time.wMonth < 10 )
		csMounth.Format("0%d", Time.wMonth );
	else
		csMounth.Format("%d", Time.wMonth );
	if( Time.wDay < 10 )
		csDay.Format("0%d", Time.wDay );
	else
		csDay.Format("%d", Time.wDay );

	if( Time.wHour < 10 )
		csHour.Format("0%d", Time.wHour );
	else
		csHour.Format("%d", Time.wHour );

	if( Time.wMinute < 10 )
		csMin.Format("0%d", Time.wMinute );
	else
		csMin.Format("%d", Time.wMinute );

	// Create File
	CString csFileNameTime;
	csFileNameTime.Format("_%d%s%s_%s%s_", Time.wYear, csMounth, csDay, csHour, csMin );
	CString csFileName = _TrayMapReportName + csFileNameTime + _TrayMapReport;
	CString csFile = m.CustomFilePath.TrayMapReportPath + csFileName;

	CTime time = CTime::GetCurrentTime();
	// Time
	CString cstime = _T("");
	SYSTEMTIME ti; 
	GetLocalTime(&ti);
	cstime.Format("%d.%d.%d.%d.%5.2f", 
		ti.wMonth, ti.wDay, ti.wHour, ti.wMinute, ti.wSecond + ( ti.wMilliseconds / 1000. ) );

	// File write
	CFile file;	
	CString csDATA = "";
	int iSerial = 0;
	CString csSerial;
	if(file.Open(csFile, CFile::modeCreate | CFile::modeWrite | CFile::shareDenyNone
		| CFile::modeNoTruncate, NULL) != 0)
	{

		csDATA.Format("%s\r\n", csTrayMap );

		file.SeekToEnd();
		file.Write(csDATA.GetBuffer(0), csDATA.GetLength());
		file.Close();
	}

	Lock.Unlock();
}
int CFunction::ExportTrayMapReportMapMaxCodeLength()
{
	long m_length = 0;
	CString csCode = _DefaultCode;
	m_length = csCode.GetLength();

	std::list<tagTrayMapLog> TrayMapReport;
	TrayMapReport = m.TrayMap[0];

	//
	TrayMapReport.reverse();
	std::list<tagTrayMap>::iterator p = TrayMapReport.begin();

	for(int i=0; i<TrayMapReport.size(); i++, p++)
	{
		csCode = p->code;
		int m_codelength = csCode.GetLength();
		if( m_codelength >= m_length )
			m_length = m_codelength;
	}

	return m_length;
}
// (x,y) -> first (1, 1)
CString CFunction::ExportTrayMapReportMapGetCode(int x, int y)
{
	CString csCode = _T("");
	csCode = _DefaultCode;

	std::list<tagTrayMapLog> TrayMapReport;
	TrayMapReport = m.TrayMap[0];

	//
	TrayMapReport.reverse();
	std::list<tagTrayMap>::iterator p = TrayMapReport.begin();

	for(int i=0; i<TrayMapReport.size(); i++, p++)
	{
		if( x == p->pos.x && y == p->pos.y )
		{
			csCode = p->code;
			break;
		}
	}

	return csCode;
}
void CFunction::ExportTrayMapReportMap(int col, int row)
{
	// 產生檔名
	CString csFileName = _T("");
	CTime time = CTime::GetCurrentTime();
	csFileName.Format("TrayMap_%s", time.Format("%m_%d_%H_%M"));
	CString csFile = _T("");
	csFile = m.CustomFilePath.TrayMapReportPath + csFileName + _TrayMapReport;

	// 刪除前一份檔案
	::DeleteFile( csFile );

	// 開啟檔案
	CFile file;
	file.Open( csFile, CFile::modeCreate | CFile::modeWrite
		| CFile::modeNoTruncate | CFile::shareDenyNone, NULL);	

	// 找檔案結尾
	file.SeekToEnd();

	// 填入標題		
	CString csTitle = "**************************** TrayMap ****************************\r\n";
	file.Write(csTitle.GetBuffer(0), csTitle.GetLength());

	CString csTime = _T("");
	csTime.Format("Export Time: %s\r\n", time.Format("Modth:%m Day:%d Hours:%H Min:%M Sec:%S"));	
	file.Write(csTime.GetBuffer(0), csTime.GetLength());

	//
	CString csBreak = _T("");
	csBreak.Format("\r\n\r\n");
	file.Write(csBreak.GetBuffer(0), csBreak.GetLength());

	int iMax = ExportTrayMapReportMapMaxCodeLength();

	for(int i=0;i<row;i++)
	{
		for(int j=0;j<col;j++)
		{
			CString csColData = _T("");
			CString csCode = _T("");
			csCode = ExportTrayMapReportMapGetCode(j+1, i+1);
			if( iMax <= 5 )
				csColData.Format("(%.2d:%.2d),%6s, ", i+1, j+1, csCode);
			else if( iMax > 5 && iMax < 10 )
				csColData.Format("(%.2d:%.2d),%11s, ", i+1, j+1, csCode);
			else if( iMax > 10 && iMax < 20 )
				csColData.Format("(%.2d:%.2d),%21s, ", i+1, j+1, csCode);
			else
				csColData.Format("(%.2d:%.2d),%s, ", i+1, j+1, csCode);

			file.Write(csColData.GetBuffer(0), csColData.GetLength());
		}	
		CString csBreak = _T("");
		csBreak.Format("\r\n");
		file.Write(csBreak.GetBuffer(0), csBreak.GetLength());
	}
}
void CFunction::ExportTrayMapReport()
{
	std::list<tagTrayMapLog> TrayMapReport;
	TrayMapReport = m.TrayMap[0];

	//
	CArray<tagTrayMapReportData, tagTrayMapReportData> m_TrayMapReportData;
	m_TrayMapReportData.RemoveAll();

	//
	TrayMapReport.reverse();
	std::list<tagTrayMap>::iterator p = TrayMapReport.begin();

	for(int i=0; i<TrayMapReport.size(); i++, p++)
	{
		CString csLog = _T("");
		csLog.Format("%d, %d, %s", p->pos.y, p->pos.x, p->code);

		tagTrayMapReportData m_Data;
		m_Data.x = p->pos.x;
		m_Data.y = p->pos.y;

		LogTrayMapCSV( csLog );
	}
}
void CFunction::LoadTrayMap()
{
	CString csFile = _T("");
	csFile = m.FilePath.TrayMapPath;

	CFile file0;
	tagTrayMap map;
	int size;
	if(file0.Open(csFile + "\\TrayMap0.txt", CFile::modeRead, NULL))
	{
		CArchive ar0(&file0, CArchive::load);
		int c = file0.GetLength();		// Make sure there have data
		if( c > 0 )
		{	
			ar0 >> size;			
			for(int i=0; i<size; i++)
			{
				ar0 >> map.code >> map.StackNo >> map.pos >> map.site >> map.temperature;
				m.TrayMap[0].push_back(map);
			}
		}
		ar0.Close();	
		file0.Close();
	}
	// Output 1 
/*
	CFile file1;
	if(file1.Open(csFile + "\\TrayMap1.txt", CFile::modeRead, NULL))
	{
		CArchive ar1(&file1, CArchive::load);
		int c = file1.GetLength();		// Make sure there have data
		if( c > 0 )
		{
			ar1 >> size;
			for(int i=0; i<size; i++)
			{
				ar1 >> map.code >> map.StackNo >> map.pos >> map.site >> map.temperature;
				m.TrayMap[1].push_back(map);
			}
		}
		ar1.Close();
		file1.Close();
	}
	// Output 2 Bin 2
	
	CFile file2;
	if(file2.Open(csFile + "\\TrayMap2.txt", CFile::modeRead, NULL))
	{
		CArchive ar2(&file2, CArchive::load);
		int c = file2.GetLength();		// Make sure there have data
		if( c > 0 )
		{
			ar2 >> size;
			for(int i=0; i<size; i++)
			{
				ar2 >> map.code >> map.StackNo >> map.pos >> map.site >> map.temperature;
				m.TrayMap[2].push_back(map);
			}
		}
		ar2.Close();
		file2.Close();		
	}
	// Output 3 Bin 3

	CFile file3;
	if(file3.Open(csFile + "\\TrayMap3.txt", CFile::modeRead, NULL))
	{
		CArchive ar3(&file3, CArchive::load);
		int c = file3.GetLength();		// Make sure there have data
		if( c > 0 )
		{
			ar3 >> size;
			for(int i=0; i<size; i++)
			{
				ar3 >> map.code >> map.StackNo >> map.pos >> map.site >> map.temperature;
				m.TrayMap[3].push_back(map);
			}
		}
		ar3.Close();
		file3.Close();		
	}
	// Output 4 Bin 4
*/
}
void CFunction::SaveTrayMap()
{
	CString csFile = _T("");
	csFile = m.FilePath.TrayMapPath;

	CFile file0;
	file0.Open( csFile + "\\TrayMap0.txt", CFile::modeCreate | CFile::modeWrite
		| CFile::modeNoTruncate | CFile::shareDenyNone, NULL);
	CArchive ar0(&file0, CArchive::store);
	std::list<tagTrayMap>::iterator p0 = m.TrayMap[0].begin();
	ar0 << m.TrayMap[0].size();
	for(int i=0; i<m.TrayMap[0].size(); i++, p0++)
	{
		ar0 << p0->code << p0->StackNo << p0->pos << p0->site << p0->temperature;
	}
	ar0.Close();
	file0.Close();
	// Output 1
/*
	CFile file1;
	file1.Open( csFile + "\\TrayMap1.txt", CFile::modeCreate | CFile::modeWrite
		| CFile::modeNoTruncate | CFile::shareDenyNone, NULL);
	CArchive ar1(&file1, CArchive::store);
	std::list<tagTrayMap>::iterator p1 = m.TrayMap[1].begin();
	ar1 << m.TrayMap[1].size();
	for(i=0; i<m.TrayMap[1].size(); i++, p1++)
	{
		ar1 << p1->code << p1->StackNo << p1->pos << p1->site << p1->temperature;
	}
	ar1.Close();
	file1.Close();
	// Bin2 Bin
	
	CFile file2;
	file2.Open( csFile + "\\TrayMap2.txt", CFile::modeCreate | CFile::modeWrite
		| CFile::modeNoTruncate | CFile::shareDenyNone, NULL);
	CArchive ar2(&file2, CArchive::store);
	std::list<tagTrayMap>::iterator p2 = m.TrayMap[2].begin();
	ar2 << m.TrayMap[2].size();
	for(i=0; i<m.TrayMap[2].size(); i++, p2++)
	{
		ar2 << p2->code << p2->StackNo << p2->pos << p2->site << p2->temperature;
	}
	ar2.Close();
	file2.Close();
	// Bin3 Bin

	CFile file3;
	file3.Open( csFile + "\\TrayMap3.txt", CFile::modeCreate | CFile::modeWrite
		| CFile::modeNoTruncate | CFile::shareDenyNone, NULL);
	CArchive ar3(&file3, CArchive::store);
	std::list<tagTrayMap>::iterator p3 = m.TrayMap[3].begin();
	ar3 << m.TrayMap[3].size();
	for(i=0; i<m.TrayMap[3].size(); i++, p3++)
	{
		ar3 << p3->code << p3->StackNo << p3->pos << p3->site << p3->temperature;
	}
	ar3.Close();
	file3.Close();
	// Bin4 Bin
*/
}
// RepeatTray TrayMap
void CFunction::LoadTrayMapRepeat()
{
	CString csFile = _T("");
	csFile = m.FilePath.TrayMapPath;

	CFile file0;
	tagTrayMap map;
	int size;
	if(file0.Open(csFile + "\\TrayMap0.txt", CFile::modeRead, NULL))
	{
		CArchive ar0(&file0, CArchive::load);
		int c = file0.GetLength();		// Make sure there have data
		if( c > 0 )
		{	
			ar0 >> size;	
			for(int i=0; i<size; i++)
			{
				ar0 >> map.code >> map.StackNo >> map.pos >> map.site >> map.temperature;
				m.TrayMapRepeat[0].push_back(map);
			}
		}
		ar0.Close();	
		file0.Close();
	}
	// Tray 1 

	CFile file1;
	if(file1.Open(csFile + "\\TrayMap1.txt", CFile::modeRead, NULL))
	{
		CArchive ar1(&file1, CArchive::load);
		int c = file1.GetLength();		// Make sure there have data
		if( c > 0 )
		{
			ar1 >> size;
			for(int i=0; i<size; i++)
			{
				ar1 >> map.code >> map.StackNo >> map.pos >> map.site >> map.temperature;
				m.TrayMapRepeat[1].push_back(map);
			}
		}
		ar1.Close();
		file1.Close();
	}
	// Tray 2
}
void CFunction::SaveTrayMapRepeat()
{
	CString csFile = _T("");
	csFile = m.FilePath.TrayMapPath;

	CFile file0;
	if( file0.Open( csFile + "\\TrayMap0.txt", CFile::modeCreate | CFile::modeWrite
		| CFile::modeNoTruncate | CFile::shareDenyNone, NULL) )
	{
		CArchive ar0(&file0, CArchive::store);
		std::list<tagTrayMap>::iterator p0 = m.TrayMapRepeat[0].begin();
		ar0 << m.TrayMapRepeat[0].size();
		for(int i=0; i<m.TrayMapRepeat[0].size(); i++, p0++)
		{
			ar0 << p0->code << p0->StackNo << p0->pos << p0->site << p0->temperature;
		}
		ar0.Close();
		file0.Close();
	}	
	// Tray 1

	CFile file1;
	if( file1.Open( csFile + "\\TrayMap1.txt", CFile::modeCreate | CFile::modeWrite
		| CFile::modeNoTruncate | CFile::shareDenyNone, NULL) )
	{
		CArchive ar1(&file1, CArchive::store);
		std::list<tagTrayMap>::iterator p1 = m.TrayMapRepeat[1].begin();
		ar1 << m.TrayMapRepeat[1].size();
		for(int i=0; i<m.TrayMapRepeat[1].size(); i++, p1++)
		{
			ar1 << p1->code << p1->StackNo << p1->pos << p1->site << p1->temperature;
		}
		ar1.Close();
		file1.Close();
	}	
	// Tray 2
}
static CMutex MutexTrayMapRepeat;
void CFunction::AddTrayMapRepeat(int stack, CString code, CPoint point, int site, double temperature)
{
	CSingleLock Lock(&MutexTrayMapRepeat);
	Lock.Lock();

	tagTrayMap map;
	map.code = code;
	map.StackNo = stack;
	map.pos = point;
	map.site = site;
	map.temperature = temperature;
	m.TrayMapRepeat[stack].push_front(map);
	if(m.TrayMapRepeat[stack].size() > _Max_Tray_Map_Size)
		m.TrayMapRepeat[stack].pop_back();

	Lock.Unlock();
}
void CFunction::AddTrayMapRepeat(int stack, int bin, CPoint point, int site, double temperature)
{
	CSingleLock Lock(&MutexTrayMapRepeat);
	Lock.Lock();

	tagTrayMap map;
	map.code.Format("%d", bin);
	map.StackNo = stack;
	map.pos = point;
	map.site = site;
	map.temperature = temperature;
	m.TrayMapRepeat[stack].push_front(map);
	if(m.TrayMapRepeat[stack].size() > _Max_Tray_Map_Size)
		m.TrayMapRepeat[stack].pop_back();

	Lock.Unlock();
}
static CMutex MutexLog;
void CFunction::Log(int iLog)
{
	CSingleLock Lock(&MutexLog);
	Lock.Lock();

	CString csLog = _T("");
	csLog.Format("%d", iLog);
	
	CString cs = _T("");
	CString cstime;
	CTime time = CTime::GetCurrentTime();
	cs.Format("%s, %s\r\n", time.Format("%m/%d %H:%M:%S"), csLog);
	cstime.Format("%s",time.Format("%y-%m-%d"));
	
	CFile file;
	if( file.Open(".\\Log\\"+cstime+".txt", CFile::modeCreate | CFile::modeWrite
		| CFile::modeNoTruncate | CFile::shareDenyNone, NULL) )
	{		
		file.SeekToEnd();		
		file.Write(cs.GetBuffer(0), cs.GetLength());
		file.Close();
	}
	
	Lock.Unlock();
}
static CMutex MotorMutexLog;
void CFunction::MotorLog(CString csLog)
{
	//
	if( m.Setting.m_bEnableMotorLog == 0 )
		return;
	//

	CSingleLock Lock(&MotorMutexLog);
	Lock.Lock();
	
	CString cs;
	CString cstime;
	CTime time = CTime::GetCurrentTime();
	cs.Format("%s, %s\r\n", time.Format("%m/%d %H:%M:%S"), csLog);
	cstime.Format("cs %s",time.Format("%y-%m-%d"));
	
	CFile file;

	file.Open(".\\Log\\"+cstime+"_Motor.txt", CFile::modeCreate | CFile::modeWrite
		| CFile::modeNoTruncate | CFile::shareDenyNone, NULL);
	
	file.SeekToEnd();
	
	file.Write(cs.GetBuffer(0), cs.GetLength());
	file.Close();
	
	Lock.Unlock();
}
static CMutex MotorSingleSpeedMutexLog;
void CFunction::SingleMotorLog(CString csLog)
{
	//
	if( m.Setting.m_bEnableSingleMotorLog == 0 )
		return;
	//

	CSingleLock Lock(&MotorSingleSpeedMutexLog);
	Lock.Lock();
	
	CString cs;
	CString cstime;
	CTime time = CTime::GetCurrentTime();
	cs.Format("%s, %s\r\n", time.Format("%m/%d %H:%M:%S"), csLog);
	cstime.Format("%s",time.Format("%y-%m-%d"));
	
	CFile file;

	file.Open(".\\Log\\"+cstime+"_SingleSpeedMotor.txt", CFile::modeCreate | CFile::modeWrite
		| CFile::modeNoTruncate | CFile::shareDenyNone, NULL);
	
	file.SeekToEnd();
	
	file.Write(cs.GetBuffer(0), cs.GetLength());
	file.Close();
	
	Lock.Unlock();
}
static CMutex MotorSpeedMutexLog;
void CFunction::SpeedMotorLog(CString csLog)
{
	//
	if( m.Setting.m_bEnableDualMotorLog == 0 )
		return;
	//

	CSingleLock Lock(&MotorSpeedMutexLog);
	Lock.Lock();
	
	CString cs;
	CString cstime;
	CTime time = CTime::GetCurrentTime();
	cs.Format("%s, %s\r\n", time.Format("%m/%d %H:%M:%S"), csLog);
	cstime.Format("%s",time.Format("%y-%m-%d"));
	
	CFile file;

	file.Open(".\\Log\\"+cstime+"_SpeedMotor.txt", CFile::modeCreate | CFile::modeWrite
		| CFile::modeNoTruncate | CFile::shareDenyNone, NULL);
	
	file.SeekToEnd();
	
	file.Write(cs.GetBuffer(0), cs.GetLength());
	file.Close();
	
	Lock.Unlock();
}

static CMutex csMutexCSVLog;
void CFunction::LogCSV(CString csLog, int iThread )
{
	CSingleLock Lock(&csMutexCSVLog);
	Lock.Lock();

	if( m.Setting.m_bEnableStatusReportLog == 0 )
	{
		Lock.Unlock();
		return;
	}

	// 
	// 我只需要 Arm, TestSite, Tester 相關 Log.
	if( iThread == theApp.enDArm || 
		iThread == theApp.enDTestSite || 
		iThread == theApp.enDTester ||
		iThread == theApp.enDManual )
	{
	
	}
	else
	{
		Lock.Unlock();
		return;
	}

	static CString csLogContact = "";
	if( csLogContact != csLog )
	{
		csLogContact = csLog;
	}
	else
	{
		// 如果是重複的...那就不要再寫入資料.
		Lock.Unlock();
		return;
	}

	//
	// Get Systme Time...
	SYSTEMTIME Time;
	::GetLocalTime(&Time);

	// Convert Time Format
	CString csMounth	= "";
	CString csDay		= "";
	CString csHour		= "";
	CString csMin		= "";

	if( Time.wMonth < 10 )
		csMounth.Format("0%d", Time.wMonth );
	else
		csMounth.Format("%d", Time.wMonth );
	if( Time.wDay < 10 )
		csDay.Format("0%d", Time.wDay );
	else
		csDay.Format("%d", Time.wDay );

	if( Time.wHour < 10 )
		csHour.Format("0%d", Time.wHour );
	else
		csHour.Format("%d", Time.wHour );

	if( Time.wMinute < 10 )
		csMin.Format("0%d", Time.wMinute );
	else
		csMin.Format("%d", Time.wMinute );

	// Create File
	CString csFileNameTime;
	csFileNameTime.Format("Report_%d%s%s_%s", Time.wYear, csMounth, csDay, csHour );
	CString csFileName = csFileNameTime + _StatusReportLog;
	CString csFile = ".\\Log\\" + csFileName;

	CString csThread = "None";
	if( iThread == theApp.enDArm )
		csThread = "Arm";
	else if( iThread == theApp.enDTestSite )
		csThread = "Ts";
	else if( iThread == theApp.enDTester )
		csThread = "Tester";
	else if( iThread == theApp.enDManual )
		csThread = "Manual";
	else
		csThread = "None";
	//

	CTime time = CTime::GetCurrentTime();
	// Time
	CString cstime = _T("");
	SYSTEMTIME ti; 
	GetLocalTime(&ti);
	cstime.Format("%d.%d.%d.%d.%5.2f", 
		ti.wMonth, ti.wDay, ti.wHour, ti.wMinute, ti.wSecond + ( ti.wMilliseconds / 1000. ) );

	// File write
	CFile file;	
	CString csDATA = "";
	int iSerial = 0;
	CString csSerial;
	if(file.Open(csFile, CFile::modeCreate | CFile::modeWrite | CFile::shareDenyNone
		| CFile::modeNoTruncate, NULL) != 0)
	{

		csDATA.Format("%s, %s, %s\r\n", cstime, csThread, csLog );

		file.SeekToEnd();
		file.Write(csDATA.GetBuffer(0), csDATA.GetLength());
		file.Close();
	}

	Lock.Unlock();
}

void CFunction::CloseAllOutput()
{

	
}
void CFunction::MotorServoOffForAlignmentNoTs()
{
	// Servo Off Motor for alignment
	// Note : When Alignment Dialog Open	
	f.Motor.Servo( &m.m_Motor.ArmX, false );
	f.Motor.Servo( &m.m_Motor.ArmY, false );
	f.Motor.Servo( &m.m_Motor.ArmZ, false );
}
void CFunction::MotorServoOffForAlignment()
{
	// Servo Off Motor for alignment
	// Note : When Alignment Dialog Open	
	f.Motor.Servo( &m.m_Motor.ArmX, false );
	f.Motor.Servo( &m.m_Motor.ArmY, false );
	f.Motor.Servo( &m.m_Motor.ArmZ, false );
	f.Motor.Servo( &m.m_Motor.Inserter, false );
}
void CFunction::MotorServoOffAll()
{
#ifdef _Demo
	return;
#endif
	// Servo Off All Motor 
	// Note : When App Close
	f.Motor.Servo( &m.m_Motor.ArmX, false );
	f.Motor.Servo( &m.m_Motor.ArmY, false );
	f.Motor.Servo( &m.m_Motor.ArmZ, false );
	f.Motor.Servo( &m.m_Motor.Inserter, false );
}
void CFunction::MotorServoOnAll()
{
	// Servo On All Motor 
	// Note : When App start
	f.Motor.Servo( &m.m_Motor.ArmX, true );
	f.Motor.Servo( &m.m_Motor.ArmY, true );
	f.Motor.Servo( &m.m_Motor.ArmZ, true );
	f.Motor.Servo( &m.m_Motor.Inserter, true );
}

void CFunction::CycleCounter()
{
	m.CalcInfo.CycleTimes++;
}
void CFunction::Counter(int iBin)
{
	// For RunPage calc counter.
	if( iBin == theApp.enBin1 )
		m.Counter.OutputCount[0]++;
	else if( iBin == theApp.enBin2 )
		m.Counter.OutputCount[1]++;
	else if( iBin == theApp.enBin3 )
		m.Counter.OutputCount[2]++;
	else if( iBin == theApp.enBin4 )	// Altera 發現居然只有 enBin4 打成 enBin3	// 導致 enBin4 無法加總 Denny 發現 已經跑 21顆IC可是 Total 只有 4顆
		m.Counter.OutputCount[3]++;	
	else
		; // Never be here.

	m.CalcInfo.TestedIC = m.Counter.OutputCount[0] + 
		m.Counter.OutputCount[1] + 
		m.Counter.OutputCount[2] +
		m.Counter.OutputCount[3];
}

int CFunction::RandResult()
{
	CTime time = CTime::GetCurrentTime();

	int randNo = 0;

	int sec = time.GetSecond();
	if( sec > 0 && sec < 15 )		// 0 - 15
		randNo = 0;	// Pass Bin
	else if( sec > 15 && sec < 25 )	// 15 - 25
		randNo = 1;	// Bin 2
	else if( sec > 25 && sec < 40 )	// 25 - 40
		randNo = 2;	// Bin 2
	else
		randNo = 3;	// Bin 3

	return randNo;
}

void CFunction::SetCoord()
{
/////////////////////////////////////////////////////////////
// Coord

	// Set Input Tray Coord.
	theApp.m_InputTray.SetCoordinate( m.FilePath.InputCoordPath );
	theApp.m_Tray1.SetCoordinate( m.FilePath.Tray1CoordPath );
	// Set Output Tray Coord 
	theApp.m_OutputTray.SetCoordinate( m.FilePath.Output1CoordPath );
	theApp.m_Tray2.SetCoordinate( m.FilePath.Tray2CoordPath );
	// Reset TrayStatus
	theApp.m_InputTray.SetLocation();
	theApp.m_Tray1.SetLocation();
	theApp.m_OutputTray.SetLocation();
	theApp.m_Tray2.SetLocation();
	//
	theApp.m_InputTray.SetLocationStatus();
	theApp.m_Tray1.SetLocationStatus();
	theApp.m_OutputTray.SetLocationStatus();
	theApp.m_Tray2.SetLocationStatus();
}

void CFunction::SetTrayData()
{
	// 1: Set Align
	// 2: Set Gear
	// 3: Set Tary Spec
	// 4: Set Me value.
	// 5: Set Coord ( FilePath and reset the iNow and iNext. )

	// 1: Set Align
	// Set Input Tray Alignment.
	theApp.m_InputTray.SetAlign( m.m_Align.Input );
	theApp.m_Tray1.SetAlign( m.m_Align.Input );
	// Set Output Tray Alignment
	theApp.m_OutputTray.SetAlign( m.m_Align.Output1 );
	theApp.m_Tray2.SetAlign( m.m_Align.Output1 );

//////////////////////////////////////////////////////////////
//  Input / Output Stack
	// Set Output Tary Gear Ration
	tagXYZ InputGear;
	tagXYZ Output1Gear;
	tagXYZ PreHeaterGear;
	
	// Input 
	InputGear.x			= m.m_Ratio.X_GearRation;
	InputGear.y			= m.m_Ratio.Y_GearRation;
	InputGear.z			= m.m_Ratio.Z_GearRation;

	// Output 1 
	Output1Gear.x		= m.m_Ratio.X_GearRation;
	Output1Gear.y		= m.m_Ratio.Y_GearRation;
	Output1Gear.z		= m.m_Ratio.Z_GearRation;
	
	// PreHeater
	PreHeaterGear.x		= m.m_Ratio.X_GearRation;
	PreHeaterGear.y		= m.m_Ratio.Y_GearRation;
	PreHeaterGear.z		= m.m_Ratio.Z_GearRation;

	// 2: Set Gear
	theApp.m_InputTray.SetGear( InputGear );			// Auto Input
	theApp.m_Tray1.SetGear( InputGear );
	theApp.m_OutputTray.SetGear( Output1Gear );			// Auto Output
	theApp.m_Tray2.SetGear( Output1Gear );	
	theApp.m_PreHeaterTray.SetGear( PreHeaterGear );	// Pre-Heater

	// Chip Tray
	theApp.m_InputTray.SetChipMode(	m.TraySpec.m_InputUseChipTray );
	theApp.m_Tray1.SetChipMode(	m.TraySpec.m_InputUseChipTray );
	theApp.m_OutputTray.SetChipMode( m.TraySpec.m_OutputUseChipTray );
	theApp.m_Tray2.SetChipMode( m.TraySpec.m_OutputUseChipTray );

	// 3: Set Tary Spec
	theApp.m_InputTray.SetSpec(	m.TraySpec );
	theApp.m_Tray1.SetSpec(	m.TraySpec );
	theApp.m_OutputTray.SetSpec( m.TraySpec );
	theApp.m_Tray2.SetSpec( m.TraySpec );
	theApp.m_PreHeaterTray.SetSpec( m.TraySpec );
	// 4: Set Me value.
	theApp.m_InputTray.SetMe( ( _Stack_A * m.m_Ratio.Y_GearRation ), ( _Stack_B * m.m_Ratio.X_GearRation ));
	theApp.m_Tray1.SetMe( ( _Stack_A * m.m_Ratio.Y_GearRation ), ( _Stack_B * m.m_Ratio.X_GearRation ));
	theApp.m_OutputTray.SetMe( ( _Stack_A * m.m_Ratio.Y_GearRation ),  ( _Stack_B * m.m_Ratio.X_GearRation ));
	theApp.m_Tray2.SetMe( ( _Stack_A * m.m_Ratio.Y_GearRation ),  ( _Stack_B * m.m_Ratio.X_GearRation ));
	theApp.m_PreHeaterTray.SetMe( ( _PreHeater_A * m.m_Ratio.X_GearRation ), ( _PreHeater_B * m.m_Ratio.Y_GearRation ));

/////////////////////////////////////////////////////////////
// Coord

	theApp.m_InputTray.SetCoordinate( m.FilePath.InputCoordPath );			// Input
	theApp.m_Tray1.SetCoordinate( m.FilePath.Tray1CoordPath );
	theApp.m_OutputTray.SetCoordinate( m.FilePath.Output1CoordPath );		// Output1 Pass
	theApp.m_Tray2.SetCoordinate( m.FilePath.Tray2CoordPath );

	// Reset TrayStatus	// Set CTrayFile iNow and iNext value.
	theApp.m_InputTray.SetLocation();				// Input
	theApp.m_Tray1.SetLocation();
	theApp.m_OutputTray.SetLocation();				// Output1
	theApp.m_Tray2.SetLocation();

	// Reset TrayStatus // Set enOK status to Tray
	theApp.m_InputTray.SetLocationStatus();			// Input
	theApp.m_Tray1.SetLocationStatus();
	theApp.m_OutputTray.SetLocationStatus();		// Output
	theApp.m_Tray2.SetLocationStatus();
}

CString CFunction::StringToIntArrayByToken(CString cs, CArray <int, int> &array, CString token)
{
	array.RemoveAll();
	while(1)
	{
		int i = cs.Find(",", 0);
		if(i == -1)
		{
			if(cs.GetLength() > 0)
			{
				int ii = atoi(cs.GetBuffer(0));
				if(ii > -100)
					array.Add(ii);
			}
			break;
		}
		else
		{			
			CString csT = cs.Left(i);
			cs.Delete(0, i+1);
			if(csT.GetLength() > 0)
			{
				int ii = atoi(csT.GetBuffer(0));
				if(ii > -100)
					array.Add(ii);
			}
		}
	}

	CString csNew;
	for(int i=0; i<array.GetSize(); i++)
	{
		CString ccs;
		ccs.Format("%d", array.GetAt(i));
		csNew += ccs;
		if(i < array.GetSize() - 1)
			csNew +=",";
	}

	return csNew;
}

CString CFunction::StringToIntArrayByToken(CString cs, CArray <double, double> &array, CString token)
{
	array.RemoveAll();
	while(1)
	{
		int i = cs.Find(",", 0);
		if(i == -1)
		{
			if(cs.GetLength() > 0)
			{
				double ii = atof(cs.GetBuffer(0));
				if(ii > -100)
					array.Add(ii);
			}
			break;
		}
		else
		{			
			CString csT = cs.Left(i);
			cs.Delete(0, i+1);
			if(csT.GetLength() > 0)
			{
				double ii = atof(csT.GetBuffer(0));
				if(ii > -100)
					array.Add(ii);
			}
		}
	}

	CString csNew;
	for(int i=0; i<array.GetSize(); i++)
	{
		CString ccs;
		ccs.Format("%5.2f", array.GetAt(i));
		csNew += ccs;
		if(i < array.GetSize() - 1)
			csNew +=",";
	}

	return csNew;
}
CString CFunction::StringToIntArrayByToken(CString cs, CArray <CString, CString> &array, CString token)
{
	array.RemoveAll();
	while(1)
	{
		int i = cs.Find(",", 0);
		if(i == -1)
		{
			if(cs.GetLength() > 0)
			{
				CString ii = (cs.GetBuffer(0));
//				if(ii > -100)
					array.Add(ii);
			}
			break;
		}
		else
		{			
			CString csT = cs.Left(i);
			cs.Delete(0, i+1);
			if(csT.GetLength() > 0)
			{
				CString ii = (csT.GetBuffer(0));
//				if(ii > -100)
					array.Add(ii);
			}
		}
	}

	CString csNew;
	for(int i=0; i<array.GetSize(); i++)
	{
		CString ccs;
		ccs.Format("%s", array.GetAt(i));
		csNew += ccs;
		if(i < array.GetSize() - 1)
			csNew +=",";
	}

	return csNew;
}

// 
// 清除舊檔案, 避免 Log 檔過大.!
void CFunction::DeleteOldFile(CString FileExt, int DaysBefore)
{
	COleDateTime tOld = COleDateTime::GetCurrentTime() - COleDateTimeSpan(DaysBefore, 0, 0, 0);

	CFileFind find;
	BOOL bResult;
	bResult = find.FindFile(FileExt);
	CTime tTime;
	while(bResult)
	{
		bResult = find.FindNextFile();
		find.GetCreationTime(tTime);
		COleDateTime tFile(tTime.GetTime());
		if(tFile < tOld)
			::DeleteFile(find.GetFilePath());
	}
	find.Close();
}

// 
// Altera 想要知道 Contact Counter 的資訊
void CFunction::LoadContactCounter()
{
	CString csFile = _T("");
	csFile = m.FilePath.SystemSettingPath;
	GetSetting(csFile, "Contact Counter", "Socket Counter", m.m_ContactCounterValue.lContactConter );

}
void CFunction::SaveContactCounter()
{
	CString csFile = _T("");
	csFile = m.FilePath.SystemSettingPath;
	SaveSetting(csFile, "Contact Counter", "Socket Counter", m.m_ContactCounterValue.lContactConter );
}

//
void CFunction::LoadSMTPSetting()
{
	CString csFile;
	csFile = m.FilePath.SMPTPath;

	GetSetting(csFile, "SMTP", "Content1",		m.m_MailSetting.csContent1);
	GetSetting(csFile, "SMTP", "Content2",		m.m_MailSetting.csContent2);
	GetSetting(csFile, "SMTP", "Mail From",		m.m_MailSetting.csMailFrom);
	GetSetting(csFile, "SMTP", "Login Name",	m.m_MailSetting.csSMTPUserName);
	GetSetting(csFile, "SMTP", "Login Pwd",		m.m_MailSetting.csSMTPPassword);
	GetSetting(csFile, "SMTP", "Port",			m.m_MailSetting.iSMTPPort);
	GetSetting(csFile, "SMTP", "Server",		m.m_MailSetting.csSMTPServer);
	GetSetting(csFile, "SMTP", "Subject",		m.m_MailSetting.csMailSubject);
	GetSetting(csFile, "SMTP", "Mail To1",		m.m_MailSetting.csMailTo1);
	GetSetting(csFile, "SMTP", "Mail To2",		m.m_MailSetting.csMailTo2);
	GetSetting(csFile, "SMTP", "Mail Name",		m.m_MailSetting.csShowName);

}
void CFunction::SaveSMTPSetting()
{
	CString csFile;
	csFile = m.FilePath.SMPTPath;

	SaveSetting(csFile, "SMTP", "Content1",		m.m_MailSetting.csContent1);
	SaveSetting(csFile, "SMTP", "Content2",		m.m_MailSetting.csContent2);
	SaveSetting(csFile, "SMTP", "Mail From",	m.m_MailSetting.csMailFrom);
	SaveSetting(csFile, "SMTP", "Login Name",	m.m_MailSetting.csSMTPUserName);
	SaveSetting(csFile, "SMTP", "Login Pwd",	m.m_MailSetting.csSMTPPassword);
	SaveSetting(csFile, "SMTP", "Port",			m.m_MailSetting.iSMTPPort);
	SaveSetting(csFile, "SMTP", "Server",		m.m_MailSetting.csSMTPServer);
	SaveSetting(csFile, "SMTP", "Subject",		m.m_MailSetting.csMailSubject);
	SaveSetting(csFile, "SMTP", "Mail To1",		m.m_MailSetting.csMailTo1);
	SaveSetting(csFile, "SMTP", "Mail To2",		m.m_MailSetting.csMailTo2);
	SaveSetting(csFile, "SMTP", "Mail Name",	m.m_MailSetting.csShowName);
}

void CFunction::LoadCatoregyColor()
{
	CString csFile;
	csFile = m.FilePath.TrayPath;

	for( int i=0;i<_Tray_Bin;i++)
	{
		CString csBinColor;
		csBinColor.Format("%d", i );
		GetSetting(csFile, "Bin Color", csBinColor,	m.iBinColor[i] = 65535);
		m.iBinColor[i] = m.iBinColor[i];
	}
}
//
void CFunction::LoadAutoRetryExterndValue()
{
	CString csFile;
	csFile = m.FilePath.AutoRetrySettingPath;

	//
	GetSetting(csFile, "Arm Z Auto Retry Adjust", "Always Adjust(1)Y(0)N",	m.m_AutoRetryAjsutValue.iAlwaysAdjsut = 0 );
	GetSetting(csFile, "Arm Z Auto Retry Adjust", "Adjust Value(mm)",		m.m_AutoRetryAjsutValue.dAdjustValue = 0.5 );
}
void CFunction::SaveAutoRetryExterndValue()
{
	CString csFile;
	csFile = m.FilePath.AutoRetrySettingPath;

	//
	SaveSetting(csFile, "Arm Z Auto Retry Adjust", "Always Adjust(1)Y(0)N",	m.m_AutoRetryAjsutValue.iAlwaysAdjsut );
	SaveSetting(csFile, "Arm Z Auto Retry Adjust", "Adjust Value(mm)",		m.m_AutoRetryAjsutValue.dAdjustValue );
}
void CFunction::LoadAutoRetryEnable()
{
	CString csFile;
	csFile = m.FilePath.SystemSettingPath;

	GetSetting(csFile, "Setting", "Arm Z Auot Retry",	m.Setting.m_bArmZAutoRetry );
}
void CFunction::SaveAutoRetryEnable()
{
	CString csFile;
	csFile = m.FilePath.SystemSettingPath;

	SaveSetting(csFile, "Setting", "Arm Z Auot Retry",	m.Setting.m_bArmZAutoRetry );
}
void CFunction::LoadTorqueCtrlLimit()
{
	CString csFile = _T("");
	csFile = m.FilePath.UIPath;

	GetSetting( csFile, "Torque UI", "UI Max Limit(kg)", m.Setting.m_iTorqueHighLimit = 50 );
	GetSetting( csFile, "Torque UI", "UI Min Limit(kg)", m.Setting.m_iTorqueLowLimit = 2 );
}
void CFunction::SaveTorqueCtrlLimit()
{
	CString csFile = _T("");
	csFile = m.FilePath.UIPath;

	GetSetting( csFile, "Torque UI", "UI Max Limit", m.Setting.m_iTorqueHighLimit );
	GetSetting( csFile, "Torque UI", "UI Min Limit", m.Setting.m_iTorqueLowLimit );
}
void CFunction::LoadAutoRetrySetting()
{
	CString csFile;
	csFile = m.FilePath.UIPath;

	//
	GetSetting( csFile, "Arm Z Auto Retry", "Retry Counter ", m.Setting.m_iAutoRetrySetting );
}
void CFunction::SaveAutoRetrySetting()
{
	CString csFile;
	csFile = m.FilePath.UIPath;

	//
	SaveSetting( csFile, "Arm Z Auto Retry", "Retry Counter ", m.Setting.m_iAutoRetrySetting );
}
static CMutex MutexIncraseThreadCount;
void CFunction::IncraseThreadCount()
{
	CSingleLock Lock(&MutexIncraseThreadCount);
	Lock.Lock();

	m.Info.iThreadCount++;

	Lock.Unlock();
}
static CMutex MutexReduceThreadCount;
void CFunction::ReduceThreadCount()
{
	CSingleLock Lock(&MutexReduceThreadCount);
	Lock.Lock();

	m.Info.iThreadCount--;

	Lock.Unlock();
}
void CFunction::ExportSummaryReport()
{
	f.Report.SetReport_BinLog();
}
void CFunction::ClearYieldCtrl()
{
	m.m_YieldCtrl.m_lContinueFail = 0;
	m.m_YieldCtrl.m_lTested		  = 0;
	m.m_YieldCtrl.m_iPFArray.RemoveAll();
	m.m_YieldCtrl.m_dFailRate	  = 0;
}

// 1.0Af
// Remove this function, and re-build new one
/*
void CFunction::ExportErrorRateReport()
{	
	if( m.Setting.m_bEnableJamRateReport == 1 )
	{
		// 刪除前一份
		CString csFile = _T("");
		csFile = m.FilePath.JamRateReportPath;
		::DeleteFile( csFile );

		//
		CFile file;
		if(file.Open(csFile, CFile::modeCreate | CFile::modeWrite | CFile::shareDenyNone
			| CFile::modeNoTruncate, NULL) != 0)
		{
			CString csContent = _T("");

			// Lot Number		
			CString csLotNumber = _T("");
			csLotNumber.Format("Lot Number: %s\r\n", m.LotInfo.LotInfoNo );
			csContent = csContent + csLotNumber;

			// Lot Start 
			CString csLotStart = _T("");
			csLotStart.Format("Lot Start: %s\r\n", m.LotInfo.LotStartTime );
			csContent = csContent + csLotStart;

			// Get Total.
			CString csTotal = _T("");
			long total = 0;
			int i = 0;
			for(i=0; i<_Output_Stack_No; i++)
				total += m.Counter.OutputCount[i];
			csTotal.Format("Total IC: %d\r\n", total );
			csContent = csContent + csTotal;

			// Get Error Count
			int iErrorCount = GetJamRateCount();
			CString csErrorCount = _T("");
			csErrorCount.Format("ErrorCount: %d\r\n", iErrorCount );
			csContent = csContent + csErrorCount;

			// Rate
			CString csRate = _T("");
			if( total > 0 )
			{
				double dtotal = total;
				double dErrorCount = iErrorCount;
				csRate.Format("Error Rate: %5.2f\r\n", (double)(dErrorCount / total) );
			}
			else
				csRate.Format("Error Rate: No Tested\r\n" );
			csContent = csContent + csRate;

			//
			CString csLine = _T("");
			csLine.Format("-----------------------------------------\r\n");
			csContent = csContent + csLine;
			
			CString csCodeList = _T("");
			csCodeList = GetJamRateCodeList();
			csContent = csContent + csCodeList;

			// Write to File...
			file.SeekToEnd();
 			file.Write(csContent.GetBuffer(0), csContent.GetLength());
		}

		file.Close();

		// 清除全部的資料
		ClearRateData();

	}//Enable
}
*/
void CFunction::ExportErrorRateReport()
{	
	if( m.Setting.m_bEnableJamRateReport == 1 )
	{
		// 刪除前一份
		CString csFile = _T("");
		csFile = m.FilePath.JamRateReportPath;
		::DeleteFile( csFile );

		//
		CFile file;
		if(file.Open(csFile, CFile::modeCreate | CFile::modeWrite | CFile::shareDenyNone
			| CFile::modeNoTruncate, NULL) != 0)
		{
			CString csContent = _T("");

			// Lot Number		
			CString csLotNumber = _T("");
			csLotNumber.Format("Lot Number: %s\r\n", m.LotInfo.LotInfoNo );
			csContent = csContent + csLotNumber;

			// Lot Start 
			CString csLotStart = _T("");
			csLotStart.Format("Lot Start: %s\r\n", m.LotInfo.LotStartTime );
			csContent = csContent + csLotStart;

			// Get Total.
			CString csTotal = _T("");
			long total = 0;
			int i = 0;
			/*
			for(i=0; i<_Output_Stack_No; i++)
				total += m.Counter.OutputCount[i];
			*/
			total = m.m_JamRateInfo.m_lTotalUnit;
			csTotal.Format("Total IC: %d\r\n", total );
			csContent = csContent + csTotal;

			// Get Error Count
			int iErrorCount = GetJamRateCount();
			CString csErrorCount = _T("");
			csErrorCount.Format("ErrorCount: %d\r\n", iErrorCount );
			csContent = csContent + csErrorCount;

			// Rate
			CString csRate = _T("");
			if( total > 0 )
			{
				double dtotal = total;
				double dErrorCount = iErrorCount;
				csRate.Format("Error Rate: %5.2f %%, (%d/%d)\r\n", 
					(double)(dErrorCount / total), iErrorCount, total );
			}
			else
				csRate.Format("Error Rate: No Tested\r\n" );
			csContent = csContent + csRate;

			//
			CString csLine = _T("");
			csLine.Format("-----------------------------------------\r\n");
			csContent = csContent + csLine;
			
			CString csCodeList = _T("");
			csCodeList = GetJamRateCodeList();
			csContent = csContent + csCodeList;

			// Write to File...
			file.SeekToEnd();
 			file.Write(csContent.GetBuffer(0), csContent.GetLength());
		}

		file.Close();

		// 清除全部的資料
		ClearRateData();

	}//Enable
}
void CFunction::LoadJamRateData()
{
	if( m.Setting.m_bEnableJamRateReport == 1 )
	{
		CString csFile;
		csFile = m.FilePath.JamRateResultPath;

		
		CString csCode = _T("");
		tagRateDataLogData m_SingleData;

		int iCount = 0;
		int iSize = m.m_ErrorRateData.GetSize();
		for(int i=0;i<iSize;i++)
		{
			iCount = 0;
			csCode.Format("%d", m.m_ErrorRateData.GetAt(i).iCode );
			f.GetSetting( csFile, "ErrorCode Count", csCode, iCount );
			m_SingleData.iCode	= m.m_ErrorRateData.GetAt(i).iCode;
			m_SingleData.iCount = iCount; 
			m.m_ErrorRateData.SetAt(i, m_SingleData );			
		}
	}
}
void CFunction::ErrorRateControl(int iErrorCode)
{
	if( m.Setting.m_bEnableJamRateReport == 1 )
	{
		int iSize = m.m_ErrorRateData.GetSize();
		int iCode = 0;
		tagRateDataLogData m_SingleData;
		int iCount = 0;
		for(int i=0;i<iSize;i++)
		{
			iCode = 0;
			iCode = m.m_ErrorRateData.GetAt(i).iCode;
			if( iErrorCode == iCode )
			{
				iCount = m.m_ErrorRateData.GetAt(i).iCount;
				iCount++;

				m_SingleData.iCode = 0;
				m_SingleData.iCount = 0;
				//
				m_SingleData.iCode = iErrorCode;
				m_SingleData.iCount = iCount;

				m.m_ErrorRateData.SetAt(i, m_SingleData );
			}
		}
		SaveJamRateData();
	}
}
CString CFunction::GetJamRateCodeList()
{
	CString csCodeList = _T("");

	if( m.Setting.m_bEnableJamRateReport == 1 )
	{
		int iCode = 0;
		CString csCode = _T("");
		int iSize = m.m_ErrorRateData.GetSize();
		for(int i=0;i<iSize;i++)
		{
			iCode = 0;
			iCode = m.m_ErrorRateData.GetAt(i).iCode;
			
			csCode.Format("%d\r\n", iCode );
			csCodeList = csCodeList + csCode;
		}
	}
	return csCodeList;
}
int CFunction::GetJamRateCount()
{
	int iErrorCount = 0;
	if( m.Setting.m_bEnableJamRateReport == 1 )
	{
		int iCount = 0;
		int iSize = m.m_ErrorRateData.GetSize();
		for(int i=0;i<iSize;i++)
		{
			iCount = 0;
			iCount = m.m_ErrorRateData.GetAt(i).iCount;
			
			iErrorCount = iErrorCount + iCount;
		}
	}
	return iErrorCount;
}
void CFunction::ClearRateData()
{
	if( m.Setting.m_bEnableJamRateReport == 1 )
	{
		CString csFile;
		csFile = m.FilePath.JamRateResultPath;

		CString csCode = _T("");
		int iCount = 0;		
		int iSize = m.m_ErrorRateData.GetSize();
		for(int i=0;i<iSize;i++)
		{
			// 清掉數值
			iCount = 0;
			csCode.Format("%d", m.m_ErrorRateData.GetAt(i).iCode );
			f.SaveSetting( csFile, "ErrorCode Count", csCode, iCount );
		}

		// 清除後再重新載入
		LoadJamRateData();
	}
}

void CFunction::SaveJamRateData()
{
	if( m.Setting.m_bEnableJamRateReport == 1 )
	{
		CString csFile = _T("");
		csFile = m.FilePath.JamRateResultPath;

		CString csCode = _T("");
		int iCount = 0;		
		int iSize = m.m_ErrorRateData.GetSize();
		for(int i=0;i<iSize;i++)
		{
			iCount = m.m_ErrorRateData.GetAt(i).iCount;
			csCode.Format("%d", m.m_ErrorRateData.GetAt(i).iCode );
			f.SaveSetting( csFile, "ErrorCode Count", csCode, iCount );
		}
	}
}
void CFunction::LoadJamRateCode()
{
	if( m.Setting.m_bEnableJamRateReport == 1 )
	{		
		CString csFile;
		csFile = m.FilePath.JamRateCodePath;		

		//
		CFile file;	
		if(file.Open(csFile, CFile::modeRead  | CFile::shareDenyNone, NULL) != 0)
		{
			file.SeekToBegin();
			CArchive ar(&file, CArchive::load);
			CString cs;
			
			while(1)
			{
				BOOL bReadOK = ar.ReadString(cs);
				if( !bReadOK )
					break;

				//
				cs.TrimLeft();
				cs.TrimRight();
				//

				tagRateDataLogData m_SingleData;
				m_SingleData.iCode	= atoi(cs);
				m_SingleData.iCount = 0;
				m.m_ErrorRateData.Add( m_SingleData );
			}

			ar.Close();
			file.Close();
		}
		else
		{
			// Open Fail. ( File is not exists )
			// create new one			
			if(file.Open(csFile, CFile::modeCreate | CFile::shareDenyNone, NULL) != 0)
			{
				//
			}

			file.Close();
		}

	}// Enable
}

static CMutex MutexEventLogReport;
void CFunction::ExportEventLog()
{
	CSingleLock Lock(&MutexEventLogReport);
	Lock.Lock();

	//
	// Get Systme Time...
	SYSTEMTIME Time;
	::GetLocalTime(&Time);

	// Convert Time Format
	CString csMounth	= "";
	CString csDay		= "";
	CString csHour		= "";
	CString csMin		= "";

	if( Time.wMonth < 10 )
		csMounth.Format("0%d", Time.wMonth );
	else
		csMounth.Format("%d", Time.wMonth );
	if( Time.wDay < 10 )
		csDay.Format("0%d", Time.wDay );
	else
		csDay.Format("%d", Time.wDay );

	if( Time.wHour < 10 )
		csHour.Format("0%d", Time.wHour );
	else
		csHour.Format("%d", Time.wHour );

	if( Time.wMinute < 10 )
		csMin.Format("0%d", Time.wMinute );
	else
		csMin.Format("%d", Time.wMinute );

	// Create File
	CString csFileNameTime;
	csFileNameTime.Format("%d%s%s_%s%s_", Time.wYear, csMounth, csDay, csHour, csMin );
	CString csFileName = csFileNameTime + _EventLogFileName + _EventLogReport;
	CString csFile = m.CustomFilePath.EventLogReportPath + csFileName;

	//確認檔案在不在
	CFileFind Find;
	CFile file;
	//
	if(Find.FindFile( csFile ))
	{
		::DeleteFile( csFile );
	}
	//
	
	// 加入檔案產生時間
	CString cs;
	CString csTitleTime;
	csTitleTime.Format("Create Report Time: %s",  csFileNameTime );
	if(file.Open(csFile, CFile::modeCreate | CFile::modeWrite | CFile::shareDenyNone
		| CFile::modeNoTruncate, NULL) != 0)
	{
		cs.Format("%s\r\n", csTitleTime);
		file.SeekToEnd();
		file.Write(cs.GetBuffer(0), cs.GetLength());
		file.Close();
	}

	// 加入標題
	CString csTitle;
	csTitle.Format("Serial, Time, Code, Level, Desc" );

	if(file.Open(csFile, CFile::modeCreate | CFile::modeWrite | CFile::shareDenyNone
		| CFile::modeNoTruncate, NULL) != 0)
	{
		cs.Format("%s\r\n", csTitle);
		file.SeekToEnd();
		file.Write(cs.GetBuffer(0), cs.GetLength());
		file.Close();
	}

// 填入資料
	int iSerial = 0;
	CString csSerial;
	if(file.Open(csFile, CFile::modeCreate | CFile::modeWrite | CFile::shareDenyNone
		| CFile::modeNoTruncate, NULL) != 0)
	{
		CString csSerial;
		CString csRow;
		CString csCol;
		CString csResult;

		tagErrorParam err[_Max_Event];
		int iCount = f.m_Log.ReadEvent(err, 2);
		tagErrorMsg msg;

		// DATA
		// message
		CString lmessage;
		// time
		CTime lctime;
		CString ltime;
		// code
		long lccode;
		CString lcode;
		// level;
		long lclevel;
		CString llevel;
		//
		for(int i=0;i<iCount; i++ )
		{
			// serial
			iSerial++;
			csSerial.Format("%d", iSerial );
			
			// message.
			msg = f.GetErrorMsg(err[i].Code);
			if(m.UI.Language == m.enChinese)
			{
				if(msg.Code == -1)
					lmessage = "錯誤碼未定義";
				else
					lmessage = msg.Chi;
			}
			else				
			{
				if(msg.Code == -1)
					lmessage = "Undefine error code";
				else
					lmessage = msg.Eng;
			}
			
			// time.
			lctime = err[i].Time;
			ltime.Format("%s", lctime.Format("%m_%d_%H_%M_%S") );
			// code
			lccode = err[i].Code;
			lcode.Format("%d", lccode );
			// level
			lclevel = msg.Level - 1;
			llevel.Format("%d", lclevel+1);
			//

			// Single Report
			CString csDATA;
			csDATA.Format("%s, %s, %s, %s, %s\r\n", csSerial, ltime, lcode, llevel, lmessage );

			//
			// Write Report
			file.SeekToEnd();
			file.Write(csDATA.GetBuffer(0), csDATA.GetLength());

		}

		file.Close();
	}

	Lock.Unlock();
}

void CFunction::AutoCreateFolder(CString csFolder)
{
	CString csTemp = _T("");
	CFileFind find;
	BOOL bResult = find.FindFile(csFolder, 0);	
	BOOL bCreateResult = TRUE;
	if(!bResult)
	{
		bCreateResult = CreateDirectory(csFolder, NULL);		
	}
}

void CFunction::LoadBinColor()
{
	CString csFile = _T("");
	csFile = m.FilePath.BinColorPath;

	//
	m.BinColorItem.RemoveAll();

	//
	int iCount = 0;

	CFile file;
	if(file.Open(csFile, CFile::modeRead | CFile::shareDenyNone, NULL) != 0)
	{			
		file.SeekToBegin();
		CArchive ar(&file, CArchive::load);
		CString cs;
		
		while(1)
		{
			BOOL bReadOK = ar.ReadString(cs);

			if( !bReadOK )
				break;

			long lColor = 0;
			lColor		= atoi( cs );
			
			tagBinColor BinRecord;
			
			BinRecord.item	= iCount;
			BinRecord.color = lColor;

			//
			m.BinColorItem.Add( BinRecord );

			//
			iCount++;
		}
		ar.Close();
		file.Close();
	}

}
void CFunction::SaveBinColor()
{
	CString csFile = _T("");
	csFile = m.FilePath.BinColorPath;

	::DeleteFile( csFile );

	//
	int iCount = 0;

	CFile file;
	if(file.Open(csFile, CFile::modeCreate | CFile::modeWrite 
		| CFile::modeNoTruncate | CFile::shareDenyNone, NULL) != 0)
	{			
		int iSize = m.BinColorItem.GetSize();
		for(int i=0;i<iSize;i++)
		{			
			tagBinColor BinRecord;
			//
			BinRecord.color = m.BinColorItem.GetAt(i).color;
			BinRecord.item = i;

			//
			CString csColor = _T("");
			csColor.Format("%d\r\n", BinRecord.color );
			file.Write( csColor.GetBuffer(0), csColor.GetLength() );

		}

		file.Close();		
	}	
}

void CFunction::LoadATCMonitor()
{
	CString csFile = _T("");
	csFile = m.FilePath.ATCMonitorPath;

	GetSetting( csFile, "ATC Monitor", "SV",		m.m_ATCMonitor.sv = 25. );
}

void CFunction::SaveATCMonitor()
{
	CString csFile = _T("");
	csFile = m.FilePath.ATCMonitorPath;

	SaveSetting( csFile, "ATC Monitor", "SV",		m.m_ATCMonitor.sv );
}

void CFunction::LoadHandlerComPort()
{
	CString csFile = _T("");
	csFile = m.FilePath.HandlerComPortPath;

	//
	GetSetting( csFile, "Handler Comn Port",		"Remote Port",	m.m_HandlerComPort.iPortRemoteCom );

	//
	GetSetting( csFile, "Handler Comn Port",		"ATC Module",	m.m_HandlerComPort.iPortATCModule );
	GetSetting( csFile, "Handler Comn Port",		"Tester",		m.m_HandlerComPort.iPortTester );

	//
	GetSetting( csFile, "Handler Comn Port",		"PID Port",		m.m_HandlerComPort.iPortPIDValue );
	GetSetting( csFile, "Handler Comn Port",		"PID ID",		m.m_HandlerComPort.iIDPIDValue );

	//
	GetSetting( csFile, "Handler Comn Port",		"IO Port",		m.m_HandlerComPort.iPortIOModule );
	GetSetting( csFile, "Handler Comn Port",		"IO ID",		m.m_HandlerComPort.iIDIOModuleIDIn );
	GetSetting( csFile, "Handler Comn Port",		"IO ID Out",	m.m_HandlerComPort.iIDIOModuleIDOut );

	//
	GetSetting( csFile, "Handler Comn Port",		"West Port",	m.m_HandlerComPort.iPortWest );
	GetSetting( csFile, "Handler Comn Port",		"Heater ID",	m.m_HandlerComPort.iPortWestHeaterID );

	//
	GetSetting( csFile, "Handler Comn Port",		"Torque Port",	m.m_HandlerComPort.iPortTorqueStatus );
}
void CFunction::SaveHandlerComPort()
{
	CString csFile = _T("");
	csFile = m.FilePath.HandlerComPortPath;

	SaveSetting( csFile, "Handler Comn Port",		"Remote Port",	m.m_HandlerComPort.iPortRemoteCom );

	//
	SaveSetting( csFile, "Handler Comn Port",		"ATC Module",	m.m_HandlerComPort.iPortATCModule );
	SaveSetting( csFile, "Handler Comn Port",		"Tester",		m.m_HandlerComPort.iPortTester );

	//
	SaveSetting( csFile, "Handler Comn Port",		"PID Port",		m.m_HandlerComPort.iPortPIDValue );
	SaveSetting( csFile, "Handler Comn Port",		"PID ID",		m.m_HandlerComPort.iIDPIDValue );

	//
	SaveSetting( csFile, "Handler Comn Port",		"IO Port",		m.m_HandlerComPort.iPortIOModule );
	SaveSetting( csFile, "Handler Comn Port",		"IO ID",		m.m_HandlerComPort.iIDIOModuleIDIn );
	SaveSetting( csFile, "Handler Comn Port",		"IO ID Out",	m.m_HandlerComPort.iIDIOModuleIDOut );

	//
	SaveSetting( csFile, "Handler Comn Port",		"West Port",	m.m_HandlerComPort.iPortWest );
	SaveSetting( csFile, "Handler Comn Port",		"Heater ID",	m.m_HandlerComPort.iPortWestHeaterID );	

	//
	SaveSetting( csFile, "Handler Comn Port",		"Torque Port",	m.m_HandlerComPort.iPortTorqueStatus );
}
void CFunction::LoadUPHInfo()
{
	CString csFile = _T("");
	csFile = m.FilePath.UPHPath;

	GetSetting( csFile, "UPH",	"Tested",		m.UPH.ICTested );
	GetSetting( csFile, "UPH",	"Cycle Time",	m.UPH.CycleTime );
}
void CFunction::SaveUPHInfo()
{
	CString csFile = _T("");
	csFile = m.FilePath.UPHPath;

	SaveSetting( csFile, "UPH",	"Tested",		m.UPH.ICTested );
	SaveSetting( csFile, "UPH",	"Cycle Time",	m.UPH.CycleTime );
}
void CFunction::LoadATCModuleMultiSVSetting(CString csFileName, 
											double &dTemperatureRange, double &dChangeStable)
{
	CString csFile = _T("");
	csFile = m.FilePath.AtcModuleSettingPath + csFileName;
	double dTempRange = 0.0;
	double dChangeTime = 0.0;
	GetSetting(csFile, "ATCModule", "Temperature Range",			dTempRange );
	GetSetting(csFile, "ATCModule", "Change Stable Time",			dChangeTime );

	dTemperatureRange = dTempRange;
	dChangeStable = dChangeTime;
}
void CFunction::SaveATCModuleMultiSVSetting(CString csFileName, 
											double dTemperatureRange, double dChangeStable)
{
	CString csFile = _T("");
	csFile = m.FilePath.AtcModuleSettingPath + csFileName;
	SaveSetting(csFile, "ATCModule", "Temperature Range",			dTemperatureRange );
	SaveSetting(csFile, "ATCModule", "Change Stable Time",			dChangeStable );
}
void CFunction::LoadATCModuleMultiSVSetting()
{
}
void CFunction::LoadATCModuleMultiSVFile()
{
	CString csFile = _T("");
	csFile = m.FilePath.UIPath;
	GetSetting(csFile, "UI", "ATC Module MultiSV File",			m.UI.ATCModuleMultiSV );
}
void CFunction::SaveATCModuleMultiSVFile()
{	
	CString csFile = _T("");
	csFile = m.FilePath.UIPath;
	SaveSetting(csFile, "UI", "ATC Module MultiSV File",		m.UI.ATCModuleMultiSV );


}
void CFunction::LoadSocketPattern()
{
	CString csFile = _T("");
	csFile = m.FilePath.UIPath;
	GetSetting(csFile, "UI", "SOCKET PATTERN FILE",				m.UI.SocketPatternName );
//Jerome Add 20140709
	GetSetting(csFile, "UI", "PIN1 PATTERN FILE",				m.UI.Pin1PatternName );
}
//
void CFunction::LoadMCEnable()
{
	CString csFile = _T("");
	csFile = m.FilePath.ManualContactPath;	
				
	GetSetting(csFile, "Manual Contact Page", "Torque Contrl",		m.m_MCFunction.m_bEnableTorqueControl);
	GetSetting(csFile, "Manual Contact Page", "If Contrl",			m.m_MCFunction.m_bEnableInterfaceTesting);
	GetSetting(csFile, "Manual Contact Page", "Temp Contrl",		m.m_MCFunction.m_bEnableTemperatureControl);
	GetSetting(csFile, "Manual Contact Page", "Offset Contrl",		m.m_MCFunction.m_bEnableOffsetControl);
	GetSetting(csFile, "Manual Contact Page", "Ts DirectContact",	m.m_MCFunction.m_bEnableTestDirectContact);
	GetSetting(csFile, "Manual Contact Page", "Test Site Vacc",		m.m_MCFunction.m_bEnableTestSiteVacc);
}
void CFunction::SaveMCEnable()
{
	CString csFile = _T("");
	csFile = m.FilePath.ManualContactPath;	

	SaveSetting(csFile, "Manual Contact Page", "Torque Contrl",		m.m_MCFunction.m_bEnableTorqueControl);
	SaveSetting(csFile, "Manual Contact Page", "If Contrl",			m.m_MCFunction.m_bEnableInterfaceTesting);
	SaveSetting(csFile, "Manual Contact Page", "Temp Contrl",		m.m_MCFunction.m_bEnableTemperatureControl);
	SaveSetting(csFile, "Manual Contact Page", "Offset Contrl",		m.m_MCFunction.m_bEnableOffsetControl);
	SaveSetting(csFile, "Manual Contact Page", "Ts DirectContact",	m.m_MCFunction.m_bEnableTestDirectContact);
	SaveSetting(csFile, "Manual Contact Page", "Test Site Vacc",		m.m_MCFunction.m_bEnableTestSiteVacc);
}
void CFunction::LoadPageEnable()
{
	CString csFile = _T("");
	csFile = m.FilePath.PageEnablePath;					

	// Enable Page Function
	GetSetting(csFile, "Engineer Page", "EnableMotorMon",		m.m_EngineerPageEnable.m_bEnableMotorMon);
	GetSetting(csFile, "Engineer Page", "EnableIOMonitor",		m.m_EngineerPageEnable.m_bEnableIOMonitor);
	GetSetting(csFile, "Engineer Page", "EnableAlignment",		m.m_EngineerPageEnable.m_bEnableAlignment);
	GetSetting(csFile, "Engineer Page", "EnableEventLog",		m.m_EngineerPageEnable.m_bEnableEventLog);
	GetSetting(csFile, "Engineer Page", "EnableSocketCCD",		m.m_EngineerPageEnable.m_bEnableSocketCCD);
	GetSetting(csFile, "Engineer Page", "EnableSpeed",			m.m_EngineerPageEnable.m_bEnableSpeed);
	GetSetting(csFile, "Engineer Page", "EnableTSCounter",		m.m_EngineerPageEnable.m_bEnableTSCounter);
	GetSetting(csFile, "Engineer Page", "EnableChangeFile",		m.m_EngineerPageEnable.m_bEnableChangeFile);
	GetSetting(csFile, "Engineer Page", "EnableLoopTest",		m.m_EngineerPageEnable.m_bEnableLoopTest);
	GetSetting(csFile, "Engineer Page", "EnableAlarmMail",		m.m_EngineerPageEnable.m_bEnableAlarmMail);

	// Enable Page Function
	GetSetting(csFile, "User Page", "EnableSummaryReport",		m.m_UserPageEnable.m_bEnableSummaryReport);
	GetSetting(csFile, "User Page", "EnableManualContact",		m.m_UserPageEnable.m_bEnableManualContact);
	GetSetting(csFile, "User Page", "EnableDeviceSetup",		m.m_UserPageEnable.m_bEnableDeviceSetup);
	GetSetting(csFile, "User Page", "EnableSiteSetting",		m.m_UserPageEnable.m_bEnableSiteSetting);
	GetSetting(csFile, "User Page", "EnableVisualPanel",		m.m_UserPageEnable.m_bEnableVisualPanel);
	GetSetting(csFile, "User Page", "EnableLotInformation",		m.m_UserPageEnable.m_bEnableLotInformation);
	GetSetting(csFile, "User Page", "EnableAutoSkip",			m.m_UserPageEnable.m_bEnableAutoSkip);
	GetSetting(csFile, "User Page", "EnableYieldCtrl",			m.m_UserPageEnable.m_bEnableYieldCtrl);
	GetSetting(csFile, "User Page", "EnableIfTesting",			m.m_UserPageEnable.m_bEnableIfTesting);
	GetSetting(csFile, "User Page", "EnableTrayMapReport",		m.m_UserPageEnable.m_bEnableTrayMapReport);
	GetSetting(csFile, "User Page", "EnableTestSiteVacc",		m.m_UserPageEnable.m_bTestSiteVaccOn);
	GetSetting(csFile, "User Page", "EnableTestResult",			m.m_UserPageEnable.m_bTestResultReport);
	GetSetting(csFile, "User Page", "EnableRepeatTrayStatus",	m.m_UserPageEnable.m_bRepeatTrayStatus);
	GetSetting(csFile, "User Page", "EnableTrayDefColor",		m.m_UserPageEnable.m_bTrayDefColor);
	GetSetting(csFile, "User Page", "EnableArmLogICImage",		m.m_UserPageEnable.m_bArmLogICImage);
	GetSetting(csFile, "User Page", "EnableSLTProtocol",		m.m_UserPageEnable.m_bSLTProtocol);

	// Enable Page Function
	GetSetting(csFile, "Setup Page", "EnableOffset",			m.m_SetupPageEnable.m_bEnableOffset);
	GetSetting(csFile, "Setup Page", "EnableSpeed",				m.m_SetupPageEnable.m_bEnableSpeed);
	GetSetting(csFile, "Setup Page", "EnableTimer",				m.m_SetupPageEnable.m_bEnableTimer);
	GetSetting(csFile, "Setup Page", "EnableEventLog",			m.m_SetupPageEnable.m_bEnableEventLog);
	GetSetting(csFile, "Setup Page", "EnableSiteSetting",		m.m_SetupPageEnable.m_bEnableSiteSetting);
	GetSetting(csFile, "Setup Page", "EnableYieldCtrl",			m.m_SetupPageEnable.m_bEnableYieldCtrl);
	GetSetting(csFile, "Setup Page", "EnableAutoRetry",			m.m_SetupPageEnable.m_bEnableAutoRetry);
	GetSetting(csFile, "Setup Page", "EnableDeviceSetup",		m.m_SetupPageEnable.m_bEnableDeviceSetup);
	GetSetting(csFile, "Setup Page", "EnableTrayFile",			m.m_SetupPageEnable.m_bEnableTrayFile	);
	GetSetting(csFile, "Setup Page", "EnableIfTesting",			m.m_SetupPageEnable.m_bEnableIfTesting);
	GetSetting(csFile, "Setup Page", "EnableCatoregy",			m.m_SetupPageEnable.m_bEnableCatoregy);
	GetSetting(csFile, "Setup Page", "EnableInterface",			m.m_SetupPageEnable.m_bEnableInterface);
	GetSetting(csFile, "Setup Page", "EnableRemoteControl",		m.m_SetupPageEnable.m_bEnableRemoteControl);
	GetSetting(csFile, "Setup Page", "EnableRemoteInput",		m.m_SetupPageEnable.m_bEnableRemoteInput);
	GetSetting(csFile, "Setup Page", "EnableInputTray",			m.m_SetupPageEnable.m_bEnableInputTray);
	GetSetting(csFile, "Setup Page", "EnableOutputTray",		m.m_SetupPageEnable.m_bEnableOutputTray);
	GetSetting(csFile, "Setup Page", "EnableIOMonitor",			m.m_SetupPageEnable.m_bEnableIOMonitor);
	GetSetting(csFile, "Setup Page", "EnableAlignment",			m.m_SetupPageEnable.m_bEnableAlignment);
	GetSetting(csFile, "Setup Page", "EnableInOutTray",			m.m_SetupPageEnable.m_bEnableInOutTray);
	GetSetting(csFile, "Setup Page", "EnableRepeatTray",		m.m_SetupPageEnable.m_bEnableRepeatTray);
	GetSetting(csFile, "Setup Page", "TowerSetting",			m.m_SetupPageEnable.m_bEnableTowerSetting);
}
void CFunction::SavePageEnable()
{
	CString csFile = _T("");
	csFile = m.FilePath.PageEnablePath;

	// Enable Page Function
	SaveSetting(csFile, "Engineer Page", "EnableMotorMon",		m.m_EngineerPageEnable.m_bEnableMotorMon);
	SaveSetting(csFile, "Engineer Page", "EnableIOMonitor",		m.m_EngineerPageEnable.m_bEnableIOMonitor);
	SaveSetting(csFile, "Engineer Page", "EnableAlignment",		m.m_EngineerPageEnable.m_bEnableAlignment);
	SaveSetting(csFile, "Engineer Page", "EnableEventLog",		m.m_EngineerPageEnable.m_bEnableEventLog);
	SaveSetting(csFile, "Engineer Page", "EnableSocketCCD",		m.m_EngineerPageEnable.m_bEnableSocketCCD);
	SaveSetting(csFile, "Engineer Page", "EnableSpeed",			m.m_EngineerPageEnable.m_bEnableSpeed);
	SaveSetting(csFile, "Engineer Page", "EnableTSCounter",		m.m_EngineerPageEnable.m_bEnableTSCounter);
	SaveSetting(csFile, "Engineer Page", "EnableChangeFile",	m.m_EngineerPageEnable.m_bEnableChangeFile);
	SaveSetting(csFile, "Engineer Page", "EnableLoopTest",		m.m_EngineerPageEnable.m_bEnableLoopTest);
	SaveSetting(csFile, "Engineer Page", "EnableAlarmMail",		m.m_EngineerPageEnable.m_bEnableAlarmMail);
	
	// Enable Page Function
	SaveSetting(csFile, "User Page", "EnableSummaryReport",		m.m_UserPageEnable.m_bEnableSummaryReport);
	SaveSetting(csFile, "User Page", "EnableManualContact",		m.m_UserPageEnable.m_bEnableManualContact);
	SaveSetting(csFile, "User Page", "EnableDeviceSetup",		m.m_UserPageEnable.m_bEnableDeviceSetup);
	SaveSetting(csFile, "User Page", "EnableSiteSetting",		m.m_UserPageEnable.m_bEnableSiteSetting);
	SaveSetting(csFile, "User Page", "EnableVisualPanel",		m.m_UserPageEnable.m_bEnableVisualPanel);
	SaveSetting(csFile, "User Page", "EnableLotInformation",	m.m_UserPageEnable.m_bEnableLotInformation);
	SaveSetting(csFile, "User Page", "EnableAutoSkip",			m.m_UserPageEnable.m_bEnableAutoSkip);
	SaveSetting(csFile, "User Page", "EnableYieldCtrl",			m.m_UserPageEnable.m_bEnableYieldCtrl);
	SaveSetting(csFile, "User Page", "EnableIfTesting",			m.m_UserPageEnable.m_bEnableIfTesting);
	SaveSetting(csFile, "User Page", "EnableTrayMapReport",		m.m_UserPageEnable.m_bEnableTrayMapReport);
	SaveSetting(csFile, "User Page", "EnableTestSiteVacc",		m.m_UserPageEnable.m_bTestSiteVaccOn);
	SaveSetting(csFile, "User Page", "EnableTestResult",		m.m_UserPageEnable.m_bTestResultReport);
	SaveSetting(csFile, "User Page", "EnableRepeatTrayStatus",	m.m_UserPageEnable.m_bRepeatTrayStatus);
	SaveSetting(csFile, "User Page", "EnableTrayDefColor",		m.m_UserPageEnable.m_bTrayDefColor);
	SaveSetting(csFile, "User Page", "EnableArmLogICImage",		m.m_UserPageEnable.m_bArmLogICImage);
	SaveSetting(csFile, "User Page", "EnableSLTProtocol",		m.m_UserPageEnable.m_bSLTProtocol);

	// Enable Page Function
	SaveSetting(csFile, "Setup Page", "EnableOffset",			m.m_SetupPageEnable.m_bEnableOffset);
	SaveSetting(csFile, "Setup Page", "EnableSpeed",			m.m_SetupPageEnable.m_bEnableSpeed);
	SaveSetting(csFile, "Setup Page", "EnableTimer",			m.m_SetupPageEnable.m_bEnableTimer);
	SaveSetting(csFile, "Setup Page", "EnableEventLog",			m.m_SetupPageEnable.m_bEnableEventLog);
	SaveSetting(csFile, "Setup Page", "EnableSiteSetting",		m.m_SetupPageEnable.m_bEnableSiteSetting);
	SaveSetting(csFile, "Setup Page", "EnableYieldCtrl",		m.m_SetupPageEnable.m_bEnableYieldCtrl);
	SaveSetting(csFile, "Setup Page", "EnableAutoRetry",		m.m_SetupPageEnable.m_bEnableAutoRetry);
	SaveSetting(csFile, "Setup Page", "EnableDeviceSetup",		m.m_SetupPageEnable.m_bEnableDeviceSetup);
	SaveSetting(csFile, "Setup Page", "EnableTrayFile",			m.m_SetupPageEnable.m_bEnableTrayFile	);
	SaveSetting(csFile, "Setup Page", "EnableIfTesting",		m.m_SetupPageEnable.m_bEnableIfTesting);
	SaveSetting(csFile, "Setup Page", "EnableCatoregy",			m.m_SetupPageEnable.m_bEnableCatoregy);
	SaveSetting(csFile, "Setup Page", "EnableInterface",		m.m_SetupPageEnable.m_bEnableInterface);
	SaveSetting(csFile, "Setup Page", "EnableRemoteControl",	m.m_SetupPageEnable.m_bEnableRemoteControl);
	SaveSetting(csFile, "Setup Page", "EnableRemoteInput",		m.m_SetupPageEnable.m_bEnableRemoteInput);
	SaveSetting(csFile, "Setup Page", "EnableInputTray",		m.m_SetupPageEnable.m_bEnableInputTray);
	SaveSetting(csFile, "Setup Page", "EnableOutputTray",		m.m_SetupPageEnable.m_bEnableOutputTray);
	SaveSetting(csFile, "Setup Page", "EnableIOMonitor",		m.m_SetupPageEnable.m_bEnableIOMonitor);
	SaveSetting(csFile, "Setup Page", "EnableAlignment",		m.m_SetupPageEnable.m_bEnableAlignment);
	SaveSetting(csFile, "Setup Page", "EnableInOutTray",		m.m_SetupPageEnable.m_bEnableInOutTray);
	SaveSetting(csFile, "Setup Page", "EnableRepeatTray",		m.m_SetupPageEnable.m_bEnableRepeatTray);
	SaveSetting(csFile, "Setup Page", "TowerSetting",			m.m_SetupPageEnable.m_bEnableTowerSetting);
}	
void CFunction::SaveSocketPattern()
{
	CString csFile = _T("");
	csFile = m.FilePath.UIPath;
	SaveSetting(csFile, "UI", "SOCKET PATTERN FILE",			m.UI.SocketPatternName );
//Jerome add 20140709
	SaveSetting(csFile, "UI", "PIN1 PATTERN FILE",			m.UI.Pin1PatternName );

}
void CFunction::LoadContactForce()
{
	CString csFile = _T("");
	csFile = m.FilePath.TorqueCtrlPath;
	GetSetting( csFile, "Contact Force",	"Power", m.m_ContactForce.lPower );

	// 如果沒有選 TrayFile 還是要設定一個預設值
	if( m.UI.FileMain == "")
		theApp.m_tIORemote.SetTorqueValue( m.m_ContactForce.lPower );
}
void CFunction::SaveContactForce()
{
	CString csFile = _T("");
	csFile = m.FilePath.TorqueCtrlPath;

	SaveSetting( csFile, "Contact Force",	"Power", m.m_ContactForce.lPower );
}

void CFunction::LoadInterfaceEnable()
{
	CString csFile = _T("");
	csFile = m.FilePath.UIPath;

	GetSetting( csFile, "Interface Enable",	"Tcp",		m.m_InterfaceEnable.m_bEnableTcp );
	GetSetting( csFile, "Interface Enable",	"Rs232",	m.m_InterfaceEnable.m_bEnableRs232 );
	GetSetting( csFile, "Interface Enable",	"Gpib",		m.m_InterfaceEnable.m_bEnableGpib);
	GetSetting( csFile, "Interface Enable",	"TTL",		m.m_InterfaceEnable.m_bEnableTTL);

}
void CFunction::SaveInterfaceEnable()
{
	CString csFile = _T("");
	csFile = m.FilePath.UIPath;

	SaveSetting( csFile, "Interface Enable",	"Tcp",		m.m_InterfaceEnable.m_bEnableTcp );
	SaveSetting( csFile, "Interface Enable",	"Rs232",	m.m_InterfaceEnable.m_bEnableRs232 );
	SaveSetting( csFile, "Interface Enable",	"Gpib",		m.m_InterfaceEnable.m_bEnableGpib );
	SaveSetting( csFile, "Interface Enable",	"TTL",		m.m_InterfaceEnable.m_bEnableTTL);
}
void CFunction::LoadOutputColor()
{
	CString csFile = _T("");
	csFile = m.FilePath.UIPath;

	GetSetting( csFile, "Run Page Color",	"R",		m.m_RunPageOutputColor.R = 0 );
	GetSetting( csFile, "Run Page Color",	"G",		m.m_RunPageOutputColor.G = 255 );
	GetSetting( csFile, "Run Page Color",	"B",		m.m_RunPageOutputColor.B = 0 );
}
void CFunction::SaveOutputColor()
{
	CString csFile = _T("");
	csFile = m.FilePath.UIPath;

	SaveSetting( csFile, "Run Page Color",	"R",		m.m_RunPageOutputColor.R );
	SaveSetting( csFile, "Run Page Color",	"G",		m.m_RunPageOutputColor.G );
	SaveSetting( csFile, "Run Page Color",	"B",		m.m_RunPageOutputColor.B  );
}
COLORREF CFunction::GetCategoryColor(CString result)
{
	COLORREF ColorRef = ST_GRAY;	// If Can not find code vlaue...default is gray....

	result.TrimLeft(); 
	result.TrimRight();

	bool ok = false;
	int Size = m.BinMap.GetSize();
	for(int i=0; i<Size; i++)
	{
		if(m.BinMap.ElementAt(i).code == result)
		{
			ColorRef = m.BinMap.ElementAt(i).color;
			ok = true;
			break;
		}
	}

	return ColorRef;
}
void CFunction::LoadCCDPin1Control()
{
	CString csFile;
	csFile = m.FilePath.CCDCameraPath;

	GetSetting( csFile, "CCD Control", "Use ID",		m.m_CCDPin1Control.iCCDUse = 0 );		// 
	GetSetting( csFile, "CCD Control", "Def ROI X",		m.m_CCDPin1Control.RoiX = 160 );
	GetSetting( csFile, "CCD Control", "Def ROI Y",		m.m_CCDPin1Control.RoiY = 120 );
	GetSetting( csFile, "CCD Control", "Def ROI W",		m.m_CCDPin1Control.RoiW = 320 );
	GetSetting( csFile, "CCD Control", "Def ROI H",		m.m_CCDPin1Control.RoiH = 240 );
}
void CFunction::SaveCCDPin1Control()
{
	CString csFile;
	csFile = m.FilePath.CCDCameraPath;	
	
	SaveSetting( csFile, "CCD Control", "Use ID",		 m.m_CCDPin1Control.iCCDUse );		// 
	SaveSetting( csFile, "CCD Control", "Def ROI X",	 m.m_CCDPin1Control.RoiX );
	SaveSetting( csFile, "CCD Control", "Def ROI Y",	 m.m_CCDPin1Control.RoiY );
	SaveSetting( csFile, "CCD Control", "Def ROI W",	 m.m_CCDPin1Control.RoiW );
	SaveSetting( csFile, "CCD Control", "Def ROI H",	 m.m_CCDPin1Control.RoiH );
}
void CFunction::LoadCCDSocketControl()
{
	CString csFile;
	csFile = m.FilePath.CCDCameraPath;

	GetSetting( csFile, "CCD Control Socket", "Use ID",			m.m_CCDSocketControl.iCCDUse = 1 );		// 
	GetSetting( csFile, "CCD Control Socket", "Def ROI X",		m.m_CCDSocketControl.RoiX = 160 );
	GetSetting( csFile, "CCD Control Socket", "Def ROI Y",		m.m_CCDSocketControl.RoiY = 120 );
	GetSetting( csFile, "CCD Control Socket", "Def ROI W",		m.m_CCDSocketControl.RoiW = 320 );
	GetSetting( csFile, "CCD Control Socket", "Def ROI H",		m.m_CCDSocketControl.RoiH = 240 );
}
void CFunction::SaveCCDSocketControl()
{
	CString csFile;
	csFile = m.FilePath.CCDCameraPath;

	SaveSetting( csFile, "CCD Control Socket", "Use ID",		m.m_CCDSocketControl.iCCDUse );		// 
	SaveSetting( csFile, "CCD Control Socket", "Def ROI X",		m.m_CCDSocketControl.RoiX );
	SaveSetting( csFile, "CCD Control Socket", "Def ROI Y",		m.m_CCDSocketControl.RoiY );
	SaveSetting( csFile, "CCD Control Socket", "Def ROI W",		m.m_CCDSocketControl.RoiW );
	SaveSetting( csFile, "CCD Control Socket", "Def ROI H",		m.m_CCDSocketControl.RoiH );
}
void CFunction::LotDoneClearOutputYieldCounter()
{
	m.m_OutputYieldCounter.RemoveAll();
}
void CFunction::InitOutputYieldCount()
{
	m.m_OutputYieldCounter.RemoveAll();
}
void CFunction::LoadOutputYield()
{
	//
	m.m_OutputYieldCounter.RemoveAll();

	//
	int iSize = 0;
	iSize = m.BinMap.GetSize();
	for(int i=0;i<iSize;i++)
	{
		tagOutputYield m_data;
		m_data.m_csCode			= m.BinMap.GetAt(i).code;
		m_data.m_lCodeCounter	= 0;
		m.m_OutputYieldCounter.Add( m_data );	
	}

	// Timeout
	tagOutputYield m_data;
	m_data.m_csCode = _BinDescTimeout;
	m_data.m_lCodeCounter = 0;
	m.m_OutputYieldCounter.Add(m_data);

	// Other
	m_data.m_csCode = _BinDescOther;
	m_data.m_lCodeCounter = 0;
	m.m_OutputYieldCounter.Add(m_data);
}
///////////////////////////////////////////////////////////
// Torque Function
void CFunction::InitTorqueCtrl()
{	
	if( m.Setting.m_bEnableTorqueCtrl == 1 )
	{
		if( m.m_Torque.OpenFlowControl( m.m_HandlerComPort.iIDPIDValue, 9600 ) )
		{
			// Open Succress
			CString csMsg = _T("");
			csMsg.Format("Torque(PID) Control Open Success");
			f.DMsg.DMsg( csMsg );
		}
		else
		{
			// Open Fail
			CString csMsg = _T("");
			csMsg.Format("Torque Control Open Fail");
			f.DMsg.DMsg( csMsg + _DMsgMark, false );
#ifdef _Demo
#else
			if( m.Setting.m_bEnableProgramInitialStart == 1 )
			{
			}
			else
				AfxMessageBox( csMsg );
#endif
		}
	}	
}
///////////////////////////////////////////////////////////
// Torque Status Function
void CFunction::InitTorqueStatus()
{
	if( m.Setting.m_bEnableTorqueStatus == 1 )
	{
		bool bOpenOK = false;
		bOpenOK = m.m_DriveMotorTorque.Open( m.m_HandlerComPort.iPortTorqueStatus );

		if( bOpenOK )
		{
			// Open Success
			CString csMsg = _T("");
			csMsg.Format("Init TorqueStatus Success");
			f.DMsg.DMsg( csMsg  );
		}
		else
		{
			// Open Fail
			CString csMsg = _T("");
			csMsg.Format("Open Read Really Torque Status Fail.!");
			f.DMsg.DMsg( csMsg + _DMsgMark, false );
#ifdef _Demo
#else
			if( m.Setting.m_bEnableProgramInitialStart == 1 )
			{
			}
			else
				AfxMessageBox( csMsg );
#endif
		}
	}
}
void CFunction::InitPorgramStartInitial()
{
	
	CString csFile = _T("");
	csFile = m.FilePath.SystemSettingPath;
	GetSetting(csFile, "Setting", "Program Start Initial",						m.Setting.m_bEnableProgramInitialStart );
	
#ifdef _Demo
	m.Setting.m_bEnableProgramInitialStart = 0;
#endif
	//
	if( m.Setting.m_bEnableProgramInitialStart == 1 )
	{
		theApp.m_DlgProgramStartInitial = new CDlgProgramStart();
		theApp.m_DlgProgramStartInitial->Create((UINT)IDD_PROGRAM_START, NULL);
		 
		theApp.m_DlgProgramStartInitial->ShowWindow(SW_SHOW);

		//
		f.DMsg.DMsgClear();
	}
}
bool CFunction::InitDMsg()
{
	// 建立相關目錄
	AutoCreateFolder( m.FilePath.DMsgReportPath );
	return true;
}
///////////////////////////////////////////////////////////
// West Function
void CFunction::InitWest()
{
	if( !m.m_DriveWest.Open( m.m_HandlerComPort.iPortWest ) )
	{
		CString csMsg = _T("");
		csMsg.Format("Open West Com Port Fail");
		f.DMsg.DMsg( csMsg + _DMsgMark, false );
#ifdef _Demo
#else
		// Open Fail
		if( m.Setting.m_bEnableProgramInitialStart == 1 )
		{
					
		}
		else
			AfxMessageBox( csMsg );
#endif
	}
	else
	{
		// Open OK
		CString csMsg = _T("");
		csMsg.Format("West Open Success");
		f.DMsg.DMsg( csMsg  );	
	}

	//
	m.m_WestControllerList.m_List.RemoveAll();
	tagWestControllerList m_Data;

	// TS
	m_Data.csFunctionName = "Test Site";
	m_Data.m_lID		  = 0;
	m.m_WestControllerList.m_List.Add( m_Data );
}
///////////////////////////////////////////////////////////
// Mail Function
void CFunction::InitMail()
{
	m.m_MailCtrl.SetMailSetting( m.m_MailSetting );
	m.m_MailCtrl.InitMail();

	//
	CString csMsg = _T("");
	csMsg.Format("Alarm Mail Open Success");
	f.DMsg.DMsg( csMsg  );
}
void CFunction::SendAlarmMail(int iCode, CString csDesc)
{
	if( m.Setting.m_bCustomAlarmMail )
	{
		CString csCode = _T("");
		CString csTime = _T("");
	
		//
		csCode.Format("%d", iCode );

		//
		SYSTEMTIME ti; 
		GetLocalTime(&ti);
		csTime.Format("%d/%d - %d:%d:%5.3f", 
			ti.wMonth, ti.wDay, ti.wHour, ti.wMinute, ti.wSecond + ( ti.wMilliseconds / 1000. ) );

		//
		m.m_MailCtrl.AddCmd(csTime, csCode, csDesc );	
	}
}
///////////////////////////////////////////////////////////
// CCD Function
// void CFunction::InitCCD()
// {	
// 	// Create Backup Folder
// 	f.AutoCreateFolder( m.FilePath.CCDImageBackPath );
// 
// 	// Init CCD Device
// 	bool bInitCCDOK			= true;	
// 	bool bInitSocketCCDOK	= true;
// 	bool bInitPin1CCDOK		= true;
// 	if( m.Setting.m_bEnableCCDPin1 == 1 || m.Setting.m_bEnableCCDSocket == 1 || m.Setting.m_bEnableCCDLogICImage == 1 )
// 	{
// 		int iCCDCount = 0;
// 		iCCDCount = m.m_Vision.UpdateCameraList();
// 
// 		if( iCCDCount > 0 )
// 		{
// 			// CCD Pin1 
// 			if( m.Setting.m_bEnableCCDPin1 == 1 || m.Setting.m_bEnableCCDLogICImage == 1 )
// 			{
// 				if( m.m_Vision.Open( m.m_CCDPin1Control.iCCDUse ) )
// 				{
// 					// Open OK
// 					CString csMsg = _T("");
// 					csMsg.Format("CCD Pin1 Open Success");
// 					f.DMsg.DMsg( csMsg );					
// 				}		
// 				else
// 				{
// 					// Open Fail
// 					CString csMsg = _T("");
// 					csMsg.Format("Open Pin1 CCD Fail.");
// 					f.DMsg.DMsg( csMsg + _DMsgMark, false );
// 					bInitPin1CCDOK = false;
// #ifdef _Demo
// #else				
// 					if( m.Setting.m_bEnableProgramInitialStart == 1 )
// 					{
// 					}
// 					else
// 						AfxMessageBox( csMsg );
// #endif
// 				}//ccd pin1 open fail
// 			}
// 
// 			// CCD Socket
// 			if( m.Setting.m_bEnableCCDSocket == 1 )
// 			{
// 				if( m.m_Vision.Open( m.m_CCDSocketControl.iCCDUse ) )
// 				{
// 					// Open OK
// 					CString csMsg = _T("");
// 					csMsg.Format("CCD Socket Open Success");
// 					f.DMsg.DMsg( csMsg );					
// 				}		
// 				else
// 				{
// 					// Open Fail
// 					CString csMsg = _T("");
// 					csMsg.Format("Open Socket CCD Fail.");
// 					bInitSocketCCDOK = false;
// 					f.DMsg.DMsg( csMsg + _DMsgMark, false );
// #ifdef _Demo
// #else
// 					if( m.Setting.m_bEnableProgramInitialStart == 1 )
// 					{
// 					
// 					}
// 					else
// 						AfxMessageBox( csMsg );
// #endif
// 				}// ccd socket open fail
// 			}
// 		}
// 		else
// 		{
// 			// 找不到任何一支 CCD
// 			CString csMsg = _T("");
// 			csMsg.Format("Can not find any CCD, Please re-install CCD and re-open 3111 S/W.!.");
// 			bInitCCDOK = false;
// 			f.DMsg.DMsg( csMsg + _DMsgMark, false );
// #ifdef _Demo
// #else
// 			if( m.Setting.m_bEnableProgramInitialStart == 1 )
// 			{
// 				
// 			}
// 			else
// 				AfxMessageBox( csMsg );
// #endif
// 		}// no ccd
// 	}
// 	else
// 	{
// 		// No Enable CCD Function
// 	}
// }
bool CFunction::ManualVacc(unsigned char* Vacc, unsigned char* pSensor, double dTimeout )
{
	// Note : This function for Pick IC.
	// 1: Turn on the Vacc
	// 2: Wait for Vacc sensor On
	// 3: check Timeout.
	// 4: Pick success. Move to next ststus.
	// 5: check sensor again when Arm Z up.

	int	iStart;

	*Vacc = 1;		// Turn on vacuum.
	iStart = ::GetTickCount();
	while (1)
	{
		if ( (::GetTickCount() - iStart ) >= dTimeout * 1000 )
		{
			// Error - stop vacuum.
			*Vacc = 0;	
			return false;
		}

		// Check the vacuum sensor.
		if (*pSensor == _ArmZVaccOn)
		{
			// Do a debounce on the sensor.
			Sleep(10);
			if (*pSensor == _ArmZVaccOn)
				break;
			// check 2 times.
		}

		if(!m.Info.bRunning)
			return false;

		Sleep(_Wait);
	}

	// Check it one more time.
	if (*pSensor == _ArmZVaccOn)
		return true;

	// Something wrong - turn it off.
	*Vacc = 0;
	return false;
}
bool CFunction::ManualBlow(unsigned char* Vacc, unsigned char* Puff, unsigned char* pSensor, double dTimeout )
{
	// Note : This function for Puff IC.
	// 1: Turn on the Puff
	// 2: wait for Puff sensor On
	// 3: check Timeout 
	// 4: Place success. Move to next status.
	// 5: check sensor again when Arm Z up

	int iStart = ::GetTickCount();

	*Vacc = 0;	// Vacuum off
	*Puff = 1;		// Puff on

	while (1)
	{
		if ( (::GetTickCount() - iStart) >= (dTimeout * 1000.) )
			break;

		if(!m.Info.bRunning)
			return false;
		
		Sleep(_Wait);
	}

	if(*pSensor)
	{
		*Puff = 0;
		return false;
	}
	// Before return this function. 
	// We check Arm Z have IC or Not.
	// If there have IC, Puff fail

    // Turn puff off.    
    *Puff = 0;
	return true;
}
bool CFunction::Vacc(unsigned char* Vacc, unsigned char* pSensor, double dTimeout )
{
	// Note : This function for Pick IC.
	// 1: Turn on the Vacc
	// 2: Wait for Vacc sensor On
	// 3: check Timeout.
	// 4: Pick success. Move to next ststus.
	// 5: check sensor again when Arm Z up.

	int	iStart;

	*Vacc = 1;		// Turn on vacuum.
	iStart = ::GetTickCount();
	while (1)
	{
		if ( (::GetTickCount() - iStart ) >= dTimeout * 1000 )
		{
			// Error - stop vacuum.
			*Vacc = 0;	
			return false;
		}

		// Check the vacuum sensor.
		if (*pSensor == _TSVacOn)
		{
			// Do a debounce on the sensor.
			Sleep(10);
			if (*pSensor == _TSVacOn)
				break;
			// check 2 times.
		}

		if(f.IsPause())
			return false;
		// if System Pause. Do not turn off

		if(!m.Info.bRunning)
			return false;

		Sleep(_Wait);
	}

	// Check it one more time.
	if (*pSensor == _TSVacOn)
		return true;

	// Something wrong - turn it off.
	*Vacc = 0;

	return false;
}
bool CFunction::Blow(unsigned char* Vacc, unsigned char* Puff, unsigned char* pSensor, double dTimeout )
{
	// Note : This function for Puff IC.
	// 1: Turn on the Puff
	// 2: wait for Puff sensor On
	// 3: check Timeout 
	// 4: Place success. Move to next status.
	// 5: check sensor again when Arm Z up

	int iStart = ::GetTickCount();

	*Vacc = 0;	// Vacuum off
	*Puff = 1;		// Puff on

	while (1)
	{
		if ( (::GetTickCount() - iStart) >= (dTimeout * 1000.) )
			break;

		if(f.IsPause())
		{
			 *Puff = 0;
			 return true;
		}

		if(!m.Info.bRunning)
			return false;
		
		Sleep(_Wait);
	}

	if(*pSensor)
	{
		*Puff = 0;
		return false;
	}
	// Before return this function. 
	// We check Arm Z have IC or Not.
	// If there have IC, Puff fail

    // Turn puff off.    
    *Puff = 0;
	return true;
}
bool CFunction::ShuttleMovePickPlace()		// Shuttle move to testSite pick / place position
{
	bool bMovePick = false;
#ifdef _Demo
	bMovePick = true;
#else

	m.OutSet.Shuttle = true;
	int iStart = ::GetTickCount();
	while(1)
	{
		if( m.InStatus.ShuttleNLmt == _ShuttleNLmtOff && m.InStatus.ShuttlePLmt == _ShuttlePLmtOn )
		{
			bMovePick = true;
			break;
		}
		else if(f.IsPause())
		{
			bMovePick = false;
			break;
		}
		else if(!m.Info.bRunning)
		{
			bMovePick = false;
			break;
		}
		else if( (::GetTickCount() - iStart ) > m.TimerSetting.iShuttlePickTimeout )
		{
			bMovePick = false;
			break;
		}
		else
			; // Wait here.	
	}
#endif
	return bMovePick;
}
bool CFunction::CheckTSZVaccSensor()
{
	bool bVacc = false;
#ifdef _Demo
	bVacc = true;
#else
	if( m.InStatus.TestSiteZVaccSensor == _TSVacOn )
		bVacc = true;
	else
		bVacc = false;
#endif

	return bVacc;
}
bool CFunction::ShuttleMoveHome()		// Shuttle move to arm pick / place position
{
	bool bMoveHome = false;
#ifdef _Demo
	bMoveHome = true;
#else

	m.OutSet.Shuttle = false;
	int iStart = ::GetTickCount();
	while(1)
	{
		if( m.InStatus.ShuttleNLmt == _ShuttleNLmtOn && m.InStatus.ShuttlePLmt == _ShuttlePLmtOff )
		{
			bMoveHome = true;
			break;
		}
		else if(f.IsPause())
		{
			bMoveHome = false;
			break;
		}
		else if(!m.Info.bRunning)
		{
			bMoveHome = false;
			break;
		}
		else if( (::GetTickCount() - iStart ) > m.TimerSetting.iShuttleHomeTimeout )
		{
			bMoveHome = false;
			break;
		}
		else
			; // Wait here.
	}
#endif
	return bMoveHome;
}
bool CFunction::CheckShuttleJam()	
{
	bool bJam = false;
#ifdef _Demo
#else
	if( m.InStatus.ShuttleInputJam == _ShuttleJamOn )
		bJam = true;
	else 
		bJam = false;
#endif
	return bJam;
}
bool CFunction::CheckShuttlePickPlaceOK()	// Check shuttle move to pick / place position ok
{
	bool bMovePickOK = false;
#ifdef _Demo
	bMovePickOK = true;
#else	
	if( m.InStatus.ShuttleNLmt == _ShuttleNLmtOff && m.InStatus.ShuttlePLmt == _ShuttlePLmtOn )
		bMovePickOK = true;
	else
		bMovePickOK	= false;
#endif
	return bMovePickOK;
}
bool CFunction::CheckShuttleHomeOK()	// Check shuttle move to home / pick / place position ok
{
	bool bMoveHomeOK = false;
#ifdef _Demo
	bMoveHomeOK = true;
#else
	if( m.InStatus.ShuttleNLmt == _ShuttleNLmtOn && m.InStatus.ShuttlePLmt == _ShuttlePLmtOff )
		bMoveHomeOK = true;
	else
		bMoveHomeOK	= false;
#endif
	return bMoveHomeOK;
}
//
bool CFunction::ManualShuttleMovePickPlace()		// Shuttle move to testSite pick / place position
{
	bool bMovePick = false;
#ifdef _Demo
	bMovePick = true;
#else

	m.OutSet.Shuttle = true;
	int iStart = ::GetTickCount();
	while(1)
	{
		if( m.InStatus.ShuttleNLmt == _ShuttleNLmtOff && m.InStatus.ShuttlePLmt == _ShuttlePLmtOn )
		{
			bMovePick = true;
			break;
		}
		else if(!m.Info.bRunning)
		{
			bMovePick = false;
			break;
		}
		else if( (::GetTickCount() - iStart ) > m.TimerSetting.iShuttlePickTimeout )
		{
			bMovePick = false;
			break;
		}
		else
			; // Wait here.	
	}
#endif
	return bMovePick;
}
bool CFunction::ManualShuttleMoveHome()		// Shuttle move to arm pick / place position
{
	bool bMoveHome = false;
#ifdef _Demo
	bMoveHome = true;
#else

	m.OutSet.Shuttle = false;
	int iStart = ::GetTickCount();
	while(1)
	{
		if( m.InStatus.ShuttleNLmt == _ShuttleNLmtOn && m.InStatus.ShuttlePLmt == _ShuttlePLmtOff )
		{
			bMoveHome = true;
			break;
		}
		else if(!m.Info.bRunning)
		{
			bMoveHome = false;
			break;
		}
		else if( (::GetTickCount() - iStart ) > m.TimerSetting.iShuttleHomeTimeout )
		{
			bMoveHome = false;
			break;
		}
		else
			; // Wait here.
	}
#endif
	return bMoveHome;
}
// Rotator
bool CFunction::ManualRotatorN(unsigned char* Turn,	unsigned char* pSensor, unsigned char* nSensor, double dTimeout)
{
#ifdef _Demo
	return true;
#endif 

	// -90
	// 1. Set Output 
	// 2. Set Timer
	// 3. Check lmt OK
	// 4. return

	int iStart = ::GetTickCount();
	*Turn = 0;	// set to false, to find P lmt

	while (1)
	{
		if ( (::GetTickCount() - iStart) >= (dTimeout) )
			return false;	// Timeout
		else if( *pSensor == 0 && *nSensor == 1 )
			return true;	// InPos	// Make in nlmt and leave plmt

		Sleep(_Wait);
	}

	return false;
}
bool CFunction::ManualRotatorP(unsigned char* Turn,	unsigned char* pSensor, unsigned char* nSensor, double dTimeout)	
{
#ifdef _Demo
	return true;
#endif 

	// 90
	// 1. Set Output 
	// 2. Set Timer
	// 3. Check lmt OK
	// 4. return

	int iStart = ::GetTickCount();
	*Turn = 1;	// set to false, to find P lmt

	while (1)
	{
		if ( (::GetTickCount() - iStart) >= (dTimeout) )
			return false;	// Timeout
		else if( *pSensor == 1 && *nSensor == 0 )
			return true;	// InPos	// Make in plmt and leave nlmt

		Sleep(_Wait);
	}

	return false;
}
bool CFunction::HeaterOnNeed()
{
	bool bNeed = false;
	if( m.TraySpec.Heating == theApp.enHeater )
	{
		bNeed = true;
	}	

	return bNeed;
}
bool CFunction::HeaterIsStable(double &dSpendTime)
{
	// Stable Time
	double m_dStableTime = m.m_West.dStableTime;
	// 1.0Ac
	if( m.m_RepeatTrayCtrl.m_iRepeatTrayMode == theApp.enRepeatTrayInOutCtrl )
	{
		int iSize = m.m_RepeatTrayTemperData.GetSize();
		if( iSize > m.m_RepeatTrayDATA.m_NowCount )
			m_dStableTime = m.m_RepeatTrayTemperData.GetAt( m.m_RepeatTrayDATA.m_NowCount ).m_dStableTime;
	}


	double m_dRemainTime = 0.0;	
	long m_lNowTime = ::GetTickCount();
	long m_lResult = m_lNowTime - m.m_heaterCtrl.m_lHeaterStart;
	m_dRemainTime = m_lResult / 1000.;
	dSpendTime = m_dRemainTime;
	if( m_dRemainTime > m_dStableTime && m.m_heaterCtrl.m_lHeaterStart != 0 )
	{
		m.m_heaterCtrl.m_bHeaterIsStable = true;
		return true;
	}
	else
	{
		return false;
	}
}
bool CFunction::CheckInitialNeed()
{
	bool bNeed = false;
//#ifdef _Demo
//#else
	if( m.Info.iStatus != theApp.enReady )
	{
		if( m.Info.iStatus == theApp.enCycleStop )
		{
			AfxMessageBox("Please Press [One Cycle/Override] to clear IC in handler.!");
			bNeed = true;
			return bNeed;
		}

		if( m.Info.iStatus == theApp.enUninitial )
		{
			AfxMessageBox("Please Press [Initial] first.!");
			bNeed = true;
			return bNeed;
		}

		if( m.Info.iStatus == theApp.enManual )
		{
			AfxMessageBox("Please Press [Initial] first.!");
			bNeed = true;
			return bNeed;
		}

		// 避免有狀態沒有檢查到
		AfxMessageBox("Please Press [Initial] first.!");
		bNeed = true;
		return bNeed;
		// 
	}
//#endif

	return bNeed;
}
void CFunction::LoadInterface()
{
	if( m.UI.FileMainTestSetting == "" )
		return;

	CString csFile = _T("");
	csFile = m.FilePath.TestSettingPath + m.UI.FileMainTestSetting;

	GetSetting(csFile, "Interface", "GPIB",	m.UI.FileMainInterFaceGpib );
	GetSetting(csFile, "Interface", "RS22",	m.UI.FileMainInterFaceRs232 );
	GetSetting(csFile, "Interface", "TCP",	m.UI.FileMainInterFaceTcp );
	GetSetting(csFile, "Interface", "TTL",	m.UI.FileMainInterFaceTtl );
}
void CFunction::LoadTcpToObject()
{
	m.m_InterfaceTcp.SetInterface( 
		m.m_TcpipInterfaceSetting.m_csCmdHeader, 
		m.m_TcpipInterfaceSetting.m_csCmdTailHeader,
		m.m_TcpipInterfaceSetting.m_csCmdBin,
		m.m_TcpipInterfaceSetting.m_csCmdGo,
		m.m_TcpipInterfaceSetting.m_csCmdReady,
		m.m_TcpipInterfaceSetting.m_csCmdStart );
}
void CFunction::LoadInterFaceTcp()
{
	CString csFile = _T("");
	csFile = m.FilePath.InterfaceTcpPath + m.UI.FileMainInterFaceTcp;

	// Header
	GetSetting(csFile, "Command Format", "CommandHeader",		m.m_TcpipInterfaceSetting.m_csCmdHeader );
	GetSetting(csFile, "Command Format", "CommandTailHeader",	m.m_TcpipInterfaceSetting.m_csCmdTailHeader );

	// HandShake communcaion
	GetSetting(csFile, "Command Format", "Command Ready",		m.m_TcpipInterfaceSetting.m_csCmdReady );
	GetSetting(csFile, "Command Format", "Command Start",		m.m_TcpipInterfaceSetting.m_csCmdStart );
	GetSetting(csFile, "Command Format", "Command Go",			m.m_TcpipInterfaceSetting.m_csCmdGo );
	GetSetting(csFile, "Command Format", "Command Bin",			m.m_TcpipInterfaceSetting.m_csCmdBin );
	
	// Timeout
	GetSetting(csFile, "Command Format", "Command Timeout",		m.m_TcpipInterfaceSetting.m_dCmdTimeout = m.Setting.m_dTimeoutHighLimit );
	GetSetting(csFile, "Command Format", "Send Start Delay",	m.m_TcpipInterfaceSetting.m_dSendStartDleay = _SendStartDelayMax );
}
void CFunction::LoadInterFaceRs232()
{
	CString csFile = _T("");
	csFile = m.FilePath.InterfaceRs232Path + m.UI.FileMainInterFaceRs232;

	// Header
	GetSetting(csFile, "Command Format", "CommandHeader",		m.m_InterfaceSetting.m_csCmdHeader );
	GetSetting(csFile, "Command Format", "CommandTailHeader",	m.m_InterfaceSetting.m_csCmdTailHeader );

	// HandShake communcaion
	GetSetting(csFile, "Command Format", "Command Ready",		m.m_InterfaceSetting.m_csCmdReady );
	GetSetting(csFile, "Command Format", "Command Start",		m.m_InterfaceSetting.m_csCmdStart );
	GetSetting(csFile, "Command Format", "Command Go",			m.m_InterfaceSetting.m_csCmdGo );
	GetSetting(csFile, "Command Format", "Command Bin",			m.m_InterfaceSetting.m_csCmdBin );
	
	// Timeout
	GetSetting(csFile, "Command Format", "Command Timeout",		m.m_InterfaceSetting.m_dCmdTimeout = m.Setting.m_dTimeoutHighLimit );
	GetSetting(csFile, "Command Format", "Send Start Delay",	m.m_InterfaceSetting.m_dSendStartDleay = _SendStartDelayMax );
}
void CFunction::LotDoneClearYieldValue()
{
	CString csFile = _T("");
	csFile = m.FilePath.OutputYieldPath;	

	//
	char cProt[1256];	
	unsigned int Count = 0;
	char cValue[256];
	unsigned int CountPrivate = 0;

	memset(cProt, '/0', sizeof(cProt));
	memset(cValue, '/0', sizeof(cValue));
	CString csGetProt = _T("");
	csGetProt =  "Yield Value";
	unsigned int iSize = ::GetPrivateProfileSection( csGetProt, cProt, 1256, csFile );

	while(Count < iSize)
	{
		memset(cValue, '/0', sizeof(cValue));
		memcpy(cValue, &cProt[Count], strlen(&cProt[Count]));
		CountPrivate = strlen(&cProt[Count]) + 1;
		Count += CountPrivate;

		CString cs;
		cs.Format("%s", cValue );
		int iStart = cs.Find("=", 0 );
		CString csPr = _T("");
		csPr = cs.Left(iStart);

		EarseYieldValue(csFile, csGetProt, csPr );
	}
}
// 1.0Ap
// Remove this and re-build new one
/*
bool CFunction::InitRemoteCtrl()
{
	bool bOK = false;

	// 1.0Ak
	// Defautl no open the com port
	if( m.m_HandlerComPort.iPortRemoteCom == 0 )
	{
		bOK = true;
		CString csMsg = _T("");
		csMsg.Format("Remote Control Port No Enable");
		f.DMsg.DMsg( csMsg );
	}
	else
	{		
		bOK = m.m_TestInterface.InitTestInterface( m.m_HandlerComPort.iPortRemoteCom );
		m.m_TestInterface.SetLogPath( m.CustomFilePath.SLTProtocolPath );
		
		if( bOK )
		{
			CString csMsg = _T("");
			csMsg.Format("Remote Control Port Open Success");
			f.DMsg.DMsg( csMsg );
		}
		else
		{
			CString csMsg = _T("");
			csMsg.Format("Remote Control Port Open Fail");
			f.DMsg.DMsg( csMsg + _DMsgMark, false );
		}
	}

	return bOK;
}
*/
// 1.0Ap
bool CFunction::InitRemoteCtrl()
{
	bool bOK = false;

	// 1.0Ap
	// Set SLT Protocol Log Path
	m.m_TestInterface.SetLogPath( m.CustomFilePath.SLTProtocolPath );

	// 1.0Ak
	// Defautl no open the com port
	if( m.m_HandlerComPort.iPortRemoteCom == 0 )
	{
		bOK = true;
		CString csMsg = _T("");
		csMsg.Format("Remote Control Port No Enable");
		f.DMsg.DMsg( csMsg );
	}
	else
	{		
		bOK = m.m_TestInterface.InitTestInterface( m.m_HandlerComPort.iPortRemoteCom );
		
		if( bOK )
		{
			CString csMsg = _T("");
			csMsg.Format("Remote Control Port Open Success");
			f.DMsg.DMsg( csMsg );
		}
		else
		{
			CString csMsg = _T("");
			csMsg.Format("Remote Control Port Open Fail");
			f.DMsg.DMsg( csMsg + _DMsgMark, false );
		}
	}

	// 1.0Ap
	m.m_TestInterface.InitTestInterfaceTCP();

	// 1.0Ap
	m.m_TestInterface.InitTestInterfaceExcute();

	//
	return bOK;
}
void CFunction::InitProtuctShuttle()
{
	if( m.InStatus.ShuttlePLmt == _ShuttlePLmtOn )
	{
		m.OutSet.Shuttle = true;
	}
}
void CFunction::InitArmLogICImage()
{
	AutoCreateFolder( m.FilePath.ArmLogICImagePath );
}
void CFunction::LoadArmLogICImagePath()
{
	CString csFile = _T("");
	csFile = m.FilePath.SystemSettingPath;

	GetSetting(csFile, "Arm Log IC Image", "Path",		m.m_ArmLogICImage.csImageFilePath );
}
void CFunction::SaveArmLogICImagePath()
{
	CString csFile = _T("");
	csFile = m.FilePath.SystemSettingPath;

	SaveSetting(csFile, "Arm Log IC Image", "Path",		m.m_ArmLogICImage.csImageFilePath );
}
void CFunction::LoadArmLogICImage()
{
	CString csFile = _T("");
	csFile = m.FilePath.SystemSettingPath;
	
	GetSetting(csFile, "Arm Log IC Image", "Enable",		m.m_ArmLogICImage.bEnableArmLogICImage );
}
void CFunction::SaveArmLogICImage()
{
	CString csFile = _T("");
	csFile = m.FilePath.SystemSettingPath;

	SaveSetting(csFile, "Arm Log IC Image", "Enable",		m.m_ArmLogICImage.bEnableArmLogICImage );
}
void CFunction::LoadAlignmentProf()
{
	CString csFile = _T("");
	csFile = m.FilePath.SystemSettingPath;

	GetSetting(csFile, "Alignment Protection", "Test Site",		
		m.Setting.m_dTestSiteProf = _AlignmentShuttle * m.m_Ratio.Inserter_GearRation );
}
void CFunction::LoadOutputYieldValue()
{
	int nGetSize = m.m_OutputYieldCounter.GetSize();
	if( nGetSize <= 0 ) 
		return;

	CString csFile = _T("");
	csFile = m.FilePath.OutputYieldPath;

	//
	char cProt[1256];	
	unsigned int Count = 0;
	char cValue[256];
	unsigned int CountPrivate = 0;

	memset(cProt, '/0', sizeof(cProt));
	memset(cValue, '/0', sizeof(cValue));
	CString csGetProt = _T("");
	csGetProt =  "Yield Value";
	unsigned int iSize = ::GetPrivateProfileSection( csGetProt, cProt, 1256, csFile );

	while(Count < iSize)
	{
		memset(cValue, '/0', sizeof(cValue));
		memcpy(cValue, &cProt[Count], strlen(&cProt[Count]));
		CountPrivate = strlen(&cProt[Count]) + 1;
		Count += CountPrivate;

		CString cs;
		cs.Format("%s", cValue );
		int iStart = cs.Find("=", 0 );
		CString csPr = _T("");
		csPr = cs.Left(iStart);

		// Get Counter
		long m_lCounter = 0;
		int nSize = m.m_OutputYieldCounter.GetSize();
		for(int i=0;i<nSize;i++)
		{			
			CString csCode = _T("");
			csCode = m.m_OutputYieldCounter.GetAt(i).m_csCode;
			if( csPr == csCode )
			{
				GetSetting(csFile, csGetProt, csPr, m_lCounter );
				tagOutputYield m_data;
				m_data.m_csCode = csCode;
				m_data.m_lCodeCounter = m_lCounter;
				m.m_OutputYieldCounter.SetAt(i, m_data);
			}
		}
	}
}
void CFunction::SaveOutputYieldValue()
{
	CString csFile = _T("");
	csFile = m.FilePath.OutputYieldPath;

	int iSize = m.m_OutputYieldCounter.GetSize();
	for(int i=0;i<iSize;i++)
	{
		CString csProt = _T("");
		csProt = m.m_OutputYieldCounter.GetAt(i).m_csCode;
		long lCounter = 0;
		lCounter = m.m_OutputYieldCounter.GetAt(i).m_lCodeCounter;
		SaveSetting(csFile, "Yield Value", csProt, lCounter );
	}
}
void CFunction::LoadLoopTest()
{
	CString csFile = _T("");
	csFile = m.FilePath.LoopTestSettingPath;
}
void CFunction::SaveLoopTest()
{
	CString csFile = _T("");
	csFile = m.FilePath.LoopTestSettingPath;
}
void CFunction::SaveLoopTested()
{
	CString csFile = _T("");
	csFile = m.FilePath.LoopTestSettingPath;
}
void CFunction::ClearLoopTest()
{

}
void CFunction::LoadIf()
{
	LoadIfNote(theApp.enNIfRs232);
	LoadIfNote(theApp.enNIfTcpIp);
}
CString CFunction::LoadIfNote(int uId)
{
	CString csIfNote = _T("");
	
	CString csFile = _T("");
	csFile = m.FilePath.InterfaceNotePath;

	switch(uId)
	{
	case theApp.enNIfRs232:
		{
			GetIfNote(csFile, "If Note", "Rs232", csIfNote );
		}
		break;
	case theApp.enNIfTcpIp:
		{
			GetIfNote(csFile, "If Note", "Tcp", csIfNote );
		}
		break;
	}

	return csIfNote;
}
void CFunction::GetIfNote(CString csFile, CString csSection, CString csProperty, CString &csValue)
{
	char cValue[10000] = {0};

	GetPrivateProfileString(csSection, csProperty, "NO_VALUE", 
		cValue, sizeof(cValue), csFile);
	CString c = cValue;
	if(c == "NO_VALUE")
	{
		::WritePrivateProfileString(csSection, csProperty, csValue, 
			csFile);
	} 
	else
		csValue = c;
}
bool CFunction::IsTextOffsetNote()
{
	bool bIsExist = false;

	CString csMsg = _T("");
	CString csAllMsg = _T("");

	//
	csMsg = GetTextOffsetNote(theApp.enNofRotatorX);
	csAllMsg += csMsg;
	csMsg = GetTextOffsetNote(theApp.enNofRotatorY);
	csAllMsg += csMsg;
	csMsg = GetTextOffsetNote(theApp.enNofRotatorZ);
	csAllMsg += csMsg;
	csMsg = GetTextOffsetNote(theApp.enNofRotatorZ2);
	csAllMsg += csMsg;

	csMsg = GetTextOffsetNote(theApp.enNofShInX);
	csAllMsg += csMsg;
	csMsg = GetTextOffsetNote(theApp.enNofShInY);
	csAllMsg += csMsg;
	csMsg = GetTextOffsetNote(theApp.enNofShInZ);
	csAllMsg += csMsg;
	csMsg = GetTextOffsetNote(theApp.enNofShInZ2);
	csAllMsg += csMsg;

	csMsg = GetTextOffsetNote(theApp.enNofShOutX);
	csAllMsg += csMsg;
	csMsg = GetTextOffsetNote(theApp.enNofShOutY);
	csAllMsg += csMsg;
	csMsg = GetTextOffsetNote(theApp.enNofShOutZ);
	csAllMsg += csMsg;

	csMsg = GetTextOffsetNote(theApp.enNofInputX);
	csAllMsg += csMsg;
	csMsg = GetTextOffsetNote(theApp.enNofInputY);
	csAllMsg += csMsg;
	csMsg = GetTextOffsetNote(theApp.enNofInputZ);
	csAllMsg += csMsg;
	csMsg = GetTextOffsetNote(theApp.enNofInputZ2);
	csAllMsg += csMsg;

	csMsg = GetTextOffsetNote(theApp.enNofOutputX);
	csAllMsg += csMsg;
	csMsg = GetTextOffsetNote(theApp.enNofOutputY);
	csAllMsg += csMsg;
	csMsg = GetTextOffsetNote(theApp.enNofOutputZ);
	csAllMsg += csMsg;
	csMsg = GetTextOffsetNote(theApp.enNofOutputZ2);
	csAllMsg += csMsg;

	csMsg = GetTextOffsetNote(theApp.enNofTsPick);
	csAllMsg += csMsg;
	csMsg = GetTextOffsetNote(theApp.enNofTsPlace);
	csAllMsg += csMsg;
	csMsg = GetTextOffsetNote(theApp.enNofTsContact);
	csAllMsg += csMsg;

	csAllMsg.TrimLeft();
	csAllMsg.TrimRight();
	if( csAllMsg != "" )
		bIsExist = true;

	return bIsExist;
}

void CFunction::LoadTextOffsetNote()
{
	// First Create
	GetTextOffsetNote(theApp.enNofRotatorX);
	GetTextOffsetNote(theApp.enNofRotatorY);
	GetTextOffsetNote(theApp.enNofRotatorZ);
	GetTextOffsetNote(theApp.enNofRotatorZ2);
		
	GetTextOffsetNote(theApp.enNofShInX);
	GetTextOffsetNote(theApp.enNofShInY);
	GetTextOffsetNote(theApp.enNofShInZ);
	GetTextOffsetNote(theApp.enNofShInZ2);

	GetTextOffsetNote(theApp.enNofShOutX);
	GetTextOffsetNote(theApp.enNofShOutY);
	GetTextOffsetNote(theApp.enNofShOutZ);

	GetTextOffsetNote(theApp.enNofInputX);
	GetTextOffsetNote(theApp.enNofInputY);
	GetTextOffsetNote(theApp.enNofInputZ);
	GetTextOffsetNote(theApp.enNofInputZ2);

	GetTextOffsetNote(theApp.enNofOutputX);
	GetTextOffsetNote(theApp.enNofOutputY);
	GetTextOffsetNote(theApp.enNofOutputZ);
	GetTextOffsetNote(theApp.enNofOutputZ2);

	GetTextOffsetNote(theApp.enNofTsPick);
	GetTextOffsetNote(theApp.enNofTsPlace);
	GetTextOffsetNote(theApp.enNofTsContact);
}
CString CFunction::GetTextOffsetNote(int uId)
{
	CString csFile = _T("");
	csFile = m.FilePath.OffsetTxtNotePath;
	CString csNote = _T("");
	switch(uId)
	{			
	case theApp.enNofRotatorX:
		{
			GetOffsetSetting( csFile, "Rotator", "X", csNote);
		}
		break;
	case theApp.enNofRotatorY:
		{
			GetOffsetSetting( csFile, "Rotator", "Y", csNote);
		}
		break;
	case theApp.enNofRotatorZ:
		{
			GetOffsetSetting( csFile, "Rotator", "Z", csNote);
		}
		break;
	case theApp.enNofRotatorZ2: // Place
		{
			GetOffsetSetting( csFile, "Rotator", "Z(Place)", csNote);
		}
		break;
	case theApp.enNofShInX:
		{
			GetOffsetSetting( csFile, "Arm In Shuttle Input", "X", csNote);
		}
		break;
	case theApp.enNofShInY:
		{
			GetOffsetSetting( csFile, "Arm In Shuttle Input", "Y", csNote);
		}
		break;
	case theApp.enNofShInZ:
		{
			GetOffsetSetting( csFile, "Arm In Shuttle Input", "Z", csNote);
		}
		break;
	case theApp.enNofShInZ2:// Place
		{
			GetOffsetSetting( csFile, "Arm In Shuttle Input", "Z(Place)", csNote);
		}
		break;
		
	case theApp.enNofShOutX:
		{
			GetOffsetSetting( csFile, "Arm In Shuttle Output", "X", csNote);
		}
		break;
	case theApp.enNofShOutY:
		{
			GetOffsetSetting( csFile, "Arm In Shuttle Output", "Y", csNote);
		}
		break;
	case theApp.enNofShOutZ:
		{
			GetOffsetSetting( csFile, "Arm In Shuttle Output", "Z", csNote);
		}
		break;
	case theApp.enNofInputX:
		{
			GetOffsetSetting( csFile, "Input Tray", "X", csNote);
		}
		break;
	case theApp.enNofInputY:
		{
			GetOffsetSetting( csFile, "Input Tray", "Y", csNote);
		}
		break;
	case theApp.enNofInputZ:
		{
			GetOffsetSetting( csFile, "Input Tray", "Z", csNote);
		}
		break;
	case theApp.enNofInputZ2:// Place
		{
			GetOffsetSetting( csFile, "Input Tray", "Z(Place)", csNote);
		}
		break;
		
	case theApp.enNofOutputX:
		{
			GetOffsetSetting( csFile, "Output Tray", "X", csNote);
		}
		break;
	case theApp.enNofOutputY:
		{
			GetOffsetSetting( csFile, "Output Tray", "Y", csNote);
		}
		break;
	case theApp.enNofOutputZ:
		{
			GetOffsetSetting( csFile, "Output Tray", "Z", csNote);
		}
		break;
	case theApp.enNofOutputZ2:// Place
		{
			GetOffsetSetting( csFile, "Output Tray", "Z(Place)", csNote);
		}
		break;
	case theApp.enNofTsPick:
		{
			GetOffsetSetting( csFile, "Test Site", "Pick", csNote);
		}
		break;
	case theApp.enNofTsPlace:
		{
			GetOffsetSetting( csFile, "Test Site", "Place", csNote);
		}
		break;
	case theApp.enNofTsContact:
		{
			GetOffsetSetting( csFile, "Test Site", "Contact", csNote);
		}
		break;
	default:
		csNote = "";
		break;
	}

	csNote.TrimLeft();
	csNote.TrimRight();

	return csNote;
}
void CFunction::GetOffsetSetting(CString csFile, CString csSection, CString csProperty, CString &csValue)
{
	char cValue[10000] = {0};

	GetPrivateProfileString(csSection, csProperty, "NO_VALUE", 
		cValue, sizeof(cValue), csFile);
	CString c = cValue;
	if(c == "NO_VALUE")
	{
		::WritePrivateProfileString(csSection, csProperty, csValue, 
			csFile);
	} 
	else
		csValue = c;
}

void CFunction::SaveSiteSettingRunMode()
{
	CString csTrayFile = _T("");
	csTrayFile = m.UI.FileMain;
	csTrayFile.TrimLeft();
	csTrayFile.TrimRight();
	if( csTrayFile != "" )
	{
		CString csFile = _T("");
		csFile = m.FilePath.TrayFilesPath + m.UI.FileMain;
		SaveSetting(csFile, "Site Setting", "Site Setting", m.Site.iRunMode );
	}
}
void CFunction::SaveManualContactTsMode()
{
	CString csFile = _T("");
	csFile = m.FilePath.SystemSettingPath;
	SaveSetting(csFile, "Manual Contact Ts Mode", 
		"DirectContactMode(1)forEnable", m.m_ManualContactMode.bIsTsDirectContact );
	SaveSetting(csFile, "Manual Contact Ts Mode", 
		"TestSite Vacc(1)forClose", m.m_ManualContactMode.bIsTsKeepVaccOn );
}
void CFunction::LoadManualContactTsMode()
{
	CString csFile = _T("");
	csFile = m.FilePath.SystemSettingPath;
	GetSetting(csFile, "Manual Contact Ts Mode", 
		"DirectContactMode(1)forEnable", m.m_ManualContactMode.bIsTsDirectContact );
	GetSetting(csFile, "Manual Contact Ts Mode", 
		"TestSite Vacc(1)forClose", m.m_ManualContactMode.bIsTsKeepVaccOn );
}
int CFunction::GetTesterBaudRate()
{
	return 9600;
}
BOOL CFunction::GetHandlerIPAddress(CString &szLocalIP)
{
	char szHostName[64];
	memset(szHostName, 0, sizeof(szHostName));
	gethostname(szHostName, sizeof(szHostName));
	HOSTENT* pHostent = gethostbyname(szHostName);

	//	
	BYTE *p;
	p =(BYTE *)pHostent->h_addr;
	CString csLocalIP = _T("");
	csLocalIP.Format("%d.%d.%d.%d", p[0], p[1], p[2], p[3]);

	//
	szLocalIP = csLocalIP;

	return TRUE;
}
BOOL CFunction::GetTesterIPAddress(char* szLocalIP)
{
	char szHostName[64];
	memset(szHostName, 0, sizeof(szHostName));
	gethostname(szHostName, sizeof(szHostName));
	HOSTENT* pHostent = gethostbyname(szHostName);
	
	SOCKADDR_IN addr;
	addr.sin_addr.s_addr = ((IN_ADDR*)pHostent->h_addr_list)->s_addr;
	strcpy(szLocalIP, inet_ntoa(addr.sin_addr));

	return TRUE;
}

// 1.0Ac
// Vision Function
tagInfoParameter CFunction::GetIMGFileSetting(CString csFilePath)
{
	tagInfoParameter m_Info;
	m_Info.dScore = 1.00;
	m_Info.iHeight = 0;
	m_Info.iWidth = 0;
	m_Info.iX = 0;
	m_Info.iY = 0;
	CString csFile = _T("");
	csFile = csFilePath;

	//
	f.GetSetting( csFile, "Source Image", "X",		m_Info.iX );
	f.GetSetting( csFile, "Source Image", "Y",		m_Info.iY );
	f.GetSetting( csFile, "Source Image", "Width",	m_Info.iWidth );
	f.GetSetting( csFile, "Source Image", "Height", m_Info.iHeight );	
	f.GetSetting( csFile, "Source Image", "Score",	m_Info.dScore );

	return m_Info;
}

void CFunction::LoadTorqueParameter()
{
	CString csFile = _T("");
	csFile = m.FilePath.TorqueStatusPar;

	GetSetting(csFile, "Torque Status", "Torque Ration",	m.m_TorqueStatusPar.dTorqueRation = 1.15 );
}
void CFunction::SaveTorqueParameter()
{
	CString csFile = _T("");
	csFile = m.FilePath.TorqueStatusPar;

	SaveSetting(csFile, "Torque Status", "Torque Ration",	m.m_TorqueStatusPar.dTorqueRation );
}

void CFunction::LoadRepeatTraySetting()
{
	CString csFile = _T("");
	csFile = m.FilePath.RepeatTrayPath;
	GetSetting(csFile, "Repeat Trat Mode", "Mode(0)None",	m.m_RepeatTrayCtrl.m_iRepeatTrayMode = 1 );
}
void CFunction::SaveRepeatTraySetting()
{
	CString csFile = _T("");
	csFile = m.FilePath.RepeatTrayPath;
	SaveSetting(csFile, "Repeat Trat Mode", "Mode(0)None",	m.m_RepeatTrayCtrl.m_iRepeatTrayMode );
}
void CFunction::LoadRepeatTrayTemper()
{
	CString csFile = _T("");
	csFile = m.FilePath.RepeatTrayTemperPath;

	// Remove data from array
	m.m_RepeatTrayTemperData.RemoveAll();

	// Load old file
	CFile file;
	if(file.Open(csFile, CFile::modeRead | CFile::shareDenyNone, NULL) != 0)
	{	
		file.SeekToBegin();
		CArchive ar(&file, CArchive::load);
		CString cs = _T("");
		while(1)
		{
			BOOL bReadOK = ar.ReadString(cs);
			if( !bReadOK )
				break;

			tagRepeatTemperData m_Data;
			m_Data.m_dSV = 0.0;
			m_Data.m_dStableTime = 0.0;
			m_Data.m_dSoakingTime = 0.0;
			m_Data.m_dTolerance = 0.0;

			CArray <CString, CString> m_Record;
			m_Record.RemoveAll();
			f.StringToIntArrayByToken(	cs, m_Record, ",");

			if( m_Record.GetSize() == 4 )
			{
				// SV
				CString csSV = _T("");
				csSV = m_Record.GetAt(0);
				csSV.TrimLeft(); csSV.TrimRight();
				m_Data.m_dSV = atof(csSV);

				// Stable Time
				CString csStableTime = _T("");
				csStableTime = m_Record.GetAt(1);
				csStableTime.TrimLeft(); csStableTime.TrimRight();
				m_Data.m_dStableTime = atof(csStableTime);

				// Soaking Time
				CString csSoakingTime = _T("");
				csSoakingTime = m_Record.GetAt(2);
				csSoakingTime.TrimLeft(); csSoakingTime.TrimRight();
				m_Data.m_dSoakingTime = atof(csSoakingTime);

				// Tolerance
				CString csTolerance = _T("");
				csTolerance = m_Record.GetAt(3);
				csTolerance.TrimLeft(); csTolerance.TrimRight();
				m_Data.m_dTolerance = atof(csTolerance);

				m.m_RepeatTrayTemperData.Add(m_Data);
			}
			else
			{
				// data break. 
			}

			Sleep(1);
		}
		ar.Close();
		file.Close();
	}
	else
	{
//		CString csMsg = _T("");
//		csMsg.Format("Load repeat tray fiel fail, %s", csFile );
//		AfxMessageBox( csMsg );
		CFile fileNew;
		if( fileNew.Open(csFile , CFile::modeCreate | CFile::modeWrite
			| CFile::modeNoTruncate | CFile::shareDenyNone, NULL) )
		{
			fileNew.SeekToBegin();
			CString csNew = _T("");
			csNew = "25.00,30.00,30.00,3.00\r\n";
			fileNew.Write( csNew.GetBuffer(0), csNew.GetLength() );
			fileNew.Close();
		}
	}	
}
CString CFunction::GetTrayFileNowMode()
{
	CString csTrayMode = _T("");
	if( m.TraySpec.Heating == theApp.enHeater )
		csTrayMode = "Heater";
	else if( m.TraySpec.Heating == theApp.enAmbit )
		csTrayMode = "Ambient";
	else if( m.TraySpec.Heating == theApp.enATCMoudle )
		csTrayMode = "ATC Module";
	else if( m.TraySpec.Heating == theApp.enTriTemperature )
		csTrayMode = "Tri-Temperature";
	else if( m.TraySpec.Heating == theApp.enPTCMoudle )
		csTrayMode = "PTC Module";
	else if( m.TraySpec.Heating == theApp.enRemote )
		csTrayMode = "Remote Module";
	else
		csTrayMode = "None";

	return csTrayMode;
}
CString CFunction::GetRunTimeFromCycleTime(long lsecs)
{
	CString csRunTime = _T("");
	int ihh = 0;	// hours
	int imm = 0;	// min
	int iss = 0;	// sec
	int idd	= 0;	// day

	if( lsecs != 0 )
	{		
		int s = 0;
		int min2 = 0;
		int s2 = 0;
		int h2 = 0;

		// secs
		iss = lsecs % 60;

		// mins
		s2 = lsecs / 60;
		imm = s2 % 60;

		// hours
		min2 = s2 / 60;
		ihh = min2 % 24;

		// day
		h2 = min2 / 24;
		idd = h2 % 24;
	}

	csRunTime.Format("%.3d:%.2d:%.2d:%.2d", idd, ihh, imm, iss );	

	return csRunTime;
}
void CFunction::SaveRepeatTrayTemper()
{
	CString csFile = _T("");
	csFile = m.FilePath.RepeatTrayTemperPath;
}
void CFunction::LoadRepeatTrayInOut()
{
	CString csFile = _T("");
	csFile = m.FilePath.RepeatTrayPath;
	GetSetting(csFile, "Repeat Trat Mode(InOutCtrl)", "Tray1",	m.m_RepeatInOutCtrl.m_iTray1 = 0 );
	GetSetting(csFile, "Repeat Trat Mode(InOutCtrl)", "Tray2",	m.m_RepeatInOutCtrl.m_iTray2 = 1 );
	GetSetting(csFile, "Repeat Times", "Times",					m.m_RepeatInOutCtrl.m_iRepeatTimes = 0 );
	GetSetting(csFile, "Repeat Temperature Confim",	"Confim",	m.m_RepeatInOutCtrl.m_iRepeatConfimFromComm = 0 );
}
void CFunction::SaveRepeatTrayInOut()
{
	CString csFile = _T("");
	csFile = m.FilePath.RepeatTrayPath;
	SaveSetting(csFile, "Repeat Trat Mode(InOutCtrl)", "Tray1",		m.m_RepeatInOutCtrl.m_iTray1 );
	SaveSetting(csFile, "Repeat Trat Mode(InOutCtrl)", "Tray2",		m.m_RepeatInOutCtrl.m_iTray2 );
	SaveSetting(csFile, "Repeat Times", "Times",					m.m_RepeatInOutCtrl.m_iRepeatTimes );
	SaveSetting(csFile, "Repeat Temperature Confim",	"Confim",	m.m_RepeatInOutCtrl.m_iRepeatConfimFromComm );
}
void CFunction::LoadRepeatTrayFunEnable()
{
	CString csFile = _T("");
	csFile = m.FilePath.RepeatTrayFunEnable;

	GetSetting(csFile, "Repeat Trat Fun Enable", "None",			m.m_EnableRepeatTrayFun.m_bNone = false );
	GetSetting(csFile, "Repeat Trat Fun Enable", "InOut Ctrl",		m.m_EnableRepeatTrayFun.m_bInOutCtrl = true );
	GetSetting(csFile, "Repeat Trat Fun Enable", "Binning Ctrl",	m.m_EnableRepeatTrayFun.m_bTrayBinningCtrl = false );
}
void CFunction::SaveRepeatTrayFunEnable()
{
	CString csFile = _T("");
	csFile = m.FilePath.RepeatTrayFunEnable;

	SaveSetting(csFile, "Repeat Trat Fun Enable", "None",			m.m_EnableRepeatTrayFun.m_bNone );
	SaveSetting(csFile, "Repeat Trat Fun Enable", "InOut Ctrl",		m.m_EnableRepeatTrayFun.m_bInOutCtrl  );
	SaveSetting(csFile, "Repeat Trat Fun Enable", "Binning Ctrl",	m.m_EnableRepeatTrayFun.m_bTrayBinningCtrl );
}
void CFunction::LoadJamRateCycleTimeInfo()
{
	CString csFile = _T("");
	csFile = m.FilePath.JamRateCycleTimePath;
	GetSetting(csFile, "Jam Rate Info", "Cycle Time",	m.m_JamRateInfo.m_lCycleTime );
}
void CFunction::SaveJamRateCycleTimeInfo()
{
	CString csFile = _T("");
	csFile = m.FilePath.JamRateCycleTimePath;
	SaveSetting(csFile, "Jam Rate Info", "Cycle Time",	m.m_JamRateInfo.m_lCycleTime );
}
CString CFunction::GetRepeatTreyDefine(int iDefine)
{
	CString csTrayDefine = _T("");
/*
	enRepeatDefineInput			= 0,
	enRepeatDefineOutput		= 1,
	enRepeatDefineBoth			= 2,
	enRepeatDefineDisable		= 3,
	enRepeatDefinePass			= 4,
	enRepeatDefineFail			= 5,
*/

/*
	#define _RepeartTrayInput	"Input"			// 入料
	#define _RepeartTrayOutput	"Output"		// 出料
	#define _RepeartTrayBoth	"Both"			// 入料/出料
	#define _RepeartTrayDisable	"Disable"		// 關閉
	#define _RepeartPass		"Pass"			// 入料(放Pass)
	#define _RepeartFail		"Fail"			// 出料(放Fail)
*/
	if( iDefine == theApp.enRepeatDefineInput )
		csTrayDefine = _RepeartTrayInput;
	else if( iDefine == theApp.enRepeatDefineOutput )
		csTrayDefine = _RepeartTrayOutput;
	else if( iDefine == theApp.enRepeatDefineBoth )
		csTrayDefine = _RepeartTrayBoth;
	else if( iDefine == theApp.enRepeatDefineDisable )
		csTrayDefine = _RepeartTrayDisable;
	else if( iDefine == theApp.enRepeatDefinePass )
		csTrayDefine = _RepeartPass;
	else if( iDefine == theApp.enRepeatDefineFail )
		csTrayDefine = _RepeartFail;
	else 
		csTrayDefine = "None";

	return csTrayDefine;
}
bool CFunction::IsTrayFileNeedTemperature()
{
	bool bIsNeed = false;
	if( m.TraySpec.Heating == theApp.enHeater )
		bIsNeed = true;
	else if( m.TraySpec.Heating == theApp.enAmbit )
		bIsNeed = false;
	else if( m.TraySpec.Heating == theApp.enATCMoudle )
		bIsNeed = false;
	else if( m.TraySpec.Heating == theApp.enTriTemperature )
		bIsNeed = false;
	else if( m.TraySpec.Heating == theApp.enPTCMoudle )
		bIsNeed = false;
	else if( m.TraySpec.Heating == theApp.enRemote )
		bIsNeed = false;
	else 
		; // Nerver be here

	return bIsNeed;
}
COLORREF CFunction::GetRepeatTrayFileColor(int iTrayFile)
{
	COLORREF color = ST_WHITE;

	if( m.TraySpec.Heating == theApp.enHeater )
	{
		color = m.m_TrayFileDefColor.m_colHeater;
	}
	else if( m.TraySpec.Heating == theApp.enAmbit )
	{
		color = m.m_TrayFileDefColor.m_colAmbit;
	}
	else if( m.TraySpec.Heating == theApp.enATCMoudle )
	{
		color = m.m_TrayFileDefColor.m_colATCModule;
	}
	else if( m.TraySpec.Heating == theApp.enTriTemperature )
	{
		color = m.m_TrayFileDefColor.m_colTriTemperature;
	}
	else if( m.TraySpec.Heating == theApp.enPTCMoudle )
	{
		color = m.m_TrayFileDefColor.m_colPTCModule;
	}
	else 
		; // Nerver be here

	return color;
}
CString CFunction::GetRepeatTrayMode()
{
	CString csRepeatTrayMode = _T("");
/*
		enRepeatTrayNone			= 0,
		enRepeatTrayInOutCtrl		= 1,
		enRepeatTrayBinningCtrl		= 2,
*/
	if( m.m_RepeatTrayCtrl.m_iRepeatTrayMode == theApp.enRepeatTrayNone )
		csRepeatTrayMode = "None";
	else if( m.m_RepeatTrayCtrl.m_iRepeatTrayMode == theApp.enRepeatTrayInOutCtrl )
		csRepeatTrayMode = "Input/Output";
	else if( m.m_RepeatTrayCtrl.m_iRepeatTrayMode == theApp.enRepeatTrayBinningCtrl )
		csRepeatTrayMode = "Binning";
	else
		csRepeatTrayMode = "None";

	return csRepeatTrayMode;
}
void CFunction::LoadTrayFileDefColor()
{
	CString csFile = _T("");
	csFile = m.FilePath.UIPath;
	
	GetSetting(csFile, "TrayFile Color", "Ambient",				m.m_TrayFileDefColor.m_colAmbit = ST_DEF_AMBIENT );
	GetSetting(csFile, "TrayFile Color", "ATC Module",			m.m_TrayFileDefColor.m_colATCModule = ST_DEF_ATC );
	GetSetting(csFile, "TrayFile Color", "Heater",				m.m_TrayFileDefColor.m_colHeater = ST_DEF_HEATER );
	GetSetting(csFile, "TrayFile Color", "PTC Module",			m.m_TrayFileDefColor.m_colPTCModule = ST_DEF_PTC );
	GetSetting(csFile, "TrayFile Color", "Tri-Temerature",		m.m_TrayFileDefColor.m_colTriTemperature = ST_DEF_TRI );
}
void CFunction::SaveTrayFileDefColor()
{
	CString csFile = _T("");
	csFile = m.FilePath.UIPath;

	SaveSetting(csFile, "TrayFile Color", "Ambient",			m.m_TrayFileDefColor.m_colAmbit );
	SaveSetting(csFile, "TrayFile Color", "ATC Module",			m.m_TrayFileDefColor.m_colATCModule );
	SaveSetting(csFile, "TrayFile Color", "Heater",				m.m_TrayFileDefColor.m_colHeater );
	SaveSetting(csFile, "TrayFile Color", "PTC Module",			m.m_TrayFileDefColor.m_colPTCModule );
	SaveSetting(csFile, "TrayFile Color", "Tri-Temerature",		m.m_TrayFileDefColor.m_colTriTemperature );
}
void CFunction::ClearJamRateInfo()
{
	m.m_JamRateInfo.m_lJamError = 0;
	m.m_JamRateInfo.m_lTotalUnit = 0;
	m.m_JamRateInfo.m_lCycleTime = 0;

//	f.SaveJamRateInfo();
	f.SaveJamRateCycleTimeInfo();
}
void CFunction::LoadJamRateInfo()
{
	CString csFile = _T("");
	csFile = m.FilePath.JamReportCounterPath;

	GetSetting(csFile, "Jam Rate Info", "Total Unit",		m.m_JamRateInfo.m_lTotalUnit );
	GetSetting(csFile, "Jam Rate Info", "Jam Counter",		m.m_JamRateInfo.m_lJamError );
}
void CFunction::SaveJamRateInfo()
{
	CString csFile = _T("");
	csFile = m.FilePath.JamReportCounterPath;

	SaveSetting(csFile, "Jam Rate Info", "Total Unit",		m.m_JamRateInfo.m_lTotalUnit );
	SaveSetting(csFile, "Jam Rate Info", "Jam Counter",		m.m_JamRateInfo.m_lJamError );
}
void CFunction::SaveJamRateTotalCounter()
{
	CString csFile = _T("");
	csFile = m.FilePath.JamReportCounterPath;
	SaveSetting(csFile, "Jam Rate Info", "Total Unit",		m.m_JamRateInfo.m_lTotalUnit );
}
void CFunction::InsertJamRateTotalCounter()
{
	if( m.Setting.m_bShowHandlerStatus == 1 )
	{
		m.m_JamRateInfo.m_lTotalUnit++;
		SaveJamRateTotalCounter();
	}
}
void CFunction::InsertJamRateCounter(int iCode)
{
	if( m.Setting.m_bShowHandlerStatus == 1 )
	{
		int iSize = m.m_ErrorRateData.GetSize();
		for(int i=0;i<iSize;i++)
		{
			int m_iGetCode = m.m_ErrorRateData.GetAt(i).iCode;
			if( iCode == m_iGetCode )
			{		
				m.m_JamRateInfo.m_lJamError++;
				f.SaveJamRateInfo();	
				break;
			}
		}
	}
	else
	{
		// do nothing.
	}
}

int CFunction::GetRepeatTrayModeMoation()
{
	int iMode = 0;
	if( m.m_RepeatInOutCtrl.m_iTray1 == theApp.enRepeatDefineInput &&
		m.m_RepeatInOutCtrl.m_iTray2 == theApp.enRepeatDefineOutput )
	{
		// Input->Output
		return theApp.enRepeatTray1ToTray2;
	}
	else if( m.m_RepeatInOutCtrl.m_iTray1 == theApp.enRepeatDefineOutput &&
		m.m_RepeatInOutCtrl.m_iTray2 == theApp.enRepeatDefineInput )
	{
		// Output->Input
		return theApp.enRepeatTray2ToTray1;
	}
	else if( m.m_RepeatInOutCtrl.m_iTray1 == theApp.enRepeatDefineBoth &&
		m.m_RepeatInOutCtrl.m_iTray2 == theApp.enRepeatDefineDisable )
	{
		// Both, Disable
		return theApp.enRepeatTray1AndDisable;
	}
	else if( m.m_RepeatInOutCtrl.m_iTray1 == theApp.enRepeatDefineDisable &&
		m.m_RepeatInOutCtrl.m_iTray2 == theApp.enRepeatDefineBoth )
	{
		// Disable, Both
		return theApp.enRepeatDisableAndTray2;
	}
	else if( m.m_RepeatInOutCtrl.m_iTray1 == theApp.enRepeatDefineBoth &&
		m.m_RepeatInOutCtrl.m_iTray2 == theApp.enRepeatDefineBoth )
	{
		// Both, Both
		return theApp.enRepeatTray1AndTray2;
	}
	else if( m.m_RepeatInOutCtrl.m_iTray1 == theApp.enRepeatDefinePass &&
		m.m_RepeatInOutCtrl.m_iTray2 == theApp.enRepeatDefineFail )
	{
		// Pass, Fail
		return theApp.enRepeatPass1AndFail2;
	}
	else if( m.m_RepeatInOutCtrl.m_iTray1 == theApp.enRepeatDefineFail && 
		m.m_RepeatInOutCtrl.m_iTray2 == theApp.enRepeatDefinePass )
	{
		// Fail, Pass
		return theApp.enRepeatFail1AndPass2;
	}

	return iMode;
}
void CFunction::ClearRepeatTrayDATA()
{
	m.m_RepeatTrayDATA.m_NowCount = 0;
	f.SaveNowMoation();
}
double CFunction::GetNowTemperature(int NowCount)
{
	double m_dNowTemperature = 0.0;
	int iSize = m.m_RepeatTrayTemperData.GetSize();
	if( iSize > 0 && iSize > NowCount )
		m_dNowTemperature = m.m_RepeatTrayTemperData.GetAt(NowCount).m_dSV;

	return m_dNowTemperature;
}
int CFunction::GetRepeatTrayTimes()
{
	int iRepeatTimes = 0;
	if ( f.IsTrayFileNeedTemperature() )
		iRepeatTimes = m.m_RepeatTrayTemperData.GetSize();
	else
		iRepeatTimes = m.m_RepeatInOutCtrl.m_iRepeatTimes;

	return iRepeatTimes;
}
int CFunction::GetNowMoation(int NowCount)
{
	int iMationNow = 0;	
	iMationNow = NowCount % 2;	
	return iMationNow;
}	
void CFunction::LoadNowMoation()
{
	CString csFile = _T("");
	csFile = m.FilePath.RepeatTrayCurrPath;
	GetSetting(csFile, "Repeat Tray Operation", "Now Times",	m.m_RepeatTrayDATA.m_NowCount );	
}
void CFunction::SaveNowMoation()
{
	CString csFile = _T("");
	csFile = m.FilePath.RepeatTrayCurrPath;
	SaveSetting(csFile, "Repeat Tray Operation", "Now Times",	m.m_RepeatTrayDATA.m_NowCount );
}
void CFunction::LoadRepeaterTrayCommand()
{
	CString csFile = _T("");
	csFile = m.FilePath.UIPath;
	GetSetting(csFile, "Repeat Tray Confim Command", "Book",		m.m_RepeatConfimCmd.m_csBook );
	GetSetting(csFile, "Repeat Tray Confim Command", "Soak",		m.m_RepeatConfimCmd.m_csSoakTime );
	GetSetting(csFile, "Repeat Tray Confim Command", "Stable",		m.m_RepeatConfimCmd.m_csStableTime );
	GetSetting(csFile, "Repeat Tray Confim Command", "SV",			m.m_RepeatConfimCmd.m_csSV );
	GetSetting(csFile, "Repeat Tray Confim Command", "Tolerance",	m.m_RepeatConfimCmd.m_csTolerance );
	GetSetting(csFile, "Repeat Tray Confim Command", "Timeout",		m.m_RepeatConfimCmd.m_dTimeout = 2.00 );

	// Book
	m.m_RepeatConfimCmd.m_csBook.TrimLeft(); m.m_RepeatConfimCmd.m_csBook.TrimRight();
	if( m.m_RepeatConfimCmd.m_csBook == "" )
	{
		m.m_RepeatConfimCmd.m_csBook = "Book=";
		SaveSetting(csFile, "Repeat Tray Confim Command", "Book",		m.m_RepeatConfimCmd.m_csBook );
	}
	// Soak Time
	m.m_RepeatConfimCmd.m_csSoakTime.TrimLeft(); m.m_RepeatConfimCmd.m_csSoakTime.TrimRight();
	if( m.m_RepeatConfimCmd.m_csSoakTime == "" )
	{
		m.m_RepeatConfimCmd.m_csSoakTime = "SoakTime=";
		SaveSetting(csFile, "Repeat Tray Confim Command", "Soak",		m.m_RepeatConfimCmd.m_csSoakTime );
	}
	// Stable Time
	m.m_RepeatConfimCmd.m_csStableTime.TrimLeft(); m.m_RepeatConfimCmd.m_csStableTime.TrimRight();
	if( m.m_RepeatConfimCmd.m_csStableTime == "" )
	{
		m.m_RepeatConfimCmd.m_csStableTime = "StableTime=";
		SaveSetting(csFile, "Repeat Tray Confim Command", "Stable",		m.m_RepeatConfimCmd.m_csStableTime );
	}
	// SV
	m.m_RepeatConfimCmd.m_csSV.TrimLeft(); m.m_RepeatConfimCmd.m_csSV.TrimRight();
	if( m.m_RepeatConfimCmd.m_csSV == "" )
	{
		m.m_RepeatConfimCmd.m_csSV = "SV=";
		SaveSetting(csFile, "Repeat Tray Confim Command", "SV",			m.m_RepeatConfimCmd.m_csSV );
	}
	// Tolerance
	m.m_RepeatConfimCmd.m_csTolerance.TrimLeft(); m.m_RepeatConfimCmd.m_csTolerance.TrimRight();
	if( m.m_RepeatConfimCmd.m_csTolerance == "" )
	{
		m.m_RepeatConfimCmd.m_csTolerance = "Tolerance=";
		SaveSetting(csFile, "Repeat Tray Confim Command", "Tolerance",	m.m_RepeatConfimCmd.m_csTolerance );
	}
}
void CFunction::LoadTowerSetting()
{
	CString csFile = _T("");
	csFile = m.FilePath.SystemSettingPath;

	// blink
	for(int i=0;i<_MaxTowerBlink;i++)
	{
		CString csBlink = _T("");
		csBlink.Format("%s%.2d",_MaxTowerDesc, i+1);
		GetSetting(csFile, _TowerSetupSetting, csBlink, m.m_TowerSetupSetting.dBlinkTime[i] = 0.5 );
	}

	// Tower Setting
	///////////////////////////////////////////////////////////////////////////
	// Uninitial
	CString csUninitial = _T("");
	csUninitial = "Uninitial";
	GetSetting(csFile, _TowerSetupSetting, csUninitial + _TowerRed,			m.m_TowerSetupSetting.Uninitial.LightRedChoise = theApp.enTowerChoiseDisable );
	GetSetting(csFile, _TowerSetupSetting, csUninitial + _TowerYellow,		m.m_TowerSetupSetting.Uninitial.LightYellowChoise = theApp.enTowerChoiseEnable );
	GetSetting(csFile, _TowerSetupSetting, csUninitial + _TowerGreen,		m.m_TowerSetupSetting.Uninitial.LightGreenChoise = theApp.enTowerChoiseDisable );

	// Initial
	CString csInitial = _T("");
	csInitial = "Initial";
	GetSetting(csFile, _TowerSetupSetting, csInitial + _TowerRed,			m.m_TowerSetupSetting.Initial.LightRedChoise = theApp.enTowerChoiseEnable );
	GetSetting(csFile, _TowerSetupSetting, csInitial + _TowerYellow,		m.m_TowerSetupSetting.Initial.LightYellowChoise = theApp.enTowerChoiseDisable );
	GetSetting(csFile, _TowerSetupSetting, csInitial + _TowerGreen,			m.m_TowerSetupSetting.Initial.LightGreenChoise = theApp.enTowerChoiseEnable );

	// Cycle
	CString csCycle = _T("");
	csCycle = "Cycle";
	GetSetting(csFile, _TowerSetupSetting, csCycle + _TowerRed,				m.m_TowerSetupSetting.Cycle.LightRedChoise = theApp.enTowerChoiseDisable );
	GetSetting(csFile, _TowerSetupSetting, csCycle + _TowerYellow,			m.m_TowerSetupSetting.Cycle.LightYellowChoise = theApp.enTowerChoiseDisable );
	GetSetting(csFile, _TowerSetupSetting, csCycle + _TowerGreen,			m.m_TowerSetupSetting.Cycle.LightGreenChoise = theApp.enTowerChoiseEnable );

	// Cycle Stop
	CString csCycleStop = _T("");
	csCycleStop = "CycleStop";
	GetSetting(csFile, _TowerSetupSetting, csCycleStop + _TowerRed,			m.m_TowerSetupSetting.CycleStop.LightRedChoise = theApp.enTowerChoiseDisable );
	GetSetting(csFile, _TowerSetupSetting, csCycleStop + _TowerYellow,		m.m_TowerSetupSetting.CycleStop.LightYellowChoise = theApp.enTowerChoiseEnable );
	GetSetting(csFile, _TowerSetupSetting, csCycleStop + _TowerGreen,		m.m_TowerSetupSetting.CycleStop.LightGreenChoise = theApp.enTowerChoiseDisable );

	// One Cycle
	CString csOneCycle = _T("");
	csOneCycle = "OneCycle";
	GetSetting(csFile, _TowerSetupSetting, csOneCycle + _TowerRed,			m.m_TowerSetupSetting.OneCycle.LightRedChoise = theApp.enTowerChoiseDisable );
	GetSetting(csFile, _TowerSetupSetting, csOneCycle + _TowerYellow,		m.m_TowerSetupSetting.OneCycle.LightYellowChoise = theApp.enTowerChoiseDisable );
	GetSetting(csFile, _TowerSetupSetting, csOneCycle + _TowerGreen,		m.m_TowerSetupSetting.OneCycle.LightGreenChoise = theApp.enTowerChoiseEnable );

	// One Cycle Stop
	CString csOneCycleStop = _T("");
	csOneCycleStop = "OneCycleStop";
	GetSetting(csFile, _TowerSetupSetting, csOneCycleStop + _TowerRed,		m.m_TowerSetupSetting.OneCycleStop.LightRedChoise = theApp.enTowerChoiseDisable );
	GetSetting(csFile, _TowerSetupSetting, csOneCycleStop + _TowerYellow,	m.m_TowerSetupSetting.OneCycleStop.LightYellowChoise = theApp.enTowerChoiseEnable );
	GetSetting(csFile, _TowerSetupSetting, csOneCycleStop + _TowerGreen,	m.m_TowerSetupSetting.OneCycleStop.LightGreenChoise = theApp.enTowerChoiseDisable );

	// Override
	CString csOverride = _T("");
	csOverride = "Override";
	GetSetting(csFile, _TowerSetupSetting, csOverride + _TowerRed,			m.m_TowerSetupSetting.Override.LightRedChoise = theApp.enTowerChoiseDisable );
	GetSetting(csFile, _TowerSetupSetting, csOverride + _TowerYellow,		m.m_TowerSetupSetting.Override.LightYellowChoise = theApp.enTowerChoiseDisable );
	GetSetting(csFile, _TowerSetupSetting, csOverride + _TowerGreen,		m.m_TowerSetupSetting.Override.LightGreenChoise = theApp.enTowerChoiseEnable );

	// Override Stop
	CString csOverrideStop = _T("");
	csOverrideStop = "OverrideStop";
	GetSetting(csFile, _TowerSetupSetting, csOverrideStop + _TowerRed,		m.m_TowerSetupSetting.OverrideStop.LightRedChoise = theApp.enTowerChoiseDisable );
	GetSetting(csFile, _TowerSetupSetting, csOverrideStop + _TowerYellow,	m.m_TowerSetupSetting.OverrideStop.LightYellowChoise = theApp.enTowerChoiseEnable );
	GetSetting(csFile, _TowerSetupSetting, csOverrideStop + _TowerGreen,	m.m_TowerSetupSetting.OverrideStop.LightGreenChoise = theApp.enTowerChoiseDisable );

	// Manual
	CString csManual = _T("");
	csManual = "Manual";
	GetSetting(csFile, _TowerSetupSetting, csManual + _TowerRed,			m.m_TowerSetupSetting.Manual.LightRedChoise = theApp.enTowerChoiseDisable );
	GetSetting(csFile, _TowerSetupSetting, csManual + _TowerYellow,			m.m_TowerSetupSetting.Manual.LightYellowChoise = theApp.enTowerChoiseDisable );
	GetSetting(csFile, _TowerSetupSetting, csManual + _TowerGreen,			m.m_TowerSetupSetting.Manual.LightGreenChoise = theApp.enTowerChoiseEnable );

	// Manual Stop
	CString csManualStop = _T("");
	csManualStop = "ManualStop";
	GetSetting(csFile, _TowerSetupSetting, csManualStop + _TowerRed,		m.m_TowerSetupSetting.ManualStop.LightRedChoise = theApp.enTowerChoiseDisable );
	GetSetting(csFile, _TowerSetupSetting, csManualStop + _TowerYellow,		m.m_TowerSetupSetting.ManualStop.LightYellowChoise = theApp.enTowerChoiseEnable );
	GetSetting(csFile, _TowerSetupSetting, csManualStop + _TowerGreen,		m.m_TowerSetupSetting.ManualStop.LightGreenChoise = theApp.enTowerChoiseDisable );

	// Ready
	CString csReady = _T("");
	csReady = "Ready";
	GetSetting(csFile, _TowerSetupSetting, csReady + _TowerRed,				m.m_TowerSetupSetting.Ready.LightRedChoise = theApp.enTowerChoiseDisable );
	GetSetting(csFile, _TowerSetupSetting, csReady + _TowerYellow,			m.m_TowerSetupSetting.Ready.LightYellowChoise = theApp.enTowerChoiseEnable );
	GetSetting(csFile, _TowerSetupSetting, csReady + _TowerGreen,			m.m_TowerSetupSetting.Ready.LightGreenChoise = theApp.enTowerChoiseDisable );
}
void CFunction::SavetowerSetting()
{
	CString csFile = _T("");
	csFile = m.FilePath.SystemSettingPath;

	// blink
	for(int i=0;i<_MaxTowerBlink;i++)
	{
		CString csBlink = _T("");
		csBlink.Format("%s%.2d",_MaxTowerDesc, i+1);
		SaveSetting(csFile, _TowerSetupSetting, csBlink, m.m_TowerSetupSetting.dBlinkTime[i]);
	}

	// Tower Setting
	///////////////////////////////////////////////////////////////////////////
	// Uninitial
	CString csUninitial = _T("");
	csUninitial = "Uninitial";
	SaveSetting(csFile, _TowerSetupSetting, csUninitial + _TowerRed,		m.m_TowerSetupSetting.Uninitial.LightRedChoise );
	SaveSetting(csFile, _TowerSetupSetting, csUninitial + _TowerYellow,		m.m_TowerSetupSetting.Uninitial.LightYellowChoise );
	SaveSetting(csFile, _TowerSetupSetting, csUninitial + _TowerGreen,		m.m_TowerSetupSetting.Uninitial.LightGreenChoise );

	// Initial
	CString csInitial = _T("");
	csInitial = "Initial";
	SaveSetting(csFile, _TowerSetupSetting, csInitial + _TowerRed,			m.m_TowerSetupSetting.Initial.LightRedChoise );
	SaveSetting(csFile, _TowerSetupSetting, csInitial + _TowerYellow,		m.m_TowerSetupSetting.Initial.LightYellowChoise );
	SaveSetting(csFile, _TowerSetupSetting, csInitial + _TowerGreen,		m.m_TowerSetupSetting.Initial.LightGreenChoise );

	// Cycle
	CString csCycle = _T("");
	csCycle = "Cycle";
	SaveSetting(csFile, _TowerSetupSetting, csCycle + _TowerRed,			m.m_TowerSetupSetting.Cycle.LightRedChoise );
	SaveSetting(csFile, _TowerSetupSetting, csCycle + _TowerYellow,			m.m_TowerSetupSetting.Cycle.LightYellowChoise );
	SaveSetting(csFile, _TowerSetupSetting, csCycle + _TowerGreen,			m.m_TowerSetupSetting.Cycle.LightGreenChoise );

	// Cycle Stop
	CString csCycleStop = _T("");
	csCycleStop = "CycleStop";
	SaveSetting(csFile, _TowerSetupSetting, csCycleStop + _TowerRed,		m.m_TowerSetupSetting.CycleStop.LightRedChoise );
	SaveSetting(csFile, _TowerSetupSetting, csCycleStop + _TowerYellow,		m.m_TowerSetupSetting.CycleStop.LightYellowChoise );
	SaveSetting(csFile, _TowerSetupSetting, csCycleStop + _TowerGreen,		m.m_TowerSetupSetting.CycleStop.LightGreenChoise );

	// One Cycle
	CString csOneCycle = _T("");
	csOneCycle = "OneCycle";
	SaveSetting(csFile, _TowerSetupSetting, csOneCycle + _TowerRed,			m.m_TowerSetupSetting.OneCycle.LightRedChoise );
	SaveSetting(csFile, _TowerSetupSetting, csOneCycle + _TowerYellow,		m.m_TowerSetupSetting.OneCycle.LightYellowChoise );
	SaveSetting(csFile, _TowerSetupSetting, csOneCycle + _TowerGreen,		m.m_TowerSetupSetting.OneCycle.LightGreenChoise );

	// One Cycle Stop
	CString csOneCycleStop = _T("");
	csOneCycleStop = "OneCycleStop";
	SaveSetting(csFile, _TowerSetupSetting, csOneCycleStop + _TowerRed,		m.m_TowerSetupSetting.OneCycleStop.LightRedChoise );
	SaveSetting(csFile, _TowerSetupSetting, csOneCycleStop + _TowerYellow,	m.m_TowerSetupSetting.OneCycleStop.LightYellowChoise );
	SaveSetting(csFile, _TowerSetupSetting, csOneCycleStop + _TowerGreen,	m.m_TowerSetupSetting.OneCycleStop.LightGreenChoise );

	// Override
	CString csOverride = _T("");
	csOverride = "Override";
	SaveSetting(csFile, _TowerSetupSetting, csOverride + _TowerRed,			m.m_TowerSetupSetting.Override.LightRedChoise );
	SaveSetting(csFile, _TowerSetupSetting, csOverride + _TowerYellow,		m.m_TowerSetupSetting.Override.LightYellowChoise );
	SaveSetting(csFile, _TowerSetupSetting, csOverride + _TowerGreen,		m.m_TowerSetupSetting.Override.LightGreenChoise );

	// Override Stop
	CString csOverrideStop = _T("");
	csOverrideStop = "OverrideStop";
	SaveSetting(csFile, _TowerSetupSetting, csOverrideStop + _TowerRed,		m.m_TowerSetupSetting.OverrideStop.LightRedChoise );
	SaveSetting(csFile, _TowerSetupSetting, csOverrideStop + _TowerYellow,	m.m_TowerSetupSetting.OverrideStop.LightYellowChoise );
	SaveSetting(csFile, _TowerSetupSetting, csOverrideStop + _TowerGreen,	m.m_TowerSetupSetting.OverrideStop.LightGreenChoise );

	// Manual
	CString csManual = _T("");
	csManual = "Manual";
	SaveSetting(csFile, _TowerSetupSetting, csManual + _TowerRed,			m.m_TowerSetupSetting.Manual.LightRedChoise );
	SaveSetting(csFile, _TowerSetupSetting, csManual + _TowerYellow,		m.m_TowerSetupSetting.Manual.LightYellowChoise );
	SaveSetting(csFile, _TowerSetupSetting, csManual + _TowerGreen,			m.m_TowerSetupSetting.Manual.LightGreenChoise );

	// Manual Stop
	CString csManualStop = _T("");
	csManualStop = "ManualStop";
	SaveSetting(csFile, _TowerSetupSetting, csManualStop + _TowerRed,		m.m_TowerSetupSetting.ManualStop.LightRedChoise );
	SaveSetting(csFile, _TowerSetupSetting, csManualStop + _TowerYellow,	m.m_TowerSetupSetting.ManualStop.LightYellowChoise );
	SaveSetting(csFile, _TowerSetupSetting, csManualStop + _TowerGreen,		m.m_TowerSetupSetting.ManualStop.LightGreenChoise );

	// Ready
	CString csReady = _T("");
	csReady = "Ready";
	SaveSetting(csFile, _TowerSetupSetting, csReady + _TowerRed,			m.m_TowerSetupSetting.Ready.LightRedChoise );
	SaveSetting(csFile, _TowerSetupSetting, csReady + _TowerYellow,			m.m_TowerSetupSetting.Ready.LightYellowChoise );
	SaveSetting(csFile, _TowerSetupSetting, csReady + _TowerGreen,			m.m_TowerSetupSetting.Ready.LightGreenChoise );
}
static CMutex MutexUPHReportLog;
void CFunction::ExportUPHLogReport(CString csFileName, CArray <double, double> &m_UPHLog )
{
	CSingleLock Lock(&MutexUPHReportLog);
	Lock.Lock();

	// Get Systme Time...
	SYSTEMTIME Time;
	::GetLocalTime(&Time);

	// Convert Time Format
	CString csMounth	= _T("");
	CString csDay		= _T("");
	CString csHour		= _T("");
	CString csMin		= _T("");

	if( Time.wMonth < 10 )
		csMounth.Format("0%d", Time.wMonth );
	else
		csMounth.Format("%d", Time.wMonth );
	if( Time.wDay < 10 )
		csDay.Format("0%d", Time.wDay );
	else
		csDay.Format("%d", Time.wDay );

	if( Time.wHour < 10 )
		csHour.Format("0%d", Time.wHour );
	else
		csHour.Format("%d", Time.wHour );

	if( Time.wMinute < 10 )
		csMin.Format("0%d", Time.wMinute );
	else
		csMin.Format("%d", Time.wMinute );

	// Create File
	CString csFileNameTime = _T("");
	csFileNameTime.Format("UPHReport_%s_%d%s%s_%s", csFileName, Time.wYear, csMounth, csDay, csHour );
	CString csSaveFileName = csFileNameTime + _UPHLogReport;
	CString csFile = m.CustomFilePath.UPHReportPath + csSaveFileName;

	CTime time = CTime::GetCurrentTime();
	// Time
	CString cstime = _T("");
	SYSTEMTIME ti; 
	GetLocalTime(&ti);
	cstime.Format("%d.%d.%d.%d.%5.2f", 
		ti.wMonth, ti.wDay, ti.wHour, ti.wMinute, ti.wSecond + ( ti.wMilliseconds / 1000. ) );

	// File write
	CFile file;	
	CString csDATA = _T("");
	int iSerial = 0;
	CString csSerial;
	if(file.Open(csFile, CFile::modeCreate | CFile::modeWrite | CFile::shareDenyNone
		| CFile::modeNoTruncate, NULL) != 0)
	{
		int iSize = m_UPHLog.GetSize();
		for(int i=0;i<iSize;i++)
		{
			csDATA.Format("%d, %5.2f\r\n", i+1,  m_UPHLog.GetAt(i));
			file.SeekToEnd();
			file.Write(csDATA.GetBuffer(0), csDATA.GetLength());
		}		
	}		
	file.Close();

	Lock.Unlock();
}
void CFunction::ExportUPHReport(int iReport, CArray <double, double> &m_UPHLog)
{
	switch( iReport )
	{
	case enUPHExportNone:
		{
			
		}
		break;
	case enUPHExportTsSel:
		{
			f.ExportUPHLogReport( _UPHTs, m_UPHLog );
		}
		break;
	default:
		break;
	}
}
void CFunction::TSMessageCounter()
{
	if( m.Page.Run.GetSafeHwnd() != NULL )
	{
		::SendMessage(m.Page.Run.GetSafeHwnd(), 
			WM_UPDATA_TS_COUNTER, NULL , NULL );	
	}
}
void CFunction::UPHMessageForClear()
{
	if( theApp.m_DlgUPHData.GetSafeHwnd() != NULL )
	{
		::SendMessage(theApp.m_DlgUPHData.GetSafeHwnd(), 
			WM_UPH_CLEAR, NULL , NULL );	
	}	
}
void CFunction::UPHMessageForTs()
{
	if( theApp.m_DlgUPHData.GetSafeHwnd() != NULL )
	{
		::SendMessage(theApp.m_DlgUPHData.GetSafeHwnd(), 
			WM_UPH_TS, NULL , NULL );	
	}	
}

void CFunction::MessageCommunicationInfo(CString csInfo )
{
	if( theApp.m_DlgCommunicationInfo.GetSafeHwnd() != NULL )
	{
		::SendMessage(theApp.m_DlgCommunicationInfo.GetSafeHwnd(), 
			WM_COMM_INFO, (WPARAM)&csInfo , (LPARAM)&csInfo );	
	}
}
void CFunction::LoadLastTrayFile()
{
	CString csFile = _T("");
	csFile = m.FilePath.SystemSettingPath;

	GetSetting(csFile, "Last TrayFile", "FileName",		m.m_LastTrayFile.csLastTrayFile );
}
void CFunction::SaveLastTrayFile()
{
	CString csFile = _T("");
	csFile = m.FilePath.SystemSettingPath;
	m.m_LastTrayFile.csLastTrayFile	= m.UI.FileMain;

	SaveSetting(csFile, "Last TrayFile", "FileName",	m.m_LastTrayFile.csLastTrayFile );
}
void CFunction::IsRepeatHeaterNeed()
{
	if( m.TraySpec.Heating == theApp.enRemote )
		m.RemoteOutSet.HeaterOn = true;
}
void CFunction::AutoSeletLastTrayFile()
{
	if( m.Setting.m_bEnableAutoSelLastTrayFile == 1 )
	{
		m.UI.FileMain						= m.m_LastTrayData.FileMain;
		m.UI.FileMainMapping				= m.m_LastTrayData.FileMainMapping;
		m.UI.FileMainTestSetting			= m.m_LastTrayData.FileMainTestSetting;
		m.TraySpec.VisionOcrPatternName		= m.m_LastTrayData.VisionOcrPatternName;
		m.TraySpec.VisionPatternName		= m.m_LastTrayData.VisionPatternName;

		f.SaveUI();
	}
}
void CFunction::LoadLastTrayData()
{
	CString csFile = _T("");
	csFile = m.FilePath.UIPath;
	
	GetSetting(csFile, "Auro TrayFile Data", "FileName",	m.m_LastTrayData.FileMain );
	GetSetting(csFile, "Auro TrayFile Data", "Mapping",		m.m_LastTrayData.FileMainMapping );
	GetSetting(csFile, "Auro TrayFile Data", "TestSet",		m.m_LastTrayData.FileMainTestSetting );
	GetSetting(csFile, "Auro TrayFile Data", "OcrPattern",	m.m_LastTrayData.VisionOcrPatternName );
	GetSetting(csFile, "Auro TrayFile Data", "Pattern",		m.m_LastTrayData.VisionPatternName );
}
void CFunction::SaveLastTrayData()
{
	CString csFile = _T("");
	csFile = m.FilePath.UIPath;
	
	SaveSetting(csFile, "Auro TrayFile Data", "FileName",	m.m_LastTrayData.FileMain );
	SaveSetting(csFile, "Auro TrayFile Data", "Mapping",	m.m_LastTrayData.FileMainMapping );
	SaveSetting(csFile, "Auro TrayFile Data", "TestSet",	m.m_LastTrayData.FileMainTestSetting );
	SaveSetting(csFile, "Auro TrayFile Data", "OcrPattern",	m.m_LastTrayData.VisionOcrPatternName );
	SaveSetting(csFile, "Auro TrayFile Data", "Pattern",	m.m_LastTrayData.VisionPatternName );
}
void CFunction::LotDeviceSetup(CString csTrayFile)
{
	CString csFile = _T("");
	csFile = m.FilePath.TrayFilesPath + csTrayFile;

	f.GetSetting(csFile, "Mapping",	 "MappingFile",	m.UI.FileMainMapping );
	f.GetSetting(csFile, "Testing",	 "TestFile",	m.UI.FileMainTestSetting );

	m.UI.FileMain					= csTrayFile;
	f.LoadTraySpec();

	m.TraySpec.MappingName			= m.UI.FileMainMapping;
	m.TraySpec.TestingName			= m.UI.FileMainTestSetting;
	f.SaveTraySpec();

	f.SaveUI();
	f.LoadUI();
	// Save & Load UI

	// 1: Speed. 2:Yield. 3: Offset. 4:TraySpec.ABCD. 5: Temperature 6: SiteSetting. 7:Timer. 8:TTL
	// 9: Drop/Place. 10:Category. 11:Test Info. 12: Bin Mapping. 13: Slow Contact
	
	f.LoadSpeed();			// #1
	f.LoadYield();			// #2
	f.LoadOffset();			// #3
	f.LoadTraySpec();		// #4
	f.LoadSiteSetting();	// #5
	f.LoadTimer();			// #6
	f.LoadBinMapping();		// #7
//	f.LoadCategory();		// #7
	f.LoadPogoParameter();	// #8
	f.LoadOutputYield();	// #9

	f.LoadAlignment();		// 	
	f.LoadMotorParameter();
	f.LoadTestSetting();
	//
	f.LoadInterface();
	f.LoadInterFaceRs232();
	f.LoadInterFaceTcp();
	f.LoadTcpToObject();

	// 更新 Run Page 畫面.!
	m.Page.Run.UpdateSetting();

	// 重新設定 Tray Data
	f.SetTrayData();

	// 更新整個 Tray 的資料
	theApp.m_InputTray.ChangeTray();
	theApp.m_OutputTray.ChangeTray();

	// 更新整個 Tray 的資料 / Repeat Tray
	theApp.m_Tray1.ChangeTray();
	theApp.m_Tray2.ChangeTray();

	// 紀錄本次所選 TrayFile
	f.SaveLastTrayFile();
}

// 1.0Ah
void CFunction::SetTitleExtend(LPVOID p, int nType)
{
	CDialog *dr = (CDialog *)p;
 
	if( dr->GetSafeHwnd() != NULL )
	{
		CString csOrignal = _T("");
		dr->GetWindowText( csOrignal );
		if( nType == theApp.enTitleTrayFile )
			dr->SetWindowText( csOrignal + m.m_TitleExtendNote.TitleTrayExtendNote );
		else if( nType == theApp.enTtileMachineFile )
			dr->SetWindowText( csOrignal + m.m_TitleExtendNote.TitleMachineExtend );
		else
		{
			// Nerver be here
		}
	}
}
void CFunction::LoadTitleExtend()
{
	CString csFile = _T("");
	csFile = m.FilePath.UIPath;

	GetSetting(csFile, "Ttile Extend Note", "Tray",		m.m_TitleExtendNote.TitleTrayExtendNote );
	GetSetting(csFile, "Ttile Extend Note", "Machine",	m.m_TitleExtendNote.TitleMachineExtend );

	if( m.m_TitleExtendNote.TitleTrayExtendNote == "" )
		m.m_TitleExtendNote.TitleTrayExtendNote = _TrayRemind;

	if( m.m_TitleExtendNote.TitleMachineExtend == "" )
		m.m_TitleExtendNote.TitleMachineExtend = _HandlerRemind;
}
CString CFunction::GetManualContactNote()
{
	CString csManualContactNote = _T("");
	
	CString csFile = _T("");
	csFile = m.FilePath.MContactNotePath;

	//
	CString csNote = _T("");

	unsigned char cTemp[1001] = {0};
	unsigned long ulNumRead = 0;
	HANDLE	m_hComm = NULL;

	m_hComm = CreateFile (  csFile,// Pointer to the name of the port
		GENERIC_READ | GENERIC_WRITE,
		// Access (read/write) mode
		0,            // Share mode
		NULL,         // Pointer to the security attribute
		OPEN_EXISTING,// How to open the serial port
		0,            // Port attributes
		NULL);        // Handle to port with attribute

	while(1)
	{
		::ReadFile(m_hComm, cTemp, sizeof(cTemp), &ulNumRead, NULL);
		if(ulNumRead == 0)
			break;
		// No more data. break.
		
		for(int i=0;i<ulNumRead;i++ )
			csNote += cTemp[i];
	}

	::CloseHandle(m_hComm);
	m_hComm = NULL;

	//
	csManualContactNote = csNote;

	return csManualContactNote;
}

// GDIPlus
int CFunction::GetEncoderClsid(const WCHAR* format, CLSID* pClsid)   
{   
    UINT num = 0;                     // number of image encoders   
    UINT size = 0;                   // size of the image encoder array in bytes   
    ImageCodecInfo* pImageCodecInfo = NULL;   
    GetImageEncodersSize(&num, &size);   
    if(size == 0)   
        return -1;     //   Failure 
    
    pImageCodecInfo = (ImageCodecInfo*)(malloc(size));   
    if(pImageCodecInfo == NULL)   
        return -1;     //   Failure   
    
    GetImageEncoders(num, size, pImageCodecInfo);   
    for(UINT j = 0; j < num; ++j)   
    {   
        if( wcscmp(pImageCodecInfo[j].MimeType, format) == 0 )   
        {   
            *pClsid = pImageCodecInfo[j].Clsid;   
            free(pImageCodecInfo);   
            return j;     //   Success   
        }           
    }
	
    free(pImageCodecInfo);

    return -1;
	//   Failure   
}

Status CFunction::SaveFile(Bitmap* pImage, const wchar_t* pFileName)//
{
    EncoderParameters encoderParameters;
    CLSID jpgClsid;

	GetEncoderClsid(L"image/jpeg", &jpgClsid);

    encoderParameters.Count = 1;
    encoderParameters.Parameter[0].Guid = EncoderQuality;
    encoderParameters.Parameter[0].Type = EncoderParameterValueTypeLong;
    encoderParameters.Parameter[0].NumberOfValues = 1;

    // Save the image as a JPEG with quality level 100.
    ULONG             quality;
    quality = 100;
    encoderParameters.Parameter[0].Value = &quality;
    Status status = pImage->Save(pFileName, &jpgClsid, &encoderParameters);
    if (status != Ok) 
    {
        wprintf(L"%d Attempt to save %s failed.\n", status, pFileName);

		//
		CString csMsg = _T("");
		csMsg.Format("%d Attempt to save %s failed.(%s)\n", status, pFileName, GetStatusValue(status));
		VisionMessage( csMsg );
    }

	return status;
}

void CFunction::ConvertFile(CString csSourceBmp, CString csDestionJpg)
{
	Bitmap newbitmap(csSourceBmp.AllocSysString());
	const unsigned short *pFileName=csDestionJpg.AllocSysString();
	Status status = SaveFile(&newbitmap,pFileName );
}
void CFunction::VisionMessage(CString csMsg)
{
	csMsg.TrimLeft();
	csMsg.TrimRight();

	//
	TRACE( csMsg );

	//
	f.CWinMessage( csMsg, theApp.enDArm );
}
CString CFunction::GetStatusValue(Status status)
{
  if( status == Ok )
	  return "Ok";
  if( status == GenericError )
	  return "GenericError";
  if( status == InvalidParameter )
	  return "InvalidParameter";
  if( status == OutOfMemory )
	  return "OutOfMemory";
  if( status == ObjectBusy )
	  return "ObjectBusy";
  if( status == InsufficientBuffer )
	  return "InsufficientBuffer";
  if( status == NotImplemented )
	  return "NotImplemented";
  if( status == Win32Error )
	  return "Win32Error";
  if( status == WrongState )
	  return "WrongState";
  if( status == Aborted )
	  return "Aborted";
  if( status == FileNotFound )
	  return "FileNotFound";
  if( status == ValueOverflow )
	  return "ValueOverflow";
  if( status == AccessDenied )
	  return "AccessDenied";
  if( status == UnknownImageFormat )
	  return "UnknownImageFormat";
  if( status == FontFamilyNotFound )
	  return "FontFamilyNotFound";
  if( status == FontStyleNotFound )
	  return "FontStyleNotFound";
  if( status == NotTrueTypeFont )
	  return "NotTrueTypeFont";
  if( status == UnsupportedGdiplusVersion )
	  return "UnsupportedGdiplusVersion";
  if( status == GdiplusNotInitialized )
	  return "GdiplusNotInitialized";
//  if( status == PropertyNotFound )
//	  return "PropertyNotFound";
//  if( status == PropertyNotSupported )
//	  return "PropertyNotSupported";
//  if( status == ProfileNotFound )
//	  return "ProfileNotFound";

  return "No Define";
}
void CFunction::InitSLTProtocolHelp()
{
	GetSLTProtocolHelp();
}
bool CFunction::GetSLTProtocolHelp()
{
	CString csNote = _T("");

	// Summary Report 
	CString csFile = _T("");
	csFile = m.FilePath.SLTProtocolNotePath;

	unsigned char cTemp[1001] = {0};
	unsigned long ulNumRead = 0;
	HANDLE	m_hComm = NULL;

	m_hComm = CreateFile (  csFile,// Pointer to the name of the port
		GENERIC_READ | GENERIC_WRITE,
		// Access (read/write) mode
		0,            // Share mode
		NULL,         // Pointer to the security attribute
		OPEN_EXISTING,// How to open the serial port
		0,            // Port attributes
		NULL);        // Handle to port with attribute

	while(1)
	{
		::ReadFile(m_hComm, cTemp, sizeof(cTemp), &ulNumRead, NULL);
		if(ulNumRead == 0)
			break;
		// No more data. break.
		
		for(int i=0;i<ulNumRead;i++ )
			csNote += cTemp[i];
	}

	::CloseHandle(m_hComm);
	m_hComm = NULL;

	// Show Data
	csNote.TrimLeft(); csNote.TrimRight();
	if( csNote != "" )
		return true;

	return false;
}
void CFunction::RemoteMessage(int iCode)
{
	tagErrorMsg e = GetErrorMsg(iCode);
	if(m.m_TestInterface.m_bRemoteMode)
	{
		if(m.m_TestInterface.m_bRemoteSendEvent)		
		{
			m.m_TestInterface.SetErrorMessage(iCode, e.Eng);
		}
	}
}
void CFunction::RemoteSeCoordnationInitial()
{
	m.m_TestInterface.RequestCoordnationMissionInitial();
}
void CFunction::RemoteSetCoordnationDone()
{
	m.m_TestInterface.SetCoordnationDone();
}
void CFunction::RemoteSetCoordnationReturnDone()
{
	m.m_TestInterface.SetCoordnationReturnDone();
}
void CFunction::RemoteSetStateInitialDone()
{
	m.m_TestInterface.SetStateInitialDone();
}
void CFunction::RemoteSetStateRetryDone()
{
	m.m_TestInterface.SetStateRetryDone();
}
void CFunction::RemoteSetStateSkipDone()
{
	m.m_TestInterface.SetStateSkipDone();
}
void CFunction::RemoteSetStateOneCycleDone()
{
	m.m_TestInterface.SetStateOneCycleDone();
}
void CFunction::RemoteSetStateStopDone()
{
	m.m_TestInterface.SetStateStopDone();
}
void CFunction::RemoteSetStateResetDone()
{
	m.m_TestInterface.SetStateResetDone();
}
void CFunction::RemoteSetStateErrorCtrl()
{
	m.m_TestInterface.SetStateErrorCtrlDone();
}
void CFunction::RemoteSetStateError()
{
	m.m_TestInterface.SetStateError();
}
void CFunction::RemoteSetStatus(int iStatus, int iCode)
{
	m.m_TestInterface.SetStatus(iStatus, iCode);
}

void CFunction::RemoteSendTestEvent(long TestEvent)
{
	CString csMsg = _T("");
	if(m.m_TestInterface.m_bRemoteMode) // 有連線才傳資訊
	{
		if(TestEvent == enSOT)
			csMsg.Format("<<*%%TESTEVENT%%%s>>",m.m_DeviceInfo.csDeviceID);
		else if(TestEvent == enLotStart)
			csMsg.Format("<<*%%TESTEVENT%%LOTSTART>>");
		else if(TestEvent == enLotDone)
			csMsg.Format("<<*%%TESTEVENT%%LOTDONE>>");
		else//Test Event Idle
			csMsg.Format("<<*%%TESTEVENT%%NAK>>");
		//儲存到Array 
		m.m_TestInterface.AddReplyCmd(csMsg);
	}
}

void CFunction::LiveReflash()
{
	if( theApp.m_pWndVisionSetup == NULL )
		return;
	
	CString live = "";
	
	// 將功能切給 CCD 一般模式的表單, 與 CCD Orc 模式的表單
	if( theApp.m_pWndVisionSetup->GetSafeHwnd() != NULL )
	{
		::SendMessage(theApp.m_pWndVisionSetup->GetSafeHwnd(), 
			WM_CCD_LIVE, (WPARAM)&live , (LPARAM)&live );
	}
	
	if( theApp.m_pWndVisionOrcSetup->GetSafeHwnd() != NULL )
	{
		::SendMessage(theApp.m_pWndVisionOrcSetup->GetSafeHwnd(), 
			WM_CCD_LIVE, (WPARAM)&live , (LPARAM)&live );
	}
}

static CMutex CCDMutexLog;
void CFunction::CCDLog(CString csLog)
{
	CSingleLock Lock(&CCDMutexLog);
	Lock.Lock();
	
	CString cs;
	CString cstime;
	CTime time = CTime::GetCurrentTime();
	cs.Format("%s, %s\r\n", time.Format("%m/%d %H:%M:%S"), csLog);
	cstime.Format("cs %s",time.Format("%y-%m-%d"));
	
	CFile file;
	
	file.Open(".\\Log\\CCD_"+cstime+".txt", CFile::modeCreate | CFile::modeWrite
		| CFile::modeNoTruncate | CFile::shareDenyNone, NULL);
	
	file.SeekToEnd();
	
	file.Write(cs.GetBuffer(0), cs.GetLength());
	file.Close();
	
	Lock.Unlock();
}

void CFunction::LoadSocketPatternSetting()
{
	CString csFile;
	csFile = m.FilePath.SocketImagePath + m.UI.SocketPatternName + "\\" + _ScoketSettingInfo;
	
	f.GetSetting(csFile, "Source Image", "X",			m.CSC.iMatchROIX );
	f.GetSetting(csFile, "Source Image", "Y",			m.CSC.iMatchROIY );
	f.GetSetting(csFile, "Source Image", "Width",		m.CSC.iMatchWidth );
	f.GetSetting(csFile, "Source Image", "Height",		m.CSC.iMatchHeight );
	f.GetSetting(csFile, "Source Image", "Score",		m.CSC.dMatchMinScore );
//Jerome Add 20140709
	csFile = m.FilePath.CCDImagePath + m.UI.Pin1PatternName + "\\" + _ScoketSettingInfo;
	f.GetSetting(csFile, "Source Image", "X",			m.CCDPin1.iMatchROIX );
	f.GetSetting(csFile, "Source Image", "Y",			m.CCDPin1.iMatchROIY );
	f.GetSetting(csFile, "Source Image", "Width",		m.CCDPin1.iMatchWidth );
	f.GetSetting(csFile, "Source Image", "Height",		m.CCDPin1.iMatchHeight );
	f.GetSetting(csFile, "Source Image", "Score",		m.CCDPin1.dMatchMinScore );
	
}
void CFunction::LoadVisionProfile()
{
	if( m.Setting.m_bCCD == 1 && m.TraySpec.VisionPatternName != "" )
		m.CCD.Load(m.TraySpec.VisionPatternName);
	else
		; // No Enable CCD
}
bool CFunction::InitCCDSocket()
{
	// 建立相關目錄
	AutoCreateFolder( m.FilePath.ImagePath );
	AutoCreateFolder( m.FilePath.SocketImagePath );
	
	//
	bool bInitCCDSocketOK = true;
	
	//
	int iCCDCount = 0;
	iCCDCount = m.m_VisionMatch.UpdateCameraList();
	if( iCCDCount > 0 )
	{
		if( m.m_VisionMatch.Open(m.m_CCDSocketControl.iCCDUse) )
		{
			CString csMsg = _T("");
			csMsg = "Open Socket CCD Success";
			f.DMsg.DMsg( csMsg );
		}
		else
		{
			// 
			CString csMsg = _T("");
			csMsg.Format("Open Socket CCD Fail.");
			bInitCCDSocketOK = false;
			
			//
			f.DMsg.DMsg( csMsg + _DMsgMark, false );
			if( m.Setting.m_bEnableProgramInitialStart == 0 )
				AfxMessageBox( csMsg );
		}
	}
	else
	{
		// 找不到任何一支 CCD
		CString csMsg = _T("");
		csMsg.Format("Can not Find Any Socket CCD, Please re-install Socket CCD and Re-Open 3111 S/W.!.");
		bInitCCDSocketOK = false;
		
		//
		f.DMsg.DMsg( csMsg + _DMsgMark, false );
		if( m.Setting.m_bEnableProgramInitialStart == 0 )
			AfxMessageBox( csMsg );
	}
	
	return bInitCCDSocketOK;
}

bool CFunction::InitCCDPin1()
{
	// 建立相關目錄
	AutoCreateFolder( m.FilePath.ImagePath );
	AutoCreateFolder( m.FilePath.CCDImagePath);
	//
	bool bInitCCDPin1OK = true;
	//
//	int iCCDCount = 0;
// 	iCCDCount = m.m_VisionMatch.UpdateCameraList();
// 	if( iCCDCount > 0 ){
		if( m.m_VisionMatch.Open(m.m_CCDPin1Control.iCCDUse) ){
			CString csMsg = _T("");
			csMsg = "Open Pin1 CCD Success";
			f.DMsg.DMsg( csMsg );
		}
		else{
			// 
			CString csMsg = _T("");
			csMsg.Format("Open Pin1 CCD Fail.");
			bInitCCDPin1OK = false;
			//
			f.DMsg.DMsg( csMsg + _DMsgMark, false );
			if( m.Setting.m_bEnableProgramInitialStart == 0 )
				AfxMessageBox( csMsg );
		}
//	}
// 	else{
// 		// 找不到任何一支 CCD
// 		CString csMsg = _T("");
// 		csMsg.Format("Can not Find Any Pin1 CCD, Please re-install Pin1 CCD and Re-Open 3111 S/W.!.");
// 		bInitCCDPin1OK = false;
// 		
// 		//
// 		f.DMsg.DMsg( csMsg + _DMsgMark, false );
// 		if( m.Setting.m_bEnableProgramInitialStart == 0 )
// 			AfxMessageBox( csMsg );
// 	}	
	return bInitCCDPin1OK;
}