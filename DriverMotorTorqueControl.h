// DriverMotorTorqueControl.h: interface for the CDriverMotorTorqueControl class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DRIVERMOTORTORQUECONTROL_H__C8C9738C_8E41_4500_862B_80746CCE7E12__INCLUDED_)
#define AFX_DRIVERMOTORTORQUECONTROL_H__C8C9738C_8E41_4500_862B_80746CCE7E12__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define _Site_No	1

class CDriverMotorTorqueControl  
{
public:
	CDriverMotorTorqueControl();
	virtual ~CDriverMotorTorqueControl();

	enum enParamList {enParamTorque = 0x5E};

protected:
	typedef struct tagParamProperty{
		unsigned char vLow;
		char vHigh;
		unsigned char MinLow;
		char MinHigh;
		unsigned char MaxLow;
		char MaxHigh;
		unsigned char PropertyLow;
		char PropertyHigh;
	} tagParamProperty;
	
	typedef struct tagPageDataRead{
		unsigned char CmdType; // 0x82
		unsigned char AxisNo;
		unsigned char ModeCmd; // 0x1B
		unsigned char PageNo; // 0 ~ 7
		tagParamProperty Param[16];
		unsigned char Err;
		unsigned char CheckSum;
	} tagPageDataRead;
		
	typedef struct tagCmdTorque{
		unsigned char DataNo;
		unsigned char AxisNo;
		unsigned char ModeCmd;
		unsigned char CheckSum;
	} tagCmdTorque;

	typedef struct tagResTorque{
		unsigned char DataNo;
		unsigned char AxisNo;
		unsigned char ModeCmd;
		char Data[2];
		unsigned char Err;
		unsigned char CheckSum;
	} tagResTorque;

	typedef struct tagWriteParameter{
		unsigned char DataNo; // 3
		unsigned char AxisNo;
		unsigned char ModeCmd; // 0x18
		unsigned char ParamNo;
		unsigned char vLow;
		char vHigh;
		unsigned char CheckSum;
	} tagWriteParameter;

	typedef struct tagWriteRes{
		unsigned char DataNo; // 1
		unsigned char AxisNo;
		unsigned char ModeCmd; // 0x18
		unsigned char Err;
		unsigned char CheckSum;
	} tagWriteRes;

	typedef struct tagReadParameter{
		unsigned char DataNo; // 1
		unsigned char AxisNo;
		unsigned char ModeCmd; // 0x08
		unsigned char ParamNo;
		unsigned char CheckSum;
	} tagReadParameter;

	typedef struct tagReadRes{
		unsigned char DataNo; // 3
		unsigned char AxisNo;
		unsigned char ModeCmd; // 0x08
		unsigned char vLow;
		char vHigh;
		unsigned char Err;
		unsigned char CheckSum;
	} tagReadRes;

	typedef struct tagWriteCmd{
		unsigned char AxisNo;
		unsigned char ParamNo;
		long value;
	} tagWriteCmd; 

	CArray <tagWriteCmd, tagWriteCmd> CmdQue;

public:
	bool MotorParamRead(int MotorID, int ParamNo, long &data); // ㄑ场㊣弄皑笷把块
	bool MotorParamWrite(int MotorID, int ParamNo, long data); // ㄑ场㊣糶皑笷把计

public:
	bool ThreadPause(bool stop = false);
	void DownloadMotorParam();
	void SaveMotorParam();
	void SetForceTorqueRatio(double ratio); // x = Force / Torque ==> Force = x * Torque
	void SetInitialLoad(int id);
	bool IsWorking(int id);
	void AddWriteCmd(int id, int paraNo, long value);
	long ReadPara(int id, int para);
	long GetBaudRate(int id);
	double GetForce(int site);
	void ProcessRead(int id);
	double GetTorque(int iSite);
	double GetTorqueSetting(int iSite);
	void ProcessCmd();
	bool IsConnected();
	bool Open(int iPort = 1, int iBaudRate = 57600, bool bReboot = true);
	bool Close();
	HANDLE hProcess;
	long ParaRead[_Site_No][0x7F];
	long ParaWrite[_Site_No][0x7F];

	bool pause;
	bool paused;

private:
	HANDLE	m_hComm;
	bool	bBaudRateOK[6];
	long	iBaudRate[8]; //  贺 baudrate
	long	iBaudRateTry[6];
	long	iBaudRateNow;
	double tTorqueSetting[6], tTorque[6];

	double InitialLoad[6];
	double ForceTorqueRatio;

protected:
	bool _PageRead(int id, int page, long *data);
	void SetBaudRate(long BaudRate);
	bool WritePara(tagWriteCmd cmdWrite);
	long SwitchToNextBaudRate(int id);
	void PurgeComm();
	bool _GetTorque(int id);
	void _WriteString(unsigned char *buffer, int size);
	bool _GetResponse(unsigned char *buffer);
	unsigned char CheckSum(unsigned char *pCmdWord, int iLength);
	bool WaitCMD(unsigned char cmd);
	bool SendCMD(unsigned char cmd);

protected:

	bool bOpenOK;

public:
	static UINT ThreadMotorTorqueControl(LPVOID p);
	bool GetOpenOK();
};

#endif // !defined(AFX_DRIVERMOTORTORQUECONTROL_H__C8C9738C_8E41_4500_862B_80746CCE7E12__INCLUDED_)
