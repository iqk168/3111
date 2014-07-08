// DlgSocketVisionCam.cpp : implementation file
//

#include "stdafx.h"
#include "deer.h"
#include "DlgSocketVisionCam.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgSocketVisionCam dialog


CDlgSocketVisionCam::CDlgSocketVisionCam(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgSocketVisionCam::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgSocketVisionCam)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgSocketVisionCam::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgSocketVisionCam)
	DDX_Control(pDX, IDOK,			m_btnOK);
	DDX_Control(pDX, IDCANCEL,		m_btnCancel);
	DDX_Control(pDX, IDC_CAM_LIST,	m_listCam);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgSocketVisionCam, CDialog)
	//{{AFX_MSG_MAP(CDlgSocketVisionCam)

	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgSocketVisionCam message handlers

BOOL CDlgSocketVisionCam::PreTranslateMessage(MSG* pMsg) 
{
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

BOOL CDlgSocketVisionCam::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// init button 
	m_btnOK.SetIcon(IDI_OK);;
	m_btnOK.SetAlign(CButtonST::ST_ALIGN_VERT);;
	m_btnOK.SetFlat(FALSE);
	
	m_btnCancel.SetIcon(IDI_CANCEL);
	m_btnCancel.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnCancel.SetFlat(FALSE);

	//
	UpdataCamList();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
void CDlgSocketVisionCam::UpdataCamList() 
{
	//
	m_listCam.ResetContent();

	//
	CArray <CString, CString> m_DeviceList;
	m_DeviceList.RemoveAll();

	// Get Data from Class
	m.m_VisionMatch.GetCameraList( m_DeviceList );

	//
	int iDeviceSize = m_DeviceList.GetSize();
	for(int i=0;i<iDeviceSize;i++)
	{
		CString cs = _T("");
		cs.Format("%d: \t%s", i, m_DeviceList.GetAt(i) );
		m_listCam.AddString( cs );
	}
}
void CDlgSocketVisionCam::OnCancel() 
{
	
	CDialog::OnCancel();
}

void CDlgSocketVisionCam::OnOK() 
{
	
	CDialog::OnOK();
}


