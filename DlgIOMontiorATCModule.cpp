// DlgIOMontiorATCModule.cpp : implementation file
//

#include "stdafx.h"
#include "deer.h"
#include "DlgIOMontiorATCModule.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgIOMontiorATCModule dialog


CDlgIOMontiorATCModule::CDlgIOMontiorATCModule(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgIOMontiorATCModule::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgIOMontiorATCModule)
	//}}AFX_DATA_INIT

	m_bOnlyShow = false;
}


void CDlgIOMontiorATCModule::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgIOMontiorATCModule)
	DDX_Control(pDX, IDC_LED_ATC_FAN2,			m_ledATCFan2);
	DDX_Control(pDX, IDC_LED_ATC_FAN1,			m_ledATCFan1);
	DDX_Control(pDX, IDC_LED_ATC_WATER_FLOW,	m_ledATCWaterFlow);
	DDX_Control(pDX, IDC_LED_ATC_WATER_PUMP,	m_ledATCWaterPump);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgIOMontiorATCModule, CDialog)
	//{{AFX_MSG_MAP(CDlgIOMontiorATCModule)
	ON_WM_TIMER()
	ON_WM_DESTROY()
	ON_WM_SHOWWINDOW()
	ON_BN_CLICKED(IDC_LED_ATC_WATER_PUMP, OnLedAtcWaterPump)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgIOMontiorATCModule message handlers

BOOL CDlgIOMontiorATCModule::PreTranslateMessage(MSG* pMsg) 
{
	// Tips
	m_ToolTip.RelayEvent(pMsg);
	
	return CDialog::PreTranslateMessage(pMsg);
}

BOOL CDlgIOMontiorATCModule::OnInitDialog() 
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

void CDlgIOMontiorATCModule::InitLed()
{
	m_ledATCFan2.SetLed(CLed::LED_COLOR_RED);
	m_ledATCFan1.SetLed(CLed::LED_COLOR_RED);
	m_ledATCWaterFlow.SetLed(CLed::LED_COLOR_RED);
	m_ledATCWaterPump.SetLed(CLed::LED_COLOR_GREEN);
}
void CDlgIOMontiorATCModule::InitTips()
{
	// Tips // Init Tips
	m_ToolTip.Create(this);
	m_ToolTip.SetMaxTipWidth(800);
	m_ToolTip.SetDelayTime( TTDT_AUTOPOP, 10000 );
	m_ToolTip.SetDelayTime( TTDT_INITIAL, 25 );
	m_ToolTip.EnableToolTips(true);

	m_ToolTip.AddTool( GetDlgItem(IDC_LED_ATC_FAN2),			_T("R-I1-08") );
	m_ToolTip.AddTool( GetDlgItem(IDC_LED_ATC_FAN1),			_T("R-I1-07") );
	m_ToolTip.AddTool( GetDlgItem(IDC_LED_ATC_WATER_FLOW),		_T("R-I1-09") );
	m_ToolTip.AddTool( GetDlgItem(IDC_LED_ATC_WATER_PUMP),		_T("R-O1-08") );

}
void CDlgIOMontiorATCModule::IOQuery()
{
//	m_ledATCFan2		= m.RemoteInStatus.ATCFan2				== 0 ? false : true;
//	m_ledATCFan1		= m.RemoteInStatus.ATCFan1 				== 0 ? false : true;
//	m_ledATCWaterFlow	= m.RemoteInStatus.ATCWater 			== 0 ? false : true;
//	m_ledATCWaterPump	= m.RemoteOutStatus.ATCModuleWaterPump	== 0 ? false : true;
}
//
void CDlgIOMontiorATCModule::SetOnlyShow(bool bOnlyShow)
{
	m_bOnlyShow = bOnlyShow;
}
void CDlgIOMontiorATCModule::ReDrawUI()
{

}
void CDlgIOMontiorATCModule::OnTimer(UINT nIDEvent) 
{
	switch(nIDEvent)
	{
	case ID_TIME_GET_STATUS:
		IOQuery();
		break;
	}		
	CDialog::OnTimer(nIDEvent);
}

void CDlgIOMontiorATCModule::OnDestroy() 
{
	KillTimer( ID_TIME_GET_STATUS );

	CDialog::OnDestroy();	
}

void CDlgIOMontiorATCModule::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	if( bShow )
		ReDrawUI();

	CDialog::OnShowWindow(bShow, nStatus);	
}

void CDlgIOMontiorATCModule::OnLedAtcWaterPump() 
{
	if(m_bOnlyShow)
		return;

//	m.RemoteOutSet.ATCModuleWaterPump = !m.RemoteOutStatus.ATCModuleWaterPump;
}
