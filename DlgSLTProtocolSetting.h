#if !defined(AFX_DLGSLTPROTOCOLSETTING_H__8443FF95_BEF5_426C_B625_9B4050683FA5__INCLUDED_)
#define AFX_DLGSLTPROTOCOLSETTING_H__8443FF95_BEF5_426C_B625_9B4050683FA5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgSLTProtocolSetting.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgSLTProtocolSetting dialog

class CDlgSLTProtocolSetting : public CDialog
{
// Construction
public:
	CDlgSLTProtocolSetting(CWnd* pParent = NULL);   // standard constructor

	void InitValue();
	void InitUI();

// Dialog Data
	//{{AFX_DATA(CDlgSLTProtocolSetting)
	enum { IDD = IDD_DLG_SLT_PROTOCOL_SETTING };
	CGroupControl	m_wndSerialGrp;
	CStatic	m_wndEthernetPort;
	CStatic	m_wndEthernetIPAddress;
	CStatic	m_wndSerialPort;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgSLTProtocolSetting)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgSLTProtocolSetting)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGSLTPROTOCOLSETTING_H__8443FF95_BEF5_426C_B625_9B4050683FA5__INCLUDED_)
