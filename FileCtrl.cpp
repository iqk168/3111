// FileCtrl.cpp: implementation of the CFileCtrl class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "deer.h"
#include "FileCtrl.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CFileCtrl::CFileCtrl()
{

}

CFileCtrl::~CFileCtrl()
{

}
bool CFileCtrl::IsFileExist(CString csSoureFolder, CString csSubFileName)
{
	bool bFileExist = false;

	csSubFileName = "*" + csSubFileName;
	csSoureFolder.TrimLeft();
	csSoureFolder.TrimRight();
	csSoureFolder = csSoureFolder + "\\";
				
	CFileFind find;
	CString csFile = csSoureFolder;
	BOOL bResult = find.FindFile( csFile + csSubFileName );	
	if(bResult)
		bFileExist = true;
	else
		bFileExist = false;

	return bFileExist;
}
//
void CFileCtrl::DoDeleteFolderFile(CString csSoureFolder, CString csSubFileName )
{
	csSubFileName = "*" + csSubFileName;
	csSoureFolder.TrimLeft();
	csSoureFolder.TrimRight();
	csSoureFolder = csSoureFolder + "\\";
				
	CFileFind find;
	CString csFile = csSoureFolder;
	BOOL bResult = find.FindFile( csFile + csSubFileName );	
	CString file = _T("");
	while(bResult)
	{
		bResult = find.FindNextFile();
		file = find.GetFileName();	// Get File Name..

		::DeleteFile( csSoureFolder + file );
	}
}
void CFileCtrl::DoDeleteFolder(CString csSourceFolder)
{
	csSourceFolder.TrimLeft();
	csSourceFolder.TrimRight();
	::RemoveDirectory( csSourceFolder );
}
void CFileCtrl::DoCopyFolderFile(CString csSourceFolder, CString csDestFolder, CString csSubFileName )
{
	CFileFind find;	
	csSourceFolder.TrimLeft();
	csSourceFolder.TrimRight();
	csSourceFolder = csSourceFolder + "\\";
	csDestFolder.TrimLeft();
	csDestFolder.TrimLeft();
	csDestFolder = csDestFolder + "\\";
	//
	csSubFileName = "*" + csSubFileName;

	CString csFile = csSourceFolder;
	CString csFinalFile = _T("");
	csFinalFile = csFile + csSubFileName;
	BOOL bResult = find.FindFile( csFinalFile );	
	CString file = _T("");
	while(bResult)
	{
		bResult = find.FindNextFile();
		file = find.GetFileName();	// Get File Name
		::CopyFile( csSourceFolder + file, csDestFolder + file, FALSE );
	}
}
