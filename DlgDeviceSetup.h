#if !defined(AFX_DLGDEVICESETUP_H__9E5B6CF9_9AC7_451E_8437_CBE3275E5B61__INCLUDED_)
#define AFX_DLGDEVICESETUP_H__9E5B6CF9_9AC7_451E_8437_CBE3275E5B61__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgDeviceSetup.h : header file
//

// GroupBox
#include "GroupControl.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgDeviceSetup dialog

class CDlgDeviceSetup : public CDialog
{
// Construction
public:
	CDlgDeviceSetup(CWnd* pParent = NULL);   // standard constructor

	int m_TestType;
	void LoadTrayFile(CString csFile);
	
	//
	void SaveTrayVision(CString csVisiionPattern);
	void SaveTrayVision(CString csTrayFile, CString csVisiionPattern);
	void LoadTrayVision(CString &csVisiionPattern);
	void LoadTrayVision(CString csTrayFile, CString &csVisiionPattern);

	//

	//
	void ReDrawUI();

	//
	bool m_bCCDSocketEnable;

	//
	void LockUIForCCDPin1();
	void LockUIForCCDSocket();

	//
	void InitLastTrayFile();

// Dialog Data
	//{{AFX_DATA(CDlgDeviceSetup)
	enum { IDD = IDD_DEVICE_SETUP };
	CButtonST	m_btnLastTrayFile;
	CStatic	m_wndStaticSocketCCDFile;
	CStatic	m_wndStaticCCDFile;
	CGroupControl	m_wndCCDGroup;
	CButtonST	m_btnModify;
	CComboBox	m_cbxCCDSocketSettingFileList;
	CComboBox	m_cbxCCDSettingFileList;
	CComboBox	m_cbxFileList;
	CComboBox	m_cbxMappingFileList;
	CComboBox	m_cbxTestSettingFileList;
	CButtonST	m_btnCancel;
	CButtonST	m_btnOK;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgDeviceSetup)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation

protected:

	void UpdateTrayFileList();
	void UpdateBinFileList();
	void UpdateTestSettingFileList();
	void UpdataCurrentFile();
	void UpdataCurrentFileCCD();
	
	CString m_Mapping;
	CString m_Testing;
	CString m_Vision;
	void UpdataTrayMapping();

	// CCD Group
	void UpdateCCDSettingFileList();
	void UpdateCCDSocketSettingFileList();

protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgDeviceSetup)
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnOpenTrayFile();
	afx_msg void OnOpenCategory();
	afx_msg void OnOpenTestSetting();
	afx_msg void OnModifyParameter();
	afx_msg void OnClose();
	afx_msg void OnSelchangeTrayFile();
	afx_msg void OnSelendokTrayFile();
	afx_msg void OnEditupdateTrayFile();
	afx_msg void OnDropdownTrayFile();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnLastTray();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGDEVICESETUP_H__9E5B6CF9_9AC7_451E_8437_CBE3275E5B61__INCLUDED_)
