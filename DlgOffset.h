#if !defined(AFX_DLGOFFSET_H__05A44151_50AA_45F1_A149_A649B9E7E126__INCLUDED_)
#define AFX_DLGOFFSET_H__05A44151_50AA_45F1_A149_A649B9E7E126__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgOffset.h : header file
//

// GroupBox
#include "GroupControl.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgOffset dialog

class CDlgOffset : public CDialog
{
// Construction
public:
	CDlgOffset(CWnd* pParent = NULL);   // standard constructor

	CToolTipCtrl m_ToolTip;

	void InitValue();
	void InitTips();
	
	void ReDrawUI();

	bool m_fChange;

	tagOffset m_Offset;

	bool SaveData();
	bool CheckValue();

public:
	// 1.0Ab
	void InitNoteUI();

// Dialog Data
	//{{AFX_DATA(CDlgOffset)
	enum { IDD = IDD_DLG_OFFSET };
	CStatic				m_wndStaticRotatorPLZ;
	CStatic				m_wndStaticRotatorPKZ;
	CStatic				m_wndStaticRotatorY;
	CStatic				m_wndStaticRotatorX;
	CRichEditCtrl		m_RichNote;
	CGroupControl		m_wndRotatorGrp;
	CButtonST			m_btnOK;
	CButtonST			m_btnCancel;
	double				m_dOffsetInputArmX;
	double				m_dOffsetInputArmY;
	double				m_dOffsetInputArmZ;
	double				m_dOffsetOutputArmX;
	double				m_dOffsetOutputArmY;
	double				m_dOffsetOutputArmZ;
	double				m_dOffsetRotatorArmX;
	double				m_dOffsetRotatorArmY;
	double				m_dOffsetRotatorArmZ;
	double				m_dOffsetSocketArmX;
	double				m_dOffsetSocketArmY;
	double				m_dOffsetSocketArmZ;
	double				m_dOffsetSocketArmZ2;
	double				m_dOffsetRotatorArmZ2;
	double				m_dOffsetInputArmZ2;
	double				m_dOffsetOutputArmZ2;
	double				m_dOffsetShuttleInputX;
	double				m_dOffsetShuttleInputY;
	double				m_dOffsetShuttleInputZ2;
	double				m_dOffsetShuttleOutX;
	double				m_dOffsetShuttleOutY;
	double				m_dOffsetShuttleOutZ;
	double				m_dOffsetTSContact;
	double				m_dOffsetTSPick;
	double				m_dOffsetTSPlace;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgOffset)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgOffset)
	virtual BOOL OnInitDialog();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnChangeOffsetInputArmX();
	afx_msg void OnChangeOffsetInputArmY();
	afx_msg void OnChangeOffsetInputArmZ();
	afx_msg void OnChangeOffsetOutputArmX();
	afx_msg void OnChangeOffsetOutputArmY();
	afx_msg void OnChangeOffsetOutputArmZ();
	afx_msg void OnChangeOffsetSocketArmX();
	afx_msg void OnChangeOffsetSocketArmY();
	afx_msg void OnChangeOffsetSocketArmZ();
	afx_msg void OnChangeOffsetRotatorArmX();
	afx_msg void OnChangeOffsetRotatorArmY();
	afx_msg void OnChangeOffsetRotatorArmZ();
	afx_msg void OnChangeOffsetSocketArmZ2();
	afx_msg void OnChangeOffsetRotatorArmZ2();
	afx_msg void OnChangeOffsetInputArmZ2();
	afx_msg void OnChangeOffsetOutputArmZ2();
	afx_msg void OnChangeOffsetShinArmX();
	afx_msg void OnChangeOffsetShinArmY();
	afx_msg void OnChangeOffsetShoutArmX();
	afx_msg void OnChangeOffsetShoutArmY();
	afx_msg void OnChangeOffsetShinArmZ2();
	afx_msg void OnChangeOffsetShoutArmZ();
	afx_msg void OnSetfocusOffsetInputArmX();
	afx_msg void OnSetfocusOffsetInputArmY();
	afx_msg void OnSetfocusOffsetInputArmZ();
	afx_msg void OnSetfocusOffsetInputArmZ2();
	afx_msg void OnSetfocusOffsetOutputArmX();
	afx_msg void OnSetfocusOffsetOutputArmY();
	afx_msg void OnSetfocusOffsetOutputArmZ();
	afx_msg void OnSetfocusOffsetOutputArmZ2();
	afx_msg void OnSetfocusOffsetRotatorArmX();
	afx_msg void OnSetfocusOffsetRotatorArmY();
	afx_msg void OnSetfocusOffsetRotatorArmZ();
	afx_msg void OnSetfocusOffsetRotatorArmZ2();
	afx_msg void OnSetfocusOffsetShinArmX();
	afx_msg void OnSetfocusOffsetShinArmY();
	afx_msg void OnSetfocusOffsetShinArmZ2();
	afx_msg void OnSetfocusOffsetShoutArmX();
	afx_msg void OnSetfocusOffsetShoutArmY();
	afx_msg void OnSetfocusOffsetShoutArmZ();
	afx_msg void OnSetfocusOffsetSocketArmX();
	afx_msg void OnSetfocusOffsetSocketArmY();
	afx_msg void OnSetfocusOffsetSocketArmZ();
	afx_msg void OnSetfocusOffsetSocketArmZ2();
	afx_msg void OnSetfocusOffsetTsContact();
	afx_msg void OnSetfocusOffsetTsPick();
	afx_msg void OnSetfocusOffsetTsPlace();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGOFFSET_H__05A44151_50AA_45F1_A149_A649B9E7E126__INCLUDED_)
