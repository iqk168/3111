// DlgProgramStart.cpp : implementation file
//

#include "stdafx.h"
#include "deer.h"
#include "DlgProgramStart.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgProgramStart dialog


CDlgProgramStart::CDlgProgramStart(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgProgramStart::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgProgramStart)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	m_bPass = true;
}


void CDlgProgramStart::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgProgramStart)
	DDX_Control(pDX, IDC_SHOW_LIST,			m_listShowCtrl);
	DDX_Control(pDX, IDCANCEL,				m_btnCancel);
	DDX_Control(pDX, IDOK,					m_btnOK);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgProgramStart, CDialog)
	//{{AFX_MSG_MAP(CDlgProgramStart)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgProgramStart message handlers

BOOL CDlgProgramStart::PreTranslateMessage(MSG* pMsg) 
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

BOOL CDlgProgramStart::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// init button 
	m_btnOK.SetIcon(IDI_OK);
	m_btnOK.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnOK.SetFlat(FALSE);
	
	m_btnCancel.SetIcon(IDI_CANCEL);
	m_btnCancel.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnCancel.SetFlat(FALSE);

	//
	Style();

	//
	CenterWindow();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
CString CDlgProgramStart::GetFilePath()
{
	CString strFilePath = _T("");
	BROWSEINFO bi;
	char Buffer[512];
	
	bi.hwndOwner = NULL;
	bi.pidlRoot = NULL;
	bi.pszDisplayName = Buffer;
	bi.lpszTitle = "File Path";
	bi.ulFlags = BIF_RETURNONLYFSDIRS;
	bi.lpfn = NULL;
	bi.iImage = 0;
	
	LPITEMIDLIST pIDList = SHBrowseForFolder(&bi);
	if(pIDList)
	{
		SHGetPathFromIDList(pIDList, Buffer);
		strFilePath = Buffer;
		return strFilePath;
	}
	else
		return strFilePath;	
}
void CDlgProgramStart::Style()
{
	LONG lStyle;
	lStyle = GetWindowLong(m_listShowCtrl.m_hWnd, GWL_STYLE);
	lStyle &= ~LVS_TYPEMASK; 
	lStyle |= LVS_REPORT; 
	SetWindowLong(m_listShowCtrl.m_hWnd, GWL_STYLE, lStyle);
	
	DWORD dwStyle = m_listShowCtrl.GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT;
	dwStyle |= LVS_EX_GRIDLINES;
	m_listShowCtrl.SetExtendedStyle(dwStyle); 
}
void CDlgProgramStart::OnOK() 
{
	
	CDialog::OnOK();
}

void CDlgProgramStart::OnCancel() 
{
	
	CDialog::OnCancel();
}
