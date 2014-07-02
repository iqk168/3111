#if !defined(AFX_PAGEDEBUG_H__63D393D2_9740_4561_B595_1EF388B91E98__INCLUDED_)
#define AFX_PAGEDEBUG_H__63D393D2_9740_4561_B595_1EF388B91E98__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PageDebug.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPageDebug dialog

class CPageDebug : public CDialog
{
// Construction
public:
	CPageDebug(CWnd* pParent = NULL);   // standard constructor


	void GetButtonDistance(int &Width, int &Height, int &WDistance, int &HDistance);
	void ReDrawUI();
	void ReDrawUIHandlerModule();

	CToolTipCtrl m_ToolTip;
	void InitTips();

// Dialog Data
	//{{AFX_DATA(CPageDebug)
	enum { IDD = IDD_PAGE_DEBUG };
	CButtonST	m_btnArmLogIC;
	CButtonST	m_btnTrayDefColor;
	CButtonST	m_btnRepeatTrayEnable;
	CButtonST	m_btnManualEnable;
	CButtonST	m_btnPageFunction;
	CButtonST	m_btnTSPIDValve;
	CButtonST	m_btnATCMonitor;
	CButtonST	m_btnCameraSetting;
	CButtonST	m_btnTrayMapUI;
	CButtonST	m_btnHandlerComPortSetting;
	CButtonST	m_btnFilePath;
	CButtonST	m_btnCommunication;
	CButtonST	m_btnBasicSetting;
	CButtonST	m_btnUPH;
	CButtonST	m_btnAlignmentCheck;
	CButtonST	m_btnChipTrayMapInput;
	CButtonST	m_btnMail;
	CButtonST	m_btnSLTFile;
	CButtonST	m_btnTorqueSetup;
	CButtonST	m_btnAlignment;
	CButtonST	m_btnTimerSetting;
	CButtonST	m_btnTimer;
	CButtonST	m_btnSetting;
	CButtonST	m_btnLanguage;
	CButtonST	m_btnGearRation;
	CButtonST	m_btnDebugFunction;
	CButtonST	m_btnChangeFile;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPageDebug)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPageDebug)
	virtual BOOL OnInitDialog();
	afx_msg void OnDebugFunction();
	afx_msg void OnLanguage();
	afx_msg void OnGearRation();
	afx_msg void OnHandlerSetting();	
	afx_msg void OnTimer();
	afx_msg void OnTimerSetting();	
	afx_msg void OnAlignmentSetup();
	afx_msg void OnChangeFile();
	afx_msg void OnTorqueSetup();
	afx_msg void OnTestProgram();
	afx_msg void OnMail();
	afx_msg void OnInputTrayChip();
	afx_msg void OnAlignment();
	afx_msg void OnUph();
	afx_msg void OnBasicSetting();
	afx_msg void OnCommunication();
	afx_msg void OnFilePath();
	afx_msg void OnHandlerComSetting();
	afx_msg void OnTrayUi();
	afx_msg void OnCcdCamera();
	afx_msg void OnHotKey();
	afx_msg void OnPw();
	afx_msg void OnAtcMonitor();
	afx_msg void OnPidControl();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnPageFunction();
	afx_msg void OnManualEnable();
	afx_msg void OnRepeatTrayEnable();
	afx_msg void OnTrayColor();
	afx_msg void OnArmLogic();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PAGEDEBUG_H__63D393D2_9740_4561_B595_1EF388B91E98__INCLUDED_)
