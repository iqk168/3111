#if !defined(AFX_DLGBINMAPPING_H__F0D768BA_C9DD_4E9C_9447_451A1294B362__INCLUDED_)
#define AFX_DLGBINMAPPING_H__F0D768BA_C9DD_4E9C_9447_451A1294B362__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgBinMapping.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgBinMapping dialog

class CDlgBinMapping : public CDialog
{
// Construction
public:
	CDlgBinMapping(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgBinMapping)
	enum { IDD = IDD_DLG_BIN_MAPPING_SETUP };
	
	CStatic	m_wndFile;
	CListBox	m_bxFile;
	CListCtrl	m_listBin;
	
	CStatic		m_wndMappingBase;
	CButtonST	m_btnDelete;
	CButtonST	m_btnNew;
	CButtonST	m_btnSetBase;

	CButtonST	m_btnModify;
	CButtonST	m_btnCancel;
	CButtonST	m_btnOK;
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgBinMapping)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	void ResetMappingList();
	void UpdateFileList();
	
	void LoadBinMapping(CString file);

	CArray <tagBinMapping, tagBinMapping> m_BinMap;
	// Generated message map functions
	//{{AFX_MSG(CDlgBinMapping)
	afx_msg void OnDestroy();
	afx_msg void OnClose();
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnModifyParameter();
	afx_msg void OnSetAsBaseFile();
	afx_msg void OnNew();
	afx_msg void OnDelete();

	afx_msg void OnSelect();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGBINMAPPING_H__F0D768BA_C9DD_4E9C_9447_451A1294B362__INCLUDED_)
