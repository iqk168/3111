// Easy_Extern_C.h: Easy library header file for eVision 6.7.1.0
//
// Copyright ( c) 1997-2006, Euresys. All rights reserved.
//

#ifndef __EASY_EXTERN_C_H__
#define __EASY_EXTERN_C_H__

#include "Easy_Compilers.h"


extern "C"
{
  E_DLL0 void E_DLL1 eVision_Free(void* data);
  E_DLL0 void* E_DLL1 eVision_Malloc(int size);

  E_DLL0 void E_DLL1 InternalDLLMain();
  E_DLL0 void E_DLL1 InternalDLLMainExit();
  E_DLL0 void E_DLL1 TraceSilent();

  E_DLL0 void E_DLL1 InitializeThreadLocalStorage();
  E_DLL0 void E_DLL1 CloseThreadLocalStorage();

  // Operator extern C functions for GeneircRoiExtentWithBroadcast.
  E_DLL0 int E_DLL1 GenericRoiExtentWithBroadcast_operatorAssign_GenericRoiExtentWithBroadcast(void* impl, void* src);
  E_DLL0 int E_DLL1 GenericRoiExtentWithBroadcast_operatorAssign_GenericRoiExtent(void* impl, void* src);
  E_DLL0 int E_DLL1 GenericRoiExtentWithBroadcast_operatorEquality_GenericRoiExtentBroadcastingVector_GenericRoiExtentBroadcastingVector(void* src, void* dst, bool* retVal);
  E_DLL0 int E_DLL1 GenericRoiExtentWithBroadcast_operatorInequality_GenericRoiExtentBroadcastingVector_GenericRoiExtentBroadcastingVector(void* src, void* dst, bool* retVal);
}

#endif //__EASY_EXTERN_C_H__

