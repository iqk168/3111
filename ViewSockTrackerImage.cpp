// ViewSockTrackerImage.cpp : implementation file
//

#include "stdafx.h"
#include "deer.h"
#include "ViewSockTrackerImage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CViewSockTrackerImage

IMPLEMENT_DYNCREATE(CViewSockTrackerImage, CView)

CViewSockTrackerImage::CViewSockTrackerImage()
{
	m_pBitmap = NULL;

	csInfomation = _T("");

	m_h = 0;
	m_w = 0;

	m_LoadRect.top = 0;
	m_LoadRect.left = 0;
	m_LoadRect.bottom = 50;
	m_LoadRect.right = 50;

	//
	m_AlignRectTracker.m_rect.SetRect(0,0,50,50);
	m_AlignRectTracker.m_nStyle= CRectTracker::resizeInside|CRectTracker::solidLine; 

	//
	m_bLoadRect = false;

	//
	m_bLockUI	= false;
}


CViewSockTrackerImage::~CViewSockTrackerImage()
{
}
void CViewSockTrackerImage::SetInfomation(CString csInfo)
{
	//
	m_bLockUI	= true;

	//
	csInfomation = csInfo;
	Invalidate(FALSE);
}
void CViewSockTrackerImage::SetBmpAddress(HBITMAP *pBitmap)
{
	m_bLockUI	 = false;

	m_pBitmap = pBitmap;

	// 有圖片後, 先重畫
	Invalidate(FALSE);
}
void CViewSockTrackerImage::SendPos()
{
	::SendMessage( GetParent()->GetParent()->GetSafeHwnd(), WM_RECT_POS, NULL, NULL );
}
void CViewSockTrackerImage::GetPatternInfo(int &top, int &left, int &bottom, int &right)
{
	CRect PatternRect;
	CRect ControlRect;
	GetClientRect( &ControlRect );
	m_AlignRectTracker.GetTrueRect( &PatternRect );

	//
	int w = ControlRect.right - ControlRect.left;
	int h = ControlRect.bottom - ControlRect.top;

	// 計算圖檔比控制項大多少
/*
	double w_rx = (double)m_w / (double)w;
	double w_ry = (double)m_h / (double)h;
*/
	int w_rx = m_w / w;
	int w_ry = m_h / h;

	//
	top		= PatternRect.top		* w_ry;
	bottom	= PatternRect.bottom	* w_ry;
	left	= PatternRect.left		* w_rx;
	right	= PatternRect.right		* w_rx;
}
void CViewSockTrackerImage::SetPatternInfomation(int top, int left, int bottom, int right)
{
	m_bLoadRect = true;
	m_LoadRect.top = top;
	m_LoadRect.left = left;
	m_LoadRect.bottom = bottom;
	m_LoadRect.right = right;
}
BEGIN_MESSAGE_MAP(CViewSockTrackerImage, CView)
	//{{AFX_MSG_MAP(CViewSockTrackerImage)
	ON_WM_SETCURSOR()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CViewSockTrackerImage drawing

void CViewSockTrackerImage::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// 這邊畫 圖片
	/////////////////////////////////////////////////////////////////////
	CRect RectImage;
	GetClientRect( &RectImage );
	if(m_pBitmap != NULL && csInfomation == "" )  
	{  
		CBitmap   bmp;  
		if(bmp.Attach(m_pBitmap))  
		{  
			CString csW = _T("");
			
			BITMAP   bmpInfo;  
			bmp.GetBitmap(&bmpInfo);  
			
			CDC   dcMemory;  
			dcMemory.CreateCompatibleDC(pDC);  
			dcMemory.SelectObject(&bmp);  
			pDC->SetStretchBltMode(HALFTONE);  
			pDC->StretchBlt(RectImage.left,RectImage.top,RectImage.Width(),RectImage.Height(),&dcMemory,0,0,
				bmpInfo.bmWidth,bmpInfo.bmHeight,SRCCOPY);  
			bmp.Detach();

			//
			m_w = bmpInfo.bmWidth;
			m_h = bmpInfo.bmHeight;
		}  
	}  
	//

	// 這邊畫 Pattern ROI 
	/////////////////////////////////////////////////////////////////////
	if(m_pBitmap != NULL && csInfomation == "" )  
	{
		CRect rect;	
		COLORREF color = RGB(255, 255, 0);
		m_AlignRectTracker.SetRectColor( color );
		m_AlignRectTracker.GetTrueRect(&rect); 
		if( m_bLoadRect )
		{
			m_bLoadRect = false;
			m_AlignRectTracker.m_rect = m_LoadRect;
			m_AlignRectTracker.Draw( pDC, m_LoadRect );
		}
		else
			m_AlignRectTracker.Draw( pDC );
	}
	/////////////////////////////////////////////////////////////////////

	if( csInfomation != "" )
	{
		CRect RectText;
		GetClientRect( &RectText );
		int x = 0;
		int y = 0;		

		x = 20;
		y = RectText.Height() / 2;

		pDC->TextOut( x, y, csInfomation );
		pDC->TextOut( x, y + 15 , "Image is lost" );
		csInfomation = "";
	}

	// 
	m_pBitmap = NULL;
}

/////////////////////////////////////////////////////////////////////////////
// CViewSockTrackerImage diagnostics

#ifdef _DEBUG
void CViewSockTrackerImage::AssertValid() const
{
	CView::AssertValid();
}

void CViewSockTrackerImage::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CViewSockTrackerImage message handlers

BOOL CViewSockTrackerImage::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
	if (pWnd == this && m_AlignRectTracker.SetCursor(this, nHitTest))          
		return TRUE; 	
	
	return CView::OnSetCursor(pWnd, nHitTest, message);
}

void CViewSockTrackerImage::OnLButtonDown(UINT nFlags, CPoint point) 
{
	if(m_bLockUI)
		return;

	m_AlignRectTracker.Track(this,point,TRUE); 

	Invalidate(FALSE);	
	
	CView::OnLButtonDown(nFlags, point);
}

void CViewSockTrackerImage::OnMouseMove(UINT nFlags, CPoint point) 
{
	SendPos();
	
	CView::OnMouseMove(nFlags, point);
}
