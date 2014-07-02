// PreheaterFile.h: interface for the CPreheaterFile class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PREHEATERFILE_H__D3AC3ACF_F5C1_4361_A7AA_421F7C741D7C__INCLUDED_)
#define AFX_PREHEATERFILE_H__D3AC3ACF_F5C1_4361_A7AA_421F7C741D7C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Member.h" 
//#include "Define.h" 
// Because We need 
// #1: tagTratSpec struct
// #2: tag XYZ struct

#include <cmath>
#include <afxmt.h>
// avoid crash in status array.

typedef struct tagPreheater{
	int Status;
} tagPreheater;

class CPreheaterFile  
{
public:
	CPreheaterFile();
	virtual ~CPreheaterFile();

	// add new function
	void SetSpec(tagTraySpec TraySpec);	// 把 Tray data, A, B, C, D.. Tray 盤資料傳進來.
	void SetMe(int A, int B );			// 把機構誤差傳進來
	void SetAlign(tagXYZ Align);		// 把 Alignment 資料傳進來.
	void SetGear(tagXYZ Gear);			// 把 Gear Ration 資料傳進來
	void SetCoordinate(CString csFile);
	void SetSoak(long SoakTime);		// 設定 SoakTime 以及重新設定 iNext 和 iCount.
	int	 GetiNext();
	int	 GetiCount();

	tagTraySpec m_TraySpec;				// Tray data, A, B, C, D...位置. 單位 mm
	tagXYZ		m_Align;				// Arm XYZ Alignment 位置.. 單位 Motor Pulse.
	tagXYZ		m_Gear;					// Arm XYZ 的 Gear Ration.. 單位. 倍率	
	int			m_MeA;					// 機構參數 原點與 A
	int			m_MeB;					// 機構參數 原點與 B
	CString		m_Coordinate;			

	BOOL ClearBuffer();
	long GetRemainSoakTime();
	void SetSoakTime(long time);
	CPoint GetCoordinate(int iNo);
	void OutputDone();
	void InputDone();
	BOOL OutputLocationQuery();
	BOOL InputLocationQuery();
	void Save();
	void Load();
	void LoadFile();
	
	enum Status {enEOF = -1, enEmpty = 0, enBooking = 1, enMoving = 2, enOK = 3};
	
	// 改變 Dut 的位置
	int	Convert( int iNo );

protected:

	long m_iSoakTime; // in sec
	long m_iNext;
	long m_iCount;
	COleDateTime m_Time[_MaxPreHeaterDevice]; // max 200 device can put in preheater
};

#endif // !defined(AFX_PREHEATERFILE_H__D3AC3ACF_F5C1_4361_A7AA_421F7C741D7C__INCLUDED_)
