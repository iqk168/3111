#if !defined(AFX_DLGDEBUGERRORLIST_H__55D51561_6320_4030_8D5A_184DF8FB61E4__INCLUDED_)
#define AFX_DLGDEBUGERRORLIST_H__55D51561_6320_4030_8D5A_184DF8FB61E4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgDebugErrorList.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgDebugErrorList dialog

class CDlgDebugErrorList : public CDialog
{
// Construction
public:
	CDlgDebugErrorList(CWnd* pParent = NULL);   // standard constructor


	//
	typedef struct tagErrorCodeListItem 
	{
		long	item;
		long	code;
		int		level;
		CString desc;
		CString operation;
	} tagErrorCodeListItem;

	CArray <tagErrorCodeListItem, tagErrorCodeListItem> m_Source;

	//
	void InitValue();
	void ShowTitle();

	void Style();

	void UpdataEngList();
	void UpdataChiList();
	void UpdataSimChiList();
	void UpdataModifyDate();

	//
	int iSel;

	int m_iErrorCodeCount;

// Dialog Data
	//{{AFX_DATA(CDlgDebugErrorList)
	enum { IDD = IDD_DLG_DEBUG_ERR_LIST };
	CButtonST	m_btnOK;
	CButtonST	m_btnCancel;
	CListCtrl	m_listData;
	CStatic	m_wndModifyData;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgDebugErrorList)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgDebugErrorList)
	virtual void OnOK();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnGetdispinfoData(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDblclkData(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnClickData(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnRclickData(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnModifyData();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGDEBUGERRORLIST_H__55D51561_6320_4030_8D5A_184DF8FB61E4__INCLUDED_)
