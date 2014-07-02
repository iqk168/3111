// DlgSettingRs232.cpp : implementation file
//

#include "stdafx.h"
#include "deer.h"
#include "DlgSettingRs232.h"
#include "DlgSettingNote.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgSettingRs232 dialog


CDlgSettingRs232::CDlgSettingRs232(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgSettingRs232::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgSettingRs232)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	m_csRs232File = _T("");	

	m_csExtendErrMsg = _T("");
}


void CDlgSettingRs232::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgSettingRs232)
	DDX_Control(pDX, IDC_IF_NOTE,				m_wndIfNote);
	DDX_Control(pDX, IDC_RS232_START_DLEAY,		m_wndSendStartDelay);
	DDX_Control(pDX, IDC_RS232_TIMEOUT,			m_wndRs232Timeout);
	DDX_Control(pDX, IDC_RS232_START,			m_wndRs232Start);
	DDX_Control(pDX, IDC_RS232_READY,			m_wndRs232Ready);
	DDX_Control(pDX, IDC_RS232_GO,				m_wndRs232Go);
	DDX_Control(pDX, IDC_RS232_BIN,				m_wndRs232Bin);
	DDX_Control(pDX, IDC_E_TAIL,				m_wndRs232Tail);
	DDX_Control(pDX, IDC_E_HEADER,				m_wndRs232Header);
	DDX_Control(pDX, IDC_FILE,					m_wndFile);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgSettingRs232, CDialog)
	//{{AFX_MSG_MAP(CDlgSettingRs232)
	ON_BN_CLICKED(IDC_NOTE,						OnNote)
	ON_BN_CLICKED(IDC_FILE,						OnFile)
	ON_BN_CLICKED(IDC_E_STATIC,					OnEStatic)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgSettingRs232 message handlers

BOOL CDlgSettingRs232::PreTranslateMessage(MSG* pMsg) 
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

BOOL CDlgSettingRs232::OnInitDialog() 
{
	CDialog::OnInitDialog();

	InitIfNote();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
void CDlgSettingRs232::InitIfNote()
{
	CString csMsg = _T("");
	csMsg = f.LoadIfNote(theApp.enNIfRs232);
	csMsg.TrimLeft();
	csMsg.TrimRight();
	if( csMsg != "" )
	{
		csMsg.Replace("\\r\\n", "\r\n");
//		csMsg += "\r\n";
	}	

	CString csSystem = _T("");
	int m_iBaudRate = f.GetTesterBaudRate();
	csSystem.Format("Com Port: %d, Rate: %d", 
		m.m_HandlerComPort.iPortTester, m_iBaudRate );
	csMsg += csSystem;

	//
	m_wndIfNote.SetWindowText( csMsg );

	//
	m_wndIfNote.ShowWindow( TRUE );
}
//
void CDlgSettingRs232::LoadFile()
{
	tagIfRs232Setting	m_IffileRs232;

	CString csFile = _T("");
	csFile = m.FilePath.InterfaceRs232Path + m_csRs232File;

	// Header
	f.GetSetting(csFile, "Command Format", "CommandHeader",		m_IffileRs232.m_csCmdHeader );
	f.GetSetting(csFile, "Command Format", "CommandTailHeader",	m_IffileRs232.m_csCmdTailHeader );

	// HandShake communcaion
	f.GetSetting(csFile, "Command Format", "Command Ready",		m_IffileRs232.m_csCmdReady );
	f.GetSetting(csFile, "Command Format", "Command Start",		m_IffileRs232.m_csCmdStart );
	f.GetSetting(csFile, "Command Format", "Command Go",		m_IffileRs232.m_csCmdGo );
	f.GetSetting(csFile, "Command Format", "Command Bin",		m_IffileRs232.m_csCmdBin );
	
	// Timeout
	f.GetSetting(csFile, "Command Format", "Command Timeout",	m_IffileRs232.m_dCmdTimeout = m.Setting.m_dTimeoutHighLimit );
	f.GetSetting(csFile, "Command Format", "Send Start Delay",	m_IffileRs232.m_dSendStartDleay = _SendStartDelayMax );

	m_IfRs232 = m_IffileRs232;
}
void CDlgSettingRs232::InitValue()
{
	CString m_csTimeout = _T("");
	m_csTimeout.Format("%5.2f", m_IfRs232.m_dCmdTimeout );
	m_csTimeout.TrimLeft();
	m_csTimeout.TrimRight();
	m_wndRs232Timeout.SetWindowText( m_csTimeout );

	CString m_csSendStartDelay = _T("");
	m_csSendStartDelay.Format("%5.2f", m_IfRs232.m_dSendStartDleay );
	m_wndSendStartDelay.SetWindowText( m_csSendStartDelay );

	m_wndRs232Start.SetWindowText( m_IfRs232.m_csCmdStart );
	m_wndRs232Ready.SetWindowText( m_IfRs232.m_csCmdReady );
	m_wndRs232Go.SetWindowText( m_IfRs232.m_csCmdGo );
	m_wndRs232Bin.SetWindowText( m_IfRs232.m_csCmdBin );
	m_wndRs232Tail.SetWindowText( m_IfRs232.m_csCmdTailHeader );
	m_wndRs232Header.SetWindowText( m_IfRs232.m_csCmdHeader );
}
bool CDlgSettingRs232::SaveData()
{
	bool bOK = true;

	return bOK;
}
void CDlgSettingRs232::SetFile(CString csfile)
{
	m_csRs232File = csfile;
	m_wndFile.SetWindowText( m_csRs232File );

	//
	LoadFile();
	
	//
	InitValue();
}
void CDlgSettingRs232::OnNote() 
{
	CDlgSettingNote dlg( theApp.enRS232 );
	dlg.DoModal();
}

void CDlgSettingRs232::OnFile() 
{
	
	
}

bool CDlgSettingRs232::GetDataFromUI(tagIfRs232Setting &UIData)
{
	bool bGetOK = true;

	m_csExtendErrMsg = "";

	////////////////////////////////////////////////////////////
	// Get data from UI

	tagIfRs232Setting	m_IfUIRs232;

	// Timeout
	CString m_csTimeout = _T("");
	m_wndRs232Timeout.GetWindowText( m_csTimeout );
	m_csTimeout.TrimLeft();
	m_csTimeout.TrimRight();
	m_IfUIRs232.m_dCmdTimeout = atof( m_csTimeout );

	// Send Start Delay
	CString m_csSendStartDelay = _T("");
	m_wndSendStartDelay.GetWindowText( m_csSendStartDelay );
	m_csSendStartDelay.TrimLeft();
	m_csSendStartDelay.TrimRight();
	m_IfUIRs232.m_dSendStartDleay = atof( m_csSendStartDelay );

	// Start 
	CString csStart = _T("");
	m_wndRs232Start.GetWindowText( csStart );
	csStart.TrimLeft();
	csStart.TrimRight();
	m_IfUIRs232.m_csCmdStart = csStart;

	// Ready
	CString csReady = _T("");
	m_wndRs232Ready.GetWindowText( csReady );
	csReady.TrimLeft();
	csReady.TrimRight();
	m_IfUIRs232.m_csCmdReady = csReady;

	// Go
	CString csGo = _T("");
	m_wndRs232Go.GetWindowText( csGo );
	csGo.TrimLeft();
	csGo.TrimRight();
	m_IfUIRs232.m_csCmdGo = csGo;

	// Bin
	CString csBin = _T("");
	m_wndRs232Bin.GetWindowText( csBin );
	csBin.TrimLeft();
	csBin.TrimRight();
	m_IfUIRs232.m_csCmdBin = csBin;

	// Header
	CString csHeader = _T("");
	m_wndRs232Tail.GetWindowText( csHeader );
	csHeader.TrimLeft();
	csHeader.TrimRight();
	m_IfUIRs232.m_csCmdTailHeader = csHeader;

	// Tail
	CString csTail = _T("");
	m_wndRs232Header.GetWindowText( csTail );	
	csTail.TrimLeft();
	csTail.TrimRight();
	m_IfUIRs232.m_csCmdHeader = csTail;

	// Valid
	if( m_IfUIRs232.m_csCmdBin == "" || 
		m_IfUIRs232.m_csCmdGo == "" || 
		m_IfUIRs232.m_csCmdHeader == "" ||
		m_IfUIRs232.m_csCmdReady == "" ||
		m_IfUIRs232.m_csCmdStart == "" ||
		m_IfUIRs232.m_csCmdTailHeader == "" ||
		m_IfUIRs232.m_dCmdTimeout == 0 || 
		m_IfUIRs232.m_dCmdTimeout < 0 ||
		m_IfUIRs232.m_dSendStartDleay == 0 ||
		m_IfUIRs232.m_dSendStartDleay < 0 )
	{		
		if( m_IfUIRs232.m_dCmdTimeout < 0 )
			m_csExtendErrMsg += "Timeout can't < 0\r\n";

		if( m_IfUIRs232.m_dSendStartDleay < 0 )
			m_csExtendErrMsg += "Send Start Delay can't < 0\r\n";

		if( m_IfUIRs232.m_dSendStartDleay == 0 )
			m_csExtendErrMsg += "Send Start Delay can't be 0\r\n";

		if( m_IfUIRs232.m_dCmdTimeout == 0 )
			m_csExtendErrMsg += "Timeout can't be 0\r\n";

		if( m_IfUIRs232.m_csCmdBin == "" )
			m_csExtendErrMsg += "Bin field can't be empty\r\n";

		if( m_IfUIRs232.m_csCmdGo == "" )
			m_csExtendErrMsg += "Go field be empty\r\n";

		if( m_IfUIRs232.m_csCmdHeader == "" )
			m_csExtendErrMsg += "Header field be empty\r\n";

		if( m_IfUIRs232.m_csCmdReady == "" )
			m_csExtendErrMsg += "Ready field be empty\r\n";

		if( m_IfUIRs232.m_csCmdStart == "" )
			m_csExtendErrMsg += "Start field be empty\r\n";

		if( m_IfUIRs232.m_csCmdTailHeader == "" )
			m_csExtendErrMsg += "Tail field be empty\r\n";

		bGetOK = false;
		return bGetOK;
	}

	UIData = m_IfUIRs232;

	return bGetOK;
}
void CDlgSettingRs232::SaveDataToFile(tagIfRs232Setting FileData)
{
	////////////////////////////////////////////////////////////
	// Save data to file
	tagIfRs232Setting m_IffileRs232;
	m_IffileRs232 = FileData;

	CString csFile = _T("");
	csFile = m.FilePath.InterfaceRs232Path + m_csRs232File;

	// Header
	f.SaveSetting(csFile, "Command Format", "CommandHeader",		m_IffileRs232.m_csCmdHeader );
	f.SaveSetting(csFile, "Command Format", "CommandTailHeader",	m_IffileRs232.m_csCmdTailHeader );

	// HandShake communcaion
	f.SaveSetting(csFile, "Command Format", "Command Ready",		m_IffileRs232.m_csCmdReady );
	f.SaveSetting(csFile, "Command Format", "Command Start",		m_IffileRs232.m_csCmdStart );
	f.SaveSetting(csFile, "Command Format", "Command Go",			m_IffileRs232.m_csCmdGo );
	f.SaveSetting(csFile, "Command Format", "Command Bin",			m_IffileRs232.m_csCmdBin );
	
	// Timeout
	f.SaveSetting(csFile, "Command Format", "Command Timeout",		m_IffileRs232.m_dCmdTimeout );
	f.SaveSetting(csFile, "Command Format", "Send Start Delay",		m_IffileRs232.m_dSendStartDleay );
}
bool CDlgSettingRs232::SaveRS232Data()
{
	bool bOK = true;

	//
	tagIfRs232Setting	m_IfUIRs232;
	if( !GetDataFromUI( m_IfUIRs232 ) )
		bOK = false;

	//
	if( bOK )
		SaveDataToFile( m_IfUIRs232 );

	return bOK;
}
void CDlgSettingRs232::OnEStatic() 
{
	m_wndFile.ShowWindow( TRUE );		
}
