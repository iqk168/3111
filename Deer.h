// Deer.h : main header file for the DEER application
//

#include "resource.h"

#if !defined(AFX_DEER_H__2138A7A0_6BC3_4784_82F4_CE39748F3DBE__INCLUDED_)
#define AFX_DEER_H__2138A7A0_6BC3_4784_82F4_CE39748F3DBE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

#include "Member.h"
#include "Function.h"
#include "Parser3111.h"
// Dialog
#include "DlgManualContact.h"
#include "DlgRemoteRecover.h"
#include "DlgManualContactRecover.h"
#include "DlgVisualButton.h"
#include "DlgThreadMontior.h"
#include "DlgMotorSimpleStatus.h"
#include "DlgReLoadFile.h"
#include "DlgButton.h"
#include "DlgTrayStatus.h"
#include "DlgBinStatus.h"
#include "DlgBinColor.h"
#include "DlgYieldMonitor.h"
#include "DlgRemoteControlCustom.h"
#include "DlgUPHTool.h"
#include "DlgCylinderLifeTimeTool.h"
#include "DlgTestTesting.h"
#include "DlgOutputYield.h"
#include "DlgTrayRepeatStatus.h"
#include "DlgProgramStart.h"
#include "DlgCommunicationInfo.h"
#include "DlgRemoteCommunication.h"
#include "DlgSLTProtocol.h"

// Nudm
#include "Dll6.h"

// CWinThread
#include "ThErrorCtrl.h"
#include "ThIOReadWrite.h"

#include "ThArm.h"
#include "ThInspect.h"	
#include "ThTester.h"
#include "ThInserter.h"	
#include "ThManualCtrl.h"
#include "ThIOReadWriteRemoteIO.h"
// Initial Arm 
#include "ThInitialArm.h"



/////////////////////////////////////////////////////////////////////////////
// CDeerApp:
// See Deer.cpp for the implementation of this class
//

class CDeerApp : public CWinApp
{
public:
	CDeerApp();

	// GDIPlus
	ULONG_PTR        m_gdiplusToken;

	// 1.0Ah
	enum TitleExtendNote {
		enTitleTrayFile			= 0,
		enTtileMachineFile		= 1,
	};

	// 1.0Af
	enum TrayCurrentStatus {
		// 0-Tray1, 1-Tray2
		enTray1					= 0,
		enTray2					= 1,
	};

	// 1.0Af
	enum TowerChoiseSel {
		// 0-Disable, 1-Enable, 3-Blink1, 4-Blink2, 5-Blink3, 6-Blink4, 7-Blink5
		enTowerChoiseDisable	= 0,
		enTowerChoiseEnable		= 1,
		enTowerChoiseBlink1		= 2,
		enTowerChoiseBlink2		= 3,
		enTowerChoiseBlink3		= 4,
		enTowerChoiseBlink4		= 5,
		enTowerChoiseBlink5		= 6,
	};

	// 1.0Ac
	enum RepeatTrayDefMation{
		enRepeatTrayMation1			= 0,
		enRepeatTrayMation2			= 1,
	};

	// 1.0Aj
	enum RemoteTrayDefMation{
		enRemoteTrayMation1			= 0,
		enRemoteTrayMation2			= 1,
	};

	// 1.0Ac
	enum RepeatTrayMationDef{
		enRepeatTray1ToTray2		= 1,	// Input->Output
		enRepeatTray2ToTray1		= 2,	// Output->Input
		enRepeatTray1AndDisable		= 3,	// Both, Disable
		enRepeatDisableAndTray2		= 4,	// Disable, Both
		enRepeatTray1AndTray2		= 5,	// Both, Both
		enRepeatPass1AndFail2		= 6,	// Pass, Fail (Tray1 Pass Tray2 Fail)
		enRepeatFail1AndPass2		= 7,	// Fail, Pass (Tray1 Fail Tray2 Pass)
	};

	// 1.0Ac
	enum RepeatTrayDefine{
		enRepeatDefineInput			= 0,
		enRepeatDefineOutput		= 1,
		enRepeatDefineBoth			= 2,
		enRepeatDefineDisable		= 3,
		enRepeatDefinePass			= 4,
		enRepeatDefineFail			= 5,
	};

	// 1.0Ac
	enum RepeatTrayMode{
		enRepeatTrayNone			= 0,
		enRepeatTrayInOutCtrl		= 1,
		enRepeatTrayBinningCtrl		= 2,
	};

	// 1.0Ab
	enum IfNote{
		enNIfRs232					= 0,
		enNIfTcpIp					= 1,
	};

	// 1.0Ab
	enum OffsetNote {
		enNofRotatorX				= 0,
		enNofRotatorY				= 1,
		enNofRotatorZ				= 2,
		enNofRotatorZ2				= 3, // Place
		
		enNofShInX					= 4,
		enNofShInY					= 5,
		enNofShInZ					= 6,
		enNofShInZ2					= 7, // Place

		enNofShOutX					= 8,
		enNofShOutY					= 9,
		enNofShOutZ					= 10,

		enNofInputX					= 11,
		enNofInputY					= 12,
		enNofInputZ					= 13,
		enNofInputZ2				= 14, // Place

		enNofOutputX				= 15,
		enNofOutputY				= 16,
		enNofOutputZ				= 17,
		enNofOutputZ2				= 18, // Place

		enNofTsPick					= 19,
		enNofTsPlace				= 20,
		enNofTsContact				= 21,
	};
	
	enum RemoteControlStatus {
		enRemoteNone				= 0,
		enRemoteWaitOK				= 1,
		enRemoteMoving				= 2,
		enRemoteStandy				= 3,
		enRemoteAlarm				= 4,
	};


	// Communcation GPIB
	enum CommunicationGPIB {
		enGPIBSeikoNS6000		= 0,
		enGPIBRohm				= 1,
	};

	enum AlignmentCheck {
		enAlignemntFix1						= 0,
		enAlignemntFix2						= 1,
		enAlignemntOutput1					= 2,
		enAlignemntOutput2					= 3,
		enAlignemntInput					= 4,
		enAlignemntArmInShuttleInput		= 5,
		enAlignemntArmInShuttleOutput		= 6,
		enAlignmentArmInShuttle				= 7,
		enAlignemntArmShuttleInputoffset	= 8,
		enAlignemntArmShuttleOutputoffset	= 9,
		enAlignmentArmTrayPosition			= 10,
		enAlignmentArmZHome					= 11,
		enAlignmentArmXYHome				= 12,
		enAlignmentArmZMove					= 13,
		enAlignmentPreHeater				= 14,
		enAlignmentRotator					= 18,
		enAlignmentTSAutoKHeigh				= 19,
	};

	enum enStack{
		enNone = -1,
		enInputStack = 0,
		enOutput1Stack = 1,
		enOutput2Stack = 2,
	};

	enum enTrayStack{
		enTrayNone = -1,
		enTrayInputStack	= 0,
		enTrayOutput1Stack	= 1,
		enTrayOutput2Stack	= 2,
		enTrayEmptyStack	= 3,
	};

	enum enGPIBError
	{
		enTimeout	= 1,
		enTmo		= 2,
		enWait		= 3,
	};

	enum enUPHLog
	{
		enUPHTS			= 0,
		enUPHArmZ		= 1,
		enUPHArmZCustom = 2,
		enUPHOutput		= 3,
	};

	enum enTrayMode
	{		
		enHeater			= 0,
		enAmbit				= 1,	
		enATCMoudle			= 2,
		enTriTemperature	= 3,
		enPTCMoudle			= 4,
		enRemote			= 5,
	};

	enum enSystemStatus 
	{
		enReady = 0x11,							// After Initial. Wait for Start		
		enInitial = 0x20,	enUninitial = 0x21,		
		enCycle = 0x30,		enCycleStop = 0x31,
		enOneCycle = 0x40,	enOneCycleStop = 0x41,
		enOverride = 0x50,	enOverrideStop = 0x51,
		enManual = 0x60,	enManualStop = 0x61,
		//後續新增
		enDemoRun	=0x70,		enDemoStop = 0x71,
		enOfflineRun = 0x80,	enOfflineStop = 0x81,
		enError = 0x91,
		enAbotring = 0xA0,
		enWaitTempStable = 0xB0,
	};

	enum enBinCode
	{
		enBin1			= 0,	// Output 1
		//
		enBin2			= 1,	
		enBin3			= 2,
		enBin4			= 3,
	};

	// 0: RS232, 1: TTL, 2: GPIB
	enum enInterFaceType
	{
		enRS232		= 0,	// RS232
		enGPIB		= 1,	// GPIB
		enTCP		= 2,	// TCP
		enTTL		= 3,	// TTL
	};

	enum enDebugMessage 
	{
		enDArm			= 1,
		enDTestSite		= 2,
		enDWest			= 3,
		enDInspect		= 4,
		enDTester		= 5,
		enDSpecially	= 6,
		enDStack		= 7,
		enDManual		= 8,
	};

	enum enWest
	{
		enWestPreheater = 1,
		enWestShuttle = 2,
		enWestTestSite = 3,
	};

	// If error. Witch Button press by USER.
	enum ErrorAction 
	{		
		ActionNone			= 0,
		ActionInitial		= 1,
		ActionStart			= 2,
		ActionStop			= 3,
		ActionOneCycle		= 4,
		ActionSkip			= 5, 
		ActionRetry			= 6, 
		ActionReset			= 7,
		ActionTSSkip		= 8,
	};

	// Multi SV
	enum MultiSVController
	{
		enATEC302Controller = 0,
		enWestController	= 1,
	};

	// Site Setting
	enum enRunMode
	{
		enOnLine = 0, 
		enOffLine = 1, 
		enDemo = 2, 
		enRunModeEnd = 3
	}; // do not change

	enum BinColor {
		enPass = RGB( 0, 255, 0),
		enOutput1 = RGB( 255, 0, 0),
		enOutput2 = RGB( 255, 255, 0),
//		enOutput3 = RGB(0, 0, 255),
	}; 
	// It is for Bin color.
	// Note: effect in Run Page. and Tray Map.

	void InitialStatus();
	void InitialParameter();
	void InitialIOStatus();

protected:
	HACCEL ghAccelTable;

// CWinThread
public:
	CThErrorCtrl				m_tErr;
	CThIOReadWrite				m_tIO;
	CThIOReadWriteRemoteIO		m_tIORemote;

	// 		
	CThArm						m_tArm;	
	CThInspect					m_tInspect;		
	CThTester					m_tTester;
	CThInserter					m_tInserter;
	CThManualCtrl				m_tManualCtrl;
	CThInitialArm				m_thInitialArm;		// This is for Initial Arm. 

	//
	CDlgThreadMontior			m_DlgThreadMonitor;
	CDlgButton					m_DlgButton;
	CDlgTrayStatus				m_DlgTrayStatus;
	CDlgBinStatus				m_DlgBinStatus;
	CDlgBinColor				m_DlgBinColor;
	CDlgYieldMonitor			m_DlgYieldMonitor;
	CDlgUPHTool					m_DlgUPHData;
	CDlgCylinderLifeTimeTool	m_DlgCylinderLifeTimeTool;
	CDlgOutputYield				m_DlgOutputYield;
	CDlgTrayRepeatStatus		m_DlgTrayRepeatStatus;
	CDlgCommunicationInfo		m_DlgCommunicationInfo;
	CDlgRemoteCommunication		m_DlgRemoteComm;

	// User Request
	CDlgVisualButton			m_DlgVisualButton;
	CDlgMotorSimpleStatus		m_DlgMotorSimpleStatus;
	CDlgReLoadFile				m_DlgReloadFile;
	CDlgRemoteControlCustom		*m_DlgRemoteControlCustom;
	CDlgManualContact			*m_DlgManualContact;
	CDlgManualContactRecover	*m_DlgManualContactRecover;
	CDlgTestTesting				*m_DlgTesting;
	CDlgSLTProtocol				*m_DlgSLTProtocol;

	// Program Start Initial
	CDlgProgramStart			*m_DlgProgramStartInitial;


	CWnd	*m_pWndMotor;		// This is for Verify dialog updata message. Motor	
	CWnd	*m_pWndSerial;		// This is for Serial Port (RS232) updata message. Refer Interface Testing Dialog

	CWnd	*m_pWndVisionSetup;	// This is for VisionSetup Port  updata message. Refer GPIB Ctrl Dialog
	CWnd	*m_pDlgTesting;		// This is for Testing	Using
	// 
	CWnd	*m_pWndVisionOrcSetup;	// This is for VisionSetup Port  updata message. Refer GPIB Ctrl Dialog


	/////////////////////////////////////////////////////////////////////////////
	// Tray File
	CTrayFile	m_InputTray;
	CTrayFile	m_OutputTray;

	/////////////////////////////////////////////////////////////////////////////
	// Tray File / Repeat Tray
	CTrayFile	m_Tray1;
	CTrayFile	m_Tray2;

	// PreHeater
	CPreheaterFile	m_PreHeaterTray;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDeerApp)
	public:
	virtual BOOL InitInstance();
	virtual BOOL ProcessMessageFilter(int code, LPMSG lpMsg);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CDeerApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

extern CDeerApp theApp;
extern CMember m;
extern CFunction f;
extern CParser3111 ps;
/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DEER_H__2138A7A0_6BC3_4784_82F4_CE39748F3DBE__INCLUDED_)
