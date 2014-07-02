#if !defined(AFX_DLGVISIONSETUP_H__8CFDF177_7162_4138_A8C5_A52A82A50B99__INCLUDED_)
#define AFX_DLGVISIONSETUP_H__8CFDF177_7162_4138_A8C5_A52A82A50B99__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgVisionSetup.h : header file
//

#include "CtrlVisionAlignment.h"
#include "CtrlVisionMatch.h"
#include "ViewImage.h"
/////////////////////////////////////////////////////////////////////////////
// CDlgVisionSetup dialog

class CDlgVisionSetup : public CDialog
{
// Construction
public:
	CDlgVisionSetup(CWnd* pParent = NULL);   // standard constructor

public:
	CViewImage	*pViewGrabImage;

public:

	//
	CCtrlVisionMatch		m_VisionMatch;

public:

	bool CheckTrayIsUse(CString csFileName, CString &csNowFileName);

	//
	CArray <CString, CString> m_FileDictory;

	//
	CToolTipCtrl m_ToolTip;

	//
	void InitLib();
	void InitImage();
	void InitTips();
	void InitValue();

	//
	CString GetSettingFileName();
	double GetSettingScore();
	CString GetCurrentSettingFileName();

	//
	CRect GetSettingROI();

	//
	CRect GetPatternInfo();
	CRect GetDefaulePatternInfo();
	void SetPatternInfo(CString csPath, tagInfoParameter m_Info);

	//
	void UpdataSettingList();
	void GetSettingFolder();
	void GetSettingFolderInfo();
	void MatchResult(double dResult, double dScore);	// 顯示比對結果

	//
	void UpdataPatternInfo();

	//
	void Message( CString csMsg = _T(""));

	// Function
	void FunctionLoad();
	void FunctionNewLoad();	// show grab
	void FunctionSave();
	void FunctionDelete();
	void FunctionNew();
	bool IsFileExist();

	// temp show image
	CString CopyImageToTemp();

	//
	bool DeleteIMGFile(CString csSettingName);	// copy

	//
	// Thread ( Live )
	DWORD m_dwThreadIdCamera;
	static UINT WorkerThreadGrab(LPVOID p);		// Live 的 Thread

	// Live
	void CameraLive();
	void CameraLiveStop();
	void LiveLockUI(bool bEnable);

	// Grab
	void CaptureLockUI(bool bEnable);
	void CameraCapture();

	// File Lock All
	void FileLockUI(bool bEnable);

	//
	void SetInitialFile();

	// Debug
	void UnLockDebugUI();

	//
	HANDLE hProcess;

public:

	void MoationLockUI(bool bEnable);
	void MoationMotorErrorLockAll();
	void MoationDeviceInUI();
	void MoationDeviceOutUI();
	void MoationDeviceMoveCheck();
	bool m_IsDeviceIn;
public:
	static UINT DeviceInThread(LPVOID p);
	static UINT DeviceOutThread(LPVOID p);

// Dialog Data
	//{{AFX_DATA(CDlgVisionSetup)
	enum { IDD = IDD_DLG_VISION_SETUP };
	CColorFontStatic	m_wndTestScore;
	CButton	m_btnMatch;
	CButton	m_btnDeviceOutput;
	CButton	m_btnDeviceInput;
	CButton	m_btnLive;
	CButton	m_btnStop;
	CStatic	m_wndFileName;
	CEdit	m_wndScoreHeight;
	CEdit	m_wndScoreWidth;
	CEdit	m_wndScoreY;
	CEdit	m_wndScoreX;
	CEdit	m_wndScoreMinMatchScore;
	CStatic	m_stcPicture;
	CButtonST	m_btnGrab;
	CButtonST	m_btnDelete;
	CButtonST	m_btnSave;
	CButtonST	m_btnLoad;
	CComboBox	m_listFileFolder;
	CButtonST	m_btnOK;
	CButtonST	m_btnCancel;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgVisionSetup)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgVisionSetup)
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT nIDEvent);
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnInputDevice();
	afx_msg void OnOutputDevice();
	afx_msg void OnMatch();
	afx_msg void OnGrab();
	afx_msg void OnLoad();
	afx_msg void OnSave();
	afx_msg void OnDelete();
	afx_msg void OnStop();
	afx_msg void OnLive();
	afx_msg void OnTest();
	afx_msg void OnClear();
	afx_msg void OnSetScope();
	afx_msg void OnSetDefault();
	afx_msg LRESULT OnPosInfo(WPARAM p, LPARAM l);
	afx_msg void OnClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGVISIONSETUP_H__8CFDF177_7162_4138_A8C5_A52A82A50B99__INCLUDED_)
