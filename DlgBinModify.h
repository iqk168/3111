#if !defined(AFX_DLGBINMODIFY_H__20E22CFE_04A1_4127_AE4B_980F43D3505E__INCLUDED_)
#define AFX_DLGBINMODIFY_H__20E22CFE_04A1_4127_AE4B_980F43D3505E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgBinModify.h : header file
//

#include ".\GridCtrl\GridCtrl.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgBinModify dialog

class CDlgBinModify : public CDialog
{
// Construction
public:
	CDlgBinModify(CString TempFileName,
		CArray <tagBinMapping, tagBinMapping> *BinMap,
		CWnd* pParent = NULL);   // standard constructor
	void LoadBinMapping(CString file);

// Dialog Data
	//{{AFX_DATA(CDlgBinModify)
	enum { IDD = IDD_DLG_BIN_MODIFY };

	CButtonST	m_btnOK;
	CButtonST	m_btnCancel;

	CButtonST	m_btnSave;
	CButtonST	m_btnInsert;
	CButtonST	m_btnDelete;

	CGridCtrl	m_Grid;

		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgBinModify)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	void UpdateView();

	CString m_TempFileName;
	CArray <tagBinMapping, tagBinMapping> *m_SourceBinMap, m_BinMap;

	// Generated message map functions
	//{{AFX_MSG(CDlgBinModify)
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnInsert();
	afx_msg void OnSave();
	afx_msg void OnDelete();
	afx_msg void OnClose();
	afx_msg void OnDestroy();
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGBINMODIFY_H__20E22CFE_04A1_4127_AE4B_980F43D3505E__INCLUDED_)
