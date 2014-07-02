#if !defined(AFX_VIEWTRAYMOTOR_H__6BA11849_5C96_4A43_A179_115DE8D1FE47__INCLUDED_)
#define AFX_VIEWTRAYMOTOR_H__6BA11849_5C96_4A43_A179_115DE8D1FE47__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ViewTrayMotor.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CViewTrayMotor view

#include "TrayFile.h"

class CViewTrayMotor : public CView
{

public:
	enum Status 
	{
		enEOF		= -1,	// 
		enEmpty		= 0,	// 該位置是空白.
		enBooking	= 1,	// 正在寫入資料.
		enUnBook	= 2,	// 有 IC 但是沒有測試.
		enMoving	= 3,	// 正在移動中.
		enOK		= 4,	// 

		// For Pick 
		enSoakDone		= 5,	// 表示 Soak Time OK. 可以取走
		enSoakBooking	= 6,	// 正在寫入資料.		
		enSoakMoving	= 7,	// 正在移動中.
		enSoakOK		= 8,	// 表示 Soak Time OK. 而且被取走成功
		enWaitSoak		= 9,	// 表示被指定過時間.等待 Soak Time
	};	

protected:


// Attributes
public:
	CViewTrayMotor();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CViewTrayMotor)

	virtual ~CViewTrayMotor();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	void SetType(int Type);
	int m_iType;
	CBrush	m_Brush[11];	// 
	
	// 
	void SetChipMode(int Chip);	// 0 is not chip / 1 is chip tray
	int	 m_iChip;

	// 
	void LockPick();
	void UnLockPick();
	int  Lock;	// 1 = Lock , 0 = Unlock
	
	// 
	void ShowValue();
	int	 Show;	// 1 = Show, 0 = No Show

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CViewTrayMotor)
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	//}}AFX_VIRTUAL

// Implementation
protected:


	// Generated message map functions
protected:
	//{{AFX_MSG(CViewTrayMotor)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VIEWTRAYMOTOR_H__6BA11849_5C96_4A43_A179_115DE8D1FE47__INCLUDED_)
