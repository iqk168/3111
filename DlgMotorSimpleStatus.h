#if !defined(AFX_DLGMOTORSIMPLESTATUS_H__34A76540_1637_42A4_9F2C_D56A2E7A4AE1__INCLUDED_)
#define AFX_DLGMOTORSIMPLESTATUS_H__34A76540_1637_42A4_9F2C_D56A2E7A4AE1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgMotorSimpleStatus.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgMotorSimpleStatus dialog

class CDlgMotorSimpleStatus : public CDialog
{
// Construction
public:
	CDlgMotorSimpleStatus(CWnd* pParent = NULL);   // standard constructor

	void MototStatusQuery();

	void InitLed();

	void SelectMotor();

	// Board 0
	tagMotorParam *InserterMotor;
	tagMotorParam *ArmYMotor;
	tagMotorParam *ArmXMotor;
	tagMotorParam *ArmZMotor;

// Dialog Data
	//{{AFX_DATA(CDlgMotorSimpleStatus)
	enum { IDD = IDD_DLG_MOTOR_SIMPLE };
	CLed	m_ledTSTLC;
	CStatic	m_wndArmZRCount;
	CStatic	m_wndArmZpLmt;
	CStatic	m_wndArmZnLmt;
	CStatic	m_wndArmZLCount;
	CStatic	m_wndArmXRCount;
	CStatic	m_wndArmXpLmt;
	CStatic	m_wndArmXnLmt;
	CStatic	m_wndArmXLCount;
	CStatic	m_wndTSRCount;
	CStatic	m_wndTSpLmt;
	CStatic	m_wndTSnLmt;
	CStatic	m_wndTSLCount;
	CStatic	m_wndArmYRCount;
	CStatic	m_wndArmYpLmt;
	CStatic	m_wndArmYnLmt;
	CStatic	m_wndArmYLCount;
	CButtonST	m_btnOK;
	CButtonST	m_btnCancel;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgMotorSimpleStatus)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgMotorSimpleStatus)
	virtual void OnOK();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGMOTORSIMPLESTATUS_H__34A76540_1637_42A4_9F2C_D56A2E7A4AE1__INCLUDED_)
