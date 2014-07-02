// DlgSpeed.cpp : implementation file
//

#include "stdafx.h"
#include "deer.h"
#include "DlgSpeed.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgSpeed dialog

CDlgSpeed::CDlgSpeed(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgSpeed::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgSpeed)
	m_iSpeedArmX = 0;
	m_iSpeedArmY = 0;
	m_iSpeedArmZ = 0;
	m_iSpeedInserter = 0;
	//
	m_iSpeedArmX_Pos = 0;
	m_iSpeedArmY_Pos = 0;
	m_iSpeedArmZ_Pos = 0;
	m_iSpeedInserter_Pos = 0;
	//
	//}}AFX_DATA_INIT
	m_fChange = false;
	m_SameForAll = false;
}


void CDlgSpeed::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgSpeed)
	DDX_Control(pDX, IDC_SPEED_TITLE,			m_wndSpeedTitle);
	DDX_Control(pDX, IDC_ALL_SAME,				m_btnSameForAll);
	DDX_Control(pDX, IDC_CANCEL_SAME,			m_btnCancelSame);
	DDX_Control(pDX, IDC_SL_SPEED_INSERTER,		m_wndSlInserter);
	DDX_Control(pDX, IDC_SL_SPEED_ARM_Z,		m_wndSlArmZ);
	DDX_Control(pDX, IDC_SL_SPEED_ARM_X,		m_wndSlArmX);
	DDX_Control(pDX, IDOK,						m_btnOK);
	DDX_Control(pDX, IDCANCEL,					m_btnCancel);
	DDX_Text(pDX, IDC_SPEED_ARM_X,				m_iSpeedArmX);
	DDX_Text(pDX, IDC_SPEED_ARM_Z,				m_iSpeedArmZ);
	DDX_Text(pDX, IDC_SPEED_INSERTER,			m_iSpeedInserter);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgSpeed, CDialog)
	//{{AFX_MSG_MAP(CDlgSpeed)
	ON_WM_CLOSE()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_CANCEL_SAME,			OnCancelSame)
	ON_EN_CHANGE(IDC_SPEED_ARM_X,			OnChangeSpeedArmX)
	ON_EN_CHANGE(IDC_SPEED_ARM_Z,			OnChangeSpeedArmZ)
	ON_EN_CHANGE(IDC_SPEED_INSERTER,		OnChangeSpeedInserter)
	ON_WM_HSCROLL()
	ON_BN_CLICKED(IDC_ALL_SAME,				OnAllSame)
	
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgSpeed message handlers

void CDlgSpeed::OnClose() 
{
	m.Info.bSubDlgOpen = false;
	f.UpdateButtonState();
	
	CDialog::OnClose();
}

void CDlgSpeed::OnDestroy() 
{
	m.Info.bSubDlgOpen = false;
	f.UpdateButtonState();

	CDialog::OnDestroy();	
}

BOOL CDlgSpeed::OnInitDialog() 
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

	m_btnCancelSame.SetIcon(IDI_CANCEL);
	m_btnCancelSame.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnCancelSame.SetFlat(FALSE);

	// Disable first
	m_btnCancelSame.EnableWindow( FALSE );
	
	// init SliderCtrl 
	// 設定範圍
	m_wndSlInserter.SetRange(m.Setting.m_iSpeedLowLimit, m.Setting.m_iSpeedHighLimit);
	m_wndSlArmZ.SetRange(m.Setting.m_iSpeedLowLimit, m.Setting.m_iSpeedHighLimit);
	m_wndSlArmX.SetRange(m.Setting.m_iSpeedLowLimit, m.Setting.m_iSpeedHighLimit);

	// 設定每次移動數量數值
	m_wndSlInserter.SetPageSize(5);
	m_wndSlArmZ.SetPageSize(5);
	m_wndSlArmX.SetPageSize(5);

	// 設定 UI 初始值
	InitValue();

	// Backup 初始值
	GetAllValue();

	// 設定速度的初始位置.
	
	m_wndSlInserter.SetPos( m.m_Motor.Inserter.Speed );	
	m_wndSlArmZ.SetPos( m.m_Motor.ArmZ.Speed );
	m_wndSlArmX.SetPos( m.m_Motor.ArmX.Speed );

	// 設定 HS Control 的標題
	CString csTitle;
	csTitle.Format("%d                                 %d",m.Setting.m_iSpeedLowLimit,  m.Setting.m_iSpeedHighLimit );
	m_wndSpeedTitle.SetWindowText( csTitle );

	m_btnSameForAll.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnSameForAll.SetFlat(FALSE);
	
	bool bShow = TRUE;
	if( m.Info.user == enLevelSuperUser )
		bShow = TRUE;
	else
		bShow = FALSE;

	//
	InitTips();

	//
	f.SetTitleExtend(this, theApp.enTitleTrayFile );

	//
	f.ChangeLanguage(GetSafeHwnd());
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
void CDlgSpeed::InitTips()
{
	// Tips 
	// Init Tips
	m_ToolTip.Create(this);
	m_ToolTip.SetMaxTipWidth(800);
	m_ToolTip.SetDelayTime( TTDT_AUTOPOP, 10000 );
	m_ToolTip.SetDelayTime( TTDT_INITIAL, 25 );
	m_ToolTip.EnableToolTips(true);

	//
	m_ToolTip.AddTool( GetDlgItem(IDC_STATIC_ARM_XY),	
		_T("Adjust, Arm XY moving speed") );
	m_ToolTip.AddTool( GetDlgItem(IDC_STATIC_ARM_Z),	
		_T("Adjust, Arm Z moving speed") );
	m_ToolTip.AddTool( GetDlgItem(IDC_STATIC_TS),	
		_T("Adjust, Test site moving speed") );


}
bool CDlgSpeed::CheckAllValue()
{
	if( UpdateData() )
	{
		// Check all value. Each Axis motor.!
		if( m_iSpeedArmX > m.Setting.m_iSpeedHighLimit || m_iSpeedArmX < m.Setting.m_iSpeedLowLimit )
			return false;

		if( m_iSpeedArmY > m.Setting.m_iSpeedHighLimit || m_iSpeedArmY < m.Setting.m_iSpeedLowLimit )
			return false;
	
		if( m_iSpeedArmZ > m.Setting.m_iSpeedHighLimit || m_iSpeedArmZ < m.Setting.m_iSpeedLowLimit )
			return false;

		if( m_iSpeedInserter > m.Setting.m_iSpeedHighLimit || m_iSpeedInserter < m.Setting.m_iSpeedLowLimit )
			return false;	

	}
	else
		return false;
	// Can not get value from dialog.

	return true;
}
void CDlgSpeed::GetAllValue()
{
	UpdateData();

	m_iSpeedArmX_Pos = m_iSpeedArmX;
	m_iSpeedArmY_Pos = m_iSpeedArmY;
	m_iSpeedArmZ_Pos = m_iSpeedArmZ;	
	m_iSpeedInserter_Pos = m_iSpeedInserter;
}

void CDlgSpeed::InitValue()
{
	m_iSpeedArmX = m.m_Motor.ArmX.Speed;
	m_iSpeedArmY = m.m_Motor.ArmX.Speed;
	m_iSpeedArmZ = m.m_Motor.ArmZ.Speed;
	m_iSpeedInserter = m.m_Motor.Inserter.Speed;

	UpdateData(FALSE);
}

void CDlgSpeed::OnOK() 
{	
	if( !CheckAllValue() )
	{
		CString cs;
		cs.Format("Speed out of range.! value shuld be > %d and value < %d", 
			m.Setting.m_iSpeedLowLimit,
			m.Setting.m_iSpeedHighLimit );
		AfxMessageBox( cs );
		return;
	}

	UpdateData();

	m.m_Motor.ArmX.Speed		= m.m_Motor.ArmY.Speed = m_iSpeedArmX;	
	m.m_Motor.ArmZ.Speed		= m_iSpeedArmZ;
	m.m_Motor.Inserter.Speed	= m_iSpeedInserter;

	f.SaveSpeed();
	// Store Speed in current tray file 

	m.Info.bSubDlgOpen = false;
	f.UpdateButtonState();

	CDialog::OnOK();
}

void CDlgSpeed::OnCancel() 
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
		// Data already be modify.
		// So. 
		// If User say YES. We call OnOK() function to store alignment value
		// If User say NO. We did not do anything.
	}
	else
	{
		m.Info.bSubDlgOpen = false;
		f.UpdateButtonState();

		CDialog::OnCancel();
		// Data not be modify.
		// Just Get out the Alignment dialog.
	}
}

void CDlgSpeed::OnCancelSame() 
{
//	InitValue();
	// Reset all motor speed to initial value
	// initial value from tray file.

	// 設定速度的初始位置 In HS control.
	// Reset all motor speed for HS control

	m_wndSlInserter.SetPos( m_iSpeedInserter_Pos );
	m_wndSlArmZ.SetPos( m_iSpeedArmZ_Pos );
	m_wndSlArmX.SetPos( m_iSpeedArmX_Pos );

	m_iSpeedArmX = m_iSpeedArmX_Pos;
	m_iSpeedArmY = m_iSpeedArmY_Pos;
	m_iSpeedArmZ = m_iSpeedArmZ_Pos;
	m_iSpeedInserter = m_iSpeedInserter_Pos;

	UpdateData(FALSE);

	// Disable self button.
	m_btnCancelSame.EnableWindow( FALSE );
	m_btnSameForAll.SetCheck(0);
	m_SameForAll = false;

}	
////////////////////////////////////////////////////////////////
// On Change 
void CDlgSpeed::OnChangeSpeedArmX() 
{
	m_fChange = true;	

	// Get Value from dialog.
	if( UpdateData())
		m_wndSlArmX.SetPos( m_iSpeedArmX );

	// We need Get all value
	// When we change value. We need backup all value
	GetAllValue();
}

void CDlgSpeed::OnChangeSpeedArmZ() 
{
	m_fChange = true;

	// Get Value from dialog.
	if( UpdateData())
		m_wndSlArmZ.SetPos( m_iSpeedArmZ );

	// We need Get all value
	// When we change value. We need backup all value
	GetAllValue();
}
void CDlgSpeed::OnChangeSpeedInserter() 
{
	m_fChange = true;
	
	// Get Value from dialog.
	if( UpdateData())
		m_wndSlInserter.SetPos( m_iSpeedInserter );

	// We need Get all value
	// When we change value. We need backup all value
	GetAllValue();
}

void CDlgSpeed::OnAllSame() 
{
	int b = m_btnSameForAll.GetCheck();
	if( b == 1 )
		m_SameForAll = true;
	else
		m_SameForAll = false;

	// 
	if( b == 1 )
		m_btnCancelSame.EnableWindow( TRUE );
	else
		m_btnCancelSame.EnableWindow( FALSE );
}

////////////////////////////////////////////////////////////////
// On Speed bar 
void CDlgSpeed::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// TODO: Add your message handler code here and/or call default
	// We catch ON_WM_HSCROLL Event from Windows operaton system.

	// Note :
	// If User checked Same for All.
	// Then we store the pos. And set to All motor speed.!

	int Pos = 0;

	CSliderCtrl *pSliderCtrl = (CSliderCtrl*)pScrollBar;

	if (pSliderCtrl->m_hWnd == ::GetDlgItem(m_hWnd, IDC_SL_SPEED_ARM_X))
	{
		m_iSpeedArmX = pSliderCtrl->GetPos();
		Pos = m_iSpeedArmX;
	}
	// It is for Arm X Speed.
	if (pSliderCtrl->m_hWnd == ::GetDlgItem(m_hWnd, IDC_SL_SPEED_ARM_Y)) 
	{
		m_iSpeedArmY = pSliderCtrl->GetPos();
		Pos = m_iSpeedArmY;
	}
	// It is for Arm Y Speed.

	if (pSliderCtrl->m_hWnd == ::GetDlgItem(m_hWnd, IDC_SL_SPEED_ARM_Z)) 
	{
		m_iSpeedArmZ = pSliderCtrl->GetPos();
		Pos = m_iSpeedArmZ;
	}
	// It is for Arm Z Speed.

	if (pSliderCtrl->m_hWnd == ::GetDlgItem(m_hWnd, IDC_SL_SPEED_INSERTER)) 
	{
		m_iSpeedInserter = pSliderCtrl->GetPos();
		Pos = m_iSpeedInserter;
	}
	// It is for Inserter Speed.

	if( !m_SameForAll )
	{
		m_iSpeedArmX_Pos = m_iSpeedArmX;
		m_iSpeedArmY_Pos = m_iSpeedArmY;
		m_iSpeedArmZ_Pos = m_iSpeedArmZ;
		m_iSpeedInserter_Pos = m_iSpeedInserter;
	}
	///////////////////////////////////////////////////////////////////////////////////////
	// Same for All.
		
	if( m_SameForAll )
	// We set Same for All
	{
		// 設定速度的初始位置.
		// 我們設定 HS 控制項
		m_wndSlInserter.SetPos( Pos );
		m_wndSlArmZ.SetPos( Pos );
		m_wndSlArmX.SetPos( Pos );
		
		// 我們設定 Speed.
		m_iSpeedArmX = Pos;
		m_iSpeedArmY = Pos;
		m_iSpeedArmZ = Pos;
		m_iSpeedInserter = Pos;
	}

	m_fChange = true;	

	UpdateData(FALSE);

	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}


BOOL CDlgSpeed::PreTranslateMessage(MSG* pMsg) 
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

