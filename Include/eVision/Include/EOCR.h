////////////////////////////////////////////////////////////////////////////////////////////////////
// EOCR.h: EasyOCR library header file for eVision 6.7.1.0
//
// EasyOCR implements robust optical character recognition
//
// Copyright ( c) 1997-2006, Euresys. All rights reserved.
//

#ifndef __EOCR_H__
#define __EOCR_H__

///////////////////////////////////////////////////////////////////////////////
// Standard include files
#include <stdio.h>

// eVision header files
#include "Easy.h"
#include "EObject.h"
#include "EOCR_Enum.h"



///////////////////////////////////////////////////////////////////////////////
//
class EOCRChar;
class EOCRPattern;

///////////////////////////////////////////////////////////////////////////////
// + OBSOLETE after 5.2
#define LoadFont Load
#define SaveFont Save
// - OBSOLETE after 5.2

///////////////////////////////////////////////////////////////////////////////
// OCR context
class EOCR
{
// Wrapping members
public:
  int handle_;
  FinalizeCallback callback_;

public:
  // Constructor/destructor
  E_DLL0 CONSTRUCTOR E_DLL1         EOCR                    ( );
  virtual E_DLL0 DESTRUCTOR E_DLL1  ~EOCR                   ( );
  E_DLL0 CONSTRUCTOR E_DLL1         EOCR                    (const EOCR& other);

  E_DLL0 EOCR& E_DLL1               operator=               (const EOCR& other);


  
  // Size
  E_DLL0 UINT32 E_DLL1              GetPatternWidth         ( );
  E_DLL0 UINT32 E_DLL1              GetPatternHeight        ( );
  
  // Recognition parameters
  E_DLL0 enum OCR_MATCHING_MODES E_DLL1  GetMatchingMode    ( ) { return m_eMatchingMode; }
  E_DLL0 void E_DLL1                SetMatchingMode         ( enum OCR_MATCHING_MODES eMatchingMode) { m_eMatchingMode = eMatchingMode; }

  E_DLL0 enum OCR_SHIFTING_MODES E_DLL1  GetShiftingMode    ( ) { return m_eShiftingMode; }
  E_DLL0 void E_DLL1                SetShiftingMode         ( enum OCR_SHIFTING_MODES eShiftingMode) { m_eShiftingMode = eShiftingMode; }

  E_DLL0 UINT32 E_DLL1              GetShiftXTolerance      ( ) { return m_un32ShiftXTolerance; }
  E_DLL0 void E_DLL1                SetShiftXTolerance      ( UINT32 un32ShiftXTolerance) { m_un32ShiftXTolerance = un32ShiftXTolerance; }
                                                            
  E_DLL0 UINT32 E_DLL1              GetShiftYTolerance      ( ) { return m_un32ShiftYTolerance; }
  E_DLL0 void E_DLL1                SetShiftYTolerance      ( UINT32 un32ShiftYTolerance) { m_un32ShiftYTolerance = un32ShiftYTolerance; }

  //  Contrast
  E_DLL0 enum OCRColor E_DLL1       GetTextColor            ( ) { return m_eTextColor; }
  E_DLL0 void E_DLL1                SetTextColor            ( enum OCRColor eTextColor) { m_eTextColor = eTextColor; }
                                                            
  E_DLL0 void E_DLL1                SetThreshold            ( INT32 un32Threshold = IMG_MIN_RESIDUE_THRESHOLD) { m_un32Threshold = un32Threshold; 
                                                                                                                 m_un32TrueThreshold = un32Threshold;}
  E_DLL0 INT32 E_DLL1               GetThreshold            ( ) { return m_un32Threshold; }
  
  //  Character dimensions
  E_DLL0 INT32 E_DLL1               GetMinCharWidth         ( ) { return m_n32MinCharWidth; }
  E_DLL0 void E_DLL1                SetMinCharWidth         ( INT32 n32MinCharWidth) { m_n32MinCharWidth = n32MinCharWidth; }
                                                            
  E_DLL0 INT32 E_DLL1               GetMaxCharWidth         ( ) { return m_n32MaxCharWidth; }
  E_DLL0 void E_DLL1                SetMaxCharWidth         ( INT32 n32MaxCharWidth) { m_n32MaxCharWidth = n32MaxCharWidth; }
                                    
  E_DLL0 INT32 E_DLL1               GetMinCharHeight        ( ) { return m_n32MinCharHeight; }
  E_DLL0 void E_DLL1                SetMinCharHeight        ( INT32 n32MinCharHeight) { m_n32MinCharHeight = n32MinCharHeight; }
                                                            
  E_DLL0 INT32 E_DLL1               GetMaxCharHeight        ( ) { return m_n32MaxCharHeight; }
  E_DLL0 void E_DLL1                SetMaxCharHeight        ( INT32 n32MaxCharHeight) { m_n32MaxCharHeight = n32MaxCharHeight; }
                                    
  E_DLL0 INT32 E_DLL1               GetCharSpacing          ( ) { return m_n32CharSpacing; }
  E_DLL0 void E_DLL1                SetCharSpacing          ( INT32 n32CharSpacing) { m_n32CharSpacing = n32CharSpacing; }
                                    
  //   Segmentation                 
  E_DLL0 INT32 E_DLL1               GetNoiseArea            ( ) { return m_n32NoiseArea; }
  E_DLL0 void E_DLL1                SetNoiseArea            ( INT32 n32NoiseArea) { m_n32NoiseArea = n32NoiseArea; }

  E_DLL0 enum OCRSegmentationMode E_DLL1  GetSegmentationMode( ) { return m_eSegmentationMode; }
  E_DLL0 void E_DLL1                SetSegmentationMode     ( enum OCRSegmentationMode eSegmentationMode) { m_eSegmentationMode = eSegmentationMode; }
                                    
  E_DLL0 BOOL E_DLL1                GetCutLargeChars        ( ) { return m_bCutLargeChars; }
  E_DLL0 void E_DLL1                SetCutLargeChars        ( BOOL bCutLargeChars) { m_bCutLargeChars = bCutLargeChars; }

  E_DLL0 FLOAT32 E_DLL1             GetRelativeSpacing      ( ) { return m_f32RelativeSpacing; }
  E_DLL0 void E_DLL1                SetRelativeSpacing      ( FLOAT32 f32RelativeSpacing) { m_f32RelativeSpacing = f32RelativeSpacing; }
                                    
  E_DLL0 BOOL E_DLL1                GetRemoveNarrowOrFlat   ( ) { return m_bRemoveNarrowOrFlat; }
  E_DLL0 void E_DLL1                SetRemoveNarrowOrFlat   ( BOOL bRemoveNarrowOrFlat) { m_bRemoveNarrowOrFlat = bRemoveNarrowOrFlat; }
                                    
  E_DLL0 BOOL E_DLL1                GetRemoveBorder         ( ) { return m_bRemoveBorder; }
  E_DLL0 void E_DLL1                SetRemoveBorder         ( BOOL bRemoveBorder) { m_bRemoveBorder = bRemoveBorder; }
                                    
  E_DLL0 BOOL E_DLL1                GetCompareAspectRatio   ( ) { return m_bCompareAspectRatio; }
  E_DLL0 void E_DLL1                SetCompareAspectRatio   ( BOOL bCompareAspectRatio) { m_bCompareAspectRatio = bCompareAspectRatio; }
                                    
  E_DLL0 BOOL E_DLL1                GetDeskew               ( ) { return m_bDeskew; }
  E_DLL0 void E_DLL1                SetDeskew               ( BOOL bDeskew) { m_bDeskew = bDeskew; }

  E_DLL0 FLOAT32 E_DLL1             GetSkewAngle            ( ) { return EFromRadians( m_f32SkewAngle); }

  // Candidate characters
  E_DLL0 INT32 E_DLL1               GetNumChars             ( );
                                    
  E_DLL0 INT32 E_DLL1               GetFirstCharCode        ( INT32 n32Index);
  E_DLL0 INT16 E_DLL1               SetFirstCharCode        ( INT32 n32Index, INT32 n32Code);
  E_DLL0 INT32 E_DLL1               GetSecondCharCode       ( INT32 n32Index);
  E_DLL0 INT16 E_DLL1               SetSecondCharCode       ( INT32 n32Index, INT32 n32Code);
                                    
  E_DLL0 FLOAT32 E_DLL1             GetFirstCharDistance    ( INT32 n32Index);
  E_DLL0 INT16 E_DLL1               SetFirstCharDistance    ( INT32 n32Index, FLOAT32 f32Distance);
  E_DLL0 FLOAT32 E_DLL1             GetSecondCharDistance   ( INT32 n32Index);
  E_DLL0 INT16 E_DLL1               SetSecondCharDistance   ( INT32 n32Index, FLOAT32 f32Distance);
                                    
  E_DLL0 FLOAT32 E_DLL1             GetConfidenceRatio      ( INT32 n32Index);
                                    
  E_DLL0 FLOAT32 E_DLL1             GetAverageFirstCharDistance( );
                                    
  E_DLL0 INT32 E_DLL1               CharGetOrgX             ( INT32 n32Index);
  E_DLL0 INT32 E_DLL1               CharGetOrgY             ( INT32 n32Index);
  E_DLL0 INT32 E_DLL1               CharGetDstX             ( INT32 n32Index);
  E_DLL0 INT32 E_DLL1               CharGetDstY             ( INT32 n32Index);
  E_DLL0 INT32 E_DLL1               CharGetTotalOrgX        ( INT32 n32Index);
  E_DLL0 INT32 E_DLL1               CharGetTotalOrgY        ( INT32 n32Index);
  E_DLL0 INT32 E_DLL1               CharGetTotalDstX        ( INT32 n32Index);
  E_DLL0 INT32 E_DLL1               CharGetTotalDstY        ( INT32 n32Index);
  E_DLL0 INT32 E_DLL1               CharGetWidth            ( INT32 n32Index);
  E_DLL0 INT32 E_DLL1               CharGetHeight           ( INT32 n32Index);
  
  // Optical Character Recognition
  E_DLL0 INT16 E_DLL1               BuildObjects            ( EROIBW8* pSrcImage);
  E_DLL0 INT16 E_DLL1               FindAllChars            ( EROIBW8* pSrcImage);
  E_DLL0 INT16 E_DLL1               MatchChar               ( EROIBW8* pSrcImage, UINT32 un32Classes, INT32& n32Index, INT32 n32ShiftX, INT32 n32ShiftY);
                                    
  E_DLL0 INT16 E_DLL1               ReadText                ( EROIBW8* pSrcImage, INT32 n32MaxChars, UINT32 un32Classes, char* pszString, BOOL bAutoSegmentation = TRUE);
  E_DLL0 INT16 E_DLL1               ReadText                ( EROIBW8* pSrcImage, INT32 n32MaxChars, UINT32* pun32Classes, char* pszString, BOOL bAutoSegmentation = TRUE);
                                                            
  E_DLL0 void E_DLL1                Recognize               ( EROIBW8* pSrcImage, INT32 n32MaxChars, UINT32 un32Classes, char* pszString);
  E_DLL0 void E_DLL1                Recognize               ( EROIBW8* pSrcImage, INT32 n32MaxChars, UINT32* pun32Classes, char* pszString);
  E_DLL0 void E_DLL1                Recognize               ( EROIBW8* pSrcImage, INT32 n32MaxChars, Euresys::eVision::Utils::Vector<UINT32> pun32Classes, char* pszString);

  // Unicode                        
  E_DLL0 void E_DLL1                ReadText                ( EROIBW8* pSrcImage, INT32 n32MaxChars, UINT32 un32Classes, UNICHAR* pszString, BOOL bAutoSegmentation = TRUE);
  E_DLL0 void E_DLL1                ReadText                ( EROIBW8* pSrcImage, INT32 n32MaxChars, UINT32* pun32Classes, UNICHAR* pszString, BOOL bAutoSegmentation = TRUE);
  E_DLL0 void E_DLL1                Recognize               ( EROIBW8* pSrcImage, INT32 n32MaxChars, UINT32 un32Classes, UNICHAR* pszString);
  E_DLL0 void E_DLL1                Recognize               ( EROIBW8* pSrcImage, INT32 n32MaxChars, UINT32* pun32Classes, UNICHAR* pszString);
  E_DLL0 void E_DLL1                Recognize               ( EROIBW8* pSrcImage, INT32 n32MaxChars, Euresys::eVision::Utils::Vector<UINT32> pun32Classes, UNICHAR* pszString);
  
  // Learning
  E_DLL0 BOOL E_DLL1                HitChars                ( INT32 n32CursorX, INT32 n32CursorY, UINT32& un32CharIndex,
                                                              FLOAT32 f32ZoomX = 1.f, FLOAT32 f32ZoomY = 0.f,
                                                              FLOAT32 f32PanX = 0.f, FLOAT32 f32PanY = 0.f);
  E_DLL0 BOOL E_DLL1                HitChar                 ( INT32 n32CursorX, INT32 n32CursorY, UINT32 un32CharIndex,
                                                              FLOAT32 f32ZoomX = 1.f, FLOAT32 f32ZoomY = 0.f,
                                                              FLOAT32 f32PanX = 0.f, FLOAT32 f32PanY = 0.f);
  
  E_DLL0 void E_DLL1                LearnPattern            ( EROIBW8* pSrcImage, UINT32 un32CharIndex, INT32 n32Code, UINT32 un32Class = OCR_CLASS_0, BOOL bAutoSegmentation = TRUE);
                                                            
  E_DLL0 void E_DLL1                LearnPatterns           ( EROIBW8* pSrcImage, const char* pszString, UINT32 un32Class = OCR_CLASS_0, BOOL bAutoSegmentation = TRUE);
  E_DLL0 void E_DLL1                LearnPatterns           ( EROIBW8* pSrcImage, const char* pszString, UINT32* pun32Classes, BOOL bAutoSegmentation = TRUE);
                                                            
  // Unicode                                                
  E_DLL0 void E_DLL1                LearnPatterns           ( EROIBW8* pSrcImage, const UNICHAR* pszString, UINT32 un32Class = OCR_CLASS_0, BOOL bAutoSegmentation = TRUE);
  E_DLL0 void E_DLL1                LearnPatterns           ( EROIBW8* pSrcImage, const UNICHAR* pszString, UINT32* pun32Classes, BOOL bAutoSegmentation = TRUE);
                                    
  E_DLL0 void E_DLL1                AddPatternFromImage     ( EROIBW8* pSrcImage,
                                                              INT32 n32OrgX, INT32 n32OrgY, INT32 n32Width, INT32 n32Height,
                                                              INT32 n32Code, UINT32 un32Class = OCR_CLASS_0);
                                    
  // Deskewing                      
  E_DLL0 void E_DLL1                MeasureSkew             ( );
  E_DLL0 void E_DLL1                Deskew                  ( );
  
  // Deskewed image
  EImageBW8 m_Deskewed;
  
  // Font management
  E_DLL0 INT16 E_DLL1               NewFont                 ( UINT32 un32PatternWidth = 5, UINT32 un32PatternHeight = 9);
  E_DLL0 void E_DLL1                RemovePattern           ( UINT32 un32Index);
                                    
  E_DLL0 INT16 E_DLL1               Load                    ( const char* pszPathName);
  E_DLL0 void E_DLL1                Load                    ( const UNICHAR* pszPathName);
                                                            
  E_DLL0 INT16 E_DLL1               Save                    ( const char* pszPathName);
  E_DLL0 void E_DLL1                Save                    ( const UNICHAR* pszPathName);
                                    
  virtual E_DLL0 void E_DLL1        Serialize               ( FILE* pFile, BOOL bOutput);
                                    
  E_DLL0 INT32 E_DLL1               GetNumPatterns          ( );
                                                            
  E_DLL0 INT32 E_DLL1               GetPatternCode          ( INT32 n32Index);
  E_DLL0 void E_DLL1                SetPatternCode          ( INT32 n32Index, INT32 n32Code);
                                    
  E_DLL0 UINT32 E_DLL1              GetPatternClass         ( INT32 n32Index);
  E_DLL0 void E_DLL1                SetPatternClass         ( INT32 n32Index, UINT32 un32Class);
                                    
  E_DLL0 FLOAT32 E_DLL1             PatternDistance         ( INT32 n32Index0, INT32 n32Index1);
  E_DLL0 EBW8* E_DLL1               GetPatternBitmap        ( INT32 n32Index);
                                    
  // Text management                
  E_DLL0 void E_DLL1                EmptyChars              ( );
  E_DLL0 INT16 E_DLL1               AddChar                 ( INT32 n32OrgX, INT32 n32OrgY, INT32 n32EndX, INT32 n32EndY);
                                                            
  E_DLL0 void E_DLL1                DrawChar                ( HDC hDC, UINT32 un32CharIndex, FLOAT32 f32ZoomX = 1.f, FLOAT32 f32ZoomY = 0.f, FLOAT32 f32PanX = 0.f, FLOAT32 f32PanY = 0.f);
  E_DLL0 void E_DLL1                DrawChar                ( Euresys::DrawAdapter* drawAdapter, UINT32 un32CharIndex, FLOAT32 f32ZoomX = 1.f, FLOAT32 f32ZoomY = 0.f, FLOAT32 f32PanX = 0.f, FLOAT32 f32PanY = 0.f);

  E_DLL0 void E_DLL1                DrawChars               ( HDC hDC, FLOAT32 f32ZoomX = 1.f, FLOAT32 f32ZoomY = 0.f, FLOAT32 f32PanX = 0.f, FLOAT32 f32PanY = 0.f);
  E_DLL0 void E_DLL1                DrawChars               ( Euresys::DrawAdapter* drawAdapter, FLOAT32 f32ZoomX = 1.f, FLOAT32 f32ZoomY = 0.f, FLOAT32 f32PanX = 0.f, FLOAT32 f32PanY = 0.f);
                                    
  E_DLL0 void E_DLL1                DrawObjects             ( HDC hDC, enum E_SELECTION_MODE eSelection = E_SELECTED_TRUE, FLOAT32 f32ZoomX = 1.f, FLOAT32 f32ZoomY = 0.f, FLOAT32 f32PanX = 0.f, FLOAT32 f32PanY = 0.f);
  E_DLL0 void E_DLL1                DrawObjects             ( Euresys::DrawAdapter* drawAdapter, enum E_SELECTION_MODE eSelection = E_SELECTED_TRUE, FLOAT32 f32ZoomX = 1.f, FLOAT32 f32ZoomY = 0.f, FLOAT32 f32PanX = 0.f, FLOAT32 f32PanY = 0.f);

  // Debugging facilities
  E_DLL0 void E_DLL1                Dump                    ( );
  
  // True Threshold Accessor
  E_DLL0 UINT32 E_DLL1              GetTrueThreshold        ( ) { return m_un32TrueThreshold; }
  
protected:

  void OCR_InternalCopyTo(const EOCR* This, EOCR& dest);


  enum OCR_MATCHING_MODES           m_eMatchingMode; 
  enum OCR_SHIFTING_MODES           m_eShiftingMode; 
  UINT32                            m_un32ShiftXTolerance; 
  UINT32                            m_un32ShiftYTolerance; 
  enum OCRColor                     m_eTextColor; 
  INT32                             m_n32MinCharWidth; 
  INT32                             m_n32MaxCharWidth; 
  INT32                             m_n32MinCharHeight; 
  INT32                             m_n32MaxCharHeight; 
  INT32                             m_n32CharSpacing; 
  INT32                             m_n32NoiseArea; 
  enum OCRSegmentationMode          m_eSegmentationMode; 
  BOOL                              m_bCutLargeChars; 
  FLOAT32                           m_f32RelativeSpacing; 
  BOOL                              m_bRemoveNarrowOrFlat; 
  BOOL                              m_bRemoveBorder; 
  BOOL                              m_bCompareAspectRatio; 
  BOOL                              m_bDeskew; 
  FLOAT32                           m_f32SkewAngle; 

private:
  // Coded image
  ECodedImage                       m_CodedImage;
  
  // Thresholding
  UINT32                            m_un32Threshold;
  UINT32                            m_un32TrueThreshold;
  
  // ROI origin
  INT32                             m_n32OrgX;
  INT32                             m_n32OrgY;
  
  // Text ( set of candidate characters)
  INT32                             m_n32MaxChars;
  INT32                             m_n32NumChars;
  EOCRChar*                         m_pChar;
  
  // Font ( set of recorded patterns)
  UINT32                            m_un32PatternWidth;
  UINT32                            m_un32PatternHeight;
  
  UINT32                            m_un32NumPatterns;
  UINT32                            m_un32MaxPatterns;
  EOCRPattern*                      m_pPattern;
  
  // Font management
  INT16                             AddPattern              ( );
  
  // Optical character recognition
  INT16                             MatchPattern            ( EOCRPattern& Pattern, UINT32 un32Classes, 
                                                              INT32& n32FirstIndex, FLOAT32& f32FirstDistance,
                                                              INT32& n32SecondIndex, FLOAT32& f32SecondDistance);
};

///////////////////////////////////////////////////////////////////////////////
// Characters
class EOCRChar
{
public:
  // Geometry
  INT32                             GetOrgX                 ( );
  INT32                             GetOrgY                 ( );
  INT32                             GetDstX                 ( );
  INT32                             GetDstY                 ( );
  INT32                             GetWidth                ( );
  INT32                             GetHeight               ( );
  
  // Codes
  INT32                             GetFirstCode            ( );
  INT16                             SetFirstCode            ( INT32 n32Code);
  INT32                             GetSecondCode           ( );
  INT16                             SetSecondCode           ( INT32 n32Code);
  
  // Distances
  FLOAT32                           GetFirstDistance        ( );
  INT16                             SetFirstDistance        ( FLOAT32 f32Distance);
  FLOAT32                           GetSecondDistance       ( );
  INT16                             SetSecondDistance       ( FLOAT32 f32Distance);

  // Confidence ratio
  FLOAT32                           GetConfidenceRatio      ( );

private:
  // Absolute position
  INT32                             m_n32OrgX;
  INT32                             m_n32OrgY;
  INT32                             m_n32DstX;
  INT32                             m_n32DstY;
  
  // Recognition
  INT32                             m_n32FirstCode;
  INT32                             m_n32SecondCode;
  FLOAT32                           m_f32FirstDistance;
  FLOAT32                           m_f32SecondDistance;

  friend class EOCR;
};

///////////////////////////////////////////////////////////////////////////////
// Patterns
class EOCRPattern
{
public:
  // Constructor/destructor
                                    EOCRPattern             ( );
                                    EOCRPattern             ( UINT32 un32Width, UINT32 un32Height);
  virtual                           ~EOCRPattern            ( );
  E_DLL0 CONSTRUCTOR E_DLL1         EOCRPattern             (const EOCRPattern& other);

  E_DLL0 EOCRPattern& E_DLL1        operator=               (const EOCRPattern& other);

  
  // Data member access
  E_DLL0 INT32 E_DLL1               GetCode                 ( ) { return m_n32Code; }
  E_DLL0 void E_DLL1                SetCode                 ( INT32 n32Code) { m_n32Code = n32Code; }
                                    
  E_DLL0 UINT32 E_DLL1              GetClass                ( ) { return m_un32Class; }
  E_DLL0 void E_DLL1                SetClass                ( UINT32 un32Class) { m_un32Class = un32Class; }
                                    
  E_DLL0 FLOAT32 E_DLL1             GetDistance             ( ) { return m_f32Distance; }
  E_DLL0 void E_DLL1                SetDistance             ( FLOAT32 f32Distance) { m_f32Distance = f32Distance; }
                                    
  // Serialization                  
  INT16                             ReadFromFile            ( FILE* pFile, BOOL bTrueSize = TRUE, BOOL bTranspose = FALSE);
  INT16                             WriteToFile             ( FILE* pFile);
                                    
  // Creation                       
  INT16                             ComputeFromImage        ( EROIBW8* pSrcImage,
                                                              INT32 n32OrgX, INT32 n32OrgY, INT32 n32Width, INT32 n32Height,
                                                              INT32 eTextColor, UINT32 un32Threshold);
                                    
  // Rating                         
  FLOAT32                           Distance                ( EOCRPattern& Pattern, BOOL bCompareAspectRatio, enum OCR_MATCHING_MODES m_eMatchingMode);
  
  // Debugging facilities
  void                              Dump                    ( );

protected:

  void                              EOCRPattern_InternalCopyTo      (const EOCRPattern* This, EOCRPattern& dest);

  INT32                             m_n32Code; 
  UINT32                            m_un32Class; 
  FLOAT32                           m_f32Distance; 
  
private:
  // Pattern bitmap
  UINT32                            m_un32Width;
  UINT32                            m_un32Height;
  UINT32                            m_un32Area;
  UINT8*                            m_pun8Bitmap;
  
  // Actual size
  UINT32                            m_un32TrueWidth;
  UINT32                            m_un32TrueHeight;
  
  friend class EOCR;
};

///////////////////////////////////////////////////////////////////////////////
//
#endif //__EOCR_H__
