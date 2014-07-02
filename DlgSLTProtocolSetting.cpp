// DlgSLTProtocolSetting.cpp : implementation file
//

#include "stdafx.h"
#include "deer.h"
#include "DlgSLTProtocolSetting.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgSLTProtocolSetting dialog


CDlgSLTProtocolSetting::CDlgSLTProtocolSetting(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgSLTProtocolSetting::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgSLTProtocolSetting)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgSLTProtocolSetting::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgSLTProtocolSetting)
	DDX_Control(pDX, IDC_STATIC_SERIAL_GRP,			m_wndSerialGrp);
	DDX_Control(pDX, IDC_E_ETHERNET_PORT,			m_wndEthernetPort);
	DDX_Control(pDX, IDC_E_ETHERNET_IP_ADDRESS,		m_wndEthernetIPAddress);
	DDX_Control(pDX, IDC_E_SERIAL_BAUDRATE,			m_wndSerialPort);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgSLTProtocolSetting, CDialog)
	//{{AFX_MSG_MAP(CDlgSLTProtocolSetting)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgSLTProtocolSetting message handlers

BOOL CDlgSLTProtocolSetting::PreTranslateMessage(MSG* pMsg) 
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

BOOL CDlgSLTProtocolSetting::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	InitValue();
	
	InitUI();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
void CDlgSLTProtocolSetting::InitValue()
{
	// Serial Port
	CString csSerialPortBaudRate = _T("");
	int iBaudRate = 0;
	m.m_TestInterface.GetBaudRate( iBaudRate );
	csSerialPortBaudRate.Format("  %d", iBaudRate );
	m_wndSerialPort.SetWindowText( csSerialPortBaudRate );

	// Ethernet (TCP/IP)
	CString csEthernetIPAddress = _T("");
	CString csEthernetPort = _T("");
	m.m_TestInterface.GetEthernet( csEthernetIPAddress, csEthernetPort);
	m_wndEthernetIPAddress.SetWindowText( " " + csEthernetIPAddress );
	m_wndEthernetPort.SetWindowText( " " + csEthernetPort );
}
void CDlgSLTProtocolSetting::InitUI()
{
	if( m.m_HandlerComPort.iPortRemoteCom == 0 )
		m_wndSerialGrp.ShowWindow( FALSE );
	else
		m_wndSerialGrp.ShowWindow( TRUE );
}
