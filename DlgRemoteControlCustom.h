#if !defined(AFX_DLGREMOTECONTROLCUSTOM_H__3DB357F6_81D7_4F29_9CDA_A841041CA275__INCLUDED_)
#define AFX_DLGREMOTECONTROLCUSTOM_H__3DB357F6_81D7_4F29_9CDA_A841041CA275__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgRemoteControlCustom.h : header file
//

#include "TrayMapSelCtrl.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgRemoteControlCustom dialog

class CDlgRemoteControlCustom : public CDialog
{
// Construction
public:
	CDlgRemoteControlCustom(CWnd* pParent = NULL);   // standard constructor

	void InitUI();
	void InitLed();
	void UpdateSel();
	void UpdatePos();

	//
	BOOL bPickButtonStatus;
	BOOL bReleaseButtonStatus;
	void BackupUI();
	void RecoverUI();

	//
	void ChangeUI( int Status );
	void InitRemoteControl();
	void ReleaseRemoteControl();

	//
	void InitTrayStatus();

	//
	void PickIC();
	void ReleaseIC();
	void ContinueIC();

	//
	CArray <tagInputTrayDataFile, tagInputTrayDataFile> m_LoadFileData;
	void LoadTrayStatus(int value); // Remote Input Status..
	struct tagTrayMap
	{
		int	iCol;				// Tray 共有幾行.
		int	iRow;				// Tray 共有幾列.
		int	iStatus[50][100];	// Tray 每一個 Device 的狀態.
	} m_trayMap;

	//
	bool IsInputMark();

public:
	CTrayMapSelCtrl	m_stTrayMap;

// Dialog Data
	//{{AFX_DATA(CDlgRemoteControlCustom)
	enum { IDD = IDD_DLG_REMOTE_CUSTOM };
	CStatic	m_wndPosition;
	CButton	m_btnContinue;
	CButton	m_btnReleaseIC;
	CButton	m_btnPickIC;
	CLed	m_ledAlarm;
	CLed	m_ledReady;
	CButtonST	m_btnCancel;
	CButtonST	m_btnOK;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgRemoteControlCustom)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgRemoteControlCustom)
	virtual void OnOK();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnStInputtray();
	afx_msg void OnAstatic();
	afx_msg void OnEPickIc();
	afx_msg void OnEReleaseIc();
	afx_msg void OnEContinue();

	//
	afx_msg LRESULT OnRemoteReady(WPARAM p, LPARAM l);
	afx_msg LRESULT OnRemoteReleaseIC(WPARAM p, LPARAM l);
	afx_msg LRESULT OnRemotePickIC(WPARAM p, LPARAM l);
	afx_msg LRESULT OnRemoteAlarm(WPARAM p, LPARAM l);


	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGREMOTECONTROLCUSTOM_H__3DB357F6_81D7_4F29_9CDA_A841041CA275__INCLUDED_)
