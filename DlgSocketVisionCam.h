#if !defined(AFX_DLGSOCKETVISIONCAM_H__C09E669D_AC95_4541_8F45_39675AEB4D5F__INCLUDED_)
#define AFX_DLGSOCKETVISIONCAM_H__C09E669D_AC95_4541_8F45_39675AEB4D5F__INCLUDED_

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
	virtual void OnOK();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGSOCKETVISIONCAM_H__C09E669D_AC95_4541_8F45_39675AEB4D5F__INCLUDED_)
