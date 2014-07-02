// TcpInterfaceDlg.h : header file
//

#if !defined(AFX_TCPINTERFACEDLG_H__7E99E7FC_3792_4127_A6F4_CD7850DF3130__INCLUDED_)
#define AFX_TCPINTERFACEDLG_H__7E99E7FC_3792_4127_A6F4_CD7850DF3130__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CTcpInterfaceDlg dialog

#include "ThTesting.h"
#include "NetInterface.h"
#include "BtnST.h"
#include "ColorFontStatic.h"

#define _Site_No 16

class CTcpInterfaceDlg : public CDialog
{
// Construction
public:
	CTcpInterfaceDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CTcpInterfaceDlg)
	enum { IDD = IDD_TCPINTERFACE_DIALOG };
	CButtonST	m_btnSnet3;
	CButtonST	m_btnExit;
	CButtonST	m_btnSent1;
	CButtonST	m_btnSent2;
	CButtonST	m_btnClear;
	CButtonST	m_btnConnectServer;
	CIPAddressCtrl	m_edtIpAddress;
	CListBox	m_wndDisplay;
	long		m_iPort;
	//}}AFX_DATA

	CColorFontStatic	m_wndSiteCode[_Site_No];

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTcpInterfaceDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

public:
	CString getIpAddress();
	void DisplayErrorCode(int iSite, CString Code, COLORREF Color);
	void AddString(char *csText);
	CNetInterface m_Interface;
	
	CThTesting	*m_ThTesting[_Site_No];

	// Generated message map functions
	//{{AFX_MSG(CTcpInterfaceDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnConnectServer();
	afx_msg void OnSend1();
	afx_msg void OnSend2();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnClear();
	afx_msg void OnDestroy();
	afx_msg void OnAutoTestConnect();
	virtual void OnOK();
	afx_msg void OnSend3();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	char changeHex(char c);
	void addBCC(CString &Message);
	void UpdateInfo();
	CString GetErrorCode(char *Buffer);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TCPINTERFACEDLG_H__7E99E7FC_3792_4127_A6F4_CD7850DF3130__INCLUDED_)
