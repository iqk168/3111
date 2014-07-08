// EOCVText.h: EasyOCV library header file for eVision 6.7.1.0
//
// Copyright ( c) 1997-2006, Euresys. All rights reserved.
//

#ifndef __EOCV_TEXT_H__
#define __EOCV_TEXT_H__

///////////////////////////////////////////////////////////////////////////////
#include <stdio.h>

///////////////////////////////////////////////////////////////////////////////
// eVision header files
#include "Easy.h"
#include "EOCVCharVector.h"

///////////////////////////////////////////////////////////////////////////////
class E_DLL1 EOCVText 
{
// Wrapping members
public:
  int handle_;
  FinalizeCallback callback_;

public:
  BOOL                            m_bIsotropicScaling;
  // == General
  // Construction and assignment + helpers
  E_DLL0 CONSTRUCTOR E_DLL1       EOCVText                  ( );
  E_DLL0 CONSTRUCTOR E_DLL1       EOCVText                  ( const EOCVText& other);
  E_DLL0 EOCVText& E_DLL1         operator=                 ( const EOCVText& other);
private :                                                   
  void                            CopyTo                    ( EOCVText* target) const;

public:
  // Initialization
  E_DLL0 void E_DLL1              ResetParameters           ( );
  
  // == Template edition  
  // Selection
  BOOL                            m_bSelected;    
  
  // == Location  
  // Location parameters
  UINT32                          m_un32NumContourPoints;
  
  // Location score
  FLOAT32                         m_f32TemplateLocationScore;
  FLOAT32                         m_f32SampleLocationScore;
  FLOAT32                         m_f32LocationScoreTolerance;
  
  // Location tolerance parameters
  FLOAT32                         m_f32RelativeTolerance;
  FLOAT32                         m_f32ShiftXBias;
  FLOAT32                         m_f32ShiftXTolerance;
  FLOAT32                         m_f32ShiftYBias;
  FLOAT32                         m_f32ShiftYTolerance;
  FLOAT32                         m_f32ScaleXBias;
  FLOAT32                         m_f32ScaleXTolerance;
  FLOAT32                         m_f32ScaleYBias;
  FLOAT32                         m_f32ScaleYTolerance;
  FLOAT32                         m_f32ShearBias;
  FLOAT32                         m_f32ShearTolerance;
  FLOAT32                         m_f32SkewBias;
  FLOAT32                         m_f32SkewTolerance;
                                  
  UINT32                          m_un32ShiftXStride;
  UINT32                          m_un32ShiftYStride;
  UINT32                          m_un32ScaleXCount;
  UINT32                          m_un32ScaleYCount;
  UINT32                          m_un32ShearCount;
  UINT32                          m_un32SkewCount;
  
  // Measured position ( with respect to the nominal position)
  FLOAT32                         m_f32ScaleX;
  FLOAT32                         m_f32ScaleY;
  FLOAT32                         m_f32Shear;
  FLOAT32                         m_f32Skew;
  FLOAT32                         m_f32ShiftX;
  FLOAT32                         m_f32ShiftY;
  
  // == Inspection  
  // Qualitative diagnostics
  UINT32                          m_un32Diagnostics;
  
  // Margin width
  UINT32                          m_un32MarginWidth;
  
  // Inspected ROI ( in the source image)
  EROIBW8                         m_InspectedRoi;
  
  // Quality indicators
  UINT32                          m_un32TemplateForegroundArea;
  UINT32                          m_un32SampleForegroundArea;
  UINT32                          m_un32ForegroundAreaTolerance;
                                  
  UINT32                          m_un32TemplateBackgroundArea;
  UINT32                          m_un32SampleBackgroundArea;
  UINT32                          m_un32BackgroundAreaTolerance;
                                  
  FLOAT32                         m_f32TemplateForegroundSum;
  FLOAT32                         m_f32SampleForegroundSum;
  FLOAT32                         m_f32ForegroundSumTolerance;
                                  
  FLOAT32                         m_f32TemplateBackgroundSum;
  FLOAT32                         m_f32SampleBackgroundSum;
  FLOAT32                         m_f32BackgroundSumTolerance;
                                  
  FLOAT32                         m_f32Correlation;
  FLOAT32                         m_f32CorrelationTolerance;
  
  // == Statistics  
  // Statistical moments
  FLOAT32                         m_f32ShiftXAverage;
  FLOAT32                         m_f32ShiftXDeviation;
  FLOAT32                         m_f32ShiftXMin;
  FLOAT32                         m_f32ShiftXMax;
  FLOAT32                         m_f32ShiftYAverage;
  FLOAT32                         m_f32ShiftYDeviation;
  FLOAT32                         m_f32ShiftYMin;
  FLOAT32                         m_f32ShiftYMax;
  FLOAT32                         m_f32ShearAverage;
  FLOAT32                         m_f32ShearDeviation;
  FLOAT32                         m_f32ShearMin;
  FLOAT32                         m_f32ShearMax;
  FLOAT32                         m_f32SkewAverage;
  FLOAT32                         m_f32SkewDeviation;
  FLOAT32                         m_f32SkewMin;
  FLOAT32                         m_f32SkewMax;
  FLOAT32                         m_f32ScaleXAverage;
  FLOAT32                         m_f32ScaleXDeviation;
  FLOAT32                         m_f32ScaleXMin;
  FLOAT32                         m_f32ScaleXMax;
  FLOAT32                         m_f32ScaleYAverage;
  FLOAT32                         m_f32ScaleYDeviation;
  FLOAT32                         m_f32ScaleYMin;
  FLOAT32                         m_f32ScaleYMax;
  FLOAT32                         m_f32ForegroundAreaAverage;
  FLOAT32                         m_f32ForegroundAreaDeviation;
  FLOAT32                         m_f32BackgroundAreaAverage;
  FLOAT32                         m_f32BackgroundAreaDeviation;
  FLOAT32                         m_f32ForegroundSumAverage;
  FLOAT32                         m_f32ForegroundSumDeviation;
  FLOAT32                         m_f32BackgroundSumAverage;
  FLOAT32                         m_f32BackgroundSumDeviation;
  FLOAT32                         m_f32CorrelationAverage;
  FLOAT32                         m_f32CorrelationDeviation;
  FLOAT32                         m_f32LocationScoreAverage;
  FLOAT32                         m_f32LocationScoreDeviation;
  
  // Drawing
  E_DLL0 void E_DLL1              Draw                      ( HDC hDC,
                                                              FLOAT32 f32ZoomX = 1.f, FLOAT32 f32ZoomY = 0.f,
                                                              FLOAT32 f32PanX = 0.f, FLOAT32 f32PanY = 0.f);
  E_DLL0 void E_DLL1              Draw                      ( Euresys::DrawAdapter* drawAdapter,
                                                              FLOAT32 f32ZoomX = 1.f, FLOAT32 f32ZoomY = 0.f,
                                                              FLOAT32 f32PanX = 0.f, FLOAT32 f32PanY = 0.f);
  
  
private:
  // == Template structure/geometry  
  // Character list
  EOCVCharVector                  m_Chars;
  
  // Total contour length
  UINT32                          m_un32TotalContourLength;
  
  // Bounding box
  INT32                           m_n32OrgX;
  INT32                           m_n32OrgY;
  INT32                           m_n32EndX;
  INT32                           m_n32EndY;
  FLOAT32                         m_f32HalfWidth;
  FLOAT32                         m_f32HalfHeight;
  
  // == Location
  // Location image 
  EImageBW8                       m_LocationImage;
  
  // Nominal position ( with respect to the template center)
  FLOAT32                         m_f32NominalX;
  FLOAT32                         m_f32NominalY;
  
  // Measured position ( with respect to the inspected ROI center)
  FLOAT32                         m_f32CenterX;
  FLOAT32                         m_f32CenterY;
  
  // == Statistics
  // Update
  void                            ClearStatistics           ( );
  void                            UpdateStatistics          ( );
  
  friend class EOCV;
  friend void Serialize( EOCVText& Value, FILE* pFile, BOOL bOutput, UINT32 un32Version);
};

///////////////////////////////////////////////////////////////////////////////
#endif //__EOCV_TEXT_H__
