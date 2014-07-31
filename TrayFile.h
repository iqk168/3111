// TrayFile.h: interface for the CTrayFile class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TRAYFILE_H__68F611BA_E0F9_4082_973D_BF2D0080FB45__INCLUDED_)
#define AFX_TRAYFILE_H__68F611BA_E0F9_4082_973D_BF2D0080FB45__INCLUDED_

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

typedef struct tagTray{
	int Status;
} tagTray;

class CTrayFile  
{
public:
	BOOL SemiAuto(int Coord);
	CTrayFile();
	virtual ~CTrayFile();

	tagTraySpec m_TraySpec;				// Tray data, A, B, C, D...位置. 單位 mm
	tagXYZ		m_Align;				// Arm XYZ Alignment 位置.. 單位 Motor Pulse.
	tagXYZ		m_Gear;					// Arm XYZ 的 Gear Ration.. 單位. 倍率	

	int m_Row;							// Tray data 的 Row 數
	int m_Col;							// Tray data 的 Col 數
	int m_TraySize;						// Tray data Row * Col,一個Tra的IC數量

	int m_MeA;							// 機構參數 原點與 A
	int m_MeB;							// 機構參數 原點與 B

	void SetSpec(tagTraySpec TraySpec);	// 把 Tray data, A, B, C, D.. Tray 盤資料傳進來.
	void SetMe(int A, int B );			// 把機構誤差傳進來
	void SetAlign(tagXYZ Align);		// 把 Alignment 資料傳進來.
	void SetGear(tagXYZ Gear);			// 把 Gear Ration 資料傳進來

	// Chip Tray
	void SetChipMode(int Chip);
	int	m_Chip;	// 1 表示使用 Chip Tray, 0 表示沒有使用 Chip Tray

	// 宣告一組 TrayStatus. 陣列大小是 Tray Size.
	int *m_TrayStatus;
	void TrayStatusResize();	// 等到 TraySpec 傳進來後. Resize 陣列大小.

	// Terence / Denny 希望可以讓使用者知道是否是 Auto Skip 的狀態
	int *m_TrayStatusAutoSkip;
	int TrayiNoGetStatusAuto(int iNo);
	void TrayiNoGetStatusSetAuto();

	// 運轉用的功能
	enum Status 
	{
		enEOF		=-1,	// 
		enEmpty		= 0,	// 該位置是空白.
		enBooking	= 1,	// 正在寫入資料.
		enMoving	= 3,	// 正在移動中.
		enOK		= 4		// 被取走.或是被擺放
	};	

	// 設定 Tray 盤狀態
	void SetFull();					// 我們將狀態全部設為 enEmpty, 從 iNext設Size加1
	void ChangeTray();				// 我們將狀態全部設為 enEmpty, 從 iNext Dut#1
	BOOL LocationQuery();			// 確認這個 Tray 是否還有 IC
	int	 LocationBooking();			// 把位置設為 enBooking. 把準備要放的位置設為 Booking.
	BOOL LocationMove();			// 把位置設為 enMoving, 把正在移動的位置設為 Moving.
	BOOL LocationMove(int DeiNo);	// 把特定位置設為 enMoving, 把正在移動的位置設為 Moving.
	CPoint GetCoordinate(int iNo);	// 抓取座標
	CPoint GetIndex();				// 抓取座標, 給 Tray Map 檔案用
	CPoint GetIndex(int iNo);		// 抓取座標, 給 Tray Map 檔案用
	BOOL LocationDone();

	BOOL LocationDone(int DeiNo);
	// Debug using.

	BOOL GetStatus(int *pTray, int iSize);
	BOOL SetStatus(int *pTray, int iSize);

	int TrayiNoGetStatus(int iNo);

	int m_iNext;	// 下一個可以取或放的位置 IC (Input是取的位置. Output是放的位置)
	int m_iNow;		// 目前正在取或放(Input是取的位置. Output是放的位置)

	// Note : 如果Input和Output是同一個則要宣告兩次
	
	// #1: 有一個新的 Tray. 先將狀態全部設為 enEmpty, 表示有 IC. 但是還沒有開始記錄 void SetFull();	
	// #2: 確認這個 Tray 還有沒有 IC. 是否還存在 enUnBook. BOOL LocationQuery();
	// #3: 把準備要取放的 IC 要到, 然後設為 enBooking.
	// #4: 取得位置後, MotorRun 設為 Moving.
	// #5: 當取到IC或放完IC LocationDone 設為 enOK 並把下一個 m_iNext+1

	CString		m_Coordinate;			// Coordinate 檔案位置
	void SetCoordinate(CString csFile);	// 設定檔案位置
	void SaveLocation();				// 記錄目前的位置
	void SetLocation();					// 設定目前的位置
	BOOL SetLocationStatus();			// 重新設定狀態 (根據 iNow 和 iNext )

	BOOL LocationAllDone();				// 把位置全部設為 enOK
	void LotDoneSetFull();				// 把位置全部設為 enEmpty

	BOOL Check();

	// Chip Tray Convert
	void ConvertChipTray();
	int GetChipTrayPosition( int iBooking );
	int *m_ChipTrayArray;						// 用來紀錄轉換陣列的
	int	*m_ChipTrayArrayStatus;					// 用來紀錄轉換陣列的狀態
	CPoint GetCoordinateCustomRemote(int iNo);	// 抓取座標

	// Location In / Location Out 
	CPoint GetCoordinateLocation(int iNo);		// 抓取座標


};

#endif // !defined(AFX_TRAYFILE_H__68F611BA_E0F9_4082_973D_BF2D0080FB45__INCLUDED_)
