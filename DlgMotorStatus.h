#if !defined(AFX_DLGMOTORSTATUS_H__E6D93EE3_5593_4BB3_9698_7D6E921B0A3F__INCLUDED_)
#define AFX_DLGMOTORSTATUS_H__E6D93EE3_5593_4BB3_9698_7D6E921B0A3F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgMotorStatus.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgMotorStatus dialog

class CDlgMotorStatus : public CDialog
{
// Construction
public:
	CDlgMotorStatus(CWnd* pParent = NULL);   // standard constructor

	void UpdataMotorStatus();
	void UpdataMotorSpeedStatus();

	void SelectMotor();

	// Board 0
	tagMotorParam *InserterMotor;
	tagMotorParam *ArmXMotor;
	tagMotorParam *ArmYMotor;
	tagMotorParam *ArmZMotor;

// Dialog Data
	//{{AFX_DATA(CDlgMotorStatus)
	enum { IDD = IDD_DLG_MOTOR_STATUS };
	CButtonST	m_btnCancel;
	CButtonST	m_btnOK;
	CString	m_csArmX;
	CString	m_csArmY;
	CString	m_csArmZ;
	CString	m_csInserter;
	CString	m_csArmX2;
	CString	m_csArmY2;
	CString	m_csArmZ2;
	CString	m_csInserter2;

	//}}AFX_DATA

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgMotorStatus)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgMotorStatus)
	virtual void OnOK();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnDestroy();
	afx_msg void OnClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGMOTORSTATUS_H__E6D93EE3_5593_4BB3_9698_7D6E921B0A3F__INCLUDED_)
