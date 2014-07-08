// DlgSocketVisionLive.cpp : implementation file
//

#include "stdafx.h"
#include "deer.h"
#include "DlgSocketVisionLive.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgSocketVisionLive dialog


CDlgSocketVisionLive::CDlgSocketVisionLive(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgSocketVisionLive::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgSocketVisionLive)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgSocketVisionLive::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgSocketVisionLive)
	DDX_Control(pDX, IDC_SOCKETLIVE_GRAB, m_BtnGrab);
	DDX_Control(pDX, IDC_SOCKETLIVE_LIVE, m_BtnLive);
	DDX_Control(pDX, IDC_SOCKETLIVE_LIST, m_CBList);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgSocketVisionLive, CDialog)
	//{{AFX_MSG_MAP(CDlgSocketVisionLive)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_SOCKETLIVE_LIVE,	OnSocketliveLive)
	ON_BN_CLICKED(IDC_SOCKETLIVE_GRAB,	OnSocketliveGrab)
	ON_BN_CLICKED(IDC_OPERATE,			OnOperate)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgSocketVisionLive message handlers

BOOL CDlgSocketVisionLive::PreTranslateMessage(MSG* pMsg) 
{
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

BOOL CDlgSocketVisionLive::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// init button 
	m_BtnGrab.SetIcon(IDI_SOCCCD_GRAB);
	m_BtnGrab.SetAlign(CButtonST::ST_ALIGN_VERT);

	m_BtnLive.SetIcon(IDI_SOCCCD_LIVE);
	m_BtnLive.SetAlign(CButtonST::ST_ALIGN_VERT);

	//
	InitTips();

	// Updata CCD Camera List.
	UpdateCameraControlList();

	//
	InitValue();

	//
	InitDefault(); // shouble be after UpdateCameraControlList

	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
//
void CDlgSocketVisionLive::UpdateCameraControlList()
{
	CArray <CString, CString> m_DeviceList;
	m_DeviceList.RemoveAll();
	m.m_VisionMatch.GetCameraList( m_DeviceList );

	int iSize = m_DeviceList.GetSize();
	for(int i=0;i<iSize;i++)
	{
		CString cs;
		cs.Format("%s", m_DeviceList.GetAt(i) );
		m_CBList.AddString( cs );
	}
}
//
void CDlgSocketVisionLive::InitDefault()
{
	m_CBList.SetCurSel(0);
}
void CDlgSocketVisionLive::InitValue()
{

}

void CDlgSocketVisionLive::InitTips()
{
	// Init Tips
	m_ToolTip.Create(this);
	m_ToolTip.SetDelayTime( TTDT_AUTOPOP, 10000 );
	m_ToolTip.SetDelayTime( TTDT_INITIAL, 25 );
	m_ToolTip.EnableToolTips(true);

	m_ToolTip.AddTool( GetDlgItem(IDC_SOCKETLIVE_GRAB),	_T("Get one image frame") );
	m_ToolTip.AddTool( GetDlgItem(IDC_SOCKETLIVE_LIVE),	_T("Continue to get image frame") );

}
void CDlgSocketVisionLive::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	
	CDialog::OnTimer(nIDEvent);
}

// Thread
DWORD CDlgSocketVisionLive::WorkerThreadGrab(void* pVoid)
{
	CDlgSocketVisionLive* pThis = (CDlgSocketVisionLive*)pVoid;

	while( m.m_VisionMatch.m_bCameraLive )
	{
// 		m.m_VisionMatch.CameraGrab( m.m_VisionMatch.m_iCameraUseID );//
// 		m.m_VisionMatch.DrawWindow( m.m_VisionMatch.m_iCameraUseID,(LPVOID)pThis, IDC_SOCKETLIVE_WINDOW);//
//Jerome Add 20140707
		m.m_VisionMatch.CameraGrab( m.m_CCDSocketControl.iCCDUse );//
		m.m_VisionMatch.DrawWindow( m.m_CCDSocketControl.iCCDUse,(LPVOID)pThis, IDC_SOCKETLIVE_WINDOW);//
	
		Sleep(1);
	}
	return 0;
}

void CDlgSocketVisionLive::ChangePage()
{
	if( m.m_VisionMatch.m_bCameraLive )
	{
		m.m_VisionMatch.m_bCameraLive = false;
		Sleep(10);
		ButtonLive( false );
	}
}
void CDlgSocketVisionLive::ClosePage()
{
	if( m.m_VisionMatch.m_bCameraLive )
	{
		m.m_VisionMatch.m_bCameraLive = false;
		Sleep(10);
		ButtonLive( false );
	}
}
void CDlgSocketVisionLive::OnSocketliveLive() 
{
	if( m.m_VisionMatch.m_bCameraLive )
	{
		// 已經在 Live 現在要關掉 Live
		m.m_VisionMatch.m_bCameraLive = false;
		ButtonLive( false );
	}
	else
	{
		// 啟動 Live
		ButtonLive( true );
		m.m_VisionMatch.m_bCameraLive = true;
		CreateThread(NULL, NULL, WorkerThreadGrab, this, FALSE, 
			&m_dwThreadIdCamera);	
	}
}

void CDlgSocketVisionLive::OnSocketliveGrab() 
{
// 	m.m_VisionMatch.CameraGrab(m.m_VisionMatch.m_iCameraUseID);
// 	m.m_VisionMatch.DrawWindow(m.m_VisionMatch.m_iCameraUseID, (LPVOID)this, IDC_SOCKETLIVE_WINDOW );
//Jerome Add 20140707	
	m.m_VisionMatch.CameraGrab(m.m_CCDSocketControl.iCCDUse);
	m.m_VisionMatch.DrawWindow(m.m_CCDSocketControl.iCCDUse, (LPVOID)this, IDC_SOCKETLIVE_WINDOW );	
}

void CDlgSocketVisionLive::ButtonLive(bool bLive )
{
	BOOL bEnalbe = TRUE;
	if( bLive )
	{
		bEnalbe = TRUE;
		// set status to live
		m_BtnGrab.EnableWindow( !bEnalbe );
		m_BtnLive.EnableWindow( bEnalbe );

		m_BtnLive.SetIcon(IDI_SOCCCD_STOP);
	}
	else
	{
		bEnalbe = TRUE;
		// set status to close live.
		m_BtnGrab.EnableWindow( bEnalbe );
		m_BtnLive.EnableWindow( bEnalbe );

		m_BtnLive.SetIcon(IDI_SOCCCD_LIVE);
	}
}
void CDlgSocketVisionLive::OnOperate() 
{
	m_CBList.EnableWindow( TRUE );
}
