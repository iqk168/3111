#if !defined(AFX_DLGATCMODULECALIBRATION_H__B1F0E5B8_4CFF_4213_9896_5E90FF075465__INCLUDED_)
#define AFX_DLGATCMODULECALIBRATION_H__B1F0E5B8_4CFF_4213_9896_5E90FF075465__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgATCModuleCalibration.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgATCModuleCalibration dialog

class CDlgATCModuleCalibration : public CDialog
{
// Construction
public:
	CDlgATCModuleCalibration(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgATCModuleCalibration)
	enum { IDD = IDD_DLG_ATC_MODULE_CALIBRATION };
	CButtonST	m_btnOK;
	CButtonST	m_btnCancel;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgATCModuleCalibration)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgATCModuleCalibration)
	virtual void OnOK();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGATCMODULECALIBRATION_H__B1F0E5B8_4CFF_4213_9896_5E90FF075465__INCLUDED_)
