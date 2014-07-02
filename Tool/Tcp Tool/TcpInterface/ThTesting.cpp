// ThTesting.cpp : implementation file
//

#include "stdafx.h"
#include "TcpInterface.h"
#include "TcpInterfaceDlg.h"
#include "ThTesting.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CThTesting

IMPLEMENT_DYNCREATE(CThTesting, CWinThread)

CThTesting::CThTesting()
{
}

CThTesting::CThTesting(int iID)
{
	m_iID = iID;
}

CThTesting::~CThTesting()
{
}

BOOL CThTesting::InitInstance()
{
	if(!InitialConnect())
		return FALSE;

	return TRUE;
}

int CThTesting::ExitInstance()
{
	m_Interface.Close();
	
	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(CThTesting, CWinThread)
	//{{AFX_MSG_MAP(CThTesting)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CThTesting message handlers

int CThTesting::Run() 
{
	COLORREF color;
	CString cs, csSendText;
	CString GetTelegram = _T("");
	CTcpInterfaceDlg *p = (CTcpInterfaceDlg *) theApp.m_pMainWnd;

	int i=0, counter = 0;
	while(m_Interface.IsOpen())
	{
		GetTelegram = _T("");
		bool ret = m_Interface.GetString(GetTelegram.GetBuffer(GetTelegram.GetLength()));
		
		cs.Format("1:%3d R:%s\n", m_iID+1, GetTelegram);
		ShowMessage(cs);

		if(ret)
		{
			Sleep(100);

			if (GetTelegram.Find("C1", 0) != -1)
			{
				csSendText.Format("@OK;12345,8#");
				ret = m_Interface.WriteString(csSendText.GetBuffer(csSendText.GetLength()), csSendText.GetLength());
				if (ret)
				{
					if (p->GetSafeHwnd() != NULL) p->DisplayErrorCode(m_iID+1, csSendText, color);

					cs.Format("2:%3d S:%s\n", m_iID+1, csSendText);
					ShowMessage(cs);
				}

				Sleep(100);

				int iResult = (int) ((rand() % 20) - 10); // -10 ~ 9
				if (iResult == 0) ++iResult;			  // ¤£¬° 0.

				csSendText.Format("@E%d,12345;%d,7#", iResult>0 ? 1 : 2, iResult);
				ret = m_Interface.WriteString(csSendText.GetBuffer(csSendText.GetLength()), csSendText.GetLength());
				if (ret)
				{
					CString str;
					str.Format("%d", iResult);
					if (p->GetSafeHwnd() != NULL) p->DisplayErrorCode(m_iID+1, str, color);

					cs.Format("3:%3d S:%s\n", m_iID+1, csSendText);
					ShowMessage(cs);
				}

				GetTelegram = _T("");
				ret = m_Interface.GetString(GetTelegram.GetBuffer(GetTelegram.GetLength()));
				
				cs.Format("4:%3d R:%s\n", m_iID+1, GetTelegram);
				ShowMessage(cs);
			}
			else if (GetTelegram.Find("C2", 0) != -1) 
			{
				csSendText.Format("@OK;6MULTI,9#");
				ret = m_Interface.WriteString(csSendText.GetBuffer(csSendText.GetLength()), csSendText.GetLength());
				if (ret)
				{
					if (p->GetSafeHwnd() != NULL) p->DisplayErrorCode(m_iID+1, csSendText, color);

					cs.Format("5:%3d S:%s\n", m_iID+1, csSendText);
					ShowMessage(cs);
				}
			}
		}

		Sleep(100);
	}
	
	return CWinThread::Run();
}



bool CThTesting::InitialConnect()
{
	if(!m_Interface.IsOpen())
	{

		CTcpInterfaceDlg *p = (CTcpInterfaceDlg *) theApp.m_pMainWnd;

		//CString IpAddress = "192.168.10.201";
		//CString IpAddress = "127.0.0.1";
		//CString IpAddress = "192.168.206.10";

		CString IpAddress = p->getIpAddress();

		int m_iPort = 7211 + m_iID;

		if(!m_Interface.Open(IpAddress.GetBuffer(IpAddress.GetLength()), m_iPort))
			return FALSE;

// 		CString cs, csSendText;
// 		csSendText.Format("((SLT2_START=S-305, %d))", m_iID+1);
// 
// 
// 		m_Interface.WriteString(csSendText.GetBuffer(csSendText.GetLength()), csSendText.GetLength());
// 
// 		cs.Format("%3d S:%s", m_iID+1, csSendText);
// 		if(p->GetSafeHwnd() != NULL) p->AddString(cs.GetBuffer(cs.GetLength()));
	}
	else
	{
		m_Interface.Close();
		return false;
	}

	return true;
}

void CThTesting::ShowMessage(CString cs)
{
	CTcpInterfaceDlg *p = (CTcpInterfaceDlg *) theApp.m_pMainWnd;

	if(p->GetSafeHwnd() != NULL) p->AddString(cs.GetBuffer(cs.GetLength()));
}
