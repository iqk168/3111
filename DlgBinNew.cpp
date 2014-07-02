// DlgBinNew.cpp : implementation file
//

#include "stdafx.h"
#include "deer.h"
#include "DlgBinNew.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgBinNew dialog


CDlgBinNew::CDlgBinNew(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgBinNew::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgBinNew)
	m_csNewFile = _T("");
	//}}AFX_DATA_INIT
}


void CDlgBinNew::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgBinNew)
	DDX_Control(pDX, IDC_MAPPING_BASEFILE, m_wndMappingBase);
	DDX_Control(pDX, IDOK, m_btnOK);
	DDX_Control(pDX, IDCANCEL, m_btnCancel);
	DDX_Text(pDX, IDC_NEW_FILE, m_csNewFile);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgBinNew, CDialog)
	//{{AFX_MSG_MAP(CDlgBinNew)
	ON_WM_DESTROY()
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgBinNew message handlers

BOOL CDlgBinNew::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// init button 
	m_btnOK.SetIcon(IDI_OK);;
	m_btnOK.SetAlign(CButtonST::ST_ALIGN_VERT);;
	m_btnOK.SetFlat(FALSE);

	m_btnCancel.SetIcon(IDI_CANCEL);;
	m_btnCancel.SetAlign(CButtonST::ST_ALIGN_VERT);;
	m_btnCancel.SetFlat(FALSE);

	m_wndMappingBase.SetWindowText( m.UI.FileMainBaseMapping );
	
	f.ChangeLanguage(GetSafeHwnd());

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgBinNew::OnDestroy() 
{
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here
	
}

void CDlgBinNew::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	
	CDialog::OnClose();
}

void CDlgBinNew::OnOK() 
{
	UpdateData();

	CString csFile;

	if( m_csNewFile == "" )
	{
		AfxMessageBox(" Get File Name Fail");
		return;
	}
	csFile = m_csNewFile + _SubMappingName2;

	// 檢查檔案是否存在
	CFileFind Find;
	if(!Find.FindFile( m.FilePath.CategoryPath + m.UI.FileMainBaseMapping ))
	{
		AfxMessageBox("Base File not found!");
		return;
	}

	if(!::CopyFile( m.FilePath.CategoryPath + m.UI.FileMainBaseMapping, 
		m.FilePath.CategoryPath + csFile, TRUE))
	{
		AfxMessageBox( "File Already Exist!" );
		return;
	}

	CDialog::OnOK();
}

void CDlgBinNew::OnCancel() 
{
	
	CDialog::OnCancel();
}

BOOL CDlgBinNew::PreTranslateMessage(MSG* pMsg) 
{
	// z avoid ESC / Enter to crash the software
	if(pMsg->message  == WM_KEYDOWN)   
	{
		int nVirtKey = (int)pMsg->wParam;    
		if( nVirtKey == VK_ESCAPE )
			return   TRUE;   
//		if( nVirtKey == VK_RETURN )   
//			return   TRUE;   
	}	
	return CDialog::PreTranslateMessage(pMsg);
}
