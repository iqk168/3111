#if !defined(AFX_DLGLOTINFORMATIONDONE_H__791FD80C_8ECC_4F79_86E0_D24CDACBA2FB__INCLUDED_)
#define AFX_DLGLOTINFORMATIONDONE_H__791FD80C_8ECC_4F79_86E0_D24CDACBA2FB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgLotInformationDone.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgLotInformationDone dialog

class CDlgLotInformationDone : public CDialog
{
// Construction
public:
	CDlgLotInformationDone(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgLotInformationDone)
	enum { IDD = IDD_LOT_INFO_DONE };
	CEdit	m_wndLotDeviceID;
	CEdit	m_wndLotMachineID;
	CEdit	m_wndLotNo;
	CEdit	m_wndLotOperator;
	CEdit	m_wndLotProgramerID;
	CButtonST	m_btnCancel;
	CButtonST	m_btnOK;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgLotInformationDone)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	void UpdataValue();
	void UpdataUI(bool ui);
	// Generated message map functions
	//{{AFX_MSG(CDlgLotInformationDone)
	afx_msg void OnDestroy();
	virtual BOOL OnInitDialog();
	afx_msg void OnClose();
	virtual void OnOK();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGLOTINFORMATIONDONE_H__791FD80C_8ECC_4F79_86E0_D24CDACBA2FB__INCLUDED_)
