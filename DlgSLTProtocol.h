#if !defined(AFX_DLGSLTPROTOCOL_H__EBEF53B8_7350_4418_9DA0_ACE8757DEED4__INCLUDED_)
#define AFX_DLGSLTPROTOCOL_H__EBEF53B8_7350_4418_9DA0_ACE8757DEED4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgSLTProtocol.h : header file
//

#include "DlgSLTProtocolSetting.h"
#include "DlgSLTProtocolMonitor.h"
#include "DlgSLTProtocolHelp.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgSLTProtocol dialog

class CDlgSLTProtocol : public CDialog
{
// Construction
public:
	CDlgSLTProtocol(CWnd* pParent = NULL);   // standard constructor

	/////////////////////////////////////////////////////
	// 宣告 Remote Communication 頁面數量(Page)結構區
	struct tagDlgPage
	{
		CDlgSLTProtocolSetting	m_DlgSLTProtocolSetting;
		CDlgSLTProtocolMonitor	m_DlgSLTProtocolMonitor;
		CDlgSLTProtocolHelp		m_DlgSLTProtocolHelp;
		
		TCITEM				m_Page; //儲存參數用
	} DlgPage;

	void InitSLTPage();

// Dialog Data
	//{{AFX_DATA(CDlgSLTProtocol)
	enum { IDD = IDD_DLG_SLT_PROTOCOL };
	CTabCtrl	m_tabSLT;
	CButtonST	m_btnCancel;
	CButtonST	m_btnOK;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgSLTProtocol)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CDlgSLTProtocol)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnSelchangeTabSlt(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg LRESULT OnSLTRecvRaw(WPARAM p, LPARAM l);

	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGSLTPROTOCOL_H__EBEF53B8_7350_4418_9DA0_ACE8757DEED4__INCLUDED_)
