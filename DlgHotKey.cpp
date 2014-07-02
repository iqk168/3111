// DlgHotKey.cpp : implementation file
//

#include "stdafx.h"
#include "deer.h"
#include "DlgHotKey.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgHotKey dialog


CDlgHotKey::CDlgHotKey(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgHotKey::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgHotKey)
	//}}AFX_DATA_INIT
}


void CDlgHotKey::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgHotKey)
	DDX_Control(pDX, IDCANCEL,			m_btnCancel);
	DDX_Control(pDX, IDOK,				m_btnOK);
	DDX_Control(pDX, IDC_DATA,			m_listHotKey);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgHotKey, CDialog)
	//{{AFX_MSG_MAP(CDlgHotKey)
	ON_NOTIFY(LVN_GETDISPINFO, IDC_DATA, OnGetdispinfoData)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgHotKey message handlers

BOOL CDlgHotKey::PreTranslateMessage(MSG* pMsg) 
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

BOOL CDlgHotKey::OnInitDialog() 
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
	Style();

	//
	ShowTitle();
	
	//
	ShowData();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
void CDlgHotKey::Style()
{
	LONG lStyle;
	lStyle = GetWindowLong(m_listHotKey.m_hWnd, GWL_STYLE);
	lStyle &= ~LVS_TYPEMASK; 
	lStyle |= LVS_REPORT; 
	SetWindowLong(m_listHotKey.m_hWnd, GWL_STYLE, lStyle);
	
	DWORD dwStyle = m_listHotKey.GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT;
	dwStyle |= LVS_EX_GRIDLINES;
//	dwStyle |= LVS_EX_CHECKBOXES;
	m_listHotKey.SetExtendedStyle(dwStyle); 
}
void CDlgHotKey::ShowTitle()
{
	// 設定顯示參數
	COLORREF crBkColor = ::GetSysColor(COLOR_3DFACE);
	m_listHotKey.SetTextColor(ST_BLACK);

	// 清掉全部的 Item
	if(!m_listHotKey.DeleteAllItems())
		return;

	// 先清掉全部的資料
	theApp.DoWaitCursor(1);
	while(m_listHotKey.DeleteColumn(0));
	
	// 新增 標頭
	if(m.UI.Language == m.enChinese)
	{
		m_listHotKey.InsertColumn(0, "項目");  
		m_listHotKey.InsertColumn(1, "熱鍵");   
		m_listHotKey.InsertColumn(2, "描述");
	}
	else
	{
		m_listHotKey.InsertColumn(0, "Item");
		m_listHotKey.InsertColumn(1, "Hot Key");
		m_listHotKey.InsertColumn(2, "Desc");
	}

	// 設定預設寬度
	m_listHotKey.SetColumnWidth(0, 50);
	m_listHotKey.SetColumnWidth(1, 250);
	m_listHotKey.SetColumnWidth(2, 450);

	theApp.DoWaitCursor(0);
}
void CDlgHotKey::InsertData()
{
	// Clear Data
	m_HotKeyData.csHotKey.RemoveAll();
	m_HotKeyData.csHotKeyDesc.RemoveAll();
	m_HotKeyData.csHotKeyNote.RemoveAll();

	CString csHotKey = _T("");
	CString csHotKeyDesc = _T("");
	CString csHotKeyNote = _T("");

	//
	CString csAlt			= _T("Alt + ");
	CString csCtrl			= _T("Ctrl + ");
	CString csCtrlAltShf	= _T("Ctrl + Alt + Shift + ");

	////////////////////////////////////////////////////
	// Alt
	// Hot Key: West Tool
	csHotKey = csAlt + "H";
	csHotKeyDesc = "West Tool";
	csHotKeyNote = "";
	m_HotKeyData.csHotKey.Add(csHotKey);
	m_HotKeyData.csHotKeyDesc.Add(csHotKeyDesc);
	m_HotKeyData.csHotKeyNote.Add(csHotKeyNote);

	// Hot Key: Cylinder Life Time Tool
	csHotKey = csAlt + "L";
	csHotKeyDesc = "Cylinder Life Time Tool";
	csHotKeyNote = "";
	m_HotKeyData.csHotKey.Add(csHotKey);
	m_HotKeyData.csHotKeyDesc.Add(csHotKeyDesc);
	m_HotKeyData.csHotKeyNote.Add(csHotKeyNote);

	// Hot Key: Remote IO Tool 
	csHotKey = csAlt + "O";
	csHotKeyDesc = "Remote IO Tool";
	csHotKeyNote = "";
	m_HotKeyData.csHotKey.Add(csHotKey);
	m_HotKeyData.csHotKeyDesc.Add(csHotKeyDesc);
	m_HotKeyData.csHotKeyNote.Add(csHotKeyNote);

	// Hot Key: CCD List 
	csHotKey = csAlt + "A";
	csHotKeyDesc = "Yield Monitor";
	csHotKeyNote = "";
	m_HotKeyData.csHotKey.Add(csHotKey);
	m_HotKeyData.csHotKeyDesc.Add(csHotKeyDesc);
	m_HotKeyData.csHotKeyNote.Add(csHotKeyNote);

	// Hot Key: CCD List 
	csHotKey = csAlt + "W";
	csHotKeyDesc = "CCD Camera List";
	csHotKeyNote = "";
	m_HotKeyData.csHotKey.Add(csHotKey);
	m_HotKeyData.csHotKeyDesc.Add(csHotKeyDesc);
	m_HotKeyData.csHotKeyNote.Add(csHotKeyNote);

	// Hot Key: Auto Cycle 
	csHotKey = csAlt + "Z";
	csHotKeyDesc = "Auto Cycle Setting";
	csHotKeyNote = "";
	m_HotKeyData.csHotKey.Add(csHotKey);
	m_HotKeyData.csHotKeyDesc.Add(csHotKeyDesc);
	m_HotKeyData.csHotKeyNote.Add(csHotKeyNote);

	// Hot Key: Catoregy Color
	csHotKey = csAlt + "X";
	csHotKeyDesc = "Catoregy Color";
	csHotKeyNote = "";
	m_HotKeyData.csHotKey.Add(csHotKey);
	m_HotKeyData.csHotKeyDesc.Add(csHotKeyDesc);
	m_HotKeyData.csHotKeyNote.Add(csHotKeyNote);

	// Hot Key: Bin Code Really Time Status
	csHotKey = csAlt + "B";
	csHotKeyDesc = "Bin Code Really Time Status";
	csHotKeyNote = "";
	m_HotKeyData.csHotKey.Add(csHotKey);
	m_HotKeyData.csHotKeyDesc.Add(csHotKeyDesc);
	m_HotKeyData.csHotKeyNote.Add(csHotKeyNote);

	// Hot Key: Summary Report
	csHotKey = csAlt + "S";
	csHotKeyDesc = "Summary Report";
	csHotKeyNote = "";
	m_HotKeyData.csHotKey.Add(csHotKey);
	m_HotKeyData.csHotKeyDesc.Add(csHotKeyDesc);
	m_HotKeyData.csHotKeyNote.Add(csHotKeyNote);

	// Hot Key: Error Debug
	csHotKey = csAlt + "C";
	csHotKeyDesc = "Error Code Debbug";
	csHotKeyNote = "";
	m_HotKeyData.csHotKey.Add(csHotKey);
	m_HotKeyData.csHotKeyDesc.Add(csHotKeyDesc);
	m_HotKeyData.csHotKeyNote.Add(csHotKeyNote);

	// Hot Key: Re-Load File Control
	csHotKey = csAlt + "F";
	csHotKeyDesc = "Re-Load File";
	csHotKeyNote = "";
	m_HotKeyData.csHotKey.Add(csHotKey);
	m_HotKeyData.csHotKeyDesc.Add(csHotKeyDesc);
	m_HotKeyData.csHotKeyNote.Add(csHotKeyNote);

	// Hot Key: Log Enable Control
	csHotKey = csAlt + "N";
	csHotKeyDesc = "Log File Enable/Disable";
	csHotKeyNote = "";
	m_HotKeyData.csHotKey.Add(csHotKey);
	m_HotKeyData.csHotKeyDesc.Add(csHotKeyDesc);
	m_HotKeyData.csHotKeyNote.Add(csHotKeyNote);

	// Hot Key: Jam Rate Report
	csHotKey = csAlt + "J";
	csHotKeyDesc = "Jam Rate Report Tool";
	csHotKeyNote = "";
	m_HotKeyData.csHotKey.Add(csHotKey);
	m_HotKeyData.csHotKeyDesc.Add(csHotKeyDesc);
	m_HotKeyData.csHotKeyNote.Add(csHotKeyNote);

	// Hot Key: Auto Retry Setting
	csHotKey = csAlt + "Y";
	csHotKeyDesc = "Arm Z Auto Retry Setting";
	csHotKeyNote = "";
	m_HotKeyData.csHotKey.Add(csHotKey);
	m_HotKeyData.csHotKeyDesc.Add(csHotKeyDesc);
	m_HotKeyData.csHotKeyNote.Add(csHotKeyNote);

	////////////////////////////////////////////////////
	// Ctrl
	// Hot Key: Error Code List
	csHotKey = csCtrl + "E";
	csHotKeyDesc = "Error Code List";
	csHotKeyNote = "";
	m_HotKeyData.csHotKey.Add(csHotKey);
	m_HotKeyData.csHotKeyDesc.Add(csHotKeyDesc);
	m_HotKeyData.csHotKeyNote.Add(csHotKeyNote);

	// Hot Key: Handler Status List
	csHotKey = csCtrl + "Q";
	csHotKeyDesc = "Handler Status Report List";
	csHotKeyNote = "";
	m_HotKeyData.csHotKey.Add(csHotKey);
	m_HotKeyData.csHotKeyDesc.Add(csHotKeyDesc);
	m_HotKeyData.csHotKeyNote.Add(csHotKeyNote);

	////////////////////////////////////////////////////
	// Ctrl + Alt + Shift
	// Hot Key: Motor Simple Statue
	csHotKey = csCtrlAltShf + "P";
	csHotKeyDesc = "Motor Simple Statue";
	csHotKeyNote = "";
	m_HotKeyData.csHotKey.Add(csHotKey);
	m_HotKeyData.csHotKeyDesc.Add(csHotKeyDesc);
	m_HotKeyData.csHotKeyNote.Add(csHotKeyNote);

	// Hot Key: Motor Statue
	csHotKey = csCtrlAltShf + "L";
	csHotKeyDesc = "Motor Statue";
	csHotKeyNote = "";
	m_HotKeyData.csHotKey.Add(csHotKey);
	m_HotKeyData.csHotKeyDesc.Add(csHotKeyDesc);
	m_HotKeyData.csHotKeyNote.Add(csHotKeyNote);


	// Hot Key: Thread Monitor
	csHotKey = csCtrlAltShf + "T";
	csHotKeyDesc = "Thread Monitor";
	csHotKeyNote = "";
	m_HotKeyData.csHotKey.Add(csHotKey);
	m_HotKeyData.csHotKeyDesc.Add(csHotKeyDesc);
	m_HotKeyData.csHotKeyNote.Add(csHotKeyNote);

	// Hot Key: Handler Status
	csHotKey = csCtrlAltShf + "F3";
	csHotKeyDesc = "Handler Detail Status";
	csHotKeyNote = "";
	m_HotKeyData.csHotKey.Add(csHotKey);
	m_HotKeyData.csHotKeyDesc.Add(csHotKeyDesc);
	m_HotKeyData.csHotKeyNote.Add(csHotKeyNote);
}
void CDlgHotKey::ShowData()
{
	//
	InsertData();

	// 顯示資料
	theApp.DoWaitCursor(1);
	int iCount = 0;
	tagHotKeyItem Label;

	int iSize = 0;
	iSize = m_HotKeyData.csHotKey.GetSize();
	for(int i=0;i<iSize;i++)
	{
		iCount++;
		Label.item			= iCount;
		Label.cshotkey		= m_HotKeyData.csHotKey.GetAt(i);
		Label.cshotkeydesc	= m_HotKeyData.csHotKeyDesc.GetAt(i);	
		
		m_Source.SetAtGrow(iCount-1, Label);
	}

	// 更新資料
	m_listHotKey.SetItemCountEx(iCount);
	m_listHotKey.Invalidate();

	theApp.DoWaitCursor(0);
}
void CDlgHotKey::OnOK() 
{
	
	CDialog::OnOK();
}

void CDlgHotKey::OnCancel() 
{
	
	CDialog::OnCancel();
}

void CDlgHotKey::OnGetdispinfoData(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LV_DISPINFO* pDispInfo = (LV_DISPINFO*)pNMHDR;
	LV_ITEM* pItem= &(pDispInfo)->item;
	tagHotKeyItem rLabel = m_Source.ElementAt(pItem->iItem);

	if (pItem->mask & LVIF_TEXT) //valid text buffer?
	{
		// then display the appropriate column
		switch(pItem->iSubItem)
		{
		case 0:
			sprintf(pItem->pszText, "%d",	rLabel.item );			// 	
			break;
		case 1:
			sprintf(pItem->pszText, "%s",	rLabel.cshotkey );		// 
			break;
		case 2:
			sprintf(pItem->pszText, "%s",	rLabel.cshotkeydesc );	// 
			break;
		default:
			ASSERT(0);
			break;
		}
	}		
	*pResult = 0;
}
