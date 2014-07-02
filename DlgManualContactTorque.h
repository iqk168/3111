#if !defined(AFX_DLGMANUALCONTACTTORQUE_H__4708D65B_F7FE_49C8_8C36_4A0C4AEB1973__INCLUDED_)
#define AFX_DLGMANUALCONTACTTORQUE_H__4708D65B_F7FE_49C8_8C36_4A0C4AEB1973__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgManualContactTorque.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgManualContactTorque dialog

class CDlgManualContactTorque : public CDialog
{
// Construction
public:
	CDlgManualContactTorque(CWnd* pParent = NULL);   // standard constructor

	void InitUI();
	void SaveDataToFile(CString csTrayFileName);
	void InitValue();

	void ConvertKgf();

	tagTsFloatingParameter m_TsFloatingParameter;

// Dialog Data
	//{{AFX_DATA(CDlgManualContactTorque)
	enum { IDD = IDD_DLG_MANUAL_CONTACT_TORQUE };
	CButtonST	m_btnSet;
	CStatic	m_wndForce;
	CComboBox	m_cbxPogoForce;
	CComboBox	m_cbxPogoCount;
	CButtonST	m_btnOK;
	CButtonST	m_btnCancel;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgManualContactTorque)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgManualContactTorque)
	virtual void OnOK();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangePPogoCount();
	afx_msg void OnSelchangePPogoForce();
	afx_msg void OnWriteToCont();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGMANUALCONTACTTORQUE_H__4708D65B_F7FE_49C8_8C36_4A0C4AEB1973__INCLUDED_)
