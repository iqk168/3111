#if !defined(AFX_DLGALIGNMENTCHECK_H__9C3A6918_DC2D_4976_BBC6_475CB8ABEC44__INCLUDED_)
#define AFX_DLGALIGNMENTCHECK_H__9C3A6918_DC2D_4976_BBC6_475CB8ABEC44__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgAlignmentCheck.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgAlignmentCheck dialog

class CDlgAlignmentCheck : public CDialog
{
// Construction
public:
	CDlgAlignmentCheck(CWnd* pParent = NULL);   // standard constructor

	static UINT AlignmnetCheckThread(LPVOID p);
	static UINT AlignmnetCheckTSThread(LPVOID p);
	static UINT AlignmnetCheckShuttleThread(LPVOID p);
	static UINT AlignmnetCheckInputStackThread(LPVOID p);
	static UINT AlignmnetCheckOutputStackThread(LPVOID p);


	// Arm XYZ Pos
	long m_ArmXPos;
	long m_ArmYPos;
	long m_ArmZPos;

	// Test Site Pos
	long m_TestSiteArmPos;

	// Test Site Home Pos
	long m_TestSiteArmHomePos;

	// Shuttle / Pick / Place
	long m_ShuttlePos; // 0 home, 1 pick/place

	// Input/Output 
	CPoint px;

	void LockUI(bool bEnable);

// Dialog Data
	//{{AFX_DATA(CDlgAlignmentCheck)
	enum { IDD = IDD_DLG_ALIGNMENT_CHECK };
	CButton	m_btnMoveOutputPos;
	CButton	m_btnMoveInputPos;
	CButton	m_btnMoveShuttlePP;
	CButton	m_btnMoveShuttleHome;
	CButton	m_btnMoveTSPlace;
	CButton	m_btnMoveTSPick;
	CButton	m_btnMoveTSContact;
	CButton	m_btnMoveHome;
	CButton	m_btnMoveShuttle;
	CButton	m_btnMoveOutput;
	CButton	m_btnMoveInput;
	CButtonST	m_btnCancel;
	CButtonST	m_btnOK;
	int		m_iInputPos;
	int		m_iOutputPos;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgAlignmentCheck)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgAlignmentCheck)
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnMMoveInput();
	afx_msg void OnMMoveOutput();
	afx_msg void OnMMoveShuttle();
	afx_msg void OnMMoveHome();
	afx_msg void OnMTestSitePick();
	afx_msg void OnMTestSitePlace();
	afx_msg void OnMTestSiteContact();
	afx_msg void OnShuttleHome();
	afx_msg void OnShuttlePickplace();
	afx_msg void OnInputMove();
	afx_msg void OnOutputMove();
	afx_msg void OnFArmVacc();
	afx_msg void OnChangeEInputPos();
	afx_msg void OnChangeEOutputPos();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGALIGNMENTCHECK_H__9C3A6918_DC2D_4976_BBC6_475CB8ABEC44__INCLUDED_)
