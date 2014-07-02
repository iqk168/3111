#if !defined(AFX_THMANUALCTRL_H__6459EDB8_6419_4EBC_8669_53A7FF722641__INCLUDED_)
#define AFX_THMANUALCTRL_H__6459EDB8_6419_4EBC_8669_53A7FF722641__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ThManualCtrl.h : header file
//



/////////////////////////////////////////////////////////////////////////////
// CThManualCtrl thread

class CThManualCtrl : public CWinThread
{
	DECLARE_DYNCREATE(CThManualCtrl)
public:	
	CThManualCtrl();           // protected constructor used by dynamic creation
	virtual ~CThManualCtrl();

	enum Status{
		enIdle							= 0x10,			// Idle 
		enInitialize					= 0x20,			// Initial

		// IC Into Socket
		enManualStart					= 0x1110,		// Manual Contact Start
		enManualShMoveToInStart			= 0x1120,		// Manual Shuttle move to PP start
		enManualShCheckJam				= 0x1130,		// Manual Shuttle move to PP Check Jam Before Move
		enManualShMoveToIn				= 0x1140,		// Manual Shuttle move to PP (Testsite pick)
		enManualShMoveToInEnd			= 0x1150,		// Manual Shuttle move to PP end
		enManualTSPick					= 0x1160,		// Manual Test Site Down to Pick
		enManualTSVacc					= 0x1170,		// Manual Test Site Vacc
		enManualTSVaccEnd				= 0x1180,		// Manual Test Site Vacc End
		enManualTSUpForContact			= 0x1190,		// Manual Test Site Up For contact
		enManualShuttleMoveHome			= 0x11a0,		// Manual Shuttle move to home ( Testsite ready down to contact )
		enManualTSDownToContact			= 0x11b0,		// Manual Test site down to socket
		enManualTSStandy				= 0x11c0,		// Manual Test site stanyby ( wait for up )

		// IC Return Shuttle
		enManualUpStart					= 0x2110,		// Manual Return IC Start
		enManualUpTsVacc				= 0x2120,		// Manual Return IC, Vacc On
		enManualTSUpForPlace			= 0x2130,		// Manual TS Up for place
		enManualShMovetoOutStart		= 0x2140,		// Manual Shuttle move to output start
		enManualShMoveToOut				= 0x2150,		// Manual Shuttle move to output
		enManualShMoveToOutEnd			= 0x2160,		// Manual Shuttle move to output end
		enManualTSPlace					= 0x2170,		// Manual Test Site Down to Place
		enManualTSBlow					= 0x2180,		// Manual Test Site Blow
		enManualTSUpForReady			= 0x2190,		// Manual Test Site Up For Ready
		enManualShutleMoveToStandy		= 0x21a0,		// Manual Shuttle move to Standy (Home)
		enManualEnd						= 0x21b0,		// Manual Shuttle move to Home (back to Idle)

		// TS Pick IC Fail. Recover 
		enManualReTSUpForReadyStart		= 0x5110,		// Manual TS up move to Ready start 
		enManualReTSUpForReady			= 0x5120,		// Manual TS up move to Ready
		enManualReShuttleHomeForReady	= 0x5130,		// Manual Shuttle Home to Ready
		enManualReShuttleEnd			= 0x5140,		// Manual Shuttle Home end

		// Adjust Contact
		enManualTSMoveStart				= 0x3110,		// Manual Adjust TS Contact Position Start
		enManualTSMove					= 0x3120,		// Manual Adjust TS Contact Position 
		enManualTSMoveEnd				= 0x3130,		// Manual Adjust TS Contact Position End

		// 1.0Ab
		// Manaul Contact Test Site Direct Contact
		// Test Down
		enManualTsDirectContactStart	= 0x6110,		// Manual Contact, Test Site Direct Contact Start
		enManualTsDirectContactDown		= 0x6120,		// Manual Contact, Test Site Direct Contact Down
		enManualTsDirectContactEnd		= 0x6130,		// Manual Contact, Test Site Direct Contact Down End
		// Test Up
		enManualTsDirectContactUpStart	= 0x6140,		// Manual Contact, Test Site Direct Contact Up Start
		enManualTsDirectContactUp		= 0x6150,		// Manual Contact, Test Site Direct Contact Up
		enManualTsDirectContactUpEnd	= 0x6160,		// Manual Contact, Test Site Direct Contact Up End

		//
		enManualShMoveToInError			= 0x4110,		// Manual Move to Shuttle Pick Fail
		enManualTSUpForContactError		= 0x4120,		// Manual Test Site Pick IC Fail
		enManualShuttleMoveHomeError	= 0x4130,		// Manual Test Site Move to Home Fail
		enManualShMoveToOutError		= 0x4140,		// Manual Move to Shuttle Place Fail
		enManualShutleMoveToStandyError	= 0x4150,		// Manual Move to Shuttle Standy Fail
		enManualShCheckJamError			= 0x4160,		// Manual Check Jam
	};
	
	long m_iRunError;		// It is for motor error, If Motor function fail.	
	int  m_bStatus;

	void Running();
	void CheckRestart();
	void NextStatus();
	bool IsPause();

	void InitialStart();
	void Initialize();

	bool m_bInitialized;
	bool m_bInitialRequest;

	// Function
	bool m_bRequestContact;
	bool m_bRequestUp;
	bool m_bRequestMove;

	void InitialRequest();
	void RequestContact();
	void RequestUp();
	void RequestMove();

	// Message
	void ManualContactCtDone();
	void ManualContactUpDone();
	void ManualContactMvDone();

	bool m_TSZWithIC;

public:
	bool VaccOff(unsigned char* Vacc);

protected:

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CThManualCtrl)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CThManualCtrl)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_THMANUALCTRL_H__6459EDB8_6419_4EBC_8669_53A7FF722641__INCLUDED_)
