// CtrlVisionMatch.cpp: implementation of the CCtrlVisionMatch class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "deer.h"
#include "CtrlVisionMatch.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCtrlVisionMatch::CCtrlVisionMatch()
{
	lPatternHx = 0;
	lPatternWx = 0;

	//
	m_VisionCtrl.InitLib();

	//
	RectROI.top = 0;
	RectROI.left = 0;
	RectROI.bottom = 0;
	RectROI.right = 0;
}

CCtrlVisionMatch::~CCtrlVisionMatch()
{
	TRACE("~CCtrlVisionMatch\n");
}
//
void CCtrlVisionMatch::Message(CString csMsg)
{
	if( csMsg != "" )
	{
#ifdef _Demo
		AfxMessageBox( csMsg );
#endif
	}
}
bool CCtrlVisionMatch::SetTraining()
{
	// Training
	bool bTraingingOK = true;

	try
	{
/*
		BOOL bSuccess = m_VisionCtrl.pVBCreateNCCMatchColorModel( m_VisionCtrl.hHandle, 
			m_VisionCtrl.hHandleNCCTool );
*/
		BOOL bSuccess = m_VisionCtrl.pVBCreateNCCMatchColorModel( m_VisionCtrl.hHandleMatchPatten, 
			m_VisionCtrl.hHandleNCCTool );

		if( bSuccess )
		{
			bTraingingOK = true;
		}
		else
		{
			bTraingingOK = false;
		}
	}
	catch(...)
	{

	}
	return bTraingingOK;
}
// 1.0Ac
bool CCtrlVisionMatch::SetSubInspect(CString csInspect, CRect ROI, CString csSourceName, CString csSubName)
{
	bool bSaveInspectSubOK = true;
	try
	{		
		// Load Inspect Image, Grab.bmp
		CString cs = _T("");
		cs.Format("%s", csInspect );
		char *szBuf = new char[cs.GetLength()+1];
		memset(szBuf, 0, cs.GetLength());
		strcpy(szBuf, (LPCTSTR)cs);
		BOOL bSuccess = m_VisionCtrl.pLoadCImage(m_VisionCtrl.hHandleMatchSubInspect, szBuf);
		
		// Get Inspect Sub Image
		m_VisionCtrl.VBROI.Top		= ROI.top;
		m_VisionCtrl.VBROI.Left		= ROI.left;
		m_VisionCtrl.VBROI.Right	= ROI.right;
		m_VisionCtrl.VBROI.bottom	= ROI.bottom;
		BOOL bSubSuccess = m_VisionCtrl.pVBGetSubImage(m_VisionCtrl.hHandleMatchInspect, 
			m_VisionCtrl.hHandleMatchSubInspect, m_VisionCtrl.VBROI );
		CString csInspectSubPath = _T("");
		csInspectSubPath = csInspect;
		csInspectSubPath.Replace( csSourceName, "");
		csInspectSubPath = csInspectSubPath + csSubName;

		// 1.0Af
		// CCD
		char *szSaveBuf = new char[csInspectSubPath.GetLength()+1];
		memset(szSaveBuf, 0, csInspectSubPath.GetLength());
		strcpy(szSaveBuf, (LPCTSTR)csInspectSubPath);

		m_VisionCtrl.pSaveCImage( m_VisionCtrl.hHandleMatchInspect, szSaveBuf );

		if( bSubSuccess && bSuccess )
			bSaveInspectSubOK = true;
		else
			bSaveInspectSubOK = false;

		//
		delete []szBuf;
		delete []szSaveBuf;
	}
	catch(...)
	{

	}

	return bSaveInspectSubOK;
}
// 1.0Ac
bool CCtrlVisionMatch::SetSubPattern(CString csPattern, CRect ROI)
{
	// 載入比對的參照檔
	bool bSaveSubOK = true;
	try
	{
		m_VisionCtrl.VBROI.Top		= ROI.top;
		m_VisionCtrl.VBROI.Left		= ROI.left;
		m_VisionCtrl.VBROI.Right	= ROI.right;
		m_VisionCtrl.VBROI.bottom	= ROI.bottom;

		BOOL bSubSuccess = m_VisionCtrl.pVBGetSubImage(m_VisionCtrl.hHandleMatchPatten, 
			m_VisionCtrl.hHandle, m_VisionCtrl.VBROI );

		// 1.0Af
		// CCD
		char *szBuf = new char[csPattern.GetLength()+1];
		memset(szBuf, 0, csPattern.GetLength());
		strcpy(szBuf, (LPCTSTR)csPattern);

		m_VisionCtrl.pSaveCImage( m_VisionCtrl.hHandleMatchPatten, szBuf );

		if( bSubSuccess )
			bSaveSubOK = true;
		else
			bSaveSubOK = false;

		//
		delete []szBuf;
	}
	catch(...)
	{

	}

	return bSaveSubOK;
}
// 1.0Ac
bool CCtrlVisionMatch::SetPattern(CString csPattern)
{
	// 載入比對的參照檔
	bool bLoadOK = true;
	try
	{
		CString cs = _T("");
		cs.Format("%s", csPattern );
		char *szBuf = new char[cs.GetLength()+1];
		memset(szBuf, 0, cs.GetLength());
		strcpy(szBuf, (LPCTSTR)cs);
		BOOL bSuccess = m_VisionCtrl.pLoadCImage(m_VisionCtrl.hHandle, szBuf);

		lPatternHx = m_VisionCtrl.pVBGetWidth( m_VisionCtrl.hHandle );
		lPatternWx = m_VisionCtrl.pVBGetHeight( m_VisionCtrl.hHandle );

		if( bSuccess )
			bLoadOK = true;
		else
			bLoadOK = false;

		//
		delete []szBuf;
	}
	catch(...)
	{

	}

	return bLoadOK;
}
// 1.0Ac
// Remove this function. and build new one
/*
bool CCtrlVisionMatch::SetPattern(CString csPattern)
{
	// 載入比對的參照檔
	bool bLoadOK = true;

	try
	{
		CString cs = _T("");
		cs.Format("%s", csPattern );
		char *szBuf = new char[cs.GetLength()+1];
		memset(szBuf, 0, cs.GetLength());
		strcpy(szBuf, (LPCTSTR)cs);
		BOOL bSuccess = m_VisionCtrl.pLoadCImage(m_VisionCtrl.hHandle, szBuf);

		lPatternHx = m_VisionCtrl.pVBGetWidth( m_VisionCtrl.hHandle );
		lPatternWx = m_VisionCtrl.pVBGetHeight( m_VisionCtrl.hHandle );

		if( bSuccess )
			bLoadOK = true;
		else
			bLoadOK = false;

		//
		delete []szBuf;
	}
	catch(...)
	{

	}

	return bLoadOK;
}
*/
// 1.0Ac
bool CCtrlVisionMatch::SetMatch(double &dMatchResult)
{
	bool bMatch = true;
	try
	{
		// Match
		double dNCCLimit	= 0.0;
		double dMaxAng		= 60;
		double dMinAng		= -60;
		int iObjectNum		= 1;

		double dResult = 0.0;
		dResult = m_VisionCtrl.pVBFindNCCMatchColorModel( m_VisionCtrl.hHandleMatchInspect, 
			m_VisionCtrl.hHandleNCCTool, dNCCLimit, dMaxAng, dMinAng, true, iObjectNum );

		dMatchResult = 0.0;
		if( dResult > 0 )
		{
			CString csMsg = _T("");
			// 取出值
			BOOL bFindSuccess = m_VisionCtrl.pVBGetNCCMatchResults( m_VisionCtrl.hHandleNCCTool, 0, &m_VisionCtrl.NCCFind );
			if( bFindSuccess )
			{
				CString csFind;
				csFind.Format(" Width: %d, Height: %d, Cx: %5.2f, Cy: %5.2f, Score: %5.2f", 
					m_VisionCtrl.NCCFind.Width, 
					m_VisionCtrl.NCCFind.Height, 
					m_VisionCtrl.NCCFind.CX, 
					m_VisionCtrl.NCCFind.CY, 
					m_VisionCtrl.NCCFind.Score );
				dMatchResult = m_VisionCtrl.NCCFind.Score;
			}
		}
		else
		{
			CString csMsg = _T("");
			csMsg.Format("Fail");
//			AfxMessageBox( csMsg );
		}
	}
	catch(...)
	{

	}
	
	//
	return bMatch;
}
double CCtrlVisionMatch::MatchCheck(int iUserID, CString csPatternPath, CString csGrabPath,
		CString csSourceName, CString csSubName, CRect rect )
{
	double m_MatchResultSource = 0.0;

	// Set Pattern ( 選擇目前的設定檔 )
	bool bPattern = SetPattern(csPatternPath);
	if(!bPattern)
		Message("Set Pattern Fail.!");

	// Set Sub ( 選擇目前的設定檔, 將目前設定檔的圖片存成小圖 )
	CString csSubPath = csPatternPath;
	csSubPath.Replace( csSourceName, "");
	csSubPath = csSubPath + csSubName;
	bool bSubPatterm = SetSubPattern(csSubPath, rect);
	if(!bSubPatterm)
		Message("Set Sub File.!");

	// Training ( 設定基底 )
	bool bTraining = SetTraining();
	if(!bTraining)
		Message("Set Training Fail.!");
	
	// Set Inspect Sub (將最後一次取像的圖檔, 存成小圖)
	CString csSubInspectPath = _T("");
	csSubInspectPath = csGrabPath;
	bool bSubInspect = SetSubInspect( csSubInspectPath, rect, csSourceName, csSubName);
	if(!bSubInspect)
		Message("Set Sub Inspect.!");

	// Match ( 比對 )
	double dResult = 0.0;
	bool bMatch = SetMatch(dResult);
	if(!bMatch)
		Message("Set Match Fail.!");

	//
	m_MatchResultSource = dResult;

	return m_MatchResultSource;
}