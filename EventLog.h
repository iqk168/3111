// EventLog.h: interface for the CEventLog class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_EVENTLOG_H__10DD2E1C_F9CB_4C20_B3BF_AD4158417469__INCLUDED_)
#define AFX_EVENTLOG_H__10DD2E1C_F9CB_4C20_B3BF_AD4158417469__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <afxmt.h>

class CEventLog  
{
public:
	CEventLog();
	virtual ~CEventLog();

	int iNowShowMonth;
	void AddEvent(long Code);
	int ReadEvent(tagErrorParam *Log, int iShowMonth);
	BOOL CheckEventTime();

	// Debug
	void AddLogEvent(CString msg);

	CMutex EventMutex;
};

#endif // !defined(AFX_EVENTLOG_H__10DD2E1C_F9CB_4C20_B3BF_AD4158417469__INCLUDED_)
