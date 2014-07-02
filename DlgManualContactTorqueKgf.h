#if !defined(AFX_DLGMANUALCONTACTTORQUEKGF_H__915A0316_9BAA_4ACB_B59A_098A570FB8BC__INCLUDED_)
#define AFX_DLGMANUALCONTACTTORQUEKGF_H__915A0316_9BAA_4ACB_B59A_098A570FB8BC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgManualContactTorqueKgf.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgManualContactTorqueKgf dialog

class CDlgManualContactTorqueKgf : public CDialog
{
// Construction
public:
	CDlgManualContactTorqueKgf(CWnd* pParent = NULL);   // standard constructor

	void InitValue();
	void InitCbxKgf();
	bool SaveData();

// Dialog Data
	//{{AFX_DATA(CDlgManualContactTorqueKgf)
	enum { IDD = IDD_DLG_MANUAL_CONTACT_TORQUE_KGF };
	CComboBox	m_cbxKgf;
	CStatic	m_wndContactForce;
	CButtonST	m_btnSet;
	CButtonST	m_btnCancel;
	CButtonST	m_btnOK;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgManualContactTorqueKgf)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgManualContactTorqueKgf)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnWriteToCont();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGMANUALCONTACTTORQUEKGF_H__915A0316_9BAA_4ACB_B59A_098A570FB8BC__INCLUDED_)
