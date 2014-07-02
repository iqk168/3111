#if !defined(AFX_PAGERUN_H__FD97B4A4_0263_47C0_9F0D_AB2A292C21B7__INCLUDED_)
#define AFX_PAGERUN_H__FD97B4A4_0263_47C0_9F0D_AB2A292C21B7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PageRun.h : header file
// 

#include "ContinueFailCtrl.h" // Progress.
#include "YieldControl.h"
#include "ColorFontStatic.h"  // Text Output.
#include "ColorListCtrl.h"	
#include "Led.h"

//
// GroupBox
#include "GroupControl.h"

/////////////////////////////////////////////////////////////////////////////
// CPageRun dialog

class CPageRun : public CDialog
{
// Construction
public:
	CPageRun(CWnd* pParent = NULL);   // standard constructor
	//
	bool m_bRemoteFlash;

	//
	void UpdateUPHCycle();
	void UpdateSiteCounter();
	void UpdateSingleSiteCounter(int iSite);
	void UpdateTSTemperature();
	void UpdateHeaterStatus();
	void UpdateHeaterStableStatus();
	void UpdateHeaterSoakTimeStatus();

	void UpdateColorCatoregyInformation();
	void UpdateYieldContactModeInformation();
	void UpdateHandlerRunModeStatusInformation();
	void UpdateAutoSkipStatusInformation();
	void UpdataTsVaccOffStatusInformation();
	void UpdateYieldSettingInformation();
	void UpdateLotInformation();
	void UpdateRotatorStatus();
	void UpdateCCDPin1Status();
	void UpdataCCDSocketStatus();
	void UpdateCatoregyStatus();
	void UpdateSetting();
	void UpdateYieldSetting();
	void UpdateRepeatTrayDetailStatus();
	void UpdataLot();
	void UpdataICONButton();
	void UpdataRepeatTrayStatus();
	void UpdataHandlerStatusInfo();
	void UpdataNowTemperature();
	void UpdataRepeatInformation();
	void UpdataRepeatMation();
	void UpdataRemoteModeStatus();

	//
	double GetOutputYieldValue(CString csCode);

	CToolTipCtrl m_ToolTip;
	// It is for information to User

	// Init
	void InitUI();
	void InitTips();

	void InitStatus();
	void InitOutput();
	void InitYield();

	void InitOutputColor();

	//
	void InitColorCatoregyFormat();

	long lOutputColor;
	void ReDrawOutputColor();
	void ReDrawTemperature();
	void ReDrawHeaterModule();
	void ReDrawHeaterOption();
	void ReDrawTorqueStatus();
	void ReDrawRepeatTrayStatus();
	void ReDrawRepeatTrayFileBkColor();
	void ReDrawHandlerStatus();
	void ReDrawNowTemperature();
	void ReDrawRepeatTrayICStatus();
	void ReDrawTsCounterStatus();

public:

	//
	typedef struct tagCatoregyRunPageItem 
	{
		int		item;
		CString software;
		CString code;
		int pf;
	} tagCatoregyRunPageItem;

	//
	CArray <tagBinMapping, tagBinMapping> RunBinMap; // Bin Use
	CArray <tagCatoregyRunPageItem, tagCatoregyRunPageItem> m_Source;


// Dialog Data
	//{{AFX_DATA(CPageRun)
	enum { IDD = IDD_PAGE_RUN };

	//
	CColorListCtrl		m_listData;
	//
	CColorFontStatic	m_wndOutput[_Output_Stack_No];
	CListBox			m_wndCategory[_Output_Stack_No];
	CColorFontStatic	m_wndOutputCount[_Output_Stack_No];
	//
	CColorFontStatic	m_wndUPH;
	CColorFontStatic	m_wndTotal;
	CColorFontStatic	m_wndSiteCount[_Site_Count];
	CColorFontStatic	m_wndYield;
	CContinueFailCtrl	m_ContinueFail;
	//
	CColorFontStatic	m_wndTesting;
	CButtonST			m_btnContactMode;
	CButtonST			m_btnCCD;
	CButtonST			m_btnCCDSocket;
	//
	CGroupControl		m_HeaterModuleGrp;
	//
	CColorFontStatic	m_wndShuttleTemp;
	CColorFontStatic	m_wndTestSiteTemp;
	CColorFontStatic	m_wndTestTime;

	// Test Site Counter ­p¼Æ
	CStatic				m_wndContactCounterr;
	CYieldControl		m_YieldControl;
	CButtonST			m_btnTestSiteVacc;
	CButtonST			m_btnRotatorStstus;
	CButtonST			m_btnAutoSkip;
	CButtonST			m_btnLotInformation;
	CButtonST			m_btnLotDone;
	CButtonST			m_btnTrayMap;
	CButtonST			m_btnClearCount;
	CButtonST			m_btnIOMonitor;
	CButtonST			m_btnYieldCTRL;
	CButtonST			m_btnEvent;
	CButtonST			m_btnRepeatTrayInOutCtrl;
	CButtonST			m_btnVisualPanel;

	//
	CStatic				m_wndContinueFail;
	CStatic				m_wndYieldLimit;
	CStatic				m_wndRetestTimes;
	//
	CStatic				m_wndHeaterStableTime;
	CStatic				m_wndHeaterSoakTine;
	CStatic				m_wndHeaterDisSoakTine;
	CStatic				m_wndHeaterSetPoint;
	CStatic				m_wndHeaterStableRemain;
	//
	CLed				m_ledRetest;
	CLed				m_ledContinueFail;
	CLed				m_ledYieldControl;
	CLed				m_ledHeater;
	CLed				m_ledHeaterStable;
	//
	CColorFontStatic	m_wndFile;
	CColorFontStatic	m_wndRunStatus;
	CColorFontStatic	m_wndRunMode;
	//
	CColorFontStatic	m_wndTempTS;
	//
	CColorFontStatic	m_wndTorqueStatus;
	//
	CColorFontStatic	m_wndRepeatTrayStatus;
	//
	CColorFontStatic	m_wndHandlerStatus;
	//
	CColorFontStatic	m_wndNowTemperature;
	CColorFontStatic	m_wndNowMoation;
	CColorFontStatic	m_wndCurrentRepeatTrayStatus;


	//}}AFX_DATA

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPageRun)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPageRun)
	virtual BOOL OnInitDialog();
	afx_msg void OnGetdispinfoData(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnTestSiteVaccOff();
	afx_msg void OnTrayAutoSkip();
	afx_msg void OnYieldCtrl();
	afx_msg void OnIoMontior();
	afx_msg void OnEventLog();
	afx_msg void OnClearCount();
	afx_msg void OnTrayMap();
	afx_msg void OnLotDone();
	afx_msg void OnLotInformation();
	afx_msg void OnContactMode();
	afx_msg void OnRepeatTrayInOutCtrl();
	afx_msg void OnVisualPanel();
	afx_msg void OnOutputYield();
	afx_msg void OnRunMode();
	afx_msg void OnRepeatTrayTemper();
	afx_msg void OnFileDeviceSetup();
	afx_msg void OnFileRepeatTraySetup();
	afx_msg void OnTsCounter();

	afx_msg void OnCCD();
	afx_msg LRESULT OnHeaterOn(WPARAM p, LPARAM l);
	afx_msg LRESULT OnUpdataTsCounter(WPARAM p, LPARAM l);

	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PAGERUN_H__FD97B4A4_0263_47C0_9F0D_AB2A292C21B7__INCLUDED_)
