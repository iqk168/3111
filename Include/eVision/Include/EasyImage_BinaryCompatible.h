// EasyImage_BinaryCompatible.h: EasyImage library header file for eVision 6.7.1.0
//
// Copyright ( c) 1997-2006, Euresys. All rights reserved.
//

#ifndef __EASYIMAGE_BINARY_COMPATIBLE_H__
#define __EASYIMAGE_BINARY_COMPATIBLE_H__


////////////////////////////////////////////////////////////////////////////////////////////////////
// Vector element types
//

// Path from an image ( coordinates)
struct EPath
{ 
  INT16 m_n16X, m_n16Y;
};


// Path from a BW8 image ( coordinates, pixel value)
struct EBW8Path
{ 
  INT16 m_n16X, m_n16Y;
  EBW8 m_bw8Pixel;
};


// Path from a BW16 image ( coordinates, pixel value)
struct EBW16Path
{ 
  INT16 m_n16X, m_n16Y;
  EBW16 m_bw16Pixel;
};


// Path from a C24 image ( coordinates, pixel value)
struct EC24Path
{ 
  INT16 m_n16X, m_n16Y;
  EC24 m_c24Pixel;
};


// Peak ( position in vector, strength, coordinates)
struct EPeak
{
  UINT32 m_un32Start, m_un32Length;
  FLOAT32 m_f32Center;
  INT32 m_n32Amplitude, m_n32Area;
};




#endif //__EASYIMAGE_BINARY_COMPATIBLE_H__
