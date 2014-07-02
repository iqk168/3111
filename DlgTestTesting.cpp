// DlgTestTesting.cpp : implementation file
//

#include "stdafx.h"
#include "deer.h"
#include "DlgTestTesting.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgTestTesting dialog


CDlgTestTesting::CDlgTestTesting(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgTestTesting::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgTestTesting)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	m_iIfType = 0;
}


void CDlgTestTesting::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgTestTesting)
	DDX_Control(pDX, IDC_INFO,			m_wndTesterInfo);
	DDX_Control(pDX, IDC_LIST,			m_list);
	DDX_Control(pDX, IDC_E_CLEAR,		m_btnClear);
	DDX_Control(pDX, IDC_E_SEND,		m_btnSend);
	DDX_Control(pDX, IDOK,				m_btnOK);
	DDX_Control(pDX, IDCANCEL,			m_btnCancel);
	DDX_Control(pDX, IDC_TYPE_INDEXC2,	m_Index2);
	DDX_Control(pDX, IDC_TYPE_INDEXC,	m_Index1);
	DDX_Control(pDX, IDC_I_RS232,		m_btnRs232);
	DDX_Control(pDX, IDC_I_GPIB,		m_btnGbip);
	DDX_Control(pDX, IDC_I_TCP,			m_btnTcpip);
	DDX_Control(pDX, IDC_I_TTL,			m_btnTtl);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDlgTestTesting, CDialog)
	//{{AFX_MSG_MAP(CDlgTestTesting)
	ON_WM_SHOWWINDOW()
	ON_BN_CLICKED(IDC_I_TTL,		OnITtl)
	ON_BN_CLICKED(IDC_I_RS232,		OnIRs232)
	ON_BN_CLICKED(IDC_I_GPIB,		OnIGpib)
	ON_BN_CLICKED(IDC_I_TCP,		OnITcp)
	ON_BN_CLICKED(IDC_E_SEND,		OnESend)
	ON_BN_CLICKED(IDC_E_CLEAR,		OnEClear)
	//
	ON_MESSAGE( WM_MANUAL_TEST_MSG,	OnTestingMessage )
	
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgTestTesting message handlers

void CDlgTestTesting::OnCancel() 
{
	
	CDialog::OnCancel();
}

void CDlgTestTesting::OnOK() 
{
	
	CDialog::OnOK();
}

BOOL CDlgTestTesting::PreTranslateMessage(MSG* pMsg) 
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

BOOL CDlgTestTesting::OnInitDialog() 
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
	LockUI();
	
	//
	SetDefaultIf( LoadInterfaceType() );

	//
	ClearAllInformation();

	//
	InitInfo();

	f.ChangeLanguage(GetSafeHwnd());

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
void CDlgTestTesting::InitInfo()
{
	int m_iIf = LoadInterfaceType();

	if( m_iIf == theApp.enRS232 )
	{
		CString csMsg = _T("");
		CString csSystem = _T("");
		int m_iBaudRate = f.GetTesterBaudRate();
		csSystem.Format("Com Port: %d, Rate: %d", 
		m.m_HandlerComPort.iPortTester, m_iBaudRate );
		csMsg += csSystem;

		m_wndTesterInfo.SetWindowText( csMsg );
	}
	else if( m_iIf == theApp.enTCP )
	{
		// 1.0Ah
		// Remove this function and re-build new one
		/*
		CString csMsg = _T("");
		CString csSystem = _T("");
		CString csIP = _T("");
		char cIp[256];
		csIP = f.GetTesterIPAddress(cIp);
		int read = sizeof(cIp);
		for(int i=0; i<read; i++)
			csIP += cIp[i];
		csSystem.Format("IP: %s, Port: %d", csIP, _Tcp_If_Port);
		csMsg += csSystem;
		*/

		// 1.0Ah
		CString csMsg = _T("");
		CString csSystem = _T("");
		CString csIP = _T("");
		f.GetHandlerIPAddress(csIP);
		csSystem.Format("IP: %s, Port: %d", csIP, _Tcp_If_Port);
		csMsg += csSystem;

		m_wndTesterInfo.SetWindowText( csMsg );
	}
}
int CDlgTestTesting::LoadInterfaceType()
{
	int iSelected = -1;
	
	if( m.UI.FileMainTestSetting == "" )
		return iSelected;

	CString csTesting = _T("");
	csTesting = m.UI.FileMainTestSetting;

	CString csTestingFilePath = _T("");
	csTestingFilePath = m.FilePath.TestSettingPath + csTesting;	

	//
	f.GetSetting(csTestingFilePath, "Interface Selected", "Selected",	iSelected );	
	
	return iSelected;
}
void CDlgTestTesting::LockUI()
{
	if( LoadInterfaceType() == -1 )
	{
		BOOL bEnable = FALSE;
		m_btnRs232.EnableWindow( bEnable );
		m_btnGbip.EnableWindow( bEnable );
		m_btnTcpip.EnableWindow( bEnable );
		m_btnTtl.EnableWindow( bEnable );

		//
		m_btnSend.EnableWindow( bEnable );
		m_btnClear.EnableWindow( bEnable );
	}
}
static CMutex MutexMsg;
void CDlgTestTesting::ShowInformation(CString csInfo )
{
	CSingleLock Lock(&MutexMsg);
	Lock.Lock();

	m_list.InsertString( m_list.GetCount(), csInfo );
	m_list.SetCurSel( m_list.GetCount() - 1 );

	Lock.Unlock();
}
void CDlgTestTesting::ClearAllInformation()
{
	m_list.ResetContent();
}
void CDlgTestTesting::SetDefaultIf(int iIf)
{
	if( iIf != -1 )
	{
		if( iIf == theApp.enRS232 )
		{
			m_btnRs232.SetCheck(1);
			m_btnGbip.SetCheck(0);
			m_btnTcpip.SetCheck(0);
			m_btnTtl.SetCheck(0);
		}
		else if( iIf == theApp.enTCP )
		{
			m_btnRs232.SetCheck(0);
			m_btnGbip.SetCheck(0);
			m_btnTcpip.SetCheck(1);
			m_btnTtl.SetCheck(0);
		}
		else if( iIf == theApp.enGPIB )
		{
			m_btnRs232.SetCheck(0);
			m_btnGbip.SetCheck(1);
			m_btnTcpip.SetCheck(0);
			m_btnTtl.SetCheck(0);
		}
		else if( iIf == theApp.enTTL )
		{
			m_btnRs232.SetCheck(0);
			m_btnGbip.SetCheck(0);
			m_btnTcpip.SetCheck(0);
			m_btnTtl.SetCheck(1);
		}
	}
}
void CDlgTestTesting::GetButtonDistance(int &Width, int &Distance)
{
	// 取得 Option Button 的寬度, 和兩個按鈕之間的距離.

	CRect Rect;
	m_Index1.GetClientRect( Rect );
	Width = Rect.right - Rect.left;

	//	
	CRect Rect1, Rect2;	
	m_Index1.GetWindowRect( Rect1 );
	m_Index2.GetWindowRect( Rect2 );
	Distance = Rect2.left - Rect1.right;
}
void CDlgTestTesting::UpdataInterfaceTypeButton()
{
	//////////////////////////////////////////////////////////////////////
	// 重設介面
	RECT rt;
	::GetWindowRect(::GetDlgItem(m_hWnd, IDC_TYPE_INDEXC), &rt);
	::MapWindowPoints(NULL, m_hWnd, (LPPOINT)&rt, 2);	

	RECT rtW[_IF_TYPE_ICON];
	bool rtUse[_IF_TYPE_ICON];
	for(int i=0;i<_IF_TYPE_ICON;i++)
		rtUse[i] = false;

	//
	for(i=0;i<_IF_TYPE_ICON;i++)
		rtW[i] = rt;
	
	////
	int iDistance = 0;
	int iWidth = 0;
	GetButtonDistance( iWidth, iDistance );

	//
	for(i=0;i<_IF_TYPE_ICON;i++)
	{
		rtW[i].left	 = rt.left + ( iWidth * i ) + ( iDistance * i );
		rtW[i].right = rt.right	+ ( iWidth * i ) + ( iDistance * i );
	}

	// RS232
	if( m.m_InterfaceEnable.m_bEnableRs232 == 1 )
	{
		m_btnRs232.ShowWindow( TRUE );
		for(i=0;i<_IF_TYPE_ICON;i++)
		{
			if( !rtUse[i] )
			{
				rtUse[i] = true;
				m_btnRs232.MoveWindow(&rtW[i]);
				break;
			}
		}
	}
	else
	{
		m_btnRs232.ShowWindow( FALSE );
	}

	// TCP
	if( m.m_InterfaceEnable.m_bEnableTcp == 1 )
	{
		m_btnTcpip.ShowWindow( TRUE );
		for(i=0;i<_IF_TYPE_ICON;i++)
		{
			if( !rtUse[i] )
			{
				rtUse[i] = true;
				m_btnTcpip.MoveWindow(&rtW[i]);
				break;
			}
		}
	}
	else
	{
		m_btnTcpip.ShowWindow( FALSE );
	}

	// GPIB
	if( m.m_InterfaceEnable.m_bEnableGpib == 1 )
	{
		m_btnGbip.ShowWindow( TRUE );
		for(i=0;i<_IF_TYPE_ICON;i++)
		{
			if( !rtUse[i] )
			{
				rtUse[i] = true;
				m_btnGbip.MoveWindow(&rtW[i]);
				break;
			}
		}
	}
	else
	{
		m_btnGbip.ShowWindow( FALSE );
	}

	// TTL
	if( m.m_InterfaceEnable.m_bEnableTTL == 1 )
	{
		m_btnTtl.ShowWindow( TRUE );
		for(i=0;i<_IF_TYPE_ICON;i++)
		{
			if( !rtUse[i] )
			{
				rtUse[i] = true;
				m_btnTtl.MoveWindow(&rtW[i]);
				break;
			}
		}
	}
	else
	{
		m_btnTtl.ShowWindow( FALSE );
	}
}

void CDlgTestTesting::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	if( bShow )
	{
		UpdataInterfaceTypeButton();
	}

	CDialog::OnShowWindow(bShow, nStatus);	
}
void CDlgTestTesting::ButtonUpdataStatus() 
{
	m_btnRs232.Invalidate();
	m_btnGbip.Invalidate();
	m_btnTcpip.Invalidate();
	m_btnTtl.Invalidate();
}
void CDlgTestTesting::OnITtl() 
{
	ButtonUpdataStatus();
}
void CDlgTestTesting::OnIRs232() 
{
	SetDefaultIf( LoadInterfaceType() );

	ButtonUpdataStatus();
}
void CDlgTestTesting::OnIGpib() 
{
	SetDefaultIf( LoadInterfaceType() );

	ButtonUpdataStatus();
}
void CDlgTestTesting::OnITcp() 
{
	SetDefaultIf( LoadInterfaceType() );

	ButtonUpdataStatus();	
}
UINT CDlgTestTesting::TestingThread(LPVOID p)
{
	CDlgTestTesting *pt = (CDlgTestTesting *)p;

	while(1)
	{
		if( pt->m_iIfType == 1 )
		{
			// Rs232
			theApp.m_tTester.RS232Testing();
			break;
		}	
		else if( pt->m_iIfType == 2 )
		{
			// ttl
			break;
		}
		else if( pt->m_iIfType == 3 )
		{
			// gpib
			break;
		}
		else if( pt->m_iIfType == 4 )
		{
			// Tcpip
			theApp.m_tTester.TcpTesting();
			break;
		}
	
		Sleep(1);
	}

	pt->TestingLockUI( false );

	return TRUE;
}
LRESULT CDlgTestTesting::OnTestingMessage(WPARAM p, LPARAM l)
{
	CString *pp = (CString *)p;

	ShowInformation( *pp );

	return TRUE;
}
void CDlgTestTesting::TestingLockUI(bool bEnable) 
{
	if( bEnable )
	{
		// Lock
		m_btnClear.EnableWindow( FALSE );
		m_btnSend.EnableWindow( FALSE );
		m_btnOK.EnableWindow( FALSE );
		m_btnCancel.EnableWindow( FALSE );
		m_Index2.EnableWindow( FALSE );
		m_Index1.EnableWindow( FALSE );
		m_btnRs232.EnableWindow( FALSE );
		m_btnGbip.EnableWindow( FALSE );
		m_btnTcpip.EnableWindow( FALSE );
		m_btnTtl.EnableWindow( FALSE );
	}
	else
	{
		// Unlock
		m_btnClear.EnableWindow( TRUE );
		m_btnSend.EnableWindow( TRUE );
		m_btnOK.EnableWindow( TRUE );
		m_btnCancel.EnableWindow( TRUE );
		m_Index2.EnableWindow( TRUE );
		m_Index1.EnableWindow( TRUE );
		m_btnRs232.EnableWindow( TRUE );
		m_btnGbip.EnableWindow( TRUE );
		m_btnTcpip.EnableWindow( TRUE );
		m_btnTtl.EnableWindow( TRUE );	
	}
	ButtonUpdataStatus();
}
void CDlgTestTesting::OnESend() 
{
	int b1 = m_btnRs232.GetCheck();
	int b2 = m_btnTtl.GetCheck();
	int b3 = m_btnGbip.GetCheck();
	int b4 = m_btnTcpip.GetCheck();	

	TestingSetIf(b1, b2, b3, b4);
	TestingLockUI( true );
	AfxBeginThread(TestingThread, this);	
}
void CDlgTestTesting::TestingSetIf(int b1, int b2, int b3, int b4)
{
	if( b1 == 1 )
		m_iIfType = 1; //Rs232
	else if( b2 == 1 )
		m_iIfType = 2; // ttl
	else if( b3 == 1 )
		m_iIfType = 3; // gpib
	else if( b4 == 1 )
		m_iIfType = 4; // tcpip
	else
		;
}
void CDlgTestTesting::OnEClear() 
{
	ClearAllInformation();	
}
