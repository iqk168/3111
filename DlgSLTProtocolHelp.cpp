// DlgSLTProtocolHelp.cpp : implementation file
//

#include "stdafx.h"
#include "deer.h"
#include "DlgSLTProtocolHelp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgSLTProtocolHelp dialog


CDlgSLTProtocolHelp::CDlgSLTProtocolHelp(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgSLTProtocolHelp::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgSLTProtocolHelp)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgSLTProtocolHelp::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgSLTProtocolHelp)
	DDX_Control(pDX, IDC_SLT_HELP, m_wndSLTHelp);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgSLTProtocolHelp, CDialog)
	//{{AFX_MSG_MAP(CDlgSLTProtocolHelp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgSLTProtocolHelp message handlers

BOOL CDlgSLTProtocolHelp::PreTranslateMessage(MSG* pMsg) 
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

BOOL CDlgSLTProtocolHelp::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	InitValue();
	
	InitUI();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
void CDlgSLTProtocolHelp::InitValue()
{
	CString csNote = _T("");

	// SLT Protocol Help
	CString csFile = _T("");
	csFile = m.FilePath.SLTProtocolNotePath;

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
	m_wndSLTHelp.SetWindowText( csNote );
}
void CDlgSLTProtocolHelp::InitUI()
{

}