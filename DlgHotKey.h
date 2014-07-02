#if !defined(AFX_DLGHOTKEY_H__540D0D4D_FF63_4FA8_B97E_1538217D1B8F__INCLUDED_)
#define AFX_DLGHOTKEY_H__540D0D4D_FF63_4FA8_B97E_1538217D1B8F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgHotKey.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgHotKey dialog

class CDlgHotKey : public CDialog
{
// Construction
public:
	CDlgHotKey(CWnd* pParent = NULL);   // standard constructor

	//
	typedef struct tagHotKeyItem 
	{
		long	item;
		CString cshotkey;
		CString cshotkeydesc;

	} tagHotKeyItem;	

	//
	CArray <tagHotKeyItem, tagHotKeyItem> m_Source;

	struct m_HotKeyData{
		CArray <CString, CString> csHotKey;
		CArray <CString, CString> csHotKeyDesc;
		CArray <CString, CString> csHotKeyNote;
	} m_HotKeyData;

	//
	void Style();
	void ShowTitle();
	void InsertData();
	void ShowData();


// Dialog Data
	//{{AFX_DATA(CDlgHotKey)
	enum { IDD = IDD_DLG_HOT_KEY };
	CButtonST	m_btnCancel;
	CButtonST	m_btnOK;
	CListCtrl	m_listHotKey;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgHotKey)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgHotKey)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnGetdispinfoData(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGHOTKEY_H__540D0D4D_FF63_4FA8_B97E_1538217D1B8F__INCLUDED_)
