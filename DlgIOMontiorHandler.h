#if !defined(AFX_DLGIOMONTIORHANDLER_H__37C4347D_2DF7_47BA_A3BF_B0810BB48881__INCLUDED_)
#define AFX_DLGIOMONTIORHANDLER_H__37C4347D_2DF7_47BA_A3BF_B0810BB48881__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgIOMontiorHandler.h : header file
//

// GroupBox
#include "GroupControl.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgIOMontiorHandler dialog

class CDlgIOMontiorHandler : public CDialog
{
// Construction
public:
	CDlgIOMontiorHandler(CWnd* pParent = NULL);   // standard constructor

	CToolTipCtrl m_ToolTip;

	void InitLed();
	void InitTips();
	void IOQuery();

	//
	void ReDrawUI();

	//
	bool m_bOnlyShow;
	void SetOnlyShow(bool bOnlyShow);

	void QueryCount();

// Dialog Data
	//{{AFX_DATA(CDlgIOMontiorHandler)
	enum { IDD = IDD_DLG_IOMONITOR_HANDLER };
	CLed	m_ledTSATX;
	CLed	m_ledTSBlowGo;
	CLed	m_ledTester;
	CLed	m_ledTSSkipPress;
	CLed	m_ledTSSkipOn;
	CLed	m_ledHeater;
	CLed	m_ledShuttleJam;
	CLed	m_ledShuttlepLmt;
	CLed	m_ledShuttlenLmt;
	CLed	m_ledShuttle;
	CLed	m_ledTSBlow;
	CLed	m_ledTSVaccSensor;
	CLed	m_ledTSVacc;
	CStatic	m_wndDebugCount;
	CLed	m_ledSystemEmg;
	CLed	m_ledSystemDoor;
	CLed	m_ledSystemION;
	CLed	m_ledSystemAirSource;
	CGroupControl	m_wndRotatorGroup;
	CLed	m_ledRotatorMissing;
	CLed	m_ledRotatorJam;
	CLed	m_ledRotatorNLmt;
	CLed	m_ledRotatorPLmt;
	CLed	m_ledRotatorRotate;
	CLed	m_ledTrayOutput;
	CLed	m_ledTrayInput;
	CLed	m_ledZBlow;
	CLed	m_ledZVacc;
	CLed	m_ledZVaccSensor;
	CLed	m_ledTowerYellow;
	CLed	m_ledTowerRed;
	CLed	m_ledTowerGreen;
	CLed	m_ledTowerBuzzer;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgIOMontiorHandler)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgIOMontiorHandler)
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnDestroy();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnLedZVacc();
	afx_msg void OnLedZBlow();
	afx_msg void OnLedTszSet();
	afx_msg void OnLedTowerRed();
	afx_msg void OnLedTowerYellow();
	afx_msg void OnLedTowerGreen();
	afx_msg void OnLedTowerBuzzer();
	afx_msg void OnLedRotate();
	afx_msg void OnERotatorGrp();
	afx_msg void OnDe();
	afx_msg void OnLedHeater();
	afx_msg void OnLedTsSkipPress();
	afx_msg void OnLedTsZVacc();
	afx_msg void OnLedTsZBlow();
	afx_msg void OnLedTsSkipOn();
	afx_msg void OnLedTester();
	afx_msg void OnLedShuttle();
	afx_msg void OnLedTsZBlowGo();
	afx_msg void OnLedTsAtx();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGIOMONTIORHANDLER_H__37C4347D_2DF7_47BA_A3BF_B0810BB48881__INCLUDED_)
