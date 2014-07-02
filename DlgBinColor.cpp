// DlgBinColor.cpp : implementation file
//

#include "stdafx.h"
#include "deer.h"
#include "DlgBinColor.h"

//
#include "ColorListCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgBinColor dialog


CDlgBinColor::CDlgBinColor(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgBinColor::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgBinColor)
	//}}AFX_DATA_INIT

	m_iItem = -1;
}


void CDlgBinColor::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgBinColor)
	DDX_Control(pDX, IDC_COLOR,		m_wndColor);
	DDX_Control(pDX, IDC_E_B,		m_wndB);
	DDX_Control(pDX, IDC_E_G,		m_wndG);
	DDX_Control(pDX, IDC_E_R,		m_wndR);
	DDX_Control(pDX, IDC_SLIDER_B,	m_SilB);
	DDX_Control(pDX, IDC_SLIDER_G,	m_SilG);
	DDX_Control(pDX, IDC_SLIDER_R,	m_SilR);
	DDX_Control(pDX, IDC_DATA,		m_listData);
	DDX_Control(pDX, IDOK,			m_btnOK);
	DDX_Control(pDX, IDCANCEL,		m_btnCancel);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgBinColor, CDialog)
	//{{AFX_MSG_MAP(CDlgBinColor)
	ON_NOTIFY(LVN_GETDISPINFO, IDC_DATA,	OnGetdispinfoData)
	ON_NOTIFY(NM_CLICK, IDC_DATA,			OnClickData)
	ON_NOTIFY(NM_OUTOFMEMORY, IDC_SLIDER_R, OnOutofmemorySliderR)
	ON_NOTIFY(NM_OUTOFMEMORY, IDC_SLIDER_G, OnOutofmemorySliderG)
	ON_NOTIFY(NM_OUTOFMEMORY, IDC_SLIDER_B, OnOutofmemorySliderB)
	ON_WM_HSCROLL()
	ON_BN_CLICKED(IDC_C_ADD,				OnCAdd)
	ON_BN_CLICKED(IDC_C_SAVE,				OnCSave)
	ON_BN_CLICKED(IDC_C_DEL,				OnCDel)
	ON_BN_CLICKED(IDC_COLOR, OnColor)
	ON_WM_SHOWWINDOW()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgBinColor message handlers

void CDlgBinColor::OnOK() 
{
	SaveData();

	CDialog::OnOK();
}

void CDlgBinColor::OnCancel() 
{
	
	CDialog::OnCancel();
}

BOOL CDlgBinColor::PreTranslateMessage(MSG* pMsg) 
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

BOOL CDlgBinColor::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// init button 
	m_btnOK.SetIcon(IDI_SAVE);;
	m_btnOK.SetAlign(CButtonST::ST_ALIGN_VERT);;
	m_btnOK.SetFlat(FALSE);
	
	m_btnCancel.SetIcon(IDI_CANCEL);
	m_btnCancel.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnCancel.SetFlat(FALSE);	

	//
	InitColorSilder();	

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

void CDlgBinColor::InitValue()
{	
	m_BinColorItem.RemoveAll();
	m_BinColorItem.Copy( m.BinColorItem );

	// 
	m_iItem = -1;
}
void CDlgBinColor::InitColorSilder()
{
	//
	m_SilR.SetRange( 0, 255, FALSE );
	m_SilG.SetRange( 0, 255, FALSE );
	m_SilB.SetRange( 0, 255, FALSE );

	//
	int iR = 128;
	m_SilR.SetPos( iR );
	int iG = 128;
	m_SilG.SetPos( iG );
	int iB = 128;
	m_SilB.SetPos( iB );

	//
	iR = m_SilR.GetPos();
	iG = m_SilG.GetPos();
	iB = m_SilB.GetPos();

	CString csR = _T("");
	CString csG = _T("");
	CString csB = _T("");

	csR.Format("%d", iR );
	m_wndR.SetWindowText( csR );

	csG.Format("%d", iG );
	m_wndG.SetWindowText( csG );

	csB.Format("%d", iB );
	m_wndB.SetWindowText( csB );

	//
	COLORREF RCOLOR = RGB( iR, iG, iB );
	m_wndColor.SetNewBkColor( RCOLOR );
}
void CDlgBinColor::SetColorSilderValue(int iColor)
{
	int Blue;
	int Green;
	int Red;

	ParseColor( iColor, Red, Green, Blue );

	int iR = Red;
	m_SilR.SetPos( iR );
	int iG = Green;
	m_SilG.SetPos( iG );
	int iB = Blue;
	m_SilB.SetPos( iB );

	CString csR = _T("");
	CString csG = _T("");
	CString csB = _T("");

	csR.Format("%d", iR );
	m_wndR.SetWindowText( csR );

	csG.Format("%d", iG );
	m_wndG.SetWindowText( csG );

	csB.Format("%d", iB );
	m_wndB.SetWindowText( csB );

	//	
	COLORREF RCOLOR = RGB( iB, iG, iR );
	m_wndColor.SetNewBkColor( RCOLOR );	
}
int CDlgBinColor::GetColorSilderValue()
{
	int iColor = 0;

	//
	int iR = m_SilR.GetPos();
	int iG = m_SilG.GetPos();
	int iB = m_SilB.GetPos();

	CString csR = _T("");
	CString csG = _T("");
	CString csB = _T("");

	csR.Format("%d", iR );
	m_wndR.SetWindowText( csR );

	csG.Format("%d", iG );
	m_wndG.SetWindowText( csG );

	csB.Format("%d", iB );
	m_wndB.SetWindowText( csB );

	//
	COLORREF RCOLOR = RGB( iB, iG, iR );
	m_wndColor.SetNewBkColor( RCOLOR );

	//
	iColor = RCOLOR;

	return iColor;
}
void CDlgBinColor::ShowTitle()
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
		m_listData.InsertColumn(1, "顏色"); 
	}
	else
	{
		m_listData.InsertColumn(0, "Item");  
		m_listData.InsertColumn(1, "Color"); 
	}

	// 設定預設寬度
	m_listData.SetColumnWidth(0, 50);
	m_listData.SetColumnWidth(1, 450);

	theApp.DoWaitCursor(0);
}
void CDlgBinColor::ShowData()
{
	// 顯示資料
	theApp.DoWaitCursor(1);

	//
	m_listData.ResetColors();

	int iCount = 0;
	tagBinColorFileItem Label;

	int iSize = 0;
	iSize = m_BinColorItem.GetSize();
	for(int i=0;i<iSize;i++)
	{
		iCount++;
		Label.item			= m_BinColorItem.GetAt(i).item;
		Label.color 		= m_BinColorItem.GetAt(i).color;
		m_listData.SetCellColor( m_BinColorItem.GetAt(i).color, i, 1);
		m_Source.SetAtGrow(iCount-1, Label);
	}

	// 更新資料
	m_listData.SetItemCountEx(iCount);
	m_listData.Invalidate();

	theApp.DoWaitCursor(0);
}
void CDlgBinColor::Style()
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

void CDlgBinColor::OnGetdispinfoData(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LV_DISPINFO* pDispInfo = (LV_DISPINFO*)pNMHDR;
	LV_ITEM* pItem= &(pDispInfo)->item;
	tagBinColorFileItem rLabel = m_Source.ElementAt(pItem->iItem);

	if (pItem->mask & LVIF_TEXT) //valid text buffer?
	{
		// then display the appropriate column
		switch(pItem->iSubItem)
		{
		case 0:
			sprintf(pItem->pszText, "%d",	rLabel.item );			
			break;
		case 1:
			sprintf(pItem->pszText, "%d",	rLabel.color );		
			break;
		default:
			ASSERT(0);
			break;
		}
	}		

	*pResult = 0;
}
void CDlgBinColor::GetColumnDATA(int nItem)
{
	long lColor = 0;
	lColor = atoi(	m_listData.GetItemText( nItem, 1 ) );	// Color

	SetColorSilderValue( lColor );
}
void CDlgBinColor::OnClickData(NMHDR* pNMHDR, LRESULT* pResult) 
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
	m_iItem = nItem;

	*pResult = 0;
}
void CDlgBinColor::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// TODO: Add your message handler code here and/or call default
	// We catch ON_WM_HSCROLL Event from Windows operaton system.
	GetColorSilderValue();

	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}
void CDlgBinColor::OnOutofmemorySliderR(NMHDR* pNMHDR, LRESULT* pResult) 
{
	*pResult = 0;
}

void CDlgBinColor::OnOutofmemorySliderG(NMHDR* pNMHDR, LRESULT* pResult) 
{	
	*pResult = 0;
}

void CDlgBinColor::OnOutofmemorySliderB(NMHDR* pNMHDR, LRESULT* pResult) 
{
	GetColorSilderValue();
	
	*pResult = 0;
}
void CDlgBinColor::ColorAdd()
{
	int iColor = GetColorSilderValue();	
	
	//
	tagBinColor m_Color;
	int iSize = m_BinColorItem.GetSize();
	m_Color.color = iColor;
	m_Color.item = iSize++;

	m_BinColorItem.Add( m_Color );

	//
	ShowData();
}
//
void CDlgBinColor::ColorSave()
{
	if( m_iItem < 0 )
	{
		CString csMsg = _T("");
		csMsg.Format("Please select item first.!");
		AfxMessageBox( csMsg ); 
		return;
	}

	//
	int iR = m_SilR.GetPos();
	int iG = m_SilG.GetPos();
	int iB = m_SilB.GetPos();
	
	tagBinColor m_Color;
	COLORREF RCOLOR = RGB( iB, iG, iR );

	m_Color.item = m_iItem;
	m_Color.color = RCOLOR;

	int n = m_iItem;
	m_BinColorItem.SetAt(n, m_Color );

	//
	ShowData();
}
void CDlgBinColor::ColorDel()
{
	int n = m_iItem;

	int iSize = m_listData.GetItemCount();
	if( n < 0 || n > iSize || n == iSize )
	{
		CString csMsg = _T("");
		csMsg.Format("Please select first");
		AfxMessageBox( csMsg );
		return;
	}
	else if( iSize == 1 )
	{
		CString csMsg = _T("");
		csMsg.Format("It is the last one");
		AfxMessageBox( csMsg );
		return;
	}

	m_BinColorItem.RemoveAt( n );

	//
	ShowData();
}
void CDlgBinColor::SaveData()
{
	m.BinColorItem.Copy( m_BinColorItem );

	f.SaveBinColor();

	//
	f.LoadBinColor();
}
void CDlgBinColor::OnCAdd() 
{
	ColorAdd();
}
void CDlgBinColor::OnCSave() 
{
	ColorSave();
}
void CDlgBinColor::OnCDel() 
{
	ColorDel();
}
void CDlgBinColor::ParseColor(int Color, int &R, int &G, int &B)
{
	int Blue	=	Color & 255;
	int Green	=	(Color >> 8) & 255;
	int Red		=   (Color >> 16) & 255;

	R = Red;
	G = Green;
	B = Blue;
}
void CDlgBinColor::OnColor() 
{
	int iColor = m_wndColor.GetBkColor();

	int R, G, B;
	ParseColor( iColor, R, G, B );

	//
	CString csColor = _T("");
	csColor.Format("%d, [%d, %d, %d]", iColor, R, G, B );
	AfxMessageBox( csColor );
}

void CDlgBinColor::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);	
}
