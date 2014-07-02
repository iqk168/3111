// DlgSummaryReport.cpp : implementation file
//

#include "stdafx.h"
#include "deer.h"
#include "DlgSummaryReport.h"
#include "DlgSummaryReportDetail.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgSummaryReport dialog


CDlgSummaryReport::CDlgSummaryReport(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgSummaryReport::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgSummaryReport)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	csFile = _T("");
}


void CDlgSummaryReport::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgSummaryReport)
	DDX_Control(pDX, IDC_DEL,				m_btnDel);
	DDX_Control(pDX, IDC_DEL_ALL,			m_btnDelAll);
	DDX_Control(pDX, IDC_FILE_COUNT,		m_wndFileCount);
	DDX_Control(pDX, IDC_DATA,				m_listData);
	DDX_Control(pDX, IDCANCEL,				m_btnCancel);
	DDX_Control(pDX, IDOK,					m_btnOK);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgSummaryReport, CDialog)
	//{{AFX_MSG_MAP(CDlgSummaryReport)
	ON_NOTIFY(LVN_GETDISPINFO, IDC_DATA,	OnGetdispinfoData)
	ON_BN_CLICKED(IDC_DEL_ALL,				OnDelAll)
	ON_BN_CLICKED(IDC_DEL,					OnDel)
	ON_NOTIFY(NM_CLICK, IDC_DATA,			OnClickData)
	ON_NOTIFY(NM_DBLCLK, IDC_DATA,			OnDblclkData)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgSummaryReport message handlers

void CDlgSummaryReport::OnOK() 
{
	m.Info.bSubDlgOpen = false;
	f.UpdateButtonState();	

	CDialog::OnOK();
}

void CDlgSummaryReport::OnCancel() 
{
	m.Info.bSubDlgOpen = false;
	f.UpdateButtonState();
	
	CDialog::OnCancel();
}

BOOL CDlgSummaryReport::PreTranslateMessage(MSG* pMsg) 
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

BOOL CDlgSummaryReport::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m.Info.bSubDlgOpen = true;
	f.UpdateButtonState();

	m_btnOK.SetIcon(IDI_OK);
	m_btnOK.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnOK.SetFlat(FALSE);
	
	m_btnCancel.SetIcon(IDI_CANCEL);
	m_btnCancel.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnCancel.SetFlat(FALSE);

	m_btnDelAll.SetIcon(IDI_DELETE);
	m_btnDelAll.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnDelAll.SetFlat(FALSE);

	m_btnDel.SetIcon(IDI_DELETE_ONE);
	m_btnDel.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnDel.SetFlat(FALSE);

	//
	Style();

	//
	ShowTitle();

	//
	ShowData();

	//
	InitValue();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgSummaryReport::Style()
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
void CDlgSummaryReport::InitValue()
{

}
void CDlgSummaryReport::ShowTitle()
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
		m_listData.InsertColumn(1, "檔名名稱");   
		m_listData.InsertColumn(2, "建立時間");
	}
	else
	{
		m_listData.InsertColumn(0, "Item");
		m_listData.InsertColumn(1, "FileName");
		m_listData.InsertColumn(2, "Create Data");
	}

	// 設定預設寬度
	m_listData.SetColumnWidth(0, 50);
	m_listData.SetColumnWidth(1, 350);
	m_listData.SetColumnWidth(2, 250);

	theApp.DoWaitCursor(0);

}
void CDlgSummaryReport::ShowData()
{
	// 顯示資料
	theApp.DoWaitCursor(1);
	int iCount = 0;
	tagSummaryReportItem Label;

	CFileFind find;	
	BOOL bResult = find.FindFile( m.FilePath.SummaryReportPath + _Sum1 );	
	CString file;
	while(bResult)
	{
		bResult = find.FindNextFile();
		file = find.GetFileName();	// Get File Name..
		if(file.Find( _Sum2, 0)>-1)
		{
			// find file success...
			iCount++;
			Label.item = iCount;
			Label.filename = file;

			// show file data
			CString csfile_status;
			csfile_status.Format("%s", m.FilePath.SummaryReportPath + file );
			CFileStatus status;
			CFile::GetStatus( csfile_status, status );
			CString cc;
			cc.Format("%s", status.m_mtime.Format( "%Y/%m/%d %H:%M:%S" ) );
			Label.createtime = cc;

			m_Source.SetAtGrow(iCount-1, Label);
			
		}
	}

	// 更新資料
	m_listData.SetItemCountEx(iCount);
	m_listData.Invalidate();

	theApp.DoWaitCursor(0);

	// 顯示資料筆數
	CString csCount;
	csCount.Format("Summary Report Count: %d", iCount );
	m_wndFileCount.SetWindowText( csCount );
}

void CDlgSummaryReport::OnGetdispinfoData(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LV_DISPINFO* pDispInfo = (LV_DISPINFO*)pNMHDR;
	LV_ITEM* pItem= &(pDispInfo)->item;
	tagSummaryReportItem rLabel = m_Source.ElementAt(pItem->iItem);

	if (pItem->mask & LVIF_TEXT) //valid text buffer?
	{
		// then display the appropriate column
		switch(pItem->iSubItem)
		{
		case 0:
			sprintf(pItem->pszText, "%d",	rLabel.item );			// Item	
			break;
		case 1:
			sprintf(pItem->pszText, "%s",	rLabel.filename );		// file name		
			break;
		case 2:
			sprintf(pItem->pszText, "%s",	rLabel.createtime );	// create time
			break;
		default:
			ASSERT(0);
			break;
		}
	}	
	*pResult = 0;
}

void CDlgSummaryReport::OnDelAll() 
{
	CString csMsg;
	csMsg.Format("Do You Really Want To Delete All Files?\n");
	if(IDYES != AfxMessageBox(csMsg,
		MB_YESNO|MB_ICONEXCLAMATION))
	{
		return;
	}	
	else
	{
		// Delete all file
		CFileFind find;	
		BOOL bResult = find.FindFile( m.FilePath.SummaryReportPath + _Sum1 );	
		CString file;
		while(bResult)
		{
			bResult = find.FindNextFile();
			file = find.GetFileName();	// Get File Name..
			::DeleteFile( m.FilePath.SummaryReportPath + file.Left(file.Find(_Sum2, 0)) 
			+ _Sum2 );

			//			
		}

		ShowData();
	}
}
void CDlgSummaryReport::SetColumn(int value) 
{
	// 
	if( value < 0 )
		return;

	if( value > m_listData.GetItemCount() - 1 )
		value = m_listData.GetItemCount() - 1;

	m_listData.SetItemState(value, LVIS_SELECTED|LVIS_FOCUSED, LVIS_SELECTED|LVIS_FOCUSED);
}
void CDlgSummaryReport::OnDel() 
{
	// Make Sure. User Already select a file
	POSITION pos = m_listData.GetFirstSelectedItemPosition();	
	if (pos == NULL || csFile == "" )
	{
		AfxMessageBox("Please Select File First.");
		return;
	}

	//
	CString csMsg;
	csMsg.Format("Do You Really Want To Delete This [%s] File?\n", csFile );
	if(IDYES != AfxMessageBox(csMsg,
		MB_YESNO|MB_ICONEXCLAMATION))
	{
		return;
	}
	else
	{
		// User Want To Delete this File.
		// Delete The Old File.	
		::DeleteFile( m.FilePath.SummaryReportPath + csFile.Left(csFile.Find(_Sum2, 0)) 
			+ _Sum2 );

		//
		ShowData();

		// Set Pointer to List Control..
		SetColumn( 0 ); // 0~n
	}	
}

void CDlgSummaryReport::OnClickData(NMHDR* pNMHDR, LRESULT* pResult) 
{
	POSITION pos = m_listData.GetFirstSelectedItemPosition();

	int nItem = -1;
	CString cs = "";
	if (pos == NULL)
		cs.Format("No items were selected!\n");
	else
	{
		while (pos)
		{
			nItem = m_listData.GetNextSelectedItem(pos);
			cs.Format("Item %d was selected!\n", nItem);
			// you could do your own processing on nItem here
		}
	}
	
	if( nItem == -1 )
	{
		AfxMessageBox("No Item Be Selected..");
		return;
	}	

	csFile		= ( m_listData.GetItemText( nItem, 1 ) );	// File Name.
	
	*pResult = 0;
}

void CDlgSummaryReport::OnDblclkData(NMHDR* pNMHDR, LRESULT* pResult) 
{
	CDlgSummaryReportDetail dlg( csFile );
	dlg.DoModal();

	*pResult = 0;
}
