// TorqueCtrl.h: interface for the CTorqueCtrl class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TORQUECTRL_H__08A879A6_A94B_457D_9981_439D9D979177__INCLUDED_)
#define AFX_TORQUECTRL_H__08A879A6_A94B_457D_9981_439D9D979177__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CTorqueCtrl  
{
public:
	CTorqueCtrl();
	virtual ~CTorqueCtrl();
public:
	// api
	bool FlowControlApi(double dValue, int &iReturnCode);

public:
	// Norrmal
	bool OpenFlowControl(int ComNo, int BaudRate = 9600);
	long ConWriteString(CString cs);
	long ConGetString(char *buffer, int iMaxRead = 100);
	bool Close();

	//
	CMutex object;

	HANDLE	m_hComm;
	int		m_iComNo;
	int		m_iBaudRate;
	int		m_iByteSize;
	int		m_iParity;
	int		m_iStopBit;

	//
	void Clear();

	//
	void FlowControl(long iPower);

	int OutputPort;	// 外部設定的 Port
};

#endif // !defined(AFX_TORQUECTRL_H__08A879A6_A94B_457D_9981_439D9D979177__INCLUDED_)
