#if !defined(AFX_VIEWIMAGE_H__39C07649_AB8A_42F2_8270_5A2CDB6C3AF6__INCLUDED_)
#define AFX_VIEWIMAGE_H__39C07649_AB8A_42F2_8270_5A2CDB6C3AF6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ViewImage.h : header file
//

#include "AlignRectTracker.h"

/////////////////////////////////////////////////////////////////////////////
// CViewImage view

class CViewImage : public CView
{
public:
	CViewImage();           // protected constructor used by dynamic creation
	virtual ~CViewImage();

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
protected:
	DECLARE_DYNCREATE(CViewImage)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CViewImage)
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	//}}AFX_VIRTUAL

// Implementation
protected:

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CViewImage)
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VIEWIMAGE_H__39C07649_AB8A_42F2_8270_5A2CDB6C3AF6__INCLUDED_)
