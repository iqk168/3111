// CtrlVision.h: interface for the CCtrlVision class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CTRLVISION_H__544469B7_05BD_4E5E_8007_0F926F2EFD0C__INCLUDED_)
#define AFX_CTRLVISION_H__544469B7_05BD_4E5E_8007_0F926F2EFD0C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "multicam32.h"
#include "Easy.h"
#include "EMatch.h"
#include "EImage.h"

static bool m_bVisionInitial;
static bool m_bVisionStart;

class CCtrlVision  
{
public:

	void SetID(int BoardID, int ChannelID);
	void SetMatchPattern(EROIC24 &image);
	void Save(EROIC24 *image, CString file, CString BmpFile);
	void Load(CString file);
	void Initial();
	EImageC24 *GetPatternImage();
	EROIC24 &GetPatternROI();
	EImageC24 *GetGrabImage();
	EROIC24 GetGrabROI();
	void SetMatchPattern(CString file, CRect rect, double MinScore = 0.5);
	
	typedef struct tagVector{
		CString file;
		unsigned char RowR[700];
		unsigned char RowG[700];
		unsigned char RowB[700];
		double MatchResult;
	} tagVector;
	
	void SaveGrabFile(CString file);
	void SetProjectionPattern(CString file = "PASS.bmp", long level = 5);
	BOOL Projection(CString file);
	BOOL Projection();

	enum tagReturnCode{enGrabFail, enPass, enProjectionFail, enMatchFail};

	// 將取像的整個圖與原圖比較，回傳位置偏差值
	CPoint CheckAlignment(EImageC24 *pSourceImage);
	// 比對 Pattern 的 相似度
	void MatchCheck(EImageC24 *pSourceImage);
	void GrabMatch(int site);
	bool Grab();
	void GrabDone();
	void LiveStop();
	bool Live();

	CCtrlVision();
	virtual ~CCtrlVision();

	long m_State;
	
	enum enState{enNone, enGrab, enLive};
	EMatch MatchObj;
	
	struct tagMatch{
		double Score;
		bool GrabOK;
		EImageC24 PatternImageColor;	// Load from file
		EROIC24 PatternROIColor;		// convert from PatternImageColor,  尺寸為設定的大小
		EROIC24 PatternROI_Original;	// convert from PatternImageColor, 尺寸為原大小
		EROIC24 SourceROI;
		CRect rect;
		double MinScore;
		bool Pass;
		CString MatchResult;
		CString File;
	} m_Match;
	
	struct tagProjection{
		tagVector Source;
		tagVector Now;
		EImageC24 PatternImage;
		long level;
	} m_Projection;
		
public:
	bool GetMatchResult();
	ECHANDLE hChannel0;

protected:
	int m_iBoardID;
	int m_iChannelID;

	BOOL CheckProjection(tagVector &source, tagVector &target);
	void CountProjection(tagVector &Vect, EImageC24 *pImage);

	EImageC24 *m_pGrabImage;
	EROIC24 m_GrabImage;

	ECHANDLE hSurface;
	INT32	ImageSizeX, ImageSizeY;

public:
	
};

#endif // !defined(AFX_CTRLVISION_H__544469B7_05BD_4E5E_8007_0F926F2EFD0C__INCLUDED_)
