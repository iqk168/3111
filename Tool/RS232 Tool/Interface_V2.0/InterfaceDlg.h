// InterfaceDlg.h : header file
//

#if !defined(AFX_INTERFACEDLG_H__401A2B5B_1B23_424B_AFBF_57B1E050B34F__INCLUDED_)
#define AFX_INTERFACEDLG_H__401A2B5B_1B23_424B_AFBF_57B1E050B34F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CInterfaceDlg dialog

class CInterfaceDlg : public CDialog
{
// Construction
public:
	void Add(char *buff, int size);
	CInterfaceDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	CColorBtn	m_btnCode2;
	//{{AFX_DATA(CInterfaceDlg)
	enum { IDD = IDD_INTERFACE_DIALOG };
	CEdit	m_wndValue;
	CButtonST	m_btnSend3;
	CEdit	m_wndCount;
	CEdit	m_edtSendText2;
	CButtonST	m_btnSend2;
	CColorBtn	m_btnCode;
	CButtonST	m_btnClear;
	CColorBtn	m_btnShowCode;
	CColorBtn	m_btnShowNumeric;
	CListBox	m_listShowText;
	CComboBox	m_cbxStopBit;
	CEdit	m_edtSendText;
	CButtonST	m_btnSend;
	CComboBox	m_cbxParityCheck;
	CComboBox	m_cbxDataBit;
	CComboBox	m_cbxComPort;
	CComboBox	m_cbxBaudRate;
	CButtonST	m_btnConnect;
	int		m_iBaudRate;
	int		m_iCodeOrNum;
	int		m_iPortNo;
	int		m_iDataBit;
	int		m_iParityCheck;
	CString	m_csSendText;
	int		m_iStopBit;
	CString	m_csSendText2;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CInterfaceDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void EnableWindow();
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CInterfaceDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnCancel();
	afx_msg void OnConnect();
	afx_msg void OnShowCode();
	afx_msg void OnShowNumeric();
	afx_msg void OnCode();
	afx_msg void OnCode2();
	afx_msg void OnSend();
	afx_msg void OnClear();
	afx_msg void OnSend2();
	afx_msg void OnSend3();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnSet();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INTERFACEDLG_H__401A2B5B_1B23_424B_AFBF_57B1E050B34F__INCLUDED_)
