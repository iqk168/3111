// EChecker.h: EasyOCV library header file for eVision 6.7.1.0
//
// Copyright ( c) 1997-2006, Euresys. All rights reserved.
//

#ifndef __ECHECKER_H__
#define __ECHECKER_H__

///////////////////////////////////////////////////////////////////////////////
#include <stdio.h>

///////////////////////////////////////////////////////////////////////////////
// eVision header files
#include "Easy.h"
#include "EMatch.h"
#include "EOCV_Enum.h"

///////////////////////////////////////////////////////////////////////////////
// Allowed degrees of freedom
enum OCV_DEGREES_OF_FREEDOM
{
  OCV_TRANSLATION = 0x1,
  OCV_ROTATION = 0x2,
  OCV_SCALING = 0x4,
  OCV_DEGREES_OF_FREEDOM_UNKNOWN  = 0xFFFFFFFF
};

///////////////////////////////////////////////////////////////////////////////
class EChecker
{
  // Wrapping members
public:
  int handle_;
  FinalizeCallback callback_;
public:
  // Matching contexts
  EMatch                          m_Match0;
  EMatch                          m_Match1;
  
  // Template images
  EImageBW8                       m_Low;
  EImageBW8                       m_High;
  
public:
  // Registered image
  EImageBW8                       m_Registered;
  
public:
  // Constructor
  E_DLL0 CONSTRUCTOR E_DLL1       EChecker                  ( );
  E_DLL0 DESTRUCTOR E_DLL1        ~EChecker                 ( );
  
  // Source image
  E_DLL0 void E_DLL1              Attach                    ( EROIBW8* pSrc);
  E_DLL0 EROIBW8* E_DLL1          GetSrcImage               ( ) { return m_pSrcImage; }
  
  // Search tolerances
  E_DLL0 UINT32 E_DLL1            GetToleranceX             ( ) { return m_un32ToleranceX; }
                                                            
  E_DLL0 UINT32 E_DLL1            GetToleranceY             ( ) { return m_un32ToleranceY; }

  E_DLL0 void E_DLL1              SetTolerance              ( UINT32 un32ToleranceX, UINT32 un32ToleranceY);
  
  // Statistics
  E_DLL0 UINT32 E_DLL1            GetNumAverageSamples      ( ) { return m_un32NumAverageSamples; }

  E_DLL0 UINT32 E_DLL1            GetNumDeviationSamples    ( ) { return m_un32NumDeviationSamples; }

  E_DLL0 enum OCV_NORMALIZATION_MODE E_DLL1  GetNormalize   ( ) { return m_eNormalize; }
  E_DLL0 void E_DLL1              SetNormalize              ( enum OCV_NORMALIZATION_MODE eNormalize) { m_eNormalize = eNormalize; }

  E_DLL0 FLOAT32 E_DLL1           GetAverage                ( ) { return m_f32Average; }
                                  
  E_DLL0 FLOAT32 E_DLL1           GetDeviation              ( ) { return m_f32Deviation; }

  // Allowed degrees of freedom
  E_DLL0 UINT32 E_DLL1            GetDegreesOfFreedom       ( ) { return m_un32DegreesOfFreedom; }
  E_DLL0 void E_DLL1              SetDegreesOfFreedom       ( UINT32 un32DegreesOfFreedom) { m_un32DegreesOfFreedom = un32DegreesOfFreedom; }
                                  
  // Learning                     
  E_DLL0 void E_DLL1              Register                  ( );
  E_DLL0 void E_DLL1              Learn                     ( enum OCV_LEARNING_MODES eMode);
                                  
  E_DLL0 FLOAT32 E_DLL1           GetRelativeTolerance      ( ) { return m_f32RelativeTolerance; }
  E_DLL0 void E_DLL1              SetRelativeTolerance      ( FLOAT32 f32RelativeTolerance) { m_f32RelativeTolerance = f32RelativeTolerance; }
                                  
  // Batch learning               
  E_DLL0 void E_DLL1              EmptyPathNames            ( );
  E_DLL0 void E_DLL1              AddPathName               ( const char* pszPathName);
  E_DLL0 void E_DLL1              BatchLearn                ( enum OCV_LEARNING_MODES eMode);
  
  // Learning ROIs
  EROIBW8                         m_LearnRoi0;
  EROIBW8                         m_LearnRoi1;
  
  // Searching ROIs
  EROIBW8                         m_MatchRoi0;
  EROIBW8                         m_MatchRoi1;
  
  // Inspected ROI
  EROIBW8                         m_InspectRoi;
  EROIBW8                         m_MaxInspectRoi;
  
  // Miscellaneous
  E_DLL0 FLOAT32 E_DLL1           GetDarkGray               ( ) { return m_f32DarkGray; }
  E_DLL0 void E_DLL1              SetDarkGray               ( FLOAT32 f32DarkGray) { m_f32DarkGray = f32DarkGray; }
                                  
  E_DLL0 FLOAT32 E_DLL1           GetLightGray              ( ) { return m_f32LightGray; }
  E_DLL0 void E_DLL1              SetLightGray              ( FLOAT32 f32LightGray) { m_f32LightGray = f32LightGray; }
                                  
  // Zooming and paning           
  E_DLL0 void E_DLL1              SetZoom                   ( FLOAT32 f32Zoom) { m_f32ZoomX = f32Zoom; m_f32ZoomY = f32Zoom; }
  E_DLL0 void E_DLL1              SetZoom                   ( FLOAT32 f32ZoomX, FLOAT32 f32ZoomY) { m_f32ZoomX = f32ZoomX; m_f32ZoomY = f32ZoomY; }
  E_DLL0 void E_DLL1              SetPan                    ( FLOAT32 f32PanX, FLOAT32 f32PanY) { m_f32PanX = f32PanX; m_f32PanY = f32PanY; }
                                                            
  E_DLL0 FLOAT32 E_DLL1           GetZoomX                  ( ) { return m_f32ZoomX; }
                                                            
  E_DLL0 FLOAT32 E_DLL1           GetZoomY                  ( ) { return m_f32ZoomY; }
                                                            
  E_DLL0 FLOAT32 E_DLL1           GetPanX                   ( ) { return m_f32PanX; }
                                                            
  E_DLL0 FLOAT32 E_DLL1           GetPanY                   ( ) { return m_f32PanY; }
                                                            
  // Drawing                                                
  E_DLL0 void E_DLL1              Draw                      ( HDC hDC,
                                                              enum OCV_DRAWING_MODES eDrawingMode,
                                                              BOOL bHandles = FALSE,
                                                              FLOAT32 f32ZoomX = 1, FLOAT32 f32ZoomY = 0,
                                                              FLOAT32 f32PanX = 0, FLOAT32 f32PanY = 0);

  E_DLL0 void E_DLL1              Draw                      ( Euresys::DrawAdapter* drawAdapter,
                                                              enum OCV_DRAWING_MODES eDrawingMode,
                                                              BOOL bHandles = FALSE,
                                                              FLOAT32 f32ZoomX = 1, FLOAT32 f32ZoomY = 0,
                                                              FLOAT32 f32PanX = 0, FLOAT32 f32PanY = 0);
  
  E_DLL0 BOOL E_DLL1              HitTest                   ( INT32 n32X, INT32 n32Y);
  E_DLL0 enum E_HANDLES E_DLL1    GetHitHandle              ( ) { return m_eHitHandle; }
  E_DLL0 enum ROI_HIT E_DLL1      GetHitRoi                 ( ) { return m_eHitRoi; }
  
  E_DLL0 void E_DLL1              Drag                      ( INT32 n32X, INT32 n32Y);
  E_DLL0 void E_DLL1              Drag                      ( INT32 n32X, INT32 n32Y, enum ROI_HIT eHitRoi, enum E_HANDLES eHitHandle);
                                                            
  // Serialization                                          
  E_DLL0 void E_DLL1              Load                      ( const char* pszPathName);
  E_DLL0 void E_DLL1              Load                      ( const UNICHAR* pszPathName);
                                                            
  E_DLL0 void E_DLL1              Save                      ( const char* pszPathName);
  E_DLL0 void E_DLL1              Save                      ( const UNICHAR* pszPathName);
  
protected:
  // Serialization
  virtual E_DLL0 void E_DLL1      Serialize                 ( FILE* pFile, BOOL bOutput, UINT32 un32Version);
  
  UINT32                          m_un32ToleranceX; 
  UINT32                          m_un32ToleranceY; 
  UINT32                          m_un32NumAverageSamples; 
  UINT32                          m_un32NumDeviationSamples; 
  enum OCV_NORMALIZATION_MODE     m_eNormalize; 
  FLOAT32                         m_f32Average; 
  FLOAT32                         m_f32Deviation; 
  UINT32                          m_un32DegreesOfFreedom; 
  FLOAT32                         m_f32RelativeTolerance; 
  FLOAT32                         m_f32DarkGray; 
  FLOAT32                         m_f32LightGray; 
  FLOAT32                         m_f32ZoomX; 
  FLOAT32                         m_f32ZoomY; 
  FLOAT32                         m_f32PanX; 
  FLOAT32                         m_f32PanY; 

private:
  // Internal state
  enum OCV_LEARNING_MODES         m_eState;
  
  // Accumulation images
  EImageBW16                      m_Sum;
  EImageBW32                      m_SumSum;
  
  // Source image
  EROIBW8*                        m_pSrcImage;
  
  // Registration
  FLOAT32                         m_f32SrcPivotX;
  FLOAT32                         m_f32SrcPivotY;
  FLOAT32                         m_f32DstPivotX;
  FLOAT32                         m_f32DstPivotY;
  FLOAT32                         m_f32Angle;
  FLOAT32                         m_f32Scale;
  void                            Isometry                  ( FLOAT32 f32SrcPivot0X, FLOAT32 f32SrcPivot0Y, 
                                                              FLOAT32 f32SrcPivot1X, FLOAT32 f32SrcPivot1Y,
    
                                                              FLOAT32 f32DstPivot0X, FLOAT32 f32DstPivot0Y,
                                                              FLOAT32 f32DstPivot1X, FLOAT32 f32DstPivot1Y);

  // Learning image set
  EVectorTemplate<char*>          m_PathNames;
  
  // Dragging
  enum E_HANDLES                  m_eHitHandle;
  enum ROI_HIT                    m_eHitRoi;
};

///////////////////////////////////////////////////////////////////////////////
#endif //__ECHECKER_H__
