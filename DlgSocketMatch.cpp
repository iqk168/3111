// DlgSocketMatch.cpp : implementation file
//

#include "stdafx.h"
#include "deer.h"
#include "DlgSocketMatch.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgSocketMatch dialog


CDlgSocketMatch::CDlgSocketMatch(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgSocketMatch::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgSocketMatch)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgSocketMatch::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgSocketMatch)
	DDX_Control(pDX, IDC_TAB_SOCKETVISION, m_tabSocketCCD);
	DDX_Control(pDX, IDCANCEL, m_btnCancel);
	DDX_Control(pDX, IDOK, m_btnOK);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgSocketMatch, CDialog)
	//{{AFX_MSG_MAP(CDlgSocketMatch)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_SOCKETVISION, OnSelchangeTabSocketvision)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgSocketMatch message handlers

void CDlgSocketMatch::OnCancel() 
{
	
	CDialog::OnCancel();
}

void CDlgSocketMatch::OnOK() 
{
	
	CDialog::OnOK();
}

BOOL CDlgSocketMatch::PreTranslateMessage(MSG* pMsg) 
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

BOOL CDlgSocketMatch::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// init button 
	m_btnOK.SetIcon(IDI_OK);

	m_btnOK.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnOK.SetFlat(FALSE);

	m_btnCancel.SetIcon(IDI_CANCEL);;
	m_btnCancel.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnCancel.SetFlat(FALSE);
	
	InitTabControl();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgSocketMatch::InitTabControl()
{
	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	CRect ir,cr;
	m_tabSocketCCD.GetItemRect(0, &ir);
	m_tabSocketCCD.GetClientRect(&cr);

	// Create Object
	DlgPage.m_DlgSocketSetting.Create(CDlgSocketVisionCtrlSetting	::IDD,&m_tabSocketCCD);
	DlgPage.m_DlgSocketSetting.SetWindowPos(NULL, ir.left, ir.bottom, cr.right, cr.bottom-5, SWP_NOZORDER);
	DlgPage.m_DlgSocketSetting.ShowWindow(SW_SHOW);

	DlgPage.m_DlgSocketLive.Create(CDlgSocketVisionCtrlLive::IDD, &m_tabSocketCCD);
	DlgPage.m_DlgSocketLive.SetWindowPos(NULL, ir.left, ir.bottom, cr.right, cr.bottom-5, SWP_NOZORDER);
	DlgPage.m_DlgSocketLive.ShowWindow(SW_HIDE);

	//
	int iCount = 0;
	m_tabSocketCCD.InsertItem(TCIF_TEXT | TCIF_PARAM, 0, "Setting", -1, (LPARAM)&DlgPage.m_DlgSocketSetting);
	m_tabSocketCCD.InsertItem(TCIF_TEXT | TCIF_PARAM, 1, "Live", 	 -1, (LPARAM)&DlgPage.m_DlgSocketLive);

	//
	m_tabSocketCCD.SetCurSel(0);	

	//
	DlgPage.m_Page.mask = TCIF_PARAM;
	m_tabSocketCCD.GetItem(m_tabSocketCCD.GetCurSel(), &DlgPage.m_Page);

 	//將目前作用選擇視窗顯示
 	((CDialog *)(DlgPage.m_Page.lParam))->ShowWindow(SW_SHOW);
}

void CDlgSocketMatch::OnSelchangeTabSocketvision(NMHDR* pNMHDR, LRESULT* pResult) 
{
	//套用CMember->Page成員
	((CDialog *)(DlgPage.m_Page.lParam))->ShowWindow(SW_HIDE); //將目前點畫面隱藏
	DlgPage.m_Page.mask = TCIF_PARAM;
	m_tabSocketCCD.GetItem(m_tabSocketCCD.GetCurSel(), &DlgPage.m_Page);//將目前點選畫面參數儲存
	((CDialog *)(DlgPage.m_Page.lParam))->ShowWindow(SW_SHOW);//將目前點選畫面顯示
	
	*pResult = 0;
}
