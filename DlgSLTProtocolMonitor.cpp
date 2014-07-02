// DlgSLTProtocolMonitor.cpp : implementation file
//

#include "stdafx.h"
#include "deer.h"
#include "DlgSLTProtocolMonitor.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgSLTProtocolMonitor dialog


CDlgSLTProtocolMonitor::CDlgSLTProtocolMonitor(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgSLTProtocolMonitor::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgSLTProtocolMonitor)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgSLTProtocolMonitor::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgSLTProtocolMonitor)
	DDX_Control(pDX, IDC_LIST_LOG_RAW, m_listRaw);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgSLTProtocolMonitor, CDialog)
	//{{AFX_MSG_MAP(CDlgSLTProtocolMonitor)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgSLTProtocolMonitor message handlers

BOOL CDlgSLTProtocolMonitor::PreTranslateMessage(MSG* pMsg) 
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

BOOL CDlgSLTProtocolMonitor::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	InitValue();

	InitUI();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
void CDlgSLTProtocolMonitor::InsertLogRaw(CString csLog)
{
	csLog.TrimLeft();
	csLog.TrimRight();

	if( csLog != "" )
	{
		CString csMsg = _T("");
		CTime time = CTime::GetCurrentTime();
		csMsg.Format("%.2d,%.2d, %.2d:%.2d:%.2d,  %s", 
			time.GetMonth(), time.GetDay(), time.GetHour(), time.GetMinute(), time.GetSecond(), csLog );
		
		m_listRaw.AddString(csLog);
	}
}
void CDlgSLTProtocolMonitor::InitValue()
{

}
void CDlgSLTProtocolMonitor::InitUI()
{

}