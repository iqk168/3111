// DlgIOMontiorPTCModule.cpp : implementation file
//

#include "stdafx.h"
#include "deer.h"
#include "DlgIOMontiorPTCModule.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgIOMontiorPTCModule dialog


CDlgIOMontiorPTCModule::CDlgIOMontiorPTCModule(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgIOMontiorPTCModule::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgIOMontiorPTCModule)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	m_bOnlyShow = false;
}


void CDlgIOMontiorPTCModule::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgIOMontiorPTCModule)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	DDX_Control(pDX, IDC_LED_PTC_FAN2,			m_ledPTCFan2);
	DDX_Control(pDX, IDC_LED_PTC_FAN1,			m_ledPTCFan1);
	DDX_Control(pDX, IDC_LED_PTC_WATER_FLOW,	m_ledPTCWaterFlow);
	DDX_Control(pDX, IDC_LED_PTC_WATER_PUMP,	m_ledPTCWaterPump);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgIOMontiorPTCModule, CDialog)
	//{{AFX_MSG_MAP(CDlgIOMontiorPTCModule)
	ON_WM_TIMER()
	ON_WM_DESTROY()
	ON_WM_SHOWWINDOW()
	ON_BN_CLICKED(IDC_LED_PTC_WATER_PUMP, OnLedPtcWaterPump)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgIOMontiorPTCModule message handlers

BOOL CDlgIOMontiorPTCModule::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	//
	InitLed();

	//
	InitTips();

	// Set Timer for get IO Status
	SetTimer(ID_TIME_GET_STATUS, _Status_Timer, NULL);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgIOMontiorPTCModule::InitLed()
{
	m_ledPTCFan2.SetLed(CLed::LED_COLOR_RED);
	m_ledPTCFan1.SetLed(CLed::LED_COLOR_RED);
	m_ledPTCWaterFlow.SetLed(CLed::LED_COLOR_RED);
	m_ledPTCWaterPump.SetLed(CLed::LED_COLOR_GREEN);
}
void CDlgIOMontiorPTCModule::InitTips()
{
	// Tips // Init Tips
	m_ToolTip.Create(this);
	m_ToolTip.SetMaxTipWidth(800);
	m_ToolTip.SetDelayTime( TTDT_AUTOPOP, 10000 );
	m_ToolTip.SetDelayTime( TTDT_INITIAL, 25 );
	m_ToolTip.EnableToolTips(true);

	m_ToolTip.AddTool( GetDlgItem(IDC_LED_PTC_FAN2),			_T("R-I1-08") );
	m_ToolTip.AddTool( GetDlgItem(IDC_LED_PTC_FAN1),			_T("R-I1-07") );
	m_ToolTip.AddTool( GetDlgItem(IDC_LED_PTC_WATER_FLOW),		_T("R-I1-09") );
	m_ToolTip.AddTool( GetDlgItem(IDC_LED_PTC_WATER_PUMP),		_T("R-O1-07") );

}
void CDlgIOMontiorPTCModule::IOQuery()
{
//	m_ledPTCFan2		= m.RemoteInStatus.ATCFan2				== 0 ? false : true;
//	m_ledPTCFan1		= m.RemoteInStatus.ATCFan1 				== 0 ? false : true;
//	m_ledPTCWaterFlow	= m.RemoteInStatus.ATCWater 			== 0 ? false : true;
//	m_ledPTCWaterPump	= m.RemoteOutStatus.ATCModuleWaterPump	== 0 ? false : true;
}
//
void CDlgIOMontiorPTCModule::SetOnlyShow(bool bOnlyShow)
{
	m_bOnlyShow = bOnlyShow;
}
void CDlgIOMontiorPTCModule::ReDrawUI()
{

}
void CDlgIOMontiorPTCModule::OnTimer(UINT nIDEvent) 
{
	switch(nIDEvent)
	{
	case ID_TIME_GET_STATUS:
		IOQuery();
		break;
	}		
	CDialog::OnTimer(nIDEvent);
}

void CDlgIOMontiorPTCModule::OnDestroy() 
{
	KillTimer( ID_TIME_GET_STATUS );

	CDialog::OnDestroy();	
}

void CDlgIOMontiorPTCModule::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	if( bShow )
		ReDrawUI();

	CDialog::OnShowWindow(bShow, nStatus);	
}

BOOL CDlgIOMontiorPTCModule::PreTranslateMessage(MSG* pMsg) 
{
	// Tips
	m_ToolTip.RelayEvent(pMsg);
	
	return CDialog::PreTranslateMessage(pMsg);
}

void CDlgIOMontiorPTCModule::OnLedPtcWaterPump() 
{
	if(m_bOnlyShow)
		return;

//	m.RemoteOutSet.ATCModuleWaterPump = !m.RemoteOutStatus.ATCModuleWaterPump;	
}
