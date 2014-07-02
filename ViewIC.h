#if !defined(AFX_VIEWIC_H__EB773D5F_9CC4_40C5_BBDF_39D6C3FDBFF8__INCLUDED_)
#define AFX_VIEWIC_H__EB773D5F_9CC4_40C5_BBDF_39D6C3FDBFF8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ViewIC.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CViewIC view

class CViewIC : public CView
{
public:
	CViewIC();           // protected constructor used by dynamic creation
	virtual ~CViewIC();

	CString csFile;

	//
	IPicture* m_pPic;

public:
	void SetFileName(CString file);

protected:
	DECLARE_DYNCREATE(CViewIC)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CViewIC)
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
	//{{AFX_MSG(CViewIC)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VIEWIC_H__EB773D5F_9CC4_40C5_BBDF_39D6C3FDBFF8__INCLUDED_)
