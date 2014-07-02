// DlgRemoteControlCustomInput.cpp : implementation file
//

#include "stdafx.h"
#include "deer.h"
#include "DlgRemoteControlCustomInput.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgRemoteControlCustomInput dialog


CDlgRemoteControlCustomInput::CDlgRemoteControlCustomInput(int iCol, int iRow, CWnd* pParent /*=NULL*/)
	: CDialog(CDlgRemoteControlCustomInput::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgRemoteControlCustomInput)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	// 1. 恶︽计.
	m_trayMap.iCol = iCol;

	// 2. 恶计.
	m_trayMap.iRow = iRow;

	// 3. 恶篈. (0: ON, 1: OFF)
	// int	iStatus[50][100]; 程 (50, 100)
	for (int row = 0; row < m_trayMap.iRow; ++row) 
		for (int col = 0; col < m_trayMap.iCol; ++col) 
			m_trayMap.iStatus[col][row] = 0;

	//
	bLoadFile = false;

	//
	m_LoadFileData.RemoveAll();
}


void CDlgRemoteControlCustomInput::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgRemoteControlCustomInput)
	DDX_Control(pDX, IDOK,		m_btnOK);
	DDX_Control(pDX, IDCANCEL,	m_btnCancel);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgRemoteControlCustomInput, CDialog)
	//{{AFX_MSG_MAP(CDlgRemoteControlCustomInput)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_CLEAR_ALL,	OnClearAll)
	ON_BN_CLICKED(IDC_INVERT,		OnInvert)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgRemoteControlCustomInput message handlers

BOOL CDlgRemoteControlCustomInput::PreTranslateMessage(MSG* pMsg) 
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

BOOL CDlgRemoteControlCustomInput::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// init button 
	m_btnOK.SetIcon(IDI_OK);
	m_btnOK.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnOK.SetFlat(FALSE);
	
	m_btnCancel.SetIcon(IDI_CANCEL);
	m_btnCancel.SetAlign(CButtonST::ST_ALIGN_VERT);
	m_btnCancel.SetFlat(FALSE);
	
	//
	InitTrayStatus();
	
	//
	InitDropListValue();

	//
	SetDefault(0);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
void CDlgRemoteControlCustomInput::SetDefault(int value)
{
	LoadTrayStatus(value);
}
void CDlgRemoteControlCustomInput::InitTrayStatus()
{
	if (GetDlgItem(IDC_ST_INPUTTRAY)) {
		m_stTrayMap.SubclassDlgItem(IDC_ST_INPUTTRAY, this);

		m_stTrayMap.setMapSize(m_trayMap.iCol, m_trayMap.iRow);
		m_stTrayMap.SetForeColour(RGB(255, 0, 0));
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
	if( m.Setting.m_bInputTrayInfo == 1 )
		m_stTrayMap.setInfo( true );

	//
	if( m.Setting.m_bInputTrayTipsNumber == 1 )
		m_stTrayMap.setNumber( true );

	m_stTrayMap.Invalidate();

	SetDlgItemText(IDC_CLEAR_ALL, "Clear All");
	SetDlgItemText(IDC_INVERT, "Invert");

	m_uiTimer = SetTimer(10, 100, NULL);
}
void CDlgRemoteControlCustomInput::InitDropListValue()
{

}
void CDlgRemoteControlCustomInput::LoadTrayStatus(int value)
{
	bLoadFile = true;
	
	CString csFileName = _T("");
	csFileName.Format("%s%d%s", _RemoteInputTrayFileDATA ,value, _RemoteInputTrayFileDATASub );

	//
	m_LoadFileData.RemoveAll();

	//
	CString csFile = m.FilePath.InputCustomInputPath + csFileName;	
	CFile file;
	if(file.Open(csFile, CFile::modeRead | CFile::shareDenyNone, NULL) != 0)
	{
		file.SeekToBegin();
		CArchive ar(&file, CArchive::load);
		CString cs;
		
		while(1)
		{
			BOOL bReadOK = ar.ReadString(cs);
			if( !bReadOK )
				break;
			
			CArray <CString, CString > m_InputRecord;
			f.StringToIntArrayByToken(	cs, m_InputRecord, ",");

			// Position
			int iPos = -1;
			CString csPos = _T("");
			csPos = m_InputRecord.GetAt(0);
			iPos = atoi(csPos);

			// Result 
			int iResult = -1;
			CString csResult = _T("");
			csResult = m_InputRecord.GetAt(1);
			iResult = atoi(csResult);

			// Fill the value 
			int col = 0;
			int row = 0;
			
			col = iPos % m_trayMap.iCol;
			row = iPos / m_trayMap.iCol;
			
			if( iResult == 1 || iResult == 4)
				m_trayMap.iStatus[col][row] = 4;
			else
				m_trayMap.iStatus[col][row] = 0;
		}
		ar.Close();
		file.Close();
	}
	else
	{
		// Open Fail.. ボ⊿Τ郎, ⊿Τ砆砞﹚筁..场耴箂
		for (int row = 0; row < m_trayMap.iRow; ++row) {
			for (int col = 0; col < m_trayMap.iCol; ++col) {
				m_trayMap.iStatus[col][row] = 0;
			}
		}
	}

	// Fill the Object
	for (int row = 0; row < m_trayMap.iRow; ++row) {
		for (int col = 0; col < m_trayMap.iCol; ++col) {
			int n = m_trayMap.iStatus[col][row];
			m_stTrayMap.setCellStatus(col, row, n);
		}
	}

	// Request to Fill UI
	m_stTrayMap.Invalidate();

	bLoadFile = false;
}
void CDlgRemoteControlCustomInput::SaveTrayStatus(int value)
{
	bLoadFile = true;
	
	CString csFileName = _T("");
	csFileName.Format("%s%d%s", _RemoteInputTrayFileDATA ,value, _RemoteInputTrayFileDATASub );
	CString csFile = m.FilePath.InputCustomInputPath + csFileName;	

	// Delete Old File. 
	::DeleteFile( csFile );
	
	//
	CFile file;
	if( file.Open( csFile, CFile::modeCreate | CFile::modeWrite
		| CFile::modeNoTruncate | CFile::shareDenyNone, NULL) != 0)
	{

		if (::IsWindow(m_stTrayMap.m_hWnd)) {
//			if (m_stTrayMap.isModified()) {
				for (int row = 0; row < m_trayMap.iRow; ++row) {
					for (int col = 0; col < m_trayMap.iCol; ++col) {
						
						int n = m_stTrayMap.getCellStatus(col, row);
						file.SeekToEnd();
						int ipos = col + ( m_trayMap.iCol * row );
						CString csstatus = _T("");
						csstatus.Format("%d,%d\r\n", ipos, n);
						file.Write( csstatus.GetBuffer(0), csstatus.GetLength() );
						// 
					}
				}
			}
//		}		
	}

	bLoadFile = false;
}

void CDlgRemoteControlCustomInput::OnTimer(UINT nIDEvent) 
{
	if (!IsWindowVisible()) 
		return;

	if( bLoadFile )
		return;

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

void CDlgRemoteControlCustomInput::OnOK() 
{
	SaveTrayStatus(0);
	
	CDialog::OnOK();
}

void CDlgRemoteControlCustomInput::OnCancel() 
{
	
	CDialog::OnCancel();
}

void CDlgRemoteControlCustomInput::OnClearAll() 
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

void CDlgRemoteControlCustomInput::OnInvert() 
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
