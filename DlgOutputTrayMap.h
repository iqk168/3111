#if !defined(AFX_DLGOUTPUTTRAYMAP_H__27F59CE2_EA26_43DA_A967_0B8ACFA114B4__INCLUDED_)
#define AFX_DLGOUTPUTTRAYMAP_H__27F59CE2_EA26_43DA_A967_0B8ACFA114B4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgOutputTrayMap.h : header file
//

#include "TrayMapCtrl.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgOutputTrayMap dialog

class CDlgOutputTrayMap : public CDialog
{
// Construction
public:
	CDlgOutputTrayMap(int iCol, int iRow, int *piStatus, CWnd* pParent = NULL);   // standard constructor

	void InitTips();

// Dialog Data
	//{{AFX_DATA(CDlgOutputTrayMap)
	enum { IDD = IDD_DLG_OUTPUTTRAY };
	CButtonST	m_btnCancel;
	CButtonST	m_btnOK;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgOutputTrayMap)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	struct tagTrayMap
	{
		int	iCol;				// Tray 共有幾行.
		int	iRow;				// Tray 共有幾列.
		int	iStatus[50][100];	// Tray 每一個 Device 的狀態.
	} m_trayMap;

	int				*m_piStatus;
	CTrayMapCtrl	m_stTrayMap;
	UINT m_uiTimer;

	// Generated message map functions
	//{{AFX_MSG(CDlgOutputTrayMap)
	afx_msg void OnDestroy();
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnClearAll();
	afx_msg void OnInvert();
	virtual void OnOK();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGOUTPUTTRAYMAP_H__27F59CE2_EA26_43DA_A967_0B8ACFA114B4__INCLUDED_)
