#if !defined(AFX_TRAYMAPSELCTRL_H__21E36CE9_B717_4AB6_8B93_D01276685C77__INCLUDED_)
#define AFX_TRAYMAPSELCTRL_H__21E36CE9_B717_4AB6_8B93_D01276685C77__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TrayMapSelCtrl.h : header file
//

#include <vector>

/////////////////////////////////////////////////////////////////////////////
// CTrayMapSelCtrl window

class CTrayMapSelCtrl : public CStatic
{
// Construction
public:
	CTrayMapSelCtrl();

public:
	int m_col;
	int m_row;
	std::vector< std::vector<int> > m_traymap;
	std::vector< std::vector<int> > m_binmap;

	std::vector< std::vector<int> > m_traymapststus;

	//
	COLORREF	m_colFore;
	COLORREF	m_colBk;
	COLORREF	m_colRemoteBk;
	COLORREF	m_colRemoteOverBk;
public:
	void setMapSize(int x, int y, int stat = 0);
	void SetForeColour(COLORREF col);
	void SetBkColour(COLORREF col);

	//
	int getPositionInfo(int mx, int my);
	CPoint getPositionPoint(int iposition);

	//
	int m_Position;
	int getPosition();				// 外部取得目前被點選的位置.

	void setPosition(int position);	// 讓外部預設被點選的位置

	//
	bool m_bLock;
	void LockUI();
	void UnLockUI();

	//
	int setCellStatus(int x, int y, int stat);

protected:
	void _DrawSelf(CDC &dc);

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTrayMapSelCtrl)
	protected:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);


// Implementation
public:
	virtual ~CTrayMapSelCtrl();

	// Generated message map functions
protected:
	//{{AFX_MSG(CTrayMapSelCtrl)
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	//}}AFX_MSG
	
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TRAYMAPSELCTRL_H__21E36CE9_B717_4AB6_8B93_D01276685C77__INCLUDED_)
