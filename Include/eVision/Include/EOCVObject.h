// EOCVObject.h: EasyOCV library header file for eVision 6.7.1.0
//
// Copyright ( c) 1997-2006, Euresys. All rights reserved.
//

#ifndef __EOCV_OBJECT_H__
#define __EOCV_OBJECT_H__

///////////////////////////////////////////////////////////////////////////////
// eVision header files
#include "Easy.h"
#include "EObject.h"

///////////////////////////////////////////////////////////////////////////////
// Object descriptor
struct EOCVObject
{ 
  EListItem*                      m_pCodedObject;
  BOOL                            m_bSelected;
};

///////////////////////////////////////////////////////////////////////////////
#endif //__EOCV_OBJECT_H__
