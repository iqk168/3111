// DlgExtendFunction.cpp : implementation file
//

#include "stdafx.h"
#include "deer.h"
#include "DlgExtendFunction.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgExtendFunction dialog


CDlgExtendFunction::CDlgExtendFunction(CString file, CWnd* pParent /*=NULL*/)
	: CDialog(CDlgExtendFunction::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgExtendFunction)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	m_file = _T("");
	m_file = file;
}


void CDlgExtendFunction::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgExtendFunction)
	
	// Rotator 
	DDX_Control(pDX, IDC_N_90,				m_n90);
	DDX_Control(pDX, IDC_P_90,				m_p90);
	DDX_Control(pDX, IDC_P_0,				m_p0);
	DDX_Control(pDX, IDC_P_180,				m_p180);
	
	// Function Enable Or Not...
	DDX_Control(pDX, IDC_CCD_USE,			m_btnCCDUse);
	DDX_Control(pDX, IDC_CCD_SOCKET_USE,	m_btnCCDSocket);
	DDX_Control(pDX, IDC_ROTATOR_USE,		m_btnRotatorUse);
	DDX_Radio(pDX,	 IDC_N_90,				m_iAngle);

	DDX_Control(pDX, IDOK,					m_btnOK);
	DDX_Control(pDX, IDCANCEL,				m_btnCancel);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgExtendFunction, CDialog)
	//{{AFX_MSG_MAP(CDlgExtendFunction)
	ON_BN_CLICKED(IDC_CCD_SOCKET_USE,		OnCcdSocketUse)
	ON_BN_CLICKED(IDC_CCD_USE,				OnCcdUse)
	ON_BN_CLICKED(IDC_ROTATOR_USE,			OnRotatorUse)
	ON_BN_CLICKED(IDC_N_90,					OnN90)
	ON_BN_CLICKED(IDC_P_90,					OnP90)
	ON_BN_CLICKED(IDC_P_0,					OnP0)
	ON_BN_CLICKED(IDC_P_180,				OnP180)
	ON_WM_SHOWWINDOW()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgExtendFunction message handlers

void CDlgExtendFunction::OnOK() 
{
	if( !f.CheckEnaleChange() )
		return;

	//
	SaveData();

	//
	m.Info.bSubDlgOpen = false;
	f.UpdateButtonState();
	
	CDialog::OnOK();
}

void CDlgExtendFunction::OnCancel() 
{
	m.Info.bSubDlgOpen = false;
	f.UpdateButtonState();
	
	CDialog::OnCancel();
}

BOOL CDlgExtendFunction::PreTranslateMessage(MSG* pMsg) 
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

BOOL CDlgExtendFunction::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m.Info.bSubDlgOpen = true;
	f.UpdateButtonState();

	// init button 
	m_btnOK.SetIcon(IDI_SAVE);;
	m_btnOK.SetAlign(CButtonST::ST_ALIGN_VERT);;
	m_btnOK.SetFlat(FALSE);
	
	m_btnCancel.SetIcon(IDI_CANCEL);
	m_btnCancel.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnCancel.SetFlat(FALSE);

	if( m_file == "" )
		m_file = m.UI.FileMainTestSetting;
	LoadTesting( m_file );
	// Load Testing Setting refer File.

	//
	InitTips();
	
	//
	InitValue();

	//
	InitRotatorUI();

	//
	f.ChangeLanguage(GetSafeHwnd());

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgExtendFunction::UpdataExterndFunctionButton()
{
	//////////////////////////////////////////////////////////////////////
	// ­«³]¤¶­±
	RECT rt;
	::GetWindowRect(::GetDlgItem(m_hWnd, IDC_P_90), &rt);
	::MapWindowPoints(NULL, m_hWnd, (LPPOINT)&rt, 2);	

	RECT rtW[_ROTATOR_ICON];
	bool rtUse[_ROTATOR_ICON];
	for(int i=0;i<_ROTATOR_ICON;i++)
		rtUse[i] = false;

	//
	for(i=0;i<_ROTATOR_ICON;i++)
		rtW[i] = rt;
	
	//
	for(i=0;i<_ROTATOR_ICON;i++)
	{
		rtW[i].left		= ( rt.right - rt.left ) + rt.left	+ ( 68 * i ) + 10;
		rtW[i].right	= ( rt.right - rt.left ) + rt.right	+ ( 68 * i ) + 10;
	}

	// 0
	if( m.Setting.m_bEnableRotatorPreGuide == 1 )
	{
		for(i=0;i<_ROTATOR_ICON;i++)
		{
			if( !rtUse[i] )
			{
				rtUse[i] = true;
				m_p0.MoveWindow(&rtW[i]);
				break;
			}
		}
	}

	// 180
	if( m.Setting.m_bEnableRotatorTurn == 1 )
	{
		for(i=0;i<_ROTATOR_ICON;i++)
		{
			if( !rtUse[i] )
			{
				rtUse[i] = true;
				m_p180.MoveWindow(&rtW[i]);
				break;
			}
		}
	}
}
void CDlgExtendFunction::ReDrawRotatorUI()
{

}
// 1.0Ah
// Remove this and re-build new one
/*
void CDlgExtendFunction::ReDrawUI()
{
	// 0
	if( m.Setting.m_bEnableRotatorPreGuide == 1 )
		m_p0.ShowWindow( TRUE );
	else
		m_p0.ShowWindow( FALSE );

	// 180
	if( m.Setting.m_bEnableRotatorTurn == 1 )
		m_p180.ShowWindow( TRUE );
	else
		m_p180.ShowWindow( FALSE );

	// CCD Pin1
	if( m.Setting.m_bEnableCCDPin1 == 1 )
		m_btnCCDUse.ShowWindow( TRUE );
	else
		m_btnCCDUse.ShowWindow( FALSE );

	// CCD Socket
	if( m.Setting.m_bEnableCCDSocket == 1 )
		m_btnCCDSocket.ShowWindow( TRUE );
	else
		m_btnCCDSocket.ShowWindow( FALSE );
}
*/
// 1.0Ah
void CDlgExtendFunction::ReDrawUI()
{
	// 0
	if( m.Setting.m_bEnableRotatorPreGuide == 1 && 
		m_TestSetting.m_RotatorUse == 1 )
		m_p0.ShowWindow( TRUE );
	else
		m_p0.ShowWindow( FALSE );

	// 180
	if( m.Setting.m_bEnableRotatorTurn == 1 && 
		m_TestSetting.m_RotatorUse == 1 )
		m_p180.ShowWindow( TRUE );
	else
		m_p180.ShowWindow( FALSE );

	// +90
	if( m_TestSetting.m_RotatorUse == 1 )
		m_p90.ShowWindow( TRUE );
	else
		m_p90.ShowWindow( FALSE );

	// -90
	if( m_TestSetting.m_RotatorUse == 1 )
		m_n90.ShowWindow( TRUE );
	else
		m_n90.ShowWindow( FALSE );
	

	// CCD Pin1
	if( m.Setting.m_bEnableCCDPin1 == 1 )
		m_btnCCDUse.ShowWindow( TRUE );
	else
		m_btnCCDUse.ShowWindow( FALSE );

	// CCD Socket
	if( m.Setting.m_bEnableCCDSocket == 1 )
		m_btnCCDSocket.ShowWindow( TRUE );
	else
		m_btnCCDSocket.ShowWindow( FALSE );
}
void CDlgExtendFunction::SaveTesting(CString csFile)
{
	CString csFilePath;
	csFile = m.FilePath.TestSettingPath + csFile;

	f.SaveSetting(csFile, "Test Extend", "CCD Socket",	m_TestSetting.m_CCDSocketUse );
	f.SaveSetting(csFile, "Test Extend", "CCD",			m_TestSetting.m_CCDUse );
	f.SaveSetting(csFile, "Test Extend", "ROTATOR",		m_TestSetting.m_RotatorUse );
	f.SaveSetting(csFile, "Test Extend", "Angle",		m_TestSetting.m_Angle );
}
void CDlgExtendFunction::LoadTesting(CString csFile)
{
	CString csFilePath;
	csFile = m.FilePath.TestSettingPath + csFile;

	f.GetSetting(csFile, "Test Extend", "CCD Socket",	m_TestSetting.m_CCDSocketUse );
	f.GetSetting(csFile, "Test Extend", "CCD",			m_TestSetting.m_CCDUse );
	f.GetSetting(csFile, "Test Extend", "ROTATOR",		m_TestSetting.m_RotatorUse );
	f.GetSetting(csFile, "Test Extend", "Angle",		m_TestSetting.m_Angle );
}
void CDlgExtendFunction::InitRotatorUI()
{
	
}
void CDlgExtendFunction::InitValue()
{
	// CCD Use
	if( m_TestSetting.m_CCDUse == 1 )
		m_btnCCDUse.SetCheck(1);
	else
		m_btnCCDUse.SetCheck(0);

	// Rotator Use
	if( m_TestSetting.m_RotatorUse == 1 )
		m_btnRotatorUse.SetCheck(1);
	else
		m_btnRotatorUse.SetCheck(0);

	// CCD Socket Use
	if( m_TestSetting.m_CCDSocketUse == 1 )
		m_btnCCDSocket.SetCheck(1);
	else
		m_btnCCDSocket.SetCheck(0);

	//////////////////////////////////////////////////////////////

	// Angle
	m_iAngle = m_TestSetting.m_Angle;
	UpdateData( FALSE );
}
void CDlgExtendFunction::InitTips()
{

}
void CDlgExtendFunction::SaveData()
{
	// Save Testing 
	SaveTesting( m_file );
	f.LoadTestSetting();
}

void CDlgExtendFunction::OnCcdSocketUse() 
{
	if( m_btnCCDSocket.GetCheck() )
		m_TestSetting.m_CCDSocketUse = 1;
	else
		m_TestSetting.m_CCDSocketUse = 0;

	m_btnCCDSocket.Invalidate();	
}

void CDlgExtendFunction::OnCcdUse() 
{
	if( m_btnCCDUse.GetCheck() )
		m_TestSetting.m_CCDUse = 1;
	else
		m_TestSetting.m_CCDUse = 0;

	m_btnCCDUse.Invalidate();	
}

void CDlgExtendFunction::OnRotatorUse() 
{
	if( m_btnRotatorUse.GetCheck() )
		m_TestSetting.m_RotatorUse = 1;
	else
		m_TestSetting.m_RotatorUse = 0;

	m_btnRotatorUse.Invalidate();

	// 1.0Ah
	EnableRotatorUI( m_TestSetting.m_RotatorUse );
}

// 1.0Ah
void CDlgExtendFunction::EnableRotatorUI(int bEnable)
{
	if( bEnable == 1 )
	{
		BOOL bEnable = TRUE;
		m_n90.ShowWindow( bEnable );
		m_p90.ShowWindow( bEnable );

		if( m.Setting.m_bEnableRotatorPreGuide == 1 )
			m_p0.ShowWindow( bEnable );

		if( m.Setting.m_bEnableRotatorTurn == 1 )
			m_p180.ShowWindow( bEnable );
	}
	else
	{
		BOOL bEnable = FALSE;
		m_n90.ShowWindow( bEnable );
		m_p90.ShowWindow( bEnable );
		m_p0.ShowWindow( bEnable );
		m_p180.ShowWindow( bEnable );	
	}
}

void CDlgExtendFunction::OnN90() 
{
	UpdateData();
	m_TestSetting.m_Angle = m_iAngle;	// 0 (-90)

	m_n90.Invalidate();
	m_p90.Invalidate();
	m_p0.Invalidate();
	m_p180.Invalidate();	
}

void CDlgExtendFunction::OnP90() 
{
	UpdateData();
	m_TestSetting.m_Angle = m_iAngle;	// 1 (+90)

	m_n90.Invalidate();
	m_p90.Invalidate();
	m_p0.Invalidate();
	m_p180.Invalidate();
}

void CDlgExtendFunction::OnP0() 
{
	UpdateData();
	m_TestSetting.m_Angle = m_iAngle;	// 2 (0)

	m_n90.Invalidate();
	m_p90.Invalidate();
	m_p0.Invalidate();
	m_p180.Invalidate();	
}

void CDlgExtendFunction::OnP180() 
{
	UpdateData();
	m_TestSetting.m_Angle = m_iAngle;	// 3 (180)

	m_n90.Invalidate();
	m_p90.Invalidate();
	m_p0.Invalidate();
	m_p180.Invalidate();
}

void CDlgExtendFunction::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	if(bShow)
	{
		ReDrawUI();
		ReDrawRotatorUI();
		UpdataExterndFunctionButton();
	}

	CDialog::OnShowWindow(bShow, nStatus);	
}
