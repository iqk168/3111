#if !defined(AFX_VIEWTRAYMAP_H__6BAE8EC5_A451_4501_9241_504BCF9D5527__INCLUDED_)
#define AFX_VIEWTRAYMAP_H__6BAE8EC5_A451_4501_9241_504BCF9D5527__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ViewTrayMap.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CViewTrayMap view

class CViewTrayMap : public CView
{
public:
	CViewTrayMap();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CViewTrayMap)

	virtual ~CViewTrayMap();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
protected:

// Attributes
public:
	CBrush	m_Brush[1];

	CFont font;

	// FT
	void SetTrayID( int ID);						// 砞﹚ヘ玡硂ン琌倒 Output ノ
	void SetTrayBrush( int ID);						// 箇砞ぃンΤぃ Brush, ┮砞﹚ ID 琵ン∕﹚璶ノ Brush

	bool m_bBrush;									// 琌パ场砞﹚筁肅︹
	COLORREF m_crColor;								// 场肅︹
	void SetTrayBrush(COLORREF crColor);			// 琵场砞﹚肅︹ ( Output 璹肅︹, 3160 暗猭)

	void SetTrayBrush( bool bBin, int ID );			// 砞﹚ 琘 ID琌璶パ场更郎
	bool m_bBinColor;								// OnDraw 琌 FT家Α
	COLORREF nBkColor;
	CBrush	m_BinBrush[_Tray_Bin];					// 场郎ノ Brush FT 1~16 Bin Using..
	int ChangeBrush(CString Code);					// パ Bin Code ㄓ∕﹚肅︹	
	void SetBinColor(int bin, COLORREF crColor );	// 砞﹚– Bin肅︹
	COLORREF iBinColor[_Tray_Bin];					// 纗肅︹

	// SLT
	bool m_bCustomColor;							// 琌硂家Α
	bool SetCustomColor(CString csCode, COLORREF crColor);			// 场更 Catoregy Color
	void ClearCsutomColor();						// 睲埃郎
	COLORREF GetCustomColor(CString csCode);		// パ Code  Mapping Color
	CArray<CString, CString> m_BinCode;
	CArray<long, long> m_BinColor;
	CBrush	m_BinCustomBrush[1];
	CString GetColorList();							// 琵场弄秈ㄓ郎
	int iCustomColorSize;
 
	// Page
	int iTray; // ê TrayMap 璶陪ボ.

	int m_iTrayNo[4];

	int m_iPage;						// 讽计, 材琌 0. 材 1,2,3,.....
	int m_iPageCount;					// ヘ玡竒Τ碭
	void ChangePageUp();				// э
	void ChangePageDown();				// э
	void ChangePage(int Page);			// 眏ち传计
	void ChangePageCount(int count);	// 糤ヘ玡计
	int	 GetNowPage();					// 肚讽计
	int	 GetPageCount();				// 肚竒Τ碭

	void ResetPage();					// 砞计 (埃.)

	void SaveAsBmp(CString filename);

	// 砞﹚ Chip Tray Mode 
	void SetChipMode(int Chip);	// 0 is not chip / 1 is chip tray
	int	 m_iChip;

	// 砞﹚琌 Repeat Tray
	enum TrayMapMode {
		enTrayMapModeNone		= 0, // None
		enTrayMapModeInOutCtrl	= 1, // Input / Output Ctrl
	};
	int m_iRepeatMode;
	void SetRepeatTray(int iMode);	// 0 is normal, 1 is input/output ctrl



// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CViewTrayMap)
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
protected:
	//{{AFX_MSG(CViewTrayMap)
//	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VIEWTRAYMAP_H__6BAE8EC5_A451_4501_9241_504BCF9D5527__INCLUDED_)
