// DlgSummaryReportDetail.cpp : implementation file
//

#include "stdafx.h"
#include "deer.h"
#include "DlgSummaryReportDetail.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgSummaryReportDetail dialog


CDlgSummaryReportDetail::CDlgSummaryReportDetail(CString csFile, CWnd* pParent /*=NULL*/)
	: CDialog(CDlgSummaryReportDetail::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgSummaryReportDetail)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	m_file = csFile;

	//
	csNote = "";
}


void CDlgSummaryReportDetail::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgSummaryReportDetail)
	DDX_Control(pDX, IDC_SUMMARY_REPORT,	m_wndSummaryReport);
	DDX_Control(pDX, IDC_FILE_NAME,			m_wndFileName);
	DDX_Control(pDX, IDOK,					m_btnOK);
	DDX_Control(pDX, IDCANCEL,				m_btnCancel);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgSummaryReportDetail, CDialog)
	//{{AFX_MSG_MAP(CDlgSummaryReportDetail)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgSummaryReportDetail message handlers

void CDlgSummaryReportDetail::OnOK() 
{
	
	CDialog::OnOK();
}

void CDlgSummaryReportDetail::OnCancel() 
{
	
	CDialog::OnCancel();
}

BOOL CDlgSummaryReportDetail::PreTranslateMessage(MSG* pMsg) 
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

BOOL CDlgSummaryReportDetail::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_btnOK.SetIcon(IDI_OK);
	m_btnOK.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnOK.SetFlat(FALSE);
	
	m_btnCancel.SetIcon(IDI_CANCEL);
	m_btnCancel.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnCancel.SetFlat(FALSE);
	
	//
	InitValue();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgSummaryReportDetail::InitValue()
{
	// File Name..
	m_wndFileName.SetWindowText( "  " + m_file );

	// Summary Report 
	CString csFile = _T("");
	csFile = m.FilePath.SummaryReportPath + m_file;

	unsigned char cTemp[1001] = {0};
	unsigned long ulNumRead = 0;
	HANDLE	m_hComm = NULL;

	m_hComm = CreateFile (  csFile,// Pointer to the name of the port
		GENERIC_READ | GENERIC_WRITE,
		// Access (read/write) mode
		0,            // Share mode
		NULL,         // Pointer to the security attribute
		OPEN_EXISTING,// How to open the serial port
		0,            // Port attributes
		NULL);        // Handle to port with attribute

	while(1)
	{
		::ReadFile(m_hComm, cTemp, sizeof(cTemp), &ulNumRead, NULL);
		if(ulNumRead == 0)
			break;
		// No more data. break.
		
		for(int i=0;i<ulNumRead;i++ )
			csNote += cTemp[i];
	}

	::CloseHandle(m_hComm);
	m_hComm = NULL;

	// Show Data
	m_wndSummaryReport.SetWindowText( csNote );
}
