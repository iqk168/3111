#if !defined(AFX_DLGSETTINGTCP_H__87995BBE_366B_4EE7_AB99_02E5A870D7C8__INCLUDED_)
#define AFX_DLGSETTINGTCP_H__87995BBE_366B_4EE7_AB99_02E5A870D7C8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgSettingTcp.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgSettingTcp dialog

class CDlgSettingTcp : public CDialog
{
// Construction
public:
	CDlgSettingTcp(CWnd* pParent = NULL);   // standard constructor

	CString m_csTcpFile;
	void SetFile(CString csfile);

	//
	void LoadFile();
	void InitValue();
	bool SaveData();

	tagIfTcpSetting	m_IfTcp;

	//
	bool SaveTcpData();
	bool GetDataFromUI(tagIfTcpSetting &UIData);
	void SaveDataToFile(tagIfTcpSetting FileData);

	CString m_csExtendErrMsg;

public:
	void InitIfNote();

// Dialog Data
	//{{AFX_DATA(CDlgSettingTcp)
	enum { IDD = IDD_SETTING_TCP };
	CStatic	m_wndIfNote;
	CEdit	m_wndSendStartDelay;
	CEdit	m_wndTcpTimeout;
	CEdit	m_wndTcpStart;
	CEdit	m_wndTcpReady;
	CEdit	m_wndTcpGo;
	CEdit	m_wndTcpBin;
	CEdit	m_wndTcpTail;
	CEdit	m_wndTcpHeader;
	CStatic	m_wndFile;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgSettingTcp)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgSettingTcp)
	virtual BOOL OnInitDialog();
	afx_msg void OnNote();
	afx_msg void OnEStatic();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGSETTINGTCP_H__87995BBE_366B_4EE7_AB99_02E5A870D7C8__INCLUDED_)
