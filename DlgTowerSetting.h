#if !defined(AFX_DLGTOWERSETTING_H__C2B35738_A663_4486_B654_67A9EEBA1098__INCLUDED_)
#define AFX_DLGTOWERSETTING_H__C2B35738_A663_4486_B654_67A9EEBA1098__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgTowerSetting.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgTowerSetting dialog

class CDlgTowerSetting : public CDialog
{
// Construction
public:
	CDlgTowerSetting(CWnd* pParent = NULL);   // standard constructor

	CToolTipCtrl m_ToolTip;
	void InitTips();
	bool SaveData();
	void InitValue();

	//
	void InitUI();
	void InitBlink();

	//
	bool CheckValue();

	tagTowerSetupSetting m_TowerSetupSetting;

public:
	void NextChoise(int &iChoise);
	void SetCtrlColor(CButtonST &ctrl, COLORREF cc);
	void SetChoiseTitle(CButtonST &ctrl, int iChoise);

// Dialog Data
	//{{AFX_DATA(CDlgTowerSetting)
	enum { IDD = IDD_DLG_TOWER_SETTING };
		// NOTE: the ClassWizard will add data members here
	CButtonST	m_btnReadyYellow;
	CButtonST	m_btnReadyRed;
	CButtonST	m_btnReadyGreen;
	CButtonST	m_btnOverrideStopYellow;
	CButtonST	m_btnOverrideStopRed;
	CButtonST	m_btnOverrideStopGreen;
	CButtonST	m_btnOverrideYellow;
	CButtonST	m_btnOverrideRed;
	CButtonST	m_btnOverrideGreen;
	CButtonST	m_btnOneCycleStopYellow;
	CButtonST	m_btnOneCycleStopRed;
	CButtonST	m_btnOneCycleStopGreen;
	CButtonST	m_btnOneCycleYellow;
	CButtonST	m_btnOneCycleRed;
	CButtonST	m_btnOneCycleGreen;
	CButtonST	m_btnManualStopYellow;
	CButtonST	m_btnManualStopRed;
	CButtonST	m_btnManualStopGreen;
	CButtonST	m_btnManualYellow;
	CButtonST	m_btnManualRed;
	CButtonST	m_btnManualGreen;
	CButtonST	m_btnInitialYellow;
	CButtonST	m_btnInitialRed;
	CButtonST	m_btnInitialGreen;
	CButtonST	m_btnCycleStopYellow;
	CButtonST	m_btnCycleStopRed;
	CButtonST	m_btnCycleStopGreen;
	CButtonST	m_btnCycleYellow;
	CButtonST	m_btnCycleRed;
	CButtonST	m_btnCycleGreen;
	CButtonST	m_btnUninitialGreen;
	CButtonST	m_btnUninitialYellow;
	CButtonST	m_btnUninitialRed;

	//
	CEdit				m_wndBlinkTime;
	CComboBox			m_coBlinkList;
	CColorFontStatic	m_wndTowerGreen;
	CColorFontStatic	m_wndTowerYellow;
	CColorFontStatic	m_wndTowerRed;
	CButtonST			m_btnCancel;
	CButtonST			m_btnOK;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgTowerSetting)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgTowerSetting)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnCSetBlink();
	afx_msg void OnSelchangeCBlinkList();
	afx_msg void OnCUninitialRed();
	afx_msg void OnCUninitialYellow();
	afx_msg void OnCUninitialGreen();
	afx_msg void OnCInitialRed();
	afx_msg void OnCInitialYellow();
	afx_msg void OnCInitialGreen();
	afx_msg void OnCReadyRed();
	afx_msg void OnCReadyYellow();
	afx_msg void OnCReadyGreen();
	afx_msg void OnCCycleRed();
	afx_msg void OnCCycleYellow();
	afx_msg void OnCCycleGreen();
	afx_msg void OnCCycleStopRed();
	afx_msg void OnCCycleStopYellow();
	afx_msg void OnCCycleStopGreen();
	afx_msg void OnCOneCycleRed();
	afx_msg void OnCOneCycleYellow();
	afx_msg void OnCOneCycleGreen();
	afx_msg void OnCOneCycleStopRed();
	afx_msg void OnCOneCycleStopYellow();
	afx_msg void OnCOneCycleStopGreen();
	afx_msg void OnCOverrideRed();
	afx_msg void OnCOverrideYellow();
	afx_msg void OnCOverrideGreen();
	afx_msg void OnCOverrideStopRed();
	afx_msg void OnCOverrideStopYellow();
	afx_msg void OnCOverrideStopGreen();
	afx_msg void OnCManualRed();
	afx_msg void OnCManualYellow();
	afx_msg void OnCManualGreen();
	afx_msg void OnCManualStopRed();
	afx_msg void OnCManualStopYellow();
	afx_msg void OnCManualStopGreen();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGTOWERSETTING_H__C2B35738_A663_4486_B654_67A9EEBA1098__INCLUDED_)
