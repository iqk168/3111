// DlgVisionSetup.cpp : implementation file
//

#include "stdafx.h"
#include "deer.h"
#include "DlgVisionSetup.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgVisionSetup dialog


CDlgVisionSetup::CDlgVisionSetup(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgVisionSetup::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgVisionSetup)
	//}}AFX_DATA_INIT

	m_FileDictory.RemoveAll();

	m_IsDeviceIn = false;

	hProcess = NULL;
}


void CDlgVisionSetup::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgVisionSetup)
	DDX_Control(pDX, IDC_SCORE,					m_wndTestScore);
	DDX_Control(pDX, IDC_MATCH,					m_btnMatch);
	DDX_Control(pDX, IDC_OUTPUT_DEVICE,			m_btnDeviceOutput);
	DDX_Control(pDX, IDC_INPUT_DEVICE,			m_btnDeviceInput);
	DDX_Control(pDX, IDC_LIVE,					m_btnLive);
	DDX_Control(pDX, IDC_STOP,					m_btnStop);
	DDX_Control(pDX, IDC_FILE,					m_wndFileName);
	DDX_Control(pDX, IDC_SETUP_HEIGHT,			m_wndScoreHeight);
	DDX_Control(pDX, IDC_SETUP_WIDTH,			m_wndScoreWidth);
	DDX_Control(pDX, IDC_SETUP_SOURCE_Y,		m_wndScoreY);
	DDX_Control(pDX, IDC_SETUP_SOURCE_X,		m_wndScoreX);
	DDX_Control(pDX, IDC_MIN_MATCH_SCORE,		m_wndScoreMinMatchScore);
	DDX_Control(pDX, IDC_WINDOW_DRAW,			m_stcPicture);
	DDX_Control(pDX, IDC_GRAB,					m_btnGrab);
	DDX_Control(pDX, IDC_DELETE,				m_btnDelete);
	DDX_Control(pDX, IDC_SAVE,					m_btnSave);
	DDX_Control(pDX, IDC_LOAD,					m_btnLoad);
	DDX_Control(pDX, IDC_SETUP_IMAGE_LIST,		m_listFileFolder);
	DDX_Control(pDX, IDOK,						m_btnOK);
	DDX_Control(pDX, IDCANCEL,					m_btnCancel);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgVisionSetup, CDialog)
	//{{AFX_MSG_MAP(CDlgVisionSetup)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_INPUT_DEVICE,		OnInputDevice)
	ON_BN_CLICKED(IDC_OUTPUT_DEVICE,	OnOutputDevice)
	ON_BN_CLICKED(IDC_MATCH,			OnMatch)
	ON_BN_CLICKED(IDC_GRAB,				OnGrab)
	ON_BN_CLICKED(IDC_LOAD,				OnLoad)
	ON_BN_CLICKED(IDC_SAVE,				OnSave)
	ON_BN_CLICKED(IDC_DELETE,			OnDelete)
	ON_BN_CLICKED(IDC_STOP,				OnStop)
	ON_BN_CLICKED(IDC_LIVE,				OnLive)
	ON_BN_CLICKED(IDC_TEST,				OnTest)
	ON_BN_CLICKED(IDC_CLEAR,			OnClear)
	ON_BN_CLICKED(IDC_SET_SCOPE,		OnSetScope)
	ON_BN_CLICKED(IDC_SET_DEFAULT,		OnSetDefault)
	ON_MESSAGE(WM_RECT_POS,				OnPosInfo)
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgVisionSetup message handlers

BOOL CDlgVisionSetup::PreTranslateMessage(MSG* pMsg) 
{
	m_ToolTip.RelayEvent(pMsg);	

	// z avoid ESC / Enter to crash the software
	if(pMsg->message  == WM_KEYDOWN)   
	{
		int nVirtKey = (int)pMsg->wParam;    
		if( nVirtKey == VK_ESCAPE )
			return   TRUE;   
		if( nVirtKey == VK_RETURN )   
			return   TRUE;   
	}	
	return CDialog::PreTranslateMessage(pMsg);
}
void CDlgVisionSetup::MoationMotorErrorLockAll()
{
	BOOL bEnable = FALSE;
	m_btnDeviceInput.EnableWindow( bEnable );
	m_btnDeviceOutput.EnableWindow( bEnable );

	CString csMsg = _T("");
	csMsg.Format("Motor Error, Please close this dialog, and Initial again");
	AfxMessageBox( csMsg );
}
void CDlgVisionSetup::MoationDeviceInUI()
{
	BOOL bEnable = FALSE;
	m_btnGrab.EnableWindow( !bEnable );
	m_btnDelete.EnableWindow( !bEnable );
	m_btnSave.EnableWindow( !bEnable );
	m_btnLoad.EnableWindow( !bEnable );
	m_listFileFolder.EnableWindow( !bEnable );
	//
	m_btnDeviceInput.EnableWindow( bEnable );
	m_btnDeviceOutput.EnableWindow( !bEnable );
	m_btnMatch.EnableWindow( bEnable );
	//
	m_stcPicture.EnableWindow( bEnable );
}
void CDlgVisionSetup::MoationDeviceMoveCheck()
{
	if( m.Info.iStatus != theApp.enReady )
	{
		BOOL bEnable = FALSE;
		m_btnDeviceInput.EnableWindow( bEnable );
		m_btnDeviceOutput.EnableWindow( bEnable );
	}
}
void CDlgVisionSetup::MoationDeviceOutUI()
{
	BOOL bEnable = TRUE;
	m_btnGrab.EnableWindow( bEnable );
	m_btnDelete.EnableWindow( bEnable );
	m_btnSave.EnableWindow( bEnable );
	m_btnLoad.EnableWindow( bEnable );
	m_listFileFolder.EnableWindow( bEnable );
	//
	m_btnDeviceInput.EnableWindow( bEnable );
	m_btnDeviceOutput.EnableWindow( !bEnable );
	m_btnMatch.EnableWindow( bEnable );
	//
	m_stcPicture.EnableWindow( bEnable );
}
void CDlgVisionSetup::MoationLockUI(bool bEnable)
{
	if( bEnable )
	{
		BOOL bEnable = FALSE;
		m_btnGrab.EnableWindow( bEnable );
		m_btnDelete.EnableWindow( bEnable );
		m_btnSave.EnableWindow( bEnable );
		m_btnLoad.EnableWindow( bEnable );
		m_listFileFolder.EnableWindow( bEnable );
		m_btnStop.EnableWindow( bEnable );
		m_btnLive.EnableWindow( bEnable );
		//
		m_btnDeviceInput.EnableWindow( bEnable );
		m_btnDeviceOutput.EnableWindow( bEnable );
		m_btnMatch.EnableWindow( bEnable );
		//
		m_stcPicture.EnableWindow( bEnable );
	}
	else
	{
		BOOL bEnable = TRUE;
		m_btnGrab.EnableWindow( bEnable );
		m_btnDelete.EnableWindow( bEnable );
		m_btnSave.EnableWindow( bEnable );
		m_btnLoad.EnableWindow( bEnable );
		m_listFileFolder.EnableWindow( bEnable );
		m_btnStop.EnableWindow( !bEnable );
		m_btnLive.EnableWindow( bEnable );
		//
		m_btnDeviceInput.EnableWindow( bEnable );
		m_btnDeviceOutput.EnableWindow( bEnable );
		m_btnMatch.EnableWindow( bEnable );
		//
		m_stcPicture.EnableWindow( bEnable );
	}
}
UINT CDlgVisionSetup::DeviceInThread(LPVOID p)
{
	CDlgVisionSetup *pt = (CDlgVisionSetup *)p;
	
	//
	if(m.m_Vision.m_bCameraLive)
		pt->CameraLiveStop();

	//
	double m_dArmX = 0.0;
	double m_dArmY = 0.0;
	double m_dArmZ = 0.0;

	//
	long m_iRunError = enCodeRunOK;

	// Arm Z Up
	m_iRunError = f.Motor.ManualMotorRun( 
		&m.m_Motor.ArmZ, ( _InitialZHome * m.m_Ratio.Z_GearRation ), true, 
		m.TimerSetting.iMotorRunTimeout );		

	// 
	if( m_iRunError != enCodeRunOK )
	{
		pt->MoationMotorErrorLockAll();
		return TRUE;
	}

	// Arm XY Run Line
	CPoint pp;
	pp = theApp.m_InputTray.GetCoordinate( m.m_VisionSet.lVisionPickDut );
	m_dArmX = pp.x;
	m_dArmY = pp.y;
	m_iRunError = f.Motor.ManualMotorRunLine(	
					&m.m_Motor.ArmX, m_dArmX, 
					&m.m_Motor.ArmY, m_dArmY,
					true, m.TimerSetting.iMotorRunlineTimeout );

	//
	if( m_iRunError != enCodeRunOK )
	{
		pt->MoationMotorErrorLockAll();
		return TRUE;
	}

	// Arm Z Down
	m_dArmZ = m.m_Align.Input.z + ( m.m_Offset.Input.z * m.m_Ratio.Z_GearRation );
	m_iRunError = f.Motor.ManualMotorRun( 
		&m.m_Motor.ArmZ, m_dArmZ, true, 
		m.TimerSetting.iMotorRunTimeout );
	
	//
	if( m_iRunError != enCodeRunOK )
	{
		pt->MoationMotorErrorLockAll();
		return TRUE;
	}
	
	// Arm Vacc
	f.ManualVacc( &m.OutSet.ArmVacc, &m.InStatus.ArmZVaccSensor, m.Timer.m_dPickPick );

	// Arm Z Up
	m_iRunError = f.Motor.ManualMotorRun( 
		&m.m_Motor.ArmZ, ( _InitialZHome * m.m_Ratio.Z_GearRation ), false, 
		m.TimerSetting.iMotorRunTimeout );	

	//
	if( m_iRunError != enCodeRunOK )
	{
		pt->MoationMotorErrorLockAll();
		return TRUE;
	}

	// Arm Z Run Line to shuttle input
	m_dArmX = m.m_Align.DutIn.x + ( m.m_Offset.DutIn.x * m.m_Ratio.X_GearRation);
	m_dArmY = m.m_Align.DutIn.y + ( m.m_Offset.DutIn.y * m.m_Ratio.Y_GearRation);
	m_iRunError = f.Motor.ManualMotorRunLine(	
					&m.m_Motor.ArmX, m_dArmX, 
					&m.m_Motor.ArmY, m_dArmY,
					true, m.TimerSetting.iMotorRunlineTimeout );

	//
	if( m_iRunError != enCodeRunOK )
	{
		pt->MoationMotorErrorLockAll();
		return TRUE;
	}

	// Arm Z Down (shuttle input)
	m_dArmZ = m.m_Align.DutIn.z2 + ( m.m_Offset.DutIn.z2 * m.m_Ratio.Z_GearRation );
	m_iRunError = f.Motor.ManualMotorRun( 
		&m.m_Motor.ArmZ, m_dArmZ, true, 
		m.TimerSetting.iMotorRunTimeout );

	//
	if( m_iRunError != enCodeRunOK )
	{
		pt->MoationMotorErrorLockAll();
		return TRUE;
	}

	// Blow
	f.ManualBlow( &m.OutSet.ArmVacc, 
				&m.OutSet.ArmBlow, 
				&m.InStatus.ArmZVaccSensor, 
				m.Timer.m_dPickPuff );

	// Arm Z Up
	m_iRunError = f.Motor.ManualMotorRun( 
		&m.m_Motor.ArmZ, ( _InitialZHome * m.m_Ratio.Z_GearRation ), false, 
		m.TimerSetting.iMotorRunTimeout );	

	//
	if( m_iRunError != enCodeRunOK )
	{
		pt->MoationMotorErrorLockAll();
		return TRUE;
	}

	// Arm move to CCD Position
	m_dArmX = m.m_Align.DutIn.x 
		+ ( m.m_Offset.DutIn.x * m.m_Ratio.X_GearRation) + ( _ArmZToCCD_X * m.m_Ratio.X_GearRation);
	m_dArmY = m.m_Align.DutIn.y 
		+ ( m.m_Offset.DutIn.y * m.m_Ratio.Y_GearRation) + ( _ArmZToCCD_Y * m.m_Ratio.Y_GearRation);
	m_iRunError = f.Motor.ManualMotorRunLine(	
					&m.m_Motor.ArmX, m_dArmX, 
					&m.m_Motor.ArmY, m_dArmY,
					true, m.TimerSetting.iMotorRunlineTimeout );

	//
	if( m_iRunError != enCodeRunOK )
	{
		pt->MoationMotorErrorLockAll();
		return TRUE;
	}

	pt->m_IsDeviceIn = true;
	pt->MoationDeviceInUI();

	return TRUE;
}
UINT CDlgVisionSetup::DeviceOutThread(LPVOID p)
{
	CDlgVisionSetup *pt = (CDlgVisionSetup *)p;

	//
	if(m.m_Vision.m_bCameraLive)
		pt->CameraLiveStop();
	
	//
	double m_dArmX = 0.0;
	double m_dArmY = 0.0;
	double m_dArmZ = 0.0;

	//
	long m_iRunError = enCodeRunOK;

	// Arm Z Run Line to shuttle output
	m_dArmX = m.m_Align.DutOut.x + ( m.m_Offset.DutOut.x * m.m_Ratio.X_GearRation);
	m_dArmY = m.m_Align.DutOut.y + ( m.m_Offset.DutOut.y * m.m_Ratio.Y_GearRation);
	m_iRunError = f.Motor.ManualMotorRunLine(	
					&m.m_Motor.ArmX, m_dArmX, 
					&m.m_Motor.ArmY, m_dArmY,
					true, m.TimerSetting.iMotorRunlineTimeout );

	//
	if( m_iRunError != enCodeRunOK )
	{
		pt->MoationMotorErrorLockAll();
		return TRUE;
	}


	// Arm Z Down (shuttle output)
	m_dArmZ = m.m_Align.DutOut.z + ( m.m_Offset.DutOut.z * m.m_Ratio.Z_GearRation );
	m_iRunError = f.Motor.ManualMotorRun( 
		&m.m_Motor.ArmZ, m_dArmZ, true, 
		m.TimerSetting.iMotorRunTimeout );

	//
	if( m_iRunError != enCodeRunOK )
	{
		pt->MoationMotorErrorLockAll();
		return TRUE;
	}

	// Arm Vacc
	f.ManualVacc( &m.OutSet.ArmVacc, &m.InStatus.ArmZVaccSensor, m.Timer.m_dPickPick );

	// Arm Z Up
	m_iRunError = f.Motor.ManualMotorRun( 
		&m.m_Motor.ArmZ, ( _InitialZHome * m.m_Ratio.Z_GearRation ), false, 
		m.TimerSetting.iMotorRunTimeout );	

	//
	if( m_iRunError != enCodeRunOK )
	{
		pt->MoationMotorErrorLockAll();
		return TRUE;
	}

	// Arm XY Run Line
	CPoint pp;
	pp = theApp.m_InputTray.GetCoordinate( m.m_VisionSet.lVisionPickDut );
	m_dArmX = pp.x;
	m_dArmY = pp.y;
	m_iRunError = f.Motor.ManualMotorRunLine(	
					&m.m_Motor.ArmX, m_dArmX, 
					&m.m_Motor.ArmY, m_dArmY,
					true, m.TimerSetting.iMotorRunlineTimeout );

	//
	if( m_iRunError != enCodeRunOK )
	{
		pt->MoationMotorErrorLockAll();
		return TRUE;
	}

	// Arm Z Down
	m_dArmZ = m.m_Align.Input.z2 + ( m.m_Offset.Input.z2 * m.m_Ratio.Z_GearRation );
	m_iRunError = f.Motor.ManualMotorRun( 
		&m.m_Motor.ArmZ, m_dArmZ, true, 
		m.TimerSetting.iMotorRunTimeout );
	
	//
	if( m_iRunError != enCodeRunOK )
	{
		pt->MoationMotorErrorLockAll();
		return TRUE;
	}

	// Blow
	f.ManualBlow( &m.OutSet.ArmVacc, 
				&m.OutSet.ArmBlow, 
				&m.InStatus.ArmZVaccSensor, 
				m.Timer.m_dPickPuff );

	// Arm Z Up
	m_iRunError = f.Motor.ManualMotorRun( 
		&m.m_Motor.ArmZ, ( _InitialZHome * m.m_Ratio.Z_GearRation ), false, 
		m.TimerSetting.iMotorRunTimeout );	

	//
	if( m_iRunError != enCodeRunOK )
	{
		pt->MoationMotorErrorLockAll();
		return TRUE;
	}

	m_dArmX = 0;
	m_dArmY = 0;
	m_iRunError = f.Motor.ManualMotorRunLine(	
					&m.m_Motor.ArmX, m_dArmX, 
					&m.m_Motor.ArmY, m_dArmY,
					true, m.TimerSetting.iMotorRunlineTimeout );
	//
	if( m_iRunError != enCodeRunOK )
	{
		pt->MoationMotorErrorLockAll();
		return TRUE;
	}

	// Change to READY
	m.Info.iStatus = theApp.enReady;
	f.UpdateButtonState();

	pt->m_IsDeviceIn = false;
	pt->MoationDeviceOutUI();

	return TRUE;
}
BOOL CDlgVisionSetup::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m.Info.bSubDlgOpen = true;
	f.UpdateButtonState();

	// init button 
	m_btnOK.SetIcon(IDI_OK);
	m_btnOK.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnOK.SetFlat(FALSE);
	
	m_btnCancel.SetIcon(IDI_CANCEL);
	m_btnCancel.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnCancel.SetFlat(FALSE);

	//
	m_btnGrab.SetIcon(IDI_RT_IMAGE);
	m_btnGrab.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnGrab.SetFlat(FALSE);

	m_btnLoad.SetIcon(IDI_OK);
	m_btnLoad.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnLoad.SetFlat(FALSE);

	m_btnSave.SetIcon(IDI_SAVE);
	m_btnSave.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnSave.SetFlat(FALSE);

	m_btnDelete.SetIcon(IDI_DELETE);
	m_btnDelete.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnDelete.SetFlat(FALSE);

	m_wndTestScore.SetText("", 14, "Arial Black", DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	m_wndTestScore.SetNewBkColor(ST_WHITE);

	//
	LiveLockUI(false);

	//
	MoationDeviceOutUI();

	//
	MoationDeviceMoveCheck();

	//
	InitLib();

	//
	InitImage();

	//
	InitTips();

	//
	InitValue();

	//
	UpdataSettingList();

	//
	SetInitialFile();

	//
//	UnLockDebugUI();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
void CDlgVisionSetup::InitValue()
{
	CString csMsg = _T("");
	csMsg.Format( "#%d", m.m_VisionSet.lVisionPickDut );
	GetDlgItem(IDC_PICK_DUT)->SetWindowText( csMsg );
}
void CDlgVisionSetup::UnLockDebugUI()
{

#ifdef _Demo
	GetDlgItem(IDC_TEST)->ShowWindow( TRUE );
	GetDlgItem(IDC_CLEAR)->ShowWindow( TRUE );
	GetDlgItem(IDC_STATIC_MATCH_FAIL)->ShowWindow( TRUE );
	GetDlgItem(IDC_STATIC_MATCH_PASS)->ShowWindow( TRUE );
	GetDlgItem(IDC_STATIC_PICK_DUT)->ShowWindow( TRUE );
	GetDlgItem(IDC_FAIL_COUNT)->ShowWindow( TRUE );
	GetDlgItem(IDC_MATCH_COUNT)->ShowWindow( TRUE );
	GetDlgItem(IDC_PICK_DUT)->ShowWindow( TRUE );
#endif

}
void CDlgVisionSetup::Message( CString csMsg)
{
	if( csMsg != "" )
	{
		AfxMessageBox( csMsg );
	}
}
void CDlgVisionSetup::SetInitialFile()
{
	m_listFileFolder.SetCurSel(0);

	FunctionLoad();
}
void CDlgVisionSetup::InitTips()
{
	// Tips 
	// Init Tips
	m_ToolTip.Create(this);
	m_ToolTip.SetMaxTipWidth(800);
	m_ToolTip.SetDelayTime( TTDT_AUTOPOP, 10000 );
	m_ToolTip.SetDelayTime( TTDT_INITIAL, 25 );
	m_ToolTip.EnableToolTips(true);

	m_ToolTip.AddTool( GetDlgItem(IDC_INPUT_DEVICE),	_T("Arm XY Pick #dut1 IC to Socket") );
	m_ToolTip.AddTool( GetDlgItem(IDC_OUTPUT_DEVICE),	_T("Arm XY Pick IC from Socket, back to #dut1") );

	m_ToolTip.AddTool( GetDlgItem(IDC_GRAB),			_T("Grab Image Profile") );
	m_ToolTip.AddTool( GetDlgItem(IDC_LOAD),			_T("Load Image Profile") );
	m_ToolTip.AddTool( GetDlgItem(IDC_SAVE),			_T("Save Image Profile") );
	m_ToolTip.AddTool( GetDlgItem(IDC_DELETE),			_T("Delete Image Profile") );
	m_ToolTip.AddTool( GetDlgItem(IDC_MATCH),			_T("Match") );
	
	m_ToolTip.AddTool( GetDlgItem(IDC_STOP),			_T("Stop to live") );
	m_ToolTip.AddTool( GetDlgItem(IDC_LIVE),			_T("Start to live") );
}
void CDlgVisionSetup::InitLib()
{

}
void CDlgVisionSetup::InitImage()
{
	CRect rectImage, rectPatternImage;
	m_stcPicture.GetClientRect( rectImage );

	// Grab Image
	pViewGrabImage = new CViewImage();
	pViewGrabImage->Create(NULL, "Image", WS_CHILD | WS_VISIBLE, rectImage, 
		(CWnd *)&m_stcPicture, IDC_WINDOW_DRAW);	
}
void CDlgVisionSetup::GetSettingFolder()
{
	//
	m_FileDictory.RemoveAll();

	//
	CString csFilePath = _T("");
	csFilePath = m.FilePath.CCDImageProfilePath;

	//
	CFileFind finder;											//建立搜尋用的CFileFind物件
	BOOL bResult = finder.FindFile( csFilePath  + "*.*" );		//尋找第一個檔案
	while(bResult)
	{
		bResult = finder.FindNextFile();						//尋找下一個檔案
		if(!finder.IsDots() && finder.IsDirectory())
		{
			CString csFileDirectory;
			csFileDirectory.Format("%s", finder.GetFileTitle() );
			
			m_FileDictory.Add( csFileDirectory );
		}
	}
}
void CDlgVisionSetup::UpdataSettingList()
{
	//
	GetSettingFolder();

	//
	m_listFileFolder.ResetContent();
	int iSize = m_FileDictory.GetSize();
	
	for(int i=0;i<iSize;i++)
	{
		m_listFileFolder.AddString( m_FileDictory.GetAt(i) );
	}
}
void CDlgVisionSetup::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	
	CDialog::OnTimer(nIDEvent);
}

void CDlgVisionSetup::OnOK() 
{
	m.Info.bSubDlgOpen = false;
	f.UpdateButtonState();
	
	CDialog::OnOK();
}

void CDlgVisionSetup::OnCancel() 
{
	//
	if(m.m_Vision.m_bCameraLive)
		CameraLiveStop();

	//
	m.Info.bSubDlgOpen = false;
	f.UpdateButtonState();

	//
	CDialog::OnCancel();
}

void CDlgVisionSetup::OnInputDevice() 
{	
	MoationLockUI( true );
	AfxBeginThread(DeviceInThread, this);
}

void CDlgVisionSetup::OnOutputDevice() 
{
	MoationLockUI( true );
	AfxBeginThread(DeviceOutThread, this);
}

void CDlgVisionSetup::OnMatch() 
{
	// 先取像. 這樣才可以用取到的像跟設定檔比
	CameraCapture();

	//
	CString csPatternPath = _T("");
	CString csFileFolderName = _T("");
	CString csImageFileName = _T("");
	CString csSettingPath = _T("");

	// 設定 Pattern 的路徑
	csSettingPath = GetSettingFileName();
	csImageFileName = GetSettingFileName();
	csFileFolderName = m.FilePath.CCDImageProfilePath + csSettingPath + "\\" + csImageFileName;
	csPatternPath = csFileFolderName + _CCDImageName2;

	// 設定 Grab 的路徑
	CString csGrabPath = _T("");
	csGrabPath = m.FilePath.CCDImagePath + _CCDPin1;

	// 設定 ROI
	CRect rect;
	CString csInfoPath = _T("");
	rect.left = 0;
	rect.right = 0;
	rect.top = 0;
	rect.bottom = 0;
	rect = GetSettingROI();
	
	//
	double dScore = 0.0;
	double dResult = 0.0;
	dScore = GetSettingScore();
	dResult = m_VisionMatch.MatchCheck( m.m_CCDPin1Control.iCCDUse, 
		csPatternPath, csGrabPath, _CCDPin1, _CCDSubPin1, rect  );

	//
	MatchResult( dResult, dScore );
}
void CDlgVisionSetup::MatchResult(double dResult, double dScore)
{
	bool bPass = false;

	if( dResult >= dScore )
		bPass = true;
	else 
		bPass = false;

	//
	CString csResult = _T("");
	csResult.Format("%5.2f", dResult );
	m_wndTestScore.SetWindowText( csResult );

	//
	if( bPass )
		m_wndTestScore.SetNewBkColor( ST_GREEN );
	else
		m_wndTestScore.SetNewBkColor( ST_RED );
}
void CDlgVisionSetup::OnGrab() 
{
	CaptureLockUI( true );
	CameraCapture();
	FunctionNewLoad();
	CaptureLockUI( false );	
}
CString CDlgVisionSetup::GetCurrentSettingFileName()
{
	CString csSettingCurrentFolderName = _T("");
	m_listFileFolder.GetWindowText(csSettingCurrentFolderName);

	csSettingCurrentFolderName.TrimLeft();
	csSettingCurrentFolderName.TrimRight();

	return csSettingCurrentFolderName;
}
CString CDlgVisionSetup::GetSettingFileName()
{
	int iSel = m_listFileFolder.GetCurSel();
	CString csSettingFolderName = _T("");

	if( iSel == -1 )
	{
		// 錯誤, 他只能用選的.
	}
	else
	{
		// 是用選的
		m_listFileFolder.GetLBText( iSel, csSettingFolderName );
	}
	
	//
	csSettingFolderName.TrimLeft();
	csSettingFolderName.TrimRight();

	return csSettingFolderName; 
}
CRect CDlgVisionSetup::GetSettingROI()
{
	CRect rect;
	rect.top = 0;
	rect.bottom = 0;
	rect.left = 0;
	rect.right = 0;

	CString csFolderName = _T("");
	CString csInfoName = _T("");
	csInfoName = csFolderName = GetSettingFileName();

	CString csFile = _T("");
	csFile = m.FilePath.CCDImageProfilePath + csFolderName + "\\" + csInfoName + _CCDName2;

	int iX = 0;
	int iY = 0;
	int iWidth = 0;
	int iHeight = 0;

	f.GetSetting( csFile, "Source Image", "X",		iX );
	f.GetSetting( csFile, "Source Image", "Y",		iY );
	f.GetSetting( csFile, "Source Image", "Width",	iWidth );
	f.GetSetting( csFile, "Source Image", "Height", iHeight );

	//
	rect.top	= iY + _VisionOffset;
	rect.left	= iX;
	rect.bottom	= iY + iHeight + _VisionOffset;
	rect.right	= iX + iWidth;

	return rect;
}
double CDlgVisionSetup::GetSettingScore()
{
	double dGetScore = 0.0;

	CString csFolderName = _T("");
	CString csInfoName = _T("");
	csInfoName = csFolderName = GetSettingFileName();

	CString csFile = _T("");
	csFile = m.FilePath.CCDImageProfilePath + csFolderName + "\\" + csInfoName + _CCDName2;

	//
	f.GetSetting( csFile, "Source Image", "Score",	dGetScore );

	return dGetScore;
}
void CDlgVisionSetup::GetSettingFolderInfo()
{
	// 從檔案讀出資料
	//////////////////////////////////////////////////////////////
	tagInfoParameter m_Info;

	//
	CString csFolderName = _T("");
	CString csInfoName = _T("");
	csInfoName = csFolderName = GetSettingFileName();
	
	CString csFile = _T("");
	csFile = m.FilePath.CCDImageProfilePath + csFolderName + "\\" + csInfoName + _CCDName2;

	f.GetSetting( csFile, "Source Image", "X",		m_Info.iX );
	f.GetSetting( csFile, "Source Image", "Y",		m_Info.iY );
	f.GetSetting( csFile, "Source Image", "Width",	m_Info.iWidth );
	f.GetSetting( csFile, "Source Image", "Height", m_Info.iHeight );	
	f.GetSetting( csFile, "Source Image", "Score",	m_Info.dScore );

	// 把內容顯示到畫面
	CString csHeight = _T("");
	CString csWidth = _T("");
	CString csY	= _T("");
	CString csX = _T("");
	CString csScore = _T("");

	csHeight.Format("%d", m_Info.iHeight );
	m_wndScoreHeight.SetWindowText( csHeight );
	csWidth.Format("%d", m_Info.iWidth );
	m_wndScoreWidth.SetWindowText( csWidth );
	csY.Format("%d", m_Info.iY );
	m_wndScoreY.SetWindowText( csY );
	csX.Format("%d", m_Info.iX );
	m_wndScoreX.SetWindowText( csX );

	csScore.Format("%5.2f", m_Info.dScore );
	csScore.TrimLeft();
	csScore.TrimRight();
	m_wndScoreMinMatchScore.SetWindowText( csScore );
}
void CDlgVisionSetup::UpdataPatternInfo()
{
	int top		= 0;
	int left	= 0;
	int bottom	= 0;
	int right	= 0;

	pViewGrabImage->GetPatternInfo(top, left, bottom, right );
	CString csTop		= _T("");
	CString csLeft		= _T("");
	CString csBottom	= _T("");
	CString csRight		= _T("");

	csTop.Format("%d",		top );
	csLeft.Format("%d",		left );
	csBottom.Format("%d",	bottom - top );
	csRight.Format("%d",	right - left );

	//
	m_wndScoreHeight.SetWindowText( csBottom );
	m_wndScoreWidth.SetWindowText( csRight );
	m_wndScoreY.SetWindowText( csTop );
	m_wndScoreX.SetWindowText( csLeft );
}
LRESULT CDlgVisionSetup::OnPosInfo(WPARAM p, LPARAM l)
{
	UpdataPatternInfo();

	return true;
}
void CDlgVisionSetup::FunctionSave()
{
	try
	{
		// 從介面取回數值
		//////////////////////////////////////////////////////////////
		CString csTop	= _T("");
		CString csLeft	= _T("");
		CString csBottom = _T("");
		CString csRight = _T("");
		CString csScore = _T("");

		m_wndScoreHeight.GetWindowText( csBottom ); 
		m_wndScoreWidth.GetWindowText( csRight );
		m_wndScoreY.GetWindowText( csTop );
		m_wndScoreX.GetWindowText( csLeft );
		m_wndScoreMinMatchScore.GetWindowText( csScore );

		// 把數值存回檔案
		int iHeight = 0;
		iHeight = atoi( csBottom );
		int iWidth = 0;
		iWidth = atoi( csRight );
		int iX = 0;
		iX = atoi( csLeft );
		int iY = 0;
		iY = atoi( csTop );
		double dScore = atof( csScore );

		tagInfoParameter m_Info;

		//
		m_Info.dScore = dScore;
		m_Info.iX = iX;
		m_Info.iY = iY;
		m_Info.iHeight = iHeight;
		m_Info.iWidth = iWidth;

		CString csFolderName = _T("");
		CString csInfoName = _T("");
		csInfoName = csFolderName = GetSettingFileName();
	
		CString csFile = _T("");
		csFile = m.FilePath.CCDImageProfilePath + csFolderName + "\\" + csInfoName + _CCDName2;
	
		f.SaveSetting( csFile, "Source Image", "X",			m_Info.iX );	
		f.SaveSetting( csFile, "Source Image", "Y",			m_Info.iY );	
		f.SaveSetting( csFile, "Source Image", "Width",		m_Info.iWidth );	
		f.SaveSetting( csFile, "Source Image", "Height",	m_Info.iHeight );		
		f.SaveSetting( csFile, "Source Image", "Score",		m_Info.dScore );
	}	
	catch(...)
	{
		Message("Function Save Excute Fail.!");
	}	
}
CRect CDlgVisionSetup::GetDefaulePatternInfo()
{
	CRect m_DefFileRect;

	//
	m_DefFileRect.top		= m.m_CCDPin1Control.RoiY;
	m_DefFileRect.left		= m.m_CCDPin1Control.RoiX;
	m_DefFileRect.bottom	= m.m_CCDPin1Control.RoiY + m.m_CCDPin1Control.RoiH;
	m_DefFileRect.right		= m.m_CCDPin1Control.RoiX + m.m_CCDPin1Control.RoiW;

	return m_DefFileRect;
}
void CDlgVisionSetup::SetPatternInfo(CString csPath, tagInfoParameter m_Info)
{
	CString csFile = _T("");
	csFile = csPath;

	f.SaveSetting( csFile, "Source Image", "X",			m_Info.iX );
	f.SaveSetting( csFile, "Source Image", "Y",			m_Info.iY );
	f.SaveSetting( csFile, "Source Image", "Width",		m_Info.iWidth );
	f.SaveSetting( csFile, "Source Image", "Height",	m_Info.iHeight );	
	f.SaveSetting( csFile, "Source Image", "Score",		m_Info.dScore );	
}
CRect CDlgVisionSetup::GetPatternInfo()
{
	CRect m_FileRect;
	
	//
	tagInfoParameter m_Info;

	//
	CString csFolderName = _T("");
	CString csInfoName = _T("");
	csInfoName = csFolderName = GetSettingFileName();
	
	CString csFile = _T("");
	csFile = m.FilePath.CCDImageProfilePath + csFolderName + "\\" + csInfoName + _CCDName2;

	f.GetSetting( csFile, "Source Image", "X",		m_Info.iX );
	f.GetSetting( csFile, "Source Image", "Y",		m_Info.iY );
	f.GetSetting( csFile, "Source Image", "Width",	m_Info.iWidth );
	f.GetSetting( csFile, "Source Image", "Height", m_Info.iHeight );	
	f.GetSetting( csFile, "Source Image", "Score",	m_Info.dScore );

	m_FileRect.top		= m_Info.iY;
	m_FileRect.left		= m_Info.iX;
	m_FileRect.bottom	= m_Info.iY + m_Info.iHeight;
	m_FileRect.right	= m_Info.iX + m_Info.iWidth;

	return m_FileRect;
}
void CDlgVisionSetup::FunctionDelete()
{
	// Check Message
	CString VisionFileName = GetSettingFileName();
	CString csDel = _T("");
	csDel.Format("Delete this file [%s]. ?", VisionFileName);
	if(IDNO == MessageBox(csDel, "3111", MB_ICONSTOP | MB_YESNO))
		return;

	// 確認是否在使用中
	CString VisionFile = GetSettingFileName();
	CString csTrayFile = _T("");
	bool bUsing = CheckTrayIsUse( VisionFile, csTrayFile );
	if( !bUsing )
	{
		CString csMsg = _T("");
		CString csF = _T("");
		csF = VisionFile;
		csMsg.Format("[%s] in using.in [%s], Please change it then delete.", csF, csTrayFile );
		AfxMessageBox( csMsg );
		return;
	}

	// 刪除 *.IMG (參數檔), 刪除 *.bmp
	DeleteIMGFile( VisionFile );

	// 更新列表
	UpdataSettingList();

	// 重新選回第一個
	SetInitialFile();
}
void CDlgVisionSetup::FunctionNew()
{
	try
	{
		//
		CString csNewFolderSetting = _T("");
		csNewFolderSetting = GetCurrentSettingFileName();

		// 根據輸入的字樣創造一個新的資料夾
		//////////////////////////////////////////////////////////////
		CString csNewFolderSettingPath = _T("");
		csNewFolderSettingPath = m.FilePath.CCDImageProfilePath + csNewFolderSetting;
		f.AutoCreateFolder( csNewFolderSettingPath );

		// 把當下 Grab.bmp 複製到 Profile 資料夾
		//////////////////////////////////////////////////////////////
		GetSettingFolder();	// 更新資料夾
		int iSize = m_FileDictory.GetSize();
		bool bExist = false;
		for(int i=0;i<iSize;i++)
		{
			CString csFolderName = m_FileDictory.GetAt(i);
			if( csNewFolderSetting == csFolderName )
			{
				bExist = true;
				break;
			}
		}

		// 資料夾存在, 把檔案複製進去, 並且改名
		//////////////////////////////////////////////////////////////
		if( bExist )
		{
			CString csGrabImagePath = _T("");
			CString csCopyImagePath = _T("");
			csGrabImagePath = m.FilePath.CCDImagePath + _CCDPin1;
			csCopyImagePath = m.FilePath.CCDImageProfilePath + csNewFolderSetting + "\\" +
				csNewFolderSetting + _CCDImageName2;
			::CopyFile( csGrabImagePath, csCopyImagePath, TRUE );					
		}

		// 資料夾存在, 產生新的 Info
		//////////////////////////////////////////////////////////////
		if( bExist )
		{
			CString csNewInfoPath = _T("");
			csNewInfoPath = m.FilePath.CCDImageProfilePath + csNewFolderSetting + "\\" +
				csNewFolderSetting + _CCDName2;
			
			CString csTop	= _T("");
			CString csLeft	= _T("");
			CString csBottom = _T("");
			CString csRight = _T("");
			CString csScore = _T("");
			
			m_wndScoreHeight.GetWindowText( csBottom ); 
			m_wndScoreWidth.GetWindowText( csRight );
			m_wndScoreY.GetWindowText( csTop );
			m_wndScoreX.GetWindowText( csLeft );
			m_wndScoreMinMatchScore.GetWindowText( csScore );
			
			// 把數值存回檔案
			int iHeight = 0;
			iHeight = atoi( csBottom );
			int iWidth = 0;
			iWidth = atoi( csRight );
			int iX = 0;
			iX = atoi( csLeft );
			int iY = 0;
			iY = atoi( csTop );
			double dScore = atof( csScore );
			
			tagInfoParameter m_Info;
			
			//
			m_Info.dScore = dScore;
			m_Info.iX = iX;
			m_Info.iY = iY;
			m_Info.iHeight = iHeight;
			m_Info.iWidth = iWidth;
			SetPatternInfo( csNewInfoPath, 	m_Info );			
		}

		// Create 資料夾失敗
		//////////////////////////////////////////////////////////////
		if( !bExist )
		{
			CString csErrMsg = _T("");
			csErrMsg.Format("Create new folder fail");
			AfxMessageBox( csErrMsg );		
		}
	}
	catch(...)
	{
		Message("Function New Excute Fail.!");
	}
}
bool CDlgVisionSetup::IsFileExist()
{
	bool bFolderExist = false;
	
	return bFolderExist;
}
void CDlgVisionSetup::FunctionNewLoad()
{
	try
	{
		// 取的圖片名稱 (Grab)
		//////////////////////////////////////////////////////////////
		CString csFolderName = _T("");
		csFolderName = m.FilePath.CCDImagePath + _CCDPin1;

		// 顯示圖片
		//////////////////////////////////////////////////////////////
		// Load Image.
		CString csGrabImage = _T("");
		csGrabImage.Format("%s", csFolderName );

		char *szBuf = new char[csGrabImage.GetLength()+1];
		memset(szBuf, 0, csGrabImage.GetLength());
		strcpy(szBuf, (LPCTSTR)csGrabImage);
		BOOL bGrabSuccess = m_VisionMatch.m_VisionCtrl.pLoadCImage(m_VisionMatch.m_VisionCtrl.hHandleInspect, szBuf);

		HBITMAP *pGrabBitmap = NULL;

		CRect m_FileRect = GetDefaulePatternInfo();	

		pViewGrabImage->SetPatternInfomation( m_FileRect.top, m_FileRect.left, m_FileRect.bottom, m_FileRect.right );
		pGrabBitmap = m_VisionMatch.m_VisionCtrl.pGetBitmapAddress(m_VisionMatch.m_VisionCtrl.hHandleInspect);
		pViewGrabImage->SetBmpAddress( pGrabBitmap );

		//
		delete []szBuf;
	}	
	catch(...)
	{
		Message("Function New(Grab) Excute Fail.!");
	}	
}
CString CDlgVisionSetup::CopyImageToTemp()
{
	//
	CString csFinalFilePath = _T("");

	//
	CString csImageName = _T("");
	CString csFolderName = _T("");
	csImageName = csFolderName = GetSettingFileName();

	CString csFileSource = _T("");
	csFileSource = m.FilePath.CCDImageProfilePath + csFolderName + "\\" + csImageName + _CCDImageName2;
	CString csFileDestion = _T("");
	csFileDestion = m.FilePath.CCDImagePath + _CCDShowPin1;

	//
	::CopyFile(csFileSource, csFileDestion, TRUE);

	csFinalFilePath = csFileDestion;

	return csFinalFilePath;
}
void CDlgVisionSetup::FunctionLoad()
{
	try
	{
		// 取的圖片名稱
		//////////////////////////////////////////////////////////////
		CString csFolderName = _T("");
		CString csImageName = _T("");
		csImageName = csFolderName = GetSettingFileName();

		// 顯示圖片
		//////////////////////////////////////////////////////////////
		// Load Image.
		CString csGrabImage = _T("");
		csGrabImage.Format("%s", 
			m.FilePath.CCDImageProfilePath + csFolderName + 
			"\\" + csImageName + _CCDImageName2 );
		
		//
		char *szBuf = new char[csGrabImage.GetLength()+1];
		memset(szBuf, 0, csGrabImage.GetLength());
		strcpy(szBuf, (LPCTSTR)csGrabImage);
		BOOL bGrabSuccess = m_VisionMatch.m_VisionCtrl.pLoadCImage(m_VisionMatch.m_VisionCtrl.hHandleInspect, szBuf);

		HBITMAP *pGrabBitmap = NULL;

		CRect m_FileRect = GetPatternInfo();	

		pViewGrabImage->SetPatternInfomation( m_FileRect.top, m_FileRect.left, m_FileRect.bottom, m_FileRect.right );
		pGrabBitmap = m_VisionMatch.m_VisionCtrl.pGetBitmapAddress(m_VisionMatch.m_VisionCtrl.hHandleInspect);
		pViewGrabImage->SetBmpAddress( pGrabBitmap );

		//
		delete []szBuf;

		// 取得 Image Info 相關資料
		GetSettingFolderInfo();

		// 把檔案名稱顯示到介面上
		m_wndFileName.SetWindowText( csImageName );
		//////////////////////////////////////////////////////////////
	}	
	catch(...)
	{
		Message("Function Load Excute Fail.!");
	}	
}
void CDlgVisionSetup::OnLoad() 
{
	CString csSettingFolder = GetCurrentSettingFileName();
	if( csSettingFolder == "" )
	{
		CString csMsg = _T("");
		csMsg.Format("Empty, Please select new one");
		AfxMessageBox( csMsg );
	}
	else
	{
		FileLockUI( true );
		FunctionLoad();
		FileLockUI( false );
	}
}

void CDlgVisionSetup::OnSave() 
{
	// check score first, Is score in range.
	CString m_csGetScore = _T("");
	m_wndScoreMinMatchScore.GetWindowText( m_csGetScore );
	m_csGetScore.TrimLeft();
	m_csGetScore.TrimRight();
	if( m_csGetScore == "" )
	{
		CString csMsg = _T("");
		csMsg.Format("Score is empty, Please enter a value.");
		AfxMessageBox( csMsg );
		m_wndScoreMinMatchScore.SetFocus();
		return;
	}
	double m_dGetScore = 1.0;
	m_dGetScore = atof( m_csGetScore );
	if( m_dGetScore > 1.00 || m_dGetScore < 0.0 )
	{
		CString csMsg = _T("");
		csMsg.Format("[%4.2f]Score is out of range\r\nThe range is 0.00~1.00\r\nPlease re-enter new value", m_dGetScore );
		AfxMessageBox( csMsg );
		m_wndScoreMinMatchScore.SetFocus();
		return;
	}

	//
	CString csSettingFolder = GetCurrentSettingFileName();
	if( csSettingFolder == "" )
	{
		CString csMsg = _T("");
		csMsg.Format("Empty, Please select new one or create new");
		AfxMessageBox( csMsg );
	}
	else
	{
		// Check folder exist or not
		int iSize = m_FileDictory.GetSize();
		bool bExist = false;
		for(int i=0;i<iSize;i++)
		{
			CString csFolderName = _T("");
			csFolderName = m_FileDictory.GetAt(i);
			if( csFolderName == csSettingFolder )
			{
				bExist = true;
				break;
			}
		}

		if(bExist)
		{
			FileLockUI( true );
			FunctionSave();			// Folder exist, so save value to file
			FileLockUI( false );
		}
		else
		{
			FileLockUI( true );
			FunctionNew();			// Folder not exist, so create new one
			UpdataSettingList();
			FileLockUI( false );
		}
	}
}

void CDlgVisionSetup::OnDelete() 
{
	FileLockUI( true );
	FunctionDelete();
	FileLockUI( false );
}

void CDlgVisionSetup::OnStop() 
{
	CameraLiveStop();
}
void CDlgVisionSetup::LiveLockUI(bool bEnable)
{
	if( bEnable )
	{
		// Live.. Lock all
		BOOL bEnable = FALSE;
		m_btnGrab.EnableWindow( bEnable );
		m_btnDelete.EnableWindow( bEnable );
		m_btnSave.EnableWindow( bEnable );
		m_btnLoad.EnableWindow( bEnable );
		m_listFileFolder.EnableWindow( bEnable );
		m_btnStop.EnableWindow( !bEnable );
		m_btnLive.EnableWindow( bEnable );

		//
		m_btnDeviceInput.EnableWindow( bEnable );
		m_btnDeviceOutput.EnableWindow( bEnable );
		m_btnMatch.EnableWindow( bEnable );

		//
		m_stcPicture.EnableWindow( bEnable );
	}
	else
	{
		// Stop Live.. Unlock all
		BOOL bEnable = TRUE;
		m_btnGrab.EnableWindow( bEnable );
		m_btnDelete.EnableWindow( bEnable );
		m_btnSave.EnableWindow( bEnable );
		m_btnLoad.EnableWindow( bEnable );
		m_listFileFolder.EnableWindow( bEnable );
		m_btnStop.EnableWindow( !bEnable );
		m_btnLive.EnableWindow( bEnable );

		//
		m_btnDeviceInput.EnableWindow( bEnable );
		m_btnDeviceOutput.EnableWindow( !bEnable );
		m_btnMatch.EnableWindow( bEnable );

		//
		m_stcPicture.EnableWindow( bEnable );
	}
}
void CDlgVisionSetup::FileLockUI(bool bEnable)
{
	if( bEnable )
	{
		// File Lock all
		BOOL bEnable = FALSE;
		m_btnGrab.EnableWindow( bEnable );
		m_btnDelete.EnableWindow( bEnable );
		m_btnSave.EnableWindow( bEnable );
		m_btnLoad.EnableWindow( bEnable );
		m_listFileFolder.EnableWindow( bEnable );
		m_btnStop.EnableWindow( bEnable );
		m_btnLive.EnableWindow( bEnable );

		//
		m_btnDeviceInput.EnableWindow( bEnable );
		m_btnDeviceOutput.EnableWindow( bEnable );
		m_btnMatch.EnableWindow( bEnable );

		//
		m_stcPicture.EnableWindow( bEnable );
	}
	else
	{
		// File complete, Unlock all
		BOOL bEnable = TRUE;
		m_btnGrab.EnableWindow( bEnable );
		m_btnDelete.EnableWindow( bEnable );
		m_btnSave.EnableWindow( bEnable );
		m_btnLoad.EnableWindow( bEnable );
		m_listFileFolder.EnableWindow( bEnable );
		m_btnStop.EnableWindow( !bEnable );
		m_btnLive.EnableWindow( bEnable );

		//
		m_btnDeviceInput.EnableWindow( bEnable );
		m_btnDeviceOutput.EnableWindow( !bEnable );
		m_btnMatch.EnableWindow( bEnable );

		//
		m_stcPicture.EnableWindow( bEnable );		
	}
}
void CDlgVisionSetup::CaptureLockUI(bool bEnable)
{
	if( bEnable )
	{
		// Grab Lock all
		BOOL bEnable = FALSE;
		m_btnGrab.EnableWindow( bEnable );
		m_btnDelete.EnableWindow( bEnable );
		m_btnSave.EnableWindow( bEnable );
		m_btnLoad.EnableWindow( bEnable );
		m_listFileFolder.EnableWindow( bEnable );
		m_btnStop.EnableWindow( bEnable );
		m_btnLive.EnableWindow( bEnable );

		//
		m_btnDeviceInput.EnableWindow( bEnable );
		m_btnDeviceOutput.EnableWindow( bEnable );
		m_btnMatch.EnableWindow( bEnable );

		//
		m_stcPicture.EnableWindow( bEnable );
	}
	else
	{
		// Grab complete, Unlock all
		BOOL bEnable = TRUE;
		m_btnGrab.EnableWindow( bEnable );
		m_btnDelete.EnableWindow( bEnable );
		m_btnSave.EnableWindow( bEnable );
		m_btnLoad.EnableWindow( bEnable );
		m_listFileFolder.EnableWindow( bEnable );
		m_btnStop.EnableWindow( !bEnable );
		m_btnLive.EnableWindow( bEnable );

		//
		m_btnDeviceInput.EnableWindow( bEnable );
		m_btnDeviceOutput.EnableWindow( !bEnable );
		m_btnMatch.EnableWindow( bEnable );

		//
		m_stcPicture.EnableWindow( bEnable );		
	}
}
void CDlgVisionSetup::CameraCapture()
{
	CDC* pDC = GetDlgItem(IDC_WINDOW_DRAW)->GetDC();
	HDC hDC = pDC->GetSafeHdc();

	CRect rect;
	GetDlgItem(IDC_WINDOW_DRAW)->GetClientRect(&rect);

	CString csImagePath = _T("");
	csImagePath = m.FilePath.CCDImagePath + _CCDPin1;
	if(m.m_Vision.CameraGrabSave(m.m_CCDPin1Control.iCCDUse, csImagePath))
	{
//		m.m_Vision.Draw(hDC,rect, &m.m_Vision.m_CaptureFrame[m.m_CCDPin1Control.iCCDUse] );	
	}
	else
	{
		// Grab Error
		CString csMsg = _T("");
		csMsg.Format("Grab Fail");
		AfxMessageBox( csMsg );
	}
}
void CDlgVisionSetup::CameraLive()
{
	// 啟動 Live
	LiveLockUI( true );
	m.m_Vision.m_bCameraLive = true;

/*
	hProcess = CreateThread(NULL, NULL, WorkerThreadGrab, this, FALSE, 
		&m_dwThreadIdCamera);
*/

	hProcess = AfxBeginThread(WorkerThreadGrab, this);
}
UINT CDlgVisionSetup::WorkerThreadGrab(LPVOID p)
{
	CDlgVisionSetup* pThis = (CDlgVisionSetup*)p;

	CDC* pDC = pThis->GetDlgItem(IDC_WINDOW_DRAW)->GetDC();
	HDC hDC = pDC->GetSafeHdc();

	CRect rect;
	pThis->GetDlgItem(IDC_WINDOW_DRAW)->GetClientRect(&rect);

	while( m.m_Vision.m_bCameraLive )
	{
		if( m.m_Vision.CameraGrab( m.m_CCDPin1Control.iCCDUse ) )
		{
			m.m_Vision.Draw(hDC, rect, &m.m_Vision.m_CaptureFrame[m.m_CCDPin1Control.iCCDUse] );
		}
		else
			break;
		Sleep(1);
	}

	return 0;
}
void CDlgVisionSetup::CameraLiveStop()
{
	// 已經在 Live 現在要關掉 Live	
	m.m_Vision.m_bCameraLive = false;

	// 
	BOOL bSuccess = FALSE;
	DWORD nThread = 0;
	do
	{
		bSuccess = GetExitCodeThread( hProcess, &nThread );
		Sleep(1);
	}
	while(bSuccess && nThread == STILL_ACTIVE);

	//
	if( m_IsDeviceIn )
		MoationDeviceInUI();
	else
		LiveLockUI( false );
}
void CDlgVisionSetup::OnLive() 
{
	CameraLive();
}

void CDlgVisionSetup::OnTest() 
{
	
}

void CDlgVisionSetup::OnClear() 
{
	
}

void CDlgVisionSetup::OnSetScope() 
{
	
}

void CDlgVisionSetup::OnSetDefault() 
{
	
}
bool CDlgVisionSetup::DeleteIMGFile(CString csSettingName)
{
	// copy
	bool bOK = true;

	CString csSourceFolderPath = _T("");
	CString csDestFolderPath = _T("");

	csSourceFolderPath = m.FilePath.CCDImageProfilePath + csSettingName + "\\";
	csDestFolderPath = m.FilePath.CCDImageBackPath + csSettingName + "\\";

	// Delete Exist Folder Files
	f.m_FileCtrl.DoDeleteFolderFile( csDestFolderPath, ".*");

	// Delete Exist Folder
	f.m_FileCtrl.DoDeleteFolder( csDestFolderPath );

	// Create Folder For Backup
	f.AutoCreateFolder( csDestFolderPath );

	// Backup Setting Folder (Copy Files to Backup Folder)
	CString csSourceCopyPath = _T("");
	CString csDestCopyPath = _T("");
	csSourceCopyPath = m.FilePath.CCDImageProfilePath + csSettingName;
	csDestCopyPath = m.FilePath.CCDImageBackPath + csSettingName;
	f.m_FileCtrl.DoCopyFolderFile( csSourceCopyPath, csDestCopyPath, ".*" );

	// Delete Old Folder Files (.bmp)
	f.m_FileCtrl.DoDeleteFolderFile( csSourceFolderPath, _CCDImageName2);

	// Check Image Exist
	if( f.m_FileCtrl.IsFileExist(csSourceFolderPath, _CCDImageName2) )
	{
		bOK = false;
		return bOK;
	}

	// Delete Old Filder Files (.IMG)
	f.m_FileCtrl.DoDeleteFolderFile( csSourceFolderPath, _CCDName2);

	// Delete Old Folder
	f.m_FileCtrl.DoDeleteFolder( csSourceFolderPath );

	return bOK;
}
bool CDlgVisionSetup::CheckTrayIsUse(CString csFileName, CString &csNowFileName)
{
	bool bOK = true;	// 如果有在使用 就 return false
	
	CFileFind find;	
	BOOL bResult = find.FindFile( m.FilePath.TrayFilesPath + _SubFileName1 );
	CString file;
	while(bResult)
	{
		bResult = find.FindNextFile();
		file = find.GetFileName();
		CString csVision = "";
		if(file.Find( _SubFileName2, 0)>-1)
		{
			CString csFile;
			csFile = m.FilePath.TrayFilesPath + file;
			f.GetSetting(csFile, "Vision Pattern", "File",	csVision );
			
			CString File = csFileName + _CCDName2;
			if( File == csVision ) 
			{
				csNowFileName = file;
				CString f;
				f = _SubFileName2;
				int s = f.GetLength();
				csNowFileName = csNowFileName.Left( csNowFileName.GetLength() - s );	// 拿掉附檔名
				bOK = false;
				break;
				// 這個檔案被使用中
			}
		}
	}
	find.Close();

	return bOK;
}

void CDlgVisionSetup::OnClose() 
{
	if( pViewGrabImage != NULL )
	{
		delete pViewGrabImage;
		pViewGrabImage = NULL;
	}
	
	CDialog::OnClose();
}
