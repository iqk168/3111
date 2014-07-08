// SocketVision.h: interface for the CSocketVision class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SOCKETVISION_H__382B1AAF_D173_4875_94A1_0EBBA9254063__INCLUDED_)
#define AFX_SOCKETVISION_H__382B1AAF_D173_4875_94A1_0EBBA9254063__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//
#include "CameraDS.h"

//
#include "Easy.h"
#include "EMatch.h"
#include "EImage.h"

// 相機最大數量
#define _MaxCam			10	// 設大一點, 避免被人插入太多 Cam, 造成當機..
#define _CAMERA_WIDTH	640
#define _CAMERA_HEIGHT	480

class CSocketVision  
{
public:
	CSocketVision();
	virtual ~CSocketVision();

	//
	struct tagMatch{
		double Score;
		bool GrabOK;
		EImageC24 PatternImageColor;
		EROIC24 PatternROIColor;
		bool bLearn;
		EROIC24 SourceROI;
		CRect rect;
		double MinScore;
		bool Pass;
		CString MatchResult;
		CString File;
		bool IsGrabOK;
	} m_Match[_MaxCam];

	// Caram List
	CArray <CString, CString> m_CaramList;					// 儲存相機列表的 Array
	bool m_bIsCameraReady[_MaxCam];							// 用來儲存是否曾經被初始化過
	int m_iCameraID[_MaxCam];
	CCameraDS m_Camera[_MaxCam];							// 相機的 class ( DirectShow )
	int m_iCameraOpenCount;									// 目前開到第幾支相機
	bool m_bCameraLive;										// 是否在 Live
	bool m_MediaControlUse[_MaxCam];

	char *m_pCapturImageData[_MaxCam];						// 儲存相機資料

	// File Path
	CString m_csPatternPath;								// 設定檔案路徑
	CString m_csInfoPath;
	void SetPath(CString PatternPath, CString csInfoPath );

	// Function
	int UpdateCameraList();									// 取得目前已經接上的 Camera 列表
	void GetCameraList(CArray <CString, CString> &array );	// 讓外部可以取得列表
	int m_iCameraUseID;
	bool CameraInitial(int iUserID,int iCameraID);			// 對硬體初始化
	bool Open(int iCameraID);
	
	//
	char *m_CaptureFrame;
	char* GatImagePtr(int iID,char * pImageData);
	bool CameraGrab(int iUserID);
	void DrawWindow(int iUserID,LPVOID hWndShowPage,int iWindowID);

	//IplImage m_CaptureFrame;
	EImageC24 SourceImage[_MaxCam];

	// 取得影像..
	EImageC24 GetGrabImage(int iUserID);

	//
	EROIC24 SourceROI;

	//
	double GrabMatch(int site);
	void MatchCheck(tagMatch *pMatch,EImageC24 *pSourceImage);

	//
	EMatch MatchObj;

	//
	void SetMatchPattern(int iUser,CString FilePath, CRect rect, double MinScore);

	//
	bool GetMatchGrabOK(int iUserID);
};

#endif // !defined(AFX_SOCKETVISION_H__382B1AAF_D173_4875_94A1_0EBBA9254063__INCLUDED_)
