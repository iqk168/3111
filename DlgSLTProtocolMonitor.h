#if !defined(AFX_DLGSLTPROTOCOLMONITOR_H__89851807_BD40_404F_AB1F_1A3F721C422E__INCLUDED_)
#define AFX_DLGSLTPROTOCOLMONITOR_H__89851807_BD40_404F_AB1F_1A3F721C422E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgSLTProtocolMonitor.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgSLTProtocolMonitor dialog

class CDlgSLTProtocolMonitor : public CDialog
{
// Construction
public:
	CDlgSLTProtocolMonitor(CWnd* pParent = NULL);   // standard constructor

	void InitValue();
	void InitUI();

	//
	void InsertLogRaw(CString csLog);

// Dialog Data
	//{{AFX_DATA(CDlgSLTProtocolMonitor)
	enum { IDD = IDD_DLG_SLT_PROTOCOL_MONITOR };
	CListBox	m_listRaw;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgSLTProtocolMonitor)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgSLTProtocolMonitor)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGSLTPROTOCOLMONITOR_H__89851807_BD40_404F_AB1F_1A3F721C422E__INCLUDED_)
