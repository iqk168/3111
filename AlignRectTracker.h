// AlignRectTracker.h: interface for the CAlignRectTracker class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ALIGNRECTTRACKER_H__CDF25F50_8200_4DE2_B172_605EE1955E18__INCLUDED_)
#define AFX_ALIGNRECTTRACKER_H__CDF25F50_8200_4DE2_B172_605EE1955E18__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CAlignRectTracker : public CRectTracker  
{
public:
	CAlignRectTracker();
	virtual ~CAlignRectTracker();

	//
	void Draw( CDC* pDC ) const;
	HBRUSH				  _afxHatchBrush;
	CBrush				  m_brushHatch;

	//
	COLORREF m_RectColor;
	void SetRectColor(COLORREF color);
	
public:
	void Draw( CDC* pDC, CRect rect ) const;
};

#endif // !defined(AFX_ALIGNRECTTRACKER_H__CDF25F50_8200_4DE2_B172_605EE1955E18__INCLUDED_)
