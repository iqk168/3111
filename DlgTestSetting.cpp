// DlgTestSetting.cpp : implementation file
//

#include "stdafx.h"
#include "deer.h"
#include "DlgTestSetting.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgTestSetting dialog


CDlgTestSetting::CDlgTestSetting(CString csFile, CWnd* pParent /*=NULL*/)
	: CDialog(CDlgTestSetting::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgTestSetting)
	//}}AFX_DATA_INIT

	m_GPIBfile	= _T("");
	m_Rs232file	= _T("");
	m_Tcpfile	= _T("");
	m_Ttlfile	= _T("");

	//
	m_csProductionFile = _T("");
	m_csProductionFile = csFile;

	m_GPIBfile	= m_csProductionFile + _SubInterfaceGPIB;
	m_Rs232file	= m_csProductionFile + _SubInterfaceRS232;
	m_Tcpfile	= m_csProductionFile + _SubInterfaceTCP;
	m_Ttlfile	= m_csProductionFile + _SubInterfaceTTL;
}

void CDlgTestSetting::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgTestSetting)
	DDX_Control(pDX, IDC_TYPE_INDEXC2,	m_Index2);
	DDX_Control(pDX, IDC_TYPE_INDEXC,	m_Index1);
	DDX_Control(pDX, IDOK,				m_btnOK);
	DDX_Control(pDX, IDCANCEL,			m_btnCancel);
	DDX_Control(pDX, IDC_I_RS232,		m_btnRs232);
	DDX_Control(pDX, IDC_I_GPIB,		m_btnGbip);
	DDX_Control(pDX, IDC_I_TCP,			m_btnTcpip);
	DDX_Control(pDX, IDC_I_TTL,			m_btnTTL);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgTestSetting, CDialog)
	//{{AFX_MSG_MAP(CDlgTestSetting)
	ON_WM_SHOWWINDOW()
	ON_BN_CLICKED(IDC_I_RS232,			OnIRs232)
	ON_BN_CLICKED(IDC_I_TCP,			OnITcp)
	ON_BN_CLICKED(IDC_I_GPIB,			OnIGpib)
	ON_BN_CLICKED(IDC_I_TTL,			OnITtl)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgTestSetting message handlers

void CDlgTestSetting::OnCancel() 
{
	
	CDialog::OnCancel();
}
bool CDlgTestSetting::SaveData()
{
	bool bSaveOK	= true;
	bool bRs232OK	= true;
	bool bTcpOK		= true;
	bool bGpibOK	= true;
	bool bTtlOK		= true;

	bRs232OK	= DlgPage.m_DlgRs232.SaveRS232Data();
	bTcpOK		= DlgPage.m_DlgTcp.SaveTcpData();
	bGpibOK		= DlgPage.m_DlgGpib.SaveGPIBData();
	bTtlOK		= DlgPage.m_DlgTTL.SaveTTLData();

	if( bRs232OK && bTcpOK && bGpibOK && bTtlOK )
		bSaveOK = true;
	else 
	{
		bSaveOK = false;
		if( !bRs232OK )
		{
			CString csMsg = _T("");
			csMsg.Format("Rs232 interface parameter setting fail.! Please check again.!\r\n%s", 
				DlgPage.m_DlgRs232.m_csExtendErrMsg );
			AfxMessageBox( csMsg );
		}
		else if( !bTcpOK )
		{
			CString csMsg = _T("");
			csMsg.Format("Tcp interface parameter setting fail.! Please check again.!\r\n%s", 
				DlgPage.m_DlgTcp.m_csExtendErrMsg );
			AfxMessageBox( csMsg );
		}
		else if( !bGpibOK )
		{
			AfxMessageBox("Gpib interface parameter setting fail.! Please check again.!");
		}	
		else if( !bTtlOK )
		{
			AfxMessageBox("Ttl interface parameter setting fail.! Please check again.!");
		}
	}

	// 儲存所選的類別
	SaveInterfaceType(); // RS232, TCP, GPIB, TTL

	return bSaveOK;
}
void CDlgTestSetting::OnOK() 
{	
	if( !SaveData() )
	{
		return;
	}

	f.LoadInterface();
	f.LoadInterFaceRs232();
	f.LoadInterFaceTcp();
	f.LoadTcpToObject();

	CDialog::OnOK();
}

BOOL CDlgTestSetting::PreTranslateMessage(MSG* pMsg) 
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

BOOL CDlgTestSetting::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// init button 
	m_btnOK.SetIcon(IDI_SAVE);
	m_btnOK.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnOK.SetFlat(FALSE);
	
	m_btnCancel.SetIcon(IDI_CANCEL);
	m_btnCancel.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnCancel.SetFlat(FALSE);
	
	//
	InitPageControl();

	//
	InitValue();

	f.ChangeLanguage(GetSafeHwnd());

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
void CDlgTestSetting::InitValue()
{
	SetInterfaceType ( LoadInterfaceType() );

	SetDefaultButton( LoadInterfaceType() );
}

void CDlgTestSetting::SaveInterfaceType()
{		
	int iSelected = 0;
	int iGet1 = m_btnRs232.GetCheck();
	int iGet2 = m_btnTcpip.GetCheck();
	int iGet3 = m_btnGbip.GetCheck();
	int iGet4 = m_btnTTL.GetCheck();

	if( iGet1 == 1 )
		iSelected = theApp.enRS232;
	else if( iGet2 == 1 )
		iSelected = theApp.enTCP;
	else if( iGet3 == 1 )
		iSelected = theApp.enGPIB;
	else if( iGet4 == 1 )
		iSelected = theApp.enTTL;
	else
		; // Nerver be here.!

	//
	CString csTesting = _T("");
	csTesting = m_csProductionFile + _SubTestSettingName2;

	CString csTestingFilePath = _T("");
	csTestingFilePath = m.FilePath.TestSettingPath + csTesting;	

	//
	f.SaveSetting(csTestingFilePath, "Interface Selected", "Selected",	iSelected );
}
int CDlgTestSetting::LoadInterfaceType()
{	
	int iSelected = 0;
	//
	CString csTesting = _T("");
	csTesting = m_csProductionFile + _SubTestSettingName2;

	CString csTestingFilePath = _T("");
	csTestingFilePath = m.FilePath.TestSettingPath + csTesting;	

	//
	f.GetSetting(csTestingFilePath, "Interface Selected", "Selected",	iSelected );	
	
	return iSelected;
}
void CDlgTestSetting::SetInterfaceType(int iInterfaceType)
{
	ChangeInterface( iInterfaceType );	
}
void CDlgTestSetting::SetDefaultButton( int iInterfaceType)
{
	if( iInterfaceType == theApp.enRS232 )
	{
		m_btnRs232.SetCheck(1);
		m_btnGbip.SetCheck(0);
		m_btnTcpip.SetCheck(0);	
		m_btnTTL.SetCheck(0);	
	}
	else if( iInterfaceType == theApp.enTCP )
	{
		m_btnRs232.SetCheck(0);
		m_btnGbip.SetCheck(0);
		m_btnTcpip.SetCheck(1);	
		m_btnTTL.SetCheck(0);
	}
	else if( iInterfaceType == theApp.enGPIB )
	{
		m_btnRs232.SetCheck(0);
		m_btnGbip.SetCheck(1);
		m_btnTcpip.SetCheck(0);	
		m_btnTTL.SetCheck(0);
	}
	else if( iInterfaceType == theApp.enTTL )
	{
		m_btnRs232.SetCheck(0);
		m_btnGbip.SetCheck(0);
		m_btnTcpip.SetCheck(0);	
		m_btnTTL.SetCheck(1);
	}
	else 
		; // Never be here.!!

	ButtonUpdataStatus();
}
void CDlgTestSetting::InitPageControl() 
{
	RECT rt;
	::GetWindowRect(::GetDlgItem(m_hWnd, IDC_INDEX), &rt);
	::MapWindowPoints(NULL, m_hWnd, (LPPOINT)&rt, 2);

	DlgPage.m_DlgGpib.Create(IDD_SETTING_GPIB, this);
	DlgPage.m_DlgGpib.MoveWindow(&rt);
	DlgPage.m_DlgGpib.ShowWindow(SW_HIDE);
	DlgPage.m_DlgGpib.SetFile( m_GPIBfile );

	DlgPage.m_DlgRs232.Create(IDD_SETTING_RS232, this);
	DlgPage.m_DlgRs232.MoveWindow(&rt);
	DlgPage.m_DlgRs232.ShowWindow(SW_HIDE);
	DlgPage.m_DlgRs232.SetFile( m_Rs232file );

	DlgPage.m_DlgTcp.Create(IDD_SETTING_TCP, this);
	DlgPage.m_DlgTcp.MoveWindow(&rt);
	DlgPage.m_DlgTcp.ShowWindow(SW_HIDE);
	DlgPage.m_DlgTcp.SetFile( m_Tcpfile );

	DlgPage.m_DlgTTL.Create(IDD_SETTING_TTL, this);
	DlgPage.m_DlgTTL.MoveWindow(&rt);
	DlgPage.m_DlgTTL.ShowWindow(SW_HIDE);
	DlgPage.m_DlgTTL.SetFile( m_Ttlfile );
	// Set File to Child Page.!

}
void CDlgTestSetting::ChangeInterface(int page)
{
/*
	enRS232		= 0,	// RS232
	enGPIB		= 1,	// GPIB
	enTCP		= 2,	// TCP
	enTTL		= 3,	// TTL

	CString csMsg = _T("");
	csMsg.Format("page: %d", page );
	AfxMessageBox( csMsg );
*/

	if( page == theApp.enRS232 )
	{
		DlgPage.m_DlgRs232.ShowWindow(SW_SHOW);
		DlgPage.m_DlgGpib.ShowWindow(SW_HIDE);
		DlgPage.m_DlgTcp.ShowWindow(SW_HIDE);
		DlgPage.m_DlgTTL.ShowWindow(SW_HIDE);
	}
	else if( page == theApp.enGPIB )
	{	
		DlgPage.m_DlgGpib.ShowWindow(SW_SHOW);
		DlgPage.m_DlgRs232.ShowWindow(SW_HIDE);
		DlgPage.m_DlgTcp.ShowWindow(SW_HIDE);
		DlgPage.m_DlgTTL.ShowWindow(SW_HIDE);
	}
	else if( page == theApp.enTCP )
	{
		DlgPage.m_DlgGpib.ShowWindow(SW_HIDE);
		DlgPage.m_DlgRs232.ShowWindow(SW_HIDE);
		DlgPage.m_DlgTcp.ShowWindow(SW_SHOW);
		DlgPage.m_DlgTTL.ShowWindow(SW_HIDE);
	}
	else if( page == theApp.enTTL )
	{
		DlgPage.m_DlgGpib.ShowWindow(SW_HIDE);
		DlgPage.m_DlgRs232.ShowWindow(SW_HIDE);
		DlgPage.m_DlgTcp.ShowWindow(SW_HIDE);
		DlgPage.m_DlgTTL.ShowWindow(SW_SHOW);
	}	 
	else
		; // Never be here	
}
void CDlgTestSetting::ButtonUpdataStatus() 
{
	m_btnRs232.Invalidate();
	m_btnGbip.Invalidate();
	m_btnTcpip.Invalidate();
	m_btnTTL.Invalidate();
}
void CDlgTestSetting::OnIRs232() 
{
	ChangeInterface( theApp.enRS232 );

	ButtonUpdataStatus();
}
void CDlgTestSetting::OnITcp() 
{
	ChangeInterface( theApp.enTCP );

	ButtonUpdataStatus();
}
void CDlgTestSetting::OnIGpib() 
{
	ChangeInterface( theApp.enGPIB );

	ButtonUpdataStatus();
}

void CDlgTestSetting::OnITtl() 
{
	ChangeInterface( theApp.enTTL );

	ButtonUpdataStatus();
}
void CDlgTestSetting::GetButtonDistance(int &Width, int &Distance)
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
void CDlgTestSetting::UpdataInterfaceTypeButton()
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

	////
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
		m_btnTTL.ShowWindow( TRUE );
		for(i=0;i<_IF_TYPE_ICON;i++)
		{
			if( !rtUse[i] )
			{
				rtUse[i] = true;
				m_btnTTL.MoveWindow(&rtW[i]);
				break;
			}
		}
	}
	else
	{
		m_btnTTL.ShowWindow( FALSE );
	}
}

void CDlgTestSetting::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	if(bShow)
	{
		UpdataInterfaceTypeButton();
	}

	CDialog::OnShowWindow(bShow, nStatus);	
}

