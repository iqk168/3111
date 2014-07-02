#if !defined(AFX_DLGMANUALCONTACT_H__4173846B_9698_4B3E_A0BA_F1694632A553__INCLUDED_)
#define AFX_DLGMANUALCONTACT_H__4173846B_9698_4B3E_A0BA_F1694632A553__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgManualContact.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgManualContact dialog

class CDlgManualContact : public CDialog
{
// Construction
public:
	CDlgManualContact(CWnd* pParent = NULL);   // standard constructor

	void InitUI();

	void UILockForContact();
	void UILockForUp();
	void UIUnLockForContacted();
	void UIUnLockForUPed();
	void UILockFunction();
	void UIUnLockFunction();

	// 1.0Ab
	void UIContactedLockFunction();
	void UIUpUnLockFunction();

	//
	bool m_bUpOK;
	bool m_bAlarm;

	//
	CToolTipCtrl m_ToolTip;
	void InitTips();

	//
	void UpdateMotorStatus();
	void UpdatePositionStatus();

	void GetButtonDistance(int &Width, int &Height, int &WDistance, int &HDistance);

	//
	void ReDrawUI();

	// Error Ctrl
	BOOL bManualUpStatus;
	BOOL bManualDownStatus;
	BOOL bManualMoveStatus;
	void ErrorBackupUI();
	void ErrorRecoverUI();

public:
	// 1.0Ab
	void ReDrawForTsMode();
	void ReDrawForTsVacc();

public:
	// 1.0Ah
	void InitManualContactNote();

// Dialog Data
	//{{AFX_DATA(CDlgManualContact)
	enum { IDD = IDD_DLG_MANUAL_CONTACT };
	CRichEditCtrl	m_wndManualContactNote;
	CButtonST			m_btnTestSiteVacc;
	CButtonST			m_btnTestSiteMode;
	CButtonST			m_btnFContinue;
	CButtonST			m_btnTorqueControl;
	CColorFontStatic	m_wndResult;
	CColorFontStatic	m_wndCurrentHeight;
	CColorFontStatic	m_wndCommandContactHeight;
	CButtonST			m_btnFUp;
	CButtonST			m_btnFMove;
	CButtonST			m_btnFDown;
	CButtonST			m_btnTemperature;
	CButtonST			m_btnOffset;
	CButtonST			m_btnInterfaceTesting;
	CButtonST			m_btnCancel;
	CButtonST			m_btnOK;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgManualContact)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgManualContact)
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnFTemperature();
	afx_msg void OnFInterfaceTesting();
	afx_msg void OnFOffset();
	afx_msg void OnFUp();
	afx_msg void OnFDown();
	afx_msg void OnFMove();
	afx_msg LRESULT OnTSContacted(WPARAM p, LPARAM l);
	afx_msg LRESULT OnTSUped(WPARAM p, LPARAM l);
	afx_msg LRESULT OnTSMved(WPARAM p, LPARAM l);
	afx_msg LRESULT OnAlarm(WPARAM p, LPARAM l);
	afx_msg void OnFTorque();
	afx_msg void OnFContinue();
	afx_msg void OnFTsMode();
	afx_msg void OnFTsVacc();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGMANUALCONTACT_H__4173846B_9698_4B3E_A0BA_F1694632A553__INCLUDED_)
