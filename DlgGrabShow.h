#if !defined(AFX_DLGGRABSHOW_H__9DF2B269_00F0_45CC_95F2_425C1468FB92__INCLUDED_)
#define AFX_DLGGRABSHOW_H__9DF2B269_00F0_45CC_95F2_425C1468FB92__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgGrabShow.h : header file
//

#include "CtrlVision.h"


/////////////////////////////////////////////////////////////////////////////
// CDlgGrabShow dialog

class CDlgGrabShow : public CDialog
{
// Construction
public:
	CDlgGrabShow(CWnd* pParent = NULL);   // standard constructor

	void CheckModify();
	void CheckModifyLevel();

	//
	EImageC24 SourceImage;
	EROIC24 SourceROI;

	//	public 
	void UpdateGrabImage(EImageC24 *pImage, CString result);
	//


// Dialog Data
	//{{AFX_DATA(CDlgGrabShow)
	enum { IDD = IDD_DLG_GRAB_SHOW };
	CStatic	m_wndGrab;
	CStatic	m_wndPattern;
	CColorFontStatic	m_wndResult;
	CButtonST	m_btnOK;
	CButtonST	m_btnCancel;
	CEdit	m_edtScore;
	CButton		m_btnMatch;
	CButtonST	m_btnSave;
	CButtonST	m_btnModify;
	double	m_dScore;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgGrabShow)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgGrabShow)
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnMatch();
	afx_msg void OnModify();
	afx_msg void OnSave();
	afx_msg void OnLoadFile();
	afx_msg void OnClose();
	afx_msg void OnDestroy();
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnPaint();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

protected:

	EImageC24 *m_pImage;
	CRect m_Rect;
	CBitmap m_Pattern;
	CPen sourcePen;
	CPen disablePen;
	CPen RedPen;
	enum E_HANDLES m_eHandle;
	CRect rectWnd, rectShow;
	CPoint Origin;

	bool m_bModify;

	// Modify Using
	EImageC24 m_ImageC24;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGGRABSHOW_H__9DF2B269_00F0_45CC_95F2_425C1468FB92__INCLUDED_)
