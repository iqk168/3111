////////////////////////////////////////////////////////////////////////////////////////////////////
// EOCV.h: EasyOCV library header file for eVision 6.7.1.0
//
// EasyOCV performs optical character verification on printed text
//
// Copyright ( c) 1997-2006, Euresys. All rights reserved.
//

#ifndef __EOCV_H__
#define __EOCV_H__

///////////////////////////////////////////////////////////////////////////////
// eVision header files
#include "EOCV_Enum.h"
#include "EOCV_Main.h"
#include "EOCVChar.h"
#include "EOCVText.h"
#include "EChecker.h"
#include "EOCVObjectVector.h"
#include "EOCVCharVector.h"
#include "EOCVTextVector.h"

///////////////////////////////////////////////////////////////////////////////
#if defined E_BC45
  // Forward declarations of class instances
  template<class Type> class EVectorTemplate;
  class EVectorTemplate<char*>;
#elif defined E_BC50 || defined E_BCB
  // Forward declarations of class instances
  template class E_DLL1 EVectorTemplate<char*>;
#endif

///////////////////////////////////////////////////////////////////////////////
#endif //__EOCV_H__
