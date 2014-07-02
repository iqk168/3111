// ViewIC.cpp : implementation file
//

#include "stdafx.h"
#include "deer.h"
#include "ViewIC.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CViewIC

IMPLEMENT_DYNCREATE(CViewIC, CView)

CViewIC::CViewIC()
{
	csFile = _T("");

	m_pPic = NULL;
}

CViewIC::~CViewIC()
{
	if( m_pPic != NULL )
	{
		m_pPic->Release();
		m_pPic = NULL;
	}
}


BEGIN_MESSAGE_MAP(CViewIC, CView)
	//{{AFX_MSG_MAP(CViewIC)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CViewIC drawing
void CViewIC::SetFileName(CString file)
{
	csFile = file;
}
void CViewIC::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();

	if( csFile == "" )
		return;
	
	
	CRect rect;
	GetClientRect(rect);
	CDC	content;
	content.CreateCompatibleDC(pDC);	
	
	const LPOLESTR PICTURE_PATH = csFile.AllocSysString();
	CDC		dcMemory;
	CBitmap bm;
	dcMemory.CreateCompatibleDC(pDC);
	bm.CreateCompatibleBitmap(pDC, rect.Width(), rect.Height());
	dcMemory.SelectObject(&bm);
	if( m_pPic )
	{
		m_pPic->Release();
		m_pPic = NULL;
	}
	
	VERIFY( S_OK == ::OleLoadPicturePath( PICTURE_PATH, 0, 0, 0, IID_IPicture, (LPVOID*)&m_pPic) );
	
	OLE_XSIZE_HIMETRIC	cxhm = 0;
	OLE_YSIZE_HIMETRIC	cyhm = 0;
	CSize				sizeDevice;
	
	if(m_pPic != NULL)
	{
		VERIFY(S_OK==m_pPic->get_Width(&cxhm));
		VERIFY(S_OK==m_pPic->get_Height(&cyhm));
		sizeDevice.cx = cxhm;
		sizeDevice.cy = cyhm;
		pDC->HIMETRICtoDP(&sizeDevice);
	}
	
	m_pPic->Render(dcMemory, 0, 0, rect.Width(), rect.Height(),
		0, 0, cxhm, cyhm, 0);
	
	pDC->StretchBlt(0, 0, rect.Width(), rect.Height(), &dcMemory,
			0, (rect.Height() ), rect.Width(), -(rect.Height()), SRCCOPY);
}

/////////////////////////////////////////////////////////////////////////////
// CViewIC diagnostics

#ifdef _DEBUG
void CViewIC::AssertValid() const
{
	CView::AssertValid();
}

void CViewIC::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CViewIC message handlers
