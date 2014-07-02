#if !defined(AFX_DLGTEMPERATURECALIBRATION_H__DA92DB15_4AA4_478B_B905_AD500F3CF76A__INCLUDED_)
#define AFX_DLGTEMPERATURECALIBRATION_H__DA92DB15_4AA4_478B_B905_AD500F3CF76A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgTemperatureCalibration.h : header file
//
#include "ColorBtn.h"
/////////////////////////////////////////////////////////////////////////////
// CDlgTemperatureCalibration dialog

class CDlgTemperatureCalibration : public CDialog
{
// Construction
public:
	CDlgTemperatureCalibration(CWnd* pParent = NULL);   // standard constructor

	void InitValue();
	void SaveData();
	bool CheckValue();

	//
	void InitSync();
	void InitTips();
	void InitUI();

	//
	void InitController();

	//
	void UpdateDisplay();

	long m_WestID;
	CToolTipCtrl m_ToolTip;

	void SetSyncUI();
	void SetIOSyncUI();
	bool m_bEnableSync;

	double m_dReadPV;

	void CalibrationMeasureMent();
	void CalibrationSetSV();

	//
	void ChangePage();

// Dialog Data
	//{{AFX_DATA(CDlgTemperatureCalibration)
	enum { IDD = IDD_DLG_TEMPERATURE_CALIBRATION };
	CColorBtn	m_btnEnableSync;
	CButton	m_btnSyncSite;
	CComboBox	m_cbxControllerSel;
	CEdit	m_wndMeasureTemperature;
	CColorFontStatic	m_wndDisplayTemperature;
	CColorBtn	m_btnHeaterOn;
	CButtonST	m_btnSave;
	double	m_dSetPoint;
	double	m_dSoakTime;
	double	m_dStableTime;
	double	m_dTolerance;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgTemperatureCalibration)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgTemperatureCalibration)
	virtual BOOL OnInitDialog();
	afx_msg void OnSave();
	afx_msg void OnHeatOn();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnChangePSetpoint();
	afx_msg void OnChangePSoakTime();
	afx_msg void OnChangePStableTime();
	afx_msg void OnChangePTolerance();
	afx_msg void OnEnableSync();
	afx_msg void OnSSite1();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGTEMPERATURECALIBRATION_H__DA92DB15_4AA4_478B_B905_AD500F3CF76A__INCLUDED_)
