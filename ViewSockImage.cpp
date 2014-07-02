// ViewSockImage.cpp : implementation file
//

#include "stdafx.h"
#include "deer.h"
#include "ViewSockImage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CViewSockImage

IMPLEMENT_DYNCREATE(CViewSockImage, CView)

CViewSockImage::CViewSockImage()
{
	m_pBitmap = NULL;

	m_h = 0;
	m_w = 0;
}

CViewSockImage::~CViewSockImage()
{
}


BEGIN_MESSAGE_MAP(CViewSockImage, CView)
	//{{AFX_MSG_MAP(CViewSockImage)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CViewSockImage drawing

void CViewSockImage::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// 這邊畫 圖片
	/////////////////////////////////////////////////////////////////////
	CRect RectImage;
	GetClientRect( &RectImage );
	if(m_pBitmap != NULL)  
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

	m_pBitmap = NULL;
}
void CViewSockImage::SetBmpAddress(HBITMAP *pBitmap)
{
	m_pBitmap = pBitmap;

	// 有圖片後, 先重畫
	Invalidate(FALSE);
}
/////////////////////////////////////////////////////////////////////////////
// CViewSockImage diagnostics

#ifdef _DEBUG
void CViewSockImage::AssertValid() const
{
	CView::AssertValid();
}

void CViewSockImage::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CViewSockImage message handlers
