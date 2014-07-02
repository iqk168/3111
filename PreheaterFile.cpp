// PreheaterFile.cpp: implementation of the CPreheaterFile class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Deer.h"
#include "PreheaterFile.h"

#include <cmath>
#include <afxmt.h>
// avoid crash in status array.

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPreheaterFile::CPreheaterFile()
{
	m_Time[0] = COleDateTime::GetCurrentTime();
	for(int i=1; i<200; i++)
		m_Time[i] = m_Time[0];

	m_iNext = 1;
}

CPreheaterFile::~CPreheaterFile()
{
	Save();
}

BOOL CPreheaterFile::ClearBuffer()
{
	/////////////////////////////////////////
	// clear plate buffer
	m_iNext = 1;
	m_iCount = 0;

	Save();

	return TRUE;
}
	   
CPoint CPreheaterFile::GetCoordinate(int iNo)
{
	if(iNo <= 0 || iNo > m_TraySpec.PlateRow * m_TraySpec.PlateColumn)
		iNo = 1;

	//
	// 轉換後, 會把 Dut#1 的位置, 改變到左邊, 如果要轉為右邊, 就把它 Mark 掉
	iNo = Convert( iNo );

	CPoint p;

	int j = (iNo + m_TraySpec.PlateColumn - 1) / m_TraySpec.PlateColumn;
	int k = iNo - (j-1) * m_TraySpec.PlateColumn;

	p.x = (long)(m_Align.x + 
		( m_TraySpec.PlateA + (m_TraySpec.PlateColumn - k)
		* m_TraySpec.PlateC) * m_Gear.x ) + ( m_MeA );
	
	p.y = (long)(m_Align.y + 
		( m_TraySpec.PlateB + (j - 1) * m_TraySpec.PlateD)
		* m_Gear.y) + ( m_MeB );

	return p;
}

long CPreheaterFile::GetRemainSoakTime()
{
	if(m_iCount <= 0)
		return 0;

	int start = m_iNext - m_iCount;
	int max = m_TraySpec.PlateRow * m_TraySpec.PlateColumn;
	while(start <= 0)
		start += max;

	COleDateTimeSpan t = COleDateTime::GetCurrentTime() - m_Time[start-1];
	long spent = (long)t.GetTotalSeconds();
	if(spent >= m_iSoakTime)
		return 0;
	else
		return m_iSoakTime - spent;
}

void CPreheaterFile::InputDone()
{
	m_Time[m_iNext-1] = COleDateTime::GetCurrentTime();
	m_iNext++;
	m_iCount++;

	if(m_iNext > m_TraySpec.PlateRow * m_TraySpec.PlateColumn)
		m_iNext = 1;
}

BOOL CPreheaterFile::InputLocationQuery()
{
	if(m_TraySpec.PlateRow <= 0 || m_TraySpec.PlateColumn <= 0)
		return enEOF;

	if(m_iCount >= m_TraySpec.PlateRow * m_TraySpec.PlateColumn)
		return enEOF;

	return m_iNext;
}

void CPreheaterFile::OutputDone()
{
	m_iCount--;
}

BOOL CPreheaterFile::OutputLocationQuery()
{
	if(m_iCount <= 0)
		return enEmpty;

	int start = m_iNext - m_iCount;
	int max = m_TraySpec.PlateRow * m_TraySpec.PlateColumn;
	while(start <= 0)
		start += max;

	COleDateTimeSpan t = COleDateTime::GetCurrentTime() - m_Time[start-1];
	long spent = (long)t.GetTotalSeconds();
	if(spent >= m_iSoakTime)
		return start;
	else
		return enEOF;
}

void CPreheaterFile::SetCoordinate(CString csFile)
{
	// 設定檔案位置
	m_Coordinate = csFile;
}
void CPreheaterFile::Save()
{
	// 記錄目前的位置
	if( m_Coordinate == "" )
		return;
	
	f.SaveSetting( m_Coordinate, "Coordinate", "iCount",	m_iCount );
	f.SaveSetting( m_Coordinate, "Coordinate", "iNext",		m_iNext );
}
void CPreheaterFile::LoadFile()
{
	m_Time[0] = COleDateTime::GetCurrentTime();
	for(int i=1; i<_MaxPreHeaterDevice; i++)
		m_Time[i] = m_Time[0];

	Load();
}
void CPreheaterFile::Load()
{
	// 記錄目前的位置
	if( m_Coordinate == "" )
		return;

	f.GetSetting( m_Coordinate, "Coordinate", "iNext",	m_iNext );
	f.GetSetting( m_Coordinate, "Coordinate", "iCount",	m_iCount );		
}	

int CPreheaterFile::GetiNext()
{
	return m_iNext;
}
int CPreheaterFile::GetiCount()
{
	return m_iCount;
}
void CPreheaterFile::SetSoak(long SoakTime)
{
	m_iSoakTime = SoakTime;
}

void CPreheaterFile::SetAlign(tagXYZ Align)
{
	m_Align = Align;
}
void CPreheaterFile::SetGear(tagXYZ Gear)
{
	m_Gear = Gear;
}

void CPreheaterFile::SetMe(int A, int B )
{
	// 這裡會給機構誤差, 讓計算原點時把機構誤差也算進去.
	m_MeA = A;
	m_MeB = B;
}

int	CPreheaterFile::Convert( int iNo )
{	
	int iConvert = -1;
	iNo = iNo - 1;

	iConvert = m_TraySpec.PlateColumn * ( ( iNo / m_TraySpec.PlateColumn ) + 1 ) - 
		( ( iNo % m_TraySpec.PlateColumn ) + 1 );


	iConvert = iConvert + 1;

	return iConvert;
}

void CPreheaterFile::SetSpec(tagTraySpec TraySpec)
{
	m_TraySpec = TraySpec;

}
void CPreheaterFile::SetSoakTime(long time)
{
	m_iSoakTime = time;
}