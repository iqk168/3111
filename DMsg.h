// DMsg.h: interface for the CDMsg class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DMSG_H__10352FE3_6752_4C51_8584_4F505DBD177A__INCLUDED_)
#define AFX_DMSG_H__10352FE3_6752_4C51_8584_4F505DBD177A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CDMsg  
{
public:
	CDMsg();
	virtual ~CDMsg();

public:
	CArray<CString, CString> m_DMsg;
	CString m_ReportPath;	//ex: C:\\Report.csv

public:
	void SetReportPath(CString csFilePath);
	void DMsgClear();
	void DMsg(CString csMsg, bool bPass = true);
	void DMsgEnd();
	void ExportDMsgReport();
};

#endif // !defined(AFX_DMSG_H__10352FE3_6752_4C51_8584_4F505DBD177A__INCLUDED_)
