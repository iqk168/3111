#if !defined(AFX_DLGSOCKETVISIONCTRLLIVE_H__A04321DF_7C14_4B0B_AB58_D1B0B18CDEA0__INCLUDED_)
#define AFX_DLGSOCKETVISIONCTRLLIVE_H__A04321DF_7C14_4B0B_AB58_D1B0B18CDEA0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgSocketVisionCtrlLive.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgSocketVisionCtrlLive dialog

class CDlgSocketVisionCtrlLive : public CDialog
{
// Construction
public:
	CDlgSocketVisionCtrlLive(CWnd* pParent = NULL);   // standard constructor

public:
	void InitValue();

	CToolTipCtrl m_ToolTip;
	void InitTips();

public:

	// Thread ( Live )
	DWORD m_dwThreadIdSocketCamera;
	static DWORD WINAPI WorkerThreadGrab(void* pVoid);

	//
	void UpdateCameraControlList();

	//
	void CameraLive();
	void CameraStop();
	void CameraCapture();
	void CaptureLockUI(bool bEnable);
	void LiveLockUI(bool bEnable);

public:

// Dialog Data
	//{{AFX_DATA(CDlgSocketVisionCtrlLive)
	enum { IDD = IDD_DLG_SOCKETVISION_CTL_LIVE };
	CComboBox	m_CBList;
	CButtonST	m_btnLive;
	CButtonST	m_btnGrab;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgSocketVisionCtrlLive)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgSocketVisionCtrlLive)
	virtual BOOL OnInitDialog();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnSocketliveLive();
	afx_msg void OnSocketliveGrab();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGSOCKETVISIONCTRLLIVE_H__A04321DF_7C14_4B0B_AB58_D1B0B18CDEA0__INCLUDED_)
