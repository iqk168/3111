#if !defined(AFX_DLGCOMMUNICATIONINFO_H__B31A47CE_F0A6_4EB8_A3BB_C2D16712A361__INCLUDED_)
#define AFX_DLGCOMMUNICATIONINFO_H__B31A47CE_F0A6_4EB8_A3BB_C2D16712A361__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgCommunicationInfo.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgCommunicationInfo dialog

class CDlgCommunicationInfo : public CDialog
{
// Construction
public:
	CDlgCommunicationInfo(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgCommunicationInfo)
	enum { IDD = IDD_DLG_COMM_INFO };
	CButtonST	m_btnClear;
	CButtonST	m_btnOK;
	CButtonST	m_btnCancel;
	CListBox	m_listInfo;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgCommunicationInfo)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgCommunicationInfo)
	virtual BOOL OnInitDialog();
	afx_msg void OnClear();
	afx_msg LRESULT OnCommunicationInfo(WPARAM p, LPARAM l);

	virtual void OnOK();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGCOMMUNICATIONINFO_H__B31A47CE_F0A6_4EB8_A3BB_C2D16712A361__INCLUDED_)
