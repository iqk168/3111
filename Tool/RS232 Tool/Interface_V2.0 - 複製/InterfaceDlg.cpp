// InterfaceDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Interface.h"
#include "InterfaceDlg.h"

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
// CInterfaceDlg dialog

CInterfaceDlg::CInterfaceDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CInterfaceDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CInterfaceDlg)
	m_iBaudRate = 1;
	m_iCodeOrNum = 0;
	m_iPortNo = 1;
	m_iDataBit = 1;
	m_iParityCheck = 0;
	m_csSendText = _T("<<READY>>");
	m_csSendText2 = _T("<<GO>>");
	m_iStopBit = 0;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CInterfaceDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CODE2, m_btnCode2);
	//{{AFX_DATA_MAP(CInterfaceDlg)
	DDX_Control(pDX, IDC_VALUE, m_wndValue);
	DDX_Control(pDX, IDC_SEND3, m_btnSend3);
	DDX_Control(pDX, IDC_CODE_COUNT, m_wndCount);
	DDX_Control(pDX, IDC_SEND_TEXT2, m_edtSendText2);
	DDX_Control(pDX, IDC_SEND2, m_btnSend2);
	DDX_Control(pDX, IDC_CODE, m_btnCode);
	DDX_Control(pDX, IDC_CLEAR, m_btnClear);
	DDX_Control(pDX, IDC_SHOW_CODE, m_btnShowCode);
	DDX_Control(pDX, IDC_SHOW_NUMERIC, m_btnShowNumeric);
	DDX_Control(pDX, IDC_SHOW_TEXT, m_listShowText);
	DDX_Control(pDX, IDC_STOP_BIT, m_cbxStopBit);
	DDX_Control(pDX, IDC_SEND_TEXT, m_edtSendText);
	DDX_Control(pDX, IDC_SEND, m_btnSend);
	DDX_Control(pDX, IDC_PARITY_CHECK, m_cbxParityCheck);
	DDX_Control(pDX, IDC_DATA_BIT, m_cbxDataBit);
	DDX_Control(pDX, IDC_COM_PORT, m_cbxComPort);
	DDX_Control(pDX, IDC_BAUD_RATE, m_cbxBaudRate);
	DDX_Control(pDX, IDC_CONNECT, m_btnConnect);
	DDX_CBIndex(pDX, IDC_BAUD_RATE, m_iBaudRate);
	DDX_Radio(pDX, IDC_CODE, m_iCodeOrNum);
	DDX_CBIndex(pDX, IDC_COM_PORT, m_iPortNo);
	DDX_CBIndex(pDX, IDC_DATA_BIT, m_iDataBit);
	DDX_CBIndex(pDX, IDC_PARITY_CHECK, m_iParityCheck);
	DDX_Text(pDX, IDC_SEND_TEXT, m_csSendText);
	DDX_CBIndex(pDX, IDC_STOP_BIT, m_iStopBit);
	DDX_Text(pDX, IDC_SEND_TEXT2, m_csSendText2);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CInterfaceDlg, CDialog)
	//{{AFX_MSG_MAP(CInterfaceDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_CONNECT, OnConnect)
	ON_BN_CLICKED(IDC_SHOW_CODE, OnShowCode)
	ON_BN_CLICKED(IDC_SHOW_NUMERIC, OnShowNumeric)
	ON_BN_CLICKED(IDC_CODE, OnCode)
	ON_BN_CLICKED(IDC_CODE2, OnCode2)
	ON_BN_CLICKED(IDC_SEND, OnSend)
	ON_BN_CLICKED(IDC_CLEAR, OnClear)
	ON_BN_CLICKED(IDC_SEND2, OnSend2)
	ON_BN_CLICKED(IDC_SEND3, OnSend3)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_SET, OnSet)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CInterfaceDlg message handlers

BOOL CInterfaceDlg::OnInitDialog()
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
	
	m_btnConnect.SetIcon(IDI_DISCONNECT);
	m_btnConnect.SetAlign(CButtonST::ST_ALIGN_VERT);

	m_btnSend.SetIcon(IDI_SEND);
	m_btnSend2.SetIcon(IDI_SEND);
	m_btnSend3.SetIcon(IDI_SEND);
	m_btnClear.SetIcon(IDI_CLEAR);

	m_btnShowCode.SetCheck(1);

	EnableWindow();

	SetTimer(ID_TIME_STATUS, 100, NULL); 
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CInterfaceDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CInterfaceDlg::OnPaint() 
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
HCURSOR CInterfaceDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CInterfaceDlg::OnCancel() 
{
	CDialog::OnCancel();
}

void CInterfaceDlg::OnConnect() 
{
	CString cs;
	m_btnConnect.GetWindowText(cs);
	if(cs == "Connect")
	{
		UpdateData();
		if(m.Com.Open(m_iPortNo, m_iBaudRate, m_iDataBit, m_iStopBit, m_iParityCheck))
		{
			m_btnConnect.SetWindowText("Disconnect");
			m_btnConnect.SetIcon(IDI_CONNECT);
			AfxBeginThread(ReadThread, 0);
		}
		else
			AfxMessageBox("Open port error!");
	}
	else
	{
		m_btnConnect.SetWindowText("Connect");
		m_btnConnect.SetIcon(IDI_DISCONNECT);
		m.Com.Close();
	}

	EnableWindow();
}

void CInterfaceDlg::OnShowCode() 
{
	m_btnShowCode.Invalidate();	
}

void CInterfaceDlg::OnShowNumeric() 
{
	m_btnShowNumeric.Invalidate();	
}

void CInterfaceDlg::OnCode() 
{
	m_btnCode.Invalidate();
}

void CInterfaceDlg::OnCode2() 
{
	m_btnCode2.Invalidate();
}

void CInterfaceDlg::EnableWindow()
{
	CString cs;
	BOOL ok;
	m_btnConnect.GetWindowText(cs);
	if(cs == "Disconnect")
		ok = TRUE;
	else
		ok = FALSE;

	m_cbxBaudRate.EnableWindow(!ok);
	m_cbxDataBit.EnableWindow(!ok);
	m_cbxComPort.EnableWindow(!ok);
	m_cbxStopBit.EnableWindow(!ok);
	m_cbxParityCheck.EnableWindow(!ok);

	m_btnSend.EnableWindow(ok);
	m_btnSend2.EnableWindow(ok);
	m_btnClear.EnableWindow(ok);
	m_btnShowCode.EnableWindow(ok);
	m_btnShowCode.Invalidate();
	m_btnShowNumeric.EnableWindow(ok);
	m_btnShowNumeric.Invalidate();
	m_btnCode.EnableWindow(ok);
	m_btnCode.Invalidate();
	m_btnCode2.EnableWindow(ok);
	m_btnCode2.Invalidate();
	m_edtSendText.EnableWindow(ok);
	m_edtSendText2.EnableWindow(ok);
	m_listShowText.EnableWindow(ok);
}

void CInterfaceDlg::Add(char *buff, int size)
{
	CString cs, csLine;
			csLine.Format("%d R :", m_listShowText.GetCount());
	for(int i=0; i<size; i++)
	{
		if(m_btnShowNumeric.GetCheck() && m_btnShowCode.GetCheck())
			cs.Format("%c(0x%x)", buff[i], buff[i]);
		else if(m_btnShowNumeric.GetCheck() && !m_btnShowCode.GetCheck())
			cs.Format("(0x%x) ", buff[i]);
		else
			cs.Format("%c", buff[i]);

		csLine += cs;
		if(csLine.GetLength() > 50)
		{
			m_listShowText.InsertString(0, csLine);
			csLine.Format("%d R :", m_listShowText.GetCount());
		}
	}

	if(csLine.GetLength() > 0)
		m_listShowText.InsertString(0, csLine);
}

void CInterfaceDlg::OnSend() 
{
	CString cs;
	CString cs2;
	m_edtSendText.GetWindowText(cs);
	
	if(m_btnCode.GetCheck())
	{
		m.Com.WriteString(cs.GetBuffer(0), cs.GetLength());
		cs2.Format("%d S: %s", m_listShowText.GetCount(), cs);
		m_listShowText.InsertString(0, cs2);
	}
	else
	{
		char c[2];
		c[0] = atoi(cs.GetBuffer(0));
		m.Com.WriteString(c, sizeof(char));
		cs2.Format("%d S: [%d]", m_listShowText.GetCount(), c[0]);
		m_listShowText.InsertString(0, cs2);
	}
}

void CInterfaceDlg::OnClear() 
{
	m_listShowText.ResetContent();	
}

void CInterfaceDlg::OnSend2() 
{
	CString cs;
	CString cs2;
	m_edtSendText2.GetWindowText(cs);
	
	if(m_btnCode.GetCheck())
	{
		m.Com.WriteString(cs.GetBuffer(0), cs.GetLength());
		cs2.Format("%d S: %s", m_listShowText.GetCount(), cs);
		m_listShowText.InsertString(0, cs2);
	}
	else
	{
		char c[2];
		c[0] = atoi(cs.GetBuffer(0));
		m.Com.WriteString(c, sizeof(char));
		cs2.Format("%d S: [%d]", m_listShowText.GetCount(), c[0]);
		m_listShowText.InsertString(0, cs2);
	}
	
}

void CInterfaceDlg::OnSend3() 
{	
	for( int s = 0; s< 1000000; s++)
	{
		CString cs;
		CString cs2;
		m_edtSendText.GetWindowText(cs);
	
		if(m_btnCode.GetCheck())
		{
			m.Com.WriteString(cs.GetBuffer(0), cs.GetLength());
			cs2.Format("%d S: %s ", m_listShowText.GetCount(), cs);
			m_listShowText.InsertString(0, cs2);
		}
		else
		{
			char c[2];
			c[0] = atoi(cs.GetBuffer(0));
			m.Com.WriteString(c, sizeof(char));
			cs2.Format("%d S: [%d]", m_listShowText.GetCount(), c[0]);
			m_listShowText.InsertString(0, cs2);
		}

		Sleep(2);
	}
}

void CInterfaceDlg::OnTimer(UINT nIDEvent) 
{
	switch(nIDEvent)
	{
	case ID_TIME_STATUS:
		{
			CString cs;
			cs.Format("%d", m.Count);
			m_wndCount.SetWindowText( cs );
		}
		break;
	}	
	CDialog::OnTimer(nIDEvent);
}

void CInterfaceDlg::OnSet() 
{
	CString csValue = _T("");
	m_wndValue.GetWindowText( csValue );
	m.iValue = atoi( csValue );
}
