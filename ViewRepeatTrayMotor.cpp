// ViewRepeatTrayMotor.cpp : implementation file
//

#include "stdafx.h"
#include "deer.h"
#include "ViewRepeatTrayMotor.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CViewRepeatTrayMotor

IMPLEMENT_DYNCREATE(CViewRepeatTrayMotor, CView)

CViewRepeatTrayMotor::CViewRepeatTrayMotor()
{
	m_iChip = false;
	m_iType = -1;

	m_Brush[0].CreateSolidBrush( RGB(0, 255, 0) );			// Green / Moving.	
	m_Brush[1].CreateSolidBrush( RGB( 255, 0, 0) );			// Red / Booking.	
	m_Brush[2].CreateSolidBrush( RGB( 255, 255, 0) );		// Yellow / OK.	
	m_Brush[3].CreateSolidBrush( RGB( 255, 255, 255) );		// Spec test
	m_Brush[4].CreateSolidBrush( RGB(0, 0, 128) );			// PreHeater
	m_Brush[5].CreateSolidBrush( RGB(128, 128, 128) );		// Dark Blue PreHeater Soak Done
	m_Brush[6].CreateSolidBrush( RGB(192, 0, 0) );			// Gray PreHeater Booking
	m_Brush[7].CreateSolidBrush( RGB(255, 255, 128) );		// Brow PreHeater Moving	// Light Yellow PreHeater OK
	m_Brush[8].CreateSolidBrush( RGB(64, 0, 64) );			// Disable PreHeater Wait Soak	
	m_Brush[9].CreateSolidBrush( RGB(0, 255, 0) );
	m_Brush[10].CreateSolidBrush( RGB(119, 255, 119) );
}

CViewRepeatTrayMotor::~CViewRepeatTrayMotor()
{
}


BEGIN_MESSAGE_MAP(CViewRepeatTrayMotor, CView)
	//{{AFX_MSG_MAP(CViewRepeatTrayMotor)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CViewRepeatTrayMotor drawing

void CViewRepeatTrayMotor::SetType(int type)
{
	m_iType = type;
}
void CViewRepeatTrayMotor::OnDraw(CDC* pDC)
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


	// Draw Tray
	int iColumn = -1;
	int	iRow = -1;
	int iSize = -1;
	if( m_iChip == 1 )
	{
		// Chip Tray
		// 由 Sub Tray 來計算有多少 IC
		iColumn = m.TraySpec.m_SubTrayColumn * m.TraySpec.m_SubChipTrayColumn;
		iRow = m.TraySpec.m_SubTrayRow * m.TraySpec.m_SubChipTrayRow;
		iSize = iColumn * iRow;
	}
	else
	{
		iColumn = m.TraySpec.Column;
		iRow = m.TraySpec.Row;	
		iSize = m.TraySpec.Column * m.TraySpec.Row;	
		// Tray
	}

	////////////////////////////////////////////////////////////////
	// CView Tray 的設定檔
	long	LeftSide =	m.Setting.m_dTraySpecLeftSide;		// 左邊離 CStatic 的間距.
	long	TopSide =	m.Setting.m_dTraySpecTopSide;		// 上方離 CStatic 的間距.
	int		ICSide =	m.Setting.m_dTraySpecICSide;		// IC 在格子裡面. 顯示顏色與邊框的距離.
	
	////////////////////////////////////////////////////////////////
	if(iColumn <=0 || iRow <=0) 
		return;

	long iXPitch = rect.Width()  / iColumn;
	long iYPitch = rect.Height() / iRow;
	// Tray 

	CRect rectH;
	GetWindowRect(rectH);

	// Chip Tray
	CRect	rectHChipTray;
	GetWindowRect(rectHChipTray);


	/////////////////////////////////////////////////
	// Tray 1 Status
	if( m_iType == 0 )
	{
		if( m_iChip == 1 )
		{
			// 找到最大的長寬
			long right =	(long)(iColumn)*iXPitch;
			long bottom =	(long)(iRow)*iYPitch;	

			int iSubColumn  = -1;
			int iSubRow		= -1;
			iSubColumn = m.TraySpec.m_SubTrayColumn;
			iSubRow	   = m.TraySpec.m_SubTrayRow;
			CPen penChip;
			penChip.CreatePen(PS_SOLID, 1, RGB( 255, 153, 0   ) );	
			// 設定 Chip Tray 外框的顏色
			CPen* pOldPen = dcMemory.SelectObject(&penChip);
			double iXPitch = /*rectHChipTray.Width()*/right		/	iSubColumn;
			double iYPitch = /*rectHChipTray.Height()*/bottom	/	iSubRow;

			for(int i=0; i<iSubColumn; i++)
			{
				for(int j=0; j<iSubRow; j++)
				{
					rectHChipTray.left		= (long)((i)*iXPitch);
					rectHChipTray.right		= (long)(i+1)*iXPitch;
					rectHChipTray.top		= (long)(j)*iYPitch;
					rectHChipTray.bottom	= (long)(j+1)*iYPitch;
					dcMemory.Rectangle(&rectHChipTray);
					// 畫 Chip Tray Map 的格子
				}
			}
			dcMemory.SelectObject(pOldPen);
			// 畫完. 復原 CPen 設定顏色(黑色)
		}

		for(int i=0; i<iColumn; i++)
		{
			for(int j=0; j<iRow; j++)
			{
				rectH.left =	(long)((i)*(iXPitch)) + LeftSide;
				rectH.right =	(long)(i+1)*iXPitch;
				rectH.top =		(long)((j)*(iYPitch)) + TopSide;
				rectH.bottom =	(long)(j+1)*iYPitch;				
				dcMemory.Rectangle(&rectH);
				// 畫 Motor Map 的格子
			}
		}
		
		// Draw Output Device
		for(i=0; i<iSize;i++)
		{	
			CPoint p;
			
			int m_iColL = i % iColumn;		
			int m_iRowL = i / iColumn;		
	
			p.x = m_iColL + 1;
			p.y = m_iRowL + 1;
		
			// Col = 8 Row = 15
			// x 是 取 Col 餘數
			// y 是 商	
						
			rectH.left =	(int)((p.x-1)*iXPitch) + LeftSide	+ ICSide;
			rectH.right =	(int)((p.x)*iXPitch)	- ICSide;
			rectH.top =		(int)((p.y-1)*iYPitch) + TopSide		+ ICSide;
			rectH.bottom =	(int)((p.y)*iYPitch)	- ICSide;
			// Draw 
			
			if(  theApp.m_Tray1.TrayiNoGetStatus(i) == enMoving )
				dcMemory.FillRect(&rectH, &m_Brush[0]);		
			else if ( theApp.m_Tray1.TrayiNoGetStatus(i) == enBooking )
				dcMemory.FillRect(&rectH, &m_Brush[1]);
			else if ( theApp.m_Tray1.TrayiNoGetStatus(i) == enOK )
			{
				if( theApp.m_Tray1.TrayiNoGetStatusAuto(i) == enOK )
					dcMemory.FillRect(&rectH, &m_Brush[10]);	// 這是 AutoSkip 的位置, 表示沒有 IC
				else
					dcMemory.FillRect(&rectH, &m_Brush[9]);		// 
			}
			else if ( theApp.m_Tray1.TrayiNoGetStatus(i) == enEmpty )
				dcMemory.FillRect(&rectH, &m_Brush[3]);		
			else
				;
			// Color.!
			
			// Note : 請注意, 在 pos 裡面儲存的是座標點 (x,y). 
			// 左上角是第一顆, 右邊是第二顆
			// 第一顆是 (1,1). 第二顆是 (2.1) 第三顆是 (3.1) 以此類推.
		}
	}


	/////////////////////////////////////////////////
	// Tray 2 Status
	if( m_iType == 1 )
	{
		if( m_iChip == 1 )
		{
			// 找到最大的長寬
			long right =	(long)(iColumn)*iXPitch;
			long bottom =	(long)(iRow)*iYPitch;	

			int iSubColumn  = -1;
			int iSubRow		= -1;
			iSubColumn = m.TraySpec.m_SubTrayColumn;
			iSubRow	   = m.TraySpec.m_SubTrayRow;
			CPen penChip;
			penChip.CreatePen(PS_SOLID, 1, RGB( 255, 153, 0   ) );	
			// 設定 Chip Tray 外框的顏色
			CPen* pOldPen = dcMemory.SelectObject(&penChip);
			double iXPitch = /*rectHChipTray.Width()*/right		/	iSubColumn;
			double iYPitch = /*rectHChipTray.Height()*/bottom	/	iSubRow;

			for(int i=0; i<iSubColumn; i++)
			{
				for(int j=0; j<iSubRow; j++)
				{
					rectHChipTray.left		= (long)((i)*iXPitch);
					rectHChipTray.right		= (long)(i+1)*iXPitch;
					rectHChipTray.top		= (long)(j)*iYPitch;
					rectHChipTray.bottom	= (long)(j+1)*iYPitch;
					dcMemory.Rectangle(&rectHChipTray);
					// 畫 Chip Tray Map 的格子
				}
			}
			dcMemory.SelectObject(pOldPen);
			// 畫完. 復原 CPen 設定顏色(黑色)
		}

		for(int i=0; i<iColumn; i++)
		{
			for(int j=0; j<iRow; j++)
			{
				rectH.left =	(long)((i)*(iXPitch)) + LeftSide;
				rectH.right =	(long)(i+1)*iXPitch;
				rectH.top =		(long)((j)*(iYPitch)) + TopSide;
				rectH.bottom =	(long)(j+1)*iYPitch;				
				dcMemory.Rectangle(&rectH);
				// 畫 Motor Map 的格子
			}
		}
		
		// Draw Output Device
		for(i=0; i<iSize;i++)
		{	
			CPoint p;
			
			int m_iColL = i % iColumn;		
			int m_iRowL = i / iColumn;		
	
			p.x = m_iColL + 1;
			p.y = m_iRowL + 1;
		
			// Col = 8 Row = 15
			// x 是 取 Col 餘數
			// y 是 商	
						
			rectH.left =	(int)((p.x-1)*iXPitch) + LeftSide	+ ICSide;
			rectH.right =	(int)((p.x)*iXPitch)	- ICSide;
			rectH.top =		(int)((p.y-1)*iYPitch) + TopSide		+ ICSide;
			rectH.bottom =	(int)((p.y)*iYPitch)	- ICSide;
			// Draw 
			
			if(  theApp.m_Tray2.TrayiNoGetStatus(i) == enMoving )
				dcMemory.FillRect(&rectH, &m_Brush[0]);		
			else if ( theApp.m_Tray2.TrayiNoGetStatus(i) == enBooking )
				dcMemory.FillRect(&rectH, &m_Brush[1]);
			else if ( theApp.m_Tray2.TrayiNoGetStatus(i) == enOK )
			{
				if( theApp.m_Tray2.TrayiNoGetStatusAuto(i) == enOK )
					dcMemory.FillRect(&rectH, &m_Brush[10]);	// 這是 AutoSkip 的位置, 表示沒有 IC
				else
					dcMemory.FillRect(&rectH, &m_Brush[9]);		// 
			}
			else if ( theApp.m_Tray2.TrayiNoGetStatus(i) == enEmpty )
				dcMemory.FillRect(&rectH, &m_Brush[3]);		
			else
				;
			// Color.!
			
			// Note : 請注意, 在 pos 裡面儲存的是座標點 (x,y). 
			// 左上角是第一顆, 右邊是第二顆
			// 第一顆是 (1,1). 第二顆是 (2.1) 第三顆是 (3.1) 以此類推.
		}
	}


	pDC->BitBlt(0, 0, rect.Width(), rect.Height(), &dcMemory, 0, 0, SRCCOPY);
	ReleaseDC(&dcMemory);
}

/////////////////////////////////////////////////////////////////////////////
// CViewRepeatTrayMotor diagnostics

#ifdef _DEBUG
void CViewRepeatTrayMotor::AssertValid() const
{
	CView::AssertValid();
}

void CViewRepeatTrayMotor::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CViewRepeatTrayMotor message handlers
