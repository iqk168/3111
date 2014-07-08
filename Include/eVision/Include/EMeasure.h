////////////////////////////////////////////////////////////////////////////////////////////////////
// EMeasure.h: EasyMeasure library header file for eVision 6.7.1.0
//
// EasyMeasure performs sub-pixel precision geometric measurements
//
// Copyright ( c) 1997-2006, Euresys. All rights reserved.
//

#ifndef __EMEASURE_H__
#define __EMEASURE_H__

// eVision header files
#include "Easy.h"

////////////////////////////////////////////////////////////////////////////////
// Constant definitions
//

// Transition type
enum MEASURE_TRANSITION_TYPE
{ 
  MEASURE_BW = 0,
    MEASURE_WB = 1,
    MEASURE_WB_OR_BW = 2,
    MEASURE_BWB = 3,
    MEASURE_WBW = 4,
    UNKNOWN  = 0xFFFFFFFF
};

// Transition choice
enum MEASURE_TRANSITION_CHOICE
{ 
  MEASURE_BEST_SHARPNESS = 0,
    MEASURE_CENTER = 1,
    MEASURE_FROM_BEGIN = 2, 
    MEASURE_FROM_END = 3,
    MEASURE_TRANSITION_CHOICE_UNKNOWN  = 0xFFFFFFFF
};

// Measure type
enum MEASURE_TYPE
{ 
  MEASURE_POINT,
    MEASURE_LINE,
    MEASURE_PARABOLA,
    MEASURE_CIRCLE,
    MEASURE_TYPE_UNKNOWN  = 0xFFFFFFFF
};

// Tolerance direction
enum MEASURE_TOLERANCE_VERTICALLY
{ 
  MEASURE_HORIZONTAL = 0,
    MEASURE_VERTICAL = 1,
    MEASURE_TOLERANCE_UNKNOWN  = 0xFFFFFFFF
};

// Transition smoothing
enum MEASURE_TRANSITION_SMOOTHING
{ 
  MEASURE_NO_SMOOTHING = 0,
    MEASURE_INTEGRATION_ACROSS_3_PIXELS = 1,
    MEASURE_INTEGRATION_ACROSS_5_PIXELS = 2,
    MEASURE_INTEGRATION_ACROSS_7_PIXELS = 4, // CAUTION !
    MEASURE_INTEGRATION_ACROSS_9_PIXELS = 3,
    MEASURE_INTEGRATION_UNKNOWN  = 0xFFFFFFFF
};

// Tolerance orientation
enum MEASURE_INVERSE_TRANSITION
{ 
  MEASURE_TOP_BOTTOM_LEFT_RIGHT = 0,
    MEASURE_BOTTOM_TOP_RIGHT_LEFT = 1,
    MEAUSRE_INVERSE_TRANSITION_UNKNOWN  = 0xFFFFFFFF
};

// Tolerance slope
enum MEASURE_SLOPE
{ 
  MEASURE_VARYING_SLOPE = 0,
    MEASURE_FIXED_SLOPE = 1,
    MEASURE_SLOPE_UNKNOWN  = 0xFFFFFFFF
};

// Base direction
enum MEASURE_BASE_VERTICALLY
{ 
  MEASURE_MORE_HORIZONTAL_LINE = 0,
    MEASURE_MORE_VERTICAL_LINE = 1,
    MEASURE_BASE_UNKNOWN  = 0xFFFFFFFF
};

// Circle centering mode
enum MEASURE_CIRCLE_CENTERING
{ 
  MEASURE_NO_PREADJUSTED_CIRCLE_CENTER = 0,
    MEASURE_PREADJUSTED_CIRCLE_CENTER = 1,
    MEAUSRE_CIRCLE_CENTERING_UNKNOWN  = 0xFFFFFFFF
};

// Circle fitting mode
enum MEASURE_CIRCLE_ISOTROPIC
{ 
  MEASURE_USE_GENERAL_ALGORITHM = 0,
    MEASURE_USE_OPTIMISED_ALGORITHM = 1,
    MEASURE_CIRCLE_ISOTROPIC_UNKNOWN  = 0xFFFFFFFF
};

// Circle fitting stopping criterion
enum MEASURE_CIRCLE_AUTOMATIC_STOP
{ 
  MEASURE_ITERATE_UNTIL_THRESHOLD = 0,
    MEASURE_ITERATE_UNTIL_COUNT = 1,
    MEASURE_CIRCLE_ITERATE_STOP_UNKNOWN  = 0xFFFFFFFF
};

// Drawing modes
enum MEASURE_DRAWING_MODE
{
  MEASURE_DRAW_NOMINAL, // Point, line or circle
    MEASURE_DRAW_TRANSITION, // Transition symbol
    MEASURE_DRAW_TOLERANCE, // Segment, rectangle or curved rectangle
    MEASURE_DRAW_MEASURED, // Point, line ( segment) or circle ( arc)
    MEASURE_DRAW_SAMPLED_TOLERANCES, // Sampled segments along the model ( segment or arc)
    MEASURE_DRAW_SAMPLED_POINTS, // Measured points along the model ( segment or arc)
    MEASURE_DRAW_INVALID_SAMPLED_POINTS, // Bad measured points along the model ( segment or arc)
    MEASURE_DRAW_UNKNOWN  = 0xFFFFFFFF
};

// Handle names
enum MEASURE_HANDLES
{
  MEASURE_HANDLE_NONE,
    MEASURE_HANDLE_ORG, // Segment or arc origin
    MEASURE_HANDLE_MID, // Center point
    MEASURE_HANDLE_END, // Segment or arc end
    MEASURE_HANDLE_TOL0, // First tolerance
    MEASURE_HANDLE_TOL1, // Second tolerance
    MEASURE_HANDLE_CENTER, // Circle center
    MEASURE_HANDLE_UNKNOWN  = 0xFFFFFFFF
};

#define MEASURE_CIRCLE_SAMPLING_STEP_DEF_VALUE 1
#define MEASURE_PROJECTION_THICKNESS_DEF_VALUE 1
#define MEASURE_TRANSITION_HYSTERESIS_DEF_VALUE 5 
#define MEASURE_DERIVATIVE_THRESHOLD_DEF_VALUE 5 
#define MEASURE_SAMPLING_STEP_DEF_VALUE 5.f
#define MEASURE_CIRCLE_ITERATION_COUNT_DEF_VALUE 8
#define MEASURE_TRANSITION_MIN_GRAY_STEP_DEF_VALUE 20
#define MEASURE_OUTLINE_TOLERANCE_DEF_VALUE 20
#define MEASURE_POINT_HV_TOLERANCE_DEF_VALUE 32

#define MEASURE_SECTOR_AXE_DEF_VALUE TURN_2Q
#define MEASURE_SECTOR_EXCURSION_DEF_VALUE eVision_TWO_PI
#define MEASURE_RATIO_X_BY_Y_DEF_VALUE 1.0F
#define MEASURE_CIRCLE_MAX_DISPLACEMENT_DEF_VALUE 0.015625F // 1/64 //
#define MEASURE_FILTERING_THRESHOLD_DEF_VALUE 2.0F
#define MEASURE_BASE_SIZE_DEF_VALUE 128.0F
#define MEASURE_NOMINAL_RADIUS_DEF_VALUE 50.0F
#define MEASURE_MEASURED_RADIUS_DEF_VALUE 50.0F
#define MEASURE_NOMINAL_Y_DEF_VALUE 50.0F
#define MEASURE_MEASURED_Y_DEF_VALUE 50.0F
#define MEASURE_NOMINAL_X_DEF_VALUE 50.0F
#define MEASURE_MEASURED_X_DEF_VALUE 50.0F

// m_n32CircleNormalPoint
#define MEASURE_CIRCLE_SAMPLE_R_TETA 3

struct MsrSampleStruct
{
  FLOAT32 f32SampleXR;
  FLOAT32 f32SampleYTheta;
  FLOAT32 f32SampleDeviation;
  INT32 n32SampleValid;
  INT32 n32MeasuredGrayStep;
};

typedef struct MsrSampleStruct MEASURE_SAMPLE;


////////////////////////////////////////////////////////////////////////////////
// EMeasure class
//

class EMeasure
{
public:
  // Constructor/destructor
  E_DLL0 CONSTRUCTOR E_DLL1  EMeasure( );
  virtual E_DLL0 DESTRUCTOR E_DLL1  ~EMeasure( );
  
  // ROI origin
  INT32 m_n32OrgX, m_n32OrgY;
  
  // Profile vectors
  EVector m_ProfileData;
  EVector m_ProfileDerivative;
  
  // Sample points vector
  EVector m_SamplePoints;
  
  // Calibration
  E_DLL0 void E_DLL1  GetPixelDimensions( FLOAT32& f32PixelWidth, FLOAT32& f32PixelHeight, const EMeasurementUnit*( &pUnitofLength));
  E_DLL0 void E_DLL1  SetPixelDimensions( FLOAT32 f32PixelWidth, FLOAT32 f32PixelHeight, EMeasurementUnit* pPixelUnitOfLength = &EUnitNone);
  
  // Data members access
  E_DLL0 INT32 E_DLL1  GetID( ); 
  E_DLL0 INT32 E_DLL1  GetTransitionType( );
  E_DLL0 INT32 E_DLL1  GetInverseTransition( );
  E_DLL0 INT32 E_DLL1  GetProjectionThickness( );
  E_DLL0 INT32 E_DLL1  GetTransitionSmoothing( );
  E_DLL0 INT32 E_DLL1  GetDerivativeThreshold( );
  E_DLL0 INT32 E_DLL1  GetTransitionChoice( );
  E_DLL0 INT32 E_DLL1  GetTransitionHysteresis( );
  E_DLL0 INT32 E_DLL1  GetTransitionMinGrayStep( );
  E_DLL0 INT32 E_DLL1  GetPointToleranceVertically( );
  E_DLL0 INT32 E_DLL1  GetType( );
  E_DLL0 FLOAT32 E_DLL1  GetSamplingStep( );
  E_DLL0 INT32 E_DLL1  GetFilteringCount( );
  E_DLL0 INT32 E_DLL1  GetFixedSlope( );
  E_DLL0 INT32 E_DLL1  GetBaseVertically( );
  E_DLL0 INT32 E_DLL1  GetCircleCentering( );
  E_DLL0 INT32 E_DLL1  GetCircleIsotropic( );
  E_DLL0 INT32 E_DLL1  GetCircleIterationCount( );
  E_DLL0 INT32 E_DLL1  GetPointCount( );
  E_DLL0 INT32 E_DLL1  GetPointValidCount( );
  E_DLL0 INT32 E_DLL1  GetTransitionNumber( );
  E_DLL0 BOOL E_DLL1  GetAllTransitions( ) ;
  E_DLL0 INT32 E_DLL1  GetDetectOnly( );
  E_DLL0 INT32 E_DLL1  GetCircleNormalPoint( );
  E_DLL0 INT32 E_DLL1  GetCircleAutomaticStop( );
  E_DLL0 INT32 E_DLL1  GetMeasuredGrayStep( UINT32 un32Index = 0);
  E_DLL0 FLOAT32 E_DLL1  GetPointPositionX( );
  E_DLL0 FLOAT32 E_DLL1  GetPointPositionY( );
  E_DLL0 FLOAT32 E_DLL1  GetPointHVTolerance( );
  E_DLL0 FLOAT32 E_DLL1  GetPointSlope( );
  E_DLL0 FLOAT32 E_DLL1  GetPointAngle( );
  E_DLL0 FLOAT32 E_DLL1  GetOutlineTolerance( );
  E_DLL0 FLOAT32 E_DLL1  GetFilteringThreshold( );
  E_DLL0 FLOAT32 E_DLL1  GetNominalX( );
  E_DLL0 FLOAT32 E_DLL1  GetNominalY( );
  E_DLL0 FLOAT32 E_DLL1  GetNominalRadius( );
  E_DLL0 FLOAT32 E_DLL1  GetNominalSlope( );
  E_DLL0 FLOAT32 E_DLL1  GetBaseSize( );
  E_DLL0 FLOAT32 E_DLL1  GetBaseAngle( );
  E_DLL0 FLOAT32 E_DLL1  GetSectorAxe( );
  E_DLL0 FLOAT32 E_DLL1  GetSectorExcursion( );
  E_DLL0 FLOAT32 E_DLL1  GetCircleMaxDisplacement( );
  E_DLL0 FLOAT32 E_DLL1  GetMeasuredX( UINT32 un32Index = 0);
  E_DLL0 FLOAT32 E_DLL1  GetMeasuredY( UINT32 un32Index = 0);
  E_DLL0 BOOL E_DLL1  GetValidPoint( UINT32 un32Index = 0);
  E_DLL0 FLOAT32 E_DLL1  GetRelativePosition( UINT32 un32Index = 0);
  E_DLL0 FLOAT32 E_DLL1  GetMeasuredRadius( );
  E_DLL0 FLOAT32 E_DLL1  GetMeasuredSlope( );
  E_DLL0 FLOAT32 E_DLL1  GetMeasuredStdDeviation( );
  E_DLL0 FLOAT32 E_DLL1  GetMeasuredAngle( );
  
  E_DLL0 void E_DLL1  SetID( INT32 n32NewValue);
  E_DLL0 void E_DLL1  SetTransitionType( INT32 n32NewValue);
  E_DLL0 void E_DLL1  SetInverseTransition( INT32 n32NewValue);
  E_DLL0 void E_DLL1  SetProjectionThickness( INT32 n32NewValue);
  E_DLL0 void E_DLL1  SetTransitionSmoothing( INT32 n32NewValue);
  E_DLL0 void E_DLL1  SetDerivativeThreshold( INT32 n32NewValue);
  E_DLL0 void E_DLL1  SetTransitionChoice( INT32 n32NewValue);
  E_DLL0 void E_DLL1  SetTransitionHysteresis( INT32 n32NewValue);
  E_DLL0 void E_DLL1  SetTransitionMinGrayStep( INT32 n32NewValue);
  E_DLL0 void E_DLL1  SetPointToleranceVertically( INT32 n32NewValue);
  E_DLL0 void E_DLL1  SetType( INT32 n32NewValue);
  E_DLL0 void E_DLL1  SetSamplingStep( FLOAT32 f32NewValue);
  E_DLL0 void E_DLL1  SetFilteringCount( INT32 n32NewValue);
  E_DLL0 void E_DLL1  SetFixedSlope( INT32 n32NewValue);
  E_DLL0 void E_DLL1  SetBaseVertically( INT32 n32NewValue);
  E_DLL0 void E_DLL1  SetCircleCentering( INT32 n32NewValue);
  E_DLL0 void E_DLL1  SetCircleIsotropic( INT32 n32NewValue);
  E_DLL0 void E_DLL1  SetCircleIterationCount( INT32 n32NewValue);
  E_DLL0 void E_DLL1  SetPointCount( INT32 n32NewValue);
  E_DLL0 void E_DLL1  SetPointValidCount( INT32 n32NewValue);
  E_DLL0 void E_DLL1  SetTransitionNumber( INT32 n32NewValue = ~0);
  E_DLL0 void E_DLL1  SetDetectOnly( INT32 n32NewValue);
  E_DLL0 void E_DLL1  SetCircleNormalPoint( INT32 n32NewValue);
  E_DLL0 void E_DLL1  SetCircleAutomaticStop( INT32 n32NewValue);
  E_DLL0 void E_DLL1  SetMeasuredGrayStep( INT32 n32NewValue);
  E_DLL0 void E_DLL1  SetFilteringThreshold( FLOAT32 f32NewValue);
  E_DLL0 void E_DLL1  SetPointPositionX( FLOAT32 f32NewValue);
  E_DLL0 void E_DLL1  SetPointPositionY( FLOAT32 f32NewValue);
  E_DLL0 void E_DLL1  SetPointSlope( FLOAT32 f32NewValue);
  E_DLL0 void E_DLL1  SetPointAngle( FLOAT32 f32NewValue);
  E_DLL0 void E_DLL1  SetPointHVTolerance( FLOAT32 f32NewValue);
  E_DLL0 void E_DLL1  SetOutlineTolerance( FLOAT32 f32NewValue);
  E_DLL0 void E_DLL1  SetNominalX( FLOAT32 f32NewValue);
  E_DLL0 void E_DLL1  SetNominalY( FLOAT32 f32NewValue);
  E_DLL0 void E_DLL1  SetNominalRadius( FLOAT32 f32NewValue);
  E_DLL0 void E_DLL1  SetNominalSlope( FLOAT32 f32NewValue);
  E_DLL0 void E_DLL1  SetBaseSize( FLOAT32 f32NewValue);
  E_DLL0 void E_DLL1  SetBaseAngle( FLOAT32 f32Angle);
  E_DLL0 void E_DLL1  SetSectorAxe( FLOAT32 f32NewValue);
  E_DLL0 void E_DLL1  SetSectorExcursion( FLOAT32 f32NewValue);
  E_DLL0 void E_DLL1  SetCircleMaxDisplacement( FLOAT32 f32NewValue);
  E_DLL0 void E_DLL1  SetMeasuredStdDeviation( FLOAT32 f32NewValue);
  
  E_DLL0 void E_DLL1  Draw( HDC hDC,
    enum MEASURE_DRAWING_MODE eDrawingMode = MEASURE_DRAW_MEASURED, BOOL bHandles = FALSE,
    FLOAT32 f32ZoomX = 1.f, FLOAT32 f32ZoomY = 0.f, FLOAT32 f32PanX = 0.f, FLOAT32 f32PanY = 0.f);
  
  E_DLL0 enum MEASURE_HANDLES E_DLL1  HitTest( INT32 n32X, INT32 n32Y,
    FLOAT32 f32ZoomX = 1.f, FLOAT32 f32ZoomY = 0.f, FLOAT32 f32PanX = 0.f, FLOAT32 f32PanY = 0.f);
  E_DLL0 void E_DLL1  Drag( enum MEASURE_HANDLES eHandle, INT32 n32X, INT32 n32Y,
    FLOAT32 f32ZoomX = 1.f, FLOAT32 f32ZoomY = 0.f, FLOAT32 f32PanX = 0.f, FLOAT32 f32PanY = 0.f);
  
 private :
   // Global parameters
   MEASURE_TYPE m_eType;
   INT32 m_n32ID;
   
   // Handles
   INT32 m_n32CenterX, m_n32CenterY;
   INT32 m_n32Org0X, m_n32Org0Y, m_n32Mid0X, m_n32Mid0Y, m_n32End0X, m_n32End0Y;
   INT32 m_n32Org1X, m_n32Org1Y, m_n32Mid1X, m_n32Mid1Y, m_n32End1X, m_n32End1Y;
   INT32 m_n32Org2X, m_n32Org2Y, m_n32Mid2X, m_n32Mid2Y, m_n32End2X, m_n32End2Y;
   FLOAT32 m_f32AngleOrg, m_f32AngleMid, m_f32AngleEnd;
   
   // True scale
   BOOL m_bTrueScale;
   EDimensionalValue m_PixelWidth;
   EDimensionalValue m_PixelHeight;
   
   // Points
   // Transition description
   enum MEASURE_TRANSITION_TYPE m_eTransitionType;
   INT32 m_n32InverseTransition;
   INT32 m_n32TransitionChoice;
   INT32 m_n32TransitionNumber; 
   INT32 m_n32DetectOnly; 
   FLOAT32 m_f32RelativePosition;
   BOOL m_bAll;
   
   // Transition steepness
   INT32 m_n32DerivativeThreshold;
   INT32 m_n32TransitionHysteresis;
   INT32 m_n32TransitionMinGrayStep;
   
   // Pre-filtering
   INT32 m_n32ProjectionThickness;
   INT32 m_n32TransitionSmoothing;
   
   // Reference geometry ( true scale coordinates)
   FLOAT32 m_f32PointPositionX;
   FLOAT32 m_f32PointPositionY;
   FLOAT32 m_f32PointSlope; 
   FLOAT32 m_f32PointHVTolerance;
   INT32 m_n32PointToleranceVertically;
   
   // Lines and circles
   // Reference geometry ( true scale coordinates)
   FLOAT32 m_f32NominalX; 
   FLOAT32 m_f32NominalY; 
   FLOAT32 m_f32NominalRadius; 
   FLOAT32 m_f32NominalSlope; 
   enum MEASURE_SLOPE m_eFixedSlope; 
   
   // Geometry delimiting ( true scale coordinates)
   INT32 m_n32BaseVertically; 
   FLOAT32 m_f32BaseSize; 
   
 public:
   FLOAT32 m_f32SectorAxe; 
   FLOAT32 m_f32SectorExcursion; 
   
 private:
   // Sampling parameters
   FLOAT32 m_f32SamplingStep; 
   FLOAT32 m_f32OutlineTolerance; 
   
   // Samples post-filtering
   INT32 m_n32FilteringCount; 
   FLOAT32 m_f32FilteringThreshold; 
   
   // Algorithm options and stopping criteria
   INT32 m_n32CircleCentering; 
   INT32 m_n32CircleIsotropic; 
   INT32 m_n32CircleNormalPoint; 
   INT32 m_n32CircleIterationCount; 
   INT32 m_n32CircleAutomaticStop; 
   FLOAT32 m_f32CircleMaxDisplacement; 
   
   // Measurement results ( true scale coordinates)
   FLOAT32 m_f32MeasuredX; 
   FLOAT32 m_f32MeasuredY; 
   FLOAT32 m_f32MeasuredRadius; 
   FLOAT32 m_f32MeasuredSlope; 
   FLOAT32 m_f32MeasuredStdDeviation; 
   INT32 m_n32MeasuredGrayStep;
   INT32 m_n32PointCount; 
   INT32 m_n32PointValidCount; 
   
   void NominalHandles( FLOAT32 f32ZoomX, FLOAT32 f32ZoomY, FLOAT32 f32PanX, FLOAT32 f32PanY);
   void ToleranceHandles( FLOAT32 f32ZoomX, FLOAT32 f32ZoomY, FLOAT32 f32PanX, FLOAT32 f32PanY);
   
   void DrawTransition( HDC hDC, INT32 n32OrgX, INT32 n32OrgY, FLOAT32 f32Angle);
   
   friend void CalculateBarycentre( EMeasure*, MEASURE_SAMPLE*);
   friend void CalculateLineSlope( EMeasure*, MEASURE_SAMPLE*);
   friend void CalculateLineDeviation( EMeasure*, MEASURE_SAMPLE*);
   friend void MeasureParabola( EMeasure*, MEASURE_SAMPLE*);
   friend void MeasureCircle( EMeasure*, MEASURE_SAMPLE*);
   friend void Center( EMeasure*, MEASURE_SAMPLE*);
   friend void CalculateRadius( EMeasure*, MEASURE_SAMPLE*);
   friend void BringCircleCloser( EMeasure*, MEASURE_SAMPLE*);
   friend void CalculateS( EMeasure*, MEASURE_SAMPLE*, FLOAT32*, FLOAT32*);
   friend void CalculateT( EMeasure*, MEASURE_SAMPLE*, FLOAT32*, FLOAT32*);
   friend void CalculateRH( EMeasure*, MEASURE_SAMPLE*, FLOAT32*, FLOAT32*, FLOAT32*);
   friend void MeasureProfile( INT32, INT32, INT32, INT16*, EMeasure*, INT16*, FLOAT32*, FLOAT32*);
   friend INT16 MeasurePointXY( EROIBW8*, EMeasure*, INT16*, FLOAT32*, FLOAT32*);
   friend INT16 MsrMeasureOutline( EROIBW8*, EMeasure*);
   friend INT16 SelectPoint( EMeasure*, INT32);
   friend void SelectPointLine( EMeasure*, FLOAT32);
   friend void SelectPointParabola( EMeasure*, FLOAT32);
   friend void SelectPointCircle( EMeasure*, FLOAT32);
   friend E_DLL0 INT16 E_DLL1  MsrFindPointAlongLine( EROIBW8*, EMeasure*);
}; 


////////////////////////////////////////////////////////////////////////////////
// Global functions
//

E_DLL0 INT16 E_DLL1  MsrFindPointAlongLine( EROIBW8* pSrcImage, EMeasure *pMeasure);

E_DLL0 INT16 E_DLL1  MsrFitLine( EROIBW8* pSrcImage, EMeasure* pMeasure);

E_DLL0 INT16 E_DLL1  MsrFitCircle( EROIBW8* pSrcImage, EMeasure* pMeasure);

E_DLL0 void E_DLL1  MsrArcThroughThreePoints
( FLOAT32 X0, FLOAT32 Y0, FLOAT32 X1, FLOAT32 Y1, FLOAT32 X2, FLOAT32 Y2,
 FLOAT32& X, FLOAT32& Y,
 FLOAT32& R, FLOAT32& A0, FLOAT32& A);

////////////////////////////////////////////////////////////////////////////////
// Calibration transform

// Calibration transform setup
E_DLL0 void E_DLL1  MsrEmptyCalibrationPointPairs( );
E_DLL0 void E_DLL1  MsrAddCalibrationPointPair( FLOAT32 f32WorldX, FLOAT32 f32WorldY, FLOAT32 f32ImageX, FLOAT32 f32ImageY);
E_DLL0 void E_DLL1  MsrSetupLinearCalibration( );
E_DLL0 void E_DLL1  MsrSetupPerspectiveCalibration( );

// Transform parameters
E_DLL0 void E_DLL1  MsrGetCalibration
( FLOAT32& f32Axx, FLOAT32& f32Axy, FLOAT32& f32Ax,
 FLOAT32& f32Ayx, FLOAT32& f32Ayy, FLOAT32& f32Ay, 
 FLOAT32& f32Bx, FLOAT32& f32By);

E_DLL0 void E_DLL1  MsrGetInvCalibration
( FLOAT32& f32Axx, FLOAT32& f32Axy, FLOAT32& f32Ax,
 FLOAT32& f32Ayx, FLOAT32& f32Ayy, FLOAT32& f32Ay, 
 FLOAT32& f32Bx, FLOAT32& f32By);

E_DLL0 void E_DLL1  MsrGetCalibrationAngles( FLOAT32& f32AngleX, FLOAT32& f32AngleY, FLOAT32& f32AngleZ);

// Transforms for points
E_DLL0 void E_DLL1  MsrLinearCalibration( FLOAT32 f32WorldX, FLOAT32 f32WorldY, FLOAT32& f32ImageX, FLOAT32& f32ImageY);
E_DLL0 void E_DLL1  MsrInvLinearCalibration( FLOAT32 f32ImageX, FLOAT32 f32ImageY, FLOAT32& f32WorldX, FLOAT32& f32WolrdY);
E_DLL0 void E_DLL1  MsrPerspectiveCalibration( FLOAT32 f32WorldX, FLOAT32 f32WorldY, FLOAT32& f32ImageX, FLOAT32& f32ImageY);
E_DLL0 void E_DLL1  MsrInvPerspectiveCalibration( FLOAT32 f32ImageX, FLOAT32 f32ImageY, FLOAT32& f32WorldX, FLOAT32& f32WolrdY);

// Transforms for images
E_DLL0 void E_DLL1  MsrLinearCalibration( EROIBW8* pSrcImage, EROIBW8* pDstImage);
E_DLL0 void E_DLL1  MsrInvLinearCalibration( EROIBW8* pSrcImage, EROIBW8* pDstImage);
E_DLL0 void E_DLL1  MsrPerspectiveCalibration( EROIBW8* pSrcImage, EROIBW8* pDstImage);
E_DLL0 void E_DLL1  MsrInvPerspectiveCalibration( EROIBW8* pSrcImage, EROIBW8* pDstImage);

// Miscellaneous
E_DLL0 void E_DLL1  MsrEsope( BOOL bCompatibility);

// + OBSOLETE 
#define GetTransitionMinGreyStep GetTransitionMinGrayStep
#define SetTransitionMinGreyStep SetTransitionMinGrayStep
#define GetMeasuredGreyStep GetMeasuredGrayStep
#define SetMeasuredGreyStep SetMeasuredGrayStep
// - OBSOLETE 

#endif //__EMEASURE_H__
