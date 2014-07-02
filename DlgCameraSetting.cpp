// DlgCameraSetting.cpp : implementation file
//

#include "stdafx.h"
#include "deer.h"
#include "DlgCameraSetting.h"

//
#include "DlgSocketVisionCam.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgCameraSetting dialog


CDlgCameraSetting::CDlgCameraSetting(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgCameraSetting::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgCameraSetting)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgCameraSetting::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgCameraSetting)
	DDX_Control(pDX, IDC_CCD_LIST,			m_btnCameraList);
	DDX_Control(pDX, IDCANCEL,				m_btnCancel);
	DDX_Control(pDX, IDOK,					m_btnOK);
	DDX_Control(pDX, IDC_ROI_H,				m_wndRoiH);
	DDX_Control(pDX, IDC_ROI_W,				m_wndRoiW);
	DDX_Control(pDX, IDC_ROI_X,				m_wndRoiX);
	DDX_Control(pDX, IDC_ROI_Y,				m_wndRoiY);
	DDX_Text(pDX, IDC_CAMERA_USE,			m_iCameraID);
	DDX_Text(pDX, IDC_ROI_X,				m_RoiX);
	DDX_Text(pDX, IDC_ROI_Y,				m_RoiY);
	DDX_Text(pDX, IDC_ROI_H,				m_RoiH);
	DDX_Text(pDX, IDC_ROI_W,				m_RoiW);
	DDX_Control(pDX, IDC_ROI_H_SOCKET,		m_wndRoiHSocket);
	DDX_Control(pDX, IDC_ROI_W_SOCKET,		m_wndRoiWSocket);
	DDX_Control(pDX, IDC_ROI_X_SOCKET,		m_wndRoiXSocket);
	DDX_Control(pDX, IDC_ROI_Y_SOCKET,		m_wndRoiYSocket);
	DDX_Text(pDX, IDC_CAMERA_USE_SOCKET,	m_iCameraIDSocket);
	DDX_Text(pDX, IDC_ROI_X_SOCKET,			m_RoiXSocket);
	DDX_Text(pDX, IDC_ROI_Y_SOCKET,			m_RoiYSocket);
	DDX_Text(pDX, IDC_ROI_H_SOCKET,			m_RoiHSocket);
	DDX_Text(pDX, IDC_ROI_W_SOCKET,			m_RoiWSocket);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgCameraSetting, CDialog)
	//{{AFX_MSG_MAP(CDlgCameraSetting)
	ON_BN_CLICKED(IDC_CCD_LIST,	OnCcdList)
	ON_BN_CLICKED(IDC_LOCK, OnLock)
	ON_BN_CLICKED(IDC_CCD_DEVICE, OnCcdDevice)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgCameraSetting message handlers

void CDlgCameraSetting::OnCcdList() 
{
	CDlgSocketVisionCam dlg;
	dlg.DoModal();
}

void CDlgCameraSetting::OnOK() 
{
	//
	SaveData();

	m.Info.bSubDlgOpen = false;
	f.UpdateButtonState();
	
	CDialog::OnOK();
}

void CDlgCameraSetting::OnCancel() 
{
	m.Info.bSubDlgOpen = false;
	f.UpdateButtonState();
	
	CDialog::OnCancel();
}

BOOL CDlgCameraSetting::PreTranslateMessage(MSG* pMsg) 
{
	// z avoid ESC / Enter to crash the software
	if(pMsg->message  == WM_KEYDOWN)   
	{
		int nVirtKey = (int)pMsg->wParam;    
		if( nVirtKey == VK_ESCAPE )
			return   TRUE;   
		if( nVirtKey == VK_RETURN )   
			return   TRUE;   
	}	
	return CDialog::PreTranslateMessage(pMsg);
}

BOOL CDlgCameraSetting::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m.Info.bSubDlgOpen = true;
	f.UpdateButtonState();

	// init button 
	m_btnOK.SetIcon(IDI_SAVE);
	m_btnOK.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnOK.SetFlat(FALSE);
	
	m_btnCancel.SetIcon(IDI_CANCEL);
	m_btnCancel.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnCancel.SetFlat(FALSE);

	m_btnCameraList.SetIcon(IDI_CCD_LIST);
	m_btnCameraList.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnCameraList.SetFlat(FALSE);

	//
	InitValue();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgCameraSetting::InitValue()
{
	// CCD Pin1 
	m_iCameraID			= m.m_CCDPin1Control.iCCDUse;

	m_RoiX				= m.m_CCDPin1Control.RoiX;
	m_RoiY				= m.m_CCDPin1Control.RoiY;
	m_RoiW				= m.m_CCDPin1Control.RoiW;
	m_RoiH				= m.m_CCDPin1Control.RoiH;

	// CCD Socket 
	m_iCameraIDSocket	= m.m_CCDSocketControl.iCCDUse;

	m_RoiXSocket		= m.m_CCDSocketControl.RoiX;
	m_RoiYSocket		= m.m_CCDSocketControl.RoiY;
	m_RoiWSocket		= m.m_CCDSocketControl.RoiW;
	m_RoiHSocket		= m.m_CCDSocketControl.RoiH;

	UpdateData( FALSE );
}
void CDlgCameraSetting::SaveData()
{
	UpdateData();

	// CCD Pin1
	m.m_CCDPin1Control.iCCDUse		= m_iCameraID;
	
	m.m_CCDPin1Control.RoiX			= m_RoiX;
	m.m_CCDPin1Control.RoiY			= m_RoiY;
	m.m_CCDPin1Control.RoiW			= m_RoiW;
	m.m_CCDPin1Control.RoiH			= m_RoiH;

	// CCD Socket 
	m.m_CCDSocketControl.iCCDUse	= m_iCameraIDSocket;

	m.m_CCDSocketControl.RoiX		= m_RoiXSocket;
	m.m_CCDSocketControl.RoiY		= m_RoiYSocket;
	m.m_CCDSocketControl.RoiW		= m_RoiWSocket;
	m.m_CCDSocketControl.RoiH		= m_RoiHSocket;

	f.SaveCCDPin1Control();
	f.SaveCCDSocketControl();
}
//
void CDlgCameraSetting::UnLock()
{
	BOOL bEnable = TRUE;
	m_wndRoiX.EnableWindow( bEnable );
	m_wndRoiY.EnableWindow( bEnable );
	m_wndRoiH.EnableWindow( bEnable );
	m_wndRoiW.EnableWindow( bEnable );

	m_wndRoiXSocket.EnableWindow( bEnable );
	m_wndRoiYSocket.EnableWindow( bEnable );
	m_wndRoiHSocket.EnableWindow( bEnable );
	m_wndRoiWSocket.EnableWindow( bEnable );
}

void CDlgCameraSetting::OnLock() 
{
	UnLock();
}

void CDlgCameraSetting::OnCcdDevice() 
{

}
