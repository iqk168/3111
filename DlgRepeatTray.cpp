// DlgRepeatTray.cpp : implementation file
//

#include "stdafx.h"
#include "deer.h"
#include "DlgRepeatTray.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgRepeatTray dialog


CDlgRepeatTray::CDlgRepeatTray(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgRepeatTray::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgRepeatTray)
	m_iRepeatTray = -1;
	//}}AFX_DATA_INIT

	m_RepeatTrayCtrl = m.m_RepeatTrayCtrl;

	m_bMappingOn = false;
}


void CDlgRepeatTray::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgRepeatTray)
	DDX_Control(pDX, IDC_MAPPING,					m_btnRepeatMapping);
	DDX_Control(pDX, IDC_R_REPEAT_TRAY_MODE_BIN,	m_btnRepeatTrayBinningCtrl);
	DDX_Control(pDX, IDC_R_REPEAT_TRAY_MODE_INOUT,	m_btnRepeatTrayInOutCtrl);
	DDX_Control(pDX, IDC_R_REPEAT_TRAY_MODE_NONE,	m_btnRepeatTrayNone);
	DDX_Control(pDX, IDCANCEL,						m_btnCancel);
	DDX_Control(pDX, IDOK,							m_btnOK);
	DDX_Radio(pDX, IDC_R_REPEAT_TRAY_MODE_NONE,		m_iRepeatTray);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgRepeatTray, CDialog)
	//{{AFX_MSG_MAP(CDlgRepeatTray)
	ON_BN_CLICKED(IDC_R_REPEAT_TRAY_MODE_NONE,		OnRRepeatTrayModeNone)
	ON_BN_CLICKED(IDC_R_REPEAT_TRAY_MODE_INOUT,		OnRRepeatTrayModeInOutCtrl)
	ON_BN_CLICKED(IDC_R_REPEAT_TRAY_MODE_BIN,		OnRRepeatTrayModeBinning)
	ON_WM_SHOWWINDOW()
	ON_BN_CLICKED(IDC_MAPPING, OnMapping)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgRepeatTray message handlers

void CDlgRepeatTray::OnOK() 
{
	SaveData();

	m.Info.bSubDlgOpen = false;
	f.UpdateButtonState();
	
	CDialog::OnOK();
}

void CDlgRepeatTray::OnCancel() 
{
	m.Info.bSubDlgOpen = false;
	f.UpdateButtonState();
	
	CDialog::OnCancel();
}

BOOL CDlgRepeatTray::PreTranslateMessage(MSG* pMsg) 
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

BOOL CDlgRepeatTray::OnInitDialog() 
{
	CDialog::OnInitDialog();

	m.Info.bSubDlgOpen = true;
	f.UpdateButtonState();	

	// init button 
	m_btnOK.SetIcon(IDI_SAVE);
	m_btnOK.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnOK.SetFlat(FALSE);

	m_btnCancel.SetIcon(IDI_CANCEL);;
	m_btnCancel.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnCancel.SetFlat(FALSE);

	m_btnRepeatMapping.SetIcon(IDI_REPEAT_TRAY_OFF);
	m_btnRepeatMapping.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnRepeatMapping.SetFlat(FALSE);

	//
	InitPage();

	//
	InitValue();

	//
	InitTips();

	//
	LockUI();

	//
	f.SetTitleExtend(this, theApp.enTtileMachineFile );

	//
	f.ChangeLanguage(GetSafeHwnd());
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
void CDlgRepeatTray::LockUI()
{
	if( m.LotInfo.LotInfoIsLotStart == 1 )
	{
		// Lock all
		BOOL bEnable = FALSE;
		m_btnRepeatTrayBinningCtrl.EnableWindow( bEnable );
		m_btnRepeatTrayInOutCtrl.EnableWindow( bEnable );
		m_btnRepeatTrayNone.EnableWindow( bEnable );
	}
	else
	{
		// No Lock all
		BOOL bEnable = TRUE;
		m_btnRepeatTrayBinningCtrl.EnableWindow( bEnable );
		m_btnRepeatTrayInOutCtrl.EnableWindow( bEnable );
		m_btnRepeatTrayNone.EnableWindow( bEnable );
	}
}
void CDlgRepeatTray::InitPage()
{
	RECT rt;
	::GetWindowRect(::GetDlgItem(m_hWnd, IDC_MODE_GRP), &rt);
	::MapWindowPoints(NULL, m_hWnd, (LPPOINT)&rt, 2);

	DlgRePage.m_DlgInOutCtrl.Create(IDD_DLG_REPEAT_TRAY_INOUT, this);
	DlgRePage.m_DlgInOutCtrl.MoveWindow(&rt);
	DlgRePage.m_DlgInOutCtrl.ShowWindow(SW_SHOW);	// defaul

	DlgRePage.m_DlgBinCtrl.Create(IDD_DLG_REPEAT_TRAY_BIN, this);
	DlgRePage.m_DlgBinCtrl.MoveWindow(&rt);
	DlgRePage.m_DlgBinCtrl.ShowWindow(SW_HIDE);
}
void CDlgRepeatTray::InitValue()
{
	m_iRepeatTray = m_RepeatTrayCtrl.m_iRepeatTrayMode;

	UpdateData( FALSE );

	ButtonPress();
}
void CDlgRepeatTray::SaveData()
{
	UpdateData();
	
	// Mode
	m_RepeatTrayCtrl.m_iRepeatTrayMode = m_iRepeatTray;

	// Input / Output 
	CString csInOut = _T("");
	bool bInOutOK = DlgRePage.m_DlgInOutCtrl.SaveData(csInOut);

	if( !bInOutOK )
	{
		CString csMsg = _T("");
		csMsg += csInOut;

		AfxMessageBox( csMsg );
		return;
	}

	//
	m.m_RepeatTrayCtrl = m_RepeatTrayCtrl;
	f.SaveRepeatTraySetting();
}
void CDlgRepeatTray::InitTips()
{
	// Init Tips
	m_ToolTip.Create(this);
	m_ToolTip.SetMaxTipWidth(800);
	m_ToolTip.SetDelayTime( TTDT_AUTOPOP, 10000 );
	m_ToolTip.SetDelayTime( TTDT_INITIAL, 25 );
	m_ToolTip.EnableToolTips(true);

	//
	if( m.m_EnableRepeatTrayFun.m_bNone == 1 )
		m_ToolTip.AddTool( GetDlgItem(IDC_R_REPEAT_TRAY_MODE_NONE),			_T("Repeat Tray None") );
	if( m.m_EnableRepeatTrayFun.m_bInOutCtrl == 1 )
		m_ToolTip.AddTool( GetDlgItem(IDC_R_REPEAT_TRAY_MODE_INOUT),		_T("Repeat Tray Input/Output control") );
	if( m.m_EnableRepeatTrayFun.m_bTrayBinningCtrl == 1 )
		m_ToolTip.AddTool( GetDlgItem(IDC_R_REPEAT_TRAY_MODE_BIN),			_T("Repeat Tray Binning control") );
}
void CDlgRepeatTray::ButtonPress() 
{
	if( m.m_EnableRepeatTrayFun.m_bTrayBinningCtrl == 1 )
		m_btnRepeatTrayBinningCtrl.Invalidate();
	if( m.m_EnableRepeatTrayFun.m_bInOutCtrl == 1 )
		m_btnRepeatTrayInOutCtrl.Invalidate();
	if( m.m_EnableRepeatTrayFun.m_bNone == 1 )
		m_btnRepeatTrayNone.Invalidate();
}
void CDlgRepeatTray::ChangeRepeatTrayMode(int iMode)
{
	switch(iMode)
	{
	case theApp.enRepeatTrayNone:
		{
			DlgRePage.m_DlgInOutCtrl.ShowWindow(SW_HIDE);
			DlgRePage.m_DlgBinCtrl.ShowWindow(SW_HIDE);			
		}
		break;
	case theApp.enRepeatTrayInOutCtrl:
		{
			DlgRePage.m_DlgInOutCtrl.ShowWindow(SW_SHOW);
			DlgRePage.m_DlgBinCtrl.ShowWindow(SW_HIDE);			
		}
		break;
	case theApp.enRepeatTrayBinningCtrl:
		{
			DlgRePage.m_DlgInOutCtrl.ShowWindow(SW_HIDE);
			DlgRePage.m_DlgBinCtrl.ShowWindow(SW_SHOW);		
		}
		break;
	default:
		{
			DlgRePage.m_DlgInOutCtrl.ShowWindow(SW_HIDE);
			DlgRePage.m_DlgBinCtrl.ShowWindow(SW_HIDE);			
		}
	}
}
void CDlgRepeatTray::OnRRepeatTrayModeNone() 
{
	ChangeRepeatTrayMode( theApp.enRepeatTrayNone );
	ButtonPress();	
}
void CDlgRepeatTray::OnRRepeatTrayModeInOutCtrl() 
{
	ChangeRepeatTrayMode( theApp.enRepeatTrayInOutCtrl );
	ButtonPress();
}
void CDlgRepeatTray::OnRRepeatTrayModeBinning() 
{
	ChangeRepeatTrayMode( theApp.enRepeatTrayBinningCtrl );
	ButtonPress();
}
void CDlgRepeatTray::GetButtonDistance(int &Width, int &Height, int &WDistance, int &HDistance)
{
	// 取得 Option Button 的寬度, 和兩個按鈕之間的距離.
	CRect Rect;
	GetDlgItem(IDC_INDEX1)->GetClientRect( &Rect );
	Width = Rect.right - Rect.left;
	Height = Rect.bottom - Rect.top;

	//	
	CRect Rect1;
	GetDlgItem(IDC_INDEX1)->GetWindowRect( &Rect1 );
	WDistance = _RE_ICON_W;
	HDistance = _RE_ICON_H;
}
void CDlgRepeatTray::ReDrawRepeatFun()
{
	//////////////////////////////////////////////////////////////////////
	// 重設介面
	RECT rt;
	::GetWindowRect(::GetDlgItem(m_hWnd, IDC_INDEX1), &rt);
	::MapWindowPoints(NULL, m_hWnd, (LPPOINT)&rt, 2);	
	
	RECT rtW[_RE_ICON_Max];
	bool rtUse[_RE_ICON_Max];
	for(int i=0;i<_RE_ICON_Max;i++)
		rtUse[i] = false;

	//
	for(i=0;i<_RE_ICON_Max;i++)
		rtW[i] = rt;
	
	//
	int iButtonWidth		= 0;
	int iButtonHeight		= 0;
	int iButtonWDistance	= 0;
	int iButtonHDistance	= 0;
	GetButtonDistance( iButtonWidth, iButtonHeight, iButtonWDistance, iButtonHDistance );
	//
	for(i=0;i<_RE_ICON_Max;i++)
	{
		int x = i % _RE_ICON_Max_Row;
		int y = i / _RE_ICON_Max_Row;
		rtW[i].left		= rt.left + ( iButtonWidth * x ) + ( iButtonWDistance * x );
		rtW[i].right	= rt.right	+ ( iButtonWidth * x ) + ( iButtonWDistance * x );

		rtW[i].top		= rt.top + ( iButtonHeight * y ) + ( iButtonHDistance * y );
		rtW[i].bottom	= rt.bottom + ( iButtonHeight * y ) + ( iButtonHDistance * y );
	}

	// None
	if( m.m_EnableRepeatTrayFun.m_bNone == 1 )
	{		
		for(i=0;i<_RE_ICON_Max;i++)
		{
			m_btnRepeatTrayNone.ShowWindow( TRUE );
			if( !rtUse[i] )
			{
				rtUse[i] = true;
				m_btnRepeatTrayNone.MoveWindow(&rtW[i]);
				break;
			}
		}
	}
	else
		m_btnRepeatTrayNone.ShowWindow( FALSE );

	// Input/Output control
	if( m.m_EnableRepeatTrayFun.m_bInOutCtrl == 1 )
	{		
		for(i=0;i<_RE_ICON_Max;i++)
		{
			m_btnRepeatTrayInOutCtrl.ShowWindow( TRUE );
			if( !rtUse[i] )
			{
				rtUse[i] = true;
				m_btnRepeatTrayInOutCtrl.MoveWindow(&rtW[i]);
				break;
			}
		}
	}
	else
		m_btnRepeatTrayInOutCtrl.ShowWindow( FALSE );

	// Binning control
	if( m.m_EnableRepeatTrayFun.m_bTrayBinningCtrl == 1 )
	{		
		m_btnRepeatTrayBinningCtrl.ShowWindow( TRUE );
		for(i=0;i<_RE_ICON_Max;i++)
		{
			if( !rtUse[i] )
			{
				rtUse[i] = true;
				m_btnRepeatTrayBinningCtrl.MoveWindow(&rtW[i]);
				break;
			}
		}
	}
	else
		m_btnRepeatTrayBinningCtrl.ShowWindow( FALSE );
}
void CDlgRepeatTray::ReDrawUI()
{

}
void CDlgRepeatTray::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	if(bShow)
	{
		ReDrawRepeatFun();
	}
	CDialog::OnShowWindow(bShow, nStatus);
}
void CDlgRepeatTray::OnMapping() 
{
	TurnOnMapping();	
}
void CDlgRepeatTray::TurnOnMapping() 
{

}