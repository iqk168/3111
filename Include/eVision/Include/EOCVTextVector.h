// EOCVTextVector.h: EasyOCV library header file for eVision 6.7.1.0
//
// Copyright ( c) 1997-2006, Euresys. All rights reserved.
//

#ifndef __EOCV_TEXT_VECTOR_H__
#define __EOCV_TEXT_VECTOR_H__

///////////////////////////////////////////////////////////////////////////////
// eVision header files
#include "Easy.h"
#include "EOCVText.h"

///////////////////////////////////////////////////////////////////////////////

class E_DLL1 EOCVTextVector: public EVectorTemplate<EOCVText> 
{
public:
  E_DLL0 CONSTRUCTOR E_DLL1       EOCVTextVector            ( ) {}
  E_DLL0 CONSTRUCTOR E_DLL1       EOCVTextVector            ( UINT32 un32MaxElements);
};

///////////////////////////////////////////////////////////////////////////////
#endif //__EOCV_TEXT_VECTOR_H__
