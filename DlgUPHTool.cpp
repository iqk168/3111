// DlgUPHTool.cpp : implementation file
//

#include "stdafx.h"
#include "deer.h"
#include "DlgUPHTool.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgUPHTool dialog


CDlgUPHTool::CDlgUPHTool(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgUPHTool::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgUPHTool)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgUPHTool::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgUPHTool)
	DDX_Control(pDX, IDC_STATIC_TS_AVG,		m_wndTsAvg);
	DDX_Control(pDX, IDOK,					m_btnOK);
	DDX_Control(pDX, IDCANCEL,				m_btnCancel);
	DDX_Control(pDX, IDC_DATA_TS,			m_listUPHTS);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgUPHTool, CDialog)
	//{{AFX_MSG_MAP(CDlgUPHTool)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_TS_CLEAR,				OnTsClear)
	ON_BN_CLICKED(IDC_TS_EXPORT,			OnTsExport)
	ON_MESSAGE(WM_UPH_TS,					OnUPHTs)
	ON_MESSAGE(WM_UPH_CLEAR,				OnUPHClear)
	ON_LBN_DBLCLK(IDC_DATA_TS,				OnDblclkDataTs)
	ON_BN_CLICKED(IDC_STATIC_TS_AVG,		OnStaticTsAvg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgUPHTool message handlers

BOOL CDlgUPHTool::PreTranslateMessage(MSG* pMsg) 
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

void CDlgUPHTool::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	
	CDialog::OnTimer(nIDEvent);
}

BOOL CDlgUPHTool::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// init button 
	m_btnOK.SetIcon(IDI_OK);;
	m_btnOK.SetAlign(CButtonST::ST_ALIGN_VERT);;
	m_btnOK.SetFlat(FALSE);
	
	m_btnCancel.SetIcon(IDI_CANCEL);
	m_btnCancel.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnCancel.SetFlat(FALSE);

	//
	InitUI();

	//
	CenterWindow();
	
	//
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
void CDlgUPHTool::InitUI()
{
	CString csTsDef = _T("");
	csTsDef.Format("%5.2f (%d)", 0.0, 0);
	m_wndTsAvg.SetWindowText(csTsDef);
}
void CDlgUPHTool::OnOK() 
{
	
	CDialog::OnOK();
}

void CDlgUPHTool::OnCancel() 
{
	
	CDialog::OnCancel();
}
void CDlgUPHTool::ShowTSData()
{

}

void CDlgUPHTool::ClearTSData() 
{	
	f.ClearUPHTSData();
	m_listUPHTS.ResetContent();
	AvgTs();
}
void CDlgUPHTool::OnTsExport() 
{
	CArray<double, double> m_Log;
	m_Log.RemoveAll();
	int iSize = m_listUPHTS.GetCount();
	for(int x=0;x<iSize;x++)
	{
		CString csValue = _T("");
		m_listUPHTS.GetText(x, csValue );
		m_Log.Add(atof(csValue));
	}
	f.ExportUPHReport(enUPHExportTsSel, m_Log );
}
void CDlgUPHTool::OnTsClear() 
{
	// Check Message
	if(IDNO == MessageBox("Clear ?", "3110", MB_ICONSTOP | MB_YESNO))
		return;

	ClearTSData();
}
void CDlgUPHTool::UpdataClearAllInfo()
{
	// Ts
	m_listUPHTS.ResetContent();
	AvgTs();
}
void CDlgUPHTool::AvgTs()
{
	// Avg
	int iSize = m_listUPHTS.GetCount();
	if( iSize > 0 )
	{
		double dTotal = 0.0;
		for(int x=0;x<iSize;x++)
		{
			CString csValue = _T("");
			m_listUPHTS.GetText(x, csValue );
			dTotal += atof(csValue);
		}
		double dTsAvg = dTotal / double(iSize);
		CString csTsAvg = _T("");
		csTsAvg.Format("%5.2f (%d)", dTsAvg, iSize);
		m_wndTsAvg.SetWindowText( csTsAvg );
	}
	else
	{
		CString csTsAvg = _T("");
		csTsAvg.Format("0.00 (0)");
		m_wndTsAvg.SetWindowText( csTsAvg );
	}
}
void CDlgUPHTool::UpdataTsInfo() 
{
	int i = m.m_UPHData.m_TSCalc.GetSize();
	CString cs = _T("");		
	if( m.m_UPHData.m_TSCalc.GetSize() > 1 )
	{
		int iNext = m.m_UPHData.m_TSCalc.GetAt(i-1);
		int iNow = m.m_UPHData.m_TSCalc.GetAt(i-2);
		int iDiff = iNext - iNow;
		cs.Format( "%5.2f", iDiff / 1000. );
		m_listUPHTS.InsertString( 0, cs );

		AvgTs();
	}
}
LRESULT CDlgUPHTool::OnUPHTs(WPARAM p, LPARAM l)
{
	UpdataTsInfo();
	return true;
}
LRESULT CDlgUPHTool::OnUPHClear(WPARAM p, LPARAM l)
{
	UpdataClearAllInfo();
	return true;
}

void CDlgUPHTool::OnDblclkDataTs() 
{
	CString csMsg = _T("");
	int iSel = m_listUPHTS.GetCurSel();
	CString csValue = _T("");
	m_listUPHTS.GetText( iSel, csValue); 
	csMsg.Format("%s, (%d)", csValue, iSel + 1);
	AfxMessageBox(csMsg);	
}

void CDlgUPHTool::OnStaticTsAvg() 
{	
	int iSel = m_listUPHTS.GetCurSel();
	m_listUPHTS.DeleteString(iSel);
}
