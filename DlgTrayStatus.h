#if !defined(AFX_DLGTRAYSTATUS_H__5E9D600D_ECA8_44C5_A03A_9EC6DB127596__INCLUDED_)
#define AFX_DLGTRAYSTATUS_H__5E9D600D_ECA8_44C5_A03A_9EC6DB127596__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgTrayStatus.h : header file
//

// Draw CTrayFile
#include "ViewTrayMotor.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgTrayStatus dialog

class CDlgTrayStatus : public CDialog
{
// Construction
public:
	CDlgTrayStatus(CWnd* pParent = NULL);   // standard constructor

	CToolTipCtrl m_ToolTip;

	void InitValue();
	void InitTips();

	// Tray
	CViewTrayMotor *pViewTrayOutput1;		// Output 1
	CViewTrayMotor *pViewTrayInput1;		// Input Tray 

	void InitTrayStatus();
	void ChangeTrayStatus();

	void UpdateStatus();

// Dialog Data
	//{{AFX_DATA(CDlgTrayStatus)
	enum { IDD = IDD_DLG_TRAY_STATUS };
	CStatic	m_wndOutputTray1;
	CStatic	m_wndInputTray1;
	CButtonST	m_btnOK;
	CButtonST	m_btnCancel;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgTrayStatus)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgTrayStatus)
	virtual void OnOK();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGTRAYSTATUS_H__5E9D600D_ECA8_44C5_A03A_9EC6DB127596__INCLUDED_)
