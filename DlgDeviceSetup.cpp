// DlgDeviceSetup.cpp : implementation file
//

#include "stdafx.h"
#include "deer.h"
#include "DlgDeviceSetup.h"

// Dlg
#include "DlgTrayFile.h"
#include "DlgBinMapping.h"
#include "DlgTrayFileNoHeater.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgDeviceSetup dialog

CDlgDeviceSetup::CDlgDeviceSetup(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgDeviceSetup::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgDeviceSetup)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_TestType = -1;

	//
	m_bCCDSocketEnable = false;
}


void CDlgDeviceSetup::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgDeviceSetup)
	DDX_Control(pDX, IDC_LAST_TRAY,					m_btnLastTrayFile);
	DDX_Control(pDX, IDC_STATIC_CCD_SOCKET_FILE,	m_wndStaticSocketCCDFile);
	DDX_Control(pDX, IDC_STATIC_CCD_FILE,			m_wndStaticCCDFile);
	DDX_Control(pDX, IDC_INDEX_CCD,					m_wndCCDGroup);
	DDX_Control(pDX, IDC_MODIFY_PARAMETER,			m_btnModify);
	DDX_Control(pDX, IDC_CCD_SOCKET_FILE,			m_cbxCCDSocketSettingFileList);
	DDX_Control(pDX, IDC_CCD_FILE,					m_cbxCCDSettingFileList);
	DDX_Control(pDX, IDC_TRAY_FILE,					m_cbxFileList);
	DDX_Control(pDX, IDC_CATEGORY,					m_cbxMappingFileList);	
	DDX_Control(pDX, IDC_TEST_SETTING,				m_cbxTestSettingFileList);	
	DDX_Control(pDX, IDCANCEL,						m_btnCancel);
	DDX_Control(pDX, IDOK,							m_btnOK);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgDeviceSetup, CDialog)
	//{{AFX_MSG_MAP(CDlgDeviceSetup)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_OPEN_TRAY_FILE,				OnOpenTrayFile)
	ON_BN_CLICKED(IDC_OPEN_CATEGORY,				OnOpenCategory)
	ON_BN_CLICKED(IDC_OPEN_TEST_SETTING,			OnOpenTestSetting)		
	ON_BN_CLICKED(IDC_MODIFY_PARAMETER,				OnModifyParameter)	
	ON_WM_CLOSE()
	ON_CBN_SELCHANGE(IDC_TRAY_FILE,					OnSelchangeTrayFile)
	ON_CBN_SELENDOK(IDC_TRAY_FILE,					OnSelendokTrayFile)
	ON_CBN_EDITUPDATE(IDC_TRAY_FILE,				OnEditupdateTrayFile)
	ON_CBN_DROPDOWN(IDC_TRAY_FILE,					OnDropdownTrayFile)
	ON_WM_SHOWWINDOW()
	ON_BN_CLICKED(IDC_LAST_TRAY, OnLastTray)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgDeviceSetup message handlers

BOOL CDlgDeviceSetup::OnInitDialog() 
{
	CDialog::OnInitDialog();

	m.Info.bSubDlgOpen = true;
	f.UpdateButtonState();	

	// init button 
	m_btnOK.SetIcon(IDI_OK);;
	m_btnOK.SetAlign(CButtonST::ST_ALIGN_VERT);;
	m_btnOK.SetFlat(FALSE);
	
	m_btnCancel.SetIcon(IDI_CANCEL);
	m_btnCancel.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnCancel.SetFlat(FALSE);

	m_btnModify.SetIcon(IDI_SAVE);
	m_btnModify.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnModify.SetFlat(FALSE);

	m_btnLastTrayFile.SetIcon(IDI_LAST_TRAY);
	m_btnLastTrayFile.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnLastTrayFile.SetFlat(FALSE);

	UpdateTrayFileList();
	UpdateBinFileList();
	UpdateTestSettingFileList();

	// CCD Group
	UpdateCCDSettingFileList();
	UpdateCCDSocketSettingFileList();

	// UpdataCurrent File
	UpdataCurrentFile();

//Jerome Add 20140709
	// UpdataCurrent CCD Pin1 File (Profile)
//	UpdataCurrentFileCCD();

	// If No use ccd pin1, disable it
	LockUIForCCDPin1();

	// If No use ccd socket, disable it.
//	LockUIForCCDSocket();

	// Initial Last TrayFile Status
	InitLastTrayFile();

	//
	f.ChangeLanguage(GetSafeHwnd());
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgDeviceSetup::OnDestroy() 
{
	CDialog::OnDestroy();		
}

void CDlgDeviceSetup::OnOK() 
{
	m.Info.bSubDlgOpen = false;
	f.UpdateButtonState();

	CDialog::OnOK();
}

void CDlgDeviceSetup::OnCancel() 
{
	m.Info.bSubDlgOpen = false;
	f.UpdateButtonState();
	
	CDialog::OnCancel();
}

////////////////////////////////////////////////////////////////////////////
// Updata File list 
void CDlgDeviceSetup::UpdataCurrentFile()
{
	if( m.UI.FileMain != "" )
	{
		// 1.0Ac, change style to droplist
		int iSel = m_cbxFileList.FindString(0, m.UI.FileMain );
		m_cbxFileList.SetCurSel( iSel );

		m_cbxMappingFileList.SetWindowText(m.UI.FileMainMapping);
		m_cbxTestSettingFileList.SetWindowText(m.UI.FileMainTestSetting);
		m_cbxCCDSocketSettingFileList.SetWindowText(m.UI.SocketPatternName);
//Jerome Add 20140709
		m_cbxCCDSettingFileList.SetWindowText(m.UI.Pin1PatternName);
	}
	else{}
}
void CDlgDeviceSetup::UpdataCurrentFileCCD()
{
	if( m.UI.FileMain != "" )
	{
		CString csVisionFile = _T("");
		LoadTrayVision(csVisionFile);
		csVisionFile.TrimLeft();
		csVisionFile.TrimRight();

		//
		int iCCDPorfileSel = 0;
		iCCDPorfileSel = m_cbxCCDSettingFileList.FindString( 0, csVisionFile );
		m_cbxCCDSettingFileList.SetCurSel( iCCDPorfileSel );
	}
}
void CDlgDeviceSetup::UpdateTrayFileList()
{
	CFileFind findList;
	CString tempStr;
	BOOL findResult;

	// Update List: Mapping File
	findResult = findList.FindFile( m.FilePath.TrayFilesPath + "\\" + _SubFileName1 );
	m_cbxFileList.ResetContent();

	while(findResult)
	{
		findResult = findList.FindNextFile();
		tempStr = findList.GetFileName();
		if(tempStr.Find( _SubFileName2, 0)>-1)
			m_cbxFileList.AddString(tempStr);
	}
	findList.Close();
}
void CDlgDeviceSetup::UpdateBinFileList()
{
	CFileFind findList;
	CString tempStr;
	BOOL findResult;

	// Update List: Mapping File
	findResult = findList.FindFile( m.FilePath.CategoryPath + "\\" + _SubMappingName1 );
	m_cbxMappingFileList.ResetContent();

	while(findResult)
	{
		findResult = findList.FindNextFile();
		tempStr = findList.GetFileName();
		if(tempStr.Find( _SubMappingName2, 0)>-1)
			m_cbxMappingFileList.AddString(tempStr);
	}
	findList.Close();
}

void CDlgDeviceSetup::UpdateTestSettingFileList()
{
	CFileFind findList;
	CString tempStr;
	BOOL findResult;

	// Update List: Test Setting File
	findResult = findList.FindFile( m.FilePath.TestSettingPath + "\\" + _SubTestSettingName1 );
	m_cbxTestSettingFileList.ResetContent();

	while(findResult)
	{
		findResult = findList.FindNextFile();
		tempStr = findList.GetFileName();
		if(tempStr.Find( _SubTestSettingName2, 0)>-1)
			m_cbxTestSettingFileList.AddString(tempStr);
	}
	findList.Close();
}

void CDlgDeviceSetup::UpdateCCDSettingFileList()
{
	CFileFind findList;

	// Update List: CCD File
	m_cbxCCDSettingFileList.ResetContent();

	//
	CString csFilePath = _T("");
	csFilePath = m.FilePath.CCDImageProfilePath;

	//
	CFileFind finder;											//建立搜尋用的CFileFind物件
//	BOOL bResult = finder.FindFile( csFilePath  + "*.*" );		//尋找第一個檔案
//	Jerome Add 20140709
	BOOL bResult = finder.FindFile( m.FilePath.CCDPin1ImagePath + "*.*" );	//尋找第一個檔案
	while(bResult)
	{
		bResult = finder.FindNextFile();						//尋找下一個檔案
		if(!finder.IsDots() && finder.IsDirectory())
		{
			CString csFileDirectory = _T("");
			csFileDirectory.Format("%s", finder.GetFileTitle() );
			
			m_cbxCCDSettingFileList.AddString( csFileDirectory );
		}
	}
}
void CDlgDeviceSetup::UpdateCCDSocketSettingFileList()
{
	CFileFind finder;														
	//建立搜尋用的CFileFind物件
	
	BOOL bResult = finder.FindFile( m.FilePath.CCDSocketImagePath	 + "*.*" );	//尋找第一個檔案
	while(bResult)
	{
		bResult = finder.FindNextFile();									//尋找下一個檔案
		if(!finder.IsDots() && finder.IsDirectory())
		{
			CString csFileDirectory;
			csFileDirectory.Format("%s", finder.GetFileTitle() );
			
			m_cbxCCDSocketSettingFileList.AddString( csFileDirectory );
		}
	}
}
void CDlgDeviceSetup::OnOpenTrayFile() 
{
	CDlgTrayFileNoHeater dlg;
	dlg.DoModal();

	// Re-set the File List.!
	UpdateTrayFileList();
	UpdataCurrentFile();
}

void CDlgDeviceSetup::OnOpenCategory() 
{

}

void CDlgDeviceSetup::OnOpenTestSetting()
{

}
void CDlgDeviceSetup::LoadTrayVision(CString &csVisiionPattern)
{
	CString csFile = _T("");
	csFile = m.FilePath.TrayFilesPath + m.UI.FileMain;
	f.GetSetting(csFile, "Vision Pattern", "File",	csVisiionPattern);
}
void CDlgDeviceSetup::LoadTrayVision(CString csTrayFile, CString &csVisiionPattern)
{
	CString csFile = _T("");
	csFile = m.FilePath.TrayFilesPath + csTrayFile;
	f.GetSetting(csFile, "Vision Pattern", "File",	csVisiionPattern);
}
void CDlgDeviceSetup::SaveTrayVision(CString csVisiionPattern)
{
	CString csFile = _T("");
	csFile = m.FilePath.TrayFilesPath + m.UI.FileMain;
	f.SaveSetting(csFile, "Vision Pattern", "File",	csVisiionPattern);
}
void CDlgDeviceSetup::SaveTrayVision(CString csTrayFile, CString csVisiionPattern)
{
	CString csFile = _T("");
	csFile = m.FilePath.TrayFilesPath + csTrayFile;
	f.SaveSetting(csFile, "Vision Pattern", "File",	csVisiionPattern);
}
void CDlgDeviceSetup::OnModifyParameter() 
{	
//Jerome Change 20140709
#ifndef _Demo 
	if( !f.CheckEnaleChange() )
		return;
#endif

	UpdateData();

	int iSel = 0;
	CString cFile = _T("");
	m_cbxFileList.GetLBText( iSel, cFile );
	if( cFile != m.UI.FileMain )
	{		
		// Check data exist first 
		if(m_cbxFileList.GetCurSel() < 0)
		{
			CString csMsg = _T("");
			csMsg.Format("Please Select Tray File");
			AfxMessageBox( csMsg );
			return;
		}
	}
	//////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////
	// CCD Pin1	Jerome Add 20140709
	CString csCCDPin1 = _T("");
	m_cbxCCDSettingFileList.GetWindowText( csCCDPin1 );
	if( m.Setting.m_bEnableCCDPin1 == 1 )
	{
		csCCDPin1.TrimLeft();
		csCCDPin1.TrimRight();
		if( csCCDPin1 != "" )
		{
			// 儲存
			m.UI.Pin1PatternName = csCCDPin1;
			f.SaveSocketPattern();
		}	
		else
		{
			CString csMsg = _T("");
			csMsg.Format("Please select CCD Pin1 File");
			AfxMessageBox( csMsg );
			return;
		}
	}

//舊寫法
// 	CString csCCDPin1Profile = _T("");
// 	int iCCDSel = m_cbxCCDSettingFileList.GetCurSel();
// 	if( m.Setting.m_bEnableCCDPin1 == 1 )
// 	{
// 		if( m.m_TestSetting.m_CCDUse == 1 )
// 		{
// 			if(m_cbxCCDSettingFileList.GetCurSel() < 0)
// 			{
// 				CString csMsg = _T("");
// 				csMsg.Format("Please select CCD Pin1 Profile");
// 				AfxMessageBox( csMsg );
// 				return;
// 			}
// 			else
// 			{
// 				m_cbxCCDSettingFileList.GetLBText( iCCDSel, csCCDPin1Profile );
// 				CString csTrayFileName = _T("");
// 				m_cbxFileList.GetWindowText(csTrayFileName);
// 				// 儲存檔案到 TrayFile..
// 				m.TraySpec.VisionPatternName = csCCDPin1Profile;
// 				SaveTrayVision( csTrayFileName, csCCDPin1Profile );
// 			}
// 		}
// 	}
	//////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////
	// CCD Socket 
	CString csCCDSocket = _T("");
	m_cbxCCDSocketSettingFileList.GetWindowText( csCCDSocket );
	if( m.Setting.m_bEnableCCDSocket == 1 )
	{
		csCCDSocket.TrimLeft();
		csCCDSocket.TrimRight();
		if( csCCDSocket != "" )
		{
			// 儲存
			m.UI.SocketPatternName = csCCDSocket;
			f.SaveSocketPattern();
		}	
		else
		{
			CString csMsg = _T("");
			csMsg.Format("Please select CCD Socket File");
			AfxMessageBox( csMsg );
			return;
		}
	}
	//////////////////////////////////////////////////////////

	// Init value
	CString File			= "";
	CString MappingFile		= "";
	CString TestSettingFile = "";

	m_cbxFileList.GetWindowText(File);
	m_cbxMappingFileList.GetWindowText(MappingFile);
	m_cbxTestSettingFileList.GetWindowText(TestSettingFile);

	m.UI.FileMain					= File;
	m.UI.FileMainMapping			= MappingFile;
	m.UI.FileMainTestSetting		= TestSettingFile;
	f.LoadTraySpec();

	m.TraySpec.MappingName			= MappingFile;
	m.TraySpec.TestingName			= TestSettingFile;
	f.SaveTraySpec();
	// Tray Spec for vision

	f.SaveUI();
	f.LoadUI();
	// Save & Load UI

	// 1: Speed. 2:Yield. 3: Offset. 4:TraySpec.ABCD. 5: Temperature 6: SiteSetting. 7:Timer. 8:TTL
	// 9: Drop/Place. 10:Category. 11:Test Info. 12: Bin Mapping. 13: Slow Contact
	
	f.LoadSpeed();			// #1
	f.LoadYield();			// #2
	f.LoadOffset();			// #3
	f.LoadTraySpec();		// #4
	f.LoadSiteSetting();	// #5
	f.LoadTimer();			// #6
	f.LoadBinMapping();		// #7
//	f.LoadCategory();		// #7
	f.LoadPogoParameter();	// #8
	f.LoadOutputYield();	// #9

	f.LoadAlignment();		// 	
	f.LoadMotorParameter();
	f.LoadTestSetting();
	//
	f.LoadInterface();
	f.LoadInterFaceRs232();
	f.LoadInterFaceTcp();
	f.LoadTcpToObject();

	// 更新 Run Page 畫面.!
	m.Page.Run.UpdateSetting();

	// 重新設定 Tray Data
	f.SetTrayData();

	// 更新整個 Tray 的資料
	theApp.m_InputTray.ChangeTray();
	theApp.m_OutputTray.ChangeTray();

	// 更新整個 Tray 的資料 / Repeat Tray
	theApp.m_Tray1.ChangeTray();
	theApp.m_Tray2.ChangeTray();

	// 紀錄本次所選 TrayFile
	f.SaveLastTrayFile();

	f.LoadSocketPatternSetting();

	//
	CDialog::OnOK();
}

void CDlgDeviceSetup::OnClose() 
{
	CDialog::OnClose();
}

BOOL CDlgDeviceSetup::PreTranslateMessage(MSG* pMsg) 
{
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

void CDlgDeviceSetup::LoadTrayFile(CString csFile)
{
	CString csFilePath = _T("");
	csFile = m.FilePath.TrayFilesPath + csFile;

	f.GetSetting(csFile, "Vision Pattern",  "File",			m_Vision );
	f.GetSetting(csFile, "Mapping",		    "MappingFile",	m_Mapping );
	f.GetSetting(csFile, "Testing",		    "TestFile",		m_Testing );
}

void CDlgDeviceSetup::OnSelchangeTrayFile() 
{
	CString File = _T("");

	int iSel = m_cbxFileList.GetCurSel();
	if( iSel == -1 )
		return;

	m_cbxFileList.GetLBText( iSel, File );
	LoadTrayFile( File );

	// 更新 File List
	m_cbxMappingFileList.SetWindowText( m_Mapping );
	m_cbxTestSettingFileList.SetWindowText( m_Testing );

	// 更新 CCD List / Enable / Disable
	LockUIForCCDPin1();

	// 更新 CCD File
	int iCCDPorfileSel = 0;
	CString csVisionFile = _T("");
	CString csTrayFile = _T("");
	csTrayFile = File;
	LoadTrayVision( csTrayFile, csVisionFile );
	iCCDPorfileSel = m_cbxCCDSettingFileList.FindString( 0, csVisionFile );
	m_cbxCCDSettingFileList.SetCurSel( iCCDPorfileSel );
}
void CDlgDeviceSetup::OnSelendokTrayFile() 
{
	
}
void CDlgDeviceSetup::OnEditupdateTrayFile() 
{

}
void CDlgDeviceSetup::OnDropdownTrayFile() 
{
	
}
void CDlgDeviceSetup::ReDrawUI()
{
	if( m.Setting.m_bEnableCCDPin1 == 1 || m.Setting.m_bEnableCCDSocket == 1 )
	{
		m_wndCCDGroup.ShowWindow( TRUE );
	}
	else
	{
		m_wndCCDGroup.ShowWindow( FALSE );
	}

	//
	//////////////////////////////////////////////////////////////////////
	// 重設介面
	int di = 15;
	if( m.Setting.m_bEnableCCDPin1 == 1 && m.Setting.m_bEnableCCDSocket == 1 ) 
	{
		// do nothing.
	}
	else
	{
		if( m.Setting.m_bEnableCCDPin1 == 1 && m.Setting.m_bEnableCCDSocket == 0 )
		{
			RECT rt, rt2;
			::GetWindowRect(::GetDlgItem(m_hWnd, IDC_CCD_FILE), &rt);
			::MapWindowPoints(NULL, m_hWnd, (LPPOINT)&rt, 2);	
			::GetWindowRect(::GetDlgItem(m_hWnd, IDC_STATIC_CCD_FILE), &rt2);
			::MapWindowPoints(NULL, m_hWnd, (LPPOINT)&rt2, 2);

			rt.top = rt.top + di;
			rt.bottom = rt.bottom + di;
			rt2.top = rt2.top + di;
			rt2.bottom = rt2.bottom + di;
			// Only CCD Pin1
			m_cbxCCDSettingFileList.MoveWindow( &rt );
			m_wndStaticCCDFile.MoveWindow( &rt2 );

			// hide another
			m_cbxCCDSocketSettingFileList.ShowWindow( FALSE );
			m_wndStaticSocketCCDFile.ShowWindow( FALSE );
		}
		else if( m.Setting.m_bEnableCCDPin1 == 0 && m.Setting.m_bEnableCCDSocket == 1 )
		{
			RECT rt, rt2;
			::GetWindowRect(::GetDlgItem(m_hWnd, IDC_CCD_SOCKET_FILE), &rt);
			::MapWindowPoints(NULL, m_hWnd, (LPPOINT)&rt, 2);
			::GetWindowRect(::GetDlgItem(m_hWnd, IDC_STATIC_CCD_SOCKET_FILE), &rt2);
			::MapWindowPoints(NULL, m_hWnd, (LPPOINT)&rt2, 2);

			rt.top = rt.top - di;
			rt.bottom = rt.bottom - di;
			rt2.top = rt2.top - di;
			rt2.bottom = rt2.bottom - di;	
			
			// Only CCD Socket 
			m_cbxCCDSocketSettingFileList.MoveWindow( &rt );
			m_wndStaticSocketCCDFile.MoveWindow( &rt2 );

			// hide another
			m_cbxCCDSettingFileList.ShowWindow( FALSE );
			m_wndStaticCCDFile.ShowWindow( FALSE );
		}
		else
			; // do nothing...	
	}

}
void CDlgDeviceSetup::LockUIForCCDPin1()
{
//Jerome Add 20140709
	if( m.Setting.m_bEnableCCDPin1 == 1 )
		m_cbxCCDSocketSettingFileList.EnableWindow( TRUE );
	else
		m_cbxCCDSocketSettingFileList.EnableWindow( FALSE );

// 	if( m.Setting.m_bEnableCCDPin1 == 1 )
// 	{		
// 		int iCCDUse = 0;
// 		CString csFile = _T("");
// 		int iSel = 0;
// 		CString csTrayFile = _T("");
// 		iSel = m_cbxFileList.GetCurSel();
// 		if( iSel >= 0 )
// 		{
// 			m_cbxFileList.GetLBText( iSel, csTrayFile );
// 			csTrayFile.Replace( _SubFileName2, "");
// 			csTrayFile = csTrayFile + _SubTestSettingName2;
// 			csFile = m.FilePath.TestSettingPath + csTrayFile;
// 			f.GetSetting(csFile, "Test Extend", "CCD", iCCDUse );
// 			if( iCCDUse == 1 )
// 				m_cbxCCDSettingFileList.EnableWindow( TRUE );
// 			else
// 				m_cbxCCDSettingFileList.EnableWindow( FALSE );
// 		}
// 	}
}
void CDlgDeviceSetup::LockUIForCCDSocket()
{
	if( m.m_TestSetting.m_CCDSocketUse == 1 )
	{
		m_cbxCCDSocketSettingFileList.EnableWindow( TRUE );
	}
	else
	{
		m_cbxCCDSocketSettingFileList.EnableWindow( FALSE );
	}
}
void CDlgDeviceSetup::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	if(bShow)
		ReDrawUI();

	CDialog::OnShowWindow(bShow, nStatus);
}
void CDlgDeviceSetup::InitLastTrayFile()
{
	if( m.m_LastTrayFile.csLastTrayFile	== "" )
		m_btnLastTrayFile.EnableWindow( FALSE );
	else
		m_btnLastTrayFile.EnableWindow( TRUE );
}
void CDlgDeviceSetup::OnLastTray() 
{
	int iFind = m_cbxFileList.FindString(0, m.m_LastTrayFile.csLastTrayFile	);
	if( iFind != CB_ERR )
	{
		m_cbxFileList.SetCurSel( iFind );
		OnSelchangeTrayFile();
	}
	else
	{
		CString csMsg = _T("");
		csMsg.Format("Last TrayFile is missing - [%s]", m.m_LastTrayFile.csLastTrayFile );
		AfxMessageBox( csMsg );
	}
}
