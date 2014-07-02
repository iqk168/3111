// DlgManualContactTorque.cpp : implementation file
//

#include "stdafx.h"
#include "deer.h"
#include "DlgManualContactTorque.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgManualContactTorque dialog


CDlgManualContactTorque::CDlgManualContactTorque(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgManualContactTorque::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgManualContactTorque)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgManualContactTorque::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgManualContactTorque)
	DDX_Control(pDX, IDC_WRITE_TO_CONT, m_btnSet);
	DDX_Control(pDX, IDC_F_FORCE,		m_wndForce);
	DDX_Control(pDX, IDC_P_POGO_FORCE,	m_cbxPogoForce);
	DDX_Control(pDX, IDC_P_POGO_COUNT,	m_cbxPogoCount);
	DDX_Control(pDX, IDOK,				m_btnOK);
	DDX_Control(pDX, IDCANCEL,			m_btnCancel);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgManualContactTorque, CDialog)
	//{{AFX_MSG_MAP(CDlgManualContactTorque)
	ON_CBN_SELCHANGE(IDC_P_POGO_COUNT, OnSelchangePPogoCount)
	ON_CBN_SELCHANGE(IDC_P_POGO_FORCE, OnSelchangePPogoForce)
	ON_BN_CLICKED(IDC_WRITE_TO_CONT, OnWriteToCont)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgManualContactTorque message handlers

void CDlgManualContactTorque::OnOK() 
{
	if( m.UI.FileMain != "" )
	{
		SaveDataToFile( m.UI.FileMain );
		f.LoadPogoParameter();
	}

	CDialog::OnOK();
}

void CDlgManualContactTorque::OnCancel() 
{
	if( m.UI.FileMain != "" )
	{		
		f.LoadPogoParameter();
	}	
	CDialog::OnCancel();
}

BOOL CDlgManualContactTorque::PreTranslateMessage(MSG* pMsg) 
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

BOOL CDlgManualContactTorque::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// init button 
	m_btnOK.SetIcon(IDI_SAVE);
	m_btnOK.SetAlign(CButtonST::ST_ALIGN_VERT);;
	m_btnOK.SetFlat(FALSE);
	
	m_btnCancel.SetIcon(IDI_CANCEL);
	m_btnCancel.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnCancel.SetFlat(FALSE);

	m_btnSet.SetIcon(IDI_DEBUG);
	m_btnSet.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnSet.SetFlat(FALSE);

	InitUI();

	InitValue();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
void CDlgManualContactTorque::InitUI()
{
	// Pogo Count
	for(int i=0;i<_MaxPogoCount;i++)
	{
		CString csPogoCount = _T("");
		csPogoCount.Format("%d", i+1);
		m_cbxPogoCount.AddString(csPogoCount);
	}

	// Pogo Force
	for(int j=0;j<_MaxPogoForce;j++)
	{
		CString csPogoForce = _T("");
		csPogoForce.Format("%d", j+1);
		m_cbxPogoForce.AddString(csPogoForce);
	}

	//
	m_cbxPogoCount.SetCurSel(0);
	m_cbxPogoForce.SetCurSel(0);

}
void CDlgManualContactTorque::InitValue()
{
	// Pogo pin counter
	CString csPogoCount = _T("");
	csPogoCount.Format("%d", m.m_TsFolatingParameter.iPogoCount );
	int iFindCount = m_cbxPogoCount.FindString(0, csPogoCount);
	if( iFindCount != LB_ERR )
		m_cbxPogoCount.SetCurSel( iFindCount );

	// Pogo pin forces
	CString csPogoForce = _T("");
	csPogoForce.Format("%d", m.m_TsFolatingParameter.iPogoForce );
	int iFindForce = m_cbxPogoForce.FindString(0, csPogoForce );
	if( iFindForce != LB_ERR )
		m_cbxPogoForce.SetCurSel( iFindForce );

	//
	ConvertKgf();
}
void CDlgManualContactTorque::SaveDataToFile(CString csTrayFileName)
{
	CString csFile = _T("");
	csFile = m.FilePath.TrayFilesPath + csTrayFileName;

	f.SaveSetting(csFile, "Ts Floating", "Pogo Counter",	m_TsFloatingParameter.iPogoCount );
	f.SaveSetting(csFile, "Ts Floating", "Pogo Force(g.)",	m_TsFloatingParameter.iPogoForce );
}
void CDlgManualContactTorque::ConvertKgf() 
{
	int m_iSelPogoCount = m_cbxPogoCount.GetCurSel();
	int m_iSelPogoForce = m_cbxPogoForce.GetCurSel();

	CString csPogoCount = _T("");
	CString csPogoForce = _T("");

	m_cbxPogoCount.GetLBText(m_iSelPogoCount, csPogoCount);
	m_cbxPogoForce.GetLBText(m_iSelPogoForce, csPogoForce);

	// Debug
//	CString csMsg = _T("");
//	csMsg.Format("Count: %s, Force: %s", csPogoCount, csPogoForce);
//	AfxMessageBox( csMsg );

	CString csKg = _T("");
	csKg.Format("%5.2f", (atof(csPogoCount) * atof(csPogoForce)) / 1000. );
	m_wndForce.SetWindowText( csKg );

}
void CDlgManualContactTorque::OnSelchangePPogoCount() 
{
	ConvertKgf();	
}

void CDlgManualContactTorque::OnSelchangePPogoForce() 
{
	ConvertKgf();	
}

void CDlgManualContactTorque::OnWriteToCont() 
{
	double dTorqueValue = 0.0;
	CString csValue = _T("");
	m_wndForce.GetWindowText( csValue );
	dTorqueValue = atof( csValue );
	dTorqueValue = dTorqueValue * m.m_TsFolatingConvert.dTsFloatingConvert;

	//
	theApp.m_tIORemote.SetTorqueValue( dTorqueValue );	
}
