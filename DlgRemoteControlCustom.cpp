// DlgRemoteControlCustom.cpp : implementation file
//

#include "stdafx.h"
#include "deer.h"
#include "DlgRemoteControlCustom.h"
#include "DlgRemoteRecover.h"

//
#include "DlgPasswordNeed.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgRemoteControlCustom dialog


CDlgRemoteControlCustom::CDlgRemoteControlCustom(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgRemoteControlCustom::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgRemoteControlCustom)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	bPickButtonStatus		= FALSE;
	bReleaseButtonStatus	= FALSE;

}


void CDlgRemoteControlCustom::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgRemoteControlCustom)
	DDX_Control(pDX, IDC_POSITION,			m_wndPosition);
	DDX_Control(pDX, IDC_E_CONTINUE,		m_btnContinue);
	DDX_Control(pDX, IDC_E_RELEASE_IC,		m_btnReleaseIC);
	DDX_Control(pDX, IDC_E_PICK_IC,			m_btnPickIC);
	DDX_Control(pDX, IDC_LED_L_ALARM,		m_ledAlarm);
	DDX_Control(pDX, IDC_LED_L_READY,		m_ledReady);
	DDX_Control(pDX, IDCANCEL,				m_btnCancel);
	DDX_Control(pDX, IDOK,					m_btnOK);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgRemoteControlCustom, CDialog)
	//{{AFX_MSG_MAP(CDlgRemoteControlCustom)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_ST_INPUTTRAY,			OnStInputtray)
	ON_BN_CLICKED(IDC_ASTATIC,				OnAstatic)
	ON_BN_CLICKED(IDC_E_PICK_IC,			OnEPickIc)
	ON_BN_CLICKED(IDC_E_RELEASE_IC,			OnEReleaseIc)
	ON_BN_CLICKED(IDC_E_CONTINUE,			OnEContinue)

	//
	ON_MESSAGE( WM_REMOTE_READY,			OnRemoteReady )
	ON_MESSAGE( WM_REMOTE_RELEASE_IC,		OnRemoteReleaseIC )
	ON_MESSAGE( WM_REMOTE_PICK_IC,			OnRemotePickIC )
	ON_MESSAGE( WM_REMOTE_ALARM,			OnRemoteAlarm )

	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgRemoteControlCustom message handlers

void CDlgRemoteControlCustom::OnOK() 
{
	ReleaseRemoteControl();

	CDialog::OnOK();
}

void CDlgRemoteControlCustom::OnCancel() 
{
	CDlgPasswordNeed dlg(false, false);
	if(dlg.DoModal() != IDOK)
		return;

	ReleaseRemoteControl();

	CDialog::OnCancel();
}

BOOL CDlgRemoteControlCustom::PreTranslateMessage(MSG* pMsg) 
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
void CDlgRemoteControlCustom::InitLed()
{
	m_ledReady.SetLed(CLed::LED_COLOR_GREEN);
	m_ledAlarm.SetLed(CLed::LED_COLOR_RED);
}
void CDlgRemoteControlCustom::InitUI()
{
	if (GetDlgItem(IDC_ST_INPUTTRAY)) 
	{
		m_stTrayMap.SubclassDlgItem(IDC_ST_INPUTTRAY, this);
		m_stTrayMap.setMapSize( m.TraySpec.Column , m.TraySpec.Row );
		m_stTrayMap.SetForeColour(RGB(192,192,192));
		m_stTrayMap.SetBkColour(RGB(0,128,192));
	}	
}
BOOL CDlgRemoteControlCustom::OnInitDialog() 
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
	InitUI();

	//
	InitTrayStatus();

	//
	LoadTrayStatus(0);

	//
	InitLed();

	//
	InitRemoteControl();
	
	//
	SetTimer( ID_TIME_TRAY_SEL_STATUS, 100, NULL);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
void CDlgRemoteControlCustom::BackupUI()
{	
	bReleaseButtonStatus	= m_btnReleaseIC.IsWindowEnabled();
	bPickButtonStatus		= m_btnPickIC.IsWindowEnabled();
}
void CDlgRemoteControlCustom::RecoverUI()
{
	m_btnContinue.EnableWindow( FALSE );
	m_btnReleaseIC.EnableWindow( bReleaseButtonStatus );
	m_btnPickIC.EnableWindow( bPickButtonStatus );

	bReleaseButtonStatus = FALSE;
	bPickButtonStatus = FALSE;
}
void CDlgRemoteControlCustom::ChangeUI( int Status )
{
	if( Status == theApp.enRemoteNone )
	{
		// Nothing
		BOOL bEnable = FALSE;
		m_btnContinue.EnableWindow( bEnable );
		m_btnReleaseIC.EnableWindow( bEnable );
		m_btnPickIC.EnableWindow( bEnable );
	}
	else if( Status == theApp.enRemoteWaitOK )
	{
		// IC in socket OK, wait for release IC
		BOOL bEnable = FALSE;
		m_btnContinue.EnableWindow( bEnable );
		m_btnReleaseIC.EnableWindow( !bEnable );
		m_btnPickIC.EnableWindow( bEnable );
	}
	else if( Status == theApp.enRemoteMoving )
	{
		// Moving..
		BOOL bEnable = FALSE;
		m_btnContinue.EnableWindow( bEnable );
		m_btnReleaseIC.EnableWindow( bEnable );
		m_btnPickIC.EnableWindow( bEnable );
	}
	else if( Status == theApp.enRemoteStandy )
	{
		// IC Place back OK, wait for next time pick IC
		BOOL bEnable = FALSE;
		m_btnContinue.EnableWindow( bEnable );
		m_btnReleaseIC.EnableWindow( bEnable );
		m_btnPickIC.EnableWindow( !bEnable );
	}
	else if( Status == theApp.enRemoteAlarm )
	{
		// Alarm..
		BOOL bEnable = FALSE;
		BackupUI();
		m_btnContinue.EnableWindow( !bEnable );
		m_btnReleaseIC.EnableWindow( bEnable );
		m_btnPickIC.EnableWindow( bEnable );
	}
	else
		; // Nerver be here.!
}
void CDlgRemoteControlCustom::ReleaseRemoteControl()
{	
	// stop all handler
	f.ButtonStop();
	
	// reset system status
	m.Info.iStatus = theApp.enUninitial;
	f.UpdateButtonState();

	// disable module
	if( m.Setting.m_bEnableATCModule == 1 )
	{
		// 
	}
	else if( m.Setting.m_bEnablePTCModule == 1 )
	{
		//
	}

	m.RemoteInterlock.IsRemoteControlMode = false;

}
void CDlgRemoteControlCustom::InitTrayStatus()
{
	// 1. 恶︽计.
	m_trayMap.iCol = m.TraySpec.Column;

	// 2. 恶计.
	m_trayMap.iRow = m.TraySpec.Row;

	// 3. 恶篈. (0: ON, 1: OFF)
	// int	iStatus[50][100]; 程 (50, 100)
	for (int row = 0; row < m_trayMap.iRow; ++row) 
		for (int col = 0; col < m_trayMap.iCol; ++col) 
			m_trayMap.iStatus[col][row] = 0;
}
void CDlgRemoteControlCustom::InitRemoteControl()
{
	m.RemoteInterlock.IsRemoteControlMode = true;
	m.RemoteInterlock.PickIC = false;
	m.RemoteInterlock.ReleaseIC = false;
	m.RemoteInterlock.RemotePosition = 0;

	//
	ChangeUI( theApp.enRemoteStandy );

	//
	m_stTrayMap.setPosition(0);

}
void CDlgRemoteControlCustom::LoadTrayStatus(int value)
{
	CString csFileName = _T("");
	csFileName.Format("%s%d%s", _RemoteInputTrayFileDATA ,value, _RemoteInputTrayFileDATASub );

	//
	m_LoadFileData.RemoveAll();

	//
	CString csFile = m.FilePath.InputCustomInputPath + csFileName;	
	CFile file;
	if(file.Open(csFile, CFile::modeRead | CFile::shareDenyNone, NULL) != 0)
	{
		file.SeekToBegin();
		CArchive ar(&file, CArchive::load);
		CString cs = _T("");
		
		while(1)
		{
			BOOL bReadOK = ar.ReadString(cs);
			if( !bReadOK )
				break;
			
			CArray <CString, CString > m_InputRecord;
			f.StringToIntArrayByToken(	cs, m_InputRecord, ",");

			// Position
			int iPos = -1;
			CString csPos = _T("");
			csPos = m_InputRecord.GetAt(0);
			iPos = atoi(csPos);

			// Result 
			int iResult = -1;
			CString csResult = _T("");
			csResult = m_InputRecord.GetAt(1);
			iResult = atoi(csResult);

			// Fill the value 
			int col = 0;
			int row = 0;
			
			col = iPos % m_trayMap.iCol;
			row = iPos / m_trayMap.iCol;
			
			if( iResult == 1 || iResult == 4)
				m_trayMap.iStatus[col][row] = 4;
			else
				m_trayMap.iStatus[col][row] = 0;
		}
		ar.Close();
		file.Close();
	}
	else
	{
		// Open Fail.. ボ⊿Τ郎, ⊿Τ砆砞﹚筁..场耴箂
		for (int row = 0; row < m_trayMap.iRow; ++row) {
			for (int col = 0; col < m_trayMap.iCol; ++col) {
				m_trayMap.iStatus[col][row] = 0;
			}
		}
	}

	// Fill the Object
	for (int row = 0; row < m_trayMap.iRow; ++row) {
		for (int col = 0; col < m_trayMap.iCol; ++col) {
			int n = m_trayMap.iStatus[col][row];
			m_stTrayMap.setCellStatus(col, row, n);
		}
	}

	// Request to Fill UI
//	m_stTrayMap.Invalidate();
}
void CDlgRemoteControlCustom::UpdatePos()
{	
	//
	if (::IsWindow(m_stTrayMap.m_hWnd)) 
	{
		CString csPos = _T("");
		int iPos = m_stTrayMap.getPosition();
		csPos.Format("%d", iPos );

		//
		m.RemoteInterlock.RemotePosition = iPos;

		//
		m_wndPosition.SetWindowText( csPos );
	}
}
void CDlgRemoteControlCustom::UpdateSel()
{
	if (!IsWindowVisible()) 
		return;

	//
	if (::IsWindow(m_stTrayMap.m_hWnd)) 
	{
		m_stTrayMap.Invalidate();
	}	
}
void CDlgRemoteControlCustom::OnTimer(UINT nIDEvent) 
{
	switch(nIDEvent)
	{
	case ID_TIME_TRAY_SEL_STATUS:
		{
			UpdateSel();
			UpdatePos();
		}
		break;
	default:
		break;
	}	
	CDialog::OnTimer(nIDEvent);
}

void CDlgRemoteControlCustom::OnStInputtray() 
{

}

void CDlgRemoteControlCustom::OnAstatic() 
{
	m_wndPosition.ShowWindow( TRUE );
}

void CDlgRemoteControlCustom::PickIC()
{
	//
	m_stTrayMap.LockUI();

	//
	ChangeUI( theApp.enRemoteMoving );

	//
	m.RemoteInterlock.PickIC = true;
	m.RemoteInterlock.ReleaseIC = false;

	//
	m.PanelButton.BtnStartPushed = true;
}
LRESULT CDlgRemoteControlCustom::OnRemoteAlarm(WPARAM p, LPARAM l)
{
	m_ledAlarm = true;

	ChangeUI( theApp.enRemoteAlarm );

	return true;
}
LRESULT CDlgRemoteControlCustom::OnRemotePickIC(WPARAM p, LPARAM l)
{
	ChangeUI( theApp.enRemoteStandy );

	m_stTrayMap.UnLockUI();

	return true;
}
LRESULT CDlgRemoteControlCustom::OnRemoteReleaseIC(WPARAM p, LPARAM l)
{
	ChangeUI( theApp.enRemoteMoving );

	m_ledReady = false;

	return true;
}
LRESULT CDlgRemoteControlCustom::OnRemoteReady(WPARAM p, LPARAM l)
{
	ChangeUI( theApp.enRemoteWaitOK );

	m_ledReady = true;

	return true;
}
void CDlgRemoteControlCustom::ContinueIC()
{
	RecoverUI();

	m.PanelButton.BtnStartPushed = true;
}
void CDlgRemoteControlCustom::ReleaseIC()
{
	ChangeUI( theApp.enRemoteMoving );

	m.RemoteInterlock.PickIC = false;
	m.RemoteInterlock.ReleaseIC = true;

	//
}
bool CDlgRemoteControlCustom::IsInputMark()
{
	bool bMarked = false;
#if 0
	return bMarked;
#else
	int m_iPos = m.RemoteInterlock.RemotePosition;

	int col = 0;
	int row = 0;
	
	col = m_iPos % m_trayMap.iCol;
	row = m_iPos / m_trayMap.iCol;
	
	if( m_trayMap.iStatus[col][row] == 4 || m_trayMap.iStatus[col][row] == 1 )
		bMarked = true;

	return bMarked;
#endif
}
void CDlgRemoteControlCustom::OnEPickIc() 
{
	if( IsInputMark() )
	{
		if(IDYES != AfxMessageBox("Data is be marked. Continue?\n",
			MB_YESNO|MB_ICONEXCLAMATION))
		{
			return;		
		}
		else
		{
			
		}
	}

	PickIC();
}

void CDlgRemoteControlCustom::OnEReleaseIc() 
{
	ReleaseIC();
}

void CDlgRemoteControlCustom::OnEContinue() 
{
	ContinueIC();
}

