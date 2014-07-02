#if !defined(AFX_DLGTRAYMAPUI_H__A8B3E672_65ED_4B98_B29C_A9EE8E8A906F__INCLUDED_)
#define AFX_DLGTRAYMAPUI_H__A8B3E672_65ED_4B98_B29C_A9EE8E8A906F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgTrayMapUI.h : header file
//

#include "ColorPickerCB.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgTrayMapUI dialog

class CDlgTrayMapUI : public CDialog
{
// Construction
public:
	CDlgTrayMapUI(CWnd* pParent = NULL);   // standard constructor

	void InitValue();
	void SaveData();
	void InitColorCombox();

// Dialog Data
	//{{AFX_DATA(CDlgTrayMapUI)
	enum { IDD = IDD_DLG_BASIC_TRAY_UI };
	CColorPickerCB	m_wndTraySpecColorBk;
	CButtonST	m_btnOK;
	CButtonST	m_btnCancel;
	double	m_dTraySpecLeftSide;
	double	m_dTraySpecTopSide;
	double	m_dTraySpecICSide;
	double	m_dTraySpecTextUpSide;
	double  m_dTraySpecTextLeftSide;
	CComboBox	m_iTraySpecTextBreak;
	CComboBox	m_iTraySpecTextSize;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgTrayMapUI)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgTrayMapUI)
	virtual void OnOK();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGTRAYMAPUI_H__A8B3E672_65ED_4B98_B29C_A9EE8E8A906F__INCLUDED_)
