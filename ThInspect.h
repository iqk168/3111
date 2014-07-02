#if !defined(AFX_THINSPECT_H__6BEECBF8_EA9B_42C4_824B_D15B312B13CD__INCLUDED_)
#define AFX_THINSPECT_H__6BEECBF8_EA9B_42C4_824B_D15B312B13CD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ThInspect.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CThInspect thread

class CThInspect : public CWinThread
{	
	DECLARE_DYNCREATE(CThInspect)
public:
	virtual ~CThInspect();	
	CThInspect();           // protected constructor used by dynamic creation

	enum Status{
		enIdle			= 0x10,
		enInitialize	= 0x20,
	};

	long m_iRunError;	// It is for motor error, If Motor function fail.

	int  m_bStatus;

	void Running();
	void CheckRestart();
	void NextStatus();
	bool IsPause();

	void InitialStart();
	void Initialize();
	bool IsInitialError();

	bool m_bInitialized;
	bool m_bInitialRequest;

protected:

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CThInspect)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CThInspect)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_THINSPECT_H__6BEECBF8_EA9B_42C4_824B_D15B312B13CD__INCLUDED_)
