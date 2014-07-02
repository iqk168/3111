// DlgTemperature.cpp : implementation file
//

#include "stdafx.h"
#include "deer.h"
#include "DlgTemperature.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgTemperature dialog


CDlgTemperature::CDlgTemperature(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgTemperature::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgTemperature)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgTemperature::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgTemperature)
	DDX_Control(pDX, IDC_TAB_TEMPERATURE, m_tabTemperature);
	DDX_Control(pDX, IDOK, m_btnOK);
	DDX_Control(pDX, IDCANCEL, m_btnCancel);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgTemperature, CDialog)
	//{{AFX_MSG_MAP(CDlgTemperature)
	ON_WM_TIMER()
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_TEMPERATURE, OnSelchangeTabTemperature)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgTemperature message handlers

void CDlgTemperature::OnOK() 
{
	m.Info.bSubDlgOpen = false;
	f.UpdateButtonState();
	
	CDialog::OnOK();
}

void CDlgTemperature::OnCancel() 
{
	m.Info.bSubDlgOpen = false;
	f.UpdateButtonState();

	CDialog::OnCancel();
}

BOOL CDlgTemperature::PreTranslateMessage(MSG* pMsg) 
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

BOOL CDlgTemperature::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m.Info.bSubDlgOpen = true;
	f.UpdateButtonState();

	// init button 
	m_btnOK.SetIcon(IDI_OK);;
	m_btnOK.SetAlign(CButtonST::ST_ALIGN_VERT);;
	m_btnOK.SetFlat(FALSE);
	
	m_btnCancel.SetIcon(IDI_CANCEL);
	m_btnCancel.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnCancel.SetFlat(FALSE);
	
	//
	InitTabControl();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
void CDlgTemperature::InitTabControl()
{
	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	CRect ir,cr;
	m_tabTemperature.GetItemRect(0, &ir);
	m_tabTemperature.GetClientRect(&cr);

	// Create Object
	DlgPage.m_DlgTemperatureCalibration.Create(CDlgTemperatureCalibration::IDD,&m_tabTemperature);
	DlgPage.m_DlgTemperatureCalibration.SetWindowPos(NULL, ir.left, ir.bottom, cr.right, cr.bottom-5, SWP_NOZORDER);
	DlgPage.m_DlgTemperatureCalibration.ShowWindow(SW_SHOW);

	DlgPage.m_DlgTemperatureLookupTable.Create(CDlgTemperatureLookupTable::IDD, &m_tabTemperature);
	DlgPage.m_DlgTemperatureLookupTable.SetWindowPos(NULL, ir.left, ir.bottom, cr.right, cr.bottom-5, SWP_NOZORDER);
	DlgPage.m_DlgTemperatureLookupTable.ShowWindow(SW_HIDE);

	DlgPage.m_DlgTemperatureTool.Create(CDlgTemperatureTool::IDD, &m_tabTemperature);
	DlgPage.m_DlgTemperatureTool.SetWindowPos(NULL, ir.left, ir.bottom, cr.right, cr.bottom-5, SWP_NOZORDER);
	DlgPage.m_DlgTemperatureTool.ShowWindow(SW_HIDE);

	//
	m_tabTemperature.InsertItem(TCIF_TEXT | TCIF_PARAM, 0, "Calibration", 		-1, (LPARAM)&DlgPage.m_DlgTemperatureCalibration);
	m_tabTemperature.InsertItem(TCIF_TEXT | TCIF_PARAM, 1, "LookupTable", 		-1, (LPARAM)&DlgPage.m_DlgTemperatureLookupTable);
	if( m.Info.user == enLevelSuperUser )
		m_tabTemperature.InsertItem(TCIF_TEXT | TCIF_PARAM, 2, "Tool", 			-1, (LPARAM)&DlgPage.m_DlgTemperatureTool);

	//
	m_tabTemperature.SetCurSel(0);	

	//
	DlgPage.m_Page.mask = TCIF_PARAM;
	m_tabTemperature.GetItem(m_tabTemperature.GetCurSel(), &DlgPage.m_Page);

 	//將目前作用選擇視窗顯示
 	((CDialog *)(DlgPage.m_Page.lParam))->ShowWindow(SW_SHOW);

}
void CDlgTemperature::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	
	CDialog::OnTimer(nIDEvent);
}
void CDlgTemperature::ChangeTabPage()
{
	int iSeled = m_tabTemperature.GetCurSel();
	if( iSeled == 0 )
	{
		// 
		CString csMsg = _T("");
		csMsg = "Calibration";
//		AfxMessageBox( csMsg );
		DlgPage.m_DlgTemperatureCalibration.ChangePage();
	}
	else if( iSeled == 1 )
	{
		CString csMsg = _T("");
		csMsg = "Lookup Table";
//		AfxMessageBox( csMsg );
		DlgPage.m_DlgTemperatureLookupTable.ChangePage();
	}	
	else if( iSeled == 2 )
	{
		CString csMsg = _T("");
		csMsg = "Tool";
//		AfxMessageBox( csMsg );	
	}
}
void CDlgTemperature::OnSelchangeTabTemperature(NMHDR* pNMHDR, LRESULT* pResult) 
{
	//套用CMember->Page成員
	((CDialog *)(DlgPage.m_Page.lParam))->ShowWindow(SW_HIDE);				//將目前點畫面隱藏
	DlgPage.m_Page.mask = TCIF_PARAM;
	m_tabTemperature.GetItem(m_tabTemperature.GetCurSel(), &DlgPage.m_Page);//將目前點選畫面參數儲存
	((CDialog *)(DlgPage.m_Page.lParam))->ShowWindow(SW_SHOW);				//將目前點選畫面顯示	

	//
	ChangeTabPage();

	*pResult = 0;
}
