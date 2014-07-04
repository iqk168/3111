#if !defined(AFX_THINSERTER_H__79E7115A_E390_420B_A302_700FE66B8C31__INCLUDED_)
#define AFX_THINSERTER_H__79E7115A_E390_420B_A302_700FE66B8C31__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ThInserter.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CThInserter thread

class CThInserter : public CWinThread
{
	DECLARE_DYNCREATE(CThInserter)
public:
	virtual ~CThInserter();	
	CThInserter();           // protected constructor used by dynamic creation

	enum Status{
		enIdle						= 0x10,		// Idle
		enInitialize				= 0x20,		// Initial

		//
		enShuttleHome				= 0x30,		// Shuttle move to home
		enShuttleHomeStandy			= 0x40,		// Shuttle move to home standy
		enShuttleRestart			= 0x50,		// Test Pick From Socket Fail. Re-set it, ask Arm move to input again
		enShuttleRestartDrop		= 0x60,		// Test Down Place to Socket. But IC Missing

		// 
		enShuttleInput				= 0x110,	// Shuttle move to input
		enShuttleInputJam			= 0x120,	// Shuttle move to input, and check jam again
		enShutlleInputEnd			= 0x130,	// Shuttle move to input end

		//
		enTestSitePickForVacc		= 0x210,	// Test site down to pick
		enTestSiteVaccForUp			= 0x220,	// Test site turn on the vacc
		enTestSiteUpForContact		= 0x230,	// Test site up for contact
		enShuttleHomeForContact		= 0x240,	// Shuttle move to home
		enTestSiteDownForContact	= 0x250,	// Test site down to place ic to socket (fast)
		enTestSiteToDrop			= 0x260,	// Test site drop mode
		enTestSiteDropDevice		= 0x270,	// Test site drop mode blow
		enTestSiteContact			= 0x280,	// Test site contact 
		enTestStteContactEnd		= 0x290,	// Test site contact end

		///////////////////////////////
		// Test Site / Drop Alarm
		enTestSiteICDropBackHome	= 0x910,	// Test site down to drop or contact position, but IC drop
		enTestSiteICDropAlarm		= 0x929,	// Test site back home, alarm it

		///////////////////////////////
		// Test Site / Remote Control
		enTestSiteRemoteCtrl		= 0x610,	// Test site in remote control
		enTestSiteRemoteStandy		= 0x620,	// Test site in remote control standby
		enTestSiteRemoteRelease		= 0x630,	// Test site in remote control Release

		///////////////////////////////
		// Test Site / Wait Heater
		enTestSiteHeaterStart		= 0x710,	// Test Site Wait Heater
		enTestSiteHeaterWait		= 0x720,	// Test Site Wait 
		enTestSiteHeaterEnd			= 0x730,	// Test Site Wait End

		///////////////////////////////
		// Test Site / Testing
		enTestSiteTestStart			= 0x410,	// Test Start
		enTestSiteTesting			= 0x420,	// Testing 
		enTestSiteTestEnd			= 0x430,	// Test End
		enTestSiteYield				= 0x440,	// Test Yield Control

		///////////////////////////////
		// Test Site / Output 
		enTestSiteVaccStart			= 0x510,	// Test Site ready turn on the vacc
		enTestSiteVacc				= 0x520,	// Test Site turn on the vacc
		enTestSiteVaccEnd			= 0x530,	// Test Site turn on the vacc
		enTestSiteUpForPlace		= 0x540,	// Test Site up for place ic to shuttle output 
		enShuttleOutput				= 0x550,	// Shuttle move to pick, test site can put ic to shuttle 
		enTestSitePlace				= 0x560,	// Test Site down to place IC to shuttle 
		enTestSitePlaceBlow			= 0x570,	// Test Site turn on the blow 
		enTestSiteUpForOut			= 0x580,	// Test Up for shuttle move home, Arm can pick ic from shuttle
		enShuttleHomeForOutput		= 0x590,	// Shuttle move to home
		
		// Test Site Pick IC Retry
		enTestSiteReDownToPick		= 0x710,	// Test Site Down To Pick (Retry)
		enTestSiteReVacc			= 0x720,	// Test Site Down To Pick, Turn in the Vacc
		enTestSiteReVaccEnd			= 0x730,	// Test Site Down To Pick OK.		

		///////////////////////////////
		// Test Site CCD Socket 
		enTestSiteCCDSocketStart	= 0x310,	// CCD Socket Start
		enTestSiteCCDSocketGrab		= 0x320,	// CCD Grab
		enTestSiteCCDSocketMatch	= 0x330,	// CCD Match
		enTestSiteCCDSocketMatchEnd	= 0x340,	// CCD Match End (Check Error or not )
		enTestSiteCCDSocketEnd		= 0x350,	// CCD Socket End

		///////////////////////////////
		// Test Site SLT Protocol
		enTestSiteRemoteSendMsg		= 0x810,	// SLT Protocol, Wait
		enTestSiteRemoteWaitCmd		= 0x820,	// STL Protocol, Wait Command
		
		///////////////////////////////	
		// Error status
		enShuttleHomeError			= 0x1110,	// Shuttle move to home fail	
		enShuttleInputError			= 0x1120,	// Shuttle move to pick fail
		enTestSiteUpForContactError	= 0x1130,	// Test Site Pick IC fail ( pick form shuttle input )
		enShuttleHomeForContactError= 0x1140,	// Test Site ready move to socket, shuttle move to home fail.
		enShuttleOutputError		= 0x1150,	// Shuttle move to place fail
		enShuttleHomeForOutputError	= 0x1160,	// Shuttle move to home fail
		enTestSiteUpForPlaceError	= 0x1170,	// Test Site Pick IC fail ( pick form socket )
		enShuttleInputJamError		= 0x1180,	// Shuttle move to input, then check jam fail
		enTestSiteICDropError		= 0x1190,	// Test Site IC Drop

		///////////////////////////////	
		// Error status (Yield Conteol)
		enTesYieldContFailError		= 0x2110,	
		enTesYieldYieldRateError	= 0x2120,
	};

	long m_iRunError;		// It is for motor error, If Motor function fail.

	int  m_bStatus;

	bool CheckTSArmZIC(unsigned char* Vacc, unsigned char* pSensor, long dTimeout);
	void Running();
	void CheckRestart();
	void NextStatus();
	bool IsPause();

	void InitialStart();
	void Initialize();
	bool IsInitialError(long err, long id);

	bool m_bInitialized;
	bool m_bInitialRequest;

	tagTestLog TestSiteLog;
	void ClearTestSiteLog();
	// Note : When Test Site Get TestResult. We store the Test Result in this Member.
	// When TestSite Put IC in Shuttle OUT. We need copy Member to Shuttle Member.
	// When Arm Pick IC in Shuttle OUT. We need copy this Member to Arm.
	// Note : Every time copy value. we have to clear the value.( set to default. )

	bool ShuttleMovePickPlace();	// Shuttle move to testSite pick / place position
	bool ShuttleMoveHome();			// Shuttle move to arm pick / place position
	bool CheckShuttlePickPlaceOK();	// Check shuttle move to pick / place position ok
	bool CheckShuttleHomeOK();		// Check shuttle move to home / pick / place position ok
	

	//
	bool m_TSZWithIC;		

	//
	bool Vacc(unsigned char* Vacc, unsigned char* pSensor, double dTimeout );
	bool Blow(unsigned char* Vacc, unsigned char* Puff, unsigned char* pSensor, double dTimeout );
	bool CheckTSZVaccSensor();
	bool VaccOff(unsigned char* Vacc);

	// UPH
	void UPHTSDataAdd();

public:
	// Remote
	void RemoteControlMessageICReady();
	void RemoteControlMessageReleaseIC();
	void RemoteControlMessageArmReady();

public:
	// Heater
	void InitHeaterValue();
	void SetHeaterStart();
	bool WaitHeaterSoakOK();
	void ClearHeaterValue();
	tagTsHeaterSoak m_TsSoak;

public:
	// Yield Control
	bool IsYieldPassFail(CString csCode);
	bool IsYieldContinueFail();	// 
	bool IsYieldFailRateFail(); //
	bool IsYieldRetestNeed();
	void ClearYieldControlTested();

public:
	void SaveTSCounter();

public:
	// 1.0Ab
	// Shuttle Input, Check Jam
	bool CheckShuttleInputJam();

	// 1.0Ab
	bool ShuttleMoveLogJam();

public:
	// 1.0Ac
	void InitTorqueInitialLoad();

	// 1.0Ah
	void InitICDropInd();
	void SetICDropInd(bool bInd);
	bool GetICDropInd();
	bool ICDropInd;

	// 1.0Ah
	void InitShuttleStatus();

	// 1.0 Aj
	bool m_bMissionOnTheGo;
	void InitialMissionOnTheGo();
	void SetRemoteCoordRequest( bool bMissionGo = false );
	bool GetRemoteCoordRequest();
	void SetRemoteCoordRequestReturn( bool bMissionGo = false );
	bool GetRemoteCoordRequestReturn();

	// Debug
	int GetThreadMotionStatus();

	// 1.0 Av
	long m_lRemoteStatus;	//»·ºÝ»»±±Insertª¬ºA¥Î

protected:

// Attributes
public:

// Operations
public:


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CThInserter)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CThInserter)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_THINSERTER_H__79E7115A_E390_420B_A302_700FE66B8C31__INCLUDED_)
