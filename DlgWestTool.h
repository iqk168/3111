#if !defined(AFX_DLGWESTTOOL_H__B14D6049_851F_401A_81B0_E8E13CDC6687__INCLUDED_)
#define AFX_DLGWESTTOOL_H__B14D6049_851F_401A_81B0_E8E13CDC6687__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgWestTool.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgWestTool dialog

class CDlgWestTool : public CDialog
{
// Construction
public:
	CDlgWestTool(CWnd* pParent = NULL);   // standard constructor

	void InitWestSel();
	void InitUI();
	void TemperatureQuery();

	//
	int m_iWestID;

// Dialog Data
	//{{AFX_DATA(CDlgWestTool)
	enum { IDD = IDD_DLG_WEST_TOOL };
	CColorFontStatic	m_wndOffset;
	CColorFontStatic	m_wndPv;
	CColorFontStatic	m_wndSv;
	CComboBox	m_wndWestSel;
	CButtonST	m_btnOK;
	CButtonST	m_btnCancel;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgWestTool)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgWestTool)
	virtual void OnOK();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnEditchangeFSelWest();
	afx_msg void OnSelchangeFSelWest();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGWESTTOOL_H__B14D6049_851F_401A_81B0_E8E13CDC6687__INCLUDED_)
