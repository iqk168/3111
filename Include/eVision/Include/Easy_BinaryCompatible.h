// Easy_BinaryCompatible.h: Easy library header file for eVision 6.7.1.0
//
// Copyright ( c) 1997-2006, Euresys. All rights reserved.
//

#ifndef __EASY_BINARY_COMPATIBLE_H__
#define __EASY_BINARY_COMPATIBLE_H__

#include "Easy_Compilers.h"
#include "eVision_Types.h"
#ifdef E_GCC
#include <stdio.h>
#endif

struct TripletUINT8
{
  TripletUINT8(UINT8 v0, UINT8 v1, UINT8 v2)
  {
    this->v0 = v0;
    this->v1 = v1;
    this->v2 = v2;
  };
  TripletUINT8()
  {
    this->v0 = 0;
    this->v1 = 0;
    this->v2 = 0;
  };
  UINT8 v0;
  UINT8 v1;
  UINT8 v2;
  UINT8 pad;
};

struct TripletFLOAT
{
  TripletFLOAT(FLOAT32 v0, FLOAT32 v1, FLOAT32 v2)
  {
    this->v0 = v0;
    this->v1 = v1;
    this->v2 = v2;
  };

  TripletFLOAT()
  {
    this->v0 = 0;
    this->v1 = 0;
    this->v2 = 0;
  };

  FLOAT32 v0;
  FLOAT32 v1;
  FLOAT32 v2;
};



////////////////////////////////////////////////////////////////////////////////////////////////////
// Pixel types

// BW structures
typedef struct EBW8
{
  UINT8 m_un8Value;
  // Default constructor
  EBW8( ) {}
  // Initializing constructor
  EBW8( UINT8 un8Value ) { m_un8Value = un8Value; }
  operator UINT8() const { return m_un8Value; }
} EBW8;

struct EBW16
{
  UINT16 m_un16Value;
  // Default constructor
  EBW16( ) {}
  // Initializing constructor
  EBW16( UINT16 un16Value ) { m_un16Value = un16Value; }
  // Type conversion operator
  operator UINT16() const { return m_un16Value; }
  EBW16& operator+=(const UINT16& un16Value) { m_un16Value = m_un16Value + un16Value; return *this; }
};

struct EBW32
{
  UINT32 m_un32Value;
  // Default constructor
  EBW32( ) {}
  // Initializing constructor
  EBW32( UINT32 un32Value ) { m_un32Value = un32Value; }
  // Type conversion operator
  operator UINT32() const { return m_un32Value; }
  EBW32& operator+=(const UINT32& un32Value) { m_un32Value += un32Value; return *this; }
};

struct EFLOAT32
{
  FLOAT32 m_f32Value;
  // Default constructor
  EFLOAT32( ) {}
  // Initializing constructor
  EFLOAT32( FLOAT32 f32Value ) { m_f32Value = f32Value; }
  // Type conversion operator
  operator FLOAT32() const { return m_f32Value; }
  EFLOAT32& operator+=(const FLOAT32& f32Value) { m_f32Value += f32Value; return *this; }
};

struct EFLOAT64
{
  FLOAT64 m_f64Value;
  // Default constructor
  EFLOAT64( ) {}
  // Initializing constructor
  EFLOAT64( FLOAT64 f64Value ) { m_f64Value = f64Value; }
  // Type conversion operator
  operator FLOAT64() const { return m_f64Value; }
  EFLOAT64& operator+=(const FLOAT64& f64Value) { m_f64Value += f64Value; return *this; }
};
// RGB triplet, windows 15 bpp bitmap format ( C0 C1 C2 = RGB)
struct EC15
{ 
  UINT16 m_un5C2:5, m_un5C1:5, m_un5C0:5, m_un8Pad:1;

  // Default constructor
  EC15( ) {}

  // Initializing constructor
  EC15( UINT8 un8C0, UINT8 un8C1, UINT8 un8C2) { m_un5C2 = un8C2; m_un5C1 = un8C1; m_un5C0 = un8C0; }
};

// EBW1 : unsigned 32 bit value for black and white monochrome images
struct EBW1
{
  UINT32 m_un32Value;

  // Default constructor
  EBW1( )
  {
#ifdef E_GCC
      printf("\n*** Sorry EBW1 Binary images are NOT supported under Linux ***\n");
#endif        
  }
  // Initializing constructor
  EBW1( UINT32 un32Value ) { m_un32Value = un32Value; }
  // Type conversion operator
  operator UINT32() const { return m_un32Value; }
};

// RGB triplet, windows 16 bpp bitmap format ( C0 C1 C2 = RGB)
struct EC16
{ 
  UINT16 m_un5C2:5, m_un6C1:6, m_un5C0:5;

  // Default constructor
  EC16( ) {}

  // Initializing constructor
  EC16( UINT8 un8C0, UINT8 un8C1, UINT8 un8C2) { m_un5C2 = un8C2; m_un6C1 = un8C1; m_un5C0 = un8C0; }
};

// RGB triplet, windows 24 bpp bitmap format ( C0 C1 C2 = RGB)
struct EC24
{ 
  UINT8 m_un8C2, m_un8C1, m_un8C0;

  // Default constructor
  EC24( ) {}

  // Initializing constructor
  EC24( UINT8 un8C0, UINT8 un8C1, UINT8 un8C2) { m_un8C2 = un8C2; m_un8C1 = un8C1; m_un8C0 = un8C0; }
};

// RGB triplet, windows 32 bpp bitmap format ( A C0 C1 C2 = ARGB)
struct EC24A
{ 
  UINT8 m_un8C2, m_un8C1, m_un8C0, m_un8A;

  // Default constructor
  EC24A( ) {}

  // Initializing constructor
  EC24A( UINT8 un8C0, UINT8 un8C1, UINT8 un8C2) { m_un8C2 = un8C2; m_un8C1 = un8C1; m_un8C0 = un8C0; }
};



namespace Euresys
{
  // Simple RGB Color Structure
  class RGBColor
  {
  public:
    int red;
    int green;
    int blue;

    RGBColor()
    {
      red= 0;
      green= 0;
      blue= 0;
    }

    RGBColor(int redIn, int greenIn, int blueIn)
    {
      red= redIn;
      green= greenIn;
      blue= blueIn;
    }

    bool operator==(const RGBColor& color) const
    {
      return ((color.red == red) &&
        (color.green == green) &&
        (color.blue == blue));
    }

    bool operator!=(const RGBColor& color) const
    {
      return !((color.red == red) &&
        (color.green == green) &&
        (color.blue == blue));
    }

    static const RGBColor Black;
    static const RGBColor White;
    static const RGBColor Grey;
    static const RGBColor Red;
    static const RGBColor Blue;
    static const RGBColor NoColor;
  };
}



////////////////////////////////////////////////////////////////////////////////////////////////////
// Color Systems

typedef struct { FLOAT32 m_f32X, m_f32Y, m_f32Z; } EXYZ;
typedef struct { FLOAT32 m_f32R, m_f32G, m_f32B; } ERGB;
typedef struct { FLOAT32 m_f32Y, m_f32U, m_f32V; } EYUV;
typedef struct { FLOAT32 m_f32Y, m_f32I, m_f32Q; } EYIQ;
typedef struct { FLOAT32 m_f32L, m_f32S, m_f32H; } ELSH;
typedef struct { FLOAT32 m_f32I, m_f32S, m_f32H; } EISH;
typedef struct { FLOAT32 m_f32Y, m_f32S, m_f32H; } EYSH;
typedef struct { FLOAT32 m_f32V, m_f32S, m_f32H; } EVSH;
typedef struct { FLOAT32 m_f32L, m_f32A, m_f32B; } ELAB;
typedef struct { FLOAT32 m_f32L, m_f32C, m_f32H; } ELCH;
typedef struct { FLOAT32 m_f32L, m_f32U, m_f32V; } ELUV;

typedef union EColor
{ 
  EXYZ m_XYZ;
  ERGB m_RGB;
  ELAB m_LAB;
  ELUV m_LUV;
  EYUV m_YUV;
  EYIQ m_YIQ;
  ELCH m_LCH;
  ELSH m_LSH;
  EISH m_ISH;
  EVSH m_VSH;
  EYSH m_YSH;

  // Default constructor
  E_DLL0 CONSTRUCTOR E_DLL1             EColor            ( ) {}

  // Initializing constructor                         
  E_DLL0 CONSTRUCTOR E_DLL1             EColor            ( FLOAT32 f32C0, FLOAT32 f32C1, FLOAT32 f32C2) {
    m_RGB.m_f32R = f32C0;
    m_RGB.m_f32G = f32C1;
    m_RGB.m_f32B = f32C2;
  }
} EColor;


#endif //__EASY_BINARY_COMPATIBLE_H__
