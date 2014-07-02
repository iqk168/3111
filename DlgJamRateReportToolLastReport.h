#if !defined(AFX_DLGJAMRATEREPORTTOOLLASTREPORT_H__C3285986_4DD8_4D12_A94A_14B7411F0372__INCLUDED_)
#define AFX_DLGJAMRATEREPORTTOOLLASTREPORT_H__C3285986_4DD8_4D12_A94A_14B7411F0372__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgJamRateReportToolLastReport.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgJamRateReportToolLastReport dialog

class CDlgJamRateReportToolLastReport : public CDialog
{
// Construction
public:
	CDlgJamRateReportToolLastReport(CWnd* pParent = NULL);   // standard constructor

	void InitValue();

// Dialog Data
	//{{AFX_DATA(CDlgJamRateReportToolLastReport)
	enum { IDD = IDD_DLG_JAM_RATE_REPORT_LAST };
	CStatic	m_wndFileTime;
	CRichEditCtrl	m_wndErrorRateReport;
	CButtonST	m_btnCancel;
	CButtonST	m_btnOK;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgJamRateReportToolLastReport)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgJamRateReportToolLastReport)
	virtual void OnOK();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGJAMRATEREPORTTOOLLASTREPORT_H__C3285986_4DD8_4D12_A94A_14B7411F0372__INCLUDED_)
