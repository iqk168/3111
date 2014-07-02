#if !defined(AFX_VIEWREPEATTRAYMOTOR_H__3025BE2F_7B38_416C_93BC_164EFEB6F412__INCLUDED_)
#define AFX_VIEWREPEATTRAYMOTOR_H__3025BE2F_7B38_416C_93BC_164EFEB6F412__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ViewRepeatTrayMotor.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CViewRepeatTrayMotor view

class CViewRepeatTrayMotor : public CView
{
public:	

	CViewRepeatTrayMotor();           // protected constructor used by dynamic creation
	virtual ~CViewRepeatTrayMotor();


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


	bool m_iChip;
	int m_iType;
	void SetType(int type);
	CBrush	m_Brush[11];

protected:
	DECLARE_DYNCREATE(CViewRepeatTrayMotor)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CViewRepeatTrayMotor)
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	//}}AFX_VIRTUAL

// Implementation
protected:

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CViewRepeatTrayMotor)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VIEWREPEATTRAYMOTOR_H__3025BE2F_7B38_416C_93BC_164EFEB6F412__INCLUDED_)
