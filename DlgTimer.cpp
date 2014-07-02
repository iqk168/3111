// DlgTimer.cpp : implementation file
//

#include "stdafx.h"
#include "deer.h"
#include "DlgTimer.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgTimer dialog


CDlgTimer::CDlgTimer(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgTimer::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgTimer)

	m_dInsertPuff		= 0.0;
	m_dInsertPick		= 0.0;
	m_dPickPuff			= 0.0;
	m_dPickPick			= 0.0;	


	//}}AFX_DATA_INIT
	m_fChange = false;
}

//
bool CDlgTimer::CheckValue()
{
	bool bOK = true;

	if( m_dInsertPuff > m.Setting.m_dTimerHighLimit || m_dInsertPuff < m.Setting.m_dTimerLowLimit )
		bOK = false;
	if( m_dInsertPick > m.Setting.m_dTimerHighLimit || m_dInsertPick < m.Setting.m_dTimerLowLimit )
		bOK = false;
	
	if( m_dPickPuff > m.Setting.m_dTimerHighLimit || m_dPickPuff < m.Setting.m_dTimerLowLimit )
		bOK = false;
	if( m_dPickPick > m.Setting.m_dTimerHighLimit || m_dPickPick < m.Setting.m_dTimerLowLimit )
		bOK = false;

	return bOK;
}

void CDlgTimer::InitValue()
{
	m_dInsertPuff		= m.Timer.m_dInsertPuff;
	m_dInsertPick		= m.Timer.m_dInsertPick;
	m_dPickPuff			= m.Timer.m_dPickPuff;
	m_dPickPick			= m.Timer.m_dPickPick;
	UpdateData( FALSE );
}

void CDlgTimer::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgTimer)
	DDX_Control(pDX, IDC_MODIFY_PARAMETER,		m_btnModify);
	DDX_Control(pDX, IDOK,						m_btnOK);
	//
	DDX_Control(pDX, IDCANCEL,					m_btnCancel);	
	// Arm
	DDX_Text(pDX, IDC_TIMER_INSERT_PICK_PUFF,	m_dInsertPuff);
	DDX_Text(pDX, IDC_TIMER_INSERT_PICK_VAC,	m_dInsertPick);
	DDX_Text(pDX, IDC_TIMER_PICK_PUFF,			m_dPickPuff);
	DDX_Text(pDX, IDC_TIMER_PICK_VAC,			m_dPickPick);

	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgTimer, CDialog)
	//{{AFX_MSG_MAP(CDlgTimer)
	ON_WM_CLOSE()
	ON_WM_TIMER()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_MODIFY_PARAMETER,			OnModifyParameter)
	ON_EN_CHANGE(IDC_TIMER_PICK_VAC,			OnChangePickVac)
	ON_EN_CHANGE(IDC_TIMER_PICK_PUFF,			OnChangePickPuff)
	ON_EN_CHANGE(IDC_TIMER_INSERT_PICK_VAC,		OnChangeInserterPickVac)
	ON_EN_CHANGE(IDC_TIMER_INSERT_PICK_PUFF,	OnChangeInserterPickPuff)

	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgTimer message handlers

void CDlgTimer::OnOK() 
{	
	if(m_fChange)
	{
		if(IDYES != AfxMessageBox("Data is modified. Save?\n",
			MB_YESNO|MB_ICONEXCLAMATION))
		{
			m.Info.bSubDlgOpen = false;
			f.UpdateButtonState();
			CDialog::OnOK();
		}
		else
		{
			OnModifyParameter();
			m.Info.bSubDlgOpen = false;
			f.UpdateButtonState();	
			CDialog::OnOK();
		}
		// Data already be modify.
		// So. 
		// If User say YES. We call OnOK() function to store alignment value
		// If User say NO. We did not do anything.
	}
	else
	{
		m.Info.bSubDlgOpen = false;
		f.UpdateButtonState();
	
		CDialog::OnOK();
		// Data not be modify.
		// Just Get out the Timer dialog.
	}
}

void CDlgTimer::OnCancel() 
{
	if(m_fChange)
	{
		if(IDYES != AfxMessageBox("Data is modified. Save?\n",
			MB_YESNO|MB_ICONEXCLAMATION))
		{
			m.Info.bSubDlgOpen = false;
			f.UpdateButtonState();
			CDialog::OnCancel();
		}
		else
		{
			OnModifyParameter();
			m.Info.bSubDlgOpen = false;
			f.UpdateButtonState();	
			CDialog::OnCancel();
		}
		// Data already be modify.
		// So. 
		// If User say YES. We call OnOK() function to store alignment value
		// If User say NO. We did not do anything.
	}
	else
	{
		m.Info.bSubDlgOpen = false;
		f.UpdateButtonState();
	
		CDialog::OnCancel();
		// Data not be modify.
		// Just Get out the Alignment dialog.
	}
}

void CDlgTimer::OnClose() 
{
	m.Info.bSubDlgOpen = false;
	f.UpdateButtonState();
	
	CDialog::OnClose();
}

BOOL CDlgTimer::OnInitDialog() 
{
	CDialog::OnInitDialog();

	m.Info.bSubDlgOpen = true;
	f.UpdateButtonState();

	// init button 
	m_btnOK.SetIcon(IDI_OK);
	m_btnOK.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnOK.SetFlat(FALSE);
	
	m_btnCancel.SetIcon(IDI_CANCEL);
	m_btnCancel.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnCancel.SetFlat(FALSE);

	m_btnModify.SetIcon(IDI_SAVE);
	m_btnModify.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnModify.SetFlat(FALSE);

	InitValue();
	// Get InitValue and display to dialog.

	//
	InitTips();

	//
	f.SetTitleExtend(this, theApp.enTitleTrayFile );

	//
	f.ChangeLanguage(GetSafeHwnd());
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
void CDlgTimer::InitTips()
{
	// Init Tips
	m_ToolTip.Create(this);
	m_ToolTip.SetMaxTipWidth(800);
	m_ToolTip.SetDelayTime( TTDT_AUTOPOP, 10000 );
	m_ToolTip.SetDelayTime( TTDT_INITIAL, 25 );
	m_ToolTip.EnableToolTips(true);

	//
	m_ToolTip.AddTool( GetDlgItem(IDC_STATIC_AMZ_BLOW),	
		_T("#1 effect arm z place ic to tray\r\n#2 effect arm z place ic to shuttle\r\n It will turn on blow timeout") );

	m_ToolTip.AddTool( GetDlgItem(IDC_STATIC_AMZ_VACC),	
		_T("#1 effect arm z pick ic from tray\r\n#2 effect arm z pick ic from shuttle\r\n It will turn on vacc unitl sensor on or timeout") );
	//
	m_ToolTip.AddTool( GetDlgItem(IDC_STATIC_TSZ_BLOW),	
		_T("#1 effect ts z place ic to socket (drop mode)\r\n#2 effect ts z place ic to shuttle\r\n It will turn on blow timeout") );

	m_ToolTip.AddTool( GetDlgItem(IDC_STATIC_TSZ_VACC),	
		_T("#1 effect ts z pick ic from socket\r\n#2 effect ts z pick ic from shuttle\r\n It will turn on vacc unitl sensor on or timeout") );

}
void CDlgTimer::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	
	CDialog::OnTimer(nIDEvent);
}

//////////////////////////////////////////////////////
// On Change 
void CDlgTimer::OnChangePickVac()
{
	m_fChange = true;
}
void CDlgTimer::OnChangePickPuff()
{
	m_fChange = true;
}
void CDlgTimer::OnChangeInserterPickVac()
{
	m_fChange = true;
}
void CDlgTimer::OnChangeInserterPickPuff()
{
	m_fChange = true;
}

void CDlgTimer::OnDestroy() 
{
	m.Info.bSubDlgOpen = false;
	f.UpdateButtonState();

	CDialog::OnDestroy();	
}

void CDlgTimer::OnModifyParameter() 
{
	if( UpdateData() )
	{		
		if( !CheckValue() )
		{
			CString cs;
			cs.Format("Timer Set Value out of range.! Please reset the value [%5.2f and %5.2f]",
				m.Setting.m_dTimerHighLimit, m.Setting.m_dTimerLowLimit);
			AfxMessageBox( cs );
			return;
		}

		m.Timer.m_dInsertPuff = m_dInsertPuff;
		m.Timer.m_dInsertPick = m_dInsertPick;
		m.Timer.m_dPickPuff   = m_dPickPuff;
		m.Timer.m_dPickPick   = m_dPickPick;	

		f.SaveTimer();

		CDialog::OnOK();
	}
}

BOOL CDlgTimer::PreTranslateMessage(MSG* pMsg) 
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


