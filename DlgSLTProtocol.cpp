// DlgSLTProtocol.cpp : implementation file
//

#include "stdafx.h"
#include "deer.h"
#include "DlgSLTProtocol.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgSLTProtocol dialog


CDlgSLTProtocol::CDlgSLTProtocol(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgSLTProtocol::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgSLTProtocol)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgSLTProtocol::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgSLTProtocol)
	DDX_Control(pDX, IDC_TAB_SLT,	m_tabSLT);
	DDX_Control(pDX, IDCANCEL,		m_btnCancel);
	DDX_Control(pDX, IDOK,			m_btnOK);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgSLTProtocol, CDialog)
	//{{AFX_MSG_MAP(CDlgSLTProtocol)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_SLT, OnSelchangeTabSlt)
	ON_MESSAGE(WM_SLT_PROTOCOL_MSG,		  OnSLTRecvRaw )

	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgSLTProtocol message handlers

BOOL CDlgSLTProtocol::PreTranslateMessage(MSG* pMsg) 
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

BOOL CDlgSLTProtocol::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m.Info.bSubDlgOpen = true;
	f.UpdateButtonState();

	// init button 
	m_btnOK.SetIcon(IDI_OK);
	m_btnOK.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnOK.SetFlat(FALSE);
	
	m_btnCancel.SetIcon(IDI_CANCEL);
	m_btnCancel.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnCancel.SetFlat(FALSE);
	
	//
	InitSLTPage();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
void CDlgSLTProtocol::InitSLTPage()
{
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	CRect ir,cr;
	m_tabSLT.GetItemRect(0, &ir);
	m_tabSLT.GetClientRect(&cr);

	// Create Object
	DlgPage.m_DlgSLTProtocolSetting.Create(CDlgSLTProtocolSetting::IDD,&m_tabSLT);
	DlgPage.m_DlgSLTProtocolSetting.SetWindowPos(NULL, ir.left, ir.bottom, cr.right, cr.bottom-5, SWP_NOZORDER);
	DlgPage.m_DlgSLTProtocolSetting.ShowWindow(SW_SHOW);

	DlgPage.m_DlgSLTProtocolMonitor.Create(CDlgSLTProtocolMonitor::IDD, &m_tabSLT);
	DlgPage.m_DlgSLTProtocolMonitor.SetWindowPos(NULL, ir.left, ir.bottom, cr.right, cr.bottom-5, SWP_NOZORDER);
	DlgPage.m_DlgSLTProtocolMonitor.ShowWindow(SW_HIDE);

	DlgPage.m_DlgSLTProtocolHelp.Create(CDlgSLTProtocolHelp::IDD, &m_tabSLT);
	DlgPage.m_DlgSLTProtocolHelp.SetWindowPos(NULL, ir.left, ir.bottom, cr.right, cr.bottom-5, SWP_NOZORDER);
	DlgPage.m_DlgSLTProtocolHelp.ShowWindow(SW_HIDE);

	bool bHelpReady = f.GetSLTProtocolHelp();

	/////
	//
	int iCount = 0;
	m_tabSLT.InsertItem(TCIF_TEXT | TCIF_PARAM, iCount, "Setting",	iCount, (LPARAM)&DlgPage.m_DlgSLTProtocolSetting);
	iCount++;
	m_tabSLT.InsertItem(TCIF_TEXT | TCIF_PARAM, iCount, "Monitor",	iCount, (LPARAM)&DlgPage.m_DlgSLTProtocolMonitor);
	iCount++;
	if( bHelpReady )
		m_tabSLT.InsertItem(TCIF_TEXT | TCIF_PARAM, iCount, "Help",	iCount, (LPARAM)&DlgPage.m_DlgSLTProtocolHelp);

	//
	m_tabSLT.SetCurSel(0);	

	//
	DlgPage.m_Page.mask = TCIF_PARAM;
	m_tabSLT.GetItem(m_tabSLT.GetCurSel(), &DlgPage.m_Page);

 	//將目前作用選擇視窗顯示
 	((CDialog *)(DlgPage.m_Page.lParam))->ShowWindow(SW_SHOW);
}
LRESULT CDlgSLTProtocol::OnSLTRecvRaw(WPARAM p, LPARAM l)
{
	CString *pp = (CString *)p;	
	CString csMsg = _T("");

	// Time
	CTime time = CTime::GetCurrentTime();
	CString cstime = _T("");
	SYSTEMTIME ti; 
	GetLocalTime(&ti);
	cstime.Format("%.2d/%.2d/%.2d:%.2d", 
		ti.wMonth, ti.wDay, ti.wHour, ti.wMinute, ti.wSecond );

	// Msg
	csMsg.Format("%s %s", cstime, *pp);
	DlgPage.m_DlgSLTProtocolMonitor.InsertLogRaw( csMsg );

	return true;
}
void CDlgSLTProtocol::OnOK() 
{
	m.Info.bSubDlgOpen = false;
	f.UpdateButtonState();
	
	CDialog::OnOK();
}

void CDlgSLTProtocol::OnCancel() 
{
	m.Info.bSubDlgOpen = false;
	f.UpdateButtonState();
	
	CDialog::OnCancel();
}

void CDlgSLTProtocol::OnSelchangeTabSlt(NMHDR* pNMHDR, LRESULT* pResult) 
{
	//套用CMember->Page成員
	((CDialog *)(DlgPage.m_Page.lParam))->ShowWindow(SW_HIDE); //將目前點畫面隱藏
	DlgPage.m_Page.mask = TCIF_PARAM;
	m_tabSLT.GetItem(m_tabSLT.GetCurSel(), &DlgPage.m_Page);//將目前點選畫面參數儲存
	((CDialog *)(DlgPage.m_Page.lParam))->ShowWindow(SW_SHOW);//將目前點選畫面顯示
	
	*pResult = 0;
}
