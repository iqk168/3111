#if !defined(AFX_DLGCAMERASETTING_H__834077AA_9561_40A8_95A6_7F81AEC19444__INCLUDED_)
#define AFX_DLGCAMERASETTING_H__834077AA_9561_40A8_95A6_7F81AEC19444__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgCameraSetting.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgCameraSetting dialog

class CDlgCameraSetting : public CDialog
{
// Construction
public:
	CDlgCameraSetting(CWnd* pParent = NULL);   // standard constructor

	void InitValue();
	void SaveData();

	//
	void UnLock();

// Dialog Data
	//{{AFX_DATA(CDlgCameraSetting)
	enum { IDD = IDD_DLG_CAMERA_SETTING };
	CButtonST	m_btnCameraList;
	CButtonST	m_btnCancel;
	CButtonST	m_btnOK;
	CEdit		m_wndRoiH;
	CEdit		m_wndRoiW;
	CEdit		m_wndRoiX;
	CEdit		m_wndRoiY;
	int			m_iCameraID;
	int			m_RoiX;
	int			m_RoiY;
	int			m_RoiH;
	int			m_RoiW;
	CEdit		m_wndRoiHSocket;
	CEdit		m_wndRoiWSocket;
	CEdit		m_wndRoiXSocket;
	CEdit		m_wndRoiYSocket;
	int			m_iCameraIDSocket;
	int			m_RoiXSocket;
	int			m_RoiYSocket;
	int			m_RoiHSocket;
	int			m_RoiWSocket;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgCameraSetting)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgCameraSetting)
	afx_msg void OnCcdList();
	virtual void OnOK();
	virtual void OnCancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnLock();
	afx_msg void OnCcdDevice();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGCAMERASETTING_H__834077AA_9561_40A8_95A6_7F81AEC19444__INCLUDED_)
