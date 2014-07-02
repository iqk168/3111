// DlgTemperatureLookupTable.cpp : implementation file
//

#include "stdafx.h"
#include "deer.h"
#include "DlgTemperatureLookupTable.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgTemperatureLookupTable dialog


CDlgTemperatureLookupTable::CDlgTemperatureLookupTable(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgTemperatureLookupTable::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgTemperatureLookupTable)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_lID = 0;
}


void CDlgTemperatureLookupTable::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgTemperatureLookupTable)
	DDX_Control(pDX, IDC_MODIFY_DATA,	m_wndModifyData);
	DDX_Control(pDX, IDC_E_CONTROLER,	m_cbxController);
	DDX_Control(pDX, IDC_DATA,			m_listData);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgTemperatureLookupTable, CDialog)
	//{{AFX_MSG_MAP(CDlgTemperatureLookupTable)
	ON_NOTIFY(LVN_GETDISPINFO, IDC_DATA,	OnGetdispinfoData)
	ON_NOTIFY(NM_RCLICK, IDC_DATA,			OnRclickList)
	ON_COMMAND(ID_LST_DELETE,				OnLstDelete)
	ON_COMMAND(ID_LST_DELETE_ALL,			OnLstDeleteAll)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgTemperatureLookupTable message handlers

BOOL CDlgTemperatureLookupTable::PreTranslateMessage(MSG* pMsg) 
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

BOOL CDlgTemperatureLookupTable::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	Style();

	InitController();

	InitTips();

	InitValue();

	ShowTitle();

	ShowData(m_lID);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
void CDlgTemperatureLookupTable::ShowTitle()
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
		m_listData.InsertColumn(0, "序號");   
		m_listData.InsertColumn(1, "溫度(deg)");
		m_listData.InsertColumn(2, "微調(deg)");
	}
	else
	{
		m_listData.InsertColumn(0, "Serial");
		m_listData.InsertColumn(1, "SV(deg)");
		m_listData.InsertColumn(2, "OffSet(deg)");
	}

	// 設定預設寬度
	m_listData.SetColumnWidth(0, 100);
	m_listData.SetColumnWidth(1, 180);
	m_listData.SetColumnWidth(2, 120);

	theApp.DoWaitCursor(0);
}
void CDlgTemperatureLookupTable::ShowData(int iDeviceID)
{
	CString csGetProt = _T("");
	int nSize = m.m_WestControllerList.m_List.GetSize();
	for(int i=0;i<nSize;i++)
	{
		long m_id = m.m_WestControllerList.m_List.GetAt(i).m_lID;
		if( m_id == iDeviceID )
		{
			CString csName = _T("");
			csName.Format("%s", m.m_WestControllerList.m_List.GetAt(i).csFunctionName );
			csGetProt = csName;
			break;
		}
	}

	//
	m_Source.RemoveAll();

	//
	CString csFile = m.FilePath.HeaterTempLkPath;

	//
	char cProt[1256];	
	unsigned int Count = 0;
	char cValue[256];
	unsigned int CountPrivate = 0;

	memset(cProt, '/0', sizeof(cProt));
	memset(cValue, '/0', sizeof(cValue));
	unsigned int iSize = ::GetPrivateProfileSection( csGetProt, cProt, 1256, csFile );

	//
	long lItem = 0;
	long iCount = 0;
	tagLoockupTableItem Label;
	theApp.DoWaitCursor(1);
	while(Count < iSize)
	{
		memset(cValue, '/0', sizeof(cValue));
		memcpy(cValue, &cProt[Count], strlen(&cProt[Count]));
		CountPrivate = strlen(&cProt[Count]) + 1;
		Count += CountPrivate;

		CString cs;
		cs.Format("%s", cValue );
		int iStart = cs.Find("=", 0 );
		CString csPr;
		csPr = cs.Left(iStart);

		// Get Offset
		double dOffset = 0.0;
		double dtemperature = 0.0;
		f.GetWestLoopupTableTemperature( csPr, csGetProt, dOffset );
		dtemperature = atof( csPr );
		//

		if( dOffset != 0 )
		{
			iCount++;
			// Add data
			Label.item = lItem+1;
			Label.temperature = dtemperature;
			Label.offset = dOffset;
			m_Source.SetAtGrow(iCount-1, Label);
			lItem++;
		}
	}	
	// 更新資料
	m_listData.SetItemCountEx(iCount);
	m_listData.Invalidate();

	theApp.DoWaitCursor(0);

	InitValue();
}
void CDlgTemperatureLookupTable::InitController()
{
	int nSize = m.m_WestControllerList.m_List.GetSize();
	for(int i=0;i<nSize;i++)
	{
		CString csName = _T("");
		csName.Format("%s", m.m_WestControllerList.m_List.GetAt(i).csFunctionName);
		m_cbxController.AddString(csName);
	}
	m_cbxController.SetCurSel(0);
}
void CDlgTemperatureLookupTable::InitValue()
{
	//
	CString csfile_status;
	csfile_status.Format("%s", m.FilePath.HeaterTempLkPath );
	CFileStatus status;
	CFile::GetStatus( csfile_status, status );

	CString cc;
	cc.Format("Modify Data: %s", status.m_mtime.Format( "%Y/%m/%d %H:%M:%S" ) );

	m_wndModifyData.SetWindowText( cc );
}
void CDlgTemperatureLookupTable::InitTips()
{

}
void CDlgTemperatureLookupTable::DeleteDataAll(CString Prot)
{
	CString csFile = _T("");
	f.DeleteWestLoopupTableTemperatureAll( Prot );
}
void CDlgTemperatureLookupTable::OnLstDeleteAll() 
{
	//
	CString csGetProt = _T("");
	int nSize = m.m_WestControllerList.m_List.GetSize();
	int nSel  = m_cbxController.GetCurSel();
	CString csName = _T("");
	m_cbxController.GetLBText( nSel, csName );
	for(int i=0;i<nSize;i++)
	{
		CString csFinName = m.m_WestControllerList.m_List.GetAt(i).csFunctionName;
		if( csFinName == csName )
		{
			CString csName = _T("");
			csName.Format("%s", m.m_WestControllerList.m_List.GetAt(i).csFunctionName );
			csGetProt = csName;
			break;
		}
	}
	//

	DeleteDataAll(csName);

	ShowData(m_lID);
}

void CDlgTemperatureLookupTable::DeleteData(CString Prot, CString Value)
{
	double dOffset = 0.0;
	f.DeleteWestLoopupTableTemperature( Value, Prot, dOffset);
}

void CDlgTemperatureLookupTable::OnLstDelete() 
{
	// Get the current selected item
	POSITION SelectionPos = m_listData.GetFirstSelectedItemPosition();
	int iCurSel = -1;

	// Delete the selected item from the list control 
	while (NULL != SelectionPos)
	{
		SelectionPos = m_listData.GetFirstSelectedItemPosition();
		iCurSel = m_listData.GetNextSelectedItem(SelectionPos);		
	}

	//
	CString csGetProt = _T("");
	int nSize = m.m_WestControllerList.m_List.GetSize();
	int nSel  = m_cbxController.GetCurSel();
	CString csName = _T("");
	m_cbxController.GetLBText( nSel, csName );
	for(int i=0;i<nSize;i++)
	{
		CString csFinName = m.m_WestControllerList.m_List.GetAt(i).csFunctionName;
		if( csFinName == csName )
		{
			CString csName = _T("");
			csName.Format("%s", m.m_WestControllerList.m_List.GetAt(i).csFunctionName );
			csGetProt = csName;
			break;
		}
	}
	//
	CString csValue = _T("");
	csValue = m_listData.GetItemText( iCurSel, 1 );

	double dTempValue = atof( csValue );
	csValue.Format("%5.2f", dTempValue);

	// Delete In File
	DeleteData(csGetProt, csValue);

	ShowData(m_lID);
}
void CDlgTemperatureLookupTable::OnRclickList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	CMenu obMenu;
	obMenu.LoadMenu(IDR_LIST_WEST_POPUP); 

	CMenu* pPopupMenu = obMenu.GetSubMenu(0);
	ASSERT(pPopupMenu); 
	
	// Get the cursor position
	CPoint obCursorPoint = (0, 0);
	
	GetCursorPos(&obCursorPoint);

	if (0 >= m_listData.GetSelectedCount())
	{
		pPopupMenu->EnableMenuItem(ID_LST_DELETE, MF_BYCOMMAND | MF_GRAYED | MF_DISABLED); 
	}
	else
	{
		pPopupMenu->EnableMenuItem(ID_LST_DELETE, MF_BYCOMMAND | MF_ENABLED);
	}

	// Track the popup menu
	pPopupMenu->TrackPopupMenu(TPM_LEFTALIGN|TPM_LEFTBUTTON|TPM_RIGHTBUTTON, obCursorPoint.x, 
									obCursorPoint.y, this);

	*pResult = 0;
}
void CDlgTemperatureLookupTable::Style()
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
void CDlgTemperatureLookupTable::ChangePage()
{
	ShowData(m_lID);
}
void CDlgTemperatureLookupTable::OnGetdispinfoData(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LV_DISPINFO* pDispInfo = (LV_DISPINFO*)pNMHDR;
	LV_ITEM* pItem= &(pDispInfo)->item;
	tagLoockupTableItem rLabel = m_Source.ElementAt(pItem->iItem);
	
	if (pItem->mask & LVIF_TEXT) //valid text buffer?
	{
		// then display the appropriate column
		switch(pItem->iSubItem)
		{
		case 0:
			sprintf(pItem->pszText, "%d",		rLabel.item );				// Item	
			break;
		case 1:
			sprintf(pItem->pszText, "%6.2f",	rLabel.temperature );		// Temperature		
			break;
		case 2:
			sprintf(pItem->pszText, "%6.2f",	rLabel.offset );			// Offset
			break;
		default:
			ASSERT(0);
			break;
		}
	}	
	
	*pResult = 0;
}
