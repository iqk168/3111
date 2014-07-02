#if !defined(AFX_DLGSETTINGNOTE_H__4CDB3DEF_9264_4B0A_8C9A_61D92DA01666__INCLUDED_)
#define AFX_DLGSETTINGNOTE_H__4CDB3DEF_9264_4B0A_8C9A_61D92DA01666__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgSettingNote.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgSettingNote dialog

class CDlgSettingNote : public CDialog
{
// Construction
public:
	CDlgSettingNote(int iIftype, CWnd* pParent = NULL);   // standard constructor

	int m_iIftype;
	
	void LoadFile();
	void InitValue();
	CString GetIfNoteFileName();

// Dialog Data
	//{{AFX_DATA(CDlgSettingNote)
	enum { IDD = IDD_SETTING_NOTE };
	CRichEditCtrl	m_wndIfReport;
	CButtonST	m_btnCancel;
	CButtonST	m_btnOK;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgSettingNote)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgSettingNote)
	virtual void OnOK();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGSETTINGNOTE_H__4CDB3DEF_9264_4B0A_8C9A_61D92DA01666__INCLUDED_)
