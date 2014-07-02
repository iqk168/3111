#if !defined(AFX_DLGCUSTOMPAGEFUNCTION_H__9EA121A2_D3BA_46E6_8656_717A43D1373D__INCLUDED_)
#define AFX_DLGCUSTOMPAGEFUNCTION_H__9EA121A2_D3BA_46E6_8656_717A43D1373D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgCustomPageFunction.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgCustomPageFunction dialog

class CDlgCustomPageFunction : public CDialog
{
// Construction
public:
	CDlgCustomPageFunction(CWnd* pParent = NULL);   // standard constructor

	tagUserPageEnable m_UserPageEnable;
	tagSetupPageEnable m_SetupPageEnable;
	tagEngineerPageEnable m_EngineerPageEnable;

public:
	void InitOption();
	void SaveOption();

// Dialog Data
	//{{AFX_DATA(CDlgCustomPageFunction)
	enum { IDD = IDD_DLG_CUSTOM_PAGE_FUN };
	CButtonST	m_btnOK;
	CButtonST	m_btnCancel;
	BOOL	m_bUserSummaryReport;
	BOOL	m_bUserVisualPanel;
	BOOL	m_bUserSiteSetting;
	BOOL	m_bUserManualContact;
	BOOL	m_bUserLotInfomation;
	BOOL	m_bUserDeviceSetup;
	BOOL	m_bUserAutoSkip;
	BOOL	m_bUserYieldControl;
	BOOL	m_bSetupAlignment;
	BOOL	m_bSetupAutoRetry;
	BOOL	m_bSetupCatoregy;
	BOOL	m_bSetupDeviceSetup;
	BOOL	m_bSetupEventLog;
	BOOL	m_bSetupIFTesting;
	BOOL	m_bSetupInputTray;
	BOOL	m_bSetupInterface;
	BOOL	m_bSetupIOMonitor;
	BOOL	m_bSetupOffset;
	BOOL	m_bSetupOutputTray;
	BOOL	m_bSetupRemoteControl;
	BOOL	m_bSetupRemoteInput;
	BOOL	m_bSetupSiteSetting;
	BOOL	m_bSetupSpeed;
	BOOL	m_bSetupTimer;
	BOOL	m_bSetupTrayFile;
	BOOL	m_bSetupYieldCtrl;
	BOOL	m_bTrayMapSetting;
	BOOL	m_btnEngAlignment;
	BOOL	m_btnEngCCDSocket;
	BOOL	m_btnEngChangeFile;
	BOOL	m_btnEventLog;
	BOOL	m_btnEngIOMonitor;
	BOOL	m_btnEngMotorMonitor;
	BOOL	m_btnEngSpeed;
	BOOL	m_btnEngTSCounter;
	BOOL	m_btnLoopTest;
	BOOL	m_btnEngAlarmMail;
	BOOL	m_bUserIfTesting;
	BOOL	m_bUserTrayMapReport;
	BOOL	m_bUserTestSiteVacc;
	BOOL	m_bTestResultReport;
	BOOL	m_bSetupRepeatTray;
	BOOL	m_bRepeatTrayStatus;
	BOOL	m_bUserTrayDefColor;
	BOOL	m_bSetupTowerSetting;
	BOOL	m_bUserArmLogICImage;
	BOOL	m_bUserSLTProtocol;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgCustomPageFunction)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgCustomPageFunction)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGCUSTOMPAGEFUNCTION_H__9EA121A2_D3BA_46E6_8656_717A43D1373D__INCLUDED_)
