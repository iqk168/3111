#if !defined(AFX_DLGTESTTESTING_H__9319BC39_6CE3_48C3_81C1_2DA18FEBCDC3__INCLUDED_)
#define AFX_DLGTESTTESTING_H__9319BC39_6CE3_48C3_81C1_2DA18FEBCDC3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgTestTesting.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgTestTesting dialog

#include "ColorBtn.h"

class CDlgTestTesting : public CDialog
{
// Construction
public:
	CDlgTestTesting(CWnd* pParent = NULL);   // standard constructor

	void UpdataInterfaceTypeButton();
	void GetButtonDistance(int &Width, int &Distance);

	//
	void LockUI();
	int LoadInterfaceType();
	void SetDefaultIf(int iIf);
	void ButtonUpdataStatus();

	//
	void ShowInformation(CString csInfo);
	void ClearAllInformation();

	//
	static UINT TestingThread(LPVOID p);
	void TestingLockUI(bool bEnable);
	void TestingSetIf(int b1, int b2, int b3, int b4);
	int m_iIfType;

public:
	void InitInfo();

// Dialog Data
	//{{AFX_DATA(CDlgTestTesting)
	enum { IDD = IDD_DLG_TEST_TESTING };
	CStatic	m_wndTesterInfo;
	CListBox	m_list;
	CButton	m_btnClear;
	CButton	m_btnSend;
	CButtonST	m_btnOK;
	CButtonST	m_btnCancel;
	CButton		m_Index2;
	CButton		m_Index1;
	CColorBtn	m_btnRs232;
	CColorBtn	m_btnGbip;
	CColorBtn	m_btnTcpip;
	CColorBtn	m_btnTtl;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgTestTesting)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgTestTesting)
	virtual void OnCancel();
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnITtl();
	afx_msg void OnIRs232();
	afx_msg void OnIGpib();
	afx_msg void OnITcp();
	afx_msg void OnESend();
	afx_msg void OnEClear();
	afx_msg LRESULT OnTestingMessage(WPARAM p, LPARAM l);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGTESTTESTING_H__9319BC39_6CE3_48C3_81C1_2DA18FEBCDC3__INCLUDED_)
