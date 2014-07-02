// ErrView.cpp : implementation file
//

#include "stdafx.h"
#include "deer.h"
#include "ErrView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CErrView

IMPLEMENT_DYNCREATE(CErrView, CView)

CErrView::CErrView(tagErrorMsg *p)
{
	msg = p;
}

CErrView::~CErrView()
{
}


BEGIN_MESSAGE_MAP(CErrView, CView)
	//{{AFX_MSG_MAP(CErrView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CErrView drawing

void CErrView::OnDraw(CDC* pDC)
{
	CRect rect;
	GetClientRect(rect);
//	ClientToScreen(rect);

	CDC	content;
	content.CreateCompatibleDC(pDC);

	CPoint ptOri(0, 0);
	BITMAP bmp;

	if(msg->p.y != 0 && msg->p.x != 0)
	{
		if( msg->Code == enCodeCycleFinish )
		{
			content.SelectObject(&m.Bitmap.CycleEnd);
			m.Bitmap.CycleEnd.GetBitmap(&bmp);
			// Note : This is for Cycle Finish.
		}
		else
		{	
			{
				// 如果沒有選 PreHeater 的模組就維持正常
				content.SelectObject(&m.Bitmap.Layout);
				m.Bitmap.Layout.GetBitmap(&bmp);
				// Note : This for error 
			}
		}

//		m.Bitmap.Layout.GetBitmap(&bmp);
		pDC->StretchBlt(ptOri.x, ptOri.y, rect.Width(), rect.Height(), &content,
						0, 0, bmp.bmWidth, bmp.bmHeight, SRCCOPY);

		content.SelectObject(&m.Bitmap.Black);
		pDC->BitBlt(msg->p.x - 32 + ptOri.x, msg->p.y -32 + ptOri.y, 
			64, 64, &content, 0, 0, MERGEPAINT);

		pDC->BitBlt(msg->p.x - 32 + ptOri.x, msg->p.y -32 + ptOri.y, 
			64, 64, &content, 0, 0, DSTINVERT);

		content.SelectObject(&m.Bitmap.Err);
		pDC->BitBlt(msg->p.x - 32 + ptOri.x, msg->p.y -32 + ptOri.y, 
			64, 64, &content, 0, 0, SRCERASE);
	}
	else if(msg->p.y == 0 && msg->p.x == 0)
	{
		if( msg->Code == enCodeCycleFinish )
		{
			content.SelectObject(&m.Bitmap.CycleEnd);
			m.Bitmap.CycleEnd.GetBitmap(&bmp);
			// Note : This is for Cycle Finish.
		}
		else
		{
			{
				// 如果沒有選 PreHeater 的模組就維持正常
				content.SelectObject(&m.Bitmap.Layout);
				m.Bitmap.Layout.GetBitmap(&bmp);
			}			
		}

		long x, y;

		x = 60;
		y = 480;
		
		pDC->StretchBlt(ptOri.x, ptOri.y, rect.Width(), rect.Height(), &content,
						0, 0, bmp.bmWidth, bmp.bmHeight, SRCCOPY);

	}
	else
	{
	
	
	}

//	CDocument* pDoc = GetDocument();
	
}

/////////////////////////////////////////////////////////////////////////////
// CErrView diagnostics

#ifdef _DEBUG
void CErrView::AssertValid() const
{
	CView::AssertValid();
}

void CErrView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CErrView message handlers
