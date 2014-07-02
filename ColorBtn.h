#if !defined(AFX_COLORBTN_H__0F7EC0E2_8CB0_46D0_855D_A7DF36BE5C2A__INCLUDED_)
#define AFX_COLORBTN_H__0F7EC0E2_8CB0_46D0_855D_A7DF36BE5C2A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ColorBtn.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CColorBtn window


class CColorBtn : public CButton
{


public:
	COLORREF    m_TextColor;
	COLORREF    m_BkgndColor;


private:
	CBrush		m_brBack;
	COLORREF	m_clrBack;

// Construction
public:
	CColorBtn();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CColorBtn)
	public:	
//	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CColorBtn();
	afx_msg void OnPaint();

	// Generated message map functions
protected:
	//{{AFX_MSG(CColorBtn)
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COLORBTN_H__0F7EC0E2_8CB0_46D0_855D_A7DF36BE5C2A__INCLUDED_)
