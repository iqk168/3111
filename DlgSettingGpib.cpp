// DlgSettingGpib.cpp : implementation file
//

#include "stdafx.h"
#include "deer.h"
#include "DlgSettingGpib.h"
#include "DlgSettingNote.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgSettingGpib dialog


CDlgSettingGpib::CDlgSettingGpib(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgSettingGpib::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgSettingGpib)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	m_csGpibFile = _T("");
}

void CDlgSettingGpib::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgSettingGpib)

	DDX_Control(pDX, IDC_FILE,			m_wndFile);
	DDX_Control(pDX, IDC_SITE_SET,		m_cbSite);
	DDX_Control(pDX, IDC_COMBO_ADDR,	m_cbAddr);
	DDX_Control(pDX, IDC_COMBO_BASE,	m_cbBinBase);
	DDX_Control(pDX, IDC_COMBO_GPIB,	m_cbGpib);
	DDX_Control(pDX, IDC_EDIT_DELAY,	m_edtDelay);
	DDX_Control(pDX, IDC_EDIT_TIMEOUT,	m_edtTimeout);

	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgSettingGpib, CDialog)
	//{{AFX_MSG_MAP(CDlgSettingGpib)
	ON_BN_CLICKED(IDC_NOTE,			OnNote)
	ON_BN_CLICKED(IDC_FILE,			OnFile)
	ON_BN_CLICKED(IDC_E_STATIC,		OnEStatic)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgSettingGpib message handlers

BOOL CDlgSettingGpib::PreTranslateMessage(MSG* pMsg) 
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

BOOL CDlgSettingGpib::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
void CDlgSettingGpib::SetFile(CString csfile)
{
	m_csGpibFile = csfile;
	m_wndFile.SetWindowText( m_csGpibFile );

	//
	InitUI();

	//
	LoadFile();

	//
	InitValue();
}

void CDlgSettingGpib::InitUI()
{
	int sel = -1;
	int i;
	for (i = 0; i < 15; ++i) 
	{
		CString str;
		str.Format("GPIB%d", i);
		int n = m_cbGpib.AddString(str);
		m_cbGpib.SetItemData(n, i);
	}


	sel = -1;
	for (i = 0; i < _GPIBAddr ; ++i) 
	{
		CString str;
		str.Format("%d", i);
		m_cbAddr.AddString(str);
	}

	sel = -1;
	for (i = 0; i < 2; ++i) 
	{
		CString str;
		str.Format("%d", i);
		m_cbBinBase.AddString(str);
	}

	sel = -1;
	for (i = 0; i < 8; ++i) 
	{
		CString str;
		str.Format("%d", i+1);
		m_cbSite.AddString(str);
	}
}

void CDlgSettingGpib::LoadFile()
{
	if( m_csGpibFile == "" )
		return;

	CString csFile = _T("");
	csFile = m.FilePath.InterfaceGpibPath + m_csGpibFile;

	f.GetSetting(csFile, "GPIB", "Bin Base",		m_GPIBParam.m_iBinBase );
	f.GetSetting(csFile, "GPIB", "Addr",			m_GPIBParam.m_iGpibAddr );
	f.GetSetting(csFile, "GPIB", "Port",			m_GPIBParam.m_iGpibPort );

	f.GetSettingDouble(csFile, "GPIB", "Delay",		m_GPIBParam.m_dSendStart );
	f.GetSettingDouble(csFile, "GPIB", "Timeout",	m_GPIBParam.m_dTimeout );

	f.GetSetting(csFile, "GPIB", "Site",			m_GPIBParam.m_Site );
}
void CDlgSettingGpib::InitValue()
{	
	m_cbBinBase.SetCurSel( m_GPIBParam.m_iBinBase );
	m_cbGpib.SetCurSel( m_GPIBParam.m_iGpibPort );
	m_cbAddr.SetCurSel( m_GPIBParam.m_iGpibAddr );
	m_cbSite.SetCurSel( m_GPIBParam.m_Site - 1 );	

	CString csDelay = _T("");
	csDelay.Format("%5.2f", m_GPIBParam.m_dSendStart );
	csDelay.TrimLeft();
	csDelay.TrimRight();
	m_edtDelay.SetWindowText( csDelay );

	CString csTimeout = _T("");
	csTimeout.Format("%5.2f", m_GPIBParam.m_dTimeout );
	csTimeout.TrimLeft();
	csTimeout.TrimRight();
	m_edtTimeout.SetWindowText( csTimeout );
}
void CDlgSettingGpib::OnNote() 
{
	CDlgSettingNote dlg( theApp.enGPIB );
	dlg.DoModal();
}

void CDlgSettingGpib::OnFile() 
{

}
bool CDlgSettingGpib::SaveGPIBData()
{
	bool bOK = true;

	//
	tagGPIBParameter	m_IfUIGpib;
	if( !GetDataFromUI( m_IfUIGpib ) )
		bOK = false;

	//
	if( bOK )
		SaveDataToFile( m_IfUIGpib );

	return bOK;
}
bool CDlgSettingGpib::GetDataFromUI(tagGPIBParameter &UIData)
{
	bool bGetOK = true;

	tagGPIBParameter m_UIGpib;

	// Get All data form here.
	m_UIGpib.m_iBinBase		= m_cbBinBase.GetCurSel();
	m_UIGpib.m_iGpibPort	= m_cbGpib.GetCurSel();
	m_UIGpib.m_iGpibAddr	= m_cbAddr.GetCurSel();
	m_UIGpib.m_Site			= m_cbSite.GetCurSel() + 1 ;

	CString csDelay = _T("");
	m_edtDelay.GetWindowText( csDelay );
	m_UIGpib.m_dSendStart =	atof( csDelay );

	CString csTimeout = _T("");
	m_edtTimeout.GetWindowText( csTimeout );
	m_UIGpib.m_dTimeout	= atof( csTimeout );

	if(  m_UIGpib.m_dSendStart == 0 || m_UIGpib.m_dTimeout == 0 )
	{
		bGetOK = false;
		return bGetOK;
	}

	UIData = m_UIGpib;

	return bGetOK;
}
void CDlgSettingGpib::SaveDataToFile(tagGPIBParameter FileData)
{
	if( m_csGpibFile == "" )
		return;

	CString csFile;
	csFile = m.FilePath.InterfaceGpibPath + m_csGpibFile;

	f.SaveSetting(csFile, "GPIB", "Bin Base",		FileData.m_iBinBase );
	f.SaveSetting(csFile, "GPIB", "Addr",			FileData.m_iGpibAddr );
	f.SaveSetting(csFile, "GPIB", "Port",			FileData.m_iGpibPort );

	f.SaveSettingDouble(csFile, "GPIB", "Delay",	FileData.m_dSendStart );
	f.SaveSettingDouble(csFile, "GPIB", "Timeout",	FileData.m_dTimeout );

	f.SaveSetting(csFile, "GPIB", "Site",			FileData.m_Site );
}

void CDlgSettingGpib::OnEStatic() 
{
	m_wndFile.ShowWindow( TRUE );		
}
