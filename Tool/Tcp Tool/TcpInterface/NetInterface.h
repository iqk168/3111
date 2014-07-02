// NetInterface.h: interface for the CNetInterface class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_NETINTERFACE_H__F4DBF14D_B1A2_4101_B82E_1F9793E68EC9__INCLUDED_)
#define AFX_NETINTERFACE_H__F4DBF14D_B1A2_4101_B82E_1F9793E68EC9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <winsock.h>
#include <afxmt.h>
#pragma comment(lib, "wsock32.lib")

class CAutoLock
{
public:
	CAutoLock(CSyncObject &mutex) : m_mutex(mutex) { m_mutex.Lock();}
	~CAutoLock() {m_mutex.Unlock();}

private:
	CSyncObject &m_mutex;
};

class CNetInterface  
{
public:
	bool GetString(char *buffer);
	bool Close();
	bool IsOpen();
	bool WriteString(char *buffer, int iSize);
	BOOL Open(char *IPaddress, int Port);
	CNetInterface();
	virtual ~CNetInterface();

	SOCKET m_ClientSocket;
	char   m_RecvBuffer[255];
};

#endif // !defined(AFX_NETINTERFACE_H__F4DBF14D_B1A2_4101_B82E_1F9793E68EC9__INCLUDED_)
