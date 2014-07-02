// ViewTrayMap.cpp : implementation file
//

#include "stdafx.h"
#include "deer.h"
#include "ViewTrayMap.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CViewTrayMap

IMPLEMENT_DYNCREATE(CViewTrayMap, CView)

CViewTrayMap::CViewTrayMap()
{		
	font.CreatePointFont(60, "Arial");

	// TrayMpa Page
	iTray = -1; // default is -1, if no set TrayID. return it.
	m_iPage = 1;
	m_iPageCount = 0;

	// FT
	m_bBrush = false;
	m_bBinColor = false;

	// SLT
	m_bCustomColor = false;
	iCustomColorSize = 0;
	m_BinCustomBrush[0].CreateSolidBrush( ST_GRAY );

	// Chip Tray
	m_iChip = -1;

	//
	nBkColor = RGB(255, 255, 255);

	//
	m_iRepeatMode = enTrayMapModeNone;
}

CViewTrayMap::~CViewTrayMap()
{
}


BEGIN_MESSAGE_MAP(CViewTrayMap, CView)
	//{{AFX_MSG_MAP(CViewTrayMap)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CViewTrayMap drawing
void CViewTrayMap::SetRepeatTray(int iMode)
{
	// 0 is normal
	// 1 is input/output ctrl

	m_iRepeatMode = iMode;
}
bool CViewTrayMap::SetCustomColor(CString csCode, COLORREF crColor)			
{	
	if( csCode == "" || crColor <= 0 )
		return false;

	m_bCustomColor = true;
	m_BinCode.Add( csCode );
	m_BinColor.Add( crColor );

	iCustomColorSize++;

	return true;
}
void CViewTrayMap::ClearCsutomColor()			
{
	m_bCustomColor = false;
	m_BinCode.RemoveAll();
	m_BinColor.RemoveAll();

	iCustomColorSize = 0;
}
COLORREF CViewTrayMap::GetCustomColor(CString csCode)
{
	// 由 Code 去 Mapping Color
	COLORREF color = ST_GRAY;;
	
	int iSize = m_BinCode.GetSize();
	int iCodeNumber = -1;
	for(int i=0;i<iSize;i++)
	{
		CString csRefCode = _T("");
		csRefCode = m_BinCode.GetAt(i);

		if( csRefCode == csCode )
			iCodeNumber = i;
	}

	int ibound = 0;
	ibound = m_BinColor.GetUpperBound();
	if( iCodeNumber > ibound )
		; // Gray
	else if ( iCodeNumber == -1 )
		; // Gray // can not find code to mapping color.
	else
		color = m_BinColor.GetAt( iCodeNumber );

	return color;
}
CString CViewTrayMap::GetColorList()							
{
	// 讓外部看一下被新增的檔案
	CString csList = _T("");
	
	int iSize = m_BinCode.GetSize();
	for(int i=0;i<iSize;i++)
	{
		CString csMsg = _T("");		
		csMsg.Format( "Code: %s, Color: %d\r\n", m_BinCode.GetAt(i), m_BinColor.GetAt(i) );
		csList += csMsg;
	}

	return csList;
} 
/////////////////////////////////////////////////////////////////////////////
// Change Page.
void CViewTrayMap::ChangePageUp()
{
	if( m_iPage > m_iPageCount - 1)
		return;

	// 更改到上一頁
	m_iPage++;
}
void CViewTrayMap::ChangePageDown()
{
	if( m_iPage == 1 )
		return;

	// 更改到下一頁
	m_iPage--;
}
void CViewTrayMap::ChangePage(int Page)
{
	if( Page < 1 )
		return;

	if( Page > m_iPageCount - 1)
		return;

	// 強迫切換頁數
	m_iPage = Page;
}
int	CViewTrayMap::GetNowPage()
{
	// 回傳當下頁數
	return m_iPage;
}
void CViewTrayMap::ChangePageCount(int count)
{
	// 增加目前頁數
	m_iPageCount = count;
}
int CViewTrayMap::GetPageCount()	
{
	// 回傳已經有幾頁
	return m_iPageCount;
}
/////////////////////////////////////////////////////////////////////////////
void CViewTrayMap::SetChipMode(int Chip)
{
	m_iChip = Chip;
}
void CViewTrayMap::SetTrayID(int ID)
{
	if( ID < 0 )
		iTray = -1;
	else
		iTray = ID;
	// set Tray ID
}
void CViewTrayMap::SetTrayBrush(COLORREF crColor)
{
	m_bBrush = true;
	m_Brush[0].CreateSolidBrush( crColor );
}
void CViewTrayMap::SetBinColor(int bin, COLORREF crColor )
{
	iBinColor[bin] = crColor;
}
void CViewTrayMap::SetTrayBrush( bool bBin, int ID )
{
	// 避免設定有問題, 先給預設值
	if( ID == 0 )
		m_Brush[0].CreateSolidBrush( RGB(0, 255, 0) );	
	else if(ID == 1)
		m_Brush[0].CreateSolidBrush( RGB( 255, 0, 0) );	
	else if(ID == 2)
		m_Brush[0].CreateSolidBrush( RGB( 255, 255, 0) );
	else if(ID == 3)
		m_Brush[0].CreateSolidBrush( RGB( 255, 128, 0) );
	else
		m_Brush[0].CreateSolidBrush( RGB(166, 202, 240) );

	m_bBinColor = true;
	for(int i=0;i<_Tray_Bin;i++)
		m_BinBrush[i].CreateSolidBrush( iBinColor[i] );
	// 由外部檔案載入 TrayMap.color
}
void CViewTrayMap::SetTrayBrush(int ID)
{
	if( ID == 0 )
		m_Brush[0].CreateSolidBrush( RGB(0, 255, 0) );	
	else if(ID == 1)
		m_Brush[0].CreateSolidBrush( RGB( 255, 0, 0) );	
	else if(ID == 2)
		m_Brush[0].CreateSolidBrush( RGB( 255, 255, 0) );
	else if(ID == 3)
		m_Brush[0].CreateSolidBrush( RGB( 255, 128, 0) );
	else
		m_Brush[0].CreateSolidBrush( RGB(166, 202, 240) );
}

int CViewTrayMap::ChangeBrush(CString Code )
{
	if( m_bBinColor )
	{		
		if( Code == "0" )
			return 0;
		else if( Code == "1" )
			return 1;
		else if( Code == "2" )
			return 2;
		else if( Code == "3" )
			return 3;
		else if( Code == "4" )
			return 4;
		else if( Code == "5" )
			return 5;
		else if( Code == "6" )
			return 6;
		else if( Code == "7" )
			return 7;
		else if( Code == "8" )
			return 8;
		else if( Code == "9" )
			return 9;
		else if( Code == "10" )
			return 10;
		else if( Code == "11" )
			return 11;
		else if( Code == "12" )
			return 12;
		else if( Code == "13" )
			return 13;
		else if( Code == "14" )
			return 14;
		else if( Code == "15" )
			return 15;
		else if( Code == "16" )
			return 16;
		else
			return 0;
	}
	else
		return 0;
}

// 1.0An
// Remove this and re-build new one
/*
void CViewTrayMap::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here

	CBitmap bmp;
	CDC		dcMemory;

	CRect rect;
	GetClientRect(rect);
	// Complete wrong. It will get dialog rect

	CClientDC dc(this);
	dcMemory.CreateCompatibleDC(&dc);
	bmp.CreateCompatibleBitmap(&dc, rect.Width(), rect.Height());
	dcMemory.SelectObject(&bmp);
	dcMemory.FillRect(rect, &CBrush(RGB(0, 0, 255)));
	dcMemory.FillRect(rect, &CBrush( nBkColor ));

	//
	int	iStackNow = 0;
	int OldPos = 0;

	// If Programer no set tray ID. return it. Do not do anything.
	if( iTray == -1 )
		return;

	// Draw Tray
	int iColumn = -1;
	int iRow = -1;
	if( m_iChip )
	{
		iColumn = m.TraySpec.m_SubTrayColumn * m.TraySpec.m_SubChipTrayColumn;
		iRow = m.TraySpec.m_SubTrayRow * m.TraySpec.m_SubChipTrayRow;
	}
	else
	{
		iColumn = m.TraySpec.Column;
		iRow = m.TraySpec.Row;
	}

	////////////////////////////////////////////////////////////////
	// CView Tray 的設定檔
	double LeftSide		= m.Setting.m_dTraySpecLeftSide;		// 左邊離 CStatic 的間距.
	double TopSide		= m.Setting.m_dTraySpecTopSide;			// 上方離 CStatic 的間距.
	int e = iTray;												// 目前這個 CView 該顯示那一個 OutputTrayMap.
	int ICSide			= m.Setting.m_dTraySpecICSide;			// IC 在格子裡面. 顯示顏色與邊框的距離.

	int ICTextTopSide	= m.Setting.m_dTraySpecTextUpSide;		// IC 顯示訊資訊的 TextOut 的距離.微調用
	int ICTextLeftSide	= m.Setting.m_dTraySpecTextLeftSide;	// IC 顯示訊資訊的 TextOut 的距離.微調用
	int nBkColor		= m.Setting.m_iTraySpecBkColor;	
	dcMemory.FillRect(rect, &CBrush( nBkColor ));

	// 讓文字可以被修改
	int ICTextSize = 60 + ( m.Setting.m_iTraySpecTextSize * 10 );
	int ICTextBreak = 8 + m.Setting.m_iTraySpecTextBreak;
	////////////////////////////////////////////////////////////////

	if(iColumn <=0 || iRow <=0) 
		return;

	dcMemory.SelectObject(&font);

	// 變更 Text Out 字體大小.!
	////////////////////////////////////////////////////////////
	CFont front;
	LOGFONT lf;
	memset(&lf, 0, sizeof(LOGFONT));			// clear out structure.
	lf.lfHeight = ICTextSize;                   // request a 12-pixel-height font
	strcpy(lf.lfFaceName, "Arial");	
//	CClientDC dc(this);
	CFont font;
	VERIFY(font.CreatePointFontIndirect(&lf, &dc));	
	dcMemory.SelectObject( &font );
	////////////////////////////////////////////////////////////
	
	// Chip
	// 如果是 Chip Tray 預設的頁數由 1 開始
	if( m_iChip )
		iStackNow = 1;

	double iXPitch = rect.Width()	/ iColumn;
	double iYPitch = rect.Height()	/ iRow;

	CRect rectH;
	dcMemory.SetTextAlign(TA_RIGHT);

	// Output 1
	for(int i=0; i<iColumn; i++)
	{
		for(int j=0; j<iRow; j++)
		{
			rectH.left =	(long)((i)*iXPitch) + LeftSide;
			rectH.right =	(long)(i+1)*iXPitch;
			rectH.top =		(long)(j)*iYPitch	+ TopSide;
			rectH.bottom =	(long)(j+1)*iYPitch;
			dcMemory.Rectangle(&rectH);
			// 畫 TrayFile 的格子
		}
	}

	/////////////////////////////////////////////////////////////////////////////////////////////////////
	// Draw Output 1 Device
	std::list<tagTrayMap>::iterator p = m.TrayMap[e].begin();
	for(i=0; i<m.TrayMap[e].size(); i++, p++)
	{		
		// TrayMap 顯示變更
		// TrayMap 的邏輯很簡單, 就是 座標 y * column > 前一次的 y * column 
		// 就表示說已經讀到前一頁的 紀錄
		// 但是 Chip Tray 的邏輯需要變更
		if( m_iChip )
		{
			// 如果讀到最大頁數, 當作是換頁
			if( p->pos.x * p->pos.y == iColumn * iRow )
				iStackNow++;
		}
		else
		{
			if((p->pos.x + p->pos.y * iColumn) >= OldPos)
				iStackNow++;
		}

		OldPos = p->pos.x + p->pos.y * iColumn;
		if( iStackNow == m_iPage )
		{			
			rectH.left =	(long)((p->pos.x-1)*iXPitch)	+ LeftSide  + ICSide;
			rectH.right =	(long)((p->pos.x)*iXPitch)		- ICSide;
			rectH.top =		(long)((p->pos.y-1)*iYPitch)	+ TopSide	+ ICSide;
			rectH.bottom =	(long)((p->pos.y)*iYPitch)		- ICSide;

			CString csCode = "";
			csCode.Format("%s", p->code );
			
			if( m_bBinColor )
			{
				int iBrush = ChangeBrush( csCode );
				dcMemory.FillRect(&rectH, &m_BinBrush[iBrush]);		// 自訂的顏色 FT 1~16 Bin　的模式
			}
			else if( m_bCustomColor )
			{
				COLORREF crcolor = ST_GRAY;
				crcolor = GetCustomColor( csCode );
				m_BinCustomBrush[0].DeleteObject();
				m_BinCustomBrush[0].CreateSolidBrush( crcolor );
				dcMemory.FillRect(&rectH, &m_BinCustomBrush[0]);	// 自訂的顏色 FT 1~16 Bin　的模式
			}
			else
				dcMemory.FillRect(&rectH, &m_Brush[0]);				// 預設的顏色 只顯示一種顏色的模式
			
			// Note : 請注意, 在 pos 裡面儲存的是座標點 (x,y). 
			// 左上角是第一顆, 右邊是第二顆
			// 第一顆是 (1,1). 第二顆是 (2.1) 第三顆是 (3.1) 以此類推.
			
			if( m.TrayMapSetting.bCode && !m.TrayMapSetting.bTemp )
			{
				CString csSite; // Whitch Information we want to show.
				csSite.Format("(%s)", p->code);
				if( csSite.GetLength() > ICTextBreak )
				{
					int s = ((long)((p->pos.y-1)*iYPitch) + (iYPitch*0.1) + TopSide + ICSide ) + ICTextTopSide;
					// 第二行放在中間往下 0.1 個 YPitch 的地方
					dcMemory.TextOut( 
						((long)((p->pos.x-1)*iXPitch) + (iXPitch*0.5) + LeftSide + ICSide ) + ICTextLeftSide, 
						s - (0.5*s), 
						csSite.Left(8) );
					// 第一行放在中間往上 0.2 個 YPitch 的地方
					dcMemory.TextOut( 
						((long)((p->pos.x-1)*iXPitch) + (iXPitch*0.5) + LeftSide + ICSide ) + ICTextLeftSide, 
						s + (0.2*s), 
						csSite.Right(csSite.GetLength()-8) );	
				}
				else
				{
					dcMemory.TextOut( 
						((long)((p->pos.x-1)*iXPitch) + (iXPitch*0.8) + LeftSide + ICSide ) + ICTextLeftSide, 
						((long)((p->pos.y-1)*iYPitch) + (iYPitch*0.1) + TopSide + ICSide ) + ICTextTopSide, 
						csSite );
					// Note : 我們把字串顯示在格子接近中間位置往下 和 往右 兩個距離.
					// 中間位置為 x 的0.8距離. y的 0.1距離
				}
			}
			// Display Code.
			/////////////////////////////////////////////////////////////////////////////////////////////////////
			/////////////////////////////////////////////////////////////////////////////////////////////////////
						
			if(  m.TrayMapSetting.bTemp && !m.TrayMapSetting.bCode)
			{
				CString csSite; // Whitch Information we want to show.
				csSite.Format("%.1f", p->temperature);
				if( csSite.GetLength() > ICTextBreak )
				{
					int s = ((long)((p->pos.y-1)*iYPitch) + (iYPitch*0.1) + TopSide + ICSide ) + ICTextTopSide;
					// 第二行放在中間往下 0.1 個 YPitch 的地方
					dcMemory.TextOut( 
						((long)((p->pos.x-1)*iXPitch) + (iXPitch*0.5) + LeftSide + ICSide ) + ICTextLeftSide, 
						s - (0.5*s), 
						csSite.Left(8) );
					// 第一行放在中間往上 0.2 個 YPitch 的地方
					dcMemory.TextOut( 
						((long)((p->pos.x-1)*iXPitch) + (iXPitch*0.5) + LeftSide + ICSide ) + ICTextLeftSide, 
						s + (0.2*s), 
						csSite.Right(csSite.GetLength()-8) );	
				}
				else
				{
					dcMemory.TextOut( 
						((long)((p->pos.x-1)*iXPitch) + (iXPitch*0.4) + LeftSide + ICSide ) + ICTextLeftSide, 
						((long)((p->pos.y-1)*iYPitch) + (iYPitch*0.1) + TopSide + ICSide ) + ICTextTopSide, 
						csSite );
					// Note : 我們把字串顯示在格子接近中間位置往下 和 往右 兩個距離.
					// 中間位置為 x 的0.8距離. y的 0.1距離
				}
			}
			// Display Temp.
			
			if(  m.TrayMapSetting.bTemp && m.TrayMapSetting.bCode)
			{
				CString csSite; // Whitch Information we want to show.
				csSite.Format("%s(%.1f)", p->code, p->temperature);
				if( csSite.GetLength() > ICTextBreak )
				{
					int s = ((long)((p->pos.y-1)*iYPitch) + (iYPitch*0.1) + TopSide + ICSide ) + ICTextTopSide;
					// 第二行放在中間往下 0.1 個 YPitch 的地方
					dcMemory.TextOut( 
						((long)((p->pos.x-1)*iXPitch) + (iXPitch*0.8) + LeftSide + ICSide ) + ICTextLeftSide, 
						s - (0.5*s), 
						csSite.Left(8) );
					// 第一行放在中間往上 0.2 個 YPitch 的地方
					dcMemory.TextOut( 
						((long)((p->pos.x-1)*iXPitch) + (iXPitch*0.8) + LeftSide + ICSide ) + ICTextLeftSide, 
						s + (0.2*s), 
						csSite.Right(csSite.GetLength()-8) );	
				}
				else
				{
					dcMemory.TextOut( 
						((long)((p->pos.x-1)*iXPitch) + (iXPitch*0.4) + LeftSide + ICSide ) + ICTextLeftSide, 
						((long)((p->pos.y-1)*iYPitch) + (iYPitch*0.1) + TopSide + ICSide ) + ICTextTopSide, 
						csSite );
					// Note : 我們把字串顯示在格子接近中間位置往下 和 往右 兩個距離.
					// 中間位置為 x 的0.8距離. y的 0.1距離
				}
			}
			// Display Temp and Code.
		}
	}

	pDC->BitBlt(0, 0, rect.Width(), rect.Height(), &dcMemory, 0, 0, SRCCOPY);
	ReleaseDC(&dcMemory);
}
*/
void CViewTrayMap::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here

	CBitmap bmp;
	CDC		dcMemory;

	CRect rect;
	GetClientRect(rect);
	// Complete wrong. It will get dialog rect

	CClientDC dc(this);
	dcMemory.CreateCompatibleDC(&dc);
	bmp.CreateCompatibleBitmap(&dc, rect.Width(), rect.Height());
	dcMemory.SelectObject(&bmp);
	dcMemory.FillRect(rect, &CBrush(RGB(0, 0, 255)));
	dcMemory.FillRect(rect, &CBrush( nBkColor ));

	//
	int	iStackNow = 0;
	int OldPos = 0;

	// If Programer no set tray ID. return it. Do not do anything.
	if( iTray == -1 )
		return;

	// Draw Tray
	int iColumn = -1;
	int iRow = -1;
	if( m_iChip )
	{
		iColumn = m.TraySpec.m_SubTrayColumn * m.TraySpec.m_SubChipTrayColumn;
		iRow = m.TraySpec.m_SubTrayRow * m.TraySpec.m_SubChipTrayRow;
	}
	else
	{
		iColumn = m.TraySpec.Column;
		iRow = m.TraySpec.Row;
	}

	////////////////////////////////////////////////////////////////
	// CView Tray 的設定檔
	double LeftSide		= m.Setting.m_dTraySpecLeftSide;		// 左邊離 CStatic 的間距.
	double TopSide		= m.Setting.m_dTraySpecTopSide;			// 上方離 CStatic 的間距.
	int e = iTray;												// 目前這個 CView 該顯示那一個 OutputTrayMap.
	int ICSide			= m.Setting.m_dTraySpecICSide;			// IC 在格子裡面. 顯示顏色與邊框的距離.

	int ICTextTopSide	= m.Setting.m_dTraySpecTextUpSide;		// IC 顯示訊資訊的 TextOut 的距離.微調用
	int ICTextLeftSide	= m.Setting.m_dTraySpecTextLeftSide;	// IC 顯示訊資訊的 TextOut 的距離.微調用
	int nBkColor		= m.Setting.m_iTraySpecBkColor;	
	dcMemory.FillRect(rect, &CBrush( nBkColor ));

	// 讓文字可以被修改
	int ICTextSize = 60 + ( m.Setting.m_iTraySpecTextSize * 10 );
	int ICTextBreak = 8 + m.Setting.m_iTraySpecTextBreak;
	////////////////////////////////////////////////////////////////

	if(iColumn <=0 || iRow <=0) 
		return;

	dcMemory.SelectObject(&font);

	// 變更 Text Out 字體大小.!
	////////////////////////////////////////////////////////////
	CFont front;
	LOGFONT lf;
	memset(&lf, 0, sizeof(LOGFONT));			// clear out structure.
	lf.lfHeight = ICTextSize;                   // request a 12-pixel-height font
	strcpy(lf.lfFaceName, "Arial");	
//	CClientDC dc(this);
	CFont font;
	VERIFY(font.CreatePointFontIndirect(&lf, &dc));	
	dcMemory.SelectObject( &font );
	////////////////////////////////////////////////////////////
	
	// Chip
	// 如果是 Chip Tray 預設的頁數由 1 開始
	if( m_iChip )
		iStackNow = 1;

	double iXPitch = rect.Width()	/ iColumn;
	double iYPitch = rect.Height()	/ iRow;

	CRect rectH;
	dcMemory.SetTextAlign(TA_RIGHT);

	// Output 1
	for(int i=0; i<iColumn; i++)
	{
		for(int j=0; j<iRow; j++)
		{
			rectH.left =	(long)((i)*iXPitch) + LeftSide;
			rectH.right =	(long)(i+1)*iXPitch;
			rectH.top =		(long)(j)*iYPitch	+ TopSide;
			rectH.bottom =	(long)(j+1)*iYPitch;
			dcMemory.Rectangle(&rectH);
			// 畫 TrayFile 的格子
		}
	}

	/////////////////////////////////////////////////////////////////////////////////////////////////////
	// Draw Output 1 Device
	int iTrayMapSize = 0;
	std::list<tagTrayMap>::iterator p;
	if( m_iRepeatMode == enTrayMapModeNone )
	{
		p = m.TrayMap[e].begin();
		iTrayMapSize = m.TrayMap[e].size();
	}
	else if( m_iRepeatMode == enTrayMapModeInOutCtrl )
	{
		p = m.TrayMapRepeat[e].begin();
		iTrayMapSize = m.TrayMapRepeat[e].size();	
	}
	else
	{
		p = m.TrayMap[e].begin();
		iTrayMapSize = m.TrayMap[e].size();	
	}
	
	//
	for(i=0; i<iTrayMapSize; i++, p++)
	{		
		// TrayMap 顯示變更
		// TrayMap 的邏輯很簡單, 就是 座標 y * column > 前一次的 y * column 
		// 就表示說已經讀到前一頁的 紀錄
		// 但是 Chip Tray 的邏輯需要變更
		if( m_iChip )
		{
			// 如果讀到最大頁數, 當作是換頁
			if( p->pos.x * p->pos.y == iColumn * iRow )
			{
				iStackNow++;
				m_iPageCount = iStackNow;
			}
		}
		else
		{
			if((p->pos.x + p->pos.y * iColumn) >= OldPos)
			{
				iStackNow++;
				m_iPageCount = iStackNow;
			}
		}

		OldPos = p->pos.x + p->pos.y * iColumn;
		if( iStackNow == m_iPage )
		{			
			rectH.left =	(long)((p->pos.x-1)*iXPitch)	+ LeftSide  + ICSide;
			rectH.right =	(long)((p->pos.x)*iXPitch)		- ICSide;
			rectH.top =		(long)((p->pos.y-1)*iYPitch)	+ TopSide	+ ICSide;
			rectH.bottom =	(long)((p->pos.y)*iYPitch)		- ICSide;

			CString csCode = "";
			csCode.Format("%s", p->code );
			
			if( m_bBinColor )
			{
				int iBrush = ChangeBrush( csCode );
				dcMemory.FillRect(&rectH, &m_BinBrush[iBrush]);		// 自訂的顏色 FT 1~16 Bin　的模式
			}
			else if( m_bCustomColor )
			{
				COLORREF crcolor = ST_GRAY;
				crcolor = GetCustomColor( csCode );
				m_BinCustomBrush[0].DeleteObject();
				m_BinCustomBrush[0].CreateSolidBrush( crcolor );
				dcMemory.FillRect(&rectH, &m_BinCustomBrush[0]);	// 自訂的顏色 FT 1~16 Bin　的模式
			}
			else
				dcMemory.FillRect(&rectH, &m_Brush[0]);				// 預設的顏色 只顯示一種顏色的模式
			
			// Note : 請注意, 在 pos 裡面儲存的是座標點 (x,y). 
			// 左上角是第一顆, 右邊是第二顆
			// 第一顆是 (1,1). 第二顆是 (2.1) 第三顆是 (3.1) 以此類推.
			
			if( m.TrayMapSetting.bCode && !m.TrayMapSetting.bTemp )
			{
				CString csSite; // Whitch Information we want to show.
				csSite.Format("(%s)", p->code);
				if( csSite.GetLength() > ICTextBreak )
				{
					int s = ((long)((p->pos.y-1)*iYPitch) + (iYPitch*0.1) + TopSide + ICSide ) + ICTextTopSide;
					// 第二行放在中間往下 0.1 個 YPitch 的地方
					dcMemory.TextOut( 
						((long)((p->pos.x-1)*iXPitch) + (iXPitch*0.5) + LeftSide + ICSide ) + ICTextLeftSide, 
						s - (0.5*s), 
						csSite.Left(8) );
					// 第一行放在中間往上 0.2 個 YPitch 的地方
					dcMemory.TextOut( 
						((long)((p->pos.x-1)*iXPitch) + (iXPitch*0.5) + LeftSide + ICSide ) + ICTextLeftSide, 
						s + (0.2*s), 
						csSite.Right(csSite.GetLength()-8) );	
				}
				else
				{
					dcMemory.TextOut( 
						((long)((p->pos.x-1)*iXPitch) + (iXPitch*0.8) + LeftSide + ICSide ) + ICTextLeftSide, 
						((long)((p->pos.y-1)*iYPitch) + (iYPitch*0.1) + TopSide + ICSide ) + ICTextTopSide, 
						csSite );
					// Note : 我們把字串顯示在格子接近中間位置往下 和 往右 兩個距離.
					// 中間位置為 x 的0.8距離. y的 0.1距離
				}
			}
			// Display Code.
			/////////////////////////////////////////////////////////////////////////////////////////////////////
			/////////////////////////////////////////////////////////////////////////////////////////////////////
						
			if(  m.TrayMapSetting.bTemp && !m.TrayMapSetting.bCode)
			{
				CString csSite; // Whitch Information we want to show.
				csSite.Format("%.1f", p->temperature);
				if( csSite.GetLength() > ICTextBreak )
				{
					int s = ((long)((p->pos.y-1)*iYPitch) + (iYPitch*0.1) + TopSide + ICSide ) + ICTextTopSide;
					// 第二行放在中間往下 0.1 個 YPitch 的地方
					dcMemory.TextOut( 
						((long)((p->pos.x-1)*iXPitch) + (iXPitch*0.5) + LeftSide + ICSide ) + ICTextLeftSide, 
						s - (0.5*s), 
						csSite.Left(8) );
					// 第一行放在中間往上 0.2 個 YPitch 的地方
					dcMemory.TextOut( 
						((long)((p->pos.x-1)*iXPitch) + (iXPitch*0.5) + LeftSide + ICSide ) + ICTextLeftSide, 
						s + (0.2*s), 
						csSite.Right(csSite.GetLength()-8) );	
				}
				else
				{
					dcMemory.TextOut( 
						((long)((p->pos.x-1)*iXPitch) + (iXPitch*0.4) + LeftSide + ICSide ) + ICTextLeftSide, 
						((long)((p->pos.y-1)*iYPitch) + (iYPitch*0.1) + TopSide + ICSide ) + ICTextTopSide, 
						csSite );
					// Note : 我們把字串顯示在格子接近中間位置往下 和 往右 兩個距離.
					// 中間位置為 x 的0.8距離. y的 0.1距離
				}
			}
			// Display Temp.
			
			if(  m.TrayMapSetting.bTemp && m.TrayMapSetting.bCode)
			{
				CString csSite; // Whitch Information we want to show.
				csSite.Format("%s(%.1f)", p->code, p->temperature);
				if( csSite.GetLength() > ICTextBreak )
				{
					int s = ((long)((p->pos.y-1)*iYPitch) + (iYPitch*0.1) + TopSide + ICSide ) + ICTextTopSide;
					// 第二行放在中間往下 0.1 個 YPitch 的地方
					dcMemory.TextOut( 
						((long)((p->pos.x-1)*iXPitch) + (iXPitch*0.8) + LeftSide + ICSide ) + ICTextLeftSide, 
						s - (0.5*s), 
						csSite.Left(8) );
					// 第一行放在中間往上 0.2 個 YPitch 的地方
					dcMemory.TextOut( 
						((long)((p->pos.x-1)*iXPitch) + (iXPitch*0.8) + LeftSide + ICSide ) + ICTextLeftSide, 
						s + (0.2*s), 
						csSite.Right(csSite.GetLength()-8) );	
				}
				else
				{
					dcMemory.TextOut( 
						((long)((p->pos.x-1)*iXPitch) + (iXPitch*0.4) + LeftSide + ICSide ) + ICTextLeftSide, 
						((long)((p->pos.y-1)*iYPitch) + (iYPitch*0.1) + TopSide + ICSide ) + ICTextTopSide, 
						csSite );
					// Note : 我們把字串顯示在格子接近中間位置往下 和 往右 兩個距離.
					// 中間位置為 x 的0.8距離. y的 0.1距離
				}
			}
			// Display Temp and Code.
		}
	}

	pDC->BitBlt(0, 0, rect.Width(), rect.Height(), &dcMemory, 0, 0, SRCCOPY);
	ReleaseDC(&dcMemory);
}
void CViewTrayMap::SaveAsBmp(CString filename)   
{
	CRect clientRC;   
	this->GetClientRect(clientRC);   
	int iWidth = clientRC.Width();   
	int iHeight = clientRC.Height();   
	int iPixel = 32;   

	BITMAPINFO *lpbmih = new BITMAPINFO;   
	lpbmih->bmiHeader.biSize = sizeof(BITMAPINFOHEADER);   
	lpbmih->bmiHeader.biWidth = iWidth;   
	lpbmih->bmiHeader.biHeight = iHeight;   
	lpbmih->bmiHeader.biPlanes = 1;   
	lpbmih->bmiHeader.biBitCount = iPixel;   
	lpbmih->bmiHeader.biCompression = BI_RGB;   
	lpbmih->bmiHeader.biSizeImage = 0;   
	lpbmih->bmiHeader.biXPelsPerMeter = 0;   
	lpbmih->bmiHeader.biYPelsPerMeter = 0;   
	lpbmih->bmiHeader.biClrUsed = 0;   
	lpbmih->bmiHeader.biClrImportant = 0;   

	HDC hdc,hdcMem;   
	HBITMAP hBitMap = NULL;   
	CBitmap *pBitMap = NULL;   
	CDC *pMemDC = NULL;   
	BYTE *pBits;   
	
	hdc = CreateIC(TEXT("DISPLAY"),NULL,NULL,NULL);   
	hdcMem = CreateCompatibleDC(hdc);   
	hBitMap = CreateDIBSection(hdcMem,lpbmih,DIB_PAL_COLORS,(void **)&pBits,NULL,0);   
	pBitMap = new CBitmap;   
	pBitMap->Attach(hBitMap);   
	pMemDC = new CDC;   
	pMemDC->Attach(hdcMem);   
	pMemDC->SelectObject(pBitMap);   
	//   
	CRect rc(0,0,iWidth,iHeight);   
	pMemDC->SetBkMode(TRANSPARENT);   

	OnDraw(pMemDC);   

	BITMAPFILEHEADER bmfh;   
	ZeroMemory(&bmfh,sizeof(BITMAPFILEHEADER));   
	*((char *)&bmfh.bfType) = 'B';   
	*(((char *)&bmfh.bfType) + 1) = 'M';   
	bmfh.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);   
	bmfh.bfSize = bmfh.bfOffBits + (iWidth * iHeight) * iPixel / 8;   
	
	TCHAR szBMPFileName[128];   
	int iBMPBytes = iWidth * iHeight * iPixel / 8;   
	strcpy(szBMPFileName,filename);   
	CFile file;   
	if(file.Open(szBMPFileName,CFile::modeWrite | CFile::modeCreate))   
	{   
		file.Write(&bmfh,sizeof(BITMAPFILEHEADER));   
		file.Write(&(lpbmih->bmiHeader),sizeof(BITMAPINFOHEADER));   
		file.Write(pBits,iBMPBytes);   
		file.Close();   
	}   
	
	pMemDC->DeleteDC();   
	delete pMemDC; pMemDC = NULL;   
	delete pBitMap; pBitMap = NULL;   
	delete lpbmih; lpbmih = NULL;   
}

void CViewTrayMap::ResetPage()
{
	// 重設頁數 (因為刪除了.)
	m_iPage = 0;						// 當下頁數, 第一頁是 0. 第二頁 1,2,3,.....
	m_iPageCount = 0;					// 目前已經有幾頁
}

/*
void CViewTrayMap::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	
	// Do not call CView::OnPaint() for painting messages
}
*/
void CViewTrayMap::OnLButtonDown(UINT nFlags, CPoint point) 
{
	CDocument* pDoc = GetDocument();

	CString cs;
	cs.Format("x = %d, y = %d", point.x, point.y );

	CView::OnLButtonDown(nFlags, point);
}
/////////////////////////////////////////////////////////////////////////////
// CViewTrayMap diagnostics

#ifdef _DEBUG
void CViewTrayMap::AssertValid() const
{
	CView::AssertValid();
}

void CViewTrayMap::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CViewTrayMap message handlers
