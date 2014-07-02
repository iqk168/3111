#if !defined(AFX_DLGREMOTECONTROLCUSTOMINPUT_H__038BD5F1_FC5F_4A81_A393_9A5235D24D70__INCLUDED_)
#define AFX_DLGREMOTECONTROLCUSTOMINPUT_H__038BD5F1_FC5F_4A81_A393_9A5235D24D70__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgRemoteControlCustomInput.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgRemoteControlCustomInput dialog

#include "TrayMapCtrl.h"

class CDlgRemoteControlCustomInput : public CDialog
{
// Construction
public:
	CDlgRemoteControlCustomInput(int iCol, int iRow, CWnd* pParent = NULL);   // standard constructor

	void InitTrayStatus();
	void InitDropListValue();

	//
	bool bLoadFile;
	CArray <tagInputTrayDataFile, tagInputTrayDataFile> m_LoadFileData;
	void LoadTrayStatus(int value);
	void SaveTrayStatus(int value);

	//
	void SetDefault(int value);

// Dialog Data
	//{{AFX_DATA(CDlgRemoteControlCustomInput)
	enum { IDD = IDD_DLG_REMOTE_CUSTOM_INPUT };
	CButtonST	m_btnOK;
	CButtonST	m_btnCancel;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgRemoteControlCustomInput)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgRemoteControlCustomInput)
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT nIDEvent);
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnClearAll();
	afx_msg void OnInvert();
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

#endif // !defined(AFX_DLGREMOTECONTROLCUSTOMINPUT_H__038BD5F1_FC5F_4A81_A393_9A5235D24D70__INCLUDED_)
