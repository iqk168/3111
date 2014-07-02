// DlgTrayRepeatStatus.cpp : implementation file
//

#include "stdafx.h"
#include "deer.h"
#include "DlgTrayRepeatStatus.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgTrayRepeatStatus dialog


CDlgTrayRepeatStatus::CDlgTrayRepeatStatus(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgTrayRepeatStatus::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgTrayRepeatStatus)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgTrayRepeatStatus::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgTrayRepeatStatus)
	DDX_Control(pDX, IDC_E_TRAY2,		m_wndTray2);
	DDX_Control(pDX, IDC_E_TRAY1,		m_wndTray1);
	DDX_Control(pDX, IDOK,				m_btnOK);
	DDX_Control(pDX, IDCANCEL,			m_btnCancel);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgTrayRepeatStatus, CDialog)
	//{{AFX_MSG_MAP(CDlgTrayRepeatStatus)
	ON_WM_TIMER()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgTrayRepeatStatus message handlers

BOOL CDlgTrayRepeatStatus::PreTranslateMessage(MSG* pMsg) 
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

void CDlgTrayRepeatStatus::OnTimer(UINT nIDEvent) 
{
	switch(nIDEvent)
	{
	case ID_TIME_TRAY_STATUS:
		{
			UpdataTrayStatus();
		}
		break;
	}
	
	CDialog::OnTimer(nIDEvent);
}
void CDlgTrayRepeatStatus::UpdataTrayStatus()
{
	if( pViewTray1 != NULL )
		pViewTray1->Invalidate(FALSE);
	if( pViewTray2 != NULL )
		pViewTray2->Invalidate(FALSE);
}
BOOL CDlgTrayRepeatStatus::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
//	m.Info.bSubDlgOpen = true;
//	f.UpdateButtonState();

	// init button 
	m_btnOK.SetIcon(IDI_SAVE);
	m_btnOK.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnOK.SetFlat(FALSE);
	
	m_btnCancel.SetIcon(IDI_CANCEL);
	m_btnCancel.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnCancel.SetFlat(FALSE);

	//
	InitTrayStatus();

	//
	SetTimer(ID_TIME_TRAY_STATUS, _Tray_Status_Timer, NULL);

	//
	CenterWindow();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
	//
void CDlgTrayRepeatStatus::InitTrayStatus()
{
	CRect rect1;
	m_wndTray1.GetClientRect( rect1 );		// Input 1
	CRect rect2;
	m_wndTray2.GetClientRect( rect2 );	// Output 1

	//
	// Tray 1
	pViewTray1 = new CViewRepeatTrayMotor();
	pViewTray1->SetType(0);
	pViewTray1->Create(NULL, "Tray 1", WS_CHILD | WS_VISIBLE, rect1, 
		(CWnd *)&m_wndTray1, IDC_E_TRAY1);		// Tray 1

	// Tray 2
	pViewTray2 = new CViewRepeatTrayMotor();
	pViewTray2->SetType(1);
	pViewTray2->Create(NULL, "Tray 2", WS_CHILD | WS_VISIBLE, rect1, 
		(CWnd *)&m_wndTray2, IDC_E_TRAY2);		// Tray 2
}

void CDlgTrayRepeatStatus::OnOK() 
{
//	m.Info.bSubDlgOpen = false;
//	f.UpdateButtonState();

	CDialog::OnOK();
}

void CDlgTrayRepeatStatus::OnCancel() 
{
//	m.Info.bSubDlgOpen = false;
//	f.UpdateButtonState();

	CDialog::OnCancel();
}

void CDlgTrayRepeatStatus::OnDestroy() 
{
	if( pViewTray1 != NULL )
		delete pViewTray1;
	if( pViewTray2 != NULL )
		delete pViewTray2;

	CDialog::OnDestroy();	
}
