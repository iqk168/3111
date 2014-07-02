// DlgRemoteCommunication.cpp : implementation file
//

#include "stdafx.h"
#include "deer.h"
#include "DlgRemoteCommunication.h"
#include "DlgRemoteCommMsg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgRemoteCommunication dialog


CDlgRemoteCommunication::CDlgRemoteCommunication(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgRemoteCommunication::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgRemoteCommunication)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgRemoteCommunication::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgRemoteCommunication)
	DDX_Control(pDX, IDC_TAB_REMOTE,	m_tabRemote);
	DDX_Control(pDX, IDOK,				m_btnOK);
	DDX_Control(pDX, IDCANCEL,			m_btnCancel);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgRemoteCommunication, CDialog)
	//{{AFX_MSG_MAP(CDlgRemoteCommunication)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_REMOTE, OnSelchangeTabRemote)
	ON_MESSAGE( WM_REMOTE_RECV,				 OnRemoteRecv )
	ON_MESSAGE( WM_REMOTE_RECV_RAW,			 OnRemoteRecvRaw )
	ON_MESSAGE( WM_REMOTE_SEND,				 OnRemoteSend )

	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgRemoteCommunication message handlers

void CDlgRemoteCommunication::OnOK() 
{
	
	CDialog::OnOK();
}

void CDlgRemoteCommunication::OnCancel() 
{
	
	CDialog::OnCancel();
}

BOOL CDlgRemoteCommunication::PreTranslateMessage(MSG* pMsg) 
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

BOOL CDlgRemoteCommunication::OnInitDialog() 
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
	InitTabControl();

	//
	CenterWindow();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgRemoteCommunication::InitTabControl()
{
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	CRect ir,cr;
	m_tabRemote.GetItemRect(0, &ir);
	m_tabRemote.GetClientRect(&cr);

	// Create Object
	DlgPage.m_DlgRemoteMonitor.Create(CDlgRemoteCommMonitor::IDD,&m_tabRemote);
	DlgPage.m_DlgRemoteMonitor.SetWindowPos(NULL, ir.left, ir.bottom, cr.right, cr.bottom-5, SWP_NOZORDER);
	DlgPage.m_DlgRemoteMonitor.ShowWindow(SW_SHOW);

	DlgPage.m_DlgRemoteMsg.Create(CDlgRemoteCommMsg::IDD, &m_tabRemote);
	DlgPage.m_DlgRemoteMsg.SetWindowPos(NULL, ir.left, ir.bottom, cr.right, cr.bottom-5, SWP_NOZORDER);
	DlgPage.m_DlgRemoteMsg.ShowWindow(SW_HIDE);

	DlgPage.m_DlgRemoteMsgLot.Create(CDlgRemoteCommMsgLot::IDD, &m_tabRemote);
	DlgPage.m_DlgRemoteMsgLot.SetWindowPos(NULL, ir.left, ir.bottom, cr.right, cr.bottom-5, SWP_NOZORDER);
	DlgPage.m_DlgRemoteMsgLot.ShowWindow(SW_HIDE);

	/////
	//
	int iCount = 0;
	m_tabRemote.InsertItem(TCIF_TEXT | TCIF_PARAM, iCount, "Remote Monitor", iCount, (LPARAM)&DlgPage.m_DlgRemoteMonitor);
	iCount++;
	m_tabRemote.InsertItem(TCIF_TEXT | TCIF_PARAM, iCount, "Remote Msg",	 iCount, (LPARAM)&DlgPage.m_DlgRemoteMsg);
	iCount++;
	m_tabRemote.InsertItem(TCIF_TEXT | TCIF_PARAM, iCount, "Remote Msg Lot", iCount, (LPARAM)&DlgPage.m_DlgRemoteMsgLot);

	//
	m_tabRemote.SetCurSel(0);	

	//
	DlgPage.m_Page.mask = TCIF_PARAM;
	m_tabRemote.GetItem(m_tabRemote.GetCurSel(), &DlgPage.m_Page);

 	//將目前作用選擇視窗顯示
 	((CDialog *)(DlgPage.m_Page.lParam))->ShowWindow(SW_SHOW);
}

void CDlgRemoteCommunication::OnSelchangeTabRemote(NMHDR* pNMHDR, LRESULT* pResult) 
{
	//套用CMember->Page成員
	((CDialog *)(DlgPage.m_Page.lParam))->ShowWindow(SW_HIDE); //將目前點畫面隱藏
	DlgPage.m_Page.mask = TCIF_PARAM;
	m_tabRemote.GetItem(m_tabRemote.GetCurSel(), &DlgPage.m_Page);//將目前點選畫面參數儲存
	((CDialog *)(DlgPage.m_Page.lParam))->ShowWindow(SW_SHOW);//將目前點選畫面顯示
	
	*pResult = 0;
}
LRESULT CDlgRemoteCommunication::OnRemoteSend(WPARAM p, LPARAM l)
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
	csMsg.Format("%s %s %s", cstime, _R_SEND, *pp);
	DlgPage.m_DlgRemoteMonitor.InsertLogCmd( csMsg );

	return true;
}
LRESULT CDlgRemoteCommunication::OnRemoteRecvRaw(WPARAM p, LPARAM l)
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
	DlgPage.m_DlgRemoteMonitor.InsertLogRaw( csMsg );

	return true;
}
LRESULT CDlgRemoteCommunication::OnRemoteRecv(WPARAM p, LPARAM l)
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
	csMsg.Format("%s %s %s", cstime, _R_REV, *pp);
	DlgPage.m_DlgRemoteMonitor.InsertLogCmd( csMsg );
	
	return true;
}
