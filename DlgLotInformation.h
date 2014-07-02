#if !defined(AFX_DLGLOTINFORMATION_H__EEF42F9A_3303_4F37_ABD8_354178C91356__INCLUDED_)
#define AFX_DLGLOTINFORMATION_H__EEF42F9A_3303_4F37_ABD8_354178C91356__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgLotInformation.h : header file
//


#include "ColorBtn.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgLotInformation dialog

class CDlgLotInformation : public CDialog
{
// Construction
public:
	CDlgLotInformation(CWnd* pParent = NULL);   // standard constructor
	
	CToolTipCtrl m_ToolTip;
	void InitTips();

	void InitUI();

public:

	// 1.0Af
	void InitTrayFileDropList();
	void InitCopyLastAll();

	void CopyLastAll();
	void CopyLastCtrl();

// Dialog Data
	//{{AFX_DATA(CDlgLotInformation)
	enum { IDD = IDD_LOT_INFO };
	CComboBox	m_wndTrayFileDropList;
	CEdit	m_wndLotTrayFile;
	CEdit	m_wndLotProgramerID;
	CEdit	m_wndLotOperator;
	CEdit	m_wndLotNo;
	CEdit	m_wndLotMachineID;
	CEdit	m_wndLotDeviceID;
	CButtonST	m_btnCancel;
	CButtonST	m_btnOK;
	CButtonST	m_btnCopLotNo;
	CButtonST	m_btnCopyMachineID;
	CButtonST	m_btnCopyOperator;
	CButtonST	m_btnCopyDeviceID;
	CButtonST	m_btnCopyProgramID;
	CColorBtn	m_btnReCycleTest;
	CColorBtn	m_btnNormal;
	int			m_iTestItem;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgLotInformation)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	void UpdataValue();
	bool CheckValue();	// 如果沒輸入完,就不准 建立成功

	// Generated message map functions
	//{{AFX_MSG(CDlgLotInformation)
	afx_msg void OnClose();
	afx_msg void OnDestroy();
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();

	// Copy Last
	afx_msg void OnCopyLotNo();
	afx_msg void OnCopyMachineNo();
	afx_msg void OnCopyOperatorID();
	afx_msg void OnCopyDeviceID();
	afx_msg void OnCopyProgramID();
	//
	afx_msg void OnCopyLastAll();
	//
	afx_msg void OnNormalTest();
	afx_msg void OnRcTest();

	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGLOTINFORMATION_H__EEF42F9A_3303_4F37_ABD8_354178C91356__INCLUDED_)
