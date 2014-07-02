// DlgTrayMapReport.cpp : implementation file
//

#include "stdafx.h"
#include "deer.h"
#include "DlgTrayMapReport.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgTrayMapReport dialog


CDlgTrayMapReport::CDlgTrayMapReport(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgTrayMapReport::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgTrayMapReport)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgTrayMapReport::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgTrayMapReport)
	DDX_Control(pDX, IDC_P_TRAY_MAP_REPORT_PATH,	m_edtTrayMapReportPath);
	DDX_Control(pDX, IDC_EXPORT,					m_btnExport);
	DDX_Control(pDX, IDC_DTRAY_OUTPUT1,				m_wndOutputTray1);
	DDX_Control(pDX, IDCANCEL,						m_btnCancel);
	DDX_Control(pDX, IDOK,							m_btnOK);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgTrayMapReport, CDialog)
	//{{AFX_MSG_MAP(CDlgTrayMapReport)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_EXPORT, OnExport)
	ON_BN_CLICKED(IDC_B_TRAYMAP_REPORT_PATH, OnBTraymapReportPath)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgTrayMapReport message handlers

BOOL CDlgTrayMapReport::PreTranslateMessage(MSG* pMsg) 
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

void CDlgTrayMapReport::OnTimer(UINT nIDEvent) 
{
	switch(nIDEvent)
	{
	case ID_TIME_TRAY_STATUS:
		{
			UpdateView();
		}
		break;
	}		
	CDialog::OnTimer(nIDEvent);
}

BOOL CDlgTrayMapReport::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// init button 
	m_btnOK.SetIcon(IDI_OK);
	m_btnOK.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnOK.SetFlat(FALSE);
	
	m_btnCancel.SetIcon(IDI_CANCEL);
	m_btnCancel.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnCancel.SetFlat(FALSE);
	
	m_btnExport.SetIcon(IDI_EXPORT);
	m_btnExport.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnExport.SetFlat(FALSE);	//

	InitTrayMap();

	//
	InitValue();

	//
	InitTips();

	//
	InitFilePath();

	f.ChangeLanguage(GetSafeHwnd());
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
void CDlgTrayMapReport::InitFilePath()
{
	CString csFilePath = _T("");
	csFilePath = m.CustomFilePath.TrayMapReportPath;

	csFilePath.Replace("\\\\", "\\");
	m_edtTrayMapReportPath.SetWindowText( csFilePath );
}
CString CDlgTrayMapReport::GetFilePath()
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
void CDlgTrayMapReport::InitTrayMap()
{
	CRect rect1;
	m_wndOutputTray1.GetClientRect( rect1 );

	pViewTrayOutput1 = new CViewTrayMap();
	pViewTrayOutput1->SetTrayID(0);
	if( m.TraySpec.m_OutputUseChipTray == 1 )
		pViewTrayOutput1->SetChipMode(1);
	else
		pViewTrayOutput1->SetChipMode(0);

	//
//	pViewTrayOutput1->SetTrayBrush( 0 );	// 先顯示綠色
	pViewTrayOutput1->ClearCsutomColor();
	int iSize = m.BinMap.GetSize();
	for(int i=0;i<iSize;i++)
		pViewTrayOutput1->SetCustomColor( m.BinMap.GetAt(i).code, m.BinMap.GetAt(i).color );

	//
	pViewTrayOutput1->Create(NULL, "Output1", WS_CHILD | WS_VISIBLE, rect1, 
		(CWnd *)&m_wndOutputTray1, IDC_DTRAY_OUTPUT1);	// Output 1
}
void CDlgTrayMapReport::InitValue()
{
	// Set a Timer for updata the Tray Status.
	if( m.TimerSetting.iScanTrayStatus > 0 )
		SetTimer(ID_TIME_TRAY_STATUS, m.TimerSetting.iScanTrayStatus, NULL);
	else
		SetTimer(ID_TIME_TRAY_STATUS, _Tray_Status_Timer, NULL);
}
void CDlgTrayMapReport::InitTips()
{
	// Tips 
	// Init Tips
	m_ToolTip.Create(this);
	m_ToolTip.SetMaxTipWidth(800);
	m_ToolTip.SetDelayTime( TTDT_AUTOPOP, 10000 );
	m_ToolTip.SetDelayTime( TTDT_INITIAL, 25 );
	m_ToolTip.EnableToolTips(true);

//	m_ToolTip.AddTool( GetDlgItem(IDC_ALIGNMENT_INPUT_READ),	_T("Read ArmXYZ Motor RCount Value With Input Alignment Position") );
}
void CDlgTrayMapReport::UpdateView()
{
	// If CView Object is NULL. We can not send request to Invalidate.
	if( pViewTrayOutput1 == NULL )
		return;

	pViewTrayOutput1->Invalidate(FALSE);
	// 強迫 OnReDraw
}
void CDlgTrayMapReport::OnOK() 
{
	
	CDialog::OnOK();
}

void CDlgTrayMapReport::OnCancel() 
{
	
	CDialog::OnCancel();
}

void CDlgTrayMapReport::OnExport() 
{
	if( m.UI.FileMain != "" )
	{		
//		f.ExportTrayMapReport();
		f.ExportTrayMapReportMap(m.TraySpec.Column, m.TraySpec.Row);
	}
	else
	{
		CString csMsg = _T("");
		csMsg.Format("There is no data");
		AfxMessageBox( csMsg );
	}
}
void CDlgTrayMapReport::OnBTraymapReportPath() 
{
	CString csFile = _T("");
	csFile = GetFilePath();

	if(csFile == "" )
		return;

	csFile.TrimLeft();
	csFile.TrimRight();
	csFile = csFile + "\\";
	csFile.Replace("\\", "\\\\");

	m.CustomFilePath.TrayMapReportPath = csFile;

	f.SavePath();
	f.LoadPath();
	InitFilePath();
}
