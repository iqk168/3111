// DlgGearRation.cpp : implementation file
//

#include "stdafx.h"
#include "deer.h"
#include "DlgGearRation.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgGearRation dialog


CDlgGearRation::CDlgGearRation(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgGearRation::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgGearRation)
	m_dXGearRation =			m.m_Ratio.X_GearRation;
	m_dYGearRation =			m.m_Ratio.Y_GearRation;
	m_dZGearRation =			m.m_Ratio.Z_GearRation;
	m_dInserterGearRation =		m.m_Ratio.Inserter_GearRation;

	//}}AFX_DATA_INIT
}


void CDlgGearRation::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgGearRation)
	DDX_Control(pDX, IDOK,					m_btnOK);
	DDX_Control(pDX, IDCANCEL,				m_btnCancel);
	DDX_Text(pDX, IDC_X_GEAR_RATION,		m_dXGearRation);
	DDX_Text(pDX, IDC_Y_GEAR_RATION,		m_dYGearRation);
	DDX_Text(pDX, IDC_Z_GEAR_RATION,		m_dZGearRation);
	DDX_Text(pDX, IDC_INSERTER_GEAR_RATION, m_dInserterGearRation);

	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgGearRation, CDialog)
	//{{AFX_MSG_MAP(CDlgGearRation)
	ON_WM_DESTROY()
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgGearRation message handlers

void CDlgGearRation::OnOK() 
{
	m.Info.bSubDlgOpen = false;
	f.UpdateButtonState();
	
	CDialog::OnOK();
}

void CDlgGearRation::OnCancel() 
{

	m.Info.bSubDlgOpen = false;
	f.UpdateButtonState();
	
	CDialog::OnCancel();
}

BOOL CDlgGearRation::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m.Info.bSubDlgOpen = true;
	f.UpdateButtonState();

	// init button 
	m_btnOK.SetIcon(IDI_OK);;
	m_btnOK.SetAlign(CButtonST::ST_ALIGN_VERT);;
	m_btnOK.SetFlat(FALSE);
	
	m_btnCancel.SetIcon(IDI_CANCEL);
	m_btnCancel.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnCancel.SetFlat(FALSE);

	f.ChangeLanguage(GetSafeHwnd());
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgGearRation::OnDestroy() 
{
	m.Info.bSubDlgOpen = false;
	f.UpdateButtonState();

	CDialog::OnDestroy();	
}

void CDlgGearRation::OnClose() 
{
	m.Info.bSubDlgOpen = false;
	f.UpdateButtonState();
	
	CDialog::OnClose();
}

BOOL CDlgGearRation::PreTranslateMessage(MSG* pMsg) 
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
