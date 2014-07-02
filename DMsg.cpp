// DMsg.cpp: implementation of the CDMsg class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "deer.h"
#include "DMsg.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDMsg::CDMsg()
{
	m_DMsg.RemoveAll();
	m_ReportPath = _T("");
}
void CDMsg::SetReportPath(CString csFilePath)
{
	m_ReportPath = csFilePath;
}
void CDMsg::DMsgClear()
{
	if( m.Setting.m_bEnableProgramInitialStart == 1 )
	{
		theApp.m_DlgProgramStartInitial->m_listShowCtrl.InsertColumn(0, "Contact",	LVCFMT_LEFT, 800);
		theApp.m_DlgProgramStartInitial->m_btnOK.EnableWindow(FALSE);
	}
}
void CDMsg::DMsgEnd()
{
#ifdef _Demo
	if( m.Setting.m_bEnableProgramInitialStart == 1 )
		theApp.m_DlgProgramStartInitial->m_bPass = true;
#endif

	if( m.Setting.m_bEnableProgramInitialStart == 1 )
	{
		theApp.m_DlgProgramStartInitial->m_btnOK.EnableWindow(TRUE);
		if( theApp.m_DlgProgramStartInitial->m_bPass == true )
			theApp.m_DlgProgramStartInitial->ShowWindow(FALSE);	// Initial Pass
		else
		{
			theApp.m_DlgProgramStartInitial->ShowWindow(TRUE);
			theApp.m_DlgProgramStartInitial->UpdateWindow();
		}
	}
}
static CMutex MutexDMsg;
void CDMsg::DMsg(CString csMsg, bool bPass)
{
	if( m.Setting.m_bEnableProgramInitialStart == 1 )
	{
		CSingleLock Lock(&MutexDMsg);
		Lock.Lock(1);
		if( Lock.IsLocked() )
		{			
			csMsg.TrimLeft();
			csMsg.TrimRight();
			if( theApp.m_DlgProgramStartInitial != NULL )
			{
				// Time
				CTime time = CTime::GetCurrentTime();
				CString csTime = _T("");
				csTime.Format("%s", time.Format("%m:%d:%H:%M:%S"));

				// CListBox
				CString DeMsg = _T("");
				DeMsg.Format("%s, %s",csTime, csMsg);
			
				// CListCtrl
				int iItemCount = theApp.m_DlgProgramStartInitial->m_listShowCtrl.GetItemCount();
				CString csItem = _T("");
				theApp.m_DlgProgramStartInitial->m_listShowCtrl.InsertItem(iItemCount, csItem);
				theApp.m_DlgProgramStartInitial->m_listShowCtrl.SetItemText(iItemCount, 0, DeMsg);
				if(bPass)
					theApp.m_DlgProgramStartInitial->m_listShowCtrl.SetRowColor(ST_GREEN, iItemCount);
				else
				{
					theApp.m_DlgProgramStartInitial->m_bPass = false;
					theApp.m_DlgProgramStartInitial->m_listShowCtrl.SetRowColor(ST_RED, iItemCount);
				}
				f.ThreadWait();
			}
			Lock.Unlock();
		}// Islocked		
	}	
}
void CDMsg::ExportDMsgReport()
{
	if( m_ReportPath == "" )
		return;
}
CDMsg::~CDMsg()
{
	m_DMsg.RemoveAll();
}
