// DlgPin1VisionSetting.cpp : implementation file
//

#include "stdafx.h"
#include "deer.h"
#include "DlgPin1VisionSetting.h"

//
#include <afx.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgPin1VisionSetting dialog


CDlgPin1VisionSetting::CDlgPin1VisionSetting(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgPin1VisionSetting::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgPin1VisionSetting)
	m_iMatchROIX = 0;
	m_iMatchROIY = 0;
	m_iMatchWidth = 0;
	m_iMatchHeight = 0;
	m_dMatchMinScore = 0.0;
	//}}AFX_DATA_INIT

	bGrabed				= false;
	bRoied				= false;
	bSelected			= false;
	bPatterned			= false;
	bPatternSelected	= false;

	//
	m_fMatchTestScore = 0.0;


}


void CDlgPin1VisionSetting::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgPin1VisionSetting)
	DDX_Control(pDX, IDC_MATCH_TESTSCORE,			m_wndTestScore);
	DDX_Control(pDX, IDC_SOCKETVISION_CLASS,		m_listFileFolder);
	DDX_Control(pDX, IDC_SOCKETVISION_TEST,			m_btnPatternTest);
	DDX_Control(pDX, IDC_SOCKETVISION_CAPTURE,		m_btnCapture);
	DDX_Control(pDX, IDC_SOCKETVISION_SAVE,			m_btnPatternSave);
	DDX_Control(pDX, IDC_SOCKETVISION_DELETE,		m_btnClassDelete);
	DDX_Control(pDX, IDC_SOCKETVISION_CREATE,		m_btnClassCreate);
	DDX_Text(pDX, IDC_SOCKETVISION_INFOROIX,		m_iMatchROIX);
	DDX_Text(pDX, IDC_SOCKETVISION_INFOROIY,		m_iMatchROIY);
	DDX_Text(pDX, IDC_SOCKETVISION_INFOROIWIDTH,	m_iMatchWidth);
	DDX_Text(pDX, IDC_SOCKETVISION_INFOROIHEIGHT,	m_iMatchHeight);
	DDX_Text(pDX, IDC_SOCKETVISION_INFOMINSCORE,	m_dMatchMinScore);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgPin1VisionSetting, CDialog)
	//{{AFX_MSG_MAP(CDlgPin1VisionSetting)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_SOCKETVISION_CREATE, OnSocketvisionCreate)
	ON_BN_CLICKED(IDC_SOCKETVISION_DELETE, OnSocketvisionDelete)
	ON_BN_CLICKED(IDC_SOCKETVISION_SAVE, OnSocketvisionSave)
	ON_BN_CLICKED(IDC_SOCKETVISION_CAPTURE, OnSocketvisionCapture)
	ON_BN_CLICKED(IDC_SOCKETVISION_TEST, OnSocketvisionTest)
	ON_CBN_EDITCHANGE(IDC_SOCKETVISION_CLASS, OnEditchangeSocketvisionClass)
	ON_WM_MOUSEMOVE()
	ON_WM_PAINT()
	ON_WM_DESTROY()
	ON_CBN_SELCHANGE(IDC_SOCKETVISION_CLASS, OnSelchangeSocketvisionClass)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgPin1VisionSetting message handlers

BOOL CDlgPin1VisionSetting::PreTranslateMessage(MSG* pMsg) 
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

BOOL CDlgPin1VisionSetting::OnInitDialog() 
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
	GetInitValue();

	//
	InitValue();

	//
	InitTips();

	//
	UpdataSettingList();

	//
	SetectDefault( m.UI.SocketPatternName );

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
void CDlgPin1VisionSetting::GetSettingFolder()
{
	//
	m_FileDictory.RemoveAll();

	//
	CFileFind finder;														//建立搜尋用的CFileFind物件
	BOOL bResult = finder.FindFile( m.FilePath.CCDImagePath + "*.*" );	//尋找第一個檔案
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
void CDlgPin1VisionSetting::UpdataSettingSelect(CString NewName)
{
	int iPos = m_listFileFolder.FindString(0, NewName);
	m_listFileFolder.SetCurSel( iPos );
}
void CDlgPin1VisionSetting::UpdataSettingList()
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
void CDlgPin1VisionSetting::GetInitValue()
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
void CDlgPin1VisionSetting::InitValue()
{
	sourcePen.CreatePen(PS_SOLID, 1, RGB(255, 255, 0));

	//
	m_wndTestScore.SetNewBkColor(ST_WHITE);
	m_wndTestScore.SetText("--", 9, "Arial", DT_CENTER | DT_VCENTER | DT_SINGLELINE);
}
void CDlgPin1VisionSetting::InitTips()
{
	// Init Tips
	m_ToolTip.Create(this);
	m_ToolTip.SetDelayTime( TTDT_AUTOPOP, 10000 );
	m_ToolTip.SetDelayTime( TTDT_INITIAL, 25 );
	m_ToolTip.EnableToolTips(true);

	m_ToolTip.AddTool( GetDlgItem(IDC_SOCKETVISION_CREATE),		_T("Create File") );
	m_ToolTip.AddTool( GetDlgItem(IDC_SOCKETVISION_DELETE),		_T("Delete File") );
	m_ToolTip.AddTool( GetDlgItem(IDC_SOCKETVISION_SAVE),		_T("Save File") );
	m_ToolTip.AddTool( GetDlgItem(IDC_SOCKETVISION_CAPTURE),	_T("Capture Image") );
	m_ToolTip.AddTool( GetDlgItem(IDC_SOCKETVISION_TEST),		_T("Test") );
}
//
void CDlgPin1VisionSetting::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	
	CDialog::OnTimer(nIDEvent);
}
////////////////////////////////////////////////////////////////////////////////////
bool CDlgPin1VisionSetting::IsSettingFileExist(CString csFileName)
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
bool CDlgPin1VisionSetting::IsSettingFileEmpty()
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
		CString cs;
		cs.Format("File List is Empty. Please select new or set new name.!");
		AfxMessageBox( cs );
		bEmpty = true;
		return bEmpty;
	}

	return bEmpty;
}

void CDlgPin1VisionSetting::SetectDefault(CString csFileFolder)
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
CString CDlgPin1VisionSetting::GetSettingFileName()
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

bool CDlgPin1VisionSetting::LoadSettingFile(CString csFileName)
{
	bool bLoadOK = true;


	return bLoadOK;
}
//
void CDlgPin1VisionSetting::CopyGrabImage(CString csFileFolder)
{
	//
	CString csFile; // Destion Image
	csFile = m.FilePath.CCDImagePath + csFileFolder + "\\" + _SocketSettingImage;
	
	//
	CString csSourceFile;
	csSourceFile = m.FilePath.CCDImagePath + _SocketGrab;

	if(::CopyFile(csSourceFile, csFile, FALSE ) == 0 )
	{
		AfxMessageBox("Copy Fail.!");
	}
	else
	{
	
	}
}

void CDlgPin1VisionSetting::LoadSettingImage(CString csFileFolder)
{
	CString csFile = _T("");
	csFile.Format( "%s", m.FilePath.CCDImagePath + csFileFolder + "\\" + _SocketSettingImage );

	//
	SourceImage.Load( csFile );
	SourceROI.Detach();
	SourceROI.Attach(&SourceImage);
	// 1.0Rl
	// 參數代錯
//	SourceROI.SetPlacement( m_iMatchROIX, m_iMatchROIX, m_iMatchWidth, m_iMatchHeight);
	SourceROI.SetPlacement( m_iMatchROIX, m_iMatchROIY, m_iMatchWidth, m_iMatchHeight);

	bSelected = true;
	bPatternSelected = true;
	Invalidate();
}
void CDlgPin1VisionSetting::LoadSettingInfo(CString csFileFolder)
{
	//
	CString csFile;
	csFile = m.FilePath.CCDImagePath + csFileFolder + "\\" + _ScoketSettingInfo;

	f.GetSetting(csFile, "Source Image", "X",			m_iMatchROIX );
	f.GetSetting(csFile, "Source Image", "Y",			m_iMatchROIY );
	f.GetSetting(csFile, "Source Image", "Width",		m_iMatchWidth );
	f.GetSetting(csFile, "Source Image", "Height",		m_iMatchHeight );
	//
	f.GetSetting(csFile, "Source Image", "Score",		m_dMatchMinScore );

	UpdateData( FALSE );
}
void CDlgPin1VisionSetting::SaveSettingInfo(CString csFileFolder)
{
	UpdateData();

	//
	CString csFile;
	csFile = m.FilePath.CCDImagePath + csFileFolder + "\\" + _ScoketSettingInfo;

	f.SaveSetting(csFile, "Source Image", "X",			m_iMatchROIX );
	f.SaveSetting(csFile, "Source Image", "Y",			m_iMatchROIY );
	f.SaveSetting(csFile, "Source Image", "Width",		m_iMatchWidth );
	f.SaveSetting(csFile, "Source Image", "Height",		m_iMatchHeight );
	//
	f.SaveSetting(csFile, "Source Image", "Score",		m_dMatchMinScore );
}
////////////////////////////////////////////////////////////////////////////////////
void CDlgPin1VisionSetting::OnSocketvisionCreate() 
{
	// 把 Carray 的值拿來比一下. 如果資料夾已經存在..那就叫使用者打一個新的.
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

void CDlgPin1VisionSetting::OnSocketvisionDelete() 
{
	if( IsSettingFileEmpty() )
		return;	

	// Check Message
	if(IDNO == MessageBox("Delete This File. ?", "3111", MB_ICONSTOP | MB_YESNO))
		return;

	// 
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
	SetectDefault( m.UI.SocketPatternName );	
}

void CDlgPin1VisionSetting::DeleteOldFolder( CString csFileFolder)
{
	CString csFileFolderPath = _T("");
	csFileFolderPath = m.FilePath.CCDImagePath + csFileFolder;

	// 刪除檔案
	CString csInfoFile = csFileFolderPath + "\\" + _ScoketSettingInfo;
	::DeleteFile( csInfoFile );

	// 刪除圖片
	CString csImageFile = csFileFolderPath + "\\" + _SocketSettingImage;
	::DeleteFile( csImageFile );

	// 刪除目錄	
	RemoveDirectory( csFileFolderPath );
}

void CDlgPin1VisionSetting::CreateNewFolder(CString csFileFolder)
{
	// 建立資料夾
	CString csFileFolderPath = _T("");
	csFileFolderPath = m.FilePath.CCDImagePath + csFileFolder;

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
void CDlgPin1VisionSetting::ReplaceFolderSave(CString csFileFolder)
{
	// Copy Grab.bmp
//	CopyGrabImage(csFileFolder);	

	// Create Info.txt
	SaveSettingInfo(csFileFolder);	
}
void CDlgPin1VisionSetting::ReplaceFolder(CString csFileFolder)
{
	// Copy Grab.bmp
	CopyGrabImage(csFileFolder);	

	// Create Info.txt
	SaveSettingInfo(csFileFolder);	
}
void CDlgPin1VisionSetting::OnSocketvisionSave() 
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
//		ReplaceFolder( csFileFolderName );
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

	// 存成使用的檔案
//	m.UI.SocketPatternName = csFileFolderName;
//	f.SaveSocketPattern();
	f.LoadSocketPatternSetting(); // Robin: V1.1S 不然無法及時更新
}

void CDlgPin1VisionSetting::OnSocketvisionCapture() 
{
	// 請 CCD 先取個像吧..
	/////////////////////////////////////////////////////////////////////////////////////////
//	m.m_VisionMatch.CameraGrab(m.m_VisionMatch.m_iCameraUseID);
//	m.m_VisionMatch.GetGrabImage(m.m_VisionMatch.m_iCameraUseID).Save( m.FilePath.CCDImagePath + _SocketGrab , E_FILE_FORMAT_COLOR_BMP);
//Jerome Add 20140707
	m.m_VisionMatch.CameraGrab(m.m_CCDPin1Control.iCCDUse);
	m.m_VisionMatch.GetGrabImage(m.m_CCDPin1Control.iCCDUse).Save( m.FilePath.CCDImagePath + _SocketGrab , E_FILE_FORMAT_COLOR_BMP);

	SourceImage.Load( m.FilePath.CCDImagePath + _SocketGrab );
	SourceROI.Detach();
	SourceROI.Attach(&SourceImage);
	SourceROI.SetPlacement( m.m_CCDSocketControl.RoiX, m.m_CCDSocketControl.RoiY, m.m_CCDSocketControl.RoiW, m.m_CCDSocketControl.RoiH);
	
	m_iMatchROIX		= m.m_CCDSocketControl.RoiX; //160
	m_iMatchROIY		= m.m_CCDSocketControl.RoiY; //120
	m_iMatchWidth		= m.m_CCDSocketControl.RoiW; //320
	m_iMatchHeight		= m.m_CCDSocketControl.RoiH; //240
	m_dMatchMinScore	= _SocketMinScore;
	UpdateData(FALSE);
	
	//
	bGrabed = true;	
	bPatternSelected = true;
	Invalidate();
	////////////////////////////////////////////////////////////////////////////////////////
}

void CDlgPin1VisionSetting::OnSocketvisionTest() 
{
	UpdateData();

/*
	// 在這邊不應該用取向的圖檔來 Learn 
	// Learn
	CString csFileFolderPath = _T("");
	csFileFolderPath = m.FilePath.CCDImagePath + _SocketGrab;
	m.m_VisionMatch.SetMatchPattern(
		m.m_VisionMatch.m_iCameraUseID,
		csFileFolderPath,
		CRect(m_iMatchROIX, m_iMatchROIY, m_iMatchWidth+m_iMatchROIX, m_iMatchHeight + m_iMatchROIY),
		m_dMatchMinScore);
*/
	CString csFileFolderName = _T("");
	csFileFolderName = GetSettingFileName();

	// Learn
	CString csFileFolderPath = _T("");
	csFileFolderPath = m.FilePath.CCDImagePath + csFileFolderName + "\\" + _SocketSettingImage;
	m.m_VisionMatch.SetMatchPattern(
		//m.m_VisionMatch.m_iCameraUseID,
		m.m_CCDPin1Control.iCCDUse,	//Jerome Add 20140707
		csFileFolderPath,
		CRect(m_iMatchROIX, m_iMatchROIY, m_iMatchWidth+m_iMatchROIX, m_iMatchHeight + m_iMatchROIY),
		m_dMatchMinScore);

	// Match
// 	m_fMatchTestScore =	m.m_VisionMatch.GrabMatch( m.m_VisionMatch.m_iCameraUseID );
// 	SourceImage = m.m_VisionMatch.GetGrabImage(m.m_VisionMatch.m_iCameraUseID);
//Jerome Add 20140707
	m_fMatchTestScore =	m.m_VisionMatch.GrabMatch( m.m_CCDPin1Control.iCCDUse );
	SourceImage = m.m_VisionMatch.GetGrabImage(m.m_CCDPin1Control.iCCDUse);

	SourceROI.Detach();
	SourceROI.Attach(&SourceImage);
	SourceROI.SetPlacement(m_iMatchROIX, m_iMatchROIY, m_iMatchWidth, m_iMatchHeight);

	bGrabed = true;
	bPatterned = true;
	UpdateData(false);
	Invalidate();

	//
	CString csScore = _T("");
	if( m_fMatchTestScore >= m_dMatchMinScore )
		m_wndTestScore.SetNewBkColor(ST_GREEN);
	else
		m_wndTestScore.SetNewBkColor(ST_RED);
	csScore.Format("%5.2f", m_fMatchTestScore );
	m_wndTestScore.SetWindowText( csScore );
}
//
void CDlgPin1VisionSetting::OnEditchangeSocketvisionClass() 
{
	
}

void CDlgPin1VisionSetting::OnMouseMove(UINT nFlags, CPoint point) 
{
	double	WindowRatioW = m_WindowWidth/(double)SourceImage.GetWidth();
	double	WindowRatioH = m_WindowHeight/(double)SourceImage.GetHeight();
	point.x = (long)((double)point.x/WindowRatioW) - m_RectMainWindow.left;;
	point.y = (long)((double)point.y/WindowRatioH) - m_RectMainWindow.top;

	if((nFlags & MK_LBUTTON) && (m_eHandle != E_HANDLE_NONE))
	{
		SourceROI.Drag(m_eHandle, point.x, point.y);
		CString tempStr;

		m_iMatchROIX = SourceROI.GetOrgX();
		tempStr.Format("%d", m_iMatchROIX < 0 ? 0 : m_iMatchROIX);

		m_iMatchROIY = SourceROI.GetOrgY();
		tempStr.Format("%d", m_iMatchROIY < 0 ? 0 : m_iMatchROIY);

		m_iMatchWidth = SourceROI.GetWidth();
		tempStr.Format("%d", m_iMatchWidth < 0 ? 0 : m_iMatchWidth);

		m_iMatchHeight = SourceROI.GetHeight();
		tempStr.Format("%d", m_iMatchHeight < 0 ? 0 : m_iMatchHeight);

		UpdateData(false);
		bRoied = true;
		Invalidate(FALSE);
	}
	else
	{
		m_eHandle = SourceROI.HitTest(point.x, point.y);
	}	

	switch(m_eHandle)
	{
	case E_HANDLE_INSIDE:
		SetCursor(LoadCursor(NULL, IDC_SIZEALL));
		break;
		
	case E_HANDLE_NORTH:
	case E_HANDLE_SOUTH:
		SetCursor(LoadCursor(NULL, IDC_SIZENS));
		break;
		
	case E_HANDLE_EAST:
	case E_HANDLE_WEST:
		SetCursor(LoadCursor(NULL, IDC_SIZEWE));
		break;
		
	case E_HANDLE_NORTH_WEST:
	case E_HANDLE_SOUTH_EAST:
		SetCursor(LoadCursor(NULL, IDC_SIZENWSE));
		break;
		
	case E_HANDLE_NORTH_EAST:
	case E_HANDLE_SOUTH_WEST:
		SetCursor(LoadCursor(NULL, IDC_SIZENESW));
		break;
	}


	CDialog::OnMouseMove(nFlags, point);
}

void CDlgPin1VisionSetting::OnPaint() 
{
	CPaintDC dc(this); // device context for painting	

	// Grab
	if(bGrabed)
	{
		bGrabed = false;

		// Main Image
		double	WindowRatioW = m_WindowWidth/(double)SourceImage.GetWidth();
		double	WindowRatioH = m_WindowHeight/(double)SourceImage.GetHeight();	
		CDC *Grabdc = GetDlgItem(IDC_SOCKETVISION_SHOWWINDOW)->GetDC(); // device context for painting
		SourceImage.Draw(Grabdc->GetSafeHdc(), WindowRatioW, WindowRatioH);
		
		// Sub Image
		double	SubWindowRatioW = m_SubWindowWidth/(double)SourceImage.GetWidth();
		double	SubWindowRatioH = m_SubWindowHeight/(double)SourceImage.GetHeight();	
		CDC *GrabSubdc = GetDlgItem(IDC_SETUP_GRABIMAGE1)->GetDC(); // device context for painting
		SourceImage.Draw(GrabSubdc->GetSafeHdc(), SubWindowRatioW, SubWindowRatioH);
		
		// Draw ROI
		Grabdc->SelectObject(&sourcePen);
		SourceROI.DrawFrame(Grabdc->GetSafeHdc(), E_FRAME_ON, FALSE,WindowRatioW,WindowRatioH);
		ReleaseDC(Grabdc);		
	}

	// File List change..
	if(bSelected)
	{
		bSelected = false;
		double	WindowRatioW = m_WindowWidth/(double)SourceImage.GetWidth();
		double	WindowRatioH = m_WindowHeight/(double)SourceImage.GetHeight();	
		CDC *Grabdc = GetDlgItem(IDC_SOCKETVISION_SHOWWINDOW)->GetDC(); // device context for painting
		SourceImage.Draw(Grabdc->GetSafeHdc(), WindowRatioW, WindowRatioH);
		
		//
		double	SubWindowRatioW = m_SubWindowWidth/(double)SourceImage.GetWidth();
		double	SubWindowRatioH = m_SubWindowHeight/(double)SourceImage.GetHeight();	
		CDC *GrabSubdc = GetDlgItem(IDC_SETUP_GRABIMAGE1)->GetDC(); // device context for painting
		SourceImage.Draw(GrabSubdc->GetSafeHdc(), SubWindowRatioW, SubWindowRatioH);
		
		//
		Grabdc->SelectObject(&sourcePen);
		SourceROI.DrawFrame(Grabdc->GetSafeHdc(), E_FRAME_ON, FALSE,WindowRatioW,WindowRatioH);
		ReleaseDC(Grabdc);	
	}

	// Draw ROI Image
	if( bPatterned )
	{
		bPatterned = false;

		CDC *GrabPatterndc = GetDlgItem(IDC_SETUP_PATTERN1)->GetDC(); // device context for painting
		double	WindowRatioW = 0.0;
		double	WindowRatioH = 0.0;
// 		WindowRatioW = m_PatternWindowWidth/(double)m.m_VisionMatch.m_Match[m.m_VisionMatch.m_iCameraUseID].PatternROIColor.GetWidth();	
// 		WindowRatioH = m_PatternWindowHeight/(double)m.m_VisionMatch.m_Match[m.m_VisionMatch.m_iCameraUseID].PatternROIColor.GetHeight();
//		m.m_VisionMatch.m_Match[m.m_VisionMatch.m_iCameraUseID].PatternROIColor.Draw(GrabPatterndc->GetSafeHdc(),WindowRatioW,WindowRatioH);
//Jerome Add 20140707
		WindowRatioW = m_PatternWindowWidth/(double)m.m_VisionMatch.m_Match[m.m_CCDPin1Control.iCCDUse].PatternROIColor.GetWidth();	
		WindowRatioH = m_PatternWindowHeight/(double)m.m_VisionMatch.m_Match[m.m_CCDPin1Control.iCCDUse].PatternROIColor.GetHeight();
		m.m_VisionMatch.m_Match[m.m_CCDPin1Control.iCCDUse].PatternROIColor.Draw(GrabPatterndc->GetSafeHdc(),WindowRatioW,WindowRatioH);

		ReleaseDC(GrabPatterndc);	
	}

	//
	if( bPatternSelected )
	{
		bPatternSelected = false;

		CDC *GrabSelPatterndc = GetDlgItem(IDC_SETUP_PATTERN1)->GetDC(); // device context for painting
		double	WindowRatioW = 0.0;
		WindowRatioW = m_PatternWindowWidth/(double)SourceROI.GetWidth();
		double	WindowRatioH = 0.0;
		WindowRatioH = m_PatternWindowHeight/(double)SourceROI.GetHeight();		
		SourceROI.Draw(GrabSelPatterndc->GetSafeHdc(),WindowRatioW,WindowRatioH);
		ReleaseDC(GrabSelPatterndc);	
	}

	// Reset ROI
	if(bRoied)
	{
		bRoied = false;
		double	WindowRatioW = m_WindowWidth/(double)SourceImage.GetWidth();
		double	WindowRatioH = m_WindowHeight/(double)SourceImage.GetHeight();	
		CDC *Grabdc = GetDlgItem(IDC_SOCKETVISION_SHOWWINDOW)->GetDC(); // device context for painting
		SourceImage.Draw(Grabdc->GetSafeHdc(), WindowRatioW, WindowRatioH);
		Grabdc->SelectObject(&sourcePen);
		SourceROI.DrawFrame(Grabdc->GetSafeHdc(), E_FRAME_ON, FALSE,WindowRatioW,WindowRatioH);
		ReleaseDC(Grabdc);		
	}
}

void CDlgPin1VisionSetting::OnDestroy() 
{
	CDialog::OnDestroy();
	
	//
	sourcePen.DeleteObject();
}

void CDlgPin1VisionSetting::OnSelchangeSocketvisionClass() 
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
