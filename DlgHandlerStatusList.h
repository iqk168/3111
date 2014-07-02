#if !defined(AFX_DLGHANDLERSTATUSLIST_H__A37DE30E_84A9_4A5C_9560_BC69A3ABC60A__INCLUDED_)
#define AFX_DLGHANDLERSTATUSLIST_H__A37DE30E_84A9_4A5C_9560_BC69A3ABC60A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgHandlerStatusList.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgHandlerStatusList dialog

class CDlgHandlerStatusList : public CDialog
{
// Construction
public:
	CDlgHandlerStatusList(CWnd* pParent = NULL);   // standard constructor

	//
	typedef struct tagHandlerStatusLogListItem 
	{
		long		 item;
		CString		 filename;
		CString		 data;

	} tagHandlerStatusLogListItem;	

	//
	CArray <tagHandlerStatusLogListItem, tagHandlerStatusLogListItem> m_Source;

	//
	void InitValue();
	void Style();
	void ShowTitle();
	void ShowData();
	int GetFileCount();
	void DeleteFile(CString filename);
	void DeleteFileeAll();

	//
	CString csSelFile;

// Dialog Data
	//{{AFX_DATA(CDlgHandlerStatusList)
	enum { IDD = IDD_DLG_HANDLER_STATUS_LIST };
	CButtonST	m_btnOK;
	CButtonST	m_btnCancel;
	CButtonST	m_btnDelAll;
	CButtonST	m_btnDel;
	CListCtrl	m_listData;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgHandlerStatusList)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgHandlerStatusList)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnGetdispinfoData(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDelAll();
	afx_msg void OnDel();
	afx_msg void OnDblclkData(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnClickData(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGHANDLERSTATUSLIST_H__A37DE30E_84A9_4A5C_9560_BC69A3ABC60A__INCLUDED_)
