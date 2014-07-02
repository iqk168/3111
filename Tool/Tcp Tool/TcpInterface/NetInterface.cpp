// NetInterface.cpp: implementation of the CNetInterface class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TcpInterface.h"
#include "NetInterface.h"
#include "TcpInterfaceDlg.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

DWORD WINAPI WorkerThread(LPVOID lpPtr)
{
	CNetInterface *pThis = (CNetInterface*) lpPtr;

	while(TRUE)
	{
		memset(pThis->m_RecvBuffer, sizeof(pThis->m_RecvBuffer), 0);

		pThis->GetString(pThis->m_RecvBuffer);
		if(pThis->m_ClientSocket == NULL)
			return 0;


		CString cs;
		cs.Format("R%d: %s", theApp.m_iIndex++, pThis->m_RecvBuffer);

		CTcpInterfaceDlg *p = (CTcpInterfaceDlg *) theApp.m_pMainWnd;
		if(p->GetSafeHwnd() != NULL)
			p->AddString(cs.GetBuffer(cs.GetLength()));

		// Auto Response
		CString csGet = _T("");
		csGet.Format("%s", pThis->m_RecvBuffer);
		if(  csGet == "<<Start>>" )
		{
			CString csResponse = _T("");
			csResponse.Format("<<Ready>>");
			pThis->WriteString( csResponse.GetBuffer(0), csResponse.GetLength() );
		}
		else if(  csGet == "<<Go>>" )
		{
			CString csResponse = _T("");
			csResponse.Format("<<Bin=1>>");
			pThis->WriteString( csResponse.GetBuffer(0), csResponse.GetLength() );
		}

		Sleep(1);
	}

	return 0;
}

CNetInterface::CNetInterface()
{
	m_ClientSocket = NULL;
}

CNetInterface::~CNetInterface()
{

}

static CMutex MutexOpen;
BOOL CNetInterface::Open(char *IPaddress, int Port)
{
//	CAutoLock lock(MutexOpen);

	WSADATA wsaData;
	memset(&wsaData, 0, sizeof(wsaData));
	if(WSAStartup(MAKEWORD(2,2), &wsaData) != 0)
	{
		char Buffer[100];
		sprintf(Buffer, "WSAStartup Failed \n", WSAGetLastError());
		AfxMessageBox(Buffer);
		return false;
	}

	m_ClientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	
	if(m_ClientSocket == INVALID_SOCKET)
	{
		char Buffer[100];
		sprintf(Buffer, "Fail create socket [%d]\n", WSAGetLastError());
		AfxMessageBox(Buffer);
		WSACleanup();
		m_ClientSocket = NULL;
		return false;
	}

	SOCKADDR_IN addr;
// 	addr.sin_family	= AF_INET;
// 	addr.sin_port = htons(nPort);
// 	addr.sin_addr.s_addr = (unsigned long)GetLocalIPToLong();

	addr.sin_family	= AF_INET;
	addr.sin_port = htons(Port);
 	addr.sin_addr.s_addr = inet_addr(IPaddress);//INADDR_ANY;

	if(connect(m_ClientSocket, (SOCKADDR*)&addr, sizeof(addr)) == SOCKET_ERROR)
	{
		char Buffer[100];
		sprintf(Buffer, "Connect Error [%d]\n", WSAGetLastError());
		AfxMessageBox(Buffer);
		WSACleanup();
		m_ClientSocket = NULL;
		return false;
	}

	DWORD dwThreadId = 0;
	HANDLE handle = CreateThread(NULL, 0, &WorkerThread, this, 0, &dwThreadId);

	TRACE("OK");
	return true;
}

bool CNetInterface::Close()
{
//	if(m_ClientSocket == NULL)
//		return true;

	m_ClientSocket = NULL;
	WSACleanup();
	return closesocket(m_ClientSocket) == 0 ? true : false;
}

bool CNetInterface::WriteString(char *buffer, int iSize)
{
	if(send(m_ClientSocket, buffer, iSize, 0) == SOCKET_ERROR)
	{
		m_ClientSocket = NULL;
		return false;
	}

	return true;
}

bool CNetInterface::GetString(char *buffer)
{
	char tempBuffer[255] = {0};

	if(recv(m_ClientSocket, tempBuffer, sizeof(tempBuffer), 0) == SOCKET_ERROR)
	{
		closesocket( m_ClientSocket );
		m_ClientSocket = NULL;
		return false;
	}

	memcpy(buffer, tempBuffer, sizeof(tempBuffer));
	return true;
}

bool CNetInterface::IsOpen()
{
	return m_ClientSocket == NULL ? false : true;
}


