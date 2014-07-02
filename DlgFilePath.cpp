// DlgFilePath.cpp : implementation file
//

#include "stdafx.h"
#include "deer.h"
#include "DlgFilePath.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgFilePath dialog


CDlgFilePath::CDlgFilePath(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgFilePath::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgFilePath)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	m_CustomFilePath = m.CustomFilePath;
}


void CDlgFilePath::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgFilePath)
	DDX_Control(pDX, IDC_P_SLT_PROTOCOL_PATH, m_edtSLTProtocolPath);
	DDX_Control(pDX, IDC_P_UPH_REPORT_PATH,			m_edtUPHReportPath);
	DDX_Control(pDX, IDC_P_TRAY_MAP_REPORT_PATH,	m_edtTrayMapReportPath);
	DDX_Control(pDX, IDC_P_MULTIRT_TRAYMAP_PATH,	m_edtMultiSVSVTrayMapPath);
	DDX_Control(pDX, IDC_P_EVENT_LOG_PATH,			m_edtEventLogPath);
	DDX_Control(pDX, IDC_P_MULTIRT_REPORT_PATH,		m_edtMultiSVReportPath);
	DDX_Control(pDX, IDC_P_MULTIRT_PROGRAM_PATH,	m_edtMultiSVProgramPath);
	DDX_Control(pDX, IDC_P_LOOPTEST_REPORT_PATH,	m_edtLoopTestReport);
	DDX_Control(pDX, IDOK,							m_btnOK);
	DDX_Control(pDX, IDCANCEL,						m_btnCancel);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgFilePath, CDialog)
	//{{AFX_MSG_MAP(CDlgFilePath)
	ON_BN_CLICKED(IDC_B_TRAYMAP_REPORT_PATH,		OnBTraymapReportPath)
	ON_BN_CLICKED(IDC_B_EVENT_LOG_PATH,				OnBEventLogPath)
	ON_BN_CLICKED(IDC_B_LOOP_TEST_RESULT_PATH,		OnBLoopTestResultPath)
	ON_BN_CLICKED(IDC_B_TEST_TRAY_MAP_PATH,			OnBTestTrayMapPath)
	ON_BN_CLICKED(IDC_B_TEST_RESULT_REPORT_PATH,	OnBTestResultReportPath)
	ON_BN_CLICKED(IDC_B_MULTISV_PROGRAM_PATH,		OnBMultisvProgramPath)
	ON_BN_CLICKED(IDC_B_UPH_REPORT,					OnBUphReport)
	ON_BN_CLICKED(IDC_B_SLT_PROTOCOL_PATH, OnBSltProtocolPath)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgFilePath message handlers

BOOL CDlgFilePath::PreTranslateMessage(MSG* pMsg) 
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

BOOL CDlgFilePath::OnInitDialog() 
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
	InitValue();

	//
	f.ChangeLanguage(GetSafeHwnd());
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
void CDlgFilePath::InitValue() 
{
	// Multi SV
	CString csFilePath = _T("");
	csFilePath = m_CustomFilePath.MultiSVProgramExportPath;
	csFilePath.Replace("\\\\", "\\");
	m_edtMultiSVProgramPath.SetWindowText( csFilePath );

	csFilePath = m_CustomFilePath.MultiSVTestReportPath;
	csFilePath.Replace("\\\\", "\\");
	m_edtMultiSVReportPath.SetWindowText( csFilePath );

	csFilePath = m_CustomFilePath.MultiSVTrayMapFilePath;
	csFilePath.Replace("\\\\", "\\");
	m_edtMultiSVSVTrayMapPath.SetWindowText( csFilePath );

	// Loop Test
	csFilePath = m_CustomFilePath.LoopTestResultReportPath;
	csFilePath.Replace("\\\\", "\\");
	m_edtLoopTestReport.SetWindowText( csFilePath );

	// Event Log
	csFilePath = m_CustomFilePath.EventLogReportPath;
	csFilePath.Replace("\\\\", "\\");
	m_edtEventLogPath.SetWindowText( csFilePath );

	// Tray Map Report
	csFilePath = m_CustomFilePath.TrayMapReportPath;
	csFilePath.Replace("\\\\", "\\");
	m_edtTrayMapReportPath.SetWindowText( csFilePath );

	// UPH Report
	csFilePath = m_CustomFilePath.UPHReportPath;
	csFilePath.Replace("\\\\", "\\");
	m_edtUPHReportPath.SetWindowText( csFilePath );

	// SLT Protocol
	csFilePath = m_CustomFilePath.SLTProtocolPath;
	csFilePath.Replace("\\\\", "\\");
	m_edtSLTProtocolPath.SetWindowText( csFilePath );
}
void CDlgFilePath::OnOK() 
{
	m.CustomFilePath = m_CustomFilePath;

	f.SavePath();

	m.Info.bSubDlgOpen = false;
	f.UpdateButtonState();
	
	CDialog::OnOK();
}

void CDlgFilePath::OnCancel() 
{
	m.Info.bSubDlgOpen = false;
	f.UpdateButtonState();
	
	CDialog::OnCancel();
}
CString CDlgFilePath::GetFilePath()
{
	CString strFilePath = _T("");
	BROWSEINFO bi;
	char Buffer[512];
	
	bi.hwndOwner = NULL;
	bi.pidlRoot = NULL;
	bi.pszDisplayName = Buffer;
	bi.lpszTitle = "Export File Path";
	bi.ulFlags = BIF_RETURNONLYFSDIRS;
	bi.lpfn = NULL;
	bi.iImage = 0;
	
	LPITEMIDLIST pIDList = SHBrowseForFolder(&bi);
	if(pIDList)
	{
		SHGetPathFromIDList(pIDList, Buffer);
		strFilePath = Buffer;
		return strFilePath;
	}
	else
		return strFilePath;	
}
void CDlgFilePath::OnBTraymapReportPath() 
{
	CString csFile = _T("");
	csFile = GetFilePath();

	if(csFile == "" )
		return;

	csFile.TrimLeft();
	csFile.TrimRight();
	csFile = csFile + "\\";
	csFile.Replace("\\", "\\\\");

	m_CustomFilePath.TrayMapReportPath = csFile;

	InitValue();
}

void CDlgFilePath::OnBEventLogPath() 
{
	CString csFile = _T("");
	csFile = GetFilePath();

	if(csFile == "" )
		return;

	csFile.TrimLeft();
	csFile.TrimRight();
	csFile = csFile + "\\";
	csFile.Replace("\\", "\\\\");

	m_CustomFilePath.EventLogReportPath = csFile;

	InitValue();	
}

void CDlgFilePath::OnBLoopTestResultPath() 
{
	CString csFile = _T("");
	csFile = GetFilePath();

	if(csFile == "" )
		return;

	csFile.TrimLeft();
	csFile.TrimRight();
	csFile = csFile + "\\";
	csFile.Replace("\\", "\\\\");

	m_CustomFilePath.LoopTestResultReportPath = csFile;

	InitValue();		
}

void CDlgFilePath::OnBTestTrayMapPath() 
{
	CString csFile = _T("");
	csFile = GetFilePath();

	if(csFile == "" )
		return;

	csFile.TrimLeft();
	csFile.TrimRight();
	csFile = csFile + "\\";
	csFile.Replace("\\", "\\\\");

	m_CustomFilePath.MultiSVTrayMapFilePath = csFile;

	InitValue();		
}

void CDlgFilePath::OnBTestResultReportPath() 
{
	CString csFile = _T("");
	csFile = GetFilePath();

	if(csFile == "" )
		return;

	csFile.TrimLeft();
	csFile.TrimRight();
	csFile = csFile + "\\";
	csFile.Replace("\\", "\\\\");

	m_CustomFilePath.MultiSVTestReportPath = csFile;

	InitValue();		
}

void CDlgFilePath::OnBMultisvProgramPath() 
{
	CString csFile = _T("");
	csFile = GetFilePath();

	if(csFile == "" )
		return;

	csFile.TrimLeft();
	csFile.TrimRight();
	csFile = csFile + "\\";
	csFile.Replace("\\", "\\\\");

	m_CustomFilePath.MultiSVProgramExportPath = csFile;

	InitValue();	
}

void CDlgFilePath::OnBUphReport() 
{
	CString csFile = _T("");
	csFile = GetFilePath();

	if( csFile == "" )
		return;

	csFile.TrimLeft();
	csFile.TrimRight();
	csFile = csFile + "\\";
	csFile.Replace("\\", "\\\\");

	m_CustomFilePath.UPHReportPath = csFile;

	InitValue();		
}

void CDlgFilePath::OnBSltProtocolPath() 
{
	CString csFile = _T("");
	csFile = GetFilePath();

	if( csFile == "" )
		return;

	csFile.TrimLeft();
	csFile.TrimRight();
	csFile = csFile + "\\";
	csFile.Replace("\\", "\\\\");

	m_CustomFilePath.SLTProtocolPath = csFile;

	InitValue();			
}
