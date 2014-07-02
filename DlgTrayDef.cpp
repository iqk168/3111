// DlgTrayDef.cpp : implementation file
//

#include "stdafx.h"
#include "deer.h"
#include "DlgTrayDef.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgTrayDef dialog


CDlgTrayDef::CDlgTrayDef(bool bUser, CWnd* pParent /*=NULL*/)
	: CDialog(CDlgTrayDef::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgTrayDef)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	m_bUser = bUser;

	m_TrayFileDefColor = m.m_TrayFileDefColor;
}


void CDlgTrayDef::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgTrayDef)
	DDX_Control(pDX, IDC_E_B,			m_wndB);
	DDX_Control(pDX, IDC_E_G,			m_wndG);
	DDX_Control(pDX, IDC_E_R,			m_wndR);
	DDX_Control(pDX, IDC_SLIDER_B,		m_SilB);
	DDX_Control(pDX, IDC_SLIDER_G,		m_SilG);
	DDX_Control(pDX, IDC_SLIDER_R,		m_SilR);
	//
	DDX_Control(pDX, IDC_E_TRI,			m_wndETRI);
	DDX_Control(pDX, IDC_E_PTC,			m_wndEPTC);
	DDX_Control(pDX, IDC_E_HEATER,		m_wndEHeater);
	DDX_Control(pDX, IDC_E_ATC,			m_wneEATC);
	DDX_Control(pDX, IDC_E_AMBIENT,		m_wndEAmbient);
	DDX_Control(pDX, IDC_TRAY_FILE_DEF, m_cbxTrayFileDef);
	DDX_Control(pDX, IDOK,				m_btnOK);
	DDX_Control(pDX, IDCANCEL,			m_btnCancel);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgTrayDef, CDialog)
	//{{AFX_MSG_MAP(CDlgTrayDef)
	ON_CBN_SELCHANGE(IDC_TRAY_FILE_DEF, OnSelchangeTrayFileDef)
	ON_NOTIFY(NM_OUTOFMEMORY, IDC_SLIDER_R, OnOutofmemorySliderR)
	ON_NOTIFY(NM_OUTOFMEMORY, IDC_SLIDER_G, OnOutofmemorySliderG)
	ON_NOTIFY(NM_OUTOFMEMORY, IDC_SLIDER_B, OnOutofmemorySliderB)
	ON_WM_HSCROLL()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgTrayDef message handlers

void CDlgTrayDef::OnOK() 
{
	SaveData();

	m.Info.bSubDlgOpen = false;
	f.UpdateButtonState();
	
	CDialog::OnOK();
}

void CDlgTrayDef::OnCancel() 
{
	m.Info.bSubDlgOpen = false;
	f.UpdateButtonState();
	
	CDialog::OnCancel();
}
void CDlgTrayDef::SaveData()
{
	m.m_TrayFileDefColor = m_TrayFileDefColor;
	f.SaveTrayFileDefColor();
}
void CDlgTrayDef::InitTrayFileDef()
{
	if( m_bUser )
	{
		int iCount = 0;
		m_cbxTrayFileDef.InsertString(iCount, "Heater");
		iCount++;
		m_cbxTrayFileDef.InsertString(iCount, "Ambit");
		iCount++;
		if( m.Setting.m_bEnableATCModule == 1 )
		{
			m_cbxTrayFileDef.InsertString(iCount, "ATCModule");
			iCount++;
		}
		if( m.Setting.m_bEnableTriTempModule == 1 )
		{
			m_cbxTrayFileDef.InsertString(iCount, "Tri-Temperature");
			iCount++;
		}
		if( m.Setting.m_bEnablePTCModule == 1 )
		{
			m_cbxTrayFileDef.InsertString(iCount, "PTCModule");
			iCount++;
		}
	}
	else
	{
		m_cbxTrayFileDef.InsertString(0, "Heater");
		m_cbxTrayFileDef.InsertString(1, "Ambit");
		m_cbxTrayFileDef.InsertString(2, "ATCModule");
		m_cbxTrayFileDef.InsertString(3, "Tri-Temperature");
		m_cbxTrayFileDef.InsertString(4, "PTCModule");	
	}
	m_cbxTrayFileDef.SetCurSel(0);
	SetColorSilderValue( m_TrayFileDefColor.m_colHeater );
}
void CDlgTrayDef::InitColorSilder()
{
	//
	m_SilR.SetRange( 0, 255, FALSE );
	m_SilG.SetRange( 0, 255, FALSE );
	m_SilB.SetRange( 0, 255, FALSE );

	//
	int iR = 128;
	m_SilR.SetPos( iR );
	int iG = 128;
	m_SilG.SetPos( iG );
	int iB = 128;
	m_SilB.SetPos( iB );

	//
	iR = m_SilR.GetPos();
	iG = m_SilG.GetPos();
	iB = m_SilB.GetPos();

	CString csR = _T("");
	CString csG = _T("");
	CString csB = _T("");

	csR.Format("%d", iR );
	m_wndR.SetWindowText( csR );

	csG.Format("%d", iG );
	m_wndG.SetWindowText( csG );

	csB.Format("%d", iB );
	m_wndB.SetWindowText( csB );

	//
	COLORREF RCOLOR = RGB( iR, iG, iB );
}
void CDlgTrayDef::InitControl()
{
	if( m_bUser )
	{
		// ATC Module
		if( m.Setting.m_bEnableATCModule == 1 )
		{
			GetDlgItem(IDC_STATIC_ATC_MOD)->ShowWindow( TRUE );
			GetDlgItem(IDC_E_ATC)->ShowWindow( TRUE );
		}
		else
		{
			GetDlgItem(IDC_STATIC_ATC_MOD)->ShowWindow( FALSE );
			GetDlgItem(IDC_E_ATC)->ShowWindow( FALSE );	
		}
		
		// PTC Module
		if( m.Setting.m_bEnablePTCModule == 1 )
		{
			GetDlgItem(IDC_STATIC_PTC_MOD)->ShowWindow( TRUE );
			GetDlgItem(IDC_E_PTC)->ShowWindow( TRUE );
		}
		else
		{
			GetDlgItem(IDC_STATIC_PTC_MOD)->ShowWindow( FALSE );
			GetDlgItem(IDC_E_PTC)->ShowWindow( FALSE );	
		}

		// Tri-Temperature
		if( m.Setting.m_bEnableTriTempModule == 1 )
		{
			GetDlgItem(IDC_STATIC_TRI_MOD)->ShowWindow( TRUE );
			GetDlgItem(IDC_E_TRI)->ShowWindow( TRUE );
		}
		else
		{
			GetDlgItem(IDC_STATIC_TRI_MOD)->ShowWindow( FALSE );
			GetDlgItem(IDC_E_TRI)->ShowWindow( FALSE );	
		}
	}
}
void CDlgTrayDef::InitTrayFileColor()
{
	m_wndETRI.SetNewBkColor( m_TrayFileDefColor.m_colTriTemperature );
	m_wndEPTC.SetNewBkColor( m_TrayFileDefColor.m_colPTCModule );
	m_wndEHeater.SetNewBkColor( m_TrayFileDefColor.m_colHeater );
	m_wneEATC.SetNewBkColor( m_TrayFileDefColor.m_colATCModule );
	m_wndEAmbient.SetNewBkColor( m_TrayFileDefColor.m_colAmbit );
}

int CDlgTrayDef::GetColorSilderValue()
{
	int iColor = 0;

	//
	int iR = m_SilR.GetPos();
	int iG = m_SilG.GetPos();
	int iB = m_SilB.GetPos();

	CString csR = _T("");
	CString csG = _T("");
	CString csB = _T("");

	csR.Format("%d", iR );
	m_wndR.SetWindowText( csR );

	csG.Format("%d", iG );
	m_wndG.SetWindowText( csG );

	csB.Format("%d", iB );
	m_wndB.SetWindowText( csB );

	//
	COLORREF RCOLOR = RGB( iB, iG, iR );

	//
	iColor = RCOLOR;

	//
	ChangeColorSilder( iColor );

	return iColor;
}
void CDlgTrayDef::SetColorSilderValue(int iColor)
{
	int Blue;
	int Green;
	int Red;

	ParseColor( iColor, Red, Green, Blue );

	int iR = Red;
	m_SilR.SetPos( iR );
	int iG = Green;
	m_SilG.SetPos( iG );
	int iB = Blue;
	m_SilB.SetPos( iB );

	CString csR = _T("");
	CString csG = _T("");
	CString csB = _T("");

	csR.Format("%d", iR );
	m_wndR.SetWindowText( csR );

	csG.Format("%d", iG );
	m_wndG.SetWindowText( csG );

	csB.Format("%d", iB );
	m_wndB.SetWindowText( csB );

	//	
	COLORREF RCOLOR = RGB( iB, iG, iR );	
}
void CDlgTrayDef::ParseColor(int Color, int &R, int &G, int &B)
{
	int Blue	=	Color & 255;
	int Green	=	(Color >> 8) & 255;
	int Red		=   (Color >> 16) & 255;

	R = Red;
	G = Green;
	B = Blue;
}
BOOL CDlgTrayDef::PreTranslateMessage(MSG* pMsg) 
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

BOOL CDlgTrayDef::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m.Info.bSubDlgOpen = true;
	f.UpdateButtonState();

	// init button 
	m_btnOK.SetIcon(IDI_SAVE);
	m_btnOK.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnOK.SetFlat(FALSE);
	
	m_btnCancel.SetIcon(IDI_CANCEL);
	m_btnCancel.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnCancel.SetFlat(FALSE);

	//
	InitColorSilder();

	//
	InitTrayFileDef();

	//
	InitTrayFileColor();

	//
	InitControl();

	//
	f.SetTitleExtend(this, theApp.enTtileMachineFile );

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgTrayDef::OnSelchangeTrayFileDef() 
{
	int iSel = m_cbxTrayFileDef.GetCurSel();

	if(iSel < 0 )
		return;

	if( iSel == theApp.enHeater )
		SetColorSilderValue( m_TrayFileDefColor.m_colHeater );
	else if( iSel == theApp.enAmbit )
		SetColorSilderValue( m_TrayFileDefColor.m_colAmbit );
	else if( iSel == theApp.enATCMoudle )
		SetColorSilderValue( m_TrayFileDefColor.m_colATCModule );
	else if( iSel == theApp.enTriTemperature )
		SetColorSilderValue( m_TrayFileDefColor.m_colTriTemperature );
	else if( iSel == theApp.enPTCMoudle )
		SetColorSilderValue( m_TrayFileDefColor.m_colPTCModule );
	else
		; // Nerver
}
void CDlgTrayDef::ChangeColorSilder(COLORREF color)
{
	int iSel = m_cbxTrayFileDef.GetCurSel();
	if(iSel < 0 )
		return;

	if( iSel == theApp.enHeater )
	{
		m_wndEHeater.SetNewBkColor( color );
		m_TrayFileDefColor.m_colHeater = color;
	}
	else if( iSel == theApp.enAmbit )
	{
		m_wndEAmbient.SetNewBkColor( color );
		m_TrayFileDefColor.m_colAmbit = color;
	}
	else if( iSel == theApp.enATCMoudle )
	{
		m_wneEATC.SetNewBkColor( color );
		m_TrayFileDefColor.m_colATCModule = color;
	}
	else if( iSel == theApp.enTriTemperature )
	{
		m_wndETRI.SetNewBkColor( color );
		m_TrayFileDefColor.m_colTriTemperature = color;
	}
	else if( iSel == theApp.enPTCMoudle )
	{
		m_wndEPTC.SetNewBkColor( color );
		m_TrayFileDefColor.m_colPTCModule = color;
	}
	else
		; // Nerve

}
void CDlgTrayDef::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// TODO: Add your message handler code here and/or call default
	// We catch ON_WM_HSCROLL Event from Windows operaton system.
	GetColorSilderValue();

	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}
void CDlgTrayDef::OnOutofmemorySliderR(NMHDR* pNMHDR, LRESULT* pResult) 
{
	*pResult = 0;
}

void CDlgTrayDef::OnOutofmemorySliderG(NMHDR* pNMHDR, LRESULT* pResult) 
{
	*pResult = 0;
}

void CDlgTrayDef::OnOutofmemorySliderB(NMHDR* pNMHDR, LRESULT* pResult) 
{
	*pResult = 0;
}
