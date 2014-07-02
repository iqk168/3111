// TcpInterfaceDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TcpInterface.h"
#include "TcpInterfaceDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTcpInterfaceDlg dialog

CTcpInterfaceDlg::CTcpInterfaceDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTcpInterfaceDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTcpInterfaceDlg)
	m_iPort = 2000;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	theApp.m_iIndex = 0;
}

void CTcpInterfaceDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTcpInterfaceDlg)
	DDX_Control(pDX, IDC_SEND3, m_btnSnet3);
	DDX_Control(pDX, IDOK, m_btnExit);
	DDX_Control(pDX, IDC_SEND1, m_btnSent1);
	DDX_Control(pDX, IDC_SEND2, m_btnSent2);
	DDX_Control(pDX, IDC_CLEAR, m_btnClear);
	DDX_Control(pDX, IDC_CONNECT_SERVER, m_btnConnectServer);
	DDX_Control(pDX, IDC_IPADDRESS, m_edtIpAddress);
	DDX_Control(pDX, IDC_DISPLAY, m_wndDisplay);
	DDX_Text(pDX, IDC_PORT, m_iPort);
	//}}AFX_DATA_MAP

	DDX_Control(pDX, IDC_SITE1, m_wndSiteCode[0]);
	DDX_Control(pDX, IDC_SITE2, m_wndSiteCode[1]);
	DDX_Control(pDX, IDC_SITE3, m_wndSiteCode[2]);
	DDX_Control(pDX, IDC_SITE4, m_wndSiteCode[3]);
	DDX_Control(pDX, IDC_SITE5, m_wndSiteCode[4]);
	DDX_Control(pDX, IDC_SITE6, m_wndSiteCode[5]);
	DDX_Control(pDX, IDC_SITE7, m_wndSiteCode[6]);
	DDX_Control(pDX, IDC_SITE8, m_wndSiteCode[7]);
	DDX_Control(pDX, IDC_SITE9, m_wndSiteCode[8]);
	DDX_Control(pDX, IDC_SITE10, m_wndSiteCode[9]);
	DDX_Control(pDX, IDC_SITE11, m_wndSiteCode[10]);
	DDX_Control(pDX, IDC_SITE12, m_wndSiteCode[11]);
	DDX_Control(pDX, IDC_SITE13, m_wndSiteCode[12]);
	DDX_Control(pDX, IDC_SITE14, m_wndSiteCode[13]);
	DDX_Control(pDX, IDC_SITE15, m_wndSiteCode[14]);
	DDX_Control(pDX, IDC_SITE16, m_wndSiteCode[15]);
}

BEGIN_MESSAGE_MAP(CTcpInterfaceDlg, CDialog)
	//{{AFX_MSG_MAP(CTcpInterfaceDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_CONNECT_SERVER, OnConnectServer)
	ON_BN_CLICKED(IDC_SEND1, OnSend1)
	ON_BN_CLICKED(IDC_SEND2, OnSend2)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_CLEAR, OnClear)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_AUTO_TEST_CONNECT, OnAutoTestConnect)
	ON_BN_CLICKED(IDC_SEND3, OnSend3)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTcpInterfaceDlg message handlers

BOOL CTcpInterfaceDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	m_btnExit.SetIcon(IDI_QUIT);
	m_btnExit.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnExit.SetFlat(FALSE);
	
	m_btnSent1.SetIcon(IDI_SENT);
	m_btnSent1.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnSent1.SetFlat(FALSE);

	m_btnSent2.SetIcon(IDI_SENT);
	m_btnSent2.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnSent2.SetFlat(FALSE);

	m_btnSnet3.SetIcon(IDI_SENT);
	m_btnSnet3.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnSnet3.SetFlat(FALSE);
	
	m_btnClear.SetIcon(IDI_CLEAR);
	m_btnClear.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnClear.SetFlat(FALSE);
	
	m_btnConnectServer.SetIcon(IDI_OFFLINE);
	m_btnConnectServer.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnConnectServer.SetFlat(FALSE);

	//m_edtIpAddress.SetWindowText("192.168.100.4");
	m_edtIpAddress.SetWindowText("127.0.0.1");
	//m_edtIpAddress.SetWindowText("192.168.1.5");

	for(int i=0;i<_Site_No;++i)	
	{
		m_ThTesting[i] = NULL;
		//m_wndSiteCode[i].SetWindowText("");
		m_wndSiteCode[i].SetText("", 10, "Arial Black", DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		m_wndSiteCode[i].SetNewBkColor(ST_GRAY);
	}
	SetDlgItemText(IDC_SEND_TEXT1, "((load:0;))");
	SetDlgItemText(IDC_SEND_TEXT2, "((end:0))");
	UpdateInfo();

	SetTimer(IDC_UPDATE_TIMER, 500, NULL);
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CTcpInterfaceDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CTcpInterfaceDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CTcpInterfaceDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CTcpInterfaceDlg::OnConnectServer() 
{
	UpdateData();

	if(!m_Interface.IsOpen())
	{
		CString IpAddress;
		m_edtIpAddress.GetWindowText(IpAddress);

		m_Interface.Open(IpAddress.GetBuffer(IpAddress.GetLength()), m_iPort);
	}
	else
	{
		m_Interface.Close();
	}
}

void CTcpInterfaceDlg::OnSend1() 
{
	UpdateData();

	CString csSendText;
	GetDlgItemText(IDC_SEND_TEXT1, csSendText);

//	addBCC(csSendText);

	m_Interface.WriteString(csSendText.GetBuffer(csSendText.GetLength()), csSendText.GetLength());

	CString csTemp;
	csTemp.Format("S%d: %s", theApp.m_iIndex++,  csSendText);
	AddString(csTemp.GetBuffer(csTemp.GetLength()));
}

void CTcpInterfaceDlg::OnSend2() 
{
	UpdateData();

	CString csSendText;
	GetDlgItemText(IDC_SEND_TEXT2, csSendText);

//	addBCC(csSendText);

	m_Interface.WriteString(csSendText.GetBuffer(csSendText.GetLength()), csSendText.GetLength());

	CString csTemp;
	csTemp.Format("S%d: %s", theApp.m_iIndex++,  csSendText);
	AddString(csTemp.GetBuffer(csTemp.GetLength()));
}

void CTcpInterfaceDlg::OnTimer(UINT nIDEvent) 
{
	if(IDC_UPDATE_TIMER)
	{
		UpdateInfo();
	}
	
	CDialog::OnTimer(nIDEvent);
}

void CTcpInterfaceDlg::UpdateInfo()
{
	bool bConnect = m_Interface.IsOpen();
	
	if(bConnect)
	{
		m_btnConnectServer.SetWindowText("Disconnect");
		m_btnConnectServer.SetIcon(IDI_ONLINE);
	}
	else
	{
		m_btnConnectServer.SetWindowText("Connect");
		m_btnConnectServer.SetIcon(IDI_OFFLINE);
	}
//	GetDlgItem(IDC_CONNECT_SERVER)->EnableWindow(!bConnect);
	GetDlgItem(IDC_SEND1)->EnableWindow(bConnect);
	GetDlgItem(IDC_SEND2)->EnableWindow(bConnect);
	GetDlgItem(IDC_SEND3)->EnableWindow(bConnect);
	GetDlgItem(IDC_IPADDRESS)->EnableWindow(!bConnect);
	GetDlgItem(IDC_PORT)->EnableWindow(!bConnect);
}

static CMutex MutexAddString;
void CTcpInterfaceDlg::AddString(char *csText)
{
	MutexAddString.Lock();
	m_wndDisplay.InsertString(0, csText);
	MutexAddString.Unlock();
}

void CTcpInterfaceDlg::OnClear() 
{
	m_wndDisplay.ResetContent();
}

void CTcpInterfaceDlg::OnDestroy() 
{
	CDialog::OnDestroy();

	m_Interface.Close();
	KillTimer(IDC_UPDATE_TIMER);

	// kill all thread of testing.
// 	HANDLE hThread[_Site_No];
// 	for(int i=0;i<_Site_No;++i)
// 		if(m_ThTesting[i])	
// 		{
// 			m_ThTesting[i]->PostThreadMessage(WM_QUIT, 0, 0);
// 			hThread[i] = m_ThTesting[i]->m_hThread;
// 		}
// 		else
// 			hThread[i] = NULL;
// 	
// 	WaitForMultipleObjects(_Site_No, hThread, true, 2000);
}

void CTcpInterfaceDlg::OnAutoTestConnect() 
{
	for(int i=0;i<3;++i)		
	{
		if(m_ThTesting[i] != NULL)
		{
			delete m_ThTesting[i];
			Sleep(100);
		}
		else
		{
			m_ThTesting[i] = new CThTesting(i);
			m_ThTesting[i]->CreateThread();
		}
	}
}

void CTcpInterfaceDlg::DisplayErrorCode(int iSite, CString Code, COLORREF Color)
{
	CString cs = GetErrorCode(Code.GetBuffer(Code.GetLength()));
	m_wndSiteCode[iSite-1].SetWindowText(cs);
	m_wndSiteCode[iSite-1].SetNewBkColor(Color);
}

CString CTcpInterfaceDlg::GetErrorCode(char *Buffer)
{
	char *token = Buffer;
	token = strtok(token, "((" );
	token = strtok(token, "))" );

	char *pSiteNo = strstr(token, "Error Code = ");
	
	if(pSiteNo)
	{
		token = strtok(token, "Error Code = ");
		return token;
	}
	else
		return "";
}

void CTcpInterfaceDlg::OnOK() 
{
	// TODO: Add extra validation here
	
	CDialog::OnOK();
}

CString CTcpInterfaceDlg::getIpAddress()
{
	CString IpAddress;
	m_edtIpAddress.GetWindowText(IpAddress);

	return IpAddress;
}

void CTcpInterfaceDlg::addBCC(CString &Message)
{
	unsigned char checkSum = 0;

	char buff[20] = {0};

	// 從 1 開始, 因為 0x2 不被列入 Check Sum 的計算.
	for(int i=0; i<Message.GetLength(); ++i)
		checkSum = (unsigned char) checkSum ^ (unsigned char) * (Message.GetBuffer(0)+i);

//	Message += (char)(unsigned char)(((checkSum & 0xf0)>>4)+0x30) + (char)(unsigned char)((checkSum & 0xf)+0x30);

	char BccHigh = changeHex((checkSum & 0xf0)>>4);
	char BccLow  = changeHex(checkSum & 0xf);

	CString str;
//	str.Format("%s%c%c\r", Message, BccHigh, BccLow);
	str.Format("%s\r", Message);

	Message = str;


 	for(i=0;i<20;++i)
 		buff[i] = *(Message.GetBuffer(0)+i);
}

char CTcpInterfaceDlg::changeHex(char c)
{
	if (c >= 0xA && c <= 0xF)
		return c - 0xA + 'A';

	else
		return c + '0';
	
	return 'A';
}

void CTcpInterfaceDlg::OnSend3() 
{
	int i;
	for(i=0;i<100;i++)
	{
		UpdateData();
		
		CString csSendText;
		GetDlgItemText(IDC_SEND_TEXT1, csSendText);
		
		//	addBCC(csSendText);
		CString cs;
		cs.Format("<<%d>>",i);
		
		csSendText = csSendText + cs;

		m_Interface.WriteString(csSendText.GetBuffer(csSendText.GetLength()), csSendText.GetLength() );
		
		CString csTemp;
		csTemp.Format("S%d: %s", theApp.m_iIndex++,  csSendText);
		AddString(csTemp.GetBuffer(csTemp.GetLength()));

		Sleep(25);
	}
}
