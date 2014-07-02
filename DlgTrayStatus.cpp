// DlgTrayStatus.cpp : implementation file
//

#include "stdafx.h"
#include "deer.h"
#include "DlgTrayStatus.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgTrayStatus dialog


CDlgTrayStatus::CDlgTrayStatus(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgTrayStatus::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgTrayStatus)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgTrayStatus::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgTrayStatus)
	DDX_Control(pDX, IDC_TRAY_OUTPUT1,		m_wndOutputTray1);
	DDX_Control(pDX, IDC_TRAY_INPUT1,		m_wndInputTray1);
	DDX_Control(pDX, IDOK,					m_btnOK);
	DDX_Control(pDX, IDCANCEL,				m_btnCancel);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgTrayStatus, CDialog)
	//{{AFX_MSG_MAP(CDlgTrayStatus)
	ON_WM_TIMER()
	ON_WM_SHOWWINDOW()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgTrayStatus message handlers

void CDlgTrayStatus::OnOK() 
{
	
	CDialog::OnOK();
}

void CDlgTrayStatus::OnCancel() 
{
	
	CDialog::OnCancel();
}

BOOL CDlgTrayStatus::PreTranslateMessage(MSG* pMsg) 
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

BOOL CDlgTrayStatus::OnInitDialog() 
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
	InitTips();

	//
	InitTrayStatus();

	//
	InitValue();

	//
	f.ChangeLanguage(GetSafeHwnd());

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgTrayStatus::InitTrayStatus()
{
	CRect rect1;
	m_wndInputTray1.GetClientRect( rect1 );		// Input 1
	CRect rect2;
	m_wndOutputTray1.GetClientRect( rect2 );	// Output 1

	//
	// Input
	pViewTrayInput1 = new CViewTrayMotor();
	pViewTrayInput1->SetType(0);
	if( m.TraySpec.m_InputUseChipTray == 1 )
		pViewTrayInput1->SetChipMode(1);
	else
		pViewTrayInput1->SetChipMode(0);
	pViewTrayInput1->Create(NULL, "Input1", WS_CHILD | WS_VISIBLE, rect1, 
		(CWnd *)&m_wndInputTray1, IDC_TRAY_INPUT1);		// Input Tray

	// Output 
	pViewTrayOutput1 = new CViewTrayMotor();
	pViewTrayOutput1->SetType(1);
	if( m.TraySpec.m_OutputUseChipTray == 1 )
		pViewTrayOutput1->SetChipMode(1);
	else
		pViewTrayOutput1->SetChipMode(0);
	pViewTrayOutput1->Create(NULL, "Output1", WS_CHILD | WS_VISIBLE, rect2, 
		(CWnd *)&m_wndOutputTray1, IDC_TRAY_OUTPUT1);	// Output 1 Tary
}
void CDlgTrayStatus::ChangeTrayStatus()
{

}
void CDlgTrayStatus::UpdateStatus()
{
	if( pViewTrayInput1 != NULL )
		pViewTrayInput1->Invalidate(FALSE);
	if( pViewTrayOutput1 != NULL )
		pViewTrayOutput1->Invalidate(FALSE);
}

void CDlgTrayStatus::InitValue()
{
	// 設定掃描頻率
	if( m.TimerSetting.iScanTrayStatus > 0 )
		SetTimer(ID_TIME_STATUS, m.TimerSetting.iScanTrayStatus , NULL);
	else
		SetTimer(ID_TIME_STATUS, 100 , NULL);	
}
void CDlgTrayStatus::InitTips()
{
	// Tips 
	// Init Tips
	m_ToolTip.Create(this);
	m_ToolTip.SetMaxTipWidth(800);
	m_ToolTip.SetDelayTime( TTDT_AUTOPOP, 10000 );
	m_ToolTip.SetDelayTime( TTDT_INITIAL, 25 );
	m_ToolTip.EnableToolTips(true);

//	m_ToolTip.AddTool( GetDlgItem(IDC_ALIGNMENT_INPUT_READ),	_T("Read ArmXYZ Motor RCount Value With Input Alignment Position") );

}
void CDlgTrayStatus::OnTimer(UINT nIDEvent) 
{
	switch(nIDEvent)
	{
	case ID_TIME_STATUS:
		UpdateStatus();
		break;
	}	
	CDialog::OnTimer(nIDEvent);
}

void CDlgTrayStatus::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	if(bShow)
	{
		// 重新. 設定掃描頻率
		if( m.TimerSetting.iScanTrayStatus > 0 )
			SetTimer(ID_TIME_STATUS, m.TimerSetting.iScanTrayStatus , NULL);
		else
			SetTimer(ID_TIME_STATUS, 100 , NULL);
	}

	CDialog::OnShowWindow(bShow, nStatus);
}

void CDlgTrayStatus::OnDestroy() 
{
	if( pViewTrayInput1 != NULL )
		delete pViewTrayInput1;

	if( pViewTrayOutput1 != NULL )
		delete pViewTrayOutput1;

	CDialog::OnDestroy();	
}
