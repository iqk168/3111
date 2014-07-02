// DlgInOutputTrayMap.cpp : implementation file
//

#include "stdafx.h"
#include "deer.h"
#include "DlgInOutputTrayMap.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgInOutputTrayMap dialog


CDlgInOutputTrayMap::CDlgInOutputTrayMap(int iCol, int iRow, int *piStatusInput, int *piStatusOutput, CWnd* pParent /*=NULL*/)
	: CDialog(CDlgInOutputTrayMap::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgInOutputTrayMap)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	///////////////////////////////////////////////
	// Input 
	InitInputTrayObject(iCol, iRow, piStatusInput);

	///////////////////////////////////////////////
	// Output 
	InitOutputTrayObject(iCol, iRow, piStatusOutput);
}


void CDlgInOutputTrayMap::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgInOutputTrayMap)
	DDX_Control(pDX, IDCANCEL,	m_btnCancel);
	DDX_Control(pDX, IDOK,		m_btnOK);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgInOutputTrayMap, CDialog)
	//{{AFX_MSG_MAP(CDlgInOutputTrayMap)
	ON_BN_CLICKED(IDC_IN_CLEAR_ALL,			OnInClearAll)
	ON_BN_CLICKED(IDC_IN_INVERT,			OnInInvert)
	ON_BN_CLICKED(IDC_OUT_CLEAR_ALL,		OnOutClearAll)
	ON_BN_CLICKED(IDC_OUT_INVERT,			OnOutInvert)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgInOutputTrayMap message handlers

void CDlgInOutputTrayMap::OnInClearAll() 
{
	for (int row = 0; row < m_trayMapInput.iRow; ++row) {
		for (int col = 0; col < m_trayMapInput.iCol; ++col) {
			m_stTrayMapInput.setCellStatus(col, row, 1);
			m_trayMapInput.iStatus[col][row] = 1;
		}
	}
	m_stTrayMapInput.Invalidate();	
}

void CDlgInOutputTrayMap::OnInInvert() 
{
	for (int row = 0; row < m_trayMapInput.iRow; ++row) {
		for (int col = 0; col < m_trayMapInput.iCol; ++col) {
			int n = m_stTrayMapInput.getCellStatus(col, row)?0:1;
			m_stTrayMapInput.setCellStatus(col, row, n);
			m_trayMapInput.iStatus[col][row] = n;;
		}
	}
	m_stTrayMapInput.Invalidate();		
}

void CDlgInOutputTrayMap::OnOutClearAll() 
{
	for (int row = 0; row < m_trayMapOutput.iRow; ++row) {
		for (int col = 0; col < m_trayMapOutput.iCol; ++col) {
			m_stTrayMapOutput.setCellStatus(col, row, 1);
			m_trayMapOutput.iStatus[col][row] = 1;
		}
	}
	m_stTrayMapOutput.Invalidate();	
}

void CDlgInOutputTrayMap::OnOutInvert() 
{
	for (int row = 0; row < m_trayMapOutput.iRow; ++row) {
		for (int col = 0; col < m_trayMapOutput.iCol; ++col) {
			int n = m_stTrayMapOutput.getCellStatus(col, row)?0:1;
			m_stTrayMapOutput.setCellStatus(col, row, n);
			m_trayMapOutput.iStatus[col][row] = n;;
		}
	}
	m_stTrayMapOutput.Invalidate();	
}
void CDlgInOutputTrayMap::SaveTrayStatus() 
{
	// Input 
	SaveInputTrayStatus();

	// Output
	SaveOutputTrayStatus();
}
void CDlgInOutputTrayMap::SaveInputTrayStatus()
{
	for (int row = 0; row < m_trayMapInput.iRow; ++row) 
		for (int col = 0; col < m_trayMapInput.iCol; ++col) 
			*(m_piStatusInput + (row * m_trayMapInput.iCol + col)) = m_trayMapInput.iStatus[col][row] == 1 ? 4 : 0;
}
void CDlgInOutputTrayMap::SaveOutputTrayStatus()
{
	for (int row = 0; row < m_trayMapOutput.iRow; ++row) 
		for (int col = 0; col < m_trayMapOutput.iCol; ++col) 
			*(m_piStatusOutput + (row * m_trayMapOutput.iCol + col)) = m_trayMapOutput.iStatus[col][row] == 1 ? 4 : 0;
}
void CDlgInOutputTrayMap::OnOK() 
{
	SaveTrayStatus();

	m.Info.bSubDlgOpen = false;
	f.UpdateButtonState();
	
	CDialog::OnOK();
}

void CDlgInOutputTrayMap::OnCancel() 
{
	m.Info.bSubDlgOpen = false;
	f.UpdateButtonState();
	
	CDialog::OnCancel();
}

BOOL CDlgInOutputTrayMap::PreTranslateMessage(MSG* pMsg) 
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

BOOL CDlgInOutputTrayMap::OnInitDialog() 
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
	InitInputTray();

	//
	InitOutputTray();

	//
	m_uiTimer = SetTimer(10, 100, NULL);

	f.ChangeLanguage(GetSafeHwnd());
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
void CDlgInOutputTrayMap::InitInputTrayObject(int iCol, int iRow, int *piStatusInput)
{
	// 1. 恶︽计.
	m_trayMapInput.iCol = iCol;

	// 2. 恶计.
	m_trayMapInput.iRow = iRow;

	// 3. 恶篈. (0: ON, 1: OFF)
	// int	iStatus[50][100]; 程 (50, 100)
	m_piStatusInput = piStatusInput;
	for (int row = 0; row < m_trayMapInput.iRow; ++row) 
		for (int col = 0; col < m_trayMapInput.iCol; ++col) 
			m_trayMapInput.iStatus[col][row] = *(m_piStatusInput + (row * m_trayMapInput.iCol + col)) == 4 ? 1 : 0;
}
void CDlgInOutputTrayMap::InitOutputTrayObject(int iCol, int iRow, int *piStatusOutput)
{
	// 1. 恶︽计.
	m_trayMapOutput.iCol = iCol;

	// 2. 恶计.
	m_trayMapOutput.iRow = iRow;

	// 3. 恶篈. (0: ON, 1: OFF)
	// int	iStatus[50][100]; 程 (50, 100)					   
	m_piStatusOutput = piStatusOutput;
	for (int row = 0; row < m_trayMapOutput.iRow; ++row) 
		for (int col = 0; col < m_trayMapOutput.iCol; ++col) 
			m_trayMapOutput.iStatus[col][row] = *(m_piStatusOutput + (row * m_trayMapOutput.iCol + col)) == 4 ? 1 : 0;
}
void CDlgInOutputTrayMap::InitInputTray()
{
	if (GetDlgItem(IDC_ST_INPUTTRAY)) {
		m_stTrayMapInput.SubclassDlgItem(IDC_ST_INPUTTRAY, this);

		m_stTrayMapInput.setMapSize(m_trayMapInput.iCol, m_trayMapInput.iRow);
		m_stTrayMapInput.SetForeColour(RGB(192,192,192));
		m_stTrayMapInput.SetBkColour(RGB(0,128,192));
	}

	for (int row = 0; row < m_trayMapInput.iRow; ++row) {
		for (int col = 0; col < m_trayMapInput.iCol; ++col) {

			int n = m_trayMapInput.iStatus[col][row];
			m_stTrayMapInput.setCellStatus(col, row, n);
		}
	}
	
	// Chip Tray
	m_stTrayMapInput.setChipTray( 
		m.TraySpec.m_InputUseChipTray, m.TraySpec.m_SubTrayColumn, m.TraySpec.m_SubTrayRow );

	//
	if( m.Setting.m_bInputTrayTipsNumber == 1 )
		m_stTrayMapInput.setNumber( true );

	m_stTrayMapInput.Invalidate();
}
void CDlgInOutputTrayMap::InitOutputTray()
{
	if (GetDlgItem(IDC_ST_INPUTTRAY)) {
		m_stTrayMapOutput.SubclassDlgItem(IDC_ST_OUTPUTTRAY, this);

		m_stTrayMapOutput.setMapSize(m_trayMapInput.iCol, m_trayMapInput.iRow);
//		m_stTrayMapOutput.SetForeColour(RGB(192,192,192));
//		m_stTrayMapOutput.SetBkColour(RGB(0,128,192));

		m_stTrayMapOutput.SetBkColour(RGB(192,192,192));
		m_stTrayMapOutput.SetForeColour(RGB(0,128,192));
	}

	for (int row = 0; row < m_trayMapOutput.iRow; ++row) {
		for (int col = 0; col < m_trayMapOutput.iCol; ++col) {

			int n = m_trayMapOutput.iStatus[col][row];
			m_stTrayMapOutput.setCellStatus(col, row, n);
		}
	}
	
	// Chip Tray
	m_stTrayMapOutput.setChipTray( 
		m.TraySpec.m_FixUseChipTray, m.TraySpec.m_SubTrayColumn, m.TraySpec.m_SubTrayRow );

	//
	if( m.Setting.m_bInputTrayTipsNumber == 1 )
		m_stTrayMapOutput.setNumber( true );

	m_stTrayMapOutput.Invalidate();
}

void CDlgInOutputTrayMap::OnTimer(UINT nIDEvent) 
{
	if (!IsWindowVisible()) 
		return;

	///////////////////////////////////////////////////////
	// Input
	if (::IsWindow(m_stTrayMapInput.m_hWnd)) {
		if (m_stTrayMapInput.isModified()) {
			for (int row = 0; row < m_trayMapInput.iRow; ++row) {
				for (int col = 0; col < m_trayMapInput.iCol; ++col) {

					int n = m_stTrayMapInput.getCellStatus(col, row);
					m_trayMapInput.iStatus[col][row] = n;
				}
			}
			m_stTrayMapInput.setModified(false);
			m_stTrayMapInput.Invalidate();
		}
	}	
	
	///////////////////////////////////////////////////////
	// Output
	if (::IsWindow(m_stTrayMapOutput.m_hWnd)) {
		if (m_stTrayMapOutput.isModified()) {
			for (int row = 0; row < m_trayMapOutput.iRow; ++row) {
				for (int col = 0; col < m_trayMapOutput.iCol; ++col) {

					int n = m_stTrayMapOutput.getCellStatus(col, row);
					m_trayMapOutput.iStatus[col][row] = n;
				}
			}
			m_stTrayMapOutput.setModified(false);
			m_stTrayMapOutput.Invalidate();
		}
	}	
	CDialog::OnTimer(nIDEvent);
}
