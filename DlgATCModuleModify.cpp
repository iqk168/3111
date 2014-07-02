// DlgATCModuleModify.cpp : implementation file
//

#include "stdafx.h"
#include "deer.h"
#include "DlgATCModuleModify.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgATCModuleModify dialog


CDlgATCModuleModify::CDlgATCModuleModify(CString csFile, CWnd* pParent /*=NULL*/)
	: CDialog(CDlgATCModuleModify::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgATCModuleModify)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	m_csFile = csFile;
}


void CDlgATCModuleModify::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgATCModuleModify)
	DDX_Control(pDX, IDC_DATA,		m_listData);
	DDX_Control(pDX, IDC_FILE,		m_wndFile);
	DDX_Control(pDX, IDOK,			m_btnOK);
	DDX_Control(pDX, IDCANCEL,		m_btnCancel);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgATCModuleModify, CDialog)
	//{{AFX_MSG_MAP(CDlgATCModuleModify)
	ON_NOTIFY ( NM_CUSTOMDRAW, IDC_DATA,	OnCustomdrawList )
	ON_NOTIFY(NM_RCLICK, IDC_DATA,			OnRclickList)
	ON_WM_SHOWWINDOW()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgATCModuleModify message handlers

BOOL CDlgATCModuleModify::PreTranslateMessage(MSG* pMsg) 
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

BOOL CDlgATCModuleModify::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// init button 
	m_btnOK.SetIcon(IDI_SAVE);
	m_btnOK.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnOK.SetFlat(FALSE);
	
	m_btnCancel.SetIcon(IDI_CANCEL);
	m_btnCancel.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnCancel.SetFlat(FALSE);

	//
	Style();

	//
	InitValue();

	//
	InitGrid();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
void CDlgATCModuleModify::InitValue()
{
	m_wndFile.SetText(m_csFile, 10, "Arial Black", DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	m_wndFile.SetNewBkColor(ST_WHITE);
}
void CDlgATCModuleModify::InitGrid()
{
	// Make the necessary initializations
	m_listData.InsertColumn(0, "Item",			LVCFMT_LEFT, 100);
	m_listData.InsertColumn(1, "Temperature",	LVCFMT_LEFT, 100);
	m_listData.InsertColumn(2, "Soak TimeSV",	LVCFMT_LEFT, 100);

	m_listData.SetReadOnlyColumns(0);

	CString strValidChars = "-0123456789.";
	m_listData.SetValidEditCtrlCharacters(strValidChars);
//	m_listData.EnableVScroll(); 

	m_listData.SetExtendedStyle(LVS_EX_FULLROWSELECT);	
}
void CDlgATCModuleModify::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);	
}
void CDlgATCModuleModify::Style()
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
void CDlgATCModuleModify::OnRclickList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	CMenu obMenu;
	obMenu.LoadMenu(IDR_LIST_POPUP); 

	CMenu* pPopupMenu = obMenu.GetSubMenu(0);
	ASSERT(pPopupMenu); 
	
	// Get the cursor position
	CPoint obCursorPoint = (0, 0);
	
	GetCursorPos(&obCursorPoint);

	if (0 >= m_listData.GetSelectedCount())
	{
		pPopupMenu->EnableMenuItem(ID_LST_DELETE, MF_BYCOMMAND | MF_GRAYED | MF_DISABLED); 
	}
	else
	{
		pPopupMenu->EnableMenuItem(ID_LST_DELETE, MF_BYCOMMAND | MF_ENABLED);
	}

	// Track the popup menu
	pPopupMenu->TrackPopupMenu(TPM_LEFTALIGN|TPM_LEFTBUTTON|TPM_RIGHTBUTTON, obCursorPoint.x, 
									obCursorPoint.y, this);

	*pResult = 0;
}
void CDlgATCModuleModify::OnCustomdrawList ( NMHDR* pNMHDR, LRESULT* pResult )
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
