// TrayMapCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "TrayMapCtrl.h"
#include "memdc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTrayMapCtrl

CTrayMapCtrl::CTrayMapCtrl()
: m_traymap(), m_binmap()
{
	m_bEnableInfo	= false;
	m_bEnableNumber	= false;	

	//
	m_bEnableTips	= false;

	//
	m_bShowText		= TRUE;
	m_strText.Empty();
	m_colFore		= ::GetSysColor(COLOR_HIGHLIGHT);
	m_colBk			= RGB(255,255,255);
	m_colTextFore	= ::GetSysColor(COLOR_HIGHLIGHT);
	m_colTextBk		= ::GetSysColor(COLOR_WINDOW);
	
	m_col = m_row = 1;
	m_traymap.resize(m_row, std::vector<int>(m_col, 0));
	m_binmap.resize(m_row, std::vector<int>(m_col, 0));

	m_modified = false;

	m_cpStartPos = 0;
	m_cpEndPos   = 0;

	// Chip Tray
	m_ChipTray	 = -1;
	m_chipcol	 = -1;
	m_chiprow	 = -1;

	// Tips
#ifdef _Demo
	BOOL bRet = m_Tips.Create(CSize(100, 20));
#else
	BOOL bRet = m_Tips.Create(CSize(100, 20));
#endif
}

CTrayMapCtrl::~CTrayMapCtrl()
{
}


BEGIN_MESSAGE_MAP(CTrayMapCtrl, CStatic)
	//{{AFX_MSG_MAP(CTrayMapCtrl)
	ON_WM_ERASEBKGND()
	ON_WM_SIZE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_NCHITTEST()
	ON_WM_MBUTTONDBLCLK()
	ON_WM_LBUTTONDBLCLK()
	//}}AFX_MSG_MAP
	ON_WM_DRAWITEM_REFLECT()
	ON_MESSAGE(WM_SETTEXT, OnSetText)
	ON_MESSAGE(WM_GETTEXT, OnGetText)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTrayMapCtrl message handlers

BOOL CTrayMapCtrl::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
//	RECT rtWin;
//	GetClientRect(&rtWin);
//	pDC->FillSolidRect(&rtWin, m_colBk);
	return TRUE;
}

//LRESULT CTrayMapCtrl::OnGetText(UINT cchTextMax, LPTSTR szText)
LRESULT CTrayMapCtrl::OnGetText(WPARAM wParam, LPARAM lParam)
{
	UINT cchTextMax = wParam;
	LPTSTR szText = (LPTSTR)lParam;
	if (!_tcsncpy(szText, m_strText, cchTextMax))
		return 0;
	else 
		return min(cchTextMax, (UINT) m_strText.GetLength());
}

//LRESULT CTrayMapCtrl::OnSetText(UINT, LPCTSTR szText)
LRESULT CTrayMapCtrl::OnSetText(WPARAM wParam, LPARAM lParam)
{
	LRESULT result = Default();
	
	LPCTSTR szText = (LPCTSTR)lParam;
	if ( (!szText && m_strText.GetLength()) ||
		(szText && (m_strText != szText))   )
	{
		m_strText = szText;
		Invalidate();
	}
	
	return result;
}

void CTrayMapCtrl::OnSize(UINT nType, int cx, int cy) 
{
	CStatic::OnSize(nType, cx, cy);
}

void CTrayMapCtrl::SetForeColour(COLORREF col)
{
	if (m_colFore != col) {
		m_colFore = col;
		Invalidate();
	}
}

void CTrayMapCtrl::SetBkColour(COLORREF col)
{
	if (m_colBk != col) {
		m_colBk = col;
		Invalidate();
	}
}

void CTrayMapCtrl::ShowText(BOOL bShow)
{
	if (::IsWindow(m_hWnd) && m_bShowText != bShow) {
		m_bShowText = bShow;
		Invalidate();
	}
}

void CTrayMapCtrl::SetTextBkColour(COLORREF col)
{
	m_colTextBk = col;
}

void CTrayMapCtrl::SetTextForeColour(COLORREF col)
{
	m_colTextFore = col;
}

void CTrayMapCtrl::Clear()
{
	for (int row = 0; row < m_row; ++row) {
		for (int col = 0; col < m_col; ++col) {
			m_traymap[row][col] = 0;
			m_binmap[row][col] = 0;
		}
	}
	Invalidate();
}

void CTrayMapCtrl::PreSubclassWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
	ModifyStyle(SS_TYPEMASK, SS_OWNERDRAW);
	
	CStatic::PreSubclassWindow();
}

void CTrayMapCtrl::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	// TODO: Add your message handler code here and/or call default
	ASSERT(lpDrawItemStruct != NULL);
	//CDC*  pDC = CDC::FromHandle(lpDrawItemStruct->hDC);
	//_DrawSelf(*pDC);

	CMemDC dc(CDC::FromHandle(lpDrawItemStruct->hDC));
	_DrawSelf(dc);

}
void CTrayMapCtrl::setNumber(bool bEnable)
{
	m_bEnableNumber = bEnable;
}
void CTrayMapCtrl::setInfo(bool bEnable)
{
	m_bEnableInfo = bEnable;

	if( m_bEnableInfo )
	{
		CSize cSize = CSize(150, 20);
		m_Tips.SetCSize( cSize );
	}
}
int CTrayMapCtrl::GetTextSize(int col, int row)
{
	int textsize = 80;
	int traysize = col * row;
	if( traysize > 0 && traysize < 260 )
		textsize = 80;
	else if( traysize >= 260 && traysize < 1000 )
		textsize = 60;
	else if( traysize >= 1000 )
		textsize = 50;


	return textsize;
}
void CTrayMapCtrl::_DrawSelf(CDC &dc) 
{
	CRect rtWin;
	GetClientRect(&rtWin);

	double w = (double)rtWin.right / m_col;
	double h = (double)rtWin.bottom / m_row;
	RECT rt;

	for (int row = 0; row < m_row; ++row) {
		for (int col = 0; col < m_col; ++col) {
			double x = col * w;
			double y = row * h;
			SetRect(&rt, x, y, x+w, y+h);
			if (m_traymap[row][col]) {
				dc.FillSolidRect(&rt, m_colFore);
			} else {
				dc.FillSolidRect(&rt, m_colBk);
			}
			dc.FrameRect(&rt, CBrush::FromHandle((HBRUSH)::GetStockObject(BLACK_BRUSH)));
		}
	}

	if (m_cpStartPos.x != 0 && m_cpStartPos.y != 0) {
		SetRect(&rt, min(m_cpStartPos.x, m_cpEndPos.x), min(m_cpStartPos.y, m_cpEndPos.y),
					 max(m_cpStartPos.x, m_cpEndPos.x), max(m_cpStartPos.y, m_cpEndPos.y));
		dc.FrameRect(&rt, CBrush::FromHandle((HBRUSH)::GetStockObject(DEVICE_DEFAULT_FONT)));
	}
// 	else if (m_cpEndPos.x <= 0 || m_cpEndPos.y <= 0){
// 		SetRect(&rt, 0, 0, 0, 0);
// 		dc.FrameRect(&rt, CBrush::FromHandle((HBRUSH)::GetStockObject(BLACK_BRUSH)));
// 	}

	// Change TextOut Size
	////////////////////////////////////////////////////////////
	CFont front;
	LOGFONT lf;
	memset(&lf, 0, sizeof(LOGFONT));				// clear out structure.
	int textSize = GetTextSize( m_col, m_row );
	lf.lfHeight = textSize;								// request a 12-pixel-height font
	strcpy(lf.lfFaceName, "Arial");	
	CFont font;
	VERIFY(font.CreatePointFontIndirect(&lf, &dc));	
	dc.SelectObject( &font );
	dc.SetBkMode(TRANSPARENT);
	////////////////////////////////////////////////////////////

	// Input Tray Number 
	if( m_bEnableNumber )
	{
		//
		int iIC = 0;
		for (int row = 0; row < m_row; ++row) 
		{
			for (int col = 0; col < 1; ++col) 
			{
				double x = col * w;
				double y = row * h;
				CString cs = _T("");
				iIC++;
				cs.Format("%d", iIC );
				dc.TextOut(x + (w/4), y, cs );
			}
		}	

		int iIC2 = 0;
		for (row = 0; row < 1; ++row) 
		{
			for (int col = 0; col < m_col; ++col)
			{
				double x = col * w;
				double y = row * h;
				CString cs = _T("");
				iIC2++;
				cs.Format("%d", iIC2 );
				dc.TextOut(x + (w/4), y, cs );
			}
		}	
	}

	// Chip Tray 
	if( m_ChipTray == 1)
	{
		CPen penChip;
		penChip.CreatePen(PS_SOLID, 1, RGB( 255, 153, 0   ) );		
		CPen* pOldPen = dc.SelectObject(&penChip);		

		CRect	m_ChipTrayRect;
		double chipxpitch = (double)rtWin.right		/ m_chipcol;
		double chipypitch = (double)rtWin.bottom	/ m_chiprow;
		for(int i=0; i<m_chipcol; i++)
		{
			for(int j=0; j<m_chiprow; j++)
			{
				m_ChipTrayRect.left =	(double)((i)*chipxpitch);
				m_ChipTrayRect.right =	(double)(i+1)*chipxpitch;
				m_ChipTrayRect.top =	(double)(j)*chipypitch;
				m_ChipTrayRect.bottom =	(double)(j+1)*chipypitch;
				dc.SelectStockObject(NULL_BRUSH); // 框框背景透明
				dc.Rectangle(&m_ChipTrayRect);
				// 畫 Chip Tray Map 的格子
			}
		}

		dc.SelectObject(pOldPen);
	}
	else
		;

}

void CTrayMapCtrl::setMapSize(int x, int y, int stat) 
{
	if (x <= 0 || y <= 0) return;
	m_col = x;
	m_row = y;
	m_traymap.clear();
	m_traymap.resize(y, std::vector<int>(x, stat));
	m_binmap.clear();
	m_binmap.resize(y, std::vector<int>(x, stat));
}

int CTrayMapCtrl::getCellStatus(int x, int y)
{
	if (x >=0 && x < m_col) {
		if (y >=0 && y < m_row) {
			return m_traymap[y][x];
		}
	}
	return -1;
}

int CTrayMapCtrl::setCellStatus(int x, int y, int stat) {
	if (x >=0 && x < m_col) {
		if (y >=0 && y < m_row) {
			m_traymap[y][x] = stat;
			return 0;
		}
	}
	return -1;
}

int CTrayMapCtrl::setCellBin(int x, int y, int bin) {
	if (x >=0 && x < m_col) {
		if (y >=0 && y < m_row) {
			m_binmap[y][x] = bin;
			return 0;
		}
	}
	return -1;
}

bool CTrayMapCtrl::isModified()
{
	return m_modified;
}

void CTrayMapCtrl::setModified(bool b)
{
	m_modified = b;
}

void CTrayMapCtrl::getLastPoint(POINT &pt)
{
	pt = m_pt;
}

void CTrayMapCtrl::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default

	m_cpStartPos = point;

	CRect rtWin;
	GetClientRect(&rtWin);

	double w = (double)rtWin.right / m_col;
	double h = (double)rtWin.bottom / m_row;

	int x = point.x / w;
	int y = point.y / h;

	m_pt.x = x;
	m_pt.y = y;

	if ((x >= 0 && x < m_col) && (y >= 0 && y < m_row)) {
		int mark = m_traymap[y][x] != 0?0:1;
		if (GetKeyState(VK_CONTROL) & 0x8000) {
			for (int i = x; i < m_col; ++i) {
				m_traymap[y][i] = mark;
			}

		} else if (GetKeyState(VK_SHIFT) & 0x8000) {
			int mark = m_traymap[y][x] != 0?0:1;
			for (int i = x; i >= 0; --i) {
				m_traymap[y][i] = mark;
			}
		} else {
			m_traymap[y][x] = mark;
		}

		m_modified = true;
	}
	
	
	CStatic::OnLButtonDown(nFlags, point);
}

LRESULT CTrayMapCtrl::OnNcHitTest(CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	return HTCLIENT;
	//return CStatic::OnNcHitTest(point);
}

void CTrayMapCtrl::OnLButtonUp(UINT nFlags, CPoint point) 
{
	if (m_cpStartPos.x != 0 && m_cpStartPos.y != 0) {

		CRect rtWin;
		GetClientRect(&rtWin);

		double w = (double)rtWin.right / m_col;
		double h = (double)rtWin.bottom / m_row;

		int start_x = m_cpStartPos.x / w;
		int start_y = m_cpStartPos.y / h;
		int end_x = point.x / w;
		int end_y = point.y / h;
	
		m_pt.x = end_x;
		m_pt.y = end_y;	

		if ((end_x >= 0 && end_x < m_col) && (end_y >= 0 && end_y < m_row)) {
			if (!(start_x == end_x && start_y == end_y)) {
				for (int i = min(start_x, end_x); i <= max(start_x, end_x); ++i) {
					for (int j = min(start_y, end_y); j <= max(start_y, end_y); ++j) {
						m_traymap[j][i] = 1;//m_traymap[j][i] != 0?0:1;
					}
				}

				m_modified = true;
			}
		}

		m_cpStartPos.x = 0;
		m_cpStartPos.y = 0;
	}
}
int CTrayMapCtrl::getPositionInfoValue(int mx, int my)
{
	CRect rtWin;
	GetClientRect(&rtWin);
	double w = (double)rtWin.right	/ m_col;
	double h = (double)rtWin.bottom / m_row;

	int m_colvalue = -1;
	int m_rowvalue = -1;

	// calucation the col value
	for(int i=0;i<m_col;i++)
	{
		double hlimt = w*(i+1);
		double llimt = w*i;
		if( mx < hlimt && mx > llimt )
		{
			m_colvalue = i;
			break;
		}
	}

	// calucation the row value
	for(int j=0;j<m_row;j++)
	{
		double hlimt = h*(j+1);
		double llimt = h*j;
		if( my < hlimt && my > llimt )
		{
			m_rowvalue = j;
			break;
		}
	}

	int iposition = -1;	
	iposition = ( m_rowvalue * m_col ) + m_colvalue;
	
	return iposition;

}
CString CTrayMapCtrl::getPositionInfo(int mx, int my)
{
	CString csPosition = _T("None");

	CRect rtWin;
	GetClientRect(&rtWin);
	double w = (double)rtWin.right	/ m_col;
	double h = (double)rtWin.bottom / m_row;

	int m_colvalue = -1;
	int m_rowvalue = -1;

	// calucation the col value
	for(int i=0;i<m_col;i++)
	{
		double hlimt = w*(i+1);
		double llimt = w*i;
		if( mx < hlimt && mx > llimt )
		{
			m_colvalue = i;
			break;
		}
	}

	// calucation the row value
	for(int j=0;j<m_row;j++)
	{
		double hlimt = h*(j+1);
		double llimt = h*j;
		if( my < hlimt && my > llimt )
		{
			m_rowvalue = j;
			break;
		}
	}

	int iposition = -1;	
	iposition = ( m_rowvalue * m_col ) + m_colvalue;
	iposition++;
	csPosition.Format( "%d", iposition );
//	csPosition.Format("%d", iposition );
	
	return csPosition;
}
void CTrayMapCtrl::OnMouseMove(UINT nFlags, CPoint point)
{
	m_cpEndPos = point;
	m_modified = true; 

	if( m_bEnableTips )
	{
		CPoint ptLog = point;			
		ClientToScreen(&ptLog);
		CString csTemp1 = _T("");
		CString csTemp2 = _T("");
		csTemp1.Format("%s", getPositionInfo( point.x, point.y ) );

		int Value = getPositionInfoValue( point.x, point.y );

		int row = m_row;
		int col = m_col;

		int xx = Value / (col);
		int yy = Value % (col);
		if( m_bEnableInfo )
			csTemp2.Format(" (col %d, row %d)", xx+1, yy+1);

		m_Tips.ShowTips( ptLog.x - 5, ptLog.y - 25, csTemp1 + csTemp2 );

	}
}
void CTrayMapCtrl::setTip(bool bEnable)
{
	m_bEnableTips = bEnable;
}
void CTrayMapCtrl::setChipTray(int chiptray, int col, int row)
{
	m_chipcol  = col;
	m_chiprow  = row;
	m_ChipTray = chiptray;
}

void CTrayMapCtrl::OnMButtonDblClk(UINT nFlags, CPoint point) 
{
	CStatic::OnMButtonDblClk(nFlags, point);
}

void CTrayMapCtrl::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
//	AfxMessageBox("Mouse Double Click.!");
	
	CStatic::OnLButtonDblClk(nFlags, point);
}
