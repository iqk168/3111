#if !defined(AFX_THIOREADWRITE_H__A409C181_ECAE_4900_8EBB_532308E84CE5__INCLUDED_)
#define AFX_THIOREADWRITE_H__A409C181_ECAE_4900_8EBB_532308E84CE5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ThIOReadWrite.h : header file
//

#include "matrix_gpio.h"

/////////////////////////////////////////////////////////////////////////////
// CThIOReadWrite thread

class CThIOReadWrite : public CWinThread
{
	DECLARE_DYNCREATE(CThIOReadWrite)	
public:
	virtual ~CThIOReadWrite();	
	CThIOReadWrite();           // protected constructor used by dynamic creation

	// MXC-4000
	// IO Card DATA structure
	typedef struct _Card_Info_Type
	{
		USHORT initFlag;
		USHORT cardType;
		ULONG  SBaddr;
		HANDLE hDev;
	} Card_Info_Type;
	Card_Info_Type card_Info;

	int err;

	U16 card_number;
	I16 card;

protected:

	// 3111 Moudle 
	bool Init();
	void ReadInput();
	void SetOutput();
	void SetLimitation();

	//
	void CloseAllIOOutput();
	void CloseAllIOOutputProtuctShuttle();

public:
	// 1.0Af
	// Lamp Setup
	void BlinkInit();
	void BlinkConvert();
	bool BlinkFlash(int iChoise);

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CThIOReadWrite)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation
protected:
	

	// Generated message map functions
	//{{AFX_MSG(CThIOReadWrite)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_THIOREADWRITE_H__A409C181_ECAE_4900_8EBB_532308E84CE5__INCLUDED_)
