#if !defined(AFX_DLGARMLOGICIMAGE_H__0013A74C_3C46_47CA_9DD9_51EC4F45F7CD__INCLUDED_)
#define AFX_DLGARMLOGICIMAGE_H__0013A74C_3C46_47CA_9DD9_51EC4F45F7CD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgArmLogICImage.h : header file
//

#include "ViewIC.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgArmLogICImage dialog

class CDlgArmLogICImage : public CDialog
{
// Construction
public:
	CDlgArmLogICImage(CWnd* pParent = NULL);   // standard constructor

	void InitValue();
	void UpdataFolderStatus();
	CString GetFolderName();
	CString GetFileName();
	void UpdataFileStatus(CString csFolderName);
	void DeleteImageFolder(CString csFolderName);
	void SetFolderValue(int iIndex);

	CArray<CString, CString> m_Folder;
	CArray<CString, CString> m_Files;

public:
	void InitImageValue();
	CViewIC *pViewICImage;
	void LoadImage();

// Dialog Data
	//{{AFX_DATA(CDlgArmLogICImage)
	enum { IDD = IDD_DLG_ARM_LOGIC };
	CStatic	m_wndImage;
	CStatic	m_wndLastFolder;
	CStatic	m_wndlistFileCounter;
	CListBox	m_listFolderFileStatus;
	CStatic	m_wndlistFolderCounter;
	CListBox	m_listFolderStatus;
	CButtonST	m_btnCancel;
	CButtonST	m_btnOK;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgArmLogICImage)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgArmLogICImage)
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnStaticFloderList();
	virtual BOOL OnInitDialog();
	afx_msg void OnStaticFileList();
	afx_msg void OnSelchangeListFolder();
	afx_msg void OnDblclkListFile();
	afx_msg void OnDblclkListFolder();
	afx_msg void OnSelchangeListFile();
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGARMLOGICIMAGE_H__0013A74C_3C46_47CA_9DD9_51EC4F45F7CD__INCLUDED_)
