// CtrlVision.cpp: implementation of the CCtrlVision class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "deer.h"
#include "CtrlVision.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCtrlVision::CCtrlVision()
{
	m_iCameraUseID = 0;

	m_pBitmap = NULL;

	for(int i=0;i<_MaxCam;i++)
	{
		m_bIsCameraReady[i] = false;
		m_pCapturImageData[i] = NULL;
	}

	m_iCameraOpenCount = 0;


}

CCtrlVision::~CCtrlVision()
{
	// 1.0Af
	// CameraDS Memory leak
	for(int i=0;i<_MaxCam;i++)
		free(m_pCapturImageData[i]);

	TRACE("~CCtrlVision\n");
}

///////////////////////////////////////////////////////////////////////////
void CCtrlVision::GetCameraList(CArray <CString, CString> &array )
{
	array.Copy( m_CaramList );
}

int CCtrlVision::UpdateCameraList()
{
	int cam_count = 0;
	int i = 0;

	// 清除陣列
	m_CaramList.RemoveAll();

	//僅僅獲取攝像頭數目
	cam_count = CCameraDS::CameraCount();
	TRACE1("There are %d cameras.\n", cam_count);
 
	//獲取所有攝像頭的名稱
	for(i=0; i < cam_count; i++)
	{
		char camera_name[1024];  
		int retval = CCameraDS::CameraName(i, camera_name, sizeof(camera_name) );
 
		if(retval >0)
		{
			TRACE2("Camera #%d's Name is '%s'.\n", i, camera_name);
			m_CaramList.Add(camera_name);
			//m_Device_List.InsertString(i,camera_name);
		}else
			TRACE1("Can not get Camera #%d's name.\n", i);
	}

	return cam_count;
}

static CMutex MutexCameraGrabSave;
bool CCtrlVision::CameraGrabSave(int iUserID, CString csFilePath)
{
	// 取像而且儲存
	CSingleLock Lock(&MutexCameraGrabSave);
	Lock.Lock();

	//檢查使用權 是否是自己的,在別人那 先關掉別人的使用權 再拿過來
	if(m_MediaControlUse[iUserID] == false)
	{
		for(int i =0;i<_MaxCam;i++)
		{
			if(m_MediaControlUse[i])
				m_Camera[i].SetMediaControl(false);//關掉使用權
		}
	}

	m_MediaControlUse[iUserID] = true;

	bool bCameraLost = false;
	m_CaptureFrame = m_Camera[iUserID].QueryFrame(bCameraLost);	

//
	BITMAPINFO bmi;
    ZeroMemory(&bmi, sizeof(BITMAPINFO));
    bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    bmi.bmiHeader.biBitCount = 24;
    bmi.bmiHeader.biHeight = 480;
    bmi.bmiHeader.biWidth = 640;
    bmi.bmiHeader.biPlanes = 1;

    HDC dc = CreateCompatibleDC(NULL);
	HBITMAP hbitmap = CreateDIBSection(dc, &bmi, DIB_RGB_COLORS, (void **)m_CaptureFrame, NULL, 0 );

	m_pBitmap = &hbitmap;

	// 存檔
	SaveImage( csFilePath.GetBuffer(0), m_CaptureFrame, 640, 480 );

	Lock.Unlock();
	
	return true;
}
static CMutex MutexCameraGrab;
bool CCtrlVision::CameraGrab(int iUserID)
{
	CSingleLock Lock(&MutexCameraGrab);
	Lock.Lock();

	//檢查使用權 是否是自己的,在別人那 先關掉別人的使用權 再拿過來
	if(m_MediaControlUse[iUserID] == false)
	{
		for(int i =0;i<_MaxCam;i++)
		{
			if(m_MediaControlUse[i])
				m_Camera[i].SetMediaControl(false);//關掉使用權
		}
	}

	m_MediaControlUse[iUserID] = true;

	bool bCameraLost = false;
	m_CaptureFrame = m_Camera[iUserID].QueryFrame(bCameraLost);	

//
	BITMAPINFO bmi;
    ZeroMemory(&bmi, sizeof(BITMAPINFO));
    bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    bmi.bmiHeader.biBitCount = 24;
    bmi.bmiHeader.biHeight = 480;
    bmi.bmiHeader.biWidth = 640;
    bmi.bmiHeader.biPlanes = 1;

    HDC dc = CreateCompatibleDC(NULL);
	HBITMAP hbitmap = CreateDIBSection(dc, &bmi, DIB_RGB_COLORS, (void **)m_CaptureFrame, NULL, 0 );

	m_pBitmap = &hbitmap;

	Lock.Unlock();

	return true;
}
void CCtrlVision::Draw(HDC hDC,CRect rect,char* pBuffer) 
{
	BITMAPINFO lpbmih;
    lpbmih.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    lpbmih.bmiHeader.biWidth = 640;
    lpbmih.bmiHeader.biHeight = 480;
    lpbmih.bmiHeader.biPlanes = 1;
    lpbmih.bmiHeader.biBitCount = 24;
    lpbmih.bmiHeader.biCompression = BI_RGB;
    lpbmih.bmiHeader.biSizeImage = 0;
    lpbmih.bmiHeader.biXPelsPerMeter = 0;
    lpbmih.bmiHeader.biYPelsPerMeter = 0;
    lpbmih.bmiHeader.biClrUsed = 0;
    lpbmih.bmiHeader.biClrImportant = 0;
	
	SetStretchBltMode(hDC,COLORONCOLOR);
	StretchDIBits(hDC, 
		rect.left, rect.top,rect.right, rect.bottom,
		0, 0,  lpbmih.bmiHeader.biWidth, lpbmih.bmiHeader.biHeight,
		pBuffer, &lpbmih, DIB_RGB_COLORS, SRCCOPY);

}
void CCtrlVision::DrawWindow(int iUserID,LPVOID hWndShowPage,int iWindowID)
{
	if(hWndShowPage == NULL || iWindowID ==NULL)
		return;

	CDialog  *Dlg_Show=(CDialog *)hWndShowPage;

	if( Dlg_Show->GetSafeHwnd() == NULL )
		return ;

	CDC* pDC = Dlg_Show->GetDlgItem(iWindowID)->GetDC();
	HDC hDC = pDC->GetSafeHdc();

	CRect rect;
	Dlg_Show->GetDlgItem(iWindowID)->GetClientRect(&rect);
	
	ReleaseDC(Dlg_Show->m_hWnd,hDC);
}
HBITMAP* CCtrlVision::GetBitmap()
{
	return m_pBitmap;
}
bool CCtrlVision::SaveImage(char* szPathName, void* lpBits, int w, int h)
{ 	
	//Create a new file for writing	
	FILE *pFile = fopen(szPathName, "wb");
	
	if(pFile == NULL)		
	{ 		
		return false;		
	}

	BITMAPINFOHEADER BMIH;	
	BMIH.biSize = sizeof(BITMAPINFOHEADER);	
	BMIH.biSizeImage = w * h * 3;	

	// Create the bitmap for this OpenGL context	
	BMIH.biSize = sizeof(BITMAPINFOHEADER);	
	BMIH.biWidth = w;	
	BMIH.biHeight = h;	
	BMIH.biPlanes = 1;	
	BMIH.biBitCount = 24;	
	BMIH.biCompression = BI_RGB;	
	BMIH.biSizeImage = w * h* 3; 	
	BITMAPFILEHEADER bmfh;
	
	int nBitsOffset = sizeof(BITMAPFILEHEADER) + BMIH.biSize; 	
	LONG lImageSize = BMIH.biSizeImage;	
	LONG lFileSize = nBitsOffset + lImageSize;	
	bmfh.bfType = 'B'+('M'<<8);	
	bmfh.bfOffBits = nBitsOffset;	
	bmfh.bfSize = lFileSize;	
	bmfh.bfReserved1 = bmfh.bfReserved2 = 0;
	
	//Write the bitmap file header	
	UINT nWrittenFileHeaderSize = fwrite(&bmfh, 1, 		
		sizeof(BITMAPFILEHEADER), pFile);
	
	//And then the bitmap info header	
	UINT nWrittenInfoHeaderSize = fwrite(&BMIH, 		
		1, sizeof(BITMAPINFOHEADER), pFile);
	
	//Finally, write the image data itself 	
	//-- the data represents our drawing	
	UINT nWrittenDIBDataSize = 		
		fwrite(lpBits, 1, lImageSize, pFile);
	
	fclose(pFile);
	
	return true;	
}

bool CCtrlVision::CameraInitial(int iUserID,int iCameraID)
{
	// iUserID		-> 紀錄目前開到第幾支相機..因為可能會開很多支
	// iCameraID	-> 現在要開列表裡面的第幾支相機..

	// m_iCameraUseID 由設定檔來
	m_iCameraUseID	= iCameraID;

	// 表示 m_iCameraID 目前要開啟的那支是設定為多少 
	m_iCameraID[iUserID] = iCameraID;

	// 表示第 n 支是否開啟成功
	m_bIsCameraReady[iUserID] = 
		m_Camera[iUserID].OpenCamera(iUserID, false, _CAMERA_WIDTH, _CAMERA_HEIGHT);
	
	m_pCapturImageData[iUserID] = (char*)malloc( _CAMERA_WIDTH * _CAMERA_HEIGHT*3*sizeof(char));

	return m_bIsCameraReady[iUserID];
}
bool CCtrlVision::Open(int iCameraID)
{
	// iCameraID	-> 讓使用者決定要開哪一支相機.. 這樣可以寫到 ini 檔. 不要寫死在程式裡面
	bool bOpenOK = true;
	if( CameraInitial(m_iCameraOpenCount, iCameraID ) )
	{
		// Open OK
		m_iCameraOpenCount +=1;
	}
	else
	{
		bOpenOK = false;
	}

	return bOpenOK;
}
/*
// GDIPlus
int CCtrlVision::GetEncoderClsid(const WCHAR* format, CLSID* pClsid)   
{   
    UINT num = 0;                     // number of image encoders   
    UINT size = 0;                   // size of the image encoder array in bytes   
    ImageCodecInfo* pImageCodecInfo = NULL;   
    GetImageEncodersSize(&num, &size);   
    if(size == 0)   
        return -1;     //   Failure 
    
    pImageCodecInfo = (ImageCodecInfo*)(malloc(size));   
    if(pImageCodecInfo == NULL)   
        return -1;     //   Failure   
    
    GetImageEncoders(num, size, pImageCodecInfo);   
    for(UINT j = 0; j < num; ++j)   
    {   
        if( wcscmp(pImageCodecInfo[j].MimeType, format) == 0 )   
        {   
            *pClsid = pImageCodecInfo[j].Clsid;   
            free(pImageCodecInfo);   
            return j;     //   Success   
        }           
    }
	
    free(pImageCodecInfo);

    return -1;
	//   Failure   
}

Status CCtrlVision::SaveFile(Bitmap* pImage, const wchar_t* pFileName)//
{
    EncoderParameters encoderParameters;
    CLSID jpgClsid;

	GetEncoderClsid(L"image/jpeg", &jpgClsid);

    encoderParameters.Count = 1;
    encoderParameters.Parameter[0].Guid = EncoderQuality;
    encoderParameters.Parameter[0].Type = EncoderParameterValueTypeLong;
    encoderParameters.Parameter[0].NumberOfValues = 1;

    // Save the image as a JPEG with quality level 100.
    ULONG             quality;
    quality = 100;
    encoderParameters.Parameter[0].Value = &quality;
    Status status = pImage->Save(pFileName, &jpgClsid, &encoderParameters);
    if (status != Ok) 
    {
        wprintf(L"%d Attempt to save %s failed.\n", status, pFileName);

		//
		CString csMsg = _T("");
		csMsg.Format("%d Attempt to save %s failed.(%s)\n", status, pFileName, GetStatusValue(status));
		VisionMessage( csMsg );
    }

	return status;
}

void CCtrlVision::ConvertFile(CString csSourceBmp, CString csDestionJpg)
{
	Bitmap newbitmap(csSourceBmp.AllocSysString());
	const unsigned short *pFileName=csDestionJpg.AllocSysString();
	Status status = SaveFile(&newbitmap,pFileName );
}
void CCtrlVision::VisionMessage(CString csMsg)
{
	csMsg.TrimLeft();
	csMsg.TrimRight();

	//
	TRACE( csMsg );

	//
	f.CWinMessage( csMsg, theApp.enDArm );
}
CString CCtrlVision::GetStatusValue(Status status)
{
  if( status == Ok )
	  return "Ok";
  if( status == GenericError )
	  return "GenericError";
  if( status == InvalidParameter )
	  return "InvalidParameter";
  if( status == OutOfMemory )
	  return "OutOfMemory";
  if( status == ObjectBusy )
	  return "ObjectBusy";
  if( status == InsufficientBuffer )
	  return "InsufficientBuffer";
  if( status == NotImplemented )
	  return "NotImplemented";
  if( status == Win32Error )
	  return "Win32Error";
  if( status == WrongState )
	  return "WrongState";
  if( status == Aborted )
	  return "Aborted";
  if( status == FileNotFound )
	  return "FileNotFound";
  if( status == ValueOverflow )
	  return "ValueOverflow";
  if( status == AccessDenied )
	  return "AccessDenied";
  if( status == UnknownImageFormat )
	  return "UnknownImageFormat";
  if( status == FontFamilyNotFound )
	  return "FontFamilyNotFound";
  if( status == FontStyleNotFound )
	  return "FontStyleNotFound";
  if( status == NotTrueTypeFont )
	  return "NotTrueTypeFont";
  if( status == UnsupportedGdiplusVersion )
	  return "UnsupportedGdiplusVersion";
  if( status == GdiplusNotInitialized )
	  return "GdiplusNotInitialized";
//  if( status == PropertyNotFound )
//	  return "PropertyNotFound";
//  if( status == PropertyNotSupported )
//	  return "PropertyNotSupported";
//  if( status == ProfileNotFound )
//	  return "ProfileNotFound";

  return "No Define";
}
*/






