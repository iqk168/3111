#if !defined(AFX_DLGEVENT_H__07A3CC98_6632_49CE_A430_6EA2D99DE578__INCLUDED_)
#define AFX_DLGEVENT_H__07A3CC98_6632_49CE_A430_6EA2D99DE578__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgEvent.h : header file
//

#include <afxtempl.h> // For CArrary

/////////////////////////////////////////////////////////////////////////////
// CDlgEvent dialog

class CDlgEvent : public CDialog
{
// Construction
public:
	CDlgEvent(bool Mode = false, CWnd* pParent = NULL);   // standard constructor

	bool m_Mode; // default is false. Is User have new request. Use it to make different.!

	
// Dialog Data
	//{{AFX_DATA(CDlgEvent)
	enum { IDD = IDD_EVENT };
	CButtonST	m_btnExport;
	CButtonST	m_btnShowTwoMonth;
	CButtonST	m_btnDelete;
	CListCtrl	m_listEvent;
	CButtonST	m_btnCancel;
	CButtonST	m_btnOK;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgEvent)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void ShowData(int iMonth);
	typedef struct tagItem 
	{
		long level;
		CTime time;
		long code;
		CString message;
	} tagItem;
	CArray <tagItem, tagItem> m_Member;
protected:
	void SetHeaderImage(int iItem);
	static int __cdecl LevelCompare(const void *elem1, const void *elem2);
	static int __cdecl MsgCompare(const void *elem1, const void *elem2);
	static int __cdecl CodeCompare(const void *elem1, const void *elem2);
	static int __cdecl TimeCompare(const void *elem1, const void *elem2);
	// Generated message map functions
	//{{AFX_MSG(CDlgEvent)
	afx_msg void OnClose();
	afx_msg void OnDestroy();
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT nIDEvent);
	virtual void OnCancel();
	virtual void OnOK();
	afx_msg void OnColumnclickEvent(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnGetdispinfoEvent(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDelete();
	afx_msg void OnShowTwoMonth();
	afx_msg void OnExport();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGEVENT_H__07A3CC98_6632_49CE_A430_6EA2D99DE578__INCLUDED_)
