// ContinueFailCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "ContinueFailCtrl.h"
#include "MemDC.h"
#include "Deer.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CContinueFailCtrl

CContinueFailCtrl::CContinueFailCtrl()
{
	m_nPos			= 0;
	m_nStepSize		= 1;
	m_nMax			= 10;
	m_nMin			= 0;
	m_bShowText		= TRUE;
	m_strText.Empty();
	m_colFore		= ::GetSysColor(COLOR_HIGHLIGHT);
//	m_colBk			= ::GetSysColor(COLOR_WINDOW);
//	m_colBk			= ::GetSysColor(COLOR_3DFACE);
	m_colBk			= ST_BLACK;
	m_colTextFore	= ::GetSysColor(COLOR_HIGHLIGHT);
	m_colTextBk		= ::GetSysColor(COLOR_WINDOW);
	
	m_nBarWidth = -1;

	_lstColor.clear();
}

CContinueFailCtrl::~CContinueFailCtrl()
{
}


BEGIN_MESSAGE_MAP(CContinueFailCtrl, CProgressCtrl)
	//{{AFX_MSG_MAP(CContinueFailCtrl)
	ON_WM_ERASEBKGND()
	ON_WM_PAINT()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_SETTEXT, OnSetText)
	ON_MESSAGE(WM_GETTEXT, OnGetText)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CContinueFailCtrl message handlers

BOOL CContinueFailCtrl::OnEraseBkgnd(CDC* /*pDC*/) 
{
	// TODO: Add your message handler code here and/or call default
	
//	return CProgressCtrl::OnEraseBkgnd(pDC);
	return TRUE;
}

LRESULT CContinueFailCtrl::OnGetText(UINT cchTextMax, LPTSTR szText)
{
	if (!_tcsncpy(szText, m_strText, cchTextMax))
		return 0;
	else 
		return min(cchTextMax, (UINT) m_strText.GetLength());
}

LRESULT CContinueFailCtrl::OnSetText(UINT, LPCTSTR szText)
{
	LRESULT result = Default();
	
	if ( (!szText && m_strText.GetLength()) ||
		(szText && (m_strText != szText))   )
	{
		m_strText = szText;
		Invalidate();
	}
	
	return result;
}

void CContinueFailCtrl::OnPaint() 
{
	if(m_nMin >= m_nMax) 
		return;
	
	CRect SubRect, ClientRect;
	GetClientRect(ClientRect);
	
	CPaintDC PaintDC(this); // device context for painting
	CMemDC dc(&PaintDC);
	
	dc.FillSolidRect(ClientRect, m_colBk);
	SubRect = ClientRect;

	std::list<COLORREF>::iterator p = _lstColor.begin();
	int iLastRight = 0;
	int i;
	for(i = 0; i < _lstColor.size(); i++, p++)
	{
		// 20020422.
		SubRect.right = ClientRect.Width() * (i +1) / m_nMax;
		SubRect.left = iLastRight;
		iLastRight = SubRect.right;

		CRect rTemp = SubRect;
		rTemp.top -= 1;
		rTemp.bottom +=1;
		rTemp.left +=1;
		rTemp.right -= 1;

		dc.FillSolidRect(rTemp, *p);
	}

	if (m_bShowText)
	{
		CString str;
		if(m_strText.GetLength())
			str = m_strText;
		
		dc.SetBkMode(TRANSPARENT);
		
		CRgn rgn;
		rgn.CreateRectRgn(ClientRect.left, ClientRect.top,
			ClientRect.right, ClientRect.bottom);
		dc.SelectClipRgn(&rgn);
		dc.SetTextColor(m_colTextFore);
		
		dc.DrawText(str, ClientRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		
		rgn.DeleteObject();
	}
}

void CContinueFailCtrl::OnSize(UINT nType, int cx, int cy) 
{
	CProgressCtrl::OnSize(nType, cx, cy);
	
	m_nBarWidth	= -1;   // Force update if SetPos called
}

void CContinueFailCtrl::SetBkColour(COLORREF col)
{
	m_colBk = col;
}

int CContinueFailCtrl::_SetPos(int nPos)
{
	if (!::IsWindow(m_hWnd))
		return -1;
	
	int nOldPos = m_nPos;
	m_nPos = nPos;
	
	CRect rect;
	GetClientRect(rect);
	
	double Fraction = (double)(m_nPos - m_nMin) / ((double)(m_nMax - m_nMin));
	int nBarWidth = (int) (Fraction * rect.Width());
	
	if (nBarWidth != m_nBarWidth)
	{
		m_nBarWidth = nBarWidth;
		RedrawWindow();
	}
	
	return nOldPos;
}

void CContinueFailCtrl::_SetRange(int nLower, int nUpper)
{
	m_nMax = nUpper;
	m_nMin = nLower;
}

void CContinueFailCtrl::SetShowText(BOOL bShow)
{
	if (::IsWindow(m_hWnd) && m_bShowText != bShow)
		Invalidate();
	
	m_bShowText = bShow;
}

int CContinueFailCtrl::_SetStep(int nStep)
{
	int nOldStep = m_nStepSize;
	m_nStepSize = nStep;
	return nOldStep;
}

void CContinueFailCtrl::SetTextBkColour(COLORREF col)
{
	m_colTextBk = col;
}

void CContinueFailCtrl::SetTextForeColour(COLORREF col)
{
	m_colTextFore = col;
}

int CContinueFailCtrl::_StepIt()
{
   return SetPos(m_nPos + m_nStepSize);
}

int CContinueFailCtrl::StepIt(COLORREF col)
{
	int iPos = m_nPos + m_nStepSize;
	_lstColor.push_front(col);

	// 20020422.
	if(_lstColor.size() > m_nMax)
		_lstColor.pop_back();

	return _SetPos(iPos);
}

// Return last max.
// If you want to know the current max,
//  call GetMax().
int CContinueFailCtrl::SetLimitation(int iMax)
{
	CRect ClientRect;
	GetClientRect(ClientRect);

	// 20020422.
	if(ClientRect.Width() < (iMax * 3 -1))
		return m_nMax;

	int iOldMax = m_nMax;
	m_nMax = iMax;
	if(m_nMax <= 0)
		m_nMax = 1;

	// 20020422.
	while(_lstColor.size() > m_nMax)
		_lstColor.pop_back();

	// 20020422.
	Invalidate();

	return iOldMax;
}

void CContinueFailCtrl::Clear()
{
	_lstColor.clear();
	_SetPos(0);
	Invalidate();
}

int CContinueFailCtrl::GetMax()
{
	return m_nMax;
}

bool CContinueFailCtrl::Add(COLORREF col)
{
	StepIt(col);

	if(m_nPos < m_nMax)
		return true;
	else
	{
		std::list<COLORREF>::iterator p = _lstColor.begin();
		for(int i = 0; i < _lstColor.size(); i++, p++)
		{
			if(*p == theApp.enPass)
				return true;
			// Note: enPass. Please refer Deer.h enum...
		}
	}

	return false;
}
