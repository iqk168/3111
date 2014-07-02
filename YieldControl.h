// YieldControl.h: interface for the CYieldControl class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_YIELDCONTROL_H__C8D89F8D_B044_4956_B7C8_DFE114DF99C7__INCLUDED_)
#define AFX_YIELDCONTROL_H__C8D89F8D_B044_4956_B7C8_DFE114DF99C7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CYieldControl  
{
#define _Max_Yield_Item 2000

public:
	double GetYield();
	void Clear();
	double Add(bool bPass);
	void SetWindowSize(int iSize);
	CYieldControl();
	virtual ~CYieldControl();

protected:
	long	m_iSizeTotal;
	long	m_iNext;
	long	m_iSizeNow;
	bool	m_bControl[_Max_Yield_Item];

};

#endif // !defined(AFX_YIELDCONTROL_H__C8D89F8D_B044_4956_B7C8_DFE114DF99C7__INCLUDED_)
