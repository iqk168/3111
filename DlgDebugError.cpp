// DlgDebugError.cpp : implementation file
//

#include "stdafx.h"
#include "deer.h"
#include "DlgDebugError.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgDebugError dialog


CDlgDebugError::CDlgDebugError(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgDebugError::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgDebugError)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_iError = 0;
}


void CDlgDebugError::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgDebugError)
	DDX_Control(pDX, IDOK,			m_btnOK);
	DDX_Control(pDX, IDCANCEL,		m_btnCancel);
	DDX_Text(pDX, IDC_ERROR,		m_iError);

	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgDebugError, CDialog)
	//{{AFX_MSG_MAP(CDlgDebugError)
	ON_BN_CLICKED(IDC_OPEN_ERROR, OnOpenError)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgDebugError message handlers

void CDlgDebugError::OnOK() 
{
	
	CDialog::OnOK();
}

void CDlgDebugError::OnCancel() 
{
	
	CDialog::OnCancel();
}

BOOL CDlgDebugError::PreTranslateMessage(MSG* pMsg) 
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

BOOL CDlgDebugError::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// init button 
	m_btnOK.SetIcon(IDI_OK);;
	m_btnOK.SetAlign(CButtonST::ST_ALIGN_VERT);;
	m_btnOK.SetFlat(FALSE);
	
	m_btnCancel.SetIcon(IDI_CANCEL);
	m_btnCancel.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnCancel.SetFlat(FALSE);
	

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgDebugError::OnOpenError() 
{
	UpdateData();

	if( m_iError > 0  )
		m.Err.System.Code = m_iError;	
}
