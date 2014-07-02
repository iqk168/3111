// DlgOutputTrayMap.cpp : implementation file
//

#include "stdafx.h"
#include "deer.h"
#include "DlgOutputTrayMap.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgOutputTrayMap dialog


CDlgOutputTrayMap::CDlgOutputTrayMap(int iCol, int iRow, int *piStatus, CWnd* pParent /*=NULL*/)
	: CDialog(CDlgOutputTrayMap::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgOutputTrayMap)
		// NOTE: the ClassWizard will add member initialization here
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


void CDlgOutputTrayMap::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgOutputTrayMap)
	DDX_Control(pDX, IDCANCEL, m_btnCancel);
	DDX_Control(pDX, IDOK, m_btnOK);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgOutputTrayMap, CDialog)
	//{{AFX_MSG_MAP(CDlgOutputTrayMap)
	ON_WM_DESTROY()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_CLEAR_ALL, OnClearAll)
	ON_BN_CLICKED(IDC_INVERT, OnInvert)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgOutputTrayMap message handlers

BOOL CDlgOutputTrayMap::PreTranslateMessage(MSG* pMsg) 
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
void CDlgOutputTrayMap::InitTips()
{

}
void CDlgOutputTrayMap::OnDestroy() 
{
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here
	
}

BOOL CDlgOutputTrayMap::OnInitDialog() 
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
//		m_stTrayMap.SetForeColour(RGB(192,192,192));
//		m_stTrayMap.SetBkColour(RGB(0,128,192));

		m_stTrayMap.SetBkColour(RGB(192,192,192));
		m_stTrayMap.SetForeColour(RGB(0,128,192));
	}

	for (int row = 0; row < m_trayMap.iRow; ++row) {
		for (int col = 0; col < m_trayMap.iCol; ++col) {

			int n = m_trayMap.iStatus[col][row];
			m_stTrayMap.setCellStatus(col, row, n);
		}
	}
	
	// Chip Tray
	m_stTrayMap.setChipTray( 
		m.TraySpec.m_FixUseChipTray, m.TraySpec.m_SubTrayColumn, m.TraySpec.m_SubTrayRow );

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

void CDlgOutputTrayMap::OnTimer(UINT nIDEvent) 
{
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

void CDlgOutputTrayMap::OnClearAll() 
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

void CDlgOutputTrayMap::OnInvert() 
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

void CDlgOutputTrayMap::OnOK() 
{
	// TODO: Add extra validation here
	for (int row = 0; row < m_trayMap.iRow; ++row) 
		for (int col = 0; col < m_trayMap.iCol; ++col) 
			*(m_piStatus + (row * m_trayMap.iCol + col)) = m_trayMap.iStatus[col][row] == 1 ? 4 : 0;

	m.Info.bSubDlgOpen = false;
	f.UpdateButtonState();
	
	CDialog::OnOK();
}

void CDlgOutputTrayMap::OnCancel() 
{
	m.Info.bSubDlgOpen = false;
	f.UpdateButtonState();
	
	CDialog::OnCancel();
}
