#if !defined(AFX_DLGBINCOLOR_H__84423364_429B_405C_A4CD_CA76A3943930__INCLUDED_)
#define AFX_DLGBINCOLOR_H__84423364_429B_405C_A4CD_CA76A3943930__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgBinColor.h : header file
//

#include "ColorListCtrl.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgBinColor dialog

class CDlgBinColor : public CDialog
{
// Construction
public:
	CDlgBinColor(CWnd* pParent = NULL);   // standard constructor

	//
	typedef struct tagBinColorFileItem 
	{
		int		item;
		int		color;
	} tagBinColorFileItem;

	//
	CArray <tagBinColorFileItem, tagBinColorFileItem> m_Source;

	CArray <tagBinColor, tagBinColor> m_BinColorItem;

	//
	void InitValue();
	void ShowTitle();
	void ShowData();
	void Style();

	//
	void GetColumnDATA(int nItem);

	//
	void InitColorSilder();
	int GetColorSilderValue();
	void SetColorSilderValue(int iColor);

	//
	void ColorAdd();
	void ColorSave();
	void ColorDel();

	//
	void SaveData();

	void ParseColor(int Color, int &R, int &G, int &B);

	//
	int m_iItem;

// Dialog Data
	//{{AFX_DATA(CDlgBinColor)
	enum { IDD = IDD_DLG_BIN_COLOR };
	CColorFontStatic	m_wndColor;
	CEdit	m_wndB;
	CEdit	m_wndG;
	CEdit	m_wndR;
	CSliderCtrl	m_SilB;
	CSliderCtrl	m_SilG;
	CSliderCtrl	m_SilR;
	CColorListCtrl	m_listData;
	CButtonST	m_btnOK;
	CButtonST	m_btnCancel;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgBinColor)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgBinColor)
	virtual void OnOK();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnGetdispinfoData(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnClickData(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnOutofmemorySliderR(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnOutofmemorySliderG(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnOutofmemorySliderB(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnCAdd();
	afx_msg void OnCSave();
	afx_msg void OnCDel();
	afx_msg void OnColor();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGBINCOLOR_H__84423364_429B_405C_A4CD_CA76A3943930__INCLUDED_)
