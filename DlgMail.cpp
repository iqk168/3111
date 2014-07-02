// DlgMail.cpp : implementation file
//

#include "stdafx.h"
#include "deer.h"
#include "DlgMail.h"

#include "CSmtp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgMail dialog


CDlgMail::CDlgMail(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgMail::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgMail)
	m_csSmtpContent1 = _T("");
	m_csSmtpContent2 = _T("");
	m_csSmtpFrom = _T("");
	m_csSmtpLoginName = _T("");
	m_csSmtpLoginPwd = _T("");
	m_iSmtpPort = 0;
	m_csSmtpServer = _T("");
	m_csSmtpSubject = _T("");
	m_csSmtpTo1 = _T("");
	m_csSmtpTo2 = _T("");
	m_csSmtpName = _T("");
	//}}AFX_DATA_INIT

	m_fChange = false;
	m_MailSetting = m.m_MailSetting;
}


void CDlgMail::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgMail)
	DDX_Control(pDX, IDCANCEL,				m_btnCancel);
	DDX_Control(pDX, IDOK,					m_btnOK);
	DDX_Text(pDX, IDC_E_SMTP_CONTENT1,		m_csSmtpContent1);
	DDX_Text(pDX, IDC_E_SMTP_CONTENT2,		m_csSmtpContent2);
	DDX_Text(pDX, IDC_E_SMTP_FROM,			m_csSmtpFrom);
	DDX_Text(pDX, IDC_E_SMTP_LOGIN_NAME,	m_csSmtpLoginName);
	DDX_Text(pDX, IDC_E_SMTP_LOGIN_PWD,		m_csSmtpLoginPwd);
	DDX_Text(pDX, IDC_E_SMTP_PORT,			m_iSmtpPort);
	DDX_Text(pDX, IDC_E_SMTP_SERVER,		m_csSmtpServer);
	DDX_Text(pDX, IDC_E_SMTP_SUBJECT,		m_csSmtpSubject);
	DDX_Text(pDX, IDC_E_SMTP_TO1,			m_csSmtpTo1);
	DDX_Text(pDX, IDC_E_SMTP_TO2,			m_csSmtpTo2);
	DDX_Text(pDX, IDC_E_SMTP_NAME,			m_csSmtpName);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgMail, CDialog)
	//{{AFX_MSG_MAP(CDlgMail)
	ON_WM_DESTROY()
	ON_EN_CHANGE(IDC_E_SMTP_CONTENT1,		OnChangeESmtpContent1)
	ON_EN_CHANGE(IDC_E_SMTP_CONTENT2,		OnChangeESmtpContent2)
	ON_EN_CHANGE(IDC_E_SMTP_FROM,			OnChangeESmtpFrom)
	ON_EN_CHANGE(IDC_E_SMTP_LOGIN_NAME,		OnChangeESmtpLoginName)
	ON_EN_CHANGE(IDC_E_SMTP_LOGIN_PWD,		OnChangeESmtpLoginPwd)
	ON_EN_CHANGE(IDC_E_SMTP_PORT,			OnChangeESmtpPort)
	ON_EN_CHANGE(IDC_E_SMTP_SERVER,			OnChangeESmtpServer)
	ON_EN_CHANGE(IDC_E_SMTP_SUBJECT,		OnChangeESmtpSubject)
	ON_EN_CHANGE(IDC_E_SMTP_TO1,			OnChangeESmtpTo1)
	ON_EN_CHANGE(IDC_E_SMTP_TO2,			OnChangeESmtpTo2)
	ON_BN_CLICKED(IDC_SEND,					OnSend)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgMail message handlers

void CDlgMail::OnDestroy() 
{
	CDialog::OnDestroy();	
}

BOOL CDlgMail::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m.Info.bSubDlgOpen = true;
	f.UpdateButtonState();

	// init button 
//	m_btnOK.SetIcon(IDI_OK);
	m_btnOK.SetIcon(IDI_SAVE);
	m_btnOK.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnOK.SetFlat(FALSE);
	
	m_btnCancel.SetIcon(IDI_CANCEL);
	m_btnCancel.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnCancel.SetFlat(FALSE);

	// Init Value
	InitValue();	

	//
	InitTips();

	//
	f.SetTitleExtend(this, theApp.enTtileMachineFile );

	//
	f.ChangeLanguage(GetSafeHwnd());

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
void CDlgMail::InitTips() 
{
	// Init Tips
	m_ToolTip.Create(this);
	m_ToolTip.SetMaxTipWidth(800);
	m_ToolTip.SetDelayTime( TTDT_AUTOPOP, 10000 );
	m_ToolTip.SetDelayTime( TTDT_INITIAL, 25 );
	m_ToolTip.EnableToolTips(true);

	m_ToolTip.AddTool( GetDlgItem(IDC_STATIC_SMTP_SERVER),			_T("SMTP Server") );
	m_ToolTip.AddTool( GetDlgItem(IDC_STATIC_SMTP_PORT),			_T("SMTP Port") );
	m_ToolTip.AddTool( GetDlgItem(IDC_STATIC_SMTP_LOG_NAME),		_T("SMTP Login Name") );
	m_ToolTip.AddTool( GetDlgItem(IDC_STATIC_SMTP_LOGIN_PWD),		_T("SMTP Login password") );
	m_ToolTip.AddTool( GetDlgItem(IDC_STATIC_SMTP_MAIL_FROM),		_T("SMTP Mail From") );
	m_ToolTip.AddTool( GetDlgItem(IDC_STATIC_SMTP_MAIL_TO1),		_T("SMTP Mail First Recv User") );
	m_ToolTip.AddTool( GetDlgItem(IDC_STATIC_SMTP_MAIL_TO2),		_T("SMTP Mail Second Recv User") );
	m_ToolTip.AddTool( GetDlgItem(IDC_STATIC_SMTP_MAIL_SUBJECT),	_T("SMTP Mail Subject") );
	m_ToolTip.AddTool( GetDlgItem(IDC_STATIC_SMTP_CONTENT1),		_T("SMTP Mail Content 1") );
	m_ToolTip.AddTool( GetDlgItem(IDC_STATIC_SMTP_CONTENT2),		_T("SMTP Mail Content 2") );
	m_ToolTip.AddTool( GetDlgItem(IDC_STATIC_SMTP_SENDER_NAME),		_T("SMTP Mail Sender Name") );
}
void CDlgMail::InitValue() 
{
	m_csSmtpContent1	= m_MailSetting.csContent1;
	m_csSmtpContent2	= m_MailSetting.csContent2;
	m_csSmtpFrom		= m_MailSetting.csMailFrom;
	m_csSmtpLoginName	= m_MailSetting.csSMTPUserName;
	m_csSmtpLoginPwd	= m_MailSetting.csSMTPPassword;
	m_iSmtpPort			= m_MailSetting.iSMTPPort;
	m_csSmtpServer		= m_MailSetting.csSMTPServer;
	m_csSmtpSubject		= m_MailSetting.csMailSubject;
	m_csSmtpTo1			= m_MailSetting.csMailTo1;
	m_csSmtpTo2			= m_MailSetting.csMailTo2;
	m_csSmtpName		= m_MailSetting.csShowName;

	UpdateData( FALSE );
}
void CDlgMail::OnOK() 
{
	if( !UpdateData() )
		return;

	// Get Data from dialog
	m_MailSetting.csContent1		= m_csSmtpContent1;
	m_MailSetting.csContent2		= m_csSmtpContent2;
	m_MailSetting.csMailFrom		= m_csSmtpFrom;
	m_MailSetting.csSMTPUserName	= m_csSmtpLoginName;
	m_MailSetting.csSMTPPassword	= m_csSmtpLoginPwd;
	m_MailSetting.iSMTPPort			= m_iSmtpPort;
	m_MailSetting.csSMTPServer		= m_csSmtpServer;
	m_MailSetting.csMailSubject		= m_csSmtpSubject;
	m_MailSetting.csMailTo1			= m_csSmtpTo1;
	m_MailSetting.csMailTo2			= m_csSmtpTo2;	
	m_MailSetting.csShowName		= m_csSmtpName;

	m.m_MailSetting					= m_MailSetting;
	f.SaveSMTPSetting();

	m.Info.bSubDlgOpen = false;
	f.UpdateButtonState();	

	CDialog::OnOK();
}

void CDlgMail::OnCancel() 
{
	if( m_fChange )
	{
		if(IDYES != AfxMessageBox("Data is modified. Save?\n",
			MB_YESNO|MB_ICONEXCLAMATION))
		{
					m.Info.bSubDlgOpen = false;
					f.UpdateButtonState();
		}
		else
		{
			OnOK();
		}
	}
	else
	{
		m.Info.bSubDlgOpen = false;
		f.UpdateButtonState();
	}
	CDialog::OnCancel();
}

/// On Change.
void CDlgMail::OnChangeESmtpContent1() 
{
	m_fChange = true;	
}

void CDlgMail::OnChangeESmtpContent2() 
{
	m_fChange = true;	
}

void CDlgMail::OnChangeESmtpFrom() 
{
	m_fChange = true;	
}

void CDlgMail::OnChangeESmtpLoginName() 
{
	m_fChange = true;	
}

void CDlgMail::OnChangeESmtpLoginPwd() 
{
	m_fChange = true;
}

void CDlgMail::OnChangeESmtpPort() 
{
	m_fChange = true;	
}

void CDlgMail::OnChangeESmtpServer() 
{
	m_fChange = true;	
}

void CDlgMail::OnChangeESmtpSubject() 
{
	m_fChange = true;	
}

void CDlgMail::OnChangeESmtpTo1() 
{
	m_fChange = true;	
}

void CDlgMail::OnChangeESmtpTo2() 
{
	m_fChange = true;	
}

void CDlgMail::OnSend() 
{
	if( !UpdateData() )
		return;

	m_MailSetting.csContent1 =		m_csSmtpContent1;
	m_MailSetting.csContent2 =		m_csSmtpContent2;
	m_MailSetting.csMailFrom =		m_csSmtpFrom;
	m_MailSetting.csSMTPUserName =	m_csSmtpLoginName;
	m_MailSetting.csSMTPPassword =	m_csSmtpLoginPwd;
	m_MailSetting.iSMTPPort =		m_iSmtpPort;
	m_MailSetting.csSMTPServer =	m_csSmtpServer;
	m_MailSetting.csMailSubject =	m_csSmtpSubject;
	m_MailSetting.csMailTo1 =		m_csSmtpTo1;
	m_MailSetting.csMailTo2 =		m_csSmtpTo2;	
	m_MailSetting.csShowName =		m_csSmtpName;

	bool bError = false;

	try
	{
		CSmtp mail;
		CSmtp mail2;

		// 指定 SMTP Server 
		mail.SetSMTPServer( m_MailSetting.csSMTPServer, m_MailSetting.iSMTPPort );

		// 指定 SMTP 登入資訊 
		mail.SetLogin(		m_MailSetting.csSMTPUserName );
		mail.SetPassword(	m_MailSetting.csSMTPPassword );
 		mail.SetSenderName( m_MailSetting.csShowName );

		// 寄發 Mail 資訊
  		mail.SetSenderMail( m_MailSetting.csMailFrom );
		mail.SetReplyTo(	m_MailSetting.csMailTo1 );

		// Mail 寄件主旨
		mail.SetSubject(	m_MailSetting.csMailSubject );
		mail.AddRecipient(	m_MailSetting.csMailTo1 );
  		mail.SetXPriority(XPRIORITY_NORMAL);

  		mail.SetXMailer("The Bat! (v3.02) Professional");

  		mail.AddMsgLine( m_MailSetting.csContent1 );
		mail.AddMsgLine( m_MailSetting.csContent2 );
		mail.AddMsgLine("...");

		//
		mail.Send();

		////////////////////////////////////////////////////////////////////////////////////////
		//
		// 指定 SMTP Server 
		mail2.SetSMTPServer( m_MailSetting.csSMTPServer, m_MailSetting.iSMTPPort );

		// 指定 SMTP 登入資訊 
		mail2.SetLogin(			m_MailSetting.csSMTPUserName );
		mail2.SetPassword(		m_MailSetting.csSMTPPassword );
 		mail2.SetSenderName(	m_MailSetting.csShowName );

		// 寄發 Mail 資訊
  		mail2.SetSenderMail(	m_MailSetting.csMailFrom );
		mail2.SetReplyTo(		m_MailSetting.csMailTo2 );

		// Mail 寄件主旨
		mail2.SetSubject(		m_MailSetting.csMailSubject );
		mail2.AddRecipient(		m_MailSetting.csMailTo2 );
  		mail2.SetXPriority(XPRIORITY_NORMAL);

  		mail2.SetXMailer("The Bat! (v3.02) Professional");

  		mail2.AddMsgLine( m_MailSetting.csContent1 );
		mail2.AddMsgLine( m_MailSetting.csContent2 );
		mail2.AddMsgLine("...");
		
		//
		mail2.Send();
	}
	catch(ECSmtp e)
	{
		AfxMessageBox( e.GetErrorText().c_str() );
		bError = true;
	}

	if(!bError)
		;	// OK. Mail was send.!
	else
		AfxMessageBox("Mail was not send success.!");
}

BOOL CDlgMail::PreTranslateMessage(MSG* pMsg) 
{
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
