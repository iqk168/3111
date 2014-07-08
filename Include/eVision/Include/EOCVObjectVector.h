// EOCVObjectVector.h: EasyOCV library header file for eVision 6.7.1.0
//
// Copyright ( c) 1997-2006, Euresys. All rights reserved.
//

#ifndef __EOCV_OBJECT_VECTOR_H__
#define __EOCV_OBJECT_VECTOR_H__

///////////////////////////////////////////////////////////////////////////////
// eVision header files
#include "Easy.h"
#include "EOCVObject.h"

///////////////////////////////////////////////////////////////////////////////
// Vector of objects
class E_DLL1 EOCVObjectVector: public EVectorTemplate<EOCVObject> 
{
public:
  E_DLL0 CONSTRUCTOR E_DLL1       EOCVObjectVector          ( ) {}
  E_DLL0 CONSTRUCTOR E_DLL1       EOCVObjectVector          ( UINT32 un32MaxElements);
};

///////////////////////////////////////////////////////////////////////////////
#endif //__EOCV_OBJECT_VECTOR_H__
