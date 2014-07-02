#if !defined(AFX_TRAYMAPCTRL_H__3E925CD0_13EC_4641_A4AA_8797208E0578__INCLUDED_)
#define AFX_TRAYMAPCTRL_H__3E925CD0_13EC_4641_A4AA_8797208E0578__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// TrayMapCtrl.h : header file
//
#include <vector>

#include "C_ColorToolTip.h"

/////////////////////////////////////////////////////////////////////////////
// CTrayMapCtrl window

class CTrayMapCtrl : public CStatic
{
// Construction
public:
	CTrayMapCtrl();
	virtual ~CTrayMapCtrl();

	//
	C_ColorToolTip m_Tips;//
	CString getPositionInfo(int mx, int my);
	int getPositionInfoValue(int mx, int my);

// Attributes
protected:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTrayMapCtrl)
	protected:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);

// Implementation
public:
	
	//
	int GetTextSize(int col, int row);

	//
	void setNumber(bool bEnable);
	bool m_bEnableNumber;
	void setInfo(bool bEnable);
	bool m_bEnableInfo;

	//
	void setTip(bool bEnable);
	bool m_bEnableTips;

	// TrayMapCtrl in Input Tray Support Chip Tray
	void setChipTray(int chiptray, int col, int row);	// 0 for Normal, 1 for ChipTray
	int	 m_chipcol;
	int  m_chiprow;
	int	 m_ChipTray;
	//

	void setMapSize(int x, int y, int stat = 0);
	int getCellStatus(int x, int y);
	int setCellStatus(int x, int y, int stat);
	int setCellBin(int x, int y, int bin);
	void getLastPoint(POINT &pt);
	
	bool isModified();
	void setModified(bool b);

	void ShowText(BOOL bShow);
	void Clear();

	void SetTextForeColour(COLORREF col);
	void SetTextBkColour(COLORREF col);
	void SetForeColour(COLORREF col);
	void SetBkColour(COLORREF col);

protected:
	void _DrawSelf(CDC &dc);

protected:
	int m_col;
	int m_row;
	BOOL		m_bShowText;
	CString		m_strText;
	COLORREF	m_colFore;
	COLORREF	m_colBk;
	COLORREF	m_colTextFore;
	COLORREF	m_colTextBk;

	std::vector< std::vector<int> > m_traymap;
	std::vector< std::vector<int> > m_binmap;
	POINT		m_pt;
	bool		m_modified;

	CPoint		m_cpStartPos;
	CPoint		m_cpEndPos;

public:
	

	// Generated message map functions
protected:
	//{{AFX_MSG(CTrayMapCtrl)
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point); 
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg LRESULT OnNcHitTest(CPoint point);
	afx_msg void OnMButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	//}}AFX_MSG
	afx_msg LRESULT OnSetText(WPARAM, LPARAM);
	afx_msg LRESULT OnGetText(WPARAM, LPARAM);

	DECLARE_MESSAGE_MAP()

};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TRAYMAPCTRL_H__3E925CD0_13EC_4641_A4AA_8797208E0578__INCLUDED_)
