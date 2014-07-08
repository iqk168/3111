// CtrlVision.cpp: implementation of the CCtrlVision class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Deer.h"
#include "CtrlVision.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
// ------------------------------------------------------------------------
// Callback
void WINAPI GlobalHandler(PVOID context, PECEVENTINFO pInfo)
{
	if(pInfo->EventID == EC_SIGNAL_SURFACE_STATE)
	{
		if(pInfo->ChannelID == m.CCD.hChannel0)
		{
			switch(m.CCD.m_State)
			{
			case CCtrlVision::enGrab:
				m.CCD.GrabDone();
				break;
			case CCtrlVision::enLive:
				f.LiveReflash();
				break;
			default:
				m.CCD.LiveStop();
				break;
			}
		}
		else
			; // Cycle Useing.
	}
}


CCtrlVision::CCtrlVision()
{

}

CCtrlVision::~CCtrlVision()
{
	TRACE("~CCtrlVision\n");
}

//
bool CCtrlVision::Grab()
{
	m_State = enGrab;
	MultiCamChannelSetParameterInt(hChannel0, EC_PARAM_ChannelState, CHANNEL_STATE_IDLE);
	MultiCamChannelSetParameterInt(hChannel0, EC_PARAM_RepeatGrabCount, 0);
	MultiCamChannelSetParameterInt(hChannel0, EC_PARAM_ChannelState, CHANNEL_STATE_ACTIVE);

	long start = ::GetTickCount();
	while(1)
	{
		if(m_State == enNone)
		{
			m_Match.GrabOK = true;
			break;
		}
		else if(::GetTickCount() - start > 5000)
		{
			MultiCamChannelSetParameterInt(hChannel0, EC_PARAM_ChannelState, CHANNEL_STATE_IDLE);
			m_Match.GrabOK = false;
			m_State = enNone;
			break;
		}
		Sleep(10);
	}
	
	if(m_Match.GrabOK)
	{
		CRect rect;
		m_GrabImage.Detach();
		m_GrabImage.Attach(m_pGrabImage);
		m_GrabImage.SetPlacement(0, 0, m_GrabImage.GetTotalWidth(), 
			m_GrabImage.GetTotalHeight());
	}

	return m_Match.GrabOK;
}

void CCtrlVision::GrabDone()
{
	MultiCamChannelSetParameterInt(hChannel0, EC_PARAM_ChannelState, CHANNEL_STATE_IDLE);

	m_State = enNone;
}

void CCtrlVision::GrabMatch(int site)
{
	if(Grab())
	{
		MatchCheck(m_pGrabImage);
	}
	else
	{
		m_Match.Score = 0.0;
		m_Match.MatchResult.Format("GrabErr: S=%5.2f", 
					m_Match.Score);
		m_Match.Pass = false;
	}

	// ccd	
	if( theApp.m_DlgGrabShow.GetSafeHwnd() != NULL)
	{
		if(site > 0)
		{
			CString cs;
			cs.Format("Site%d : ", site);
			theApp.m_DlgGrabShow.UpdateGrabImage(m_pGrabImage, cs + m_Match.MatchResult);
		}
		else
			theApp.m_DlgGrabShow.UpdateGrabImage(m_pGrabImage, m_Match.MatchResult);
	}
	//
}

CPoint CCtrlVision::CheckAlignment(EImageC24 *pSourceImage)
{
	CPoint pt;
	pt.x = 9999;
	pt.y = 9999;

	EImageBW8 bb(m_Match.PatternImageColor.GetWidth(), m_Match.PatternImageColor.GetHeight());
	EROIBW8 imag;
	imag.Attach(&bb);
	
	imag.SetPlacement(20, 20, pSourceImage->GetWidth()-40, pSourceImage->GetHeight()-40);
	
	m_Match.PatternROI_Original.Detach();
	m_Match.PatternROI_Original.Attach(&m_Match.PatternImageColor);
	m_Match.PatternROI_Original.SetPlacement(20, 20, pSourceImage->GetWidth()-40, pSourceImage->GetHeight()-40);

	ImgConvert(&m_Match.PatternROI_Original, &imag);

	MatchObj.LearnPattern(&imag);
	
	m_Match.SourceROI.Detach();
	m_Match.SourceROI.Attach(pSourceImage);
	m_Match.SourceROI.SetPlacement(0, 0, pSourceImage->GetWidth(), pSourceImage->GetHeight());

	////////////////////////////////////////////////////////
	EROIBW8 ima;
	EImageBW8 aa(pSourceImage->GetWidth(), pSourceImage->GetHeight());
	ima.Attach(&aa);
	ima.SetPlacement(0, 0, pSourceImage->GetWidth(), pSourceImage->GetHeight());
	ImgConvert(&m_Match.SourceROI, &ima);
	////////////////////////////////////////////////////////
	
	MatchObj.Match(&ima);
	
	if(MatchObj.GetNumPositions() > 0)
	{
		EMatchPosition *pos = MatchObj.GetPosition(0);
		if(pos->m_f32Score > 0.6)
		{
			pt.x = pos->m_f32CenterX - pSourceImage->GetWidth()/2;
			pt.y = pos->m_f32CenterY - pSourceImage->GetHeight()/2;
		}
	}

	return pt;
}

void CCtrlVision::MatchCheck(EImageC24 *pSourceImage)
{
	MatchObj.SetMinScore((float)0.1);
	MatchObj.SetMaxPositions(3);
	MatchObj.SetMinAngle((float)-1.5);
	MatchObj.SetMaxAngle((float)1.5);

	CPoint pt;
	
	// ccd
	/*
	if(m.ExtraFunction.ImagePatternAlign == 2)
	{
		pt = CheckAlignment(pSourceImage);
		
		if(pt.x > 25 || pt.y > 25)
		{
			m_Match.MatchResult.Format("Fail: S=0");
			m_Match.Pass = false;
			
			if( theApp.m_DlgGrabShow.GetSafeHwnd() != NULL)
				theApp.m_DlgGrabShow.UpdateGrabImage(pSourceImage, m_Match.MatchResult);
			return;
		}
	}
	//
	*/

	EImageBW8 bb(m_Match.PatternImageColor.GetWidth(), m_Match.PatternImageColor.GetHeight());
	EROIBW8 imag;
	imag.Attach(&bb);
	
	imag.SetPlacement(m_Match.PatternROIColor.GetOrgX(),
		m_Match.PatternROIColor.GetOrgY(), 
		m_Match.PatternROIColor.GetWidth(),
		m_Match.PatternROIColor.GetHeight());
	
	ImgConvert(&m_Match.PatternROIColor, &imag);

	MatchObj.LearnPattern(&imag);
	
	m_Match.SourceROI.Detach();
	m_Match.SourceROI.Attach(pSourceImage);

	int l = 0;
	int t = 0;
	int r, b;

	/*
	if(m.ExtraFunction.ImagePatternAlign == 2)
	{
		//////////////////////////////////////////////////////
		// Lance: 新的方式
		int iW = m_Match.PatternROIColor.GetWidth();
		int iH = m_Match.PatternROIColor.GetHeight();
		l = m_Match.PatternROIColor.GetOrgX() - 5 + pt.x;
		r = iW + 10;
		
		t = m_Match.PatternROIColor.GetOrgY() - 5 + pt.y;
		b = iH + 10;
		if(r > pSourceImage->GetWidth())
			r = pSourceImage->GetWidth();
		if(b > pSourceImage->GetHeight())
			b = pSourceImage->GetHeight();
		if(l < 0 || (l + r) > pSourceImage->GetWidth()) 
			l = 0;
		if(t < 0 || (t + b) > pSourceImage->GetHeight())
			t = 0;
		
		m_Match.SourceROI.SetPlacement(l, t, r, b);
	}
	else if(m.ExtraFunction.ImagePatternAlign == 0)
	{
		//////////////////////////////////////////////////////
		// 對於很小的框來說 -50, +100 太大了
		// Lance: V2.0QE, 框框跟著 source 的大小做變化
		l = m_Match.PatternROIColor.GetOrgX() - 50;
		if(l < 0) 
			l = 0;
		
		t = m_Match.PatternROIColor.GetOrgY() - 50;
		if(t < 0) 
			t = 0;
		
		r = m_Match.PatternROIColor.GetWidth() + 100;
		if(r > pSourceImage->GetWidth())
			r = pSourceImage->GetWidth();
		
		b = m_Match.PatternROIColor.GetHeight() + 100;
		if(b > pSourceImage->GetHeight())
			b = pSourceImage->GetHeight();

		m_Match.SourceROI.SetPlacement(l, t, r, b);
	}
	else
	*/
	{
		int iW = m_Match.PatternROIColor.GetWidth();
		int iH = m_Match.PatternROIColor.GetHeight();
		if(iW < 10)
		{
			l = m_Match.PatternROIColor.GetOrgX() - 10;
			r = iW + 20;
		}
		if(iW < 100)
		{
			l = m_Match.PatternROIColor.GetOrgX() - iW/2;
			r = iW + iW;
		}
		else
		{
			l = m_Match.PatternROIColor.GetOrgX() - 50;
			r = iW + 100;
		}
		if(iH < 10)
		{
			t = m_Match.PatternROIColor.GetOrgY() - 10;
			b = iH + 20;
		}
		else if(iW < 100)
		{
			t = m_Match.PatternROIColor.GetOrgY() - iH/2;
			b = iH + iH;
		}
		else
		{
			t = m_Match.PatternROIColor.GetOrgY() - 50;
			b = iH + 100;
		}
		if(l < 0) 
			l = 0;
		if(t < 0)
			t = 0;
		if(r > pSourceImage->GetWidth())
			r = pSourceImage->GetWidth();
		if(b > pSourceImage->GetHeight())
			b = pSourceImage->GetHeight();
		//////////////////////////////////////////////////////
		m_Match.SourceROI.SetPlacement(l, t, r, b);
	}
	
	////////////////////////////////////////////////////////
	EROIBW8 ima;
	EImageBW8 aa(pSourceImage->GetWidth(), pSourceImage->GetHeight());
	ima.Attach(&aa);
	ima.SetPlacement(l, t, r, b);
	ImgConvert(&m_Match.SourceROI, &ima);
	////////////////////////////////////////////////////////
	
	MatchObj.Match(&ima);
	
	if(MatchObj.GetNumPositions() > 0)
	{
		EMatchPosition *pos = MatchObj.GetPosition(0);
		m_Match.Score = pos->m_f32Score;
		if(m_Match.Score > m_Match.MinScore)
		{
			m_Match.MatchResult.Format("Pass: S=%5.2f", m_Match.Score);
			m_Match.Pass = true;
		}
		else
		{
			m_Match.MatchResult.Format("Fail: S=%5.2f", m_Match.Score);
			m_Match.Pass = false;
		}
	}
	else
	{
		m_Match.Score = 0.0;
		m_Match.MatchResult.Format("MatchErr: S=%5.2f", m_Match.Score);
		m_Match.Pass = false;
	}

	// ccd
	if( theApp.m_DlgGrabShow.GetSafeHwnd() != NULL)
		theApp.m_DlgGrabShow.UpdateGrabImage(pSourceImage, m_Match.MatchResult);
	//
}

void CCtrlVision::SetMatchPattern(CString file, CRect rect, double MinScore)
{
	m_Match.PatternImageColor.Load(".\\Image\\Images\\" + file);
	m_Match.rect = rect;
	m_Match.MinScore = MinScore;

	m_Match.PatternROI_Original.Detach();
	m_Match.PatternROI_Original.Attach(&m_Match.PatternImageColor);
	m_Match.PatternROI_Original.SetPlacement(20, 20, m_Match.PatternImageColor.GetWidth()-40,
		m_Match.PatternImageColor.GetHeight()-40);

	m_Match.PatternROIColor.Detach();
	m_Match.PatternROIColor.Attach(&m_Match.PatternImageColor);
	m_Match.PatternROIColor.SetPlacement(m_Match.rect.left, m_Match.rect.top, 
		m_Match.rect.Width(), m_Match.rect.Height());
}

void CCtrlVision::CountProjection(tagVector &Vect, EImageC24 *pImage)
{
	EC24Vector VectorRow;
	EC24Vector VectorColomn;
	EROIC24 image;
	image.Detach();
	image.Attach(pImage);
	image.SetPlacement(0, 0, 640, 480);
	ImgProjectOnARow(&image, &VectorRow);
	UINT32 nXStep = VectorRow.GetNumElements();

	ImgProjectOnARow(pImage, &VectorRow);
	
	unsigned char *pRGBValue = (unsigned char *)VectorRow.GetDataPtr();
	
	for(UINT32 i=0; i<nXStep; i++, pRGBValue+=3)
	{
		Vect.RowB[i] = *pRGBValue;
		Vect.RowG[i] = *(pRGBValue+1);
		Vect.RowR[i] = *(pRGBValue+2);
	}
}

BOOL CCtrlVision::CheckProjection(tagVector &source, tagVector &target)
{
	CString cs;
	if(m_Match.Score < 0.99)
		return enMatchFail;

	long AverB = 0;
	long AverG = 0;
	long AverR = 0;
	for(int i=50; i<570; i++)
	{
		AverB += target.RowB[i];
		AverG += target.RowG[i];
		AverR += target.RowR[i];
	}
	AverB /= 520;
	AverG /= 520;
	AverR /= 520;

	if(AverB < 38)
		return enProjectionFail;
	if(AverG < 38)
		return enProjectionFail;
	if(AverR < 38)
		return enProjectionFail;
	
	for(int j=50; j<570; j++)
	{

		if(abs(target.RowB[j]-target.RowB[j+1]) > 1)
			return enProjectionFail;
		if(abs(target.RowG[j]-target.RowG[j+1]) > 1)
			return enProjectionFail;
		if(abs(target.RowR[j]-target.RowR[j+1]) > 1)
			return enProjectionFail;

		for(int k=1; k<10; k+=2)
		{
			if(abs(target.RowB[j]-target.RowB[j+k]) > 1)
				return enProjectionFail;
			if(abs(target.RowG[j]-target.RowG[j+k]) > 1)
				return enProjectionFail;
			if(abs(target.RowR[j]-target.RowR[j+k]) > 1)
				return enProjectionFail;
		}

		for(k=1; k<12; k+=3)
		{
			if(abs(target.RowB[j]-target.RowB[j+k]) > 5)
				return enProjectionFail;
			if(abs(target.RowG[j]-target.RowG[j+k]) > 5)
				return enProjectionFail;
			if(abs(target.RowR[j]-target.RowR[j+k]) > 5)
				return enProjectionFail;
		}

		if(abs(target.RowB[j] - AverB) > 5)
			return enProjectionFail;
		if(abs(target.RowG[j] - AverG) > 5)
			return enProjectionFail;
		if(abs(target.RowR[j] - AverR) > 5)
			return enProjectionFail;
	}

	return enPass;
}

BOOL CCtrlVision::Projection()
{
	if(Grab())
		MatchCheck(m_pGrabImage);
	else
		return enGrabFail;

	CountProjection(m_Projection.Now, m_pGrabImage);

	return CheckProjection(m_Projection.Source, m_Projection.Now);
}

void CCtrlVision::SetProjectionPattern(CString file, long level)
{
	m_Projection.PatternImage.Load(file);
	m_Projection.level = level;
	CRect r(0, 0, 640, 480);
#ifndef _Demo
	SetMatchPattern(file, r);
	CountProjection(m_Projection.Source, &m_Projection.PatternImage);
#endif
}

BOOL CCtrlVision::Projection(CString file)
{
	EImageC24 image;
	image.Load(file);
	CountProjection(m_Projection.Now, &image);

	return CheckProjection(m_Projection.Source, m_Projection.Now);
}

void CCtrlVision::SaveGrabFile(CString file)
{
	m_GrabImage.Save(file, E_FILE_FORMAT_COLOR_BMP);
}

EImageC24 *CCtrlVision::GetGrabImage()
{
	return m_pGrabImage;	
}

EROIC24 CCtrlVision::GetGrabROI()
{
	return m_GrabImage;
}

EImageC24 *CCtrlVision::GetPatternImage()
{
	return &m_Match.PatternImageColor;
}

EROIC24 &CCtrlVision::GetPatternROI()
{
	return m_Match.PatternROIColor;
}

void CCtrlVision::Initial()
{
	char ErrorMessage [128] ;
	ECSTATUS Status;
	ECSURFACEINFO SurfInfo ;
	CString BoardID;
	BoardID.Format("#%d", m_iBoardID);

	m_pGrabImage = NULL;

	if(!m_bVisionInitial)
	{
		// ------------------------------------------------------------------------
		// Initialize library
		// ------------------------------------------------------------------------
		Status = MultiCamSystemInitialize();
		if(Status != EC_OK)
		{
			AfxMessageBox("Cannot Initialize device driver", MB_OK | MB_APPLMODAL | MB_ICONINFORMATION);
			return;
		}
		m_bVisionInitial = true;
	}

	// ------------------------------------------------------------------------
	// Create a Channel 
	// ------------------------------------------------------------------------
	hChannel0 = MultiCamChannelCreate(NULL, BoardID, m_iChannelID);
	if (hChannel0 <= 0)
	{
		sprintf(ErrorMessage, "Cannot Create Channel to board %s", BoardID);
		AfxMessageBox(ErrorMessage, MB_OK | MB_APPLMODAL | MB_ICONSTOP);
		return ;
	}

	MultiCamChannelSetParameterInt(hChannel0, EC_PARAM_ChannelState, CHANNEL_STATE_IDLE);

	MultiCamChannelSetParameterInt(hChannel0, EC_PARAM_InitPause, 0);
	MultiCamChannelSetParameterInt(hChannel0, EC_PARAM_InitTrigger, INIT_TRIGGER_PAUSE);
	MultiCamChannelSetParameterInt(hChannel0, EC_PARAM_InitGrabSync, GRABSYNC_NEXT);
	MultiCamChannelSetParameterInt(hChannel0, EC_PARAM_InitGrabDelay, 0);
	MultiCamChannelSetParameterInt(hChannel0, EC_PARAM_RepeatPause, 0);
	MultiCamChannelSetParameterInt(hChannel0, EC_PARAM_RepeatTrigger, REPEAT_TRIGGER_PAUSE);
	MultiCamChannelSetParameterInt(hChannel0, EC_PARAM_RepeatGrabSync, GRABSYNC_NEXT);
	MultiCamChannelSetParameterInt(hChannel0, EC_PARAM_RepeatGrabDelay, 0);
	MultiCamChannelSetParameterInt(hChannel0, EC_PARAM_RepeatGrabCount, -1 );

	MultiCamChannelSetParameterInt(hChannel0, EC_PARAM_TriggerMode, TRIGGERMODE_AUTO);
	MultiCamChannelSetParameterInt(hChannel0, EC_PARAM_TriggerMask, TRIGGERMASK_BYPASS);
	MultiCamChannelSetParameterInt(hChannel0, EC_PARAM_AssemblerMask, ASMMASK__DELAY);

#ifdef PAL
	MultiCamChannelSetParameterInt(hChannel0, EC_PARAM_Standard, EC_STANDARD_PAL);
#else	
	MultiCamChannelSetParameterInt(hChannel0, EC_PARAM_Standard, EC_STANDARD_NTSC);
#endif
	
	MultiCamChannelSetParameterInt(hChannel0, EC_PARAM_Scanning, EC_SCANNING_INTERLACED);
	MultiCamChannelSetParameterInt(hChannel0, EC_PARAM_Resolution, EC_RESOLUTION_SQUARE);

	MultiCamChannelSetParameterInt(hChannel0, EC_PARAM_FieldMode, 2);
	MultiCamChannelSetParameterInt(hChannel0, EC_PARAM_AcqColFmt, EC_COLORFORMAT_RGB24);

	MultiCamChannelSetParameterInt(hChannel0, EC_PARAM_VideoGain, 0x10000);
	MultiCamChannelSetParameterInt(hChannel0, EC_PARAM_VideoOffset, 0x0);

	MultiCamChannelSetParameterInt(hChannel0, EC_PARAM_VideoUGain, 0x10000);
	MultiCamChannelSetParameterInt(hChannel0, EC_PARAM_VideoVGain, 0x10000);

	MultiCamChannelSetParameterInt(hChannel0, EC_PARAM_VideoHue, 0x0);


	// ------------------------------------------------------------------------
	// Create a surface
	// ------------------------------------------------------------------------

	MultiCamChannelGetParameterInt(hChannel0, EC_PARAM_ImageSizeX, &ImageSizeX);
	MultiCamChannelGetParameterInt(hChannel0, EC_PARAM_ImageSizeY, &ImageSizeY);

	m_pGrabImage = new EImageC24(ImageSizeX, ImageSizeY);
	SurfInfo.StructSize = sizeof (ECSURFACEINFO);
	SurfInfo.Type = EC_SURFACE_TYPE_PC;
	SurfInfo.Size = ImageSizeX*ImageSizeY*3;
	SurfInfo.Pitch = ImageSizeX*3;
	SurfInfo.UserAllocatedMemory = 0;
	SurfInfo.Address = m_pGrabImage->GetImagePtr();

	hSurface = MultiCamSurfaceCreate(&SurfInfo);
	if (hSurface < 0)
	{
		AfxMessageBox("Cannot Create Surface", MB_OK | MB_APPLMODAL | MB_ICONSTOP);
		return ;
	}

	memset(SurfInfo.Address, 0, SurfInfo.Size);

	// ------------------------------------------------------------------------
	// Add Surface in channel
	// ------------------------------------------------------------------------
	Status = MultiCamChannelAddSurface(hChannel0, hSurface);
	if (Status != EC_OK)
	{
		AfxMessageBox("Cannot add surface into channel", MB_OK | MB_APPLMODAL | MB_ICONSTOP);
		return ;
	}

	if(m_bVisionInitial && !m_bVisionStart)
	{
		// ------------------------------------------------------------------------
		// Register signal "Surface available" callback function
		// ------------------------------------------------------------------------
		Status = MultiCamSignalRegister(EC_SIGNAL_SURFACE_STATE, ::GlobalHandler, NULL);	
		if(Status != EC_OK)
		{
			AfxMessageBox("Cannot Register Signal Handler", MB_OK | MB_APPLMODAL | MB_ICONSTOP);
			return;
		}
		
		// ------------------------------------------------------------------------
		// Enable Acquisition
		// ------------------------------------------------------------------------
		Status = MultiCamSystemAcquisitionStart();
		if (Status != EC_OK)
		{
			AfxMessageBox("Cannot enable acquisition", MB_OK | MB_APPLMODAL | MB_ICONSTOP);
			return ;
		}
		m_bVisionStart = true;
	}
}

void CCtrlVision::Load(CString file)
{
	long Left, Top, Width, Height;
	double Score;
	f.GetSetting(".\\Image\\Profiles\\" + file, "Source Image", "Image File", 
		m_Match.File);

	f.GetSetting(".\\Image\\Profiles\\" + file, "Source Image", "X", Left);
	f.GetSetting(".\\Image\\Profiles\\" + file, "Source Image", "Y", Top);
	f.GetSetting(".\\Image\\Profiles\\" + file, "Source Image", "Width", Width);
	f.GetSetting(".\\Image\\Profiles\\" + file, "Source Image", "Height", Height);
	f.GetSetting(".\\Image\\Profiles\\" + file, "Source Image", "Score", Score);

	SetMatchPattern(m_Match.File, CRect(Left, Top, Width+Left, Height+Top), Score);
}

void CCtrlVision::Save(EROIC24 *image, CString file, CString BmpFile)
{
	m_Match.File = BmpFile;
	image->Save(".\\Image\\Images\\" + m_Match.File, E_FILE_FORMAT_COLOR_BMP);
	f.SaveSetting(".\\Image\\Profiles\\" + file, "Source Image", "Image File", 
		m_Match.File);

	f.SaveSetting(".\\Image\\Profiles\\" + file, "Source Image", "X", m_Match.rect.left);
	f.SaveSetting(".\\Image\\Profiles\\" + file, "Source Image", "Y", m_Match.rect.top);
	f.SaveSetting(".\\Image\\Profiles\\" + file, "Source Image", "Width", (long)m_Match.rect.Width());
	f.SaveSetting(".\\Image\\Profiles\\" + file, "Source Image", "Height", (long)m_Match.rect.Height());
	f.SaveSetting(".\\Image\\Profiles\\" + file, "Source Image", "Score", m_Match.MinScore);
}

void CCtrlVision::SetMatchPattern(EROIC24 &image)
{
	MatchObj.SetMaxPositions(3);
	MatchObj.SetMinAngle((float)-1.5);
	MatchObj.SetMaxAngle((float)1.5);
	MatchObj.SetMinScore((float)0.1);

	MatchObj.LearnPattern(&image);
}

void CCtrlVision::SetID(int BoardID, int ChannelID)
{
	m_iBoardID = BoardID;
	m_iChannelID = ChannelID;
}

bool CCtrlVision::GetMatchResult()
{
	return m_Match.Pass;
}

bool CCtrlVision::Live()
{
	MultiCamChannelSetParameterInt (hChannel0, EC_PARAM_RepeatGrabCount, -1 );
	MultiCamChannelSetParameterInt (hChannel0, EC_PARAM_ChannelState, CHANNEL_STATE_ACTIVE);

	m_State = enLive;

	return true;
}

void CCtrlVision::LiveStop()
{
	MultiCamChannelSetParameterInt(hChannel0, EC_PARAM_ChannelState, CHANNEL_STATE_IDLE);

	m_State = enNone;
}

