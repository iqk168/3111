// Interface.h: interface for the CInterface class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_INTERFACE_H__6F27642D_1423_424E_A24E_AFC53EC252E1__INCLUDED_)
#define AFX_INTERFACE_H__6F27642D_1423_424E_A24E_AFC53EC252E1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CInterface  
{
public:
	void WriteString(char *buffer, int iSize);
	void WriteTelegram(CString tele);
	long GetString(char *buffer);
	void WriteString(char c, int iSize);
	void Clear();
	bool Open(int iComNo, int iBaudRate = 9600, CString csHeader = "<",
		CString csTail = ">", int iDataBit = 1, int iStopBit =0, int iParityCheck = 0);

	bool GetTelegram(CString &csTelegram);
	bool Close();
	CInterface();
	virtual ~CInterface();
	CString m_csTelegramBuffer;
	bool PickupTelegram(CString &csTelegram);

	bool m_newData;
	long m_newDataLength;
	unsigned char m_csNewData[1000];

protected:
	HANDLE	m_hComm;

	CString m_csHeader;
	CString m_csTail;

};

#endif // !defined(AFX_INTERFACE_H__6F27642D_1423_424E_A24E_AFC53EC252E1__INCLUDED_)
