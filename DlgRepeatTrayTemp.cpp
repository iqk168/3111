// DlgRepeatTrayTemp.cpp : implementation file
//

#include "stdafx.h"
#include "deer.h"
#include "DlgRepeatTrayTemp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgRepeatTrayTemp dialog


CDlgRepeatTrayTemp::CDlgRepeatTrayTemp(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgRepeatTrayTemp::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgRepeatTrayTemp)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgRepeatTrayTemp::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgRepeatTrayTemp)
	DDX_Control(pDX, IDC_LIST,	m_List);
	DDX_Control(pDX, IDCANCEL,	m_btnCancel);
	DDX_Control(pDX, IDOK,		m_btnOK);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgRepeatTrayTemp, CDialog)
	//{{AFX_MSG_MAP(CDlgRepeatTrayTemp)
	ON_NOTIFY ( NM_CUSTOMDRAW, IDC_LIST,		OnCustomdrawList )
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgRepeatTrayTemp message handlers

BOOL CDlgRepeatTrayTemp::PreTranslateMessage(MSG* pMsg) 
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

BOOL CDlgRepeatTrayTemp::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// init button 
	m_btnOK.SetIcon(IDI_SAVE);
	m_btnOK.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnOK.SetFlat(FALSE);

	m_btnCancel.SetIcon(IDI_CANCEL);;
	m_btnCancel.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnCancel.SetFlat(FALSE);
	
	//
	Style();

	//
	ShowTitle();

	//
	InitTemp();

	//

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgRepeatTrayTemp::Style()
{
	LONG lStyle;
	lStyle = GetWindowLong(m_List.m_hWnd, GWL_STYLE);
	lStyle &= ~LVS_TYPEMASK; 
	lStyle |= LVS_REPORT; 
	SetWindowLong(m_List.m_hWnd, GWL_STYLE, lStyle);
	
	DWORD dwStyle = m_List.GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT;
	dwStyle |= LVS_EX_GRIDLINES;
//	dwStyle |= LVS_EX_CHECKBOXES;
	m_List.SetExtendedStyle(dwStyle);
}

void CDlgRepeatTrayTemp::InitTemp()
{
	int iSize = m.m_RepeatTrayTemperData.GetSize();
	for(int i=0;i<iSize;i++)
	{
		// Format
		CString strResource = _T("");
		strResource.Format("%d", i+1);
		CString strSVResource = _T("");
		strSVResource.Format("%5.2f", m.m_RepeatTrayTemperData.GetAt(i).m_dSV );
		CString strSoakResurce = __T("");
		strSoakResurce.Format("%5.2f", m.m_RepeatTrayTemperData.GetAt(i).m_dSoakingTime );
		CString strStableResurce = _T("");
		strStableResurce.Format("%5.2f", m.m_RepeatTrayTemperData.GetAt(i).m_dStableTime );
		CString strToleranceResurce = _T("");
		strToleranceResurce.Format("%5.2f", m.m_RepeatTrayTemperData.GetAt(i).m_dTolerance );
		//	
		
		m_List.InsertItem(LVIF_TEXT|LVIF_STATE, i, 
			strResource, LVIS_FOCUSED, LVIS_FOCUSED, 0, 0);
		m_List.SetItemText(i, 1, strSVResource );
		m_List.SetItemText(i, 2, strSoakResurce );
		m_List.SetItemText(i, 3, strStableResurce );
		m_List.SetItemText(i, 4, strToleranceResurce );
	}
}
void CDlgRepeatTrayTemp::ShowTitle()
{
	// Make the necessary initializations
	m_List.InsertColumn(0, "Item",				LVCFMT_LEFT, 100);
	m_List.InsertColumn(1, "SV(deg)",			LVCFMT_LEFT, 150);
	m_List.InsertColumn(2, "Soak Time(secs)",	LVCFMT_LEFT, 150);
	m_List.InsertColumn(3, "Stable Time(secs)",	LVCFMT_LEFT, 150);
	m_List.InsertColumn(4, "Tolerance(deg)",	LVCFMT_LEFT, 130);

	m_List.SetReadOnlyColumns(0);
	m_List.SetReadOnlyColumns(1);
	m_List.SetReadOnlyColumns(2);
	m_List.SetReadOnlyColumns(3);
	m_List.SetReadOnlyColumns(4);

	CString strValidChars = "-0123456789.";
	m_List.SetValidEditCtrlCharacters(strValidChars);

	m_List.SetExtendedStyle(LVS_EX_FULLROWSELECT);	
}
void CDlgRepeatTrayTemp::OnCustomdrawList ( NMHDR* pNMHDR, LRESULT* pResult )
{
	NMLVCUSTOMDRAW* pLVCD = reinterpret_cast<NMLVCUSTOMDRAW*>( pNMHDR );
	
    // Take the default processing unless 
    // we set this to something else below.
    *pResult = CDRF_DODEFAULT;
	
    // First thing - check the draw stage. If it's the control's prepaint
    // stage, then tell Windows we want messages for every item.
	
    if ( CDDS_PREPAINT == pLVCD->nmcd.dwDrawStage )
	{
        *pResult = CDRF_NOTIFYITEMDRAW;
	}
    else if ( CDDS_ITEMPREPAINT == pLVCD->nmcd.dwDrawStage )
	{
        // This is the notification message for an item.  We'll request
        // notifications before each subitem's prepaint stage.
		
        *pResult = CDRF_NOTIFYSUBITEMDRAW;
	}
    else if ( (CDDS_ITEMPREPAINT | CDDS_SUBITEM) == pLVCD->nmcd.dwDrawStage )
	{
        // This is the prepaint stage for a subitem. Here's where we set the
        // item's text and background colors. Our return value will tell 
        // Windows to draw the subitem itself, but it will use the new colors
        // we set here.
        // The text color will cycle through red, green, and light blue.
        // The background color will be light blue for column 0, red for
        // column 1, and black for column 2.
		
        COLORREF crText, crBkgnd;
        
        if ( 0 == pLVCD->iSubItem )
		{
			crText	= ST_BLACK;
			crBkgnd = ST_WHITE;
		}
        else if ( 1 == pLVCD->iSubItem )
		{
			crText	= ST_GREEN;
			crBkgnd = ST_WHITE;
		}
		else if ( 2 == pLVCD->iSubItem )
		{
			crText	= ST_RED;
			crBkgnd = ST_WHITE;
		}
        else
		{
			crText	= RGB(128,128,255);
			crBkgnd = ST_WHITE;
		}
		
        // Store the colors back in the NMLVCUSTOMDRAW struct.
        pLVCD->clrText = crText;
        pLVCD->clrTextBk = crBkgnd;
		
        // Tell Windows to paint the control itself.
        *pResult = CDRF_DODEFAULT;
	}
}
void CDlgRepeatTrayTemp::OnOK() 
{
	CDialog::OnOK();
}

void CDlgRepeatTrayTemp::OnCancel() 
{
	
	CDialog::OnCancel();
}
