////////////////////////////////////////////////////////////////////////////////////////////////////
// EColor.h: EasyColor library header file for eVision 6.7.1.0
//
// EasyColor provides color conversion functions between many colorimetric systems
//
// Copyright ( c) 1997-2006, Euresys. All rights reserved.
//

#ifndef __ECOLOR_H__
#define __ECOLOR_H__

// eVision header files
#include "Easy.h"

// Gamma exponents
#define CLR_NTSC_GAMMA 2.2f
#define CLR_PAL_GAMMA 2.8f
#define CLR_SMPTE_GAMMA ( 1 / 0.45f)

// Inverse gamma exponents
#define CLR_COMPENSATE_NTSC_GAMMA ( 1 / 2.2f)
#define CLR_COMPENSATE_PAL_GAMMA ( 1 / 2.8f)
#define CLR_COMPENSATE_SMPTE_GAMMA 0.45f

// White illuminants
#define CLR_CIE_A_R 146.130f
#define CLR_CIE_A_G 90.747f
#define CLR_CIE_A_B 26.491f

#define CLR_CIE_D50_R 106.938f
#define CLR_CIE_D50_G 102.691f
#define CLR_CIE_D50_B 67.766f

#define CLR_CIE_D55_R 102.742f
#define CLR_CIE_D55_G 103.161f
#define CLR_CIE_D55_B 76.352f

#define CLR_CIE_D65_R 96.673f
#define CLR_CIE_D65_G 103.334f
#define CLR_CIE_D65_B 91.381f

#define CLR_CIE_F_R 105.405f
#define CLR_CIE_F_G 104.676f
#define CLR_CIE_F_B 61.568f

class EColorVector : public EVectorTemplate<EColor>
{
  // Wrapping members
public:
  int handle_;
  FinalizeCallback callback_;

public:
  // Mandated to avoid confusion with the copy constructor
  explicit E_DLL0 CONSTRUCTOR E_DLL1  EColorVector( UINT32 un32MaxElements = 0);
};

////////////////////////////////////////////////////////////////////////////////////////////////////
// Class EColorLookup

enum CLR_LOOKUP_MODES
{
  CLR_SEPARABLE,
    CLR_LINEAR,
    CLR_GENERAL,
    CLR_LOOKUP_UNKNOWN  = 0xFFFFFFFF
};


class EColorLookup
// ( 8, 8, 8) bits in, ( 8, 8, 8) bits out color lookup table
{
  // Wrapping members
public:
  int handle_;
  FinalizeCallback callback_;
  
private:
  // LUT mode
  enum CLR_LOOKUP_MODES m_eMode;
  enum E_COLOR_SYSTEM m_eColorSystemIn, m_eColorSystemOut;
  
  // Separable mode
  EBW8Vector m_RLut, m_GLut, m_BLut;
  
  // Non separable mode
  EC24* m_pEntry;
  UINT32 m_un32IndexBits;
  BOOL m_bInterpolation;
  
public:
  // Constructors
  E_DLL0 CONSTRUCTOR E_DLL1  EColorLookup( UINT32 un32IndexBits = 5, BOOL bInterpolation = FALSE);
  
  // Destructor
  virtual E_DLL0 DESTRUCTOR E_DLL1  ~EColorLookup( );
  
  // Data member access
  E_DLL0 void E_DLL1  SetInterpolation( BOOL bInterpolation);
  E_DLL0 BOOL E_DLL1  GetInterpolation( );
  E_DLL0 void E_DLL1  SetIndexBits( UINT32 un32IndexBits);
  E_DLL0 UINT32 E_DLL1  GetIndexBits( );
  E_DLL0 enum E_COLOR_SYSTEM E_DLL1  GetColorSystemIn( );
  E_DLL0 enum E_COLOR_SYSTEM E_DLL1  GetColorSystemOut( );
  
  // Initialization
  E_DLL0 void E_DLL1  WhiteBalance( 
    FLOAT32 f32Gain = 1, FLOAT32 f32Gamma = 1,
    FLOAT32 f32BalanceR = 255, FLOAT32 f32BalanceG = 255, FLOAT32 f32BalanceB = 255);
  
  E_DLL0 void E_DLL1  AdjustGainOffset( enum E_COLOR_SYSTEM eColorSystem,
    FLOAT32 f32Gain0 = 1.f, FLOAT32 f32Offset0 = 0.f,
    FLOAT32 f32Gain1 = 1.f, FLOAT32 f32Offset1 = 0.f,
    FLOAT32 f32Gain2 = 1.f, FLOAT32 f32Offset2 = 0.f);
  
  E_DLL0 void E_DLL1  ConvertToRGB( enum E_COLOR_SYSTEM eColorSystem);
  E_DLL0 void E_DLL1  ConvertFromRGB( enum E_COLOR_SYSTEM eColorSystem);
  
  E_DLL0 void E_DLL1  Calibrate( 
    EC24 Color, FLOAT32 f32X, FLOAT32 f32Y, FLOAT32 f32Z);
  E_DLL0 void E_DLL1  Calibrate( 
    EC24 Color0, FLOAT32 f32X0, FLOAT32 f32Y0, FLOAT32 f32Z0,
    EC24 Color1, FLOAT32 f32X1, FLOAT32 f32Y1, FLOAT32 f32Z1,
    EC24 Color2, FLOAT32 f32X2, FLOAT32 f32Y2, FLOAT32 f32Z2);
  E_DLL0 void E_DLL1  Calibrate( 
    EC24 Color0, FLOAT32 f32X0, FLOAT32 f32Y0, FLOAT32 f32Z0,
    EC24 Color1, FLOAT32 f32X1, FLOAT32 f32Y1, FLOAT32 f32Z1,
    EC24 Color2, FLOAT32 f32X2, FLOAT32 f32Y2, FLOAT32 f32Z2,
    EC24 Color3, FLOAT32 f32X3, FLOAT32 f32Y3, FLOAT32 f32Z3);
  
  E_DLL0 void E_DLL1  SetTransform( void ( *Transform)( EColor SrcColor, EColor& DstColor),
    enum E_COLOR_SYSTEM eSystemIn = E_COLOR_SYSTEM_RGB, enum E_COLOR_SYSTEM eSystemOut = E_COLOR_SYSTEM_RGB);
  
  // Use
  E_DLL0 void E_DLL1  Transform( EC24 SrcColor, EC24& DstColor);
  E_DLL0 void E_DLL1  Transform( EROIC24* pSrcImage, EROIC24* pDstImage);
  
  friend E_DLL0 void E_DLL1  ClrTransformBayer( EROIBW8 *pSrcImage, EROIBW8 *pDstImage, EColorLookup* pLookup, BOOL bEvenCol, BOOL bEvenRow);
};

////////////////////////////////////////////////////////////////////////////////////////////////////
// Class EPseudoColorLookup

class EPseudoColorLookup
{ 
  // Wrapping members
public:
  int handle_;
  FinalizeCallback callback_;

  EPseudoColorLookup() 
  {
    handle_ = 0;
    callback_ = 0;
  }

private:
  EC24 m_Array[256];
  
public:
  E_DLL0 void E_DLL1  SetShading( EC24 c24Black, EC24 c24White, enum E_COLOR_SYSTEM eColorSystem, BOOL bWrap = TRUE);
  
  friend E_DLL0 void E_DLL1  ClrPseudoColor( EROIBW8* pSrc, EROIC24* pDst, EPseudoColorLookup* pLookup);
};

////////////////////////////////////////////////////////////////////////////////////////////////////
// Pseudo-colors

E_DLL0 void E_DLL1  ClrPseudoColor( EROIBW8* pSrc, EROIC24* pDst, EPseudoColorLookup* pLookup);

////////////////////////////////////////////////////////////////////////////////////////////////////
// Color Systems Variants

E_DLL0 void E_DLL1  ClrSetRGBStandard( enum E_RGB_STANDARD eStandard);
E_DLL0 enum E_RGB_STANDARD E_DLL1  ClrGetRGBStandard( );

E_DLL0 void E_DLL1  ClrSetSrcQuantization( enum E_COLOR_QUANTIZATION eQuantization);
E_DLL0 void E_DLL1  ClrSetDstQuantization( enum E_COLOR_QUANTIZATION eQuantization);
E_DLL0 enum E_COLOR_QUANTIZATION E_DLL1  ClrGetSrcQuantization( );
E_DLL0 enum E_COLOR_QUANTIZATION E_DLL1  ClrGetDstQuantization( );

////////////////////////////////////////////////////////////////////////////////////////////////////
// Unquantized color conversions

////////////////////////////////////////////////////////////////////////////////////////////////////
// RGB

E_DLL0 void E_DLL1  ClrDequantize( EC24 Src, ERGB& Dst);
E_DLL0 void E_DLL1  ClrQuantize( ERGB Src, EC24& Dst);

////////////////////////////////////////////////////////////////////////////////////////////////////
// XYZ

E_DLL0 void E_DLL1  ClrDequantize( EC24 Src, EXYZ& Dst);
E_DLL0 void E_DLL1  ClrQuantize( EXYZ Src, EC24& Dst);

E_DLL0 void E_DLL1  ClrRGBToXYZ( ERGB In, EXYZ& Out);
E_DLL0 void E_DLL1  ClrXYZToRGB( EXYZ In, ERGB& Out);

E_DLL0 void E_DLL1  ClrRGBToReducedXYZ( ERGB In, EXYZ& Out);

////////////////////////////////////////////////////////////////////////////////////////////////////
// Normalized Digital YUV

E_DLL0 void E_DLL1  ClrDequantize( EC24 Src, EYUV& Dst);
E_DLL0 void E_DLL1  ClrQuantize( EYUV Src, EC24& Dst);

E_DLL0 void E_DLL1  ClrRGBToYUV( ERGB In, EYUV& Out);
E_DLL0 void E_DLL1  ClrYUVToRGB( EYUV In, ERGB& Out);

////////////////////////////////////////////////////////////////////////////////////////////////////
// Normalized Digital YIQ

E_DLL0 void E_DLL1  ClrDequantize( EC24 Src, EYIQ& Dst);
E_DLL0 void E_DLL1  ClrQuantize( EYIQ Src, EC24& Dst);

E_DLL0 void E_DLL1  ClrRGBToYIQ( ERGB In, EYIQ& Out);
E_DLL0 void E_DLL1  ClrYIQToRGB( EYIQ In, ERGB& Out);

////////////////////////////////////////////////////////////////////////////////////////////////////
// Hue, Saturation, Lightness

E_DLL0 void E_DLL1  ClrDequantize( EC24 Src, ELSH& Dst);
E_DLL0 void E_DLL1  ClrQuantize( ELSH Src, EC24& Dst);

E_DLL0 void E_DLL1  ClrRGBToLSH( ERGB In, ELSH& Out);
E_DLL0 void E_DLL1  ClrLSHToRGB( ELSH In, ERGB& Out);

////////////////////////////////////////////////////////////////////////////////////////////////////
// Hue, Saturation, Value

E_DLL0 void E_DLL1  ClrDequantize( EC24 Src, EVSH& Dst);
E_DLL0 void E_DLL1  ClrQuantize( EVSH Src, EC24& Dst);

E_DLL0 void E_DLL1  ClrRGBToVSH( ERGB In, EVSH& Out);
E_DLL0 void E_DLL1  ClrVSHToRGB( EVSH In, ERGB& Out);

////////////////////////////////////////////////////////////////////////////////////////////////////
// Hue, Saturation, Intensity

E_DLL0 void E_DLL1  ClrDequantize( EC24 Src, EISH& Dst);
E_DLL0 void E_DLL1  ClrQuantize( EISH Src, EC24& Dst);

E_DLL0 void E_DLL1  ClrRGBToISH( ERGB In, EISH& Out);
E_DLL0 void E_DLL1  ClrISHToRGB( EISH In, ERGB& Out);

////////////////////////////////////////////////////////////////////////////////////////////////////
// Hue, Saturation, Brightness

E_DLL0 void E_DLL1  ClrDequantize( EC24 Src, EYSH& Dst);
E_DLL0 void E_DLL1  ClrQuantize( EYSH Src, EC24& Dst);

E_DLL0 void E_DLL1  ClrRGBToYSH( ERGB In, EYSH& Out);
E_DLL0 void E_DLL1  ClrYSHToRGB( EYSH In, ERGB& Out);

////////////////////////////////////////////////////////////////////////////////////////////////////
// L*a*b*

E_DLL0 void E_DLL1  ClrDequantize( EC24 Src, ELAB& Dst);
E_DLL0 void E_DLL1  ClrQuantize( ELAB Src, EC24& Dst);

E_DLL0 void E_DLL1  ClrRGBToLAB( ERGB In, ELAB& Out);
E_DLL0 void E_DLL1  ClrLABToRGB( ELAB In, ERGB& Out);

E_DLL0 void E_DLL1  ClrXYZToLAB( EXYZ In, ELAB& Out);
E_DLL0 void E_DLL1  ClrLABToXYZ( ELAB In, EXYZ& Out);

////////////////////////////////////////////////////////////////////////////////////////////////////
// Lightness, Chroma, Hue

E_DLL0 void E_DLL1  ClrDequantize( EC24 Src, ELCH& Dst);
E_DLL0 void E_DLL1  ClrQuantize( ELCH Src, EC24& Dst);

E_DLL0 void E_DLL1  ClrRGBToLCH( ERGB In, ELCH& Out);
E_DLL0 void E_DLL1  ClrLCHToRGB( ELCH In, ERGB& Out);

////////////////////////////////////////////////////////////////////////////////////////////////////
// L*u*v*

E_DLL0 void E_DLL1  ClrDequantize( EC24 Src, ELUV& Dst);
E_DLL0 void E_DLL1  ClrQuantize( ELUV Src, EC24& Dst);

E_DLL0 void E_DLL1  ClrRGBToLUV( ERGB In, ELUV& Out);
E_DLL0 void E_DLL1  ClrLUVToRGB( ELUV In, ERGB& Out);

E_DLL0 void E_DLL1  ClrXYZToLUV( EXYZ In, ELUV& Out);
E_DLL0 void E_DLL1  ClrLUVToXYZ( ELUV In, EXYZ& Out);

////////////////////////////////////////////////////////////////////////////////////////////////////
// Quantized color conversions

E_DLL0 void E_DLL1  ClrRGBToXYZ( EC24 In, EC24& Out);
E_DLL0 void E_DLL1  ClrRGBToYUV( EC24 In, EC24& Out);
E_DLL0 void E_DLL1  ClrRGBToYIQ( EC24 In, EC24& Out);
E_DLL0 void E_DLL1  ClrRGBToLSH( EC24 In, EC24& Out);
E_DLL0 void E_DLL1  ClrRGBToVSH( EC24 In, EC24& Out);
E_DLL0 void E_DLL1  ClrRGBToISH( EC24 In, EC24& Out);
E_DLL0 void E_DLL1  ClrRGBToYSH( EC24 In, EC24& Out);
E_DLL0 void E_DLL1  ClrRGBToLAB( EC24 In, EC24& Out);
E_DLL0 void E_DLL1  ClrRGBToLCH( EC24 In, EC24& Out);
E_DLL0 void E_DLL1  ClrRGBToLUV( EC24 In, EC24& Out);

E_DLL0 void E_DLL1  ClrXYZToRGB( EC24 In, EC24& Out);
E_DLL0 void E_DLL1  ClrYUVToRGB( EC24 In, EC24& Out);
E_DLL0 void E_DLL1  ClrYIQToRGB( EC24 In, EC24& Out);
E_DLL0 void E_DLL1  ClrLSHToRGB( EC24 In, EC24& Out);
E_DLL0 void E_DLL1  ClrVSHToRGB( EC24 In, EC24& Out);
E_DLL0 void E_DLL1  ClrISHToRGB( EC24 In, EC24& Out);
E_DLL0 void E_DLL1  ClrYSHToRGB( EC24 In, EC24& Out);
E_DLL0 void E_DLL1  ClrLABToRGB( EC24 In, EC24& Out);
E_DLL0 void E_DLL1  ClrLCHToRGB( EC24 In, EC24& Out);
E_DLL0 void E_DLL1  ClrLUVToRGB( EC24 In, EC24& Out);

E_DLL0 void E_DLL1  ClrXYZToLAB( EC24 In, EC24& Out);
E_DLL0 void E_DLL1  ClrLABToXYZ( EC24 In, EC24& Out);
E_DLL0 void E_DLL1  ClrXYZToLUV( EC24 In, EC24& Out);
E_DLL0 void E_DLL1  ClrLUVToXYZ( EC24 In, EC24& Out);
E_DLL0 void E_DLL1  ClrRGBToReducedXYZ( EC24 In, EC24& Out);

////////////////////////////////////////////////////////////////////////////////////////////////////
// Color space transformations

E_DLL0 void E_DLL1  ClrCompose
( EROIBW8* pC0Src, EROIBW8* pC1Src, EROIBW8* pC2Src,
 EROIC24* pColorDst, EColorLookup* pLookup = NULL);

E_DLL0 void E_DLL1  ClrDecompose
( EROIC24* pColorSrc,
 EROIBW8* pC0Dst, EROIBW8* pC1Dst, EROIBW8* pC2Dst, EColorLookup* pLookup = NULL);

E_DLL0 void E_DLL1  ClrGetComponent
( EROIC24* pColorSrc, EROIBW8* pBWDst,
 UINT32 un32Component, EColorLookup* pLookup = NULL);

E_DLL0 void E_DLL1  ClrSetComponent
( EROIBW8* pBWSrc, EROIC24* pColorDst,
 UINT32 un32Component);

E_DLL0 void E_DLL1  ClrTransform( EROIC24* pSrcImage, EROIC24* pDstImage, EColorLookup* pLookup);
E_DLL0 void E_DLL1  ClrTransform
( EROIC24* pSrcImage, EROIC24* pDstImage, void ( *Transform)( EC24 SrcColor, EC24& DstColor),
 enum E_COLOR_SYSTEM eSystemIn = E_COLOR_SYSTEM_RGB, enum E_COLOR_SYSTEM eSystemOut = E_COLOR_SYSTEM_RGB);
E_DLL0 void E_DLL1  ClrTransform
( EROIC24* pSrcImage, EROIC24* pDstImage, void ( *Transform)( EColor SrcColor, EColor& DstColor),
 enum E_COLOR_SYSTEM eSystemIn = E_COLOR_SYSTEM_RGB, enum E_COLOR_SYSTEM eSystemOut = E_COLOR_SYSTEM_RGB);


////////////////////////////////////////////////////////////////////////////////////////////////////
// Color segmentation

// NOT DOCUMENTED YET
E_DLL0 void E_DLL1  ClrAssignNearestClassCenter( EROIC24* pSrcImage, EROIC24* pDstImage, EC24Vector* pClassCenters);
E_DLL0 void E_DLL1  ClrAssignNearestClass( EROIC24* pSrcImage, EROIBW8* pDstImage, EC24Vector* pClassCenters);
E_DLL0 void E_DLL1  ClrImproveClassCenters( EROIC24* pSrcImage, EC24Vector* pClassCenters);
E_DLL0 void E_DLL1  ClrClassAverages( EROIC24* pSrcImage, EC24Vector* pClassCenters, EColorVector* pAverages);
E_DLL0 void E_DLL1  ClrClassVariances( EROIC24* pSrcImage, EC24Vector* pClassCenters, EColorVector* pAverages, EColorVector* pVariances);

////////////////////////////////////////////////////////////////////////////////////////////////////
// Miscellaneous transformations

// 4:2:2 color encoding
E_DLL0 void E_DLL1  ClrFormat422To444( EROIBW16* pSrcImage, EROIC24* pDstImage, BOOL bYFirst);
E_DLL0 void E_DLL1  ClrFormat444To422( EROIC24* pSrcImage, EROIBW16* pDstImage, BOOL bYFirst);

E_DLL0 void E_DLL1  ClrRGBToYUV
( EROIC24* pSrc, EROIC24* pDst,
 enum E_COLOR_QUANTIZATION eQuantizationMode = E_COLOR_QUANTIZATION_FULL_RANGE);
E_DLL0 void E_DLL1  ClrYUVToRGB
( EROIC24* pSrc, EROIC24* pDst,
 enum E_COLOR_QUANTIZATION eQuantizationMode = E_COLOR_QUANTIZATION_FULL_RANGE);

// Bayer pattern color encoding
E_DLL0 void E_DLL1  ClrBayerToC24
( EROIBW8* pSrcBayerImage, EROIC24* pDstImage,
 BOOL bEvenCol = TRUE, BOOL bEvenRow = TRUE, BOOL bInterpolate = TRUE, BOOL bImproved = FALSE);

E_DLL0 void E_DLL1  ClrC24ToBayer
( EROIC24* pSrcImage, EROIBW8* pDstBayerImage,
 BOOL bEvenCol = TRUE, BOOL bEvenRow = TRUE);

E_DLL0 void E_DLL1  ClrTransformBayer
( EROIBW8* pSrcBayerImage, EROIBW8* pDstBayerImage, EColorLookup* pLookup,
 BOOL bEvenCol = TRUE, BOOL bEvenRow = TRUE);

// Color plane aligment
E_DLL0 void E_DLL1  ClrRegisterPlanes
( EROIC24* pSrc, EROIC24* pDst,
 INT32 n32RShiftX = 0, INT32 n32GShiftX = 0, INT32 n32BShiftX = 0,
 INT32 n32RShiftY = 0, INT32 n32GShiftY = 0, INT32 n32BShiftY = 0);

#endif // __ECOLOR_H__
