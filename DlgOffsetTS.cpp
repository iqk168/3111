// DlgOffsetTS.cpp : implementation file
//

#include "stdafx.h"
#include "deer.h"
#include "DlgOffsetTS.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgOffsetTS dialog


CDlgOffsetTS::CDlgOffsetTS(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgOffsetTS::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgOffsetTS)
	m_dOffsetTSPick = 0.0;
	m_dOffsetTSPlace = 0.0;
	m_dOffsetTSContact = 0.0;
	//}}AFX_DATA_INIT

	m_Offset = m.m_Offset;

	m_fChange = false;
}


void CDlgOffsetTS::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgOffsetTS)
	DDX_Control(pDX, IDOK,					m_btnOK);
	DDX_Control(pDX, IDCANCEL,				m_btnCancel);
	DDX_Text(pDX, IDC_OFFSET_TS_PICK,		m_dOffsetTSPick);
	DDX_Text(pDX, IDC_OFFSET_TS_PLACE,		m_dOffsetTSPlace);
	DDX_Text(pDX, IDC_OFFSET_TS_CONTACT,	m_dOffsetTSContact);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgOffsetTS, CDialog)
	//{{AFX_MSG_MAP(CDlgOffsetTS)
	ON_WM_TIMER()
	ON_EN_CHANGE(IDC_OFFSET_TS_PICK,		OnChangeOffsetTsPick)
	ON_EN_CHANGE(IDC_OFFSET_TS_PLACE,		OnChangeOffsetTsPlace)
	ON_EN_CHANGE(IDC_OFFSET_TS_CONTACT,		OnChangeOffsetTsContact)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgOffsetTS message handlers

BOOL CDlgOffsetTS::PreTranslateMessage(MSG* pMsg) 
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

BOOL CDlgOffsetTS::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m.Info.bSubDlgOpen = true;
	f.UpdateButtonState();

	// init button 
	m_btnOK.SetIcon(IDI_SAVE);
	m_btnOK.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnOK.SetFlat(FALSE);
	
	m_btnCancel.SetIcon(IDI_CANCEL);
	m_btnCancel.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnCancel.SetFlat(FALSE);

	//
	InitValue();

	//
	InitTips();

	//
	f.SetTitleExtend(this, theApp.enTitleTrayFile );

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
void CDlgOffsetTS::InitValue()
{
	// Test Site 
	m_dOffsetTSContact		= m_Offset.TestSite.contact;
	m_dOffsetTSPick			= m_Offset.TestSite.pick;
	m_dOffsetTSPlace		= m_Offset.TestSite.place;

	UpdateData(FALSE);

	m_fChange = false;	
}
void CDlgOffsetTS::InitTips()
{
	// Tips 
	// Init Tips
	m_ToolTip.Create(this);
	m_ToolTip.SetMaxTipWidth(800);
	m_ToolTip.SetDelayTime( TTDT_AUTOPOP, 10000 );
	m_ToolTip.SetDelayTime( TTDT_INITIAL, 25 );
	m_ToolTip.EnableToolTips(true);

}
void CDlgOffsetTS::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	
	CDialog::OnTimer(nIDEvent);
}

void CDlgOffsetTS::OnOK() 
{
	if( !SaveData() )
		return;

	m.Info.bSubDlgOpen = false;
	f.UpdateButtonState();
	
	CDialog::OnOK();
}
bool CDlgOffsetTS::SaveData()
{
	bool bOK = true;

	if( !CheckValue() )
	{
		bOK = false;
		CString csMsg = _T("");
		csMsg.Format("Offset value is out of range.! %5.2f ~ %5.2f", 
			m.Setting.m_dOffsetHighLimit, m.Setting.m_dOffsetLowLimit);
		AfxMessageBox( csMsg );
		return bOK;
	}
	
	UpdateData();

	// Test Site 
	m_Offset.TestSite.contact	= m_dOffsetTSContact;
	m_Offset.TestSite.pick		= m_dOffsetTSPick;
	m_Offset.TestSite.place		= m_dOffsetTSPlace;

	m.m_Offset = m_Offset;

	f.SaveOffset();

	return bOK;
}
bool CDlgOffsetTS::CheckValue()
{
	bool bValueOK = true;

	//
	UpdateData();

	// Test Site 
	if( m_dOffsetTSContact > m.Setting.m_dOffsetHighLimit || 
		m_dOffsetTSContact < m.Setting.m_dOffsetLowLimit )
	{
		bValueOK = false;
	}

	if( m_dOffsetTSPick > m.Setting.m_dOffsetHighLimit || 
		m_dOffsetTSPick < m.Setting.m_dOffsetLowLimit )
	{
		bValueOK = false;
	}

	if( m_dOffsetTSPlace > m.Setting.m_dOffsetHighLimit || 
		m_dOffsetTSPlace < m.Setting.m_dOffsetLowLimit )
	{
		bValueOK = false;
	}

	return bValueOK;

}
void CDlgOffsetTS::OnCancel() 
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
			OnOK();
	}
	else
	{
		m.Info.bSubDlgOpen = false;
		f.UpdateButtonState();
		CDialog::OnCancel();		
	}
}

void CDlgOffsetTS::OnChangeOffsetTsPick() 
{
	m_fChange = true;
}

void CDlgOffsetTS::OnChangeOffsetTsPlace() 
{
	m_fChange = true;
}

void CDlgOffsetTS::OnChangeOffsetTsContact() 
{
	m_fChange = true;
}
