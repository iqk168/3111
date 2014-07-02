#if !defined(AFX_DLGREMOTECOMMMSG_H__86C593EE_9E4E_46DE_B646_CB4271FA3F43__INCLUDED_)
#define AFX_DLGREMOTECOMMMSG_H__86C593EE_9E4E_46DE_B646_CB4271FA3F43__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgRemoteCommMsg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgRemoteCommMsg dialog

class CDlgRemoteCommMsg : public CDialog
{
// Construction
private:
	HANDLE hProcess;

public:
	CDlgRemoteCommMsg(CWnd* pParent = NULL);   // standard constructor

	void InitCustomCoordnation();

public:
	void LockUI(bool bEnable);
	void CloseCommandThread();
	bool m_bCommandLoopRun;
	static UINT ThreadCommandLoopThread(LPVOID p);
	COleDateTimeSpan tSpend;
	CString GetRunTimeTime(long lsecs);


// Dialog Data
	//{{AFX_DATA(CDlgRemoteCommMsg)
	enum { IDD = IDD_DLG_REMOTE_COMMUNICATION_MSG };
	CStatic		m_wndSpendTime;
	CComboBox	m_cbxCoordnationRow;
	CComboBox	m_cbxCoordnationCol;
	CComboBox	m_cbxCoordnationTray;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgRemoteCommMsg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgRemoteCommMsg)
	virtual BOOL OnInitDialog();
	afx_msg void OnFGetstatus();
	afx_msg void OnFVersion();
	afx_msg void OnFGetsiteTemp();
	afx_msg void OnFSetsiteTemp();
	afx_msg void OnFEnableTemp();
	afx_msg void OnFEnableTemp2();
	afx_msg void OnFEnableRota();
	afx_msg void OnFEnableRota2();
	afx_msg void OnFChangeRota();
	afx_msg void OnFChangeRota2();
	afx_msg void OnFChangeRota3();
	afx_msg void OnFChangeRota4();
	afx_msg void OnFEnableCcd();
	afx_msg void OnFEnableCcd2();
	afx_msg void OnFSetCoordnation();
	afx_msg void OnFGetCoordnation();
	afx_msg void OnFChangeAutoskip();
	afx_msg void OnFChangeAutoskip2();
	afx_msg void OnFGetAutoskip();
	afx_msg void OnFGetTrayspec();
	afx_msg void OnFSetCoordnation2();
	afx_msg void OnFSetCustomCoordnation();
	afx_msg void OnFGetCoordnationGo();
	afx_msg void OnFGetCoordnationReturn();
	afx_msg void OnFPickLoopStart();
	afx_msg void OnFPickLoopStop();
	afx_msg void OnFGetsiteTempMeas();
	afx_msg void OnFSetSetcoordnationClearGo();
	afx_msg void OnFGetstate();
	afx_msg void OnFGethelp();
	afx_msg void OnFGetRota();
	afx_msg void OnFSetPressure();
	afx_msg void OnFGetPressure();
	afx_msg void OnFButtonInitial();
	afx_msg void OnFButtonStart();
	afx_msg void OnFButtonStop();
	afx_msg void OnFButtonRetry();
	afx_msg void OnFButtonSkip();
	afx_msg void OnFButtonReset();
	afx_msg void OnFButtonOnecycle();
	afx_msg void OnFSetTsVacc();
	afx_msg void OnFSetTsVacc2();
	afx_msg void OnFGetTsVacc();

	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGREMOTECOMMMSG_H__86C593EE_9E4E_46DE_B646_CB4271FA3F43__INCLUDED_)
