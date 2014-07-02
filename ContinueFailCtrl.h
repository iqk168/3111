#if !defined(AFX_SEGPROGRESSCTRL_H__3E925CD0_13EC_4641_A4AA_8797208E0578__INCLUDED_)
#define AFX_SEGPROGRESSCTRL_H__3E925CD0_13EC_4641_A4AA_8797208E0578__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//////////////////////////////////////////
/*	Updation Note

	Author: Maxwell Chen
	Modify Date: April 22, 2002

	2002-04-22:
		1) OnPaint() fix uneven segmentation.
		2) SetMax(int) blur protect, garbage queue clean, refresh output.
		3) StepIt(COLORREF) fix history data removal.
	
*/
//////////////////////////////////////////

// ContinueFailCtrl.h : header file
//
#include <list>

/////////////////////////////////////////////////////////////////////////////
// CContinueFailCtrl window

class CContinueFailCtrl : public CProgressCtrl
{
// Construction
public:
	CContinueFailCtrl();
	virtual ~CContinueFailCtrl();

// Attributes
protected:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CContinueFailCtrl)
	//}}AFX_VIRTUAL

// Implementation
public:
	void SetShowText(BOOL bShow);
	int SetLimitation(int iLimit);
	void Clear();
	bool Add(COLORREF col);

protected:
	int GetMax();
	int StepIt(COLORREF col);
	void SetTextForeColour(COLORREF col);
	void SetTextBkColour(COLORREF col);

public:
	void SetBkColour(COLORREF col);

protected:
	void _SetRange(int nLower, int nUpper);
	int _SetStep(int nStep);
	int _SetPos(int nPos);
	int _StepIt();

protected:
	int	m_nPos;
	int	m_nStepSize;
	int	m_nMax; 
	int	m_nMin;
	CString	m_strText;
	BOOL		m_bShowText;
	int		m_nBarWidth;
	COLORREF	m_colFore;
	COLORREF		m_colBk;
	COLORREF		m_colTextFore;
	COLORREF		m_colTextBk;
	std::list<COLORREF>		_lstColor;

	// Generated message map functions
protected:
	//{{AFX_MSG(CContinueFailCtrl)
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	afx_msg LRESULT OnSetText(UINT, LPCTSTR szText);
	afx_msg LRESULT OnGetText(UINT cchTextMax, LPTSTR szText);

	DECLARE_MESSAGE_MAP()

};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SEGPROGRESSCTRL_H__3E925CD0_13EC_4641_A4AA_8797208E0578__INCLUDED_)
