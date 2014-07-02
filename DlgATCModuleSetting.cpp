// DlgATCModuleSetting.cpp : implementation file
//

#include "stdafx.h"
#include "deer.h"
#include "DlgATCModuleSetting.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgATCModuleSetting dialog


CDlgATCModuleSetting::CDlgATCModuleSetting(CString csFile, CWnd* pParent /*=NULL*/)
	: CDialog(CDlgATCModuleSetting::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgATCModuleSetting)
	m_dChangeStableTime = 0.0;
	m_dTemperatureRange = 0.0;
	m_csFile = csFile + _Atc2;
	//}}AFX_DATA_INIT
}


void CDlgATCModuleSetting::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgATCModuleSetting)
	DDX_Control(pDX, IDC_FILE_NAME,				m_wndFileName);
	DDX_Control(pDX, IDOK,						m_btnOK);
	DDX_Control(pDX, IDCANCEL,					m_btnCancel);
	DDX_Text(pDX, IDC_P_CHANGE_STABLE_TIME,		m_dChangeStableTime);
	DDX_Text(pDX, IDC_P_TEMP_RANGE,				m_dTemperatureRange);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgATCModuleSetting, CDialog)
	//{{AFX_MSG_MAP(CDlgATCModuleSetting)
	ON_WM_SHOWWINDOW()
	ON_EN_CHANGE(IDC_P_TEMP_RANGE, OnChangePTempRange)
	ON_EN_CHANGE(IDC_P_CHANGE_STABLE_TIME, OnChangePChangeStableTime)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgATCModuleSetting message handlers

BOOL CDlgATCModuleSetting::PreTranslateMessage(MSG* pMsg) 
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

BOOL CDlgATCModuleSetting::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// init button 
	m_btnOK.SetIcon(IDI_SAVE);
	m_btnOK.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnOK.SetFlat(FALSE);
	
	m_btnCancel.SetIcon(IDI_CANCEL);
	m_btnCancel.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnCancel.SetFlat(FALSE);

	InitValue();

	m_fChange = false;
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
void CDlgATCModuleSetting::InitValue()
{
	double dTemperatureRangeValue = 0.0;
	double dChangeStableTimeValue = 0.0;
	f.LoadATCModuleMultiSVSetting( m_csFile, dTemperatureRangeValue, dChangeStableTimeValue );

	m_dTemperatureRange = dTemperatureRangeValue;
	m_dChangeStableTime = dChangeStableTimeValue;

	UpdateData(FALSE);

	//
#ifdef _Demo
	m_wndFileName.SetWindowText( m_csFile );
#endif

}
bool CDlgATCModuleSetting::SaveData()
{
	UpdateData();

	bool bOK = true;
	bool bTempRange = true;
	bool bChangeStable = true;
	if( m_dTemperatureRange >= _MaxATCModuleTempRange || 
		m_dTemperatureRange <= _MinATCModuleTempRange )
		bTempRange = false;

	if( m_dChangeStableTime >= _MaxATCModuleChangeStableTime ||
		m_dChangeStableTime <= _MinATCModuleChangeStableTime )
		bChangeStable = false;

	if( !bChangeStable || !bTempRange )
		bOK = false;

	CString csMsg = _T("");
	if( !bTempRange )
	{
		CString csInfo = _T("");
		csInfo.Format("Temperature is out of range [%5.2f~%5.2f]\r\n", 
			_MinATCModuleTempRange, _MaxATCModuleTempRange);
		csMsg += csInfo;
	}
	if( !bChangeStable )
	{
		CString csInfo = _T("");
		csInfo.Format("Change Stable Time is out of range [%5.2f~%5.2f]", 
			_MinATCModuleChangeStableTime, _MaxATCModuleChangeStableTime);
		csMsg += csInfo;
	}

	if(!bOK)
		AfxMessageBox( csMsg );
	else
	{
		// Save Data
		f.SaveATCModuleMultiSVSetting(m_csFile, m_dTemperatureRange, m_dChangeStableTime);
	}

	return bOK;
}
void CDlgATCModuleSetting::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);	
}

void CDlgATCModuleSetting::OnChangePTempRange() 
{
	m_fChange = true;
}

void CDlgATCModuleSetting::OnChangePChangeStableTime() 
{
	m_fChange = true;	
}

void CDlgATCModuleSetting::OnOK() 
{
	if(!SaveData())
		return;

	CDialog::OnOK();
}

void CDlgATCModuleSetting::OnCancel() 
{
	if( m_fChange )
	{
		if(IDYES != AfxMessageBox("Data is modified. Save?\n",
			MB_YESNO|MB_ICONEXCLAMATION))
		{

			CDialog::OnCancel();
		}
		else
			OnOK();
	}
	else
	{
		CDialog::OnCancel();
	}	
	CDialog::OnCancel();
}
