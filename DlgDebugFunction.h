#if !defined(AFX_DLGDEBUGFUNCTION_H__3AE19BAF_E685_486C_9BCA_5EFCEEBAF9BE__INCLUDED_)
#define AFX_DLGDEBUGFUNCTION_H__3AE19BAF_E685_486C_9BCA_5EFCEEBAF9BE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgDebugFunction.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgDebugFunction dialog

class CDlgDebugFunction : public CDialog
{
// Construction
public:
	CDlgDebugFunction(CWnd* pParent = NULL);   // standard constructor

	void InitValue();
	void SaveData();

	//
	void InitInterfaceEnable();
	void SaveInterfaceEnable();

	//
	bool CheckModuleValid();

// Dialog Data
	//{{AFX_DATA(CDlgDebugFunction)
	enum { IDD = IDD_DLG_DEBUG_FUNCTION };
	CButtonST	m_btnTSRemainIC;
	CButtonST	m_btnByPassShuttleError;
	CButtonST	m_btnByPassTrayInPos;
	CButtonST	m_btnTorqueCtrl;
	CButtonST	m_btnEnableCustomInput;
	CButtonST	m_btnEnableInputTrayInfo;
	CButtonST	m_btnEnableInputTrayNumber;
	CButtonST	m_btnEnableTTL;
	CButtonST	m_btnEnableTcp;
	CButtonST	m_btnEnableRs232;
	CButtonST	m_btnEnableGPIB;
	CButtonST	m_btnPTCModule;
	CButtonST	m_btnRemoteControl;
	CButtonST	m_btnHeaterModule;
	CButtonST	m_btnTriTemperatureModule;
	CButtonST	m_btnCCDSocket;
	CButtonST	m_btnCCDPin1;
	CButtonST	m_btnATCModule;
	CButtonST	m_btnRemoteIO;
	CButtonST	m_btnInputTrayTips;
	CButtonST	m_btnEnableICMissingDetect;
	CButtonST	m_btnEnableSummaryReport;
	CButtonST	m_btnEnableRotatorTurn;
	CButtonST	m_btnEnableRotatorPreGuide;
	CButtonST	m_btnIONFanAlarmDetect;
	CButtonST	m_btnAlarmMail;
	CButtonST	m_btnInitialPreMove;	
	CButtonST	m_btnEnableSimplified;
	CButtonST	m_btnShowContactCounter;
	CButtonST	m_btnEnableChipTray;
	CButtonST	m_btnByPassTestVacc;
	CButtonST	m_btnByPassEnableIORecovery;
	CButtonST	m_btnByEnableRotatorError;
	CButtonST	m_btnRotatoUse;
	CButtonST	m_btnEnableDoorSensor;
	CButtonST	m_btnByPassVacc;
	CButtonST	m_btnEnableAlarm;
	CButtonST	m_btnSetByMode;
	CButtonST	m_btnEnableSaveSiteSetting;
	CButtonST	m_btnCancel;
	CButtonST	m_btnOK;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgDebugFunction)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgDebugFunction)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGDEBUGFUNCTION_H__3AE19BAF_E685_486C_9BCA_5EFCEEBAF9BE__INCLUDED_)
