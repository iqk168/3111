////////////////////////////////////////////////////////////////////////////////////////////////////
// EFind.h: EasyFind library header file for eVision 6.7.1.0
//
// EasyFind implements geometric pattern matching
//
// Copyright ( c) 1997-2006, Euresys. All rights reserved.
//

#ifndef __EFIND_IMPL_H__
#define __EFIND_IMPL_H__

#if (_MSC_VER >= 1300)
#pragma warning( push )
#pragma warning( disable : 4702 ) 
#endif // (_MSC_VER >= 1300)

#include <vector>

#if (_MSC_VER >= 1300)
#pragma warning( pop )
#endif // (_MSC_VER >= 1300)

using std::vector;

// Include the new EasyFind API
#include "EasyFind.h"

// eVision header files
#include "EInspect.h"
#include "EObject.h"
#include "EFind_Enum.h"
#include "Easy_PointLineSegment.h"
#ifdef HAUSDORFF_DEBUG
#include "..\..\Tools\EPlotDebug.h"
#endif

using namespace Euresys::eVision;
using namespace Euresys::eVision::Utils;


// ---------------------------------------------------------------------------


enum FND_STATES
{
  FND_LEARNING,
  FND_FINDING,
  FND_READY,

  FND_STATE_UNKNOWN  = 0xFFFFFFFF
};

// ---------------------------------------------------------------------------

// Pattern candidate location
struct EFindPosition
{
  // Location
  FLOAT32     m_f32X;
  FLOAT32     m_f32Y;
  FLOAT32     m_f32Angle;
  FLOAT32     m_f32Scale;
  
  // Score
  FLOAT32     m_f32Score;
  FLOAT32     m_f32UniformityScore;
  //FLOAT32     m_f32PureEdgeScore;
  FLOAT32     m_f32HausdorffScore;
};

// ---------------------------------------------------------------------------

// Feature point data
struct EFeaturePoint
{
  // Point coordinates
  INT16       n16X;
  INT16       n16Y;
  
  // Transformed point coordinates
  INT16       n16x;
  INT16       n16y;
  
  // Transformed point offset
  INT32       n32Offset;
  
  // Gradient components
  INT16       n16GX;
  INT16       n16GY;
  
  // Transformed gradient components
  INT16       n16Gx;
  INT16       n16Gy;

  INT32       n32Number;
  BOOL        bHit;
};



struct ERegionFeaturePoint
{
  // Point coordinates
  INT32       n32X, n32Y;

  // Transformed point coordinates
  INT32       n32x, n32y;

  Vector<INT32> LocalRFPGradientVector;

  // Transformed point offset
  INT32       n32Offset;
};

typedef vector<ERegionFeaturePoint> ERegionFeaturePointVector;

typedef vector< vector<INT32> > UniformityBlobVectorType;
typedef vector< UINT8 >         UniformityRangeVectorType;


// Multi-dimensional arrays
template<class Type> class EArray
{
public:
  // Constructor
  E_DLL0 CONSTRUCTOR E_DLL1         EArray              ( );
  E_DLL0 DESTRUCTOR E_DLL1          ~EArray             ( );
                                                  
  // Initialization                               
  E_DLL0 void E_DLL1                SafeFill            ( Type Value);
  
  // Updates
  E_DLL0 void E_DLL1                SetRange            ( INT32 n32MinIndex0, INT32 n32NumElements0);
  E_DLL0 void E_DLL1                SetRange            ( INT32 n32MinIndex0, INT32 n32NumElements0,
                                                          INT32 n32MinIndex1, INT32 n32NumElements1);
  E_DLL0 void E_DLL1                SetRange            ( INT32 n32MinIndex0, INT32 n32NumElements0,
                                                          INT32 n32MinIndex1, INT32 n32NumElements1,
                                                          INT32 n32MinIndex2, INT32 n32NumElements2);
  E_DLL0 void E_DLL1                SetRange            ( INT32 n32MinIndex0, INT32 n32NumElements0,
                                                          INT32 n32MinIndex1, INT32 n32NumElements1,
                                                          INT32 n32MinIndex2, INT32 n32NumElements2,
                                                          INT32 n32MinIndex3, INT32 n32NumElements3);
  E_DLL0 void E_DLL1                SetRange            ( INT32 n32MinIndex0, INT32 n32NumElements0,
                                                          INT32 n32MinIndex1, INT32 n32NumElements1,
                                                          INT32 n32MinIndex2, INT32 n32NumElements2,
                                                          INT32 n32MinIndex3, INT32 n32NumElements3,
                                                          INT32 n32MinIndex4, INT32 n32NumElements4);
  E_DLL0 void E_DLL1                SetRange            ( INT32 n32MinIndex0, INT32 n32NumElements0,
                                                          INT32 n32MinIndex1, INT32 n32NumElements1,
                                                          INT32 n32MinIndex2, INT32 n32NumElements2,
                                                          INT32 n32MinIndex3, INT32 n32NumElements3,
                                                          INT32 n32MinIndex4, INT32 n32NumElements4,
                                                          INT32 n32MinIndex5, INT32 n32NumElements5);
  
  // Queries
  E_DLL0 Type* E_DLL1               GetElement          ( INT32 n32Index0);
  E_DLL0 Type* E_DLL1               GetElement          ( INT32 n32Index0, INT32 n32Index1);
  E_DLL0 Type* E_DLL1               GetElement          ( INT32 n32Index0, INT32 n32Index1, INT32 n32Index2);
  E_DLL0 Type* E_DLL1               GetElement          ( INT32 n32Index0, INT32 n32Index1, INT32 n32Index2, INT32 n32Index3);
  E_DLL0 Type* E_DLL1               GetElement          ( INT32 n32Index0, INT32 n32Index1, INT32 n32Index2, INT32 n32Index3, INT32 n32Index4);
  E_DLL0 Type* E_DLL1               GetElement          ( INT32 n32Index0, INT32 n32Index1, INT32 n32Index2, INT32 n32Index3, INT32 n32Index4, INT32 n32Index5);
  
  E_DLL0 UINT32 E_DLL1              GetNumElements      ( );
                                                  
  E_DLL0 Type* E_DLL1               GetSafeElement      ( INT32 n32Index0) { return ( Type*)&m_pBase[sizeof( Type) * n32Index0]; }
  E_DLL0 Type* E_DLL1               GetSafeElement      ( INT32 n32Index0, INT32 n32Index1) { return ( Type*)&m_pBase[sizeof( Type) * n32Index0 + m_pn32Stride[1] * n32Index1]; }
  E_DLL0 Type* E_DLL1               GetSafeElement      ( INT32 n32Index0, INT32 n32Index1, INT32 n32Index2) { return ( Type*)&m_pBase[sizeof( Type) * n32Index0 + m_pn32Stride[1] * n32Index1 + m_pn32Stride[2] * n32Index2]; }
  E_DLL0 Type* E_DLL1               GetSafeElement      ( INT32 n32Index0, INT32 n32Index1, INT32 n32Index2, INT32 n32Index3) { return ( Type*)&m_pBase[sizeof( Type) * n32Index0 + m_pn32Stride[1] * n32Index1 + m_pn32Stride[2] * n32Index2 + m_pn32Stride[3] * n32Index3]; }
  E_DLL0 Type* E_DLL1               GetSafeElement      ( INT32 n32Index0, INT32 n32Index1, INT32 n32Index2, INT32 n32Index3, INT32 n32Index4) { return ( Type*)&m_pBase[sizeof( Type) * n32Index0 + m_pn32Stride[1] * n32Index1 + m_pn32Stride[2] * n32Index2 + m_pn32Stride[3] * n32Index3 + m_pn32Stride[4] * n32Index4]; }
  E_DLL0 Type* E_DLL1               GetSafeElement      ( INT32 n32Index0, INT32 n32Index1, INT32 n32Index2, INT32 n32Index3, INT32 n32Index4, INT32 n32Index5) { return ( Type*)&m_pBase[sizeof( Type) * n32Index0 + m_pn32Stride[1] * n32Index1 + m_pn32Stride[2] * n32Index2 + m_pn32Stride[3] * n32Index3 + m_pn32Stride[4] * n32Index4 + m_pn32Stride[5] * n32Index5]; }
  
  // Shifting
  E_DLL0 void E_DLL1                Shift               ( INT32 n32Shift0, Type FillValue);
  E_DLL0 void E_DLL1                Shift               ( INT32 n32Shift0, INT32 n32Shift1, Type FillValue);
  E_DLL0 void E_DLL1                Shift               ( INT32 n32Shift0, INT32 n32Shift1, INT32 n32Shift2, Type FillValue);
  E_DLL0 void E_DLL1                Shift               ( INT32 n32Shift0, INT32 n32Shift1, INT32 n32Shift2, INT32 n32Shift3, Type FillValue);
  E_DLL0 void E_DLL1                Shift               ( INT32 n32Shift0, INT32 n32Shift1, INT32 n32Shift2, INT32 n32Shift3, INT32 n32Shift4, Type FillValue);
  E_DLL0 void E_DLL1                Shift               ( INT32 n32Shift0, INT32 n32Shift1, INT32 n32Shift2, INT32 n32Shift3, INT32 n32Shift4, INT32 n32Shift5, Type FillValue);
  
  // Local maxima
  E_DLL0 BOOL E_DLL1                SafeIsStrongLargest ( Type* pElement);
  E_DLL0 BOOL E_DLL1                SafeIsWeakLargest   ( Type* pElement);
  
protected:
  INT32                             m_un32NumDimensions;
  INT32                             m_pn32MinIndex[6];
  INT32                             m_pn32NumElements[6];
  INT32                             m_pn32Stride[6];
                                    
  UINT8                             *m_pData, *m_pBase;
};


// ---------------------------------------------------------------------------

class EScoreArray: public EArray<FLOAT32>
{
};

// ---------------------------------------------------------------------------

const unsigned int FND_MAX_STAGES = 10U;

class EFindStage
{
private:
  // Construction
  CONSTRUCTOR                       EFindStage( );
                                    
  // Score                          
  FLOAT32                           m_f32Score;
  FLOAT32                           m_f32UniformityScore;
  //FLOAT32                           m_f32PureEdgeScore;
  UINT32                            m_un32ScoreCount;
  UINT32                            m_un32TransformCount;
  UINT32                            m_un32NumCandidates;
  INT32                             m_n32Time;

  UINT32                            m_stg_idx;
  BOOL                              m_bAccuracy;

  ERegionFeaturePointVector         m_RegionFeaturePoints;
  UniformityBlobVectorType          m_UniformityRegions;
  UniformityRangeVectorType         m_UniformityRegionsRange;
  INT32                             m_UNIFORMITY_EXTENT;
  INT32                             m_n32BlobsArea;
  FLOAT32                           m_UniformityArea;
  FLOAT32                           m_f32UniformRegionImportance;

  // Feature map
  EVectorTemplate<EFeaturePoint>    m_Feature;
  UINT32                            m_un32MaxFeaturePoints;
  FLOAT32                           m_f32SumPP;
  FLOAT32                           m_f32FairScore[3]; // one fair score for each possible contrast (Normal, Inverse, Any)
                                   
  // Learning ROI ( pivot coordinates)
  INT32                             m_n32LXMin;
  INT32                             m_n32LXMax;
  INT32                             m_n32LYMin;
  INT32                             m_n32LYMax;
  
  // Transformed pattern bounding box ( pivot coordinates)
  INT32                             m_n32BXMin;
  INT32                             m_n32BXMax;
  INT32                             m_n32BYMin;
  INT32                             m_n32BYMax;
  
  // Reference center ( pivot coordinates)
  FLOAT32                           m_f32OffsetX;
  FLOAT32                           m_f32OffsetY;
                                    
  // DOF ranges                     
  INT32                             m_un32NumAngles;
  INT32                             m_un32NumScales;
  FLOAT32                           m_f32AngleMin;
  FLOAT32                           m_f32AngleStep;
  FLOAT32                           m_f32ScaleMin;
  FLOAT32                           m_f32ScaleStep;
                                    
  // Pivot location                 
  INT32                             m_n32PivotX;
  INT32                             m_n32PivotY;

  // Stage find extension
  INT32                             m_n32Extension;

  // Gradient vector image
  EImageBW32                        m_VectorGradient;
                                    
  // Don't Care image               
  EImageBW8                         m_DontCare;      // this one is emptied at the end of the learn processing
  EImageBW8                         m_LocalDontCare; // this one will be kept after the learn processing
                                    
  // Source image                   
  EImageBW8                         m_Source;

                                    
  // Learning                       

  void                              BuildFeaturePoints  ( EROIBW8* pSource, EROIBW32* pVectorGradient,
                                                          EROIBW8* pDontCare, 
                                                          enum FND_FEATURE_SELECTION eFeatureSelection,
                                                          INT32 n32PivotX, INT32 n32PivotY);
  void                              BuildFeaturePoints  ( INT32 un32OrgX, INT32 un32OrgY,
                                                          INT32 un32Width, INT32 un32Height, BOOL bDontCare,
                                                          enum FND_FEATURE_SELECTION eFeatureSelection,
                                                          INT32 n32PivotX, INT32 n32PivotY);
  void                              DrawFeaturePoints   ( HDC hDC, EFindPosition& Position, FLOAT32 f32Zoom = 1.f);
                                    
  UINT32                            m_un32GradientThreshold;
                                    
  // Helpers                        
  FLOAT32                           AverageShift        ( FLOAT32 f32Angle, FLOAT32 f32Scale);
  void                              Transform           ( FLOAT32 f32Angle, FLOAT32 f32Scale,
                                                          INT32 n32ColPitch, INT32 n32RowPitch);
  void                              Scan                ( EScoreArray& Scores, enum FND_CONTRAST_MODE eContrastMode, EVectorTemplate<EFindPosition>& Position);
  void                              FindCandidates      ( EScoreArray& Scores,
                                                          EVectorTemplate<EFindPosition>& Position);

 
  inline void                       AccumulateUniformRegionGradientInConfinedPattern( EBW8 *pbw8Src, INT32 n32SrcRowPitch, INT32 &n32SumSS);
  inline void                       AccumulateUniformRegionGradientInConfinedPattern( EGradient32 *pg32Src, INT32 n32SrcRowPitch, INT32 &n32SumSS);
  inline void                       AccumulateUniformRegionGradientInConfinedPatternExtended( EGradient32 *pg32Src, INT32 n32SrcRowPitch, INT32 &n32SumSS, INT32 n32X, INT32 n32Y);
  inline void                       AccumulateUniformRegionGradientInPattern( EGradient32 *pg32Src, INT32 n32SrcRowPitch, INT32 &n32SumSS, INT32 width, INT32 height , INT32 n32X, INT32 n32Y);
  inline void                       AccumulateUniformRegionGradientInPatternExtended( EGradient32 *pg32Src, INT32 n32SrcRowPitch, INT32 &n32SumSS, INT32 n32X, INT32 n32Y);
  inline void                       AccumulateUniformRegionGradientInConfinedPatternExtended( EBW8 *pbw8Src, INT32 n32SrcRowPitch, INT32 &n32SumSS, INT32 width, INT32 height, INT32 n32X, INT32 n32Y);



  FLOAT32                           Score               ( EROIBW8* pSrc, INT32 n32X, INT32 n32Y,
                                                          enum FND_CONTRAST_MODE eContrastMode,
                                                          BOOL bConfined);
  FLOAT32                           ScoreExtended       ( EROIBW8* pSrc, INT32 n32X, INT32 n32Y,
                                                          enum FND_CONTRAST_MODE eContrastMode);
  FLOAT32                           Score               ( EROIBW32* pSrc, INT32 n32X, INT32 n32Y,
                                                          enum FND_CONTRAST_MODE eContrastMode,
                                                          BOOL bConfined);

  inline FLOAT32                    NonUniformityScore                 (EGradient32 *pbw32Src, INT32 n32Width, INT32 n32Height, INT32 n32X, INT32 n32Y);
  // inline has been removed intentionnaly for the next line to cope with bad MsVc60 compiler
         FLOAT32                    NonUniformityScore                 (EBW8 *pbw8Src, INT32 n32Width, INT32 n32Height, INT32 n32X, INT32 n32Y);
  inline FLOAT32                    NonUniformityScoreExtended         (EBW8 *pbw8Src, INT32 n32X, INT32 n32Y);
  inline FLOAT32                    NonUniformityScoreExtended         (EGradient32 *pbw32Src, INT32 n32X, INT32 n32Y);
  inline FLOAT32                    ConfinedNonUniformityScore         (EGradient32 *pbw32Src);
  inline FLOAT32                    ConfinedNonUniformityScore         (EBW8 *pbw8Src);

  void                              FeaturePointSelection(UINT32 &un32NumFeatures);

  friend class EFind;
};

// ---------------------------------------------------------------------------


// ---------------------------------------------------------------------------

class EFind: public EPointShape
{
public:
  // Constructor
  E_DLL0 CONSTRUCTOR E_DLL1         EFind                   ( );
  
  // Learning
  E_DLL0 void E_DLL1                Learn                   ( EROIBW8* pSource, EROIBW8* pDontCare = NULL);
  E_DLL0 BOOL E_DLL1                GetLearnt               ( ) const;

  // Retrieving a copy of the learnt pattern (caller is reponsible for the image deletion)
  E_DLL0 EImageBW8* E_DLL1          CreatePatternCopy       ( );
                              
  // Search                   
  E_DLL0 void E_DLL1                Find                    ( EROIBW8* pSource);
  
  // Degrees of freedom
  E_DLL0 FLOAT32 E_DLL1             GetAngleBias            ( ) { return EFromRadians( m_f32AngleBias); }
  E_DLL0 void E_DLL1                SetAngleBias            ( FLOAT32 f32AngleBias) { m_f32AngleBias = EToRadians( f32AngleBias); }
                              
  E_DLL0 FLOAT32 E_DLL1             GetAngleTolerance       ( ) { return EFromRadians( m_f32AngleTolerance); }
  E_DLL0 void E_DLL1                SetAngleTolerance       ( FLOAT32 f32AngleTolerance) { m_f32AngleTolerance = EToRadians( f32AngleTolerance); }
                              
  E_DLL0 FLOAT32 E_DLL1             GetScaleBias            ( ) { return m_f32ScaleBias; }
  E_DLL0 void E_DLL1                SetScaleBias            ( FLOAT32 f32ScaleBias) { m_f32ScaleBias = f32ScaleBias; }
                              
  E_DLL0 FLOAT32 E_DLL1             GetScaleTolerance       ( ) { return m_f32ScaleTolerance; }
  E_DLL0 void E_DLL1                SetScaleTolerance       ( FLOAT32 f32ScaleTolerance) { m_f32ScaleTolerance = f32ScaleTolerance; }
                              
  // Interpolation            
  E_DLL0 BOOL E_DLL1                GetInterpolate          ( ) { return m_bInterpolate; }
  E_DLL0 void E_DLL1                SetInterpolate          ( BOOL bInterpolate) { m_bInterpolate = bInterpolate; }

  // Matching mode
  E_DLL0 enum FND_CONTRAST_MODE E_DLL1  GetContrastMode     ( ) { return m_eContrastMode; }
  E_DLL0 void E_DLL1                SetContrastMode         ( enum FND_CONTRAST_MODE eContrastMode) { m_eContrastMode = eContrastMode; }

  // Geometry
  E_DLL0 void E_DLL1                SetCenter               ( EPoint Point) { SetCenter( Point.GetX( ), Point.GetY( )); }
  E_DLL0 void E_DLL1                SetCenter               ( FLOAT32 f32CenterX, FLOAT32 f32CenterY);

  // Search criteria
  E_DLL0 UINT32 E_DLL1              GetMaxInstances         ( ) { return m_un32MaxInstances; }
  E_DLL0 void E_DLL1                SetMaxInstances         ( UINT32 un32MaxInstances) { m_un32MaxInstances = un32MaxInstances; }
                              
  E_DLL0 FLOAT32 E_DLL1             GetMinScore             ( ) { return m_f32MinScore; }
  E_DLL0 void E_DLL1                SetMinScore             ( FLOAT32 f32MinScore) { m_f32MinScore = f32MinScore; }
                              
  // Search results           
  E_DLL0 UINT32 E_DLL1              GetNumInstances         ( );
  E_DLL0 void E_DLL1                SelectInstance          ( UINT32 un32Index);
  E_DLL0 FLOAT32 E_DLL1             GetCenterX              ( );
  E_DLL0 FLOAT32 E_DLL1             GetCenterY              ( );
  E_DLL0 FLOAT32 E_DLL1             GetAngle                ( );
  E_DLL0 FLOAT32 E_DLL1             GetScale                ( );
  E_DLL0 FLOAT32 E_DLL1             GetScore                ( );
  
  // Drawing
  E_DLL0 void E_DLL1                DrawInstance            ( HDC hDC, BOOL bEdges = FALSE);
  E_DLL0 void E_DLL1                DrawInstances           ( HDC hDC, BOOL bEdges = FALSE);
  E_DLL0 void E_DLL1                DrawInstance            ( Euresys::DrawAdapter* drawAdapter, BOOL bEdges);
  E_DLL0 void E_DLL1                DrawInstances           ( Euresys::DrawAdapter* drawAdapter, BOOL bEdges);

  // Selection
  E_DLL0 UINT32 E_DLL1              ClosestInstance         ( INT32 n32CursorX, INT32 n32CursorY);

  // Advanced

  E_DLL0 enum FND_COARSE_TO_FINE_ANALYSIS_MODE E_DLL1 GetCoarseToFineAnalysisMode  ( ) { return static_cast<FND_COARSE_TO_FINE_ANALYSIS_MODE>(m_eCoarseToFineAnalysisMode); }
  E_DLL0 void E_DLL1                SetCoarseToFineAnalysisMode       ( enum FND_COARSE_TO_FINE_ANALYSIS_MODE eCoarseToFineAnalysisMode);

  E_DLL0 UINT32 E_DLL1              GetCoarseStage          ( ) { return m_un32CoarseStage; }
  E_DLL0 void E_DLL1                SetCoarseStage          ( UINT32 un32CoarseStage) { m_un32CoarseStage = un32CoarseStage; }
                              
  E_DLL0 UINT32 E_DLL1              GetFineStage            ( ) { return m_un32FineStage; }
  E_DLL0 void E_DLL1                SetFineStage            ( UINT32 un32FineStage) { m_un32FineStage = un32FineStage; }
                              
  E_DLL0 UINT32 E_DLL1              GetMinFeaturePoints     ( ) { return m_un32MinFeaturePoints; }
  E_DLL0 void E_DLL1                SetMinFeaturePoints     ( UINT32 un32MinFeaturePoints) { m_un32MinFeaturePoints = un32MinFeaturePoints; }
                                                  
  E_DLL0 UINT32 E_DLL1              GetMaxFeaturePoints     ( ) { return m_un32MaxFeaturePoints; };
  E_DLL0 void E_DLL1                SetMaxFeaturePoints     ( UINT32 un32MaxFeaturePoints) { m_un32MaxFeaturePoints = un32MaxFeaturePoints; };
                              
  E_DLL0 BOOL E_DLL1                GetStrongMaxima         ( ) { return m_bStrongMaxima; };
  E_DLL0 void E_DLL1                SetStrongMaxima         ( BOOL bStrongMaxima) { m_bStrongMaxima = bStrongMaxima; };
                              
  E_DLL0 FLOAT32 E_DLL1             GetScoreFactor          ( ) { return m_f32ScoreFactor; };
  E_DLL0 void E_DLL1                SetScoreFactor          ( FLOAT32 f32ScoreFactor) { m_f32ScoreFactor = f32ScoreFactor; };

  E_DLL0 enum FND_PATTERN_TYPE E_DLL1    GetPatternType          ( ) const;
  E_DLL0 void E_DLL1                SetPatternType          ( FND_PATTERN_TYPE val);

  E_DLL0 enum FND_FEATURE_SELECTION E_DLL1  GetFeatureSelection( ) { return m_eFeatureSelection; };
  E_DLL0 void E_DLL1                SetFeatureSelection ( enum FND_FEATURE_SELECTION eFeatureSelection) { m_eFeatureSelection = eFeatureSelection; };

  // Local Search Mode
  E_DLL0 void E_DLL1                SetLocalSearchMode  (enum FND_LOCAL_SEARCH_MODE eLocalSearchMode);
  E_DLL0 enum FND_LOCAL_SEARCH_MODE E_DLL1  GetLocalSearchMode  ();

  // Local Search Extents
  E_DLL0 void E_DLL1                SetAngleSearchExtent(INT32 n32Extent);
  E_DLL0 void E_DLL1                SetScaleSearchExtent(INT32 n32Extent);
  E_DLL0 void E_DLL1                SetXSearchExtent(INT32 n32Extent);
  E_DLL0 void E_DLL1                SetYSearchExtent(INT32 n32Extent);

  E_DLL0 INT32 E_DLL1               GetAngleSearchExtent();
  E_DLL0 INT32 E_DLL1               GetScaleSearchExtent();
  E_DLL0 INT32 E_DLL1               GetXSearchExtent();
  E_DLL0 INT32 E_DLL1               GetYSearchExtent();

  // Typing
  E_DLL0 INS_SHAPE_TYPES E_DLL1     GetType             ( );

  // Find ROI Extension
  E_DLL0 INT32 E_DLL1               GetFindExtension();
  E_DLL0 void  E_DLL1               SetFindExtension(INT32 n32Extension);
  
  // Pyramid
  EFindStage                        m_pStage[FND_MAX_STAGES];
  UINT32                            m_un32NumStages;
  UINT32                            m_un32InitialStage;
  UINT32                            m_un32FinalStage;

  Euresys::eVision::Point           pivot;

  E_DLL0 void E_DLL1                GetInternalFeaturePoints(INT32 inst, Euresys::eVision::Utils::Vector<Euresys::eVision::Point>& featurePoints, Euresys::eVision::Utils::Vector<Euresys::eVision::Point>& rectangleCorners);
  // For drawing purposes
  EImageBW8                         m_UniformRegionImg; 
protected:
  // Serialization
  E_DLL0 void virtual E_DLL1        Serialize ( ESerializer* serializer, UINT32 un32FileVersion, BOOL bDaughters = TRUE);             
  E_DLL0 void virtual E_DLL1        Serialize ( FILE* pFile, BOOL bWrite, UINT32 un32FileVersion, BOOL bDaughters = TRUE);             

  FLOAT32                           m_f32AngleBias; 
  FLOAT32                           m_f32AngleTolerance; 
  FLOAT32                           m_f32ScaleBias; 
  FLOAT32                           m_f32ScaleTolerance; 
  BOOL                              m_bInterpolate; 
  FND_CONTRAST_MODE                 m_eContrastMode; 
  UINT32                            m_un32MaxInstances; 
  FLOAT32                           m_f32MinScore; 
  UINT32                            m_un32CoarseStage; 
  UINT32                            m_un32FineStage; 
  UINT32                            m_un32MinFeaturePoints; 
  UINT32                            m_un32MaxFeaturePoints; 
  BOOL                              m_bStrongMaxima; 
  FLOAT32                           m_f32ScoreFactor; 
  FLOAT32                           m_f32UniformRegionImportance;
  FND_FEATURE_SELECTION             m_eFeatureSelection;

                                    
private:                            
  // Position                       
  EFrame                            m_Instance;
  INT32                             m_n32RoiOrgX;
  INT32                             m_n32RoiOrgY;
  INT32                             m_n32RoiWidth;
  INT32                             m_n32RoiHeight;
  FLOAT32                           m_f32PivotX;
  FLOAT32                           m_f32PivotY;
                                    
  // Learnt source pattern
  EImageBW8                         m_Source;
                                    
  //HausDorff Map
  EVectorTemplate<EFeaturePoint>    m_HaussDorfEdgePosition;
  ECodedImage                       m_InstanceCodedImage;
  EImageBW32                        m_HausdorffNumber;
  EImageBW8                         m_HausdorffMap;
  EImageBW8                         m_HausdorffInstance;
  EImageBW8                         m_ThresholdedUniformRegion;
  INT32                             m_n32MinSizeEdges;
  INT32                             m_UniformRegionSize;
  UINT8                             m_HausdorffDistanceMax;





  INT32                             m_n32LearntRoiOrgX;
  INT32                             m_n32LearntRoiOrgY;
                                    
                                    
  // Scores array                   
  EScoreArray                       m_Scores;
  EScoreArray                       m_UniformityScores;
  //EScoreArray                       m_PureEdgeScores;

  FLOAT32                           *m_pf32Score;
                                    
  // Candidates list
  EVectorTemplate<EFindPosition>    m_Candidate;

  // Instance selection
  EFindPosition                     *m_pInstance;
                                    
  // State                          
  enum FND_STATES                   m_eState;
  BOOL                              m_bDontCare;
                                    
  // Helpers                        
  void                              SetupPyramid        ( EROIBW8* pSource, EROIBW8* pDontCare);
  void                              SetupExtendedPyramid(EROIBW8* pSrc);
  FLOAT32                           QuadriOptimum       ( FLOAT32& f32X, FLOAT32& f32Y, FLOAT32& f32Z, FLOAT32& f32T);

  // Find Neighborhood
  FND_LOCAL_SEARCH_MODE        m_eLocalSearchMode; 
  
  FND_COARSE_TO_FINE_ANALYSIS_MODE              m_eCoarseToFineAnalysisMode;



  INT32                             m_pn32MinScaleOffset[FND_MAX_STAGES];
  INT32                             m_pn32MinAngleOffset[FND_MAX_STAGES];
  INT32                             m_pn32MinOrdinateOffset[FND_MAX_STAGES];
  INT32                             m_pn32MinAbscissaOffset[FND_MAX_STAGES];

  INT32                             m_pn32MaxScaleOffset[FND_MAX_STAGES];
  INT32                             m_pn32MaxAngleOffset[FND_MAX_STAGES];
  INT32                             m_pn32MaxOrdinateOffset[FND_MAX_STAGES];
  INT32                             m_pn32MaxAbscissaOffset[FND_MAX_STAGES];

  INT32                             m_pn32ScaleKernelSize[FND_MAX_STAGES];
  INT32                             m_pn32AngleKernelSize[FND_MAX_STAGES];
  INT32                             m_pn32OrdinateKernelSize[FND_MAX_STAGES];
  INT32                             m_pn32AbscissaKernelSize[FND_MAX_STAGES];

  INT32                             m_n32MinScaleOffset;
  INT32                             m_n32MinAngleOffset;
  INT32                             m_n32MinOrdinateOffset;
  INT32                             m_n32MinAbscissaOffset;

  INT32                             m_n32ScaleKernelSize;
  INT32                             m_n32AngleKernelSize;
  INT32                             m_n32OrdinateKernelSize;
  INT32                             m_n32AbscissaKernelSize;

  // Find Search Extension
  INT32                             m_n32FindExtension;

private:
  void                    BuildRegionFeaturePoints(INT32 un32OrgX, INT32 un32OrgY, INT32 un32Width, INT32 un32Height, EROIBW8* pSrc, EFindStage &stage);
  void                    FindRegionFeaturePoints(EROIBW8* PatternRoi, EROIBW16* RegionImg, EFindStage &stage, INT32 un32OrgX, INT32 un32OrgY);
  void                    CorrelateRegions(EROIBW8* pSrc);
  void                    ComputeUniformityRegionArea(EFindStage& stage, INT32 width, INT32 height);
  void                    BuildLocalGradientVectors(EFindStage &stage, Vector<Pointn32> &BlobPtsList);

  //HausDorff
  void                    BuildHausDorffMap( EROIBW8* pSrc, EROIBW32* pNum);
  void                    HausdorffScore(EROIBW8* pScoreMap = NULL, EROIBW8* pSrc = NULL);
  void                    ComputeInstanceHausdorffFP(EVectorTemplate<EFeaturePoint>& instanceHausdorffFP, FLOAT32& f32ThresholdedDifference);
  




  void                    DrawCandidates( HDC hDC, UINT32 stg_idx, BOOL bFull, BOOL bEdges /* = FALSE */);
  void                    DrawCandidateFullResolution(HDC hDC, UINT32 stg_idx, UINT32 index, BOOL bEdges /* = FALSE */);
  void                    DrawCandidate( HDC hDC, UINT32 stg_idx, UINT32 index, BOOL bEdges);

  void                    ImgLocalMeanAndStdDeviation(EROIBW8* pImg, EROIBW8* pMean, EROIBW8* pStdDev, EImageBW16 &varImg16, INT32 UNIFORMITY_KSIZE);

  void                    ComputeExtents(); 

  public:
#ifdef HAUSDORFF_DEBUG
E_DLL0 void E_DLL1                   ScoreMap(EROIBW8* pScoreMap, EROIBW8* pSrc);
   E_DLL0 void E_DLL1                   ComputeInstanceHausdorffFPDebug(EROIBW8* pSrc, INT32 x, INT32 y);
   E_DLL0 void E_DLL1                   ComputeUniformityScore(EROIBW8* pSrc, INT32 x, INT32 y, EPlotDebug* myplot);
#endif
};

// ---------------------------------------------------------------------------

#endif //__EFIND_IMPL_H__
