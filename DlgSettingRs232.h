#if !defined(AFX_DLGSETTINGRS232_H__8FE47A7B_3075_4CB7_8762_FD31893E2A03__INCLUDED_)
#define AFX_DLGSETTINGRS232_H__8FE47A7B_3075_4CB7_8762_FD31893E2A03__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgSettingRs232.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgSettingRs232 dialog

class CDlgSettingRs232 : public CDialog
{
// Construction
public:
	CDlgSettingRs232(CWnd* pParent = NULL);   // standard constructor

	CString m_csRs232File;
	void SetFile(CString csfile);

	//
	void LoadFile();
	void InitValue();
	bool SaveData();

	tagIfRs232Setting	m_IfRs232;

	//
	bool SaveRS232Data();
	bool GetDataFromUI(tagIfRs232Setting &UIData);
	void SaveDataToFile(tagIfRs232Setting FileData);

	//
	CString m_csExtendErrMsg;

public:
	void InitIfNote();

// Dialog Data
	//{{AFX_DATA(CDlgSettingRs232)
	enum { IDD = IDD_SETTING_RS232 };
	CStatic	m_wndIfNote;
	CEdit	m_wndSendStartDelay;
	CEdit	m_wndRs232Timeout;
	CEdit	m_wndRs232Start;
	CEdit	m_wndRs232Ready;
	CEdit	m_wndRs232Go;
	CEdit	m_wndRs232Bin;
	CEdit	m_wndRs232Tail;
	CEdit	m_wndRs232Header;
	CStatic	m_wndFile;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgSettingRs232)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgSettingRs232)
	virtual BOOL OnInitDialog();
	afx_msg void OnNote();
	afx_msg void OnFile();
	afx_msg void OnEStatic();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGSETTINGRS232_H__8FE47A7B_3075_4CB7_8762_FD31893E2A03__INCLUDED_)
