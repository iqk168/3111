#if !defined(AFX_DLGBASICSETTING_H__51131A0F_168C_4B54_B97D_401197661DD0__INCLUDED_)
#define AFX_DLGBASICSETTING_H__51131A0F_168C_4B54_B97D_401197661DD0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgBasicSetting.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgBasicSetting dialog

class CDlgBasicSetting : public CDialog
{
// Construction
public:
	CDlgBasicSetting(CWnd* pParent = NULL);   // standard constructor

	CToolTipCtrl m_ToolTip;

	void InitValue();
	void InitTips();

	//
	void InitColor();
	void SaveColorData();
	void PreSetColor();

	bool ChekcValue();
	void SaveData();

	bool m_fChange;

// Dialog Data
	//{{AFX_DATA(CDlgBasicSetting)
	enum { IDD = IDD_DLG_BASIC_SETTING };
	CEdit	m_wndTorqueForceRation;
	CEdit	m_wndTestSiteSocketStandyPosition;
	CEdit	m_wndTestSitePosition;
	CColorFontStatic	m_wndOutputColor;
	CEdit		m_wndOutputColorB;
	CEdit		m_wndOutputColorG;
	CEdit		m_wndOutputColorR;
	CButtonST	m_btnOK;
	CButtonST	m_btnCancel;
	int			m_iSpeedLowLimit;
	int			m_iSpeedHighLimit;
	double		m_dOffsetHighLimit;
	double		m_dOffsetLowLimit;
	double		m_dTimerHighLimit;
	double		m_dTimerLowLimit;
	int			m_iInitialPreMoveDistance;
	double		m_dTestSiteStandbyPosition;
	double		m_dTestSiteSocketStandyPos;
	double	m_dStandyX;
	double	m_dStandyY;
	double	m_dTimeoutHighLimit;
	double	m_dTimeoutLowLimit;
	double	m_dBuzzerAutoClose;
	double	m_dTorqueForceRation;
	int		m_iRepeatTrayMaxValue;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgBasicSetting)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgBasicSetting)
	virtual void OnCancel();
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnChangeSpeedLowLimit();
	afx_msg void OnChangeSpeedHighLimit();
	afx_msg void OnChangeOffsetLowLimit();
	afx_msg void OnChangeOffsetHighLimit();
	afx_msg void OnChangeTimerLowLimit();
	afx_msg void OnChangeTimerHighLimit();
	afx_msg void OnChangeInitialPreDistance();
	afx_msg void OnEOutputSet();
	afx_msg void OnEOutputSave();
	afx_msg void OnChangeEOutputR();
	afx_msg void OnChangeEOutputG();
	afx_msg void OnChangeEOutputB();
	afx_msg void OnEPositionStatic();
	afx_msg void OnChangeTsStandyPosition();
	afx_msg void OnEPositionStatic2();
	afx_msg void OnStaticTorqueRation();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGBASICSETTING_H__51131A0F_168C_4B54_B97D_401197661DD0__INCLUDED_)
