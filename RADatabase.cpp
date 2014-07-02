// RADatabase.cpp: implementation of the CRADatabase class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "RADatabase.h"
#include <cmath>
#include <afxmt.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CString CRADatabase::IntToStr(int nVal)
{
	CString strRet;
	char buff[10];
	
	itoa(nVal, buff, 10);
	strRet = buff;
	return strRet;
}

CString CRADatabase::LongToStr(long lVal)
{
	CString strRet;
	char buff[20];
	
	ltoa(lVal, buff, 10);
	strRet = buff;
	return strRet;
}

CString CRADatabase::ULongToStr(unsigned long ulVal)
{
	CString strRet;
	char buff[20];
	
	ultoa(ulVal, buff, 10);
	strRet = buff;
	return strRet;

}


CString CRADatabase::DblToStr(double dblVal, int ndigits)
{
	CString strRet;
	char buff[50];

   _gcvt(dblVal, ndigits, buff);
	strRet = buff;
	return strRet;
}

CString CRADatabase::DblToStr(float fltVal)
{
	CString strRet = _T("");
	char buff[50];
	
   _gcvt(fltVal, 10, buff);
	strRet = buff;
	return strRet;
}

CRADatabase::CRADatabase()
{
	try
	{
		// Initialize COM
		CoInitialize(NULL);
		// Initialize ADO
		m_Command.CreateInstance(__uuidof(Command));
		m_Recordset.CreateInstance(__uuidof(Recordset));
		m_Connection.CreateInstance(__uuidof(Connection));	
	}
	catch(_com_error &e)
	{
		printf("Description = %s\n", (char*) e.Description());   
	}
	catch(...)
	{
	}
}

CRADatabase::~CRADatabase()
{
	// Clean up ADO objects
	try
	{
		if (m_Recordset)
		{
			if(m_Recordset->State == adStateOpen)
			{
				m_Recordset->Close();
				m_Recordset.Release();			
			}
		}		
		if (m_Connection)
		{
			if(m_Connection->State == adStateOpen)
			{
				m_Connection->Close();
				m_Connection.Release();			
			}
		}

		m_Connection = NULL;
		m_Command = NULL;
		m_Recordset = NULL;

		CoUninitialize();
	}
	catch(_com_error &e)
	{
		printf("Description = %s\n", (char*) e.Description());   
	}
	catch(...)
	{
	}
}

HRESULT CRADatabase::RAConnect(const char *ConnectionString)
{
	// Attemp a connect, reconnect, or leave if already connected
	if(strlen(ConnectionString) > 0)
	{
		try
		{
			if(m_Connection == NULL)
				m_Connection.CreateInstance(__uuidof(Connection));
			if(0 == _stricmp(ConnectionString, m_ConnectionString) && 
				m_Connection->State == adStateOpen)
				return S_OK;
			else
			{
				if(m_Connection->State == adStateOpen)
					m_Connection->Close();
				sprintf(m_ConnectionString, ConnectionString);
			}
			// Perform the connect
			if(S_OK == m_Connection->Open((char*)m_ConnectionString, L"", L"", adModeUnknown))
				return S_OK;
		}
		catch(_com_error &e)
		{
			printf("Description = %s\n", (char*) e.Description());   
			return E_FAIL;
		}
		catch(...)
		{
			return E_FAIL;
		}
	}
	return E_FAIL;
}

_RecordsetPtr CRADatabase::RAGetDisconnectedRs(const char *SqlStatement)
{
	// Attempt get a disconnected RS and terminate the connection to the DB
	if(strlen(SqlStatement) > 0)
	{		
		try
		{
			if(m_Connection == NULL || m_Connection->State == adStateClosed)
				RAConnect(m_ConnectionString);

			if(m_Recordset)
			{
				if(m_Recordset->State == adStateOpen)
					m_Recordset->Close();
			}
			else
			{				
				m_Recordset.CreateInstance(__uuidof(Recordset));
			}

			m_Recordset->CursorLocation = adUseClient;
			
			m_Recordset->Open(SqlStatement,
				m_Connection.GetInterfacePtr(),
				adOpenForwardOnly, 
				adLockOptimistic, 
				-1);

			m_Recordset->PutRefActiveConnection(NULL); 
			
			if(m_Connection->GetState() == adStateOpen)
				m_Connection->Close();
			
			return m_Recordset;
		}
		catch(_com_error &e)
		{
			CString cs = _T("");
			cs.Format("Description = %s\n", (char*) e.Description());
 			AfxMessageBox(cs);
			SetDataLog(cs, ".\\Log\\DBLog.log");
			Close();

			return NULL;
		}
		catch(...)
		{
			return NULL;
		}
	}
	return NULL;
}


HRESULT CRADatabase::RAExecuteNoRs(const char *SqlStatement)
{
	// Attempt to execute a SQL statement and leave connection open
	if (strlen(SqlStatement) > 0)
	{		
		try
		{
			if(m_Connection == NULL || m_Connection->State == adStateClosed)
				RAConnect(m_ConnectionString);

			m_Connection->Execute(SqlStatement, NULL, adExecuteNoRecords );

			return S_OK;
		}
		catch(_com_error &e)
		{
			CString cs = _T("");
			cs.Format("Description = %s\n", (char*) e.Description());
//			AfxMessageBox(cs);
			SetDataLog(cs, ".\\Log\\DBLog.log");
			Close();
			return E_FAIL;
		}
		catch(...)
		{
			return E_FAIL;
		}
	}
	return E_FAIL;
}

_RecordsetPtr CRADatabase::RAExecuteRs(const char *SqlStatement)
{
	// Attempt to execute a SQL statement, return the RS, and leave connection open
	if (strlen(SqlStatement) > 0)
	{		
		try
		{
			if(m_Connection == NULL || m_Connection->State == adStateClosed)
				RAConnect(m_ConnectionString);
			if(m_Recordset)
			{
				if(m_Recordset->State == adStateOpen)
					m_Recordset->Close();
			}
			else
			{				
				m_Recordset.CreateInstance(__uuidof(Recordset));
			}
			
			m_Command->ActiveConnection = m_Connection;
			m_Command->CommandType = adCmdText;
			m_Command->CommandText = SqlStatement;
			
			_variant_t vNull;
			vNull.vt = VT_ERROR;
			vNull.scode = DISP_E_PARAMNOTFOUND;
			
			return m_Command->Execute(&vNull, &vNull, adCmdText);
			
//			m_Recordset = m_Command->Execute(&vNull, &vNull, adCmdText);
//			return m_Recordset;
		}
		catch(_com_error &e)
		{
			printf("Description = %s\n", (char*) e.Description());   
			Close();
		}
		catch(...)
		{
		}
	}

	return NULL;
}

/////////////////////////////////////////////////////////////////////
// Add Functions

BOOL CRADatabase::GetFieldValue(_RecordsetPtr r, LPCTSTR lpFieldName, double& dbValue)
{	
	double val = (double)NULL;
	_variant_t vtFld;
	
	try
	{
		vtFld = r->Fields->GetItem(lpFieldName)->Value;
		switch(vtFld.vt)
		{
		case VT_R4:
			val = vtFld.fltVal;
			break;
		case VT_R8:
			val = vtFld.dblVal;
			break;
		case VT_DECIMAL:
			//Corrected by José Carlos Martínez Galán
			val = vtFld.decVal.Lo32;
			val *= (vtFld.decVal.sign == 128)? -1 : 1;
			val /= pow(10, vtFld.decVal.scale); 
			break;
		case VT_UI1:
			val = vtFld.iVal;
			break;
		case VT_I2:
		case VT_I4:
			val = vtFld.lVal;
			break;
		case VT_INT:
			val = vtFld.intVal;
			break;
		case VT_NULL:
		case VT_EMPTY:
			val = 0;
			break;
		default:
			val = vtFld.dblVal;
		}
		dbValue = val;
		return TRUE;
	}
	catch(_com_error &e)
	{
		printf("Description = %s\n", (char*) e.Description());   
		return FALSE;
	}
}


BOOL CRADatabase::GetFieldValue(_RecordsetPtr r, int nIndex, double& dbValue)
{	
	double val = (double)NULL;
	_variant_t vtFld;
	_variant_t vtIndex;

	vtIndex.vt = VT_I2;
	vtIndex.iVal = nIndex;
	
	try
	{
		vtFld = r->Fields->GetItem(vtIndex)->Value;
		switch(vtFld.vt)
		{
		case VT_R4:
			val = vtFld.fltVal;
			break;
		case VT_R8:
			val = vtFld.dblVal;
			break;
		case VT_DECIMAL:
			//Corrected by José Carlos Martínez Galán
			val = vtFld.decVal.Lo32;
			val *= (vtFld.decVal.sign == 128)? -1 : 1;
			val /= pow(10, vtFld.decVal.scale); 
			break;
		case VT_UI1:
			val = vtFld.iVal;
			break;
		case VT_I2:
		case VT_I4:
			val = vtFld.lVal;
			break;
		case VT_INT:
			val = vtFld.intVal;
			break;
		case VT_NULL:
		case VT_EMPTY:
			val = 0;
			break;
		default:
			val = 0;
		}
		dbValue = val;
		return TRUE;
	}
	catch(_com_error &e)
	{
		printf("Description = %s\n", (char*) e.Description());   
		return FALSE;
	}
}


BOOL CRADatabase::GetFieldValue(_RecordsetPtr r, LPCTSTR lpFieldName, long& lValue)
{
	long val = (long)NULL;
	_variant_t vtFld;
	
	try
	{
		vtFld = r->Fields->GetItem(lpFieldName)->Value;
		if(vtFld.vt != VT_NULL && vtFld.vt != VT_EMPTY)
			val = vtFld.lVal;
		lValue = val;
		return TRUE;
	}
	catch(_com_error &e)
	{
		printf("Description = %s\n", (char*) e.Description());   
		return FALSE;
	}
}

BOOL CRADatabase::GetFieldValue(_RecordsetPtr r, int nIndex, long& lValue)
{
	long val = (long)NULL;
	_variant_t vtFld;
	_variant_t vtIndex;
	
	vtIndex.vt = VT_I2;
	vtIndex.iVal = nIndex;

	try
	{
		vtFld = r->Fields->GetItem(vtIndex)->Value;
		if(vtFld.vt != VT_NULL && vtFld.vt != VT_EMPTY)
			val = vtFld.lVal;
		lValue = val;
		return TRUE;
	}
	catch(_com_error &e)
	{
		printf("Description = %s\n", (char*) e.Description());   
		return FALSE;
	}
}


BOOL CRADatabase::GetFieldValue(_RecordsetPtr r, LPCTSTR lpFieldName, unsigned long& ulValue)
{
	long val = (long)NULL;
	_variant_t vtFld;
	
	try
	{
		vtFld = r->Fields->GetItem(lpFieldName)->Value;
		if(vtFld.vt != VT_NULL && vtFld.vt != VT_EMPTY)
			val = vtFld.ulVal;
		ulValue = val;
		return TRUE;
	}
	catch(_com_error &e)
	{
		printf("Description = %s\n", (char*) e.Description());   
		return FALSE;
	}
}

BOOL CRADatabase::GetFieldValue(_RecordsetPtr r, int nIndex, unsigned long& ulValue)
{
	long val = (long)NULL;
	_variant_t vtFld;
	_variant_t vtIndex;
	
	vtIndex.vt = VT_I2;
	vtIndex.iVal = nIndex;

	try
	{
		vtFld = r->Fields->GetItem(vtIndex)->Value;
		if(vtFld.vt != VT_NULL && vtFld.vt != VT_EMPTY)
			val = vtFld.ulVal;
		ulValue = val;
		return TRUE;
	}
	catch(_com_error &e)
	{
		printf("Description = %s\n", (char*) e.Description());   
		return FALSE;
	}
}

BOOL CRADatabase::GetFieldValue(_RecordsetPtr r, LPCTSTR lpFieldName, int& nValue)
{
	int val = NULL;
	_variant_t vtFld;
	
	try
	{
		vtFld = r->Fields->GetItem(lpFieldName)->Value;
		switch(vtFld.vt)
		{
		case VT_BOOL:
			val = vtFld.boolVal;
			break;
		case VT_I2:
		case VT_UI1:
			val = vtFld.iVal;
			break;
		case VT_INT:
			val = vtFld.intVal;
			break;
		case VT_NULL:
		case VT_EMPTY:
			val = 0;
			break;
		default:
			val = vtFld.iVal;
		}	
		nValue = val;
		return TRUE;
	}
	catch(_com_error &e)
	{
		printf("Description = %s\n", (char*) e.Description());   
		return FALSE;
	}
}

BOOL CRADatabase::GetFieldValue(_RecordsetPtr r, int nIndex, int& nValue)
{
	int val = (int)NULL;
	_variant_t vtFld;
	_variant_t vtIndex;
	
	vtIndex.vt = VT_I2;
	vtIndex.iVal = nIndex;

	try
	{
		vtFld = r->Fields->GetItem(vtIndex)->Value;
		switch(vtFld.vt)
		{
		case VT_BOOL:
			val = vtFld.boolVal;
			break;
		case VT_I2:
		case VT_UI1:
			val = vtFld.iVal;
			break;
		case VT_INT:
			val = vtFld.intVal;
			break;
		case VT_NULL:
		case VT_EMPTY:
			val = 0;
			break;
		default:
			val = vtFld.iVal;
		}	
		nValue = val;
		return TRUE;
	}
	catch(_com_error &e)
	{
		printf("Description = %s\n", (char*) e.Description());   
		return FALSE;
	}
}

BOOL CRADatabase::GetFieldValue(_RecordsetPtr r, LPCTSTR lpFieldName, CString& strValue, CString strDateFormat)
{
	CString str = _T("");
	_variant_t vtFld;

	try
	{
		vtFld = r->Fields->GetItem(lpFieldName)->Value;
		switch(vtFld.vt) 
		{
		case VT_R4:
			str = DblToStr(vtFld.fltVal);
			break;
		case VT_R8:
			str = DblToStr(vtFld.dblVal, 32);
			break;
		case VT_BSTR:
			str = vtFld.bstrVal;
			break;
		case VT_I2:
		case VT_UI1:
			str = IntToStr(vtFld.iVal);
			break;
		case VT_INT:
			str = IntToStr(vtFld.intVal);
			break;
		case VT_I4:
			str = LongToStr(vtFld.lVal);
			break;
		case VT_UI4:
			str = ULongToStr(vtFld.ulVal);
			break;
		case VT_DECIMAL:
			{
			//Corrected by José Carlos Martínez Galán
			double val = vtFld.decVal.Lo32;
			val *= (vtFld.decVal.sign == 128)? -1 : 1;
			val /= pow(10, vtFld.decVal.scale); 
			str = DblToStr(val, 32);
			}
			break;
		case VT_DATE:
			{
				COleDateTime dt(vtFld);

				if(strDateFormat.IsEmpty())
					strDateFormat = _T("%Y-%m-%d %H:%M:%S");
				str = dt.Format(strDateFormat);
			}
			break;
		case VT_EMPTY:
		case VT_NULL:
			str.Empty();
			break;
		case VT_BOOL:
			str = vtFld.boolVal == VARIANT_TRUE? 'T':'F';
			break;
		default:
			str.Empty();
			return FALSE;
		}
		strValue = str;
		return TRUE;
	}
	catch(_com_error &e)
	{
		printf("Description = %s\n", (char*) e.Description());   
		return FALSE;
	}
}

BOOL CRADatabase::GetFieldValue(_RecordsetPtr r, int nIndex, CString& strValue, CString strDateFormat)
{
	CString str = _T("");
	_variant_t vtFld;
	_variant_t vtIndex;

	vtIndex.vt = VT_I2;
	vtIndex.iVal = nIndex;
	
	try
	{
		vtFld = r->Fields->GetItem(vtIndex)->Value;
		switch(vtFld.vt) 
		{
		case VT_R4:
			str = DblToStr(vtFld.fltVal);
			break;
		case VT_R8:
			str = DblToStr(vtFld.dblVal, 32);
			break;
		case VT_BSTR:
			str = vtFld.bstrVal;
			break;
		case VT_I2:
		case VT_UI1:
			str = IntToStr(vtFld.iVal);
			break;
		case VT_INT:
			str = IntToStr(vtFld.intVal);
			break;
		case VT_I4:
			str = LongToStr(vtFld.lVal);
			break;
		case VT_UI4:
			str = ULongToStr(vtFld.ulVal);
			break;
		case VT_DECIMAL:
			{
			//Corrected by José Carlos Martínez Galán
			double val = vtFld.decVal.Lo32;
			val *= (vtFld.decVal.sign == 128)? -1 : 1;
			val /= pow(10, vtFld.decVal.scale); 
			str = DblToStr(val, 32);
			}
			break;
		case VT_DATE:
			{
				COleDateTime dt(vtFld);
				
				if(strDateFormat.IsEmpty())
					strDateFormat = _T("%Y-%m-%d %H:%M:%S");
				str = dt.Format(strDateFormat);
			}
			break;
		case VT_BOOL:
			str = vtFld.boolVal == VARIANT_TRUE? 'T':'F';
			break;
		case VT_EMPTY:
		case VT_NULL:
			str.Empty();
			break;
		default:
			str.Empty();
			return FALSE;
		}
		strValue = str;
		return TRUE;
	}
	catch(_com_error &e)
	{
		printf("Description = %s\n", (char*) e.Description());   
		return FALSE;
	}
}

BOOL CRADatabase::GetFieldValue(_RecordsetPtr r, LPCTSTR lpFieldName, COleDateTime& time)
{
	_variant_t vtFld;
	
	try
	{
		vtFld = r->Fields->GetItem(lpFieldName)->Value;
		switch(vtFld.vt) 
		{
		case VT_DATE:
			{
				COleDateTime dt(vtFld);
				time = dt;
			}
			break;
		case VT_EMPTY:
		case VT_NULL:
			time.SetStatus(COleDateTime::null);
			break;
		default:
			return FALSE;
		}
		return TRUE;
	}
	catch(_com_error &e)
	{
		printf("Description = %s\n", (char*) e.Description());   
		return FALSE;
	}
}

BOOL CRADatabase::GetFieldValue(_RecordsetPtr r, int nIndex, COleDateTime& time)
{
	_variant_t vtFld;
	_variant_t vtIndex;
	
	vtIndex.vt = VT_I2;
	vtIndex.iVal = nIndex;
	
	try
	{
		vtFld = r->Fields->GetItem(vtIndex)->Value;
		switch(vtFld.vt) 
		{
		case VT_DATE:
			{
				COleDateTime dt(vtFld);
				time = dt;
			}
			break;
		case VT_EMPTY:
		case VT_NULL:
			time.SetStatus(COleDateTime::null);
			break;
		default:
			return FALSE;
		}
		return TRUE;
	}
	catch(_com_error &e)
	{
		printf("Description = %s\n", (char*) e.Description());   
		return FALSE;
	}
}

BOOL CRADatabase::GetFieldValue(_RecordsetPtr r, LPCTSTR lpFieldName, bool& bValue)
{
	_variant_t vtFld;
	
	try
	{
		vtFld = r->Fields->GetItem(lpFieldName)->Value;
		switch(vtFld.vt) 
		{
		case VT_BOOL:
			bValue = vtFld.boolVal == 0 ? false : true;
			break;
		case VT_EMPTY:
		case VT_NULL:
			bValue = false;
			break;
		default:
			return FALSE;
		}
		return TRUE;
	}
	catch(_com_error &e)
	{
		printf("Description = %s\n", (char*) e.Description());   
		return FALSE;
	}
}

BOOL CRADatabase::GetFieldValue(_RecordsetPtr r, int nIndex, bool& bValue)
{
	_variant_t vtFld;
	_variant_t vtIndex;
	
	vtIndex.vt = VT_I2;
	vtIndex.iVal = nIndex;
	
	try
	{
		vtFld = r->Fields->GetItem(vtIndex)->Value;
		switch(vtFld.vt) 
		{
		case VT_BOOL:
			bValue = vtFld.boolVal == 0 ? false : true;
			break;
		case VT_EMPTY:
		case VT_NULL:
			bValue = false;
			break;
		default:
			return FALSE;
		}
		return TRUE;
	}
	catch(_com_error &e)
	{
		printf("Description = %s\n", (char*) e.Description());   
		return FALSE;
	}
}

BOOL CRADatabase::GetFieldValue(_RecordsetPtr r, LPCTSTR lpFieldName, COleCurrency& cyValue)
{
	_variant_t vtFld;
	
	try
	{
		vtFld = r->Fields->GetItem(lpFieldName)->Value;
		switch(vtFld.vt) 
		{
		case VT_CY:
			cyValue = (CURRENCY)vtFld.cyVal;
			break;
		case VT_EMPTY:
		case VT_NULL:
			{
			cyValue = COleCurrency();
			cyValue.m_status = COleCurrency::null;
			}
			break;
		default:
			return FALSE;
		}
		return TRUE;
	}
	catch(_com_error &e)
	{
		printf("Description = %s\n", (char*) e.Description());   
		return FALSE;
	}
}

BOOL CRADatabase::GetFieldValue(_RecordsetPtr r, int nIndex, COleCurrency& cyValue)
{
	_variant_t vtFld;
	_variant_t vtIndex;
	
	vtIndex.vt = VT_I2;
	vtIndex.iVal = nIndex;
	
	try
	{
		vtFld = r->Fields->GetItem(vtIndex)->Value;
		switch(vtFld.vt) 
		{
		case VT_CY:
			cyValue = (CURRENCY)vtFld.cyVal;
			break;
		case VT_EMPTY:
		case VT_NULL:
			{
			cyValue = COleCurrency();
			cyValue.m_status = COleCurrency::null;
			}
			break;
		default:
			return FALSE;
		}
		return TRUE;
	}
	catch(_com_error &e)
	{
		printf("Description = %s\n", (char*) e.Description());   
		return FALSE;
	}
}

BOOL CRADatabase::GetFieldValue(_RecordsetPtr r, LPCTSTR lpFieldName, _variant_t& vtValue)
{
	try
	{
		vtValue = r->Fields->GetItem(lpFieldName)->Value;
		return TRUE;
	}
	catch(_com_error &e)
	{
		printf("Description = %s\n", (char*) e.Description());   
		return FALSE;
	}
}

BOOL CRADatabase::GetFieldValue(_RecordsetPtr r, int nIndex, _variant_t& vtValue)
{
	_variant_t vtIndex;
	
	vtIndex.vt = VT_I2;
	vtIndex.iVal = nIndex;
	
	try
	{
		vtValue = r->Fields->GetItem(vtIndex)->Value;
		return TRUE;
	}
	catch(_com_error &e)
	{
		printf("Description = %s\n", (char*) e.Description());   
		return FALSE;
	}
}

void CRADatabase::Close()
{
	if(m_Connection != NULL && m_Connection->State == adStateOpen)
		m_Connection->Close();
}

static CMutex MutexSetDatabaseLog;
void CRADatabase::SetDataLog(CString csLog, CString csFileName)
{
	CSingleLock Lock(&MutexSetDatabaseLog);
	Lock.Lock();
	
	CFile file;
	file.Open(csFileName, CFile::modeCreate | CFile::modeWrite
		| CFile::modeNoTruncate | CFile::shareDenyNone, NULL);

	file.SeekToEnd();

	CString cs;
	cs.Format("%s\r\n", csLog);
	file.Write(cs.GetBuffer(0), cs.GetLength());
	file.Close();

	Lock.Unlock();
}
