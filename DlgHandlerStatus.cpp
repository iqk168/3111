// DlgHandlerStatus.cpp : implementation file
//

#include "stdafx.h"
#include "deer.h"
#include "DlgHandlerStatus.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgHandlerStatus dialog


CDlgHandlerStatus::CDlgHandlerStatus(CString csFile, CWnd* pParent /*=NULL*/)
	: CDialog(CDlgHandlerStatus::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgHandlerStatus)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	m_csFile = csFile;

	//
	m_iSel = 0;
}


void CDlgHandlerStatus::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgHandlerStatus)
	DDX_Control(pDX, IDOK,			m_btnOK);
	DDX_Control(pDX, IDCANCEL,		m_btnCancel);
	DDX_Control(pDX, IDC_DATA,		m_listData);
	DDX_Control(pDX, IDC_FILE,		m_wndFile);
	DDX_Control(pDX, IDC_TYPE,		m_btnType);
	DDX_Radio(pDX, IDC_TYPE,		m_iSel);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgHandlerStatus, CDialog)
	//{{AFX_MSG_MAP(CDlgHandlerStatus)
	ON_NOTIFY(LVN_GETDISPINFO, IDC_DATA, OnGetdispinfoData)
	ON_BN_CLICKED(IDC_TYPE,		OnType)
	ON_BN_CLICKED(IDC_TYPE2,	OnType2)
	ON_BN_CLICKED(IDC_TYPE3,	OnType3)
	ON_BN_CLICKED(IDC_TYPE4,	OnType4)
	ON_BN_CLICKED(IDC_TYPE5,	OnType5)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgHandlerStatus message handlers

BOOL CDlgHandlerStatus::PreTranslateMessage(MSG* pMsg) 
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

BOOL CDlgHandlerStatus::OnInitDialog() 
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
	LoadFile( m_csFile );

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

void CDlgHandlerStatus::LoadFile( CString csFileName  )
{
	// Clear Data
	m_HandlerStatusFileData.csDate.RemoveAll();
	m_HandlerStatusFileData.csDesc.RemoveAll();
	m_HandlerStatusFileData.csType.RemoveAll();

	//
	CString csFile;
	csFile = ".\\Log\\" + csFileName;

	CFile file;

	if(file.Open(csFile, CFile::modeRead | CFile::shareDenyNone, NULL) != 0)
	{			
		file.SeekToBegin();
		CArchive ar(&file, CArchive::load);
		CString cs;

		while(1)
		{
			BOOL bReadOK = ar.ReadString(cs);
			
			if( !bReadOK )
				break;

			CArray <CString, CString > m_Record;
			f.StringToIntArrayByToken(	cs, m_Record, ",");

			// date
			CString csData = _T("");
			csData.Format("%s", m_Record.GetAt(0) );
			m_HandlerStatusFileData.csDate.Add(csData);

			// type
			CString csType = _T("");
			csType.Format("%s", m_Record.GetAt(1) );
			m_HandlerStatusFileData.csType.Add( csType );

			// desc
			CString csDesc = _T("");
			csDesc.Format("%s", m_Record.GetAt(2) );
			m_HandlerStatusFileData.csDesc.Add(csDesc);
		}
		ar.Close();
		file.Close();
	}
}
void CDlgHandlerStatus::InitValue()	
{
	//
	m_btnType.SetCheck(1);

	//
	m_wndFile.SetWindowText( m_csFile );
}
void CDlgHandlerStatus::Style()
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
void CDlgHandlerStatus::ShowTitle()
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
		m_listData.InsertColumn(1, "日期");   
		m_listData.InsertColumn(2, "類別");
		m_listData.InsertColumn(3, "描述");
	}
	else
	{
		m_listData.InsertColumn(0, "Item");
		m_listData.InsertColumn(1, "Date");
		m_listData.InsertColumn(2, "Type");
		m_listData.InsertColumn(3, "Desc");
	}

	// 設定預設寬度
	m_listData.SetColumnWidth(0, 100);
	m_listData.SetColumnWidth(1, 150);
	m_listData.SetColumnWidth(2, 80);
	m_listData.SetColumnWidth(3, 400);

	theApp.DoWaitCursor(0);
}
int CDlgHandlerStatus::GetSel()
{
	int iSel = 0;

	return iSel;
}
void CDlgHandlerStatus::ShowData()
{
	//
	UpdateData();

	//Debug
//	CString ccc;
//	ccc.Format("Sel: %d", m_iSel );
//	AfxMessageBox( ccc );

	// 顯示資料
	theApp.DoWaitCursor(1);
	int iCount = 0;
	CString csTT = _T("");
	tagHandlerStatusReportLogItem Label;
	int iSize = m_HandlerStatusFileData.csDate.GetSize();
	for( int i = 0; i<iSize; i++)
	{
		csTT = Label.type	 	= m_HandlerStatusFileData.csType.GetAt(i);

		if( m_iSel == 0 )
		{
			// All
			iCount++;
			Label.item		= iCount;	// Item									
			Label.data 		= m_HandlerStatusFileData.csDate.GetAt(i);
			Label.type	 	= m_HandlerStatusFileData.csType.GetAt(i);
			Label.desc		= m_HandlerStatusFileData.csDesc.GetAt(i);

			m_Source.SetAtGrow(iCount-1, Label);	
		}
		else if( m_iSel == 1 )
		{
			// Arm 
			if( csTT.Find( "Arm", 0 ) >-1 )
			{
				iCount++;
				Label.item		= iCount;	// Item									
				Label.data 		= m_HandlerStatusFileData.csDate.GetAt(i);
				Label.type	 	= m_HandlerStatusFileData.csType.GetAt(i);
				Label.desc		= m_HandlerStatusFileData.csDesc.GetAt(i);

				m_Source.SetAtGrow(iCount-1, Label);	
			}
		}	
		else if( m_iSel == 2 )
		{
			// Tester
			if( csTT.Find( "Tester", 0 ) >-1 )
			{
				iCount++;
				Label.item		= iCount;	// Item									
				Label.data 		= m_HandlerStatusFileData.csDate.GetAt(i);
				Label.type	 	= m_HandlerStatusFileData.csType.GetAt(i);
				Label.desc		= m_HandlerStatusFileData.csDesc.GetAt(i);

				m_Source.SetAtGrow(iCount-1, Label);	
			}
		}
		else if( m_iSel == 3 )
		{
			// Ts
			if( csTT.Find( "Ts", 0 ) >-1 )
			{
				iCount++;
				Label.item		= iCount;	// Item									
				Label.data 		= m_HandlerStatusFileData.csDate.GetAt(i);
				Label.type	 	= m_HandlerStatusFileData.csType.GetAt(i);
				Label.desc		= m_HandlerStatusFileData.csDesc.GetAt(i);

				m_Source.SetAtGrow(iCount-1, Label);	
			}
		}
		else if( m_iSel == 4 )
		{
			// Ts
			if( csTT.Find( "Manual", 0 ) >-1 )
			{
				iCount++;
				Label.item		= iCount;	// Item									
				Label.data 		= m_HandlerStatusFileData.csDate.GetAt(i);
				Label.type	 	= m_HandlerStatusFileData.csType.GetAt(i);
				Label.desc		= m_HandlerStatusFileData.csDesc.GetAt(i);

				m_Source.SetAtGrow(iCount-1, Label);	
			}
		}
	}

	// 更新資料
	m_listData.SetItemCountEx(iCount);
	m_listData.Invalidate();

	theApp.DoWaitCursor(0);
}
void CDlgHandlerStatus::OnOK() 
{
	
	CDialog::OnOK();
}

void CDlgHandlerStatus::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

void CDlgHandlerStatus::OnGetdispinfoData(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LV_DISPINFO* pDispInfo = (LV_DISPINFO*)pNMHDR;
	LV_ITEM* pItem= &(pDispInfo)->item;
	tagHandlerStatusReportLogItem rLabel = m_Source.ElementAt(pItem->iItem);

	if (pItem->mask & LVIF_TEXT) //valid text buffer?
	{
		// then display the appropriate column
		switch(pItem->iSubItem)
		{
		case 0:
			sprintf(pItem->pszText, "%d",		rLabel.item );		// 	
			break;
		case 1:
			sprintf(pItem->pszText, "%s",		rLabel.data );		// 
			break;
		case 2:
			sprintf(pItem->pszText, "%s",		rLabel.type );		// 
			break;
		case 3:
			sprintf(pItem->pszText, "%s",		rLabel.desc );		// 
			break;
		default:
			ASSERT(0);
			break;
		}
	}			
	*pResult = 0;
}

void CDlgHandlerStatus::OnType() 
{
	ShowData();
}
void CDlgHandlerStatus::OnType2() 
{
	ShowData();
}
void CDlgHandlerStatus::OnType3() 
{
	ShowData();
}
void CDlgHandlerStatus::OnType4() 
{
	ShowData();
}

void CDlgHandlerStatus::OnType5() 
{
	ShowData();	
}
