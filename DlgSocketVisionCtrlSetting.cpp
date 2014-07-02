// DlgSocketVisionCtrlSetting.cpp : implementation file
//

#include "stdafx.h"
#include "deer.h"
#include "DlgSocketVisionCtrlSetting.h"

//
#include "CtrlVisionMatch.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgSocketVisionCtrlSetting dialog


CDlgSocketVisionCtrlSetting::CDlgSocketVisionCtrlSetting(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgSocketVisionCtrlSetting::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgSocketVisionCtrlSetting)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

void CDlgSocketVisionCtrlSetting::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgSocketVisionCtrlSetting)
	DDX_Control(pDX, IDC_SETUP_GRABIMAGE1,				m_wndGrabImage);
	DDX_Control(pDX, IDC_SETUP_PATTERN1,				m_wndPatternImage);
	DDX_Control(pDX, IDC_SOCKETVISION_SHOWWINDOW,		m_wndImage);
	DDX_Control(pDX, IDC_MATCH_TESTSCORE,				m_wndTestScore);
	DDX_Text(pDX, IDC_SOCKETVISION_INFOROIX,			m_iMatchROIX);
	DDX_Text(pDX, IDC_SOCKETVISION_INFOROIY,			m_iMatchROIY);
	DDX_Text(pDX, IDC_SOCKETVISION_INFOROIWIDTH,		m_iMatchWidth);
	DDX_Text(pDX, IDC_SOCKETVISION_INFOROIHEIGHT,		m_iMatchHeight);
	DDX_Text(pDX, IDC_SOCKETVISION_INFOMINSCORE,		m_dMatchMinScore);	
	DDX_Control(pDX, IDC_SOCKETVISION_INFOROIY,			m_wndInfoROIY);
	DDX_Control(pDX, IDC_SOCKETVISION_INFOROIX,			m_wndInfoROIX);
	DDX_Control(pDX, IDC_SOCKETVISION_INFOROIWIDTH,		m_wndInfoWidth);
	DDX_Control(pDX, IDC_SOCKETVISION_INFOROIHEIGHT,	m_wndInfoHeight);
	DDX_Control(pDX, IDC_SOCKETVISION_CLASS,			m_listFileFolder);
	DDX_Control(pDX, IDC_SOCKETVISION_TEST,				m_btnPatternTest);
	DDX_Control(pDX, IDC_SOCKETVISION_CAPTURE,			m_btnCapture);
	DDX_Control(pDX, IDC_SOCKETVISION_SAVE,				m_btnPatternSave);
	DDX_Control(pDX, IDC_SOCKETVISION_DELETE,			m_btnClassDelete);
	DDX_Control(pDX, IDC_SOCKETVISION_CREATE,			m_btnClassCreate);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgSocketVisionCtrlSetting, CDialog)
	//{{AFX_MSG_MAP(CDlgSocketVisionCtrlSetting)
	ON_WM_TIMER()
	ON_WM_SHOWWINDOW()
	ON_BN_CLICKED(IDC_SOCKETVISION_CAPTURE,				OnSocketvisionCapture)
	ON_BN_CLICKED(IDC_SOCKETVISION_CREATE,				OnSocketvisionCreate)
	ON_BN_CLICKED(IDC_SOCKETVISION_DELETE,				OnSocketvisionDelete)
	ON_BN_CLICKED(IDC_SOCKETVISION_SAVE,				OnSocketvisionSave)
	ON_BN_CLICKED(IDC_SOCKETVISION_TEST,				OnSocketvisionTest)
	ON_CBN_SELCHANGE(IDC_SOCKETVISION_CLASS,			OnSelchangeSocketvisionClass)
	ON_MESSAGE(WM_RECT_POS,								OnPosInfo)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgSocketVisionCtrlSetting message handlers

BOOL CDlgSocketVisionCtrlSetting::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	//
	// init button 
	m_btnClassCreate.SetIcon(IDI_SOCCCD_CREATE);
	m_btnClassCreate.SetAlign(CButtonST::ST_ALIGN_VERT);

	m_btnClassDelete.SetIcon(IDI_SOCCCD_DEL);
	m_btnClassDelete.SetAlign(CButtonST::ST_ALIGN_VERT);

	m_btnCapture.SetIcon(IDI_SOCCCD_GRAB);
	m_btnCapture.SetAlign(CButtonST::ST_ALIGN_VERT);

	m_btnPatternSave.SetIcon(IDI_SOCCCD_SAVE);
	m_btnPatternSave.SetAlign(CButtonST::ST_ALIGN_VERT);

	m_btnPatternTest.SetIcon(IDI_SOCCCD_TEST);
	m_btnPatternTest.SetAlign(CButtonST::ST_ALIGN_VERT);

	//
	InitLib();

	//
	GetInitValue();

	//
	InitResult();

	//
	InitImage();

	//
	InitValue();

	//
	InitTips();

	//
	UpdataSettingList();

	//
	SelectDefault( m.UI.SocketPatternName );
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
void CDlgSocketVisionCtrlSetting::Message(CString csMsg )
{
	csMsg.TrimLeft();
	csMsg.TrimRight();
	if( csMsg == "" )
	{
		
	}
	else
	{
		AfxMessageBox( csMsg );
	}
}
LRESULT CDlgSocketVisionCtrlSetting::OnPosInfo(WPARAM p, LPARAM l)
{
	UpdataPatternInfo();

	return true;
}
void CDlgSocketVisionCtrlSetting::UpdataPatternInfo()
{
	int itop = 0;
	int ibottom = 0;
	int ileft = 0;
	int iright = 0;
	pViewMainImage->GetPatternInfo( itop, ileft, ibottom, iright );

	//
	CString csTop = _T("");
	csTop.Format("%d", itop);
	m_wndInfoROIY.SetWindowText( csTop );

	CString csLeft = _T("");
	csLeft.Format("%d", ileft );
	m_wndInfoROIX.SetWindowText( csLeft );

	CString csBottom = _T("");
	csBottom.Format("%d", ( ibottom - itop ) );
	m_wndInfoHeight.SetWindowText( csBottom );

	CString csRight = _T("");
	csRight.Format("%d", ( iright - ileft ) );
	m_wndInfoWidth.SetWindowText( csRight );
}
void CDlgSocketVisionCtrlSetting::InitLib()
{
	m_VisionUse.InitLib();
}

void CDlgSocketVisionCtrlSetting::InitImage()
{
/*
	// Image
	CViewSockTrackerImage	*pViewMainImage;
	CViewSockImage			*pViewGrabImage;
	CViewSockImage			*pViewPatternImage;

	m_wndImage
	m_wndPatternImage
	m_wndGrabImage
*/
	// Main Image
	CRect rectImage, rectPatternImage, rectGrabImage;

	//
	m_wndImage.GetClientRect( rectImage );
	pViewMainImage = new CViewSockTrackerImage();
	pViewMainImage->Create(NULL, "Image", WS_CHILD | WS_VISIBLE, rectImage, 
		(CWnd *)&m_wndImage, IDC_SOCKETVISION_SHOWWINDOW);	

	// Pattern Image
	m_wndPatternImage.GetClientRect( rectPatternImage );
	pViewPatternImage = new CViewSockImage();
	pViewPatternImage->Create(NULL, "Pattern Image", WS_CHILD | WS_VISIBLE, rectPatternImage, 
		(CWnd *)&m_wndPatternImage, IDC_SETUP_PATTERN1);
	
	// Grab Image
	m_wndGrabImage.GetClientRect( rectGrabImage );
	pViewGrabImage = new CViewSockImage();
	pViewGrabImage->Create(NULL, "Grab Image", WS_CHILD | WS_VISIBLE, rectGrabImage, 
		(CWnd *)&m_wndGrabImage, IDC_SETUP_GRABIMAGE1);
}
void CDlgSocketVisionCtrlSetting::GetInitValue()
{
	// Main Image
	GetDlgItem(IDC_SOCKETVISION_SHOWWINDOW)->GetWindowRect(&m_RectMainWindow);
	ScreenToClient(&m_RectMainWindow);
	m_WindowWidth	= m_RectMainWindow.Width();
	m_WindowHeight	= m_RectMainWindow.Height();

	// Sub Image
	GetDlgItem(IDC_SETUP_GRABIMAGE1)->GetWindowRect(&m_SubRectMainWindow);
	ScreenToClient(&m_SubRectMainWindow);
	m_SubWindowWidth	= m_SubRectMainWindow.Width();
	m_SubWindowHeight	= m_SubRectMainWindow.Height();

	// Pattern Image
	GetDlgItem(IDC_SETUP_PATTERN1)->GetWindowRect(&m_PatternRectMainWindow);
	ScreenToClient(&m_PatternRectMainWindow);
	m_PatternWindowWidth	= m_PatternRectMainWindow.Width();
	m_PatternWindowHeight	= m_PatternRectMainWindow.Height();
}
void CDlgSocketVisionCtrlSetting::UpdataSettingList()
{
	//
	// 取得 Socket 資料夾裡面設定檔的資料夾....
	GetSettingFolder();

	//
	m_listFileFolder.ResetContent();
	int iSize = m_FileDictory.GetSize();
	
	for(int i=0;i<iSize;i++)
	{
		m_listFileFolder.AddString( m_FileDictory.GetAt(i) );
	}
}
void CDlgSocketVisionCtrlSetting::GetSettingFolder()
{
	//
	m_FileDictory.RemoveAll();

	//
	CFileFind finder;														//建立搜尋用的CFileFind物件
	BOOL bResult = finder.FindFile( m.FilePath.SocketImagePath + "*.*" );	//尋找第一個檔案
	while(bResult)
	{
		bResult = finder.FindNextFile();									//尋找下一個檔案
		if(!finder.IsDots() && finder.IsDirectory())
		{
			CString csFileDirectory;
			csFileDirectory.Format("%s", finder.GetFileTitle() );
			
			m_FileDictory.Add( csFileDirectory );
		}
	}
}
void CDlgSocketVisionCtrlSetting::SelectDefaultPos(int iPos)
{
	CString csFileFolder = _T("");
	m_listFileFolder.SetCurSel( iPos );
	m_listFileFolder.GetLBText(iPos, csFileFolder ); 

	// 更新畫面
	////////////////////////////////////////////
	LoadSettingInfo( csFileFolder );
	
	//
	LoadSettingImage( csFileFolder );
	////////////////////////////////////////////
}
void CDlgSocketVisionCtrlSetting::SelectDefault(CString csFileFolder)
{
	int iPos = m_listFileFolder.FindString(0, csFileFolder);
	m_listFileFolder.SetCurSel( iPos );	

	// 更新畫面
	////////////////////////////////////////////
	LoadSettingInfo( csFileFolder );
	
	//
	LoadSettingImage( csFileFolder );
	////////////////////////////////////////////
}
void CDlgSocketVisionCtrlSetting::LoadSettingInfo(CString csFileFolder)
{
	//
	CString csFile;
	csFile = m.FilePath.SocketImagePath + csFileFolder + "\\" + _ScoketSettingInfo;

	f.GetSetting(csFile, "Source Image", "X",			m_iMatchROIX );
	f.GetSetting(csFile, "Source Image", "Y",			m_iMatchROIY );
	f.GetSetting(csFile, "Source Image", "Width",		m_iMatchWidth );
	f.GetSetting(csFile, "Source Image", "Height",		m_iMatchHeight );
	//
	f.GetSetting(csFile, "Source Image", "Score",		m_dMatchMinScore );

	UpdateData( FALSE );
}
CRect CDlgSocketVisionCtrlSetting::GetPatternInfo()
{
	CRect m_FileRect;
	
	//
	tagInfoParameter m_Info;

	//
	CString csFolderName = _T("");
	csFolderName = GetSettingFileName();
	
	CString csFile = _T("");
	csFile = m.FilePath.SocketImagePath + csFolderName + "\\" + _ScoketSettingInfo;

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
void CDlgSocketVisionCtrlSetting::ReDrawMainImage(CString csFileFolder)
{
	CString csFilePath = _T("");	
	csFilePath = m.FilePath.SocketImagePath + csFileFolder + "\\" + _SocketSettingImage;

	// 顯示之前先確定檔案在
	CFileFind Find;
	if(!Find.FindFile( csFilePath ))
	{
		CString csMsg = _T("");
		csMsg.Format("%s", csFilePath );
		pViewMainImage->SetInfomation( csMsg );
		return;
	}

	//
	try
	{
		char *szBuf = new char[csFilePath.GetLength()+1];
		memset(szBuf, 0, csFilePath.GetLength());
		strcpy(szBuf, (LPCTSTR)csFilePath);
		BOOL bGrabSuccess = m_VisionUse.pLoadCImage(m_VisionUse.hHandleInspect, szBuf);
		HBITMAP *pGrabBitmap = NULL;

		CRect m_FileRect = GetPatternInfo();	
		pViewMainImage->SetPatternInfomation( m_FileRect.top, m_FileRect.left, m_FileRect.bottom, m_FileRect.right );
		pGrabBitmap = m_VisionUse.pGetBitmapAddress(m_VisionUse.hHandleInspect);
		pViewMainImage->SetBmpAddress( pGrabBitmap );

		//
		delete []szBuf;
	}	
	catch(...)
	{
		Message("ReDrawMainImage Excute Fail.!");
	}
}
void CDlgSocketVisionCtrlSetting::ReDrawCamGrabPatternImahe()
{
	CString csFilePath = _T("");	
	csFilePath = m.FilePath.SocketImagePath + _SocketGrab;

	// 顯示之前先確定檔案在
	CFileFind Find;
	if(!Find.FindFile( csFilePath ))
	{
		return;
	}

	//
	try
	{
		// 每次都以最新的Image.bmp去產生SubImage.bmp
		// 雖然每次都會浪費一點時間,但是不會用到舊的

		int w = m_VisionUse.pVBGetWidth(   m_VisionUse.hHandleInspect );
		int h = m_VisionUse.pVBGetHeight(  m_VisionUse.hHandleInspect );

		//
		int top		= m.m_CCDSocketControl.RoiY;
		int left	= m.m_CCDSocketControl.RoiX;
		int bottom	= m.m_CCDSocketControl.RoiY + m.m_CCDSocketControl.RoiH;
		int right	= m.m_CCDSocketControl.RoiX + m.m_CCDSocketControl.RoiW;

		// 
		m_VisionUse.VBROI.Top		= top		* m.m_CCDSocketControl.RationY;  
		m_VisionUse.VBROI.Left		= left		* m.m_CCDSocketControl.RationX;	
		m_VisionUse.VBROI.bottom	= bottom	* m.m_CCDSocketControl.RationY;
		m_VisionUse.VBROI.Right		= right		* m.m_CCDSocketControl.RationX;	

		BOOL bSubSuccess = m_VisionUse.pVBGetSubImage(m_VisionUse.hHandleSubInspect, 
			m_VisionUse.hHandleInspect, m_VisionUse.VBROI );

		HBITMAP *pPatterbBitmap;	
		pPatterbBitmap = m_VisionUse.pGetBitmapAddress(m_VisionUse.hHandleSubInspect);
		pViewPatternImage->SetBmpAddress( pPatterbBitmap );
	}	
	catch(...)
	{
		Message("ReDrawPatternImage Excute Fail.!");
	}

}
void CDlgSocketVisionCtrlSetting::ReDrawCamGrabImage()
{
	CString csFilePath = _T("");	
	csFilePath = m.FilePath.SocketImagePath + _SocketGrab;

	// 顯示之前先確定檔案在
	CFileFind Find;
	if(!Find.FindFile( csFilePath ))
	{
		CString csMsg = _T("");
		csMsg.Format("%s", csFilePath );
		pViewMainImage->SetInfomation( csMsg );
		return;
	}

	//
	try
	{
		char *szBuf = new char[csFilePath.GetLength()+1];
		memset(szBuf, 0, csFilePath.GetLength());
		strcpy(szBuf, (LPCTSTR)csFilePath);
		BOOL bGrabSuccess = m_VisionUse.pLoadCImage(m_VisionUse.hHandleInspect, szBuf);

		HBITMAP *pGrabBitmap = NULL;

		CRect m_FileRect;
		
		// 寫入預設的 ROI
		m_FileRect.top		= m.m_CCDSocketControl.RoiY;
		m_FileRect.left		= m.m_CCDSocketControl.RoiX;
		m_FileRect.bottom	= m.m_CCDSocketControl.RoiY + m.m_CCDSocketControl.RoiH;
		m_FileRect.right	= m.m_CCDSocketControl.RoiX + m.m_CCDSocketControl.RoiW;

		pViewMainImage->SetPatternInfomation( m_FileRect.top, m_FileRect.left, m_FileRect.bottom, m_FileRect.right );
		pGrabBitmap = m_VisionUse.pGetBitmapAddress(m_VisionUse.hHandleInspect);
		pViewMainImage->SetBmpAddress( pGrabBitmap );

		//
		delete []szBuf;
	}	
	catch(...)
	{
		Message("ReDrawMainImage Excute Fail.!");
	}
}
void CDlgSocketVisionCtrlSetting::ReDrawGrabImage()
{	
	CString csFilePath = _T("");	
	csFilePath = m.FilePath.SocketImagePath + _SocketGrab;

	// 顯示之前先確定檔案在
	CFileFind Find;
	if(!Find.FindFile( csFilePath ))
	{
		return;
	}

	//
	try
	{
		char *szBuf = new char[csFilePath.GetLength()+1];
		memset(szBuf, 0, csFilePath.GetLength());
		strcpy(szBuf, (LPCTSTR)csFilePath);
		BOOL bGrabSuccess = m_VisionUse.pLoadCImage(m_VisionUse.hHandleExtInspect, szBuf);

		HBITMAP *pGrabBitmap = NULL;

		pGrabBitmap = m_VisionUse.pGetBitmapAddress(m_VisionUse.hHandleExtInspect);
		pViewGrabImage->SetBmpAddress( pGrabBitmap );

		//
		delete []szBuf;
	}	
	catch(...)
	{
		Message("ReDrawGrabImage Excute Fail.!");
	}
}
void CDlgSocketVisionCtrlSetting::ReDrawPatternImage(CString csFileFolder)
{
	CString csFilePath = _T("");	
	csFilePath = m.FilePath.SocketImagePath + csFileFolder + "\\" + _SocketSettingImage;

	// 顯示之前先確定檔案在
	CFileFind Find;
	if(!Find.FindFile( csFilePath ))
	{
		return;
	}

	//
	try
	{
		// 每次都以最新的Image.bmp去產生SubImage.bmp
		// 雖然每次都會浪費一點時間,但是不會用到舊的

		//
		int w = m_VisionUse.pVBGetWidth(   m_VisionUse.hHandleInspect );
		int h = m_VisionUse.pVBGetHeight(  m_VisionUse.hHandleInspect );

		CRect rectFile = GetPatternInfo();
		// 
		m_VisionUse.VBROI.Top		= rectFile.top		* m.m_CCDSocketControl.RationY;  
		m_VisionUse.VBROI.Left		= rectFile.left		* m.m_CCDSocketControl.RationX;	
		m_VisionUse.VBROI.bottom	= rectFile.bottom	* m.m_CCDSocketControl.RationY;
		m_VisionUse.VBROI.Right		= rectFile.right	* m.m_CCDSocketControl.RationX;	

		BOOL bSubSuccess = m_VisionUse.pVBGetSubImage(m_VisionUse.hHandleSubInspect, 
			m_VisionUse.hHandleInspect, m_VisionUse.VBROI );

		HBITMAP *pPatterbBitmap;	
		pPatterbBitmap = m_VisionUse.pGetBitmapAddress(m_VisionUse.hHandleSubInspect);
		pViewPatternImage->SetBmpAddress( pPatterbBitmap );
	}	
	catch(...)
	{
		Message("ReDrawPatternImage Excute Fail.!");
	}
}
void CDlgSocketVisionCtrlSetting::LoadSettingImage(CString csFileFolder)
{
	// 更新主畫面
	ReDrawMainImage( csFileFolder );

	// 更新 Pattern 
	ReDrawPatternImage( csFileFolder );

	// 更新 Grab
	ReDrawGrabImage();

	//
	Invalidate();
}
void CDlgSocketVisionCtrlSetting::InitValue()
{
/*
	CRect rect;
	m_wndImage.GetClientRect( rect );
	int W = ( rect.Width() ) * m.m_CCDSocketControl.RationX;
	int H = ( rect.Height() ) * m.m_CCDSocketControl.RationY;

	CString csMsg = _T("");
	csMsg.Format("W %d, H %d", W, H);
	AfxMessageBox( csMsg );
*/
}
void CDlgSocketVisionCtrlSetting::InitResult()
{
	m_wndTestScore.SetNewBkColor( ST_WHITE );
	m_wndTestScore.SetText("--", 9, "Arial", DT_CENTER | DT_VCENTER | DT_SINGLELINE);
}
void CDlgSocketVisionCtrlSetting::InitTips()
{
	// Tips // Init Tips
	m_ToolTip.Create(this);
	m_ToolTip.SetMaxTipWidth(800);
	m_ToolTip.SetDelayTime( TTDT_AUTOPOP, 10000 );
	m_ToolTip.SetDelayTime( TTDT_INITIAL, 25 );
	m_ToolTip.EnableToolTips(true);

	m_ToolTip.AddTool( GetDlgItem(IDC_SOCKETVISION_CREATE),			_T("Create New Socket CCD Profile") );
	m_ToolTip.AddTool( GetDlgItem(IDC_SOCKETVISION_DELETE),			_T("Delete Old Socket CCD Profile") );
	m_ToolTip.AddTool( GetDlgItem(IDC_SOCKETVISION_SAVE),			_T("Save Socket CCD Profile") );
	m_ToolTip.AddTool( GetDlgItem(IDC_SOCKETVISION_CAPTURE),		_T("Grab a image") );
	m_ToolTip.AddTool( GetDlgItem(IDC_SOCKETVISION_TEST),			_T("Grab a image and match test") );

}
void CDlgSocketVisionCtrlSetting::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	
	CDialog::OnTimer(nIDEvent);
}

void CDlgSocketVisionCtrlSetting::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);	
}

BOOL CDlgSocketVisionCtrlSetting::PreTranslateMessage(MSG* pMsg) 
{
	// Tips
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
void CDlgSocketVisionCtrlSetting::CaptureLockUI(bool bEnable)
{
	if( bEnable )
	{
		m_btnClassCreate.EnableWindow( FALSE );
		m_btnClassDelete.EnableWindow( FALSE );
		m_btnCapture.EnableWindow( FALSE );
		m_btnPatternSave.EnableWindow( FALSE );
		m_btnPatternTest.EnableWindow( FALSE );
		m_listFileFolder.EnableWindow( FALSE );
	}
	else
	{
		m_btnClassCreate.EnableWindow( TRUE );
		m_btnClassDelete.EnableWindow( TRUE );
		m_btnCapture.EnableWindow( TRUE );
		m_btnPatternSave.EnableWindow( TRUE );
		m_btnPatternTest.EnableWindow( TRUE );
		m_listFileFolder.EnableWindow( TRUE );
	}
}
void CDlgSocketVisionCtrlSetting::CameraCapture()
{
	CString csFilePath = _T("");
	csFilePath = m.FilePath.SocketImagePath + _SocketGrab;
	m.m_Vision.CameraGrabSave( m.m_CCDSocketControl.iCCDUse, csFilePath );
}
void CDlgSocketVisionCtrlSetting::OnSocketvisionCapture() 
{
	CaptureLockUI( true );
	
	CameraCapture();				// 取像
	
	ReDrawGrabImage();				// 更新畫面

	ReDrawCamGrabImage();			// 更新主畫面

	ReDrawCamGrabPatternImahe();	// 更新畫面的 Pattern
	
	CaptureLockUI( false );		
}

void CDlgSocketVisionCtrlSetting::OnSocketvisionCreate() 
{
	FunctionCreate();
}
void CDlgSocketVisionCtrlSetting::OnSocketvisionDelete() 
{
	FunctionDelete();
}
void CDlgSocketVisionCtrlSetting::OnSocketvisionSave() 
{
	FunctionSave();	
}
void CDlgSocketVisionCtrlSetting::OnSocketvisionTest() 
{
	FunctionTest();
}
////////////////////////////////////////////////////////////////////////////////////
void CDlgSocketVisionCtrlSetting::SaveSettingInfo(CString csFileFolder)
{
	UpdateData();

	//
	CString csFile = _T("");
	csFile = m.FilePath.SocketImagePath + csFileFolder + "\\" + _ScoketSettingInfo;

	f.SaveSetting(csFile, "Source Image", "X",			m_iMatchROIX );
	f.SaveSetting(csFile, "Source Image", "Y",			m_iMatchROIY );
	f.SaveSetting(csFile, "Source Image", "Width",		m_iMatchWidth );
	f.SaveSetting(csFile, "Source Image", "Height",		m_iMatchHeight );
	//
	f.SaveSetting(csFile, "Source Image", "Score",		m_dMatchMinScore );
}
void CDlgSocketVisionCtrlSetting::CopyGrabImage(CString csFileFolder)
{
	//
	CString csFile = _T(""); // Destion Image
	csFile = m.FilePath.SocketImagePath + csFileFolder + "\\" + _SocketSettingImage;
	
	//
	CString csSourceFile = _T("");
	csSourceFile = m.FilePath.SocketImagePath + _SocketGrab;

	if(::CopyFile(csSourceFile, csFile, FALSE ) == 0 )
	{
		AfxMessageBox("Copy Fail.!");
	}
	else
	{
	
	}
}
void CDlgSocketVisionCtrlSetting::ReplaceFolder(CString csFileFolder)
{
	// Copy Grab.bmp
	CopyGrabImage(csFileFolder);	

	// Create Info.txt
	SaveSettingInfo(csFileFolder);	
}
void CDlgSocketVisionCtrlSetting::ReplaceFolderSave(CString csFileFolder)
{
	// Copy Grab.bmp
//	CopyGrabImage(csFileFolder);	

	// Create Info.txt
	SaveSettingInfo(csFileFolder);	
}
bool CDlgSocketVisionCtrlSetting::IsSettingFileExist(CString csFileName)
{
	GetSettingFolder();	

	bool bExist = false;

	int iSize = m_FileDictory.GetSize();
	for(int i=0;i<iSize;i++)
	{
		CString csF = _T("");
		csF = m_FileDictory.GetAt(i);
		if( csF == csFileName )
		{
			bExist = true;
			break;
		}
	}

	return bExist;
}
bool CDlgSocketVisionCtrlSetting::IsSettingFileLastOne()
{
	bool bLastOne = false;

	int iCount = m_listFileFolder.GetCount();
	if( iCount <= 1 )
	{
		CString csMsg = _T("");
		csMsg.Format("File List is the last one. Please create new one first.!");
		AfxMessageBox( csMsg );
		bLastOne = true;
		return bLastOne;
	}
	
	return bLastOne;
}
bool CDlgSocketVisionCtrlSetting::IsSettingFileEmpty()
{
	bool bEmpty = false;
	
	// 看有沒有選
	int iSel = m_listFileFolder.GetCurSel();
	CString csSettingFolderName = _T("");

	// 看有沒有輸入
	CString csSettingName = _T("");
	m_listFileFolder.GetWindowText( csSettingName );
	csSettingName.TrimLeft();
	csSettingName.TrimRight();

	if( iSel == -1 && csSettingName == "" )
	{
		CString cs = _T("");
		cs.Format("File List is Empty. Please select new or set new name.!");
		AfxMessageBox( cs );
		bEmpty = true;
		return bEmpty;
	}

	return bEmpty;
}
///////////////////////////////////////////////////////////////////
//
void CDlgSocketVisionCtrlSetting::CreateNewFolder(CString csFileFolder)
{
	// 建立資料夾
	CString csFileFolderPath = _T("");
	csFileFolderPath = m.FilePath.SocketImagePath + csFileFolder;

	BOOL bCreateResult = FALSE;
	bCreateResult = CreateDirectory(csFileFolderPath, NULL);	

	if( bCreateResult )
	{
		// Copy Grab.bmp
		CopyGrabImage(csFileFolder);	

		// Create Info.txt
		SaveSettingInfo(csFileFolder);	
	}
	else
	{
		// Error 
		AfxMessageBox("Create Folder Fail.!");
	}
}
void CDlgSocketVisionCtrlSetting::UpdataSettingSelect(CString NewName)
{
	int iPos = m_listFileFolder.FindString(0, NewName);
	m_listFileFolder.SetCurSel( iPos );
}
void CDlgSocketVisionCtrlSetting::FunctionSave()
{
	// 如果檔案不存在於目前的資料夾, 那就開一個新的資料夾來存圖檔. 然後存入預設值
	// 如果存在, 就用新的替換掉
	
	if( IsSettingFileEmpty() )
		return;	

	// 檢查有沒有存在
	CString csFileFolderName = _T("");
	csFileFolderName = GetSettingFileName();
	if( IsSettingFileExist( csFileFolderName ) )
	{
		// 已經存在了, 替換他
		ReplaceFolderSave( csFileFolderName );
	}
	else
	{
		// 檔案不存在..建新檔案...
		CreateNewFolder( csFileFolderName );
	}

	// 更新列表
	UpdataSettingList();

	// 重新選擇
	UpdataSettingSelect(csFileFolderName);

	// 重新畫 Pattern ( 因為可能 ROI 改變了 )
	ReDrawPatternImage(csFileFolderName);
}
void CDlgSocketVisionCtrlSetting::DeleteOldFolder( CString csFileFolder)
{
	// 重選檔案, 避免圖檔被占用
	ChangeFileFolderOther();

	//
	CString csFileFolderPath = _T("");
	csFileFolderPath = m.FilePath.SocketImagePath + csFileFolder;

	// 刪除檔案
	CString csDbFile = csFileFolderPath + "\\" + _SockeDb;
	::DeleteFile( csDbFile );

	// 刪除檔案
	CString csInfoFile = csFileFolderPath + "\\" + _ScoketSettingInfo;
	::DeleteFile( csInfoFile );

	// 刪除圖片
	CString csImageFile = csFileFolderPath + "\\" + _SocketSettingImage;
	BOOL bDeleteImage = ::DeleteFile( csImageFile );

	// 刪除圖片
	CString csImageSubFile = csFileFolderPath + "\\" + _SocketSettingSubImage;
	BOOL bDeleteSubImage = ::DeleteFile( csImageSubFile );

	// 刪除目錄	
	RemoveDirectory( csFileFolderPath );
}
void CDlgSocketVisionCtrlSetting::FunctionDelete()
{
	if( IsSettingFileEmpty() )
		return;
	
	if( IsSettingFileLastOne() )
		return;

	// Check Message
	if(IDNO == MessageBox("Delete This File. ?", "3111", MB_ICONSTOP | MB_YESNO))
		return;

	// 確認是否在使用中..
	if( m.UI.SocketPatternName == GetSettingFileName() )
	{
		// 
		CString csF = GetSettingFileName();
		CString csMsg;
		csMsg.Format("[%s] in using.! Please change it then delete.", csF );
		AfxMessageBox( csMsg );
		return;
	}

	// 整個資料夾砍掉
	CString csOldF = GetSettingFileName();
	DeleteOldFolder( csOldF );

	// 更新列表
	UpdataSettingList();

	// 重新選回第一個
	SelectDefault( m.UI.SocketPatternName );
}
void CDlgSocketVisionCtrlSetting::FunctionCreate()
{
	// 把 CArray 的值拿來比一下. 如果資料夾已經存在..那就叫使用者打一個新的.
	// 如果有輸入新的. 就新增資料夾. 就把當下的 Grab.bmp 存起來. 然後把當下 Value 也存起來
	// 只是萬一沒取像. 會存到舊的.

	if( IsSettingFileEmpty() )
		return;	

	// 檢查有沒有存在
	CString csFileFolderName = _T("");
	csFileFolderName = GetSettingFileName();
	if( IsSettingFileExist( csFileFolderName ) )
	{
		// 已經存在了, 替換他
		ReplaceFolder( csFileFolderName );
	}
	else
	{
		// 檔案不存在..建新檔案...
		CreateNewFolder( csFileFolderName );
	}

	// 更新列表
	UpdataSettingList();

	// 重新選擇
	UpdataSettingSelect(csFileFolderName);
}
double CDlgSocketVisionCtrlSetting::GetSettingScore(CString csFileFolder)
{
	double dScore = 1.00;

	CString csFile = _T("");
	//
	double dGetScore = 1.00;
	csFile = m.FilePath.SocketImagePath + csFileFolder + "\\" + _ScoketSettingInfo;
	f.GetSetting(csFile, "Source Image", "Score",	dGetScore = 1.00 );
	dScore = dGetScore;

	return dScore;
}
void CDlgSocketVisionCtrlSetting::MatchResult(double dResult, double dScore)
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
void CDlgSocketVisionCtrlSetting::FunctionTest()
{
	// 先取像. 這樣才可以用取到的像跟設定檔比
	CameraCapture();

	// 設定 Pattern 的路徑
	CString csPatternPath = _T("");
	CString csFileFolderName = _T("");
	csFileFolderName = GetSettingFileName();
	csPatternPath = m.FilePath.SocketImagePath + csFileFolderName + "\\" + _SocketSettingImage;

	// 設定 Grab 的路徑
	CString csGrabPath = _T("");
	csGrabPath = m.FilePath.SocketImagePath + _SocketGrab;

	//
	double dScore = 0.0;
	double dResult = 0.0;
//	dScore = GetSettingScore( csFileFolderName );
//	dResult = m_VisionMatch.MatchCheck( m.m_CCDSocketControl.iCCDUse, csPatternPath, 
//		csGrabPath, _SocketGrab, _SocketGrabSub );

	//
	MatchResult( dResult, dScore );
}
void CDlgSocketVisionCtrlSetting::ChangeFileFolderOther()
{
	int iSel = m_listFileFolder.GetCurSel();
	int iCount = m_listFileFolder.GetCount();
	if( iSel == 0 )
	{
		// 選到第一個刪除, 移到下一個
		SelectDefaultPos(iSel+1);		TRACE("# CCD Socket Delete: First\n");
	}
	else if( iSel == (iCount-1) )
	{
		// 選到最後一個刪除
		SelectDefaultPos(0);			TRACE("# CCD Socket Delete: Last\n");
	}
	else 
	{
		// 選到中間刪除
		SelectDefaultPos(iSel+1);		TRACE("# CCD Socket Delete: Next\n");
	}
}
void CDlgSocketVisionCtrlSetting::ChangeFileFolder()
{	
	// 選擇檔案..
	if( IsSettingFileEmpty() )
		return;	

	// 檢查有沒有存在
	CString csFileFolderName = _T("");
	csFileFolderName = GetSettingFileName();

	//
	LoadSettingInfo( csFileFolderName );
	
	//
	LoadSettingImage( csFileFolderName );
}
CString CDlgSocketVisionCtrlSetting::GetSettingFileName()
{
	int iSel = m_listFileFolder.GetCurSel();
	CString csSettingFolderName = _T("");

	if( iSel == -1 )
	{
		// 是輸入的
		CString csSettingName = _T("");
		m_listFileFolder.GetWindowText( csSettingName );
		csSettingName.TrimLeft();
		csSettingName.TrimRight();

		csSettingFolderName = csSettingName;
	}
	else
	{
		// 是用選的
		m_listFileFolder.GetLBText( iSel, csSettingFolderName );
	}
	return csSettingFolderName;
}
void CDlgSocketVisionCtrlSetting::OnSelchangeSocketvisionClass() 
{
	ChangeFileFolder();
}
