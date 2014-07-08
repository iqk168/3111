#if !defined(AFX_DLGPIN1MATCH_H__32CC5651_17B1_472B_9FFC_0679889BFF4C__INCLUDED_)
#define AFX_DLGPIN1MATCH_H__32CC5651_17B1_472B_9FFC_0679889BFF4C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// Socket CCD Sensor
#include "DlgPin1VisionLive.h"
#include "DlgPin1VisionSetting.h"

// DlgPin1Match.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgPin1Match dialog

class CDlgPin1Match : public CDialog
{
// Construction
public:
	CDlgPin1Match(CWnd* pParent = NULL);   // standard constructor

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
		CDlgPin1VisionSetting m_DlgPin1Match;
		CDlgPin1VisionLive	m_DlgLive;
		
		TCITEM				m_Page; //儲存參數用
	} DlgPage;

// Dialog Data
	//{{AFX_DATA(CDlgPin1Match)
	enum { IDD = IDD_DLG_PIN1VISION };
	CTabCtrl	m_tabSocketVision;
	CButtonST	m_btnCancel;
	CButtonST	m_btnOK;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgPin1Match)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CDlgPin1Match)
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

#endif // !defined(AFX_DLGPIN1MATCH_H__32CC5651_17B1_472B_9FFC_0679889BFF4C__INCLUDED_)
