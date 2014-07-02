// DlgReLoadFile.cpp : implementation file
//

#include "stdafx.h"
#include "deer.h"
#include "DlgReLoadFile.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgReLoadFile dialog


CDlgReLoadFile::CDlgReLoadFile(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgReLoadFile::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgReLoadFile)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgReLoadFile::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgReLoadFile)
	DDX_Control(pDX, IDC_LOAD_ERRORCODE,	m_btnErrorCode);
	DDX_Control(pDX, IDC_LOAD_LANGUAGE,		m_btnLanguage);
	DDX_Control(pDX, IDOK,					m_btnOK);
	DDX_Control(pDX, IDCANCEL,				m_btnCancel);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgReLoadFile, CDialog)
	//{{AFX_MSG_MAP(CDlgReLoadFile)
	ON_BN_CLICKED(IDC_LOAD_LANGUAGE,		OnLoadLanguage)
	ON_BN_CLICKED(IDC_LOAD_ERRORCODE,		OnLoadErrorcode)
	ON_BN_CLICKED(IDC_LOAD_SYSTEM,			OnLoadSystem)
	ON_BN_CLICKED(IDC_ALIGNMENT,			OnAlignment)
	ON_BN_CLICKED(IDC_REPEAT_TRAY_CONFIM,	OnRepeatTrayConfim)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgReLoadFile message handlers

void CDlgReLoadFile::OnOK() 
{
	
	CDialog::OnOK();
}

void CDlgReLoadFile::OnCancel() 
{
	
	CDialog::OnCancel();
}

BOOL CDlgReLoadFile::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// init button 
	m_btnOK.SetIcon(IDI_OK);
	m_btnOK.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnOK.SetFlat(FALSE);
	
	m_btnCancel.SetIcon(IDI_CANCEL);
	m_btnCancel.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnCancel.SetFlat(FALSE);

	//
	f.ChangeLanguage(GetSafeHwnd());
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CDlgReLoadFile::PreTranslateMessage(MSG* pMsg) 
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
void CDlgReLoadFile::DisableUI(bool bEnable)
{
	if( bEnable )
	{
		BOOL b = TRUE;
		m_btnErrorCode.EnableWindow( b );
		m_btnLanguage.EnableWindow( b );
	}
	else
	{
		BOOL b = FALSE;
		m_btnErrorCode.EnableWindow( b );
		m_btnLanguage.EnableWindow( b );
	}
}
void CDlgReLoadFile::OnLoadLanguage() 
{
	DisableUI( false );
	f.OpenDatabase();	// Open dBase.
	f.LoadLanguage();	// Load ErrorCode
	DisableUI( true );
}

void CDlgReLoadFile::OnLoadErrorcode() 
{
	DisableUI( false );
	f.OpenDatabase();	// Open dBase.
	f.LoadErrorCode();	// Load ErrorCode
	DisableUI( true );
}

void CDlgReLoadFile::OnLoadSystem() 
{
	f.LoadSystemSetting();
}

void CDlgReLoadFile::OnAlignment() 
{
	f.LoadAlignment();	
}

void CDlgReLoadFile::OnRepeatTrayConfim() 
{
	f.LoadRepeaterTrayCommand();
	
	// show informatioon..
	CString csCommand = _T("");
	csCommand.Format("Book: %s\r\nSoak: %s\r\nStable: %s\r\nSV :%s\r\nTolerance: %s\r\nTimeout: %5.2f\r\n",
		m.m_RepeatConfimCmd.m_csBook,
		m.m_RepeatConfimCmd.m_csSoakTime,
		m.m_RepeatConfimCmd.m_csStableTime,
		m.m_RepeatConfimCmd.m_csSV,
		m.m_RepeatConfimCmd.m_csTolerance,
		m.m_RepeatConfimCmd.m_dTimeout );

	AfxMessageBox( csCommand );
}
