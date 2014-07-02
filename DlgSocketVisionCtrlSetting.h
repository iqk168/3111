#if !defined(AFX_DLGSOCKETVISIONCTRLSETTING_H__804ADD05_FFA3_49EA_916A_69CA1E19CB26__INCLUDED_)
#define AFX_DLGSOCKETVISIONCTRLSETTING_H__804ADD05_FFA3_49EA_916A_69CA1E19CB26__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgSocketVisionCtrlSetting.h : header file
//

#include "CtrlVisionAlignment.h"
#include "CtrlVisionMatch.h"
//
#include "ViewSockImage.h"
#include "ViewSockTrackerImage.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgSocketVisionCtrlSetting dialog

class CDlgSocketVisionCtrlSetting : public CDialog
{
// Construction
public:
	// Image
	CViewSockTrackerImage	*pViewMainImage;
	CViewSockImage			*pViewGrabImage;
	CViewSockImage			*pViewPatternImage;
	
	CCtrlVisionAlignment	m_VisionUse; // image 
	//
	CCtrlVisionMatch		m_VisionMatch;

	void InitImage();
	void InitLib();

public:
	CDlgSocketVisionCtrlSetting(CWnd* pParent = NULL);   // standard constructor

public:
	void InitValue();
	void InitResult();

	CToolTipCtrl m_ToolTip;
	void InitTips();

public:
	void GetInitValue();
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

///////////////////////////////////////////////////
	//
	// File Folder
	CArray <CString, CString > m_FileDictory;

	
	void GetSettingFolder();							// 取的目前的目錄
	void UpdataSettingList();							// 更新檔案的選單			
	// 
	void SelectDefault(CString csFileFolder);			// 設定預設的檔案
	void SelectDefaultPos(int iPos);					// 設定預設的檔案(根據位置)

	//
	void LoadSettingImage(CString csFileFolder);		// 載入圖檔
	void LoadSettingInfo(CString csFileFolder);			// 載入設定參數
	void SaveSettingInfo(CString csFileFolder);			// 儲存資料
	void CopyGrabImage(CString csFileFolder);			// 複製最後一比取像的檔案到設定檔資料夾
	void ReplaceFolder(CString csFileFolder);			// 替換設定檔的參數和圖檔
	void CreateNewFolder(CString csFileFolder);			// 建立新的資料夾, 並且把最後一比取像的檔案貼到新的資料夾
	void ReplaceFolderSave(CString csFileFolder);		// 替換設定檔的參數
	void UpdataSettingSelect(CString NewName);			// 根據設定檔名, 選擇下拉選單
	bool IsSettingFileEmpty();							// 確認有選取檔案
	bool IsSettingFileLastOne();						// 確認是否是最後一個檔案
	bool IsSettingFileExist(CString csFileName);		// 確認這個設定檔, 是否已經存在
	void DeleteOldFolder( CString csFileFolder);		// 刪除這個設定檔, 刪除圖片, 刪除參數檔
	
	CString GetSettingFileName();						// 取回目前的資料夾名稱 (不管是選的還是輸入的 )
	CRect GetPatternInfo();								// 取得檔案的資訊 ( Info.txt )
	
	//
	double GetSettingScore(CString csFileFolder);		// 取回目前設定檔的參數
	void MatchResult(double dResult, double dScore);	// 顯示比對結果

	//
	void ReDrawMainImage(CString csFileFolder);			// 重畫目前的主畫面
	void ReDrawPatternImage(CString csFileFolder);		// 重畫目前的Pattern畫面
	void ReDrawGrabImage();								// 重畫目前的Grab畫面 ( Grab.bmp )

	//
	void ReDrawCamGrabImage();							// 取像完, 更新畫面
	void ReDrawCamGrabPatternImahe();					// 取像完, 更新Pattern

	//
	void UpdataPatternInfo();							// 接收CView的ROI位置並更新畫面數據

	//
	void CaptureLockUI(bool bEnable);					// 取像時鎖訂畫面
	void CameraCapture();								// 取像

	//
	typedef struct tagInfoParameter {	
		int iX;			// Left
		int iY;			// Top
		int iWidth;		// Right
		int iHeight;	// Bottom
		double dScore;
	} tagInfoParameter;
///////////////////////////////////////////////////
	// 
	void Message(CString csMsg = _T("") );
///////////////////////////////////////////////////
	// 
	void ChangeFileFolder();							// 選擇檔案
	void ChangeFileFolderOther();
	void FunctionCreate();
	void FunctionDelete();
	void FunctionSave();
	void FunctionTest();

// Dialog Data
	//{{AFX_DATA(CDlgSocketVisionCtrlSetting)
	enum { IDD = IDD_DLG_SOCKETVISION_CTL_SETTING };
	CStatic	m_wndGrabImage;
	CStatic	m_wndPatternImage;
	CStatic	m_wndImage;
	CColorFontStatic	m_wndTestScore;
	int		m_iMatchROIX;
	int		m_iMatchROIY;
	int		m_iMatchWidth;
	int		m_iMatchHeight;
	double	m_dMatchMinScore;	
	CEdit	m_wndInfoROIY;
	CEdit	m_wndInfoROIX;
	CEdit	m_wndInfoWidth;
	CEdit	m_wndInfoHeight;
	CComboBox	m_listFileFolder;
	CButtonST	m_btnPatternTest;
	CButtonST	m_btnCapture;
	CButtonST	m_btnPatternSave;
	CButtonST	m_btnClassDelete;
	CButtonST	m_btnClassCreate;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgSocketVisionCtrlSetting)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CDlgSocketVisionCtrlSetting)
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnSocketvisionCapture();
	afx_msg void OnSocketvisionCreate();
	afx_msg void OnSocketvisionDelete();
	afx_msg void OnSocketvisionSave();
	afx_msg void OnSocketvisionTest();
	afx_msg void OnSelchangeSocketvisionClass();
	afx_msg LRESULT OnPosInfo(WPARAM p, LPARAM l);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGSOCKETVISIONCTRLSETTING_H__804ADD05_FFA3_49EA_916A_69CA1E19CB26__INCLUDED_)
