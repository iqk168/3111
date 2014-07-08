////////////////////////////////////////////////////////////////////////////////////////////////////
// EInspect.h: EasyInspect library header file for eVision 6.7.1.0
//
// EasyInspect implements a geometric framework for structured inspections
//
// Copyright ( c) 1997-2006, Euresys. All rights reserved.
//

#ifndef __EINSPECT_H__
#define __EINSPECT_H__

// eVision header files
#include "EImage.h"
#include "EInspect_Enum.h"


////////////////////////////////////////////////////////////////////////////////////////////////////
// Base shapes
//

// Forward declarations
class EWorld;
class EFrame;
class EPoint;
class ELine;
class ERectangle;
class ECircle;
class EWedge;

////////////////////////////////////////////////////////////////////////////////////////////////////
// Point primitive
class E_DLL1 EPoint
{
  // Wrapping members
public:
  int handle_;
  FinalizeCallback callback_;

public:
  // Constructors
  E_DLL0 CONSTRUCTOR E_DLL1         EPoint                  ( );
  E_DLL0 CONSTRUCTOR E_DLL1         EPoint                  ( FLOAT32 f32CenterX, FLOAT32 f32CenterY);

public :
  E_DLL0 CONSTRUCTOR E_DLL1         EPoint                  ( const EPoint& other);
  E_DLL0 EPoint& E_DLL1             operator=               ( const EPoint& other);

  virtual E_DLL0 EPoint* E_DLL1     CreatePointClone        ( ) const;
  E_DLL0 EPoint* E_DLL1             CopyTo                  ( EPoint* dest ) const;

protected :
  E_DLL0 EPoint* E_DLL1             InternalCopyTo          ( EPoint* dest, BOOL isACtor) const;

public :
  // Updates                                          
  E_DLL0 void E_DLL1                Set                     ( FLOAT32 f32CenterX, FLOAT32 f32CenterY);
                                                               
  E_DLL0 void E_DLL1                SetCenter               ( EPoint Center);
  E_DLL0 void E_DLL1                SetCenter               ( FLOAT32 f32CenterX, FLOAT32 f32CenterY);
                                                      
  // Queries                                          
  E_DLL0 FLOAT32 E_DLL1             GetX                    ( ) const;
  E_DLL0 FLOAT32 E_DLL1             GetY                    ( ) const;
  E_DLL0 FLOAT32& E_DLL1            x( ) { return m_f32CenterX; }
  E_DLL0 FLOAT32& E_DLL1            y( ) { return m_f32CenterY; }
  E_DLL0 EPoint E_DLL1              GetCenter               ( );
                                                      
  // Vector arithmetic                                
  E_DLL0 EPoint E_DLL1              operator+               ( EPoint Point);
  E_DLL0 EPoint E_DLL1              operator-               ( EPoint Point);
  E_DLL0 EPoint E_DLL1              operator*               ( FLOAT32 f32Scalar);
  E_DLL0 EPoint E_DLL1              operator/               ( FLOAT32 f32Scalar);
  E_DLL0 BOOL   E_DLL1              operator==              ( EPoint Point);
  E_DLL0 BOOL   E_DLL1              operator!=              ( EPoint Point);

  E_DLL0 EPoint E_DLL1              MidPoint                ( EPoint Point);
  E_DLL0 EPoint E_DLL1              Rotate                  ( FLOAT32 f32Angle);
                                                      
  E_DLL0 FLOAT32 E_DLL1             Square                  ( );
  E_DLL0 FLOAT32 E_DLL1             Modulus                 ( );
  E_DLL0 FLOAT32 E_DLL1             Argument                ( );
                                                            
  E_DLL0 FLOAT32 E_DLL1             Dot                     ( EPoint Point);
  E_DLL0 FLOAT32 E_DLL1             Area                    ( EPoint Point);
                                                      
  // Projections                                      
  E_DLL0 EPoint E_DLL1              Project                 ( ELine Line);
  E_DLL0 EPoint E_DLL1              Project                 ( ECircle Circle);
                                                      
  // Distances                                        
  E_DLL0 FLOAT32 E_DLL1             SquaredDistance         ( EPoint Point);
  E_DLL0 FLOAT32 E_DLL1             Distance                ( EPoint Point);
  E_DLL0 FLOAT32 E_DLL1             Distance                ( ELine Line, BOOL bSegmentOnly = FALSE);
  E_DLL0 FLOAT32 E_DLL1             Distance                ( ECircle Circle, BOOL bArcOnly = FALSE);
  //E_DLL0 FLOAT32 E_DLL1             Distance                ( ERectangle Rectangle, BOOL bEdgesOnly = FALSE);
                                                      
  // Serialization                                    
  virtual E_DLL0 void E_DLL1        Serialize               ( ESerializer* serializer, UINT32 un32FileVersion);
  virtual E_DLL0 void E_DLL1        Serialize               ( FILE*  pFile, BOOL bWrite, UINT32 un32FileVersion);

// Debug DumpToStream method
// ---------------------------------------------------------------------------
public :
//  virtual E_DLL0 void E_DLL1        DumpToStream            ( std::ostream& strm , int indent = 0 ) const;

protected:
  // Coordinates
  FLOAT32                           m_f32CenterX;
  FLOAT32                           m_f32CenterY;
};

// stream operator for EPoint
E_DLL0 std::ostream& E_DLL1  operator<<( std::ostream& stream, const EPoint& point);

////////////////////////////////////////////////////////////////////////////////////////////////////
// Frame primitive
class E_DLL1 EFrame: public EPoint
{
  // Wrapping members
public:
  int handle_;
  FinalizeCallback callback_;

public:
  // Constructors
  E_DLL0 CONSTRUCTOR E_DLL1         EFrame                  ( );
  E_DLL0 CONSTRUCTOR E_DLL1         EFrame                  ( FLOAT32 f32CenterX, FLOAT32 f32CenterY,
                                                              FLOAT32 f32Angle = 0, FLOAT32 f32Scale = 1);
public :
  E_DLL0 CONSTRUCTOR E_DLL1         EFrame                  ( const EFrame& frame);
  E_DLL0 EFrame& E_DLL1             operator=               ( const EFrame& frame);

  virtual E_DLL0 EPoint* E_DLL1     CreatePointClone        ( ) const;
  E_DLL0 EFrame* E_DLL1             CopyTo                  ( EFrame* dest ) const;

protected :
  E_DLL0 EFrame* E_DLL1             InternalCopyTo          ( EFrame*, BOOL ) const;

public :
  // Updates                                          
  E_DLL0 void E_DLL1                Set                     ( EPoint Center,
                                                              FLOAT32 f32Angle = 0, FLOAT32 f32Scale = 1);
                                                               
  E_DLL0 void E_DLL1                SetAngle                ( FLOAT32 f32Angle);
  E_DLL0 void E_DLL1                SetScale                ( FLOAT32 f32Scale);
                                                      
  // Queries                                          
  E_DLL0 FLOAT32 E_DLL1             GetCenterX              ( );
  E_DLL0 FLOAT32 E_DLL1             GetCenterY              ( );
  E_DLL0 FLOAT32 E_DLL1             GetAngle                ( );
  E_DLL0 FLOAT32 E_DLL1             GetScale                ( );
  E_DLL0 FLOAT32 E_DLL1             GetDirect               ( );
                                                      
  // Coefficients adjustment                          
  E_DLL0 void E_DLL1                ValidateFrame           ( EFrame* pMother);
  E_DLL0 void E_DLL1                InvalidateFrame         ( );
                                                      
  // Coordinate transforms                            
  E_DLL0 EPoint E_DLL1              LocalToGlobal           ( EPoint LPoint);
  E_DLL0 EFrame E_DLL1              LocalToGlobal           ( EFrame LFrame);
  E_DLL0 ELine E_DLL1               LocalToGlobal           ( ELine Line);
  E_DLL0 ECircle E_DLL1             LocalToGlobal           ( ECircle Circle);
                                                      
  E_DLL0 EPoint E_DLL1              GlobalToLocal           ( EPoint GPoint);
  E_DLL0 EFrame E_DLL1              GlobalToLocal           ( EFrame GFrame);
                                                      
  // Transform fitting                                
  E_DLL0 void E_DLL1                ResetFit                ( );
  E_DLL0 void E_DLL1                AccumulateFit           ( EPoint World, EPoint Local);
  E_DLL0 void E_DLL1                Fit                     ( UINT32 un32CalibrationModes);
                                                      
  // Serialization                                    
  virtual E_DLL0 void E_DLL1        Serialize               ( ESerializer* serializer, UINT32 un32FileVersion);
  virtual E_DLL0 void E_DLL1        Serialize               ( FILE*  pFile, BOOL bWrite, UINT32 un32FileVersion);
 
// Debug DumpToStream method
// ---------------------------------------------------------------------------
public :
//  virtual E_DLL0 void E_DLL1        DumpToStream            ( std::ostream& strm , int indent = 0 ) const;

protected:
  // Angle in radians
  FLOAT32                           m_f32Angle;
                                    
  // Scale                          
  FLOAT32                           m_f32Scale;
                                    
  // Ratio ( obsolete)              
  static FLOAT32                    m_f32Ratio;

  // Local to world linear coefficients
  FLOAT32                           m_f32Xx;
  FLOAT32                           m_f32Xy;
  FLOAT32                           m_f32Yx;
  FLOAT32                           m_f32Yy;
  
  // World to local linear coefficients
  FLOAT32                           m_f32xX;
  FLOAT32                           m_f32xY;
  FLOAT32                           m_f32yX;
  FLOAT32                           m_f32yY;
                                    
  // Affine coefficients            
  FLOAT32                           m_f32X;
  FLOAT32                           m_f32Y;
                                    
  void                              InverseTransform( );
  
  // Affine coefficients management
  EFrame*                           (*m_pGetFrame) (EFrame* owner, EFrame* pMother);
  static EFrame*                    StaticGetInvalidFrame(EFrame* owner, EFrame* pMother);
  static EFrame*                    StaticGetValidFrame(EFrame* owner, EFrame* pMother);
  EFrame*                           GetFrame                ( EFrame* pMother) {
                                                              return (*m_pGetFrame)(this, pMother);
                                                            }
  EFrame*                           GetValidFrame           ( EFrame* pMother);
  EFrame*                           GetInvalidFrame         ( EFrame* pMother);
  BOOL                              ValidFrame              ( );
  
  friend class EPoint;
  friend class EShape;
  friend class EPointGauge;
  friend class ECircleGauge;
};

////////////////////////////////////////////////////////////////////////////////////////////////////
// Line primitive
class E_DLL1 ELine: public EFrame
{
  // Wrapping members
public:
  int handle_;
  FinalizeCallback callback_;

public:
  // Constructors
  E_DLL0 CONSTRUCTOR E_DLL1         ELine                   ( );
  E_DLL0 CONSTRUCTOR E_DLL1         ELine                   ( EPoint Center,
                                                              FLOAT32 f32Length, FLOAT32 f32Angle = 0);
  E_DLL0 CONSTRUCTOR E_DLL1         ELine                   ( EPoint Org, EPoint End);

public :
  E_DLL0 CONSTRUCTOR E_DLL1         ELine                   ( const ELine& other);
  E_DLL0 ELine& E_DLL1              operator=               ( const ELine& other);

  virtual E_DLL0 EPoint* E_DLL1     CreatePointClone        ( ) const;
  E_DLL0 ELine* E_DLL1              CopyTo                  ( ELine* dest ) const;

protected :
  E_DLL0 ELine* E_DLL1              InternalCopyTo          ( ELine* dest, BOOL isACtor) const;

public :
  // Updates                                          
  E_DLL0 void E_DLL1                Set                     ( EPoint Center,
                                                              FLOAT32 f32Length, FLOAT32 f32Angle = 0);
  E_DLL0 void E_DLL1                Set                     ( EPoint Org, EPoint End);
  E_DLL0 void E_DLL1                SetLength               ( FLOAT32 f32Length);
                                                      
  // Queries                                          
  E_DLL0 EPoint E_DLL1              GetOrg                  ( );
  E_DLL0 EPoint E_DLL1              GetEnd                  ( );
  E_DLL0 FLOAT32 E_DLL1             GetLength               ( );
  E_DLL0 FLOAT32 E_DLL1             GetLength               ( ) const;
  E_DLL0 EPoint E_DLL1              GetPoint                ( FLOAT32 f32Fraction);
                                                      
  // Serialization                                    
  virtual E_DLL0 void E_DLL1        Serialize               ( FILE*  pFile, BOOL bWrite, UINT32 un32FileVersion);
  virtual E_DLL0 void E_DLL1        Serialize               ( ESerializer* serializer, UINT32 un32FileVersion);

// Debug DumpToStream method
// ---------------------------------------------------------------------------
public :
//  virtual E_DLL0 void E_DLL1        DumpToStream            ( std::ostream& strm , int indent = 0 ) const;

protected:
  // Length
  FLOAT32                           m_f32HalfLength;
  
  friend class ETransition;
  friend class ELineGauge;
  friend class ECircleGauge;
};

////////////////////////////////////////////////////////////////////////////////////////////////////
// Rectangle primitive
class E_DLL1 ERectangle: public EFrame
{
  // Wrapping members
public:
  int handle_;
  FinalizeCallback callback_;

public:
  // Constructors
  E_DLL0 CONSTRUCTOR E_DLL1           ERectangle            ( );
  E_DLL0 CONSTRUCTOR E_DLL1           ERectangle            ( EPoint Center,
                                                              FLOAT32 f32SizeX, FLOAT32 f32SizeY,
                                                              FLOAT32 f32Angle = 0);
  E_DLL0 CONSTRUCTOR E_DLL1           ERectangle            ( EPoint Org, EPoint End);
  E_DLL0 CONSTRUCTOR E_DLL1           ERectangle            ( EPoint Org, EPoint Mid, EPoint End);

public :
  E_DLL0 CONSTRUCTOR E_DLL1           ERectangle            ( const ERectangle& other);
  E_DLL0 ERectangle& E_DLL1           operator=             ( const ERectangle& other);

  virtual E_DLL0 EPoint* E_DLL1       CreatePointClone      ( ) const;
  E_DLL0 ERectangle* E_DLL1           CopyTo                ( ERectangle* dest ) const;

protected :
  E_DLL0 ERectangle* E_DLL1           InternalCopyTo        ( ERectangle*, BOOL ) const;

public :
  // Updates                                          
  E_DLL0 void E_DLL1                  Set                   ( EPoint Center,
                                                      FLOAT32 f32SizeX, FLOAT32 f32SizeY,
                                                      FLOAT32 f32Angle = 0);
  E_DLL0 void E_DLL1                  Set                   ( EPoint Org, EPoint End);
  E_DLL0 void E_DLL1                  Set                   ( EPoint Org, EPoint Mid, EPoint End);
  E_DLL0 void E_DLL1                  SetSize               ( FLOAT32 f32SizeX, FLOAT32 f32SizeY);
                                                      
  // Queries                                          
  E_DLL0 FLOAT32 E_DLL1               GetSizeX              ( );
  E_DLL0 FLOAT32 E_DLL1               GetSizeX              ( ) const;
  E_DLL0 FLOAT32 E_DLL1               GetSizeY              ( );
  E_DLL0 FLOAT32 E_DLL1               GetSizeY              ( ) const;
  E_DLL0 EPoint E_DLL1                GetPoint              ( FLOAT32 f32FractionX, FLOAT32 f32FractionY);
                                                      
  E_DLL0 void E_DLL1                  GetMidEdges           ( EPoint& Px, EPoint& PX, EPoint& Py, EPoint& PY);
  E_DLL0 void E_DLL1                  GetCorners            ( EPoint& Pxy, EPoint& PXy, EPoint& PxY, EPoint& PXY);
  E_DLL0 void E_DLL1                  GetEdges              ( ELine& Ex, ELine& EX, ELine& Ey, ELine& EY);
 
// Debug DumpToStream method
// ---------------------------------------------------------------------------
public :
//  virtual E_DLL0 void E_DLL1          DumpToStream          ( std::ostream& strm , int indent = 0 ) const;

protected:
  // Size
  FLOAT32                             m_f32HalfSizeX;
  FLOAT32                             m_f32HalfSizeY;

  // Serialization
  virtual E_DLL0 void E_DLL1          Serialize             ( FILE*  pFile, BOOL bWrite, UINT32 un32FileVersion);
  virtual E_DLL0 void E_DLL1          Serialize             ( ESerializer* serializer, UINT32 un32FileVersion);
};

////////////////////////////////////////////////////////////////////////////////////////////////////
// Circle primitive
class E_DLL1 ECircle: public EFrame
{
  // Wrapping members
public:
  int handle_;
  FinalizeCallback callback_;

public:
  // Constructors
  E_DLL0 CONSTRUCTOR E_DLL1         ECircle                 ( );
  E_DLL0 CONSTRUCTOR E_DLL1         ECircle                 ( EPoint Center, FLOAT32 f32Diameter, FLOAT32 f32OrgAngle = 0, BOOL bDirect = TRUE);
  E_DLL0 CONSTRUCTOR E_DLL1         ECircle                 ( EPoint Center, EPoint Org, BOOL bDirect = TRUE);
  E_DLL0 CONSTRUCTOR E_DLL1         ECircle                 ( EPoint Center, FLOAT32 f32Diameter, FLOAT32 f32OrgAngle, FLOAT32 f32Amplitude);
  E_DLL0 CONSTRUCTOR E_DLL1         ECircle                 ( EPoint Org, EPoint Mid, EPoint End, BOOL bFull = TRUE);
      
public :
  E_DLL0 CONSTRUCTOR E_DLL1         ECircle                 ( const ECircle& circle);
  E_DLL0 ECircle& E_DLL1            operator=               ( const ECircle& circle);

  virtual E_DLL0 EPoint* E_DLL1     CreatePointClone        ( ) const;
  E_DLL0 ECircle* E_DLL1            CopyTo                  ( ECircle* dest ) const;

protected :
  E_DLL0 ECircle* E_DLL1            InternalCopyTo          ( ECircle*, BOOL ) const;

public :
  // Updates                                          
  E_DLL0 void E_DLL1                Set                     ( EPoint Center, FLOAT32 f32Diameter, FLOAT32 f32OrgAngle = 0, BOOL bDirect = TRUE);
  E_DLL0 void E_DLL1                Set                     ( EPoint Center, FLOAT32 f32Diameter, FLOAT32 f32OrgAngle, FLOAT32 f32Amplitude);
  E_DLL0 void E_DLL1                Set                     ( EPoint Center, EPoint Org, BOOL bDirect = TRUE);
  E_DLL0 void E_DLL1                Set                     ( EPoint Org, EPoint Mid, EPoint End, BOOL bFull = TRUE);
  E_DLL0 void E_DLL1                SetRadius               ( FLOAT32 f32Radius);
  E_DLL0 void E_DLL1                SetDiameter             ( FLOAT32 f32Diameter);
                                                      
  // Queries                                          
  E_DLL0 FLOAT32 E_DLL1             GetRadius               ( );
  E_DLL0 FLOAT32 E_DLL1             GetDiameter             ( );
  E_DLL0 FLOAT32 E_DLL1             GetArcLength            ( );
  E_DLL0 FLOAT32 E_DLL1             GetArcLength            ( ) const;
  E_DLL0 FLOAT32 E_DLL1             GetOrgAngle             ( );
  E_DLL0 FLOAT32 E_DLL1             GetApexAngle            ( );
  E_DLL0 FLOAT32 E_DLL1             GetEndAngle             ( );
  E_DLL0 FLOAT32 E_DLL1             GetAmplitude            ( );
  E_DLL0 EPoint E_DLL1              GetOrg                  ( );
  E_DLL0 EPoint E_DLL1              GetApex                 ( );
  E_DLL0 EPoint E_DLL1              GetEnd                  ( );
  E_DLL0 EPoint E_DLL1              GetPoint                ( FLOAT32 f32Fraction);
  E_DLL0 BOOL E_DLL1                GetFull                 ( );
  E_DLL0 BOOL E_DLL1                GetDirect               ( );
  E_DLL0 void E_DLL1                SetAmplitude            (FLOAT32 ampl) {m_f32Amplitude = ampl;}
                                                      
  // Distances                                        
  E_DLL0 FLOAT32 E_DLL1             Distance                ( ECircle& Circle);
 
// Debug DumpToStream method
// ---------------------------------------------------------------------------
public :
//  virtual E_DLL0 void E_DLL1        DumpToStream            ( std::ostream& strm , int indent = 0 ) const;

protected:
  // Radius
  FLOAT32                           m_f32Radius;
  
  // Limiting angles in radians. When full circle, absolute amplitude is 2 pi
  FLOAT32                           m_f32Amplitude;

  // Serialization
  virtual E_DLL0 void E_DLL1        Serialize               ( FILE*  pFile, BOOL bWrite, UINT32 un32FileVersion);
  virtual E_DLL0 void E_DLL1        Serialize               ( ESerializer* serializer, UINT32 un32FileVersion);

  friend class ECircleGauge;
};

////////////////////////////////////////////////////////////////////////////////////////////////////
// Wedge primitive
class E_DLL1 EWedge: public EFrame
{
  // Wrapping members
public:
  int handle_;
  FinalizeCallback callback_;

public:
  // Constructors
  E_DLL0 CONSTRUCTOR E_DLL1         EWedge                  ( );
  E_DLL0 CONSTRUCTOR E_DLL1         EWedge                  ( EPoint Center,
                                                              FLOAT32 f32Diameter, FLOAT32 f32Breadth = 0,
                                                              FLOAT32 f32OrgAngle = 0, BOOL bDirect = TRUE);
  E_DLL0 CONSTRUCTOR E_DLL1         EWedge                  ( EPoint Center, EPoint Org,
                                                              FLOAT32 f32Breadth = 0, BOOL bDirect = TRUE);
  E_DLL0 CONSTRUCTOR E_DLL1         EWedge                  ( EPoint Center, FLOAT32 f32Diameter,
                                                              FLOAT32 f32Breadth, FLOAT32 f32OrgAngle,
                                                              FLOAT32 f32Amplitude);
  E_DLL0 CONSTRUCTOR E_DLL1         EWedge                  ( EPoint Org, EPoint Mid, EPoint End,
                                                              FLOAT32 f32Breadth = 0, BOOL bFullCircle = TRUE);
public :
  E_DLL0 CONSTRUCTOR E_DLL1         EWedge                  ( const EWedge& other);
  E_DLL0 EWedge& E_DLL1             operator=               ( const EWedge& other);

  virtual E_DLL0 EPoint* E_DLL1     CreatePointClone        ( ) const;
  E_DLL0 EWedge* E_DLL1             CopyTo                  ( EWedge* dest ) const;

protected :
  E_DLL0 EWedge* E_DLL1             InternalCopyTo          ( EWedge*, BOOL ) const;

public :
  // Updates              
                          
  // Full wedge           
  E_DLL0 void E_DLL1                Set                     ( EPoint Center,
                                                              FLOAT32 f32Diameter, FLOAT32 f32Breadth = 0,
                                                              FLOAT32 f32OrgAngle = 0, BOOL bDirect = TRUE);
  E_DLL0 void E_DLL1                Set                     ( EPoint Center, FLOAT32 f32Diameter,
                                                              FLOAT32 f32Breadth, FLOAT32 f32OrgAngle,
                                                              FLOAT32 f32Amplitude);
  E_DLL0 void E_DLL1                Set                     ( EPoint Center, EPoint Org, FLOAT32 f32Breadth = 0,
                                                              BOOL bDirect = TRUE);
  E_DLL0 void E_DLL1                Set                     ( EPoint Org, EPoint Mid, EPoint End,
                                                              FLOAT32 f32Breadth = 0, BOOL bFull = TRUE);
                                                      
  E_DLL0 void E_DLL1                SetAmplitude            ( FLOAT32 ampl);
  E_DLL0 void E_DLL1                SetRadii                ( FLOAT32 f32Radius, FLOAT32 f32Breadth = 0);
  E_DLL0 void E_DLL1                SetDiameters            ( FLOAT32 f32Diameter, FLOAT32 f32Breadth = 0);
                          
  // Queries              
  E_DLL0 FLOAT32 E_DLL1             GetInnerDiameter        ( );
  E_DLL0 FLOAT32 E_DLL1             GetOuterDiameter        ( );
  E_DLL0 FLOAT32 E_DLL1             GetInnerRadius          ( );
  E_DLL0 FLOAT32 E_DLL1             GetOuterRadius          ( );
  E_DLL0 FLOAT32 E_DLL1             GetBreadth              ( );
  E_DLL0 FLOAT32 E_DLL1             GetBreadth              ( ) const;
  E_DLL0 FLOAT32 E_DLL1             GetInnerArcLength       ( );
  E_DLL0 FLOAT32 E_DLL1             GetOuterArcLength       ( );
  E_DLL0 FLOAT32 E_DLL1             GetOrgAngle             ( );
  E_DLL0 FLOAT32 E_DLL1             GetApexAngle            ( );
  E_DLL0 FLOAT32 E_DLL1             GetEndAngle             ( );
  E_DLL0 FLOAT32 E_DLL1             GetAmplitude            ( );
  E_DLL0 EPoint E_DLL1              GetInnerOrg             ( );
  E_DLL0 EPoint E_DLL1              GetInnerApex            ( );
  E_DLL0 EPoint E_DLL1              GetInnerEnd             ( );
  E_DLL0 EPoint E_DLL1              GetOuterOrg             ( );
  E_DLL0 EPoint E_DLL1              GetOuterApex            ( );
  E_DLL0 EPoint E_DLL1              GetOuterEnd             ( );
  E_DLL0 EPoint E_DLL1              GetInnerPoint           ( FLOAT32 f32Fraction);
  E_DLL0 EPoint E_DLL1              GetOuterPoint           ( FLOAT32 f32Fraction);
  E_DLL0 EPoint E_DLL1              GetPoint                ( FLOAT32 f32BreadthFraction, FLOAT32 f32AngleFraction);
  E_DLL0 BOOL E_DLL1                GetFullBreadth          ( );
  E_DLL0 BOOL E_DLL1                GetFullBreadth          ( ) const;
  E_DLL0 BOOL E_DLL1                GetFullCircle           ( );
  E_DLL0 BOOL E_DLL1                GetFullCircle           ( ) const;
  E_DLL0 BOOL E_DLL1                GetDirect               ( );
                                                      
  E_DLL0 void E_DLL1                GetMidEdges             ( EPoint& Pa, EPoint& PA, EPoint& Pr, EPoint& PR);
  E_DLL0 void E_DLL1                GetCorners              ( EPoint& Par, EPoint& PAr, EPoint& PaR, EPoint& PAR);
  E_DLL0 void E_DLL1                GetEdges                ( ELine& Ea, ELine& EA, ECircle& Er, ECircle& ER);
 
// Debug DumpToStream method
// ---------------------------------------------------------------------------
public :
//  virtual E_DLL0 void E_DLL1        DumpToStream            ( std::ostream& strm , int indent = 0 ) const;

protected:
  // Radii
  FLOAT32                           m_f32CoRadius;
  FLOAT32                           m_f32Radius;
  
  // Limiting angles in radians. When full wedge, absolute amplitude is 2 pi
  FLOAT32                           m_f32Amplitude;

  // Serialization
  virtual E_DLL0 void E_DLL1        Serialize               ( FILE*  pFile, BOOL bWrite, UINT32 un32FileVersion);
  virtual E_DLL0 void E_DLL1        Serialize               ( ESerializer* serializer, UINT32 un32FileVersion);
};

// Forward declarations
class EWorldShape;
class EFrameShape;
class ELineShape;
class ECircleShape;
class EWedgeShape;
class ERectangleShape;
class EWorldShape;
namespace Euresys { namespace eVision { class ShapeChecker; } }

// Base shape object

class E_DLL1 EShape
{
  // Wrapping members
public:
  int handle_;
  FinalizeCallback callback_;

  friend class Euresys::eVision::ShapeChecker;

public: 
  E_DLL0 CONSTRUCTOR E_DLL1         EShape                  ( );
  virtual E_DLL0 DESTRUCTOR E_DLL1  ~EShape                 ( );

  // This class is abstract thus we do not need a copy constructor
  // and an assignment operators since they are never virtual.

private :
  E_DLL0 void E_DLL1                InitEmpty               ( );
  E_DLL0 void E_DLL1                MakeEmpty               ( );
protected : 
  E_DLL0 EShape* E_DLL1             InternalCopyTo          ( EShape*, BOOL , BOOL ) const;
public :
  // note : this virtual constructor pattern does not use a covariant return type because
  // this is not supported by Visual C++ 6.0
  virtual E_DLL0 EShape* E_DLL1     CreateShapeClone        ( BOOL bRecursive ) const = 0;
  E_DLL0 EShape* E_DLL1             CopyTo                  ( EShape* dest, BOOL bRecursive) const;

public :
  virtual E_DLL0 enum INS_SHAPE_TYPES E_DLL1  GetType       ( ) = 0;
  
  // Name
  const E_DLL0 char* E_DLL1         GetName                 ( );
  const E_DLL0 UNICHAR* E_DLL1      GetNameUnicode          ( );
  E_DLL0 void E_DLL1                SetName                 ( const char* pszName);
  E_DLL0 void E_DLL1                SetName                 ( const UNICHAR* pszName);
  E_DLL0 EShape* E_DLL1             GetShapeNamed           ( const char* pszName);
  E_DLL0 EShape* E_DLL1             GetShapeNamed           ( const UNICHAR* pszName);
  
  // Behavior
  E_DLL0 BOOL E_DLL1                GetVisible              ( ) { return ( m_un32Behavior & INS_VISIBLE) != 0; }
  E_DLL0 void E_DLL1                SetVisible              ( BOOL bVisible, BOOL bDaughters = FALSE);
  E_DLL0 BOOL E_DLL1                GetSelected             ( ) 
  { 
    return ( m_un32Behavior & INS_SELECTED) != 0; 
  }
  E_DLL0 void E_DLL1                SetSelected             ( BOOL bSelected, BOOL bDaughters = FALSE);
  E_DLL0 BOOL E_DLL1                GetSelectable           ( ) 
  { 
    return ( m_un32Behavior & INS_SELECTABLE) != 0; 
  }
  E_DLL0 void E_DLL1                SetSelectable           ( BOOL bSelectable, BOOL bDaughters = FALSE);
  E_DLL0 BOOL E_DLL1                GetDragable             ( ) 
  { 
    return ( m_un32Behavior & INS_DRAGABLE) != 0; 
  }
  E_DLL0 void E_DLL1                SetDragable             ( BOOL bDragable, BOOL bDaughters = FALSE);
  E_DLL0 BOOL E_DLL1                GetResizable            ( ) 
  { 
    return ( m_un32Behavior & INS_RESIZABLE) != 0; 
  }
  E_DLL0 void E_DLL1                SetResizable            ( BOOL bResizable, BOOL bDaughters = FALSE);
  E_DLL0 BOOL E_DLL1                GetRotatable            ( ) 
  { 
    return ( m_un32Behavior & INS_ROTATABLE) != 0; 
  }
  E_DLL0 void E_DLL1                SetRotatable            ( BOOL bRotatable, BOOL bDaughters = FALSE);
  E_DLL0 BOOL E_DLL1                GetActive               ( ) 
  { 
    return ( m_un32Behavior & INS_ACTIVE) != 0; 
  }
  virtual E_DLL0 void E_DLL1        SetActive               ( BOOL bActive, BOOL bDaughters = FALSE);
  E_DLL0 BOOL E_DLL1                GetLabeled              ( ) 
  { 
    return ( m_un32Behavior & INS_LABELED) != 0; 
  }
  E_DLL0 void E_DLL1                SetLabeled              ( BOOL bLabeled, BOOL bDaughters = FALSE);
  E_DLL0 BOOL E_DLL1                GetAutoArrange          ( ) 
  { 
    return ( m_un32Behavior & INS_AUTO_ARRANGE) != 0; 
  }
  E_DLL0 void E_DLL1                SetAutoArrange          ( BOOL bAutoArrange, BOOL bDaughters = FALSE);
  E_DLL0 BOOL E_DLL1                GetFound                ( ) 
  { 
    return ( m_un32Behavior & INS_FOUND) != 0; 
  }
  virtual E_DLL0 void E_DLL1        SetFound                ( BOOL bFound, BOOL bDaughters = FALSE);
  E_DLL0 BOOL E_DLL1                GetActualShape          ( ) 
  { 
    return ( m_un32Behavior & INS_ACTUAL_SHAPE) != 0; 
  }
  E_DLL0 void E_DLL1                SetActualShape          ( BOOL bActualShape, BOOL bDaughters = FALSE);
  E_DLL0 BOOL E_DLL1                GetInspected            ( ) 
  { 
    return ( m_un32Behavior & INS_INSPECTED) != 0; 
  }
  E_DLL0 void E_DLL1                SetInspected            ( BOOL bFound, BOOL bDaughters = FALSE);
  E_DLL0 BOOL E_DLL1                GetPassed               ( ) 
  { 
    return ( m_un32Behavior & INS_PASSED) != 0; 
  }
  E_DLL0 void E_DLL1                SetPassed               ( BOOL bFound, BOOL bDaughters = FALSE);
  E_DLL0 BOOL E_DLL1                GetQuickDraw            ( ) 
  { 
    return ( m_un32Behavior & INS_QUICK_DRAW) != 0; 
  }
  E_DLL0 void E_DLL1                SetQuickDraw            ( BOOL bFound, BOOL bDaughters = FALSE);
  E_DLL0 BOOL E_DLL1                GetOptionalDraw         ( ) 
  { 
    return ( m_un32Behavior & INS_OPTIONAL_DRAW) != 0; 
  }
  E_DLL0 void E_DLL1                SetOptionalDraw         ( BOOL bFound, BOOL bDaughters = FALSE);
  E_DLL0 BOOL E_DLL1                GetUserFlag             ( ) 
  { 
    return ( m_un32Behavior & INS_USER_FLAG) != 0; 
  }
  E_DLL0 void E_DLL1                SetUserFlag             ( BOOL bUserFlag, BOOL bDaughters = FALSE);

  // Reserved
  E_DLL0 BOOL E_DLL1                GetIndexed              ( ) const { return ( m_un32Behavior & INS_INDEXED) != 0; }
  E_DLL0 BOOL E_DLL1                Get2DArray              ( ) const { return ( m_un32Behavior & INS_2D_ARRAY) != 0; }
  E_DLL0 BOOL E_DLL1                GetAllocated            ( ) const { return ( m_un32Behavior & INS_ALLOCATED) != 0; }
  E_DLL0 void E_DLL1                SetAllocated            ( BOOL bAllocated, BOOL bDaughters = FALSE);
                              
  E_DLL0 void E_DLL1                EnableBehaviorFilter    ( enum INS_SHAPE_BEHAVIOR eBehavior, BOOL bValue = TRUE);
  E_DLL0 void E_DLL1                DisableBehaviorFilter   ( enum INS_SHAPE_BEHAVIOR eBehavior);
  E_DLL0 void E_DLL1                EnableTypeFilter        ( UINT32 un32Types);
  E_DLL0 void E_DLL1                DisableTypeFilter       ( );

  // Grouping update
  E_DLL0 void E_DLL1                Attach                  ( EShape* pMother);
  E_DLL0 void E_DLL1                Detach                  ( );
  E_DLL0 void E_DLL1                DetachDaughters         ( );
  E_DLL0 UINT32 E_DLL1              GetNumDaughters         ( );
  E_DLL0 UINT32 E_DLL1              GetMaxDaughters         ( );
  E_DLL0 EShape* E_DLL1             GetMother               ( ) { return m_pMother; }
  E_DLL0 EShape* E_DLL1             GetNextDaughter         ( UINT32& un32Index);
  E_DLL0 EShape* E_DLL1             GetDaughter             ( UINT32 un32DaughterIndex);
  
  E_DLL0 void E_DLL1                SetIndexed              ( UINT32 un32NumShapes);
  E_DLL0 void E_DLL1                AttachIndexed           ( EShape* pMother, UINT32 un32Index);
  E_DLL0 void E_DLL1                AttachIndexed           ( ERectangleShape* pMother,
                                                              UINT32 un32ColIndex, UINT32 un32RowIndex);
  E_DLL0 void E_DLL1                AttachIndexed           ( EWedgeShape* pMother,
                                                              UINT32 un32ColIndex, UINT32 un32RowIndex);
  E_DLL0 UINT32 E_DLL1              GetIndex                ( );
  
  static E_DLL0 BOOL E_DLL1         GetPreserveOrder        ( );
  static E_DLL0 void E_DLL1         SetPreserveOrder        ( BOOL bPreserveOrder);
  
  // World ancestor
  E_DLL0 EWorldShape* E_DLL1        GetWorldShape           ( );
  
  // Cloning
  E_DLL0 void E_DLL1                Clone                   ( EShape* pShape);
  E_DLL0 void E_DLL1                Clone                   ( EShape* pShape, UINT32 un32NumClones);
  E_DLL0 void E_DLL1                Clone                   ( ERectangleShape* pShape,
                                                              UINT32 un32NumCols, UINT32 un32NumRows,
                                                              BOOL bStaggered = FALSE);
  E_DLL0 void E_DLL1                Clone                   ( EWedgeShape* pShape,
                                                              UINT32 un32NumCols, UINT32 un32NumRows,
                                                              BOOL bStaggered = FALSE);
  
  // Geometric transforms
  E_DLL0 BOOL E_DLL1                IsWorld                 ( ) { return GetType( ) == INS_WORLD_SHAPE; }  
  E_DLL0 void E_DLL1                InvalidateWorld         ( );

  virtual E_DLL0 EFrame* E_DLL1     CastToFrame             ( ) = 0;
  E_DLL0 EFrame* E_DLL1             GetFrame                ( );
  E_DLL0 void E_DLL1                ValidateFrame           ( );
  E_DLL0 void E_DLL1                InvalidateFrame         ( );

  // Global rescaling
  virtual E_DLL0 void E_DLL1        Rescale                 ( FLOAT32 f32Factor, BOOL bDaughters = TRUE) = 0;
  
  // Point transforms
  E_DLL0 EPoint E_DLL1              LocalToWorld            ( EPoint LPoint);
  E_DLL0 ELine E_DLL1               LocalToWorld            ( ELine LLine);
  E_DLL0 ECircle E_DLL1             LocalToWorld            ( ECircle LCircle);
  E_DLL0 EPoint E_DLL1              WorldToLocal            ( EPoint WPoint);
  E_DLL0 EPoint E_DLL1              LocalToSensor           ( EPoint LPoint);
  E_DLL0 EPoint E_DLL1              SensorToLocal           ( EPoint SPoint);
  
  // Display transforms
  E_DLL0 void E_DLL1                LocalToDisplay          ( EPoint LPoint, INT32& n32IX, INT32& n32IY);
  E_DLL0 void E_DLL1                LocalToDisplay          ( ELine LLine, INT32& n32IX0, INT32& n32IY0,
                                                              INT32& n32IX1, INT32& n32IY1);
  E_DLL0 void E_DLL1                LocalToDisplay          ( ECircle LCircle, INT32& n32IX0, INT32& n32IY0,
                                                              INT32& n32IX1, INT32& n32IY1);
  
  E_DLL0 EPoint E_DLL1              DisplayToLocal          ( INT32 n32IX, INT32 n32IY);
  
  // Drawing
  virtual E_DLL0 void E_DLL1        Draw                    ( HDC hDC, enum INS_DRAWING_MODES eDrawingMode = INS_DRAW_NOMINAL, BOOL bDaughters = TRUE) = 0;
  virtual E_DLL0 void E_DLL1        Draw                    ( Euresys::DrawAdapter* drawAdapter, enum INS_DRAWING_MODES eDrawingMode = INS_DRAW_NOMINAL, BOOL bDaughters = TRUE) = 0;

  // Zooming and panning
  E_DLL0 FLOAT32 E_DLL1             GetZoomX                ( );
  E_DLL0 FLOAT32 E_DLL1             GetZoomY                ( );
  E_DLL0 FLOAT32 E_DLL1             GetPanX                 ( );
  E_DLL0 FLOAT32 E_DLL1             GetPanY                 ( );
  E_DLL0 void E_DLL1                SetZoom                 ( FLOAT32 f32ZoomX = 1, FLOAT32 f32ZoomY = 0);
  E_DLL0 void E_DLL1                SetPan                  ( FLOAT32 f32PanX = 0, FLOAT32 f32PanY = 0);
  
  // Handles detection
  virtual E_DLL0 BOOL E_DLL1        HitTest                 ( BOOL bDaughters = TRUE) = 0;
  E_DLL0 enum INS_HANDLES E_DLL1    GetHitHandle            ( );
  E_DLL0 EShape* E_DLL1             GetHitShape             ( );
  
  // Dragging
  E_DLL0 void E_DLL1                SetDraggingMode         ( enum INS_DRAGGING_MODES eDraggingMode,
                                                              BOOL bDaughters = FALSE);
  E_DLL0 enum INS_DRAGGING_MODES E_DLL1  GetDraggingMode    ( );
  
  E_DLL0 void E_DLL1                SetCursor               ( INT32 n32CursorX, INT32 n32CursorY);
  virtual E_DLL0 void E_DLL1        Drag                    ( INT32 n32CursorX, INT32 n32CursorY) = 0;
  
  // Neighboring
  virtual E_DLL0 void E_DLL1        Closest                 ( ) = 0;
  E_DLL0 EShape* E_DLL1             GetClosestShape         ( );
  
  // Box selection
  E_DLL0 void E_DLL1                Select                  ( INT32 n32OrgX, INT32 n32OrgY,
                                                              INT32 n32EndX, INT32 n32EndY,
                                                              BOOL bDaughters = TRUE);
  
  // Implicit processing
  virtual E_DLL0 void E_DLL1        Process                 ( EROIBW8* pSrc, BOOL bDaughters = TRUE);
  
  // Serialization
  E_DLL0 void E_DLL1                Save                    ( ESerializer* serializer, BOOL bDaughters = FALSE);
  E_DLL0 void E_DLL1                Load                    ( ESerializer* serializer, BOOL bDaughters = FALSE);
  E_DLL0 void E_DLL1                Save                    ( const char* pszPathName, BOOL bDaughters = FALSE);
  E_DLL0 void E_DLL1                Load                    ( const char* pszPathName, BOOL bDaughters = FALSE);
  E_DLL0 void E_DLL1                Save                    ( const UNICHAR* pszPathName, BOOL bDaughters = FALSE);
  E_DLL0 void E_DLL1                Load                    ( const UNICHAR* pszPathName, BOOL bDaughters = FALSE);
  
  // Dumping
  E_DLL0 void E_DLL1                Dump                    ( BOOL bDaughters = TRUE);

// Debug DumpToStream method
// ---------------------------------------------------------------------------
public :
//  virtual E_DLL0 void E_DLL1              DumpToStream            ( std::ostream& strm , int indent = 0 ) const;

protected:
  // +-----------------------------+
  // | protected methods           |
  // +-----------------------------+
  BOOL                                    FilteredIn              ( );
  void                                    Link                    ( EShape* pMother, UINT32 un32DaughterIndex = ~0);
  void                                    Unlink                  ( );
  // Private behavior
  UINT32                                  GetMaxIndex             ( ) const;

  // Cloning
  virtual EShape*                   New                     ( ) = 0;
  E_DLL0 EShape* E_DLL1             Copy                    ( EShape* pShape, BOOL bDaughters = TRUE);
  virtual void                      ArrangeDaughters        ( ) = 0; 
  
  // Serialization
  virtual UINT32                    GetSignature            ( ) = 0;
  virtual E_DLL0 void E_DLL1        Serialize               ( ESerializer* serializer, UINT32 un32FileVersion, BOOL bDaughters = TRUE);
  virtual E_DLL0 void E_DLL1        Serialize               ( FILE*  pFile, BOOL bWrite, UINT32 un32FileVersion, BOOL bDaughters = TRUE);

  // +-----------------------------+
  // | protected class data        |
  // +-----------------------------+
  static E_DLL0 BOOL E_DLL1               m_bDaughters;
  static E_DLL0 UINT32 E_DLL1             m_un32BehaviorFilterUse;
  static E_DLL0 UINT32 E_DLL1             m_un32BehaviorFilterValue;
  static E_DLL0 UINT32 E_DLL1             m_un32FilteredTypes;
  static INT32                            m_n32CursorX, m_n32CursorY;
  static E_DLL0 enum INS_HANDLES E_DLL1   m_eHitHandle;
  static E_DLL0 EShape* E_DLL1            m_pHitShape;
  // Neighboring
  static E_DLL0 EShape* E_DLL1            m_pClosestShape;
  static FLOAT32                          m_f32BestDistance;

  static E_DLL0 BOOL E_DLL1               m_bPreserveOrder;
  
  // +-----------------------------+
  // | protected instance data     |
  // +-----------------------------+
  char*                                   m_pszName;
  // Behavior flags
  UINT32                                  m_un32Behavior;
  // Dragging
  enum INS_DRAGGING_MODES                 m_eDraggingMode;
  // Grouping
  EShape*                                 m_pMother;
  UINT32                                  m_un32DaughterIndex;
  EShape**                                m_ppDaughter;
  UINT32                                  m_un32NumDaughters;
  UINT32                                  m_un32MaxDaughters;
  // World ancestor
  EWorldShape*                            m_pWorld;
};

inline UINT32 EShape::GetMaxIndex( ) const
{
  return GetIndexed( ) ? m_un32MaxDaughters : m_un32NumDaughters;
}

// stream operator for EShape
E_DLL0 std::ostream& E_DLL1  operator<<( std::ostream& stream, const EShape& shape);

////////////////////////////////////////////////////////////////////////////////////////////////////
// Frame interactive shape
class E_DLL1 EFrameShape: public EFrame, public EShape
{
  // Wrapping members
public:
  int handle_;
  FinalizeCallback callback_;

public:
  // Constructors
  E_DLL0 CONSTRUCTOR E_DLL1         EFrameShape             ( FLOAT32 f32CenterX = 0, FLOAT32 f32CenterY = 0, FLOAT32 f32Angle = 0, FLOAT32 f32Scale = 1, FLOAT32 f32SizeX = 100, FLOAT32 f32SizeY = 100, BOOL bWorld = FALSE);
  E_DLL0 DESTRUCTOR E_DLL1          ~EFrameShape            ( );
  
public :
  E_DLL0 CONSTRUCTOR E_DLL1         EFrameShape             ( const EFrameShape& other);
  E_DLL0 EFrameShape& E_DLL1        operator=               ( const EFrameShape& other);

  virtual E_DLL0 EShape* E_DLL1     CreateShapeClone        ( BOOL bRecursive ) const;
  E_DLL0 EFrameShape* E_DLL1        CopyTo                  ( EFrameShape* dest, BOOL bRecursive ) const;

protected :
  E_DLL0 EFrameShape* E_DLL1        InternalCopyTo          ( EFrameShape*, BOOL bRecursive, BOOL bIsACtor) const;

public :  
  E_DLL0 EShape* E_DLL1             New                     ( ) { return Copy( new EFrameShape( *this)); }
  
  // Typing
  E_DLL0 INS_SHAPE_TYPES E_DLL1     GetType                 ( );
  
  // Geometry
  E_DLL0 void E_DLL1                SetAxis                 ( EPoint Center, FLOAT32 f32Angle = 0, FLOAT32 f32Scale = 1, FLOAT32 f32SizeX = 100, FLOAT32 f32SizeY = 100);
  E_DLL0 void E_DLL1                SetCenter               ( EPoint Point);
  E_DLL0 void E_DLL1                SetCenter               ( FLOAT32 f32CenterX, FLOAT32 f32CenterY) { SetCenter( EPoint( f32CenterX, f32CenterY)); }
  
  // Queries
  E_DLL0 FLOAT32 E_DLL1             GetSizeX                ( ) { return m_f32SizeX; }
  E_DLL0 FLOAT32 E_DLL1             GetSizeY                ( ) { return m_f32SizeY; }
  
  // Updates
  E_DLL0 void E_DLL1                Set                     ( EPoint Center,
                                                              FLOAT32 f32Angle = 0, FLOAT32 f32Scale = 1) {
                                                                EFrame::Set( Center, f32Angle, f32Scale); EShape::InvalidateFrame( );
                                                              }
  E_DLL0 void E_DLL1                SetAngle                ( FLOAT32 f32Angle) {
                                                                EFrame::SetAngle( f32Angle); EShape::InvalidateFrame( );
                                                              }
  E_DLL0 void E_DLL1                SetScale                ( FLOAT32 f32Scale) {
                                                                EFrame::SetScale( f32Scale); EShape::InvalidateFrame( );
                                                              }
  E_DLL0 void E_DLL1                SetSize                 ( FLOAT32 f32SizeX, FLOAT32 f32SizeY = 0);
  E_DLL0 void E_DLL1                Rescale                 ( FLOAT32 f32Factor, BOOL bDaughters = TRUE);
  
  // Handles interaction
  E_DLL0 void E_DLL1                Closest                 ( );
  E_DLL0 BOOL E_DLL1                HitTest                 ( BOOL bDaughters = TRUE);
  E_DLL0 void E_DLL1                Drag                    ( INT32 n32CursorX, INT32 n32CursorY);
                                                      
  E_DLL0 void E_DLL1                Draw                    ( HDC hDC,
                                                              enum INS_DRAWING_MODES eDrawingMode = INS_DRAW_NOMINAL,
                                                              BOOL bDaughters = TRUE);
  E_DLL0 void E_DLL1                Draw                    ( Euresys::DrawAdapter* drawAdapter,
                                                              enum INS_DRAWING_MODES eDrawingMode = INS_DRAW_NOMINAL,
                                                              BOOL bDaughters = TRUE);
  E_DLL0 void E_DLL1                DrawCrossGrid           ( HDC hDC, 
                                                              FLOAT32 f32XMin = - 100, FLOAT32 f32XMax = + 100,
                                                              FLOAT32 f32YMin = - 100, FLOAT32 f32YMax = + 100,
                                                              UINT32 un32NumXIntervals = 2,
                                                              UINT32 un32NumYIntervals = 2);
  E_DLL0 void E_DLL1                DrawCrossGrid           ( Euresys::DrawAdapter* drawAdapter, 
                                                              FLOAT32 f32XMin = - 100, FLOAT32 f32XMax = + 100,
                                                              FLOAT32 f32YMin = - 100, FLOAT32 f32YMax = + 100,
                                                              UINT32 un32NumXIntervals = 2,
                                                              UINT32 un32NumYIntervals = 2);
  
  // Geometry
  E_DLL0 EFrame* E_DLL1             CastToFrame             ( ) { return this; }
  
  // Labeling
  static E_DLL0 void E_DLL1         SetFormat               ( char* pszFormat);
  static E_DLL0 char* E_DLL1        GetFormat               ( );
 
// Debug DumpToStream method
// ---------------------------------------------------------------------------
public :
//  virtual E_DLL0 void E_DLL1        DumpToStream            ( std::ostream& strm , int indent = 0 ) const;

protected:
  // Axes length
  FLOAT32                           m_f32SizeX;
  FLOAT32                           m_f32SizeY;
  
  // Labeling
  static char*                      m_pszFormat;
  
  // Reference counting
  static UINT32                     m_un32ReferenceCount;
  
  void                              ArrangeDaughters        ( ) {}

  // Serialization
  E_DLL0 UINT32 E_DLL1              GetSignature            ( );
  virtual E_DLL0 void E_DLL1        Serialize               ( FILE*  pFile, BOOL bWrite, UINT32 un32FileVersion, BOOL bDaughters = TRUE);
  virtual E_DLL0 void E_DLL1        Serialize               ( ESerializer* serializer, UINT32 un32FileVersion, BOOL bDaughters = TRUE);
};

// stream operator for EFrameShape
E_DLL0 std::ostream& E_DLL1  operator<<( std::ostream& stream, const EFrameShape& frameShape);

////////////////////////////////////////////////////////////////////////////////////////////////////
// Point interactive shape
class E_DLL1 EPointShape: public EFrame, public EShape
{
  // Wrapping members
public:
  int handle_;
  FinalizeCallback callback_;

public:
  // Constructors
  E_DLL0 CONSTRUCTOR E_DLL1         EPointShape             ( FLOAT32 f32CenterX = 0, FLOAT32 f32CenterY = 0);
  
  E_DLL0 DESTRUCTOR E_DLL1          ~EPointShape            ( );
  
public :
  E_DLL0 CONSTRUCTOR E_DLL1         EPointShape             ( const EPointShape& other);
  E_DLL0 EPointShape& E_DLL1        operator=               ( const EPointShape& other);

  virtual E_DLL0 EShape* E_DLL1     CreateShapeClone        ( BOOL bRecursive ) const;
  E_DLL0 EPointShape* E_DLL1        CopyTo                  ( EPointShape* dest, BOOL bRecursive ) const;

protected :
  E_DLL0 EPointShape* E_DLL1        InternalCopyTo          ( EPointShape*, BOOL, BOOL ) const;

public :  
  E_DLL0 EShape* E_DLL1             New                     ( ) { return Copy( new EPointShape( *this)); }
  
  // Typing
  E_DLL0 INS_SHAPE_TYPES E_DLL1     GetType                 ( );
  
  // Drawing
  E_DLL0 void E_DLL1                Draw                    ( HDC hDC,
                                                              enum INS_DRAWING_MODES eDrawingMode = INS_DRAW_NOMINAL,
                                                              BOOL bDaughters = TRUE);
  E_DLL0 void E_DLL1                Draw                    ( Euresys::DrawAdapter* drawAdapter,
                                                              enum INS_DRAWING_MODES eDrawingMode = INS_DRAW_NOMINAL,
                                                              BOOL bDaughters = TRUE);
  
  // Queries
  
  // Updates
  virtual E_DLL0 void E_DLL1        SetCenter               ( FLOAT32 f32CenterX, FLOAT32 f32CenterY);
  virtual E_DLL0 void E_DLL1        SetCenter               ( EPoint Point);
  E_DLL0 void E_DLL1                Rescale                 ( FLOAT32 f32Factor, BOOL bDaughters = TRUE);
  
  // Dragging
  E_DLL0 void E_DLL1                Closest                 ( );
  E_DLL0 BOOL E_DLL1                HitTest                 ( BOOL bDaughters = TRUE);
  E_DLL0 void E_DLL1                Drag                    ( INT32 n32CursorX, INT32 n32CursorY);
  
  // Geometry
  E_DLL0 EFrame* E_DLL1             CastToFrame             ( ) { return this; }
  
  // Labeling
  static E_DLL0 void E_DLL1         SetFormat               ( char* pszFormat);
  static E_DLL0 char* E_DLL1        GetFormat               ( );
 
// Debug DumpToStream method
// ---------------------------------------------------------------------------
public :
//  virtual E_DLL0 void E_DLL1        DumpToStream            ( std::ostream& strm , int indent = 0 ) const;

protected:
  // Labeling
  static char*                      m_pszFormat;
  
  // Reference counting
  static UINT32                     m_un32ReferenceCount;
  
  void                              ArrangeDaughters        ( ) {}

  // Serialization
  E_DLL0 UINT32 E_DLL1              GetSignature            ( );
  virtual E_DLL0 void E_DLL1        Serialize               ( ESerializer* serializer, UINT32 un32FileVersion, BOOL bDaughters = TRUE);
  virtual E_DLL0 void E_DLL1        Serialize               ( FILE*  pFile, BOOL bWrite, UINT32 un32FileVersion, BOOL bDaughters = TRUE);
};

// stream operator for EPointShape
E_DLL0 std::ostream& E_DLL1  operator<<( std::ostream& stream, const EPointShape& pointShape);

////////////////////////////////////////////////////////////////////////////////////////////////////
// Line interactive shape
class E_DLL1 ELineShape: public ELine, public EShape
{
  // Wrapping members
public:
  int handle_;
  FinalizeCallback callback_;

public:
  // Constructors
  E_DLL0 CONSTRUCTOR E_DLL1         ELineShape              ( FLOAT32 f32CenterX = 0, FLOAT32 f32CenterY = 0,
                                                              FLOAT32 f32Length = 100, FLOAT32 f32Angle = 0);
  
  E_DLL0 DESTRUCTOR E_DLL1          ~ELineShape             ( );
  
public :
  E_DLL0 CONSTRUCTOR E_DLL1         ELineShape              ( const ELineShape& other);
  E_DLL0 ELineShape& E_DLL1         operator=               ( const ELineShape& other);

  virtual E_DLL0 EShape* E_DLL1     CreateShapeClone        ( BOOL bRecursive ) const;
  E_DLL0 ELineShape* E_DLL1         CopyTo                  ( ELineShape* dest, BOOL bRecursive ) const;

protected :
  E_DLL0 ELineShape* E_DLL1         InternalCopyTo          ( ELineShape*, BOOL, BOOL ) const;

public :  
  E_DLL0 EShape* E_DLL1             New                     ( ) { return Copy( new ELineShape( *this)); }
  
  // Typing
  E_DLL0 INS_SHAPE_TYPES E_DLL1     GetType                 ( );
  
  // Grouping
  E_DLL0 void E_DLL1                ArrangeDaughters        ( ); 
  
  // Drawing
  E_DLL0 void E_DLL1                Draw                    ( HDC hDC,
                                                              enum INS_DRAWING_MODES eDrawingMode = INS_DRAW_NOMINAL,
                                                              BOOL bDaughters = TRUE);
  E_DLL0 void E_DLL1                Draw                    ( Euresys::DrawAdapter* drawAdapter,
                                                              enum INS_DRAWING_MODES eDrawingMode = INS_DRAW_NOMINAL,
                                                              BOOL bDaughters = TRUE);
  
  // Queries
  
  // Updates
  E_DLL0 void E_DLL1                Set                     ( EPoint Center, FLOAT32 f32Angle);
  E_DLL0 void E_DLL1                Set                     ( EPoint Center, FLOAT32 f32Length, FLOAT32 f32Angle) {
                                                              ELine::Set( Center, f32Length, f32Angle); EShape::InvalidateFrame( ); }
  E_DLL0 void E_DLL1                Set                     ( EPoint Org, EPoint End) {
                                                              ELine::Set( Org, End); EShape::InvalidateFrame( ); }
  E_DLL0 void E_DLL1                SetLength               ( FLOAT32 f32Length) {
                                                              ELine::SetLength( f32Length); EShape::InvalidateFrame( ); }
  E_DLL0 void E_DLL1                Rescale                 ( FLOAT32 f32Factor, BOOL bDaughters = TRUE);
                              
  E_DLL0 void E_DLL1                Closest                 ( );
  E_DLL0 BOOL E_DLL1                HitTest                 ( BOOL bDaughters = TRUE);
  E_DLL0 void E_DLL1                Drag                    ( INT32 n32CursorX, INT32 n32CursorY);
  
  // Geometry
  E_DLL0 EFrame* E_DLL1             CastToFrame             ( ) { return this; }
  
  // Labeling
  static E_DLL0 void E_DLL1         SetFormat               ( char* pszFormat);
  static E_DLL0 char* E_DLL1        GetFormat               ( );

// Debug DumpToStream method
// ---------------------------------------------------------------------------
public :
//  virtual E_DLL0 void E_DLL1        DumpToStream            ( std::ostream& strm , int indent = 0 ) const;

protected:
  // Labeling
  static char*                      m_pszFormat;
  
  // Reference counting
  static UINT32                     m_un32ReferenceCount;

  // Serialization
  E_DLL0 UINT32 E_DLL1              GetSignature            ( );
  virtual E_DLL0 void E_DLL1        Serialize               ( FILE*  pFile, BOOL bWrite, UINT32 un32FileVersion, BOOL bDaughters = TRUE);
  virtual E_DLL0 void E_DLL1        Serialize               ( ESerializer* serializer, UINT32 un32FileVersion, BOOL bDaughters = TRUE);
};

// stream operator for ELineShape
E_DLL0 std::ostream& E_DLL1  operator<<( std::ostream& stream, const ELineShape& lineShape);

////////////////////////////////////////////////////////////////////////////////////////////////////
// Rectangle interactive shape
class E_DLL1 ERectangleShape : public ERectangle, public EShape
{
  // Wrapping members
public:
  int handle_;
  FinalizeCallback callback_;

public:
  // Constructors
  E_DLL0 CONSTRUCTOR E_DLL1         ERectangleShape         ( FLOAT32 f32CenterX = 0, FLOAT32 f32CenterY = 0,
                                                              FLOAT32 f32SizeX = 100, FLOAT32 f32SizeY = 100,
                                                              FLOAT32 f32Angle = 0);
  E_DLL0 CONSTRUCTOR E_DLL1         ERectangleShape         ( EPoint Org, EPoint End);
  E_DLL0 CONSTRUCTOR E_DLL1         ERectangleShape         ( EPoint Org, EPoint Mid, EPoint End);
  
  E_DLL0 DESTRUCTOR E_DLL1          ~ERectangleShape        ( );
  
public :
  E_DLL0 CONSTRUCTOR E_DLL1         ERectangleShape         ( const ERectangleShape& other);
  E_DLL0 ERectangleShape& E_DLL1    operator=               ( const ERectangleShape& other);

  virtual E_DLL0 EShape* E_DLL1     CreateShapeClone        ( BOOL bRecursive ) const;
  E_DLL0 ERectangleShape* E_DLL1    CopyTo                  ( ERectangleShape* dest, BOOL bRecursive ) const;

protected :
  E_DLL0 ERectangleShape* E_DLL1    InternalCopyTo          ( ERectangleShape*, BOOL, BOOL ) const;

public :  
  E_DLL0 EShape* E_DLL1             New                     ( ) { return Copy( new ERectangleShape( *this)); }
  
  // Typing
  E_DLL0 INS_SHAPE_TYPES E_DLL1     GetType                 ( );
  
  // Drawing
  E_DLL0 void E_DLL1                Draw                    ( HDC hDC,
                                                              enum INS_DRAWING_MODES eDrawingMode = INS_DRAW_NOMINAL,
                                                              BOOL bDaughters = TRUE);
  E_DLL0 void E_DLL1                Draw                    ( Euresys::DrawAdapter* drawAdapter,
                                                              enum INS_DRAWING_MODES eDrawingMode = INS_DRAW_NOMINAL,
                                                              BOOL bDaughters = TRUE);
  
  // Queries
  E_DLL0 UINT32 E_DLL1              GetNumCols              ( );
  E_DLL0 UINT32 E_DLL1              GetNumRows              ( );
  
  E_DLL0 EShape* E_DLL1             GetDaughter             ( UINT32 un32Index) { return EShape::GetDaughter( un32Index); }
                                                      
  E_DLL0 UINT32 E_DLL1              GetRowIndex             ( EShape* pDaughter);
  E_DLL0 UINT32 E_DLL1              GetColIndex             ( EShape* pDaughter);
  E_DLL0 UINT32 E_DLL1              GetDaughterIndex        ( UINT32 un32ColIndex, UINT32 un32RowIndex);
  E_DLL0 EShape* E_DLL1             GetDaughter             ( UINT32 un32ColIndex, UINT32 un32RowIndex);
  E_DLL0 void E_DLL1                SetDaughter             ( UINT32 un32ColIndex, UINT32 un32RowIndex,
                                                              EShape* pDaughter = NULL);
  
  // Updates
  E_DLL0 void E_DLL1                Set                     ( EPoint Center, FLOAT32 f32SizeX, FLOAT32 f32SizeY,
                                                                FLOAT32 f32Angle = 0) {
                                                                ERectangle::Set( Center, f32SizeX, f32SizeY, f32Angle); EShape::InvalidateFrame( );
                                                              }
  E_DLL0 void E_DLL1                Set                     ( EPoint Org, EPoint End) {
                                                                ERectangle::Set( Org, End); EShape::InvalidateFrame( );
                                                              }
  E_DLL0 void E_DLL1                Set                     ( EPoint Org, EPoint Mid, EPoint End) {
                                                                ERectangle::Set( Org, Mid, End); EShape::InvalidateFrame( );
                                                              }
  E_DLL0 void E_DLL1                SetSize                 ( FLOAT32 f32SizeX, FLOAT32 f32SizeY) {
                                                                ERectangle::SetSize( f32SizeX, f32SizeY); EShape::InvalidateFrame( );
                                                              }
  E_DLL0 void E_DLL1                Rescale                 ( FLOAT32 f32Factor, BOOL bDaughters = TRUE);
  
  // Grouping
  E_DLL0 void E_DLL1                SetIndexed              ( UINT32 un32NumCols, UINT32 un32NumRows);
  E_DLL0 void E_DLL1                ArrangeDaughters        ( ); 
                              
  // Dragging                 
  E_DLL0 void E_DLL1                Closest                 ( );
  E_DLL0 BOOL E_DLL1                HitTest                 ( BOOL bDaughters = TRUE);
  E_DLL0 void E_DLL1                Drag                    ( INT32 n32CursorX, INT32 n32CursorY);
  
  // Geometry
  E_DLL0 EFrame* E_DLL1             CastToFrame             ( ) { return this; }
  E_DLL0 void E_DLL1                SetupMask               ( EROIBW8* pDst);
  E_DLL0 void E_DLL1                SetupMask               ( EROIC24* pDst);
                                                      
  // Labeling                                         
  static E_DLL0 void E_DLL1         SetFormat               ( char* pszFormat);
  static E_DLL0 char* E_DLL1        GetFormat               ( );

// Debug DumpToStream method
// ---------------------------------------------------------------------------
public :
//  virtual E_DLL0 void E_DLL1        DumpToStream            ( std::ostream& strm , int indent = 0 ) const;

protected:
  // Labeling
  static char*                      m_pszFormat;
  
  // Grouping
  UINT32                            m_un32NumRows;
  
  // Reference counting
  static UINT32                     m_un32ReferenceCount;

  // Serialization
  E_DLL0 UINT32 E_DLL1              GetSignature            ( );
  virtual E_DLL0 void E_DLL1        Serialize               ( FILE*  pFile, BOOL bWrite, UINT32 un32FileVersion, BOOL bDaughters = TRUE);
  virtual E_DLL0 void E_DLL1        Serialize               ( ESerializer* serializer, UINT32 un32FileVersion, BOOL bDaughters = TRUE);
  
  friend class EShape;
};

// stream operator for ERectangleShape
E_DLL0 std::ostream& E_DLL1  operator<<( std::ostream& stream, const ERectangleShape& rectangleShape);

////////////////////////////////////////////////////////////////////////////////////////////////////
// Circle interactive shape
class E_DLL1 ECircleShape: public ECircle, public EShape
{
  // Wrapping members
public:
  int handle_;
  FinalizeCallback callback_;

public:
  // Constructors
  E_DLL0 CONSTRUCTOR E_DLL1         ECircleShape            ( FLOAT32 f32CenterX = 0, FLOAT32 f32CenterY = 0,
                                                              FLOAT32 f32Diameter = 100, FLOAT32 f32OrgAngle = 0, BOOL bDirect = TRUE);
  E_DLL0 CONSTRUCTOR E_DLL1         ECircleShape            ( EPoint Center, FLOAT32 f32Diameter,
                                                              FLOAT32 f32OrgAngle, FLOAT32 f32Amplitude);
  E_DLL0 CONSTRUCTOR E_DLL1         ECircleShape            ( EPoint Org, EPoint Mid, EPoint End, BOOL bDirect);
  E_DLL0 CONSTRUCTOR E_DLL1         ECircleShape            ( EPoint Center, EPoint Org, BOOL bFull = TRUE);
 
public :
  E_DLL0 CONSTRUCTOR E_DLL1         ECircleShape            ( const ECircleShape& other);
  E_DLL0 ECircleShape& E_DLL1       operator=               ( const ECircleShape& other);

  virtual E_DLL0 EShape* E_DLL1     CreateShapeClone        ( BOOL bRecursive ) const;
  E_DLL0 ECircleShape* E_DLL1       CopyTo                  ( ECircleShape* dest, BOOL bRecursive ) const;

protected :
  E_DLL0 ECircleShape* E_DLL1       InternalCopyTo          ( ECircleShape*, BOOL, BOOL ) const;

public :
  E_DLL0 void E_DLL1                Rescale                 ( FLOAT32 f32Factor, BOOL bDaughters = TRUE);
  
  E_DLL0 DESTRUCTOR E_DLL1          ~ECircleShape           ( );
  
  E_DLL0 EShape* E_DLL1             New                     ( ) { return Copy( new ECircleShape( *this)); }
  
  // Typing
  E_DLL0 INS_SHAPE_TYPES E_DLL1     GetType                 ( );
  
  // Queries
  
  // Updates
  E_DLL0 void E_DLL1                Set                     ( EPoint Center, FLOAT32 f32Diameter,
                                                              FLOAT32 f32OrgAngle = 0, BOOL bDirect = TRUE);
  E_DLL0 void E_DLL1                Set                     ( EPoint Center, FLOAT32 f32Diameter,
                                                              FLOAT32 f32OrgAngle, FLOAT32 f32Amplitude);
  E_DLL0 void E_DLL1                Set                     ( EPoint Center, EPoint Org, BOOL bDirect = TRUE);
  E_DLL0 void E_DLL1                Set                     ( EPoint Org, EPoint Mid, EPoint End, BOOL bFull = TRUE);
                              
  // Grouping                 
  E_DLL0 void E_DLL1                SetIndexed              ( UINT32 un32NumShapes);
  E_DLL0 void E_DLL1                ArrangeDaughters        ( ); 
                              
  // Drawing                  
  E_DLL0 void E_DLL1                Draw                    ( HDC hDC, enum INS_DRAWING_MODES eDrawingMode = INS_DRAW_NOMINAL, BOOL bDaughters = TRUE);
  E_DLL0 void E_DLL1                Draw                    ( Euresys::DrawAdapter* drawAdapter, enum INS_DRAWING_MODES eDrawingMode = INS_DRAW_NOMINAL, BOOL bDaughters = TRUE);
                              
  E_DLL0 void E_DLL1                Closest                 ( );
  E_DLL0 BOOL E_DLL1                HitTest                 ( BOOL bDaughters = TRUE);
  E_DLL0 void E_DLL1                Drag                    ( INT32 n32CursorX, INT32 n32CursorY);
  
  // Geometry
  E_DLL0 EFrame* E_DLL1             CastToFrame             ( ) { return this; }
  
  // Labeling
  static E_DLL0 void E_DLL1         SetFormat               ( char* pszFormat);
  static E_DLL0 char* E_DLL1        GetFormat               ( BOOL bFull = FALSE);
 
// Debug DumpToStream method
// ---------------------------------------------------------------------------
public :
//  virtual E_DLL0 void E_DLL1        DumpToStream            ( std::ostream& strm , int indent = 0 ) const;

protected:
  // Handle angles
  FLOAT32                           m_f32MidHandle;
  FLOAT32                           m_f32EndHandle;
  EPoint                            GetOrgHandle            ( );
  EPoint                            GetMidHandle            ( );
  EPoint                            GetEndHandle            ( );
  
  // Labeling
  static char*                      m_pszFormat;
  
  // Reference counting
  static UINT32                     m_un32ReferenceCount;

  // Serialization
  E_DLL0 UINT32 E_DLL1              GetSignature            ( );
  virtual E_DLL0 void E_DLL1        Serialize               ( FILE*  pFile, BOOL bWrite, UINT32 un32FileVersion, BOOL bDaughters = TRUE);
  virtual E_DLL0 void E_DLL1        Serialize               ( ESerializer* serializer, UINT32 un32FileVersion, BOOL bDaughters = TRUE);
};

// stream operator for ECircleShape
E_DLL0 std::ostream& E_DLL1  operator<<( std::ostream& stream, const ECircleShape& circleShape);

////////////////////////////////////////////////////////////////////////////////////////////////////
// Wedge interactive shape
class E_DLL1 EWedgeShape: public EWedge, public EShape
{
  // Wrapping members
public:
  int handle_;
  FinalizeCallback callback_;

public:
  // Constructors
  E_DLL0 CONSTRUCTOR E_DLL1         EWedgeShape             ( FLOAT32 f32CenterX = 0, FLOAT32 f32CenterY = 0,
                                                              FLOAT32 f32Diameter = 100, FLOAT32 f32Breadth = 0,
                                                              FLOAT32 f32OrgAngle = 0, BOOL bDirect = TRUE);
  E_DLL0 CONSTRUCTOR E_DLL1         EWedgeShape             ( EPoint Center, FLOAT32 f32Diameter,
                                                              FLOAT32 f32Breadth, FLOAT32 f32OrgAngle,
                                                              FLOAT32 f32Amplitude);
  E_DLL0 CONSTRUCTOR E_DLL1         EWedgeShape             ( EPoint Center, EPoint Org,
                                                              FLOAT32 f32Breadth = 0, BOOL bDirect = TRUE);
  E_DLL0 CONSTRUCTOR E_DLL1         EWedgeShape             ( EPoint Org, EPoint Mid, EPoint End,
                                                              FLOAT32 f32Breadth = 0, BOOL bFullCircle = TRUE);
  
  E_DLL0 DESTRUCTOR E_DLL1          ~EWedgeShape            ( );
  
public :
  E_DLL0 CONSTRUCTOR E_DLL1         EWedgeShape             ( const EWedgeShape& other);
  E_DLL0 EWedgeShape& E_DLL1        operator=               ( const EWedgeShape& other);

  virtual E_DLL0 EShape* E_DLL1     CreateShapeClone        ( BOOL bRecursive ) const;
  E_DLL0 EWedgeShape* E_DLL1        CopyTo                  ( EWedgeShape* dest, BOOL bRecursive ) const;

protected :
  E_DLL0 EWedgeShape* E_DLL1        InternalCopyTo          ( EWedgeShape*, BOOL, BOOL ) const;

public :  
  E_DLL0 EShape* E_DLL1             New                     ( ) { return Copy( new EWedgeShape( *this)); }
  
  // Typing
  E_DLL0 INS_SHAPE_TYPES E_DLL1     GetType                 ( );
  
  // Queries
  
  // Updates
  E_DLL0 void E_DLL1                Set                     ( EPoint Center, FLOAT32 f32Diameter,
                                                              FLOAT32 f32Breadth = 0, FLOAT32 f32OrgAngle = 0,
                                                              BOOL bDirect = TRUE);
  E_DLL0 void E_DLL1                Set                     ( EPoint Center, FLOAT32 f32Diameter,
                                                              FLOAT32 f32Breadth, FLOAT32 f32OrgAngle,
                                                              FLOAT32 f32Amplitude);
  E_DLL0 void E_DLL1                Set                     ( EPoint Center, EPoint Org,
                                                              FLOAT32 f32Breadth = 0, BOOL bDirect = TRUE);
  E_DLL0 void E_DLL1                Set                     ( EPoint Org, EPoint Mid, EPoint End,
                                                              FLOAT32 f32Breadth = 0, BOOL bFullCircle = TRUE);
  E_DLL0 void E_DLL1                Rescale                 ( FLOAT32 f32Factor, BOOL bDaughters = TRUE);
  
  // Grouping
  E_DLL0 EShape* E_DLL1             GetDaughter             ( UINT32 un32Index) { return EShape::GetDaughter( un32Index); }
                                                      
  E_DLL0 UINT32 E_DLL1              GetRowIndex             ( EShape* pDaughter);
  E_DLL0 UINT32 E_DLL1              GetColIndex             ( EShape* pDaughter);
  E_DLL0 UINT32 E_DLL1              GetDaughterIndex        ( UINT32 un32ColIndex, UINT32 un32RowIndex);
  E_DLL0 EShape* E_DLL1             GetDaughter             ( UINT32 un32ColIndex, UINT32 un32RowIndex);
  E_DLL0 void E_DLL1                SetDaughter             ( UINT32 un32ColIndex, UINT32 un32RowIndex,
                                                              EShape* pDaughter = NULL);
                              
  E_DLL0 void E_DLL1                SetIndexed              ( UINT32 un32NumCols, UINT32 un32NumRows);
  E_DLL0 void E_DLL1                ArrangeDaughters        ( ); 
                              
  // Drawing                  
  E_DLL0 void E_DLL1                Draw                    ( HDC hDC,
                                                              enum INS_DRAWING_MODES eDrawingMode = INS_DRAW_NOMINAL,
                                                              BOOL bDaughters = TRUE);
  E_DLL0 void E_DLL1                Draw                    ( Euresys::DrawAdapter* drawAdapter,
                                                              enum INS_DRAWING_MODES eDrawingMode = INS_DRAW_NOMINAL,
                                                              BOOL bDaughters = TRUE);
                              
  E_DLL0 void E_DLL1                Closest                 ( );
  E_DLL0 BOOL E_DLL1                HitTest                 ( BOOL bDaughters = TRUE);
  E_DLL0 void E_DLL1                Drag                    ( INT32 n32CursorX, INT32 n32CursorY);
  
  // Geometry
  E_DLL0 EFrame* E_DLL1             CastToFrame             ( ) { return this; }
  E_DLL0 void E_DLL1                SetupMask               ( EROIBW8* pDst);
  E_DLL0 void E_DLL1                SetupMask               ( EROIC24* pDst);
                                                      
  // Labeling                                         
  static E_DLL0 void E_DLL1         SetFormat               ( char* pszFormat);
  static E_DLL0 char* E_DLL1        GetFormat               ( BOOL bFull = FALSE);

// Debug DumpToStream method
// ---------------------------------------------------------------------------
public :
//  virtual E_DLL0 void E_DLL1        DumpToStream            ( std::ostream& strm , int indent = 0 ) const;

protected:
  // Handle angles
  FLOAT32                           m_f32MidHandle;
  FLOAT32                           m_f32EndHandle;
  
  // Labeling
  static char*                      m_pszFormat;
  
  // Grouping
  UINT32                            m_un32NumRows;
  
  // Handles
  EPoint                            GetCoOrgHandle          ( );
  EPoint                            GetCoMidHandle          ( );
  EPoint                            GetCoEndHandle          ( ); 
  EPoint                            GetOrgHandle            ( );
  EPoint                            GetMidHandle            ( );
  EPoint                            GetEndHandle            ( );
  
  // Reference counting
  static UINT32                     m_un32ReferenceCount;
  
  // Serialization
  E_DLL0 UINT32 E_DLL1              GetSignature            ( );
  virtual E_DLL0 void E_DLL1        Serialize               ( FILE*  pFile, BOOL bWrite, UINT32 un32FileVersion, BOOL bDaughters = TRUE);
  virtual E_DLL0 void E_DLL1        Serialize               ( ESerializer* serializer, UINT32 un32FileVersion, BOOL bDaughters = TRUE);
  friend class EShape;
};

// stream operator for EWedgeShape
E_DLL0 std::ostream& E_DLL1  operator<<( std::ostream& stream, const EWedgeShape& wedgeShape);

////////////////////////////////////////////////////////////////////////////////////////////////////
// Landmark descriptor
struct ELandmark
{
  // Coordinate pairs
  EPoint Sensor, World;
  
  // Tag
  UINT32 un32Tag;
  
  union {
    // Grid reconstruction
    struct {
      // Grid topology
      UINT32 un32Neighbor[4];
    } Grid;
    
    // BGA ball measurement
    struct {
      FLOAT32 f32Diameter, f32Circularity, f32Doughnutness, f32QualityFactor;
      EListItem* pObject;
    } Bga;
  };
};

////////////////////////////////////////////////////////////////////////////////////////////////////
// Explicit class instantiation
//E_INSTANCE( EVectorTemplate<ELandmark>);



#define CALIBRATION_LANDMARK_NUMBER_MIN 4

////////////////////////////////////////////////////////////////////////////////////////////////////
// + OBSOLETE after 5.3.2
#define EmptyPointPairs EmptyLandmarks
#define AddPointPair AddLandmark
// - OBSOLETE after 5.3.2

// + OBSOLETE after 6.0.4
#define EnableFilter EnableBehaviorFilter
#define DisableFilter DisableBehaviorFilter
// - OBSOLETE after 6.0.4

#define NUM_DOF 9

////////////////////////////////////////////////////////////////////////////////////////////////////
// World frame primitive
class E_DLL1 EWorld: public EFrame
{
  // Wrapping members
public:
  int handle_;
  FinalizeCallback callback_;

public:
  // Constructor
  E_DLL0 CONSTRUCTOR E_DLL1         EWorld                  ( );
  E_DLL0 CONSTRUCTOR E_DLL1         EWorld                  ( FLOAT32 f32CenterX, FLOAT32 f32CenterY,
                                                              FLOAT32 f32Angle = 0, FLOAT32 f32Scale = 1);
                                                      
public :
  E_DLL0 CONSTRUCTOR E_DLL1         EWorld                  ( const EWorld& other);
  E_DLL0 EWorld& E_DLL1             operator=               ( const EWorld& other);

  virtual E_DLL0 EPoint* E_DLL1     CreatePointClone        ( ) const;
  E_DLL0 EWorld* E_DLL1             CopyTo                  ( EWorld* dest ) const;

protected :
  E_DLL0 EWorld* E_DLL1             InternalCopyTo          ( EWorld*, BOOL ) const;

public :
  // Calibration                                      
  E_DLL0 void E_DLL1                SetSensor               ( INT32 n32SensorWidth, INT32 n32SensorHeight,
                                                              FLOAT32 f32FieldWidth = 0, FLOAT32 f32FieldHeight = 0,
                                                              FLOAT32 f32CenterX = FLOAT32_UNDEFINED,
                                                              FLOAT32 f32CenterY = FLOAT32_UNDEFINED,
                                                              FLOAT32 f32Angle = 0,
                                                              FLOAT32 f32TiltXAngle = 0, FLOAT32 f32TiltYAngle = 0,
                                                              FLOAT32 f32PerspectiveStrength = 0,
                                                              FLOAT32 f32DistortionStrength = 0,
                                                              FLOAT32 f32DistortionStrength2 = 0,
                                                              FLOAT32 f32OpticalCenterX = FLOAT32_UNDEFINED,
                                                              FLOAT32 f32OpticalCenterY = FLOAT32_UNDEFINED, 
                                                              UINT32 un32RequiredCalibrationModes = 0);
                                                      
  // Simple calibration                               
  E_DLL0 void E_DLL1                SetSensorSize           ( INT32 n32Width, INT32 n32Height);
  E_DLL0 void E_DLL1                SetFieldSize            ( FLOAT32 f32FieldWidth, FLOAT32 f32FieldHeight = 0);
  E_DLL0 void E_DLL1                SetResolution           ( FLOAT32 f32XResolution, FLOAT32 f32YResolution = 0);
  E_DLL0 void E_DLL1                SetAngle                ( FLOAT32 f32Angle, BOOL bWorld = TRUE);
  E_DLL0 void E_DLL1                SetRatio                ( FLOAT32 f32Ratio);
                                                      
  E_DLL0 INT32 E_DLL1               GetSensorWidth          ( );
  E_DLL0 INT32 E_DLL1               GetSensorHeight         ( );
  E_DLL0 FLOAT32 E_DLL1             GetFieldWidth           ( );
  E_DLL0 FLOAT32 E_DLL1             GetFieldHeight          ( );
  E_DLL0 FLOAT32 E_DLL1             GetXResolution          ( );
  E_DLL0 FLOAT32 E_DLL1             GetYResolution          ( );
  E_DLL0 FLOAT32 E_DLL1             GetRatio                ( );
  E_DLL0 FLOAT32 E_DLL1             GetAngle                ( BOOL /*bWorld*/ = TRUE) { return EFrame::GetAngle( ); }
                                                      
  // Advanced calibration                             
  E_DLL0 void E_DLL1                SetPerspective          ( FLOAT32 f32TiltXAngle, FLOAT32 f32TiltYAngle,
                                                              FLOAT32 f32PerspectiveStrength);
  E_DLL0 FLOAT32 E_DLL1             GetTiltXAngle           ( ) { return EFromRadians( m_f32TiltXAngle); }
                                                      
  E_DLL0 FLOAT32 E_DLL1             GetTiltYAngle           ( ) { return EFromRadians( m_f32TiltYAngle); }
                              
  E_DLL0 FLOAT32 E_DLL1             GetPerspectiveStrength  ( ) { return m_f32PerspectiveStrength; }
                              
  E_DLL0 void E_DLL1                SetDistortion           ( FLOAT32 f32DistortionStrength,
                                                              FLOAT32 f32DistortionStrength2 = 0);
  E_DLL0 void E_DLL1                SetOpticalCenter        ( FLOAT32 f32CenterX, FLOAT32 f32CenterY);
                                                      
  E_DLL0 FLOAT32 E_DLL1             GetDistortionStrength   ( ) { return m_f32DistortionStrength; }
                              
  E_DLL0 FLOAT32 E_DLL1             GetDistortionStrength2  ( ) { return m_f32DistortionStrength2; }
                              
  E_DLL0 FLOAT32 E_DLL1             GetOpticalCenterX       ( );
  E_DLL0 FLOAT32 E_DLL1             GetOpticalCenterY       ( );
                                                      
  E_DLL0 UINT32 E_DLL1              GetCalibrationModes     ( ) { return m_un32CalibrationModes; }
  E_DLL0 void E_DLL1                SetCalibrationModes     ( UINT32 un32CalibrationModes);

  // User-defined calibration
  E_DLL0 void E_DLL1                SetUserCalibration      ( 
  void                                ( *WorldToSensor)       ( FLOAT32 f32WorldX, FLOAT32 f32WorldY, FLOAT32& f32SensorX, FLOAT32& f32SensorY),
  void                                ( *WorldToSensorJacobian)( FLOAT32 f32WorldX, FLOAT32 f32WorldY, FLOAT32& f32SensorX, FLOAT32& f32SensorY, FLOAT32& f32Xx, FLOAT32& f32Xy, FLOAT32& f32Yx, FLOAT32& f32Yy),
  void                                ( *SensorToWorld)       ( FLOAT32 f32SensorX, FLOAT32 f32SensorY, FLOAT32& f32WorldX, FLOAT32& f32WorldY));
  
  E_DLL0 void E_DLL1                EmptyLandmarks          ( );
  E_DLL0 void E_DLL1                AddPoint                ( EPoint SensorPoint);
  E_DLL0 void E_DLL1                AddLandmark             ( EPoint SensorPoint, EPoint WorldPoint);
  E_DLL0 void E_DLL1                RemoveLandmark          ( UINT32 un32Index);
  E_DLL0 void E_DLL1                AddLandmark             ( EPoint SensorPoint, EPoint WorldPoint, 
                                                              FLOAT32 f32Diameter, FLOAT32 f32Circularity,
                                                              FLOAT32 f32Doughnutness, FLOAT32 f32QualityFactor,
                                                              EListItem* pObject);
  E_DLL0 void E_DLL1                Calibrate               ( UINT32 un32CalibrationModes = ~0);
  
  E_DLL0 UINT32 E_DLL1              AutoCalibrate           ( BOOL bTestEmpiricModes= FALSE);
  E_DLL0 UINT32 E_DLL1              AutoCalibrateLandmarks  ( BOOL bTestEmpiricModes= FALSE);
  E_DLL0 UINT32 E_DLL1              AutoCalibrateDotGrid    ( EROIBW8* pSrc, FLOAT32 f32ColPitch, FLOAT32 f32RowPitch, BOOL bTestEmpiricalModes = FALSE);
  
  // Calibration success (no Landmark calibration)
  E_DLL0 BOOL E_DLL1                CalibrationSucceeded();

  // Calibration Coefficients
  E_DLL0 void E_DLL1                ComputeCalibrationQualityIndicators();

  E_DLL0 FLOAT32 E_DLL1             GetGridPointsMeanVariation  ( );
  E_DLL0 FLOAT32 E_DLL1             GetGridPointsMaxVariation   ( );

  E_DLL0 FLOAT32 E_DLL1             GetGridPointsMeanVariationThreshold ( );
  E_DLL0 void E_DLL1                SetGridPointsMeanVariationThreshold (FLOAT32 f32MeanVariationThreshold);

  E_DLL0 FLOAT32 E_DLL1             GetGridPointsMaxVariationThreshold  ( );
  E_DLL0 void E_DLL1                SetGridPointsMaxVariationThreshold  (FLOAT32 f32MaxVariationThreshold);
                              
  // Grid calibration         
  E_DLL0 UINT32 E_DLL1              RebuildGrid             ( FLOAT32 f32ColPitch, FLOAT32 f32RowPitch, UINT32 un32CenterIndex = ~0, EPoint WorldCenter = EPoint( 0, 0), BOOL bDirect = TRUE);
                              
  // Registration             
  E_DLL0 EPoint E_DLL1              SensorPointsGravityCenter( );
  E_DLL0 EPoint E_DLL1              SensorPointsMoments     ( FLOAT32& f32Mxx, FLOAT32& f32Mxy, FLOAT32& f32Myy);
  E_DLL0 EPoint E_DLL1              WorldPointsGravityCenter( );
  E_DLL0 EPoint E_DLL1              WorldPointsMoments      ( FLOAT32& f32Mxx, FLOAT32& f32Mxy, FLOAT32& f32Myy);
                              
  // Distortion removal       
  E_DLL0 void E_DLL1                Unwarp                  ( EROIBW8* pSrcImage, EROIBW8* pDstImage, BOOL bInterpolate = TRUE);
  E_DLL0 void E_DLL1                Unwarp                  ( EROIC24* pSrcImage, EROIC24* pDstImage, BOOL bInterpolate = TRUE);
                              
  E_DLL0 void E_DLL1                SetupUnwarp             ( EROISubPixel64* pLookupTable, EROIBW8* pSrcImage, BOOL bInterpolate = TRUE);
  E_DLL0 void E_DLL1                SetupUnwarp             ( EROISubPixel64* pLookupTable, EROIC24* pSrcImage, BOOL bInterpolate = TRUE);
  E_DLL0 void E_DLL1                Unwarp                  ( EROISubPixel64* pLookupTable, EROIBW8* pSrcImage, EROIBW8* pDstImage, BOOL bInterpolate = TRUE);
  E_DLL0 void E_DLL1                Unwarp                  ( EROISubPixel64* pLookupTable, EROIC24* pSrcImage, EROIC24* pDstImage, BOOL bInterpolate = TRUE);
                              
  // Helpers                  
  E_DLL0 BOOL E_DLL1                GetDirect               ( );
  E_DLL0 void E_DLL1                Invalidate              ( );
  E_DLL0 void E_DLL1                Validate                ( );
                              
  E_DLL0 EPoint E_DLL1              SensorToWorld           ( EPoint SPoint) { return (*m_pSensorToWorld)(this, SPoint); } 
  E_DLL0 EPoint E_DLL1              WorldToSensor           ( EPoint WPoint) { return (*m_pWorldToSensor)(this, WPoint); }  
  E_DLL0 EPoint E_DLL1              WorldToSensor           ( EPoint WPoint,
                                                              FLOAT32& f32Xx, FLOAT32& f32Xy,
                                                              FLOAT32& f32Yx, FLOAT32& f32Yy) {
                                                                return (*m_pWorldToSensorJacobian)(this, WPoint, f32Xx, f32Xy, f32Yx, f32Yy);
                                                              }  

// Debug DumpToStream method
// ---------------------------------------------------------------------------
public :
//  virtual E_DLL0 void E_DLL1        DumpToStream            ( std::ostream& strm , int indent = 0 ) const;

protected:

  // Calibration transform tables
  EPoint                            WorldToSensorInvalid    ( EPoint WPoint);
  EPoint                            WorldToSensorRaw        ( EPoint WPoint);
  EPoint                            WorldToSensorCenteredInverse( EPoint WPoint);
  EPoint                            WorldToSensorCenteredDirect( EPoint WPoint);
  EPoint                            WorldToSensorScaled     ( EPoint WPoint);
  EPoint                            WorldToSensorAffine     ( EPoint WPoint);
  EPoint                            WorldToSensorPerspective( EPoint WPoint);
  EPoint                            WorldToSensorRadialCenteredInverse( EPoint WPoint);
  EPoint                            WorldToSensorRadialCenteredDirect( EPoint WPoint);
  EPoint                            WorldToSensorRadialScaled( EPoint WPoint);
  EPoint                            WorldToSensorRadialAffine( EPoint WPoint);
  EPoint                            WorldToSensorRadialPerspective( EPoint WPoint);
  EPoint                            WorldToSensorBilinear   ( EPoint WPoint);
  EPoint                            WorldToSensorQuadratic  ( EPoint WPoint);
  EPoint                            WorldToSensorUser       ( EPoint WPoint);

  static EPoint                     StaticWorldToSensorInvalid    (EWorld* owner, EPoint WPoint);
  static EPoint                     StaticWorldToSensorRaw        (EWorld* owner, EPoint WPoint);
  static EPoint                     StaticWorldToSensorCenteredInverse(EWorld* owner, EPoint WPoint);
  static EPoint                     StaticWorldToSensorCenteredDirect(EWorld* owner, EPoint WPoint);
  static EPoint                     StaticWorldToSensorScaled     (EWorld* owner, EPoint WPoint);
  static EPoint                     StaticWorldToSensorAffine     (EWorld* owner, EPoint WPoint);
  static EPoint                     StaticWorldToSensorPerspective(EWorld* owner, EPoint WPoint);
  static EPoint                     StaticWorldToSensorRadialCenteredInverse(EWorld* owner, EPoint WPoint);
  static EPoint                     StaticWorldToSensorRadialCenteredDirect(EWorld* owner, EPoint WPoint);
  static EPoint                     StaticWorldToSensorRadialScaled(EWorld* owner, EPoint WPoint);
  static EPoint                     StaticWorldToSensorRadialAffine(EWorld* owner, EPoint WPoint);
  static EPoint                     StaticWorldToSensorRadialPerspective(EWorld* owner, EPoint WPoint);
  static EPoint                     StaticWorldToSensorBilinear   (EWorld* owner, EPoint WPoint);
  static EPoint                     StaticWorldToSensorQuadratic  (EWorld* owner, EPoint WPoint);
  static EPoint                     StaticWorldToSensorUser       (EWorld* owner, EPoint WPoint);
                                    
  EPoint                            WorldToSensorInvalid    ( EPoint WPoint, FLOAT32& f32Xx, FLOAT32& f32Xy, FLOAT32& f32Yx, FLOAT32& f32Yy);
  EPoint                            WorldToSensorRaw        ( EPoint WPoint, FLOAT32& f32Xx, FLOAT32& f32Xy, FLOAT32& f32Yx, FLOAT32& f32Yy);
  EPoint                            WorldToSensorCenteredInverse( EPoint WPoint, FLOAT32& f32Xx, FLOAT32& f32Xy, FLOAT32& f32Yx, FLOAT32& f32Yy);
  EPoint                            WorldToSensorCenteredDirect( EPoint WPoint, FLOAT32& f32Xx, FLOAT32& f32Xy, FLOAT32& f32Yx, FLOAT32& f32Yy);
  EPoint                            WorldToSensorScaled     ( EPoint WPoint, FLOAT32& f32Xx, FLOAT32& f32Xy, FLOAT32& f32Yx, FLOAT32& f32Yy);
  EPoint                            WorldToSensorAffine     ( EPoint WPoint, FLOAT32& f32Xx, FLOAT32& f32Xy, FLOAT32& f32Yx, FLOAT32& f32Yy);
  EPoint                            WorldToSensorPerspective( EPoint WPoint, FLOAT32& f32Xx, FLOAT32& f32Xy, FLOAT32& f32Yx, FLOAT32& f32Yy);
  EPoint                            WorldToSensorRadialCenteredInverse( EPoint WPoint, FLOAT32& f32Xx, FLOAT32& f32Xy, FLOAT32& f32Yx, FLOAT32& f32Yy);
  EPoint                            WorldToSensorRadialCenteredDirect( EPoint WPoint, FLOAT32& f32Xx, FLOAT32& f32Xy, FLOAT32& f32Yx, FLOAT32& f32Yy);
  EPoint                            WorldToSensorRadialScaled( EPoint WPoint, FLOAT32& f32Xx, FLOAT32& f32Xy, FLOAT32& f32Yx, FLOAT32& f32Yy);
  EPoint                            WorldToSensorRadialAffine( EPoint WPoint, FLOAT32& f32Xx, FLOAT32& f32Xy, FLOAT32& f32Yx, FLOAT32& f32Yy);
  EPoint                            WorldToSensorRadialPerspective( EPoint WPoint, FLOAT32& f32Xx, FLOAT32& f32Xy, FLOAT32& f32Yx, FLOAT32& f32Yy);
  EPoint                            WorldToSensorBilinear   ( EPoint WPoint, FLOAT32& f32Xx, FLOAT32& f32Xy, FLOAT32& f32Yx, FLOAT32& f32Yy);
  EPoint                            WorldToSensorQuadratic  ( EPoint WPoint, FLOAT32& f32Xx, FLOAT32& f32Xy, FLOAT32& f32Yx, FLOAT32& f32Yy);
  EPoint                            WorldToSensorUser       ( EPoint WPoint, FLOAT32& f32Xx, FLOAT32& f32Xy, FLOAT32& f32Yx, FLOAT32& f32Yy);

  static EPoint                     StaticWorldToSensorInvalid    (EWorld* owner, EPoint WPoint, FLOAT32& f32Xx, FLOAT32& f32Xy, FLOAT32& f32Yx, FLOAT32& f32Yy);
  static EPoint                     StaticWorldToSensorRaw        (EWorld* owner, EPoint WPoint, FLOAT32& f32Xx, FLOAT32& f32Xy, FLOAT32& f32Yx, FLOAT32& f32Yy);
  static EPoint                     StaticWorldToSensorCenteredInverse(EWorld* owner, EPoint WPoint, FLOAT32& f32Xx, FLOAT32& f32Xy, FLOAT32& f32Yx, FLOAT32& f32Yy);
  static EPoint                     StaticWorldToSensorCenteredDirect(EWorld* owner, EPoint WPoint, FLOAT32& f32Xx, FLOAT32& f32Xy, FLOAT32& f32Yx, FLOAT32& f32Yy);
  static EPoint                     StaticWorldToSensorScaled     (EWorld* owner, EPoint WPoint, FLOAT32& f32Xx, FLOAT32& f32Xy, FLOAT32& f32Yx, FLOAT32& f32Yy);
  static EPoint                     StaticWorldToSensorAffine     (EWorld* owner, EPoint WPoint, FLOAT32& f32Xx, FLOAT32& f32Xy, FLOAT32& f32Yx, FLOAT32& f32Yy);
  static EPoint                     StaticWorldToSensorPerspective(EWorld* owner, EPoint WPoint, FLOAT32& f32Xx, FLOAT32& f32Xy, FLOAT32& f32Yx, FLOAT32& f32Yy);
  static EPoint                     StaticWorldToSensorRadialCenteredInverse(EWorld* owner, EPoint WPoint, FLOAT32& f32Xx, FLOAT32& f32Xy, FLOAT32& f32Yx, FLOAT32& f32Yy);
  static EPoint                     StaticWorldToSensorRadialCenteredDirect(EWorld* owner, EPoint WPoint, FLOAT32& f32Xx, FLOAT32& f32Xy, FLOAT32& f32Yx, FLOAT32& f32Yy);
  static EPoint                     StaticWorldToSensorRadialScaled(EWorld* owner, EPoint WPoint, FLOAT32& f32Xx, FLOAT32& f32Xy, FLOAT32& f32Yx, FLOAT32& f32Yy);
  static EPoint                     StaticWorldToSensorRadialAffine(EWorld* owner, EPoint WPoint, FLOAT32& f32Xx, FLOAT32& f32Xy, FLOAT32& f32Yx, FLOAT32& f32Yy);
  static EPoint                     StaticWorldToSensorRadialPerspective(EWorld* owner, EPoint WPoint, FLOAT32& f32Xx, FLOAT32& f32Xy, FLOAT32& f32Yx, FLOAT32& f32Yy);
  static EPoint                     StaticWorldToSensorBilinear   (EWorld* owner, EPoint WPoint, FLOAT32& f32Xx, FLOAT32& f32Xy, FLOAT32& f32Yx, FLOAT32& f32Yy);
  static EPoint                     StaticWorldToSensorQuadratic  (EWorld* owner, EPoint WPoint, FLOAT32& f32Xx, FLOAT32& f32Xy, FLOAT32& f32Yx, FLOAT32& f32Yy);
  static EPoint                     StaticWorldToSensorUser       (EWorld* owner, EPoint WPoint, FLOAT32& f32Xx, FLOAT32& f32Xy, FLOAT32& f32Yx, FLOAT32& f32Yy);
                                    
  EPoint                            SensorToWorldInvalid    ( EPoint WPoint);
  EPoint                            SensorToWorldRaw        ( EPoint WPoint);
  EPoint                            SensorToWorldCenteredInverse( EPoint WPoint);
  EPoint                            SensorToWorldCenteredDirect( EPoint WPoint);
  EPoint                            SensorToWorldScaled     ( EPoint WPoint);
  EPoint                            SensorToWorldAffine     ( EPoint WPoint);
  EPoint                            SensorToWorldPerspective( EPoint WPoint);
  EPoint                            SensorToWorldRadialCenteredInverse( EPoint WPoint);
  EPoint                            SensorToWorldRadialCenteredDirect( EPoint WPoint);
  EPoint                            SensorToWorldRadialScaled( EPoint WPoint);
  EPoint                            SensorToWorldRadialAffine( EPoint WPoint);
  EPoint                            SensorToWorldRadialPerspective( EPoint WPoint);
  EPoint                            SensorToWorldQuadratic  ( EPoint WPoint);
  EPoint                            SensorToWorldBilinear   ( EPoint WPoint);
  EPoint                            SensorToWorldUser       ( EPoint WPoint);

  static EPoint                     StaticSensorToWorldInvalid    (EWorld* owner, EPoint WPoint);
  static EPoint                     StaticSensorToWorldRaw        (EWorld* owner, EPoint WPoint);
  static EPoint                     StaticSensorToWorldCenteredInverse(EWorld* owner, EPoint WPoint);
  static EPoint                     StaticSensorToWorldCenteredDirect(EWorld* owner, EPoint WPoint);
  static EPoint                     StaticSensorToWorldScaled     (EWorld* owner, EPoint WPoint);
  static EPoint                     StaticSensorToWorldAffine     (EWorld* owner, EPoint WPoint);
  static EPoint                     StaticSensorToWorldPerspective(EWorld* owner, EPoint WPoint);
  static EPoint                     StaticSensorToWorldRadialCenteredInverse(EWorld* owner, EPoint WPoint);
  static EPoint                     StaticSensorToWorldRadialCenteredDirect(EWorld* owner, EPoint WPoint);
  static EPoint                     StaticSensorToWorldRadialScaled(EWorld* owner, EPoint WPoint);
  static EPoint                     StaticSensorToWorldRadialAffine(EWorld* owner, EPoint WPoint);
  static EPoint                     StaticSensorToWorldRadialPerspective(EWorld* owner, EPoint WPoint);
  static EPoint                     StaticSensorToWorldQuadratic  (EWorld* owner, EPoint WPoint);
  static EPoint                     StaticSensorToWorldBilinear   (EWorld* owner, EPoint WPoint);
  static EPoint                     StaticSensorToWorldUser       (EWorld* owner, EPoint WPoint);
                                    
  void                              PointFit                ( BOOL bXEquation, EPoint WPoint, FLOAT32& f32Fit,
                                                              FLOAT32 f32Derivatives[]);
  void                              Helper1                 ( FLOAT32 f32Unknowns[],
                                                              FLOAT32 f32LHS[NUM_DOF][NUM_DOF],
                                                              FLOAT32 f32RHS[], FLOAT32& f32Residue);
  void                              Helper2                 ( FLOAT32 f32Unknowns[],
                                                              FLOAT32 f32Array[NUM_DOF][NUM_DOF],
                                                              FLOAT32 f32LHS[NUM_DOF][NUM_DOF],
                                                              FLOAT32& f32Residue, FLOAT32& f32Score);
  
                                    
  // Helpers                        
  void                              InverseTransform        ( );
                                    
  void                              Connect                 ( UINT32  un32From, 
                                                              UINT32  un32To, 
                                                              UINT32  un32Dir, 
                                                              BOOL    bDirect);
  
  void                              HeapStackConnect        ( UINT32                    startNextCallAtAddress, 
                                                              INT32&                    stackIndex, 
                                                              void*                     cookie);
  
  // Serialization
  virtual E_DLL0 void E_DLL1        Serialize               ( FILE*  pFile, BOOL bWrite, UINT32 un32FileVersion);
  virtual E_DLL0 void E_DLL1        Serialize               ( ESerializer* serializer, UINT32 un32FileVersion);

  friend class EWedgeShape;
public :
  // Calibration points
  EVectorTemplate<ELandmark>  		  m_Landmark;
  void*                             m_opaqueTR;

protected :
  FLOAT32                           m_f32TiltXAngle; 
  FLOAT32                           m_f32TiltYAngle; 
  FLOAT32                           m_f32PerspectiveStrength; 
  FLOAT32                           m_f32DistortionStrength; 
  FLOAT32                           m_f32DistortionStrength2; 
  UINT32                            m_un32CalibrationModes; 

  // Grid calibration               
  UINT32                            m_un32GridCenterIndex;
  UINT32                            m_un32NumGridPoints;
  FLOAT32                           m_f32GridPitchX;
  FLOAT32                           m_f32GridPitchY;

  EPoint                            (*m_pWorldToSensor)(EWorld* owner, EPoint WPoint);
  EPoint                            (*m_pWorldToSensorJacobian)(EWorld* owner, EPoint WPoint, FLOAT32& f32Xx, FLOAT32& f32Xy, FLOAT32& f32Yx, FLOAT32& f32Yy);
  EPoint                            (*m_pSensorToWorld)(EWorld* owner, EPoint WPoint);

  UINT32                            m_un32Frozen;
  // User-defined transform call-backs
  void                              ( * m_pWorldToSensorUser)( FLOAT32 f32WorldX, FLOAT32 f32WorldY, FLOAT32& f32SensorX, FLOAT32& f32SensorY);
  void                              ( * m_pWorldToSensorJacobianUser)( FLOAT32 f32WorldX, FLOAT32 f32WorldY, FLOAT32& f32SensorX, FLOAT32& f32SensorY, FLOAT32& f32Xx, FLOAT32& f32Xy, FLOAT32& f32Yx, FLOAT32& f32Yy);
  void                              ( * m_pSensorToWorldUser)( FLOAT32 f32SensorX, FLOAT32 f32SensorY, FLOAT32& f32WorldX, FLOAT32& f32WorldY);

  // Sensor size                    
  INT32                             m_n32SensorWidth;
  INT32                             m_n32SensorHeight;
  FLOAT32                           m_f32OpticalCenterX;
  FLOAT32                           m_f32OpticalCenterY;

  // Aspect ratio                   
  FLOAT32                           m_f32Ratio;

  // Inverse affine coefficients
  FLOAT32                           m_f32x;
  FLOAT32                           m_f32y;

  // Perspective coefficients
  FLOAT32                           m_f32Zx;
  FLOAT32                           m_f32Zy;
  FLOAT32                           m_f32zX;
  FLOAT32                           m_f32zY;

  // Bilinear/quadratic coefficients
  FLOAT32                           m_f32Xxx;
  FLOAT32                           m_f32Xxy;
  FLOAT32                           m_f32Xyy;
  FLOAT32                           m_f32Yxx;
  FLOAT32                           m_f32Yxy;
  FLOAT32                           m_f32Yyy;

  // Inverse bilinear/quadratic coefficients
  FLOAT32                           m_f32xXX;
  FLOAT32                           m_f32xXY;
  FLOAT32                           m_f32xYY;
  FLOAT32                           m_f32yXX;
  FLOAT32                           m_f32yXY;
  FLOAT32                           m_f32yYY;

  // Model order
  UINT32                            m_un32Order;

  // Calibration distances
  FLOAT32                           m_f32MeanSquareDistance;
  FLOAT32                           m_f32MaxSquareDistance;
  FLOAT32                           m_f32MeanSquareDistanceThreshold;
  FLOAT32                           m_f32MaxSquareDistanceThreshold;
};

////////////////////////////////////////////////////////////////////////////////////////////////////
// EWorldShape class
class E_DLL1 EWorldShape: public EWorld, public EShape
{
  // Wrapping members
public:
  int handle_;
  FinalizeCallback callback_;

public:
  // Constructors
  E_DLL0 CONSTRUCTOR E_DLL1         EWorldShape             ( FLOAT32 f32CenterX = 0, FLOAT32 f32CenterY = 0,
                                                              FLOAT32 f32Angle = 0, FLOAT32 f32Scale = 1,
                                                              FLOAT32 f32SizeX = 100, FLOAT32 f32SizeY = 100);
public :
  E_DLL0 CONSTRUCTOR E_DLL1         EWorldShape             ( const EWorldShape& other);
  E_DLL0 EWorldShape& E_DLL1        operator=               ( const EWorldShape& other);

  virtual E_DLL0 EShape* E_DLL1     CreateShapeClone        ( BOOL bRecursive ) const;
  E_DLL0 EWorldShape* E_DLL1        CopyTo                  ( EWorldShape* dest, BOOL bRecursive ) const;

protected :
  E_DLL0 EWorldShape* E_DLL1        InternalCopyTo          ( EWorldShape* dest, BOOL bRecursive, BOOL bIsACtor) const;

public :  
  E_DLL0 EShape* E_DLL1             New                     ( ) { return Copy( new EWorldShape( *this)); }
  
  // Typing
  E_DLL0 INS_SHAPE_TYPES E_DLL1     GetType                 ( );

  // Grouping
  E_DLL0 void E_DLL1                Attach                  ( EShape* pMother);
  E_DLL0 void E_DLL1                Detach                  ( );
  
  // Geometry
  E_DLL0 EFrame* E_DLL1             CastToFrame             ( ) { return this; }
  E_DLL0 void E_DLL1                SetSize                 ( FLOAT32 f32SizeX, FLOAT32 f32SizeY = 0);
  E_DLL0 void E_DLL1                Rescale                 ( FLOAT32 f32Factor, BOOL bDaughters = TRUE);
  
  // Handles interaction
  E_DLL0 void E_DLL1                Closest                 ( );
  E_DLL0 BOOL E_DLL1                HitTest                 ( BOOL bDaughters = TRUE);
  E_DLL0 void E_DLL1                Drag                    ( INT32 n32CursorX, INT32 n32CursorY);
                              
  E_DLL0 void E_DLL1                Draw                    ( HDC hDC,
                                                              enum INS_DRAWING_MODES eDrawingMode = INS_DRAW_NOMINAL,
                                                              BOOL bDaughters = TRUE);
  E_DLL0 void E_DLL1                Draw                    ( Euresys::DrawAdapter* drawAdapter,
                                                              enum INS_DRAWING_MODES eDrawingMode = INS_DRAW_NOMINAL,
                                                              BOOL bDaughters = TRUE);
  E_DLL0 void E_DLL1                DrawCrossGrid           ( HDC hDC, 
                                                              FLOAT32 f32XMin = - 1, FLOAT32 f32XMax = + 1,
                                                              FLOAT32 f32YMin = - 1, FLOAT32 f32YMax = + 1,
                                                              UINT32 un32NumXIntervals = 2,
                                                              UINT32 un32NumYIntervals = 2);
  E_DLL0 void E_DLL1                DrawCrossGrid           ( Euresys::DrawAdapter* drawAdapter, 
                                                              FLOAT32 f32XMin = - 1, FLOAT32 f32XMax = + 1,
                                                              FLOAT32 f32YMin = - 1, FLOAT32 f32YMax = + 1,
                                                              UINT32 un32NumXIntervals = 2,
                                                              UINT32 un32NumYIntervals = 2);
  
  // Zooming and panning
  E_DLL0 FLOAT32 E_DLL1             GetZoomX                ( );
  E_DLL0 FLOAT32 E_DLL1             GetZoomY                ( );
  E_DLL0 FLOAT32 E_DLL1             GetPanX                 ( );
  E_DLL0 FLOAT32 E_DLL1             GetPanY                 ( );
  E_DLL0 void E_DLL1                SetZoom                 ( FLOAT32 f32ZoomX = 1, FLOAT32 f32ZoomY = 0);
  E_DLL0 void E_DLL1                SetPan                  ( FLOAT32 f32PanX = 0, FLOAT32 f32PanY = 0);
  
  // Grid calibration
  E_DLL0 void E_DLL1                DrawGrid                ( HDC hDC);
  E_DLL0 void E_DLL1                DrawGrid                ( Euresys::DrawAdapter* drawAdapter);

  // Landmarks calibration                            
  E_DLL0 void E_DLL1                DrawLandmarks           ( Euresys::DrawAdapter* drawAdapter);
  E_DLL0 void E_DLL1                DrawLandmarks           ( HDC hDC);
  E_DLL0 void E_DLL1                HitLandmark             ( );
  E_DLL0 UINT32 E_DLL1              GetHitLandmark          ( );
  E_DLL0 void E_DLL1                DragLandmark            ( INT32 n32CursorX, INT32 n32CursorY);
                                                      
  // Drawing helpers                                  
  E_DLL0 void E_DLL1                HalveSegment            ( HDC hDC, EPoint P0, INT32 n32X0, INT32 n32Y0, EPoint P2, INT32 n32X2, INT32 n32Y2);
  E_DLL0 void E_DLL1                HalveSegment            ( Euresys::DrawAdapter* drawAdapter, EPoint P0, INT32 n32X0, INT32 n32Y0, EPoint P2, INT32 n32X2, INT32 n32Y2);
  E_DLL0 void E_DLL1                HalveCircle             ( HDC hDC, EPoint Center, FLOAT32 f32Radius,
                                                              FLOAT32 f32Angle0, INT32 n32X0, INT32 n32Y0,
                                                              FLOAT32 f32Angle2, INT32 n32X2, INT32 n32Y2);
  E_DLL0 void E_DLL1                HalveCircle             ( Euresys::DrawAdapter* drawAdapter, EPoint Center, FLOAT32 f32Radius,
                                                              FLOAT32 f32Angle0, INT32 n32X0, INT32 n32Y0,
                                                              FLOAT32 f32Angle2, INT32 n32X2, INT32 n32Y2);
  E_DLL0 void E_DLL1                HalveArc                ( HDC hDC, EPoint Center, FLOAT32 f32Radius,
                                                              FLOAT32 f32Angle0, INT32 n32X0, INT32 n32Y0,
                                                              FLOAT32 f32Angle2, INT32 n32X2, INT32 n32Y2);
  E_DLL0 void E_DLL1                HalveArc                ( Euresys::DrawAdapter* drawAdapter, EPoint Center, FLOAT32 f32Radius,
                                                              FLOAT32 f32Angle0, INT32 n32X0, INT32 n32Y0,
                                                              FLOAT32 f32Angle2, INT32 n32X2, INT32 n32Y2);

  // Debug DumpToStream method
// ---------------------------------------------------------------------------
public :
//  virtual E_DLL0 void E_DLL1        DumpToStream            ( std::ostream& strm , int indent = 0 ) const;

protected:
  // Axes length
  FLOAT32                           m_f32SizeX, m_f32SizeY;
  
  // Labeling
  static char*                      m_pszFormat;
  
  // Serialization
  E_DLL0 UINT32 E_DLL1              GetSignature            ( );
  virtual E_DLL0 void E_DLL1        Serialize               ( ESerializer* serializer, UINT32 un32FileVersion, BOOL bDaughters = TRUE);
  virtual E_DLL0 void E_DLL1        Serialize               ( FILE*  pFile, BOOL bWrite, UINT32 un32FileVersion, BOOL bDaughters = TRUE); 

  // Landmarks calibration
  UINT32                            m_un32HitLandmark;
  
  // Grid calibration
  void                              DrawGridEdge            ( HDC hDC, UINT32 un32From, UINT32 un32To);
  void                              DrawGridEdge            ( Euresys::DrawAdapter* drawAdapter, UINT32 un32From, UINT32 un32To);
  void                              DrawGridEdge_HeapStack  ( INT32& stackIndex, void* cookie);
                                    
  void                              ArrangeDaughters        ( ) {}

  // Zooming and panning
  FLOAT32                           m_f32ZoomX;
  FLOAT32                           m_f32ZoomY;
  FLOAT32                           m_f32PanX;
  FLOAT32                           m_f32PanY;

  friend class EShape;
};

////////////////////////////////////////////////////////////////////////////////////////////////////
// Default world shape
extern E_DLL0 EWorldShape E_DLL1  EasyWorld;

////////////////////////////////////////////////////////////////////////////////////////////////////
// Stream operators
E_DLL0 std::ostream& E_DLL1     operator<<( std::ostream& strm, const ELandmark& obj);

inline EFrame* EShape::GetFrame( )
{
  EFrame* motherFrame;
  EShape* worldShape = ( EShape*)GetWorldShape( );

  if ( m_pMother == worldShape) motherFrame = NULL;
  else motherFrame = m_pMother->GetFrame( );

  EFrame* myFrame = CastToFrame();
  return myFrame->GetFrame( motherFrame);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
#endif // __EINSPECT_H__
