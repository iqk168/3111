#if !defined(AFX_THTESTER_H__331D3933_78B7_4B26_B275_972DAB208C5F__INCLUDED_)
#define AFX_THTESTER_H__331D3933_78B7_4B26_B275_972DAB208C5F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ThTester.h : header file
//

// Rs232
#include "Interface.h"

// Tcpip
#include "InterfaceTcp.h"

#include <afxtempl.h>

/////////////////////////////////////////////////////////////////////////////
// CThTester thread

class CThTester : public CWinThread
{	
	DECLARE_DYNCREATE(CThTester)
public:
	virtual ~CThTester();	
	CThTester();           // protected constructor used by dynamic creation

	enum Status{
		enIdle			= 0x10,		// Idle
		enInitialize	= 0x20,		// Initial 

		// Cycle 
		enTestStart		= 0x210,	// Start Testing

		// SLT
		enSLTTestStart	= 0x310,	// SLT Test Start
		enSLTTesting	= 0x320,	// SLT Testing 
		enSLTTestEnd	= 0x330,	// SLT Test End

		// FT
		enFTTestStart	= 0x410,	// FT Test Start
		enFTTesting		= 0x420,	// FT Testing
		enFTTestEnd		= 0x430,	// FT Test End
	};

	long m_iRunError;	// It is for motor error, If Motor function fail.

	int  m_bStatus;

	void Running();
	void CheckRestart();
	void NextStatus();

	void InitialStart();
	void Initialize();
	bool IsInitialError();

	bool m_bInitialized;
	bool m_bInitialRequest;

	void Wait(int msec);

	int TestTime;	//  代刚Ω计, 璸衡琌代

	tagTestLog TesterLog;
	void ClearTesterLog();	

	//
	bool InitValue();

	// Yield Control
	int *m_YieldLimit;
	void ReSizeYieldLimit(int LimitSize);

	// SLT Testing
	void SLTShowTesting();
	void SLTTesting();
	void SLTResultInfo();

	// FT Testing
	void FTShowTesting();
	void FTShowSendStartDelay();
	void FTSetWaitSendStartDelay( bool bIsWait );
	bool FTGetWaitSendStartDelay();
	bool m_bIsWaitSendStartDelay;
	bool WaitSendStartDelay(double dSecs);
	void FTTesting();
	void FTResultInfo();
	
	// 盢代刚丁э 陪ボ
	int TestStartTime;										// 秨﹍代刚丁
	double TestOldTime;										// Ω计		
	double TestInOldTime;									// 糤秖丁			

	void InitTestStartTime();
	void ResetTestTime();									// 代刚玡盢代刚睲 0 
	void ResetFinalTestTime();								// 陪ボ Site Setting 程计
	void UpdateTestTime(int iStartTime, double iOldTime );	// 代刚丁
	void WaitForDummyTest(int mesc);

	//
	void UpdateTestedIC();

	// 硄癟ノ代刚 (Τ硄癟ぃ北 IO )
	CString SLTTcpIpTesting();

public:
	bool Init();

public:
	////////////////////////////////////////
	// RS232 Interface Communcation function.
	bool m_bSeralOpen;
	CInterface m_Interface;
	CString RS232Testing();
	void SendTelegram(CString cs);
	bool InitRs232();

	bool CloseRs232();

public:
	////////////////////////////////////////
	// TCPIP Interface Communcation function.
	bool InitTcpip();
	CString TcpTesting();

public:
	////////////////////////////////////////
	// Pass/Faill Communcation function.
	int GetPassFailValue(CString csBin); // 1 For Pass, 0 For Fail

public:
	void ManualTestMessage(CString csMsg = _T(""));

	// 1.0Af
	void RemoteFunction(CString csRemoteCommand);
	
	// 1.0Af
	void RepeatTrayCurrentTestIC();
	void RepeatTrayCurrentTestICClear();

protected:

// Attributes
public:

// Operations
public:
	void FTTestingRemoteMode();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CThTester)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CThTester)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_THTESTER_H__331D3933_78B7_4B26_B275_972DAB208C5F__INCLUDED_)
