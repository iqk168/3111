// DlgAutoRetry.cpp : implementation file
//

#include "stdafx.h"
#include "deer.h"
#include "DlgAutoRetry.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgAutoRetry dialog


CDlgAutoRetry::CDlgAutoRetry(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgAutoRetry::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgAutoRetry)
	m_iArmZRetry = 0;	
	//}}AFX_DATA_INIT

	m_fChange = false;
}


void CDlgAutoRetry::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgAutoRetry)
	DDX_Control(pDX, IDOK,			m_btnOK);
	DDX_Control(pDX, IDCANCEL,		m_btnCancel);
	DDX_Text(pDX, IDC_AMRZ_RETRY,	m_iArmZRetry);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgAutoRetry, CDialog)
	//{{AFX_MSG_MAP(CDlgAutoRetry)
	ON_EN_CHANGE(IDC_AMRZ_RETRY, OnChangeAmrzRetry)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgAutoRetry message handlers

void CDlgAutoRetry::OnOK() 
{
	if( !CheckValue() )
	{
		//
		CString cs;
		cs.Format("The Max Value < %d", _MaxRetryCounter );
		AfxMessageBox( cs );

		// Reset Value to Max
		m_iArmZRetry = _MaxRetryCounter;
		UpdateData( FALSE );
		return;
	}

	UpdateData();

	//
	m.Setting.m_iAutoRetrySetting = m_iArmZRetry;

	//
	f.SaveAutoRetrySetting();
	
	//
	m.Info.bSubDlgOpen = false;
	f.UpdateButtonState();
	
	CDialog::OnOK();
}

void CDlgAutoRetry::OnCancel() 
{
	if( m_fChange )
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

BOOL CDlgAutoRetry::PreTranslateMessage(MSG* pMsg) 
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
void CDlgAutoRetry::InitTips()
{
	// Tips 
	// Init Tips
	m_ToolTip.Create(this);
	m_ToolTip.SetMaxTipWidth(800);
	m_ToolTip.SetDelayTime( TTDT_AUTOPOP, 10000 );
	m_ToolTip.SetDelayTime( TTDT_INITIAL, 25 );
	m_ToolTip.EnableToolTips(true);

	// 
	CString csInfo = _T("");
	csInfo.Format("%s&&%s", "If arm z pick ic fail, It will auto retry\r\n", 
		"ex: value set 2, 1 pick fail it will pick continue try 2 more times unitl pick success");
	m_ToolTip.AddTool( GetDlgItem(IDC_STATIC_AUTO_RETRY),	
		_T( csInfo ) );
}
void CDlgAutoRetry::InitValue()
{
	m_iArmZRetry = m.Setting.m_iAutoRetrySetting;

	UpdateData( FALSE );
}
bool CDlgAutoRetry::CheckValue()
{
	bool bOK = true;
	UpdateData();

	if( m_iArmZRetry > _MaxRetryCounter )
		bOK = false;

	return bOK;
}

BOOL CDlgAutoRetry::OnInitDialog() 
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
	f.SetTitleExtend(this, theApp.enTtileMachineFile );

	//
	f.ChangeLanguage(GetSafeHwnd());
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgAutoRetry::OnChangeAmrzRetry() 
{
	m_fChange = true;	
}
