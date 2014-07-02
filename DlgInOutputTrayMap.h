#if !defined(AFX_DLGINOUTPUTTRAYMAP_H__E9038DCB_A5A7_4FE1_B7EB_0B162F704B33__INCLUDED_)
#define AFX_DLGINOUTPUTTRAYMAP_H__E9038DCB_A5A7_4FE1_B7EB_0B162F704B33__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgInOutputTrayMap.h : header file
//

#include "TrayMapCtrl.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgInOutputTrayMap dialog

class CDlgInOutputTrayMap : public CDialog
{
// Construction
public:
	CDlgInOutputTrayMap(int iCol, int iRow, int *piStatusInput, int *piStatusOutput, CWnd* pParent = NULL);   // standard constructor

	//
	void InitInputTrayObject(int iCol, int iRow, int *piStatusInput);
	void InitOutputTrayObject(int iCol, int iRow, int *piStatusOutput);

	void InitInputTray();
	void InitOutputTray();

	//
	void SaveTrayStatus();
	void SaveInputTrayStatus();
	void SaveOutputTrayStatus();

// Dialog Data
	//{{AFX_DATA(CDlgInOutputTrayMap)
	enum { IDD = IDD_DLG_IN_OUT_TRAY };
	CButtonST	m_btnCancel;
	CButtonST	m_btnOK;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgInOutputTrayMap)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Input 
	struct tagTrayMapInput
	{
		int	iCol;				// Tray 共有幾行.
		int	iRow;				// Tray 共有幾列.
		int	iStatus[50][100];	// Tray 每一個 Device 的狀態.
	} m_trayMapInput;

	int				*m_piStatusInput;
	CTrayMapCtrl	m_stTrayMapInput;

	// Output 
	struct tagTrayMapOutput
	{
		int	iCol;				// Tray 共有幾行.
		int	iRow;				// Tray 共有幾列.
		int	iStatus[50][100];	// Tray 每一個 Device 的狀態.
	} m_trayMapOutput;

	int				*m_piStatusOutput;
	CTrayMapCtrl	m_stTrayMapOutput;

	UINT m_uiTimer;

	// Generated message map functions
	//{{AFX_MSG(CDlgInOutputTrayMap)
	afx_msg void OnInClearAll();
	afx_msg void OnInInvert();
	afx_msg void OnOutClearAll();
	afx_msg void OnOutInvert();
	virtual void OnOK();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGINOUTPUTTRAYMAP_H__E9038DCB_A5A7_4FE1_B7EB_0B162F704B33__INCLUDED_)
