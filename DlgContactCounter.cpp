// DlgContactCounter.cpp : implementation file
//

#include "stdafx.h"
#include "deer.h"
#include "DlgContactCounter.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgContactCounter dialog


CDlgContactCounter::CDlgContactCounter(bool bClear, CWnd* pParent /*=NULL*/)
	: CDialog(CDlgContactCounter::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgContactCounter)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_bClear = bClear;
}


void CDlgContactCounter::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgContactCounter)
	DDX_Control(pDX, IDC_CLEAR,				m_btnClear);
	DDX_Control(pDX, IDC_CONTACT_COUNTER,	m_wndContactCounter);
	DDX_Control(pDX, IDOK,					m_btnOK);
	DDX_Control(pDX, IDCANCEL,				m_btnCancel);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgContactCounter, CDialog)
	//{{AFX_MSG_MAP(CDlgContactCounter)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_CLEAR, OnClear)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgContactCounter message handlers

void CDlgContactCounter::OnOK() 
{
	m.Info.bSubDlgOpen = false;
	f.UpdateButtonState();
	
	CDialog::OnOK();
}

void CDlgContactCounter::OnCancel() 
{
	m.Info.bSubDlgOpen = false;
	f.UpdateButtonState();

	CDialog::OnCancel();
}

BOOL CDlgContactCounter::OnInitDialog() 
{
	CDialog::OnInitDialog();

	m.Info.bSubDlgOpen = true;
	f.UpdateButtonState();
	
	// init button 
	m_btnOK.SetIcon(IDI_OK);;
	m_btnOK.SetAlign(CButtonST::ST_ALIGN_VERT);;
	m_btnOK.SetFlat(FALSE);
	
	m_btnCancel.SetIcon(IDI_CANCEL);
	m_btnCancel.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnCancel.SetFlat(FALSE);

	m_btnClear.SetIcon(IDI_CLEAR_COUNT);
	m_btnClear.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnClear.SetFlat(FALSE);


	// Init Value
	CString cs = _T("");
	cs.Format("%d", m.m_ContactCounterValue.lContactConter );
	m_wndContactCounter.SetWindowText( cs );
	//

	// 
	// 設定 Clear 的開關是否要啟動
	if( m_bClear )
		m_btnClear.EnableWindow( TRUE );
	else
		m_btnClear.EnableWindow( FALSE );

	//
	f.SetTitleExtend(this, theApp.enTtileMachineFile );

	//
	f.ChangeLanguage(GetSafeHwnd());
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgContactCounter::OnDestroy() 
{
	CDialog::OnDestroy();
	
}

void CDlgContactCounter::OnClear() 
{
	m.m_ContactCounterValue.lContactConter = 0;
	f.SaveContactCounter();

	CString cs = _T("");
	cs.Format("%d", m.m_ContactCounterValue.lContactConter );
	m_wndContactCounter.SetWindowText( cs );

	f.TSMessageCounter();
}
