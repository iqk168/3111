// DriverTestInterface.h: interface for the CDriverTestInterface class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DRIVERTESTINTERFACE_H__950CE285_B2D9_4C24_A50D_D359AEC12A97__INCLUDED_)
#define AFX_DRIVERTESTINTERFACE_H__950CE285_B2D9_4C24_A50D_D359AEC12A97__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// Interface Layer
#include "DriverTestInterfaceTCP.h"

// Message
#define _STX		"<<"
#define _ETX		">>"
#define _MTX		"%"
#define _STDONE		" DONE"
#define _STERROR	" ERROR"
#define _STOK		" OK"


#define _CMTX		","

// Coordnation, Tray
#define _MaxCol		50
#define _MaxRow		50

// Self Software Parameter
#define _ModelName	"3111"

// Log
#define _RemoteRawLog	"ProtocolRawLog.log"
#define _RemoteLog		"ProtocolLog.log"

//
typedef struct tagRemoteCommand {
	int m_iRemoteCommandID;
	CString m_csRemoteCommandName;
	CString m_csRemoteFunction;
} tagRemoteCommand;

typedef struct tagRemoteCommandList{
	CArray< tagRemoteCommand, tagRemoteCommand > m_RemoteCommand;
} tagRemoteCommandList;

typedef struct tagRemoteLotInfo {
	int iFiled;
	CString csLotInfo;
} tagRemoteLotInfo;

// 命令
typedef struct tagTestProtocol
{
	int site;				// site 1, igone
	CString csSite;			// site 1, igone
	CString cmd;			// tempetature, coordnation
	CString parameter;		//
} tagTestProtocol;

// Rotator 模式
enum RotatorMode {
	enRotatorModeN				= 0,	// -90
	enRotatorModeP				= 1,	// +90
	enRotatorModeZ				= 2,	// 0
	enRotatorModeU				= 3,	// 180
};

// Lot 欄位
enum LotField {
	enLotFieldLotNo				= 0,
	enLotFieldMachineNo			= 1,
	enLotFieldOperatorID		= 2,
	enLotFieldDeviceID			= 3,
	enLotFieldProgramID			= 4,
};

// Tray 角色
enum RemoteTrayMode {
	enCmdTray1					= 0,	// Tray1
	enCmdTray2					= 1,	// Tray2
};

// 回復命令
enum RemoteReturnCmd
{
	enReturnCodeConnect					= 0,
	enReturnCodeDisconnect				= 1,
	enReturnVersion						= 2,
	enReturnGetTemp						= 3,
	enReturnGetSetTemp					= 4,
	enReturnSetTemp						= 5,
	enReturnEnableTemp					= 6,
	enReturnGetStatus					= 7,
	enReturnEnableRotator				= 8,
	enReturnChangeRotatorStatus			= 9,
	enReturnChangeRotator				= 10,
	enReturnSetCoordnation				= 11,
	enReturnGetCoordnation				= 12,
	enReturnCCDLogIC					= 13,
	enReturnErrMessage					= 14,
	enReturnAutoSkip					= 15,
	enReturnGetAutoSkip					= 16,
	enReturnGetTraySpec					= 17,
	enReturnSetCoordnationGo			= 18,
	enReturnSetCoordnationDone			= 19,
	enReturnSetCoordnationReturn		= 20,
	enReturnSetCoordnationReturnDone	= 21,
	enReturnSetCoordnationClearGo		= 22,
	enReturnGetAirPressure				= 23,
	enReturnSetAirPressure				= 24,
	enReturnSetState					= 25,
	enReturnGetState					= 26,
	enReturnGetHelp						= 27,
	enReturnSetStateInitial				= 28,
	enReturnSetStateStart				= 29,
	enReturnSetStateStop				= 30,
	enReturnSetStateRetry				= 31,
	enReturnSetStateSkip				= 32,
	enReturnSetStateReset				= 33,
	enReturnSetStateOneCycle			= 34,
	enReturnSetStateErrorCtrl			= 35,
	enReturnSetError					= 36,
	enReturnSetCoordnationGoError		= 37,
	enReturnSetCoordnationReturnError	= 38,
	enReturnSetRunMode					= 39,
	enReturnGetRunMode					= 40,
	enReturnSetTsVacc					= 41,
	enReturnGetTsVacc					= 42,
	enReturnSetLotDone					= 43,
	enReturnSetNewLot					= 44,
	enReturnGetLotNo					= 45,
	enReturnSetLotNo					= 46,
	enReturnGetMachineNo				= 47,
	enReturnSetMachineNo				= 48,
	enReturnGetOperationID				= 49,
	enReturnSetOperationID				= 50,
	enReturnGetDeviceID					= 51,
	enReturnSetDeviceID					= 52,
	enReturnGetProgramID				= 53,
	enReturnSetProgramID				= 54,
};

// 設定狀態
enum RemoteSetState
{
	enSetStateInitial					= 0,
	enSetStateStart						= 1,
	enSetStateStop						= 2,
	enSetStateOneCycle					= 3,
	enSetStateReset						= 4,
	enSetStateRetry						= 5,
	enSetStateSkip						= 6,
};

// 設定狀態
enum RemoteCommandSetStatus
{
	enRemoteCommandStatusOK				= 0,
	enRemoteCommandStatusError			= 1,
	enRemoteCommandStatusInitial		= 2,
	enRemoteCommandStatusGo				= 3,
};

class CDriverTestInterface  
{
private:
	HANDLE	m_hComm;

	bool m_bInSocket;			// 是否在 Socket 內, 表示接下來的錯誤只能由 Tester 詢問, 不能主動發出
	bool m_bReturnError;		// 是否發生過錯誤, 如果是表示下次 Start 是復歸, 直接執行 return

public:

	void InitTestInterfaceExcute(); //RS232 執行緒將處理命令送到 CArray 準備送出


	// 1.0Ao
	// TCP/IP
	CDriverTestInterfaceTCP	m_TesterInterfaceTcp;
	bool OpenTCP(int iPort);
	void CloseTCP();
	void GetEthernet(CString &csEthernetIP, CString &csEthernetPort);
	void CloseReadTCP();
	void CloseWriteTCP();
	CArray< CString, CString > m_SendTCPCmd;

	//
	// 建立連線
	void InitTestInterfaceTCP();	

	//
	// TCP 收到的訊息都會先存在這
	CString csTCPBuffer;
	void ReadTCP();
	void WriteTCP();

	// 執行緒控制
	HANDLE hProcessWriteTCP;
	HANDLE hProcessReadTCP;

	static UINT ThreadTestInterfaceWriteTCP(LPVOID p);
	static UINT ThreadTestInterfaceReadTCP(LPVOID p);

	// 1.0Ap
	HANDLE hProcessExcute;
	void CloseExcute();
	static UINT ThreadTestInterfaceExcute(LPVOID p);

public:
	
	struct tagRemoteReturnCmd {
		CString csConnect;
		CString csDisconnect;
		CString csVersion;
	} m_RemoteReturnCmd;
	
	struct tagRemoteCoord {
		int iCol;
		int iRow;
		int iTray;
	} m_RemoteTray;
	
public:
	CString CommandRun(tagTestProtocol  telegram);//
	tagRemoteCommandList m_RemoteCommandList;

public:
	CDriverTestInterface();
	virtual ~CDriverTestInterface();

	// Debug
	void RemoteCommMsgCmd(CString csMsg = _T(""));				// 送出
	void RemoteRawMsg(CString csMsg = _T(""));					// 收到
	void RemoteSendMsdCmd(CString csMsg = _T(""));				// 
	void RemoteCommAddBuffer(CString csSimBuffer = _T(""));		//
	CString m_csSimBuffer;
	
	//
	CArray< tagTestProtocol, tagTestProtocol > m_ReviceCmd;

	CArray< CString, CString > m_SendCmd;
	CArray< CString, CString > m_PreSendCmd;

	// 建立 Link
	bool Open(int iPort, int iBaudRate = 9600); // 115200
	bool SetOpen(HANDLE m_hCommOther);

	// 取得資訊
	int m_iBaudRate;
	void GetBaudRate(int &BaudRate);

	// 建立命令
	void InitCommandSetup();

	// 讀寫命令
	void Read();
	void AddReadCmd(tagTestProtocol tagReadCmd);
	void Write();
	void AddReplyCmd(CString csReplyCmd, bool bAddCommand = true);

	// 執行命令
	void ProcessCommand();

	// 解釋命令
	void GetReturnCommand(tagTestProtocol msg, CString &csReturnCmd, int &iReturnCode, bool &bNeedReturn);
	void GetSendCommand(int iCode, CString &csSendCmd, CString csExtMsg = _T("") );
	bool GetReadyCommand(CString &csNoReadyReason );
	bool GetReadyReturnCommand(CString &csNoReturnReason );

	/*
	如果要變更命令格式, 在 GetReturnCommand 變更回復命令
						在 GetSendCommand 變更主動通知命令
	*/

	// RS232 收到的訊息都會先存在這
	CString csBuffer;

	// 建立/與解除
	bool InitTestInterface(int iPort);
	void CloseWrite();
	void CloseRead();
	bool Close();

	// 執行緒控制
	HANDLE hProcessWrite;
	HANDLE hProcessRead;

	// 執行緒
	static UINT ThreadTestInterfaceWrite(LPVOID p);
	static UINT ThreadTestInterfaceRead(LPVOID p);

	//
	tagTestProtocol GetProtocol(CString &cs);

	//
	bool m_bRemoteMode;						// 是否為 Remote Mode
	bool GetRemoteMode();					// 回傳是否為 Remote Mode ( 是否有連接上 )
	void SetRemoteMode(bool bRemote);		// 設定是否為 Remote Mode

	// 是否要傳送 Event
	bool m_bRemoteSendEvent;


	// 是否在 PurgeDevice
	bool m_bRemotePurgeDevices;


	// 是否要重測 //可以設定次數
	int m_bRemoteRetest;

public:

	// 記錄通訊
	CString m_csLogPath;
	void SetLogPath(CString csPath = _T(""));
	CString GetLogPath();
	void LogRaw(CString csLog = _T(""));
	void Log(CString csLog = _T(""));

	// 記錄目前 Interface Status
	int m_MachineStatus;									// 0 for normal ready status
	int m_MachineStatusCode;								// 0 for normal ready code

public:

	// 本機專用命令(控制本機的動作/儀器)
	CString SetStatus(int iStatus, int iCode);				// 設定 目前的狀態 (Remote)
	CString GetStatus(int &iStatus, int &iCode);			// 取得 目前的狀態 (Remote)
	CString GetStatusContent();								// 取得目前系統狀態的描述
	CString GetTempMaxMin(double &dMax, double &dMin );		// 取得系統最高最低溫限制
	CString GetTorqueMaxMin(double &dMax, double &dMin);	// 取得系統最高最低壓力限制
	CString GetProgramVersion();							// 取得版本
	CString GetSiteTemp();									// 取得溫度
	CString GetSiteSetTemp();								// 取得設定溫度
	CString SetSiteTemp(double dTemp);						// 設定溫度
	CString EnableTemp(bool bEnable);						// 啟動溫度
	CString GetSystemStatus();								// 取得系統狀態
	CString EnableRotator(bool bEnable);					// 設定是否使用 Rotator
	CString SetRotator(int iDegree);						// 設定 Rotator 角度
	CString GetRotator(int &iDegree);						// 取得 Rotator 角度
	CString SetErrorMessage(int iCode, CString csMsg);		// 設定 ErrorMessage (Code)
	CString EnableCCDLogIC(bool bEnable);					// 設定啟動CCD記錄 IC
	CString SetCoord(int iTray, int iX, int iY);			// 設定 Coordnation
	CString GetCoord(int &iTray, int &iX, int &iY);			// 取得 Coordnation
	CString GetTraySpec(int &iCol, int &iRow);				// 取得 TraySpec
	CString SetAutoSkip(bool bEnable);						// 設定 AutoSkip 狀態
	CString GetAutoSkip(bool &bEnable);						// 取得 Auto Skip 狀態
	CString SetTsVacc(bool bEnable);						// 設定 Test Site vacc 狀態
	CString GetTsVacc(bool &bEnable);						// 取得 Test Site vacc 狀態
	CString SetCoordnationDone();							// 設定 Coordnation 成功 (IC in socket)
	CString SetCoordnationReturnDone();						// 設定歸還 IC 成功 (Error Skip 也會設定)
	CString SetStateInitialDone();							// 設定 Initial Done
	CString SetStateRetryDone();							// 設定 Retry Done
	CString SetStateSkipDone();								// 設定 Skip Done
	CString SetStateStartDone();							// 設定 Start Done
	CString SetStateStopDone();								// 設定 Stop Done
	CString SetStateResetDone();							// 設定 Reset Done
	CString SetStateOneCycleDone();							// 設定 OneCycle Done
	CString SetStateErrorCtrlDone();						// 設定 ErrorCtrl Done
	CString SetStateError();								// 設定 Error
	CString SetAirPressure(double dAirPressure);			// 設定 Air Pressure 數值
	CString GetAirPressure(double &dAirPressure);			// 取得 Air Pressure 數值
	CString GetHelpFile(CString &csHelpFile);				// 取得 Help File 字串
	CString SetButtonInitial();								// 設定 Button Initial
	CString SetButtonStart();								// 設定 Button Start
	CString SetButtonStop();								// 設定 Button Stop
	CString SetButtonOneCycle();							// 設定 Button OneCycle
	CString SetButtonRetry();								// 設定 Button Retry 
	CString SetButtonSkip();								// 設定 Button Skip
	CString SetButtonReset();								// 設定 Button Reset
	CString SetRunMode(int iMode);							// 設定 Run Mode
	CString GetRunMode(int &iMode);							// 取得 Run Mode
	CString SetLotInfo(int iLotField, CString csInfo);		// 設定 Lot Information
	CString GetLotInfo(int iLotFiled, CString &csInfo);		// 取得 Lot Information
	
	bool GetLotCreate();									// 確認是否有建立工單
	bool GetDoorStatus();									// 確認是否門被開啟
	bool GetEStopStatus();									// 確認緊急停止鈕
	bool GetSystemReady();									// 確認系統準備好
	bool GetSystemError();									// 取得目前系統是否錯誤
	bool GetCoordnationReady();								// 確認已經設定 Coordnation
	bool GetTrayFileMatchNow();								// 確認最後一份 TrayFileSpec Match
	bool GetCoordnationGoStatusReady();						// 確認目前的狀態
	bool GetAirPressureEnable();							// 確認是否啟動 電控比例閥
	bool GetIOMonitorOpen();								// 確認 IO Monitor 是否被打開
	bool GetButtonStartStatus();							// 確認 Panel Start 是否可以被按下
	bool GetButtonStopStatus();								// 確認 Panel Stop 是否可以被按下
	bool GetButtonInitialStatus();							// 確認 Panel Initial 是否可以被按下
	bool GetButtonRetryStatus();							// 確認 Panel Retry 是否可以被按下
	bool GetButtonSkipStatus();								// 確認 Panel Skip 是否可以被按下
	bool GetButtonResetStatus();							// 確認 Panel Reset 是否可以被按下
	bool GetButtonOneCycleStatus();							// 確認 Panel OneCycle 是否可以被按下
	bool GetNewLot();										// 確認是否可以建立 New Lot
	bool GetLotDone();										// 確認是否可以建立 Lot Done
	
	// SetState
	bool SetState(int iState);								// 設定目前的狀態
	
	// Mission
	void RequestCoordnationMissionGo();						// 要求 Arm 開始執行任務
	void RequestCoordnationMissionReturn();					// 要求 Ts 開始執行任務
	void RequestCoordnationMissionClearGo();				// 要求 Arm 清除任務
	void RequestCoordnationMissionInitial();				// 初始化參數

	// Verify
	bool VerifyCoord(CString csCmd, tagRemoteCoord &t);		// 分析 Coordnation
	void GetCurrentCoord(int &iTray, int &iCol, int &iRow);	// 取得目前的 Coordnation
	void ClearRemoteTray();									// 清除設定

	bool VerifyLotInfo(CString csCmd, tagRemoteLotInfo &lot);
};

#endif // !defined(AFX_DRIVERTESTINTERFACE_H__950CE285_B2D9_4C24_A50D_D359AEC12A97__INCLUDED_)
