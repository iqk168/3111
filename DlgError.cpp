// DlgError.cpp : implementation file
//

#include "stdafx.h"
#include "Deer.h"
#include "DeerDlg.h"
#include "DlgError.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgError dialog


CDlgError::CDlgError(tagErrorMsg *e, CWnd* pParent /*=NULL*/)
	: CDialog(CDlgError::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgError)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	
	msg = e;

	m_lStart = 0;
}


void CDlgError::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgError)
	DDX_Control(pDX, IDC_LED_B_TS_SKIP,		m_ledTestSiteSkip);
	DDX_Control(pDX, IDC_LED_B_RESET,		m_ledReset);
	DDX_Control(pDX, IDC_LED_B_SKIP,		m_ledSkip);
	DDX_Control(pDX, IDC_LED_B_RETRY,		m_ledRetry);
	DDX_Control(pDX, IDC_RESET,				m_btnReset);
	DDX_Control(pDX, IDC_RETRY,				m_btnRetry);
	DDX_Control(pDX, IDC_SKIP,				m_btnSkip);
	DDX_Control(pDX, IDC_LAYOUT,			m_wndLayout);
	DDX_Control(pDX, IDC_MSG,				m_wndMessage);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgError, CDialog)
	//{{AFX_MSG_MAP(CDlgError)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_MSG, OnMsg)
	ON_WM_CLOSE()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_SKIP, OnSkip)
	ON_BN_CLICKED(IDC_RETRY, OnRetry)
	ON_BN_CLICKED(IDC_RESET, OnReset)
	ON_BN_CLICKED(IDC_TEST_SITE_SKIP, OnTestSiteSkip)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgError message handlers

BOOL CDlgError::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	CString cs;

	cs.Format("Code = %d  :  %s\n %s", msg->Code, msg->Eng, msg->EngProcess);
	m_wndMessage.SetWindowText(cs);
	// Show Error Position	
	
	CRect rect;
	m_wndLayout.GetClientRect(&rect);

	CRect rectMe;
	GetClientRect(&rectMe);
	ClientToScreen(rectMe);

	pView = new CErrView(msg);
	pView->Create(NULL, "Error", WS_CHILD | WS_VISIBLE, rect, 
		(CWnd *)&m_wndLayout, IDC_ERROR_VIEW);

	count = 0;	
	m_lStart = ::GetTickCount();
	SetTimer(ID_TIME_ALARM, 100, NULL);
	CDeerDlg *p = (CDeerDlg *)theApp.m_pMainWnd;
	p->m_btnShutDown.ShowWindow(SW_HIDE);

	SetTimer(ID_TIME_BUTTON, 10, NULL);	// 更新畫面可以不用很快, 但是按鈕要快一點

	CenterWindow();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgError::OnTimer(UINT nIDEvent) 
{
	switch(nIDEvent)
	{
	case ID_TIME_ALARM:
		{
			if( m.Setting.m_dBuzzerAutoClose != 0 )
			{
				if( ( ::GetTickCount() - m_lStart ) > m.Setting.m_dBuzzerAutoClose * 1000 )
				{
					// Auto Close Buzzer
					m.Info.bBuzzer = false;
				}
			}

			count++;
			switch(msg->Level)
			{
			case 1:
				{
					// Normal Mode
					if(count%6 == 1)
						m.Info.bAlarmTimer = !m.Info.bAlarmTimer;
				}
				break;
			case 2:
				{				
					// Normal Mode
					if(count%3 == 1)
					{
						m.Info.bAlarmTimer = !m.Info.bAlarmTimer;
					}
				}
				break;
			case 3:
				{
					// Normal Mode
					if(count%3 == 1)
						m.Info.bAlarmTimer = true;
					else
						m.Info.bAlarmTimer = false;
				}
				break;
			case 4:
				{				
					// Normal Mode
					m.Info.bAlarmTimer = !m.Info.bAlarmTimer;				
				}
				break;
			}
		}
		break;
	case ID_TIME_BUTTON:
		{
			ButtonQuery();	
		}
		break;
	default:
		break;
	}
}
void CDlgError::ButtonQuery() 
{
	if( m.RemoteOutSet.BtnResetOn )
		m_ledReset.SetNewBkColor( ST_RED );
	else
		m_ledReset.SetNewBkColor( ST_WHITE );
		
	if( m.RemoteOutSet.BtnRetryOn )
		m_ledRetry.SetNewBkColor( ST_RED );
	else
		m_ledRetry.SetNewBkColor( ST_WHITE );
	
	if( m.RemoteOutSet.BtnSkipOn )
		m_ledSkip.SetNewBkColor( ST_RED );
	else
		m_ledSkip.SetNewBkColor( ST_WHITE );

	if( m.OutSet.TestSiteSkip )
		m_ledTestSiteSkip.SetNewBkColor( ST_RED );
	else
		m_ledTestSiteSkip.SetNewBkColor( ST_WHITE );
}
void CDlgError::OnMsg() 
{
#ifdef _Demo
	m.Info.bResetError = true;
#endif // _DEBUG
}

void CDlgError::OnClose() 
{
	
	CDialog::OnClose();
}

BOOL CDlgError::DestroyWindow() 
{
	
	return CDialog::DestroyWindow();
}

void CDlgError::Close()
{
	CDeerDlg *p = (CDeerDlg *)theApp.m_pMainWnd;
	p->m_btnShutDown.ShowWindow(SW_SHOW);
	delete pView;	
	CDialog::OnOK();
}

void CDlgError::OnDestroy() 
{
	CDeerDlg *p = (CDeerDlg *)theApp.m_pMainWnd;
	p->m_btnShutDown.ShowWindow(SW_SHOW);

	CDialog::OnDestroy();
	
}

BOOL CDlgError::PreTranslateMessage(MSG* pMsg) 
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

void CDlgError::OnSkip() 
{
	m.PanelButton.BtnSkipPushed = true;
}

void CDlgError::OnRetry() 
{
	m.PanelButton.BtnRetryPushed = true;
}

void CDlgError::OnReset() 
{
	m.PanelButton.BtnResetPushed = true;	
}

void CDlgError::PostNcDestroy() 
{	
	CDialog::PostNcDestroy();
	delete this;	// 防止 Memory Leak
}

void CDlgError::OnTestSiteSkip() 
{
	m.PanelButton.BtnTestSiteSkip = true;	
}
