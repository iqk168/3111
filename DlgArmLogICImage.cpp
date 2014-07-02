// DlgArmLogICImage.cpp : implementation file
//

#include "stdafx.h"
#include "deer.h"
#include "DlgArmLogICImage.h"

#include "ViewIC.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgArmLogICImage dialog


CDlgArmLogICImage::CDlgArmLogICImage(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgArmLogICImage::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgArmLogICImage)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	m_Folder.RemoveAll();

	m_Files.RemoveAll();
}


void CDlgArmLogICImage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgArmLogICImage)
	DDX_Control(pDX, IDC_IMAGE,							m_wndImage);
	DDX_Control(pDX, IDC_STATIC_LAST_FLODER,			m_wndLastFolder);
	DDX_Control(pDX, IDC_STATIC_FILE_LIST_COUNTER,		m_wndlistFileCounter);
	DDX_Control(pDX, IDC_LIST_FILE,						m_listFolderFileStatus);
	DDX_Control(pDX, IDC_STATIC_FLODER_LIST_COUNTER,	m_wndlistFolderCounter);
	DDX_Control(pDX, IDC_LIST_FOLDER,					m_listFolderStatus);
	DDX_Control(pDX, IDCANCEL,							m_btnCancel);
	DDX_Control(pDX, IDOK,								m_btnOK);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgArmLogICImage, CDialog)
	//{{AFX_MSG_MAP(CDlgArmLogICImage)
	ON_BN_CLICKED(IDC_STATIC_FLODER_LIST,		OnStaticFloderList)
	ON_BN_CLICKED(IDC_STATIC_FILE_LIST,			OnStaticFileList)
	ON_LBN_SELCHANGE(IDC_LIST_FOLDER,			OnSelchangeListFolder)
	ON_LBN_DBLCLK(IDC_LIST_FILE,				OnDblclkListFile)
	ON_LBN_DBLCLK(IDC_LIST_FOLDER,				OnDblclkListFolder)
	ON_LBN_SELCHANGE(IDC_LIST_FILE,				OnSelchangeListFile)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgArmLogICImage message handlers

void CDlgArmLogICImage::OnOK() 
{
	m.Info.bSubDlgOpen = false;
	f.UpdateButtonState();
	

	CDialog::OnOK();
}

void CDlgArmLogICImage::OnCancel() 
{
	m.Info.bSubDlgOpen = false;
	f.UpdateButtonState();
	
	CDialog::OnCancel();
}

BOOL CDlgArmLogICImage::PreTranslateMessage(MSG* pMsg) 
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

BOOL CDlgArmLogICImage::OnInitDialog() 
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

	//
	InitImageValue();

	//
	InitValue();
	
	//
	UpdataFolderStatus();

	//
	SetFolderValue(0);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
void CDlgArmLogICImage::InitImageValue()
{
	//
	CRect rect;
	m_wndImage.GetClientRect(&rect);

	pViewICImage = new CViewIC;	
	pViewICImage->Create(NULL, "CCDImage", WS_CHILD | WS_VISIBLE, rect, 
		(CWnd *)&m_wndImage, IDC_IMAGE);
}
void CDlgArmLogICImage::InitValue()
{
	CString csLastFileFolder = _T("");
	csLastFileFolder.Format("Last Path: %s", m.m_ArmLogICImage.csImageFilePath );
	m_wndLastFolder.SetWindowText( csLastFileFolder );
}
CString CDlgArmLogICImage::GetFileName()
{
	CString csFileName = _T("");

	int iSel = m_listFolderFileStatus.GetCurSel();
	m_listFolderFileStatus.GetText(iSel,  csFileName );

	return csFileName;
}
CString CDlgArmLogICImage::GetFolderName()
{
	CString csFolderName = _T("");

	int iSel = m_listFolderStatus.GetCurSel();
	m_listFolderStatus.GetText(iSel,  csFolderName );

	return csFolderName;
}
void CDlgArmLogICImage::SetFolderValue(int iIndex)
{
	int iSize = m_Folder.GetSize();
	if( iIndex > iSize )
		iIndex = 0;

	if( iSize == 0 )
	{
		m_listFolderFileStatus.ResetContent(); // last one clear all
		return;
	}

	m_listFolderStatus.SetCurSel(iIndex);

	//
	CString csFolderName = GetFolderName();
	UpdataFileStatus( csFolderName );
}
void CDlgArmLogICImage::DeleteImageFolder(CString csFolderName)
{
	CString csFilePath = _T("");
	csFilePath = m.FilePath.ArmLogICImagePath + csFolderName + "\\";

	CFileFind find;	
	BOOL bResult = find.FindFile( csFilePath + _ArmLogICImage2 );	
	CString file = _T("");
	m_Files.RemoveAll();
	long lFileSize = 0.0;
	while(bResult)
	{
		bResult = find.FindNextFile();
		file = find.GetFileName();	// Get File Name..
		if(file.Find( _ArmLogICImage, 0)>-1)
		{
			// show file data
			CString csDeleteFilePath = _T("");
			csDeleteFilePath = m.FilePath.ArmLogICImagePath + csFolderName + "\\" + file;
			
			::DeleteFile( csDeleteFilePath );
		}
	}

	//
	CString csDeleteDbFilePath = _T("");
	csDeleteDbFilePath = m.FilePath.ArmLogICImagePath + csFolderName + "\\" + _ArmLogICDb;
	::DeleteFile( csDeleteDbFilePath );

	//
	RemoveDirectory( m.FilePath.ArmLogICImagePath + csFolderName );
}
void CDlgArmLogICImage::UpdataFileStatus(CString csFolderName)
{
	CString csFilePath = _T("");
	csFilePath = m.FilePath.ArmLogICImagePath + csFolderName + "\\";

	CFileFind find;	
	BOOL bResult = find.FindFile( csFilePath + _ArmLogICImage2 );	
	CString file = _T("");
	m_Files.RemoveAll();
	long lFileSize = 0.0;
	while(bResult)
	{
		bResult = find.FindNextFile();
		file = find.GetFileName();	// Get File Name..
		if(file.Find( _ArmLogICImage, 0)>-1)
		{
			// show file data
			CString csfile_status;
			CString csSingleFilePath = _T("");
			csSingleFilePath = m.FilePath.ArmLogICImagePath + csFolderName + "\\" + file;
			csfile_status.Format("%s", csSingleFilePath );
			CFileStatus status;
			CFile::GetStatus( csfile_status, status );		

			long lSize = status.m_size;
			lFileSize += lSize;
			
			m_Files.Add( file );
		}
	}

	m_listFolderFileStatus.ResetContent();
	int iSize = m_Files.GetSize();
	for(int i=0;i<iSize;i++)
		m_listFolderFileStatus.AddString( m_Files.GetAt(i) );

	// 
	CString csCount = _T("");
	csCount.Format("File Counter: %d, MB: %5.2f (%d Bytes)", iSize, lFileSize / 1048., lFileSize );
	m_wndlistFileCounter.SetWindowText( csCount );
}
void CDlgArmLogICImage::UpdataFolderStatus()
{
	// Get the folder name
	m_Folder.RemoveAll();

	CString csFilePath = _T("");
	csFilePath = m.FilePath.ArmLogICImagePath;
	CFileFind finder;											//建立搜尋用的CFileFind物件
	BOOL bResult = finder.FindFile( csFilePath  + "*.*" );		//尋找第一個檔案
	while(bResult)
	{
		bResult = finder.FindNextFile();						//尋找下一個檔案
		if(!finder.IsDots() && finder.IsDirectory())
		{
			CString csFileDirectory = _T("");
			csFileDirectory.Format("%s", finder.GetFileTitle() );
			
			m_Folder.Add( csFileDirectory );
		}
	}
	
	m_listFolderStatus.ResetContent();
	int iSize = m_Folder.GetSize();
	for(int i=0;i<iSize;i++)
	{
		CString csFolderName = _T("");
		csFolderName = m_Folder.GetAt(i);
		m_listFolderStatus.AddString( csFolderName );
	}
	CString csFolderCounter = _T("");
	csFolderCounter.Format("Folder Counter: %d", iSize );
	m_wndlistFolderCounter.SetWindowText( csFolderCounter );
}
void CDlgArmLogICImage::OnStaticFloderList() 
{
	
}
void CDlgArmLogICImage::OnStaticFileList() 
{

}
void CDlgArmLogICImage::LoadImage() 
{
	CString csFolderName = GetFolderName();
	CString csFileName = GetFileName();
	CString csFilePath = m.FilePath.ArmLogICImagePath + "" + csFolderName + "\\" + csFileName;

#ifdef _Demo
	AfxMessageBox( csFilePath );
#endif

	pViewICImage->SetFileName( csFilePath );	
	pViewICImage->Invalidate( FALSE );
	CenterWindow();
}
void CDlgArmLogICImage::OnSelchangeListFolder() 
{
	CString csFolderName = GetFolderName();
	UpdataFileStatus( csFolderName );	
}

void CDlgArmLogICImage::OnDblclkListFile() 
{
	CString csFileName = GetFileName();
	CString csMsg = _T("");
	csMsg.Format("Delete this file [%s] ?\n", csFileName );
	if(IDYES != AfxMessageBox( csMsg,
			MB_YESNO|MB_ICONEXCLAMATION))
	{
		// No
	}
	else
	{
		// Delete
		CString csFolderName = GetFolderName();
		CString csFilePath = _T("");
		csFilePath = m.FilePath.ArmLogICImagePath + "\\" + csFolderName + "\\" + csFileName;
		::DeleteFile( csFilePath );
		
		//
		UpdataFileStatus( csFolderName );
	}	
}

void CDlgArmLogICImage::OnDblclkListFolder() 
{
	CString csFolderName = GetFolderName();
	CString csFilePath = _T("");
	CString csMsg = _T("");
	csMsg.Format("Delete Folder [%s] ?\n", csFolderName );
	if(IDYES != AfxMessageBox( csMsg,
			MB_YESNO|MB_ICONEXCLAMATION))
	{
		// No
	}
	else
	{
		DeleteImageFolder( csFolderName );
		UpdataFolderStatus();
		SetFolderValue(0);
	}
}

void CDlgArmLogICImage::OnSelchangeListFile() 
{
	LoadImage();	
}

void CDlgArmLogICImage::OnDestroy() 
{
	if( pViewICImage != NULL )
		delete pViewICImage;

	CDialog::OnDestroy();	
}
