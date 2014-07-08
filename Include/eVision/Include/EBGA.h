//////////////////////////////////////////////////////////////////////////////
// EBGA.h: EasyBGA library header file for eVision 6.7.1.0
//
// EasyBGA inspects BGA components in 2D
//
// Copyright ( c) 1997-2006, Euresys. All rights reserved.
//

#ifndef __EBGA_H__
#define __EBGA_H__

//////////////////////////////////////////////////////////////////////////////
//
// eVision header files
#include "EInspect.h"
#include "EGauge.h"
#include "EObject.h"
#include "EBGA_Enum.h"

//////////////////////////////////////////////////////////////////////////////
//


//////////////////////////////////////////////////////////////////////////////
//
class EBGA;
class EBGAComponent;
class EBGAArray;
class E_DLL1 EBGABall: public ECircleShape
{
  // Wrapping members
public:
  int handle_;
  FinalizeCallback callback_;

  // Constructors, copy and assignment
public:
  E_DLL0 CONSTRUCTOR E_DLL1             EBGABall                ( FLOAT32 f32CenterX = 0, FLOAT32 f32CenterY = 0, FLOAT32 f32Diameter = 1, BOOL bDirect = TRUE, FLOAT32 f32OrgAngle = 0);
  virtual E_DLL0 DESTRUCTOR E_DLL1      ~EBGABall               ( );
private :
                                        EBGABall                ( const EBGABall&);
  EBGABall&                             operator=               ( const EBGABall&);

public :
  E_DLL0 EShape* E_DLL1                 New                     ( );

  // Typing
  E_DLL0 INS_SHAPE_TYPES E_DLL1         GetType                 ( );

  // Component, array and ball indexes
  E_DLL0 EBGAComponent* E_DLL1          GetComponent            ( );
  E_DLL0 UINT32 E_DLL1                  GetComponentIndex       ( );

  E_DLL0 EBGAArray* E_DLL1              GetArray                ( );
  E_DLL0 UINT32 E_DLL1                  GetArrayIndex           ( );
  
  E_DLL0 UINT32 E_DLL1                  GetBallRowIndex         ( );
  E_DLL0 UINT32 E_DLL1                  GetBallColIndex         ( );
  
  // Updates
  E_DLL0 void E_DLL1                    Set                     ( EPoint Center, FLOAT32 f32Diameter, BOOL bDirect = TRUE, FLOAT32 f32OrgAngle = 0);
  E_DLL0 enum INS_MEASURE_MODE E_DLL1   GetMeasureMode          ( ) { return m_eMeasureMode; }
  E_DLL0 void E_DLL1                    SetMeasureMode          ( enum INS_MEASURE_MODE eMeasureMode) { m_eMeasureMode = eMeasureMode; }

  E_DLL0 FLOAT32 E_DLL1                 GetDiameterTolerance    ( ) { return m_f32DiameterTolerance; }
  E_DLL0 void E_DLL1                    SetDiameterTolerance    ( FLOAT32 f32DiameterTolerance) { m_f32DiameterTolerance = f32DiameterTolerance; }
                                  
  E_DLL0 UINT32 E_DLL1                  GetDiagnostics          ( ) { return m_un32Diagnostics; }
                                  
  E_DLL0 BOOL E_DLL1                    GetDiagnostic           ( enum BGA_DIAGNOSTICS eDiagnostic);
  
  // Measurement
  E_DLL0 BOOL E_DLL1                    GetWhiteOnBlack         ( ) { return m_bWhiteOnBlack; }
  E_DLL0 void E_DLL1                    SetWhiteOnBlack         ( BOOL bWhiteOnBlack) { m_bWhiteOnBlack = bWhiteOnBlack; }

  static E_DLL0 void E_DLL1             SetupSrcROI             ( EROIBW8* pSrc, FLOAT32 f32OuterDiameter, FLOAT32 f32InnerDiameter);
  static E_DLL0 void E_DLL1             SetupRadialField        ( INT32 n32Width, INT32 n32Height, BOOL bWhiteOnBlack = TRUE);
  E_DLL0 BOOL E_DLL1                    RadialCenter            ( );
  E_DLL0 enum BGA_MEASURE_BALL E_DLL1   RadialInertiaWithGauge  ( FLOAT32 f32DoughnutnessTolerance, FLOAT32 diameterInPixels, EBGA*, EROI<EBW8>* image );
  E_DLL0 enum BGA_MEASURE_BALL E_DLL1   RadialInertia           ( FLOAT32 f32DoughnutnessTolerance, enum BGA_MEASURE_ASSESSMENT m_eMeasureAssessment, enum BGA_CIRCULARITY_ASSESSMENT m_eCircularityAssessment);
  static E_DLL0 void E_DLL1             DetachSrcROI            ( );
  
  // Measured results
  ECircle                               m_Measured;
  E_DLL0 FLOAT32 E_DLL1                 GetMeasuredDiameter     ( ) { return m_Measured.GetDiameter( ); }
  E_DLL0 FLOAT32 E_DLL1                 GetMeasuredOffsetX      ( ) { return m_f32MeasuredOffsetX; }
  E_DLL0 FLOAT32 E_DLL1                 GetMeasuredOffsetY      ( ) { return m_f32MeasuredOffsetY; }
  E_DLL0 FLOAT32 E_DLL1                 GetMeasuredPitchX       ( ) { return m_f32MeasuredPitchX; }
  E_DLL0 FLOAT32 E_DLL1                 GetMeasuredPitchY       ( ) { return m_f32MeasuredPitchY; }
  E_DLL0 FLOAT32 E_DLL1                 GetMeasuredCircularity  ( ) { return m_f32MeasuredCircularity; }
  E_DLL0 FLOAT32 E_DLL1                 GetMeasuredDoughnutness ( ) { return m_f32MeasuredDoughnutness; }
  E_DLL0 FLOAT32 E_DLL1                 GetMeasuredQualityFactor( ) { return m_f32MeasuredQualityFactor; }
  
  // Per-ball batch statistics
  E_DLL0 UINT32 E_DLL1                  GetNumBatchSamples      ( ) { return m_un32NumBatchSamples; }
  E_DLL0 FLOAT32 E_DLL1                 GetMinimumOffset        ( ) { return m_f32MinimumOffset; }
  E_DLL0 FLOAT32 E_DLL1                 GetMaximumOffset        ( ) { return m_f32MaximumOffset; }
  E_DLL0 FLOAT32 E_DLL1                 GetAverageOffset        ( ) { return m_f32AverageOffset; }
  E_DLL0 FLOAT32 E_DLL1                 GetDeviationOffset      ( );

  E_DLL0 FLOAT32 E_DLL1                 GetMinimumPitch         ( ) { return m_f32MinimumPitch; }
  E_DLL0 FLOAT32 E_DLL1                 GetMaximumPitch         ( ) { return m_f32MaximumPitch; }
  E_DLL0 FLOAT32 E_DLL1                 GetAveragePitch         ( ) { return m_f32AveragePitch; }
  E_DLL0 FLOAT32 E_DLL1                 GetDeviationPitch       ( );

  E_DLL0 FLOAT32 E_DLL1                 GetMinimumDiameter      ( ) { return m_f32MinimumDiameter; }
  E_DLL0 FLOAT32 E_DLL1                 GetMaximumDiameter      ( ) { return m_f32MaximumDiameter; }
  E_DLL0 FLOAT32 E_DLL1                 GetAverageDiameter      ( ) { return m_f32AverageDiameter; }
  E_DLL0 FLOAT32 E_DLL1                 GetDeviationDiameter    ( );

  E_DLL0 FLOAT32 E_DLL1                 GetMinimumCircularity   ( ) { return m_f32MinimumCircularity; }
  E_DLL0 FLOAT32 E_DLL1                 GetMaximumCircularity   ( ) { return m_f32MaximumCircularity; }
  E_DLL0 FLOAT32 E_DLL1                 GetAverageCircularity   ( ) { return m_f32AverageCircularity; }
  E_DLL0 FLOAT32 E_DLL1                 GetDeviationCircularity ( );

  E_DLL0 FLOAT32 E_DLL1                 GetMinimumDoughnutness  ( ) { return m_f32MinimumDoughnutness; }
  E_DLL0 FLOAT32 E_DLL1                 GetMaximumDoughnutness  ( ) { return m_f32MaximumDoughnutness; }
  E_DLL0 FLOAT32 E_DLL1                 GetAverageDoughnutness  ( ) { return m_f32AverageDoughnutness; }
  E_DLL0 FLOAT32 E_DLL1                 GetDeviationDoughnutness( );

  E_DLL0 FLOAT32 E_DLL1                 GetMinimumQualityFactor  ( ) { return m_f32MinimumQualityFactor; }
  E_DLL0 FLOAT32 E_DLL1                 GetMaximumQualityFactor  ( ) { return m_f32MaximumQualityFactor; }
  E_DLL0 FLOAT32 E_DLL1                 GetAverageQualityFactor  ( ) { return m_f32AverageQualityFactor; }
  E_DLL0 FLOAT32 E_DLL1                 GetDeviationQualityFactor( );
  // Drawing
  E_DLL0 void E_DLL1                    Draw                    ( HDC hDC, enum INS_DRAWING_MODES eDrawingMode = INS_DRAW_NOMINAL, BOOL bDaughters = TRUE);
  E_DLL0 void E_DLL1                    Draw                    ( Euresys::DrawAdapter* drawAdapter, enum INS_DRAWING_MODES eDrawingMode = INS_DRAW_NOMINAL, BOOL bDaughters = TRUE);
  
/*
  Protected methods
*/
protected :
  // Diagnostics
  E_DLL0 void E_DLL1                    SetDiagnostic           ( enum BGA_DIAGNOSTICS eDiagnostic, BOOL bValue = TRUE);
  // Serialization
  E_DLL0 UINT32 E_DLL1                  GetSignature            ( );
  virtual E_DLL0 void E_DLL1            Serialize               ( ESerializer* serializer, UINT32 un32FileVersion, BOOL bRecurse = TRUE);
  virtual E_DLL0 void E_DLL1            Serialize               ( FILE*  pFile, BOOL bWrite, UINT32 un32FileVersion, BOOL bDaughters = TRUE);

/*
  Protected member data
*/
protected:
  enum INS_MEASURE_MODE                 m_eMeasureMode; 
  FLOAT32                               m_f32DiameterTolerance; 
  UINT32                                m_un32Diagnostics; 
  BOOL                                  m_bWhiteOnBlack; 
  UINT32                                m_un32NumBatchSamples; 

  FLOAT32                               m_f32MinimumOffset; 
  FLOAT32                               m_f32MaximumOffset; 
  FLOAT32                               m_f32AverageOffset; 
  FLOAT32                               m_f32DeviationOffset; 

  FLOAT32                               m_f32MinimumPitch; 
  FLOAT32                               m_f32MaximumPitch; 
  FLOAT32                               m_f32AveragePitch; 
  FLOAT32                               m_f32DeviationPitch; 

  FLOAT32                               m_f32MinimumDiameter; 
  FLOAT32                               m_f32MaximumDiameter; 
  FLOAT32                               m_f32AverageDiameter; 
  FLOAT32                               m_f32DeviationDiameter; 

  FLOAT32                               m_f32MinimumCircularity; 
  FLOAT32                               m_f32MaximumCircularity; 
  FLOAT32                               m_f32AverageCircularity; 
  FLOAT32                               m_f32DeviationCircularity;
  
  FLOAT32                               m_f32MinimumDoughnutness; 
  FLOAT32                               m_f32MaximumDoughnutness; 
  FLOAT32                               m_f32AverageDoughnutness; 
  FLOAT32                               m_f32DeviationDoughnutness; 

  FLOAT32                               m_f32MinimumQualityFactor; 
  FLOAT32                               m_f32MaximumQualityFactor; 
  FLOAT32                               m_f32AverageQualityFactor; 
  FLOAT32                               m_f32DeviationQualityFactor; 

  // Measured results
  FLOAT32                               m_f32MeasuredOffsetX;
  FLOAT32                               m_f32MeasuredOffsetY;
  FLOAT32                               m_f32MeasuredPitchX;
  FLOAT32                               m_f32MeasuredPitchY;
  FLOAT32                               m_f32MeasuredCircularity;
  FLOAT32                               m_f32MeasuredDoughnutness;
  FLOAT32                               m_f32MeasuredQualityFactor;

  // Apparent diameter correction       
  FLOAT32                               m_f32DiameterCorrection;

  // Corresponding Landmark
  ELandmark                             *m_pLandmark;

/*
  Protected class data
*/
  // Radial field                       
  static EImageBW32                     ms_RadialField;
  static EROIBW32                       ms_FieldROI;

  // Measurement ROI                    
  static EImageBW8                      ms_Gradient;
  static EROIBW8                        ms_SrcROI;

  // Histogram for thresholding         
  static EBWHistogramVector             ms_Histo;

  // Lookup table for soft thresholding
  static EBW8Vector                     ms_LUT;

  friend class EBGA;
};

//////////////////////////////////////////////////////////////////////////////
//
class EBGA;

class EBGAArray: public ERectangleShape
{
  // Wrapping members
public:
  int handle_;
  FinalizeCallback callback_;

  // Constructors, copy and assignment
public:
  E_DLL0 CONSTRUCTOR E_DLL1             EBGAArray               ( );
private :
                                        EBGAArray               ( const EBGAArray&);
  EBGAArray&                            operator=               ( const EBGAArray&);

public :
  E_DLL0 EShape* E_DLL1                 New                     ( );
  
  // Typing
  E_DLL0 INS_SHAPE_TYPES E_DLL1         GetType                 ( );
  
  // Arrangement
  E_DLL0 BOOL E_DLL1                    GetStaggered            ( ) { return m_bStaggered; }
  E_DLL0 void E_DLL1                    SetStaggered            ( BOOL bStaggered) { m_bStaggered = bStaggered; }
                                  
  // Array labels
  E_DLL0 BOOL E_DLL1                    GetInverseRowNumbering  ( ) { return m_bInverseRowNumbering; }
  E_DLL0 void E_DLL1                    SetInverseRowNumbering  ( BOOL bInverseRowNumbering) { m_bInverseRowNumbering = bInverseRowNumbering; }
  E_DLL0 BOOL E_DLL1                    GetInverseColNumbering  ( ) { return m_bInverseColNumbering; }
  E_DLL0 void E_DLL1                    SetInverseColNumbering  ( BOOL bInverseColNumbering) { m_bInverseColNumbering = bInverseColNumbering; }
                                  
protected:                        
  virtual E_DLL0 void E_DLL1            Serialize               ( ESerializer* serializer, UINT32 un32FileVersion, BOOL bRecurse = TRUE);
  virtual E_DLL0 void E_DLL1            Serialize               ( FILE*  pFile, BOOL bWrite, UINT32 un32FileVersion, BOOL bDaughters = TRUE);
  
private:
  // Parameters
  BOOL                                  m_bStaggered;
  BOOL                                  m_bInverseRowNumbering;
  BOOL                                  m_bInverseColNumbering;
  
  // Serialization
  E_DLL0 UINT32 E_DLL1                  GetSignature            ( );

  friend class EBGA;
};

//////////////////////////////////////////////////////////////////////////////
//
class EBGAComponent: public ERectangleShape
{
  // Wrapping members
public:
  int handle_;
  FinalizeCallback callback_;

  // Constructors, copy and assignment
public :
  E_DLL0 CONSTRUCTOR E_DLL1             EBGAComponent           ( );
private :
                                        EBGAComponent           ( const EBGAComponent&);
  EBGAComponent&                        operator=               ( const EBGAComponent&);

public:
  // Constructors
  E_DLL0 EShape* E_DLL1                 New                     ( );
  // Queries
  E_DLL0 UINT32 E_DLL1                  GetNumBalls             ( );
  
  // Updates
  E_DLL0 void E_DLL1                    SetCenter               ( EPoint Center)
  {
    // Assign center
    m_NominalCenter = Center;
    ERectangleShape::SetCenter( Center);
  }

  E_DLL0 void E_DLL1                    SetCenter               ( FLOAT32 centerX, FLOAT32 centreY) {this->SetCenter(EPoint(centerX, centreY));};
  
  // Typing
  E_DLL0 INS_SHAPE_TYPES E_DLL1         GetType                 ( );  
  
  // Diagnostics
  E_DLL0 UINT32 E_DLL1                  GetNumMissingBalls      ( );
  E_DLL0 UINT32 E_DLL1                  GetNumBallsFound        ( ) { return m_un32NumBallsFound; }
                                  
  E_DLL0 UINT32 E_DLL1                  GetDiagnostics          ( ) { return m_un32Diagnostics; }

  E_DLL0 BOOL E_DLL1                    GetDiagnostic           ( enum BGA_DIAGNOSTICS eDiagnostic);
  
  // Per component statistics
  E_DLL0 FLOAT32 E_DLL1                 GetMinimumOffset        ( ) { return m_f32MinimumOffset; }
  E_DLL0 FLOAT32 E_DLL1                 GetMaximumOffset        ( ) { return m_f32MaximumOffset; }
  E_DLL0 FLOAT32 E_DLL1                 GetAverageOffset        ( ) { return m_f32AverageOffset; }
  E_DLL0 FLOAT32 E_DLL1                 GetDeviationOffset      ( );

  E_DLL0 FLOAT32 E_DLL1                 GetMinimumPitch         ( ) { return m_f32MinimumPitch; }
  E_DLL0 FLOAT32 E_DLL1                 GetMaximumPitch         ( ) { return m_f32MaximumPitch; }
  E_DLL0 FLOAT32 E_DLL1                 GetAveragePitch         ( ) { return m_f32AveragePitch; }
  E_DLL0 FLOAT32 E_DLL1                 GetDeviationPitch       ( );

  E_DLL0 FLOAT32 E_DLL1                 GetMinimumDiameter      ( ) { return m_f32MinimumDiameter; }
  E_DLL0 FLOAT32 E_DLL1                 GetMaximumDiameter      ( ) { return m_f32MaximumDiameter; }
  E_DLL0 FLOAT32 E_DLL1                 GetAverageDiameter      ( ) { return m_f32AverageDiameter; }
  E_DLL0 FLOAT32 E_DLL1                 GetDeviationDiameter    ( );

  E_DLL0 FLOAT32 E_DLL1                 GetMinimumCircularity   ( ) { return m_f32MinimumCircularity; }
  E_DLL0 FLOAT32 E_DLL1                 GetMaximumCircularity   ( ) { return m_f32MaximumCircularity; }
  E_DLL0 FLOAT32 E_DLL1                 GetAverageCircularity   ( ) { return m_f32AverageCircularity; }
  E_DLL0 FLOAT32 E_DLL1                 GetDeviationCircularity ( );

  E_DLL0 FLOAT32 E_DLL1                 GetMinimumDoughnutness  ( ) { return m_f32MinimumDoughnutness; }
  E_DLL0 FLOAT32 E_DLL1                 GetMaximumDoughnutness  ( ) { return m_f32MaximumDoughnutness; }
  E_DLL0 FLOAT32 E_DLL1                 GetAverageDoughnutness  ( ) { return m_f32AverageDoughnutness; }
  E_DLL0 FLOAT32 E_DLL1                 GetDeviationDoughnutness( );

  E_DLL0 FLOAT32 E_DLL1                 GetMinimumQualityFactor  ( ) { return m_f32MinimumQualityFactor; }
  E_DLL0 FLOAT32 E_DLL1                 GetMaximumQualityFactor  ( ) { return m_f32MaximumQualityFactor; }
  E_DLL0 FLOAT32 E_DLL1                 GetAverageQualityFactor  ( ) { return m_f32AverageQualityFactor; }
  E_DLL0 FLOAT32 E_DLL1                 GetDeviationQualityFactor( );

protected:
  // Serialization
  E_DLL0 UINT32 E_DLL1                  GetSignature            ( );
  virtual E_DLL0 void E_DLL1            Serialize               ( ESerializer* serializer, UINT32 un32FileVersion, BOOL bRecurse = TRUE);
  virtual E_DLL0 void E_DLL1            Serialize               ( FILE*  pFile, BOOL bWrite, UINT32 un32FileVersion, BOOL bDaughters = TRUE);
  
  UINT32                                m_un32NumBallsFound; 

  UINT32                                m_un32Diagnostics; 
  FLOAT32                               m_f32MinimumOffset; 
  FLOAT32                               m_f32MaximumOffset; 
  FLOAT32                               m_f32AverageOffset; 
  FLOAT32                               m_f32DeviationOffset; 

  FLOAT32                               m_f32MinimumPitch; 
  FLOAT32                               m_f32MaximumPitch; 
  FLOAT32                               m_f32AveragePitch; 
  FLOAT32                               m_f32DeviationPitch; 

  FLOAT32                               m_f32MinimumDiameter; 
  FLOAT32                               m_f32MaximumDiameter; 
  FLOAT32                               m_f32AverageDiameter; 
  FLOAT32                               m_f32DeviationDiameter; 

  FLOAT32                               m_f32MinimumCircularity; 
  FLOAT32                               m_f32MaximumCircularity; 
  FLOAT32                               m_f32AverageCircularity; 
  FLOAT32                               m_f32DeviationCircularity; 

  FLOAT32                               m_f32MinimumDoughnutness; 
  FLOAT32                               m_f32MaximumDoughnutness; 
  FLOAT32                               m_f32AverageDoughnutness; 
  FLOAT32                               m_f32DeviationDoughnutness;

  FLOAT32                               m_f32MinimumQualityFactor; 
  FLOAT32                               m_f32MaximumQualityFactor; 
  FLOAT32                               m_f32AverageQualityFactor; 
  FLOAT32                               m_f32DeviationQualityFactor;
                                        
private:                                
  EPoint                                m_NominalCenter;
  
  friend class EBGA;
};

//////////////////////////////////////////////////////////////////////////////
//
class ECircleGauge;

class EBGA : public ERectangleShape
{
  // Wrapping members
public:
  int handle_;
  FinalizeCallback callback_;

  // Constructors, copy and assignment
public:
  E_DLL0 CONSTRUCTOR E_DLL1             EBGA                    ( );
  virtual E_DLL0 DESTRUCTOR E_DLL1      ~EBGA                   ( );
private :
                                        EBGA                    ( const EBGA&);
  EBGA&                                 operator=               ( const EBGA&);

  // Type information
public :
  E_DLL0 INS_SHAPE_TYPES E_DLL1         GetType                 ( );
  
  // Measurement unit
  enum E_MEASUREMENT_UNITS              GetUnit                 ( );
  void                                  SetUnit                 ( enum E_MEASUREMENT_UNITS eUnit);

  // Whether close blobs should be merged (slower)
  E_DLL0 BOOL E_DLL1                    GetPackCloseBlobs       ( ) const;
  E_DLL0 void E_DLL1                    SetPackCloseBlobs       ( BOOL bPackCloseBlobs );

  // Model edition
  E_DLL0 UINT32 E_DLL1                  GetComponentNumBalls    ( );
  E_DLL0 UINT32 E_DLL1                  GetNumBalls             ( );

  // Package center
  E_DLL0 FLOAT32 E_DLL1                 GetPackageCenterX       ( );
  E_DLL0 FLOAT32 E_DLL1                 GetPackageCenterY       ( );
                                                          
  // Package size                                         
  E_DLL0 FLOAT32 E_DLL1                 GetPackageWidth         ( );
  E_DLL0 FLOAT32 E_DLL1                 GetPackageHeight        ( );
  E_DLL0 void E_DLL1                    SetPackageSize          ( FLOAT32 f32PackageWidth, FLOAT32 f32PackageHeight = 0);
  
  // Package name
  const E_DLL0 char* E_DLL1             GetPackageName          ( );
  E_DLL0 void E_DLL1                    SetPackageName          ( const char* pszName);
  
  // Balls diameter
  E_DLL0 FLOAT32 E_DLL1                 GetBallDiameter         ( ) { return m_f32BallDiameter; }
  E_DLL0 void E_DLL1                    SetBallDiameter         ( FLOAT32 f32BallDiameter);
                                  
  E_DLL0 FLOAT32 E_DLL1                 GetBallDiameterTolerance( ) { return m_f32BallDiameterTolerance; }
  E_DLL0 void E_DLL1                    SetBallDiameterTolerance( FLOAT32 f32BallDiameterTolerance); 
                                  
  // Balls shape                  
  E_DLL0 FLOAT32 E_DLL1                 GetBallCircularityTolerance( ) { return m_f32BallCircularityTolerance; }
  E_DLL0 void E_DLL1                    SetBallCircularityTolerance( FLOAT32 f32BallCircularityTolerance) { m_f32BallCircularityTolerance = f32BallCircularityTolerance; }
                                  
  E_DLL0 FLOAT32 E_DLL1                 GetBallDoughnutnessTolerance( ) { return m_f32BallDoughnutnessTolerance; }
  E_DLL0 void E_DLL1                    SetBallDoughnutnessTolerance( FLOAT32 f32BallDoughnutnessTolerance = 0.1f) { m_f32BallDoughnutnessTolerance = f32BallDoughnutnessTolerance; }
                                  
  E_DLL0 FLOAT32 E_DLL1                 GetBallQualityFactorTolerance( ) { return m_f32BallQualityFactorTolerance; }
  E_DLL0 void E_DLL1                    SetBallQualityFactorTolerance( FLOAT32 f32BallQualityFactorTolerance = 0.1f) { m_f32BallQualityFactorTolerance = f32BallQualityFactorTolerance; }
                                  
  // Balls position               
  E_DLL0 FLOAT32 E_DLL1                 GetBallOffsetXTolerance ( );
  E_DLL0 FLOAT32 E_DLL1                 GetBallOffsetYTolerance ( );
  E_DLL0 void E_DLL1                    SetBallOffsetTolerance  ( FLOAT32 f32XTolerance, FLOAT32 f32YTolerance = 0);
  E_DLL0 void E_DLL1                    SetBallOffsetXTolerance ( FLOAT32 f32XTolerance );
  E_DLL0 void E_DLL1                    SetBallOffsetYTolerance ( FLOAT32 f32YTolerance );
                                  
  // Balls pitch                  
  E_DLL0 FLOAT32 E_DLL1                 GetBallPitchXTolerance  ( );
  E_DLL0 FLOAT32 E_DLL1                 GetBallPitchYTolerance  ( );
  E_DLL0 void E_DLL1                    SetBallPitchTolerance   ( FLOAT32 f32XTolerance, FLOAT32 f32YTolerance = 0);
  
  // Balls
  E_DLL0 EBGABall* E_DLL1               GetBall                 ( UINT32 un32ColIndex, UINT32 un32RowIndex);
  
  // Arrays
  E_DLL0 UINT32 E_DLL1                  GetNumArrays            ( );
  
  E_DLL0 UINT32 E_DLL1                  GetCurrentArray         ( );
  E_DLL0 void E_DLL1                    SetCurrentArray         ( UINT32 un32CurrentArray);

  E_DLL0 EBGAArray* E_DLL1              GetArray                ( );
  E_DLL0 void E_DLL1                    AddArray                ( FLOAT32 f32ArrayWidth = 11.43f,
                                                                  FLOAT32 f32ArrayHeight = 0, 
                                                                  UINT32 un32NumCols = 10,
                                                                  UINT32 un32NumRows = 0,
                                                                  FLOAT32 f32CenterX = 0,
                                                                  FLOAT32 f32CenterY = 0,
                                                                  BOOL bStaggered = FALSE,
                                                                  BOOL bInverseColNumbering = FALSE,
                                                                  BOOL bInverseRowNumbering = FALSE);
  E_DLL0 void E_DLL1                    RemoveArray             ( );
  E_DLL0 UINT32 E_DLL1                  GetArrayNumBalls        ( );
  
  // Array physical size
  E_DLL0 FLOAT32 E_DLL1                 GetArraySizeX           ( );
  E_DLL0 FLOAT32 E_DLL1                 GetArraySizeY           ( );
  E_DLL0 void E_DLL1                    SetArrayPhysicalSize    ( FLOAT32 f32Width = 11.43f, FLOAT32 f32Height = 0);
  
  E_DLL0 FLOAT32 E_DLL1                 GetArrayPitchX          ( );
  E_DLL0 FLOAT32 E_DLL1                 GetArrayPitchY          ( );
  E_DLL0 void E_DLL1                    SetArrayPitches         ( FLOAT32 f32PitchX = 1.27f, FLOAT32 f32PitchY = 0);
  
  // Array center
  E_DLL0 FLOAT32 E_DLL1                 GetArrayCenterX         ( );
  E_DLL0 FLOAT32 E_DLL1                 GetArrayCenterY         ( );
  E_DLL0 void E_DLL1                    SetArrayCenter          ( FLOAT32 f32CenterX = 0, FLOAT32 f32CenterY = 0);
  
  // Array logical size
  E_DLL0 UINT32 E_DLL1                  GetArrayNumCols         ( );
  E_DLL0 UINT32 E_DLL1                  GetArrayNumRows         ( );
  E_DLL0 void E_DLL1                    SetArrayLogicalSize     ( UINT32 un32NumCols = 10, UINT32 un32NumRows = 0, BOOL bStaggered = FALSE);
  
  // Array edition
  E_DLL0 enum BGA_SYMMETRY E_DLL1       GetSymmetry             ( ) { return m_eSymmetry; }
  E_DLL0 void E_DLL1                    SetSymmetry             ( enum BGA_SYMMETRY eSymmetry) { m_eSymmetry = eSymmetry; }

  E_DLL0 void E_DLL1                    ToggleBall              ( UINT32 un32Col, UINT32 un32Row);
  E_DLL0 void E_DLL1                    ToggleBalls             ( INT32 n32OrgX, INT32 n32OrgY, INT32 n32EndX, INT32 n32EndY);
  
  // Array labels
  E_DLL0 void E_DLL1                    DrawArrayLabels         ( HDC hDC);
  E_DLL0 void E_DLL1                    DrawArrayLabels         ( Euresys::DrawAdapter* drawAdapter);
  
  // Components
  E_DLL0 UINT32 E_DLL1                  GetNumComponents        ( );
  E_DLL0 BOOL E_DLL1                    GetRegularPlacement     ( );
  
  // Regular placement
  E_DLL0 void E_DLL1                    SetNumComponents        ( UINT32 un32NumCols, UINT32 un32NumRows);
  E_DLL0 void E_DLL1                    SetCurrentComponent     ( UINT32 un32ColIndex, UINT32 un32RowIndex);
  E_DLL0 EBGAComponent* E_DLL1          GetComponent            ( );
  
  E_DLL0 FLOAT32 E_DLL1                 GetComponentPitchX      ( );
  E_DLL0 FLOAT32 E_DLL1                 GetComponentPitchY      ( );
  E_DLL0 void E_DLL1                    SetComponentPitches     ( FLOAT32 f32PitchX, FLOAT32 f32PitchY = 0);
  
  // Arbitrary placement
  E_DLL0 void E_DLL1                    SetNumComponents        ( UINT32 un32Num);
  E_DLL0 UINT32 E_DLL1                  GetCurrentComponent     ( ) { return m_un32CurrentComponent; }
  E_DLL0 void E_DLL1                    SetCurrentComponent     ( UINT32 un32CurrentComponent) { m_un32CurrentComponent = un32CurrentComponent; }
                                  
  E_DLL0 void E_DLL1                    SetComponentCenter      ( FLOAT32 f32CenterX, FLOAT32 f32CenterY);
  
  // Blob analysis
  E_DLL0 BOOL E_DLL1                    GetWhiteOnBlack         ( ) { return m_bWhiteOnBlack; }
  E_DLL0 void E_DLL1                    SetWhiteOnBlack         ( BOOL bWhiteOnBlack) { m_bWhiteOnBlack = bWhiteOnBlack; }

  E_DLL0 void E_DLL1                    SetBlobThreshold        ( UINT32 un32Threshold = IMG_MIN_RESIDUE_THRESHOLD) { m_un32BlobThreshold = un32Threshold; }
  E_DLL0 UINT32 E_DLL1                  GetBlobThreshold        ( ) { return m_un32BlobThreshold; }
  E_DLL0 void E_DLL1                    SetMinBlobArea          ( UINT32 un32MinArea = UINT32_UNDEFINED) { m_un32MinBlobArea = un32MinArea; }
  E_DLL0 UINT32 E_DLL1                  GetMinBlobArea          ( ) { return m_un32MinBlobArea; }
  E_DLL0 void E_DLL1                    SetMaxBlobArea          ( UINT32 un32MaxArea = UINT32_UNDEFINED) { m_un32MaxBlobArea = un32MaxArea; }
  E_DLL0 UINT32 E_DLL1                  GetMaxBlobArea          ( ) { return m_un32MaxBlobArea; }

  // Inspection modes
  E_DLL0 BOOL E_DLL1                    GetSingulatedComponents ( ) { return m_bSingulatedComponents; }
  E_DLL0 void E_DLL1                    SetSingulatedComponents ( BOOL bSingulatedComponents);

  E_DLL0 UINT32 E_DLL1                  GetMaxMissingBalls      ( ) { return m_un32MaxMissingBalls; }
  E_DLL0 void E_DLL1                    SetMaxMissingBalls      ( UINT32 un32MaxMissingBalls) { m_un32MaxMissingBalls = un32MaxMissingBalls; }
                                  
  E_DLL0 BOOL E_DLL1                    GetAutoCalibrateWorld   ( ) { return m_bAutoCalibrateWorld; }
  E_DLL0 void E_DLL1                    SetAutoCalibrateWorld   ( BOOL bAutoCalibrateWorld) { m_bAutoCalibrateWorld = bAutoCalibrateWorld; }
                                                          
  E_DLL0 BOOL E_DLL1                    GetAutoCalibrateBalls   ( ) { return m_bAutoCalibrateBalls; }
  E_DLL0 void E_DLL1                    SetAutoCalibrateBalls   ( BOOL bAutoCalibrateBalls) { m_bAutoCalibrateBalls = bAutoCalibrateBalls; }
                                  
  E_DLL0 void E_DLL1                    ResetBallsCalibration   ( );

  // Diagnostics and statistics
  E_DLL0 UINT32 E_DLL1                  GetEnabledQualityDiagnostics( ) { return m_un32EnabledQualityDiagnostics; }
  E_DLL0 void E_DLL1                    SetEnabledQualityDiagnostics( UINT32 un32EnabledQualityDiagnostics) { m_un32EnabledQualityDiagnostics = un32EnabledQualityDiagnostics; }
                                  
  E_DLL0 UINT32 E_DLL1                  GetEnabledQualityStatistics( ) { return m_un32EnabledQualityStatistics; }
  E_DLL0 void E_DLL1                    SetEnabledQualityStatistics( UINT32 un32EnabledQualityStatistics) { m_un32EnabledQualityStatistics = un32EnabledQualityStatistics; }
                                  
  E_DLL0 UINT32 E_DLL1                  GetDiagnostics          ( ) { return m_un32Diagnostics; }
                                  
  E_DLL0 BOOL E_DLL1                    GetDiagnostic           ( enum BGA_DIAGNOSTICS eDiagnostic);
  
  // Per-batch statistics
  E_DLL0 void E_DLL1                    ClearBatchStatistics    ( BOOL bEnable = TRUE);
  
  // Single image inspection
  E_DLL0 void E_DLL1                    Inspect                 ( EROIBW8* pSrcImage, EROIBW8* pAuxImage = NULL);

  // Multiple image inspection
  E_DLL0 void E_DLL1                    BeginInspect            ( );
  E_DLL0 void E_DLL1                    InspectImage            ( EROIBW8* pSrcImage, EROIBW8* pAuxImage = NULL);
  E_DLL0 void E_DLL1                    EndInspect              ( );

  // Diagnostics
  E_DLL0 UINT32 E_DLL1                  GetNumBallsFound        ( );
  E_DLL0 UINT32 E_DLL1                  GetNumMissingBalls      ( );
  E_DLL0 UINT32 E_DLL1                  GetNumClutter           ( ) { return m_un32NumClutter; }
                                  
  E_DLL0 UINT32 E_DLL1                  GetNumExtraBalls        ( ) { return m_un32NumExtraBalls; }

  // Drawing
  E_DLL0 void E_DLL1                    DrawPackages            ( HDC hDC);
  E_DLL0 void E_DLL1                    DrawPackages            ( Euresys::DrawAdapter* drawAdapter);

  E_DLL0 void E_DLL1                    DrawClutter             ( HDC hDC);
  E_DLL0 void E_DLL1                    DrawClutter             ( Euresys::DrawAdapter* drawAdapter);

  E_DLL0 void E_DLL1                    DrawExtraBalls          ( HDC hDC);
  E_DLL0 void E_DLL1                    DrawExtraBalls          ( Euresys::DrawAdapter* drawAdapter);

  // Advanced parameters
  E_DLL0 FLOAT32 E_DLL1                 GetOuterRoiDiameter       ( ) { return m_f32OuterRoiDiameter; }
  E_DLL0 void E_DLL1                    SetOuterRoiDiameter       ( FLOAT32 f32OuterRoiDiameter) { m_f32OuterRoiDiameter = f32OuterRoiDiameter; }
  E_DLL0 FLOAT32 E_DLL1                 GetInnerRoiDiameter       ( ) { return m_f32InnerRoiDiameter; }
  E_DLL0 void E_DLL1                    SetInnerRoiDiameter       ( FLOAT32 f32InnerRoiDiameter) { m_f32InnerRoiDiameter = f32InnerRoiDiameter; }
  
  E_DLL0 void E_DLL1                    SetMeasureAssessment      ( enum BGA_MEASURE_ASSESSMENT eMeasureAssessment) { m_eMeasureAssessment = eMeasureAssessment; }
  E_DLL0 enum BGA_MEASURE_ASSESSMENT E_DLL1 GetMeasureAssessment  ( ) const { return m_eMeasureAssessment; }

  E_DLL0 void E_DLL1                    SetCircularityAssessment  ( enum BGA_CIRCULARITY_ASSESSMENT eCircularityAssessment) { m_eCircularityAssessment = eCircularityAssessment; }
  E_DLL0 enum BGA_CIRCULARITY_ASSESSMENT E_DLL1 GetCircularityAssessment( ) const { return m_eCircularityAssessment; }
    
  // ------------------------------------
  // OBSOLETE after 6.4.0.1
  // Use Get/SetMeasureAssessment() and Get/SetCircularityAssessment() instead
  //
  E_DLL0 BOOL E_DLL1                    GetFineBallMeasure        ( );
  E_DLL0 void E_DLL1                    SetFineBallMeasure        ( BOOL bFineBallMeasure);
  E_DLL0 BOOL E_DLL1                    GetFineCircularity        ( );
  E_DLL0 void E_DLL1                    SetFineCircularity        ( BOOL bFineCircularity);
  // ------------------------------------

  // Per field-of-view statistics
  E_DLL0 FLOAT32 E_DLL1                 GetMinimumOffset        ( );
  E_DLL0 FLOAT32 E_DLL1                 GetMaximumOffset        ( );
  E_DLL0 FLOAT32 E_DLL1                 GetAverageOffset        ( );
  E_DLL0 FLOAT32 E_DLL1                 GetDeviationOffset      ( );
                                  
  E_DLL0 FLOAT32 E_DLL1                 GetMinimumPitch         ( );
  E_DLL0 FLOAT32 E_DLL1                 GetMaximumPitch         ( );
  E_DLL0 FLOAT32 E_DLL1                 GetAveragePitch         ( );
  E_DLL0 FLOAT32 E_DLL1                 GetDeviationPitch       ( );
                                  
  E_DLL0 FLOAT32 E_DLL1                 GetMinimumDiameter      ( );
  E_DLL0 FLOAT32 E_DLL1                 GetMaximumDiameter      ( );
  E_DLL0 FLOAT32 E_DLL1                 GetAverageDiameter      ( );
  E_DLL0 FLOAT32 E_DLL1                 GetDeviationDiameter    ( );
                                  
  E_DLL0 FLOAT32 E_DLL1                 GetMinimumCircularity   ( );
  E_DLL0 FLOAT32 E_DLL1                 GetMaximumCircularity   ( );
  E_DLL0 FLOAT32 E_DLL1                 GetAverageCircularity   ( );
  E_DLL0 FLOAT32 E_DLL1                 GetDeviationCircularity ( );
                                  
  E_DLL0 FLOAT32 E_DLL1                 GetMinimumDoughnutness  ( );
  E_DLL0 FLOAT32 E_DLL1                 GetMaximumDoughnutness  ( );
  E_DLL0 FLOAT32 E_DLL1                 GetAverageDoughnutness  ( );
  E_DLL0 FLOAT32 E_DLL1                 GetDeviationDoughnutness( );

  E_DLL0 FLOAT32 E_DLL1                 GetMinimumQualityFactor   ( );
  E_DLL0 FLOAT32 E_DLL1                 GetMaximumQualityFactor   ( );
  E_DLL0 FLOAT32 E_DLL1                 GetAverageQualityFactor   ( );
  E_DLL0 FLOAT32 E_DLL1                 GetDeviationQualityFactor ( );

  E_DLL0 EWorldShape* E_DLL1            GetCircleGaugeWorldShape( );

  E_DLL0 ECircleGauge* E_DLL1           GetCircleGauge            ( );
  E_DLL0 FLOAT32 E_DLL1                 GetCircleGauge_Tolerance                ( );
  E_DLL0 void E_DLL1                    SetCircleGauge_Tolerance                ( FLOAT32 );
  E_DLL0 FLOAT32 E_DLL1                 GetCircleGauge_Diameter                 ( );
  E_DLL0 void E_DLL1                    SetCircleGauge_Diameter                 ( FLOAT32 );
  E_DLL0 GGE_TRANSITION_CHOICE E_DLL1   GetCircleGauge_TransitionChoice         ( );
  E_DLL0 void E_DLL1                    SetCircleGauge_TransitionChoice         ( GGE_TRANSITION_CHOICE );
  E_DLL0 UINT32 E_DLL1                  GetCircleGauge_Threshold                ( );
  E_DLL0 void E_DLL1                    SetCircleGauge_Threshold                ( UINT32 );
  E_DLL0 UINT32 E_DLL1                  GetCircleGauge_MinAmplitude             ( );
  E_DLL0 void E_DLL1                    SetCircleGauge_MinAmplitude             ( UINT32 );
  E_DLL0 UINT32 E_DLL1                  GetCircleGauge_Thickness                ( );
  E_DLL0 void E_DLL1                    SetCircleGauge_Thickness                ( UINT32 );
  E_DLL0 UINT32 E_DLL1                  GetCircleGauge_Smoothing                ( );
  E_DLL0 void E_DLL1                    SetCircleGauge_Smoothing                ( UINT32 );
  E_DLL0 FLOAT32 E_DLL1                 GetCircleGauge_SamplingStep             ( );
  E_DLL0 void E_DLL1                    SetCircleGauge_SamplingStep             ( FLOAT32 );
  E_DLL0 UINT32 E_DLL1                  GetCircleGauge_NumFilteringPasses       ( );
  E_DLL0 void E_DLL1                    SetCircleGauge_NumFilteringPasses       ( UINT32 );
  E_DLL0 FLOAT32 E_DLL1                 GetCircleGauge_FilteringThreshold       ( );
  E_DLL0 void E_DLL1                    SetCircleGauge_FilteringThreshold       ( FLOAT32 );
  E_DLL0 FLOAT32 E_DLL1                 GetCircleGauge_InnerFilteringThreshold  ( );
  E_DLL0 void E_DLL1                    SetCircleGauge_InnerFilteringThreshold  ( FLOAT32 );
  E_DLL0 enum GGE_FITTING_MODE E_DLL1   GetCircleGauge_FittingMode              ( );
  E_DLL0 void E_DLL1                    SetCircleGauge_FittingMode              ( enum GGE_FITTING_MODE );

private:
  FLOAT32                               m_CircleGauge_Tolerance;
  FLOAT32                               m_CircleGauge_Diameter;
  GGE_TRANSITION_CHOICE                 m_CircleGauge_TransitionChoice;
  UINT32                                m_CircleGauge_Threshold;
  UINT32                                m_CircleGauge_MinAmplitude;
  UINT32                                m_CircleGauge_Thickness;
  UINT32                                m_CircleGauge_Smoothing;
  FLOAT32                               m_CircleGauge_SamplingStep;
  UINT32                                m_CircleGauge_NumFilteringPasses;
  FLOAT32                               m_CircleGauge_FilteringThreshold;
  FLOAT32                               m_CircleGauge_InnerFilteringThreshold;
  enum GGE_FITTING_MODE                 m_CircleGauge_FittingMode;

/*
  private methods
*/
private :
  // Helpers                            
  EPoint                                BallsGravityCenter      ( );
  EPoint                                BallsMoments            ( FLOAT32& f32Mxx, FLOAT32& f32Mxy, FLOAT32& f32Myy);
  void                                  ToggleBall              ( EBGAArray* pArray, UINT32 un32ColIndex, UINT32 un32RowIndex);
  // Processing                         
  void                                  MatchBalls              ( );
  // Diagnosis                          
  void                                  CheckBallOffsets        ( BOOL bDiagnostics, BOOL bComponentStatistics, BOOL bBatchStatistics);
  void                                  CheckBallPitches        ( BOOL bDiagnostics, BOOL bComponentStatistics, BOOL bBatchStatistics);
  void                                  CheckBallDiameters      ( BOOL bDiagnostics, BOOL bComponentStatistics, BOOL bBatchStatistics);
  void                                  CheckBallCircularities  ( BOOL bDiagnostics, BOOL bComponentStatistics, BOOL bBatchStatistics);
  void                                  CheckBallDoughnutnesses ( BOOL bDiagnostics, BOOL bComponentStatistics, BOOL bBatchStatistics);
  void                                  CheckBallQualityFactor  ( BOOL bDiagnostics, BOOL bComponentStatistics, BOOL bBatchStatistics);

/*
  protected methods
*/
protected :
  // Serialization
  virtual E_DLL0 void E_DLL1            Serialize               ( ESerializer* serializer, UINT32 un32FileVersion, BOOL bRecurse = TRUE);
  virtual E_DLL0 void E_DLL1            Serialize               ( FILE*  pFile, BOOL bWrite, UINT32 un32FileVersion, BOOL bRecurse = TRUE);  

/*
  public variables
*/
public:
  Euresys::eVision::Utils::Vector<EBGABall*>  BadBalls;

/*
  protected member data
*/
protected :
  enum E_MEASUREMENT_UNITS              m_eUnit;
  FLOAT32                               m_f32BallDiameter; 
  FLOAT32                               m_f32BallDiameterTolerance; 
  FLOAT32                               m_f32BallCircularityTolerance; 
  UINT32                                m_un32CurrentArray; 
  enum BGA_SYMMETRY                     m_eSymmetry; 
  UINT32                                m_un32CurrentComponent; 
  BOOL                                  m_bWhiteOnBlack; 
  BOOL                                  m_bSingulatedComponents; 
  UINT32                                m_un32MaxMissingBalls; 
  BOOL                                  m_bAutoCalibrateWorld; 
  BOOL                                  m_bAutoCalibrateBalls; 
  UINT32                                m_un32EnabledQualityDiagnostics; 
  UINT32                                m_un32EnabledQualityStatistics; 
  UINT32                                m_un32Diagnostics; 
  UINT32                                m_un32NumClutter; 
  UINT32                                m_un32NumExtraBalls; 

/*
  public member data
*/
public :
  // Embedded coded image for blob analysis
  ECodedImage                           m_Blobs;
  ECodedImage*                          GetBlobs( ) { return &m_Blobs; }

/*
  private member data
*/
private :
  // whether we should perform a first check pass on the blobs
  // to merge closely grouped ones, in case segmentation 
  // erroneously treated two blobs belonging to the same
  // ball as TWO balls
  BOOL                                  m_bPackCloseBlobs;
  // Raw ball positions
  EWorld                                m_BallCenters;
  FLOAT32                               m_f32BallOffsetXTolerance;
  FLOAT32                               m_f32BallOffsetYTolerance;
  FLOAT32                               m_f32BallPitchXTolerance;
  FLOAT32                               m_f32BallPitchYTolerance;
  FLOAT32                               m_f32BallDoughnutnessTolerance;
  FLOAT32                               m_f32BallQualityFactorTolerance;
  UINT32                                m_un32BlobThreshold;
  UINT32                                m_un32MinBlobArea;
  UINT32                                m_un32MaxBlobArea;
  INT32                                 m_n32SensorWidth;
  INT32                                 m_n32SensorHeight;
  FLOAT32                               m_f32OuterRoiDiameter;
  FLOAT32                               m_f32InnerRoiDiameter;
  enum BGA_MEASURE_ASSESSMENT           m_eMeasureAssessment;
  enum BGA_CIRCULARITY_ASSESSMENT       m_eCircularityAssessment;

  ECircleGauge*                         m_pCircleGauge;
  EWorldShape*                          m_pCircleGaugeWorldShape;
};

inline BOOL EBGA::GetPackCloseBlobs( ) const
{
  return m_bPackCloseBlobs;
}

inline void EBGA::SetPackCloseBlobs( BOOL bPackCloseBlobs )
{
  m_bPackCloseBlobs = bPackCloseBlobs;
}

inline enum E_MEASUREMENT_UNITS EBGA::GetUnit( )
{
  return m_eUnit;
}

inline void EBGA::SetUnit( enum E_MEASUREMENT_UNITS eUnit)
{
  m_eUnit = eUnit;
}


//////////////////////////////////////////////////////////////////////////////
//
#endif // __EBGA_H__
