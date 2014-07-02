#if !defined(AFX_DLGEXTENDFUNCTION_H__67AF2C93_4E44_44BB_AF68_2A78AB01DFFC__INCLUDED_)
#define AFX_DLGEXTENDFUNCTION_H__67AF2C93_4E44_44BB_AF68_2A78AB01DFFC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgExtendFunction.h : header file
//

#include "ColorBtn.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgExtendFunction dialog

class CDlgExtendFunction : public CDialog
{
// Construction
public:
	CDlgExtendFunction(CString file = _T(""), CWnd* pParent = NULL);   // standard constructor

	//
	tagTestSetting m_TestSetting;

	CString		m_file;
	void SaveTesting(CString csFile);
	void LoadTesting(CString csFile);

	//
	void InitValue();
	void InitTips();

	void SaveData();

	// 
	void ReDrawUI();

	//
	void UpdataExterndFunctionButton();	

public:

	// 1.0Ah
	void InitRotatorUI();
	void EnableRotatorUI(int bEnable);
	void ReDrawRotatorUI();

// Dialog Data
	//{{AFX_DATA(CDlgExtendFunction)
	enum { IDD = IDD_DLG_EXTEND_FUNCTION };

	CButtonST	m_btnOK;
	CButtonST	m_btnCancel;
	
	//
	CColorBtn	m_n90;
	CColorBtn	m_p90;
	CColorBtn	m_p0;
	CColorBtn	m_p180;

	//
	CColorBtn	m_btnCCDSocket;
	CColorBtn	m_btnCCDUse;
	CColorBtn	m_btnRotatorUse;
	int			m_iAngle;

	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgExtendFunction)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgExtendFunction)
	virtual void OnOK();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnCcdSocketUse();
	afx_msg void OnCcdUse();
	afx_msg void OnRotatorUse();
	afx_msg void OnN90();
	afx_msg void OnP90();
	afx_msg void OnP0();
	afx_msg void OnP180();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGEXTENDFUNCTION_H__67AF2C93_4E44_44BB_AF68_2A78AB01DFFC__INCLUDED_)
