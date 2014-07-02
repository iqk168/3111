// DlgLotInformation.cpp : implementation file
//

#include "stdafx.h"
#include "deer.h"
#include "DlgLotInformation.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgLotInformation dialog


CDlgLotInformation::CDlgLotInformation(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgLotInformation::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgLotInformation)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgLotInformation::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgLotInformation)
	DDX_Control(pDX, IDC_LOT_TRAY_FILE_DROP,	m_wndTrayFileDropList);
	DDX_Control(pDX, IDC_LOT_TRAY_FILE,			m_wndLotTrayFile);
	DDX_Control(pDX, IDC_LOT_PROGRAM_ID,		m_wndLotProgramerID);
	DDX_Control(pDX, IDC_LOT_OPERATER,			m_wndLotOperator);
	DDX_Control(pDX, IDC_LOT_NO,				m_wndLotNo);
	DDX_Control(pDX, IDC_LOT_MACHINE,			m_wndLotMachineID);
	DDX_Control(pDX, IDC_LOT_DEVICE_ID,			m_wndLotDeviceID);
	DDX_Control(pDX, IDCANCEL,					m_btnCancel);
	DDX_Control(pDX, IDOK,						m_btnOK);
	DDX_Control(pDX, IDC_COPY_LOT_NO,			m_btnCopLotNo);
	DDX_Control(pDX, IDC_COPY_MACHINE_NO,		m_btnCopyMachineID);
	DDX_Control(pDX, IDC_COPY_OPERATOR_ID,		m_btnCopyOperator);
	DDX_Control(pDX, IDC_COPY_DEVICE_ID,		m_btnCopyDeviceID);
	DDX_Control(pDX, IDC_COPY_PROGRAM_ID,		m_btnCopyProgramID);
	DDX_Control(pDX, IDC_RC_TEST,				m_btnReCycleTest);
	DDX_Control(pDX, IDC_NORMAL_TEST,			m_btnNormal);
	//}}AFX_DATA_MAP

}


BEGIN_MESSAGE_MAP(CDlgLotInformation, CDialog)
	//{{AFX_MSG_MAP(CDlgLotInformation)
	ON_WM_CLOSE()
	ON_WM_DESTROY()

	ON_BN_CLICKED(IDC_COPY_LOT_NO,		OnCopyLotNo)
	ON_BN_CLICKED(IDC_COPY_MACHINE_NO,	OnCopyMachineNo)
	ON_BN_CLICKED(IDC_COPY_OPERATOR_ID, OnCopyOperatorID)
	ON_BN_CLICKED(IDC_COPY_DEVICE_ID,	OnCopyDeviceID)
	ON_BN_CLICKED(IDC_COPY_PROGRAM_ID,	OnCopyProgramID)
	//
	// Copy last all	
	ON_BN_CLICKED(IDC_COPY_LAST_ALL,	OnCopyLastAll)
	//
	ON_BN_CLICKED(IDC_NORMAL_TEST,		OnNormalTest)
	ON_BN_CLICKED(IDC_RC_TEST,			OnRcTest)

	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgLotInformation message handlers

void CDlgLotInformation::OnClose() 
{
	m.Info.bSubDlgOpen = false;
	f.UpdateButtonState();
	
	CDialog::OnClose();
}

void CDlgLotInformation::OnDestroy() 
{
	m.Info.bSubDlgOpen = false;
	f.UpdateButtonState();

	CDialog::OnDestroy();
}

BOOL CDlgLotInformation::OnInitDialog() 
{
	CDialog::OnInitDialog();

	m.Info.bSubDlgOpen = true;
	f.UpdateButtonState();
	
	// init button 
	m_btnOK.SetIcon(IDI_OK);;
	m_btnOK.SetAlign(CButtonST::ST_ALIGN_VERT);;
	m_btnOK.SetFlat(FALSE);
	
	m_btnCancel.SetIcon(IDI_CANCEL);
	m_btnCancel.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnCancel.SetFlat(FALSE);

	// init copy last button
	m_btnCopLotNo.SetAlign(CButtonST::ST_ALIGN_VERT);;
	m_btnCopLotNo.SetFlat(FALSE);

	m_btnCopyMachineID.SetAlign(CButtonST::ST_ALIGN_VERT);;
	m_btnCopyMachineID.SetFlat(FALSE);

	m_btnCopyOperator.SetAlign(CButtonST::ST_ALIGN_VERT);;
	m_btnCopyOperator.SetFlat(FALSE);

	m_btnCopyDeviceID.SetAlign(CButtonST::ST_ALIGN_VERT);;
	m_btnCopyDeviceID.SetFlat(FALSE);

	m_btnCopyProgramID.SetAlign(CButtonST::ST_ALIGN_VERT);;
	m_btnCopyProgramID.SetFlat(FALSE);

	// init UI value
	UpdataValue();

	//
	InitTips();

	//
	InitUI();

	//
	InitTrayFileDropList();

	//
	InitCopyLastAll();

	//
	f.ChangeLanguage(GetSafeHwnd());
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgLotInformation::InitUI()
{
	// Check Old data is exists.?
	// if there have data enable button else disable button.
	///////////////////////////////////////////////////
	if ( m.LotInfo.OldLotInfoDeviceID == "" )
		m_btnCopyDeviceID.EnableWindow( FALSE );
	else
		m_btnCopyDeviceID.EnableWindow( TRUE );

	if ( m.LotInfo.OldLotInfoMachineID == "" )
		m_btnCopyMachineID.EnableWindow( FALSE );
	else
		m_btnCopyMachineID.EnableWindow( TRUE );

	if ( m.LotInfo.OldLotInfoNo	== "" )
		m_btnCopLotNo.EnableWindow( FALSE );
	else
		m_btnCopLotNo.EnableWindow( TRUE );

	if ( m.LotInfo.OldLotInfoOperator == "" )
		m_btnCopyOperator.EnableWindow( FALSE );
	else
		m_btnCopyOperator.EnableWindow( TRUE );

	if ( m.LotInfo.OldLotInfoProgramerID == "" )
		m_btnCopyProgramID.EnableWindow( FALSE );
	else
		m_btnCopyProgramID.EnableWindow( TRUE );


	if( m.UI.FileMain != "" )
		m_wndLotTrayFile.SetWindowText( m.UI.FileMain );
	///////////////////////////////////////////////////

	if( m.LotInfo.LotInfoIsLotStart == 1 )
	{
		// No End Lot 
		// Do not enable copy last button.!
	}
}
void CDlgLotInformation::InitCopyLastAll()
{
	if( m.Setting.m_bEnableAutoCopyLastLotInfo == 1 )
	{
		CopyLastAll();
		CopyLastCtrl();
	}
}
void CDlgLotInformation::InitTrayFileDropList()
{
	CFileFind findList;
	CString tempStr;
	BOOL findResult;

	// Update List: Mapping File
	findResult = findList.FindFile( m.FilePath.TrayFilesPath + "\\" + _SubFileName1 );
	m_wndTrayFileDropList.ResetContent();

	while(findResult)
	{
		findResult = findList.FindNextFile();
		tempStr = findList.GetFileName();
		if(tempStr.Find( _SubFileName2, 0)>-1)
			m_wndTrayFileDropList.AddString(tempStr);
	}
	findList.Close();

	// Updata current status
	if( m.UI.FileMain != "" )
	{
		int iSel = m_wndTrayFileDropList.FindString(0, m.UI.FileMain );
		m_wndTrayFileDropList.SetCurSel( iSel );
	}
	else
	{

	}
}
void CDlgLotInformation::InitTips()
{
	// Init Tips
	m_ToolTip.Create(this);
	m_ToolTip.SetMaxTipWidth(800);
	m_ToolTip.SetDelayTime( TTDT_AUTOPOP, 10000 );
	m_ToolTip.SetDelayTime( TTDT_INITIAL, 25 );
	m_ToolTip.EnableToolTips(true);

	//
	m_ToolTip.AddTool( GetDlgItem(IDC_STATIC_LOT_NO),				
		_T("Lot No") );
	m_ToolTip.AddTool( GetDlgItem(IDC_STATIC_MACHINE_NO),				
		_T("Machine No") );
	m_ToolTip.AddTool( GetDlgItem(IDC_STATIC_OPERATOR),				
		_T("Operator") );
	m_ToolTip.AddTool( GetDlgItem(IDC_STATIC_DEVICE_ID),				
		_T("Device ID") );
	m_ToolTip.AddTool( GetDlgItem(IDC_STATIC_PROGRAM_ID),				
		_T("Program ID") );

	// Copy last
	m_ToolTip.AddTool( GetDlgItem(IDC_COPY_LOT_NO),				
		_T("Copy last lot no") );
	m_ToolTip.AddTool( GetDlgItem(IDC_COPY_MACHINE_NO),				
		_T("Copy last machine no") );
	m_ToolTip.AddTool( GetDlgItem(IDC_COPY_OPERATOR_ID),				
		_T("Copy last operator") );
	m_ToolTip.AddTool( GetDlgItem(IDC_COPY_DEVICE_ID),				
		_T("Copy last device id") );
	m_ToolTip.AddTool( GetDlgItem(IDC_COPY_PROGRAM_ID),				
		_T("Copy last program id") );
	m_ToolTip.AddTool( GetDlgItem(IDC_COPY_LAST_ALL),				
		_T("Copy last all") );

}
void CDlgLotInformation::OnNormalTest()
{
	CString csTemp;	
	csTemp.Format("RT Mode");
	m_btnReCycleTest.SetWindowText(csTemp);	

	m_btnNormal.SetCheck(true);
	m_btnNormal.Invalidate();
	m_btnReCycleTest.SetCheck(false);

	m_iTestItem = 0;	
}
void CDlgLotInformation::OnRcTest()
{

}
void CDlgLotInformation::OnOK() 
{
	if( !CheckValue() )
	{
		CString csMsg = _T("");
		csMsg.Format("Please complete the Lot.!");
		AfxMessageBox( csMsg );
		return;
	}
	// make sure the dialog 

	if( m.UI.FileMain != "" )
	{
	
	}
	else
	{
		// 沒有做 Device Setup. 要求使用者先設定 Device Setup
		CString csMsg = _T("");
		csMsg.Format("Please to Setup Page [Device Setup], Build a new setting first.!");
		AfxMessageBox( csMsg );
		return;
	}

	// Init value
	CString LotInfoDeviceID		= "";
	CString LotInfoMachineID	= "";
	CString LotInfoNo			= "";
	CString LotInfoOperator		= "";
	CString LotInfoProgramerID	= "";

	m_wndLotDeviceID.GetWindowText(LotInfoDeviceID);
	m_wndLotMachineID.GetWindowText(LotInfoMachineID);
	m_wndLotNo.GetWindowText(LotInfoNo);
	m_wndLotOperator.GetWindowText(LotInfoOperator);
	m_wndLotProgramerID.GetWindowText(LotInfoProgramerID);

	char CheckChar[] = {'/','\\',':','*','?','<','>','|'};

	for(int i=0;i<8;i++)
		if( LotInfoNo.Find(CheckChar[i], 0) > -1 )
		{
			AfxMessageBox("Lot No. cannot include : / \\ : * ? < > |");
			return;
		}

	m.LotInfo.LotInfoDeviceID		= LotInfoDeviceID;
	m.LotInfo.LotInfoMachineID		= LotInfoMachineID;
	m.LotInfo.LotInfoNo				= LotInfoNo;
	m.LotInfo.LotInfoOperator		= LotInfoOperator; 
	m.LotInfo.LotInfoProgramerID	= LotInfoProgramerID;

	m.LotInfo.LotInfoIsLotStart		= 1;

	m.LotInfo.TestItem				= m_iTestItem;  

	// 儲存 Lot 的開始時間
	CTime time = CTime::GetCurrentTime();
	CString csT = _T("");
	csT.Format("Lot Start Time: %s", time.Format("Modth:%m Day:%d Hours:%H Min:%M Sec:%S"));
	m.LotInfo.LotStartTime = csT;

	// 儲存 Lot 的資訊
	f.SaveLotInfo();

	// 新增 Arm Log IC 的資料夾
	f.AddNewArmLogICFolder( m.LotInfo.LotInfoNo );

	// 由 Lot 來新增 Device Setup
	CString csfile = _T("");
	m_wndTrayFileDropList.GetWindowText(csfile);
	f.LotDeviceSetup(csfile);

	//
	CDialog::OnOK();
}

bool CDlgLotInformation::CheckValue()
{
	bool bIsOK = true;	
	// 如果沒有輸入完成,就不可以建立成功

	CString LotInfoDeviceID		= "";
	CString LotInfoMachineID	= "";
	CString LotInfoNo			= "";
	CString LotInfoOperator		= "";
	CString LotInfoProgramerID	= "";

	m_wndLotDeviceID.GetWindowText(LotInfoDeviceID);
	m_wndLotMachineID.GetWindowText(LotInfoMachineID);
	m_wndLotNo.GetWindowText(LotInfoNo);
	m_wndLotOperator.GetWindowText(LotInfoOperator);
	m_wndLotProgramerID.GetWindowText(LotInfoProgramerID);

	if( LotInfoDeviceID == "" )
		bIsOK = false;
	if( LotInfoMachineID == "" )
		bIsOK = false;
	if( LotInfoNo == "" )
		bIsOK = false;
	if( LotInfoOperator == "" )
		bIsOK = false;
	if( LotInfoProgramerID == "" )
		bIsOK = false;

	return bIsOK;
}

void CDlgLotInformation::UpdataValue() 
{
	// Init value
	CString LotInfoDeviceID		= "";
	CString LotInfoMachineID	= "";
	CString LotInfoNo			= "";
	CString LotInfoOperator		= "";
	CString LotInfoProgramerID	= "";

	bool bEnable = FALSE;
	// init Value
	// if No Lot Done. We not allow user to change any lot info

	if( m.LotInfo.LotInfoIsLotStart == 1 )
	{
		LotInfoDeviceID					= m.LotInfo.LotInfoDeviceID;
		LotInfoMachineID				= m.LotInfo.LotInfoMachineID;
		LotInfoNo						= m.LotInfo.LotInfoNo;
		LotInfoOperator					= m.LotInfo.LotInfoOperator; 
		LotInfoProgramerID				= m.LotInfo.LotInfoProgramerID;

		m_wndLotDeviceID.SetWindowText(LotInfoDeviceID);
		m_wndLotMachineID.SetWindowText(LotInfoMachineID);
		m_wndLotNo.SetWindowText(LotInfoNo);
		m_wndLotOperator.SetWindowText(LotInfoOperator);
		m_wndLotProgramerID.SetWindowText(LotInfoProgramerID);
		
		// Disable UI wnd
		bEnable = FALSE;
	}
	else
	{
		// Never New Lot so Enable UI
		bEnable = TRUE;
	}

	m_wndLotDeviceID.EnableWindow(bEnable);
	m_wndLotMachineID.EnableWindow(bEnable);
	m_wndLotNo.EnableWindow(bEnable);
	m_wndLotOperator.EnableWindow(bEnable);
	m_wndLotProgramerID.EnableWindow(bEnable);
	// Enable / Disable UI

	m_iTestItem = m.LotInfo.TestItem;
	// 判斷是否為 RC1, RC2, RC3,如果為其它值就表示 Normal Test
	CString csTemp;	
	if(m.LotInfo.TestItem >= 1)
	{
		if(m.LotInfo.TestItem >1)
			csTemp.Format("RT%d",m.LotInfo.TestItem -1);
		else
			csTemp.Format("RT");

		m_btnReCycleTest.SetWindowText(csTemp);
		m_btnReCycleTest.SetCheck(true);
		m_btnReCycleTest.Invalidate();
		m_btnNormal.SetCheck(false);
	}
	else
	{
		m_btnNormal.SetCheck(true);
		m_btnNormal.Invalidate();
		
		csTemp.Format("RC Mode");
		m_btnReCycleTest.SetWindowText(csTemp);
		m_btnReCycleTest.SetCheck(false);
	}
}

void CDlgLotInformation::OnCancel() 
{
	m.Info.bSubDlgOpen = false;
	f.UpdateButtonState();
	
	CDialog::OnCancel();
}

///////////////////////////////////////////////
// Copy Last

void CDlgLotInformation::OnCopyLotNo()
{
	CString OldLotInfoNo		= "";
	OldLotInfoNo				= m.LotInfo.OldLotInfoNo;
	m_wndLotNo.SetWindowText(OldLotInfoNo);
}
void CDlgLotInformation::OnCopyMachineNo()
{
	CString OldLotInfoMachineID	= "";
	OldLotInfoMachineID			= m.LotInfo.OldLotInfoMachineID;
	m_wndLotMachineID.SetWindowText(OldLotInfoMachineID);
}
void CDlgLotInformation::OnCopyOperatorID()
{
	CString OldLotInfoOperator		= "";
	OldLotInfoOperator				= m.LotInfo.OldLotInfoOperator; 
	m_wndLotOperator.SetWindowText(OldLotInfoOperator);
}
void CDlgLotInformation::OnCopyDeviceID()
{
	CString OldLotInfoDeviceID		= "";
	OldLotInfoDeviceID				= m.LotInfo.OldLotInfoDeviceID;
	m_wndLotDeviceID.SetWindowText(OldLotInfoDeviceID);
}
void CDlgLotInformation::OnCopyProgramID()
{
	CString OldLotInfoProgramerID	= "";
	OldLotInfoProgramerID			= m.LotInfo.OldLotInfoProgramerID;
	m_wndLotProgramerID.SetWindowText(OldLotInfoProgramerID);
}
//
void CDlgLotInformation::CopyLastCtrl()
{
	BOOL bEnable = FALSE;
	GetDlgItem(IDC_COPY_LOT_NO)->ShowWindow( bEnable );
	GetDlgItem(IDC_COPY_MACHINE_NO)->ShowWindow( bEnable );
	GetDlgItem(IDC_COPY_OPERATOR_ID)->ShowWindow( bEnable );
	GetDlgItem(IDC_COPY_DEVICE_ID)->ShowWindow( bEnable );
	GetDlgItem(IDC_COPY_PROGRAM_ID)->ShowWindow( bEnable );
	GetDlgItem(IDC_COPY_LAST_ALL)->ShowWindow( bEnable );
}
void CDlgLotInformation::CopyLastAll()
{	
	CString OldLotInfoNo		= _T("");
	OldLotInfoNo				= m.LotInfo.OldLotInfoNo;
	m_wndLotNo.SetWindowText(OldLotInfoNo);
	//
	CString OldLotInfoMachineID	= "";
	OldLotInfoMachineID			= m.LotInfo.OldLotInfoMachineID;
	m_wndLotMachineID.SetWindowText(OldLotInfoMachineID);
	//
	CString OldLotInfoOperator		= _T("");
	OldLotInfoOperator				= m.LotInfo.OldLotInfoOperator; 
	m_wndLotOperator.SetWindowText(OldLotInfoOperator);
	//
	CString OldLotInfoDeviceID		= "";
	OldLotInfoDeviceID				= m.LotInfo.OldLotInfoDeviceID;
	m_wndLotDeviceID.SetWindowText(OldLotInfoDeviceID);
	//
	CString OldLotInfoProgramerID	= _T("");
	OldLotInfoProgramerID			= m.LotInfo.OldLotInfoProgramerID;
	m_wndLotProgramerID.SetWindowText(OldLotInfoProgramerID);
}
void CDlgLotInformation::OnCopyLastAll()
{
	CopyLastAll();
}
BOOL CDlgLotInformation::PreTranslateMessage(MSG* pMsg) 
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
