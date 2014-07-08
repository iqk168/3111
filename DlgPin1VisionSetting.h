#if !defined(AFX_DLGPIN1VISIONSETTING_H__4AC60F4F_DCD8_4730_9366_803DD693BB41__INCLUDED_)
#define AFX_DLGPIN1VISIONSETTING_H__4AC60F4F_DCD8_4730_9366_803DD693BB41__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgPin1VisionSetting.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgPin1VisionSetting dialog

#include "SocketVision.h"

class CDlgPin1VisionSetting : public CDialog
{
// Construction
public:
	CDlgPin1VisionSetting(CWnd* pParent = NULL);   // standard constructor

	//
	void GetSettingFolder();
	void UpdataSettingList();
	void UpdataSettingSelect(CString NewName);
	bool IsSettingFileEmpty();						// Empty String return true....
	bool IsSettingFileExist(CString csFileName);	// Exist return true...
	CString GetSettingFileName();

	// 
	void SetectDefault(CString csFileFolder);

	//
	void CreateNewFolder(CString csFileFolder);
	void ReplaceFolder(CString csFileFolder);
	void ReplaceFolderSave(CString csFileFolder);

	//
	void CopyGrabImage(CString csFileFolder);
	void LoadSettingInfo(CString csFileFolder);
	void SaveSettingInfo(CString csFileFolder);

	void LoadSettingImage(CString csFileFolder);

	//
	bool LoadSettingFile(CString csFileName); // Load File return false..

	//
	void DeleteOldFolder( CString csFileFolder);
	
	//
	void GetInitValue();
	void InitValue();
	void InitTips();
	CToolTipCtrl m_ToolTip;

	// File Folder
	CArray <CString, CString > m_FileDictory;

	// eVision
	EImageC24 SourceImage;
	EROIC24 SourceROI;
	CPen sourcePen;

	//
	// Show Window
	double m_WindowWidth;
	double m_WindowHeight;
	CRect m_RectMainWindow;

	// Sub Grab Window
	double m_SubWindowWidth;
	double m_SubWindowHeight;
	CRect m_SubRectMainWindow;

	// Sub Pattern Window
	double m_PatternWindowWidth;
	double m_PatternWindowHeight;
	CRect m_PatternRectMainWindow;	

	//
	enum E_HANDLES m_eHandle; // Mouse Move Use

	//
	bool bGrabed;
	bool bRoied;
	bool bSelected;
	bool bPatterned;
	bool bPatternSelected;
	//

	//
	double m_fMatchTestScore;


// Dialog Data
	//{{AFX_DATA(CDlgPin1VisionSetting)
	enum { IDD = IDD_DLG_PIN1VISION_SETTING };
	CColorFontStatic	m_wndTestScore;
	CComboBox	m_listFileFolder;
	CButtonST	m_btnPatternTest;
	CButtonST	m_btnCapture;
	CButtonST	m_btnPatternSave;
	CButtonST	m_btnClassDelete;
	CButtonST	m_btnClassCreate;
	int		m_iMatchROIX;
	int		m_iMatchROIY;
	int		m_iMatchWidth;
	int		m_iMatchHeight;
	double	m_dMatchMinScore;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgPin1VisionSetting)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;


	// Generated message map functions
	//{{AFX_MSG(CDlgPin1VisionSetting)
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnSocketvisionCreate();
	afx_msg void OnSocketvisionDelete();
	afx_msg void OnSocketvisionSave();
	afx_msg void OnSocketvisionCapture();
	afx_msg void OnSocketvisionTest();
	afx_msg void OnEditchangeSocketvisionClass();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnPaint();
	afx_msg void OnDestroy();
	afx_msg void OnSelchangeSocketvisionClass();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGPIN1VISIONSETTING_H__4AC60F4F_DCD8_4730_9366_803DD693BB41__INCLUDED_)
