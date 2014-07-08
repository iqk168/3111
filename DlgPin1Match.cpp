// DlgPin1Match.cpp : implementation file
//

#include "stdafx.h"
#include "deer.h"
#include "DlgPin1Match.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgPin1Match dialog


CDlgPin1Match::CDlgPin1Match(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgPin1Match::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgPin1Match)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgPin1Match::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgPin1Match)
	DDX_Control(pDX, IDC_TAB_SOCKETVISION,		m_tabSocketVision);
	DDX_Control(pDX, IDCANCEL,					m_btnCancel);
	DDX_Control(pDX, IDOK,						m_btnOK);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgPin1Match, CDialog)
	//{{AFX_MSG_MAP(CDlgPin1Match)
	ON_WM_TIMER()
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_SOCKETVISION, OnSelchangeTabSocketvision)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgPin1Match message handlers

void CDlgPin1Match::OnOK() 
{
	//
	ExitPage();

	m.Info.bSubDlgOpen = false;
	f.UpdateButtonState();	

	CDialog::OnOK();
}

void CDlgPin1Match::OnCancel() 
{
	//
	ExitPage();

	m.Info.bSubDlgOpen = false;
	f.UpdateButtonState();
	
	CDialog::OnCancel();
}

BOOL CDlgPin1Match::PreTranslateMessage(MSG* pMsg) 
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

BOOL CDlgPin1Match::OnInitDialog() 
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
//Jerome Add 20140704 : 在此載入目前所使用的CCD編號
//	m.m_VisionMatch.m_iCameraUseID = m.m_CCDPin1Control.iCCDUse;
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
void CDlgPin1Match::InitTabControl()
{
	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	CRect ir,cr;
	m_tabSocketVision.GetItemRect(0, &ir);
	m_tabSocketVision.GetClientRect(&cr);

	// Create Object
	DlgPage.m_DlgPin1Match.Create(CDlgPin1VisionSetting::IDD,&m_tabSocketVision);
	DlgPage.m_DlgPin1Match.SetWindowPos(NULL, ir.left, ir.bottom, cr.right, cr.bottom-5, SWP_NOZORDER);
	DlgPage.m_DlgPin1Match.ShowWindow(SW_SHOW);

	DlgPage.m_DlgLive.Create(CDlgPin1VisionLive::IDD, &m_tabSocketVision);
	DlgPage.m_DlgLive.SetWindowPos(NULL, ir.left, ir.bottom, cr.right, cr.bottom-5, SWP_NOZORDER);
	DlgPage.m_DlgLive.ShowWindow(SW_HIDE);

	//
	m_tabSocketVision.InsertItem(TCIF_TEXT | TCIF_PARAM, 0, "Live", 	-1, (LPARAM)&DlgPage.m_DlgLive);
	m_tabSocketVision.InsertItem(TCIF_TEXT | TCIF_PARAM, 0, "Socket",	-1, (LPARAM)&DlgPage.m_DlgPin1Match);

	//
	m_tabSocketVision.SetCurSel(0);	

	//
	DlgPage.m_Page.mask = TCIF_PARAM;
	m_tabSocketVision.GetItem(m_tabSocketVision.GetCurSel(), &DlgPage.m_Page);

 	//將目前作用選擇視窗顯示
 	((CDialog *)(DlgPage.m_Page.lParam))->ShowWindow(SW_SHOW);
}
void CDlgPin1Match::InitValue()
{

}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CDlgPin1Match::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CDlgPin1Match::OnTimer(UINT nIDEvent) 
{
	
	CDialog::OnTimer(nIDEvent);
}
void CDlgPin1Match::ExitPage()
{
	DlgPage.m_DlgLive.ClosePage();
}
void CDlgPin1Match::ChangeTab()
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
void CDlgPin1Match::OnSelchangeTabSocketvision(NMHDR* pNMHDR, LRESULT* pResult) 
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

void CDlgPin1Match::OnPaint() 
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
