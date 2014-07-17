
#ifndef _DEFINE_H
#define _DEFINE_H

#include <afxtempl.h>
// This is for CArray

#define _AlignmentShuttle	18.0 //mm

#define _TrayRemind			" - tray file (Product)"
#define _HandlerRemind		" - handler file (Machine)"

#define _Infinity			"Infinity"

#define _MaxLoopTestSet		50

#define _DefaultCode		"None"

#define _Tcp_If_Port		2000

#define _TimeTSRemainIC		50

#define _SendStartDelayMax	8	// secs

#define _BinDescOther		"Other"
#define _BinDescTimeout		"Timeout"

//
#define _DRecv				"R:"
#define _DSend				"S:"

//
#define _MaxPogoCount		500
#define _MaxPogoForce		45

#define _ArmLogICTray1		"Tray1"
#define _ArmLogICTray2		"Tray2"
#define _ArmLogICImage		".bmp"
#define _ArmLogICImage2		"*.bmp"
#define _ArmLogICImageJpg	".jpg"

#define _GPIBAddr			33

#define _RepeartTrayInput	"Input"			// 入料
#define _RepeartTrayOutput	"Output"		// 出料
#define _RepeartTrayBoth	"Both"			// 入料/出料
#define _RepeartTrayDisable	"Disable"		// 關閉
#define _RepeartPass		"Pass"			// 入料(放Pass)
#define _RepeartFail		"Fail"			// 出料(放Fail)

// 1.0Af
// UPH Tool
#define _UPHTs				"TsUPH"

#define _DMsgMark			" !!!!!!!!!!"

#define _ICON_Count			15
#define _ICON_Module		3	// 功能模組, 由第幾排開始排列
#define _ICON_TrayMod		4	// Tray File 相關功能, 由第幾排開始排列
#define _ICON_Handler		4	// 功能模組 Handler 主設定, 由第幾排開始排列
#define _ICON_Max			35	// 一個 page 最大功能數量
#define _ICON_Max_Row		7	// 一個 page 一列最多放幾個 Button
#define _ICON_H				8	// 一個 page Button上下距離
#define _ICON_W				8	// 一個 page Button左右距離

//
#define _MC_ICON_Max		6	// Manual Contact Extend Function
#define _MC_ICON_H			8	// Manual Contact 一個 Button上下距離
#define _MC_ICON_W			8	// Manual Contact 一個 Button左右距離
#define _MC_ICON_Max_Row	99	// Manual Contact 一列最多放幾個 Button

//
#define _RE_ICON_H			8	// Repeat Tray
#define _RE_ICON_W			8	// Repeat Tray 一個 Button上下距離
#define _RE_ICON_Max		6	// Repeat Tray 一個 Button左右距離
#define _RE_ICON_Max_Row	99	// Repeat Tray 一列最多放幾個 Button

#define _MaxATCModuleTempRange	10.0	// deg
#define _MinATCModuleTempRange	0.5		// deg
#define _MaxATCModuleChangeStableTime	600.0	// secs
#define _MinATCModuleChangeStableTime	300.0	// secs

#define _RemoteLength	9

//
#define	_MaxHeaterTemp			145.00
#define	_MinHeaterTemp			25.00
#define	_MaxHeaterStableTime	500
#define	_MinHeaterStableTime	5
#define	_MaxHeaterSoakTime		500
#define	_MinHeaterSoakTime		5
#define _MaxHeaterTolerance		3.0
#define _MinHeaterTolerance		1.0

//
#define _ICON_TRAY_TYPE	7

//
#define _ROTATOR_ICON	2

//
#define _IF_TYPE_ICON	4

#define _MaxAutoRetry	3

// Motor
#define _pSpeed			1
#define _WaitPLmt		500

//
#define _IOButtonOn		0x1
#define _IOButtonOff	0x0

#define _IOBtnTSPress	0		

#define _ShuttleNLmtOn	0
#define _ShuttleNLmtOff 1
#define _ShuttlePLmtOn	0
#define _ShuttlePLmtOff	1
#define _ShuttleJamOn	0
#define _ShuttleJamOff	1

//
#define _TSVacOff		1
#define _ArmZVacOff		1
#define _TSSkipOff		1
#define _TrayInPosOff	1
#define _DoorNoClose	1
#define _EmgNoError		1
#define _AirNoSource	1

#define _ArmZVaccOn		0
#define _TSVacOn		0
#define _EmgError		1
#define _TrayInPosOn	0
#define _RotatorJamOn	1
#define _RotatorExistOn	1
#define _HeaterOn		1

// CCD Socket
#define _SockeDb					"Thumbs.db"
#define _SocketGrab					"Grab.bmp"
#define _SocketGrabSub				"GrabSub.bmp"
#define _ScoketSettingInfo			"Info.txt"
#define _SocketSettingImage			"Image.bmp"
#define _SocketSettingSubImage		"ImageSub.bmp"
#define _SocketMinScore				0.7

#define _ArmLogICDb					"Thumbs.db"

// UI
#define	_UpdataTestTime		1		// sec

#define _MaxRetryCounter	5

// Initial Arm X easy timeout.! When it happen, RCount = 1000, LCount = 1001 / Motor is not easy InPos Really
#define	_InitialInPosRange			3

#define	_Tray_Bin					17 // 0~15 Bin and 16 for Other

// ION Alarm Detect Time
#define _IONAlarmCheckTime			2000	// ms

// CSV
#define _ProgramReport			".csv"

#define _EventLogFileName		"EventLog"
#define _EventLogReport			".csv"	

// TrayMapReport
#define _TrayMapReportName		"TrayMapReport"
#define _TrayMapReport			".csv"	

//
#define _StatusReportLog		".csv"	
#define _StatusReportLogList	"*.csv"

//
#define _UPHLogReport			".csv"

//
// CCD Pin1
#define	_CCDName1				"*.IMG"
#define	_CCDName2				".IMG"
#define _CCDImageName1			"*.bmp"
#define _CCDImageName2			".bmp"
#define _CCDImageName3			"Sub.bmp"
#define _CCDPin1				"Grab.bmp"
#define _CCDSubPin1				"GrabSub.bmp"
#define _CCDShowPin1			"GrabShow.bmp"
#define _CCDPin1MinScore		0.8
#define _VisionOffset			0 // 取像換算偏移 15

#define _CCDNameDelete			".IMGDelete"
#define _CCDNameImageDelete		".bmpDelete"

// Multi Input Tray 
#define _RemoteInputTrayFileDATA		"RemoteInputTrayDATA"
#define _RemoteInputTrayFileDATASub		".RemoteDATA"
#define _RemoteInputTrayFileDATAFolder	"*.RemoteDATA"

// 
#define _MaxDaysLog			30	// Max days for backup Log file.! 

//
#define _TestingStatus		"TestSettingStatus"
#define _TestingStatusR		"TestSettingStatus:"

#define _MappingStatus		"MappingStatus"
#define _MappingStatusR		"MappingStatus:"

#define _InteraceStatus		"InterfaceStatus"
#define _InteraceStatusR	"InterfaceStatus:"

#define _SLTProgramStatus	"SLTProgramStatus"
#define _SLTProgramStatusR	"SLTProgramStatus:"

//
#define _YieldControlStatus		"YieldControlStatus"
#define _YieldControlStatusR	"YieldControlStatus:"

#define _AutoSkipStatus			"AutoSkip"
#define _AutoSkipStatusR		"AutoSkip:"

// 1.0Af
// Tower Setting (Lamp)
#define _TowerSetupSetting	"TowerSetupSetting"
#define _MaxTowerBlink		5
#define _MaxTowerDesc		"Blink "
#define _MaxTowerBlinkTime	2.0
#define _MinTowerBlinkTime	0.05

// 1.0Af
// Tower Setting (Lamp)
#define _TowerLightOff		"Off"
#define _TowerLightOn		"On"
#define _TowerLightBlink1	"Blink1"
#define _TowerLightBlink2	"Blink2"
#define _TowerLightBlink3	"Blink3"
#define _TowerLightBlink4	"Blink4"
#define _TowerLightBlink5	"Blink5"

#define _TowerRed			" Red"
#define _TowerYellow		" Yellow"
#define _TowerGreen			" Green"

// Error 
#define IDC_ERROR_VIEW  1139

// Tray def color
#define ST_DEF_HEATER	RGB(255, 0, 0)
#define ST_DEF_AMBIENT	RGB(0, 255, 0)
#define ST_DEF_TRI		RGB(76, 76, 255)
#define ST_DEF_PTC		RGB(255, 255, 0)
#define ST_DEF_ATC		RGB(255, 255, 0)

// Color
#define ST_BLACK		RGB(0, 0, 0)				
#define ST_WHITE		RGB(255, 255, 255)			
#define ST_RED			RGB(255, 0, 0)				
#define ST_GREEN		RGB(0, 255, 0)				
#define ST_BLUE			RGB(0, 0, 255)				
#define ST_CYAN			RGB(0, 255, 255)
#define ST_YELLOW		RGB(255, 255, 0)
#define ST_MAGENTA		RGB(255, 0, 255)
#define ST_DARKRED		RGB(128, 0, 0)
#define ST_DARKGREEN	RGB(0, 128, 0)
#define ST_LIGHTGREEN	RGB(0, 192, 0)
#define ST_LIGHTYELLOW	RGB(255, 255, 128)
#define ST_DARKBLUE		RGB(0, 0, 128)
#define ST_DARKMAGENTA	RGB(128, 0, 128)
#define ST_SKYBLUE		RGB(166, 202, 240)
#define ST_GRAY			RGB(128, 128, 128)
#define ST_BACKGROUND	RGB(192, 192, 192)
#define ST_BROWN		RGB(192, 0, 0)
#define ST_LANCE		RGB(240, 210, 240)
#define ST_DISABLE		RGB(64, 0, 64)

// Time setting 
#define		_InitialArmXTimeout			60000	// msec
#define		_InitialArmYTimeout			60000	// msec
#define		_InitialArmZTimeout			60000	// msec
#define		_InitialTestSiteTimeout		60000	// mesc
#define		_InitialShuttleTimeout		60000	// msec
#define		_InitialStackTimeout		60000	// msec
#define		_ClearCountWait				1500	// msec
#ifdef _Demo
#define		_WaitLmt					550		// msec
#else
#define		_WaitLmt					1250	// msec
#endif
#define		_PansonicCheckBusy			500		// msec

// Software setting.
#define _Max_Error					1000
#define _Max_Language				1000
#define _Max_Event					30000

// Repeat Temper Error
#define _RepeatErrorTemp			999.0

//
#define _Max_Range_Error			2500

#if _Demo
#define _Wait						1		// ms
#else
#define _Wait						1		// ms
#endif

#define _TimeUpdate					200		// ms
#define _Status_Timer				100		// ms
#define _Tray_Status_Timer			200		// ms
#define _Interrupt_Time_Interval	50		// ms

#define _WaitD						0		// ms

#define _WaitLotDoneProgress		5		// ms

// File setting
#define _SubFileName1				"*.Tray"
#define _SubFileName2				".Tray"

#define _SubOffsetName1				"*.offset"
#define _SubOffsetName2				".offset"

#define _SubMappingName1			"*.mapping"
#define _SubMappingName2			".mapping"

#define _SubTestSettingName1		"*.set"
#define _SubTestSettingName2		".set"

// Interface Sub FileName
#define _SubInterfaceGPIB			".GPIB"
#define _SubInterfaceRS232			".RS232"
#define _SubInterfaceTCP			".TCP"
#define _SubInterfaceTTL			".TTL"

#define _SubSLTName1				"*.SLT"
#define _SubSLTName2				".SLT"

#define	_InitialZHome			2		// mm
#define	_InitialYHome			10		// mm
#define	_InitialXHome			-10		// mm
#define _InitialShuttleHome		-5		// mm
#define _InitialTestSite		10		// mm

#define _ArmRotaotr				-5.5		// mm
#define	_ArmZPlace				-1		// mm
#define _ArmZShuttle			0		// mm
#define _MaxSocketPos			-50.0	// mm


// TrayMap Using.
#define _Output_Stack_No		1		// 1 fix output
#define _Max_Tray_Map_Size		10000

// TrayMap Repeat Using
#define _Output_Stack_Number	2		// 2 fix (tray1, tray2)


#define _Site_Count				1		// 1 Site

#define _Sum1				"*.sum"
#define _Sum2				".sum"

#define _Atc1				"*.atc"
#define _Atc2				".atc"
#define _AtcDelete			".Delete"

// PreHeater 
#define _MaxPreHeaterDevice		300

//
#define _Output_Stack			1
#define _Input_Stack			1

// H/W
#define _Stack_A				4		// mm
#define _Stack_B				0		// mm

#define _PreHeater_A			10		// mm
#define _PreHeater_B			10		// mm
#define _ShuttleInput			0		// mm
#define _ShuttleOutput			0		// mm
#define _ShuttleOutputZ			-5.5	// mm
#define _TestSitePickToPlace	-1		// mm
#define _TestSitePickToHome		-15		// mm
#define _FixInputOuputZ			-5.5	// mm
#define _ArmZToCCD_X			-19		// mm
#define _ArmZToCCD_Y			2		// mm

// DB
#define _InsertCount			5
// Vision Device In, Pick Dut Position
#define		_Dut						0

#endif // _DEFINE_H

// Color Button
// Colors for the button.
const COLORREF  COLOR_RED           = RGB( 255,   0, 0   );
const COLORREF  COLOR_PINK          = RGB( 255, 192, 203 );
const COLORREF  COLOR_YELLOW        = RGB( 255, 255, 0   );
const COLORREF  COLOR_PALE_YELLOW   = RGB( 240, 230, 140 );
const COLORREF  COLOR_ORANGE        = RGB( 255, 153, 0   );
const COLORREF  COLOR_GREEN         = RGB(   0, 255, 0   );
const COLORREF  COLOR_PALE_GREEN    = RGB( 152, 251, 152 );
const COLORREF  COLOR_BLUE          = RGB(  51,  51, 255 );
const COLORREF  COLOR_WHITE         = RGB( 255, 255, 255 );

//////////////////////////////////////////////////////
// 宣告 Site Setting 結構 
// Site Setting
typedef struct tagSite{
//	bool bSiteEnable[_Site_No];
	long iRunMode;				 // the default value is on-line, we never save
	double dDemoTestTime;        // Demo Test Time
	long iSiteDummyBinForCatorgy;
	CString csSiteDummyBinForCatorgy;
} tagSite;

/////////////////////////////////////////////////////////
// 宣告 Yield Setting 結構 
// Yield Setting.
typedef struct tagYieldSetting{

	int	bYieldControlEnable;    // Yield Control Enable/Disable					 @bEnableYieldControl
	double dYieldLimit;         // Yield Limitation								 @dYieldLimit
	long iYieldWindow;          // Yield Control Quantity Condition				 @iYieldWindow			

	int	bContinueFailEnable;    // Continue Fail Enable/Disable
	long iFailCount;            // Continue Fail Counter
	long iRetestCount;          // Retest Count	

	int bDropMode;				// Yield Control Enable/Disable 
	// Note: 
	// if value == 1. 
	// It will enable Drop IC to socket. 
	// if value == 0. 
	// Test site will let IC direct contact to socket

	double dDropHigh;			// Drop Mode High
	double dDropTimer;			// Drop Mode Timer
} tagYieldSetting;

////////////////////////////////////////////////
// 宣告 Thread Count 結構 
// Thread Montior
typedef struct tagThreadCode{
	long times;					// Run Times
	long line;					// Witch stamtment
	long info;					
} tagThreadCode;

////////////////////////////////////////////////
// 宣告 ErrorParam 結構
typedef struct tagErrorMsg {
	long Code;				// 0
	CString Eng;			// 1
	CString Chi;			// 2
	CPoint p;				// 3.4
	long Level;				// 5
	bool Stop;				// 6
	bool Alarm;				// 7

	bool InitialNeed;		// 8
	CString EngProcess;		// 9
	CString ChiProcess;		// 10

	// Enable Button / Disable.
	bool BStart;			// 11
	bool BStop;				// 12
	bool BRetry;			// 13
	bool BSkip;				// 14
	bool BTrayChange;		// 15
	bool BInitial;			// 16
	bool BOneCycle;			// 17
	bool BOverride;			// 18
	bool BTestSiteSkip;		// 19
} tagErrorMsg;

////////////////////////////////////////////////
// 宣告EventLog ErrorParam 結構
typedef struct tagErrorParam {
	long Time;			//紀錄時間
	long Code;			//錯誤代碼
	long Result;		//狀態
} tagErrorParam;

////////////////////////////////////////////////
// 宣告 MotorParam 結構
typedef struct tagMotorParam{
	unsigned char	BoardID;
	unsigned char	AxisNo;
	bool			nLMT;
	bool			pLMT;
	bool			EMG;
	bool			Alarm;
	bool			InPos;
	bool			InPosReal;
	bool			ZPhase;
	bool			ZeroSpeed;
	bool			TLC;
	bool			DRV;
	bool			ERRR;
	long			RCount;
	long			LCount;
	long			Start;
	long			MaxSpeed;
	long			Accelerate;
	long			Multiple;
	long			Speed;
	long			InPosRange;
	bool			ServoOn;
	long			DrifSpeed;
	long			SearchSpeed;
	long			Jerk;
	bool			nLMTStop;
	bool			pLMTStop;
	bool			ZPhaseStop;
	bool			TLCStop;
	bool			Reverse;	// Face the motor axis, counter-clock is +
	bool			TL1;		// Torque 轉換IO(O5) 
} tagMotorParam;	

////////////////////////////////////////////////
// 宣告 Bin 結構
typedef struct tagBinMapping{
	CString software;
	CString code;
	CString description;
	bool	pass;
	int		color;
	int		hardware;
} tagBinMapping;

////////////////////////////////////////////////
// 宣告 Tray 結構
typedef struct tagTraySpec{
	double		A;	// mm
	double		B;	// mm
	double		C;	// mm
	double		D;	// mm
	long		Column;
	long		Row;
	double		PlateA;
	double		PlateB;
	double		PlateC;
	double		PlateD;
	long		PlateColumn;
	long		PlateRow;
	double		XRatio; // pulse/mm
	double		YRatio; // pulse/mm
	int			Heating;
	CString		BinMappingFile;
	bool		ThickTrayMode;
	bool		NoBootRetest;

	int			Cooling;
	int			SortMode;
	CString		VisionPatternName;

	// Mapping and Testing record in TrayFile
	CString		MappingName;
	CString		TestingName;

	double      TrayHeight;  // for double tray detect

	// Chip Tray
	long		m_SubTrayColumn;
	long		m_SubTrayRow;
	double		m_SubTrayA;
	double		m_SubTrayB;
	double		m_SubTrayC;
	double		m_SubTrayD;
	
	long		m_SubChipTrayColumn;
	long		m_SubChipTrayRow;
	double		m_SubChipTrayA;
	double		m_SubChipTrayB;
	double		m_SubChipTrayC;
	double		m_SubChipTrayD;

	int			m_InputUseChipTray;
	int			m_OutputUseChipTray;
	int			m_FixUseChipTray;

	// Ocr feature
	CString		VisionOcrPatternName;

} tagTraySpec;

////////////////////////////////////////////////
// 宣告 Software Setting 結構
typedef struct tagSetting
{
	int	  m_bA4P;		// if true application will use A4P Pansonic Driver.!
	int	  m_bCCD;							// if true application will use CCD
	int	  m_bSocketCCDDoubleDetect;				// if true application will user CCD Double Device Detect
	int	  m_bPin1CCDDoubleDetect;	

	int	  m_iRepeatMaxiumValue;				// if Repeat Maxium
	//
	int	  m_bEnableDoorSensor;				// if true application will disable door sensor
	//
	int	  m_iTorqueHighLimit;				// This is for torque low torque high Limit
	int	  m_iTorqueLowLimit;				// This is for torque high torque low Limit
	//
	int	  m_iSpeedLowLimit;					// This is for speed dialog speed low Limit
	int   m_iSpeedHighLimit;				// This is for speed dialog speed high Limit
	//
	double  m_dTimerHighLimit;				// This is for Timer dialog secs high Limit
	double  m_dTimerLowLimit;				// This is for Timer dialog secs low Limit
	//
	double	m_dTimeoutHighLimit;			// This is for communication dialog secs high Limit
	double  m_dTimeoutLowLimit;				// This is for communication dialog secs low Limit
	//
	double  m_dBuzzerAutoClose;				// This is for Buzzer auto close
	//
	double	m_dOffsetHighLimit;				// This is for offset dialog mm low Limit
	double  m_dOffsetLowLimit;				// This is for offset dialog mm high Limit
	//
	double	m_dTestSiteProf;				// This is for Test Site Prof distance
	//
	double	m_dTraySpecLeftSide;			// This is for TrayMap Dialog. Each IC display adjust. (CRect Left)
	double	m_dTraySpecTopSide;				// This is for TrayMap Dialog. Each IC display adjust. (CRect Top)
	double  m_dTraySpecICSide;				// This is for TrayMap Dialog. Each IC display adjust. Distance with CRect 
	double  m_dTraySpecTextUpSide;			// This is for TrayMap Dialog. Each IC display adjust.
	double  m_dTraySpecTextLeftSide;		// This is for TrayMap Dialog. Each IC display adjust.
	int		m_iTraySpecTextSize;			// This is for TrayMap Dialog. Each IC display adjust.
	int		m_iTraySpecTextBreak;			// This is for TrayMap Dialog. Each IC display adjust.
	int		m_iTraySpecBkColor;				// This is for TrayMap Dialog. Background Color
	//
	int		m_bRotatoUse;					// This is for SLT function. If use it. Test Site will have rotota function.
	int		m_bEnableRotatorPreGuide;		// Enable Rotator PreGuide, 1 is enable, 0 is not enable..
	int		m_bEnableRotatorTurn;			// Enable Rotator 180 degree, if enable, Rotator Support 180..
	int		m_bEnableATCModule;				// Enable ATC Module
	int		m_bEnablePTCModule;				// Enable PTC Module
	int		m_bEnableTriTempModule;			// Enable Tri-Temperature Module
	int		m_bEnableHeaterModule;			// Enable Heater Module
	int		m_bEnableRemoteModule;			// Enable Remote Module
	int		m_bEnableRemoteIO;				// Enable Remote IO
	int		m_bEnableCCDPin1;				// Enable CCD Pin1
	int		m_bEnableCCDSocket;				// Enable CCD Socket
	int		m_bEnableCCDLogICImage;			// Enable CCD Log IC Image
	int		m_bEnableRemoteControl;			// Enable Remote Control
	int		m_bEnableLotDoneProgress;		// Enable Lot Done Progress.
	//
	int		m_bEnableAlarm;					// if true. application will Normal ststus.
	//
	int		m_bByPassVacc;					// if true. application will by Pass check Vacc success.
	int		m_bByPassTestVacc;				// if true. application will byPass TestVacc check
	int		m_bByPassRotatorAlarm;			// if true. application when Demo Mode. TestSite will not turn off Vacc
	int		m_bByPassTrayInPos;				// if true. application will byPass Tray In Pos
	int		m_bByPassShuttleAlarm;			// if true. application will byPass Shuttle error
	//
	int		m_bEnableSaveSiteSetting;		// if true. application will save site setting.
	int		m_bByPassEnableIORecovery;		// if true. application will enable IO Monitor Recovery 
	//
	int		m_bSetByMode;					// if true. application will force setting by Run Mode / Demo / Offline / Online.
	// 
	int		m_bEnableSimplified;			// if true. application will show simplified chinese for chinese language
	//
	int		m_bShowContactCounter;			// Show TS Contact Counter information in Run Page
	int		m_bSummaryReport;				// Show Summary Report 
	int		m_bEnableChipTray;				// if true. Enable Chip Tray Function in TrayFile
	//
	int		m_bInitialPreMove;				// After Initial Arm X Move Enable
	int		m_iInitialPreMoveDistance;		// After Initial Arm X Move Distance
	//
	double	m_dStandyX;						// Standy X distance 
	double  m_dStandyY;						// Standy Y distance
	//
	double	m_dTestSiteStandbyPosition;		// Test Site Standby position
	double  m_dTestSiteSocketStandyPos;		// Test Site Socket position
	// 
	bool	m_bPreMove;						// Enable Arm XY Pre-Move Function
	int		m_iPreMoveDistance;				// Define Arx XY Pre-Move Distance(mm)
	//
	int		m_iTestSiteStandByDistance;		// It is for TestSite Pick IC from Shuttle Input / StandBy Position adjust
	int		m_bCustomAlarmMail;				// Alarm Mail
	int		m_iAutoRetrySetting;			// Auto Retry Setting
	//
	int		m_bArmZAutoRetry;				// Enable Arm Z Auto Retry
	//
	int		m_bEnableTSRemainIC;			// Enable Test Site Remain IC
	//
	int		m_bIONAlarm;					// Enable ION Alarm.
	// Log Enable flag
	int		m_bEnableUPHLog;				// if true. application will Log UPH value
	int		m_bEnableCommLog;				// if true. application will Log Commcation Log / RS232 / TTL / GPIB
	int		m_bEnableSingleMotorLog;		// if true. application will Log Single Speed Log.
	int		m_bEnableDualMotorLog;			// if true. application will Log Motor Run Line Log
	int		m_bEnableGpibLog;				// if true. application will Log Gpib Log
	int		m_bEnableMotorLog;				// if true. application will Log Motor Log
	int		m_bEnableStatusLog;				// if true. application will Log Handler Status Log
	int		m_bEnableAutoKLog;				// if true. application will Log Auto K TS Height RCount / LCount
	int		m_bEnableStatusReportLog;		// if true. application will Log Report Status
	int		m_bEnableCCDSocketLog;			// if true. application will Log CCD Socket
	int		m_bEnableJamRateReport;			// if true. application will Log Jam Report
	int		m_bEnableShuttleJamLog;			// if true. application will Log Shuttle Jam 
	//
	int		m_bEnableICMissingDetect;		// IC Missing Detect Enable..
	int		m_bInputTrayTips;				// Input Enable Tips.
	int		m_bInputTrayTipsNumber;			// Input Enable Number 
	int		m_bInputTrayInfo;				// Input Enable Info
	int		m_bRemoteCustomInput;			// Remote Control Input
	int		m_bEnableTorqueCtrl;			// Torque Control
	int		m_bEnableTorqueStatus;			// Torque Status
	int		m_bCancelDoubleChkChange;		// When press cancel, if change value, 1 will check with user, else not.
	int		m_bShowHandlerStatus;			// Show Handler Status
	int		m_bEnableProgramInitialStart;	// Show Program Initial Start
	int		m_bEnableRepeatTrayStatus;		// Show Repeat Tray Status
	int		m_bEnableAutoSelLastTrayFile;	// Enable Auto Select TrayFile After Lot Done
	int		m_bEnableAutoCopyLastLotInfo;	// Enable Auto Copy Last Information
	bool	m_bEnableSemiAuto;				// Enable SemiAuto
	int		m_iSemiAutoIndex;				// SemiAuto IC Index
	CString	m_csSemiAutoFileName;			// SemiAuto File Name

}tagSetting;

////////////////////////////////////////////////
// 宣告 Software Setting 結構
typedef struct tagSimulationSetting{
	// Debug Log Option.
	int	m_bDLArm;			// Enable Log Option	
	int	m_bDLTestSite;		// Enable Log Option
	int	m_bDLInspect;		// Enable Log Option	
	int	m_bDLTester;		// Enable Log Option
	int m_bDLManual;		// Enable Log Option
	int m_bDLWest;			// Enable Log Option
} tagSimulationSetting;

////////////////////////////////////////////////
// 宣告 Timer 結構 (一種Tray 一種 Timer 設定)
typedef struct tagTimer{	
	double m_dInsertPuff;
	double m_dInsertPick;
	double m_dPickPuff;
	double m_dPickPick;	
} tagTimer;



////////////////////////////////////////////////
// 宣告 IO input 結構
typedef struct tagInput
{	
	unsigned char Emg;							// .00	 Emg button
	unsigned char ArmZVaccSensor;				// .01	 Check Arm Vacc sensor
	unsigned char AirSourceDetect;				// .02	 Air Source Detect
	unsigned char DoorSensor;					// .03	 Door Sensor
	unsigned char TestSiteZVaccSensor;			// .04	 Check Test Site Vacc sensor
	unsigned char ShuttleInputJam;				// .05	 Check Shuttle Input Jam
	unsigned char TestSiteSkip;					// .06	 Test Site skip
	unsigned char IONAlarm;						// .07	 ION Alarm
	unsigned char ShuttlePLmt;					// .08	 Shuttle Move P Lmt
	unsigned char ShuttleNLmt;					// .09	 Shuttle Move N Lmt
	unsigned char InputTrayInPos;				// .10	 Input Tray InPos sensor
	unsigned char OutputTrayInPos;				// .11	 Output Tray InPos sensor
} tagInput; 

////////////////////////////////////////////////
// 宣告 Remote IO input 結構
typedef struct tagRemoteInput
{
	// Handler Panel
	unsigned char BtnStartPushed;				// .00	 Check Panel Start pushed or Not
	unsigned char BtnStopPushed;				// .01	 Check Panel Stop pushed or Not
	unsigned char BtnSkipPushed;				// .02	 Check Panel Skip pushed or Not
	unsigned char BtnRetryPushed;				// .03	 Check Panel Retry pushed or Not
	unsigned char BtnResetPushed;				// .04	 Check Panel Reset pushed or Not
	unsigned char BtnInitialPushed;				// .05	 Check Panel Initial pushed or Not
	unsigned char BtnOneCyclePushed;			// .06	 Check Panel OneCycle pushed or Not
	//	
	unsigned char RotatorICMissing;				// .07	 Rotator IC Missing sensor
	unsigned char RotatorICJam;					// .08	 Rotator IC Jam sensor
	unsigned char RotatepLmt;					// .09	 Rotator P Lmt sensor				  
	unsigned char RotatenLmt;					// .10	 Rotator N Lmt sensor	
	//
	unsigned char Unuse11;						// .11	 Unuse
	unsigned char Unuse12;						// .12	 Unuse
	unsigned char Unuse13;						// .13	 Unuse
	unsigned char Unuse14;						// .14	 Unuse

} tagRemoteInput;

////////////////////////////////////////////////
// 宣告 IO Onput 結構
typedef struct tagOutput{
	unsigned char ArmVacc;						// 00	Set Arm Vacc turn on, 1 is turn on, 0 is turn off
	unsigned char ArmBlow;						// 01	Set Arm Blow turn on, 1 is turn on, 0 is turn off
	unsigned char TestSiteVacc;					// 02	Set Test Site Z Vacc turn on, 1 is turn on, 0 is turn off
	unsigned char TestSiteBlow;					// 03	Set Test Site Z Blow turn on, 1 is turn on, 0 is turn off
	unsigned char Shuttle;						// 04	Set Shuttle active				  
	unsigned char TestSiteSkip;					// 05	Set TestSite Skip Button Led On
	unsigned char TowerRedOn;					// 06	Set Tower Red light on
	unsigned char TowerYellowOn;				// 07	Set Tower Yellow light on
	unsigned char TowerGreenOn;					// 08	Set Tower Green light on
	unsigned char TowerBuzzerOn;				// 09	Set Tower Buzzer light on
//	unsigned char HeaterOn;						// 10	Set Heater On
	unsigned char ATXPower;						// 10	Set Heater On
	unsigned char Tester;						// 11	Set Tester active
} tagOutput;

////////////////////////////////////////////////
// 宣告 IO Remote Onput 結構
typedef struct tagRemoteOutput{
	// Handler Panel
	unsigned char BtnStartOn;				 // 00	Set Panel Start light on
	unsigned char BtnStopOn;				 // 01	Set Panel Stop light on
	unsigned char BtnSkipOn;			     // 02	Set Panel Skip light on
	unsigned char BtnRetryOn;				 // 03	Set Panel Retry light on
	unsigned char BtnResetOn;				 // 04	Set Panel Reset light on
	unsigned char BtnInitialOn;				 // 05	Set Panel Initial light onOne Cycel light on
	unsigned char BtnOneCycleOn;			 // 06	Set Panel One Cycel light on
	unsigned char Rotator;					 // 07	Set Rotator
	unsigned char HeaterOn;					 // 08	Heater On
	unsigned char Unuse09;					 // 09	Unuse
	unsigned char Unuse10;					 // 10	Unuse
	unsigned char Unuse11;					 // 11	Unuse
	unsigned char Unuse12;					 // 12	Unuse
	unsigned char Unuse13;					 // 13	Unuse
	unsigned char Unuse14;					 // 14	Unuse
} tagRemoteOutput;
////////////////////////////////////////////////
// 宣告 Test Site 結構
typedef struct tagTestSite{
	double home;		// store test site motor home RCount
	double pick;		// store test site motor pick IC from dut shuttle RCount
	double place;		// store test site motor place IC to dut shuttle RCount
	double contact;		// store test site motor press IC in tester socket
} tagTestSite;

typedef struct tagXYZ{
	double x;			// store motor Arm X RCount
	double y;			// store motor Arm y RCount
	double z;			// store motor Arm z RCount
	double z2;			// store motor Arm z RCount for Place
} tagXYZ;

typedef struct tagArm{
	double x;			// store motor Arm home x RCount ( refer stack output backward position (Arm standby position) )
	double y;			// store motor Arm home y RCount
	double z;			// store motor Arm home z RCount
} tagArm;

/////////////////////////////////////////////////////////////////////////
// Motor Run.
// When motor run. The position is below

// Alignment + Offset * GearRation  = Current Position.!
// GearRation = 1 mm  = 200 pulse. Or 0.5 mm = 100 pulse.
// For example : 1000 pulse + ( 3 mm * 200 pulse ) = Current Position.
// Refer : theApp.m_Align.TestSite[m_ID].pick + m.Offset.TestSite[m_ID].pick * theApp.m_Ratio.TestSite
typedef struct tagShuttle{
	double exchange;	// store motor shuttle home RCount
	double output;		// store motor shuttle output RCount
	double input;		// store motor shuttle input RCount
} tagShuttle;

typedef struct tagAlignment{
	tagTestSite TestSite;	// Test site position
	tagXYZ Input;			// Arm in Input Stack position
	tagXYZ Output1;			// Arm in Output1 position
	tagXYZ Rotator;			// Arm in Rotator position
	tagXYZ Socket;			// Arm in Rotator position
	tagXYZ Shuttle;			// Arm in Rotator position
	
	tagShuttle Shuttle2;		// Shuttle work position

	// calc
	tagXYZ StandyBy;		// Arm in StandBy position
	tagXYZ DutIn;			// Arm in DutShuttle position
	tagXYZ DutOut;			// Arm in DutShuttle position

} tagAlignment;
// Pulse

typedef struct tagOffset{
	tagTestSite TestSite;	// Test site position
	tagXYZ Input;			// Arm in Input Stack position
	tagXYZ Output1;			// Arm in Output1 position
	tagXYZ Rotator;			// Arm in Rotator position
	tagXYZ Socket;			// Arm in Rotator position

	// calc
	tagXYZ StandyBy;		// Arm in StandBy position
	tagXYZ DutIn;			// Arm in DutShuttle position
	tagXYZ DutOut;			// Arm in DutShuttle position

} tagOffset;
// mm 

//////////////////////////////////////////////////////
// Tray Map Record
typedef struct tagTrayMap{
	CPoint pos;							// Col. Row				// 畫在 TrayMap 的座標
	int StackNo;						// Witch StackNo		// 目前第幾個 Stack
	CString code;						// Bin Code				// 該位置的 Bin Code
	int site;							// Whitch site tested	// 是第幾個 Site 測的
	double temperature;					// Temperature			// 來自 IC 的溫度
} tagTrayMapLog;

// 在發生 Error 或 Lot Done 可以寄出 Mail
typedef struct tagMailSetting{
		CString csSMTPServer;	// ex: "smtp.mail.yahoo.com"
		int		iSMTPPort;		// ex: 25
		CString csSMTPUserName;	// ex: xxx
		CString csSMTPPassword;	// ex: xxx
		CString csMailFrom;		// source mail address. ex: jim.superman@yahoo.com
		CString csMailTo1;		// desation mail address. ex: ken.liang@chroma.com.tw
		CString csMailTo2;		// desation mail address. ex: ken.liang@chroma.com.tw
		/* Jim send the mail to Ken */

		CString csMailSubject;	
		CString csContent1;		// Line1 Content
		CString csContent2;		// Line2 Content
		CString csShowName;		// Source Mail Show Name
} tagMailSetting;

//
typedef struct tagMailCmd{
	CString csEventTime;
	CString csCode;
	CString csDesc;
} tagMailCmd;

// Error Rate Report
typedef struct tagRateDataLogData{
	int iCode;
	int iCount;
} tagRateDataLogData;

// Auto Retry Adjust Value
typedef struct tagAutoRetryAdjsutValue{
	int iAlwaysAdjsut;
	double dAdjustValue;	// mm
} tagAutoRetryAdjsutValue;

//
typedef struct tagTestLog {
	CString csCode;			// BinMap Code.		// 測試結果的字串, 從通訊來
	int iSetTemperature;	// Test Temperature	// 由IC自我測試量測出來的,然後由通訊送給Handler
	int iBin;				// BinMap SW Bin	// 解析 Catrogy 後, 拿測試結果的字串 mapping後取得 Hardware Bin
	int iBooking;			// Booking number	// 由 Input Tray 取 IC 的位置
	double dTestTime;		// Test Time		// 測試時間 秒數
	bool bError;			// GPIB				// 通訊是否 Error
	int	iTray;				// Tray				// 該 IC 是從哪裡來, Tray1=0, Tray2=1
	int iPF;				// PF				// 目前該 IC 是 Pass, 還是 Fail, 1=Pass, 0=Fail
} tagTestLog;

typedef struct tagTestSetting{
	int m_TestType;		// 0: RS232, 1: TCP/IP
	//
	int m_CCDUse;		// if true, enable CCD
	int m_RotatorUse;	// if true, enable Rotator
	int m_CCDSocketUse;	// if true, enable CCD Socket
	//
	int m_Angle;		// record degree
} TestSetting;

typedef	struct tagCategorySetup{
	COLORREF iOutputColor[_Output_Stack_No]; // RGB color
} tagCategorySetup;

// Bin Color
typedef struct tagBinColor 
{	
	int		item;
	int		color;
} tagBinColor;

// West Control
typedef struct tagWestControllerList
{
	long m_lID;
	CString csFunctionName;
} tagWestControllerList;

// Handler Com Port
typedef struct tagHandlerComPort
{	
	int iPortPIDValue;		// PID
	int iIDPIDValue;		// PID
	int	iPortTester;		// Tester Port (RS232)
	int iPortATCModule;		// ATC Module Port
	int iPortWest;			// West Port
	int	iPortWestHeaterID;	// West Heater ID
	int iPortIOModule;		// IO Module Port
	int	iIDIOModuleIDIn;	// IO Module ID (input)
	int iIDIOModuleIDOut;	// IO Module ID (output)
	int iPortTorqueStatus;	// Test site Torque Port
	int iPortRemoteCom;		// Remote Port
} tagHandlerComPort;

typedef struct tagContactForce
{
	long lPower;
} tagContactForce;

// Interface Enable
typedef struct tagInterfaceEnable
{
	int m_bEnableRs232;
	int m_bEnableTcp;
	int m_bEnableGpib;
	int m_bEnableTTL;
} tagInterfaceEnable;

// Input Tray Data for Load File....
typedef struct tagInputTrayDataFile{
	int ipos;
	int status;
} tagInputTrayDataFile;

////////////////////////////////////////////////
// 宣告 RS232參數 結構
typedef	struct tagIfRs232Setting{	
	CString	m_csCmdHeader;		// Ex: <<
	CString	m_csCmdTailHeader;	// Ex: >>
	CString m_csCmdReady;		// Ex: Ready
	CString m_csCmdStart;		// Ex: Start 
	CString m_csCmdGo;			// Ex: Go
	CString m_csCmdBin;			// Ex: Bin
	double	m_dCmdTimeout;		//
	double  m_dSendStartDleay;	// 
} tagIfRs232Setting;

////////////////////////////////////////////////
// 宣告 TCP參數 結構
typedef	struct tagIfTcpSetting{	
	CString	m_csCmdHeader;		// Ex: <<
	CString	m_csCmdTailHeader;	// Ex: >>
	CString m_csCmdReady;		// Ex: Ready
	CString m_csCmdStart;		// Ex: Start 
	CString m_csCmdGo;			// Ex: Go
	CString m_csCmdBin;			// Ex: Bin
	double	m_dCmdTimeout;		//
	double  m_dSendStartDleay;	//
} tagIfTcpSetting;

////////////////////////////////////////////////
// 宣告 GPIB參數 結構
typedef struct tagGPIBParameter {

	int m_iGpibPort;
	int m_iGpibAddr;
	int m_iBinBase;

	double m_dSendStart;
	double m_dTimeout;

	// for single site
	int	   m_Site;

} tagGPIBParameter;

////////////////////////////////////////////////
// 宣告 TTL參數 結構
typedef struct tagTTLParameter {
	int s_iBinAssertion;
	int s_iEOTAssertion;
	int s_iRDYAssertion;
	int s_iRDYMode;
	int s_iLineMode;
	int s_iSiteAddress[4];
	int s_iSiteMask[4];

	double	s_dStartDelay;
	double	s_dTimeout;
	int		s_iPowerMode;		
} tagTTLParameter;

////////////////////////////////////////////////
// 宣告 UPH 結構
typedef struct tagUPHData {
	CArray <long, long> m_TSCalc;
} tagUPHData;

////////////////////////////////////////////////
// 宣告 Log Information Progress 結構
typedef struct tagLotProgressData {
	CString m_csLotInformationInfo;
	long m_lLotInformationStatus;
	bool m_bLotInformationDone;
} tagLotProgressData;

////////////////////////////////////////////////
// 宣告 Heatr Temperature 結構
typedef struct tagHeaterParam {
	double dSetPoint;
	double dStableTime;
	double dSoakTime;
	double dTolerance;
} tagHeaterParam;

////////////////////////////////////////////////
// 宣告 Page Enable 結構
// User Page Enable
typedef struct tagUserPageEnable{
	bool m_bEnableSummaryReport;
	bool m_bEnableManualContact;
	bool m_bEnableDeviceSetup;
	bool m_bEnableSiteSetting;
	bool m_bEnableVisualPanel;
	bool m_bEnableLotInformation;
	bool m_bEnableAutoSkip;
	bool m_bEnableYieldCtrl;
	bool m_bEnableIfTesting;
	bool m_bEnableTrayMapReport;
	bool m_bTestSiteVaccOn;
	bool m_bTestResultReport;
	bool m_bRepeatTrayStatus;
	bool m_bTrayDefColor;
	bool m_bArmLogICImage;
	bool m_bSLTProtocol;
} tagUserPageEnable;

// Setup Page Enable
typedef struct tagSetupPageEnable{
	bool m_bEnableOffset;
	bool m_bEnableSpeed;
	bool m_bEnableTimer;
	bool m_bEnableEventLog;
	bool m_bEnableSiteSetting;
	bool m_bEnableYieldCtrl;
	bool m_bEnableAutoRetry;
	bool m_bEnableDeviceSetup;
	bool m_bEnableTrayFile;
	bool m_bEnableIfTesting;
	bool m_bEnableCatoregy;
	bool m_bEnableInterface;
	bool m_bEnableRemoteControl;
	bool m_bEnableRemoteInput;
	bool m_bEnableInputTray;
	bool m_bEnableOutputTray;
	bool m_bEnableIOMonitor;
	bool m_bEnableAlignment;
	bool m_bEnableInOutTray;
	bool m_bEnableRepeatTray;
	bool m_bEnableTowerSetting;
} tagSetupPageEnable;

// Engineer Page Enable 
typedef struct tagEngineerPageEnable{
	bool m_bEnableMotorMon;
	bool m_bEnableIOMonitor;
	bool m_bEnableAlignment;
	bool m_bEnableEventLog;
	bool m_bEnableSocketCCD;
	bool m_bEnableSpeed;
	bool m_bEnableTSCounter;
	bool m_bEnableChangeFile;
	bool m_bEnableLoopTest;
	bool m_bEnableAlarmMail;
} tagEngineerPageEnable;

// Manual Contact Enable 
typedef struct tagManualContactEnable{
	bool m_bEnableTorqueControl;
	bool m_bEnableTemperatureControl;
	bool m_bEnableInterfaceTesting;
	bool m_bEnableOffsetControl;
	bool m_bEnableTestDirectContact;
	bool m_bEnableTestSiteVacc;
} tagManualContactEnable;

// TS Remain IC Parameter
typedef struct tagTSRemainICParameter{	
	double dTSRemainICVacc;
	int	   iTSRemainICAlwaysOn;	// 1 for always on, 0 for not always on
	int	   iTSRemainICSpeed;	//
	bool   bTSRemainICflag;		// true for next time press start will run TSRemain IC process
} tagTSRemainICParameter;

// Torque Control
typedef struct tagTsFloatingParameter{
	int iPogoCount;
	int iPogoForce;
	int iPogoTorqueForce;
} tagTsFloatingParameter;

// Torque Control Convert
typedef struct tagTsFloatingConvert{
	double dTsFloatingConvert;
} tagTsFloatingConvert;

// Test Site Heater Soak
typedef struct tagTsHeaterSoak{
	long lSoakStart;
} tagTsHeaterSoak;

/*
// It is for Interface header and tail format
typedef	struct tagInterfaceSetting{	
	CString	m_csCommandHeader;		// Ex: <<
	CString	m_csCommandTailHeader;	// Ex: >>
	CString m_csCommandReady;		// Ex: Ready
	CString m_csCommandStart;		// Ex: Start 
	CString m_csCommandGo;			// Ex: Go
	CString m_csCommandBin;			// Ex: Bin
	double	m_dCommandTimeout;		//
} tagInterfaceSetting;
*/

// It is for output yield
typedef struct tagOutputYield{
	CString m_csCode;
	long m_lCodeCounter;
} tagOutputYield;
	
// Custom File Path
typedef struct tagCustomFilePath{			
	CString MultiSVProgramExportPath;	// Multi SV
	CString MultiSVTestReportPath;		// Multi SV
	CString MultiSVTrayMapFilePath;		// Multi SV
	CString LoopTestResultReportPath;	// Loop Test	
	CString EventLogReportPath;			// Event Log	
	CString TrayMapReportPath;			// TrayMap Report
	CString UPHReportPath;				// UPH Tool
	CString SLTProtocolPath;			// SLT Protocol 
} tagCustomFilePath;

// Tray Map Report Data
typedef struct tagTrayMapReportData{
	int x;
	int y;
	CString code;
	int book;
} tagTrayMapReportData;

// Manual Contact Ts Direct Contact
typedef struct tagManulContactMode{
	int bIsTsDirectContact;	// 1 for direct contact, 0 for user place ic to shuttle
	int bIsTsKeepVaccOn;	// 1 for close Vacc, 0 for default(Vacc always on)
} tagManulContactMode;

// Vision Function
typedef struct tagInfoParameter {	
	int iX;					// Left
	int iY;					// Top
	int iWidth;				// Right
	int iHeight;			// Bottom
	double dScore;			// Score
} tagInfoParameter;

// TrayFile Color
typedef struct tagTrayFileDefColor {
	COLORREF m_colHeater;
	COLORREF m_colAmbit;
	COLORREF m_colATCModule;
	COLORREF m_colTriTemperature;
	COLORREF m_colPTCModule;
	COLORREF m_colRemoteModule;
} tagTrayFileDefColor;

// Really time torque status
typedef struct tagTorqueStatus{
	double dTorqueRation;	// Drive force (%) -> Kgf rate
} tagTorqueStatus;

// Repeat Tray Enable 
typedef struct tagEnableRepeatTray{
	bool m_bNone;
	bool m_bInOutCtrl;
	bool m_bTrayBinningCtrl;
} tagEnableRepeatTray;

// Repeat Tray Function
typedef struct tagRepeatTrayCtrl {
	int	m_iRepeatTrayMode;	// 0 is none
} tagRepeatTrayCtrl;

// Repeat Tray Input/OutputCtrl
typedef struct tagRepeatInOutCtrl {
	int m_iTray1;
	int m_iTray2;
	int m_iRepeatTimes;				// for ambient
	int	m_iRepeatConfimFromComm;	// for control temperature
} tagRepeatInOutCtrl;

// Repeat Tray Temperature Data
typedef struct tagRepeatTemperData {
	double m_dSV;
	double m_dStableTime;
	double m_dSoakingTime;
	double m_dTolerance;
} tagRepeatTemperData;

// Repeat Tray, Data
typedef struct tagRepeatTrayDATA {
	int m_NowCount;				// 0~n
	bool m_bRepeatIsTray1;		// Both, Both mode, true for tray1, false for tray2
	bool m_bIsOneCyclePress;	//
} tagRepeatTrayDATA;

// Repeat Tray, Command
typedef struct tagRepeatConfimCmd {
	CString m_csBook;
	CString m_csSV;
	CString m_csSoakTime;
	CString m_csStableTime;
	CString m_csTolerance;
	double m_dTimeout;
} tagRepeatConfimCmd;

// 1.0Af
typedef struct tagTowerLightInd{
	int LightRedChoise;
	int LightYellowChoise;
	int LightGreenChoise;
} tagTowerLightInd;

// 1.0Af
typedef struct tagTowerSetupSetting{
	double dBlinkTime[_MaxTowerBlink];	// blink flash timer
	// 0-Disable, 1-Enable, 3-Blink1, 4-Blink2, 5-Blink3, 6-Blink4, 7-Blink5	
	tagTowerLightInd Uninitial;		// Uninitial 
	tagTowerLightInd Initial;		// Initial
	tagTowerLightInd Ready;			// Ready
	tagTowerLightInd Cycle;			// Cycle
	tagTowerLightInd CycleStop;		// Cycle Stop
	tagTowerLightInd OneCycle;		// One Cycle
	tagTowerLightInd OneCycleStop;	// One Cycle Stop
	tagTowerLightInd Override;		// Override
	tagTowerLightInd OverrideStop;	// Override Stop
	tagTowerLightInd Manual;		// Manual
	tagTowerLightInd ManualStop;	// Manual Stop
} tagTowerSetupSetting;

// 1.0Af
// Arm Log Image
typedef struct tagArmLogICImage{
	int bEnableArmLogICImage;
	CString csImageFilePath;
	double dCaptureStableTime;
	bool bKeepSourceImage;
} tagArmLogICImage;

// 1.0Af
typedef struct tagLastTrayData{
	CString FileMain;
	CString FileMainMapping;
	CString FileMainTestSetting;	
	CString VisionPatternName;
	CString VisionOcrPatternName;
} tagLastTrayData;

// 1.0Ah
typedef struct tagTitleExtendNote{
	CString TitleTrayExtendNote;
	CString TitleMachineExtend;
} tagTitleExtendNote;

// 1.0Ak
typedef struct tagRemoteCtrlFun{
	int m_iAutoReplayEvent;
} tagRemoteCtrlFun;











