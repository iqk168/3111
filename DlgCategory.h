#if !defined(AFX_DLGCATEGORY_H__0F36ADB3_A29C_41DC_8265_470445EEB5C1__INCLUDED_)
#define AFX_DLGCATEGORY_H__0F36ADB3_A29C_41DC_8265_470445EEB5C1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgCategory.h : header file
//

#include "ColorListCtrl.h"
#include "ColorPickerCB.h"
		  
/////////////////////////////////////////////////////////////////////////////
// CDlgCategory dialog

class CDlgCategory : public CDialog
{
// Construction
public:
	CDlgCategory(CWnd* pParent = NULL);   // standard constructor

	//
	bool m_fChange;

	//
	CArray <tagBinMapping, tagBinMapping> BinMap; // Bin Use

	//
	typedef struct tagCatoregyFileItem 
	{
		int		item;
		CString software;
		CString code;
		CString description;
		bool	pass;
		int		color;
		int		hardware;
	} tagCatoregyFileItem;

	//
	CArray <tagCatoregyFileItem, tagCatoregyFileItem> m_Source;

	//
	void InitColorCombox();
	void InitPFCombox();
	void InitHWCombox();

	//
	void InitValue();
	void ShowTitle();
	void ShowData();
	void Style();

	//
	void GetColumnDATA(int nItem );
	void SetDefaultColumn(int col);

	//
	void SetColumn(int col );

	//
	void ResetUIForAdd();
	void ResetUIForDelete();

	//
	void RetUI(int Item);

	//
	bool CheckFieldValid();
	int  BinAddData();
	int BinDelData();
	void BinSaveData();
	int BinUpData();
	int BinDownData();

	//
	void SaveData();

	bool CheckCodeVaild();

public:
	CToolTipCtrl m_ToolTip;
	void InitTips();

// Dialog Data
	//{{AFX_DATA(CDlgCategory)
	enum { IDD = IDD_DLG_CATOREGY_SETUP };
	CComboBox	m_wndPF;
	CComboBox	m_wndHw;
	CColorPickerCB	m_wndColor;
	CEdit				m_wndCode;
	CColorFontStatic	m_wndColorBk;
	CEdit				m_wndDescription;
	CEdit				m_wndSWNumber;
	CEdit				m_wndItem;
	CStatic				m_wndFile;
	CColorListCtrl		m_listData;
	CButtonST			m_btnCancel;
	CButtonST			m_btnOK;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgCategory)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgCategory)
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnGetdispinfoData(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnFile();
	afx_msg void OnClickData(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnFSet();
	afx_msg void OnFAdd();
	afx_msg void OnFDel();
	afx_msg void OnFUp();
	afx_msg void OnFDown();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGCATEGORY_H__0F36ADB3_A29C_41DC_8265_470445EEB5C1__INCLUDED_)
