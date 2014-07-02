#if !defined(AFX_PAGESETUP_H__D164DAB2_2EE0_4E00_B23A_F3CA3D339286__INCLUDED_)
#define AFX_PAGESETUP_H__D164DAB2_2EE0_4E00_B23A_F3CA3D339286__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PageSetup.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPageSetup dialog

class CPageSetup : public CDialog
{
// Construction
public:
	CPageSetup(CWnd* pParent = NULL);   // standard constructor

	void GetButtonDistance(int &Width, int &Height, int &WDistance, int &HDistance);
	void ReDrawUI();
	void ReDrawUIOptionFunction();
	void ReDrawUITrayModuleFunction();

	CToolTipCtrl m_ToolTip;
	void InitTips();
	//
	bool CheckRemoteControl(); // OK return true

// Dialog Data
	//{{AFX_DATA(CPageSetup)
	enum { IDD = IDD_PAGE_SETUP };
	CButtonST	m_btnTowerSetting;
	CButtonST	m_btnRepeatTray;
	CButtonST	m_btnInOutTray;
	CButtonST	m_btnOutputTrayMap;
	CButtonST	m_btnTemperature;
	CButtonST	m_btnATCModule;
	CButtonST	m_btnRemoteInput;
	CButtonST	m_btnInterFaceSetting;
	CButtonST	m_btnATCCalibration;
	CButtonST	m_btnCCDSetup;
	CButtonST	m_btnSocketCCDSetup;
	CButtonST	m_btnCatoregy;
	CButtonST	m_btnRemoteControl;
	CButtonST	m_btnExtendFunction;
	CButtonST	m_btnAutoRetry;
	CButtonST	m_btnInputTrayMap;
	CButtonST	m_btnTrayFile2;
	CButtonST	m_btnInterfaceTesting;
	CButtonST	m_btnYieldCTRL;
	CButtonST	m_btnSpeed;
	CButtonST	m_btnTimer;
	CButtonST	m_btnOffset;
	CButtonST	m_btnDeviceSetup;
	CButtonST	m_btnAlignment;
	CButtonST	m_btnEvent;
	CButtonST	m_btnIOMonitor;
	CButtonST	m_btnSiteSetting;
	//}}AFX_DATA
	

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPageSetup)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPageSetup)
	virtual BOOL OnInitDialog();
	afx_msg void OnIoMontior();
	afx_msg void OnEventLog();
	afx_msg void OnAlignmentSetup();
	afx_msg void OnDeviceSetup();
	afx_msg void OnOffset();
	afx_msg void OnSpeed();
	afx_msg void OnTimer();
	afx_msg void OnYieldCtrl();
	afx_msg void OnInterfaceTesting();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnSiteSeeing();
	afx_msg void OnInputTray();
	afx_msg void OnAutoRetry();
	afx_msg void OnChangeFile3();
	afx_msg void OnExtendFunction();
	afx_msg void OnRemoteControl();
	afx_msg void OnCatoregy();
	afx_msg void OnCcdSocket();
	afx_msg void OnCcdSetup();
	afx_msg void OnAtcCalibration();
	afx_msg void OnInterfaceSetting();
	afx_msg void OnRemoteInput();
	afx_msg void OnAtcModule();
	afx_msg void OnTemperature();
	afx_msg void OnOutputTray();
	afx_msg void OnInOutTray();
	afx_msg void OnRepeatTray();
	afx_msg void OnTowerSetting();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PAGESETUP_H__D164DAB2_2EE0_4E00_B23A_F3CA3D339286__INCLUDED_)
