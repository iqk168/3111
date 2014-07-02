// DlgDebugErrorList.cpp : implementation file
//

#include "stdafx.h"
#include "deer.h"
#include "DlgDebugErrorList.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgDebugErrorList dialog


CDlgDebugErrorList::CDlgDebugErrorList(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgDebugErrorList::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgDebugErrorList)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	iSel = -1;

	m_iErrorCodeCount = 0;
}


void CDlgDebugErrorList::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgDebugErrorList)
	DDX_Control(pDX, IDOK,				m_btnOK);
	DDX_Control(pDX, IDCANCEL,			m_btnCancel);
	DDX_Control(pDX, IDC_DATA,			m_listData);
	DDX_Control(pDX, IDC_MODIFY_DATA,	m_wndModifyData);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgDebugErrorList, CDialog)
	//{{AFX_MSG_MAP(CDlgDebugErrorList)
	ON_NOTIFY(LVN_GETDISPINFO, IDC_DATA, OnGetdispinfoData)
	ON_NOTIFY(NM_DBLCLK, IDC_DATA, OnDblclkData)
	ON_NOTIFY(NM_CLICK, IDC_DATA, OnClickData)
	ON_NOTIFY(NM_RCLICK, IDC_DATA, OnRclickData)
	ON_BN_CLICKED(IDC_MODIFY_DATA, OnModifyData)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgDebugErrorList message handlers

void CDlgDebugErrorList::OnOK() 
{
	m.Info.bSubDlgOpen = false;
	f.UpdateButtonState();
	
	CDialog::OnOK();
}

void CDlgDebugErrorList::OnCancel() 
{
	m.Info.bSubDlgOpen = false;
	f.UpdateButtonState();
	
	CDialog::OnCancel();
}

BOOL CDlgDebugErrorList::OnInitDialog() 
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
	InitValue();
	
	//
	Style();

	//
	ShowTitle();

	//
	UpdataEngList();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgDebugErrorList::InitValue()
{
	CString csfile_status;
	csfile_status.Format("%s", m.FilePath.SystemPath + "ErrorCode.mdb" );
	CFileStatus status;
	CFile::GetStatus( csfile_status, status );

	CString cc;
	cc.Format("Modify Data: %s", status.m_mtime.Format( "%Y/%m/%d %H:%M:%S" ) );

	m_wndModifyData.SetWindowText( cc );
}
void CDlgDebugErrorList::Style()
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
void CDlgDebugErrorList::ShowTitle()
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
		m_listData.InsertColumn(2, "層級");
		m_listData.InsertColumn(3, "描述");
		m_listData.InsertColumn(4, "操作");
	}
	else
	{
		m_listData.InsertColumn(0, "Item");
		m_listData.InsertColumn(1, "Code");
		m_listData.InsertColumn(2, "Level");
		m_listData.InsertColumn(3, "Desc");
		m_listData.InsertColumn(4, "Operation");
	}

	// 設定預設寬度
	m_listData.SetColumnWidth(0, 80);
	m_listData.SetColumnWidth(1, 80);
	m_listData.SetColumnWidth(2, 70);
	m_listData.SetColumnWidth(3, 510);
	m_listData.SetColumnWidth(4, 810);
}
void CDlgDebugErrorList::UpdataEngList()
{
	theApp.DoWaitCursor(1);

	int iCount = 0;
	int iCodeCount = 0;
	tagErrorCodeListItem Label;

	while(1)
	{
		iCount++;
		tagErrorMsg e = f.GetErrorMsg(iCount);
		if(e.Code == -1 )
			;
		else
		{
			iCodeCount++;
			Label.item		= iCodeCount;
			Label.code		= e.Code;
			Label.level		= e.Level;
			Label.desc		= e.Eng;
			Label.operation = e.EngProcess;

			m_Source.SetAtGrow(iCodeCount-1, Label);		
		}
	
		if(iCount == _Max_Range_Error )
			break;
	}

	// 記錄資料筆數
	m_iErrorCodeCount = iCodeCount;

	// 更新資料
	m_listData.SetItemCountEx(iCodeCount);
	m_listData.Invalidate();

	theApp.DoWaitCursor(0);

}
void CDlgDebugErrorList::UpdataChiList()
{

}
void CDlgDebugErrorList::UpdataSimChiList()
{

}
BOOL CDlgDebugErrorList::PreTranslateMessage(MSG* pMsg) 
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

void CDlgDebugErrorList::OnGetdispinfoData(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LV_DISPINFO* pDispInfo = (LV_DISPINFO*)pNMHDR;
	LV_ITEM* pItem= &(pDispInfo)->item;
	tagErrorCodeListItem rLabel = m_Source.ElementAt(pItem->iItem);

	if (pItem->mask & LVIF_TEXT) //valid text buffer?
	{
		// then display the appropriate column
		switch(pItem->iSubItem)
		{
		case 0:
			sprintf(pItem->pszText, "%d",	rLabel.item );	// Item	
			break;
		case 1:
			sprintf(pItem->pszText, "%d",	rLabel.code );	// 		
			break;
		case 2:
			sprintf(pItem->pszText, "%d",	rLabel.level );	// 
			break;
		case 3:
			sprintf(pItem->pszText, "%s",	rLabel.desc );	// 
			break;
		case 4:
			sprintf(pItem->pszText, "%s",	rLabel.operation );	// 
			break;

		default:
			ASSERT(0);
			break;
		}
	}		
	*pResult = 0;
}

void CDlgDebugErrorList::OnDblclkData(NMHDR* pNMHDR, LRESULT* pResult) 
{
	if( iSel == -1 )
		;
	else
	{		
		CString csMsg = _T("");
		
		tagErrorMsg e = f.GetErrorMsg(iSel);
	
		csMsg.Format("Code: %d, Retry: %d, Skip: %d, Stop: %d, TestSiteSkip: %d, TrayChage: %d", 
			iSel, 
			e.BRetry,
			e.BSkip,
			e.BStop,
			e.BTestSiteSkip,
			e.BTrayChange );
		
		
		//
		AfxMessageBox( csMsg );
	}
	*pResult = 0;
}

void CDlgDebugErrorList::OnClickData(NMHDR* pNMHDR, LRESULT* pResult) 
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

	CString csSelItem = _T("");
	csSelItem		= ( m_listData.GetItemText( nItem, 1 ) );	// 
	iSel = atoi( csSelItem );
	
	*pResult = 0;
}

void CDlgDebugErrorList::UpdataModifyDate()
{
	CString csfile_status;
	csfile_status.Format("%s", m.FilePath.SystemPath + "ErrorCode.mdb" );
	CFileStatus status;
	CFile::GetStatus( csfile_status, status );

	CString cc;
	cc.Format("Modify Data: %s", status.m_mtime.Format( "%Y/%m/%d %H:%M:%S" ) );

	m_wndModifyData.SetWindowText( cc );
}
void CDlgDebugErrorList::OnRclickData(NMHDR* pNMHDR, LRESULT* pResult) 
{
	return;
	// Get Code
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

	CString csSelItem = _T("");
	csSelItem		= ( m_listData.GetItemText( nItem, 1 ) );	// 
	iSel = atoi( csSelItem );

	// Delete Code
	if( iSel == -1 )
		;
	else
	{		
		CString csMsg = _T("");
		
		tagErrorMsg e = f.GetErrorMsg(iSel);
	
		csMsg.Format("Code: %d, Desc: %s Delete.?\n", 
			iSel, 
			e.Eng );
		
		
		//
		if(IDYES != AfxMessageBox( csMsg,
			MB_YESNO|MB_ICONEXCLAMATION))
		{
		
		}
		else
		{
			// Yes. Delete this code..

			// Delete 
			f.DeleteErrorCode( iSel );

			// Updata List 
			UpdataEngList();

			// Updata Modify Data
			UpdataModifyDate();
		}
	}
	
	*pResult = 0;
}

void CDlgDebugErrorList::OnModifyData() 
{
	CString csMsg = _T("");
	csMsg.Format("Error Code Count :%d", m_iErrorCodeCount );

	AfxMessageBox( csMsg );
}
