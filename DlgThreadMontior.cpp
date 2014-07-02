// DlgThreadMontior.cpp : implementation file
//

#include "stdafx.h"
#include "deer.h"
#include "DlgThreadMontior.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgThreadMontior dialog


CDlgThreadMontior::CDlgThreadMontior(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgThreadMontior::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgThreadMontior)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgThreadMontior::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgThreadMontior)
	DDX_Control(pDX, IDC_MANUAL_CTRL,			m_wndManual);
	DDX_Control(pDX, IDC_TESTER_CTRL,			m_wndTesterCtrl);	
	DDX_Control(pDX, IDC_INSPECT_CTRL,			m_wndInspectCtrl);
	DDX_Control(pDX, IDC_INSERTER_CTRL,			m_wndInserterCtrl);		
	DDX_Control(pDX, IDC_ARM_CTRL,				m_wndArmCtrl);
	DDX_Control(pDX, IDC_SYSTEM_STATUS,			m_wndSystemStatus);
	DDX_Control(pDX, IDC_IO,					m_wndIO);
	DDX_Control(pDX, IDC_ERR_CTRL,				m_wndErrCtrl);
	DDX_Control(pDX, IDC_THREAD_COUNTER,		m_wndThreadCounter);	
	DDX_Control(pDX, IDOK,						m_btnOK);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgThreadMontior, CDialog)
	//{{AFX_MSG_MAP(CDlgThreadMontior)
	ON_WM_CLOSE()
	ON_WM_DESTROY()
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgThreadMontior message handlers

BOOL CDlgThreadMontior::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// init button 
	m_btnOK.SetIcon(IDI_OK);;
	m_btnOK.SetAlign(CButtonST::ST_ALIGN_VERT);;
	m_btnOK.SetFlat(FALSE);
	
	SetTimer(ID_TIME_THREAD_MONITOR, 100, NULL);

	f.ChangeLanguage(GetSafeHwnd());

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgThreadMontior::OnClose() 
{
//	m.Info.bSubDlgOpen = false;
//	f.UpdateButtonState();
	
	CDialog::OnClose();
}

void CDlgThreadMontior::OnDestroy() 
{
//	m.Info.bSubDlgOpen = false;
//	f.UpdateButtonState();

	KillTimer(ID_TIME_THREAD_MONITOR);

	CDialog::OnDestroy();	
}

void CDlgThreadMontior::OnTimer(UINT nIDEvent) 
{
	switch(nIDEvent)
	{
	case ID_TIME_THREAD_MONITOR:
		UpdateStatus();
		break;
	default:
		break;
	}
	
	CDialog::OnTimer(nIDEvent);
}

void CDlgThreadMontior::UpdateStatus()
{
	// System Status
	CString cs;
	cs.Format("%d - %s", m.Info.iStatus, GetSystemText(m.Info.iStatus));
	m_wndSystemStatus.SetWindowText(cs);
	// System Control
	m_wndErrCtrl.SetWindowText(GetText(m.ThStatus.ErrCtrl));
	m_wndIO.SetWindowText(GetText(m.ThStatus.IO, m.Err.IO.Code));
	// Motion CWinthread
	m_wndTesterCtrl.SetWindowText(GetText(m.ThStatus.TesterCtrl,		m.Err.Tester.Code ));
	m_wndInspectCtrl.SetWindowText(GetText(m.ThStatus.InspectCtrl,		m.Err.Inspect.Code));
	m_wndInserterCtrl.SetWindowText(GetText(m.ThStatus.InserterCtrl,	m.Err.Inserter.Code));	
	m_wndArmCtrl.SetWindowText(GetText(m.ThStatus.ArmCtrl,				m.Err.Arm.Code));
	m_wndManual.SetWindowText(GetText(m.ThStatus.ManualCtrl,			m.Err.Manual.Code));

	// Check Thread Counter
	CString csThreadCount = "";
	csThreadCount.Format("%d", m.Info.iThreadCount );
	m_wndThreadCounter.SetWindowText( csThreadCount );
}

CString CDlgThreadMontior::GetSystemText(int SystemStatus)
{

//	enReady = 0x11,								
//	enInitial = 0x20, enUninitial = 0x21,		
//	enCycle = 0x30, enCycleStop = 0x31,
//	enManual = 0x40, enManualStop = 0x41,
//	enOverride 0x50, enOverrideStop = 0x51,
//  enOneCycle = 0x60, enOneCycleStop = 0x61,
	// Please check define in Deer.h

	CString csSystemStatus ="";
	switch(SystemStatus)
	{
	case theApp.enReady:	
		csSystemStatus = "Ready";
		break;
	case theApp.enInitial:
		csSystemStatus = "Initial";
		break;
	case theApp.enUninitial:
		csSystemStatus = "Uninitial";
		break;
	case theApp.enCycle:
		csSystemStatus = "Cycle";
		break;
	case theApp.enCycleStop:
		csSystemStatus = "CycleStop";
		break;
	case theApp.enOneCycle:
		csSystemStatus = "One Cycle";
		break;
	case theApp.enOneCycleStop:
		csSystemStatus = "One Cycle Stop";
		break;
	case theApp.enOverride:
		csSystemStatus = "Override";
		break;
	case theApp.enOverrideStop:
		csSystemStatus = "Override Stop";
		break;
	case theApp.enManual:
		csSystemStatus = "Manual";
		break;
	case theApp.enManualStop:
		csSystemStatus = "ManualStop";
		break;
	default:
		break;
	}	
	return csSystemStatus;
}

CString CDlgThreadMontior::GetText(tagThreadCode value, long code)
{
	CString cs;
	if(code > 0)
		cs.Format("%d = 0x%x, Err = 0x%x", value.times, value.line, code);
	else
		cs.Format("%d = 0x%x", value.times, value.line);
	return cs;
}
void CDlgThreadMontior::OnCancel() 
{	
	m.Info.bSubDlgOpen = false;
	f.UpdateButtonState();

//	CDialog::OnCancel();
}

void CDlgThreadMontior::OnOK() 
{
//	m.Info.bSubDlgOpen = false;
//	f.UpdateButtonState();

	CDialog::OnOK();
}
BOOL CDlgThreadMontior::PreTranslateMessage(MSG* pMsg) 
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
