#if !defined(AFX_DLGTRAYDEF_H__0E18CE27_AC1F_4DCD_A802_EAC31B00F19A__INCLUDED_)
#define AFX_DLGTRAYDEF_H__0E18CE27_AC1F_4DCD_A802_EAC31B00F19A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgTrayDef.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgTrayDef dialog

class CDlgTrayDef : public CDialog
{
// Construction
public:
	CDlgTrayDef(bool bUser = false, CWnd* pParent = NULL);   // standard constructor

public:
	bool m_bUser;

	void InitTrayFileDef();
	void InitTrayFileColor();
	void InitControl();
	void SaveData();

	tagTrayFileDefColor m_TrayFileDefColor;

public:
	void ParseColor(int Color, int &R, int &G, int &B);
	int GetColorSilderValue();
	void SetColorSilderValue(int iColor);
	void InitColorSilder();

	void ChangeColorSilder(COLORREF color);

// Dialog Data
	//{{AFX_DATA(CDlgTrayDef)
	enum { IDD = IDD_DLG_TRAY_DEF_COLOR };
	CEdit				m_wndB;
	CEdit				m_wndG;
	CEdit				m_wndR;
	CSliderCtrl			m_SilB;
	CSliderCtrl			m_SilG;
	CSliderCtrl			m_SilR;
	//
	CColorFontStatic	m_wndETRI;
	CColorFontStatic	m_wndEPTC;
	CColorFontStatic	m_wndEHeater;
	CColorFontStatic	m_wneEATC;
	CColorFontStatic	m_wndEAmbient;
	CComboBox			m_cbxTrayFileDef;
	CButtonST			m_btnOK;
	CButtonST			m_btnCancel;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgTrayDef)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgTrayDef)
	virtual void OnOK();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeTrayFileDef();
	afx_msg void OnOutofmemorySliderR(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnOutofmemorySliderG(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnOutofmemorySliderB(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGTRAYDEF_H__0E18CE27_AC1F_4DCD_A802_EAC31B00F19A__INCLUDED_)
