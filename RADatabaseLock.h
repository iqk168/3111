// RADatabaseLock.h: interface for the CRADatabaseLock class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RARTM_H__AE2417A0_4028_4F9E_B77C_06CC91510CBE__INCLUDED_)
#define AFX_RARTM_H__AE2417A0_4028_4F9E_B77C_06CC91510CBE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "RADatabase.h"
#include <afxmt.h>

class CRADatabaseLock : public CRADatabase  
{
public:
	HRESULT RAExecuteNoRs(const char *SqlStatement);
	_RecordsetPtr RAGetDisconnectedRs(const char *SqlStatement);
	CRADatabaseLock();
	virtual ~CRADatabaseLock();

	CMutex object;

};

#endif // !defined(AFX_RARTM_H__AE2417A0_4028_4F9E_B77C_06CC91510CBE__INCLUDED_)
