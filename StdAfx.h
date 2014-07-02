// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__18A27D27_37E2_479A_8CE7_47F14CB2EE80__INCLUDED_)
#define AFX_STDAFX_H__18A27D27_37E2_479A_8CE7_47F14CB2EE80__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#pragma warning (disable : 4786)

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdisp.h>        // MFC Automation classes
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

#include "BtnST.h"

// GDIPlus
#define ULONG_PTR unsigned long
#include <Gdiplus.h>
using namespace Gdiplus;

////////////////////////////////////////////////////////////////////////////////
// enum

// Button status
enum enButton
{	
	enBtnInitial		= 1,
	enBtnStart			= 2,
	enBtnStop			= 3,
	enBtnOncycle		= 4,
	enBtnSkip			= 5,
	enBtnRetry			= 6,
	enBtnReset			= 7,
	enBtnTestSiteSkip	= 8,

};

enum enSensorFlag {enZPhase, enTLC};

// Constant status
enum enStatus {enAbort};

// User level
enum enUserLevel
{
	enLevelInitial		= 0,
	enLevelRun			= 1,
	enLevelUser			= 2,
	enLevelSetup		= 3,
	enLevelEngineer		= 4,
	enLevelSuperUser	= 5,
};

// UPH Report
enum enUPHToolReport
{
	enUPHExportNone		= 0,
	enUPHExportTsSel	= 1,
};

// Error code list
enum enErrorCode
{
	enCodeRunOK								= 0x0,	 // 00
	enCodeRunCancel							= 0x1,	 // 01
	
	// About System
	enCodeSystemStartUp						= 0x2,	 // 02
	enCodeSystemShutDown					= 0x3,	 // 03

	// Door Alarm
	enCodeFrontDoor							= 0x4,	 // 04

	// Initial Error Code ( 50 - 100 )
	enCodeArmZInitialhaveIC					= 0x32,	 // 50 
	enCodeTSArmZInitialhaveIC				= 0x33,	 // 51

	// Dlg Open Or Function
	// #1: Run Page.
	enCodeRunPageTrayMap					= 0xc8,	 // 200
	enCodeRunPageLotInformation				= 0xc9,	 // 201
	enCodeRunPageLotDone					= 0xca,	 // 202
	enCodeRunPageYieldControl				= 0xcb,	 // 203
	enCodeRunPageIOMonitor					= 0xcc,	 // 204
	enCodeRunPageEventLog					= 0xcd,	 // 205
	enCodeRunPageClearCount					= 0xce,  // 206

	// #2: User Page
	enCodeUserPageYieldControl				= 0xdc,	 // 220
	enCodeUserPageLotInformation			= 0xdd,	 // 221
	enCodeUserPageTrayAutoSkip				= 0xde,	 // 222
	enCodeUserPageTrayNoSkip				= 0xdf,	 // 223
	enCodeUserPageDeviceSetup				= 0xe0,  // 224
	enCodeUserPageManualContact				= 0xe1,  // 225
	enCodeUserPageCategorySetup				= 0xe2,  // 226
	
	// #2: Setup Page
	enCodeSetupPageOffset					= 0xf0,	 // 240	
	enCodeSetupPageSpeed					= 0xf1,	 // 241
	enCodeSetupPageTimer					= 0xf2,	 // 242
	enCodeSetupPageEventLog					= 0xf3,	 // 243
	enCodeSetupPageYieldControl				= 0xf4,	 // 244
	enCodeSetupPageIOMonitor				= 0xf5,	 // 245
	enCodeSetupPageDeviceSetup				= 0xf6,	 // 246
	enCodeSetupPageAlignment				= 0xf7,	 // 247
	enCodeSetupPageManualContact			= 0xf8,	 // 248
	enCodeSetupPageSLTProgram				= 0xf9,	 // 249
	enCodeSetupPageSiteSetting				= 0xfa,	 // 250
	enCodeSetupPageTrayFile					= 0xfb,  // 251
	enCodeSetupPageCCDSetup					= 0xfc,  // 252
	enCodeSetupPageATCMoudle				= 0xfd,  // 253
	enCodeSetupPageFunction					= 0xfe,  // 254
	enCodeSetupPageInputTray				= 0xff,  // 255
	enCodeSetupPageAutoRetry				= 0x100, // 256
	enCodeSetupPageLoopTest					= 0x101, // 257
	enCodeSetupPageLoopTestMap				= 0x102, // 258
	enCodeSetupPageCategorySetup			= 0x103, // 259
	
	// #3: Engineer Page
	enCodeEngPageSpeed						= 0x118, // 280
	enCodeEngPageTrayFile					= 0x119, // 281
	enCodeEngPageMotorMonitor				= 0x11a, // 282
	enCodeEngPageIOMonitor					= 0x11b, // 283
	enCodeEngPageAlignment					= 0x11c, // 284
	enCodeEngPageEventLog					= 0x11d, // 285
	enCodeEngPageCCDSetup					= 0x11e, // 286

	// #4: Debug
	enCodeDebugPageGearRation				= 0x12d, // 301
	enCodeDebugPageLanguage					= 0x12e, // 302
	enCodeDebugPageFunction					= 0x12f, // 303
	enCodeDebugPageSiteSetting				= 0x130, // 304
	enCodeDebugPageHandler					= 0x131, // 305
	enCodeDebugPageTimer					= 0x132, // 306
	enCodeDebugPageTimerSetting				= 0x133, // 307
	enCodeDebugPageAlignment				= 0x134, // 308
	enCodeDebugPageTrayFile					= 0x135, // 309
	enCodeDebugPageATCMonitor				= 0x136, // 310
/*
	Timeout Base = 299
	X	= 299 + 1 = 300
	Y	= 299 + 2 = 301
	Z 	= 299 + 3 = 302
	TS	= 299 + 4 = 303
*/
	// About Motor
	// Timeout
	enCodeMotorBaseTimeout					= 0x190, // 400
	enCodeMotorArmXTimeout					= 0x191, // 401
	enCodeMotorArmYTimeout					= 0x192, // 402
	enCodeMotorArmZTimeout					= 0x193, // 403
	enCodeMotorTestSiteTimeout				= 0x194, // 404
	enCodeMotorTestSiteTorque				= 0x195, // 405
/*
	Overheater Base = 309
	X	= 309 + 1 = 310
	Y	= 309 + 2 = 311
	Z 	= 309 + 3 = 312
	TS	= 309 + 4 = 313
*/
	enCodeMotorBaseOverheat					= 0x19a, // 410
	enCodeMotorArmXOverheat					= 0x19b, // 411
	enCodeMotorArmYOverheat					= 0x19c, // 412
	enCodeMotorArmZOverheat					= 0x19d, // 413
	enCodeMotorTestSiteOverheat				= 0x19e, // 414

/*
	Driver Base	  = 319
	X	= 309 + 1 = 320
	Y	= 309 + 2 = 321
	Z 	= 309 + 3 = 322
	TS	= 309 + 4 = 323
*/

	enCodeMotorBaseDriverAlarm				= 0x1a4, // 420
	enCodeMotorArmXDriverAlarm				= 0x1a5, // 421
	enCodeMotorArmYDriverAlarm				= 0x1a6, // 422
	enCodeMotorArmZDriverAlarm				= 0x1a7, // 423
	enCodeMotorTSDriverAlarm				= 0x1a8, // 424

	// About Button Event
	enButtonOneCyclePushed					= 0x1ae, // 430
	enButtonInitialPushed					= 0x1af, // 431
	enButtonRetryPushed						= 0x1b0, // 432
	enButtonSkipPushed						= 0x1b1, // 433
	enButtonStartPushed						= 0x1b2, // 434
	enButtonStopPushed						= 0x1b3, // 435
	enButtonResetPushed						= 0x1b4, // 436
	enButtonTestSiteSkipPushed				= 0x1b5, // 437

	// Arm Error
	enCodeArmPickICFail						= 0x1f4, // 500 Pick IC Fail!
	enCodeArmPickICFailWithRotator			= 0x1fc, // 508 Arm Z Pick IC Fail From Rotator
	enCodeArmPickICFailWithShuttle			= 0x1fd, // 509 Arm Z Pick IC Fail From Shuttle output 
	enCodeArmRotatorInPosFail				= 0x1fe, // 510 Rotator InPos Fail.!
	enCodeArmFix1TrayMissing				= 0x1ff, // 511 Fix1 Tray Missing.
	enCodeArmFix1TrayFull					= 0x201, // 513 Fix1 Tray Full
	enCodeArmInputTrayMissing				= 0x202, // 514 Input Tray Missing
	enCodeArmInputShuttleJam				= 0x203, // 515 Input Shuttle Jam
	enCodeArmOutputTray1Full				= 0x204, // 516 Tray1 Fail Full
	enCodeArmOutputTray2Full				= 0x205, // 517 Tray2 Fail Full

	// Arm Error With Rotator
	// Rotator Input
	enCodeArmInRotatorRemainFail			= 0x208, // 520	Rotator Input Before Place detect IC
	enCodeArmInRotatorJamFail				= 0x209, // 521 Rotator Input After Place detect IC Jam
	enCodeArmInRotatorICMissing				= 0x20a, // 522	Rotator Input Before Pick detect IC Missing
	// Rotator Output
	enCodeArmOutRotatorRemainFail			= 0x20b, // 523	Rotator Output Before Place detect IC
	enCodeArmOutRotatorJamFail				= 0x20c, // 524	Rotator Output After Place detect IC Jam
	enCodeArmOutRotatorICMissing			= 0x20d, // 525	Rotator Output Before Pick detect IC Missing
	// Rotator 180 Input
	enCodeArmInRotator180NLmtFail			= 0x226, // 550	Rotator Input 180 degree N Lmt InPos Fail
	enCodeArmInRotator180PLmtFail			= 0x227, // 551	Rotator Input 180 degree P Lmt InPos Fail
	// Rotator 180 Output
	enCodeArmOutRotator180PLmtFail			= 0x228, // 552	Rotator Output 180 degree P Lmt InPos Fail
	enCodeArmOutRotator180NLmtFail			= 0x229, // 553 Rotator Output 180 degree N Lmt InPos Fail
	// Rotaotr 180 Input Jam / Exist / Missing
	enCodeArmInRotator180Exist				= 0x22a, // 554	Rotator Input 180 degree. Detect IC Exist Before Place
	enCodeArmInRotator180Jam				= 0x22b, // 555	Rotator Input 180 degree. Detect IC Jam After Place
	// Rotator 180 Output Jam / Exist / Missing
	enCodeArmOutRotator180Missing			= 0x22c, // 556	Rotator Output 180 degree. After Place IC. IC Missing
	enCodeArmOutRotator180Jam				= 0x22d, // 557	Rotator Output 180 degree. After Place IC. IC Jam

	// CCD Fail..
	enCodeArmCCDMatchFail					= 0x20e, // 526	CCD Match Fail.!

	// Moving Fail. (IC Missing)
	enCodeArmMovingICMissing				= 0x20f, // 527	Arm XY Moving. IC Missing.!
	enCodeArmInPreheaterVacuumFail			= 0x214, // 532	Arm Pick IC Fail 

	// Test Site / Shuttle Move Fail
	enCodeShuttleMoveToPickFail				= 0x258, // 600 Shuttle Move to Pick Fail
	enCodeShuttleMoveToPlaceFail			= 0x259, // 601 Shuttle Move to Place Fail
	enCodeShuttleMoveToHomeFail				= 0x25a, // 602 Shuttle Move to Home Fail
	enCodeTestPickICFromSHFail				= 0x25b, // 603 Test Site Pick IC Fail from shuttle input 
	enCodeTestPickICFromSocketFail			= 0x25c, // 604 Test Site Pick IC Fail from socket
	enCodeShuttleInputJamFail				= 0x25d, // 605 Shuttle move to input(under test site), check jam fail
	enCodeTestSiteMoveICMissing				= 0x25e, // 606 Test Site move to place, IC missing

	// Yield Control Fail
	enCodeLowYieldFail						= 0x2bd, // 701	Low Yield alarm
	enCodeContinueFail						= 0x2be, // 702	Contunue Fail alar,

	// ATC Moudle
	enCodeATCModuleFANError					= 0x33b, // 827	ATC Module Fan Detect Fail
	enCodeATCModuleWaterFlowError			= 0x33c, // 828 ATC Module Water Detect Fail
	enCodeATCModuleStableError				= 0x33e, // 830 ATC Change Stable Time Fail
	enCodeATCModuleEnableError				= 0x33f, // 831 ATC Module Enable Driver Fail

	// Socket CCD Match Fail.
	enCodeCCDSocketMatchFailError			= 0x346, // 838
	enCodeCCDSocketGrabFailError			= 0x347, // 839

	enCodeEStop								= 0x400, // 1024 E-Stop be pushed
	enCodeCycleFinish						= 0x401, // 1025 Cycle Finish

	// System Error Code
	// Motion Card Fail
	enErrorCodeMotorCard1Fail				= 0x500, // 1280	

	// ION Alarm
	enErrorIONAlarmFail						= 0x501, // 1281 // ION Alarm io pull high.!
	enErrorAirPressureFail					= 0x502, // 1282 // Air Pressure Detect Fail

	// TS Remain IC
	enCodeTSRemainICFail					= 0x503, // 1283 TS Remain IC

	enCodeManualShuttleInFail				= 0x700, // 1792 // Manual Contact Shuttle Move to Input fail
	enCodeManuelTestPickICFail				= 0x701, // 1793 // Manual Contact Test Site Pick Fail
	enCodeManualShuttleHomeFail				= 0x702, // 1794 // Manual Shuttle Move to Home fail
	enCodeManualShuttleOutFail				= 0x703, // 1795 // Manual Shuttle Move to Output fail
	enCodeManualShuttleStandyFail			= 0x704, // 1796 // Manual Test Pick IC from Socket Fail
	enCodeManualShuttleJamFail				= 0x705, //	1797 // Manual Shuttle Jam Fail
};




////////////////////////////////////////////////////////////////////////////////
// 


//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__18A27D27_37E2_479A_8CE7_47F14CB2EE80__INCLUDED_)
