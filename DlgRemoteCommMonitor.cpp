// DlgRemoteCommMonitor.cpp : implementation file
//

#include "stdafx.h"
#include "deer.h"
#include "DlgRemoteCommMonitor.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgRemoteCommMonitor dialog

CDlgRemoteCommMonitor::CDlgRemoteCommMonitor(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgRemoteCommMonitor::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgRemoteCommMonitor)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_lMonitorDataCount = 0;
}


void CDlgRemoteCommMonitor::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgRemoteCommMonitor)
	DDX_Control(pDX, IDC_LIST_LOG_RAW,	m_wndLogRaw);
	DDX_Control(pDX, IDC_LIST_LOG_CMD,	m_wndLogCmd);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgRemoteCommMonitor, CDialog)
	//{{AFX_MSG_MAP(CDlgRemoteCommMonitor)
	ON_BN_CLICKED(IDC_E_CLEAR_RAW_LOG,	OnEClearRawLog)
	ON_BN_CLICKED(IDC_E_CLEAR_LOG,		OnEClearLog)
	ON_BN_CLICKED(IDC_E_DEL_RAW_LOG,	OnEDelRawLog)
	ON_BN_CLICKED(IDC_E_DEL_LOG,		OnEDelLog)
	ON_LBN_SELCHANGE(IDC_LIST_LOG_CMD,	OnSelchangeListLogCmd)
	ON_LBN_DBLCLK(IDC_LIST_LOG_CMD,		OnDblclkListLogCmd)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgRemoteCommMonitor message handlers

BOOL CDlgRemoteCommMonitor::PreTranslateMessage(MSG* pMsg) 
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
void CDlgRemoteCommMonitor::InsertLogRaw(CString csLog)
{
	csLog.TrimLeft();
	csLog.TrimRight();

	if( csLog != "" )
	{
		CString csMsg = _T("");
		CTime time = CTime::GetCurrentTime();
		csMsg.Format("%.2d,%.2d, %.2d:%.2d:%.2d,  %s", 
			time.GetMonth(), time.GetDay(), time.GetHour(), time.GetMinute(), time.GetSecond(), csLog );
		
//		m_wndLogRaw.InsertString(0, csLog );
		m_wndLogRaw.AddString(csLog);
	}
}
void CDlgRemoteCommMonitor::InsertLogCmd(CString csLog)
{
	csLog.TrimLeft();
	csLog.TrimRight();

	if( csLog != "" )
	{
		m_lMonitorDataCount++;
		CString csInsertLog = _T("");
		csInsertLog.Format("%.4d, %s", m_lMonitorDataCount, csLog );

		CString csMsg = _T("");
		m_wndLogCmd.AddString(csInsertLog);
	}
}
BOOL CDlgRemoteCommMonitor::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgRemoteCommMonitor::OnEClearRawLog() 
{
	m_wndLogRaw.ResetContent();
}

void CDlgRemoteCommMonitor::OnEClearLog() 
{
	m_wndLogCmd.ResetContent();
}
void CDlgRemoteCommMonitor::DeleteLog(CString csFileName )
{
	CString csPath = m.m_TestInterface.GetLogPath();
	CString csFile = _T("");
	csFile = csPath + csFileName;
	::DeleteFile( csFile );
}
void CDlgRemoteCommMonitor::OnEDelRawLog() 
{
	DeleteLog( _RemoteRawLog );
}

void CDlgRemoteCommMonitor::OnEDelLog() 
{
	DeleteLog( _RemoteLog );
}

void CDlgRemoteCommMonitor::OnSelchangeListLogCmd() 
{
	return;
	int iSel = m_wndLogCmd.GetCurSel();
	if( iSel > 0 )
	{
		CString csMsg = _T("");
		m_wndLogCmd.GetText(iSel, csMsg );
		AfxMessageBox( csMsg );
	}
}

void CDlgRemoteCommMonitor::OnDblclkListLogCmd() 
{
	int iSel = m_wndLogCmd.GetCurSel();
	if( iSel > 0 )
	{
		CString csMsg = _T("");
		m_wndLogCmd.GetText(iSel, csMsg );
		AfxMessageBox( csMsg );
	}	
}
