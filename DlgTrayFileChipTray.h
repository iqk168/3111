#if !defined(AFX_DLGTRAYFILECHIPTRAY_H__665F7803_3A56_45F3_81EC_0D405E8700D5__INCLUDED_)
#define AFX_DLGTRAYFILECHIPTRAY_H__665F7803_3A56_45F3_81EC_0D405E8700D5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgTrayFileChipTray.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgTrayFileChipTray dialog

class CDlgTrayFileChipTray : public CDialog
{
// Construction
public:
	CDlgTrayFileChipTray(CString csFile = "", CWnd* pParent = NULL);   // standard constructor

	void			LoadTraySpec();
	void			SaveTraySpec();

	tagTraySpec		m_TraySpec;
	CString			m_csFile;

	bool			m_fChange;

	// Debug
	void ConvertChipTray();
	int GetChipTrayPosition( int iBooking );
	int *m_ChipTrayArray;				// 用來紀錄轉換陣列的
	CPoint	GetIndex(int iNo);

// Dialog Data
	//{{AFX_DATA(CDlgTrayFileChipTray)
	enum { IDD = IDD_TRAY_FILE_CHIP_TRAY };
	CStatic	m_wndFile;
	CButtonST	m_btnCancel;
	CButtonST	m_btnOK;
	double	m_dSubA;
	double	m_dSubB;
	double	m_dSubC;
	double	m_dSubChipA;
	double	m_dSubChipB;
	double	m_dSubChipC;
	double	m_dSubChipD;
	long	m_lSubChipColumn;
	long	m_lSubChipRow;
	long	m_lSubColumn;
	double	m_dSubD;
	long	m_lSubRow;
	BOOL	m_bUseFixTray;
	BOOL	m_bUseInput;
	BOOL	m_bUseOutput;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgTrayFileChipTray)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgTrayFileChipTray)
	virtual void OnOK();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnUseInputStack();
	afx_msg void OnUseOutputStack();
	afx_msg void OnUseFixTray();
	afx_msg void OnChangeSubA();
	afx_msg void OnChangeSubB();
	afx_msg void OnChangeSubC();
	afx_msg void OnChangeSubD();
	afx_msg void OnChangeSubColumn();
	afx_msg void OnChangeSubChipA();
	afx_msg void OnChangeSubChipB();
	afx_msg void OnChangeSubChipC();
	afx_msg void OnChangeSubChipD();
	afx_msg void OnChangeSubChipColumn();
	afx_msg void OnChangeSubChipRow();
	afx_msg void OnConvert();
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGTRAYFILECHIPTRAY_H__665F7803_3A56_45F3_81EC_0D405E8700D5__INCLUDED_)
