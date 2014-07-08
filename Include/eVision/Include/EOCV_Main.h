// EOCV_Main.h: EasyOCV library header file for eVision 6.7.1.0
//
// Copyright ( c) 1997-2006, Euresys. All rights reserved.
//

#ifndef __EOCV_MAIN_H__
#define __EOCV_MAIN_H__

///////////////////////////////////////////////////////////////////////////////
#include <stdio.h>

///////////////////////////////////////////////////////////////////////////////
// eVision header files
#include "Easy.h"
#include "EImage.h"
#include "EObject.h"
#include "EOCV_Enum.h"
#include "EOCVChar.h"
#include "EOCVText.h"
#include "EOCVObjectVector.h"
#include "EOCVCharVector.h"
#include "EOCVTextVector.h"

///////////////////////////////////////////////////////////////////////////////
class E_DLL1 EOCV 
{
// Wrapping members
public:
  int handle_;
  FinalizeCallback callback_;
public:
  
  // == General
  // Constructor/destructor
  E_DLL0 CONSTRUCTOR E_DLL1       EOCV                      ( );
  virtual E_DLL0 DESTRUCTOR E_DLL1 ~EOCV                    ( );
  
  // Default parameters
  E_DLL0 FLOAT32 E_DLL1           GetRelativeTolerance      ( ) { return m_f32RelativeTolerance; }
  E_DLL0 void E_DLL1              SetRelativeTolerance      ( FLOAT32 f32RelativeTolerance) { m_f32RelativeTolerance = f32RelativeTolerance; }
                                                            
  E_DLL0 void E_DLL1              ComputeDefaultTolerances  ( EROIBW8 *pRoi, UINT32 un32Threshold = IMG_MIN_RESIDUE_THRESHOLD);
                                                            
  // Debugging                                              
  E_DLL0 void E_DLL1              Dump                      ( );
                                                            
  // Serialization                                          
  E_DLL0 void E_DLL1              Load                      ( const char* pszPathName);
  E_DLL0 void E_DLL1              Load                      ( const UNICHAR* pszPathName);
                                                            
  E_DLL0 void E_DLL1              Save                      ( const char* pszPathName);
  E_DLL0 void E_DLL1              Save                      ( const UNICHAR* pszPathName);
                                                            
  virtual E_DLL0 void E_DLL1      Serialize                 ( FILE*  pFile, BOOL bOutput, UINT32 un32Version);
                                                            
  // == Template structure/geometry                         
  // Template image                                         
  EImageBW8                       m_TemplateImage;          
                                                            
  // Pixels size                                            
  FLOAT32                         m_f32PixelWidth;          
  FLOAT32                         m_f32PixelHeight;         
                                                            
  // Free objects list                                      
  EOCVObjectVector                m_FreeObjects;            
                                                            
  // Free objects drawing                                   
  E_DLL0 void E_DLL1              DrawTemplateObjects       ( HDC hDC,
                                                              enum E_SELECTION_MODE eObjectsSelectionMode = E_SELECTED_TRUE,
                                                              FLOAT32 f32ZoomX = 1.f, FLOAT32 f32ZoomY = 0.f,
                                                              FLOAT32 f32PanX = 0.f, FLOAT32 f32PanY = 0.f);
                                                            
  E_DLL0 void E_DLL1              DrawTemplateObjects       ( Euresys::DrawAdapter* drawAdapter,
                                                              enum E_SELECTION_MODE eObjectsSelectionMode = E_SELECTED_TRUE,
                                                              FLOAT32 f32ZoomX = 1.f, FLOAT32 f32ZoomY = 0.f,
                                                              FLOAT32 f32PanX = 0.f, FLOAT32 f32PanY = 0.f);
                                                            
  // Free characters list                                   
  EOCVCharVector                  m_FreeChars;              
                                                            
  // Free characters drawing                                
  E_DLL0 void E_DLL1              DrawTemplateChars         ( HDC hDC,
                                                              enum E_SELECTION_MODE eCharsSelectionMode = E_SELECTED_TRUE,
                                                              FLOAT32 f32ZoomX = 1.f, FLOAT32 f32ZoomY = 0.f,
                                                              FLOAT32 f32PanX = 0.f, FLOAT32 f32PanY = 0.f);
                                                            
  E_DLL0 void E_DLL1              DrawTemplateChars         ( Euresys::DrawAdapter* drawAdapter,
                                                              enum E_SELECTION_MODE eCharsSelectionMode = E_SELECTED_TRUE,
                                                              FLOAT32 f32ZoomX = 1.f, FLOAT32 f32ZoomY = 0.f,
                                                              FLOAT32 f32PanX = 0.f, FLOAT32 f32PanY = 0.f);
                                                            
  // Texts list                                             
  EOCVTextVector                  m_Texts;                  
                                                            
  // Drawing                                                
  E_DLL0 void E_DLL1              DrawTemplateTexts         ( HDC hDC,
                                                              enum E_SELECTION_MODE eTextsSelectionMode = E_SELECTED_TRUE,
                                                              FLOAT32 f32ZoomX = 1.f, FLOAT32 f32ZoomY = 0.f,
                                                              FLOAT32 f32PanX = 0.f, FLOAT32 f32PanY = 0.f);
  E_DLL0 void E_DLL1              DrawTemplateTexts         ( Euresys::DrawAdapter* drawAdapter,
                                                              enum E_SELECTION_MODE eTextsSelectionMode = E_SELECTED_TRUE,
                                                              FLOAT32 f32ZoomX = 1.f, FLOAT32 f32ZoomY = 0.f,
                                                              FLOAT32 f32PanX = 0.f, FLOAT32 f32PanY = 0.f);
                                                            
  E_DLL0 void E_DLL1              DrawTemplateTextsChars    ( HDC hDC,    
                                                              enum E_SELECTION_MODE eTextsSelectionMode = E_SELECTED_TRUE,
                                                              enum E_SELECTION_MODE eCharsSelectionMode = E_SELECTED_TRUE,
                                                              FLOAT32 f32ZoomX = 1.f, FLOAT32 f32ZoomY = 0.f,
                                                              FLOAT32 f32PanX = 0.f, FLOAT32 f32PanY = 0.f);
  E_DLL0 void E_DLL1              DrawTemplateTextsChars    ( Euresys::DrawAdapter* drawAdapter,    
                                                              enum E_SELECTION_MODE eTextsSelectionMode = E_SELECTED_TRUE,
                                                              enum E_SELECTION_MODE eCharsSelectionMode = E_SELECTED_TRUE,
                                                              FLOAT32 f32ZoomX = 1.f, FLOAT32 f32ZoomY = 0.f,
                                                              FLOAT32 f32PanX = 0.f, FLOAT32 f32PanY = 0.f);
                                                            
  // == Template edition          
  // Template image reference     
  EROIBW8                         *m_pTemplateImage;
  EROIBW8                         *m_pTemplateObjectsImage;
  E_DLL0 void E_DLL1              SetTemplateImage          ( EROIBW8* pImage, EROIBW8* pObjectsImage = NULL);
  E_DLL0 EROIBW8* E_DLL1          GetTemplateImage          ( void);
  E_DLL0 EROIBW8* E_DLL1          GetTemplateObjectsImage   ( void);
                                                            
  // Coded image reference                                  
  ECodedImage                     *m_pCodedImage;                               
                                                            
  // Free objects management                                
  E_DLL0 void E_DLL1              CreateTemplateObjects     ( ECodedImage* pCodedImage,
                                                              enum E_SELECTION_MODE eCodedObjectsSelectionMode = E_SELECTED_TRUE);
  E_DLL0 void E_DLL1              SelectTemplateObjects     ( INT32 n32OrgX, INT32 n32OrgY, INT32 n32Width, INT32 n32Height,
                                                              enum E_SELECTION_MODE eObjectsSelectionMode = E_SELECTED_ANY);
  E_DLL0 void E_DLL1              DeleteTemplateObjects     ( enum E_SELECTION_MODE eObjectsSelectionMode = E_SELECTED_TRUE);
                                                            
  // Free characters management                             
  E_DLL0 void E_DLL1              CreateTemplateChars       ( enum E_SELECTION_MODE eObjectsSelectionMode = E_SELECTED_TRUE,
                                                              enum OCV_CHAR_CREATION_MODES eCreationMode = OCV_CREATE_CHAR_OVERLAP);
  E_DLL0 void E_DLL1              SelectTemplateChars       ( INT32 n32OrgX, INT32 n32OrgY, INT32 n32Width, INT32 n32Height,
                                                              enum E_SELECTION_MODE eCharsSelectionMode = E_SELECTED_ANY);
  E_DLL0 void E_DLL1              DeleteTemplateChars       ( enum E_SELECTION_MODE eCharsSelectionMode = E_SELECTED_TRUE);
                                                            
  // Texts management                                       
  E_DLL0 void E_DLL1              CreateTemplateTexts       ( enum E_SELECTION_MODE eCharsSelectionMode = E_SELECTED_TRUE);
  E_DLL0 void E_DLL1              SelectTemplateTexts       ( INT32 n32OrgX, INT32 n32OrgY, INT32 n32Width, INT32 n32Height,
                                                              enum E_SELECTION_MODE eTextsSelectionMode = E_SELECTED_ANY);
  E_DLL0 void E_DLL1              DeleteTemplateTexts       ( enum E_SELECTION_MODE eTextsSelectionMode = E_SELECTED_TRUE);
                                                            
  // Texts selection                                        
  E_DLL0 void E_DLL1              SelectSampleTexts         ( INT32 n32OrgX, INT32 n32OrgY, INT32 n32Width, INT32 n32Height,
                                                              enum E_SELECTION_MODE eTextsSelectionMode = E_SELECTED_ANY);
  E_DLL0 void E_DLL1              SelectSampleTextsChars    ( INT32 n32OrgX, INT32 n32OrgY, INT32 n32Width, INT32 n32Height,
                                                              enum E_SELECTION_MODE eTextsSelectionMode = E_SELECTED_ANY,
                                                              enum E_SELECTION_MODE eCharsSelectionMode = E_SELECTED_ANY);
                                                            
  // Learning                                               
  E_DLL0 void E_DLL1              Learn                     ( EROIBW8* pImage,
                                                              enum E_SELECTION_MODE eTextsSelectionMode = E_SELECTED_TRUE,
                                                              enum E_SELECTION_MODE eCharsSelectionMode = E_SELECTED_TRUE);
                                                            
  // == Contrast                                            
  // Histogram analysis                                     
  EBWHistogramVector              m_Histogram;              
                                                            
  // Template contrast                                      
  E_DLL0 BOOL E_DLL1              GetWhiteOnBlack           ( ) { return m_bWhiteOnBlack; }
  E_DLL0 void E_DLL1              SetWhiteOnBlack           ( BOOL bWhiteOnBlack) { m_bWhiteOnBlack = bWhiteOnBlack; }
                                  
  EBW8                            m_bw8TemplateThreshold;
  FLOAT32                         m_f32TemplateBackground;
  FLOAT32                         m_f32TemplateForeground;
                                  
  // Sample contrast              
  EBW8                            m_bw8SampleThreshold;
  FLOAT32                         m_f32SampleBackground;
  FLOAT32                         m_f32SampleForeground;
  
  // Global contrast
  E_DLL0 FLOAT32 E_DLL1           GetSampleContrast         ( );
  E_DLL0 FLOAT32 E_DLL1           GetContrastAverage        ( );
  E_DLL0 FLOAT32 E_DLL1           GetContrastDeviation      ( );
  E_DLL0 void E_DLL1              SetContrastTolerance      ( FLOAT32);
  E_DLL0 FLOAT32 E_DLL1           GetContrastTolerance      ( );  
  E_DLL0 FLOAT32 E_DLL1           GetTemplateContrast       ( );
  
  // Global quality indicators
  E_DLL0 UINT32 E_DLL1            GetBackgroundAreaTolerance( );
  E_DLL0 void E_DLL1              SetBackgroundAreaTolerance( UINT32 un32Tolerance);
  E_DLL0 FLOAT32 E_DLL1           GetBackgroundAreaAverage  ( );
  E_DLL0 FLOAT32 E_DLL1           GetBackgroundAreaDeviation( );
                                  
  E_DLL0 UINT32 E_DLL1            GetForegroundAreaTolerance( );
  E_DLL0 void E_DLL1              SetForegroundAreaTolerance( UINT32 un32Tolerance);
  E_DLL0 FLOAT32 E_DLL1           GetForegroundAreaAverage  ( );
  E_DLL0 FLOAT32 E_DLL1           GetForegroundAreaDeviation( );
                                  
  E_DLL0 FLOAT32 E_DLL1           GetBackgroundSumTolerance ( );
  E_DLL0 void E_DLL1              SetBackgroundSumTolerance ( FLOAT32 f32Tolerance);
  E_DLL0 FLOAT32 E_DLL1           GetBackgroundSumAverage   ( );
  E_DLL0 FLOAT32 E_DLL1           GetBackgroundSumDeviation ( );
                                  
  E_DLL0 FLOAT32 E_DLL1           GetForegroundSumTolerance ( );
  E_DLL0 void E_DLL1              SetForegroundSumTolerance ( FLOAT32 f32Tolerance);
  E_DLL0 FLOAT32 E_DLL1           GetForegroundSumAverage   ( );
  E_DLL0 FLOAT32 E_DLL1           GetForegroundSumDeviation ( );
  
  // == Location
  // Sample image reference
  EImageBW8                       *m_pSampleImage;
  
  // Location image
  EImageBW8                       m_LocationImage;
  
  // Absolute position with respect to the sample image
  FLOAT32                         m_f32CenterX;
  FLOAT32                         m_f32CenterY;
  
  // Location options
  enum OCV_LOCATION_MODE          m_eLocationMode;
  E_DLL0 BOOL E_DLL1              GetReduceLocationScore    ( ) { return m_bReduceLocationScore; }
  E_DLL0 void E_DLL1              SetReduceLocationScore    ( BOOL bReduceLocationScore) { m_bReduceLocationScore = bReduceLocationScore; }
                                  
  E_DLL0 BOOL E_DLL1              GetNormalizeLocationScore ( ) { return m_bNormalizeLocationScore; }
  E_DLL0 void E_DLL1              SetNormalizeLocationScore ( BOOL bNormalizeLocationScore) { m_bNormalizeLocationScore = bNormalizeLocationScore; }
                                  
  E_DLL0 BOOL E_DLL1              GetAccurateTextsLocationScores( ) { return m_bAccurateTextsLocationScores; }
  E_DLL0 void E_DLL1              SetAccurateTextsLocationScores( BOOL bAccurateTextsLocationScores) { m_bAccurateTextsLocationScores = bAccurateTextsLocationScores; }

  // Location shape
  INT32                           m_n32ShapeXMin;
  INT32                           m_n32ShapeXMax;
  INT32                           m_n32ShapeYMin;
  INT32                           m_n32ShapeYMax;
  EINT32Vector                    m_WhiteShape;
  EINT32Vector                    m_BlackShape;
  
  // Regions of interest
  void                            BoundTextRois             ( );
  static void                     Bound                     ( FLOAT32& f32XMin,   FLOAT32& f32XMax,
                                                              FLOAT32& f32YMin,   FLOAT32& f32YMax,
                                                              FLOAT32 f32X,       FLOAT32 f32Y,
                                                              FLOAT32 f32ScaleX,  FLOAT32 f32ScaleY,
                                                              FLOAT32 f32Shear,   FLOAT32 f32Skew,
                                                              FLOAT32 f32ShiftX,  FLOAT32 f32ShiftY);
  
  // Geometric transform
  static void                     TransformCoefficients     ( FLOAT32 f32ScaleX, FLOAT32 f32ScaleY,
                                                              FLOAT32 f32Shear, FLOAT32 f32Skew,
                                                              FLOAT32 f32ShiftX, FLOAT32 f32ShiftY,
                                                              FLOAT32& f32Axx, FLOAT32& f32Axy, FLOAT32& f32Ax,
                                                              FLOAT32& f32Ayx, FLOAT32& f32Ayy, FLOAT32& f32Ay);
  void                            TextToShape               ( EOCVText& Text,
                                                              FLOAT32 f32ScaleX, FLOAT32 f32ScaleY,
                                                              FLOAT32 f32Shear, FLOAT32 f32Skew,
                                                              EROIBW8& Image);
  void                            CharToShape               ( EOCVText& Text, EOCVChar& Char, EROIBW8& Image);
  
  // Geometric search
  void                            LocateText                ( EOCVText& Text);
  void                            BestShapeTranslation      ( EROIBW8& Image,
                                                              INT32& n32BestX, INT32& n32BestY,
                                                              UINT32& un32BestScore,
                                                              UINT32 un32XStride, UINT32 un32YStride);
  void                            BestTextTransform         ( EOCVText& Text);
  void                            BestCharsTranslation      ( EOCVText& Text);
  
  E_DLL0 UINT32 E_DLL1            GetNumTexts               ( );
  E_DLL0 void E_DLL1              GetTextParameters         ( EOCVText& Text, UINT32 un32TextIndex);
  E_DLL0 void E_DLL1              SetTextParameters         ( EOCVText& Text, UINT32 un32TextIndex);
  E_DLL0 void E_DLL1              GatherTextsParameters     ( EOCVText& Text, enum E_SELECTION_MODE eTextsSelectionMode);
  E_DLL0 void E_DLL1              ScatterTextsParameters    ( EOCVText& Text, enum E_SELECTION_MODE eTextsSelectionMode);
  
  E_DLL0 UINT32 E_DLL1            GetNumTextChars           ( UINT32 un32TextIndex);
  E_DLL0 void E_DLL1              GetTextCharParameters     ( EOCVChar& Char, UINT32 un32TextIndex, UINT32 un32CharIndex);
  E_DLL0 void E_DLL1              SetTextCharParameters     ( EOCVChar& Char, UINT32 un32TextIndex, UINT32 un32CharIndex);
  E_DLL0 void E_DLL1              GatherTextsCharsParameters( EOCVChar& Char,
                                                              enum E_SELECTION_MODE eTextsSelectionMode,
                                                              enum E_SELECTION_MODE eCharsSelectionMode);
  E_DLL0 void E_DLL1              ScatterTextsCharsParameters( EOCVChar& Char, 
                                                              enum E_SELECTION_MODE eTextsSelectionMode,
                                                              enum E_SELECTION_MODE eCharsSelectionMode);
  
  // Parameters selection flags
  UINT32                          m_un32GeneralMask;
  UINT8                           m_un8LocationScoreMask;
  UINT8                           m_un8ShiftXMask;
  UINT8                           m_un8ShiftYMask;
  UINT8                           m_un8SkewMask;
  UINT8                           m_un8ScaleXMask;
  UINT8                           m_un8ScaleYMask;
  UINT8                           m_un8ShearMask;
  UINT8                           m_un8ForegroundAreaMask;
  UINT8                           m_un8BackgroundAreaMask;
  UINT8                           m_un8ForegroundSumMask;
  UINT8                           m_un8BackgroundSumMask;
  UINT8                           m_un8CorrelationMask;
  
  // Sample text drawing
  E_DLL0 void E_DLL1              DrawTextRoi               ( HDC hDC, EOCVText& Text,
                                                              FLOAT32 f32ZoomX = 1.f, FLOAT32 f32ZoomY = 0.f,
                                                              FLOAT32 f32PanX = 0.f, FLOAT32 f32PanY = 0.f);
  E_DLL0 void E_DLL1              DrawTextRoi               ( Euresys::DrawAdapter* drawAdapter, EOCVText& Text,
                                                              FLOAT32 f32ZoomX = 1.f, FLOAT32 f32ZoomY = 0.f,
                                                              FLOAT32 f32PanX = 0.f, FLOAT32 f32PanY = 0.f);

  E_DLL0 void E_DLL1              DrawTextsRois             ( HDC hDC,
                                                              enum E_SELECTION_MODE eTextsSelectionMode = E_SELECTED_TRUE,
                                                              FLOAT32 f32ZoomX = 1.f, FLOAT32 f32ZoomY = 0.f,
                                                              FLOAT32 f32PanX = 0.f, FLOAT32 f32PanY = 0.f);
  E_DLL0 void E_DLL1              DrawTextsRois             ( Euresys::DrawAdapter* drawAdapter,
                                                              enum E_SELECTION_MODE eTextsSelectionMode = E_SELECTED_TRUE,
                                                              FLOAT32 f32ZoomX = 1.f, FLOAT32 f32ZoomY = 0.f,
                                                              FLOAT32 f32PanX = 0.f, FLOAT32 f32PanY = 0.f);
  
  E_DLL0 void E_DLL1              DrawText                  ( HDC hDC, EOCVText& Text,
                                                              FLOAT32 f32ZoomX = 1.f, FLOAT32 f32ZoomY = 0.f,
                                                              FLOAT32 f32PanX = 0.f, FLOAT32 f32PanY = 0.f);
  E_DLL0 void E_DLL1              DrawText                  ( Euresys::DrawAdapter* drawAdapter, EOCVText& Text,
                                                              FLOAT32 f32ZoomX = 1.f, FLOAT32 f32ZoomY = 0.f,
                                                              FLOAT32 f32PanX = 0.f, FLOAT32 f32PanY = 0.f);

  E_DLL0 void E_DLL1              DrawTexts                 ( HDC hDC,
                                                              enum E_SELECTION_MODE eTextsSelectionMode = E_SELECTED_TRUE,
                                                              FLOAT32 f32ZoomX = 1.f, FLOAT32 f32ZoomY = 0.f,
                                                              FLOAT32 f32PanX = 0.f, FLOAT32 f32PanY = 0.f);
  E_DLL0 void E_DLL1              DrawTexts                 ( Euresys::DrawAdapter* drawAdapter,
                                                              enum E_SELECTION_MODE eTextsSelectionMode = E_SELECTED_TRUE,
                                                              FLOAT32 f32ZoomX = 1.f, FLOAT32 f32ZoomY = 0.f,
                                                              FLOAT32 f32PanX = 0.f, FLOAT32 f32PanY = 0.f);

  E_DLL0 void E_DLL1              GetTextPoint              ( UINT32 un32TextIndex, INT32& n32X, INT32& n32Y, 
                                                              FLOAT32 f32ReducedX = 0.f, FLOAT32 f32ReducedY = 0.f, 
                                                              FLOAT32 f32ZoomX = 1.f, FLOAT32 f32ZoomY = 0.f,
                                                              FLOAT32 f32PanX = 0.f, FLOAT32 f32PanY = 0.f);
  
  
  // Sample texts characters drawing
  E_DLL0 void E_DLL1              DrawTextCharRoi           ( HDC hDC, EOCVText& Text, EOCVChar& Char,
                                                              FLOAT32 f32ZoomX = 1.f, FLOAT32 f32ZoomY = 0.f,
                                                              FLOAT32 f32PanX = 0.f, FLOAT32 f32PanY = 0.f);
  E_DLL0 void E_DLL1              DrawTextCharRoi           ( Euresys::DrawAdapter* drawAdapter, EOCVText& Text, EOCVChar& Char,
                                                              FLOAT32 f32ZoomX = 1.f, FLOAT32 f32ZoomY = 0.f,
                                                              FLOAT32 f32PanX = 0.f, FLOAT32 f32PanY = 0.f);
                                  
  E_DLL0 void E_DLL1              DrawTextsCharsRois        ( HDC hDC,
                                                              enum E_SELECTION_MODE eTextsSelectionMode = E_SELECTED_TRUE,
                                                              enum E_SELECTION_MODE eCharsSelectionMode = E_SELECTED_TRUE,
                                                              FLOAT32 f32ZoomX = 1.f, FLOAT32 f32ZoomY = 0.f, FLOAT32 f32PanX = 0.f, FLOAT32 f32PanY = 0.f);
  E_DLL0 void E_DLL1              DrawTextsCharsRois        ( Euresys::DrawAdapter* drawAdapter,
                                                              enum E_SELECTION_MODE eTextsSelectionMode = E_SELECTED_TRUE,
                                                              enum E_SELECTION_MODE eCharsSelectionMode = E_SELECTED_TRUE,
                                                              FLOAT32 f32ZoomX = 1.f, FLOAT32 f32ZoomY = 0.f, FLOAT32 f32PanX = 0.f, FLOAT32 f32PanY = 0.f);
                                  
  E_DLL0 void E_DLL1              DrawTextChars             ( HDC hDC, EOCVText& Text,
                                                              enum E_SELECTION_MODE eCharsSelectionMode = E_SELECTED_TRUE,
                                                              FLOAT32 f32ZoomX = 1.f, FLOAT32 f32ZoomY = 0.f, FLOAT32 f32PanX = 0.f, FLOAT32 f32PanY = 0.f);
  E_DLL0 void E_DLL1              DrawTextChars             ( Euresys::DrawAdapter* drawAdapter, EOCVText& Text,
                                                              enum E_SELECTION_MODE eCharsSelectionMode = E_SELECTED_TRUE,
                                                              FLOAT32 f32ZoomX = 1.f, FLOAT32 f32ZoomY = 0.f, FLOAT32 f32PanX = 0.f, FLOAT32 f32PanY = 0.f);
                                  
  E_DLL0 void E_DLL1              DrawTextsChars            ( HDC hDC,
                                                              enum E_SELECTION_MODE eTextsSelectionMode = E_SELECTED_TRUE,
                                                              enum E_SELECTION_MODE eCharsSelectionMode = E_SELECTED_TRUE,
                                                              FLOAT32 f32ZoomX = 1.f, FLOAT32 f32ZoomY = 0.f, FLOAT32 f32PanX = 0.f, FLOAT32 f32PanY = 0.f);
  E_DLL0 void E_DLL1              DrawTextsChars            ( Euresys::DrawAdapter* drawAdapter,
                                                              enum E_SELECTION_MODE eTextsSelectionMode = E_SELECTED_TRUE,
                                                              enum E_SELECTION_MODE eCharsSelectionMode = E_SELECTED_TRUE,
                                                              FLOAT32 f32ZoomX = 1.f, FLOAT32 f32ZoomY = 0.f, FLOAT32 f32PanX = 0.f, FLOAT32 f32PanY = 0.f);
                                  
  E_DLL0 void E_DLL1              GetTextCharPoint          ( UINT32 un32TextIndex, UINT32 un32CharIndex, INT32& n32X, INT32& n32Y, 
                                                              FLOAT32 f32ReducedX = 0.f, FLOAT32 f32ReducedY = 0.f, 
                                                              FLOAT32 f32ZoomX = 1.f, FLOAT32 f32ZoomY = 0.f, FLOAT32 f32PanX = 0.f, FLOAT32 f32PanY = 0.f);
  
  // == Inspection
  // Quality indicators selection
  UINT32                          m_un32UsedQualityIndicators;
  E_DLL0 UINT32 E_DLL1            GetUsedQualityIndicators  ( );
  E_DLL0 void E_DLL1              SetUsedQualityIndicators  ( UINT32 un32UsedQualityIndicators);
  
  // Geometric matching mode
  BOOL                            m_bResampleChars;
  E_DLL0 BOOL E_DLL1              GetResampleChars          ( );
  E_DLL0 void E_DLL1              SetResampleChars          ( BOOL bResampleChars);
  
  // Qualitative diagnostics
  UINT32                          m_un32Diagnostics;
  E_DLL0 UINT32 E_DLL1            GetDiagnostics            ( );
  
  // Inspection
  E_DLL0 void E_DLL1              Inspect                   ( EROIBW8* pSampleImage, UINT32 un32Threshold);
  
  // Rating
  void                            RateTemplate              ( );
  void                            RateSample                ( );
  void                            RateTemplateText          ( EOCVText& Text);
  void                            RateSampleText            ( EOCVText& Text);
  void                            RateTemplateTextChar      ( EOCVText& Text, EOCVChar& Char);
  void                            RateSampleTextChar        ( EOCVText& Text, EOCVChar& Char);
  
  // == Statistics
  // Count
  UINT32                          m_un32Count;
  E_DLL0 UINT32 E_DLL1            GetStatisticsCount        ( );
                                  
  // Updating                     
  E_DLL0 void E_DLL1              ClearStatistics           ( );
  E_DLL0 void E_DLL1              UpdateStatistics          ( );
  
  
  // == Adjustments
  
  // Shift tolerances from inspection ROI
  E_DLL0 void E_DLL1              AdjustShiftTolerances     ( EROIBW8 *pRoi);
  
  // Model updating from statistics
  E_DLL0 void E_DLL1              AdjustQualityRanges       ( FLOAT32 f32Factor);
  E_DLL0 void E_DLL1              AdjustTextsLocationRanges ( FLOAT32 f32Factor = 1.2, 
                                                              enum E_SELECTION_MODE eSelection = E_SELECTED_TRUE);
  E_DLL0 void E_DLL1              AdjustTextsQualityRanges  ( FLOAT32 f32Factor = 3.3, 
                                                              enum E_SELECTION_MODE eSelection = E_SELECTED_TRUE);
  E_DLL0 void E_DLL1              AdjustCharsLocationRanges ( FLOAT32 f32Factor = 1.2,
                                                              enum E_SELECTION_MODE eTextSelection = E_SELECTED_TRUE,
                                                              enum E_SELECTION_MODE eCharSelection = E_SELECTED_TRUE);
  E_DLL0 void E_DLL1              AdjustCharsQualityRanges  ( FLOAT32 f32Factor = 3.3,
                                                              enum E_SELECTION_MODE eTextSelection = E_SELECTED_TRUE,
                                                               enum E_SELECTION_MODE eCharSelection = E_SELECTED_TRUE);  
  
protected:
  FLOAT32                         m_f32RelativeTolerance; 
  BOOL                            m_bWhiteOnBlack; 
  BOOL                            m_bReduceLocationScore; 
  BOOL                            m_bNormalizeLocationScore; 
  BOOL                            m_bAccurateTextsLocationScores; 

   // Learning ROI placement
  UINT32                          m_un32LearningRoiHeight;
  UINT32                          m_un32LearningRoiWidth;
                                  
  UINT32                          GetTotalChars             ( );
  FLOAT32                         m_f32ContrastSum;
  FLOAT32                         m_f32ContrastSquareSum;  
  
  // Global contrast
  FLOAT32                         m_f32TemplateContrast;
  FLOAT32                         m_f32SampleContrast;
  FLOAT32                         m_f32ContrastAverage;
  FLOAT32                         m_f32ContrastDeviation;
  FLOAT32                         m_f32ContrastTolerance;
  
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
  
  // Statistics
  FLOAT32                         m_f32ForegroundAreaAverage;
  FLOAT32                         m_f32ForegroundAreaDeviation;
  FLOAT32                         m_f32BackgroundAreaAverage;
  FLOAT32                         m_f32BackgroundAreaDeviation;
  FLOAT32                         m_f32ForegroundSumAverage;
  FLOAT32                         m_f32ForegroundSumDeviation;
  FLOAT32                         m_f32BackgroundSumAverage;
  FLOAT32                         m_f32BackgroundSumDeviation;
};

///////////////////////////////////////////////////////////////////////////////
#endif //__EOCV_MAIN_H__
