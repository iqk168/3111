// ColorBtn.cpp : implementation file
//

#include "stdafx.h"
#include "ColorBtn.h"

#include <afxtempl.h>	// for CArray

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

namespace clr
{
	const COLORREF CLR_BTN_WHITE  = RGB(255, 255, 255);
	const COLORREF CLR_BTN_BLACK  = RGB(0, 0, 0);
	const COLORREF CLR_BTN_DGREY  = RGB(128, 128, 128);
	const COLORREF CLR_BTN_GREY   = RGB(192, 192, 192);
	const COLORREF CLR_BTN_LLGREY = RGB(223, 223, 223);
}


/////////////////////////////////////////////////////////////////////////////
// CColorBtn

CColorBtn::CColorBtn()
{
	m_clrBack = RGB(0, 255, 0);
	m_brBack.CreateSolidBrush(m_clrBack);
}

CColorBtn::~CColorBtn()
{
}


BEGIN_MESSAGE_MAP(CColorBtn, CButton)
	//{{AFX_MSG_MAP(CColorBtn)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CColorBtn message handlers

void CColorBtn::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	CString s;
	GetWindowText(s);
	SetWindowText(s);
	CRect rect, rt;
	GetClientRect(&rect);
	if(GetCheck() == 1)
	{
		rt = rect; rt.bottom = rt.top + 5;
		dc.FillRect(&rt, &m_brBack);
		rt = rect; rt.right = rt.left + 5;
		dc.FillRect(&rt, &m_brBack);
		rt = rect; rt.top = rt.bottom - 5;
		dc.FillRect(&rt, &m_brBack);
		rt = rect; rt.left = rt.right - 5;
		dc.FillRect(&rt, &m_brBack);
	}
}




