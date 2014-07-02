// YieldControl.cpp: implementation of the CYieldControl class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Deer.h"
#include "YieldControl.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CYieldControl::CYieldControl()
{
	m_iSizeTotal = 0;
	Clear();
}

CYieldControl::~CYieldControl()
{

}

void CYieldControl::SetWindowSize(int iSize)
{
	m_iSizeTotal = iSize;
	Clear();
}

double CYieldControl::Add(bool bPass)
{
	if(m_iSizeTotal <= 0)
	{
		AfxMessageBox("Please set yield control window size.");
		return 0;
	}
	if(m_iSizeNow < m_iSizeTotal)
		m_iSizeNow++;
	
	if(m_iNext >= m_iSizeTotal)
		m_iNext = 0;
	m_bControl[m_iNext] = bPass;
	m_iNext++;

	int iFail = 0;
	for(int i=0; i<m_iSizeNow; i++)
	{
		if(!m_bControl[i]) iFail++;
	}

	return (1.0 - (iFail * 1.0 / m_iSizeTotal)) * 100;
}

void CYieldControl::Clear()
{
	m_iSizeNow = m_iNext = 0;
}

double CYieldControl::GetYield()
{
	int iFail = 0;
	for(int i=0; i<m_iSizeNow; i++)
	{
		if(!m_bControl[i]) iFail++;
	}

	if(m_iSizeTotal <=0)
		return 0;
	else
		return (1.0 - (iFail * 1.0 / m_iSizeTotal)) * 100;
}
