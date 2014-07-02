// RADatabase.h: interface for the CRADatabase class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RADATABASE_H__1ED0D67C_5A19_4695_9E6D_3E51D86E5AC9__INCLUDED_)
#define AFX_RADATABASE_H__1ED0D67C_5A19_4695_9E6D_3E51D86E5AC9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "msado15.tlh"

class CRADatabase  
{
public:
	void SetDataLog(CString csLog, CString csFileName);
	HRESULT RAConnect(const char *ConnectionString);
	HRESULT RAExecuteNoRs(const char *SqlStatement);
	_RecordsetPtr RAExecuteRs(const char *SqlStatement);
	_RecordsetPtr RAGetDisconnectedRs(const char *SqlStatement);
	CRADatabase();
	virtual ~CRADatabase();

	BOOL GetFieldValue(_RecordsetPtr r, LPCTSTR lpFieldName, int& nValue);
	BOOL GetFieldValue(_RecordsetPtr r, int nIndex, int& nValue);
	BOOL GetFieldValue(_RecordsetPtr r, LPCTSTR lpFieldName, long& lValue);
	BOOL GetFieldValue(_RecordsetPtr r, int nIndex, long& lValue);
	BOOL GetFieldValue(_RecordsetPtr r, LPCTSTR lpFieldName, unsigned long& ulValue);
	BOOL GetFieldValue(_RecordsetPtr r, int nIndex, unsigned long& ulValue);
	BOOL GetFieldValue(_RecordsetPtr r, LPCTSTR lpFieldName, double& dbValue);
	BOOL GetFieldValue(_RecordsetPtr r, int nIndex, double& dbValue);
	BOOL GetFieldValue(_RecordsetPtr r, LPCTSTR lpFieldName, CString& strValue, CString strDateFormat = _T(""));
	BOOL GetFieldValue(_RecordsetPtr r, int nIndex, CString& strValue, CString strDateFormat = _T(""));
	BOOL GetFieldValue(_RecordsetPtr r, LPCTSTR lpFieldName, COleDateTime& time);
	BOOL GetFieldValue(_RecordsetPtr r, int nIndex, COleDateTime& time);
	BOOL GetFieldValue(_RecordsetPtr r, int nIndex, bool& bValue);
	BOOL GetFieldValue(_RecordsetPtr r, LPCTSTR lpFieldName, bool& bValue);
	BOOL GetFieldValue(_RecordsetPtr r, int nIndex, COleCurrency& cyValue);
	BOOL GetFieldValue(_RecordsetPtr r, LPCTSTR lpFieldName, COleCurrency& cyValue);
	BOOL GetFieldValue(_RecordsetPtr r, int nIndex, _variant_t& vtValue);
	BOOL GetFieldValue(_RecordsetPtr r, LPCTSTR lpFieldName, _variant_t& vtValue);

	void Close();

private:
	char m_ConnectionString[MAX_PATH];
	_RecordsetPtr m_Recordset;
	_CommandPtr m_Command;
	_ConnectionPtr m_Connection;

protected:
//	void Close();
	CString IntToStr(int nVal);
	CString LongToStr(long lVal);
	CString ULongToStr(unsigned long ulVal);
	CString DblToStr(double dblVal, int ndigits);
	CString DblToStr(float fltVal);
};

#endif // !defined(AFX_RADATABASE_H__1ED0D67C_5A19_4695_9E6D_3E51D86E5AC9__INCLUDED_)
