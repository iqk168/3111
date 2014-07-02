#if !defined(AFX_DLGREPEATTRAYBINCTRL_H__12B74882_B57B_4C36_866A_F42863C5CF61__INCLUDED_)
#define AFX_DLGREPEATTRAYBINCTRL_H__12B74882_B57B_4C36_866A_F42863C5CF61__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgRepeatTrayBinCtrl.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgRepeatTrayBinCtrl dialog

class CDlgRepeatTrayBinCtrl : public CDialog
{
// Construction
public:
	CDlgRepeatTrayBinCtrl(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgRepeatTrayBinCtrl)
	enum { IDD = IDD_DLG_REPEAT_TRAY_BIN };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgRepeatTrayBinCtrl)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgRepeatTrayBinCtrl)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGREPEATTRAYBINCTRL_H__12B74882_B57B_4C36_866A_F42863C5CF61__INCLUDED_)
