#if !defined(AFX_DLGTRAYMAPREPEAT_H__C962AF31_F190_4DF9_9FFF_686B25BEC0DA__INCLUDED_)
#define AFX_DLGTRAYMAPREPEAT_H__C962AF31_F190_4DF9_9FFF_686B25BEC0DA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgTrayMapRepeat.h : header file
//

#include "ViewTrayMap.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgTrayMapRepeat dialog

class CDlgTrayMapRepeat : public CDialog
{
// Construction
public:
	CDlgTrayMapRepeat(CWnd* pParent = NULL);   // standard constructor

	CToolTipCtrl m_ToolTip;

	void InitValue();
	void InitTips();
	void InitTrayMap();
	//
	void UpdateView();

	//
	CViewTrayMap *pViewTrayOutput1; // Tray Output 1 ( Tray1 )
	CViewTrayMap *pViewTrayOutput2; // Tray Output 2 ( Tray2 )

// Dialog Data
	//{{AFX_DATA(CDlgTrayMapRepeat)
	enum { IDD = IDD_DLG_TRAYMAP_REPEAT };
	CStatic	m_wndTray2;
	CStatic	m_wndTray1;
	CStatic	m_wndOutputTray2;
	CStatic	m_wndOutputTray1;
	CButtonST	m_btnCancel;
	CButtonST	m_btnOK;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgTrayMapRepeat)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgTrayMapRepeat)
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT nIDEvent);
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnETray1Up();
	afx_msg void OnETray1Down();
	afx_msg void OnETray2Up();
	afx_msg void OnETray2Down();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGTRAYMAPREPEAT_H__C962AF31_F190_4DF9_9FFF_686B25BEC0DA__INCLUDED_)
