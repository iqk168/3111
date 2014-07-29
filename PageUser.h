#if !defined(AFX_PAGEUSER_H__66DDDFDF_0FE8_41A0_95FC_78369DBEB23F__INCLUDED_)
#define AFX_PAGEUSER_H__66DDDFDF_0FE8_41A0_95FC_78369DBEB23F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PageUser.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPageUser dialog

class CPageUser : public CDialog
{
// Construction
public:
	CPageUser(CWnd* pParent = NULL);   // standard constructor

	void ResetUserPageAutoSkip();
	void ReDrawUI();
	void ReDrawAutoSkip();
	void ReDrawTestSiteVaccOff();
	void GetButtonDistance(int &Width, int &Height, int &WDistance, int &HDistance);

	//
	CToolTipCtrl m_ToolTip;
	void InitTips();

	//
	void InitICON();

// Dialog Data
	//{{AFX_DATA(CPageUser)
	enum { IDD = IDD_PAGE_USER };
	CButtonST	m_btnSLTProtocol;
	CButtonST	m_btnArmLogICList;
	CButtonST	m_btnArmLogImage;
	CButtonST	m_btnTrayDefColor;
	CButtonST	m_btnRepeatTrayStatus;
	CButtonST	m_btnTestResult;
	CButtonST	m_btnTestSiteVacc;
	CButtonST	m_btnTrayMapReport;
	CButtonST	m_btnInterfaceTesting;
	CButtonST	m_btnSummaryReport;
	CButtonST	m_btnManualContact;
	CButtonST	m_btnDeviceSetup;
	CButtonST	m_btnSiteSetting;
	CButtonST	m_btnVisualButton;
	CButtonST	m_btnLotInformation;
	CButtonST	m_btnAutoSkip;
	CButtonST	m_btnYieldCTRL;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPageUser)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPageUser)
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnYieldCtrl();
	afx_msg void OnTrayAutoSkip();
	afx_msg void OnLotInformation();
	afx_msg void OnVisualPanel();
	afx_msg void OnSiteSetting();
	afx_msg void OnDeviceSetup();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnSummaryReport();
	afx_msg void OnManualContact();
	afx_msg void OnInterfaceTesting();
	afx_msg void OnTrayMapReport();
	afx_msg void OnTsVacc();
	afx_msg void OnTestResult();
	afx_msg void OnRepeatTrayStatus();
	afx_msg void OnTrayDefColor();
	afx_msg void OnArmLogImage();
	afx_msg void OnArmLogIcList();
	afx_msg void OnSltProtocol();
	afx_msg void OnDebug();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PAGEUSER_H__66DDDFDF_0FE8_41A0_95FC_78369DBEB23F__INCLUDED_)
