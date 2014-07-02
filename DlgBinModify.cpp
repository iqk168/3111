// DlgBinModify.cpp : implementation file
//

#include "stdafx.h"
#include "deer.h"
#include "DlgBinModify.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgBinModify dialog


CDlgBinModify::CDlgBinModify(CString TempFileName,
		CArray <tagBinMapping, tagBinMapping> *BinMap,
		CWnd* pParent /*=NULL*/)
	: CDialog(CDlgBinModify::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgBinModify)
	m_SourceBinMap = BinMap;
	m_BinMap.Copy(*BinMap);
	
	m_TempFileName = TempFileName;
	//}}AFX_DATA_INIT
}


void CDlgBinModify::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgBinModify)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
	DDX_Control(pDX, IDOK, m_btnOK);
	DDX_Control(pDX, IDCANCEL, m_btnCancel);

	DDX_Control(pDX, IDC_SAVE, m_btnSave);
	DDX_Control(pDX, IDC_INSERT, m_btnInsert);
	DDX_Control(pDX, IDC_DELETE, m_btnDelete);

	DDX_Control(pDX, IDC_DATA, m_Grid);             // associate the grid window with a C++ object
}


BEGIN_MESSAGE_MAP(CDlgBinModify, CDialog)
	//{{AFX_MSG_MAP(CDlgBinModify)
	ON_BN_CLICKED(IDC_INSERT, OnInsert)
	ON_BN_CLICKED(IDC_SAVE, OnSave)
	ON_BN_CLICKED(IDC_DELETE, OnDelete)
	ON_WM_CLOSE()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgBinModify message handlers

void CDlgBinModify::OnOK() 
{
	
	CDialog::OnOK();
}

void CDlgBinModify::OnCancel() 
{
	
	CDialog::OnCancel();
}

void CDlgBinModify::OnInsert() 
{
	m_Grid.InsertRow("");	
	m_Grid.Invalidate();
}

void CDlgBinModify::OnSave() 
{
	CFile file;
	CString cs;

	m_BinMap.RemoveAll();

	tagBinMapping BinMap;
	for(int i=1; i<m_Grid.GetRowCount(); i++)
	{
		if(m_Grid.GetItemText(i, 1) != _T(""))
		{	
//			BinMap.software		= atoi(m_Grid.GetItemText(i, 0));					// Note : SW Bin
			cs.Format("%d", i - 1);
			BinMap.software		= cs;
			BinMap.code			= m_Grid.GetItemText(i, 1);							// Note : Code
			BinMap.description	= m_Grid.GetItemText(i, 2);							// Note : Desc
			BinMap.pass			= m_Grid.GetItemText(i, 3) == "0" ? false : true;	// Note : Pass/Fail
			BinMap.color  		= atoi(m_Grid.GetItemText(i, 4));					// Note : Color
			BinMap.hardware		= atoi(m_Grid.GetItemText(i, 5));					// Note : HW Bin
			m_BinMap.Add(BinMap);
		}
	}

	m_SourceBinMap->Copy(m_BinMap);

	UpdateView();
}

void CDlgBinModify::OnDelete() 
{
	// 如果 Bin Mapping 數量為 0 就返回
	if(m_BinMap.GetSize() == 0)
		return;

	CCellRange r = m_Grid.GetSelectedCellRange();	
	
	CArray <int, int> iDeleteItem;
	int iDeleteCounter = 0;

	// 先記錄要被刪除的 Row
	for(int i=r.GetMinRow(); i<=r.GetMaxRow(); i++)
		if(m_Grid.IsCellSelected(i,0) || m_Grid.IsCellSelected(i,1)
			|| m_Grid.IsCellSelected(i,2) || m_Grid.IsCellSelected(i,3)
			|| m_Grid.IsCellSelected(i,4))
		{
			iDeleteItem.Add(i);
			iDeleteCounter++;
		}

	// 逐一刪除所選取的資料 (-k 只為了刪除後的順序會變化,而做的一個 Shift).
	for(int j=0, k=0;j<iDeleteCounter;j++, k++)
	{
		m_Grid.DeleteRow(iDeleteItem.ElementAt(j)-k);
		m_BinMap.RemoveAt(iDeleteItem.ElementAt(j)-1-k);
	}

	m_Grid.Invalidate();
	UpdateView();
}

BOOL CDlgBinModify::PreTranslateMessage(MSG* pMsg) 
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

void CDlgBinModify::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	
	CDialog::OnClose();
}

void CDlgBinModify::OnDestroy() 
{
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here
	
}

BOOL CDlgBinModify::OnInitDialog() 
{
	CDialog::OnInitDialog();

	
	// init button 
	m_btnOK.SetIcon(IDI_OK);;
	m_btnOK.SetAlign(CButtonST::ST_ALIGN_VERT);;
	m_btnOK.SetFlat(FALSE);

	m_btnCancel.SetIcon(IDI_CANCEL);;
	m_btnCancel.SetAlign(CButtonST::ST_ALIGN_VERT);;
	m_btnCancel.SetFlat(FALSE);

	m_btnSave.SetIcon(IDI_SAVE);
	m_btnSave.SetAlign(CButtonST::ST_ALIGN_HORIZ);

	m_btnDelete.SetIcon(IDI_DELETE);
	m_btnDelete.SetAlign(CButtonST::ST_ALIGN_HORIZ);

	m_btnInsert.SetIcon(IDI_NEW);
	m_btnInsert.SetAlign(CButtonST::ST_ALIGN_HORIZ);

	m_Grid.SetHeaderSort(TRUE);
	
	LoadBinMapping( m_TempFileName );

	UpdateView();

	f.ChangeLanguage(GetSafeHwnd());

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CDlgBinModify::UpdateView()
{
	m_Grid.DeleteAllItems();

	m_Grid.InsertColumn("SW Bin");
	m_Grid.InsertColumn("Code");
	m_Grid.InsertColumn("Description");
	m_Grid.InsertColumn("Pass/Fail");
	m_Grid.InsertColumn("Color");
	m_Grid.InsertColumn("HW Bin");
	m_Grid.SetFixedRowCount(1);
		
	tagBinMapping BinMap;
	CString cs;
	for(int i=0; i<m_BinMap.GetSize(); i++)
	{
		BinMap = m_BinMap.GetAt(i);
		m_Grid.InsertRow("");
//		cs.Format("%d", m.BinMap.GetAt(i).software);
		m_Grid.SetItemText(i+1, 0, BinMap.software );				// Note : SW Bin		
		m_Grid.SetItemText(i+1, 1, BinMap.code);					// Note : Code
		m_Grid.SetItemText(i+1, 2, BinMap.description );			// Note : Desc
		m_Grid.SetItemText(i+1, 3, BinMap.pass == 0 ? "0" : "1");	// Note : Pass/Fail
		cs.Format("%d", BinMap.color );
		m_Grid.SetItemText(i+1, 4, cs );							// Note : Color		
		cs.Format("%d", BinMap.hardware );							// Note : HW Bin
		m_Grid.SetItemText(i+1, 5, cs);	
		
	}
	
	m_Grid.AutoSize();
	m_Grid.SetSortColumn(0);

}

void CDlgBinModify::LoadBinMapping(CString file)
{
	// Update m_BinMap for modify
	CArray<CString, CString> array;
	f.ReadBinMappingFile( file , array);

	m_BinMap.RemoveAll();
	tagBinMapping bin;

	// 6 is item count 

	// 0 is software
	// 1 is code
	// 2 is description
	// 3 is pass ( 0 or 1)
	// 4 is color
	// 5 is Bin
	// Note : So, 0 - 4 have 5 items
	// Note : Please check *.mapping.

	for(int i=1; i<array.GetSize() / 6; i++)
	{
//		if(atoi(array[i*6+1].GetBuffer(0)) != 1)	//
		{
			bin.software = array[i*6+0];
			bin.code = array[i*6+1];
			bin.description = array[i*6+2];
			bin.pass = array[i*6+3] == "1" ? true : false;
			bin.color = atoi(array[i*6+4]);
			bin.hardware = atoi(array[i*6+5]);
			m_BinMap.Add(bin);
		}	
	}
}