// DlgTrayFileNoHeater.cpp : implementation file
//

#include "stdafx.h"
#include "Deer.h"
#include "DlgTrayFileNoHeater.h"
#include "DlgTrayFileChipTray.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgTrayFileNoHeater dialog


CDlgTrayFileNoHeater::CDlgTrayFileNoHeater(CString m_csfile, CWnd* pParent /*=NULL*/)
	: CDialog(CDlgTrayFileNoHeater::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgTrayFileNoHeater)
	//}}AFX_DATA_INIT
	m_TraySpec = m.TraySpec;

	m_file = m_csfile;

	m_fChange = false;
}


void CDlgTrayFileNoHeater::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgTrayFileNoHeater)
	DDX_Control(pDX, IDC_CHIP_TRAY,					m_btnChipTray);
	DDX_Control(pDX, IDC_THICK_TRAY_MODE,			m_btnThickTrayMode);
	DDX_Control(pDX, IDC_HEATING,					m_btnHeater);
	DDX_Control(pDX, IDC_CHANGE_KIT,				m_btnChangeKit);
	DDX_Control(pDX, IDC_PTC_MODULE,				m_btnPTCModule);
	DDX_Control(pDX, IDC_AMBIENT,					m_btnAmbient);
	DDX_Control(pDX, IDC_ATC_MOUDLE,				m_btnATCMoudle);	
	DDX_Control(pDX, IDC_TRI_TEMPERATURE,			m_btnTriTemperature);
	DDX_Control(pDX, IDC_REMOTE,					m_btnRemoteModule);
	DDX_Control(pDX, IDC_COLUMN,					m_edtColumn);
	DDX_Control(pDX, IDC_ROW,						m_edtRow);
	DDX_Control(pDX, IDC_D,							m_edtD);
	DDX_Control(pDX, IDC_C,							m_edtC);
	DDX_Control(pDX, IDC_B,							m_edtB);
	DDX_Control(pDX, IDC_A,							m_edtA);
	DDX_Control(pDX, IDC_NOT_MODIFY,				m_btnModifyCancel);
	DDX_Control(pDX, IDC_SET_AS_BASE_FILE,			m_btnSetBase);
	DDX_Control(pDX, IDC_MODIFY,					m_btnModify);
	DDX_Control(pDX, IDC_SAVE,						m_btnSave);
	DDX_Control(pDX, IDC_NEW,						m_btnNew);
	DDX_Control(pDX, IDOK,							m_btnOK);
	DDX_Control(pDX, IDC_DELETE,					m_btnDelete);
	DDX_Control(pDX, IDCANCEL,						m_btnCancel);
	DDX_Control(pDX, IDC_BASE_FILE,					m_wndBaseFile);
	DDX_Control(pDX, IDC_FILE_LIST,					m_cbxFileList);
	//}}AFX_DATA_MAP

	// ResetDlg 
	// TrayFile
	DDX_Text(pDX, IDC_A, m_TraySpec.A);
	DDV_MinMaxDouble(pDX, m_TraySpec.A, 0., 100.);
	DDX_Text(pDX, IDC_B, m_TraySpec.B);
	DDV_MinMaxDouble(pDX, m_TraySpec.B, 0., 100.);
	DDX_Text(pDX, IDC_C, m_TraySpec.C);
	DDV_MinMaxDouble(pDX, m_TraySpec.C, 1., 100.);
	DDX_Text(pDX, IDC_D, m_TraySpec.D);
	DDV_MinMaxDouble(pDX, m_TraySpec.D, 1., 100.);
	DDX_Text(pDX, IDC_COLUMN, m_TraySpec.Column);
	DDV_MinMaxLong(pDX, m_TraySpec.Column, 1, 100);
	DDX_Text(pDX, IDC_ROW, m_TraySpec.Row);

	DDX_Radio(pDX, IDC_HEATING, m_TraySpec.Heating);

}


BEGIN_MESSAGE_MAP(CDlgTrayFileNoHeater, CDialog)
	//{{AFX_MSG_MAP(CDlgTrayFileNoHeater)
	ON_WM_DESTROY()
	ON_WM_CLOSE()
	ON_CBN_SELCHANGE(IDC_FILE_LIST,				OnSelchangeFileList)
	ON_BN_CLICKED(IDC_SET_AS_BASE_FILE,			OnSetAsBaseFile)
	ON_BN_CLICKED(IDC_MODIFY,					OnModify)
	ON_BN_CLICKED(IDC_NOT_MODIFY,				OnNotModify)
	ON_BN_CLICKED(IDC_DELETE,					OnDelete)
	ON_BN_CLICKED(IDC_NEW,						OnNew)
	ON_BN_CLICKED(IDC_SAVE,						OnSave)
	ON_BN_CLICKED(IDC_AMBIENT,					OnAmbient)
	ON_BN_CLICKED(IDC_HEATING,					OnHeater)
	ON_EN_CHANGE(IDC_COLUMN,					OnChangeColumn)
	ON_EN_CHANGE(IDC_A,							OnChangeA)
	ON_EN_CHANGE(IDC_ROW,						OnChangeRow)
	ON_EN_CHANGE(IDC_C,							OnChangeC)
	ON_EN_CHANGE(IDC_B,							OnChangeB)
	ON_EN_CHANGE(IDC_D,							OnChangeD)
	ON_BN_CLICKED(IDC_CHANGE_KIT,				OnChangeKit)
	ON_BN_CLICKED(IDC_ATC_MOUDLE,				OnAtcMoudle)
	ON_BN_CLICKED(IDC_TRI_TEMPERATURE,			OnTriTemperature)
	ON_BN_CLICKED(IDC_THICK_TRAY_MODE,			OnThickTrayMode)
	ON_WM_SHOWWINDOW()
	ON_BN_CLICKED(IDC_CHIP_TRAY,				OnChipTray)
	ON_BN_CLICKED(IDC_PTC_MODULE, OnPtcModule)
	ON_BN_CLICKED(IDC_REMOTE, OnRemote)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgTrayFileNoHeater message handlers

void CDlgTrayFileNoHeater::OnDestroy() 
{
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here
	
}

BOOL CDlgTrayFileNoHeater::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m.Info.bSubDlgOpen = true;
	f.UpdateButtonState();

	//
	UpdateFileList();

	//
	InitTrayFileUI();

	//
	UpdataCurrentFile();

	// Set BaseFile
	m_wndBaseFile.SetWindowText( m.UI.FileBaseFile );

	// Disable File List title.
	m_cbxFileList.EnableScrollBar( FALSE );

	//
	InitTrayFileButton();

	ThickTray();

	UpdataTrayICONButton();
	////////////////////////////////////////////////////////////////////////////////////////

	f.ChangeLanguage(GetSafeHwnd());

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

/////////////////////////////////////////////////////////////////////////////
// File Control Function
void CDlgTrayFileNoHeater::OnSelchangeFileList() 
{
	LoadTraySpec();	

	UpdateData(FALSE);

	m_btnAmbient.Invalidate();	
	m_btnATCMoudle.Invalidate();		
	m_btnTriTemperature.Invalidate();
	m_btnPTCModule.Invalidate();
	m_btnHeater.Invalidate();
	m_btnRemoteModule.Invalidate();
}

void CDlgTrayFileNoHeater::ThickTray()
{
	if( m_TraySpec.ThickTrayMode )
		m_btnThickTrayMode.SetCheck(1);
	else
		m_btnThickTrayMode.SetCheck(0);
	// Note : For updata Thick Mode button


	
}

void CDlgTrayFileNoHeater::LoadTraySpec()
{
	CString csFile;
	CString FileName;

	int iPos = m_cbxFileList.GetCurSel();
	if( iPos == -1)
	{
		AfxMessageBox("Please select a file first.!");
		return;
	}
	m_cbxFileList.GetLBText(iPos, FileName);
	if( FileName == "")
	{
		AfxMessageBox("Please select file first.!");
		return;
	}

	csFile = m.FilePath.TrayFilesPath + FileName + _SubFileName2;

	// Load Tray Spec
	m_TraySpec.A = m_TraySpec.B = m_TraySpec.C = m_TraySpec.D = 10;
	m_TraySpec.Column = m_TraySpec.Row = 3;

	f.GetSetting( csFile, "Tray Spec", "A",				m_TraySpec.A);
	f.GetSetting( csFile, "Tray Spec", "B",				m_TraySpec.B);
	f.GetSetting( csFile, "Tray Spec", "C",				m_TraySpec.C);
	f.GetSetting( csFile, "Tray Spec", "D",				m_TraySpec.D);
	f.GetSetting( csFile, "Tray Spec", "Column",		m_TraySpec.Column);
	f.GetSetting( csFile, "Tray Spec", "Row",			m_TraySpec.Row);
	f.GetSetting( csFile, "Tray Spec", "Thick Tray",	m_TraySpec.ThickTrayMode );
	f.GetSetting( csFile, "Tray Spec", "Tray Height",	m_TraySpec.TrayHeight );

	// Load Temperature
	f.GetSetting(csFile, "Temperature", "High Temperature Enable", m_TraySpec.Heating);

	// Load Preheater
	m_TraySpec.PlateA = m_TraySpec.PlateB = m_TraySpec.PlateC 
		= m.TraySpec.PlateD = 10;
	m_TraySpec.PlateColumn = m_TraySpec.PlateRow = 3;
}


void CDlgTrayFileNoHeater::SaveTraySpec()
{
	if(!UpdateData())
		return;

	CString csFile = _T("");
	CString FileName = _T("");
	m_cbxFileList.GetWindowText(FileName);
	csFile = m.FilePath.TrayFilesPath + FileName + _SubFileName2;

	// Save TraySpec
	f.SaveSetting( csFile, "Tray Spec", "A",			m_TraySpec.A);
	f.SaveSetting( csFile, "Tray Spec", "B",			m_TraySpec.B);
	f.SaveSetting( csFile, "Tray Spec", "C",			m_TraySpec.C);
	f.SaveSetting( csFile, "Tray Spec", "D",			m_TraySpec.D);
	f.SaveSetting( csFile, "Tray Spec", "Column",		m_TraySpec.Column);
	f.SaveSetting( csFile, "Tray Spec", "Row",			m_TraySpec.Row);
	f.SaveSetting( csFile, "Tray Spec", "Thick Tray",	m_TraySpec.ThickTrayMode );	
	f.SaveSetting( csFile, "Tray Spec", "Tray Height",	m_TraySpec.TrayHeight );	// 

	// Load Temperature
	f.SaveSetting(csFile, "Temperature", "High Temperature Enable", m_TraySpec.Heating);
	
	// Heater = 0
	// Ambit = 1
	// Skip Pre-Heater = 2
	// Cold Chamber = 3
	// ATC = 4
	// Tri = 5
	// Remote = 6
}
/////////////////////////////////////////////////////////////////////////////

void CDlgTrayFileNoHeater::UpdateFileList() 
{
	bool bIsBaseFileExist = false;
	CFileFind find;	

	CString d;
	BOOL bResult = find.FindFile( m.FilePath.TrayFilesPath + _SubFileName1 );

	m_cbxFileList.ResetContent();
	CString file;

	while(bResult)
	{
		bResult = find.FindNextFile();
		file = find.GetFileName();
		if(file.Find( _SubFileName2, 0)>-1)
			m_cbxFileList.AddString(file.Left(file.Find( _SubFileName2, 0)));
		if(file == m.UI.FileBaseFile)  // Check Base File Exist
			bIsBaseFileExist = true;
	}

	find.Close();

	m_wndBaseFile.SetWindowText(m_csBaseFile.Left(m_csBaseFile.Find( _SubFileName2 , 0)));
	m_cbxFileList.SetWindowText(m_csFile);

	if(!bIsBaseFileExist)
	{
		// If base file not exist, Re-set base file.
		CString file;
		m_cbxFileList.GetLBText(0, file);

		m.UI.FileBaseFile = m_csBaseFile = file + _SubFileName2;
		m_wndBaseFile.SetWindowText(m_csBaseFile.Left(m_csBaseFile.Find( _SubFileName2 , 0)));
		f.SaveUI();
	}
}


void CDlgTrayFileNoHeater::OnClose() 
{
	m.Info.bSubDlgOpen = false;
	f.UpdateButtonState();
	
	CDialog::OnClose();
}

//
void CDlgTrayFileNoHeater::OnNew() 
{
	CString csFile;
	m_cbxFileList.GetWindowText(csFile);

	CString m_file;
	
	if( csFile == "" )
	{
		AfxMessageBox("Please make an file name for new file.\n");
		return;
	} 

	m_file = csFile;	// for create other file.!
	csFile = csFile + _SubFileName2;


	// 檢查檔案是否存在
	CFileFind Find;
	if(!Find.FindFile( m.FilePath.TrayFilesPath + m.UI.FileBaseFile ))
	{		
		AfxMessageBox("Base File not found!");
		return;
	}

	if(!::CopyFile( m.FilePath.TrayFilesPath + m.UI.FileBaseFile, 
		m.FilePath.TrayFilesPath + csFile, TRUE))
	{
		AfxMessageBox( "File Already Exist!" );
		m_cbxFileList.SetFocus();
		return;
	}

	SaveOffset();
	// Note : Create Offset File

	UpdateFileList();	

	m_wndBaseFile.SetWindowText( m.UI.FileBaseFile );

	//
	CreateNewFile( m_file );					// Create New Testing 
	ResetTrayFileMappingAndInterface( m_file );
}

void CDlgTrayFileNoHeater::DeleteInterfaceForTrayFile( CString csFile )
{
	// Delete Rs232
	// 刪除原始存在的檔案(.delete)
	::DeleteFile( m.FilePath.InterfaceRs232Path + csFile + ".delete");
	// 更改副檔名為 .delete
	::MoveFile( m.FilePath.InterfaceRs232Path + csFile + _SubInterfaceRS232	, 
		m.FilePath.InterfaceRs232Path + csFile + ".delete");

	// Delete Tcp
	// 刪除原始存在的檔案(.delete)
	::DeleteFile( m.FilePath.InterfaceTcpPath + csFile + ".delete");
	// 更改副檔名為 .delete
	::MoveFile( m.FilePath.InterfaceTcpPath + csFile + _SubInterfaceTCP	, 
		m.FilePath.InterfaceTcpPath + csFile + ".delete");

	// Delete Gpib
	// 刪除原始存在的檔案(.delete)
	::DeleteFile( m.FilePath.InterfaceGpibPath + csFile + ".delete");
	// 更改副檔名為 .delete
	::MoveFile( m.FilePath.InterfaceGpibPath + csFile + _SubInterfaceGPIB	, 
		m.FilePath.InterfaceGpibPath + csFile + ".delete");

	// Delete Ttl
	// 刪除原始存在的檔案(.delete)
	::DeleteFile( m.FilePath.InterfaceTtlPath + csFile + ".delete");
	// 更改副檔名為 .delete
	::MoveFile( m.FilePath.InterfaceTtlPath + csFile + _SubInterfaceTTL	, 
		m.FilePath.InterfaceTtlPath + csFile + ".delete");
}
void CDlgTrayFileNoHeater::DeleteOtherFileForTrayFile( CString csFile )
{
	// Delete TestSetting
	// 刪除原始存在的檔案(.delete)
	::DeleteFile( m.FilePath.TestSettingPath + csFile + ".delete");
	// 更改副檔名為 .delete
	::MoveFile( m.FilePath.TestSettingPath + csFile + _SubTestSettingName2, 
		m.FilePath.TestSettingPath + csFile + ".delete");

	// Delete Mapping 
	// 刪除原始存在的檔案(.delete)
	::DeleteFile( m.FilePath.CategoryPath + csFile + ".delete");
	// 更改副檔名為 .delete
	::MoveFile( m.FilePath.CategoryPath + csFile + _SubMappingName2, 
		m.FilePath.CategoryPath + csFile + ".delete");
}
void CDlgTrayFileNoHeater::ResetTrayFileMappingAndInterface( CString csFile )
{
	CString csMappingFile;
	CString csTestingFile;

	csMappingFile = m.FilePath.TrayFilesPath + csFile + _SubFileName2;
	csTestingFile = m.FilePath.TrayFilesPath + csFile + _SubFileName2;
	//

	CString NewMapping;
	CString NewTesting;
	NewMapping = csFile + _SubMappingName2;
	NewTesting = csFile + _SubTestSettingName2;
	f.SaveSetting(csMappingFile, "Mapping", "MappingFile",		NewMapping );
	f.SaveSetting(csTestingFile, "Testing", "TestFile",			NewTesting );
}
void CDlgTrayFileNoHeater::ResetNewFileInterface( CString csFile )
{
	// 重新把 Interface 的檔案設定過來.

	CString csTesting = _T("");
	csTesting = csFile + _SubTestSettingName2;

	CString csTestingFilePath = _T("");
	csTestingFilePath = m.FilePath.TestSettingPath + csTesting;

	f.SaveSetting(csTestingFilePath, "Interface", "GPIB",	csFile + _SubInterfaceGPIB );
	f.SaveSetting(csTestingFilePath, "Interface", "RS22",	csFile + _SubInterfaceRS232 );
	f.SaveSetting(csTestingFilePath, "Interface", "TCP",	csFile + _SubInterfaceTCP );
	f.SaveSetting(csTestingFilePath, "Interface", "TTL",	csFile + _SubInterfaceTTL );

}
void CDlgTrayFileNoHeater::ResetInterfaceType( CString csFile )
{
	// 把預設的 Interface 類型 設定為 有 Enable 的第一個選項
	CString csTesting = _T("");
	csTesting = csFile + _SubTestSettingName2;
	CString csTestingFilePath = _T("");
	csTestingFilePath = m.FilePath.TestSettingPath + csTesting;

	int iSelected = -1;
	if( m.m_InterfaceEnable.m_bEnableRs232 == 1 )
		iSelected = theApp.enRS232;
	else if( m.m_InterfaceEnable.m_bEnableGpib == 1 )
		iSelected = theApp.enGPIB;
	else if( m.m_InterfaceEnable.m_bEnableTcp == 1 )
		iSelected = theApp.enTCP;
	else if( m.m_InterfaceEnable.m_bEnableTTL == 1 )
		iSelected = theApp.enTTL;

	f.SaveSetting(csTestingFilePath, "Interface Selected", "Selected",	iSelected );
}	
void CDlgTrayFileNoHeater::CreateInterfacefile(CString csFile )
{
	// 以後要改 Interface 的預設值的時候, 就到這邊改...
	CString csRs232file		= _T("");
	CString csTcpfile		= _T("");
	CString csGpibfile		= _T("");
	CString csTtlfile		= _T("");

	//
	csRs232file		= csFile + _SubInterfaceRS232;
	csTcpfile		= csFile + _SubInterfaceTCP;
	csGpibfile		= csFile + _SubInterfaceGPIB;
	csTtlfile		= csFile + _SubInterfaceTTL;

	//
	tagIfRs232Setting m_DefRs232;
	tagIfTcpSetting m_DefTcp;
	tagGPIBParameter m_DefGpib;
	tagTTLParameter m_DefTtl;

	// 設定 Rs232 初值
	m_DefRs232.m_csCmdBin			= "Bin=";
	m_DefRs232.m_csCmdGo			= "Go";
	m_DefRs232.m_csCmdHeader		= "<<";
	m_DefRs232.m_csCmdReady			= "Ready";
	m_DefRs232.m_csCmdStart			= "Start";
	m_DefRs232.m_csCmdTailHeader	= ">>";
	m_DefRs232.m_dCmdTimeout		= 25;

	SaveDataToFile( csRs232file, m_DefRs232 );

	// 設定 Tcp 初值
	m_DefTcp.m_csCmdBin				= "Bin=";
	m_DefTcp.m_csCmdGo				= "Go";
	m_DefTcp.m_csCmdHeader			= "<<";
	m_DefTcp.m_csCmdReady			= "Ready";
	m_DefTcp.m_csCmdStart			= "Start";
	m_DefTcp.m_csCmdTailHeader		= ">>";
	m_DefTcp.m_dCmdTimeout			= 35;

	SaveDataToFile( csTcpfile, m_DefTcp );

	// 設定 Gpib 初值
	m_DefGpib.m_dSendStart			= 2;
	m_DefGpib.m_dTimeout			= 20;
	m_DefGpib.m_iBinBase			= 1;
	m_DefGpib.m_iGpibAddr			= 0;
	m_DefGpib.m_iGpibPort			= 0;
	m_DefGpib.m_Site				= 1;

	SaveDataToFile( csGpibfile, m_DefGpib );

	// 設定 Ttl 初值
	m_DefTtl.s_dStartDelay			= 2;
	m_DefTtl.s_dTimeout				= 15;
	m_DefTtl.s_iBinAssertion		= 0;
	m_DefTtl.s_iEOTAssertion		= 0;
	m_DefTtl.s_iLineMode			= 0;
	m_DefTtl.s_iPowerMode			= 0;
	m_DefTtl.s_iRDYAssertion		= 0;
	m_DefTtl.s_iRDYMode				= 0;
	m_DefTtl.s_iSiteAddress[0]		= 0x260;
	m_DefTtl.s_iSiteAddress[1]		= 0x262;
	m_DefTtl.s_iSiteAddress[2]		= 0x266;
	m_DefTtl.s_iSiteAddress[3]		= 0x268;
	m_DefTtl.s_iSiteMask[0]			= 0xffff;
	m_DefTtl.s_iSiteMask[1]			= 0x0;
	m_DefTtl.s_iSiteMask[2]			= 0xffff;
	m_DefTtl.s_iSiteMask[3]			= 0x0;

	SaveDataToFile( csTtlfile, m_DefTtl );
}
void CDlgTrayFileNoHeater::SaveDataToFile(CString csFileName, tagGPIBParameter FileData)
{
	CString csFile;
	csFile = m.FilePath.InterfaceGpibPath + csFileName;

	f.SaveSetting(csFile, "GPIB", "Bin Base",		FileData.m_iBinBase );
	f.SaveSetting(csFile, "GPIB", "Addr",			FileData.m_iGpibAddr );
	f.SaveSetting(csFile, "GPIB", "Port",			FileData.m_iGpibPort );

	f.SaveSettingDouble(csFile, "GPIB", "Delay",	FileData.m_dSendStart );
	f.SaveSettingDouble(csFile, "GPIB", "Timeout",	FileData.m_dTimeout );

	f.SaveSetting(csFile, "GPIB", "Site",			FileData.m_Site );
}

void CDlgTrayFileNoHeater::SaveDataToFile(CString csFileName, tagTTLParameter FileData)
{

	CString csFile = _T("");
	csFile = m.FilePath.InterfaceTtlPath + csFileName;

	// True / False setting.
	f.SaveSettingTrueFalse(csFile, "信號 Active High(1), Low(0)", "EOT",				FileData.s_iEOTAssertion);
	f.SaveSettingTrueFalse(csFile, "信號 Active High(1), Low(0)", "RDY",				FileData.s_iRDYAssertion);
	f.SaveSettingTrueFalse(csFile, "信號 Active High(1), Low(0)", "BIN",				FileData.s_iBinAssertion);	
	f.SaveSettingTrueFalse(csFile, "信號 Active High(1), Low(0)", "Level(0),Pulse(1)",	FileData.s_iRDYMode);	
	f.SaveSettingTrueFalse(csFile, "Bin 信號", "LINE(0), BCD(1)",						FileData.s_iLineMode);

	f.SaveSettingDouble(csFile, "Other", "Send Start Delay (sec)",						FileData.s_dStartDelay);
	f.SaveSettingDouble(csFile, "Other", "Timeout (sec)",								FileData.s_dTimeout);
	f.SaveSettingTrueFalse(csFile, "Other", "Power Mode(1)Tester(0)Handler",			FileData.s_iPowerMode);

	// Wring.
	for(int i=0; i<4; i++)
	{
		CString cs;
		cs.Format("Site %d", i+1);
		f.SaveSettingHex(csFile, "Address (pin31:0x260, pin32:0x262, pin33:0x266, pin34:0x268)",
			cs, FileData.s_iSiteAddress[i]);
		f.SaveSettingBinary(csFile, "MASK (接線寫 1, 沒接寫 0, pin1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16)", 
			cs, FileData.s_iSiteMask[i]);
	}

}
void CDlgTrayFileNoHeater::SaveDataToFile(CString csFileName, tagIfRs232Setting FileData)
{
	////////////////////////////////////////////////////////////
	// Save data to file
	tagIfRs232Setting m_IffileRs232;
	m_IffileRs232 = FileData;

	CString csFile = _T("");
	csFile = m.FilePath.InterfaceRs232Path + csFileName;

	// Header
	f.SaveSetting(csFile, "Command Format", "CommandHeader",		m_IffileRs232.m_csCmdHeader );
	f.SaveSetting(csFile, "Command Format", "CommandTailHeader",	m_IffileRs232.m_csCmdTailHeader );

	// HandShake communcaion
	f.SaveSetting(csFile, "Command Format", "Command Ready",		m_IffileRs232.m_csCmdReady );
	f.SaveSetting(csFile, "Command Format", "Command Start",		m_IffileRs232.m_csCmdStart );
	f.SaveSetting(csFile, "Command Format", "Command Go",			m_IffileRs232.m_csCmdGo );
	f.SaveSetting(csFile, "Command Format", "Command Bin",			m_IffileRs232.m_csCmdBin );
	
	// Timeout
	f.SaveSetting(csFile, "Command Format", "Command Timeout",		m_IffileRs232.m_dCmdTimeout );
	f.SaveSetting(csFile, "Command Format", "Send Start Delay",		m_IffileRs232.m_dSendStartDleay );
}

void CDlgTrayFileNoHeater::SaveDataToFile(CString csFileName, tagIfTcpSetting FileData)
{
	////////////////////////////////////////////////////////////
	// Save data to file
	tagIfTcpSetting m_IffileTcp;
	m_IffileTcp = FileData;

	CString csFile = _T("");
	csFile = m.FilePath.InterfaceTcpPath + csFileName;

	// Header
	f.SaveSetting(csFile, "Command Format", "CommandHeader",		m_IffileTcp.m_csCmdHeader );
	f.SaveSetting(csFile, "Command Format", "CommandTailHeader",	m_IffileTcp.m_csCmdTailHeader );

	// HandShake communcaion
	f.SaveSetting(csFile, "Command Format", "Command Ready",		m_IffileTcp.m_csCmdReady );
	f.SaveSetting(csFile, "Command Format", "Command Start",		m_IffileTcp.m_csCmdStart );
	f.SaveSetting(csFile, "Command Format", "Command Go",			m_IffileTcp.m_csCmdGo );
	f.SaveSetting(csFile, "Command Format", "Command Bin",			m_IffileTcp.m_csCmdBin );
	
	// Timeout
	f.SaveSetting(csFile, "Command Format", "Command Timeout",		m_IffileTcp.m_dCmdTimeout );
	f.SaveSetting(csFile, "Command Format", "Send Start Delay",		m_IffileTcp.m_dSendStartDleay );
}

void CDlgTrayFileNoHeater::CreateNewFile(CString csFile )
{
	CString csCatoregy = _T("");
	CString csTesting = _T("");

	// Creater Mapping File
	csCatoregy = csFile + _SubMappingName2;
	if(!::CopyFile( m.FilePath.CategoryPath + m.UI.FileMainMapping, 
		m.FilePath.CategoryPath + csCatoregy, TRUE))
	{
		// Create New one
		CeeateNewMapping( csCatoregy );
	}
	else
	{
		// Copy OK.!
	}

	// Create Testing File
	csTesting = csFile + _SubTestSettingName2;
	if(!::CopyFile( m.FilePath.TestSettingPath + m.UI.FileMainTestSetting, 
		m.FilePath.TestSettingPath + csTesting, TRUE))
	{
		// Create New one
		CeeateNewTesting( csTesting );
	}
	else
	{
		// Copy OK.
	}	

	ResetNewFileInterface( csFile );
	ResetInterfaceType( csFile );
	CreateInterfacefile( csFile );
}
void CDlgTrayFileNoHeater::CeeateNewTesting( CString csFile )
{
	if( csFile == "" )
		return;	

	csFile = m.FilePath.TestSettingPath + csFile;

	tagTestSetting m_TestSetting;

	// Default Testing Setting
	m_TestSetting.m_Angle = 0;
	m_TestSetting.m_RotatorUse = 0;
	m_TestSetting.m_CCDUse = 0;
	m_TestSetting.m_CCDSocketUse = 0;

	f.SaveSetting(csFile, "Test Extend", "CCD Socket",	m_TestSetting.m_CCDSocketUse );
	f.SaveSetting(csFile, "Test Extend", "CCD",			m_TestSetting.m_CCDUse );
	f.SaveSetting(csFile, "Test Extend", "ROTATOR",		m_TestSetting.m_RotatorUse );
	f.SaveSetting(csFile, "Test Extend", "Angle",		m_TestSetting.m_Angle );
}
void CDlgTrayFileNoHeater::CeeateNewMapping( CString csFile )
{
	if( csFile == "" )
		return;	

/*
	CString cs = _T("");
	tagCategorySetup m_Category;
	csFile = m.FilePath.CategoryPath + csFile;
	for(int i=0; i< _Output_Stack_No; i++)
	{
		cs.Format("Color in Stack %d", i+1);
		f.SaveSetting(csFile, "Category", cs, m_Category.iOutputColor[i]);
	}
*/

	// 預設的 *.mapping.
	tagBinMapping BinMap;
	CArray <tagBinMapping, tagBinMapping> m_BinMap;
	BinMap.code = "Pass";
	BinMap.color = m.BinColorItem.GetAt(0).color;
	BinMap.description = "Pass condition";
	BinMap.hardware = 0;
	BinMap.pass = 1;
	BinMap.software = "0";

	m_BinMap.Add(BinMap);

	f.SaveBinMapping( csFile, &m_BinMap );
}
void CDlgTrayFileNoHeater::OnSetAsBaseFile() 
{
	CString csFile;
	m_cbxFileList.GetWindowText(csFile);
	if(csFile == _T("") || m_cbxFileList.FindString(0, csFile) == LB_ERR)
	{
		AfxMessageBox("Please select an exist file for base.\n");
		return;
	}

	csFile = csFile + _SubFileName2;

	// 檢查檔案是否存在
	CFileFind Find;
	if(!Find.FindFile( m.FilePath.TrayFilesPath + csFile ))
	{
		AfxMessageBox("File not found!");
		return;
	}

	m.UI.FileBaseFile = csFile;
	f.SaveUI();
	// Note : Backup BaseSequence File.

	m_wndBaseFile.SetWindowText( m.UI.FileBaseFile );
}

void CDlgTrayFileNoHeater::OnModify() 
{
	CString csFile;
	m_cbxFileList.GetWindowText(csFile);
	
	if( csFile == "" )
	{
		AfxMessageBox("Please select file first.!\n");
		return;
	} 
	// Check data first.!

	BOOL bEnable;
	bEnable = TRUE;
	m_btnAmbient.EnableWindow(bEnable);
	m_btnATCMoudle.EnableWindow(bEnable);
	m_btnTriTemperature.EnableWindow(bEnable);
	m_btnPTCModule.EnableWindow(bEnable);
	m_btnHeater.EnableWindow(bEnable);
	m_btnRemoteModule.EnableWindow(bEnable);

	m_btnSave.EnableWindow(bEnable);
	m_edtColumn.EnableWindow(bEnable);
	m_edtRow.EnableWindow(bEnable);
	m_edtD.EnableWindow(bEnable);
	m_edtC.EnableWindow(bEnable);
	m_edtB.EnableWindow(bEnable);
	m_edtA.EnableWindow(bEnable);
	m_btnModifyCancel.EnableWindow(bEnable);
	
	bEnable = FALSE;
	m_cbxFileList.EnableWindow(bEnable);
	m_btnOK.EnableWindow(bEnable);
	m_btnDelete.EnableWindow(bEnable);
	m_btnNew.EnableWindow(bEnable);
	m_btnCancel.EnableWindow(bEnable);
	m_btnDelete.EnableWindow(bEnable);
	m_btnModify.EnableWindow(bEnable);
	m_btnSetBase.EnableWindow(bEnable);

	UpdateData(FALSE);

	m_btnAmbient.Invalidate();	
	m_btnATCMoudle.Invalidate();	
	m_btnTriTemperature.Invalidate();
	m_btnPTCModule.Invalidate();
	m_btnHeater.Invalidate();
	m_btnRemoteModule.Invalidate();
}

void CDlgTrayFileNoHeater::NotModify() 
{
	BOOL bEnable;
	bEnable = FALSE;
	m_btnAmbient.EnableWindow(bEnable);
	m_btnATCMoudle.EnableWindow(bEnable);
	m_btnTriTemperature.EnableWindow(bEnable);
	m_btnPTCModule.EnableWindow(bEnable);
	m_btnHeater.EnableWindow(bEnable);
	m_btnRemoteModule.EnableWindow(bEnable);

	m_btnSave.EnableWindow(bEnable);
	m_edtColumn.EnableWindow(bEnable);
	m_edtRow.EnableWindow(bEnable);
	m_edtD.EnableWindow(bEnable);
	m_edtC.EnableWindow(bEnable);
	m_edtB.EnableWindow(bEnable);
	m_edtA.EnableWindow(bEnable);
	m_btnModifyCancel.EnableWindow(bEnable);

	//-----

	bEnable = TRUE;
	m_cbxFileList.EnableWindow(bEnable);
	m_btnOK.EnableWindow(bEnable);
	m_btnDelete.EnableWindow(bEnable);
	m_btnNew.EnableWindow(bEnable);
	m_btnCancel.EnableWindow(bEnable);
	m_btnDelete.EnableWindow(bEnable);
	m_btnModify.EnableWindow(bEnable);
	m_btnSetBase.EnableWindow(bEnable);

	UpdateData(FALSE);

	m_btnAmbient.Invalidate();	
	m_btnATCMoudle.Invalidate();	
	m_btnTriTemperature.Invalidate();
	m_btnPTCModule.Invalidate();
	m_btnHeater.Invalidate();
	m_btnRemoteModule.Invalidate();
}
void CDlgTrayFileNoHeater::OnNotModify() 
{
	if( m_fChange )
	{

		if(IDYES != AfxMessageBox("Data is modified. Save?\n",
			MB_YESNO|MB_ICONEXCLAMATION))
		{
			NotModify();
		}
		else
			OnSave();
		// Data already be modify.
		// So. 
		// If User say YES. We call OnOK() function to store alignment value
		// If User say NO. We did not do anything.	
	}
	else
	{
		NotModify();
		// Data not be modify.
		// Just Get out the Alignment dialog.
	}
}
void CDlgTrayFileNoHeater::OnChangeKit() 
{
	// 如果不在 Ready 的狀態, 不可以使用 Change Kit 功能
	// Ready 只有有 Cycle Finish 和剛 Initial 完才會有
	if( f.CheckInitialNeed())
		return;
}

void CDlgTrayFileNoHeater::OnDelete() 
{
	if( !f.CheckEnaleChange() )
		return;

	int iPos = m_cbxFileList.GetCurSel();

	if(iPos < 0) 
		return;
	// Note : The folder is no more file.!

	//////////////////////////////////////////////////////////
	// Start check real file.
	CString csFile1; // For *.Tray
	CString csFile2; // For *.offset
	CString m_file;

	m_cbxFileList.GetWindowText(csFile1);
	m_cbxFileList.GetWindowText(csFile2);

	m_file	= csFile1;	// For Delete Other File.!
	csFile1 = csFile1 + _SubFileName2;
	csFile2 = csFile2 + _SubOffsetName2;

	if( csFile1 == "" )
	{
		AfxMessageBox("Please select an exist file for delete file.\n");
		return;
	} 
	// 檢查檔案是否正在使用
	if( csFile1 == m.UI.FileMain )
	{
		AfxMessageBox("File is using !");
		return;
	}
	// 檢查檔案是否為 Base File
	if( csFile1 == m.UI.FileBaseFile )
	{
		AfxMessageBox("This File is Base Tray File!");
		return;
	}
	//////////////////////////////////////////////////////////

	// 刪除原始存在的檔案(.delete)
	::DeleteFile( m.FilePath.TrayFilesPath + csFile1.Left(csFile1.Find(_SubFileName2, 0)) + ".deleteTray");	
	// 更改副檔名為 .delete
	::MoveFile( m.FilePath.TrayFilesPath + csFile1, m.FilePath.TrayFilesPath + csFile1.Left(csFile1.Find(_SubFileName2, 0)) + ".deleteTray");

	// 刪除原始存在的檔案(.delete)
	::DeleteFile( m.FilePath.TrayFilesPath + csFile2.Left(csFile2.Find(_SubOffsetName2, 0)) + ".delete");
	// 更改副檔名為 .delete
	::MoveFile( m.FilePath.TrayFilesPath + csFile2, m.FilePath.TrayFilesPath + csFile2.Left(csFile2.Find(_SubOffsetName2, 0)) + ".delete");
	
	// Delete Other File 
	// Mapping / Testing / Interface
	DeleteOtherFileForTrayFile( m_file );
	DeleteInterfaceForTrayFile( m_file );

	UpdateFileList();
	
	// Set BaseFile
	m_wndBaseFile.SetWindowText( m.UI.FileBaseFile );
}

void CDlgTrayFileNoHeater::OnHeater()
{
	m_fChange = true;

	m_btnAmbient.Invalidate();	
	m_btnATCMoudle.Invalidate();
	m_btnTriTemperature.Invalidate();
	m_btnPTCModule.Invalidate();
	m_btnHeater.Invalidate();
	m_btnRemoteModule.Invalidate();
}

void CDlgTrayFileNoHeater::OnAtcMoudle() 
{
	m_fChange = true;

	m_btnAmbient.Invalidate();	
	m_btnATCMoudle.Invalidate();
	m_btnTriTemperature.Invalidate();
	m_btnPTCModule.Invalidate();
	m_btnHeater.Invalidate();
	m_btnRemoteModule.Invalidate();
}

void CDlgTrayFileNoHeater::OnTriTemperature() 
{
	m_fChange = true;

	m_btnAmbient.Invalidate();	
	m_btnATCMoudle.Invalidate();
	m_btnTriTemperature.Invalidate();
	m_btnPTCModule.Invalidate();
	m_btnHeater.Invalidate();
	m_btnRemoteModule.Invalidate();
}
void CDlgTrayFileNoHeater::OnPtcModule() 
{
	m_fChange = true;

	m_btnAmbient.Invalidate();	
	m_btnATCMoudle.Invalidate();
	m_btnTriTemperature.Invalidate();
	m_btnPTCModule.Invalidate();
	m_btnHeater.Invalidate();
	m_btnRemoteModule.Invalidate();
}
void CDlgTrayFileNoHeater::OnRemote() 
{
	m_fChange = true;

	m_btnAmbient.Invalidate();	
	m_btnATCMoudle.Invalidate();
	m_btnTriTemperature.Invalidate();
	m_btnPTCModule.Invalidate();
	m_btnHeater.Invalidate();
	m_btnRemoteModule.Invalidate();	
}
void CDlgTrayFileNoHeater::OnAmbient() 
{
	BOOL bEnable;
	bEnable = FALSE;

	m_fChange = true;

	m_btnAmbient.Invalidate();	
	m_btnATCMoudle.Invalidate();	
	m_btnTriTemperature.Invalidate();	
	m_btnPTCModule.Invalidate();	
	m_btnHeater.Invalidate();
	m_btnRemoteModule.Invalidate();
}

void CDlgTrayFileNoHeater::OnSave() 
{
	if( !f.CheckEnaleChange() )
		return;

	m_fChange = false;

	SaveTraySpec();
	// We save the TraySpec in Dialog
	LoadTraySpec();

	f.LoadTraySpec();
	// We reload TraySpec. 
	// Then we can use the new setting now.

	// Chip Tray
	theApp.m_InputTray.SetChipMode(	m.TraySpec.m_InputUseChipTray );
	theApp.m_OutputTray.SetChipMode( m.TraySpec.m_OutputUseChipTray );

	// Chip Tray / Repeat Tray
	theApp.m_Tray1.SetChipMode(	m.TraySpec.m_InputUseChipTray );
	theApp.m_Tray2.SetChipMode(	m.TraySpec.m_OutputUseChipTray );

	// Set TraySpec
	theApp.m_InputTray.SetSpec(	m.TraySpec );
	theApp.m_OutputTray.SetSpec( m.TraySpec );

	// Set TraySpec / Repeat Tray
	theApp.m_Tray1.SetSpec(	m.TraySpec );
	theApp.m_Tray2.SetSpec( m.TraySpec );

	// Set Me
	theApp.m_InputTray.SetMe( ( _Stack_A * m.m_Ratio.Y_GearRation ), ( _Stack_B * m.m_Ratio.X_GearRation ));
	theApp.m_OutputTray.SetMe( ( _Stack_A * m.m_Ratio.Y_GearRation ), ( _Stack_B * m.m_Ratio.X_GearRation ));

	// Set Me / Repeat Tray
	theApp.m_Tray1.SetMe( ( _Stack_A * m.m_Ratio.Y_GearRation ), ( _Stack_B * m.m_Ratio.X_GearRation ));
	theApp.m_Tray2.SetMe( ( _Stack_A * m.m_Ratio.Y_GearRation ), ( _Stack_B * m.m_Ratio.X_GearRation ));


	NotModify();
}

void CDlgTrayFileNoHeater::SaveOffset()
{
	if(!UpdateData())
		return;

	CString FileName;
	m_cbxFileList.GetWindowText(FileName);

	CString csBaseFile = m.UI.FileBaseFile;
	CString cc;
	cc = m.FilePath.TrayFilesPath + csBaseFile.Left( m.UI.FileBaseFile.Find(_SubFileName2, 0)) + _SubOffsetName2;
	
	CString dd;
	dd = m.FilePath.TrayFilesPath + FileName + _SubFileName2;
	
	if(!::CopyFile( m.FilePath.TrayFilesPath + csBaseFile.Left( m.UI.FileBaseFile.Find(_SubFileName2, 0)) + _SubOffsetName2, 
		m.FilePath.TrayFilesPath + FileName + _SubOffsetName2, TRUE))
	{
		return;
	}

}

void CDlgTrayFileNoHeater::OnCancel() 
{	
	m.Info.bSubDlgOpen = false;
	f.UpdateButtonState();

	CDialog::OnCancel();
}

void CDlgTrayFileNoHeater::OnOK() 
{	
	m.Info.bSubDlgOpen = false;
	f.UpdateButtonState();

	CDialog::OnOK();
}


void CDlgTrayFileNoHeater::OnChangeColumn() 
{
	if( !m_btnModify.IsWindowEnabled() )
		m_fChange = true;	
}
void CDlgTrayFileNoHeater::OnChangeRow() 
{
	if( !m_btnModify.IsWindowEnabled() )
		m_fChange = true;	
}
void CDlgTrayFileNoHeater::OnChangeA() 
{
	if( !m_btnModify.IsWindowEnabled() )
		m_fChange = true;	
}
void CDlgTrayFileNoHeater::OnChangeC() 
{
	if( !m_btnModify.IsWindowEnabled() )
		m_fChange = true;	
}
void CDlgTrayFileNoHeater::OnChangeB() 
{
	if( !m_btnModify.IsWindowEnabled() )
		m_fChange = true;	
}
void CDlgTrayFileNoHeater::OnChangeD() 
{
	if( !m_btnModify.IsWindowEnabled() )
		m_fChange = true;	
}


void CDlgTrayFileNoHeater::OnThickTrayMode() 
{
	m_fChange = true;
	m_TraySpec.ThickTrayMode = m_btnThickTrayMode.GetCheck() == 1 ? true : false;
	m_btnThickTrayMode.Invalidate();
}

BOOL CDlgTrayFileNoHeater::PreTranslateMessage(MSG* pMsg) 
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

void CDlgTrayFileNoHeater::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);

	if( bShow )
	{
		if( m.Setting.m_bEnableChipTray == 1 )
		{
			m_btnChipTray.ShowWindow( TRUE );
		}
		else
		{
			m_btnChipTray.ShowWindow( FALSE );
		}
	}
}
// Chip Tray
void CDlgTrayFileNoHeater::OnChipTray() 
{
	// 確定有選到檔案
	CString FileName = _T("");
	int iPos = m_cbxFileList.GetCurSel();
	if( iPos == -1)
	{
		AfxMessageBox("Please select a file first.!");
		return;
	}
	m_cbxFileList.GetLBText(iPos, FileName);
	if( FileName == "")
	{
		AfxMessageBox("Please select file first.!");
		return;
	}
	//

	// 把選到的檔案傳到 Chip Tray 的編輯表單裡面
	CDlgTrayFileChipTray dlg( FileName );
	dlg.DoModal();
}
void CDlgTrayFileNoHeater::InitTrayFileButton() 
{
	m_btnAmbient.Invalidate();	
	m_btnATCMoudle.Invalidate();
	m_btnTriTemperature.Invalidate();
	m_btnPTCModule.Invalidate();
	m_btnHeater.Invalidate();
	m_btnRemoteModule.Invalidate();
}
void CDlgTrayFileNoHeater::InitTrayFileUI() 
{
	// init button
	m_btnCancel.SetIcon(IDI_CANCEL);
	m_btnCancel.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnDelete.SetIcon(IDI_DELETE);
	m_btnDelete.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnOK.SetIcon(IDI_OK);
	m_btnOK.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnSave.SetIcon(IDI_SAVE);
	m_btnSave.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnNew.SetIcon(IDI_NEW);
	m_btnNew.SetAlign(CButtonST::ST_ALIGN_VERT);	
	m_btnModify.SetIcon(IDI_MODIFY);
	m_btnModify.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnSetBase.SetIcon(IDI_SET_BASE);
	m_btnSetBase.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnModifyCancel.SetIcon(IDI_CANCEL);
	m_btnModifyCancel.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnChangeKit.SetIcon(IDI_SERVO_MOTOR);
	m_btnChangeKit.SetAlign(CButtonST::ST_ALIGN_VERT);

	m_btnChipTray.SetAlign(CButtonST::ST_ALIGN_VERT);

	// Enable Or Disable
	// Enable
	BOOL bEnable;
	bEnable = TRUE;
	m_btnOK.EnableWindow(bEnable);
	m_btnDelete.EnableWindow(bEnable);
	m_btnNew.EnableWindow(bEnable);
	m_btnSetBase.EnableWindow(bEnable);
	m_btnModify.EnableWindow(bEnable);
	m_btnCancel.EnableWindow(bEnable);
	// Disable
	bEnable = FALSE;
	m_btnAmbient.EnableWindow(bEnable);
	m_btnATCMoudle.EnableWindow(bEnable);
	m_btnTriTemperature.EnableWindow(bEnable);
	m_btnPTCModule.EnableWindow(bEnable);
	m_btnHeater.EnableWindow(bEnable);
	m_btnRemoteModule.EnableWindow(bEnable);

	m_btnSave.EnableWindow(bEnable);

	m_edtColumn.EnableWindow(bEnable);
	m_edtRow.EnableWindow(bEnable);

	m_edtD.EnableWindow(bEnable);
	m_edtC.EnableWindow(bEnable);
	m_edtB.EnableWindow(bEnable);
	m_edtA.EnableWindow(bEnable);
	m_btnModifyCancel.EnableWindow(bEnable);
}
void CDlgTrayFileNoHeater::UpdataCurrentFile() 
{
	// 顯示目前使用的檔案在 List File
	CString csMainFile;
	if( m_file == "" )
	{
		if( m.UI.FileMain != "" )
		{
			csMainFile = m.UI.FileMain;
			csMainFile = m.UI.FileMain.Left( m.UI.FileMain.Find(_SubFileName2, 0));
			m_cbxFileList.SetWindowText( csMainFile );
			// We need remove *.Tray
		}
		else
		{
			int iPos = 0;
			m_cbxFileList.SetCurSel( iPos );
			m_cbxFileList.GetWindowText( csMainFile );
		}
	}
	else
	{
//		AfxMessageBox("");
	}
	
	int iPos = -1;
	iPos = m_cbxFileList.FindString( 0, csMainFile);	// Find Index of File List.
	if( iPos == -1 )
		iPos = 0; 
	m_cbxFileList.SetCurSel( iPos );					// Set Index
	LoadTraySpec();
	UpdateData(FALSE);
}
void CDlgTrayFileNoHeater::UpdataTrayICONButton() 
{
	//////////////////////////////////////////////////////////////////////
	// 重設介面
	RECT rt;
	::GetWindowRect(::GetDlgItem(m_hWnd, IDC_AMBIENT), &rt);
	::MapWindowPoints(NULL, m_hWnd, (LPPOINT)&rt, 2);	
	
	RECT rtW[_ICON_TRAY_TYPE];
	bool rtUse[_ICON_TRAY_TYPE];
	for(int i=0;i<_ICON_TRAY_TYPE;i++)
		rtUse[i] = false;

	//
	for(i=0;i<_ICON_TRAY_TYPE;i++)
		rtW[i] = rt;
	
	//
	/*
	for(i=0;i<_ICON_TRAY_TYPE;i++)
	{
		rtW[i].left		= ( rt.right - rt.left ) + rt.left	+ ( 153 * i ) + 10;
		rtW[i].right	= ( rt.right - rt.left ) + rt.right	+ ( 153 * i ) + 10;
	}
	*/
	for(i=0;i<_ICON_TRAY_TYPE;i++)
	{
		rtW[i].left		= rt.left + (( rt.right - rt.left ) * (i+1)) + (5 * (i+1));
		rtW[i].right	= rt.right + (( rt.right - rt.left ) * (i+1)) + (5 * (i+1));
	}


	// 判斷是否使用 ATC Module	
	if( m.Setting.m_bEnableATCModule == 1 )
	{
		m_btnATCMoudle.ShowWindow( TRUE );
		for(i=0;i<_ICON_TRAY_TYPE;i++)
		{
			if( !rtUse[i] )
			{
				rtUse[i] = true;
				m_btnATCMoudle.MoveWindow(&rtW[i]);
				break;
			}
		}
	}
	else
	{
		m_btnATCMoudle.ShowWindow( FALSE );
	}

	// 判斷是否使用 Tri-Temperature
	if( m.Setting.m_bEnableTriTempModule == 1 )
	{
		m_btnTriTemperature.ShowWindow( TRUE );
		for(i=0;i<_ICON_TRAY_TYPE;i++)
		{
			if( !rtUse[i] )
			{
				rtUse[i] = true;
				m_btnTriTemperature.MoveWindow(&rtW[i]);
				break;
			}
		}
	}
	else
	{
		m_btnTriTemperature.ShowWindow( FALSE );
	}

	// 判斷是否使用 PTC Moduel
	if( m.Setting.m_bEnablePTCModule == 1 )
	{
		m_btnPTCModule.ShowWindow( TRUE );
		for(i=0;i<_ICON_TRAY_TYPE;i++)
		{
			if( !rtUse[i] )
			{
				rtUse[i] = true;
				m_btnPTCModule.MoveWindow(&rtW[i]);
				break;
			}
		}
	}
	else
	{
		m_btnPTCModule.ShowWindow( FALSE );
	}	

	// 判斷是否使用 Heater Module
	if( m.Setting.m_bEnableHeaterModule == 1 )
	{
		m_btnHeater.ShowWindow( TRUE );
		for(i=0;i<_ICON_TRAY_TYPE;i++)
		{
			if( !rtUse[i] )
			{
				rtUse[i] = true;
				m_btnHeater.MoveWindow(&rtW[i]);
				break;
			}
		}
	}
	else
	{
		m_btnHeater.ShowWindow( FALSE );
	}

	// 判斷是否使用 Remote Module
	if( m.Setting.m_bEnableRemoteModule == 1 )
	{
		m_btnRemoteModule.ShowWindow( TRUE );
		for(i=0;i<_ICON_TRAY_TYPE;i++)
		{
			if( !rtUse[i] )
			{
				rtUse[i] = true;
				m_btnRemoteModule.MoveWindow(&rtW[i]);
				break;
			}
		}	
	}
	else
	{
		m_btnRemoteModule.ShowWindow( FALSE );
	}
}


