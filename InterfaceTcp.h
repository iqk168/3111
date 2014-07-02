#if !defined(AFX_INTERFACETCP_H__58551C02_8A43_47DC_A8E8_2244363FD3F4__INCLUDED_)
#define AFX_INTERFACETCP_H__58551C02_8A43_47DC_A8E8_2244363FD3F4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// InterfaceTcp.h : header file
//

#include <afxsock.h>

/////////////////////////////////////////////////////////////////////////////
// CInterfaceTcp command target

class CInterfaceTcp : public CAsyncSocket
{
// Attributes
public:

// Operations
public:
	CInterfaceTcp();
	virtual ~CInterfaceTcp();

	bool SendTelegram(CString cs);
	void ShowErrorMessage(long l);
	void ReplyTelegramBin(CString msg);

	CMutex TcpMutex;
public:
	void SetInterface(CString header, 
		CString taill, 
		CString binheader, 
		CString go, 
		CString ready, 
		CString start);

	CString m_header;
	CString m_tail;
	CString m_binheader;
	CString m_go;
	CString m_ready;
	CString m_start;

	SOCKET m_ClientSocket;


// Overrides
public:
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CInterfaceTcp)
	public:
	virtual void OnAccept(int nErrorCode);
	virtual void OnReceive(int nErrorCode);
	virtual void OnClose(int nErrorCode);
	virtual void OnConnect(int nErrorCode);
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(CInterfaceTcp)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

// Implementation
protected:
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INTERFACETCP_H__58551C02_8A43_47DC_A8E8_2244363FD3F4__INCLUDED_)
