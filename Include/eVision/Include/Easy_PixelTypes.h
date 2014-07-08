// Easy_PixelTypes.h: Easy library header file for eVision 6.7.1.0
//
// Copyright ( c) 1997-2006, Euresys. All rights reserved.
//

#ifndef __EASY_PIXELTYPES_H__
#define __EASY_PIXELTYPES_H__

struct EINT32
{
  INT32 m_n32Value;
  // Default constructor
  EINT32( ) {}
  // Initializing constructor
  EINT32( INT32 n32Value ) { m_n32Value = n32Value; }
  // Type conversion operator
  operator INT32() const { return m_n32Value; }
};

struct EF32
{
  FLOAT32 m_f32Value;
  // Default constructor
  EF32( ) {}
  // Initializing constructor
  EF32( FLOAT32 f32Value ) { m_f32Value = f32Value; }
  // Type conversion operator
  operator FLOAT32() const { return m_f32Value; }
};

// RGB triplet, windows 24 bpp bitmap format ( C0 C1 C2 = RGB)
struct EYUY2
{ 
  UINT8 m_un8Y, m_un8U, m_un8V;

  // Default constructor
  EYUY2( ) {}

  // Initializing constructor
  EYUY2( UINT8 un8Y, UINT8 un8U, UINT8 un8V) { m_un8Y= un8Y; m_un8U = un8U; m_un8V = un8V; }
};


// Sub-pixel pointer
typedef union
{
  // Offset/sub-coordinates
  struct {
    INT32 n32Offset;
    INT16 n16SubX, n16SubY;
  } Oxy;

  // Coordinates/sub-coordinates
  struct {
    INT32 n32X, n32Y;
  } XxYy;

} ESubPixel64;


struct EComplex64
  // Complex pair
{ 
  FLOAT32 m_f32Re, m_f32Im;
};

struct ERaw32
  // Raw 32 bits
{
  UINT8 un8Byte[4];
};

struct ERaw96
  // Raw 96 bits
{
  UINT8 un8Byte[12];
};

#endif //__EASY_PIXELTYPES_H__
