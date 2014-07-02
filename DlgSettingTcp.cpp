// DlgSettingTcp.cpp : implementation file
//

#include "stdafx.h"
#include "deer.h"
#include "DlgSettingTcp.h"
#include "DlgSettingNote.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgSettingTcp dialog


CDlgSettingTcp::CDlgSettingTcp(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgSettingTcp::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgSettingTcp)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	m_csTcpFile = _T("");

	m_csExtendErrMsg = _T("");
}

void CDlgSettingTcp::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgSettingTcp)
	DDX_Control(pDX, IDC_IF_NOTE,				m_wndIfNote);
	DDX_Control(pDX, IDC_TCP_START_DLEAY,		m_wndSendStartDelay);
	DDX_Control(pDX, IDC_TCP_TIMEOUT,			m_wndTcpTimeout);
	DDX_Control(pDX, IDC_TCP_START,				m_wndTcpStart);
	DDX_Control(pDX, IDC_TCP_READY,				m_wndTcpReady);
	DDX_Control(pDX, IDC_TCP_GO,				m_wndTcpGo);
	DDX_Control(pDX, IDC_TCP_BIN,				m_wndTcpBin);
	DDX_Control(pDX, IDC_E_TAIL,				m_wndTcpTail);
	DDX_Control(pDX, IDC_E_HEADER,				m_wndTcpHeader);
	DDX_Control(pDX, IDC_FILE,					m_wndFile);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgSettingTcp, CDialog)
	//{{AFX_MSG_MAP(CDlgSettingTcp)
	ON_BN_CLICKED(IDC_NOTE,						OnNote)
	ON_BN_CLICKED(IDC_E_STATIC,					OnEStatic)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgSettingTcp message handlers

BOOL CDlgSettingTcp::PreTranslateMessage(MSG* pMsg) 
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

BOOL CDlgSettingTcp::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	InitIfNote();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
void CDlgSettingTcp::InitIfNote()
{
	CString csMsg = _T("");
	csMsg = f.LoadIfNote(theApp.enNIfTcpIp);
	csMsg.TrimLeft();
	csMsg.TrimRight();
	if( csMsg != "" )
	{
		csMsg.Replace("\\r\\n", "\r\n");
	}	

	// 1.0Ah
	// Remove this function and re-build new one
	/*
	CString csSystem = _T("");
	CString csIP = _T("");
	char cIp[256];
	csIP = f.GetTesterIPAddress(cIp);
	int read = sizeof(cIp);
	for(int i=0; i<read; i++)
		csIP += cIp[i];
	csSystem.Format("IP: %s, Port: %d", csIP, _Tcp_If_Port);
	csMsg += csSystem;
	*/

	// 1.0Ah
	CString csSystem = _T("");
	CString csIP = _T("");
	f.GetHandlerIPAddress(csIP);
	csSystem.Format("IP: %s\nPort: %d", csIP, _Tcp_If_Port);
	csMsg += csSystem;

	//
	m_wndIfNote.SetWindowText( csMsg );

	//
	m_wndIfNote.ShowWindow( TRUE );
}
void CDlgSettingTcp::LoadFile()
{
	tagIfTcpSetting	m_IffileTcp;

	CString csFile = _T("");
	csFile = m.FilePath.InterfaceTcpPath + m_csTcpFile;

	// Header
	f.GetSetting(csFile, "Command Format", "CommandHeader",		m_IffileTcp.m_csCmdHeader );
	f.GetSetting(csFile, "Command Format", "CommandTailHeader",	m_IffileTcp.m_csCmdTailHeader );

	// HandShake communcaion
	f.GetSetting(csFile, "Command Format", "Command Ready",		m_IffileTcp.m_csCmdReady );
	f.GetSetting(csFile, "Command Format", "Command Start",		m_IffileTcp.m_csCmdStart );
	f.GetSetting(csFile, "Command Format", "Command Go",		m_IffileTcp.m_csCmdGo );
	f.GetSetting(csFile, "Command Format", "Command Bin",		m_IffileTcp.m_csCmdBin );
	
	// Timeout
	f.GetSetting(csFile, "Command Format", "Command Timeout",	m_IffileTcp.m_dCmdTimeout = m.Setting.m_dTimeoutHighLimit );
	f.GetSetting(csFile, "Command Format", "Send Start Delay",	m_IffileTcp.m_dSendStartDleay = _SendStartDelayMax );

	m_IfTcp = m_IffileTcp;
}
void CDlgSettingTcp::InitValue()
{
	CString m_csTimeout = _T("");
	m_csTimeout.Format("%5.2f", m_IfTcp.m_dCmdTimeout );
	m_csTimeout.TrimLeft();
	m_csTimeout.TrimRight();
	m_wndTcpTimeout.SetWindowText( m_csTimeout );

	CString m_csSendStartDelay = _T("");
	m_csSendStartDelay.Format("%5.2f", m_IfTcp.m_dSendStartDleay );
	m_csSendStartDelay.TrimLeft();
	m_csSendStartDelay.TrimRight();
	m_wndSendStartDelay.SetWindowText( m_csSendStartDelay );

	m_wndTcpStart.SetWindowText( m_IfTcp.m_csCmdStart );
	m_wndTcpReady.SetWindowText( m_IfTcp.m_csCmdReady );
	m_wndTcpGo.SetWindowText( m_IfTcp.m_csCmdGo );
	m_wndTcpBin.SetWindowText( m_IfTcp.m_csCmdBin );
	m_wndTcpTail.SetWindowText( m_IfTcp.m_csCmdTailHeader );
	m_wndTcpHeader.SetWindowText( m_IfTcp.m_csCmdHeader );
}

bool CDlgSettingTcp::SaveTcpData()
{
	bool bOK = true;

	//
	tagIfTcpSetting	m_IfUITcp;
	if( !GetDataFromUI( m_IfUITcp ) )
		bOK = false;

	//
	if( bOK )
		SaveDataToFile( m_IfUITcp );

	return bOK;
}
bool CDlgSettingTcp::GetDataFromUI(tagIfTcpSetting &UIData)
{
	bool bGetOK = true;

	m_csExtendErrMsg = "";

	////////////////////////////////////////////////////////////
	// Get data from UI

	tagIfTcpSetting	m_IfUITcp;

	// Send Start Delay
	CString m_csSendStartDelay = _T("");
	m_wndSendStartDelay.GetWindowText( m_csSendStartDelay );
	m_csSendStartDelay.TrimLeft();
	m_csSendStartDelay.TrimRight();
	m_IfUITcp.m_dSendStartDleay = atof( m_csSendStartDelay );

	// Timeout
	CString m_csTimeout = _T("");
	m_wndTcpTimeout.GetWindowText( m_csTimeout );
	m_csTimeout.TrimLeft();
	m_csTimeout.TrimRight();
	m_IfUITcp.m_dCmdTimeout = atof( m_csTimeout );

	// Start 
	CString csStart = _T("");
	m_wndTcpStart.GetWindowText( csStart );
	csStart.TrimLeft();
	csStart.TrimRight();
	m_IfUITcp.m_csCmdStart = csStart;

	// Ready
	CString csReady = _T("");
	m_wndTcpReady.GetWindowText( csReady );
	csReady.TrimLeft();
	csReady.TrimRight();
	m_IfUITcp.m_csCmdReady = csReady;

	// Go
	CString csGo = _T("");
	m_wndTcpGo.GetWindowText( csGo );
	csGo.TrimLeft();
	csGo.TrimRight();
	m_IfUITcp.m_csCmdGo = csGo;

	// Bin
	CString csBin = _T("");
	m_wndTcpBin.GetWindowText( csBin );
	csBin.TrimLeft();
	csBin.TrimRight();
	m_IfUITcp.m_csCmdBin = csBin;

	// Header
	CString csHeader = _T("");
	m_wndTcpTail.GetWindowText( csHeader );
	csHeader.TrimLeft();
	csHeader.TrimRight();
	m_IfUITcp.m_csCmdTailHeader = csHeader;

	// Tail
	CString csTail = _T("");
	m_wndTcpHeader.GetWindowText( csTail );	
	csTail.TrimLeft();
	csTail.TrimRight();
	m_IfUITcp.m_csCmdHeader = csTail;

	// Valid
	if( m_IfUITcp.m_csCmdBin == "" || 
		m_IfUITcp.m_csCmdGo == "" || 
		m_IfUITcp.m_csCmdHeader == "" ||
		m_IfUITcp.m_csCmdReady == "" ||
		m_IfUITcp.m_csCmdStart == "" ||
		m_IfUITcp.m_csCmdTailHeader == "" ||
		m_IfUITcp.m_dCmdTimeout == 0 || 
		m_IfUITcp.m_dCmdTimeout < 0 ||
		m_IfUITcp.m_dSendStartDleay == 0 || 
		m_IfUITcp.m_dSendStartDleay < 0 )
	{
		if( m_IfUITcp.m_dCmdTimeout < 0 )
			m_csExtendErrMsg += "Timeout can't < 0\r\n";

		if( m_IfUITcp.m_dSendStartDleay < 0 )
			m_csExtendErrMsg += "Send Start Delay can't < 0\r\n";

		if( m_IfUITcp.m_dSendStartDleay == 0 )
			m_csExtendErrMsg += "Send Start Delay can't be 0\r\n";

		if( m_IfUITcp.m_dCmdTimeout == 0 )
			m_csExtendErrMsg += "Timeout can't be 0\r\n";

		if( m_IfUITcp.m_csCmdBin == "" )
			m_csExtendErrMsg += "Bin field can't be empty\r\n";

		if( m_IfUITcp.m_csCmdGo == "" )
			m_csExtendErrMsg += "Go field be empty\r\n";

		if( m_IfUITcp.m_csCmdHeader == "" )
			m_csExtendErrMsg += "Header field be empty\r\n";

		if( m_IfUITcp.m_csCmdReady == "" )
			m_csExtendErrMsg += "Ready field be empty\r\n";

		if( m_IfUITcp.m_csCmdStart == "" )
			m_csExtendErrMsg += "Start field be empty\r\n";

		if( m_IfUITcp.m_csCmdTailHeader == "" )
			m_csExtendErrMsg += "Tail field be empty\r\n";

		bGetOK = false;
		return bGetOK;
	}

	UIData = m_IfUITcp;

	return bGetOK;
}
void CDlgSettingTcp::SaveDataToFile(tagIfTcpSetting FileData)
{
	////////////////////////////////////////////////////////////
	// Save data to file
	tagIfTcpSetting m_IffileTcp;
	m_IffileTcp = FileData;

	CString csFile = _T("");
	csFile = m.FilePath.InterfaceTcpPath + m_csTcpFile;

	// Header
	f.SaveSetting(csFile, "Command Format", "CommandHeader",		m_IffileTcp.m_csCmdHeader );
	f.SaveSetting(csFile, "Command Format", "CommandTailHeader",	m_IffileTcp.m_csCmdTailHeader );

	// HandShake communcaion
	f.SaveSetting(csFile, "Command Format", "Command Ready",		m_IffileTcp.m_csCmdReady );
	f.SaveSetting(csFile, "Command Format", "Command Start",		m_IffileTcp.m_csCmdStart );
	f.SaveSetting(csFile, "Command Format", "Command Go",			m_IffileTcp.m_csCmdGo );
	f.SaveSetting(csFile, "Command Format", "Command Bin",			m_IffileTcp.m_csCmdBin );
	
	// Timeout
	f.SaveSetting(csFile, "Command Format", "Command Timeout",		m_IffileTcp.m_dCmdTimeout );
	f.SaveSetting(csFile, "Command Format", "Send Start Delay",		m_IffileTcp.m_dSendStartDleay );
}
bool CDlgSettingTcp::SaveData()
{
	bool bOK = true;

	return bOK;
}
void CDlgSettingTcp::SetFile(CString csfile)
{
	m_csTcpFile = csfile;
	m_wndFile.SetWindowText( m_csTcpFile );

	//
	LoadFile();

	// 
	InitValue();
}
void CDlgSettingTcp::OnNote() 
{
	CDlgSettingNote dlg( theApp.enTCP );
	dlg.DoModal();
}

void CDlgSettingTcp::OnEStatic() 
{
	m_wndFile.ShowWindow( TRUE );			
}
