#if !defined(AFX_DLGTRAYFILENOHEATER_H__5E03BD94_68A8_4627_9B03_4785E3FB303E__INCLUDED_)
#define AFX_DLGTRAYFILENOHEATER_H__5E03BD94_68A8_4627_9B03_4785E3FB303E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgTrayFileNoHeater.h : header file
//

#include "ColorBtn.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgTrayFileNoHeater dialog

class CDlgTrayFileNoHeater : public CDialog
{
// Construction
public:
	CDlgTrayFileNoHeater(CString m_csfile = "",
		CWnd* pParent = NULL);   // standard constructor

	bool m_fChange;	// It is for Ambit setting change

	//
	void InitTrayFileUI();
	void InitTrayFileButton();
	void UpdataCurrentFile();
	void UpdataTrayICONButton();	

	//
	void CreateNewFile(CString csFile);
	void CeeateNewTesting( CString csFile );
	void CeeateNewMapping( CString csFile );

	//
	void ResetNewFileInterface( CString csFile );
	void ResetInterfaceType( CString csFile );

	// 把  TrayFile 裡面的 Mapping, Testsetting 改成新的
	void ResetTrayFileMappingAndInterface( CString csFile );
	void DeleteOtherFileForTrayFile( CString csFile );

	// 產生新的 Interface 檔案 ( Rs232, Tcp, Gpib, Ttl ) 預設值在這邊改...
	void CreateInterfacefile( CString csFile );
	void SaveDataToFile(CString csFileName, tagIfRs232Setting FileData);
	void SaveDataToFile(CString csFileName, tagIfTcpSetting FileData);
	void SaveDataToFile(CString csFileName, tagGPIBParameter FileData);
	void SaveDataToFile(CString csFileName, tagTTLParameter FileData);
	void DeleteInterfaceForTrayFile( CString csFile );

public:

// Dialog Data
	//{{AFX_DATA(CDlgTrayFileNoHeater)
	enum { IDD = IDD_TRAY_FILE_NO_HEATER };
	CButtonST	m_btnChipTray;
	CColorBtn	m_btnThickTrayMode;
	CColorBtn	m_btnHeater;
	CButtonST	m_btnChangeKit;
	CColorBtn	m_btnPTCModule;
	CColorBtn	m_btnAmbient;
	CColorBtn	m_btnATCMoudle;
	CColorBtn	m_btnTriTemperature;
	CColorBtn	m_btnRemoteModule;

	CEdit	m_edtColumn;	
	CEdit	m_edtRow;
	CEdit	m_edtD;
	CEdit	m_edtC;
	CEdit	m_edtB;
	CEdit	m_edtA;
	CButtonST	m_btnModifyCancel;
	CButtonST	m_btnSetBase;
	CButtonST	m_btnModify;
	CButtonST	m_btnSave;
	CButtonST	m_btnNew;
	CButtonST	m_btnOK;
	CButtonST	m_btnDelete;
	CButtonST	m_btnCancel;
	CStatic	m_wndBaseFile;
	CComboBox	m_cbxFileList;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgTrayFileNoHeater)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void UpdateFileList();
	void NotModify();
	void SaveTraySpec();
	void LoadTraySpec();
	void SaveOffset();
	void ThickTray();

	// File
	CString m_csFile;
	CString m_csBaseFile;

	// Tray
	tagTraySpec m_TraySpec;
	CString m_file;

	// Generated message map functions
	//{{AFX_MSG(CDlgTrayFileNoHeater)
	afx_msg void OnDestroy();
	virtual BOOL OnInitDialog();
	afx_msg void OnClose();
	afx_msg void OnSelchangeFileList();
	virtual void OnCancel();
	virtual void OnOK();
	afx_msg void OnSetAsBaseFile();
	afx_msg void OnModify();
	afx_msg void OnNotModify();
	afx_msg void OnDelete();
	afx_msg void OnNew();
	afx_msg void OnSave();
	afx_msg void OnAmbient();
	afx_msg void OnHeater();
	afx_msg void OnChangeColumn();
	afx_msg void OnChangeA();
	afx_msg void OnChangeRow();
	afx_msg void OnChangeC();
	afx_msg void OnChangeB();
	afx_msg void OnChangeD();
	afx_msg void OnChangeKit();
	afx_msg void OnAtcMoudle();
	afx_msg void OnTriTemperature();
	afx_msg void OnThickTrayMode();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnChipTray();
	afx_msg void OnPtcModule();
	afx_msg void OnRemote();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGTRAYFILENOHEATER_H__5E03BD94_68A8_4627_9B03_4785E3FB303E__INCLUDED_)
