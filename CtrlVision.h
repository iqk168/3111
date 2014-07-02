// CtrlVision.h: interface for the CCtrlVision class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CTRLVISION_H__C18B56E6_E8EB_4B79_A731_17BA8A94EBE5__INCLUDED_)
#define AFX_CTRLVISION_H__C18B56E6_E8EB_4B79_A731_17BA8A94EBE5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


//
#include "CameraDS.h"

// 相機最大數量
#define _MaxCam			10	// 設大一點, 避免被人插入太多 Cam, 造成當機..
#define _CAMERA_WIDTH	640
#define _CAMERA_HEIGHT	480

class CCtrlVision  
{
public:
	CCtrlVision();
	virtual ~CCtrlVision();

	// Caram List
	CArray <CString, CString> m_CaramList;					// 儲存相機列表的 Array
	bool m_bIsCameraReady[_MaxCam];							// 用來儲存是否曾經被初始化過
	int m_iCameraID[_MaxCam];
	CCameraDS m_Camera[_MaxCam];							// 相機的 class ( DirectShow )
	int m_iCameraOpenCount;									// 目前開到第幾支相機
	bool m_bCameraLive;										// 是否在 Live
	bool m_MediaControlUse[_MaxCam];

public:
	// Function
	int UpdateCameraList();									// 取得目前已經接上的 Camera 列表
	void GetCameraList(CArray <CString, CString> &array );	// 讓外部可以取得列表

	//
	bool Open(int iCameraID);
	int m_iCameraUseID;
	bool CameraInitial(int iUserID,int iCameraID);

public:
	char *m_pCapturImageData[_MaxCam];						// 儲存相機資料

	char *m_CaptureFrame;
	bool CameraGrab(int iUserID);							// 取像
	bool CameraGrabSave(int iUserID, CString csFilePath);	// 取像而且儲存

public:

	bool SaveImage(char* szPathName, void* lpBits, int w, int h);
	HBITMAP *m_pBitmap;
	HBITMAP* GetBitmap();
	void Draw(HDC hDC,CRect rect,char* pBuffer);
	void DrawWindow(int iUserID,LPVOID hWndShowPage,int iWindowID);
	
	// GDIPlus
	/*
	int GetEncoderClsid(const WCHAR* format, CLSID* pClsid);
	Status SaveFile(Bitmap* pImage, const wchar_t* pFileName);
	void ConvertFile(CString csSourceBmp, CString csDestionJpg);

	CString GetStatusValue(Status status);
	void VisionMessage(CString csMsg);
	*/
};

#endif // !defined(AFX_CTRLVISION_H__C18B56E6_E8EB_4B79_A731_17BA8A94EBE5__INCLUDED_)
