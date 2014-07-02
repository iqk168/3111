// InterfaceTcp.cpp : implementation file
//

#include "stdafx.h"
#include "Deer.h"
#include "InterfaceTcp.h"

#include <afxsock.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CInterfaceTcp

CInterfaceTcp::CInterfaceTcp()
{
	m_ClientSocket = NULL;

	m_header = _T("");
	m_tail = _T("");
	m_binheader = _T("");
	m_go = _T("");
	m_ready = _T("");
	m_start = _T("");
}

CInterfaceTcp::~CInterfaceTcp()
{
	
}
void CInterfaceTcp::SetInterface(CString header, 
								 CString taill, 
								 CString binheader, 
								 CString go, 
								 CString ready, 
								 CString start)
{
	m_tail      = taill;
	m_header	= header;
	m_binheader = binheader;
	m_go		= go;
	m_ready		= ready;
	m_start		= start;
}

void CInterfaceTcp::OnAccept(int nErrorCode) 
{	
	if( nErrorCode == 0 )
	{
		CInterfaceTcp *pClient = new CInterfaceTcp;
		Accept(*pClient);
		pClient->SetInterface( m.m_TcpipInterfaceSetting.m_csCmdHeader, 
		m.m_TcpipInterfaceSetting.m_csCmdTailHeader,
		m.m_TcpipInterfaceSetting.m_csCmdBin,
		m.m_TcpipInterfaceSetting.m_csCmdGo,
		m.m_TcpipInterfaceSetting.m_csCmdReady,
		m.m_TcpipInterfaceSetting.m_csCmdStart );
		m_ClientSocket = pClient->m_hSocket;
	}
	else
	{
		// Accept Fail
	}
}

void CInterfaceTcp::OnReceive(int nErrorCode) 
{
	CSingleLock lock(&TcpMutex);
	lock.Lock();

	// Lance: 這邊是 Socket 收到訊息後要處理的
	char buffer[1000] = {0};
	Receive(buffer, 1000);

	CString cs = buffer;
	cs.TrimRight();

	int read = cs.GetLength();

	if( read > 0  )
	{	
		ReplyTelegramBin( cs );
	}

	CAsyncSocket::OnReceive(nErrorCode);
	
	lock.Unlock();
}

void CInterfaceTcp::OnClose(int nErrorCode) 
{
	if( nErrorCode != 0 )
		ShowErrorMessage( nErrorCode );

	Close();
}

bool CInterfaceTcp::SendTelegram(CString cs)
{
	// Server send message to client
	send( m_ClientSocket, cs.GetBuffer(0), cs.GetLength(), 0 );
	return true;
}

void CInterfaceTcp::ReplyTelegramBin(CString msg)
{
	CString cstcpbin = "-2";
	if( msg.Find( m_header ) == -1 && 
		msg.Find( m_tail ) == -1)
	{
		// Message
	}
	else 
	{
		int iStart = msg.Find( m_header );			
		int iEnd = msg.Find( m_tail , iStart);
		
		CString csMessage = _T("");

		int HeaderLength = m_header.GetLength();
		int TailHeaderLength = m_tail.GetLength();

		// 取得真正的命令 (移除 開頭與結尾)	
		csMessage = msg.Mid( iStart + HeaderLength, iEnd - TailHeaderLength );

		if( csMessage.Find( m_start ) == 0 )
		{
			m.m_TcpValue.gettcpstart = true;
			m.m_TcpValue.gettcpstartRev = true;

			m.m_TcpValue.tcpReady = msg;

			CString csgo = _T("");
			csgo = m_header + m_go + m_tail;
			Send( csgo.GetBuffer(0), csgo.GetLength() );	// Get Tester say Ready. Send Go. Ask Tester Start Testing
		}
		else if( csMessage.Find( m_binheader ) == 0 )
		{
			if( m.m_TcpValue.gettcpstart )		// 如果沒有取得 Tester的Start也不接受 bin code的值
			{
				m.m_TcpValue.gettcpstart = false;
				// 這是 Bin Code 開始處理分 Bin						
				// 取得 Bin Code 的起始點 / 本身沒有意義
				int iBinCodeHeaderLebgth = m_binheader.GetLength();
				int iBinCodeStart = csMessage.Find( m_binheader, 0 );
						
				// 把 Bin Code Header 移掉. 剩下的就是 Bin Code.
				CString code = _T("");
				code = csMessage;
				code.Delete(0, iBinCodeHeaderLebgth );
				cstcpbin = code;
				// 取得 Bin	
				
				// 設定 bin / 然後通知別人來取
				m.m_TcpValue.tcpBin = code;
				m.m_TcpValue.tcpBinSource = msg;
				m.m_TcpValue.gettcpBin = true;
			}
		}
		else
			;	// Never be here
	}
}
void CInterfaceTcp::OnConnect(int nErrorCode) 
{	
	if( nErrorCode != 0 )
	{
		ShowErrorMessage( nErrorCode );
		Close();
	}
	else
	{
		// Client Connect OK.!
	}
	
	CAsyncSocket::OnConnect(nErrorCode);
}

void CInterfaceTcp::ShowErrorMessage(long l)
{
	return;
	if( l == WSANOTINITIALISED )
		AfxMessageBox("WSANOTINITIALISED");
	else if( l == WSAENETDOWN  )
		AfxMessageBox("WSAENETDOWN");
	else if( l == WSAEACCES )
		AfxMessageBox("WSAEACCES ");
	else if( l == WSAEINPROGRESS )
		AfxMessageBox("WSAEINPROGRESS  ");
	else if( l == WSAEFAULT )
		AfxMessageBox("WSAEFAULT");
	else if( l == WSAENOBUFS )
		AfxMessageBox("WSAENOBUFS ");
	else if( l == WSAENOTCONN )
		AfxMessageBox("WSAENOTCONN");
	else if( l == WSAENOTSOCK )
		AfxMessageBox("WSAENOTSOCK");
	else if( l == WSAEOPNOTSUPP  )
		AfxMessageBox("WSAEOPNOTSUPP");
	else if( l == WSAESHUTDOWN )
		AfxMessageBox("WSAESHUTDOWN");
	else if( l == WSAEWOULDBLOCK )
		AfxMessageBox("WSAEWOULDBLOCK ");
	else if( l == WSAEMSGSIZE  )
		AfxMessageBox("WSAEMSGSIZE ");
	else if( l == WSAECONNABORTED )
		AfxMessageBox("WSAECONNABORTED");
	else if( l == WSAECONNRESET  )
		AfxMessageBox("WSAECONNRESET");
	else
		; // Never be here
}

// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP(CInterfaceTcp, CAsyncSocket)
	//{{AFX_MSG_MAP(CInterfaceTcp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0

/////////////////////////////////////////////////////////////////////////////
// CInterfaceTcp member functions


