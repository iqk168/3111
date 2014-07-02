// RADatabaseLock.cpp: implementation of the CRADatabaseLock class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "RADatabaseLock.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CRADatabaseLock::CRADatabaseLock()
{

}

CRADatabaseLock::~CRADatabaseLock()
{

}

_RecordsetPtr CRADatabaseLock::RAGetDisconnectedRs(const char *SqlStatement)
{
	CSingleLock L(&object);
	L.Lock();

	return CRADatabase::RAGetDisconnectedRs(SqlStatement);
}

HRESULT CRADatabaseLock::RAExecuteNoRs(const char *SqlStatement)
{
	CSingleLock L(&object);
	L.Lock();

	return CRADatabase::RAExecuteNoRs(SqlStatement);
}
