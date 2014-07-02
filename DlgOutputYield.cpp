// DlgOutputYield.cpp : implementation file
//

#include "stdafx.h"
#include "deer.h"
#include "DlgOutputYield.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgOutputYield dialog


CDlgOutputYield::CDlgOutputYield(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgOutputYield::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgOutputYield)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgOutputYield::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgOutputYield)
	DDX_Control(pDX, IDC_CATEGORY1, m_listData);
	DDX_Control(pDX, IDOK,			m_btnOK);
	DDX_Control(pDX, IDCANCEL,		m_btnCancel);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgOutputYield, CDialog)
	//{{AFX_MSG_MAP(CDlgOutputYield)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgOutputYield message handlers

void CDlgOutputYield::OnOK() 
{
	
	CDialog::OnOK();
}

void CDlgOutputYield::OnCancel() 
{
	
	CDialog::OnCancel();
}

BOOL CDlgOutputYield::PreTranslateMessage(MSG* pMsg) 
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

BOOL CDlgOutputYield::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// init button 
	m_btnOK.SetIcon(IDI_OK);;
	m_btnOK.SetAlign(CButtonST::ST_ALIGN_VERT);;
	m_btnOK.SetFlat(FALSE);
	
	m_btnCancel.SetIcon(IDI_CANCEL);
	m_btnCancel.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnCancel.SetFlat(FALSE);

	InitValue();

	Style();

	ShowTitle();

	ShowData();	

	CenterWindow();

	SetTimer( ID_TIME_OUTPUT_YIELD, 50, NULL );

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
void CDlgOutputYield::InitValue()
{

}
void CDlgOutputYield::Style()
{
	LONG lStyle;
	lStyle = GetWindowLong(m_listData.m_hWnd, GWL_STYLE);
	lStyle &= ~LVS_TYPEMASK; 
	lStyle |= LVS_REPORT; 
	SetWindowLong(m_listData.m_hWnd, GWL_STYLE, lStyle);
	
	DWORD dwStyle = m_listData.GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT;
	dwStyle |= LVS_EX_GRIDLINES;
//	dwStyle |= LVS_EX_CHECKBOXES;
	m_listData.SetExtendedStyle(dwStyle); 
}
void CDlgOutputYield::ShowTitle()
{
	m_listData.InsertColumn(0, "Serial");
	m_listData.InsertColumn(1, "Code");
	m_listData.InsertColumn(2, "Counter");
	m_listData.InsertColumn(3, "Rate(%)");

	m_listData.SetColumnWidth(0, 100);
	m_listData.SetColumnWidth(1, 160);
	m_listData.SetColumnWidth(2, 100);
	m_listData.SetColumnWidth(3, 100);
}
void CDlgOutputYield::ShowData()
{
	m_listData.DeleteAllItems();
	int iSize = m.m_OutputYieldCounter.GetSize();

	// get total
	long m_lTotal = 0;
	for(int i=0;i<iSize;i++)
	{
		long m_lCounter = m.m_OutputYieldCounter.GetAt(i).m_lCodeCounter;
		m_lTotal += m_lCounter;
	}

	// display data
	for( i=0;i<iSize;i++)
	{
		tagOutputYield m_data;
		m_data.m_csCode = m.m_OutputYieldCounter.GetAt(i).m_csCode;
		m_data.m_lCodeCounter = m.m_OutputYieldCounter.GetAt(i).m_lCodeCounter;
		CString m_csSerial= _T("");
		m_csSerial.Format("%d", i+1);
		m_listData.InsertItem(i, m_csSerial);
		m_listData.SetItemText(i, 1, m_data.m_csCode);
		CString m_csCounter = _T("");
		m_csCounter.Format("%d", m_data.m_lCodeCounter);
		m_listData.SetItemText(i, 2, m_csCounter);

		// rate
		CString m_csRate = _T("");
		if( m_data.m_lCodeCounter != 0 && m_lTotal != 0 )
		{
			double m_dCounter = m_data.m_lCodeCounter;
			double m_dTotal = m_lTotal;
			m_csRate.Format("%5.2f", (m_dCounter / m_dTotal) * 100 );
		}
		else
			m_csRate.Format("%5.2f", 0.0);
		m_listData.SetItemText(i, 3, m_csRate);

	}
}
void CDlgOutputYield::ShowValue()
{
	int iSize = m.m_OutputYieldCounter.GetSize();

	// get total
	long m_lTotal = 0;
	for(int i=0;i<iSize;i++)
	{
		long m_lCounter = m.m_OutputYieldCounter.GetAt(i).m_lCodeCounter;
		m_lTotal += m_lCounter;
	}

	// display data
	for( i=0;i<iSize;i++)
	{
		tagOutputYield m_data;
		m_data.m_lCodeCounter = m.m_OutputYieldCounter.GetAt(i).m_lCodeCounter;

		// counter
		CString m_csCounter = _T("");
		m_csCounter.Format("%d", m_data.m_lCodeCounter);
		m_listData.SetItemText(i, 2, m_csCounter);

		// rate
		CString m_csRate = _T("");
		if( m_data.m_lCodeCounter != 0 && m_lTotal != 0 )
		{
			double m_dCounter = m_data.m_lCodeCounter;
			double m_dTotal = m_lTotal;
			m_csRate.Format("%5.2f", (m_dCounter / m_dTotal) * 100 );
		}
		else
			m_csRate.Format("%5.2f", 0.0);
		m_listData.SetItemText(i, 3, m_csRate);
	}
}
void CDlgOutputYield::OnTimer(UINT nIDEvent) 
{
	switch(nIDEvent)
	{
	case ID_TIME_OUTPUT_YIELD:
		{
			ShowValue();
		}
		break;
	default:
		break;
	}	
	CDialog::OnTimer(nIDEvent);
}
