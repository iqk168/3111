#if !defined(AFX_DLGREMOTECOMMMSGLOT_H__2B2E107E_FF3A_4898_A929_B7181EF795E0__INCLUDED_)
#define AFX_DLGREMOTECOMMMSGLOT_H__2B2E107E_FF3A_4898_A929_B7181EF795E0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgRemoteCommMsgLot.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgRemoteCommMsgLot dialog

class CDlgRemoteCommMsgLot : public CDialog
{
// Construction
public:
	CDlgRemoteCommMsgLot(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgRemoteCommMsgLot)
	enum { IDD = IDD_DLG_REMOTE_COMMUNICATION_MSG_LOT };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgRemoteCommMsgLot)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgRemoteCommMsgLot)
	virtual BOOL OnInitDialog();
	afx_msg void OnFGetLotNo();
	afx_msg void OnFSetLotNo();
	afx_msg void OnFGetMachineNo();
	afx_msg void OnFSetMachineNo();
	afx_msg void OnFGetOperatorNo();
	afx_msg void OnFSetOperatorNo();
	afx_msg void OnFGetDeviceId();
	afx_msg void OnFSetDeviceId();
	afx_msg void OnFGetProgramId();
	afx_msg void OnFSetProgramId();
	afx_msg void OnFSetNewLot();
	afx_msg void OnFSetLotDown();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGREMOTECOMMMSGLOT_H__2B2E107E_FF3A_4898_A929_B7181EF795E0__INCLUDED_)
