// Easy_CopyBehaviour.h: Easy library header file for eVision 6.7.1.0
//
// Copyright ( c) 1997-2006, Euresys. All rights reserved.
//

#ifndef __EASY_COPYBEHAVIOUR_H__
#define __EASY_COPYBEHAVIOUR_H__

////////////////////////////////////////////////////////////////////////////////////////////////////
// Control of the behaviour of composite objects when using a copy 
// constructor or an assignment operator

E_DLL0 BOOL E_DLL1                  EGetRecursiveCopyBehavior ( );
E_DLL0 void E_DLL1                  ESetRecursiveCopyBehavior ( BOOL bRecursiveCopy);
inline BOOL GetRecursiveCopyBehavior ( )
{
  return EGetRecursiveCopyBehavior( );
}

inline void SetRecursiveCopyBehavior ( BOOL bRecursiveCopy)
{
  ESetRecursiveCopyBehavior(bRecursiveCopy);
}


#endif //__EASY_COPYBEHAVIOUR_H__
