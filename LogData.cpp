// LogData.cpp: implementation of the CLogData class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "deer.h"
#include "LogData.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

// Copy constructor.
CLogData::CLogData( const CLogData& src )
{
    this->status = src.status;

    for ( int i = 0; i < LOG_DATA_SIZE; i++ )
        this->logData[i] = src.logData[i];
}

CLogData::CLogData()
{
	status = Fail;

    for ( int i = 0; i < LOG_DATA_SIZE; i++ )
        logData[i] = 0;
}

CLogData::~CLogData()
{

}
