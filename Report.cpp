// Report.cpp: implementation of the CReport class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Deer.h"
#include "Report.h"

// Mutex
#include <afxmt.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CReport::CReport()
{

}

CReport::~CReport()
{

}

// Insert Log
static CMutex MutexAutoBinLog;
void CReport::InsertAutoLog(tagTestLog tLog)
{
#ifdef _Demo
//	return;
#endif

	CSingleLock Lock(&MutexAutoBinLog);
	Lock.Lock();


	CString csSQL;
	csSQL.Format("INSERT INTO [CodeLog](Code, TestTime, Bin, Booking ) "
		" VALUES ('%s', '%6.2f', %d, %d);", tLog.csCode, tLog.dTestTime, tLog.iBin, tLog.iBooking );

	int nak = E_FAIL;
	int i=0;
	while(nak != S_OK)
	{
		nak = m.DB.tLog.RAExecuteNoRs(csSQL);
		i++;
		if(nak != S_OK)
		{
			m.DB.tLog.Close();																		 
			m.DB.tLog.RAConnect("Driver={Microsoft Access Driver (*.mdb)};Initial Catalog=.\\Report\\TempBinLog.mdb");

			Sleep(10);
		}

		if(i> _InsertCount)
		{
			break;
		}
		Sleep(1);
	}
	//
	m.DB.tLog.Close();

	Lock.Unlock();
}

static CMutex MutexBinLog;
void CReport::InsertBinLog(tagTestLog tLog)
{
	CSingleLock Lock(&MutexBinLog);
	Lock.Lock();

	//
	CString csSQL;
	csSQL.Format("INSERT INTO [CodeLog](Code, TestTime, Bin, Booking ) "
		" VALUES ('%s', '%6.2f', %d, %d);", tLog.csCode, tLog.dTestTime, tLog.iBin, tLog.iBooking );

	m.DB.Log.RAConnect("Driver={Microsoft Access Driver (*.mdb)};Initial Catalog=.\\Report\\BinLog.mdb");

	int nak = E_FAIL;
	int i=0;
	while(nak != S_OK)
	{
		nak = m.DB.Log.RAExecuteNoRs(csSQL);
		i++;
		if(nak != S_OK)
		{
			m.DB.Log.Close();
			m.DB.Log.RAConnect("Driver={Microsoft Access Driver (*.mdb)};Initial Catalog=.\\Report\\BinLog.mdb");
			
			Sleep(10);
		}
		if(i> _InsertCount)
		{
//			AfxMessageBox("Please copy this screen to Chroma's Engineer");
			break;
		}
	}
	//
	m.DB.Log.Close();

	Lock.Unlock();
}

static CMutex MutexTempBinLog;
void CReport::InsertTempLog(tagTestLog tLog)
{
	CSingleLock Lock(&MutexTempBinLog);
	Lock.Lock();

	CString csSQL;
	csSQL.Format("INSERT INTO [CodeLog](ID, Code, TestTime, Bin, Booking ) "
		" VALUES ('%s', '%6.2f', %d, %d);", tLog.csCode, tLog.dTestTime, tLog.iBin, tLog.iBooking );
	
	m.DB.tLog.RAConnect("Driver={Microsoft Access Driver (*.mdb)};Initial Catalog=.\\Report\\TempBinLog.mdb");

	int nak = E_FAIL;
	int i=0;
	while(nak != S_OK)
	{
		nak = m.DB.tLog.RAExecuteNoRs(csSQL);
		i++;
		if(nak != S_OK)
		{
			m.DB.tLog.Close();

			m.DB.tLog.RAConnect("Driver={Microsoft Access Driver (*.mdb)};Initial Catalog=.\\Report\\TempBinLog.mdb");
		
			Sleep(10);
		}
//		if(i>20)
		if(i> _InsertCount) 
		{
			break;
		}
		Sleep(1);
	}

	m.DB.tLog.Close();

	Lock.Unlock();
}
static CMutex MutexBinReport;
void CReport::SetReport_BinLog()
{
	CSingleLock Lock(&MutexBinReport);
	Lock.Lock();

	CString csName = _T("");
	CTime time = CTime::GetCurrentTime();
//	cs.Format("%s, [%s]\r\n", time.Format("%m/%d %H:%M:%S"), csLog);
	csName.Format("%s_SummaryReport", time.Format("%m_%d_%H_%M_%S"));

	CString csFile;
	csFile = m.FilePath.SummaryReportPath + csName + _Sum2;
	// 產生檔名

	CFile file;
	file.Open( csFile, CFile::modeCreate | CFile::modeWrite
		| CFile::modeNoTruncate | CFile::shareDenyNone, NULL);	
	// 開啟檔案
	file.SeekToEnd();
	// 找檔案結尾
	
	//y
	CString csTitle = "**************************** Summary ****************************\r\n";

	file.Write(csTitle.GetBuffer(0), csTitle.GetLength());
	// 填入標題	

	// 填入工單資訊		
	CString csLotStart;
	csLotStart.Format("%s\r\n", m.LotInfo.LotStartTime );
	file.Write(csLotStart.GetBuffer(0), csLotStart.GetLength());
	// 工單號碼

	//
	CString csLotNumber;
	csLotNumber.Format("Lot Number : %s\r\n", m.LotInfo.LotInfoNo );
	file.Write(csLotNumber.GetBuffer(0), csLotNumber.GetLength());
	// 工單號碼
	
	CString csLotOperationerID;
	csLotOperationerID.Format("Lot Operationer ID : %s\r\n", m.LotInfo.LotInfoOperator );
	file.Write(csLotOperationerID.GetBuffer(0), csLotOperationerID.GetLength());
	// 填入作業員資訊

	CString csLotProgramName;
	csLotProgramName.Format("Lot Operationer ID : %s\r\n", m.LotInfo.LotInfoProgramerID );
	file.Write(csLotProgramName.GetBuffer(0), csLotProgramName.GetLength());
	// 填入 Program Name

	CString csLotDeviceID;
	csLotDeviceID.Format("Lot Device ID : %s\r\n", m.LotInfo.LotInfoDeviceID );
	file.Write(csLotDeviceID.GetBuffer(0), csLotDeviceID.GetLength());
	// 填入 Device ID

	CString csTotal = _T("");
	CString csSiteCounter = _T("");

	int total = 0;
	int i = 0;
	for(i=0; i<_Output_Stack_No; i++)
		total += m.Counter.OutputCount[i];

	csTotal.Format("Total Tested IC : %d\r\n", total );
	file.Write(csTotal.GetBuffer(0), csTotal.GetLength());
	// 總數

	for(i=0; i<_Output_Stack_No; i++)
	{
		csSiteCounter.Format("Hardware Bin %d: %d (%3.2f%%)\r\n",
					i+1, m.Counter.OutputCount[i], m.Counter.OutputCount[i] * 100. / total);

		file.Write(csSiteCounter.GetBuffer(0), csSiteCounter.GetLength());
	}
	// Hardware Bin
	// 填入良率 / 總數

	CString csTitle1 = "**************************** Test Log ****************************\r\n";
	file.Write(csTitle1.GetBuffer(0), csTitle1.GetLength());
	// 填入標題	1

	CString csTitle2 = "ID\tCode\tBin\tBooking\t\tTestTime\r\n";
	file.Write(csTitle2.GetBuffer(0), csTitle2.GetLength());
	// 填入標題	2
 
	m.DB.Log.RAConnect("Driver={Microsoft Access Driver (*.mdb)};Initial Catalog=.\\Report\\BinLog.mdb");
	// 連線 mdb

	_RecordsetPtr r = m.DB.Log.RAGetDisconnectedRs("Select * From CodeLog");

	CString csID;
	CString csCode;
	CString csBin;
	CString csBooking;
//	COleDateTime csTestTime;
	double dTestTime;

	CString csRecord;
	int iID = 0;
	bool    bExistData = false;
	if (r)
	{
		CRADatabaseLock recordset;
		while (!r->adoEOF)
		{
			iID++;
			csID.Format("%d", iID);

			m.DB.Log.GetFieldValue(r, "Code",		csCode);
			m.DB.Log.GetFieldValue(r, "Bin",		csBin);
			m.DB.Log.GetFieldValue(r, "Booking",	csBooking);
			m.DB.Log.GetFieldValue(r, "TestTime",	dTestTime);

			CString csTestTime = _T("");
			csTestTime.Format("%5.2f", dTestTime );

			csBin.Replace("-1", _DefaultCode );
			
			csRecord.Format("%s\t%s\t%s\t%s\t\t%s\t\r\n", csID, csCode, csBin, csBooking, csTestTime );
			file.Write(csRecord.GetBuffer(0), csRecord.GetLength());
			// 寫入資料

			m.m_LotInfoProg.m_lLotInformationStatus++;
			bExistData = true;
			
			r->MoveNext();
		}
		// 從 BinLog.mdb 取出資料 然後填入 Report.
	}
	else
		;	// 沒有取到資料

	file.Close();
	// 
	Lock.Unlock();
}

static CMutex MutexDTemoBinReport;
void CReport::EarseTempReport_BinLog()
{
	CSingleLock Lock(&MutexDTemoBinReport);
	Lock.Lock();

	m.DB.tLog.RAConnect("Driver={Microsoft Access Driver (*.mdb)};Initial Catalog=.\\Report\\TempBinLog.mdb");
	// 連線 mdb

	_RecordsetPtr r = m.DB.tLog.RAGetDisconnectedRs("DELETE From CodeLog");
	// 刪除資料

	m.DB.tLog.Close();

	Lock.Unlock();
}
static CMutex MutexDBinReport;
void CReport::EarseReport_BinLog()
{
	CSingleLock Lock(&MutexDBinReport);
	Lock.Lock();

	m.DB.Log.RAConnect("Driver={Microsoft Access Driver (*.mdb)};Initial Catalog=.\\Report\\BinLog.mdb");
	// 連線 mdb

	_RecordsetPtr r = m.DB.Log.RAGetDisconnectedRs("DELETE From CodeLog");
	// 刪除資料

	Lock.Unlock();
}

int  CReport::GetBinCountTemp()
{
	CString csSQL;

	m.DB.tLog.RAConnect("Driver={Microsoft Access Driver (*.mdb)};Initial Catalog=.\\Report\\TempBinLog.mdb");
	// 準備要寫入的 Bin Log

	int a = 0;
	_RecordsetPtr r = m.DB.tLog.RAGetDisconnectedRs("SELECT COUNT(*) as a From CodeLog");
	CRADatabaseLock recordset;							

	int iCount = 0;
	if(r)
	{
		if (!r->adoEOF) 
		{
			recordset.GetFieldValue(r, "a",	iCount);
		}
	}

	m.DB.tLog.Close();

	return iCount;
}
int  CReport::GetBinCount()
{
	CString csSQL;

	m.DB.Log.RAConnect("Driver={Microsoft Access Driver (*.mdb)};Initial Catalog=.\\Report\\BinLog.mdb");
	// 準備要寫入的 Bin Log

	int a = 0;
	_RecordsetPtr r = m.DB.Log.RAGetDisconnectedRs("SELECT COUNT(*) as a From CodeLog");
	CRADatabaseLock recordset;							

	int iCount = 0;
	if(r)
	{
		if (!r->adoEOF) 
		{
			recordset.GetFieldValue(r, "a",	iCount);
		}
	}

	m.DB.Log.Close();

	return iCount;

}
void CReport::InsertMassDataOpen()
{
	CString csSQL;
	tagTestLog tLog;
	m.DB.tLog.RAConnect("Driver={Microsoft Access Driver (*.mdb)};Initial Catalog=.\\Report\\TempBinLog.mdb");
	// 連線 mdb
}
static CMutex MutexMassBinLog;
void CReport::InsertMassData(tagTestLog tLog)
{
	CSingleLock Lock(&MutexMassBinLog);
	Lock.Lock();

	//
	CString csSQL;
	csSQL.Format("INSERT INTO [CodeLog](Code, TestTime, Bin, Booking ) "
		" VALUES ('%s', '%6.2f', %d, %d);", tLog.csCode, tLog.dTestTime, tLog.iBin, tLog.iBooking );

	int nak = E_FAIL;
	int i=0;
	while(nak != S_OK)
	{
		nak = m.DB.tLog.RAExecuteNoRs(csSQL);
		i++;
		if(nak != S_OK)
		{
			m.DB.tLog.Close();
			m.DB.tLog.RAConnect("Driver={Microsoft Access Driver (*.mdb)};Initial Catalog=.\\Report\\BinLog.mdb");
			
			Sleep(10);
		}
		if(i> _InsertCount)
		{
			break;
		}
	}
	Lock.Unlock();
}
void CReport::InsertMassDataClose()
{
	m.DB.tLog.Close();
}
// 1.0Af
// Remove this function and re-build new one
/*
void  CReport::CopyBinLog()
{
	CString csSQL;
	tagTestLog tLog;

	m.DB.tLog.RAConnect("Driver={Microsoft Access Driver (*.mdb)};Initial Catalog=.\\Report\\TempBinLog.mdb");
	// 連線 mdb

	m.DB.Log.RAConnect("Driver={Microsoft Access Driver (*.mdb)};Initial Catalog=.\\Report\\BinLog.mdb");
	// 準備要寫入的 Bin Log

	_RecordsetPtr r = m.DB.tLog.RAGetDisconnectedRs("Select * From CodeLog");

	int iD = 0;
	CString csRecord;
	bool    bExistData = false;
	if (r)
	{
		CRADatabaseLock recordset;
		while (!r->adoEOF)
		{
			m.DB.tLog.GetFieldValue(r, "Code",		tLog.csCode);
			m.DB.tLog.GetFieldValue(r, "Bin",		tLog.iBin );
			m.DB.tLog.GetFieldValue(r, "Booking",	tLog.iBooking );
			m.DB.tLog.GetFieldValue(r, "TestTime",	tLog.dTestTime );
			// 把資料取出來.

			// 直接在這裡 InsertBinLog 太慢.
			// 因為會連很多次浪費時間	
			csSQL.Format("INSERT INTO [CodeLog](Code, TestTime, Bin, Booking ) "
				" VALUES ('%s', '%6.2f', %d, %d);", tLog.csCode, tLog.dTestTime, tLog.iBin, tLog.iBooking );
			
			int nak = E_FAIL;
			nak = m.DB.Log.RAExecuteNoRs(csSQL);
			int i=0;
			while(nak != S_OK)
			{
				i++;
				if( nak != S_OK )
				{
					m.DB.Log.Close();
					m.DB.Log.RAConnect("Driver={Microsoft Access Driver (*.mdb)};Initial Catalog=.\\Report\\BinLog.mdb");
					nak = m.DB.Log.RAExecuteNoRs(csSQL);
					Sleep(10);
					// 如果沒有成功寫入資料就 斷掉重連然後再執行一次
				}

				if(i> _InsertCount)
				{		
					// 超過次數了, 真的沒辦法了. 這筆資料放棄
					break;
				}
				Sleep(1);
			}
			//

			bExistData = true;
			m.m_LotInfoProg.m_lLotInformationStatus++;			
			r->MoveNext();

			Sleep(_Wait);
		}
		// 從 TemoBinLog.mdb 取出資料 然後填入 BinLog.mdb.
	}
	else
		;	// 沒有取到資料

	m.DB.Log.Close();
	m.DB.tLog.Close();
}	
*/
void  CReport::CopyBinLog()
{
	CString csSQL;
	tagTestLog tLog;

	if( S_OK != m.DB.tLog.RAConnect("Driver={Microsoft Access Driver (*.mdb)};Initial Catalog=.\\Report\\TempBinLog.mdb"))
	{
		if( S_OK != m.DB.tLog.RAConnect("Driver={Microsoft Access Driver (*.mdb)};Initial Catalog=.\\Report\\TempBinLog.mdb"))
		{
			m.DB.Log.Close();
			return;
		}
	}
	// 連線 mdb

	if( S_OK != m.DB.Log.RAConnect("Driver={Microsoft Access Driver (*.mdb)};Initial Catalog=.\\Report\\BinLog.mdb"))
	{
		if( S_OK != m.DB.Log.RAConnect("Driver={Microsoft Access Driver (*.mdb)};Initial Catalog=.\\Report\\BinLog.mdb"))
		{
			m.DB.Log.Close();
			m.DB.tLog.Close();
			return;
		}
	}
	// 準備要寫入的 Bin Log

	_RecordsetPtr r = m.DB.tLog.RAGetDisconnectedRs("Select * From CodeLog");

	int iD = 0;
	CString csRecord;
	bool    bExistData = false;
	if (r)
	{
		CRADatabaseLock recordset;
		while (!r->adoEOF)
		{
			m.DB.tLog.GetFieldValue(r, "Code",		tLog.csCode);
			m.DB.tLog.GetFieldValue(r, "Bin",		tLog.iBin );
			m.DB.tLog.GetFieldValue(r, "Booking",	tLog.iBooking );
			m.DB.tLog.GetFieldValue(r, "TestTime",	tLog.dTestTime );
			// 把資料取出來.

			// 直接在這裡 InsertBinLog 太慢.
			// 因為會連很多次浪費時間	
			csSQL.Format("INSERT INTO [CodeLog](Code, TestTime, Bin, Booking ) "
				" VALUES ('%s', '%6.2f', %d, %d);", tLog.csCode, tLog.dTestTime, tLog.iBin, tLog.iBooking );
			
			int nak = E_FAIL;
			nak = m.DB.Log.RAExecuteNoRs(csSQL);
			int i=0;
			while(nak != S_OK)
			{
				i++;
				if( nak != S_OK )
				{
					m.DB.Log.Close();
					m.DB.Log.RAConnect("Driver={Microsoft Access Driver (*.mdb)};Initial Catalog=.\\Report\\BinLog.mdb");
					nak = m.DB.Log.RAExecuteNoRs(csSQL);
					Sleep(10);
					// 如果沒有成功寫入資料就 斷掉重連然後再執行一次
				}

				if(i> _InsertCount)
				{		
					// 超過次數了, 真的沒辦法了. 這筆資料放棄
					break;
				}
				Sleep(1);
			}
			//

			bExistData = true;
			m.m_LotInfoProg.m_lLotInformationStatus++;			
			r->MoveNext();

			Sleep(_Wait);
		}
		// 從 TemoBinLog.mdb 取出資料 然後填入 BinLog.mdb.
	}
	else
	{
		// 沒有取到資料
	}

	m.DB.Log.Close();
	m.DB.tLog.Close();
}


// Delete dbase
static CMutex MutexDelBinLog;
void  CReport::DeleteBinLog()
{
	CSingleLock Lock(&MutexDelBinLog);
	Lock.Lock();


	Lock.Unlock();
}
static CMutex MutexDelTempBinLog;
void  CReport::DeleteTempBinLog()
{
	CSingleLock Lock(&MutexDelTempBinLog);
	Lock.Lock();


	Lock.Unlock();
}

void CReport::DeleteAllSummaryReport()
{
	CFileFind find;
	CString file;
	BOOL bResult = find.FindFile( m.FilePath.SummaryReportPath + "\\" + _Sum1 );
	while(bResult)
	{
		bResult = find.FindNextFile();
		file = find.GetFileName();
		if(file.Find( _Sum2, 0)>-1)
			::DeleteFile( m.FilePath.SummaryReportPath + "\\" + file );
	}
}
