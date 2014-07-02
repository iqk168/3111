// DlgJamRateReportToolLastReport.cpp : implementation file
//

#include "stdafx.h"
#include "deer.h"
#include "DlgJamRateReportToolLastReport.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgJamRateReportToolLastReport dialog


CDlgJamRateReportToolLastReport::CDlgJamRateReportToolLastReport(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgJamRateReportToolLastReport::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgJamRateReportToolLastReport)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgJamRateReportToolLastReport::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgJamRateReportToolLastReport)
	DDX_Control(pDX, IDC_FILE_TIME,				m_wndFileTime);
	DDX_Control(pDX, IDC_ERRORRATE_REPORT,		m_wndErrorRateReport);
	DDX_Control(pDX, IDCANCEL,					m_btnCancel);
	DDX_Control(pDX, IDOK,						m_btnOK);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgJamRateReportToolLastReport, CDialog)
	//{{AFX_MSG_MAP(CDlgJamRateReportToolLastReport)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgJamRateReportToolLastReport message handlers

void CDlgJamRateReportToolLastReport::OnOK() 
{
	
	CDialog::OnOK();
}

void CDlgJamRateReportToolLastReport::OnCancel() 
{
	
	CDialog::OnCancel();
}

BOOL CDlgJamRateReportToolLastReport::PreTranslateMessage(MSG* pMsg) 
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

BOOL CDlgJamRateReportToolLastReport::OnInitDialog() 
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

void CDlgJamRateReportToolLastReport::InitValue()
{
	CString csNote = _T("");

	// Error Rate Report 
	CString csFile = _T("");
	csFile = m.FilePath.JamRateReportPath;

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

	///

	// Show Data
	m_wndErrorRateReport.SetWindowText( csNote );

	// File Modify Time
	CString csfile_status;
	csfile_status.Format("%s", m.FilePath.JamRateReportPath );
	CFileStatus status;
	CFile::GetStatus( csfile_status, status );
	CString cc = _T("");
	cc.Format(" File Modify: %s", status.m_mtime.Format( "%Y/%m/%d %H:%M:%S" ) );
	m_wndFileTime.SetWindowText( cc );
}
