////////////////////////////////////////////////////////////////////////////////////////////////////
// EMatch.h: EasyMatch library header file for eVision 6.7.1.0
//
// EasyMatch implements normalized correlation pattern matching
//
// Copyright ( c) 1997-2006, Euresys. All rights reserved.
//

#ifndef __EMATCH_H__
#define __EMATCH_H__

// ---------------------------------------------------------------------------

// eVision header files
#include "Easy.h"
#include "EMatch_Enum.h"

#include "EasyMatch_BinaryCompatible.h"

// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------

#if defined E_BC45

  // Forward declarations of class instances
  template<class Type> class EVectorTemplate;
  class EVectorTemplate<EMatchPosition>;

#elif defined E_BC50 || defined E_BCB

  // Forward declarations of class instances
  template<class Type> class EVectorTemplate;
  template class E_DLL1 EVectorTemplate<EMatchPosition>;

#endif

class EMatchPositionsVector : public EVectorTemplate<EMatchPosition>
{
  // Wrapping members
public:
  int handle_;
  FinalizeCallback callback_;

public:
  E_DLL0 CONSTRUCTOR E_DLL1  EMatchPositionsVector( UINT32 un32MaxPositions);
};

// ---------------------------------------------------------------------------

// Maximum neighborhood size
#define RADIUS_MAX        4
#define DIAMETER_MAX      ( 2 * RADIUS_MAX + 1)

// Must be smaller than any correlation value
#define MINUS_INFINITY  -2.f

// ---------------------------------------------------------------------------

// Pattern class ( manages the pattern geometric transform during matching
struct EPatternRun
{
  // Offset coordinates of the run starting point
  INT32 m_n32OffsetX;
  INT32 m_n32OffsetY;

  // Length of the run
  INT32 m_n32Length;

  // Run limiting pointers in the source or transformed areas
  UINT8 *m_pun8PatBeg;
  UINT8 *m_pun8PatEnd;
};

// ---------------------------------------------------------------------------


struct EImagePattern
{
  EPatternRun* m_pRuns;
  
  INT32 m_n32NumRuns;

  INT64 m_n64PatPatSigma;
  INT64 m_n64PatPatSum;

  FLOAT32 m_f32AreaRatio;
};


class EPattern
{
public:
  E_DLL0 CONSTRUCTOR E_DLL1   EPattern            ( );
  virtual E_DLL0 DESTRUCTOR E_DLL1  ~EPattern     ( );

  E_DLL0 FLOAT32 E_DLL1       Correlate           ( INT32 n32X, INT32 n32Y, FLOAT32& f32AreaRatio);
  E_DLL0 void E_DLL1          SetPattern          ( EGenericROI* pPattern, UINT32 un32PatExtension = 0);
  E_DLL0 void E_DLL1          SetImage            ( EGenericROI* pImage);
  E_DLL0 void E_DLL1          SetupRuns           ( );
  E_DLL0 void E_DLL1          SetupRuns           ( 
                                                    FLOAT32 f32SrcX,
                                                    FLOAT32 f32SrcY,
                                                    FLOAT32 f32DstX,
                                                    FLOAT32 f32DstY,
                                                    FLOAT32 f32Angle = 0.f,
                                                    FLOAT32 f32ScaleX = 1.f,
                                                    FLOAT32 f32ScaleY = 1.f,
                                                    FLOAT32 f32PixelWidth = 1.f,
                                                    FLOAT32 f32PixelHeight = 1.f);
  
  // Compute and store the direct transform coefficients
  E_DLL0 void E_DLL1          SetTransform        ( 
                                                    FLOAT32 f32SrcX,
                                                    FLOAT32 f32SrcY,
                                                    FLOAT32 f32DstX,
                                                    FLOAT32 f32DstY,
                                                    FLOAT32 f32Angle = 0.f,
                                                    FLOAT32 f32ScaleX = 1.f,
                                                    FLOAT32 f32ScaleY = 1.f,
                                                    FLOAT32 f32PixelWidth = 1.f,
                                                    FLOAT32 f32PixelHeight = 1.f);
  
  // Store the direct transform coefficients
  E_DLL0 void E_DLL1          SetTransformMatrix  ( 
                                                    FLOAT32 f32Axx, FLOAT32 f32Axy, FLOAT32 f32Ax,
                                                    FLOAT32 f32Ayx, FLOAT32 f32Ayy, FLOAT32 f32Ay);
  
  // Debugging utilities
  E_DLL0 void E_DLL1          Copy                ( EGenericROI* pDst);

  // Match Extension
  E_DLL0 void E_DLL1          SetExtension(INT32 n32ExtensionX, INT32 n32ExtensionY);

protected:
  //void ClipPatternForAllPositions();
  //void ClearClippedPatterns();
  
protected:
// Reference pattern description
//------------------------------
  EGenericROI                 *m_pPat; // current pattern
                              
  // Pattern parameters       
  UINT32                      m_un32PatWidth;
  UINT32                      m_un32PatHeight;
  UINT32                      m_un32ExtPatWidth;
  UINT32                      m_un32ExtPatHeight;
  UINT32                      m_un32PatRowPitch;
  UINT32                      m_un32PatExtension;
  UINT8                       *m_pun8Pat; // address of first pixel
  
  // Pattern Size, unreduced.
  INT32                       m_n32PatternWidth;
  INT32                       m_n32PatternHeight;
  
// Image to be searched description
//---------------------------------
  EGenericROI                 *m_pImg; // store the search field
                              
  // Image parameters         
  UINT32                      m_un32ImgWidth;
  UINT32                      m_un32ImgHeight;
  UINT32                      m_un32ImgRowPitch;
  UINT8                       *m_pun8Img; // address of first pixel
  
// Direct affine transform coefficients
//-------------------------------------
  FLOAT32                     m_f32Axx;
  FLOAT32                     m_f32Axy;
  FLOAT32                     m_f32Ax;
  FLOAT32                     m_f32Ayx;
  FLOAT32                     m_f32Ayy;
  FLOAT32                     m_f32Ay;
  
// Transformed pattern description
//--------------------------------
  //   Runs list
  BOOL                        m_bIsRunReady;
                              
  EPatternRun                 *m_pRuns;
  UINT32                      m_un32MaxRuns;
  UINT32                      m_un32NumRuns;
                              
  EPatternRun                 *m_pBorderRuns;
  UINT32                      m_un32MaxBorderRuns;
  UINT32                      m_un32NumBorderRuns;
                              
  //   Pixel data             
  UINT8                       *m_pun8Data;
  UINT32                      m_un32NumData;
  UINT32                      m_un32MaxData;
                              
  //   Bounding box           
  INT32                       m_n32TrfXMin;
  INT32                       m_n32TrfXMax;
  INT32                       m_n32TrfYMin;
  INT32                       m_n32TrfYMax;
  UINT32                      m_un32StripHeight;
  
  //   Intermediate Bounding box 
  INT32                       m_n32TrfExtXMin;
  INT32                       m_n32TrfExtXMax;
  INT32                       m_n32TrfExtYMin;
  INT32                       m_n32TrfExtYMax;
  UINT32                      m_un32ExtStripHeight;
  
// Correlation computation ( constant moments)
//--------------------------------------------
  FLOAT32                     m_f32Sum;
  FLOAT32                     m_f32SumPat;
  FLOAT32                     m_f32SumPatPat;
  FLOAT32                     m_f32SigmaPatPat;
                              
  FLOAT32                     m_f32SumExt;
  FLOAT32                     m_f32SumExtPat;
  FLOAT32                     m_f32SumExtPatPat;
  FLOAT32                     m_f32SigmaExtPatPat;
  
// Searching process
//------------------
  // Don't care threshold
  UINT32                      m_un32DontCareThreshold;
                              
  MCH_CONTRAST_MODE           m_eContrastMode;
                              
  E_CORRELATION_MODE          m_eCorrelationMode;
                              
  // Search steps             
  FLOAT32                     m_f32CenterXStep;
  FLOAT32                     m_f32CenterYStep;
  FLOAT32                     m_f32AngleStep;
  FLOAT32                     m_f32ScaleXStep;
  FLOAT32                     m_f32ScaleYStep;
  FLOAT32                     m_f32ScaleStep;

  INT32                       m_n32NumAngleStep;
  INT32                       m_n32NumScaleXStep;
  INT32                       m_n32NumScaleYStep;
  INT32                       m_n32NumScaleStep;

  // Reduction level
  INT32                       m_n32ReductionIndex;

  // Zero, first and second order moments of the ( full) pattern and image
  UINT32                      m_un32FullSum;
  UINT32                      m_un32FullSumPat;
  FLOAT64                     m_f64FullSumPatPat;
                              
  UINT32                      m_un32Sum;
  UINT32                      m_un32SumImg;
  UINT32                      m_un32SumPat;
  FLOAT64                     m_f64SumImgImg;
  FLOAT64                     m_f64SumImgPat;
  FLOAT64                     m_f64SumPatPat;

protected:
  // Match Extensions (found pattern occurrences may fall outside the matching ROI)
  INT32                       m_n32ExtensionX;
  INT32                       m_n32ExtensionY;

  INT32                       m_n32CurrentExtensionX;
  INT32                       m_n32CurrentExtensionY;

  // Contrasted mode
  INT32                       m_n32CurrentPatternThreshold;
};

// ---------------------------------------------------------------------------

class EMatchStaticArray1;
class EMatchStaticArray2;
class EMatchStaticArray3;
class EMatchStaticArray4;
class EMatchStaticArray5;

class EMatch: public EPattern
{

  // Wrapping members
public:
  int handle_;
  FinalizeCallback callback_;

public:
  // Constructor/destructor
  E_DLL0 CONSTRUCTOR E_DLL1     EMatch                    ( );
  E_DLL0 CONSTRUCTOR E_DLL1     EMatch                    ( UINT32 un32NumDOF );
  E_DLL0 CONSTRUCTOR E_DLL1     EMatch                    ( const EMatch &Match);
  virtual E_DLL0 DESTRUCTOR E_DLL1  ~EMatch               ( );
  E_DLL0 void E_DLL1            InitEmpty                 ( UINT32 un32NumDOF );
  E_DLL0 EMatch* E_DLL1         CopyTo                    ( EMatch *pMatch = NULL) const;
  E_DLL0 EMatch& E_DLL1         operator=                 ( const EMatch &Match);
                                                         
  // Serialization                                       
  E_DLL0 void E_DLL1            Load                      ( const char* pszPathName);
  E_DLL0 void E_DLL1            Load                      ( const UNICHAR* pszPathName);
  E_DLL0 void E_DLL1            Load                      ( ESerializer* serializer );
  E_DLL0 void E_DLL1            Load                      ( FILE* file);
                                                         
  E_DLL0 void E_DLL1            Save                      ( const char* pszPathName);
  E_DLL0 void E_DLL1            Save                      ( const UNICHAR* pszPathName);
  E_DLL0 void E_DLL1            Save                      ( ESerializer* serializer );
  E_DLL0 void E_DLL1            Save                      ( FILE* file);
  
  static E_DLL0 UINT32 E_DLL1   GetVersion                ( );
  virtual E_DLL0 void E_DLL1    Serialize                 ( ESerializer* serializer, UINT32 un32Version);
  virtual E_DLL0 void E_DLL1    Serialize                 ( FILE*  pFile, BOOL bOutput, UINT32 un32Version);
                                                         
  // Learning                                            
  E_DLL0 void E_DLL1            LearnPattern              ( EROIBW8* pPattern);
  E_DLL0 void E_DLL1            LearnPattern              ( EROIC24* pPattern);
  E_DLL0 void E_DLL1            LearnImage                ( EROIBW8* pImage);
  E_DLL0 void E_DLL1            LearnImage                ( EROIC24* pImage);
  E_DLL0 void E_DLL1            ClearImage                ( );
  E_DLL0 BOOL E_DLL1            IsPatternLearnt           ( );
  //E_DLL0 EROIBW8 * E_DLL1       ComputeCorrelationImage   ( EROIBW8 *pResult);
  E_DLL0 EGenericROI* E_DLL1    CreatePatternCopy         ( ) const;
                                                         
  // Matching                                            
  E_DLL0 void E_DLL1            Match                     ( );
  E_DLL0 void E_DLL1            Match                     ( EROIBW8* pImage);
  E_DLL0 void E_DLL1            Match                     ( EROIC24* pImage);
                                                         
  // Learning parameters                            
  E_DLL0 void E_DLL1            SetMinReducedArea         ( UINT32 un32Area);
  E_DLL0 UINT32 E_DLL1          GetMinReducedArea         ( );
                                                    
  E_DLL0 void E_DLL1            SetAlignment              ( BOOL bAlignment);
  E_DLL0 BOOL E_DLL1            GetAlignment              ( );
                                                    
  E_DLL0 void E_DLL1            SetDontCareThreshold      ( UINT32 un32Threshold);
  E_DLL0 UINT32 E_DLL1          GetDontCareThreshold      ( );
  
  // Matching parameters
  E_DLL0 void E_DLL1            SetCorrelationMode        ( enum E_CORRELATION_MODE eMode);
  E_DLL0 enum E_CORRELATION_MODE E_DLL1  GetCorrelationMode( );
  
  E_DLL0 void E_DLL1            SetContrastMode           ( enum MCH_CONTRAST_MODE eMode);
  E_DLL0 enum MCH_CONTRAST_MODE E_DLL1  GetContrastMode   ( );
  
  E_DLL0 UINT32 E_DLL1          GetMaxPositions           ( );
  E_DLL0 void E_DLL1            SetMaxPositions           ( UINT32 un32MaxPositions);
                          
  E_DLL0 UINT32 E_DLL1          GetMaxInitialPositions    ( );
  E_DLL0 void E_DLL1            SetMaxInitialPositions    ( UINT32 un32MaxInitialPositions);
                          
  E_DLL0 FLOAT32 E_DLL1         GetInitialMinScore        ( );
  E_DLL0 void E_DLL1            SetInitialMinScore        ( FLOAT32 f32InitialMinScore);
                                                         
  E_DLL0 FLOAT32 E_DLL1         GetMinScore               ( );
  E_DLL0 void E_DLL1            SetMinScore               ( FLOAT32 f32MinScore);
                                                         
  E_DLL0 FLOAT32 E_DLL1         GetMinAngle               ( );
  E_DLL0 void E_DLL1            SetMinAngle               ( FLOAT32 f32MinAngle);
                                                         
  E_DLL0 FLOAT32 E_DLL1         GetMaxAngle               ( );
  E_DLL0 void E_DLL1            SetMaxAngle               ( FLOAT32 f32MaxAngle);
                                                         
  E_DLL0 FLOAT32 E_DLL1         GetMinScale               ( );
  E_DLL0 void E_DLL1            SetMinScale               ( FLOAT32 f32Scale);
                                                         
  E_DLL0 FLOAT32 E_DLL1         GetMaxScale               ( );
  E_DLL0 void E_DLL1            SetMaxScale               ( FLOAT32 f32Scale);
                                                    
  E_DLL0 FLOAT32 E_DLL1         GetMinScaleX              ( );
  E_DLL0 void E_DLL1            SetMinScaleX              ( FLOAT32 f32MinScaleX);
                                                         
  E_DLL0 FLOAT32 E_DLL1         GetMaxScaleX              ( );
  E_DLL0 void E_DLL1            SetMaxScaleX              ( FLOAT32 f32MaxScaleX);
                                                         
  E_DLL0 FLOAT32 E_DLL1         GetMinScaleY              ( );
  E_DLL0 void E_DLL1            SetMinScaleY              ( FLOAT32 f32MinScaleY);
                                                         
  E_DLL0 FLOAT32 E_DLL1         GetMaxScaleY              ( );
  E_DLL0 void E_DLL1            SetMaxScaleY              ( FLOAT32 f32MaxScaleY);
                                                    
  E_DLL0 BOOL E_DLL1            GetIsotropicScale         ( );
                                                    
  E_DLL0 FLOAT32 E_DLL1         GetAngleStep              ( );
  E_DLL0 FLOAT32 E_DLL1         GetScaleStep              ( );
  E_DLL0 FLOAT32 E_DLL1         GetScaleXStep             ( );
  E_DLL0 FLOAT32 E_DLL1         GetScaleYStep             ( );
                                                    
  E_DLL0 INT32 E_DLL1           GetMaxNumAngleStep        ( );
  E_DLL0 INT32 E_DLL1           GetMaxNumScaleStep        ( );
  E_DLL0 INT32 E_DLL1           GetMaxNumScaleXStep       ( );
  E_DLL0 INT32 E_DLL1           GetMaxNumScaleYStep       ( );
                                                    
  E_DLL0 void E_DLL1            SetMaxNumAngleStep        ( INT32 n32MaxNumAngleStep );
  E_DLL0 void E_DLL1            SetMaxNumScaleStep        ( INT32 n32MaxNumScaleStep );
  E_DLL0 void E_DLL1            SetMaxNumScaleXStep       ( INT32 n32MaxNumScaleXStep);
  E_DLL0 void E_DLL1            SetMaxNumScaleYStep       ( INT32 n32MaxNumScaleYStep);
                                                    
  E_DLL0 void E_DLL1            SetPixelDimensions        ( FLOAT32 f32Width, FLOAT32 f32Height);
  E_DLL0 void E_DLL1            GetPixelDimensions        ( FLOAT32& f32Width, FLOAT32& f32Height);
                                                    
  E_DLL0 BOOL E_DLL1            GetInterpolate            ( );
  E_DLL0 void E_DLL1            SetInterpolate            ( BOOL bInterpolate);

  E_DLL0 BOOL E_DLL1            GetKeepInitialLocalMaxima ( );
  E_DLL0 void E_DLL1            SetKeepInitialLocalMaxima ( BOOL bKeepInitialLocalMaxima);

  E_DLL0 enum MCH_FILTERING_MODE E_DLL1  GetFilteringMode ( );
  E_DLL0 void E_DLL1            SetFilteringMode          ( enum MCH_FILTERING_MODE eFilteringMode);

  E_DLL0 void E_DLL1            SetEnableDiscriminate(BOOL bDiscriminate);
  E_DLL0 BOOL E_DLL1            GetEnableDiscriminate();
  
  E_DLL0 BOOL E_DLL1            GetDiscriminate();

  E_DLL0 void E_DLL1            SetEnableAutoMinReducedArea(BOOL bEnableAutoMinReducedArea);
  E_DLL0 BOOL E_DLL1            GetEnableAutoMinReducedArea();

  E_DLL0 UINT32 E_DLL1          GetInternalMinReducedArea();
                                                    
  // Matching results                               
  E_DLL0 UINT32 E_DLL1          GetNumPositions           ( );
  E_DLL0 EMatchPosition* E_DLL1  GetPosition              ( UINT32 un32Index);
                                                    
  // Reductions                                     
  E_DLL0 UINT32 E_DLL1          GetNumReductions          ( );
  E_DLL0 EGenericROI* E_DLL1    GetPattern                ( UINT32 un32Index);
  E_DLL0 EGenericROI* E_DLL1    GetImage                  ( UINT32 un32Index);
  E_DLL0 void E_DLL1            SelectReduction           ( INT32 un32Index);
                                                    
  E_DLL0 enum MCH_REDUCTION_DECAY_MODE E_DLL1  GetReductionDecayMode ( );
  E_DLL0 void E_DLL1            SetReductionDecayMode     ( enum MCH_REDUCTION_DECAY_MODE eReductionDecayMode);
                                                    
  // Drawing                                        
  E_DLL0 void E_DLL1            DrawPosition              ( HDC hDC, UINT32 un32Index, BOOL bCorner = FALSE, FLOAT32 f32ZoomX = 1.f, FLOAT32 f32ZoomY = 0.f, FLOAT32 f32PanX = 0.f, FLOAT32 f32PanY = 0.f);
  E_DLL0 void E_DLL1            DrawPosition              ( Euresys::DrawAdapter* drawAdapter, UINT32 un32Index, BOOL bCorner = FALSE, FLOAT32 f32ZoomX = 1.f, FLOAT32 f32ZoomY = 0.f, FLOAT32 f32PanX = 0.f, FLOAT32 f32PanY = 0.f);
  E_DLL0 void E_DLL1            DrawPositions             ( HDC hDC, BOOL bCorner = FALSE, FLOAT32 f32ZoomX = 1.f, FLOAT32 f32ZoomY = 0.f, FLOAT32 f32PanX = 0.f, FLOAT32 f32PanY = 0.f);
  E_DLL0 void E_DLL1            DrawPositions             ( Euresys::DrawAdapter* drawAdapter, BOOL bCorner = FALSE, FLOAT32 f32ZoomX = 1.f, FLOAT32 f32ZoomY = 0.f, FLOAT32 f32PanX = 0.f, FLOAT32 f32PanY = 0.f);
                                                    
  E_DLL0 void E_DLL1            SetFinalReduction         ( UINT32 un32FinalReduction);
  E_DLL0 UINT32 E_DLL1          GetFinalReduction         ( );
                          
  // Old modes            
  E_DLL0 BOOL E_DLL1            GetRoughStepEvaluation    ( );
  E_DLL0 void E_DLL1            SetRoughStepEvaluation    ( BOOL bRoughStepEvaluation);
  E_DLL0 BOOL E_DLL1            GetResampleOnTheFly       ( );
  E_DLL0 void E_DLL1            SetResampleOnTheFly       ( BOOL bResampleOnTheFly);
  
  // Pattern Size 
  E_DLL0 INT32 E_DLL1           GetPatternWidth() {return m_n32PatternWidth;};
  E_DLL0 INT32 E_DLL1           GetPatternHeight() {return m_n32PatternHeight;};
  
  EVectorTemplate<EMatchPosition> m_Position;

protected:
  const static UINT32           m_un32FileVersion;
  const static UINT8            m_pun8FileSignature[4];
                                
  UINT32                        m_un32NumDOF;
  UINT32                        m_un32MaxPositions; 
  UINT32                        m_un32MaxInitialPositions; 
                                
  FLOAT32                       m_f32InitialMinScore; 
  FLOAT32                       m_f32MinScore; 
                                
  FLOAT32                       m_f32MinInternalAngle;  // Purpose of Internal Angle/Scale is to leave unmodified
  FLOAT32                       m_f32MaxInternalAngle;  // the search range given by the user. Internally, the range
  FLOAT32                       m_f32MinAngle;          // is recomputed from the origin with discrete steps, and therefore,
  FLOAT32                       m_f32MaxAngle;          // is not excactly the same as the user's one.
                                
  FLOAT32                       m_f32MinInternalScale; 
  FLOAT32                       m_f32MaxInternalScale;
  FLOAT32                       m_f32MinScale; 
  FLOAT32                       m_f32MaxScale;

  FLOAT32                       m_f32MinInternalScaleX; 
  FLOAT32                       m_f32MaxInternalScaleX;
  FLOAT32                       m_f32MinScaleX; 
  FLOAT32                       m_f32MaxScaleX;
                                
  FLOAT32                       m_f32MinInternalScaleY; 
  FLOAT32                       m_f32MaxInternalScaleY; 
  FLOAT32                       m_f32MinScaleY; 
  FLOAT32                       m_f32MaxScaleY; 
                                
  BOOL                          m_bInterpolate; 
                                
private:                        
  // Learning parameters        
  UINT32                        m_un32MinReducedArea;
  BOOL                          m_bAlignment;
  INT32                         m_pPatternExtension[MCH_MAX_REDUCTIONS + 1];
  INT32                         m_pNegSearchLimit[MCH_MAX_REDUCTIONS];
  INT32                         m_pPosSearchLimit[MCH_MAX_REDUCTIONS];

  INT32                         m_pOldPatternExtension[MCH_MAX_REDUCTIONS + 1];
  INT32                         m_pOldNegSearchLimit[MCH_MAX_REDUCTIONS];
  INT32                         m_pOldPosSearchLimit[MCH_MAX_REDUCTIONS];

  void                          ComputePatternExtension   ( );
  void                          ComputeSearchLimit        ( );

  // Search steps for the full-size pattern            
  INT32                         m_n32MaxNumAngleStep;
  INT32                         m_n32MaxNumScaleXStep;
  INT32                         m_n32MaxNumScaleYStep;
  INT32                         m_n32MaxNumScaleStep;

  FLOAT32                       m_f32AnglePatternStep;
  FLOAT32                       m_f32ScaleXPatternStep;
  FLOAT32                       m_f32ScaleYPatternStep;
  FLOAT32                       m_f32ScalePatternStep;
  void                          ComputePatternSteps ( );
  
  // Matching parameters        
  BOOL                          m_bIsotropicScale;
  BOOL                          m_bEnableDiscriminate;
  BOOL                          m_bDiscriminate;
                                
  // Pixel dimensions           
  FLOAT32                       m_f32PixelWidth;
  FLOAT32                       m_f32PixelHeight;
  
  // Arrays of reduced images
  UINT32                        m_un32PlanesPerPixel; // 1==EBW8, 3==EC24
  UINT32                        m_un32NumReductions;  // total nb of stages
  UINT32                        m_un32FinalReduction;
  
  enum MCH_REDUCTION_DECAY_MODE m_eReductionDecayMode;
  enum MCH_REDUCTION_DECAY_MODE m_eOldReductionDecayMode;
                          
  // Reductions                                     
  EGenericROI                   *m_pPattern   [MCH_MAX_REDUCTIONS];
  EGenericROI                   *m_pImage     [MCH_MAX_REDUCTIONS];

  INT32                         m_pn32PatternThreshold[MCH_MAX_REDUCTIONS];
                                
  BOOL                          m_bCopyFirstImage;
  BOOL                          m_bPatternLearnt;
                                
  BOOL                          m_bKeepInitialLocalMaxima;

  // Old modes                  
  BOOL                          m_bResampleOnTheFly;
  BOOL                          m_bEnableResampleOnTheFly;
  BOOL                          m_bRoughStepEvaluation;
  BOOL                          m_bEnableRoughStepEvaluation;
                                
  // Search image ROI origin                 
  INT32                         m_n32OrgX;
  INT32                         m_n32OrgY;

  // Automatic determination of Min Reduced Area
  BOOL                          m_bAutoMinReducedArea;

  // User Set Min Reduced Area
  UINT32                        m_un32UserMinReducedArea;
  
  // Pyramid                    
  enum MCH_FILTERING_MODE       m_eFilteringMode;

  E_DLL0 INT16 E_DLL1           FilterAndReduceImage      ( EROIBW8* pSrc, EROIBW8* pDst);
  E_DLL0 INT16 E_DLL1           Filter3x3AndReducePattern ( EROIBW8* pSrc, EROIBW8* pDst);
  E_DLL0 INT16 E_DLL1           Filter3x3AndReduceImage   ( EROIBW8* pSrc, EROIBW8* pDst);
  E_DLL0 INT16 E_DLL1           Filter2x2AndReducePattern ( EROIBW8* pSrc, EROIBW8* pDst);
  E_DLL0 INT16 E_DLL1           Filter2x2AndReduceImage   ( EROIBW8* pSrc, EROIBW8* pDst);
  E_DLL0 INT16 E_DLL1           FilterMinMax2x2AndReducePattern( EROIBW8* pSrc, EROIBW8* pDst);
  E_DLL0 INT16 E_DLL1           FilterMinMax2x2AndReduceImage  ( EROIBW8* pSrc, EROIBW8* pDst);

  E_DLL0 INT16 E_DLL1           Reduce                    ( EROIC24* pSrc, EROIC24* pDst);
                                                    
  // Correlation                                    
  void                          AccumulatePattern         ( );
  void                          Accumulate                ( INT32 n32OrgX, INT32 n32OrgY);
  void                          Accumulate                ( FLOAT32 f32Axx, FLOAT32 f32Axy, FLOAT32 f32Ax, FLOAT32 f32Ayx, FLOAT32 f32Ayy, FLOAT32 f32Ay);
                                                          
  FLOAT32                       Correlation               ( FLOAT32 f32CenterX, FLOAT32 f32CenterY);
  FLOAT32                       Correlation               ( FLOAT32 f32CenterX, FLOAT32 f32CenterY, FLOAT32 f32Rotation, FLOAT32 f32ScaleX, FLOAT32 f32ScaleY);
  FLOAT32                       Correlation               ( FLOAT32 f32Axx, FLOAT32 f32Axy, FLOAT32 f32Ax, FLOAT32 f32Ayx, FLOAT32 f32Ayy, FLOAT32 f32Ay);
                                                          
  // Maxima separation                                    
  void                          Sift                      ( EMatchPosition& Position, UINT32 un32NumElements);
  void                          KeepBest                  ( UINT32 un32Number, FLOAT32 f32MinScore, FLOAT32 f32MinGap = 0.0f);
  
  // Maxima improvement
  enum ImprovementMode {
    CheckOnly,
    Improve,
    ImproveMore
  };

  BOOL                          ImproveSxSyAXY            ( EMatchPosition& Position, enum ImprovementMode eMode, INT32 n32NegSx, INT32 n32PosSx, INT32 n32NegSy, INT32 n32PosSy, INT32 n32NegA, INT32 n32PosA, INT32 n32Neg = 1, INT32 n32Pos = 1);
  BOOL                          ImproveSxAXY              ( EMatchPosition& Position, enum ImprovementMode eMode, INT32 n32NegSx, INT32 n32PosSx, INT32 n32NegA, INT32 n32PosA, INT32 n32Neg = 1, INT32 n32Pos = 1);
  BOOL                          ImproveSyAXY              ( EMatchPosition& Position, enum ImprovementMode eMode, INT32 n32NegSy, INT32 n32PosSy, INT32 n32NegA, INT32 n32PosA, INT32 n32Neg = 1, INT32 n32Pos = 1);
  BOOL                          ImproveSAXY               ( EMatchPosition& Position, enum ImprovementMode eMode, INT32 n32NegS, INT32 n32PosS, INT32 n32NegA, INT32 n32PosA, INT32 n32Neg = 1, INT32 n32Pos = 1);
  BOOL                          ImproveSxSyXY             ( EMatchPosition& Position, enum ImprovementMode eMode, INT32 n32NegSx, INT32 n32PosSx, INT32 n32NegSy, INT32 n32PosSy, INT32 n32Neg = 1, INT32 n32Pos = 1);
  BOOL                          ImproveSxXY               ( EMatchPosition& Position, enum ImprovementMode eMode, INT32 n32NegSx, INT32 n32PosSx, INT32 n32Neg = 1, INT32 n32Pos = 1);
  BOOL                          ImproveSyXY               ( EMatchPosition& Position, enum ImprovementMode eMode, INT32 n32NegSy, INT32 n32PosSy, INT32 n32Neg = 1, INT32 n32Pos = 1);
  BOOL                          ImproveSXY                ( EMatchPosition& Position, enum ImprovementMode eMode, INT32 n32NegS, INT32 n32PosS, INT32 n32Neg = 1, INT32 n32Pos = 1);
  BOOL                          ImproveAXY                ( EMatchPosition& Position, enum ImprovementMode eMode, INT32 n32NegA, INT32 n32PosA, INT32 n32Neg = 1, INT32 n32Pos = 1);
  BOOL                          ImproveXY                 ( EMatchPosition& Position, enum ImprovementMode eMode, INT32 n32Neg = 1, INT32 n32Pos = 1);
                                
  // handling of the pf32Fx variables
  void                          MakeFArrayAliases         ( );
  void                          FreeFArrays               ( );
  void                          MakeFArrays               ( UINT32 un32NumDOF);
                                
  // the object that actually holds the arrays
  EMatchStaticArray1*           m_pStaticArray1;
  EMatchStaticArray2*           m_pStaticArray2;
  EMatchStaticArray3*           m_pStaticArray3;
  EMatchStaticArray4*           m_pStaticArray4;
  EMatchStaticArray5*           m_pStaticArray5;

  // Function value array aliases to center positions
  FLOAT32                       ( * pf32G2) [DIAMETER_MAX];
  FLOAT32                       ( * pf32G3) [DIAMETER_MAX][DIAMETER_MAX];
  FLOAT32                       ( * pf32G4) [DIAMETER_MAX][DIAMETER_MAX][DIAMETER_MAX];
  FLOAT32                       ( * pf32G5) [DIAMETER_MAX][DIAMETER_MAX][DIAMETER_MAX][DIAMETER_MAX];
  
  // Optimum improvement by interplation
  FLOAT32                       Value                     ( FLOAT32 f32X);
  FLOAT32                       Optimum                   ( );
  FLOAT32                       BiOptimum                 ( FLOAT32& f32X, FLOAT32& f32Y);
  FLOAT32                       TriOptimum                ( FLOAT32& f32X, FLOAT32& f32Y, FLOAT32& f32Z);
  FLOAT32                       QuadriOptimum             ( FLOAT32& f32X, FLOAT32& f32Y, FLOAT32& f32Z, FLOAT32& f32T);
  FLOAT32                       QuintiOptimum             ( FLOAT32& f32X, FLOAT32& f32Y, FLOAT32& f32Z, FLOAT32& f32T, FLOAT32& f32U);
};

// ---------------------------------------------------------------------------

#endif //__E_MATCH_H__
