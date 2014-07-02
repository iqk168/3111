// DlgInputTrayMap.cpp : implementation file
//

#include "stdafx.h"
#include "Deer.h"
#include "DlgInputTrayMap.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgInputTrayMap dialog


CDlgInputTrayMap::CDlgInputTrayMap(int iCol, int iRow, int *piStatus, CWnd* pParent /*=NULL*/)
	: CDialog(CDlgInputTrayMap::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgInputTrayMap)
	//}}AFX_DATA_INIT

	// 1. 填入行數.
	m_trayMap.iCol = iCol;

	// 2. 填入列數.
	m_trayMap.iRow = iRow;

	// 3. 填入狀態. (0: ON, 1: OFF)
	// int	iStatus[50][100]; 最大值為 (50, 100)
	m_piStatus = piStatus;
	for (int row = 0; row < m_trayMap.iRow; ++row) 
		for (int col = 0; col < m_trayMap.iCol; ++col) 
			m_trayMap.iStatus[col][row] = *(m_piStatus + (row * m_trayMap.iCol + col)) == 4 ? 1 : 0;
}


void CDlgInputTrayMap::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgInputTrayMap)
	DDX_Control(pDX, IDOK, m_btnOK);
	DDX_Control(pDX, IDCANCEL, m_btnCancel);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgInputTrayMap, CDialog)
	//{{AFX_MSG_MAP(CDlgInputTrayMap)
	ON_WM_DESTROY()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_INVERT, OnInvert)
	ON_BN_CLICKED(IDC_CLEAR_ALL, OnClearAll)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgInputTrayMap message handlers

BOOL CDlgInputTrayMap::OnInitDialog() 
{
	CDialog::OnInitDialog();

	m.Info.bSubDlgOpen = true;
	f.UpdateButtonState();	
	
	// init button 
	m_btnOK.SetIcon(IDI_OK);;
	m_btnOK.SetAlign(CButtonST::ST_ALIGN_VERT);;
	m_btnOK.SetFlat(FALSE);
	
	m_btnCancel.SetIcon(IDI_CANCEL);
	m_btnCancel.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnCancel.SetFlat(FALSE);

	//
//	InitTips();
	
	if (GetDlgItem(IDC_ST_INPUTTRAY)) {
		m_stTrayMap.SubclassDlgItem(IDC_ST_INPUTTRAY, this);

		m_stTrayMap.setMapSize(m_trayMap.iCol, m_trayMap.iRow);
		m_stTrayMap.SetForeColour(RGB(192,192,192));
		m_stTrayMap.SetBkColour(RGB(0,128,192));
	}

	for (int row = 0; row < m_trayMap.iRow; ++row) {
		for (int col = 0; col < m_trayMap.iCol; ++col) {

			int n = m_trayMap.iStatus[col][row];
			m_stTrayMap.setCellStatus(col, row, n);
		}
	}
	
	// Chip Tray
	m_stTrayMap.setChipTray( 
		m.TraySpec.m_InputUseChipTray, m.TraySpec.m_SubTrayColumn, m.TraySpec.m_SubTrayRow );

	//
	if( m.Setting.m_bInputTrayTips == 1 )
		m_stTrayMap.setTip( true );

	//
	if( m.Setting.m_bInputTrayTipsNumber == 1 )
		m_stTrayMap.setNumber( true );

	//
	if( m.Setting.m_bInputTrayInfo == 1 )
		m_stTrayMap.setInfo( true );

	m_stTrayMap.Invalidate();

	SetDlgItemText(IDC_CLEAR_ALL, "Clear All");
	SetDlgItemText(IDC_INVERT, "Invert");

	m_uiTimer = SetTimer(10, 100, NULL);

	f.ChangeLanguage(GetSafeHwnd());

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
void CDlgInputTrayMap::InitTips()
{

}
void CDlgInputTrayMap::OnDestroy() 
{
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here
	if (m_uiTimer) {
		KillTimer(m_uiTimer);
		m_uiTimer = 0;
	}
}

void CDlgInputTrayMap::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	if (!IsWindowVisible()) return;

	if (::IsWindow(m_stTrayMap.m_hWnd)) {
		if (m_stTrayMap.isModified()) {
			for (int row = 0; row < m_trayMap.iRow; ++row) {
				for (int col = 0; col < m_trayMap.iCol; ++col) {

					int n = m_stTrayMap.getCellStatus(col, row);
					m_trayMap.iStatus[col][row] = n;
				}
			}
			m_stTrayMap.setModified(false);
			m_stTrayMap.Invalidate();
		}
	}

	CDialog::OnTimer(nIDEvent);
}

void CDlgInputTrayMap::OnOK() 
{
	// TODO: Add extra validation here
	for (int row = 0; row < m_trayMap.iRow; ++row) 
		for (int col = 0; col < m_trayMap.iCol; ++col) 
			*(m_piStatus + (row * m_trayMap.iCol + col)) = m_trayMap.iStatus[col][row] == 1 ? 4 : 0;
	

	m.Info.bSubDlgOpen = false;
	f.UpdateButtonState();

	CDialog::OnOK();
}

void CDlgInputTrayMap::OnInvert() 
{
	// TODO: Add your control notification handler code here
	for (int row = 0; row < m_trayMap.iRow; ++row) {
		for (int col = 0; col < m_trayMap.iCol; ++col) {
			int n = m_stTrayMap.getCellStatus(col, row)?0:1;
			m_stTrayMap.setCellStatus(col, row, n);
			m_trayMap.iStatus[col][row] = n;;
		}
	}
	m_stTrayMap.Invalidate();			
}

void CDlgInputTrayMap::OnClearAll() 
{
	// TODO: Add your control notification handler code here
	for (int row = 0; row < m_trayMap.iRow; ++row) {
		for (int col = 0; col < m_trayMap.iCol; ++col) {
			m_stTrayMap.setCellStatus(col, row, 1);
			m_trayMap.iStatus[col][row] = 1;
		}
	}
	m_stTrayMap.Invalidate();		
}

void CDlgInputTrayMap::OnCancel() 
{
	m.Info.bSubDlgOpen = false;
	f.UpdateButtonState();
	
	CDialog::OnCancel();
}

BOOL CDlgInputTrayMap::PreTranslateMessage(MSG* pMsg) 
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
