#if !defined(AFX_DLGREMOTECOMMUNICATION_H__7F82E9D7_A4C9_4404_BD46_C7420FBE82F7__INCLUDED_)
#define AFX_DLGREMOTECOMMUNICATION_H__7F82E9D7_A4C9_4404_BD46_C7420FBE82F7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgRemoteCommunication.h : header file
//

#include "DlgRemoteCommMonitor.h"
#include "DlgRemoteCommMsg.h"
#include "DlgRemoteCommMsgLot.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgRemoteCommunication dialog

class CDlgRemoteCommunication : public CDialog
{
// Construction
public:
	CDlgRemoteCommunication(CWnd* pParent = NULL);   // standard constructor

	void InitTabControl();

public:
	/////////////////////////////////////////////////////
	// 宣告 Remote Communication 頁面數量(Page)結構區
	struct tagDlgPage
	{
		CDlgRemoteCommMonitor	m_DlgRemoteMonitor;
		CDlgRemoteCommMsg		m_DlgRemoteMsg;
		CDlgRemoteCommMsgLot	m_DlgRemoteMsgLot;
		
		TCITEM				m_Page; //儲存參數用
	} DlgPage;

// Dialog Data
	//{{AFX_DATA(CDlgRemoteCommunication)
	enum { IDD = IDD_DLG_REMOTE_COMMUNICATION };
	CTabCtrl	m_tabRemote;
	CButtonST	m_btnOK;
	CButtonST	m_btnCancel;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgRemoteCommunication)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CDlgRemoteCommunication)
	virtual void OnOK();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeTabRemote(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg LRESULT OnRemoteRecvRaw(WPARAM p, LPARAM l);
	afx_msg LRESULT OnRemoteRecv(WPARAM p, LPARAM l);
	afx_msg LRESULT OnRemoteSend(WPARAM p, LPARAM l);

	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGREMOTECOMMUNICATION_H__7F82E9D7_A4C9_4404_BD46_C7420FBE82F7__INCLUDED_)
