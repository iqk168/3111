////////////////////////////////////////////////////////////////////////////////////////////////////
// EGauge.h: EasyGauge library header file for eVision 6.7.1.0
//
// EasyGauge performs sub-pixel precision calibrated geometric measurements
//
// Copyright ( c) 1997-2006, Euresys. All rights reserved.
//

#ifndef __EGAUGE_H__
#define __EGAUGE_H__

// eVision header files
#include "EInspect.h"
#include "EGauge_Enum.h"


struct ESampledPoint //--ND
{
  EPoint    m_Point;
  FLOAT32   m_f32Distance;
  INT32     m_n32RegionLabel; // only set and used for CircleGauge
  FLOAT32   m_f32Weight;
  BOOL      m_bValid;
  BOOL      m_bOutliers;
  BOOL      m_bInSkipRanges; // TRUE when skipped because of dont care range
};

// Stream operators
////////////////////////////////////////////////////////////////////////////////////////////////////////
E_DLL0 std::ostream& E_DLL1  operator<<( std::ostream& strm, const ESampledPoint& sampledPoint);


class ESampledPointsVector : public EVectorTemplate<ESampledPoint> //--ND
{
  // Wrapping members
public:
  int handle_;
  FinalizeCallback callback_;

public:
  // Mandated to avoid confusion with the copy constructor
  E_DLL0 CONSTRUCTOR E_DLL1         ESampledPointsVector    ( ) 
  {
    handle_ = 0;
    callback_ = 0;
  }
  E_DLL0 CONSTRUCTOR E_DLL1         ESampledPointsVector    ( UINT32 un32MaxElements);
  
  E_DLL0 void E_DLL1                Draw                    ( HDC hDC, BOOL bDaughters = FALSE,
                                                              FLOAT32 f32ZoomX = 1.f, FLOAT32 f32ZoomY = 0.f,
                                                              FLOAT32 f32PanX = 0.f, FLOAT32 f32PanY = 0.f);
  E_DLL0 void E_DLL1                Draw                    ( Euresys::DrawAdapter* drawAdapter, BOOL bDaughters = FALSE,
                                                              FLOAT32 f32ZoomX = 1.f, FLOAT32 f32ZoomY = 0.f,
                                                              FLOAT32 f32PanX = 0.f, FLOAT32 f32PanY = 0.f);

};

class EProfileVector: public EBW32Vector //--ND
{
  // Wrapping members
public:
  int handle_;
  FinalizeCallback callback_;

  EProfileVector( ) 
  {
    handle_ = 0;
    callback_ = 0;
  }

public:
  E_DLL0 void E_DLL1                DrawAnnotations         ( HDC hDC, UINT32 un32Weight,
                                                              INT32 n32Width, INT32 n32Height,
                                                              INT32 n32OrgX, INT32 n32OrgY,
                                                              char* pszXLabel, char* pszYLabel);
  E_DLL0 void E_DLL1                Plot                    ( HDC hDC, UINT32 un32Weight,
                                                              FLOAT32 f32Width, FLOAT32 f32Height,
                                                              FLOAT32 f32OrgX = 0.f, FLOAT32 f32OrgY = 0.f);
  E_DLL0 void E_DLL1                DrawAnnotations         ( Euresys::DrawAdapter* drawAdapter, UINT32 un32Weight,
                                                              INT32 n32Width, INT32 n32Height,
                                                              INT32 n32OrgX, INT32 n32OrgY,
                                                              char* pszXLabel, char* pszYLabel);
  E_DLL0 void E_DLL1                Plot                    ( Euresys::DrawAdapter* drawAdapter, UINT32 un32Weight,
                                                              FLOAT32 f32Width, FLOAT32 f32Height,
                                                              FLOAT32 f32OrgX = 0.f, FLOAT32 f32OrgY = 0.f);

};


class EDerivativeVector: public EBW32Vector //--ND
{
  // Wrapping members
public:
  int handle_;
  FinalizeCallback callback_;

  EDerivativeVector( ) 
  {
    handle_ = 0;
    callback_ = 0;
  }

public:
  E_DLL0 void E_DLL1                DrawAnnotations         ( HDC hDC, UINT32 un32Weight,
                                                              INT32 n32Width, INT32 n32Height,
                                                              INT32 n32OrgX, INT32 n32OrgY,
                                                              char* pszXLabel, char* pszYLabel);
  E_DLL0 void E_DLL1                Plot                    ( HDC hDC, UINT32 un32Weight,
                                                              UINT32 un32Amplitude,
                                                              FLOAT32 f32Width, FLOAT32 f32Height,
                                                              FLOAT32 f32OrgX = 0.f, FLOAT32 f32OrgY = 0.f);
  E_DLL0 void E_DLL1                DrawAnnotations         ( Euresys::DrawAdapter* drawAdapter, UINT32 un32Weight,
                                                              INT32 n32Width, INT32 n32Height,
                                                              INT32 n32OrgX, INT32 n32OrgY,
                                                              char* pszXLabel, char* pszYLabel);
  E_DLL0 void E_DLL1                Plot                    ( Euresys::DrawAdapter* drawAdapter, UINT32 un32Weight,
                                                              UINT32 un32Amplitude,
                                                              FLOAT32 f32Width, FLOAT32 f32Height,
                                                              FLOAT32 f32OrgX = 0.f, FLOAT32 f32OrgY = 0.f);
};


class ETransition //--ND
{
  // Wrapping members
public:
  int handle_;
  FinalizeCallback callback_;

public:
  // Constructor
  E_DLL0 CONSTRUCTOR E_DLL1         ETransition             ( FLOAT32 f32Tolerance = 10.f, FLOAT32 f32ToleranceAngle = 0);
 
public :
//  virtual E_DLL0 void E_DLL1        DumpToStream            ( std::ostream& strm , int indent = 0 ) const;

public :

  // Update
  E_DLL0 void E_DLL1                SetTolerance            ( FLOAT32 f32Tolerance, FLOAT32 Angle = 0);
  E_DLL0 void E_DLL1                Rescale                 ( FLOAT32 f32Factor);
  
  // Inquiry
  E_DLL0 FLOAT32 E_DLL1             GetTolerance            ( );
  E_DLL0 FLOAT32 E_DLL1             GetToleranceAngle       ( );
  E_DLL0 BOOL E_DLL1                GetHVConstraint         ( ) { return m_bHVConstraint; }
  E_DLL0 void E_DLL1                SetHVConstraint         ( BOOL bHVConstraint) { m_bHVConstraint = bHVConstraint; }

  // Spatial filtering
  E_DLL0 UINT32 E_DLL1              GetThickness            ( ) { return m_un32Thickness; }
  E_DLL0 void E_DLL1                SetThickness            ( UINT32 un32Thickness) { m_un32Thickness = un32Thickness; }
                                                      
  E_DLL0 UINT32 E_DLL1              GetSmoothing            ( ) { return m_un32Smoothing; }
  E_DLL0 void E_DLL1                SetSmoothing            ( UINT32 un32Smoothing) { m_un32Smoothing = un32Smoothing; }

  // Point selection
  E_DLL0 void E_DLL1                SetTransitionType       ( enum GGE_TRANSITION_TYPE eTransitionType) { m_eTransitionType = eTransitionType; }
  E_DLL0 enum GGE_TRANSITION_TYPE E_DLL1 GetTransitionType  ( ) { return m_eTransitionType; }

  E_DLL0 void E_DLL1                SetTransitionChoice     ( enum GGE_TRANSITION_CHOICE eTransitionChoice) { m_eTransitionChoice = eTransitionChoice; }
  E_DLL0 enum GGE_TRANSITION_CHOICE E_DLL1 GetTransitionChoice( ) { return m_eTransitionChoice; }

  E_DLL0 void E_DLL1                SetTransitionIndex      ( UINT32 un32TransitionIndex) { m_un32TransitionIndex = un32TransitionIndex; }
  E_DLL0 UINT32 E_DLL1              GetTransitionIndex      ( ) { return m_un32TransitionIndex; }

  E_DLL0 void E_DLL1                SetThreshold            ( UINT32 un32Threshold) { m_un32Threshold = un32Threshold; }
  E_DLL0 UINT32 E_DLL1              GetThreshold            ( ) { return m_un32Threshold; }

  E_DLL0 void E_DLL1                SetMinAmplitude         ( UINT32 un32MinAmplitude) { m_un32MinAmplitude = un32MinAmplitude; }
  E_DLL0 UINT32 E_DLL1              GetMinAmplitude         ( ) { return m_un32MinAmplitude; }

  E_DLL0 void E_DLL1                SetMinArea              ( UINT32 un32MinArea) { m_un32MinArea = un32MinArea; }
  E_DLL0 UINT32 E_DLL1              GetMinArea              ( ) { return m_un32MinArea; }
  
  
  
  E_DLL0 void E_DLL1                SetKeepFirstAndLastIncompletePeak( BOOL bKeepFirstAndLastIncompletePeak) { m_bKeepFirstAndLastIncompletePeak = bKeepFirstAndLastIncompletePeak;}
  E_DLL0 BOOL E_DLL1                GetKeepFirstAndLastIncompletePeak( ) {return m_bKeepFirstAndLastIncompletePeak;}
  
  // Measurement results
  E_DLL0 UINT32 E_DLL1              GetNumMeasuredPoints    ( );
  E_DLL0 EPoint E_DLL1              GetMeasuredPoint        ( UINT32 un32Index = ~0);
  E_DLL0 EPeak E_DLL1               GetMeasuredPeak         ( UINT32 un32Index = ~0);
  E_DLL0 BOOL E_DLL1                GetValid                ( );
  
  // Data vectors
  EProfileVector                    m_Profile;
  EDerivativeVector                 m_Derivative;
  EPeaksVector                      m_Peaks;
  
  // Drawing
  E_DLL0 void E_DLL1                Plot                    ( HDC hDC, enum GGE_PLOT_ITEMS eDrawItems,
                                                              FLOAT32 f32Width, FLOAT32 f32Height,
                                                              FLOAT32 f32OrgX = 0.f, FLOAT32 f32OrgY = 0.f);
  E_DLL0 void E_DLL1                Plot                    ( Euresys::DrawAdapter* drawAdapter, enum GGE_PLOT_ITEMS eDrawItems,
                                                              FLOAT32 f32Width, FLOAT32 f32Height,
                                                              FLOAT32 f32OrgX = 0.f, FLOAT32 f32OrgY = 0.f);


protected:
  // Serialization  
  E_DLL0 UINT32 E_DLL1              GetSignature            ( );
  virtual E_DLL0 void E_DLL1        Serialize               ( FILE*  pFile, BOOL bWrite, UINT32 un32Version);
  
  //Transition shape
  E_DLL0 void E_DLL1                SetTransitionRectangularSamplingArea      ( BOOL bRectangularSamplingArea) { m_bRectangularSamplingArea = bRectangularSamplingArea;}
  E_DLL0 BOOL E_DLL1                GetTransitionRectangularSamplingArea      ( ) {return m_bRectangularSamplingArea;}

  BOOL                              m_bValid;
  BOOL                              m_bHVConstraint; 
  UINT32                            m_un32Thickness; 
  UINT32                            m_un32Smoothing; 
                                    
  // Tolerance line                 
  ELine                             m_Tol;
  void                              Constrain               ( INT32& n32OrgX, INT32& n32OrgY, INT32& n32EndX, INT32& n32EndY);
                                    
  // Digital segment endpoints      
  INT32                             m_n32OrgX;
  INT32                             m_n32OrgY;
  INT32                             m_n32EndX;
  INT32                             m_n32EndY;
  UINT32                            m_un32Weight;
                                    
  // Transition type                
  enum GGE_TRANSITION_TYPE          m_eTransitionType;
                                    
  // Transition choice              
  enum GGE_TRANSITION_CHOICE        m_eTransitionChoice;
  UINT32                            m_un32TransitionIndex;
  
  // Measurement
  E_DLL0 void E_DLL1                Analyse                 ( EBW32Vector* pProfile, INT32 n32LowThreshold, INT32 n32HighThreshold);
  E_DLL0 void E_DLL1                Measure                 ( EROIBW8* pSrc, INT32 n32OrgX, INT32 n32OrgY, INT32 n32EndX, INT32 n32EndY);
  
  // Peak strength
  UINT32                            m_un32Threshold;
  UINT32                            m_un32MinAmplitude;
  UINT32                            m_un32MinArea;

  
  

  // Keep or discard the first incomplete peak
  BOOL                              m_bKeepFirstAndLastIncompletePeak;
                                    
  // Filtering                      
  void                              SampleProfile           ( EROIBW8* pSrc);
  void                              RectangularSampleProfile( EROIBW8* pSrc);
  void                              SmoothProfile           ( );
  E_DLL0 void E_DLL1                DeriveProfile           ( );
  UINT32                            m_un32PointIndex;
                                    
  // Drawing                        
  BOOL                              m_bProfile;
  void                              DrawTransition          ( HDC hDC, INT32 n32OrgX, INT32 n32OrgY, INT32 n32EndX, INT32 n32EndY);
  void                              DrawTransition          ( Euresys::DrawAdapter* drawAdapter, INT32 n32OrgX, INT32 n32OrgY, INT32 n32EndX, INT32 n32EndY);


  BOOL                              m_bRectangularSamplingArea;
  INT32                             m_n32XRectOffset; // XOffset of rect corner in axes placed at the origin of the pointgauge.
  INT32                             m_n32YRectOffset; // YOffset of rect corner in axes placed at the origin of the pointgauge.
                                    
  friend class                      ERectangleGauge;
  friend class                      EWedgeGauge;
  friend class                      EBarCode;
};


class EPointGauge: public EPointShape, public ETransition
{
  // Wrapping members
public:
  int handle_;
  FinalizeCallback callback_;

public:
  // Constructors
  
  E_DLL0 CONSTRUCTOR E_DLL1         EPointGauge             ( FLOAT32 f32CenterX = 0, FLOAT32 f32CenterY = 0) 
  {
    handle_ = 0;
    callback_ = 0;
    SetCenter( f32CenterX, f32CenterY);
    m_eDraggingMode = INS_DRAG_STANDARD;
    m_un32PointIndex = static_cast<UINT32>(~0);
    m_eTransitionChoice = GGE_ALL;
  }
  
  // Copy constructor, assignment operator and related methods
private :
  E_DLL0 void E_DLL1                InitEmpty               ( ); 
  E_DLL0 void E_DLL1                MakeEmpty               ( ); 

protected : 
  E_DLL0 EPointGauge* E_DLL1        InternalCopyTo          ( EPointGauge* dest, BOOL bRecursive, BOOL bIsACtor) const;
                                                      
public :                                              
  virtual E_DLL0 EShape* E_DLL1     CreateShapeClone        ( BOOL bRecursive ) const; 
                                                      

public :                                              
//  virtual E_DLL0 void E_DLL1        DumpToStream            ( std::ostream& strm , int indent = 0) const;


public :                                              
  E_DLL0 EPointGauge* E_DLL1        CopyTo                  ( EPointGauge* dest, BOOL bRecursive ) const;
  E_DLL0 CONSTRUCTOR E_DLL1         EPointGauge             ( const EPointGauge& otherInstance);
  E_DLL0 EPointGauge& E_DLL1        operator=               ( const EPointGauge& otherInstance);

public :
  E_DLL0 EShape* E_DLL1             New                     ( ) { return new EPointGauge( *this); }

  // Queries
  EPoint                            GetShape                ( ) { return GetActualShape( ) && GetFound( ) ? GetMeasuredPoint( ) : *this; }
  
  // Update
  E_DLL0 void E_DLL1                SetCenter               ( EPoint Point) { SetCenter( Point.GetX( ), Point.GetY( )); }
  E_DLL0 void E_DLL1                SetCenter               ( FLOAT32 f32CenterX, FLOAT32 f32CenterY);
  E_DLL0 void E_DLL1                Rescale                 ( FLOAT32 f32Factor, BOOL bDaughters = TRUE);
  E_DLL0 void E_DLL1                SetActive               ( BOOL bFound, BOOL bDaughters = FALSE);
          
  // Transition Shape
  E_DLL0 void E_DLL1                SetRectangularSamplingArea     ( BOOL bRectangularSamplingArea); 
  E_DLL0 BOOL E_DLL1                GetRectangularSamplingArea      ( );

  // Measurement                                      
  E_DLL0 void E_DLL1                Measure                 ( EROIBW8* pSrc);
  E_DLL0 void E_DLL1                Process                 ( EROIBW8* pSrc, BOOL bDaughters = true);
                                                      
  // Results
  E_DLL0 EPoint E_DLL1              GetMeasuredPoint        ( UINT32 un32Index = ~0);
                              
  // Geometry                 
  E_DLL0 EFrame* E_DLL1             CastToFrame             ( ) { return ( GetFound( ) && m_eTransitionChoice != GGE_ALL) ? GetMeasuredFrame( ) : &m_Tol; }
  E_DLL0 EFrame* E_DLL1             GetMeasuredFrame        ( UINT32 un32Index = ~0);
  
  // Typing
  E_DLL0 enum INS_SHAPE_TYPES E_DLL1 GetType                ( );
  
  // Drawing
  E_DLL0 void E_DLL1                Draw                    ( HDC hDC,
                                                              enum INS_DRAWING_MODES eDrawingMode = INS_DRAW_NOMINAL,
                                                              BOOL bDaughters = FALSE);

  E_DLL0 void E_DLL1                Draw                    ( Euresys::DrawAdapter* drawAdapter,
                                                              enum INS_DRAWING_MODES eDrawingMode = INS_DRAW_NOMINAL,
                                                              BOOL bDaughters = FALSE);
                                                      
  // Dragging                                         
  E_DLL0 BOOL E_DLL1                HitTest                 ( BOOL bDaughters = TRUE);
  E_DLL0 void E_DLL1                Drag                    ( INT32 n32CursorX, INT32 n32CursorY);
  
protected:
  // Measurement result
  EFrame m_Measured;

protected:
  // Serialization
  E_DLL0 UINT32 E_DLL1              GetSignature            ( );
  virtual E_DLL0 void E_DLL1        Serialize               ( FILE*  pFile, BOOL bWrite, UINT32 un32FileVersion, BOOL bDaughters = TRUE);
  virtual E_DLL0 void E_DLL1        Serialize               ( ESerializer* serializer, UINT32 un32FileVersion, BOOL bDaughters = TRUE);
};

// predefined type for internal reserved data
struct EGauge_OpDat;

class EGauge
{
  // Wrapping members
public:
  int handle_;
  FinalizeCallback callback_;

public:
  E_DLL0 CONSTRUCTOR E_DLL1         EGauge                  ( );
  virtual E_DLL0 E_DLL1             ~EGauge                 ( );
  E_DLL0 CONSTRUCTOR E_DLL1         EGauge                  ( const EGauge& other);
  E_DLL0 EGauge& E_DLL1             operator=               ( const EGauge& other);

protected :
  E_DLL0 EGauge* E_DLL1             InternalCopyTo          ( EGauge* dest, BOOL bIsACtor) const;

public :
//  virtual E_DLL0 void E_DLL1        DumpToStream            ( std::ostream& strm , int indent = 0 ) const;


  // Measured sample points
  EVectorTemplate<ESampledPoint> m_Samples;
  
  // Sample fitting post-filtering
  E_DLL0 FLOAT32 E_DLL1             GetFilteringThreshold   ( ) { return m_f32FilteringThreshold; }
  E_DLL0 void E_DLL1                SetFilteringThreshold   ( FLOAT32 f32FilteringThreshold) { m_f32FilteringThreshold = f32FilteringThreshold; }
                                                      
  E_DLL0 UINT32 E_DLL1              GetNumFilteringPasses   ( ) { return m_un32NumFilteringPasses; }
  E_DLL0 void E_DLL1                SetNumFilteringPasses   ( UINT32 un32NumFilteringPasses) { m_un32NumFilteringPasses = un32NumFilteringPasses; }
  // Measurement results
  E_DLL0 UINT32 E_DLL1              GetNumValidSamples      ( ) { return m_un32NumValidSamples; }
                                                      
  E_DLL0 FLOAT32 E_DLL1             GetAverageDistance      ( ) { return m_f32AverageDistance; }

  // fitting num. of samples constraint
  E_DLL0 void E_DLL1                SetMinNumFitSamples     ( INT32 n32Side0, INT32 n32Side1 = -1, INT32 n32Side2 = -1, INT32 n32Side3 = -1);
  E_DLL0 void E_DLL1                GetMinNumFitSamples     ( INT32& n32Side0, INT32& n32Side1 , INT32& n32Side2, INT32& n32Side3);

  // Skip ranges
  E_DLL0 UINT32 E_DLL1              AddSkipRange            ( const UINT32 start, const UINT32 end);
  E_DLL0 UINT32 E_DLL1              GetNumSkipRanges        ( ) const;
  E_DLL0 void E_DLL1                GetSkipRange            ( const UINT32 index, UINT32& start, UINT32& end) const;
  E_DLL0 void E_DLL1                RemoveSkipRange         ( const UINT32 index);
  E_DLL0 void E_DLL1                RemoveAllSkipRanges     ( );

protected:
  FLOAT32                           m_f32FilteringThreshold; 
  UINT32                            m_un32NumFilteringPasses; 
  UINT32                            m_un32NumValidSamples; 
  FLOAT32                           m_f32AverageDistance; 
public :
  EGauge_OpDat*                     _reserved;
};

class ELineGauge: public ELineShape, public ETransition, public EGauge
{
  // Wrapping members
public:
  int handle_;
  FinalizeCallback callback_;

public:
  // Constructor
  E_DLL0 CONSTRUCTOR E_DLL1         ELineGauge              ( );

  // Copy constructor, assignment operator and related methods
private :
  E_DLL0 void E_DLL1                InitEmpty               ( ); 
  E_DLL0 void E_DLL1                MakeEmpty               ( ); 
                                                      
protected :                   
  E_DLL0 ELineGauge* E_DLL1         InternalCopyTo          ( ELineGauge*, BOOL bRecursive, BOOL bIsACtor) const;
                                                      
public :                                              
  virtual E_DLL0 EShape* E_DLL1     CreateShapeClone        ( BOOL bRecursive ) const; 
                                                      
public :                                              
//  virtual E_DLL0 void E_DLL1        DumpToStream            ( std::ostream& strm , int indent = 0) const;

public :
  E_DLL0 ELineGauge* E_DLL1         CopyTo                  ( ELineGauge* dest, BOOL bRecursive ) const;
  E_DLL0 CONSTRUCTOR E_DLL1         ELineGauge              ( const ELineGauge& otherInstance);
  E_DLL0 ELineGauge& E_DLL1         operator=               ( const ELineGauge& otherInstance);

public :
  E_DLL0 EShape* E_DLL1             New                     ( ) { return new ELineGauge( *this); }
  
  // Typing
  E_DLL0 enum INS_SHAPE_TYPES E_DLL1 GetType                ( );
  
  // Update
  E_DLL0 void E_DLL1                Set                     ( ELine Line = ELine( EPoint( 0, 0), 2));
  E_DLL0 void E_DLL1                Set                     ( EPoint center, FLOAT32 length, FLOAT32 angle = 0) {ELineShape::Set(center, length, angle);};
  E_DLL0 void E_DLL1                Set                     ( EPoint origin, EPoint end) {ELineShape::Set(origin, end);};
  E_DLL0 void E_DLL1                Rescale                 ( FLOAT32 f32Factor, BOOL bDaughters = TRUE);
  E_DLL0 void E_DLL1                SetFound                ( BOOL bFound, BOOL bDaughters = FALSE);
  E_DLL0 void E_DLL1                SetActive               ( BOOL bFound, BOOL bDaughters = FALSE);

  // Queries
  ELine                             GetShape                ( ) { return ( GetActualShape( ) && GetFound( )) ? m_Measured : *this; }
  
  // Transition Shape
  E_DLL0 void E_DLL1                SetRectangularSamplingArea      ( BOOL bRectangularSamplingArea);
  E_DLL0 BOOL E_DLL1                GetRectangularSamplingArea      ( );

  // Edge point sampling
  E_DLL0 FLOAT32 E_DLL1             GetSamplingStep         ( ) { return m_f32SamplingStep; }
  E_DLL0 void E_DLL1                SetSamplingStep         ( FLOAT32 f32SamplingStep) { m_f32SamplingStep = f32SamplingStep; }
                              
  E_DLL0 UINT32 E_DLL1              GetNumSamples           ( );
  E_DLL0 UINT32 E_DLL1              GetNumSamples           ( ) const;

  // Processing
  E_DLL0 void E_DLL1                Process                 ( EROIBW8* pSrc, BOOL bDaughters = true);
                              
  // Measurement              
  E_DLL0 BOOL E_DLL1                GetKnownAngle           ( ) { return m_bKnownAngle; }
  E_DLL0 void E_DLL1                SetKnownAngle           ( BOOL bKnownAngle) { m_bKnownAngle = bKnownAngle; }
  E_DLL0 void E_DLL1                SetClippingMode         ( GGE_CLIPPING_MODE);
  E_DLL0 GGE_CLIPPING_MODE E_DLL1   GetClippingMode         ( ) const;
  E_DLL0 void E_DLL1                Measure                 ( EROIBW8* pSrc);
  E_DLL0 void E_DLL1                MeasureSample           ( EROIBW8* pSrc, UINT32 un32Index);
  E_DLL0 void E_DLL1                FitLine                 ( );
  
  // Results
  E_DLL0 ELine E_DLL1               GetMeasuredLine         ( ) { return GetFound( ) ? m_Measured : *this; }
  E_DLL0 EPoint E_DLL1              GetMeasuredPoint        ( UINT32 un32Index = ~0);
  
  // Geometry
  E_DLL0 EFrame* E_DLL1             CastToFrame             ( ) { return GetFound( ) ? &m_Measured : this; }
  
  // Drawing
  E_DLL0 void E_DLL1                Draw                    ( HDC hDC, enum INS_DRAWING_MODES eDrawingMode = INS_DRAW_NOMINAL, BOOL bDaughters = FALSE);
  E_DLL0 void E_DLL1                Draw                    ( Euresys::DrawAdapter* drawAdapter, enum INS_DRAWING_MODES eDrawingMode = INS_DRAW_NOMINAL, BOOL bDaughters = FALSE);
                              
  // Dragging                 
  E_DLL0 BOOL E_DLL1                HitTest                 ( BOOL bDaughters = TRUE);
  E_DLL0 void E_DLL1                Drag                    ( INT32 n32CursorX, INT32 n32CursorY);
  
protected:
  // Serialization
  E_DLL0 UINT32 E_DLL1              GetSignature            ( );
  virtual E_DLL0 void E_DLL1        Serialize               ( ESerializer* serializer, UINT32 un32FileVersion, BOOL bDaughters = TRUE);
  virtual E_DLL0 void E_DLL1        Serialize               ( FILE*  pFile, BOOL bWrite, UINT32 un32FileVersion, BOOL bDaughters = TRUE);

  FLOAT32                           m_f32SamplingStep; 
  UINT32                            m_un32NumSamples; 
  BOOL                              m_bKnownAngle; 
                                    
private:                            
  // Current sample. This is a cursor that allows to retrieve detailed infotmations on a particular path                
  UINT32                            m_un32SampleIndex;
                                    
  // Measurement result             
  ELine                             m_Measured;
};


class ECircleGauge: public ECircleShape, public ETransition, public EGauge
{
  // Wrapping members
public:
  int handle_;
  FinalizeCallback callback_;

public:
  // Constructor
  E_DLL0 CONSTRUCTOR E_DLL1         ECircleGauge            ( );
  
  // Copy constructor, assignment operator and related methods
private :
  void                              InitEmpty               ( ); 
  void                              MakeEmpty               ( ); 

protected : 
  E_DLL0 ECircleGauge* E_DLL1       InternalCopyTo          ( ECircleGauge*, BOOL bRecursive, BOOL bIsACtor) const;
                                                      
public :                                              
  virtual E_DLL0 EShape* E_DLL1     CreateShapeClone        ( BOOL bRecursive ) const; 
                                                      
public :                                              
//  virtual E_DLL0 void E_DLL1        DumpToStream            ( std::ostream& strm , int indent = 0) const;
                                                      
public :                                              
  E_DLL0 ECircleGauge* E_DLL1       CopyTo                  ( ECircleGauge* dest, BOOL bRecursive ) const;
  E_DLL0 CONSTRUCTOR E_DLL1         ECircleGauge            ( const ECircleGauge& otherInstance);
  E_DLL0 ECircleGauge& E_DLL1       operator=               ( const ECircleGauge& otherInstance);

public :
  E_DLL0 EShape* E_DLL1             New                     ( ) { return new ECircleGauge( *this); }
  
  // Typing
  E_DLL0 enum INS_SHAPE_TYPES E_DLL1 GetType                ( );
  
  // Queries
  ECircle                           GetShape                ( ) { return ( GetActualShape( ) && GetFound( )) ? m_Measured : *this; }
  
  // Update
  E_DLL0 void E_DLL1                Set                     ( ECircle Circle = ECircle( EPoint( 0, 0), 2));
  E_DLL0 void E_DLL1                Set                     ( EPoint center, FLOAT32 diameter, FLOAT32 orgAngle = 0, BOOL direct = true) {ECircleShape::Set(center, diameter, orgAngle, direct);};
  E_DLL0 void E_DLL1                Set                     ( EPoint center, FLOAT32 diameter, FLOAT32 orgAngle, FLOAT32 amplitude) {ECircleShape::Set(center, diameter, orgAngle, amplitude);};
  E_DLL0 void E_DLL1                Set                     ( EPoint center, EPoint origin, BOOL direct = true) {ECircleShape::Set(center, origin, direct);};
  E_DLL0 void E_DLL1                Set                     ( EPoint origin, EPoint middle, EPoint end, BOOL full = true) {ECircleShape::Set(origin, middle, end, full);};
  E_DLL0 void E_DLL1                Rescale                 ( FLOAT32 f32Factor, BOOL bDaughters = TRUE);
  E_DLL0 void E_DLL1                SetFound                ( BOOL bFound, BOOL bDaughters = FALSE);
  E_DLL0 void E_DLL1                SetActive               ( BOOL bFound, BOOL bDaughters = FALSE);
  
  // Transition Shape
  E_DLL0 void E_DLL1                SetRectangularSamplingArea      ( BOOL bRectangularSamplingArea); 
  E_DLL0 BOOL E_DLL1                GetRectangularSamplingArea      ( ); 
  
  // Sample point rejection
  E_DLL0 FLOAT32 E_DLL1             GetInnerFilteringThreshold( ) { return m_f32InnerFilteringThreshold; }
  E_DLL0 void E_DLL1                SetInnerFilteringThreshold( FLOAT32 f32InnerFilteringThreshold) { m_f32InnerFilteringThreshold = f32InnerFilteringThreshold; }
  E_DLL0 void E_DLL1                DisableInnerFiltering   ( ) { m_f32InnerFilteringThreshold = FLOAT32_MAX; }
  E_DLL0 BOOL E_DLL1                IsInnerFilteringEnabled ( ) { return ( m_f32InnerFilteringThreshold != FLOAT32_MAX); }
  
  // Edge point sampling
  E_DLL0 FLOAT32 E_DLL1             GetSamplingStep         ( ) { return m_f32SamplingStep; }
  E_DLL0 void E_DLL1                SetSamplingStep         ( FLOAT32 f32SamplingStep) { m_f32SamplingStep = f32SamplingStep; }

  E_DLL0 UINT32 E_DLL1              GetNumSamples           ( );
  E_DLL0 UINT32 E_DLL1              GetNumSamples           ( ) const;

  // Processing
  E_DLL0 void E_DLL1                Process                 ( EROIBW8* pSrc, BOOL bDaughters = true);
                                                      
  // Measurement                                      
  E_DLL0 void E_DLL1                Measure                 ( EROIBW8* pSrc);
  E_DLL0 void E_DLL1                MeasureSample           ( EROIBW8* pSrc, UINT32 un32Index);
  E_DLL0 void E_DLL1                FitCircle               ( );
  E_DLL0 void E_DLL1                FitCircleWeighted       ( );
  
  // Fitting mode
  E_DLL0 enum GGE_FITTING_MODE E_DLL1 GetFittingMode        ( ) { return m_eFittingMode; }
  E_DLL0 void E_DLL1                SetFittingMode          ( enum GGE_FITTING_MODE eFittingMode) { m_eFittingMode = eFittingMode; }

  // Results
  E_DLL0 ECircle E_DLL1             GetMeasuredCircle       ( ) { return GetFound( ) ? m_Measured : *this; }
  E_DLL0 EPoint E_DLL1              GetMeasuredPoint        ( UINT32 un32Index = ~0);
  E_DLL0 FLOAT32 E_DLL1             GetMeasuredCircularity  ( ) { return m_f32MeasuredCircularity; }
  E_DLL0 FLOAT32 E_DLL1             GetMeasuredTotalTransition( ) { return m_f32MeasuredTotalTransition; }
                              
  // Geometry                 
  E_DLL0 EFrame* E_DLL1             CastToFrame             ( ) { return GetFound( ) ? &m_Measured : this; }
  
  // Measured points fitting
  EVectorTemplate<ESampledPoint> m_Samples;
  
  // Drawing
  E_DLL0 void E_DLL1                Draw                    ( HDC hDC, enum INS_DRAWING_MODES eDrawingMode = INS_DRAW_NOMINAL, BOOL bDaughters = FALSE);
  E_DLL0 void E_DLL1                Draw                    ( Euresys::DrawAdapter* drawAdapter, enum INS_DRAWING_MODES eDrawingMode = INS_DRAW_NOMINAL, BOOL bDaughters = FALSE);
                              
  // Dragging                 
  E_DLL0 BOOL E_DLL1                HitTest                 ( BOOL bDaughters = TRUE);
  E_DLL0 void E_DLL1                Drag                    ( INT32 n32CursorX, INT32 n32CursorY);
  
protected:
  // Serialization
  E_DLL0 UINT32 E_DLL1              GetSignature            ( );
  virtual E_DLL0 void E_DLL1        Serialize               ( ESerializer* serializer, UINT32 un32FileVersion, BOOL bDaughters = TRUE);
  virtual E_DLL0 void E_DLL1        Serialize               ( FILE*  pFile, BOOL bWrite, UINT32 un32FileVersion, BOOL bDaughters = TRUE);

  FLOAT32                           m_f32SamplingStep; 
  UINT32                            m_un32NumSamples; 
                                    
private:                            
  // Current sample                 
  UINT32                            m_un32SampleIndex;

  // Threshold (in pixels) used to reject sample point lying inside the measured circle
  FLOAT32                           m_f32InnerFilteringThreshold;
                                    
  // Method used to fit a circle on transition points
  enum GGE_FITTING_MODE             m_eFittingMode;

  FLOAT32                           m_f32MeasuredCircularity;
  FLOAT32                           m_f32MeasuredTotalTransition;

  // Measurement result             
  ECircle                           m_Measured;
};


class ERectangleGauge: public ERectangleShape, public EGauge
{
  // Wrapping members
public:
  int handle_;
  FinalizeCallback callback_;

public:
  // Constructor
  E_DLL0 CONSTRUCTOR E_DLL1         ERectangleGauge         ( );
  
// Copy constructor, assignment operator and related methods
private :
  void                              InitEmpty               ( ); 
  void                              MakeEmpty               ( ); 

protected : 
  E_DLL0 ERectangleGauge* E_DLL1    InternalCopyTo          ( ERectangleGauge* dest, BOOL bRecursive, BOOL bIsACtor) const;
                                                      
public :                                              
  virtual E_DLL0 EShape* E_DLL1     CreateShapeClone        ( BOOL bRecursive ) const; 
                                                      
public :                                              
//  virtual E_DLL0 void E_DLL1        DumpToStream            ( std::ostream& strm , int indent = 0) const;
                                                      
public :                                              
  E_DLL0 ERectangleGauge* E_DLL1    CopyTo                  ( ERectangleGauge* dest, BOOL bRecursive ) const;
  E_DLL0 CONSTRUCTOR E_DLL1         ERectangleGauge         ( const ERectangleGauge& otherInstance);
  E_DLL0 ERectangleGauge& E_DLL1    operator=               ( const ERectangleGauge& otherInstance);

public :
  E_DLL0 EShape* E_DLL1             New                     ( ) { return new ERectangleGauge( *this); }
  
  // Typing
  E_DLL0 enum INS_SHAPE_TYPES E_DLL1 GetType                ( );

  // Queries
  ERectangle                        GetShape                ( ) { return ( GetActualShape( ) && GetFound( )) ? m_Measured : *this; }
  
  // Update
  E_DLL0 void E_DLL1                Set                     ( ERectangle Rectangle = ERectangle( EPoint( 0, 0), 1, 1));
  E_DLL0 void E_DLL1                Set                     ( EPoint center, FLOAT32 sizeX, FLOAT32 sizeY, FLOAT32 angle = 0) {ERectangleShape::Set(center, sizeX, sizeY, angle);};
  E_DLL0 void E_DLL1                Set                     ( EPoint origin, EPoint end) {ERectangleShape::Set(origin, end);};
  E_DLL0 void E_DLL1                Set                     ( EPoint origin, EPoint middle, EPoint end) {ERectangleShape::Set(origin, middle, end);};
  E_DLL0 void E_DLL1                Rescale                 ( FLOAT32 f32Factor, BOOL bDaughters = TRUE);
  E_DLL0 void E_DLL1                SetFound                ( BOOL bFound, BOOL bDaughters = FALSE);
  E_DLL0 void E_DLL1                SetActive               ( BOOL bFound, BOOL bDaughters = FALSE);

  // Transition Shape
  E_DLL0 void E_DLL1                SetRectangularSamplingArea      ( BOOL bRectangularSamplingArea);
  E_DLL0 BOOL E_DLL1                GetRectangularSamplingArea      ( ); 

  // Sample point rejection
  E_DLL0 FLOAT32 E_DLL1             GetInnerFilteringThreshold( ) { return m_f32InnerFilteringThreshold; }
  E_DLL0 void E_DLL1                SetInnerFilteringThreshold( FLOAT32 f32InnerFilteringThreshold) { m_f32InnerFilteringThreshold = f32InnerFilteringThreshold; }
  E_DLL0 void E_DLL1                DisableInnerFiltering   ( ) { m_f32InnerFilteringThreshold = FLOAT32_MAX; }
  E_DLL0 BOOL E_DLL1                IsInnerFilteringEnabled ( ) { return ( m_f32InnerFilteringThreshold != FLOAT32_MAX); }
  
  // Behavior
  E_DLL0 UINT32 E_DLL1              GetActiveEdges          ( ) { return m_un32ActiveEdges; }
  E_DLL0 void E_DLL1                SetActiveEdges          ( UINT32 un32ActiveEdges) { m_un32ActiveEdges = un32ActiveEdges; }

  // Edge point sampling
  E_DLL0 void E_DLL1                SetTolerance            ( FLOAT32 f32Tolerance);
  E_DLL0 FLOAT32 E_DLL1             GetTolerance            ( );
  E_DLL0 void E_DLL1                SetHVConstraint         ( BOOL bHVConstraint);
  E_DLL0 BOOL E_DLL1                GetHVConstraint         ( );
  E_DLL0 void E_DLL1                SetTransitionType       ( enum GGE_TRANSITION_TYPE eTransitionType);
  E_DLL0 enum GGE_TRANSITION_TYPE E_DLL1  GetTransitionType ( );
  E_DLL0 void E_DLL1                SetTransitionChoice     ( enum GGE_TRANSITION_CHOICE eTransitionChoice);
  E_DLL0 enum GGE_TRANSITION_CHOICE E_DLL1  GetTransitionChoice( );
  E_DLL0 void E_DLL1                SetTransitionIndex      ( UINT32 un32TransitionIndex);
  E_DLL0 UINT32 E_DLL1              GetTransitionIndex      ( );
  E_DLL0 void E_DLL1                SetThreshold            ( UINT32 un32Threshold);
  E_DLL0 UINT32 E_DLL1              GetThreshold            ( );
  E_DLL0 void E_DLL1                SetMinAmplitude         ( UINT32 un32MinAmplitude);
  E_DLL0 UINT32 E_DLL1              GetMinAmplitude         ( );
  E_DLL0 void E_DLL1                SetMinArea              ( UINT32 un32MinArea);
  E_DLL0 UINT32 E_DLL1              GetMinArea              ( );
  E_DLL0 UINT32 E_DLL1              GetThickness            ( );
  E_DLL0 void E_DLL1                SetThickness            ( UINT32 un32Thickness);

  E_DLL0 UINT32 E_DLL1              GetSmoothing            ( );
  E_DLL0 void E_DLL1                SetSmoothing            ( UINT32 un32Smoothing);
                              
  E_DLL0 FLOAT32 E_DLL1             GetSamplingStep         ( ) { return m_f32SamplingStep; }
  E_DLL0 void E_DLL1                SetSamplingStep         ( FLOAT32 f32SamplingStep) { m_f32SamplingStep = f32SamplingStep; }
                              
  E_DLL0 UINT32 E_DLL1              GetNumSamples           ( );
  E_DLL0 UINT32 E_DLL1              GetNumSamples           ( ) const;
                              
  E_DLL0 UINT32 E_DLL1              GetNumSamplesx          ( );
  E_DLL0 UINT32 E_DLL1              GetNumSamplesx          ( ) const;
  E_DLL0 UINT32 E_DLL1              GetNumSamplesy          ( );
  E_DLL0 UINT32 E_DLL1              GetNumSamplesy          ( ) const;
  E_DLL0 UINT32 E_DLL1              GetNumSamplesX          ( );
  E_DLL0 UINT32 E_DLL1              GetNumSamplesX          ( ) const;
  E_DLL0 UINT32 E_DLL1              GetNumSamplesY          ( );
  E_DLL0 UINT32 E_DLL1              GetNumSamplesY          ( ) const;

  // Processing
  E_DLL0 void E_DLL1                Process                 ( EROIBW8* pSrc, BOOL bDaughters = TRUE);
  
  // Measurement
  E_DLL0 BOOL E_DLL1                GetKnownAngle           ( ) { return m_bKnownAngle; }
  E_DLL0 void E_DLL1                SetKnownAngle           ( BOOL bKnownAngle) { m_bKnownAngle = bKnownAngle; }
                                                      
  E_DLL0 void E_DLL1                Measure                 ( EROIBW8* pSrc);
  E_DLL0 void E_DLL1                MeasureSample           ( EROIBW8* pSrc, UINT32 un32Index);
  E_DLL0 void E_DLL1                FitRectangle            ( );
  
  // Results
  E_DLL0 ERectangle E_DLL1          GetMeasuredRectangle    ( ) { return GetFound( ) ? m_Measured : *this; }
  E_DLL0 EPoint E_DLL1              GetMeasuredPoint        (UINT32 un32Index = ~0);
  
  // Measured sample validity
  E_DLL0 BOOL E_DLL1                GetValid();
  
  // Geometry
  E_DLL0 EFrame* E_DLL1             CastToFrame             ( ) { return GetFound( ) ? &m_Measured : this; }
  
  // Per-edge transition parameters


  ETransition                       m_Transitionx;
  ETransition                       m_Transitiony;
  ETransition                       m_TransitionX;
  ETransition                       m_TransitionY;
  
  // Measured points fitting
  EVectorTemplate<ESampledPoint>    m_Samples;
  
  // Drawing
  E_DLL0 void E_DLL1                Draw                    ( HDC hDC,
                                                              enum INS_DRAWING_MODES eDrawingMode = INS_DRAW_NOMINAL,
                                                              BOOL bDaughters = FALSE);
  E_DLL0 void E_DLL1                Draw                    ( Euresys::DrawAdapter* drawAdapter,
                                                              enum INS_DRAWING_MODES eDrawingMode = INS_DRAW_NOMINAL,
                                                              BOOL bDaughters = FALSE);
  E_DLL0 void E_DLL1                Plot                    ( HDC hDC, enum GGE_PLOT_ITEMS eDrawItems,
                                                              FLOAT32 f32Width, FLOAT32 f32Height,
                                                              FLOAT32 f32OrgX = 0.f, FLOAT32 f32OrgY = 0.f);
  E_DLL0 void E_DLL1                Plot                    ( Euresys::DrawAdapter* drawAdapter, enum GGE_PLOT_ITEMS eDrawItems,
                                                              FLOAT32 f32Width, FLOAT32 f32Height,
                                                              FLOAT32 f32OrgX = 0.f, FLOAT32 f32OrgY = 0.f);
  
  // Dragging
  E_DLL0 BOOL E_DLL1                HitTest                 ( BOOL bDaughters = TRUE);
  E_DLL0 void E_DLL1                Drag                    ( INT32 n32CursorX, INT32 n32CursorY);
  
protected:
  // Serialization
  E_DLL0 UINT32 E_DLL1              GetSignature            ( );

  virtual E_DLL0 void E_DLL1        Serialize               ( ESerializer* serializer, UINT32 un32FileVersion, BOOL bDaughters = TRUE);
  virtual E_DLL0 void E_DLL1        Serialize               ( FILE*  pFile, BOOL bWrite, UINT32 un32FileVersion, BOOL bDaughters = TRUE);

  UINT32                            m_un32ActiveEdges; 
  UINT32                            m_un32Thickness; 
  UINT32                            m_un32Smoothing; 
  FLOAT32                           m_f32SamplingStep; 
  UINT32                            m_un32NumSamples; 
  UINT32                            m_un32NumSamplesx; 
  UINT32                            m_un32NumSamplesy; 
  UINT32                            m_un32NumSamplesX; 
  UINT32                            m_un32NumSamplesY; 
  BOOL                              m_bKnownAngle; 
                                    
private:                            
  // Current sample                 
  UINT32                            m_un32SampleIndex;

  // Threshold (in pixels) used to reject sample point lying inside the measured circle
  FLOAT32                           m_f32InnerFilteringThreshold;
                                    
  // Measurement result             
  ERectangle                        m_Measured;
};


class EWedgeGauge: public EWedgeShape, public EGauge
{
  // Wrapping members
public:
  int handle_;
  FinalizeCallback callback_;

public:
  // Constructor
  E_DLL0 CONSTRUCTOR E_DLL1         EWedgeGauge             ( );

  // Copy constructor, assignment operator and related methods
private :
  void                              InitEmpty               ( ); 
  void                              MakeEmpty               ( ); 

protected : 
  E_DLL0 EWedgeGauge* E_DLL1        InternalCopyTo          ( EWedgeGauge*, BOOL bRecursive, BOOL bIsACtor) const;
                                                      
public :                                              
  virtual E_DLL0 EShape* E_DLL1     CreateShapeClone        ( BOOL bRecursive ) const; 
                                                      
public :                                              
//  virtual E_DLL0 void E_DLL1        DumpToStream            ( std::ostream& strm , int indent = 0) const;
                                                      
public :                                              
  E_DLL0 EWedgeGauge* E_DLL1        CopyTo                  ( EWedgeGauge* dest, BOOL bRecursive ) const;
  E_DLL0 CONSTRUCTOR E_DLL1         EWedgeGauge             ( const EWedgeGauge& otherInstance);
  E_DLL0 EWedgeGauge& E_DLL1        operator=               ( const EWedgeGauge& otherInstance);

public :
  E_DLL0 EShape* E_DLL1             New                     ( ) { return new EWedgeGauge( *this); }
  
  // Typing
  E_DLL0 enum INS_SHAPE_TYPES E_DLL1 GetType                ( );

  // Queries
  EWedge                            GetShape                ( ) { return ( GetActualShape( ) && GetFound( )) ? m_Measured : *this; }
  
  // Update
  E_DLL0 void E_DLL1                Set                     ( EWedge Wedge = EWedge( EPoint( 0, 0), 1, 1));
  E_DLL0 void E_DLL1                Set                     ( EPoint center, FLOAT32 diameter, FLOAT32 breadth= 0, FLOAT32 orgAngle= 0, BOOL direct= TRUE); 
  E_DLL0 void E_DLL1                Set                     ( EPoint center, FLOAT32 diameter, FLOAT32 breadth, FLOAT32 orgAngle, FLOAT32 amplitude); 
  E_DLL0 void E_DLL1                Set                     ( EPoint center, EPoint origin, FLOAT32 breadth= 0, BOOL direct= TRUE); 
  E_DLL0 void E_DLL1                Set                     ( EPoint origin, EPoint middle, EPoint end, FLOAT32 breadth= 0, BOOL full= TRUE);
  E_DLL0 void E_DLL1                Rescale                 ( FLOAT32 f32Factor, BOOL bDaughters = TRUE);
  E_DLL0 void E_DLL1                SetFound                ( BOOL bFound, BOOL bDaughters = FALSE);
  E_DLL0 void E_DLL1                SetActive               ( BOOL bFound, BOOL bDaughters = FALSE);
  
  // Transition Shape
  E_DLL0 void E_DLL1                SetRectangularSamplingArea      ( BOOL bRectangularSamplingArea);
  E_DLL0 BOOL E_DLL1                GetRectangularSamplingArea      ( ); 

  // Behavior
  E_DLL0 UINT32 E_DLL1              GetActiveEdges          ( ) { return m_un32ActiveEdges; }
  E_DLL0 void E_DLL1                SetActiveEdges          ( UINT32 un32ActiveEdges);

  //Wedge shape
  E_DLL0 void E_DLL1                SetDiameters            ( FLOAT32 f32Diameter, FLOAT32 f32Breadth);
  E_DLL0 void E_DLL1                SetRadii				( FLOAT32 f32Radius, FLOAT32 f32Breadth);

  // Edge point sampling
  E_DLL0 void E_DLL1                SetTolerance            ( FLOAT32 f32Tolerance);
  E_DLL0 FLOAT32 E_DLL1             GetTolerance            ( );
  E_DLL0 void E_DLL1                SetHVConstraint         ( BOOL bHVConstraint);
  E_DLL0 BOOL E_DLL1                GetHVConstraint         ( );
  E_DLL0 void E_DLL1                SetTransitionType       ( enum GGE_TRANSITION_TYPE eTransitionType);
  E_DLL0 enum GGE_TRANSITION_TYPE E_DLL1  GetTransitionType ( );
  E_DLL0 void E_DLL1                SetTransitionChoice     ( enum GGE_TRANSITION_CHOICE eTransitionChoice);
  E_DLL0 enum GGE_TRANSITION_CHOICE E_DLL1  GetTransitionChoice( );
  E_DLL0 void E_DLL1                SetTransitionIndex      ( UINT32 un32TransitionIndex);
  E_DLL0 UINT32 E_DLL1              GetTransitionIndex      ( );
  E_DLL0 void E_DLL1                SetThreshold            ( UINT32 un32Threshold);
  E_DLL0 UINT32 E_DLL1              GetThreshold            ( );
  E_DLL0 void E_DLL1                SetMinAmplitude         ( UINT32 un32MinAmplitude);
  E_DLL0 UINT32 E_DLL1              GetMinAmplitude         ( );
  E_DLL0 void E_DLL1                SetMinArea              ( UINT32 un32MinArea);
  E_DLL0 UINT32 E_DLL1              GetMinArea              ( );
  E_DLL0 UINT32 E_DLL1              GetThickness            ( );
  E_DLL0 void E_DLL1                SetThickness            ( UINT32 un32Thickness);
                                                      
  E_DLL0 UINT32 E_DLL1              GetSmoothing            ( );
  E_DLL0 void E_DLL1                SetSmoothing            ( UINT32 un32Smoothing);
                              
  E_DLL0 FLOAT32 E_DLL1             GetSamplingStep         ( ) { return m_f32SamplingStep; }
  E_DLL0 void E_DLL1                SetSamplingStep         ( FLOAT32 f32SamplingStep) { m_f32SamplingStep = f32SamplingStep; }
                              
  E_DLL0 UINT32 E_DLL1              GetNumSamples           ( );
  E_DLL0 UINT32 E_DLL1              GetNumSamples           ( ) const;
                              
  E_DLL0 UINT32 E_DLL1              GetNumSamplesa          ( );
  E_DLL0 UINT32 E_DLL1              GetNumSamplesa          ( ) const;
  E_DLL0 UINT32 E_DLL1              GetNumSamplesr          ( );
  E_DLL0 UINT32 E_DLL1              GetNumSamplesr          ( ) const;
  E_DLL0 UINT32 E_DLL1              GetNumSamplesA          ( );
  E_DLL0 UINT32 E_DLL1              GetNumSamplesA          ( ) const;
  E_DLL0 UINT32 E_DLL1              GetNumSamplesR          ( );
  E_DLL0 UINT32 E_DLL1              GetNumSamplesR          ( ) const;

  // Processing
  E_DLL0 void E_DLL1                Process                 ( EROIBW8* pSrc, BOOL bDaughters = TRUE);
  
  // Measurement
  E_DLL0 void E_DLL1                Measure                 ( EROIBW8* pSrc);
  E_DLL0 void E_DLL1                MeasureSample           ( EROIBW8* pSrc, UINT32 un32Index);
  E_DLL0 void E_DLL1                FitWedge                ( );

  // Results
  E_DLL0 EWedge E_DLL1              GetMeasuredWedge        ( ) { return GetFound( ) ? m_Measured : *this; }
  E_DLL0 EPoint E_DLL1              GetMeasuredPoint        (UINT32 un32Index = ~0);

  // Measured sample validity
  E_DLL0 BOOL E_DLL1                GetValid();
  
  // Geometry
  E_DLL0 EFrame* E_DLL1             CastToFrame             ( ) { return GetFound( ) ? &m_Measured : this; }
  
  // Per-edge transition parameters
 private:
   void                             CheckToleranceVsGeometric  ();

public:  

   ETransition                       m_Transitiona;
   ETransition                       m_Transitionr;
   ETransition                       m_TransitionA;
   ETransition                       m_TransitionR;

  // Measured points fitting
  EVectorTemplate<ESampledPoint>    m_Samples;
  
  // Drawing
  E_DLL0 void E_DLL1                Draw                    ( HDC hDC,
                                                              enum INS_DRAWING_MODES eDrawingMode = INS_DRAW_NOMINAL,
                                                              BOOL bDaughters = FALSE);
  E_DLL0 void E_DLL1                Draw                    ( Euresys::DrawAdapter* drawAdapter,
                                                              enum INS_DRAWING_MODES eDrawingMode = INS_DRAW_NOMINAL,
                                                              BOOL bDaughters = FALSE);
  E_DLL0 void E_DLL1                Plot                    ( HDC hDC, enum GGE_PLOT_ITEMS eDrawItems,
                                                              FLOAT32 f32Width, FLOAT32 f32Height,
                                                              FLOAT32 f32OrgX = 0.f, FLOAT32 f32OrgY = 0.f);
  E_DLL0 void E_DLL1                Plot                    ( Euresys::DrawAdapter* drawAdapter, enum GGE_PLOT_ITEMS eDrawItems,
                                                              FLOAT32 f32Width, FLOAT32 f32Height,
                                                              FLOAT32 f32OrgX = 0.f, FLOAT32 f32OrgY = 0.f);

  // Dragging
  E_DLL0 BOOL E_DLL1                HitTest                 ( BOOL bDaughters = TRUE);
  E_DLL0 void E_DLL1                Drag                    ( INT32 n32CursorX, INT32 n32CursorY);
  
protected:
  // Serialization
  E_DLL0 UINT32 E_DLL1              GetSignature            ( );
  virtual E_DLL0 void E_DLL1        Serialize               ( ESerializer* serializer, UINT32 un32FileVersion, BOOL bDaughters = TRUE);
  virtual E_DLL0 void E_DLL1        Serialize               ( FILE*  pFile, BOOL bWrite, UINT32 un32FileVersion, BOOL bDaughters = TRUE);

  UINT32                            m_un32ActiveEdges; 
  UINT32                            m_un32Thickness; 
  UINT32                            m_un32Smoothing; 
  FLOAT32                           m_f32SamplingStep; 
  UINT32                            m_un32NumSamples; 
  UINT32                            m_un32NumSamplesa; 
  UINT32                            m_un32NumSamplesr; 
  UINT32                            m_un32NumSamplesA; 
  UINT32                            m_un32NumSamplesR; 
                                    
private:                            
  // Current sample                 
  UINT32                            m_un32SampleIndex;
                                    
  // Measurement result             
  EWedge                            m_Measured;
};


E_DLL0 Euresys::eVision::Segment E_DLL1 EBestFitLine(Euresys::eVision::Utils::Vector<Euresys::eVision::Point>& points, unsigned int numFilteringPasses= 2, double filteringThreshold= 3);


#endif // __EGAUGE_H__
