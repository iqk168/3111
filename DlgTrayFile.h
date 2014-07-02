#if !defined(AFX_DLGTRAYFILE_H__2B18601B_BCC7_4DC4_97F9_9C390ABB9863__INCLUDED_)
#define AFX_DLGTRAYFILE_H__2B18601B_BCC7_4DC4_97F9_9C390ABB9863__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgTrayFile.h : header file
//

#include "ColorBtn.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgTrayFile dialog

class CDlgTrayFile : public CDialog
{
// Construction
public:
	CDlgTrayFile(CString m_csfile = "",
		CWnd* pParent = NULL);   // standard constructor

	bool m_fChange;		// It is for hearter setting change
	bool m_fSubChange;	// It is for Ambit setting change

	//
	void InitTrayFileUI();
	void InitTrayFileButton();
	void UpdataCurrentFile();
	void UpdataTrayICONButton();	

	//
	void CreateNewFile(CString csFile);
	void CeeateNewTesting( CString csFile );
	void CeeateNewMapping( CString csFile );
	// Interface
	void ResetNewFileInterface( CString csFile );
	void ResetInterfaceType( CString csFile );

	//
	void ResetTrayFileMappingAndInterface( CString csFile );
	void DeleteOtherFileForTrayFile( CString csFile );

	// 產生新的 Interface 檔案 ( Rs232, Tcp, Gpib, Ttl ) 預設值在這邊改...
	void CreateInterfacefile( CString csFile );
	void SaveDataToFile(CString csFileName, tagIfRs232Setting FileData);
	void SaveDataToFile(CString csFileName, tagIfTcpSetting FileData);
	void SaveDataToFile(CString csFileName, tagGPIBParameter FileData);
	void SaveDataToFile(CString csFileName, tagTTLParameter FileData);

// Dialog Data
	//{{AFX_DATA(CDlgTrayFile)
	enum { IDD = IDD_TRAY_FILE };
	
	CColorBtn	m_btnAmbient;
	CColorBtn	m_btnHeating;
	CColorBtn	m_btnATCMoudle;
	CColorBtn	m_btnTriTemperature;
	CColorBtn	m_btnPTCModule;

	CStatic	m_wndRowMM;
	CStatic	m_wndRow;
	CStatic	m_wndColumn;
	CStatic	m_wndColumnMM;
	CEdit	m_edtColumn;	
	CEdit	m_edtRow;
	CEdit	m_edtPlateRow;
	CEdit	m_edtPlateColumn;
	CButton	m_wndPreheater;
	CStatic	m_bmpPreheater;
	CEdit	m_edtPlateD;
	CEdit	m_edtPlateC;
	CEdit	m_edtPlateB;
	CEdit	m_edtPlateA;
	CEdit	m_edtD;
	CEdit	m_edtC;
	CEdit	m_edtB;
	CEdit	m_edtA;

	CButtonST	m_btnChangeKit;

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
	//{{AFX_VIRTUAL(CDlgTrayFile)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	void UpdateFileList();
	void NotModify();
	void LoadTraySpec();
	void SaveTraySpec();

	void SaveOffset();

	bool CheckTrayValue();	// if out of range, return false

	// File
	CString m_csFile;
	CString m_csBaseFile;

	// Tray
	tagTraySpec m_TraySpec;
	CString m_file;

	// Generated message map functions
	//{{AFX_MSG(CDlgTrayFile)
	afx_msg void OnDestroy();
	virtual BOOL OnInitDialog();
	afx_msg void OnClose();
	afx_msg void OnSetAsBaseFile();
	virtual void OnCancel();
	virtual void OnOK();
	afx_msg void OnModify();
	afx_msg void OnNotModify();
	afx_msg void OnDelete();
	afx_msg void OnAmbient();
	afx_msg void OnHeating();
	afx_msg void OnSave();
	afx_msg void OnSelchangeFileList();
	afx_msg void OnNew();
	afx_msg void OnChangeColumn();
	afx_msg void OnChangeRow();
	afx_msg void OnChangeA();
	afx_msg void OnChangeB();
	afx_msg void OnChangeC();
	afx_msg void OnChangeD();
	afx_msg void OnChangeColumn2();
	afx_msg void OnChangeRow2();
	afx_msg void OnChangeA2();
	afx_msg void OnChangeB2();
	afx_msg void OnChangeC2();
	afx_msg void OnChangeD2();
	afx_msg void OnChangeKit();
	afx_msg void OnAtcMoudle();
	afx_msg void OnTriTemperature();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnPtcModule();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGTRAYFILE_H__2B18601B_BCC7_4DC4_97F9_9C390ABB9863__INCLUDED_)
