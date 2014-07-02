// DlgCylinderLifeTimeTool.cpp : implementation file
//

#include "stdafx.h"
#include "deer.h"
#include "DlgCylinderLifeTimeTool.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgCylinderLifeTimeTool dialog


CDlgCylinderLifeTimeTool::CDlgCylinderLifeTimeTool(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgCylinderLifeTimeTool::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgCylinderLifeTimeTool)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	m_lShHomeCount = 0;
	m_lShPPCount = 0;
	m_lShCounter = 0;
	m_bEnableShLife = false;
	m_dShDelayTime = 0.0;

	m_lRoNNCount = 0;
	m_lRoPPCount = 0;
	m_lRoCounter = 0;
	m_bEnableRoLife = false;
	m_dRoDelayTime = 0.0;
}


void CDlgCylinderLifeTimeTool::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgCylinderLifeTimeTool)
	DDX_Control(pDX, IDC_R_RO_P,			m_wndRoPP);
	DDX_Control(pDX, IDC_R_RO_N,			m_wndRoNN);
	DDX_Control(pDX, IDC_R_RO_DELAY,		m_wndRoDelayTime);
	DDX_Control(pDX, IDC_R_RO_COUNTER,		m_wndRoCounter);
	DDX_Control(pDX, IDC_F_RO_CLEAR,		m_btnRoClear);
	DDX_Control(pDX, IDC_F_RO_STOP,			m_btnRoStop);
	DDX_Control(pDX, IDC_F_RO_REPORT,		m_btnRoReport);
	DDX_Control(pDX, IDC_F_RO_GO,			m_btnRoGo);
	//
	DDX_Control(pDX, IDC_R_SH_COUNTER,		m_wndShCounter);
	DDX_Control(pDX, IDC_R_SH_DELAY,		m_wndShDelayTime);
	DDX_Control(pDX, IDC_F_SH_CLEAR,		m_btnShClear);
	DDX_Control(pDX, IDC_R_SH_PP,			m_wndShPP);
	DDX_Control(pDX, IDC_R_SH_HOME,			m_wndShHome);
	DDX_Control(pDX, IDC_F_SH_STOP,			m_btnShStop);
	DDX_Control(pDX, IDC_F_SH_REPORT,		m_btnShReport);
	DDX_Control(pDX, IDC_F_SH_GO,			m_btnShGo);
	DDX_Control(pDX, IDOK,					m_btnOK);
	DDX_Control(pDX, IDCANCEL,				m_btnCancel);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgCylinderLifeTimeTool, CDialog)
	//{{AFX_MSG_MAP(CDlgCylinderLifeTimeTool)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_F_SH_GO,			OnFShGo)
	ON_BN_CLICKED(IDC_F_SH_STOP,		OnFShStop)
	ON_BN_CLICKED(IDC_F_SH_CLEAR,		OnFShClear)
	ON_BN_CLICKED(IDC_F_SH_REPORT,		OnFShReport)
	ON_BN_CLICKED(IDC_F_RO_GO,			OnFRoGo)
	ON_BN_CLICKED(IDC_F_RO_STOP,		OnFRoStop)
	ON_BN_CLICKED(IDC_F_RO_CLEAR,		OnFRoClear)
	ON_BN_CLICKED(IDC_F_RO_REPORT,		OnFRoReport)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgCylinderLifeTimeTool message handlers

BOOL CDlgCylinderLifeTimeTool::PreTranslateMessage(MSG* pMsg) 
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

BOOL CDlgCylinderLifeTimeTool::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// init button 
	m_btnOK.SetIcon(IDI_OK);;
	m_btnOK.SetAlign(CButtonST::ST_ALIGN_VERT);;
	m_btnOK.SetFlat(FALSE);
	
	m_btnCancel.SetIcon(IDI_CANCEL);
	m_btnCancel.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnCancel.SetFlat(FALSE);	
	
	// Shuttle 
	UpDataShValu();

	// Rotator
	UpDataRoValu();

	InitValue();

	CenterWindow();

	f.ChangeLanguage(GetSafeHwnd());

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
void CDlgCylinderLifeTimeTool::InitValue()
{
	m_wndShDelayTime.SetWindowText( "0.05" );
	m_wndRoDelayTime.SetWindowText( "0.05" );
}
void CDlgCylinderLifeTimeTool::LockUI(bool bEnable)
{
	if( bEnable )
	{
		BOOL m_bEnable = FALSE;

		// Rotator
		m_btnRoStop.EnableWindow( !m_bEnable);
		m_btnRoReport.EnableWindow( m_bEnable );
		m_btnRoGo.EnableWindow( m_bEnable );
		m_btnRoClear.EnableWindow( m_bEnable );
		m_wndRoDelayTime.EnableWindow( m_bEnable );

		// Shuttle
		m_btnShStop.EnableWindow( !m_bEnable);
		m_btnShReport.EnableWindow( m_bEnable );
		m_btnShGo.EnableWindow( m_bEnable );
		m_btnShClear.EnableWindow( m_bEnable );
		m_wndShDelayTime.EnableWindow( m_bEnable );

		if( m_bEnableShLife )
			m_btnRoStop.EnableWindow( m_bEnable);
		else if( m_bEnableRoLife )
			m_btnShStop.EnableWindow( m_bEnable);

		//
		m_btnCancel.EnableWindow( m_bEnable );
		m_btnOK.EnableWindow( m_bEnable );
	}
	else
	{
		BOOL m_bEnable = TRUE;

		// Rotator
		m_btnRoStop.EnableWindow( !m_bEnable);
		m_btnRoReport.EnableWindow( m_bEnable );
		m_btnRoGo.EnableWindow( m_bEnable );
		m_btnRoClear.EnableWindow( m_bEnable );
		m_wndRoDelayTime.EnableWindow( m_bEnable );

		// Shuttle
		m_btnShStop.EnableWindow( !m_bEnable);
		m_btnShReport.EnableWindow( m_bEnable );
		m_btnShGo.EnableWindow( m_bEnable );
		m_btnShClear.EnableWindow( m_bEnable );
		m_wndShDelayTime.EnableWindow( m_bEnable );

		//
		m_btnCancel.EnableWindow( m_bEnable );
		m_btnOK.EnableWindow( m_bEnable );
	}
}
void CDlgCylinderLifeTimeTool::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	
	CDialog::OnTimer(nIDEvent);
}
UINT CDlgCylinderLifeTimeTool::RoLifeTimeThread(LPVOID p)
{
	CDlgCylinderLifeTimeTool *pt = (CDlgCylinderLifeTimeTool *)p;

	long lCount = 0;
	while(1)
	{
		// stop 
		if ( pt->m_bEnableRoLife != true )
			break;

		pt->m_lRoCounter++;
		int m_iFunction = lCount % 2;
		if( m_iFunction == 0 )
		{
			// NN
			if( f.ManualRotatorN(&m.RemoteOutSet.Rotator,
					&m.RemoteInStatus.RotatepLmt,
					&m.RemoteInStatus.RotatenLmt,
					m.TimerSetting.iRotatorTimeout ) )
				pt->m_lRoNNCount++;

			Sleep( pt->m_dRoDelayTime * 1000 );
		}
		else if( m_iFunction == 1 )
		{
			// PP
			if( f.ManualRotatorP(&m.RemoteOutSet.Rotator,
					&m.RemoteInStatus.RotatepLmt,
					&m.RemoteInStatus.RotatenLmt,
					m.TimerSetting.iRotatorTimeout) )
				pt->m_lRoPPCount++;
			
			Sleep( pt->m_dRoDelayTime * 1000 );
		}
		else
			; // Nerver be here

		pt->UpDataRoValu();

		// Make sure program close. Thread will be close
		if( !m.Info.bRunning )
			break;

		lCount++;

		Sleep(1);
	}

	pt->LockUI( false );
	AfxEndThread(0);
	return 0;
}
UINT CDlgCylinderLifeTimeTool::ShLifeTimeThread(LPVOID p)
{
	CDlgCylinderLifeTimeTool *pt = (CDlgCylinderLifeTimeTool *)p;

	long lCount = 0;
	while(1)
	{
		// stop 
		if ( pt->m_bEnableShLife != true )
			break;

		pt->m_lShCounter++;
		int m_iFunction = lCount % 2;
		if( m_iFunction == 0 )
		{
			// Home
			if( f.ManualShuttleMoveHome() )
				pt->m_lShHomeCount++;

			Sleep( pt->m_dShDelayTime * 1000 );
		}
		else if( m_iFunction == 1 )
		{
			// PP
			if( f.ManualShuttleMovePickPlace() )
				pt->m_lShPPCount++;
			
			Sleep( pt->m_dShDelayTime * 1000 );
		}
		else
			; // Nerver be here

		pt->UpDataShValu();

		// Make sure program close. Thread will be close
		if( !m.Info.bRunning )
			break;

		lCount++;

		Sleep(1);
	}

	pt->LockUI( false );
	AfxEndThread(0);
	return 0;
}
void CDlgCylinderLifeTimeTool::UpDataShValu()
{
	// Home
	CString csShHome = _T("");
	csShHome.Format("%d", m_lShHomeCount );
	m_wndShHome.SetWindowText( csShHome );

	// PP
	CString csShPP = _T("");
	csShPP.Format("%d", m_lShPPCount );
	m_wndShPP.SetWindowText( csShPP );

	CString csShCounter = _T("");
	csShCounter.Format("%d", m_lShCounter );
	m_wndShCounter.SetWindowText( csShCounter );
}

void CDlgCylinderLifeTimeTool::OnFShGo() 
{
	m_bEnableShLife = true;
	CString csDelayTime = _T("");
	m_wndShDelayTime.GetWindowText( csDelayTime );
	csDelayTime.TrimLeft(); 
	csDelayTime.TrimRight();
	m_dShDelayTime = atof( csDelayTime );
	LockUI( true );
	AfxBeginThread(ShLifeTimeThread, this);
}

void CDlgCylinderLifeTimeTool::OnFShStop() 
{
	m_bEnableShLife = false;	
}

void CDlgCylinderLifeTimeTool::OnFShClear() 
{
	m_lShHomeCount = 0;
	m_lShPPCount = 0;
	m_lShCounter = 0;

	//
	UpDataShValu();
}

void CDlgCylinderLifeTimeTool::OnFShReport() 
{
	
}

void CDlgCylinderLifeTimeTool::OnCancel() 
{
	
	CDialog::OnCancel();
}

void CDlgCylinderLifeTimeTool::OnOK() 
{
	m_bEnableShLife = false;
	m_bEnableRoLife = false;	

	CDialog::OnOK();
}

void CDlgCylinderLifeTimeTool::OnFRoGo() 
{
	m_bEnableRoLife = true;
	CString csDelayTime = _T("");
	m_wndRoDelayTime.GetWindowText( csDelayTime );
	csDelayTime.TrimLeft(); 
	csDelayTime.TrimRight();
	m_dRoDelayTime = atof( csDelayTime );
	LockUI( true );
	AfxBeginThread(RoLifeTimeThread, this);	
}

void CDlgCylinderLifeTimeTool::OnFRoStop() 
{
	m_bEnableRoLife = false;	
}
void CDlgCylinderLifeTimeTool::UpDataRoValu()
{
	// NN
	CString csRoNN = _T("");
	csRoNN.Format("%d", m_lRoNNCount );
	m_wndRoNN.SetWindowText( csRoNN );

	// PP
	CString csRoPP = _T("");
	csRoPP.Format("%d", m_lRoPPCount );
	m_wndRoPP.SetWindowText( csRoPP );

	CString csRoCounter = _T("");
	csRoCounter.Format("%d", m_lRoCounter );
	m_wndRoCounter.SetWindowText( csRoCounter );
}
void CDlgCylinderLifeTimeTool::OnFRoClear() 
{
	m_lRoNNCount = 0;
	m_lRoPPCount = 0;
	m_lRoCounter = 0;	

	UpDataRoValu();
}

void CDlgCylinderLifeTimeTool::OnFRoReport() 
{
	
}
