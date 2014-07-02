#if !defined(AFX_DLGTRAYREPEATSTATUS_H__AFD8D4EC_BA60_4284_8845_FD6CEBAC7DE7__INCLUDED_)
#define AFX_DLGTRAYREPEATSTATUS_H__AFD8D4EC_BA60_4284_8845_FD6CEBAC7DE7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgTrayRepeatStatus.h : header file
//

#include "ViewRepeatTrayMotor.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgTrayRepeatStatus dialog

class CDlgTrayRepeatStatus : public CDialog
{
// Construction
public:
	CDlgTrayRepeatStatus(CWnd* pParent = NULL);   // standard constructor

	void InitTrayStatus();
	void UpdataTrayStatus();

public:
	// Tray
	CViewRepeatTrayMotor *pViewTray1;		// Tray 1
	CViewRepeatTrayMotor *pViewTray2;		// Tray 2 


// Dialog Data
	//{{AFX_DATA(CDlgTrayRepeatStatus)
	enum { IDD = IDD_DLG_TRAY_REPEAT_STATUS };
	CStatic	m_wndTray2;
	CStatic	m_wndTray1;
	CButtonST	m_btnOK;
	CButtonST	m_btnCancel;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgTrayRepeatStatus)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgTrayRepeatStatus)
	afx_msg void OnTimer(UINT nIDEvent);
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGTRAYREPEATSTATUS_H__AFD8D4EC_BA60_4284_8845_FD6CEBAC7DE7__INCLUDED_)
