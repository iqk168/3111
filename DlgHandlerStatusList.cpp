// DlgHandlerStatusList.cpp : implementation file
//

#include "stdafx.h"
#include "deer.h"
#include "DlgHandlerStatusList.h"
#include "DlgHandlerStatus.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgHandlerStatusList dialog


CDlgHandlerStatusList::CDlgHandlerStatusList(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgHandlerStatusList::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgHandlerStatusList)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgHandlerStatusList::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgHandlerStatusList)
	DDX_Control(pDX, IDOK,			m_btnOK);
	DDX_Control(pDX, IDCANCEL,		m_btnCancel);
	DDX_Control(pDX, IDC_DEL_ALL,	m_btnDelAll);
	DDX_Control(pDX, IDC_DEL,		m_btnDel);
	DDX_Control(pDX, IDC_DATA,		m_listData);
	//}}AFX_DATA_MAP

	csSelFile = _T("");
}


BEGIN_MESSAGE_MAP(CDlgHandlerStatusList, CDialog)
	//{{AFX_MSG_MAP(CDlgHandlerStatusList)
	ON_NOTIFY(LVN_GETDISPINFO, IDC_DATA, OnGetdispinfoData)
	ON_BN_CLICKED(IDC_DEL_ALL, OnDelAll)
	ON_BN_CLICKED(IDC_DEL, OnDel)
	ON_NOTIFY(NM_DBLCLK, IDC_DATA, OnDblclkData)
	ON_NOTIFY(NM_CLICK, IDC_DATA, OnClickData)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgHandlerStatusList message handlers

BOOL CDlgHandlerStatusList::PreTranslateMessage(MSG* pMsg) 
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

BOOL CDlgHandlerStatusList::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// init button 
	m_btnOK.SetIcon(IDI_OK);;
	m_btnOK.SetAlign(CButtonST::ST_ALIGN_VERT);;
	m_btnOK.SetFlat(FALSE);
	
	m_btnCancel.SetIcon(IDI_CANCEL);
	m_btnCancel.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnCancel.SetFlat(FALSE);

	m_btnDel.SetIcon(IDI_DELETE_ONE);
	m_btnDel.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnDel.SetFlat(FALSE);

	m_btnDelAll.SetIcon(IDI_DELETE);
	m_btnDelAll.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnDelAll.SetFlat(FALSE);

	//
	InitValue();

	//
	Style();

	//
	ShowTitle();

	//
	ShowData();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
void CDlgHandlerStatusList::InitValue()
{

}
void CDlgHandlerStatusList::Style()
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
void CDlgHandlerStatusList::ShowTitle()
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
		m_listData.InsertColumn(1, "檔名");   
		m_listData.InsertColumn(2, "時間");
	}
	else
	{
		m_listData.InsertColumn(0, "Item");
		m_listData.InsertColumn(1, "FileName");
		m_listData.InsertColumn(2, "Data");
	}

	// 設定預設寬度
	m_listData.SetColumnWidth(0, 100);
	m_listData.SetColumnWidth(1, 450);
	m_listData.SetColumnWidth(2, 250);
}
void CDlgHandlerStatusList::ShowData()
{
	// 顯示資料
	theApp.DoWaitCursor(1);
	int iCount = 0;
	tagHandlerStatusLogListItem Label;

	CFileFind find;	
	CString csFile = ".\\Log\\";
	BOOL bResult = find.FindFile( csFile + _StatusReportLogList );	
	CString file;
	while(bResult)
	{
		bResult = find.FindNextFile();
		file = find.GetFileName();	// Get File Name..
		if(file.Find( _StatusReportLog, 0)>-1)
		{
			if( file.Find( "Report_", 0)>-1 )
			{
				// find file success...
				iCount++;
				Label.item = iCount;
				Label.filename = file;
				
				// show file data
				CString csfile_status;
				csfile_status.Format("%s", csFile + file );
				CFileStatus status;
				CFile::GetStatus( csfile_status, status );
				CString cc;
				cc.Format("%s", status.m_mtime.Format( "%Y/%m/%d %H:%M:%S" ) );
				Label.data = cc;
				
				m_Source.SetAtGrow(iCount-1, Label);
			}			
		}
	}

	// 更新資料
	m_listData.SetItemCountEx(iCount);
	m_listData.Invalidate();

	theApp.DoWaitCursor(0);
}

int CDlgHandlerStatusList::GetFileCount()
{
	int iCount = 0;
	CFileFind find;	
	CString csFile = ".\\Log\\";
	BOOL bResult = find.FindFile( csFile + _StatusReportLogList );	
	CString file;
	while(bResult)
	{
		bResult = find.FindNextFile();
		file = find.GetFileName();	// Get File Name..
		if(file.Find( _StatusReportLog, 0)>-1)
		{
			if( file.Find( "Report_", 0)>-1 )
				iCount++;			
		}
	}

	return iCount;
}
void CDlgHandlerStatusList::OnOK() 
{
	
	CDialog::OnOK();
}

void CDlgHandlerStatusList::OnCancel() 
{
	
	CDialog::OnCancel();
}

void CDlgHandlerStatusList::OnGetdispinfoData(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LV_DISPINFO* pDispInfo = (LV_DISPINFO*)pNMHDR;
	LV_ITEM* pItem= &(pDispInfo)->item;
	tagHandlerStatusLogListItem rLabel = m_Source.ElementAt(pItem->iItem);

	if (pItem->mask & LVIF_TEXT) //valid text buffer?
	{
		// then display the appropriate column
		switch(pItem->iSubItem)
		{
		case 0:
			sprintf(pItem->pszText, "%d",		rLabel.item );			// 	
			break;
		case 1:
			sprintf(pItem->pszText, "%s",		rLabel.filename );		// 
			break;
		case 2:
			sprintf(pItem->pszText, "%s",		rLabel.data  );			// 
			break;
		default:
			ASSERT(0);
			break;
		}
	}								
	*pResult = 0;
}

void CDlgHandlerStatusList::OnDelAll() 
{
	CString csMsg = _T("");
	int iCount = GetFileCount();
	csMsg.Format("%d files, Delete.?", iCount );

	// Check Message
	if(IDNO == MessageBox(csMsg, "3111", MB_ICONSTOP | MB_YESNO))
		return;

	// Delete Files
	DeleteFileeAll();

	// Updata List
	ShowData();
}
void CDlgHandlerStatusList::DeleteFile(CString filename)
{
	if( csSelFile != "" )
	{
		CString csDelFilePath = _T("");
		csDelFilePath = ".\\Log\\" + filename;
		::DeleteFile( csDelFilePath );
	}

	//
	ShowData();
}
void CDlgHandlerStatusList::DeleteFileeAll()
{	
	CFileFind find;	
	CString csFile = ".\\Log\\";
	BOOL bResult = find.FindFile( csFile + _StatusReportLogList );	
	CString file;
	CString csFilePath = _T("");
	while(bResult)
	{
		bResult = find.FindNextFile();
		file = find.GetFileName();	// Get File Name..
		if(file.Find( _StatusReportLog, 0)>-1)
		{
			if( file.Find( "Report_", 0)>-1 )
			{	
				csFilePath = ".\\Log\\" + file;
				::DeleteFile( csFilePath );
			}			
		}
	}
}
void CDlgHandlerStatusList::OnDel() 
{
	DeleteFile( csSelFile );
}

void CDlgHandlerStatusList::OnDblclkData(NMHDR* pNMHDR, LRESULT* pResult) 
{
	CDlgHandlerStatus dlg( csSelFile );
	dlg.DoModal();
	
	*pResult = 0;
}

void CDlgHandlerStatusList::OnClickData(NMHDR* pNMHDR, LRESULT* pResult) 
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

	csSelFile		= ( m_listData.GetItemText( nItem, 1 ) );	// File Name.
	
	*pResult = 0;
}
