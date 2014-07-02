// Motor.h: interface for the CMotor class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MOTOR_H__68EA275B_2699_42D8_8892_78E0264F7369__INCLUDED_)
#define AFX_MOTOR_H__68EA275B_2699_42D8_8892_78E0264F7369__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CAutoLock
{
public:
	CAutoLock(CSyncObject &mutex) : m_mutex(mutex) { m_mutex.Lock();}
	~CAutoLock() {m_mutex.Unlock();}

private:
	CSyncObject &m_mutex;
};

class CMotor  
{
public:
	CMotor();
	virtual ~CMotor();

	// Manual Motor Run
	long ManualMotorRun(tagMotorParam *pAxis, double dPos, bool PreMove = false , long dTimeout = 55000 );
	long ManualMotorRunLine(tagMotorParam *Axis1, double dPos1, tagMotorParam *Axis2, double dPos2, bool PreMove = false, double dTimeout = 55000);
	long ManualMotorSoftRun(tagMotorParam *pAxis, double dPos, bool PreMove = false);

	// Motor Function
	void EnableInterrupt(tagMotorParam *motor, bool bEnable, int iWhichSensor = -1, bool bSensor = false);
	void MotorReadReg(tagMotorParam *pAxis, unsigned short reg, long *value);
	void GetMotorStatus(tagMotorParam *pAxis);
	void Servo(tagMotorParam *pAxis, bool enable);

	void MotorClearCount(tagMotorParam *pAxis);

	void ClearMotorAlarm(tagMotorParam *pAxis);
	void ClearMotorError(tagMotorParam *pAxis);

	void LoadDriftSpeed(tagMotorParam *pAxis);
	void LoadSearchSpeed(tagMotorParam *pAxis);
	bool LoadCycleSpeed(tagMotorParam *pAxis);

	void MotorStop(tagMotorParam *motor);	
	int	GetMotorID(tagMotorParam *motor);

	long MotorRunAnyway(tagMotorParam *pAxis, double dPos, bool PreMove, long dTimeout );

	long MotorRun(tagMotorParam *pAxis, double dPos, bool PreMove = false , long dTimeout = 55000 );
	long MotorSoftRun(tagMotorParam *pAxis, double dPos, bool PreMove = false, long dTimeout = 55000 );
	long MotorContinueMove(tagMotorParam *pAxis, bool bDirToPositive, bool bMonitor);

	long MotorRunLine(tagMotorParam &Axis1, double dPos1, tagMotorParam &Axis2, double dPos2, bool PreMove = false, double dTimeout = 55000);
	long MotorRunLineLocation(tagMotorParam &Axis1, double dPos1, tagMotorParam &Axis2, double dPos2, bool PreMove = false, double dTimeout = 55000);

	long MotorMovetopLimt(tagMotorParam *pAxis, long timeout );
	long MotorMovetonLimt(tagMotorParam *pAxis, long timeout );
	long MoveOffpLimit(tagMotorParam *pAxis, long timeout );
	long MoveOffnLimit(tagMotorParam *pAxis, long timeout );

	// Initial
	long MotorMovetonNLimt(tagMotorParam &pAxis, long timeout );
	long MotorMovetopPLimt(tagMotorParam &pAxis, long timeout );
	long MoveOffnNLimit(tagMotorParam *pAxis, long timeout );

	long MotorLmtCounter(unsigned char BordID, unsigned char Axis );	// p Lmt
	long MotorLmtCounter2(unsigned char BordID, unsigned char Axis );	// n Lmt

	long MotorLmtCounterClear();

	void MotorEncoder(tagMotorParam *motor, long pos = 0);

	// Motor Check Function
	long MotorRunTLC(tagMotorParam *pAxis, double dPos, bool PreMove = false , long dTimeout = 55000 );

	// Initial using.
	long InitialMotorMoveOffLoadPoint(tagMotorParam *pAxis, unsigned char* pSensor, 
		unsigned char* LpSensor, long dTimeout = 55000);

	// Check Error / Alarm
	bool IsMotorError( tagMotorParam *pAxis );	// Make sure there have a Error
	bool IsMotorAlarm( tagMotorParam *pAxis );	// Make sure there have a Alarm.

	// Check Motor Sensor
	bool SearchMotorMovetopLimt(tagMotorParam *pAxis, long timeout );
	bool SearchMotorMovetonLimt(tagMotorParam *pAxis, long timeout );

	// MotorHome
	long ManualMotorHome(tagMotorParam *pAxis, long timeout );

	// 
	void IsMotorErrorCode(LRESULT LRes);
	CString IsMotorErrorCodeLog(LRESULT LRes);
	bool IsMotorErrorCodeCheck(LRESULT LRes);

	// Torque Change with Motion Card
	void TorqueChange(tagMotorParam *pAxis, bool enable);

	// Soft Up and Soft Down
	long MotorRunSoftTLC(tagMotorParam *pAxis, double dPos, bool PreMove = false , long dTimeout = 55000, 
		int SoftSpeed = 10 );

	// TS Remain IC Run
	long MotorRunTSRemainIC(tagMotorParam *pAxis, double dPos, bool PreMove = false , long dTimeout = 55000, long lSpeed = 50 );

	// TS Check Vacc, When Moving
	long MotorRunTSCheckICDrop(tagMotorParam *pAxis, double dPos, bool PreMove = false , long dTimeout = 55000, long lSpeed = 50 );
	long MotorRunTLCCheckICDrop(tagMotorParam *pAxis, double dPos, bool PreMove = false , long dTimeout = 55000 );

public:
	long ManualMotorRunSoftTLC(tagMotorParam *pAxis, double dPos, bool PreMove = false , long dTimeout = 55000, 
		int SoftSpeed = 10 );
};

#endif // !defined(AFX_MOTOR_H__68EA275B_2699_42D8_8892_78E0264F7369__INCLUDED_)
