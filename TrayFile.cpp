// TrayFile.cpp: implementation of the CTrayFile class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TrayFile.h"

#include "Deer.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTrayFile::CTrayFile()
{
	m_Row = 0;		// Tray data 的 Row 數
	m_Col = 0;		// Tray data 的 Col 數
	m_TraySize = 0; // Tray data Row * Col,一個Tra的IC數量

	m_iNext = -1;
	m_iNow = -1;

	m_MeA = 0;
	m_MeB = 0;

	m_Coordinate = "";

	m_Chip = -1;
}

CTrayFile::~CTrayFile()
{
	if( m_TrayStatus != NULL )
	{
		delete m_TrayStatus;
		m_TrayStatus = NULL;
	}

	// Check Auto Skip
	if( m_TrayStatusAutoSkip != NULL )
	{
		delete m_TrayStatusAutoSkip;
		m_TrayStatusAutoSkip;
	}
	// Convert Booking
	if( m_ChipTrayArray != NULL )
	{
		delete m_ChipTrayArray;
		m_ChipTrayArray = NULL;
	}

	if( m_ChipTrayArrayStatus != NULL )
	{
		delete m_ChipTrayArrayStatus;
		m_ChipTrayArrayStatus = NULL;
	}
}
// Chip Tray
void CTrayFile::SetChipMode(int Chip)		
{
	m_Chip = Chip;
}
CPoint CTrayFile::GetIndex()		
{
	// 抓取座標, 給 Tray Map 檔案用
	int iNo = m_iNow;

	// Chip Tray
	if( m_Chip )
	{
		iNo = GetChipTrayPosition( m_iNow );
	}
	
	CPoint p;
	int m_iRowL = -1; // 跟 y 有關
	int m_iColL = -1; // 跟 x 有關		

	m_iColL = iNo % m_TraySpec.Column;		// For C
	m_iRowL = iNo / m_TraySpec.Column;		// For D

	p.x = m_iColL + 1;
	p.y = m_iRowL + 1;

	// Debug
	CString d;
	d.Format("Tray Map %dD . %dC", m_iRowL, m_iColL );
	f.CWinMessage( d, theApp.enDArm );

	return p;
}
CPoint CTrayFile::GetIndex(int iNo)		
{
	// 抓取座標, 給 Tray Map 檔案用
	
	CPoint p;
	int m_iRowL = -1; // 跟 y 有關
	int m_iColL = -1; // 跟 x 有關		

	m_iColL = iNo % m_TraySpec.Column;		// For C
	m_iRowL = iNo / m_TraySpec.Column;		// For D

	p.x = m_iColL + 1;
	p.y = m_iRowL + 1;

	// Debug
	CString d;
	d.Format("Tray Map %dD . %dC", m_iRowL, m_iColL );
	f.CWinMessage( d, theApp.enDArm );

	return p;
}

CPoint CTrayFile::GetCoordinateLocation(int iNo)		
{
	// 抓取座標
	// 這裡是給 Location In / Location Out 功能使用
	// 但是我們需要考慮 Chip Tray 的 feature 
	// 所以我們直接用 GetCoordinateCustomRemote 的程式, 但是為了避免混淆, 拆成兩個 Function
	CPoint p;
	
	if( m_Chip )
	{
		int m_iSubRowL = -1;	// 跟 y 有關 For D
		int m_iSubColL = -1;	// 跟 x 有關 For C

		int m_iChipRowL = -1;	// 跟 y 有關 For D
		int m_iChipColL = -1;	// 跟 x 有關 For C
		//

		int SubTrayColumn	= m_TraySpec.m_SubTrayColumn; 
		int ChipTrayColumn	= m_TraySpec.m_SubChipTrayColumn;
		int TotalValue = SubTrayColumn * ChipTrayColumn;

		int TotalForD = -1;
		int TotalForC = -1;

		TotalForD = iNo / TotalValue;	// 取商
		TotalForC = iNo % TotalValue;	// 取餘數

		m_iSubRowL	= TotalForD / ChipTrayColumn;	// 取得 Sub D	的變化
		m_iChipRowL = TotalForD % ChipTrayColumn;	// 取得 Chip D	的變化

		m_iSubColL	= TotalForC / ChipTrayColumn;	// 取得 Sub C	的變化
		m_iChipColL	= TotalForC % ChipTrayColumn;	// 取得 Chip C	的變化

		p.x = m_Align.x + 
			(( m_TraySpec.m_SubTrayA * m_Gear.x ) + ( m_TraySpec.m_SubChipTrayA * m_Gear.x ) + ( m_MeA )) +
			(  m_TraySpec.m_SubTrayC*(m_iSubColL ) * m_Gear.x ) + 
			(  m_TraySpec.m_SubChipTrayC*(m_iChipColL) * m_Gear.x );
		p.y = m_Align.y +
			(( m_TraySpec.m_SubTrayB * m_Gear.y ) + ( m_TraySpec.m_SubChipTrayB * m_Gear.y ) + ( m_MeB )) +
			(  m_TraySpec.m_SubTrayD*(m_iSubRowL ) * m_Gear.y ) + 
			(  m_TraySpec.m_SubChipTrayD*(m_iChipRowL) * m_Gear.y );
	}
	else
	{		
		int m_iRowL = -1; // 跟 y 有關
		int m_iColL = -1; // 跟 x 有關
		
		m_iColL = iNo % m_TraySpec.Column;		// For C
		m_iRowL = iNo / m_TraySpec.Column;		// For D
		
		p.x = m_Align.x + (( m_TraySpec.A * m_Gear.x ) + ( m_TraySpec.C*(m_iColL) * m_Gear.x )) + ( m_MeA );	
		p.y = m_Align.y + (( m_TraySpec.B * m_Gear.y ) + ( m_TraySpec.D*(m_iRowL) * m_Gear.y )) + ( m_MeB );
		
		// Debug
		CString d;
		d.Format("%dD . %dC", m_iRowL, m_iColL );
		f.CWinMessage( d, theApp.enDArm );	
	}

	return p;
}

CPoint CTrayFile::GetCoordinateCustomRemote(int iNo)
{
	// 如果是 Custom Remote Control
	// 那麼, 就不需要轉換陣列.
	// 但是重新寫一個比較好區分現在是不是 Remote Control

	CPoint p;
	
	if( m_Chip )
	{
		int m_iSubRowL = -1;	// 跟 y 有關 For D
		int m_iSubColL = -1;	// 跟 x 有關 For C

		int m_iChipRowL = -1;	// 跟 y 有關 For D
		int m_iChipColL = -1;	// 跟 x 有關 For C
		//

		int SubTrayColumn	= m_TraySpec.m_SubTrayColumn; 
		int ChipTrayColumn	= m_TraySpec.m_SubChipTrayColumn;
		int TotalValue = SubTrayColumn * ChipTrayColumn;

		int TotalForD = -1;
		int TotalForC = -1;

		TotalForD = iNo / TotalValue;	// 取商
		TotalForC = iNo % TotalValue;	// 取餘數

		m_iSubRowL	= TotalForD / ChipTrayColumn;	// 取得 Sub D	的變化
		m_iChipRowL = TotalForD % ChipTrayColumn;	// 取得 Chip D	的變化

		m_iSubColL	= TotalForC / ChipTrayColumn;	// 取得 Sub C	的變化
		m_iChipColL	= TotalForC % ChipTrayColumn;	// 取得 Chip C	的變化

		p.x = m_Align.x + 
			(( m_TraySpec.m_SubTrayA * m_Gear.x ) + ( m_TraySpec.m_SubChipTrayA * m_Gear.x ) + ( m_MeA )) +
			(  m_TraySpec.m_SubTrayC*(m_iSubColL ) * m_Gear.x ) + 
			(  m_TraySpec.m_SubChipTrayC*(m_iChipColL) * m_Gear.x );
		p.y = m_Align.y +
			(( m_TraySpec.m_SubTrayB * m_Gear.y ) + ( m_TraySpec.m_SubChipTrayB * m_Gear.y ) + ( m_MeB )) +
			(  m_TraySpec.m_SubTrayD*(m_iSubRowL ) * m_Gear.y ) + 
			(  m_TraySpec.m_SubChipTrayD*(m_iChipRowL) * m_Gear.y );

	}
	else
	{		
		int m_iRowL = -1; // 跟 y 有關
		int m_iColL = -1; // 跟 x 有關
		
		m_iColL = iNo % m_TraySpec.Column;		// For C
		m_iRowL = iNo / m_TraySpec.Column;		// For D
		
		p.x = m_Align.x + (( m_TraySpec.A * m_Gear.x ) + ( m_TraySpec.C*(m_iColL) * m_Gear.x )) + ( m_MeA );	
		p.y = m_Align.y + (( m_TraySpec.B * m_Gear.y ) + ( m_TraySpec.D*(m_iRowL) * m_Gear.y )) + ( m_MeB );
		
		// Debug
		CString d;
		d.Format("%dD . %dC", m_iRowL, m_iColL );
		f.CWinMessage( d, theApp.enDArm );	
	}

	return p;
}

CPoint CTrayFile::GetCoordinate(int iNo)
{
	// Chip Tray 驗證
	if( m_Chip )
		iNo = GetChipTrayPosition( iNo );
	// 這裡要轉換 Booking 的數值, 以符合取放狀態

	CPoint p;
	
	if( m_Chip )
	{
		int m_iSubRowL = -1;	// 跟 y 有關 For D
		int m_iSubColL = -1;	// 跟 x 有關 For C

		int m_iChipRowL = -1;	// 跟 y 有關 For D
		int m_iChipColL = -1;	// 跟 x 有關 For C
		//

		int SubTrayColumn	= m_TraySpec.m_SubTrayColumn; 
		int ChipTrayColumn	= m_TraySpec.m_SubChipTrayColumn;
		int TotalValue = SubTrayColumn * ChipTrayColumn;

		int TotalForD = -1;
		int TotalForC = -1;

		TotalForD = iNo / TotalValue;	// 取商
		TotalForC = iNo % TotalValue;	// 取餘數

		m_iSubRowL	= TotalForD / ChipTrayColumn;	// 取得 Sub D	的變化
		m_iChipRowL = TotalForD % ChipTrayColumn;	// 取得 Chip D	的變化

		m_iSubColL	= TotalForC / ChipTrayColumn;	// 取得 Sub C	的變化
		m_iChipColL	= TotalForC % ChipTrayColumn;	// 取得 Chip C	的變化

		p.x = m_Align.x + 
			(( m_TraySpec.m_SubTrayA * m_Gear.x ) + ( m_TraySpec.m_SubChipTrayA * m_Gear.x ) + ( m_MeA )) +
			(  m_TraySpec.m_SubTrayC*(m_iSubColL ) * m_Gear.x ) + 
			(  m_TraySpec.m_SubChipTrayC*(m_iChipColL) * m_Gear.x );
		p.y = m_Align.y +
			(( m_TraySpec.m_SubTrayB * m_Gear.y ) + ( m_TraySpec.m_SubChipTrayB * m_Gear.y ) + ( m_MeB )) +
			(  m_TraySpec.m_SubTrayD*(m_iSubRowL ) * m_Gear.y ) + 
			(  m_TraySpec.m_SubChipTrayD*(m_iChipRowL) * m_Gear.y );

	}
	else
	{		
		int m_iRowL = -1; // 跟 y 有關
		int m_iColL = -1; // 跟 x 有關
		
		m_iColL = iNo % m_TraySpec.Column;		// For C
		m_iRowL = iNo / m_TraySpec.Column;		// For D
		
		p.x = m_Align.x + (( m_TraySpec.A * m_Gear.x ) + ( m_TraySpec.C*(m_iColL) * m_Gear.x )) + ( m_MeA );	
		p.y = m_Align.y + (( m_TraySpec.B * m_Gear.y ) + ( m_TraySpec.D*(m_iRowL) * m_Gear.y )) + ( m_MeB );
		
		// Debug
		CString d;
		d.Format("%dD . %dC", m_iRowL, m_iColL );
		f.CWinMessage( d, theApp.enDArm );		

	}

	return p;
}
void CTrayFile::SetSpec(tagTraySpec TraySpec)
{
	m_TraySpec = TraySpec;

	// Chip Tray
	if( m_Chip )
	{
		// 如果是 Chip Tray Mode 就要修改 Column 與 Row
		// 因為要把全部的 Chip tray 合起來當作是一個大的 Tray
		m_TraySpec.Row = m_TraySpec.m_SubTrayRow * m_TraySpec.m_SubChipTrayRow;
		m_TraySpec.Column = m_TraySpec.m_SubTrayColumn * m_TraySpec.m_SubChipTrayColumn;
	}

	// Note : 把 Tray Spec 傳進來的時候, 把 Tray Size 傳進來.
	// m_TraySize 是整個 Tray 可以擺放的IC數量
	m_Row = m_TraySpec.Row;
	m_Col = m_TraySpec.Column;

	m_TraySize = ( m_Row * m_Col );
	TrayStatusResize(); // 重新定義 Tray Size

	// Convert 
	if( m_Chip )
	{
		ConvertChipTray();
		// 產生轉換用的陣列
	}
}

void CTrayFile::SetMe(int A, int B )
{
	// 這裡會給機構誤差, 讓計算原點時把機構誤差也算進去.
	m_MeA = A;
	m_MeB = B;
}

void CTrayFile::TrayStatusResize()
{
	// 不知道為什麼會發神經 先把舊的 delete 掉
	if( m_TrayStatus != NULL )
	{
		delete m_TrayStatus;
		m_TrayStatus = NULL;
	}

	// Check Auto Skip
	if( m_TrayStatusAutoSkip != NULL )
	{
		delete m_TrayStatusAutoSkip;
		m_TrayStatusAutoSkip = NULL;
	}

	// Convert Chip Tray
	if( m_ChipTrayArray != NULL )
	{
		delete m_ChipTrayArray;
		m_ChipTrayArray = NULL;
	}
	// Convert Chip Tray
	if( m_ChipTrayArrayStatus != NULL )
	{
		delete m_ChipTrayArrayStatus;
		m_ChipTrayArrayStatus = NULL;
	}

	m_TrayStatus = new int[m_TraySize];

	// Auto Skip
	m_TrayStatusAutoSkip = new int[m_TraySize];

	// Convert Chip Tray
	m_ChipTrayArray = new int[m_TraySize];
	m_ChipTrayArrayStatus = new int[m_TraySize];
	
	for(int i = 0; i<m_TraySize; i++ )
	{
		m_TrayStatus[i] = enEmpty;
		// 我們宣告一個 Tray 的 Spec 的時候. 先將它設定為 enEmpty
		
		// Check Auto Skip
		m_TrayStatusAutoSkip[i] = enEmpty;

		// Convert Chip Tray
		m_ChipTrayArray[i] = -1;
		m_ChipTrayArrayStatus[i] = enEmpty;
	}	
}

void CTrayFile::SetAlign(tagXYZ Align)
{
	m_Align = Align;
}
void CTrayFile::SetGear(tagXYZ Gear)
{
	m_Gear = Gear;
}

int CTrayFile::TrayiNoGetStatus(int iNo)
{
	// Chip
	if( m_Chip )
		return m_ChipTrayArrayStatus[iNo];

	return m_TrayStatus[iNo];
}

// Check Auto Skip
int CTrayFile::TrayiNoGetStatusAuto(int iNo)
{
	return m_TrayStatusAutoSkip[iNo];
}
// Check Auto Skip
void CTrayFile::TrayiNoGetStatusSetAuto()
{
	m_TrayStatusAutoSkip[m_iNow] = enOK;
}

///////////////////////////////////////////////////////////////////
// 運轉用的功能
BOOL CTrayFile::LocationDone(int DeiNo)
{
	m_TrayStatus[DeiNo] = enOK;

	m_iNow = DeiNo;
	m_iNext = DeiNo + 1;

	SaveLocation();
	// 把狀態記錄到文字檔

	return TRUE;
}

BOOL CTrayFile::LocationDone()
{
	m_iNext++;
	// 然後把下一個位置+1
	// 取到IC或放好IC後才+1
	// 就是當Arm Z回Home OK後

	m_TrayStatus[m_iNow] = enOK; 

	// Chip Tray
	if( m_Chip )
	{
		int iNo = GetChipTrayPosition( m_iNow );
		m_ChipTrayArrayStatus[iNo] = enOK; 
	}

	SaveLocation();
	// 把狀態記錄到文字檔

	return TRUE;
}

BOOL CTrayFile::LocationAllDone()
{
	m_iNow = m_TraySize - 1;
	m_iNext = m_TraySize;

	for(int i = 0; i<m_TraySize; i++ )
		m_TrayStatus[i] = enOK;	
	// 把全部位置設為都使用過 enOK 

	// Convert Chip Tray
	if( m_Chip )
		m_ChipTrayArrayStatus[i] = enOK;	

	SaveLocation();
	// 把狀態記錄到文字檔

	return TRUE;
}
BOOL CTrayFile::LocationMove()
{
	m_TrayStatus[m_iNow] = enMoving;

	// Chip Tray
	if( m_Chip )
	{
		int iNo = GetChipTrayPosition( m_iNow );
		m_ChipTrayArrayStatus[iNo] = enOK; 
	}

	return TRUE;
}
BOOL CTrayFile::LocationMove(int DeiNo)
{
	m_TrayStatus[DeiNo] = enMoving;
	return TRUE;
}

static CMutex MutexTrayFile;
BOOL CTrayFile::LocationQuery()
{
	CSingleLock Lock(&MutexTrayFile);
	Lock.Lock();

	if(m_TraySpec.Row <= 0 || m_TraySpec.Column <= 0)
	{
		Lock.Unlock();	// 要記得解開後才離開
		return enEOF;
	// 沒有輸入 Row. Col. Return Tray 已經結束.
	}

	//
	bool bOk = false;
	for(int i = 0; i<m_TraySize; i++ )
	{
		if (m_TrayStatus[i] == enEmpty || m_TrayStatus[i] == enMoving )
		{
			m_iNext = i;
			bOk = true;
			break;
		}
	}	

	if( m_iNext == m_TraySize || !bOk )
	{
		Lock.Unlock();	// 要記得解開後才離開
		return enEOF;
	}
	// 如果下一個位置等於 m_TraySize , 表示已經取完所有的IC
	// 這個 Tray 已經沒有 IC
	// 通知 Tray 已經結束.
	/////////////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////////////

	Lock.Unlock();

	return m_iNext;
}

BOOL CTrayFile::SemiAuto(int Coord)
{
	m_iNext = Coord;
	return m_iNext;
}


int	CTrayFile::LocationBooking()
{
	m_iNow = m_iNext;
	// 把目前位置設好

	m_TrayStatus[m_iNow] = enBooking;
	// 將要取的位置先設為 enBooking.

	// Chip Tray
	if( m_Chip )
	{
		int iNo = GetChipTrayPosition( m_iNow );
		m_ChipTrayArrayStatus[iNo] = enBooking; 
	}

	return m_iNow;
	// 把目前位置傳出去,給 GetCoordinate 算位置.
}

void CTrayFile::SetFull()
{
	for(int i = 0; i<m_TraySize; i++ )
	{
//		m_TrayStatus[i] = enEmpty;	
		m_TrayStatus[i] = enOK;
		// 有一盤新的 Tray. IC 沒有測試過, 我們將狀態全部設為 enEmpty 

		// Chip Tray
		if( m_Chip )
			m_ChipTrayArrayStatus[i] = enOK;
	}

	m_iNext = m_TraySize;
	// 設為 full
}

void CTrayFile::ChangeTray()
{
	for(int i = 0; i<m_TraySize; i++ )
	{
		m_TrayStatus[i] = enEmpty;	
		// 有一盤新的 Tray. IC 沒有測試過, 我們將狀態全部設為 enEmpty 

		// Check Auto Skip
		m_TrayStatusAutoSkip[i] = enEmpty;

		// Chip Tray
		if( m_Chip )
			m_ChipTrayArrayStatus[i] = enEmpty;
	}
	m_iNext = 0;
	m_iNow = 0;

	SaveLocation();
}
void CTrayFile::LotDoneSetFull()
{
	for(int i = 0; i<m_TraySize; i++ )
	{
		m_TrayStatus[i] = enOK;
		
		// Chip
		if( m_Chip )
			m_ChipTrayArrayStatus[i] = enOK;	
	}
	// LotDone 我們將狀態全部設為 enEmpty 

	m_iNext = 0;
	m_iNow = 0;
	// 設為 full, 表示又需要從第一個位置開始. 也就是 0.
}
void CTrayFile::SetCoordinate(CString csFile)
{
	// 設定檔案位置
	m_Coordinate = csFile;
}
void CTrayFile::SaveLocation()		
{
	// 記錄目前的位置
	if( m_Coordinate == "" )
		return;
	
	f.SaveSetting( m_Coordinate, "Coordinate", "iNow",	m_iNow );
	f.SaveSetting( m_Coordinate, "Coordinate", "iNext",	m_iNext );
}
void CTrayFile::SetLocation()		
{
	// 設定目前的位置
	int iiNow = 0;
	int iiNext = 0;

	f.GetSetting( m_Coordinate, "Coordinate", "iNow",	iiNow );
	f.GetSetting( m_Coordinate, "Coordinate", "iNext",	iiNext );

	if( iiNow == -1 || iiNext == -1 )
	{
		// 表示沒有讀到值, 強迫變成 0 當作是 SetFull
		iiNow = 0;
		iiNext = 0;
	}

	m_iNow = iiNow;
	m_iNext = iiNext;
}
BOOL CTrayFile::SetLocationStatus()
{
	// 重新設定狀態 (根據 iNow 和 iNext )

	if(m_TraySpec.Row <= 0 || m_TraySpec.Column <= 0)
		return enEOF;
	// 沒有輸入 Row. Col. Return Tray 已經結束.

	for(int i = 0; i< m_iNext; i++ )
	{
		m_TrayStatus[i] = enOK;

		if( m_Chip )
		{
			int iNo = GetChipTrayPosition( i );
			m_ChipTrayArrayStatus[iNo] = enOK;
		}
	}
	// 我們宣告一個 Tray 的 Spec 的時候. 先將它設定為 enEmpty

	return TRUE;
}

BOOL CTrayFile::GetStatus(int *pTray, int iSize)
{
	memcpy(pTray, m_TrayStatus, iSize * sizeof(int));

	return TRUE;
}

BOOL CTrayFile::SetStatus(int *pTray, int iSize)
{
	memcpy(m_TrayStatus, pTray, iSize * sizeof(int));

	// Chip Tray
	// 如果有開啟 Chip Tray 的話, 如果 Input Tray 有變更狀態
	// 也要一起更新狀態
	if( m_Chip )
	{
		memcpy(m_ChipTrayArrayStatus, pTray, iSize * sizeof(int));
	}
	return TRUE;
}

BOOL CTrayFile::Check()
{
	BOOL bOK = FALSE;
	for(int i = 0; i<m_TraySize; i++ )
	{
		if (m_TrayStatus[i] == enOK || m_TrayStatus[i] == enMoving )
		{
			bOK = TRUE;
			break;
		}
	}

	return bOK;
}

// Convert Booking 
void CTrayFile::ConvertChipTray()
{
	int itotaltray = 
		( m_TraySpec.m_SubChipTrayColumn * m_TraySpec.m_SubTrayColumn ) * 
		( m_TraySpec.m_SubChipTrayRow * m_TraySpec.m_SubTrayRow );				// 算出包含 Chip Tray 整個 Tray 總共有幾個 IC

	m_ChipTrayArray = new int[itotaltray];
	int TrayArray = 0;

	int InitialValue = 0;
	int ixxxsingletotal =  
		m_TraySpec.m_SubTrayColumn * ( m_TraySpec.m_SubChipTrayColumn * m_TraySpec.m_SubChipTrayRow );
	
	//////////////////////
	int total = m_TraySpec.m_SubChipTrayColumn * m_TraySpec.m_SubChipTrayRow;	// 一個 Chip Tray 的大小
	int *ptrf = new int[total];													// Chip Tray 陣列
	//
	int isingletotal = total * m_TraySpec.m_SubTrayColumn;
	int *ptrtempf = new int[total];
	int *ptrfsingle = new int[isingletotal];
	//

	for( int ic = 0; ic < m_TraySpec.m_SubTrayRow; ic++ )
	{		
		InitialValue = ic * isingletotal;
		// 設定單一 Column 的 起始數值
	
		/////
		int iArray	= 0;
		int iBase	= 0;
//		for( int x = 0; x< m_TraySpec.m_SubChipTrayRow; x++  )
		for( int x = 0; x< m_TraySpec.m_SubChipTrayRow; x++  )
		{
			for( int y = 0; y<m_TraySpec.m_SubChipTrayColumn; y++ )
			{
				int c = iArray / m_TraySpec.m_SubChipTrayColumn;
				int d = c * m_TraySpec.m_SubChipTrayColumn * m_TraySpec.m_SubTrayColumn + InitialValue;

				ptrf[iArray] = d + iBase;
				iBase++;
				iArray++;
			}
			iBase = 0;
		}	
		// 先求出第一盤的數列
		// ptrf[iArray] 每列第一盤的陣列
		
		for( int d = 0; d < total; d++ )
		{
			ptrfsingle[d] = ptrf[d];
			ptrtempf[d] = ptrf[d];
		}
		
		int iCount = 0;
		for( int i = total; i < isingletotal ;i ++ )
		{	
			ptrfsingle[i]		= ptrtempf[iCount] + m_TraySpec.m_SubChipTrayColumn;
			ptrtempf[iCount]	= ptrfsingle[i];
			
			iCount ++;
			
			if( iCount == total )
				iCount = 0;
		}
		/*
		// Debug 
		CString cs = "";
		for(int de = 0; de<isingletotal;de++ )
		{
		CString dd = "";
		dd.Format("%d,", ptrfsingle[de]);
		cs = cs + dd;
		}
		AfxMessageBox( cs );
		*/
		///
		for( int r = 0; r < isingletotal; r++ )
		{
			m_ChipTrayArray[TrayArray] = ptrfsingle[r];
			TrayArray++;
		}
		// 把陣列填到數列
	}
	
	// Debug 
/*
	CString cs;
	for( int de = 0; de< itotaltray; de++)
	{	
		CString ddf;
		ddf.Format("%d,", m_ChipTrayArray[de]);
		cs = cs + ddf;
	}
	AfxMessageBox( cs );
*/

	delete [] ptrf;
	delete [] ptrfsingle;
	delete [] ptrtempf;
	// 刪除陣列
}

int CTrayFile::GetChipTrayPosition( int iBooking )
{
	int m_iIndex = -1;

	m_iIndex = m_ChipTrayArray[iBooking];

	return m_iIndex;
}

