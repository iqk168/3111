////////////////////////////////////////////////////////////////////////////////////////////////////
// EMatrixCode.h: EasyMatrixCode library header file for eVision 6.7.1.0
//
// EasyMatrixCode implements a reader for Data Matrix symbols
//
// Copyright ( c) 1997-2006, Euresys. All rights reserved.
//

#ifndef __EMATRIXCODE_H__
#define __EMATRIXCODE_H__

#if (_MSC_VER >= 1300)
#pragma warning( push )
#pragma warning( disable : 4702 ) 
#endif // (_MSC_VER >= 1300)

#include <vector>
#include <cassert>

#if (_MSC_VER >= 1300)
#pragma warning( pop )
#endif // (_MSC_VER >= 1300)


#include "Easy.h"
#include "EObject.h"
#include "EInspect.h"
#include "EMatrixCode_Enum.h"

enum MXC_SYMBOL_SIZE
{
  // ECC 000-140 squares
  MXC_SIZE_9,
  MXC_SIZE_11,
  MXC_SIZE_13,
  MXC_SIZE_15,
  MXC_SIZE_17,
  MXC_SIZE_19,
  MXC_SIZE_21,
  MXC_SIZE_23,
  MXC_SIZE_25,
  MXC_SIZE_27,
  MXC_SIZE_29,
  MXC_SIZE_31,
  MXC_SIZE_33,
  MXC_SIZE_35,
  MXC_SIZE_37,
  MXC_SIZE_39,
  MXC_SIZE_41,
  MXC_SIZE_43,
  MXC_SIZE_45,
  MXC_SIZE_47,
  MXC_SIZE_49,
  
  // ECC 200 squares
  MXC_SIZE_10,
  MXC_SIZE_12,
  MXC_SIZE_14,
  MXC_SIZE_16,
  MXC_SIZE_18,
  MXC_SIZE_20,
  MXC_SIZE_22,
  MXC_SIZE_24,
  MXC_SIZE_26,
  MXC_SIZE_32,
  MXC_SIZE_36,
  MXC_SIZE_40,
  MXC_SIZE_44,
  MXC_SIZE_48,
  MXC_SIZE_52,
  MXC_SIZE_64,
  MXC_SIZE_72,
  MXC_SIZE_80,
  MXC_SIZE_88,
  MXC_SIZE_96,
  MXC_SIZE_104,
  MXC_SIZE_120,
  MXC_SIZE_132,
  MXC_SIZE_144,
  
  // ECC 200 rectangles
  MXC_SIZE_8_18,
  MXC_SIZE_8_32,
  MXC_SIZE_12_26,
  MXC_SIZE_12_36,
  MXC_SIZE_16_36,
  MXC_SIZE_16_48,
  
  // Unknown size and symbology
  MXC_SIZE_UNKNOWN = 0xFFFFFFFE,
  
  // Unknown size
  MXC_SIZE_ECC000_UNKNOWN = 0xFFFFFFFD,
  MXC_SIZE_ECC050_UNKNOWN = 0xFFFFFFFC,
  MXC_SIZE_ECC080_UNKNOWN = 0xFFFFFFFB,
  MXC_SIZE_ECC100_UNKNOWN = 0xFFFFFFFA,
  MXC_SIZE_ECC140_UNKNOWN = 0xFFFFFFF9,
  MXC_SIZE_ECC200_UNKNOWN = 0xFFFFFFF8,
  
  MXC_SYMBOL_SIZE_UNKNOWN = 0xFFFFFFFF
};

enum MXC_SYMBOL_CONTRAST
{
  // Positive or negative
  MXC_BLACK_ON_WHITE,
  MXC_WHITE_ON_BLACK,
  
  // Unknown contrast
  MXC_CONTRAST_UNKNOWN = 0xFFFFFFFE,
  MXC_SYMBOL_CONTRAST_UNKNOWN  = 0xFFFFFFFF
};


enum MXC_SYMBOL_ORIENTATION
{
  // Orientation
  MXC_ORIENTATION_NORTH,
  MXC_ORIENTATION_EAST,
  MXC_ORIENTATION_SOUTH,
  MXC_ORIENTATION_WEST,
  
  // Unknown orientation
  MXC_ORIENTATION_UNKNOWN = 0xFFFFFFFE,
  
  MXC_SYMBOL_ORIENTATION_UNKNOWN  = 0xFFFFFFFF
};


enum MXC_MIN_SYMBOL_SIZE
{
  MXC_ECC000_MIN_SIZE = MXC_SIZE_9,
  MXC_ECC050_MIN_SIZE = MXC_SIZE_11,
  MXC_ECC080_MIN_SIZE = MXC_SIZE_13,
  MXC_ECC100_MIN_SIZE = MXC_SIZE_13,
  MXC_ECC140_MIN_SIZE = MXC_SIZE_17,
  MXC_ECC200_MIN_SIZE = MXC_SIZE_10,
  MXC_MIN_SIZE_UNKNOWN  = 0xFFFFFFFF
};


enum MXC_MAX_SYMBOL_SIZE
{
  MXC_ECC000_MAX_SIZE = MXC_SIZE_49,
  MXC_ECC050_MAX_SIZE = MXC_SIZE_49,
  MXC_ECC080_MAX_SIZE = MXC_SIZE_49,
  MXC_ECC100_MAX_SIZE = MXC_SIZE_49,
  MXC_ECC140_MAX_SIZE = MXC_SIZE_49,
  MXC_ECC200_MAX_SIZE = MXC_SIZE_16_48,
  MXC_MAX_SIZE_UNKNOWN  = 0xFFFFFFFF
};


enum MXC_ECC_FAMILY { 
  MXC_ECC000, 
  MXC_ECC050, 
  MXC_ECC080, 
  MXC_ECC100, 
  MXC_ECC140,
  MXC_ECC200, 
  MXC_ECC_UNKNOWN = 0xFFFFFFFE,
  MXC_ECC_FAMILY_UNKNOWN  = 0xFFFFFFFF
};


enum MXC_THRESHOLD_MODES 
{ 
  MXC_ABSOLUTE, 
  MXC_MIN_RESIDUE, 
  MXC_READ_TIME,
  MXC_THRESHOLD_MODES_UNKNOWN  = 0xFFFFFFFF
};


enum MXC_HANDLES 
{ 
  MXC_NO_HANDLE, 
  MXC_CORNER00, 
  MXC_CORNER10, 
  MXC_CORNER11,
  MXC_CORNER01,
  MXC_ADD_CORNER = MXC_NO_HANDLE,
  MXC_HANDLE_UNKNOWN  = 0xFFFFFFFF
};


enum MXC_SYMBOL_FLIPPING
{
  MXC_FLIPPING_FALSE,
  MXC_FLIPPING_TRUE,
  
  MXC_FLIPPING_UNKNOWN  = 0xFFFFFFFF
};


unsigned char const WhiteChar = 219;
unsigned char const BlackChar = ' ';

struct EMatrixPosition
{
  // Score
  FLOAT32 m_f32Score;
  
  // Source level
  UINT32 m_un32Level;
  
  // Best level for digitization
  UINT32 m_un32DigitizeLevel;
  
  // Outer edges
  INT32 m_n32X0, m_n32X1, m_n32X2, m_n32X3;
  INT32 m_n32Y0, m_n32Y1, m_n32Y2, m_n32Y3;

  // Shape check
  BOOL Skewed( );

  // Shape overlaying
  BOOL Overlaid( EMatrixPosition& Position);
};


struct EBitPosition
{
  unsigned short Byte;
  unsigned char Weight;
};

class EMatrixCode
{
public:
  // Default constructor/destructor
  E_DLL0 CONSTRUCTOR E_DLL1  EMatrixCode( enum MXC_SYMBOL_SIZE eSize = MXC_SIZE_UNKNOWN);
  E_DLL0 DESTRUCTOR E_DLL1  ~EMatrixCode( );
  
  // Symbol type
  // . ECC family
  E_DLL0 enum MXC_ECC_FAMILY E_DLL1  GetEccFamily( ) { return m_eEccFamily; }
  E_DLL0 void E_DLL1  SetEccFamily( enum MXC_ECC_FAMILY eEccFamily) { m_eEccFamily = eEccFamily; }

  // . Size
  E_DLL0 enum MXC_SYMBOL_SIZE E_DLL1  GetSymbolSize( ) { return m_eSymbolSize; }
  E_DLL0 void E_DLL1  SetSymbolSize( enum MXC_SYMBOL_SIZE eSymbolSize);

  E_DLL0 UINT32 E_DLL1  GetSymbolWidth( ) { return m_un32SymbolWidth; }
  E_DLL0 UINT32 E_DLL1  GetSymbolHeight( ) { return m_un32SymbolHeight; }
  E_DLL0 void E_DLL1  GetCellPitch( FLOAT32& f32PitchX, FLOAT32& f32PitchY);
  E_DLL0 void E_DLL1  SetCellPitch( FLOAT32 f32PitchX, FLOAT32 f32PitchY);
  
  // . Contrast
  E_DLL0 enum MXC_SYMBOL_CONTRAST E_DLL1  GetContrast( ) { return m_eContrast; }
  E_DLL0 void E_DLL1  SetContrast( enum MXC_SYMBOL_CONTRAST eContrast) { m_eContrast = eContrast; }

  // . Flipping
  E_DLL0 enum MXC_SYMBOL_FLIPPING E_DLL1  GetFlipping( ) { return m_eFlipping; }
  E_DLL0 void E_DLL1  SetFlipping( enum MXC_SYMBOL_FLIPPING eFlipping) { m_eFlipping = eFlipping; }

  // Auto-detection
  // . Corner placement
  E_DLL0 void E_DLL1  SetImage( EROIBW8* pImage);
  E_DLL0 void E_DLL1  ResetCorners( );
  E_DLL0 void E_DLL1  DrawCorners( HDC hDC,
    FLOAT32 f32ZoomX = 1.f, FLOAT32 f32ZoomY = 0.f, FLOAT32 f32PanX = 0.f, FLOAT32 f32PanY = 0.f);
  E_DLL0 void E_DLL1  DrawCornersErrors( HDC hDC,
    FLOAT32 f32ZoomX = 1.f, FLOAT32 f32ZoomY = 0.f, FLOAT32 f32PanX = 0.f, FLOAT32 f32PanY = 0.f);
  E_DLL0 void E_DLL1  DrawCorners( Euresys::DrawAdapter* drawAdapter,
    FLOAT32 f32ZoomX = 1.f, FLOAT32 f32ZoomY = 0.f, FLOAT32 f32PanX = 0.f, FLOAT32 f32PanY = 0.f);
  E_DLL0 void E_DLL1  DrawCornersErrors( Euresys::DrawAdapter* drawAdapter,
    FLOAT32 f32ZoomX = 1.f, FLOAT32 f32ZoomY = 0.f, FLOAT32 f32PanX = 0.f, FLOAT32 f32PanY = 0.f);
  E_DLL0 enum MXC_HANDLES E_DLL1  HitTest( INT32 n32CursorX, INT32 n32CursorY,
    FLOAT32 f32ZoomX = 1.f, FLOAT32 f32ZoomY = 0.f, FLOAT32 f32PanX = 0.f, FLOAT32 f32PanY = 0.f);
  E_DLL0 void E_DLL1  Drag( enum MXC_HANDLES eHandle, INT32 n32CursorX, INT32 n32CursorY, 
    FLOAT32 f32ZoomX = 1.f, FLOAT32 f32ZoomY = 0.f, FLOAT32 f32PanX = 0.f, FLOAT32 f32PanY = 0.f);
  
  // . Detection
  E_DLL0 void E_DLL1  AutoDetect
    ( EROIBW8* pImage,
    enum MXC_SYMBOL_SIZE eSize,
    enum MXC_SYMBOL_ORIENTATION eOrientation,
    enum MXC_SYMBOL_CONTRAST eContrast,
    char* Out = NULL,
    UINT32 un32Length = 0);
  E_DLL0 void E_DLL1  AutoDetect
    ( EROIBW8* pImage,
    enum MXC_SYMBOL_SIZE eSize,
    enum MXC_SYMBOL_ORIENTATION eOrientation,
    enum MXC_SYMBOL_CONTRAST eContrast,
    UNICHAR* Out,
    UINT32 un32Length);
  
  // Automatic reading
  E_DLL0 void E_DLL1  AutoReadSymbol( EROIBW8* pImage, char* pszString, UINT32 un32Length);
  E_DLL0 void E_DLL1  AutoReadSymbol( EROIBW8* pImage, UNICHAR* pszString, UINT32 un32Length);
  void EMatrixCode::AutoReadSymbol2( EROIBW8* pImage, char* pszString, UINT32 un32Length);
  
  // Drawing
  E_DLL0 void E_DLL1  Draw( HDC hDC, FLOAT32 f32ZoomX = 1.f, FLOAT32 f32ZoomY = 0.f, FLOAT32 f32PanX = 0.f, FLOAT32 f32PanY = 0.f);
  E_DLL0 void E_DLL1  DrawErrors( HDC hDC, FLOAT32 f32ZoomX = 1.f, FLOAT32 f32ZoomY = 0.f, FLOAT32 f32PanX = 0.f, FLOAT32 f32PanY = 0.f);
  E_DLL0 void E_DLL1  DrawPosition( HDC hDC, FLOAT32 f32ZoomX = 1.f, FLOAT32 f32ZoomY = 0.f, FLOAT32 f32PanX = 0.f, FLOAT32 f32PanY = 0.f);
  E_DLL0 void E_DLL1  DrawPositions( HDC hDC, FLOAT32 f32ZoomX = 1.f, FLOAT32 f32ZoomY = 0.f, FLOAT32 f32PanX = 0.f, FLOAT32 f32PanY = 0.f);
  E_DLL0 void E_DLL1  DrawCells( HDC hDC, FLOAT32 f32ZoomX = 1.f, FLOAT32 f32ZoomY = 0.f, FLOAT32 f32PanX = 0.f, FLOAT32 f32PanY = 0.f);
  E_DLL0 void E_DLL1  Draw( Euresys::DrawAdapter* drawAdapter, FLOAT32 f32ZoomX = 1.f, FLOAT32 f32ZoomY = 0.f, FLOAT32 f32PanX = 0.f, FLOAT32 f32PanY = 0.f);
  E_DLL0 void E_DLL1  DrawErrors( Euresys::DrawAdapter* drawAdapter, FLOAT32 f32ZoomX = 1.f, FLOAT32 f32ZoomY = 0.f, FLOAT32 f32PanX = 0.f, FLOAT32 f32PanY = 0.f);
  E_DLL0 void E_DLL1  DrawPosition( Euresys::DrawAdapter* drawAdapter, FLOAT32 f32ZoomX = 1.f, FLOAT32 f32ZoomY = 0.f, FLOAT32 f32PanX = 0.f, FLOAT32 f32PanY = 0.f);
  E_DLL0 void E_DLL1  DrawPositions( Euresys::DrawAdapter* drawAdapter, FLOAT32 f32ZoomX = 1.f, FLOAT32 f32ZoomY = 0.f, FLOAT32 f32PanX = 0.f, FLOAT32 f32PanY = 0.f);
  E_DLL0 void E_DLL1  DrawCells( Euresys::DrawAdapter* drawAdapter, FLOAT32 f32ZoomX = 1.f, FLOAT32 f32ZoomY = 0.f, FLOAT32 f32PanX = 0.f, FLOAT32 f32PanY = 0.f);
  
  // Rough location
  // . Segmentation
  E_DLL0 enum MXC_THRESHOLD_MODES E_DLL1  GetLocationThresholdMode( ) { return m_eLocationThresholdMode; }
  E_DLL0 void E_DLL1  SetLocationThresholdMode( enum MXC_THRESHOLD_MODES eLocationThresholdMode) { m_eLocationThresholdMode = eLocationThresholdMode; }

  E_DLL0 UINT32 E_DLL1  GetLocationThreshold( ) { return m_un32LocationThreshold; }
  E_DLL0 void E_DLL1  SetLocationThreshold( UINT32 un32LocationThreshold) { m_un32LocationThreshold = un32LocationThreshold; }

  E_DLL0 BOOL E_DLL1  GetImproveConnexity( ) { return m_bImproveConnexity; }
  E_DLL0 void E_DLL1  SetImproveConnexity( BOOL bImproveConnexity) { m_bImproveConnexity = bImproveConnexity; }

  // Fine location  
  // . Skew range
  E_DLL0 FLOAT32 E_DLL1  GetSkewBias( ) { return EFromRadians( m_f32SkewBias); }
  E_DLL0 void E_DLL1  SetSkewBias( FLOAT32 f32SkewBias) { m_f32SkewBias = EToRadians( f32SkewBias); }

  E_DLL0 FLOAT32 E_DLL1  GetSkewTolerance( ) { return EFromRadians( m_f32SkewTolerance); }
  E_DLL0 void E_DLL1  SetSkewTolerance( FLOAT32 f32SkewTolerance);

  E_DLL0 FLOAT32 E_DLL1  GetSkewStep( ) { return EFromRadians( m_f32SkewStep); }
  E_DLL0 void E_DLL1  SetSkewStep( FLOAT32 f32SkewStep);

  E_DLL0 UINT32 E_DLL1  GetSkewCount( ) { return m_un32SkewCount; }
  E_DLL0 void E_DLL1  SetSkewCount( UINT32 un32SkewCount);

  // . Scale range
  E_DLL0 FLOAT32 E_DLL1  GetScaleBias( ) { return m_f32ScaleBias; }
  E_DLL0 void E_DLL1  SetScaleBias( FLOAT32 f32ScaleBias) { m_f32ScaleBias = f32ScaleBias; }

  E_DLL0 FLOAT32 E_DLL1  GetScaleTolerance( ) { return m_f32ScaleTolerance; }
  E_DLL0 void E_DLL1  SetScaleTolerance( FLOAT32 f32ScaleTolerance);

  E_DLL0 FLOAT32 E_DLL1  GetScaleStep( ) { return m_f32ScaleStep; }
  E_DLL0 void E_DLL1  SetScaleStep( FLOAT32 f32ScaleStep);

  E_DLL0 UINT32 E_DLL1  GetScaleCount( ) { return m_un32ScaleCount; }
  E_DLL0 void E_DLL1  SetScaleCount( UINT32 un32ScaleCount);

  // Analysis
  E_DLL0 enum MXC_THRESHOLD_MODES E_DLL1  GetReadingThresholdMode( ) { return m_eReadingThresholdMode; }
  E_DLL0 void E_DLL1  SetReadingThresholdMode( enum MXC_THRESHOLD_MODES eReadingThresholdMode) { m_eReadingThresholdMode = eReadingThresholdMode; }

  E_DLL0 UINT32 E_DLL1  GetReadingThreshold( ) { return m_un32ReadingThreshold; }
  E_DLL0 void E_DLL1  SetReadingThreshold( UINT32 un32ReadingThreshold) { m_un32ReadingThreshold = un32ReadingThreshold; }

  E_DLL0 UINT32 E_DLL1  GetNumErrors( ) { return m_un32NumErrors; }
  E_DLL0 FLOAT32 E_DLL1  GetCellFilling( ) { return m_f32CellFilling; }
  E_DLL0 void E_DLL1  SetCellFilling( FLOAT32 f32CellFilling) { m_f32CellFilling = f32CellFilling; }

  E_DLL0 void E_DLL1  ReadSymbol( EROIBW8* pImage, char* pszString, UINT32 un32Length);
  E_DLL0 void E_DLL1  ReadSymbol( EROIBW8* pImage, UNICHAR* pszString, UINT32 un32Length);
  
  // Print quality measures
  E_DLL0 BOOL E_DLL1  GetCheckPrintQuality( ) { return m_bCheckPrintQuality; }
  E_DLL0 void E_DLL1  SetCheckPrintQuality( BOOL bCheckPrintQuality) { m_bCheckPrintQuality = bCheckPrintQuality; }

  E_DLL0 FLOAT32 E_DLL1  GetSymbolContrast( );
  E_DLL0 FLOAT32 E_DLL1  GetPrintGrowth( );
  E_DLL0 FLOAT32 E_DLL1  GetAxialNonuniformity( );
  E_DLL0 FLOAT32 E_DLL1  GetUnusedErrorCorrection( );
  
  E_DLL0 void E_DLL1  SetPrintGrowthRange( FLOAT32 f32Minimum = 0.f, FLOAT32 f32Nominal = 1.f, FLOAT32 f32Maximum = 2.f);
  E_DLL0 FLOAT32 E_DLL1  GetMinimumPrintGrowth( );
  E_DLL0 FLOAT32 E_DLL1  GetNominalPrintGrowth( );
  E_DLL0 FLOAT32 E_DLL1  GetMaximumPrintGrowth( );
  E_DLL0 FLOAT32 E_DLL1  GetMeasuredPrintGrowth( );
  
  // Print quality grading
  E_DLL0 UINT32 E_DLL1  GetSymbolContrastGrade( );
  E_DLL0 UINT32 E_DLL1  GetPrintGrowthGrade( );
  E_DLL0 UINT32 E_DLL1  GetAxialNonuniformityGrade( );
  E_DLL0 UINT32 E_DLL1  GetUnusedErrorCorrectionGrade( );
  E_DLL0 UINT32 E_DLL1  GetOverallGrade( );
  
  // Persistent storage
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

  
  // For debugging purposes only
  EROIBW8 m_SearchRoi;
  EImageBW8 m_Image;
  EImageBW8 m_Blurred;
  EImageBW8 m_Reduced;  
  EPyramid m_Pyramid;
  ECodedImage m_Blobs;
  HDC m_hDC;
  HGDIOBJ m_hRedPen, m_hGreenPen, m_hBluePen;

  INT32 m_n32Reserved0, m_n32Reserved1, m_n32Reserved2, m_n32Reserved3, m_n32Reserved4, m_n32Reserved5, m_n32Reserved6;
  FLOAT32 m_f32Reserved0, m_f32Reserved1, m_f32Reserved2, m_f32Reserved3, m_f32Reserved4;
  
  // Location
  E_DLL0 void E_DLL1  RoughLocation( EROIBW8* pImage);
  E_DLL0 void E_DLL1  FineLocation( );
  E_DLL0 void E_DLL1  AutoFind( );

  // Digitization
  E_DLL0 void E_DLL1  AutoDigitize( BOOL bFlip, std::vector<bool> *pn32ThresholdDistanceVector);

  // Decoding
  E_DLL0 void E_DLL1  DecodeSymbol( char* Out, UINT32 un32Length);
  
  E_DLL0 FLOAT32 E_DLL1  GetCenterX( ) { return m_f32CenterX; }

  E_DLL0 FLOAT32 E_DLL1  GetCenterY( ) { return m_f32CenterY; }

  E_DLL0 FLOAT32 E_DLL1  GetSkew( ) { return m_f32Skew; }

  E_DLL0 FLOAT32 E_DLL1  GetScale( ) { return m_f32Scale; }

protected:
  const static UINT32           m_un32FileVersion;
  const static UINT8            m_pun8FileSignature[4];

  enum MXC_ECC_FAMILY m_eEccFamily; 
  enum MXC_SYMBOL_SIZE m_eSymbolSize; 
  enum MXC_SYMBOL_CONTRAST m_eContrast; 
  enum MXC_SYMBOL_FLIPPING m_eFlipping; 
  enum MXC_THRESHOLD_MODES m_eLocationThresholdMode; 
  UINT32 m_un32LocationThreshold; 
  BOOL m_bImproveConnexity; 
  FLOAT32 m_f32SkewBias; 
  FLOAT32 m_f32SkewTolerance; 
  FLOAT32 m_f32SkewStep; 
  UINT32 m_un32SkewCount; 
  FLOAT32 m_f32ScaleBias; 
  FLOAT32 m_f32ScaleTolerance; 
  FLOAT32 m_f32ScaleStep; 
  UINT32 m_un32ScaleCount; 
  enum MXC_THRESHOLD_MODES m_eReadingThresholdMode; 
  UINT32 m_un32ReadingThreshold; 
  FLOAT32 m_f32CellFilling; 
  BOOL m_bCheckPrintQuality; 
  FLOAT32 m_f32CenterX; 
  FLOAT32 m_f32CenterY; 
  FLOAT32 m_f32Skew; 
  FLOAT32 m_f32Scale; 

  // Source image
  EROIBW8* m_pSrc;
  INT32 m_n32SrcWidth, m_n32SrcHeight;
  
  // Symbol type
  // . Size
  UINT32 m_un32SymbolWidth, m_un32SymbolHeight;
  
  // . Available symbol sizes
  static const UINT8 m_pun8SymbolWidth[MXC_ECC200_MAX_SIZE - MXC_ECC000_MIN_SIZE + 1];
  static const UINT8 m_pun8SymbolHeight[MXC_ECC200_MAX_SIZE - MXC_ECC000_MIN_SIZE + 1];
  
  // Position
  INT32 m_n32OrgX, m_n32OrgY;
  
  // Auto-search
  // . Scoring
  FLOAT32 ScoreFinder( INT32 n32X0, INT32 n32Y0, INT32 n32X1, INT32 n32Y1, INT32 n32X2, INT32 n32Y2, INT32 n32X3, INT32 n32Y3);
  void ScoreEdge( INT32 n32X0, INT32 n32Y0, INT32 n32X1, INT32 n32Y1, FLOAT32& f32PosScore, FLOAT32& f32NegScore);
  FLOAT32 m_f32BestCorrelation;
  
  // . Fine search
  BOOL m_bAbsolute;
  E_DLL0 FLOAT32 E_DLL1  Improve( EROIBW8* pSrc, INT32 n32Radius);
  //FLOAT32 EMatrixCode::Improve2(EROIBW8* pSrc);

  // . Helpers
  E_DLL0 void E_DLL1  UpdatePosition( );
  
  // . Rigid placement
  FLOAT32 m_f32SizeX, m_f32SizeY;
  FLOAT32 m_f32NominalSkew;
  FLOAT32 m_f32NominalScale;
  
  // . Found instances
  UINT32 m_un32MaxPositions, m_un32NumPositions, m_un32CurPosition;
  EMatrixPosition m_pPosition[32];
  
  // Auto-detection
  // . Corners
  UINT32 m_un32NumCorners;
  FLOAT32 m_f32P00X, m_f32P00Y;
  FLOAT32 m_f32P10X, m_f32P10Y;
  FLOAT32 m_f32P11X, m_f32P11Y;
  FLOAT32 m_f32P01X, m_f32P01Y;
  
  // . Corners orientation  
  MXC_SYMBOL_ORIENTATION m_eOrientation;
  
  UINT32 m_un32NumFineIterations;
  
  // . Actual cell size
  FLOAT32 m_f32CellPitchX, m_f32CellPitchY;
  
  // Fine location
  // . Search area
  UINT32 m_un32SearchMargin;
  
  // . Scoring
  FLOAT32 m_f32Score;
  
  // Symbol data
  // . Codewords array ( 144 x 144 capacity)
  UINT8 m_pCodeword[20164 + 1];
  UINT8 m_pCodewordCopy[20164 + 1];
  UINT8* m_pData, * m_pDataEnd;
  UINT8 m_Matrix[144 * 144 + 1];
  
  // . Analysis
  void DigitizeSymbol( );
  void DigitizeFromCorners( EROIBW8* pSrc);

  // Decoding
  void Input( UINT8& Codeword);
  void EMatrixCode::GetStableDecoding(BOOL bFlip, char* pszString, UINT32 un32Length);

  // Grading
  FLOAT32 m_f32MinimumPrintGrowth, m_f32NominalPrintGrowth, m_f32MaximumPrintGrowth;
  EBWHistogramVector m_Histo;
  FLOAT32 m_f32SymbolContrast, m_f32PrintGrowth, m_f32UnusedErrorCorrection;
  UINT32 m_un32NumBlackCells, m_un32NumWhiteCells;
  
  // Reading
  UINT32 m_un32NumErrors;
  
  // Serialization
  static const UINT8 m_un8Signature;  
  static const UINT8 m_un8Version;
  
  // Fine location
  void Resample( EROIBW8* pSrc, UINT32 un32Margin, UINT32 un32Scale, FLOAT32 f32CenterX, FLOAT32 f32CenterY, FLOAT32 f32Skew, FLOAT32 f32Scale);
  FLOAT32 Score( EROIBW8* pImg, FLOAT32 f32CenterX, FLOAT32 f32CenterY, FLOAT32 f32Skew, FLOAT32 f32Scale);
  void BestScore( EROIBW8* pImg, FLOAT32& f32BestX, FLOAT32& f32BestY, FLOAT32& f32BestScore);
  
  // Analysis
  UINT32 ReadingThreshold( EROIBW8* pImg, INT32 n32X, INT32 n32Y);

  // AffineTransformCoefficientsStruct
  FLOAT32 m_f32Axx, m_f32Axy, m_f32Ax, m_f32Ayx, m_f32Ayy, m_f32Ay;
  
  // Grading
  void CheckPrintQuality( EROIBW8* pSrc, BOOL bAutoRead = FALSE);
  
  // Array Sizes
  UINT32 m_un32DataHeight, m_un32DataWidth, m_un32MatrixWidth, m_un32MatrixHeight, m_un32RegionWidth, m_un32RegionHeight;

  // Region
  EBitPosition* m_pRegion;

  // Region Size
  INT32 m_n32nrow, m_n32ncol;

  // Helpers
  void Helper1( int row, int col, int chr, int bit);
  void Helper2( int row, int col, int chr);
  void Helper3( int chr);
  void Helper4( int chr);
  void Helper5( int chr);
  void Helper6( int chr);
  void Helper7( );

  // Setup Arrays Sizes
  void SetupArrays( int Size, int Width, int Height, unsigned char* pMatrix);
  void ReleaseArrays( );

  // Unscramble and mark errors for ECC200
  unsigned int UnscrambleECC200( unsigned char* In, unsigned int NumCodewords, unsigned char* pMatrix, int bCompare = 0);

  // Error Correction
#define MAXELEMENTS1  256
#define  MAXELEMENTS2  37
  
  INT32 m_pn32WorkArray1[255];
  INT32 m_pn32WorkArray2[256];
  INT32 m_pn32WorkArray3[MAXELEMENTS1];
  INT32 m_pn32WorkArray4[MAXELEMENTS1];
  INT32 m_pn32WorkArray5[MAXELEMENTS2*( MAXELEMENTS2+10)];
  INT32 m_pn32WorkArray6[MAXELEMENTS2];
  INT32 m_pn32WorkArray7[MAXELEMENTS2];

  INT32  m_n32WorkValue1;

  void ProtectECC200( unsigned char *sym, INT32 size);
  
  INT32 CorrectECC200( unsigned char *sym, INT32 code, float* punused);

  //Helpers
  void Helper8( ); 
  void Helper9( INT32 size);
  void Helper10( INT32 size);
  void Helper11( unsigned char *sym, INT32 size, INT32 rssize, INT32 isize, INT32 v);

  INT32 Helper12( INT32 size);
  INT32 Helper13( INT32 size);
  INT32 Helper14( INT32, INT32);
  INT32 Helper15( INT32, INT32);

  // Helpers
  friend void Output( UINT8 Codeword);
  friend void Input( UINT8& Codeword);
};

#ifndef DOTNET_EVISION_WRAPPER

namespace Euresys { 
  namespace eVision { 
    namespace	EasyMatrixCode {



      struct SearchParamsType
      {
        SearchParamsType( ) {};
        Utils::Vector<EasyMatrixCode::LogicalSize::Type>  LogicalSize;
        Utils::Vector<EasyMatrixCode::Contrast::Type>     Contrast;
        Utils::Vector<EasyMatrixCode::Flipping::Type>     Flipping;
        Utils::Vector<EasyMatrixCode::Family::Type>    Family;
        Utils::Vector<EasyMatrixCode::PassType::Type>     Passes;
//        INT32                                             LocationThreshold;
//        INT32                                             ReadingThreshold;
        /*-- PUSCV --*/
      private :
        SearchParamsType(const SearchParamsType&);
        SearchParamsType& operator=(const SearchParamsType&);
      };

      typedef Utils::FlagMask<LearnParams::Type> LearnMaskType;
      std::ostream& operator<<( std::ostream&, const LearnMaskType& );

      namespace LearnParams
      {
        std::ostream& operator<<( std::ostream&, const Type& );
      }

      namespace LogicalSize
      {
        std::ostream&	operator<<(	std::ostream&, const Type& );
      }

      namespace Family
      {
        std::ostream&	operator<<(	std::ostream&, const Type& );
      }

      namespace Contrast
      {
        std::ostream&	operator<<(	std::ostream&, const Type& );
      }
      
      namespace Flipping
      {
        std::ostream&	operator<<(	std::ostream&, const Type& );
      }

      namespace PassType
      {
        std::ostream&	operator<<(	std::ostream&, const Type& );
      }

      namespace ThresholdMode
      {
        std::ostream&	operator<<(	std::ostream&, const Type& );
      }

      namespace Handles
      {
        std::ostream&	operator<<(	std::ostream&, const Type& );
      }
    }


    struct MatrixCode_Impl;
    struct MatrixCodeReader_Impl;

    struct MatrixCode
    {
      // Wrapping members
    public:
      int handle_;
      FinalizeCallback callback_;

      E_DLL0 CONSTRUCTOR  E_DLL1  MatrixCode  ( );
      E_DLL0 CONSTRUCTOR  E_DLL1  MatrixCode  ( const MatrixCode&);
      E_DLL0 MatrixCode&  E_DLL1  operator=   ( const MatrixCode&);
      E_DLL0 DESTRUCTOR   E_DLL1 ~MatrixCode  ( );
      E_DLL0 void         E_DLL1  Draw        ( HDC hDC, FLOAT32 f32ZoomX = 1.f, FLOAT32 f32ZoomY = 0.f, FLOAT32 f32PanX = 0.f, FLOAT32 f32PanY = 0.f);
      E_DLL0 void         E_DLL1  DrawErrors  ( HDC hDC, FLOAT32 f32ZoomX = 1.f, FLOAT32 f32ZoomY = 0.f, FLOAT32 f32PanX = 0.f, FLOAT32 f32PanY = 0.f);
      E_DLL0 void         E_DLL1  Draw        ( Euresys::DrawAdapter* drawAdapter, FLOAT32 f32ZoomX = 1.f, FLOAT32 f32ZoomY = 0.f, FLOAT32 f32PanX = 0.f, FLOAT32 f32PanY = 0.f);
      E_DLL0 void         E_DLL1  DrawErrors  ( Euresys::DrawAdapter* drawAdapter, FLOAT32 f32ZoomX = 1.f, FLOAT32 f32ZoomY = 0.f, FLOAT32 f32PanX = 0.f, FLOAT32 f32PanY = 0.f);
      E_DLL0 void         E_DLL1  Save        ( const char* );  
      E_DLL0 void         E_DLL1  Load        ( const char* );  
      E_DLL0 void         E_DLL1  Save        ( const UNICHAR* );
      E_DLL0 void         E_DLL1  Load        ( const UNICHAR* );
      E_DLL0 void         E_DLL1  Save        ( FILE* );
      E_DLL0 void         E_DLL1  Load        ( FILE* );
      E_DLL0 void         E_DLL1  Save        ( ESerializer* );
      E_DLL0 void         E_DLL1  Load        ( ESerializer* );

      Utils::Properties::HolderOpt<MatrixCode, std::string>
        DecodedString; // D
      Utils::Properties::HolderOptT<MatrixCode, INT32>
        NumErrors; // D
      Utils::Properties::HolderOptT<MatrixCode, EasyMatrixCode::LogicalSize::Type>
        LogicalSize; // D
      Utils::Properties::HolderOptT<MatrixCode, EasyMatrixCode::Contrast::Type>
        ContrastType; // D
      Utils::Properties::HolderOptT<MatrixCode, EasyMatrixCode::Flipping::Type>
        Flipping; // D
      Utils::Properties::HolderOptT<MatrixCode, EasyMatrixCode::Family::Type>       
        Family; // D
      Utils::Properties::HolderOptT<MatrixCode, INT32>                              
        LogicalSizeWidth; // D
      Utils::Properties::HolderOptT<MatrixCode, INT32>                              
        LogicalSizeHeight; // D
      Utils::Properties::HolderOptT<MatrixCode, INT32>                              
        LocationThreshold; // D
      Utils::Properties::HolderOptT<MatrixCode, INT32>                              
        ReadingThreshold; // D
      Utils::Properties::HolderOptT<MatrixCode, BOOL>                               
        IsFound; // D
      Utils::Properties::HolderOptT<MatrixCode, FLOAT32>                            
        Contrast; // D
      Utils::Properties::HolderOptT<MatrixCode, INT32>                              
        ContrastGrade; // D
      Utils::Properties::HolderOptT<MatrixCode, FLOAT32>                            
        PrintGrowth; // D
      Utils::Properties::HolderOptT<MatrixCode, FLOAT32>                            
        MeasuredPrintGrowth; //D 
      Utils::Properties::HolderOptT<MatrixCode, INT32>                              
        PrintGrowthGrade; // D
      Utils::Properties::HolderOptT<MatrixCode, FLOAT32>                            
        AxialNonUniformity; // D
      Utils::Properties::HolderOptT<MatrixCode, INT32>                              
        AxialNonUniformityGrade; // D
      Utils::Properties::HolderOptT<MatrixCode, FLOAT32>                            
        UnusedErrorCorrection; // D
      Utils::Properties::HolderOptT<MatrixCode, INT32>                              
        UnusedErrorCorrectionGrade; // D
      Utils::Properties::HolderOptT<MatrixCode, INT32>                              
        OverallGrade; // D
      Utils::Properties::HolderOptRO<MatrixCode, Point>
        Center;
      Utils::Properties::AdapterT<MatrixCode_Impl, FLOAT32>
        Angle;
      Utils::Properties::ArrayAdapterRO<MatrixCode_Impl, Point>
        Corners;

      Utils::SharedPtr<MatrixCode_Impl>    _reserved;
    };



    struct MatrixCodeReader : private Utils::NonCopyable
    {
      // Wrapping members
    public:
      int handle_;
      FinalizeCallback callback_;

      E_DLL0 CONSTRUCTOR  E_DLL1  MatrixCodeReader  ( );
      E_DLL0 DESTRUCTOR   E_DLL1 ~MatrixCodeReader  ( );
      E_DLL0 MatrixCode   E_DLL1  Read              ( const EROIBW8& );
      E_DLL0 void         E_DLL1  Reset             ( );
      E_DLL0 MatrixCode   E_DLL1  Learn             ( const EROIBW8& );
      E_DLL0 MatrixCode   E_DLL1  LearnMore         ( const EROIBW8& );
      E_DLL0 void         E_DLL1  Save              ( const char* );  
      E_DLL0 void         E_DLL1  Load              ( const char* );  
      E_DLL0 void         E_DLL1  Save              ( const UNICHAR* );
      E_DLL0 void         E_DLL1  Load              ( const UNICHAR* );
      E_DLL0 void         E_DLL1  Save              ( FILE* );
      E_DLL0 void         E_DLL1  Load              ( FILE* );
      E_DLL0 void         E_DLL1  Save              ( ESerializer* );
      E_DLL0 void         E_DLL1  Load              ( ESerializer* );

      bool LearnMask[EasyMatrixCode::LearnParams::NumItems]; // D
      Utils::Properties::Holder < MatrixCodeReader,EasyMatrixCode::SearchParamsType >  SearchParams; // D

      Utils::Properties::ChkHolderT< MatrixCodeReader, INT32 >    PreprocLocalBinHalfKSize; // D
      Utils::Properties::ChkHolderT< MatrixCodeReader, INT32 >    PreprocLocalBinNoise; // D
      Utils::Properties::ChkHolderT< MatrixCodeReader, INT32 >    MaxNumPyramidLevels; // D
      Utils::Properties::ChkHolderT< MatrixCodeReader, INT32 >    MaxNumSkippedLocationLevels; // D
      Utils::Properties::HolderT< MatrixCodeReader, BOOL >        ComputeGrading; // D
      Utils::Properties::ChkHolderT< MatrixCodeReader, INT32 >    LocationLocalBinHalfKSize; // D
      Utils::Properties::ChkHolderT< MatrixCodeReader, INT32 >    LocationLocalBinNoise; // D
      Utils::Properties::ChkHolderT< MatrixCodeReader, INT32 >    CornerShiftStepWidth; // D
      Utils::Properties::ChkHolderT< MatrixCodeReader, INT32 >    CornerShiftStepHeight; // D
      Utils::Properties::ChkHolderT< MatrixCodeReader, FLOAT32 >  MaxHeightWidthRatio; // D
      Utils::Properties::ChkHolderT< MatrixCodeReader, FLOAT32 >  MaxSkew; // D
      Utils::Properties::ChkHolderT< MatrixCodeReader, FLOAT32 >  MinCandidateProba; // D
      Utils::Properties::HolderT< MatrixCodeReader, FLOAT32>      MinimumPrintGrowth; // D S I
      Utils::Properties::HolderT< MatrixCodeReader, FLOAT32>      MaximumPrintGrowth; // D S I
      Utils::Properties::HolderT< MatrixCodeReader, FLOAT32>      NominalPrintGrowth; // D S I
      Utils::Properties::HolderT< MatrixCodeReader, UINT32 >      TimeOut;

      MatrixCodeReader_Impl* _reserved;
    };
  } // namespace eVision
} // namespace Euresys

#endif //DOTNET_EVISION_WRAPPER

#endif //__EMATRIXCODE_H__
