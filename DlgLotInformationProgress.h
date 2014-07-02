#if !defined(AFX_DLGLOTINFORMATIONPROGRESS_H__E3495C1D_1619_402D_ACDB_7881A1D1D483__INCLUDED_)
#define AFX_DLGLOTINFORMATIONPROGRESS_H__E3495C1D_1619_402D_ACDB_7881A1D1D483__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgLotInformationProgress.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgLotInformationProgress dialog

class CDlgLotInformationProgress : public CDialog
{
// Construction
public:
	CDlgLotInformationProgress(CWnd* pParent = NULL);   // standard constructor

	static UINT LotLotDoneCtrlThread(LPVOID p);
	static UINT LotCtrProgressStatuslThread(LPVOID p);

public:
	CWinThread *pWindLotDoneThread;
	CWinThread *pWindLotDonePragressThread;
	HANDLE hLotDoneProcess;
	HANDLE hLotDonePragressProcess;

	bool CloseLotDone();
	bool CloseLotDonePragress();

public:
	void SetCloseTimer();

// Dialog Data
	//{{AFX_DATA(CDlgLotInformationProgress)
	enum { IDD = IDD_LOT_INFO_PROG };
	CProgressCtrl	m_wndProgress;
	CStatic	m_wndMsg;
	CButtonST	m_btnOK;
	CButtonST	m_btnCancel;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgLotInformationProgress)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgLotInformationProgress)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGLOTINFORMATIONPROGRESS_H__E3495C1D_1619_402D_ACDB_7881A1D1D483__INCLUDED_)
