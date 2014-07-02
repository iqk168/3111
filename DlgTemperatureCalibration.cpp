// DlgTemperatureCalibration.cpp : implementation file
//

#include "stdafx.h"
#include "deer.h"
#include "DlgTemperatureCalibration.h"

//
#include "ColorBtn.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgTemperatureCalibration dialog


CDlgTemperatureCalibration::CDlgTemperatureCalibration(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgTemperatureCalibration::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgTemperatureCalibration)
	m_dSetPoint = 0.0;
	m_dSoakTime = 0.0;
	m_dStableTime = 0.0;
	m_dTolerance = 0.0;
	//}}AFX_DATA_INIT

	m_WestID = 0;

	m_dReadPV = 0;
}


void CDlgTemperatureCalibration::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgTemperatureCalibration)
	DDX_Control(pDX, IDC_ENABLE_SYNC,	m_btnEnableSync);
	DDX_Control(pDX, IDC_S_SITE1,		m_btnSyncSite);
	DDX_Control(pDX, IDC_E_CONTROLER,	m_cbxControllerSel);
	DDX_Control(pDX, IDC_M_SITE1,		m_wndMeasureTemperature);
	DDX_Control(pDX, IDC_D_SITE1,		m_wndDisplayTemperature);
	DDX_Control(pDX, IDC_HEAT_ON,		m_btnHeaterOn);
	DDX_Control(pDX, IDC_SAVE,			m_btnSave);
	DDX_Text(pDX, IDC_P_SETPOINT,		m_dSetPoint);
	DDX_Text(pDX, IDC_P_SOAK_TIME,		m_dSoakTime);
	DDX_Text(pDX, IDC_P_STABLE_TIME,	m_dStableTime);
	DDX_Text(pDX, IDC_P_TOLERANCE,		m_dTolerance);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgTemperatureCalibration, CDialog)
	//{{AFX_MSG_MAP(CDlgTemperatureCalibration)
	ON_BN_CLICKED(IDC_SAVE,			OnSave)
	ON_BN_CLICKED(IDC_HEAT_ON,		OnHeatOn)
	ON_WM_TIMER()
	ON_EN_CHANGE(IDC_P_SETPOINT,	OnChangePSetpoint)
	ON_EN_CHANGE(IDC_P_SOAK_TIME,	OnChangePSoakTime)
	ON_EN_CHANGE(IDC_P_STABLE_TIME, OnChangePStableTime)
	ON_EN_CHANGE(IDC_P_TOLERANCE,	OnChangePTolerance)
	ON_BN_CLICKED(IDC_ENABLE_SYNC,	OnEnableSync)
	ON_BN_CLICKED(IDC_S_SITE1,		OnSSite1)
	ON_WM_SHOWWINDOW()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgTemperatureCalibration message handlers

BOOL CDlgTemperatureCalibration::PreTranslateMessage(MSG* pMsg) 
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

BOOL CDlgTemperatureCalibration::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// init button 
	m_btnSave.SetIcon(IDI_SAVE);;
	m_btnSave.SetAlign(CButtonST::ST_ALIGN_VERT);;
	m_btnSave.SetFlat(FALSE);
		
	InitController();

	InitValue();

	InitUI();

	InitTips();

	SetSyncUI();

	InitSync();

	SetTimer( ID_TIME_WEST_TEMP, 50, NULL );
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
void CDlgTemperatureCalibration::InitController()
{
	int nSize = m.m_WestControllerList.m_List.GetSize();
	for(int i=0;i<nSize;i++)
	{
		CString csName = _T("");
		csName.Format("%s", m.m_WestControllerList.m_List.GetAt(i).csFunctionName);
		m_cbxControllerSel.AddString(csName);
	}
	m_cbxControllerSel.SetCurSel(0);
}
void CDlgTemperatureCalibration::InitTips()
{
	// Tips 
	// Init Tips
	m_ToolTip.Create(this);
	m_ToolTip.SetMaxTipWidth(800);
	m_ToolTip.SetDelayTime( TTDT_AUTOPOP, 10000 );
	m_ToolTip.SetDelayTime( TTDT_INITIAL, 25 );
	m_ToolTip.EnableToolTips(true);

	//
	m_ToolTip.AddTool( GetDlgItem(IDC_STATIC_DISPLAY_TEMP),	
		_T("Display Temperature") );
}
void CDlgTemperatureCalibration::InitUI()
{
	//
	m_wndDisplayTemperature.SetNewBkColor(ST_LIGHTGREEN);	
	m_wndDisplayTemperature.SetText("--", 10, "Arial", DT_CENTER | DT_VCENTER | DT_SINGLELINE);	

	//
	CString csDefaultMea = "0";
	m_wndMeasureTemperature.SetWindowText( csDefaultMea );
}
void CDlgTemperatureCalibration::InitSync()
{
	if( m.RemoteOutStatus.HeaterOn )
		m_btnHeaterOn.SetCheck(1);
	else
		m_btnHeaterOn.SetCheck(0);

	m_btnHeaterOn.Invalidate();
}
void CDlgTemperatureCalibration::InitValue()
{
	m_dSetPoint		= m.m_West.dSetPoint;
	m_dSoakTime		= m.m_West.dSoakTime;
	m_dStableTime	= m.m_West.dStableTime;
	m_dTolerance	= m.m_West.dTolerance;

	UpdateData(FALSE);
}
void CDlgTemperatureCalibration::SaveData()
{
	UpdateData();	
	m.m_West.dSetPoint		= m_dSetPoint;
	m.m_West.dSoakTime		= m_dSoakTime;
	m.m_West.dStableTime	= m_dStableTime;
	m.m_West.dTolerance		= m_dTolerance;

	f.SaveTemperatureSetting();
}
bool CDlgTemperatureCalibration::CheckValue()
{
	UpdateData();	
/*
	_MaxHeaterTemp
	_MinHeaterTemp
	_MaxHeaterStableTime
	_MinHeaterStableTime
	_MaxHeaterSoakTime
	_MinHeaterSoakTime
*/
	bool bOK = true;
	CString csMsg = _T("");
	// Set Point
	if( m_dSetPoint > _MaxHeaterTemp || m_dSetPoint < _MinHeaterTemp )
	{
		CString csErr = _T("");
		csErr.Format("Set Point is out of range, [%5.2f~%5.2f]\r\n", _MinHeaterTemp, _MaxHeaterTemp );
		csMsg += csErr;
		bOK = false;
	}
	// Stable Time
	if( m_dStableTime > _MaxHeaterStableTime || m_dStableTime < _MinHeaterStableTime )
	{
		CString csErr = _T("");
		csErr.Format("Stable Time is out of range, [%d~%d]\r\n", _MinHeaterStableTime, _MaxHeaterStableTime );
		csMsg += csErr;
		bOK = false;
	}
	// Soak Time
	if( m_dSoakTime > _MaxHeaterSoakTime || m_dSoakTime < _MinHeaterSoakTime )
	{
		CString csErr = _T("");
		csErr.Format("Soak Time is out of range, [%d~%d]\r\n", _MinHeaterSoakTime, _MaxHeaterSoakTime );
		csMsg += csErr;
		bOK = false;
	}
	// Tolerance
	if( m_dTolerance > _MaxHeaterTolerance || m_dTolerance < _MinHeaterTolerance )
	{
		CString csErr = _T("");
		csErr.Format("Tolerance is out of range, [%5.2f~%5.2f]\r\n", _MinHeaterTolerance, _MaxHeaterTolerance );
		csMsg += csErr;
		bOK = false;
	}

	if(!bOK)
		AfxMessageBox( csMsg );

	return bOK;
}
void CDlgTemperatureCalibration::CalibrationSetSV() 
{
	UpdateData();
	double dSV = 0.0;
	dSV = m_dSetPoint;
	// set sv
	m.m_DriveWest.AddCmd(m_WestID+1, enSV, dSV );

	// set offset
	CString csGetProt = _T("");
	int nSize = m.m_WestControllerList.m_List.GetSize();
	int nSel  = m_cbxControllerSel.GetCurSel();
	CString csName = _T("");
	m_cbxControllerSel.GetLBText( nSel, csName );
	for(int i=0;i<nSize;i++)
	{
		CString csFinName = m.m_WestControllerList.m_List.GetAt(i).csFunctionName;
		if( csFinName == csName )
		{
			CString csName = _T("");
			csName.Format("%s", m.m_WestControllerList.m_List.GetAt(i).csFunctionName );
			csGetProt = csName;
			break;
		}
	}
	//
	double dOffset = 0.0;
	CString csSV = _T("");
	csSV.Format("%5.2f", dSV );
	f.GetWestLoopupTableTemperature( csSV, csGetProt, dOffset );
	m.m_DriveWest.AddCmd(m_WestID+1, enOffset, dOffset );

	//
	m.m_heaterCtrl.m_bHeaterIsStable = false;

}
void CDlgTemperatureCalibration::OnSave() 
{
	if( !CheckValue() )
		return;
	
	CalibrationSetSV();

	SaveData();
}

void CDlgTemperatureCalibration::OnHeatOn() 
{
	// Heater Control..
	int m_iHeaterOn = m_btnHeaterOn.GetCheck();
	if( m_iHeaterOn == 1 )
		m.RemoteOutSet.HeaterOn = true; 
	else
	{
		m.m_heaterCtrl.m_bHeaterIsStable = false;
		m.RemoteOutSet.HeaterOn = false;
	}

	m_btnHeaterOn.Invalidate();
}
void CDlgTemperatureCalibration::UpdateDisplay() 
{
	CString csPV = _T("");
#ifdef _Demo
	

#else
	double dPV[_MaxWestDevice];
	double dSV[_MaxWestDevice];
	m.m_DriveWest.GetValue(dPV, dSV);
	csPV.Format("%5.2f", dPV[m_WestID+1]);
	m_dReadPV = dPV[m_WestID+1];
	m_wndDisplayTemperature.SetWindowText( csPV );
#endif
}
void CDlgTemperatureCalibration::OnTimer(UINT nIDEvent) 
{
	switch(nIDEvent)
	{
	case ID_TIME_WEST_TEMP:
		UpdateDisplay();	
		break;
	default:
		break;
	}	
	CDialog::OnTimer(nIDEvent);
}

void CDlgTemperatureCalibration::OnChangePSetpoint() 
{
	
}

void CDlgTemperatureCalibration::OnChangePSoakTime() 
{
	
}

void CDlgTemperatureCalibration::OnChangePStableTime() 
{
	
}

void CDlgTemperatureCalibration::OnChangePTolerance() 
{
	
}
void CDlgTemperatureCalibration::SetIOSyncUI()
{
	if( m.RemoteOutStatus.HeaterOn )
		m_btnHeaterOn.SetCheck(1);
	else
		m_btnHeaterOn.SetCheck(0);

	m_btnHeaterOn.Invalidate();
}
void CDlgTemperatureCalibration::SetSyncUI()
{
	m_btnEnableSync.Invalidate();	

	m_bEnableSync = m_btnEnableSync.GetCheck() ? true : false;

	if( m_bEnableSync )
	{
		m_btnSyncSite.EnableWindow( TRUE );
		// Enable Sync UI
	}
	else
	{
		m_btnSyncSite.EnableWindow( FALSE );
		// Disable Sync UI
	}
}

void CDlgTemperatureCalibration::OnEnableSync() 
{
	SetSyncUI();
}
void CDlgTemperatureCalibration::CalibrationMeasureMent() 
{
	UpdateData();

#ifdef _Demo
	m_dReadPV = m_dSetPoint;
#else
	
#endif
	// SV
	CString csSV = _T("");
	csSV.Format("%5.2f", m_dSetPoint );

	// Prot
	CString csGetProt = _T("");
	int nSize = m.m_WestControllerList.m_List.GetSize();
	int nSel  = m_cbxControllerSel.GetCurSel();
	CString csName = _T("");
	m_cbxControllerSel.GetLBText( nSel, csName );
	for(int i=0;i<nSize;i++)
	{
		CString csFinName = m.m_WestControllerList.m_List.GetAt(i).csFunctionName;
		if( csFinName == csName )
		{
			CString csName = _T("");
			csName.Format("%s", m.m_WestControllerList.m_List.GetAt(i).csFunctionName );
			csGetProt = csName;
			break;
		}
	}
	//

	// Offset
	// Measument 10.5,  Present 5.5 -> -5.0
	CString csMeasument = _T("");
	m_wndMeasureTemperature.GetWindowText( csMeasument );
	double dMeasument = atof( csMeasument );
	double dOffset = 0.0;
	//
	double dLkOffset = 0.0;
	f.GetWestLoopupTableTemperature( csSV, csGetProt, dLkOffset );
	//
	dOffset = dMeasument - m_dReadPV + (dLkOffset);
	CString csOffset = _T("");
	csOffset.Format("%5.2f", dOffset );

	//
	m.m_DriveWest.AddCmd(m_WestID+1, enOffset, dOffset );

	f.SetWestLoopupTableTemperature(csSV, csGetProt, csOffset );
}
void CDlgTemperatureCalibration::OnSSite1() 
{
	CalibrationMeasureMent();
}
void CDlgTemperatureCalibration::ChangePage()
{
	SetSyncUI();

	SetIOSyncUI();
}

void CDlgTemperatureCalibration::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	if(bShow)
	{
	
	}

	CDialog::OnShowWindow(bShow, nStatus);	
}
