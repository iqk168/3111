#if !defined(AFX_DLGMOTORMONTIOR_H__8D2CFC92_FABF_480F_ACB0_7E73520084C6__INCLUDED_)
#define AFX_DLGMOTORMONTIOR_H__8D2CFC92_FABF_480F_ACB0_7E73520084C6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgMotorMontior.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgMotorMontior dialog

#include "BtnST.h"
#include "ColorBtn.h"

class CDlgMotorMontior : public CDialog
{
// Construction
public:
	CDlgMotorMontior(bool Mode = false, bool Show = false, bool Operator = false,
		CWnd* pParent = NULL);   // standard constructor

	void QueryIO();

	void InitLed();
	void EnableUI();
	void OnSelect();
	
	bool m_fChange;

	tagMotorParam *Motor;

	bool m_Mode;		// if SuperUser. We will enable Motor parameter Or We set it to true.
	bool m_Show;		// if SuperUser. We will show Motor parameter. Or We set it to true.
	bool m_Operator;	// if RunPage. No One can operator all function.!

	bool MotorRun(long pulse);
	bool m_bStop;	// if true. Stop the Motor.

public:

	bool m_bRunGo;
	bool m_bRunStop;
	void SetGoUI(bool bGo);
	static UINT MotorMonitorThread(LPVOID p);

// Dialog Data
	//{{AFX_DATA(CDlgMotorMontior)
	enum { IDD = IDD_DLG_MOTORMONTIOR };
	CButtonST	m_btnTorque;
	CStatic	m_wndMsg;
	CButton	m_btnPreCheckAll;
	CButton	m_btnPreCheck;
	CButton	m_btnClearCount;
	CButton	m_btnServoOffAll;
	CStatic	m_wndInPos2;
	CLed	m_ledInPos2;
	CStatic	m_wndELCount;
	CStatic	m_wndERCount;
	CStatic	m_wndError;
	CStatic	m_wndZPhase;
	CStatic	m_wndZeroSpeed;
	CStatic	m_wndTLC;
	CStatic	m_wndPLmt;
	CStatic	m_wndNLmt;
	CStatic	m_wndEmg;
	CEdit	m_wnddStandy;
	CEdit	m_wnddPos3;
	CEdit	m_wnddPos2;
	CEdit	m_wnddPos1;
	CStatic	m_wndStandy;
	CStatic	m_wndPos3;
	CStatic	m_wndPos2;
	CStatic	m_wndPos1;
	CButton	m_btnGo;
	CButton	m_btnStop;
	CColorBtn	m_btnNormalSetting;
	CButton	m_wndWGroup;
	CStatic	m_wndWStartSpeed;
	CStatic	m_wndWMaxSpeed;
	CStatic	m_wndWAccl;
	CStatic	m_wndWMulSpeed;
	CStatic	m_wndWDriftSpeed;
	CStatic	m_wndWInPos;
	CStatic	m_wndWSearchSpeed;
	CStatic	m_wndWJerk;
	CStatic	m_wndLCount;
	CLed	m_TLC;
	CLed	m_ZeroSpeed;
	CButtonST	m_btnModify;
	CButtonST	m_btnCancel;
	CButtonST	m_btnOK;
	CLed	m_Connection;
	CLed	m_ZPhase;
	CLed	m_pLMT;
	CLed	m_nLMT;
	CLed	m_InPos;
	CLed	m_Err;
	CLed	m_Emg;
	CLed	m_Drv;
	CLed	m_Alarm;
	CLed	m_Servo;
	int		m_iJerk;
	int		m_iStartSpeed;
	int		m_iAccelerate;
	int		m_iMaxSpeed;
	int		m_iMultiple;
	int		m_iInPosRange;
	int		m_iDriftSpeed;
	int		m_iSearchSpeed;
	CEdit	m_wndStartSpeed;
	CEdit	m_wndSearchSpeed;
	CEdit	m_wndMultiple;
	CEdit	m_wndMaxSpeed;
	CEdit	m_wndInPosRange;
	CEdit	m_wndDriffSpeed;
	CEdit	m_wndAccelerate;
	CEdit	m_wndJerk;
	CStatic	m_wndRCount;
	int		m_iMotor;
	CColorBtn	m_btnArmX;
	CColorBtn	m_btnArmY;
	CColorBtn	m_btnArmZ;
	CColorBtn	m_btnArmInserter;
	long	m_lMotorPos1;
	long	m_lMotorPos2;
	long	m_lMotorPos3;
	long	m_lmsc;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgMotorMontior)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL DestroyWindow();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgMotorMontior)
	virtual BOOL OnInitDialog();
	afx_msg void OnLCount();
	afx_msg void OnAlarm();
	afx_msg void OnDrv();
	afx_msg void OnServo();
	afx_msg void OnClearErr();
	afx_msg void OnClearRCount();
	afx_msg void OnClear();
	afx_msg void OnServoOffAllMotor();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnClose();
	afx_msg void OnDestroy();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnModifyParameter();
	afx_msg void OnChangeStartSpeed();
	afx_msg void OnChangeMaxSpeed();
	afx_msg void OnChangeAccel();
	afx_msg void OnChangeMul();
	afx_msg void OnChangeDriftSpeed();
	afx_msg void OnChangeSearchSpeed();
	afx_msg void OnChangeJerk();
	afx_msg void OnChangeInPosRange();
	afx_msg void OnGo();
	afx_msg void OnStop();
	afx_msg void OnNormal();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnPreCheck();
	afx_msg void OnPreCheck2();
	afx_msg void OnTorque();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGMOTORMONTIOR_H__8D2CFC92_FABF_480F_ACB0_7E73520084C6__INCLUDED_)
