// DlgGrabShow.cpp : implementation file
//

#include "stdafx.h"
#include "Deer.h"
#include "DlgGrabShow.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgGrabShow dialog


CDlgGrabShow::CDlgGrabShow(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgGrabShow::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgGrabShow)
	m_dScore = 0.0;
	//}}AFX_DATA_INIT


	m_pImage = m.CCD.GetGrabImage();
}


void CDlgGrabShow::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgGrabShow)
	DDX_Control(pDX, IDC_GRAB, m_wndGrab);
	DDX_Control(pDX, IDC_PATTERN, m_wndPattern);
	DDX_Control(pDX, IDC_RESULT, m_wndResult);
	DDX_Control(pDX, IDOK, m_btnOK);
	DDX_Control(pDX, IDCANCEL, m_btnCancel);
	DDX_Control(pDX, IDC_SCORE, m_edtScore);
	DDX_Control(pDX, IDC_MATCH, m_btnMatch);
	DDX_Control(pDX, IDC_SAVE, m_btnSave);
	DDX_Control(pDX, IDC_MODIFY, m_btnModify);
	DDX_Text(pDX, IDC_SCORE, m_dScore);
	DDV_MinMaxDouble(pDX, m_dScore, 0., 1.);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgGrabShow, CDialog)
	//{{AFX_MSG_MAP(CDlgGrabShow)
	ON_BN_CLICKED(IDC_MATCH, OnMatch)
	ON_BN_CLICKED(IDC_MODIFY, OnModify)
	ON_BN_CLICKED(IDC_SAVE, OnSave)
	ON_BN_CLICKED(IDC_LOAD_FILE, OnLoadFile)
	ON_WM_CLOSE()
	ON_WM_DESTROY()
	ON_WM_TIMER()
	ON_WM_PAINT()
	ON_WM_MOUSEMOVE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgGrabShow message handlers

void CDlgGrabShow::OnOK() 
{
	
	CDialog::OnOK();
}

void CDlgGrabShow::OnCancel() 
{
	
	CDialog::OnCancel();
}

void CDlgGrabShow::OnMatch() 
{
	if(!UpdateData())
		return;

	if(m_pImage == NULL)
		return;

	m.CCD.m_Match.MinScore = m_dScore;
	m.CCD.m_Match.rect.left = m.CCD.GetPatternROI().GetOrgX();
	m.CCD.m_Match.rect.top = m.CCD.GetPatternROI().GetOrgY();
	m.CCD.m_Match.rect.right = m.CCD.GetPatternROI().GetWidth()
		+ m.CCD.m_Match.rect.left;
	m.CCD.m_Match.rect.bottom = m.CCD.GetPatternROI().GetHeight()
		+ m.CCD.m_Match.rect.top;


	m.CCD.GetPatternROI().Detach();
	m.CCD.GetPatternROI().Attach(m.CCD.GetPatternImage());
	m.CCD.GetPatternROI().SetPlacement(m.CCD.m_Match.rect.left, 
		m.CCD.m_Match.rect.top, m.CCD.m_Match.rect.Width(), 
		m.CCD.m_Match.rect.Height());
	m.CCD.SetMatchPattern(m.CCD.GetPatternROI());

	m.CCD.MatchCheck(m_pImage);

  m_wndResult.SetWindowText(m.CCD.m_Match.MatchResult);

	if(m.CCD.GetMatchResult())
		m_wndResult.SetNewBkColor(ST_GREEN);	
	else
		m_wndResult.SetNewBkColor(ST_RED);

	Invalidate();
}

void CDlgGrabShow::OnModify() 
{
	m_bModify = !m_bModify;	
	CheckModify();
}

void CDlgGrabShow::OnSave() 
{
	if(!UpdateData())
		return;

	m.CCD.m_Match.MinScore = m_dScore;
	m.CCD.m_Match.rect.left = m.CCD.GetPatternROI().GetOrgX();
	m.CCD.m_Match.rect.top = m.CCD.GetPatternROI().GetOrgY();
	m.CCD.m_Match.rect.right = m.CCD.GetPatternROI().GetWidth()
		+ m.CCD.m_Match.rect.left;
	m.CCD.m_Match.rect.bottom = m.CCD.GetPatternROI().GetHeight()
		+ m.CCD.m_Match.rect.top;

	m.CCD.Save(m.CCD.GetPatternImage(), m.TraySpec.VisionPatternName, m.CCD.m_Match.File);
	f.LoadVisionProfile();

	m_bModify = !m_bModify;
	CheckModify();
	Invalidate();
}

void CDlgGrabShow::OnLoadFile() 
{
	CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_NOCHANGEDIR,
		"*.bmp |*.bmp||");
	if(dlg.DoModal() != IDOK)
		return;

	CString csFile = dlg.GetPathName();
	m_ImageC24.Load(csFile);
	m_pImage = &m_ImageC24;

	Invalidate();
}

void CDlgGrabShow::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	
	CDialog::OnClose();
}

void CDlgGrabShow::OnDestroy() 
{
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here
	
}
void CDlgGrabShow::CheckModifyLevel()
{
	// if level it not height then setup user.
	// It can not use modify function
	if( m.Info.user == enLevelSuperUser || 
		m.Info.user == enLevelSetup ||
		m.Info.user == enLevelEngineer )
	{
		m_btnModify.EnableWindow( true );
	}
	else
		m_btnModify.EnableWindow( false );

	Invalidate();
}
void CDlgGrabShow::CheckModify()
{
	m_edtScore.EnableWindow(m_bModify);
	m_btnSave.EnableWindow(m_bModify);	
	m_btnModify.EnableWindow(!m_bModify);

	Invalidate();
}

BOOL CDlgGrabShow::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// init button 
	m_btnOK.SetIcon(IDI_OK);;
	m_btnOK.SetAlign(CButtonST::ST_ALIGN_VERT);;
	m_btnOK.SetFlat(FALSE);
	
	m_btnCancel.SetIcon(IDI_CANCEL);
	m_btnCancel.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnCancel.SetFlat(FALSE);

	m_btnModify.SetIcon(IDI_MODIFY);
	m_btnModify.SetAlign(CButtonST::ST_ALIGN_VERT);

	m_btnSave.SetIcon(IDI_SAVE);
	m_btnSave.SetAlign(CButtonST::ST_ALIGN_VERT);

	// 取得目前視窗的 Rect
	GetWindowRect(rectWnd);
	m_wndPattern.GetWindowRect(rectShow);

	// 設定顯示結果控制項
	m_wndResult.SetText("--", 10, "Arial", DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	m_wndResult.SetNewBkColor(ST_GREEN);

	// 設定繪圖的預設值
	sourcePen.CreatePen(PS_SOLID, 1, RGB(255, 255, 0));
	RedPen.CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	disablePen.CreatePen(PS_SOLID, 1, RGB(0, 0, 0));

	// 設定 ROI 範圍
	CString cs;
	cs.Format("%5.2f", m.CCD.m_Match.MinScore);
	m_edtScore.SetWindowText(cs);

	// Default set it to false.
	m_bModify = false;
	CheckModify();
	CheckModifyLevel();

	f.ChangeLanguage(GetSafeHwnd());
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgGrabShow::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	
	CDialog::OnTimer(nIDEvent);
}

void CDlgGrabShow::OnPaint() 
{
	CPaintDC dc(this); // device context for painting

	if(m_pImage != NULL)
	{
		CDC *pp = m_wndGrab.GetDC();
		m_pImage->Draw(pp->GetSafeHdc(), (float)0.6, (float)0.6);
		pp->SelectObject(&RedPen);
		m.CCD.m_Match.SourceROI.DrawFrame(pp->GetSafeHdc(), E_FRAME_ON, FALSE,
			(float)0.6, (float)0.6);

		if(m.CCD.MatchObj.GetNumPositions() > 0)
		{
			pp->SelectObject(&sourcePen);
			m.CCD.MatchObj.DrawPosition(pp->GetSafeHdc(), 0, FALSE, 
				(float)0.6, (float)0.6);
		}

		m_wndGrab.ReleaseDC(pp);
	}
	// 繪圖 CCD Pattern 

	if(m.CCD.GetPatternImage() != NULL)
	{
		CDC *p = m_wndPattern.GetDC();
		m.CCD.GetPatternImage()->Draw(p->GetSafeHdc());
		
		if(m_bModify)
			p->SelectObject(&sourcePen);
		else
			p->SelectObject(&disablePen);
		
		m.CCD.GetPatternROI().DrawFrame(p->GetSafeHdc(), E_FRAME_ON, FALSE);
		m_wndPattern.ReleaseDC(p);
	}
	// 繪圖 Pattern 

}

void CDlgGrabShow::OnMouseMove(UINT nFlags, CPoint point) 
{
	if(!m_bModify)
		return;
	
	if((nFlags & MK_LBUTTON) && (m_eHandle != E_HANDLE_NONE))
	{
		m.CCD.GetPatternROI().Drag(m_eHandle, point.x, point.y);
		Invalidate(FALSE);
	}
	else
		m_eHandle = m.CCD.GetPatternROI().HitTest(point.x, point.y);
	
	switch(m_eHandle)
	{
	case E_HANDLE_INSIDE:
		SetCursor(LoadCursor(NULL, IDC_SIZEALL));
		break;
		
	case E_HANDLE_NORTH:
	case E_HANDLE_SOUTH:
		SetCursor(LoadCursor(NULL, IDC_SIZENS));
		break;
		
	case E_HANDLE_EAST:
	case E_HANDLE_WEST:
		SetCursor(LoadCursor(NULL, IDC_SIZEWE));
		break;
		
	case E_HANDLE_NORTH_WEST:
	case E_HANDLE_SOUTH_EAST:
		SetCursor(LoadCursor(NULL, IDC_SIZENWSE));
		break;
		
	case E_HANDLE_NORTH_EAST:
	case E_HANDLE_SOUTH_WEST:
		SetCursor(LoadCursor(NULL, IDC_SIZENESW));
		break;
	}

	CDialog::OnMouseMove(nFlags, point);
}

//////
void CDlgGrabShow::UpdateGrabImage(EImageC24 *pImage, CString result)
{
	m_pImage = pImage;
	m_wndGrab.GetWindowRect(m_Rect);
	m_Rect.SetRect(m_Rect.left, m_Rect.right, pImage->GetWidth(), pImage->GetHeight());
	::InvalidateRect(m_hWnd, &m_Rect, FALSE);

	m_wndResult.SetNewText(result);
	if(m.CCD.GetMatchResult())
		m_wndResult.SetNewBkColor(ST_GREEN);
	else
		m_wndResult.SetNewBkColor(ST_RED);
}

//////

BOOL CDlgGrabShow::PreTranslateMessage(MSG* pMsg) 
{
	// z avoid ESC / Enter to crash the software
	if(pMsg->message  == WM_KEYDOWN)   
	{
		int nVirtKey = (int)pMsg->wParam;    
		if( nVirtKey == VK_ESCAPE )
			return   TRUE;   
//		if( nVirtKey == VK_RETURN )   
//			return   TRUE;   
	}
	return CDialog::PreTranslateMessage(pMsg);
}
