#if !defined(AFX_DLGFILEPATH_H__5DB9BB06_2BF6_48FB_934E_CEAC73DB6646__INCLUDED_)
#define AFX_DLGFILEPATH_H__5DB9BB06_2BF6_48FB_934E_CEAC73DB6646__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgFilePath.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgFilePath dialog

class CDlgFilePath : public CDialog
{
// Construction
public:
	CDlgFilePath(CWnd* pParent = NULL);   // standard constructor

	void InitValue();

	CString GetFilePath();

	tagCustomFilePath m_CustomFilePath;

// Dialog Data
	//{{AFX_DATA(CDlgFilePath)
	enum { IDD = IDD_DLG_FILE_PATH };
	CEdit	m_edtSLTProtocolPath;
	CEdit	m_edtUPHReportPath;
	CEdit	m_edtTrayMapReportPath;
	CEdit	m_edtMultiSVSVTrayMapPath;
	CEdit	m_edtEventLogPath;
	CEdit	m_edtMultiSVReportPath;
	CEdit	m_edtMultiSVProgramPath;
	CEdit	m_edtLoopTestReport;
	CButtonST	m_btnOK;
	CButtonST	m_btnCancel;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgFilePath)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgFilePath)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnBTraymapReportPath();
	afx_msg void OnBEventLogPath();
	afx_msg void OnBLoopTestResultPath();
	afx_msg void OnBTestTrayMapPath();
	afx_msg void OnBTestResultReportPath();
	afx_msg void OnBMultisvProgramPath();
	afx_msg void OnBUphReport();
	afx_msg void OnBSltProtocolPath();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGFILEPATH_H__5DB9BB06_2BF6_48FB_934E_CEAC73DB6646__INCLUDED_)
