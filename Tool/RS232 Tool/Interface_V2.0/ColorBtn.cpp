// ColorBtn.cpp : implementation file
//

#include "stdafx.h"
#include "ColorBtn.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

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
