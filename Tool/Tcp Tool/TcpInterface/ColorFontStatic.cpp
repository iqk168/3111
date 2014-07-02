// ColorStatic.cpp : implementation file
//

#include "stdafx.h"
#include "ColorFontStatic.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CColorFontStatic

CColorFontStatic::CColorFontStatic()
{
	m_clrText = RGB(0, 0, 0);
	m_clrBack = ::GetSysColor(COLOR_3DFACE);
	m_brBack.CreateSolidBrush(m_clrBack);
	m_clrInitFocus = ST_SKYBLUE;

	_SetInitBkColorValue();
	_SetInitTextColorValue();

//	SetText("ColorStatic", 12);
//	this->m_Text = "ColorStatic";
	this->m_FontSize = 12 * 10;
	SetComplementMode(false);
}

CColorFontStatic::~CColorFontStatic()
{
}


BEGIN_MESSAGE_MAP(CColorFontStatic, CStatic)
	//{{AFX_MSG_MAP(CColorFontStatic)
	ON_WM_CTLCOLOR_REFLECT()
	ON_WM_LBUTTONUP()
	ON_WM_SETFOCUS()
	ON_WM_KILLFOCUS()
	ON_WM_LBUTTONDOWN()
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CColorFontStatic message handlers

void CColorFontStatic::SetNewTextColor(COLORREF clrText)
{
	if(m_clrText != clrText)
	{
		m_clrText = clrText;
		Invalidate();
	}
}

void CColorFontStatic::SetNewBkColor(COLORREF clrBack)
{
	if(m_clrBack != clrBack)
	{
		m_clrBack = clrBack;
		m_brBack.DeleteObject();
		m_brBack.CreateSolidBrush(clrBack);
		Invalidate();
		if(clrBack == enFail || clrBack == enTray)
			SetNewTextColor(ST_WHITE);
		else if(clrBack == enOpen || clrBack == enPass)
			SetNewTextColor(ST_BLACK);
	}
}

HBRUSH CColorFontStatic::CtlColor(CDC* pDC, UINT nCtlColor) 
{
	pDC->SetTextColor(m_clrText);	// Useless
	pDC->SetBkColor(m_clrBack);	// Useless

	return (HBRUSH)m_brBack;
}

void CColorFontStatic::OnLButtonUp(UINT nFlags, CPoint point) 
{
//	CStatic::OnLButtonUp(nFlags, point);
}

void CColorFontStatic::OnSetFocus(CWnd* pOldWnd) 
{
//	CStatic::OnSetFocus(pOldWnd);

//	SetNewBkColor(m_clrInitFocus);	
	SetNewTextColor(ST_DARKBLUE);
}

void CColorFontStatic::OnKillFocus(CWnd* pNewWnd) 
{
	CStatic::OnKillFocus(pNewWnd);
	
	SetNewBkColor(_GetInitBkColor());
	SetNewTextColor(_GetInitTextColor());
}

void CColorFontStatic::OnLButtonDown(UINT nFlags, CPoint point) 
{
//	SetFocus();
	
	CStatic::OnLButtonDown(nFlags, point);
}

void CColorFontStatic::InitTextColor(COLORREF clrInit)
{
	// 初始化文字顏色.
	m_clrText = clrInit;

	_SetInitTextColorValue();
}

void CColorFontStatic::InitBkColor(COLORREF clrInit)
{
	// 初始化背景顏色.
	m_clrBack = clrInit;

	// 做下列的動作去填入這個control整片的顏色.
	m_brBack.DeleteObject();
	m_brBack.CreateSolidBrush(m_clrBack);
	Invalidate();

	_SetInitBkColorValue();
}

void CColorFontStatic::Initial(COLORREF clrText,
							COLORREF clrBackground, COLORREF clrFocus)
{
	InitBkColor(clrBackground);
	// 初始化文字和背景顏色.
	InitTextColor(clrText);

	m_clrInitFocus = clrFocus;
}

void CColorFontStatic::_SetInitTextColorValue()
{
	m_clrInitText = m_clrText;
}

void CColorFontStatic::_SetInitBkColorValue()
{
	m_clrInitBack = m_clrBack;
}

COLORREF CColorFontStatic::_GetInitTextColor()
{
	m_clrText = m_clrInitText;
	return m_clrText;
}

COLORREF CColorFontStatic::_GetInitBkColor()
{
	m_clrBack = m_clrInitBack;
	return m_clrBack;
}

void CColorFontStatic::SetText(const CString &text, int size,
							   const CString &face, unsigned int format)
{
	this->m_FontSize = size * 10;
	this->m_FontFace = face;
	this->m_Format = format;
	CWnd::SetWindowText(text);
}


void CColorFontStatic::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	CFont font;
	font.CreatePointFont(m_FontSize, m_FontFace);

	SetBkColor(dc.m_hDC, m_clrBack);
	if(m_bComplementColor)
		SetTextColor(dc.m_hDC, _GetComplementColor(m_clrBack));
	else
		SetTextColor(dc.m_hDC, m_clrText);

	CRect rect;
	GetClientRect(&rect);

	dc.SelectObject(&font);
	dc.FillRect(&rect, &m_brBack);
	CString s;
	GetWindowText(s);
	dc.DrawText(s, -1, &rect, m_Format);
	ReleaseDC(&dc);
}

void CColorFontStatic::SetNewText(const CString &text)
{
	if(m_Text != text)
	{
		CWnd::SetWindowText(text);
		m_Text = text;
		RedrawWindow();
		UpdateWindow();
	}
}

COLORREF CColorFontStatic::_GetComplementColor(COLORREF &color)
{
	const ULONG mask = 0xFFFFFF;
	return (~color & mask);
}

void CColorFontStatic::SetWindowText(LPCTSTR lpszString)
{
	SetNewText(lpszString);
}
