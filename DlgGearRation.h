#if !defined(AFX_DLGGEARRATION_H__74078D55_C755_46A8_8012_3F6816EADC04__INCLUDED_)
#define AFX_DLGGEARRATION_H__74078D55_C755_46A8_8012_3F6816EADC04__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgGearRation.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgGearRation dialog

class CDlgGearRation : public CDialog
{
// Construction
public:
	CDlgGearRation(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgGearRation)
	enum { IDD = IDD_DLG_GEAR_RATION };
	CButtonST	m_btnOK;
	CButtonST	m_btnCancel;
	double		m_dXGearRation;
	double		m_dYGearRation;
	double		m_dZGearRation;	
	double		m_dInserterGearRation;

	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgGearRation)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgGearRation)
	virtual void OnOK();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	afx_msg void OnClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGGEARRATION_H__74078D55_C755_46A8_8012_3F6816EADC04__INCLUDED_)
