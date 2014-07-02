// DlgSettingTTL.cpp : implementation file
//

#include "stdafx.h"
#include "deer.h"
#include "DlgSettingTTL.h"
#include "DlgSettingNote.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgSettingTTL dialog


CDlgSettingTTL::CDlgSettingTTL(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgSettingTTL::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgSettingTTL)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	m_csTtlFile = _T("");
}


void CDlgSettingTTL::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgSettingTTL)
	DDX_Control(pDX, IDC_MASK_GROUP,	m_wndMaskGroup);
	DDX_Control(pDX, IDC_FILE,			m_wndFile);
	DDX_Control(pDX, IDC_TIMEOUT,		m_edtTimeout);
	DDX_Control(pDX, IDC_START_DELAY,	m_edtStartDelay);
	DDX_Control(pDX, IDC_SITE4,			m_edtSite4);
	DDX_Control(pDX, IDC_SITE3,			m_edtSite3);
	DDX_Control(pDX, IDC_SITE2,			m_edtSite2);
	DDX_Control(pDX, IDC_SITE1,			m_edtSite1);
	DDX_Control(pDX, IDC_EOT1,			m_btnEOT1);
	DDX_Control(pDX, IDC_EOT2,			m_btnEOT2);
	DDX_Control(pDX, IDC_READY1,		m_btnReady1);
	DDX_Control(pDX, IDC_READY2,		m_btnReady2);
	DDX_Control(pDX, IDC_LINE1,			m_btnLine);
	DDX_Control(pDX, IDC_LINE2,			m_btnBCD);
	DDX_Control(pDX, IDC_BIN1,			m_btnBinSignal1);
	DDX_Control(pDX, IDC_BIN2,			m_btnBinSignal2);
	DDX_Control(pDX, IDC_LEVEL1,		m_btnLevel);
	DDX_Control(pDX, IDC_LEVEL2,		m_btnPulse);
	DDX_Control(pDX, IDC_TTLPWR0,		m_btnTester);
	DDX_Control(pDX, IDC_TTLPWR1,		m_btnHandler);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgSettingTTL, CDialog)
	//{{AFX_MSG_MAP(CDlgSettingTTL)
	ON_BN_CLICKED(IDC_NOTE,				OnNote)
	ON_BN_CLICKED(IDC_TTL_FILENAME,		OnTtlFilename)
	ON_BN_CLICKED(IDC_ESTATIC,			OnEstatic)
	ON_BN_CLICKED(IDC_EOT1,				OnEot1)
	ON_BN_CLICKED(IDC_EOT2,				OnEot2)
	ON_BN_CLICKED(IDC_READY1,			OnReady1)
	ON_BN_CLICKED(IDC_READY2,			OnReady2)
	ON_BN_CLICKED(IDC_BIN1,				OnBin1)
	ON_BN_CLICKED(IDC_BIN2,				OnBin2)
	ON_BN_CLICKED(IDC_LEVEL1,			OnLevel1)
	ON_BN_CLICKED(IDC_LEVEL2,			OnLevel2)
	ON_BN_CLICKED(IDC_LINE1,			OnLine1)
	ON_BN_CLICKED(IDC_LINE2,			OnLine2)
	ON_BN_CLICKED(IDC_TTLPWR0,			OnTtlpwr0)
	ON_BN_CLICKED(IDC_TTLPWR1,			OnTtlpwr1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgSettingTTL message handlers

void CDlgSettingTTL::OnNote() 
{
	CDlgSettingNote dlg( theApp.enTTL );
	dlg.DoModal();
}

BOOL CDlgSettingTTL::PreTranslateMessage(MSG* pMsg) 
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

BOOL CDlgSettingTTL::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

//
void CDlgSettingTTL::LoadFile()
{
	if( m_csTtlFile == "" )
		return;

	CString csFile = _T("");
	csFile = m.FilePath.InterfaceTtlPath + m_csTtlFile;

	// True / False setting.
	f.GetSettingTrueFalse(csFile, "信號 Active High(1), Low(0)", "EOT",					m_TTLPamera.s_iEOTAssertion);
	f.GetSettingTrueFalse(csFile, "信號 Active High(1), Low(0)", "RDY",					m_TTLPamera.s_iRDYAssertion);
	f.GetSettingTrueFalse(csFile, "信號 Active High(1), Low(0)", "BIN",					m_TTLPamera.s_iBinAssertion);	
	f.GetSettingTrueFalse(csFile, "信號 Active High(1), Low(0)", "Level(0),Pulse(1)",	m_TTLPamera.s_iRDYMode);	
	f.GetSettingTrueFalse(csFile, "Bin 信號", "LINE(0), BCD(1)",						m_TTLPamera.s_iLineMode);

	f.GetSettingDouble(csFile, "Other", "Send Start Delay (sec)",						m_TTLPamera.s_dStartDelay);
	f.GetSettingDouble(csFile, "Other", "Timeout (sec)",								m_TTLPamera.s_dTimeout);
	f.GetSettingTrueFalse(csFile, "Other", "Power Mode(1)Tester(0)Handler",				m_TTLPamera.s_iPowerMode);

	// Wring.
	for(int i=0; i<4; i++)
	{
		CString cs;
		cs.Format("Site %d", i+1);
		f.GetSettingHex(csFile, "Address (pin31:0x260, pin32:0x262, pin33:0x266, pin34:0x268)",
			cs, m_TTLPamera.s_iSiteAddress[i]);

		f.GetSettingBinary(csFile, "MASK (接線寫 1, 沒接寫 0, pin1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16)", 
			cs, m_TTLPamera.s_iSiteMask[i]);
	}
}
void CDlgSettingTTL::InitValue()
{
	if( m_TTLPamera.s_iEOTAssertion == 0 )
	{
		m_btnEOT1.SetCheck(1);
		m_btnEOT2.SetCheck(0);
	}
	else
	{
		m_btnEOT1.SetCheck(0);
		m_btnEOT2.SetCheck(1);
	}
	// EOT Signal 
	// s_iEOTAssertion is 0, It is Low Active

	if( m_TTLPamera.s_iRDYAssertion == 0)
	{
		m_btnReady1.SetCheck(1);
		m_btnReady2.SetCheck(0);
	}
	else
	{
		m_btnReady1.SetCheck(0);
		m_btnReady2.SetCheck(1);
	}
	// READY Signal
	// s_iRDYAssertion is 0,It is Low Acvite

	if( m_TTLPamera.s_iBinAssertion == 0)
	{
		m_btnBinSignal1.SetCheck(1);
		m_btnBinSignal2.SetCheck(0);
	}
	else
	{
		m_btnBinSignal1.SetCheck(0);
		m_btnBinSignal2.SetCheck(1);
	}
	// BIN Signal
	// s_iBinAssertion is 0, It is Low Active

	if( m_TTLPamera.s_iRDYMode == 0 )
	{
		m_btnLevel.SetCheck(1);
		m_btnPulse.SetCheck(0);
	}
	else
	{
		m_btnLevel.SetCheck(0);
		m_btnPulse.SetCheck(1);
	}
	// Signal From
	// TTLParm.s_iRDYMode: 0 is level, It it level. 1 is pulse

	if( m_TTLPamera.s_iLineMode == 0 )
	{
		m_btnLine.SetCheck(1);
		m_btnBCD.SetCheck(0);
	}
	else
	{
		m_btnLine.SetCheck(0);
		m_btnBCD.SetCheck(1);
	}
	// Output Line
	// TTLParm.s_iLineMode: 0 is Line to Line. 1 is BCD

	if( m_TTLPamera.s_iPowerMode == 1 )
	{
		m_btnTester.SetCheck(1);
		m_btnHandler.SetCheck(0);
	}
	else
	{
		m_btnTester.SetCheck(0);
		m_btnHandler.SetCheck(1);
	}
	// Power Mode. 1 = from Tester / 0 = from Handler.!

	// Mask.
	CString csSite4 = _T("");
	csSite4.Format("%s", ConvertIntToBin ( m_TTLPamera.s_iSiteMask[3] ) );
	m_edtSite4.SetWindowText( csSite4 );

	CString csSite3 = _T("");
	csSite3.Format("%s", ConvertIntToBin ( m_TTLPamera.s_iSiteMask[2] ) );
	m_edtSite3.SetWindowText( csSite3 );

	CString csSite2 = _T("");
	csSite2.Format("%s", ConvertIntToBin ( m_TTLPamera.s_iSiteMask[1] ) );
	m_edtSite2.SetWindowText( csSite2 );


	CString csSite1 = _T("");
	csSite1.Format("%s", ConvertIntToBin( m_TTLPamera.s_iSiteMask[0] ) );
	m_edtSite1.SetWindowText( csSite1 );
	

	//
	CString csTimeout = _T("");
	csTimeout.Format("%5.2f", m_TTLPamera.s_dTimeout );	
	m_edtTimeout.SetWindowText( csTimeout );

	//
	CString csStartDelay = _T("");
	csStartDelay.Format("%5.2f", m_TTLPamera.s_dStartDelay );
	m_edtStartDelay.SetWindowText( csStartDelay );
}
CString CDlgSettingTTL::ConvertIntToBin(int iMask)
{
	CString csBinInfo = _T("");
	CString csBit = _T("");
	for(int i=0;i<16;i++)
	{
		if( iMask >> i & 0x000000001 )
			csBit = "1";
		else
			csBit = "0";

		csBinInfo += csBit;
	}

	//
	csBinInfo.MakeReverse();

	return csBinInfo;
}
//
bool CDlgSettingTTL::SaveTTLData()
{
	bool bOK = true;

	//
	tagTTLParameter	m_IfUITTL;
	if( !GetDataFromUI( m_IfUITTL ) )
		bOK = false;

	//
	if( bOK )
		SaveDataToFile( m_IfUITTL );

	return bOK;
}
bool CDlgSettingTTL::GetDataFromUI(tagTTLParameter &UIData)
{
	bool bGetOK = true;

	tagTTLParameter m_UITTL;

	m_UITTL = m_TTLPamera;

	// 再按下按鈕的時候, 已經有變更參數了, 現在只要取得 Send Start Delay 和 Timeout
	
	CString csTimeout = _T("");
	m_edtTimeout.GetWindowText( csTimeout );
	m_UITTL.s_dTimeout	= atof( csTimeout ); 

	CString csSendStartDelay = _T("");
	m_edtStartDelay.GetWindowText( csSendStartDelay );
	m_UITTL.s_dStartDelay	= atof( csSendStartDelay );

	if( m_UITTL.s_dTimeout == 0 || m_UITTL.s_dStartDelay == 0 )
	{
		bGetOK = false;
		return bGetOK;
	}	

	//
	UIData = m_UITTL;

	return bGetOK;
}
void CDlgSettingTTL::SaveDataToFile(tagTTLParameter FileData)
{
	if( m_csTtlFile == "" )
		return;

	CString csFile = _T("");
	csFile = m.FilePath.InterfaceTtlPath + m_csTtlFile;

	// True / False setting.
	f.SaveSettingTrueFalse(csFile, "信號 Active High(1), Low(0)", "EOT",				FileData.s_iEOTAssertion);
	f.SaveSettingTrueFalse(csFile, "信號 Active High(1), Low(0)", "RDY",				FileData.s_iRDYAssertion);
	f.SaveSettingTrueFalse(csFile, "信號 Active High(1), Low(0)", "BIN",				FileData.s_iBinAssertion);	
	f.SaveSettingTrueFalse(csFile, "信號 Active High(1), Low(0)", "Level(0),Pulse(1)",	FileData.s_iRDYMode);	
	f.SaveSettingTrueFalse(csFile, "Bin 信號", "LINE(0), BCD(1)",						FileData.s_iLineMode);

	f.SaveSettingDouble(csFile, "Other", "Send Start Delay (sec)",						FileData.s_dStartDelay);
	f.SaveSettingDouble(csFile, "Other", "Timeout (sec)",								FileData.s_dTimeout);
	f.SaveSettingTrueFalse(csFile, "Other", "Power Mode(1)Tester(0)Handler",			FileData.s_iPowerMode);
/*
	// Wring.
	for(int i=0; i<4; i++)
	{
		CString cs;
		cs.Format("Site %d", i+1);
		f.SaveSettingHex(csFile, "Address (pin31:0x260, pin32:0x262, pin33:0x266, pin34:0x268)",
			cs, FileData.s_iSiteAddress[i]);
		f.SaveSettingBinary(csFile, "MASK (接線寫 1, 沒接寫 0, pin1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16)", 
			cs, FileData.s_iSiteMask[i]);
	}
*/
}
void CDlgSettingTTL::SetFile(CString csfile)
{
	m_csTtlFile = csfile;	
	m_wndFile.SetWindowText( m_csTtlFile );

	//
	LoadFile();

	//
	InitValue();
}

void CDlgSettingTTL::OnTtlFilename() 
{
	m_wndFile.ShowWindow( TRUE );
}

void CDlgSettingTTL::OnEstatic() 
{
	m_wndMaskGroup.ShowWindow( TRUE );
}
void CDlgSettingTTL::MInvalidate()
{
	m_btnEOT1.Invalidate();	
	m_btnEOT2.Invalidate();

	m_btnReady1.Invalidate();
	m_btnReady2.Invalidate();

	m_btnBinSignal1.Invalidate();
	m_btnBinSignal2.Invalidate();
	
	m_btnLevel.Invalidate();
	m_btnPulse.Invalidate();

	m_btnLine.Invalidate();
	m_btnBCD.Invalidate();

	m_btnTester.Invalidate();
	m_btnHandler.Invalidate();
}
void CDlgSettingTTL::ResetButton()
{
	if( m_TTLPamera.s_iEOTAssertion == 0 )
	{
		m_btnEOT1.SetCheck(1);
		m_btnEOT2.SetCheck(0);
	}
	else
	{
		m_btnEOT1.SetCheck(0);
		m_btnEOT2.SetCheck(1);
	}
	// EOT Signal 
	// s_iEOTAssertion is 0, It is Low Active

	if( m_TTLPamera.s_iRDYAssertion == 0)
	{
		m_btnReady1.SetCheck(1);
		m_btnReady2.SetCheck(0);
	}
	else
	{
		m_btnReady1.SetCheck(0);
		m_btnReady2.SetCheck(1);
	}
	// READY Signal
	// s_iRDYAssertion is 0,It is Low Acvite

	if( m_TTLPamera.s_iBinAssertion == 0)
	{
		m_btnBinSignal1.SetCheck(1);
		m_btnBinSignal2.SetCheck(0);
	}
	else
	{
		m_btnBinSignal1.SetCheck(0);
		m_btnBinSignal2.SetCheck(1);
	}
	// BIN Signal
	// s_iBinAssertion is 0, It is Low Active

	if( m_TTLPamera.s_iRDYMode == 0 )
	{
		m_btnLevel.SetCheck(1);
		m_btnPulse.SetCheck(0);
	}
	else
	{
		m_btnLevel.SetCheck(0);
		m_btnPulse.SetCheck(1);
	}
	// Signal From
	// TTLParm.s_iRDYMode: 0 is level, It it level. 1 is pulse

	if( m_TTLPamera.s_iLineMode == 0 )
	{
		m_btnLine.SetCheck(1);
		m_btnBCD.SetCheck(0);
	}
	else
	{
		m_btnLine.SetCheck(0);
		m_btnBCD.SetCheck(1);
	}
	// Output Line
	// TTLParm.s_iLineMode: 0 is Line to Line. 1 is BCD

	if( m_TTLPamera.s_iPowerMode == 1 )
	{
		m_btnTester.SetCheck(1);
		m_btnHandler.SetCheck(0);
	}
	else
	{
		m_btnTester.SetCheck(0);
		m_btnHandler.SetCheck(1);
	}
	// Power Mode. 1 = from Tester / 0 = from Handler.!
}
// eot
void CDlgSettingTTL::OnEot1() 
{	
//	EOT Signal
	m_TTLPamera.s_iEOTAssertion = 0;	
	ResetButton();
	MInvalidate();
}
void CDlgSettingTTL::OnEot2() 
{
//	EOT Signal
	m_TTLPamera.s_iEOTAssertion = 1;
	ResetButton();
	MInvalidate();
}
// ready
void CDlgSettingTTL::OnReady1() 
{
//	READY Signal	
	m_TTLPamera.s_iRDYAssertion = 0;
	ResetButton();
	MInvalidate();
}
void CDlgSettingTTL::OnReady2() 
{
//	READY Signal
	m_TTLPamera.s_iRDYAssertion = 1;
	ResetButton();
	MInvalidate();
}
// bin
void CDlgSettingTTL::OnBin1() 
{
//	BIN Signal
	m_TTLPamera.s_iBinAssertion = 0;
	ResetButton();
	MInvalidate();
}
void CDlgSettingTTL::OnBin2() 
{
//	BIN Signal
	m_TTLPamera.s_iBinAssertion = 1;
	ResetButton();
	MInvalidate();
}
// level
void CDlgSettingTTL::OnLevel1() 
{
//	Signal From
	m_TTLPamera.s_iRDYMode = 0; // Level
	ResetButton();
	MInvalidate();
}
void CDlgSettingTTL::OnLevel2() 
{
//	Signal From
	m_TTLPamera.s_iRDYMode = 1; // Ready
	ResetButton();
	MInvalidate();
}
// output
void CDlgSettingTTL::OnLine1() 
{
//	Output Line	
	m_TTLPamera.s_iLineMode  = 0; // Line
	ResetButton();
	MInvalidate();
}
void CDlgSettingTTL::OnLine2() 
{
//	Output Line
	m_TTLPamera.s_iLineMode  = 1; // BCD
	ResetButton();
	MInvalidate();
}
// power
void CDlgSettingTTL::OnTtlpwr0() 
{
	m_TTLPamera.s_iPowerMode = 1; // Power from Tester
	ResetButton();
	MInvalidate();
}
void CDlgSettingTTL::OnTtlpwr1() 
{
	m_TTLPamera.s_iPowerMode = 0; // Power from Handler
	ResetButton();
	MInvalidate();
}
