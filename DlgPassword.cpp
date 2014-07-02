// DlgPassword.cpp : implementation file
//

#include "stdafx.h"
#include "deer.h"
#include "DlgPassword.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgPassword dialog


CDlgPassword::CDlgPassword(bool bPassword, CWnd* pParent /*=NULL*/)
	: CDialog(CDlgPassword::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgPassword)
	m_csNewPassword2 = _T("");
	//}}AFX_DATA_INIT

	m_bPassword = bPassword;
	if(bPassword)
		m_iUser = enLevelEngineer;
	else
		m_iUser = m.Info.user;
}


void CDlgPassword::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgPassword)
	DDX_Control(pDX, IDOK,					m_btnOK);
	DDX_Control(pDX, IDCANCEL,				m_btnCancel);
	DDX_Control(pDX, IDC_USER3,				m_btnUser3);
	DDX_Control(pDX, IDC_USER2,				m_btnUser2);
	DDX_Control(pDX, IDC_USER,				m_btnUser);
	DDX_Control(pDX, IDC_PASSWORD,			m_edtPassword);
	DDX_Control(pDX, IDC_CHANGE_PASSWORD,	m_btnChangePassword);
	DDX_Control(pDX, IDC_NEW2,				m_wndNew2);
	DDX_Control(pDX, IDC_NEW_PASSWORD2,		m_edtNewPassword2);
	DDX_Control(pDX, IDC_NEW,				m_wndNew);
	DDX_Control(pDX, IDC_OLD,				m_wndOld);	
	DDX_Control(pDX, IDC_NEW_PASSWORD,		m_edtNewPassword);
	DDX_Text(pDX, IDC_PASSWORD,				m_csPassword);
	DDX_Text(pDX, IDC_NEW_PASSWORD,			m_csNewPassword);
	DDX_Text(pDX, IDC_NEW_PASSWORD2,		m_csNewPassword2);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgPassword, CDialog)
	//{{AFX_MSG_MAP(CDlgPassword)
	ON_BN_CLICKED(IDC_USER,					OnUser)
	ON_BN_CLICKED(IDC_USER2,				OnSetup)
	ON_BN_CLICKED(IDC_USER3,				OnEngineer)
	ON_WM_CLOSE()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_CHANGE_PASSWORD,		OnChangePassword)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgPassword message handlers

void CDlgPassword::OnUser() 
{
	m_edtPassword.SetFocus();
	m_iUser = enLevelUser;
	m_btnUser.SetCheck(TRUE);
	m_btnUser2.SetCheck(FALSE);
	m_btnUser3.SetCheck(FALSE);
	m_btnChangePassword.EnableWindow(FALSE);
}

void CDlgPassword::OnSetup() 
{
	m_edtPassword.SetFocus();
	m_iUser = enLevelSetup;
	m_btnUser.SetCheck(FALSE);
	m_btnUser2.SetCheck(TRUE);
	m_btnUser3.SetCheck(FALSE);
	m_btnChangePassword.EnableWindow(FALSE);	
//	m_btnChangePassword.EnableWindow(TRUE);
}

void CDlgPassword::OnEngineer() 
{
	m_edtPassword.SetFocus();
	m_iUser = enLevelEngineer;
	m_btnUser.SetCheck(FALSE);
	m_btnUser2.SetCheck(FALSE);
	m_btnUser3.SetCheck(TRUE);
	m_btnChangePassword.EnableWindow(TRUE);
}

void CDlgPassword::OnOK() 
{
	UpdateData();

	// Note : if m_bPassword == true
	// It mean user try to change password
	// else just for login different user.

	if(m_bPassword)
	{
		switch(m_iUser)
		{
		case enLevelSetup:			
			{
				f.LoadPassword();
				if(m_csPassword == m.UI.PasswordSetup 
					&& m_csNewPassword == m_csNewPassword2)
				{
					if (m_csNewPassword == m.UI.PasswordSuperUser)
					{
						AfxMessageBox( ("Password not accepted!") );
						break;
					}
					
					m.UI.PasswordSetup = m_csNewPassword;
					f.SavePassword();
					f.LoadPassword(); // Reload New Password
				}
				else
					AfxMessageBox( ("Password error") );
			}
			break;
		case enLevelEngineer:
			{
				f.LoadPassword();
				if (m_csPassword == m.UI.PasswordEngineer
					&& m_csNewPassword == m_csNewPassword2)
				{
					if (m_csNewPassword == m.UI.PasswordSuperUser)
					{
						AfxMessageBox( ("Password not accepted!") );
						break;
					}
					
					m.UI.PasswordEngineer = m_csNewPassword;
					f.SavePassword();
					f.LoadPassword(); // Reload New Password
				}
				else
					AfxMessageBox( ("Password error") );
			}
			break;		
		case enLevelUser:			
		default:
			break;
		}
	}
	else
	// Note : Check Password.
	{	
		if(m_csPassword == "jim")
		{
			m.Info.user = enLevelSuperUser;
		}
		else if(m_csPassword == "k")
		{
			m.Info.user = enLevelSuperUser;
		}
		else
		{
			switch(m_iUser)
			{
			case enLevelSetup:
				{
					if( m_csPassword == m.UI.PasswordSetup )
					{
						m.Info.user = m_iUser;
					}
					else
					{
						AfxMessageBox( ("Password error") );
						m_csPassword = "";
						UpdateData(FALSE);
						return;
					}
				}
				break;
			case enLevelEngineer:
				{
					if( m_csPassword == m.UI.PasswordEngineer )
					{
						m.Info.user = m_iUser;
					}
					else
					{
						AfxMessageBox( ("Password error") );
						m_csPassword = "";
						UpdateData(FALSE);
						return;
					}
				}
				break;
			case enLevelUser:
				m.Info.user = enLevelUser;
			default:
				m.Info.user = m_iUser;
				break;
			}
		}
	}

	m.Info.bSubDlgOpen = false;
	f.UpdateButtonState();

	CDialog::OnOK();
}

void CDlgPassword::OnCancel() 
{
/*
	enLevelInitial		= 0,
	enLevelRun			= 1,
	enLevelUser			= 2,
	enLevelSetup		= 3,
	enLevelEngineer		= 4,
	enLevelSuperUser	= 5,
*/

//	m.Info.user = m_iUser; // Recover default

	m.Info.bSubDlgOpen = false;
	f.UpdateButtonState();
	
	CDialog::OnCancel();
}

void CDlgPassword::OnClose() 
{
	m.Info.bSubDlgOpen = false;
	f.UpdateButtonState();
	
	CDialog::OnClose();
}

void CDlgPassword::OnDestroy() 
{
	m.Info.bSubDlgOpen = false;
	f.UpdateButtonState();

	CDialog::OnDestroy();	
}

BOOL CDlgPassword::OnInitDialog() 
{
	CDialog::OnInitDialog();
			
	// init button
	m_btnOK.SetIcon(IDI_OK);
	m_btnOK.SetAlign(CButtonST::ST_ALIGN_VERT);
//	m_btnOK.SetFlat(FALSE);

	m_btnCancel.SetIcon(IDI_CANCEL);;
	m_btnCancel.SetAlign(CButtonST::ST_ALIGN_VERT);;
//	m_btnCancel.SetFlat(FALSE);
	
	m_btnUser.SetIcon(IDI_LEVEL_USER);
	m_btnUser.SetAlign(CButtonST::ST_ALIGN_VERT);

	m_btnUser2.SetIcon(IDI_LEVEL_SETUP);
	m_btnUser2.SetAlign(CButtonST::ST_ALIGN_VERT);

	m_btnUser3.SetIcon(IDI_LEVEL_ENGINEER);
	m_btnUser3.SetAlign(CButtonST::ST_ALIGN_VERT);

	if(m_bPassword)
	{
		m_wndOld.ShowWindow(SW_SHOW);
		m_wndNew.ShowWindow(SW_SHOW);
		m_edtNewPassword.ShowWindow(SW_SHOW);
		m_wndNew2.ShowWindow(SW_SHOW);
		m_edtNewPassword2.ShowWindow(SW_SHOW);
		m_btnChangePassword.ShowWindow(SW_HIDE);
		m_btnUser.ShowWindow(SW_HIDE);
		OnEngineer();
	}
	else
	{
		m_wndOld.ShowWindow(SW_HIDE);
		m_wndNew.ShowWindow(SW_HIDE);
		m_edtNewPassword.ShowWindow(SW_HIDE);
		m_wndNew2.ShowWindow(SW_HIDE);
		m_edtNewPassword2.ShowWindow(SW_HIDE);
		m_btnChangePassword.ShowWindow(SW_SHOW);
		OnUser();
	}

	m.Info.bSubDlgOpen = true;
	f.UpdateButtonState();

	f.ChangeLanguage(GetSafeHwnd());
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CDlgPassword::OnChangePassword() 
{
	CDlgPassword dlg(true);
	dlg.DoModal();
}

BOOL CDlgPassword::PreTranslateMessage(MSG* pMsg) 
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
