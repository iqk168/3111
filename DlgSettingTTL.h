#if !defined(AFX_DLGSETTINGTTL_H__E33A4B5F_5684_41B0_814B_65B18D95140C__INCLUDED_)
#define AFX_DLGSETTINGTTL_H__E33A4B5F_5684_41B0_814B_65B18D95140C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgSettingTTL.h : header file
//

#include "ColorBtn.h"
// GroupBox
#include "GroupControl.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgSettingTTL dialog

class CDlgSettingTTL : public CDialog
{
// Construction
public:
	CDlgSettingTTL(CWnd* pParent = NULL);   // standard constructor

	//
	tagTTLParameter	m_TTLPamera;

	//
	CString m_csTtlFile;
	void SetFile(CString csfile);

	//
	void LoadFile();
	void InitValue();

	//
	bool SaveTTLData();
	bool GetDataFromUI(tagTTLParameter &UIData);
	void SaveDataToFile(tagTTLParameter FileData);

	//
	CString ConvertIntToBin(int iMask);

	void ResetButton();
	void MInvalidate();

// Dialog Data
	//{{AFX_DATA(CDlgSettingTTL)
	enum { IDD = IDD_SETTING_TTL };
	CGroupControl	m_wndMaskGroup;
	CStatic		m_wndFile;
	CEdit		m_edtTimeout;
	CEdit		m_edtStartDelay;
	CEdit		m_edtSite4;
	CEdit		m_edtSite3;
	CEdit		m_edtSite2;
	CEdit		m_edtSite1;
	CColorBtn	m_btnEOT1;
	CColorBtn	m_btnEOT2;
	CColorBtn	m_btnReady1;
	CColorBtn	m_btnReady2;
	CColorBtn	m_btnLine;
	CColorBtn	m_btnBCD;
	CColorBtn	m_btnBinSignal1;
	CColorBtn	m_btnBinSignal2;
	CColorBtn	m_btnLevel;
	CColorBtn	m_btnPulse;
	CColorBtn	m_btnTester;
	CColorBtn	m_btnHandler;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgSettingTTL)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgSettingTTL)
	afx_msg void OnNote();
	virtual BOOL OnInitDialog();
	afx_msg void OnTtlFilename();
	afx_msg void OnEstatic();
	afx_msg void OnEot1();
	afx_msg void OnEot2();
	afx_msg void OnReady1();
	afx_msg void OnReady2();
	afx_msg void OnBin1();
	afx_msg void OnBin2();
	afx_msg void OnLevel1();
	afx_msg void OnLevel2();
	afx_msg void OnLine1();
	afx_msg void OnLine2();
	afx_msg void OnTtlpwr0();
	afx_msg void OnTtlpwr1();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGSETTINGTTL_H__E33A4B5F_5684_41B0_814B_65B18D95140C__INCLUDED_)
