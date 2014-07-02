// DriveWest.h: interface for the CDriveWest class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DRIVEWEST_H__9622D379_0D2B_48F4_B0C5_4DCDEDC6B409__INCLUDED_)
#define AFX_DRIVEWEST_H__9622D379_0D2B_48F4_B0C5_4DCDEDC6B409__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define _Device_Error		-9999
#define _MaxWestDevice		2


enum enWest { enSV = 0x0, enOffset = 0x1};
class CDriveWest  
{
public:
	CDriveWest();
	virtual ~CDriveWest();

public:

	// 開啟連線
	BOOL Open(int iWestComPortNo);

protected:
	HANDLE	m_hComm;
	BOOL	m_bConnectStatus;

	BOOL	SetOffsetTemperature(int iDevice, double dNewOffset);	// 讀取 Offset 設定值
	double	ReadOffsetTemperature(int iDevice);					// 讀取顯示器上的溫度	
	double	ReadDisplayTemperature(int iDevice);				// 設定要加溫到達的溫度	
	double	ReadSettingTemperature(int iDevice);
	BOOL	SetTemperature(int iDevice, double dTemperature);
	double _RetrieveTemperature(CString &csValue);
	CString	_Send(CString cs);									// 送出字串, 並接受回應
	CString	_Send(unsigned char *data, int len);				// 送出字串, 並接受回應
	void ShowErrorMessage(int iErrorCode);
	bool Close();

	bool IsConnected();

	//
	static UINT WestCtrlThread(LPVOID p);
	CEvent threadEvent;

public:

	void GetValue(double *pPV, double *pSV);
	void GetOffsetValue(double *pOffset);
	double dPV[_MaxWestDevice];
	double dSV[_MaxWestDevice];
	double dOffSet[_MaxWestDevice];

	typedef struct tagCmd {
		byte id;
		short addr;	// 0: sv, 1:offset
		double value;
	} tagCmd;
	void AddCmd(byte id, short addr, double value);
	CArray <tagCmd, tagCmd> CmdSet;

public:
	HANDLE hProcess;

};

#endif // !defined(AFX_DRIVEWEST_H__9622D379_0D2B_48F4_B0C5_4DCDEDC6B409__INCLUDED_)
