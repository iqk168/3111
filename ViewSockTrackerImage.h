#if !defined(AFX_VIEWSOCKTRACKERIMAGE_H__C9F5453F_2164_45FB_8623_F282862F9387__INCLUDED_)
#define AFX_VIEWSOCKTRACKERIMAGE_H__C9F5453F_2164_45FB_8623_F282862F9387__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ViewSockTrackerImage.h : header file
//

#include "AlignRectTracker.h"

/////////////////////////////////////////////////////////////////////////////
// CViewSockTrackerImage view

class CViewSockTrackerImage : public CView
{

public:
	CViewSockTrackerImage();           // protected constructor used by dynamic creation

public:
	void SetBmpAddress(HBITMAP *pBitmap);
	HBITMAP *m_pBitmap;

	int m_h;	// Grab Image high
	int m_w;	// Grab Image width

//
	void SendPos();
	CAlignRectTracker m_AlignRectTracker;

	void GetPatternInfo(int &top, int &left, int &bottom, int &right);

	bool m_bLoadRect;
	CRect m_LoadRect;
	void SetPatternInfomation(int top, int left, int bottom, int right);

	//
	CString csInfomation;
	void SetInfomation(CString csInfo);

	//
	bool m_bLockUI;	// 

protected:
	DECLARE_DYNCREATE(CViewSockTrackerImage)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CViewSockTrackerImage)
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CViewSockTrackerImage();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CViewSockTrackerImage)
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VIEWSOCKTRACKERIMAGE_H__C9F5453F_2164_45FB_8623_F282862F9387__INCLUDED_)
