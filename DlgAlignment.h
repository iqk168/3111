#if !defined(AFX_DLGALIGNMENT_H__3763F112_BD40_48F5_8F72_E88D667F1534__INCLUDED_)
#define AFX_DLGALIGNMENT_H__3763F112_BD40_48F5_8F72_E88D667F1534__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgAlignment.h : header file
//

// GroupBox
#include "GroupControl.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgAlignment dialog

class CDlgAlignment : public CDialog
{
// Construction
public:
	CDlgAlignment(bool key = false, CWnd* pParent = NULL);   // standard constructor

	//
	bool m_key;	// 如果是 Debug Page 進入, 那麼就可以用 Key 的

	CToolTipCtrl m_ToolTip;

	void InitValue();
	void InitTips();
	void InitMotor();
	
	void GetMotorPosition();
	void CheckSuperUser();

	void ReDrawUI();
	void ReDrawUIForKeyIn();

	bool m_fChange;

	tagAlignment m_Align;

	void SaveData();
	void GetValueFromUI();

	// 
	void InitLed();
	void InitTimer();
	void IOQuery();
	
public:
	bool m_bAlignmentAlive;
	long m_lAlignmentPosition;
	long m_lAlignmentGoPosition;
	static UINT TestSiteMoveThread(LPVOID p);
	//

// Dialog Data
	//{{AFX_DATA(CDlgAlignment)
	enum { IDD = IDD_DLG_ALIGNMENT };
	CLed	m_ledShuttlePLmt;
	CLed	m_ledShuttleNLmt;
	CLed	m_ledShuttle;
	CGroupControl		m_wndRotatorGrp;
	CButtonST			m_btnOK;
	CButtonST			m_btnCancel;
	int					m_iAlignmentInputArmX;
	int					m_iAlignmentInputArmY;
	int					m_iAlignmentInputArmZ;
	int					m_iAlignmentOutputArmX;
	int					m_iAlignmentOutputArmY;
	int					m_iAlignmentOutputArmZ;
	int					m_iAlignmentRotatorArmX;
	int					m_iAlignmentRotatorArmY;
	int					m_iAlignmentRotatorArmZ;
	int					m_iAlignmentSocketArmX;
	int					m_iAlignmentSocketArmY;
	int					m_iAlignmentSocketArmZ;
	int		m_iAlignmentShuttleArmX;
	int		m_iAlignmentShuttleArmY;
	int		m_iAlignmentShuttleArmZ;
	int		m_iAlignmentTSPick;
	int		m_iAlignmentTSContact;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgAlignment)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgAlignment)
	virtual void OnOK();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnAlignmentInputRead();
	afx_msg void OnAlignmentOutputRead();
	afx_msg void OnAlignmentSocketRead();
	afx_msg void OnAlignmentRotatorRead();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnChangeAlignmentInputArmX();
	afx_msg void OnChangeAlignmentInputArmY();
	afx_msg void OnChangeAlignmentInputArmZ();
	afx_msg void OnChangeAlignmentOutputArmX();
	afx_msg void OnChangeAlignmentOutputArmY();
	afx_msg void OnChangeAlignmentOutputArmZ();
	afx_msg void OnChangeAlignmentSocketArmX();
	afx_msg void OnChangeAlignmentSocketArmY();
	afx_msg void OnChangeAlignmentSocketArmZ();
	afx_msg void OnChangeAlignmentRotatorArmX();
	afx_msg void OnChangeAlignmentRotatorArmY();
	afx_msg void OnChangeAlignmentRotatorArmZ();
	afx_msg void OnAlignmentShuttleRead();
	afx_msg void OnAlignmentTsShRead();
	afx_msg void OnAlignmentTsCoRead();
	afx_msg void OnChangeAlignmentShuttleArmX();
	afx_msg void OnChangeAlignmentShuttleArmY();
	afx_msg void OnChangeAlignmentShuttleArmZ();
	afx_msg void OnChangeAlignmentTsPick();
	afx_msg void OnChangeAlignmentTsCont();
	afx_msg void OnLedShuttle();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGALIGNMENT_H__3763F112_BD40_48F5_8F72_E88D667F1534__INCLUDED_)
