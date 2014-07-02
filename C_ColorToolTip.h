#if !defined(AFX_C_COLORTOOLTIP_H__CFCCAC8A_A5CF_46ED_94BA_B5F572B3AC51__INCLUDED_)
#define AFX_C_COLORTOOLTIP_H__CFCCAC8A_A5CF_46ED_94BA_B5F572B3AC51__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// C_ColorToolTip.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// C_ColorToolTip window

typedef BOOL (*TRANSPARENTWINDOWPROC)(
HWND hwnd, // handle to the layered window
COLORREF crKey, // specifies the color key
BYTE bAlpha, // value for the blend function
DWORD dwFlags // action
);

class C_ColorToolTip : public CWnd
{
// Construction
public:
	C_ColorToolTip();

// Attributes
public:

// Operations
public:
	/// @ create the tool tip
	BOOL Create(CSize szSize, CWnd *pWnd = NULL);

	/// @ adjust tip size
	void SetToolTipSize(CSize szSize);

	/// @ adjust tip size
	void SetCSize(CSize szSize);

	/// @ Show tip 
	void ShowTips(int nX, int nY, CString strTipsContent);

	/// @ hide tip
	void HideTips();

	/// @ Set back ground color
	void SetBkColor(COLORREF clrBack);

	/// @ Set tip text color
	void SetTipTextColor(COLORREF clrText);

	/// @ Set Frame color
	void SetFrameColor(COLORREF clrFrame);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(C_ColorToolTip)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~C_ColorToolTip();
private: 
    CPoint  m_ptOrg;
	CSize   m_TipSize;
	CString m_strTips;
	COLORREF m_clrBack;
	COLORREF m_clrText;
	COLORREF m_clrFrameColor;

	// Generated message map functions
protected:
	//{{AFX_MSG(C_ColorToolTip)
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_C_COLORTOOLTIP_H__CFCCAC8A_A5CF_46ED_94BA_B5F572B3AC51__INCLUDED_)
