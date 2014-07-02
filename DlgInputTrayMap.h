#if !defined(AFX_DLGINPUTTRAYMAP_H__8897FFC9_5112_4166_8E51_DCF1C7E455F1__INCLUDED_)
#define AFX_DLGINPUTTRAYMAP_H__8897FFC9_5112_4166_8E51_DCF1C7E455F1__INCLUDED_

#include "TrayMapCtrl.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgInputTrayMap.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgInputTrayMap dialog

class CDlgInputTrayMap : public CDialog
{
// Construction
public:
	CDlgInputTrayMap(int iCol, int iRow, int *piStatus, CWnd* pParent = NULL);   // standard constructor

	void InitTips();

// Dialog Data
	//{{AFX_DATA(CDlgInputTrayMap)
	enum { IDD = IDD_DLG_INPUTTRAY };
	CButtonST	m_btnOK;
	CButtonST	m_btnCancel;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgInputTrayMap)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgInputTrayMap)
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	afx_msg void OnTimer(UINT nIDEvent);
	virtual void OnOK();
	afx_msg void OnInvert();
	afx_msg void OnClearAll();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	
	struct tagTrayMap
	{
		int	iCol;				// Tray 共有幾行.
		int	iRow;				// Tray 共有幾列.
		int	iStatus[50][100];	// Tray 每一個 Device 的狀態.
	} m_trayMap;

	int				*m_piStatus;
	CTrayMapCtrl	m_stTrayMap;
	UINT m_uiTimer;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGINPUTTRAYMAP_H__8897FFC9_5112_4166_8E51_DCF1C7E455F1__INCLUDED_)
