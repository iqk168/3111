// MailCtrl.h: interface for the CMailCtrl class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAILCTRL_H__B7BAEF37_81ED_4059_915F_5113612936A0__INCLUDED_)
#define AFX_MAILCTRL_H__B7BAEF37_81ED_4059_915F_5113612936A0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CSmtp.h"

class CMailCtrl  
{
public:
	CMailCtrl();
	virtual ~CMailCtrl();
	
	void InitMail();

	CArray <tagMailCmd, tagMailCmd> CmdSet;
	bool ExecuteCmd(CString csTime, CString csCode, CString csDesc);
	tagMailSetting	m_MailSetting;
	void SetMailSetting(tagMailSetting MailSetting);
	void AddCmd(CString csTime, CString csCode, CString csDesc);

	CEvent threadEvent;

	CSmtp mail;
	CSmtp mail2;
	static UINT MailCtrlThread(LPVOID p);

	//
	void ErrorLog(CString csMsg);

	void Close();

private:
	HANDLE hProcess;
};

#endif // !defined(AFX_MAILCTRL_H__B7BAEF37_81ED_4059_915F_5113612936A0__INCLUDED_)
