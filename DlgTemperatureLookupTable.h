#if !defined(AFX_DLGTEMPERATURELOOKUPTABLE_H__DB778BE3_D2F5_4729_AACF_763F7483D5DD__INCLUDED_)
#define AFX_DLGTEMPERATURELOOKUPTABLE_H__DB778BE3_D2F5_4729_AACF_763F7483D5DD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgTemperatureLookupTable.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgTemperatureLookupTable dialog

class CDlgTemperatureLookupTable : public CDialog
{
// Construction
public:
	CDlgTemperatureLookupTable(CWnd* pParent = NULL);   // standard constructor

	void InitController();
	void Style();
	void InitTips();
	CToolTipCtrl m_ToolTip;

	//
	void InitValue();
	long m_lID;

	//
	//
	void ShowTitle();
	void ShowData(int iDeviceID);

	//
	typedef struct tagLoockupTableItem 
	{
		long	item;
		double	temperature;
		double  offset;
	} tagLoockupTableItem;

	//
	CArray <tagLoockupTableItem, tagLoockupTableItem> m_Source;

	void DeleteData(CString Prot, CString Value);
	void DeleteDataAll(CString Prot);

	void ChangePage();

// Dialog Data
	//{{AFX_DATA(CDlgTemperatureLookupTable)
	enum { IDD = IDD_DLG_TEMPERATURE_LOOKUP };
	CStatic	m_wndModifyData;
	CComboBox	m_cbxController;
	CListCtrl	m_listData;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgTemperatureLookupTable)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgTemperatureLookupTable)
	virtual BOOL OnInitDialog();
	afx_msg void OnGetdispinfoData(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnRclickList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnLstDelete();
	afx_msg void OnLstDeleteAll();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGTEMPERATURELOOKUPTABLE_H__DB778BE3_D2F5_4729_AACF_763F7483D5DD__INCLUDED_)
