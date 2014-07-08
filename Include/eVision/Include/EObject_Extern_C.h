// EObject_Extern_C.h: EasyObject library header file for eVision 6.7.1.0
//
// Copyright ( c) 1997-2006, Euresys. All rights reserved.
//

#ifndef __EOBJECT_EXTERN_C_H__
#define __EOBJECT_EXTERN_C_H__

#ifdef E_EXTERN_C_BUILD


extern "C"
{

  int FeatureData_Ctor(void** impl);
  int FeatureData_Dtor(void* impl);
  int FeatureData_getSize_INT32(void* impl, int* retVal);
  int FeatureData_setSize_INT32(void* impl, int retVal);
  int FeatureData_getFeatNum_INT32(void* impl, int* retVal);
  int FeatureData_setFeatNum_INT32(void* impl, int retVal);
  int FeatureData_getFeatDataType_INT32(void* impl, int* retVal);
  int FeatureData_setFeatDataType_INT32(void* impl, int retVal);
  int FeatureData_getFeatDataSize_INT32(void* impl, int* retVal);
  int FeatureData_setFeatDataSize_INT32(void* impl, int retVal);
  int ObjectData_Ctor(void** impl);
  int ObjectData_Dtor(void* impl);
  int ObjectData_getClass_INT32(void* impl, int* retVal);
  int ObjectData_setClass_INT32(void* impl, int retVal);
  int ObjectData_getObjNum_INT32(void* impl, int* retVal);
  int ObjectData_setObjNum_INT32(void* impl, int retVal);
  int ObjectData_getObjNbRun_INT32(void* impl, int* retVal);
  int ObjectData_setObjNbRun_INT32(void* impl, int retVal);
  int ObjectData_getObjNbHole_INT32(void* impl, int* retVal);
  int ObjectData_setObjNbHole_INT32(void* impl, int retVal);
  int ObjectData_getIsSelected_INT8(void* impl, signed char* retVal);
  int ObjectData_setIsSelected_INT8(void* impl, signed char retVal);
  int ObjectData_getIsHole_BOOL(void* impl, int* retVal);
  int ObjectData_setIsHole_BOOL(void* impl, int retVal);
  int RunData_Ctor(void** impl);
  int RunData_Dtor(void* impl);
  int RunData_getOrgX_INT32(void* impl, int* retVal);
  int RunData_setOrgX_INT32(void* impl, int retVal);
  int RunData_getOrgY_INT32(void* impl, int* retVal);
  int RunData_setOrgY_INT32(void* impl, int retVal);
  int RunData_getLen_INT32(void* impl, int* retVal);
  int RunData_setLen_INT32(void* impl, int retVal);
  int RunData_getClass_INT32(void* impl, int* retVal);
  int RunData_setClass_INT32(void* impl, int retVal);
  int RunData_getObjNum_INT32(void* impl, int* retVal);
  int RunData_setObjNum_INT32(void* impl, int retVal);


}

#endif //E_EXTERN_C_BUILD

#endif //__EOBJECT_EXTERN_C_H__