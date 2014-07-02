#if !defined(AFX_DLGSOCKETMATCH_H__F43B09EC_A7B3_4F5F_B82F_43F2F2D34640__INCLUDED_)
#define AFX_DLGSOCKETMATCH_H__F43B09EC_A7B3_4F5F_B82F_43F2F2D34640__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgSocketMatch.h : header file
//

#include "DlgSocketVisionCtrlLive.h"
#include "DlgSocketVisionCtrlSetting.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgSocketMatch dialog

class CDlgSocketMatch : public CDialog
{
// Construction
public:
	CDlgSocketMatch(CWnd* pParent = NULL);   // standard constructor
	
	void InitTabControl();

public:
	/////////////////////////////////////////////////////
	// 宣告 IO 頁面數量(Page)結構區
	struct tagDlgPage
	{
		CDlgSocketVisionCtrlLive		m_DlgSocketLive;
		CDlgSocketVisionCtrlSetting		m_DlgSocketSetting;
		
		TCITEM				m_Page; //儲存參數用
	} DlgPage;

// Dialog Data
	//{{AFX_DATA(CDlgSocketMatch)
	enum { IDD = IDD_DLG_SOCKETVISION };
	CTabCtrl	m_tabSocketCCD;
	CButtonST	m_btnCancel;
	CButtonST	m_btnOK;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgSocketMatch)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
	// Generated message map functions
	//{{AFX_MSG(CDlgSocketMatch)
	virtual void OnCancel();
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeTabSocketvision(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGSOCKETMATCH_H__F43B09EC_A7B3_4F5F_B82F_43F2F2D34640__INCLUDED_)
