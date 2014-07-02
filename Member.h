// Member.h: interface for the CMember class.
//
//////////////////////////////////////////////////////////////////////


#if !defined(AFX_MEMBER_H__9F8F057C_6810_4EE9_97B3_F33DB2394AE8__INCLUDED_)
#define AFX_MEMBER_H__9F8F057C_6810_4EE9_97B3_F33DB2394AE8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// Define
#include "Define.h"

// CTrayFile
#include "TrayFile.h"

// PreHeaterFile
#include "PreheaterFile.h"

// DB
#include "RADatabase.h"
#include "RADatabaseLock.h"

// Page
#include "PageInitial.h"
#include "PageRun.h"
#include "PageUser.h"
#include "PageSetup.h"
#include "PageEngineer.h"
#include "PageDebug.h"

// System
#include <math.h>
#include <afxmt.h>
#include <afxtempl.h>
#include <map>
#include <vector>

// TrayMap
#include <list> 
#include <string> 
#include <functional> 
#include <iostream>

// SMTP Mail..
#include "CSmtp.h"
#include "MailCtrl.h"

// Torque
#include "DriverMotorTorqueControl.h"

// CCD 
#include "CtrlVision.h"
//#include "CtrlVisionMatch.h"

// Torque
#include "TorqueCtrl.h"

// West
#include "DriveWest.h"

// Tcp
#include "InterfaceTcp.h"

// Remote Mode
#include "DriverTestInterface.h"

class CMember  
{
public:
	CMember();
	virtual ~CMember();

	/////////////////////////////////////////////////////
	// Last Tray
	tagLastTrayData m_LastTrayData;

	/////////////////////////////////////////////////////////
	// Error code library
	tagErrorMsg	Msg[_Max_Error];

	/////////////////////////////////////////////////////
	// Torque
	CTorqueCtrl	m_Torque;	
	
	/////////////////////////////////////////////////////
	// Tray
	tagTraySpec TraySpec;
	
	CString csDebug;

	/////////////////////////////////////////////////////
	// Device Setup File Path
	struct tagFilePath{
		///< 由於會指定檔案，導致相對路徑失效； 
		///< Initial 時，轉成絕對路徑
		
		CString SystemPath;			
		CString SystemSettingPath;
		CString UIPath;
		CString PasswordPath;
		//
		CString CategoryPath;
		CString TrayFilesPath;	
		CString TrayMapPath;
		CString TestSettingPath;
		CString SimulationPath;
		CString AlignmentPath;
		CString MotorNamePath;				
		// Release Note / User Guide
		CString DebugNotePath;				// Debug Function Note
		CString OffsetNotePath;				// Offset Note
		//
		CString BinLogPath;					// Bin Log
		CString TempBinLogPath;				// Temp Bin Log
		CString InputCoordPath;				// Input 
		CString Output1CoordPath;			// Output1
		CString Tray1CoordPath;				// Tray 1
		CString Tray2CoordPath;				// Tray 2
		//
		CString PreHeaterCoordPath;			// Pre-Heater 	
		CString SummaryReportPath;			// Summary Report
		CString AtcModuleSettingPath;		// ATC Module Multi SV Setting
		CString SMPTPath;					// SMTP for Mail Function
		CString TrayPath;					// TrayMap 
		CString CustomFilePath;				// Custom Path
		CString CommuncationPath;			// Communcation Path
		CString JamRateCodePath;			// Jam Rate Code Path
		CString JamRateResultPath;			// Jam Rate Code Result Path
		CString JamRateReportPath;			// Jam Rate Report
		CString AutoRetrySettingPath;		// Auto Retry Setting
		CString BinColorPath;				// Bin Color Path
		CString SimulationCountPath;		// Simulation Path;
		CString ATCMonitorPath;				// ATC Monitor
		CString HandlerComPortPath;			// Handler Com Port 
		CString CCDCameraPath;				// CCD Socket Sensor Path

		// Interface Setting
		CString InterfaceRs232Path;			// RS232 Path
		CString InterfaceTcpPath;			// Tcp Path
		CString InterfaceGpibPath;			// Gpib Path
		CString InterfaceTtlPath;			// TTL Path

		// Note
		CString Rs232NotePath;				// If Note Path - RS232
		CString TcpNotePath;				// If Note Path - Tcp
		CString GpibNotePath;				// If Note Path - Gpib
		CString TtlNotePath;				// If Note Path - Ttl
		//
		CString UPHPath;					// UPH Infomation
		// CCD
		CString CCDImageProfilePath;		// CCD Pin1 Path
		CString CCDImagePath;				// CCD Pin1 Image Path
		CString CCDImageBackPath;			// CCD Pin1 Image Backup Path;
		CString SocketImagePath;			// CCS Socket Setting file and Image Pattent				
		//
		CString TorqueCtrlPath;				// Torque Control..
		CString InputCustomInputPath;		// Input Tray Data File Path
		//
		CString HeaterTempSetPath;			// Heater Setting Path
		CString HeaterTempLkPath;			// Heater Lookup Table Path
		//
		CString PageEnablePath;				// Page Enable Function
		CString ManualContactPath;			// Manual Contact Path
		CString TSRemainICParamPath;		// Ts Remain IC Path
		//
		CString LoopTestSettingPath;		// Loop Test Path
		CString OutputYieldPath;			// Yield Rate Path
		CString OffsetTxtNotePath;			// Offset Note
		CString InterfaceNotePath;			// Interface Note
		CString TorqueStatusPar;			// Torque Status Parameter Path
		CString RepeatTrayCurrPath;			// Repeat Tray current Path
		CString RepeatTrayPath;				// Repeat Tray ctrl setting Path
		CString RepeatTrayTemperPath;		// Repeat Tray temper Path
		CString RepeatTrayFunEnable;		// Repeat Fun Enable Path
		CString JamRateCycleTimePath;		// Handler Status Path
		CString JamReportCounterPath;		// Jam rate counter Path
		CString DMsgReportPath;				// Program Initial
		CString ArmLogICImagePath;			// Arm Log IC Image Path
		CString MContactNotePath;			// Manual Contact Note
		CString SLTProtocolNotePath;		// SLTProtocol Path Note
	}FilePath;

	struct tagReleaseNote{
		CString csDebugNote;
		CString csOffsetNote;
	} ReleaseNote;

	struct tagPanelButton
	{
		unsigned char BtnStartPushed;				// 	Panel Start be pushed
		unsigned char BtnStopPushed;				// 	Panel Stop	be pushed
		unsigned char BtnRetryPushed;				// 	Panel Retry be pushed
		unsigned char BtnSkipPushed;				// 	Panel Skip	be pushed
		unsigned char BtnInitPushed;				// 	Panel Init	be pushed
		unsigned char BtnOneCyclePushed;			//  Panel Flush be pushed
		unsigned char BtnResetPushed;				//  Panel Reset be pushed
		unsigned char BtnTestSiteSkip;				//  Panel TSSkip be pushed
	} PanelButton;

	//////////////////////////////////////////////////////
	// Gear Ration
	struct tagGearRation{
		double X_GearRation;
		double Y_GearRation;
		double Z_GearRation;	
		double Inserter_GearRation;
	} m_Ratio;
	//////////////////////////////////////////////////////

	//////////////////////////////////////////////////////
	// Interface Testing.
	struct tagInterfaceData{
		// It is Interface test dialog CString data
		CString T1;
		CString T2;
		CString T3;
		CString T4;
		// It is Interface test dialog interger data
		int N1;
		int N2;
		int N3;
		int N4;
	} InterfaceData;
	//////////////////////////////////////////////////////

	/////////////////////////////////////////////////
	// Thread monitor
	struct tagThreadStatus{		
		tagThreadCode ErrCtrl;
		tagThreadCode IO;

		// Thstatus for each handler part.		
		tagThreadCode ArmCtrl;			// for Arm control(motor)		
		tagThreadCode InserterCtrl;		// for Inserter control(motor)		
		tagThreadCode TesterCtrl;		// for Tester communction
		tagThreadCode InspectCtrl;		// for spect 
		tagThreadCode ManualCtrl;		// for Manual
	} ThStatus;

	/////////////////////////////////////////////////////////
	// Counter
	struct tagCounter{
		long OutputCount[_Output_Stack_No];	// for RunPage using
		long SiteLotTotal;					// for total testes
		long SiteLotPass;					// for 
		long SitePass;						// for
		long SiteTotal;
		long SocketCount;
	} Counter;

	/////////////////////////////////////////////////////////
	// Event Log 
	struct tagImageList{
		CImageList EventType;
		CImageList Sort;
	} ImageList;

	//////////////////////////////////////////////////////
	// Bitmap
	struct tagBitmap{
		CBitmap Led;
		CBitmap Layout;
		CBitmap Err;
		CBitmap Black;
		CBitmap Logo;
		CBitmap CycleEnd;
	} Bitmap;

	//////////////////////////////////////////////////////
	// Database
	struct tagDB{
		CRADatabaseLock ErrorCode;			// ErrorCode mdb 
		CRADatabaseLock Language;			// Language mdb
		CRADatabaseLock Log;				// BinLog mdb
		CRADatabaseLock tLog;				// tempLog mdb
	} DB;

	struct tagLoadDatabase{
		bool bErrorCode;					// Error Code
	}LoadDatabase;

	/////////////////////////////////////////////////////////
	// Language
	enum LanguageType {enEnglish, enChinese};
	struct tagLanguage{
		long count;
		CString eng[_Max_Language];
		CString chi[_Max_Language];
	} Language;

	/////////////////////////////////////////////////////
	// Tray Skip
	struct tagTraySkip{
		int AutoSkip;
		int TestSiteVacc;
	} TraySkip;


	/////////////////////////////////////////////////////////
	// UI Setting
	// 宣告 UI設定變數(UI)結構區，要讀(存)檔
	struct tagUISetting{
		int Language;								//目前使用語言

		CString	MachineID;							//目前機台名稱		
		// Password using
		CString PasswordSetup;
		CString PasswordEngineer;
		CString PasswordDebug;
		CString PasswordSuperUser;		
		// Mapping
		CString FileMainMapping;					//目前的 Mapping檔案
		CString FileMainBaseMapping;				//目前的 MAPPING BASE FILE 檔案 
		// Tray File
		CString FileMain;							//目前的 TrayFile檔案
		CString FileBaseFile;						//目前的 TrayFile BASE FILE 檔案
		// Testsetting
		CString FileMainTestSetting;				//目前的 TestSetting檔案
		CString FileMainBaseTestSetting;			//目前的 TestSetting BASE FILE 檔案
		// Interface
		CString FileMainInterFaceRs232;				//目前的 Rs232 檔案
		CString FileMainInterFaceTcp;				//目前的 Tcp 檔案
		CString FileMainInterFaceGpib;				//目前的 Gpib 檔案
		CString FileMainInterFaceTtl;				//目前的 Ttl 檔案
		// CCD Socket 
		CString SocketPatternName;					//目前使用的 CCD Socket 檔案
		// ATC Module 
		CString ATCModuleMultiSV;					//目前使用的 ATC Module Multi SV檔案
	} UI;


	/////////////////////////////////////////////////////
	// 宣告主頁面數量(Page)結構區
	struct tagPage{
		CPageInitial	Initial;  //初始化畫面
		CPageRun		Run;	  //執行畫面	給作業員用
		CPageUser		User;	  //使用者畫面	給作業員用
		CPageSetup		Setup;    //設定畫面	給廠工用
		CPageEngineer	Enginner; //工程師畫面	給客戶工程師或自己的技術人員用
		CPageDebug		Debug;	  //軟體工程師  Debug用
		TCITEM			m_Page;	  //儲存參數用
	} Page;

	/////////////////////////////////////////////
	// 系統資訊
	struct tagInfo{
		bool	bRunning;
		int		iThreadCount;	// Now. How many cwinthread be create.
		bool	bCardStatus[2];	// Mocation Card status
		long	ErrorCode;		// System if have ErrorCode.
		bool	bError;			// System have ErrorCode (CheckError).
		bool	bAlarmTimer;	// System have ErrorCode. so Buzzzer Alarm fast or slow
		bool	bSubDlgOpen;	// There are a SubDialog Open (All Button need to disable.)
		bool	bResetError;	// only use when we have no press button for using
	
		long	user;			// enLevelUser, enLevelSetup,...
		bool	bBuzzer;		// if true, turn on Buzzer
		bool	bIOMonitor;		// Is IOMontior Open. If IO Montior Open. Application do not response any single.
		bool	bAlignment;		// Is Alignment Open. If Alignment Open. Application do not response any single.

		int		iStatus;		// Now handler status. Ex: CYCLE,READY,MANUAL....
		CString csError;		// Store now Error desc
			
	} Info;

	//////////////////////////////////////////////////////
	// Bin Setting 
	CArray <tagBinMapping, tagBinMapping> BinMap; // Bin Use

	//////////////////////////////////////////////////////
	// Error code handler
	struct tagError{
		tagErrorParam System;
		tagErrorParam IO;		
		tagErrorParam Arm;		
		tagErrorParam Inserter;
		tagErrorParam Tester;
		tagErrorParam Inspect;
		tagErrorParam Manual;
	} Err;

	/////////////////////////////////////////////////////
	// LotInfo Using.
	struct tagLotInfo{
		// It current lot information
		CString LotInfoDeviceID;
		CString LotInfoMachineID;
		CString LotInfoNo;
		CString LotInfoOperator;
		CString LotInfoProgramerID;
		int		LotInfoIsLotStart;

		int TestItem;		  // 0:Normal, 1:RC1, 2:RC2, 3:RC3

		// It is last time lot information
		// for lot dialog copy last function
		CString OldLotInfoDeviceID;
		CString OldLotInfoMachineID;
		CString OldLotInfoNo;
		CString OldLotInfoOperator;
		CString OldLotInfoProgramerID;

		CString LotStartTime;

	} LotInfo;

	/////////////////////////////////////////////////////////
	// IO
	tagInput	InStatus;

	tagOutput	OutStatus;
	tagOutput	OutSet;
	tagOutput	OutWrite;

	// InStatus		IO 目前 Input 的狀態
	// OutStatus	IO 目前 Output 實際的狀態
    // OutSet		IO 目前 Output 準備要寫入的狀態(新的狀態)
	// OutWrite		IO 目前 Output 實際  寫入的狀態(當前狀態)

	/////////////////////////////////////////////////////////
	// Remote IO
	tagRemoteInput	RemoteInStatus;

	tagRemoteOutput	RemoteOutStatus;
	tagRemoteOutput	RemoteOutSet;
	tagRemoteOutput	RemoteOutWrite;

	/////////////////////////////////////////////////////////
	// Motor
	struct tagMotor{
		tagMotorParam ArmX;
		tagMotorParam ArmY;
		tagMotorParam ArmZ;
		tagMotorParam Inserter;
	} m_Motor;

	//////////////////////////////////////////////////////
	// Timer Setting
	struct tagTimerSetting{
		int iInitialEachMotorWaitTime;		// For Initial Sleep use
		int iMotorRunlineTimeout;			// For Motor RunLine function time out
		int iMotorRunTimeout;				// For Single Motor Run Function time out
		int iInitialZMotorWaitTime;			// For Initial Z Time out 
		int iInitialTimeout;				// For Initialing Time out
		int iCommectionTimeout;				// For Communction Time out
		int iBinLogInsertTimeout;			// For Bin Log Insert to dBase time out
		int	iScanTrayStatus;				// For Tray Status updata.
		int iArmZCheckTime;					// For Amr Z initial check Arm Z have IC timer
		int iRotatorTime;					// For Rotator Stable 
		double	iRotatorTimeout;			// For Rotator Timeout
		int iShuttlePickTimeout;			// For Shuttle Move pick Timeout
		int iShuttleHomeTimeout;			// For Shuttle Move Home Timeout
		int iShuttleStableTime;				// For Shuttle Move Stable Time
	} TimerSetting;

	///////////////////////////////////////////////
	// Interlock for multi-thread
	struct tagRemoteInterlock{
		bool IsRemoteControlMode;			// if true. System in Remote Control Mode
		bool PickIC;						// if true. UI ask Pick IC
		bool ReleaseIC;						// if true. UI ask Release IC

		int RemotePosition;					// UI selected position.
	} RemoteInterlock;

	struct tagManualInterlock{
		bool IsManualControlMode;			// if true. System in Manual Control Mode
	} ManualInterlok;

	///////////////////////////////////////////////
	// Interlock for multi-thread
	struct tagInitialInterlock{
		
		bool InitialTSUpOK;					// if true, It mean initial, TS Up OK, Arm Z can start to initial
		bool InitialArmZUpOK;				// if true, It mean initial, Arm Z Up OK, Arm XY can start to initial
		
	} InitialInterLock;
	///////////////////////////////////////////////
	// Interlock for multi-thread
	struct tagInterlock{

		bool ArmEnd;						// if true. It mean 

		// 
		bool IsIORead;						// if true. It mean already read IO Instatus.
		bool IsIODone;						// if true. It mean IO Thread already create complete
		bool IsRemoteIODone;				// if true. It mean Remote IO Thread already create complete

		// Initial Interlock using. It is Each Axis initial complete
		bool InitialArmZEnd;				// if true, Arm Z initial complete, Arm Z already in Home
		bool InitialArmYEnd;				// if true, Arm Y initial complete, Arm Y already in Home
		bool InitialArmXEnd;				// if true, Arm X initial complete, Arm X already in Home
		bool InserterEnd;					// if true, Inserter already initial complete. Inserter already in Home
		bool TesterEnd;						// if true, Tester initial complete
		bool InspectEnd;					// if true, Inspect initial complete
		bool ManualCtrlEnd;					// if true, Manual initial complete
	
		// Position have IC interlock	
		bool TestSiteWithIC;				// if true. It mean TestSite have IC.
		bool ArmZGetIC;						// if true. It mean ArmZ have a IC.
		bool SocketWithIC;					// if true. It mean Socket with IC.
		bool RotatorWithIC;					// if true. It mean Rotota with IC.
		bool ShuttleWithIC;					// if true. It mean Shuttle with IC
		bool ShuttleHome;					// if true. It mean Shuttle Home
	
		//
		bool ShuttleInputICOK;				// if true. It mean Shuttle IC ready ( Arm put ic to shuttle input )
		bool ShuttleOutputICOK;				// it true. It mean Shuttle IC ready ( Test site put ic to shuttle output )
		bool ShuttleResetInput;				// if true. It mean TestSite Pick IC from socket, 
		//
		// Cycle Finish.
		bool IsCycleFinishOK;				// if true. It mean Cycle Finish, And Run Page can Enable Lot Done.

		// Testing
		bool TestingGo;						// Request ThTester SOT
		bool Testing;						// Testing 
		bool TestingOK;						// ThTester Get EOT

	} InterLock;

	/////////////////////////////////////////////////////
	// Initial Motor Status. 
	struct tagMotorStatus{
		CString ArmX;			// When we Initial. Set Initial cstring status of Arm X
		CString ArmY;			// When we Initial. Set Initial cstring status of Arm Y
		CString ArmZ;			// When we Initial. Set Initial cstring status of Arm Z
		CString Inserter;		// When we Initial. Set Initial cstring status of Inserter
		CString Tester;			// When we Initial. Set Initial cstring status of Tester
		CString Inspect;		// When we Initial. Set Initial cstring status of Inspect
		CString ManualCtrl;		// When we Initial. Set Initial cstring status of Manual

		long ArmXRCount;			// When we Initial. Set Initial RCount status of Arm X
		long ArmYRCount;			// When we Initial. Set Initial RCount status of Arm Y
		long ArmZRCount;			// When we Initial. Set Initial RCount status of Arm Z
		long InserterRCount;		// When we Initial. Set Initial RCount status of Inserter

		bool ArmXInitialed;			// if true, It mean ArmX Initial Complete
		bool ArmYInitialed;			// if true, It mean ArmY Initial Complete
		bool ArmZInitialed;			// if true, It mean ArmZ Initial Complete
		bool InserterInitialed;		// if true, It mean Inserter(Test site) Initial Complete (WebCam taka a image )
		bool TesterInitialed;		// if true, It mean Tester Initial Complete
		bool InspectInitialed;		// if true, It mean Inspect Initial Complete  (WebCam taka a image )
		bool ManualCtrlInitialed;	// if true, It mean Manual Initial Complete
	} MotorStatus;

	struct tagUPH{
		CTime CycleStartTime;
		int CycleTime;				// System Cycle Time.
		int ICTested;				// How many IC be Tested
		int iUPH;					// UPH
	} UPH;

	struct tagDebugError{
		// IO Card
		long ReadErr;
		long ReadCount;
		// Remote IO
		long ReadRemoteErr;
		long ReadRemoteCount;
		long ReadRemoteSpendTime;
	} DebugError;

	/////////////////////////////////////////////////////
	// simulation setting
	tagSimulationSetting Simulation;

	/////////////////////////////////////////////////////////
	// Alignment Point
	tagAlignment m_Align;
	
	/////////////////////////////////////////////////////////
	// Offset Point
	tagOffset m_Offset;

	/////////////////////////////////////////////////////
	// Timer 
	tagTimer Timer;	// ex : Puff. Vac......

	/////////////////////////////////////////////////////
	// Debug Using.
	bool EnginnerCloseErr;

	/////////////////////////////////////////////////////
	// Software setting
	tagSetting Setting;
	/////////////////////////////////////////////////////
	// Yield Setting.
	tagYieldSetting	YieldSetting;	
	/////////////////////////////////////////////////////
	// Site Setting.
	tagSite Site;
	/////////////////////////////////////////////////////
	// Test Setting.
	tagTestSetting m_TestSetting;

	/////////////////////////////////////////////////////////////////////////////////////
	// TrayMap 在使用的變數與結構
	// TrayMap Using.
	std::list<tagTrayMapLog> TrayMap[_Output_Stack_No];

	/////////////////////////////////////////////////////////////////////////////////////
	// TrayMap 在使用的變數與結構 (Repeat Tray)
	// TrayMap Using.
	std::list<tagTrayMapLog> TrayMapRepeat[_Output_Stack_Number];
	
	/////////////////////////////////////////////////////
	// Tray Map Dialog setting.
	struct tagTrayMapSetting{
		bool bTemp;		// 是否要顯示 溫度, 用來表示那一顆 IC 的溫度
		bool bCode;		// 是否要顯示 Bin Code. 正確的字串請參考 Category.
	} TrayMapSetting;
		  
	/////////////////////////////////////////////////////////
	// UPH and Cycle times information
	struct tagCalcInfo{
		int UPH;			// UPH / PerHour tested ic
		int CycleTimes;		// How many cycle finish times
		int TestedIC;		// How many IC be tested
	} CalcInfo;

	int iDebugCount;			// check error times.
	int iDebugPreHeaterCount;	// check Soak time error

	CPoint m_ArmPosition;
	int	   m_ArmBook;
	int	   m_ArmPlaceBook;
	int	   m_ArmChipTrayBook;

	// Note: Yield Control
	struct tagYieldCheck{
		int iCountinueFail;	// 如果遇到 Fail 就開始計數. 如果遇到 Pass 就清成 0
		int iYieldControl;	// Yield Control 的計數器
	} YieldCheck;


	struct tagdBLog{
		int InsertFailCount;	// 記錄有多少次 Insert 失敗		
	} dBLog;

	// Smart Mail 的功能
	tagMailSetting	m_MailSetting;

	// Contact Counter 的資訊
	struct tagContactCounterValue{
		long lContactConter;
	} m_ContactCounterValue;

	// TrayMap Color
	COLORREF iBinColor[_Tray_Bin];

	// ATC Monitor
	struct tagATCMonitor{
		double sv;
	} m_ATCMonitor;

	// Jam rate information
	struct tagJamRateInfo{
		long m_lJamError;
		long m_lTotalUnit;
		long m_lCycleTime;
	} m_JamRateInfo;

	// Debug / Initial Lmt Counter
	struct tagLmtCounter{
		int iTSnLmtCounter;	// Initial Direction
		int	iTSpLmtCounter;
		int iYpLmtCounter;	// Initial Direction
		int iYnLmtCounter;
		int iXpLmtCounter;	// Initial Direction
		int iXnLmtCounter;
		int iZnLmtCounter;	// Initial Direction	
		int iZpLmtCounter;
	} m_LmtCounter;

	// ION Fan Alarm Timer
	long IONFanAlarmStart;
	bool IONFanAlarm;

	// Input Tray Alarm
	struct tagInputTrayControl{	
		bool bInputTrayChange;	// If User used the Input Tray. We Should Alarm it..
	} m_InputTrayControl;

	// Run Page Output Color
	struct tagOutputRunPageColor{	
		int R;	
		int G;
		int B;
	} m_RunPageOutputColor;

	// Camera (CCD Socket)
	struct tagCCDSocketControl{	
		int iCCDUse;	// If User used the Input Tray. We Should Alarm it.		
		// ROI
		int RoiX;
		int RoiY;
		int RoiW;
		int RoiH;
		double RationX;
		double RationY;
	} m_CCDSocketControl;

	// Camera (CCD Pin1)
	struct tagCCDPin1Control{	
		int iCCDUse;	// If User used the Input Tray. We Should Alarm it.		
		// ROI
		int RoiX;
		int RoiY;
		int RoiW;
		int RoiH;
	} m_CCDPin1Control;

	// West List
	struct tagWestCtrlList{
		CArray<tagWestControllerList, tagWestControllerList> m_List;
	} m_WestControllerList;

	// Remote IO Tool 
	struct tagRemoteIOTool{
		CString csInputResult;
		byte receive[_RemoteLength];
		CString csOutputResult;
	} m_RemoteIOTool;

	// Heater control
	struct tagHeaterCtrl{
		bool m_bHeaterIsStable;
		bool m_bHeaterTempOK;
		long m_lHeaterStart;
	} m_heaterCtrl;

	// Yield Control
	struct tagYieldCtrl{
		long m_lContinueFail;
		CArray <int, int> m_iPFArray;
		double m_dFailRate;
		long m_lTested;
	} m_YieldCtrl;

	// Torque Tool Control
	struct tagTorqueToolSet{
		double daValue;
		double dbValue;
	} m_TorqueToolSet;

	// Vision Setup
	struct tagVisionSet{
		long lVisionPickDut;
	} m_VisionSet;

	// TcipInfo
	struct tagTcpInfo{
		CString csTesterIP;
		unsigned int iPort;
	} m_TcpInfo;

	// Page Enable 
	tagUserPageEnable m_UserPageEnable;
	tagSetupPageEnable m_SetupPageEnable;
	tagEngineerPageEnable m_EngineerPageEnable;

	// Custom Manual Contact
	tagManualContactEnable m_MCFunction;

	// Error Rate Report
	CArray <tagRateDataLogData, tagRateDataLogData> m_ErrorRateData; 

	// Auto Retry Adjust Value
	tagAutoRetryAdjsutValue	m_AutoRetryAjsutValue;

	// Bin Color
	CArray <tagBinColor, tagBinColor> BinColorItem;

	// Output Yield 
	CArray <tagOutputYield, tagOutputYield> m_OutputYieldCounter;

	//
	tagInterfaceEnable	m_InterfaceEnable;

	//
	tagHandlerComPort	m_HandlerComPort;

	//
	tagContactForce	m_ContactForce;

	//
	CCtrlVision	m_Vision;

	//
//	CCtrlVisionMatch m_VisionMatch;

	//
	CMailCtrl	m_MailCtrl;

	//
	tagUPHData	m_UPHData;

	//
	tagLotProgressData m_LotInfoProg;

	//
	tagIfRs232Setting	m_IfRs232;

	//
	tagHeaterParam	m_West;

	//
	CDriveWest	m_DriveWest;

	//
	CDriverMotorTorqueControl  m_DriveMotorTorque;

	//
	tagTSRemainICParameter	m_TSRemainICParameter;

	//
	tagTsFloatingConvert	m_TsFolatingConvert;

	//
	tagTsFloatingParameter	m_TsFolatingParameter;

	//
	tagCustomFilePath CustomFilePath;

	//
	tagManulContactMode m_ManualContactMode;

	//
	tagTrayFileDefColor m_TrayFileDefColor;

	//
	tagRepeatTrayDATA m_RepeatTrayDATA;

	//
	tagRepeatConfimCmd m_RepeatConfimCmd;

public:
	CInterfaceTcp m_InterfaceTcp;
	// TCP
	struct tagTcpValue{
		bool	gettcpBin;
		bool	gettcpstart;
		bool	gettcpstartRev;
		CString	tcpBin;
		CString tcpReady;
		CString tcpBinSource;
	} m_TcpValue;

public:
	tagIfRs232Setting m_InterfaceSetting;
	tagIfTcpSetting	m_TcpipInterfaceSetting;

public:

	// 1.0Ac
	struct tagRepeatTrayTemp{
		double dSV;
		double dStableTime;
		double dSoakTime;
		double dTolerance;
	} m_RepeatTemp;

public:
	// 1.0Ac
	tagTorqueStatus	m_TorqueStatusPar;

	// 1.0Ac
	// Repeat Tray
	tagRepeatTrayCtrl m_RepeatTrayCtrl;				// main mode
	tagRepeatInOutCtrl m_RepeatInOutCtrl;			// input/output ctrl
	tagEnableRepeatTray m_EnableRepeatTrayFun;		// function

	CArray<tagRepeatTemperData, tagRepeatTemperData&> m_RepeatTrayTemperData;

public:
	// 1.0Af
	// Lamp Setup
	struct tagTowerBlinkTimer{
		bool bBlink1;
		bool bBlink2;
		bool bBlink3;
		bool bBlink4;
		bool bBlink5;
		long lBlink1Start;
		long lBlink2Start;
		long lBlink3Start;
		long lBlink4Start;
		long lBlink5Start;
	} m_TowerBlinkTimer;

	// 1.0Af
	struct tagLastTrayFile{
		CString csLastTrayFile;
	} m_LastTrayFile;

	// 1.0Ah
	struct tagAlignProtuction{
		double m_TestNoSafePosition;
	} m_AlignProtuction;

public:
	//
	tagTowerSetupSetting m_TowerSetupSetting;

	tagArmLogICImage m_ArmLogICImage;

	tagTitleExtendNote m_TitleExtendNote;

	tagRemoteCtrlFun m_RemoteCtrlFun;

public:

	// 1.0Ah
	CDriverTestInterface m_TestInterface;
	CDriverTestInterfaceTCP *m_singleSocket;

public:

	struct tagRemoteTestResult{
		CString m_TestResult;
		bool m_bResultReady;
	} m_rTestResilt;
};	

#endif // !defined(AFX_MEMBER_H__9F8F057C_6810_4EE9_97B3_F33DB2394AE8__INCLUDED_)
