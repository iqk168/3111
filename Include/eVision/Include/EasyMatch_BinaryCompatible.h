// EasyMatch_BinaryCompatible.h: EasyMatch library header file for eVision 6.7.1.0
//
// Copyright ( c) 1997-2006, Euresys. All rights reserved.
//

#ifndef __EASYMATCH_BINARY_COMPATIBLE_H__
#define __EASYMATCH_BINARY_COMPATIBLE_H__


// ---------------------------------------------------------------------------

// Match position
typedef struct
{
  FLOAT32   m_f32CenterX;
  FLOAT32   m_f32CenterY;
  FLOAT32   m_f32Angle;

  union {
    FLOAT32 m_f32Scale;
    FLOAT32 m_f32ScaleX;
  };

  FLOAT32   m_f32ScaleY;
  FLOAT32   m_f32Score;
  BOOL      m_bInterpolated;

  FLOAT32   m_f32AreaRatio;

  FLOAT32   m_f32Reserved;

} EMatchPosition;



#endif //__EASYMATCH_BINARY_COMPATIBLE_H__
