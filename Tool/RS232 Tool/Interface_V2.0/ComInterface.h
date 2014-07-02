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
	bool IsOpen();
	void WriteString(char *buffer, int iSize);
	long GetString(char *buffer);
	void Clear();
	bool Open(int iComNo, int iBaudRate, int iDataBit, int iStopBit, int iParity);
	bool Close();
	CInterface();
	virtual ~CInterface();

protected:
	HANDLE	m_hComm;
};

#endif // !defined(AFX_INTERFACE_H__6F27642D_1423_424E_A24E_AFC53EC252E1__INCLUDED_)
