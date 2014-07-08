// SocketVision.cpp: implementation of the CSocketVision class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "deer.h"

#include "CameraDS.h"
#include "SocketVision.h"

//
#include "Easy.h"
#include "EMatch.h"
#include "EImage.h"

//
#include <afxmt.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSocketVision::CSocketVision()
{
	//
	m_csPatternPath = _T("");
	m_csInfoPath	= _T("");
	
	//
	for(int i=0;i<_MaxCam;i++)
	{
		m_bIsCameraReady[i]		= false;
		m_iCameraID[i]			= 0;
		m_pCapturImageData[i]	= NULL;
		m_MediaControlUse[i]	= false;
	}

	//
	m_iCameraOpenCount		= 0;

	//
	m_bCameraLive			= false;

	//
	m_iCameraUseID			= 0;
}

CSocketVision::~CSocketVision()
{
	// 1.0Rk
	// Clear the Memory
// 	if( m_CaptureFrame != NULL )
// 	{
// 		free( m_CaptureFrame );
// 		m_CaptureFrame = NULL;
// 	}
// 
// 	TRACE("~CSocketVision\n");
	
	// 1.0Rl
	// CCD Socket Memory Leak
	for(int i=0;i<_MaxCam;i++)
		free(m_pCapturImageData[i]);
	
	TRACE("~CSocketVision\n");	

}
void CSocketVision::DrawWindow(int iUserID,LPVOID hWndShowPage,int iWindowID)
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
	
	double fSourceImage_WindowRatioW = rect.Width()/(double)SourceImage[iUserID].GetWidth();
	double fSourceImage_WindowRatioR = rect.Height()/(double)SourceImage[iUserID].GetHeight();
	
	SourceImage[iUserID].Draw(hDC,fSourceImage_WindowRatioW,fSourceImage_WindowRatioR);
	
	ReleaseDC(Dlg_Show->m_hWnd,hDC);
}

char* CSocketVision::GatImagePtr(int iUserID,char * pImageData)
{
	int i;
	int iByteRow	= _CAMERA_WIDTH * 3;
	int iCol		= _CAMERA_HEIGHT;
	int iCol0		= iCol-1;
	for(i=0;i<iCol;i++)
	{
		memcpy(m_pCapturImageData[iUserID]+(i*iByteRow),pImageData+(i*iByteRow),iByteRow);
	}

	return m_pCapturImageData[iUserID];
}

static CMutex MutexCameraGrab;
bool CSocketVision::CameraGrab(int iUserID)
{
	CSingleLock Lock(&MutexCameraGrab);
	Lock.Lock();
	if(m_bIsCameraReady[iUserID] == false)
		return false;

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

	SourceImage[iUserID].SetImagePtr( _CAMERA_WIDTH, _CAMERA_HEIGHT, 
		GatImagePtr(iUserID,m_CaptureFrame/*m_CaptureFrame.imageData*/));

	Lock.Unlock();

	//
	if( bCameraLost )
	{
		m_MediaControlUse[iUserID] = false;
		m_Camera[iUserID].CloseCamera();
		m_bIsCameraReady[iUserID] = false;
		m_iCameraID[iUserID] = -1;
		return false;
	}
	
	return true;
}


// Path 
void CSocketVision::SetPath(CString PatternPath, CString csInfoPath )
{
	m_csPatternPath = PatternPath;
	m_csInfoPath	= csInfoPath;
}
void CSocketVision::GetCameraList(CArray <CString, CString> &array )
{
	array.Copy( m_CaramList );
}

int CSocketVision::UpdateCameraList()
{
	int cam_count;
	int i;

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
bool CSocketVision::Open(int iCameraID)
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
bool CSocketVision::CameraInitial(int iUserID,int iCameraID)
{
	// iUserID		-> 紀錄目前開到第幾支相機..因為可能會開很多支
	// iCameraID	-> 現在要開列表裡面的第幾支相機..

	// 是否已有開啟相機
	if(m_bIsCameraReady[iUserID])
	{
		return m_bIsCameraReady[iUserID];		
	}
	// 檢查相機是否已有被其他開啟	

	//
	m_iCameraUseID	= iCameraID;
	//

	m_iCameraID[iUserID] = iCameraID;
	m_bIsCameraReady[iUserID] = 
		m_Camera[iUserID].OpenCamera(iCameraID, false, _CAMERA_WIDTH, _CAMERA_HEIGHT);
	
	m_pCapturImageData[iUserID] = (char*)malloc( _CAMERA_WIDTH * _CAMERA_HEIGHT*3*sizeof(char));

	return m_bIsCameraReady[iUserID];
}

//
EImageC24 CSocketVision::GetGrabImage(int iUserID)
{
	return SourceImage[iUserID];
}
double CSocketVision::GrabMatch(int site)
{
	if(CameraGrab(site))
	{
		MatchCheck(&m_Match[site],&SourceImage[site]);
		m_Match[site].IsGrabOK = true;
	}
	else
	{
		m_Match[site].Score = 0.0;
		m_Match[site].MatchResult.Format("GrabErr: S=%5.2f", 
					m_Match[site].Score);
		m_Match[site].Pass = false;
		m_Match[site].IsGrabOK = false;
	}
	
	return m_Match[site].Score;
}

bool CSocketVision::GetMatchGrabOK(int iUserID)
{
	return m_Match[iUserID].IsGrabOK;
}

void CSocketVision::MatchCheck(tagMatch *pMatch,EImageC24 *pSourceImage)
{
	EImageBW8 bb(pMatch->PatternImageColor.GetWidth(),
		pMatch->PatternImageColor.GetHeight());
	EROIBW8 imag;
	imag.Attach(&bb);
	
	imag.SetPlacement(pMatch->PatternROIColor.GetOrgX(),
		pMatch->PatternROIColor.GetOrgY(), 
		pMatch->PatternROIColor.GetWidth(),
		pMatch->PatternROIColor.GetHeight());
	
	ImgConvert(&pMatch->PatternROIColor, &imag);

	MatchObj.LearnPattern(&imag);

	pMatch->SourceROI.Detach();
	pMatch->SourceROI.Attach(pSourceImage);
	int l = pMatch->PatternROIColor.GetOrgX() - 50;
	if(l < 0) 
		l = 0;
	
	int t = pMatch->PatternROIColor.GetOrgY() - 50;
	if(t < 0) 
		t = 0;
	
	int r = pMatch->PatternROIColor.GetWidth() + 100;
	if(r > pSourceImage->GetWidth())
		r = pSourceImage->GetWidth();
	
	int b = pMatch->PatternROIColor.GetHeight() + 100;
	if(b > pSourceImage->GetHeight())
		b = pSourceImage->GetHeight();
	
	pMatch->SourceROI.SetPlacement(l, t, r, b);

	////////////////////////////////////////////////////////
	EROIBW8 ima;
	EImageBW8 aa(pSourceImage->GetWidth(), 
		pSourceImage->GetHeight());
	ima.Attach(&aa);
	ima.SetPlacement(l, t, r, b);
	ImgConvert(&pMatch->SourceROI, &ima);
	////////////////////////////////////////////////////////
	
	MatchObj.Match(&ima);
	
	if(MatchObj.GetNumPositions() > 0)
	{
		EMatchPosition *pos = MatchObj.GetPosition(0);
		pMatch->Score = pos->m_f32Score;
		if(pMatch->Score > pMatch->MinScore)
		{
			pMatch->MatchResult.Format("Pass: S=%5.2f", 
				pMatch->Score);
			pMatch->Pass = true;
		}
		else
		{
			pMatch->MatchResult.Format("Fail: S=%5.2f", 
				pMatch->Score);
			pMatch->Pass = false;
		}
	}
	else
	{
		pMatch->Score = 0.0;
		pMatch->MatchResult.Format("MatchErr: S=%5.2f", 
			pMatch->Score);
		pMatch->Pass = false;
	}
}


void CSocketVision::SetMatchPattern(int iUser,CString FilePath, CRect rect, double MinScore)
{
	m_Match[iUser].PatternImageColor.Load(FilePath);
	m_Match[iUser].rect = rect;
	m_Match[iUser].MinScore = MinScore;

	m_Match[iUser].PatternROIColor.Detach();
	m_Match[iUser].PatternROIColor.Attach(&m_Match[iUser].PatternImageColor);
	m_Match[iUser].PatternROIColor.SetPlacement(m_Match[iUser].rect.left, m_Match[iUser].rect.top, 
		m_Match[iUser].rect.Width(), m_Match[iUser].rect.Height());
}