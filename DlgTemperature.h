#if !defined(AFX_DLGTEMPERATURE_H__DB483208_0751_4F06_97F2_B875B309C0B7__INCLUDED_)
#define AFX_DLGTEMPERATURE_H__DB483208_0751_4F06_97F2_B875B309C0B7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgTemperature.h : header file
//
#include "DlgTemperatureCalibration.h"
#include "DlgTemperatureLookupTable.h"
#include "DlgTemperatureTool.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgTemperature dialog

class CDlgTemperature : public CDialog
{
// Construction
public:
	CDlgTemperature(CWnd* pParent = NULL);   // standard constructor

public:
	void InitTabControl();

	/////////////////////////////////////////////////////
	// 宣告 Temperature 頁面數量(Page)結構區
	struct tagDlgPage
	{
		CDlgTemperatureCalibration		m_DlgTemperatureCalibration;
		CDlgTemperatureLookupTable		m_DlgTemperatureLookupTable;
		CDlgTemperatureTool				m_DlgTemperatureTool;
		TCITEM				m_Page; //儲存參數用
	} DlgPage;

	void ChangeTabPage();

// Dialog Data
	//{{AFX_DATA(CDlgTemperature)
	enum { IDD = IDD_DLG_TEMPERATURE };
	CTabCtrl	m_tabTemperature;
	CButtonST	m_btnOK;
	CButtonST	m_btnCancel;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgTemperature)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
	// Generated message map functions
	//{{AFX_MSG(CDlgTemperature)
	virtual void OnOK();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnSelchangeTabTemperature(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGTEMPERATURE_H__DB483208_0751_4F06_97F2_B875B309C0B7__INCLUDED_)
