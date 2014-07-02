// DlgATCModuleNew.cpp : implementation file
//

#include "stdafx.h"
#include "deer.h"
#include "DlgATCModuleNew.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgATCModuleNew dialog


CDlgATCModuleNew::CDlgATCModuleNew(CString csFile, CWnd* pParent /*=NULL*/)
	: CDialog(CDlgATCModuleNew::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgATCModuleNew)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	m_csFile = csFile;
}


void CDlgATCModuleNew::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgATCModuleNew)
	DDX_Control(pDX, IDC_NEW_FILE, m_wndNewFile);
	DDX_Control(pDX, IDC_FILE, m_wndBaseFile);
	DDX_Control(pDX, IDOK,		m_btnOK);
	DDX_Control(pDX, IDCANCEL,	m_btnCancel);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgATCModuleNew, CDialog)
	//{{AFX_MSG_MAP(CDlgATCModuleNew)
	ON_WM_SHOWWINDOW()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgATCModuleNew message handlers

BOOL CDlgATCModuleNew::PreTranslateMessage(MSG* pMsg) 
{
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

BOOL CDlgATCModuleNew::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// init button 
	m_btnOK.SetIcon(IDI_SAVE);
	m_btnOK.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnOK.SetFlat(FALSE);
	
	m_btnCancel.SetIcon(IDI_CANCEL);
	m_btnCancel.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnCancel.SetFlat(FALSE);

	InitValue();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
void CDlgATCModuleNew::InitValue() 
{
	m_wndBaseFile.SetText(m_csFile, 10, "Arial Black", DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	m_wndBaseFile.SetNewBkColor(ST_WHITE);
}
void CDlgATCModuleNew::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);
	
	// TODO: Add your message handler code here
	
}
bool CDlgATCModuleNew::IsFileExist(CString csFile) 
{
	bool m_bExist = false;
	// if file exist return true

	CFileFind find;	
	BOOL bResult = find.FindFile( m.FilePath.AtcModuleSettingPath + _Atc1 );	
	CString file = _T("");
	while(bResult)
	{
		bResult = find.FindNextFile();
		file = find.GetFileName();	// Get File Name..
		if(file.Find( _Atc2, 0)>-1)
		{
			// find file success...
			if( file == csFile )
			{
				m_bExist = true;
				break;
			}			
		}
	}

	return m_bExist;
}
bool CDlgATCModuleNew::CreateNewFile() 
{
	bool m_bNewOK = true;

	CString m_csNewFile = _T("");
	m_wndNewFile.GetWindowText( m_csNewFile );

	m_csNewFile.TrimLeft();
	m_csNewFile.TrimRight();

	// Check File Exist
	if( IsFileExist(m_csNewFile + _Atc2) )
	{
		CString csMsg = _T("");
		csMsg.Format("File already exist. Please replace with new one.!");
		AfxMessageBox( csMsg );
		m_bNewOK = false;
		return m_bNewOK;

	}

	// Copy New File
	if(!::CopyFile( m.FilePath.AtcModuleSettingPath + m_csFile + _Atc2, 
		m.FilePath.AtcModuleSettingPath + m_csNewFile + _Atc2, TRUE))
	{
		CString csMsg = _T("");
		csMsg.Format("CopyFile Fail.!");
		AfxMessageBox( csMsg );
		m_bNewOK = false;
		return m_bNewOK;
	}

	return m_bNewOK;
}
void CDlgATCModuleNew::OnOK() 
{
	if(!CreateNewFile())
		return;

	CDialog::OnOK();
}

void CDlgATCModuleNew::OnCancel() 
{
	
	CDialog::OnCancel();
}
