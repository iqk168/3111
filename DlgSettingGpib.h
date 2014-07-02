#if !defined(AFX_DLGSETTINGGPIB_H__8146CADA_27F8_4D77_960D_BA8DA382A5FD__INCLUDED_)
#define AFX_DLGSETTINGGPIB_H__8146CADA_27F8_4D77_960D_BA8DA382A5FD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgSettingGpib.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgSettingGpib dialog

class CDlgSettingGpib : public CDialog
{
// Construction
public:
	CDlgSettingGpib(CWnd* pParent = NULL);   // standard constructor

	//
	void InitUI();

	tagGPIBParameter m_GPIBParam;

	//
	CString m_csGpibFile;
	void SetFile(CString csfile);

	//
	void LoadFile();
	void InitValue();

	//
	bool SaveGPIBData();
	bool GetDataFromUI(tagGPIBParameter &UIData);
	void SaveDataToFile(tagGPIBParameter FileData);

// Dialog Data
	//{{AFX_DATA(CDlgSettingGpib)
	enum { IDD = IDD_SETTING_GPIB };
	CComboBox	m_cbSite;
	CStatic	m_wndFile;
	CComboBox	m_cbAddr;
	CComboBox	m_cbBinBase;
	CComboBox	m_cbGpib;
	CEdit	m_edtDelay;
	CEdit	m_edtTimeout;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgSettingGpib)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgSettingGpib)
	virtual BOOL OnInitDialog();
	afx_msg void OnNote();
	afx_msg void OnFile();
	afx_msg void OnEStatic();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGSETTINGGPIB_H__8146CADA_27F8_4D77_960D_BA8DA382A5FD__INCLUDED_)
