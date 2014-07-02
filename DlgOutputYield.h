#if !defined(AFX_DLGOUTPUTYIELD_H__3486D543_79AB_4DD0_B424_2BCB286EFF66__INCLUDED_)
#define AFX_DLGOUTPUTYIELD_H__3486D543_79AB_4DD0_B424_2BCB286EFF66__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgOutputYield.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgOutputYield dialog

class CDlgOutputYield : public CDialog
{
// Construction
public:
	CDlgOutputYield(CWnd* pParent = NULL);   // standard constructor

	void InitValue();
	void Style();
	void ShowTitle();
	void ShowData();

	void ShowValue();

// Dialog Data
	//{{AFX_DATA(CDlgOutputYield)
	enum { IDD = IDD_DLG_OUTPUT_YIELD };
	CListCtrl	m_listData;
	CButtonST	m_btnOK;
	CButtonST	m_btnCancel;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgOutputYield)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgOutputYield)
	virtual void OnOK();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGOUTPUTYIELD_H__3486D543_79AB_4DD0_B424_2BCB286EFF66__INCLUDED_)
