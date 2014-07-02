#if !defined(AFX_DLGREPEATTRAY_H__6B058DC4_D26A_4794_A3DA_D1577AE479A9__INCLUDED_)
#define AFX_DLGREPEATTRAY_H__6B058DC4_D26A_4794_A3DA_D1577AE479A9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgRepeatTray.h : header file
//

#include "ColorBtn.h"

// Page
#include "DlgRepeatTrayInOutCtrl.h"
#include "DlgRepeatTrayBinCtrl.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgRepeatTray dialog

class CDlgRepeatTray : public CDialog
{
// Construction
public:
	CDlgRepeatTray(CWnd* pParent = NULL);   // standard constructor

	//
	CToolTipCtrl m_ToolTip;
	void InitValue();
	void SaveData();
	void InitTips();

	//
	void ButtonPress();
	void ChangeRepeatTrayMode(int iMode);

	//
	void GetButtonDistance(int &Width, int &Height, int &WDistance, int &HDistance);
	void ReDrawRepeatFun();
	void ReDrawUI();

	//
	tagRepeatTrayCtrl m_RepeatTrayCtrl;

	//
	void LockUI();

public:
	void InitPage();

public:
	/////////////////////////////////////////////////////
	// 宣告 IF 頁面數量(Page)結構區
	struct tagReDlgPage
	{
		CDlgRepeatTrayInOutCtrl				m_DlgInOutCtrl;
		CDlgRepeatTrayBinCtrl				m_DlgBinCtrl;
		TCITEM								m_Page; //儲存參數用
	} DlgRePage;

	//
	bool m_bMappingOn;
	void TurnOnMapping();

// Dialog Data
	//{{AFX_DATA(CDlgRepeatTray)
	enum { IDD = IDD_DLG_REPEAT_TRAY };
	CButtonST	m_btnRepeatMapping;
	CColorBtn	m_btnRepeatTrayBinningCtrl;
	CColorBtn	m_btnRepeatTrayInOutCtrl;
	CColorBtn	m_btnRepeatTrayNone;
	CButtonST	m_btnCancel;
	CButtonST	m_btnOK;
	int		m_iRepeatTray;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgRepeatTray)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgRepeatTray)
	virtual void OnOK();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnRRepeatTrayModeNone();
	afx_msg void OnRRepeatTrayModeInOutCtrl();
	afx_msg void OnRRepeatTrayModeBinning();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnMapping();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGREPEATTRAY_H__6B058DC4_D26A_4794_A3DA_D1577AE479A9__INCLUDED_)
