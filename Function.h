// Function.h: interface for the CFunction class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FUNCTION_H__8AB0BEF6_9431_4CDF_A85D_468322D8C6A9__INCLUDED_)
#define AFX_FUNCTION_H__8AB0BEF6_9431_4CDF_A85D_468322D8C6A9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// Motor Function.
#include "Motor.h"

// Report Function
#include "Report.h"

// MSG
#include "DMsg.h"

// File Control
#include "FileCtrl.h"

#include "Member.h"
#include "EventLog.h"

#include <map>
#include <vector>

class CFunction  
{
public:
	CFunction();
	virtual ~CFunction();

	//
	CMotor	Motor;				// Motor

	//
	CReport	Report;				// Report

	//
	CDMsg	DMsg;				// DMsg
	
	//
	CEventLog m_Log;			// About Log

	//
	CFileCtrl m_FileCtrl;		// File Control

	//
	bool InitRemoteInputTrayData();
	void DeleteRemoteInputTrayData();

	void MotorServoOnAll();
	void MotorServoOffAll();
	void MotorServoOffForAlignment();
	void MotorServoOffForAlignmentNoTs();

	void CloseAllOutput();

	void Log(int iLog);

	//
	void LogCSV(CString csLog, int iThread);

	// Button function
	long Wait(int msec);
	bool IsPause();

	void CycleFinish();

	//
	void CycleFinishDone();

	//
	void CycleRepeatFinishDone();

	//
	void CycleRemoteFinish();

	void UpdateButtonState();
	void ButtonInitial();
	void ButtonStop();
	void ButtonSkip();
	void ButtonStart();
	void ButtonRetry();
	void ButtonOneCycle();
	void ButtonReset();

	// BasicFile Temperature
	bool EarseTemperatureSetting(CString csFile, CString csSection, CString csProperty);

	//
	bool EarseYieldValue(CString csFile, CString csSection, CString csProperty);

	bool GetTemperatureSetting(CString csFile, CString csSection, CString csProperty, double &dValue);
	bool GetTemperatureSetting(CString csFile, CString csSection, CString csProperty, int &iValue);
	bool SaveTemperatureSetting(CString csFile, CString csSection, CString csProperty, double dValue);
	bool SaveTemperatureSetting(CString csFile, CString csSection, CString csProperty, int iValue);


	// BasicFile Control
	// About PC 
	void GetSettingBinary(CString csFileName, CString csSection, CString csProperty, int &iValue);
	void GetSettingHex(CString csFileName, CString csSection, CString csProperty, int &iValue);
	void GetSettingDouble(CString csFileName, CString csSection, CString csProperty, double &value);
	void GetSettingTrueFalse(CString csFileName, CString csSection, CString csProperty, int &iValue);

	void GetSetting(CString csFile, CString csSection, CString csProperty, tagMotorParam &Param);
	void GetSetting(CString csFile, CString csSection, CString csProperty, double &dValue);
	void GetSetting(CString csFile, CString csSection, CString csProperty, CString &csValue);
	void GetSetting(CString csFile, CString csSection, CString csProperty, long &iValue);
	void GetSetting(CString csFile, CString csSection, CString csProperty, int &iValue);
	void GetSetting(CString csFile, CString csSection, CString csProperty, COLORREF &iValue);
	void GetSetting(CString csFile, CString csSection, CString csProperty, bool &bValue);

	void SaveSetting(CString csFile, CString csSection, CString csProperty, tagMotorParam Param);	
	void SaveSetting(CString csFile, CString csSection, CString csProperty, double dValue);
	void SaveSetting(CString csFile, CString csSection, CString csProperty, CString csValue);
	void SaveSetting(CString csFile, CString csSection, CString csProperty, long iValue);
	void SaveSetting(CString csFile, CString csSection, CString csProperty, int iValue);
	void SaveSetting(CString csFile, CString csSection, CString csProperty, COLORREF iValue);
	void SaveSetting(CString csFile, CString csSection, CString csProperty, bool bValue);

	void SaveSettingDouble(CString csFileName, CString csSection, CString csProperty, double dValue);
	void SaveSettingBinary(CString csFileName, CString csSection, CString csProperty, int iValue);
	void SaveSettingHex(CString csFileName, CString csSection, CString csProperty, int iValue);
	void SaveSettingTrueFalse(CString csFileName, CString csSection, CString csProperty, int iValue);

	// 
	void DeleteSetting(CString csFile, CString csSection, CString csProperty, double dValue);

	void LoadLotInfo();
	void SaveLotInfo();
	void LotDone();
	bool CheckNewLot();	// 檢查有沒有 建過 New Lot, 如果沒有, 不可能使用機台.

	void AddNewArmLogICFolder(CString csLotName);

	//
	void LotDoneClearUPH();
	void LotDoneClearTrayMap();
	void LotDoneClearTrayMapRepeat();
	void LotDoneCopyInfo();
	void LotDoneClearInfo();
	void LotDoneClearCoord();
	void LotDoneResetRunPageUI();
	void LotDoneClearSetting();	

	void SaveAlignment();
	void LoadAlignment();

	void LoadPassword();
	void SavePassword();

	// Gear Ration
	// This for motor pulse to really distance.
	void SaveGearRationParameter();
	void LoadGearRationParameter();

	// This for handler timer setting.
	void SaveTimerSetting();
	void LoadTimerSetting();

	// For software setting.
	// Auto Skip 
	void SaveSetting();
	void LoadSetting();

	// For System Setting.
	void SaveSystemSetting();
	void LoadSystemSetting();
	
	// For Run Page. Count.
	// Note : Each site test count. 
	void LoadCounter();
	void SaveCounter();

	// For Handler ID. Display in Main Dialog.
	void LoadMachineID();
	void SaveMachineID();

	void LoadUI();
	void SaveUI();

	// Motor 
	void SaveMotorParameter();
	void LoadMotorParameter();

	// Load File
	void Decryption(CString *csCode);
	void Encryption(CString *csCode);

	// System Control
	void ShutDown();
	void ThreadWait();

	// Bin Category
	void LoadBinMapping();
	bool ReadBinMappingFile(CString csFile, CArray<CString, CString> &array);
	tagBinMapping GetBinMapping(CString code);
	bool SaveBinMapping(CString csFile, CArray <tagBinMapping, tagBinMapping>* TempBinMap);
	
	void LoadFile();
	void LoadCoord();

	void LoadPath();
	void SavePath();

	// Simulation Debug using.
	void LoadSimulation();
	void SaveSimulation();

	// dBase
	void OpenDatabase();
	void LoadErrorCode();
	void LoadLanguage();
	void DeleteErrorCode(int Code);

	// Interface testing
	void LoadInterfaceTesting();

	void LoadSLT();
	void SaveSLT();

	// Language
	void ChangeLanguage(HWND wnd);

	void LoadMotorAddress();

	// Release Note
	void LoadDebugNote();
	void LoadOffsetNote();

	// UI
	void MyGetVersion(LPCTSTR lpszFileName, LPSTR lpszVersion, DWORD dwVerLen);
	BOOL ParseVersionString(LPSTR lpVersion, DWORD& dwMajor, DWORD& dwSecond, DWORD& dwThird, DWORD& dwFourth);

	void MyGetProductVersion();

	void CWinMessage(CString msg, int value);

	/////////////////////////////////////////////////////////
	// Error code library 
	tagErrorMsg GetErrorMsg(long Code);

	void SaveSpeed();
	void LoadSpeed();
	
	void SavePogoParameter();
	void LoadPogoParameter();

	void LoadYield();
	void SaveYield();

	void SaveOffset();
	void LoadOffset();

	void SaveTraySpec();
	void LoadTraySpec();

	//
	void LoadSiteSetting();
	void SaveSiteSetting();

	void SaveTimer();
	void LoadTimer();

	int RandResult();

	void Counter(int iBin);	// For RunPage calc counter.
	void CycleCounter();	// For RunPage UPH and Cycle counter
	/////////////////////////////////////////////////////////

	// SetTray Parameter
	void SetTrayData();		
	// Set Alignment
	// Set Gear Ration
	// Set Tray Spec. A, B, C, D....

	void SetCoord();

	////////////////////////////////////////////////////////
	// Tray Map Function
	void LoadTrayMap();
	void SaveTrayMap();
	void AddTrayMap(int stack, CString code, CPoint point, int site, double temperature);
	void AddTrayMap(int stack, int bin, CPoint point, int site, double temperature);

	////////////////////////////////////////////////////////
	// Tray Map Function ( RepeatTray TrayMap )
	void LoadTrayMapRepeat();
	void SaveTrayMapRepeat();
	void AddTrayMapRepeat(int stack, CString code, CPoint point, int site, double temperature);
	void AddTrayMapRepeat(int stack, int bin, CPoint point, int site, double temperature);

	////////////////////////////////////////////////////////
	// Tray Map Log Report
	void LogTrayMapCSV(CString csTrayMap);
	void ExportTrayMapReport();
	CString ExportTrayMapReportMapGetCode(int x, int y);
	int ExportTrayMapReportMapMaxCodeLength();
	void ExportTrayMapReportMap(int col, int row);

	// Log
	void CommLog( CString csLog );
	void ShuttleJamLog(CString csLog);

	bool CheckEnaleChange();

	// 
	CString StringToIntArrayByToken(CString cs, CArray <int, int> &array, CString token);
	CString StringToIntArrayByToken(CString cs, CArray <double, double> &array, CString token);
	CString StringToIntArrayByToken(CString cs, CArray <CString, CString> &array, CString token);
	
	void DeleteOldFile(CString FileExt, int DaysBefore); // 清除舊 檔案避免 Log 檔太大.!

	// 
	void LoadContactCounter();
	void SaveContactCounter();

	void LoadCatoregyColor();

	// Smart Mail Function
	void LoadSMTPSetting();
	void SaveSMTPSetting();

	// 
	void MotorLog(CString csLog);
	void SpeedMotorLog(CString csLog);
	void SingleMotorLog(CString csLog);

	// Auto Retry
	void LoadAutoRetrySetting();
	void SaveAutoRetrySetting();

	// Troque Limit
	void LoadTorqueCtrlLimit();
	void SaveTorqueCtrlLimit();

	// Event Log 
	void ExportEventLog();

	//
	void AutoCreateFolder(CString csFolder);

	//
	void LoadJamRateCode();
	void LoadJamRateData();
	int GetJamRateCount();
	CString GetJamRateCodeList();
	void SaveJamRateData();
	void ErrorRateControl(int iErrorCode);
	void ExportErrorRateReport();
	void ClearRateData();

	//
	void ClearYieldCtrl();

	//
	void LoadAutoRetryExterndValue();
	void SaveAutoRetryExterndValue();
	void LoadAutoRetryEnable();
	void SaveAutoRetryEnable();

	//
	void ExportSummaryReport();

	//
	void LoadTestSetting();
	void SaveTestSetting();

	//
	void IncraseThreadCount();
	void ReduceThreadCount();

	//
	void LoadBinColor();
	void SaveBinColor();
	
	// 
	void LoadATCMonitor();
	void SaveATCMonitor();

	//
	COLORREF GetCategoryColor(CString result);

	//
	void LoadHandlerComPort();
	void SaveHandlerComPort();
	
	void LoadOutputColor();
	void SaveOutputColor();

	void LoadInterfaceEnable();
	void SaveInterfaceEnable();

	void LoadUPHInfo();
	void SaveUPHInfo();

	///////////////////////////////////////////////////////////
	//
	void LoadCCDSocketControl();
	void SaveCCDSocketControl();

	//
	void LoadCCDPin1Control();
	void SaveCCDPin1Control();

	// Init Msg
	void InitPorgramStartInitial();
	bool InitDMsg();

	// CCD Function
	void InitCCD();

	// Mail Function
	void InitMail();
	void SendAlarmMail(int iCode, CString csDesc);
	
	// West 
	void InitWest();

	// 1.0Ab
	// Motor Status
	void InitTorqueStatus();

	//
	void InitTorqueCtrl();

	//
	void InitOutputYieldCount();
	void LotDoneClearOutputYieldCounter();
	void LoadOutputYield();

	//
	void LoadContactForce();
	void SaveContactForce();

	//
	void LoadSocketPattern();
	void SaveSocketPattern();

	//
	void LoadPageEnable();
	void SavePageEnable();

	//
	void LoadMCEnable();
	void SaveMCEnable();

	//
	void LoadTemperatureSetting();
	void SaveTemperatureSetting();

	//
	void LoadTSRemainICParameter();
	void SaveTSRemainICParameter();

	//
	void LoadTsFolatingConvert();
	void SaveTsFloatingConvert();

	//
	void LoadTorqueToolSet();
	void SaveTorqueToolSet();

	//
	void LoadVisionSet();
	void SaveVisionSet();

public:
	// Interface File 
	void LoadInterface();
	void LoadInterFaceRs232();
	void LoadInterFaceTcp();
	void LoadTcpToObject();

public:
	// ATC Module
	void LoadATCModuleMultiSVFile();
	void SaveATCModuleMultiSVFile();
	void LoadATCModuleMultiSVSetting();
	void LoadATCModuleMultiSVSetting(CString csFileName, double &dTemperatureRange, double &dChangeStable);
	void SaveATCModuleMultiSVSetting(CString csFileName, double dTemperatureRange, double dChangeStable);

public:
	// UPH
	void ClearUPHAllData();
	void ClearUPHTSData();
	void ExportUPHLog(int item, double dTime);

public:
	// ATC Module
	void InitATCModule();
	void InitTcp();

public:
	bool CheckInitialNeed();

public:

public:
	void GetWestLoopupTableTemperature(CString csSV, CString csProt, double &dOffset );
	void DeleteWestLoopupTableTemperature(CString csSV, CString csProt, double &dOffset );
	void DeleteWestLoopupTableTemperatureAll(CString csProt);
	void SetWestLoopupTableTemperature(CString csSV, CString csProt, CString csOffset);

public:
	bool ShuttleMoveHome();
	bool ShuttleMovePickPlace();
	bool CheckShuttlePickPlaceOK();	// Check shuttle move to pick / place position ok
	bool CheckShuttleHomeOK();		// Check shuttle move to home / pick / place position ok
	bool CheckShuttleJam();			// Check shuttle move to picl / place position check jam before move
	bool CheckTSZVaccSensor();

	bool ManualShuttleMoveHome();
	bool ManualShuttleMovePickPlace();
	bool Vacc(unsigned char* Vacc, unsigned char* pSensor, double dTimeout );	// Ts
	bool Blow(unsigned char* Vacc, unsigned char* Puff, unsigned char* pSensor, double dTimeout ); // Ts
	
	bool ManualVacc(unsigned char* Vacc, unsigned char* pSensor, double dTimeout );	// ArmZ
	bool ManualBlow(unsigned char* Vacc, unsigned char* Puff, unsigned char* pSensor, double dTimeout ); // ArmZ

public:
	bool ManualRotatorN(unsigned char* Turn,	unsigned char* pSensor, unsigned char* nSensor, double dTimeout = 5.5 ); // -90
	bool ManualRotatorP(unsigned char* Turn,	unsigned char* pSensor, unsigned char* nSensor, double dTimeout = 5.5 );	// 90

public:
	// Heater
	bool HeaterOnNeed();
	bool HeaterIsStable(double &dSpendTime);

public:
	// Loop Test
	void LoadLoopTest();
	void SaveLoopTest();
	void SaveLoopTested();
	void ClearLoopTest();

public:
	// Yield Rate
	void LoadOutputYieldValue();
	void SaveOutputYieldValue();
	void LotDoneClearYieldValue();

public:
	// Basic Setting
	void LoadAlignmentProf();

public:
	bool IsTextOffsetNote();
	void LoadTextOffsetNote();
	CString GetTextOffsetNote(int uId);
	void GetOffsetSetting(CString csFile, CString csSection, CString csProperty, CString &csValue);

public:
	// 1.0Ab
	void SaveSiteSettingRunMode();

	// 1.0Ab
	void SaveManualContactTsMode();
	void LoadManualContactTsMode();

public:
	// 1.0Ab
	void LoadIf();
	CString LoadIfNote(int uId);
	void GetIfNote(CString csFile, CString csSection, CString csProperty, CString &csValue);

	int GetTesterBaudRate();
	BOOL GetTesterIPAddress(char* szLocalIP);
	BOOL GetHandlerIPAddress(CString &szLocalIP);

public:
	// 1.0Ac
	// Vision Function
	tagInfoParameter GetIMGFileSetting(CString csFilePath);

	// 1.0Ac
	void LoadTorqueParameter();
	void SaveTorqueParameter();

public:

	// 1.0Ac Repeat Tray Setting
	void LoadRepeatTraySetting();
	void SaveRepeatTraySetting();
	void LoadRepeatTrayInOut();
	void SaveRepeatTrayInOut();
	void LoadRepeatTrayTemper();
	void SaveRepeatTrayTemper();

	void LoadRepeatTrayFunEnable();
	void SaveRepeatTrayFunEnable();

public:
	CString GetTrayFileNowMode();
	CString GetRunTimeFromCycleTime(long lsecs);
	void LoadJamRateCycleTimeInfo();
	void SaveJamRateCycleTimeInfo();
	void ClearJamRateInfo();
	void LoadJamRateInfo();
	void SaveJamRateInfo();
	void InsertJamRateCounter(int iCode);
	void InsertJamRateTotalCounter();
	void SaveJamRateTotalCounter();

	//
	CString GetRepeatTrayMode();
	CString GetRepeatTreyDefine(int iDefine);
	COLORREF GetRepeatTrayFileColor(int iTrayFile);

	void LoadTrayFileDefColor();
	void SaveTrayFileDefColor();

	//
	bool IsTrayFileNeedTemperature();
public:

	int GetRepeatTrayModeMoation();
	void ClearRepeatTrayDATA();
	double GetNowTemperature(int NowCount);

	int GetRepeatTrayTimes();

	// Tray1<->Tray2
	int GetNowMoation(int NowCount);
	void LoadNowMoation();
	void SaveNowMoation();

public:
	void LoadRepeaterTrayCommand();

public:
	// 1.0Af
	// Lamp Setup
	void LoadTowerSetting();
	void SavetowerSetting();

public:
	// 1.0Af
	// UPH Tool
	void TSMessageCounter();

	// 1.0Af
	// UPH Tool
	void UPHMessageForClear();
	void UPHMessageForTs();

	// 1.0Af
	// UPH Tool
	void ExportUPHReport(int iReport, CArray <double, double> &m_UPHLog);
	void ExportUPHLogReport(CString csFileName, CArray <double, double> &m_UPHLog );

	// 1.0Af
	// Arm Log IC Image
	void InitArmLogICImage();
	void LoadArmLogICImage();
	void SaveArmLogICImage();
	void LoadArmLogICImagePath();
	void SaveArmLogICImagePath();

	// 1.0Ah
	void InitProtuctShuttle();

	// 1.0Af
	void MessageCommunicationInfo(CString csInfo );

	void LoadLastTrayFile();
	void SaveLastTrayFile();

	// 1.0Af
	void IsRepeatHeaterNeed();

	// 1.0Af
	void AutoSeletLastTrayFile();
	void LoadLastTrayData();
	void SaveLastTrayData();
	void LotDeviceSetup(CString csTrayFile);

	// 1.0Ah
	CString GetManualContactNote();

	// 1.0Ah
	bool InitRemoteCtrl();

public:

	void LoadTitleExtend();
	void SetTitleExtend(LPVOID p, int nType);

	// 1.0Ah
	// GDIPlus
	int GetEncoderClsid(const WCHAR* format, CLSID* pClsid);
	Status SaveFile(Bitmap* pImage, const wchar_t* pFileName);
	void ConvertFile(CString csSourceBmp, CString csDestionJpg);

	CString GetStatusValue(Status status);
	void VisionMessage(CString csMsg);

	// 1.0Aj
	// SLT Protocol
	void RemoteMessage(int iCode);
	void RemoteSetCoordnationDone();
	void RemoteSetCoordnationReturnDone();
	// 1.0Al
	void RemoteSeCoordnationInitial();
	void RemoteSetStateInitialDone();
	void RemoteSetStateRetryDone();
	void RemoteSetStateSkipDone();
	void RemoteSetStateOneCycleDone();
	void RemoteSetStateStopDone();
	void RemoteSetStateResetDone();
	void RemoteSetStateErrorCtrl();
	void RemoteSetStateError();
	void RemoteSetStatus(int iStatus, int iCode);

	// 1.0Ao
	void InitSLTProtocolHelp();
	bool GetSLTProtocolHelp();	
	
protected:

};

#endif // !defined(AFX_FUNCTION_H__8AB0BEF6_9431_4CDF_A85D_468322D8C6A9__INCLUDED_)
