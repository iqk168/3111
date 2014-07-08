#if !defined(AFX_DLGSOCKETVISIONLIVE_H__AF48902C_A403_44E3_B383_50A1EBD3E19C__INCLUDED_)
#define AFX_DLGSOCKETVISIONLIVE_H__AF48902C_A403_44E3_B383_50A1EBD3E19C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgSocketVisionLive.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgSocketVisionLive dialog

class CDlgSocketVisionLive : public CDialog
{
// Construction
public:
	CDlgSocketVisionLive(CWnd* pParent = NULL);   // standard constructor

	//
	void UpdateCameraControlList();

	//
	CToolTipCtrl m_ToolTip;

	//
	void InitDefault();
	void InitValue();
	void InitTips();

	// Thread ( Live )
	DWORD m_dwThreadIdCamera;
	static DWORD WINAPI WorkerThreadGrab(void* pVoid);		// Live ªº Thread

	//
	void ButtonLive(bool bLive );	// Live is true, No Live is falsel

	void ChangePage();
	void ClosePage();

// Dialog Data
	//{{AFX_DATA(CDlgSocketVisionLive)
	enum { IDD = IDD_DLG_SOCKETVISION_LIVE };
	CButtonST	m_BtnGrab;
	CButtonST	m_BtnLive;
	CComboBox	m_CBList;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgSocketVisionLive)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgSocketVisionLive)
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnSocketliveLive();
	afx_msg void OnSocketliveGrab();
	afx_msg void OnOperate();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGSOCKETVISIONLIVE_H__AF48902C_A403_44E3_B383_50A1EBD3E19C__INCLUDED_)
