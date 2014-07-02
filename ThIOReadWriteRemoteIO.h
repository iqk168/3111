#if !defined(AFX_THIOREADWRITEREMOTEIO_H__212F7F8B_ADDB_4B0D_B3E4_6F96910AF538__INCLUDED_)
#define AFX_THIOREADWRITEREMOTEIO_H__212F7F8B_ADDB_4B0D_B3E4_6F96910AF538__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ThIOReadWriteRemoteIO.h : header file
//

//#include "Dll6.h"

/////////////////////////////////////////////////////////////////////////////
// CThIOReadWriteRemoteIO thread

class CThIOReadWriteRemoteIO : public CWinThread
{
	DECLARE_DYNCREATE(CThIOReadWriteRemoteIO)

public:
	CThIOReadWriteRemoteIO();           // protected constructor used by dynamic creation
	virtual ~CThIOReadWriteRemoteIO();

	// output
	I16 ret;
	// input
	I16 Ret;
	U32 Input;

	bool Init();
	bool Open(int ComNo, int BaudRate = 9600);
	bool ReadInput();
	bool SetOutput();

	double m_dTorqueValue;
	double m_dOldTorqueValue;
	void SetTorqueValue( double dValue);
	void GetTorqueValue( double &dValue);
	bool SetTorque();

	void CloseAllIOOutput();
	bool Close();
	void Clear();

public:
	int		m_iComNo;
	int		m_iBaudRate;
	int		m_iByteSize;
	int		m_iParity;
	int		m_iStopBit;

protected:

	HANDLE	m_hComm;

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CThIOReadWriteRemoteIO)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CThIOReadWriteRemoteIO)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_THIOREADWRITEREMOTEIO_H__212F7F8B_ADDB_4B0D_B3E4_6F96910AF538__INCLUDED_)
