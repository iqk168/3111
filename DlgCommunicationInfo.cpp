// DlgCommunicationInfo.cpp : implementation file
//

#include "stdafx.h"
#include "deer.h"
#include "DlgCommunicationInfo.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgCommunicationInfo dialog


CDlgCommunicationInfo::CDlgCommunicationInfo(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgCommunicationInfo::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgCommunicationInfo)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgCommunicationInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgCommunicationInfo)
	DDX_Control(pDX, IDC_CLEAR, m_btnClear);
	DDX_Control(pDX, IDOK,		m_btnOK);
	DDX_Control(pDX, IDCANCEL,	m_btnCancel);
	DDX_Control(pDX, IDC_LIST1, m_listInfo);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgCommunicationInfo, CDialog)
	//{{AFX_MSG_MAP(CDlgCommunicationInfo)
	ON_BN_CLICKED(IDC_CLEAR,	OnClear)
	ON_MESSAGE(WM_COMM_INFO,	OnCommunicationInfo)

	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgCommunicationInfo message handlers

BOOL CDlgCommunicationInfo::PreTranslateMessage(MSG* pMsg) 
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

BOOL CDlgCommunicationInfo::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// init button 
	m_btnClear.SetIcon(IDI_CLEAR_COUNT);;
	m_btnClear.SetAlign(CButtonST::ST_ALIGN_VERT);;
	m_btnClear.SetFlat(FALSE);

	m_btnOK.SetIcon(IDI_OK);;
	m_btnOK.SetAlign(CButtonST::ST_ALIGN_VERT);;
	m_btnOK.SetFlat(FALSE);
	
	m_btnCancel.SetIcon(IDI_CANCEL);
	m_btnCancel.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnCancel.SetFlat(FALSE);

	//
	CenterWindow();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
LRESULT CDlgCommunicationInfo::OnCommunicationInfo(WPARAM p, LPARAM l)
{
	CString csMsg = *(CString *)p;

	CString csTime = _T("");

	CTime time = CTime::GetCurrentTime();
	csTime.Format("%.4d, %.2d%.2d, %.2d.%.2d.%.2d, ", 
		time.GetYear(), time.GetMonth(), time.GetDay(), time.GetHour(), time.GetMinute(), time.GetSecond() );  
	
	CString csFinalMsg = _T("");
	csFinalMsg = csTime + csMsg;

	m_listInfo.InsertString(0, csFinalMsg);

	//
	return true;
}
void CDlgCommunicationInfo::OnClear() 
{
	m_listInfo.ResetContent();
}

void CDlgCommunicationInfo::OnOK() 
{
	
	CDialog::OnOK();
}

void CDlgCommunicationInfo::OnCancel() 
{
	
	CDialog::OnCancel();
}
