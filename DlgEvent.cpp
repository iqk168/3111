// DlgEvent.cpp : implementation file
//

#include "stdafx.h"
#include "deer.h"
#include "DlgEvent.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgEvent dialog
bool bSort = false;
CDlgEvent::CDlgEvent(bool Mode, CWnd* pParent /*=NULL*/)
	: CDialog(CDlgEvent::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgEvent)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	m_Mode = Mode;

//	 bSort = false;
	// m_Mode default is false;
	// If User have new request. Use it to make different.!
}


void CDlgEvent::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgEvent)
	DDX_Control(pDX, IDC_EXPORT,			m_btnExport);
	DDX_Control(pDX, IDC_SHOW_TWO_MONTH,	m_btnShowTwoMonth);
	DDX_Control(pDX, IDC_DELETE,			m_btnDelete);
	DDX_Control(pDX, IDC_EVENT,				m_listEvent);
	DDX_Control(pDX, IDCANCEL,				m_btnCancel);
	DDX_Control(pDX, IDOK,					m_btnOK);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgEvent, CDialog)
	//{{AFX_MSG_MAP(CDlgEvent)
	ON_WM_CLOSE()
	ON_WM_DESTROY()
	ON_WM_TIMER()
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_EVENT, OnColumnclickEvent)
	ON_NOTIFY(LVN_GETDISPINFO, IDC_EVENT, OnGetdispinfoEvent)
	ON_BN_CLICKED(IDC_DELETE, OnDelete)
	ON_BN_CLICKED(IDC_SHOW_TWO_MONTH, OnShowTwoMonth)
	ON_BN_CLICKED(IDC_EXPORT, OnExport)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgEvent message handlers

void CDlgEvent::OnClose() 
{
	m.Info.bSubDlgOpen = false;
	f.UpdateButtonState();
	
	CDialog::OnClose();
}

void CDlgEvent::OnDestroy() 
{
	m.Info.bSubDlgOpen = false;
	f.UpdateButtonState();

	CDialog::OnDestroy();	
}

BOOL CDlgEvent::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// init button 
	m_btnOK.SetIcon(IDI_OK);;
	m_btnOK.SetAlign(CButtonST::ST_ALIGN_VERT);;
	m_btnOK.SetFlat(FALSE);
	
	m_btnCancel.SetIcon(IDI_CANCEL);
	m_btnCancel.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnCancel.SetFlat(FALSE);

	m_btnDelete.SetIcon(IDI_DELETE);
	m_btnDelete.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnDelete.SetFlat(FALSE);
	
	m_btnShowTwoMonth.SetIcon(IDI_READ_FILE);
	m_btnShowTwoMonth.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnShowTwoMonth.SetFlat(FALSE);

	m_btnExport.SetIcon(IDI_REPORT);
	m_btnExport.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnExport.SetFlat(FALSE);

	// 修正無法顯示中文
	//
	CFont front;
	LOGFONT lf;
	memset(&lf, 0, sizeof(LOGFONT));       // clear out structure.
	lf.lfHeight = 100;                     // request a 12-pixel-height font
	if( m.UI.Language == m.enEnglish )
		strcpy(lf.lfFaceName, "Arial Black");			
	else if( m.UI.Language == m.enChinese )
	{
		if( m.Setting.m_bEnableSimplified == 1 )
//			strcpy(lf.lfFaceName, "simkai");
			strcpy(lf.lfFaceName, "Arial Black");	// 先顯示英文		
		else
			strcpy(lf.lfFaceName, "新細明體");	
//			strcpy(lf.lfFaceName, "Arial Black");	// 先顯示英文				
	}
	else
		strcpy(lf.lfFaceName, "Arial Black");			
	
	CClientDC dc(this);
	CFont font;
	VERIFY(font.CreatePointFontIndirect(&lf, &dc));  
	m_listEvent.SetFont( &font );

	// Make a level .
	// If true. It mean setup level 
	// setup level can modify event setting.
	if( !m_Mode )
	{
		m_btnDelete.EnableWindow( FALSE );	
		m_btnShowTwoMonth.EnableWindow( FALSE );
	}

	m_listEvent.SetImageList(&m.ImageList.EventType, LVSIL_SMALL);

	CHeaderCtrl	*pHeader = m_listEvent.GetHeaderCtrl();
	pHeader->SetImageList(&m.ImageList.Sort);
	pHeader->ModifyStyle(0, HDS_HOTTRACK);// | HDS_FILTERBAR | HDS_FLAT);

	COLORREF crBkColor = ::GetSysColor(COLOR_3DFACE);
	m_listEvent.SetBkColor(crBkColor);
	m_listEvent.SetTextBkColor(crBkColor);
	
	//
	ShowData(1);

	m.Info.bSubDlgOpen = true;
	f.UpdateButtonState();

	// 目前怎麼調都無法顯示簡體中文, 所以先讓簡體中文顯示英文
	if( m.UI.Language == m.enChinese && m.Setting.m_bEnableSimplified == 1 )
		;
	else
		f.ChangeLanguage(GetSafeHwnd());

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgEvent::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	
	CDialog::OnTimer(nIDEvent);
}

void CDlgEvent::OnCancel() 
{	
	m.Info.bSubDlgOpen = false;
	f.UpdateButtonState();

	CDialog::OnCancel();
}

void CDlgEvent::OnOK() 
{
	m.Info.bSubDlgOpen = false;
	f.UpdateButtonState();

	CDialog::OnOK();
}
void CDlgEvent::OnDelete() 
{
	if(IDYES != AfxMessageBox("Do you really want to delete log.?\n?",
			MB_YESNO|MB_ICONEXCLAMATION))
	{
		return; // User say no delete.!
	}

	CTime time = CTime::GetCurrentTime();
	CString cs;
	int y = time.GetYear();
	int m = time.GetMonth();
	cs.Format(".\\Log\\%d_%d.log", y, m);
	::MoveFile(cs, ".\\Log\\" + time.Format("%Y_%m_%d_%H_%M_%S") + ".Backlog");
	
	// Clear the ListCtrl
	m_listEvent.DeleteAllItems();
	AfxMessageBox("Delete File Completed");	
}
void CDlgEvent::OnShowTwoMonth() 
{
	ShowData(2);	
}

///////////////////////////////////////////////////////////////
// Dlg Function
void CDlgEvent::OnGetdispinfoEvent(NMHDR* pNMHDR, LRESULT* pResult) 
{				
	LV_DISPINFO* pDispInfo = (LV_DISPINFO*)pNMHDR;
	LV_ITEM* pItem= &(pDispInfo)->item;
	tagItem rLabel = m_Member.ElementAt(pItem->iItem);

	if (pItem->mask & LVIF_TEXT) //valid text buffer?
	{
		// then display the appropriate column
		switch(pItem->iSubItem)
		{
		case 0:
			break;
		case 1:
			sprintf(pItem->pszText, "%s", 
				rLabel.time.Format("%m/%d %H:%M:%S"));
			break;
		case 2:
			sprintf(pItem->pszText, "%d", rLabel.code);
			break;
		case 3:
			sprintf(pItem->pszText, "%s", rLabel.message);
			break;
		default:
			ASSERT(0);
			break;
		}
	}
	if (pItem->mask & LVIF_IMAGE)
	{
		// then display the appropriate column
		switch(pItem->iSubItem)
		{
		case 0:
			pItem->iImage = rLabel.level;
			break;
		default:
			ASSERT(0);
			break;
		}
	}

	*pResult = 0;
}
void CDlgEvent::OnColumnclickEvent(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	if(m_Member.GetSize() <=0) return;

	bSort = !bSort;

	switch(pNMListView->iSubItem)
	{
	case 0: // sort by Type
		qsort(static_cast<void*>(&m_Member[0]), m_Member.GetSize(),
			sizeof(tagItem), LevelCompare);
		break;
	case 1: // sort by Time
		qsort(static_cast<void*>(&m_Member[0]), m_Member.GetSize(),
			sizeof(tagItem), TimeCompare);
		break;
	case 2: // sort by Code
		qsort(static_cast<void*>(&m_Member[0]), m_Member.GetSize(),
			sizeof(tagItem), CodeCompare);
		break; 
	case 3: // sort by Note
		qsort(static_cast<void*>(&m_Member[0]), m_Member.GetSize(),
			sizeof(tagItem), MsgCompare);
		break;
	}

	SetHeaderImage(pNMListView->iSubItem);
	m_listEvent.Invalidate();

	*pResult = 0;
}

///////////////////////////////////////////////////////////////
// Event Log Function
void CDlgEvent::ShowData(int iMonth)
{
	if(!m_listEvent.DeleteAllItems())
		return;

	theApp.DoWaitCursor(1);
	while(m_listEvent.DeleteColumn(0));
	m_Member.RemoveAll();

	if(m.UI.Language == m.enChinese)
	{
		m_listEvent.InsertColumn(0, "");
		m_listEvent.InsertColumn(1, "時間");   
		m_listEvent.InsertColumn(2, "碼");
		m_listEvent.InsertColumn(3, "事件");
	}
	else
	{
		m_listEvent.InsertColumn(0, "");
		m_listEvent.InsertColumn(1, "Time");
		m_listEvent.InsertColumn(2, "Code");
		m_listEvent.InsertColumn(3, "Message");
	}
	
	m_listEvent.SetColumnWidth(0, 30);
	m_listEvent.SetColumnWidth(1, 150);
	m_listEvent.SetColumnWidth(2, 70);
	m_listEvent.SetColumnWidth(3, 620);

	tagItem Label;

	tagErrorParam err[_Max_Event];
	int iCount = f.m_Log.ReadEvent(err, iMonth);
	tagErrorMsg msg;
	for(int i=iCount-1; i>=0; i--)
	{
		msg = f.GetErrorMsg(err[i].Code);

		if(m.UI.Language == m.enChinese)
		{
			if(msg.Code == -1)
				Label.message = "錯誤碼未定義";
			else
				Label.message = msg.Chi;
		}
		else

		{
			if(msg.Code == -1)
				Label.message = "Undefine error code";
			else
				Label.message = msg.Eng;
		}

		Label.time = err[i].Time;
		Label.code = err[i].Code;
		Label.level = msg.Level - 1;
		m_Member.SetAtGrow(iCount-1-i, Label);
	}
	
	// Tell the list box to update itself.
	m_listEvent.SetItemCountEx(iCount);
	m_listEvent.Invalidate();
	SetHeaderImage(1);

	theApp.DoWaitCursor(0);
}


void CDlgEvent::SetHeaderImage(int iItem)
{
	enum Image { enAscending = 3, enDescending = 4, enType = 5 };
	HDITEM    curItem;

	CHeaderCtrl	*pHeader = m_listEvent.GetHeaderCtrl();
	if(!::IsWindow(pHeader->GetSafeHwnd()))
		return;

	for(int i=0; i<4; i++)
	{
		//pHeader->GetItem(i, &curItem);
		curItem.mask= HDI_IMAGE | HDI_FORMAT;
		if(i==0)
			curItem.iImage = enType;
		else
			curItem.iImage = -1;

		if(i==iItem && i!=0)
		{
			if(bSort)
				curItem.iImage= enAscending;
			else
				curItem.iImage= enDescending;
		}
		
		curItem.fmt= HDF_LEFT | HDF_IMAGE | HDF_STRING;
		pHeader->SetItem(i, &curItem);
	}

}
int __cdecl CDlgEvent::LevelCompare(const void *elem1, const void *elem2)
{
	tagItem *p1 = (tagItem *)elem1;
	tagItem *p2 = (tagItem *)elem2;

	if(bSort)
	{
		if(p1->level > p2->level) return 1;
		else if(p1->level < p2->level) return -1;
		else
		{
			if(p1->time > p2->time) return 1;
			else if(p1->time < p2->time) return -1;
		}
	}
	else
	{
		if(p1->level > p2->level) return -1;
		else if(p1->level < p2->level) return 1;
		else
		{
			if(p1->time > p2->time) return -1;
			else if(p1->time < p2->time) return 1;
		}
	}
	return 0;
}
int __cdecl CDlgEvent::MsgCompare(const void *elem1, const void *elem2)
{
	tagItem *p1 = (tagItem *)elem1;
	tagItem *p2 = (tagItem *)elem2;
	
	int Result;

	if(bSort)
	{
		Result = strcmp(p1->message, p2->message);
		if(Result == 0)
		{
			if(p1->time > p2->time) return 1;
			else if(p1->time < p2->time) return -1;
		}
	//	return strcmp(p1->message, p2->message);
	}
	else
	{
		Result = strcmp(p2->message, p1->message);
		if(Result == 0)
		{
			if(p1->time > p2->time) return -1;
			else if(p1->time < p2->time) return 1;
		}
	//	return strcmp(p2->message, p1->message);
	}
	return Result;
}

int __cdecl CDlgEvent::CodeCompare(const void *elem1, const void *elem2)
{
	tagItem *p1 = (tagItem *)elem1;
	tagItem *p2 = (tagItem *)elem2;

	if(bSort)
	{
		if(p1->code > p2->code) return 1;
		else if(p1->code < p2->code) return -1;
		else
		{
			if(p1->time > p2->time) return 1;
			else if(p1->time < p2->time) return -1;
		}
			
	}
	else
	{
		if(p1->code > p2->code) return -1;
		else if(p1->code < p2->code) return 1;
		else
		{
			if(p1->time > p2->time) return -1;
			else if(p1->time < p2->time) return 1;
		}
	}
	return 0;
}

int __cdecl CDlgEvent::TimeCompare(const void *elem1, const void *elem2)
{
	tagItem *p1 = (tagItem *)elem1;
	tagItem *p2 = (tagItem *)elem2;

	if(bSort)
	{
		if(p1->time > p2->time) return 1;
		else if(p1->time < p2->time) return -1;
	}
	else
	{
		if(p1->time > p2->time) return -1;
		else if(p1->time < p2->time) return 1;
	}
	return 0;
}



BOOL CDlgEvent::PreTranslateMessage(MSG* pMsg) 
{
	// z avoid ESC / Enter to crash the software
	if(pMsg->message  == WM_KEYDOWN)   
	{
		int nVirtKey = (int)pMsg->wParam;    
		if( nVirtKey == VK_ESCAPE )
			return   TRUE;   
//		if( nVirtKey == VK_RETURN )   
//			return   TRUE;   
	}	
	return CDialog::PreTranslateMessage(pMsg);
}

void CDlgEvent::OnExport() 
{
	f.ExportEventLog();
}
