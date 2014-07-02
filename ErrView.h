#if !defined(AFX_ERRVIEW_H__692175A5_2C90_4ED0_ACF8_8662F2F9C593__INCLUDED_)
#define AFX_ERRVIEW_H__692175A5_2C90_4ED0_ACF8_8662F2F9C593__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ErrView.h : header file
//

#include "stdafx.h"
#include "Member.h"

/////////////////////////////////////////////////////////////////////////////
// CErrView view

class CErrView : public CView
{
protected:
	DECLARE_DYNCREATE(CErrView)
public:
	CErrView(tagErrorMsg *p = NULL);           // protected constructor used by dynamic creation
	virtual ~CErrView();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CErrView)
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
	//{{AFX_MSG(CErrView)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	tagErrorMsg *msg;

};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ERRVIEW_H__692175A5_2C90_4ED0_ACF8_8662F2F9C593__INCLUDED_)
