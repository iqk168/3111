#if !defined(AFX_DLGATCMODULEFILE_H__56D669F9_FCBB_4346_BE42_4D47D92CF941__INCLUDED_)
#define AFX_DLGATCMODULEFILE_H__56D669F9_FCBB_4346_BE42_4D47D92CF941__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgATCModuleFile.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgATCModuleFile dialog

class CDlgATCModuleFile : public CDialog
{
// Construction
public:
	CDlgATCModuleFile(CWnd* pParent = NULL);   // standard constructor

	//
	typedef struct tagATCFileItem 
	{
		long	item;
		CString filename;
		CString createtime;
	} tagATCFileItem;

	CArray <tagATCFileItem, tagATCFileItem> m_Source;

	//
	CString csFile;

	//
	void Style();
	void ShowTitle();
	void ShowData();
	void InitValue();
	void SetUsingFile();

// Dialog Data
	//{{AFX_DATA(CDlgATCModuleFile)
	enum { IDD = IDD_DLG_ATC_MODULE_FILE };
	CStatic	m_wndFile;
	CStatic	m_wndFileCount;
	CButtonST	m_btnSetFile;
	CButtonST	m_btnDelete;
	CListCtrl	m_listData;
	CButtonST	m_btnSetting;
	CButtonST	m_btnNew;
	CButtonST	m_btnOK;
	CButtonST	m_btnCancel;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgATCModuleFile)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgATCModuleFile)
	virtual BOOL OnInitDialog();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnClickData(NMHDR* pNMHDR, LRESULT* pResult);
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnFNew();
	afx_msg void OnFSetting();
	afx_msg void OnDel();
	afx_msg void OnSet();
	afx_msg void OnGetdispinfoData(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDblclkData(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGATCMODULEFILE_H__56D669F9_FCBB_4346_BE42_4D47D92CF941__INCLUDED_)
