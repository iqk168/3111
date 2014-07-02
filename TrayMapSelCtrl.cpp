// TrayMapSelCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "deer.h"
#include "TrayMapSelCtrl.h"
#include "memdc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTrayMapSelCtrl

CTrayMapSelCtrl::CTrayMapSelCtrl()
{
	m_colFore			= ::GetSysColor(COLOR_HIGHLIGHT);
	m_colBk				= RGB(255,255,255);
	m_colRemoteBk		= RGB(255, 255, 0);
	m_colRemoteOverBk	= RGB(0, 255, 0);
	
	m_col = m_row = 1;
	m_traymap.resize(m_row, std::vector<int>(m_col, 0));
	m_traymapststus.resize(m_row, std::vector<int>(m_col, 0));
	m_binmap.resize(m_row, std::vector<int>(m_col, 0));

	//
	m_Position = -1;

	//
	m_bLock = false;
}

CTrayMapSelCtrl::~CTrayMapSelCtrl()
{
}
void CTrayMapSelCtrl::SetForeColour(COLORREF col)
{
	if (m_colFore != col) {
		m_colFore = col;
		Invalidate();
	}
}

void CTrayMapSelCtrl::SetBkColour(COLORREF col)
{
	if (m_colBk != col) {
		m_colBk = col;
		Invalidate();
	}
}
void CTrayMapSelCtrl::PreSubclassWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
	ModifyStyle(SS_TYPEMASK, SS_OWNERDRAW);
	
	CStatic::PreSubclassWindow();
}
void CTrayMapSelCtrl::setMapSize(int x, int y, int stat) 
{
	if (x <= 0 || y <= 0) return;
	m_col = x;
	m_row = y;
	m_traymap.clear();
	m_traymap.resize(y, std::vector<int>(x, stat));
	m_traymapststus.clear();
	m_traymapststus.resize(y, std::vector<int>(x, stat));
	m_binmap.clear();
	m_binmap.resize(y, std::vector<int>(x, stat));
}
int CTrayMapSelCtrl::setCellStatus(int x, int y, int stat) {
	if (x >=0 && x < m_col) {
		if (y >=0 && y < m_row) {
			m_traymapststus[y][x] = stat;
			return 0;
		}
	}
	return -1;
}
void CTrayMapSelCtrl::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	// TODO: Add your message handler code here and/or call default
	ASSERT(lpDrawItemStruct != NULL);
	//CDC*  pDC = CDC::FromHandle(lpDrawItemStruct->hDC);
	//_DrawSelf(*pDC);

	CMemDC dc(CDC::FromHandle(lpDrawItemStruct->hDC));
	_DrawSelf(dc);

}
CPoint CTrayMapSelCtrl::getPositionPoint(int iposition)
{
	CPoint pp;

	pp.x = iposition % m_col;
	pp.y = iposition / m_col;
	
	return pp;
}

int CTrayMapSelCtrl::getPositionInfo(int mx, int my)
{
	int m_iPosition = -1;

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
//	csPosition.Format( "%d", iposition );

	m_iPosition = iposition;
	
	return m_iPosition;
}

void CTrayMapSelCtrl::_DrawSelf(CDC &dc) 
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
			if (m_traymap[row][col] && !m_traymapststus[row][col] ) 
			{
				dc.FillSolidRect(&rt, m_colFore);
			} 
			else if( m_traymap[row][col] && m_traymapststus[row][col] )
			{
				dc.FillSolidRect(&rt, m_colRemoteOverBk);
			}
			else 
			{
				if (m_traymapststus[row][col]) 
					dc.FillSolidRect(&rt, m_colRemoteBk);
				else
					dc.FillSolidRect(&rt, m_colBk);
			}
			dc.FrameRect(&rt, CBrush::FromHandle((HBRUSH)::GetStockObject(BLACK_BRUSH)));
		}
	}
}

BEGIN_MESSAGE_MAP(CTrayMapSelCtrl, CStatic)
	//{{AFX_MSG_MAP(CTrayMapSelCtrl)
	ON_WM_LBUTTONDBLCLK()
	ON_WM_DRAWITEM_REFLECT()
	ON_WM_LBUTTONUP()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTrayMapSelCtrl message handlers
void CTrayMapSelCtrl::setPosition(int position)
{
	// 讓外部預設被點選的位置
	// Clear data and reset
	std::vector< std::vector<int> > m_traymap_m;
	CPoint tray;
	m_traymap_m.clear();
	m_traymap_m.resize(m_row, std::vector<int>(m_col, 0));
	tray = getPositionPoint( position );	

	m_traymap_m[tray.y][tray.x] = 1;

	m_Position = position;

	m_traymap.clear();
	m_traymap = m_traymap_m;
}
int CTrayMapSelCtrl::getPosition()
{
	return m_Position;
}
void CTrayMapSelCtrl::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	// Try to location IC position
	CPoint pp;
	pp = point;
	int iPosition = getPositionInfo( pp.x, pp.y );
	
	// Clear data and reset
	std::vector< std::vector<int> > m_traymap_m;
	CPoint tray;
	m_traymap_m.clear();
	m_traymap_m.resize(m_row, std::vector<int>(m_col, 0));
	iPosition--;
	tray = getPositionPoint( iPosition );
	
	// 指定後, 讓外部可以取得
	m_Position = iPosition;

	m_traymap_m[tray.y][tray.x] = 1;

	// Copy new data
	m_traymap.clear();
	m_traymap = m_traymap_m;

	CStatic::OnLButtonDblClk(nFlags, point);
}
void CTrayMapSelCtrl::LockUI()
{
	m_bLock = true;
}
void CTrayMapSelCtrl::UnLockUI()
{
	m_bLock = false;
}
void CTrayMapSelCtrl::OnLButtonUp(UINT nFlags, CPoint point) 
{
	if( !m_bLock )
	{		
		// Try to location IC position
		CPoint pp;
		pp = point;
		int iPosition = getPositionInfo( pp.x, pp.y );
		
		// Clear data and reset
		std::vector< std::vector<int> > m_traymap_m;
		CPoint tray;
		m_traymap_m.clear();
		m_traymap_m.resize(m_row, std::vector<int>(m_col, 0));
		iPosition--;
		tray = getPositionPoint( iPosition );
		
		// 指定後, 讓外部可以取得
		m_Position = iPosition;
		
		m_traymap_m[tray.y][tray.x] = 1;
		
		// Copy new data
		m_traymap.clear();
		m_traymap = m_traymap_m;
	}
	
	CStatic::OnLButtonUp(nFlags, point);
}
