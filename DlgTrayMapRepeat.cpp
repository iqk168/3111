// DlgTrayMapRepeat.cpp : implementation file
//

#include "stdafx.h"
#include "deer.h"
#include "DlgTrayMapRepeat.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgTrayMapRepeat dialog


CDlgTrayMapRepeat::CDlgTrayMapRepeat(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgTrayMapRepeat::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgTrayMapRepeat)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgTrayMapRepeat::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgTrayMapRepeat)
	DDX_Control(pDX, IDC_TRAY2,				m_wndTray2);
	DDX_Control(pDX, IDC_TRAY1,				m_wndTray1);
	DDX_Control(pDX, IDC_DTRAY_OUTPUT2,		m_wndOutputTray2);
	DDX_Control(pDX, IDC_DTRAY_OUTPUT1,		m_wndOutputTray1);
	DDX_Control(pDX, IDCANCEL,				m_btnCancel);
	DDX_Control(pDX, IDOK,					m_btnOK);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgTrayMapRepeat, CDialog)
	//{{AFX_MSG_MAP(CDlgTrayMapRepeat)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_E_TRAY1_UP, OnETray1Up)
	ON_BN_CLICKED(IDC_E_TRAY1_DOWN, OnETray1Down)
	ON_BN_CLICKED(IDC_E_TRAY2_UP, OnETray2Up)
	ON_BN_CLICKED(IDC_E_TRAY2_DOWN, OnETray2Down)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgTrayMapRepeat message handlers

BOOL CDlgTrayMapRepeat::PreTranslateMessage(MSG* pMsg) 
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

BOOL CDlgTrayMapRepeat::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// init button 
	m_btnOK.SetIcon(IDI_OK);
	m_btnOK.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnOK.SetFlat(FALSE);
	
	m_btnCancel.SetIcon(IDI_CANCEL);
	m_btnCancel.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnCancel.SetFlat(FALSE);
	
	InitTrayMap();

	//
	InitValue();

	//
	InitTips();

	f.ChangeLanguage(GetSafeHwnd());

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
void CDlgTrayMapRepeat::InitValue()
{
	// Set a Timer for updata the Tray Status.
	if( m.TimerSetting.iScanTrayStatus > 0 )
		SetTimer(ID_TIME_TRAY_STATUS, m.TimerSetting.iScanTrayStatus, NULL);
	else
		SetTimer(ID_TIME_TRAY_STATUS, _Tray_Status_Timer, NULL);
}
void CDlgTrayMapRepeat::InitTips()
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
void CDlgTrayMapRepeat::InitTrayMap()
{
	//////////////////////////////////////////////////////////////////
	int iSize = 0;
	int i = 0;

	//////////////////////////////////////////////////////////////////
	// Tray 1
	CRect rect1;
	m_wndOutputTray1.GetClientRect( rect1 );

	pViewTrayOutput1 = new CViewTrayMap();
	pViewTrayOutput1->SetTrayID(0);
	pViewTrayOutput1->SetRepeatTray(1);
	if( m.TraySpec.m_OutputUseChipTray == 1 )
		pViewTrayOutput1->SetChipMode(1);
	else
		pViewTrayOutput1->SetChipMode(0);

	//
	pViewTrayOutput1->ClearCsutomColor();
	iSize = m.BinMap.GetSize();
	for(i=0;i<iSize;i++)
		pViewTrayOutput1->SetCustomColor( m.BinMap.GetAt(i).code, m.BinMap.GetAt(i).color );

	//
	pViewTrayOutput1->Create(NULL, "Output1", WS_CHILD | WS_VISIBLE, rect1, 
		(CWnd *)&m_wndOutputTray1, IDC_DTRAY_OUTPUT1);	// Output 1

	//////////////////////////////////////////////////////////////////
	// Tray 2
	CRect rect2;
	m_wndOutputTray2.GetClientRect( rect1 );

	pViewTrayOutput2 = new CViewTrayMap();
	pViewTrayOutput2->SetTrayID(1);
	pViewTrayOutput2->SetRepeatTray(1);
	if( m.TraySpec.m_OutputUseChipTray == 1 )
		pViewTrayOutput2->SetChipMode(1);
	else
		pViewTrayOutput2->SetChipMode(0);

	//
	pViewTrayOutput2->ClearCsutomColor();
	iSize = m.BinMap.GetSize();
	for(i=0;i<iSize;i++)
		pViewTrayOutput2->SetCustomColor( m.BinMap.GetAt(i).code, m.BinMap.GetAt(i).color );

	//
	pViewTrayOutput2->Create(NULL, "Output2", WS_CHILD | WS_VISIBLE, rect1, 
		(CWnd *)&m_wndOutputTray2, IDC_DTRAY_OUTPUT2);	// Output 1

	//
	UpdateView();
}
//
static CMutex MutexTrayMapRepeat;
void CDlgTrayMapRepeat::UpdateView()
{
	CSingleLock Lock(&MutexTrayMapRepeat);
	Lock.Lock();

	// If CView Object is NULL. We can not send request to Invalidate.
	if( pViewTrayOutput1 == NULL )
	{
	}
	else
	{
		pViewTrayOutput1->Invalidate(FALSE);
		// ±j­¢ OnReDraw

		CString cs1 = _T("");
		CString csOld1 = _T("");
		int iCount1 = pViewTrayOutput1->GetPageCount();
		int iNow1 = pViewTrayOutput1->GetNowPage();
		if ( iCount1 == 0 )
			iCount1 = 1;

		cs1.Format(" %d/%d", iNow1, iCount1 );
		m_wndTray1.GetWindowText(csOld1);
		if( csOld1 != cs1 )		
			m_wndTray1.SetWindowText(cs1);
		// Tray 1
	}

	// If CView Object is NULL. We can not send request to Invalidate.
	if( pViewTrayOutput2 == NULL )
	{
	}
	else
	{
		pViewTrayOutput2->Invalidate(FALSE);
		// ±j­¢ OnReDraw

		CString cs2 = _T("");
		CString csOld2 = _T("");
		int iCount2 = pViewTrayOutput2->GetPageCount();
		int iNow2 = pViewTrayOutput2->GetNowPage();
		if ( iCount2 == 0 )
			iCount2 = 1;

		cs2.Format(" %d/%d", iNow2, iCount2 );
		m_wndTray2.GetWindowText(csOld2);
		if( csOld2 != cs2 )		
			m_wndTray2.SetWindowText(cs2);
		// Tray 2
	}

	Lock.Unlock();
}
void CDlgTrayMapRepeat::OnTimer(UINT nIDEvent) 
{
	switch(nIDEvent)
	{
	case ID_TIME_TRAY_STATUS:
		{
			UpdateView();
		}
		break;
	}	
	CDialog::OnTimer(nIDEvent);
}

void CDlgTrayMapRepeat::OnOK() 
{
	KillTimer( ID_TIME_TRAY_STATUS );
	
	CDialog::OnOK();
}

void CDlgTrayMapRepeat::OnCancel() 
{
	KillTimer( ID_TIME_TRAY_STATUS );
	
	CDialog::OnCancel();
}
//////////////////////////////////////////////////////////////////
// Change Page
void CDlgTrayMapRepeat::OnETray1Up() 
{
	pViewTrayOutput1->ChangePageUp();

	CString cs = _T("");
	CString csOld = _T("");
	int iCount = pViewTrayOutput1->GetPageCount();
	int iNow = pViewTrayOutput1->GetNowPage();
	if ( iCount == 0 )
		iCount = 1;

	cs.Format(" %d/%d", iNow, iCount );
	m_wndTray1.SetWindowText(cs);

	UpdateView();	
}

void CDlgTrayMapRepeat::OnETray1Down() 
{
	pViewTrayOutput1->ChangePageDown();

	CString cs = _T("");
	CString csOld = _T("");
	int iCount = pViewTrayOutput1->GetPageCount();
	int iNow = pViewTrayOutput1->GetNowPage();
	if ( iCount == 0 )
		iCount = 1;

	cs.Format(" %d/%d", iNow, iCount );
	m_wndTray1.SetWindowText(cs);

	UpdateView();	
}

void CDlgTrayMapRepeat::OnETray2Up() 
{
	pViewTrayOutput2->ChangePageUp();

	CString cs = _T("");
	CString csOld = _T("");
	int iCount = pViewTrayOutput2->GetPageCount();
	int iNow = pViewTrayOutput2->GetNowPage();
	if ( iCount == 0 )
		iCount = 1;

	cs.Format(" %d/%d", iNow, iCount );
	m_wndTray2.SetWindowText(cs);

	UpdateView();		
}

void CDlgTrayMapRepeat::OnETray2Down() 
{
	pViewTrayOutput2->ChangePageDown();

	CString cs = _T("");
	CString csOld = _T("");
	int iCount = pViewTrayOutput2->GetPageCount();
	int iNow = pViewTrayOutput2->GetNowPage();
	if ( iCount == 0 )
		iCount = 1;

	cs.Format(" %d/%d", iNow, iCount );
	m_wndTray2.SetWindowText(cs);

	UpdateView();		
}
