#if !defined(AFX_DLGTORQUECONTROL_H__80F1DCA0_03AE_4B52_AF2C_31862748DF45__INCLUDED_)
#define AFX_DLGTORQUECONTROL_H__80F1DCA0_03AE_4B52_AF2C_31862748DF45__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgTorqueControl.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgTorqueControl dialog

class CDlgTorqueControl : public CDialog
{
// Construction
public:
	CDlgTorqueControl(CWnd* pParent = NULL);   // standard constructor

	void InitValue();
	bool SaveData();

	bool m_fChange;

// Dialog Data
	//{{AFX_DATA(CDlgTorqueControl)
	enum { IDD = IDD_DLG_TORQUE_CONTROL };
	CEdit	m_wndPowerValue;
	CButtonST	m_btnCancel;
	CButtonST	m_btnOK;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgTorqueControl)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgTorqueControl)
	virtual void OnOK();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnChangePower();
	afx_msg void OnSet();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGTORQUECONTROL_H__80F1DCA0_03AE_4B52_AF2C_31862748DF45__INCLUDED_)
