// DlgLotInformationProgress.cpp : implementation file
//

#include "stdafx.h"
#include "deer.h"
#include "DlgLotInformationProgress.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgLotInformationProgress dialog


CDlgLotInformationProgress::CDlgLotInformationProgress(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgLotInformationProgress::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgLotInformationProgress)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	pWindLotDoneThread = NULL;
	pWindLotDonePragressThread = NULL;

	hLotDoneProcess = NULL;
	hLotDonePragressProcess = NULL;
}


void CDlgLotInformationProgress::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgLotInformationProgress)
	DDX_Control(pDX, IDC_PROGRESS1, m_wndProgress);
	DDX_Control(pDX, IDC_MSG,		m_wndMsg);
	DDX_Control(pDX, IDOK,			m_btnOK);
	DDX_Control(pDX, IDCANCEL,		m_btnCancel);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgLotInformationProgress, CDialog)
	//{{AFX_MSG_MAP(CDlgLotInformationProgress)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgLotInformationProgress message handlers
UINT CDlgLotInformationProgress::LotLotDoneCtrlThread(LPVOID p)
{
	CDlgLotInformationProgress *pt = (CDlgLotInformationProgress *)p;

	//
	f.LotDone();

	//
	AfxEndThread(0);
	return 0;
}

UINT CDlgLotInformationProgress::LotCtrProgressStatuslThread(LPVOID p)
{
	CDlgLotInformationProgress *pt = (CDlgLotInformationProgress *)p;

	m.m_LotInfoProg.m_csLotInformationInfo		= "";
	m.m_LotInfoProg.m_lLotInformationStatus		= 0;
	m.m_LotInfoProg.m_bLotInformationDone		= false;

	long lProgressSize = f.Report.GetBinCountTemp();
	pt->m_wndProgress.SetRange( 0, lProgressSize);
	pt->m_wndProgress.SetPos(0);

	while(1)
	{
		CString csMsg = _T("");
		if( m.m_LotInfoProg.m_lLotInformationStatus != 0 )
			csMsg.Format("%s [%d]", m.m_LotInfoProg.m_csLotInformationInfo, m.m_LotInfoProg.m_lLotInformationStatus );
		else
			csMsg.Format("%s", m.m_LotInfoProg.m_csLotInformationInfo );
		pt->m_wndMsg.SetWindowText( csMsg );

		pt->m_wndProgress.SetPos(m.m_LotInfoProg.m_lLotInformationStatus);

		if( m.m_LotInfoProg.m_bLotInformationDone )
			break;
	
		// Make sure program close. Thread will be close
		if( !m.Info.bRunning )
			break;

		Sleep(1);
	}

	//
	pt->m_wndProgress.SetRange( 0, 100);
	pt->m_wndProgress.SetPos(100);
//	pt->m_btnOK.EnableWindow( TRUE );

	//
	pt->SetCloseTimer();

	//
	AfxEndThread(0);
	return 0;
}
BOOL CDlgLotInformationProgress::PreTranslateMessage(MSG* pMsg) 
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

BOOL CDlgLotInformationProgress::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// init button 
	m_btnOK.SetIcon(IDI_OK);;
	m_btnOK.SetAlign(CButtonST::ST_ALIGN_VERT);;
	m_btnOK.SetFlat(FALSE);
	
	m_btnCancel.SetIcon(IDI_CANCEL);
	m_btnCancel.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnCancel.SetFlat(FALSE);

	m_btnOK.EnableWindow( FALSE );

	// 1.0Af
	// Remove this function and re-build new one
	/*
	AfxBeginThread(LotCtrProgressStatuslThread, this);
	AfxBeginThread(LotLotDoneCtrlThread, this);
	*/

	// 1.0Af 
	// Handle the thread hThread, avoid close un-complete.
	pWindLotDonePragressThread = AfxBeginThread(LotCtrProgressStatuslThread, this);
	if(pWindLotDonePragressThread)
		hLotDonePragressProcess = pWindLotDonePragressThread->m_hThread;															  

	pWindLotDoneThread = AfxBeginThread(LotLotDoneCtrlThread, this);
	if(pWindLotDoneThread)
		hLotDoneProcess = pWindLotDoneThread->m_hThread;

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
void CDlgLotInformationProgress::SetCloseTimer()
{
	SetTimer(ID_TIME_CLOSE_PROGRESS, 800, NULL );
}
bool CDlgLotInformationProgress::CloseLotDone()
{
	MSG				msg;
	LARGE_INTEGER	start, end, freq;
	DWORD			nThreadExitCode = 0;
	BOOL			bSuccess = FALSE;

	::QueryPerformanceFrequency(&freq);
	::QueryPerformanceCounter(&start);
	if(hLotDoneProcess != NULL)
	{
	do
	{
		bSuccess = GetExitCodeThread(hLotDoneProcess, &nThreadExitCode);
		::QueryPerformanceCounter(&end);

		if(::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			::TranslateMessage(&msg);
			::DispatchMessage(&msg);
		}
	}while(bSuccess && nThreadExitCode == STILL_ACTIVE && (end.QuadPart - start.QuadPart) / freq.QuadPart < 10);  //10秒表示等10s, 可依據需求修改
	}
	return true;
}
bool CDlgLotInformationProgress::CloseLotDonePragress()
{
	MSG				msg;
	LARGE_INTEGER	start, end, freq;
	DWORD			nThreadExitCode = 0;
	BOOL			bSuccess = FALSE;

	::QueryPerformanceFrequency(&freq);
	::QueryPerformanceCounter(&start);
	if(hLotDonePragressProcess != NULL)
	{
	do
	{
		bSuccess = GetExitCodeThread(hLotDonePragressProcess, &nThreadExitCode);
		::QueryPerformanceCounter(&end);

		if(::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			::TranslateMessage(&msg);
			::DispatchMessage(&msg);
		}
	}while(bSuccess && nThreadExitCode == STILL_ACTIVE && (end.QuadPart - start.QuadPart) / freq.QuadPart < 10);  //10秒表示等10s, 可依據需求修改
	}
	return true;
}
void CDlgLotInformationProgress::OnOK() 
{
	//
	CloseLotDone();
	CloseLotDonePragress();
	
	//
	CDialog::OnOK();
}

void CDlgLotInformationProgress::OnTimer(UINT nIDEvent) 
{
	switch(nIDEvent)
	{
	case ID_TIME_CLOSE_PROGRESS:
		{
			EndDialog(IDOK);
		}	
		break;
	default:
		break;
	}	
	CDialog::OnTimer(nIDEvent);
}
