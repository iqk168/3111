// MailCtrl.cpp: implementation of the CMailCtrl class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "deer.h"
#include "MailCtrl.h"

//
#include "CSmtp.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMailCtrl::CMailCtrl()
{
	hProcess = NULL;

	//
	CmdSet.RemoveAll();
}

CMailCtrl::~CMailCtrl()
{
	// 1.0Ad 
	// Remove this function
	// WaitForSingleObject(threadEvent, 800);

	TRACE("~CMailCtrl 1\n");
	Close();
	TRACE("~CMailCtrl 2\n");
}

UINT CMailCtrl::MailCtrlThread(LPVOID p)
{
	CMailCtrl *dr = (CMailCtrl *)p;

	int err = 0;
	while(1)
	{
		if(dr->CmdSet.GetSize() > 0)
		{
			if(dr->ExecuteCmd(dr->CmdSet.GetAt(0).csEventTime, dr->CmdSet.GetAt(0).csCode, dr->CmdSet.GetAt(0).csDesc))
			{
				err = 0;
				dr->CmdSet.RemoveAt(0);
			}
			else
				err++;

			if(err > 3)
				dr->CmdSet.RemoveAt(0);

			//
			if( !m.Info.bRunning )
				dr->CmdSet.RemoveAt(0);
		}
		else
		{
			// Wait Command
		}

		// Make sure program close. Thread will be close
		if( !m.Info.bRunning )
			break;

		Sleep(1);
	}

	dr->threadEvent.PulseEvent();
	AfxEndThread(0);
	return 0;
}
void CMailCtrl::InitMail()
{
	CWinThread *pWindThread = NULL;
	pWindThread = AfxBeginThread(MailCtrlThread, this);

	if(pWindThread)
		hProcess = pWindThread->m_hThread;
}
void CMailCtrl::Close()
{
	MSG				msg;
	LARGE_INTEGER	start, end, freq;
	DWORD			nThreadExitCode = 0;
	BOOL			bSuccess = FALSE;

	::QueryPerformanceFrequency(&freq);
	::QueryPerformanceCounter(&start);
	if(hProcess != NULL)
	{
	do
	{
		bSuccess = GetExitCodeThread(hProcess, &nThreadExitCode);
		::QueryPerformanceCounter(&end);

		if(::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			::TranslateMessage(&msg);
			::DispatchMessage(&msg);
		}
	}while(bSuccess && nThreadExitCode == STILL_ACTIVE && (end.QuadPart - start.QuadPart) / freq.QuadPart < 10);  //10秒表示等10s, 可依據需求修改
	}
}
void CMailCtrl::AddCmd(CString csTime, CString csCode, CString csDesc)
{
	tagMailCmd Cmd;
	Cmd.csEventTime		= csTime;
	Cmd.csCode			= csCode;
	Cmd.csDesc			= csDesc;

	CmdSet.Add( Cmd );
}
bool CMailCtrl::ExecuteCmd(CString csTime, CString csCode, CString csDesc)
{
	bool bSendOK = true;
	bool bError = false;

	CString csContent1 = _T("");
	CString csContent2 = _T("");

	csContent1.Format("%s - Handler Error Code: %s", csTime, csCode );
	csContent2.Format("Error Desc: %s", csDesc );

	try
	{
		CString csMail1 = _T("");
		csMail1 = m_MailSetting.csMailTo1;
		csMail1.TrimLeft();
		csMail1.TrimRight();

		if( csMail1 != "" )
		{			
			// 指定 SMTP Server 
			mail.SetSMTPServer( m_MailSetting.csSMTPServer, m_MailSetting.iSMTPPort );
			
			// 指定 SMTP 登入資訊 
			mail.SetLogin(		m_MailSetting.csSMTPUserName );
			mail.SetPassword(	m_MailSetting.csSMTPPassword );
			mail.SetSenderName( m_MailSetting.csShowName );
			
			// 寄發 Mail 資訊
			mail.SetSenderMail( m_MailSetting.csMailFrom );
			mail.SetReplyTo(	m_MailSetting.csMailTo1 );
			
			// Mail 寄件主旨
			mail.SetSubject(	m_MailSetting.csMailSubject );
			mail.AddRecipient(	m_MailSetting.csMailTo1 );
			mail.SetXPriority(XPRIORITY_NORMAL);
			
			mail.SetXMailer("The Bat! (v3.02) Professional");
			
			mail.DelMsgLines();
			mail.AddMsgLine( "Hi User" );
			mail.AddMsgLine( "" );
			mail.AddMsgLine( csContent1 );
			mail.AddMsgLine( csContent2 );
			mail.AddMsgLine("...");
			
			//
			mail.Send();
		}

		CString csMail2 = _T("");
		csMail2 = m_MailSetting.csMailTo2;
		csMail2.TrimLeft();
		csMail2.TrimRight();

		if( csMail2 != "" )
		{			
			////////////////////////////////////////////////////////////////////////////////////////
			//
			// 指定 SMTP Server 
			mail2.SetSMTPServer( m_MailSetting.csSMTPServer, m_MailSetting.iSMTPPort );
			
			// 指定 SMTP 登入資訊 
			mail2.SetLogin(			m_MailSetting.csSMTPUserName );
			mail2.SetPassword(		m_MailSetting.csSMTPPassword );
			mail2.SetSenderName(	m_MailSetting.csShowName );
			
			// 寄發 Mail 資訊
			mail2.SetSenderMail(	m_MailSetting.csMailFrom );
			mail2.SetReplyTo(		m_MailSetting.csMailTo2 );
			
			// Mail 寄件主旨
			mail2.SetSubject(		m_MailSetting.csMailSubject );
			mail2.AddRecipient(		m_MailSetting.csMailTo2 );
			mail2.SetXPriority(XPRIORITY_NORMAL);
			
			mail2.SetXMailer("The Bat! (v3.02) Professional");
			
			mail2.DelMsgLines();
			mail2.AddMsgLine( "Hi User" );
			mail2.AddMsgLine( "" );
			mail2.AddMsgLine( csContent1 );
			mail2.AddMsgLine( csContent2 );
			mail2.AddMsgLine("...");
			
			//
			mail2.Send();
		}
	}
	catch(ECSmtp e)
	{
		ErrorLog( e.GetErrorText().c_str() );
		bError = true;
		bSendOK = false;
	}

	if(!bError)
	{
	}	// OK. Mail was send.!
	else
	{
		ErrorLog("Mail was not send success.!");
	}

	return bSendOK;
}
static CMutex MutexMailLog;
void CMailCtrl::ErrorLog(CString csMsg)
{
	CSingleLock Lock(&MutexMailLog);
	Lock.Lock();

	CString csLog = _T("");
	csLog.Format("%s", csMsg);
	
	CString cs = _T("");
	CString cstime;
	CTime time = CTime::GetCurrentTime();
	cs.Format("%s, %s\r\n", time.Format("%m/%d %H:%M:%S"), csLog);
	cstime.Format("%s",time.Format("%y-%m-%d"));
	
	CFile file;

	if( file.Open(".\\Log\\"+cstime+"_Mail.txt", CFile::modeCreate | CFile::modeWrite
		| CFile::modeNoTruncate | CFile::shareDenyNone, NULL) )
	{		
		file.SeekToEnd();		
		file.Write(cs.GetBuffer(0), cs.GetLength());
		file.Close();
	}
	
	Lock.Unlock();
}
void CMailCtrl::SetMailSetting(tagMailSetting MailSetting)
{
	m_MailSetting = MailSetting;
}

