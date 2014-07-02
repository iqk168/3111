#if !defined(AFX_DLGREPEATTRAYTEMP_H__1977D0E0_7196_4231_AAAE_132F65A37C42__INCLUDED_)
#define AFX_DLGREPEATTRAYTEMP_H__1977D0E0_7196_4231_AAAE_132F65A37C42__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgRepeatTrayTemp.h : header file
//

#include "ComboListCtrl.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgRepeatTrayTemp dialog

class CDlgRepeatTrayTemp : public CDialog
{
// Construction
public:
	CDlgRepeatTrayTemp(CWnd* pParent = NULL);   // standard constructor

	void Style();
	void InitTemp();
	void ShowTitle();

// Dialog Data
	//{{AFX_DATA(CDlgRepeatTrayTemp)
	enum { IDD = IDD_DLG_REPEAT_TRAY_TEMP };
	CComboListCtrl	m_List;
	CButtonST	m_btnCancel;
	CButtonST	m_btnOK;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgRepeatTrayTemp)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgRepeatTrayTemp)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnCustomdrawList ( NMHDR* pNMHDR, LRESULT* pResult );

	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGREPEATTRAYTEMP_H__1977D0E0_7196_4231_AAAE_132F65A37C42__INCLUDED_)
