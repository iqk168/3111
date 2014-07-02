// DlgTemperatureTool.cpp : implementation file
//

#include "stdafx.h"
#include "deer.h"
#include "DlgTemperatureTool.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgTemperatureTool dialog


CDlgTemperatureTool::CDlgTemperatureTool(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgTemperatureTool::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgTemperatureTool)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	m_WestID = 0;
}


void CDlgTemperatureTool::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgTemperatureTool)
	DDX_Control(pDX, IDC_E_CONTROLER, m_cbxControllerSel);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgTemperatureTool, CDialog)
	//{{AFX_MSG_MAP(CDlgTemperatureTool)
	ON_BN_CLICKED(IDC_F_CLEAR_OFFSET, OnFClearOffset)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgTemperatureTool message handlers



BOOL CDlgTemperatureTool::PreTranslateMessage(MSG* pMsg) 
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

BOOL CDlgTemperatureTool::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	InitController();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
void CDlgTemperatureTool::InitController()
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
void CDlgTemperatureTool::FunctionClearOffset()
{
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
	double dOffset = 0.0;
	m.m_DriveWest.AddCmd(m_WestID+1, enOffset, dOffset );
}
void CDlgTemperatureTool::OnFClearOffset() 
{
	FunctionClearOffset();
}
