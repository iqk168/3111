#if !defined(AFX_DLGJAMRATEREPORTTOOL_H__44357BE1_FBE3_404D_991D_BFF876A28236__INCLUDED_)
#define AFX_DLGJAMRATEREPORTTOOL_H__44357BE1_FBE3_404D_991D_BFF876A28236__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgJamRateReportTool.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgJamRateReportTool dialog

class CDlgJamRateReportTool : public CDialog
{
// Construction
public:
	CDlgJamRateReportTool(CWnd* pParent = NULL);   // standard constructor

	//
	void InitValue();
	
	// Error Rate Report
	typedef struct tagRateDataLogDataItem{
		int iItem;
		int iCode;
		CString csDesc;
		int iCount;
		CString csDetail;
	} tagRateDataLogDataItem;
	CArray <tagRateDataLogDataItem, tagRateDataLogDataItem> m_Source;

	//
	void Style();
	void ShowTitle();
	void ShowData();

	//
	CString GetCodeNoteDesc(int iErrorCode );
	CString GetCodeDesc(int iErrorCode );

	//
	void ReDisplayUpdata();

// Dialog Data
	//{{AFX_DATA(CDlgJamRateReportTool)
	enum { IDD = IDD_DLG_JAM_RATE_REPORT };
	CButtonST	m_btnLastReport;
	CStatic	m_wndUpdateTime;
	CButtonST	m_btnRefreash;
	CStatic	m_wndTotalIC;
	CStatic	m_wndLotStart;
	CStatic	m_wndLotNumber;
	CListCtrl	m_listData;
	CButtonST	m_btnOK;
	CButtonST	m_btnCancel;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgJamRateReportTool)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgJamRateReportTool)
	virtual void OnOK();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnGetdispinfoData(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnRefreash();
	afx_msg void OnLastReport();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGJAMRATEREPORTTOOL_H__44357BE1_FBE3_404D_991D_BFF876A28236__INCLUDED_)
