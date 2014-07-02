// DeerDlg.h : header file
//

#if !defined(AFX_DEERDLG_H__2E622D63_E4BD_4090_A21A_EF3D6E17D599__INCLUDED_)
#define AFX_DEERDLG_H__2E622D63_E4BD_4090_A21A_EF3D6E17D599__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DlgError.h"

/////////////////////////////////////////////////////////////////////////////
// CDeerDlg dialog

class CDeerDlg : public CDialog
{
// Construction

protected:	
	CDlgError		*m_pErrDlg;

public:
	CDeerDlg(CWnd* pParent = NULL);	// standard constructor

	void OnErrorClear();

	// UI
	void SetUserPage(int level = enLevelUser, int page = 0); // 設定目前的 Tag 頁面
	void SetHandlerInfo();	// 設定目前UI顯示的資訊,包括 機台編號.機台名稱. 軟體版本.
	void SetMachineInfo();  // 顯示 目前的 Machine ID
	// UI Timer
	void UpdateTime();
	void UpdateCycleTime();
	void UpdataButton();
	void UpdataMainMsg();
	void UpdataTorqueStatus();
	void UpdateJamRateCycleTime();

public:
	bool m_bShowMainMsg;


// Dialog Data
	//{{AFX_DATA(CDeerDlg)
	enum { IDD = IDD_DEER_DIALOG };

	CColorFontStatic 	m_wndMainMsg;

	CStatic	m_wndTime;
	CButtonST	m_btnShutDown;
	CButtonST	m_btnUser;
	CTabCtrl	m_MainTab;
	CString	m_csMachine;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDeerDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;	

	// Generated message map functions
	//{{AFX_MSG(CDeerDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnDebug();
	afx_msg void OnVisualPanel();
	afx_msg void OnUser();
	afx_msg void OnTab();
	afx_msg void OnIOMontior();
	afx_msg void OnMotorMontior();
	afx_msg void OnThreadMontior();
	afx_msg void OnThread();
	afx_msg void OnMotorStatus();
	afx_msg void OnButton();
	afx_msg void OnBinStatus();
	afx_msg void OnMotorSimpleStatus();
	afx_msg void OnReLoadFile();
	afx_msg void OnLogEnable();
	afx_msg void OnDataUsing();
	afx_msg void OnDebugError();
	afx_msg void OnSummaryReport();
	afx_msg void OnErrorList();
	afx_msg void OnHandlerStatusReport();
	afx_msg void OnJamRateReport();
	afx_msg void OnAutoRetrySetting();
	afx_msg void OnTrayStatus();
	afx_msg void OnBinColor();
	afx_msg void OnCCDList();
	afx_msg void OnYieldMonitor();
	afx_msg void OnUPHData();
	afx_msg void OnCylinderLifeTimeTool();
	afx_msg void OnWestCtrlTool();
	afx_msg void OnTSRemainIC();
	afx_msg void OnTorqueCtrlTool();
	afx_msg void OnCommunicationTool();
	afx_msg void OnRemoteComm();

	afx_msg LRESULT OnHandlerID(WPARAM p, LPARAM l);
	afx_msg void OnSelchangeViewTable(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg LRESULT OnErrorClose(WPARAM p, LPARAM l);
	afx_msg LRESULT OnError(WPARAM p, LPARAM l);
	afx_msg void OnShutDown();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnDestroy();
	afx_msg void OnClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DEERDLG_H__2E622D63_E4BD_4090_A21A_EF3D6E17D599__INCLUDED_)
