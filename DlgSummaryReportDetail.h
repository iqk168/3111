#if !defined(AFX_DLGSUMMARYREPORTDETAIL_H__1D866657_6D1B_44A4_BE8D_FC262DF44112__INCLUDED_)
#define AFX_DLGSUMMARYREPORTDETAIL_H__1D866657_6D1B_44A4_BE8D_FC262DF44112__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgSummaryReportDetail.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgSummaryReportDetail dialog

class CDlgSummaryReportDetail : public CDialog
{
// Construction
public:
	CDlgSummaryReportDetail(CString csFile = "", CWnd* pParent = NULL);   // standard constructor

	CString m_file;
	void InitValue();

	//
	CString csNote;

// Dialog Data
	//{{AFX_DATA(CDlgSummaryReportDetail)
	enum { IDD = IDD_DLG_SUMMARY_REPORT_DETAIL };
	CRichEditCtrl	m_wndSummaryReport;
	CStatic	m_wndFileName;
	CButtonST	m_btnOK;
	CButtonST	m_btnCancel;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgSummaryReportDetail)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgSummaryReportDetail)
	virtual void OnOK();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGSUMMARYREPORTDETAIL_H__1D866657_6D1B_44A4_BE8D_FC262DF44112__INCLUDED_)
