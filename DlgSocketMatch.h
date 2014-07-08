#if !defined(AFX_DLGSOCKETMATCH_H__32CC5651_17B1_472B_9FFC_0679889BFF4C__INCLUDED_)
#define AFX_DLGSOCKETMATCH_H__32CC5651_17B1_472B_9FFC_0679889BFF4C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// Socket CCD Sensor
#include "DlgSocketVisionLive.h"
#include "DlgSocketVisionSetting.h"

// DlgSocketMatch.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgSocketMatch dialog

class CDlgSocketMatch : public CDialog
{
// Construction
public:
	CDlgSocketMatch(CWnd* pParent = NULL);   // standard constructor

	void InitTabControl();
	void InitValue();

	//
	void ChangeTab();

	//
	void ExitPage();

public:
	
	/////////////////////////////////////////////////////
	// 宣告 CCD Socket 頁面數量(Page)結構區
	struct tagDlgPage
	{
		CDlgSocketVisionSetting m_DlgSocketMatch;
		CDlgSocketVisionLive	m_DlgLive;
		
		TCITEM				m_Page; //儲存參數用
	} DlgPage;

// Dialog Data
	//{{AFX_DATA(CDlgSocketMatch)
	enum { IDD = IDD_DLG_SOCKETVISION };
	CTabCtrl	m_tabSocketVision;
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
	virtual void OnOK();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnSelchangeTabSocketvision(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGSOCKETMATCH_H__32CC5651_17B1_472B_9FFC_0679889BFF4C__INCLUDED_)
