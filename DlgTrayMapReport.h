#if !defined(AFX_DLGTRAYMAPREPORT_H__E7ABC29C_51C4_4C30_98D2_B9C15FC29650__INCLUDED_)
#define AFX_DLGTRAYMAPREPORT_H__E7ABC29C_51C4_4C30_98D2_B9C15FC29650__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgTrayMapReport.h : header file
//

#include "ViewTrayMap.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgTrayMapReport dialog

class CDlgTrayMapReport : public CDialog
{
// Construction
public:
	CDlgTrayMapReport(CWnd* pParent = NULL);   // standard constructor

	CToolTipCtrl m_ToolTip;

	void InitValue();
	void InitTips();
	void InitTrayMap();
	//
	void UpdateView();

	//
	CViewTrayMap *pViewTrayOutput1; // Tray Output 1 ( Pass )

public:

	void InitFilePath();
	CString GetFilePath();

// Dialog Data
	//{{AFX_DATA(CDlgTrayMapReport)
	enum { IDD = IDD_DLG_TRAYMAP_REPORT };
	CEdit	m_edtTrayMapReportPath;
	CButtonST	m_btnExport;
	CStatic	m_wndOutputTray1;
	CButtonST	m_btnCancel;
	CButtonST	m_btnOK;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgTrayMapReport)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgTrayMapReport)
	afx_msg void OnTimer(UINT nIDEvent);
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnExport();
	afx_msg void OnBTraymapReportPath();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGTRAYMAPREPORT_H__E7ABC29C_51C4_4C30_98D2_B9C15FC29650__INCLUDED_)
