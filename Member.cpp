// Member.cpp: implementation of the CMember class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Deer.h"
#include "Member.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMember::CMember()
{
	//
	m.m_RemoteTestResult							= _T("");


	//
	m.m_RemoteCtrlFun.m_iAutoReplayEvent			= 0;

	//
	m.CustomFilePath.EventLogReportPath				= _T("");
	m.CustomFilePath.LoopTestResultReportPath		= _T("");
	m.CustomFilePath.MultiSVProgramExportPath		= _T("");
	m.CustomFilePath.MultiSVTestReportPath			= _T("");
	m.CustomFilePath.MultiSVTrayMapFilePath			= _T("");
	m.CustomFilePath.SLTProtocolPath				= _T("");
	m.CustomFilePath.TrayMapReportPath				= _T("");
	m.CustomFilePath.UPHReportPath					= _T("");

	//
	m.m_AlignProtuction.m_TestNoSafePosition		= 0.0;

	// 1.0Ah
	m.m_TitleExtendNote.TitleTrayExtendNote			= _T("");
	m.m_TitleExtendNote.TitleMachineExtend			= _T("");

	m.m_LastTrayFile.csLastTrayFile					= _T("");

	// 1.0Af
	m.m_LastTrayData.FileMain						= _T("");
	m.m_LastTrayData.FileMainMapping				= _T("");
	m.m_LastTrayData.FileMainTestSetting			= _T("");
	m.m_LastTrayData.VisionOcrPatternName			= _T("");
	m.m_LastTrayData.VisionPatternName				= _T("");

	// 1.0Af
	// Arm Log IC Image
	m.m_ArmLogICImage.dCaptureStableTime			= 2.0;	//secs
	m.m_ArmLogICImage.bEnableArmLogICImage			= 0;
	m.m_ArmLogICImage.csImageFilePath				= _T("");
	m.m_ArmLogICImage.bKeepSourceImage				= false;

	// 1.0Af
	// Lamp Setup
	m.m_TowerBlinkTimer.bBlink1						= false;
	m.m_TowerBlinkTimer.bBlink2						= false;
	m.m_TowerBlinkTimer.bBlink3						= false;
	m.m_TowerBlinkTimer.bBlink4						= false;
	m.m_TowerBlinkTimer.bBlink5						= false;
	m.m_TowerBlinkTimer.lBlink1Start				= 0;
	m.m_TowerBlinkTimer.lBlink2Start				= 0;
	m.m_TowerBlinkTimer.lBlink3Start				= 0;
	m.m_TowerBlinkTimer.lBlink4Start				= 0;
	m.m_TowerBlinkTimer.lBlink5Start				= 0;

	// 1.0Af
	for(int y=0;y<_MaxTowerBlink;y++)
		m.m_TowerSetupSetting.dBlinkTime[y] = _MaxTowerBlinkTime / 2;

	//
	m.m_RepeatConfimCmd.m_csBook				= _T("");
	m.m_RepeatConfimCmd.m_csSoakTime			= _T("");
	m.m_RepeatConfimCmd.m_csStableTime			= _T("");
	m.m_RepeatConfimCmd.m_csSV					= _T("");
	m.m_RepeatConfimCmd.m_csTolerance			= _T("");
	m.m_RepeatConfimCmd.m_dTimeout				= 2.00;

	//
	m.m_RepeatInOutCtrl.m_iRepeatConfimFromComm	= 0;	// no communication
	m.m_RepeatInOutCtrl.m_iRepeatTimes			= 0;
	m.m_RepeatInOutCtrl.m_iTray1				= theApp.enRepeatDefineInput;
	m.m_RepeatInOutCtrl.m_iTray2				= theApp.enRepeatDefineOutput;

	//
	m.m_RepeatTrayDATA.m_NowCount				= 0;
	m.m_RepeatTrayDATA.m_bRepeatIsTray1			= true;
	m.m_RepeatTrayDATA.m_bIsOneCyclePress		= false;

	//
	m.m_TrayFileDefColor.m_colAmbit				= ST_WHITE;
	m.m_TrayFileDefColor.m_colATCModule			= ST_WHITE;
	m.m_TrayFileDefColor.m_colHeater			= ST_WHITE;
	m.m_TrayFileDefColor.m_colPTCModule			= ST_WHITE;
	m.m_TrayFileDefColor.m_colTriTemperature	= ST_WHITE;

	//
	m.m_JamRateInfo.m_lJamError					= 0;
	m.m_JamRateInfo.m_lTotalUnit				= 0;
	m.m_JamRateInfo.m_lCycleTime				= 0;

	//
	m_RepeatTrayTemperData.RemoveAll();

	//
	m.m_RepeatTemp.dSV							= 25.0;	// deg
	m.m_RepeatTemp.dSoakTime					= 30.0;	// secs
	m.m_RepeatTemp.dStableTime					= 35.0;	// secs
	m.m_RepeatTemp.dTolerance					= 3.0;	// deg

	//
	m.m_EnableRepeatTrayFun.m_bNone				= false;
	m.m_EnableRepeatTrayFun.m_bInOutCtrl		= false;
	m.m_EnableRepeatTrayFun.m_bTrayBinningCtrl	= false;

	//
	m.m_RepeatTrayCtrl.m_iRepeatTrayMode		= 0;	// None

	//
	m.m_TcpInfo.csTesterIP						= _T("");
	m.m_TcpInfo.iPort							= 0;

	//
	m.m_ManualContactMode.bIsTsDirectContact	= 0;
	m.m_ManualContactMode.bIsTsKeepVaccOn		= 0;

	//
	m.m_VisionSet.lVisionPickDut				= 0;

	//
	m.m_TorqueToolSet.daValue					= 0.0;
	m.m_TorqueToolSet.dbValue					= 0.0;

	//
	m.m_YieldCtrl.m_lContinueFail				= 0;
	m.m_YieldCtrl.m_lTested						= 0;
	m.m_YieldCtrl.m_iPFArray.RemoveAll();
	m.m_YieldCtrl.m_dFailRate					= 0;

	//
	m.m_heaterCtrl.m_bHeaterIsStable			= false; 
	m.m_heaterCtrl.m_bHeaterTempOK				= false;
	m.m_heaterCtrl.m_lHeaterStart				= 0;

	//
	m.m_TsFolatingParameter.iPogoCount			= 0;
	m.m_TsFolatingParameter.iPogoForce			= 0;
	m.m_TsFolatingParameter.iPogoTorqueForce	= 0;

	//
	m.m_TsFolatingConvert.dTsFloatingConvert	= 0.00;

	//
	m.m_West.dSetPoint							= 0.0;
	m.m_West.dStableTime						= 0.0;
	m.m_West.dSoakTime							= 0.0;
	m.m_West.dTolerance							= 0.0;

	//
	m.m_MCFunction.m_bEnableInterfaceTesting	= false;
	m.m_MCFunction.m_bEnableOffsetControl		= false;
	m.m_MCFunction.m_bEnableTemperatureControl	= false;
	m.m_MCFunction.m_bEnableTorqueControl		= false;
	m.m_MCFunction.m_bEnableTestDirectContact	= false;
	m.m_MCFunction.m_bEnableTestSiteVacc		= false;

	//
	m.m_RemoteIOTool.csInputResult				= _T("");
	m.m_RemoteIOTool.csOutputResult				= _T("");
	for(int i=0;i<_RemoteLength;i++)
		m.m_RemoteIOTool.receive[i]				= 0;

	// Lot Information Progress
	m.m_LotInfoProg.m_csLotInformationInfo		= _T("");
	m.m_LotInfoProg.m_lLotInformationStatus		= 0;
	m.m_LotInfoProg.m_bLotInformationDone		= false;

	// Enable Page Function
	m.m_EngineerPageEnable.m_bEnableMotorMon	= true;
	m.m_EngineerPageEnable.m_bEnableIOMonitor	= true;
	m.m_EngineerPageEnable.m_bEnableAlignment	= true;
	m.m_EngineerPageEnable.m_bEnableEventLog	= false;
	m.m_EngineerPageEnable.m_bEnableSocketCCD	= false;
	m.m_EngineerPageEnable.m_bEnableSpeed		= true;
	m.m_EngineerPageEnable.m_bEnableTSCounter	= true;
	m.m_EngineerPageEnable.m_bEnableChangeFile	= false;
	m.m_EngineerPageEnable.m_bEnableLoopTest	= true;
	m.m_EngineerPageEnable.m_bEnableAlarmMail	= false;

	// Enable Page Function
	m.m_UserPageEnable.m_bEnableSummaryReport	= true;
	m.m_UserPageEnable.m_bEnableManualContact	= true;
	m.m_UserPageEnable.m_bEnableDeviceSetup		= false;
	m.m_UserPageEnable.m_bEnableSiteSetting		= false;
	m.m_UserPageEnable.m_bEnableVisualPanel		= false;
	m.m_UserPageEnable.m_bEnableLotInformation	= true;
	m.m_UserPageEnable.m_bEnableAutoSkip		= true;
	m.m_UserPageEnable.m_bEnableYieldCtrl		= true;
	m.m_UserPageEnable.m_bEnableIfTesting		= false;
	m.m_UserPageEnable.m_bEnableTrayMapReport	= false;
	m.m_UserPageEnable.m_bTestSiteVaccOn		= false;
	m.m_UserPageEnable.m_bTestResultReport		= false;
	m.m_UserPageEnable.m_bRepeatTrayStatus		= false;
	m.m_UserPageEnable.m_bTrayDefColor			= false;
	m.m_UserPageEnable.m_bArmLogICImage			= false;
	m.m_UserPageEnable.m_bSLTProtocol			= true;

	// Enable Page Function
	m.m_SetupPageEnable.m_bEnableOffset			= true;
	m.m_SetupPageEnable.m_bEnableSpeed			= true;
	m.m_SetupPageEnable.m_bEnableTimer			= true;
	m.m_SetupPageEnable.m_bEnableEventLog		= true;
	m.m_SetupPageEnable.m_bEnableSiteSetting	= true;
	m.m_SetupPageEnable.m_bEnableYieldCtrl		= true;
	m.m_SetupPageEnable.m_bEnableAutoRetry		= true;
	m.m_SetupPageEnable.m_bEnableDeviceSetup	= true;
	m.m_SetupPageEnable.m_bEnableTrayFile		= true;
	m.m_SetupPageEnable.m_bEnableIfTesting		= true;
	m.m_SetupPageEnable.m_bEnableCatoregy		= true;
	m.m_SetupPageEnable.m_bEnableInterface		= true;
	m.m_SetupPageEnable.m_bEnableRemoteControl	= true;
	m.m_SetupPageEnable.m_bEnableRemoteInput	= true;
	m.m_SetupPageEnable.m_bEnableInputTray		= true;
	m.m_SetupPageEnable.m_bEnableOutputTray		= true;
	m.m_SetupPageEnable.m_bEnableIOMonitor		= true;
	m.m_SetupPageEnable.m_bEnableAlignment		= true;
	m.m_SetupPageEnable.m_bEnableInOutTray		= true;
	m.m_SetupPageEnable.m_bEnableRepeatTray		= false;
	m.m_SetupPageEnable.m_bEnableTowerSetting	= false;
	
	m.Setting.m_bEnableLotDoneProgress			= true;

	// UPH Tool
	m.m_UPHData.m_TSCalc.RemoveAll();

	// Manual Control flag
	m.ManualInterlok.IsManualControlMode	= false;

	// Remote Control flag
	m.RemoteInterlock.IsRemoteControlMode	= false;
	m.RemoteInterlock.PickIC				= false;
	m.RemoteInterlock.ReleaseIC				= false;
	m.RemoteInterlock.RemotePosition		= 0;

	// PID Value
	m.m_ContactForce.lPower					= 0;

	// Interface Enable
	m.m_InterfaceEnable.m_bEnableGpib		= 0;
	m.m_InterfaceEnable.m_bEnableRs232		= 0;
	m.m_InterfaceEnable.m_bEnableTcp		= 0;
	m.m_InterfaceEnable.m_bEnableTTL		= 0;

	// CCD Socket 
	m.m_CCDSocketControl.iCCDUse			= 0;
	m.m_CCDSocketControl.RoiX				= 0;
	m.m_CCDSocketControl.RoiY				= 0;
	m.m_CCDSocketControl.RoiW				= 0;
	m.m_CCDSocketControl.RoiH				= 0;
	m.m_CCDSocketControl.RationX			= 1.46;
	m.m_CCDSocketControl.RationY			= 1.43;

	// CCD Pin1
	m.m_CCDPin1Control.iCCDUse				= 0;
	m.m_CCDPin1Control.RoiX					= 0;
	m.m_CCDPin1Control.RoiY					= 0;
	m.m_CCDPin1Control.RoiW					= 0;
	m.m_CCDPin1Control.RoiH					= 0;

	// Handler Com Port
	m.m_HandlerComPort.iPortATCModule		= 0;
	m.m_HandlerComPort.iPortIOModule		= 0;
	m.m_HandlerComPort.iPortPIDValue		= 0;
	m.m_HandlerComPort.iPortTester			= 0;
	m.m_HandlerComPort.iIDPIDValue			= 0;
	m.m_HandlerComPort.iIDIOModuleIDIn 		= 0;
	m.m_HandlerComPort.iIDIOModuleIDOut 	= 0;
	m.m_HandlerComPort.iPortWest			= 0;
	m.m_HandlerComPort.iPortWestHeaterID	= 0;
	m.m_HandlerComPort.iPortTorqueStatus	= 0;

	// Debug value
	m.DebugError.ReadCount					= 0;	
	m.DebugError.ReadErr					= 0;
	m.DebugError.ReadRemoteErr				= 0;
	m.DebugError.ReadRemoteCount			= 0;
	m.DebugError.ReadRemoteSpendTime		= 0;

	// Test Setting
	m.m_TestSetting.m_Angle					= 0;
	m.m_TestSetting.m_CCDSocketUse			= 0;
	m.m_TestSetting.m_CCDUse				= 0;
	m.m_TestSetting.m_RotatorUse			= 0;
	m.m_TestSetting.m_TestType				= 0;

	m.m_ContactCounterValue.lContactConter	= 0;		// 

	// Interlock
	m.InterLock.IsCycleFinishOK				= false;	//
	m.InterLock.IsIORead					= false;
	// Position Interlock
	m.InterLock.TestSiteWithIC				= false;
	m.InterLock.ArmZGetIC					= false;
	m.InterLock.SocketWithIC				= false;
	m.InterLock.RotatorWithIC				= false;
	m.InterLock.ShuttleWithIC				= false;
	m.InterLock.ShuttleInputICOK			= false;
	m.InterLock.ShuttleOutputICOK			= false;
	m.InterLock.ShuttleResetInput			= false;
	m.InterLock.ShuttleHome					= false;
	m.InterLock.IsIODone					= false;
	m.InterLock.IsRemoteIODone				= false;

	// Thread Ctrl
	m.Info.iThreadCount						= 0;

	// Yield Ctrl
	m.YieldCheck.iCountinueFail				= 0;
	m.YieldCheck.iYieldControl				= 0;

	// init value
	m.EnginnerCloseErr						= false;

	// Remotr Control Arm value
	m.m_ArmBook = -1;
	m.m_ArmPlaceBook = -1;
	
	// Chip Tray Ctrl value
	m.m_ArmChipTrayBook = -1;				// 

	// Init setting
	m.Setting.m_iSpeedLowLimit				= 0;
	m.Setting.m_iSpeedHighLimit				= 0;
	m.Setting.m_dTimerHighLimit				= 0.0;
	m.Setting.m_dTimerLowLimit				= 0.0;
	m.Setting.m_dOffsetHighLimit			= 0.0;
	m.Setting.m_dOffsetLowLimit				= 0.0;
	m.Setting.m_dTimeoutHighLimit			= 0.0;
	m.Setting.m_dTimeoutLowLimit			= 0.0;
	m.Setting.m_dBuzzerAutoClose			= 0.0;
	m.Setting.m_dTraySpecLeftSide			= 0.0;
	m.Setting.m_dTraySpecTopSide			= 0.0; // If set all zero. There will not gap in TrayMap .	
	m.Setting.m_bByPassVacc					= 0;
	m.Setting.m_bByPassTestVacc				= 0;
	m.Setting.m_bByPassEnableIORecovery		= 0;
	m.Setting.m_bByPassRotatorAlarm			= 0;
	m.Setting.m_bByPassTrayInPos			= 0;
	m.Setting.m_bByPassShuttleAlarm			= 0;
	m.Setting.m_bEnableSimplified			= 0;	// Simplified chinese support.!	
	m.Setting.m_bSetByMode					= 0;
	m.Setting.m_dTraySpecTextUpSide			= 0.0;	
	m.Setting.m_dTraySpecTextLeftSide		= 0.0;	
	m.Setting.m_iTraySpecTextSize			= 0;
	m.Setting.m_iTraySpecTextBreak			= 0;
	m.Setting.m_iTraySpecBkColor			= 0;
	m.Setting.m_bShowContactCounter			= 0;
	m.Setting.m_bSummaryReport				= 0;
	m.Setting.m_bArmZAutoRetry				= 0;
	m.Setting.m_bEnableTSRemainIC			= 0;
	m.Setting.m_bIONAlarm					= 0;
	m.Setting.m_bInitialPreMove				= 0;
	m.Setting.m_iInitialPreMoveDistance		= 0;
	m.Setting.m_dStandyX					= 0.0;
	m.Setting.m_dStandyY					= 0.0;
	m.Setting.m_dTestSiteStandbyPosition	= 0.0;
	m.Setting.m_dTestSiteSocketStandyPos	= 0.0;
	m.Setting.m_iTestSiteStandByDistance	= 0;
	m.Setting.m_bEnableRotatorPreGuide		= 0;
	m.Setting.m_bEnableRotatorTurn			= 0;
	m.Setting.m_bEnableATCModule			= 0;	
	m.Setting.m_bEnablePTCModule			= 0;
	m.Setting.m_bEnableHeaterModule			= 0;
	m.Setting.m_bEnableRemoteModule			= 0;
	m.Setting.m_bEnableTriTempModule		= 0;
	m.Setting.m_bEnableRemoteIO				= 0;
	m.Setting.m_bEnableCCDPin1				= 0;
	m.Setting.m_bEnableCCDSocket			= 0;
	m.Setting.m_bEnableCCDLogICImage		= 0;

	m.Setting.m_bEnableICMissingDetect		= 0;
	m.Setting.m_bInputTrayTips				= 0;
	m.Setting.m_bInputTrayTipsNumber		= 0;
	m.Setting.m_bInputTrayInfo				= 0;
	m.Setting.m_bRemoteCustomInput			= 0;
	m.Setting.m_bEnableTorqueCtrl			= 0;
	m.Setting.m_bCancelDoubleChkChange		= 0;
	m.Setting.m_bEnableTorqueStatus			= 0;
	m.Setting.m_iRepeatMaxiumValue			= 0;
	m.Setting.m_bShowHandlerStatus			= 0;
	m.Setting.m_bEnableProgramInitialStart	= 0;
	m.Setting.m_bEnableRepeatTrayStatus		= 0;
	m.Setting.m_bEnableAutoSelLastTrayFile	= 0;
	m.Setting.m_bEnableAutoCopyLastLotInfo	= 0;

	// Log flag
	m.Setting.m_bEnableUPHLog				= 0;
	m.Setting.m_bEnableCommLog				= 0;	
	m.Setting.m_bEnableSingleMotorLog		= 0;
	m.Setting.m_bEnableDualMotorLog			= 0;
	m.Setting.m_bEnableMotorLog				= 0;
	m.Setting.m_bEnableCCDSocketLog			= 0;
	m.Setting.m_bEnableJamRateReport		= 0;
	//

	// System setting
	m.Info.user = enLevelUser;
	m.Site.iRunMode = 0;

	// GearRation
	m.m_Ratio.X_GearRation = 0.0;
	m.m_Ratio.Y_GearRation = 0.0;
	m.m_Ratio.Z_GearRation = 0.0;

	// Timer
	m.Timer.m_dInsertPick	= 0.0;
	m.Timer.m_dInsertPuff	= 0.0;
	m.Timer.m_dPickPick		= 0.0;
	m.Timer.m_dPickPuff		= 0.0;	

	// Initial MotorStatus
	m.MotorStatus.ArmX = "";
	m.MotorStatus.ArmY = "";
	m.MotorStatus.ArmZ = "";
	m.MotorStatus.Inserter = "";
	m.MotorStatus.Tester = "";

	m.MotorStatus.ArmXRCount = 0;	
	m.MotorStatus.ArmYRCount = 0;	
	m.MotorStatus.ArmZRCount = 0;	
	m.MotorStatus.InserterRCount = 0;	
		
	m.MotorStatus.ArmXInitialed			= false;
	m.MotorStatus.ArmYInitialed			= false;
	m.MotorStatus.ArmZInitialed			= false;
	m.MotorStatus.InserterInitialed		= false;
	m.MotorStatus.TesterInitialed		= false;

	// Initial Interlock using. It is Each Axis initial complete
	m.InterLock.InitialArmZEnd			= false;			
	m.InterLock.InitialArmYEnd			= false;			
	m.InterLock.InitialArmXEnd			= false;			
	m.InterLock.InserterEnd				= false;				
	m.InterLock.TesterEnd				= false;					
	m.InterLock.InspectEnd				= false;
	m.InterLock.ManualCtrlEnd			= false;

	m.InterLock.TestingGo				= false;
	m.InterLock.Testing					= false;
	m.InterLock.TestingOK				= false;
	//
	m.InterLock.ArmEnd					= false;


	//
	m.UPH.CycleTime = 0;
	m.UPH.ICTested = 0;
	m.UPH.iUPH = 0;

	// Display TrayMap item.
	// default display code
	m.TrayMapSetting.bCode				= true;
	m.TrayMapSetting.bTemp				= false;

	// info.
	m.Info.bIOMonitor = false;

	// Run Page UPH Value
	CalcInfo.CycleTimes = 0;
	CalcInfo.TestedIC = 0;
	CalcInfo.UPH = 0;

	// 
	m.iDebugCount = 0;
	m.iDebugPreHeaterCount = 0;

	// ÀË¬d Log 
	m.dBLog.InsertFailCount = 0;

	//
	m_LmtCounter.iTSnLmtCounter	= 0;
	m_LmtCounter.iYpLmtCounter	= 0;
	m_LmtCounter.iXpLmtCounter	= 0;
	//
	m_LmtCounter.iYnLmtCounter	= 0;
	m_LmtCounter.iTSpLmtCounter	= 0;
	m_LmtCounter.iXnLmtCounter	= 0;

	//
	IONFanAlarmStart = 0;
	IONFanAlarm = false;

	//
	m_InputTrayControl.bInputTrayChange = false;
}

CMember::~CMember()
{
	m_DriveMotorTorque.Close();
}
