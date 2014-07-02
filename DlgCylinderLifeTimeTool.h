#if !defined(AFX_DLGCYLINDERLIFETIMETOOL_H__85989E9B_91B0_49E8_B0D0_BEB03C82F02B__INCLUDED_)
#define AFX_DLGCYLINDERLIFETIMETOOL_H__85989E9B_91B0_49E8_B0D0_BEB03C82F02B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgCylinderLifeTimeTool.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgCylinderLifeTimeTool dialog

class CDlgCylinderLifeTimeTool : public CDialog
{
// Construction
public:
	CDlgCylinderLifeTimeTool(CWnd* pParent = NULL);   // standard constructor

	// Normal
	void LockUI(bool bEnable);	// true for lock

	// Shuttle
	long m_lShHomeCount;
	long m_lShPPCount;
	long m_lShCounter;
	double m_dShDelayTime;
	bool m_bEnableShLife;
	void UpDataShValu();
	static UINT ShLifeTimeThread(LPVOID p);

	// Rotatro
	long m_lRoNNCount;
	long m_lRoPPCount;
	long m_lRoCounter;
	double m_dRoDelayTime;
	bool m_bEnableRoLife;
	void UpDataRoValu();
	static UINT RoLifeTimeThread(LPVOID p);


	//
	void InitValue();

// Dialog Data
	//{{AFX_DATA(CDlgCylinderLifeTimeTool)
	enum { IDD = IDD_DLG_CYLINDER_LIFE_TIME };
	CStatic			m_wndRoPP;
	CStatic			m_wndRoNN;
	CEdit			m_wndRoDelayTime;
	CStatic			m_wndRoCounter;
	CButton			m_btnRoClear;
	CButton			m_btnRoStop;
	CButton			m_btnRoReport;
	CButton			m_btnRoGo;
	CStatic			m_wndShCounter;
	CEdit			m_wndShDelayTime;
	CButton			m_btnShClear;
	CStatic			m_wndShPP;
	CStatic			m_wndShHome;
	CButton			m_btnShStop;
	CButton			m_btnShReport;
	CButton			m_btnShGo;
	CButtonST		m_btnOK;
	CButtonST		m_btnCancel;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgCylinderLifeTimeTool)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgCylinderLifeTimeTool)
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnFShGo();
	afx_msg void OnFShStop();
	afx_msg void OnFShClear();
	afx_msg void OnFShReport();
	virtual void OnCancel();
	virtual void OnOK();
	afx_msg void OnFRoGo();
	afx_msg void OnFRoStop();
	afx_msg void OnFRoClear();
	afx_msg void OnFRoReport();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGCYLINDERLIFETIMETOOL_H__85989E9B_91B0_49E8_B0D0_BEB03C82F02B__INCLUDED_)
