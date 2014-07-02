#if !defined(AFX_DLGIOMONTIOR_H__325E8826_6D35_4E09_8FFD_BB94AC0B023D__INCLUDED_)
#define AFX_DLGIOMONTIOR_H__325E8826_6D35_4E09_8FFD_BB94AC0B023D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgIOMontior.h : header file
//

#include "DlgIOMontiorHandler.h"
#include "DlgIOMontiorRemote.h"
#include "DlgIOMontiorATCModule.h"
#include "DlgIOMontiorPTCModule.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgIOMontior dialog

class CDlgIOMontior : public CDialog
{
// Construction
public:
	CDlgIOMontior(bool bOnlyShow = false, CWnd* pParent = NULL);   // standard constructor

	bool m_bOnlyShow;

	void InitTabControl();

	tagOutput	OldOutSet;
	tagRemoteOutput	OldRemoteSet;
	// Back IO setting. Whe User close IO dialog. We need to reset IO setting.

public:
	/////////////////////////////////////////////////////
	// 宣告 IO 頁面數量(Page)結構區
	struct tagDlgPage
	{
		CDlgIOMontiorHandler	m_DlgHandler;
		CDlgIOMontiorRemote		m_DlgRemote;
		CDlgIOMontiorATCModule	m_DlgATCModule;
		CDlgIOMontiorPTCModule	m_DlgPTCModule;
		
		TCITEM				m_Page; //儲存參數用
	} DlgPage;

	
// Dialog Data
	//{{AFX_DATA(CDlgIOMontior)
	enum { IDD = IDD_DLG_IOMONITOR };
	CTabCtrl	m_tabIO;
	CButtonST	m_btnCancel;
	CButtonST	m_btnOK;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgIOMontior)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CDlgIOMontior)
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnTimer(UINT nIDEvent);
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	afx_msg void OnSelchangeTabIo(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGIOMONTIOR_H__325E8826_6D35_4E09_8FFD_BB94AC0B023D__INCLUDED_)
