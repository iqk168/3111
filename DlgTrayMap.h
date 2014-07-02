#if !defined(AFX_DLGTRAYMAP_H__483E9EF1_F401_47E2_99EF_7FA61C7A32C4__INCLUDED_)
#define AFX_DLGTRAYMAP_H__483E9EF1_F401_47E2_99EF_7FA61C7A32C4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgTrayMap.h : header file
//

#include "ViewTrayMap.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgTrayMap dialog

class CDlgTrayMap : public CDialog
{
// Construction
public:
	CDlgTrayMap(CWnd* pParent = NULL);   // standard constructor

	CToolTipCtrl m_ToolTip;

	void InitValue();
	void InitTips();
	void InitTrayMap();
	//
	void UpdateView();

	//
	CViewTrayMap *pViewTrayOutput1; // Tray Output 1 ( Pass )

// Dialog Data
	//{{AFX_DATA(CDlgTrayMap)
	enum { IDD = IDD_DLG_TRAYMAP };
	CButtonST	m_btnExport;
	CStatic	m_wndOutputTray1;
	CButtonST	m_btnCancel;
	CButtonST	m_btnOK;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgTrayMap)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgTrayMap)
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT nIDEvent);
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnStaticColor();
	afx_msg void OnExport();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGTRAYMAP_H__483E9EF1_F401_47E2_99EF_7FA61C7A32C4__INCLUDED_)
