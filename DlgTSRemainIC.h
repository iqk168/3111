#if !defined(AFX_DLGTSREMAINIC_H__39D1B59F_ECFB_4760_A770_90AEAA213917__INCLUDED_)
#define AFX_DLGTSREMAINIC_H__39D1B59F_ECFB_4760_A770_90AEAA213917__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgTSRemainIC.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgTSRemainIC dialog

class CDlgTSRemainIC : public CDialog
{
// Construction
public:
	CDlgTSRemainIC(CWnd* pParent = NULL);   // standard constructor

	void InitValue();
	void InitTips();
	void InitLed();
	void StatusQuery();

	bool SaveData();

	//
	CToolTipCtrl m_ToolTip;
// Dialog Data
	//{{AFX_DATA(CDlgTSRemainIC)
	enum { IDD = IDD_DLG_TS_REMAIN_IC };
	CButtonST	m_btnTSRemainVaccAlwaysOn;
	CLed		m_ledTSRemainICFlag;
	CLed		m_ledEnableFunction;
	CButtonST	m_btnOK;
	CButtonST	m_btnCancel;
	double		m_dTSRemainVaccTime;
	int			m_iTSRemainICSpeed;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgTSRemainIC)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgTSRemainIC)
	virtual void OnOK();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGTSREMAINIC_H__39D1B59F_ECFB_4760_A770_90AEAA213917__INCLUDED_)
