// FileCtrl.h: interface for the CFileCtrl class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FILECTRL_H__5B3E6123_3B2D_47AD_AE61_147126F85AAE__INCLUDED_)
#define AFX_FILECTRL_H__5B3E6123_3B2D_47AD_AE61_147126F85AAE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CFileCtrl  
{
public:
	CFileCtrl();
	virtual ~CFileCtrl();

	//
	void DoCopyFolderFile(CString csSourceFolder, CString csDestFolder, CString csSubFileName );
	void DoDeleteFolderFile(CString csSoureFolder, CString csSubFileName );
	void DoDeleteFolder(CString csSourceFolder);

	//
	bool IsFileExist(CString csSourceFolder, CString csSubFileName);
};

#endif // !defined(AFX_FILECTRL_H__5B3E6123_3B2D_47AD_AE61_147126F85AAE__INCLUDED_)
