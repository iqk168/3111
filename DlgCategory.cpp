// DlgCategory.cpp : implementation file
//

#include "stdafx.h"
#include "deer.h"
#include "DlgCategory.h"

//
#include "ColorPickerCB.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgCategory dialog


CDlgCategory::CDlgCategory(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgCategory::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgCategory)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	m_fChange = false;

	BinMap.RemoveAll();

	BinMap.Copy(m.BinMap);
}

void CDlgCategory::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgCategory)
	DDX_Control(pDX, IDC_E_PF,			m_wndPF);
	DDX_Control(pDX, IDC_E_HW,			m_wndHw);
	DDX_Control(pDX, IDC_E_COLOR,		m_wndColor);
	DDX_Control(pDX, IDC_E_CODE,		m_wndCode);
	DDX_Control(pDX, IDC_E_COLOR_BK,	m_wndColorBk);
	DDX_Control(pDX, IDC_E_DESC,		m_wndDescription);
	DDX_Control(pDX, IDC_E_SW_NUMBER,	m_wndSWNumber);
	DDX_Control(pDX, IDC_E_ITEM,		m_wndItem);
	DDX_Control(pDX, IDC_FILE,			m_wndFile);
	DDX_Control(pDX, IDC_DATA,			m_listData);

	//
	DDX_Control(pDX, IDCANCEL,			m_btnCancel);
	DDX_Control(pDX, IDOK,				m_btnOK);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgCategory, CDialog)
	//{{AFX_MSG_MAP(CDlgCategory)
	ON_WM_SHOWWINDOW()
	ON_NOTIFY(LVN_GETDISPINFO, IDC_DATA,	OnGetdispinfoData)
	ON_BN_CLICKED(IDC_FILE,					OnFile)
	ON_NOTIFY(NM_CLICK, IDC_DATA,			OnClickData)
	ON_BN_CLICKED(IDC_F_SET,				OnFSet)
	ON_BN_CLICKED(IDC_F_ADD,				OnFAdd)
	ON_BN_CLICKED(IDC_F_DEL,				OnFDel)
	ON_BN_CLICKED(IDC_F_UP,					OnFUp)
	ON_BN_CLICKED(IDC_F_DOWN,				OnFDown)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgCategory message handlers

BOOL CDlgCategory::PreTranslateMessage(MSG* pMsg) 
{
	// Tips
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

void CDlgCategory::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);	
}

BOOL CDlgCategory::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m.Info.bSubDlgOpen = true;
	f.UpdateButtonState();	

	// init button 
	m_btnOK.SetIcon(IDI_SAVE);;
	m_btnOK.SetAlign(CButtonST::ST_ALIGN_VERT);;
	m_btnOK.SetFlat(FALSE);
	
	m_btnCancel.SetIcon(IDI_CANCEL);
	m_btnCancel.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnCancel.SetFlat(FALSE);
	
	//
	Style();

	//
	InitColorCombox();
	InitPFCombox();
	InitHWCombox();

	//
	ShowTitle();

	//
	ShowData();

	// 
	InitValue();

	//
	SetDefaultColumn(0);

	//
	SetColumn(0);

	//
	RetUI(0);

	//
	InitTips();

	//
	f.SetTitleExtend(this, theApp.enTitleTrayFile );

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
void CDlgCategory::InitTips()
{
	// Init Tips
	m_ToolTip.Create(this);
	m_ToolTip.SetMaxTipWidth(800);
	m_ToolTip.SetDelayTime( TTDT_AUTOPOP, 10000 );
	m_ToolTip.SetDelayTime( TTDT_INITIAL, 25 );
	m_ToolTip.EnableToolTips(true);

	m_ToolTip.AddTool( GetDlgItem(IDC_STATIC_ITEM),			
		_T("Item") );
	m_ToolTip.AddTool( GetDlgItem(IDC_STATIC_SW_NUMBER),			
		_T("Software Number") );
	m_ToolTip.AddTool( GetDlgItem(IDC_STATIC_COLOR),			
		_T("Color\r\nThis bin value in traymap color") );
	m_ToolTip.AddTool( GetDlgItem(IDC_STATIC_CODE),			
		_T("Color\r\nThis bin value in traymap color") );
	m_ToolTip.AddTool( GetDlgItem(IDC_STATIC_DESC),			
		_T("Description\r\nThis bin value description") );
	m_ToolTip.AddTool( GetDlgItem(IDC_STATIC_PF),			
		_T("PF\r\nThis bin value pass or fail\r\n1 for pass\r\n0 for fail") );
	m_ToolTip.AddTool( GetDlgItem(IDC_STATIC_HW),			
		_T("H/W\r\nThis bin value output position") );

}

void CDlgCategory::SetColumn(int col )
{
	// 
	if( col < 0 )
		return;

	if( col > m_listData.GetItemCount() - 1 )
		col = m_listData.GetItemCount() - 1;

	m_listData.SetItemState(col, LVIS_SELECTED|LVIS_FOCUSED, LVIS_SELECTED|LVIS_FOCUSED);
//	m_listData.SetItemState(col, LVIS_SELECTED, LVIS_SELECTED);

	GetColumnDATA( col );
}
void CDlgCategory::SetDefaultColumn(int col)
{
	if( col < 0 )
		return;

	if( col > m_listData.GetItemCount() - 1 )
		col = m_listData.GetItemCount() - 1;

	m_listData.SetItemState(col, LVIS_SELECTED|LVIS_FOCUSED, LVIS_SELECTED|LVIS_FOCUSED);

	GetColumnDATA( col );
}
void CDlgCategory::ShowTitle()
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
		m_listData.InsertColumn(1, "S/W 項目");
		m_listData.InsertColumn(2, "顏色"); 
		m_listData.InsertColumn(3, "錯誤碼");   
		m_listData.InsertColumn(4, "描述");
		m_listData.InsertColumn(5, "P/F");
		m_listData.InsertColumn(6, "實體");
	}
	else
	{
		m_listData.InsertColumn(0, "Item");  
		m_listData.InsertColumn(1, "S/W Number");
		m_listData.InsertColumn(2, "Color"); 
		m_listData.InsertColumn(3, "Code");   
		m_listData.InsertColumn(4, "Description");
		m_listData.InsertColumn(5, "P/F");
		m_listData.InsertColumn(6, "Hardware");
	}

	// 設定預設寬度
	m_listData.SetColumnWidth(0, 50);
	m_listData.SetColumnWidth(1, 100);
	m_listData.SetColumnWidth(2, 150);
	m_listData.SetColumnWidth(3, 100);
	m_listData.SetColumnWidth(4, 150);
	m_listData.SetColumnWidth(5, 150);
	m_listData.SetColumnWidth(6, 150);

	theApp.DoWaitCursor(0);
}
void CDlgCategory::ShowData()
{
	//
	m_listData.ResetColors();

	// 顯示資料
	theApp.DoWaitCursor(1);
	int iCount = 0;
	tagCatoregyFileItem Label;

	int iSize = 0;
	iSize = BinMap.GetSize();
	for(int i=0;i<iSize;i++)
	{
		iCount++;
		Label.item			= iCount;
		Label.software		= BinMap.GetAt(i).software;
		Label.code			= BinMap.GetAt(i).code;
		Label.description	= BinMap.GetAt(i).description;
		Label.pass			= BinMap.GetAt(i).pass;
		Label.color			= BinMap.GetAt(i).color;
		Label.hardware		= BinMap.GetAt(i).hardware + 1;

		//
		m_listData.SetRowColor( BinMap.GetAt(i).color, i);
//		m_listData.SetCellColor( BinMap.GetAt(i).color, i, 2);

		m_Source.SetAtGrow(iCount-1, Label);
	}

	//
	// 更新資料
	m_listData.SetItemCountEx(iCount);
	m_listData.Invalidate();

	CString csMsg = _T("");
	csMsg.Format("%s (%d)", m.UI.FileMainMapping, iCount);
	m_wndFile.SetWindowText( csMsg );

	theApp.DoWaitCursor(0);
}
void CDlgCategory::InitColorCombox()
{
	//
	m_wndColor.ResetContent();

	//
	int iSize = m.BinColorItem.GetSize();
	for(int i=0;i<iSize;i++)
	{
		CString cs = _T("");
		cs.Format("%d", i);
		m_wndColor.AddColor(cs, m.BinColorItem.GetAt(i).color );
	}
}

void CDlgCategory::InitPFCombox()
{
	//
	m_wndPF.ResetContent();

	//
	for(int i=0;i<2;i++)
	{
		CString csValue = _T("");
		csValue.Format("%d", i);
		m_wndPF.AddString( csValue );
	}
}
void CDlgCategory::InitHWCombox()
{
	//
	m_wndHw.ResetContent();

	//
	for(int i=0;i<_Output_Stack_No;i++)
	{
		CString csHWValue = _T("");
		csHWValue.Format("%d", i+1);
		m_wndHw.AddString( csHWValue );
	}
}
void CDlgCategory::InitValue()
{

}
void CDlgCategory::Style()
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

////////////////////////////////////////////////////////////////////////
// Check Code is repeat or not
// OK return true (No repeat)
////////////////////////////////////////////////////////////////////////
bool CDlgCategory::CheckCodeVaild() 
{
	bool bOK = true;

	int iSize = BinMap.GetSize();
	for(int i=0;i<iSize;i++)
	{
		CString csReferCode = _T("");
		csReferCode = BinMap.GetAt(i).code;
		for(int j=0;j<iSize;j++)
		{
			CString csCheckCode = _T("");
			csCheckCode = BinMap.GetAt(j).code;
			if( ( csReferCode == csCheckCode ) && i!=j )
			{
				bOK = false;
				break;
			}
		}
	}
	return bOK;
}
void CDlgCategory::SaveData() 
{
	//
	m.BinMap.RemoveAll();
	m.BinMap.Copy(BinMap);

	// 存到實體檔案
	CString csFile = _T("");
	CFileFind file;
	if(!file.FindFile( m.FilePath.CategoryPath + "\\" + m.UI.FileMainMapping))
	{		
		return;
	}
	csFile = m.UI.FileMainMapping;
	bool bOK = false;
	bOK = f.SaveBinMapping( csFile, &BinMap);

	if( !bOK)
	{
		CString csMsg = _T("");
		csMsg.Format("Save mapping to file fail.!");
		AfxMessageBox( csMsg );
	}
}
void CDlgCategory::OnOK() 
{
	if( !CheckCodeVaild() )
	{
		CString csMsg = _T("");
		csMsg.Format( "Code is repeat.! Please check again.!" );
		AfxMessageBox( csMsg );
		return;
	}

	SaveData();

	m.Info.bSubDlgOpen = false;
	f.UpdateButtonState();		

	CDialog::OnOK();
}

void CDlgCategory::OnCancel() 
{
	if( m_fChange )
	{
		if(IDYES != AfxMessageBox("Data is modified. Save?\n",
			MB_YESNO|MB_ICONEXCLAMATION))
		{
			m.Info.bSubDlgOpen = false;
			f.UpdateButtonState();
			CDialog::OnCancel();
		}
		else
			OnOK();
	}
	else
	{		
		m.Info.bSubDlgOpen = false;
		f.UpdateButtonState();	
		
		CDialog::OnCancel();
	}
}

void CDlgCategory::OnGetdispinfoData(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LV_DISPINFO* pDispInfo = (LV_DISPINFO*)pNMHDR;	
	LV_ITEM* pItem= &(pDispInfo)->item;
	tagCatoregyFileItem rLabel = m_Source.ElementAt(pItem->iItem);

	if (pItem->mask & LVIF_TEXT) //valid text buffer?
	{
		// then display the appropriate column
		switch(pItem->iSubItem)
		{
		case 0:
			sprintf(pItem->pszText, "%d",	rLabel.item );			
			break;
		case 1:
			sprintf(pItem->pszText, "%s",	rLabel.software );		
			break;
		case 2:
			sprintf(pItem->pszText, "%d",	rLabel.color );	
			break;
		case 3:
			sprintf(pItem->pszText, "%s",	rLabel.code );	
			break;
		case 4:
			sprintf(pItem->pszText, "%s",	rLabel.description );	
			break;
		case 5:
			sprintf(pItem->pszText, "%d",	rLabel.pass );	
			break;
		case 6:
			sprintf(pItem->pszText, "%d",	rLabel.hardware );	
			break;

		default:
			ASSERT(0);
			break;
		}
	}		

	*pResult = 0;
}
  
void CDlgCategory::OnFile() 
{
	long lColor = RGB(0, 255, 0);
	CString csColor = _T("");
	csColor.Format("Color: %d", lColor);

	AfxMessageBox( csColor );
}
void CDlgCategory::GetColumnDATA(int nItem )
{
	// Init value
	int iItem				= 0;
	int iSWNumber			= 0;
	int iColor				= 0;
	CString csCode			= _T("");
	CString csDescription	= _T("");
	int		iPF				= 0;	// Fail
	int		iHWNumber		= 0;

	// Get value from dialog
	iItem					= atoi(	m_listData.GetItemText( nItem, 0 ) );	// Item
	iSWNumber				= atoi(	m_listData.GetItemText( nItem, 1 ) );	// SW Number
	iColor					= atoi(	m_listData.GetItemText( nItem, 2 ) );	// Color
	csCode					= m_listData.GetItemText( nItem, 3 );			// Code
	csDescription			= m_listData.GetItemText( nItem, 4 );			// Description
	iPF						= atoi(	m_listData.GetItemText( nItem, 5 ) );	// PF
	iHWNumber				= atoi(	m_listData.GetItemText( nItem, 6 ) );	// PF
	
	// Item
	CString csItem = _T("");
	csItem.Format("%d", iItem );
	m_wndItem.SetWindowText( csItem );

	// SW Number 
	CString csSWNumber = _T("");
	csSWNumber.Format("%d", iSWNumber );
	m_wndSWNumber.SetWindowText( csSWNumber );
	
	// Code
	m_wndCode.SetWindowText( csCode );

	// Description
	m_wndDescription.SetWindowText( csDescription );

	// Color
	m_wndColorBk.SetNewBkColor( iColor );
	m_wndColor.SetSelectedColorValue( iColor );

	// PF
	CString csPF = _T("");
	csPF.Format("%d", iPF );
	int iSetPF = m_wndPF.FindString(0, csPF);
	m_wndPF.SetCurSel( iSetPF );
	
	// HW
	CString csHW = _T("");
	csHW.Format("%d", iHWNumber);
	int iSetHW = m_wndHw.FindString(0, csHW );
	m_wndHw.SetCurSel( iSetHW );
}
void CDlgCategory::OnClickData(NMHDR* pNMHDR, LRESULT* pResult) 
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

	//
	GetColumnDATA( nItem );

	//
	RetUI( nItem );

	*pResult = 0;
}

void CDlgCategory::OnFSet() 
{
	if( !f.CheckEnaleChange() )
		return;

	//
	BinSaveData();

	//
	ShowData();

	//
	m_fChange = true;
}
void CDlgCategory::BinSaveData()
{
	int nItem = -1;
	CString csItem = "";
	m_wndItem.GetWindowText( csItem );
	nItem = atoi( csItem );
	nItem--;

	if( nItem == -1 )
	{
		AfxMessageBox("No Item Be Selected..");
		return;
	}

	// Init value
	int iItem				= 0;
	int iSWNumber			= 0;
	long lColor				= 0;
	CString csCode			= _T("");
	CString csDescription	= _T("");
	int		iPF				= 0;	// Fail
	int		iHWNumber		= 0;

	// PF
	CString csPF = _T("");
	m_wndPF.GetWindowText( csPF );
	iPF = atoi( csPF );

	// HW 
	CString csHW = _T("");
	m_wndHw.GetWindowText( csHW );
	iHWNumber = atoi( csHW );

	// Color 
	lColor = m_wndColor.GetSelectedColorValue();

	// Code 
	m_wndCode.GetWindowText( csCode );
	csCode.TrimLeft();
	csCode.TrimRight();
	
	// Description
	m_wndDescription.GetWindowText( csDescription );
	csDescription.TrimLeft();
	csDescription.TrimRight();

	// SW Number
	CString csSWNumber = _T("");
	m_wndSWNumber.GetWindowText( csSWNumber );
	csSWNumber.TrimLeft();
	csSWNumber.TrimRight();
	iSWNumber = atoi( csSWNumber );

	// Debug 
	CString csInfo = _T("");
	csInfo.Format("PF: %d, HW: %d, Color: %d, Code: %s, Desc: %s, SW: %d", 
		iPF, iHWNumber, lColor, csCode, csDescription, iSWNumber );
//	AfxMessageBox( csInfo );
	tagBinMapping m_BinDATA;

	m_BinDATA.code			= csCode;
	m_BinDATA.color			= lColor;
	m_BinDATA.description	= csDescription;
	iHWNumber--;
	m_BinDATA.hardware		= iHWNumber;	
	m_BinDATA.pass			= iPF == 1 ? true : false;
	m_BinDATA.software		= csSWNumber;

	BinMap.SetAt(nItem, m_BinDATA );
}
bool CDlgCategory::CheckFieldValid() 
{
	bool bOK = true;

	return bOK;
}
int CDlgCategory::BinAddData() 
{
	// Init value
	int iItem				= 0;
	int iSWNumber			= 0;
	long lColor				= 0;
	CString csCode			= _T("");
	CString csDescription	= _T("");
	int		iPF				= 0;	// Fail
	int		iHWNumber		= 0;

	// Item
	CString csItem = _T("");
	m_wndItem.GetWindowText( csItem );
	iItem = atoi( csItem );

	// PF
	CString csPF = _T("");
	m_wndPF.GetWindowText( csPF );
	iPF = atoi( csPF );

	// HW 
	CString csHW = _T("");
	m_wndHw.GetWindowText( csHW );
	iHWNumber = atoi( csHW );

	// Color 
	lColor = m_wndColor.GetSelectedColorValue();

	// Code 
	m_wndCode.GetWindowText( csCode );
	csCode.TrimLeft();
	csCode.TrimRight();
	
	// Description
	m_wndDescription.GetWindowText( csDescription );
	csDescription.TrimLeft();
	csDescription.TrimRight();

	// SW Number
	CString csSWNumber = _T("");
	m_wndSWNumber.GetWindowText( csSWNumber );
	csSWNumber.TrimLeft();
	csSWNumber.TrimRight();
	iSWNumber = atoi( csSWNumber );

	// Debug 
	CString csInfo = _T("");
	csInfo.Format("PF: %d, HW: %d, Color: %d, Code: %s, Desc: %s, SW: %d", 
		iPF, iHWNumber, lColor, csCode, csDescription, iSWNumber );
//	AfxMessageBox( csInfo );
	tagBinMapping m_BinDATA;
	m_BinDATA.code			= csCode;
	m_BinDATA.color			= lColor;
	m_BinDATA.description	= csDescription;
	iHWNumber--;
	m_BinDATA.hardware		= iHWNumber;	
	m_BinDATA.pass			= iPF == 1 ? true : false;
	m_BinDATA.software		= csSWNumber;

	BinMap.InsertAt(iItem, m_BinDATA );

	return iItem;
}
void CDlgCategory::ResetUIForAdd() 
{
	int iCount = m_listData.GetItemCount();
	if( iCount == 1 )
	{

	}
	else
	{
		BOOL bEnable = TRUE;
		GetDlgItem( IDC_F_DEL )->EnableWindow( bEnable );
	}
}
void CDlgCategory::OnFAdd() 
{
	if( !CheckFieldValid() )
		return;

	int col = BinAddData();	

	ShowData();

	ResetUIForAdd();

	m_fChange = true;
}
int CDlgCategory::BinDelData() 
{
	int nItem = -1;
	CString csItem = "";
	m_wndItem.GetWindowText( csItem );
	nItem = atoi( csItem );
	nItem--;

	//
	BinMap.RemoveAt( nItem );

	//
	return nItem;
}

void CDlgCategory::ResetUIForDelete() 
{
	// 如果最後一筆就 Disable Up, Down, Delete....
	int iCount = m_listData.GetItemCount();

	if( iCount == 1 )
	{
		// 表示最後一筆資料了, 不允許在刪除, 和 Up, Down.
		BOOL bEnable = FALSE;
		GetDlgItem( IDC_F_DEL )->EnableWindow( bEnable );
		GetDlgItem( IDC_F_UP )->EnableWindow( bEnable );
		GetDlgItem( IDC_F_DOWN )->EnableWindow( bEnable );
	}
}
void CDlgCategory::OnFDel() 
{
	int col = BinDelData();	

	ShowData();

	SetColumn( col );

	ResetUIForDelete();

	m_fChange = true;
}
void CDlgCategory::RetUI(int Item) 
{
	int iCount = m_listData.GetItemCount();
	
	if( iCount == 1 )
	{
		// 最後一筆了..
		BOOL bEnable = FALSE;
		GetDlgItem( IDC_F_DEL )->EnableWindow( bEnable );
		GetDlgItem( IDC_F_UP )->EnableWindow( bEnable );
		GetDlgItem( IDC_F_DOWN )->EnableWindow( bEnable );
	}
	else
	{
		// 還有兩筆以上
		if( Item == 0 )
		{
			GetDlgItem( IDC_F_UP )->EnableWindow( false );
			GetDlgItem( IDC_F_DOWN )->EnableWindow( true );
		}
		else if( Item == m_listData.GetItemCount() - 1 )
		{
			GetDlgItem( IDC_F_UP )->EnableWindow( true );
			GetDlgItem( IDC_F_DOWN )->EnableWindow( false );
		}
		else
		{
			GetDlgItem( IDC_F_UP )->EnableWindow( true );
			GetDlgItem( IDC_F_DOWN )->EnableWindow( true );		
		}
	}
}

int CDlgCategory::BinUpData()
{
	int nItem = -1;
	CString csItem = "";
	m_wndItem.GetWindowText( csItem );
	nItem = atoi( csItem );
	nItem--;	

	// Init value
	int iItem				= 0;
	int iSWNumber			= 0;
	long lColor				= 0;
	CString csCode			= _T("");
	CString csDescription	= _T("");
	int		iPF				= 0;	// Fail
	int		iHWNumber		= 0;

	// Change Data Order..
	int nnItem = -1;
	nnItem = nItem-1;

	// Get value from dialog
	iSWNumber				= atoi(	m_listData.GetItemText( nItem, 1 ) );	// SW Number
	lColor					= atoi(	m_listData.GetItemText( nItem, 2 ) );	// Color
	csCode					= m_listData.GetItemText( nItem, 3 );			// Code
	csDescription			= m_listData.GetItemText( nItem, 4 );			// Description
	iPF						= atoi(	m_listData.GetItemText( nItem, 5 ) );	// PF
	iHWNumber				= atoi(	m_listData.GetItemText( nItem, 6 ) );	// HW	

	// Up copy to Down
	tagBinMapping m_BinDATA;
	m_BinDATA.code			= m_listData.GetItemText( nnItem, 3 );			// Code
	m_BinDATA.color			= atoi(	m_listData.GetItemText( nnItem, 2 ) );	// Color
	m_BinDATA.description	= m_listData.GetItemText( nnItem, 4 );			// Description
	int iTempHW = atoi(	m_listData.GetItemText( nnItem, 6 ) );
	iTempHW--;
	m_BinDATA.hardware		= iTempHW;										// HW
	m_BinDATA.pass			= atoi(	m_listData.GetItemText( nnItem, 5 ) ) == 1 ? true : false;	// PF
	m_BinDATA.software		= m_listData.GetItemText( nnItem, 1 );						// SW Number
	BinMap.SetAt(nItem, m_BinDATA );

	// Down copy to Up
	tagBinMapping m_BinDATAOver;
	m_BinDATAOver.code			= csCode;
	m_BinDATAOver.color			= lColor;
	m_BinDATAOver.description	= csDescription;
	iHWNumber--;			
	m_BinDATAOver.hardware		= iHWNumber;
	m_BinDATAOver.pass			= iPF == 1 ? true : false;
	CString csTempSW = _T("");
	csTempSW.Format("%d", iSWNumber );
	m_BinDATAOver.software		= csTempSW;
	BinMap.SetAt(nnItem, m_BinDATAOver );

	//
	return nnItem;
}
int CDlgCategory::BinDownData()
{
	int nItem = -1;
	CString csItem = "";
	m_wndItem.GetWindowText( csItem );
	nItem = atoi( csItem );
	nItem--;
	
	// Init value
	int iItem				= 0;
	int iSWNumber			= 0;
	long lColor				= 0;
	CString csCode			= _T("");
	CString csDescription	= _T("");
	int		iPF				= 0;	// Fail
	int		iHWNumber		= 0;

	// Change Data Order..
	int nnItem = -1;
	nnItem = nItem+1;	

	// Get value from dialog
	iSWNumber				= atoi(	m_listData.GetItemText( nItem, 1 ) );	// SW Number
	lColor					= atoi(	m_listData.GetItemText( nItem, 2 ) );	// Color
	csCode					= m_listData.GetItemText( nItem, 3 );			// Code
	csDescription			= m_listData.GetItemText( nItem, 4 );			// Description
	iPF						= atoi(	m_listData.GetItemText( nItem, 5 ) );	// PF
	iHWNumber				= atoi(	m_listData.GetItemText( nItem, 6 ) );	// HW	

	// Down copy to Up
	tagBinMapping m_BinDATA;
	m_BinDATA.code			= m_listData.GetItemText( nnItem, 3 );			// Code
	m_BinDATA.color			= atoi(	m_listData.GetItemText( nnItem, 2 ) );	// Color
	m_BinDATA.description	= m_listData.GetItemText( nnItem, 4 );			// Description
	int iTempHW				= atoi(	m_listData.GetItemText( nnItem, 6 ) );
	iTempHW--;
	m_BinDATA.hardware		= iTempHW;
	m_BinDATA.pass			= atoi(	m_listData.GetItemText( nnItem, 5 ) ) == 1 ? true : false;
	m_BinDATA.software		= m_listData.GetItemText( nnItem, 1 );	// SW Number
	BinMap.SetAt(nItem, m_BinDATA );

	// Up copy to Down
	tagBinMapping m_BinDATAOver;
	m_BinDATAOver.code			= csCode;
	m_BinDATAOver.color			= lColor;
	m_BinDATAOver.description	= csDescription;
	iHWNumber--;			
	m_BinDATAOver.hardware		= iHWNumber;
	m_BinDATAOver.pass			= iPF == 1 ? true : false;
	CString csTempSW = _T("");
	csTempSW.Format("%d", iSWNumber );
	m_BinDATAOver.software		= csTempSW;
	BinMap.SetAt(nnItem, m_BinDATAOver );

	//
	return nnItem;
}
void CDlgCategory::OnFUp() 
{
	int col = BinUpData();

	// Debug
	CString csMsg = _T("");
	csMsg.Format("%d", col );
//	AfxMessageBox( csMsg );

	ShowData();

	SetColumn( col );

	RetUI( col );

	m_fChange = true;
}

void CDlgCategory::OnFDown() 
{
	int col = BinDownData();

	// Debug
	CString csMsg = _T("");
	csMsg.Format("%d", col );
//	AfxMessageBox( csMsg );

	ShowData();

	SetColumn( col );

	RetUI( col );

	m_fChange = true;
}
