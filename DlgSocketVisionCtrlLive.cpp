// DlgSocketVisionCtrlLive.cpp : implementation file
//

#include "stdafx.h"
#include "deer.h"
#include "DlgSocketVisionCtrlLive.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgSocketVisionCtrlLive dialog


CDlgSocketVisionCtrlLive::CDlgSocketVisionCtrlLive(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgSocketVisionCtrlLive::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgSocketVisionCtrlLive)
	//}}AFX_DATA_INIT
}


void CDlgSocketVisionCtrlLive::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgSocketVisionCtrlLive)
	DDX_Control(pDX, IDC_SOCKETLIVE_LIST, m_CBList);
	DDX_Control(pDX, IDC_SOCKETLIVE_LIVE, m_btnLive);
	DDX_Control(pDX, IDC_SOCKETLIVE_GRAB, m_btnGrab);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgSocketVisionCtrlLive, CDialog)
	//{{AFX_MSG_MAP(CDlgSocketVisionCtrlLive)
	ON_WM_SHOWWINDOW()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_SOCKETLIVE_LIVE, OnSocketliveLive)
	ON_BN_CLICKED(IDC_SOCKETLIVE_GRAB, OnSocketliveGrab)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgSocketVisionCtrlLive message handlers

BOOL CDlgSocketVisionCtrlLive::PreTranslateMessage(MSG* pMsg) 
{
	// Tips
	m_ToolTip.RelayEvent(pMsg);

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

BOOL CDlgSocketVisionCtrlLive::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// init button 
	m_btnGrab.SetIcon(IDI_SOCCCD_GRAB);
	m_btnGrab.SetAlign(CButtonST::ST_ALIGN_VERT);

	m_btnLive.SetIcon(IDI_SOCCCD_LIVE);
	m_btnLive.SetAlign(CButtonST::ST_ALIGN_VERT);

	//
	// Updata CCD Camera List.
	UpdateCameraControlList();

	//
	InitValue();

	//
	InitTips();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
void CDlgSocketVisionCtrlLive::InitValue()
{

}
void CDlgSocketVisionCtrlLive::UpdateCameraControlList()
{
	CArray <CString, CString> m_DeviceList;
	m_DeviceList.RemoveAll();
	m.m_Vision.GetCameraList( m_DeviceList );

	int iSize = m_DeviceList.GetSize();
	for(int i=0;i<iSize;i++)
	{
		CString cs;
		cs.Format("%s", m_DeviceList.GetAt(i) );
		m_CBList.AddString( cs );
	}

	m_CBList.SetCurSel( m.m_CCDSocketControl.iCCDUse );
}

void CDlgSocketVisionCtrlLive::InitTips()
{
	// Tips // Init Tips
	m_ToolTip.Create(this);
	m_ToolTip.SetMaxTipWidth(800);
	m_ToolTip.SetDelayTime( TTDT_AUTOPOP, 10000 );
	m_ToolTip.SetDelayTime( TTDT_INITIAL, 25 );
	m_ToolTip.EnableToolTips(true);

	m_ToolTip.AddTool( GetDlgItem(IDC_SOCKETLIVE_GRAB),			_T("Grab Image") );
	m_ToolTip.AddTool( GetDlgItem(IDC_SOCKETLIVE_LIVE),			_T("Live / Stop Live") );

}
void CDlgSocketVisionCtrlLive::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);
	
	// TODO: Add your message handler code here
	
}

void CDlgSocketVisionCtrlLive::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	
	CDialog::OnTimer(nIDEvent);
}
DWORD CDlgSocketVisionCtrlLive::WorkerThreadGrab(void* pVoid)
{
	CDlgSocketVisionCtrlLive* pThis = (CDlgSocketVisionCtrlLive*)pVoid;

	CDC* pDC = pThis->GetDlgItem(IDC_SOCKETLIVE_WINDOW)->GetDC();
	HDC hDC = pDC->GetSafeHdc();

	CRect rect;
	pThis->GetDlgItem(IDC_SOCKETLIVE_WINDOW)->GetClientRect(&rect);
/*
		if( m.m_Vision.CameraGrab( m.m_CCDPin1Control.iCCDUse ) )
		{
			m.m_Vision.Draw(hDC, rect, &m.m_Vision.m_CaptureFrame[m.m_CCDPin1Control.iCCDUse] );
		}
*/
	while( m.m_Vision.m_bCameraLive )
	{
		if(m.m_Vision.CameraGrab(m.m_CCDSocketControl.iCCDUse) )
		{	
			m.m_Vision.Draw(hDC,rect, &m.m_Vision.m_CaptureFrame[m.m_CCDSocketControl.iCCDUse] );	
		}
		else
			break;
		Sleep(1);
	}

	return 0;
}
void CDlgSocketVisionCtrlLive::CameraLive()
{
	// 啟動 Live
	LiveLockUI( true );
	m.m_Vision.m_bCameraLive = true;
	CreateThread(NULL, NULL, WorkerThreadGrab, this, FALSE, 
		&m_dwThreadIdSocketCamera);	
}
void CDlgSocketVisionCtrlLive::CameraStop()
{
	// 已經在 Live 現在要關掉 Live
	m.m_Vision.m_bCameraLive = false;	

	LiveLockUI( false );
}
void CDlgSocketVisionCtrlLive::LiveLockUI(bool bEnable)
{
	if( bEnable )
	{
		m_btnLive.SetIcon( IDI_SOCCCD_STOP );
		m_btnLive.EnableWindow( TRUE );
		m_btnGrab.EnableWindow( FALSE );
	}
	else
	{
		m_btnLive.SetIcon( IDI_SOCCCD_LIVE );
		m_btnLive.EnableWindow( TRUE );
		m_btnGrab.EnableWindow( TRUE );	
	}
}
void CDlgSocketVisionCtrlLive::OnSocketliveLive() 
{
	if( !m.m_Vision.m_bCameraLive )
	{
		// Start Live
		CameraLive();
	}
	else
	{
		// Stop Live
		CameraStop();
	}
}
void CDlgSocketVisionCtrlLive::CameraCapture()
{
	CDC* pDC = GetDlgItem(IDC_SOCKETLIVE_WINDOW)->GetDC();
	HDC hDC = pDC->GetSafeHdc();

	CRect rect;
	GetDlgItem(IDC_SOCKETLIVE_WINDOW)->GetClientRect(&rect);
	if(m.m_Vision.CameraGrab(m.m_CCDSocketControl.iCCDUse) )
	{
		m.m_Vision.Draw(hDC,rect, &m.m_Vision.m_CaptureFrame[m.m_CCDSocketControl.iCCDUse] );	
	}
	else
	{
		// Grab Error
		CString csMsg = _T("");
		csMsg.Format("Grab Fail");
		AfxMessageBox( csMsg );
	}
}
void CDlgSocketVisionCtrlLive::CaptureLockUI(bool bEnable)
{
	if( bEnable )
	{
		m_btnLive.EnableWindow( FALSE );
		m_btnGrab.EnableWindow( FALSE );
	}
	else
	{
		m_btnLive.EnableWindow( TRUE );
		m_btnGrab.EnableWindow( TRUE );
	}
}
void CDlgSocketVisionCtrlLive::OnSocketliveGrab() 
{
	CaptureLockUI( true );
	CameraCapture();
	CaptureLockUI( false );
}
