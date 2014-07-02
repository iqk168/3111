// Member.h: interface for the CMember class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MEMBER_H__4CDF129E_9D65_4351_93EA_339601AEC5D2__INCLUDED_)
#define AFX_MEMBER_H__4CDF129E_9D65_4351_93EA_339601AEC5D2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ComInterface.h"

class CMember  
{
public:
	CMember();
	virtual ~CMember();

public:
	CInterface Com;

	int Count;
	int iValue;
};

#endif // !defined(AFX_MEMBER_H__4CDF129E_9D65_4351_93EA_339601AEC5D2__INCLUDED_)
