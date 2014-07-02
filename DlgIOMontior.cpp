// DlgIOMontior.cpp : implementation file
//

#include "stdafx.h"
#include "deer.h"
#include "DlgIOMontior.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgIOMontior dialog


CDlgIOMontior::CDlgIOMontior(bool bOnlyShow, CWnd* pParent /*=NULL*/)
	: CDialog(CDlgIOMontior::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgIOMontior)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	m_bOnlyShow = bOnlyShow;
}


void CDlgIOMontior::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgIOMontior)
	DDX_Control(pDX, IDC_TAB_IO,				m_tabIO);
	DDX_Control(pDX, IDCANCEL,					m_btnCancel);
	DDX_Control(pDX, IDOK,						m_btnOK);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgIOMontior, CDialog)
	//{{AFX_MSG_MAP(CDlgIOMontior)
	ON_WM_TIMER()
	ON_WM_DESTROY()
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_IO, OnSelchangeTabIo)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgIOMontior message handlers

void CDlgIOMontior::OnOK() 
{
	if(!m_bOnlyShow)
	{
		if( m.Setting.m_bByPassEnableIORecovery == 1)
		{
			if(IDYES != AfxMessageBox("Do You Want to Reset the IO Monitor Old Setting?\n?",
				MB_YESNO|MB_ICONEXCLAMATION))
			{
				// User want to keep the setting
			}
			else
			{
				m.OutSet = OldOutSet;
				m.RemoteOutSet = OldRemoteSet;
			}
			// User want to Reset.!
		}
		else
		{
			m.OutSet = OldOutSet;
			m.RemoteOutSet = OldRemoteSet;
		}
	}
	// No enable IO Recovery. Just set it back.!

	// Reset IO setting. The IO setting is before User open IO dialog.
	// if User want reset it.!

	m.Info.bSubDlgOpen = false;
	f.UpdateButtonState();	
	
	m.Info.bIOMonitor = false;
	// If IO Montior Close. We set this flag to true.!
	// Because we need enable Button function

	CDialog::OnOK();
}

void CDlgIOMontior::OnCancel() 
{
	m.Info.bIOMonitor = false;
	// If IO Montior Close. We set this flag to true.!
	// Because we need enable Button function

	if(!m_bOnlyShow)
	{
		if( m.Setting.m_bByPassEnableIORecovery == 1)
		{
			if(IDYES != AfxMessageBox("Do You Want to Reset the IO Monitor Old Setting?\n?",
				MB_YESNO|MB_ICONEXCLAMATION))
			{
				// User want to keep the setting
			}
			else
			{
				m.OutSet = OldOutSet;
				m.RemoteOutSet = OldRemoteSet;
			}
			// User want to Reset.!
		}
		else
		{
			m.OutSet = OldOutSet;
			m.RemoteOutSet = OldRemoteSet;
		}
	}
	// No enable IO Recovery. Just set it back.!

	// Reset IO setting. The IO setting is before User open IO dialog.
	// if User want reset it.!

	m.Info.bSubDlgOpen = false;
	f.UpdateButtonState();	

	CDialog::OnCancel();
}

BOOL CDlgIOMontior::PreTranslateMessage(MSG* pMsg) 
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

void CDlgIOMontior::OnTimer(UINT nIDEvent) 
{	
	CDialog::OnTimer(nIDEvent);
}

BOOL CDlgIOMontior::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m.Info.bIOMonitor = true;
	// If IO Montior Open. We set this flag to true.!
	// Because we need disable Button function

	m.Info.bSubDlgOpen = true;
	f.UpdateButtonState();

	OldOutSet = m.OutSet;
	OldRemoteSet = m.RemoteOutSet;
	// It is for backup IO Setting.
	// Whe user close IO dialog. We need to reset IO setting.

	// init button 
	m_btnOK.SetIcon(IDI_OK);
	m_btnOK.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnOK.SetFlat(FALSE);
	
	m_btnCancel.SetIcon(IDI_CANCEL);
	m_btnCancel.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnCancel.SetFlat(FALSE);

	//
	InitTabControl();
	
	f.ChangeLanguage(GetSafeHwnd());

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgIOMontior::InitTabControl()
{
	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	CRect ir,cr;
	m_tabIO.GetItemRect(0, &ir);
	m_tabIO.GetClientRect(&cr);

	// Create Object
	DlgPage.m_DlgHandler.Create(CDlgIOMontiorHandler::IDD,&m_tabIO);
	DlgPage.m_DlgHandler.SetOnlyShow( m_bOnlyShow );
	DlgPage.m_DlgHandler.SetWindowPos(NULL, ir.left, ir.bottom, cr.right, cr.bottom-5, SWP_NOZORDER);
	DlgPage.m_DlgHandler.ShowWindow(SW_SHOW);

	DlgPage.m_DlgRemote.Create(CDlgIOMontiorRemote::IDD, &m_tabIO);
	DlgPage.m_DlgRemote.SetOnlyShow( m_bOnlyShow );
	DlgPage.m_DlgRemote.SetWindowPos(NULL, ir.left, ir.bottom, cr.right, cr.bottom-5, SWP_NOZORDER);
	DlgPage.m_DlgRemote.ShowWindow(SW_HIDE);

	DlgPage.m_DlgATCModule.Create(CDlgIOMontiorATCModule::IDD, &m_tabIO);
	DlgPage.m_DlgATCModule.SetOnlyShow( m_bOnlyShow );
	DlgPage.m_DlgATCModule.SetWindowPos(NULL, ir.left, ir.bottom, cr.right, cr.bottom-5, SWP_NOZORDER);
	DlgPage.m_DlgATCModule.ShowWindow(SW_HIDE);

	DlgPage.m_DlgPTCModule.Create(CDlgIOMontiorPTCModule::IDD, &m_tabIO);
	DlgPage.m_DlgPTCModule.SetOnlyShow( m_bOnlyShow );
	DlgPage.m_DlgPTCModule.SetWindowPos(NULL, ir.left, ir.bottom, cr.right, cr.bottom-5, SWP_NOZORDER);
	DlgPage.m_DlgPTCModule.ShowWindow(SW_HIDE);

	//
	int iCount = 0;
	m_tabIO.InsertItem(TCIF_TEXT | TCIF_PARAM, iCount, "Handler", 		-1, (LPARAM)&DlgPage.m_DlgHandler);
	
	if( m.Setting.m_bEnableRemoteIO == 1 )
	{
		iCount++;
		m_tabIO.InsertItem(TCIF_TEXT | TCIF_PARAM, iCount, "Panel",			-1, (LPARAM)&DlgPage.m_DlgRemote);
	}

	if( m.Setting.m_bEnableATCModule == 1 && m.Setting.m_bEnableRemoteIO == 1 )
	{
		iCount++;
		m_tabIO.InsertItem(TCIF_TEXT | TCIF_PARAM, iCount, "ATC Module",	-1, (LPARAM)&DlgPage.m_DlgATCModule);
	}

	if( m.Setting.m_bEnablePTCModule == 1 && m.Setting.m_bEnableRemoteIO == 1 )
	{
		iCount++;
		m_tabIO.InsertItem(TCIF_TEXT | TCIF_PARAM, iCount, "PTC Module",	-1, (LPARAM)&DlgPage.m_DlgPTCModule);
	}

	//
	m_tabIO.SetCurSel(0);	

	//
	DlgPage.m_Page.mask = TCIF_PARAM;
	m_tabIO.GetItem(m_tabIO.GetCurSel(), &DlgPage.m_Page);

 	//將目前作用選擇視窗顯示
 	((CDialog *)(DlgPage.m_Page.lParam))->ShowWindow(SW_SHOW);
}
void CDlgIOMontior::OnDestroy() 
{
	CDialog::OnDestroy();	
}

void CDlgIOMontior::OnSelchangeTabIo(NMHDR* pNMHDR, LRESULT* pResult) 
{
	//套用CMember->Page成員
	((CDialog *)(DlgPage.m_Page.lParam))->ShowWindow(SW_HIDE); //將目前點畫面隱藏
	DlgPage.m_Page.mask = TCIF_PARAM;
	m_tabIO.GetItem(m_tabIO.GetCurSel(), &DlgPage.m_Page);//將目前點選畫面參數儲存
	((CDialog *)(DlgPage.m_Page.lParam))->ShowWindow(SW_SHOW);//將目前點選畫面顯示
	
	*pResult = 0;
}
