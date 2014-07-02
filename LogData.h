// LogData.h: interface for the CLogData class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LOGDATA_H__495D6928_A2E4_4810_8D89_88B293055CCB__INCLUDED_)
#define AFX_LOGDATA_H__495D6928_A2E4_4810_8D89_88B293055CCB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

const   int LOG_DATA_SIZE = 32;         // log data size (Bytes).

enum DutStatus
{
    Pass,               // DUT present and passed test.
    Fail,               // DUT present and failed test.
    NoContact,          // No contact with DUT - it may or may not be there.
    NotPresent,         // DUT has been picked and is no longer in the tray.
};

class CLogData  
{
public:
	DutStatus       status;
	unsigned int	logData[LOG_DATA_SIZE];

    // Copy constructor.
    CLogData( const CLogData& src );


public:
	CLogData();
	virtual ~CLogData();

};

//////////////////////////////////////////////////////
// Tray Map Record (Jim Libby TrayMap ocx )
// Definition of the array of log data for each Tray.
typedef CArray <CLogData, CLogData> TestDataArray;

#endif // !defined(AFX_LOGDATA_H__495D6928_A2E4_4810_8D89_88B293055CCB__INCLUDED_)
