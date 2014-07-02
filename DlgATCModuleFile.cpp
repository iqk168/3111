// DlgATCModuleFile.cpp : implementation file
//

#include "stdafx.h"
#include "deer.h"
#include "DlgATCModuleFile.h"
#include "DlgATCModuleNew.h"
#include "DlgATCModuleSetting.h"
#include "DlgATCModuleModify.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgATCModuleFile dialog


CDlgATCModuleFile::CDlgATCModuleFile(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgATCModuleFile::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgATCModuleFile)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgATCModuleFile::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgATCModuleFile)
	DDX_Control(pDX, IDC_FILE,			m_wndFile);
	DDX_Control(pDX, IDC_FILE_COUNT,	m_wndFileCount);
	DDX_Control(pDX, IDC_SET,			m_btnSetFile);
	DDX_Control(pDX, IDC_DEL,			m_btnDelete);
	DDX_Control(pDX, IDC_DATA,			m_listData);
	DDX_Control(pDX, IDC_F_SETTING,		m_btnSetting);
	DDX_Control(pDX, IDC_F_NEW,			m_btnNew);
	DDX_Control(pDX, IDOK,				m_btnOK);
	DDX_Control(pDX, IDCANCEL,			m_btnCancel);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgATCModuleFile, CDialog)
	//{{AFX_MSG_MAP(CDlgATCModuleFile)
	ON_WM_SHOWWINDOW()
	ON_NOTIFY(NM_CLICK, IDC_DATA,			OnClickData)
	ON_BN_CLICKED(IDC_F_NEW,				OnFNew)
	ON_BN_CLICKED(IDC_F_SETTING,			OnFSetting)
	ON_BN_CLICKED(IDC_DEL,					OnDel)
	ON_BN_CLICKED(IDC_SET,					OnSet)
	ON_NOTIFY(LVN_GETDISPINFO, IDC_DATA,	OnGetdispinfoData)
	ON_NOTIFY(NM_DBLCLK, IDC_DATA,			OnDblclkData)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgATCModuleFile message handlers

BOOL CDlgATCModuleFile::PreTranslateMessage(MSG* pMsg) 
{
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

BOOL CDlgATCModuleFile::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m.Info.bSubDlgOpen = true;
	f.UpdateButtonState();

	// init button 
	m_btnOK.SetIcon(IDI_OK);
	m_btnOK.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnOK.SetFlat(FALSE);
	
	m_btnCancel.SetIcon(IDI_CANCEL);
	m_btnCancel.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnCancel.SetFlat(FALSE);

	m_btnNew.SetIcon(IDI_NEW);
	m_btnNew.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnNew.SetFlat(FALSE);	

	m_btnSetting.SetIcon(IDI_MULTI_STRING);
	m_btnSetting.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnSetting.SetFlat(FALSE);

	m_btnDelete.SetIcon(IDI_DELETE);
	m_btnDelete.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnDelete.SetFlat(FALSE);

	m_btnSetFile.SetIcon(IDI_SET_FILE);
	m_btnSetFile.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnSetFile.SetFlat(FALSE);

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
void CDlgATCModuleFile::Style()
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
void CDlgATCModuleFile::ShowTitle()
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
void CDlgATCModuleFile::ShowData()
{
	// 顯示資料
	theApp.DoWaitCursor(1);
	int iCount = 0;
	tagATCFileItem Label;

	CFileFind find;	
	BOOL bResult = find.FindFile( m.FilePath.AtcModuleSettingPath + _Atc1 );	
	CString file = _T("");
	while(bResult)
	{
		bResult = find.FindNextFile();
		file = find.GetFileName();	// Get File Name..
		if(file.Find( _Atc2, 0)>-1)
		{
			// find file success...
			iCount++;
			Label.item = iCount;
			CString csFileName = _T("");
			csFileName = file.Left(file.Find( _Atc2, 0));
			Label.filename = csFileName;

			// show file data
			CString csfile_status;
			csfile_status.Format("%s", m.FilePath.AtcModuleSettingPath + file );
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
	CString csCount = _T("");
	csCount.Format("ATC File Count: %d", iCount );
	m_wndFileCount.SetWindowText( csCount );
}
void CDlgATCModuleFile::InitValue()
{
	SetUsingFile();
}
void CDlgATCModuleFile::SetUsingFile()
{
	CString csUseFileName = _T("");
	csUseFileName = m.UI.ATCModuleMultiSV;
	csUseFileName = csUseFileName.Left(csUseFileName.Find( _Atc2, 0));
	m_wndFile.SetWindowText( csUseFileName );
}
void CDlgATCModuleFile::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);

}
void CDlgATCModuleFile::OnClickData(NMHDR* pNMHDR, LRESULT* pResult) 
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

void CDlgATCModuleFile::OnOK() 
{
	m.Info.bSubDlgOpen = false;
	f.UpdateButtonState();
	
	CDialog::OnOK();
}

void CDlgATCModuleFile::OnCancel() 
{
	m.Info.bSubDlgOpen = false;
	f.UpdateButtonState();

	CDialog::OnCancel();
}

void CDlgATCModuleFile::OnFNew() 
{
	// Make Sure. User Already select a file
	POSITION pos = m_listData.GetFirstSelectedItemPosition();
	if (pos == NULL || csFile == "" )
	{
		AfxMessageBox("Please Select File First.");
		return;
	}

	CDlgATCModuleNew dlg( csFile );
	dlg.DoModal();

	// Updata File List
	ShowData();
}

void CDlgATCModuleFile::OnFSetting() 
{
	// Make Sure. User Already select a file
	POSITION pos = m_listData.GetFirstSelectedItemPosition();
	if (pos == NULL || csFile == "" )
	{
		AfxMessageBox("Please Select File First.");
		return;
	}

	CDlgATCModuleSetting dlg( csFile );
	dlg.DoModal();
}

void CDlgATCModuleFile::OnDel() 
{
	// Make Sure. User Already select a file
	POSITION pos = m_listData.GetFirstSelectedItemPosition();
	if (pos == NULL || csFile == "" )
	{
		AfxMessageBox("Please Select File First.");
		return;
	}

	CString csMsg = _T("");
	csMsg.Format("Do you really want to delete [%s]. Delete?\n", csFile);
	if(IDYES != AfxMessageBox(csMsg, MB_YESNO|MB_ICONEXCLAMATION))
	{
		// No delete
	}
	else
	{
		if(!::DeleteFile( m.FilePath.AtcModuleSettingPath + csFile + _AtcDelete ))
		{

		}

		if(!::CopyFile( m.FilePath.AtcModuleSettingPath + csFile + _Atc2, 
			m.FilePath.AtcModuleSettingPath + csFile + _AtcDelete, TRUE ))
		{
			CString csMsg = _T("");
			csMsg.Format("Backup File Fail.!");
			AfxMessageBox( csMsg );
		}

		if(!::DeleteFile( m.FilePath.AtcModuleSettingPath + csFile + _Atc2 ))
		{
			CString csMsg = _T("");
			csMsg.Format("Delete File Fail.!");
			AfxMessageBox( csMsg );
		}
	}

	// Updata File List
	ShowData();
}

void CDlgATCModuleFile::OnSet() 
{
//	m.UI.ATCModuleMultiSV
	
	// Check Lot Done First....
	if( !f.CheckEnaleChange() )
		return;

	// Make Sure. User Already select a file
	POSITION pos = m_listData.GetFirstSelectedItemPosition();
	if (pos == NULL || csFile == "" )
	{
		AfxMessageBox("Please Select File First.");
		return;
	}

	CString csMsg;
	csMsg.Format("Do you really want to set ATC multi sv file [%s] File?\n", csFile );
	if(IDYES != AfxMessageBox(csMsg,
		MB_YESNO|MB_ICONEXCLAMATION))
	{
		return;
	}
	else
	{
		m.UI.ATCModuleMultiSV = csFile + _Atc2;
		f.SaveATCModuleMultiSVFile();
	}

	// Set Now Using File
	SetUsingFile();	

	// ReLoad the File
//	f.LoadChamberMultiSVSettingFile();
}

void CDlgATCModuleFile::OnGetdispinfoData(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LV_DISPINFO* pDispInfo = (LV_DISPINFO*)pNMHDR;
	LV_ITEM* pItem= &(pDispInfo)->item;
	tagATCFileItem rLabel = m_Source.ElementAt(pItem->iItem);

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

void CDlgATCModuleFile::OnDblclkData(NMHDR* pNMHDR, LRESULT* pResult) 
{
	CDlgATCModuleModify dlg( csFile );
	dlg.DoModal();
	
	*pResult = 0;
}
