#if !defined(AFX_THERRORCTRL_H__D4DDB8BE_1C2E_421D_95FD_1919E110EA10__INCLUDED_)
#define AFX_THERRORCTRL_H__D4DDB8BE_1C2E_421D_95FD_1919E110EA10__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ThErrorCtrl.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CThErrorCtrl thread

class CThErrorCtrl : public CWinThread
{
	DECLARE_DYNCREATE(CThErrorCtrl)

public:
	CThErrorCtrl();           // protected constructor used by dynamic creation
	virtual ~CThErrorCtrl();

protected:

// Attributes
public:

// Operations
public:
	long CheckErrorHandle();
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CThErrorCtrl)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation
protected:

	bool CheckIO(bool button = true);
	// Generated message map functions
	//{{AFX_MSG(CThErrorCtrl)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
private:
	bool CheckError(tagErrorParam &err);
	long CheckButton();
	void Running();

	//
	void RemoteControlMessageAlarm(int code = 0);

	//
	void ManualControlMessageAlarm(int code = 0);

public:
//	void AirErrorCheck(tagErrorParam &err);
//	void AirErrorRecover();
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_THERRORCTRL_H__D4DDB8BE_1C2E_421D_95FD_1919E110EA10__INCLUDED_)
