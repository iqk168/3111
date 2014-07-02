// DlgTrayMapUI.cpp : implementation file
//

#include "stdafx.h"
#include "deer.h"
#include "DlgTrayMapUI.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgTrayMapUI dialog


CDlgTrayMapUI::CDlgTrayMapUI(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgTrayMapUI::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgTrayMapUI)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgTrayMapUI::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgTrayMapUI)
	DDX_Control(pDX, IDC_TRAY_SPEC_COLOR_BK,			m_wndTraySpecColorBk);
	DDX_Control(pDX, IDOK,								m_btnOK);
	DDX_Control(pDX, IDCANCEL,							m_btnCancel);
	DDX_Text(pDX, IDC_TRAY_SPEC_LEFT_SIDE,				m_dTraySpecLeftSide);
	DDX_Text(pDX, IDC_TRAY_SPEC_TOP_SIDE,				m_dTraySpecTopSide);
	DDX_Text(pDX, IDC_TRAY_SPEC_IC_SIDE,				m_dTraySpecICSide);
	DDX_Text(pDX, IDC_TRAY_SPEC_TEXT_UP_SIDE,			m_dTraySpecTextUpSide);
	DDX_Text(pDX, IDC_TRAY_SPEC_TEXT_LEFT_SIDE,			m_dTraySpecTextLeftSide);
	DDX_Control(pDX, IDC_TEXT_BREAK,					m_iTraySpecTextBreak);
	DDX_Control(pDX, IDC_TEXT_SIZE,						m_iTraySpecTextSize);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgTrayMapUI, CDialog)
	//{{AFX_MSG_MAP(CDlgTrayMapUI)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgTrayMapUI message handlers

void CDlgTrayMapUI::OnOK() 
{
	//
	SaveData();

	//
	m.Info.bSubDlgOpen = false;
	f.UpdateButtonState();	

	CDialog::OnOK();
}

void CDlgTrayMapUI::OnCancel() 
{
	m.Info.bSubDlgOpen = false;
	f.UpdateButtonState();	
	
	CDialog::OnCancel();
}

BOOL CDlgTrayMapUI::PreTranslateMessage(MSG* pMsg) 
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

BOOL CDlgTrayMapUI::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m.Info.bSubDlgOpen = true;
	f.UpdateButtonState();

	// init button 
	m_btnOK.SetIcon(IDI_SAVE);;
	m_btnOK.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnOK.SetFlat(FALSE);
	
	m_btnCancel.SetIcon(IDI_CANCEL);
	m_btnCancel.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnCancel.SetFlat(FALSE);
	
	//
	InitColorCombox();

	//
	InitValue();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
void CDlgTrayMapUI::InitColorCombox()
{
	//
	m_wndTraySpecColorBk.ResetContent();
/*
#define ST_WHITE		RGB(255, 255, 255)			
#define ST_RED			RGB(255, 0, 0)				
#define ST_GREEN		RGB(0, 255, 0)				
#define ST_BLUE			RGB(0, 0, 255)				
#define ST_CYAN			RGB(0, 255, 255)
#define ST_YELLOW		RGB(255, 255, 0)
*/
	CString cs = _T("");
	cs.Format("White");
	m_wndTraySpecColorBk.AddColor( cs, ST_WHITE );	

	cs.Format("Red");
	m_wndTraySpecColorBk.AddColor( cs, ST_RED );	

	cs.Format("Green");
	m_wndTraySpecColorBk.AddColor( cs, ST_GREEN );	

	cs.Format("Blue");
	m_wndTraySpecColorBk.AddColor( cs, ST_BLUE );	

	cs.Format("Cyan");
	m_wndTraySpecColorBk.AddColor( cs, ST_CYAN );	

	cs.Format("Yellow");
	m_wndTraySpecColorBk.AddColor( cs, ST_YELLOW );	
}
void CDlgTrayMapUI::SaveData()
{
	UpdateData();

	// TrayMap
	m.Setting.m_dTraySpecLeftSide			= m_dTraySpecLeftSide;
	m.Setting.m_dTraySpecTopSide			= m_dTraySpecTopSide;
	m.Setting.m_dTraySpecICSide				= m_dTraySpecICSide;
	m.Setting.m_dTraySpecTextUpSide			= m_dTraySpecTextUpSide;
	m.Setting.m_dTraySpecTextLeftSide		= m_dTraySpecTextLeftSide;
	m.Setting.m_iTraySpecTextSize			= m_iTraySpecTextSize.GetCurSel();
	m.Setting.m_iTraySpecTextBreak			= m_iTraySpecTextBreak.GetCurSel();
	m.Setting.m_iTraySpecBkColor			= m_wndTraySpecColorBk.GetSelectedColorValue();

	f.SaveSystemSetting();
}
void CDlgTrayMapUI::InitValue()
{
	// Tray Map
	m_dTraySpecLeftSide			= m.Setting.m_dTraySpecLeftSide;
	m_dTraySpecTopSide			= m.Setting.m_dTraySpecTopSide;
	m_dTraySpecICSide			= m.Setting.m_dTraySpecICSide;
	m_dTraySpecTextUpSide		= m.Setting.m_dTraySpecTextUpSide;
	m_dTraySpecTextLeftSide		= m.Setting.m_dTraySpecTextLeftSide;
	m_iTraySpecTextSize.SetCurSel( m.Setting.m_iTraySpecTextSize );
	m_iTraySpecTextBreak.SetCurSel( m.Setting.m_iTraySpecTextBreak );
	m_wndTraySpecColorBk.SetSelectedColorValue( m.Setting.m_iTraySpecBkColor );

	UpdateData(FALSE);
}
