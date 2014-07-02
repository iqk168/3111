#if !defined(AFX_DLGHANDLERSTATUS_H__8C31F782_43DB_42BC_ABC6_EA2C9FD377CB__INCLUDED_)
#define AFX_DLGHANDLERSTATUS_H__8C31F782_43DB_42BC_ABC6_EA2C9FD377CB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgHandlerStatus.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgHandlerStatus dialog

class CDlgHandlerStatus : public CDialog
{
// Construction
public:
	CDlgHandlerStatus(CString csFile, CWnd* pParent = NULL);   // standard constructor

	CString m_csFile;

	//
	void LoadFile( CString csFileName  );

	//
	//
	typedef struct tagHandlerStatusReportLogItem 
	{
		long		item;
		CString	    data;
		CString		type;
		CString		desc;

	} tagHandlerStatusReportLogItem;	

	//
	CArray <tagHandlerStatusReportLogItem, tagHandlerStatusReportLogItem> m_Source;
	
	//
	struct tagHandlerStatusFileData
	{
		CArray <CString, CString> csDate;
		CArray <CString, CString> csType;
		CArray <CString, CString> csDesc;

	} m_HandlerStatusFileData;

	//
	void InitValue();
	void Style();
	void ShowTitle();
	void ShowData();

	//
	int GetSel();

// Dialog Data
	//{{AFX_DATA(CDlgHandlerStatus)
	enum { IDD = IDD_DLG_HANDLER_STATUS };
	CButtonST	m_btnOK;
	CButtonST	m_btnCancel;
	CListCtrl	m_listData;
	CStatic		m_wndFile;
	CButton		m_btnType;
	int			m_iSel;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgHandlerStatus)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgHandlerStatus)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnGetdispinfoData(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnType();
	afx_msg void OnType2();
	afx_msg void OnType3();
	afx_msg void OnType4();
	afx_msg void OnType5();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGHANDLERSTATUS_H__8C31F782_43DB_42BC_ABC6_EA2C9FD377CB__INCLUDED_)
