#if !defined(AFX_DLGTEMPERATURETOOL_H__8079F3CB_313D_4769_838A_E32112833685__INCLUDED_)
#define AFX_DLGTEMPERATURETOOL_H__8079F3CB_313D_4769_838A_E32112833685__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgTemperatureTool.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgTemperatureTool dialog

class CDlgTemperatureTool : public CDialog
{
// Construction
public:
	CDlgTemperatureTool(CWnd* pParent = NULL);   // standard constructor

	void InitController();
	void FunctionClearOffset();

	long m_WestID;

// Dialog Data
	//{{AFX_DATA(CDlgTemperatureTool)
	enum { IDD = IDD_DLG_TEMPERATURE_TOOL };
	CComboBox	m_cbxControllerSel;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgTemperatureTool)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgTemperatureTool)
	virtual BOOL OnInitDialog();
	afx_msg void OnFClearOffset();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGTEMPERATURETOOL_H__8079F3CB_313D_4769_838A_E32112833685__INCLUDED_)
