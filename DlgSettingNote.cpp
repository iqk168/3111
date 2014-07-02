// DlgSettingNote.cpp : implementation file
//

#include "stdafx.h"
#include "deer.h"
#include "DlgSettingNote.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgSettingNote dialog


CDlgSettingNote::CDlgSettingNote(int iIftype, CWnd* pParent /*=NULL*/)
	: CDialog(CDlgSettingNote::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgSettingNote)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	m_iIftype = -1;

	m_iIftype = iIftype;
}


void CDlgSettingNote::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgSettingNote)
	DDX_Control(pDX, IDC_IF_NOTE,		m_wndIfReport);
	DDX_Control(pDX, IDCANCEL,			m_btnCancel);
	DDX_Control(pDX, IDOK,				m_btnOK);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgSettingNote, CDialog)
	//{{AFX_MSG_MAP(CDlgSettingNote)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgSettingNote message handlers

void CDlgSettingNote::OnOK() 
{
	
	CDialog::OnOK();
}

void CDlgSettingNote::OnCancel() 
{
	
	CDialog::OnCancel();
}

BOOL CDlgSettingNote::PreTranslateMessage(MSG* pMsg) 
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

BOOL CDlgSettingNote::OnInitDialog() 
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
	InitValue();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
CString CDlgSettingNote::GetIfNoteFileName()
{
	CString csFile = _T("");
	
	if( m_iIftype == theApp.enRS232 )
		csFile = m.FilePath.Rs232NotePath + "\\" + "If.Note";
	else if( m_iIftype == theApp.enTCP )
		csFile = m.FilePath.TcpNotePath + "\\" + "If.Note";
	else if( m_iIftype == theApp.enGPIB )
		csFile = m.FilePath.GpibNotePath + "\\" + "If.Note";
	else if( m_iIftype == theApp.enTTL )
		csFile = m.FilePath.TtlNotePath + "\\" + "If.Note";

	return csFile;
}
void CDlgSettingNote::LoadFile()
{	
	// If Note 
	CString csFile = _T("");
	csFile = GetIfNoteFileName();

	//
	CString csNote = _T("");

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
	m_wndIfReport.SetWindowText( csNote );
}
void CDlgSettingNote::InitValue()
{
	LoadFile();
}
