// CtrlVisionMatch.h: interface for the CCtrlVisionMatch class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CTRLVISIONMATCH_H__AA5BC3E1_FA5D_403E_B219_BCCDFC2C980C__INCLUDED_)
#define AFX_CTRLVISIONMATCH_H__AA5BC3E1_FA5D_403E_B219_BCCDFC2C980C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "CtrlVisionAlignment.h"

class CCtrlVisionMatch  
{
public:
	CCtrlVisionMatch();
	virtual ~CCtrlVisionMatch();

public:
	CCtrlVisionAlignment	m_VisionCtrl;

public:
	// Debug
	void Message(CString csMsg = _T("") );

	// Info
	long lPatternHx;
	long lPatternWx;
	//
	CRect RectROI;
	bool SetPattern(CString csPattern);												// 載入比對的參照檔
	bool SetSubPattern(CString csPattern, CRect ROI);								// 載入比對的參照檔, 將參照檔存成小圖
	bool SetSubInspect(CString csInspect, CRect ROI,
		CString csSourceName, CString csSubName);									// 載入取像的檔案, 將取像檔存成小圖
	bool SetTraining();																// 建立比對模型
	bool SetMatch(double &dMatchResult);											// 比對
	double MatchCheck(int iUserID, CString csPatternPath, CString csGrabPath,
		CString csSourceName, CString csSubName, CRect rect /*ROI*/ );				// 比對
};

#endif // !defined(AFX_CTRLVISIONMATCH_H__AA5BC3E1_FA5D_403E_B219_BCCDFC2C980C__INCLUDED_)
