// EOCVCharVector.h: EasyOCV library header file for eVision 6.7.1.0
//
// Copyright ( c) 1997-2006, Euresys. All rights reserved.
//

#ifndef __EOCV_CHAR_VECTOR_H__
#define __EOCV_CHAR_VECTOR_H__

///////////////////////////////////////////////////////////////////////////////
// eVision header files
#include "Easy.h"
#include "EOCVChar.h"

///////////////////////////////////////////////////////////////////////////////
class E_DLL1 EOCVCharVector: public EVectorTemplate<EOCVChar> 
{
public:
  // Constructors
  E_DLL0 CONSTRUCTOR E_DLL1       EOCVCharVector            ( ) { ;}
  E_DLL0 CONSTRUCTOR E_DLL1       EOCVCharVector            ( UINT32 un32MaxElements);
};

///////////////////////////////////////////////////////////////////////////////
#endif //__EOCV_CHAR_VECTOR_H__
