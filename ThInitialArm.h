#if !defined(AFX_THINITIALARM_H__C92D55EC_8696_4AE4_98F8_11894CA31470__INCLUDED_)
#define AFX_THINITIALARM_H__C92D55EC_8696_4AE4_98F8_11894CA31470__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ThInitialArm.h : header file
//



/////////////////////////////////////////////////////////////////////////////
// CThInitialArm thread

class CThInitialArm : public CWinThread
{
	DECLARE_DYNCREATE(CThInitialArm)
public:

	CThInitialArm();           // protected constructor used by dynamic creation
	virtual ~CThInitialArm();

	enum Status{
		//
		enIdle = 0x10,					// Idle 
		enInitialize = 0x20,			// Initial
	};

	int  m_bStatus;

	long m_iRunError;		// It is for motor error, If Motor function fail.

	void Running();
	void CheckRestart();
	void NextStatus();
	bool IsPause();

	void InitialStart();
	void Initialize();
	bool IsInitialError(long err, long id);

	bool m_bInitialized;
	bool m_bInitialRequest;

	// Shuttle Home
	void ShuttleInitialHome();
	void ShuttleInitialFinalHome();

protected:

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CThInitialArm)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CThInitialArm)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_THINITIALARM_H__C92D55EC_8696_4AE4_98F8_11894CA31470__INCLUDED_)
