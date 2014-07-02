// Report.h: interface for the CReport class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_REPORT_H__B936CBB5_DCD3_44E1_B3C2_CD79041F782E__INCLUDED_)
#define AFX_REPORT_H__B936CBB5_DCD3_44E1_B3C2_CD79041F782E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CReport  
{
public:
	CReport();
	virtual ~CReport();

	// Insert Log
	void InsertBinLog(tagTestLog tLog);
	void InsertTempLog(tagTestLog tLog);
	void InsertAutoLog(tagTestLog tLog);

	// Insert Mass Data
	void InsertMassDataOpen();
	void InsertMassData(tagTestLog tLog);
	void InsertMassDataClose();

	void CopyBinLog();

	int GetBinCount();
	int GetBinCountTemp();


	// Delete dbase
	void DeleteBinLog();
	void DeleteTempBinLog();

	// Create / Earse Report
	void SetReport_BinLog();
	void EarseReport_BinLog();
	void EarseTempReport_BinLog();

	void DeleteAllSummaryReport();
};

#endif // !defined(AFX_REPORT_H__B936CBB5_DCD3_44E1_B3C2_CD79041F782E__INCLUDED_)
