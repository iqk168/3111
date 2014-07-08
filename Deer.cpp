// Deer.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "Member.h"

#include "Deer.h"
#include "DeerDlg.h"

#include <afxsock.h>
// Socket

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDeerApp

BEGIN_MESSAGE_MAP(CDeerApp, CWinApp)
	//{{AFX_MSG_MAP(CDeerApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDeerApp construction

CDeerApp::CDeerApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CDeerApp object

CDeerApp theApp;
CMember m;
CFunction f;
CParser3111 ps;
/////////////////////////////////////////////////////////////////////////////
// CDeerApp initialization

BOOL CDeerApp::PreTranslateMessage(MSG* pMsg) 
{
	return CWinApp::PreTranslateMessage(pMsg);
}

BOOL CDeerApp::ProcessMessageFilter(int code, LPMSG lpMsg) 
{
	if(!m_pMainWnd)
		return CWinApp::ProcessMessageFilter(code, lpMsg);
	
	if (m_pMainWnd->m_hWnd && ghAccelTable)
		if (::TranslateAccelerator(m_pMainWnd->m_hWnd, ghAccelTable, lpMsg))
			return (TRUE);

	return CWinApp::ProcessMessageFilter(code, lpMsg);
}

BOOL CDeerApp::InitInstance()
{
	// 註冊字串 "Chroma 3111", 只要程式在跑, "Chroma 3111" 就存在
	HANDLE hMutex = CreateMutex(NULL, FALSE, "Chroma 3111");

	// 如果 "Chroma 3111" 已存在, 表示程式以經有了
	if(GetLastError() == ERROR_ALREADY_EXISTS)
		return FALSE;

	if (!AfxSocketInit())
	{
		AfxMessageBox("Sockets Could Not Be Initialized"); 
		return FALSE;
	}

	if (!AfxOleInit())
	{
		return FALSE;
	}

	AfxEnableControlContainer();

	// 讓貼圖的速度加快
	AfxRegisterWndClass(CS_BYTEALIGNCLIENT);

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	// GDIPlus
	GdiplusStartupInput     m_gdiplusStartupInput;
	GdiplusStartup(&m_gdiplusToken, &m_gdiplusStartupInput, NULL);

	//-- 載入加速鍵
	ghAccelTable = 
		LoadAccelerators(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDR_MAINFRAME));

	// Init FilePath & Bitmap
	theApp.InitialStatus();
	theApp.InitialParameter();

	m.Info.bRunning = true;

	// 1.0Af
	// Program Initial
	f.InitPorgramStartInitial();				TRACE("# ProgInitial\n");			// Init Program Start Initial Message
	f.InitDMsg();								TRACE("# InitDMsg\n");				// Init Debug Message

	//
	f.InitOutputYieldCount();					TRACE("# InitYieldCount\n");		// Init Yield Count Message

	//
	f.LoadFile();								TRACE("# LoadFile\n");				// Init Yield Count Message

	theApp.m_tIO.CreateThread();				TRACE("# IO CreateThread\n");		f.DMsg.DMsg( "IO CreateThread");

	if( m.Setting.m_bEnableRemoteIO == 1 )		
		theApp.m_tIORemote.CreateThread();		TRACE("# IO ReCreateThread\n");		f.DMsg.DMsg( "IO Remote CreateThread");
	if( m.Setting.m_bEnableRemoteIO == 0 )
		m.InterLock.IsRemoteIODone = true; 	

	//
	theApp.InitialIOStatus();					TRACE("# IO CreateThread Done\n");	// IO / Remote IO Thread Create Done

	// dBase
	f.OpenDatabase();							TRACE("# Open DataBase\n");			// Open dBase.
	f.LoadErrorCode();							TRACE("# Open ErrorCode\n");		// Load ErrorCode
	f.LoadLanguage();							TRACE("# Open Language\n");			// Load Language
	f.SetTrayData();							TRACE("# SetTrayData\n");			// Set Tray Data
//	f.InitCCD();								TRACE("# InitCCD\n");				// Initial CCD
	f.InitRemoteInputTrayData();				TRACE("# InitRemoteInputTray\n");	// Initial Remote Input Tray Data
	f.InitMail();								TRACE("# InitMail\n");				// Initial Alarm Mail
	f.InitWest();								TRACE("# InitWest\n");				// Initial West
	f.InitTorqueStatus();						TRACE("# InitTorqueStatus\n");		// Initial Torque Status
	f.InitATCModule();							TRACE("# InitATCModule\n");			// Initial ATC Module
	f.InitTcp();								TRACE("# InitTcp\n");				// Initial TCP
	f.InitArmLogICImage();						TRACE("# InitArmLogICImage\n");		// Initial ArmLog IC Image
	f.InitProtuctShuttle();						TRACE("# Init Protuct Shuttle\n");	// Initial Protuction Shuttle
	f.InitRemoteCtrl();							TRACE("# Initial Remote Ctrl\n");	// Initial Remote Control Protocol
	f.InitSLTProtocolHelp();					TRACE("# Initial SLT Protocol\n");	// Initial SLT Protocol Help

	//
	f.m_Log.AddLogEvent( "Deer LoadFile Finish" );
	
	//加入開機 Log
	f.m_Log.AddEvent(enCodeSystemStartUp);

	// 
	AfxInitRichEdit();

	CDeerDlg dlg;
	m_pMainWnd = &dlg;

	int nResponse = dlg.DoModal();

	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}

	// Refer
	CoUninitialize();

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}
void CDeerApp::InitialIOStatus()
{
	while(1)
	{
		if( m.InterLock.IsIODone && m.InterLock.IsRemoteIODone )
			break;

		Sleep(_Wait);
	}
}
void CDeerApp::InitialStatus()
{
	///< 由於會指定檔案，導致相對路徑失效； 
	///< Initial 時，轉成絕對路徑

	CFileFind findList;
	BOOL findResult;
	CString CurrentPath = _T("");

	findResult = findList.FindFile(".");
	if(findResult)
	{
		findResult = findList.FindNextFile();
		CurrentPath = findList.GetFilePath();
	}	
	findList.Close();
	//////////////////////////////////////////////
	// Program Initial
	m.FilePath.DMsgReportPath		= CurrentPath + "\\ProgramStartInitial\\";						// Program Initial Report

	// ProductFile
	m.FilePath.CategoryPath			= CurrentPath + "\\ProductFile\\Category\\";
	m.FilePath.TrayFilesPath		= CurrentPath + "\\ProductFile\\TrayFile\\";
	m.FilePath.TestSettingPath		= CurrentPath + "\\ProductFile\\TestSetting\\";
	m.FilePath.AtcModuleSettingPath	= CurrentPath + "\\ProductFile\\ATCModuleMultiSV\\";	

	// ProductFile / Interface
	m.FilePath.InterfaceRs232Path	= CurrentPath + "\\ProductFile\\Interface\\Rs232\\";
	m.FilePath.InterfaceTcpPath		= CurrentPath + "\\ProductFile\\Interface\\Tcp\\";
	m.FilePath.InterfaceGpibPath	= CurrentPath + "\\ProductFile\\Interface\\Gpib\\";
	m.FilePath.InterfaceTtlPath		= CurrentPath + "\\ProductFile\\Interface\\Ttl\\";

	// Interface Note Path
	m.FilePath.Rs232NotePath		= CurrentPath + "\\System\\If\\Rs232\\";
	m.FilePath.TcpNotePath			= CurrentPath + "\\System\\If\\Tcp\\";
	m.FilePath.GpibNotePath			= CurrentPath + "\\System\\If\\Gpib\\";
	m.FilePath.TtlNotePath			= CurrentPath + "\\System\\If\\Ttl\\";

	// CCD Group
	m.FilePath.CCDImageProfilePath	= CurrentPath + "\\Image\\Profiles\\";
	m.FilePath.CCDImageBackPath		= CurrentPath + "\\Image\\BackupProfiles\\";
//	m.FilePath.CCDImagePath			= CurrentPath + "\\Image\\Images\\";
	m.FilePath.SocketImagePath		= CurrentPath + "\\Image\\Socket\\";

	m.FilePath.CCDImagePath			= CurrentPath + "\\Image\\Pin1\\";
	m.FilePath.CCDImageBmpPath		= CurrentPath + "\\Image\\Images\\";	
	m.FilePath.ImagePath			= CurrentPath + "\\Image\\";									// Image
//	m.FilePath.Pin1ImagePath		= CurrentPath + "\\Image\\Pin1\\";

	//
	m.FilePath.SystemPath			= CurrentPath + "\\System\\";
	m.FilePath.UIPath				= CurrentPath + "\\System\\3111.UI";
	m.FilePath.PasswordPath			= CurrentPath + "\\System\\3111.id";
	m.FilePath.SimulationPath		= CurrentPath + "\\System\\3111.setting";	
	m.FilePath.SystemSettingPath	= CurrentPath + "\\System\\3111.System";
	m.FilePath.AlignmentPath		= CurrentPath + "\\System\\3111.Align";
	m.FilePath.CustomFilePath		= CurrentPath + "\\System\\3111.Path";
	m.FilePath.UPHPath				= CurrentPath + "\\System\\3111.Uph";
	m.FilePath.TorqueStatusPar		= CurrentPath + "\\System\\3111.Tor";
	m.FilePath.RepeatTrayPath		= CurrentPath + "\\System\\3111.Repeat";
	m.FilePath.RepeatTrayCurrPath	= CurrentPath + "\\System\\3111.RepeatCur";
	m.FilePath.RepeatTrayTemperPath	= CurrentPath + "\\System\\3111.ReTemp";
	m.FilePath.JamRateCycleTimePath	= CurrentPath + "\\System\\3111.JCT";
	m.FilePath.JamReportCounterPath	= CurrentPath + "\\System\\3111.JC";


	m.FilePath.MotorNamePath		= CurrentPath + "\\System\\Motor.System"; 
	
	m.FilePath.CommuncationPath		= CurrentPath + "\\System\\3111.Communication";
	// TrayMap 測試結果的資料夾
	m.FilePath.TrayMapPath			= CurrentPath + "\\TrayMap\\";
	// SMTP
	m.FilePath.SMPTPath				= CurrentPath + "\\System\\Mail.smtp";		
	// TrayMap Color
	m.FilePath.TrayPath				= CurrentPath + "\\System\\TrayMap.color";
	//
	m.FilePath.JamRateCodePath		= CurrentPath + "\\System\\3111.RateCode";
	m.FilePath.JamRateResultPath	= CurrentPath + "\\System\\3111.RateResult";
	m.FilePath.JamRateReportPath	= CurrentPath + "\\System\\3111.RateReport";
	m.FilePath.AutoRetrySettingPath	= CurrentPath + "\\System\\3111.AutoSetting";
	m.FilePath.BinColorPath			= CurrentPath + "\\System\\3111.BinColor";
	m.FilePath.SimulationCountPath	= CurrentPath + "\\System\\3111.Sii";
	m.FilePath.ATCMonitorPath		= CurrentPath + "\\System\\3111.Atc";
	m.FilePath.HandlerComPortPath	= CurrentPath + "\\System\\3111.Port";
	m.FilePath.CCDCameraPath		= CurrentPath + "\\System\\3111.Camera";
	//
	m.FilePath.PageEnablePath		= CurrentPath + "\\System\\3111.Page";
	m.FilePath.RepeatTrayFunEnable	= CurrentPath + "\\System\\3111.ReFun";
	m.FilePath.ManualContactPath	= CurrentPath + "\\System\\3111.Mc";
	m.FilePath.TSRemainICParamPath	= CurrentPath + "\\System\\3111.TsRe";
	m.FilePath.LoopTestSettingPath	= CurrentPath + "\\System\\3111.Loop";
	m.FilePath.OutputYieldPath		= CurrentPath + "\\System\\3111.Yield";
	m.FilePath.OffsetTxtNotePath	= CurrentPath + "\\System\\3111.OfNote";
	m.FilePath.InterfaceNotePath	= CurrentPath + "\\System\\3111.IfNote";
	m.FilePath.MContactNotePath		= CurrentPath + "\\System\\3111.McNote";
	m.FilePath.SLTProtocolNotePath	= CurrentPath + "\\System\\3111.SLTNote";

	// Heater
	m.FilePath.HeaterTempSetPath	= CurrentPath + "\\System\\3111.Heater";
	m.FilePath.HeaterTempLkPath		= CurrentPath + "\\System\\3111.Temper";

	// Torque Control
	m.FilePath.TorqueCtrlPath		= CurrentPath + "\\System\\3111.Torq";

	// 使用說明檔案位置
	m.FilePath.DebugNotePath		= CurrentPath + "\\System\\Debug.de";
	m.FilePath.OffsetNotePath		= CurrentPath + "\\System\\Offset.of";	
	// Bin Log 的位置
	m.FilePath.BinLogPath			= CurrentPath + "\\Report\\BinLog.mdb";
	m.FilePath.TempBinLogPath		= CurrentPath + "\\Report\\TempBinLog.mdb";				// TempBinLog.mdb
	// Coord
	m.FilePath.InputCoordPath		= CurrentPath +	"\\Coord\\3111.Input1.Coord";
	m.FilePath.Output1CoordPath		= CurrentPath + "\\Coord\\3111.Output1.Coord";
	// Repeat Tray
	m.FilePath.Tray1CoordPath		= CurrentPath +	"\\Coord\\3111.Tray1.Coord";
	m.FilePath.Tray2CoordPath		= CurrentPath +	"\\Coord\\3111.Tray2.Coord";
	//
	m.FilePath.PreHeaterCoordPath	= CurrentPath + "\\Coord\\3111.Preheater.Coord";		// Pre-Heater
	m.FilePath.SummaryReportPath	= CurrentPath + "\\SummaryReport\\";					// Summary Report
	m.FilePath.InputCustomInputPath	= CurrentPath + "\\RemoteInput\\";						// Remote Input Function
	m.FilePath.ArmLogICImagePath	= CurrentPath + "\\ArmLogICImage\\";					// Arm Log IC Image
	
}

void CDeerApp::InitialParameter()
{
	m.Bitmap.Err.LoadBitmap(IDB_ERROR);
	m.Bitmap.Black.LoadBitmap(IDB_BLACK);
	m.Bitmap.Layout.LoadBitmap(IDB_3111_LAYEROUT);		
	m.Bitmap.CycleEnd.LoadBitmap(IDB_CYCLE_FINISH);

	// EventLog Initial.(Event Image type)
	m.ImageList.EventType.Create(IDB_EVENT_TYPE, 25, 0, RGB(255, 255, 255));
	m.ImageList.Sort.Create(IDB_SORT_SYMBOL, 20, 0, RGB(255, 255, 255));
}

int CDeerApp::ExitInstance() 
{
	// GDIPlus
	Gdiplus::GdiplusShutdown(m_gdiplusToken);

	return CWinApp::ExitInstance();
}
