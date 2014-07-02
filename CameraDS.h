//////////////////////////////////////////////////////////////////////
// Video Capture using DirectShow
// Author: Shiqi Yu (shiqi.yu@gmail.com)

//////////////////////////////////////////////////////////////////////

#ifndef CCAMERA_H
#define CCAMERA_H

#define WIN32_LEAN_AND_MEAN

#include <atlbase.h>

#include "qedit.h"
#include "dshow.h"

#include <windows.h>
#pragma comment(lib,"Strmiids.lib") 
#define MYFREEMEDIATYPE(mt)	{if ((mt).cbFormat != 0)		\
					{CoTaskMemFree((PVOID)(mt).pbFormat);	\
					(mt).cbFormat = 0;						\
					(mt).pbFormat = NULL;					\
				}											\
				if ((mt).pUnk != NULL)						\
				{											\
					(mt).pUnk->Release();					\
					(mt).pUnk = NULL;						\
				}}		


struct lImageStruct
{
	int width;
	int height;
	char * imageData;
};

struct ImageSize
{
	int width;
	int height;
};

class CCameraDS  
{
public:

	CCameraDS();
	virtual ~CCameraDS();

	//
	bool OpenCamera(int nCamID, bool bDisplayProperties = true, int nWidth = 320, int nHeight = 240);

	//
	void CloseCamera();

	//
	static int CameraCount(); 
	
	//
	static int CameraName(int nCamID, char* sName, int nBufferSize);

	//
	int GetWidth(){return m_nWidth;} 

	//
	int GetHeight(){return m_nHeight;}

	//
	char* QueryFrame(bool &cameraOK);
	void SetMediaControl(bool bRun);

	//
	void CCameraDS::ImageFlip(char *pImageBuffer);

	// IplImage *m_pFrame;
	char *m_pImageData;

private:

	bool m_bConnected, m_bLock, m_bChanged;
	
	int m_nWidth, m_nHeight;

	long m_nBufferSize;



	//lImageStruct *m_pFrame;
	CComPtr<IGraphBuilder> m_pGraph;

	CComPtr<ISampleGrabber> m_pSampleGrabber;

	CComPtr<IMediaControl> m_pMediaControl;

	CComPtr<IMediaEvent> m_pMediaEvent;

	CComPtr<IBaseFilter> m_pSampleGrabberFilter;
	CComPtr<IBaseFilter> m_pDeviceFilter;
	CComPtr<IBaseFilter> m_pNullFilter;

	CComPtr<IPin> m_pGrabberInput;
	CComPtr<IPin> m_pGrabberOutput;
	CComPtr<IPin> m_pCameraOutput;
	CComPtr<IPin> m_pNullInputPin;

	bool BindFilter(int nCamIDX, IBaseFilter **pFilter);

	void SetCrossBar();

	IMediaEventEx *m_pMediaEventEx;
};

#endif 
