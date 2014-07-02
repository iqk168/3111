// DlgJamRateReportTool.cpp : implementation file
//

#include "stdafx.h"
#include "deer.h"
#include "DlgJamRateReportTool.h"
#include "DlgJamRateReportToolLastReport.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgJamRateReportTool dialog


CDlgJamRateReportTool::CDlgJamRateReportTool(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgJamRateReportTool::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgJamRateReportTool)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgJamRateReportTool::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgJamRateReportTool)
	DDX_Control(pDX, IDC_LAST_REPORT,		m_btnLastReport);
	DDX_Control(pDX, IDC_E_UPDATE_TIME,		m_wndUpdateTime);
	DDX_Control(pDX, IDC_REFREASH,			m_btnRefreash);
	DDX_Control(pDX, IDC_E_TOTAL_IC,		m_wndTotalIC);
	DDX_Control(pDX, IDC_E_LOT_START,		m_wndLotStart);
	DDX_Control(pDX, IDC_E_LOT_NUMBER,		m_wndLotNumber);
	DDX_Control(pDX, IDC_DATA,				m_listData);
	DDX_Control(pDX, IDOK,					m_btnOK);
	DDX_Control(pDX, IDCANCEL,				m_btnCancel);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgJamRateReportTool, CDialog)
	//{{AFX_MSG_MAP(CDlgJamRateReportTool)
	ON_WM_TIMER()
	ON_NOTIFY(LVN_GETDISPINFO, IDC_DATA,	OnGetdispinfoData)
	ON_BN_CLICKED(IDC_REFREASH,				OnRefreash)
	ON_BN_CLICKED(IDC_LAST_REPORT,			OnLastReport)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgJamRateReportTool message handlers

void CDlgJamRateReportTool::OnOK() 
{
	
	CDialog::OnOK();
}

void CDlgJamRateReportTool::OnCancel() 
{
	
	CDialog::OnCancel();
}

BOOL CDlgJamRateReportTool::PreTranslateMessage(MSG* pMsg) 
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

BOOL CDlgJamRateReportTool::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// init button 
	m_btnOK.SetIcon(IDI_OK);
	m_btnOK.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnOK.SetFlat(FALSE);
	
	m_btnCancel.SetIcon(IDI_CANCEL);
	m_btnCancel.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnCancel.SetFlat(FALSE);

	m_btnRefreash.SetIcon(IDI_DEBUG);
	m_btnRefreash.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnRefreash.SetFlat(FALSE);

	m_btnLastReport.SetIcon(IDI_ERROR_RATE_REPORT);
	m_btnLastReport.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnLastReport.SetFlat(FALSE);
	
	// Control File
	f.SaveJamRateData();
	f.LoadJamRateData();

	//
	Style();

	//
	ShowTitle();

	//
	ShowData();

	//
	InitValue();

	//
	ReDisplayUpdata();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
void CDlgJamRateReportTool::InitValue()
{
	// Show Lot Number
	CString csLotNumber = _T("");
	csLotNumber.Format("  %s", m.LotInfo.LotInfoNo );
	m_wndLotNumber.SetWindowText( csLotNumber );

	// Show Lot Start
	CString csLotStart = _T("");
	csLotStart.Format("  %s", m.LotInfo.LotStartTime );
	m_wndLotStart.SetWindowText( csLotStart );
	
	// 1.0Af
	// Remove this, and re-build new one
	/*
	// Total IC //
	CString csTotalIC = _T("");
	long total = 0;
	int i = 0;
	for(i=0; i<_Output_Stack_No; i++)
		total += m.Counter.OutputCount[i];
	*/

	// Total IC
	CString csTotalIC = _T("");
	long total = 0;
	total = m.m_JamRateInfo.m_lTotalUnit;
	csTotalIC.Format("  %d", total );
	m_wndTotalIC.SetWindowText( csTotalIC );
}	
void CDlgJamRateReportTool::Style()
{
	LONG lStyle;
	lStyle = GetWindowLong(m_listData.m_hWnd, GWL_STYLE);
	lStyle &= ~LVS_TYPEMASK; 
	lStyle |= LVS_REPORT; 
	SetWindowLong(m_listData.m_hWnd, GWL_STYLE, lStyle);
	
	DWORD dwStyle = m_listData.GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT;
	dwStyle |= LVS_EX_GRIDLINES;
//	dwStyle |= LVS_EX_CHECKBOXES;
	m_listData.SetExtendedStyle(dwStyle); 
}
void CDlgJamRateReportTool::ShowTitle()
{
	// 設定顯示參數
	COLORREF crBkColor = ::GetSysColor(COLOR_3DFACE);
	m_listData.SetTextColor(ST_BLACK);

	// 清掉全部的 Item
	if(!m_listData.DeleteAllItems())
		return;

	// 先清掉全部的資料
	theApp.DoWaitCursor(1);
	while(m_listData.DeleteColumn(0));
	
	// 新增 標頭
	if(m.UI.Language == m.enChinese)
	{
		m_listData.InsertColumn(0, "項目");  
		m_listData.InsertColumn(1, "錯誤碼");   
		m_listData.InsertColumn(2, "描述");
		m_listData.InsertColumn(3, "計數");
		m_listData.InsertColumn(4, "附註");
	}
	else
	{
		m_listData.InsertColumn(0, "Item");
		m_listData.InsertColumn(1, "Code");
		m_listData.InsertColumn(2, "Desc");
		m_listData.InsertColumn(3, "Count");
		m_listData.InsertColumn(4, "Note");
	}

	// 設定預設寬度
	m_listData.SetColumnWidth(0, 50);
	m_listData.SetColumnWidth(1, 100);
	m_listData.SetColumnWidth(2, 150);
	m_listData.SetColumnWidth(3, 100);
	m_listData.SetColumnWidth(4, 450);

	theApp.DoWaitCursor(0);
}
CString CDlgJamRateReportTool::GetCodeNoteDesc(int iErrorCode )
{
	CString csDetailDesc = _T("");

	for(int i=0; i<_Max_Error; i++)
	{
		if(m.Msg[i].Code == iErrorCode )
		{
			csDetailDesc = m.Msg[i].EngProcess;
			break;
		}
	}

	return csDetailDesc;
}
CString CDlgJamRateReportTool::GetCodeDesc(int iErrorCode )
{
	CString csDesc = _T("");

	for(int i=0; i<_Max_Error; i++)
	{
		if(m.Msg[i].Code == iErrorCode )
		{
			csDesc = m.Msg[i].Eng;
			break;
		}
	}

	return csDesc;
}
void CDlgJamRateReportTool::ShowData()
{
	// 顯示資料
	theApp.DoWaitCursor(1);
	int iCount = 0;
	tagRateDataLogDataItem Label;
	//m_ErrorRateData
	int iSize = m.m_ErrorRateData.GetSize();
	for( int i = 0; i<iSize; i++)
	{
		iCount++;
		Label.iItem		= i+1;															// Item									
		Label.iCode		= m.m_ErrorRateData.GetAt(i).iCode;
		Label.csDesc 	= GetCodeDesc( m.m_ErrorRateData.GetAt(i).iCode );
		Label.csDetail	= GetCodeNoteDesc( m.m_ErrorRateData.GetAt(i).iCode );
		Label.iCount 	= m.m_ErrorRateData.GetAt(i).iCount;

		m_Source.SetAtGrow(i, Label);	
	}

	// 更新資料
	m_listData.SetItemCountEx(iCount);
	m_listData.Invalidate();

	theApp.DoWaitCursor(0);
}
void CDlgJamRateReportTool::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	
	CDialog::OnTimer(nIDEvent);
}

void CDlgJamRateReportTool::OnGetdispinfoData(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LV_DISPINFO* pDispInfo = (LV_DISPINFO*)pNMHDR;
	LV_ITEM* pItem= &(pDispInfo)->item;
	tagRateDataLogDataItem rLabel = m_Source.ElementAt(pItem->iItem);

	if (pItem->mask & LVIF_TEXT) //valid text buffer?
	{
		// then display the appropriate column
		switch(pItem->iSubItem)
		{
		case 0:
			sprintf(pItem->pszText, "%d",	rLabel.iItem );		// 	
			break;
		case 1:
			sprintf(pItem->pszText, "%d",	rLabel.iCode );		// 
			break;
		case 2:
			sprintf(pItem->pszText, "%s",	rLabel.csDesc );	// 
			break;
		case 3:
			sprintf(pItem->pszText, "%d",	rLabel.iCount );	// 
			break;
		case 4:
			sprintf(pItem->pszText, "%s",	rLabel.csDetail );	// 
			break;
		default:
			ASSERT(0);
			break;
		}
	}			
	*pResult = 0;
}
void CDlgJamRateReportTool::ReDisplayUpdata() 
{
	CTime time = CTime::GetCurrentTime();
	CString csT = _T("");
	csT.Format(" %s", time.Format("Year:20%y Modth:%m Day:%d Hours:%H Min:%M Sec:%S"));

	//
	m_wndUpdateTime.SetWindowText( csT );
}
void CDlgJamRateReportTool::OnRefreash() 
{
	//
	//
	ReDisplayUpdata();

	// 
	InitValue();

	//
	ShowData();
}

void CDlgJamRateReportTool::OnLastReport() 
{
	CDlgJamRateReportToolLastReport dlg;
	dlg.DoModal();
}
