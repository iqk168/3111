// DlgWestTool.cpp : implementation file
//

#include "stdafx.h"
#include "deer.h"
#include "DlgWestTool.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgWestTool dialog


CDlgWestTool::CDlgWestTool(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgWestTool::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgWestTool)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	m_iWestID = 1;
}


void CDlgWestTool::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgWestTool)
	DDX_Control(pDX, IDC_R_OFFSET,			m_wndOffset);
	DDX_Control(pDX, IDC_R_PV,				m_wndPv);
	DDX_Control(pDX, IDC_R_SV,				m_wndSv);
	DDX_Control(pDX, IDC_F_SEL_WEST,		m_wndWestSel);
	DDX_Control(pDX, IDOK,					m_btnOK);
	DDX_Control(pDX, IDCANCEL,				m_btnCancel);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgWestTool, CDialog)
	//{{AFX_MSG_MAP(CDlgWestTool)
	ON_WM_TIMER()
	ON_CBN_EDITCHANGE(IDC_F_SEL_WEST, OnEditchangeFSelWest)
	ON_CBN_SELCHANGE(IDC_F_SEL_WEST, OnSelchangeFSelWest)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgWestTool message handlers

void CDlgWestTool::OnOK() 
{
	m.Info.bSubDlgOpen = false;
	f.UpdateButtonState();

	KillTimer( ID_TIME_WEST_TEMP );
	
	CDialog::OnOK();
}

void CDlgWestTool::OnCancel() 
{
	m.Info.bSubDlgOpen = false;
	f.UpdateButtonState();

	KillTimer( ID_TIME_WEST_TEMP );
	
	CDialog::OnCancel();
}

BOOL CDlgWestTool::PreTranslateMessage(MSG* pMsg) 
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

BOOL CDlgWestTool::OnInitDialog() 
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
	
	InitWestSel();

	InitUI();

	SetTimer( ID_TIME_WEST_TEMP, 50, NULL );

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgWestTool::InitWestSel()
{
	for(int i=0;i<_MaxWestDevice;i++)
	{
		CString csInstrumnet = _T("");
		csInstrumnet.Format("West ID %d", i+1);
		m_wndWestSel.AddString( csInstrumnet );
	}

	m_wndWestSel.SetCurSel(0);
}
void CDlgWestTool::InitUI()
{
	m_wndOffset.SetText("", 10, "Arial Black", DT_CENTER | DT_VCENTER);
	m_wndOffset.SetNewBkColor(ST_BLACK);
	m_wndOffset.SetNewTextColor(ST_YELLOW);
	m_wndOffset.SetNewText("");

	m_wndSv.SetText("", 10, "Arial Black", DT_CENTER | DT_VCENTER);
	m_wndSv.SetNewBkColor(ST_BLACK);
	m_wndSv.SetNewTextColor(ST_GREEN);
	m_wndSv.SetNewText("");	

	m_wndPv.SetText("", 10, "Arial Black", DT_CENTER | DT_VCENTER);
	m_wndPv.SetNewBkColor(ST_BLACK);
	m_wndPv.SetNewTextColor(ST_RED);
	m_wndPv.SetNewText("");		
}
void CDlgWestTool::TemperatureQuery()
{
#ifdef _Demo
	
	CString csSV = _T("");
	CString csPV = _T("");
	CString csOffset = _T("");

	double dSV = 25.1;
	double dPV = 26.2;
	double dOffset = 1.1;

	csSV.Format("%5.2f", dSV);
	csPV.Format("%5.2f", dPV);
	csOffset.Format("%5.2f", dOffset);

	m_wndPv.SetNewText(csPV);
	m_wndSv.SetNewText(csSV);
	m_wndOffset.SetNewText(csOffset);

#else
	
	double dPV[_MaxWestDevice];
	double dSV[_MaxWestDevice];
	double dOffset[_MaxWestDevice];

	m.m_DriveWest.GetValue( dPV, dSV );
	m.m_DriveWest.GetOffsetValue( dOffset );

	CString csSV = _T("");
	CString csPV = _T("");
	CString csOffset = _T("");

	double ddSV = dSV[m_iWestID];
	double ddPV = dPV[m_iWestID];
	double ddOffset = dOffset[m_iWestID];

	csSV.Format("%5.2f", ddSV);
	csPV.Format("%5.2f", ddPV);
	csOffset.Format("%5.2f", ddOffset);

	m_wndPv.SetNewText(csPV);
	m_wndSv.SetNewText(csSV);
	m_wndOffset.SetNewText(csOffset);

#endif

}
void CDlgWestTool::OnTimer(UINT nIDEvent) 
{
	switch(nIDEvent)
	{
	case ID_TIME_WEST_TEMP:
		TemperatureQuery();
		break;
	}	
	CDialog::OnTimer(nIDEvent);
}

void CDlgWestTool::OnEditchangeFSelWest() 
{
	
}

void CDlgWestTool::OnSelchangeFSelWest() 
{
	m_iWestID = m_wndWestSel.GetCurSel();
	m_iWestID++;
	// Debug
//	CString csMsg = _T("");
//	csMsg.Format("ID = %d", m_iWestID );
//	AfxMessageBox( csMsg );
}
