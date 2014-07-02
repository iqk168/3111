#if !defined(AFX_DLGERROR_H__11289F57_29EA_4E3E_9D44_FECDCCA60DAB__INCLUDED_)
#define AFX_DLGERROR_H__11289F57_29EA_4E3E_9D44_FECDCCA60DAB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgError.h : header file
//

#include "ErrView.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgError dialog

class CDlgError : public CDialog
{
// Construction
public:
	void Close();
	CDlgError(tagErrorMsg *e, CWnd* pParent = NULL);   // standard constructor

	void ButtonQuery();
	long m_lStart;

// Dialog Data
	//{{AFX_DATA(CDlgError)
	enum { IDD = IDD_ERROR_DIALOG };
	CColorFontStatic	m_ledTestSiteSkip;
	CColorFontStatic	m_ledReset;
	CColorFontStatic	m_ledSkip;
	CColorFontStatic	m_ledRetry;
	CButton				m_btnReset;
	CButton				m_btnRetry;
	CButton				m_btnSkip;
	CStatic				m_wndLayout;
	CButton				m_wndMessage;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgError)
	public:
	virtual BOOL DestroyWindow();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void PostNcDestroy();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgError)
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnMsg();
	afx_msg void OnClose();
	afx_msg void OnDestroy();
	afx_msg void OnSkip();
	afx_msg void OnRetry();
	afx_msg void OnReset();
	afx_msg void OnTestSiteSkip();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

protected:
	tagErrorMsg *msg;
	CErrView *pView;
	int count;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGERROR_H__11289F57_29EA_4E3E_9D44_FECDCCA60DAB__INCLUDED_)
