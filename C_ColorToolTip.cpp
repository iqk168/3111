// C_ColorToolTip.cpp : implementation file
//

#include "stdafx.h"
#include "C_ColorToolTip.h"

#ifndef  WS_EX_LAYERED
#define  WS_EX_LAYERED           0x00080000
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// C_ColorToolTip

C_ColorToolTip::C_ColorToolTip()
:m_ptOrg(0,0),
m_TipSize(0,0)
{
	m_clrFrameColor = RGB(155, 110, 53);
	m_clrBack = RGB(249, 249, 238);
	m_clrText = RGB(0, 0, 0);

}

C_ColorToolTip::~C_ColorToolTip()
{

}


BEGIN_MESSAGE_MAP(C_ColorToolTip, CWnd)
	//{{AFX_MSG_MAP(C_ColorToolTip)
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


BOOL C_ColorToolTip::Create(CSize szSize, CWnd *pWnd)
{
	HWND hWnd = NULL;
	if (pWnd != NULL && IsWindow(pWnd->m_hWnd))
	{
		hWnd = pWnd->m_hWnd;
	}
	// register class 
    LPCTSTR lpszClassName = AfxRegisterWndClass(NULL);
	BOOL bRet = CreateEx(WS_EX_TOPMOST | WS_EX_TOOLWINDOW, lpszClassName, _T(""),
		WS_POPUP /*| WS_BORDER*/, 0, 0, 1, 1, NULL, NULL);
	if (bRet)
	{
		MoveWindow(CRect(m_ptOrg, szSize));	
		m_TipSize = szSize;
	}
	return bRet;
}
void C_ColorToolTip::SetCSize(CSize szSize)
{
	m_TipSize = szSize;
}

void C_ColorToolTip::SetToolTipSize(CSize szSize)
{
	if (IsWindow(m_hWnd))
	{
		MoveWindow(CRect(m_ptOrg, szSize));
	}
}

void C_ColorToolTip::ShowTips(int nX, int nY, CString strTipsContent)
{	
	  m_ptOrg = CPoint(nX, nY);
	  m_strTips = strTipsContent;
      MoveWindow(nX, nY, m_TipSize.cx, m_TipSize.cy, TRUE);
	  if (!IsWindowVisible())
	  {
		 ShowWindow(SW_SHOW);
	  }
	  Invalidate(TRUE);  
}


/////////////////////////////////////////////////////////////////////////////
// C_ColorToolTip message handlers

void C_ColorToolTip::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	CRect rtWin;
	GetClientRect(rtWin);
	dc.FillSolidRect(rtWin, m_clrBack);
	dc.SetBkMode(TRANSPARENT);
	dc.Draw3dRect(rtWin, m_clrFrameColor, m_clrFrameColor);
	dc.SetTextColor(m_clrText);                
	dc.DrawText(m_strTips, rtWin,  DT_CENTER |DT_VCENTER | DT_SINGLELINE);	
}


BOOL C_ColorToolTip::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default	
    // return CWnd::OnEraseBkgnd(pDC);
	return TRUE;
}

void C_ColorToolTip::HideTips()
{
	if (IsWindow(m_hWnd))
	{
		ShowWindow(SW_HIDE);
	}
}


void C_ColorToolTip::SetBkColor(COLORREF clrBack)
{
	m_clrBack = clrBack;
}

void C_ColorToolTip::SetFrameColor(COLORREF clrFrame)
{
	m_clrFrameColor = clrFrame;
}

void C_ColorToolTip::SetTipTextColor(COLORREF clrText)
{
	m_clrText = clrText;
}


