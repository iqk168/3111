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
	DDX_Control(pDX, IDC_TAB_SOCKETVISION,		m_tabSocketVision);
	DDX_Control(pDX, IDCANCEL,					m_btnCancel);
	DDX_Control(pDX, IDOK,						m_btnOK);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgSocketMatch, CDialog)
	//{{AFX_MSG_MAP(CDlgSocketMatch)
	ON_WM_TIMER()
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_SOCKETVISION, OnSelchangeTabSocketvision)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgSocketMatch message handlers

void CDlgSocketMatch::OnOK() 
{
	//
	ExitPage();

	m.Info.bSubDlgOpen = false;
	f.UpdateButtonState();	

	CDialog::OnOK();
}

void CDlgSocketMatch::OnCancel() 
{
	//
	ExitPage();

	m.Info.bSubDlgOpen = false;
	f.UpdateButtonState();
	
	CDialog::OnCancel();
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
	
	m.Info.bSubDlgOpen = true;
	f.UpdateButtonState();

	// init button 
	m_btnOK.SetIcon(IDI_OK);
	m_btnOK.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnOK.SetFlat(FALSE);

	m_btnCancel.SetIcon(IDI_CANCEL);;
	m_btnCancel.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnCancel.SetFlat(FALSE);

	//
	InitTabControl();
	
	//
	InitValue();
//	Jerome Add 20140704 : 在此載入目前所使用的CCD編號
//	m.m_VisionMatch.m_iCameraUseID = m.m_CCDSocketControl.iCCDUse;

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
	m_tabSocketVision.GetItemRect(0, &ir);
	m_tabSocketVision.GetClientRect(&cr);

	// Create Object
	DlgPage.m_DlgSocketMatch.Create(CDlgSocketVisionSetting::IDD,&m_tabSocketVision);
	DlgPage.m_DlgSocketMatch.SetWindowPos(NULL, ir.left, ir.bottom, cr.right, cr.bottom-5, SWP_NOZORDER);
	DlgPage.m_DlgSocketMatch.ShowWindow(SW_SHOW);

	DlgPage.m_DlgLive.Create(CDlgSocketVisionLive::IDD, &m_tabSocketVision);
	DlgPage.m_DlgLive.SetWindowPos(NULL, ir.left, ir.bottom, cr.right, cr.bottom-5, SWP_NOZORDER);
	DlgPage.m_DlgLive.ShowWindow(SW_HIDE);

	//
	m_tabSocketVision.InsertItem(TCIF_TEXT | TCIF_PARAM, 0, "Live", 	-1, (LPARAM)&DlgPage.m_DlgLive);
	m_tabSocketVision.InsertItem(TCIF_TEXT | TCIF_PARAM, 0, "Socket",	-1, (LPARAM)&DlgPage.m_DlgSocketMatch);

	//
	m_tabSocketVision.SetCurSel(0);	

	//
	DlgPage.m_Page.mask = TCIF_PARAM;
	m_tabSocketVision.GetItem(m_tabSocketVision.GetCurSel(), &DlgPage.m_Page);

 	//將目前作用選擇視窗顯示
 	((CDialog *)(DlgPage.m_Page.lParam))->ShowWindow(SW_SHOW);
}
void CDlgSocketMatch::InitValue()
{

}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CDlgSocketMatch::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CDlgSocketMatch::OnTimer(UINT nIDEvent) 
{
	
	CDialog::OnTimer(nIDEvent);
}
void CDlgSocketMatch::ExitPage()
{
	DlgPage.m_DlgLive.ClosePage();
}
void CDlgSocketMatch::ChangeTab()
{
	// 切換畫面..
	int iItem = m_tabSocketVision.GetCurSel();

	if(	iItem == 0 )
	{
		// Live to Socket
		DlgPage.m_DlgLive.ChangePage();
	}
	else if( iItem == 1 )
	{
		// Socket to Live
	}
}
void CDlgSocketMatch::OnSelchangeTabSocketvision(NMHDR* pNMHDR, LRESULT* pResult) 
{
	//套用CMember->Page成員
	((CDialog *)(DlgPage.m_Page.lParam))->ShowWindow(SW_HIDE); //將目前點畫面隱藏
	DlgPage.m_Page.mask = TCIF_PARAM;
	m_tabSocketVision.GetItem(m_tabSocketVision.GetCurSel(), &DlgPage.m_Page);//將目前點選畫面參數儲存
	((CDialog *)(DlgPage.m_Page.lParam))->ShowWindow(SW_SHOW);//將目前點選畫面顯示

	//
	ChangeTab();
	
	*pResult = 0;
}

void CDlgSocketMatch::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}
