// DlgHandlerComPort.cpp : implementation file
//

#include "stdafx.h"
#include "deer.h"
#include "DlgHandlerComPort.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgHandlerComPort dialog


CDlgHandlerComPort::CDlgHandlerComPort(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgHandlerComPort::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgHandlerComPort)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	
	m_fChange = false;

	m_HandlerComPort = m.m_HandlerComPort;
}


void CDlgHandlerComPort::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgHandlerComPort)
	DDX_Control(pDX, IDC_E_PORT_REMOTE,				m_wndRemotePort);
	DDX_Control(pDX, IDC_E_PORT_TORQUE_STATUS,		m_wndTorqueStatus);
	DDX_Control(pDX, IDC_E_PORT_WEST_HEAT_ID,		m_wndWestHeaterID);
	DDX_Control(pDX, IDC_E_PORT_REMOTE_IO3,			m_wndRemoteIOPort3);
	DDX_Control(pDX, IDC_E_PORT_WEST,				m_wndWestPort);
	DDX_Control(pDX, IDC_E_PORT_ATC_MODULE,			m_wndATCModulePort);
	DDX_Control(pDX, IDC_E_PORT_TESTER,				m_wndTesterPort);
	DDX_Control(pDX, IDC_E_PORT_REMOTE_IO2,			m_wndRemoteIOPort2);
	DDX_Control(pDX, IDC_E_PORT_REMOTE_IO,			m_wndRemoteIOPort);
	DDX_Control(pDX, IDC_E_PORT_PID2,				m_wndPIDPort2);
	DDX_Control(pDX, IDC_E_PORT_PID,				m_wndPIDPort);
	DDX_Control(pDX, IDOK,							m_btnOK);
	DDX_Control(pDX, IDCANCEL,						m_btnCancel);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgHandlerComPort, CDialog)
	//{{AFX_MSG_MAP(CDlgHandlerComPort)
	ON_EN_CHANGE(IDC_E_PORT_PID,					OnChangeEPortPid)
	ON_EN_CHANGE(IDC_E_PORT_REMOTE_IO,				OnChangeEPortRemoteIo)
	ON_EN_CHANGE(IDC_E_PORT_TESTER,					OnChangeEPortTester)
	ON_EN_CHANGE(IDC_E_PORT_ATC_MODULE,				OnChangeEPortAtcModule)
	ON_EN_CHANGE(IDC_E_PORT_PID2,					OnChangeEPortPid2)
	ON_EN_CHANGE(IDC_E_PORT_REMOTE_IO2,				OnChangeEPortRemoteIo2)
	ON_EN_CHANGE(IDC_E_PORT_TORQUE_STATUS,			OnChangeEPortTorqueStatus)
	ON_EN_CHANGE(IDC_E_PORT_REMOTE,					OnChangeEPortRemote)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgHandlerComPort message handlers

void CDlgHandlerComPort::OnOK() 
{
	SaveData();

	//
	m.Info.bSubDlgOpen = false;
	f.UpdateButtonState();
	
	CDialog::OnOK();
}

void CDlgHandlerComPort::OnCancel() 
{
	if(m_fChange)
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

BOOL CDlgHandlerComPort::PreTranslateMessage(MSG* pMsg) 
{
	// Tips
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

BOOL CDlgHandlerComPort::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m.Info.bSubDlgOpen = true;
	f.UpdateButtonState();
	
	// init button 
	m_btnOK.SetIcon(IDI_SAVE);;
	m_btnOK.SetAlign(CButtonST::ST_ALIGN_VERT);;
	m_btnOK.SetFlat(FALSE);
	
	m_btnCancel.SetIcon(IDI_CANCEL);
	m_btnCancel.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnCancel.SetFlat(FALSE);

	//
	InitTips();

	//
	InitValue();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
void CDlgHandlerComPort::InitTips()
{
	// Tips // Init Tips
	m_ToolTip.Create(this);
	m_ToolTip.SetMaxTipWidth(800);
	m_ToolTip.SetDelayTime( TTDT_AUTOPOP, 10000 );
	m_ToolTip.SetDelayTime( TTDT_INITIAL, 25 );
	m_ToolTip.EnableToolTips(true);

	m_ToolTip.AddTool( GetDlgItem(IDC_E1),				_T("ND-6024 - Port:1, ID:1") );
	m_ToolTip.AddTool( GetDlgItem(IDC_E2),				_T("ND-6054/ND-6056 - Port:1, In ID:2, Out ID:3") );
	m_ToolTip.AddTool( GetDlgItem(IDC_E3),				_T("Tester - Port:3") );
	m_ToolTip.AddTool( GetDlgItem(IDC_E4),				_T("54130") );
	m_ToolTip.AddTool( GetDlgItem(IDC_E5),				_T("West - Port:2") );
	m_ToolTip.AddTool( GetDlgItem(IDC_E6),				_T("Torque - Port:4") );
	m_ToolTip.AddTool( GetDlgItem(IDC_E7),				_T("Remote - Port:5") );
}
void CDlgHandlerComPort::InitValue()
{
	// Remote Port
	CString csRemotePort = _T("");
	csRemotePort.Format("%d", m.m_HandlerComPort.iPortRemoteCom );
	m_wndRemotePort.SetWindowText( csRemotePort );

	// ATC Module Port 
	CString csATCModulePort = _T("");
	csATCModulePort.Format("%d", m.m_HandlerComPort.iPortATCModule );
	m_wndATCModulePort.SetWindowText( csATCModulePort );

	// Test Port
	CString csTesterPort = _T("");
	csTesterPort.Format("%d", m.m_HandlerComPort.iPortTester );
	m_wndTesterPort.SetWindowText( csTesterPort );

	// Remote IO Port Input / ID
	CString csRemoteIOPort2 = _T("");
	csRemoteIOPort2.Format("%d", m.m_HandlerComPort.iIDIOModuleIDIn );	// RS485 ID Input
	m_wndRemoteIOPort2.SetWindowText( csRemoteIOPort2 );

	// Remote IO Port Output / ID
	CString csRemoteIOPort3 = _T("");
	csRemoteIOPort3.Format("%d", m.m_HandlerComPort.iIDIOModuleIDOut );	// RS485 ID Output
	m_wndRemoteIOPort3.SetWindowText( csRemoteIOPort3 );

	// Remote IO Port 
	CString csRemoteIOPort = _T("");
	csRemoteIOPort.Format("%d", m.m_HandlerComPort.iPortIOModule );
	m_wndRemoteIOPort.SetWindowText( csRemoteIOPort );

	// PID ID
	CString csPIDPort2 = _T("");
	csPIDPort2.Format("%d", m.m_HandlerComPort.iIDPIDValue );
	m_wndPIDPort2.SetWindowText( csPIDPort2 );
	
	// PID Port
	CString csPIDPort = _T("");
	csPIDPort.Format("%d", m.m_HandlerComPort.iPortPIDValue );
	m_wndPIDPort.SetWindowText( csPIDPort );

	// West 
	CString csWestPort = _T("");
	csWestPort.Format("%d", m.m_HandlerComPort.iPortWest );
	m_wndWestPort.SetWindowText( csWestPort );

	// West Heater ID
	CString csWestHeaterID = _T("");
	csWestHeaterID.Format("%d", m.m_HandlerComPort.iPortWestHeaterID );
	m_wndWestHeaterID.SetWindowText( csWestHeaterID );

	// Torque Status
	CString csTorqueStatus = _T("");
	csTorqueStatus.Format("%d", m.m_HandlerComPort.iPortTorqueStatus );
	m_wndTorqueStatus.SetWindowText( csTorqueStatus );

	//
	m_fChange = false;
}
void CDlgHandlerComPort::SaveData()
{
	CString csATCModulePort		= _T("");
	CString csTesterPort		= _T("");
	CString csRemoteIOPort3		= _T("");
	CString csRemoteIOPort2		= _T("");
	CString csRemoteIOPort		= _T("");
	CString csPIDPort2			= _T("");
	CString csPIDPort			= _T("");
	CString csWestPort			= _T("");
	CString csWestHeaterID		= _T("");
	CString csTorqueStatus		= _T("");
	CString csRemotePort		= _T("");

	// Remote Port
	m_wndRemotePort.GetWindowText( csRemotePort );
	csRemotePort.TrimLeft(); csRemotePort.TrimRight();
	m.m_HandlerComPort.iPortRemoteCom = atoi( csRemotePort );

	// ATC Module Port
	m_wndATCModulePort.GetWindowText( csATCModulePort );
	csATCModulePort.TrimLeft(); csATCModulePort.TrimRight();
	m.m_HandlerComPort.iPortATCModule = atoi( csATCModulePort );

	// Tester Port
	m_wndTesterPort.GetWindowText( csTesterPort );
	csTesterPort.TrimLeft(); csTesterPort.TrimRight();
	m.m_HandlerComPort.iPortTester = atoi( csTesterPort );
	
	// Remote IO Input ID(RS485)
	m_wndRemoteIOPort2.GetWindowText( csRemoteIOPort2 );
	csRemoteIOPort2.TrimLeft(); csRemoteIOPort2.TrimRight();
	m.m_HandlerComPort.iIDIOModuleIDIn = atoi( csRemoteIOPort2 );

	// Remote IO Output ID(RS485)
	m_wndRemoteIOPort3.GetWindowText( csRemoteIOPort3 );
	csRemoteIOPort3.TrimLeft(); csRemoteIOPort3.TrimRight();
	m.m_HandlerComPort.iIDIOModuleIDOut = atoi( csRemoteIOPort3 );

	// Remote IO Port(RS485)
	m_wndRemoteIOPort.GetWindowText( csRemoteIOPort );
	csRemoteIOPort.TrimLeft(); csRemoteIOPort.TrimRight();
	m.m_HandlerComPort.iPortIOModule = atoi( csRemoteIOPort );
	
	// PID ID
	m_wndPIDPort2.GetWindowText( csPIDPort2 );
	csPIDPort2.TrimLeft(); csPIDPort2.TrimRight();
	m.m_HandlerComPort.iIDPIDValue = atoi( csPIDPort2 );

	// PID Port
	m_wndPIDPort.GetWindowText( csPIDPort );
	csPIDPort.TrimLeft(); csPIDPort.TrimRight();
	m.m_HandlerComPort.iPortPIDValue = atoi( csPIDPort );

	// West Port
	m_wndWestPort.GetWindowText( csWestPort );
	csWestPort.TrimLeft(); csWestPort.TrimRight();
	m.m_HandlerComPort.iPortWest = atoi( csWestPort );

	// West Heater ID
	m_wndWestHeaterID.GetWindowText( csWestHeaterID );
	csWestHeaterID.TrimLeft(); csWestHeaterID.TrimRight();
	m.m_HandlerComPort.iPortWestHeaterID = atoi( csWestHeaterID );

	// Torque Status
	m_wndTorqueStatus.GetWindowText( csTorqueStatus );
	csTorqueStatus.TrimLeft(); csTorqueStatus.TrimRight();
	m.m_HandlerComPort.iPortTorqueStatus = atoi( csTorqueStatus );

	/////////////////////////////////////
	f.SaveHandlerComPort();
}

void CDlgHandlerComPort::OnChangeEPortPid() 
{
	m_fChange = true;
}

void CDlgHandlerComPort::OnChangeEPortRemoteIo() 
{
	m_fChange = true;
}

void CDlgHandlerComPort::OnChangeEPortTester() 
{
	m_fChange = true;
}

void CDlgHandlerComPort::OnChangeEPortAtcModule() 
{
	m_fChange = true;
}

void CDlgHandlerComPort::OnChangeEPortPid2() 
{
	m_fChange = true;
}

void CDlgHandlerComPort::OnChangeEPortRemoteIo2() 
{
	m_fChange = true;
}

void CDlgHandlerComPort::OnChangeEPortTorqueStatus() 
{
	m_fChange = true;
}

void CDlgHandlerComPort::OnChangeEPortRemote() 
{
	m_fChange = true;
}
