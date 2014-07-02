#if !defined(AFX_DLGHANDLERCOMPORT_H__1C0E8C39_CAAB_4F53_8627_68CDCD6185B2__INCLUDED_)
#define AFX_DLGHANDLERCOMPORT_H__1C0E8C39_CAAB_4F53_8627_68CDCD6185B2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgHandlerComPort.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgHandlerComPort dialog

class CDlgHandlerComPort : public CDialog
{
// Construction
public:
	CDlgHandlerComPort(CWnd* pParent = NULL);   // standard constructor

	CToolTipCtrl m_ToolTip;
	void InitTips();

	void InitValue();
	void SaveData();

	//
	tagHandlerComPort	m_HandlerComPort;

	bool m_fChange;
// Dialog Data
	//{{AFX_DATA(CDlgHandlerComPort)
	enum { IDD = IDD_DLG_HANDLER_COM_PORT };
	CEdit	m_wndRemotePort;
	CEdit	m_wndTorqueStatus;
	CEdit	m_wndWestHeaterID;
	CEdit	m_wndRemoteIOPort3;
	CEdit	m_wndWestPort;
	CEdit	m_wndATCModulePort;
	CEdit	m_wndTesterPort;
	CEdit	m_wndRemoteIOPort2;
	CEdit	m_wndRemoteIOPort;
	CEdit	m_wndPIDPort2;
	CEdit	m_wndPIDPort;
	CButtonST	m_btnOK;
	CButtonST	m_btnCancel;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgHandlerComPort)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgHandlerComPort)
	virtual void OnOK();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnChangeEPortPid();
	afx_msg void OnChangeEPortRemoteIo();
	afx_msg void OnChangeEPortTester();
	afx_msg void OnChangeEPortAtcModule();
	afx_msg void OnChangeEPortPid2();
	afx_msg void OnChangeEPortRemoteIo2();
	afx_msg void OnChangeEPortTorqueStatus();
	afx_msg void OnChangeEPortRemote();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGHANDLERCOMPORT_H__1C0E8C39_CAAB_4F53_8627_68CDCD6185B2__INCLUDED_)
