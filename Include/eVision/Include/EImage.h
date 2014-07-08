////////////////////////////////////////////////////////////////////////////////////////////////////
// EImage.h: EasyImage library header file for eVision 6.7.1.0
//
// EasyImage is a set of general purpose image processing functions
//
// Copyright ( c) 1997-2006, Euresys. All rights reserved.
//

#ifndef __EIMAGE_H__
#define __EIMAGE_H__

// eVision header files
#include "Easy.h"
#include "EImage_Enum.h"

#include "EasyImage_BinaryCompatible.h"



////////////////////////////////////////////////////////////////////////////////
// EKernel class
//

class EKernel
{
  // Wrapping members
public:
  int handle_;
  FinalizeCallback callback_;

private :
  INT16 m_n16SizeX;
  INT16 m_n16SizeY;
  FLOAT32 m_f32Gain;
  UINT32 m_un32Offset;
  INT16 m_n16Rectifier;
  UINT32 m_un32OutsideValue;
  FLOAT32* m_pDataPtr;
  UINT32 m_un32AllocatedSize;
  
protected :
  
public :
  // Constructor/Destructor
  E_DLL0 CONSTRUCTOR E_DLL1  EKernel( );
  E_DLL0 CONSTRUCTOR E_DLL1  EKernel( INT16 n16SizeX, INT16 n16SizeY, FLOAT32 f32Gain, UINT32 un32Offset, INT16 n16Rectifier, UINT32 un32OutsideValue);
  E_DLL0 CONSTRUCTOR E_DLL1  EKernel( enum KERNEL_TYPE KernelType);
  virtual E_DLL0 DESTRUCTOR E_DLL1  ~EKernel( );
  
  // EKernel access functions
  E_DLL0 INT16 E_DLL1  GetSizeX( );
  E_DLL0 INT16 E_DLL1  GetSizeY( );
  E_DLL0 FLOAT32 E_DLL1  GetGain( );
  E_DLL0 UINT32 E_DLL1  GetOffset( );
  E_DLL0 INT16 E_DLL1  GetRectifier( );
  E_DLL0 UINT32 E_DLL1  GetOutsideValue( );
  E_DLL0 FLOAT32* E_DLL1  GetDataPtr( );
  E_DLL0 UINT32 E_DLL1  GetAllocatedSize( );
  E_DLL0 INT16 E_DLL1  GetKernelData( INT32 n32DataX, INT32 n32DataY, FLOAT32& f32Data);
  
  E_DLL0 INT16 E_DLL1  SetKernel( enum KERNEL_TYPE Krnl);
  E_DLL0 INT16 E_DLL1  SetKernelData( INT32 n32DataX, INT32 n32DataY, FLOAT32 f32Data);
  
  E_DLL0 INT16 E_DLL1  SetKernelData( 
    FLOAT32 f32Data00, FLOAT32 f32Data10, FLOAT32 f32Data20,
    FLOAT32 f32Data01, FLOAT32 f32Data11, FLOAT32 f32Data21, 
    FLOAT32 f32Data02, FLOAT32 f32Data12, FLOAT32 f32Data22);
  
  E_DLL0 INT16 E_DLL1  SetKernelData( 
    FLOAT32 f32Data00, FLOAT32 f32Data10, FLOAT32 f32Data20, FLOAT32 f32Data30, FLOAT32 f32Data40, 
    FLOAT32 f32Data01, FLOAT32 f32Data11, FLOAT32 f32Data21, FLOAT32 f32Data31, FLOAT32 f32Data41, 
    FLOAT32 f32Data02, FLOAT32 f32Data12, FLOAT32 f32Data22, FLOAT32 f32Data32, FLOAT32 f32Data42, 
    FLOAT32 f32Data03, FLOAT32 f32Data13, FLOAT32 f32Data23, FLOAT32 f32Data33, FLOAT32 f32Data43, 
    FLOAT32 f32Data04, FLOAT32 f32Data14, FLOAT32 f32Data24, FLOAT32 f32Data34, FLOAT32 f32Data44);
  
  E_DLL0 INT16 E_DLL1  SetKernelData( 
    FLOAT32 f32Data00, FLOAT32 f32Data10, FLOAT32 f32Data20, FLOAT32 f32Data30, FLOAT32 f32Data40, FLOAT32 f32Data50, FLOAT32 f32Data60, 
    FLOAT32 f32Data01, FLOAT32 f32Data11, FLOAT32 f32Data21, FLOAT32 f32Data31, FLOAT32 f32Data41, FLOAT32 f32Data51, FLOAT32 f32Data61, 
    FLOAT32 f32Data02, FLOAT32 f32Data12, FLOAT32 f32Data22, FLOAT32 f32Data32, FLOAT32 f32Data42, FLOAT32 f32Data52, FLOAT32 f32Data62, 
    FLOAT32 f32Data03, FLOAT32 f32Data13, FLOAT32 f32Data23, FLOAT32 f32Data33, FLOAT32 f32Data43, FLOAT32 f32Data53, FLOAT32 f32Data63, 
    FLOAT32 f32Data04, FLOAT32 f32Data14, FLOAT32 f32Data24, FLOAT32 f32Data34, FLOAT32 f32Data44, FLOAT32 f32Data54, FLOAT32 f32Data64,
    FLOAT32 f32Data05, FLOAT32 f32Data15, FLOAT32 f32Data25, FLOAT32 f32Data35, FLOAT32 f32Data45, FLOAT32 f32Data55, FLOAT32 f32Data65, 
    FLOAT32 f32Data06, FLOAT32 f32Data16, FLOAT32 f32Data26, FLOAT32 f32Data36, FLOAT32 f32Data46, FLOAT32 f32Data56, FLOAT32 f32Data66);
  
  E_DLL0 INT16 E_DLL1  SetSizeX( INT16 n16SizeX);
  E_DLL0 INT16 E_DLL1  SetSizeY( INT16 n16SizeY);
  E_DLL0 INT16 E_DLL1  SetAllocatedSize( UINT32 n32AllocatedSize);
  E_DLL0 void E_DLL1  SetGain( FLOAT32 f32Gain);
  E_DLL0 void E_DLL1  SetOffset( UINT32 un32Offset);
  E_DLL0 void E_DLL1  SetRectifier( INT16 n16Rectifier);
  E_DLL0 void E_DLL1  SetOutsideValue( UINT32 un32OutsideValue);
};

////////////////////////////////////////////////////////////////////////////////////////////////////
// EMovingAverage class

class EMovingAverage
{
  // Wrapping members
public:
  int handle_;
  FinalizeCallback callback_;

private:
  UINT32 m_un32Period, m_un32Power;
  INT32 m_n32New, m_n32NumImages;
  BOOL m_bInternal;
  EImageBW8** m_pStore;
  EImageBW16 m_Accumulator;
  
public:
  // Constructor/destructor
  E_DLL0 CONSTRUCTOR E_DLL1  EMovingAverage( );
  E_DLL0 CONSTRUCTOR E_DLL1  EMovingAverage( UINT32 un32Period, INT32 n32Width, INT32 n32Height, BOOL bInternal = TRUE);
  virtual E_DLL0 DESTRUCTOR E_DLL1  ~EMovingAverage( );
  
  // Dimensioning
  E_DLL0 void E_DLL1  SetSize( UINT32 un32Period, INT32 n32Width, INT32 n32Height, BOOL bInternal = TRUE);
  E_DLL0 void E_DLL1  GetSize( UINT32& un32Period, INT32& n32Width, INT32& n32Height, BOOL& bInternal);
  
  // Integration
  E_DLL0 void E_DLL1  Reset( );
  E_DLL0 EImageBW8* E_DLL1  GetSrcImage( );
  E_DLL0 void E_DLL1  Average( EROIBW8* pDst);
  E_DLL0 void E_DLL1  Average( EROIBW8* pSrc, EROIBW8* pDst);
};

////////////////////////////////////////////////////////////////////////////////////////////////////
// Special types
//

// Gradient vectors
typedef struct
{
  INT8 n8GX, n8GY;
} EGradient16;


typedef struct
{
  INT16 n16GX, n16GY;
} EGradient32;


typedef struct
{
  INT16 n16GX0, n16GY0, n16GX1, n16GY1, n16GX2, n16GY2;
} EColorGradient32;


////////////////////////////////////////////////////////////////////////////////////////////////////
// Vector class instances
//

#if defined E_BC45 || defined E_BC50 || defined E_BCB
  // Forward declarations of class instances
  template<class Type> class EVectorTemplate;
  template class E_DLL1 EVectorTemplate<UINT32>;
  template class E_DLL1 EVectorTemplate<EPath>;
  template class E_DLL1 EVectorTemplate<EBW8Path>;
  template class E_DLL1 EVectorTemplate<EBW16Path>;
  template class E_DLL1 EVectorTemplate<EC24Path>;
  template class E_DLL1 EVectorTemplate<EPeak>;
#endif

class EPathVector : public EVectorTemplate<EPath>
{
  // Wrapping members
public:
  int handle_;
  FinalizeCallback callback_;

public:
  // Mandated to avoid confusion with the copy constructor
  E_DLL0 CONSTRUCTOR E_DLL1  EPathVector( ) { m_bClosed = FALSE; }
  E_DLL0 CONSTRUCTOR E_DLL1  EPathVector( UINT32 un32MaxElements);

  // Closed path
  E_DLL0 BOOL E_DLL1  GetClosed( ) { return m_bClosed; }
  E_DLL0 void E_DLL1  SetClosed( BOOL bClosed) { m_bClosed = bClosed; }

  E_DLL0 void E_DLL1  Draw( HDC hDC, 
    FLOAT32 f32ZoomX = 1.f, FLOAT32 f32ZoomY = 0.f, FLOAT32 f32PanX = 0.f, FLOAT32 f32PanY = 0.f);

  E_DLL0 void E_DLL1  Draw( Euresys::DrawAdapter* drawAdapter, 
    FLOAT32 f32ZoomX = 1.f, FLOAT32 f32ZoomY = 0.f, FLOAT32 f32PanX = 0.f, FLOAT32 f32PanY = 0.f);

protected:
  BOOL m_bClosed;
};

class EBW8PathVector : public EVectorTemplate<EBW8Path>
{
  // Wrapping members
public:
  int handle_;
  FinalizeCallback callback_;

public:
  // Mandated to avoid confusion with the copy constructor
  E_DLL0 CONSTRUCTOR E_DLL1  EBW8PathVector( ) 
  { 
    handle_ = 0;
    callback_ = 0;
    m_bClosed = FALSE; 
  }
  E_DLL0 CONSTRUCTOR E_DLL1  EBW8PathVector( UINT32 un32MaxElements);
  
  // Closed path
  E_DLL0 BOOL E_DLL1  GetClosed( ) { return m_bClosed; }
  E_DLL0 void E_DLL1  SetClosed( BOOL bClosed) { m_bClosed = bClosed; }

  E_DLL0 void E_DLL1  Draw( HDC hDC, 
    FLOAT32 f32ZoomX = 1.f, FLOAT32 f32ZoomY = 0.f, FLOAT32 f32PanX = 0.f, FLOAT32 f32PanY = 0.f);

  E_DLL0 void E_DLL1  Draw( Euresys::DrawAdapter* drawAdapter, 
    FLOAT32 f32ZoomX = 1.f, FLOAT32 f32ZoomY = 0.f, FLOAT32 f32PanX = 0.f, FLOAT32 f32PanY = 0.f);

protected:
  BOOL m_bClosed;
};

class EBW16PathVector : public EVectorTemplate<EBW16Path>
{
  // Wrapping members
public:
  int handle_;
  FinalizeCallback callback_;

public:
  // Mandated to avoid confusion with the copy constructor
  E_DLL0 CONSTRUCTOR E_DLL1  EBW16PathVector( ) 
  { 
    handle_ = 0;
    callback_ = 0;
    m_bClosed = FALSE; 
  }
  E_DLL0 CONSTRUCTOR E_DLL1  EBW16PathVector( UINT32 un32MaxElements);
  
  // Closed path
  E_DLL0 BOOL E_DLL1  GetClosed( ) { return m_bClosed; }
  E_DLL0 void E_DLL1  SetClosed( BOOL bClosed) { m_bClosed = bClosed; }

  E_DLL0 void E_DLL1  Draw( HDC hDC, 
    FLOAT32 f32ZoomX = 1.f, FLOAT32 f32ZoomY = 0.f, FLOAT32 f32PanX = 0.f, FLOAT32 f32PanY = 0.f);

  E_DLL0 void E_DLL1  Draw( Euresys::DrawAdapter* drawAdapter, 
    FLOAT32 f32ZoomX = 1.f, FLOAT32 f32ZoomY = 0.f, FLOAT32 f32PanX = 0.f, FLOAT32 f32PanY = 0.f);

protected:
  BOOL m_bClosed;
};

class EC24PathVector : public EVectorTemplate<EC24Path>
{
  // Wrapping members
public:
  int handle_;
  FinalizeCallback callback_;

public:
  // Mandated to avoid confusion with the copy constructor
  E_DLL0 CONSTRUCTOR E_DLL1  EC24PathVector( ) 
  { 
    handle_ = 0;
    callback_ = 0;
    m_bClosed = FALSE; 
  }
  E_DLL0 CONSTRUCTOR E_DLL1  EC24PathVector( UINT32 un32MaxElements);

  // Closed path
  E_DLL0 BOOL E_DLL1  GetClosed( ) { return m_bClosed; }
  E_DLL0 void E_DLL1  SetClosed( BOOL bClosed) { m_bClosed = bClosed; }
  
  E_DLL0 void E_DLL1  Draw( HDC hDC,
    FLOAT32 f32ZoomX = 1.f, FLOAT32 f32ZoomY = 0.f, FLOAT32 f32PanX = 0.f, FLOAT32 f32PanY = 0.f);

  E_DLL0 void E_DLL1  Draw( Euresys::DrawAdapter* drawAdapter,
    FLOAT32 f32ZoomX = 1.f, FLOAT32 f32ZoomY = 0.f, FLOAT32 f32PanX = 0.f, FLOAT32 f32PanY = 0.f);

protected:
  BOOL m_bClosed;
};

class EPeaksVector : public EVectorTemplate<EPeak>
{
  // Wrapping members
public:
  int handle_;
  FinalizeCallback callback_;

public:
  E_DLL0 CONSTRUCTOR E_DLL1  EPeaksVector( ) 
  {
    handle_ = 0;
    callback_ = 0;
  }
  
  // Mandated to avoid confusion with the copy constructor
  E_DLL0 CONSTRUCTOR E_DLL1  EPeaksVector( UINT32 un32MaxElements) {m_un32MaxElements = un32MaxElements;};
};

// + OBSOLETE after 6.1
#define EBW8HistogramVector EBWHistogramVector
// - OBSOLETE after 6.1

class EBWHistogramVector : public EVectorTemplate<UINT32>, EPlot
{
  // Wrapping members
public:
  int handle_;
  FinalizeCallback callback_;

protected:
  // Mandated to avoid clash with EBW32Vector
  static UINT32 m_PlaceHolder;
  static UINT8 m_un8Signature, m_un8Version;
  
public:
  // Mandated to avoid confusion with the copy constructor
  E_DLL0 CONSTRUCTOR E_DLL1  EBWHistogramVector( ) 
  {
    handle_ = 0;
    callback_ = 0;
  }
  E_DLL0 CONSTRUCTOR E_DLL1  EBWHistogramVector( UINT32 un32MaxElements);

  // Initialization
  E_DLL0 void E_DLL1  Clear( );
  
  // Statistics
  E_DLL0 FLOAT32 E_DLL1  Entropy( UINT32 un32MinIndex = 0, UINT32 un32MaxIndex = ~0);
  
  E_DLL0 void E_DLL1  EBWHistogramVector::Draw( HDC hDC, FLOAT32 f32Width, FLOAT32 f32Height, FLOAT32 f32OrgX = 0.f, FLOAT32 f32OrgY = 0.f);
  E_DLL0 void E_DLL1  EBWHistogramVector::Draw( Euresys::DrawAdapter* drawAdapter, FLOAT32 f32Width, FLOAT32 f32Height, FLOAT32 f32OrgX = 0.f, FLOAT32 f32OrgY = 0.f);
};

class EPyramid
{
  // Wrapping members
public:
  int handle_;
  FinalizeCallback callback_;

public:
  // Mandated to avoid confusion with the copy constructor
  E_DLL0 CONSTRUCTOR E_DLL1  EPyramid( );
  E_DLL0 DESTRUCTOR E_DLL1  ~EPyramid( );
  
  // Setup
  E_DLL0 void   E_DLL1  SetReductionMode(enum IMG_PYRAMIDAL_REDUCTION_MODE eMode);
  E_DLL0 enum IMG_PYRAMIDAL_REDUCTION_MODE E_DLL1  GetReductionMode( );
  E_DLL0 void E_DLL1  SetNumLevels( UINT32 un32NumLevels, enum E_IMAGE_TYPES eImageType);
  E_DLL0 UINT32 E_DLL1  GetNumLevels( );
  E_DLL0 enum E_IMAGE_TYPES GetImageType( );

  E_DLL0 BOOL E_DLL1  GetDropOdd( ) { return m_bDropOdd; }
  E_DLL0 void E_DLL1  SetDropOdd( BOOL bDropOdd) { m_bDropOdd = bDropOdd; }

  E_DLL0 void E_DLL1  Build( );
  E_DLL0 void E_DLL1  Build(const EROIBW8* pSrc);

  // Queries
  E_DLL0 EGenericROI* E_DLL1  GetImage( UINT32 un32LevelIndex);

protected:
  // Serialization
  static const UINT8 m_un8Signature, m_un8Version;

  // Parameters
  enum IMG_PYRAMIDAL_REDUCTION_MODE m_eMode;
  enum E_IMAGE_TYPES m_eImageType;
  UINT32 m_un32NumLevels;

  // Storage
  EGenericROI** m_ppArray;
  
  BOOL m_bDropOdd; 

  E_DLL0 void E_DLL1  Halve( EROIBW8* pSrc, EROIBW8* pDst, BOOL bDropOdd);
  E_DLL0 void E_DLL1  Halve( EROIBW32* pSrc, EROIBW32* pDst, BOOL bDropOdd);
};

////////////////////////////////////////////////////////////////////////////////////////////////////
// Edge Detection
//
//Gray Level
E_DLL0 void E_DLL1 ImgCannyDetector(EROIBW8* pSrc, EROIBW8* pDst, enum SMOOTH_MODE eSmoothMode, enum EDGE_FOLLOWING_MODE eEdgeMode);
E_DLL0 void E_DLL1 NonMaximaSuppression(EROIBW32* pGradient32, EROIBW32* pAngle32, EROIBW8* pNonMaximaSupp);
E_DLL0 void E_DLL1 ContourGrowing(EROIBW8* pGradient, EROIBW8* pDst, EROIBW32* pAngle, UINT8 Threshold);
E_DLL0 void E_DLL1 Hysteresis(EROIBW8* pGradient, EROIBW8* pDst, EImageBW32* pAngle, UINT8 lowThreshold, UINT8 highThreshold);



//////////////////////////////////////////////////////////////////////////
//Anisotropic diffusion
//
//GrayLEvel
E_DLL0 void E_DLL1 ImgAnisotropicDiffusion(EROIBW8* pSrc, EROIBW8* pDst, UINT32 numIterations, UINT8 morphStructElementSize);




////////////////////////////////////////////////////////////////////////////////////////////////////
// Functions
//

E_DLL0 void E_DLL1  ImgSetOverlayColor( EC24 c24Color);
E_DLL0 EC24 E_DLL1  ImgGetOverlayColor( );

////////////////////////////////////////////////////////////////////////////////////////////////////
// Arithmetic and logical operations
//
//Binary BW1
E_DLL0 void E_DLL1  ImgCopy( EBW1 bw1Const, EROIBW1* pDst);
E_DLL0 void E_DLL1  ImgCopy( const EROIBW1* pSrc, EROIBW1* pDst);
E_DLL0 void E_DLL1  ImgCopyAligned( EBW1 bw1Const, EROIBW1* pDst);
E_DLL0 void E_DLL1  ImgCopyAligned(const EROIBW1* pSrc, EROIBW1* pDst);
E_DLL0 void E_DLL1  ImgOper( enum ARITH_LOGIC_OPERATIONS eOperation, EBW1 bw1Const, EROIBW1* pDst);
E_DLL0 void E_DLL1  ImgOper( enum ARITH_LOGIC_OPERATIONS eOperation, const EROIBW1* pSrc, EROIBW1* pDst);
E_DLL0 void E_DLL1  ImgOper( enum ARITH_LOGIC_OPERATIONS eOperation, const EROIBW1* pSrc0, const EROIBW1* pSrc1, EROIBW1* pDst);
E_DLL0 void E_DLL1  ImgOperAligned( enum ARITH_LOGIC_OPERATIONS eOperation, EBW1 bw1Const, EROIBW1* pDst);
E_DLL0 void E_DLL1  ImgOperAligned( enum ARITH_LOGIC_OPERATIONS eOperation, const EROIBW1* pSrc, EROIBW1* pDst);
E_DLL0 void E_DLL1  ImgOperAligned( enum ARITH_LOGIC_OPERATIONS eOperation, const EROIBW1* pSrc0, const EROIBW1* pSrc1, EROIBW1* pDst);

// Gray-level
E_DLL0 void E_DLL1  ImgCopy( EBW8 bw8Const, EROIBW8* pDst);
E_DLL0 void E_DLL1  ImgCopy( EROIBW8* pSrc, EROIBW8* pDst);

E_DLL0 void E_DLL1  ImgOper( enum ARITH_LOGIC_OPERATIONS eOperation, EBW8 bw8Const, EROIBW8* pDst);
E_DLL0 void E_DLL1  ImgOper( enum ARITH_LOGIC_OPERATIONS eOperation, const EROIBW8* pSrc, EROIBW8* pDst);
E_DLL0 void E_DLL1  ImgOper( enum ARITH_LOGIC_OPERATIONS eOperation, EBW8 bw8Const, const EROIBW8* pSrc, EROIBW8* pDst);
E_DLL0 void E_DLL1  ImgOper( enum ARITH_LOGIC_OPERATIONS eOperation, const EROIBW8* pSrc, EBW8 bw8Const, EROIBW8* pDst);
E_DLL0 void E_DLL1  ImgOper( enum ARITH_LOGIC_OPERATIONS eOperation, const EROIBW8* pSrc0, const EROIBW8* pSrc1, EROIBW8* pDst);

// 16 bits gray-level
E_DLL0 void E_DLL1  ImgCopy( EBW16 bw16Const, EROIBW16* pDst);
E_DLL0 void E_DLL1  ImgCopy( EROIBW16* pSrc, EROIBW16* pDst);

E_DLL0 void E_DLL1  ImgOper( enum ARITH_LOGIC_OPERATIONS eOperation, EBW16 bw16Const, EROIBW16* pDstImage);
E_DLL0 void E_DLL1  ImgOper( enum ARITH_LOGIC_OPERATIONS eOperation, EROIBW16* pSrc, EROIBW16* pDstImage);
E_DLL0 void E_DLL1  ImgOper( enum ARITH_LOGIC_OPERATIONS eOperation, EBW16 bw16Const, EROIBW16* pSrc, EROIBW16* pDst);
E_DLL0 void E_DLL1  ImgOper( enum ARITH_LOGIC_OPERATIONS eOperation, EROIBW16* pSrc, EBW16 bw16Const, EROIBW16* pDst);
E_DLL0 void E_DLL1  ImgOper( enum ARITH_LOGIC_OPERATIONS eOperation, EROIBW16* pSrc0, EROIBW16* pSrc1, EROIBW16* pDst);

E_DLL0 void E_DLL1  ImgOper( enum ARITH_LOGIC_OPERATIONS eOperation, EROIBW8* pSrc0Image, EROIBW8* pSrc1Image, EROIBW16* pDstImage);
E_DLL0 void E_DLL1  ImgOper( enum ARITH_LOGIC_OPERATIONS eOperation, EROIBW16* pSrc0Image, EROIBW8* pSrc1Image, EROIBW16* pDstImage);

// 32 bits gray-level
E_DLL0 void E_DLL1  ImgCopy( EBW32 bw16Const, EROIBW32* pDst);
E_DLL0 void E_DLL1  ImgCopy( EROIBW32* pSrc, EROIBW32* pDst);

// Color
E_DLL0 void E_DLL1  ImgCopy( EC24 c24Const, EROIC24* pDst);
E_DLL0 void E_DLL1  ImgCopy( EROIC24* pSrc, EROIC24* pDst);

E_DLL0 void E_DLL1  ImgCopy( EC15 c15Const, EROIC15* pDst);
E_DLL0 void E_DLL1  ImgCopy( EROIC15* pSrc, EROIC15* pDst);

E_DLL0 void E_DLL1  ImgCopy( EC16 c16Const, EROIC16* pDst);
E_DLL0 void E_DLL1  ImgCopy( EROIC16* pSrc, EROIC16* pDst);

E_DLL0 void E_DLL1  ImgOper( enum ARITH_LOGIC_OPERATIONS eOperation, EC24 c24Const, EROIC24* pDst);
E_DLL0 void E_DLL1  ImgOper( enum ARITH_LOGIC_OPERATIONS eOperation, EROIC24* pSrc, EROIC24* pDst);
E_DLL0 void E_DLL1  ImgOper( enum ARITH_LOGIC_OPERATIONS eOperation, EC24 c24Const, EROIC24* pSrc, EROIC24* pDst);
E_DLL0 void E_DLL1  ImgOper( enum ARITH_LOGIC_OPERATIONS eOperation, EROIC24* pSrc, EC24 c24Const, EROIC24* pDst);
E_DLL0 void E_DLL1  ImgOper( enum ARITH_LOGIC_OPERATIONS eOperation, EROIC24* pSrc0, EROIC24* pSrc1, EROIC24* pDst);

// Color overlay
E_DLL0 void E_DLL1  ImgOverlay( EROIC24* pSrc, EROIC16* pDst, INT32 n32PanX, INT32 n32PanY, EC24 c24Ref);
E_DLL0 void E_DLL1  ImgOverlay( EROIC24* pSrc, EROIC15* pDst, INT32 n32PanX, INT32 n32PanY, EC24 c24Ref);
E_DLL0 void E_DLL1  ImgOverlay( EROIC24* pSrc, EROIC24* pDst, INT32 n32PanX, INT32 n32PanY, EC24 c24Ref);

E_DLL0 void E_DLL1  ImgOverlay( EROIBW8* pSrc, EROIC24* pOverlay, EROIC24* pDst, INT32 n32PanX, INT32 n32PanY, EC24 c24Ref);

// Mixed
E_DLL0 void E_DLL1  ImgOper( enum ARITH_LOGIC_OPERATIONS eOperation, EROIBW8* pSrc, EROIC24* pDst);
E_DLL0 void E_DLL1  ImgOper( enum ARITH_LOGIC_OPERATIONS eOperation, EROIBW8* pSrc0, EROIBW8* pSrc1, EROIC24* pDst);
E_DLL0 void E_DLL1  ImgOper( enum ARITH_LOGIC_OPERATIONS eOperation, EROIBW8* pSrc0, EROIC24* pSrc1, EROIC24* pDst);
E_DLL0 void E_DLL1  ImgOper( enum ARITH_LOGIC_OPERATIONS eOperation, EROIC24* pSrc0, EROIBW8* pSrc1, EROIC24* pDst);

// Extended arithmetic
E_DLL0 INT16 E_DLL1  ImgOper1c2( enum ARITH_LOGIC_OPERATIONS nOperation, EROIBW8 *pSrcImage, UINT16 un16Const, EImageBW16 *pDstImage);
E_DLL0 INT16 E_DLL1  ImgOper1c2( enum ARITH_LOGIC_OPERATIONS nOperation, EImageBW16 *pSrcImage, UINT16 un16Const, EImageBW16 *pDstImage);
E_DLL0 INT16 E_DLL1  ImgOper1c2( enum ARITH_LOGIC_OPERATIONS nOperation, EImageBW16 *pSrcImage, UINT16 un16Const, EROIBW8 *pDstImage);
E_DLL0 INT16 E_DLL1  ImgOper123( enum ARITH_LOGIC_OPERATIONS nOperation, EROIBW8 *pSrc1Image, EROIBW8 *pSrc2Image, EImageBW16 *pDstImage);
E_DLL0 INT16 E_DLL1  ImgOper123( enum ARITH_LOGIC_OPERATIONS nOperation, EImageBW16 *pSrc1Image, EImageBW16 *pSrc2Image, EImageBW16 *pDstImage);
E_DLL0 INT16 E_DLL1  ImgOper123( enum ARITH_LOGIC_OPERATIONS nOperation, EROIBW8 *pSrc1Image, EImageBW16 *pSrc2Image, EImageBW16 *pDstImage);
E_DLL0 INT16 E_DLL1  ImgOper123( enum ARITH_LOGIC_OPERATIONS nOperation, EImageBW16 *pSrc1Image, EROIBW8 *pSrc2Image, EImageBW16 *pDstImage);


///////////////////////////////////////////////////////////////////////////////////////////////////
//BW1 alignment/unalignment
//
E_DLL0 void E_DLL1 ImgBW1Alignment(const EROIBW1* pSrc, EROIBW1* pDst);
E_DLL0 void E_DLL1 ImgBW1UnAlignment(EROIBW1* pSrc, EROIBW1* pDst);


////////////////////////////////////////////////////////////////////////////////////////////////////
// Conversions
//

E_DLL0 void E_DLL1  ImgConvert( EROIBW32* pSrcImage, EROIBW16* pDstImage, UINT32 un32NumScalingBits = 16);
E_DLL0 void E_DLL1  ImgConvert( EROIBW32* pSrcImage, EROIBW8* pDstImage, UINT32 un32NumScalingBits = 24);
E_DLL0 void E_DLL1  ImgConvert( EROIBW16* pSrcImage, EROIBW8* pDstImage, UINT32 un32NumScalingBits = 8);
E_DLL0 void E_DLL1  ImgConvert( EROIC24* pSrcImage, EROIBW8* pDstImage);

E_DLL0 void E_DLL1  ImgConvert( EROIBW8* pSrcImage, EROIBW16* pDstImage, UINT32 un32NumScalingBits = 8);
E_DLL0 void E_DLL1  ImgConvert( EROIBW8* pSrcImage, EROIBW32* pDstImage, UINT32 un32NumScalingBits = 24);
E_DLL0 void E_DLL1  ImgConvert( EROIBW8* pSrcImage, EROIC24* pDstImage);
E_DLL0 void E_DLL1  ImgConvert( EROIBW16* pSrcImage, EROIBW32* pDstImage, UINT32 un32NumScalingBits = 16);
E_DLL0 void E_DLL1  ImgConvert( EROIC24* pSrc, EROIC15* pDst);
E_DLL0 void E_DLL1  ImgConvert( EROIC15* pSrc, EROIC24* pDst);
E_DLL0 void E_DLL1  ImgConvert( EROIBW8* pSrc, EROIC15* pDst);
E_DLL0 void E_DLL1  ImgConvert( EROIC15* pSrc, EROIBW8* pDst);
E_DLL0 void E_DLL1  ImgConvert( EROIC24* pSrc, EROIC16* pDst);
E_DLL0 void E_DLL1  ImgConvert( EROIC16* pSrc, EROIC24* pDst);
E_DLL0 void E_DLL1  ImgConvert( EROIBW8* pSrc, EROIC16* pDst);
E_DLL0 void E_DLL1  ImgConvert( EROIC16* pSrc, EROIBW8* pDst);
E_DLL0 void E_DLL1  ImgConvert( EROIC24* pSrc, EROIC24A* pDst);
E_DLL0 void E_DLL1  ImgConvert( EROIC24A* pSrc, EROIC24* pDst);
E_DLL0 void E_DLL1  ImgConvert( EROIC24* pSrc, EROIBW8* pSrcAlpha, EROIC24A* pDst);
E_DLL0 void E_DLL1  ImgConvert( EROIC24A* pSrc, EROIC24* pDst, EROIBW8* pDstAlpha);
E_DLL0 void E_DLL1  ImgConvert( EROIFLOAT32* pSrc, EROIBW8* pDst);
E_DLL0 void E_DLL1  ImgConvert( EROIFLOAT32* pSrc, EROIBW16* pDst);
E_DLL0 void E_DLL1  ImgConvert( EROIFLOAT32* pSrc, EROIBW32* pDst);
E_DLL0 void E_DLL1  ImgConvert( EROIBW8* pDst,  EROIFLOAT32* pSrc);
E_DLL0 void E_DLL1  ImgConvert( EROIBW16* pDst, EROIFLOAT32* pSrc);
E_DLL0 void E_DLL1  ImgConvert( EROIBW32* pDst, EROIFLOAT32* pSrc);
E_DLL0 void E_DLL1  ImgConvert( EROIFLOAT64* pSrc, EROIBW8* pDst);
E_DLL0 void E_DLL1  ImgConvert( EROIFLOAT64* pSrc, EROIBW16* pDst);
E_DLL0 void E_DLL1  ImgConvert( EROIFLOAT64* pSrc, EROIBW32* pDst);
E_DLL0 void E_DLL1  ImgConvert( EROIBW8* pDst,  EROIFLOAT64* pSrc);
E_DLL0 void E_DLL1  ImgConvert( EROIBW16* pDst, EROIFLOAT64* pSrc);
E_DLL0 void E_DLL1  ImgConvert( EROIBW32* pDst, EROIFLOAT64* pSrc);

E_DLL0 void E_DLL1  ImgConvert( EROIBW8* pSrcImage, EROIBW1* pDstImage);
E_DLL0 void E_DLL1  ImgConvert( EROIBW16* pSrcImage, EROIBW1* pDstImage);
E_DLL0 void E_DLL1  ImgConvert( EROIBW32* pSrcImage, EROIBW1* pDstImage);
E_DLL0 void E_DLL1  ImgConvert( EROIBW1* pSrc, EROIBW8* pDst, UINT8 un8HighValue = UINT8_MAX);
E_DLL0 void E_DLL1  ImgConvert( EROIBW1* pSrc, EROIBW16* pDst, UINT16 un16HighValue = UINT16_MAX);
E_DLL0 void E_DLL1  ImgConvert( EROIBW1* pSrc, EROIBW32* pDst, UINT32 un32HighValue = UINT32_MAX);

E_DLL0 void E_DLL1  ImgConvertAligned( EROIBW8* pSrcImage, EROIBW1* pDstImage);
E_DLL0 void E_DLL1  ImgConvertAligned( EROIBW16* pSrcImage, EROIBW1* pDstImage);
E_DLL0 void E_DLL1  ImgConvertAligned( EROIBW32* pSrcImage, EROIBW1* pDstImage);
E_DLL0 void E_DLL1  ImgConvertAligned( EROIBW1* pSrc, EROIBW8* pDst, UINT8 un8HighValue = UINT8_MAX);
E_DLL0 void E_DLL1  ImgConvertAligned( EROIBW1* pSrc, EROIBW16* pDst, UINT16 un16HighValue = UINT16_MAX);
E_DLL0 void E_DLL1  ImgConvertAligned( EROIBW1* pSrc, EROIBW32* pDst, UINT32 un32HighValue = UINT32_MAX);

E_DLL0 void E_DLL1  ImgConvertTo422( EROIBW8* pSrcImage, EROIBW16* pDstImage);


////////////////////////////////////////////////////////////////////////////////////////////////////
// Gray-level transforms 
//
// BW8
E_DLL0 void E_DLL1  ImgGainOffset( EROIBW8* pSrcImage, EROIBW8* pDstImage, FLOAT32 f32Gain = 1.f, FLOAT32 f32Offset = 0.f);

E_DLL0 void E_DLL1  ImgTransform
( EROIBW8* pSrcImage, EROIBW8* pDstImage, 
 EBW8 ( *Transform)( EBW8 bw8Src), BOOL bUseLUT = TRUE);

E_DLL0 void E_DLL1  ImgLut( const EROIBW8* pSrcImage, EROIBW8* pDstImage, EBW8* pBW8Lut);
E_DLL0 void E_DLL1  ImgLut( const EROIBW8* pSrcImage, EROIBW8* pDstImage, EBW8Vector* pLut);

E_DLL0 INT16 E_DLL1  ImgNormalize( EROIBW8* pSrcImage, EROIBW8* pDstImage, FLOAT32 f32NewAverage, FLOAT32 f32NewStdDev);

E_DLL0 void E_DLL1  ImgUniformize
( EROIBW8* pSrc, 
 EBW8 bw8Reference, EROIBW8* pReference,
 EROIBW8* pDst, 
 BOOL bMultiplicative = TRUE);

E_DLL0 void E_DLL1  ImgUniformize
( EROIBW8* pSrc,
 EBW8 bw8LightReference, EROIBW8* pLightReference, 
 EBW8 bw8DarkReference, EROIBW8* pDarkReference, 
 EROIBW8* pDst);

E_DLL0 void E_DLL1  ImgUniformize
( EROIBW8* pSrc, 
 EBW8 bw8Reference, EBW8Vector* pReference,
 EROIBW8* pDst, 
 BOOL bMultiplicative = TRUE);

E_DLL0 void E_DLL1  ImgUniformize
( EROIBW8* pSrc,
 EBW8 bw8LightReference, EBW8Vector* pLightReference, 
 EBW8 bw8DarkReference, EBW8Vector* pDarkReference, 
 EROIBW8* pDst);

E_DLL0 void E_DLL1  ImgSetRecursiveAverageLUT( EBW16Vector* pLUT, FLOAT32 f32Reduction, FLOAT32 f32Width = 0.f);
E_DLL0 void E_DLL1  ImgRecursiveAverage( EROIBW8* pSrc, EROIBW16* pStore, EROIBW8* pDst, EBW16Vector* pLUT);

// BW16
E_DLL0 void E_DLL1  ImgGainOffset( EROIBW16* pSrcImage, EROIBW16* pDstImage, FLOAT32 f32Gain = 1.f, FLOAT32 f32Offset = 0.f);

E_DLL0 void E_DLL1  ImgTransform
( EROIBW16* pSrcImage, EROIBW16* pDstImage, 
 EBW16 ( *Transform)( EBW16 bw16Src));

E_DLL0 void E_DLL1  ImgLut( EROIBW16* pSrcImage, EROIBW16* pDstImage, EBW16* pBW16Lut);
E_DLL0 void E_DLL1  ImgLut( EROIBW16* pSrcImage, EROIBW16* pDstImage, EBW16Vector* pLut);
E_DLL0 void E_DLL1  ImgLut( EROIBW16* pSrcImage, EROIBW8* pDstImage, EBW8Vector* pLut, UINT32 un32NumScalingBits = ~0);

E_DLL0 void E_DLL1  ImgNormalize( EROIBW16* pSrcImage, EROIBW16* pDstImage, FLOAT32 f32NewAverage, FLOAT32 f32NewStdDev);

E_DLL0 void E_DLL1  ImgUniformize
( EROIBW16* pSrc, 
 EBW16 bw16Reference, EROIBW16* pReference,
 EROIBW16* pDst, 
 BOOL bMultiplicative = TRUE);

E_DLL0 void E_DLL1  ImgUniformize
( EROIBW16* pSrc,
 EBW16 bw16LightReference, EROIBW16* pLightReference, 
 EBW16 bw16DarkReference, EROIBW16* pDarkReference, 
 EROIBW16* pDst);

E_DLL0 void E_DLL1  ImgUniformize
( EROIBW16* pSrc, 
 EBW16 bw16Reference, EBW16Vector* pReference,
 EROIBW16* pDst, 
 BOOL bMultiplicative = TRUE);

E_DLL0 void E_DLL1  ImgUniformize
( EROIBW16* pSrc,
 EBW16 bw16LightReference, EBW16Vector* pLightReference, 
 EBW16 bw16DarkReference, EBW16Vector* pDarkReference, 
 EROIBW16* pDst);

// Color
E_DLL0 void E_DLL1  ImgGainOffset( EROIC24* pSrcImage, EROIC24* pDstImage, EColor Gain = EColor( 1.f, 1.f, 1.f), EColor Offset = EColor( 0.f, 0.f, 0.f));

E_DLL0 void E_DLL1  ImgUniformize
( EROIC24* pSrc, 
 EC24 c24Reference, EROIC24* pReference,
 EROIC24* pDst, 
 BOOL bMultiplicative = TRUE);

E_DLL0 void E_DLL1  ImgUniformize
( EROIC24* pSrc,
 EC24 c24LightReference, EROIC24* pLightReference, 
 EC24 c24DarkReference, EROIC24* pDarkReference, 
 EROIC24* pDst);

E_DLL0 void E_DLL1  ImgUniformize
( EROIC24* pSrc, 
 EC24 c24Reference, EC24Vector* pReference,
 EROIC24* pDst, 
 BOOL bMultiplicative = TRUE);

E_DLL0 void E_DLL1  ImgUniformize
( EROIC24* pSrc,
 EC24 c24LightReference, EC24Vector* pLightReference, 
 EC24 c24DarkReference, EC24Vector* pDarkReference, 
 EROIC24* pDst);

////////////////////////////////////////////////////////////////////////////////////////////////////
// Thresholding
//

// Gray level to binary
E_DLL0 void E_DLL1  ImgThreshold( EROIBW8* pSrcImage, EROIBW1* pDstImage, UINT32 un32Threshold = IMG_MIN_RESIDUE_THRESHOLD, FLOAT32 f32RelativeThreshold = 0.5);
E_DLL0 void E_DLL1  ImgThreshold( EROIBW16* pSrcImage, EROIBW1* pDstImage, UINT32 un32Threshold = IMG_MIN_RESIDUE_THRESHOLD, FLOAT32 f32RelativeThreshold = 0.5);
E_DLL0 void E_DLL1  ImgThresholdAligned( EROIBW8* pSrcImage, EROIBW1* pDstImage, UINT32 un32Threshold = IMG_MIN_RESIDUE_THRESHOLD, FLOAT32 f32RelativeThreshold = 0.5);
E_DLL0 void E_DLL1  ImgThresholdAligned( EROIBW16* pSrcImage, EROIBW1* pDstImage, UINT32 un32Threshold = IMG_MIN_RESIDUE_THRESHOLD, FLOAT32 f32RelativeThreshold = 0.5);

// Gray level to gray level
E_DLL0 INT16 E_DLL1  ImgThreshold
( EROIBW8* pSrcImage, EROIBW8* pDstImage,
 UINT32 un32Threshold = IMG_MIN_RESIDUE_THRESHOLD,
 UINT8 un8LowValue = 0, UINT8 un8HighValue = 255, FLOAT32 f32RelativeThreshold = 0.5);

E_DLL0 void E_DLL1  ImgThreshold
( EROIBW16* pSrcImage, EROIBW16* pDstImage,
 UINT32 un32Threshold = IMG_MIN_RESIDUE_THRESHOLD,
 EBW16 bw16LowValue = 0, EBW16 bw16HighValue = 65535, FLOAT32 f32RelativeThreshold = 0.5);

E_DLL0 INT16 E_DLL1  ImgDoubleThreshold
( EROIBW8* pSrcImage, EROIBW8* pDstImage,
 UINT32 un32LowThreshold, UINT32 un32HighThreshold,
 UINT8 un8LowValue = 0, UINT8 un8MidValue = 127, UINT8 un8HighValue = 255);

E_DLL0 void E_DLL1  ImgDoubleThreshold
( EROIBW16* pSrcImage, EROIBW16* pDstImage,
 UINT32 un32LowThreshold, UINT32 un32HighThreshold,
 EBW16 bw16LowValue = 0, EBW16 bw16MidValue = 32767, EBW16 bw16HighValue = 65535);

// Color to gray level
E_DLL0 void E_DLL1  ImgThreshold( EROIC24* pSrc, EROIBW8* pDst, EC24 c24Min, EC24 c24Max);

class EColorLookup;
E_DLL0 void E_DLL1  ImgThreshold
( EROIC24* pSrcImage, EROIBW8* pDstImage,
 EC24 c24Min, EC24 c24Max,
 EColorLookup* pLookup,
 EBW8 un8RejectValue = 0, EBW8 un8AcceptValue = 255);


// special
inline INT16 ImgAbsoluteThreshold( EROIBW8* pSrcImage, EROIBW8* pDstImage, UINT32 threshold, UINT8 un8LowValue = 0, UINT8 un8HighValue = 255 )
{
  return ImgThreshold( pSrcImage, pDstImage, threshold,un8LowValue, un8HighValue);
}

inline INT16 ImgRelativeThreshold( EROIBW8* pSrcImage, EROIBW8* pDstImage, UINT8 un8LowValue = 0, UINT8 un8HighValue = 255, FLOAT32 f32RelativeThreshold = 0.5 )
{
  return ImgThreshold( pSrcImage, pDstImage, static_cast<UINT32>(IMG_RELATIVE_THRESHOLD),un8LowValue, un8HighValue, f32RelativeThreshold);
}

inline INT16 ImgMinResidueThreshold( EROIBW8* pSrcImage, EROIBW8* pDstImage, UINT8 un8LowValue = 0, UINT8 un8HighValue = 255 )
{
  return ImgThreshold( pSrcImage, pDstImage, static_cast<UINT32>(IMG_MIN_RESIDUE_THRESHOLD),un8LowValue, un8HighValue);
}

inline INT16 ImgMaxEntropyThreshold( EROIBW8* pSrcImage, EROIBW8* pDstImage, UINT8 un8LowValue = 0, UINT8 un8HighValue = 255 )
{
  return ImgThreshold( pSrcImage, pDstImage, static_cast<UINT32>(IMG_MAX_ENTROPY_THRESHOLD),un8LowValue, un8HighValue);
}

inline INT16 ImgIsodataThreshold( EROIBW8* pSrcImage, EROIBW8* pDstImage, UINT8 un8LowValue = 0, UINT8 un8HighValue = 255 )
{
  return ImgThreshold( pSrcImage, pDstImage, static_cast<UINT32>(IMG_ISODATA_THRESHOLD),un8LowValue, un8HighValue);
}

// special versions BW16
inline void ImgAbsoluteThreshold( EROIBW16* pSrcImage, EROIBW16* pDstImage, UINT32 threshold, UINT16 un8LowValue = 0, UINT16 un8HighValue = 65535 )
{
  ImgThreshold( pSrcImage, pDstImage, threshold,un8LowValue, un8HighValue);
}

inline void ImgRelativeThreshold( EROIBW16* pSrcImage, EROIBW16* pDstImage, UINT16 un8LowValue = 0, UINT16 un8HighValue = 65535, FLOAT32 f32RelativeThreshold = 0.5 )
{
  ImgThreshold( pSrcImage, pDstImage, static_cast<UINT32>(IMG_RELATIVE_THRESHOLD),un8LowValue, un8HighValue, f32RelativeThreshold);
}

inline void ImgMinResidueThreshold( EROIBW16* pSrcImage, EROIBW16* pDstImage, UINT16 un8LowValue = 0, UINT16 un8HighValue = 65535 )
{
  ImgThreshold( pSrcImage, pDstImage, static_cast<UINT32>(IMG_MIN_RESIDUE_THRESHOLD),un8LowValue, un8HighValue);
}

inline void ImgMaxEntropyThreshold( EROIBW16* pSrcImage, EROIBW16* pDstImage, UINT16 un8LowValue = 0, UINT16 un8HighValue = 65535 )
{
  ImgThreshold( pSrcImage, pDstImage, static_cast<UINT32>(IMG_MAX_ENTROPY_THRESHOLD),un8LowValue, un8HighValue);
}

inline void ImgIsodataThreshold( EROIBW16* pSrcImage, EROIBW16* pDstImage, UINT16 un8LowValue = 0, UINT16 un8HighValue = 65535 )
{
  ImgThreshold( pSrcImage, pDstImage, static_cast<UINT32>(IMG_ISODATA_THRESHOLD),un8LowValue, un8HighValue);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
// Automatic threshold
//
// Gray Level
E_DLL0 EBW8 E_DLL1  ImgAutoThreshold( EROIBW8* pSrc, enum IMG_THRESHOLD_MODES eThresholdMode, FLOAT32 f32RelativeThreshold = 0.5);

E_DLL0 void E_DLL1  ImgHistogramThreshold
( EBWHistogramVector* pHistogram,
 UINT32& un32Threshold,
 FLOAT32& f32AverageBlack, FLOAT32& f32AverageWhite,
 FLOAT32 f32RelativeThreshold = 0.5f,
 UINT32 un32From = 0, UINT32 un32To = 255);

E_DLL0 EBW8 E_DLL1  ImgIsodataThreshold( EBWHistogramVector* pHistogram, UINT32 un32From = 0, UINT32 un32To = 255);
E_DLL0 EBW8 E_DLL1  ImgMinResidueThreshold( EBWHistogramVector* pHistogram, FLOAT32& f32AverageBlack, FLOAT32& f32AverageWhite);
E_DLL0 EBW8 E_DLL1  ImgMaxEntropyThreshold( EBWHistogramVector* pHistogram, FLOAT32& f32AverageBlack, FLOAT32& f32AverageWhite);

E_DLL0 FLOAT32 E_DLL1 ImgTwoLevelsMinResidueThreshold( EBWHistogramVector* pHistogram, EBW8& ebw8FirstWhitePixelValue, FLOAT32& f32AverageBlack, FLOAT32& f32AverageWhite);
E_DLL0 FLOAT32 E_DLL1 ImgThreeLevelsMinResidueThreshold( EBWHistogramVector* pHistogram, EBW8& ebw8FirstGrayPixelValue, EBW8& ebw8FirstWhitePixelValue, FLOAT32& f32AverageBlack, FLOAT32& f32AverageGray, FLOAT32& f32AverageWhite);

struct ERegionDescriptor {

  UINT32  m_un32PixelMin;
  UINT32  m_un32PixelMax;
  FLOAT32 m_f32PixelMean;
  FLOAT32 m_f32PixelVariance;
  UINT32  m_un32Area;
};

E_DLL0 FLOAT32 E_DLL1 ImgMultiLevelsMinResidueThreshold( EBWHistogramVector* pHistogram, UINT32 un32NumClass, Euresys::eVision::Utils::Vector< struct ERegionDescriptor> &PixelClassDescriptor);

E_DLL0 FLOAT32 E_DLL1 ImgMultiLevelsMinResidueThreshold( EBWHistogramVector* pHistogram, UINT32 un32NumThreshold, Euresys::eVision::Utils::Vector<EBW8> &FirstPixelValue);

struct ELabelisationDescriptor {

  Euresys::eVision::Utils::Vector< struct ERegionDescriptor> m_RegionDescriptor;
  FLOAT32 m_f32Residue;

};

E_DLL0 FLOAT32 E_DLL1 ImgAllMultiLevelsMinResidueThreshold( EBWHistogramVector* pHistogram, UINT32 un32NumClass, Euresys::eVision::Utils::Vector< struct ELabelisationDescriptor> &LabelisationDescriptorVector);

E_DLL0 void E_DLL1  ImgAutoAdaptiveThreshold
( EROIBW8* pSrc, EROIBW8* pDst,
 enum IMG_THRESHOLD_MODES eThresholdMode, INT32 n32WindowWidth, INT32 n32WindowHeight = 0);

// + OBSOLETE after 4.0
E_DLL0 UINT32 E_DLL1  ImgIsodataThreshold( EVector* pHistogram, UINT32 un32From = 0, UINT32 un32To = 255);
// - OBSOLETE after 4.0

//BW16
E_DLL0 EBW16 E_DLL1  ImgAutoThreshold( EROIBW16* pSrc, enum IMG_THRESHOLD_MODES eThresholdMode, FLOAT32 f32RelativeThreshold = 0.5);

E_DLL0 EBW16 E_DLL1  ImgIsodataThresholdBW16( EBWHistogramVector* pHistogram, UINT32 un32From = 0, UINT32 un32To = 65535);

E_DLL0 void E_DLL1  ImgHistogramThresholdBW16
( EBWHistogramVector* pHistogram,
 UINT32& un32Threshold,
 FLOAT32& f32AverageBlack, FLOAT32& f32AverageWhite,
 FLOAT32 f32RelativeThreshold = 0.5f,
 UINT32 un32From = 0, UINT32 un32To = 65535);

////////////////////////////////////////////////////////////////////////////////////////////////////
// Local threshold
//

namespace Euresys
{
  namespace eVision
  {
    namespace Segmentation
    {
      E_DLL0 void E_DLL1 ImgLocalMeanThreshold( const EROIBW8* pSrcImage, EROIBW8* pDstImage, INT32 n32halfSize, INT32 n32minContrast);
    }
  }
}


////////////////////////////////////////////////////////////////////////////////////////////////////
// Convolution
//

// Gray-level

// General
E_DLL0 void E_DLL1  ImgConvolKernel( EROIBW8* pSrc, EROIBW8* pDst, EKernel* pKernel);
E_DLL0 void E_DLL1  ImgConvolSymmetricKernel( EROIBW8* pSrc, EROIBW8* pDst, EKernel* pKernel);

E_DLL0 void E_DLL1  ImgConvolKernel( EROIBW16* pSrc, EROIBW16* pDst, EKernel* pKernel);
E_DLL0 void E_DLL1  ImgConvolSymmetricKernel( EROIBW16* pSrc, EROIBW16* pDst, EKernel* pKernel);

// Low-pass
E_DLL0 void E_DLL1  ImgConvolLowpass1( EROIBW8* pSrc, EROIBW8* pDst = NULL);
E_DLL0 void E_DLL1  ImgConvolLowpass2( EROIBW8* pSrc, EROIBW8* pDst = NULL);
E_DLL0 void E_DLL1  ImgConvolLowpass3( EROIBW8* pSrc, EROIBW8* pDst = NULL);

E_DLL0 void E_DLL1  ImgConvolLowpass1( EROIBW16* pSrc, EROIBW16* pDst = NULL);
E_DLL0 void E_DLL1  ImgConvolLowpass2( EROIBW16* pSrc, EROIBW16* pDst = NULL);
E_DLL0 void E_DLL1  ImgConvolLowpass3( EROIBW16* pSrc, EROIBW16* pDst = NULL);

E_DLL0 void E_DLL1  ImgConvolUniform( EROIBW8* pSrc, EROIBW8* pDst = NULL, UINT32 un32HalfWidth = 1, UINT32 un32HalfHeight = ~0);
E_DLL0 void E_DLL1  ImgConvolGaussian( EROIBW8* pSrc, EROIBW8* pDst = NULL, UINT32 un32HalfWidth = 1, UINT32 un32HalfHeight = ~0);

E_DLL0 void E_DLL1  ImgConvolUniform( EROIBW16* pSrc, EROIBW16* pDst = NULL, UINT32 un32HalfWidth = 1, UINT32 un32HalfHeight = ~0);
E_DLL0 void E_DLL1  ImgConvolGaussian( EROIBW16* pSrc, EROIBW16* pDst = NULL, UINT32 un32HalfWidth = 1, UINT32 un32HalfHeight = ~0);

// High-pass
E_DLL0 void E_DLL1  ImgConvolHighpass1( EROIBW8* pSrc, EROIBW8* pDst = NULL);
E_DLL0 void E_DLL1  ImgConvolHighpass2( EROIBW8* pSrc, EROIBW8* pDst = NULL);

E_DLL0 void E_DLL1  ImgConvolHighpass1( EROIBW16* pSrc, EROIBW16* pDst = NULL);
E_DLL0 void E_DLL1  ImgConvolHighpass2( EROIBW16* pSrc, EROIBW16* pDst = NULL);

// Gradient
E_DLL0 void E_DLL1  ImgConvolGradientX( EROIBW8* pSrc, EROIBW8* pDst = NULL);
E_DLL0 void E_DLL1  ImgConvolGradientY( EROIBW8* pSrc, EROIBW8* pDst = NULL);
E_DLL0 void E_DLL1  ImgConvolGradient( EROIBW8* pSrc, EROIBW8* pDst = NULL);

E_DLL0 void E_DLL1  ImgConvolGradientX( EROIBW16* pSrc, EROIBW16* pDst = NULL);
E_DLL0 void E_DLL1  ImgConvolGradientY( EROIBW16* pSrc, EROIBW16* pDst = NULL);
E_DLL0 void E_DLL1  ImgConvolGradient( EROIBW16* pSrc, EROIBW16* pDst = NULL);

E_DLL0 void E_DLL1  ImgConvolSobelX( EROIBW8* pSrc, EROIBW8* pDst = NULL);
E_DLL0 void E_DLL1  ImgConvolSobelY( EROIBW8* pSrc, EROIBW8* pDst = NULL);
E_DLL0 void E_DLL1  ImgConvolSobel( EROIBW8* pSrc, EROIBW8* pDst = NULL);

E_DLL0 void E_DLL1  ImgConvolSobelX( EROIBW16* pSrc, EROIBW16* pDst = NULL);
E_DLL0 void E_DLL1  ImgConvolSobelY( EROIBW16* pSrc, EROIBW16* pDst = NULL);
E_DLL0 void E_DLL1  ImgConvolSobel( EROIBW16* pSrc, EROIBW16* pDst = NULL);

E_DLL0 void E_DLL1  ImgConvolPrewittX( EROIBW8* pSrc, EROIBW8* pDst = NULL);
E_DLL0 void E_DLL1  ImgConvolPrewittY( EROIBW8* pSrc, EROIBW8* pDst = NULL);
E_DLL0 void E_DLL1  ImgConvolPrewitt( EROIBW8* pSrc, EROIBW8* pDst = NULL);

E_DLL0 void E_DLL1  ImgConvolPrewittX( EROIBW16* pSrc, EROIBW16* pDst = NULL);
E_DLL0 void E_DLL1  ImgConvolPrewittY( EROIBW16* pSrc, EROIBW16* pDst = NULL);
E_DLL0 void E_DLL1  ImgConvolPrewitt( EROIBW16* pSrc, EROIBW16* pDst = NULL);

E_DLL0 void E_DLL1  ImgConvolRoberts( EROIBW8* pSrc, EROIBW8* pDst = NULL);

E_DLL0 void E_DLL1  ImgConvolRoberts( EROIBW16* pSrc, EROIBW16* pDst = NULL);

// Laplacian
E_DLL0 void E_DLL1  ImgConvolLaplacianX( EROIBW8* pSrc, EROIBW8* pDst = NULL);
E_DLL0 void E_DLL1  ImgConvolLaplacianY( EROIBW8* pSrc, EROIBW8* pDst = NULL);
E_DLL0 void E_DLL1  ImgConvolLaplacian4( EROIBW8* pSrc, EROIBW8* pDst = NULL);
E_DLL0 void E_DLL1  ImgConvolLaplacian8( EROIBW8* pSrc, EROIBW8* pDst = NULL);

E_DLL0 void E_DLL1  ImgConvolLaplacianX( EROIBW16* pSrc, EROIBW16* pDst = NULL);
E_DLL0 void E_DLL1  ImgConvolLaplacianY( EROIBW16* pSrc, EROIBW16* pDst = NULL);
E_DLL0 void E_DLL1  ImgConvolLaplacian4( EROIBW16* pSrc, EROIBW16* pDst = NULL);
E_DLL0 void E_DLL1  ImgConvolLaplacian8( EROIBW16* pSrc, EROIBW16* pDst = NULL);

// Color

// General
E_DLL0 void E_DLL1  ImgConvolKernel( EROIC24* pSrc, EROIC24* pDst, EKernel* pKernel);
E_DLL0 void E_DLL1  ImgConvolSymmetricKernel( EROIC24* pSrc, EROIC24* pDst, EKernel* pKernel);

// Low-pass
E_DLL0 void E_DLL1  ImgConvolLowpass1( EROIC24* pSrc, EROIC24* pDst = NULL);
E_DLL0 void E_DLL1  ImgConvolLowpass2( EROIC24* pSrc, EROIC24* pDst = NULL);
E_DLL0 void E_DLL1  ImgConvolLowpass3( EROIC24* pSrc, EROIC24* pDst = NULL);

E_DLL0 void E_DLL1  ImgConvolUniform( EROIC24* pSrc, EROIC24* pDst = NULL, UINT32 un32HalfWidth = 1, UINT32 un32HalfHeight = ~0);
E_DLL0 void E_DLL1  ImgConvolGaussian( EROIC24* pSrc, EROIC24* pDst = NULL, UINT32 un32HalfWidth = 1, UINT32 un32HalfHeight = ~0);

// High-pass
E_DLL0 void E_DLL1  ImgConvolHighpass1( EROIC24* pSrc, EROIC24* pDst = NULL);
E_DLL0 void E_DLL1  ImgConvolHighpass2( EROIC24* pSrc, EROIC24* pDst = NULL);

// Gradient
E_DLL0 void E_DLL1  ImgConvolGradientX( EROIC24* pSrc, EROIC24* pDst = NULL);
E_DLL0 void E_DLL1  ImgConvolGradientY( EROIC24* pSrc, EROIC24* pDst = NULL);
E_DLL0 void E_DLL1  ImgConvolGradient( EROIC24* pSrc, EROIC24* pDst = NULL);

E_DLL0 void E_DLL1  ImgConvolSobelX( EROIC24* pSrc, EROIC24* pDst = NULL);
E_DLL0 void E_DLL1  ImgConvolSobelY( EROIC24* pSrc, EROIC24* pDst = NULL);
E_DLL0 void E_DLL1  ImgConvolSobel( EROIC24* pSrc, EROIC24* pDst = NULL);

E_DLL0 void E_DLL1  ImgConvolPrewittX( EROIC24* pSrc, EROIC24* pDst = NULL);
E_DLL0 void E_DLL1  ImgConvolPrewittY( EROIC24* pSrc, EROIC24* pDst = NULL);
E_DLL0 void E_DLL1  ImgConvolPrewitt( EROIC24* pSrc, EROIC24* pDst = NULL);

E_DLL0 void E_DLL1  ImgConvolRoberts( EROIC24* pSrc, EROIC24* pDst = NULL);

// Special gradient
E_DLL0 void E_DLL1  ImgModulusImage( EImageBW8* pDst, FLOAT32 f32Gain = 1.f);
E_DLL0 void E_DLL1  ImgArgumentImage( EImageBW8* pDst, EBW8 bw8Phase = 0, FLOAT32 f32Period = 0);
E_DLL0 void E_DLL1  ImgGradientScalar( EROIBW8* pSrc, EROIBW8* pDst, EROIBW8* pLut);

E_DLL0 void E_DLL1  ImgModulusImage( EImageBW16* pDst, FLOAT32 f32Gain = 1.f);
E_DLL0 void E_DLL1  ImgArgumentImage( EImageBW16* pDst, EBW16 bw16Phase = 0, FLOAT32 f32Period = 0);
E_DLL0 void E_DLL1  ImgGradientScalar( EROIBW16* pSrc, EROIBW16* pDst, EROIBW16* pLut);

E_DLL0 void E_DLL1  ImgGradientVector( EROIBW8* pSrc, EROIBW32* pDst);
E_DLL0 void E_DLL1  ImgGradientScalar( EROIBW32* pSrc, EROIBW8* pDst, EROIBW8* pLut);

// Laplacian
E_DLL0 void E_DLL1  ImgConvolLaplacianX( EROIC24* pSrc, EROIC24* pDst = NULL);
E_DLL0 void E_DLL1  ImgConvolLaplacianY( EROIC24* pSrc, EROIC24* pDst = NULL);
E_DLL0 void E_DLL1  ImgConvolLaplacian4( EROIC24* pSrc, EROIC24* pDst = NULL);
E_DLL0 void E_DLL1  ImgConvolLaplacian8( EROIC24* pSrc, EROIC24* pDst = NULL);

// Sliding window
E_DLL0 void E_DLL1  ImgLocalAverage( EROIBW8* pSrc, EROIBW8* pDst, UINT32 un32HalfWidth, UINT32 un32HalfHeight);
E_DLL0 void E_DLL1  ImgLocalDeviation( EROIBW8* pSrc, EROIBW8* pDst, UINT32 un32HalfWidth, UINT32 un32HalfHeight);

E_DLL0 void E_DLL1  ImgLocalAverage( EROIBW16* pSrc, EROIBW16* pDst, UINT32 un32HalfWidth, UINT32 un32HalfHeight);
E_DLL0 void E_DLL1  ImgLocalDeviation( EROIBW16* pSrc, EROIBW16* pDst, UINT32 un32HalfWidth, UINT32 un32HalfHeight);

// + OBSOLETE after 5.2
#define ImgConvolSobelXY ImgConvolSobel
#define ImgConvolPrewittXY ImgConvolPrewitt
// - OBSOLETE after 5.2


E_DLL0 void E_DLL1  ImgConvolUniform3x3( EROIBW8* pSrc, EROIBW8* pDst);
E_DLL0 void E_DLL1  ImgConvolUniform5x5( EROIBW8* pSrc, EROIBW8* pDst);
E_DLL0 void E_DLL1  ImgConvolUniform7x7( EROIBW8* pSrc, EROIBW8* pDst);
E_DLL0 void E_DLL1  ImgConvolGaussian3x3( EROIBW8* pSrc, EROIBW8* pDst);
E_DLL0 void E_DLL1  ImgConvolGaussian5x5( EROIBW8* pSrc, EROIBW8* pDst);
E_DLL0 void E_DLL1  ImgConvolGaussian7x7( EROIBW8* pSrc, EROIBW8* pDst);
E_DLL0 void E_DLL1  ImgConvolLowpass1X( EROIBW8* pSrcImage, EROIBW8* pDstImage);
E_DLL0 void E_DLL1  ImgConvolLowpass1Y( EROIBW8* pSrcImage, EROIBW8* pDstImage);

////////////////////////////////////////////////////////////////////////////////////////////////////
// Morphology
//

//Binary Images
E_DLL0 void E_DLL1  ImgDilateBox( EROIBW1* pSrc, EROIBW1* pDst = NULL, UINT32 un32HalfWidth = 1, UINT32 un32HalfHeight = ~0);
E_DLL0 void E_DLL1  ImgErodeBox( EROIBW1* pSrc, EROIBW1* pDst = NULL, UINT32 un32HalfWidth = 1, UINT32 un32HalfHeight = ~0);
E_DLL0 void E_DLL1  ImgOpenBox( EROIBW1* pSrc, EROIBW1* pDst = NULL, UINT32 un32HalfWidth = 1, UINT32 un32HalfHeight = ~0);
E_DLL0 void E_DLL1  ImgCloseBox( EROIBW1* pSrc, EROIBW1* pDst = NULL, UINT32 un32HalfWidth = 1, UINT32 un32HalfHeight = ~0);
E_DLL0 void E_DLL1  ImgWhiteTopHatBox( EROIBW1* pSrc, EROIBW1* pDst = NULL, UINT32 un32HalfWidth = 1, UINT32 un32HalfHeight = ~0);
E_DLL0 void E_DLL1  ImgBlackTopHatBox( EROIBW1* pSrc, EROIBW1* pDst = NULL, UINT32 un32HalfWidth = 1, UINT32 un32HalfHeight = ~0);
E_DLL0 void E_DLL1  ImgMorphoGradientBox( EROIBW1* pSrc, EROIBW1* pDst = NULL, UINT32 un32HalfWidth = 1, UINT32 un32HalfHeight = ~0);

E_DLL0 void E_DLL1  ImgErodeDisk( EROIBW1* pSrc, EROIBW1* pDst = NULL, UINT32 un32HalfWidth = 1);
E_DLL0 void E_DLL1  ImgDilateDisk( EROIBW1* pSrc, EROIBW1* pDst = NULL, UINT32 un32HalfWidth = 1);
E_DLL0 void E_DLL1  ImgOpenDisk( EROIBW1* pSrc, EROIBW1* pDst = NULL, UINT32 un32HalfWidth = 1);
E_DLL0 void E_DLL1  ImgCloseDisk( EROIBW1* pSrc, EROIBW1* pDst = NULL, UINT32 un32HalfWidth = 1);
E_DLL0 void E_DLL1  ImgWhiteTopHatDisk( EROIBW1* pSrc, EROIBW1* pDst = NULL, UINT32 un32HalfWidth = 1);
E_DLL0 void E_DLL1  ImgBlackTopHatDisk( EROIBW1* pSrc, EROIBW1* pDst = NULL, UINT32 un32HalfWidth = 1);
E_DLL0 void E_DLL1  ImgMorphoGradientDisk( EROIBW1* pSrc, EROIBW1* pDst = NULL, UINT32 un32HalfWidth = 1);

E_DLL0 void E_DLL1  ImgDilateBoxAligned( EROIBW1* pSrc, EROIBW1* pDst = NULL, UINT32 un32HalfWidth = 1, UINT32 un32HalfHeight = ~0);
E_DLL0 void E_DLL1  ImgErodeBoxAligned( EROIBW1* pSrc, EROIBW1* pDst = NULL, UINT32 un32HalfWidth = 1, UINT32 un32HalfHeight = ~0);
E_DLL0 void E_DLL1  ImgOpenBoxAligned( EROIBW1* pSrc, EROIBW1* pDst = NULL, UINT32 un32HalfWidth = 1, UINT32 un32HalfHeight = ~0);
E_DLL0 void E_DLL1  ImgCloseBoxAligned( EROIBW1* pSrc, EROIBW1* pDst = NULL, UINT32 un32HalfWidth = 1, UINT32 un32HalfHeight = ~0);
E_DLL0 void E_DLL1  ImgWhiteTopHatBoxAligned( EROIBW1* pSrc, EROIBW1* pDst, UINT32 un32HalfWidth = 1, UINT32 un32HalfHeight = ~0);
E_DLL0 void E_DLL1  ImgBlackTopHatBoxAligned( EROIBW1* pSrc, EROIBW1* pDst, UINT32 un32HalfWidth = 1, UINT32 un32HalfHeight = ~0);
E_DLL0 void E_DLL1  ImgMorphoGradientBoxAligned( EROIBW1* pSrc, EROIBW1* pDst = NULL, UINT32 un32HalfWidth = 1, UINT32 un32HalfHeight = ~0);

E_DLL0 void E_DLL1  ImgErodeDiskAligned( EROIBW1* pSrc, EROIBW1* pDst = NULL, UINT32 un32HalfWidth = 1);
E_DLL0 void E_DLL1  ImgDilateDiskAligned( EROIBW1* pSrc, EROIBW1* pDst = NULL, UINT32 un32HalfWidth = 1);
E_DLL0 void E_DLL1  ImgOpenDiskAligned( EROIBW1* pSrc, EROIBW1* pDst = NULL, UINT32 un32HalfWidth = 1);
E_DLL0 void E_DLL1  ImgCloseDiskAligned( EROIBW1* pSrc, EROIBW1* pDst = NULL, UINT32 un32HalfWidth = 1);
E_DLL0 void E_DLL1  ImgWhiteTopHatDiskAligned( EROIBW1* pSrc, EROIBW1* pDst, UINT32 un32HalfWidth = 1);
E_DLL0 void E_DLL1  ImgBlackTopHatDiskAligned( EROIBW1* pSrc, EROIBW1* pDst, UINT32 un32HalfWidth = 1);
E_DLL0 void E_DLL1  ImgMorphoGradientDiskAligned( EROIBW1* pSrc, EROIBW1* pDst = NULL, UINT32 un32HalfWidth = 1);

//BiLevels Images
E_DLL0 void E_DLL1  ImgBiLevelErodeBox( EROIBW8* pSrc, EROIBW8* pDst = NULL, UINT32 un32HalfWidth = 1, UINT32 un32HalfHeight = ~0);
E_DLL0 void E_DLL1  ImgBiLevelDilateBox( EROIBW8* pSrc, EROIBW8* pDst = NULL, UINT32 un32HalfWidth = 1, UINT32 un32HalfHeight = ~0);
E_DLL0 void E_DLL1  ImgBiLevelOpenBox( EROIBW8* pSrc, EROIBW8* pDst = NULL, UINT32 un32HalfWidth = 1, UINT32 un32HalfHeight = ~0);
E_DLL0 void E_DLL1  ImgBiLevelCloseBox( EROIBW8* pSrc, EROIBW8* pDst = NULL, UINT32 un32HalfWidth = 1, UINT32 un32HalfHeight = ~0);
E_DLL0 void E_DLL1  ImgBiLevelWhiteTopHatBox( EROIBW8* pSrc, EROIBW8* pDst, UINT32 un32HalfWidth = 1, UINT32 un32HalfHeight = ~0);
E_DLL0 void E_DLL1  ImgBiLevelBlackTopHatBox( EROIBW8* pSrc, EROIBW8* pDst, UINT32 un32HalfWidth = 1, UINT32 un32HalfHeight = ~0);
E_DLL0 void E_DLL1  ImgBiLevelMorphoGradientBox( EROIBW8* pSrc, EROIBW8* pDst = NULL, UINT32 un32HalfWidth = 1, UINT32 un32HalfHeight = ~0);

E_DLL0 void E_DLL1  ImgBiLevelErodeDisk( EROIBW8* pSrc, EROIBW8* pDst = NULL, UINT32 un32HalfWidth = 1);
E_DLL0 void E_DLL1  ImgBiLevelDilateDisk( EROIBW8* pSrc, EROIBW8* pDst = NULL, UINT32 un32HalfWidth = 1);
E_DLL0 void E_DLL1  ImgBiLevelOpenDisk( EROIBW8* pSrc, EROIBW8* pDst = NULL, UINT32 un32HalfWidth = 1);
E_DLL0 void E_DLL1  ImgBiLevelCloseDisk( EROIBW8* pSrc, EROIBW8* pDst = NULL, UINT32 un32HalfWidth = 1);
E_DLL0 void E_DLL1  ImgBiLevelWhiteTopHatDisk( EROIBW8* pSrc, EROIBW8* pDst, UINT32 un32HalfWidth = 1);
E_DLL0 void E_DLL1  ImgBiLevelBlackTopHatDisk( EROIBW8* pSrc, EROIBW8* pDst, UINT32 un32HalfWidth = 1);
E_DLL0 void E_DLL1  ImgBiLevelMorphoGradientDisk( EROIBW8* pSrc, EROIBW8* pDst = NULL, UINT32 un32HalfWidth = 1);


// Gray levels
// Rectangular structuring element ( including square)
E_DLL0 void E_DLL1  ImgDilateBox( EROIBW8* pSrc, EROIBW8* pDst = NULL, UINT32 un32HalfWidth = 1, UINT32 un32HalfHeight = ~0);
E_DLL0 void E_DLL1  ImgErodeBox( EROIBW8* pSrc, EROIBW8* pDst = NULL, UINT32 un32HalfWidth = 1, UINT32 un32HalfHeight = ~0);
E_DLL0 void E_DLL1  ImgOpenBox( EROIBW8* pSrc, EROIBW8* pDst = NULL, UINT32 un32HalfWidth = 1, UINT32 un32HalfHeight = ~0);
E_DLL0 void E_DLL1  ImgCloseBox( EROIBW8* pSrc, EROIBW8* pDst = NULL, UINT32 un32HalfWidth = 1, UINT32 un32HalfHeight = ~0);
E_DLL0 void E_DLL1  ImgWhiteTopHatBox( EROIBW8* pSrc, EROIBW8* pDst = NULL, UINT32 un32HalfWidth = 1, UINT32 un32HalfHeight = ~0);
E_DLL0 void E_DLL1  ImgBlackTopHatBox( EROIBW8* pSrc, EROIBW8* pDst = NULL, UINT32 un32HalfWidth = 1, UINT32 un32HalfHeight = ~0);
E_DLL0 void E_DLL1  ImgMorphoGradientBox( EROIBW8* pSrc, EROIBW8* pDst = NULL, UINT32 un32HalfWidth = 1, UINT32 un32HalfHeight = ~0);

E_DLL0 void E_DLL1  ImgDilateBox( EROIBW16* pSrc, EROIBW16* pDst = NULL, UINT32 un32HalfWidth = 1, UINT32 un32HalfHeight = ~0);
E_DLL0 void E_DLL1  ImgErodeBox( EROIBW16* pSrc, EROIBW16* pDst = NULL, UINT32 un32HalfWidth = 1, UINT32 un32HalfHeight = ~0);
E_DLL0 void E_DLL1  ImgOpenBox( EROIBW16* pSrc, EROIBW16* pDst = NULL, UINT32 un32HalfWidth = 1, UINT32 un32HalfHeight = ~0);
E_DLL0 void E_DLL1  ImgCloseBox( EROIBW16* pSrc, EROIBW16* pDst = NULL, UINT32 un32HalfWidth = 1, UINT32 un32HalfHeight = ~0);
E_DLL0 void E_DLL1  ImgWhiteTopHatBox( EROIBW16* pSrc, EROIBW16* pDst = NULL, UINT32 un32HalfWidth = 1, UINT32 un32HalfHeight = ~0);
E_DLL0 void E_DLL1  ImgBlackTopHatBox( EROIBW16* pSrc, EROIBW16* pDst = NULL, UINT32 un32HalfWidth = 1, UINT32 un32HalfHeight = ~0);
E_DLL0 void E_DLL1  ImgMorphoGradientBox( EROIBW16* pSrc, EROIBW16* pDst = NULL, UINT32 un32HalfWidth = 1, UINT32 un32HalfHeight = ~0);

// Quasi-circular structuring element
E_DLL0 void E_DLL1  ImgDilateDisk( EROIBW8* pSrc, EROIBW8* pDst = NULL, UINT32 un32HalfWidth = 1);
E_DLL0 void E_DLL1  ImgErodeDisk( EROIBW8* pSrc, EROIBW8* pDst = NULL, UINT32 un32HalfWidth = 1);
E_DLL0 void E_DLL1  ImgOpenDisk( EROIBW8* pSrc, EROIBW8* pDst = NULL, UINT32 un32HalfWidth = 1);
E_DLL0 void E_DLL1  ImgCloseDisk( EROIBW8* pSrc, EROIBW8* pDst = NULL, UINT32 un32HalfWidth = 1);
E_DLL0 void E_DLL1  ImgWhiteTopHatDisk( EROIBW8* pSrc, EROIBW8* pDst = NULL, UINT32 un32HalfWidth = 1);
E_DLL0 void E_DLL1  ImgBlackTopHatDisk( EROIBW8* pSrc, EROIBW8* pDst = NULL, UINT32 un32HalfWidth = 1);
E_DLL0 void E_DLL1  ImgMorphoGradientDisk( EROIBW8* pSrc, EROIBW8* pDst = NULL, UINT32 un32HalfWidth = 1);

E_DLL0 void E_DLL1  ImgDilateDisk( EROIBW16* pSrc, EROIBW16* pDst = NULL, UINT32 un32HalfWidth = 1);
E_DLL0 void E_DLL1  ImgErodeDisk( EROIBW16* pSrc, EROIBW16* pDst = NULL, UINT32 un32HalfWidth = 1);
E_DLL0 void E_DLL1  ImgOpenDisk( EROIBW16* pSrc, EROIBW16* pDst = NULL, UINT32 un32HalfWidth = 1);
E_DLL0 void E_DLL1  ImgCloseDisk( EROIBW16* pSrc, EROIBW16* pDst = NULL, UINT32 un32HalfWidth = 1);
E_DLL0 void E_DLL1  ImgWhiteTopHatDisk( EROIBW16* pSrc, EROIBW16* pDst = NULL, UINT32 un32HalfWidth = 1);
E_DLL0 void E_DLL1  ImgBlackTopHatDisk( EROIBW16* pSrc, EROIBW16* pDst = NULL, UINT32 un32HalfWidth = 1);
E_DLL0 void E_DLL1  ImgMorphoGradientDisk( EROIBW16* pSrc, EROIBW16* pDst = NULL, UINT32 un32HalfWidth = 1);

// Color

// Rectangular structuring element ( including square)
E_DLL0 void E_DLL1  ImgDilateBox( EROIC24* pSrc, EROIC24* pDst = NULL, UINT32 un32HalfWidth = 1, UINT32 un32HalfHeight = ~0);
E_DLL0 void E_DLL1  ImgErodeBox( EROIC24* pSrc, EROIC24* pDst = NULL, UINT32 un32HalfWidth = 1, UINT32 un32HalfHeight = ~0);
E_DLL0 void E_DLL1  ImgOpenBox( EROIC24* pSrc, EROIC24* pDst = NULL, UINT32 un32HalfWidth = 1, UINT32 un32HalfHeight = ~0);
E_DLL0 void E_DLL1  ImgCloseBox( EROIC24* pSrc, EROIC24* pDst = NULL, UINT32 un32HalfWidth = 1, UINT32 un32HalfHeight = ~0);
E_DLL0 void E_DLL1  ImgWhiteTopHatBox( EROIC24* pSrc, EROIC24* pDst = NULL, UINT32 un32HalfWidth = 1, UINT32 un32HalfHeight = ~0);
E_DLL0 void E_DLL1  ImgBlackTopHatBox( EROIC24* pSrc, EROIC24* pDst = NULL, UINT32 un32HalfWidth = 1, UINT32 un32HalfHeight = ~0);
E_DLL0 void E_DLL1  ImgMorphoGradientBox( EROIC24* pSrc, EROIC24* pDst = NULL, UINT32 un32HalfWidth = 1, UINT32 un32HalfHeight = ~0);

// Quasi-circular structuring element
E_DLL0 void E_DLL1  ImgDilateDisk( EROIC24* pSrc, EROIC24* pDst = NULL, UINT32 un32HalfWidth = 1);
E_DLL0 void E_DLL1  ImgErodeDisk( EROIC24* pSrc, EROIC24* pDst = NULL, UINT32 un32HalfWidth = 1);
E_DLL0 void E_DLL1  ImgOpenDisk( EROIC24* pSrc, EROIC24* pDst = NULL, UINT32 un32HalfWidth = 1);
E_DLL0 void E_DLL1  ImgCloseDisk( EROIC24* pSrc, EROIC24* pDst = NULL, UINT32 un32HalfWidth = 1);
E_DLL0 void E_DLL1  ImgWhiteTopHatDisk( EROIC24* pSrc, EROIC24* pDst = NULL, UINT32 un32HalfWidth = 1);
E_DLL0 void E_DLL1  ImgBlackTopHatDisk( EROIC24* pSrc, EROIC24* pDst = NULL, UINT32 un32HalfWidth = 1);
E_DLL0 void E_DLL1  ImgMorphoGradientDisk( EROIC24* pSrc, EROIC24* pDst = NULL, UINT32 un32HalfWidth = 1);

// + OBSOLETE after 5.1
// Gray level
E_DLL0 INT16 E_DLL1  ImgOpen
( EROIBW8* pSrcImage, EROIBW8* pDstImage,
 INT32 n32Iter, INT32 n32ValOffErode = 255, INT32 n32ValOffDilate = 0);
E_DLL0 INT16 E_DLL1  ImgClose
( EROIBW8* pSrcImage, EROIBW8* pDstImage, INT32 n32Iter,
 INT32 n32ValOffDilate = 0, INT32 n32ValOffErode = 255);

E_DLL0 INT16 E_DLL1  ImgErode
( EROIBW8* pSrcImage, EROIBW8* pDstImage,
 INT32 n32Iter, INT32 n32ValOff = 255);
E_DLL0 INT16 E_DLL1  ImgDilate
( EROIBW8* pSrcImage, EROIBW8* pDstImage,
 INT32 n32Iter, INT32 n32ValOff = 0);

E_DLL0 INT16 E_DLL1  ImgBlackTopHat
( EROIBW8* pSrcImage, EROIBW8* pDstImage,
 INT32 n32Iter, INT32 n32ValOffDilate = 0, INT32 n32ValOffErode = 255);
E_DLL0 INT16 E_DLL1  ImgWhiteTopHat
( EROIBW8* pSrcImage, EROIBW8* pDstImage,
 INT32 n32Iter, INT32 n32ValOffErode = 255, INT32 n32ValOffDilate = 0);

E_DLL0 INT16 E_DLL1  ImgMedian( EROIBW8* pSrcImage, EROIBW8* pDstImage, INT32 n32ValOff);

// Color
E_DLL0 void E_DLL1  ImgErode
( EROIC24* pSrcImage, EROIC24* pDstImage,
 INT32 n32Iter, EC24 c24ColorOff = EWhite24);
E_DLL0 void E_DLL1  ImgDilate
( EROIC24* pSrcImage, EROIC24* pDstImage,
 INT32 n32Iter, EC24 c24ColorOff = EBlack24);

E_DLL0 void E_DLL1  ImgOpen
( EROIC24* pSrcImage, EROIC24* pDstImage,
 INT32 n32Iter, EC24 c24ColorOffErode = EWhite24, EC24 c24ColorOffDilate = EBlack24);
E_DLL0 void E_DLL1  ImgClose
( EROIC24* pSrcImage, EROIC24* pDstImage,
 INT32 n32Iter, EC24 c24ColorOffDilate = EBlack24, EC24 c24ColorOffErode = EWhite24);

E_DLL0 void E_DLL1  ImgBlackTopHat
( EROIC24* pSrcImage, EROIC24* pDstImage,
 INT32 n32Iter, EC24 c24ColorOffDilate = EBlack24, EC24 c24ColorOffErode = EWhite24);
E_DLL0 void E_DLL1  ImgWhiteTopHat
( EROIC24* pSrcImage, EROIC24* pDstImage,
 INT32 n32Iter, EC24 c24ColorOffErode = EWhite24, EC24 c24ColorOffDilate = EBlack24);

E_DLL0 void E_DLL1  ImgMedian( EROIC24* pSrcImage, EROIC24* pDstImage, EC24 c24ColorOff = EGray24);
// - OBSOLETE after 5.1

// Median, Thin, Thick for Binary Images
E_DLL0 void E_DLL1  ImgMedian( EROIBW1* pSrcImage, EROIBW1* pDstImage);

E_DLL0 INT16 E_DLL1  ImgThin( EROIBW1* pSrcImage, EROIBW1* pDstImage, EKernel* pThinKernel, 
                             enum KERNEL_ROTATION Mode, INT32& n32Iter);
E_DLL0 INT16 E_DLL1  ImgThick( EROIBW1* pSrcImage, EROIBW1* pDstImage, EKernel* pThickKernel, 
                              enum KERNEL_ROTATION Mode, INT32& n32Iter);
E_DLL0 void E_DLL1  ImgMedianAligned( EROIBW1* pSrcImage, EROIBW1* pDstImage);

E_DLL0 INT16 E_DLL1  ImgThinAligned( EROIBW1* pSrcImage, EROIBW1* pDstImage, EKernel* pThinKernel, 
                             enum KERNEL_ROTATION Mode, INT32& n32Iter);
E_DLL0 INT16 E_DLL1  ImgThickAligned( EROIBW1* pSrcImage, EROIBW1* pDstImage, EKernel* pThickKernel, 
                              enum KERNEL_ROTATION Mode, INT32& n32Iter);
// Median, Thin, Thick for BiLevels Images
E_DLL0 void E_DLL1  ImgBiLevelMedian( EROIBW8* pSrcImage, EROIBW8* pDstImage); 

E_DLL0 INT16 E_DLL1  ImgBiLevelThin( EROIBW8* pSrcImage, EROIBW8* pDstImage, EKernel* pThinKernel, 
                             enum KERNEL_ROTATION Mode, INT32& n32Iter);
E_DLL0 INT16 E_DLL1  ImgBiLevelThick( EROIBW8* pSrcImage, EROIBW8* pDstImage, EKernel* pThickKernel, 
                              enum KERNEL_ROTATION Mode, INT32& n32Iter);


E_DLL0 void E_DLL1  ImgMedian( EROIBW8* pSrcImage, EROIBW8* pDstImage);

E_DLL0 INT16 E_DLL1  ImgThin( EROIBW8* pSrcImage, EROIBW8* pDstImage, EKernel* pThinKernel, 
                            enum KERNEL_ROTATION Mode, INT32& n32Iter);
E_DLL0 INT16 E_DLL1  ImgThick( EROIBW8* pSrcImage, EROIBW8* pDstImage, EKernel* pThickKernel, 
                             enum KERNEL_ROTATION Mode, INT32& n32Iter);

E_DLL0 INT16 E_DLL1  ImgDistance( EROIBW8* pSrcImage, EImageBW16* pDstImage, INT32 n32ValOut = 0);

E_DLL0 void E_DLL1  ImgMedian( EROIBW16* pSrcImage, EROIBW16* pDstImage);

E_DLL0 void E_DLL1  ImgThin( EROIBW16* pSrcImage, EROIBW16* pDstImage, EKernel* pThinKernel, 
                            enum KERNEL_ROTATION Mode, INT32& n32Iter);
E_DLL0 void E_DLL1  ImgThick( EROIBW16* pSrcImage, EROIBW16* pDstImage, EKernel* pThickKernel, 
                             enum KERNEL_ROTATION Mode, INT32& n32Iter);

E_DLL0 void E_DLL1  ImgThin( EROIC24* pSrcImage, EROIC24* pDstImage, EKernel* pThinKernel, 
                           enum KERNEL_ROTATION Mode, INT32& n32Iter);
E_DLL0 void E_DLL1  ImgThick( EROIC24* pSrcImage, EROIC24* pDstImage, EKernel* pThickKernel, 
                            enum KERNEL_ROTATION Mode, INT32& n32Iter);

////////////////////////////////////////////////////////////////////////////////////////////////////
// Histograms
//
// Gray Level
E_DLL0 void E_DLL1  ImgHistogram
( EROIBW8* pSrcImage, EBWHistogramVector* pHistogram);

E_DLL0 void E_DLL1  ImgEqualize( EROIBW8* pSrc, EROIBW8* pDst);

E_DLL0 void E_DLL1  ImgCumulateHistogram( EBWHistogramVector* pSrc, EBWHistogramVector* pDst);

E_DLL0 FLOAT32 E_DLL1  ImgAnalyseHistogram
( EBWHistogramVector* pHistogram, enum IMG_HISTOGRAM_FEATURE,
 INT32 n32MinIndex = 0, INT32 n32MaxIndex = 255);

// BW16
E_DLL0 void E_DLL1  ImgHistogram
( EROIBW16* pSrcImage, EBWHistogramVector* pHistogram,
 UINT32 un32MostSignificantBit, UINT32 un32NumUsedBits, BOOL bSaturate = TRUE);

E_DLL0 void E_DLL1  ImgEqualize( EROIBW16* pSrc, EROIBW16* pDst);

E_DLL0 FLOAT32 E_DLL1  ImgAnalyseHistogramBW16
( EBWHistogramVector* pHistogram, enum IMG_HISTOGRAM_FEATURE,
 INT32 n32MinIndex = 0, INT32 n32MaxIndex = 65535);

// BW32
E_DLL0 void E_DLL1  ImgHistogram
( EROIBW32* pSrcImage, EBWHistogramVector* pHistogram,
 UINT32 un32MostSignificantBit, UINT32 un32NumUsedBits, BOOL bSaturate = TRUE);

// + OBSOLETE after 4.0
E_DLL0 INT16 E_DLL1  ImgHistogram( EROIBW8* pSrcImage, EVector* pDstVector);
E_DLL0 INT16 E_DLL1  ImgAnalyseHistogram( EVector* pHistVect, INT32 n32MinIndex, INT32 n32MaxIndex, INT32 n32Operation, INT32& n32Result);
E_DLL0 INT16 E_DLL1  ImgAnalyseHistogram( EVector* pHistVect, INT32 n32MinIndex, INT32 n32MaxIndex, INT32 n32Operation, FLOAT32& f32Result);
// - OBSOLETE after 4.0


////////////////////////////////////////////////////////////////////////////////////////////////////
// Projections
//

// Sum
E_DLL0 void E_DLL1  ImgProjectOnARow( EROIBW8* pSrcImage, EBW32Vector* pProjection);
E_DLL0 void E_DLL1  ImgProjectOnAColumn( EROIBW8* pSrcImage, EBW32Vector* pProjection);

E_DLL0 void E_DLL1  ImgProjectOnARow( EROIBW16* pSrcImage, EBW32Vector* pProjection);
E_DLL0 void E_DLL1  ImgProjectOnAColumn( EROIBW16* pSrcImage, EBW32Vector* pProjection);

// Average
E_DLL0 void E_DLL1  ImgProjectOnARow( EROIBW8* pSrcImage, EBW8Vector* pProjection);
E_DLL0 void E_DLL1  ImgProjectOnAColumn( EROIBW8* pSrcImage, EBW8Vector* pProjection);

E_DLL0 void E_DLL1  ImgProjectOnARow( EROIBW16* pSrcImage, EBW16Vector* pProjection);
E_DLL0 void E_DLL1  ImgProjectOnAColumn( EROIBW16* pSrcImage, EBW16Vector* pProjection);

E_DLL0 void E_DLL1  ImgProjectOnARow( EROIC24* pSrcImage, EC24Vector* pProjection);
E_DLL0 void E_DLL1  ImgProjectOnAColumn( EROIC24* pSrcImage, EC24Vector* pProjection);

// + OBSOLETE after 4.0
E_DLL0 INT16 E_DLL1  ImgProjectOnARow( EROIBW8* pSrcImage, EVector* pDstVect);
E_DLL0 INT16 E_DLL1  ImgProjectOnAColumn( EROIBW8* pSrcImage, EVector* pDstVect);
// - OBSOLETE after 4.0


////////////////////////////////////////////////////////////////////////////////////////////////////
// Miscellaneous
// Gray Level
// Average gradient energy
E_DLL0 FLOAT32 E_DLL1  ImgFocusing( EROIBW8* pImage);

// Interlacing
E_DLL0 void E_DLL1  ImgSetFrame( EROIBW8* pSrc, EROIBW8* pDst, BOOL bOdd);
E_DLL0 void E_DLL1  ImgGetFrame( EROIBW8* pSrc, EROIBW8* pDst, BOOL bOdd);

// Compensate interlacing mismatch by interpolation
E_DLL0 void E_DLL1  ImgRebuildFrame( EROIBW8* pSrcImage, EROIBW8* pDstImage, UINT32 un32FixedRow = 0);

// Remove interlacing mismatch by horizontal shifting
E_DLL0 void E_DLL1  ImgRealignFrame( EROIBW8* pSrcImage, EROIBW8* pDstImage, INT32 n32Offset, UINT32 un32FixedRow = 0);
E_DLL0 void E_DLL1  ImgMatchFrames( EROIBW8* pSrcImage, INT32 n32FixedRow, INT32 n32MinOffset, INT32 n32MaxOffset, INT32& n32BestOffset);
E_DLL0 void E_DLL1  ImgSwapFrames( EROIBW8* pSrcImage, EROIBW8* pDstImage);

// BW16
// Average gradient energy
E_DLL0 FLOAT32 E_DLL1  ImgFocusing( EROIBW16* pImage);

// Interlacing
E_DLL0 void E_DLL1  ImgSetFrame( EROIBW16* pSrc, EROIBW16* pDst, BOOL bOdd);
E_DLL0 void E_DLL1  ImgGetFrame( EROIBW16* pSrc, EROIBW16* pDst, BOOL bOdd);

// Compensate interlacing mismatch by interpolation
E_DLL0 void E_DLL1  ImgRebuildFrame( EROIBW16* pSrcImage, EROIBW16* pDstImage, UINT32 un32FixedRow = 0);

// Remove interlacing mismatch by horizontal shifting
E_DLL0 void E_DLL1  ImgRealignFrame( EROIBW16* pSrcImage, EROIBW16* pDstImage, INT32 n32Offset, UINT32 un32FixedRow = 0);
E_DLL0 void E_DLL1  ImgMatchFrames( EROIBW16* pSrcImage, INT32 n32FixedRow, INT32 n32MinOffset, INT32 n32MaxOffset, INT32& n32BestOffset);
E_DLL0 void E_DLL1  ImgSwapFrames( EROIBW16* pSrcImage, EROIBW16* pDstImage);

// Color
// Average gradient energy
E_DLL0 FLOAT32 E_DLL1  ImgFocusing( EROIC24* pImage);

// Interlacing
E_DLL0 void E_DLL1  ImgSetFrame( EROIC24* pSrc, EROIC24* pDst, BOOL bOdd);
E_DLL0 void E_DLL1  ImgGetFrame( EROIC24* pSrc, EROIC24* pDst, BOOL bOdd);

// Compensate interlacing mismatch by interpolation
E_DLL0 void E_DLL1  ImgRebuildFrame( EROIC24* pSrcImage, EROIC24* pDstImage, UINT32 un32FixedRow = 0);

// Remove interlacing mismatch by horizontal shifting
E_DLL0 void E_DLL1  ImgRealignFrame( EROIC24* pSrcImage, EROIC24* pDstImage, INT32 n32Offset, UINT32 un32FixedRow = 0);
E_DLL0 void E_DLL1  ImgMatchFrames( EROIC24* pSrcImage, INT32 n32FixedRow, INT32 n32MinOffset, INT32 n32MaxOffset, INT32& n32BestOffset);
E_DLL0 void E_DLL1  ImgSwapFrames( EROIC24* pSrcImage, EROIC24* pDstImage);

////////////////////////////////////////////////////////////////////////////////////////////////////
// Vector functions
//

E_DLL0 void E_DLL1  ImgSetupEqualize( EBWHistogramVector* pHistogram, EBW8Vector* pLookupTable);

// Line segment from image
E_DLL0 void E_DLL1  ImgImageToLineSegment
( EROIBW8* pImage, EBW8Vector* pPath,
 INT32 n32X0, INT32 n32Y0, INT32 n32X1, INT32 n32Y1);
E_DLL0 void E_DLL1  ImgImageToLineSegment
( EROIBW16* pImage, EBW16Vector* pPath,
 INT32 n32X0, INT32 n32Y0, INT32 n32X1, INT32 n32Y1);
E_DLL0 void E_DLL1  ImgImageToLineSegment
( EROIC24* pImage, EC24Vector* pPath,
 INT32 n32X0, INT32 n32Y0, INT32 n32X1, INT32 n32Y1);

// Constant line segment to image
E_DLL0 void E_DLL1  ImgLineSegmentToImage
( EROIBW8* pImage, EBW8 bw8Pixel,
 INT32 n32X0, INT32 n32Y0, INT32 n32X1, INT32 n32Y1);
E_DLL0 void E_DLL1  ImgLineSegmentToImage
( EROIBW16* pImage, EBW16 bw16Pixel,
 INT32 n32X0, INT32 n32Y0, INT32 n32X1, INT32 n32Y1);
E_DLL0 void E_DLL1  ImgLineSegmentToImage
( EROIC24* pImage, EC24 c24Pixel,
 INT32 n32X0, INT32 n32Y0, INT32 n32X1, INT32 n32Y1);

// Line segment to image
E_DLL0 void E_DLL1  ImgLineSegmentToImage
( EROIBW8* pImage, EBW8Vector* pPath,
 INT32 n32X0, INT32 n32Y0, INT32 n32X1, INT32 n32Y1);
E_DLL0 void E_DLL1  ImgLineSegmentToImage
( EROIBW16* pImage, EBW16Vector* pPath,
 INT32 n32X0, INT32 n32Y0, INT32 n32X1, INT32 n32Y1);
E_DLL0 void E_DLL1  ImgLineSegmentToImage
( EROIC24* pImage, EC24Vector* pPath,
 INT32 n32X0, INT32 n32Y0, INT32 n32X1, INT32 n32Y1);

// Path from image
E_DLL0 void E_DLL1  ImgImageToPath( EROIBW8* pImage, EBW8PathVector* pPath);
E_DLL0 void E_DLL1  ImgImageToPath( EROIBW16* pImage, EBW16PathVector* pPath);
E_DLL0 void E_DLL1  ImgImageToPath( EROIC24* pImage, EC24PathVector* pPath);

// Path to image
E_DLL0 void E_DLL1  ImgPathToImage( EROIBW8* pImage, EBW8PathVector* pPath);
E_DLL0 void E_DLL1  ImgPathToImage( EROIBW16* pImage, EBW16PathVector* pPath);
E_DLL0 void E_DLL1  ImgPathToImage( EROIC24* pImage, EC24PathVector* pPath);

// Vector neighborhood operations
E_DLL0 void E_DLL1  ImgConvolUniform( EBW8Vector* pSrc, EBW8Vector* pDst, UINT32 un32HalfWidth = 1);
E_DLL0 void E_DLL1  ImgConvolUniform( EBW16Vector* pSrc, EBW16Vector* pDst, UINT32 un32HalfWidth = 1);

// + OBSOLETE after 6.0.1
#define ImgConvolBinomial ImgConvolGaussian
// - OBSOLETE after 6.0.1
E_DLL0 void E_DLL1  ImgConvolGaussian( EBW8Vector* pSrc, EBW8Vector* pDst, UINT32 un32HalfWidth = 1);
E_DLL0 void E_DLL1  ImgConvolGaussian( EBW16Vector* pSrc, EBW16Vector* pDst, UINT32 un32HalfWidth = 1);

E_DLL0 void E_DLL1  ImgDilate( EBW8Vector* pSrc, EBW8Vector* pDst, UINT32 un32HalfWidth = 1);
E_DLL0 void E_DLL1  ImgDilate( EBW16Vector* pSrc, EBW16Vector* pDst, UINT32 un32HalfWidth = 1);

E_DLL0 void E_DLL1  ImgErode( EBW8Vector* pSrc, EBW8Vector* pDst, UINT32 un32HalfWidth = 1);
E_DLL0 void E_DLL1  ImgErode( EBW16Vector* pSrc, EBW16Vector* pDst, UINT32 un32HalfWidth = 1);

// Profiles and peaks
E_DLL0 void E_DLL1  ImgProfileDerivative( EBW8Vector* pSrc, EBW8Vector* pDst);
E_DLL0 void E_DLL1  ImgProfileDerivative( EBW16Vector* pSrc, EBW16Vector* pDst);

E_DLL0 void E_DLL1  ImgGetProfilePeaks
( EBW8Vector* pProfile, EPeaksVector* pPeaks,
 UINT32 un32LowThreshold = 0, UINT32 un32HighThreshold = 255,
 UINT32 un32MinAmplitude = 0, UINT32 un32MinArea = 0);
E_DLL0 void E_DLL1  ImgGetProfilePeaks
( EBW16Vector* pProfile, EPeaksVector* pPeaks,
 UINT32 un32LowThreshold = 0, UINT32 un32HighThreshold = 65535,
 UINT32 un32MinAmplitude = 0, UINT32 un32MinArea = 0);

// + OBSOLETE after 4.0
E_DLL0 INT16 E_DLL1  ImgVectDataShift
( EVector* pVector,
 INT32 n32Shift, INT32 n32StartGroup, INT32 n32EndGroup);
E_DLL0 INT16 E_DLL1  ImgGetVectTransition( EVector* pSrcVect, EVector* pDstVect, INT32 n32Thr = 127);
E_DLL0 INT16 E_DLL1  ImgGetVectTransition( EVector* pSrcVect, EVector* pDstVect, UINT32 un32Thr = 127u);
E_DLL0 INT16 E_DLL1  ImgConvolVect( EVector* pSrcVect, EVector* pDstVect, EKernel* pKernel,
                                  INT32 n32StartGroup, INT32 n32EndGroup);
E_DLL0 INT16 E_DLL1  ImgTransitionScan
( enum TRANS_SCAN_EDGE n32Edge, EROIBW8* pSrcImage,
 INT32 n32StartX, INT32 n32StartY, INT32 n32EndX, INT32 n32EndY, INT32 n32Threshold, INT32 n32MaxTransitions, EVector* pDstVect);
E_DLL0 INT16 E_DLL1  ImgVect1c2( enum ARITH_LOGIC_OPERATIONS nOperation, EVector *pSrcVect, INT32 n32Constant, EVector *pDstVect, INT32 n32StartGroup = 0, INT32 n32EndGroup = -1);
E_DLL0 INT16 E_DLL1  ImgVect1c2( enum ARITH_LOGIC_OPERATIONS nOperation, EVector *pSrcVect, FLOAT64 f64Constant, EVector* pDstVect);

E_DLL0 void E_DLL1  ImgSetupEqualize( EVector* pHistogram, EVector* pLookupTable);
E_DLL0 INT16 E_DLL1  ImgLineSegToVect
( EROIBW8* pSrcImage, EVector* pDstVect,
 INT32 n32StartX, INT32 n32StartY, INT32 n32EndX, INT32 n32EndY);
E_DLL0 INT16 E_DLL1  ImgVectToLineSeg( EVector* pSrcVect, EROIBW8* pDstImage);
E_DLL0 INT16 E_DLL1  ImgVectToLineSeg
( EVector* pSrcVect,
 INT32 n32StartX, INT32 n32StartY, INT32 n32EndX, INT32 n32EndY, EROIBW8* pDstImage);
E_DLL0 INT16 E_DLL1  ImgGetVectExtremes
( EVector* pSrcVect, EVector* pDstVect,
 INT32 n32LowThr = -43, INT32 n32HighThr = 42);
E_DLL0 INT16 E_DLL1  ImgGetVectExtremes
( EVector* pSrcVect, EVector* pDstVect,
 UINT32 un32LowThr = 85u, UINT32 un32HighThr = 170u);
// - OBSOLETE after 4.0

////////////////////////////////////////////////////////////////////////////////////////////////////
// Pixel statistics
//
// Binary Image
E_DLL0 UINT32 E_DLL1 ImgPixelCompare(EROIBW1* pSrcImage0, EROIBW1* pSrcImage1);
E_DLL0 UINT32 E_DLL1 ImgPixelCompareAligned(EROIBW1* pSrcImage0, EROIBW1* pSrcImage1);

// Gray level
E_DLL0 UINT32 E_DLL1  ImgCount( EROIBW8* pSrcImage, BOOL ( * Condition)( EBW8& Pixel));
E_DLL0 INT16 E_DLL1  ImgPixelMin( EROIBW8* pSrcImage, UINT8& un8MinPixVal);
E_DLL0 INT16 E_DLL1  ImgPixelMax( EROIBW8* pSrcImage, UINT8& un8MaxPixVal);
E_DLL0 INT16 E_DLL1  ImgPixelAverage( EROIBW8* pSrcImage, FLOAT32& f32Average);
E_DLL0 INT16 E_DLL1  ImgPixelStat( EROIBW8* pSrcImage, UINT8& un8MinPixVal, UINT8& un8MaxPixVal, FLOAT32& f32AveragePixVal);
E_DLL0 INT16 E_DLL1  ImgPixelStdDev( EROIBW8* pSrcImage, FLOAT32& f32StdDev, FLOAT32& f32AveragePixVal);
E_DLL0 INT16 E_DLL1  ImgPixelCount( EROIBW8* pSrcImage, UINT8 un8LowThr, UINT8 un8HighThr, INT32& n32PixelsBelow, INT32& n32PixelsBetween, INT32& n32PixelsAbove);
E_DLL0 INT16 E_DLL1  ImgArea( EROIBW8* pSrcImage, UINT8 un8Thr, INT32& n32PixelsAbove);
E_DLL0 INT16 E_DLL1  ImgAreaDoubleThreshold( EROIBW8* pSrcImage, UINT8 un8LowThr, UINT8 un8HighThr, INT32 &n32PixelsBetween);
E_DLL0 void E_DLL1  ImgPixelVariance( EROIBW8* pSrcImage, FLOAT32& f32Variance, FLOAT32& f32Mean);
E_DLL0 UINT32 E_DLL1  ImgPixelCompare( EROIBW8* pSrc0Image, EROIBW8* pSrc1Image);


E_DLL0 UINT32 E_DLL1  ImgArea( EROIBW8* pSrc);
E_DLL0 UINT32 E_DLL1  ImgArea( EROIBW8* pSrc, UINT32 un32Threshold);
E_DLL0 UINT32 E_DLL1  ImgMinimum( EROIBW8* pSrc);
E_DLL0 UINT32 E_DLL1  ImgMaximum( EROIBW8* pSrc);
E_DLL0 FLOAT32 E_DLL1  ImgAverage( EROIBW8* pSrc, UINT32* pun32Area = NULL);
E_DLL0 FLOAT32 E_DLL1  ImgVariance( EROIBW8* pSrc, FLOAT32* pf32Average = NULL, UINT32* pun32Area = NULL);
E_DLL0 void E_DLL1  ImgHisto( EROIBW8* pSrc, EBWHistogramVector* pHisto);

E_DLL0 void E_DLL1  ImgGravityCenter
( EROIBW8* pImage, 
 UINT32 un32Threshold, FLOAT32& f32GravityX, FLOAT32& f32GravityY);
E_DLL0 void E_DLL1  ImgCentroid
( EROIBW8* pImage, 
 FLOAT32& f32CenterX, FLOAT32& f32CenterY, EBW8Vector* pLut = NULL);
E_DLL0 void E_DLL1  ImgInertia
( EROIBW8* pImage, UINT32 un32Threshold, 
 FLOAT32& f32Mxx, FLOAT32& f32Mxy, FLOAT32& f32Myy,
 FLOAT32* pf32GravityX, FLOAT32* pf32GravityY, UINT32* pun32Area);
E_DLL0 void E_DLL1  ImgInertia
( EROIBW8* pImage, 
 FLOAT32& f32Mxx, FLOAT32& f32Mxy, FLOAT32& f32Myy,
 FLOAT32* pf32GravityX, FLOAT32* pf32GravityY, UINT32* pun32Area, EBW8Vector* pLut = NULL);

E_DLL0 void E_DLL1  ImgBinaryMoments
( EROIBW8* pImage, UINT32 un32Threshold,
 FLOAT32& f32M, FLOAT32& f32Mx, FLOAT32& f32My);
E_DLL0 void E_DLL1  ImgBinaryMoments
( EROIBW8* pImage, UINT32 un32Threshold,
 FLOAT32& f32M, FLOAT32& f32Mx, FLOAT32& f32My, FLOAT32& f32Mxx, FLOAT32& f32Mxy, FLOAT32& f32Myy);
E_DLL0 void E_DLL1  ImgWeightedMoments
( EROIBW8* pImage,
 FLOAT32& f32M, FLOAT32& f32Mx, FLOAT32& f32My);
E_DLL0 void E_DLL1  ImgWeightedMoments
( EROIBW8* pImage,
 FLOAT32& f32M, FLOAT32& f32Mx, FLOAT32& f32My, FLOAT32& f32Mxx, FLOAT32& f32Mxy, FLOAT32& f32Myy);
E_DLL0 void E_DLL1  ImgWeightedMoments
( EROIBW8* pImage,
 FLOAT32& f32M, FLOAT32& f32Mx, FLOAT32& f32My, FLOAT32& f32Mxx, FLOAT32& f32Mxy, FLOAT32& f32Myy,
 FLOAT32& f32Mxxx, FLOAT32& f32Mxxy, FLOAT32& f32Mxyy, FLOAT32& f32Myyy);
E_DLL0 void E_DLL1  ImgWeightedMoments
( EROIBW8* pImage,
 FLOAT32& f32M, FLOAT32& f32Mx, FLOAT32& f32My, FLOAT32& f32Mxx, FLOAT32& f32Mxy, FLOAT32& f32Myy,
 FLOAT32& f32Mxxx, FLOAT32& f32Mxxy, FLOAT32& f32Mxyy, FLOAT32& f32Myyy,
 FLOAT32& f32Mxxxx, FLOAT32& f32Mxxxy, FLOAT32& f32Mxxyy, FLOAT32& f32Mxyyy, FLOAT32& f32Myyyy);

E_DLL0 void E_DLL1  ImgWeighedMoments
( EROIBW8* pImage,
 FLOAT32& f32M, FLOAT32& f32Mx, FLOAT32& f32My);
E_DLL0 void E_DLL1  ImgWeighedMoments
( EROIBW8* pImage,
 FLOAT32& f32M, FLOAT32& f32Mx, FLOAT32& f32My, FLOAT32& f32Mxx, FLOAT32& f32Mxy, FLOAT32& f32Myy);
E_DLL0 void E_DLL1  ImgWeighedMoments
( EROIBW8* pImage,
 FLOAT32& f32M, FLOAT32& f32Mx, FLOAT32& f32My, FLOAT32& f32Mxx, FLOAT32& f32Mxy, FLOAT32& f32Myy,
 FLOAT32& f32Mxxx, FLOAT32& f32Mxxy, FLOAT32& f32Mxyy, FLOAT32& f32Myyy);
E_DLL0 void E_DLL1  ImgWeighedMoments
( EROIBW8* pImage,
 FLOAT32& f32M, FLOAT32& f32Mx, FLOAT32& f32My, FLOAT32& f32Mxx, FLOAT32& f32Mxy, FLOAT32& f32Myy,
 FLOAT32& f32Mxxx, FLOAT32& f32Mxxy, FLOAT32& f32Mxyy, FLOAT32& f32Myyy,
 FLOAT32& f32Mxxxx, FLOAT32& f32Mxxxy, FLOAT32& f32Mxxyy, FLOAT32& f32Mxyyy, FLOAT32& f32Myyyy);

E_DLL0 FLOAT32 E_DLL1  ImgRmsNoise( EROIBW8* pSrcImage, EROIBW8* pRefImage, enum IMG_REFERENCE_NOISE eReferenceNoise);
E_DLL0 FLOAT32 E_DLL1  ImgSignalNoiseRatio( EROIBW8* pSrcImage, EROIBW8* pRefImage, enum IMG_REFERENCE_NOISE eReferenceNoise = IMG_NOISE_NONE);

E_DLL0 FLOAT32 E_DLL1  ImgRmsNoise( EROIBW8* pSrcImage, EROIBW16* pRefImage, UINT32 un32Count, enum IMG_REFERENCE_NOISE eReferenceNoise);
E_DLL0 FLOAT32 E_DLL1  ImgSignalNoiseRatio( EROIBW8* pSrcImage, EROIBW16* pRefImage, UINT32 un32Count, enum IMG_REFERENCE_NOISE eReferenceNoise = IMG_NOISE_NONE);

E_DLL0 void E_DLL1  ImgCorrelogram( EROIBW8* pSrcX, EROIBW8* pSrcY, EImageBW8* pCorrelogram);
E_DLL0 void E_DLL1  ImgCorrelogram( EROIBW8* pSrcX, EROIBW8* pSrcY, EImageBW16* pCorrelogram);
E_DLL0 void E_DLL1  ImgLinearRegression( EROIBW8* pSrcX, EROIBW8* pSrcY, FLOAT32& f32Slope, FLOAT32& f32OriginY, FLOAT32& f32Correlation, BOOL bUnsaturated = TRUE);

// BW16
E_DLL0 UINT32 E_DLL1  ImgCount( EROIBW16* pSrcImage, BOOL ( * Condition)( EBW16& Pixel));
E_DLL0 UINT32 E_DLL1  ImgPixelCompare( EROIBW16* pSrc0Image, EROIBW16* pSrc1Image);

E_DLL0 void E_DLL1  ImgPixelCount( EROIBW16* pSrcImage, EBW16 bw16LowThr, EBW16 bw16HighThr, INT32& n32PixelsBelow, INT32& n32PixelsBetween, INT32& n32PixelsAbove);
E_DLL0 void E_DLL1  ImgPixelAverage( EROIBW16* pSrcImage, FLOAT32& f32Average);
E_DLL0 void E_DLL1  ImgPixelStdDev( EROIBW16* pSrcImage, FLOAT32& f32StdDev, FLOAT32& f32AveragePixVal);
E_DLL0 void E_DLL1  ImgPixelVariance( EROIBW16* pSrcImage, FLOAT32& f32Variance, FLOAT32& f32Mean);
E_DLL0 void E_DLL1  ImgPixelMin( EROIBW16* pSrcImage, EBW16& bw16MinPixVal);
E_DLL0 void E_DLL1  ImgPixelMax( EROIBW16* pSrcImage, EBW16& bw16MaxPixVal);
E_DLL0 void E_DLL1  ImgPixelStat( EROIBW16* pSrcImage, EBW16& bw16MinPixVal, EBW16& bw16MaxPixVal, FLOAT32& f32AveragePixVal);

E_DLL0 void E_DLL1  ImgArea( EROIBW16* pSrcImage, EBW16 bw16Thr, INT32& n32PixelsAbove);
E_DLL0 void E_DLL1  ImgAreaDoubleThreshold( EROIBW16* pSrcImage, EBW16 bw16LowThr, EBW16 bw16HighThr, INT32 &n32PixelsBetween);

E_DLL0 void E_DLL1  ImgGravityCenter
( EROIBW16* pImage, 
 UINT32 un32Threshold, FLOAT32& f32GravityX, FLOAT32& f32GravityY);

E_DLL0 void E_DLL1  ImgBinaryMoments
( EROIBW16* pImage, UINT32 un32Threshold,
 FLOAT32& f32M, FLOAT32& f32Mx, FLOAT32& f32My);
E_DLL0 void E_DLL1  ImgBinaryMoments
( EROIBW16* pImage, UINT32 un32Threshold,
 FLOAT32& f32M, FLOAT32& f32Mx, FLOAT32& f32My, FLOAT32& f32Mxx, FLOAT32& f32Mxy, FLOAT32& f32Myy);

E_DLL0 void E_DLL1  ImgWeightedMoments
( EROIBW16* pImage,
 FLOAT32& f32M, FLOAT32& f32Mx, FLOAT32& f32My);
E_DLL0 void E_DLL1  ImgWeightedMoments
( EROIBW16* pImage,
 FLOAT32& f32M, FLOAT32& f32Mx, FLOAT32& f32My, FLOAT32& f32Mxx, FLOAT32& f32Mxy, FLOAT32& f32Myy);
E_DLL0 void E_DLL1  ImgWeightedMoments
( EROIBW16* pImage,
 FLOAT32& f32M, FLOAT32& f32Mx, FLOAT32& f32My, FLOAT32& f32Mxx, FLOAT32& f32Mxy, FLOAT32& f32Myy,
 FLOAT32& f32Mxxx, FLOAT32& f32Mxxy, FLOAT32& f32Mxyy, FLOAT32& f32Myyy);
E_DLL0 void E_DLL1  ImgWeightedMoments
( EROIBW16* pImage,
 FLOAT32& f32M, FLOAT32& f32Mx, FLOAT32& f32My, FLOAT32& f32Mxx, FLOAT32& f32Mxy, FLOAT32& f32Myy,
 FLOAT32& f32Mxxx, FLOAT32& f32Mxxy, FLOAT32& f32Mxyy, FLOAT32& f32Myyy,
 FLOAT32& f32Mxxxx, FLOAT32& f32Mxxxy, FLOAT32& f32Mxxyy, FLOAT32& f32Mxyyy, FLOAT32& f32Myyyy);

E_DLL0 void E_DLL1  ImgWeighedMoments
( EROIBW16* pImage,
 FLOAT32& f32M, FLOAT32& f32Mx, FLOAT32& f32My);
E_DLL0 void E_DLL1  ImgWeighedMoments
( EROIBW16* pImage,
 FLOAT32& f32M, FLOAT32& f32Mx, FLOAT32& f32My, FLOAT32& f32Mxx, FLOAT32& f32Mxy, FLOAT32& f32Myy);
E_DLL0 void E_DLL1  ImgWeighedMoments
( EROIBW16* pImage,
 FLOAT32& f32M, FLOAT32& f32Mx, FLOAT32& f32My, FLOAT32& f32Mxx, FLOAT32& f32Mxy, FLOAT32& f32Myy,
 FLOAT32& f32Mxxx, FLOAT32& f32Mxxy, FLOAT32& f32Mxyy, FLOAT32& f32Myyy);
E_DLL0 void E_DLL1  ImgWeighedMoments
( EROIBW16* pImage,
 FLOAT32& f32M, FLOAT32& f32Mx, FLOAT32& f32My, FLOAT32& f32Mxx, FLOAT32& f32Mxy, FLOAT32& f32Myy,
 FLOAT32& f32Mxxx, FLOAT32& f32Mxxy, FLOAT32& f32Mxyy, FLOAT32& f32Myyy,
 FLOAT32& f32Mxxxx, FLOAT32& f32Mxxxy, FLOAT32& f32Mxxyy, FLOAT32& f32Mxyyy, FLOAT32& f32Myyyy);

E_DLL0 FLOAT32 E_DLL1  ImgRmsNoise( EROIBW16* pSrcImage, EROIBW16* pRefImage, enum IMG_REFERENCE_NOISE eReferenceNoise);
E_DLL0 FLOAT32 E_DLL1  ImgSignalNoiseRatio( EROIBW16* pSrcImage, EROIBW16* pRefImage, enum IMG_REFERENCE_NOISE eReferenceNoise = IMG_NOISE_NONE);

// Color
E_DLL0 UINT32 E_DLL1  ImgCount( EROIC24* pSrcImage, BOOL ( * Condition)( EC24& Pixel));
E_DLL0 UINT32 E_DLL1  ImgPixelCompare( EROIC24* pSrc0Image, EROIC24* pSrc1Image);

E_DLL0 void E_DLL1  ImgPixelAverage
( EROIC24* pSrcImage,
 FLOAT32& f32Mean0, FLOAT32& f32Mean1, FLOAT32& f32Mean2);

E_DLL0 void E_DLL1  ImgPixelVariance
( EROIC24* pSrcImage,
 FLOAT32& f32Variance0, FLOAT32& f32Variance1, FLOAT32& f32Variance2,
 FLOAT32& f32Covariance01, FLOAT32& f32Covariance12, FLOAT32& f32Covariance20,
 FLOAT32& f32Mean0, FLOAT32& f32Mean1, FLOAT32& f32Mean2);
E_DLL0 void E_DLL1  ImgPixelStdDev
( EROIC24* pSrcImage,
 FLOAT32& f32StdDev0, FLOAT32& f32StdDev1, FLOAT32& f32StdDev2,
 FLOAT32& f32Correlation01, FLOAT32& f32Correlation12, FLOAT32& f32Correlation20,
 FLOAT32& f32Mean0, FLOAT32& f32Mean1, FLOAT32& f32Mean2);

E_DLL0 FLOAT32 E_DLL1  ImgRmsNoise( EROIC24* pSrcImage, EROIC24* pRefImage, enum IMG_REFERENCE_NOISE eReferenceNoise);
E_DLL0 FLOAT32 E_DLL1  ImgSignalNoiseRatio( EROIC24* pSrcImage, EROIC24* pRefImage, enum IMG_REFERENCE_NOISE eReferenceNoise = IMG_NOISE_NONE);

////////////////////////////////////////////////////////////////////////////////////////////////////
// Warping
//
E_DLL0 void E_DLL1  ImgSetCircleWarp
( FLOAT32 f32XCenter, FLOAT32 f32YCenter,
 INT32 n32NumCircles, FLOAT32 f32MinRadius, FLOAT32 f32MaxRadius,
 INT32 n32NumRadii, FLOAT32 f32MinAngle, FLOAT32 f32MaxAngle,
 EImageBW16* pWarpXImage, EImageBW16* pWarpYImage);

// Gray level
E_DLL0 INT16 E_DLL1  ImgWarp
( EROIBW8* pSrcImage, EROIBW8* pDstImage, 
 EImageBW16* pWarpXImage, EImageBW16* pWarpYImage,
 INT32 n32ShiftX = 0, INT32 n32ShiftY = 0);
E_DLL0 INT16 E_DLL1  ImgWarp( EROIBW8* pSrcImage, EROIBW8* pDstImage, EImageBW32* pWarpXYImage);

// Color
E_DLL0 void E_DLL1  ImgWarp
( EROIC24* pSrcImage, EROIC24* pDstImage,
 EImageBW16* pWarpXImage, EImageBW16* pWarpYImage,
 INT32 n32ShiftX = 0, INT32 n32ShiftY = 0);








////////////////////////////////////////////////////////////////////////////////////////////////////
// Contouring
//

// Gray level
E_DLL0 void E_DLL1  ImgContour
( EROIBW8* pImage, 
 enum CONTOUR_MODE eContourMode, 
 INT32 n32StartX,
 INT32 n32StartY,
 enum CONTOUR_THRESHOLD eThresholdMode, 
 UINT32 un32Threshold, 
 enum CONNEXITY eConnexity,
 EPathVector* pPath);

E_DLL0 void E_DLL1  ImgContour
( EROIBW8* pImage, 
 enum CONTOUR_MODE eContourMode, 
 INT32 n32StartX,
 INT32 n32StartY,
 enum CONTOUR_THRESHOLD eThresholdMode, 
 UINT32 un32Threshold, 
 enum CONNEXITY eConnexity,
 EBW8PathVector* pBW8Path,
 BOOL bFreeman = FALSE);

// + OBSOLETE after 4.0
E_DLL0 INT16 E_DLL1  ImgContour
( 
 EROIBW8* pSrc,
 enum CONTOUR_MODE n32Mode,
 INT32 n32StartX,
 INT32 n32StartY,
 enum CONTOUR_THRESHOLD n32ThresholdMode,
 UINT32 un32Threshold,
 enum CONNEXITY n32Connexity,
 EVector* pDstVect);
// - OBSOLETE after 4.0

// BW16
E_DLL0 void E_DLL1  ImgContour
( EROIBW16* pImage, 
 enum CONTOUR_MODE eContourMode, 
 INT32 n32StartX,
 INT32 n32StartY,
 enum CONTOUR_THRESHOLD eThresholdMode, 
 UINT32 un32Threshold, 
 enum CONNEXITY eConnexity,
 EPathVector* pPath);

E_DLL0 void E_DLL1  ImgContour
( EROIBW16* pImage, 
 enum CONTOUR_MODE eContourMode, 
 INT32 n32StartX,
 INT32 n32StartY,
 enum CONTOUR_THRESHOLD eThresholdMode, 
 UINT32 un32Threshold, 
 enum CONNEXITY eConnexity,
 EBW16PathVector* pBW16Path,
 BOOL bFreeman = FALSE);

///////////////////////////////////////////////////////////////
// Linear transforms
//

// Gray level
E_DLL0 void E_DLL1  ImgVerticalMirror( EROIBW8* pSrcImage);
E_DLL0 void E_DLL1  ImgHorizontalMirror( EROIBW8* pSrcImage);

E_DLL0 void E_DLL1  ImgLinearTransform
( EROIBW8* pSrcImage,
 FLOAT32 f32Axx, FLOAT32 f32Axy, FLOAT32 f32Ax, 
 FLOAT32 f32Ayx, FLOAT32 f32Ayy, FLOAT32 f32Ay,
 EROIBW8* pDstImage,
 INT32 n32InterpolationBits = 0);

E_DLL0 INT16 E_DLL1  ImgScaleRotate
( EROIBW8* pSrcImage,
 FLOAT32 f32SrcPivotX, FLOAT32 f32SrcPivotY,
 FLOAT32 f32DstPivotX, FLOAT32 f32DstPivotY,
 FLOAT32 f32ScaleX, FLOAT32 f32ScaleY,
 FLOAT32 f32Rotation,
 EROIBW8* pDstImage,
 INT32 n32InterpolationBits = 0);

E_DLL0 INT16 E_DLL1  ImgScaleRotate
( EROIBW8* pImage,
 FLOAT32 f32SrcPivotX, FLOAT32 f32SrcPivotY,
 FLOAT32 f32DstPivotX, FLOAT32 f32DstPivotY,
 FLOAT32 f32ScaleX, FLOAT32 f32ScaleY,
 FLOAT32 f32Rotation,
 INT32 n32InterpolationBits = 0);

E_DLL0 void E_DLL1  ImgRegister
( EROIBW8* pSrcImage, EROIBW8* pDstImage,
 FLOAT32 f32SrcPivot0X, FLOAT32 f32SrcPivot0Y,
 FLOAT32 f32DstPivot0X, FLOAT32 f32DstPivot0Y,
 INT32 n32InterpolationBits = 0);

E_DLL0 void E_DLL1  ImgRegister
( EROIBW8* pSrcImage, EROIBW8* pDstImage,
 FLOAT32 f32SrcPivot0X, FLOAT32 f32SrcPivot0Y,
 FLOAT32 f32SrcPivot1X, FLOAT32 f32SrcPivot1Y,
 FLOAT32 f32DstPivot0X, FLOAT32 f32DstPivot0Y,
 FLOAT32 f32DstPivot1X, FLOAT32 f32DstPivot1Y,
 INT32 n32InterpolationBits = 0, BOOL bResize = FALSE);

E_DLL0 void E_DLL1  ImgRegister
( EROIBW8* pSrcImage, EROIBW8* pDstImage,
 FLOAT32 f32SrcPivot0X, FLOAT32 f32SrcPivot0Y,
 FLOAT32 f32SrcPivot1X, FLOAT32 f32SrcPivot1Y,
 FLOAT32 f32SrcPivot2X, FLOAT32 f32SrcPivot2Y,
 FLOAT32 f32DstPivot0X, FLOAT32 f32DstPivot0Y,
 FLOAT32 f32DstPivot1X, FLOAT32 f32DstPivot1Y,
 FLOAT32 f32DstPivot2X, FLOAT32 f32DstPivot2Y,
 INT32 n32InterpolationBits = 0);

E_DLL0 INT16 E_DLL1  ImgShrink( EROIBW8* pSrcImage, EROIBW8* pDstImage);
E_DLL0 void E_DLL1  ImgHalve( EROIBW8* pSrc, EROIBW8* pDst, BOOL bDropOdd = TRUE);

// BW16
E_DLL0 void E_DLL1  ImgVerticalMirror( EROIBW16* pSrcImage);
E_DLL0 void E_DLL1  ImgHorizontalMirror( EROIBW16* pSrcImage);

E_DLL0 void E_DLL1  ImgLinearTransform
( EROIBW16* pSrcImage,
 FLOAT32 f32Axx, FLOAT32 f32Axy, FLOAT32 f32Ax, 
 FLOAT32 f32Ayx, FLOAT32 f32Ayy, FLOAT32 f32Ay,
 EROIBW16* pDstImage,
 INT32 n32InterpolationBits = 0);

E_DLL0 void E_DLL1  ImgScaleRotate
( EROIBW16* pSrcImage,
 FLOAT32 f32SrcPivotX, FLOAT32 f32SrcPivotY,
 FLOAT32 f32DstPivotX, FLOAT32 f32DstPivotY,
 FLOAT32 f32ScaleX, FLOAT32 f32ScaleY,
 FLOAT32 f32Rotation,
 EROIBW16* pDstImage,
 INT32 n32InterpolationBits = 0);

E_DLL0 void E_DLL1  ImgScaleRotate
( EROIBW16* pImage,
 FLOAT32 f32SrcPivotX, FLOAT32 f32SrcPivotY,
 FLOAT32 f32DstPivotX, FLOAT32 f32DstPivotY,
 FLOAT32 f32ScaleX, FLOAT32 f32ScaleY,
 FLOAT32 f32Rotation,
 INT32 n32InterpolationBits = 0);

E_DLL0 void E_DLL1  ImgRegister
( EROIBW16* pSrcImage, EROIBW16* pDstImage,
 FLOAT32 f32SrcPivot0X, FLOAT32 f32SrcPivot0Y,
 FLOAT32 f32DstPivot0X, FLOAT32 f32DstPivot0Y,
 INT32 n32InterpolationBits = 0);

E_DLL0 void E_DLL1  ImgRegister
( EROIBW16* pSrcImage, EROIBW16* pDstImage,
 FLOAT32 f32SrcPivot0X, FLOAT32 f32SrcPivot0Y,
 FLOAT32 f32SrcPivot1X, FLOAT32 f32SrcPivot1Y,
 FLOAT32 f32DstPivot0X, FLOAT32 f32DstPivot0Y,
 FLOAT32 f32DstPivot1X, FLOAT32 f32DstPivot1Y,
 INT32 n32InterpolationBits = 0, BOOL bResize = FALSE);

E_DLL0 void E_DLL1  ImgRegister
( EROIBW16* pSrcImage, EROIBW16* pDstImage,
 FLOAT32 f32SrcPivot0X, FLOAT32 f32SrcPivot0Y,
 FLOAT32 f32SrcPivot1X, FLOAT32 f32SrcPivot1Y,
 FLOAT32 f32SrcPivot2X, FLOAT32 f32SrcPivot2Y,
 FLOAT32 f32DstPivot0X, FLOAT32 f32DstPivot0Y,
 FLOAT32 f32DstPivot1X, FLOAT32 f32DstPivot1Y,
 FLOAT32 f32DstPivot2X, FLOAT32 f32DstPivot2Y,
 INT32 n32InterpolationBits = 0);

E_DLL0 void E_DLL1  ImgShrink( EROIBW16* pSrcImage, EROIBW16* pDstImage);

// Color
E_DLL0 void E_DLL1  ImgVerticalMirror( EROIC24* pSrcImage);
E_DLL0 void E_DLL1  ImgHorizontalMirror( EROIC24* pSrcImage);

E_DLL0 void E_DLL1  ImgLinearTransform
( EROIC24* pSrcImage,
 FLOAT32 f32Axx, FLOAT32 f32Axy, FLOAT32 f32Ax, 
 FLOAT32 f32Ayx, FLOAT32 f32Ayy, FLOAT32 f32Ay,
 EROIC24* pDstImage,
 INT32 n32InterpolationBits = 0);

E_DLL0 void E_DLL1  ImgScaleRotate
( EROIC24* pSrcImage,
 FLOAT32 f32SrcPivotX, FLOAT32 f32SrcPivotY,
 FLOAT32 f32DstPivotX, FLOAT32 f32DstPivotY,
 FLOAT32 f32ScaleX, FLOAT32 f32ScaleY,
 FLOAT32 f32Rotation,
 EROIC24* pDstImage,
 INT32 n32InterpolationBits = 0);

E_DLL0 void E_DLL1  ImgRegister
( EROIC24* pSrcImage, EROIC24* pDstImage,
 FLOAT32 f32SrcPivot0X, FLOAT32 f32SrcPivot0Y,
 FLOAT32 f32DstPivot0X, FLOAT32 f32DstPivot0Y,
 INT32 n32InterpolationBits = 0);

E_DLL0 void E_DLL1  ImgRegister
( EROIC24* pSrcImage, EROIC24* pDstImage,
 FLOAT32 f32SrcPivot0X, FLOAT32 f32SrcPivot0Y, 
 FLOAT32 f32SrcPivot1X, FLOAT32 f32SrcPivot1Y,
 FLOAT32 f32DstPivot0X, FLOAT32 f32DstPivot0Y,
 FLOAT32 f32DstPivot1X, FLOAT32 f32DstPivot1Y,
 INT32 n32InterpolationBits = 0, BOOL bResize = FALSE);

E_DLL0 void E_DLL1  ImgRegister
( EROIC24* pSrcImage, EROIC24* pDstImage,
 FLOAT32 f32SrcPivot0X, FLOAT32 f32SrcPivot0Y,
 FLOAT32 f32SrcPivot1X, FLOAT32 f32SrcPivot1Y,
 FLOAT32 f32SrcPivot2X, FLOAT32 f32SrcPivot2Y,
 FLOAT32 f32DstPivot0X, FLOAT32 f32DstPivot0Y,
 FLOAT32 f32DstPivot1X, FLOAT32 f32DstPivot1Y,
 FLOAT32 f32DstPivot2X, FLOAT32 f32DstPivot2Y,
 INT32 n32InterpolationBits = 0);

E_DLL0 void E_DLL1  ImgShrink( EROIC24* pSrcImage, EROIC24* pDstImage);

////////////////////////////////////////////////////////////////////////////////////////////////////
// Complex images

E_DLL0 void E_DLL1  ImgComplexModulus
( EROIComplex64* pSrcImage, EROIBW8* pDstImage, FLOAT32 f32Scale = 1.f,
 BOOL bLog = FALSE, FLOAT32 f32LogScale = 46.16624130845f);
E_DLL0 void E_DLL1  ImgComplexRescaledModulus
( EROIComplex64* pSrcImage, EROIBW8* pDstImage, FLOAT32 f32Scale = 1.f,
 BOOL bLog = FALSE, FLOAT32 f32LogScale = 46.16624130845f);

E_DLL0 void E_DLL1  ImgComplexArgument( EROIComplex64* pSrcImage, EROIBW8* pDstImage);

E_DLL0 void E_DLL1  ImgComplexDiscEnergy( EROIComplex64* pSrcImage, EVector* pDstVector);

E_DLL0 void E_DLL1  ImgSlowDFT( EROIBW8* pSrcImage, EROIComplex64* pDstImage, FLOAT32 f32Scale = 1.f);
E_DLL0 void E_DLL1  ImgFastDFT( EROIBW8* pSrcImage, EROIComplex64* pDstImage, FLOAT32 f32Scale = 1.f);

////////////////////////////////////////////////////////////////////////////////////////////////////
// Stream operators
#include <iostream>

E_DLL0 std::ostream& E_DLL1  operator<<( std::ostream& strm, const EPath& obj);
E_DLL0 std::ostream& E_DLL1  operator<<( std::ostream& strm, const EBW8Path& obj);
E_DLL0 std::ostream& E_DLL1  operator<<( std::ostream& strm, const EC24Path& obj);
E_DLL0 std::ostream&  E_DLL1  operator<<( std::ostream& strm, const EPeak& obj);

inline void ImgInvert(EROIBW8* source, EROIBW8* destination)
{
  ImgOper(IMG_INVERT,source,destination);
}
inline void ImgInvert(EROIBW16* source, EROIBW16* destination)
{
  ImgOper(IMG_INVERT,source,destination);
}
inline void ImgInvert(EROIC24* source, EROIC24* destination)
{
  ImgOper(IMG_INVERT,source,destination);
}
inline void ImgAdd(EBW8 pix, EROIBW8* source, EROIBW8* destination)
{
  ImgOper(IMG_ADD,pix,source,destination);
}
inline void ImgAdd(EROIBW8* source, EBW8 pix, EROIBW8* destination)
{
  ImgOper(IMG_ADD,source,pix,destination);
}
inline void ImgAdd(EROIBW8* source1, EROIBW8* source2, EROIBW8* destination)
{
  ImgOper(IMG_ADD,source1,source2,destination);
}
inline void ImgAdd(EBW16 pix, EROIBW16* source, EROIBW16* destination)
{
  ImgOper(IMG_ADD,pix,source,destination);
}
inline void ImgAdd(EROIBW16* source, EBW16 pix, EROIBW16* destination)
{
  ImgOper(IMG_ADD,source,pix,destination);
}
inline void ImgAdd(EROIBW16* source1, EROIBW16* source2, EROIBW16* destination)
{
  ImgOper(IMG_ADD,source1,source2,destination);
}
inline void ImgAdd(EC24 pix, EROIC24* source, EROIC24* destination)
{
  ImgOper(IMG_ADD,pix,source,destination);
}
inline void ImgAdd(EROIC24* source, EC24 pix, EROIC24* destination)
{
  ImgOper(IMG_ADD,source,pix,destination);
}
inline void ImgAdd(EROIC24* source1, EROIC24* source2, EROIC24* destination)
{
  ImgOper(IMG_ADD,source1,source2,destination);
}
inline void ImgSubtract(EBW8 pix, EROIBW8* source, EROIBW8* destination)
{
  ImgOper(IMG_SUBTRACT,pix,source,destination);
}
inline void ImgSubtract(EROIBW8* source, EBW8 pix, EROIBW8* destination)
{
  ImgOper(IMG_SUBTRACT,source,pix,destination);
}
inline void ImgSubtract(EROIBW8* source1, EROIBW8* source2, EROIBW8* destination)
{
  ImgOper(IMG_SUBTRACT,source1,source2,destination);
}
inline void ImgSubtract(EBW16 pix, EROIBW16* source, EROIBW16* destination)
{
  ImgOper(IMG_SUBTRACT,pix,source,destination);
}
inline void ImgSubtract(EROIBW16* source, EBW16 pix, EROIBW16* destination)
{
  ImgOper(IMG_SUBTRACT,source,pix,destination);
}
inline void ImgSubtract(EROIBW16* source1, EROIBW16* source2, EROIBW16* destination)
{
  ImgOper(IMG_SUBTRACT,source1,source2,destination);
}
inline void ImgSubtract(EC24 pix, EROIC24* source, EROIC24* destination)
{
  ImgOper(IMG_SUBTRACT,pix,source,destination);
}
inline void ImgSubtract(EROIC24* source, EC24 pix, EROIC24* destination)
{
  ImgOper(IMG_SUBTRACT,source,pix,destination);
}
inline void ImgSubtract(EROIC24* source1, EROIC24* source2, EROIC24* destination)
{
  ImgOper(IMG_SUBTRACT,source1,source2,destination);
}
inline void ImgMultiply(EBW8 pix, EROIBW8* source, EROIBW8* destination)
{
  ImgOper(IMG_MULTIPLY,pix,source,destination);
}
inline void ImgMultiply(EROIBW8* source, EBW8 pix, EROIBW8* destination)
{
  ImgOper(IMG_MULTIPLY,source,pix,destination);
}
inline void ImgMultiply(EROIBW8* source1, EROIBW8* source2, EROIBW8* destination)
{
  ImgOper(IMG_MULTIPLY,source1,source2,destination);
}
inline void ImgMultiply(EBW16 pix, EROIBW16* source, EROIBW16* destination)
{
  ImgOper(IMG_MULTIPLY,pix,source,destination);
}
inline void ImgMultiply(EROIBW16* source, EBW16 pix, EROIBW16* destination)
{
  ImgOper(IMG_MULTIPLY,source,pix,destination);
}
inline void ImgMultiply(EROIBW16* source1, EROIBW16* source2, EROIBW16* destination)
{
  ImgOper(IMG_MULTIPLY,source1,source2,destination);
}
inline void ImgMultiply(EC24 pix, EROIC24* source, EROIC24* destination)
{
  ImgOper(IMG_MULTIPLY,pix,source,destination);
}
inline void ImgMultiply(EROIC24* source, EC24 pix, EROIC24* destination)
{
  ImgOper(IMG_MULTIPLY,source,pix,destination);
}
inline void ImgMultiply(EROIC24* source1, EROIC24* source2, EROIC24* destination)
{
  ImgOper(IMG_MULTIPLY,source1,source2,destination);
}
inline void ImgDivide(EBW8 pix, EROIBW8* source, EROIBW8* destination)
{
  ImgOper(IMG_DIVIDE,pix,source,destination);
}
inline void ImgDivide(EROIBW8* source, EBW8 pix, EROIBW8* destination)
{
  ImgOper(IMG_DIVIDE,source,pix,destination);
}
inline void ImgDivide(EROIBW8* source1, EROIBW8* source2, EROIBW8* destination)
{
  ImgOper(IMG_DIVIDE,source1,source2,destination);
}
inline void ImgDivide(EBW16 pix, EROIBW16* source, EROIBW16* destination)
{
  ImgOper(IMG_DIVIDE,pix,source,destination);
}
inline void ImgDivide(EROIBW16* source, EBW16 pix, EROIBW16* destination)
{
  ImgOper(IMG_DIVIDE,source,pix,destination);
}
inline void ImgDivide(EROIBW16* source1, EROIBW16* source2, EROIBW16* destination)
{
  ImgOper(IMG_DIVIDE,source1,source2,destination);
}
inline void ImgDivide(EC24 pix, EROIC24* source, EROIC24* destination)
{
  ImgOper(IMG_DIVIDE,pix,source,destination);
}
inline void ImgDivide(EROIC24* source, EC24 pix, EROIC24* destination)
{
  ImgOper(IMG_DIVIDE,source,pix,destination);
}
inline void ImgDivide(EROIC24* source1, EROIC24* source2, EROIC24* destination)
{
  ImgOper(IMG_DIVIDE,source1,source2,destination);
}
inline void ImgModulo(EBW8 pix, EROIBW8* source, EROIBW8* destination)
{
  ImgOper(IMG_MODULO,pix,source,destination);
}
inline void ImgModulo(EROIBW8* source, EBW8 pix, EROIBW8* destination)
{
  ImgOper(IMG_MODULO,source,pix,destination);
}
inline void ImgModulo(EROIBW8* source1, EROIBW8* source2, EROIBW8* destination)
{
  ImgOper(IMG_MODULO,source1,source2,destination);
}
inline void ImgModulo(EBW16 pix, EROIBW16* source, EROIBW16* destination)
{
  ImgOper(IMG_MODULO,pix,source,destination);
}
inline void ImgModulo(EROIBW16* source, EBW16 pix, EROIBW16* destination)
{
  ImgOper(IMG_MODULO,source,pix,destination);
}
inline void ImgModulo(EROIBW16* source1, EROIBW16* source2, EROIBW16* destination)
{
  ImgOper(IMG_MODULO,source1,source2,destination);
}
inline void ImgModulo(EC24 pix, EROIC24* source, EROIC24* destination)
{
  ImgOper(IMG_MODULO,pix,source,destination);
}
inline void ImgModulo(EROIC24* source, EC24 pix, EROIC24* destination)
{
  ImgOper(IMG_MODULO,source,pix,destination);
}
inline void ImgModulo(EROIC24* source1, EROIC24* source2, EROIC24* destination)
{
  ImgOper(IMG_MODULO,source1,source2,destination);
}
inline void ImgShiftLeft(EROIBW8* source, EBW8 pix, EROIBW8* destination)
{
  ImgOper(IMG_SHIFT_LEFT,source,pix,destination);
}
inline void ImgShiftLeft(EROIBW16* source, EBW16 pix, EROIBW16* destination)
{
  ImgOper(IMG_SHIFT_LEFT,source,pix,destination);
}
inline void ImgShiftLeft(EROIC24* source, EC24 pix, EROIC24* destination)
{
  ImgOper(IMG_SHIFT_LEFT,source,pix,destination);
}
inline void ImgShiftRight(EROIBW8* source, EBW8 pix, EROIBW8* destination)
{
  ImgOper(IMG_SHIFT_RIGHT,source,pix,destination);
}
inline void ImgShiftRight(EROIBW16* source, EBW16 pix, EROIBW16* destination)
{
  ImgOper(IMG_SHIFT_RIGHT,source,pix,destination);
}
inline void ImgShiftRight(EROIC24* source, EC24 pix, EROIC24* destination)
{
  ImgOper(IMG_SHIFT_RIGHT,source,pix,destination);
}
inline void ImgShiftLeft(EROIBW8* source, UINT8 pix, EROIBW8* destination)
{
  ImgOper(IMG_SHIFT_LEFT, source, EBW8(pix), destination);
}
inline void ImgShiftLeft(EROIBW16* source, UINT16 pix, EROIBW16* destination)
{
  ImgOper(IMG_SHIFT_LEFT, source, EBW16(pix), destination);
}
inline void ImgShiftLeft(EROIC24* source, TripletUINT8 pix, EROIC24* destination)
{
  EC24 pixel(pix.v0, pix.v1, pix.v2);
  ImgOper(IMG_SHIFT_LEFT, source, pixel, destination);
}
inline void ImgShiftRight(EROIBW8* source, UINT8 pix, EROIBW8* destination)
{
  ImgOper(IMG_SHIFT_RIGHT, source, EBW8(pix), destination);
}
inline void ImgShiftRight(EROIBW16* source, UINT16 pix, EROIBW16* destination)
{
  ImgOper(IMG_SHIFT_RIGHT, source, EBW16(pix), destination);
}
inline void ImgShiftRight(EROIC24* source, TripletUINT8 pix, EROIC24* destination)
{
  EC24 pixel(pix.v0, pix.v1, pix.v2);
  ImgOper(IMG_SHIFT_RIGHT, source, pixel, destination);
}
inline void ImgScaledAdd(EBW8 pix, EROIBW8* source, EROIBW8* destination)
{
  ImgOper(IMG_SCALED_ADD,pix,source,destination);
}
inline void ImgScaledAdd(EROIBW8* source, EBW8 pix, EROIBW8* destination)
{
  ImgOper(IMG_SCALED_ADD,source,pix,destination);
}
inline void ImgScaledAdd(EROIBW8* source1, EROIBW8* source2, EROIBW8* destination)
{
  ImgOper(IMG_SCALED_ADD,source1,source2,destination);
}
inline void ImgScaledAdd(EBW16 pix, EROIBW16* source, EROIBW16* destination)
{
  ImgOper(IMG_SCALED_ADD,pix,source,destination);
}
inline void ImgScaledAdd(EROIBW16* source, EBW16 pix, EROIBW16* destination)
{
  ImgOper(IMG_SCALED_ADD,source,pix,destination);
}
inline void ImgScaledAdd(EROIBW16* source1, EROIBW16* source2, EROIBW16* destination)
{
  ImgOper(IMG_SCALED_ADD,source1,source2,destination);
}
inline void ImgScaledAdd(EC24 pix, EROIC24* source, EROIC24* destination)
{
  ImgOper(IMG_SCALED_ADD,pix,source,destination);
}
inline void ImgScaledAdd(EROIC24* source, EC24 pix, EROIC24* destination)
{
  ImgOper(IMG_SCALED_ADD,source,pix,destination);
}
inline void ImgScaledAdd(EROIC24* source1, EROIC24* source2, EROIC24* destination)
{
  ImgOper(IMG_SCALED_ADD,source1,source2,destination);
}
inline void ImgScaledSubtract(EBW8 pix, EROIBW8* source, EROIBW8* destination)
{
  ImgOper(IMG_SCALED_SUBTRACT,pix,source,destination);
}
inline void ImgScaledSubtract(EROIBW8* source, EBW8 pix, EROIBW8* destination)
{
  ImgOper(IMG_SCALED_SUBTRACT,source,pix,destination);
}
inline void ImgScaledSubtract(EROIBW8* source1, EROIBW8* source2, EROIBW8* destination)
{
  ImgOper(IMG_SCALED_SUBTRACT,source1,source2,destination);
}
inline void ImgScaledSubtract(EBW16 pix, EROIBW16* source, EROIBW16* destination)
{
  ImgOper(IMG_SCALED_SUBTRACT,pix,source,destination);
}
inline void ImgScaledSubtract(EROIBW16* source, EBW16 pix, EROIBW16* destination)
{
  ImgOper(IMG_SCALED_SUBTRACT,source,pix,destination);
}
inline void ImgScaledSubtract(EROIBW16* source1, EROIBW16* source2, EROIBW16* destination)
{
  ImgOper(IMG_SCALED_SUBTRACT,source1,source2,destination);
}
inline void ImgScaledSubtract(EC24 pix, EROIC24* source, EROIC24* destination)
{
  ImgOper(IMG_SCALED_SUBTRACT,pix,source,destination);
}
inline void ImgScaledSubtract(EROIC24* source, EC24 pix, EROIC24* destination)
{
  ImgOper(IMG_SCALED_SUBTRACT,source,pix,destination);
}
inline void ImgScaledSubtract(EROIC24* source1, EROIC24* source2, EROIC24* destination)
{
  ImgOper(IMG_SCALED_SUBTRACT,source1,source2,destination);
}
inline void ImgScaledMultiply(EBW8 pix, EROIBW8* source, EROIBW8* destination)
{
  ImgOper(IMG_SCALED_MULTIPLY,pix,source,destination);
}
inline void ImgScaledMultiply(EROIBW8* source, EBW8 pix, EROIBW8* destination)
{
  ImgOper(IMG_SCALED_MULTIPLY,source,pix,destination);
}
inline void ImgScaledMultiply(EROIBW8* source1, EROIBW8* source2, EROIBW8* destination)
{
  ImgOper(IMG_SCALED_MULTIPLY,source1,source2,destination);
}
inline void ImgScaledMultiply(EBW16 pix, EROIBW16* source, EROIBW16* destination)
{
  ImgOper(IMG_SCALED_MULTIPLY,pix,source,destination);
}
inline void ImgScaledMultiply(EROIBW16* source, EBW16 pix, EROIBW16* destination)
{
  ImgOper(IMG_SCALED_MULTIPLY,source,pix,destination);
}
inline void ImgScaledMultiply(EROIBW16* source1, EROIBW16* source2, EROIBW16* destination)
{
  ImgOper(IMG_SCALED_MULTIPLY,source1,source2,destination);
}
inline void ImgScaledMultiply(EC24 pix, EROIC24* source, EROIC24* destination)
{
  ImgOper(IMG_SCALED_MULTIPLY,pix,source,destination);
}
inline void ImgScaledMultiply(EROIC24* source, EC24 pix, EROIC24* destination)
{
  ImgOper(IMG_SCALED_MULTIPLY,source,pix,destination);
}
inline void ImgScaledMultiply(EROIC24* source1, EROIC24* source2, EROIC24* destination)
{
  ImgOper(IMG_SCALED_MULTIPLY,source1,source2,destination);
}
inline void ImgScaledDivide(EBW8 pix, EROIBW8* source, EROIBW8* destination)
{
  ImgOper(IMG_SCALED_DIVIDE,pix,source,destination);
}
inline void ImgScaledDivide(EROIBW8* source, EBW8 pix, EROIBW8* destination)
{
  ImgOper(IMG_SCALED_DIVIDE,source,pix,destination);
}
inline void ImgScaledDivide(EROIBW8* source1, EROIBW8* source2, EROIBW8* destination)
{
  ImgOper(IMG_SCALED_DIVIDE,source1,source2,destination);
}
inline void ImgScaledDivide(EBW16 pix, EROIBW16* source, EROIBW16* destination)
{
  ImgOper(IMG_SCALED_DIVIDE,pix,source,destination);
}
inline void ImgScaledDivide(EROIBW16* source, EBW16 pix, EROIBW16* destination)
{
  ImgOper(IMG_SCALED_DIVIDE,source,pix,destination);
}
inline void ImgScaledDivide(EROIBW16* source1, EROIBW16* source2, EROIBW16* destination)
{
  ImgOper(IMG_SCALED_DIVIDE,source1,source2,destination);
}
inline void ImgScaledDivide(EC24 pix, EROIC24* source, EROIC24* destination)
{
  ImgOper(IMG_SCALED_DIVIDE,pix,source,destination);
}
inline void ImgScaledDivide(EROIC24* source, EC24 pix, EROIC24* destination)
{
  ImgOper(IMG_SCALED_DIVIDE,source,pix,destination);
}
inline void ImgScaledDivide(EROIC24* source1, EROIC24* source2, EROIC24* destination)
{
  ImgOper(IMG_SCALED_DIVIDE,source1,source2,destination);
}
inline void ImgBitwiseAND(EBW8 pix, EROIBW8* source, EROIBW8* destination)
{
  ImgOper(IMG_BITWISE_AND,pix,source,destination);
}
inline void ImgBitwiseAND(EROIBW8* source, EBW8 pix, EROIBW8* destination)
{
  ImgOper(IMG_BITWISE_AND,source,pix,destination);
}
inline void ImgBitwiseAND(EROIBW8* source1, EROIBW8* source2, EROIBW8* destination)
{
  ImgOper(IMG_BITWISE_AND,source1,source2,destination);
}
inline void ImgBitwiseAND(EBW16 pix, EROIBW16* source, EROIBW16* destination)
{
  ImgOper(IMG_BITWISE_AND,pix,source,destination);
}
inline void ImgBitwiseAND(EROIBW16* source, EBW16 pix, EROIBW16* destination)
{
  ImgOper(IMG_BITWISE_AND,source,pix,destination);
}
inline void ImgBitwiseAND(EROIBW16* source1, EROIBW16* source2, EROIBW16* destination)
{
  ImgOper(IMG_BITWISE_AND,source1,source2,destination);
}
inline void ImgBitwiseAND(EC24 pix, EROIC24* source, EROIC24* destination)
{
  ImgOper(IMG_BITWISE_AND,pix,source,destination);
}
inline void ImgBitwiseAND(EROIC24* source, EC24 pix, EROIC24* destination)
{
  ImgOper(IMG_BITWISE_AND,source,pix,destination);
}
inline void ImgBitwiseAND(EROIC24* source1, EROIC24* source2, EROIC24* destination)
{
  ImgOper(IMG_BITWISE_AND,source1,source2,destination);
}
inline void ImgBitwiseOR(EBW8 pix, EROIBW8* source, EROIBW8* destination)
{
  ImgOper(IMG_BITWISE_OR,pix,source,destination);
}
inline void ImgBitwiseOR(EROIBW8* source, EBW8 pix, EROIBW8* destination)
{
  ImgOper(IMG_BITWISE_OR,source,pix,destination);
}
inline void ImgBitwiseOR(EROIBW8* source1, EROIBW8* source2, EROIBW8* destination)
{
  ImgOper(IMG_BITWISE_OR,source1,source2,destination);
}
inline void ImgBitwiseOR(EBW16 pix, EROIBW16* source, EROIBW16* destination)
{
  ImgOper(IMG_BITWISE_OR,pix,source,destination);
}
inline void ImgBitwiseOR(EROIBW16* source, EBW16 pix, EROIBW16* destination)
{
  ImgOper(IMG_BITWISE_OR,source,pix,destination);
}
inline void ImgBitwiseOR(EROIBW16* source1, EROIBW16* source2, EROIBW16* destination)
{
  ImgOper(IMG_BITWISE_OR,source1,source2,destination);
}
inline void ImgBitwiseOR(EC24 pix, EROIC24* source, EROIC24* destination)
{
  ImgOper(IMG_BITWISE_OR,pix,source,destination);
}
inline void ImgBitwiseOR(EROIC24* source, EC24 pix, EROIC24* destination)
{
  ImgOper(IMG_BITWISE_OR,source,pix,destination);
}
inline void ImgBitwiseOR(EROIC24* source1, EROIC24* source2, EROIC24* destination)
{
  ImgOper(IMG_BITWISE_OR,source1,source2,destination);
}
inline void ImgBitwiseXOR(EBW8 pix, EROIBW8* source, EROIBW8* destination)
{
  ImgOper(IMG_BITWISE_XOR,pix,source,destination);
}
inline void ImgBitwiseXOR(EROIBW8* source, EBW8 pix, EROIBW8* destination)
{
  ImgOper(IMG_BITWISE_XOR,source,pix,destination);
}
inline void ImgBitwiseXOR(EROIBW8* source1, EROIBW8* source2, EROIBW8* destination)
{
  ImgOper(IMG_BITWISE_XOR,source1,source2,destination);
}
inline void ImgBitwiseXOR(EBW16 pix, EROIBW16* source, EROIBW16* destination)
{
  ImgOper(IMG_BITWISE_XOR,pix,source,destination);
}
inline void ImgBitwiseXOR(EROIBW16* source, EBW16 pix, EROIBW16* destination)
{
  ImgOper(IMG_BITWISE_XOR,source,pix,destination);
}
inline void ImgBitwiseXOR(EROIBW16* source1, EROIBW16* source2, EROIBW16* destination)
{
  ImgOper(IMG_BITWISE_XOR,source1,source2,destination);
}
inline void ImgBitwiseXOR(EC24 pix, EROIC24* source, EROIC24* destination)
{
  ImgOper(IMG_BITWISE_XOR,pix,source,destination);
}
inline void ImgBitwiseXOR(EROIC24* source, EC24 pix, EROIC24* destination)
{
  ImgOper(IMG_BITWISE_XOR,source,pix,destination);
}
inline void ImgBitwiseXOR(EROIC24* source1, EROIC24* source2, EROIC24* destination)
{
  ImgOper(IMG_BITWISE_XOR,source1,source2,destination);
}
inline void ImgLogicalAND(EROIBW8* source1, EROIBW8* source2, EROIBW8* destination)
{
  ImgOper(IMG_LOGICAL_AND,source1,source2,destination);
}
inline void ImgLogicalAND(EROIBW16* source1, EROIBW16* source2, EROIBW16* destination)
{
  ImgOper(IMG_LOGICAL_AND,source1,source2,destination);
}
inline void ImgLogicalAND(EROIC24* source1, EROIC24* source2, EROIC24* destination)
{
  ImgOper(IMG_LOGICAL_AND,source1,source2,destination);
}
inline void ImgLogicalOR(EROIBW8* source1, EROIBW8* source2, EROIBW8* destination)
{
  ImgOper(IMG_LOGICAL_OR,source1,source2,destination);
}
inline void ImgLogicalOR(EROIBW16* source1, EROIBW16* source2, EROIBW16* destination)
{
  ImgOper(IMG_LOGICAL_OR,source1,source2,destination);
}
inline void ImgLogicalOR(EROIC24* source1, EROIC24* source2, EROIC24* destination)
{
  ImgOper(IMG_LOGICAL_OR,source1,source2,destination);
}
inline void ImgLogicalXOR(EROIBW8* source1, EROIBW8* source2, EROIBW8* destination)
{
  ImgOper(IMG_LOGICAL_XOR,source1,source2,destination);
}
inline void ImgLogicalXOR(EROIBW16* source1, EROIBW16* source2, EROIBW16* destination)
{
  ImgOper(IMG_LOGICAL_XOR,source1,source2,destination);
}
inline void ImgLogicalXOR(EROIC24* source1, EROIC24* source2, EROIC24* destination)
{
  ImgOper(IMG_LOGICAL_XOR,source1,source2,destination);
}
inline void ImgMin(EBW8 pix, EROIBW8* source, EROIBW8* destination)
{
  ImgOper(IMG_MIN,pix,source,destination);
}
inline void ImgMin(EROIBW8* source, EBW8 pix, EROIBW8* destination)
{
  ImgOper(IMG_MIN,source,pix,destination);
}
inline void ImgMin(EROIBW8* source1, EROIBW8* source2, EROIBW8* destination)
{
  ImgOper(IMG_MIN,source1,source2,destination);
}
inline void ImgMin(EBW16 pix, EROIBW16* source, EROIBW16* destination)
{
  ImgOper(IMG_MIN,pix,source,destination);
}
inline void ImgMin(EROIBW16* source, EBW16 pix, EROIBW16* destination)
{
  ImgOper(IMG_MIN,source,pix,destination);
}
inline void ImgMin(EROIBW16* source1, EROIBW16* source2, EROIBW16* destination)
{
  ImgOper(IMG_MIN,source1,source2,destination);
}
inline void ImgMin(EC24 pix, EROIC24* source, EROIC24* destination)
{
  ImgOper(IMG_MIN,pix,source,destination);
}
inline void ImgMin(EROIC24* source, EC24 pix, EROIC24* destination)
{
  ImgOper(IMG_MIN,source,pix,destination);
}
inline void ImgMin(EROIC24* source1, EROIC24* source2, EROIC24* destination)
{
  ImgOper(IMG_MIN,source1,source2,destination);
}
inline void ImgMax(EBW8 pix, EROIBW8* source, EROIBW8* destination)
{
  ImgOper(IMG_MAX,pix,source,destination);
}
inline void ImgMax(EROIBW8* source, EBW8 pix, EROIBW8* destination)
{
  ImgOper(IMG_MAX,source,pix,destination);
}
inline void ImgMax(EROIBW8* source1, EROIBW8* source2, EROIBW8* destination)
{
  ImgOper(IMG_MAX,source1,source2,destination);
}
inline void ImgMax(EBW16 pix, EROIBW16* source, EROIBW16* destination)
{
  ImgOper(IMG_MAX,pix,source,destination);
}
inline void ImgMax(EROIBW16* source, EBW16 pix, EROIBW16* destination)
{
  ImgOper(IMG_MAX,source,pix,destination);
}
inline void ImgMax(EROIBW16* source1, EROIBW16* source2, EROIBW16* destination)
{
  ImgOper(IMG_MAX,source1,source2,destination);
}
inline void ImgMax(EC24 pix, EROIC24* source, EROIC24* destination)
{
  ImgOper(IMG_MAX,pix,source,destination);
}
inline void ImgMax(EROIC24* source, EC24 pix, EROIC24* destination)
{
  ImgOper(IMG_MAX,source,pix,destination);
}
inline void ImgMax(EROIC24* source1, EROIC24* source2, EROIC24* destination)
{
  ImgOper(IMG_MAX,source1,source2,destination);
}
inline void ImgSetZero(EROIBW8* source, EBW8 pix, EROIBW8* destination)
{
  ImgOper(IMG_SET_ZERO,source,pix,destination);
}
inline void ImgSetZero(EROIBW8* source1, EROIBW8* source2, EROIBW8* destination)
{
  ImgOper(IMG_SET_ZERO,source1,source2,destination);
}
inline void ImgSetZero(EROIBW16* source, EBW16 pix, EROIBW16* destination)
{
  ImgOper(IMG_SET_ZERO,source,pix,destination);
}
inline void ImgSetZero(EROIBW16* source1, EROIBW16* source2, EROIBW16* destination)
{
  ImgOper(IMG_SET_ZERO,source1,source2,destination);
}
inline void ImgSetZero(EROIC24* source, EC24 pix, EROIC24* destination)
{
  ImgOper(IMG_SET_ZERO,source,pix,destination);
}
inline void ImgSetZero(EROIC24* source1, EROIC24* source2, EROIC24* destination)
{
  ImgOper(IMG_SET_ZERO,source1,source2,destination);
}
inline void ImgSetNonZero(EROIBW8* source, EBW8 pix, EROIBW8* destination)
{
  ImgOper(IMG_SET_NON_ZERO,source,pix,destination);
}
inline void ImgSetNonZero(EROIBW8* source1, EROIBW8* source2, EROIBW8* destination)
{
  ImgOper(IMG_SET_NON_ZERO,source1,source2,destination);
}
inline void ImgSetNonZero(EROIBW16* source, EBW16 pix, EROIBW16* destination)
{
  ImgOper(IMG_SET_NON_ZERO,source,pix,destination);
}
inline void ImgSetNonZero(EROIBW16* source1, EROIBW16* source2, EROIBW16* destination)
{
  ImgOper(IMG_SET_NON_ZERO,source1,source2,destination);
}
inline void ImgSetNonZero(EROIC24* source, EC24 pix, EROIC24* destination)
{
  ImgOper(IMG_SET_NON_ZERO,source,pix,destination);
}
inline void ImgSetNonZero(EROIC24* source1, EROIC24* source2, EROIC24* destination)
{
  ImgOper(IMG_SET_NON_ZERO,source1,source2,destination);
}
inline void ImgEqual(EBW8 pix, EROIBW8* source, EROIBW8* destination)
{
  ImgOper(IMG_EQUAL,pix,source,destination);
}
inline void ImgEqual(EROIBW8* source, EBW8 pix, EROIBW8* destination)
{
  ImgOper(IMG_EQUAL,source,pix,destination);
}
inline void ImgEqual(EROIBW8* source1, EROIBW8* source2, EROIBW8* destination)
{
  ImgOper(IMG_EQUAL,source1,source2,destination);
}
inline void ImgEqual(EBW16 pix, EROIBW16* source, EROIBW16* destination)
{
  ImgOper(IMG_EQUAL,pix,source,destination);
}
inline void ImgEqual(EROIBW16* source, EBW16 pix, EROIBW16* destination)
{
  ImgOper(IMG_EQUAL,source,pix,destination);
}
inline void ImgEqual(EROIBW16* source1, EROIBW16* source2, EROIBW16* destination)
{
  ImgOper(IMG_EQUAL,source1,source2,destination);
}
inline void ImgEqual(EC24 pix, EROIC24* source, EROIC24* destination)
{
  ImgOper(IMG_EQUAL,pix,source,destination);
}
inline void ImgEqual(EROIC24* source, EC24 pix, EROIC24* destination)
{
  ImgOper(IMG_EQUAL,source,pix,destination);
}
inline void ImgEqual(EROIC24* source1, EROIC24* source2, EROIC24* destination)
{
  ImgOper(IMG_EQUAL,source1,source2,destination);
}
inline void ImgNotEqual(EBW8 pix, EROIBW8* source, EROIBW8* destination)
{
  ImgOper(IMG_NOT_EQUAL,pix,source,destination);
}
inline void ImgNotEqual(EROIBW8* source, EBW8 pix, EROIBW8* destination)
{
  ImgOper(IMG_NOT_EQUAL,source,pix,destination);
}
inline void ImgNotEqual(EROIBW8* source1, EROIBW8* source2, EROIBW8* destination)
{
  ImgOper(IMG_NOT_EQUAL,source1,source2,destination);
}
inline void ImgNotEqual(EBW16 pix, EROIBW16* source, EROIBW16* destination)
{
  ImgOper(IMG_NOT_EQUAL,pix,source,destination);
}
inline void ImgNotEqual(EROIBW16* source, EBW16 pix, EROIBW16* destination)
{
  ImgOper(IMG_NOT_EQUAL,source,pix,destination);
}
inline void ImgNotEqual(EROIBW16* source1, EROIBW16* source2, EROIBW16* destination)
{
  ImgOper(IMG_NOT_EQUAL,source1,source2,destination);
}
inline void ImgNotEqual(EC24 pix, EROIC24* source, EROIC24* destination)
{
  ImgOper(IMG_NOT_EQUAL,pix,source,destination);
}
inline void ImgNotEqual(EROIC24* source, EC24 pix, EROIC24* destination)
{
  ImgOper(IMG_NOT_EQUAL,source,pix,destination);
}
inline void ImgNotEqual(EROIC24* source1, EROIC24* source2, EROIC24* destination)
{
  ImgOper(IMG_NOT_EQUAL,source1,source2,destination);
}
inline void ImgGreaterOrEqual(EBW8 pix, EROIBW8* source, EROIBW8* destination)
{
  ImgOper(IMG_GREATER_OR_EQUAL,pix,source,destination);
}
inline void ImgGreaterOrEqual(EROIBW8* source, EBW8 pix, EROIBW8* destination)
{
  ImgOper(IMG_GREATER_OR_EQUAL,source,pix,destination);
}
inline void ImgGreaterOrEqual(EROIBW8* source1, EROIBW8* source2, EROIBW8* destination)
{
  ImgOper(IMG_GREATER_OR_EQUAL,source1,source2,destination);
}
inline void ImgGreaterOrEqual(EBW16 pix, EROIBW16* source, EROIBW16* destination)
{
  ImgOper(IMG_GREATER_OR_EQUAL,pix,source,destination);
}
inline void ImgGreaterOrEqual(EROIBW16* source, EBW16 pix, EROIBW16* destination)
{
  ImgOper(IMG_GREATER_OR_EQUAL,source,pix,destination);
}
inline void ImgGreaterOrEqual(EROIBW16* source1, EROIBW16* source2, EROIBW16* destination)
{
  ImgOper(IMG_GREATER_OR_EQUAL,source1,source2,destination);
}
inline void ImgGreaterOrEqual(EC24 pix, EROIC24* source, EROIC24* destination)
{
  ImgOper(IMG_GREATER_OR_EQUAL,pix,source,destination);
}
inline void ImgGreaterOrEqual(EROIC24* source, EC24 pix, EROIC24* destination)
{
  ImgOper(IMG_GREATER_OR_EQUAL,source,pix,destination);
}
inline void ImgGreaterOrEqual(EROIC24* source1, EROIC24* source2, EROIC24* destination)
{
  ImgOper(IMG_GREATER_OR_EQUAL,source1,source2,destination);
}
inline void ImgLesserOrEqual(EBW8 pix, EROIBW8* source, EROIBW8* destination)
{
  ImgOper(IMG_LESSER_OR_EQUAL,pix,source,destination);
}
inline void ImgLesserOrEqual(EROIBW8* source, EBW8 pix, EROIBW8* destination)
{
  ImgOper(IMG_LESSER_OR_EQUAL,source,pix,destination);
}
inline void ImgLesserOrEqual(EROIBW8* source1, EROIBW8* source2, EROIBW8* destination)
{
  ImgOper(IMG_LESSER_OR_EQUAL,source1,source2,destination);
}
inline void ImgLesserOrEqual(EBW16 pix, EROIBW16* source, EROIBW16* destination)
{
  ImgOper(IMG_LESSER_OR_EQUAL,pix,source,destination);
}
inline void ImgLesserOrEqual(EROIBW16* source, EBW16 pix, EROIBW16* destination)
{
  ImgOper(IMG_LESSER_OR_EQUAL,source,pix,destination);
}
inline void ImgLesserOrEqual(EROIBW16* source1, EROIBW16* source2, EROIBW16* destination)
{
  ImgOper(IMG_LESSER_OR_EQUAL,source1,source2,destination);
}
inline void ImgLesserOrEqual(EC24 pix, EROIC24* source, EROIC24* destination)
{
  ImgOper(IMG_LESSER_OR_EQUAL,pix,source,destination);
}
inline void ImgLesserOrEqual(EROIC24* source, EC24 pix, EROIC24* destination)
{
  ImgOper(IMG_LESSER_OR_EQUAL,source,pix,destination);
}
inline void ImgLesserOrEqual(EROIC24* source1, EROIC24* source2, EROIC24* destination)
{
  ImgOper(IMG_LESSER_OR_EQUAL,source1,source2,destination);
}
inline void ImgGreater(EBW8 pix, EROIBW8* source, EROIBW8* destination)
{
  ImgOper(IMG_GREATER,pix,source,destination);
}
inline void ImgGreater(EROIBW8* source, EBW8 pix, EROIBW8* destination)
{
  ImgOper(IMG_GREATER,source,pix,destination);
}
inline void ImgGreater(EROIBW8* source1, EROIBW8* source2, EROIBW8* destination)
{
  ImgOper(IMG_GREATER,source1,source2,destination);
}
inline void ImgGreater(EBW16 pix, EROIBW16* source, EROIBW16* destination)
{
  ImgOper(IMG_GREATER,pix,source,destination);
}
inline void ImgGreater(EROIBW16* source, EBW16 pix, EROIBW16* destination)
{
  ImgOper(IMG_GREATER,source,pix,destination);
}
inline void ImgGreater(EROIBW16* source1, EROIBW16* source2, EROIBW16* destination)
{
  ImgOper(IMG_GREATER,source1,source2,destination);
}
inline void ImgGreater(EC24 pix, EROIC24* source, EROIC24* destination)
{
  ImgOper(IMG_GREATER,pix,source,destination);
}
inline void ImgGreater(EROIC24* source, EC24 pix, EROIC24* destination)
{
  ImgOper(IMG_GREATER,source,pix,destination);
}
inline void ImgGreater(EROIC24* source1, EROIC24* source2, EROIC24* destination)
{
  ImgOper(IMG_GREATER,source1,source2,destination);
}
inline void ImgLesser(EBW8 pix, EROIBW8* source, EROIBW8* destination)
{
  ImgOper(IMG_LESSER,pix,source,destination);
}
inline void ImgLesser(EROIBW8* source, EBW8 pix, EROIBW8* destination)
{
  ImgOper(IMG_LESSER,source,pix,destination);
}
inline void ImgLesser(EROIBW8* source1, EROIBW8* source2, EROIBW8* destination)
{
  ImgOper(IMG_LESSER,source1,source2,destination);
}
inline void ImgLesser(EBW16 pix, EROIBW16* source, EROIBW16* destination)
{
  ImgOper(IMG_LESSER,pix,source,destination);
}
inline void ImgLesser(EROIBW16* source, EBW16 pix, EROIBW16* destination)
{
  ImgOper(IMG_LESSER,source,pix,destination);
}
inline void ImgLesser(EROIBW16* source1, EROIBW16* source2, EROIBW16* destination)
{
  ImgOper(IMG_LESSER,source1,source2,destination);
}
inline void ImgLesser(EC24 pix, EROIC24* source, EROIC24* destination)
{
  ImgOper(IMG_LESSER,pix,source,destination);
}
inline void ImgLesser(EROIC24* source, EC24 pix, EROIC24* destination)
{
  ImgOper(IMG_LESSER,source,pix,destination);
}
inline void ImgLesser(EROIC24* source1, EROIC24* source2, EROIC24* destination)
{
  ImgOper(IMG_LESSER,source1,source2,destination);
}
inline void ImgCompare(EBW8 pix, EROIBW8* source, EROIBW8* destination)
{
  ImgOper(IMG_COMPARE,pix,source,destination);
}
inline void ImgCompare(EROIBW8* source, EBW8 pix, EROIBW8* destination)
{
  ImgOper(IMG_COMPARE,source,pix,destination);
}
inline void ImgCompare(EROIBW8* source1, EROIBW8* source2, EROIBW8* destination)
{
  ImgOper(IMG_COMPARE,source1,source2,destination);
}
inline void ImgCompare(EBW16 pix, EROIBW16* source, EROIBW16* destination)
{
  ImgOper(IMG_COMPARE,pix,source,destination);
}
inline void ImgCompare(EROIBW16* source, EBW16 pix, EROIBW16* destination)
{
  ImgOper(IMG_COMPARE,source,pix,destination);
}
inline void ImgCompare(EROIBW16* source1, EROIBW16* source2, EROIBW16* destination)
{
  ImgOper(IMG_COMPARE,source1,source2,destination);
}
inline void ImgCompare(EC24 pix, EROIC24* source, EROIC24* destination)
{
  ImgOper(IMG_COMPARE,pix,source,destination);
}
inline void ImgCompare(EROIC24* source, EC24 pix, EROIC24* destination)
{
  ImgOper(IMG_COMPARE,source,pix,destination);
}
inline void ImgCompare(EROIC24* source1, EROIC24* source2, EROIC24* destination)
{
  ImgOper(IMG_COMPARE,source1,source2,destination);
}
inline void ImgBitwiseNOT(EROIBW8* source, EROIBW8* destination)
{
  ImgOper(IMG_BITWISE_NOT,source,destination);
}
inline void ImgBitwiseNOT(EROIBW16* source, EROIBW16* destination)
{
  ImgOper(IMG_BITWISE_NOT,source,destination);
}
inline void ImgBitwiseNOT(EROIC24* source, EROIC24* destination)
{
  ImgOper(IMG_BITWISE_NOT,source,destination);
}
inline void ImgAverage(EBW8 pix, EROIBW8* source, EROIBW8* destination)
{
  ImgOper(IMG_AVERAGE,pix,source,destination);
}
inline void ImgAverage(EROIBW8* source, EBW8 pix, EROIBW8* destination)
{
  ImgOper(IMG_AVERAGE,source,pix,destination);
}
inline void ImgAverage(EROIBW8* source1, EROIBW8* source2, EROIBW8* destination)
{
  ImgOper(IMG_AVERAGE,source1,source2,destination);
}
inline void ImgAverage(EBW16 pix, EROIBW16* source, EROIBW16* destination)
{
  ImgOper(IMG_AVERAGE,pix,source,destination);
}
inline void ImgAverage(EROIBW16* source, EBW16 pix, EROIBW16* destination)
{
  ImgOper(IMG_AVERAGE,source,pix,destination);
}
inline void ImgAverage(EROIBW16* source1, EROIBW16* source2, EROIBW16* destination)
{
  ImgOper(IMG_AVERAGE,source1,source2,destination);
}
inline void ImgAverage(EC24 pix, EROIC24* source, EROIC24* destination)
{
  ImgOper(IMG_AVERAGE,pix,source,destination);
}
inline void ImgAverage(EROIC24* source, EC24 pix, EROIC24* destination)
{
  ImgOper(IMG_AVERAGE,source,pix,destination);
}
inline void ImgAverage(EROIC24* source1, EROIC24* source2, EROIC24* destination)
{
  ImgOper(IMG_AVERAGE,source1,source2,destination);
}


// For eVision Studio
inline INT16 ImgAbsoluteThreshold( EROIBW8* pSrcImage, EROIBW8* pDstImage, UINT32 threshold, EBW8 un8LowValue, EBW8 un8HighValue )
{
  return ImgThreshold( pSrcImage, pDstImage, threshold,un8LowValue.operator UINT8() , un8HighValue.operator UINT8());
}

inline INT16 ImgAbsoluteThreshold( EROIBW8* pSrcImage, EROIBW8* pDstImage, UINT32 threshold, EBW8 un8LowValue )
{
  return ImgThreshold( pSrcImage, pDstImage, threshold,un8LowValue, 255);
}

inline void ImgAbsoluteThreshold( EROIBW16* pSrcImage, EROIBW16* pDstImage, UINT32 threshold, EBW16 un8LowValue, EBW16 un8HighValue )
{
  ImgThreshold( pSrcImage, pDstImage, threshold,un8LowValue.operator UINT16(), un8HighValue.operator UINT16());
}

inline void ImgAbsoluteThreshold( EROIBW16* pSrcImage, EROIBW16* pDstImage, UINT32 threshold, EBW16 un8LowValue )
{
  ImgThreshold( pSrcImage, pDstImage, threshold,un8LowValue, 65535);
}

inline INT16 ImgRelativeThreshold( EROIBW8* pSrcImage, EROIBW8* pDstImage, EBW8 un8LowValue, EBW8 un8HighValue, FLOAT32 f32RelativeThreshold )
{
  return ImgThreshold( pSrcImage, pDstImage, static_cast<UINT32>(IMG_RELATIVE_THRESHOLD),un8LowValue.operator UINT8(), un8HighValue.operator UINT8(), f32RelativeThreshold);
}

inline INT16 ImgRelativeThreshold( EROIBW8* pSrcImage, EROIBW8* pDstImage, EBW8 un8LowValue, EBW8 un8HighValue )
{
  return ImgThreshold( pSrcImage, pDstImage, static_cast<UINT32>(IMG_RELATIVE_THRESHOLD),un8LowValue.operator UINT8(), un8HighValue.operator UINT8(), 0.5);
}

inline INT16 ImgRelativeThreshold( EROIBW8* pSrcImage, EROIBW8* pDstImage, EBW8 un8LowValue )
{
  return ImgThreshold( pSrcImage, pDstImage, static_cast<UINT32>(IMG_RELATIVE_THRESHOLD),un8LowValue.operator UINT8(), 255, 0.5);
}

inline void ImgRelativeThreshold( EROIBW16* pSrcImage, EROIBW16* pDstImage, EBW16 un8LowValue, EBW16 un8HighValue, FLOAT32 f32RelativeThreshold )
{
  ImgThreshold( pSrcImage, pDstImage, static_cast<UINT32>(IMG_RELATIVE_THRESHOLD),un8LowValue.operator UINT16(), un8HighValue.operator UINT16(), f32RelativeThreshold);
}

inline void ImgRelativeThreshold( EROIBW16* pSrcImage, EROIBW16* pDstImage, EBW16 un8LowValue, EBW16 un8HighValue )
{
  ImgThreshold( pSrcImage, pDstImage, static_cast<UINT32>(IMG_RELATIVE_THRESHOLD),un8LowValue.operator UINT16(), un8HighValue.operator UINT16(), 0.5);
}

inline void ImgRelativeThreshold( EROIBW16* pSrcImage, EROIBW16* pDstImage, EBW16 un8LowValue )
{
  ImgThreshold( pSrcImage, pDstImage, static_cast<UINT32>(IMG_RELATIVE_THRESHOLD),un8LowValue.operator UINT16(), 65535, 0.5);
}

inline INT16 ImgMinResidueThreshold( EROIBW8* pSrcImage, EROIBW8* pDstImage, EBW8 un8LowValue, EBW8 un8HighValue )
{
  return ImgThreshold( pSrcImage, pDstImage, static_cast<UINT32>(IMG_MIN_RESIDUE_THRESHOLD),un8LowValue.operator UINT8(), un8HighValue.operator UINT8());
}

inline INT16 ImgMinResidueThreshold( EROIBW8* pSrcImage, EROIBW8* pDstImage, EBW8 un8LowValue )
{
  return ImgThreshold( pSrcImage, pDstImage, static_cast<UINT32>(IMG_MIN_RESIDUE_THRESHOLD),un8LowValue.operator UINT8(), 255);
}

inline void ImgMinResidueThreshold( EROIBW16* pSrcImage, EROIBW16* pDstImage, EBW16 un8LowValue, EBW16 un8HighValue )
{
  ImgThreshold( pSrcImage, pDstImage, static_cast<UINT32>(IMG_MIN_RESIDUE_THRESHOLD),un8LowValue.operator UINT16(), un8HighValue.operator UINT16());
}

inline void ImgMinResidueThreshold( EROIBW16* pSrcImage, EROIBW16* pDstImage, EBW16 un8LowValue )
{
  ImgThreshold( pSrcImage, pDstImage, static_cast<UINT32>(IMG_MIN_RESIDUE_THRESHOLD),un8LowValue.operator UINT16(), 65535);
}

inline INT16 ImgMaxEntropyThreshold( EROIBW8* pSrcImage, EROIBW8* pDstImage, EBW8 un8LowValue, EBW8 un8HighValue )
{
  return ImgThreshold( pSrcImage, pDstImage, static_cast<UINT32>(IMG_MAX_ENTROPY_THRESHOLD),un8LowValue.operator UINT8(), un8HighValue.operator UINT8());
}

inline INT16 ImgMaxEntropyThreshold( EROIBW8* pSrcImage, EROIBW8* pDstImage, EBW8 un8LowValue )
{
  return ImgThreshold( pSrcImage, pDstImage, static_cast<UINT32>(IMG_MAX_ENTROPY_THRESHOLD),un8LowValue.operator UINT8(), 255);
}

inline void ImgMaxEntropyThreshold( EROIBW16* pSrcImage, EROIBW16* pDstImage, EBW16 un8LowValue, EBW16 un8HighValue )
{
  ImgThreshold( pSrcImage, pDstImage, static_cast<UINT32>(IMG_MAX_ENTROPY_THRESHOLD),un8LowValue.operator UINT16(), un8HighValue.operator UINT16());
}

inline void ImgMaxEntropyThreshold( EROIBW16* pSrcImage, EROIBW16* pDstImage, EBW16 un8LowValue )
{
  ImgThreshold( pSrcImage, pDstImage, static_cast<UINT32>(IMG_MAX_ENTROPY_THRESHOLD),un8LowValue.operator UINT16(), 65535);
}

inline INT16 ImgIsodataThreshold( EROIBW8* pSrcImage, EROIBW8* pDstImage, EBW8 un8LowValue, EBW8 un8HighValue )
{
  return ImgThreshold( pSrcImage, pDstImage, static_cast<UINT32>(IMG_ISODATA_THRESHOLD),un8LowValue.operator UINT8(), un8HighValue.operator UINT8());
}

inline INT16 ImgIsodataThreshold( EROIBW8* pSrcImage, EROIBW8* pDstImage, EBW8 un8LowValue  )
{
  return ImgThreshold( pSrcImage, pDstImage, static_cast<UINT32>(IMG_ISODATA_THRESHOLD),un8LowValue.operator UINT8(), 255);
}

inline void ImgIsodataThreshold( EROIBW16* pSrcImage, EROIBW16* pDstImage, EBW16 un8LowValue, EBW16 un8HighValue )
{
  ImgThreshold( pSrcImage, pDstImage, static_cast<UINT32>(IMG_ISODATA_THRESHOLD),un8LowValue.operator UINT16(), un8HighValue.operator UINT16());
}

inline void ImgIsodataThreshold( EROIBW16* pSrcImage, EROIBW16* pDstImage, EBW16 un8LowValue )
{
  ImgThreshold( pSrcImage, pDstImage, static_cast<UINT32>(IMG_ISODATA_THRESHOLD),un8LowValue.operator UINT16(), 65535);
}

inline INT16 ImgDoubleThreshold( EROIBW8* pSrcImage, EROIBW8* pDstImage, UINT32 un32LowThreshold, UINT32 un32HighThreshold, EBW8 un8LowValue, EBW8 un8MidValue, EBW8 un8HighValue)
{
  return ImgDoubleThreshold(pSrcImage, pDstImage, un32LowThreshold, un32HighThreshold, un8LowValue.operator UINT8(), un8MidValue.operator UINT8(), un8HighValue.operator UINT8());
}

inline INT16 ImgDoubleThreshold( EROIBW8* pSrcImage, EROIBW8* pDstImage, UINT32 un32LowThreshold, UINT32 un32HighThreshold, EBW8 un8LowValue, EBW8 un8MidValue)
{
  return ImgDoubleThreshold(pSrcImage, pDstImage, un32LowThreshold, un32HighThreshold, un8LowValue.operator UINT8(), un8MidValue.operator UINT8(), 255);
}

inline INT16 ImgDoubleThreshold( EROIBW8* pSrcImage, EROIBW8* pDstImage, UINT32 un32LowThreshold, UINT32 un32HighThreshold, EBW8 un8LowValue)
{
  return ImgDoubleThreshold(pSrcImage, pDstImage, un32LowThreshold, un32HighThreshold, un8LowValue.operator UINT8(), 127, 255);
}

inline INT16 ImgArea( EROIBW8* pSrcImage, EBW8 un8Thr, INT32& n32PixelsAbove)
{
  return ImgArea( pSrcImage, un8Thr.operator UINT8(), n32PixelsAbove);
}

inline INT16 ImgAreaDoubleThreshold( EROIBW8* pSrcImage, EBW8 un8LowThr, EBW8 un8HighThr, INT32 &n32PixelsBetween)
{
  return ImgAreaDoubleThreshold( pSrcImage, un8LowThr.operator UINT8(), un8HighThr.operator UINT8(), n32PixelsBetween);
}

inline INT16 ImgPixelCount( EROIBW8* pSrcImage, EBW8 un8LowThr, EBW8 un8HighThr, INT32& n32PixelsBelow, INT32& n32PixelsBetween, INT32& n32PixelsAbove)
{
  return ImgPixelCount( pSrcImage, un8LowThr.operator UINT8(), un8HighThr.operator UINT8(), n32PixelsBelow, n32PixelsBetween, n32PixelsAbove);
}

inline INT16 ImgPixelMax( EROIBW8* pSrcImage, EBW8& un8MaxPixVal)
{
  UINT8 pix = un8MaxPixVal.operator UINT8();
  return ImgPixelMax( pSrcImage, pix);
}

inline INT16 ImgPixelMin( EROIBW8* pSrcImage, EBW8& un8MinPixVal)
{
  UINT8 pix = un8MinPixVal.operator UINT8();
  return ImgPixelMin( pSrcImage, pix);
}

inline INT16 ImgPixelStat( EROIBW8* pSrcImage, EBW8& un8MinPixVal, EBW8& un8MaxPixVal, FLOAT32& f32AveragePixVal)
{
  UINT8 pix1 = un8MinPixVal.operator UINT8();
  UINT8 pix2 = un8MaxPixVal.operator UINT8();
  return ImgPixelStat( pSrcImage, pix1, pix2, f32AveragePixVal);
}

inline INT16 ImgThreshold( EROIBW8* pSrcImage, EROIBW8* pDstImage, UINT32 un32Threshold, EBW8 un8LowValue, EBW8 un8HighValue, FLOAT32 f32RelativeThreshold)
{
  return ImgThreshold( pSrcImage, pDstImage, un32Threshold, un8LowValue.operator UINT8(), un8HighValue.operator UINT8(), f32RelativeThreshold);
}

inline INT16 ImgThreshold( EROIBW8* pSrcImage, EROIBW8* pDstImage, UINT32 un32Threshold, EBW8 un8LowValue, EBW8 un8HighValue)
{
  return ImgThreshold( pSrcImage, pDstImage, un32Threshold, un8LowValue.operator UINT8(), un8HighValue.operator UINT8(), 0.5);
}

inline INT16 ImgThreshold( EROIBW8* pSrcImage, EROIBW8* pDstImage, UINT32 un32Threshold, EBW8 un8LowValue)
{
  return ImgThreshold( pSrcImage, pDstImage, un32Threshold, un8LowValue.operator UINT8(), 255, 0.5);
}

#endif //__EIMAGE_H__
