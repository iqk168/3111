#if !defined(AFX_THARM_H__AAD642F9_E72E_45EE_9886_8D0DFA0F1C57__INCLUDED_)
#define AFX_THARM_H__AAD642F9_E72E_45EE_9886_8D0DFA0F1C57__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ThArm.h : header file
//


/////////////////////////////////////////////////////////////////////////////
// CThArm thread
class CThArm : public CWinThread
{	
	DECLARE_DYNCREATE(CThArm)
public:
	virtual ~CThArm();
	CThArm();           // protected constructor used by dynamic creation

	enum Status{
		enIdle			= 0x10,			// Idle 
		enInitialize	= 0x20,			// Initial

		// Cycle
		///////////////////////////////
		// Input Get IC
		enToInputCheckTray						= 0x100,	// Arm XY check input tray before move to input stack
		enToInput								= 0x110,	// Arm XY move to Input stack
		enPickIC								= 0x120,	// Arm Z down to pick IC
		enVacuumStart							= 0x130,	// Arm Z ready to turn on Vacc
		enVacuum								= 0x140,	// Arm Z turn on Vacc
		enVacuumEnd								= 0x150,	// Arm Z turn on Vacc and check pick ok or not.

		enToHome								= 0x160,	// Arm Z pick IC ok, Arm Z up to home
		enToHomeEnd								= 0x170,	// Arm Z back to home ok, ( check go to rotator or shuttle in)
		
		///////////////////////////////
		// Rotator Input
		enRotatorInCheckSetting					= 0x210,	// Rotator check rotator setting.
		enRotatorInRamin						= 0x220,	// After check rotator, Make sure rotator have no IC
		enRotatorInGoToRotator					= 0x230,	// Arm XY move to rotator position
		enRotatorInCheckReadyForInput			= 0x240,	// Rotator turn for input IC		
		enRotatorInBlowDown						= 0x250,	// Arm Z down to place IC
		enRotatorInBlow							= 0x260,	// Arm Z turn on blow 
		enRotatorInBlowUp						= 0x270,	// Arm Z place IC to Rotator ok, Arm Z up 
		enRotatorInCheckJamForBlow				= 0x280,	// After IC Place to Rotator. Check Jam	
		enRotatorInTurn							= 0x290,	// Rotator change IC pin1 
		enRotatorInCheckJamForPick				= 0x2a0,	// Before Arm Z Pick IC	check Jam
		enRotatorInPickDown						= 0x2b0,	// Rotator change ok, Arm Z down to pick IC
		enRotatorInPick							= 0x2c0,	// Arm Z Vacc turn on
		enRotatorInPickUp						= 0x2d0,	// Arm Z up  
		enRotatorInEnd							= 0x2e0,	// Rorator In complete. ( IC in ArmZ, ok go to shuttle )
		enRotatorInPickReset					= 0x2f0,	// Rotator Pick IC Fail
		
		///////////////////////////////
		// Shuttle (Input)
		enToShuttle								= 0x310,	// Arm XY move to shuttle 
		enShuttlePlaceIC						= 0x320,	// Arm Z down to place IC
		enShuttleBlow							= 0x330,	// Arm Z turn on the blow
		enShuttleUp								= 0x340,	// Arm Z up
		enShuttleCheckJam						= 0x350,	// Arm Shuttle Check Jam
		enShuttleCheckJamOK						= 0x360,	// Arm Shuttle Check Jam OK
		enShuttleDoubleCheckJam					= 0x370,	// Arm Shuttle Check Double Jam
		enShuttleJamGoStandy					= 0x380,	// Arm Shuttle Move Standy

		///////////////////////////////
		// CCD Pin1 
		enShuttleCCDPin1Start					= 0x390,	// CCD Pin1
		enShuttleCCDPin1Grab					= 0x3a0,	// CCD Grab
		enShuttleCCDMatch						= 0x3b0,	// CCD Grab Match
		enShuttleCCDMatchEnd					= 0x3c0,	// CCD Grab Match complete.
		
		///////////////////////////////
		// Standy 
		enToStandyStart							= 0x400,	// Arm XY move to standy start
		enToStandy								= 0x410,	// Arm XY move to standy 
		enToStandyEnd							= 0x420,	// Arm XY move to standy OK
		enToStandyWait							= 0x430,	// Arm XY move to standy for output

		// Heater
		enHeaterWaitStableStart					= 0x510,	// Heater Wait Stable Start
		enHeaterWaitTemper						= 0x520,	// Heater Wait Temp
		enHeaterWaitStable						= 0x530,	// Heater Wait Stable
		enHeaterWaitStableEnd					= 0x540,	// Heater Wait Stable end

		///////////////////////////////
		// Rotator Output
		enRotatorOutCheckSetting				= 0x710,	// Rotator check rotator setting.
		enRotatorOutRamin						= 0x720,	// After check rotator, Make sure rotator have no IC
		enRotatorOutGotoRotator					= 0x730,	// Arm XY move to rotator
		enRotatorOutCheckReadyForOutput			= 0x740,	// Turn the Rotator, then Arm can place IC to rotator
		enRotatorOutBlowDown					= 0x750,	// Arm Z down to place IC
		enRotatorOutBlow						= 0x760,	// Arm Z down and turn on the blow 
		enRotatorOutBlowUp						= 0x770,	// Arm Z up
		enRotatorOutCheckJamForBlow				= 0x780,	// After place the IC, check Jam
		enRotatorOutTurn						= 0x790,	// Turn the rotator
		enRotatorOutCheckJamForPick				= 0x7a0,	// Before Arm Z Pick IC	check Jam
		enRotatorOutPickDown					= 0x7b0,	// Arm Z down to pick IC
		enRotatorOutPick						= 0x7c0,	// Arm Z turn on the Vacuum
		enRotatorOutPickUp						= 0x7d0,	// Arm Z up
		enRotatorOutPickEnd						= 0x7e0,	// Rotator Out complete ( IC in ArmZ, ok go to bining )
		enRotatorOutputReset					= 0x7f0,	// Rotator pick fail, adjust the offset, re-move the ArmXY

		///////////////////////////////
		// Shuttle (Output)
		enToShuttleOutput						= 0x910,	// Arm XY move to shuttle 
		enToShuttlePick							= 0x920,	// Arm Z down to pick
		enToShuttlePickVaccStart				= 0x930,	// Arm Z ready to turn on the vacc
		enToShuttlePickVacc						= 0x940,	// Arm Z turn on the vacc
		enToShuttlePickVaccEnd					= 0x950,	// Arm Z vacc end
		enToShuttleUpForOutput					= 0x960,	// Arm Z up for output 

		///////////////////////////////
		// Output Place IC
		// Bin
		enToOutputCheckFix						= 0x810,	// Check Fix1 
		enToOutput								= 0x820,	// Arm XY Move to Output area, ready to place IC
		enToOutputPlaceIC						= 0x830,	// Arm Z down to place IC
		enToOutputPlaceBlow						= 0x840,	// Arm Z turn on the Blow
		enToOutputHome							= 0x850,	// Arm up to home
		enToOutputHomeEnd						= 0x860,	// Arm up to home OK. ready to input again.
		enToOutputChangeTray					= 0x870,	// Change Tray, Clear Fix Tray
	
		///////////////////////////////	
		// Cycle Finish
		enCycleStandy							= 0xa10,	// Cycle Finish Stnady
		enCycleEnd								= 0xa20,	// Cycle Finish

		///////////////////////////////
		// CCD Arm Log Image
		enArmLogImageStart						= 0x7110,	// Image Log Arm Start
		enArmLogImageStable						= 0x7120,	// Image Log Arm, Wait Motor Stable
		enArmLogImageGrabMove					= 0x7130,	// Image Log Arm, Ready to grab image
		enArmLogImageDirectory					= 0x7140,	// Image Log Arm, Is Directory Exist
		enArmLogImageGrab						= 0x7150,	// Image Log Arm, Ready to grab image
		enArmLogImageSaveIage					= 0x7160,	// Image Log Arm, Save the Image
		enArmLogImageWaitStable					= 0x7170,	// Image Log Arm, Wait Motor Stable
		enArmLogImageEnd						= 0x7180,	// Image Log Arm End

		///////////////////////////////
		// Remote Control
		enRemoteControlWait						= 0x2110,	// Remote Control. Wait for Release IC.

		enRemoteControlToInput					= 0x2120,	// To Input Place IC
		enRemoteControlPlaceIC					= 0x2130,	// Arm Z down to place IC
		enRemoteControlBlow						= 0x2140,	// Blow
		enRemoteControlHome						= 0x2150,	// Home
		enRemoteControlHomeEnd					= 0x2160,	// Home End
		enRemoteControlWaitPick					= 0x2170,	// Wait Pick.

		///////////////////////////////
		// TS Remain IC
		enTSRemainICStart						= 0x3310,	// TS Remain IC Start
		enTSRemainICContactHome					= 0x3320,	// TS Remain IC Chamber Contact Move to Home
		enTSRemainICDryHome						= 0x3330,	// TS Remain IC Dry Shuttle Move to Home
		enTSRemainICTSDown						= 0x3340,	// TS Remain IC TS Down 
		enTSRemainICTSVaccOn					= 0x3350,	// TS Remain IC Turn IC
		enTSRemainICTSVaccEnd					= 0x3360,	// TS Remain IC Vacc End ( Check do we need to turn off Vacc )
		enTSRemainICTSUp						= 0x3370,	// TS Remain IC TS Up
		enTSRemainICCheck						= 0x3380,	// TS Remain IC Check Pass Or Fail
		enTSRemainICEnd							= 0x3390,	// TS Remain IC End..
		//

		///////////////////////////////
		// Repeat Tray / Input / Output Ctrl
		// Get IC
		enRepeatToInput							= 0x4110,	// Repeat tray change input coordnation	
		enRepeatPickIC							= 0x4120,	// Repeat tray arm z down to pick ic
		enRepeatVacc							= 0x4130,	// Repeat tray turn on the vacc
		enRepeatVaccEnd							= 0x4140,	// Repeat tray vacc end
		enRepeatInToHome						= 0x4150,	// Repeat tray arm z up form pick
		enRepeatInToHomeEnd						= 0x4160,	// Repeat tray arm z up home end
		enRepeatInToHomeEndEnd					= 0x4170,	// Repeat tray arm z up home end and check next status
		
		// Put IC
		enRepeatToOutput						= 0x5110,	// Repeat tray change output coordnation
		enRepeatPlacIC							= 0x5120,	// Repeat tray arm z down to place ic
		enRepeatBlow							= 0x5130,	// Repeat tray arm z turn on the blow
		enRepeatBlowEnd							= 0x5140,	// Repeat tray arm z blow end
		enRepeatOutToHome						= 0x5150,	// Repeat tray arm z up from place
		enRepeatOutToHomeEnd					= 0x5160,	// Repeat tray arm z up home end
		enRepeatOutToHomeEndEnd					= 0x5170,	// Repeat tray arm z up home end and check next status
		enRepeatOutTray2Clear					= 0x5180,	// Repeat tray clear fail tray full status
		enRepeatOutTray1Clear					= 0x5190,	// Repeat tray clear fail tray full status

		// Cycle Finish
		enRepeatCheckComplete					= 0x6110,	// Repeat tray check complete
		enRepeatCycleStandy						= 0x6120,	// Repeat tray arm xy move to standby
		enRepeatCycleFinish						= 0x6130,	// Repeat tray arm xy cycle finish

		// Remote, SLT Protocol
		// Input
		enRemoteProtocolInput					= 0x8110,	// SLT Protocol Input
		enRemoteProtocolPick					= 0x8120,	// SLT Protocol Pick IC
		enRemoteProtocolVacc					= 0x8130,	// SLT Protocol Vacc
		enRemoteProtocolVaccEnd					= 0x8140,	// SLT Protocol Vacc End
		enRemoteProtocolInHome					= 0x8150,	// SLT Protocol Arm Z Home
		enRemoteProtocolInHomeEnd				= 0x8160,	// SLT Protocol Arm Z Home End
		
		// Output
		enRemoteProtocolOutput					= 0x8170,	// SLT Protocol Output
		enRemoteProtocolPlace					= 0x8180,	// SLT Protocol Place IC
		enRemoteProtocolBlow					= 0x8190,	// SLT Protocol Blow
		enRemoteProtocolBlowEnd					= 0x81a0,	// SLT Protocol Blow End
		enRemoteProtocolOutHome					= 0x81b0,	// SLT Protocol Arm Z Homw
		enRemoteProtocolOutHomeEnd				= 0x81c0,	// SLT Protocol Arm Z Home End

		// Finish
		enRemoteStandy							= 0x81d0,	// SLT Protocol Arm move to stand by
		enRemoteEnd								= 0x81e0,	// SLT Protocol End

		///////////////////////////////	
		// Error status
		enRotatorInCheckReadyForInputError		= 0x1110,	
		enRotatorInCheckJamForBlowError			= 0x1120,
		enRotatorInCheckMissingForBlowError		= 0x1130,
		enRotatorInTurnError					= 0x1140,
		enRotatorInCheckMissingForPickError		= 0x1150,
		enRotatorInPickError					= 0x1160,
		enRotatorOutCheckReadyForOutputError	= 0x1170,
		enRotatorOutRaminError					= 0x1180,
		enRotatorOutCheckJamForBlowError		= 0x1190,
		enRotatorOutCheckMissingForBlowError	= 0x11a0,
		enRotatorOutTurnError					= 0x11b0,
		enRotatorOutCheckMissingForPickError	= 0x11c0,
		enRotatorOutPickError					= 0x11d0,

		//
		enToHomeEndError						= 0x1210,
		enToShuttleUpForOutputError				= 0x1220,
		enToOutputCheckFixError					= 0x1230,
		enToOutputError							= 0x1240,
		enInputTrayMissingError					= 0x1250,
		enShuttleCheckJamError					= 0x1260,

		// CCD Match Error
		enShuttleCCDMatchError					= 0x1310,

		// Remain IC Error
		enTSRemainICCheckError					= 0x2110,

		// Repeat Tray Error
		enRepeatInToHomeEndEndError				= 0x3110,
		enRepeatToOutput2FullError				= 0x3120,
		enRepeatToOutput1FullError				= 0x3130,

		// Remote Control Error
		enRemoteProtocolInHomeEndError			= 0x9110,
	};
	
	long m_iRunError;		// It is for motor error, If Motor function fail.	
	int  m_bStatus;

	bool m_bFix1TrayFull;	// It is for Fix1 Tray Full.

	void Running();
	void CheckRestart();
	void NextStatus();
	bool IsPause();

	void InitialStart();
	void Initialize();
	bool IsInitialError(long err, long id);

	void InitFlag();

	bool CheckArmZIC(unsigned char* Vacc, unsigned char* pSensor, long dTimeout);				// Initial Check Arm Z have IC or Not

	bool m_bInitialized;
	bool m_bInitialRequest;


	// Tray File
	bool m_bOK;				// if true. It mean RunLine OK, and Input Not EOF
	bool m_bOutOK;			// if true. It mean RunLine OK, and Output Not EOF

	// InPos
	bool RotatorNOK;		// if true. It mean Rotator InPos OK
	bool RotatorPOK;		// if true. It mean Rotator InPos OK

	// Auto Retry
	void InitAutoRetry();
	int m_lArmRetryCounter;

	//
	void ConventSiteCounter(int Stack);

	bool CheckFixExist();

	bool m_bInTrayMissingError;
	bool CheckInputExit();

	bool m_bTSRemainICEnable;

	bool CheckArmJam();

protected:

// Attributes
public:

// Operations
public:

	bool ManualVacc(unsigned char* Vacc, unsigned char* pSensor, double dTimeout = 5.5);


	// Cycle Using
	bool Vacc(unsigned char* Vacc, unsigned char* pSensor, double dTimeout = 5.5);
	bool Blow(unsigned char* Vacc, unsigned char* Puff, unsigned char* pSensor, double = 5.5 );
		
	bool RotatorN(unsigned char* Turn,	unsigned char* pSensor, unsigned char* nSensor, double dTimeout = 5.5 ); // -90
	bool RotatorP(unsigned char* Turn,	unsigned char* pSensor, unsigned char* nSensor, double dTimeout = 5.5 );	// 90
	bool RotatorCheckJam( unsigned char* pSensor );
	bool RotatoeICExist( unsigned char* pSensor );

	bool m_ZWithIC;	
	bool m_bInputEmpty;

	tagTestLog ArmLog;
	void ClearArmLog();

	double AutoRetryAdjustValue(int iCount);	// mm

	//
	bool CheckArmZVaccSensor();
	bool CheckDoubleArmZCheckVacc();

	//
	void RemoteControlMessageICReady();
	void RemoteControlMessageReleaseIC();
	void RemoteControlMessageArmReady();

	//
	void AutoInputTray();

public:
	bool m_TSRemainWithIC;
	// TS Remain IC
	bool TSRemainICVacc(unsigned char* Vacc, unsigned char* pSensor, double dTimeout = 5.5);
	bool TSRemainICDoubleCheck( unsigned char* pSensor );
	bool TSRemainICVaccOff(unsigned char* Vacc );

public:
	void InsertOutputYield(CString csCode);

public:
	bool WaitHeaterOK();
	bool m_bWaitHeaterOK;
	bool WaitHeaterStableOK();
	bool m_bWaitHeaterStableOK;
	bool m_bHeaterStableNeed;

	// 1.0Ac
	void ClearHeaterStable();

public:
	bool bCCDPin1MatchOK;
	
public:

	// Repeat Tray
	bool bRepeatInputEmpty;

	// Repeat Tray Pass/Fail
	bool bRepeatTray2OutputFull;
	bool bRepeatTray1OutputFull;

	// Input
	long RepeatMationInput();
	void RepeatMationInputDone();

	// Output
	long RepeatMationOutput();
	void RepeatMationOutputDone();

	// Z Down
	long RepeatMationInputZDown();
	long RepeatMationOutputZDown();
	
	// Check complete
	bool IsRepeatTrayComplete();

	// Get Temperature from communication
	bool GetRepeatTemperatureConfim(tagRepeatTemperData &m_Data, int book);

	// Pass / Fail
	int GetTestLogPassFail(tagTestLog ttLog);	// 1 for Pass, 0 for fail
	void ResetInputStatus();

	// Repeat Tray Report
	void RepeatTrayReport();

	// Repeat Tray Map
	void RepeatTrayMap();

	// Repeat Yield Rate
	void RepeatTrayYieldRate();

	// SLT Protocol
	bool m_bMissionOnTheGo;
	bool m_bMissionOnTheClearGo;
	void InitialMissionOnTheGo();
	void SetRemoteCoordRequest( bool bMissionGo = false );
	bool GetRemoteCoordRequest();
	void SetRemoteCoordClearRequest( bool bMissionClearGo = false );
	bool GetRemoteCoodrClearRequest();
	struct tagRemoteArmTray {
		int m_iRemoteBooking;
		int m_iRemoteTray;
	} m_RemoteArmTray;
	void SetRemoteCoordPosition(int iBooking, int iTray);
	long RemoteMationInput();
	long RemoteMationInputZDown();
	long RemoteMationOutput();
	long RemoteMationOutputZDown();

	// Debug
	int GetThreadMotionStatus();

public:

	// Arm Log IC
	CString GetCurrentTray();
	bool IsArmLogICImageFolderMissing();
	bool IsArmLogRootFolderMissing();
	void CameraCapture();
	
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CThArm)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CThArm)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_THARM_H__AAD642F9_E72E_45EE_9886_8D0DFA0F1C57__INCLUDED_)
