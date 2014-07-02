// DlgTSRemainIC.cpp : implementation file
//

#include "stdafx.h"
#include "deer.h"
#include "DlgTSRemainIC.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgTSRemainIC dialog


CDlgTSRemainIC::CDlgTSRemainIC(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgTSRemainIC::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgTSRemainIC)
		// NOTE: the ClassWizard will add member initialization here
	m_dTSRemainVaccTime = 0.0;
	m_iTSRemainICSpeed = 0;
	//}}AFX_DATA_INIT
}


void CDlgTSRemainIC::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgTSRemainIC)
	DDX_Control(pDX, IDC_E_VACC_ALWAYS_ON,		m_btnTSRemainVaccAlwaysOn);
	DDX_Control(pDX, IDC_LED_TS_REMAIN_FLAG,	m_ledTSRemainICFlag);
	DDX_Control(pDX, IDC_LED_ENABLE_FUNCTION,	m_ledEnableFunction);
	DDX_Control(pDX, IDOK,						m_btnOK);
	DDX_Control(pDX, IDCANCEL,					m_btnCancel);
	DDX_Text(pDX, IDC_E_VACC_TIME,				m_dTSRemainVaccTime);
	DDX_Text(pDX, IDC_E_TS_SPEED,				m_iTSRemainICSpeed);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgTSRemainIC, CDialog)
	//{{AFX_MSG_MAP(CDlgTSRemainIC)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgTSRemainIC message handlers

void CDlgTSRemainIC::OnOK() 
{
	//
	if( !SaveData() )
		return;
	
	CDialog::OnOK();
}

void CDlgTSRemainIC::OnCancel() 
{
	
	CDialog::OnCancel();
}

BOOL CDlgTSRemainIC::PreTranslateMessage(MSG* pMsg) 
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

BOOL CDlgTSRemainIC::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// init button 
	m_btnOK.SetIcon(IDI_SAVE);
	m_btnOK.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnOK.SetFlat(FALSE);
	
	m_btnCancel.SetIcon(IDI_CANCEL);
	m_btnCancel.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnCancel.SetFlat(FALSE);


	//
	InitLed();

	//
	InitValue();

	//
	InitTips();

	//
	// Set Timer for get IO Status
	SetTimer(ID_TIME_TS_REMAIN_IC, _TimeTSRemainIC, NULL);
		
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
void CDlgTSRemainIC::InitValue()
{
	//
	if( m.m_TSRemainICParameter.iTSRemainICAlwaysOn == 1 )
		m_btnTSRemainVaccAlwaysOn.SetCheck(1);
	else
		m_btnTSRemainVaccAlwaysOn.SetCheck(0);
	
	//
	m_dTSRemainVaccTime			= m.m_TSRemainICParameter.dTSRemainICVacc;
	m_iTSRemainICSpeed			= m.m_TSRemainICParameter.iTSRemainICSpeed;

	UpdateData(FALSE);
}
void CDlgTSRemainIC::InitLed()
{
	m_ledTSRemainICFlag.SetLed(CLed::LED_COLOR_GREEN, CLed::LED_OFF);
	m_ledEnableFunction.SetLed(CLed::LED_COLOR_GREEN, CLed::LED_OFF);
}
void CDlgTSRemainIC::OnTimer(UINT nIDEvent) 
{
	switch(nIDEvent)
	{
	case ID_TIME_TS_REMAIN_IC:
		{			
			StatusQuery();
		}
		break;
	}	
	CDialog::OnTimer(nIDEvent);
}
void CDlgTSRemainIC::InitTips()
{
	// Tips 
	// Init Tips
	m_ToolTip.Create(this);
	m_ToolTip.SetDelayTime( TTDT_AUTOPOP, 10000 );
	m_ToolTip.SetDelayTime( TTDT_INITIAL, 25 );
	m_ToolTip.EnableToolTips(true);

	//
//	m_ToolTip.AddTool( GetDlgItem(IDC_L_SETTING),	_T("Loop Test times setting") );
}
void CDlgTSRemainIC::StatusQuery()
{
	 m_ledEnableFunction = m.Setting.m_bEnableTSRemainIC == 0 ? false : true;	
	 m_ledTSRemainICFlag = m.m_TSRemainICParameter.bTSRemainICflag == 0 ? false : true;	
}
bool CDlgTSRemainIC::SaveData()
{
	UpdateData();

	// ÀË¬d³t«×.
	if( m_iTSRemainICSpeed > m.Setting.m_iSpeedHighLimit || 
		m_iTSRemainICSpeed < m.Setting.m_iSpeedLowLimit )
	{
		AfxMessageBox("Speed(%) out of range.!");
		return false;
	}


	int Sensor = m_btnTSRemainVaccAlwaysOn.GetCheck();
	if( Sensor )
		m.m_TSRemainICParameter.iTSRemainICAlwaysOn = 1;
	else
		m.m_TSRemainICParameter.iTSRemainICAlwaysOn = 0;

	//
	m.m_TSRemainICParameter.dTSRemainICVacc		= m_dTSRemainVaccTime;
	m.m_TSRemainICParameter.iTSRemainICSpeed	= m_iTSRemainICSpeed;
	//
	f.SaveTSRemainICParameter();

	return true;
}

