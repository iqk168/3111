#if !defined(AFX_DLGUPHTOOL_H__C39A95AA_82B2_4BF0_A8BA_D499D8841E1A__INCLUDED_)
#define AFX_DLGUPHTOOL_H__C39A95AA_82B2_4BF0_A8BA_D499D8841E1A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgUPHTool.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgUPHTool dialog

class CDlgUPHTool : public CDialog
{
// Construction
public:
	CDlgUPHTool(CWnd* pParent = NULL);   // standard constructor

	void InitUI();

	void ShowTSData();
	void ClearTSData();

public:
	void UpdataClearAllInfo();
	void UpdataTsInfo();
	void AvgTs();

// Dialog Data
	//{{AFX_DATA(CDlgUPHTool)
	enum { IDD = IDD_DLG_UPH_TOOL };
	CStatic		m_wndTsAvg;
	CButtonST	m_btnOK;
	CButtonST	m_btnCancel;
	CListBox	m_listUPHTS;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgUPHTool)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgUPHTool)
	afx_msg void OnTimer(UINT nIDEvent);
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnTsClear();
	afx_msg void OnTsExport();
	afx_msg LRESULT OnUPHTs(WPARAM p, LPARAM l);
	afx_msg LRESULT OnUPHClear(WPARAM p, LPARAM l);
	afx_msg void OnDblclkDataTs();
	afx_msg void OnStaticTsAvg();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGUPHTOOL_H__C39A95AA_82B2_4BF0_A8BA_D499D8841E1A__INCLUDED_)
