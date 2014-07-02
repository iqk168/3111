// DlgBinMapping.cpp : implementation file
//

#include "stdafx.h"
#include "deer.h"
#include "DlgBinMapping.h"

// Dlg
#include "DlgBinNew.h"
#include "DlgBinModify.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgBinMapping dialog


CDlgBinMapping::CDlgBinMapping(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgBinMapping::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgBinMapping)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgBinMapping::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgBinMapping)
	DDX_Control(pDX, IDC_SELECT_FILE, m_wndFile);
	DDX_Control(pDX, IDC_FILE_LIST, m_bxFile);
	DDX_Control(pDX, IDC_BIN_LIST, m_listBin);

	DDX_Control(pDX, IDC_MAPPING_BASEFILE, m_wndMappingBase);
	DDX_Control(pDX, IDC_DELETE, m_btnDelete);
	DDX_Control(pDX, IDC_NEW, m_btnNew);
	DDX_Control(pDX, IDC_SET_AS_BASE_FILE, m_btnSetBase);
	
	DDX_Control(pDX, IDC_MODIFY_PARAMETER, m_btnModify);
	DDX_Control(pDX, IDCANCEL, m_btnCancel);
	DDX_Control(pDX, IDOK, m_btnOK);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgBinMapping, CDialog)
	//{{AFX_MSG_MAP(CDlgBinMapping)
	ON_WM_DESTROY()
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_MODIFY_PARAMETER, OnModifyParameter)
	ON_BN_CLICKED(IDC_SET_AS_BASE_FILE, OnSetAsBaseFile)
	ON_BN_CLICKED(IDC_NEW, OnNew)
	ON_BN_CLICKED(IDC_DELETE, OnDelete)

	ON_LBN_DBLCLK(IDC_FILE_LIST, OnSelect)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgBinMapping message handlers

void CDlgBinMapping::OnDestroy() 
{
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here
	
}

void CDlgBinMapping::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	
	CDialog::OnClose();
}

BOOL CDlgBinMapping::OnInitDialog() 
{
	CDialog::OnInitDialog();

	
	// init button 
	m_btnDelete.SetIcon(IDI_DELETE);
	m_btnDelete.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnDelete.SetFlat(FALSE);
	
	m_btnModify.SetIcon(IDI_SAVE);
	m_btnModify.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnModify.SetFlat(FALSE);

	m_btnOK.SetIcon(IDI_OK);;
	m_btnOK.SetAlign(CButtonST::ST_ALIGN_VERT);;
	m_btnOK.SetFlat(FALSE);

	m_btnSetBase.SetIcon(IDI_BASEFILE);
	m_btnSetBase.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnSetBase.SetFlat(FALSE);
	
	m_btnNew.SetIcon(IDI_NEW);
	m_btnNew.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnNew.SetFlat(FALSE);

	m_btnCancel.SetIcon(IDI_CANCEL);
	m_btnCancel.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnCancel.SetFlat(FALSE);
	
	m_listBin.InsertColumn(0, "SW Bin");
	m_listBin.InsertColumn(1, "Code");
	m_listBin.InsertColumn(2, "Description");
	m_listBin.InsertColumn(3, "Pass/Fail");
	m_listBin.InsertColumn(4, "Color");
	m_listBin.InsertColumn(5, "HW Bin");

	m_listBin.SetColumnWidth(0, 100);
	m_listBin.SetColumnWidth(1, 160);
	m_listBin.SetColumnWidth(2, 280);
	m_listBin.SetColumnWidth(3, 80);
	m_listBin.SetColumnWidth(4, 80);
	m_listBin.SetColumnWidth(5, 80);

	UpdateFileList();
	m_wndFile.SetWindowText(m.UI.FileMainMapping );
	// Note : Display now using mapping file

	m_wndMappingBase.SetWindowText( m.UI.FileMainBaseMapping );
	// Note : Display now Base mapping file.

	m_BinMap.Copy(m.BinMap);
	// Note : Default point Dlg Bin is Using Bin Map	

	ResetMappingList();

	m.Info.bSubDlgOpen = true;
	f.UpdateButtonState();
	// disable all button until dialog clsoe

	f.ChangeLanguage(GetSafeHwnd());

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgBinMapping::OnOK() 
{
	m.Info.bSubDlgOpen = false;
	f.UpdateButtonState();

	CDialog::OnOK();
}

void CDlgBinMapping::OnCancel() 
{
	m.Info.bSubDlgOpen = false;
	f.UpdateButtonState();

	CDialog::OnCancel();
}

void CDlgBinMapping::OnModifyParameter() 
{
	if( !f.CheckEnaleChange() )
		return;

	CString csFile;
	m_wndFile.GetWindowText( csFile );

	CDlgBinModify dlg( m.FilePath.CategoryPath  + csFile, &m_BinMap);
	dlg.DoModal();

	ResetMappingList();

	bool ok = false;
	ok = f.SaveBinMapping( csFile, &m_BinMap);

	if(!ok)
		AfxMessageBox("Warring : Updata Fail.!!!");
	// Note : Change really file data
}

void CDlgBinMapping::OnSetAsBaseFile() 
{
	// Get Touch Panel FileName
	CString csFile;
//	m_bxFile.GetWindowText(csFile);
	m_wndFile.GetWindowText( csFile );
	
	if( csFile == "" )
	{
		AfxMessageBox(" Get File Name Fail");
		return;
	} 

	// 檢查檔案是否存在
	CFileFind Find;
	if(!Find.FindFile( m.FilePath.CategoryPath + csFile ))
	{
		AfxMessageBox("File not found!");
		return;
	}

	m.UI.FileMainBaseMapping = csFile;
	f.SaveUI();
	// Note : Backup BaseSequence File.

	m_wndMappingBase.SetWindowText( m.UI.FileMainBaseMapping );
}

void CDlgBinMapping::OnNew() 
{

	CDlgBinNew dlg;
	dlg.DoModal();

	UpdateFileList();
	// Note : Refreash all file list

}

void CDlgBinMapping::OnDelete() 
{
	if( !f.CheckEnaleChange() )
		return;

	CString csFile;
	int iPos = m_bxFile.GetCurSel();
	if(iPos < 0) 
		return;
	// Note : The folder is no more file.!

	m_wndFile.GetWindowText( csFile );
	
	//////////////////////////////////////////////////////////
	// Start check real file.
	if( csFile == "" )
	{
		AfxMessageBox(" Get File Name Fail");
		return;
	} 
	// 檢查檔案是否存在
	CFileFind Find;
	if(!Find.FindFile( m.FilePath.CategoryPath + csFile))
	{
		AfxMessageBox("File not found!");
		return;
	}
	// 檢查檔案是否正在使用
	if( csFile == m.UI.FileMainMapping )
	{
		AfxMessageBox("File is using !");
		return;
	}
	// 檢查檔案是否為 Base File
	if( csFile == m.UI.FileMainBaseMapping )
	{
		AfxMessageBox("This File is Base Mapping File!");
		return;
	}

	// 刪除原始存在的檔案(.delete)
	::DeleteFile( m.FilePath.CategoryPath + csFile.Left(csFile.Find( _SubMappingName2, 0)) + ".delete");
	// 更改副檔名為 .delete
	::MoveFile( m.FilePath.CategoryPath + csFile, m.FilePath.CategoryPath + csFile.Left(csFile.Find( _SubMappingName2, 0)) + ".delete");
	
	UpdateFileList();

	// Note : Reset FileText
	m_wndFile.SetWindowText( m.UI.FileMainMapping );
	LoadBinMapping( m.FilePath.CategoryPath + m.UI.FileMainMapping );
	ResetMappingList();
}

/////////////////////////////////////////////////////////////////////////////
// File Control Function

void CDlgBinMapping::UpdateFileList()
{
	m_bxFile.ResetContent();
	CFileFind find;
	CString file;

	BOOL bResult = find.FindFile( m.FilePath.CategoryPath + "\\"  + _SubMappingName1 );

	while(bResult)
	{
		bResult = find.FindNextFile();
		file = find.GetFileName();
		if(file.Find( _SubMappingName2, 0)>-1)
			m_bxFile.AddString(file);
	}
	find.Close();

}

void CDlgBinMapping::ResetMappingList()
{
	m_listBin.DeleteAllItems();

	CString cs;
	for(int i=0; i<m_BinMap.GetSize(); i++)
	{
		m_listBin.InsertItem(i, m_BinMap.ElementAt(i).software);

		m_listBin.SetItemText(i, 1, m_BinMap.ElementAt(i).code);

		m_listBin.SetItemText(i, 2, m_BinMap.ElementAt(i).description);
		
		cs = m_BinMap.ElementAt(i).pass ? "1" : "0";
		m_listBin.SetItemText(i, 3, cs);
		
		cs.Format("%d", m_BinMap.ElementAt(i).color);
		m_listBin.SetItemText(i, 4, cs );

		cs.Format("%d", m_BinMap.ElementAt(i).hardware);
		m_listBin.SetItemText(i, 5, cs );
	}

}
void CDlgBinMapping::OnSelect() 
{
	int i = m_bxFile.GetCurSel();
	if(i < 0) return;

	CString file;
	m_bxFile.GetText(i, file);

	m_wndFile.SetWindowText(file);

	// 檢查檔案是否存在
	CFileFind Find;
	if(!Find.FindFile( m.FilePath.CategoryPath + file))
	{
		AfxMessageBox("File not found!");
		return;
	}
	
	LoadBinMapping( m.FilePath.CategoryPath + file ); // Note : Load BinMapping to m_BinMap
	
	ResetMappingList();
}

void CDlgBinMapping::LoadBinMapping(CString file)
{
	// Update m_BinMap for display

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

BOOL CDlgBinMapping::PreTranslateMessage(MSG* pMsg) 
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
