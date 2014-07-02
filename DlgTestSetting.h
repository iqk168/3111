#if !defined(AFX_DLGTESTSETTING_H__224E94B8_589A_4BDE_B12E_EAFBD125D298__INCLUDED_)
#define AFX_DLGTESTSETTING_H__224E94B8_589A_4BDE_B12E_EAFBD125D298__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgTestSetting.h : header file
//

#include "DlgSettingGpib.h"
#include "DlgSettingRs232.h"
#include "DlgSettingTcp.h"
#include "DlgSettingTTL.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgTestSetting dialog

#include "ColorBtn.h"

class CDlgTestSetting : public CDialog
{
// Construction
public:
	CDlgTestSetting(CString csFile = "" ,CWnd* pParent = NULL);   // standard constructor

	void ButtonUpdataStatus();
	void InitPageControl();

	//
	void ChangeInterface(int page);

	//
	void UpdataInterfaceTypeButton();
	void GetButtonDistance(int &Width, int &Distance);

	//
	CString m_GPIBfile;
	CString m_Rs232file;
	CString m_Tcpfile;
	CString m_Ttlfile;

	//
	void InitValue();
	CString m_csProductionFile;

	//
	int LoadInterfaceType();
	void SaveInterfaceType();
	void SetInterfaceType(int iInterfaceType); // RS232, TCP, GPIB
	void SetDefaultButton( int iInterfaceType);

	//
	bool SaveData();


public:
	/////////////////////////////////////////////////////
	// 宣告 IF 頁面數量(Page)結構區
	struct tagDlgPage
	{
		CDlgSettingGpib					m_DlgGpib;
		CDlgSettingRs232				m_DlgRs232;
		CDlgSettingTcp					m_DlgTcp;
		CDlgSettingTTL					m_DlgTTL;
		
		TCITEM				m_Page; //儲存參數用
	} DlgPage;

// Dialog Data
	//{{AFX_DATA(CDlgTestSetting)
	enum { IDD = IDD_DLG_TEST_SETTING };

	CButton	m_Index2;
	CButton	m_Index1;
	CButtonST	m_btnOK;
	CButtonST	m_btnCancel;
	CColorBtn	m_btnRs232;
	CColorBtn	m_btnGbip;
	CColorBtn	m_btnTcpip;
	CColorBtn	m_btnTTL;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgTestSetting)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgTestSetting)
	virtual void OnCancel();
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnIRs232();
	afx_msg void OnITcp();
	afx_msg void OnIGpib();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnITtl();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGTESTSETTING_H__224E94B8_589A_4BDE_B12E_EAFBD125D298__INCLUDED_)
