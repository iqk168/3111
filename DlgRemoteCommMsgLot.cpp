// DlgRemoteCommMsgLot.cpp : implementation file
//

#include "stdafx.h"
#include "deer.h"
#include "DlgRemoteCommMsgLot.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgRemoteCommMsgLot dialog


CDlgRemoteCommMsgLot::CDlgRemoteCommMsgLot(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgRemoteCommMsgLot::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgRemoteCommMsgLot)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgRemoteCommMsgLot::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgRemoteCommMsgLot)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgRemoteCommMsgLot, CDialog)
	//{{AFX_MSG_MAP(CDlgRemoteCommMsgLot)
	ON_BN_CLICKED(IDC_F_GET_LOT_NO,			OnFGetLotNo)
	ON_BN_CLICKED(IDC_F_SET_LOT_NO,			OnFSetLotNo)
	ON_BN_CLICKED(IDC_F_GET_MACHINE_NO,		OnFGetMachineNo)
	ON_BN_CLICKED(IDC_F_SET_MACHINE_NO,		OnFSetMachineNo)
	ON_BN_CLICKED(IDC_F_GET_OPERATOR_NO,	OnFGetOperatorNo)
	ON_BN_CLICKED(IDC_F_SET_OPERATOR_NO,	OnFSetOperatorNo)
	ON_BN_CLICKED(IDC_F_GET_DEVICE_ID,		OnFGetDeviceId)
	ON_BN_CLICKED(IDC_F_SET_DEVICE_ID,		OnFSetDeviceId)
	ON_BN_CLICKED(IDC_F_GET_PROGRAM_ID,		OnFGetProgramId)
	ON_BN_CLICKED(IDC_F_SET_PROGRAM_ID,		OnFSetProgramId)
	ON_BN_CLICKED(IDC_F_SET_NEW_LOT,		OnFSetNewLot)
	ON_BN_CLICKED(IDC_F_SET_LOT_DOWN,		OnFSetLotDown)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgRemoteCommMsgLot message handlers

BOOL CDlgRemoteCommMsgLot::PreTranslateMessage(MSG* pMsg) 
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

BOOL CDlgRemoteCommMsgLot::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgRemoteCommMsgLot::OnFGetLotNo() 
{
	m.m_TestInterface.RemoteCommAddBuffer( "<<GetLot?:0>>" );		
}
void CDlgRemoteCommMsgLot::OnFSetLotNo() 
{
	m.m_TestInterface.RemoteCommAddBuffer( "<<SetLot:0,LotNo>>" );	
}
void CDlgRemoteCommMsgLot::OnFGetMachineNo() 
{
	m.m_TestInterface.RemoteCommAddBuffer( "<<GetLot?:1>>" );	
}
void CDlgRemoteCommMsgLot::OnFSetMachineNo() 
{
	m.m_TestInterface.RemoteCommAddBuffer( "<<SetLot:1,Macine>>" );	
}
void CDlgRemoteCommMsgLot::OnFGetOperatorNo() 
{
	m.m_TestInterface.RemoteCommAddBuffer( "<<GetLot?:2>>" );	
}
void CDlgRemoteCommMsgLot::OnFSetOperatorNo() 
{
	m.m_TestInterface.RemoteCommAddBuffer( "<<SetLot:2,Operator>>" );	
}
void CDlgRemoteCommMsgLot::OnFGetDeviceId() 
{
	m.m_TestInterface.RemoteCommAddBuffer( "<<GetLot?:3>>" );	
}
void CDlgRemoteCommMsgLot::OnFSetDeviceId() 
{
	m.m_TestInterface.RemoteCommAddBuffer( "<<SetLot:3,DeviceID>>" );	
}
void CDlgRemoteCommMsgLot::OnFGetProgramId() 
{
	m.m_TestInterface.RemoteCommAddBuffer( "<<GetLot?:4>>" );	
}
void CDlgRemoteCommMsgLot::OnFSetProgramId() 
{
	m.m_TestInterface.RemoteCommAddBuffer( "<<SetLot:4,ProgramID>>" );	
}

void CDlgRemoteCommMsgLot::OnFSetNewLot() 
{
	
}

void CDlgRemoteCommMsgLot::OnFSetLotDown() 
{
	
}
