#if !defined(AFX_DLGSPEED_H__EC160535_98F7_4480_9B4E_CB9C1DD3E11E__INCLUDED_)
#define AFX_DLGSPEED_H__EC160535_98F7_4480_9B4E_CB9C1DD3E11E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgSpeed.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgSpeed dialog

class CDlgSpeed : public CDialog
{
// Construction
public:
	CDlgSpeed(CWnd* pParent = NULL);   // standard constructor

	void InitValue();
	bool m_fChange;
	bool m_SameForAll;


	void GetAllValue();		// Get All speed value from dialog.
	bool CheckAllValue();	// Check value range. User can change by Debug dialog

	// This is for HS control 
	// If cancel for same for all motor parameter.
	int		m_iSpeedArmX_Pos;
	int		m_iSpeedArmY_Pos;
	int		m_iSpeedArmZ_Pos;
	int		m_iSpeedInserter_Pos;

	//
public:
	CToolTipCtrl m_ToolTip;
	void InitTips();

// Dialog Data
	//{{AFX_DATA(CDlgSpeed)
	enum { IDD = IDD_DLG_SPEED };
	CStatic	m_wndSpeedTitle;
	CButtonST	m_btnSameForAll;
	CButtonST	m_btnCancelSame;
	CSliderCtrl	m_wndSlInserter;
	CSliderCtrl	m_wndSlArmZ;
	CSliderCtrl	m_wndSlArmX;
	CButtonST	m_btnOK;
	CButtonST	m_btnCancel;
	int			m_iSpeedArmX;
	int			m_iSpeedArmY;
	int			m_iSpeedArmZ;
	int			m_iSpeedInserter;
	//}}AFX_DATA

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgSpeed)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgSpeed)
	afx_msg void OnClose();
	afx_msg void OnDestroy();
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnCancelSame();
	//
	afx_msg void OnChangeSpeedArmX();
	afx_msg void OnChangeSpeedArmZ();
	afx_msg void OnChangeSpeedInserter();
	//
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnAllSame();
	
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGSPEED_H__EC160535_98F7_4480_9B4E_CB9C1DD3E11E__INCLUDED_)
