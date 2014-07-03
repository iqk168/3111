// DriverTestInterfaceTCP.cpp : implementation file
//

#include "stdafx.h"
#include "Deer.h"
#include "DriverTestInterfaceTCP.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDriverTestInterfaceTCP

CDriverTestInterfaceTCP::CDriverTestInterfaceTCP()
{
	iConnected = 0;
	iConnectedNumber = 0;
	m_bConnected = false;
	m_bOverRange = false;
	m.m_singleSocket = NULL;

	csBuffer = _T("");
}

CDriverTestInterfaceTCP::~CDriverTestInterfaceTCP()
{
	TRACE("~CDriverTestInterfaceTCP\n");
}

// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP(CDriverTestInterfaceTCP, CAsyncSocket)
	//{{AFX_MSG_MAP(CDriverTestInterfaceTCP)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0

/////////////////////////////////////////////////////////////////////////////
// CDriverTestInterfaceTCP member functions
static CMutex MutexAccessBuffer;
void CDriverTestInterfaceTCP::SetBuffer(CString csRecvBuffer)
{
	CSingleLock Lock(&MutexAccessBuffer);
	Lock.Lock();

	csBuffer = csRecvBuffer;

	Lock.Unlock();
}
void CDriverTestInterfaceTCP::GetBufferData(CString &csRecvBuffer)
{
	CSingleLock Lock(&MutexAccessBuffer);
	Lock.Lock();
	
	csRecvBuffer = csBuffer;
	
	csBuffer.Empty();
	Lock.Unlock();
}
void CDriverTestInterfaceTCP::GetTotalBufferData(CString &csRecvBuffer)
{
	//
	CString cs = _T("");
	if( m_bOverRange )
	{
		for(int i=0;i<10;i++)
		{
			if( m_Socket[i] != NULL )
			{
				CString csTempBuffer = _T("");
				m_Socket[i]->GetBufferData( csTempBuffer );
				cs += csTempBuffer;
			}		
		}

		csRecvBuffer = cs;
	}
	else
	{
		for(int i=0;i<(int)iConnectedNumber;i++)
		{
			if( m_Socket[i] != NULL )
			{			
				if( m_Socket[i]->GetConnected() )
				{
					CString csTempBuffer = _T("");
					m_Socket[i]->GetBufferData( csTempBuffer );
					cs += csTempBuffer;
				}
			}	
		}

		csRecvBuffer = cs;
	}
	//
}
void CDriverTestInterfaceTCP::OnAccept(int nErrorCode) 
{
#if 1
	if(m.m_singleSocket != NULL)
		return;
	m.m_singleSocket = new CDriverTestInterfaceTCP;
	BOOL bRect = Accept(*m.m_singleSocket);

#else 
	TRACE("OnAccept\n");
	if( nErrorCode == 0 )
	{	
		iConnected = iConnectedNumber % 10;

		//
		if( iConnectedNumber > 9 )
		{
			m_bOverRange = true;
			if( m_Socket[iConnected]->GetConnected() )
				m_Socket[iConnected]->Close();
			
			delete m_Socket[iConnected];
			
			CString csMsg = _T("");
			csMsg.Format("Kill :%d\n", iConnected ); TRACE( csMsg );
		}

		//
		m_Socket[iConnected] = new CDriverTestInterfaceTCP;
		BOOL bRect = Accept(*m_Socket[iConnected]);
		m_Socket[iConnected]->AsyncSelect(FD_READ | FD_WRITE | FD_CLOSE);
		m_Socket[iConnected]->SetConnected();
		
//		m_ClientSocket = m_Socket[iConnected]->m_hSocket;
			
		CString csMsg = _T("");
		csMsg.Format("iConnected :%d\n", iConnected ); TRACE(csMsg);
		iConnectedNumber++;
	}
#endif
	CAsyncSocket::OnAccept(nErrorCode);
}
void CDriverTestInterfaceTCP::SetConnected()
{
	m_bConnected = true;
}
bool CDriverTestInterfaceTCP::GetConnected()
{
	return m_bConnected;
}
void CDriverTestInterfaceTCP::OnClose(int nErrorCode) 
{
	if( nErrorCode == 0 )
	{
	}

	m_bConnected = false;

//	Close();
	delete m.m_singleSocket;
	m.m_singleSocket = NULL;
	CAsyncSocket::OnClose(nErrorCode);
}

void CDriverTestInterfaceTCP::OnConnect(int nErrorCode) 
{
	TRACE("OnConnect\n");
	if( nErrorCode == 0 )
	{
	
	}
	CAsyncSocket::OnConnect(nErrorCode);
}

void CDriverTestInterfaceTCP::OnReceive(int nErrorCode) 
{
#if 1
	char buffer[1000] = {0};
	Receive(buffer, 1000);
	CString cs = buffer;
	cs.TrimRight();

	while(1)
	{
		tagTestProtocol Re = m.m_TestInterface.GetProtocol(cs);
		if(Re.site == 0)
			break;

		//³B²z©R¥O
		CString Reply = m.m_TestInterface.CommandRun(Re);
		Send(Reply.GetBuffer(0),Reply.GetLength());

		Sleep(1);
	}
	
#else
	if( nErrorCode == 0 )
	{
		char buffer[1000] = {0};
		Receive(buffer, 1000);
		
		CString cs = buffer;
		cs.TrimRight();
		//
		CString csMsg = _T("");
		csMsg.Format("%s\n", cs ); TRACE(csMsg);
		SendMessageToMain( cs );
		
		//
		SetBuffer(cs);
	}
#endif
	CAsyncSocket::OnReceive(nErrorCode);
}

void CDriverTestInterfaceTCP::OnSend(int nErrorCode) 
{
	CAsyncSocket::OnSend(nErrorCode);
}

int CDriverTestInterfaceTCP::Receive(void* lpBuf, int nBufLen, int nFlags) 
{
	TRACE("Receive\n");
	return CAsyncSocket::Receive(lpBuf, nBufLen, nFlags);
}

void CDriverTestInterfaceTCP::CloseTCP()
{
	if( m_bOverRange )
	{
		for(int i=0;i<10;i++)
		{
//			if( i != iConnected ) // be delete
			{
				if( m_Socket[i] != NULL )
				{			
					CString csMsg = _T("");
					csMsg.Format("Close: %d\n", i); TRACE(csMsg);
					if( m_Socket[i]->GetConnected() )
						m_Socket[i]->Close();
					
					delete m_Socket[i];
				}
			}
		}		
	}
	else
	{
		for(int i=0;i<(int)iConnectedNumber;i++)
		{
			CString csMsg = _T("");
			csMsg.Format("Close: %d\n", i); TRACE(csMsg);
			if( m_Socket[i] != NULL )
			{			
//				CString csMsg = _T("");
//				csMsg.Format("Close: %d\n", i); TRACE(csMsg);
				if( m_Socket[i]->GetConnected() )
					m_Socket[i]->Close();
				
				delete m_Socket[i];
			}	
		}
	}
}
bool CDriverTestInterfaceTCP::SendToClient(CString csMessage)
{
	csMessage.TrimLeft(); csMessage.TrimRight();
	if( csMessage == "" )
		return false;

	//
	if( m_bOverRange )
	{
		for(int i=0;i<10;i++)
		{
			if( m_Socket[i] != NULL )
				send( m_Socket[i]->m_hSocket, csMessage.GetBuffer(0), csMessage.GetLength(), 0 );			
		}
	}
	else
	{
		for(int i=0;i<(int)iConnectedNumber;i++)
		{
			if( m_Socket[i] != NULL )
			{			
				if( m_Socket[i]->GetConnected() )
					send( m_Socket[i]->m_hSocket, csMessage.GetBuffer(0), csMessage.GetLength(), 0 );
			}	
		}
	}
	//

	return true;
}
void CDriverTestInterfaceTCP::SendMessageToMain(CString csMessage)
{
	csMessage.TrimLeft(); csMessage.TrimRight();
	if( csMessage == "" )
		return;

	/*
	CSampleServerDlg *pMainDlg = (CSampleServerDlg *)AfxGetMainWnd();
	if( pMainDlg->GetSafeHwnd() )
	{
		::SendMessage( pMainDlg->GetSafeHwnd(), 
			WM_MESSAGE_TCP, (WPARAM)&csMessage , (LPARAM)&csMessage );
	}
	*/
}
void CDriverTestInterfaceTCP::GetServerSocketName(CString &csSocketName, unsigned int &iPort)
{
	// port
	CString m_csSocketName = _T("");
	unsigned int m_iPort = 0;
	this->GetSockName( m_csSocketName, m_iPort );
	iPort = m_iPort;

	/*
		I have no idea, why "CAsyncSocket object" 
		GetSocketName, IP address always return "0.0.0.0"
		Maybe it just follow the DNS list, then the first is "0.0.0.0"
		I have no choise. I create a new "host name", 
		And include into the GetServerSocketName function..
	*/

	// host name
	char szHostName[64];
	memset(szHostName, 0, sizeof(szHostName));
	gethostname(szHostName, sizeof(szHostName));
	HOSTENT* pHostent = gethostbyname(szHostName);

	//	
	BYTE *p;
	p =(BYTE *)pHostent->h_addr;
	CString csLocalIP = _T("");
	csLocalIP.Format("%d.%d.%d.%d", p[0], p[1], p[2], p[3]);
	m_csSocketName = csLocalIP;
	csSocketName = m_csSocketName;

	//
	CString csMsg = _T("");
	csMsg.Format("SocketName: %s, Port: %d\n", m_csSocketName, m_iPort ); TRACE( csMsg );
}