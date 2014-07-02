// DlgOffset.cpp : implementation file
//

#include "stdafx.h"
#include "deer.h"
#include "DlgOffset.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgOffset dialog


CDlgOffset::CDlgOffset(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgOffset::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgOffset)
	m_dOffsetSocketArmZ2 = 0.0;
	m_dOffsetRotatorArmZ2 = 0.0;
	m_dOffsetInputArmZ2 = 0.0;
	m_dOffsetOutputArmZ2 = 0.0;
	m_dOffsetShuttleInputX = 0.0;
	m_dOffsetShuttleInputY = 0.0;
	m_dOffsetShuttleInputZ2 = 0.0;
	m_dOffsetShuttleOutX = 0.0;
	m_dOffsetShuttleOutY = 0.0;
	m_dOffsetShuttleOutZ = 0.0;
	m_dOffsetTSContact = 0.0;
	m_dOffsetTSPick = 0.0;
	m_dOffsetTSPlace = 0.0;
	//}}AFX_DATA_INIT

	m_Offset = m.m_Offset;

	m_fChange = false;
}


void CDlgOffset::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgOffset)
	DDX_Control(pDX, IDC_STATIC_ROTATOR_PL_Z,	m_wndStaticRotatorPLZ);
	DDX_Control(pDX, IDC_STATIC_ROTATOR_PK_Z,	m_wndStaticRotatorPKZ);
	DDX_Control(pDX, IDC_STATIC_ROTATOR_Y,		m_wndStaticRotatorY);
	DDX_Control(pDX, IDC_STATIC_ROTATOR_X,		m_wndStaticRotatorX);
	DDX_Control(pDX, IDC_NOTE,					m_RichNote);
	DDX_Control(pDX, IDC_ROTATOR_GRP,			m_wndRotatorGrp);
	DDX_Control(pDX, IDOK,						m_btnOK);
	DDX_Control(pDX, IDCANCEL,					m_btnCancel);
	DDX_Text(pDX, IDC_OFFSET_INPUT_ARM_X,		m_dOffsetInputArmX);
	DDX_Text(pDX, IDC_OFFSET_INPUT_ARM_Y,		m_dOffsetInputArmY);
	DDX_Text(pDX, IDC_OFFSET_INPUT_ARM_Z,		m_dOffsetInputArmZ);
	DDX_Text(pDX, IDC_OFFSET_OUTPUT_ARM_X,		m_dOffsetOutputArmX);
	DDX_Text(pDX, IDC_OFFSET_OUTPUT_ARM_Y,		m_dOffsetOutputArmY);
	DDX_Text(pDX, IDC_OFFSET_OUTPUT_ARM_Z,		m_dOffsetOutputArmZ);
	DDX_Text(pDX, IDC_OFFSET_ROTATOR_ARM_X,		m_dOffsetRotatorArmX);
	DDX_Text(pDX, IDC_OFFSET_ROTATOR_ARM_Y,		m_dOffsetRotatorArmY);
	DDX_Text(pDX, IDC_OFFSET_ROTATOR_ARM_Z,		m_dOffsetRotatorArmZ);
	DDX_Text(pDX, IDC_OFFSET_SOCKET_ARM_X,		m_dOffsetSocketArmX);
	DDX_Text(pDX, IDC_OFFSET_SOCKET_ARM_Y,		m_dOffsetSocketArmY);
	DDX_Text(pDX, IDC_OFFSET_SOCKET_ARM_Z,		m_dOffsetSocketArmZ);
	DDX_Text(pDX, IDC_OFFSET_SOCKET_ARM_Z2,		m_dOffsetSocketArmZ2);
	DDX_Text(pDX, IDC_OFFSET_ROTATOR_ARM_Z2,	m_dOffsetRotatorArmZ2);
	DDX_Text(pDX, IDC_OFFSET_INPUT_ARM_Z2,		m_dOffsetInputArmZ2);
	DDX_Text(pDX, IDC_OFFSET_OUTPUT_ARM_Z2,		m_dOffsetOutputArmZ2);
	DDX_Text(pDX, IDC_OFFSET_SHIN_ARM_X,		m_dOffsetShuttleInputX);
	DDX_Text(pDX, IDC_OFFSET_SHIN_ARM_Y,		m_dOffsetShuttleInputY);
	DDX_Text(pDX, IDC_OFFSET_SHIN_ARM_Z2,		m_dOffsetShuttleInputZ2);
	DDX_Text(pDX, IDC_OFFSET_SHOUT_ARM_X,		m_dOffsetShuttleOutX);
	DDX_Text(pDX, IDC_OFFSET_SHOUT_ARM_Y,		m_dOffsetShuttleOutY);
	DDX_Text(pDX, IDC_OFFSET_SHOUT_ARM_Z,		m_dOffsetShuttleOutZ);
	DDX_Text(pDX, IDC_OFFSET_TS_CONTACT,		m_dOffsetTSContact);
	DDX_Text(pDX, IDC_OFFSET_TS_PICK,			m_dOffsetTSPick);
	DDX_Text(pDX, IDC_OFFSET_TS_PLACE,			m_dOffsetTSPlace);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgOffset, CDialog)
	//{{AFX_MSG_MAP(CDlgOffset)
	ON_WM_SHOWWINDOW()
	ON_EN_CHANGE(IDC_OFFSET_INPUT_ARM_X,		OnChangeOffsetInputArmX)
	ON_EN_CHANGE(IDC_OFFSET_INPUT_ARM_Y,		OnChangeOffsetInputArmY)
	ON_EN_CHANGE(IDC_OFFSET_INPUT_ARM_Z,		OnChangeOffsetInputArmZ)
	ON_EN_CHANGE(IDC_OFFSET_OUTPUT_ARM_X,		OnChangeOffsetOutputArmX)
	ON_EN_CHANGE(IDC_OFFSET_OUTPUT_ARM_Y,		OnChangeOffsetOutputArmY)
	ON_EN_CHANGE(IDC_OFFSET_OUTPUT_ARM_Z,		OnChangeOffsetOutputArmZ)
	ON_EN_CHANGE(IDC_OFFSET_SOCKET_ARM_X,		OnChangeOffsetSocketArmX)
	ON_EN_CHANGE(IDC_OFFSET_SOCKET_ARM_Y,		OnChangeOffsetSocketArmY)
	ON_EN_CHANGE(IDC_OFFSET_SOCKET_ARM_Z,		OnChangeOffsetSocketArmZ)
	ON_EN_CHANGE(IDC_OFFSET_ROTATOR_ARM_X,		OnChangeOffsetRotatorArmX)
	ON_EN_CHANGE(IDC_OFFSET_ROTATOR_ARM_Y,		OnChangeOffsetRotatorArmY)
	ON_EN_CHANGE(IDC_OFFSET_ROTATOR_ARM_Z,		OnChangeOffsetRotatorArmZ)
	ON_EN_CHANGE(IDC_OFFSET_SOCKET_ARM_Z2,		OnChangeOffsetSocketArmZ2)
	ON_EN_CHANGE(IDC_OFFSET_ROTATOR_ARM_Z2,		OnChangeOffsetRotatorArmZ2)
	ON_EN_CHANGE(IDC_OFFSET_INPUT_ARM_Z2,		OnChangeOffsetInputArmZ2)
	ON_EN_CHANGE(IDC_OFFSET_OUTPUT_ARM_Z2,		OnChangeOffsetOutputArmZ2)
	ON_EN_CHANGE(IDC_OFFSET_SHIN_ARM_X,			OnChangeOffsetShinArmX)
	ON_EN_CHANGE(IDC_OFFSET_SHIN_ARM_Y,			OnChangeOffsetShinArmY)
	ON_EN_CHANGE(IDC_OFFSET_SHOUT_ARM_X,		OnChangeOffsetShoutArmX)
	ON_EN_CHANGE(IDC_OFFSET_SHOUT_ARM_Y,		OnChangeOffsetShoutArmY)
	ON_EN_CHANGE(IDC_OFFSET_SHIN_ARM_Z2,		OnChangeOffsetShinArmZ2)
	ON_EN_CHANGE(IDC_OFFSET_SHOUT_ARM_Z,		OnChangeOffsetShoutArmZ)
	ON_EN_SETFOCUS(IDC_OFFSET_INPUT_ARM_X,		OnSetfocusOffsetInputArmX)
	ON_EN_SETFOCUS(IDC_OFFSET_INPUT_ARM_Y,		OnSetfocusOffsetInputArmY)
	ON_EN_SETFOCUS(IDC_OFFSET_INPUT_ARM_Z,		OnSetfocusOffsetInputArmZ)
	ON_EN_SETFOCUS(IDC_OFFSET_INPUT_ARM_Z2,		OnSetfocusOffsetInputArmZ2)
	ON_EN_SETFOCUS(IDC_OFFSET_OUTPUT_ARM_X,		OnSetfocusOffsetOutputArmX)
	ON_EN_SETFOCUS(IDC_OFFSET_OUTPUT_ARM_Y,		OnSetfocusOffsetOutputArmY)
	ON_EN_SETFOCUS(IDC_OFFSET_OUTPUT_ARM_Z,		OnSetfocusOffsetOutputArmZ)
	ON_EN_SETFOCUS(IDC_OFFSET_OUTPUT_ARM_Z2,	OnSetfocusOffsetOutputArmZ2)
	ON_EN_SETFOCUS(IDC_OFFSET_ROTATOR_ARM_X,	OnSetfocusOffsetRotatorArmX)
	ON_EN_SETFOCUS(IDC_OFFSET_ROTATOR_ARM_Y,	OnSetfocusOffsetRotatorArmY)
	ON_EN_SETFOCUS(IDC_OFFSET_ROTATOR_ARM_Z,	OnSetfocusOffsetRotatorArmZ)
	ON_EN_SETFOCUS(IDC_OFFSET_ROTATOR_ARM_Z2,	OnSetfocusOffsetRotatorArmZ2)
	ON_EN_SETFOCUS(IDC_OFFSET_SHIN_ARM_X,		OnSetfocusOffsetShinArmX)
	ON_EN_SETFOCUS(IDC_OFFSET_SHIN_ARM_Y,		OnSetfocusOffsetShinArmY)
	ON_EN_SETFOCUS(IDC_OFFSET_SHIN_ARM_Z2,		OnSetfocusOffsetShinArmZ2)
	ON_EN_SETFOCUS(IDC_OFFSET_SHOUT_ARM_X,		OnSetfocusOffsetShoutArmX)
	ON_EN_SETFOCUS(IDC_OFFSET_SHOUT_ARM_Y,		OnSetfocusOffsetShoutArmY)
	ON_EN_SETFOCUS(IDC_OFFSET_SHOUT_ARM_Z,		OnSetfocusOffsetShoutArmZ)
	ON_EN_SETFOCUS(IDC_OFFSET_SOCKET_ARM_X,		OnSetfocusOffsetSocketArmX)
	ON_EN_SETFOCUS(IDC_OFFSET_SOCKET_ARM_Y,		OnSetfocusOffsetSocketArmY)
	ON_EN_SETFOCUS(IDC_OFFSET_SOCKET_ARM_Z,		OnSetfocusOffsetSocketArmZ)
	ON_EN_SETFOCUS(IDC_OFFSET_SOCKET_ARM_Z2,	OnSetfocusOffsetSocketArmZ2)
	ON_EN_SETFOCUS(IDC_OFFSET_TS_CONTACT,		OnSetfocusOffsetTsContact)
	ON_EN_SETFOCUS(IDC_OFFSET_TS_PICK,			OnSetfocusOffsetTsPick)
	ON_EN_SETFOCUS(IDC_OFFSET_TS_PLACE,			OnSetfocusOffsetTsPlace)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgOffset message handlers

BOOL CDlgOffset::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m.Info.bSubDlgOpen = true;
	f.UpdateButtonState();

	// init button 
	m_btnOK.SetIcon(IDI_SAVE);
	m_btnOK.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnOK.SetFlat(FALSE);
	
	m_btnCancel.SetIcon(IDI_CANCEL);
	m_btnCancel.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnCancel.SetFlat(FALSE);

	//
	InitValue();

	//
	InitTips();

	//
	InitNoteUI();

	//
	f.SetTitleExtend(this, theApp.enTitleTrayFile );

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
void CDlgOffset::InitNoteUI()
{
	if( f.IsTextOffsetNote() )
		m_RichNote.ShowWindow( TRUE );
	else
		m_RichNote.ShowWindow( FALSE );
}
void CDlgOffset::InitValue()
{
	// Input 
	m_dOffsetInputArmX		= m_Offset.Input.x;
	m_dOffsetInputArmY		= m_Offset.Input.y;
	m_dOffsetInputArmZ		= m_Offset.Input.z;
	m_dOffsetInputArmZ2		= m_Offset.Input.z2;

	// Output 
	m_dOffsetOutputArmX		= m_Offset.Output1.x;
	m_dOffsetOutputArmY		= m_Offset.Output1.y;
	m_dOffsetOutputArmZ		= m_Offset.Output1.z;
	m_dOffsetOutputArmZ2	= m_Offset.Output1.z2;

	// Rotator
	m_dOffsetRotatorArmX	= m_Offset.Rotator.x;
	m_dOffsetRotatorArmY	= m_Offset.Rotator.y;
	m_dOffsetRotatorArmZ	= m_Offset.Rotator.z;	// pick
	m_dOffsetRotatorArmZ2	= m_Offset.Rotator.z2;	// place

	// Socket
	m_dOffsetSocketArmX		= m_Offset.Socket.x;
	m_dOffsetSocketArmY		= m_Offset.Socket.y;
	m_dOffsetSocketArmZ		= m_Offset.Socket.z;
	m_dOffsetSocketArmZ2	= m_Offset.Socket.z2;

	// Shuttle Input / Output 
	// Input 
	m_dOffsetShuttleInputX	= m_Offset.DutIn.x;
	m_dOffsetShuttleInputY	= m_Offset.DutIn.y;
	m_dOffsetShuttleInputZ2 = m_Offset.DutIn.z2;
	// Output 
	m_dOffsetShuttleOutX	= m_Offset.DutOut.x;
	m_dOffsetShuttleOutY	= m_Offset.DutOut.y;
	m_dOffsetShuttleOutZ	= m_Offset.DutOut.z;

	// Test Site 
	m_dOffsetTSContact		= m_Offset.TestSite.contact;
	m_dOffsetTSPick			= m_Offset.TestSite.pick;
	m_dOffsetTSPlace		= m_Offset.TestSite.place;

	UpdateData(FALSE);

	m_fChange = false;	
}
void CDlgOffset::InitTips()
{
	// Tips 
	// Init Tips
	m_ToolTip.Create(this);
	m_ToolTip.SetMaxTipWidth(800);
	m_ToolTip.SetDelayTime( TTDT_AUTOPOP, 10000 );
	m_ToolTip.SetDelayTime( TTDT_INITIAL, 25 );
	m_ToolTip.EnableToolTips(true);

	// Group
	m_ToolTip.AddTool( GetDlgItem(IDC_ROTATOR_GRP),	
		_T("Adjust Arm XYZ work position with rotator") );
	m_ToolTip.AddTool( GetDlgItem(IDC_E_INPUT),	
		_T("Adjust Arm XYZ work position with input tray") );
	m_ToolTip.AddTool( GetDlgItem(IDC_E_OUTPUT),	
		_T("Adjust Arm XYZ work position with output tray") );	
	m_ToolTip.AddTool( GetDlgItem(IDC_E_SOCKET),	
		_T("Adjust Arm XYZ work position with socket") );

	// Tray
	m_ToolTip.AddTool( GetDlgItem(IDC_STATIC_TRAY_X),	
		_T("#1 effect arm xy move to input pick ic x position") );
	m_ToolTip.AddTool( GetDlgItem(IDC_STATIC_TRAY_Y),	
		_T("#1 effect arm xy move to input pick ic y position") );
	m_ToolTip.AddTool( GetDlgItem(IDC_STATIC_TRAY_PK_Z),	
		_T("#1 effect arm z move to input pick ic z position") );
	m_ToolTip.AddTool( GetDlgItem(IDC_STATIC_TRAY_PL_Z),	
		_T("#1 effect arm z move to input pick ic z position") );

	// Shuttle
	m_ToolTip.AddTool( GetDlgItem(IDC_STATIC_SH_X),	
		_T("#1 effect arm xy move to shuttl pick/place ic x position") );
	m_ToolTip.AddTool( GetDlgItem(IDC_STATIC_SH_Y),	
		_T("#1 effect arm z move to shuttle pick/place ic y position") );
	m_ToolTip.AddTool( GetDlgItem(IDC_STATIC_SH_PK_Z),	
		_T("#1 effect arm z move to shuttle pick ic z position") );
	m_ToolTip.AddTool( GetDlgItem(IDC_STATIC_SH_PL_Z),	
		_T("#1 effect arm z move to shuttle place ic z position") );

	// Test Site
	m_ToolTip.AddTool( GetDlgItem(IDC_STATIC_TS_PK),	
		_T("#1 effect ts pick ic from shuttle position") );
	m_ToolTip.AddTool( GetDlgItem(IDC_STATIC_TS_PL),	
		_T("#1 effect ts place ic to shuttle position") );
	m_ToolTip.AddTool( GetDlgItem(IDC_STATIC_TS_CT),	
		_T("#1 effect ts contact with socket position") );

}	
void CDlgOffset::ReDrawUI()
{
	if( m.Setting.m_bRotatoUse == 1 )
	{
		m_wndRotatorGrp.ShowWindow( TRUE );
	}
	else
		m_wndRotatorGrp.ShowWindow( FALSE );


	// 1.0Ah
	if( m.Setting.m_bRotatoUse == 1 )
	{
		BOOL bEnable = TRUE;
		m_wndStaticRotatorX.ShowWindow( bEnable );
		m_wndStaticRotatorY.ShowWindow( bEnable );
		m_wndStaticRotatorPLZ.ShowWindow( bEnable );
		m_wndStaticRotatorPKZ.ShowWindow( bEnable );
	}
	else
	{
		BOOL bEnable = FALSE;
		m_wndStaticRotatorX.ShowWindow( bEnable );
		m_wndStaticRotatorY.ShowWindow( bEnable );
		m_wndStaticRotatorPLZ.ShowWindow( bEnable );
		m_wndStaticRotatorPKZ.ShowWindow( bEnable );	
	}
}
bool CDlgOffset::CheckValue()
{
	bool bValueOK = true;

	//
	UpdateData();

	// Input 
	if( m_dOffsetInputArmX > m.Setting.m_dOffsetHighLimit || 
		m_dOffsetInputArmX < m.Setting.m_dOffsetLowLimit )
	{
		bValueOK = false;
	}
	if( m_dOffsetInputArmY > m.Setting.m_dOffsetHighLimit || 
		m_dOffsetInputArmY < m.Setting.m_dOffsetLowLimit )
	{
		bValueOK = false;
	}
	if( m_dOffsetInputArmZ > m.Setting.m_dOffsetHighLimit || 
		m_dOffsetInputArmZ < m.Setting.m_dOffsetLowLimit )
	{
		bValueOK = false;
	}
	
	// Output 
	if( m_dOffsetOutputArmX > m.Setting.m_dOffsetHighLimit || 
		m_dOffsetOutputArmX < m.Setting.m_dOffsetLowLimit )
	{
		bValueOK = false;
	}
	if( m_dOffsetOutputArmY > m.Setting.m_dOffsetHighLimit || 
		m_dOffsetOutputArmY < m.Setting.m_dOffsetLowLimit )
	{
		bValueOK = false;
	}
	if( m_dOffsetOutputArmZ > m.Setting.m_dOffsetHighLimit || 
		m_dOffsetOutputArmZ < m.Setting.m_dOffsetLowLimit )
	{
		bValueOK = false;
	}				

	// Rotator
	if( m_dOffsetRotatorArmX > m.Setting.m_dOffsetHighLimit || 
		m_dOffsetRotatorArmX < m.Setting.m_dOffsetLowLimit )
	{
		bValueOK = false;
	}
	if( m_dOffsetRotatorArmY > m.Setting.m_dOffsetHighLimit || 
		m_dOffsetRotatorArmY < m.Setting.m_dOffsetLowLimit )
	{
		bValueOK = false;
	}	
	if( m_dOffsetRotatorArmZ > m.Setting.m_dOffsetHighLimit || 
		m_dOffsetRotatorArmZ < m.Setting.m_dOffsetLowLimit )
	{
		bValueOK = false;
	}		
	if( m_dOffsetRotatorArmZ2 > m.Setting.m_dOffsetHighLimit || 
		m_dOffsetRotatorArmZ2 < m.Setting.m_dOffsetLowLimit )
	{
		bValueOK = false;
	}	

	// Socket
	if( m_dOffsetSocketArmX > m.Setting.m_dOffsetHighLimit || 
		m_dOffsetSocketArmX < m.Setting.m_dOffsetLowLimit )
	{
		bValueOK = false;
	}		
	if( m_dOffsetSocketArmY > m.Setting.m_dOffsetHighLimit || 
		m_dOffsetSocketArmY < m.Setting.m_dOffsetLowLimit )
	{
		bValueOK = false;
	}		
	if( m_dOffsetSocketArmZ > m.Setting.m_dOffsetHighLimit || 
		m_dOffsetSocketArmZ < m.Setting.m_dOffsetLowLimit )
	{
		bValueOK = false;
	}	
	if( m_dOffsetSocketArmZ2 > m.Setting.m_dOffsetHighLimit || 
		m_dOffsetSocketArmZ2 < m.Setting.m_dOffsetLowLimit )
	{
		bValueOK = false;
	}	

	// Shuttle 
	// Input 
	if( m_dOffsetShuttleInputX > m.Setting.m_dOffsetHighLimit || 
		m_dOffsetShuttleInputX < m.Setting.m_dOffsetLowLimit )
	{
		bValueOK = false;
	}

	if( m_dOffsetShuttleInputY > m.Setting.m_dOffsetHighLimit || 
		m_dOffsetShuttleInputY < m.Setting.m_dOffsetLowLimit )
	{
		bValueOK = false;
	}

	if( m_dOffsetShuttleInputZ2 > m.Setting.m_dOffsetHighLimit || 
		m_dOffsetShuttleInputZ2 < m.Setting.m_dOffsetLowLimit )
	{
		bValueOK = false;
	}
	// Output 
	if( m_dOffsetShuttleOutX > m.Setting.m_dOffsetHighLimit || 
		m_dOffsetShuttleOutX < m.Setting.m_dOffsetLowLimit )
	{
		bValueOK = false;
	}

	if( m_dOffsetShuttleOutY > m.Setting.m_dOffsetHighLimit || 
		m_dOffsetShuttleOutY < m.Setting.m_dOffsetLowLimit )
	{
		bValueOK = false;
	}

	if( m_dOffsetShuttleOutZ > m.Setting.m_dOffsetHighLimit || 
		m_dOffsetShuttleOutZ < m.Setting.m_dOffsetLowLimit )
	{
		bValueOK = false;
	}

	// Test Site 
	if( m_dOffsetTSContact > m.Setting.m_dOffsetHighLimit || 
		m_dOffsetTSContact < m.Setting.m_dOffsetLowLimit )
	{
		bValueOK = false;
	}

	if( m_dOffsetTSPick > m.Setting.m_dOffsetHighLimit || 
		m_dOffsetTSPick < m.Setting.m_dOffsetLowLimit )
	{
		bValueOK = false;
	}

	if( m_dOffsetTSPlace > m.Setting.m_dOffsetHighLimit || 
		m_dOffsetTSPlace < m.Setting.m_dOffsetLowLimit )
	{
		bValueOK = false;
	}

	return bValueOK;
}
bool CDlgOffset::SaveData()
{
	bool bOK = true;

	if( !CheckValue() )
	{
		bOK = false;
		CString csMsg = _T("");
		csMsg.Format("Offset value is out of range.! %5.2f ~ %5.2f", 
			m.Setting.m_dOffsetHighLimit, m.Setting.m_dOffsetLowLimit);
		AfxMessageBox( csMsg );
		return bOK;
	}
	
	UpdateData();

	//
	// Input 
	m_Offset.Input.x			= m_dOffsetInputArmX;
	m_Offset.Input.y			= m_dOffsetInputArmY;
	m_Offset.Input.z			= m_dOffsetInputArmZ;
	m_Offset.Input.z2			= m_dOffsetInputArmZ2;

	// Output 
	m_Offset.Output1.x			= m_dOffsetOutputArmX;
	m_Offset.Output1.y			= m_dOffsetOutputArmY;
	m_Offset.Output1.z			= m_dOffsetOutputArmZ;
	m_Offset.Output1.z2			= m_dOffsetOutputArmZ2;

	// Rotator
	m_Offset.Rotator.x			= m_dOffsetRotatorArmX;
	m_Offset.Rotator.y			= m_dOffsetRotatorArmY;
	m_Offset.Rotator.z			= m_dOffsetRotatorArmZ; 
	m_Offset.Rotator.z2			= m_dOffsetRotatorArmZ2;
	
	// Socket
	m_Offset.Socket.x			= m_dOffsetSocketArmX;
	m_Offset.Socket.y			= m_dOffsetSocketArmY;
	m_Offset.Socket.z			= m_dOffsetSocketArmZ;
	m_Offset.Socket.z2			= m_dOffsetSocketArmZ2;

	// Shuttle Input / Output 
	// Input 
	m_Offset.DutIn.x			= m_dOffsetShuttleInputX;
	m_Offset.DutIn.y			= m_dOffsetShuttleInputY;
	m_Offset.DutIn.z2			= m_dOffsetShuttleInputZ2;
	// Output 
	m_Offset.DutOut.x			= m_dOffsetShuttleOutX;
	m_Offset.DutOut.y			= m_dOffsetShuttleOutY;
	m_Offset.DutOut.z			= m_dOffsetShuttleOutZ;

	// Test Site 
	m_Offset.TestSite.contact	= m_dOffsetTSContact;
	m_Offset.TestSite.pick		= m_dOffsetTSPick;
	m_Offset.TestSite.place		= m_dOffsetTSPlace;

	m.m_Offset = m_Offset;

	f.SaveOffset();

	return bOK;
}
void CDlgOffset::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	if(bShow)
		ReDrawUI();

	CDialog::OnShowWindow(bShow, nStatus);	
}

BOOL CDlgOffset::PreTranslateMessage(MSG* pMsg) 
{
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

void CDlgOffset::OnOK() 
{
	if( !SaveData() )
		return;

	m.Info.bSubDlgOpen = false;
	f.UpdateButtonState();
	
	CDialog::OnOK();
}

void CDlgOffset::OnCancel() 
{
	if(m_fChange)
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

void CDlgOffset::OnChangeOffsetInputArmX() 
{
	m_fChange = true;
}
void CDlgOffset::OnChangeOffsetInputArmY() 
{
	m_fChange = true;
}
void CDlgOffset::OnChangeOffsetInputArmZ() 
{
	m_fChange = true;
}
void CDlgOffset::OnChangeOffsetOutputArmX() 
{
	m_fChange = true;
}
void CDlgOffset::OnChangeOffsetOutputArmY() 
{
	m_fChange = true;
}
void CDlgOffset::OnChangeOffsetOutputArmZ() 
{
	m_fChange = true;
}
void CDlgOffset::OnChangeOffsetSocketArmX() 
{
	m_fChange = true;
}
void CDlgOffset::OnChangeOffsetSocketArmY() 
{
	m_fChange = true;
}
void CDlgOffset::OnChangeOffsetSocketArmZ() 
{
	m_fChange = true;
}
void CDlgOffset::OnChangeOffsetRotatorArmX() 
{
	m_fChange = true;
}
void CDlgOffset::OnChangeOffsetRotatorArmY() 
{
	m_fChange = true;
}
void CDlgOffset::OnChangeOffsetRotatorArmZ() 
{
	m_fChange = true;
}
void CDlgOffset::OnChangeOffsetSocketArmZ2() 
{
	m_fChange = true;	
}
void CDlgOffset::OnChangeOffsetRotatorArmZ2() 
{
	m_fChange = true;	
}
void CDlgOffset::OnChangeOffsetInputArmZ2() 
{
	m_fChange = true;		
}
void CDlgOffset::OnChangeOffsetOutputArmZ2() 
{
	m_fChange = true;	
}
void CDlgOffset::OnChangeOffsetShinArmX() 
{
	m_fChange = true;	
}
void CDlgOffset::OnChangeOffsetShinArmY() 
{
	m_fChange = true;
}
void CDlgOffset::OnChangeOffsetShoutArmX() 
{
	m_fChange = true;
}
void CDlgOffset::OnChangeOffsetShoutArmY() 
{
	m_fChange = true;
}
void CDlgOffset::OnChangeOffsetShinArmZ2() 
{
	m_fChange = true;	
}
void CDlgOffset::OnChangeOffsetShoutArmZ() 
{
	m_fChange = true;	
}

void CDlgOffset::OnSetfocusOffsetInputArmX() 
{
	CString csMsg = _T("");
	csMsg = f.GetTextOffsetNote( theApp.enNofInputX );
	csMsg.Replace("\\r\\n", "\r\n");
	m_RichNote.SetWindowText( csMsg );
}

void CDlgOffset::OnSetfocusOffsetInputArmY() 
{
	CString csMsg = _T("");
	csMsg = f.GetTextOffsetNote( theApp.enNofInputY );
	csMsg.Replace("\\r\\n", "\r\n");
	m_RichNote.SetWindowText( csMsg );	
}

void CDlgOffset::OnSetfocusOffsetInputArmZ() 
{
	CString csMsg = _T("");
	csMsg = f.GetTextOffsetNote( theApp.enNofInputZ );
	csMsg.Replace("\\r\\n", "\r\n");
	m_RichNote.SetWindowText( csMsg );	
}

void CDlgOffset::OnSetfocusOffsetInputArmZ2() 
{
	CString csMsg = _T("");
	csMsg = f.GetTextOffsetNote( theApp.enNofInputZ2 );
	csMsg.Replace("\\r\\n", "\r\n");
	m_RichNote.SetWindowText( csMsg );	
}

void CDlgOffset::OnSetfocusOffsetOutputArmX() 
{
	CString csMsg = _T("");
	csMsg = f.GetTextOffsetNote( theApp.enNofOutputX );
	csMsg.Replace("\\r\\n", "\r\n");
	m_RichNote.SetWindowText( csMsg );		
}

void CDlgOffset::OnSetfocusOffsetOutputArmY() 
{
	CString csMsg = _T("");
	csMsg = f.GetTextOffsetNote( theApp.enNofOutputY );
	csMsg.Replace("\\r\\n", "\r\n");
	m_RichNote.SetWindowText( csMsg );	
}

void CDlgOffset::OnSetfocusOffsetOutputArmZ() 
{
	CString csMsg = _T("");
	csMsg = f.GetTextOffsetNote( theApp.enNofOutputZ );
	csMsg.Replace("\\r\\n", "\r\n");
	m_RichNote.SetWindowText( csMsg );	
}

void CDlgOffset::OnSetfocusOffsetOutputArmZ2() 
{
	CString csMsg = _T("");
	csMsg = f.GetTextOffsetNote( theApp.enNofOutputZ2 );
	csMsg.Replace("\\r\\n", "\r\n");
	m_RichNote.SetWindowText( csMsg );	
}

void CDlgOffset::OnSetfocusOffsetRotatorArmX() 
{
	CString csMsg = _T("");
	csMsg = f.GetTextOffsetNote( theApp.enNofRotatorX );
	csMsg.Replace("\\r\\n", "\r\n");
	m_RichNote.SetWindowText( csMsg );	
}

void CDlgOffset::OnSetfocusOffsetRotatorArmY() 
{
	CString csMsg = _T("");
	csMsg = f.GetTextOffsetNote( theApp.enNofRotatorY );
	csMsg.Replace("\\r\\n", "\r\n");
	m_RichNote.SetWindowText( csMsg );		
}

void CDlgOffset::OnSetfocusOffsetRotatorArmZ() 
{
	CString csMsg = _T("");
	csMsg = f.GetTextOffsetNote( theApp.enNofRotatorZ );
	csMsg.Replace("\\r\\n", "\r\n");
	m_RichNote.SetWindowText( csMsg );	
}

void CDlgOffset::OnSetfocusOffsetRotatorArmZ2() 
{
	CString csMsg = _T("");
	csMsg = f.GetTextOffsetNote( theApp.enNofRotatorZ2 );
	csMsg.Replace("\\r\\n", "\r\n");
	m_RichNote.SetWindowText( csMsg );	
}

void CDlgOffset::OnSetfocusOffsetShinArmX() 
{
	CString csMsg = _T("");
	csMsg = f.GetTextOffsetNote( theApp.enNofShInX );
	csMsg.Replace("\\r\\n", "\r\n");
	m_RichNote.SetWindowText( csMsg );	
}

void CDlgOffset::OnSetfocusOffsetShinArmY() 
{
	CString csMsg = _T("");
	csMsg = f.GetTextOffsetNote( theApp.enNofShInY );
	csMsg.Replace("\\r\\n", "\r\n");
	m_RichNote.SetWindowText( csMsg );	
}

void CDlgOffset::OnSetfocusOffsetShinArmZ2() 
{
	CString csMsg = _T("");
	csMsg = f.GetTextOffsetNote( theApp.enNofShInZ2 );
	csMsg.Replace("\\r\\n", "\r\n");
	m_RichNote.SetWindowText( csMsg );		
}

void CDlgOffset::OnSetfocusOffsetShoutArmX() 
{
	CString csMsg = _T("");
	csMsg = f.GetTextOffsetNote( theApp.enNofShOutX );
	csMsg.Replace("\\r\\n", "\r\n");
	m_RichNote.SetWindowText( csMsg );	
}

void CDlgOffset::OnSetfocusOffsetShoutArmY() 
{
	CString csMsg = _T("");
	csMsg = f.GetTextOffsetNote( theApp.enNofShOutY );
	csMsg.Replace("\\r\\n", "\r\n");
	m_RichNote.SetWindowText( csMsg );	
}

void CDlgOffset::OnSetfocusOffsetShoutArmZ() 
{
	CString csMsg = _T("");
	csMsg = f.GetTextOffsetNote( theApp.enNofShOutZ );
	csMsg.Replace("\\r\\n", "\r\n");
	m_RichNote.SetWindowText( csMsg );	
}

void CDlgOffset::OnSetfocusOffsetSocketArmX() 
{
	// TODO: Add your control notification handler code here
	
}

void CDlgOffset::OnSetfocusOffsetSocketArmY() 
{
	// TODO: Add your control notification handler code here
	
}

void CDlgOffset::OnSetfocusOffsetSocketArmZ() 
{
	// TODO: Add your control notification handler code here
	
}

void CDlgOffset::OnSetfocusOffsetSocketArmZ2() 
{
	// TODO: Add your control notification handler code here
	
}

void CDlgOffset::OnSetfocusOffsetTsContact() 
{
	CString csMsg = _T("");
	csMsg = f.GetTextOffsetNote( theApp.enNofTsContact );
	csMsg.Replace("\\r\\n", "\r\n");
	m_RichNote.SetWindowText( csMsg );	
}

void CDlgOffset::OnSetfocusOffsetTsPick() 
{
	CString csMsg = _T("");
	csMsg = f.GetTextOffsetNote( theApp.enNofTsPick );
	csMsg.Replace("\\r\\n", "\r\n");
	m_RichNote.SetWindowText( csMsg );		
}

void CDlgOffset::OnSetfocusOffsetTsPlace() 
{
	CString csMsg = _T("");
	csMsg = f.GetTextOffsetNote( theApp.enNofTsPlace );
	csMsg.Replace("\\r\\n", "\r\n");
	m_RichNote.SetWindowText( csMsg );		
}
