#if !defined(AFX_DLGSOCKETVISIONCAM_H__95957D1A_8423_471D_8B08_08EC8BCE3A19__INCLUDED_)
#define AFX_DLGSOCKETVISIONCAM_H__95957D1A_8423_471D_8B08_08EC8BCE3A19__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgSocketVisionCam.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgSocketVisionCam dialog

class CDlgSocketVisionCam : public CDialog
{
// Construction
public:
	CDlgSocketVisionCam(CWnd* pParent = NULL);   // standard constructor

	void UpdataCamList();

// Dialog Data
	//{{AFX_DATA(CDlgSocketVisionCam)
	enum { IDD = IDD_DLG_SOCKETVISION_CAM };
	CButtonST	m_btnOK;
	CButtonST	m_btnCancel;
	CListBox	m_listCam;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgSocketVisionCam)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgSocketVisionCam)
	virtual BOOL OnInitDialog();
	virtual void OnCancel();
	virtual void OnOK();

	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGSOCKETVISIONCAM_H__95957D1A_8423_471D_8B08_08EC8BCE3A19__INCLUDED_)
