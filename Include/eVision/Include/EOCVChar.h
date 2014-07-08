// EOCVChar.h: EasyOCV library header file for eVision 6.7.1.0
//
// Copyright ( c) 1997-2006, Euresys. All rights reserved.
//

#ifndef __EOCV_CHAR_H__
#define __EOCV_CHAR_H__

///////////////////////////////////////////////////////////////////////////////
#include <stdio.h>

///////////////////////////////////////////////////////////////////////////////
// eVision header files
#include "Easy.h"
#include "EOCVObjectVector.h"

///////////////////////////////////////////////////////////////////////////////
class E_DLL1 EOCVChar 
{
// Wrapping members
public:
  int handle_;
  FinalizeCallback callback_;

public:
  // == General
  // Construction and assignment + helpers
  E_DLL0 CONSTRUCTOR E_DLL1       EOCVChar                  ( );
  E_DLL0 CONSTRUCTOR E_DLL1       EOCVChar                  ( const EOCVChar& other);
  E_DLL0 EOCVChar& E_DLL1         operator=                 ( const EOCVChar& other);

private :
  void                            CopyTo                    ( EOCVChar* target) const;

public:
  // Initialization
  E_DLL0 void E_DLL1              ResetParameters           ( );
  
  // == Contrast  
  BOOL                            m_bWhiteOnBlack;
  
  // == Template edition  
  // Selection
  BOOL                            m_bSelected;/*GeneralMask*/
  
  // Objects list
  EOCVObjectVector                m_Objects;
  
  // == Location  
  // Location parameters
  UINT32                          m_un32NumContourPoints;/*GeneralMask*/
  
  // Relative tolerance
  FLOAT32                         m_f32RelativeTolerance;
  
  // Location score
  FLOAT32                         m_f32TemplateLocationScore;/*LocationScoreMask*/
  FLOAT32                         m_f32SampleLocationScore;/*LocationScoreMask*/
  FLOAT32                         m_f32LocationScoreTolerance;/*LocationScoreMask*/
  
  // Translation parameters
  FLOAT32                         m_f32ShiftX;/*ShiftXMask*/
  FLOAT32                         m_f32ShiftXBias;/*ShiftXMask*/
  FLOAT32                         m_f32ShiftXTolerance;/*ShiftXMask*/
  UINT32                          m_un32ShiftXStride;/*ShiftXMask*/

  FLOAT32                         m_f32ShiftY;/*ShiftYMask*/
  FLOAT32                         m_f32ShiftYBias;/*ShiftYMask*/
  FLOAT32                         m_f32ShiftYTolerance;/*ShiftYMask*/
  UINT32                          m_un32ShiftYStride;/*ShiftYMask*/
  
  // Inspected ROI
  EROIBW8                         m_InspectedRoi;
  
  // == Inspection  
  // Qualitative diagnostics
  UINT32                          m_un32Diagnostics;/*GeneralMask*/
  
  // Margin width
  UINT32                          m_un32MarginWidth;/*GeneralMask*/
  
  // Quality indicators
  UINT32                          m_un32TemplateForegroundArea;/*ForegroundAreaMask*/
  UINT32                          m_un32LearntTemplateForegroundArea;
  UINT32                          m_un32SampleForegroundArea;/*ForegroundAreaMask*/
  UINT32                          m_un32ForegroundAreaTolerance;/*ForegroundAreaMask*/
                                  
  UINT32                          m_un32TemplateBackgroundArea;/*BackgroundAreaMask*/
  UINT32                          m_un32LearntTemplateBackgroundArea;
  UINT32                          m_un32SampleBackgroundArea;/*BackgroundAreaMask*/
  UINT32                          m_un32BackgroundAreaTolerance;/*BackgroundAreaMask*/
                                  
  FLOAT32                         m_f32TemplateForegroundSum;/*ForegroundSumMask*/
  FLOAT32                         m_f32SampleForegroundSum;/*ForegroundSumMask*/
  FLOAT32                         m_f32ForegroundSumTolerance;/*ForegroundSumMask*/
                                  
  FLOAT32                         m_f32TemplateBackgroundSum;/*BackgroundSumMask*/
  FLOAT32                         m_f32SampleBackgroundSum;/*BackgroundSumMask*/
  FLOAT32                         m_f32BackgroundSumTolerance;/*BackgroundSumMask*/
                                  
  FLOAT32                         m_f32Correlation;/*CorrelationMask*/
  FLOAT32                         m_f32CorrelationTolerance;/*CorrelationMask*/
  
  // == Statistics  
  // Accumulators
  FLOAT32                         m_f32LocationScoreAverage;/*LocationScoreMask*/
  FLOAT32                         m_f32LocationScoreDeviation;/*LocationScoreMask*/

  FLOAT32                         m_f32ShiftXAverage;/*ShiftXMask*/
  FLOAT32                         m_f32ShiftXDeviation;/*ShiftXMask*/
  FLOAT32                         m_f32ShiftXMin;/*ShiftXMask*/
  FLOAT32                         m_f32ShiftXMax;/*ShiftXMask*/

  FLOAT32                         m_f32ShiftYAverage;/*ShiftYMask*/
  FLOAT32                         m_f32ShiftYDeviation;/*ShiftYMask*/
  FLOAT32                         m_f32ShiftYMin;/*ShiftYMask*/
  FLOAT32                         m_f32ShiftYMax;/*ShiftYMask*/

  FLOAT32                         m_f32ForegroundAreaAverage;/*ForegroundAreaMask*/
  FLOAT32                         m_f32ForegroundAreaDeviation;/*ForegroundAreaMask*/

  FLOAT32                         m_f32BackgroundAreaAverage;/*BackgroundAreaMask*/
  FLOAT32                         m_f32BackgroundAreaDeviation;/*BackgroundAreaMask*/

  FLOAT32                         m_f32ForegroundSumAverage;/*ForegroundSumMask*/
  FLOAT32                         m_f32ForegroundSumDeviation;/*ForegroundSumMask*/

  FLOAT32                         m_f32BackgroundSumAverage;/*BackgroundSumMask*/
  FLOAT32                         m_f32BackgroundSumDeviation;/*BackgroundSumMask*/

  FLOAT32                         m_f32CorrelationAverage;/*CorrelationMask*/
  FLOAT32                         m_f32CorrelationDeviation;/*CorrelationMask*/
  
  // Drawing
  E_DLL0 void E_DLL1              Draw                      ( HDC hDC,
                                                              FLOAT32 f32ZoomX = 1.f, FLOAT32 f32ZoomY = 0.f,
                                                              FLOAT32 f32PanX = 0.f, FLOAT32 f32PanY = 0.f);
  E_DLL0 void E_DLL1              Draw                      ( Euresys::DrawAdapter* drawAdapter,
                                                              FLOAT32 f32ZoomX = 1.f, FLOAT32 f32ZoomY = 0.f,
                                                              FLOAT32 f32PanX = 0.f, FLOAT32 f32PanY = 0.f);
  
private:
  // == Template structure/geometry  
  // Contour
  EPathVector                     m_Contour;
  
  // Bounding box
  INT32                           m_n32OrgX;
  INT32                           m_n32OrgY;
  INT32                           m_n32EndX;
  INT32                           m_n32EndY;
  FLOAT32                         m_f32HalfWidth;
  FLOAT32                         m_f32HalfHeight;
  
  // == Location  
  // Nominal position ( with respect to the text center)
  FLOAT32                         m_f32NominalX;
  FLOAT32                         m_f32NominalY;
  
  // Measured position ( with respect to the text center)
  FLOAT32                         m_f32CenterX;
  FLOAT32                         m_f32CenterY;
  
  // == Statistics
  // Update
  void                            ClearStatistics           ( );
  void                            UpdateStatistics          ( );
  
  friend class EOCV;
  friend void Serialize( EOCVChar& Value, FILE* pFile, BOOL bOutput, UINT32 un32Version);
};

///////////////////////////////////////////////////////////////////////////////
#endif //__EOCV_CHAR_H__
