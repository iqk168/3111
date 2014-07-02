// DlgRepeatTrayInOutCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "deer.h"
#include "DlgRepeatTrayInOutCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgRepeatTrayInOutCtrl dialog

CDlgRepeatTrayInOutCtrl::CDlgRepeatTrayInOutCtrl(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgRepeatTrayInOutCtrl::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgRepeatTrayInOutCtrl)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	m_iItemCount = 0;

	m_RepeatInOutCtrl = m.m_RepeatInOutCtrl;

	m_RepeatTrayTemperData.RemoveAll();
}


void CDlgRepeatTrayInOutCtrl::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgRepeatTrayInOutCtrl)
	DDX_Control(pDX, IDC_E_HIGH_TEMP_CONFIM,	m_cbxTemperatureConfim);
	DDX_Control(pDX, IDC_STATIC_TEST_SETTING,	m_wndStaticTestSetting);
	DDX_Control(pDX, IDC_REPEAT_COUNT,			m_cbxTestsetting);
	DDX_Control(pDX, IDC_E_COUNT,				m_wndCount);
	DDX_Control(pDX, IDC_LIST,					m_List);
	DDX_Control(pDX, IDC_T_TRAY2,				m_cbxTray2);
	DDX_Control(pDX, IDC_T_TRAY1,				m_cbxTray1);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgRepeatTrayInOutCtrl, CDialog)
	//{{AFX_MSG_MAP(CDlgRepeatTrayInOutCtrl)
	ON_CBN_SELCHANGE(IDC_T_TRAY1,				OnSelchangeTTray1)
	ON_CBN_SELCHANGE(IDC_T_TRAY2,				OnSelchangeTTray2)
	ON_NOTIFY(NM_RCLICK, IDC_LIST,				OnRclickList)
	ON_COMMAND(ID_LST_DELETE,					OnLstDelete)
	ON_COMMAND(ID_LST_INSERT,					OnLstInsert)
	ON_NOTIFY ( NM_CUSTOMDRAW, IDC_LIST,		OnCustomdrawList )
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgRepeatTrayInOutCtrl message handlers
void CDlgRepeatTrayInOutCtrl::OnRclickList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	CMenu obMenu;
	obMenu.LoadMenu(IDR_LIST_REPEAT_INOUT); 

	CMenu* pPopupMenu = obMenu.GetSubMenu(0);
	ASSERT(pPopupMenu); 
	
	// Get the cursor position
	CPoint obCursorPoint = (0, 0);
	
	GetCursorPos(&obCursorPoint);

	if (0 >= m_List.GetSelectedCount())
	{
		pPopupMenu->EnableMenuItem(ID_LST_DELETE, MF_BYCOMMAND | MF_GRAYED | MF_DISABLED); 
	}
	else
	{
		pPopupMenu->EnableMenuItem(ID_LST_DELETE, MF_BYCOMMAND | MF_ENABLED);
	}

	// Track the popup menu
	pPopupMenu->TrackPopupMenu(TPM_LEFTALIGN|TPM_LEFTBUTTON|TPM_RIGHTBUTTON, obCursorPoint.x, 
									obCursorPoint.y, this);

	*pResult = 0;
}
void CDlgRepeatTrayInOutCtrl::OnCustomdrawList ( NMHDR* pNMHDR, LRESULT* pResult )
{
	NMLVCUSTOMDRAW* pLVCD = reinterpret_cast<NMLVCUSTOMDRAW*>( pNMHDR );
	
    // Take the default processing unless 
    // we set this to something else below.
    *pResult = CDRF_DODEFAULT;
	
    // First thing - check the draw stage. If it's the control's prepaint
    // stage, then tell Windows we want messages for every item.
	
    if ( CDDS_PREPAINT == pLVCD->nmcd.dwDrawStage )
	{
        *pResult = CDRF_NOTIFYITEMDRAW;
	}
    else if ( CDDS_ITEMPREPAINT == pLVCD->nmcd.dwDrawStage )
	{
        // This is the notification message for an item.  We'll request
        // notifications before each subitem's prepaint stage.
		
        *pResult = CDRF_NOTIFYSUBITEMDRAW;
	}
    else if ( (CDDS_ITEMPREPAINT | CDDS_SUBITEM) == pLVCD->nmcd.dwDrawStage )
	{
        // This is the prepaint stage for a subitem. Here's where we set the
        // item's text and background colors. Our return value will tell 
        // Windows to draw the subitem itself, but it will use the new colors
        // we set here.
        // The text color will cycle through red, green, and light blue.
        // The background color will be light blue for column 0, red for
        // column 1, and black for column 2.
		
        COLORREF crText, crBkgnd;
        
        if ( 0 == pLVCD->iSubItem )
		{
			crText	= ST_BLACK;
			crBkgnd = ST_WHITE;
		}
        else if ( 1 == pLVCD->iSubItem )
		{
			crText	= ST_GREEN;
			crBkgnd = ST_WHITE;
		}
		else if ( 2 == pLVCD->iSubItem )
		{
			crText	= ST_RED;
			crBkgnd = ST_WHITE;
		}
        else
		{
			crText	= RGB(128,128,255);
			crBkgnd = ST_WHITE;
		}
		
        // Store the colors back in the NMLVCUSTOMDRAW struct.
        pLVCD->clrText = crText;
        pLVCD->clrTextBk = crBkgnd;
		
        // Tell Windows to paint the control itself.
        *pResult = CDRF_DODEFAULT;
	}
}
void CDlgRepeatTrayInOutCtrl::SetCount(int Count)
{
	CString csCount = _T("");
	csCount.Format("Repeat Times: %d", Count);
	m_wndCount.SetWindowText(csCount);
}
void CDlgRepeatTrayInOutCtrl::OnLstInsert() 
{
	// TODO: Add your command handler code here
	// Insert a new row below the selected row or at the end
	CString strResource = _T("");
	strResource.Format("%d", ++m_iItemCount);	// Item

	// Format
	CString strSVResource = _T("");
	strSVResource.Format("%5.2f", m.m_RepeatTemp.dSV );
	CString strSoakResurce = __T("");
	strSoakResurce.Format("%5.2f", m.m_RepeatTemp.dSoakTime );
	CString strStableResurce = _T("");
	strStableResurce.Format("%5.2f", m.m_RepeatTemp.dStableTime );
	CString strToleranceResurce = _T("");
	strToleranceResurce.Format("%5.2f", m.m_RepeatTemp.dTolerance );
	//

	int iCount = m_List.GetItemCount();

	int iRow = -1;

	POSITION SelectedItemPos = m_List.GetFirstSelectedItemPosition();
	int iIndex = -1;
	int iLastSelectedIndex = -1;

	while (SelectedItemPos)
	{
		iIndex = m_List.GetNextSelectedItem(SelectedItemPos);

		if ((LVIS_SELECTED == m_List.GetItemState(iIndex, LVIS_SELECTED)) && 
			(LVIS_FOCUSED == m_List.GetItemState(iIndex, LVIS_FOCUSED)))
		{
			iRow = iIndex;
		}
		m_List.SetItemState(iIndex, 0, LVIS_SELECTED|LVIS_FOCUSED);
	}


	if (-1 == iRow)
	{
		m_List.InsertItem(LVIF_TEXT|LVIF_STATE, iCount, 
			strResource, LVIS_SELECTED|LVIS_FOCUSED, LVIS_SELECTED|LVIS_FOCUSED, 0, 0);
		m_List.SetItemText(iCount, 1, strSVResource );
		m_List.SetItemText(iCount, 2, strSoakResurce );
		m_List.SetItemText(iCount, 3, strStableResurce );
		m_List.SetItemText(iCount, 4, strToleranceResurce );
	}
	else
	{
		m_List.InsertItem(LVIF_TEXT|LVIF_STATE, iRow, 
			strResource, LVIS_SELECTED|LVIS_FOCUSED, LVIS_SELECTED|LVIS_FOCUSED, 0, 0);

		m_List.SetItemText(iRow, 1, strSVResource );
		m_List.SetItemText(iRow, 2, strSoakResurce );
		m_List.SetItemText(iRow, 3, strStableResurce );
		m_List.SetItemText(iRow, 4, strToleranceResurce );
	}

	// Reset Item Value
	ResetItemValue();
}
void CDlgRepeatTrayInOutCtrl::ResetItemValue()
{
	int iSize = m_List.GetItemCount();
	int iCount = 0;
	for(int i=0;i<iSize;i++)
	{
		CString csItemValue = _T("");
		csItemValue.Format("%d", i+1);
		m_List.SetItemText(i, 0, csItemValue );
	}

	//
	SetCount( iSize );
}
void CDlgRepeatTrayInOutCtrl::OnLstDelete() 
{
	// TODO: Add your command handler code here
	// Get the current selected item
	POSITION SelectionPos = m_List.GetFirstSelectedItemPosition();
	int iCurSel = -1;

	// Laset have one data
	CString csMsg = _T("");
	int iCountNow = 0;
	iCountNow = m_List.GetItemCount();
	if( iCountNow < 0 || iCountNow == 1 )
	{
		CString csMsg = _T("");
		csMsg.Format("Please do not delete all data.!");
		AfxMessageBox( csMsg );
		return;
	}

	// Delete the selected item from the list control 
	while (NULL != SelectionPos)
	{
		SelectionPos = m_List.GetFirstSelectedItemPosition();
		iCurSel = m_List.GetNextSelectedItem(SelectionPos);
		m_List.DeleteItem(iCurSel);
	}

	// Reset Item Value
	ResetItemValue();
}
BOOL CDlgRepeatTrayInOutCtrl::PreTranslateMessage(MSG* pMsg) 
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

BOOL CDlgRepeatTrayInOutCtrl::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	//
	Style();

	//
	InitTrayMode();

	// 
	InitTestsetting();
	
	//
	InitValue();

	//
	ShowTitle();

	//
	ShowData();

	//
	LockUI();

	//
	ChangeUIForTrayFile();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
void CDlgRepeatTrayInOutCtrl::LockUI()
{
	if( m.LotInfo.LotInfoIsLotStart == 1 )
	{	
		m_cbxTestsetting.EnableWindow( FALSE );
		m_cbxTray1.EnableWindow( FALSE );
		m_cbxTray2.EnableWindow( FALSE );
		m_List.EnableWindow( FALSE );	
	}
}
void CDlgRepeatTrayInOutCtrl::ChangeUIForTrayFile()
{
	if( m.TraySpec.Heating == theApp.enHeater )
	{
		m_wndStaticTestSetting.ShowWindow( FALSE );
		m_cbxTestsetting.ShowWindow( FALSE );
		m_List.ShowWindow( TRUE );
		m_wndCount.ShowWindow( TRUE );
		m_cbxTemperatureConfim.ShowWindow( TRUE );
	}
	else if( m.TraySpec.Heating == theApp.enAmbit )
	{
		m_wndStaticTestSetting.ShowWindow( TRUE );
		m_cbxTestsetting.ShowWindow( TRUE );
		m_List.ShowWindow( FALSE );
		m_wndCount.ShowWindow( FALSE );
		m_cbxTemperatureConfim.ShowWindow( FALSE );
	}
	else if( m.TraySpec.Heating == theApp.enATCMoudle )
	{
		m_wndStaticTestSetting.ShowWindow( TRUE );
		m_cbxTestsetting.ShowWindow( TRUE );
		m_List.ShowWindow( FALSE );
		m_wndCount.ShowWindow( FALSE );
		m_cbxTemperatureConfim.ShowWindow( FALSE );
	}
	else if( m.TraySpec.Heating == theApp.enTriTemperature )
	{
		m_wndStaticTestSetting.ShowWindow( TRUE );
		m_cbxTestsetting.ShowWindow( TRUE );
		m_List.ShowWindow( FALSE );
		m_wndCount.ShowWindow( FALSE );
		m_cbxTemperatureConfim.ShowWindow( FALSE );
	}
	else if( m.TraySpec.Heating == theApp.enPTCMoudle )
	{
		m_wndStaticTestSetting.ShowWindow( TRUE );
		m_cbxTestsetting.ShowWindow( TRUE );
		m_List.ShowWindow( FALSE );
		m_wndCount.ShowWindow( FALSE );
		m_cbxTemperatureConfim.ShowWindow( FALSE );
	}
	else
	{
		// Nerver be here
		m_wndStaticTestSetting.ShowWindow( TRUE );
		m_cbxTestsetting.ShowWindow( TRUE );
		m_List.ShowWindow( FALSE );
		m_wndCount.ShowWindow( FALSE );
		m_cbxTemperatureConfim.ShowWindow( FALSE );
	}
}
void CDlgRepeatTrayInOutCtrl::Style()
{
	LONG lStyle;
	lStyle = GetWindowLong(m_List.m_hWnd, GWL_STYLE);
	lStyle &= ~LVS_TYPEMASK; 
	lStyle |= LVS_REPORT; 
	SetWindowLong(m_List.m_hWnd, GWL_STYLE, lStyle);
	
	DWORD dwStyle = m_List.GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT;
	dwStyle |= LVS_EX_GRIDLINES;
//	dwStyle |= LVS_EX_CHECKBOXES;
	m_List.SetExtendedStyle(dwStyle);
}
void CDlgRepeatTrayInOutCtrl::ShowTitle()
{
	// Make the necessary initializations
	m_List.InsertColumn(0, "Item",				LVCFMT_LEFT, 100);
	m_List.InsertColumn(1, "SV(deg)",			LVCFMT_LEFT, 150);
	m_List.InsertColumn(2, "Soak Time(secs)",	LVCFMT_LEFT, 150);
	m_List.InsertColumn(3, "Stable Time(secs)",	LVCFMT_LEFT, 150);
	m_List.InsertColumn(4, "Tolerance(deg)",	LVCFMT_LEFT, 130);

	m_List.SetReadOnlyColumns(0);

	CString strValidChars = "-0123456789.";
	m_List.SetValidEditCtrlCharacters(strValidChars);

	m_List.SetExtendedStyle(LVS_EX_FULLROWSELECT);	
}
void CDlgRepeatTrayInOutCtrl::ShowData()
{
	LoadDataFromFile();
}
void CDlgRepeatTrayInOutCtrl::InitTestsetting()
{
	// 1.0Ah
	CString csInfinity = _T("");
	csInfinity = _Infinity;
	m_cbxTestsetting.AddString( csInfinity );

	//
	int iMax = m.Setting.m_iRepeatMaxiumValue;
	for(int i=0;i<iMax;i++)
	{
		CString csValue = _T("");
		csValue.Format("%d", i+1);
		m_cbxTestsetting.AddString(csValue);
	}

	//
	m_cbxTestsetting.SetCurSel( m.m_RepeatInOutCtrl.m_iRepeatTimes );
}
void CDlgRepeatTrayInOutCtrl::InitTrayMode()
{
	m_cbxTray1.ResetContent();
	m_cbxTray2.ResetContent();

	//
	CArray<CString, CString> m_ReTrayMode;
	m_ReTrayMode.RemoveAll();
	m_ReTrayMode.Add( _RepeartTrayInput );		//	0
	m_ReTrayMode.Add( _RepeartTrayOutput );		//  1
	m_ReTrayMode.Add( _RepeartTrayBoth );		//  2
	m_ReTrayMode.Add( _RepeartTrayDisable );	//  3
//	m_ReTrayMode.Add( _RepeartPass );			//  4
//	m_ReTrayMode.Add( _RepeartFail );			//  5

	int iSize = m_ReTrayMode.GetSize();
	for(int i=0;i<iSize;i++)
	{
		m_cbxTray1.AddString( m_ReTrayMode.GetAt(i) );
		m_cbxTray2.AddString( m_ReTrayMode.GetAt(i) );
	}
}
void CDlgRepeatTrayInOutCtrl::InitValue()
{
	// Tray 1
	if( m_RepeatInOutCtrl.m_iTray1 >=0 )
		m_cbxTray1.SetCurSel( m_RepeatInOutCtrl.m_iTray1 );
	else
		m_cbxTray1.SetCurSel(0);

	// Tray 2
	if( m_RepeatInOutCtrl.m_iTray2 >=0 )
		m_cbxTray2.SetCurSel( m_RepeatInOutCtrl.m_iTray2 );
	else
		m_cbxTray2.SetCurSel(0);

	// Temperature confim with communication
	if( m_RepeatInOutCtrl.m_iRepeatConfimFromComm == 0 )
		m_cbxTemperatureConfim.SetCheck(0);
	else
		m_cbxTemperatureConfim.SetCheck(1);
}
void CDlgRepeatTrayInOutCtrl::CheckItemVerify(int iTray)
{
	if(iTray == 0 )
	{
		// Tray 1 Change..
		int iSel = m_cbxTray1.GetCurSel();
		if( iSel < 0 )
			return;

		CString csSel = _T("");
		m_cbxTray1.GetLBText( iSel, csSel );
		if( csSel ==  _RepeartTrayInput )
		{
			// 狦 Tray1 琌, ê或 Tray2 璶砞﹚
			int iResetSel = m_cbxTray2.FindString( 0, _RepeartTrayOutput );
			m_cbxTray2.SetCurSel( iResetSel );
		}
		else if( csSel ==  _RepeartTrayOutput )
		{
			// 狦 Tray1 琌, ê或 Tray2 璶砞﹚
			int iResetSel = m_cbxTray2.FindString( 0, _RepeartTrayInput );
			m_cbxTray2.SetCurSel( iResetSel );
		}
		else if( csSel == _RepeartTrayBoth )
		{
			// 狦 Tray1 琌/, ê或 Tray2 璶砞﹚/
			int iResetSel = m_cbxTray2.FindString( 0, _RepeartTrayBoth );
			m_cbxTray2.SetCurSel( iResetSel );		
		}
		else if( csSel == _RepeartTrayDisable )
		{
			// 狦 Tray1 琌闽超, ê或 Tray2 璶砞﹚/
			int iResetSel = m_cbxTray2.FindString( 0, _RepeartTrayBoth );
			m_cbxTray2.SetCurSel( iResetSel );		
		}
		else if( csSel == _RepeartPass )
		{
			// 狦 Tray1 琌 Pass, ê或 Tray2 璶砞﹚ Fail
			int iResetSel = m_cbxTray2.FindString( 0, _RepeartFail );
			m_cbxTray2.SetCurSel( iResetSel );		
		}
		else if( csSel == _RepeartFail )
		{
			// 狦 Tray1 琌 Fail, ê或 Tray2 璶砞﹚ Pass
			int iResetSel = m_cbxTray2.FindString( 0, _RepeartPass );
			m_cbxTray2.SetCurSel( iResetSel );	
		}
	}
	else if( iTray == 1 )
	{
		// Tray 2 Change..
		int iSel = m_cbxTray2.GetCurSel();
		if( iSel < 0 )
			return;

		CString csSel = _T("");
		m_cbxTray2.GetLBText( iSel, csSel );
		if( csSel ==  _RepeartTrayInput )
		{
			// 狦 Tray2 琌, ê或 Tray1 璶砞﹚
			int iResetSel = m_cbxTray1.FindString( 0, _RepeartTrayOutput );
			m_cbxTray1.SetCurSel( iResetSel );
		} 
		else if( csSel ==  _RepeartTrayOutput )
		{
			// 狦 Tray2 琌, ê或 Tray1 璶砞﹚
			int iResetSel = m_cbxTray1.FindString( 0, _RepeartTrayInput );
			m_cbxTray1.SetCurSel( iResetSel );
		}
		else if( csSel == _RepeartTrayBoth )
		{
			// 狦 Tray2 琌/, ê或 Tray1 璶砞﹚/
			int iResetSel = m_cbxTray1.FindString( 0, _RepeartTrayBoth );
			m_cbxTray1.SetCurSel( iResetSel );		
		}		
		else if( csSel == _RepeartTrayDisable )
		{
			// 狦 Tray2 琌闽超, ê或 Tray1 璶砞﹚/
			int iResetSel = m_cbxTray1.FindString( 0, _RepeartTrayBoth );
			m_cbxTray1.SetCurSel( iResetSel );		
		}
		else if( csSel == _RepeartPass )
		{
			// 狦 Tray1 琌 Pass, ê或 Tray2 璶砞﹚ Fail
			int iResetSel = m_cbxTray1.FindString( 0, _RepeartFail );
			m_cbxTray1.SetCurSel( iResetSel );		
		}
		else if( csSel == _RepeartFail )
		{
			// 狦 Tray1 琌 Fail, ê或 Tray2 璶砞﹚ Pass
			int iResetSel = m_cbxTray1.FindString( 0, _RepeartPass );
			m_cbxTray1.SetCurSel( iResetSel );	
		}
	}
}
void CDlgRepeatTrayInOutCtrl::OnSelchangeTTray1() 
{
	CheckItemVerify(0);	
}

void CDlgRepeatTrayInOutCtrl::OnSelchangeTTray2() 
{
	CheckItemVerify(1);	
}
void CDlgRepeatTrayInOutCtrl::LoadDataFromFile()
{
	CString csFile = _T("");
	csFile = m.FilePath.RepeatTrayTemperPath;
	int iSize = m_RepeatTrayTemperData.GetSize();

	// Remove data from array
	m_RepeatTrayTemperData.RemoveAll();

	// Load old file
	CFile file;
	if(file.Open(csFile, CFile::modeRead | CFile::shareDenyNone, NULL) != 0)
	{	
		file.SeekToBegin();
		CArchive ar(&file, CArchive::load);
		CString cs = _T("");
		while(1)
		{
			BOOL bReadOK = ar.ReadString(cs);
			if( !bReadOK )
				break;

			tagRepeatTemperData m_Data;
			m_Data.m_dSV = 0.0;
			m_Data.m_dStableTime = 0.0;
			m_Data.m_dSoakingTime = 0.0;
			m_Data.m_dTolerance = 0.0;

			CArray <CString, CString > m_Record;
			m_Record.RemoveAll();
			f.StringToIntArrayByToken(	cs, m_Record, ",");

			if( m_Record.GetSize() == 4 )
			{
				// SV
				CString csSV = _T("");
				csSV = m_Record.GetAt(0);
				csSV.TrimLeft(); csSV.TrimRight();
				m_Data.m_dSV = atof(csSV);

				// Stable Time
				CString csStableTime = _T("");
				csStableTime = m_Record.GetAt(1);
				csStableTime.TrimLeft(); csStableTime.TrimRight();
				m_Data.m_dStableTime = atof(csStableTime);

				// Soaking Time
				CString csSoakingTime = _T("");
				csSoakingTime = m_Record.GetAt(2);
				csSoakingTime.TrimLeft(); csSoakingTime.TrimRight();
				m_Data.m_dSoakingTime = atof(csSoakingTime);

				// Tolerance
				CString csTolerance = _T("");
				csTolerance = m_Record.GetAt(3);
				csTolerance.TrimLeft(); csTolerance.TrimRight();
				m_Data.m_dTolerance = atof(csTolerance);

				m_RepeatTrayTemperData.Add(m_Data);
			}
			else
			{
				// data break. 
			}
			Sleep(1);
		}
		ar.Close();
		file.Close();


		// Add data to list
		int iDataSize = m_RepeatTrayTemperData.GetSize();
		for(int j=0;j<iDataSize;j++)
		{
			CString strResource = _T("");
			strResource.Format("%d", j+1);	// Item
			CString strSVResource = _T("");
			strSVResource.Format("%5.2f", m_RepeatTrayTemperData.GetAt(j).m_dSV );
			CString strSoakResurce = __T("");
			strSoakResurce.Format("%5.2f", m_RepeatTrayTemperData.GetAt(j).m_dSoakingTime );
			CString strStableResurce = _T("");
			strStableResurce.Format("%5.2f", m_RepeatTrayTemperData.GetAt(j).m_dStableTime );
			CString strToleranceResurce = _T("");
			strToleranceResurce.Format("%5.2f", m_RepeatTrayTemperData.GetAt(j).m_dTolerance );
			//			
			m_List.InsertItem(LVIF_TEXT|LVIF_STATE, j, 
				strResource, LVIS_FOCUSED, LVIS_FOCUSED, 0, 0);
			m_List.SetItemText(j, 1, strSVResource );
			m_List.SetItemText(j, 2, strSoakResurce );
			m_List.SetItemText(j, 3, strStableResurce );
			m_List.SetItemText(j, 4, strToleranceResurce );			
		}
		SetCount( iDataSize );
	}
	else
	{
		//
		CString csMsg = _T("");
		csMsg.Format("Load: Open file fail, %s", csFile );
		AfxMessageBox( csMsg );
	}
}
void CDlgRepeatTrayInOutCtrl::SaveDataToFile()
{
	int iSize = m_RepeatTrayTemperData.GetSize();
	CString csFile = _T("");
	csFile = m.FilePath.RepeatTrayTemperPath;

	// Kill old file
	::DeleteFile( csFile );

	// Create new one
	CFile file;
	if( file.Open(csFile, CFile::modeCreate | CFile::modeWrite
		| CFile::modeNoTruncate | CFile::shareDenyNone, NULL) )
	{
		for(int i=0;i<iSize;i++)
		{			
			CString csData = _T("");
			//sv, stable, soaking, tolerance
			csData.Format("%5.2f,%5.2f,%5.2f,%5.2f\r\n", 
				m_RepeatTrayTemperData.GetAt(i).m_dSV,
				m_RepeatTrayTemperData.GetAt(i).m_dStableTime,
				m_RepeatTrayTemperData.GetAt(i).m_dSoakingTime,
				m_RepeatTrayTemperData.GetAt(i).m_dTolerance );

			file.SeekToEnd();
			file.Write(csData.GetBuffer(0), csData.GetLength());			
		}
		file.Close();
	}
	else
	{
		//
		CString csMsg = _T("");
		csMsg.Format("Save: Open file fail, %s", csFile );
		AfxMessageBox( csMsg );
	}
}
void CDlgRepeatTrayInOutCtrl::GetDataFromList()
{
	//
	m_RepeatTrayTemperData.RemoveAll();

	int iListSize = m_List.GetItemCount();
	for(int i=0;i<iListSize;i++)
	{
		tagRepeatTemperData m_Data;
		m_Data.m_dSV = 0.0;
		m_Data.m_dStableTime = 0.0;
		m_Data.m_dSoakingTime = 0.0;
		m_Data.m_dTolerance = 0.0;

		//
		CString csSV = _T("");	
		csSV = m_List.GetItemText(i, 1);			// SV
		m_Data.m_dSV = atof( csSV );

		CString csSoakingTime = _T("");
		csSoakingTime = m_List.GetItemText(i, 2);	// Soaking Time
		m_Data.m_dSoakingTime = atof( csSoakingTime );

		CString csStableTime = _T("");
		csStableTime = m_List.GetItemText(i, 3);	// Stable Time
		m_Data.m_dStableTime = atof( csStableTime );


		CString csTolerance = _T("");
		csTolerance = m_List.GetItemText(i, 4);		// Tolerance
		m_Data.m_dTolerance = atof( csTolerance );			

		//
		m_RepeatTrayTemperData.Add( m_Data );
	}
}
bool CDlgRepeatTrayInOutCtrl::SaveData(CString &csErr)
{
	bool bSaveOK = true;

	/////////////////////////////////////////////////////////////////
	// Input / Output Setting
	CString csFinalErr = _T("");
	int iSelTray1 = m_cbxTray1.GetCurSel();
	if( iSelTray1 < 0 )
	{
		CString csMsg = _T("");
		csMsg = "Tray1 no select item";
		csFinalErr += csMsg;
		bSaveOK = false;
	}
	else
	{
		// Get Tray1 Value
		m_RepeatInOutCtrl.m_iTray1 = iSelTray1;
	}

	//
	int iSelTray2 = m_cbxTray2.GetCurSel();
	if( iSelTray2 < 0 )
	{
		CString csMsg = _T("");
		csMsg = "Tray2 no select item";
		csFinalErr += csMsg;
		bSaveOK = false;
	}
	else
	{
		// Get Tray2 Value
		m_RepeatInOutCtrl.m_iTray2 = iSelTray2;
	}

	// Repeat Time
	m_RepeatInOutCtrl.m_iRepeatTimes = m_cbxTestsetting.GetCurSel();

	// Temperature from communication
	int iTemperature = m_cbxTemperatureConfim.GetCheck();
	m_RepeatInOutCtrl.m_iRepeatConfimFromComm = iTemperature;

	/////////////////////////////////////////////////////////////////
	// Temperature Setting 
	GetDataFromList();
	
	SaveDataToFile();

	f.LoadRepeatTrayTemper(); // re-load file

	//
	m.m_RepeatInOutCtrl = m_RepeatInOutCtrl;
	f.SaveRepeatTrayInOut();

	return bSaveOK;
}
