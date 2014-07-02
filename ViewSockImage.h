#if !defined(AFX_VIEWSOCKIMAGE_H__1BAF891D_A8A5_4D83_88E6_4B159753557F__INCLUDED_)
#define AFX_VIEWSOCKIMAGE_H__1BAF891D_A8A5_4D83_88E6_4B159753557F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ViewSockImage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CViewSockImage view

class CViewSockImage : public CView
{
public:
	CViewSockImage();           // protected constructor used by dynamic creation

public:
	void SetBmpAddress(HBITMAP *pBitmap);
	HBITMAP *m_pBitmap;

	int m_h;	// Grab Image high
	int m_w;	// Grab Image width

protected:
	DECLARE_DYNCREATE(CViewSockImage)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CViewSockImage)
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CViewSockImage();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CViewSockImage)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VIEWSOCKIMAGE_H__1BAF891D_A8A5_4D83_88E6_4B159753557F__INCLUDED_)
