#if !defined(AFX_DRIVERTESTINTERFACETCP_H__412FE59E_DFE6_41F9_97CE_1D1B8B212559__INCLUDED_)
#define AFX_DRIVERTESTINTERFACETCP_H__412FE59E_DFE6_41F9_97CE_1D1B8B212559__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DriverTestInterfaceTCP.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDriverTestInterfaceTCP command target

class CDriverTestInterfaceTCP : public CAsyncSocket
{
// Attributes
public:

// Operations
public:
	// 提供上層取得資料
	CString csBuffer;
	void SetBuffer(CString csRecvBuffer);
	void GetBufferData(CString &csRecvBuffer);
	void GetTotalBufferData(CString &csRecvBuffer);

public:
	CDriverTestInterfaceTCP();
	virtual ~CDriverTestInterfaceTCP();

	int iConnected;
	unsigned long iConnectedNumber;

	bool m_bConnected;
	CDriverTestInterfaceTCP *m_Socket[10];


	bool GetConnected();
	void SetConnected();
	void CloseTCP();
	bool m_bOverRange;

	// Send Message
	bool SendToClient(CString csMessage);

	// Send Message, popup to dialog
	void SendMessageToMain(CString csMessage);

	//
	void GetServerSocketName(CString &csSocketName, unsigned int &iPort);

// Overrides
public:
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDriverTestInterfaceTCP)
	public:
	virtual void OnAccept(int nErrorCode);
	virtual void OnClose(int nErrorCode);
	virtual void OnConnect(int nErrorCode);
	virtual void OnReceive(int nErrorCode);
	virtual void OnSend(int nErrorCode);
	virtual int Receive(void* lpBuf, int nBufLen, int nFlags = 0);
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(CDriverTestInterfaceTCP)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

// Implementation
protected:
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DRIVERTESTINTERFACETCP_H__412FE59E_DFE6_41F9_97CE_1D1B8B212559__INCLUDED_)
