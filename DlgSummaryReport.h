#if !defined(AFX_DLGSUMMARYREPORT_H__86D5766C_113E_432C_9531_16FF570447EB__INCLUDED_)
#define AFX_DLGSUMMARYREPORT_H__86D5766C_113E_432C_9531_16FF570447EB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgSummaryReport.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgSummaryReport dialog

class CDlgSummaryReport : public CDialog
{
// Construction
public:
	CDlgSummaryReport(CWnd* pParent = NULL);   // standard constructor

	//
	typedef struct tagSummaryReportItem 
	{
		long	item;
		CString filename;
		CString createtime;
	} tagSummaryReportItem;

	CArray <tagSummaryReportItem, tagSummaryReportItem> m_Source;

	//
	CString csFile;

	//
	void Style();

	//
	void InitValue();
	void ShowTitle();
	void ShowData();

	//
	void SetColumn(int vlaue);

// Dialog Data
	//{{AFX_DATA(CDlgSummaryReport)
	enum { IDD = IDD_DLG_SUMMARY_REPORT };
	CButtonST	m_btnDel;
	CButtonST	m_btnDelAll;
	CStatic	m_wndFileCount;
	CListCtrl	m_listData;
	CButtonST	m_btnCancel;
	CButtonST	m_btnOK;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgSummaryReport)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgSummaryReport)
	virtual void OnOK();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnGetdispinfoData(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDelAll();
	afx_msg void OnDel();
	afx_msg void OnClickData(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDblclkData(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGSUMMARYREPORT_H__86D5766C_113E_432C_9531_16FF570447EB__INCLUDED_)
