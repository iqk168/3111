// DlgManualContactTorqueKgf.cpp : implementation file
//

#include "stdafx.h"
#include "deer.h"
#include "DlgManualContactTorqueKgf.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgManualContactTorqueKgf dialog


CDlgManualContactTorqueKgf::CDlgManualContactTorqueKgf(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgManualContactTorqueKgf::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgManualContactTorqueKgf)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgManualContactTorqueKgf::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgManualContactTorqueKgf)
	DDX_Control(pDX, IDC_F_KGF,			m_cbxKgf);
	DDX_Control(pDX, IDC_F_FORCE,		m_wndContactForce);
	DDX_Control(pDX, IDC_WRITE_TO_CONT, m_btnSet);
	DDX_Control(pDX, IDCANCEL,			m_btnCancel);
	DDX_Control(pDX, IDOK,				m_btnOK);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgManualContactTorqueKgf, CDialog)
	//{{AFX_MSG_MAP(CDlgManualContactTorqueKgf)
	ON_BN_CLICKED(IDC_WRITE_TO_CONT, OnWriteToCont)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgManualContactTorqueKgf message handlers

BOOL CDlgManualContactTorqueKgf::PreTranslateMessage(MSG* pMsg) 
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

BOOL CDlgManualContactTorqueKgf::OnInitDialog() 
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
	
	InitCbxKgf();

	//
	InitValue();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
void CDlgManualContactTorqueKgf::InitValue()
{
	CString csValue = _T("");
	csValue.Format("%d", m.m_TsFolatingParameter.iPogoTorqueForce);
	
	/*
	int m_iValue = m_cbxKgf.FindString(0, csValue );
	if( m_iValue != 0 )
		m_cbxKgf.SetCurSel( m_iValue );
	*/

	// 1.0Al
	int m_iValue = 0;
	int iSize = m_cbxKgf.GetCount();
	for(int i=0;i<iSize;i++)
	{
		CString csTemp = _T("");
		m_cbxKgf.GetLBText(i, csTemp);
		if( csValue == csTemp )
		{
			m_iValue = i;
			i = iSize;
		}
	}
	
	if( m_iValue > 0 )
		m_cbxKgf.SetCurSel( m_iValue );
	else
		m_cbxKgf.SetCurSel( 0 );
}
void CDlgManualContactTorqueKgf::InitCbxKgf()
{
	int m_iMax = m.Setting.m_iTorqueHighLimit;
	int m_iMin = m.Setting.m_iTorqueLowLimit;
	for(int i=m_iMin;i<=m_iMax;i++)
	{
		CString csKgfValue = _T("");
		csKgfValue.Format("%d", i);
		m_cbxKgf.AddString( csKgfValue );
	}
}
bool CDlgManualContactTorqueKgf::SaveData()
{
	bool bOK = true;

	if( m.UI.FileMain != "" )
	{
		UpdateData();	
		
		int iCurSel = m_cbxKgf.GetCurSel();
		CString m_csValue = _T("");
		m_cbxKgf.GetLBText( iCurSel, m_csValue );
		double m_dSetTorque = atof( m_csValue );
		int m_iSetTorque = atoi( m_csValue );
		
		double m_dTorque = ( m_dSetTorque - m.m_TorqueToolSet.dbValue ) / m.m_TorqueToolSet.daValue;
		m_dTorque = m_dTorque * 20;

		//
		CString csFile = _T("");
		csFile = m.FilePath.TrayFilesPath + m.UI.FileMain;
		f.SaveSetting(csFile, "Ts Floating", "Pogo Force(kgf.)",	m_iSetTorque );
		f.LoadPogoParameter();
	}

	return bOK;
}
void CDlgManualContactTorqueKgf::OnOK() 
{
	SaveData();

	f.LoadPogoParameter();

	CDialog::OnOK();
}

void CDlgManualContactTorqueKgf::OnWriteToCont() 
{
	UpdateData();	

	int iCurSel = m_cbxKgf.GetCurSel();
	CString m_csValue = _T("");
	m_cbxKgf.GetLBText( iCurSel, m_csValue );
	double m_dSetTorque = atof( m_csValue );

	double m_dTorque = ( m_dSetTorque - m.m_TorqueToolSet.dbValue ) / m.m_TorqueToolSet.daValue;
	m_dTorque = m_dTorque * 20;

	theApp.m_tIORemote.SetTorqueValue( m_dTorque );
}

void CDlgManualContactTorqueKgf::OnCancel() 
{

	CDialog::OnCancel();
}
