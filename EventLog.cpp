// EventLog.cpp: implementation of the CEventLog class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "deer.h"
#include "EventLog.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CEventLog::CEventLog()
{

}

CEventLog::~CEventLog()
{

}

void CEventLog::AddLogEvent(CString msg)
{
	CString     csFilename;
	CStdioFile  file;
	CSingleLock lock(&EventMutex);
	
	lock.Lock();
	
	CTime time = CTime::GetCurrentTime();
	csFilename.Format( _T(".\\Log\\%d_%d_Log.log"), time.GetYear(), time.GetMonth());
	if ( file.Open( csFilename, CFile::modeCreate | CFile::modeWrite | CFile::shareDenyNone | CFile::modeNoTruncate, NULL) != 0)
	{       
		CString constBuf;
		constBuf.Format("%d.%d.%d.\t", time.GetHour(), time.GetMinute(),time.GetSecond() );
		constBuf = constBuf + msg;
		file.SeekToEnd();
		file.WriteString( constBuf + _T("\n") );
		file.Close();
	}
	
	lock.Unlock();

}

void CEventLog::AddEvent(long Code)
{
	CSingleLock lock(&EventMutex);
	lock.Lock();

	CString cs = _T("");
	CFile file;
	CString csFile = _T("");

	CTime time = CTime::GetCurrentTime();
	csFile.Format(".\\Log\\%d_%d.log", time.GetYear(), time.GetMonth());
	if(file.Open(csFile, CFile::modeCreate | CFile::modeWrite | CFile::shareDenyNone
		| CFile::modeNoTruncate, NULL) != 0)
	{
		cs.Format("%d %d\r\n", time.GetTime(), Code);
		file.SeekToEnd();
		file.Write(cs.GetBuffer(0), cs.GetLength());
		file.Close();
	}
	/*
	if(theApp.m_DlgRun.GetSafeHwnd() != NULL)
		::SendMessage(theApp.m_DlgRun.GetSafeHwnd(), WM_COMMAND, 
			MAKEWPARAM(ID_ADD_EVENT, 0), NULL);
	*/
	lock.Unlock();

	// 1.0Ah
	// Send Event Report to tester
	tagErrorMsg e = f.GetErrorMsg(Code);
	// 分層級不會Alarm
	if(e.Alarm)
	f.RemoteErrorMessage(Code);
		else
	f.RemoteSendEvent(Code);
	// 會Alarm
}
// 讀取 Event log, 可由 iShowMonth 來控制顯示, 最大值為本月與前月份 Event Log
int CEventLog::ReadEvent(tagErrorParam *Log, int iShowMonth)
{
	iNowShowMonth = iShowMonth;
	int iCount = 0;
	CTime time = CTime::GetCurrentTime();
	CString cs;
	int y = time.GetYear();
	int m = time.GetMonth();
	if(m == 1)
		cs.Format(".\\Log\\%d_12", y-1);
	else
		cs.Format(".\\Log\\%d_%d.log", y, m-1);
	
	CFile file;
	bool bFull = false;

	if(iShowMonth >= 2)
	{
		if(file.Open(cs, CFile::modeRead | CFile::shareDenyNone, NULL) != 0)
		{
			file.SeekToBegin();
			CArchive ar(&file, CArchive::load);
			CString cs;
			for(int i=0; i<_Max_Event; i++)
			{
				ar.ReadString(cs);
				int k = cs.Find(" ", 0);
				if(k == -1) break;
				Log[iCount].Time = atoi(cs.Left(k));
				Log[iCount].Code = atoi(cs.Right(cs.GetLength() - k));
				iCount++;
			}
			ar.Close();
			file.Close();
		}
		
		// Event 超過數量, 覆蓋舊的 Event
		if(iCount >= _Max_Event)
		{
			bFull = true;
			iCount = 0;
		}
	}

	cs.Format(".\\Log\\%d_%d.log", y, m);
	if(file.Open(cs, CFile::modeRead | CFile::shareDenyNone, NULL) != 0)
	{
		file.SeekToBegin();
		CArchive ar(&file, CArchive::load);
		CString cs;
		for(int i=0; i<_Max_Event; i++)
		{
			ar.ReadString(cs);			

			int k = cs.Find(" ", 0);
			if(k == -1) 
			{
				// 如果有人打開檔案按下空白
				// 會造成資料讀取不完全
				break;
			}
			Log[iCount].Time = atoi(cs.Left(k));
			Log[iCount].Code = atoi(cs.Right(cs.GetLength() - k));
			iCount++;
			// Event 超過數量, 覆蓋舊的 Event
			if(iCount >= _Max_Event)
			{
				bFull = true;
				iCount = 0;
			}
		}
		ar.Close();
		file.Close();
	}
	if(bFull)
		iCount = _Max_Event;

	return iCount;
}

BOOL CEventLog::CheckEventTime()
{

	return FALSE;
}
