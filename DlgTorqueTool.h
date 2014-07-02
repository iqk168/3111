#if !defined(AFX_DLGTORQUETOOL_H__88AABDCB_8156_43A7_8A40_78EEC4CDCFCF__INCLUDED_)
#define AFX_DLGTORQUETOOL_H__88AABDCB_8156_43A7_8A40_78EEC4CDCFCF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgTorqueTool.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgTorqueTool dialog

class CDlgTorqueTool : public CDialog
{
// Construction
public:
	CDlgTorqueTool(CWnd* pParent = NULL);   // standard constructor
	void InitValue();

// Dialog Data
	//{{AFX_DATA(CDlgTorqueTool)
	enum { IDD = IDD_DLG_TORQUE_TOOL };
	CButtonST	m_btnSet;
	CStatic	m_wndResult;
	CButtonST	m_btnCancel;
	CButtonST	m_btnOK;
	double	m_dSetA;
	double	m_dSetB;
	double	m_dSetTorque;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgTorqueTool)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgTorqueTool)
	virtual void OnOK();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnSet();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGTORQUETOOL_H__88AABDCB_8156_43A7_8A40_78EEC4CDCFCF__INCLUDED_)
