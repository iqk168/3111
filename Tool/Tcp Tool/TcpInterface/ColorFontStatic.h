#if !defined(AFX_COLORSTATIC_H__7E091024_5607_11D4_93E4_0080C8F8DDD9__INCLUDED_)
#define AFX_COLORSTATIC_H__7E091024_5607_11D4_93E4_0080C8F8DDD9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ColorStatic.h : header file
//


//***********************************************//
// CColorFontStatic
//
//		Version:	1.7
//		Author:	Maxwell Chen
//		Date:		Jan. 07, 2002
//***********************************************//

enum BinColor {
	enPass = RGB( 0, 255, 0),
	enFail = RGB( 255, 0, 0),
	enOpen = RGB( 255, 255, 0),
	enTray = RGB(0, 0, 255),
	enOther = RGB(166, 202, 240)
};

// Color
#define ST_BLACK		RGB(0, 0, 0)
#define ST_WHITE		RGB(255, 255, 255)
#define ST_RED			RGB(255, 0, 0)
#define ST_GREEN		RGB(0, 255, 0)
#define ST_BLUE			RGB(0, 0, 255)
#define ST_LIGHTBLUE	RGB(0, 0, 192)
#define ST_CYAN			RGB(0, 255, 255)
#define ST_YELLOW		RGB(255, 255, 0)
#define ST_MAGENTA		RGB(255, 0, 255)
#define ST_DARKRED		RGB(128, 0, 0)
#define ST_DARKGREEN	RGB(0, 128, 0)
#define ST_LIGHTGREEN	RGB(0, 192, 0)
#define ST_LIGHTYELLOW	RGB(255, 255, 128)
#define ST_DARKBLUE		RGB(0, 0, 128)
#define ST_DARKMAGENTA	RGB(128, 0, 128)
#define ST_SKYBLUE		RGB(166, 202, 240)
#define ST_GRAY			RGB(128, 128, 128)
#define ST_BACKGROUND	RGB(192, 192, 192)
#define ST_BROWN		RGB(192, 0, 0)
#define ST_DEFAULT		::GetSysColor(COLOR_3DFACE)
#define ST_DEFINE		RGB(240, 210, 240)
#define ST_DISABLE		RGB(64, 0, 64)

/////////////////////////////////////////////////////////////////////
// MACRO
//#include "Define.h"
/////////////////////////////////////////////////////////////////////////////
// CColorFontStatic window

class CColorFontStatic : public CStatic
{
// Construction
public:
	CColorFontStatic();

protected:
	// Current colors
	COLORREF	m_clrText;
	COLORREF	m_clrBack;
	CBrush		m_brBack;
	// Initial color
	COLORREF	m_clrInitText;
	COLORREF	m_clrInitBack;
	COLORREF	m_clrInitFocus;

	int		m_FontSize;
	CString	m_FontFace;
	CFont	m_Font;
	unsigned int	m_Format;

	CString	m_Text;

	bool		m_bComplementColor;

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CColorFontStatic)
	//}}AFX_VIRTUAL

// Implementation
public:
	void SetWindowText(LPCTSTR lpszString );
	void SetComplementMode(bool bCmpMode = true)	{
		m_bComplementColor = bCmpMode;
	}

	// 更改文字 內容, 大小, 字型, 及對齊格式.
	void SetText(const CString& text, int size,
		const CString& face = "Times New Roman",
		unsigned int format = DT_LEFT | DT_VCENTER | DT_SINGLELINE);

	// 更改文字.
	void CColorFontStatic::SetNewText(const CString &text);

	// 更改目前的顏色, 和備份(供還原)的顏色. 不限於呼叫一次.
	// 包裝下列 InitTextColor() 和 InitBkColor().
	void Initial(COLORREF clrText, COLORREF clrBackground,
		COLORREF clrFocus = ST_SKYBLUE);
	void InitTextColor(COLORREF clrInit);
	void InitBkColor(COLORREF clrInit);

	// 更改目前的背景顏色 (暫時性).
	void SetNewBkColor(COLORREF clrBack);

	// 更改目前的文字顏色 (暫時性).
	void SetNewTextColor(COLORREF clrText);
	virtual ~CColorFontStatic();

	COLORREF	GetTextColor() { return m_clrText; }
	COLORREF GetBkColor() { return m_clrBack; }

	// Generated message map functions
protected:
	COLORREF _GetComplementColor(COLORREF& color);
	//{{AFX_MSG(CColorFontStatic)
	afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnPaint();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
private:
	COLORREF _GetInitBkColor();
	COLORREF _GetInitTextColor();
	void _SetInitBkColorValue();
	void _SetInitTextColorValue();
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COLORSTATIC_H__7E091024_5607_11D4_93E4_0080C8F8DDD9__INCLUDED_)
